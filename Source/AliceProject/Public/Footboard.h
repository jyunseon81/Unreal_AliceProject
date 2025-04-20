// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Footboard.generated.h"

UENUM(BlueprintType)
enum class tileColor : uint8
{
	None,
	Red,
	Green,
	Blue

};

UCLASS()
class ALICEPROJECT_API AFootboard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFootboard();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mesh; 

	void setTileColor(tileColor newColor);
	tileColor getTileColor() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	tileColor currentColor;
	void updateMaterial();
};
