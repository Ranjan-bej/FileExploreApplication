#include "FileExplorer.h"
#include <iostream>
#include <stdexcept>

FileExplorer::FileExplorer() {
    // Constructor - nothing to initialize here as fileOps is automatically constructed
}

void FileExplorer::run() {
    // Main loop is handled in main.cpp
}

void FileExplorer::listDirectory(const string& path) {
    fileOps.listDirectory(path);
}

void FileExplorer::changeDirectory(const string& path) {
    fileOps.changeDirectory(path);
}

void FileExplorer::createDirectory(const string& dirName) {
    fileOps.createDirectory(dirName);
}

void FileExplorer::remove(const string& path) {
    fileOps.remove(path);
}

void FileExplorer::copyFile(const string& source, const string& destination) {
    fileOps.copyFile(source, destination);
}

void FileExplorer::moveFile(const string& source, const string& destination) {
    fileOps.moveFile(source, destination);
}

void FileExplorer::searchFile(const string& fileName) {
    fileOps.searchFile(fileName);
}

string FileExplorer::getCurrentPath() const {
    return fileOps.getCurrentPath();
}