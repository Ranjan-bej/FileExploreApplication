#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <string>
#include <cstdint>
#include <vector>
#include <filesystem>
#include <fstream>

/**
 * @brief Structure to hold file information
 */
struct FileInfo {
    std::string name;           ///< Name of the file/directory
    std::string path;           ///< Full path to the file/directory
    uintmax_t size;             ///< Size in bytes (0 for directories)
    std::string permissions;    ///< File permissions in rwx format
    std::string owner;          ///< File owner username
    std::string group;          ///< File group name
    time_t modifiedTime;        ///< Last modification time
    bool isDirectory;           ///< True if this is a directory
};

/**
 * @brief Handles all file system operations for the file explorer
 * 
 * This class encapsulates all low-level file system operations,
 * providing a clean interface for the FileExplorer class to use.
 */
class FileOperations {
public:
    /**
     * @brief Default constructor
     */
    FileOperations();

    // ==================== Directory Operations ====================
    
    /**
     * @brief Get the current working directory
     * @return Current directory path as a string
     */
    std::string getCurrentPath() const;

    /**
     * @brief List contents of a directory
     * @param path Path to list (defaults to current directory if empty)
     * @throws std::runtime_error if the directory cannot be accessed
     */
    void listDirectory(const std::string& path = "");

    /**
     * @brief Change the current working directory
     * @param path Directory path to change to (can be relative or absolute)
     * @throws std::runtime_error if the directory doesn't exist or is not accessible
     */
    void changeDirectory(const std::string& path);

    /**
     * @brief Create a new directory
     * @param dirName Name of the directory to create
     * @param createParents If true, creates parent directories as needed
     * @return true if directory was created, false if it already exists
     * @throws std::runtime_error if the directory cannot be created
     */
    bool createDirectory(const std::string& dirName, bool createParents = false);

    /**
     * @brief Remove a directory
     * @param path Path to the directory to remove
     * @param recursive If true, removes directory and its contents
     * @return true if directory was removed, false if it didn't exist
     * @throws std::runtime_error if the directory cannot be removed
     */
    bool removeDirectory(const std::string& path, bool recursive = false);

    // ==================== File Operations ====================

    /**
     * @brief Create a new empty file
     * @param fileName Name of the file to create
     * @param content Optional content to write to the file
     * @return true if file was created, false if it already exists
     * @throws std::runtime_error if the file cannot be created
     */
    bool createFile(const std::string& fileName, const std::string& content = "");

    /**
     * @brief Read the contents of a file
     * @param fileName Name of the file to read
     * @return File contents as a string
     * @throws std::runtime_error if the file cannot be read
     */
    std::string readFile(const std::string& fileName) const;

    /**
     * @brief Write content to a file
     * @param fileName Name of the file to write to
     * @param content Content to write
     * @param append If true, appends to existing file instead of overwriting
     * @return true if write was successful
     * @throws std::runtime_error if the file cannot be written
     */
    bool writeFile(const std::string& fileName, const std::string& content, bool append = false);

    /**
     * @brief Delete a file
     * @param path Path to the file to delete
     * @return true if file was deleted, false if it didn't exist
     * @throws std::runtime_error if the file cannot be deleted
     */
    bool deleteFile(const std::string& path);

    /**
     * @brief Copy a file
     * @param source Source file path
     * @param destination Destination path
     * @param overwrite If true, overwrites existing destination file
     * @return true if copy was successful
     * @throws std::runtime_error if the operation fails
     */
    bool copyFile(const std::string& source, const std::string& destination, bool overwrite = false);

    /**
     * @brief Move or rename a file
     * @param source Source file path
     * @param destination Destination path
     * @param overwrite If true, overwrites existing destination file
     * @return true if move was successful
     * @throws std::runtime_error if the operation fails
     */
    bool moveFile(const std::string& source, const std::string& destination, bool overwrite = false);

    /**
     * @brief Get file information
     * @param path Path to the file or directory
     * @return FileInfo structure with file details
     * @throws std::runtime_error if the file cannot be accessed
     */
    FileInfo getFileInfo(const std::string& path) const;

    /**
     * @brief Check if a path exists
     * @param path Path to check
     * @return true if the path exists, false otherwise
     */
    bool exists(const std::string& path) const;

    /**
     * @brief Check if a path is a directory
     * @param path Path to check
     * @return true if the path is a directory, false otherwise
     */
    bool isDirectory(const std::string& path) const;

    /**
     * @brief Check if a path is a regular file
     * @param path Path to check
     * @return true if the path is a regular file, false otherwise
     */
    bool isFile(const std::string& path) const;

    // ==================== Search Operations ====================

    /**
     * @brief Search for files by name in the current directory and subdirectories
     * @param pattern Pattern to search for (supports * and ? wildcards)
     * @return Vector of matching file paths
     */
    std::vector<std::string> findFiles(const std::string& pattern) const;

    /**
     * @brief Search for files by content
     * @param searchString String to search for in file contents
     * @param filePattern File pattern to search in (e.g., "*.txt")
     * @return Vector of file paths containing the search string
     */
    std::vector<std::string> findInFiles(const std::string& searchString, 
                                       const std::string& filePattern = "*") const;

private:
    std::string currentPath;  ///< Current working directory

    // ==================== Helper Methods ====================

    /**
     * @brief Convert a path to an absolute path
     * @param path Input path (can be relative or absolute)
     * @return Absolute path as a string
     */
    std::string getAbsolutePath(const std::string& path) const;

    /**
     * @brief Get file information for a given path (internal use)
     */
    FileInfo getFileInfoInternal(const std::filesystem::path& path) const;

    /**
     * @brief Recursively search for files matching a pattern
     */
    void searchFilesRecursive(const std::string& dirPath, 
                            const std::string& pattern, 
                            std::vector<std::string>& results) const;

    /**
     * @brief Check if a filename matches a pattern with wildcards
     */
    bool matchesPattern(const std::string& filename, const std::string& pattern) const;
};

#endif // FILE_OPERATIONS_H