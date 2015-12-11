# include<bits/stdc++.h>
using namespace std;

int fin=7;

long long power(int pt,long long e)
	{
	long long x=pt;
	for (long long i=0;i<e-1;i++)
		{
		x=(x*pt)%fin;
		}	
	cout<<endl<<x;
	}

int main()
	{
	// power(6,3);
	int a=(106*106*106)%187;
	cout<<a;
	}