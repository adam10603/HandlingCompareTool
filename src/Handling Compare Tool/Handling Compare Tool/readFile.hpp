#ifndef readFile_hpp
#define readFile_hpp

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <cstdio>

size_t readFile(const std::string& src, std::string& dst, bool binaryMode = true);

#endif /* readFile_hpp */