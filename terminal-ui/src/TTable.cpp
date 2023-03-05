#include "TTable.h"
#include <unordered_map>
#include <iostream>

namespace TUI {
    const std::unordered_map<ETTableBorderStyle, std::vector<wchar_t>> borderCharMap = {
        { ETTableBorderStyle::SINGLE, {L'\u250c', L'\u2500', L'\u2510', L'\u2502', L'\u2518', L'\u2500', L'\u2514', L'\u2502', ' '}},
        { ETTableBorderStyle::DOUBLE, {L'\u2554', L'\u2550', L'\u2557', L'\u2551', L'\u255d', L'\u2550', L'\u255a', L'\u2551', ' '}},
    };

    TTable::TTable() {
        this->borderStyle = ETTableBorderStyle::SINGLE;
        this->padding = Rect(0, 0, 1, 1);
        this->rows = {};
    }

    std::wstring TTable::Render() {
        // Calculate size
        std::vector<size_t> contentWidths;

        for (size_t i = 0, l = this->rows.size(); i < l; i++) {
            TTableRow row = this->rows[i];

            if (contentWidths.size() < row.cells.size()) {
                contentWidths.resize(row.cells.size());
            }

            for (size_t j = 0, l2 = row.cells.size(); j < l2; j++) {
                TTableCell cell = row.cells[j];

                if (cell.content.length() > contentWidths[j]) {
                    contentWidths[j] = cell.content.length();
                }
            }
        }

        const size_t cols = contentWidths.size();
        
        size_t totalContentWidth = 0;

        for (size_t i = 0; i < cols; i++) {
            totalContentWidth += contentWidths[i];
        }

        const size_t width = 2 + totalContentWidth + cols * (this->padding.left + this->padding.right);
        const size_t height = 2 + this->rows.size() + this->rows.size() * (this->padding.top + this->padding.bottom);
       
        // Render
        std::wstring out = L"";

        const std::vector<wchar_t>* borderCharSet = &borderCharMap.at(this->borderStyle);

        for (size_t y = 0; y < height; y++) {
            size_t row = std::floor((y - 1 - this->padding.top) / (float)(this->padding.top + this->padding.bottom + 1));
            bool isContentRow = y >= 1 + this->padding.top && ((y - 1 - this->padding.top) % (this->padding.top + this->padding.bottom + 1)) == 0 && y != height - 1;

            size_t col = 0;
            size_t passedContentWidth = 0;

            for (size_t x = 0; x < width; x++) {
                size_t colStart = 1 + passedContentWidth + (col * (this->padding.left + this->padding.right)) + this->padding.left;
                size_t offset = x - colStart;
                bool isContentCol = x >= 1 + this->padding.left && x < width - 1 && offset < contentWidths[col];

                if (col < cols && offset == contentWidths[col]) {
                    passedContentWidth += contentWidths[col];
                    col++;
                }

                if (isContentRow && isContentCol && this->rows[row].cells[col].content.size() > offset) {
                    out += this->rows[row].cells[col].content[offset];
                }
                else {
                    size_t charIndex = 8;

                    if (y == 0) {
                        if (x == 0) {
                            charIndex = 0;
                        }
                        else if (x == width - 1) {
                            charIndex = 2;
                        }
                        else {
                            charIndex = 1;
                        }
                    }
                    else if (y == height - 1) {
                        if (x == 0) {
                            charIndex = 6;
                        }
                        else if (x == width - 1) {
                            charIndex = 4;
                        }
                        else {
                            charIndex = 5;
                        }
                    }
                    else if (x == 0) {
                        charIndex = 7;
                    }
                    else if (x == width - 1) {
                        charIndex = 3;
                    }

                    out += (*borderCharSet)[charIndex];
                }
            }

            out += L"\n";
        }

        return out;
    }
}