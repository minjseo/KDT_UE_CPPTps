// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "ItemCube.generated.h"

UCLASS()
class CPPTPS_API AItemCube : public AItemObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//���� 
	//UPROPERTY(EditAnywhere)
	//class UStaticMeshComponent* compMesh;

	//���� ���� ȸ���� (Yaw Z��) 
	float yaw = 0;
	//ȸ�� �� �ӷ�
	//float speed = 50;

public:
	//�⺻����
	virtual void NormalState() override;
	//
	virtual void OnHit() override;
};