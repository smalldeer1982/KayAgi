#include<bits/stdc++.h>
using namespace std;
int n,a[15],sum=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	while(sum!=n-1){
		sum+=1;
		for(int i=1;i<=n-sum;i++){
			a[i]+=a[i+1];
			cout<<a[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
