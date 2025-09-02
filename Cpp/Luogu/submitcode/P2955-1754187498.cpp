#include<bits/stdc++.h>
using namespace std;
int t;
string x;
int main(){
	cin>>t;
	while(t--){
		cin>>x;
		if((x[x.size()-1]-'0')%2==1){
			cout<<"odd"<<endl;
		}
		else{
			cout<<"even"<<endl;
		}
	}
	return 0;
}