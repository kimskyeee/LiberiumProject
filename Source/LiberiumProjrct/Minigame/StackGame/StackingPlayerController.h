// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StackingPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class LIBERIUMPROJRCT_API AStackingPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	TObjectPtr<UInputAction> DropAction;

	UPROPERTY()
	TObjectPtr<UInputAction> RestartAction;

	UPROPERTY()
	TObjectPtr<UInputMappingContext> GameMappingContext;

	void OnDropPressed();
	void OnRestartPressed();
};
