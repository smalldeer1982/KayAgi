#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b,c,d;
bool solve(int x,int y){
	if(x*y<-2147483648||x*y>2147483647){
		return false;
	}
	return true;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a>>b>>c>>d;
	if(solve(a,c)&&solve(a,d)&&solve(b,c)&&solve(b,d)==1){
		cout<<"int";
	}
	else{
		cout<<"long long int";
	}
	return 0;
}
