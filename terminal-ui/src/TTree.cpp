#include "TTree.h"
#include <unordered_map>
#include <iostream>

namespace TUI {
    // Left, Left (Connection), Bottom-left, Indent, Line
    const std::unordered_map<ETreeBorderStyle, std::vector<wchar_t>> borderCharMap = {
        { ETreeBorderStyle::SINGLE, {L'\u2502', L'\u251c', L'\u2514', L' ', L'\u2500'}}
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

            for (size_t i = 0, l = this->indentSize * currentItem->depth; i < l; i++) {
                size_t charIndex = 3;

                if (i == l - this->indentSize) {
                    charIndex = 1;
                }
                else if (i % this->indentSize == 0 && i != l - 1) {
                    charIndex = 0;
                }
                else if (i > l - this->indentSize) {
                    charIndex = 4;
                }

                out += (*borderCharSet)[charIndex];
            }

            out += std::wstring(currentItem->label.begin(), currentItem->label.end()) + L"\n";

            for (size_t i = currentItem->children.size() - 1; i != SIZE_MAX; i--) {
                deepItems.push_back(&currentItem->children[i]);
            }
        }

        return out;
    }
}