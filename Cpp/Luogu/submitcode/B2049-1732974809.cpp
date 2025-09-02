#include<bits/stdc++.h>
using namespace std;
long long a,b,c;
int main(){
	cin>>a>>b>>c;
	cout<<max(a,max(b,c));
	return 0;
}