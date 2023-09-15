// Copyright..


#include "RoadTile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "RunnerCharacter.h"
#include "RunnerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Obstacle.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BillboardComponent.h"
#include "Coin.h"
#include "BigObstacle.h"
#include "BridgeObstacle.h"
#include "SmallObstacle.h"
#include "SoarObstacle.h"



ARoadTile::ARoadTile()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	// Default Properties..
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	SceneRoot->SetMobility(EComponentMobility::Movable);

	RoadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoadMesh"));
	RoadMesh->SetupAttachment(SceneRoot);
	RoadMesh->SetRelativeScale3D(FVector(1.7, 1, 3.5f));
	RoadMesh->SetMobility(EComponentMobility::Movable);

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	DirectionArrow->SetupAttachment(SceneRoot);
	DirectionArrow->SetRelativeLocation(FVector(170, 0, 2.4));
	DirectionArrow->SetRelativeScale3D (FVector(1, 4.5, 0.1));

	CenterLane = CreateDefaultSubobject<UBillboardComponent>(TEXT("CenterLane"));
	CenterLane->SetRelativeLocation(FVector(0, 0, 30));
	CenterLane->SetupAttachment(SceneRoot);
	CenterLane->SetMobility(EComponentMobility::Movable);

	LeftLane = CreateDefaultSubobject<UBillboardComponent>(TEXT("LeftLane"));
	LeftLane->SetRelativeLocation(FVector(0, -300, 30));
	LeftLane->SetupAttachment(SceneRoot);
	LeftLane->SetMobility(EComponentMobility::Movable);

	RightLane = CreateDefaultSubobject<UBillboardComponent>(TEXT("RightLane"));
	RightLane->SetRelativeLocation(FVector(0, 300, 30));
	RightLane->SetupAttachment(SceneRoot);
	RightLane->SetMobility(EComponentMobility::Movable);

	NextRoadSpawnPoint = CreateDefaultSubobject<UBillboardComponent>(TEXT("NextRoadSpawnPoint"));
	NextRoadSpawnPoint->SetRelativeLocation(FVector(1700, 0, 0));
	NextRoadSpawnPoint->SetupAttachment(SceneRoot);
	NextRoadSpawnPoint->SetMobility(EComponentMobility::Movable);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetRelativeLocation(FVector(500, 0, 200));
	BoxCollision->SetBoxExtent(FVector(32, 600, 500));
	BoxCollision->SetupAttachment(SceneRoot);
	BoxCollision->SetMobility(EComponentMobility::Movable);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ARoadTile::OnOverlapBegin);

}


void ARoadTile::BeginPlay()
{
	Super::BeginPlay();
	
}


void ARoadTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARoadTile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ARunnerCharacter* RunnerCharacter = Cast<ARunnerCharacter>(OtherActor);

		if (RunnerCharacter)
		{
			ARunnerGameMode* RunnerGameMode = Cast<ARunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

			// SPAWN Road After Running Passed 2 Times..
			OverlapTotal += 1;

			if (RunnerGameMode && OverlapTotal == 2)
			{
				RunnerGameMode->SpawnRoadTile(true);

				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(TimerHandle, this, &ARoadTile::DestroyRoadTile, 3.f, false);

				OverlapTotal = 0;
			}
		}
	}
}


void ARoadTile::SpawnItems()
{
	SpawnItemInLane(CenterLane);
	SpawnItemInLane(LeftLane  );
	SpawnItemInLane(RightLane );
}


