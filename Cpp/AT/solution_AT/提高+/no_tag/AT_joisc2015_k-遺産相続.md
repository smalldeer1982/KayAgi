# 遺産相続

## 题目描述

## JOISC2015 Day4T1 遗产继承


给定一个$N$个点、$M$条边的无向图，每条边有权值，任意两条边的权值不同。图上保证没有自环，但是可能有重边。每条边有一个标记值，初始每条边的标记值均为$0$。

接下来对这个图进行$K$次操作，第$i$次操作时执行如下操作：在图中选择一个边的集合，满足：

1、其包含的所有边的标记值都是$0$；

2、不存在任何非空子集满足这个子集在图上构成环；

3、选择的集合中所有边的权值之和是当前所有可能的选择方案中权值和最大的选择方案；

然后将这些边的标记值赋为$i$。

求$K$次操作完成之后每一条边的标记值。

## 说明/提示

$1 \leq N \leq 1000$；

$1 \leq M \leq 300000$；

$1 \leq K \leq 10000$；

$1 \leq A_i , B_i \leq N , A_i \neq B_i$；

$1 \leq C_i \leq 10^9 , \forall i \neq j , C_i \neq C_j$；

# 题解

## 作者：EuphoricStar (赞：2)

## 题意

有一个 $ N $ 个点 $ M $ 条边的无向图。第 $ i $ 条边连接 $ A_i $ 和 $ B_i $，边权为 $ C_i $，保证 $ C_i $ 互不相同。

现在有 $ K $ 个人，依次从 $ 1 $ 到 $ K $ 编号。第 $ 1 $ 个人先操作，会删掉图里一个边权和最大生成森林。然后是第 $ 2 $ 个人，会删掉剩下图里一个边权和最大生成森林。依次类推，接下来是第 $ 3 $ 个人，第 $ 4 $ 个人，……，直到第 $ K $ 个人。对于每条边，你需要求出它是被哪个人删掉的。

## 思路

首先将所有边从大到小排序，并且维护 $K$ 个并查集，代表第 $i$ 个人选的生成森林。然后遍历排序后的边，记为 $(u,v)$。显然把这条边删掉的人的编号就是满足 $(u,v)$ 在第 $i$ 个并查集不连通的最小 $i$。

直接做是 $O(MK \log n)$ 的（并查集带一个 $\log$），考虑优化。

可以证明 $(u,v)$ 在编号为 $1 \sim K$ 的并查集中的连通情况具有单调性，即有一段是连通的，有一段是不连通的。因此可以直接二分，找到 $(u,v)$ 不连通的最小编号，然后连边即可。时空复杂度与线段树方法相同。

时间复杂度 $O(NK + M \log N \log K)$，空间复杂度 $O(NK)$。

## 代码

