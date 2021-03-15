// Fill out your copyright notice in the Description page of Project Settings.


#include "BDataCollector.h"

// Sets default values
ABDataCollector::ABDataCollector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABDataCollector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABDataCollector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABDataCollector::SaveXML(int waveAmount, float totalAmountDmgByPlayer, float totalAmountDmgByTurret, int totalTowerShots, int totalPlayerShotsHit, int totalPlayerShotsCrit, int totalArgentCollected, int totalArgentSpend, int totalArgentSpendForTurrets, int totalAmountWeaponUpgrade, int totalAmountTurretsPlaced, int totalAmountTurretsUpgraded, float totalPlayTimePistol, float totalPlayTimeMinigun, float totalPlayTimeHarpune, float totalPlayTimeSniper, float totalPlayTimeLMG, float totalPlayTimeShotgun, float totalDistanceWalked)
{

}



