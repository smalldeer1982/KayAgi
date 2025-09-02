# 占领新区域 Conquer a New Region

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4539

[PDF](https://uva.onlinejudge.org/external/16/p1664.pdf)

## 样例 #1

### 输入

```
4
1 2 2
2 4 1
2 3 1
4
1 2 1
2 4 1
2 3 1```

### 输出

```
4
3```

# 题解

## 作者：亦阳 (赞：6)

**思路： 参考Kruskal算法的思路，首先初始化并查集，维护每个点的元素个数和中心点到其他点的容量之和，按照边权的大小从大到小排序，然后每次选最大的边，判断两个点，把它加到并查集，并每次优化两个点到另一个的值是多少，将集合更新为大的（相当于让尽可能多的点通过这个大的边）所有点遍历完成之后,答案就是树的根节点 。 具体见代码。**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=200000+4;
typedef long long LL;
struct Edge
{
	int from,to,weight;
}edges[MAXN];
int fa[MAXN], num[MAXN], n;
LL sum[MAXN], ans;
int find(int x)//并查集
{
	if (fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
bool cmp(Edge a, Edge b)//sort函数结构体排序
{
	return a.weight > b.weight;
}
int main()
{
	int N;
	while (scanf("%d",&N)==1 && N)
	{
		for (int i= 1 ;i < N ; i++)
		{
			scanf("%d%d%d",&edges[i].from,&edges[i].to,&edges[i].weight);
		}
		sort(edges+1,edges+N,cmp);
		for (int i = 1; i <= N; i++)//初始化
		{
			fa[i] = i;
			num[i] = 1;//每个点的元素个数
			sum[i] = 0;//中心点到其他点的容量之和
		}
		for (int i = 1; i < N ; i++)//合并，更新容量和点集大小
		{
			
			int a = find(edges[i].from);
			int b = find(edges[i].to);
			int w = edges[i].weight;
			LL f1 = sum[a] + num[b] * w;//以b为中心点
			LL f2 = sum[b] + num[a] * w;//以a为中心点
			if (f1 > f2)
			{
				fa[b] = a;
				num[a] += num[b];
				sum[a] = f1;
			}
			else
			{
				fa[a] = b;
				num[b] += num[a];
				sum[b] = f2;
			}
		}
		printf("%lld\n",sum[find(1)]); //所有的点遍历完成后，所求的点即为树的根
	}	
	return 0;
}
```

---

## 作者：reyik (赞：3)

我们把所有的边从大到小排序，这样每次遍历到一个边，肯定由一个连通块的最小值要被更新

假设这个边连接着x,y联通块，我们要判断哪一个连通块去更新

我们记录每一个连通块的大小$sz$和当前连通块的答案$sum$

那么如果我们要y联通块走这条路，那么合并以后的答案是$sum[x]+sz[y]*$这条边的权值，因为，我们是从大到小排序的，所以这条边对于y联通块内的所有点肯定是目前为止的最小值

然后如果要x联通块的点走这条路，那么合并以后的答案是$sum[y]+sz[x]*$这条边的权值，因为题目要求答案最大，所以我们看哪个大来决定$x$合并到$y$还是$y$合并到$x$

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int inf=2e9;
const int N=400005;
struct edge {
  int x,y,v;
}e[N];
int n,sz[N],fa[N];
long long sum[N];
bool cmp(edge a,edge b) {
  return a.v>b.v;
}
int finds(int x) {
  if(x==fa[x]) return fa[x];
  fa[x]=finds(fa[x]);
  return fa[x];
}
int main() {
  while(scanf("%d",&n)!=EOF) {
    for (int i=0;i<=n;++i) {
      sz[i]=1;
      fa[i]=i;
    }
    memset(sum,0,sizeof(sum));
    for (int i=1;i<n;++i) {
      scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].v);
    }
    sort(e+1,e+n,cmp);
    for (int i=1;i<n;++i) {
      int fx=finds(e[i].x),fy=finds(e[i].y);
      long long a=sum[fx]+1ll*sz[fy]*e[i].v;
      long long b=sum[fy]+1ll*sz[fx]*e[i].v;
      if(a>=b) {
        fa[fy]=fx;
        sum[fx]=a;
        sz[fx]+=sz[fy];
      }
      else {
        fa[fx]=fy;
        sum[fy]=b;
        sz[fy]+=sz[fx];
      }
    }
    printf("%lld\n",sum[finds(1)]);
  }
  return 0;
}
```

---

## 作者：Huang_Yuhan (赞：2)

# [题目描述]

给你一棵有$n$个节点的树，定义$dis(x,y)$为$x$到$y$这条路径上长度最小的边。让你找一个点$s$，使得$\sum_{i}^ndis(s,i)$最大.

$1\leqslant  n\leqslant 200000$

# 解：

我们首先可以手动模拟一个贪心策略。

先找到整棵树中权值最小的边$len$，这条边一定把原树分成了另外两棵树，假设为$A,B$

假设在$A$这棵树原问题的答案为$ans[A]$,$A$这棵树的节点个数为$cnt[A]$

类似于$dp$

$$ans=\max\{ans[A]+cnt[B]\times len,ans[B]+cnt[A]\times len\}$$

然后我们再递归去算$ans[A]$与$ans[B]$.

但是这样的策略在程序中很难实现，我们需要想另外的方法。

我们发现，当$len$这条边被讨论的时候，所有大于$len$的边一定是被讨论过的。

所以讨论顺序一定是从大到小的。

所以我们对边从大到小排序。

然后对两个端点进行合并。

时间复杂度为$O(nlog_2n+n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200000+5;
int fa[maxn];
long long cnt[maxn],ans[maxn];
struct P
{
	int a,b,c;
}edge[maxn];
bool cmp(P x,P y)
{return x.c>y.c;}
int getfa(int v)
{return v==fa[v]?v:fa[v]=getfa(fa[v]);}
int main()
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{
		for(int i=1;i<n;i++)scanf("%d%d%d",&edge[i].a,&edge[i].b,&edge[i].c),fa[i]=i,cnt[i]=1,ans[i]=0;
		fa[n]=n;cnt[n]=1;ans[n]=0;
		sort(edge+1,edge+n,cmp);
		for(int i=1;i<n;i++)
		{
			int fx=getfa(edge[i].a);
			int fy=getfa(edge[i].b);
			if(fx!=fy)
			{
				if(ans[fy]+cnt[fx]*edge[i].c>ans[fx]+cnt[fy]*edge[i].c)swap(fx,fy);
				ans[fx]+=cnt[fy]*edge[i].c;
				fa[fy]=fx;
				cnt[fx]+=cnt[fy];
			}
		}
		printf("%lld\n",ans[getfa(1)]);
	}
}
```

---

## 作者：Jadonyzx (赞：0)

像克鲁斯卡尔那样跑并查集，用 $sum_i$ 表示以 $i$ 号连通块中的某个点为中心的最优解，转移方程如下:

$sum_i=sum_i+siz_j\times w$ 其中 $w$ 为当前边权

code:


```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 200005
using namespace std;
int n,fa[maxn],siz[maxn],ans,sum[maxn];
struct EDGE{int u,v,w;}edge[maxn];
bool cmp(EDGE aaa,EDGE bbb){return aaa.w<bbb.w;}
int find(int i){
	if(i==fa[i])return i;
	fa[i]=find(fa[i]);
	return fa[i];
}
void merge(int u,int v,int w){
	u=find(u);v=find(v);
	if(u==v)return;
	int uva=sum[u]+siz[v]*w;
	int noi=sum[v]+siz[u]*w;
	if(uva>noi){
		fa[v]=u;
		siz[u]+=siz[v];
		sum[u]=uva;
	}
	else{
		fa[u]=v;
		siz[v]+=siz[u];
		sum[v]=noi;
	}
	return;
}
signed main(){
	while(cin>>n){
		for(int i=1;i<=n;++i)fa[i]=i,siz[i]=1,sum[i]=0;
		for(int i=1;i<n;++i)
			cin>>edge[i].u>>edge[i].v>>edge[i].w;
		sort(edge+1,edge+n,cmp);reverse(edge+1,edge+n);
		for(int i=1;i<n;++i){
			int uu=edge[i].u,vv=edge[i].v;
			merge(uu,vv,edge[i].w);
		}
		cout<<sum[find(1)]<<'\n';
	}
	return 0;
}
```

---

