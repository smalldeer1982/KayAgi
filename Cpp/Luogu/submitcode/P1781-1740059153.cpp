#include<bits/stdc++.h>
using namespace std;
int n;
struct zt{
	string s;
	int num;
}a[25];
bool cmp(zt x,zt y){
	if(x.s.size()>y.s.size()){
		return true;
	}
	else if(x.s.size()==y.s.size()&&x.s>y.s){
		return true;
	}
	return false;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].s;
		a[i].num=i;
	}
	sort(a+1,a+n+1,cmp);
	cout<<a[1].num<<endl;
	cout<<a[1].s;
	return 0;
}
