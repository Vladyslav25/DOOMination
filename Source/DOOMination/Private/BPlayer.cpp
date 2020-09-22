// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayer.h"

// Sets default values
ABPlayer::ABPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
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

}

// Called to bind functionality to input
void ABPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal Movement", this, &ABPlayer::HorizontalMove);
	InputComponent->BindAxis("Vertical Movement", this, &ABPlayer::VerticalMove);
}

void ABPlayer::HorizontalMove(float value) 
{
	if (value) 
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void ABPlayer::VerticalMove(float value) {
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}