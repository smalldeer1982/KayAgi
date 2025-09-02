#include<bits/stdc++.h>
using namespace std;
int n,num=0,cnt=0,c[10005];
struct student{
	int c,m,e,sum,num1,ans,flag;
}a[10005];
bool judge(student x,student y){
	if(x.sum!=y.sum){
		return x.sum>y.sum;
	}
	else if(x.sum==y.sum&&(x.c+x.m!=y.c+y.m)){
		return x.c+x.m>y.c+y.m;
	}
	else if(x.sum==y.sum&&(x.c+x.m==y.c+y.m)&&(max(x.c,x.m)!=max(y.c,y.m))){
		return max(x.c,x.m)>max(y.c,y.m);
	}
	else{
		return true;
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].c>>a[i].m>>a[i].e;
		a[i].sum=a[i].c+a[i].m+a[i].e;
		a[i].num1=i;
	}
	sort(a+1,a+n+1,judge);
//	for(int i=1;i<=n;i++){
//		cout<<a[i].c<<" "<<a[i].m<<" "<<a[i].e<<" "<<a[i].sum<<" "<<a[i].num1<<" "<<a[i].ans<<" "<<a[i].flag<<endl;
//	}
	for(int i=1;i<=n;i++){
		if(a[i-1].sum==a[i].sum&&(a[i-1].c+a[i-1].m==a[i].c+a[i].m)&&(max(a[i-1].c,a[i-1].m)==max(a[i].c,a[i].m))){
			c[a[i].num1]=c[a[i-1].num1];
			cnt+=1;
		}
		else{
			cnt+=1;
			c[a[i].num1]=cnt;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<c[i]<<endl;
	}
	return 0;
}