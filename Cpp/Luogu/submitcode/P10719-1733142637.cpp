#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[105][105],b[105][105],minn=0x3f3f3f3f,sum=0,flag=0;
char s;
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s;
			a[i][j]=s-'0';
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+a[i][j];
		}
	}
	for(int x=1;x<=n;x++){
		for(int y=1;y<=m;y++){
			for(int i=x;i<=n;i++){
				for(int j=y;j<=m;j++){
					sum=b[i][j]-b[x-1][j]-b[i][y-1]+b[x-1][y-1];
					if(sum>=k){
						flag=1;
						minn=min(minn,(i-x+1)*(j-y+1));
					}
				}
			}
		}
	}
	if(flag==0){
		cout<<0;
	}
	else{
		cout<<minn;
	}
	return 0;
}