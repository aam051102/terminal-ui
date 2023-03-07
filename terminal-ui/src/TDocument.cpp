#include "TDocument.h"

namespace TUI {
    void TDocument::AddChild(TItem* item) {
        this->children.push_back(item->Clone());
    }

    std::wstring TDocument::Render() {
        std::wstring out;
        
        for (size_t i = 0, l = this->children.size(); i < l; i++) {
            TItem* child = this->children[i].get();
            out += child->Render();
        }

        return out;
    }
}