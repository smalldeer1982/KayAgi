#include<bits/stdc++.h>
#define def(i) for(int i=1;i<=3;i++)
using namespace std;
int n,sum=0;
int main(){
	cin>>n;
	if(n>30){
		cout<<0;
		return 0;
	}
	def(a)def(b)def(c)def(d)def(e)def(f)def(g)def(h)def(i)def(j){
		if(a+b+c+d+e+f+g+h+i+j==n){
			sum+=1;
		}
	}
	cout<<sum<<endl;
	def(a)def(b)def(c)def(d)def(e)def(f)def(g)def(h)def(i)def(j){
		if(a+b+c+d+e+f+g+h+i+j==n){
			cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<g<<" "<<h<<" "<<i<<" "<<j<<endl;
		}
	}
	return 0;
}