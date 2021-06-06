#include <iostream>
#include <cmath>
#include "ANN.h"


using namespace std;

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
double expectset[2][3]={
    {60.63, 3.1, 0.79},
    {73.39, 3.9635, 0.9880}
};
void standize()
{/*min-max*/
    double mm[5]={20.55,0.6,0.09,5126,1237};
    double mmm[5];
    for(int m=0;m<5;m++){
        mmm[m]=trainingset[18][m]-mm[m];
    }
    for(int m=0;m<4;m++){
        for(int i=0;i<19;i++){
            trainingset[i][m]=(1.0*(trainingset[i][m]-mm[m]))/(1.0*(47000-mm[m]));
        }
    }
    for(int i=0;i<19;i++){
            trainingset[i][4]=(1.0*(trainingset[i][4]-mm[4]))/(1.0*(35000-mm[4]));
        }
    for(int i=0;i<19;i++){
        cout<<i<<" ";
        for(int j=0;j<5;j++)
        {cout<<trainingset[i][j]<<" ";}
        cout<<endl;
    }
     for(int m=0;m<3;m++){
        for(int i=0;i<2;i++){
            expectset[i][m]=(expectset[i][m]-mm[m])/mmm[m];
        }
    }
     for(int i=0;i<2;i++){
        cout<<i<<" ";
        for(int j=0;j<3;j++)
        {cout<<expectset[i][j]<<" ";}
        cout<<endl;
    }
}
int main()
{
    Input in1,in2,in3;
    Hidden h1,h2;
    Out out1,out2;
    standize();
    // cout<<h1.weight[0]<<endl;
    srand(1);
    in1.wei(0.5+rand()%1,0.4+rand()%1);
    in2.wei(0.4+rand()%1,0.2+rand()%1);
    in3.wei(0.3+rand()%1,0.5+rand()%1);
    cout<<"Start training..."<<endl;
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

        out1.Itera(); out2.Itera();
        h1.Itera(out1.error,out2.error);
        h2.Itera(out1.error,out2.error);
        in1.Itera(h1.error,h2.error);
        in2.Itera(h1.error,h2.error);
        in3.Itera(h1.error,h2.error);
    }
    // debug
    cout<<in1.weight[0]<<" "<<in1.weight[1]<<endl;
    cout<<in2.weight[0]<<" "<<in2.weight[1]<<endl;
    cout<<in3.weight[0]<<" "<<in3.weight[1]<<endl;
    cout<<h1.weight[0]<<" "<<h1.weight[1]<<" "<<h1.xita<<endl;
    cout<<h2.weight[0]<<" "<<h2.weight[1]<<" "<<h2.xita<<endl;
    cout<<out1.xita<<endl;
    cout<<out2.xita<<endl;
    cout<<"Traning over, begin expect..."<<endl;
    for(int i=0;i<2;i++){
        in1.In(expectset[i][0]);
        in2.In(expectset[i][1]);
        in3.In(expectset[i][2]);
        in1.Calsum(); in2.Calsum(); in3.Calsum();
        h1.In(in1.output,in2.output,in3.output);
        h2.In(in1.output,in2.output,in3.output);
        h1.Calres1(in1,in2,in3);
        h2.Calres2(in1,in2,in3);

        out1.In(h1,h2); out2.In(h1,h2);
        out1.calres1(h1,h2);
        out2.calres2(h1,h2);

    //    double temp=in1.output*in1.weight[0]+in2.output*in2.weight[0]+in3.output*in3.weight[0]+h1.xita;
    //    double temp1=in1.output*in1.weight[1]+in2.output*in2.weight[1]+in3.output*in3.weight[1]+h2.xita;
    //    double outcome=temp*h1.weight[0]+temp1*h2.weight[0]+out1.xita;
    //    double outcome1=temp*h1.weight[1]+temp1*h2.weight[1]+out2.xita;
        double outcome,outcome1;
        outcome=out1.output; outcome1=out2.output;
        cout<<outcome<<" "<<outcome1<<endl;
        outcome=out1.output*(47000-5126)+5126;
        outcome1=out2.output*(35000-1237)+1237;
        // outcome1=-1*log((1.0/outcome1)-1);
        // *(20803-1237)+1237;
        cout<<2009+i<<"年的公路客运量为"<<outcome<<" 货运量为"<<outcome1<<endl;
    }
    return 0;
}