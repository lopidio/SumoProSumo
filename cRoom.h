#ifndef CROOM_H_INCLUDED
#define CROOM_H_INCLUDED

class Game
{
    //m�todo para inicializar a janela e dispositivo Allegro
public:
    void startGameDevice( const short colordepth, int wWidth, int wHeight);
};

class Room
{
private:
    BITMAP* background; //bitmap que guarda o background
    ///vari�vel da m�sica da "room"
public:
    void updateRoom(BITMAP* buffer);
    void setRoomBuffer(short bWidth, short bHeight);
};

class Level
{
private:
    BITMAP* backgrFloor;    //imagem do ch�o de background, geralmente �gua, lava ou pedras.
    BITMAP* foregrObjects;
    BITMAP* levelStand;     //imagem da plataforma
    BITMAP* levelStandShadow;   //sombra da plataforma;
    unsigned short sHeight, sWidth, bSize, sdHeight, sdWidth;  //altura e largura da plataforma para cumulo de colis�o e da img de backgr
    unsigned short animControl;
public:
    void setBackgrFloor( short nFrames, BITMAP* image, unsigned short imgsize);
    void updateBackgrFloor(short update, BITMAP* buffer);
    void setLevelStand( BITMAP* image, BITMAP* shadowImg, unsigned short sWidth, unsigned short sHeight, unsigned short sdWidth, unsigned short sdHeight);
    void updateLevelStand(BITMAP* buffer);
    void setLevelMusic();
    void update(BITMAP* buffer, int bWidht, int bHeight);
};

#endif // CROOM_H_INCLUDED
