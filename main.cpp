#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include "FileExplorer.h"
#include "UIManager.h"

using namespace std;

vector<string> splitCommand(const string& command) {
    vector<string> tokens;
    string token;
    for (char ch : command) {
        if (ch == ' ') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += ch;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<string> splitCommand(const string& command) {
    vector<string> tokens;
    string token;
    for (char ch : command) {
        if (ch == ' ') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += ch;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    UIManager ui;
    FileExplorer explorer;
    string command;
    
    // Show welcome message
    ui.displayWelcomeMessage();
    
    while (true) {
        // Show current directory
        ui.displayCurrentDirectory(explorer.getCurrentPath());
        
        // Get user command using UIManager
        command = ui.getUserInput("Command: ");
        
        if (command.empty()) continue;
        
        vector<string> tokens = splitCommand(command);
        if (tokens.empty()) continue;
        
        string cmd = tokens[0];
        
        try {
            if (cmd == "exit") {
                if (ui.confirmAction("Are you sure you want to exit?")) {
                    ui.displayInfo("Goodbye!");
                    break;
                }
            } else if (cmd == "help") {
                ui.displayHelp();
            } else if (cmd == "ls") {
                string path = (tokens.size() > 1) ? tokens[1] : ".";
                auto files = explorer.listDirectory(path);
                for (const auto& file : files) {
                    ui.displayFileInfo(file);
                }
            } else if (cmd == "cd") {
                if (tokens.size() < 2) {
                    ui.displayError("Usage: cd <directory>");
                } else {
                    if (explorer.changeDirectory(tokens[1])) {
                        ui.displaySuccess("Changed directory to: " + explorer.getCurrentPath());
                    } else {
                        ui.displayError("Failed to change directory");
                    }
                }
            } else if (cmd == "mkdir") {
                if (tokens.size() < 2) {
                    ui.displayError("Usage: mkdir <directory_name>");
                } else {
                    if (explorer.createDirectory(tokens[1])) {
                        ui.displaySuccess("Directory created: " + tokens[1]);
                    } else {
                        ui.displayError("Failed to create directory");
                    }
                }
            } else if (cmd == "rm") {
                if (tokens.size() < 2) {
                    ui.displayError("Usage: rm <file_or_directory>");
                } else {
                    if (ui.confirmAction("Are you sure you want to delete " + tokens[1] + "?")) {
                        if (explorer.remove(tokens[1])) {
                            ui.displaySuccess("Removed: " + tokens[1]);
                        } else {
                            ui.displayError("Failed to remove " + tokens[1]);
                        }
                    }
                }
            } else if (cmd == "cp") {
                if (tokens.size() < 3) {
                    ui.displayError("Usage: cp <source> <destination>");
                } else {
                    if (explorer.copyFile(tokens[1], tokens[2])) {
                        ui.displaySuccess("Copied to: " + tokens[2]);
                    } else {
                        ui.displayError("Failed to copy file");
                    }
                }
            } else if (cmd == "mv") {
                if (tokens.size() < 3) {
                    ui.displayError("Usage: mv <source> <destination>");
                } else {
                    if (explorer.moveFile(tokens[1], tokens[2])) {
                        ui.displaySuccess("Moved to: " + tokens[2]);
                    } else {
                        ui.displayError("Failed to move file");
                    }
                }
            } else if (cmd == "find") {
                if (tokens.size() < 2) {
                    ui.displayError("Usage: find <filename>");
                } else {
                    auto results = explorer.searchFile(tokens[1]);
                    if (results.empty()) {
                        ui.displayInfo("No files found matching: " + tokens[1]);
                    } else {
                        ui.displayInfo("Found " + to_string(results.size()) + " results:");
                        for (const auto& result : results) {
                            ui.displayInfo("  " + result);
                        }
                    }
                }
            } else if (cmd == "pwd") {
                ui.displayInfo("Current directory: " + explorer.getCurrentPath());
            } else {
                ui.displayError("Unknown command: " + cmd + " (type 'help' for available commands)");
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    
    cout << "Exiting Linux File Explorer. Goodbye!" << endl;
    return 0;
}