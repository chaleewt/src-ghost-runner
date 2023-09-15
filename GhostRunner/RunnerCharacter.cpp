// Copyright..

#include "RunnerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Obstacle.h"
#include "Coin.h"
#include "Kismet/GameplayStatics.h"
#include "RunnerGameMode.h"
#include "Blueprint/UserWidget.h"


ARunnerCharacter::ARunnerCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleSize(41, 82);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -80));

	MaskMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MaskMesh"));
	MaskMesh->SetupAttachment(GetMesh());

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraLagSpeed = 3.f;
	CameraBoom->CameraRotationLagSpeed = 3.f;

	CameraBoom->SocketOffset = FVector(0.f, 0.f, 550.f);
	CameraBoom->TargetArmLength = 500.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->AddRelativeRotation(FRotator(-35.f, 0, 0)); //.. Pitch(Y) Yaw(Z) Roll(X)
	FollowCamera->bUsePawnControlRotation = false;

	// Lanes Point..
	LaneLocations.Add(-300.f);
	LaneLocations.Add(0.f   );
	LaneLocations.Add(300.f );

	GetCharacterMovement()->GravityScale = 1.5f;
	GetCharacterMovement()->MaxWalkSpeed = 1200;
	GetCharacterMovement()->JumpZVelocity = 700;
	GetCharacterMovement()->AirControl = 0;
	GetCharacterMovement()->AirControlBoostMultiplier = 0;

}


void ARunnerCharacter::OnConstruction(const FTransform& Transform)
{
	MaskMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "FaceSocket");
}


void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Run();
}


void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveLeft" , IE_Pressed, this, &ARunnerCharacter::MoveLeft );
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ARunnerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Hop"  , IE_Pressed , this, &ARunnerCharacter::Hopping     );

	PlayerInputComponent->BindAction("Slide", IE_Pressed , this, &ARunnerCharacter::SlideKeyDown);
	PlayerInputComponent->BindAction("Slide", IE_Released, this, &ARunnerCharacter::SlideKeyUp  );


}


void ARunnerCharacter::Run()
{
	// Convert Rotation into a unit Vector Facing in it's Direction..
	FRotator Rotation{ Controller->GetControlRotation() };
	AddMovementInput(Rotation.Vector());
}


void ARunnerCharacter::MoveLeft()
{
	NewLane = FMath::Clamp(CurrentLane - 1, 0, 2);

	ChangeLane();
}


void ARunnerCharacter::MoveRight()
{
	NewLane = FMath::Clamp(CurrentLane + 1, 0, 2);

	ChangeLane();
}


void ARunnerCharacter::Hopping()
{
	ACharacter::Jump();

	// Active fast falling.. 
	FTimerHandle TimerHanlde;
	GetWorldTimerManager().SetTimer(TimerHanlde, this, &ARunnerCharacter::StopHopping, 0.2, false, 0.3);
}


void ARunnerCharacter::StopHopping()
{
	FVector Impulse = FVector(0, 0, -1000);
	GetCharacterMovement()->AddImpulse(Impulse, true);
}


void ARunnerCharacter::ChangeLaneUpdate(float Value)
{
	FVector Location = GetCapsuleComponent()->GetComponentLocation();
	Location.Y = FMath::Lerp(LaneLocations[CurrentLane], LaneLocations[NewLane], Value);

	SetActorLocation(Location);
}


void ARunnerCharacter::ChangeLaneFinished()
{
	CurrentLane = NewLane;
}


void ARunnerCharacter::SlideKeyDown()
{
	bIsSlideKeyDown = true;

	// Change the capsule size to be smaller when Slide.. 
	GetCapsuleComponent()->SetCapsuleSize(55, 55);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -50));

	// Adjust Camera Postion For not getting too Close..
	// CameraBoom->SetRelativeRotation  (FRotator( 40, 0,  0  ));
	// FollowCamera->SetRelativeLocation(FVector (500, 0, -350));

	// Lock camera position to the origin position
	CameraBoom->SetRelativeRotation  (FRotator(0, 0, 0));
	FollowCamera->SetRelativeLocation(FVector (0, 0, 0));

}

void ARunnerCharacter::SlideKeyUp()
{
	bIsSlideKeyDown = false;

	// Change the capsule size to be smaller when Slide.. 
	GetCapsuleComponent()->SetCapsuleSize(41, 82);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -80));

	// Adjust Camera Postion For not getting too Close..
	CameraBoom->SetRelativeRotation  (FRotator(0, 0, 0)); 
	FollowCamera->SetRelativeLocation(FVector (0, 0, 0));

}


void ARunnerCharacter::OnDeath()
{
	bIsRunnerDeath = true;

	//GetMesh()->bPauseAnims = true;

	GetMesh()->SetSimulatePhysics(true);
	MaskMesh ->SetSimulatePhysics(true);
	GetCharacterMovement()->DisableMovement();

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());

	FTimerHandle GameOverTimerHandle;
	GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ARunnerCharacter::GameOver, 1.f, false);
}


void ARunnerCharacter::GameOver()
{
	RunnerGameMode = Cast<ARunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (RunnerGameMode)
	{
		// Hide Game Canvas HUD & Show GameOver Canvas.. 
		RunnerGameMode->GetGameHUD    ()->SetVisibility(ESlateVisibility::Hidden);
		RunnerGameMode->GetGameOverHUD()->SetVisibility(ESlateVisibility::Visible);

		RunnerGameMode->StopBGMSound();
	}

	// Setup Input Mode And Enable Mouse Cursor..
	FInputModeUIOnly InputModeUIOnly;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(InputModeUIOnly);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), GameOverSound, GetActorLocation());

	// Save Game..
	RunnerGameMode->SaveGame(CoinAmount);
}