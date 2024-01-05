// Fill out your copyright notice in the Description page of Project Settings.


#include "TpsPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <InputMappingContext.h>
#include <InputAction.h>
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

// Sets default values
ATpsPlayer::ATpsPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// imc default 파일 읽어오자
	ConstructorHelpers::FObjectFinder<UInputMappingContext> tempImc(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (tempImc.Succeeded())
	{
		imcDefault = tempImc.Object;
	}

	// ia_jump 파일 읽어오자
	ConstructorHelpers::FObjectFinder<UInputAction> tempIAJump(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Jump.IA_Jump'"));
	if (tempIAJump.Succeeded())
	{
		ia_Jump = tempIAJump.Object;
	}

	// Skeletal Mesh 읽어오자
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	
	if (tempMesh.Succeeded())
	{
		// Mesh 에 Skeletal Mesh 셋팅
		//USkeletalMeshComponent* mesh = GetMesh();
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
	}

	// Mesh 의 위치 값과 회전값을 셋팅
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));	
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0)); // Pitch, Yaw, Roll

	//Spring Arm 컴포넌트 생성
	arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ARM"));
	// arm 을 rootComponent 의 자식
	arm->SetupAttachment(RootComponent);
	// arm 위치를 바꾸자
	arm->SetRelativeLocation(FVector(0, 70, 90));

	// Camera 컴포넌트 생성
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("CAM"));
	// cam 을 arm 의 자식으로 셋팅
	cam->SetupAttachment(arm);
}

// Called when the game starts or when spawned
void ATpsPlayer::BeginPlay()
{
	Super::BeginPlay();

	// 움직이는 속력을 moveSpeed 로 하자
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;

	// Controller 의 회전값을 따라 갈지 여부
	bUseControllerRotationYaw = true;
	arm->bUsePawnControlRotation = true;

	// 카메라 상/하 회전값 을 제한 (min, max 설정)
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	playerCon->PlayerCameraManager->ViewPitchMin = -60;
	playerCon->PlayerCameraManager->ViewPitchMax = 60;

	/*APlayerCameraManager* camManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	camManager->ViewPitchMin = -60;
	camManager->ViewPitchMax = 60;*/

	// 점프 횟수 제한
	JumpMaxCount = 3;

	// APlayerController 가져오자
	APlayerController* playerController = Cast<APlayerController>(GetController());
	//subSystem 을 가져오자	
	auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	// imcDefault 추가 하자
	subSystem->AddMappingContext(imcDefault, 0);
}

// Called every frame
void ATpsPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	MoveAction();

	// RotateAction();	
}

// Called to bind functionality to input
void ATpsPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (input)
	{
		input->BindAction(ia_Jump, ETriggerEvent::Started, this, &ATpsPlayer::EnhancedJump);
	}

	
	// A, D
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ATpsPlayer::InputHorizontal);

	// W, S
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ATpsPlayer::InputVertical);

	// 마우스 좌우 움직일 때 
	PlayerInputComponent->BindAxis(TEXT("MouseX"), this, &ATpsPlayer::InputMouseX);
	// 마우스 상하 움직일 때
	PlayerInputComponent->BindAxis(TEXT("MouseY"), this, &ATpsPlayer::InputMouseY);

	// 스페이스바 눌렀을 때 
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ATpsPlayer::InputJump);
}

void ATpsPlayer::MoveAction()
{
	//// p = p0 + vt
	//FVector p0 = GetActorLocation();
	//FVector dir = GetActorRightVector() * moveInput.Y +
	//	GetActorForwardVector() * moveInput.X;
	//// dir 의 크기를 1로 만든다.
	//dir.Normalize();
	//// vt 만큼 움직여라
	//FVector vt = dir * moveSpeed * DeltaTime;
	//// 새로 이동해야 하는 위치
	//FVector p = p0 + vt;
	//SetActorLocation(p);

	FVector dir = GetActorRightVector() * moveInput.Y +
		GetActorForwardVector() * moveInput.X;
	// dir 의 크기를 1로 만든다.
	dir.Normalize();

	// dir 방향으로 움직여라
	AddMovementInput(dir);
}

void ATpsPlayer::RotateAction()
{
	// 나의 회전 yaw (z축) 값 셋팅
	SetActorRotation(FRotator(0, mx, 0));
	// spring arm 의 회전 pitch (y축) 값 셋팅
	arm->SetRelativeRotation(FRotator(my, 0, 0));
}

void ATpsPlayer::InputHorizontal(float value)
{
	moveInput.Y = value;
}

void ATpsPlayer::InputVertical(float value)
{
	moveInput.X = value;
}

void ATpsPlayer::InputMouseX(float value)
{
	AddControllerYawInput(value);

	// 좌, 우 회전하는 값을 누적
	//mx += value;

}

void ATpsPlayer::InputMouseY(float value)
{
	AddControllerPitchInput(value);
	// 상, 하 회전하는 값을 누적
	//my += value;
}

void ATpsPlayer::InputJump()
{
	//Jump();
}

void ATpsPlayer::EnhancedJump()
{
	Jump();
}

