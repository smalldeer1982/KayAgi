#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int main(){
	cin>>n>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='J'){
			s[i]='O';
		}
		else if(s[i]=='O'){
			s[i]='I';
		}
		else{
			s[i]='J';
		}
	}
	cout<<s;
	return 0;
}
