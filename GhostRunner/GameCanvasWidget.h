// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameCanvasWidget.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTRUNNER_API UGameCanvasWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
	bool bPlayCoinImageAnimation;

};
