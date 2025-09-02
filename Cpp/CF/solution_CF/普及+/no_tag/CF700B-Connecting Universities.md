# Connecting Universities

## 题目描述

树之王国是一个由n-1条双向路连接着n个城镇的国家，任意两个城镇间都是联通的。

在树之王国共有2k所大学坐落于不同的城镇之中。

最近，树国总统颁布了一项在大学间建立高速信息网络的法案。教育部部长以他自己的方式理解了这项法案，他发现用电缆连接各所学校是绰绰有余的。形式上来说，这项法案安排的任务的确被完成了！(贪官...)

为了能尽可能多地获取财政预算，部长打算把大学分成一对一对的，使得在各所学校间建立连接所需的电缆最长。换句话说，k对大学间的距离总和越大越好。

帮助部长完成这个任务。当然了，每所大学不能重复出现在多对里。你可以认为每条路的长度均为1。

## 说明/提示

下图展示了在样例一的一种可能的结果。如果你把坐落于1号城镇的大学和坐落于6号城镇的大学连接在一起，把坐落于2号城镇的大学和坐落于5号城镇的大学连接在一起，那么距离总和为6，在样例一中是最大距离总和。

![pic](https://cdn.luogu.org/upload/vjudge_pic/CF700B/d24b24140d15e90d634b3c0f9f8b570ac75746f9.png)

## 样例 #1

### 输入

```
7 2
1 5 6 2
1 3
3 2
4 5
3 7
4 3
4 6
```

### 输出

```
6
```

## 样例 #2

### 输入

```
9 3
3 2 1 6 5 9
8 9
3 2
2 7
3 4
7 6
4 5
2 1
2 8
```

### 输出

```
9
```

# 题解

## 作者：Heartlessly (赞：14)

## Description


给定一棵 $n$ 个点的树，树上每条边的边权都是 $1$，现在给定 $2k$ 个点需要两两配对，配对的价值为两点的距离，求最大价值和。

------------

## Solution

因为要使最后价值和最大，所以我们考虑贪心。
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF700B/d24b24140d15e90d634b3c0f9f8b570ac75746f9.png)

就样例而言，我们很显然发现左边的点与右边的点两两配对是最优的。

对于每一条边，我们如果统计出它左边的大学数量为 $x$，右边的大学数量为 $y$，那么该边的价值就是 $\min(x,y)$，对每条边都如此处理，遍历一遍即可，时间复杂度为 $O(n)$。在遍历的时候，其实只需要知道每个点一边大学的数量，另一边大学的数量就是 **大学总数-一边大学的数量**，我的代码以求左边为例。

------------


## Code
```cpp
#include <bits/stdc++.h>
#define next next_
using namespace std;
typedef long long LL;

template < class T > inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
    x = f ? -x : x;
}

const int maxN = 2e5 + 10;

int n, m, k, u, v, tot, head[maxN], to[maxN << 1], next[maxN << 1];
LL ans, f[maxN];//最大答案有可能爆int

inline void addEdge(int u, int v) {
	next[++tot] = head[u];
	to[tot] = v;
	head[u] = tot;
}//连边

void dfs(int from, int x) {
	for (int i = head[x]; i; i = next[i]) {
		int y = to[i];
		if (y == from) continue;
		dfs(x, y);
		f[x] += f[y];
		ans += min(f[y], (LL)(k - f[y]));
	}
}//dfs遍历每一条边，from表示边的起点，x表示边的终点

int main() {
	read(n), read(k);
	k <<= 1;//题目给的是大学数量的一半
	for (int i = 1; i <= k; ++i) { read(m); f[m] = 1; }//f[i]表示点i及它左边大学的数量
	for (int i = 1; i < n; ++i) { read(u), read(v); addEdge(u, v), addEdge(v, u); }
	dfs(0, 1);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：dottle (赞：9)

不是官方题解的贪心为什么一定可以构造出方案，这里介绍另一种贪心方法。

首先为树确定一个根，那么两点之间的距离就应该是其深度之和减去其最近公共祖先的深度。关键点的深度是确定的，那么我们要最小化的就是所有匹配的点的最近公共祖先的深度之和。

首先考虑根节点，我们求出其出边的所有子树中有多少个点，如果关键点最多的子树中关键点的数量小于总数的二分之一，那么我们一定可以将所有关键点两两配对，使得配对点的 lca 都是根节点；否则最大的那个子树中一定会有某些点必须在其内部匹配，设这个子树为 $u$。

那么我们记录好有多少个子树 $u$ 外的关键点，设为 $d$，我们递归进入子树 $u$，同样地在求 $u$ 的出边的子树有多少个关键点。显然，我们会让关键点最多的那棵子树中的点与 $u$ 外的关键点匹配。如果匹配后，其仍然大于总数的二分之一，那我们更新 $d$，继续递归；否则终止递归。

在这个过程中，我们可以很方便地统计出在每一个子树匹配了多少对关键点，从答案中减去它们即可。注意这时候每个关键点都会被多减一次，向答案中加上 $2k$ 即可。


```cpp
#include<bits/stdc++.h>
#define int long long
const int N=500050;
using namespace std;

