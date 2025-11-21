@echo off
chcp 65001 >nul
echo ========================================
echo         欢迎来到大清模拟器！
echo ========================================
echo.

REM 检查可执行文件是否存在
if exist build\Release\QingEmulator.exe (
    build\Release\QingEmulator.exe
) else if exist build\QingEmulator.exe (
    build\QingEmulator.exe
) else (
    echo 错误: 未找到游戏可执行文件！
    echo 请先运行 build_windows.bat 编译游戏
    pause
    exit /b 1
)

pause
