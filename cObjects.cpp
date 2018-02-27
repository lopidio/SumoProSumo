#include <allegro.h>
#include "cObjects.h"
#include <math.h>

short Character::nInstances = 1;//Inicializa o membro estático que conta quantas instâncias existem

//Definição dos Construtores
Character::Character(unsigned short nFrames, ECharNature nature, int X, int Y)
{
    this->currentFrame = 0;
    this->splashplay = true;
    this->nature = nature;
    this->atackPower = 5;
    this->cont_bucho = 20;
    this->ID = nInstances++;    //inicializa o índice da instância
    this->renascer = false;
    if (this->nature !=ECN_NONE)
    {
        this->setFrames();
        this->setAnimLoop(0, 0, 0);
        this->X = X;
        this->Y = Y;    //Inicializa a posição da instância
        this->nFrames = nFrames;    //diz quantos frames(animação) a imagem possúi
        this->atackAble = true;
        this->moveAble = true;  //a instância pode mover e atacar
        this->HP = 0;
        this->state = ECS_STANDING;     //define o estado inicial da instância
        //define o numero atual do frame, a velocidade,
        this->moveSpeed = 6;        //o ângulo inicial, os pontos e os contadores
        this->score = 0;
        this->atackTime = this->respawnTime = 0;
        //imagens
        this->pontos = load_bitmap("graphics/pontos.bmp", NULL);
        this->frameImage[0] = load_bitmap("graphics/fatty00.bmp", NULL);
        this->frameImage[1] = load_bitmap("graphics/fatty01.bmp", NULL);
        this->frameImage[2] = load_bitmap("graphics/fatty02.bmp", NULL);
        this->frameImage[3] = load_bitmap("graphics/fatty03.bmp", NULL);
        this->frameImage[4] = load_bitmap("graphics/fatty04.bmp", NULL);
        this->frameImage[5] = load_bitmap("graphics/fatty05.bmp", NULL);
        this->frameImage[6] = load_bitmap("graphics/fatty06.bmp", NULL);
        this->frameImage[7] = load_bitmap("graphics/fatty07.bmp", NULL);
        this->frameImage[8] = load_bitmap("graphics/fatty08.bmp", NULL);
        this->frameImage[9] = load_bitmap("graphics/fatty09.bmp", NULL);
        this->frameImage[10] = load_bitmap("graphics/fatty10.bmp", NULL);
        this->frameImage[11] = load_bitmap("graphics/waterguy1.bmp", NULL);
        this->frameImage[12] = load_bitmap("graphics/waterguy2.bmp", NULL);
        this->frameImage[13] = load_bitmap("graphics/waterguy3.bmp", NULL);
        this->frameImage[14] = load_bitmap("graphics/waterguy4.bmp", NULL);
        //sons
        this->colSound = load_wav("graphics/buchada.wav");
        this->winSound = load_wav("graphics/win.wav");
        this->splashSound = load_wav("graphics/queda.wav");

        this->respawnTime = 0;
        for (int x = 0; x <= 300; x++)
              for (int y = 0; y <= 30; y++)
              {
                   if (getpixel(pontos,x,y) == makecol(0,0,0))
                   {
                          if (ID == 1) putpixel(pontos,x,y, makecol(0,0,255));
                          if (ID == 2) putpixel(pontos,x,y, makecol(255,0,0));
                          if (ID == 3) putpixel(pontos,x,y, makecol(0,255,0));
                          if (ID == 4) putpixel(pontos,x,y, makecol(255,255,0));
                   }
              }

        for (int i = 0; i <=10; i++)
          for (int x = 0; x <= 72; x++)
                for (int y = 0; y <= 72; y++)
                {
                     if (getpixel(frameImage[i],x,y) == makecol(56,101,146))
                     { //tons claros
                          if (ID == 2) putpixel(frameImage[i],x,y, makecol(255,72,72));
                          if (ID == 3) putpixel(frameImage[i],x,y, makecol(55,255,55));
                          if (ID == 4) putpixel(frameImage[i],x,y, makecol(255,255,128));                                                                          
                     }
                     else if (getpixel(frameImage[i],x,y) == makecol(36,20,134))
                     {//tons médios
                          if (ID == 2) putpixel(frameImage[i],x,y, makecol(255,0,0));
                          if (ID == 3) putpixel(frameImage[i],x,y, makecol(0,255,0));
                          if (ID == 4) putpixel(frameImage[i],x,y, makecol(255,255,0));                                                                         
                     }                                     
                     else if (getpixel(frameImage[i],x,y) == makecol(36,28,56))
                     {//tons fortes
                          if (ID == 2) putpixel(frameImage[i],x,y, makecol(140,0,0));
                          if (ID == 3) putpixel(frameImage[i],x,y, makecol(0,30,0));
                          if (ID == 4) putpixel(frameImage[i],x,y, makecol(155,155,0));                                                                          
                     }
                     else if (getpixel(frameImage[i],x,y) == makecol(251,97,77))
                     { //thucas claras
                          if (ID == 1) putpixel(frameImage[i],x,y, makecol(56,101,146));
                          if (ID == 3) putpixel(frameImage[i],x,y, makecol(55,255,55));
                          if (ID == 4) putpixel(frameImage[i],x,y, makecol(255,255,128));                                                                          
                     }
                     else if (getpixel(frameImage[i],x,y) == makecol(203,56,8))
                     {//thuca forte
                          if (ID == 1) putpixel(frameImage[i],x,y, makecol(0,0,255));
                          if (ID == 3) putpixel(frameImage[i],x,y, makecol(0,255,0));
                          if (ID == 4) putpixel(frameImage[i],x,y, makecol(255,255,0));                                                                         
                     }                                     
                }
        //define as teclas do playerN
        switch (this->ID)
        {
            //player1
        case 1:
            this->keyIDAtack = KEY_RCONTROL;
            this->keyIDDown  = KEY_DOWN;
            this->keyIDUp    = KEY_UP;
            this->keyIDLeft  = KEY_LEFT;
            this->keyIDRight = KEY_RIGHT;
            this->angle = 0;
            break;
            //player2
        case 2:
            this->keyIDAtack = KEY_G;
            this->keyIDDown  = KEY_S;
            this->keyIDUp    = KEY_W;
            this->keyIDLeft  = KEY_A;
            this->keyIDRight = KEY_D;
            this->angle = 192;
            break;
            //player3
        case 3:
            this->keyIDAtack = KEY_P;
            this->keyIDDown  = KEY_K;
            this->keyIDUp    = KEY_I;
            this->keyIDLeft  = KEY_J;
            this->keyIDRight = KEY_L;
            this->angle = 64;
            break;
            //player4
        case 4:
            this->keyIDAtack = KEY_PGUP;
            this->keyIDDown  = KEY_5_PAD;
            this->keyIDUp    = KEY_8_PAD;
            this->keyIDLeft  = KEY_4_PAD;
            this->keyIDRight = KEY_6_PAD;
            this->angle = 128;
            break;
        }
    }
    else
        this->X = this->Y = 1000;
}

