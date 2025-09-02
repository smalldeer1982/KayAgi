# Royal Questions

## 题目描述

In a medieval kingdom, the economic crisis is raging. Milk drops fall, Economic indicators are deteriorating every day, money from the treasury disappear. To remedy the situation, King Charles Sunnyface decided make his $ n $ sons-princes marry the brides with as big dowry as possible.

In search of candidates, the king asked neighboring kingdoms, and after a while several delegations arrived with $ m $ unmarried princesses. Receiving guests, Karl learned that the dowry of the $ i $ th princess is $ w_{i} $ of golden coins.

Although the action takes place in the Middle Ages, progressive ideas are widespread in society, according to which no one can force a princess to marry a prince whom she does not like. Therefore, each princess has an opportunity to choose two princes, for each of which she is ready to become a wife. The princes were less fortunate, they will obey the will of their father in the matter of choosing a bride.

Knowing the value of the dowry and the preferences of each princess, Charles wants to play weddings in such a way that the total dowry of the brides of all his sons would be as great as possible. At the same time to marry all the princes or princesses is not necessary. Each prince can marry no more than one princess, and vice versa, each princess can marry no more than one prince.

Help the king to organize the marriage of his sons in the most profitable way for the treasury.

## 样例 #1

### 输入

```
2 3
1 2 5
1 2 1
2 1 10
```

### 输出

```
15```

## 样例 #2

### 输入

```
3 2
1 2 10
3 2 20
```

### 输出

```
30```

# 题解

## 作者：cunzai_zsy0531 (赞：8)

## CF875F 题解 --by cunzai_zsy0531

