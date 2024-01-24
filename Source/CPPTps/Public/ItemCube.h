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
	//외형 
	//UPROPERTY(EditAnywhere)
	//class UStaticMeshComponent* compMesh;

	//현재 나의 회전값 (Yaw Z값) 
	float yaw = 0;
	//회전 한 속력
	//float speed = 50;

public:
	//기본동작
	virtual void NormalState() override;
	//
	virtual void OnHit() override;
};