#define _to e[i].to
#define fore(k) for(int i=hd[k];i;i=e[i].nx)
struct edge{
    int to,nx;
}e[N];int hd[N],S;
void add(int fr,int to){
    e[++S]=(edge){to,hd[fr]},hd[fr]=S;
}

int sz[N],dp[N],a[N],ans;
void dfs(int k,int fa){
	sz[k]=a[k],dp[k]=dp[fa]+1;
	ans+=dp[k]*a[k];
	fore(k)if(_to!=fa)
		dfs(_to,k),sz[k]+=sz[_to];
}

void solve(int k,int fa,int d){
	ans-=(sz[k]-d);
	int sm=0,mx=0;
	fore(k)if(_to!=fa)
		mx=sz[_to]>sz[mx]?_to:mx;
	if(sz[mx]-d>sz[k]-sz[mx])
		solve(mx,k,d+sz[k]-sz[mx]);
}

main(){
	dp[0]=-1;
	int n,k;cin>>n>>k;
	for(int i=1;i<=k*2;i++){
		int x;cin>>x;
		a[x]=1;
	}
	for(int i=1;i<n;i++){
		int x,y;cin>>x>>y;
		add(x,y),add(y,x);
	}
	dfs(1,0);
	solve(1,0,0);
	cout<<ans+2*k<<endl;
}
```

---

## 作者：Cesare (赞：6)

$update:$  修改部分代码以及 $Latex$ 。

记录一点想法。

对于样例，我们发现两两配对的大学之间所经过的边，重合的越多，答案就越大。

所以说对于一条边，我们将它划分为两个集合：$ x,\ 2k - x $ 。 

为了使重合的边数更多，我们考虑贪心去配对边。

然后根据样例，我们已经$ yy $出了正确的做法：对于每条边，选择去对面的集合去配对。

也就是$ min (dis[x],\ 2k - dis[x]) $。

然后 $dfs$ 一遍，用 $Ans$ 不断累加当前最优的答案 。
$$Ans = \sum min (dis[x],\ 2k - dis[x])$$

就做完了。 

```cpp
#include<bits/stdc++.h>
//#include"Bignum/bignum.h"
//#define lll bignum
#define re register
#define For(i, j, k) for(re int i = j; i <= k; i++)
#define foR(i, j, k) for(re int i = j; i >= k; i--)
using namespace std;
typedef long long ll;
const ll N = 200011;

ll n, k, cnt, ans, dis[N], head[N];

struct node {
	ll to, next;
} e[N << 1];

inline void add ( ll u, ll v ) { 
	e[++cnt].to = v, e[cnt].next = head[u], head[u] = cnt; 
	e[++cnt].to = u, e[cnt].next = head[v], head[v] = cnt; 
}

namespace IO {

	#define dd ch = getchar()
	inline ll read() {
		ll x = 0; bool f = 0; char dd;
		for (; !isdigit (ch); dd) f ^= (ch == '-');
		for (; isdigit (ch); dd)  x = (x << 3) + (x << 1) + (ch ^ 48);
		return f? -x: x;
	}
	#undef dd

