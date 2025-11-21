#include "Game.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    // 设置Windows控制台UTF-8编码以正确显示中文
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    // 也可以尝试使用GBK编码（代码页936）
    // SetConsoleOutputCP(936);
    // SetConsoleCP(936);
#endif
    
    Game game;
    game.run();
    
    return 0;
}
