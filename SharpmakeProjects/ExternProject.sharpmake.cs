using Sharpmake;

[module: Sharpmake.Include("BaseProject.sharpmake.cs")]

public abstract class ExternProject : BaseProject
{
    public override string ProjectFolder
    {
        get { return "Extern"; }
    }

    protected ExternProject() : base()
    {
    }

    public override void ConfigureWin64(Configuration conf, Target target)
    {
        base.ConfigureWin64(conf, target);

        if (target.Optimization == Optimization.Debug)
        {
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.Optimization.MaximizeSpeed);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.StringPooling.Enable);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeChecks.Default);
        }
    }
}
