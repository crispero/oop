@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"

:: Заданное слово в нескольких строках
call %PROGRAM% multiline.txt "test"> %OUT%
fc %OUT% multiline_out.txt 
if errorlevel 1 goto err
echo multiline passed

:: Заданное слово в одной строке
call %PROGRAM% oneline.txt "test"> %OUT%
fc %OUT% oneline_out.txt 
if errorlevel 1 goto err
echo test passed

:: Нет заданного слова 
call %PROGRAM% empty.txt "test"> %OUT%
fc %OUT% empty_out.txt 
if errorlevel 1 goto err
echo empty passed

:: Пустая стркоа на входе
call %PROGRAM% empty_string.txt ""> %OUT%
fc %OUT% empty_string_out.txt 
if errorlevel 1 goto err
echo emptystring passed

echo All tests passed 
exit /B 0

:err
echo Program testing failed
exit /B 1