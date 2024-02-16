@echo off
REM .py 파일을 실행 파일로 변환합니다.
pyinstaller --onefile --platform linux my_script.py

REM 만들어진 실행 파일을 .bin 파일로 이름을 변경합니다.
ren dist/my_script my_script.bin

echo Conversion complete.
pause
