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

	float startHP = 0; //πŸ≤Ó±‚¿¸ 
	float endHP = 0; //πŸ≤Ô»ƒ
	float maxHP;
	//∫Ò¿≤
	float ratioHP = 10;


public:
	
	void InitHP(float mHP);
	void UpdateHP(float cHP);
	void UpdateWeapon(int32 type);
	void SetWeaponZOrder(int32 rifleZ, int32 sniperZ);

	
};
