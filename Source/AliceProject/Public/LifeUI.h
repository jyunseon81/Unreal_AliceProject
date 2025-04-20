// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LifeUI.generated.h"

/**
 * 
 */
UCLASS()
class ALICEPROJECT_API ULifeUI : public UUserWidget
{
	GENERATED_BODY()
	// 체력 UI 갱신


public:
    UFUNCTION(BlueprintCallable)
    void updateHealthDisplay(int32 currentHealth);

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Text1;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text2;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text3;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text4;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text5;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text6;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text7;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text8;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text9;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text10;

private:
    TArray<UTextBlock*> healthTexts;
};
