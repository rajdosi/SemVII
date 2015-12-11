#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<math.h>
#include<fstream>
#include<stdlib.h>
using namespace std;
string outp;
struct node
{
    char sym;
    int count;
    int weight;
	node *parent;
    node *left;
    node *right;
}*pnyt,*ptr_next;

struct symb
{
	char symbol;
    vector<int> fcode;
}arr[26];

vector<int> ans;
int next_wt;
node *max_ptr[52];
bool flag=0;

void d2b(int num, int base);
void adhuff(char next, node *root);
void search(char next, node *nod);
void increment(node *w);
void trav(char c, node *nod);
int main()
{
    int no,i,j;
	for(j=0;j<20;j++)
    {
    	d2b(j,2);

		for(i=0;i<5-ans.size();i++)
			arr[j].fcode.push_back(0);

		for(i=0;i<ans.size();i++)
			arr[j].fcode.push_back(ans[i]);

	    ans.clear();
    }

    for(j=20;j<26;j++)
    {
    	d2b(j-10,2);

		for(i=0;i<4-ans.size();i++)
			arr[j].fcode.push_back(0);

		for(i=0;i<ans.size();i++)
			arr[j].fcode.push_back(ans[i]);

	    ans.clear();
    }

	node *root;
	root=new node;
	root->sym='$';// $ = NYT
	root->count=0;
	root->weight=51;
	next_wt=50;
	root->parent=NULL;
	root->left=NULL;
	root->right=NULL;
	pnyt=root;
	ptr_next=NULL;

	for(i=0;i<=51;i++)
		max_ptr[i]=NULL;

	max_ptr[51]=root;

    char input[9]="aardvaka";

    for(i=0;input[i]!=NULL;i++)
    {
    	ptr_next=NULL;
    	ans.clear();
    	adhuff(input[i],root);
   }

//    cout<<"output "<<outp;
}

void d2b(int num, int base)
{
	if(num>0)
	{
		d2b(num/base,base);
		ans.push_back(num%base);
	}
}

void adhuff(char next, node *root)
{
	search(next,root);
	node *node_ret;
	node_ret=ptr_next;
	if(node_ret!=NULL)
	{
		cout<<next<<": ";
		flag=0;
		trav(next,root);
		cout<<endl;
		increment(node_ret);
	}
	else
    {
		flag=0;
		cout<<"nyt: ";
		trav('$',root);
		cout<<endl;

		node *nr,*nl;
		nr= new node;
		nr->sym=next;
		nr->count=1;
		nr->weight=next_wt;
		max_ptr[next_wt]=nr;
		next_wt--;
		nr->parent=pnyt;
		nr->left=NULL;
		nr->right=NULL;

		nl= new node;
		nl->sym='$';
		nl->count=0;
		nl->weight=next_wt;
		max_ptr[next_wt]=nl;
		next_wt--;
		nl->parent=pnyt;
		nl->left=NULL;
		nl->right=NULL;

		pnyt->right=nr;
		pnyt->left=nl;
		pnyt->sym='-';
		pnyt->count=1;
		pnyt=nl;
		if(pnyt->parent->parent!=NULL)
		{
			if(pnyt->parent->parent->parent==NULL)
				pnyt->parent->parent->count+=1;
			else
				increment(pnyt->parent->parent);
		}

		cout<<next<<": ";
		for(int i=0;i<arr[next-97].fcode.size();i++){
	       	cout<<arr[next-97].fcode[i];
            outp+=arr[next-97].fcode[i];
        }
		cout<<endl;
	}

}

void search(char next, node *nod)
{
	if(ptr_next==NULL && nod!=NULL)
	{
		if(nod->sym==next)
		{
			ptr_next=nod;
			return;
		}
		else
		{
			search(next,nod->left);
			search(next,nod->right);
		}
	}
}

void increment(node *w)
{
	bool swapped=0;
	int i,j;
	for(i=51;i>0&&i>w->weight;i--)
	{
		if(max_ptr[i]->count==w->count && max_ptr[i]!=w && max_ptr[i]!=w->parent)
		{
			node *temp;
			temp=new node;
			if(max_ptr[i]->left != NULL)
			{
				max_ptr[i]->left->parent=w;
				max_ptr[i]->right->parent=w;
			}
			if(w->left != NULL)
			{
				w->left->parent=max_ptr[i];
				w->right->parent=max_ptr[i];
			}
			temp->sym=max_ptr[i]->sym;
			temp->count=max_ptr[i]->count;
			temp->weight=max_ptr[i]->weight;
			temp->parent=max_ptr[i]->parent;
			temp->left=max_ptr[i]->left;
			temp->right=max_ptr[i]->right;
			max_ptr[i]->sym=w->sym;
			max_ptr[i]->count=w->count;
			max_ptr[i]->left=w->left;
			max_ptr[i]->right=w->right;
			w->sym=temp->sym;
			w->count=temp->count;
			w->left=temp->left;
			w->right=temp->right;

			swapped=1;
			break;
		}
	}
	if(w->weight<max_ptr[i]->weight)
		w=max_ptr[i];
	w->count+=1;
	if(w->parent!=NULL)
		increment(w->parent);
}

void trav(char c, node *nod)
{
	if(nod==NULL)
		ans.pop_back();

	if(nod!=NULL && flag==0)
	{
		if(nod->sym==c)
		{
			for(int j=0;j<ans.size();j++){
       	    	cout<<ans[j];
                outp+=ans[j];
			}
			flag=1;
			return;
		}
		if(nod->left!=NULL)
        {
            ans.push_back(0);
            trav(c,nod->left);
        }
        if(nod->right!=NULL)
        {
            ans.push_back(1);
            trav(c,nod->right);
        }
        ans.pop_back();
	}
}
