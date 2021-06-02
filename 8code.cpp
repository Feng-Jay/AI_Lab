#include <iostream>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

int ini[3][3]={2,3,5,4,0,6,7,8,1};
int tar[3][3]={1,2,3,8,0,4,7,6,5};
int dx[4]={0,0,-1,1}; int dy[4]={1,-1,0,0};

struct Martix{
    int martix[3][3];
};

int judge_valid(Martix mylist)
{
    int countt=0;
    int array[9];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            array[i*3+j]=mylist.martix[i][j];
        }
    }
    for(int i=0;i<9;i++){
        for(int j=i+1;j<9;j++){
            if(array[i]>array[j])
            countt++;
        }
    }
    if(countt%2) return 1;
    else return 0;
}

void init(Martix &mylist)
{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
        mylist.martix[i][j]=ini[i][j];
    }
}

tuple<int,int> find0(int mylist[3][3])
{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(mylist[i][j]==0)
            return make_tuple(i,j);
        }
    }
    return make_tuple(-2,-2);
}

int test(int mylist[3][3],int tar[3][3])
{
    int outcome=1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(mylist[i][j]!=tar[i][j]){
                outcome=0;
                return outcome;
            }
        }
    }
    return outcome;
}

int runbefore(Martix martix1,vector<Martix> before)
{
    for(int i=0;i<before.size();i++){
        int outcome=1;
        for(int m=0;m<3;m++){
            for(int n=0;n<3;n++){
                if(martix1.martix[m][n]!=before[i].martix[m][n]){
                    outcome=0;
                }
            }
        }
        if(outcome) return 1;
    }
    return 0;
}
void printMartix(Martix martix1)
{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
        cout<<martix1.martix[i][j]<<" ";
        cout<<endl;
    }
}

int BFS(Martix &mylist)
{
    queue<Martix> q;
    vector<Martix> before;
    q.push(mylist);
    before.push_back(mylist);
    while(!q.empty()){
        Martix temp=q.front();
        q.pop();
        // cout<<"1"<<endl;
        // printMartix(temp);
        if(test(temp.martix,tar)){
            cout<<"Task done"<<endl;
            cout<<"outcome:\n";
            printMartix(temp);
            return 1;
        }

        tuple<int,int>locate=find0(temp.martix);
        for(int i=0;i<4;i++){
            int x=get<0>(locate)+dx[i];
            int y=get<1>(locate)+dy[i];
            if(x>=0&&x<3&&y>=0&&y<3){
                Martix newone;
                for(int m=0;m<3;m++){
                    for(int n=0;n<3;n++){
                        newone.martix[m][n]=temp.martix[m][n];
                    }
                }
                swap(newone.martix[x][y],newone.martix[get<0>(locate)][get<1>(locate)]);
                if(!runbefore(newone,before)){
                    q.push(newone);
                    before.push_back(newone);
                    cout<<"push martix:\n";
                    printMartix(newone);
                }
            }
        }
    }
    return 1;
}
Martix mylist;
int main()
{
    init(mylist);
    if(judge_valid(mylist))
    BFS(mylist);
    else cout<<"The input cann't solved by BFS"<<endl;
    return 0;
}