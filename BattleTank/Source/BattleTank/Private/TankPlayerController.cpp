// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Public/CollisionQueryParams.h"
#include "Math/Vector2D.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	// Always call this before anything else, so that the parent class's BeginPlay is called.
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }// ensure logs out the line number and the error too.
		
	FoundAimingComponent(AimingComponent);
		
}

void ATankPlayerController::Tick(float DeltaTime)
{
	// Always do the super/parent classes function first.
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}


void ATankPlayerController::AimTowardsCrossHair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FVector HitLocation{ 0 }; // out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
		
			// Tell the control tank to aim at this point.
	}
}

// Get World Location if Line trace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{

	// Find the cross hair position
	int32 ViewPortSizeX, ViewPortSizeY;

	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	FVector2D ScreenLocation(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY*CrossHairYLocation);
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// LineTrace along that look direction, and see what we hit (up to a max range).
		// GetLookVectorHitLocation();
		GetLookVectorHitLocation(LookDirection, HitLocation);
		
	}	
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	// "De-Project" the screen position of the crosshair to a world direction
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}