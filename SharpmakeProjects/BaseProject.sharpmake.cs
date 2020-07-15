using System.IO;
using Sharpmake;

public abstract class BaseProject : Project
{
    public abstract string ProjectFolder { get; }
    public abstract string TargetFileName { get; }

    protected BaseProject() : base()
    {
        IsFileNameToLower = false;
        IsTargetFileNameToLower = false;
    }

    [Configure]
    public virtual void ConfigureAll(Configuration conf, Target target)
    {
        conf.SolutionFolder = ProjectFolder;

        conf.ProjectName = Name;
        conf.ProjectFileName = Name;
        conf.ProjectPath = Options.GetProjectPath(target);
        conf.TargetPath = Options.GetTargetPath(target);
        conf.TargetFileName = TargetFileName;
        conf.IntermediatePath = Options.GetIntermediatePath(target);

        conf.IncludePrivatePaths.Add(Options.RootPath);

        conf.Options.Add(Sharpmake.Options.Vc.Compiler.Exceptions.Enable);
        conf.Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.Latest); // CPP20

        conf.Defines.Add("POLLUX_PLATFORM_X64");

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
    }

    [Configure(Platform.win64)]
    public virtual void ConfigureWin64(Configuration conf, Target target)
    {
        conf.Defines.Add("POLLUX_SYSTEM_WINDOWS");
        conf.Defines.Add("POLLUX_DRIVER_VULKAN");

        conf.Defines.Add("_SCL_SECURE_NO_WARNINGS");
        conf.Defines.Add("_CRT_SECURE_NO_WARNINGS");
        conf.Defines.Add("WIN32_LEAN_AND_MEAN");
        conf.Defines.Add("_WINSOCKAPI_");

        conf.LibraryFiles.Add(Path.Combine(Options.ExternLibPath, "vulkan-1.lib"));

        conf.Options.Add(new Sharpmake.Options.Vc.Compiler.DisableSpecificWarnings("4005"));

        conf.Options.Add(Sharpmake.Options.Vc.General.WarningLevel.Level3);
        conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
        conf.Options.Add(Sharpmake.Options.Vc.General.DebugInformation.ProgramDatabase);
        conf.Options.Add(Sharpmake.Options.Vc.General.CharacterSet.Unicode);
        conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.v10_0_18362_0);
        conf.Options.Add(Sharpmake.Options.Vc.General.PreferredToolArchitecture.x64);
        conf.Options.Add(Sharpmake.Options.Vc.Compiler.MultiProcessorCompilation.Enable);
        
        conf.Options.Add(Sharpmake.Options.Vc.Compiler.FloatingPointModel.Precise);
        conf.Options.Add(Sharpmake.Options.Vc.Compiler.FloatingPointExceptions.Enable);
        conf.Options.Add(Sharpmake.Options.Vc.Compiler.RTTI.Disable);
        conf.Options.Add(Sharpmake.Options.Vc.Compiler.Inline.Default);
        conf.Options.Add(Sharpmake.Options.Vc.Linker.SubSystem.Console);

        conf.Options.Add(Sharpmake.Options.Vc.Linker.GenerateDebugInformation.Enable);
        conf.Options.Add(Sharpmake.Options.Vc.Linker.GenerateFullProgramDatabaseFile.Enable);

        if (target.Optimization == Optimization.Debug)
        {
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.Optimization.Disable);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.StringPooling.Disable);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeChecks.Both);
        }
        else
        {
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.Optimization.MaximizeSpeed);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.StringPooling.Enable);
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeChecks.Default);
        }


        if (target.Optimization == Optimization.Debug)
        {
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDebugDLL);
        }
        else
        {
            conf.Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDLL);
        }
    }
}
