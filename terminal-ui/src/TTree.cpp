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

    void TTree::AddChild(const TTreeItem item) {
        this->item.children.push_back(item);
    }

    // NOTE: While this is both quite fast and functional, it only supports children having parent depth + 1
    std::wstring TTree::Render() {
        // Render
        const std::vector<wchar_t>* borderCharSet = &borderCharMap.at(ETreeBorderStyle::SINGLE);

        std::wstring out = L"";

        std::vector<TTreeItem*> flatItems = { &this->item };
        std::unordered_map<size_t, TTreeItem*> lastItems;
        TTreeItem* currentItem;

        while (flatItems.size() != 0) {
            currentItem = flatItems.back();
            const bool isLastItem = lastItems[currentItem->depth - 1] == currentItem;

            // Render hierarchy lines
            size_t depthDiff = currentItem->depth - this->item.depth;
            size_t prevDepth = depthDiff - 1;

            for (size_t curDepth = 0; curDepth < depthDiff; curDepth++) {
                size_t charIndex = 0;

                if (lastItems[curDepth] == nullptr) {
                    charIndex = 3;
                }
                else if(curDepth == prevDepth) {
                    if (isLastItem) {
                        charIndex = 2;
                    }
                    else {
                        charIndex = 1;
                    }
                }
                
                out += (*borderCharSet)[charIndex];

                // Render spacing and final lines
                charIndex = 3;
                if (curDepth == prevDepth) {
                    charIndex = 4;
                }

                for (size_t j = 1; j < this->indentSize; j++) {
                    out += (*borderCharSet)[charIndex];
                }
            }

            // Render item label
            out += std::wstring(currentItem->label.begin(), currentItem->label.end()) + L"\n";

            // Remove item from item lists
            flatItems.pop_back();

            if (isLastItem) {
                lastItems[currentItem->depth - 1] = nullptr;
            }

            // Add next children
            if (currentItem->children.size() > 0) {
                for (size_t i = currentItem->children.size() - 1; i != SIZE_MAX; i--) {
                    flatItems.emplace_back(&currentItem->children[i]);
                }

                lastItems[currentItem->depth] = &currentItem->children[currentItem->children.size() - 1];
            }
        }

        return out;
    }
}