// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimPlayer.h"
#include "TpsPlayer.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h>

void UAnimPlayer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// ���� �پ��ִ� Pawn �� ��������
	ATpsPlayer* pawn = Cast<ATpsPlayer>(TryGetPawnOwner());
	if (pawn)
	{
		// ���� �չ���
		FVector forward = pawn->GetActorForwardVector();
		// �̵� ����
		FVector moveDir = pawn->GetVelocity();
		// forward �� moveDir �� ���� = cos(�� ���Ͱ� �̷�� ��) 
		// �� ���� 0���� ũ�� �� ����, 0���� ������ �� ����
		dirF = FVector::DotProduct(forward, moveDir);
		//dirF = forward.Dot(moveDir);

		//// ������ ǥ���غ��� ( ���� = arcos (�� ������ ����)) 
		//// �� ������ radian �� ǥ���ȴ�.
		//float dot = FVector::DotProduct(forward, moveDir.GetSafeNormal());
		//float radianAngle = FMath::Acos(dot);
		//float degreeAngle = radianAngle * (180 / UE_PI);
		////FMath::DegreesToRadians(90);
		////FMath::RadiansToDegrees(radianAngle)
		//UE_LOG(LogTemp, Warning, TEXT("angle : %f"), degreeAngle);


		// ���� ������ ����
		FVector right = pawn->GetActorRightVector();
		// right �� moveDir �� ���� = cos(�� ���Ͱ� �̷�� ��) 
		// �� ���� 0���� ũ�� ������ ����, 0���� ������ ���� ����
		dirR = FVector::DotProduct(right, moveDir);
		//UE_LOG(LogTemp, Warning, TEXT("dot : %f"), dirR);


		UCharacterMovementComponent* movement = pawn-> GetCharacterMovement(); 
		isAir = movement -> IsFalling();
		
		
		//->IsFalling()
		//ATpsPlayer* pawn = Cast<ATpsPlayer>(TryGetPawnPlayer());
	}
}