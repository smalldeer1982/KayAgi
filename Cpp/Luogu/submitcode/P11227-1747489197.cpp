#include<bits/stdc++.h>
using namespace std;
int n,cnt=0;
string jl[55];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>jl[i];
		bool flag=1;
		for(int j=1;j<=i-1;j++){
			if(jl[i]==jl[j]){
				flag=0;
				break;
			}
		}
		cnt+=flag;
	}
	cout<<52-cnt;
	return 0;
}
