using System.IO;
using Sharpmake;

[module: Sharpmake.Include("BaseProject.sharpmake.cs")]
[module: Sharpmake.Include("Engine.sharpmake.cs")]

[Generate]
public class EngineBuilder : BaseProject
{
    public string ProjectRootPath
    {
        get { return Path.Combine(Options.RootPath, "EngineBuilder"); }
    }

    public override string ProjectFolder
    {
        get { return ""; }
    }

    public override string TargetFileName
    {
        get { return "[project.Name]_[target.Optimization]"; }
    }

    public EngineBuilder() : base()
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

        conf.PrecompHeader = "EngineBuilder/enginebuilderpch.hpp";
        conf.PrecompSource = "EngineBuilder/enginebuilderpch.cpp";

        conf.AddPublicDependency<Engine>(target);

        conf.Output = Configuration.OutputType.Exe;

        conf.VcxprojUserFile = new Configuration.VcxprojUserFileSettings();
        conf.VcxprojUserFile.LocalDebuggerWorkingDirectory = Options.RootPath;
    }
}