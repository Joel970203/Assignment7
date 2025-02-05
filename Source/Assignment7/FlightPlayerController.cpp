// Fill out your copyright notice in the Description page of Project Settings.


#include "FlightPlayerController.h"
#include "EnhancedInputSubsystems.h"


AFlightPlayerController::AFlightPlayerController()
	: InputMappingContext(nullptr),
	MoveAction(nullptr),
	YawPitchAction(nullptr),
	RollAction(nullptr)
{
}

void AFlightPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) // 로컬플레이어의 정보 가져오기
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = // EnhancedInputSystem을 관리 하는 서브시스템 획득하기
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext) // 객체가 존재한다면 
			{
				Subsystem->AddMappingContext(InputMappingContext, 0); // 활성화 우선순위는 0
			}
		}
	}
}