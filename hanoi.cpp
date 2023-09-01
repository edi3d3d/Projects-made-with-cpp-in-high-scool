//this is just a visual representation of the solving steps for the towers of hanoi
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
ifstream f ("date.in");  //on each line there must be a move (a letter from "a" to "c", a space and another letter from a to c) you can use the hanoi solver (hanoi_solver.cpp (will add it soon)) to get the letters, the last letter has to be a "p" so it will end)
void swap(char s[], char s1[])
{
    char str[100];
    strcpy(str, s);
    strcpy(s,s1);
    strcpy(s1,str);
}
int main()
{
    int n=1;
    char t1[10][30]={
        {"         *H*          "},
        {"        **H**         "},
        {"       ***H***        "},
        {"      ****H****       "},
        {"     *****H*****      "},
        {"    ******H******     "},
        {"   *******H*******    "},
        {"  ********H********   "},
        {" HHHHHHHHHHHHHHHHHHHH "}
    };
    char t2[10][30]={
        {"          H           "},
        {"          H           "},
        {"          H           "},
        {"          H           "},
        {"          H           "},
        {"          H           "},
        {"          H           "},
        {"          H           "},
        {" HHHHHHHHHHHHHHHHHHHH "}
    };
    char t3[10][30]={
        {"          H           "},
        {"          H           "},
        {"          H           "},
        {"          H           "},
        {"          H           "},
        {"          H           "},
        {"          H           "},
        {"          H           "},
        {" HHHHHHHHHHHHHHHHHHHH "}
    };

    for(int i=0;i<9;i++)
        cout<<t1[i]<<t2[i]<<t3[i]<<endl;

    char inp, inp1;
    int aa=-1,bb=7,cc=7;
    while(inp!='p')
    {
        f>>inp;
        f>>inp1;

        cout<<aa<<" "<<bb<<" "<<cc<<endl;

        if((inp=='a' || inp=='A')&& (inp1=='b' || inp1=='B')) {swap(t1[aa+1],t2[bb]); aa++; bb--;}
        else if((inp=='a' || inp=='A')&& (inp1=='c' || inp1=='C')) {swap(t1[aa+1],t3[cc]); aa++; cc--;}
        else if((inp=='b' || inp=='B')&& (inp1=='a' || inp1=='A')) {swap(t2[bb+1],t1[aa]); bb++; aa--;}
        else if((inp=='b' || inp=='B')&& (inp1=='c' || inp1=='C')) {swap(t2[bb+1],t3[cc]); bb++; cc--;}
        else if((inp=='c' || inp=='C')&& (inp1=='a' || inp1=='A')) {swap(t3[cc+1],t1[aa]); cc++; aa--;}
        else if((inp=='c' || inp=='C')&& (inp1=='b' || inp1=='B')) {swap(t3[cc+1],t2[bb]); cc++; bb--;}

        for(int i=0;i<9;i++)
            cout<<t1[i]<<t2[i]<<t3[i]<<endl;
    }
    return 0;
}
