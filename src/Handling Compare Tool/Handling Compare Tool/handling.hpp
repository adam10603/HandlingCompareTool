#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <unordered_map>
#include <variant>
#include <array>
#include <utility>
#include <sstream>

class handling {
	friend class mainLogic;
public:
	enum objectState {
		UNINITIALIZED,
		FILE_ERROR,
		PARSING_ERROR,
		UNKNOWN_ERROR,
		GOOD_OLD,
		GOOD_NEW
	};


	struct dvec3_t {
		double x{}, y{}, z{};
		bool operator==(const dvec3_t& other) const noexcept { return x == other.x && y == other.y && z == other.z; }
	};

	using value_t = std::variant<double, uint32_t, dvec3_t, std::string>; // Don't reorder
	using handling_t = std::unordered_map<std::string, value_t>;
	using handlingSet_t = std::unordered_map<std::string, handling_t>;

	handling(const std::string&);
	handling();

	static std::string toString(const value_t&);
	static std::string toString(const value_t&, const std::string&);
	handlingSet_t& handlingData();
	static bool isEqual(const value_t&, const value_t&);
	objectState state();

private:
	enum dataType {
		FLOATING_POINT,
		VECTOR3,
		HANDLING_FLAGS,
		MODEL_FLAGS,
		DAMAGE_FLAGS,
		INTEGER,
		STRING
	};

	using fieldTypeDescriptor = std::pair<std::string, dataType>;
	using flagTable = std::array<std::pair<uint32_t, std::string>, 32>;

	handlingSet_t m_handling;
	objectState m_state{ objectState::UNINITIALIZED };

	static handlingSet_t parseDat(const std::string&);
	static handlingSet_t parseMeta(const std::string&);
	static value_t extractMetaField(const std::string&, size_t, dataType);
	static value_t extractDatField(std::stringstream&, dataType);

	static const std::array<fieldTypeDescriptor, 52> fieldTypeTable;
	static const flagTable strModelFlags;
	static const flagTable strHandlingFlags;
	static const flagTable strDamageFlags;
};