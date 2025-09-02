#include<bits/stdc++.h>
using namespace std;
string s;
int sum=0,a[100005];
bool flag=0;
int main(){
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]-'0'==0){
			flag=1;
		}
		sum+=(s[i]-'0');
	}
	if(flag==1&&sum%3==0){
		for(int i=0;i<s.size();i++){
			a[i+1]=s[i]-'0';
		}
		sort(a+1,a+s.size()+1);
		for(int i=s.size();i>=1;i--){
			cout<<a[i];
		}
	}
	else{
		cout<<-1;
	} 
	return 0;
} 