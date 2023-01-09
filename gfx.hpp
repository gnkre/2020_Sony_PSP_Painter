#include <cstdint>
namespace GFX
{
    void init();
    void clear(uint32_t color);
    void swapBuffers();
    void saveDispBuffer();
    void saveDrawBuffer();
    void saveBuffer();
    void fromMainSaveToDraw(uint32_t* load_temp);
    uint32_t* gaveTempBuffer();
    void clearScreenWithBuffer();
    void drawRect(unsigned int screen_x,unsigned int screen_y,unsigned int rect_w,unsigned int rect_h, uint32_t color);
}