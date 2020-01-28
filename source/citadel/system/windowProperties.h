#pragma once
#include "JSONSerializable.h"

namespace citadel {
	class WindowProperties : public IJSONSerializable
	{
	private:
		static const uint32_t DEFAULT_WIDTH = 640;
		static const uint32_t DEFAULT_HEIGHT = 480;
		static const std::string DEFAULT_TITLE;
		static const uint32_t DEFAULT_MAXFPS = 60;

	public:
		uint32_t width;
		uint32_t height;
		uint32_t maxFPS;
		std::string title;

	public:
		WindowProperties();
		WindowProperties(uint32_t _width, uint32_t _height, const std::string & _title = DEFAULT_TITLE, uint32_t _maxFPS = DEFAULT_MAXFPS);

		virtual void serialize(Json::Value& jValue);
		virtual void deserialize(const Json::Value& jValue);
	};
} // namespace citadel
