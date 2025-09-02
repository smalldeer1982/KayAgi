# Parsa's Humongous Tree

## 题目描述

Parsa has a humongous tree on $ n $ vertices.

On each vertex $ v $ he has written two integers $ l_v $ and $ r_v $ .

To make Parsa's tree look even more majestic, Nima wants to assign a number $ a_v $ ( $ l_v \le a_v \le r_v $ ) to each vertex $ v $ such that the beauty of Parsa's tree is maximized.

Nima's sense of the beauty is rather bizarre. He defines the beauty of the tree as the sum of $ |a_u - a_v| $ over all edges $ (u, v) $ of the tree.

Since Parsa's tree is too large, Nima can't maximize its beauty on his own. Your task is to find the maximum possible beauty for Parsa's tree.

## 说明/提示

The trees in the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528A/7830790d968daee501b061b313ebb6586c6b6ca7.png)In the first test case, one possible assignment is $ a = \{1, 8\} $ which results in $ |1 - 8| = 7 $ .

In the second test case, one of the possible assignments is $ a = \{1, 5, 9\} $ which results in a beauty of $ |1 - 5| + |5 - 9| = 8 $

## 样例 #1

### 输入

```
3
2
1 6
3 8
1 2
3
1 3
4 6
7 9
1 2
2 3
6
3 14
12 20
12 19
2 12
10 17
3 17
3 2
6 5
1 5
2 6
4 6```

### 输出

```
7
8
62```

# 题解

## 作者：Forever1507 (赞：8)

~~从题目描述和 CF 的风格明显看出这是个树形动态规划吧~~

好了步入正题，很显然每个节点的点权都要是边界才能取得最大值，这个就不用证明了吧。

所有树形动规都有一个基本状态: $dp[i]$ 表示以 $i$ 为根节点的子树所求答案的最大值，但是这样是明显无法得到状态转移方程的，因为我们缺少一个至关重要的条件：这个节点到底取哪一个最值呢？

显然，我们可以在原有的状态上加一个维度： $dp[i][0/1]$ 表示以 $i$ 为根节点的子树中，$i$ 节点选择 $l[i] / r[i]$ 时答案的最大值。

那么，状态转移方程就是：

$dp[cur][0]+=max(dp[son][0]+abs(l[cur]-l[son]),dp[son][1]+abs(l[cur]-r[son]));$

$dp[cur][1]+=max(dp[son][0]+abs(r[cur]-l[son]),dp[son][1]+abs(r[cur]-r[son]));$

