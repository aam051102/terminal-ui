#ifndef TUI_TTEXT_H
#define TUI_TTEXT_H

#include "TItem.h"
#include <string>

namespace TUI {
    class TText : public TItem {
    public:
        TText();

        std::wstring Render() override;

        std::string content;

    protected:
        virtual TText* CloneImpl() const override {
            return new TText(*this);
        };

    };
}

#endif