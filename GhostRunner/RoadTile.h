// Copyright..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoadTile.generated.h"

UCLASS()
class GHOSTRUNNER_API ARoadTile : public AActor
{
	GENERATED_BODY()
	

private:

	// Default Components..
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Road | UClasses", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* DirectionArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Road | UClasses", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* CenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Road | UClasses", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent*   LeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Road | UClasses", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent*  RightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Road | UClasses", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* NextRoadSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Road | UClasses", meta = (AllowPrivateAccess = "true"))
	class USceneComponent*      SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Road | UClasses", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent*     BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Road | UClasses", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent*  RoadMesh;

	// To Spawn Components..
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Road | Obstacle", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABigObstacle>     BigObstacle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Road | Obstacle", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASmallObstacle>   SmallObstacle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Road | Obstacle", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASoarObstacle>    SoarObstacle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Road | Obstacle", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABridgeObstacle>  BridgeObstacle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Road | Coin"    , meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACoin> Coin;

	void SpawnItemInLane(class UBillboardComponent* Lane);

	int BigObstacleTotal = 0;  int OverlapTotal = 0;

	//..

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void DestroyRoadTile();


public:

	void SpawnItems();

	FORCEINLINE class UBillboardComponent* GetNextRoadSpawnPoint() { return NextRoadSpawnPoint; }


protected:

	ARoadTile();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
