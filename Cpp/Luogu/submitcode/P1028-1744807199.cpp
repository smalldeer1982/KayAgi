#include<bits/stdc++.h>
using namespace std;
int n,a[1005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i/2;j++){
			a[i]+=a[j];
		}
		a[i]+=1;
	}
	cout<<a[n];
	return 0;
}
