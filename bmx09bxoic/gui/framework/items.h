#pragma once
#include <sstream>

#include "window.h"
#include "../item.h"

#include "../../deps/fnv64hash/hash.h"

namespace gui::framework
{
using namespace items;

// get item key that stores in hash
// key containts full path to item
//
// for example:
//
// checkbox "Enable" that located at "Ragebot->Aimbot->Main(groupbox)"
// full key will look like:
// ragebot-aimbot-main-enable
using luaItemPath = std::vector<std::string>;
inline fnv64Hash getLuaItemKey(luaItemPath path)
{
    std::string key{};
    bool first = true;
    for (auto item : path)
    {
        std::transform(item.begin(), item.end(), item.begin(), [](char c) { return std::tolower(c); });

        if (!first)
            key += "-";

        key += item;
        first = false;
    }

    return fnv64::fnv1a_hash(key);
}

// get full path to make key
// 
// for example:
//
// checkbox "Enable" that located at "Ragebot->Aimbot->Main(groupbox)"
// full key will look like:
// "Ragebot", "Aimbot", "Main", "Enable"
inline std::string getLuaItemPath(luaItemPath path)
{
    std::ostringstream oss{};
    bool first = true;

    for (auto item : path)
    {
        if (!first) 
            oss << ", ";

        oss << '"' << item << '"';
        first = false;
    }

    return oss.str();
}

struct LuaItemKey
{
    std::string path{};
    fnv64Hash hash{};
};

struct RealItemPath
{
    int tab{-1};
    int subTab{-1};
    int childCategory{-1};

    bool canRender(const RealItemPath& other);
};

class BaseItem
{
public:
    virtual int getItemType() = 0;
    virtual RealItemPath getRealItemPath() = 0;
    virtual void* getItemPtr() = 0;
    virtual void createKey() = 0;
    virtual fnv64Hash getLuaKey() = 0;
    virtual std::string getLuaPath() = 0;
};
using baseItemPtr = std::shared_ptr<BaseItem>;

class ItemCheckBox : public BaseItem
{
public:
    ItemCheckBox(CheckBox* itemPtr, RealItemPath realItemPath, luaItemPath luaItemPath);

    int getItemType() override;
    RealItemPath getRealItemPath() override;
    void* getItemPtr() override;
    void createKey() override;
    fnv64Hash getLuaKey() override;
    std::string getLuaPath() override;

private:
    luaItemPath luaPath{};
    RealItemPath realItemPath{};
    LuaItemKey luaItemKey{};
    CheckBox* itemPtr{};
    int itemType{};
};

}