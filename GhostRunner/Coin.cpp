// Copyright..


#include "Coin.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "RunnerCharacter.h"
#include "Kismet/GameplayStatics.h"

ACoin::ACoin()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
	CoinMesh->SetupAttachment(SceneRoot);
	CoinMesh->SetRelativeScale3D(FVector(1.6, 1.6, 1.6));
	CoinMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Sub1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sub1Mesh"));
	Sub1Mesh->SetupAttachment(SceneRoot);
	Sub1Mesh->SetRelativeLocation(FVector (-12,    0,   4));
	Sub1Mesh->SetRelativeRotation(FRotator(  0, -180,   0));
	Sub1Mesh->SetRelativeScale3D (FVector (1.1,  1.1, 1.1));
	Sub1Mesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Sub2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sub2Mesh"));
	Sub2Mesh->SetupAttachment(SceneRoot);
	Sub2Mesh->SetRelativeLocation(FVector ( 12,   0,   4));
	Sub2Mesh->SetRelativeRotation(FRotator(  0,   0,   0));
	Sub2Mesh->SetRelativeScale3D (FVector (1.1, 1.1, 1.1));
	Sub2Mesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	CoinRotator = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	CoinRotator->RotationRate = FRotator(0, 300, 0);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(SceneRoot);
	BoxCollision->SetBoxExtent(FVector(25, 48, 48));

	PassThroughCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PassCheckCollision"));
	PassThroughCollision->SetupAttachment(SceneRoot);
	PassThroughCollision->SetSphereRadius(1000);
	PassThroughCollision->SetMobility(EComponentMobility::Movable);
	PassThroughCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnPassThroughBeginOverlap);

}


void ACoin::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.  AddDynamic(this, &ACoin::OnOverlapEnd  );
}


void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACoin::OnPassThroughBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ARunnerCharacter* RunnerCharacter = Cast<ARunnerCharacter>(OtherActor);
		if (RunnerCharacter && !RunnerCharacter->bIsRunnerDeath)
		{
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ACoin::DestroyUnpickupCoin, 4.f, false);
		}
	}
}


void ACoin::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ARunnerCharacter* RunnerCharacter = Cast<ARunnerCharacter>(OtherActor);

		if (RunnerCharacter && !RunnerCharacter->bIsRunnerDeath)
		{
			RunnerCharacter->CoinAmount += 1;
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), OverlapSound, GetActorLocation());
			Destroy();
		}
	}
}


void ACoin::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//..
}


void ACoin::DestroyUnpickupCoin()
{
	Destroy();
}