	inline void write( ll x ) {
		if ( x < 0 ) putchar ('-'), x = -x;
		if ( x > 9 ) write ( x / 10 ); putchar ( x % 10 | 48 );
	}

	inline void wrn ( ll x ) { write (x); putchar (' '); }

	inline void wln ( ll x ) { write (x); putchar ('\n'); }

	inline void wlnn ( ll x, ll y ) { wrn (x), wln (y); }

}

using namespace IO;

inline void dfs ( ll x, ll fa ) {
	for (re int i = head[x]; i; i = e[i].next) 
		if ( e[i].to != fa ) dfs ( e[i].to, x ), dis[x] += dis[e[i].to];
	for (re int i = head[x]; i; i = e[i].next) 
		if ( e[i].to != fa ) ans += min ( dis[e[i].to], k - dis[e[i].to] );
}

ll u, v;

int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	memset (head, -1, sizeof (head));
	n = read(), k = read() << 1; For ( i, 1, k ) dis[read()] = 1;
	For ( i, 1, n - 1 ) u = read(), v = read(), add (u, v); dfs (1, 0); 
	return wln( ans ), 0;
}

/*

*/

```

---

## 作者：fighter (赞：5)

# CF700B 【Connecting Universities】

​	~~我最喜欢码量不大的思维题啦！！！~~

​	首先，因为有$n$个点和$n-1$条边，那么这显然是一棵树，题目要求我们把树上的$2k$个点两两配对，使得每一对点的路径距离和最大。

​	这道题如果从“配对”这个角度思考的话并不容易，因为没有一种显然正确的贪心方法来进行配对。于是我们从边的角度来思考。

​	对于每一条边，如果想让距离和最大，那么显然要让被这一条边隔开的剩余的两个连通分量中的大学穿过这一条边进行配对。

![样例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF700B/d24b24140d15e90d634b3c0f9f8b570ac75746f9.png)

比如我们看这个样例，对于边$(3,4)$，如果让1,2自己配对，5,6自己配对，肯定不如1穿过$(3,4)$和6配对，2穿过$(3,4)$和5配对。所以对于每一条边，设$u,v$分别为这条边隔开的连通块中拥有的大学数量，那么显然最多有$min(u,v)$个大学能够穿过这条边进行配对，于是我们的$ans$累加上能配对的数量即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAX 200005
using namespace std;

int n, k, cnt;
int num[MAX], d[MAX];
int head[MAX], Next[MAX*2], vet[MAX*2];

void add(int x, int y){
    cnt++;
    Next[cnt] = head[x];
    head[x] = cnt;
    vet[cnt] = y;
}

void dfs(int x, int fa){
    d[x] = d[fa]+1;
    for(int i = head[x]; i; i = Next[i]){
        int v = vet[i];
        if(v == fa)	continue;
        dfs(v, x);
        num[x] += num[v];
    }
}

int main()
{
    cin >> n >> k;
    k *= 2;
    int x, y;
    for(int i = 1; i <= k; i++){
        scanf("%d", &x);
        num[x] = 1;
    }
    for(int i = 1; i < n; i++){
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dfs(1, 0);
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        for(int j = head[i]; j; j = Next[j]){
            int v = vet[j];
            if(d[v] < d[i]){
                v = i;
            }
            ans += (ll)min(k-num[v], num[v]);
        }
    }
    cout << ans/2 << endl;
    
    return 0;
}
```



---

## 作者：SunsetSamsara (赞：1)

## 思路

贪心

## 分析

首先看到这道题就考虑贪心。

我们观察图中每一个点，我们要尝试把这个点与最远点配对起来。那么，我们就会发现配对的点永远是左边、右边配对。

**下一步就有一点思维难度了：如何处理配对的点距离之和呢？**

考虑为每一条边赋权值。对于每一条边，如果它左边的大学数量为 $x$，右边的大学数量为 $y$，因为这一条边能为左右两边**每一对能配对的点**提供 $1$ 的贡献，所以该边的价值就是 $\min\{x, y\}$。

而容易发现 $y = 2k-x$，所以 dfs 一遍就可以跑出 $x$，算出 $y$ 了。

