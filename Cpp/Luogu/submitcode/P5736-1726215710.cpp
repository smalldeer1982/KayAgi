#include<bits/stdc++.h>
using namespace std;
int n;
int a[105];
int judge(int x){
	if(x<=1)
		return 0;
	for(int i=2;i<=sqrt(x);i++)
		if(x%i==0)
			return 0;
	return 1;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(judge(a[i]))
			cout<<a[i]<<" ";
	}
	return 0;
}