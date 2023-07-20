@echo off

set /A count =0
set name=

SETLOCAL enabledelayedexpansion
for %%i in (*.c) do (
	set name=%%i
	gcc -o !name:~0,-2! !name!
)

for %%i in (*.exe) do (
	set /A count = !count! + 1
)

echo Found %count% executable file(s).
if %count% EQU 1 (
	echo Compiled successfully...
	.\%name:~0,-2%.exe
	pause
	cls
	for %%i in (*.exe) do del %%i
) else (
	echo Compiled failure, check your errors!
	pause
	cls
)