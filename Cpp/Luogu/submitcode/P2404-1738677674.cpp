#include<bits/stdc++.h>
using namespace std;
int n,a[15]={1},x;
void dfs(int cnt){
	for(int i=a[cnt-1];i<=x;i++){
		if(i==n){
			continue;
		}
		x-=i;
		a[cnt]=i;
		if(x==0){				
			for(int j=1;j<=cnt-1;j++){
				cout<<a[j]<<"+";
			}
			cout<<a[cnt]<<endl;
		}
		else{
			dfs(cnt+1);	
		}
		x+=i;
}	}		
int main(){
	cin>>n;
	x=n;
	dfs(1);
	return 0;
}
