#include<bits/stdc++.h>
using namespace std;
string st1,st2;
int a[10100],b[10100],c[10100];
int main(){
	cin>>st1>>st2;
	int len1=st1.size();
	int len2=st2.size();
	for(int i=0;i<len1;i++){
		a[len1-i]=st1[i]-'0';
	}
	for(int i=0;i<len2;i++){
		b[len2-i]=st2[i]-'0';
	}
	for(int i=1;i<=len1;i++){
		for(int j=1;j<=len2;j++){
			c[i+j-1]+=a[i]*b[j];
		}
	}
	int lenc=len1+len2;
	for(int i=1;i<=lenc;i++){
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	while(c[lenc]==0){
		lenc-=1;
	}
	for(int i=max(1,lenc);i>=1;i--){
		cout<<c[i];
	}
	return 0;
} 