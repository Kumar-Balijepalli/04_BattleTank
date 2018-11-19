// Copyright Karna Studios Ltd.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// UE_LOG(LogTemp, Warning, TEXT("%s DONKEY: %s"), *GetName(), *FString(__FUNCTION__));
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
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
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP Begin Play to run!
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	// Delegating to TankAimingComponent.
	TankAimingComponent->AimAt(HitLocation,LaunchSpeed);
	
}

