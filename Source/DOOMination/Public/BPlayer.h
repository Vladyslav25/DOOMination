// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "BPlayer.generated.h"

#pragma region forward decleration
class USceneComponent;
class UCapsuleComponent;
class UCameraComponent;
class USpringArmComponent;
class UArrowComponent;
class UInstancedStaticMeshComponent;
#pragma endregion


UCLASS()
class DOOMINATION_API ABPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		UCameraComponent* Camera = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USpringArmComponent* Arm = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Player")
		USceneComponent* RootArm = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		/// <summary>
		/// rotation speed in angle per second
		/// </summary>
		float RotationSpeed = 180.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		/// <summary>
		/// movement speed in cm per second
		/// </summary>
		float MovementSpeed = 500.0f;

	//Vladi
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		/// <summary>
		/// currend movement speed in cm per second
		/// </summary>
		FVector Movement = FVector();

private:
	void HorizontalMove(float value);
	void VerticalMove(float value);
	void HorizontalRot(float value);
	void VerticalRot(float value);

	void CheckJump();

	void Zoom(float value);
	void Switch();

	void Move();
	void Rotate(float LeftRight);


	UPROPERTY()
		bool jumping;

	UPROPERTY()
		bool firstPerson;

};
