#include "FileOperations.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>
#include <iomanip>

using namespace std;
namespace fs = std::filesystem;

FileOperations::FileOperations() {
    currentPath = fs::current_path().string();
}

string FileOperations::getCurrentPath() const {
    return currentPath;
}

void FileOperations::listDirectory(const string& path) {
    string targetPath = path.empty() ? currentPath : getAbsolutePath(path);
    
    if (!fs::exists(targetPath)) {
        throw runtime_error("Directory does not exist: " + targetPath);
    }
    
    if (!fs::is_directory(targetPath)) {
        throw runtime_error("Not a directory: " + targetPath);
    }

    cout << "\nContents of " << targetPath << ":\n";
    cout << "--------------------------------------------------\n";
    cout << setw(10) << "Type" << setw(15) << "Size" << setw(20) << "Owner"
         << setw(10) << "Perms" << setw(25) << "Modified" << "  " << "Name\n";
    cout << "--------------------------------------------------\n";

    for (const auto& entry : fs::directory_iterator(targetPath)) {
        try {
            // Get file status
            const auto& path = entry.path();
            const auto status = fs::status(path);
            
            // Get file permissions
            string perms = "";
            perms += (fs::is_directory(status)) ? 'd' : '-';
            perms += (status.permissions() & fs::perms::owner_read) != fs::perms::none ? 'r' : '-';
            perms += (status.permissions() & fs::perms::owner_write) != fs::perms::none ? 'w' : '-';
            perms += (status.permissions() & fs::perms::owner_exec) != fs::perms::none ? 'x' : '-';
            perms += (status.permissions() & fs::perms::group_read) != fs::perms::none ? 'r' : '-';
            perms += (status.permissions() & fs::perms::group_write) != fs::perms::none ? 'w' : '-';
            perms += (status.permissions() & fs::perms::group_exec) != fs::perms::none ? 'x' : '-';
            perms += (status.permissions() & fs::perms::others_read) != fs::perms::none ? 'r' : '-';
            perms += (status.permissions() & fs::perms::others_write) != fs::perms::none ? 'w' : '-';
            perms += (status.permissions() & fs::perms::others_exec) != fs::perms::none ? 'x' : '-';

            // Get file size
            uintmax_t size = fs::is_directory(status) ? 0 : fs::file_size(path);
            
            // Get last write time
            auto ftime = fs::last_write_time(path);
            auto sctp = chrono::time_point_cast<chrono::system_clock::duration>(
                ftime - fs::file_time_type::clock::now() + chrono::system_clock::now());
            time_t cftime = chrono::system_clock::to_time_t(sctp);
            
            // Get owner and group
            struct stat fileStat;
            stat(path.string().c_str(), &fileStat);
            struct passwd *pw = getpwuid(fileStat.st_uid);
            struct group *gr = getgrgid(fileStat.st_gid);
            
            // Print file info
            cout << setw(10) << (fs::is_directory(status) ? "<DIR>" : "<FILE>")
                 << setw(15) << size
                 << setw(20) << (pw ? pw->pw_name : "unknown")
                 << setw(10) << perms
                 << setw(25) << put_time(localtime(&cftime), "%Y-%m-%d %H:%M:%S")
                 << "  " << path.filename().string() << endl;
                
        } catch (const exception& e) {
            cerr << "Error accessing " << entry.path() << ": " << e.what() << endl;
        }
    }
    cout << endl;
}

void FileOperations::changeDirectory(const string& path) {
    string newPath = getAbsolutePath(path);
    
    if (!fs::exists(newPath)) {
        throw runtime_error("Directory does not exist: " + newPath);
    }
    
    if (!fs::is_directory(newPath)) {
        throw runtime_error("Not a directory: " + newPath);
    }
    
    currentPath = fs::canonical(newPath).string();
    cout << "Changed directory to: " << currentPath << endl;
}

void FileOperations::createDirectory(const string& dirName) {
    string fullPath = getAbsolutePath(dirName);
    
    if (fs::exists(fullPath)) {
        throw runtime_error("File or directory already exists: " + fullPath);
    }
    
    if (!fs::create_directory(fullPath)) {
        throw runtime_error("Failed to create directory: " + fullPath);
    }
    
    cout << "Created directory: " << fullPath << endl;
}

void FileOperations::remove(const string& path) {
    string targetPath = getAbsolutePath(path);
    
    if (!fs::exists(targetPath)) {
        throw runtime_error("File or directory does not exist: " + targetPath);
    }
    
    if (fs::is_directory(targetPath)) {
        // Ask for confirmation before removing directory
        cout << "Are you sure you want to remove the directory and all its contents? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            cout << "Operation cancelled." << endl;
            return;
        }
        fs::remove_all(targetPath);
    } else {
        fs::remove(targetPath);
    }
    
    cout << "Removed: " << targetPath << endl;
}

void FileOperations::copyFile(const string& source, const string& destination) {
    string srcPath = getAbsolutePath(source);
    string destPath = getAbsolutePath(destination);
    
    if (!fs::exists(srcPath)) {
        throw runtime_error("Source does not exist: " + srcPath);
    }
    
    if (fs::is_directory(destPath)) {
        // If destination is a directory, append the source filename
        destPath += "/" + fs::path(srcPath).filename().string();
    }
    
    if (fs::exists(destPath)) {
        cout << "Destination file already exists. Overwrite? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            cout << "Operation cancelled." << endl;
            return;
        }
    }
    
    fs::copy(srcPath, destPath, fs::copy_options::overwrite_existing);
    cout << "Copied " << srcPath << " to " << destPath << endl;
}

void FileOperations::moveFile(const string& source, const string& destination) {
    string srcPath = getAbsolutePath(source);
    string destPath = getAbsolutePath(destination);
    
    if (!fs::exists(srcPath)) {
        throw runtime_error("Source does not exist: " + srcPath);
    }
    
    if (fs::is_directory(destPath)) {
        // If destination is a directory, append the source filename
        destPath += "/" + fs::path(srcPath).filename().string();
    }
    
    if (fs::exists(destPath)) {
        cout << "Destination file already exists. Overwrite? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            cout << "Operation cancelled." << endl;
            return;
        }
        fs::remove_all(destPath);
    }
    
    fs::rename(srcPath, destPath);
    cout << "Moved " << srcPath << " to " << destPath << endl;
}

void FileOperations::searchFile(const string& fileName) {
    cout << "Searching for '" << fileName << "' in " << currentPath << "..." << endl;
    size_t foundCount = 0;
    
    for (const auto& entry : fs::recursive_directory_iterator(currentPath)) {
        try {
            if (entry.is_regular_file() && 
                entry.path().filename().string().find(fileName) != string::npos) {
                cout << "Found: " << entry.path().string() << endl;
                foundCount++;
            }
        } catch (const exception& e) {
            // Skip files we can't access
            continue;
        }
    }
    
    cout << "Found " << foundCount << " matching files." << endl;
}

string FileOperations::getAbsolutePath(const string& path) const {
    if (path.empty()) {
        return currentPath;
    }
    
    if (fs::path(path).is_absolute()) {
        return path;
    }
    
    return (fs::path(currentPath) / path).lexically_normal().string();
}