// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayer.h"
#pragma region UE4 include
#include "Engine.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h" 
#include "Math/UnrealMathVectorCommon.h"
#pragma endregion
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>

// Sets default values
ABPlayer::ABPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootArm = CreateDefaultSubobject<USceneComponent>(TEXT("RootArm"));
	RootArmCenter = CreateDefaultSubobject<USceneComponent>(TEXT("RootArmCenter"));
	Playerforward = CreateDefaultSubobject<UArrowComponent>(TEXT("Player Forward"));

	Playerforward->SetupAttachment(ACharacter::GetCapsuleComponent());
	RootArmCenter->SetupAttachment(ACharacter::GetCapsuleComponent());
	RootArmCenter->SetRelativeLocation(FVector(0.f, 0.f, 85.f));

	RootArm->SetupAttachment(RootArmCenter);
	RootArm->SetRelativeLocationAndRotation(FVector(0.f, 50.f, 0.f), FRotator(-15.f, -3.f, 0.f));

	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Arm->SetupAttachment(RootArm);
	Arm->TargetArmLength = 250.f;

	Arm->bEnableCameraLag = true;
	Arm->CameraLagSpeed = 10;
	Arm->CameraLagMaxDistance = 1.f;

	Arm->bEnableCameraRotationLag = true;
	Arm->CameraRotationLagSpeed = 10.f;
	Arm->CameraLagMaxTimeStep = 1.f;

	Camera->AttachToComponent(Arm,FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);

	currArmLenght = Arm->TargetArmLength;
	RotationSpeed = NormalRotationSpeed;
	MovementSpeed = NormalMovementSpeed;
	ACharacter::GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

//// Called when the game starts or when spawned
//void ABPlayer::BeginPlay()
//{
//	Super::BeginPlay();
//}
//
//// Called every frame
//void ABPlayer::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}

// Called to bind functionality to input
void ABPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABPlayer::HorizontalRot(float value)
{
	if (value)
	{
		Rotate(value * RotationSpeed * GetWorld()->GetDeltaSeconds());
	}
}

void ABPlayer::VerticalRot(float value)
{
	if (value)
	{
		float temp = Arm->GetRelativeRotation().Pitch + value;
		if (temp < 45 && temp > -65)
		{
			Arm->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}

void ABPlayer::CheckJump()
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

void ABPlayer::Zoom(float value)
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

void ABPlayer::ToggelZoomIn()
{
	currArmLenght = Arm->TargetArmLength;
	isZoomingIn = true;
	reachedTargetArmLenght = false;
	RotationSpeed = WeaponRotationSpeed;
	MovementSpeed = WeaponMovementSpeed;
	isPressingAim = true;
}

void ABPlayer::ToggelZoomOut()
{
	isZoomingIn = false;
	reachedTargetArmLenght = false;
	isPressingAim = false;
	RotationSpeed = NormalRotationSpeed;
	MovementSpeed = NormalMovementSpeed;
}

void ABPlayer::ZoomIn()
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

void ABPlayer::ZoomOut()
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

void ABPlayer::Move(float leftright, float forwardback)
{
	Movement = ACharacter::GetArrowComponent()->GetRightVector() * leftright;
	Movement += ACharacter::GetArrowComponent()->GetForwardVector() * forwardback;
	Movement.Normalize();
	ACharacter::GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	AddMovementInput(Movement);

	if (Movement.SizeSquared() > 0.1f)
	{
		FRotator rotation = UKismetMathLibrary::MakeRotFromX(Movement);
		rotation.Yaw -= 90;
		ACharacter::GetMesh()->SetRelativeRotation(rotation);
	}
}

void ABPlayer::Rotate(float LeftRight)
{
	ACharacter::GetCapsuleComponent()->AddWorldRotation(FRotator(0.0f, LeftRight, 0.0f));
}