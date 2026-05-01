#include <iostream>
#include <string>
#include "gui.h"
#include "framework/window.h"
#include "framework/bindsWindow.h"
#include "framework/mainWindow.h"

#include "../main/dllInstance.h"

#include "../guiItems/items.h"
#include "../config/config.h"

namespace gui
{
using namespace framework;

enum DPI_SCALE_AMOUNT
{
    DPI_100 = 0,
    DPI_125,
    DPI_150,
    DPI_200
};

void init()
{
    getMenuInstance().initConfig();
    getMenuInstance().initWindows();
    binds::initBinds();
}

void destroy()
{
    binds::destroyBinds();
    getMenuInstance().windows.clear();
}

void MenuDpiManager::saveUiPos(const std::string& name)
{
    auto& windows = getMenuInstance().windows;
    auto existingWindow = std::find_if(windows.begin(), windows.end(), [name](const std::shared_ptr<IWindow>& window) {
        return window->getName() == name;
    });

    if (existingWindow != windows.end())
        lastPositions.emplace_back(std::make_pair(name, (*existingWindow)->getPos()));
}

void MenuDpiManager::correctSavedUIPos(const std::string& name)
{
    if (lastPositions.empty())
        return;

    auto existingUI = std::find_if(lastPositions.begin(), lastPositions.end(),
        [name](const windowNamePosValue& item)
        {
            return item.has_value() && item->first == name;
        });

    if (existingUI != lastPositions.end())
    {
        ImGui::SetNextWindowPos(existingUI->value().second);
        lastPositions.erase(existingUI);
    }
}

void MenuDpiManager::updateDpiScale()
{
    static float prevDpi = 1.f;

    switch (getMenuInstance().dpiScale.item.value)
    {
    case DPI_100:
        framework::DPI_SCALE = 1.f;
        break;
    case DPI_125:
        framework::DPI_SCALE = 1.25f;
        break;
    case DPI_150:
        framework::DPI_SCALE = 1.5f;
        break;
    case DPI_200:
        framework::DPI_SCALE = 2.f;
        break;
    }

    if (prevDpi != framework::DPI_SCALE)
    {
        auto& windows = getMenuInstance().windows;
        for (auto& window : windows)
            saveUiPos(window->getName());

        render::getRenderInfoInstance().init = false;
        render::destroy();
        render::clearRenderTargetView();
        prevDpi = framework::DPI_SCALE;
    }
}

void Menu::initWindows()
{
    using namespace framework;
    windows.emplace_back(std::make_shared<BindsWindow>("BIND LIST", ImVec2{}));
    windows.emplace_back(std::make_shared<MainWindow>(tabsList{
        "Rage",
        "Legit",
        "Visuals",
        "Misc", 
        "Skins", 
        "Configs", 
        "LUA" 
    }, "BMX09BXOIC - MAIN", MAIN_WINDOW_SIZE));

    for (auto window : windows)
        window->init();
}

void Menu::renderWindows()
{
    for (auto window : windows)
    {
        window->render();
        window->updateWindowPosOrSize();
    }
}

void Menu::destroyWindows()
{
    windows.clear();
}

Menu& getMenuInstance()
{
    static Menu instance;
    return instance;
}

void Menu::initConfig()
{
    for (int i = 0; i < MAX_CONFIGS; ++i)
    {
        auto index = std::to_string(i);
        rage.config[i].autoFire = MAKE_CHECKBOX_RT("Auto Fire##rage" + index, false);
        rage.config[i].autoScope = MAKE_CHECKBOX_RT("Auto Scope##rage" + index, false);
        rage.config[i].fov = MAKE_SLIDER_RT("Field of View##rage" + index, 180, 0, 180);
        rage.config[i].hitBoxes = MAKE_MULTICOMBO_RT("Hit Boxes##rage" + index, 0, COMBO_LIST("Head", "Neck", "Chest", "Pelvis", "Stomach", "Arms", "Legs", "Feet"));
        rage.config[i].multiPoints = MAKE_MULTICOMBO_RT("Multi Points##rage" + index, 0, COMBO_LIST("Head", "Neck", "Chest", "Pelvis", "Stomach", "Arms", "Legs", "Feet"));
        rage.config[i].pointHeadScale = MAKE_SLIDER_RT("Head Scale##rage" + index, 0, 0, 100);
        rage.config[i].pointBodyScale = MAKE_SLIDER_RT("Body Scale##rage" + index, 0, 0, 100);
        rage.config[i].hitChance = MAKE_SLIDER_RT("Hit Chance##rage" + index, 0, 0, 100);
        rage.config[i].minDamage = MAKE_SLIDER_RT("Min Damage##rage" + index, 0, 0, 100);
        rage.config[i].preferBody = MAKE_CHECKBOX_RT("Prefer Body##rage" + index, false);
        rage.config[i].quickStop = MAKE_MULTICOMBO_RT("Quick Stop##rage" + index, 0, COMBO_LIST("Early", "Between Shots", "In Air", "Ignore Molotov"));
        rage.config[i].overrideGlobal = MAKE_CHECKBOX_RT("Override Global##rage" + index, false);

        itemsInMemory.emplace_back(ITEM_PTR_RT(rage.config[i].autoFire));
        itemsInMemory.emplace_back(ITEM_PTR_RT(rage.config[i].autoScope));
        itemsInMemory.emplace_back(ITEM_PTR_RT(rage.config[i].fov));
        itemsInMemory.emplace_back(ITEM_PTR_RT(rage.config[i].multiPoints));
        itemsInMemory.emplace_back(ITEM_PTR_RT(rage.config[i].pointHeadScale));
        itemsInMemory.emplace_back(ITEM_PTR_RT(rage.config[i].pointBodyScale));
        itemsInMemory.emplace_back(ITEM_PTR_RT(rage.config[i].hitChance));
        itemsInMemory.emplace_back(ITEM_PTR_RT(rage.config[i].minDamage));
        itemsInMemory.emplace_back(ITEM_PTR_RT(rage.config[i].preferBody));
        itemsInMemory.emplace_back(ITEM_PTR_RT(rage.config[i].quickStop));
        itemsInMemory.emplace_back(ITEM_PTR_RT(rage.config[i].overrideGlobal));
    }

    itemsInMemory.emplace_back(ITEM_PTR_RT(rage.enable));
    itemsInMemory.emplace_back(ITEM_PTR_RT(rage.autoRevolver));
    itemsInMemory.emplace_back(ITEM_PTR_RT(rage.doubleTap));
    itemsInMemory.emplace_back(ITEM_PTR_RT(rage.noSpread));
    itemsInMemory.emplace_back(ITEM_PTR_RT(rage.duckPeekAssist));
    itemsInMemory.emplace_back(ITEM_PTR_RT(rage.configSelect));
}
}