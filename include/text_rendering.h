// text_rendering.h
#ifndef TEXT_RENDERING_H
#define TEXT_RENDERING_H

void renderText(float x, float y, const char* text);
void renderTextLines(float x, float startY, float lineHeight, const char* texts[], int count);

#endif // TEXT_RENDERING_H