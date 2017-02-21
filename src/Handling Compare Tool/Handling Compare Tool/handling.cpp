#include "handling.hpp"
#include "MainForm.h"
#include "readFile.hpp"
#include <fstream>
#include <iterator>
#include <cctype>
#include <type_traits>
#include <stdexcept>
#include <cstdio>
#include <Windows.h>

decltype(handling::fieldTypeTable) handling::fieldTypeTable{{
	{ "fMass"							, handling::FLOATING_POINT	},
	{ "fInitialDragCoeff"				, handling::FLOATING_POINT	},
	{ "fPercentSubmerged"				, handling::FLOATING_POINT	},
	{ "vecCentreOfMassOffset"			, handling::VECTOR3			},
	{ "vecCOMAbs"						, handling::VECTOR3			},
	{ "vecInertiaMultiplier"			, handling::VECTOR3			},
	{ "fDriveBiasFront"					, handling::FLOATING_POINT	},
	{ "nInitialDriveGears"				, handling::INTEGER			},
	{ "fInitialDriveForce"				, handling::FLOATING_POINT	},
	{ "fDriveInertia"					, handling::FLOATING_POINT	},
	{ "fClutchChangeRateScaleUpShift"	, handling::FLOATING_POINT	},
	{ "fClutchChangeRateScaleDownShift"	, handling::FLOATING_POINT	},
	{ "fInitialDriveMaxFlatVel"			, handling::FLOATING_POINT	},
	{ "fBrakeForce"						, handling::FLOATING_POINT	},
	{ "fBrakeBiasFront"					, handling::FLOATING_POINT	},
	{ "fHandBrakeForce"					, handling::FLOATING_POINT	},
	{ "fSteeringLock"					, handling::FLOATING_POINT	},
	{ "fTractionCurveMax"				, handling::FLOATING_POINT	},
	{ "fTractionCurveMin"				, handling::FLOATING_POINT	},
	{ "fTractionCurveLateral"			, handling::FLOATING_POINT	},
	{ "fTractionCurveLongitudinal"		, handling::FLOATING_POINT	},
	{ "fTractionSpringDeltaMax"			, handling::FLOATING_POINT	},
	{ "fLowSpeedTractionLossMult"		, handling::FLOATING_POINT	},
	{ "fCamberStiffnesss"				, handling::FLOATING_POINT	},
	{ "fTractionBiasFront"				, handling::FLOATING_POINT	},
	{ "fTractionLossMult"				, handling::FLOATING_POINT	},
	{ "fSuspensionForce"				, handling::FLOATING_POINT	},
	{ "fSuspensionCompDamp"				, handling::FLOATING_POINT	},
	{ "fSuspensionReboundDamp"			, handling::FLOATING_POINT	},
	{ "fSuspensionUpperLimit"			, handling::FLOATING_POINT	},
	{ "fSuspensionLowerLimit"			, handling::FLOATING_POINT	},
	{ "fSuspensionRaise"				, handling::FLOATING_POINT	},
	{ "fSuspensionBiasFront"			, handling::FLOATING_POINT	},
	{ "fAntiRollBarForce"				, handling::FLOATING_POINT	},
	{ "fAntiRollBarBiasFront"			, handling::FLOATING_POINT	},
	{ "fRollCentreHeightFront"			, handling::FLOATING_POINT	},
	{ "fRollCentreHeightRear"			, handling::FLOATING_POINT	},
	{ "fCollisionDamageMult"			, handling::FLOATING_POINT	},
	{ "fWeaponDamageMult"				, handling::FLOATING_POINT	},
	{ "fDeformationDamageMult"			, handling::FLOATING_POINT	},
	{ "fEngineDamageMult"				, handling::FLOATING_POINT	},
	{ "fPetrolTankVolume"				, handling::FLOATING_POINT	},
	{ "fOilVolume"						, handling::FLOATING_POINT	},
	{ "fSeatOffsetDistX"				, handling::FLOATING_POINT	},
	{ "fSeatOffsetDistY"				, handling::FLOATING_POINT	},
	{ "fSeatOffsetDistZ"				, handling::FLOATING_POINT	},
	{ "nMonetaryValue"					, handling::INTEGER			},
	{ "strModelFlags"					, handling::MODEL_FLAGS		},
	{ "strHandlingFlags"				, handling::HANDLING_FLAGS	},
	{ "nAnimGroup"						, handling::INTEGER			},
	{ "AIHandling"						, handling::STRING			},
	{ "strDamageFlags"					, handling::DAMAGE_FLAGS	}
}};

