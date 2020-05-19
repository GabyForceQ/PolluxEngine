using Sharpmake;
using System;
using System.Collections.Generic;
using Newtonsoft.Json;
using System.IO;

[module: Sharpmake.Include("PolluxSolution.sharpmake.cs")]

[module: Sharpmake.Reference("Sharpmake.NuGet.dll")]
[module: Sharpmake.NuGet.Reference("Newtonsoft.Json", "12.0.2")]

public static class Main
{
    private static Dictionary<string, string> ExternalNuGetPackagesInstallation = new Dictionary<string, string>();

    [Sharpmake.Main]
    public static void SharpmakeMain(Arguments arguments)
    {
        AddExternalPackages();
        ConfigureSourcePackages();

        arguments.Generate<PolluxSolution>();
    }

    public static string GetExternalSourcePackageRootPath(string packageName)
    {
        if (!Options.ExternalNuGetPackages.ContainsKey(packageName))
        {
            throw new Error("The package named: " + packageName + " is unsupported or has the wrong spelling.");
        }

        string packageInstallLocation;

        lock (ExternalNuGetPackagesInstallation)
        {
            if (!ExternalNuGetPackagesInstallation.TryGetValue(packageName, out packageInstallLocation))
            {
                InstallSourcePackage(packageName);

                if (!ExternalNuGetPackagesInstallation.TryGetValue(packageName, out packageInstallLocation))
                {
                    throw new Error("The package named: " + packageName + " failed to be installed.");
                }
            }
        }

        return Path.Combine(packageInstallLocation, "build", "native");
    }

    private static void InstallSourcePackage(string packageName)
    {
        string packageVersion;
        if (!Options.ExternalNuGetPackages.TryGetValue(packageName, out packageVersion))
        {
            Builder.Instance.LogErrorLine("The package named: " + packageName + " is unsupported or has the wrong spelling.");
            return;
        }

        InstallSourcePackage(packageName, packageVersion);
    }

    private static void InstallSourcePackage(string packageName, string packageVersion)
    {
        ExternalNuGetPackagesInstallation[packageName] = NuGet.InstallPackage(packageName, packageVersion);

        if (string.IsNullOrEmpty(ExternalNuGetPackagesInstallation[packageName]))
        {
            Builder.Instance.LogErrorLine("Failed to install " + packageName + " NuGet package");
        }
    }

    private class ExternalPackage
    {
        public string Name { get; set; }
        public string Version { get; set; }
    }

    private static List<ExternalPackage> ReadJsonFile(string filePath)
    {
        try
        {
            var jsonString = File.ReadAllText(filePath);
            return JsonConvert.DeserializeObject<List<ExternalPackage>>(jsonString);
        }
        catch (Exception ex)
        {
            throw new Error("Error reading json file '{0}' got exception {1}", filePath, ex);
        }
    }

    private static void AddExternalPackages()
    {
        string configFilePath = Util.GetCurrentSharpmakeFileInfo().DirectoryName + "/project_dependencies.json";
        var jsonDependenciesData = ReadJsonFile(configFilePath);
        if (jsonDependenciesData != null)
        {
            foreach (var jsonDependencyData in jsonDependenciesData)
            {
                Options.ExternalNuGetPackages.Add(jsonDependencyData.Name, jsonDependencyData.Version);
            }
        }
        else
        {
            Console.WriteLine("The config file '{0}' was empty.", configFilePath);
        }
    }

    private static void ConfigureSourcePackages()
    {
        // NuGet Initialization of NuGet feeds.
        NuGet.GlobalSettings.NuGetSources.AddRange(Options.NuGetFeeds);
        NuGet.GlobalSettings.DirectDownloadInstallPath = Options.NuGetPackagesPath;
        NuGet.GlobalSettings.UseDirectDownload = true;
    }
}