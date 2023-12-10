#include <iostream>
#include <fstream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace std::chrono;
ofstream g("debugging.txt");
int score=0;
int high_score=0;
bool gameover = false;
char direction='s';
int length = 15;            //change length and height (max=~30)
int height = 15;
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
void sleep(int microsec)
{
    std::this_thread::sleep_for(std::chrono::microseconds(microsec));
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
    //g<<"fruit:"<<fruit.ii<<" "<<fruit.jj<<" "<<poz<<endl;
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
    for(int i=0;i<=height+1;i++)
    {
        for(int j=0;j<=length+1;j++)
        {
            if(a[i][j]==0) cout<<"  ";          //nothing
            else if(a[i][j]==1) cout<<"# ";     //wall
            else if(a[i][j]==2) cout<<"* ";     //snake
            else if(a[i][j]==3) cout<<"% ";     //fruit
        }
        cout<<endl;
    }
    cout<<"Score:"<<tail*10;
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
}
void move()
{
    
    if(snake[tail].ii!=0 && snake[tail].jj!=0)
    {
        a[snake[tail].ii][snake[tail].jj]=0;
    }
    
    for(int i=tail;i>0;i--)
        snake[i]=snake[i-1];
    
    switch(direction)
    {
        case 'w':
            //if(snake[0].ii-1==2) gameover=true;
            snake[0].ii--;
            break;
        case 'a':
            //if(snake[0].jj-1==2) gameover=true;
            snake[0].jj--;
            break;
        case 's':
            //if(snake[0].ii+1==2) gameover=true;
            snake[0].ii++;
            break;
        case 'd':
            //if(snake[0].jj+1==2) gameover=true;
            snake[0].jj++;
            break;
    }
    //a[snake[0].ii][snake[0].jj]=2;

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
    for(int i=1;i<=tail;i++)
    {
        if(snake[i].ii==snake[0].ii && snake[i].jj==snake[0].jj) gameover=true;
    }
    
}
void input()
{
    char aux=direction;
    for(int value=1;value<=10; value++)
    {
        if(_kbhit())
        {
            char aux1=_getch();
            if((aux1=='w' && aux!='s') || (aux1=='a' && aux!='d') || (aux1=='s' && aux!='w') || (aux1=='d' && aux!='a') || aux1=='p' || aux1=='8') direction=aux1;
        }
        sleep(1000);
    }
}
int main()
{
    setup();
    
    while(!gameover)
    {
        //auto begin = std::chrono::high_resolution_clock::now();

        draw();
        do{
            input();
            if(direction=='8') gameover=true;
        }while(direction=='p');
        move();

        //auto end = std::chrono::high_resolution_clock::now();
        //auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        //g<<elapsed.count()*1e-9<<" seconds"<<endl;
    }
    cout<<"Score:"<<tail*10;
    return 0;
}
