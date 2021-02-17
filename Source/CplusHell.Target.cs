// C plus Hell Learning Game, All Right Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CplusHellTarget : TargetRules
{
	public CplusHellTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "CplusHell" } );
	}
}
