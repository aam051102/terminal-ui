#include "TTree.h"
#include <unordered_map>
#include <iostream>

namespace TUI {
    // Left, Left (Connection), Bottom-left, Indent
    const std::unordered_map<ETreeBorderStyle, std::vector<wchar_t>> borderCharMap = {
        { ETreeBorderStyle::SINGLE, {L'\u2514', L'\u251c', L'\u2500', L' '}}
    };

    TTree::TTree() {
        this->indentSize = 4;
    }

    std::wstring TTree::Render() {
        // Render
        std::wstring out = L"";

        const std::vector<wchar_t>* borderCharSet = &borderCharMap.at(ETreeBorderStyle::SINGLE);

        std::vector<TTreeItem*> deepItems = { &this->item };

        TTreeItem* currentItem;

        while (deepItems.size() != 0 && (currentItem = deepItems.back()) != nullptr) {
            deepItems.pop_back();

            /*for (size_t i = 0; i < this->indentSize; i++) {
                out += (*borderCharSet)[3];
            }*/

            out += std::wstring(currentItem->label.begin(), currentItem->label.end()) + L"\n";

            for (size_t i = currentItem->children.size() - 1; i != SIZE_MAX; i--) {
                deepItems.push_back(&currentItem->children[i]);
            }
        }

        return out;
    }
}