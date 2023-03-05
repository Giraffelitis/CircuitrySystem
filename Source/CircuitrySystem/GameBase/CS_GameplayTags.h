// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;
/**
 * CS_GameplayTags
 *
 *	Singleton containing native gameplay tags.
 */

struct FCS_GameplayTags
{

	static const FCS_GameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

	//Input Tags
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look_Mouse;
	FGameplayTag InputTag_Look_Stick;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Crouch_Pressed;	
	FGameplayTag InputTag_Crouch_Released;
	
	FGameplayTag InputTag_Interaction_RotatePos;
	FGameplayTag InputTag_Interaction_RotateNeg;
	FGameplayTag InputTag_Interaction_Pickup;
	
	FGameplayTag InputTag_Build_ToggleBuild;
	FGameplayTag InputTag_Build_SpawnComponent;
	FGameplayTag InputTag_Build_DestroyComponent;
	
	FGameplayTag InputTag_MouseWheel_Up;
	FGameplayTag InputTag_MouseWheel_Down;
	FGameplayTag InputTag_Modifier_Alt_Pressed;
	FGameplayTag InputTag_Modifier_Alt_Released;
	FGameplayTag InputTag_Modifier_Ctrl_Pressed;
	FGameplayTag InputTag_Modifier_Ctrl_Released;
	FGameplayTag InputTag_Modifier_Shift_Pressed;
	FGameplayTag InputTag_Modifier_Shift_Released;	

protected:

	//Registers all of the tags with the GameplayTags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FCS_GameplayTags GameplayTags;
};