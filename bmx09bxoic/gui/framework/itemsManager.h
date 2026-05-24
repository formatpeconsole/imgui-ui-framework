#pragma once

#include "uiItem.h"
#include "../../guiItems/utils.h"
#include "../../render/animation/animation.h"

namespace gui::framework
{
using namespace items;

namespace
{
constexpr auto MAX_ITEMS = 1000;
}

enum UI_TABS
{
    TAB_RAGE = 0,
    TAB_LEGIT,
    TAB_VISUALS,
    TAB_MISC,
    TAB_SKINS,
    TAB_CONFIGS,
    TAB_LUA
};

enum UI_RAGE_SUB_TABS
{
    SUBTAB_RAGE_AIMBOT = 0,
    SUBTAB_RAGE_ANTIAIM
};

enum CHILD_ANIMATION
{
    CHILD_SECOND = 0,
    CHILD_THIRD,
};

enum CHILD_CATEGORY
{
    CHILD_CATEGORY_FIRST = 0,
    CHILD_CATEGORY_SECOND,
    CHILD_CATEGORY_THIRD,
};

struct tabAnimation
{
    ImVec4 radioButton{ 0.0f, 0.0f, 0.0f, 0.0f };
    ImVec4 text{ 0.0f, 0.0f, 0.0f, 0.0f };

    render::Animation radioAnimation{ 100.f, 0.f, 0.15f, render::ANIMATION_EASE_OUT_EXPO };
    float radioGlowAlpha{ 0.f };
};

using subTabChilds = std::vector<std::string>;
struct subTab
{
    subTabChilds childs{};
    tabAnimation tabAnim{};
    std::string name{};
    int childCount{};

    subTab(std::string name, subTabChilds childsList)
        : name(name), childs(childsList)
    {
        childCount = childs.size();
    }
};

struct tabItself
{
    std::vector<subTab> subTabs{};
    tabAnimation tabAnim{};
    std::string name{};
    int subTabSelection{};
    bool noSubTabs = false;

    tabItself(std::vector<subTab> subTabs, std::string name, bool noSubTabs) :
        subTabs(subTabs), name(name), subTabSelection(0), noSubTabs(noSubTabs) {
    }

    ~tabItself() {}
};

using tabsList = std::vector<tabItself>;
using itemsList = std::list<baseItemPtr>;

class ItemsManager
{
public:
    ItemsManager();
    ~ItemsManager();
    tabsList& getMainWindowTabsList();
    itemsList& getItemsList();
    std::optional<RealItemPath> getRealItemPath(itemPath& path);

    template<typename T>
    void placeItem(T* ptr, itemPath&& path, isVisibleFn&& isVisible)
    {
        if (const auto size = items.size(); size >= MAX_ITEMS)
        {
#ifdef _DEBUG
            std::string message = "Wrong " + ptr->item.name + " Path!";
            assert(false && "Too much items. Please look at place where you allocate them!");
#endif

            return;
        }

        itemPath newPath{ std::forward<itemPath>(path) };
        newPath.emplace_back(gui::items::getFormattedText(ptr->item.name));

        auto realItemPath = getRealItemPath(newPath);
        if (!realItemPath.has_value())
        {
#ifdef _DEBUG
            std::string message = "Wrong " + ptr->item.name + " Path!";
            assert(false && message.c_str());
#endif
            return;
        }
        items.emplace_back(std::make_shared<UiItem<T>>(ptr, realItemPath.value(), newPath, std::forward<isVisibleFn>(isVisible)));
    }

private:
    tabsList tabs{};
    itemsList items{};
};

extern ItemsManager& getItemsManagerInstance();
}