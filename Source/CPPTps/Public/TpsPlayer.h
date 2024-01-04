// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TpsPlayer.generated.h"

UCLASS()
class CPPTPS_API ATpsPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATpsPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* arm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* cam;

	// float h;, float v;
	FVector moveInput = FVector(0);

	float moveSpeed = 500;

	// ȸ�� ��
	float mx = 0;
	float my = 0;

public:

	void MoveAction();
	void RotateAction();

	void InputHorizontal(float value);
	void InputVertical(float value);
	void InputMouseX(float value);
	void InputMouseY(float value);
	void InputJump();
};

