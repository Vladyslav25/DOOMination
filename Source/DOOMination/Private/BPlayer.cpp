// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayer.h"

// Sets default values
ABPlayer::ABPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = false;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->AttachTo(RootComponent);

	jumping = false;
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

	InputComponent->BindAction("Jump", IE_Pressed, this, &ABPlayer::CheckJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ABPlayer::CheckJump);
}

void ABPlayer::HorizontalMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void ABPlayer::VerticalMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void ABPlayer::HorizontalRot(float value)
{
	if (value)
	{
		AddActorWorldRotation(FRotator(0, value, 0));
	}
}

void ABPlayer::VerticalRot(float value)
{
	if (value)
	{
		AddActorLocalRotation(FRotator(value, 0, 0));
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