decltype(handling::strModelFlags) handling::strModelFlags{{
	{ 0b1u << 0		, "IS_VAN"						},
	{ 0b1u << 1		, "IS_BUS"						},
	{ 0b1u << 2		, "IS_LOW"						},
	{ 0b1u << 3		, "IS_BIG"						},
	{ 0b1u << 4		, "ABS_STD"						},
	{ 0b1u << 5		, "ABS_OPTION"					},
	{ 0b1u << 6		, "ABS_ALT_STD"					},
	{ 0b1u << 7		, "ABS_ALT_OPTION"				},
	{ 0b1u << 8		, "NO_DOORS"					},
	{ 0b1u << 9		, "TANDEM_SEATS"				},
	{ 0b1u << 10	, "SIT_IN_BOAT"					},
	{ 0b1u << 11	, "HAS_TRACKS"					},
	{ 0b1u << 12	, "NO_EXHAUST"					},
	{ 0b1u << 13	, "DOUBLE_EXHAUST"				},
	{ 0b1u << 14	, "NO1FPS_LOOK_BEHIND"			},
	{ 0b1u << 15	, "CAN_ENTER_IF_NO_DOOR"		},
	{ 0b1u << 16	, "AXLE_F_TORSION"				},
	{ 0b1u << 17	, "AXLE_F_SOLID"				},
	{ 0b1u << 18	, "AXLE_F_MCPHERSON"			},
	{ 0b1u << 19	, "ATTACH_PED_TO_BODYSHELL"		},
	{ 0b1u << 20	, "AXLE_R_TORSION"				},
	{ 0b1u << 21	, "AXLE_R_SOLID"				},
	{ 0b1u << 22	, "AXLE_R_MCPHERSON"			},
	{ 0b1u << 23	, "DONT_FORCE_GRND_CLEARANCE"	},
	{ 0b1u << 24	, "DONT_RENDER_STEER"			},
	{ 0b1u << 25	, "NO_WHEEL_BURST"				},
	{ 0b1u << 26	, "INDESTRUCTIBLE"				},
	{ 0b1u << 27	, "DOUBLE_FRONT_WHEELS"			},
	{ 0b1u << 28	, "RC"							},
	{ 0b1u << 29	, "DOUBLE_RWHEELS"				},
	{ 0b1u << 30	, "MF_NO_WHEEL_BREAK"			},
	{ 0b1u << 31	, "IS_HATCHBACK"				}
}};

decltype(handling::strHandlingFlags) handling::strHandlingFlags{{
	{ 0b1u << 0		, "SMOOTH_COMPRESN"	/* :hot_pepper: */		},
	{ 0b1u << 1		, "REDUCED_MOD_MASS"						},
	{ 0b1u << 2		, "N/A"										},
	{ 0b1u << 3		, "N/A"										},
	{ 0b1u << 4		, "NO_HANDBRAKE"							},
	{ 0b1u << 5		, "STEER_REARWHEELS"						},
	{ 0b1u << 6		, "HB_REARWHEEL_STEER"						},
	{ 0b1u << 7		, "STEER_ALL_WHEELS"						},
	{ 0b1u << 8		, "FREEWHEEL_NO_GAS"						},
	{ 0b1u << 9		, "NO_REVERSE"								},
	{ 0b1u << 10	, "N/A"										},
	{ 0b1u << 11	, "STEER_NO_WHEELS"							},
	{ 0b1u << 12	, "CVT"										},
	{ 0b1u << 13	, "ALT_EXT_WHEEL_BOUNDS_BEH"				},
	{ 0b1u << 14	, "DONT_RAISE_BOUNDS_AT_SPEED"				},
	{ 0b1u << 15	, "N/A"										},
	{ 0b1u << 16	, "LESS_SNOW_SINK"							},
	{ 0b1u << 17	, "TYRES_CAN_CLIP"	/* :flushed2: */		},
	{ 0b1u << 18	, "N/A"										},
	{ 0b1u << 19	, "N/A"										},
	{ 0b1u << 20	, "OFFROAD_ABILITY"							},
	{ 0b1u << 21	, "OFFROAD_ABILITY2"						},
	{ 0b1u << 22	, "HF_TYRES_RAISE_SIDE_IMPACT_THRESHOLD"	},
	{ 0b1u << 23	, "N/A"										},
	{ 0b1u << 24	, "ENABLE_LEAN"								},
	{ 0b1u << 25	, "N/A"										},
	{ 0b1u << 26	, "HEAVYARMOUR"								},
	{ 0b1u << 27	, "ARMOURED"								},
	{ 0b1u << 28	, "SELF_RIGHTING_IN_WATER"					},
	{ 0b1u << 29	, "IMPROVED_RIGHTING_FORCE"					},
	{ 0b1u << 30	, "N/A"										},
	{ 0b1u << 31	, "N/A"										}
}};

