@echo off

chcp 1251

set PROGRAM="%~1"
set OUT="%TEMP%\out1.txt"

:: Correct input
call %PROGRAM% "6"> %OUT%
fc %OUT% correct_input_out.txt 
if errorlevel 1 goto err
echo correct_input passed

:: Input byte < 0
call %PROGRAM% "-1"> %OUT%
fc %OUT% incorrect_input1_out.txt 
if errorlevel 1 goto err
echo incorrect_input1 passed

:: Input byte > 255
call %PROGRAM% "256"> %OUT%
fc %OUT% incorrect_input2_out.txt 
if errorlevel 1 goto err
echo incorrect_input2 passed

echo All tests passed 
exit /B 0

:err
echo Program testing failed
exit /B 1