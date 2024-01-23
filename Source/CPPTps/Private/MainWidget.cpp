// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ProgressBar.h>
#include "TpsPlayer.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/CanvasPanelSlot.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>


void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(ratioHP <= 1)
	{
		ratioHP += InDeltaTime * 4 ;
		if(ratioHP > 1) ratioHP = 1;

		float hp = FMath::Lerp(startHP, endHP, ratioHP);

		//hpText 갱신(50/100)
		//UTextBlock 헤더인클루드
		FString strhp = FString::Printf(TEXT("%.0f / %.0f"), hp, maxHP);
		hpText->SetText(FText::FromString(strhp));

		//hpBar갱신
		//UProgressBar 헤더인클루드
		float percent = hp / maxHP;
		hpBar->SetPercent(percent);
	}
}

void UMainWidget::InitHP(float mHP)
{
	startHP = endHP = maxHP = mHP;
}

void UMainWidget::UpdateHP(float cHP) //float mHP
{
	//바뀌기 전 HP 설정
	startHP = endHP;
	//바꺄야 하는 HP 설정
	endHP = cHP;
	//최대 UP 설정 
	//maxHP = mHP;
	ratioHP = 0;
}

void UMainWidget::UpdateWeapon(int32 type)
{
	EWeaponType e = (EWeaponType)type;
	if (e == EWeaponType::GUN)
	{
		//UImage 헤더추가
		/*
		//라이플 총 UI 잘 보이게
		UCanvasPanelSlot* panelSlot = Cast<UCanvasPanelSlot>(rifle->Slot);
		panelSlot->SetZOrder(2);

		//라이플 총 UI 잘 안보이게
		panelSlot = Cast<UCanvasPanelSlot>(sniper->Slot);
		panelSlot->SetZOrder(0);
		*/
		SetWeaponZOrder(2,0);
	}

	else if (e == EWeaponType::SNIPER)
	{
		//UImage 헤더추가
		/*
		//라이플 총 UI 잘 안보이게
		UCanvasPanelSlot* panelSlot = Cast<UCanvasPanelSlot>(rifle->Slot);
		panelSlot->SetZOrder(0);

		//라이플 총 UI 잘 보이게
		panelSlot = Cast<UCanvasPanelSlot>(sniper->Slot);
		panelSlot->SetZOrder(2);
		*/
		SetWeaponZOrder(0, 2);
	}
}

void UMainWidget::SetWeaponZOrder(int32 rifleZ, int32 sniperZ)
{
	//라이플 총 UI 바꾸는것
	UCanvasPanelSlot* panelSlot = Cast<UCanvasPanelSlot>(rifle->Slot);
	panelSlot->SetZOrder(rifleZ);

	//라이플 총 UI 바꾸는것 
	panelSlot = Cast<UCanvasPanelSlot>(sniper->Slot);
	panelSlot->SetZOrder(sniperZ);
}
