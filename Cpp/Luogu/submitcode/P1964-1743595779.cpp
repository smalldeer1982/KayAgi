#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,ans=0;
struct thing{
	int num,v,sum;
	string s;
}a[134405];
bool cmp(thing x,thing y){
	if(x.s<y.s){
		return true;
	}
	return false;
}
bool cmp1(thing x,thing y){
	if(x.num*x.v>y.num*y.v){
		return true;
	}
	return false;
}
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].num>>a[i].v>>a[i].sum>>a[i].s;
	}
	sort(a+1,a+n+1,cmp);
	cnt=n;
	for(int i=1;i<=cnt;i++){
		if(a[i].s==a[i+1].s&&a[i].s!=""){
			if(a[i].num+a[i+1].num<=a[i].sum){
				a[i].num+=a[i+1].num;
				a[i+1].s="",a[i+1].num=0,a[i+1].v=0,a[i+1].sum=0;
			}
			else{
				a[i+1].num-=(a[i].sum-a[i].num);
				a[i].num=a[i].sum;
			}
		}
		if(a[i].num>a[i].sum){
			cnt+=1;
			a[cnt].s=a[i].s,a[cnt].num=a[i].num-a[i].sum,a[cnt].v=a[i].v,a[cnt].sum=a[i].sum;
			a[i].num=a[i].sum;
		}
	}
	sort(a+1,a+cnt+1,cmp1);
	for(int i=1;i<=21-m;i++){
		ans+=a[i].num*a[i].v;
	}
	cout<<ans;
	return 0;
}