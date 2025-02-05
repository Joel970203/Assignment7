// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FlightPlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
UCLASS()
class ASSIGNMENT7_API AFlightPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFlightPlayerController();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input");
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input");
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input");
	UInputAction* YawPitchAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input");
	UInputAction* RollAction;


protected:
	virtual void BeginPlay() override;
};
