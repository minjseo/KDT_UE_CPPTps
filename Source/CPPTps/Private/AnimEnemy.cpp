// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimEnemy.h"
#include "Enemy.h"

void UAnimEnemy::AnimNotify_OnDamage()
{
	UE_LOG(LogTemp, Warning, TEXT("OnDamage!!!!!!"));
	//target(플레이어)가 갖고 있는 DamageProcess 함수 실행
	

	//1. 나(=pawn=character= enemy)를 찾자
	APawn* pawn = TryGetPawnOwner();
	AEnemy* myPawn = Cast<AEnemy>(pawn);
	//2. target이 갖고 있는 DamgeP 함수 실행
	//myPawn->fsm->target->DamageProcess(10); --> enemy.h 로 이동
	myPawn->AttackTarget();

}
