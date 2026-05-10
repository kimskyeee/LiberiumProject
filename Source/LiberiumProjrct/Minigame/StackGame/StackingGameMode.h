// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LiberiumProjrct/Core/GameMode/LiberiumGameModeBase.h"
#include "StackingGameMode.generated.h"

class AStackBlock;
class ACameraActor;

UCLASS()
class LIBERIUMPROJRCT_API AStackingGameMode : public ALiberiumGameModeBase
{
	GENERATED_BODY()

public:
	AStackingGameMode();
	virtual void Tick(float DeltaTime) override;

	void DropCurrentBlock();
	void RestartGame();

	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetScore() const { return Score; }

	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetBlockCount() const { return BlockCount; }

	UFUNCTION(BlueprintCallable, Category = "Game")
	bool IsGameOver() const { return bGameOver; }

protected:
	virtual void BeginPlay() override;

	// Gameplay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float BaseMoveSpeed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float SpeedIncrement = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float BlockWidth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float BlockHeight = 40.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float MoveBoundaryLeft = -300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float MoveBoundaryRight = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float SpawnHeightOffset = 300.f;

	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraHeightThreshold = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraInterpSpeed = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraDistance = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraOrthoWidth = 1024.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float InitialCameraZ = 300.f;

	// Physics
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float CenterOfMassMargin = 0.3f;
	
private:
	UPROPERTY()
	TArray<TObjectPtr<AStackBlock>> StackedBlocks;

	UPROPERTY()
	TObjectPtr<AStackBlock> CurrentBlock;

	UPROPERTY()
	TObjectPtr<ACameraActor> GameCamera;

	int32 Score = 0;
	int32 BlockCount = 0;
	bool bGameOver = false;


	// Collapse
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (AllowPrivateAccess = "true"))
	float CascadeDelay = 0.08f;

	bool bCollapsing = false;
	float CollapseTimer = 0.f;
	int32 NextCollapseIndex = 0;
	float CollapseDirection = 1.f;

	void SpawnBaseBlock();
	void SpawnNextBlock();
	void OnBlockLanded(AStackBlock* Block);
	void OnBlockFell();
	void StartCollapse();
	void TickCollapse(float DeltaTime);
	void UpdateCamera(float DeltaTime);
	float GetCurrentMoveSpeed() const;
	float GetStackTopZ() const;
	float CalcCenterOfMassX() const;
	bool IsStackStable() const;
};
