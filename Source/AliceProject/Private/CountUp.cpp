// Fill out your copyright notice in the Description page of Project Settings.


#include "CountUp.h"
#include "Components/TextBlock.h"

void UCountUp::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCountUp::updateScoreDisplay(int32 score)
{
	if (Count)
	{
		FString scoreText = FString::Printf(TEXT("%d"), score);		
		Count->SetText(FText::FromString(scoreText));
	}
}

