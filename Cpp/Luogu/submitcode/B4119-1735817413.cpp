#include<bits/stdc++.h>
using namespace std;
int n;
string s;
bool ans=0,flag=0;
int main(){
	cin>>n;
	cin>>s;
	for(int i=1;i<=n/2;i++){//长度
		if(n%i==0){
			flag=1;
			for(int j=0;j<i;j++){
				for(int k=j;k<n-i;k+=i){
					if(s[k]!=s[k+i]){
						flag=0;
						break;
					}
				}
			}
			if(flag==1){
				ans=1;
				break;
			}
		}
	}
	if(ans==1){
		cout<<"Yes";
	}
	else{
		cout<<"No";
	}
	return 0;
}
