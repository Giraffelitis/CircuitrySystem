// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CS_EOSGameInstance.generated.h"

class IOnlineSubsystem;
/**
 * 
 */
UCLASS()
class CIRCUITRYSYSTEM_API UCS_EOSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCS_EOSGameInstance();
	virtual void Init() override;

	UFUNCTION(Exec, BlueprintCallable)
	void Login();
	void OnLoginComplete(int32 InLocalUserNum, bool InbWasSuccessful, const FUniqueNetId& InUserId, const FString& InError);

	UFUNCTION(Exec, BlueprintCallable)
	void CreateSession();
	void OnCreateSessionComplete(FName InSessionName, bool InbWasSuccessful);

	UFUNCTION(Exec, BlueprintCallable)
	void DestroySession();
	void OnDestroySessionComplete(FName InSessionName, bool InbWasSuccessful);

protected:
	IOnlineSubsystem* OnlineSubsystem;
	bool bIsLoggedIn;
	const FName UCSSessionName = FName("UCS_Test Session");
};
