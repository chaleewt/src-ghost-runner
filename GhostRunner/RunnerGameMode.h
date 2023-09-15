// Copyright notice..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunnerGameMode.generated.h"


UCLASS()
class GHOSTRUNNER_API ARunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()


private:

	UPROPERTY(EditDefaultsOnly, Category = "RunnerGameMode | Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ARoadTile> RoadTileToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "RunnerGameMode | Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> GameCanvas;

	UPROPERTY(EditDefaultsOnly, Category = "RunnerGameMode | Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> GameOverCanvas;

	class UUserWidget* GameHUD;
	class UUserWidget* GameOverHUD;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int RoadInitialAmount = 5;

	FTransform RoadTileSpawnLocation;

	void InitialRoadTileSpawn();

	void InitializeHUD();

	// SOUND EFFECT..
	UPROPERTY(EditDefaultsOnly, Category = "RunnerGameMode | Config", meta = (AllowPrivateAccess = "true"))
	class USoundBase*      BGMSound;
	class UAudioComponent* BGMAudio;

	// SAVE & LOAD..
	class URunnerSaveGame* RunnerSaveGame;

public:

	// SAVE & LOAD..
	UPROPERTY(BlueprintReadOnly, Category = "RunnerGameMode")
	int32 PlayerCoin = 0;

	UFUNCTION(BlueprintCallable, Category = "RunnerGameMode")
	void SaveGame(int32 CoinAmount);

	UFUNCTION(BlueprintCallable, Category = "RunnerGameMode")
	void LoadSaveGame();

	void SpawnRoadTile(const bool bSpawnItem);

	void PlayBGMSound();

	void StopBGMSound();

	FORCEINLINE class UUserWidget* GetGameHUD() { return GameHUD; }
	FORCEINLINE class UUserWidget* GetGameOverHUD() { return GameOverHUD; }


protected:

	ARunnerGameMode();

	virtual void BeginPlay() override;

};
