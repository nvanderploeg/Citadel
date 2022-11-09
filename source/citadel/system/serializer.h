#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#include <filesystem>
#include "JSONSerializable.h"

namespace citadel {
    
    class Serializer
    {
    private:
        Serializer() { }
        
    public:
        
        //TODO change fileput to input/output strings, and create additional methods to read/write to files
        static bool serialize(IJSONSerializable* pObject, const std::filesystem::path & filepath);
		static bool serialize(IJSONSerializable* pObject, std::ofstream& stream);
        static bool deserialize(IJSONSerializable*& pObject, const std::filesystem::path & filepath);
		static bool deserialize(IJSONSerializable*& pObject, std::ifstream& stream);
        
        static std::map<uint32_t, std::function<IJSONSerializable*(const Json::Value&)> >& getSerializableTypeObjectMap();
        
        static Json::Value loadFile(const std::filesystem::path & filePath);
    }; // class Serializer
    
} // namespace citadel

#endif // __SERIALIZER_H__
