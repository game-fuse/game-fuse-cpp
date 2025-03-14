using UnrealBuildTool;

public class GameFuseTests : ModuleRules {
	public GameFuseTests(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[] {
				"Core", 
				"GameFuse", 
				"Json", 
				"JsonUtilities",
				"HTTP"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[] {
				"CoreUObject",
				"Engine",
				"UnrealEd",
				"Slate",
				"SlateCore",
				"FunctionalTesting"
			}
		);

		// This is required for automation tests
		bTreatAsEngineModule = true;
		bUseUnity = false;
	}
}