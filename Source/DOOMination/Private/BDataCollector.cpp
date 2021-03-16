// Fill out your copyright notice in the Description page of Project Settings.


#include "BDataCollector.h"
#include <fstream> // ONLY USE TO SAVE XML TO FILE
#include <string> // ONLY USE TO SAVE XML TO FILE

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
	*s += "<XmlFiles>\n";

#pragma region content
	//int to FString	-->	FString::FromInt(int)
	//float to FString	-->	FString::SanitizeFloat(float) [?]

	// content
	// wave amount
	*s += "\t<WaveAmount>";
	//*s += FString::FromInt(waveAmount);
	*s += std::to_string(waveAmount);
	*s += "</WaveAmount>\n";

	// --- Damage --- //
	// Total amount of damage by player
	*s += "\t<TotalAmountDmgByPlayer>";
	//*s += FString::SanitizeFloat(totalAmountDmgByPlayer);
	*s += std::to_string(totalAmountDmgByPlayer);
	*s += "</TotalAmountDmgByPlayer>\n";

	// Total amount of damage by turret
	*s += "\t<TotalAmountDmgByTower>";
	//*s += FString::SanitizeFloat(totalAmountDmgByTurret);
	*s += std::to_string(totalAmountDmgByTurret);
	*s += "</TotalAmountDmgByTower>\n";

	// --- Shots --- //
	// Total amount of shots by Tower
	*s += "\t<TotalTowerShots>";
	//*s += FString::FromInt(totalTowerShots);
	*s += std::to_string(totalTowerShots);
	*s += "</TotalTowerShots>\n";

	// Total amount of shots hit by Player
	*s += "\t<TotalPlayerShotsHit>";
	//*s += FString::FromInt(totalPlayerShotsHit);
	*s += std::to_string(totalPlayerShotsHit);
	*s += "</TotalPlayerShotsHit>\n";

	// Total amount of shots hit critical by Player
	*s += "\t<TotalPlayerShotsHitCrit>";
	//*s += FString::FromInt(totalPlayerShotsCrit);
	*s += std::to_string(totalPlayerShotsCrit);
	*s += "</TotalPlayerShotsHitCrit>\n";

	// --- Argent --- //
	// Total amount of collected argent
	*s += "\t<TotalArgentCollected>";
	//*s += FString::FromInt(totalArgentCollected);
	*s += std::to_string(totalArgentCollected);
	*s += "</TotalArgentCollected>\n";

	// Total amount of argent spent
	*s += "\t<TotalArgentSpent>";
	//*s += FString::FromInt(totalArgentSpent);
	*s += std::to_string(totalArgentSpent);
	*s += "</TotalArgentSpent>\n";

	// Total amount of argent spent for tower
	*s += "\t<TotalArgentSpentForTurrets>";
	//*s += FString::FromInt(totalArgentSpentForTurrets);
	*s += std::to_string(totalArgentSpentForTurrets);
	*s += "</TotalArgentSpentForTurrets>\n";

	// --- Create and Upgrade --- //
	// Total amount of how many weapons were upgraded
	*s += "\t<TotalAmountWeaponUpgrade>";
	//*s += FString::FromInt(totalAmountWeaponUpgrade);
	*s += std::to_string(totalAmountWeaponUpgrade);
	*s += "</TotalAmountWeaponUpgrade>\n";

	// Total amount of how many turrets were placed
	*s += "\t<TotalAmountTurretsPlaced>";
	//*s += FString::FromInt(totalAmountTurretsPlaced);
	*s += std::to_string(totalAmountTurretsPlaced);
	*s += "</TotalAmountTurretsPlaced>\n";

	// Total amount of how many turret upgrades were purchased
	*s += "\t<TotalAmountTurretsUpgraded>";
	//*s += FString::FromInt(totalAmountTurretsUpgraded);
	*s += std::to_string(totalAmountTurretsUpgraded);
	*s += "</TotalAmountTurretsUpgraded>\n";

	// --- Weapon playtime --- //
	// Total amount of how long player used Pistol
	*s += "\t<TotalPlayTimePistol>";
	//*s += FString::SanitizeFloat(totalPlayTimePistol);
	*s += std::to_string(totalPlayTimePistol);
	*s += "</TotalPlayTimePistol>\n";

	// Total amount of how long player used minigun
	*s += "\t<TotalPlayTimeMinigun>";
	//*s += FString::SanitizeFloat(totalPlayTimeMinigun);
	*s += std::to_string(totalPlayTimeMinigun);
	*s += "</TotalPlayTimeMinigun>\n";

	// Total amount of how long player used Harpune
	*s += "\t<TotalPlayTimeHarpune>";
	//*s += FString::SanitizeFloat(totalPlayTimeHarpune);
	*s += std::to_string(totalPlayTimeHarpune);
	*s += "</TotalPlayTimeHarpune>\n";

	// Total amount of how long player used Harpune
	*s += "\t<TotalPlayTimeSniper>";
	//*s += FString::SanitizeFloat(totalPlayTimeSniper);
	*s += std::to_string(totalPlayTimeSniper);
	*s += "</TotalPlayTimeSniper>\n";

	// Total amount of how long player used Harpune
	*s += "\t<TotalPlayTimeLMG>";
	//*s += FString::SanitizeFloat(totalPlayTimeLMG);
	*s += std::to_string(totalPlayTimeLMG);
	*s += "</TotalPlayTimeLMG>\n";

	// Total amount of how long player used Shotgun
	*s += "\t<TotalPlayTimeShotgun>";
	//*s += FString::SanitizeFloat(totalPlayTimeShotgun);
	*s += std::to_string(totalPlayTimeShotgun);
	*s += "</TotalPlayTimeShotgun>\n";

	// --- Distance --- //
	// Total amount of how long player used Shotgun
	*s += "\t<TotalDistanceWalked>";
	//*s += FString::SanitizeFloat(totalDistanceWalked);
	*s += std::to_string(totalDistanceWalked);
	*s += "</TotalDistanceWalked>\n";
#pragma endregion

	// End of File
	* s += "</XmlFiles>";

#pragma region Save to File (temporary)
	//TEMPORARY: Save to File
	const char* temp = "C:\\Users\\Tobias\\Desktop\\Testordner\\Testfile.xml";
	
	std::ofstream* ofs = new std::ofstream(temp, std::ofstream::trunc);
	*ofs << *s;
	ofs->close();
	delete ofs;
	delete temp;
#pragma endregion

	delete s;
}



