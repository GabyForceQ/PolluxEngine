using System.IO;
using Sharpmake;

[module: Sharpmake.Include("BaseProject.sharpmake.cs")]

[Generate]
public class Engine : BaseProject
{
    public string ProjectRootPath
    {
        get { return Path.Combine(Options.RootPath, "Engine"); }
    }

    public override string ProjectFolder
    {
        get { return ""; }
    }

    public override string TargetFileName
    {
        get { return "[project.Name]"; }
    }

    public Engine() : base()
    {
        SourceRootPath = ProjectRootPath;

        AddTargets(new Target(
            Platform.win64,
            DevEnv.vs2019,
            Optimization.Debug | Optimization.Release,
            OutputType.Lib));
    }

    public override void ConfigureAll(Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        conf.PrecompHeader = "Engine/enginepch.hpp";
        conf.PrecompSource = "Engine/enginepch.cpp";

        conf.Output = Configuration.OutputType.Lib;

        conf.IncludePaths.AddRange(new string[]
        {
            Path.Combine(Options.ExternPath, "SingleInclude")
        });
    }
}