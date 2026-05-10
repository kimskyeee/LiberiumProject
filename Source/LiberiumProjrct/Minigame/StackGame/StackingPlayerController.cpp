// Copyright LiberiumProject. All Rights Reserved.

#include "Minigame/StackGame/StackingPlayerController.h"
#include "Minigame/StackGame/StackingGameMode.h"
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
