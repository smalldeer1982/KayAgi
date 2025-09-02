#include<bits/stdc++.h>
using namespace std;
int a,b,t,ans;
int main(){
	cin>>a>>b>>t;
	ans=a+(b-a)*(t-1);
	cout<<ans;
	return 0;
}