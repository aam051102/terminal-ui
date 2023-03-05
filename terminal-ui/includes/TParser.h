#ifndef TUI_TPARSER_H
#define TUI_TPARSER_H

#include "TDocument.h"
#include "TTable.h"
#include <pugixml.hpp>

namespace TUI {
    class TParser {
    public:
        static TDocument ParseXML(pugi::xml_node node);

    private:
        static TTable ParseTable(pugi::xml_node node);

    };
}

#endif