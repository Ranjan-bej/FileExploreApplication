#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <string>
#include "FileOperations.h"

using namespace std;

/**
 * @brief Main controller class for the file explorer application
 * 
 * This class acts as an intermediary between the user interface and the file operations,
 * providing a clean API for the main application to interact with the file system.
 */
class FileExplorer {
public:
    /**
     * @brief Default constructor
     */
    FileExplorer();

    /**
     * @brief Main application loop
     */
    void run();

    /**
     * @brief List contents of a directory
     * @param path Path to list (defaults to current directory if empty)
     */
    void listDirectory(const string& path = "");

    /**
     * @brief Change the current working directory
     * @param path Directory path to change to
     * @throws runtime_error if the directory doesn't exist or is not accessible
     */
    void changeDirectory(const string& path);

    /**
     * @brief Create a new directory
     * @param dirName Name of the directory to create
     * @throws runtime_error if the directory cannot be created
     */
    void createDirectory(const string& dirName);

    /**
     * @brief Remove a file or directory
     * @param path Path to the file or directory to remove
     * @throws runtime_error if the path doesn't exist or cannot be removed
     */
    void remove(const string& path);

    /**
     * @brief Copy a file
     * @param source Source file path
     * @param destination Destination path
     * @throws runtime_error if the operation fails
     */
    void copyFile(const string& source, const string& destination);

    /**
     * @brief Move or rename a file
     * @param source Source file path
     * @param destination Destination path
     * @throws runtime_error if the operation fails
     */
    void moveFile(const string& source, const string& destination);

    /**
     * @brief Search for files by name in the current directory and subdirectories
     * @param fileName Name or pattern to search for
     */
    void searchFile(const string& fileName);

    /**
     * @brief Get the current working directory
     * @return string containing the absolute path of the current directory
     */
    string getCurrentPath() const;

private:
    FileOperations fileOps;  // Handles all file system operations
};

#endif // FILE_EXPLORER_H