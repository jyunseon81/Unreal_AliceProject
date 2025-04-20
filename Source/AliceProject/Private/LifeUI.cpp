// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeUI.h"
#include "Components/TextBlock.h"

void ULifeUI::NativeConstruct()
{
    Super::NativeConstruct();

    // �迭�� ���� �־�α�
    healthTexts = { Text1, Text2, Text3, Text4, Text5, Text6, Text7, Text8, Text9, Text10 };
}

void ULifeUI::updateHealthDisplay(int32 currentHealth)
{
    for (int32 i = 0; i < healthTexts.Num(); ++i)
    {
        if (healthTexts[i])
        {
            // ü�� ���� index�� �����
            healthTexts[i]->SetVisibility(i < currentHealth ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
        }
    }
}