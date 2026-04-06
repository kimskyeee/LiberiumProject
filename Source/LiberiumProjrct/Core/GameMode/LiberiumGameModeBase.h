// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LiberiumGameModeBase.generated.h"

class ULiberiumGameInstance;

UCLASS()
class LIBERIUMPROJRCT_API ALiberiumGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALiberiumGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "Game")
	ULiberiumGameInstance* GetLiberiumGameInstance() const;

protected:
	virtual void BeginPlay() override;
};
