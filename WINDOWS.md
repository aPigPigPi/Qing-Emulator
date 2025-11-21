# Windows 平台使用指南

## 系统要求

- Windows 7 或更高版本
- CMake 3.10 或更高版本
- C++ 编译器（以下任一）：
  - Visual Studio 2015 或更高版本
  - MinGW-w64
  - Clang for Windows

## 安装编译工具

### 方法1: 使用 Visual Studio（推荐）

1. 下载并安装 [Visual Studio Community](https://visualstudio.microsoft.com/zh-hans/)
2. 安装时选择"使用C++的桌面开发"工作负载
3. 下载并安装 [CMake](https://cmake.org/download/)

### 方法2: 使用 MinGW

1. 下载并安装 [MinGW-w64](https://www.mingw-w64.org/)
2. 将MinGW的bin目录添加到系统PATH环境变量
3. 下载并安装 [CMake](https://cmake.org/download/)

## 快速开始

### 一键编译

1. 双击运行 `build_windows.bat`
2. 等待编译完成

### 一键运行

1. 双击运行 `run_windows.bat`
2. 开始游戏

## 手动编译（适用于高级用户）

### 使用 Visual Studio

打开"开发人员命令提示符"（Developer Command Prompt）：

```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

可执行文件位置：`build\Release\QingEmulator.exe`

### 使用 MinGW

打开命令提示符：

```cmd
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```

可执行文件位置：`build\QingEmulator.exe`

## 中文显示问题

如果游戏运行时中文显示乱码，请尝试以下方法：

### 方法1: 修改控制台编码（推荐）

在运行游戏前，先执行：
```cmd
chcp 65001
```

然后再运行游戏。

### 方法2: 使用Windows Terminal

1. 安装 [Windows Terminal](https://aka.ms/terminal)（Windows 10/11推荐）
2. 在Windows Terminal中运行游戏，中文显示会更好

### 方法3: 修改源代码

如果UTF-8编码仍有问题，可以修改`main.cpp`：

将：
```cpp
SetConsoleOutputCP(65001);
SetConsoleCP(65001);
```

改为：
```cpp
SetConsoleOutputCP(936);  // GBK编码
SetConsoleCP(936);
```

然后重新编译。

## 常见问题

### Q1: 提示"不是内部或外部命令"

**A**: 需要将CMake和编译器添加到系统PATH环境变量中。

添加PATH的步骤：
1. 右键"此电脑" -> "属性"
2. 点击"高级系统设置"
3. 点击"环境变量"
4. 在"系统变量"中找到"Path"
5. 添加CMake和编译器的bin目录路径

### Q2: CMake配置失败

**A**: 确保已安装C++编译器，并且编译器在PATH中。

### Q3: 编译时出现中文相关错误

**A**: 确保源代码文件以UTF-8编码保存。大多数现代编辑器默认使用UTF-8。

### Q4: 游戏运行时窗口一闪而过

**A**: 不要直接双击exe文件，请使用`run_windows.bat`运行，或在命令提示符中运行。

### Q5: 中文显示为方块或问号

**A**: 
1. 使用Windows Terminal而不是cmd.exe
2. 或者按照"中文显示问题"部分的方法解决

## 使用Visual Studio Code编译

如果您使用VSCode：

1. 安装插件：
   - C/C++ Extension Pack
   - CMake Tools

2. 打开项目文件夹

3. 按 `Ctrl+Shift+P`，选择"CMake: Configure"

4. 按 `Ctrl+Shift+P`，选择"CMake: Build"

5. 运行：按 `F5` 或在终端中运行可执行文件

## 性能优化

如果希望获得最佳性能，使用Release模式编译：

```cmd
cmake --build . --config Release
```

## 卸载

直接删除整个项目文件夹即可，游戏不会在系统中留下其他文件。

## 技术支持

如果遇到问题：

1. 确保使用的是最新版本的CMake和编译器
2. 检查是否正确安装了所有依赖
3. 查看编译输出的错误信息
4. 在项目的GitHub Issues页面报告问题

## 游戏截图保存

Windows用户可以使用以下快捷键截图：
- `Win + Shift + S`: 截取部分屏幕
- `Win + PrintScreen`: 截取整个屏幕

祝您游戏愉快！
