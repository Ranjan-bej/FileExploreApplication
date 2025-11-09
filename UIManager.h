#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <string>
#include <cstdint>
#include <ctime>

/**
 * @brief Structure to hold file information for display
 */
struct FileInfo {
    std::string name;           ///< Name of the file/directory
    uintmax_t size;             ///< Size in bytes
    std::string permissions;    ///< File permissions (e.g., "rwxr-xr--")
    std::string owner;          ///< File owner username
    std::string group;          ///< File group name
    time_t modifiedTime;        ///< Last modification time
    bool isDirectory;           ///< True if this is a directory
};

/**
 * @brief Handles all user interface components for the file explorer
 * 
 * This class is responsible for displaying information to the user and
 * collecting user input in a consistent and user-friendly way.
 */
class UIManager {
public:
    /**
     * @brief Display the welcome message and help information
     */
    void displayWelcomeMessage() const;

    /**
     * @brief Display the current directory path
     * @param path Current directory path to display
     */
    void displayCurrentDirectory(const std::string& path) const;

    /**
     * @brief Display information about a file or directory
     * @param file FileInfo structure containing file details
     */
    void displayFileInfo(const FileInfo& file) const;

    /**
     * @brief Display an error message
     * @param message Error message to display
     */
    void displayError(const std::string& message) const;

    /**
     * @brief Display a success message
     * @param message Success message to display
     */
    void displaySuccess(const std::string& message) const;

    /**
     * @brief Display an informational message
     * @param message Message to display
     */
    void displayInfo(const std::string& message) const;

    /**
     * @brief Get input from the user
     * @param prompt Message to display as a prompt
     * @return User input as a string
     */
    std::string getUserInput(const std::string& prompt) const;

    /**
     * @brief Ask for confirmation before performing a potentially destructive action
     * @param message Confirmation message to display
     * @return true if user confirms, false otherwise
     */
    bool confirmAction(const std::string& message) const;

    /**
     * @brief Clear the console screen
     */
    void clearScreen() const;

    /**
     * @brief Display the help menu with available commands
     */
    void displayHelp() const;

private:
    /**
     * @brief Format a file size in human-readable format
     * @param size Size in bytes
     * @return Formatted size string (e.g., "1.5 MB")
     */
    std::string formatSize(uintmax_t size) const;

    /**
     * @brief Format a timestamp as a readable date/time string
     * @param time Time value to format
     * @return Formatted date/time string
     */
    std::string formatTime(time_t time) const;
};

#endif // UI_MANAGER_H