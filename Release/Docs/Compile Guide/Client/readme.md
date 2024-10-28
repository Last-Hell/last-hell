# Client Compile Guide!

This Guide will prepare u to Compile the Last Chaos Client files e.g. NKSP.exe Engine.dll etc

## Layout

1. [INCLUDE](#include)
2. [EXECUTE_FOLDER](#execute_folder)
3. [Engine](#engine)
4. [EntitesMP](#entitiesmp)
5. [GameMP](#gamemp)
6. [NKSP](#nksp)
7. [Shaders](#shaders)
8. [Common](#common)
9. [Final Words](#final-words)

## Include

You have to include 2 Folders in order to be able to compile. Put it in main Client Folder Structure e.g. ./Client/

## Execute Folder

in the Execute Folder u just need to put the ecc.exe nothing more.
**note** Please use the correct Version of the ECC.EXE November Source needs a November ECC and june NEEDS JUNE ECC!

## Engine

Create an Folder named **Release**.
Point the Output directory to **Release**

1. VC++ Directories
Executable directory

2. include directory
$(VCInstallDir)include; 
$(VCInstallDir)atlmfc\include; 
$(WindowsSdkDir)include; 
$(FrameworkSDKDir)\include; 
..\include\DXinclude

Don't inherit any Values (uncheck Checkbox)

3. Library directory


..\Lib\DXlib;
..\Lib\libboost;
$(LibraryPath);

nothing more here...

## EntitiesMP

Point Output Folder to **Release**

1. VC++ Directories

2. Executable Directories

..\execute;
$(ExecuteablePath)

3. include Directories

$(VCInstallDir)include;
$(VCInstallDir)atlmfc\include;
$(WindowsSdkDir)include;
$(FrameworkSDKDir)\include;
..\include\DXinclude

Remove Inherit Values

## GameMP

Point Output Folder **Release**

1. VC++ Directories

2. Executeable Directories

3. include Directories

$(VCInstallDir)include;
$(VCInstallDir)atlmfc\include;
$(WindowsSdkDir)include;
$(FrameworkSDKDir)\include;
..\include\DXinclude

Remove Inherit Values

## NKSP

Point Output Folder **Release**

1. VC++ Directories

2. Executeable Directories

3. include Directories

$(VCInstallDir)include;
$(VCInstallDir)atlmfc\include;
$(WindowsSdkDir)include;
$(FrameworkSDKDir)\include;
..\include\DXinclude

## Shaders

Point Output Folder **Release**

1. VC++ Directories

2. Executeable Directories

3. include Directories

$(VCInstallDir)include;
$(VCInstallDir)atlmfc\include;
$(WindowsSdkDir)include;
$(FrameworkSDKDir)\include;
..\include\DXinclude

## Common

1. VC++ Directories

2. Executeable Directories

3. include Directories

## Final Words

This is Everything you need to change to be able to compile the Last Chaos Client in Order to make it Work u need to chage the IP in the Client which is based at ** engine/comunicationinterface.cpp ** at ** Line 785 * to the IP you LoginServer is running at. It cant be localhost or 127.0.0.1 !

This is a basic setup i will not explain on how to make modifkations to the Client. Do it on ur own I won't give any support for it!!!