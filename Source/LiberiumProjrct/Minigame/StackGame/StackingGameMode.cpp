// Copyright LiberiumProject. All Rights Reserved.

#include "Minigame/StackGame/StackingGameMode.h"
#include "Minigame/StackGame/StackBlock.h"
#include "Minigame/StackGame/StackingPlayerController.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

AStackingGameMode::AStackingGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AStackingPlayerController::StaticClass();
}

void AStackingGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Spawn orthographic camera
	GameCamera = GetWorld()->SpawnActor<ACameraActor>(
		ACameraActor::StaticClass(),
		FVector(0.f, -CameraDistance, InitialCameraZ),
		FRotator(0.f, 90.f, 0.f)
	);

	if (GameCamera)
	{
		UCameraComponent* CamComp = GameCamera->GetCameraComponent();
		CamComp->ProjectionMode = ECameraProjectionMode::Orthographic;
		CamComp->OrthoWidth = CameraOrthoWidth;

		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			PC->SetViewTarget(GameCamera);
		}
	}

	SpawnBaseBlock();
	SpawnNextBlock();
}

void AStackingGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateCamera(DeltaTime);
}

void AStackingGameMode::SpawnBaseBlock()
{
	AStackBlock* BaseBlock = GetWorld()->SpawnActor<AStackBlock>(
		AStackBlock::StaticClass(),
		FVector(0.f, 0.f, BlockHeight * 0.5f),
		FRotator::ZeroRotator
	);

	if (BaseBlock)
	{
		StackedBlocks.Add(BaseBlock);
	}
}

void AStackingGameMode::SpawnNextBlock()
{
	if (bGameOver || StackedBlocks.Num() == 0)
	{
		return;
	}

	float TopZ = GetStackTopZ();
	float TargetZ = TopZ + BlockHeight * 0.5f;
	float SpawnZ = TargetZ + SpawnHeightOffset;
	float TopBlockX = StackedBlocks.Last()->GetActorLocation().X;

	CurrentBlock = GetWorld()->SpawnActor<AStackBlock>(
		AStackBlock::StaticClass(),
		FVector(MoveBoundaryLeft, 0.f, SpawnZ),
		FRotator::ZeroRotator
	);

	if (CurrentBlock)
	{
		CurrentBlock->OnLanded.BindUObject(this, &AStackingGameMode::OnBlockLanded);
		CurrentBlock->OnFell.BindUObject(this, &AStackingGameMode::OnBlockFell);
		CurrentBlock->StartMoving(GetCurrentMoveSpeed(), MoveBoundaryLeft, MoveBoundaryRight, TargetZ, TopBlockX);
	}
}

void AStackingGameMode::DropCurrentBlock()
{
	if (bGameOver || !CurrentBlock)
	{
		return;
	}
	CurrentBlock->Drop();
}

void AStackingGameMode::OnBlockLanded(AStackBlock* Block)
{
	StackedBlocks.Add(Block);
	CurrentBlock = nullptr;

	BlockCount++;
	Score += 1;

	if (BlockCount % 10 == 0)
	{
		Score += 3;
	}

	UE_LOG(LogTemp, Log, TEXT("Block %d landed! Score: %d"), BlockCount, Score);
	SpawnNextBlock();
}

void AStackingGameMode::OnBlockFell()
{
	bGameOver = true;
	CurrentBlock = nullptr;

	UE_LOG(LogTemp, Warning, TEXT("Game Over! Final Score: %d (Blocks: %d)"), Score, BlockCount);
}

void AStackingGameMode::RestartGame()
{
	if (!bGameOver)
	{
		return;
	}
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
}

void AStackingGameMode::UpdateCamera(float DeltaTime)
{
	if (!GameCamera)
	{
		return;
	}

	float StackHeight = GetStackTopZ();
	if (StackHeight > CameraHeightThreshold)
	{
		float TargetZ = StackHeight - CameraHeightThreshold + InitialCameraZ;
		FVector CamLoc = GameCamera->GetActorLocation();
		CamLoc.Z = FMath::FInterpTo(CamLoc.Z, TargetZ, DeltaTime, CameraInterpSpeed);
		GameCamera->SetActorLocation(CamLoc);
	}
}

float AStackingGameMode::GetCurrentMoveSpeed() const
{
	return BaseMoveSpeed + (BlockCount * SpeedIncrement);
}

float AStackingGameMode::GetStackTopZ() const
{
	if (StackedBlocks.Num() == 0)
	{
		return 0.f;
	}
	return StackedBlocks.Last()->GetTopZ();
}
