#pragma once

#include <vector>
#include <string>

#define LOG_LOCATION "./log.txt"

std::vector<std::string> splitString(const std::string& s);
std::vector<std::string> getFiles(std::string root);
void log(const char *fmt, ...);