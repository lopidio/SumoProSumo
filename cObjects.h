#ifndef COBJECTS_H_INCLUDED
#define COBJECTS_H_INCLUDED

enum ECharState{ ECS_STANDING = 0, ECS_ATACKING = 2, ECS_WALKING = 1, ECS_WALKINGBACK = -1, ECS_DEAD = 4, ECS_ATACKED = 3 };
enum ECharNature { ECN_HUMAN=1, ECN_COMPUTER=2, ECN_NONE=0 };

class Character
{
public:
    unsigned short nFrames, ID, IDatacante; //número de frames e numero de identificação da instância
    static short nInstances;    //número de instâncias ativas.
    BITMAP* frameImage[15];        //imagens que serão carregadas para uso em animação
    BITMAP *pontos;                 //imagens q tão os pontos
    unsigned char animFrames[20];         //frames das animações
    bool atackAble, moveAble, atackColision, splashplay;     //controle de ataque
    //valores das teclas de ação
    bool keyUp, keyDown, keyLeft, keyRight, keyAtack;
    unsigned short keyIDUp, keyIDDown, keyIDLeft, keyIDRight, keyIDAtack;
    ///.:métodos, a definir:.
    void checkColision(Character &colider);   //método para checar se há colisão com uma dada instância
    bool checkInStand(short xStart, short yStart, short xEnd, short yEnd);    //método para checar se ainda está dentro da plataforma
    void update(short xStart, short yStart, short xEnd, short yEnd, BITMAP* buffer);          //atualiza a instância
    void setAnimLoop(unsigned short start, unsigned short end, short rate);//diz como a animação vai ser tocada...
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
    int X, Y;               //Coordenadas do sumô
    short HP;        //life do Sumô em questão
    ECharState state;       //Estado e natureza do sumô
    ECharNature nature;     //...
    unsigned short currentFrame, lowerFrame, upperFrame, moveSpeed, angle, atackTime, respawnTime, score, atackPower, cont_bucho;  //velocidade do movimento, frame atual, ângulo atual
    short animRate;
    //sons do boneco
    SAMPLE *colSound, *winSound, *splashSound;
};

// TODO (Windows#1#): Fazer a classe de gerenciamento das instancias dos Sumôs
//class gameManager
//{
//}

#endif // COBJECTS_H_INCLUDED
