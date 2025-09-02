#include<bits/stdc++.h>
using namespace std;
int n,m,k,sum=0;
char a[105][105];
bool flag=1;
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='.'){
				flag=1;
				for(int l=1;l<=k-1;l++){
					if(a[i+l][j]!='.'){
						flag=0;
						break;
					}
				}
				if(flag==1){
					sum+=1;
				}
				flag=1;	
				for(int l=1;l<=k-1;l++){
					if(a[i][j+l]!='.'){
						flag=0;
						break;
					}
				}
				if(flag==1){
					sum+=1;
				}	
			}
		}
	}
	if(k==1){
		cout<<sum/2;
	}
	else{
		cout<<sum;
	}
	return 0;
}