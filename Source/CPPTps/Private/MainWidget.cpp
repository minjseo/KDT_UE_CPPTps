// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ProgressBar.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/CanvasPanelSlot.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>
#include "TpsPlayer.h"
#include "EasingLibrary.h"


void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//startHP = FMath::Lerp(startHP, endHP, InDeltaTime * 10);
	//// hpText 갱신 (50 / 100)
	//FString strHp = FString::Printf(TEXT("%.0f / %.0f"), startHP, maxHP);
	//hpText->SetText(FText::FromString(strHp));

	//// hpBar 갱신
	//float percent = startHP / maxHP;
	//hpBar->SetPercent(percent);



	if(ratioHP < 1)
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
	//만약에 나타나야 하는 무기 UI가 있다면
	if (weaponType > 0)
	{
		ShowWeapon();
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
	
	//UI가 나타나야 하는 무기 종류
	weaponType = type; 
	weaponTime = 0;




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


		//EaseFunction 
		
		//WeaponRifle 총을 나타나게 하자
		//Cast<UCanvasPanelSlot>(Weaponrifle->Slot)->SetPosition(FVector2D::ZeroVector);
		
		//WeapongSniper의 위치를 0,0으로 하자 (anchor default)
		Cast<UCanvasPanelSlot>(Weaponsniper->Slot)->SetPosition(FVector2D::ZeroVector);
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
		Cast<UCanvasPanelSlot>(Weaponrifle->Slot)->SetPosition(FVector2D::ZeroVector);
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

void UMainWidget::ShowWeapon()
{	
	//시간을 증가 (HP ratio 와는 별개로 만들어줌)
	weaponTime += GetWorld()->GetDeltaSeconds();

	//움직임이 목적지 까지 다 도착햇다면 
	if(weaponTime > 1)
	{
		weaponTime = 1;

		//나타나야하는 무기 UI를 없앤다
		weaponType = 0;
	}

	float ratio = UEasingLibrary::EaseOutBounce(weaponTime);
	FVector2D pos = FMath::Lerp(FVector2D::ZeroVector, FVector2D(-300,0), ratio);

	if (weaponType == 1)
	{
		Cast<UCanvasPanelSlot>(Weaponrifle->Slot)->SetPosition(pos);
	}
	else if (weaponType == 2)
	{
		Cast<UCanvasPanelSlot>(Weaponsniper->Slot)->SetPosition(pos);
	}
}
