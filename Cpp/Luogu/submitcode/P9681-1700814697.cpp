#include<bits/stdc++.h>
#define int long long
using namespace std; 

int n,q;
int a[200005];//输入数列
int f_ans[200005];
//f_ans 前缀和数组，记录 i 之前合法区间与包含 i 的区间数量之和
int dis[200005];
//dis 记录包含 i 的区间 且区间右端点不为 i 的区间的数量之和
int id[200005];//id 记录这个点所处的块的编号
int tot;//编号（可能不连续）

signed main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	//输入
	for(int i=1;i<=n;i++)
	{
		f_ans[i]=f_ans[i-1];//统计方案前缀和
		id[i]=++tot;//赋予编号
		if(a[i]<=0) continue;
		//这个点不能作为区间 [x,r] 的右端点(a[r]<=0)
		//继续循环
		
		int p=i-1,nw=a[i];
		//枚举区间左端点 p，nw 记录区间 [p,r] 的和
		while(p>=1&&a[p]<=0&&nw+a[p]>0) nw+=a[p--];
		//左端点若还可以移动就移动
		for(int j=p+1,k=1;j<=i;j++,k++) f_ans[j]+=k,dis[j]+=k,id[j]=tot;
		//更新前缀和数组，dis，区间编号
		dis[i]=0;//不记录右端点为 i 的情况
		//dis 记录包含 i 的区间 且区间右端点不为 i 的区间的数量之和
	}
	
	while(q--)
	{
		int l,r;
		cin>>l>>r;
		if(id[l]==id[r]&&a[r]<=0) cout<<0<<'\n';
		//l，r 同属一个区间且 r 不能作为右端点，答案为 0
		
		else if(id[l]!=id[r]&&a[r]<=0) cout<<f_ans[r]-f_ans[l-1]-dis[r]<<'\n';
		//l，r 不属于同一个区间且 r 不可作为 r 所属区间的右端点，
		//因为前缀和 f_ans 记录了包含 r 的区间，但 r 不能作为 r 所属区间的右端点
		//所以前缀和相减后还要减掉 dis[r]（可能有些难懂）
		
		else cout<<f_ans[r]-f_ans[l-1]<<'\n';
		//反之：
		//1: l，r 同属一个区间且 r 是右端点
		//2: l，r 不属于同一个区间且 r 可以作为 r 所属区间的右端点
		//前缀和直接相减即可
	}
	
	return 0;
}