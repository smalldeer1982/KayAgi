#include<bits/stdc++.h>
using namespace std;
int n,m,a[20005],b[20005],ans=0,x=0;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++){
		if(x==n){
			break;
		}
		if(a[x+1]<=b[i]){
			x+=1;
			ans+=b[i];
		}
	}
	if(x==n){
		cout<<ans<<endl;
	}
	else{
		cout<<"you died!"<<endl;
	}
	return 0;
}
