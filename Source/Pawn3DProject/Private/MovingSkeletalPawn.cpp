#include "MovingSkeletalPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AMovingSkeletalPawn::AMovingSkeletalPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->TargetOffset.Z = 150.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->AddRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
	CameraComp->bUsePawnControlRotation = false;
}

void AMovingSkeletalPawn::BeginPlay()
{
	Super::BeginPlay();

	if (CapsuleComp->IsSimulatingPhysics())
	{
		CapsuleComp->SetSimulatePhysics(false);
	}

	if (SkeletalMeshComp->IsSimulatingPhysics())
	{
		SkeletalMeshComp->SetSimulatePhysics(false);
	}
	
}

void AMovingSkeletalPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

