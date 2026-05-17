// Copyright LiberiumProject. All Rights Reserved.

#include "UI/ViewModel/LiberiumViewModelBase.h"

void ULiberiumViewModelBase::Initialize(UWorld* InWorld)
{
	WorldContext = InWorld;
}

void ULiberiumViewModelBase::Deinitialize()
{
	WorldContext = nullptr;
}

void ULiberiumViewModelBase::BroadcastUpdate()
{
	OnViewModelUpdated.Broadcast();
}
