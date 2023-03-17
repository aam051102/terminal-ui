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

        for (size_t i = 0, l = this->rows.size(); i < l; i++) {
            const TTableRow& row = this->rows[i];

            if (contentWidths.size() < row.cells.size()) {
                contentWidths.resize(row.cells.size());
            }

            for (size_t j = 0, l2 = row.cells.size(); j < l2; j++) {
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

        prerenderedTop += borderCharSet[0];
        prerenderedDivider += borderCharSet[12];
        prerenderedBottom += borderCharSet[6];

        for (size_t i = 0; i < colCount; i++) {
            prerenderedBlank += borderCharSet[7];
            
            if (i != 0) {
                prerenderedTop += borderCharSet[14];
                prerenderedDivider += borderCharSet[11];
                prerenderedBottom += borderCharSet[15];
            }

            for (size_t j = 0; j < contentWidths[i] + this->padding.left + this->padding.right; j++) {
                prerenderedBlank += borderCharSet[8];
                prerenderedTop += borderCharSet[1];
                prerenderedDivider += borderCharSet[10];
                prerenderedBottom += borderCharSet[5];
            }
        }

        prerenderedBlank += borderCharSet[3];
        prerenderedTop += borderCharSet[2];
        prerenderedDivider += borderCharSet[13];
        prerenderedBottom += borderCharSet[4];

        for (size_t i = 0; i < this->padding.top; i++) {
            prerenderedPaddingTop += prerenderedBlank;
            if (i != this->padding.top - 1) prerenderedPaddingTop += L"\n";
        }
        
        for (size_t i = 0; i < this->padding.bottom; i++) {
            prerenderedPaddingBottom += prerenderedBlank + L"\n";
            if (i != this->padding.bottom - 1) prerenderedPaddingBottom += L"\n";
        }

        // Render
        std::wstring out;

        out += prerenderedTop + L"\n";

        for (size_t i = 0; i < this->rows.size(); i++) {
            const TTableRow& row = this->rows[i];

            if (prerenderedPaddingTop != L"") {
                out += prerenderedPaddingTop + L"\n";
            }

            std::wstring content = prerenderedBlank;
            std::wstring::iterator distPos = content.begin() + 1 + this->padding.left;

            for (size_t j = 0; j < row.cells.size(); j++) {
                std::copy(row.cells[j].content.begin(), row.cells[j].content.end(), distPos);
                
                if (j != row.cells.size() - 1) {
                    distPos += contentWidths[j] + this->padding.right + this->padding.left + 1;
                }
            }

            out += content + L"\n";

            if (prerenderedPaddingBottom != L"") {
                out += prerenderedPaddingTop + L"\n";
            }

            if(i != this->rows.size() - 1) out += prerenderedDivider + L"\n";
        }

        out += prerenderedBottom + L"\n";

        return out;
    }
}