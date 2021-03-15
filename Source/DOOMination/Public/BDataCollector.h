// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BDataCollector.generated.h"

UCLASS()
class DOOMINATION_API ABDataCollector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABDataCollector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "XML")
		void SaveXML(int waveAmount, float totalAmountDmgByPlayer, float totalAmountDmgByTurret, int totalTowerShots, int totalPlayerShotsHit, int totalPlayerShotsCrit, int totalArgentCollected, int totalArgentSpend, int totalArgentSpendForTurrets, int totalAmountWeaponUpgrade, int totalAmountTurretsPlaced, int totalAmountTurretsUpgraded, float totalPlayTimePistol, float totalPlayTimeMinigun, float totalPlayTimeHarpune, float totalPlayTimeSniper, float totalPlayTimeLMG, float totalPlayTimeShotgun, float totalDistanceWalked);
};