//Definição dos métodos da classe
void Character::Respawn(char location)  //retorna o personagem à plataforma
{
    switch (location)
    {
    case 1:
        this->X = 380;
        this->Y = 110;
        this->angle = 0;
        break;
    case 2:
        this->X = 200;
        this->Y = 270;
        this->angle = 192;
        break;
    case 3:
        this->X = 560;
        this->Y = 270;
        this->angle = 64;
        break;
    case 4:
        this->X = 380;
        this->Y = 420;
        this->angle = 128;
        break;
    }
    //else Respawn(blabla)
}
void Character::setAnimLoop(unsigned short start, unsigned short end, short rate)//faz um loop da animação entre os limites dados.
{
    this->lowerFrame = this->currentFrame = start;
    this->upperFrame = end;
    this->animRate = rate;
}
//checa se a instância ainda está na plataforma
bool Character::checkInStand(short xStart, short yStart, short xEnd, short yEnd)
{
    if ((this->X > xStart && this->X < xEnd) && (this->Y > yStart && this->Y < yEnd))
        return true;
    else
        return false;
}
//checagem de colisão
void Character::checkColision(Character &colider)//precisa ser uma referência para que os valores da instancia sofredora mudem
{
    if (colider.state != ECS_DEAD && this->state != ECS_DEAD)
        if (this->state == ECS_ATACKING)
            if  (((this->X - (25*(sin(this->angle*1.40625*M_PI/180))) - colider.X)) *
                    ((this->X - (12*(sin(this->angle*1.40625*M_PI/180))) - colider.X)) +
                    ((this->Y + (25*(cos(this->angle*1.40625*M_PI/180))) - colider.Y)) *
                    ((this->Y + (12*(cos(this->angle*1.40625*M_PI/180))) - colider.Y)) <= (38)*(38))
            {
                colider.state = ECS_ATACKED;
                this->atackTime = 15;
                this->state = ECS_STANDING;
                play_sample(this->colSound, 200, 128, 1000, false);
                  colider.X += 1 + (2 * this->atackPower * (int)-(this->moveSpeed * (sin(this->angle*1.40625*M_PI/180))));
                  colider.Y += 1 + (2 * this->atackPower * (int)(this->moveSpeed * (cos(this->angle*1.40625*M_PI/180))));
                if (!colider.checkInStand(160, 65, 590, 480))
                       this->score++;
            }
        if (colides(colider))
        {
              double alpha = atan((colider.Y - Y)/(colider.X - X + 0.000003));

              X += (colider.X - X <= 0)? cos(alpha)*20 :- cos(alpha)*20;
              Y += (colider.Y - Y <= 0)? sin(alpha)*20 :- sin(alpha)*20;

              colider.X -= (colider.X - X <= 0)? cos(alpha)*5 :- cos(alpha)*5;
              colider.Y -= (colider.Y - Y <= 0)? sin(alpha)*5 :- sin(alpha)*5;
        }
}

