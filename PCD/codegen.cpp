# include<bits/stdc++.h>
using namespace std;

struct tree
	{
	char node;
	tree *left,*right;
	tree *parent;
	}*head;

queue <struct tree *> Q;

void mknode(string s,int index)
	{
		
	//Q.push();
	return;
	}


int main()
	{
	string temp;
	char syn[100];
	struct tree *var;
	int index;
	for (int i=0;;i++)
		{
		cin>>syn[i];
		temp[i]=syn[i];
		if (syn[i]=='1')
			{
			syn[i]=='\0';
			temp[i]=syn[i];
			break;
			}
		}
	cout<<temp<<endl;
	for (int i=0;i<temp.length();i++)
		{
		cout<<syn[i]<<"\t";	
		}
	// int len=Q.size();	
	// for(int i=0;i<len;i++)
	// 	{
	// 	var=Q.front();
	// 	cout<<var->node<<"\t";
	// 	Q.pop();
	// 	}
	return 0;
	}