需要注意的几个点：
- 没有根节点，边也没有确定始末，所以要建双向边。
- 递归中要记父亲节点，不然会死循环。
代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,dp[200005][2],l[200005],r[200005];
vector<int>v1[200005];
void dfs(int cur,int fa){
	for(int i=0;i<v1[cur].size();i++){
		int son=v1[cur][i];
		if(fa==son)continue;
		dfs(son,cur);
		dp[cur][0]+=max(dp[son][0]+abs(l[cur]-l[son]),dp[son][1]+abs(l[cur]-r[son]));
		dp[cur][1]+=max(dp[son][0]+abs(r[cur]-l[son]),dp[son][1]+abs(r[cur]-r[son]));
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=n;i++)v1[i].clear();
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>l[i]>>r[i];
		}
		for(int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			v1[u].push_back(v);
			v1[v].push_back(u);
		}
		dfs(1,0);
		cout<<max(dp[1][0],dp[1][1])<<'\n';
	}
}
```


---

## 作者：iMya_nlgau (赞：4)

### 题目大意

给你一棵树，每个节点 $v$ 有两个值 $l_v,r_v$，让你对每个点确定一个 $a_v$ ($l_v\leq a_v\leq r_v$) 最大化 $\sum\limits_{(u,v)\in E} |a_u-a_v|$ （$E$ 为边集），输出最大值。

### 思路

**性质：** 对与每个节点 $v$，都有 $a_v=l_v$ 或 $a_v=r_v$。

根据货仓选址的经典结论，对于每个点 $v$, $\sum\limits_{(u,v)\in E} |a_u-a_v|$ 是关于 $a_v$ 的凸函数，所以只能在 $l_v$ 或 $r_v$ 取得最大值。

然后 DP 即可，设 $f_{i,0}$ 表示 $a_i=l_i$ 时 $i$ 子树内的最大值，$f_{i,1}$ 表示 $a_i=r_i$ 时 $i$ 子树内的最大值。则有转移

$$f_{x,0}=\sum\limits_{y\in son(x)}\max\{f_{y,0}+|l_x-l_y|,f_{y,1}+|l_x-r_y|\}$$
$$f_{x,1}=\sum\limits_{y\in son(x)}\max\{f_{y,0}+|r_x-l_y|,f_{y,1}+|r_x-r_y|\}$$

答案即为 $\max\{f_{1,0},f_{1,1}\}$。

[代码实现](https://www.luogu.com.cn/paste/dkgxtkrn)

---

## 作者：mazy (赞：1)

## 题目大意：

给出一棵有 $n$ 个节点的树，每个节点上有两个整数 $l_v$ 和 $r_v$ , 现在要给每一个节点赋一个权值 $a_v$ 满足 $l_v\leq a_v \leq r_v$ ,并最大化 $\sum_{(u,v)\in E} |a_u-a_v|$ 

## 做法：
首先我们可以用调整法证明，对于一条边 $(u,v)\in E $ , $a_u$ 的最佳取值一定在 $L_u$ 或 $R_u$ 中，那么我们不需要考虑整个区间 $[L_u,R_u]$ ,而只需要考虑 $a_u$ 取两个端点中的一个即可

![调整法证明](https://cdn.luogu.com.cn/upload/image_hosting/eul2ju5q.png)
有了这一步作基础，观察数据范围，发现 $\sum n\leq 2\times 10^5$ ,考虑树形DP：
设 $dp[x][0/1]$ 表示选x的左/右端点,在x的子树中获得的最大beauty值。那么我们可以开始进行树形dp的转移。

依题意转移，有：
$$
    dp[x][0]+=max(dp[v][0]+|L[x]-L[v]|,dp[v][1]+|L[x]-R[v]|)
$$
$$
    dp[x][1]+=max(dp[v][1]+|R[x]-R[v]|,dp[v][0]+|R[x]-L[v]|)
$$


## 对于一些小问题

加无向边是因为输入数据中，根是不确定的。若加单向边就可能不能从父亲走到儿子。为了简单起见加无向边。

最后上代码

```cpp

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int INF = 0x3f3f3f3f;
const int MAXN= (int)2e5+7;

inline ll read()
{
	ll x=0;int f=1;char ch=getchar();
	while(ch<48||ch>57)		{if(ch=='-') f=-1;ch=getchar();}
	while(ch>=48&&ch<=57)	x=x*10+ch-48,ch=getchar();
	return x*f;
}

int n,head[MAXN],ecnt;
ll L[MAXN],R[MAXN],dp[MAXN][2];
bool vis[MAXN];

struct Edge {int nxt,to;};
Edge edge[MAXN];

inline void add_edge(int u,int v)
{
	edge[++ecnt].nxt=head[u];
	edge[ecnt].to=v;
	head[u]=ecnt;
}

void dfs(int x,int fa)
{
	dp[x][0]=dp[x][1]=0;
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int &v=edge[i].to;
		if(v==fa)		continue;
		dfs(v,x);
		dp[x][0]+=max(dp[v][0]+abs(L[x]-L[v]),dp[v][1]+abs(L[x]-R[v]));
		dp[x][1]+=max(dp[v][1]+abs(R[x]-R[v]),dp[v][0]+abs(R[x]-L[v]));
	}
}

