#ifndef TUI_TTABLE_H
#define TUI_TTABLE_H

#include "TItem.h"
#include "Rect.h"
#include <vector>
#include <string>
#include <memory>

namespace TUI {
    struct TTableCell {
        std::string content;

        TTableCell(std::string content) : content(content) {};
    };

    struct TTableRow {
        std::vector<TTableCell> cells;

        TTableRow() {};
    };

    enum class ETTableBorderStyle {
        SINGLE,
        DOUBLE
    };

    class TTable : public TItem {
    public:
        TTable();

        std::wstring Render() override;

        ETTableBorderStyle borderStyle;
        Rect padding;

        std::vector<TTableRow> rows;

    protected:
        virtual TTable* CloneImpl() const override {
            return new TTable(*this);
        };

    };
}

#endif