#include "TRenderer.h"
#include "TItem.h"
#include <memory>

namespace TUI {
    std::wstring TRenderer::Render(TDocument doc, size_t width, size_t height) {
        std::wstring out;

        for (size_t i = 0, l = doc.children.size(); i < l; i++) {
            TItem* child = doc.children[i].get();
            out += child->Render();
        }

        return out;
    }
}