decltype(handling::strDamageFlags) handling::strDamageFlags{{
	{ 0b1u << 0		, "DRIVER_SIDE_FRONT_DOOR"				},
	{ 0b1u << 1		, "DRIVER_SIDE_REAR_DOOR"				},
	{ 0b1u << 2		, "DRIVER_PASSENGER_SIDE_FRONT_DOOR"	},
	{ 0b1u << 3		, "DRIVER_PASSENGER_SIDE_REAR_DOOR"		},
	{ 0b1u << 4		, "BONNET"								},
	{ 0b1u << 5		, "BOOT"								},
	{ 0b1u << 6		, "N/A"									},
	{ 0b1u << 7		, "N/A"									},
	{ 0b1u << 8		, "N/A"									},
	{ 0b1u << 9		, "N/A"									},
	{ 0b1u << 10	, "N/A"									},
	{ 0b1u << 11	, "N/A"									},
	{ 0b1u << 12	, "N/A"									},
	{ 0b1u << 13	, "N/A"									},
	{ 0b1u << 14	, "N/A"									},
	{ 0b1u << 15	, "N/A"									},
	{ 0b1u << 16	, "N/A"									},
	{ 0b1u << 17	, "N/A"									},
	{ 0b1u << 18	, "N/A"									},
	{ 0b1u << 19	, "N/A"									},
	{ 0b1u << 20	, "N/A"									},
	{ 0b1u << 21	, "N/A"									},
	{ 0b1u << 22	, "N/A"									},
	{ 0b1u << 23	, "N/A"									},
	{ 0b1u << 24	, "N/A"									},
	{ 0b1u << 25	, "N/A"									},
	{ 0b1u << 26	, "N/A"									},
	{ 0b1u << 27	, "N/A"									},
	{ 0b1u << 28	, "N/A"									},
	{ 0b1u << 29	, "N/A"									},
	{ 0b1u << 30	, "N/A"									},
	{ 0b1u << 31	, "N/A"									}
}};

handling::handling(const std::string& filename) {
	std::string data;

	try {
		if (readFile(filename, data) == 0) throw std::runtime_error("No data was read");
	}
	catch (const std::runtime_error& err) {
		mainLogic::messageBox(std::string("An error has occured while reading the file:\n") + err.what(), "Error", MB_OK | MB_ICONERROR);
		m_state = FILE_ERROR;
		return;
	}
	catch (...) {
		mainLogic::messageBox("An unknown error has occured while reading the file", "Error", MB_OK | MB_ICONERROR);
		m_state = UNKNOWN_ERROR;
		return;
	}

	try {
		if (std::string(".dat") == (filename.data() + filename.size() - 4)) {
			m_handling = parseDat(data);
			m_state = GOOD_OLD;
		}
		else if (std::string(".meta") == (filename.data() + filename.size() - 5)) {
			m_handling = parseMeta(data);
			m_state = GOOD_NEW;
		}
		else throw std::runtime_error("Unknown file format");
	}
	catch (const std::runtime_error& err) {
		mainLogic::messageBox(std::string("Error while parsing the file:\n") + err.what(), "Error", MB_OK | MB_ICONERROR);
		m_state = PARSING_ERROR;
	}
	catch (...) {
		mainLogic::messageBox("An unknown error has occured during parsing", "Error", MB_OK | MB_ICONERROR);
		m_state = UNKNOWN_ERROR;
	}

	if (m_handling.empty()) {
		m_state = PARSING_ERROR;
		mainLogic::messageBox("An unknown error has occured during parsing", "Error", MB_OK | MB_ICONERROR);
	}
}

