#include <allegro.h>
#include <allegro.h>
#include <math.h>
#include "cObjects.h"
#include "cRoom.h"

//defines
#define P1_STARTPOS 380, 110    //posição inicial dos players
#define P2_STARTPOS 200, 270
#define P3_STARTPOS 560, 270
#define P4_STARTPOS 380, 420
//variavel global

bool jogadores[4] = {true, true, false, false};

void Pause(BITMAP* buffer, BITMAP* pause,SAMPLE* tuntun)
{
    stop_sample(tuntun);
    midi_pause();
    BITMAP* preto = create_bitmap(screen->w, screen->h);
    play_sample(tuntun, 400, 128, 1000, false);    
    draw_trans_sprite(screen, preto,0,0);
    masked_blit(pause,screen,0,0,275,200,256,64);
    while (key[KEY_ENTER]);
    while (!key[KEY_ENTER]){
          if(key[KEY_Q]) stop_midi();
          if(key[KEY_ESC]) exit(1);
    }
    while (key[KEY_ENTER]);
    midi_resume();
    return;
}

void updatePlayers(Character &p1, Character &p2, Character &p3, Character &p4, BITMAP* buffer)
{
    if(p1.exists())
    {
        p1.update(160, 65, 590, 480, buffer);
        if (p2.exists()) p1.checkColision(p2);
        if (p3.exists()) p1.checkColision(p3);
        if (p4.exists()) p1.checkColision(p4);
        if (p1.renascer){
           p1.renascer = false;
           p1.Respawn(p1.getScore()%4+1);
           if (p1.colides(p2) || p1.colides(p3) || p1.colides(p4))
               p1.Respawn (p1.getScore()%4+2);
           if (p1.colides(p2) || p1.colides(p3) || p1.colides(p4))
               p1.Respawn (p1.getScore()%4+3);                                             
           if (p1.colides(p2) || p1.colides(p3) || p1.colides(p4))
               p1.Respawn (p1.getScore()%4+4);                                             
        }        
    }
    if(p2.exists())
    {
        p2.update(160, 65, 590, 480, buffer);
        if (p1.exists()) p2.checkColision(p1);
        if (p3.exists()) p2.checkColision(p3);
        if (p4.exists()) p2.checkColision(p4);
        if (p2.renascer){
           p2.renascer = false;
           p2.Respawn(p2.getScore()%4+1);
           if (p2.colides(p1) || p2.colides(p3) || p2.colides(p4))
               p2.Respawn (p2.getScore()%4+2);
           if (p2.colides(p1) || p2.colides(p3) || p2.colides(p4))
               p2.Respawn (p2.getScore()%4+3);                                             
           if (p2.colides(p1) || p2.colides(p3) || p2.colides(p4))
               p2.Respawn (p2.getScore()%4+4);                                             
        }        
    }
    if(p3.exists())
    {
        p3.update(160, 65, 590, 480, buffer);
        if (p1.exists()) p3.checkColision(p1);
        if (p2.exists()) p3.checkColision(p2);
        if (p4.exists()) p3.checkColision(p4);
        if (p3.renascer){
           p3.renascer = false;
           p3.Respawn(p3.getScore()%4+1);
           if (p3.colides(p1) || p3.colides(p2) || p3.colides(p4))
               p3.Respawn (p3.getScore()%4+2);
           if (p3.colides(p1) || p3.colides(p2) || p3.colides(p4))
               p3.Respawn (p3.getScore()%4+3);                                             
           if (p3.colides(p1) || p3.colides(p2) || p3.colides(p4))
               p3.Respawn (p3.getScore()%4+4);                                             
        }        
    }
    if(p4.exists())
    {
        p4.update(160, 65, 590, 480, buffer);
        if (p1.exists()) p4.checkColision(p1);
        if (p2.exists()) p4.checkColision(p2);
        if (p3.exists()) p4.checkColision(p3);
    }
        if (p4.renascer){
           p4.renascer = false;
           p4.Respawn(p4.getScore()%4+1);
           if (p4.colides(p1) || p4.colides(p2) || p4.colides(p3))
               p4.Respawn (p4.getScore()%4+2);
           if (p4.colides(p1) || p4.colides(p2) || p4.colides(p3))
               p4.Respawn (p4.getScore()%4+3);                                             
           if (p4.colides(p1) || p4.colides(p2) || p4.colides(p3))
               p4.Respawn (p4.getScore()%4+4);                                             
        }        
}

