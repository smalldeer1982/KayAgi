#include<bits/stdc++.h>
using namespace std;
long long n,m,c,maxn=-1e9,x,y;
long long a[1005][1005],b[1005][1005];
int main(){
	cin>>n>>m>>c;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(maxn<b[i+c-1][j+c-1]-b[i-1][j+c-1]-b[i+c-1][j-1]+b[i-1][j-1]){
				if(i+c-1<=n&&j+c-1<=m){
					x=i;
					y=j;
					maxn=b[i+c-1][j+c-1]-b[i-1][j+c-1]-b[i+c-1][j-1]+b[i-1][j-1];
				}
			}
		}
	}
	cout<<x<<" "<<y;
	return 0;
}