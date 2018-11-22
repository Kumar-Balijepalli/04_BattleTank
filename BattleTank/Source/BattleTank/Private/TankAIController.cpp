// Copyright Karna Studios Ltd.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"


// Depends on movement component via pathfinding system.
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	// We want to return the tank we are controlling.
	// The cast is needed as GetPawn returns only APawn *, and is not specific to which pawn.
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// Move Towards the Player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in centrimetres

	// Aim Towards the Player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	auto PlayerTankLocation = PlayerTank->GetActorLocation();
	
	AimingComponent->AimAt(PlayerTankLocation);
		
	// Fires projectile, but after reload time has elapsed.
	AimingComponent->Fire(); //TODO Fix firing.
	
	
}


