// Fill out your copyright notice in the Description page of Project Settings.


#include "FootboardManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFootboardManager::AFootboardManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFootboardManager::BeginPlay()
{
	Super::BeginPlay();
	initializetiles();
	UE_LOG(LogTemp, Warning, TEXT("%d"), tiles.Num());

}

// Called every frame
void AFootboardManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	enum
	{
		DROPDOWN, LEFTRIGHT,
	};
	patternTime += DeltaTime;


	if (patternTime >= 1.0f)
	{
		patternTime = 0;
		switch (patternType)
		{
		case DROPDOWN:
			dropDownGrid();
			break;
		case LEFTRIGHT:
			leftRightGrid();
			break;
		}
	}
}

void AFootboardManager::initializetiles()
{
	float tileSize = 200.0f;
	FVector origin = GetActorLocation();
	for (int row = 0; row < gridSize; row++)
	{
		tiles.Add(TArray<AFootboard*>());
		for (int col = 0; col < gridSize; col++)
		{
			FVector spawnLocation = origin + FVector(row * tileSize, col * tileSize, 0.f);
			FTransform spawnTransform(spawnLocation);
			AFootboard* tile = GetWorld()->SpawnActor<AFootboard>(tileClass, spawnTransform);
			tiles[row].Add(tile);
		}
	}
}

void AFootboardManager::spawnGreenTiles()
{
	TArray<FIntPoint> availablePositions;

	for (int x = 0; x < gridSize; ++x)
	{
		for (int y = 0; y < gridSize; ++y)
		{
			AFootboard* tile = tiles[x][y];

			// 빨간 타일은 제외
			if (tile && tile->getTileColor() == tileColor::None)
			{
				availablePositions.Add(FIntPoint(x, y));
			}
		}
	}

	if (availablePositions.Num() > 0)
	{
		int RandIndex = FMath::RandRange(0, availablePositions.Num() - 1);
		FIntPoint Pos = availablePositions[RandIndex];
		tiles[Pos.X][Pos.Y]->setTileColor(tileColor::Green);
	}

}

void AFootboardManager::spawnBlueTiles()
{
	TArray<FIntPoint> availablePositions;

	for (int x = 0; x < gridSize; ++x)
	{
		for (int y = 0; y < gridSize; ++y)
		{
			AFootboard* tile = tiles[x][y];

			// 빨강과 초록은 제외
			if (tile && tile->getTileColor() == tileColor::None)
			{
				availablePositions.Add(FIntPoint(x, y));
			}
		}
	}

	if (availablePositions.Num() > 0)
	{
		int RandIndex = FMath::RandRange(0, availablePositions.Num() - 1);
		FIntPoint Pos = availablePositions[RandIndex];
		tiles[Pos.X][Pos.Y]->setTileColor(tileColor::Blue);
	}

}

void AFootboardManager::dropDownGrid()
{
	if (!dropDownInit)
	{
		for (int i = 0; i < gridSize; i++)
		{
			tiles[0][i]->setTileColor(tileColor::Red);
		}

		dropDownInit = true;
		return;
	}
	else if (dropDownEnd)
	{
		for (int i = 0; i < tiles.Num(); i++)
		{
			tiles[dropDownIdx][i]->setTileColor(tileColor::None);
		}
		dropDownDir = UP;
		patternType = 1;
		dropDownInit = false;
		dropDownEnd = false;
		return;
	}
	for (int i = 0; i < tiles.Num(); i++)
	{
		tiles[dropDownIdx][i]->setTileColor(tileColor::None);
		tiles[dropDownIdx + dropDownDir][i]->setTileColor(tileColor::Red);
		/*UE_LOG(LogTemp, Warning, TEXT("dropDownGrid, (%d, %d)는 Red"), dropDownIdx + dropDownDir, i);
		UE_LOG(LogTemp, Warning, TEXT("dropDownGrid, (%d, %d)는 White"), dropDownIdx, i);*/

	}

	dropDownIdx = dropDownIdx + dropDownDir;
	if (dropDownIdx == gridSize - 1) dropDownDir = DOWN;
	if (dropDownIdx == 0)
	{
		dropDownEnd = true;
	}

	spawnGreenTiles();
	spawnBlueTiles();
}

void AFootboardManager::leftRightGrid()
{
	if (!leftRightInit)
	{
		for (int i = 0; i < gridSize; i++)
		{
			tiles[i][0]->setTileColor(tileColor::Red);
		}

		leftRightInit = true;
		return;
	}
	else if (leftRightEnd)
	{
		for (int i = 0; i < tiles.Num(); i++)
		{
			tiles[i][leftRightIdx]->setTileColor(tileColor::None);
		}
		leftRightDir = RIGHT;
		leftRightInit = false;
		leftRightEnd = false;
		patternType = 0;
		return;
	}
	for (int i = 0; i < tiles.Num(); i++)
	{
		tiles[i][leftRightIdx]->setTileColor(tileColor::None);
		tiles[i][leftRightIdx + leftRightDir]->setTileColor(tileColor::Red);
		/*UE_LOG(LogTemp, Warning, TEXT("dropDownGrid, (%d, %d)는 Red"), dropDownIdx + dropDownDir, i);
		UE_LOG(LogTemp, Warning, TEXT("dropDownGrid, (%d, %d)는 White"), dropDownIdx, i);*/

	}

	leftRightIdx = leftRightIdx + leftRightDir;
	if (leftRightIdx == gridSize - 1) leftRightDir = LEFT;
	if (leftRightIdx == 0)
	{
		leftRightEnd = true;
	}
	spawnGreenTiles();
	spawnBlueTiles();
}
