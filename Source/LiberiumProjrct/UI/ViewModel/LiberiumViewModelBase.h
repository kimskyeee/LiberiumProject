// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LiberiumViewModelBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnViewModelUpdated);

UCLASS(Abstract, BlueprintType)
class LIBERIUMPROJRCT_API ULiberiumViewModelBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "ViewModel")
	FOnViewModelUpdated OnViewModelUpdated;

	virtual void Initialize(UWorld* InWorld);
	virtual void Deinitialize();

protected:
	void BroadcastUpdate();

	UPROPERTY()
	TWeakObjectPtr<UWorld> WorldContext;
};
