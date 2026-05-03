#pragma once
#include "window.h"

namespace gui::framework
{
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

struct tabAnimation
{
    ImVec4 radioButton{};
    ImVec4 text{};

    float radioGlowAlpha{};
};

struct tabSelectionAnimation
{
    float xPos{};
    float yPos{ 0.f };
    float beginPosY{};

    ImVec2 base{ 119.f, 87.f };
    ImVec2 first{ 50.f, 0.f };
    ImVec2 second{ 62.f, 7.f };
    ImVec2 third{ 50.f, 14.f };
};

struct mainPositions
{
    ImVec2 baseTabs{ 34.f, 84.f };
    ImVec2 baseTabsContents{ 205.f, 56.f };
    ImVec2 logo{ 33.f, 22.f };
};

struct tabContentsAnimation
{
    float yPos{};
    float ySize{};
};

using tabItself = std::pair<std::string, bool>;
using tabsList = std::vector<tabItself>;
using tabAnimationsList = std::vector<tabAnimation>;

class MainWindow : public IWindow
{
public:
    MainWindow(tabsList tabs, std::string name, ImVec2 size);
    ~MainWindow();

    void init() override;
    void render() override;
    void updateWindowPosOrSize() override;
    std::string getName() override;
    ImVec2 getPos() override;
    ImVec2 getWindowSize() override;

private:
    void renderWindowContents();
    void renderTabs();
    void renderTabsContents();
    void renderLogo();
    void renderBottomInfo();

    std::string getBuildType();
    std::string getBuildDate();

    int getMainAlpha();

    std::unordered_map<void*, std::pair<void*, int>> items{};
    tabAnimationsList tabsAnimations{};
    tabsList tabs{};

    tabSelectionAnimation tabSelectionAnim{};
    mainPositions mainPos;
    tabContentsAnimation tabContentsAnim{};
    int tabSelection{};

    std::string name{};
    ImVec2 pos{};
    ImVec2 size{};
    float prevDpiScale{};
    float windowAlpha{};
};
}