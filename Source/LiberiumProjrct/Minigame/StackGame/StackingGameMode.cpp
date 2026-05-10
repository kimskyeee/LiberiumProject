// Copyright LiberiumProject. All Rights Reserved.

#include "StackingGameMode.h"

#include "AITestsCommon.h"
#include "StackingPlayerController.h"
#include "LiberiumProjrct/Minigame/StackGame/StackBlock.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

AStackingGameMode::AStackingGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = APawn::StaticClass();
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

	if (bCollapsing)
	{
		TickCollapse(DeltaTime);
	}

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
	if (bGameOver || bCollapsing || !CurrentBlock)
	{
		return;
	}
	CurrentBlock->Drop();
}

void AStackingGameMode::OnBlockLanded(AStackBlock* Block)
{
	StackedBlocks.Add(Block);
	CurrentBlock = nullptr;

	if (!IsStackStable())
	{
		UE_LOG(LogTemp, Warning, TEXT("Stack collapsed! Center of mass outside support base."));
		StartCollapse();
		return;
	}

	BlockCount++;
	Score += 1;

	if (BlockCount % 10 == 0)
	{
		Score += 3;
	}

	UE_LOG(LogTemp, Log, TEXT("Block %d landed! Score: %d (CoM X: %.1f)"), BlockCount, Score, CalcCenterOfMassX());
	SpawnNextBlock();
}

void AStackingGameMode::OnBlockFell()
{
	bGameOver = true;
	CurrentBlock = nullptr;

	UE_LOG(LogTemp, Warning, TEXT("Game Over! Final Score: %d (Blocks: %d)"), Score, BlockCount);
}

void AStackingGameMode::StartCollapse()
{
	bCollapsing = true;
	CurrentBlock = nullptr;
	CollapseTimer = 0.f;

	float CoMX = CalcCenterOfMassX();
	float BaseX = StackedBlocks[0]->GetActorLocation().X;
	CollapseDirection = (CoMX > BaseX) ? 1.f : -1.f;

	// Start from top block
	NextCollapseIndex = StackedBlocks.Num() - 1;

	UE_LOG(LogTemp, Warning, TEXT("Stack collapsing! Direction: %s"), CollapseDirection > 0.f ? TEXT("Right") : TEXT("Left"));
}

void AStackingGameMode::TickCollapse(float DeltaTime)
{
	CollapseTimer += DeltaTime;

	if (CollapseTimer >= CascadeDelay && NextCollapseIndex > 0)
	{
		StackedBlocks[NextCollapseIndex]->StartFalling(CollapseDirection);
		NextCollapseIndex--;
		CollapseTimer = 0.f;

		if (NextCollapseIndex <= 0)
		{
			bCollapsing = false;
			bGameOver = true;
			UE_LOG(LogTemp, Warning, TEXT("Game Over! Final Score: %d (Blocks: %d)"), Score, BlockCount);
		}
	}
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

float AStackingGameMode::CalcCenterOfMassX() const
{
	if (StackedBlocks.Num() == 0)
	{
		return 0.f;
	}

	float SumX = 0.f;
	for (const auto& Block : StackedBlocks)
	{
		SumX += Block->GetActorLocation().X;
	}
	return SumX / StackedBlocks.Num();
}

bool AStackingGameMode::IsStackStable() const
{
	if (StackedBlocks.Num() <= 1)
	{
		return true;
	}

	float HalfWidth = BlockWidth * 0.5f;
	float SupportLeft = StackedBlocks[0]->GetActorLocation().X - HalfWidth;
	float SupportRight = StackedBlocks[0]->GetActorLocation().X + HalfWidth;

	for (int32 i = 1; i < StackedBlocks.Num(); i++)
	{
		float BlockX = StackedBlocks[i]->GetActorLocation().X;
		float BlockLeft = BlockX - HalfWidth;
		float BlockRight = BlockX + HalfWidth;

		float OverlapLeft = FMath::Max(BlockLeft, SupportLeft);
		float OverlapRight = FMath::Min(BlockRight, SupportRight);
		float OverlapWidth = OverlapRight - OverlapLeft;

		if (OverlapWidth < BlockWidth * MinSupportRatio)
		{
			UE_LOG(LogTemp, Warning, TEXT("Layer %d: support %.1f < min %.1f"), i, OverlapWidth, BlockWidth * MinSupportRatio);
			return false;
		}

		SupportLeft = OverlapLeft;
		SupportRight = OverlapRight;
	}
	return true;
}
