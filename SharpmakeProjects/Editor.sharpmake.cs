using System.IO;
using Sharpmake;

[module: Sharpmake.Include("BaseProject.sharpmake.cs")]
[module: Sharpmake.Include("Engine.sharpmake.cs")]

[Generate]
public class Editor : BaseProject
{
    public string ProjectRootPath
    {
        get { return Path.Combine(Options.RootPath, "Editor"); }
    }

    public override string ProjectFolder
    {
        get { return ""; }
    }

    public override string TargetFileName
    {
        get { return "[project.Name]_[target.Optimization]"; }
    }

    public Editor() : base()
    {
        SourceRootPath = ProjectRootPath;

        AddTargets(new Target(
            Platform.win64,
            DevEnv.vs2019,
            Optimization.Debug | Optimization.Release));
    }

    public override void ConfigureAll(Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        conf.PrecompHeader = "Editor/editorpch.hpp";
        conf.PrecompSource = "Editor/editorpch.cpp";

        conf.AddPublicDependency<Engine>(target);

        conf.Output = Configuration.OutputType.Exe;
        conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.Latest); // CPP20

        conf.VcxprojUserFile = new Configuration.VcxprojUserFileSettings();
        conf.VcxprojUserFile.LocalDebuggerWorkingDirectory = Options.RootPath;

        conf.Defines.Add("POLLUX_PLATFORM_X64");
        conf.Defines.Add("POLLUX_WITH_EDITOR");

        switch (target.Optimization)
        {
            case Optimization.Debug:
                conf.Defines.Add("POLLUX_TARGET_DEBUG");
                break;
            case Optimization.Release:
                conf.Defines.Add("POLLUX_TARGET_RELEASE");
                break;
            default:
                break;
        }

        conf.LibraryFiles.Add("Iphlpapi.lib");
        conf.LibraryFiles.Add("Shlwapi.lib");
    }
}