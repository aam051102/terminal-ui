#include "TParser.h"
#include "TRenderer.h"
#include "TDocument.h"
#include <pugixml.hpp>
#include <iostream>
#include <codecvt>

using namespace TUI;

int main()
{
    // Special characters refuse to render without this.
    std::setlocale(LC_ALL, "en_US.UTF-8");

    std::cout << "Please select a file to load: ";
    std::string filePath;
    std::getline(std::cin, filePath);

    std::cout << "Loading \"" << filePath << "\"" << std::endl;

    // Parse
    pugi::xml_document doc;
    pugi::xml_parse_result loadRes = doc.load_file(filePath.c_str());
    
    if (loadRes.status != pugi::status_ok) {
        std::cout << "Failed to load \"" << filePath << "\". Invalid XML format." << std::endl;
        return 1;
    }
    
    TDocument tDoc = TParser::ParseXML(doc.root());

    // Render
    system("cls");
    std::wcout << TRenderer::Render(tDoc);
    std::cout << std::endl << "Rendering complete. Press enter to close..." << std::endl;
    std::cin.get();
    
    return 0;
}