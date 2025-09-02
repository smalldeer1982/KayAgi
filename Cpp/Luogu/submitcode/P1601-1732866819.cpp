#include<bits/stdc++.h>
using namespace std;
string st1,st2;
int a[505],b[505],c[505];
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
	int lenc=max(len1,len2);
	for(int i=1;i<=lenc;i++){
		c[i]=a[i]+b[i];
	}
	for(int i=1;i<=lenc;i++){
		if(c[i]>=10){
			c[i+1]+=1;
			c[i]-=10;
		}
	}
	if(c[lenc+1]){
		lenc+=1;
	}
	for(int i=lenc;i>=1;i--){
		cout<<c[i];
	}
	return 0;
} 