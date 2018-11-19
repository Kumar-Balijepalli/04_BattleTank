// Copyright Karna Studios Ltd.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the Barrel the right amount this frame
	// Given a max elevation speed, and the frame time.
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f); // To prevent the barrel from moving too fast.
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	// We want to prevent the RawNewElevation from going higher/lower than the max and min elevation
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));

}


