#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		cout<<"https://www.luogu.com.cn/problem/";
		if(s[0]>='0'&&s[0]<='9'){
			cout<<"P";
		}
		cout<<s<<endl;
	}	
	return 0;
}
