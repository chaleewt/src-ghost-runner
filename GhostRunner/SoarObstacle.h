// Copyright..

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "SoarObstacle.generated.h"



UCLASS()
class GHOSTRUNNER_API ASoarObstacle : public AObstacle
{
	GENERATED_BODY()


private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SoarObtracle | Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACoin> CoinToSpawn;

	ASoarObstacle();

	virtual void SpawnCoin() override;

	virtual void BeginPlay() override;
	
};
