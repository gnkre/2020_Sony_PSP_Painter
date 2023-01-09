#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include "../common/callback.hpp"
#include "gfx.hpp"
#include <pspctrl.h>
#include <stdio.h>
#include <stdlib.h>
unsigned const char color8bit_old[][3] = {0,0,0,240,157,51,239,42,85,42,239,167};
unsigned const char color8bit[][3] = {0,0,0,51,157,240,85,42,239,167,239,42};
const char* save_slot[5] = {"pic0.bingchilingbing", "pic1.bingchilingbing", "pic2.bingchilingbing", "pic3.bingchilingbing", "pic4.bingchilingbing"};
const char* save_ppm[5] = {"ms0:/PICTURE/LTPTR/pic0.bmp", "ms0:/PICTURE/LTPTR/pic1.bmp", "ms0:/PICTURE/LTPTR/pic2.bmp", "ms0:/PICTURE/LTPTR/pic3.bmp", "ms0:/PICTURE/LTPTR/pic4.bmp"};
PSP_MODULE_INFO("J aime le chocolat", PSP_MODULE_USER, 2, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);
#define DIR "ms0:/PICTURE/LTPTR"
const unsigned char bmpfileheader[14] = {'B','M', 0,20,2,0, 0,0,0,0, 54,0,0,0};
const unsigned char bmpfileinfo[40] = {40,0,0,0, /*img width*/ 0,2,0,0, /*img height*/ 10,1,0,0, /*number of color planes*/1,0, 24,0,0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0};

