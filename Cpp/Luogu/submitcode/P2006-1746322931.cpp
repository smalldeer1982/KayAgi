#include<bits/stdc++.h>
using namespace std;
int k,m,n,a[30005],b[30005];
bool flag=0;
int main(){
	cin>>k>>m>>n;
	for(int i=1;i<=m;i++){
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=m;i++){
		if((a[i]==0&&b[i]>0)||(a[i]>0&&k/a[i]*b[i]>=n)){
			cout<<i<<" ";
			flag=1;
		}
	}
	if(flag==0){
		cout<<-1;
	}
	return 0;
}
