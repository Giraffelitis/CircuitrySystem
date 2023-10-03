// Copyright 2023 by Pace Abbott. All Rights Reserved.

using UnrealBuildTool;

public class CircuitrySystem : ModuleRules
{
	public CircuitrySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"UMG", 
			"GameplayTags", 
			"EnhancedInput", 
			"PhysicsCore",
			"CableComponent"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "CableComponent" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
