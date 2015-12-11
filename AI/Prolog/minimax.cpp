#include<bits/stdc++.h>

using namespace std;


class node
{
	public:
	int arr[3][3];
};
node board;
int computer_sym = 1;
int user_sym = 0;

pair<int,bool> checkboard(int arr[3][3])
{
	
	for(int i=0;i<3;i++)
	{
		if(arr[i][0] == arr[i][1] && arr[i][2] == arr[i][0] && arr[i][0] != -1)
			return make_pair(arr[i][0],true); 
		if(arr[0][i] == arr[1][i] && arr[2][i] == arr[0][i] && arr[0][i] != -1)
			return make_pair(arr[0][i],true); 
	}
	if(arr[0][0]  == arr[1][1] && arr[1][1] == arr[2][2] && arr[0][0] != -1)
		return make_pair(arr[0][0],true); 
	if(arr[0][2]  == arr[1][1] && arr[1][1] == arr[2][0] && arr[2][0] != -1)
		return make_pair(arr[2][0],true); 
	bool f = false;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(arr[i][j] == -1){
				f = true;
				break;
			}
		}
	}
	if(!f)
		return make_pair(-1,true);
		
	return make_pair(0,false);
}



void print_board()
{
	cout<<endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(board.arr[i][j] == 1)
				cout<<"X ";
			else if(board.arr[i][j] == -1)
				cout<<"- ";
			else
				cout<<"O ";
		}
		cout<<endl;
		
	}
	cout<<endl;
}


int minmax(node s,int sym)
{
	pair<int,bool> v = checkboard(s.arr);
	if(v.second == true){
		if(v.first == sym)
			return 1;
		else if(v.first == abs(1-sym))
			return -1;
		else
			return 0;
	}
	bool flag = false;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(s.arr[i][j] == -1){
				s.arr[i][j] = sym;
				int val = minmax(s,abs(1-sym));
				s.arr[i][j] = -1;
				if(val == -1){
					return 1;
				}
				else if(val == 0){
					flag = true;
				}
			}
		}
	}
	if(flag == true)
		return 0;
	else
		return -1;
	
}

int main()
{
	cout<<"User Symbol :- O and Computer Symbol :- X"<<endl;
	bool chance;
	cout<<"If you want first chance press 0 else press 1"<<endl;
	cin>>chance;
	// true chance for computer
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++){
			board.arr[i][j] = -1;
		}
	}
	pair<int,bool> d;
	do
	{
		print_board();
		bool flag = false;
		int posx=-1,posy=-1;
		if(chance == true){
			chance = !chance;
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					if(board.arr[i][j] == -1){
						board.arr[i][j] = computer_sym;
						int val = minmax(board,user_sym);
						cout<<val<<" "<<i<<" "<<j<<endl;
						if(val == -1){
							flag = true;
							break;
						}
						else if(val == 0){
							posx = i;
							posy = j;
							board.arr[i][j] = -1;
						}
						else
							board.arr[i][j] = -1;
					}
				}
				if(flag)
					break;
			}
			if(flag == false){
				if(posx == -1 && posy == -1){
					cout<<"Computer loose!!"<<endl;
					exit(0);
				}
				else{
					board.arr[posx][posy] = computer_sym;
				}
			}
		}
		else{
			int x,y;
			cout<<"Enter the x coordinate : ";
			cin>>x;
			cout<<"Enter the y coordinate : ";
			cin>>y;
			if(board.arr[x][y] != -1){
				cout<<"Invalid Choice!! Please Enter again,..."<<endl;
				continue;
			}
			board.arr[x][y] = user_sym;
			chance = !chance; 
		}
		d = checkboard(board.arr);
	}while(d.second == false);
	print_board();
	if(d.first == computer_sym)
		cout<<"Computer won"<<endl;
	else if(d.first == user_sym)
		cout<<"user won"<<endl;
	else
		cout<<"Draw"<<endl;
	return 0;
}