void gui()
{
     midi_pause();
     SAMPLE* musica = load_wav("graphics/logos.wav");
     play_sample(musica, 200, 128, 1000, false);
     BITMAP* logo = load_bitmap("graphics/guilogo.bmp", NULL);
     BITMAP* logo_klng = load_bitmap("graphics/LOGO.bmp", NULL);
     BITMAP* buffer = create_bitmap(800,600);
          masked_blit(logo_klng, buffer,0,0,490,170,logo_klng->w,logo_klng->h);
          masked_blit(logo, buffer,0,0,90,150,logo->w,logo->h);
          draw_sprite(screen, buffer, 0,0);
     _sleep(1200);
     destroy_bitmap(logo);
     destroy_bitmap(logo_klng);
     destroy_bitmap(buffer);
     midi_resume();
return;
}


int menu_principal()
{
    while (key[KEY_ENTER]);
    SAMPLE* blit = load_wav("graphics/menu.wav");
    SAMPLE* gong = load_wav("graphics/gongo.wav");
    BITMAP* fundo = load_bitmap("graphics/fundopreto.bmp", NULL);
    BITMAP* start = load_bitmap("graphics/start jogo.bmp", NULL);
    BITMAP* tab = load_bitmap("graphics/menuTab1.bmp", NULL);
    BITMAP* buffer = create_bitmap(800,600);
    int linha = 2;
    while (true)
    {
        _sleep(120);
        masked_blit(fundo, buffer,0,0,0,0,800,600);
        set_trans_blender(255, 255, 255, 150);
        draw_trans_sprite(buffer, tab, 65, 30);
        for (int cont = 0; cont<= 3; cont++)
        {
            masked_blit(start, buffer,0 + 280*(linha == cont), 80*cont,  100,80*(cont+1),290,80);           //player 1, 2,3,4
            masked_blit(start, buffer,480 + 140*(jogadores[cont]),410,600,80*(cont+1),140,70);           //player  SIM, NAUM
        }
        masked_blit(start, buffer,0 + 280*(linha==4),320,100,400,290,80);          //Voltar
        masked_blit(start, buffer,0 + 210*(linha==5),400,100,480,120,80);          //OK
        masked_blit(buffer,screen,0,0,0,0,800,600);

        if (key[KEY_RIGHT])
        {
            jogadores[linha] = jogadores[linha] ^ 1;
            play_sample(blit, 200, 128, 1000, false);
        }
        if (key[KEY_LEFT])
        {
            jogadores[linha] = jogadores[linha] ^ 1;
            play_sample(blit, 200, 128, 1000, false);
        }

        if (key[KEY_DOWN])
        {
            (linha < 5)? linha++ :linha = 0;
            play_sample(blit, 200, 128, 1000, false);
        }
        if (key[KEY_UP])
        {
            (linha > 0)? linha-- :linha = 5;
            play_sample(blit, 200, 128, 1000, false);
        }

        if (key[KEY_ENTER])
        {
            if (linha == 4 || linha ==5) play_sample(gong, 300, 128, 1000, false);
            if (linha == 4) return 0;
            if (linha == 5 && jogadores[0] + jogadores[1]
                            + jogadores[2] + jogadores[3] > 1)
                 return jogadores[0] + 2*jogadores[1] + 4*jogadores[2] + 8*jogadores[3];
        }
        while (!keypressed()){};
    }
}

void creditos()
{
     gui();
     while(!keypressed());
     return;
}

