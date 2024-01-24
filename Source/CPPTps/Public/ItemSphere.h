// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "ItemSphere.generated.h"

UCLASS()
class CPPTPS_API AItemSphere : public AItemObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSphere();
	

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

	//���� ���� ũ�Ⱚ (Yaw Z��) 
	float scale = 1;
	//ũ�� �۾����� �ӷ�
	//float speed = 5;
	//���� Ŀ���� ���� or �۾����� ���� �˱�
	bool isGrow = true;
	int32 scaleDir = 1;
	
	//normal state�� �����ϰ� �Ұ��� ������
	bool isNormal = true;

public:
	//�⺻����
	virtual void NormalState() override;
	//
	virtual void OnHit() override;

};
