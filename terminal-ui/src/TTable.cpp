#include "TTable.h"
#include <unordered_map>
#include <iostream>

namespace TUI {
    // Top-left, Top, Top-right, Right, Bottom-right, Bottom, Bottom-left, Left, Middle, All Connections, Vertical Divider, Horizontal Divider, Left (Connection), Right (Connection), Top (Connection), Bottom (Connection)
    const std::unordered_map<ETTableBorderStyle, std::vector<wchar_t>> borderCharMap = {
        { ETTableBorderStyle::SINGLE, {L'\u250c', L'\u2500', L'\u2510', L'\u2502', L'\u2518', L'\u2500', L'\u2514', L'\u2502', ' ', L'\u2502', L'\u2500', L'\u253c', L'\u251c', L'\u2524', L'\u252c', L'\u2534'}},
        { ETTableBorderStyle::DOUBLE, {L'\u2554', L'\u2550', L'\u2557', L'\u2551', L'\u255d', L'\u2550', L'\u255a', L'\u2551', ' ', L'\u2551', L'\u2550', L'\u256c', L'\u2560', L'\u2563', L'\u2566', L'\u2569'}},
    };

    TTable::TTable() {
        this->borderStyle = ETTableBorderStyle::SINGLE;
        this->padding = Rect(0, 0, 0, 0);
        this->rows = {};
    }

    void TTable::AddRow(const TTableRow row) {
        this->rows.push_back(row);
    }

    std::wstring TTable::Render() {
        // Calculate size
        std::vector<size_t> contentWidths;

        for (size_t i = 0, rowCount = this->rows.size(); i < rowCount; i++) {
            const TTableRow& row = this->rows[i];
            const size_t cellCount = row.cells.size();

            if (contentWidths.size() < cellCount) {
                contentWidths.resize(cellCount);
            }

            for (size_t j = 0; j < cellCount; j++) {
                const TTableCell& cell = row.cells[j];

                if (cell.content.length() > contentWidths[j]) {
                    contentWidths[j] = cell.content.length();
                }
            }
        }

        const size_t colCount = contentWidths.size();
        const std::vector<wchar_t>& borderCharSet = *(&borderCharMap.at(this->borderStyle));

        // Prerender
        std::wstring prerenderedBlank;
        std::wstring prerenderedTop;
        std::wstring prerenderedDivider;
        std::wstring prerenderedBottom;
        std::wstring prerenderedPaddingTop;
        std::wstring prerenderedPaddingBottom;

        // Left side
        prerenderedTop += borderCharSet[0];
        prerenderedDivider += borderCharSet[12];
        prerenderedBottom += borderCharSet[6];

        for (size_t i = 0; i < colCount; i++) {
            // Column separators
            prerenderedBlank += borderCharSet[7];
            
            if (i != 0) {
                prerenderedTop += borderCharSet[14];
                prerenderedDivider += borderCharSet[11];
                prerenderedBottom += borderCharSet[15];
            }

            for (size_t j = 0; j < contentWidths[i] + this->padding.left + this->padding.right; j++) {
                // Between column dividers
                prerenderedBlank += borderCharSet[8];
                prerenderedTop += borderCharSet[1];
                prerenderedDivider += borderCharSet[10];
                prerenderedBottom += borderCharSet[5];
            }
        }

        // Right side
        prerenderedBlank += borderCharSet[3];
        prerenderedTop += borderCharSet[2];
        prerenderedDivider += borderCharSet[13];
        prerenderedBottom += borderCharSet[4];

        for (size_t i = 0; i < this->padding.top; i++) {
            prerenderedPaddingTop += prerenderedBlank + L"\n";
        }
        
        for (size_t i = 0; i < this->padding.bottom; i++) {
            prerenderedPaddingBottom += prerenderedBlank + L"\n";
        }

        // Render
        std::wstring out;

        out += prerenderedTop + L"\n";

        for (size_t i = 0, rowCount = this->rows.size(); i < rowCount; i++) {
            const TTableRow& row = this->rows[i];
            
            // TODO: Pre-calculate position text position
            std::wstring content = prerenderedBlank;
            std::wstring::iterator distPos = content.begin() + 1 + this->padding.left;

            for (size_t j = 0, cellCount = row.cells.size(); j < cellCount; j++) {
                std::copy(row.cells[j].content.begin(), row.cells[j].content.end(), distPos);
                
                if (j != cellCount - 1) {
                    distPos += contentWidths[j] + this->padding.right + this->padding.left + 1;
                }
            }

            out += prerenderedPaddingTop;
            out += content + L"\n";
            out += prerenderedPaddingTop;

            if(i != rowCount - 1) out += prerenderedDivider + L"\n";
        }

        out += prerenderedBottom + L"\n";

        return out;
    }
}