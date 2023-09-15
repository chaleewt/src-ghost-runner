// Copyright notice..


#include "RunnerGameMode.h"
#include "RoadTile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BillboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "RunnerSaveGame.h"

ARunnerGameMode::ARunnerGameMode()
{
	//..
}


void ARunnerGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitialRoadTileSpawn();

	InitializeHUD();

	PlayBGMSound();

	LoadSaveGame();

}


void ARunnerGameMode::InitialRoadTileSpawn()
{

	// Begin to SPAWN 3 RoadTiles..
	for (int x = 0; x < RoadInitialAmount; x++)
	{
		if (x < 3)
		{
			SpawnRoadTile(false);
		}
		else
		{
			SpawnRoadTile(true );
		}
	}
}


void ARunnerGameMode::SpawnRoadTile(const bool bSpawnItem)
{
	// SPAWN Location (0, 0, 0) in WORLD SPACE..
	ARoadTile* RoadTile = GetWorld()->SpawnActor<ARoadTile>(RoadTileToSpawn, RoadTileSpawnLocation);

	if (RoadTile)
	{
		if (bSpawnItem)
		{
			RoadTile->SpawnItems();
		}

		// Next Spawn Point..
		RoadTileSpawnLocation = RoadTile->GetNextRoadSpawnPoint()->GetComponentTransform();
	}
}


void ARunnerGameMode::InitializeHUD()
{
	if (GameCanvas)
	{
		GameHUD     = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), GameCanvas);
		GameOverHUD = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), GameOverCanvas);

		if (GameHUD && GameOverHUD)
		{
			GameHUD->AddToViewport();
			GameHUD->SetVisibility(ESlateVisibility::Visible);

			GameOverHUD->AddToViewport();
			GameOverHUD->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}


void ARunnerGameMode::PlayBGMSound()
{
	BGMAudio = UGameplayStatics::SpawnSound2D(GetWorld(), BGMSound);
}

void ARunnerGameMode::StopBGMSound()
{
	BGMAudio->SetActive(false);
}


void ARunnerGameMode::SaveGame(int32 CoinAmount)
{
	RunnerSaveGame = Cast<URunnerSaveGame>(UGameplayStatics::CreateSaveGameObject(URunnerSaveGame::StaticClass()));

	if (RunnerSaveGame)
	{
		RunnerSaveGame->CollectedCoin = CoinAmount;

		UGameplayStatics::SaveGameToSlot(RunnerSaveGame, RunnerSaveGame->SaveGameSlotName, 0);
	}
}


void ARunnerGameMode::LoadSaveGame()
{
	URunnerSaveGame* RunnerLoadSaveGame = Cast<URunnerSaveGame>(UGameplayStatics::CreateSaveGameObject(URunnerSaveGame::StaticClass()));
	RunnerSaveGame = Cast<URunnerSaveGame>(UGameplayStatics::LoadGameFromSlot(RunnerLoadSaveGame->SaveGameSlotName, 0));

	if (RunnerSaveGame)
	{
		PlayerCoin = RunnerSaveGame->CollectedCoin;
	}
}

