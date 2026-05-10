// Copyright LiberiumProject. All Rights Reserved.

#include "LiberiumProjrct/Minigame/StackGame/StackBlock.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AStackBlock::AStackBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	BoxCollision->SetBoxExtent(FVector(50.f, 10.f, 20.f));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	BlockMesh->SetupAttachment(RootComponent);
	BlockMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
	if (CubeMesh.Succeeded())
	{
		BlockMesh->SetStaticMesh(CubeMesh.Object);
	}
}

void AStackBlock::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->SetBoxExtent(FVector(BlockWidth * 0.5f, 10.f, BlockHeight * 0.5f));
	BlockMesh->SetRelativeScale3D(FVector(BlockWidth / 100.f, 0.2f, BlockHeight / 100.f));

	UMaterialInterface* BaseMat = BlockMesh->GetMaterial(0);
	if (BaseMat)
	{
		UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(BaseMat, this);
		FLinearColor Color = FLinearColor::MakeRandomColor();
		Color.A = 1.f;
		DynMat->SetVectorParameterValue(TEXT("BaseColor"), Color);
		BlockMesh->SetMaterial(0, DynMat);
	}
}

void AStackBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (BlockState)
	{
	case EStackBlockState::Moving:
		TickMoving(DeltaTime);
		break;
	case EStackBlockState::Dropping:
		TickDropping(DeltaTime);
		break;
	case EStackBlockState::Falling:
		TickFalling(DeltaTime);
		break;
	default:
		break;
	}
}

void AStackBlock::StartMoving(float Speed, float InLeftBound, float InRightBound, float InTargetLandingZ, float InReferenceX)
{
	MoveSpeed = Speed;
	LeftBoundary = InLeftBound;
	RightBoundary = InRightBound;
	TargetLandingZ = InTargetLandingZ;
	ReferenceX = InReferenceX;
	MoveDirection = 1.f;
	BlockState = EStackBlockState::Moving;
}

void AStackBlock::Drop()
{
	if (BlockState != EStackBlockState::Moving)
	{
		return;
	}
	BlockState = EStackBlockState::Dropping;
}

void AStackBlock::StartFalling(float Direction)
{
	TiltDirection = Direction;
	FallTimer = 0.f;
	BlockState = EStackBlockState::Falling;
	SetActorTickEnabled(true);
}

float AStackBlock::GetTopZ() const
{
	return GetActorLocation().Z + BlockHeight * 0.5f;
}

void AStackBlock::TickMoving(float DeltaTime)
{
	FVector Loc = GetActorLocation();
	Loc.X += MoveSpeed * MoveDirection * DeltaTime;

	if (Loc.X >= RightBoundary)
	{
		Loc.X = RightBoundary;
		MoveDirection = -1.f;
	}
	else if (Loc.X <= LeftBoundary)
	{
		Loc.X = LeftBoundary;
		MoveDirection = 1.f;
	}

	SetActorLocation(Loc);
}

void AStackBlock::TickDropping(float DeltaTime)
{
	FVector Loc = GetActorLocation();
	Loc.Z -= DropSpeed * DeltaTime;

	if (Loc.Z <= TargetLandingZ)
	{
		Loc.Z = TargetLandingZ;
		SetActorLocation(Loc);

		float OffsetX = FMath::Abs(Loc.X - ReferenceX);
		float MaxOffset = BlockWidth * OverlapTolerance;

		if (OffsetX <= MaxOffset)
		{
			BlockState = EStackBlockState::Landed;
			SetActorTickEnabled(false);
			OnLanded.ExecuteIfBound(this);
		}
		else
		{
			TiltDirection = (Loc.X > ReferenceX) ? 1.f : -1.f;
			FallTimer = 0.f;
			BlockState = EStackBlockState::Falling;
			OnFell.ExecuteIfBound();
		}
	}
	else
	{
		SetActorLocation(Loc);
	}
}

void AStackBlock::TickFalling(float DeltaTime)
{
	FallTimer += DeltaTime;

	FVector Loc = GetActorLocation();
	Loc.X += TiltDirection * 100.f * DeltaTime;
	Loc.Z -= 500.f * FallTimer;

	FRotator Rot = GetActorRotation();
	Rot.Pitch += TiltDirection * 200.f * DeltaTime;

	SetActorLocation(Loc);
	SetActorRotation(Rot);

	if (FallTimer > 3.f)
	{
		Destroy();
	}
}
