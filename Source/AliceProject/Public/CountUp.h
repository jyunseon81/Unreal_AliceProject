// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CountUp.generated.h"

/**
 * 
 */
UCLASS()
class ALICEPROJECT_API UCountUp : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 점수 UI 갱신 함수
	UFUNCTION(BlueprintCallable)
	void updateScoreDisplay(int32 score);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Count;
};
