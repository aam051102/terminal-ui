#ifndef TUI_TPARSER_H
#define TUI_TPARSER_H

#include "TDocument.h"
#include "TTable.h"
#include "TTree.h"
#include "TText.h"
#include <pugixml.hpp>
#include <stdexcept>

namespace TUI {
    class TParserException : public std::runtime_error {
    public:
        TParserException(const std::string& in) : std::runtime_error(in) {};
    };

    class TParserInvalidAttributeValueException : public TParserException {
    public:
        TParserInvalidAttributeValueException() : TParserException("Unsupported attribute value found during parsing.") {};
    };

    class TParserInvalidTagException : public TParserException {
    public:
        TParserInvalidTagException() : TParserException("Unsupported tag name found during parsing.") {};
    };

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