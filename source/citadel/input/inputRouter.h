#pragma once

#include <variant>
#include <functional>
#include <map>
#include <unordered_map>
#include <filesystem>

#include "GLFW/glfw3.h"

#include "JSONSerializable.h"

namespace citadel
{
    class KeyEvent
    {
    public:
        int keycode;
        int action;
        int modifiers;

        bool operator==(const KeyEvent& other) const
        {
            return (keycode == other.keycode && action == other.action && modifiers == other.modifiers);
        }
    };

    struct KeyEventHasher
    {
        std::size_t operator()(const KeyEvent& k) const
        {
            using std::hash;

            return ((hash<int>()(k.keycode)
                ^ (hash<int>()(k.action) << 1)) >> 1)
                ^ (hash<int>()(k.modifiers) << 1);
        }
    };

    class InputContext : public IJSONSerializable
    {
    public:
        std::unordered_map<KeyEvent, std::list<std::string>, KeyEventHasher> keyEventMap;

    public:
        InputContext();
        InputContext(const Json::Value& jValue);
        InputContext(const std::filesystem::path& path);

        void AddKeyBind(const KeyEvent& keyEvent, const std::string& label);

        virtual void serialize(Json::Value& jValue);
        virtual void deserialize(const Json::Value& jValue);
    };


    struct KeyEventData
    {
        int code;
        bool alt;
        bool control;
        bool shift;
        bool system;
    };

    struct MouseButtonEventData
    {
        int code;
        bool alt;
        bool control;
        bool shift;
        bool system;
    };

    struct MouseMoveEventData
    {
        int xPosition;
        int yPosition;
    };

    struct MouseScrollEventData
    {
        double xOffset;
        double yOffset;
    };

    typedef std::variant<KeyEventData, MouseButtonEventData, MouseMoveEventData, MouseScrollEventData> InputEventData;
    typedef std::function<bool(InputEventData&)> InputEventCallback;

    class InputRouter
    {
    public:
        std::map<std::string, std::list<InputEventCallback> > keyInputMap;
        std::shared_ptr<InputContext> inputContext;

    public:
        InputRouter();

        void BindToGLFW(GLFWwindow* window);

        void AddKeyBind(const std::string& label, const KeyEvent& keyEvent, InputEventCallback callback);
        void SetKeyCallback(const std::string& label, InputEventCallback callback);

        void SetInputContext(const Json::Value& jValue);
    };    
}
