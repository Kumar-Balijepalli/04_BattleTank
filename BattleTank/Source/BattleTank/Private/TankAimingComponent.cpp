// Copyright Karna Studios Ltd.
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "ConstructorHelpers.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// this is required to prevent a bug from showing up where the projectile_BP keeps resetting to None
	// on every hotload of UE4.
	static ConstructorHelpers::FClassFinder<AProjectile> Proj(TEXT("/Game/Tank/Projectile_BP"));
	if (Proj.Class)
	{
		ProjectileBlueprint = Proj.Class; 
	}
	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// The function that will AimAt some tank. The tank name will need to be passed as a parameter.
void UTankAimingComponent::AimAt(FVector &HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity{ 0 };
	FVector StartLocation = Barrel->GetSocketLocation(FName("BarrelTip"));

	// Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0,
		0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);

	}
	// if no aim solution found
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch); 
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);

}
void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }
	// Check if we are ready to fire, i.e time elapsed since last fire is more than ReloadTime.
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (IsReloaded)
	{
		// spawn the projectile at the socket location on barrel.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		// reset the LastFireTime to current time
		LastFireTime = FPlatformTime::Seconds();
	}

}