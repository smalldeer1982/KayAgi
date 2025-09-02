# Ants in Leaves

## 题目描述

Tree is a connected graph without cycles. A leaf of a tree is any vertex connected with exactly one other vertex.

You are given a tree with $ n $ vertices and a root in the vertex $ 1 $ . There is an ant in each leaf of the tree. In one second some ants can simultaneously go to the parent vertex from the vertex they were in. No two ants can be in the same vertex simultaneously except for the root of the tree.

Find the minimal time required for all ants to be in the root of the tree. Note that at start the ants are only in the leaves of the tree.

## 样例 #1

### 输入

```
12
1 2
1 3
1 4
2 5
2 6
3 7
3 8
3 9
8 10
8 11
8 12
```

### 输出

```
6
```

## 样例 #2

### 输入

```
2
2 1
```

### 输出

```
1
```

# 题解

## 作者：hxhhxh (赞：7)

## 大意

给定一棵有根树，每一个叶子结点上有一只蚂蚁，不允许两只蚂蚁站在同一个非根结点上，每一次操作可以使若干只蚂蚁同时移动到它的父节点，求最少需要多少次操作，可以使所有蚂蚁站在根节点。

## 思路

首先发现根节点的各个子树独立。那么我们就可以对于每一个子树单独计算，最后取最大值。

对于一棵子树，设 $ d_i $ 表示第 $ i $ 个节点的深度，根的深度为 $ 1 $ 。如果没有“不允许两只蚂蚁站在同一个非根结点上”的限制， $ d_i $ 也表示到达根所需要的步数。

将一个子树里的全部 $ d_i $ 存入 $ a $ 数组并排序。从 $ d_i $ 最小的节点开始往上走。

对于某一个节点 $ i $ （不是题目里的编号），若 $ a_i > a_{i-1} $ ，那么当 $ i $ 到达这一子树的根时，节点 $ i - 1 $ 已经到达根；否则这一子树的根有蚂蚁正在经过，需要等节点 $ i-1 $ 上的蚂蚁先走过去， $ a_i = \max(a_i,a_{i-1}+1) $ 。

