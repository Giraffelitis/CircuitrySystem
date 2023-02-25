// Copyright 2023 by Pace Abbott. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CircuitrySystemTarget : TargetRules
{
	public CircuitrySystemTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("CircuitrySystem");
	}
}
