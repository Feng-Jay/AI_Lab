#include <iostream>
#include <queue>

using namespace std;

struct Node{
    int x;
    int y;
};

int Martix[3][3]={2,3,5,4,0,6,7,8,1};
int End[3][3]={1,2,3,8,0,4,7,6,5};
int moved[4][2]={-1,0,1,0,0,1,0,-1};
int visited[3][3]={0,0,0,0,0,0,0,0,0};

void print_martix()
{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
        cout<<Martix[i][j]<<" ";
        cout<<endl;
    }
}

bool judge_end()
{
    bool res=true;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(Martix[i][j]!=End[i][j])
            res=false;
        }
    }
    return res;
}
bool is_valid(int x, int y)
{
    if(x>=0&&y>=0&&x<=2&&y<=2)
    return true;
    else 
    return false;
}
bool BFS()
{
    Node init;
    init.x=1;init.y=1;
    Node front;
    Node temp;
    queue<Node> Q;
    Q.push(init);
    visited[init.x][init.y]=1;
    while(!Q.empty()){
        front=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            temp.x=init.x-moved[i][0];
            temp.y=init.y-moved[i][1];
            if(is_valid(temp.x,temp.y)){
                if(visited[temp.x][temp.y]!=1){
                    Q.push(temp);
                    swap(Martix[temp.x][temp.y],Martix[front.x][front.y]);
                    front=temp;
                    visited[temp.x][temp.y]=1;
                    if(judge_end())
                    return true;
                }
            }
            print_martix();
            cout<<""<<endl;
        }
    }
    return false;
}

int main()
{
    cout<<"init martix:"<<endl;
    print_martix();   
    BFS();
    cout<<"ans:"<<endl;
    print_martix();
}