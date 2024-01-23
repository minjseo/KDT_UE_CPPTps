// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ProgressBar.h>

void UMainWidget::UpdateHP(float currHP, float maxHP)
{
	//hpText ����(50/100)
	FString hp = FString::Printf(TEXT("%.0f / %.0f"), currHP, maxHP);
	//UTextBlock �����Ŭ���
	hpText->SetText(FText::FromString(hp));

	//hpBar����
	float percent = currHP / maxHP;
	//UProgressBar �����Ŭ���
	hpBar->SetPercent(percent);

}
