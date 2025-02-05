#include "MyFlightGameMode.h"
#include "FlightPlayerController.h"
#include "MyPawn.h" 

AMyFlightGameMode::AMyFlightGameMode()
{
	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AFlightPlayerController::StaticClass();
}
