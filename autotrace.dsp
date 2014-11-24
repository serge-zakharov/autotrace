# Microsoft Developer Studio Project File - Name="autotrace" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=autotrace - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "autotrace.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "autotrace.mak" CFG="autotrace - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "autotrace - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "autotrace - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "autotrace - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "autotrace___Win32_Release"
# PROP BASE Intermediate_Dir "autotrace___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "autotrace___Win32_Release"
# PROP Intermediate_Dir "autotrace___Win32_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /W3 /Gm /GX /Zi /O2 /I "C:\ImageMagick-5.5.3" /I "C:\ming-0.2a" /I "C:\pstoeditb" /I "C:\libpng" /I "C:\zlib" /D "WIN32" /D "_WINDOWS" /D "_VISUALC_" /D "NeedFunctionPrototypes" /D "HAVE_MAGICK" /D PACKAGE_VERSION=\"0.31\" /D "HAVE_LIBSWF" /D inline=__inline /D "_MAGICKDLL_" /D "HAVE_LIBPSTOEDIT" /D "HAVE_LIBPNG" /Fp"autotrace___Win32_Release/autotraceexe.pch" /YX /FD /D PACKAGE_URL=\""http://autotrace.sourceforge.net"\" /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 CORE_RL_magick_.lib libming.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib pstoedit.lib libpng.lib zlib.lib /nologo /subsystem:console /machine:I386 /libpath:"C:\ImageMagick-5.5.3\VisualMagick\lib\\" /libpath:"C:\ming-0.2a\Release" /libpath:"C:\pstoeditb" /libpath:"C:\libpng\msvc\win32\libpng\lib" /libpath:"C:\zlib\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "autotrace - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "autotrace___Win32_Debug"
# PROP BASE Intermediate_Dir "autotrace___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\autotrace___Win32_Debug"
# PROP Intermediate_Dir ".\autotrace___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "C:\ImageMagick-5.5.3" /I "C:\ming-0.2a" /I "C:\pstoeditb" /I "C:\libpng" /I "C:\zlib" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_VISUALC_" /D "NeedFunctionPrototypes" /D "HAVE_MAGICK" /D PACKAGE_VERSION=\"0.31\" /D "HAVE_LIBSWF" /D inline=__inline /D "_MAGICKDLL_" /D "HAVE_LIBPSTOEDIT" /D "HAVE_LIBPNG" /FD /D PACKAGE_URL=\""http://autotrace.sourceforge.net"\" /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libming.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib CORE_DB_magick_.lib pstoedit.lib libpng.lib zlib.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"C:\ImageMagick-5.5.3\VisualMagick\lib\\" /libpath:"C:\ming-0.2a\Debug" /libpath:"C:\pstoeditb" /libpath:"C:\libpng\msvc\win32\libpng\lib" /libpath:"C:\zlib\lib"

!ENDIF 

# Begin Target

# Name "autotrace - Win32 Release"
# Name "autotrace - Win32 Debug"
# Begin Source File

SOURCE=.\src\atou.c
# End Source File
# Begin Source File

SOURCE=.\src\atou.h
# End Source File
# Begin Source File

SOURCE=.\src\autotrace.c
# End Source File
# Begin Source File

SOURCE=.\src\autotrace.h
# End Source File
# Begin Source File

SOURCE=.\src\bitmap.c
# End Source File
# Begin Source File

SOURCE=.\src\bitmap.h
# End Source File
# Begin Source File

SOURCE=.\src\cmdline.h
# End Source File
# Begin Source File

SOURCE=.\src\color.c
# End Source File
# Begin Source File

SOURCE=.\src\color.h
# End Source File
# Begin Source File

SOURCE=.\src\curve.c
# End Source File
# Begin Source File

SOURCE=.\src\curve.h
# End Source File
# Begin Source File

SOURCE=.\src\despeckle.c
# End Source File
# Begin Source File

SOURCE=.\src\despeckle.h
# End Source File
# Begin Source File

SOURCE=".\src\epsilon-equal.c"
# End Source File
# Begin Source File

SOURCE=".\src\epsilon-equal.h"
# End Source File
# Begin Source File

