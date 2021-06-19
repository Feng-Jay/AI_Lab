#include <iostream>
#include <queue>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <time.h>
using namespace std;

int ini[3][3]={1,2,3,8,0,6,4,7,5};
int tar[3][3]={1,2,3,8,0,4,7,6,5};
int dx[4]={0,0,-1,1}; int dy[4]={1,-1,0,0};

struct Martix{
    int martix[3][3];
    int f;
    int g;
    bool operator<(const Martix& other)const {
        return f>other.f;
    }
};

tuple<int,int> search(int val)
{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(tar[i][j]==val)
            return make_tuple(i,j);
        }
    }
    return make_tuple(-2,-2);
}

void cal_hf(Martix &mylist)
{
    tuple<int,int> temp;
    int x,y;
    int outcome=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            temp=search(mylist.martix[i][j]);
            x=get<0>(temp);y=get<1>(temp);
            outcome+= sqrt(abs(x*x-i*i)+abs(y*y-j*j));
        }
    }
    mylist.f=mylist.g+outcome;
}

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

int AStar(Martix &mylist)
{
    priority_queue<Martix> open_list;
    vector<Martix> close_list;
    open_list.push(mylist);
    while(!open_list.empty()){
        Martix temp=open_list.top();
        open_list.pop();
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
                if(!runbefore(newone,close_list)){
                    newone.g+=1;
                    cal_hf(newone);
                    open_list.push(newone);
                    close_list.push_back(newone);
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
    clock_t begin,end;
    begin=clock();
    init(mylist);
    if(judge_valid(mylist))
    AStar(mylist);
    else cout<<"The input cann't solved by Astar"<<endl;
    end=clock();
    cout<<"A* time = "<<-1*double(begin-end)/CLOCKS_PER_SEC<<"s"<<endl;
    return 0;
}