#include<bits/stdc++.h>
using namespace std;
int n,vis[105][105];
string a[105];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<n;j++){
			if(a[i][j]=='y'){
				if(i-7+1>=1){
					if(a[i-1][j]=='i'&&a[i-2][j]=='z'&&a[i-3][j]=='h'&&a[i-4][j]=='o'&&a[i-5][j]=='n'&&a[i-6][j]=='g'){
						vis[i][j]=1,vis[i-1][j]=1,vis[i-2][j]=1,vis[i-3][j]=1;
						vis[i-4][j]=1,vis[i-5][j]=1,vis[i-6][j]=1;
					}
				}
				if(i+7-1<=n){
					if(a[i+1][j]=='i'&&a[i+2][j]=='z'&&a[i+3][j]=='h'&&a[i+4][j]=='o'&&a[i+5][j]=='n'&&a[i+6][j]=='g'){
						vis[i][j]=1,vis[i+1][j]=1,vis[i+2][j]=1,vis[i+3][j]=1;
						vis[i+4][j]=1,vis[i+5][j]=1,vis[i+6][j]=1;
					}
				}
				if(j-7+1>=0){
					if(a[i][j-1]=='i'&&a[i][j-2]=='z'&&a[i][j-3]=='h'&&a[i][j-4]=='o'&&a[i][j-5]=='n'&&a[i][j-6]=='g'){
						vis[i][j]=1,vis[i][j-1]=1,vis[i][j-2]=1,vis[i][j-3]=1,
						vis[i][j-4]=1,vis[i][j-5]=1,vis[i][j-6]=1;
					}
				}	
				if(j+7-1<n){
					if(a[i][j+1]=='i'&&a[i][j+2]=='z'&&a[i][j+3]=='h'&&a[i][j+4]=='o'&&a[i][j+5]=='n'&&a[i][j+6]=='g'){
						vis[i][j]=1,vis[i][j+1]=1,vis[i][j+2]=1,vis[i][j+3]=1,
						vis[i][j+4]=1,vis[i][j+5]=1,vis[i][j+6]=1;
					}
				}
				if(i-7+1>=1&&j+7-1<n){
					if(a[i-1][j+1]=='i'&&a[i-2][j+2]=='z'&&a[i-3][j+3]=='h'&&a[i-4][j+4]=='o'&&a[i-5][j+5]=='n'&&a[i-6][j+6]=='g'){
						vis[i][j]=1,vis[i-1][j+1]=1,vis[i-2][j+2]=1,vis[i-3][j+3]=1,
						vis[i-4][j+4]=1,vis[i-5][j+5]=1,vis[i-6][j+6]=1;
					}
				}
				if(i-7+1>=1&&j-7+1>=0){
					if(a[i-1][j-1]=='i'&&a[i-2][j-2]=='z'&&a[i-3][j-3]=='h'&&a[i-4][j-4]=='o'&&a[i-5][j-5]=='n'&&a[i-6][j-6]=='g'){
						vis[i][j]=1,vis[i-1][j-1]=1,vis[i-2][j-2]=1,vis[i-3][j-3]=1,
						vis[i-4][j-4]=1,vis[i-5][j-5]=1,vis[i-6][j-6]=1;
					}
				}
				if(i+7-1<=n&&j-7+1>=0){
					if(a[i+1][j-1]=='i'&&a[i+2][j-2]=='z'&&a[i+3][j-3]=='h'&&a[i+4][j-4]=='o'&&a[i+5][j-5]=='n'&&a[i+6][j-6]=='g'){
						vis[i][j]=1,vis[i+1][j-1]=1,vis[i+2][j-2]=1,vis[i+3][j-3]=1,
						vis[i+4][j-4]=1,vis[i+5][j-5]=1,vis[i+6][j-6]=1;
					}
				}	
				if(i+7-1<=n&&j+7-1<n){
					if(a[i+1][j+1]=='i'&&a[i+2][j+2]=='z'&&a[i+3][j+3]=='h'&&a[i+4][j+4]=='o'&&a[i+5][j+5]=='n'&&a[i+6][j+6]=='g'){
						vis[i][j]=1,vis[i+1][j+1]=1,vis[i+2][j+2]=1,vis[i+3][j+3]=1,
						vis[i+4][j+4]=1,vis[i+5][j+5]=1,vis[i+6][j+6]=1;
					}
				}
			}				
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<n;j++){
			if(vis[i][j]==0){
				cout<<"*";
			}
			else{
				cout<<a[i][j];
			}
		}
		cout<<endl;
	}
	return 0;
}