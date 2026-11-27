#ifndef FONT_H
#define FONT_H

enum { FONT_MEDIUM = 1, FONT_SMALL = 2, FONT_LARGE = 3 };

struct FontWindow {
    short win_top;
    short win_bot;
    short win_left;
    short win_right;
    short text_x;
    short text_y;
    short max_width;
    short max_height;
    short line_spacing;
    short flags;
    short sub_pixel_x;
    short sub_pixel_y;
};

// Selects font and returns its TEX0 register value (RC1 layout; DL returns void).
unsigned long FontSet(int fontName);
int FontLen(char *s, int len);
void FontPrintMediumLeft(int x, int y, unsigned long rgba, char *text, int length);
void SetFontWindow(FontWindow *window, int win_top, int win_bot, int win_left, int win_right, int text_x, int text_y, int line_spacing, int flags);
// The window printers take the font's TEX0 value and its width table.
void FontPrintWindow(FontWindow *window, unsigned long rgba, char *text, int length, unsigned long tex0, void *metrics);
void FontPrintWindowMedium(FontWindow *window, unsigned long rgba, char *text, int length);
int FontPrintCenter(int xpos, int ypos, unsigned long rgba, char *s, int len);
void FontPrintWindowSmall(FontWindow *window, unsigned long rgba, char *s, int len);

void FontPrintSmallLeft(int x, int y, unsigned long rgba, char *text, int length);

void FontPrintLarge(int x, int y, unsigned long rgba, char *text, int length);

void FontPrintMediumRight(int x, int y, unsigned long rgba, char *text, int length);

void FontPrintSmallRight(int x, int y, unsigned long rgba, char *text, int length);

int FontPrintCenterSmall(int xpos, int ypos, unsigned long rgba, char *s, int len);

void FontPrintLargeRight(int x, int y, unsigned long rgba, char *text, int length);

int FontPrintCenterLarge(int x, int y, unsigned long rgba, char *text, int length);

int FontPrintWrappedSmall(int x, int y, unsigned long rgba, char *text, int length, int width, int spacing);

#endif
