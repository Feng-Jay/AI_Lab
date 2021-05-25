#include <iostream>
#include <queue>

using namespace std;

int martix[3][3];
int outcome[3][3]={{1,2,3},{8,0,4},{7,6,5}};
int dx[4]={0,0,-1,1};
int dy[4]={1,-1,0,0};
struct Node{
    int x;
    int y;
};
void Init_Martix()
{
    cout<<"Please input martix, use 0 replace empty."<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
        cin>>martix[i][j];
    }
}

void Print_Martix()
{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
        cout<<martix[i][j]<<" ";
        cout<<endl;
    }
}

int Ok()
{
    int ok=1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(martix[i][j]!=outcome[i][j]){
                ok=0;
                return ok;
            }
        }
    }
    return ok;
}

int BFS()
{
    queue<Node> q;
    
}

int main()
{
    Init_Martix();

    return 0;
}