#include<bits/stdc++.h>
using namespace std;
int n; 
struct node{
	string s;
	int x,y,lw,num,sum;
	char c,d;
}a[105];
bool cmp(node a1,node b1){
	if(a1.sum>b1.sum){
		return true;
	}
	if(a1.sum==b1.sum&&a1.num<b1.num){
		return true;
	}
	return false;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].s>>a[i].x>>a[i].y>>a[i].c>>a[i].d>>a[i].lw;
		a[i].num=i;
		if(a[i].x>80&&a[i].lw>=1){
			a[i].sum+=8000;
		}
		if(a[i].x>85&&a[i].y>80){
			a[i].sum+=4000;
		}
		if(a[i].x>90){
			a[i].sum+=2000;
		}
		if(a[i].x>85&&a[i].d=='Y'){
			a[i].sum+=1000; 
		}
		if(a[i].y>80&&a[i].c=='Y'){
			a[i].sum+=850;
		}
	}
	sort(a+1,a+n+1,cmp);
	cout<<a[1].s<<endl;
	cout<<a[1].sum<<endl;
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=a[i].sum;
	}
	cout<<ans;
	return 0;
}