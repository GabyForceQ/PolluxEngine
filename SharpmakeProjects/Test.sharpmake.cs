using System.IO;
using Sharpmake;

[module: Sharpmake.Include("BaseProject.sharpmake.cs")]
[module: Sharpmake.Include("Engine.sharpmake.cs")]

[Generate]
public class Test : BaseProject
{
    public string ProjectRootPath
    {
        get { return Path.Combine(Options.RootPath, "Test"); }
    }

    public override string ProjectFolder
    {
        get { return ""; }
    }

    public override string TargetFileName
    {
        get { return "[project.Name]_[target.Optimization]"; }
    }

    public Test() : base()
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

        conf.PrecompHeader = "Test/testpch.hpp";
        conf.PrecompSource = "Test/testpch.cpp";

        conf.AddPublicDependency<Engine>(target);

        conf.Output = Configuration.OutputType.Exe;

        conf.VcxprojUserFile = new Configuration.VcxprojUserFileSettings();
        conf.VcxprojUserFile.LocalDebuggerWorkingDirectory = Options.RootPath;

        conf.Defines.Add("POLLUX_TARGET_UNITTEST");
    }
}