最后将所有权值求和得到答案。

## 代码

```cpp
#include <bits/stdc++.h> 
#define lld long long
using namespace std;
int n, k;
lld cnt, ans;
lld dis[200010], head[200010];
struct node {
	int to, nxt;
} e[400010];
inline void addedge(int u, int v) {
	e[++ cnt].to = v, e[cnt].nxt = head[u], head[u] = cnt;
	e[++ cnt].to = u, e[cnt].nxt = head[v], head[v] = cnt;
}
inline void dfs(int x, int fa) {
	for (int i = head[x]; i; i = e[i].nxt) if (e[i].to != fa) dfs(e[i].to, x), dis[x] += dis[e[i].to];
	for (int i = head[x]; i; i = e[i].nxt) if (e[i].to != fa) ans += min(dis[e[i].to], k - dis[e[i].to]); // 因为 k 已经乘上 2 了，所以这里相当于 ans = min(x, 2k - x)
}
int u, v;
int main() {
	scanf("%d%d", &n, &k);
	k <<= 1;
	int x;
	for (int i = 1; i <= k; ++ i) scanf("%d", &x), dis[x] = 1;
	for (int i = 1; i < n; ++ i) scanf("%d%d", &u, &v), addedge(u, v);
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Flan (赞：1)

> 给定一棵树和树上的 $2k$ 个点。将 $2k$ 个点两两配对，使每对距离的和最大。

以任意点为根，设编号为 $i$ 的节点的深度为 $\text{dep}_i$。对于配对的一对点 $i,j$，它们的距离是 $\text{dep}_i+\text{dep}_j-2\text{dep}_{\operatorname{LCA}(i,j)}$。

$\text{dep}_i$ 和 $\text{dep}_j$ 可以事先计入答案，于是我们的任务转化为最小化 $\sum\text{dep}_{\operatorname{LCA}(i,j)}$。按深度从小到大遍历节点：设当前节点含有 $s$ 个大学，当前节点的子树中含有大学数最多的含有 $m$ 个大学，若 $m\le s-m$，则该节点中所有大学都可以以当前节点作为最近公共祖先两两配对；否则继续遍历含最多大学的那个节点。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;
const int MAXN = 2e5 + 19;

int n, k;
std::vector<int> to[MAXN];

bool isU[MAXN];
int size[MAXN], dep[MAXN];
ll ans;

void dfs(int node, int f){
	dep[node] = dep[f] + 1;
	if(size[node]) ans += dep[node];
	for(int i : to[node])
		if(i != f){
			dfs(i, node);
			size[node] += size[i];
		}
}

void solve(int node, int f, int del){
	int max = 0, nax = 0;
	for(int i : to[node])
		if(i != f && size[i] > max)
			max = size[i], nax = i;
	max = max - (size[node] - max);
	max -= del;
	if(max > 0){
		ans -= (ll)dep[node] * (size[node] - max - del);
		solve(nax, node, size[nax] - max);
	}
	else ans -= (ll)dep[node] * (size[node] - del);
}

int main(){
	std::scanf("%d%d", &n, &k);
	for(int i = 1; i <= k * 2; ++i){
		int tmp; std::scanf("%d", &tmp);
		++size[tmp], isU[tmp] = 1;
	}
	for(int i = 2; i <= n; ++i){
		int u, v; std::scanf("%d%d", &u, &v);
		to[u].push_back(v), to[v].push_back(u);
	}
	
	dfs(1, 0);
	solve(1, 0, 0);
	
	std::printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：demon_yao (赞：1)

## 题目大意
有一棵$n$个节点的树，其中有$2k$个点要两两配对，求每对点配对的距离之和的最大值
## 思路
思路很妙,但比较难想。
显然，使用暴力配对时间复杂度会爆炸。所以我们想到了什么：贪心！

我们考虑计算每个边的贡献，并对之求和。那么具体怎么贪心去配对边呢？瞎yy一下，我们会发现，对于每条边，选择去对面的集合去配对它，那么显然权值之和会是最大的。我们可以设一条边左边的要配对的点的总数为$p$,那么显然它右边的的点的集合为$2k-p$,那么这条边的贡献就是$min(p,2k-p)$。

在这之后我们就可以dfs来累加答案啦qwq$ans=(\sum{min(p,2k-p)})$

这样，我们就把这道题目做完了！qwq




代码很简洁，应该比较好理解。
```cpp


