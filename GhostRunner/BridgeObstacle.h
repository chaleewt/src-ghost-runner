// Copyright..

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "BridgeObstacle.generated.h"



UCLASS()
class GHOSTRUNNER_API ABridgeObstacle : public AObstacle
{
	GENERATED_BODY()


private:

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly, Category = "BridgeObtracle | UClass", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Sub_Sub1Mesh;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly, Category = "BridgeObtracle | UClass", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Sub_Sub2Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BridgeObtracle | Coin"  , meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACoin> CoinToSpawn;

	ABridgeObstacle();

	virtual void SpawnCoin() override;

	virtual void BeginPlay() override;

};