@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"

:: Invalid arguments
call %PROGRAM% 1> %OUT%
fc %OUT% invalid_arguments_out.txt 
if errorlevel 1 goto err
echo invalid_arguments_out passed

:: Zero dererminant
call %PROGRAM% zero_determinant.txt> %OUT%
fc %OUT% zero_determinant_out.txt 
if errorlevel 1 goto err
echo zero_determinant passed

:: Correct input
call %PROGRAM% correct_input.txt> %OUT%
fc %OUT% correct_input_out.txt 
if errorlevel 1 goto err
echo correct_input passed

:: Correct input 2
call %PROGRAM% correct_input2.txt> %OUT%
fc %OUT% correct_input2_out.txt 
if not errorlevel 0 goto err
echo correct_input2 passed

echo All tests passed 
exit /B 0

:err
echo Program testing failed
exit /B 1