// Fill out your copyright notice in the Description page of Project Settings.


#include "Footboard.h"

// Sets default values
AFootboard::AFootboard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = mesh;
	currentColor = tileColor::None;
}


// Called when the game starts or when spawned
void AFootboard::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("AFootboard::BeginPlay"));
	updateMaterial();
}

// Called every frame
void AFootboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFootboard::setTileColor(tileColor newColor)
{
	/*if (currentColor == tileColor::Red && currentColor != newColor)
		return;*/

	currentColor = newColor;
	updateMaterial();
	
}

tileColor AFootboard::getTileColor() const
{
	return currentColor;
}


void AFootboard::updateMaterial()
{
	auto dynamicMaterial = mesh->CreateAndSetMaterialInstanceDynamic(0);
	if (!dynamicMaterial) return;
	///UE_LOG(LogTemp, Warning, TEXT("updateMaterial, currentColor: %d"), currentColor);

	switch (currentColor)
	{
	case tileColor::Red:
		dynamicMaterial->SetVectorParameterValue("color", FLinearColor::Red);
		break;

	case tileColor::Green:
		dynamicMaterial->SetVectorParameterValue("color", FLinearColor::Green);
		break;

	case tileColor::Blue:
		dynamicMaterial->SetVectorParameterValue("color", FLinearColor::Blue);
		break;

	default:
		//UE_LOG(LogTemp, Warning, TEXT("updateMaterial, white"));
		dynamicMaterial->SetVectorParameterValue("color", FLinearColor::White);
		break;
	}
}

