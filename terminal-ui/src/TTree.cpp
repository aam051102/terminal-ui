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
        const std::vector<wchar_t>* borderCharSet = &borderCharMap.at(ETreeBorderStyle::SINGLE);

        std::wstring out = L"";

        std::vector<TTreeItem*> deepItems = { &this->item };
        std::vector<TTreeItem*> lastItems;
        TTreeItem* currentItem;

        while (deepItems.size() != 0 && (currentItem = deepItems.back()) != nullptr) {
            deepItems.pop_back();
            const bool isLastItem = lastItems.size() > 0 && lastItems[lastItems.size() - 1] == currentItem;

            for (size_t i = 0, l = this->indentSize * currentItem->depth; i < l; i++) {
                size_t charIndex = 3;
                size_t expectedDepth = i / this->indentSize + 1;

                if (i == l - this->indentSize) {
                    if (isLastItem) {
                        charIndex = 2;
                    }
                    else {
                        charIndex = 1;
                    }
                }
                else if (i % this->indentSize == 0 && i != l - 1 && std::find_if(lastItems.begin(), lastItems.end(), [expectedDepth](TTreeItem* item) { return item->depth == expectedDepth; }) != lastItems.end()) {
                    charIndex = 0;
                }
                else if (i > l - this->indentSize) {
                    charIndex = 4;
                }

                out += (*borderCharSet)[charIndex];
            }

            if (isLastItem) {
                lastItems.pop_back();
            }

            out += std::wstring(currentItem->label.begin(), currentItem->label.end()) + L"\n";

            if (currentItem->children.size() > 0) {
                for (size_t i = currentItem->children.size() - 1; i != SIZE_MAX; i--) {
                    deepItems.push_back(&currentItem->children[i]);
                }

                lastItems.push_back(&currentItem->children[currentItem->children.size() - 1]);
            }
        }

        return out;
    }
}