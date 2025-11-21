# 文件编码说明

## 所有源代码文件使用GBK编码

为了确保在Dev-C++和Windows环境下正常显示中文，本项目的所有源代码文件均使用**GBK（ANSI）编码**。

### 编码文件列表

以下所有文件都使用GBK编码：

- `main.cpp` - 主程序入口
- `Game.cpp` - 游戏核心逻辑实现
- `Game.h` - 游戏类头文件
- `Province.cpp` - 省份管理实现
- `Province.h` - 省份类头文件
- `General.cpp` - 将领系统实现
- `General.h` - 将领类头文件
- `Technology.h` - 科技系统头文件
- `Event.h` - 事件系统头文件

### 在Dev-C++中使用

1. 使用Dev-C++打开`QingEmulator.dev`项目文件
2. 所有源文件会自动以ANSI/GBK编码显示
3. 中文字符应该能正常显示
4. 编译运行程序，控制台输出的中文也会正常显示

### 注意事项

- **不要**将源文件转换为UTF-8编码，否则会在Dev-C++中显示乱码
- 如果在其他IDE（如VS Code）中编辑，请确保保存为GBK编码
- 本项目已在`main.cpp`中设置控制台编码为GBK(936)，与源文件编码匹配

### 编码转换

如果需要在不同编辑器间切换，可以使用以下工具转换编码：

**Windows - Notepad++**:
1. 打开文件
2. 编码 → 转为ANSI编码
3. 保存

**Linux/Mac - iconv**:
```bash
iconv -f UTF-8 -t GBK input.cpp -o output.cpp
```

**Python脚本**:
```python
with open('file.cpp', 'r', encoding='utf-8') as f:
    content = f.read()
with open('file.cpp', 'w', encoding='gbk') as f:
    f.write(content)
```

---

**重要**: 保持所有源文件使用GBK编码，确保最佳的Dev-C++兼容性！
