#include "TDocument.h"

namespace TUI {
    void TDocument::AddChild(TItem* item) {
        this->children.push_back(item->Clone());
    }
}