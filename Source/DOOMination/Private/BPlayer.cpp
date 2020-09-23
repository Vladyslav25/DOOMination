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

	jumping = false;
	currArmLenght = Arm->TargetArmLength;
	currZoomScale = 30.f;
	reachedTargetArmLenght = true;

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

	GEngine->AddOnScreenDebugMessage(-1, GetWorld()->GetDeltaSeconds(), FColor::Red, FString::Printf(TEXT("reachedTargetArmLenght is: %s"), reachedTargetArmLenght));
	GEngine->AddOnScreenDebugMessage(-1, GetWorld()->GetDeltaSeconds(), FColor::Red, FString::Printf(TEXT("isZooming is: %s"), isZooming));

	if (jumping)
	{
		Jump();
	}

	if (!reachedTargetArmLenght && isZooming)
	{
		if (isZoomingIn)
		{
			ZoomIn();
		}
		else
		{
			ZoomOut();
		}
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
	InputComponent->BindAction("Aim", IE_Pressed, this, &ABPlayer::ZoomIn);
	InputComponent->BindAction("Aim", IE_Released, this, &ABPlayer::ZoomOut);
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
	isZooming = true;
	reachedTargetArmLenght = false;
}

void ABPlayer::ToggelZoomOut()
{
	isZoomingIn = false;
	isZooming = true;
	reachedTargetArmLenght = false;
}



void ABPlayer::ZoomIn()
{
	if (Arm->TargetArmLength <= currZoomScale)
	{
		Arm->TargetArmLength = currZoomScale;
		isZooming = false;
		reachedTargetArmLenght = true;
	}
	else
	{
		Arm->TargetArmLength -= GetWorld()->GetDeltaSeconds();
	}
}

void ABPlayer::ZoomOut()
{
	if (Arm->TargetArmLength >= currArmLenght)
	{
		Arm->TargetArmLength = currZoomScale;
		isZooming = false;
		reachedTargetArmLenght = true;
	}
	else
	{
		Arm->TargetArmLength += GetWorld()->GetDeltaSeconds();
	}
}

void ABPlayer::Move()
{
	//Normalize
	Movement.Normalize();

	//Add MovementSpeed
	Movement = Movement * MovementSpeed;

	AddMovementInput(Movement, 1);

	if (Movement.SizeSquared() > 0.1f)
	{
		FRotator rotation = UKismetMathLibrary::MakeRotFromX(Movement);
		rotation.Yaw -= 90.f;
		ACharacter::GetMesh()->SetRelativeRotation(rotation);
	}
}

void ABPlayer::Rotate(float LeftRight)
{
	ACharacter::GetArrowComponent()->AddLocalRotation(FRotator(0.0f, LeftRight, 0.0f));
	RootArmCenter->AddWorldRotation(FRotator(0.0f, LeftRight, 0.0f));
}
