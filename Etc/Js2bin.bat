@echo off

REM JavaScript 파일을 .bin으로 컴파일
echo Compiling JavaScript to binary format...
pkg your_script.js
echo Compilation complete.

REM JSON 파일 자동 생성/수정
echo Creating/Modifying JSON file...

REM JSON 파일을 생성/수정할 JavaScript 파일 실행
node modify_json.js

echo JSON file creation/modification complete.
