#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <math.h>
#include <iomanip>
using namespace std;

const double LEARNING_RATE=0.9;

typedef struct Inputlayer_Node{
    double data;//输入特征值
    double weight[2];
}Inputlayer_Node; 

typedef struct Hiddenlayer_Node{
    double weight[2];//权重
    double differnces;//计算求和时的偏差值
    double data;//全加器结果
    double error;//bp误差
}HiddenLayer_Node;

void rand_Input(Inputlayer_Node temp)
{
    return ;
}

void rand_Hidden(HiddenLayer_Node temp)
{
    return ;
}

double Hidden_Layer_Compute(Inputlayer_Node node1, Inputlayer_Node node2, Inputlayer_Node node3)
{
    return ;

}

double Output_Layer_Compute()
{
    return 0.0;
}

double bp()
{
    return 0.0;
}

void update_hidden()
{
    return ;
}

void update_Input()
{
    return ;
}


int main()
{

}