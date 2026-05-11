#include "items.h"

namespace gui::framework
{
bool RealItemPath::canRender(const RealItemPath& other)
{
    return tab == other.tab 
        && subTab == other.subTab 
        && childCategory == other.childCategory;
}

ItemCheckBox::ItemCheckBox(CheckBox* itemPtr, RealItemPath realItemPath, luaItemPath luaItemPath)
    : luaPath(luaItemPath), realItemPath(realItemPath), itemPtr(itemPtr), itemType(itemPtr->item.itemType) {}

int ItemCheckBox::getItemType()
{
    return itemType;
}

RealItemPath ItemCheckBox::getRealItemPath()
{
    return realItemPath;
}

void* ItemCheckBox::getItemPtr() 
{
    return reinterpret_cast<void*>(itemPtr);
}

void ItemCheckBox::createKey() 
{
    luaItemKey.path = getLuaItemPath(luaPath);
    luaItemKey.hash = getLuaItemKey(luaPath);
}

fnv64Hash ItemCheckBox::getLuaKey() 
{
    return luaItemKey.hash;
}

std::string ItemCheckBox::getLuaPath()
{
    return luaItemKey.path;
}


}