#pragma once
#include <functional>

#include "../../render/animation/animation.h"
#include "../../guiItems/utils.h"

#include "window.h"
#include "uiItem.h"
#include "itemsManager.h"

namespace gui::framework
{
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
    ImVec2 baseTabs{ 33.f, 79.f };
    ImVec2 baseTabsContents{ 208.f, 0.f };
    ImVec2 baseSubTabsContents{ 220.f, 25.f };
};

struct tabContentsAnimation
{
    float yPos{};
    float ySize{};
    float xChildSize{};
    float yChildSize{};
    float ySubChildFactor{};
    float subChildsAlpha[2]{};

    render::Animation yPosAnimation{ 59.f, 26.f, 0.35f, render::ANIMATION_EASE_OUT_EXPO };
    render::Animation ySizeAnimation{ 437.f, 470.f, 0.35f, render::ANIMATION_EASE_OUT_EXPO };
    render::Animation xChildSizeAnimation{ 219.f, 451.f, 0.3f, render::ANIMATION_EASE_OUT_EXPO };
    render::Animation yChildSizeAnimation{ 410.f, 443.f, 0.35f, render::ANIMATION_EASE_OUT_EXPO };
    render::Animation selectedTabAnimation{ 0.f, 100.f, 0.35f, render::ANIMATION_EASE_OUT_EXPO, render::ANIMATION_FLAGS_REPLAY_FROM_START };
    render::Animation ySubChildFactorAnimation{ 100.f, 50.f, 0.35f, render::ANIMATION_EASE_OUT_EXPO };
    render::Animation subChildsAlphaAnimation[2]{
        { 100.f, 0.f, 0.35f, render::ANIMATION_EASE_OUT_QUAD },
        { 100.f, 0.f, 0.35f, render::ANIMATION_EASE_OUT_QUAD },
    };
};

class MainWindow : public IWindow
{
public:
    MainWindow(std::string name, ImVec2 size);
    ~MainWindow();

    void init() override;
    void render() override;
    void updateWindowPosOrSize() override;
    std::string getName() override;
    ImVec2 getPos() override;
    ImVec2 getWindowSize() override;

private:
    void initItems();
    void renderItem(const baseItemPtr& baseItem, const RealItemPath& currentItemPath);
    void renderChildContents(int selection, int subTabSelection, int childType);
    void updateTabsAnimation();
    void renderWindowContents();
    void renderTabs();
    void renderTabsContents();
    void renderBottomInfo();

    std::string getBuildType();
    std::string getBuildDate();

    int getMainAlpha();

    tabSelectionAnimation tabSelectionAnim{};
    mainPositions mainPos;
    tabContentsAnimation tabContentsAnim{};

    render::Animation uiOpenAnimation{ 0.f, 100.f, 0.1f, render::ANIMATION_EASE_OUT_QUAD };
    int tabSelection{};
    int oldTabSelection{};

    std::string name{};
    ImVec2 pos{};
    ImVec2 size{};
    float prevDpiScale{};
    float windowAlpha{};
};
}