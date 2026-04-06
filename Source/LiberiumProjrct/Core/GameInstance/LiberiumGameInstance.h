// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Core/LiberiumGameTypes.h"
#include "LiberiumGameInstance.generated.h"

UCLASS()
class LIBERIUMPROJRCT_API ULiberiumGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "Game")
	EGamePhase GetGamePhase() const { return CurrentGamePhase; }

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetGamePhase(EGamePhase NewPhase);

	UFUNCTION(BlueprintCallable, Category = "Map")
	void TravelToMap(const TSoftObjectPtr<UWorld>& MapAsset);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
	EGamePhase CurrentGamePhase = EGamePhase::None;
};
