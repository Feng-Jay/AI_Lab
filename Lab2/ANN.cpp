#include <iostream>
#include <cmath>

using namespace std;

const double LEARNING_RATE=0.9;

class Input
{
private:
    double input;
    double Calsum();
    double Itera(double nexterror);
public:  
    double output;
    double weight[2];
    Input(/* args */);
    Input(double in);
};

Input::Input(/* args */)
{
    input=0.0;
    output=0.0;
    weight[0]=0.5;
    weight[1]=0.5;
}
Input::Input(double in)
{
    input=in;
}
double Input::Calsum()
{
    output=input;
}

double Input::Itera(double nexterror)
{
    for(int i=0;i<3;i++){
        weight[i]+=LEARNING_RATE*1.0*nexterror*output;
    }
}

class Hidden
{
private:
    double input[3];
    double xita;
    double Calres1(Input a, Input b, Input c);
    double Calres2(Input a, Input b, Input c);
    double Calerror(double nexterror);
    double Itera(double nexterror);
public:  
    double output;
    double error;
    double weight;
    Hidden(double in1,double in2,double in3);   
};
Hidden::Hidden(double in1,double in2,double in3)
{
    input[0]=in1; input[1]=in2;input[2]=in3;
    output=0.0;
    error=0.0;
    xita=0.2;
    weight=0.5;
}
double Hidden::Calres1(Input a, Input b, Input c)
{
    double temp;
    temp=a.output*a.weight[0]+b.output*b.weight[0]+c.output*c.weight[0]+xita;
    output=1.0/(1.0+exp(-1.0*temp));
}
double Hidden::Calres2(Input a, Input b, Input c)
{
    double temp;
    temp=a.output*a.weight[1]+b.output*b.weight[1]+c.output*c.weight[1]+xita;
    output=1.0/(1.0+exp(-1.0*temp));
}
double Hidden::Calerror(double nexterror)
{
    double temp=output*1.0*(1.0-output)*nexterror*weight;
}
double Hidden::Itera(double nexterror)
{
    weight+=LEARNING_RATE*1.0*nexterror*output;
}

class Out
{
private:
    double lable;
    double input[2];
    double xita;
    double calres(Hidden h1, Hidden h2);
    double calerror();
public:
    double output;
    double error;
    Out();
    Out(double lab);
    Out(Hidden h1,Hidden h2);
};
Out::Out()
{
    lable=0.0;input[0]=0.0;input[1]=0.0;
    xita=0.3;
    output=0.0;
    error=0.0;
}
Out::Out(double lab)
{
    lable=lab;
}
Out::Out(Hidden h1, Hidden h2)
{
    input[0]=h1.output;
    input[1]=h2.output;
}

double Out::calres(Hidden h1, Hidden h2)
{
    double temp;
    temp=h1.output*h1.weight+h2.output*h2.weight;
    output=1.0/(1.0+exp(-1.0*temp));
}
double Out::calerror()
{
    error=output*(1-output)*(lable-output);
}

int main()
{
    return 0;
}