; Inno Setup Script:
; Created with ScriptMaker Version 2.0.10

[Setup]
    MinVersion=5.0,5.0
    AppName=QVna
    AppId=Qvna
    CreateUninstallRegKey=1
    UsePreviousAppDir=1
    UsePreviousGroup=1
    AppVersion=0.9.2
    AppVerName=QVna 0.9.2
    AppCopyright=--
    WizardStyle=modern
    WindowShowCaption=0
    WindowStartMaximized=0
    WindowVisible=0
    WindowResizable=0
    UninstallLogMode=Append
    DirExistsWarning=auto
    UninstallFilesDir={app}
    AllowRootDirectory=1
    DisableDirPage=0
    DisableStartupPrompt=0
    CreateAppDir=1
    DisableProgramGroupPage=0
    Uninstallable=1
    AllowNoIcons=1
    DefaultDirName={pf}\QVna
    DefaultGroupName=HiQSDR
    SourceDir=c:\ScriptMaker\smtemp
    OutputDir=C:\tmp\qvna\trunk\src\release
    PrivilegesRequired=admin
    SetupIconFile=C:\tmp\qvna\trunk\src\qvna48.ico



[Dirs]
    Name: {app}

[Files]
    Source: C:\tmp\qvna\trunk\src\release\qvna.exe; DestDir: {app}\; DestName: qvna.exe
    Source: C:\tmp\qvna\trunk\src\release\libstdc++-6.dll; DestDir: {app}\; 
    Source: C:\tmp\qvna\trunk\src\release\libgcc_s_dw2-1.dll; DestDir: {app}\; 

   

[Icons]
    Name: {group}\QVna; Filename: {app}\qvna.exe; WorkingDir: {app}; IconFilename: {app}\qvna.exe

[INI]

[Registry]

[UninstallDelete]

[InstallDelete]

[Run]

[UninstallRun]

[Languages]

Name: "en"; MessagesFile: "compiler:Default.isl"
Name: "de"; MessagesFile: "compiler:Languages\german.isl"


; ==============================================
; The lines below are used by ScriptMaker
; They are not required by Inno Setup
; DO NOT DELETE THEM or you may be unable to reload the script

;[ScriptSetup]
;VerNum=2.6.1
;InnoVer=2.0
;AddVerTo=AppName 
;SetupFilename=Setup.exe
;OutputFolder=Z:\projects\linecrypt\nlcc\dist
;SetupIconFileName=Z:\stefan\work\svn\nlcc4\src\trunk\lcc.ico
;SetupIconIndex=-1
;CopyrightText=--

