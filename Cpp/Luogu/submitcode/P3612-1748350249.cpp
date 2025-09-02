#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int n,sum;
signed main(){
	cin>>s>>n;
	sum=s.size();
	while(sum<n){
		int num=sum;
		while(n>num){
			num*=2;
		}
		num/=2;
		n-=(num+1);
		if(n==0){
			n=num;
		}
	}
	cout<<s[n-1];
	return 0;
}
