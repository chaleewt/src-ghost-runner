// Copyright..


#include "BridgeObstacle.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Coin.h"


ABridgeObstacle::ABridgeObstacle()
{
	/// Hard Code Components Size..
	GetMainMesh()->SetRelativeScale3D(FVector(3, 2, 1.7));

	GetSub1Mesh()->SetRelativeLocation(FVector (-150,   0, -85));
	GetSub1Mesh()->SetRelativeRotation(FRotator(   0, 180, -90));
	GetSub1Mesh()->SetRelativeScale3D (FVector ( 2.5, 1.7,   2));

	GetSub2Mesh()->SetRelativeLocation(FVector (150,   0, -85 ));
	GetSub2Mesh()->SetRelativeRotation(FRotator(  0,   0, -90 ));
	GetSub2Mesh()->SetRelativeScale3D (FVector (2.5, 1.7,   2 ));

	GetPassThroughCollision()->SetBoxExtent(FVector(32, 900, 700));
	GetHitBoxCollision()->SetBoxExtent(FVector(276, 102, 44));
	GetHitBoxCollision()->SetRelativeLocation(FVector(0, 0, -34));

	Sub_Sub1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sub-Sub1Mesh"));
	Sub_Sub1Mesh->SetupAttachment(RootComponent);
	Sub_Sub1Mesh->SetMobility(EComponentMobility::Movable);
	Sub_Sub1Mesh->SetCollisionProfileName(TEXT("OverlapAll" ));
	Sub_Sub1Mesh->SetRelativeLocation(FVector (-290,  0,  22));
	Sub_Sub1Mesh->SetRelativeRotation(FRotator(   0, 90, -57));
	Sub_Sub1Mesh->SetRelativeScale3D (FVector ( 2.6,  2, 2.5));

	Sub_Sub2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sub-Sub2Mesh"));
	Sub_Sub2Mesh->SetupAttachment(RootComponent);
	Sub_Sub2Mesh->SetMobility(EComponentMobility::Movable);
	Sub_Sub2Mesh->SetCollisionProfileName(TEXT("OverlapAll" ));
	Sub_Sub2Mesh->SetRelativeLocation(FVector (290,   0, 21 ));
	Sub_Sub2Mesh->SetRelativeRotation(FRotator(  0, -90, 122));
	Sub_Sub2Mesh->SetRelativeScale3D (FVector (2.6,   2, 2.5));

	GetCoinSpawnPoint()->SetRelativeLocation(FVector(0, 0, 170));

}


void ABridgeObstacle::BeginPlay()
{
	Super::BeginPlay();

	SpawnCoin();
}

// SPAWN Coin Over Obstacle..
void ABridgeObstacle::SpawnCoin()
{

	// Randdom Between 0 and 1
	const float RandomValue = FMath::FRandRange(0, 1);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform Location = GetCoinSpawnPoint()->GetComponentTransform();

	// 50%
	if (UKismetMathLibrary::InRange_FloatFloat(RandomValue, 0, 0.5, true, true))
	{
		ACoin* CoinItem = GetWorld()->SpawnActor<ACoin>(CoinToSpawn, Location, SpawnParameters);

		// Coin Stack..
		if (CoinItem)
		{
			// Front
			FTransform SpawnLocationOffset1 = Location;
			SpawnLocationOffset1.AddToTranslation(FVector(170, 0, 0));
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset1, SpawnParameters);


			// Back
			FTransform SpawnLocationOffset2 = Location;
			SpawnLocationOffset2.AddToTranslation(FVector(-170, 0, 0));
			GetWorld()->SpawnActor<ACoin>(CoinToSpawn, SpawnLocationOffset2, SpawnParameters);

		}
	}
}



