# include<bits/stdc++.h>
using namespace std;

int main()
	{
	int i=0;
	string inp,temp;
	map <string,int> dict;
	cin>>inp;
	int count=0,a;
	char b;
	//inp=inp+'0';
	while (inp[i]!='\0')
		{
		temp="\0";
		temp=temp+inp[i];
		if (dict.find(temp)==dict.end())
			{
			a=0;
			b=inp[i];
			}
		i++;
		while (dict.find(temp)!=dict.end())
			{
			a=dict[temp];
			temp=temp+inp[i];
			b=inp[i];
			i++;
			}
		count++;
		dict[temp]=count;	
		cout<<"< "<<a<<","<<b<<" >"<<endl;
		//cout<<temp<<" "<<count<<endl; 	
		}
	cout<<endl;
	for (map <string,int>::iterator it=dict.begin();it!=dict.end();it++)
		cout<<it->first<<"\t"<<it->second<<endl;
	return 0;
	}
