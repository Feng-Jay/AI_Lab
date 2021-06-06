#include <iostream>
#include <cmath>

using namespace std;

const double LEARNING_RATE=0.9;

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
    Input(/* args */);
};

Input::Input(/* args */)
{
    input=0.0;
    output=0.0;
    weight[0]=0.5;
    weight[1]=0.5;
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
    double xita;
public:  
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
    xita=0.2;
    weight[0]=0.5; weight[1]=0.5;
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
}

class Out
{
private:
    double lable;
    double input[2];
    double xita;
public:
    double output;
    double error;
    void calres1(Hidden h1, Hidden h2);
    void calres2(Hidden h1, Hidden h2);
    void calerror();
    void Inres(double lab);
    void In(Hidden h1,Hidden h2);
    Out();
};
Out::Out()
{
    lable=0.0;input[0]=0.0;input[1]=0.0;
    xita=0.3;
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
    temp=h1.output*1.0*h1.weight[0]+h2.output*h2.weight[0];
    output=1.0/(1.0+exp(-1.0*temp));
}
void Out::calres2(Hidden h1, Hidden h2)
{
    double temp;
    temp=h1.output*1.0*h1.weight[1]+h2.output*h2.weight[1];
    output=1.0/(1.0+exp(-1.0*temp));
}
void Out::calerror()
{
    error=1.0*output*(1-output)*(lable-output);
}

double trainingset[19][5]={
    {20.55,0.6,0.09,5126,1237},
    {22.44,0.75,0.11,6217,1379},
    {25.37,0.85,0.11,7730,1385},
    {27.13,0.90,0.14,9145,1399},
    {29.45,1.05,0.20,10460,1663},
    {30.1,1.35,0.23,11387,1714},
    {30.96,1.45,0.23,12353,1834},
    {34.06,1.60,0.32,15750,4322},
    {36.42,1.70,0.32,18304,8132},
    {38.09,1.85,0.34,19836,8936},
    {39.13,2.15,0.36,21024,11099},
    {39.99,2.20,0.36,19490,11203},
    {41.93,2.25,0.38,20433,10524},
    {44.59,2.35,0.49,22598,11115},
    {47.30,2.50,0.56,25107,13320},
    {52.89,2.60,0.59,33442,16762},
    {55.73,2.70,0.59,36836,18673},
    {56.76,2.85,0.67,40548,20724},
    {59.17,2.95,0.69,42927,20803}
};
double expectset[2][3]={{60.63,3.1,0.79},{73.39,3.9635,0.9880}};
int main()
{
    cout<<"Start training..."<<endl;
    Input in1,in2,in3;
    Hidden h1,h2;
    Out out1,out2;
    // cout<<h1.weight[0]<<endl;
    for(int i=0;i<19;i++){
        in1.In(trainingset[i][0]);
        in2.In(trainingset[i][1]);
        in3.In(trainingset[i][2]);
        out1.Inres(trainingset[i][3]);
        out2.Inres(trainingset[i][4]);

        in1.Calsum(); in2.Calsum(); in3.Calsum();

        h1.In(in1.output,in2.output,in3.output);
        h2.In(in1.output,in2.output,in3.output);
        h1.Calres1(in1,in2,in3);
        h2.Calres2(in1,in2,in3);

        out1.In(h1,h2); out2.In(h1,h2);
        out1.calres1(h1,h2);
        out2.calres2(h1,h2);

        //start bp
        out1.calerror();
        out2.calerror();
        h1.Calerror(out1.error,out2.error);
        h2.Calerror(out1.error,out2.error);

        h1.Itera(out1.error,out2.error);
        h2.Itera(out1.error,out2.error);
        in1.Itera(h1.error,h2.error);
        in2.Itera(h1.error,h2.error);
        in3.Itera(h1.error,h2.error);
    }
    cout<<"Traning over, begin expect..."<<endl;
    for(int i=0;i<2;i++){
        in1.In(expectset[i][0]);
        in2.In(expectset[i][1]);
        in3.In(expectset[i][3]);
        in1.Calsum(); in2.Calsum(); in3.Calsum();

        h1.In(in1.output,in2.output,in3.output);
        h2.In(in1.output,in2.output,in3.output);
        h1.Calres1(in1,in2,in3);
        h2.Calres2(in1,in2,in3);

        out1.In(h1,h2); out2.In(h1,h2);
        out1.calres1(h1,h2);
        out2.calres2(h1,h2);
        cout<<2009+i<<"年的公路客运量为"<<out1.output<<" 货运量为"<<out2.output<<endl;
    }
    return 0;
}