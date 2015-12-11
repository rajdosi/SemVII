# include<bits/stdc++.h>
using namespace std;

int main()
	{
	int i=0,count=0;
	string inp,temp;
	int code[10];
	map <string,int> dict;
	cin>>inp;
	//inp=inp+'0';
	//Normal Dictionary
	while (inp[i]!='\0')
		{
		temp=inp[i];
		i++;
		while (dict.find(temp)==dict.end())
			{
			count++;			
			dict[temp]=count;
			//cout<<temp<<"\t"<<count<<"\tlength:"<<temp.length()<<endl;
			}		
		}		
	i=0;
	int c,it=0;	
	//2nd traversal
	while (inp[i]!='\0')
		{
		temp="\0";
		temp=temp+inp[i];
		i++;
		while (dict.find(temp)!=dict.end())
			{
			code[it]=dict[temp];			
			temp=temp+inp[i];
			i++;
			}
		i--;
		it++;
		count++;
		dict[temp]=count;
		//cout<<temp<<"\t"<<count<<"\tlength:"<<temp.length()<<endl;		
		}
	for(i=0;i<it;i++)	
		cout<<code[i]<<" ";
	cout<<endl<<endl;
	for (map <string,int>::iterator it=dict.begin();it!=dict.end();it++)
	 	cout<<it->first<<"\t"<<it->second<<"\n";

	return 0;
	}
