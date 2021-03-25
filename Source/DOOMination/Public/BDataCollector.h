// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>

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
		/// <summary>
		/// Save collected Data to a xml file located in "My Documents/DOOMination/[current Date/Time].xml"
		/// </summary>
		void SaveXML(int waveAmount, float totalAmountDmgByPlayer, float totalAmountDmgByTurret, int totalTowerShots, int totalPlayerShots, int totalPlayerShotsHit, int totalPlayerShotsCrit, int totalArgentCollected, int totalArgentSpend, int totalArgentSpendForTurrets, int totalAmountWeaponUpgrade, int totalAmountTurretsPlaced, int totalAmountTurretsUpgraded, float totalPlayTimePistol, float totalPlayTimeMinigun, float totalPlayTimeHarpune, float totalPlayTimeSniper, float totalPlayTimeLMG, float totalPlayTimeShotgun, float totalDistanceWalked);

private:
	/// <summary>
	/// Add Zero to Number if number is less that maxLenght
	/// </summary>
	/// <param name="number">number to check</param>
	/// <param name="maxLenght">max amount of characters</param>
	/// <returns>new number as string</returns>
	std::string AddZero(int number, int maxLenght);

	/// <summary>
	/// Add Zero to Number if number is less that maxLenght
	/// </summary>
	/// <param name="number">number to check</param>
	/// <param name="maxLenght">max amount of characters</param>
	/// <returns>new number as string</returns>
	std::string AddZero(float number, int maxLenght);

	/// <summary>
	/// Get save Directory, not FILE
	/// </summary>
	/// <returns></returns>
	std::string GetSaveDirectory();
};
