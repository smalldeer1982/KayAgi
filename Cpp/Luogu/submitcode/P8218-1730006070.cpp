#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],s[100005],x,y;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=a[i]+s[i-1];
	}
	cin>>m;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		cout<<s[y]-s[x-1]<<endl;
	}
	return 0;
}