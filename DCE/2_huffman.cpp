/*	Practical 2 
Huffman coding 22-07 to 29-07
compile using g++ -std=c++11 jul22.cpp */

#include<bits/stdc++.h>
using namespace std;

struct tree{
	char ch;
	string code= "";
	tree *lptr,*rptr;
}*t_head;

struct node{
	int freq;
	string code;
	char ch;
	node * next;
	tree *te_head;
}*head, *temp, *newptr, *ptr, *np, *hptr;

node * ncreat(int val, char let){
	newptr = new node;
	newptr->freq = val;
	newptr->ch = let;
	newptr->next = NULL;
	return newptr;
}


void add(node  *np){
	cout<<np->ch<<endl;
	if(head==NULL){
		head = np;
	}
	else{
		int val;
		val = np->freq;
		hptr = head;
		ptr = head;
		while(ptr!=NULL){
			if(ptr->ch == np->ch){
				return;
			}
			if(ptr->freq < val){
				if(ptr == head){
					temp = head;
					head = np;
					np->next = temp;
					break;
				}
				else{
					temp = hptr->next;
					hptr->next=np;
					np->next=temp;
					break;
				}
			}
			if(ptr->next==NULL){
				ptr->next = np;
				break;
			}
			hptr = ptr;
			ptr=ptr->next;
		}
	}
}

tree * add_tree(node *left,node *right)
{
	struct tree *temp_head,*t_left,*t_right;
	t_left= new tree;
	t_right= new tree;
	temp_head= new tree;

	if(left->ch=='$' && right->ch!='$')
	{
		temp_head->lptr=left->te_head;
		temp_head->rptr=t_right;
		t_right->ch=right->ch;
		t_right->lptr=NULL;
		t_right->rptr=NULL;
		cout<<"left is tree"<<endl;
	}
	else if(right->ch=='$' && left->ch!='$')
	{
		temp_head->rptr=right->te_head;
		temp_head->lptr=t_left;
		t_left->ch=left->ch;
		t_left->lptr=NULL;
		t_left->rptr=NULL;
		cout<<"right is tree"<<endl;
	}
	else if(right->ch=='$'&& left->ch=='$')
	{
		temp_head->lptr=left->te_head;
		temp_head->rptr=right->te_head;
		cout<<"both are tree"<<endl;
	}
	else
	{
		temp_head->rptr=t_right;
		temp_head->lptr=t_left;
		t_left->ch=left->ch;
		t_right->ch=right->ch;
		t_right->lptr=NULL;
		t_right->rptr=NULL;
		t_left->lptr=NULL;
		t_left->rptr=NULL;
		cout<<"nothing is tree"<<endl;		
	}

	return temp_head;
}
void sort(node * enter)
{
	struct node *tapan,*pranjal;
	tapan=pranjal=head;
	while(tapan->freq > enter->freq && tapan!=NULL)
	{
		pranjal=tapan;
		tapan=tapan->next;
	}
	if(tapan==head)
	{
		head=enter;
		head->next=tapan;
	}
	else if(tapan==NULL)
	{
		pranjal->next=enter;
		enter->next=NULL;
	}
	else
	{
		pranjal->next=enter;
		enter->next=tapan;
	}
}
void display(){
	np=head;
	while(np!=NULL){
		cout<<np->ch<<" "<<np->freq<<" "<<np->code<<"\n";
		np = np->next;
	}
	cout<<"&&&&"<<endl<<endl;
}
void code_tree(tree* tree_head, string co){
	if(tree_head==NULL)
		return;
	if(tree_head->ch!='\0')
		cout<<tree_head->ch<<" ";
	tree_head->code=co;
	//cout<<co<<endl;
	code_tree(tree_head->lptr,co+'0');
	code_tree(tree_head->rptr,co+'1');
}
void disp_tree_code(tree* tree_head){
	if(tree_head==NULL)
		return;
	if(tree_head->ch!='\0')
		cout<<tree_head->ch<<" "<<tree_head->code<<endl;
	disp_tree_code(tree_head->lptr);
	disp_tree_code(tree_head->rptr);
}
tree* hoffman()
{
	display();
	t_head=new tree;
	struct node *last_node,*prev,*prevOfprev,*new_node;
	while(prev!=prevOfprev){
		display();	
		last_node=prev=prevOfprev=head;
		while(last_node->next!=NULL)
		{
			prevOfprev=prev;
			prev=last_node;
			last_node=last_node->next;
		}
		new_node = new node;
		prevOfprev->next=NULL;
		new_node->freq=prev->freq+last_node->freq;
		new_node->ch='$';
		sort(new_node);
		new_node->te_head=add_tree(prev,last_node);
	}
	return new_node->te_head;
}
int main(int argc, char ** argv){
	int val=0, i=0, j=0;
	char data[100], let;
	fstream f1;
	f1.open(argv[1],ios::in);
	while(!(f1.eof())){
		f1 >> data[i];
		i++;
	}
	f1.close();
	data[i]='\0';
	int last=i;
	i=0;
	while(1){
		let = data[i];
		i++;
		val=0;
		j=0;
		while(data[j]!='\0'){
			if(let == data[j]){
				val++;
			}
			j++;
		}
		temp = ncreat(val, let);
		add(temp);
		if(data[i]=='\0')
			break;
	}
	ptr=head;
	while(ptr!=NULL)
	{
		hptr=ptr;
		ptr=ptr->next;
	}
	struct tree *tree_head;
	tree_head = hoffman();
	code_tree(tree_head,"");
	cout<<endl;
	disp_tree_code(tree_head);
	//display();
	/*string output= "";
	i=0;
	struct node *print;
	//cout<<"****";
	while(i<last-1){
		//cout<<data[i]<<" ";
		print=head;
		while(print->ch!=data[i]&& print!=NULL)
		{
			print=print->next;
		}
		//cout<<print->code<<endl;
		output+=print->code;
		i++;
	}
	cout<<output<<endl;//<<"end"<<output.length()<<endl;
	/*string h = output.substr(8,16);
	cout<<h<<endl;*/
	/*string temp1="";
	for(i=0;i<int(output.length());i+=8)
	{
		int m = min(i+8,int(output.size()));
		string temp2;
		for(int k=i;k<m;k++)
			temp2 = temp2 + output[k];
		//cout<<temp2<<endl;
		//cout<<stoi(temp2,nullptr,2)<<endl;
		temp1+=stoi(temp2,nullptr,2);
	}
	fstream fout;
	fout.open("newfile.txt",ios::out);
	fout<<temp1;
	fout.close();*/
	return 0;
}
