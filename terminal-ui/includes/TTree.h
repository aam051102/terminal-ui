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
        size_t depth;
        std::vector<TTreeItem> children;

        TTreeItem() : label(""), depth(0), children() {};
    };

    enum class ETreeBorderStyle {
        SINGLE
    };

    class TTree : public TItem {
    public:
        TTree();

        virtual std::wstring Render() override;

        void AddChild(const TTreeItem child);

        void SetLabel(const std::string& label) { this->item.label = label; };
        void SetIndentSize(size_t indentSize) { this->indentSize = indentSize; }

    protected:
        size_t indentSize;
        TTreeItem item;

        virtual TTree* CloneImpl() const override {
            return new TTree(*this);
        };

    };
}

#endif