#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
struct e{int  v,w,nxt;}a[500005];int head[500005],cnt=0;int dis[500005];long long maxn=0;
int n,k;
int b[500005];
void add(int u,int v){a[++cnt].v=v;a[cnt].nxt=head[u];head[u]=cnt;}
void dfs(int x,int fa){
	for(int i=head[x];i;i=a[i].nxt){
		if(a[i].v!=fa){
			dfs(a[i].v,x);b[x]+=b[a[i].v];
		}
	}maxn=maxn+min(b[x],2*k-b[x]);
}
signed main()
{
	//freopen("ribbon.in","r",stdin);
	//freopen("ribbon.out","w",stdout);
	cin>>n>>k;int u,v,lin;
	for(int i=1;i<=2*k;i++){scanf("%lld",&lin);b[lin]++;}
	for(int i=1;i<n;i++){
		scanf("%lld %lld",&u,&v);add(u,v);add(v,u);
	}
	dfs(1,0);
	cout<<maxn;
	return 0;
}
```


---

## 作者：nytyq (赞：0)

## 具体做法：

考虑一个朴素的贪心。

考虑到现在使得 $2k$ 个城市两两匹配求距离最大，则有考虑到设置一个根，分为左连通块和右连通块，因而考虑到使得匹配最大化距离和，从而只匹配左连通块中与右连通块中的大学数量，设左边有 $p$ 个大学，右边有 $q$ 个大学，则一共匹配 $\min(p,q)$ 个大学，答案为 $\sum\min(p,q)$。

代码在 [here](https://www.luogu.com.cn/paste/8ckmg2v1)。

---

## 作者：huhangqi (赞：0)

看题目如果直接从如何配对的角度去考虑的话，还是比较困难的。

但是我们不只能从点的角度入手，我们也可以尝试从边的角度入手。

一条边如果要被两个点之间的最短路径经过，那么这两个点一定分别分布在这一条边的两边。

由于我们选择的是最长路径，而任意两个点之间的简单路径只有一条。

那么很容易就可以发现为了使长度最大，一定会使节点较小的一端连接到另一端，那么每一条边的贡献就是两端的较小值了。

原因也很简单，假设我们目前考虑两个点在同一侧，那么它们的距离就是两个点到最近公共祖先的距离，而由于我们只是使用了一条边分开了两部分，那么这一条边一定比这个祖先要远，所以在同一侧连接的收益一定是低于不同侧连接的收益的。

代码非常短：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[200005],siz[200005],ans;
vector<int> e[200005];
void dfs(int p,int fa){
	for(int i:e[p]){
		if(i==fa)continue;
		dfs(i,p);
		siz[p]+=siz[i];
	}
	ans+=min(2*k-siz[p],siz[p]);
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=2*k;i++)cin>>a[i],siz[a[i]]=1;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}
``````

---

## 作者：Beihai_Jiang (赞：0)

# Connecting Universities

[Connecting Universities - 洛谷 | 计算机科学教育新生态](https://www.luogu.com.cn/problem/CF700B)

## 题意

给定一棵无根树，其中有 $k$ 个点，试将其两两配对，使配对的两点距离之和最大。

## 100pts

**贪心**

从点的配对下手，发现有些困难。

分析样例，考虑从**边的角度**下手。

对于每一条边，为使距离之和最大，就要使经过该边的次数尽可能多。

记该边以左的大学数为 $x$，以右的大学数为 $y$。

**因为经过该边后要两两配对，所以经过的最多次数为 $\min(x,y)$**。

（若大于 $\min(x,y)$，则一定存在至少一个点无法两两配对，鸽巢原理）。

代码实现上，以 $1$ 为根节点，记 $f_u$ 为以 $u$ 为根的子树中大学的数量。

对于一条边，经过其的次数为 $\min(f_u,n-f_u)$，$u$ 为该边的儿子端点（即深度较大的端点）。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5;
int n,k;
ll f[N],ans;
unordered_map<int,bool> uni;
int cnt,head[N];
struct Edge{
	int to,next;
}a[N<<1];
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0' || ch>'9')
		ch=getchar();
	while(ch>='0' && ch<='9')
		x=10*x+ch-'0',ch=getchar();
	return x;
}
void AddEdge(int x,int y){
	cnt++;
	a[cnt].to=y;
	a[cnt].next=head[x];
	head[x]=cnt;
}
void solve(int u,int fa){
	if(uni[u]) f[u]++;
	for(int i=head[u];i;i=a[i].next){
		int v=a[i].to;
		if(v==fa) continue;
		solve(v,u);
		f[u]+=f[v];
		ans+=min(f[v],2*k-f[v]);
	}
}
int main(){
	n=read(),k=read();
	for(int i=1;i<=k<<1;i++){
		int u=read();
		uni[u]=1;
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		AddEdge(u,v);
		AddEdge(v,u);
	}
	solve(1,0);
	cout<<ans;
	return 0;
}
```

