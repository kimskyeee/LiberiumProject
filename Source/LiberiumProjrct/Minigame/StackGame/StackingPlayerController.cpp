// Copyright LiberiumProject. All Rights Reserved.

#include "LiberiumProjrct/Minigame/StackGame/StackingPlayerController.h"
#include "LiberiumProjrct/Minigame/StackGame/StackingGameMode.h"
#include "UI/ViewModel/StackGameHUDViewModel.h"
#include "UI/ViewModel/GameOverViewModel.h"
#include "UI/View/StackGameHUDWidget.h"
#include "UI/View/GameOverWidget.h"
#include "UI/Model/MinigameResult.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"

void AStackingPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AStackingPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());

	// Create input actions
	DropAction = NewObject<UInputAction>(this, TEXT("IA_Drop"));
	DropAction->ValueType = EInputActionValueType::Boolean;

	RestartAction = NewObject<UInputAction>(this, TEXT("IA_Restart"));
	RestartAction->ValueType = EInputActionValueType::Boolean;

	// Create mapping context and bind keys
	GameMappingContext = NewObject<UInputMappingContext>(this, TEXT("IMC_StackGame"));
	GameMappingContext->MapKey(DropAction, EKeys::SpaceBar);
	GameMappingContext->MapKey(RestartAction, EKeys::R);

	// Add mapping context to the local player
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(GameMappingContext, 0);
	}

	// Bind actions
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(DropAction, ETriggerEvent::Started, this, &AStackingPlayerController::OnDropPressed);
		EIC->BindAction(RestartAction, ETriggerEvent::Started, this, &AStackingPlayerController::OnRestartPressed);
	}

	// Create HUD
	CreateHUD();

	// Bind game over event
	if (AStackingGameMode* GM = Cast<AStackingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->OnGameOverEvent.AddDynamic(this, &AStackingPlayerController::OnGameOver);
	}
}

void AStackingPlayerController::CreateHUD()
{
	if (!HUDWidgetClass)
	{
		return;
	}

	HUDViewModel = NewObject<UStackGameHUDViewModel>(this);
	HUDViewModel->Initialize(GetWorld());

	HUDWidget = CreateWidget<UStackGameHUDWidget>(this, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->SetViewModel(HUDViewModel);
		HUDWidget->AddToViewport();
	}
}

void AStackingPlayerController::OnGameOver()
{
	if (!GameOverWidgetClass)
	{
		return;
	}

	// Populate result
	FMinigameResult Result;
	Result.GameName = FText::FromString(TEXT("Stack Game"));

	if (AStackingGameMode* GM = Cast<AStackingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		Result.Score = GM->GetScore();
		Result.ExtraFields.Add(TEXT("Blocks"), FText::AsNumber(GM->GetBlockCount()));
	}

	// Create GameOver ViewModel and Widget
	GameOverVM = NewObject<UGameOverViewModel>(this);
	GameOverVM->SetResult(Result);

	GameOverWidgetInstance = CreateWidget<UGameOverWidget>(this, GameOverWidgetClass);
	if (GameOverWidgetInstance)
	{
		GameOverWidgetInstance->SetViewModel(GameOverVM);
		GameOverWidgetInstance->AddToViewport(10);
	}
}

void AStackingPlayerController::OnDropPressed()
{
	if (AStackingGameMode* GM = Cast<AStackingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->DropCurrentBlock();
	}
}

void AStackingPlayerController::OnRestartPressed()
{
	if (AStackingGameMode* GM = Cast<AStackingGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->RestartGame();
	}
}
