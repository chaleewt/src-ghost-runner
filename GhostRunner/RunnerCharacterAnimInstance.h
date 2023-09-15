/// Copyright..
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RunnerCharacterAnimInstance.generated.h"



UCLASS()
class GHOSTRUNNER_API URunnerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


private:

	URunnerCharacterAnimInstance();

	// Similar to Beginplay, Called once per frame ////////////////////////
	UFUNCTION(BlueprintCallable, Category = "URunnerCharacterAnimInstance")
	virtual void NativeInitializeAnimation() override;

	// Update animation every frame ///////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "URunnerCharacterAnimInstance")
	void UpdateAnimationProperties(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "URunnerCharacterAnimInstance", meta = (AllowPrivateAccess = "true"))
	class ARunnerCharacter* RunnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "URunnerCharacterAnimInstance", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "URunnerCharacterAnimInstance", meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

};
