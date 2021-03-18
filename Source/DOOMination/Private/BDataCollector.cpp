// Fill out your copyright notice in the Description page of Project Settings.


#include "BDataCollector.h"
#include <string>
//#include <fstream> // ONLY USE TO SAVE XML TO FILE

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

void ABDataCollector::SaveXML(
	int waveAmount,
	float totalAmountDmgByPlayer,
	float totalAmountDmgByTurret,
	int totalTowerShots,
	int totalPlayerShots,
	int totalPlayerShotsHit,
	int totalPlayerShotsCrit,
	int totalArgentCollected,
	int totalArgentSpent,
	int totalArgentSpentForTurrets,
	int totalAmountWeaponUpgrade,
	int totalAmountTurretsPlaced,
	int totalAmountTurretsUpgraded,
	float totalPlayTimePistol,
	float totalPlayTimeMinigun,
	float totalPlayTimeHarpune,
	float totalPlayTimeSniper,
	float totalPlayTimeLMG,
	float totalPlayTimeShotgun,
	float totalDistanceWalked)//
{
	std::string* s = new std::string();

	// XML Header
	*s = "<?xml version=\"1.0\"?>\n";
	*s += "<ArrayOfRound>\n";
	*s += "\t<Round>";
#pragma region content
	//int to FString	-->	FString::FromInt(int)
	//float to FString	-->	FString::SanitizeFloat(float) [?]

	// content
#pragma region Save Time
	// date time
	* s += "\t\t<DateOfRound>";
	FDateTime timeNow;
	timeNow = FDateTime::UtcNow();
	// year
	*s += std::to_string(timeNow.GetYear()) + "-";
	// month
	*s += std::to_string(timeNow.GetMonth()) + "-";
	// day
	*s += std::to_string(timeNow.GetDay());
	
	// hour
	*s += "T" + std::to_string(timeNow.GetHour()) + ":";
	// minute
	*s += std::to_string(timeNow.GetMinute()) + ":";
	// second
	*s += std::to_string(timeNow.GetSecond()) + ".";
	// minisecond
	*s += std::to_string(timeNow.GetMillisecond());

	//GTM (HARDCODED)
	*s += "+01:00";
	*s += "</DateOfRound>";
#pragma endregion
	

	// wave amount
	*s += "\t\t<WaveAmount>";
	//*s += FString::FromInt(waveAmount);
	*s += std::to_string(waveAmount);
	*s += "</WaveAmount>\n";

	// --- Damage --- //
	// Total amount of damage
	*s += "\t\t<CompleteAmountOfDamage>";
	//*s += FString::SanitizeFloat(totalAmountDmgByPlayer);
	float totalDmg = totalAmountDmgByPlayer + totalAmountDmgByTurret;
	*s += std::to_string(totalDmg);
	*s += "</CompleteAmountOfDamage>\n";

	// Total amount of damage by player
	*s += "\t\t<CompleteAmountOfDamageByPlayer>";
	//*s += FString::SanitizeFloat(totalAmountDmgByPlayer);
	*s += std::to_string(totalAmountDmgByPlayer);
	*s += "</CompleteAmountOfDamageByPlayer>\n";

	// Total amount of damage by turret
	*s += "\t\t<CompleteAmountOfDamageByTurret>";
	//*s += FString::SanitizeFloat(totalAmountDmgByTurret);
	*s += std::to_string(totalAmountDmgByTurret);
	*s += "</CompleteAmountOfDamageByTurret>\n";

	// --- Shots --- //
	// Total amount of shots by Tower (NOT IMPLEMENTED IN WPF YET)
	*s += "\t\t<TotalTowerShots>";
	//*s += FString::FromInt(totalTowerShots);
	*s += std::to_string(totalTowerShots);
	*s += "</TotalTowerShots>\n";

	// Total amount of shots by Player
	*s += "\t\t<ShotsFired>";
	//*s += FString::FromInt(totalTowerShots);
	*s += std::to_string(totalPlayerShots);
	*s += "</ShotsFired>\n";

	// Total amount of shots hit by Player
	*s += "\t\t<ShotsHit>";
	//*s += FString::FromInt(totalPlayerShotsHit);
	*s += std::to_string(totalPlayerShotsHit);
	*s += "</ShotsHit>\n";

	// Total amount of shots hit critical by Player
	*s += "\t\t<ShotsCrit>";
	//*s += FString::FromInt(totalPlayerShotsCrit);
	*s += std::to_string(totalPlayerShotsCrit);
	*s += "</ShotsCrit>\n";

	// --- Argent --- //
	// Total amount of collected argent
	*s += "\t\t<CollectedArgent>";
	//*s += FString::FromInt(totalArgentCollected);
	*s += std::to_string(totalArgentCollected);
	*s += "</CollectedArgent>\n";

	// Total amount of argent spent
	*s += "\t\t<SpendedAmountOfArgent>";
	//*s += FString::FromInt(totalArgentSpent);
	*s += std::to_string(totalArgentSpent);
	*s += "</SpendedAmountOfArgent>\n";

	// Total amount of argent spent for tower
	*s += "\t\t<SpendedAmountOfArgentForTurrets>";
	//*s += FString::FromInt(totalArgentSpentForTurrets);
	*s += std::to_string(totalArgentSpentForTurrets);
	*s += "</SpendedAmountOfArgentForTurrets>\n";

	// --- Create and Upgrade --- //
	// Total amount of how many weapons were upgraded
	*s += "\t\t<AmountOfWeaponUpgrades>";
	//*s += FString::FromInt(totalAmountWeaponUpgrade);
	*s += std::to_string(totalAmountWeaponUpgrade);
	*s += "</AmountOfWeaponUpgrades>\n";

	// Total amount of how many turrets were placed
	*s += "\t\t<AmountOfTurretsPlaced>";
	//*s += FString::FromInt(totalAmountTurretsPlaced);
	*s += std::to_string(totalAmountTurretsPlaced);
	*s += "</AmountOfTurretsPlaced>\n";
	
	// Total amount of how many turret upgrades were purchased
	*s += "\t\t<AmountOfTurretUpgrades>";
	//*s += FString::FromInt(totalAmountTurretsUpgraded);
	*s += std::to_string(totalAmountTurretsUpgraded);
	*s += "</AmountOfTurretUpgrades>\n";

	// --- Weapon playtime --- //
	// Total amount of how long player used Pistol
	*s += "\t\t<TotalPlayTimePistol>";
	//*s += FString::SanitizeFloat(totalPlayTimePistol);
	*s += std::to_string(totalPlayTimePistol);
	*s += "</TotalPlayTimePistol>\n";

	// Total amount of how long player used minigun
	*s += "\t\t<TotalPlayTimeMinigun>";
	//*s += FString::SanitizeFloat(totalPlayTimeMinigun);
	*s += std::to_string(totalPlayTimeMinigun);
	*s += "</TotalPlayTimeMinigun>\n";

	// Total amount of how long player used Harpune
	*s += "\t\t<TotalPlayTimeHarpune>";
	//*s += FString::SanitizeFloat(totalPlayTimeHarpune);
	*s += std::to_string(totalPlayTimeHarpune);
	*s += "</TotalPlayTimeHarpune>\n";

	// Total amount of how long player used Harpune
	*s += "\t\t<TotalPlayTimeSniper>";
	//*s += FString::SanitizeFloat(totalPlayTimeSniper);
	*s += std::to_string(totalPlayTimeSniper);
	*s += "</TotalPlayTimeSniper>\n";

	// Total amount of how long player used Harpune
	*s += "\t\t<TotalPlayTimeLMG>";
	//*s += FString::SanitizeFloat(totalPlayTimeLMG);
	*s += std::to_string(totalPlayTimeLMG);
	*s += "</TotalPlayTimeLMG>\n";

	// Total amount of how long player used Shotgun
	*s += "\t\t<TotalPlayTimeShotgun>";
	//*s += FString::SanitizeFloat(totalPlayTimeShotgun);
	*s += std::to_string(totalPlayTimeShotgun);
	*s += "</TotalPlayTimeShotgun>\n";

	// --- Distance --- //
	// Total amount of how long player used Shotgun
	*s += "\t\t<DistancePlayer>";
	//*s += FString::SanitizeFloat(totalDistanceWalked);
	*s += std::to_string(totalDistanceWalked);
	*s += "</DistancePlayer>\n";
#pragma endregion

	// End of File
	* s += "\t</Round>";
	* s += "</ArrayOfRound>";

#pragma region Save to File (temporary)
	//TEMPORARY: Save to File
	//const char* temp = "E:\\Tobias\\Dokumente\\ToTest\\Game.xml";
	//
	//std::ofstream* ofs = new std::ofstream(temp, std::ofstream::trunc);
	//*ofs << *s;
	//ofs->close();
	//delete ofs;
#pragma endregion

	delete s;
}



