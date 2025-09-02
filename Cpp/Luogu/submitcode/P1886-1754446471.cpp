#include<bits/stdc++.h>
using namespace std;
int n,k,a[1000005],h=1,t=0;
int q[1000005];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		while(h<=t&&a[q[t]]>=a[i]){
			t--;
		}
		q[++t]=i;
		if(q[h]<i-k+1){
			h++; 
		}
		if(i>=k){
			cout<<a[q[h]]<<" ";
		}
	}
	cout<<'\n';
	h=1,t=0;
	memset(q,0,sizeof(q));
	for(int i=1;i<=n;i++){
		while(h<=t&&a[q[t]]<=a[i]){
			t--;
		}
		q[++t]=i;
		if(q[h]<i-k+1){
			h++; 
		}
		if(i>=k){
			cout<<a[q[h]]<<" ";
		}
	}
	return 0;
}
