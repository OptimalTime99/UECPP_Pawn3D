#include "MovingSkeletalPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Pawn3DPlayerController.h"
#include "EnhancedInputComponent.h"

AMovingSkeletalPawn::AMovingSkeletalPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);
	CapsuleComp->SetSimulatePhysics(false);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);
	SkeletalMeshComp->SetSimulatePhysics(false);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->TargetOffset.Z = 150.0f;
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->AddRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
	CameraComp->bUsePawnControlRotation = false;
}

void AMovingSkeletalPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APawn3DPlayerController* PlayerController = Cast<APawn3DPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInputComponent->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AMovingSkeletalPawn::Move
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInputComponent->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AMovingSkeletalPawn::Look
				);
			}
		}
	}
}

void AMovingSkeletalPawn::Move(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector2D MoveInput = Value.Get<FVector2D>();

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	if (!MoveInput.IsNearlyZero())
	{
		FVector DeltaLocation = FVector(MoveInput.X, MoveInput.Y, 0.0f);

		DeltaLocation = DeltaLocation * MoveSpeed * DeltaTime;

		AddActorLocalOffset(DeltaLocation, true);
	}
}

void AMovingSkeletalPawn::Look(const FInputActionValue& Value)
{
	const FVector2D LookInput = Value.Get<FVector2D>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	if (!LookInput.IsNearlyZero())
	{
		if (LookInput.X != 0.0f)
		{
			FRotator YawRotation = FRotator(0.0f, LookInput.X * RotationSpeed * DeltaTime, 0.0f);
			AddActorLocalRotation(YawRotation);
		}

		if (LookInput.Y != 0.0f)
		{
			FRotator CurrentSpringArmRot = SpringArmComp->GetRelativeRotation();

			float NewPitch = CurrentSpringArmRot.Pitch - (LookInput.Y * RotationSpeed * DeltaTime);

			FRotator NewRotation = FRotator(NewPitch, 0.0f, 0.0f);

			SpringArmComp->SetRelativeRotation(NewRotation);
		}
	}
}

