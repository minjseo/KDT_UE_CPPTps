// Fill out your copyright notice in the Description page of Project Settings.


#include "Minimap.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SceneCaptureComponent2D.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "TpsPlayer.h"

// Sets default values
AMinimap::AMinimap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//USceneCaptureComponent2D �߰�
	compCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CAPTURE"));
	SetRootComponent(compCapture);

	//render Target �о�ͼ� ���� 
	ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D>tempTex(TEXT("/Script/Engine.TextureRenderTarget2D'/Game/Resources/MiniMap/RT_MiniMap.RT_MiniMap'"));
	if (tempTex.Succeeded())
	{
		compCapture->TextureTarget = tempTex.Object;
	}

}

// Called when the game starts or when spawned
void AMinimap::BeginPlay()
{
	Super::BeginPlay();

	player = UGameplayStatics::GetActorOfClass(GetWorld(), ATpsPlayer::StaticClass());
	
	
}

// Called every frame
void AMinimap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�÷��̾��� xy��ǥ�� ������ ���� Tick ����
	FVector myPos = GetActorLocation();
	FVector playerPos = player->GetActorLocation();

	myPos.X = playerPos.X;
	myPos.Y = playerPos.Y;
	SetActorLocation(myPos);

}

