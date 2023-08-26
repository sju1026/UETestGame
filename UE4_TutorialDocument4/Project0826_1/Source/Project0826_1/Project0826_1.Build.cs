// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project0826_1 : ModuleRules
{
	public Project0826_1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
