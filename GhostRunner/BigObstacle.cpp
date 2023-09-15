// Copyright..


#include "BigObstacle.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"


ABigObstacle::ABigObstacle()
{
	// Hard Code Components Size..
	GetMainMesh()->SetRelativeScale3D (FVector (0.5, 2, 3   ));

	GetSub1Mesh()->SetRelativeScale3D (FVector (1.5,  2, 1.5));
	GetSub1Mesh()->SetRelativeLocation(FVector (-43,  0, 30 ));
	GetSub1Mesh()->SetRelativeRotation(FRotator(  0, 90, 0  ));

	GetPassThroughCollision()->SetBoxExtent(FVector(32, 900, 700));
	GetHitBoxCollision()->SetBoxExtent(FVector(26, 100, 150));

	GetCoinSpawnPoint()->SetRelativeLocation(FVector(0, 0, 200));
}