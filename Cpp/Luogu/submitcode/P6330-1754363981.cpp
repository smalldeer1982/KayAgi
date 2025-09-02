#include<bits/stdc++.h>
using namespace std;
int x,y,a,b;
int main(){
	for(int i=1;i<=3;i++){
		cin>>a>>b;
		x^=a;
		y^=b;
	}
	cout<<x<<" "<<y;
	return 0;
} 