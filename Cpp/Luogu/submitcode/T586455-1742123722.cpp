#include<bits/stdc++.h>
using namespace std;
string s;
bool flag=0;
int main(){
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]==')'){
			flag=0;
		}
		if(flag==1){
			cout<<s[i];
		}
		if(s[i]=='('){
			flag=1;
		}
	}
	return 0;
}
