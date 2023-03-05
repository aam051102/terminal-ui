#ifndef TUI_TRENDERER_H
#define TUI_TRENDERER_H

#include "TDocument.h"
#include <string>

namespace TUI {
    class TRenderer {
    public:
        static std::wstring Render(TDocument doc, size_t width = 32, size_t height = 18);

    };
}

#endif