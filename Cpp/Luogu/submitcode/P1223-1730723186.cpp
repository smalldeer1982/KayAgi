#include<bits/stdc++.h>
using namespace std;
int n,sum=0;
double ans=0;
struct student{
	int x,y;
}stu[1000005];
bool cmp(student a,student b){
	if(a.x<b.x){
		return true;
	}
	return false;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>stu[i].x;
		stu[i].y=i;
	}
	sort(stu+1,stu+n+1,cmp);
	for(int i=1;i<=n;i++){
		cout<<stu[i].y<<" ";
		ans+=sum;
		sum+=stu[i].x;
	}
	cout<<endl;
	ans/=n;
	printf("%.2f",ans);
	return 0;
}