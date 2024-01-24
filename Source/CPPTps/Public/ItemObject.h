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
	//���� 
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;

	//����Ǵ� �ӷ�
	float speed = 0;

	//� Item ����?
	UPROPERTY(EditAnywhere)
	EItemType itemType;


public:
	//�⺻����
	virtual void NormalState();
	//
	virtual void OnHit();
	//virtual void OnHit(); = 0; //���� �����ռ� 
	//���������Լ��� �ڽĿ��� override �����ʾƵ� ������ ������Ѿ��� 

};
