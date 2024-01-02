// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class SimPleMySQL : ModuleRules
{
    public string ProjectDirectory
    {
        get
        {
            //返回模块路径，UE4 自带的，从当前文件所在的位置跳出去，后面的点就是跳多少次
            return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../../"));  //项目路径
        }
    }

    //把东西拷贝到Binaries里面  
    private void CopyToProjectBinaries(string FilePathName, ReadOnlyTargetRules Target)
    {
        //项目名称\Binaries\Win64  
        string BineriesDirectory = Path.Combine(ProjectDirectory, "Binaries", Target.Platform.ToString());
        //文件的名字
        string Filename = Path.GetFileName(FilePathName);

        //路径是否存在
        if (!Directory.Exists(BineriesDirectory))
        {
            //创建路径
            Directory.CreateDirectory(BineriesDirectory);
        }

        //路径加名字
        string ProjectFileFullName = Path.Combine(BineriesDirectory, Filename);

        if (!File.Exists(ProjectFileFullName))
        {
            //拷贝过去
            File.Copy(FilePathName, ProjectFileFullName, true);
        }

        RuntimeDependencies.Add(ProjectFileFullName);//添加到实时的依赖里面，这个很重要会支持自动考
    }

	public SimPleMySQL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        //为定义标识符的一个警告
        bEnableUndefinedIdentifierWarnings = false;//给警告关掉 

        //宏定义wind版本
        PublicDefinitions.Add("NTDDI_WIN7SP1"); //定义windows版本


        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        //ModuleDirectory 表示当前模块的目录
        string PluginsDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", ".."));//只是一个路径
        string SQLLibDirectory = Path.Combine(PluginsDirectory, "Source", "MySQL"); //MySQL路径
        string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";

        string MysqlPath = Path.Combine(SQLLibDirectory, PlatformString);//路径加名字

        PublicIncludePaths.Add(MysqlPath);

        RuntimeDependencies.Add(Path.Combine(MysqlPath, "libmysql.dll"));   //动态链接
        PublicAdditionalLibraries.Add(Path.Combine(MysqlPath, "libmysql.lib")); //静态链接

        CopyToProjectBinaries(Path.Combine(MysqlPath, "libmysql.dll"), Target);
        CopyToProjectBinaries(Path.Combine(MysqlPath, "libmysql.lib"), Target);

        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
