// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimPlayer.generated.h"

/**
 * 
 */
UCLASS()
class CPPTPS_API UAnimPlayer : public UAnimInstance
{
	GENERATED_BODY()

public:	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
public:
	
	// ��, �� �Ǻ� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float dirF = 0;

	// ��, �� �Ǻ� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float dirR = 0;

	//���߿� �� �ִ��� ���� 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isAir = false;


};