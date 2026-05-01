#include "mainWindow.h"

#include "../gui.h"
#include "../item.h"
#include "../../guiItems/items.h"
#include "../../main/dllInstance.h"

#include "../../guiItems/items.h"
#include "../../config/config.h"

namespace gui::framework
{
// TO-DO:
// subtabs (made as child) +
// MAIN (with weapon config) + 
// ANTI-AIM (stand/move/air/crouch/slowwalk) +
void renderSubTabs(const std::vector<std::string>& tabs, int& selection)
{
    ImGui::BeginGroup();
    for (int i = 0; i < tabs.size(); ++i)
    {
        if (ImGui::Button(tabs[i].c_str(), ImVec2(tabs[i].length() * 10, 18)))
            selection = i;

        ImGui::SameLine();
    }
    ImGui::EndGroup();
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
}

void renderRageTab()
{
    ImVec2 weaponitemsChildSize = ImVec2(374 * DPI_SCALE, 440 * DPI_SCALE);
    ImVec2 mainChildSize = ImVec2(weaponitemsChildSize.x, weaponitemsChildSize.y * 0.272f);
    ImVec2 antiAimChildSize = ImVec2(weaponitemsChildSize.x, weaponitemsChildSize.y * 0.95f);
    ImVec2 configChildSize = ImVec2(weaponitemsChildSize.x, 60 * DPI_SCALE);

    ImGui::BeginGroup();
    {
        ImGui::BeginChild("Main##rage", mainChildSize, ImGuiChildFlags_Borders, ImGuiWindowFlags_NoScrollbar);
        {
            checkbox::render(getMenuInstance().rage.enable);
            checkbox::render(getMenuInstance().rage.autoRevolver);
            checkbox::render(getMenuInstance().rage.doubleTap);
            checkbox::render(getMenuInstance().rage.noSpread);
            checkbox::render(getMenuInstance().rage.duckPeekAssist);
        }
        ImGui::EndChild();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::BeginChild("Anti Aim##rage", antiAimChildSize, ImGuiChildFlags_Borders, ImGuiWindowFlags_NoScrollbar);
        {
            checkbox::render(getMenuInstance().rage.antiAim.enable);
            checkbox::render(getMenuInstance().rage.antiAim.atTarget);
            combobox::render(getMenuInstance().rage.antiAim.pitch);
            combobox::render(getMenuInstance().rage.antiAim.yaw);
            combobox::render(getMenuInstance().rage.antiAim.jitter);
            slider::render(getMenuInstance().rage.antiAim.jitterOffset);
            slider::render(getMenuInstance().rage.antiAim.yawOffset);

            ImGui::BeginGroup();
            {
                checkbox::render(getMenuInstance().rage.antiAim.freestanding);
                ImGui::SameLine();

                if (ImGui::SmallButton("..."))
                {
                    ImGui::OpenPopup("freestand-popup");
                }

                if (ImGui::BeginPopup("freestand-popup"))
                {
                    checkbox::render(getMenuInstance().rage.antiAim.zeroOnPeek);
                    ImGui::EndPopup();
                }
            }
            ImGui::EndGroup();
        }
        ImGui::EndChild();
    }
    ImGui::EndGroup();

    ImGui::SameLine();

    ImGui::BeginGroup();
    {
        ImGui::BeginChild("Weapon Config Selector##rage", configChildSize, ImGuiChildFlags_Borders, ImGuiWindowFlags_NoScrollbar);
        {
            ImGui::PushItemWidth(configChildSize.x * 0.958f);
            combobox::render(getMenuInstance().rage.configSelect);
            ImGui::PopItemWidth();
        }
        ImGui::EndChild();
        ImGui::Spacing();
        ImGui::BeginChild("Weapon Config##rage", weaponitemsChildSize, ImGuiChildFlags_Borders, ImGuiWindowFlags_NoScrollbar);
        {
            auto& itemFromWeaponConfig = getMenuInstance().rage.config[getMenuInstance().rage.configSelect.item.value];

            ImGui::PushItemWidth(configChildSize.x * 0.958f);
            if (getMenuInstance().rage.configSelect.item.value != 0)
                checkbox::render(itemFromWeaponConfig.overrideGlobal);

            checkbox::render(itemFromWeaponConfig.autoFire);
            checkbox::render(itemFromWeaponConfig.autoScope);
            slider::render(itemFromWeaponConfig.fov);
            multicombobox::render(itemFromWeaponConfig.hitBoxes);
            multicombobox::render(itemFromWeaponConfig.multiPoints);
            slider::render(itemFromWeaponConfig.pointHeadScale);
            slider::render(itemFromWeaponConfig.pointBodyScale);
            checkbox::render(itemFromWeaponConfig.preferBody);
            slider::render(itemFromWeaponConfig.hitChance);
            slider::render(itemFromWeaponConfig.minDamage);
            multicombobox::render(itemFromWeaponConfig.quickStop);
            ImGui::PopItemWidth();
        }
        ImGui::EndChild();
    }
    ImGui::EndGroup();
}

void renderLegitTab()
{

}

void renderVisualsTab()
{

}

void renderMiscTab()
{

}

void renderSkinsTab()
{
}

void renderConfigsTab()
{
    ImGui::BeginGroup();
    {
        combobox::render(getMenuInstance().dpiScale);

        if (ImGui::SmallButton("Save"))
            config::saveConfig();
        ImGui::SameLine();
        if (ImGui::SmallButton("Load"))
            config::loadConfig();
    }
    ImGui::EndGroup();

#ifdef _DEBUG
    if (ImGui::SmallButton("Unload"))
        getDllInstance().shouldQuit = true;
#endif
}

void renderLUATab()
{
}

void MainWindow::init()
{
 
}

// TO-DO: different layout that allows to handle multiple sections at the same time
// for example:
// RAGE MAIN:
// [ Main child with enable / exploits ] + 
// [ Weapon config ] + 
// ANTI AIM MAIN:
// [ Main Child with pitch yaw (offset) jitter (offset) at target ] +
// [ Misc Child with freestanding edge ] +
void MainWindow::render()
{
    if (!getMenuInstance().opened)
        return;

    getMenuInstance().dpiManager.correctSavedUIPos(name);
    ImGui::SetNextWindowSize(size * DPI_SCALE);

    render::pushFont(FONT_LOGO);
    ImGui::Begin(name.c_str(), &getMenuInstance().opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    render::popFont();

    {
        using namespace gui::items;
        render::pushFont(FONT_ITEMS);
        ImGui::BeginGroup();
        for (int i = 0; i < tabs.size(); ++i)
        {
            if (ImGui::Button(tabs[i].c_str(), ImVec2(tabs[i].length() * 10.f * DPI_SCALE, 18 * DPI_SCALE)))
                tabSelection = i;

            ImGui::SameLine();
        }
        ImGui::EndGroup();
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::BeginGroup();
        {
            switch (tabSelection)
            {
            case TAB_RAGE:
                renderRageTab();
                break;
            case TAB_LEGIT:
                renderLegitTab();
                break;
            case TAB_VISUALS:
                renderVisualsTab();
                break;
            case TAB_MISC:
                renderMiscTab();
                break;
            case TAB_SKINS:
                renderSkinsTab();
                break;
            case TAB_CONFIGS:
                renderConfigsTab();
                break;
            case TAB_LUA:
                renderLUATab();
                break;
            }
        }
        ImGui::EndGroup();
        render::popFont();
    }
    ImGui::End();
}

void MainWindow::updateWindowPosOrSize()
{
    const auto latestWindow = GImGui->Windows.back();
    pos = latestWindow->Pos;
}

std::string MainWindow::getName()
{
    return name;
}

ImVec2 MainWindow::getPos()
{
    return pos;
}

ImVec2 MainWindow::getWindowSize()
{
    return size;
}
}