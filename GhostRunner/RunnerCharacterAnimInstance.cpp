// Copyright..

#include "RunnerCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RunnerCharacter.h"


URunnerCharacterAnimInstance::URunnerCharacterAnimInstance() :

	MovementSpeed(0.00f), bIsInAir(false)
{
	//..
}


void URunnerCharacterAnimInstance::NativeInitializeAnimation()
{
	RunnerCharacter = Cast<ARunnerCharacter>(TryGetPawnOwner());
}


void URunnerCharacterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (RunnerCharacter == NULL)
	{
		RunnerCharacter = Cast<ARunnerCharacter>(TryGetPawnOwner());
	}

	if (RunnerCharacter)
	{

		FVector Speed = RunnerCharacter->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();

		bIsInAir = RunnerCharacter->GetCharacterMovement()->IsFalling();
	}
}
