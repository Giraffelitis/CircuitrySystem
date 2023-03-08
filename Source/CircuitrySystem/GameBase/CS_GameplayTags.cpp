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
	AddTag(InputTag_Crouch_Pressed, "InputTag.Crouch.Pressed", "Start Crouch");
	AddTag(InputTag_Crouch_Released, "InputTag.Crouch.Released", "End Crouch");
	
	AddTag(InputTag_Interaction_RotatePos, "InputTag.Interaction.Rotate.Positive", "Increase held object rotation");
	AddTag( InputTag_Interaction_RotateNeg, "InputTag.Interaction.Rotate.Negative", "Decrease held object rotation");
	AddTag( InputTag_Interaction_Pickup, "InputTag.Interaction.Pickup", "Pickup Object");

	AddTag( InputTag_Build_ToggleBuild, "InputTag.Build.Toggle", "Toggle Build Mode");
	AddTag( InputTag_Build_SpawnComponent, "InputTag.Build.Component.Spawn", "Spawn selected component");
	AddTag( InputTag_Build_DestroyComponent, "InputTag.Build.Component.Destroy", "Destroy targeted component");

	AddTag( InputTag_MouseWheel_Up, "InputTag.Modifier.MouseWheel.Up", "MouseWheel Up input");
	AddTag( InputTag_MouseWheel_Down, "InputTag.Modifier.MouseWheel.Down", "MouseWheel Down input");
	AddTag( InputTag_Modifier_Alt_Pressed, "InputTag.Modifier.Alt.Pressed", "Input Modifier Alt Pressed");
	AddTag( InputTag_Modifier_Alt_Released, "InputTag.Modifier.Alt.Released", "Input Modifier Alt Pressed");
	AddTag( InputTag_Modifier_Ctrl_Pressed, "InputTag.Modifier.Ctrl.Pressed", "Input Modifier Ctrl Pressed");
	AddTag( InputTag_Modifier_Ctrl_Released, "InputTag.Modifier.Ctrl.Released", "Input Modifier Ctrl Pressed");
	AddTag( InputTag_Modifier_Shift_Pressed, "InputTag.Modifier.Shift.Pressed", "Input Modifier Shift Pressed");
	AddTag( InputTag_Modifier_Shift_Released, "InputTag.Modifier.Shift.Released", "Input Modifier Shift Pressed");

	AddTag(BuildTag_Player_Private,"BuildTag.Player.Private","Build tag player built private");
	AddTag(BuildTag_Player_Public,"BuildTag.Player.Public","Build tag player built public");}

void FCS_GameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}