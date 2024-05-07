#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;
int score=0;
int high_score=0;
bool gameover = false;
char direction='s';
int length = 10;
int height = 10;
int a[30][30];
int tail=0;
struct{
    int ii=0;
    int jj=0;
} fruit, snake[900];
int abso(int n)
{
    if(n<0) return -n;
    return n;
}
void gen_fruit()
{
    int v[1000];
    int k=0;
    for(int i=0;i<=height;i++)
        for(int j=0;j<=length;j++)
            if(a[i][j]==0) {v[k]=90000+i*100+j; k++;}
    int poz=rand()%k;
    fruit={v[poz]/100%100, v[poz]%100};
}
void setup()
{
    srand(time(0));
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
void draw()
{
    char total[10000]="";
    char aux[100]="\n";
    for(int i=0;i<=height+1;i++)
    {
        char s[100]="";
        for(int j=0;j<=length+1;j++)
        {
            if(a[i][j]==0) s[j*2]=' ';
            else if(a[i][j]==1) s[j*2]='#';
            else if(a[i][j]==2) s[j*2]='*';
            else if(a[i][j]==3) s[j*2]='%';
            s[j*2+1]=' ';
        }
        strcat(total,s);
        strcat(total,aux);
    }
    cout<<total<<"Score:"<<tail*10<<'\n';
}
void move()
{
    if(snake[tail].ii!=0 && snake[tail].jj!=0)
        a[snake[tail].ii][snake[tail].jj]=0;
    
    for(int i=tail;i>0;i--)
        snake[i]=snake[i-1];
    
    switch(direction)
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

    if(snake[0].ii==0 || snake[0].ii==height+1)
    {
        a[snake[0].ii][snake[0].jj]=1;
        snake[0].ii=abso(height-snake[0].ii);
    }
    else if(snake[0].jj==0 || snake[0].jj==length+1)
    {
        a[snake[0].ii][snake[0].jj]=1;
        snake[0].jj=abso(length-snake[0].jj);
    }
    a[snake[0].ii][snake[0].jj]=2;
    if(snake[0].ii==fruit.ii && snake[0].jj==fruit.jj)
    {
        a[fruit.ii][fruit.jj]=2;
        tail++;
        gen_fruit();
        a[fruit.ii][fruit.jj]=3;
    }
    for(int i=1;i<=tail && gameover==false;i++)
    {
        if(snake[i].ii==snake[0].ii && snake[i].jj==snake[0].jj) gameover=true;
    }
    
}
void input()
{
    char aux=direction;
    for(int value=1;value<=9000; value++)
    {
        if(_kbhit())
        {
            char aux1=_getch();
            if((aux1=='w' && aux!='s') || (aux1=='a' && aux!='d') || (aux1=='s' && aux!='w') || (aux1=='d' && aux!='a') || aux1=='p' || aux1=='8') direction=aux1;
        }
    }
}
int main()
{
    setup();

    while(!gameover)
    {
        draw();

        do{
            input();
            if(direction=='8') gameover=true;
        }while(direction=='p');

        move();
    }
    return 0;
}