handling::handling() {}

handling::handlingSet_t& handling::handlingData() {
	return m_handling;
}

bool handling::isEqual(const value_t& valueA, const value_t& valueB) {
	if ((valueA.index() != valueB.index())) return false;

	if (valueA.index() == 0) {
		return std::get<0>(valueA) == std::get<0>(valueB);
	}
	else if (valueA.index() == 1) {
		return std::get<1>(valueA) == std::get<1>(valueB);
	}
	else if (valueA.index() == 2) {
		return std::get<2>(valueA) == std::get<2>(valueB);
	}
	else /* index is 3 */ {
		return std::get<3>(valueA) == std::get<3>(valueB);
	}
}

handling::objectState handling::state() {
	return m_state;
}

std::string handling::toString(const value_t& val) {
	auto fToString = [](double v) {
		auto ret = std::to_string(v);
		if (ret.find('.') != std::string::npos) {
			auto it = std::prev(std::end(ret));
			size_t n{ 0 };
			while (*it == '0') { n++; it--; }
			if (*it == '.') n--;
			ret.resize(ret.size() - n);
		}
		return ret;
	};
	if (val.index() == 0) {
		// double
		return fToString(std::get<0>(val));
	}
	else if (val.index() == 1) {
		// uint32_t
		return std::to_string(std::get<1>(val));
	}
	else if (val.index() == 2) {
		// dvec3_t
		auto v = std::get<2>(val);
		return
			std::string("[ ") +
			"x=" + fToString(v.x) + ", " +
			"y=" + fToString(v.y) + ", " +
			"z=" + fToString(v.z) + std::string(" ]");
	}
	else if (val.index() == 3) {
		// string
		return std::get<3>(val);
	}
	else return {};
}

std::string handling::toString(const value_t& val, const std::string& name) {
	if (name == "strHandlingFlags" || name == "strModelFlags" || name == "strDamageFlags") {
		auto intValue = std::get<1>(val);
		char buffer[32];
		sprintf(buffer, "%X", intValue);
		return buffer;
	}
	else return toString(val);
}

handling::handlingSet_t handling::parseDat(const std::string& data) {
	handlingSet_t ret;
	std::stringstream currentLine;

	size_t lineEnd{ 0 };

	auto getNextLine = [&]() {
		auto tmpPos = data.find("\n", lineEnd);
		if (tmpPos == std::string::npos) {
			return false;
		} else {
			currentLine = std::stringstream(data.substr(lineEnd, tmpPos - lineEnd));
			lineEnd = tmpPos + 1;
			return true;
		}
	};

	while (getNextLine()) {
		std::string vehicleName;
		currentLine >> vehicleName;
		if (vehicleName.empty()) continue;

#pragma warning( push )
#pragma warning( disable : 4309)

		auto firstChar = vehicleName.front();
		if (firstChar == ';' ||
			firstChar == '%' ||
			firstChar == '!' ||
			firstChar == '$' ||
			firstChar == static_cast<char>(163) || // Pound symbol
			firstChar == '*' ||
			firstChar == '&' ||
			firstChar == '@' ||
			firstChar == '^') continue;

#pragma warning( pop )

		handling_t tmpFieldSet;
		
		for (auto&& fieldDescription : fieldTypeTable) {
			if (fieldDescription.first == "fTractionCurveLongitudinal")
				continue;
			tmpFieldSet[fieldDescription.first] = extractDatField(currentLine, fieldDescription.second);
		}

		ret[vehicleName] = tmpFieldSet;
	}

	return ret;
}

