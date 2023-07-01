// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_Gravity_ChangerComponent.h"
#include "EclipseCharacter.h"
#include "EclipseProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTP_Gravity_ChangerComponent::ChangeGravity()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	Character->SwitchGravityDirection();
}


void UTP_Gravity_ChangerComponent::AttachGravityChanger(AEclipseCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr)
	{
		return;
	}

	// Attach the gravity changer to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Change Gravity action when using touch input
			Subsystem->AddMappingContext(ChangeGravityMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Change gravity
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_Gravity_ChangerComponent::ChangeGravity);
		}
	}
}

void UTP_Gravity_ChangerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(ChangeGravityMappingContext);
		}
	}
}



