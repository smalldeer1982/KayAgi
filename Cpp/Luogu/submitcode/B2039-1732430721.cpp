#include<bits/stdc++.h>
using namespace std;
long long x,y;
int main(){
	cin>>x>>y;
	if(x>y){
		cout<<">";
	}
	else if(x<y){
		cout<<"<";
	}
	else{
		cout<<"=";
	}
	return 0;
}