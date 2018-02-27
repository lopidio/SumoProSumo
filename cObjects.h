#ifndef COBJECTS_H_INCLUDED
#define COBJECTS_H_INCLUDED

enum ECharState{ ECS_STANDING = 0, ECS_ATACKING = 2, ECS_WALKING = 1, ECS_WALKINGBACK = -1, ECS_DEAD = 4, ECS_ATACKED = 3 };
enum ECharNature { ECN_HUMAN=1, ECN_COMPUTER=2, ECN_NONE=0 };

class Character
{
public:
    unsigned short nFrames, ID, IDatacante; //n�mero de frames e numero de identifica��o da inst�ncia
    static short nInstances;    //n�mero de inst�ncias ativas.
    BITMAP* frameImage[15];        //imagens que ser�o carregadas para uso em anima��o
    BITMAP *pontos;                 //imagens q t�o os pontos
    unsigned char animFrames[20];         //frames das anima��es
    bool atackAble, moveAble, atackColision, splashplay;     //controle de ataque
    //valores das teclas de a��o
    bool keyUp, keyDown, keyLeft, keyRight, keyAtack;
    unsigned short keyIDUp, keyIDDown, keyIDLeft, keyIDRight, keyIDAtack;
    ///.:m�todos, a definir:.
    void checkColision(Character &colider);   //m�todo para checar se h� colis�o com uma dada inst�ncia
    bool checkInStand(short xStart, short yStart, short xEnd, short yEnd);    //m�todo para checar se ainda est� dentro da plataforma
    void update(short xStart, short yStart, short xEnd, short yEnd, BITMAP* buffer);          //atualiza a inst�ncia
    void setAnimLoop(unsigned short start, unsigned short end, short rate);//diz como a anima��o vai ser tocada...
    void Respawn(char location);
    void move();
    void setFrames();
    bool exists();
    unsigned short getScore(){return score;};
    bool colides (Character);
    bool renascer;
    void print(BITMAP* buffer, bool b);
    void printPonto(BITMAP *buffer, BITMAP *pontos);
    //construtores
    Character(unsigned short nFrames, ECharNature nature, int X, int Y);
    //Character(const Character &Instance);

private:
    int X, Y;               //Coordenadas do sum�
    short HP;        //life do Sum� em quest�o
    ECharState state;       //Estado e natureza do sum�
    ECharNature nature;     //...
    unsigned short currentFrame, lowerFrame, upperFrame, moveSpeed, angle, atackTime, respawnTime, score, atackPower, cont_bucho;  //velocidade do movimento, frame atual, �ngulo atual
    short animRate;
    //sons do boneco
    SAMPLE *colSound, *winSound, *splashSound;
};

// TODO (Windows#1#): Fazer a classe de gerenciamento das instancias dos Sum�s
//class gameManager
//{
//}

#endif // COBJECTS_H_INCLUDED
