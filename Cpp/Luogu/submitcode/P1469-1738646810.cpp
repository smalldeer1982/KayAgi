#include<bits/stdc++.h>
using namespace std;
int n,a[10000005],x,ans=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		ans^=x;
	}
	cout<<ans;
	return 0;
}
