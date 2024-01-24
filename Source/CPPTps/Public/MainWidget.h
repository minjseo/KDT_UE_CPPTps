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

	float startHP = 0; //바뀌기전 
	float endHP = 0; //바뀐후
	float maxHP;
	//비율
	float ratioHP = 10;

	//현재 들고 있는 총의 타입
	int32 weaponType;
	
	//총 UI가 나오는 시간
	float weaponTime;


public:
	
	void InitHP(float mHP);
	void UpdateHP(float cHP);
	void UpdateWeapon(int32 type);
	void SetWeaponZOrder(int32 rifleZ, int32 sniperZ);

	void ShowWeapon();

	
};
