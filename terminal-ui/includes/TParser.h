#ifndef TUI_TPARSER_H
#define TUI_TPARSER_H

#include "TDocument.h"
#include "TTable.h"
#include "TTree.h"
#include "TText.h"
#include <pugixml.hpp>

namespace TUI {
    class TParser {
    public:
        static TDocument ParseXML(pugi::xml_node node);

    private:
        static TTable ParseTable(pugi::xml_node node);
        static TTree ParseTree(pugi::xml_node node);
        static TText ParseText(pugi::xml_node node);
        static TTreeItem ParseTreeItem(pugi::xml_node node, size_t depth);

    };
}

#endif