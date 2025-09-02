#include<bits/stdc++.h>
using namespace std;
string s1,s2;
void dfs(string x,string y){
	if(x=="\0"||y=="\0"){
		return;
	}
	int pos=x.find(y[y.size()-1]);
	cout<<x[pos];
	dfs(x.substr(0,pos),y.substr(0,pos));
	dfs(x.substr(pos+1),y.substr(pos,y.size()-pos-1));
}
int main(){
	cin>>s1>>s2;
	dfs(s1,s2);
	return 0;
}
