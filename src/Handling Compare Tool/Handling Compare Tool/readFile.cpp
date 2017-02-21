#include "readFile.hpp"
#include <stdexcept>
#include <array>

size_t readFile(const std::string& src, std::string& dst, bool binaryMode) {
	auto fp = fopen(src.c_str(), (binaryMode) ? "rb" : "r");
	if (!fp) throw std::runtime_error("Cannot open file");
	fseek(fp, 0, SEEK_END);
	auto fSize = ftell(fp);
	rewind(fp);
	dst.clear();
	dst.reserve(fSize);
	std::array<std::string::value_type, 4096 / sizeof(std::string::value_type) /* 4KB */ > buffer;
	auto size = size_t{ 0 };
	auto n = size_t{ 0 };
	do {
		size += (n = fread(buffer.data(), sizeof(std::string::value_type), buffer.size(), fp));
		dst.append(buffer.data(), n);
	} while (n == buffer.size());
	fclose(fp);
	return size;
}