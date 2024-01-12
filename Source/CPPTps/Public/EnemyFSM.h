// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

// Enemy ���¸� ���� (enum ������)
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	IDLE,
	MOVE,
	ATTACK,
	DAMAGE,
	DIE
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPTPS_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ���� ���� ���¸� ���� ����
	EEnemyState currState = EEnemyState::IDLE;

	// Ÿ�� (Player)
	class ATpsPlayer* target;

	// �� ������Ʈ�� � ���Ϳ� �پ��ִ���
	class AEnemy* myActor;

	// �Ѿ� �� �� �ִ� ���� (���� ����)
	UPROPERTY(EditAnywhere)
	float traceRange = 1000;

	// ���� �� �� �ִ� ���� (���� ����)
	UPROPERTY(EditAnywhere)
	float attackRange = 200;

	// ����ð�
	float currTime = 0;
	// ���ݴ��ð�
	UPROPERTY(EditAnywhere)
	float attackDelayTime = 2;
	// �ǰݴ��ð�
	UPROPERTY(EditAnywhere)
	float damageDelayTime = 2;

public:
	// ���°� �ٲ� �ѹ� ���� �Ǵ� �Լ�
	void ChangeState(EEnemyState s);
	// ���
	void UpdateIdle();
	// �̵�
	void UpdateMove();
	// ����
	void UpdateAttack();
	// �ǰ�
	void UpdateDamaged(float deltaTime);
};
