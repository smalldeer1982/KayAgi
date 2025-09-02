#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],b[100005],cnt=1,sum=0;
bool flag=0;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
		sum+=b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++){
		if(a[cnt]<b[i]){
			cnt+=1;
			sum-=b[i];
		}
		if(cnt==n+1){
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<0;
	}
	else{
		cout<<sum;
	}
	return 0;
}
