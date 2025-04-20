// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Footboard.h"
#include "FootboardManager.generated.h"

UCLASS()
class ALICEPROJECT_API AFootboardManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFootboardManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf <AFootboard> tileClass;

	TArray<TArray <AFootboard*>> tiles;
	
	FTimerHandle patternTimerHandle;

	void initializetiles();
	
	// 패턴 함수
	void spawnGreenTiles();
	void spawnBlueTiles();

	int gridSize = 5;

	float patternTime = 0.0f;
	int patternType = 0;

	void dropDownGrid();
	void leftRightGrid();

	enum { DOWN = -1, UP = 1, LEFT  = -1, RIGHT = 1 };
	int dropDownDir = UP;
	int dropDownIdx = 0;
	bool dropDownInit = false;
	bool dropDownEnd = false;

	int  leftRightDir = RIGHT;
	int  leftRightIdx = 0;
	bool leftRightInit = false;
	bool leftRightEnd = false;
};
