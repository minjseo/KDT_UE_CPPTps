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
	//외형 
	//UPROPERTY(EditAnywhere)
	//class UStaticMeshComponent* compMesh;

	//현재 나의 크기값 (Yaw Z값) 
	float scale = 1;
	//크고 작아지는 속력
	//float speed = 5;
	//내가 커지는 상태 or 작아지는 상태 알기
	bool isGrow = true;
	int32 scaleDir = 1;
	
	//normal state를 실행하게 할건지 말건지
	bool isNormal = true;

public:
	//기본동작
	virtual void NormalState() override;
	//
	virtual void OnHit() override;

};
