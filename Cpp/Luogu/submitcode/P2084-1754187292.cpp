#include<bits/stdc++.h>
using namespace std;
int n;
string s;
bool flag=1;
int main(){
	cin>>n>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]-'0'){
			if(flag){
				flag=0;
				cout<<s[i]<<"*"<<n<<"^"<<s.size()-i-1;
			}
			else{
				cout<<"+"<<s[i]<<"*"<<n<<"^"<<s.size()-i-1;
			}
			
		}
	}
	return 0;
}