// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeUI.h"
#include "Components/TextBlock.h"

void ULifeUI::NativeConstruct()
{
    Super::NativeConstruct();

    // 배열에 전부 넣어두기
    healthTexts = { Text1, Text2, Text3, Text4, Text5, Text6, Text7, Text8, Text9, Text10 };
}

void ULifeUI::updateHealthDisplay(int32 currentHealth)
{
    for (int32 i = 0; i < healthTexts.Num(); ++i)
    {
        if (healthTexts[i])
        {
            // 체력 이하 index는 숨기기
            healthTexts[i]->SetVisibility(i < currentHealth ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
        }
    }
}