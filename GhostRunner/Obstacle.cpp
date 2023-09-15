// Copyright..


#include "Obstacle.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "RunnerCharacter.h"


AObstacle::AObstacle()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	SceneRoot->SetMobility(EComponentMobility::Movable);

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	MainMesh->SetupAttachment(SceneRoot);
	MainMesh->SetMobility(EComponentMobility::Movable);
	MainMesh->SetCollisionProfileName(TEXT("MyObstacle"));

	Sub1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sub1Mesh"));
	Sub1Mesh->SetupAttachment(SceneRoot);
	Sub1Mesh->SetMobility(EComponentMobility::Movable);
	Sub1Mesh->SetCollisionProfileName(TEXT("OverlapAll"));

	Sub2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sub2Mesh"));
	Sub2Mesh->SetupAttachment(SceneRoot);
	Sub2Mesh->SetMobility(EComponentMobility::Movable);
	Sub2Mesh->SetCollisionProfileName(TEXT("OverlapAll"));

	PassThroughCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PassCheckCollision"));
	PassThroughCollision->SetupAttachment(SceneRoot);
	PassThroughCollision->SetMobility(EComponentMobility::Movable);
	PassThroughCollision->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnPassThroughBeginOverlap); 

	HitBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxCollision"));
	HitBoxCollision->SetupAttachment(SceneRoot);
	HitBoxCollision->SetMobility(EComponentMobility::Movable);
	HitBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnHitBeginOverlap);

	CoinSpawnPoint = CreateDefaultSubobject<UBillboardComponent>(TEXT("CoinSpawnPoint"));
	CoinSpawnPoint->SetRelativeLocation(FVector(0, 0, 30));
	CoinSpawnPoint->SetupAttachment(SceneRoot);
	CoinSpawnPoint->SetMobility(EComponentMobility::Movable);
}


void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}


void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AObstacle::OnPassThroughBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ARunnerCharacter* RunnerCharacter = Cast<ARunnerCharacter>(OtherActor);
		if (RunnerCharacter && !RunnerCharacter->bIsRunnerDeath)
		{
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AObstacle::DestroyObstacle, 4.f, false);
		}
	}
}


void AObstacle::OnHitBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ARunnerCharacter* RunnerCharacter = Cast<ARunnerCharacter>(OtherActor);

		if (RunnerCharacter)
		{
			RunnerCharacter->OnDeath();
		}
	}
}


void AObstacle::DestroyObstacle()
{
	Destroy();
}


void AObstacle::SpawnCoin()
{
	// Virtual Func..
}
