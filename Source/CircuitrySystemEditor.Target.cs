// Copyright 2023 by Pace Abbott. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CircuitrySystemEditorTarget : TargetRules
{
	public CircuitrySystemEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("CircuitrySystem");
	}
}
