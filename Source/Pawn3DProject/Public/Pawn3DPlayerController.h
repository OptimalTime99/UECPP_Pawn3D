#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Pawn3DPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PAWN3DPROJECT_API APawn3DPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APawn3DPlayerController();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputMappingContext* InputMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* LookAction;

protected:
    virtual void BeginPlay() override;
};
