@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"

:: Invalid arguments
call %PROGRAM% 1> %OUT%
fc %OUT% invalid_arguments_out.txt 
if errorlevel 1 goto err
echo invalid_arguments_out passed

:: Wrong format
call %PROGRAM% wrong_format.txt> %OUT%
fc %OUT% wrong_format_out.txt 
if errorlevel 1 goto err
echo wrong_format passed

:: Sun bmp format
call %PROGRAM% sun.bmp> %OUT%
fc %OUT% sun_out.txt 
if errorlevel 1 goto err
echo sun passed

:: Black square bmp format
call %PROGRAM% hqdefault.bmp> %OUT%
fc %OUT% black_square_out.txt 
if errorlevel 1 goto err
echo black_square passed

echo All tests passed 
exit /B 0

:err
echo Program testing failed
exit /B 1