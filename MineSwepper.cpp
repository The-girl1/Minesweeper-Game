#include<bits/stdc++.h>
using namespace std;
int Mines,Side;
#define Maxsides 25
#define Maxmines 99

bool isvalid(int x,int y)
{
    return (x>=0) && (x<Side) && (y>=0) && (y<Side);
}
//Choose difficulty level
void choosedifflevel()
{
    int n;
    cout<<"\nEnter the difficulty level \n1.Beginner (9X9 Sided and 10 mines) \n2.Medium (16X16 Sided and 40 mines) \n3.Hard (24X24 sided and 99 mines";
    cin>>n;
    if(n==1)
    {
        Side=9;
        Mines=10;
    }
    else if(n==2)
    {
        Side=16;
        Mines=40;
    }
    else
    {
        Side=24;
        Mines=99;
    }
}

//Initialize real and main board
void initialize(char mb[][Maxsides] , char rb[][Maxsides])
{
    srand(time(NULL));
    for(int i=0;i<Side;i++)
    {
        for(int j=0;j<Side;j++)
            mb[i][j] = rb[i][j] = '-';
    }
}

//Place mines on real board
void placeMine(char rb[][Maxsides] , int mine[][2])
{
    int x,y;
    int mark[Maxsides*Maxsides];
    memset(mark,false,sizeof(mark));
    for(int i=0;i<Mines;)
    {
        int random=rand() % (Side*Side);
        x=random/Side;
        y=random%Side;
        if(mark[random]==false)
        {
            mine[i][0] = x;
            mine[i][1] = y;
            rb[x][y]= '*';
            mark[random]=true;
            i++;
        }
    }
}

//Print main board
void print(char mb[][Maxsides])
{
    int i,j;
    cout<<"   \n";
    for(i=0;i<Side;i++)
        cout<<" "<<i;
    cout<<"\n\n";
    for(i=0;i<Side;i++)
    {
        cout<<i<<" ";
        for(j=0;j<Side;j++)
        {
            cout<<mb[i][j]<<" ";
        }
        cout<<endl;
    }
}
//Make move
void makeMove(int *x,int *y)
{
    cout<<"\nEnter your move (row no, col no)";
    cin>>*x>>*y;
}
//Check whether their is mine on location (x,y);
bool ismine(int x,int y , char board[][Maxsides])
{
    if(board[x][y]=='*')
        return true;
    else
        return false;
}
//Function to replace mine
void replacemine(int x,int y, char board[][Maxsides])
{
    for(int i=0;i<Side;i++)
    {
        for(int j=0;j<Side;j++)
        {
            if(board[i][j]=='-')
            {
                board[i][j]='*';
                board[x][y]='-';
                return ;
            }
        }
    }
}
//To count adjacent mines
int adjacentmines(int x,int y,int mines[][2],char rb[][Maxsides])
{
    int i,cnt=0;
    if(isvalid(x-1,y)==true)
        if(ismine(x-1,y,rb)==true)
        cnt++;
    if(isvalid(x+1,y)==true)
        if(ismine(x+1,y,rb)==true)
        cnt++;
    if(isvalid(x,y-1)==true)
        if(ismine(x,y-1,rb)==true)
        cnt++;
    if(isvalid(x,y+1)==true)
        if(ismine(x,y+1,rb)==true)
        cnt++;
    if(isvalid(x-1,y-1)==true)
        if(ismine(x-1,y-1,rb)==true)
        cnt++;
    if(isvalid(x+1,y+1)==true)
        if(ismine(x+1,y+1,rb)==true)
        cnt++;
    if(isvalid(x-1,y+1)==true)
        if(ismine(x-1,y+1,rb)==true)
        cnt++;
    if(isvalid(x+1,y-1)==true)
        if(ismine(x+1,y-1,rb)==true)
        cnt++;
    return cnt;
}
//Recursive function to play
bool playutil(char mb[][Maxsides],char rb[][Maxsides],int mines[][2],int x, int y,int *moves)
{
    if(mb[x][y]!='-')
    {
        return false;
    }
    if(rb[x][y]=='*')
    {
        mb[x][y]='*';
        for(int i=0;i<Mines;i++)
        {
            mb[mines[i][0]][mines[i][1]]='*';
        }
        print(mb);
        cout<<"\n YOU LOST!!!! \n";
        return true;
    }
    else
    {
        int cnt=adjacentmines(x,y,mines,rb);
        (*moves)--;
        mb[x][y]=cnt+'0';
        if(!cnt)
        {
            if(isvalid(x-1,y)==true)
                if(ismine(x-1,y,rb)==false)
                playutil(mb,rb,mines,x-1,y,moves);
            if(isvalid(x+1,y)==true)
                if(ismine(x+1,y,rb)==false)
                playutil(mb,rb,mines,x+1,y,moves);
            if(isvalid(x,y-1)==true)
                if(ismine(x,y-1,rb)==false)
                playutil(mb,rb,mines,x,y-1,moves);
            if(isvalid(x,y+1)==true)
                if(ismine(x,y+1,rb)==false)
                playutil(mb,rb,mines,x,y+1,moves);
            if(isvalid(x-1,y-1)==true)
                if(ismine(x-1,y-1,rb)==false)
                playutil(mb,rb,mines,x-1,y-1,moves);
            if(isvalid(x+1,y+1)==true)
                if(ismine(x+1,y+1,rb)==false)
                playutil(mb,rb,mines,x+1,y+1,moves);
            if(isvalid(x-1,y+1)==true)
                if(ismine(x-1,y+1,rb)==false)
                playutil(mb,rb,mines,x-1,y+1,moves);
            if(isvalid(x+1,y-1)==true)
                if(ismine(x+1,y-1,rb)==false)
                playutil(mb,rb,mines,x+1,y-1,moves);
        }
        return false;
    }
}
//Main function for playing game
void play()
{
    bool gameover=false;
    char mainboard[Maxsides][Maxsides] , realboard[Maxsides][Maxsides] ;
    int moves = Side*Side - Mines , x, y;
    int mines[Maxsides][2];
    initialize(mainboard,realboard);
    placeMine(realboard , mines);
    int currMove = 0;
    while(gameover==false)
    {
        cout<<"\nCurrent Board status-> ";
        print(mainboard);
        makeMove(&x,&y);
        if(currMove==0)
        {
            if(ismine(x,y,realboard)==true)
                replacemine(x,y,realboard);
        }
        currMove++;
        gameover = playutil(mainboard,realboard,mines,x,y,&moves);
    }
}

int main()
{
    choosedifflevel();
    play();
}
