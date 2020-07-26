using Sharpmake;

[module: Sharpmake.Include("Options.sharpmake.cs")]
[module: Sharpmake.Include("Engine.sharpmake.cs")]
[module: Sharpmake.Include("EngineBuilder.sharpmake.cs")]
[module: Sharpmake.Include("Editor.sharpmake.cs")]
[module: Sharpmake.Include("Test.sharpmake.cs")]

[Generate]
public class PolluxSolution : Solution
{
    public PolluxSolution()
    {
        IsFileNameToLower = false;
        Name = "PolluxEngine";

        AddTargets(new Target(
            Platform.win64,
            DevEnv.vs2019,
            Optimization.Debug | Optimization.Release));
    }

    [Configure]
    public void ConfigureAll(Configuration conf, Target target)
    {
        conf.SolutionPath = Options.GetProjectPath(target);

        conf.AddProject<Editor>(target);
        conf.AddProject<EngineBuilder>(target);
        conf.AddProject<Test>(target);
    }
}
