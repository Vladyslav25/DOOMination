// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"

// Sets default values
ABasePlayer::ABasePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = false;

	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
		MovementArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("MovementArrow"));
		PlayerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerCollider"));
			RootArmCenter = CreateDefaultSubobject<USceneComponent>(TEXT("RootArmCenter"));
				RootArm = CreateDefaultSubobject<USceneComponent>(TEXT("RootArm"));
					Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
						Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
				CameraForward = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraForward"));
	//MovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("MovementComponent"));

	SetRootComponent(PlayerMesh);
	MovementArrow->SetupAttachment(PlayerMesh);
	PlayerCapsule->SetupAttachment(PlayerMesh);
	RootArmCenter->SetupAttachment(PlayerCapsule);
	RootArm->SetupAttachment(RootArmCenter);
	Arm->SetupAttachment(RootArm);
	Camera->SetupAttachment(Arm);
	CameraForward->SetupAttachment(RootArmCenter);


	CameraForward->bIsScreenSizeScaled = true;
	RootArmCenter->SetRelativeLocation(FVector(0.f, 0.f, 85.f));

	RootArm->SetRelativeLocationAndRotation(FVector(0.f, 50.f, 0.f), FRotator(-15.f, -3.f, 0.f));

	Arm->TargetArmLength = 250.f;

	Arm->bEnableCameraLag = true;
	Arm->CameraLagSpeed = 10;
	Arm->CameraLagMaxDistance = 1.f;

	Arm->bEnableCameraRotationLag = true;
	Arm->CameraRotationLagSpeed = 10.f;
	Arm->CameraLagMaxTimeStep = 1.f;

	currArmLenght = Arm->TargetArmLength;
	RotationSpeed = NormalRotationSpeed;
	MovementSpeed = NormalMovementSpeed;
	//MovementComponent->MaxWalkSpeed = MovementSpeed;
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APawn::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasePlayer::HorizontalRot(float value)
{
	if (value)
	{
		Rotate(value * RotationSpeed * GetWorld()->GetDeltaSeconds());
	}
}

void ABasePlayer::VerticalRot(float value)
{
	if (value)
	{
		float temp = Arm->GetRelativeRotation().Pitch + value;
		if (temp < 25 && temp > -65)
		{
			Arm->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}

void ABasePlayer::CheckJump()
{
	if (jumping)
	{
		jumping = false;
	}
	else
	{
		jumping = true;
	}
}

void ABasePlayer::Zoom(float value)
{
	if (value)
	{
		float temp = Arm->TargetArmLength + (value * -10);
		if (temp < 310 && temp > 140)
		{
			Arm->TargetArmLength = temp;
		}
	}
}

void ABasePlayer::ToggelZoomIn()
{
	currArmLenght = Arm->TargetArmLength;
	isZoomingIn = true;
	reachedTargetArmLenght = false;
	RotationSpeed = WeaponRotationSpeed;
	MovementSpeed = WeaponMovementSpeed;
	isPressingAim = true;
}

void ABasePlayer::ToggelZoomOut()
{
	isZoomingIn = false;
	reachedTargetArmLenght = false;
	isPressingAim = false;
	RotationSpeed = NormalRotationSpeed;
	MovementSpeed = NormalMovementSpeed;
}

void ABasePlayer::ZoomIn()
{
	if (Arm->TargetArmLength <= WeaponZoomScale)
	{
		Arm->TargetArmLength = WeaponZoomScale;
		reachedTargetArmLenght = true;
	}
	else
	{
		if (zoomRatio > 1)
		{
			zoomRatio = 1;
		}
		else
		{
			zoomRatio += GetWorld()->GetDeltaSeconds() * aimSpeed;
		}
	}
}

void ABasePlayer::ZoomOut()
{
	if (Arm->TargetArmLength >= currArmLenght)
	{
		Arm->TargetArmLength = currArmLenght;
		reachedTargetArmLenght = true;
	}
	else
	{
		if (zoomRatio < 0)
		{
			zoomRatio = 0;
		}
		else
		{
			zoomRatio -= GetWorld()->GetDeltaSeconds() * aimSpeed;
		}
	}
}

void ABasePlayer::Move(float leftright, float forwardback)
{
	Movement = MovementArrow->GetRightVector() * leftright;
	Movement += MovementArrow->GetForwardVector() * forwardback;
	Movement.Normalize();
	AddMovementInput(Movement);

	if (Movement.SizeSquared() > 0.1f)
	{
		FRotator rotation = UKismetMathLibrary::MakeRotFromX(Movement);
		PlayerCapsule->SetRelativeRotation(rotation);
	}
}

void ABasePlayer::Rotate(float LeftRight)
{
	MovementArrow->AddLocalRotation(FRotator(0.0f, LeftRight, 0.0f));
	RootArmCenter->AddWorldRotation(FRotator(0.0f, LeftRight, 0.0f));
}

void ABasePlayer::RotateToCameraForward()
{
	FRotator rotation = UKismetMathLibrary::MakeRotFromX(CameraForward->GetForwardVector());
	rotation.Yaw -= 90;
	//PlayerMesh->SetRelativeRotation(rotation);
}