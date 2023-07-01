// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_Gravity_ChangerComponent.generated.h"

class AEclipseCharacter;
class UInputMappingContext;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSE_API UTP_Gravity_ChangerComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputMappingContext* ChangeGravityMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* FireAction;

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category = "GravityChanger")
		void AttachGravityChanger(AEclipseCharacter* TargetCharacter);

	/** Change gravity direction of FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category = "GravityChanger")
		void ChangeGravity();

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** The Character holding this weapon*/
	AEclipseCharacter* Character;
};


