#include<bits/stdc++.h>
using namespace std;
int l,r,ans=0;
int main(){
	cin>>l>>r;	
	for(int i=l;i<=r;i++){
		string s=to_string(i);
		for(int j=0;j<s.length();j++){
			if(s[j]=='2'){
				ans+=1;
			} 
		}
	}
	cout<<ans;
	return 0;
}