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

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) // �����÷��̾��� ���� ��������
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = // EnhancedInputSystem�� ���� �ϴ� ����ý��� ȹ���ϱ�
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext) // ��ü�� �����Ѵٸ� 
			{
				Subsystem->AddMappingContext(InputMappingContext, 0); // Ȱ��ȭ �켱������ 0
			}
		}
	}
}