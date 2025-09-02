#include<bits/stdc++.h>
using namespace std;
int n,m,minn=3000,sum=0;
char a[55][55];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n-2;i++){
		for(int j=i+1;j<=n-1;j++){
			sum=0;
			for(int k=1;k<=m;k++){
				for(int l=1;l<=i;l++){
					if(a[l][k]!='W'){
						sum+=1;
					}
				}
			}
			for(int k=1;k<=m;k++){
				for(int l=i+1;l<=j;l++){
					if(a[l][k]!='B'){
						sum+=1;
					}
				}
			}
			for(int k=1;k<=m;k++){
				for(int l=j+1;l<=n;l++){
					if(a[l][k]!='R'){
						sum+=1;
					}
				}
			}
			minn=min(minn,sum);
		}
	}
	cout<<minn;
	return 0;
}