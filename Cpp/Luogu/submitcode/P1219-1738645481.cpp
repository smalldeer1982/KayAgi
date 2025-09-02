#include <bits/stdc++.h>
using namespace std;
int num=0,n=1,result[15],sum=0;
void dfs(int k){
	if(k==n+1){
		num+=1;
		sum+=1;
		if(sum<=3){
			for(int i=1;i<=n;i++){
				cout<<result[i]<<" ";
			}
			cout<<endl;
		}
		return;
	}
	for(int i=1;i<=n;i++){
		bool flag=1;
		for(int j=1;j<k;j++){
			if(result[j]==i||abs(k-j)==abs(i-result[j])){
				flag=0;
				break;
			}
		}
		if(flag){
			result[k]=i;
			dfs(k+1);
		}
	}
}
int main(){
	cin>>n;
	dfs(1);
	cout<<num;
	return 0;
}