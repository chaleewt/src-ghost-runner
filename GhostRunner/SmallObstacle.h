// Copyright..

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "SmallObstacle.generated.h"



UCLASS()
class GHOSTRUNNER_API ASmallObstacle : public AObstacle
{
	GENERATED_BODY()
	

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SmallObtracle | Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACoin> CoinToSpawn;

	ASmallObstacle();

	virtual void SpawnCoin() override;

	virtual void BeginPlay() override;
};
