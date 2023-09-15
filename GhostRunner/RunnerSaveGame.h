// Copyright..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RunnerSaveGame.generated.h"




UCLASS()
class GHOSTRUNNER_API URunnerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	URunnerSaveGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RunnerSaveGame")
	int32 CollectedCoin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "RunnerSaveGame")
	FString SaveGameSlotName;
};