signed main()
{
	int tc=read();
	while(tc--)
	{
		n=read();
		for(int i=1;i<=n;i++)	L[i]=read(),R[i]=read();
		
		memset(dp,0,sizeof(dp));
		memset(vis,0,sizeof(vis));
		memset(head,0,sizeof(head));
		ecnt=0;
		
		for(int i=1;i<n;i++)
		{
			int uu=read(),vv=read();
			add_edge(uu,vv);
			add_edge(vv,uu);
		}
		dfs(1,0);
		printf("%lld\n",max(dp[1][0],dp[1][1]));
	}
	return 0;
}
```

---

## 作者：_lbw_ (赞：1)

首先我们发现肯定得逐个节点考虑。

我们假设已经固定了其他结点的值，还剩 $i$ 号点。

这时把与这个点相邻的所有点权值放在一个数轴上看，肯定离权值中位数越远越好。

发现不论如何，选 $l_i$ 或 $r_i$ 可以权值中位数最远。

于是只要考虑选 $l_i$ 或 $r_i$。

记下当前点选哪个，树形 dp 一下就可。

码：

```cpp
ll T,n,csp,first[maxn],dp[maxn][2],l[maxn],r[maxn];
struct edge{
	ll to,nxt;
}e[2*maxn];
void add(ll u,ll v){
	e[++csp]=edge{v,first[u]};
	first[u]=csp;
}
void dfs(ll now,ll fa){
	for(int i=first[now];i;i=e[i].nxt){
		ll v=e[i].to;
		if(v==fa)continue;
		dfs(v,now);
		dp[now][0]+=max(dp[v][0]+abs(l[now]-l[v]),dp[v][1]+abs(l[now]-r[v]));
		dp[now][1]+=max(dp[v][0]+abs(r[now]-l[v]),dp[v][1]+abs(r[now]-r[v]));
	}
}
int main(){
	T=read();
	while(T--){
		n=read();csp=0;
		F(i,1,n)first[i]=0,dp[i][0]=dp[i][1]=0;
		F(i,1,n)l[i]=read(),r[i]=read();
		F(i,2,n){
			ll u=read(),v=read();
			add(u,v);add(v,u);
		}
		dfs(1,0);
		cout<<max(dp[1][0],dp[1][1])<<endl;
	}
	return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：0)

真的水，不知道为什么成了 Div2 赛时的分水岭。           

我们考虑最终选出来的数，显然对于任意点如果没取到一个点的极值答案是不会最优的。            

于是 DP 一下每个点是选极大值还是极小值就好了。         
```cpp
#include "bits/stdc++.h"
using namespace std;//因为如果不取到峰值，那么我们的答案必定不是最优 
const int Len = 1e5 + 5;
#define int long long
int n,m,head[Len],cnt,L[Len],R[Len],DP[Len][2];
inline int Iabs(int x){return x < 0 ? -x : x;}
struct node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
void dfs(int x,int f)
{
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		dfs(to , x);
		DP[x][0] += max(Iabs(L[x] - L[to]) + DP[to][0] , Iabs(L[x] - R[to]) + DP[to][1]);
		DP[x][1] += max(Iabs(R[x] - L[to]) + DP[to][0] , Iabs(R[x] - R[to]) + DP[to][1]);
	}
}
signed main()
{
	int t;scanf("%lld",&t);
	while(t --)
	{
		memset(head , 0 , sizeof head) ; cnt = 0;
		memset(DP , 0 , sizeof DP);
		scanf("%lld",&n);
		for(int i = 1 ; i <= n ; i ++) scanf("%lld %lld",&L[i],&R[i]);
		for(int i = 1 ; i < n ; i ++)
		{
			int x,y;scanf("%lld %lld",&x,&y);
			add(x , y) , add(y , x); 
		}
		dfs(1 , 0);
		printf("%lld\n",max(DP[1][0] , DP[1][1]));
	}
	return 0;
}
```

---

