// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StackBlock.generated.h"

UENUM(BlueprintType)
enum class EStackBlockState : uint8
{
	Idle,
	Moving,
	Dropping,
	Landed,
	Falling
};

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class LIBERIUMPROJRCT_API AStackBlock : public AActor
{
	GENERATED_BODY()

public:
	AStackBlock();
	virtual void Tick(float DeltaTime) override;

	void StartMoving(float Speed, float InLeftBound, float InRightBound, float InTargetLandingZ, float InReferenceX);
	void Drop();
	void StartFalling(float Direction);

	FORCEINLINE EStackBlockState GetBlockState() const { return BlockState; }
	float GetTopZ() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block")
	float BlockWidth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block")
	float BlockHeight = 40.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block")
	float DropSpeed = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block")
	float OverlapTolerance = 0.5f;

	DECLARE_DELEGATE_OneParam(FOnLanded, AStackBlock*);
	DECLARE_DELEGATE(FOnFell);
	FOnLanded OnLanded;
	FOnFell OnFell;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BlockMesh;

private:
	EStackBlockState BlockState = EStackBlockState::Idle;
	float MoveSpeed = 200.f;
	float MoveDirection = 1.f;
	float LeftBoundary = -300.f;
	float RightBoundary = 300.f;
	float TargetLandingZ = 0.f;
	float ReferenceX = 0.f;
	float FallTimer = 0.f;
	float TiltDirection = 1.f;

	void TickMoving(float DeltaTime);
	void TickDropping(float DeltaTime);
	void TickFalling(float DeltaTime);
};
