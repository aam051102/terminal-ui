#ifndef TUI_TDOCUMENT_H
#define TUI_TDOCUMENT_H

#include "TItem.h"
#include <vector>
#include <memory>

namespace TUI {
    class TDocument {
    public:
        TDocument() : children() {};

        void AddChild(TItem* child);
        
        std::vector<std::unique_ptr<TItem>> children;
      
        // Rule of five
        ~TDocument() = default;
        TDocument(TDocument const& other) : children() {
            for (size_t i = 0, l = other.children.size(); i < l; i++) {
                this->children.push_back(other.children[i]->Clone());
            }
        };
        TDocument(TDocument&& other) = default;
        TDocument& operator=(TDocument const& other) {
            this->children.clear();

            for (size_t i = 0, l = other.children.size(); i < l; i++) {
                this->children.push_back(other.children[i]->Clone());
            }

            return *this;
        }
        TDocument& operator=(TDocument&& other) = default;
    };
}

#endif