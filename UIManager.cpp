#include "UIManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

using namespace std;

void UIManager::displayWelcomeMessage() const {
    clearScreen();
    cout << "========================================\n";
    cout << "     Linux Console File Explorer\n";
    cout << "========================================\n";
    cout << "Type 'help' to see available commands\n\n";
}

void UIManager::displayCurrentDirectory(const string& path) const {
    cout << "\nCurrent Directory: " << path << "\n";
    cout << string(80, '=') << "\n";
}

void UIManager::displayFileInfo(const FileInfo& file) const {
    cout << left << setw(15) << (file.isDirectory ? "[DIR]" : "[FILE]")
         << setw(20) << file.name
         << setw(15) << formatSize(file.size)
         << setw(15) << file.permissions
         << setw(25) << formatTime(file.modifiedTime)
         << file.owner << "@" << file.group << "\n";
}

void UIManager::displayError(const string& message) const {
    cerr << "\033[1;31mError: " << message << "\033[0m\n";
}

void UIManager::displaySuccess(const string& message) const {
    cout << "\033[1;32m" << message << "\033[0m\n";
}

void UIManager::displayInfo(const string& message) const {
    cout << "\033[1;34m" << message << "\033[0m\n";
}

string UIManager::getUserInput(const string& prompt) const {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

bool UIManager::confirmAction(const string& message) const {
    cout << message << " (y/n): ";
    char response;
    cin >> response;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return (response == 'y' || response == 'Y');
}

void UIManager::clearScreen() const {
    // Use system-specific clear command
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

string UIManager::formatSize(uintmax_t size) const {
    ostringstream oss;
    if (size < 1024) {
        oss << size << " B";
    } else if (size < 1024 * 1024) {
        oss << fixed << setprecision(1) << (size / 1024.0) << " KB";
    } else if (size < 1024 * 1024 * 1024) {
        oss << fixed << setprecision(1) << (size / (1024.0 * 1024.0)) << " MB";
    } else {
        oss << fixed << setprecision(1) << (size / (1024.0 * 1024.0 * 1024.0)) << " GB";
    }
    return oss.str();
}

string UIManager::formatTime(time_t time) const {
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&time));
    return string(buffer);
}

void UIManager::displayHelp() const {
    clearScreen();
    cout << "\033[1;36m=== File Explorer Help ===\033[0m\n";
    cout << "\n\033[1mNavigation:\033[0m\n";
    cout << "  ls [path]     - List directory contents\n";
    cout << "  cd <path>     - Change directory\n";
    cout << "  pwd           - Show current directory\n\n";
    
    cout << "\033[1mFile Operations:\033[0m\n";
    cout << "  cp <src> <dst> - Copy file\n";
    cout << "  mv <src> <dst> - Move/rename file\n";
    cout << "  rm <path>     - Remove file or directory\n\n";
    
    cout << "\033[1mDirectory Operations:\033[0m\n";
    cout << "  mkdir <name>  - Create new directory\n\n";
    
    cout << "\033[1mSearch and Info:\033[0m\n";
    cout << "  find <name>   - Search for files\n";
    cout << "  help          - Show this help\n";
    cout << "  exit          - Exit the program\n\n";
    
    cout << "Press Enter to continue...";
    cin.ignore();
}