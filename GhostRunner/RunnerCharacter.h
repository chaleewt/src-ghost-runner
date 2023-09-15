// Copyright..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunnerCharacter.generated.h"



UCLASS()
class GHOSTRUNNER_API ARunnerCharacter : public ACharacter
{
	GENERATED_BODY()


private:

	// Default Components..
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "RunnerCharacter | UClasses", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent*  FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "RunnerCharacter | UClasses", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "RunnerCharacter | UClasses", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent*  MaskMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "RunnerCharacter | Config"  , meta = (AllowPrivateAccess = "true"))
	bool bIsSlideKeyDown = false;

	void Run         ();

	void Hopping     ();

	void MoveLeft    ();

	void MoveRight   ();

	void StopHopping ();

	void SlideKeyDown();

	void SlideKeyUp  ();

	// Sound Effect Components..
	UPROPERTY(EditAnywhere, BlueprintReadOnly    , Category = "RunnerCharacter | Config", meta = (AllowPrivateAccess = "true"))
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly    , Category = "RunnerCharacter | Config", meta = (AllowPrivateAccess = "true"))
	class USoundBase* GameOverSound;


	// Lane Switching Components..
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RunnerCharacter | Config", meta = (AllowPrivateAccess = "true"))
	TArray<float> LaneLocations;

	UFUNCTION(BlueprintCallable)
	void ChangeLaneUpdate  (float Value);

	UFUNCTION(BlueprintCallable)
	void ChangeLaneFinished(  /*....*/ );

	int32 CurrentLane = 1; int32 NewLane;

	// Game Config..
	void GameOver();

	class ARunnerGameMode* RunnerGameMode;

public:

	// Lane Switching Components..
	UFUNCTION(BlueprintImplementableEvent, Category = "RunnerCharacter")
	void ChangeLane();

	// Game Config..
	UPROPERTY(BlueprintReadOnly   , Category = "RunnerCharacter | Coin")
	int32 CoinAmount = 0;

	void OnDeath();

	UPROPERTY(BlueprintReadWrite)
	bool bIsRunnerDeath;

protected:

	ARunnerCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnConstruction(const FTransform& Transform) override;

};
