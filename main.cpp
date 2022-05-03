#include <bits/stdc++.h>
#pragma GCC optimize("-Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx2,tune=native")
using namespace std;
///Ultimate tic tac toe bot using Monte Carlo Tree Search
int8_t GRID[3][3][3][3],GRID2[3][3][3][3],CHK[3][3];
mt19937 rng(2005);
int LL,RR;
void UPDGRID(int CO1=-1,int CO2=-1)
{
    for(int i=0; i<3; i++)
    {
        if(CO1==i||CO1==-1)
            for(int l=0; l<3; l++)
            {
                if(CO2!=l&&CO2!=-1)
                    continue;
                int A=0,B=0,CNT=0;
                for(int x=0; x<3; x++)
                {
                    for(int z=0; z<3; z++)
                    {
                        if(GRID[i][l][x][z]==1)
                            A++;
                        else if(GRID[i][l][x][z])
                            B++;
                    }
                    if(A==3)
                    {
                        CHK[i][l]=1;
                        goto a;
                    }
                    else if(B==3)
                    {
                        CHK[i][l]=2;
                        goto a;
                    }
                    A=0,B=0;
                }
                for(int x=0; x<3; x++)
                {
                    for(int z=0; z<3; z++)
                    {
                        if(GRID[i][l][z][x]==1)
                            A++,CNT++;
                        else if(GRID[i][l][z][x])
                            B++,CNT++;
                    }
                    if(A==3)
                    {
                        CHK[i][l]=1;
                        goto a;
                    }
                    else if(B==3)
                    {
                        CHK[i][l]=2;
                        goto a;
                    }
                    A=0,B=0;
                }
                for(int x=0; x<3; x++)
                {
                    if(GRID[i][l][x][x]==1)
                        A++;
                    else if(GRID[i][l][x][x])
                        B++;
                }
                if(A==3)
                {
                    CHK[i][l]=1;
                    goto a;
                }
                else if(B==3)
                {
                    CHK[i][l]=2;
                    goto a;
                }
                A=0,B=0;
                for(int x=0; x<3; x++)
                {
                    if(GRID[i][l][2-x][x]==1)
                        A++;
                    else if(GRID[i][l][2-x][x])
                        B++;
                }
                if(A==3)
                {
                    CHK[i][l]=1;
                    goto a;
                }
                else if(B==3)
                {
                    CHK[i][l]=2;
                    goto a;
                }
                if(CNT==9)
                    CHK[i][l]=-1;
                else
                    CHK[i][l]=0;
a:
                ;
                A=0,B=0;
            }
    }
}
void RESET()
{
    for(int i=0; i<3; i++)
        for(int l=0; l<3; l++)
            for(int x=0; x<3; x++)
                for(int z=0; z<3; z++)
                    GRID[i][l][x][z]=GRID2[i][l][x][z];
}
int CHECKER()
{
    int A=0,B=0,CNT=0,C=0,D=0;
    for(int i=0; i<3; i++)
    {
        if(CHK[i][i]==1)
            A++;
        else if(CHK[i][i]==2)
            B++;
    }
    if(A==3)
        return 2;
    else if(B==3)
        return 0;
    A=0,B=0;
    for(int i=0; i<3; i++)
    {
        if(CHK[2-i][i]==1)
            A++;
        else if(CHK[2-i][i]==2)
            B++;
    }
    if(A==3)
        return 2;
    else if(B==3)
        return 0;
    A=0,B=0;
    for(int i=0; i<3; i++)
    {
        for(int l=0; l<3; l++)
        {
            if(CHK[i][l]==1)
                A++,CNT++,C++;
            else if(CHK[i][l]==2)
                B++,CNT++,D++;
            else if(CHK[i][l])
                CNT++;
        }
        if(A==3)
            return 2;
        else if(B==3)
            return 0;
        A=0,B=0;
    }
    for(int i=0; i<3; i++)
    {
        for(int l=0; l<3; l++)
        {
            if(CHK[l][i]==1)
                A++;
            else if(CHK[l][i]==2)
                B++;
        }
        if(A==3)
            return 2;
        else if(B==3)
            return 0;
        A=0,B=0;
    }
    if(CNT==9&&C>D)
        return 2;
    else if(CNT==9&&C<D)
        return 0;
    else if(CNT==9)
        return -1;
    return 1;
}
struct node
{
    double value=2.0;
    int plays=0;
    double wins=0.0;
    int8_t R,C;
    priority_queue<pair<double,node*>>CHILD;
};
node* ROOT;
pair<int8_t,int8_t>TEMP[82];
double SIMULATE(int8_t X,int8_t Y,bool CAN)
{
    int8_t F=0,DEP=2;
    int8_t LAST=CHECKER();
    if(LAST==1)
        while(1)
        {
            DEP++;
            if(CHK[X%3][Y%3])
            {
                for(int i=0; i<3; i++)
                {
                    for(int l=0; l<3; l++)
                    {
                        if(!CHK[i][l])
                            for(int x=0; x<3; x++)
                                for(int z=0; z<3; z++)
                                {
                                    if(!GRID[i][l][x][z])
                                        TEMP[F]= {i*3+x,l*3+z},F++;
                                }
                    }
                }
            }
            else
            {
                for(int i=0; i<3; i++)
                    for(int l=0; l<3; l++)
                    {
                        if(!GRID[X%3][Y%3][i][l])
                            TEMP[F]= {(X%3)*3+i,(Y%3)*3+l},F++;
                    }
            }
            int FF=rng()%F;
//cout<<TEMP.size()<<endl;
            int X=TEMP[FF].first/3,Y=TEMP[FF].second/3,X2=TEMP[FF].first%3,Y2=TEMP[FF].second%3;
            GRID[X][Y][X2][Y2]=(CAN?2:1);
            int8_t OLD=CHK[X][Y];
            UPDGRID(X,Y);
            if(OLD!=CHK[X][Y])
                LAST=CHECKER();
            if(LAST!=1)
                break;
            CAN=!CAN;
            F=0;
        }
    if(LAST==2)
        return 1.0/log(DEP);
    else if(!LAST)
        return 0;
    return -1.0/log(DEP);
}
inline double ENHANCE(int X,int Y,bool ENEMY=1,int AM=1,node* CUR=ROOT)
{
    if(CHECKER()!=1)
    {
        if(CHECKER()==2)
            return 1;
        else if(!CHECKER())
            return 0;
        return -1;
    }
    if(!(CUR->CHILD).size())
    {
        if(X==-1||CHK[X%3][Y%3])
        {
            for(int i=0; i<3; i++)
                for(int l=0; l<3; l++)
                    if(!CHK[i][l])
                        for(int x=0; x<3; x++)
                            for(int z=0; z<3; z++)
                                if(!GRID[i][l][x][z])
                                {
                                    node* yay=new node;
                                    (yay->R)=i*3+x,(yay->C)=l*3+z;
                                    (CUR->CHILD).push({ENEMY?(yay->value):-(yay->value),yay});
                                }
        }
        else
        {
            for(int x=0; x<3; x++)
                for(int z=0; z<3; z++)
                    if(!GRID[X%3][Y%3][x][z])
                    {
                        node*yay=new node;
                        (yay->R)=(X%3)*3+x,(yay->C)=(Y%3)*3+z;
                        (CUR->CHILD).push({(yay->value),yay});
                    }
        }
        int posX=(((CUR->CHILD).top().second)->R),posY=(((CUR->CHILD).top().second)->C);
        GRID[posX/3][posY/3][posX%3][posY%3]=(ENEMY?1:2);
        UPDGRID(posX/3,posY/3);
        double R=SIMULATE(posX,posY,ENEMY);
        if(R>0&&ENEMY)
            (CUR->wins)+=R;
        else if(R<0&&!ENEMY)
            (CUR->wins)-=R;
        (CUR->plays)++;
        (CUR->value)=(double)(CUR->wins)/(CUR->plays)+sqrt((double)2)*sqrt(log((double)AM)/(double)(CUR->plays));
        node* flol=((CUR->CHILD).top().second);
        (CUR->CHILD).pop();
        (CUR->CHILD).push({(CUR->value),flol});
        return R;
    }
    int posX=(((CUR->CHILD).top().second)->R),posY=(((CUR->CHILD).top().second)->C);
    GRID[posX/3][posY/3][posX%3][posY%3]=(ENEMY?1:2);
    UPDGRID(posX/3,posY/3);
    (CUR->plays)++;
    double R=ENHANCE(posX,posY,!ENEMY,(CUR->plays),(CUR->CHILD).top().second);
    if(R>0&&ENEMY)
        (CUR->wins)+=R;
    else if(R<0&&!ENEMY)
        (CUR->wins)-=R;
    (CUR->value)=(double)(CUR->wins)/(CUR->plays)+sqrt((double)2)*sqrt(log((double)AM)/(double)(CUR->plays));
    node* flol=((CUR->CHILD).top().second);
    (CUR->CHILD).pop();
    (CUR->CHILD).push({(CUR->value),flol});
    return R;
}
int32_t main()
{
//freopen("output.txt","w",stdout);
//freopen("sorting.in","r",stdin);
    cin.tie(0),iostream::sync_with_stdio(0);
    ROOT=new node;
    int FF=1,CLOCK=0;
    while(1)
    {
        int X=-1,Y=-1,L,R,n;
        string s,t;
//cin>>s>>t;
        /*if(s=="NW")
        X=0,Y=0;
        else if(s=="N")
        X=3,Y=0;
        else if(s=="NE")
        X=6,Y=0;
        else if(s=="C")
        X=3,Y=3;
        else if(s=="W")
        X=0,Y=3;
        else if(s=="E")
        X=6,Y=3;
        else if(s=="SW")
        X=0,Y=6;
        else if(s=="S")
        X=3,Y=6;
        else
        X=6,Y=6;
        if(t=="NW")
        X+=0,Y+=0;
        else if(t=="N")
        X+=1,Y+=0;
        else if(t=="NE")
        X+=2,Y+=0;
        else if(t=="C")
        X+=1,Y+=1;
        else if(t=="W")
        X+=0,Y+=1;
        else if(t=="E")
        X+=2,Y+=1;
        else if(t=="SW")
        X+=0,Y+=2;
        else if(t=="S")
        X+=1,Y+=2;
        else
        X+=2,Y+=2;*/
        swap(X,Y);
        cin>>X>>Y;
        if(X!=-1)
        {
            GRID[X/3][Y/3][X%3][Y%3]=2;
            if(ROOT->CHILD.size())
                while(!(((ROOT->CHILD.top().second)->R==X)&&((ROOT->CHILD.top().second)->C)==Y))
                {
                    (ROOT->CHILD).pop();
                    if(!(ROOT->CHILD.size()))
                        break;
                }
            if(!(ROOT->CHILD.size()))
                ROOT=new node;
            else
                ROOT=(ROOT->CHILD.top().second);
        }
        for(int i=0; i<3; i++)
            for(int l=0; l<3; l++)
                for(int x=0; x<3; x++)
                    for(int z=0; z<3; z++)
                        GRID2[i][l][x][z]=GRID[i][l][x][z];
        UPDGRID();
        while(clock()-CLOCK<99000*(FF?10:1))
        {
            ENHANCE(X,Y);
            RESET();
            UPDGRID();
        }
        FF=0;
        int FL=((ROOT->CHILD.top().second)->R),FR=((ROOT->CHILD.top().second)->C);
        cerr<<fixed<<setprecision(5)<<(ROOT->CHILD.top().first)<<endl;
        cout<<FL<<' '<<FR<<endl;
        ROOT=(ROOT->CHILD.top().second);
        GRID[FL/3][FR/3][FL%3][FR%3]=1;
        CLOCK=clock();
        /*for(int i=0;i<3;i++){
        for(int l=0;l<3;l++)
        cerr<<(int)CHK[i][l];
        cerr<<endl;
        }*/
        /*for(int i=0;i<3;i++){
        for(int l=0;l<3;l++){
        for(int x=0;x<3;x++){
        for(int z=0;z<3;z++){
        if(GRID[i][x][l][z]==1)
        cout<<'o';
        else if(GRID[i][x][l][z]==2)
        cout<<'x';
        else
        cout<<'.';
        //cout<<(int)GRID[i][x][l][z];
        }
        }
        cout<<endl;
        }
        }*/
    }
    return 0;
}
