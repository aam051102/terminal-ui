#ifndef TUI_TTREE_H
#define TUI_TTREE_H

#include "TItem.h"
#include "Rect.h"
#include <vector>
#include <string>
#include <memory>

namespace TUI {
    struct TTreeItem {
        std::string label;
        std::vector<TTreeItem> children;
    };

    enum class ETreeBorderStyle {
        SINGLE
    };

    class TTree : public TItem {
    public:
        TTree();

        std::wstring Render() override;

        size_t indentSize;

        TTreeItem item;

    protected:
        virtual TTree* CloneImpl() const override {
            return new TTree(*this);
        };

    };
}

#endif