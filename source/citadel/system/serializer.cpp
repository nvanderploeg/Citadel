
#include "citadelSystem.h"

namespace citadel {

    Json::Value Serializer::loadFile(const std::filesystem::path & filePath)
    {
		// TODO: is getResourcePath necessary with std::filesystem?
        std::ifstream stream(getResourcePath() + filePath.string(), std::ifstream::binary);
        if (!stream)
        {
            return Json::nullValue;
        }
        
        Json::Value jRoot;
        Json::Reader jReader;
        if (!jReader.parse(stream, jRoot))
        {
            stream.close();
            return Json::nullValue;
        }
        stream.close();
        
        return jRoot;
    }

    bool Serializer::serialize(IJSONSerializable * pObject, const std::filesystem::path & filepath)
    {
		// TODO: is getResourcePath necessary with std::filesystem?
        std::ofstream stream(getResourcePath() + filepath.string());
		return serialize(pObject, stream);
    }

	bool Serializer::serialize(IJSONSerializable * pObject, std::ofstream & stream)
	{
		if (pObject == nullptr)
		{
			return false;
		}

		//TODO: validate filestream

		Json::Value jRoot;
		pObject->serialize(jRoot);

		Json::StyledStreamWriter jWriter;
		jWriter.write(stream, jRoot);

		return true;
	}
    
    bool Serializer::deserialize(IJSONSerializable *& pObject, const std::filesystem::path & filepath)
    {
		// TODO: is getResourcePath necessary with std::filesystem?
        std::ifstream stream(getResourcePath() + filepath.string(), std::ifstream::binary);
		return deserialize(pObject, stream);
    }

	bool Serializer::deserialize(IJSONSerializable *& pObject, std::ifstream & stream)
	{
		if (pObject != nullptr)
		{
			return false;
		}

		//TODO: validate filestream

		Json::Value jRoot;
		Json::Reader jReader;

		if (!jReader.parse(stream, jRoot))
		{
			return false;
		}

		uint32_t type = jRoot["type"].asUInt();
		auto serializedTypeObjectMap = Serializer::getSerializableTypeObjectMap();
		if (serializedTypeObjectMap.find(type) != serializedTypeObjectMap.end())
		{
			pObject = Serializer::getSerializableTypeObjectMap()[type](jRoot);
		}

		return true;
	}

    std::map<uint32_t, std::function<IJSONSerializable*(const Json::Value&)> >& Serializer::getSerializableTypeObjectMap()
    {
        static std::map<uint32_t, std::function<IJSONSerializable*(const Json::Value&)> > s_serializableTypObjectMap;
        return s_serializableTypObjectMap;
    }

} // namespace citadel