handling::handlingSet_t handling::parseMeta(const std::string& data) {

	// Didn't feel like using a full-blown XML parser library, so this loop just looks for the value names basically

	static const std::string nameStartStr("<handlingName>");
	static const std::string nameEndStr("</handlingName>");
	static const std::string entryEndStr("</Item>");

	handlingSet_t ret;
	size_t pos{ 0 };

	while ((pos = data.find(nameStartStr, pos)) != std::string::npos) {
		auto nameBeginPos = pos + nameStartStr.size();
		auto nameEndPos = data.find(nameEndStr, nameBeginPos);
		if (nameEndPos == std::string::npos) throw std::runtime_error("Incomplete name field");
		auto entryEndPos = data.find(entryEndStr, nameEndPos);
		if (entryEndPos == std::string::npos) throw std::runtime_error("Incomplete entry");
		entryEndPos += entryEndStr.size();
		auto vehicleName = data.substr(nameBeginPos, nameEndPos - nameBeginPos);
		auto fieldSearchBegin = nameEndPos + nameEndStr.size();
		handling_t tmpFieldSet;

		for (auto&& fieldDescription : fieldTypeTable) {
			if (fieldDescription.first == "fTractionCurveLongitudinal" || fieldDescription.first == "nAnimGroup" || fieldDescription.first == "vecCOMAbs")
				continue;
			auto fieldPos = data.find(fieldDescription.first, fieldSearchBegin);
			if (fieldPos == std::string::npos) throw std::runtime_error("Unable to find data field");
			tmpFieldSet[fieldDescription.first] = extractMetaField(data, fieldPos, fieldDescription.second);
		}

		if (tmpFieldSet.empty()) throw std::runtime_error("No valid data fields were found in vehicle entry");

		ret[vehicleName] = tmpFieldSet;

		pos = entryEndPos; // Never delete this line
	}

	return ret;
}

handling::value_t handling::extractMetaField(const std::string& data, size_t fieldBegin, handling::dataType fieldType) {
	handling::value_t ret;
	size_t b{}, e{}, b2{}, e2{}, b3{}, e3{};

	switch (fieldType) {
	case handling::dataType::FLOATING_POINT:
		b = data.find("=\"", fieldBegin) + 2;
		e = data.find("\"", b);
		ret = std::stod(data.substr(b, e - b));
		break;
	case handling::dataType::INTEGER:
		b = data.find("=\"", fieldBegin) + 2;
		e = data.find("\"", b);
		ret = static_cast<uint32_t>(std::stoul(data.substr(b, e - b)));
		break;
	case handling::dataType::VECTOR3:
		b = data.find("x=\"", fieldBegin) + 3;
		e = data.find("\"", b);
		b2 = data.find("y=\"", e) + 3;
		e2 = data.find("\"", b2);
		b3 = data.find("z=\"", e2) + 3;
		e3 = data.find("\"", b3);
		ret = handling::dvec3_t{ stod(data.substr(b, e - b)), stod(data.substr(b2, e2 - b2)), stod(data.substr(b3, e3 - b3)) };
		break;
	case handling::dataType::HANDLING_FLAGS:
		[[fallthrough]];
	case handling::dataType::MODEL_FLAGS:
		[[fallthrough]];
	case handling::dataType::DAMAGE_FLAGS:
		b = data.find(">", fieldBegin) + 1;
		e = data.find("<", b);
		ret = static_cast<uint32_t>(std::stoul(data.substr(b, e - b), nullptr, 0x10));
		break;
	case handling::dataType::STRING:
		b = data.find(">", fieldBegin) + 1;
		e = data.find("<", b);
		ret = data.substr(b, e - b);
		break;
	default:
		break;
	}

	return ret;
}

handling::value_t handling::extractDatField(std::stringstream& data, dataType fieldType) {
	value_t ret;

	double d{ 0.0 }, x{ 0.0 }, y{ 0.0 }, z{ 0.0 };
	uint32_t i{ 0 };
	std::string str;

	switch (fieldType) {
	case handling::dataType::FLOATING_POINT:
		data >> d;
		ret = d;
		break;
	case handling::dataType::VECTOR3:
		data >> x >> y >> z;
		ret = dvec3_t{ x, y, z };
		break;
	case handling::dataType::HANDLING_FLAGS:
		[[fallthrough]];
	case handling::dataType::MODEL_FLAGS:
		[[fallthrough]];
	case handling::dataType::DAMAGE_FLAGS:
		data >> std::hex >> i;
		ret = i;
		break;
	case handling::dataType::INTEGER:
		data >> i;
		ret = i;
		break;
	case handling::dataType::STRING:
		data >> str;
		ret = str;
		break;
	default:
		break;
	}

	return ret;
}
