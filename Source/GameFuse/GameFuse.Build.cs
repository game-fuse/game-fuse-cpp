/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

using UnrealBuildTool;

public class GameFuse : ModuleRules {
	public GameFuse(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(
			new[] {
				"Core",
				"CoreUObject",
				"HTTP",
				"Json",
				"JsonUtilities",
				"Engine",
				"Slate",
				"SlateCore"
			}
		);
	}
}