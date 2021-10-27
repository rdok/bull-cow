using UnrealBuildTool;
using System.Collections.Generic;

public class PioneerEditorTarget : TargetRules
{
	public PioneerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Pioneer" } );
	}
}
