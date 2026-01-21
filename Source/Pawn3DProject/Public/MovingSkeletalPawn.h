#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovingSkeletalPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PAWN3DPROJECT_API AMovingSkeletalPawn : public APawn
{
	GENERATED_BODY()

public:
	AMovingSkeletalPawn();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCameraComponent* CameraComp;


protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
