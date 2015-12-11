# include<bits/stdc++.h>
using namespace std;

int main()
	{
	int i=0,c=0;
	string input,key,cipher,decipher;
	cout<<"Enter the plain text:";
	cin>>input;
	cout<<"Enter the key:";
	cin>>key;
	key=key+input;
	cout<<"\n";
	cout<<"Encrypted Text:";
	while(i!=input.length())
			{
			cipher[i]=((input[i]-'a')+(key[i]-'a'))%26 +'a';
			//c++;
			cout<<cipher[i];
			//c=c%key.length();								polyalpha
			i++;
			}
	i=0;
	cout<<endl<<"Decrypted Text:";
	while(i!=input.length())
			{
			char a=((cipher[i]-'a')-(key[i]-'a'));
			if(int(a)<0)
				a=a+'z'+1;
			else
				a=a+'a';
			cout<<a;
			//c=c%key.length();								polyalpha
			i++;
			}
		cout<<endl;
	return 0;
	}