SOURCE=.\src\exception.c
# End Source File
# Begin Source File

SOURCE=.\src\exception.h
# End Source File
# Begin Source File

SOURCE=.\src\filename.c
# End Source File
# Begin Source File

SOURCE=.\src\filename.h
# End Source File
# Begin Source File

SOURCE=.\src\fit.c
# End Source File
# Begin Source File

SOURCE=.\src\fit.h
# End Source File
# Begin Source File

SOURCE=.\src\getopt.c
# End Source File
# Begin Source File

SOURCE=.\src\getopt.h
# End Source File
# Begin Source File

SOURCE=.\src\getopt1.c
# End Source File
# Begin Source File

SOURCE=".\src\image-header.h"
# End Source File
# Begin Source File

SOURCE=".\src\image-proc.c"
# End Source File
# Begin Source File

SOURCE=".\src\image-proc.h"
# End Source File
# Begin Source File

SOURCE=".\src\input-bmp.c"
# End Source File
# Begin Source File

SOURCE=".\src\input-bmp.h"
# End Source File
# Begin Source File

SOURCE=".\src\input-magick.c"
# End Source File
# Begin Source File

SOURCE=".\src\input-magick.h"
# End Source File
# Begin Source File

SOURCE=".\src\input-png.c"
# End Source File
# Begin Source File

SOURCE=".\src\input-png.h"
# End Source File
# Begin Source File

SOURCE=".\src\input-pnm.c"
# End Source File
# Begin Source File

SOURCE=".\src\input-pnm.h"
# End Source File
# Begin Source File

SOURCE=".\src\input-tga.c"
# End Source File
# Begin Source File

SOURCE=".\src\input-tga.h"
# End Source File
# Begin Source File

SOURCE=.\src\input.c
# End Source File
# Begin Source File

SOURCE=.\src\input.h
# End Source File
# Begin Source File

SOURCE=.\src\logreport.c
# End Source File
# Begin Source File

SOURCE=.\src\logreport.h
# End Source File
# Begin Source File

SOURCE=.\src\main.c
# End Source File
# Begin Source File

SOURCE=.\src\median.c
# End Source File
# Begin Source File

SOURCE=.\src\message.h
# End Source File
# Begin Source File

SOURCE=".\src\output-cgm.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-cgm.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-dr2d.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-dr2d.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-dxf.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-dxf.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-emf.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-emf.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-epd.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-epd.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-eps.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-eps.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-er.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-er.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-fig.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-fig.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-mif.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-mif.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-p2e.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-p2e.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-pdf.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-pdf.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-pstoedit.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-pstoedit.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-sk.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-sk.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-svg.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-svg.h"
# End Source File
# Begin Source File

SOURCE=".\src\output-swf.c"
# End Source File
# Begin Source File

SOURCE=".\src\output-swf.h"
# End Source File
# Begin Source File

SOURCE=.\src\output.c
# End Source File
# Begin Source File

SOURCE=.\src\output.h
# End Source File
# Begin Source File

SOURCE=.\src\ptypes.h
# End Source File
# Begin Source File

SOURCE=".\src\pxl-outline.c"
# End Source File
# Begin Source File

SOURCE=".\src\pxl-outline.h"
# End Source File
# Begin Source File

SOURCE=.\src\quantize.h
# End Source File
# Begin Source File

SOURCE=.\src\spline.c
# End Source File
# Begin Source File

SOURCE=.\src\spline.h
# End Source File
# Begin Source File

SOURCE=.\src\strgicmp.c
# End Source File
# Begin Source File

SOURCE=.\src\strgicmp.h
# End Source File
# Begin Source File

SOURCE=".\src\thin-image.c"
# End Source File
# Begin Source File

SOURCE=".\src\thin-image.h"
# End Source File
# Begin Source File

SOURCE=.\src\types.h
# End Source File
# Begin Source File

SOURCE=.\src\vector.c
# End Source File
# Begin Source File

SOURCE=.\src\vector.h
# End Source File
# Begin Source File

SOURCE=.\src\xstd.c
# End Source File
# Begin Source File

SOURCE=.\src\xstd.h
# End Source File
# End Target
# End Project
