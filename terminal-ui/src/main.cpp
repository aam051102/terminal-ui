#include "TParser.h"
#include "TDocument.h"
#include <pugixml.hpp>
#include <iostream>
#include <codecvt>

using namespace TUI;

int main(int argc, char* argv[]) {
    // Special characters refuse to render without this.
    std::setlocale(LC_ALL, "en_US.UTF-8");

    std::string filePath = argc > 1 ? argv[1] : "";
    while (filePath == "") {
        std::cout << "Please select a file to load: ";
        std::getline(std::cin, filePath);

        if (filePath == "") {
            system("cls");
        }
    }

    std::cout << "Loading \"" << filePath << "\"" << std::endl;

    // Parse
    pugi::xml_document doc;
    pugi::xml_parse_result loadRes = doc.load_file(filePath.c_str());
    
    if (loadRes.status != pugi::status_ok) {
        std::cout << "Failed to load \"" << filePath << "\". Invalid XML format." << std::endl;
        return 1;
    }
    
    try {
        TDocument tDoc = TParser::ParseXML(doc.root());

        // Render
        system("cls");
        std::wcout << tDoc.Render();
        std::cout << std::endl << "Rendering complete. Press enter to close..." << std::endl;
        std::cin.get();
    }
    catch (const TParserException& e) {
        std::cerr << "Parsing failed: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}