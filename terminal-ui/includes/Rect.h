#ifndef TUI_RECT_H
#define TUI_RECT_H

namespace TUI {
    struct Rect {
        int top, left, bottom, right;

        Rect() : top(0), bottom(0), left(0), right(0) {};
        Rect(int top, int bottom, int left, int right) : top(top), bottom(bottom), left(left), right(right) {};
    };
};

#endif