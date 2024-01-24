// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPPTPS_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* hpBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* hpText;

	UPROPERTY(meta = (BindWidget))
	class UImage* rifle;

	UPROPERTY(meta = (BindWidget))
	class UImage* sniper;

	UPROPERTY(meta = (BindWidget))
	class UImage* Weaponrifle;

	UPROPERTY(meta = (BindWidget))
	class UImage* Weaponsniper;

	float startHP = 0; //�ٲ���� 
	float endHP = 0; //�ٲ���
	float maxHP;
	//����
	float ratioHP = 10;

	//���� ��� �ִ� ���� Ÿ��
	int32 weaponType;
	
	//�� UI�� ������ �ð�
	float weaponTime;


public:
	
	void InitHP(float mHP);
	void UpdateHP(float cHP);
	void UpdateWeapon(int32 type);
	void SetWeaponZOrder(int32 rifleZ, int32 sniperZ);

	void ShowWeapon();

	
};
