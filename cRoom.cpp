#include <allegro.h>
#include "cRoom.h"

//inicializa o dispositivo e a janela Allegro
void Game::startGameDevice(const short colordepth, int wWidth, int wHeight)
{
    allegro_init();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_color_depth(colordepth);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,wWidth,wHeight, 0, 0);
}

//cria e seta as imagens do chão de background
void Level::setBackgrFloor( short nFrames, BITMAP* image, unsigned short imgSize)
{
    animControl = nFrames;
    backgrFloor = image;
    bSize = imgSize;
}

//cria e seta a plataforma do level
void Level::setLevelStand( BITMAP* image, BITMAP* shadowImg, unsigned short sWidth, unsigned short sHeight, unsigned short sdWidth, unsigned short sdHeight)
{
    levelStand = image;
    levelStandShadow = shadowImg;
    Level::sWidth = sWidth;
    Level::sHeight = sHeight;
    Level::sdWidth = sdWidth;
    Level::sdHeight = sdHeight;
}

//desenha na tela e atualiza o chão e o stand:.
void Level::updateBackgrFloor(short update, BITMAP* buffer)
{
    for (int x=0; x<=800; x+=64)
        for (int y=0; y<=600; y+=64)
            masked_blit(backgrFloor, buffer, update%animControl*bSize, 0, x, y, bSize, bSize);
}

//:.
void Level::updateLevelStand(BITMAP* buffer)
{
    set_trans_blender(255, 255, 255, 155);
    draw_trans_sprite(buffer, levelStandShadow, 180-(sWidth - sdWidth)/2, 80+(sHeight - sdHeight)/2);
    masked_blit(levelStand, buffer, 0, 0, 180, 80, 453, 444);
}

//atualiza o buffer e os elementos do level que não são personagens
void Level::update(BITMAP* buffer, int bWidth, int bHeight)
{
    updateLevelStand(buffer);
}
