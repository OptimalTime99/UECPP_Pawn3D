#include "Pawn3DPlayerController.h"
#include "EnhancedInputSubsystems.h"

APawn3DPlayerController::APawn3DPlayerController() :
    InputMappingContext(nullptr),
    MoveAction(nullptr),
    LookAction(nullptr) {}

void APawn3DPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
                Subsystem->AddMappingContext(InputMappingContext, 0);

            }
        }
    }
}