bool Character::colides(Character colider){
         if ((this->X - colider.X) * (this->X - colider.X) + (this->Y - colider.Y) * (this->Y - colider.Y) <= (50)*(50))
                      return true;
         return false;
    }
//atualiza a cada frame o personagem em questão
void Character::update(short xStart, short yStart, short xEnd, short yEnd, BITMAP* buffer)
{
    printPonto(buffer, pontos);
    this->cont_bucho++; 
    this->keyAtack = key[this->keyIDAtack];
    this->keyDown  = key[this->keyIDDown];
    this->keyUp    = key[this->keyIDUp];
    this->keyLeft  = key[this->keyIDLeft];
    this->keyRight = key[this->keyIDRight];
    //atualiza os frames:.
    this->currentFrame += this->animRate;
    if (this->currentFrame >= this->upperFrame && this->animRate>=0)
            this->currentFrame = this->lowerFrame;
        else
            if (this->currentFrame <= this->upperFrame && this->animRate<=0)
                this->currentFrame = this->lowerFrame;

    if (this->checkInStand(xStart, yStart, xEnd, yEnd))
    {
        //contadores:.
        if (this->state == ECS_ATACKING)
        {
            this->atackTime++;
        }
        if (this->atackTime >=4)
        {
            this->atackAble = true;
            this->state = ECS_STANDING;
            this->setAnimLoop(0, 0, 0);
            this->atackTime = 0;
        }

        //move o boneco
        if (this->state != ECS_DEAD)
            this->move();
        if (this->state == ECS_ATACKED)
            this->atackColision++;
        if (this->atackColision>=1)
        {
            this->atackColision = 0;
            this->state = ECS_STANDING;
        }
    }
    else
    {
        set_trans_blender(80, 80, 80, 90);
        if(this->splashplay)    //se ele acabou de cair na agua, toca som e animação
        {
            play_sample(this->splashSound, 200, 128, 1000, false);
            setAnimLoop(16, 19, 1);
            this->splashplay = false;
        }
        this->state = ECS_DEAD;
        this->moveAble = false;
        this->respawnTime++;
        if (this->respawnTime >= 20)
        {
            this->renascer = true;
            setAnimLoop(0, 0, 0);
            this->moveAble = true;
            this->atackAble = true;
            this->atackTime = 0;
            this->state = ECS_STANDING;
            this->splashplay = true;
            this->respawnTime = 0;
        }
    }
}
//move o personagem caso alguma tecla seja apertada:.
void Character::move()
{
    //teclas direita e esquerda para rotação
    if ((this->state != ECS_DEAD && this->state != ECS_ATACKING && this->state != ECS_ATACKED) && this->keyLeft)
        this->angle -= 10;

    if ((this->state != ECS_DEAD && this->state != ECS_ATACKING && this->state != ECS_ATACKED) && this->keyRight)
        this->angle += 10;

    //teclas cima e baixo para translação
    if ((this->state != ECS_DEAD && this->state != ECS_ATACKING && this->state != ECS_ATACKED) && this->keyUp)
    {
        if (this->state != ECS_WALKING)
        {
            setAnimLoop(0, 7, 1);
            this->state = ECS_WALKING;
        }
    }
    else
        if ((this->state != ECS_DEAD && this->state != ECS_ATACKING && this->state != ECS_ATACKED) && this->keyDown)
        {
            if (this->state != ECS_WALKINGBACK)
            {
                setAnimLoop(7, 0, -1);
                this->state = ECS_WALKINGBACK;
            }
        }
        else
            //tecla de ataque
            if ((this->state != ECS_DEAD && this->state != ECS_ATACKING && this->atackAble) && this->keyAtack && this->cont_bucho > 20)
            {
                this->cont_bucho = 0;
                this->state = ECS_ATACKING;
                this->atackAble = false;
                this->atackTime = 0;
                setAnimLoop(8, 12, 1);
            }
            else
                if (this->state != ECS_ATACKING && this->state != ECS_ATACKED && this->state != ECS_STANDING)
                {
                    setAnimLoop(0, 0, 0);
                    this->state = ECS_STANDING;
                }

    if (this->moveAble && (this->state != ECS_DEAD && this->state != ECS_ATACKED))
    {
        this->X += -2 * (int)(this->moveSpeed * (sin(this->angle * 1.40625*M_PI/180))) *this->state;
        this->Y +=  2 * (int)(this->moveSpeed * (cos(this->angle * 1.40625*M_PI/180))) *this->state;
    }
}

