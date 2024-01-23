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

		//hpText ����(50/100)
		//UTextBlock �����Ŭ���
		FString strhp = FString::Printf(TEXT("%.0f / %.0f"), hp, maxHP);
		hpText->SetText(FText::FromString(strhp));

		//hpBar����
		//UProgressBar �����Ŭ���
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
	//�ٲ�� �� HP ����
	startHP = endHP;
	//�ٲ��� �ϴ� HP ����
	endHP = cHP;
	//�ִ� UP ���� 
	//maxHP = mHP;
	ratioHP = 0;
}

void UMainWidget::UpdateWeapon(int32 type)
{
	EWeaponType e = (EWeaponType)type;
	if (e == EWeaponType::GUN)
	{
		//UImage ����߰�
		/*
		//������ �� UI �� ���̰�
		UCanvasPanelSlot* panelSlot = Cast<UCanvasPanelSlot>(rifle->Slot);
		panelSlot->SetZOrder(2);

		//������ �� UI �� �Ⱥ��̰�
		panelSlot = Cast<UCanvasPanelSlot>(sniper->Slot);
		panelSlot->SetZOrder(0);
		*/
		SetWeaponZOrder(2,0);
	}

	else if (e == EWeaponType::SNIPER)
	{
		//UImage ����߰�
		/*
		//������ �� UI �� �Ⱥ��̰�
		UCanvasPanelSlot* panelSlot = Cast<UCanvasPanelSlot>(rifle->Slot);
		panelSlot->SetZOrder(0);

		//������ �� UI �� ���̰�
		panelSlot = Cast<UCanvasPanelSlot>(sniper->Slot);
		panelSlot->SetZOrder(2);
		*/
		SetWeaponZOrder(0, 2);
	}
}

void UMainWidget::SetWeaponZOrder(int32 rifleZ, int32 sniperZ)
{
	//������ �� UI �ٲٴ°�
	UCanvasPanelSlot* panelSlot = Cast<UCanvasPanelSlot>(rifle->Slot);
	panelSlot->SetZOrder(rifleZ);

	//������ �� UI �ٲٴ°� 
	panelSlot = Cast<UCanvasPanelSlot>(sniper->Slot);
	panelSlot->SetZOrder(sniperZ);
}
