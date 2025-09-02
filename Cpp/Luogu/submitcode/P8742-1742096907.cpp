#include<bits/stdc++.h>
using namespace std;
int n,a[105],f[105][100005];
int main(){
	cin>>n;
	int m=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		m+=a[i];
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=m;j>=0;j--){
			f[i][j]=f[i-1][j]||f[i-1][abs(j-a[i])]||f[i-1][j+a[i]];
		}
	}
	int ans=0;
	for(int i=1;i<=m;i++){
		if(f[n][i]==1){
			ans+=1;
		}
	}
	cout<<ans;
	return 0;
}
