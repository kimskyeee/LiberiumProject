// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LiberiumWidgetBase.generated.h"

class ULiberiumViewModelBase;

UCLASS(Abstract)
class LIBERIUMPROJRCT_API ULiberiumWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ViewModel")
	void SetViewModel(ULiberiumViewModelBase* InViewModel);

	UFUNCTION(BlueprintCallable, Category = "ViewModel")
	ULiberiumViewModelBase* GetViewModel() const { return ViewModel; }

protected:
	virtual void BindViewModel();
	virtual void UnbindViewModel();

	UPROPERTY(BlueprintReadOnly, Category = "ViewModel")
	TObjectPtr<ULiberiumViewModelBase> ViewModel;
};
