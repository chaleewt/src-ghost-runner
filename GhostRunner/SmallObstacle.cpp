// Copyright..


#include "SmallObstacle.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Coin.h"


ASmallObstacle::ASmallObstacle()
{
	// Hard Code Components Size..
	GetMainMesh()->SetRelativeScale3D  (FVector ( 0.5,  2, 1  ));

	GetSub1Mesh ()->SetRelativeScale3D (FVector (   3,  2, 1.6));
	GetSub1Mesh ()->SetRelativeLocation(FVector ( -38,  0, 18 ));
	GetSub1Mesh ()->SetRelativeRotation(FRotator(   0, 90, 0  ));

	GetPassThroughCollision()->SetBoxExtent(FVector(32, 900, 700));
	GetHitBoxCollision()->SetBoxExtent(FVector(26, 100, 51));

	GetCoinSpawnPoint()->SetRelativeLocation(FVector(0, 0, 200));
}


void ASmallObstacle::BeginPlay()
{
	Super::BeginPlay();

	SpawnCoin();
}


// SPAWN Coin On Obstacle..
void ASmallObstacle::SpawnCoin()
{
	// Randdom Between 0 and 1
	const float RandomValue = FMath::FRandRange(0, 1);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform Location = GetCoinSpawnPoint()->GetComponentTransform();

	// 50% 
	if (UKismetMathLibrary::InRange_FloatFloat(RandomValue, 0, 0.5, true, true))
	{
		ACoin* Coin = GetWorld()->SpawnActor<ACoin>(CoinToSpawn, Location, SpawnParameters);

		// Stack Rondom...
		const float StackRandomValue = FMath::FRandRange(0, 1);

		// 20%
		if (UKismetMathLibrary::InRange_FloatFloat(StackRandomValue, 0, 0.2, true, true))
		{
			// Front
			FTransform SpawnLocationOffset1 = Location;
			FTransform SpawnLocationOffset2 = Location;

			SpawnLocationOffset1.AddToTranslation(FVector(170, 0, 0));
			SpawnLocationOffset2.AddToTranslation(FVector(320, 0, 0));

			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset1, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset2, SpawnParameters);


			// Back
			FTransform SpawnLocationOffset3 = Location;
			FTransform SpawnLocationOffset4 = Location;

			SpawnLocationOffset3.AddToTranslation(FVector(-170, 0, 0));
			SpawnLocationOffset4.AddToTranslation(FVector(-320, 0, 0));

			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset3, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset4, SpawnParameters);
		}

		// 20%
		if (UKismetMathLibrary::InRange_FloatFloat(StackRandomValue, 0.2, 0.4, true, true))
		{
			// Front
			FTransform SpawnLocationOffset1 = Location;
			FTransform SpawnLocationOffset2 = Location;
			FTransform SpawnLocationOffset3 = Location;
			FTransform SpawnLocationOffset4 = Location;
			FTransform SpawnLocationOffset5 = Location;

			SpawnLocationOffset1.AddToTranslation(FVector(170, 0,    0));
			SpawnLocationOffset2.AddToTranslation(FVector(320, 0,  -30));
			SpawnLocationOffset3.AddToTranslation(FVector(450, 0,  -60));
			SpawnLocationOffset4.AddToTranslation(FVector(580, 0,  -90));
			SpawnLocationOffset5.AddToTranslation(FVector(710, 0, -120));

			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset1, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset2, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset3, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset4, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset5, SpawnParameters);

			// Back
			FTransform SpawnLocationOffset6  = Location;
			FTransform SpawnLocationOffset7  = Location;
			FTransform SpawnLocationOffset8  = Location;
			FTransform SpawnLocationOffset9  = Location;
			FTransform SpawnLocationOffset10 = Location;

			SpawnLocationOffset6. AddToTranslation(FVector(-170, 0,    0));
			SpawnLocationOffset7. AddToTranslation(FVector(-320, 0,  -30));
			SpawnLocationOffset8. AddToTranslation(FVector(-450, 0,  -60));
			SpawnLocationOffset9. AddToTranslation(FVector(-580, 0,  -90));
			SpawnLocationOffset10.AddToTranslation(FVector(-710, 0, -120));

			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset6 , SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset7 , SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset8 , SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset9 , SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset10, SpawnParameters);
		}
	}
}