[code](https://atcoder.jp/contests/joisc2015/submissions/32583809)

---

## 作者：Imaginative (赞：2)

# 题意
有一个 $N$ 个点 $M$ 条边的无向图。第 $i$ 条边连接 $A_i$ 和 $B_i$，边权为 $C_i$。现在有 $k$ 次操作，每次操作会删掉图里一个边权和最大生成森林，直到删完。问这 $M$ 条边分别是第几轮被删除的。
# 想法
- 考虑暴力，直接模拟 $K$ 轮的时间复杂度是 $O(KM)$ 的，因为每条边都可能被检查 $K$ 次才被删除。
- 考虑到操作上实际在为边分类，这提供给我们并查集的想法。
1.   定义联通关系为图上顶点集合的划分，用并查集维护集合内点两两联通，最终我们要维护 $K$ 个并查集。
2.   按边权从大到小检查每条边 $e$,每次找到第一个不成环的一组并查集 $d_j$，并将 $e$ 合并进去。
   
但如果暴力枚举每一个并查集和边，时间将退化成暴力，考虑优化。

**优化结论：** $d_1 \dots d_k$ 联通强度单调不增，即 $d_i$ 的联通关系可由 $d_{i+1}$ 中加若干条边获得。

**证明：** 加入边 $e$，假设 $d_{i+1}$ 是能满足要求合并 $e$ 的集合，且加入后 $d_i$ 的联通强度不再不弱于 $d_{i+1}$,那么 $e$ 必定能联通 $d_i$ 中的两个连通块，矛盾。

根据结论，得到其具有单调性，用二分优化即可，时间复杂度 $O(M \log M + M \log K +KN)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+5;
int n,m,k;
struct node{
	int u,v,w,id;
	friend bool operator<(node x,node y){
		return x.w>y.w;
	}
}op[N];
int res[N],f[2050][10050];
int find(int x,int id){
	return f[x][id]==x?x:f[x][id]=find(f[x][id],id);
}
void un(int x,int y,int id){
	int u=find(x,id),v=find(y,id);
	if(u!=v) f[u][id]=v;
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			f[i][j]=i;
		}
	}
	for(int i=1;i<=m;i++){
		cin>>op[i].u>>op[i].v>>op[i].w;
		op[i].id=i;
	}
	sort(op+1,op+m+1);
	for(int i=1;i<=m;i++){
		int u=op[i].u,v=op[i].v;
		int l=1,r=k,rs=0;
		while(l<=r){
			int mid=(l+r)>>1;
			int fu=find(u,mid),fv=find(v,mid);
			if(fu==fv) l=mid+1;
			else r=mid-1,rs=mid;
		}
		if(rs){
			un(u,v,rs);
			res[op[i].id]=rs;
		} 
	}
	for(int i=1;i<=m;i++) cout<<res[i]<<endl;
	return 0;
}
```

---

## 作者：LeBao2023 (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_joisc2015_k)

### 简要题意

有一个 $N$ 个点 $M$ 条边的无向图。第 $i$ 条边连接 $A_i$ 和 $B_i$，边权为 $C_i$，保证 $C_i$互不相同。

现在有 $K$ 个人，依次从 $1$ 到 $K$ 编号。第 $1$ 个人先操作，会删掉图里一个边权和最大生成森林。每个人都这样做，直到第 $K$ 个人。对于每条边，你需要求出它是被哪个人删掉的。

### 思路

考虑贪心，我们可以依次从最大边开始删，看第几个人可以加上这条边，取编号最小的，时间复杂度 $O(NK+M\log M+MK\log N)$，$\log N$ 是并查集的时间，不能通过。

考虑优化，在一个 $1$ 到 $K$ 中找最小的可以加的集合，猜测可以使用二分，现在要证明连通性有单调性，即一个集合可以加入这条边，编号比它小的集合也可以，故加入之后也满足单调性。

证明：

1. 开始时，一条边都没有，易证有单调性。

2. 当每加入一条边时，若原来的集有单调性，则新加入的一条边会在第一个可以加的地方加入，加入以后，被加入的集合满足编号比它小的集合也可以，故加入之后也满足单调性。

3. 故所有的时候都满足单调性，可以二分。

时间复杂度：$O(NK+M\log M+M\log K\log N)$。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxm=3e5+5;
const int maxn=1005;
const int maxk=1e4+5;
struct edge
{
	int a,b,w,id,ans;
}e[maxm];
bool cmp(edge a,edge b)
{
	return a.w>b.w;
}
int fa[maxn][maxk];
int find(int x,int id)
{
	return fa[x][id]==x?x:fa[x][id]=find(fa[x][id],id);
}
void join(int x,int y,int id)
{
	int xx=find(x,id),yy=find(y,id);
	if(xx!=yy)
	{
		fa[xx][id]=yy;
	}
}
int n,m,k,ans[maxm];
signed main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=k+1;j++)
		{
			fa[i][j]=i;
		}
	}
	for(int i=1;i<=m;i++)
	{
		cin>>e[i].a>>e[i].b>>e[i].w;
		e[i].id=i; 
	}
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		int l=1,r=k+1;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(find(e[i].a,mid)!=find(e[i].b,mid))
			{
				r=mid;
			}
			else
			{
				l=mid+1;
			}
		}
		if(l==k+1)
		{
			e[i].ans=0;
			continue;
		}
		join(e[i].a,e[i].b,l);
		e[i].ans=l;
	}
	for(int i=1;i<=m;i++)
	{
		ans[e[i].id]=e[i].ans;
	}
	for(int i=1;i<=m;i++)
	{
		cout<<ans[i]<<'\n';
	}
}
```

---

