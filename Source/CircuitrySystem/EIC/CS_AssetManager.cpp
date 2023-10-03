// Copyright 2023 by Pace Abbott. All Rights Reserved.

#include "CS_AssetManager.h"


UCS_AssetManager::UCS_AssetManager()
{

}

UCS_AssetManager& UCS_AssetManager::Get()
{
	check(GEngine);

	UCS_AssetManager* MyAssetManager = Cast<UCS_AssetManager>(GEngine->AssetManager);
	return *MyAssetManager;
}

void UCS_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

}