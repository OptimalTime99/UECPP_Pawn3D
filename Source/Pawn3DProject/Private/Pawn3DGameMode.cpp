#include "Pawn3DGameMode.h"
#include "MovingSkeletalPawn.h"
#include "Pawn3DPlayerController.h"

APawn3DGameMode::APawn3DGameMode()
{
    DefaultPawnClass = AMovingSkeletalPawn::StaticClass();

    PlayerControllerClass = APawn3DPlayerController::StaticClass();
}