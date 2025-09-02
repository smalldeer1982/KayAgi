#include<bits/stdc++.h>
using namespace std;
string s;
string expand(){
	string s="",x;
	char c;
	int d;
	while(cin>>c){
		if(c=='['){
			cin>>d;
			x=expand();
			while(d--){
				s+=x;
			} 
		}
		else if(c==']'){
			return s;
		}
		else{
			s+=c;
		}
	}
	return s;
}
int main(){
	cout<<expand();
	return 0;
}