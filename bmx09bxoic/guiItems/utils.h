#pragma once
#include <string>
#include "../gui/item.h"
#include "../gui/binds/utils.h"

#include "../deps/fnv64hash/hash.h"

namespace gui::items
{
// get item key that stores in hash
// key containts full path to item
//
// for example:
//
// checkbox "Enable" that located at "Ragebot->Aimbot->Main(groupbox)"
// full key will look like:
// ragebot-aimbot-main-enable
inline fnv64Hash getItemKey(std::vector<std::string> path)
{
    std::string key{};
    fnv64Hash result{};
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

// get text without hashtags for ui naming
// for example
// we have name of item in UI called "Hit Chance##rage"
// but ##rage is used just to make unique hash
// so for UI Bind list better visualize name without this unique hash
// in result it will be "Hit Chance"
inline std::string getFormattedText(const std::string& text)
{
    size_t pos = text.find("##");
    if (pos == std::string::npos)
        return text;

    return text.substr(0, pos);
}

template<typename T>
inline std::string getPreviewItemName(const BindValues<T>& value)
{
    if (value.bindKey > 0 && value.bindMode != -1)
    {
        return binds::ImGui_ImplWin32_VKeyToString(value.bindKey)
            + " - "
            + binds::getBindMode(value.bindMode + 1);
    }

    return "New Bind ##" + value.name;
}

template<typename T>
inline std::string getBindsComboLabel(const Item<T>& item, const BindPreview<T>& preview)
{
    if (item.binds.empty()
        || !preview.selectedBind.has_value() 
        || preview.selectedBind.value() == item.binds.end())
        return "No binds.";

    return preview.selectedBind.value()->previewName;
}
}