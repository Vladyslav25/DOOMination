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

	//ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForrwardArrow"));
	//ForwardArrow->AttachTo(RootComponent);

	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	//Arm->AttachTo(RootArm);
	Arm->SetupAttachment(RootArm);
	Arm->TargetArmLength = 300.f;
	Arm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));

	Arm->bEnableCameraLag = true;
	Arm->CameraLagSpeed = 10;
	Arm->CameraLagMaxDistance = 1.f;

	Arm->bEnableCameraRotationLag = true;
	Arm->CameraRotationLagSpeed = 10.f;
	Arm->CameraLagMaxTimeStep = 1.f;

	Camera->AttachTo(Arm, USpringArmComponent::SocketName);

	jumping = false;

	firstPerson = false;
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

	if (jumping)
	{
		Jump();
	}
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
	InputComponent->BindAction("ChangeCamera", IE_Pressed, this, &ABPlayer::Switch);
}

void ABPlayer::HorizontalMove(float value)
{
	if (value)
	{
		AddMovementInput(ACharacter::GetArrowComponent()->GetRightVector(), value);
		FRotator rot = UKismetMathLibrary::MakeRotFromX(ACharacter::GetArrowComponent()->GetRightVector());
		SetActorRelativeRotation(rot);
	}
}

void ABPlayer::VerticalMove(float value)
{
	if (value)
	{
		AddMovementInput(ACharacter::GetArrowComponent()->GetForwardVector(), value);
	}
}

void ABPlayer::HorizontalRot(float value)
{
	if (value)
	{
		ACharacter::GetArrowComponent()->AddWorldRotation(FRotator(0, value, 0));
		Arm->AddWorldRotation(FRotator(0, value, 0));
		//AddActorWorldRotation(FRotator(0, value, 0));
	}
}

void ABPlayer::VerticalRot(float value)
{
	if (value)
	{
		float temp = 0;
		if (firstPerson)
		{
			temp = Camera->GetRelativeRotation().Pitch + value;
			if (temp < 65 && temp > -65)
			{
				Camera->AddLocalRotation(FRotator(value, 0, 0));
			}
		}
		else
		{
			temp = Arm->GetRelativeRotation().Pitch + value;
			if (temp < 25 && temp > -65)
			{
				Arm->AddLocalRotation(FRotator(value, 0, 0));
			}
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

void ABPlayer::Switch()
{
	if (firstPerson)
	{
		Arm->TargetArmLength = 300;
		Arm->SetRelativeRotation(FRotator(-15, 0, 0));
		Camera->SetRelativeRotation(FRotator(0, 0, 0));
		Camera->AttachTo(Arm, USpringArmComponent::SocketName);
		firstPerson = false;
	}
	else
	{
		Camera->AttachTo(RootComponent);
		Camera->SetRelativeLocation(FVector(0, 0, 100));
		firstPerson = true;
	}
}

void ABPlayer::Move(float LeftRight, float ForwardBack)
{
	Movement = MovementDirection->GetForwardVector() * ForwardBack;
	Movement += MovementDirection->GetRightVector() * LeftRight;

	//Normalize
	Movement.Normalize();

	//Add MovementSpeed
	Movement = Movement * MovementSpeed;

	// try to add world offset
	ACharacter::GetCapsuleComponent()->AddWorldOffset(Movement * GetWorld()->GetDeltaSeconds(), true);

	if (Movement.SizeSquared() > 0.1f)
	{

		FRotator rotation = UKismetMathLibrary::MakeRotFromX(Movement);
		ACharacter::GetMesh()->SetRelativeRotation(rotation);
	}
}
