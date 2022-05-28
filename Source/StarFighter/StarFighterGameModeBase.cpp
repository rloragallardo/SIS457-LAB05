// Copyright Epic Games, Inc. All Rights Reserved.


#include "StarFighterGameModeBase.h"
#include "NaveTerrestreEnemiga01.h"
#include "NaveAcuatica.h"
void AStarFighterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Dentro de BeginPlay en GameModeBase"));
	GetWorldTimerManager().SetTimer(AcuaticaTimerHandle, this, &AStarFighterGameModeBase::SpawnNave, 03.0f, true, 2.0f);


}

AStarFighterGameModeBase::AStarFighterGameModeBase()
{


}

void AStarFighterGameModeBase::SpawnNave()
{
	UWorld* const World = GetWorld();

	srand(time(nullptr));
	ejeX = rand() % 100 + 1;
	ejeY = rand() % 100 + 1;

	World->SpawnActor<ANaveAcuatica>(FVector(ejeX, ejeY, 112.0f), FRotator::ZeroRotator);

}
