#include<iostream>

using namespace std;

main()
{
    int n,i,j,temp;
    cout<<"Enter N:";
    cin>>n;
    int a[n][n],t[n];
    for(i=0;i<n;i++)
        for(j=0;j<n;j++) a[i][j]=0;
    temp=n%6;
    int k=0;
    if(temp!=2 || temp!=3)
    {
        for(i=1;i<n;i=i+2)
            a[k++][i]=1;
        for(i=0;i<n;i=i+2)
            a[k++][i]=1;

    }
    else
    {
        for(i=1;i<n;i=i+2)
            t[k++]=i;
        for(i=0;i<n;i=i+2)
            t[k++]=i;
        if(temp==2)
        {
            t[n/2]=3;
            t[n/2+1]=1;
            for(i=n/2+2;i<n-1;i++) t[i]=t[i+1];
            t[n-1]=5;
            for(i=0;i<n;i++)
                a[i][t[i]]=1;
        }
        else
        {
            for(i=0;i<n/2-1;i++) t[i]=t[i+1];
            t[n/2-1]=2;
            for(i=n/2;i<n-2;i++) t[i]=t[i+2];
            t[n-2]=1;
            t[n-1]=3;
             for(i=0;i<n;i++)
                a[i][t[i]]=1;
        }
    }
    for(i=0;i<n;i++)
    {
        cout<<endl;
        for(j=0;j<n;j++) cout<<a[i][j]<<" ";
    }
    return 0;
}
