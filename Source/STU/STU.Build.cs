// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class STU : ModuleRules
{
	public STU(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{	
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
            "Niagara",
			"PhysicsCore",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem"
        });

		PublicIncludePaths.AddRange(new string[]
		{
			"STU/Player",
			"STU/Weapons",
            "STU/Weapons/Components",
            "STU/UI",
			"STU/Anims",
			"STU/Components",
			"STU/Menu",
			"STU/Menu/UI",
			"STU/AI",
			"STU/AI/Tasks",
			"STU/AI/Services",
			"STU/AI/Context",
			"STU/AI/Decorators",
			"STU/AI/Tests",
			"STU/PickUps",
			"STU/Sound"
			
		});
	}
}
