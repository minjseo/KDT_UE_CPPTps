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
	//// hpText ���� (50 / 100)
	//FString strHp = FString::Printf(TEXT("%.0f / %.0f"), startHP, maxHP);
	//hpText->SetText(FText::FromString(strHp));

	//// hpBar ����
	//float percent = startHP / maxHP;
	//hpBar->SetPercent(percent);



	if(ratioHP < 1)
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
	//���࿡ ��Ÿ���� �ϴ� ���� UI�� �ִٸ�
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
	
	//UI�� ��Ÿ���� �ϴ� ���� ����
	weaponType = type; 
	weaponTime = 0;




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


		//EaseFunction 
		
		//WeaponRifle ���� ��Ÿ���� ����
		//Cast<UCanvasPanelSlot>(Weaponrifle->Slot)->SetPosition(FVector2D::ZeroVector);
		
		//WeapongSniper�� ��ġ�� 0,0���� ���� (anchor default)
		Cast<UCanvasPanelSlot>(Weaponsniper->Slot)->SetPosition(FVector2D::ZeroVector);
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
		Cast<UCanvasPanelSlot>(Weaponrifle->Slot)->SetPosition(FVector2D::ZeroVector);
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

void UMainWidget::ShowWeapon()
{	
	//�ð��� ���� (HP ratio �ʹ� ������ �������)
	weaponTime += GetWorld()->GetDeltaSeconds();

	//�������� ������ ���� �� �����޴ٸ� 
	if(weaponTime > 1)
	{
		weaponTime = 1;

		//��Ÿ�����ϴ� ���� UI�� ���ش�
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
