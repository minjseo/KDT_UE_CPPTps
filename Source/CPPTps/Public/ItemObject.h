// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemObject.generated.h"

enum class EItemType : uint8;

UCLASS()
class CPPTPS_API AItemObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//외형 
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;

	//변경되는 속력
	float speed = 0;

	//어떤 Item 인지?
	UPROPERTY(EditAnywhere)
	EItemType itemType;


public:
	//기본동작
	virtual void NormalState();
	//
	virtual void OnHit();
	//virtual void OnHit(); = 0; //순수 가상합수 
	//순수가상함수는 자식에서 override 쓰지않아도 무조건 실행시켜야함 

};