注：*map* 基于红黑树，元素有序，适合需要排序或稳定查询性能的场景；**unordered_map** 基于哈希表，**查询速度快**，但元素**无序**，适用于查找效率优先的情况。

---

## 作者：_xxxxx_ (赞：0)

### 题意

给出一棵树，树上有 $2k$ 个黑点，你要将他们分为 $k$ 组，使得每组距离之和最大。

### 分析

每组距离**之和**最大可以转换为尽量使每组距离最大。

我们可以在剩余的点中找最远的分组，可是点到点不好进行操作。

我们换一个思路，既然这是一棵树，那对于一条边而言，如果他的上面和下面都有给定点，那他一定会被走过，也就是对答案有贡献。

令一条边上面的给定点为 $x$，下面为 $y$，最佳匹配一定是使尽量多的点走过这条边，因此每条边的贡献为 $\min(x,y)$。

跑一遍 `dfs`，记录下来给出点的数量，另一边未遍历到的就是总点数减去遍历到的点了。

### 代码

```cpp
#include <iostream>
#include <cmath>
#include <map>
#include <string.h>
#include <queue>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int N = 4e5 + 10;
const int INF = 0x3f3f3f3f;
int n, k;
int head[N], ne[N], to[N], id;
void add(int x, int y)
{
	to[++id] = y;
	ne[id] = head[x];
	head[x] = id;
}
int ans;
int num[N];
void dfs(int u, int fa)
{
	for(int i = head[u]; i ; i = ne[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs(v, u);
		num[u] += num[v];
		ans += min(num[v], (k * 2 - num[v]));
		//把能走的都走了 
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for(int i = 1; i <= 2 * k; i++) 
	{
		int x;
		cin >> x;
		num[x] = 1;
	}
	for(int i = 1; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		add(x, y);
		add(y, x);
	}
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：wyyqwq (赞：0)

### B.
对每个点分开来计算被经过了多少次，发现只要有两个点在它的不同侧就一定会经过这个点，然后就 dfs 一遍即可。

设一条边左边的点的数量为 $x$，答案即为 $\sum \min(x, 2k - x)$。

``` c++
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e6 + 7;
int p[N];
struct edge {
    int next, to;
}e[N];
int head[N], ecnt;
void addedge(int u, int v) {
    e[++ ecnt].to = v;
    e[ecnt].next = head[u];
    head[u] = ecnt;
}
int ans;
int cnt[N];
void dfs(int u, int fa) {
    for(int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if(v == fa) continue;
        dfs(v, u);
        cnt[u] += cnt[v];
    }
}
signed main() {
    memset(head, -1, sizeof head);
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= 2 * k; i ++) cin >> p[i], cnt[p[i]] = 1;

    for(int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }
    dfs(1, 0);
    int ans = 0;
    for(int i = 1; i <= n; i ++) ans += min(cnt[i], 2 * k - cnt[i]);
    cout << ans << endl;
}
```

---

