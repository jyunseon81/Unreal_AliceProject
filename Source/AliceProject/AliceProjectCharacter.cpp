// Copyright Epic Games, Inc. All Rights Reserved.

#include "AliceProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Footboard.h"
#include "FootboardManager.h"
#include "LifeUI.h"
#include "CountUp.h"

AAliceProjectCharacter::AAliceProjectCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AAliceProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAliceProjectCharacter::OnCapsuleBeginOverlap);
	if (lifeUIClass)
	{
		lifeUI = CreateWidget<ULifeUI>(GetWorld(), lifeUIClass);
		if (lifeUI)
		{
			lifeUI->AddToViewport();
			lifeUI->SetVisibility(ESlateVisibility::Visible);
			lifeUI->updateHealthDisplay(currentHealth);

			UE_LOG(LogTemp, Warning, TEXT("LifeUI Init"));
		}
	}

	if (countUpClass)
	{
		countUpUI = CreateWidget<UCountUp>(GetWorld(), countUpClass);
		if (countUpUI)
		{
			countUpUI->AddToViewport();
			countUpUI->updateScoreDisplay(score); 
		}
	}
}

void AAliceProjectCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

// »¡°£»ö Å¸ÀÏÀÌ¶û ¿À¹ö·¦ µÆÀ» ¶§ ÇÏÆ® -1
void AAliceProjectCharacter::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	AFootboard* tile = Cast<AFootboard>(OtherActor);
	if (tile && tile->getTileColor() == tileColor::Red)
	{
		if (currentHealth > 0)
		{
			currentHealth -= 1;
			UE_LOG(LogTemp, Warning, TEXT("Health: %d"), currentHealth);

			if (lifeUI)
			{
				lifeUI->updateHealthDisplay(currentHealth);
			}
		}
	}

	if (tile && tile->getTileColor() == tileColor::Blue)
	{
		score++;

		UE_LOG(LogTemp, Warning, TEXT(" Score: %d"), score);

		if (countUpUI)
		{
			countUpUI->updateScoreDisplay(score);
		}
	}
}
