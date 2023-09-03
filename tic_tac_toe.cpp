#include <iostream>
#include <stdlib.h>
using namespace std;
void creare_tabla(char a[5][5])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            a[i][j]=' ';
            cout<<"["<<7+j-(3*i)<<"] ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void afisare_tabla(char a[5][5])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            cout<<"["<<a[i][j]<<"] ";
        cout<<endl;
    }
    cout<<endl;
}
int castig(char a[5][5], int jucator, int depth)
{
    int win=20;
    
    if(depth==9) win=0;
    
    for(int i=0;i<3;i++)
    {
        if(a[i][0]==a[i][1] && a[i][1]==a[i][2] && a[i][2]!=' ') win=1;
        if(a[0][i]==a[1][i] && a[1][i]==a[2][i] && a[2][i]!=' ') win=1;
    }
    
    if(a[0][0]==a[1][1] && a[1][1]==a[2][2] && a[2][2]!=' ') win=1;
        else if(a[0][2]==a[1][1] && a[1][1]==a[2][0] && a[2][0]!=' ') win=1;
    
    if(win==1)
    {
        if(jucator==1) return 1;
        else return -1;
    }
    return win;
}
int castig_minimax(char a[5][5], int depth, bool maximizer)
{
    int win_minimax=20;
    
    for(int i=0;i<3;i++)
    {
        if(a[i][0]==a[i][1] && a[i][1]==a[i][2] && a[i][2]!=' ') win_minimax=1;
        if(a[0][i]==a[1][i] && a[1][i]==a[2][i] && a[2][i]!=' ') win_minimax=1;
    }

    if(a[0][0]==a[1][1] && a[1][1]==a[2][2] && a[2][2]!=' ') win_minimax=1;
        else if(a[0][2]==a[1][1] && a[1][1]==a[2][0] && a[2][0]!=' ') win_minimax=1;
    
    if(win_minimax==20) return 20;
    else if(depth==9 && win_minimax==20) return 0;
    
    if(maximizer==true) return  win_minimax*(10-depth);
    else return -win_minimax*(10-depth);
}
int minimax(char a[5][5], int depth, int jucator, bool maximizer)
{
    int i, j, win_minimax, max=-10, min=10, val_minimax;
    if(depth<9)
    {
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                if(a[i][j]==' ')
                {
                    if((jucator+maximizer)%2==0) a[i][j]='X';
                    else a[i][j]='O';
                    win_minimax=castig_minimax(a, depth, maximizer);
                    if(win_minimax==20)
                    {
                        if(maximizer==true) val_minimax=minimax(a, depth+1, jucator, false);
                        else val_minimax=minimax(a, depth+1, jucator, true);
                        
                        if(val_minimax>max) max=val_minimax;
                        if(val_minimax<min) min=val_minimax;

                        a[i][j]=' ';
                    }
                    else
                    {
                        a[i][j]=' ';
                        return win_minimax;
                    }
                }
        if(maximizer==true) return max;
        else return min;
    }
    else return castig_minimax(a, depth, maximizer);
}
void poz_om(char a[5][5], int jucator)
{
    citire:
    int nr, i=0, j;
    cout<<"Jucatorul "<<jucator<<":";
    cin>>nr;

    i=(9-nr)/3;
    j=(nr-1)%3;

    if(a[i][j]==' ' && jucator==1) a[i][j]='X';
    else if(a[i][j]==' ' && jucator==2) a[i][j]='O';
    else goto citire;
}
void poz_RAI(char a[5][5], int jucator)
{
    srand(time(0));
    int i=0, j, v[9]={}, k=0, n;

    for(i=0;i<=2;i++)
        for(j=0;j<=2;j++)
            if(a[i][j]==' ') {v[k]=i*10+j; k++;}

    n=rand()%k;
    i=0;
    if(v[n]<10) j=v[n];
    else
    {
        i=v[n]/10;
        j=v[n]%10;
    }

    cout<<"Jucatorul "<<jucator<<":"<<7+j-(3*i)<<endl;
    if(jucator==1) a[i][j]='X';
    else a[i][j]='O';
}
void poz_AAI(char a[5][5], int depth, int jucator)
{
    int i, j, win_minimax, max=-20, maxi=0, maxj=0, val_minimax;
    bool maximizer=true;
    if(depth>0)
    {
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                if(a[i][j]==' ')
                {
                    if(jucator==1) a[i][j]='X';
                    else a[i][j]='O';
                    win_minimax=castig_minimax(a, depth, maximizer);
                    if(win_minimax==20)
                    {
                        val_minimax=minimax(a, depth+1, jucator, false);
                        
                        if(val_minimax>max) 
                        {
                            max=val_minimax;
                            maxi=i;
                            maxj=j;
                        }
                        else if(val_minimax==max)
                        {
                            srand(time(0));
                            int random=rand()%2;
                            if(random==0)
                            {
                                max=val_minimax;
                                maxi=i;
                                maxj=j;
                            }
                        }
                    }
                    else if(win_minimax>max) max=win_minimax;
                    a[i][j]=' ';
                    cout<<val_minimax<<endl;
                }
        cout<<"Jucatorul "<<jucator<<":"<<7-3*maxi+maxj<<endl;
        if(jucator==1) a[maxi][maxj]='X';
        else a[maxi][maxj]='O';
    } 
    else poz_RAI(a, jucator);
}
int main()
{
    int win=20, jucator=1, player1, player2, p1_win=0, p2_win=0, rem=0, depth=0, k=0;
    char a[5][5], replay;
    
    int repetitions=-1;

    if(repetitions==0)
    {
        nr_rep:
        cout<<"Repetitions:";
        cin>>repetitions;
        repetitions--;
    }

    citire_juc:
    cout<<"jucatorul 1 este Om, RandomAI, AdvancedAI (1, 2, 3)"<<endl;      //citire jucator 1      player1
    cin>>player1;
    if(player1==7) k++;
	else if(player1<1 || player1>3) goto citire_juc;

	citire_juc1:
    cout<<"jucatorul 2 este Om, RandomAI, AdvancedAI (1, 2, 3)"<<endl;      //citire jucator 2      player2
    cin>>player2;
    if(player2==9 && k!=0) {k=2; goto nr_rep;}
	else if(player2<1 || player2>3) goto citire_juc1;


    start_game:
    creare_tabla(a);
    afisare_tabla(a);
    
    while(win==20)
    {
        if(jucator==1)
        {
            if(player1==1) poz_om(a, jucator);
            else if(player1==2) poz_RAI(a, jucator);
            else if(player1==3) poz_AAI(a, depth, jucator);
        }
        else
        {
            if(player2==1) poz_om(a, jucator);
            else if(player2==2) poz_RAI(a, jucator);
            else if(player2==3) poz_AAI(a, depth, jucator);
        }
        depth++;
        afisare_tabla(a);

        win=castig(a, jucator, depth);
        if(jucator==1) jucator=2;
        else jucator=1;

    }

    if(win==0)
    {
        cout<<"remiza"<<endl;
        rem++;
    }
    else if(win==1)
    {
        cout<<"Player 1 wins"<<endl;
        p1_win++;
    }
    else if(win==-1)
    {
        cout<<"Player 2 wins"<<endl;
        p2_win++;
    }

    while(repetitions>0)
    {
        repetitions--;
        win=20;
        jucator=1;
        depth=0;
        goto start_game;
    }
    if(repetitions==0)
    {
        cout<<endl<<"Player 1 wins "<<p1_win;
        cout<<endl<<"Player 2 wins "<<p2_win;
        cout<<endl<<"Draws "<<rem;
        return 0;
    }
    
    cout<<endl<<"Replay? Y/N"<<endl;
    cin>>replay;
    if(replay=='Y' || replay=='y')
    {
        win=20;
        jucator=1;
        depth=0;
        goto start_game;
    }
    else
    {
        cout<<endl<<"Player 1 wins "<<p1_win;
        cout<<endl<<"Player 2 wins "<<p2_win;
        cout<<endl<<"Draws "<<rem;
        return 0;
    }
}
