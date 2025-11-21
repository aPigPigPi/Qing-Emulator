#include "Game.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    // 设置Windows控制台编码以正确显示中文
    // UTF-8编码 (65001) - 适用于Windows 10及以上，Windows Terminal
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    // 如果UTF-8显示乱码，可以改用GBK编码 (936)
    // 取消下面两行的注释，并注释掉上面的UTF-8设置
    // SetConsoleOutputCP(936);
    // SetConsoleCP(936);
#endif
    
    Game game;
    game.run();
    
    return 0;
}
