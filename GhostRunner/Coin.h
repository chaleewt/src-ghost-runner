// Copyright..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class GHOSTRUNNER_API ACoin : public AActor
{
	GENERATED_BODY()
	

private:

	// Default Components..
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin | UClass", meta = (AllowPrivateAccess = "true"))
	class USceneComponent*     SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin | UClass", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CoinMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin | UClass", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Sub1Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin | UClass", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Sub2Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin | UClass", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin | UClass", meta = (AllowPrivateAccess = "true"))
	class URotatingMovementComponent* CoinRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin | UClass", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* PassThroughCollision;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Coin | Sounds", meta = (AllowPrivateAccess = "true"))
	class USoundBase* OverlapSound;

	//..

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
    void OnPassThroughBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//..
	void DestroyUnpickupCoin();


protected:
	
	ACoin();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
