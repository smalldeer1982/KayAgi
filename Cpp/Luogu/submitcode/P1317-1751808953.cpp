#include <bits/stdc++.h>
using namespace std;
int n,m,a[100001],ans,k;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	int i=1;
	while(i<=n){
		while(a[i]<=a[i-1]&&i<=n) i++;//1
		while(a[i]>=a[i-1]&&i<=n) i++;//2
		ans++;//一段完了多一个答案
	}
	printf("%d",ans-2);//最开始与最后都算了所以减掉
    return 0;
}