int main()
{
    //png_access_version_number();
    
    SceCtrlData pad;
    sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    
    //int file_cursor = 0;
    EXIT::setupExitCallback();
    pspDebugScreenInit();
    GFX::init();
    int x = 0;
    int y = 0;
    int color[4] = {0x339ef0, 0x542aef, 0xa7ef2a, 0x000000};
    int color_cursor = 0;
    int color_cursor_temp = 0;
    int mode = 1;
    pspDebugScreenPrintf("load complete.");
    sceKernelDelayThread(1000000);
    GFX::clear(0x000000);
    GFX::swapBuffers();
    SceUID check_dir = sceIoDopen(DIR);
    if (check_dir < 0)
    {
        pspDebugScreenPrintf("\nThis seems to be your first time using this.\nPress circle to make a dir in \"MS0:/PICTURE\" to save pictures.");
        sceCtrlReadBufferPositive(&pad, 1);
        while (pad.Buttons != PSP_CTRL_CIRCLE)
        {
            sceCtrlReadBufferPositive(&pad, 1);
        }
        sceIoMkdir(DIR, 0777);
    }
    
    pspDebugScreenInit();
    while(EXIT::isRunning()) 
    {
		sceDisplayWaitVblankStart(); // wait for vblank
		sceCtrlReadBufferPositive(&pad, 1);
        if (pad.Buttons != 0)
        {
            if (pad.Buttons & PSP_CTRL_UP)
            {
                if (pad.Buttons & PSP_CTRL_CROSS)
                {
                    y -= 2;
                }
				y--;
                if (y < 0)
                {
                    y = 0;
                }
			} 
			if (pad.Buttons & PSP_CTRL_DOWN)
            {
                if (pad.Buttons & PSP_CTRL_CROSS)
                {
                    y += 2;
                }
                y++;
                if (y > 252)
                {
                    y = 252;
                }
			} 
			if (pad.Buttons & PSP_CTRL_LEFT)
            {
                if (pad.Buttons & PSP_CTRL_CROSS)
                {
                    x -= 2;
                }
				x--;
                if (x < 0)
                {
                    x = 0;
                }
			} 
			if (pad.Buttons & PSP_CTRL_RIGHT)
            {
                
                if (pad.Buttons & PSP_CTRL_CROSS)
                {
                    x += 2;
                }
				x++;
                if (x > 460)
                {
                    x = 460;
                }
			}
            if (pad.Buttons & PSP_CTRL_TRIANGLE)
            {
                pad.Buttons = 0;
                pspDebugScreenInit();
                pspDebugScreenPrintf("Press square to clear the canvas, cross to cancel.");
                sceKernelDelayThread(200000);
                while (true)
                {
                    sceCtrlReadBufferPositive(&pad, 1);
                    if (pad.Buttons == PSP_CTRL_SQUARE)
                    {
                        GFX::clear(0x000000);
                        GFX::saveDrawBuffer();
                        pad.Buttons = 0;
                        break;
                    }
                    if (pad.Buttons == PSP_CTRL_CROSS)
                    {
                        pad.Buttons = 0;
                        break;
                    }
                }
                
            }
            if (pad.Buttons & PSP_CTRL_SQUARE)
            {
                color_cursor++;
                color_cursor = color_cursor % 3;
                color_cursor_temp = color_cursor;
                sceKernelDelayThread(100000);
            }
            if (pad.Buttons & PSP_CTRL_CIRCLE)
            {
                GFX::saveDispBuffer();
            }
            if (pad.Buttons & PSP_CTRL_RTRIGGER)
            {
                color_cursor = 3;
                GFX::saveDispBuffer();
                
                //GFX::clearScreenWithBuffer();
            }
            
            if (pad.Buttons & PSP_CTRL_LTRIGGER)
            {
                int running_all_menu = 1;

                pspDebugScreenInit();
                pspDebugScreenSetXY(0, 0);
                pspDebugScreenPrintf("\n\nThis is the save/load menu\ntriangle to save and cross to load.\nsquare to cancel.");
                int saving_cursor = 0;
                while (running_all_menu == 1)
                {
                    sceCtrlReadBufferPositive(&pad, 1);
                    
                    if (pad.Buttons & PSP_CTRL_TRIANGLE)
                    {
                        int running_save_menu = 1;
                        int cancelsav = 0;
                        pspDebugScreenInit();
                        pspDebugScreenPrintf("\n\nThis is the saving menu\npress square to cancel.\n\n");
                        
                        while (running_save_menu == 1)
                        {
                            pspDebugScreenSetXY(0, 5);

                            pspDebugScreenPrintf("Saving in slot : %d", saving_cursor);
                            sceCtrlReadBufferPositive(&pad, 1);

                            if (pad.Buttons & PSP_CTRL_UP)
                            {
                                if (saving_cursor > 3)
                                {
                                    saving_cursor = -1;
                                }
                                saving_cursor++;
                                sceKernelDelayThread(200000);
                            }
                            if (pad.Buttons & PSP_CTRL_CIRCLE)
                            {
                                running_save_menu = 0;
                                running_all_menu = 0;
                                sceKernelDelayThread(200000);
                            }
                            if (pad.Buttons & PSP_CTRL_SQUARE)
                            {
                                running_all_menu = 0;
                                cancelsav = 1;
                                break;
                                
                            }
                    
                        }
                        if (cancelsav == 0)
                        {
                            FILE* fptr = fopen(save_slot[saving_cursor], "wb");
                            uint32_t* saving = GFX::gaveTempBuffer();
                            pspDebugScreenPrintf("\ngot buffer address, ");


                            pspDebugScreenPrintf("saving to slot %d...\n first pixel:%d  last pixel:%d\n", saving_cursor, saving[0], saving[139263]);
                            sceKernelDelayThread(100000);
                            for(int i = 0 ; i < 139264; i++)
                            {
                                fprintf(fptr, "%u\n", saving[i]);
                            }
                            fclose(fptr);
                            pspDebugScreenPrintf("Writing complete, now formatting .BMP image...\n");
                            FILE* imageFile = fopen(save_ppm[saving_cursor], "wb");
                            if (imageFile == NULL) 
                            {
                                pspDebugScreenPrintf("error: cannot open output file\n closing menu...");
                                running_all_menu = 0;
                                break;
                            }
                            else
                            {
                                pspDebugScreenPrintf("file found, formatting and overwriting %s...\n", save_ppm[saving_cursor]);

                                fwrite(bmpfileheader, 1, 14, imageFile);
                                fwrite(bmpfileinfo, 1, 40, imageFile);
                                //unsigned const char c[] = {100};
                                int sav_inst = 0, sav2 = 0;
                                for (int i = 272; i >= 0; i--)
                                {
                                    sav_inst = i * 512;
                                    for (int j = 0; j < 512; j++)
                                    {
                                        sav2 = sav_inst + j;
                                        if (saving[sav2] == 3383024)
                                        {
                                            fwrite(color8bit[1], 1, 3, imageFile);
                                        }
                                        else if (saving[sav2] == 11005738)
                                        {
                                            fwrite(color8bit[3], 1, 3, imageFile);
                                        }
                                        else if (saving[sav2] == 5516015)
                                        {
                                            fwrite(color8bit[2], 1, 3, imageFile);
                                        }
                                        else 
                                        {
                                            fwrite(color8bit[0], 1, 3, imageFile);
                                        }
                                    }
                                }
                                
                                fclose(imageFile);
                                pspDebugScreenPrintf("Press square to exit.");
                                sceCtrlReadBufferPositive(&pad, 1);
                                while (!(pad.Buttons & PSP_CTRL_SQUARE))
                                {
                                    sceCtrlReadBufferPositive(&pad, 1);
                                }
                                
                            }
                            
                            
                        }
                    }
                    if (pad.Buttons & PSP_CTRL_CROSS)
                    {
                        pspDebugScreenInit();
                        pspDebugScreenSetXY(0, 0);
                        pspDebugScreenPrintf("loading...\n");
                        uint32_t* load_temp = GFX::gaveTempBuffer();
                        pspDebugScreenPrintf("buffer memory pointer loaded, writing directly to eDRAM\n");
                        int running_load_menu = 1;
                        //pspDebugScreenInit();
                        pspDebugScreenSetXY(0, 3);
                        pspDebugScreenPrintf("\n\nThis is the loading menu\nchoose a loading slot\npress square to cancel\n");
                        int loading_cursor = 0;
                        int cancel = 0;
                        while (running_load_menu == 1)
                        {
                            sceDisplayWaitVblankStart();
                            sceCtrlReadBufferPositive(&pad, 1);
                            if (pad.Buttons & PSP_CTRL_SQUARE)
                            {
                                cancel = 1;
                                running_all_menu = 0;
                                break;
                                
                            }
                            if (pad.Buttons & PSP_CTRL_UP)
                            {
                                if (loading_cursor > 3)
                                {
                                    loading_cursor = -1;
                                }
                                loading_cursor++;
                                sceKernelDelayThread(200000);
                            }
                            if (pad.Buttons & PSP_CTRL_CIRCLE)
                            {
                                running_load_menu = 0;
                                running_all_menu = 0;
                                sceKernelDelayThread(200000);
                            }
                            pspDebugScreenSetXY(0, 8);

                            pspDebugScreenPrintf("loading from slot : %d\n\n", loading_cursor);
                            //sceKernelDelayThread(1000000);
                        }
                        if (cancel == 0)
                        {
                            FILE* fread = fopen(save_slot[loading_cursor], "rb");
                            for(int i = 0 ; i < 139264; i++)
                            {
                                fscanf(fread, "%u", &load_temp[i]);
                                //pspDebugScreenPrintf("%d ", load_temp[i]);
                            }

                            pspDebugScreenPrintf("load complete %d %d", load_temp[0], load_temp[139263]);
                            fclose(fread);
                            //sceKernelDelayThread(1000000);
                            pspDebugScreenPrintf("\n\nPress square to exit.");
                            sceCtrlReadBufferPositive(&pad, 1);
                            while (!(pad.Buttons & PSP_CTRL_SQUARE))
                            {
                                sceCtrlReadBufferPositive(&pad, 1);
                            }
                            sceDisplayWaitVblankStart();
                            GFX::fromMainSaveToDraw(load_temp);
                        }
                
                        
                    }


                    if (pad.Buttons & PSP_CTRL_SQUARE)
                    {
                        running_all_menu = 0;
                        break;        
                    }
                }
            }

        }
        //GFX::clear(0x000000);
        GFX::clearScreenWithBuffer();

		GFX::drawRect(x, y, 20, 20, color[color_cursor]);
        GFX::swapBuffers();
        
        //sceDisplayWaitVblankStart(); enable it will get strange display
	}
    sceKernelExitGame();	
	return 0;
}