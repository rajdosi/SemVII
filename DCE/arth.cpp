#include<bits/stdc++.h>

using namespace std;

struct sym
{
    char ch;
    float prob;
    float cf;
};

string fun(float a)
{
    string ans;
    for(int i=0;i<6;i++){
        a *= 2;
        if(a > 1){
            ans = ans + '1';
            a--;
        }
        else
            ans = ans + '0';
    }
    return ans;
}

int main()
{
    int n;
    cout<<"enter the bnumber of symbols"<<endl;
    cin>>n;
    sym symbol[n];
    float scale[n+1];
    string app;
    for(int i=0;i<n;i++)
    {
        cin>>symbol[i].ch>>symbol[i].prob;
        if(i != 0){
            symbol[i].cf = symbol[i-1].cf + symbol[i].prob;
            scale[i] = symbol[i-1].cf;
        }
        else{
            scale[i] = 0;
            symbol[i].cf = symbol[i].prob;
        }
    }
    scale[n] = 1;
    cout<<"Enter the string..."<<endl;
    string str;
    cin>>str;
    float lower,upper;
    for(int i=0;i<str.length();i++){
        for(int k=0;k<n;k++){
            if(symbol[k].ch == str[i]){
                cout<<"Element is :- "<<str[i]<<endl;
                lower = scale[k];
                upper = scale[k+1];
                while(true){
                    if(lower<float(0.5) && upper<float(0.5)){
                        lower = 2*lower;
                        upper = 2*upper;
                        app = app + '0';
                    }
                    else if(lower>=float(0.5) && upper>=float(0.5)){
                        lower = 2*lower - 1;
                        upper = 2*upper - 1;
                        app = app + '1';
                    }
                    else
                        break;
                }
                break;
            }
        }
        for(int i=0;i<n+1;i++){
            cout<<"Scale "<<i<<" = "<<scale[i]<<endl;
        }
        cout<<endl; 
        for(int i=1;i<n;i++){
            scale[i] = lower+(((scale[i] - scale[0])*(upper-lower))/(scale[n]-scale[0]));
        }
        scale[0] = lower;
        scale[n] = upper;    
        
    }    
    for(int i=0;i<n+1;i++){
        cout<<"Scale "<<i<<" = "<<scale[i]<<endl;
    }
    cout<<endl;
    cout<<"Append string :- "<<app<<endl;
    string h = fun(scale[0]);
    cout<<"Binary of generated tag :- "<<h<<endl;
    cout<<"Final tag :- "<<endl<<"0."<<app<<h<<endl; 
    return 0;
}
