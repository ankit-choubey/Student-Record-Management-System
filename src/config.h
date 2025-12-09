// config.h
// Configuration file with ANSI colors, constants, and UI utilities

#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <string>

namespace Color {
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string CYAN    = "\033[36m";
    const std::string GREEN   = "\033[32m";
    const std::string RED     = "\033[31m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string BRIGHT_CYAN   = "\033[96m";
    const std::string BRIGHT_GREEN  = "\033[92m";
    const std::string BRIGHT_RED    = "\033[91m";
    const std::string BRIGHT_YELLOW = "\033[93m";
}

namespace Box {
    const std::string HORIZONTAL = "═";
    const std::string VERTICAL   = "║";
    const std::string TOP_LEFT   = "╔";
    const std::string TOP_RIGHT  = "╗";
    const std::string BOTTOM_LEFT = "╚";
    const std::string BOTTOM_RIGHT = "╝";
}

namespace Config {
    const float AT_RISK_GPA_THRESHOLD = 5.0;
    const int DASHBOARD_WIDTH = 80;
}

inline void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

inline void printCenteredTitle(const std::string& title) {
    int padding = (Config::DASHBOARD_WIDTH - title.length()) / 2;
    std::cout << Color::BOLD << Color::BRIGHT_CYAN;
    std::cout << std::string(padding, ' ') << title << std::string(padding, ' ');
    std::cout << Color::RESET << std::endl;
}

inline void printDivider(char ch = '=', int width = Config::DASHBOARD_WIDTH) {
    std::cout << Color::CYAN << std::string(width, ch) << Color::RESET << std::endl;
}

inline void printSuccess(const std::string& message) {
    std::cout << Color::BRIGHT_GREEN << "✓ " << message << Color::RESET << std::endl;
}

inline void printError(const std::string& message) {
    std::cout << Color::BRIGHT_RED << "✗ " << message << Color::RESET << std::endl;
}

inline void printWarning(const std::string& message) {
    std::cout << Color::BRIGHT_YELLOW << "⚠ " << message << Color::RESET << std::endl;
}

inline void printInfo(const std::string& message) {
    std::cout << Color::BRIGHT_CYAN << "ℹ " << message << Color::RESET << std::endl;
}

#endif
