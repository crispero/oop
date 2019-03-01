@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"

:: ������������ ����������
call %PROGRAM% 2> %OUT%
fc %OUT% invalid_arguments_out.txt 
if errorlevel 1 goto err
echo invalid_arguments_out passed

:: �������� ����� � ���������� �������
call %PROGRAM% multiline.txt "test"> %OUT%
fc %OUT% multiline_out.txt 
if errorlevel 1 goto err
echo multiline passed

:: �������� ����� � ����� ������
call %PROGRAM% oneline.txt "test"> %OUT%
fc %OUT% oneline_out.txt 
if errorlevel 1 goto err
echo oneline passed

:: ��� ��������� ����� 
call %PROGRAM% empty.txt "test"> %OUT%
fc %OUT% empty_out.txt 
if not errorlevel 0 goto err
echo empty passed

:: ������ ������ �� �����
call %PROGRAM% empty_string.txt ""> %OUT%
fc %OUT% empty_string_out.txt 
if not errorlevel 0 goto err
echo emptystring passed

echo All tests passed 
exit /B 0

:err
echo Program testing failed
exit /B 1