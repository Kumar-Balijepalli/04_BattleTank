// Copyright Karna Studios Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class ATank;
class UTankAimingComponent; // Forward declaration to prevent code duplication and shorten compile times
class UTankTurret;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent *TankAimingComponent = nullptr;

public:	

	void AimAt(FVector HitLocation);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// This is to prevent the tanks from firing every frame.
	// Making this EditDefaultsOnly to make all tanks have the same value.
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.0f;

	// EditDefaultsOnly because, all tanks must have the same value
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.0f; 

	// Local barrel reference for spawning projectile.
	UTankBarrel *Barrel = nullptr; // TODO Remove

	double LastFireTime = 0.0;

};
