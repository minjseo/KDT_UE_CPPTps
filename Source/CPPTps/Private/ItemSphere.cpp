// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSphere.h"
#include "Inventory.h"
// Sets default values
AItemSphere::AItemSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	itemType = EItemType::ITEM_SPHERE;
	
}

// Called when the game starts or when spawned
void AItemSphere::BeginPlay()
{
	Super::BeginPlay();

	speed = 5;
	
}

// Called every frame
void AItemSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isNormal == true)
	{
	NormalState();
	}

}

void AItemSphere::NormalState()
{
	//scaleDir �������� ũ�⸦ ���������
	scale += speed * GetWorld()->GetDeltaSeconds() * scaleDir;


	SetActorScale3D(FVector(scale));
	//���࿡ scale ���� 2 ���� Ŀ���ų�
	//scale ���� 1���� �۾����� 
	if (scale > 2 || scale < 1)
	{
		//scale ���� �ּ� : 1, �ִ� : 2
		scale = FMath::Clamp(scale, 1, 2);

		//scaleDir�� ������ �ٲ�� (* -1)
		scaleDir *= -1;
	}
	


	/*
	//���࿡ Ŀ���� ���¶��
	if (isGrow == true)
	{
		//scale �� 2�� �ɶ����� Ŀ����
		scale += speed * GetWorld()->GetDeltaSeconds();
		SetActorScale3D(FVector(scale));
		
		//���࿡ scale ���� 2���� Ŀ����
		if (scale > 2)
		{
			isGrow = false;
		}
		
		//�۾����� ���·� �ٲ��

	}
	else
	{
		scale -= speed * GetWorld()->GetDeltaSeconds();
		SetActorScale3D(FVector(scale));

		//�׷��� �ʰ� �۾����� ���¶��
		if (scale <  1)
		{
			//scale �� 1�� �ɶ����� �۾�����
			isGrow = true;
		}
	}
	*/

}

void AItemSphere::OnHit()
{
	Super::OnHit();
	//isNormal �ݴ�� �����ϰ� ����
	isNormal = !isNormal;
	
}