题目链接 [Link](https://www.luogu.com.cn/problem/CF875F)

首先我们考虑建边，如果我们把某一个公主的两个潜在丈夫连一条边，边权为 $w_i$，如果选了某一条边，就相当于是选了一个公主。

接下来我们考虑什么情况下我们的选边是合法的。首先考虑树的情况，如果我们选择了 $k$ 条边连接了 $k+1$ 个顶点，那么我们可以舍弃一个点（一个王子），那么剩下 $k$ 个王子可以完全匹配这 $k$ 个公主。

那么我们继续思考，如果在这棵树中增加一条边呢？这样是 $k+1$ 个王子和 $k+1$ 个公主，那么他们能够完全匹配吗？答案是肯定的。对于这样一棵基环树（就是上面讲的点数$=$边数的东西），我们把其中唯一的那个环作为根节点，因为这个环中，王子和公主可以匹配，所以我们把它看成根节点，剩下的边（公主）都和儿子点（王子）匹配，这样就可以完成了。

我们可以使用 $Kruskal$ 算法解决这个问题（可以理解为边权和最大的基环树或树组成的森林）。我们在普通的 $Kruskal$ 的基础上再定义一个数组 $d_i$ 表示以 $i$ 为代表元的集合是否是一个基环树，$1$ 表示无环， $0$ 表示是一个基环树。显然，两个树可以合成一个树，一个树和一个基环树可以合成一个基环树。

我们设$x=find(e[i].u)$，$y=find(e[i].v)$，其中 $find()$ 表示并查集的代表元。分两种情况讨论：

1. 若 $x \neq y$，那么如果 $d[x]\ or\ d[y] =1$，说明 $x$ 和 $y$，至少有一个不是基环树，可以合成一棵树或基环树。那么我们加上这条边的边权（公主的嫁妆）。这时我们还要更新新树的$d=d[x]\ and\ d[y]$，大家稍微思考一下即可。

2. 若 $x=y$，那么 $d[x]$ 只能等于$0$，即树，加一条边成为了基环树，$d[x]$ 变为 $1$ 。

这样我们就可以使用修改版的 $Kruskal$ 通过此题。

# Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
inline void read(int &t){
	int res=0,flag=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-') flag=-1;c=getchar();}
	while(isdigit(c)) res=res*10+c-'0',c=getchar();
	t=res*flag;
}
const int N=2e5+13;
struct Edge{
	int u,v,w;
	bool operator <(const Edge &a)const{return w>a.w;}
}e[N];
int fa[N],d[N],n,m,sum;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
	read(n),read(m);
	for(int i=1;i<=n;++i) fa[i]=i,d[i]=1;
	for(int i=1;i<=m;++i) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	sort(e+1,e+m+1);//别忘了Kruskal是基于贪心思想，要排序。
    //下面就是修改后的Kruskal
	for(int i=1;i<=m;++i){
		int x=find(e[i].u),y=find(e[i].v);
		if(x!=y&&(d[x]||d[y])) fa[x]=y,sum+=e[i].w,d[y]=d[x]&d[y];//第一种情况
		else if(x==y&&d[x]) d[x]=0,sum+=e[i].w;//第二种情况
	}
	printf("%d\n",sum);//最终的答案就是累加的那些边权
	return 0;
}
```

## 谢谢各位！

---

## 作者：hegm (赞：6)

### [Royal Questions](https://www.luogu.com.cn/problem/CF875F)

逆天题，遇见一道比赛题目过来的，本质上是最大权值基环森林。

但是看到这道题目的时候懵逼了，这道题目和最大权值生成基环森林有什么关系。

还是在看到输入的格式后才反应过来。

首先转化题意，即“最大权值生成基环森林”。

容易发现对于每一个公主，连接两个王子 $u,v$，边权为 $w$。

那么会形成一张无向图，由于目的是选择一个王子和一个公主匹配，权值为 $w$，所以容易发现可以转化为：对每个点选择至多一条出边，问边权和最大是多少。

由于每个节点最多一条出边，所以形成的图一定是基环树。又因为没有要求连通性，所以是基环森林。

因此转化为最大权值基环森林，考虑如何求最大权值基环森林。

考虑 $\text{Kruskal}$ 的过程，我们知道 $\text{Kruskal}$ 的本质是按照权值顺序枚举每一条边，看能否加入到生成树内。

所以考虑修改一下，对于每一个并查集，同时维护此并查集的点集组成的是树还是基环树。

对于一条边，如果他连接的两个联通快内至少有一个是树，那么可以连接。如果他连接的两点属于同一个联通快，那么只有当前联通快是树才可以，此时会从树变为基环树。

```cpp
#include<bits/stdc++.h>
#define N 200005
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,vis[N],s[N],a[N],fa[N],ans;
map<int,bool> mp[N];
struct edge
{
	int u,v,w;
}k[N*2];int tot;
bool cmp2(edge x,edge y)
{
	return x.w>y.w;
}
int find(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
signed main()
{
//	freopen("contact.in","r",stdin);
//	freopen("contact.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		k[i].u=read();
		k[i].v=read();
		k[i].w=read();
	}
	sort(k+1,k+1+m,cmp2);
	for(int i=1;i<=n;i++)fa[i]=i,vis[i]=1;
	for(int i=1,u,v;i<=m;i++)
	{
		u=k[i].u,v=k[i].v;
		if(find(u)!=find(v)&&(vis[fa[u]]|vis[fa[v]]))
		{
			ans+=k[i].w;
			vis[fa[u]]&=vis[fa[v]];
			fa[fa[v]]=fa[u];
		}
		else if(fa[u]==fa[v]&&vis[fa[u]])
		{
			vis[fa[u]]=0;
			ans+=k[i].w;
		}
	}
	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：ql12345 (赞：5)

[洛谷传送门](https://www.luogu.com.cn/problem/CF875F) [CF传送门](https://codeforces.com/problemset/problem/875/F)

### 前言

模拟赛考了这题，都想的最大生成基环树森林，所以都假了，网络流可做

### Solution：

#### Part 1 ： 为什么错

先提供一组hack数据
```cpp
6 7
1 2 10000
2 3 10000
1 3 10000
4 5 10000
5 6 10000
4 6 10000
1 4 1
```
解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/4z1ouwlo.png)

应该是选两个环，但最大生成基环树森林为少选一条环上的边，答案变小 ~~（我自己写法丑，全选）~~

#### Part 2 ： 怎么改

说一下我是怎么改的，我原来的代码：

```cpp
n = read(), m = read();
for (int i = 1; i <= m; ++i) {
    int a = read(), b = read(), c = read();
    e[i] = {a, b, c};
}
sort(e + 1, e + m + 1);
for (int i = 1; i <= n + m; ++i) fa[i] = i;
for (int i = 1; i <= m; ++i) {
    int a = find(e[i].a), b = find(e[i].b), c = e[i].c;
    if (a != b) ans += c, fa[min(a, b)] = max(a, b);
    else if (a <= n) ans += c, fa[a] = n + i;
}
```

含义：一个连通块如果已经多加了一条边，用多加的一条边作为并查集的代表元素（但这不重要，重要的是我下面怎么改）

观察到有可能a>n && b>n && a!=b，这时就会在两个环中加一条边，答案肯定变大，也不合法，因此可以判一下a和b是否全大于n（但这样还是错的）

考虑上面说到的为什么是错的，不难发现，跑最大生成树的时候最优策略为：碰到一条边，能加就加，不用同一个树内就不加了

于是判断能不能加一条边就好了，不能加当且仅当：

- 两端为两个基环树

- 两端为同一个基环树

用vis标记一个并查集是不是基环树即可

#### Code：

```cpp
n = read(), m = read();
for (int i = 1; i <= m; ++i) {
    int a = read(), b = read(), c = read();
    e[i] = {a, b, c};
}
sort(e + 1, e + m + 1);
for (int i = 0; i <= n + m + 1; ++i) fa[i] = i;
for (int i = 1; i <= m; ++i) {
    int a = find(e[i].a), b = find(e[i].b), c = e[i].c;
    if (a == b) {
    	if (! vis[a])
    		vis[a] = 1, ans += c;
	}
	else {
		if (! vis[a] && ! vis[b])
			fa[a] = b, ans += c;
		else if (vis[a]) {
			if (! vis[b])
				fa[b] = a, ans += c;
		}
		else {
			fa[a] = b, ans += c;
		}
	}
}
```

---

## 作者：lotus_grow (赞：5)

题意

有 $n$ 个王子和 $m$ 个公主。每个公主有两个喜欢的王子，编号分别为 $a_{i}$ , $b_{i}$，但一个王子只能娶一个公主（一个公主也只能嫁给一个王子）。每个公主有嫁妆价值为 $w_{i}$ ,求国王能够得到的嫁妆的最大值。（可以有王子或公主无伴侣）

分析

看到一个王子只能娶一个公主（一个公主也只能嫁给一个王子），马上想到带权二分图匹配，但数据明显不允许这样。

（ $1<=n,m<=200000$ ）

考虑到一个王子只能娶一个公主，那么若构图，则每个点的入度最多为 $1$ 。那我们将每对$a_{i}$ , $b_{i}$ 连一条边，方向暂时不定。那这样就是一个并查集了，且这张图至多有一个环。

再考虑贪心，我们先以嫁妆 $w_{i}$ 为关键字从大到小排序。每次操作分两种情况:

1. $a_{i}$ , $b_{i}$ 不在一个并查集中。若它们各自属于的并查集中一共有少于2个环，则合并两个并查集，$ans+=w_{i}$。否则不合并。

1. $a_{i}$ , $b_{i}$ 在一个并查集中。若这个并查集中没有环，则修改这个并查集为有环，$ans+=w_{i}$。否则不操作。

输出 $ans$ 即可。

代码
```cpp
#include<algorithm>
#include<cstdio>

using namespace std;

struct node
{
	int a,b,w;
	node(int x,int y,int z)
	{
		a=x,b=y,w=z;
	}node(){}
}p[200001];
int n,m,ans;
int fa[200001],d[200001];

bool cmp(node x,node y)
{
	return x.w>y.w;
}
int find(int k)
{
	if(k!=fa[k]) fa[k]=find(fa[k]);
	return fa[k];
}
		
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		p[i]=node(x,y,z);
	}
	sort(p+1,p+m+1,cmp);
	for(int i=1;i<=n;i++) fa[i]=i,d[i]=1;
	for(int i=1;i<=m;i++)
	{
		int x=find(p[i].a),y=find(p[i].b);
		if(x!=y && (d[x]!=0 || d[y]!=0)) fa[y]=x,ans+=p[i].w,d[x]=d[x]&d[y];
		else if(x==y && d[x]) d[x]=0,ans+=p[i].w;
	}
	printf("%d\n",ans);
	return 0;
}
```






---

## 作者：封禁用户 (赞：3)

## 题意

有 $n$ 个王子和 $m$ 个公主。每个公主喜欢两个王子，编号为 $a_{i}$，$b_{i}$。每一个王子只能娶一个公主，每一个公主也只能娶一个王子（可以无伴侣），每个公主有嫁妆价值为 $w_{i}$，现在问你一共能得到最大的嫁妆是多少。

## 解法

这题一眼看过去是二分图带权匹配可以秒掉，但是一看数据，发现 $n, m \le 2 \times 10^5$，肯定会超时。

考虑 $a_i\rightarrow b_i$ 连一条边，权值 $w_i$。（反方向同理）

接下来我们考虑什么情况下我们的选边是合法的。

1. 这是一个树

如果我们现在选择了 $l$ 条边，这 $l$ 条边连接了 $l + 1$ 个点，我们可以丢掉一个点（舍弃一个王子），则剩下 $l$ 个王子就可以完全匹配这 $l$ 个公主。

2. 这是一个基环树

在 $l$ 条边和 $l + 1$ 个点的树中新增一条边，就是 $l + 1$  条边和 $l + 1$ 个点。这不就是一个基环树吗？对于这一个基环树，我们把其中唯一的环作为根节点，在这个环中，王子和公主可以完全匹配，所以我们把它看成根节点，剩下的边都和点也就可以匹配。

那么如何解决呢？我们可以用 $\operatorname{Kruskal}$ 来解决。

令 $du_i$ 表示 $i$ 为代表元（一个集合中具有代表性的元素）的集合是不是一个基环树，$0$ 表示这是一个基环树，$1$ 表示不是一个基环树。我们可以发现两个树可以合并成一个树，一个树和一个基环树可以合并成一个基环树。


我们设 $x, y$ 是当前枚举到的两个点，我们可以再分两种情况讨论:

1. 若 $x \neq y$

那么如果 $du[x]\operatorname{or}du[y] =1$，那么 $x, y$ 所在的集合至少有一个不是基环树，可以合成一棵树或基环树。答案加上这条边的边权。并且将这两个树合并： $du[x] = du[x]\operatorname{and} du[y]$。

2. 若 $x=y$

$du[x]$ 只能等于 $1$，代表这个集合是一个树，加一条边成为了基环树，$du[x]$ 变为 $0$。答案加上当前这条边的边权。

这题就做完了。

## AC 代码

```cpp
/*****************************************
备注：
******************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <climits>
using namespace std;
typedef long long ll;
#define int ll
const int MAXN = 2e6 + 10;
const int MR = 10 + 5;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const bool debug = false;
struct node
{
	int a, b, w;
}a[MAXN];
bool cmp(node x,node y)
{
	return x.w > y.w;
}
int n, m;
int fa[MAXN];
int du[MAXN];
void init()
{
	for(int i = 1;i <= n; i++)
	{
		fa[i] = i;
		du[i] = 1;//一个树
	}
}
int getfa(int f)
{
	return (f != fa[f] ? fa[f] = getfa(fa[f]) : fa[f]);
}
signed main()
{
	// int start = clock();
	cin >> n >> m;
	init();
	for(int i = 1; i <= m; i++)
	{
		cin >> a[i].a >> a[i].b >> a[i].w;
	}
	sort(a + 1,a + 1 + m, cmp);
	int ans = 0;	
	for(int i = 1; i <= m; i++)
	{
		int x = getfa(a[i].a);
		int y = getfa(a[i].b);
		if(x != y)
		{
			if(du[x] || du[y])
			{
				fa[y] = x;
				ans += a[i].w;
				du[x] = (du[x] & du[y]);
			}
		}
		else
		{
			if(du[x])
			{
				ans += a[i].w;
				du[x] = 0;
			}
		}
	}
	cout << ans << endl;
	// printf("%.3lf", clock() - start);
    return 0;
}
```

---

## 作者：whiteqwq (赞：2)

[CF875F Royal Questions](https://www.luogu.com.cn/problem/CF875F)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1750100)

## 题意

- $n$个王子，$m$个公主，每个公主有嫁妆$w_i$；
- 王子和公主都只能有一个伴侣，每个公主有两个喜欢的王子（只能挑选喜欢的王子作为伴侣）；
- 作为国王，你要选择王子的伴侣，达到收获的嫁妆最多。
- 数据范围：$2\leqslant n\leqslant 2\cdot 10^5,1\leqslant m\leqslant 2\cdot 10^5$。

## 分析

贪心+并查集妙题

考虑定义一条有向边$u\rightarrow v$的意义为$u$把公主让给了$v$，那么每个点一定入度为$1$，所有的边会形成一个外向基环树森林。

贪心地把公主按照嫁妆从大到小排序，每个公主看成一条无向边，那么可行的方案一定会形成一个基环树森林。

用并查集维护所有王子组成的基环树，用标记$flg$来记录一个并查集代表的集合为基环树还是树，然后考虑选择一条边的方法：

- 如果合并的两个点属于同一个并查集：
- - 如果这个并查集是一棵树，那么可以选，并标记为基环树；
- - 否则不选。
- 如果合并的两个点不属于一个并查集：
- - 如果合并两棵树，那么可以选，标记为树；
- - 如果合并一棵树，一棵基环树，那么可以选，标记为基环树；
- - 否则不选。

## 代码
```
#include<stdio.h>
#include<algorithm>
using namespace std;
const int maxn=200005,maxm=200005; 
int n,m,e,ans;
int f[maxn],flg[maxn];
struct edge{
	int x,y,z;
}g[maxm];
inline int cmp(edge a,edge b){
	return a.z>b.z;
}
int find(int x){
	return f[x]==x? x:f[x]=find(f[x]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&g[i].x,&g[i].y,&g[i].z);
	sort(g+1,g+1+m,cmp);
	for(int i=1;i<=n;i++)
		f[i]=i;
	for(int i=1;i<=m;i++){
		int x=find(g[i].x),y=find(g[i].y);
		if(x==y){
			if(flg[x]==0)
				flg[x]=1,ans+=g[i].z;
			continue;
		}
		if(flg[x]+flg[y]<=1){
			f[y]=x,flg[x]=flg[x]+flg[y];
			ans+=g[i].z;
		}
	}
	printf("%d\n",ans);
 	return 0;
}
```

---

## 作者：lfxxx (赞：1)

并查集模拟费用流。

考虑费用流建模，一个公主连边 $(S,i,1,w_i)$，再连边 $(i,a_i,1,0),(i,b_i,1,0)$，每个王子连边 $(i,T,1,0)$。

将公主按照 $w_i$ 从大到小加入后，图上没有正环，只用考虑增广路即可。

不难发现增广路一定形如 $S \to i \to x \to j \to y \to T$，其中 $x \to j$ 是因为之前走了一条 $S \to j \to x$ 形成的反悔边，注意力集中一下，你发现一个点要么可以直接走向汇点，要么可以通过不断走反悔边和普通边走到**唯一**一个可以走到汇点的点，要么不断走反悔边和普通边会陷入循环，没有增广路。

这个性质之所以是对的是因为一组匹配 $S \to i \to a_i \to x \to T$ 产生的影响是之前不断走反悔边和普通边走到 $x$ 的点现在会通过 $x \to a_i \to i \to b_i$ 走到 $b_i$ 上，而假若 $b_i$ 之前就会走到 $a_i$ 上就会形成一个环，一旦走入这个环就不会有任何增广路，因此这个环可以直接视作删去。

考虑使用并查集维护一个点可以走到的唯一一个能走向汇点的点即可做到 $O((n+m) \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 2e5+114;
pair<int,pair<int,int> > a[maxn];
int n,m;
int ans; 
int ch[maxn];//使用的点走退流边到的点 走不到有流量的点就是 0 自己有流量就是自己 
int found(int u){
	return ch[u]=(ch[u]==u?u:found(ch[u]));
} 
bool cmp(pair<int,pair<int,int> > x,pair<int,pair<int,int> > y){
	return x>y;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) ch[i]=i;
	for(int i=1;i<=m;i++) cin>>a[i].second.first>>a[i].second.second>>a[i].first;
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++){
		int u=a[i].second.first,v=a[i].second.second,w=a[i].first;
		if(found(u)!=0){
			ans+=w;
			if(found(v)==found(u)) ch[found(u)]=0;
			else ch[found(u)]=found(v);
		}else if(found(v)!=0){
			ans+=w;
			if(found(v)==found(u)) ch[found(v)]=0;
			else ch[found(v)]=found(u);
		}
	} 
	cout<<ans<<'\n';
	return 0;
}

```

---

## 作者：cpchenpi (赞：1)

首先题目显然可以建模为一个二分图的最大权匹配问题。根据贪心的思想，将公主按价值从大到小排序，每次搜索交错树；若找到未匹配节点，直接增广，否则丢弃该节点。这样我们就得到了一个 $O(m(m+n))$ 的算法。但这个复杂度显然不够优秀，我们要寻找加速它的方法。

首先直接给出算法如下：初始化所有 $n+m$ 个节点的并查集。同样将公主按价值从大到小排序。对她的两个相邻王子节点，若其并查集中所在连通块的大小为奇数，则可以取该公主节点，并同时将公主节点与相邻两节点在并查集中连通。否则丢弃该公主节点。

该算法的正确性依赖于以下结论：在我们的连接规则下，若一个邻王子节点所在连通块的大小为奇数，意味着交错树中存在未匹配节点。下面简单证明这个结论。

首先，根据我们的连接方式，显然交错树的对应部分包含于对应连通块中。注意到由于公主节点的度为 $2$，交错树这样的一个部分一定为链或者环；且为链时，存在未匹配节点；为环时不存在。若连通块中不存在除交错树外的节点，显然连通块的奇偶性决定了为链或者环的性质。而连通块中除交错树外的节点一定是两两匹配的节点，所以个数为偶，不影响上面的性质。

复杂度为 $O(m\log{m}+(n+m)\alpha(n+m))$，其中 $\alpha$ 表示反阿克曼函数。

通过代码（C++）：
``` cpp
#include <bits/stdc++.h>

using namespace std;

// 并查集代码
class UnionFindSet {
    vector<int> F;
    vector<int> rank;
    int n;

  public:
    UnionFindSet(int _n) {
        n = _n;
        F.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++) {
            F[i] = i;
        }
    }

    int size(int x) { return rank[find(x)]; }

    int find(int x) {
        return x == F[x] ? x : F[x] = find(F[x]);
    }

    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy)
            return;

        if (rank[fx] < rank[fy])
            swap(fx, fy);

        F[fy] = fx;
        rank[fx] += rank[fy];
    }
};

