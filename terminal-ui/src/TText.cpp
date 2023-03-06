#include "TText.h"
#include <unordered_map>
#include <iostream>

namespace TUI {
    TText::TText() {

    }

    std::wstring TText::Render() {
        return std::wstring(this->content.begin(), this->content.end()) + L"\n";
    }
}