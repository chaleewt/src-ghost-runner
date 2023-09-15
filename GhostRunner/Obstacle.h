// Copyright..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class GHOSTRUNNER_API AObstacle : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obtracle | UClass", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* CoinSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obtracle | UClass", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MainMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obtracle | UClass", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Sub1Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obtracle | UClass", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Sub2Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obtracle | UClass", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obtracle | UClass", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* HitBoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obtracle | UClass", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* PassThroughCollision;

public:

	FORCEINLINE class UStaticMeshComponent* GetMainMesh() { return MainMesh; }
	FORCEINLINE class UStaticMeshComponent* GetSub1Mesh() { return Sub1Mesh; }
	FORCEINLINE class UStaticMeshComponent* GetSub2Mesh() { return Sub2Mesh; }

	FORCEINLINE class UBillboardComponent*  GetCoinSpawnPoint() { return CoinSpawnPoint;       }
	FORCEINLINE class UBoxComponent*  GetPassThroughCollision() { return PassThroughCollision; }
	FORCEINLINE class UBoxComponent*       GetHitBoxCollision() { return HitBoxCollision;      }


protected:
	
	AObstacle();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SpawnCoin();

	void DestroyObstacle();

	UFUNCTION()
	virtual void OnPassThroughBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnHitBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
