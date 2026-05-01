#pragma once
#include "window.h"

namespace gui::framework
{
class BindsWindow : public IWindow
{
public:
    BindsWindow(std::string name, ImVec2 size) : name(name), size(size) {}

    void init() override;
    void render() override;
    void updateWindowPosOrSize() override;

    std::string getName() override;
    ImVec2 getPos() override;
    ImVec2 getWindowSize() override;

private:
    std::unordered_map<void*, std::pair<void*, int>> items{};
    std::string name{};
    ImVec2 pos{};
    ImVec2 size{};
};
}