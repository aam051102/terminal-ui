#ifndef TUI_RECT_H
#define TUI_RECT_H

namespace TUI {
    struct Rect {
        int top, left, bottom, right;

        Rect(int top = 0, int bottom = 0, int left = 0, int right = 0) : top(top), bottom(bottom), left(left), right(right) {};
    };
};

#endif