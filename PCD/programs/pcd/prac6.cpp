#include<bits/stdc++.h>
using namespace std;

int length,i,nameOfreg=1;
string input;


struct tree{
	
	char node;
	int no_reg,lines_code;
	char name_reg[4];
	char code[400];
	tree * left,*right;
	tree *parent;

};

int generate_tree(struct tree * root){

	if(i==0) return 0;
	if(input[i]!='+' && input[i]!='/' && input[i]!='-' && input[i]!='*'){
		return 0;
	}

	tree *r_child=new tree;
	i--;
	root->right=r_child;
	r_child->node=input[i];
	r_child->parent=root;

	r_child->left=NULL;
	r_child->right=NULL;
	
	generate_tree(r_child);

	tree *l_child=new tree;
	i--;
	root->left=l_child;
	l_child->node=input[i];
	l_child->parent=root;

	l_child->left=NULL;
	l_child->right=NULL;
	generate_tree(l_child);



}
void generate_code(struct tree *p,int count){

	
	if(p->left==NULL){
	
		if(count!=0){
			p->name_reg[0]='R';
			char temp[2];
			sprintf(temp,"%d",nameOfreg);
			strcat(p->name_reg,temp);
			nameOfreg++;
			p->lines_code=1;
			strcpy(p->code,"MOV ");
			strcat(p->code,p->name_reg);
			strcat(p->code," ");
			sprintf(temp,"%c",p->node);
			strcat(p->code,temp);
			strcat(p->code,". ");
		}
		else{
			p->name_reg[0]=p->node;
			p->lines_code=0;
		}
		
		p->no_reg=count;
		return;
	}
	
	generate_code(p->left,1);
	generate_code(p->right,0);
	
	if(p->left->no_reg != p->right->no_reg){
		p->no_reg = max(p->left->no_reg,p->right->no_reg);
	}
	else{
		p->no_reg=p->left->no_reg+1;
	}
	strcpy(p->name_reg,p->left->name_reg);
	p->lines_code=p->left->lines_code+p->right->lines_code+1;
	strcat(p->code,p->left->code);
	strcat(p->code,p->right->code);
	if(p->node=='*')
		strcat(p->code,"MUL ");
	else if(p->node=='+')
		strcat(p->code,"ADD ");
	else if(p->node=='-')
		strcat(p->code,"SUB ");
	else if(p->node=='/')
		strcat(p->code,"DIV ");
	strcat(p->code,p->left->name_reg);
	strcat(p->code," ");
	strcat(p->code,p->right->name_reg);
	strcat(p->code,". ");
}


int print_tree(tree * temp){

	if(temp==NULL)	return 0;

	cout<<temp->node<<" "<<temp->no_reg<<" "<<temp->name_reg<<" "<<temp->code<<endl;
	print_tree(temp->left);
	print_tree(temp->right);

}

int main(){
	
	cout<<"Enter tree."<<endl;
	cin>>input;

	length=input.length();
	i=length-1;

	
	tree * root_node=new tree;
	root_node->node=input[length-1];
		
	generate_tree(root_node);

	generate_code(root_node,1);
	cout<<endl;
	print_tree(root_node);

	return 0;
}

