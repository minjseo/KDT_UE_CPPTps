// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimEnemy.h"
#include "Enemy.h"

void UAnimEnemy::AnimNotify_OnDamage()
{
	UE_LOG(LogTemp, Warning, TEXT("OnDamage!!!!!!"));
	//target(�÷��̾�)�� ���� �ִ� DamageProcess �Լ� ����
	

	//1. ��(=pawn=character= enemy)�� ã��
	APawn* pawn = TryGetPawnOwner();
	AEnemy* myPawn = Cast<AEnemy>(pawn);
	//2. target�� ���� �ִ� DamgeP �Լ� ����
	//myPawn->fsm->target->DamageProcess(10); --> enemy.h �� �̵�
	myPawn->AttackTarget();

}
