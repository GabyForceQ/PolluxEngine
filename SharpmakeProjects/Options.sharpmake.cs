using Sharpmake;
using System.Collections.Generic;
using System.IO;

public static class Options
{
    public static string RootPath = Util.PathMakeStandard(Path.GetFullPath(
        Path.Combine(Util.GetCurrentSharpmakeFileInfo().DirectoryName, "..")));

    public static string ExternPath = Path.Combine(RootPath, "Extern");

    public static string BuildPath = Path.Combine(RootPath, "Build");

    public static string TempPath = Path.Combine(BuildPath, "Temp");
    public static string LibPath = Path.Combine(BuildPath, "Lib");
    public static string NuGetPackagesPath = Path.Combine(TempPath, "Nuget");
    public static string OutputPath = Path.Combine(BuildPath, "Output");
    public static string ProjectsPath = Path.Combine(BuildPath, "Projects");

    public static Dictionary<string, string> ExternalNuGetPackages = new Dictionary<string, string>();

    // Global NuGet feeds to use
    public static string[] NuGetFeeds =
    {
        "https://artifactory.ubisoft.org/api/nuget/nuget",
        "https://artifactory.ubisoft.org/api/nuget/nuget-playground",
        "https://artifactory.ubisoft.org/api/nuget/nuget-snapshot"
    };

    public static string GetProjectPath(Target target)
    {
        return Path.Combine(ProjectsPath, GetPlatformDevEnvPath(target));
    }

    public static string GetTargetPath(Target target)
    {
        return Path.Combine(Options.OutputPath,
            string.Format("{0}_{1}", GetPlatformDevEnvPath(target), GetOptimizationModeOutputTypeFolderName(target)));
    }

    public static string GetIntermediatePath(Target target)
    {
        return Path.Combine(Options.TempPath,
            "Obj",
            GetPlatformDevEnvPath(target),
            "[project.Name]",
            GetOptimizationModeOutputTypeFolderName(target));
    }

    private static string GetPlatformDevEnvPath(Target target)
    {
        string devEnvPath = string.Format("{0}_{1}", target.Platform, target.DevEnv);
        return devEnvPath;
    }

    private static string GetOptimizationModeOutputTypeFolderName(Target target)
    {
        return string.Format("{0}{1}",
                target.Optimization,
                ToPathExtension(target.OutputType));
    }

    private static string ToPathExtension(OutputType outputType)
    {
        switch (outputType)
        {
            case OutputType.Dll:
                return "_dll";
            case OutputType.Lib:
                return string.Empty;
            default:
                throw new Error("Unknown OutputType type");
        }
    }
}