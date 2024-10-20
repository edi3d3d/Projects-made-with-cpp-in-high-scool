#include <iostream>
#include <fstream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;
using namespace std::chrono;
ofstream g("debugging.txt");
int score=0;
int high_score=0;
bool gameover = false;
char direction='s';
int length = 10;            //change length and height (max=~30)
int height = 10;            //cu cat este mai mare cu atat creste posibilitatea de stuttering
int a[30][30];
int tail=0;
struct{                     //coordonate i si j din matrice
    int ii=0;
    int jj=0;
} fruit, snake[900];
int abso(int n)             //absolut sau modulul matematic
{
    if(n<0) return -n;
    return n;
}
void sleep(int microsec)    //pune pauza, unitatea de timp este microsecunda
{
    std::this_thread::sleep_for(std::chrono::microseconds(microsec));
}
void gen_fruit()            //generarea fructului
{
    int v[1000];
    int k=0;
    for(int i=0;i<=height;i++)
        for(int j=0;j<=length;j++)
            if(a[i][j]==0) {v[k]=90000+i*100+j; k++;}           //se noteaza fiecare pozitie libera
    int poz=rand()%k;                                           //folosind un generator de numere intamplator si se alege o pozitie noua a fructului
    fruit={v[poz]/100%100, v[poz]%100};                         //actualizarea fructului cu pozitia noua
}
void setup()                //generarea tablei goale, a zidului inconjurator, a sarpelui si a fructului
{
    srand(time(0));         //salvarea timpului initial pentru generatorul de numere a fructului
    for(int i=0;i<=length+1;i++)
    {
        a[0][i]=1;
        a[height+1][i]=1;
    }
    for(int i=0;i<=height+1;i++)
    {
        a[i][0]=1;
        a[i][length+1]=1;
    }
    snake[0]={3, 7};
    gen_fruit();
    a[fruit.ii][fruit.jj]=3;
    a[snake[0].ii][snake[0].jj]=2;
}
void draw()                 //afisare. Fiecare valoare este salvata intr-un vector de caractere, inclusiv sfarsitul de linie si este afisat la final pentru a elimina stuttering-ul
{
    system("cls");
    char total[10000]="";
    char aux[100]="\n";
    for(int i=0;i<=height+1;i++)
    {
        char s[100]="";
        for(int j=0;j<=length+1;j++)
        {
            if(a[i][j]==0) s[j*2]=' ';          //nothing
            else if(a[i][j]==1) s[j*2]='#';     //wall
            else if(a[i][j]==2) s[j*2]='*';     //snake
            else if(a[i][j]==3) s[j*2]='%';     //fruit
            s[j*2+1]=' ';
        }
        strcat(total,s);
        strcat(total,aux);
    }
    cout<<total<<"Score:"<<tail*10<<'\n';
}
void move()
{
    
    if(snake[tail].ii!=0 && snake[tail].jj!=0)  //eliminarea "cozii" sarpelui pentru a putea muta "corpul" in fata
    {
        a[snake[tail].ii][snake[tail].jj]=0;
    }
    
    for(int i=tail;i>0;i--)                     //miscarea "corpului" sarpelui
        snake[i]=snake[i-1];
    
    switch(direction)                           //schimbarea directiei si miscarea "capului" sarpelui
    {
        case 'w':
            snake[0].ii--;
            break;
        case 'a':
            snake[0].jj--;
            break;
        case 's':
            snake[0].ii++;
            break;
        case 'd':
            snake[0].jj++;
            break;
    }

    if(snake[0].ii==0 || snake[0].ii==height+1)         //detectarea de zid si mutarea sarpelui la zidul opus
    {
        a[snake[0].ii][snake[0].jj]=1;
        snake[0].ii=abso(height-snake[0].ii);
    }
    else if(snake[0].jj==0 || snake[0].jj==length+1)    //detectarea de zid si mutarea sarpelui la zidul opus
    {
        a[snake[0].ii][snake[0].jj]=1;
        snake[0].jj=abso(length-snake[0].jj);
    }
    a[snake[0].ii][snake[0].jj]=2;                      //desenarea "capului" nou al sarpelui
    if(snake[0].ii==fruit.ii && snake[0].jj==fruit.jj)  //atunci cand "capul" sarpelui mananca fruct:
    {
        a[fruit.ii][fruit.jj]=2;                        //fructul devine sarpele
        tail++;                                         //coada creste iar actualizarea o sa se intample la prima schimbare a sarpelui
        gen_fruit();                                    //generarea unui fruct nou
        a[fruit.ii][fruit.jj]=3;                        //pozitia fructului actualizata
    }
    for(int i=1;i<=tail;i++)                            //verificare sfarsit joc (daca "capul" sarpelui atinge "corpul")
    {
        if(snake[i].ii==snake[0].ii && snake[i].jj==snake[0].jj) gameover=true;
    }
    
}
void input()                //citirea directiei, pauza sau opririi programului
{
    char aux=direction;
    for(int value=1;value<=10; value++)
    {
        if(_kbhit())    //detectare input de la tastatura
        {
            char aux1=_getch(); //in caz de detectare iti returneaza caracterul tastat
            if((aux1=='w' && aux!='s') || (aux1=='a' && aux!='d') || (aux1=='s' && aux!='w') || (aux1=='d' && aux!='a') || aux1=='p' || aux1=='8') direction=aux1;  //verificare pentru schimbare de directie, pauza sau "opreste jocul"
        }
        sleep(1000);
    }
}
int main()
{
    setup();                //generare

    while(!gameover)        //se repeta pana cand jocul se termina
    {
        draw();             //se deseneaza sarpele si zidul

        do{
            input();        //se citeste input
            if(direction=='8') gameover=true;               //sfarsit de joc
        }while(direction=='p');                             //se pune pauza

        move();                                             //actualizarea tablei si a pozitiei sarpelui
    }
    return 0;
}
