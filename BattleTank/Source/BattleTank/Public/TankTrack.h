// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	// Sets a throttle between -1 and +1.
	UFUNCTION(BlueprintCallable, category = Input)
	void SetThrottle(float Throttle);

	// Max force per track, in Newtons.
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.0f; // Assume 40 tonne tank and 1g acceleration (10 m/s^2).
	
	void ApplySidewaysForce();
	   
	UTankTrack(); //declaration for constructor ! Don't delete.
	
private:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor * OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();

	float CurrentThrottle = 0;
};
