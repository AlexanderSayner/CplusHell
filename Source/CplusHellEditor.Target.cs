// C plus Hell Learning Game, All Right Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CplusHellEditorTarget : TargetRules
{
	public CplusHellEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "CplusHell" } );
	}
}
