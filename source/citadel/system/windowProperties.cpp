#include <string>

#include "JSONSerializable.h"
#include "windowProperties.h"

namespace
{
	const uint32_t DEFAULT_WIDTH = 640;
	const uint32_t DEFAULT_HEIGHT = 480;
	const std::string DEFAULT_TITLE = "citadel game";
	const uint32_t DEFAULT_MAXFPS = 60;
}

namespace citadel
{
	WindowProperties::WindowProperties()
		: width(DEFAULT_WIDTH)
		, height(DEFAULT_HEIGHT)
		, title(DEFAULT_TITLE)
		, maxFPS(DEFAULT_MAXFPS)
	{

	}

	WindowProperties::WindowProperties(uint32_t _width, uint32_t _height, const std::string & _title, uint32_t _maxFPS)
		: width(_width)
		, height(_height)
		, title(_title)
		, maxFPS(_maxFPS)
	{
		if (_title.empty())
			title = DEFAULT_TITLE;

		if (_maxFPS == 0)
			maxFPS = DEFAULT_MAXFPS;
	}

	void WindowProperties::serialize(Json::Value& jValue)
	{
		jValue["width"] = width;
		jValue["height"] = height;
		jValue["title"] = title;
		jValue["maxFPS"] = maxFPS;
	}

	void WindowProperties::deserialize(const Json::Value& jValue)
	{
		width = jValue.get("width", DEFAULT_WIDTH).asUInt();
		height = jValue.get("height", DEFAULT_HEIGHT).asUInt();
		title = jValue.get("title", DEFAULT_TITLE).asString();
		maxFPS = jValue.get("maxFPS", DEFAULT_MAXFPS).asUInt();
	}
} // namespace citadel
