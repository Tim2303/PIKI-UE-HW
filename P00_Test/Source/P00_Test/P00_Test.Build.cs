// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class P00_Test : ModuleRules
{
	public P00_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "AndroidRuntimeSettings" });

		PublicIncludePaths.AddRange(new string[] {
			"P00_Test",
			"P00_Test/Variant_Strategy",
			"P00_Test/Variant_Strategy/UI",
			"P00_Test/Variant_TwinStick",
			"P00_Test/Variant_TwinStick/AI",
			"P00_Test/Variant_TwinStick/Gameplay",
			"P00_Test/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
