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

        return tTable;
    }

    TTreeItem TParser::ParseTreeItem(pugi::xml_node node, size_t depth) {
        TTreeItem tTreeItem;
        tTreeItem.label = node.attribute("label").as_string("");
        tTreeItem.depth = depth + 1;

        const pugi::xml_object_range<pugi::xml_named_node_iterator> itemChildItems = node.children("item");

        for (pugi::xml_named_node_iterator itemIt = itemChildItems.begin(), itemEnd = itemChildItems.end(); itemIt != itemEnd; itemIt++) {
            tTreeItem.children.push_back(ParseTreeItem(*itemIt, tTreeItem.depth));
        }

        return tTreeItem;
    }

    TTree TParser::ParseTree(pugi::xml_node node) {
        TTree tTree;

        // Label
        const std::string& treeLabel = node.attribute("label").as_string();
        tTree.item.label = treeLabel;
        tTree.item.depth = 0;

        // Items
        const pugi::xml_object_range<pugi::xml_named_node_iterator> treeChildItems = node.children("item");

        for (pugi::xml_named_node_iterator itemIt = treeChildItems.begin(), itemEnd = treeChildItems.end(); itemIt != itemEnd; itemIt++) {
            tTree.item.children.push_back(ParseTreeItem(*itemIt, 0));
        }

        return tTree;
    }

    TDocument TParser::ParseXML(pugi::xml_node node) {
        TDocument tDoc;

        pugi::xml_object_range<pugi::xml_node_iterator> children = node.child("root").children();

        for (pugi::xml_node_iterator it = children.begin(), end = children.end(); it != end; it++) {
            if (std::string((*it).name()) == "table") {
                TTable tTable = TParser::ParseTable((*it));
                tDoc.AddChild(&tTable);
            }
            else if (std::string((*it).name()) == "tree") {
                TTree tTree = TParser::ParseTree((*it));
                tDoc.AddChild(&tTree);
            }
            else {
                throw TParserInvalidTagException();
            }
        }

        return tDoc;
    }
}