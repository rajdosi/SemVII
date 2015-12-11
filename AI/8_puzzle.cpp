#include<bits/stdc++.h>
using namespace std;


struct got{

    string imp;
    got * arya,*rob,*jon,*sansa;
    got * ned;

}*mad_king;


string goal_state;
queue <string> bfs_queue;
queue <int> bfs_queue_blanks;
queue <int> bfs_count;
queue <struct got *> many_faced_god;
map<string, bool> my_map;


void lynna(struct got * tywin){

    if(tywin==mad_king)
        return ;
    lynna(tywin->ned);
    cout<<tywin->imp<<endl;
}

void bfs(string input,int blank_position,int count , got * spider )
{

    my_map[input]=true;
  //      cout<<input<<endl;
    if(input==goal_state){

        cout<<"SUCCESS."<<endl;
        cout<<"No of Steps :: "<<count<<endl;
        cout<<"Path::"<<endl;
        lynna(spider);
        exit(0);
    }

    struct got *ramsay;

    if(blank_position-3 >= 0){

        input[blank_position]=input[blank_position-3];
        input[blank_position-3]='0';
        if(my_map.find(input)== my_map.end()){

            bfs_queue.push(input);
            bfs_queue_blanks.push(blank_position-3);
            bfs_count.push(count+1);

            ramsay = new got;
            ramsay->imp = input;
            ramsay->ned = spider;
            spider->arya=ramsay;
            many_faced_god.push(ramsay);
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

            bfs_queue.push(input);
            bfs_queue_blanks.push(blank_position+3);
            bfs_count.push(count+1);

            ramsay = new got;
            ramsay->imp = input;
            ramsay->ned = spider;
            spider->sansa=ramsay;
            many_faced_god.push(ramsay);
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

            bfs_queue.push(input);
            bfs_queue_blanks.push(blank_position-1);
            bfs_count.push(count+1);

            ramsay = new got;
            ramsay->imp = input;
            ramsay->ned = spider;
            spider->rob=ramsay;
            many_faced_god.push(ramsay);
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

            bfs_queue.push(input);
            bfs_queue_blanks.push(blank_position+1);
            bfs_count.push(count+1);

            ramsay = new got;
            ramsay->imp = input;
            ramsay->ned = spider;
            spider->jon=ramsay;
            many_faced_god.push(ramsay);
        }
        else    spider->jon=NULL;
        input[blank_position+1]=input[blank_position];
        input[blank_position]='0';
    }
    else    spider->jon=NULL;

    string temp=bfs_queue.front();
    int pos=bfs_queue_blanks.front();
    int cou=bfs_count.front();
    struct got * valar_morghulis = new got;
    valar_morghulis = many_faced_god.front();


    bfs_queue.pop();
    bfs_queue_blanks.pop();
    bfs_count.pop();
    many_faced_god.pop();

    bfs(temp,pos,cou,valar_morghulis);

}


int main()
{
    string current_state;

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

    bfs(current_state,i,0,mad_king);

    return 0;
}
