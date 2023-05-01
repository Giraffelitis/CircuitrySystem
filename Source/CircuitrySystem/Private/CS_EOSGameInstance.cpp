// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_EOSGameInstance.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"

UCS_EOSGameInstance::UCS_EOSGameInstance()
{
	bIsLoggedIn = false;
}

void UCS_EOSGameInstance::Init()
{
	Super::Init();

	OnlineSubsystem = IOnlineSubsystem::Get();
}

void UCS_EOSGameInstance::Login()
{
	if(OnlineSubsystem)
	{
		if(IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			FOnlineAccountCredentials Credentials;
			Credentials.Id = FString("127.0.0.1:8081");
			Credentials.Token = FString("FutureSurvival");
			Credentials.Type = FString("developer");

			Identity->OnLoginCompleteDelegates->AddUObject(this, &UCS_EOSGameInstance::OnLoginComplete);
			Identity->Login(0, Credentials);
		}
	}
}

void UCS_EOSGameInstance::OnLoginComplete(int32 InLocalUserNum, bool InbWasSuccessful, const FUniqueNetId& InUserId, const FString& InError)
{
	UE_LOG(LogTemp, Warning, TEXT("UCS Logged In Success: %d"), InbWasSuccessful)
	bIsLoggedIn = InbWasSuccessful;
	
	if(OnlineSubsystem)
	{
		if(IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			Identity->ClearOnLoginCompleteDelegates(0, this);
		}
	}
	
}

void UCS_EOSGameInstance::CreateSession()
{
	if(bIsLoggedIn)
	{
		if(OnlineSubsystem)
		{
			if(IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				FOnlineSessionSettings SessionSettings;
				SessionSettings.bIsDedicated = false;
				SessionSettings.bShouldAdvertise = true;
				SessionSettings.bIsLANMatch = false;
				SessionSettings.NumPublicConnections = 5;
				SessionSettings.bAllowJoinInProgress = true;
				SessionSettings.bAllowJoinViaPresence = true;
				SessionSettings.bUsesPresence = true;
				SessionSettings.bUseLobbiesIfAvailable = true;
				
				SessionSettings.Set(SEARCH_KEYWORDS, FString("FutureSurvivalLobby"), EOnlineDataAdvertisementType::ViaOnlineService);
			
				SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UCS_EOSGameInstance::OnCreateSessionComplete);
			
				SessionPtr->CreateSession(0, UCSSessionName, SessionSettings);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session user not logged in"))
	}
}

void UCS_EOSGameInstance::OnCreateSessionComplete(FName InSessionName, bool InbWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("UCS Create Online Session Success: %d"), InbWasSuccessful)

	if(OnlineSubsystem)
	{
		if(IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnCreateSessionCompleteDelegates(this);
		}
	}
}

void UCS_EOSGameInstance::DestroySession()
{
	if(bIsLoggedIn)
	{
		if(OnlineSubsystem)
		{
			if(IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				SessionPtr->OnDestroySessionCompleteDelegates.AddUObject(this, &UCS_EOSGameInstance::OnDestroySessionComplete);
				SessionPtr->DestroySession(UCSSessionName);
			}
		}
	}
}

void UCS_EOSGameInstance::OnDestroySessionComplete(FName InSessionName, bool InbWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("UCS Destroy Online Session Success: %d"), InbWasSuccessful)

	if(OnlineSubsystem)
	{
		if(IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnDestroySessionCompleteDelegates(this);
		}
	}
}
