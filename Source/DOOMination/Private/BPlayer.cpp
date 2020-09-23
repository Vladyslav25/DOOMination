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
	CameraForward = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraForward"));
	CameraForward->SetupAttachment(RootArmCenter);
	CameraForward->bIsScreenSizeScaled = true;
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

	Camera->AttachTo(Arm, USpringArmComponent::SocketName);

	currArmLenght = Arm->TargetArmLength;
	RotationSpeed = NormalRotationSpeed;
	MovementSpeed = NormalMovementSpeed;
}

// Called when the game starts or when spawned
void ABPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, GetWorld()->GetDeltaSeconds(), FColor::Purple, FString::Printf(TEXT("CameraForward is: %s"), *CameraForward->GetForwardVector().ToString()));
	GEngine->AddOnScreenDebugMessage(-1, GetWorld()->GetDeltaSeconds(), FColor::Purple, FString::Printf(TEXT("rotPlayer is: %s"), rotPlayer ? TEXT("true") : TEXT("false")));
	GEngine->AddOnScreenDebugMessage(-1, GetWorld()->GetDeltaSeconds(), FColor::Purple, FString::SanitizeFloat(rotRatio));

	if (!isPressingAim && Movement.SizeSquared() > 0.1f || isPressingAim)
	{
		ToggelRotateToCameraForward();
	}
	else
	{
		rotPlayer = false;
		rotRatio = 0;
	}

	if (!rotPlayer)
	{
		rotPlayer = false;
		rotRatio = 0;
	}

	if (jumping)
	{
		Jump();
	}

	if (!reachedTargetArmLenght)
	{
		if (isZoomingIn)
		{
			ZoomIn();
		}
		else
		{
			ZoomOut();
		}
		Arm->TargetArmLength = FMath::Lerp(currArmLenght, WeaponZoomScale, zoomRatio);
	}

	if (rotPlayer)
	{
		RotateToCameraForward();
	}

	Move();
	Movement = FVector(0, 0, 0);
}

// Called to bind functionality to input
void ABPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal Movement", this, &ABPlayer::HorizontalMove);
	InputComponent->BindAxis("Vertical Movement", this, &ABPlayer::VerticalMove);
	InputComponent->BindAxis("Horizontal Rotation", this, &ABPlayer::HorizontalRot);
	InputComponent->BindAxis("Vertical Rotation", this, &ABPlayer::VerticalRot);

	InputComponent->BindAxis("Zoom", this, &ABPlayer::Zoom);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ABPlayer::CheckJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ABPlayer::CheckJump);
	InputComponent->BindAction("Aim", IE_Pressed, this, &ABPlayer::ToggelZoomIn);
	InputComponent->BindAction("Aim", IE_Released, this, &ABPlayer::ToggelZoomOut);
}

void ABPlayer::HorizontalMove(float value)
{
	if (value)
	{
		Movement += ACharacter::GetArrowComponent()->GetRightVector() * value;
	}
}

void ABPlayer::VerticalMove(float value)
{
	if (value)
	{
		Movement += ACharacter::GetArrowComponent()->GetForwardVector() * value;
	}
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
		if (temp < 25 && temp > -65)
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
	GEngine->AddOnScreenDebugMessage(-1, GetWorld()->GetDeltaSeconds(), FColor::Yellow, TEXT("----ZoomIN----"));

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
	GEngine->AddOnScreenDebugMessage(-1, GetWorld()->GetDeltaSeconds(), FColor::Yellow, TEXT("----ZoomOUT----"));

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

void ABPlayer::Move()
{
	Movement.Normalize();
	Movement = Movement * MovementSpeed;

	AddMovementInput(Movement);
}

void ABPlayer::Rotate(float LeftRight)
{
	ACharacter::GetArrowComponent()->AddLocalRotation(FRotator(0.0f, LeftRight, 0.0f));
	RootArmCenter->AddWorldRotation(FRotator(0.0f, LeftRight, 0.0f));
}

void ABPlayer::RotateToCameraForward()
{
	rotRatio += GetWorld()->GetDeltaSeconds() * rotSpeed;
	if (rotRatio >= 1)
	{
		rotRatio = 1;
	}
	FRotator rotation = UKismetMathLibrary::MakeRotFromX(FMath::Lerp(rotStartForward, CameraForward->GetForwardVector(), rotRatio));
	//rotation.Yaw -= 90.f;
	ACharacter::GetMesh()->SetRelativeRotation(rotation);
}

void ABPlayer::ToggelRotateToCameraForward()
{
	if (!rotPlayer)
	{
		rotRatio = 0;
		rotStartForward = ACharacter::GetMesh()->GetForwardVector();
		rotPlayer = true;
	}
}
