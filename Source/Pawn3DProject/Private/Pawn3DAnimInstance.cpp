#include "Pawn3DAnimInstance.h"
#include "GameFramework/Pawn.h"

UPawn3DAnimInstance::UPawn3DAnimInstance()
{
	GroundSpeed = 0.0f;
	bIsMoving = false;
	PreviousLocation = FVector::ZeroVector;
}

void UPawn3DAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerPawn = TryGetPawnOwner();
	if (OwnerPawn)
	{
		PreviousLocation = OwnerPawn->GetActorLocation();
	}
}

void UPawn3DAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerPawn)
	{
		OwnerPawn = TryGetPawnOwner();
		return;
	}

	FVector CurrentLocation = OwnerPawn->GetActorLocation();

	FVector DeltaLocation = CurrentLocation - PreviousLocation;

	DeltaLocation.Z = 0.0f;

	double DistanceTraveled = DeltaLocation.Size();

	if (DeltaSeconds > 0.0f)
	{
		GroundSpeed = DistanceTraveled / DeltaSeconds;
	}
	else
	{
		GroundSpeed = 0.0f;
	}

	bIsMoving = GroundSpeed > 3.0f;

	PreviousLocation = CurrentLocation;
}
