//Practical-1 Shannon fano 08/07-08/07
#include<bits/stdc++.h>
using namespace std;

struct node{
	int freq;
	string code;
	char ch;
	node * next;
}*head, *temp, *newptr, *ptr, *np, *hptr;

node * ncreat(int val, char let){
	newptr = new node;
	newptr->freq = val;
	newptr->ch = let;
	newptr->next = NULL;
	return newptr;
}

void add(node  *np){
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
void display(){
	np=head;
	while(np!=NULL){
		cout<<np->ch<<" "<<np->freq<<" "<<np->code<<"\n";
		np = np->next;
	}
	//cout<<"&&&&"<<endl;
}
void calc(node * np , node *end){
	struct node *temphead,*pre,*head1,*head2;
	temphead = np;
	if(np==end)
		return;
	int sum=0,avg=0,i=0,total=0;
	while(np!=end){
		sum=sum+np->freq;
		np = np->next;
	}
	sum=sum+np->freq;
	avg=sum/2;
	//cout<<endl<<sum<<avg;
	np = temphead;
	for(i=0;i<sum;i++){
		total = total+ np->freq;
		pre=np;
		np->code.push_back('0');
		np = np->next;
		if(total >= avg)
			break;	
	}
	head1=np;
	while(np!=end){
		np->code.push_back('1');
		np=np->next;
	}
	np->code.push_back('1');
	calc(temphead,pre);
	calc(head1,end);
}

int main(int argc, char**argv){
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
		//cout<<let<<endl;
		i++;
		val=0;
		j=0;
		while(data[j]!='\0'){
			if(let == data[j]){
				val++;
			}
			j++;
		}
		if(data[i]=='\0')
			break;
		temp = ncreat(val, let);
		add(temp);
	}
	//cout<<data;
	//display(head);
	ptr=head;
	while(ptr!=NULL)
	{
		hptr=ptr;
		ptr=ptr->next;
	}
	calc(head,hptr);
	display();
	string output= "";
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
	string temp1="";	
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
	fout.close();
	return 0;
}
