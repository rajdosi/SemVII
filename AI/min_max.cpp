# include<bits/stdc++.h>
using namespace std;

struct tree 
	{
		int i_p, p_c;
		int val;
		struct tree **child,*parent;
	}*head;

int array[9]={0};
queue <struct tree *> Q;

void disp_b(int *arr)
	{
	cout<<endl;
	int i,j;
		for(i=1;i<=9;i++)
			{
			if (arr[i-1]==1)
				cout<<"X  ";
			else if (arr[i-1]==-1) 
				cout<<"O  ";
			else
				cout<<"   ";
			if(i%3==0)
				cout<<"\n";
			}
	}

int checkwin(int *tr,int chance)
	{
		int win[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
		int i,j,count,m=3;
		for(i=0;i<8;i++)
			{
			count=0;
			j=0;
			m=3;
			while(m--)
				{
				if(tr[win[i][j]]==chance)
					count++;	
				j++;
				}
			if(count==3)
				{
				return 1;
				}
			}
		return 0;
	}

void bfs_print(struct tree *temp)
	{
	int i;
	if (temp==NULL)
		{
		cout<<"   ";
		return;
		}
	for (i=0;i<temp->p_c;i++)
		{
		Q.push(temp->child[i]);
		cout<<temp->child[i]->val<<" ";
		}
	cout<<endl;
	struct tree *t2=Q.front();
	Q.pop();
	bfs_print(t2);
	}

int min_max(struct tree *temp,int *tr,int turn)
	{
	if (checkwin(tr,turn*-1))
		{
		if (turn*-1==-1)
			{
			//cout<<"I won"<<endl;
			temp->val=temp->val+1;
			}
		else if (turn*-1==1)
			{
			//cout<<"You won"<<endl;
			temp->val=temp->val-1;
			}	
		//cout<<"\t"<<temp->val<<endl;
		return temp->val;
		}

	temp->child= new struct tree*[temp->p_c];
	int f=0;
	for(int i=0;i<9;i++)	
	 	{
	 	if (tr[i]==0)
	 		{
	 		struct tree *temp2=new struct tree;	
	 		temp2->parent=temp;
	 		temp2->p_c=temp->p_c-1;
	 		temp2->val=0;
	 		temp2->i_p=i;
	 		tr[temp2->i_p]=turn;
			temp->child[f]=temp2;
			int r= min_max(temp2,tr,turn*-1);
			tr[temp2->i_p]=0;
	 		temp->val+=r;	
			f++;
			}
		}
	//cout<<"\t"<<temp->val<<endl;
	return temp->val;
	}

void play_game(struct tree *temp,int chance,int *tr)
	{
	int pos;
	if (chance==1)
		{
		cout<<"Please enter a valid position [1 to 9]:";
		cin>>pos;
		tr[pos]=1;
		for(int i=0;i<temp->p_c;i++)
			{
			if(temp->child[i]->i_p==pos)
				{
				temp=temp->child[i];		
				break;
				}
			}
		disp_b(tr);
		play_game(temp,chance*-1,tr);
		}
	else
		{
		long int max=-999999;
		for (int i=0;i<temp->i_p;i++)
			{
			if(temp->child[i]->val>max)
				{
				max=temp->child[i]->val;
				pos=i;
				cout<<endl<<max<<" "<<i;
				}
			}
		temp=temp->child[pos];
		tr[temp->i_p]=-1;
		disp_b(tr);
		play_game(temp,chance*-1,tr);
		}
	}

int main()
	{
	head= new struct tree;
	struct tree *usr= new struct tree;
	head->parent=NULL;
	head->p_c=9;
	head->val=0;
	int choice,turn,r;
	cout<<"Who goes first?\n1)User('X',1)\n2)Me('O',-1)\n";
	cin>>choice;
	switch(choice)
		{
		case 1:
			{
				turn=1;
				usr->parent=head;
				int pos;
				usr->p_c=8;
				cout<<"Please enter a valid position [1 to 9]:";
				cin>>pos;
				usr->i_p=pos;
				array[pos-1]=1;
				min_max(usr,array,turn*-1);
				//cout<<r<<endl;
				turn=turn*-1;
				break;
			}
		case 2:
			{
				turn=-1;
				usr=head;
				usr->p_c=head->p_c;
				usr->parent=NULL;
				usr->val=0;
				r=min_max(usr,array,turn);
				//cout<<r<<endl;
				break;
			}
		default:
			{
			cout<<"No such choice available || Please try again!!"<<endl;
			}
		}
	//bfs_print(usr);
	play_game(usr,turn,array);
	return 0;	
	}