using i64 = int64_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v;
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--, b--;
        v.push_back({w, i, a, b});
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    auto ufs = UnionFindSet(n + m);
    i64 ans = 0;
    for (auto v : v) {
        int w = v[0], i = v[1], a = v[2], b = v[3];
        if (ufs.size(a) % 2 == 1 || ufs.size(b) % 2 == 1) {
            ans += w;
            ufs.merge(i + n, a);
            ufs.merge(i + n, b);
        }
    }
    cout << ans << endl;
}
```

---

## 作者：xixiup (赞：1)

## 思路分享

考虑将问题转化到图上，我们可以设有向边 $u \rightarrow v$ 表示一个王子 $u$ 将公主让给了王子 $v$，由于一个王子只能娶一个公主，所以每个节点的入度至多为 $1$ (也能为 $0$，表示这个王子还要单身)，这时候整个图就是一个**外向基环树森林**。

那么考虑如何建图，我们可以贪心地将公主以嫁妆的从多到少排序，嫁妆多的公主优先选择。我们可以把每一个公主看作一条无向边 $a_i - b_i$。

为什么要这么做呢？我们考虑将给这条边一个方向，如果是 $a_i \rightarrow b_i$，那么表示将公主 $i$ 嫁给了王子 $b_i$，而如果是 $a_i \leftarrow b_i$，则表示将公主 $i$ 嫁给了王子 $a_i$。

那么我们要考虑怎样才是合法的。如果我们选取的公主连成的图是一个**基环树森林**时，我们就可以将这些公主去一个方向，使这个图变为**外向基环树森林**。

那么我们需要怎样建成**基环树森林**呢？

考虑使用并查集，但是除了 $fa_i$ 之外我们还需要一个 $pd_i$，$pd_i$ 为 $0$ 表示这个并查集是一棵树，$pd_i$ 为 $1$ 表示这个并查集是一个基环树。

那么考虑加入边 $a - b$，合并并查集 $x$ 与 $y$：

$1.$ $x=y$

$\quad 1.1.$ $pd_x=1$ 则不能加入

$\quad 1.2.$ $pd_x=0$ 可以加入，并将 $pd_x$ 改为 $1$。

$2.$ $x \not=y$

$\quad 2.1.$ $pd_x+pd_y=2$ 则不能加入

$\quad 2.1.$ $pd_x+pd_y=1$ 可以加入，若 $x$ 是新的根结点，则 $pd_x=1$

$\quad 2.1.$ $pd_x+pd_y=0$ 可以加入，若 $x$ 是新的根结点，则 $pd_x=0$

然后我们就可以欢乐(bushi)地过掉这道题了！

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200100,maxm=maxn;
int n,m,fa[maxn],pd[maxn],ans;
struct node{
	int a,b,w;
	bool operator <(node u)const{
		return w>u.w;
	}
}p[maxm];
int judge(int x,int y){//判断，为1则可以加入，为0则不可以加入
	if(x==y){
		if(pd[x]==0){
			pd[x]=1;
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		if(pd[x]+pd[y]==2){
			return 0;
		}	
		else{
			fa[y]=x;
			pd[x]+=pd[y];
			return 1;
		}
	}
}
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&p[i].a,&p[i].b,&p[i].w);
	}
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	sort(p+1,p+1+m);
	for(int i=1;i<=m;i++){
		int x=find(p[i].a),y=find(p[i].b);
		ans+=judge(x,y)*p[i].w;//加入新的边
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：SIGSEGV (赞：1)

第一眼:网络流板子题！交了两发: `TLE on test 15......`

然后~~因为输入格式像一张在输入一张图，~~考虑根据输入建图。此时图中的每一条边只能匹配一个与它相邻的点。

因此，一个连通块$C$内的答案相当于在这个连通块内选出一个边集$E$,使得$E$中的每一条边都有至少一个唯一与其匹配的点且$C$能通过$E$连通。显然有$|C|-1\le |E|\le|C|$。

接下来分类讨论

1. 当$|E|=|C|-1$时，相当于选出一棵最大生成树，此时每条边匹配它的父亲。

2. 当$|E|=|C|$时，相当于选出一棵基环树。此时环上的边均匹配其“同一侧”的点，而不在环上的边均匹配朝向环一侧的点。

故上述两种方案均可行。然后按照 Kruskal 的思想贪心做就可以了。

每次用并查集维护当前连通块的形态，连通块不能合并，当且仅当两个连通块均为基环树。若发现当前边的两个点在同一连通块内时，判断是否能将该连通块从树变为基环树即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
using ll = long long;
int n,m,f[N],cyc[N];
struct Edge {int u,v,w;} e[N];
int getf(int v) {return f[v] == v ? v : f[v] = getf(f[v]);}
int main ()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1;i <= m;i++) cin >> e[i].u >> e[i].v >> e[i].w;
    sort(e + 1,e + m + 1,[](Edge a,Edge b) {return a.w > b.w;});
    ll ans = 0;
    for (int i = 1;i <= n;i++) f[i] = i;
    for (int i = 1;i <= m;i++)
    {
        int u = getf(e[i].u),v = getf(e[i].v);
        if (u == v)
        {
            if (!cyc[u]) ans += e[i].w,cyc[u] = 1;
            continue;
        }
        if (cyc[u] && cyc[v]) continue;
        f[u] = v;cyc[v] |= cyc[u];ans += e[i].w;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Merge_all (赞：0)

~~似乎可以用网络流搞一些分，似乎可以用反悔贪心水过去。~~
# Solution
当你第一眼看的是样例时，这道题你已经对了一半了。

输入很像一个图的输入，那么考虑建图。

- 将公主当作边来建图，那么最优的答案一定是 $n$ 个点配 $n$ 条边。

$n$ 个点 $n$ 条边，很容易就能想到基环树，那么这道题就转换成了求图中最大权值的基环树（不一定所有的点都取完）。

基环树和树的区别在于多了一条边，那么考虑使用 kruskal 进行加边。

怎么在 kruskal 上进行判断？开一个标记数组即可，考虑对于 $2$ 个点，判断所属集合是否是基环树，然后分类讨论即可。
# Code
```
#include <bits/stdc++.h>
//#define int long long
using namespace std;
using LL = long long;
using ULL = unsigned long long;
using pii = pair<int, int>;
using AR3 = array<int, 3>;
constexpr int N = 2e5 + 5;
int n, m, fa[N], ans;
bool vis[N];
int fd (int x) {return x == fa[x] ? x : fa[x] = fd (fa[x]);}
struct Node {
    int u, v, w;
} ev[N];

