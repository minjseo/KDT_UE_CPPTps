// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include <Kismet/GameplayStatics.h>
#include "TpsPlayer.h"
#include "Enemy.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// �÷��̾ ã��
	AActor* findActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATpsPlayer::StaticClass());
	target = Cast<ATpsPlayer>(findActor);
	
	// ���� ���͸� ã��
	myActor = Cast<AEnemy>(GetOwner());

	
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ���࿡ Target �� ���ٸ� �Լ��� ������
	if (target == nullptr) return;

	switch (currState)
	{
	case EEnemyState::IDLE:
		UpdateIdle();
		break;
	case EEnemyState::MOVE:
		UpdateMove();
		break;
	case EEnemyState::ATTACK:
		UpdateAttack();
		break;
	case EEnemyState::DAMAGE:
		UpdateDamaged(DeltaTime);
		break;
	default:
		break;
	}
}

void UEnemyFSM::ChangeState(EEnemyState s)
{
	//�ٲ�� ���¸� �������
	UEnum* enumptr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEnemyState"), true);
	if (enumptr != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s -----> %s"), 
		*enumptr->GetNameStringByIndex((int32)currState),
		*enumptr->GetNameStringByIndex((int32)s));
	}


	// ���� ���¸� ����
	currState = s;
	
	// ���� �ð��� �ʱ�ȭ
	currTime = 0;

	switch (currState)
	{
	case EEnemyState::IDLE:

		break;
	case EEnemyState::MOVE:

		break;
	case EEnemyState::ATTACK:
		// �ٷ� ���� �����ϰ� ����ð��� attackDelayTime ���� ����
		currTime = attackDelayTime;
		break;
	case EEnemyState::DIE:
		myActor->Destroy();
		break;
	default:
		break;
	}
}

void UEnemyFSM::UpdateIdle()
{
	// 1. �÷��̾���� �Ÿ��� ������.
	FVector dir = target->GetActorLocation() - myActor->GetActorLocation();
	float dist = dir.Length();
	// 2. ���࿡ �Ÿ��� �������� ���� ������ (�÷��̾ �Ѿư� �� �ִ� ����)
	if (dist < traceRange)
	{
		// 3. ���� ���¸� MOVE �� �ٲ���
		ChangeState(EEnemyState::MOVE);
	}

	UE_LOG(LogTemp, Warning, TEXT("IDLE"));
}

void UEnemyFSM::UpdateMove()
{
	// 1. �÷��̾ ���ϴ� ������ ������
	FVector dir = target->GetActorLocation() - myActor->GetActorLocation();
	
	// 2. �� �������� ��������. 
	myActor->AddMovementInput(dir.GetSafeNormal());

	// 3. �÷��̾���� �Ÿ��� ���� �������� ������
	float dist = dir.Length();
	if (dist < attackRange)
	{
		// 4. ���� ���¸� ATTACK �� �ٲ���
		ChangeState(EEnemyState::ATTACK);	
	}	

	UE_LOG(LogTemp, Warning, TEXT("MOVE"));
}

void UEnemyFSM::UpdateAttack()
{
	// 1. �ð��� �帣�� �Ѵ�.
	currTime += GetWorld()->DeltaTimeSeconds;
	// 2. ���࿡ Attack Delay �ð��� ������
	if (currTime > attackDelayTime)
	{
		// �÷������ �Ÿ�
		float dist = FVector::Distance(target->GetActorLocation(), myActor->GetActorLocation());
		// �� �Ÿ��� ���ݹ���- > ��¥ ����
		if (dist < attackRange)
		{
			// 3. ��¥ ����!!
			UE_LOG(LogTemp, Warning, TEXT("ATTACK"));
		}
		// �������� -> �̵� 
		else if (dist < traceRange)
		{
			ChangeState(EEnemyState::MOVE);
		}
		// �� �ܴ� -> ���
		else
		{
			ChangeState(EEnemyState::IDLE);
		}
		
		// 4. ����ð� �ʱ�ȭ
		currTime = 0;
	}
}

void UEnemyFSM::UpdateDamaged(float deltaTime)
{
	// damageDelayTime ��ٷȴٰ�
	currTime += deltaTime;
	if (currTime > damageDelayTime)
	{
		// IDLE ���·� ��ȯ
		ChangeState(EEnemyState::IDLE);
	}
}

