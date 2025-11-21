@echo off
chcp 65001 >nul
echo ========================================
echo      大清模拟器 - Windows编译脚本
echo ========================================
echo.

REM 检查是否存在CMake
where cmake >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo 错误: 未找到CMake，请先安装CMake
    echo 下载地址: https://cmake.org/download/
    pause
    exit /b 1
)

REM 检查是否存在编译器
where cl >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    set COMPILER=MSVC
    echo 检测到 MSVC 编译器
) else (
    where g++ >nul 2>nul
    if %ERRORLEVEL% EQU 0 (
        set COMPILER=MinGW
        echo 检测到 MinGW 编译器
    ) else (
        echo 错误: 未找到C++编译器
        echo 请安装 Visual Studio 或 MinGW
        pause
        exit /b 1
    )
)

REM 创建构建目录
if not exist build (
    mkdir build
)

cd build

REM 运行CMake配置
echo.
echo 正在配置项目...
if "%COMPILER%"=="MinGW" (
    cmake -G "MinGW Makefiles" ..
) else (
    cmake ..
)

if %ERRORLEVEL% NEQ 0 (
    echo 配置失败！
    pause
    exit /b 1
)

REM 编译项目
echo.
echo 正在编译...
cmake --build . --config Release

if %ERRORLEVEL% NEQ 0 (
    echo 编译失败！
    pause
    exit /b 1
)

echo.
echo ========================================
echo 编译成功！
echo 可执行文件位置: build\QingEmulator.exe
echo 或 build\Release\QingEmulator.exe
echo ========================================
echo.

cd ..
pause
