# include <bits/stdc++.h>
using namespace std;

int main()
	{
	int i=0,j,k,l,wi=-1,we=-1,maxl,maxi,cnt,temp;
	string inp;
	cin>>inp;
	while(inp[i]!='\0')
		{
		maxl=0;
		maxi=we+1;
		for (j=we;j>wi;j--)
			{
			if (inp[i]==inp[j])
				{
				k=i;
				l=j;
				cnt=0;
				while(inp[k++]==inp[l++])
					{
					cnt++;
					}
				if (maxl<cnt)
					{
					maxl=cnt;
					maxi=j;
					}
				}
			}
		temp=i;
		i+=maxl+1;
		cout<<endl;
		for(int loop=temp;loop<i;loop++)
			cout<<inp[loop];			
		printf("\t<%d %d %d> \n",we-maxi+1,maxl,inp[i-1]-96);
		we+=maxl+1;
		if(we-wi>=8)
			wi=we-8;
		}
	return 0;
	}
