// Copyright LiberiumProject. All Rights Reserved.

#include "LiberiumProjrct/UI/View/LiberiumWidgetBase.h"
#include "LiberiumProjrct/UI/ViewModel/LiberiumViewModelBase.h"

void ULiberiumWidgetBase::SetViewModel(ULiberiumViewModelBase* InViewModel)
{
	if (ViewModel)
	{
		UnbindViewModel();
	}

	ViewModel = InViewModel;

	if (ViewModel)
	{
		BindViewModel();
	}
}

void ULiberiumWidgetBase::BindViewModel()
{
}

void ULiberiumWidgetBase::UnbindViewModel()
{
}
