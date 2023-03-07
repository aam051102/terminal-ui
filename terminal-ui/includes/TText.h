#ifndef TUI_TTEXT_H
#define TUI_TTEXT_H

#include "TItem.h"
#include <string>

namespace TUI {
    class TText : public TItem {
    public:
        TText();

        virtual std::wstring Render() override;

        void SetContent(const std::string& content) { this->content = content; };

    protected:
        std::string content;

        virtual TText* CloneImpl() const override {
            return new TText(*this);
        };

    };
}

#endif