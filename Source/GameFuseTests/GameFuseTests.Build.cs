using UnrealBuildTool;

public class GameFuseTests : ModuleRules {
	public GameFuseTests(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[] {
				"Core", "GameFuse", "Json", "JsonUtilities"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[] {
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
			}
		);
	}
}