最后一只蚂蚁过去的时间就是整棵子树的答案。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,cnt,ans,a[500005];
vector<int>e[500005];
void dfs(int x,int f,int dep){
	bool flg=true;
	for(int i=0;i<e[x].size();i++){
        if(e[x][i]==f)continue;
        dfs(e[x][i],x,dep+1);
        flg=false;
    }
	if(flg) a[++cnt]=dep;
}
signed main(){
	cin>>n;
	for(int i=1,j,k;i<n;i++){
		scanf("%lld %lld",&j,&k);
        e[j].push_back(k);
        e[k].push_back(j);
	}
	for(int i=0;i<e[1].size();i++){
		cnt=0;
		dfs(e[1][i],1,1);
		sort(a+1,a+cnt+1);
		for(int j=2;j<=cnt;j++) a[j]=max(a[j],a[j-1]+1);
		ans=max(ans,a[cnt]);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：rizynvu (赞：2)

[我的博客](https://www.cnblogs.com/rizynvu/p/18459321)。

首先因为 $1$ 点是可以一次性到多个点的，因此不需要考虑 $1$ 点的情况，而是转而分析 $1$ 的每个子树的情况，最后取 $\max$。

那么对于每个子树，就有每个节点每个时刻至多存在 $1$ 个点的性质了。  
考虑如何去求解。

首先一个贪心的想法是肯定是每个蚂蚁越早到一个点越好。
于是一个想法是考虑在 dfs 的时候合并。  
即维护子树 $u$ 内叶子到 $u$ 的时间 $S$，子树 $v$ 内叶子到 $v$ 的时间 $T$。  
那么如果存在 $x\in S$ 满足 $x\in T$，那么就钦定这个蚂蚁先不往上爬，而是等到 $x + 1$ 时刻继续爬，即 $x\leftarrow x + 1$ 直到 $x\not \in T$。  

但是问题在于合并的次数太多了，这个合并的方法也不太好用数据结构维护（其实可以启发式合并 + 线段树二分做到 $\mathcal{O}(n\log^2 n)$）。

考虑到一个 $x\in S$，这个 $x$ 会和许多其他集合 $T$ 合并，但是合并操作都是若 $x\in T$，则 $x\leftarrow x + 1$。  
那么这说明实际上各个集合是不区分的，那么就可以直接把所有的叶子放在根处合并。

即直接维护可重集合 $S = \{\operatorname{dep}_u | u \operatorname{is\ leaf}\}$，那么若 $S$ 中存在 $c(c\ge 1)$ 个 $x$，就直接钦定一个 $x$ 到根，而剩下的 $c - 1$ 个 $x$ 就只能变为 $x + 1$ 继续等待。  
$x$ 从小到大操作直到 $S$ 为空，变为空的那个时刻就代表着最后一个叶子的蚂蚁跳到了根，这个时刻就是这个子树的答案。  

容易发现这是与上述的递归合并过程等价的，因为这个让 $c - 1$ 个 $x$ 变为 $x + 1$ 就代表着在合并过程中发现了其他的 $x$ 选择了让步。

然后考虑优化 $S$ 的变化的过程。  
其实能够发现真正只关注每个 $x$ 的个数 $\operatorname{cnt}_x$。  
那么就可以直接递推，当 $\operatorname{cnt}_x\ge 1$ 时有 $\operatorname{cnt}_{x + 1}\leftarrow \operatorname{cnt}_{x + 1} + \operatorname{cnt}_x$。 

然后考虑一下这个过程中 $x$ 最大会是多少。  
一个很宽的上界是 $\operatorname{size}(T) + \max \operatorname{dep}(T)\le 2\operatorname{size}(T)$。  
又因为 $1$ 的所有子树 $\operatorname{size}$ 之和 $= n - 1$。  
所以可以知道实际上 $\sum \max x\le 2n - 2$。

于是时间复杂度就为 $\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
const int maxn = 5e5 + 10;
std::vector<int> to[maxn];
int dep[maxn], cnt[maxn * 2], tot;
int dfs(int u, int fa) {
   dep[u] = dep[fa] + 1;
   if (to[u].size() == 1)
      cnt[dep[u]]++, tot++;
   int siz = 1;
   for (int v : to[u])
      if (v != fa)
         siz += dfs(v, u);
   return siz;
}
int main() {
   int n; scanf("%d", &n);
   for (int i = 1, x, y; i < n; i++)
      scanf("%d%d", &x, &y), to[x].push_back(y), to[y].push_back(x);
   int mx = 0;
   for (int u : to[1]) {
      int siz = dfs(u, 1);
      for (int i = 1; ; i++) {
         if (cnt[i])
            tot--, cnt[i + 1] += cnt[i] - 1;
         if (! tot) {
            mx = std::max(mx, i); break;
         }
      }
      memset(cnt + 1, 0, sizeof(int) * siz * 2);
   }
   return printf("%d\n", mx), 0;
}
```

---

## 作者：Cry_For_theMoon (赞：2)

[传送门](https://codeforces.com/contest/622/problem/E)

神妙题，搞了半小时的树上dp...

#### 分析

把蚂蚁当成人吧......

首先发现根节点的不同子树独立，我们分开来考虑。

考虑一颗根节点子树内的所有人。此时，两个人 $(i,j)$ 的 $lca$ 不为 $1$，可能发生冲突。

此时发现一个事情，就是深度越小，这个人会越早到根。这是因为两个人有同一个父亲的时候，你选哪个上去都是一样的。这可能需要自己手玩一下。

然后就可以对这些人按深度排序，记深度为 $d$，显然第一个人 $d_1$ 就上去了，第二个人如果深度不同，则不会冲突，如果相同，那么它得等一次，所以从小往大更新 $d$：

$$d_i=\max\{d_i,d_{i-1}+1\}$$

然后不同子树的 $d_{sz}$ 的 $\max$ 就是答案，因为它们独立，其中 $sz$ 为子树内人数。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const ll MAXN=5e5+10,INF=1e18;
ll n,u,v,f[MAXN],depth[MAXN],b[MAXN],now;
vector<int>e[MAXN];
void dfs(int u,int fa){
	int flag=0;
	depth[u]=depth[fa]+1;
	for(auto v:e[u]){
		if(v==fa)continue;
		dfs(v,u);
		flag=1;
	}
	if(!flag){
		b[++now]=depth[u];
	}
}
int main(){
	cin>>n;
	rep(i,1,n-1){
		cin>>u>>v;
		e[u].pb(v);e[v].pb(u);
	}
	ll ans=-INF;
	for(auto v:e[1]){
		now=0;
		dfs(v,1);
		sort(b+1,b+1+now);
		rep(i,2,now){
			b[i]=max(b[i],b[i-1]+1);
		}
		ans=max(ans,b[now]);
	}
	cout<<ans;
	
	return 0;
}

```

---

## 作者：He_Ren (赞：2)

发现点1与其他点的处理方式不同，于是分开处理

答案就是对点1所有儿子的答案求max

考虑如何求每个儿子的答案

考虑贪心

显然，深度较浅的点会先到达，深度较深的点会后到达

答案就是深度最深的点

但是有一个问题，有深度相同的点

所以对于深度相同的点，就强行将一些点的深度增加1

在实现上，先将深度排序

$t$表示的就是当前的深度，当这个点的深度$>t$时，t就更新为当前点的深度，否则```++t;```

算出点1所有子树的答案，然后求max就行了

```cpp
#include<cstdio>
#include<algorithm>
const int MAXN = 5e5 + 5;
using namespace std;

inline void chk_max(int &a,int b){ if(a<b) a=b;}

struct Edge
{
	int next,to;
}e[MAXN<<1];
int head[MAXN],d[MAXN],etot=0;
inline void add(int u,int v)
{
	++etot;
	e[etot] = (Edge){ head[u],v};
	head[u] = etot;
	++d[v];
}

int q[MAXN],tl=0;
void dfs(int u,int fa,int lvl)
{
	if(d[u]==1)
	{
		q[++tl]=lvl;
		return;
	}
	for(int i=head[u]; i; i=e[i].next)
	{
		if(e[i].to==fa) continue;
		dfs(e[i].to,u,lvl+1);
	}
}

int main(void)
{
	int n;
	scanf("%d",&n);
	for(int i=1; i<n; ++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v); add(v,u);
	}
	
	int ans=0;
	for(int i=head[1]; i; i=e[i].next)
	{
		int u=e[i].to;
		tl=0;
		dfs(u,1,1);
		sort(q+1,q+tl+1);
		
		int t=0;
		for(int i=1; i<=tl; ++i)
		{
			if(t<q[i]) t=q[i];
			else ++t;
		}
		chk_max(ans,t);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Loop1st (赞：2)

### CF622E Ants in Leaves
第一道紫，纪念一下~。

首先每只蚂蚁肯定是能往上走就往上走的（假设这只蚂蚁能往上走但是它选择礼让，让另一只蚂蚁先往上走，那就相当于另一只蚂蚁能往上就往上，这只蚂蚁被挡住了所以没往上）。
一只蚂蚁不考虑交通堵塞走到根节点的步数就是它的深度，这是一个约束条件，另一个约束条件是和它在同一个根节点儿子的子树中的蚂蚁到这个根节点儿子的时间，即为它到根节点的时间 $-1$，那这只蚂蚁就要停下来等另一只蚂蚁到根节点，再往上走到根节点儿子和根节点，时间为另一只到根节点的时间 $-1$ 再 $+2$，那么我们就可以考虑每个根节点的子树，将子树中蚂蚁们按深度排序，然后用两个约束条件算出每只蚂蚁到达的时间，最后将答案和最后一只蚂蚁到的时间取 max 就行。

时间复杂度 $O(n \log n)$。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
typedef pair<int, int> pii;
int n, dep[N], c[N], tot, ans;
vector<int>edges[N];
inline void dfs(int pos, int fa) {
    bool flag = false;
    dep[pos] = dep[fa] + 1;
    for (auto x : edges[pos]) {
        if (x == fa) continue;
        flag = true;
        dfs(x, pos);
    }
    if (!flag) c[++tot] = dep[pos];
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    for (auto x : edges[1]) {
        tot = 0;
        dfs(x, 1);
        sort(c + 1, c + tot + 1);
        for (int i = 2; i <= tot; i++) c[i] = max(c[i], c[i - 1] + 1); //更新后的 c[i] 表示 i 到根节点的时间
        // i 到根节点的时间被深度, i - 1 到的时间约束, i - 1 到达根节点儿子的时间为 c[i - 1] - 1, 这时 i 不能走到根节点儿子处,
        // 只能等 i - 1 到根节点, 即时间为 c[i - 1] 是才能往上走, 时间为 c[i - 1] 时到达根节点儿子, c[i - 1] + 1 时到达根节点
        ans = max(ans, c[tot]);
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Rain_chr (赞：2)

感觉其他题解做法并不本质。

正着不好直接做，考虑时光倒流，最小化所有蚂蚁回到叶子节点的代价。

因为一个节点上只能有一个蚂蚁，所以蚂蚁从根节点出发，去各个儿子的时候，必须等待一秒再走，否则就会和上一只蚂蚁在儿子处重叠。

我们假定这只蚂蚁来自深度为 $d$ 的叶子节点，那么它从根节点出发后一定会一直朝着这片叶子走，在 $d$ 秒后回到叶子。因为我们保证了在子树中出发时间隔一秒，所以显然蚂蚁不会在下面的子树中重叠。

因为我们要最小化等待时间与深度之和的最大值，有因为先出发的等待时间少，所以我们对于每一个子树，让深度大的先出发，最后答案就是所有蚂蚁回到叶子所花时间的最大值。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
vector<int> a[N];
int d[N];
vector<int> can;
void dfs(int x,int fa)
{
    d[x]=d[fa]+1;
    int son=0;
    for(int to:a[x])
    {
        if(to==fa) continue;
        dfs(to,x);
        son++;
    }
    if(!son)
        can.push_back(d[x]);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    int ans=0;
    for(int to:a[1])
    {
        can.clear();
        dfs(to,1);
        sort(can.begin(),can.end(),greater<int>());
        int wait=0;
        for(int i:can)
            ans=max(ans,i+wait),wait++;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：hsy8116 (赞：0)

## 题意简述

[link: 题面](https://codeforces.com/problemset/problem/622/E)

有一棵树，$1$ 号点是根，每个叶子有一只蚂蚁，每次可以往上爬一个点，除根外的点每次只能容纳一只蚂蚁，问所有蚂蚁爬到根结点的最小时间。

## 解题思路

首先考虑根结点可以容纳多只蚂蚁而其他点不能，所以根结点的子结点可以同时往根上跑蚂蚁，所以蚂蚁爬完的最终时间是根结点的子结点中最慢爬完蚂蚁的时间。

考虑根的一棵子树，$x$ 为子树根。$x$ 子树中会存在多个叶子结点（有蚂蚁的结点），这些叶子跑到整个树的根 $1$ 号点会有一个距离，这个距离和深度 `dep` 一致（$1$ 号点深度为 $0$），所以将叶子的 `dep` 值放入 `dis`，组成叶子跑到整个树的根 $1$ 号点的距离数组。在 `dis` 数组中，如果有两个值相等，那么在 $x$ 子树中一定有两只蚂蚁会在这个子树中的某个点撞上，所以需要让一个值增加 $1$，进行等待。

在具体实现上，考虑对每个 $x$ 子树的 `dis` 排序，从小到大遍历，若有相邻的两个值相等，对靠后的值加 $1$ 以避免冲突。

## $Code$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int NR = 5e5 + 10;

struct edge
{
	int nxt, to;
}e[NR * 2];

int head[NR], cnt;

void add(int x, int y)
{
	e[++cnt].nxt = head[x];
	e[cnt].to = y;
	head[x] = cnt;
}

int dep[NR];
int dis[NR], sz;

void dfs(int x, int fa)
{
	dep[x] = dep[fa] + 1;
	bool isLeaf = true;
	for (int i = head[x]; i; i = e[i].nxt)
	{
		int y = e[i].to;
		if (y == fa) continue;
		isLeaf = false;
		dfs(y, x);
	}
	if (isLeaf) dis[++sz] = dep[x];
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; i ++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
		add(y, x);
	}
	int ans = 0;
	for (int i = head[1]; i; i = e[i].nxt)
	{
		int x = e[i].to;
		sz = 0;
		dep[1] = 0;
		dfs(x, 1);
		sort(dis + 1, dis + sz + 1);
		for (int j = 2; j <= sz; j ++)
		{
			dis[j] = max(dis[j], dis[j - 1] + 1);
		}
		ans = max(ans, dis[sz]);
	}
	printf("%d\n", ans);
	return 0;
}
```

整体复杂度为 $O(n\log{n})$，注意对每个子树 $x$ 不要做 `memset` 否则会超时。

---

## 作者：wfc284 (赞：0)

似乎是一种新的理解方式。

难办的显然是一只蚂蚁被其父结点的蚂蚁卡住。  
我们令蚂蚁初始的【既定耗时】为其深度（由于每秒一单位）。  
蚂蚁被卡住，就是由于有两只蚂蚁的【既定耗时】相同。

直接模拟显然是不好做的。  
换个角度，我们让将要被卡住的蚂蚁晚点出发，这样就可以一路畅通了。  
晚多少呢？我们可以将蚂蚁的【既定耗时】从小到大排序，开一个桶表示每只蚂蚁什么时候能到达终点。  
本来，每只蚂蚁应该要用等同其深度的时间走到终点。  
依次枚举【既定耗时】，如果它在桶中出现过，那么它一定会被卡住。这时，让它的“深度”（即耗时）为在桶中最大的数加一，就是最优的（不用二分，因为是从小到大枚举的）。  

这样做，每只蚂蚁自然会延迟一些出发，从而避免了互相卡住。这个贪心也是最优的。

还有一个细节，要在 $1$ 号结点的所有儿子中跑刚刚的过程，取所有蚂蚁中最大的【既定耗时】作为子树的答案。再在所有的子树答案中取 $\max$。  
原因就是 $1$ 号结点可以容纳多只蚂蚁。

瓶颈是排序，时间复杂度 $O(n \log n)$。  
[submission.](https://codeforces.com/contest/622/submission/305385441)

---

## 作者：Z_kazuha (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF622E)

刚做时被难度吓到了，但好像是水紫。

发现蚂蚁是可以随便（指没有一个的限制）到根节点的，所以根节点的不同子树独立。

蚂蚁是能走就走的：因为如果是两个蚂蚁抢一个点然后这个蚂蚁等了就可以看作是另一个蚂蚁能走就走。

### 代码实现

先用一个 `dfs` 预处理出来深度，然后对于每个根的子树内的点把他们的深度排序，放进 $d$ 数组里。

对于一个点，若 $d_i>d_{i-1}$ 说明他可以直接往上跳，若 $d_i=d_{i-1}$ 说明他需要等 $d_{i-1}$ 给他腾出地方他才能跳。

所以：$d_i=\max(d_i,d_{i-1}+1)$。

根节点就是个统计点，输出他的子树的 $\max$ 即可。

---

## 作者：Hoks (赞：0)

## 前言
貌似不是很难做？好像一眼胡对整体走向了。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
显然的有一种贪心的想法：能移动的蚂蚁都移动最好。

那么我们只要找到最下面的那只蚂蚁走上来的时间就行了。

而蚂蚁都往根上走，路径显然有交，先后顺序即为深度的大小。

对于这点实现，我们只需要考虑从上往下的所有节点，看下哪个节点把他下面的那个节点卡住了即可。

考虑证明下这个贪心为什么是对的。

因为对于一个点 $i$，在这个点子树中的叶子无论怎样都要经过他，只有时间的先后之分。

所以对于任何一只蚂蚁，肯定越早经过点 $i$ 越好。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,tot,ans,a[N],dep[N];vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='#'||c=='.'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void dfs(int u,int ff)
{
    dep[u]=dep[ff]+1;if(e[u].size()==1) a[++tot]=dep[u];
    for(auto v:e[u]) if(v!=ff) dfs(v,u);
}
signed main()
{
    n=read();for(int i=1,u,v;i<n;i++) u=read(),v=read(),e[u].emplace_back(v),e[v].emplace_back(u);
    for(auto v:e[1])
    {
        tot=0;dfs(v,1);sort(a+1,a+1+tot);
        for(int j=2;j<=tot;j++) a[j]=max(a[j],a[j-1]+1);
        ans=max(ans,a[tot]);
    }print(ans);
    genshin:;flush();return 0;
}
```

---

## 作者：tZEROちゃん (赞：0)

> 给定一棵 $n$ 个节点的树，根节点是 $1$。这棵树的每一个叶节点都有一只小蚂蚁。每过 $1$ 秒钟，可以选择让一些蚂蚁向父节点走一步。注意，两只蚂蚁不能同时在一个除去根节点的节点上。            
> 问这些蚂蚁最少用多少秒的时间，使得所有蚂蚁都走到根节点。


我们考虑一个简化版本，如果没有「两只蚂蚁不能同时在一个除去根节点的节点上」，那么可以怎么做。

显然我们直接求出每个节点的深度，设这个深度是 $d_i$，那么显然 $\max\{d_i\}$ 就是答案。

那如果有这个条件怎么办？

我们可以强行把一个蚂蚁按着不让他走。

也就是说我们把这个蚂蚁深度加上 $1$。

那么做法就是，我们对根节点的每一刻子树的深度拿出来排个序，然后设 $dp_i$ 表示子树里的前 $i$ 个节点的蚂蚁爬到根节点的最小步数。

不难写出以下状态转移方程：

$$dp_i = \max\{dp_i, dp_{i-1}+1\}$$

答案是每棵子树的最后一个 $dp$ 值的最大值。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define pb push_back

const int N = 5e5 + 10;
vector<int> g[N], dp; int n, ans;

void dfs(int x, int f, int dep) {
  bool ck = 0;
  for (auto i : g[x]) {
    if (i == f) continue;
    dfs(i, x, dep + 1); ck = 1;
  }
  if (!ck) dp.pb(dep);
}

int main() {
  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int x, y; cin >> x >> y;
    g[x].pb(y); g[y].pb(x);
  }
  for (auto i : g[1]) {
    dp.clear();
    dfs(i, 1, 1); sort(dp.begin(), dp.end());
    for (int i = 1; i < dp.size(); ++i) {
      dp[i] = max(dp[i], dp[i - 1] + 1);
    }
    ans = max(dp[dp.size() - 1], ans);
  }
  cout << ans << endl;
}
```

---

## 作者：orz_z (赞：0)

### 题目大意

给定一棵 $n$ 个节点的树，根节点是 $1$。

这棵树的每一个叶节点都有一只小蚂蚁。

每过 $1$ 秒钟，可以选择让一些蚂蚁向父节点走一步。

注意，两只蚂蚁不能同时在一个的节点上，除了根节点。

问这些蚂蚁最少用多少秒的时间，使得所有蚂蚁都走到根节点。

对于 $100\%$ 的数据，保证 $2 \leq n \leq 5 \times10^5$。

### 解题思路

首先将根节点分开处理。

对于根节点的每一棵子树，不能使深度相同的两个叶节点同时到达当前子树的根节点。

那么可以对于根节点的每一棵子树对每个叶子节点的深度进行排序。

显然，深度较浅的点会先到达，深度较深的点会后到达。

答案就是深度最深的点。

但是有一个问题，有深度相同的点，

所以对于深度相同的点，就强行将一些点需要的步数加 $1$，因为要等前面的走一步，才能走。

那么设 $f_i$ 表示当前子树前 $i$ 个叶节点的蚂蚁爬到根节点需要最少步数，

则 $f_i=\max( f_i , f_{i-1}+1 )$。

设当前子树有 $p$ 个叶节点，那么答案即为所有 $f_p$ 的最大值。

时间复杂度 $\mathcal O(n \log n)$。

具体见代码。

### CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll read()
{
    ll a = 0, b = getchar(), c = 1;
    while (!isdigit(b))
        c = b == '-' ? -1 : 1, b = getchar();
    while (isdigit(b))
        a = a * 10 + b - '0', b = getchar();
    return a * c;
}

const int _ = 5e5 + 7;

int tot, head[_], to[_ << 1], nxt[_ << 1];

int n, ans, dp[_], now;

void add(int u, int v)
{
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs(int u, int fa, int d)
{
    bool flag = 0;
    for (int i = head[u]; i; i = nxt[i])
    {
        if (to[i] != fa)
        {
            flag = 1;
            dfs(to[i], u, d + 1);
        }
    }
    if (!flag)
        dp[++now] = d;
}
void DP()
{
    for (int i = head[1]; i; i = nxt[i])
    {
        now = 0;
        dfs(to[i], 1, 1);
        sort(dp + 1, dp + now + 1);
        for (int i = 1; i <= now; ++i)
            dp[i] = max(dp[i], dp[i - 1] + 1);
        ans = max(ans, dp[now]);
    }
}

signed main()
{
    n = read();
    for (int i = 1; i < n; i++)
    {
        int x = read(), y = read();
        add(x, y), add(y, x);
    }
    DP();
    printf("%d\n", ans);
    return 0;
}
```



---

## 作者：Create_Random (赞：0)

[E. Ants in Leaves](https://codeforces.ml/contest/622/problem/E)

解法：

因为两只蚂蚁不能同时在一个除去根节点的节点上，

所以对于每一棵子树，

不能使深度相同的两个叶节点同时到达当前子树的根节点。

那么可以对于根节点 $1$ 的每一棵子树对每个叶子节点的深度进行排序，

设 $f_i$ 表示当前子树前 $i$ 个叶节点的蚂蚁爬到根节点需要的步数，

则 $f_i=\max( f_i , f_{i-1}+1 ) $.

因为没有不能同时到达根节点这一要求，

那么对于每棵子树，

设此子树有 $m$ 个叶子节点，

最终答案即为所有 $f_m$ 的最大值。

时间复杂度 $O(n \log n) $.

$Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct Edge
{
    int to,next;
}edge[1000010];
int head[1000010];
int deep[500010];
int cnt=1;
int ans;
int now;
void add(int u,int v)
{
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
void dfs(int root,int fa,int dep)
{
	bool vis=0;
	for(int i=head[root];i;i=edge[i].next)
	{
		if(edge[i].to==fa)
		{
			continue;
		}
		vis=1;
		dfs(edge[i].to,root,dep+1);
	}
	if(!vis)
	{
		deep[++now]=dep;
	}
}
void dp()
{
	for(int i=head[1];i;i=edge[i].next)
	{
		now=0;
		dfs(edge[i].to,1,1);
		sort(deep+1,deep+now+1);
		for(int i=1;i<=now;i++)
		{
			deep[i]=max(deep[i],deep[i-1]+1);
		}
		ans=max(ans,deep[now]);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dp();
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：jzh817 (赞：0)

对于每一个父节点为1的子树，只需求出它们每一个点的深度，进行sort，然后在进行dp

因为每一个结点只允许有一只蚂蚁，对于同一个父节点下的蚂蚁，只能在上一只蚂蚁出发后1秒出发，也会晚到1秒，不难想出方程dp[j]=max(dp[j],dp[j-1]+1);

放代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read(){
	ll a=0,b=getchar(),c=1;
	while(!isdigit(b))c=b=='-'?-1:1,b=getchar();
	while(isdigit(b))a=a*10+b-'0',b=getchar();
	return a*c;
}
struct edge{
	int to,next;
}e[1000005];
int n,ab,ans,dp[500005],h[500005];
void add(int x,int y){
	ab++,e[ab]={y,h[x]},h[x]=ab;
}
void dfs(int x,int y,int d){
	bool z=true;
	for(int i=h[x];i;i=e[i].next)
		if(e[i].to!=y)z=false,dfs(e[i].to,x,d+1);
	if(z)dp[ab]=d,ab++;
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	for(int i=h[1];i;i=e[i].next){
		ab=0,dfs(e[i].to,1,0);
		sort(dp,dp+ab);
		for(int j=1;j<ab;j++)
			dp[j]=max(dp[j],dp[j-1]+1);
		ans=max(ans,dp[ab-1]+1);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：NATO (赞：0)

哎哎哎，主播 2200 做 1h，有点耻辱，记录一下。

### 思路浅析：

首先一眼发现根节点的各个子树独立，算出每个子树的最大时间取个 $\max$ 即可。

考虑一个菊花的情况，发现这个东西实际上相当于一条链上每个点有个蚂蚁。

然后？...主播被创了 1h 呢！

考虑一个子树内的点最后蚂蚁必然都会走一个非根节点的点，故某两个蚂蚁深度只要相同必然撞上。考虑两蚁相撞的代价，考虑此时我任意让一个蚁上去没有任何区别，留下的蚂蚁时间 $+1$ 后继续和其它蚂蚁合并即可，整个子树就可以抽象为上文蚂蚁链。

发现是一个按子树叶节点深度排序后将之前所用最大时间 $+1$ 与当前深度取 $\max$ 的事情，意义既是我不断加入更深的蚂蚁，如果我的深度小于之前蚂蚁链的长度 $+1$，意味着我会和之前某只蚁冲上，链长 $+1$，否则链长为我的深度。

时间复杂度 $O(n\log n)$，瓶颈在于排序。

#### 参考代码：


```cpp
#include<bits/stdc++.h>
#define INF 214748364719260817ll
#define ll long long
using namespace std;
ll n;
ll head[500005],cnt;
struct ed
{
	ll v,next;
}edge[1000005];
void add(ll u,ll v)
{
	edge[++cnt].v=v;edge[cnt].next=head[u];head[u]=cnt;
	edge[++cnt].v=u;edge[cnt].next=head[v];head[v]=cnt;
}
ll dp[500005],dep[500005],cot;
void dfs(ll id,ll fa)
{
	bool ok=0;
	dep[id]=dep[fa]+1;
	for(ll i=head[id];i;i=edge[i].next)
	{
		ll v=edge[i].v;
		if(v==fa)continue;
		ok=1;
		dfs(v,id);
	}
	if(!ok)	dp[++cot]=dep[id];
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	ll u,v;
	for(ll i=1;i<n;++i)cin>>u>>v,add(u,v);
	ll res=0;
	for(ll i=head[1];i;i=edge[i].next)
	{
		ll v=edge[i].v;
		cot=0;
		dfs(v,1);
		sort(dp+1,dp+1+cot);
		ll ans=0;
		for(ll j=1;j<=cot;++j)ans=max(ans+1,dp[j]);
		res=max(res,ans);
	}
	cout<<res<<'\n';
}
```

---