bool Character::exists()
{
    if (this->nature == ECN_HUMAN)
        return true;
    return false;
}

void Character::setFrames()
{
    animFrames[0] = 0;
    animFrames[1] = 1;
    animFrames[2] = 2;
    animFrames[3] = 1;
    animFrames[4] = 0;
    animFrames[5] = 3;
    animFrames[6] = 4;
    animFrames[7] = 3;
    animFrames[8] = 7;
    animFrames[9] = 5;
    animFrames[10] = 6;
    animFrames[11] = 5;
    animFrames[12] = 7;
    animFrames[13] = 8;
    animFrames[14] = 9;
    animFrames[15] = 10;
    animFrames[16] = 11;
    animFrames[17] = 12;
    animFrames[18] = 13;
    animFrames[19] = 14;
}

void Character::print(BITMAP* buffer, bool b)
{
         if (state != ECS_DEAD && b)
              rotate_sprite(buffer, this->frameImage[this->animFrames[this->currentFrame]], this->X-10, this->Y-10, itofix(this->angle));
         else if (state == ECS_DEAD && !b)
              draw_trans_sprite(buffer, this->frameImage[this->animFrames[this->currentFrame]], this->X, this->Y);
}

BITMAP* getnum(unsigned short x, BITMAP*pontos){
        BITMAP* res = create_bitmap(60,30);
        clear_to_color(res, makecol(255,0,255));
        masked_blit(pontos, res, x%10*30,0,30,0,30,30);
        x/=10;
        masked_blit(pontos, res, x%10*30,0,00,0,30,30);
        return res;
}

void Character::printPonto(BITMAP *buffer, BITMAP *pnt){
         BITMAP* pontos = getnum(score, pnt);                         
         if (ID == 1) masked_blit(pontos, buffer, 0,0, 10,10,60,30);
         if (ID == 2) masked_blit(pontos, buffer, 0,0, 10,550,60,30);
         if (ID == 3) masked_blit(pontos, buffer, 0,0, 730,10,60,30);
         if (ID == 4) masked_blit(pontos, buffer, 0,0, 730,550,60,30);
    }
