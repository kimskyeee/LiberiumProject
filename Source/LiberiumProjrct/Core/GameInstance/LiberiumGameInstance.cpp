// Copyright LiberiumProject. All Rights Reserved.

#include "LiberiumGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "LiberiumProjrct/Core/LiberiumGameTypes.h"

void ULiberiumGameInstance::Init()
{
	Super::Init();

	CurrentGamePhase = EGamePhase::Town;
}

void ULiberiumGameInstance::SetGamePhase(EGamePhase NewPhase)
{
	if (CurrentGamePhase == NewPhase)
	{
		return;
	}

	CurrentGamePhase = NewPhase;
}

void ULiberiumGameInstance::TravelToMap(const TSoftObjectPtr<UWorld>& MapAsset)
{
	if (MapAsset.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("TravelToMap: MapAsset is null."));
		return;
	}

	const FString MapPath = MapAsset.ToSoftObjectPath().GetLongPackageName();
	GetWorld()->ServerTravel(MapPath);
}
