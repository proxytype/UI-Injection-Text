# UI-Injection-Text
Change applications UI labels by overwrite user32.dll functions.

![alt text](https://raw.githubusercontent.com/proxytype/UI-Injection-Text/main/overwrite_interface.JPG)

## Requierments:
Microsoft Detours Library - https://github.com/microsoft/Detours

**Compile:**
1. Unzip source code, open command line and enter to source directory
2. SET DETOURS_TARGET_PROCESSOR=X64
3. C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat
4. NMAKE

Add detours.lib to Linker additional libraries.

**Hooked Function:**
- SetDlgItemTextW <br>
