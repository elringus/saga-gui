namespace UnrealBuildTool.Rules
{
	public class SGUI : ModuleRules
	{
		public SGUI (TargetInfo Target)
		{
			PublicIncludePaths.AddRange(new string[] { "SGUI/Public" });
			PrivateIncludePaths.AddRange(new string[] { "SGUI/Private" });
			PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore", "Http" });
			PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
			DynamicallyLoadedModuleNames.AddRange(new string[] { /* ... add any modules that your module loads dynamically here ... */ });
		}
	}
}