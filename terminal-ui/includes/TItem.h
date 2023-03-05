#ifndef TUI_TITEM_H
#define TUI_TITEM_H

#include <string>
#include <memory>

namespace TUI {
    class TItem {
    public:
        virtual ~TItem() {};

        auto Clone() const { return std::unique_ptr<TItem>(CloneImpl()); };
        virtual std::wstring Render() = 0;

    protected:
        virtual TItem* CloneImpl() const = 0;

    };
}

#endif