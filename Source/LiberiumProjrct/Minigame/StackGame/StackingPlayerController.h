// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StackingPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class UStackGameHUDViewModel;
class UStackGameHUDWidget;
class UGameOverWidget;
class UGameOverViewModel;

UCLASS()
class LIBERIUMPROJRCT_API AStackingPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UStackGameHUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGameOverWidget> GameOverWidgetClass;

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

	UPROPERTY()
	TObjectPtr<UStackGameHUDViewModel> HUDViewModel;

	UPROPERTY()
	TObjectPtr<UStackGameHUDWidget> HUDWidget;

	UPROPERTY()
	TObjectPtr<UGameOverViewModel> GameOverVM;

	UPROPERTY()
	TObjectPtr<UGameOverWidget> GameOverWidgetInstance;

	void OnDropPressed();
	void OnRestartPressed();
	void CreateHUD();

	UFUNCTION()
	void OnGameOver();
};
