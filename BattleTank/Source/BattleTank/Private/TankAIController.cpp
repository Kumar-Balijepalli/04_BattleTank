// Copyright Karna Studios Ltd.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

// Depends on movement component via pathfinding system.
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// We want to return the tank we are controlling.
	// The cast is needed as GetPawn returns only APawn *, and is not specific to which pawn.
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (ensure(PlayerTank))
	{
		// Move Towards the Player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in centrimetres
		// Aim Towards the Player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		// Fires projectile, but after reload time has elapsed.
		ControlledTank->Fire();
	}
	
}


