// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_GameplayTags.h"
#include "GameplayTagsManager.h"

FCS_GameplayTags FCS_GameplayTags::GameplayTags;

void FCS_GameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(GameplayTagsManager);

	GameplayTagsManager.DoneAddingNativeTags();
}

//Add Tags for the editor here.
//AddTag(TagFName, "TagHierarchyName", "TagDescription");
//@TagFName is used on C++ side to assign bindings
//@TagHierarchyName is used on editor side to identify tag and build Hierarchy
//@TagDescription is used by editor to help define tag further if needed

// Changes made here require engine reboot to update in the editor	

void FCS_GameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	AddTag(InputTag_Move, "InputTag.Move", "Move input.");
	AddTag(InputTag_Look_Mouse, "InputTag.Look.Mouse", "Look (mouse) input.");
	AddTag(InputTag_Look_Stick, "InputTag.Look.Stick", "Look (stick) input.");
	AddTag(InputTag_Jump, "InputTag.Jump", "Jump input");
	AddTag(InputTag_Pickup, "InputTag.Pickup", "Pickup input.");
}

void FCS_GameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}