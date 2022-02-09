// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class fpstest : ModuleRules
{
	public fpstest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay",
			"MediaAssets",
			"Slate",
			"DesktopPlatform",
			"QuestSystem",
		});
	}
}
