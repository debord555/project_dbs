#include "misc.hpp"
#include <regex>
#include <filesystem>
#include <stack>
#include <stdarg.h>

/**
 * @brief Splits a string on each occurrence of a delimiter and returns a vector
 *        of strings.
 *
 * @details The delimiters are specified by the regular expression "[&;,]".
 *          The function removes any leading or trailing whitespace from the
 *          resulting strings.
 *
 * @param[in] s The string to split.
 *
 * @return A vector of strings.
 */
std::vector<std::string> splitString(const std::string& s) {
    std::vector<std::string> result;
    std::regex re("[&;,]");
    std::sregex_token_iterator it(s.begin(), s.end(), re, -1);
    std::sregex_token_iterator end;
    for (; it != end; ++it) {
        std::string str = *it;
        str.erase(0, str.find_first_not_of(" \t\r\n")); // remove leading whitespaces
        str.erase(str.find_last_not_of(" \t\r\n") + 1); // remove trailing whitespaces
        if (str != "")
            result.push_back(str);
    }
    return result;
}

/**
 * @brief Finds all files in the given directory and all its subdirectories.
 *
 * @details This function returns a vector of strings, each containing the path
 *          to a file found in the given root directory or its subdirectories.
 *
 * @param[in] root The root directory to search in.
 *
 * @return A vector of strings containing file paths.
 */
std::vector<std::string> getFiles(std::string root) {
    std::vector<std::string> files;
    std::filesystem::path curr_path(root);
    std::stack<std::filesystem::path> directories;
    if (std::filesystem::exists(curr_path) && std::filesystem::is_directory(curr_path))
        directories.push(curr_path);
    while (!directories.empty()) {
        curr_path = directories.top();
        directories.pop();
        if (std::filesystem::exists(curr_path)) {
            if (std::filesystem::is_directory(curr_path)) {
                for (const auto& entry : std::filesystem::directory_iterator(curr_path))
                    directories.push(entry.path());
            } else if (std::filesystem::is_regular_file(curr_path))
                files.push_back(curr_path.string());
        }
    }
    return files;
}

/**
 * @brief Logs a formatted message with a timestamp to a specified log file.
 *
 * @details This function appends a timestamped message to the log file 
 *          located at LOG_LOCATION. The message is formatted similarly to 
 *          printf, using variadic arguments to specify the format and the 
 *          values to include in the log entry. LOG_LOCATION is a macro defined
 *          in cxx_functions.hpp.
 *
 * @param[in] fmt The format string, followed by any additional arguments 
 *                required by the format specifiers.
 */
void log(const char *fmt, ...) {
    va_list args;
    FILE *fptr;
    char time_string[64];
    time_t now;
    time(&now);
    fptr = fopen(LOG_LOCATION, "a+");
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", localtime(&now));
    fprintf(fptr, "[%s] ", time_string);
    va_start(args, fmt);
    vfprintf(fptr, fmt, args);
    va_end(args);
    fclose(fptr);
}