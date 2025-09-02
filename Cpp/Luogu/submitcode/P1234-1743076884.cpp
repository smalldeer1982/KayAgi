#include<bits/stdc++.h>
using namespace std;
int n,m,sum;
string a[1005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<m;j++){
			if(a[i][j]=='h'){
				if(i-4+1>=1){
					if(a[i-1][j]=='e'&&a[i-2][j]=='h'&&a[i-3][j]=='e'){
						sum+=1;
					}
				}
				if(i+4-1<=n){
					if(a[i+1][j]=='e'&&a[i+2][j]=='h'&&a[i+3][j]=='e'){
						sum+=1;
					}
				}
				if(j-4+1>=0){
					if(a[i][j-1]=='e'&&a[i][j-2]=='h'&&a[i][j-3]=='e'){
						sum+=1;
					}
				}	
				if(j+4-1<m){
					if(a[i][j+1]=='e'&&a[i][j+2]=='h'&&a[i][j+3]=='e'){
						sum+=1;
					}
				}
			}				
		}
	}
	cout<<sum;
	return 0;
}