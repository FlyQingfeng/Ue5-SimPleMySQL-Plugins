// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class SimPleMySQL : ModuleRules
{
    public string ProjectDirectory
    {
        get
        {
            //����ģ��·����UE4 �Դ��ģ��ӵ�ǰ�ļ����ڵ�λ������ȥ������ĵ���������ٴ�
            return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../../"));  //��Ŀ·��
        }
    }

    //�Ѷ���������Binaries����  
    private void CopyToProjectBinaries(string FilePathName, ReadOnlyTargetRules Target)
    {
        //��Ŀ����\Binaries\Win64  
        string BineriesDirectory = Path.Combine(ProjectDirectory, "Binaries", Target.Platform.ToString());
        //�ļ�������
        string Filename = Path.GetFileName(FilePathName);

        //·���Ƿ����
        if (!Directory.Exists(BineriesDirectory))
        {
            //����·��
            Directory.CreateDirectory(BineriesDirectory);
        }

        //·��������
        string ProjectFileFullName = Path.Combine(BineriesDirectory, Filename);

        if (!File.Exists(ProjectFileFullName))
        {
            //������ȥ
            File.Copy(FilePathName, ProjectFileFullName, true);
        }

        RuntimeDependencies.Add(ProjectFileFullName);//��ӵ�ʵʱ���������棬�������Ҫ��֧���Զ���
    }

	public SimPleMySQL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        //Ϊ�����ʶ����һ������
        bEnableUndefinedIdentifierWarnings = false;//������ص� 

        //�궨��wind�汾
        PublicDefinitions.Add("NTDDI_WIN7SP1"); //����windows�汾


        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        //ModuleDirectory ��ʾ��ǰģ���Ŀ¼
        string PluginsDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", ".."));//ֻ��һ��·��
        string SQLLibDirectory = Path.Combine(PluginsDirectory, "Source", "MySQL"); //MySQL·��
        string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";

        string MysqlPath = Path.Combine(SQLLibDirectory, PlatformString);//·��������

        PublicIncludePaths.Add(MysqlPath);

        RuntimeDependencies.Add(Path.Combine(MysqlPath, "libmysql.dll"));   //��̬����
        PublicAdditionalLibraries.Add(Path.Combine(MysqlPath, "libmysql.lib")); //��̬����

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
