#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Pawn3DAnimInstance.generated.h"

UCLASS()
class PAWN3DPROJECT_API UPawn3DAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPawn3DAnimInstance();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeInitializeAnimation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	bool bIsMoving;

	UPROPERTY()
	class APawn* OwnerPawn;

	FVector PreviousLocation;
};
