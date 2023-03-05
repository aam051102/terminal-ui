#include "TParser.h"
#include "StringHelper.h"
#include <stdexcept>
#include <unordered_map>
#include <iostream>

namespace TUI {
    // --- Maps ---
    static std::unordered_map<std::string, ETTableBorderStyle> tableBorderStyleMap = {
        { "single", ETTableBorderStyle::SINGLE },
        { "double", ETTableBorderStyle::DOUBLE}
    };

    // --- Exceptions ---
    class TParserInvalidAttributeValueException : public std::exception {
    public:
        const char* what()
        {
            return "Unsupported attribute value found during parsing.";
        }
    };

    class TParserInvalidTagException : public std::exception {
    public:
        const char* what()
        {
            return "Unsupported tag name found during parsing.";
        }
    };

    // --- Methods ---
    TTable TParser::ParseTable(pugi::xml_node node) {
        TTable tTable;

        // Border style
        const std::string borderStyle = node.attribute("borderStyle").as_string("single");

        if (tableBorderStyleMap.find(borderStyle) == tableBorderStyleMap.end()) {
            throw TParserInvalidAttributeValueException();
        }
        
        tTable.borderStyle = tableBorderStyleMap.at(borderStyle);

        // Padding
        const std::string paddingStr = node.attribute("padding").as_string("0,0,0,0");
        
        const std::vector<std::string> paddingStrSplit = StringHelper::Split(paddingStr, ",");

        if (paddingStrSplit.size() != 4) {
            throw TParserInvalidAttributeValueException();
        }

        if (!StringHelper::IsNumber(paddingStrSplit[0]) || !StringHelper::IsNumber(paddingStrSplit[1]) || !StringHelper::IsNumber(paddingStrSplit[2]) || !StringHelper::IsNumber(paddingStrSplit[3])) {
            throw TParserInvalidAttributeValueException();
        }

        tTable.padding = Rect(std::stoi(paddingStrSplit[0]), std::stoi(paddingStrSplit[1]), std::stoi(paddingStrSplit[2]), std::stoi(paddingStrSplit[3]));

        // Head


        // Body
        const pugi::xml_node bodyNode = node.child("tbody");

        if (bodyNode) {
            const pugi::xml_object_range<pugi::xml_named_node_iterator> bodyChildRows = bodyNode.children("tr");

            for (pugi::xml_named_node_iterator rowIt = bodyChildRows.begin(), rowEnd = bodyChildRows.end(); rowIt != rowEnd; rowIt++) {
                const pugi::xml_object_range<pugi::xml_named_node_iterator> bodyRowChildCells = (*rowIt).children("td");
                TTableRow tRow;

                for (pugi::xml_named_node_iterator cellIt = bodyRowChildCells.begin(), cellEnd = bodyRowChildCells.end(); cellIt != cellEnd; cellIt++) {
                    const std::string cellContent = (*cellIt).text().as_string("");

                    TTableCell tCell(cellContent);
                    tRow.cells.push_back(tCell);
                }

                tTable.rows.push_back(tRow);
            }
        }

        // Foot


        return tTable;
    }

    TDocument TParser::ParseXML(pugi::xml_node node) {
        TDocument tDoc;

        pugi::xml_object_range<pugi::xml_node_iterator> children = node.child("root").children();

        for (pugi::xml_node_iterator it = children.begin(), end = children.end(); it != end; it++) {
            if (std::string((*it).name()) == "table") {
                TTable tTable = TParser::ParseTable((*it));
                tDoc.AddChild(&tTable);
            }
            else {
                throw TParserInvalidTagException();
            }
        }

        return tDoc;
    }
}