// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class VolumeMeshPlugin : ModuleRules
{
	public VolumeMeshPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "marching_cubes", "include"),
				// ... add other private include paths required here ...
			}
			);
		var configuration = Target.Configuration == UnrealTargetConfiguration.Debug && Target.bDebugBuildsActuallyUseDebugCRT
		? "debug"
		: "release";
		PublicAdditionalLibraries.Add(
			Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "marching_cubes", "target", configuration, "libmc.a")
			);
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"ProceduralMeshComponent",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
