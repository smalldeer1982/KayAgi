#include<bits/stdc++.h>
using namespace std;
int n,m,g[85][85];
__int128 dp[85][85],b[85];
__int128 solve(int a[],int c){
	for(int len=1;len<=c;len++){
		for(int i=1;i+len-1<=c;i++){
			int j=i+len-1;
			int k=c-j+i;
			if(i==j){
				dp[i][j]=b[k]*a[i];
			}
			else{
				dp[i][j]=max(b[k]*a[i]+dp[i+1][j],b[k]*a[j]+dp[i][j-1]);
			}
		}
	}
	return dp[1][c];
}
void print(__int128 x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9){
		print(x/10);
	}
	putchar('0'+x%10);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>g[i][j];
		}
	}
	b[1]=2;
	for(int i=2;i<=m;i++){
		b[i]=b[i-1]*2;
	}
	__int128 ans=0;
	for(int i=1;i<=n;i++){
		ans+=solve(g[i],m);
	}
	print(ans);
	return 0;
}
