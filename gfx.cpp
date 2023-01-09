#include "gfx.hpp"
#include <pspge.h>
#include <pspdisplay.h>
#include <psputils.h>


namespace GFX
{
    uint32_t* draw_buffer;
    uint32_t* disp_buffer;
    uint32_t* save_temp;
    
    void init()
    {
        draw_buffer = static_cast<uint32_t*>(sceGeEdramGetAddr());
        disp_buffer = static_cast<uint32_t*>(sceGeEdramGetAddr()) + (272 * 512);
        save_temp = static_cast<uint32_t*>(sceGeEdramGetAddr()) + (272 * 512 * 2);
        sceDisplaySetMode(0, 480, 272);
        sceDisplaySetFrameBuf(disp_buffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, 1);      
        return;
    }
    void fromMainSaveToDraw(uint32_t* load_temp)
    {
        for(int i = 0; i < 139264; i++)
        {
            disp_buffer[i] = load_temp[i];
            draw_buffer[i] = load_temp[i];
            save_temp[i] = load_temp[i];
        }
        return;
    }
    void clear(uint32_t color)
    {
        for(int i = 0; i < 139264; i++)
        {
            draw_buffer[i] = color;
        }
        return;
    }
    void saveDispBuffer()
    {
        for(int i = 0; i < 139264; i++)
        {
            save_temp[i] = disp_buffer[i];
        }
        return;
    }
    void saveBuffer()
    {
        for(int i = 0; i < 139264; i++)
        {
            save_temp[i] = disp_buffer[i];
        }
        return;
    }
    void saveDrawBuffer()
    {
        for(int i = 0; i < 139264; i++)
        {
            save_temp[i] = draw_buffer[i];
        }
        return;
    }
    void clearScreenWithBuffer()
    {
        for(int i = 0; i < 139264; i++)
        {
            draw_buffer[i] = save_temp[i];
        }
        return;
    }

    void swapBuffers()
    {
        uint32_t* temp = disp_buffer;
        disp_buffer = draw_buffer;
        draw_buffer = temp;

        sceKernelDcacheWritebackInvalidateAll();
        sceDisplaySetFrameBuf(disp_buffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, 1);
        return;
    }

    void drawRect(unsigned int screen_x,unsigned int screen_y,unsigned int rect_w,unsigned int rect_h, uint32_t color)
    {
        //confine to screensize
        if (screen_x > 480)
        {
            screen_x = 480;
        }
        if (screen_y > 272)
        {
            screen_y = 272;
        }
        //confine the rect into screen size
        if ((screen_x + rect_w) > 480)
        {
            rect_w = 480 - screen_x;
        }
        if ((screen_y + rect_h > 272))
        {
            rect_h = 272 - screen_y;
        }
        //render the rect
        int offset = screen_x + (screen_y * 512);
        for(int y1 = 0; y1 < rect_h; y1++)
        {
            for(int x1 = 0; x1 < rect_w; x1++)
            {
                draw_buffer[x1 + offset + y1 * 512] = color;
            }
        }
        return;
    }
    uint32_t* gaveTempBuffer()
    {
        return save_temp;
    }
}