int main () {
    ios_base :: sync_with_stdio (false);
    *cin.tie (nullptr) << fixed << setprecision (20);
    
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) cin >> ev[i].u >> ev[i].v >> ev[i].w;
    sort (ev + 1, ev + m + 1, [] (auto x, auto y) {
        return x.w > y.w;
    });
    iota (fa + 1, fa + n + 1, 1);
    fill (vis + 1, vis + n + 1, 1);
    for (int i = 1; i <= m; i ++) {
        int x = ev[i].u, y = ev[i].v, z = ev[i].w;
        x = fd (x), y = fd (y);
        if (x != y && (vis[x] | vis[y])) fa[x] = y, ans += z, vis[y] = vis[x] & vis[y];
        else  if (x == y && vis[x]) vis[x] = 0, ans += z;
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：lovely_qiqi (赞：0)

## 思路

首先建模，考虑将公主作为边，两边作为潜在的王子。于是问题转换成了 $n$ 个点 $n$ 条边，那就是基环树了。不要求联通，就是**最大基环树森林**。

接下来求最大，然后基环树又是从树加一条边变过来的，考虑 kruscal。那么我们直接开始改。

+ 在对于一条边的两个点在一个连通块里的话，那这个连通块必须是树，如果是基环树就不能再加了，因为会破坏定义。

+ 否则对于两个连通块，必须要有一个是树（如果两个都是基环树连起来同样破坏定义）。

实现的话，用一个标记数组配合并查集就可以了。 

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,rx,ry,ans,fa[500010];
bool is[500010];
struct node{
	int u,v,w;
}a[500010];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
bool cmp(node t1,node t2){
	return t1.w>t2.w;
}
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i].u>>a[i].v>>a[i].w;
	sort(a+1,a+1+m,cmp);
	for(int i=1;i<=n;i++) fa[i]=i,is[i]=true;
	for(int i=1;i<=m;i++){
		rx=find(a[i].u);
		ry=find(a[i].v);
		if(rx==ry){
			if(is[rx]){
				is[rx]=false;
				ans+=a[i].w;
			}
		}
		else if(is[rx]||is[ry]){
			fa[rx]=ry;
			is[ry]=is[rx]&is[ry];
			ans+=a[i].w;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## solution

对于一个公主 $i$，其实她是没有任何意义的，关键点始终在于 $a_i, b_i$ 两个王子中只有一个能选取公主 $i$ 的价值 $w_i$。

那么我们 $a_i$ 向 $b_i$ 连一条边权为 $w$ 的边，给每条边定一个向，相当于我要满足每个点的出边不超过一条。

那么发现这个东西是一个内向基环树森林，我们仍然可以使用最小生成树的做法，给每个连通块打上标记，是否有环，我们仅可以将两个不都是环的连通块进行合并，当然，如果两个点在同一个连通块内，如果之前是一棵树，那么判为环。

## code

code：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 4e5 + 5;

int n, m, cnt, ans;
int fa[N], p[N];

int find ( int x ) {
  if ( fa[x] == x ) {
    return x;
  }
  return fa[x] = find ( fa[x] );
}

void unionn ( int x, int y ) {
  x = find ( x ), y = find ( y );
  if ( x != y ) {
    fa[x] = y;
    p[y] |= p[x];
  }
}

struct Node {
  int u, v, w;
} a[N];

void Solve () {
  cin >> n >> m;
  for ( int i = 1; i <= m; i ++ ) {
    int u, v, w;
    cin >> u >> v >> w;
    a[++ cnt] = { u, v, w };
  }
  sort ( a + 1, a + 1 + cnt, [] ( Node x, Node y ) { return x.w > y.w; } );
  int res = 0;
  for ( int i = 1; i <= n; i ++ ) {
    fa[i] = i;
  }
  for ( int i = 1; i <= cnt; i ++ ) {
    int u = find ( a[i].u ), v = find ( a[i].v );
    if ( u != v && !( p[u] && p[v] ) ) {
      unionn ( a[i].u, a[i].v );
      ans += a[i].w;
      res ++;
    }
    if ( u == v && !p[u] ) {
      p[u] = 1;
      ans += a[i].w;
      res ++;
    }
    if ( res == n ) {
      break;
    }
  }
  cout << ans;
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
	return 0;
}
```

---

## 作者：wyyqwq (赞：0)

[更好的阅读体验（或许](https://www.cnblogs.com/wwyyyy/p/18189751)

[洛谷传送门](https://www.luogu.com.cn/problem/CF875F)


$a_i$ 和 $b_i$ 之间连一条 $w_i$ 的边，相当于把公主当作限制条件。

考虑选当前这条边是否合法：

1.若选了当前这条边后变成了一棵树，那即为 $x$ 个点和 $x-1$ 个边，可以任意舍去一个点（因为可以有王子不结婚），所以一定合法。 

2.若选了当前这条边后，变成了一棵基环树，即为 $x$ 个点和 $x$ 条边，那显然一定合法。

重点在于判选了这条边后是否是一个基环树。考虑仍使用 kruskal 的方法，排序后依次考虑。若当前的边的两端 $a,b$ 在同一个树内，那连上这条边会让他变成一个基环树，否则的话会变成一棵树。设 $vis_i$ 表示以 $i$ 为根的集合是树/基环树。$vis_i = 0$ 表示树，反之基环树。

不难得知一棵树和一棵树合并一定会变成一棵树，一棵树和一棵基环树合并会变成一棵基环树。然后在加边的时候按照这个进行判断即可，细节看代码。

```c++
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;
struct node {
    int a, b, k;
}g[N];
bool cmp(node x, node y) {
    return x.k > y.k;
}
int fa[N], vis[N];
int findfa(int x) {
    if(fa[x] == x) return x;
    return fa[x] = findfa(fa[x]);
}
int main () {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) fa[i] = i, vis[i] = 1;
    for(int i = 1; i <= m; i ++) {
        cin >> g[i].a >> g[i].b >> g[i].k;
    }
    sort(g + 1, g + m + 1, cmp);
    int cnt = 0, ans = 0;
    for(int i = 1; i <= m; i ++) {
        int fx = findfa(g[i].a), fy = findfa(g[i].b);
        if(fx != fy) {
            if(vis[fx] == 1 || vis[fy] == 1) {
                fa[fy] = fx;
                if(vis[fx] == 0 || vis[fy] == 0) vis[fx] = 0;
                else vis[fx] = 1;
                ans += g[i].k;
                cnt ++;
            }
        }
        else {
            if(vis[fx]) {
                ans += g[i].k;
                vis[fx] = 0;
                cnt ++;
            }
        }
        if(cnt == n) break;
    }
    cout << ans << endl;
}
```

---

## 作者：OIer_ACMer (赞：0)

~~奇妙的结婚机制~~

------------
这道题难度适中，作为紫题估计是高估了它的难度，但是，它所涉及到的知识点还是非常值得我们深究的。


## 大致思路：
一开始觉得是**二分图**，但是想一想却是**贪心**，策略是：每次取只取**最大嫁妆**的那一对未婚夫妻，再判断是否会出现环。因为建边只能通过将两个王子连在一起（这是我的思路），如果出现了环，就会有人无法配对，所以就要用**并查集**进行判断，判断是否能够加入集合。


## 具体步骤：
1. 输入数据，以嫁妆大小为标准，进行降序排序，便于后面合并时得到的局部解**是最优解**。

2. 进行并查集合并，定义 $ans$ 数组为最终最优解，每次判断两王子是否已经处于一个集合，是的就不加，否则就判断各自处于的集合**是否已经无法再进行配对**，如果有一个可以，那么就~~另寻出路~~合并在一起，成为一个新的集合，给更多的~~单身狗~~王子一个机会。

3. 如果当前王子**自己所处的集合还能够进行配对**（大部分情况是**第一次匹配**），那么就直接更新 $ans$ 的值，不用再做别的操作。


## 代码如下:

```c++

#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct node
{
    int a, b, val;
    bool operator<(const node &i) const
    {
        return val > i.val;
    }
} edge[maxn];
int n, m;
int fa[maxn], appeared[maxn];
int find(int x)
{
    if (x != fa[x])
    {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}
void init()
{
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
        appeared[i] = 1;
    }
}
void solve()
{
    int ans = 0;
    for (int i = 1; i <= m; i++)
    {
        int fx = find(edge[i].a), fy = find(edge[i].b);
        if (fx != fy)
        {
            if (appeared[fx] || appeared[fy])
            {
                fa[fx] = fy;
                ans += edge[i].val;
                appeared[fy] = (appeared[fx] & appeared[fy]);
            }
        }
        else
        {
            if (appeared[fx])
            {
                ans += edge[i].val;
                appeared[fx] = 0;
            }
        }
    }
    cout << ans;
}
int main()
{
    n = read();
    m = read();
    init();
    for (int i = 1; i <= m; i++)
    {
        edge[i].a = read();
        edge[i].b = read();
        edge[i].val = read();
    }
    sort(edge + 1, edge + m + 1);
    solve();
    return 0;
}

```
[AC记录](https://www.luogu.com.cn/record/120071238)

---

## 作者：Leasier (赞：0)

考虑将原问题转化为一个图论问题：

- 连边 $a_i \to^{w_i} b_i$ 表示 $a_i$ 可以把公主让给 $b_i$。
- 把边反向后亦然。

然后可以发现只要我们抓出一个连通块，使得每个点的出度 $\leq 1$ 即可满足条件。

于是这个连通块要么是树，要么是基环树。

考虑贪心。把边按照 $w_i$ 降序排序，讨论当前的两个连通块：

- 若两个连通块不同且其中至少一个是树，则可以直接合并。
- 若两个连通块相同且该连通块是树，则也可以连边。

最终输出连上的边权和即可。时间复杂度为 $O(n + m(\log n + \log m))$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

typedef struct {
	int start;
	int end;
	int dis;
} Edge;

int root[200007];
bool vis[200007];
Edge edge[200007];

bool operator <(const Edge a, const Edge b){
	return a.dis > b.dis;
}

inline void init(int n){
	for (register int i = 1; i <= n; i++){
		root[i] = i;
		vis[i] = true;
	}
}

int get_root(int x){
	if (root[x] == x) return x;
	return root[x] = get_root(root[x]);
}

inline ll kruskal(int n, int m){
	ll ans = 0;
	for (register int i = 1; i <= m; i++){
		int x_root = get_root(edge[i].start), y_root = get_root(edge[i].end);
		if (x_root != y_root){
			if (vis[x_root] || vis[y_root]){
				root[x_root] = y_root;
				vis[y_root] &= vis[x_root];
				ans += edge[i].dis;
			}
		} else if (vis[x_root]){
			vis[x_root] = false;
			ans += edge[i].dis;
		}
	}
	return ans;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	init(n);
	for (register int i = 1; i <= m; i++){
		scanf("%d %d %d", &edge[i].start, &edge[i].end, &edge[i].dis);
	}
	sort(edge + 1, edge + m + 1);
	cout << kruskal(n, m);
	return 0;
}
```

---

## 作者：syzf2222 (赞：0)

考虑贪心地按$w_i$从大到小选择。

首先想到匈牙利算法，然而复杂度$O(nm)$，$TLE$到飞起(然而我跑了63个点，奇迹)。

这里给出一个奇妙的并查集做法，先上代码。
```
for(int i=1;i<=n;i++)
	fa[i]=i;
for(int i=1;i<=m;i++){
	int x=find(p[i].a),y=find(p[i].b);
	if(x==y&&f[x]==0){
		f[x]=1;
		ans+=p[i].w;
	}
	if(f[x]+f[y]<=1){
		fa[y]=x;f[x]+=f[y];
		ans+=p[i].w;
	}
}
```
$f[x]=0$代表这个集合还差一个塞满，$f[x]=1$代表这个集合全部塞满。

如果两个王子在同一个集合中，然而这个集合还未塞满，则可以再塞一个进去。

如果不在同一集合，只要有其中一个没有塞满，就可以塞进去，同时合并集合。

那么这样复杂度就降低为$O(mlogm)$了（瓶颈为排序）。

代码如下，仅供参考：
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,m,fa[maxn],f[maxn],ans;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
struct node{
	int a,b,w;
}p[maxn];
inline int cmp(node x,node y){
	return x.w>y.w;
}
inline int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		p[i].a=read();
		p[i].b=read();
		p[i].w=read();
	}
	sort(p+1,p+1+m,cmp);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=find(p[i].a),y=find(p[i].b);
		if(x==y&&f[x]==0){
			f[x]=1;
			ans+=p[i].w;
		}
		if(f[x]+f[y]<=1){
			fa[y]=x;f[x]+=f[y];
			ans+=p[i].w;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```
同时分享一个卡常小技巧，之前写匈牙利时无意发现的。

朴素代码：
```
inline int dfs(int x){
	if(!vis[p[x].a]){
		vis[p[x].a]=1;st[++top]=p[x].a;
		if(!mat[p[x].a]||dfs(mat[p[x].a])){
			mat[p[x].a]=x;
			return 1;
		}
	}
	if(!vis[p[x].b]){
		vis[p[x].b]=1;st[++top]=p[x].b;
		if(!mat[p[x].b]||dfs(mat[p[x].b])){
			mat[p[x].b]=x;
			return 1;
		}
	}
	return 0;
}
```
我们记数组$col[i]$，若有一次$x$未匹配成功，则设$col[x]=1$，此后忽略此点。

优化代码如下：
```
inline int dfs(int x){
	if(col[x])return 0;
	if(!vis[p[x].a]){
		vis[p[x].a]=1;st[++top]=p[x].a;
		if(!mat[p[x].a]||dfs(mat[p[x].a])){
			mat[p[x].a]=x;
			return 1;
		}
	}
	if(!vis[p[x].b]){
		vis[p[x].b]=1;st[++top]=p[x].b;
		if(!mat[p[x].b]||dfs(mat[p[x].b])){
			mat[p[x].b]=x;
			return 1;
		}
	}
	col[x]=1;
	return 0;
}
```
这样就从14个点跑到了63个点。

但个人认为一定程度上降低了复杂度？？

欢迎大家批评指正。

---

