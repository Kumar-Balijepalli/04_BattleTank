// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	    UFUNCTION(BlueprintCallable, category = "input")
		void IntendMoveForward(float Throw);

		UFUNCTION(BlueprintCallable, category = "input")
		void IntendTurnRight(float Throw);

		UFUNCTION(BlueprintCallable, category = "Setup")
		void Initialize(UTankTrack* LeftTrackToSet, UTankTrack *RightTrackToSet);

private:
		// TODO check best protection.
		virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


public:
	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;
};
