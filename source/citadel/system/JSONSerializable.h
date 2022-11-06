
#ifndef __N0_IJSONSerializable_H__
#define __N0_IJSONSerializable_H__
#include "json/json.h"
#include <functional>

namespace citadel {

    class IJSONSerializable
    {
    public:
        IJSONSerializable() { }
        virtual ~IJSONSerializable() { }
        virtual void serialize(Json::Value& jValue) = 0;
        virtual void deserialize(const Json::Value& jValue) = 0;
        
    }; // class IJSONSerializable
    
#define SERIALIZABLE_FACTORY(type, id) \
    class type##Factory \
    { \
    public: \
        type##Factory() \
        { \
            Serializer::getSerializableTypeObjectMap()[id] = construct##type; \
        } \
        static type* construct##type(const Json::Value& jValue) \
        { \
            type* pObject = new type(); \
            pObject->deserialize(jValue); \
            return pObject; \
        } \
    }; \
    static type##Factory s_##type##Factory;

    

} // namespace citadel

#endif // __N0_IJSONSerializable_H__
