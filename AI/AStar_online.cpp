#include<bits/stdc++.h>
using namespace std;


struct got{

    string imp;
    got * arya,*rob,*jon,*sansa;
    got * ned;

}*mad_king;

struct open_stack{

    string state;
    int heuristic;
    int current_path_length;
    int blank_position;
    struct got *current_tree_node;

    open_stack * next;
}*head=NULL;

string goal_state,current_state;
map<string, bool> my_map;
struct got * spider ;

void lynna(struct got * tywin){

    if(tywin==mad_king)
        return ;
    lynna(tywin->ned);
    for(int i=0;i<9;i++){
        cout<<tywin->imp[i]<<" ";
        if((i+1)%3==0)  cout<<endl;
    }
    cout<<endl;
}

int check_heuristic(string input){

    int heuristic=0;
    for(int i=0;i<9;i++){
        if(input[i]!=goal_state[i])
            heuristic++;
    }
    return heuristic;
}


void insert_into_open_stack(string input, int heurisrtic, int current_path,int blank_position,struct got *current_tree_node){

    struct open_stack * temp,*previous;
    for(temp=head;temp!=NULL;temp=temp->next){
        if(input==temp->state && (heurisrtic+current_path)<(temp->heuristic+temp->current_path_length)){
            if(temp==head)  head=head->next;
            else if(temp->next==NULL)   previous->next=NULL;
            else{
                    previous->next=temp->next;
                    temp->next=NULL;
            }
        }
        else if(input==temp->state)
            return ;
        previous=temp;
    }
    struct open_stack * insert_node = new open_stack;
    if(head==NULL){
        head=insert_node;
        insert_node->next=NULL;
    }
    else{

        temp=head;
        while(temp!=NULL && (temp->heuristic+temp->current_path_length)<(heurisrtic+current_path)){
            previous=temp;
            temp=temp->next;
        }
        if(temp==head) {
            insert_node->next=head;
            head=insert_node;
        }
        else if(temp==NULL){
            previous->next=insert_node;
            insert_node->next = NULL;
        }
        else{
            previous->next=insert_node;
            insert_node->next=temp;
        }
    }
    insert_node->state=input;
    insert_node->heuristic=heurisrtic;
    insert_node->current_path_length=current_path;
    insert_node->blank_position=blank_position;
    insert_node->current_tree_node=current_tree_node;
    return;
}

void a_star()
{


    struct open_stack *current = new open_stack,*temp_print;
    current=head;
    head=head->next;
    current->next=NULL;

    string input = current->state;
    int current_path_length= current->current_path_length;
    int blank_position= current->blank_position;
    spider = current->current_tree_node;

    if(current_path_length==20){
        cout<<"Solution Not Possible with i5 processor with windows 8.1 OS with sitting baba on your right side."<<endl;
        exit(0);
    }
    if(input==goal_state){

        cout<<"SUCCESS.\t";
        cout<<"No of Steps :: "<<current_path_length<<endl;
        cout<<"Path::"<<endl;
        cout<<current_state[0]<<" "<<current_state[1]<<" "<<current_state[2]<<endl;
        cout<<current_state[3]<<" "<<current_state[4]<<" "<<current_state[5]<<endl;
        cout<<current_state[6]<<" "<<current_state[7]<<" "<<current_state[8]<<endl<<endl;
        lynna(spider);
        exit(0);
    }

    my_map[input]=true;

    struct got *ramsay;
    int heuristic;

    if(blank_position-3 >= 0){

        input[blank_position]=input[blank_position-3];
        input[blank_position-3]='0';
        if(my_map.find(input)== my_map.end()){

            ramsay = new got;
            ramsay->imp = input;
            ramsay->ned = spider;
            spider->arya=ramsay;

            heuristic=check_heuristic(input);
            insert_into_open_stack(input,heuristic,current_path_length+1,blank_position-3,ramsay);
        }
        else    spider->arya=NULL;
        input[blank_position-3]=input[blank_position];
        input[blank_position]='0';
    }
    else    spider->arya=NULL;

    if(blank_position+3 <= 8){

        input[blank_position]=input[blank_position+3];
        input[blank_position+3]='0';
        if(my_map.find(input)== my_map.end()){

            ramsay = new got;
            ramsay->imp = input;
            ramsay->ned = spider;
            spider->sansa=ramsay;

            heuristic=check_heuristic(input);
            insert_into_open_stack(input,heuristic,current_path_length+1,blank_position+3,ramsay);
        }
        else    spider->sansa=NULL;
        input[blank_position+3]=input[blank_position];
        input[blank_position]='0';
    }
    else    spider->sansa=NULL;

    if(blank_position%3 != 0){

        input[blank_position]=input[blank_position-1];
        input[blank_position-1]='0';
        if(my_map.find(input)== my_map.end()){
            ramsay = new got;
            ramsay->imp = input;
            ramsay->ned = spider;
            spider->rob=ramsay;

            heuristic=check_heuristic(input);
            insert_into_open_stack(input,heuristic,current_path_length+1,blank_position-1,ramsay);
        }
        else    spider->rob=NULL;
        input[blank_position-1]=input[blank_position];
        input[blank_position]='0';
    }
    else    spider->rob=NULL;

    if((blank_position+1)%3 != 0){

        input[blank_position]=input[blank_position+1];
        input[blank_position+1]='0';
        if(my_map.find(input)== my_map.end()){

            ramsay = new got;
            ramsay->imp = input;
            ramsay->ned = spider;
            spider->jon=ramsay;

            heuristic=check_heuristic(input);
            insert_into_open_stack(input,heuristic,current_path_length+1,blank_position+1,ramsay);
        }
        else    spider->jon=NULL;
        input[blank_position+1]=input[blank_position];
        input[blank_position]='0';
    }
    else    spider->jon=NULL;

    a_star();

}


int main()
{
    cout<<"Enter current state row wise."<<endl;
    cin>>current_state;

    cout<<"Enter goal state roe wise."<<endl;
    cin>>goal_state;

    int i;
    for(i=0;i<9;i++)
    {
        if(current_state[i]=='0')
            break;
    }
    mad_king = new got;
    mad_king->ned=NULL;
    mad_king->imp=current_state;

    head= new open_stack;
    head->state=current_state;
    head->heuristic=check_heuristic(current_state);
    head->blank_position=i;
    head->current_path_length=0;
    head->current_tree_node=mad_king;
    head->next=NULL;
    a_star();
    return 0;
}
