
#include "../Flare.h"
#include "FlareAsteroid.h"
#include "FlareGame.h"


/*----------------------------------------------------
	Constructor
----------------------------------------------------*/

AFlareAsteroid::AFlareAsteroid(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	// Mesh data
	GetStaticMeshComponent()->bTraceComplexOnMove = true;
	GetStaticMeshComponent()->LDMaxDrawDistance = 100000; // 1km
	GetStaticMeshComponent()->SetSimulatePhysics(true);
	GetStaticMeshComponent()->SetLinearDamping(0);
	GetStaticMeshComponent()->SetAngularDamping(0);
	SetActorEnableCollision(true);

	// Settings
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}


/*----------------------------------------------------
	Gameplay
----------------------------------------------------*/

void AFlareAsteroid::Load(const FFlareAsteroidSave& Data)
{
	AFlareGame* Game = Cast<AFlareGame>(GetWorld()->GetAuthGameMode());
	if (Game)
	{
		AsteroidData = Data;
		GetStaticMeshComponent()->SetStaticMesh(Game->GetAsteroidCatalog()->Asteroids[Data.AsteroidMeshID]);
		GetStaticMeshComponent()->SetPhysicsLinearVelocity(Data.LinearVelocity);
		GetStaticMeshComponent()->SetPhysicsAngularVelocity(Data.AngularVelocity);
	}
}

FFlareAsteroidSave* AFlareAsteroid::Save()
{
	// Physical data
	AsteroidData.Location = GetActorLocation();
	AsteroidData.Rotation = GetActorRotation();
	AsteroidData.LinearVelocity = GetStaticMeshComponent()->GetPhysicsLinearVelocity();
	AsteroidData.AngularVelocity = GetStaticMeshComponent()->GetPhysicsAngularVelocity();
	
	return &AsteroidData;
}
