// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimPlayer.h"

void UAnimPlayer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 내가 붙어있는 Pawn 을 가져오자
	APawn* pawn = TryGetPawnOwner();
	if (pawn != nullptr)
	{
		// 나의 앞방향
		FVector forward = pawn->GetActorForwardVector();
		// 이동 방향
		FVector moveDir = pawn->GetVelocity();
		// forward 와 moveDir 의 내적 = cos(두 벡터가 이루는 각) 
		// 위 값이 0보다 크면 앞 방향, 0보다 작으면 뒷 방향
		dirF = FVector::DotProduct(forward, moveDir);
		//dirF = forward.Dot(moveDir);

		// 나의 오른쪽 방향
		FVector right = pawn->GetActorRightVector();
		// right 와 moveDir 의 내적 = cos(두 벡터가 이루는 각) 
		// 위 값이 0보다 크면 오른쪽 방향, 0보다 작으면 왼쪽 방향
		dirR = FVector::DotProduct(right, moveDir);
		UE_LOG(LogTemp, Warning, TEXT("dot : %f"), dirR);
	}
}