void ARoadTile::SpawnItemInLane(class UBillboardComponent* Lane)
{
	// Randdom between 0 and 1
	const float RandomValue = FMath::FRandRange(0, 1);

	// Force Actor To SPAWN, even if some Issue Occured...
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// SPAWN Location..
	const FTransform& SpawnLocation = Lane->GetComponentTransform();


	//////////////////////////////////////////////////////////////////////////////////////////////////

	// 5%
	if (UKismetMathLibrary::InRange_FloatFloat(RandomValue, 0, 0.05, true, true))
	{
		// Adjust Z-Position..
		FTransform SpawnLocationOffset = SpawnLocation;
		SpawnLocationOffset.AddToTranslation(FVector(0, 0, 70));

		ACoin* _Coin = GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset, SpawnParameters);

		// Stack Rondom..
		const float StackRandomValue = FMath::FRandRange(0, 1);

		// Full Stack.. 5%
		if (UKismetMathLibrary::InRange_FloatFloat(RandomValue, 0, 0.05, true, true))
		{
			// Front
			FTransform SpawnLocationOffset1 = SpawnLocation;
			FTransform SpawnLocationOffset2 = SpawnLocation;
			FTransform SpawnLocationOffset3 = SpawnLocation;
			FTransform SpawnLocationOffset4 = SpawnLocation;
			FTransform SpawnLocationOffset5 = SpawnLocation;
			FTransform SpawnLocationOffset6 = SpawnLocation;

			SpawnLocationOffset1.AddToTranslation(FVector(170, 0, 70));
			SpawnLocationOffset2.AddToTranslation(FVector(320, 0, 70));
			SpawnLocationOffset3.AddToTranslation(FVector(450, 0, 70));
			SpawnLocationOffset4.AddToTranslation(FVector(580, 0, 70));
			SpawnLocationOffset5.AddToTranslation(FVector(710, 0, 70));
			SpawnLocationOffset6.AddToTranslation(FVector(840, 0, 70));

			GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset1, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset2, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset3, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset4, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset5, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset6, SpawnParameters);

			// Back
			FTransform SpawnLocationOffset7 = SpawnLocation;
			FTransform SpawnLocationOffset8 = SpawnLocation;
			FTransform SpawnLocationOffset9 = SpawnLocation;
			FTransform SpawnLocationOffset10 = SpawnLocation;
			FTransform SpawnLocationOffset11 = SpawnLocation;


			SpawnLocationOffset7.AddToTranslation (FVector(-170, 0, 70));
			SpawnLocationOffset8.AddToTranslation (FVector(-320, 0, 70));
			SpawnLocationOffset9.AddToTranslation (FVector(-450, 0, 70));
			SpawnLocationOffset10.AddToTranslation(FVector(-580, 0, 70));
			SpawnLocationOffset11.AddToTranslation(FVector(-710, 0, 70));

			GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset7 , SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset8 , SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset9 , SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset10, SpawnParameters);
			GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset11, SpawnParameters);
		}

		// Half Stack.. 10%
		if (UKismetMathLibrary::InRange_FloatFloat(RandomValue, 0.05, 0.15, true, true))
		{
			// Stack Rondom...
			const float RandV = FMath::FRandRange(0, 1);

			// 5%
			if (UKismetMathLibrary::InRange_FloatFloat(RandV, 0, 0.05, true, true))
			{
				// Front
				FTransform SpawnLocationOffset1 = SpawnLocation;
				SpawnLocationOffset1.AddToTranslation(FVector(170, 0, 70));
				GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset1, SpawnParameters);

				FTransform SpawnLocationOffset2 = SpawnLocation;
				SpawnLocationOffset2.AddToTranslation(FVector(320, 0, 70));
				GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset2, SpawnParameters);

			}

			// 5%
			if (UKismetMathLibrary::InRange_FloatFloat(RandV, 0.05, 0.15, true, true))
			{
				// Front
				FTransform SpawnLocationOffset1 = SpawnLocation;
				SpawnLocationOffset1.AddToTranslation(FVector(170, 0, 70));
				GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset1, SpawnParameters);

				// Back
				FTransform SpawnLocationOffset7 = SpawnLocation;
				SpawnLocationOffset7.AddToTranslation(FVector(-170, 0, 70));
				GetWorld()->SpawnActor<ACoin>(Coin, SpawnLocationOffset7, SpawnParameters);

			}
		}

	}

	// 25%
	if (UKismetMathLibrary::InRange_FloatFloat(RandomValue, 0.05, 0.30, true, true))
	{
		FTransform SpawnLocationOffset = SpawnLocation;
		SpawnLocationOffset.AddToTranslation(FVector(0, 0, 5));

		ASoarObstacle* _SoarObstacle = GetWorld()->SpawnActor<ASoarObstacle>(SoarObstacle, SpawnLocationOffset, SpawnParameters);
	}
	
	// 25%
	if (UKismetMathLibrary::InRange_FloatFloat(RandomValue, 0.30, 0.55, true, true))
	{
		FTransform SpawnLocationOffset = SpawnLocation;
		SpawnLocationOffset.AddToTranslation(FVector(0, 0, 20));

		ASmallObstacle* _SmallObstacle = GetWorld()->SpawnActor<ASmallObstacle>(SmallObstacle, SpawnLocationOffset, SpawnParameters);
	}
	
	// 25%
	if (UKismetMathLibrary::InRange_FloatFloat(RandomValue, 0.55, 0.80, true, true))
	{
		// BIG THREE OBSTACLE CHECK: Preventing 3 Giant Obsatacles from blocking running path.. 
		BigObstacleTotal++;

		if (BigObstacleTotal < 3)
		{
			FTransform SpawnLocationOffset = SpawnLocation;
			SpawnLocationOffset.AddToTranslation(FVector(0, 0, 120));

			ABigObstacle* _BigObstacle = GetWorld()->SpawnActor<ABigObstacle>(BigObstacle, SpawnLocationOffset, SpawnParameters);
		}

		// Reset value..
		if (BigObstacleTotal >= 3)
		{
			BigObstacleTotal = 0;
		}

	}
	
	// 20%
	if (UKismetMathLibrary::InRange_FloatFloat(RandomValue, 0.80, 1, true, true))
	{
		FTransform SpawnLocationOffset = SpawnLocation;
		SpawnLocationOffset.AddToTranslation(FVector(0, 0, 54));

		ABridgeObstacle* _BridgeObstacle = GetWorld()->SpawnActor<ABridgeObstacle>(BridgeObstacle, SpawnLocationOffset, SpawnParameters);
	}
}


void ARoadTile::DestroyRoadTile()
{
	Destroy();
}