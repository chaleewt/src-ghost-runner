// Copyright..


#include "SoarObstacle.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Coin.h"


ASoarObstacle::ASoarObstacle()
{
	// Hard Code Components Size..
	GetMainMesh()->SetRelativeScale3D (FVector(0.5, 2, 1  ));
	GetMainMesh()->SetRelativeLocation(FVector(  0, 0, 150));

	GetSub1Mesh()->SetRelativeScale3D (FVector (  3,  2, 1.6));
	GetSub1Mesh()->SetRelativeLocation(FVector (-38,  0, 142));
	GetSub1Mesh()->SetRelativeRotation(FRotator(180, 90, 0  ));

	GetPassThroughCollision()->SetBoxExtent(FVector(32, 900, 700));

	GetHitBoxCollision()->SetRelativeLocation (FVector(0, 0, 150));
	GetHitBoxCollision()->SetBoxExtent(FVector(26, 100, 51));

	GetCoinSpawnPoint()->SetRelativeLocation(FVector(0, 0, 30));
}


void ASoarObstacle::BeginPlay()
{
	Super::BeginPlay();

	SpawnCoin();
}


// SPAWN Coin On Obstacle..
void ASoarObstacle::SpawnCoin()
{
	// Randdom Between 0 and 1
	const float RandomValue = FMath::FRandRange(0, 1);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform Location = GetCoinSpawnPoint()->GetComponentTransform();

	// 70%
	if (UKismetMathLibrary::InRange_FloatFloat(RandomValue, 0, 0.7, true, true))
	{
		ACoin* Coin = GetWorld()->SpawnActor<ACoin>(CoinToSpawn, Location, SpawnParameters);

		// Stack Rondom...
		const float StackRandomValue = FMath::FRandRange(0, 1);

		// 10%
		if (UKismetMathLibrary::InRange_FloatFloat(StackRandomValue, 0, 0.1, true, true))
		{
			// Front
			FTransform SpawnLocationOffset1 = Location;
			FTransform SpawnLocationOffset2 = Location;
			FTransform SpawnLocationOffset3 = Location;
			FTransform SpawnLocationOffset4 = Location;
			FTransform SpawnLocationOffset5 = Location;
			FTransform SpawnLocationOffset6 = Location;

			SpawnLocationOffset1.AddToTranslation(FVector(170, 0, 0));
			SpawnLocationOffset2.AddToTranslation(FVector(320, 0, 0));
			SpawnLocationOffset3.AddToTranslation(FVector(450, 0, 0));
			SpawnLocationOffset4.AddToTranslation(FVector(580, 0, 0));
			SpawnLocationOffset5.AddToTranslation(FVector(710, 0, 0));
			SpawnLocationOffset6.AddToTranslation(FVector(840, 0, 0));

			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset1, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset2, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset3, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset4, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset5, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset6, SpawnParameters);

			// Back
			FTransform SpawnLocationOffset7  = Location;
			FTransform SpawnLocationOffset8  = Location;
			FTransform SpawnLocationOffset9  = Location;
			FTransform SpawnLocationOffset10 = Location;
			FTransform SpawnLocationOffset11 = Location;

			SpawnLocationOffset7. AddToTranslation(FVector(-170, 0, 0));
			SpawnLocationOffset8. AddToTranslation(FVector(-320, 0, 0));
			SpawnLocationOffset9. AddToTranslation(FVector(-450, 0, 0));
			SpawnLocationOffset10.AddToTranslation(FVector(-580, 0, 0));
			SpawnLocationOffset11.AddToTranslation(FVector(-710, 0, 0));

			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset7 , SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset8 , SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset9 , SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset10, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset11, SpawnParameters);
		}

		// 30%
		if (UKismetMathLibrary::InRange_FloatFloat(StackRandomValue, 0.1, 0.3, true, true))
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
	}
}