int inicio_jogo()
{
    while (key[KEY_ENTER]);
    while (key[KEY_ENTER]);
    SAMPLE* blit = load_wav("graphics/menu.wav");
    SAMPLE* gong = load_wav("graphics/gongo.wav");
    MIDI* fundoS = load_midi("graphics/musica.mid");
    play_midi(fundoS, true);
    int opcao = 0;
    BITMAP* fundo = load_bitmap("graphics/fundopreto.bmp", NULL);
    BITMAP* tab = load_bitmap("graphics/menutab.bmp", NULL);
    BITMAP* menu = load_bitmap("graphics/Menu Principal.bmp", NULL);
    BITMAP* buffer = create_bitmap(800,600);

    masked_blit(fundo, buffer,0,0,0,0,800,600);
    masked_blit(buffer,screen,0,0,0,0,800,600);
    _sleep(1450);
    while (true)
    {
        _sleep(120);
        masked_blit(fundo, buffer,0,0,0,0,800,600);
        set_trans_blender(255, 255, 255, 150);
        draw_trans_sprite(buffer, tab, 160, 120);
        masked_blit(menu, buffer,0 + 390*(opcao==0),0  ,200,190,380,70);
        masked_blit(menu, buffer,0 + 390*(opcao==1),70 ,200,260,380,70);
        masked_blit(menu, buffer,0 + 390*(opcao==2),140,200,330,380,80);

        masked_blit(buffer,screen,0,0,0,0,800,600);
        if (key[KEY_DOWN])
        {
            (opcao < 2)? opcao++ :opcao = 0;
            play_sample(blit, 200, 128, 1000, false);
        }
        if (key[KEY_UP])
        {
            (opcao > 0)? opcao-- :opcao = 2;
            play_sample(blit, 200, 128, 1000, false);
        }
        if (key[KEY_ENTER])
        {
            play_sample(gong, 400, 128, 1000, false);
            if (opcao == 0 && key[KEY_ENTER]) return menu_principal();
            if (opcao == 1 && key[KEY_ENTER]) creditos();
            if (opcao == 2 && key[KEY_ENTER]) return -1;
        }
        while (!keypressed());
    }
}

void imprime_agua(BITMAP* buffer ,BITMAP* water, int frame_agua)  //desenha todo o fundo de água
{
    for (int x = 0; x <= 800; x +=  64)
        for (int y = 0; y <= 600; y +=  64)
            masked_blit(water,buffer,frame_agua%4*64,0,x,y,64,64);
    return;
}


int main()
{

    Game sumoGame;
    sumoGame.startGameDevice(32, 800, 600);
    Level levelOne;
    set_window_title("Sumo Pro Sumo");

    BITMAP *pause = load_bitmap("graphics/pause.bmp",NULL);
    BITMAP *arena = load_bitmap("graphics/arena.bmp",NULL);
    BITMAP *arena_shadow = load_bmp("graphics/arena_shadow.bmp", NULL);

    BITMAP *water = load_bitmap("graphics/water.bmp",NULL);
    levelOne.setBackgrFloor(4, water, 64);
    levelOne.setLevelStand(arena, arena_shadow, 453, 444, 483, 473);

    BITMAP *buffer = create_bitmap(800,600);
    int frame_agua = 0;

    int jogadores = inicio_jogo();
    bool player[4];

    while (jogadores <= 0)
    {
        if (jogadores == -1) return 0;
        jogadores = inicio_jogo();
    }
    for (int cont = 0; cont <= 3; cont++)
    {
        player[cont] = jogadores%2;
        jogadores/=2;
    }    
    
    Character player1(11, player[0]? ECN_HUMAN : ECN_NONE, P1_STARTPOS);
    Character player2(11, player[1]? ECN_HUMAN : ECN_NONE, P2_STARTPOS);
    Character player3(11, player[2]? ECN_HUMAN : ECN_NONE, P3_STARTPOS);
    Character player4(11, player[3]? ECN_HUMAN : ECN_NONE, P4_STARTPOS);

    while (key[KEY_ENTER]);
    SAMPLE* tuntun = load_wav("graphics/tuntuntuntun.wav");
    stop_midi();
    play_sample(tuntun, 400, 128, 1000, false);    

    MIDI* jogoS = load_midi("graphics/firstmusica.mid");
    play_midi(jogoS, true);
   
    while (true)
    {
        if (key[KEY_ENTER]) Pause(buffer, pause, tuntun);

        clear(buffer);
        levelOne.updateBackgrFloor(frame_agua++, buffer);

        if (player[0]) player1.print(buffer, false); //imprime sob a plataforma
        if (player[1]) player2.print(buffer, false);
        if (player[2]) player3.print(buffer, false);                
        if (player[3]) player4.print(buffer, false);        

        levelOne.update(buffer, 800, 600);
        updatePlayers(player1, player2, player3, player4, buffer);

        if (player[0]) player1.print(buffer, true); //imprime sobre a plataforma
        if (player[1]) player2.print(buffer, true);
        if (player[2]) player3.print(buffer, true);                
        if (player[3]) player4.print(buffer, true);        

        masked_blit(buffer,screen,0,0,0,0,800,600);
        _sleep(50);
    }
    return 0;

}

END_OF_MAIN();

