#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>

const double LEARNING_RATE=0.035;

class Input
{
private:
    double input;
public:  
    double output;
    double weight[2];
    void Calsum();
    void Itera(double nexterror1,double nexterror2);
    void In(double in);
    void wei(double x,double y);
    Input(/* args */);
};

Input::Input(/* args */)
{
    input=0.0;
    output=0.0;
    srand(1);
    weight[0]=0.5+rand()%1;
    weight[1]=0.3+rand()%1;
}
void Input::wei(double x, double y)
{
    weight[0]=x;
    weight[1]=y;
}
void Input::In(double in)
{
    input=in;
}
void Input::Calsum()
{
    output=input;
}

void Input::Itera(double nexterror1,double nexterror2)
{
        weight[0]+=LEARNING_RATE*1.0*nexterror1*output;
        weight[1]+=LEARNING_RATE*1.0*nexterror2*output;
}

class Hidden
{
private:
    double input[3];
public:  
    double xita;
    double output;
    double error;
    double weight[2];
    void Calres1(Input a, Input b, Input c);
    void Calres2(Input a, Input b, Input c);
    void Calerror(double nexterror,double nexterror2);
    void Itera(double nexterror, double nexterror2);
    void In(double in1,double in2,double in3); 
    Hidden();  
};
Hidden::Hidden()
{
    output=0.0;
    error=0.0;
    xita=0.0;
    srand(2);
    weight[0]=0.5+rand()%1;
    weight[1]=0.3+rand()%1;
}
void Hidden::In(double in1,double in2,double in3)
{
    input[0]=in1; input[1]=in2;input[2]=in3;
}
void Hidden::Calres1(Input a, Input b, Input c)
{
    double temp;
    temp=a.output*a.weight[0]+b.output*b.weight[0]+c.output*c.weight[0]+xita;
    output=1.0/(1.0+exp(-1.0*temp));
}
void Hidden::Calres2(Input a, Input b, Input c)
{
    double temp;
    temp=a.output*a.weight[1]+b.output*b.weight[1]+c.output*c.weight[1]+xita;
    output=1.0/(1.0+exp(-1.0*temp));
}
void Hidden::Calerror(double nexterror1,double nexterror2)
{
    double temp=output*1.0*(1.0-output)*(nexterror1*weight[0]+nexterror2*weight[1]);
    error=temp;
}
void Hidden::Itera(double nexterror1, double nexterror2)
{
    weight[0]+=LEARNING_RATE*1.0*nexterror1*output;
    weight[1]+=LEARNING_RATE*1.0*nexterror2*output;
    xita+=LEARNING_RATE*1.0*error;
}

class Out
{
private:
    double lable;
    double input[2];
public:
    double xita;
    double output;
    double error;
    void calres1(Hidden h1, Hidden h2);
    void calres2(Hidden h1, Hidden h2);
    void calerror();
    void Inres(double lab);
    void In(Hidden h1,Hidden h2);
    void Itera();
    Out();
};
Out::Out()
{
    lable=0.0;input[0]=0.0;input[1]=0.0;
    xita=0.03;
    output=0.0;
    error=0.0;
}
void Out::Inres(double lab)
{
    lable=lab;
}
void Out::In(Hidden h1, Hidden h2)
{
    input[0]=h1.output;
    input[1]=h2.output;
}

void Out::calres1(Hidden h1, Hidden h2)
{
    double temp;
    temp=h1.output*1.0*h1.weight[0]+1.0*h2.output*h2.weight[0];
    output=1.0/(1.0+exp(-1.0*temp));
}
void Out::calres2(Hidden h1, Hidden h2)
{
    double temp;
    temp=h1.output*1.0*h1.weight[1]+1.0*h2.output*h2.weight[1];
    output=1.0/(1.0+exp(-1.0*temp));
}
void Out::calerror()
{
    error=1.0*output*(1-output)*(lable-output);
}
void Out::Itera()
{
    xita+=LEARNING_RATE*error;
}
