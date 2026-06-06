#pragma once
#include <string>
#include <list>
#include <functional>
#include <optional>
#include <unordered_map>
#include <lua.hpp>

namespace lua
{
class LuaState
{
public:
    void init();
    void destroy();
    lua_State* getState();

    void executeScript(std::string path);

    std::string getLoadedLuaName();
    void setLoadedLuaName(const std::string& name);

private:

    std::string luaName{};
    lua_State* state{ nullptr };
};

extern LuaState& getLuaStateInstance();
}