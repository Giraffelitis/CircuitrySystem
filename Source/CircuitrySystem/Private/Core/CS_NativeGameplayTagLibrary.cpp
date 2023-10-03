#include "Core/CS_NativeGameplayTagLibrary.h"

namespace CS_NativeGameplayTagLibrary
{
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look_Mouse, "InputTag.Look.Mouse");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look_Stick, "InputTag.Look.Stick");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Crouch_Pressed, "InputTag.Crouch.Pressed");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Crouch_Released, "InputTag.Crouch.Released");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interaction_RotatePos, "InputTag.Interaction.Rotate.Positive");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interaction_RotateNeg, "InputTag.Interaction.Rotate.Negative");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interaction_Pickup, "InputTag.Interaction.Pickup");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interaction_Attach, "InputTag.Interaction.Attach");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Build_ToggleBuild, "InputTag.Build.Toggle");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Build_SpawnComponent, "InputTag.Build.Component.Spawn");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Build_DestroyComponent, "InputTag.Build.Component.Destroy");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_MouseWheel_Up, "InputTag.Modifier.MouseWheel.Up");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MouseWheel_Down, "InputTag.Modifier.MouseWheel.Down");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Modifier_Alt_Pressed, "InputTag.Modifier.Alt.Pressed");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Modifier_Alt_Released, "InputTag.Modifier.Alt.Released");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Modifier_Ctrl_Pressed, "InputTag.Modifier.Ctrl.Pressed");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Modifier_Ctrl_Released, "InputTag.Modifier.Ctrl.Released");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Modifier_Shift_Pressed, "InputTag.Modifier.Shift.Pressed");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Modifier_Shift_Released, "InputTag.Modifier.Shift.Released");

	UE_DEFINE_GAMEPLAY_TAG(BuildTag_Player_Private, "BuildTag.Player.Private");
	UE_DEFINE_GAMEPLAY_TAG(BuildTag_Player_Public, "BuildTag.Player.Public");

	UE_DEFINE_GAMEPLAY_TAG(ComponentTag_Circuit_Base, "ComponentTag.Circuit.Base");
	UE_DEFINE_GAMEPLAY_TAG(ComponentTag_Circuit_PowerBlock, "ComponentTag.Circuit.PowerBlock");
	UE_DEFINE_GAMEPLAY_TAG(ComponentTag_Circuit_LaserEmitter, "ComponentTag.Circuit.LaserEmitter");
	UE_DEFINE_GAMEPLAY_TAG(ComponentTag_Circuit_LaserReceiver, "ComponentTag.Circuit.LaserReceiver");
	UE_DEFINE_GAMEPLAY_TAG(ComponentTag_Circuit_PowerJumper, "ComponentTag.Circuit.PowerJumper");
	UE_DEFINE_GAMEPLAY_TAG(ComponentTag_Circuit_Switch, "ComponentTag.Circuit.Switch");

	UE_DEFINE_GAMEPLAY_TAG(ItemTag_Pickup_Socketable, "ItemTag.Pickup.Socketable");
	UE_DEFINE_GAMEPLAY_TAG(ItemTag_Pickup_PickedUp, "ItemTag.Pickup.PickedUp");
	UE_DEFINE_GAMEPLAY_TAG(ItemTag_Power_Receiver,"ItemTag.Power.Receiver");
	UE_DEFINE_GAMEPLAY_TAG(ItemTag_Power_Giver,"ItemTag.Power.Giver");
	UE_DEFINE_GAMEPLAY_TAG(ItemTag_Attach_Point,"ItemTag.Attach.Point");
	UE_DEFINE_GAMEPLAY_TAG(ItemTag_Attach_Used,"ItemTag.Attach.Used");
}