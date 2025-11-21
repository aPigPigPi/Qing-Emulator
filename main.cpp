#include "Game.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    // 设置Windows控制台编码以正确显示中文
    // GBK/ANSI编码 (936) - 适用于ANSI编码的源文件（Dev-C++默认）
    SetConsoleOutputCP(936);
    SetConsoleCP(936);
    
    // 如果源文件是UTF-8编码，可以改用UTF-8 (65001)
    // 取消下面两行的注释，并注释掉上面的GBK设置
    // SetConsoleOutputCP(65001);
    // SetConsoleCP(65001);
#endif
    
    Game game;
    game.run();
    
    return 0;
}
