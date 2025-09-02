#include<bits/stdc++.h>
using namespace std;
int n,a[1005][1005],b[1005][1005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			cin>>a[i][j];
			if(i==n){
				b[i][j]=a[i][j];
			}
		}
	}
	for(int i=n-1;i>=1;i--){
		for(int j=1;j<=i;j++){
			b[i][j]=a[i][j]+max(b[i+1][j],b[i+1][j+1]);
		}
	}
	cout<<b[1][1];
	return 0;
}