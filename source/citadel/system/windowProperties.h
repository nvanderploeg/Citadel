#pragma once
#include "JSONSerializable.h"

namespace citadel {
	class WindowProperties : public IJSONSerializable
	{
	public:
		uint32_t width;
		uint32_t height;
		uint32_t maxFPS;
		std::string title;

	public:
		WindowProperties();
		WindowProperties(uint32_t _width, uint32_t _height, const std::string & _title = "", uint32_t _maxFPS = 0);

		virtual void serialize(Json::Value& jValue);
		virtual void deserialize(const Json::Value& jValue);
	};
} // namespace citadel
