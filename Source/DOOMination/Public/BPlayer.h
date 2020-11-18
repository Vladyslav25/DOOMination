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

public:
	// Called to bind functionality to input

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Camera")
		UCameraComponent* Camera = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Camera")
		USpringArmComponent* Arm = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Camera")
		USceneComponent* RootArm = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Camera")
		USceneComponent* RootArmCenter = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Aim")
		float RotationSpeed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Aim")
		float NormalRotationSpeed = 180.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Aim")
		float WeaponRotationSpeed = 80.0f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player")
		UArrowComponent* Playerforward = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player")
		float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		float NormalMovementSpeed = 500.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Player")
		float WeaponMovementSpeed = 100.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player")
		FVector Movement = FVector();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Aim")
		float WeaponZoomScale = 20.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Aim")
		float aimSpeed = 10.f;

	UFUNCTION(BlueprintCallable, DisplayName = "Rotate Horizontal")
		void HorizontalRot(float value);
	UFUNCTION(BlueprintCallable, DisplayName = "Rotate Vertical")
		void VerticalRot(float value);

	UFUNCTION(BlueprintCallable, DisplayName = "Check for Jump")
		void CheckJump();

	UFUNCTION(BlueprintCallable)
		void Zoom(float value);
	UFUNCTION(BlueprintCallable, DisplayName = "Toggel Zoom In")
		void ToggelZoomIn();
	UFUNCTION(BlueprintCallable, DisplayName = "Toggel Zoom Out")
		void ToggelZoomOut();

	UFUNCTION(BlueprintCallable, DisplayName = "Zoom In")
		void ZoomIn();
	UFUNCTION(BlueprintCallable, DisplayName = "Zoom Out")
		void ZoomOut();

	UFUNCTION(BlueprintCallable, DisplayName = "Move Player")
		void Move(float leftright, float forwardback);
	UFUNCTION(BlueprintCallable, DisplayName = "Rotate Player")
		void Rotate(float LeftRight);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool jumping = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool isPressingAim = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool reachedTargetArmLenght = true;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool isZooming;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool isZoomingIn;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float currArmLenght;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float zoomRatio = 0.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float rotSpeed = 6.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FVector rotStartForward = FVector();
};
