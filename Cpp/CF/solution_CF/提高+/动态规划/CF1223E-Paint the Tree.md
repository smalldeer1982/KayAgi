# Paint the Tree

## 题目描述

给定一个有 $N$ 个节点的树，每个节点要染上 $K$ 种颜色，有无数多种颜色，每种颜色最多用两次。当一条边的两个节点附上的颜色中有至少一种相同颜色时，这条边的贡献就是它的权值，否则贡献为 $0$。

求这颗树所有边最大的贡献之和。

## 说明/提示

$1\le T\le 5\cdot 10^5,1\le N,K\le 5\cdot 10^5$，保证所有 $N$ 之和小于等于 $5\cdot 10^5$。

## 样例 #1

### 输入

```
2
4 1
1 2 5
3 1 2
3 4 3
7 2
1 2 5
1 3 4
1 4 2
2 5 1
2 6 2
4 7 3
```

### 输出

```
8
14
```

# 题解

## 作者：__charlie520__ (赞：5)

首先注意到如果一个颜色分配给的两个点如果不相邻的话，这种颜色就被浪费了。  
我们完全可以给他们涂不一样的颜色。  
所以一个颜色分配给的两个点一定是相邻的。  
从一个点出发的被“渗透”的边数不会超过 $k$。  
也就是求树的一个最大匹配，但是每个点最多可以被匹配 k 次。  
思考 $k=1$ 的做法。  

$k>1$ 时方法是一样的。  
每个节点 $u$ 有两种状态：  
- $0$ 还剩余一次匹配可以留给 $u$ 的父亲；  
- $1$ 已经和子节点匹配了 $k$ 次，没有给父亲留机会。 

枚举 $u$ 的子节点 $v[1], v[2], \dots, v[s]$ 进行转移。  
$f[u][0]$：最多可以匹配 $k-1$ 个孩子。  
$f[u][1]$：最多可以匹配 $k$ 个孩子。

$0$ 还剩余一次匹配可以留给 u 的父亲。  
$1$ 已经和子节点匹配了 k 次，没有给父亲留机会。  
如何选择子节点 $v[i]$ 和 u 进行匹配呢？  
假设所有的 $v[i]$ 都没有给 $u$ 留机会，即 $v[i]$ 的状态全都是 $1$。  
那么 $f[u][0]$ 和 $f[v][1]$ 至少是 $\sum^{s}_{i=1}f[v_i][1]$。  
如果 $u$ 和 $v[i]$ 匹配，那么原来的收益是 $f[v[i]][1]$，现在就变成了 $f[v[i]][0] + w(u, v[i])$，带来的变化是 $f[v_i][0]+w(u,v_i)-f[v_i][1]$。

初始值 $f[u][0]=f[u][1]=\sum^{s}_{i=1}f[v_i][1]$。  
对于 $s$ 个孩子，计算 $d[i] = f[v_i][0]+w(u, v_i)-f[v_i][1]$。  
如果 $d[i] > 0$ 那么和 $v[i]$ 匹配可以带来更多的收益，  
如果 $d[i] < 0$ 那么和 $v[i]$ 不匹配更优。  
对 $d$ 从大到小排序，对于 $f[u][0]$ 取 $d$ 的前 $k-1$ 位更新。  
对于 $f[u][1]$ 取 $d$ 的前 $k$ 位更新。  
时间复杂度 $O(n \log n)$。

AC CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while(c<'0' || c>'9'){if(c=='-')f=-1; c = getchar();}
	while(c>='0'&&c<='9'){x = x*10+c-'0'; c = getchar();}
	return x*f;
}

const int N = 500100;
int n, k;

vector< pair<int,int> > g[N];

long long f[N][2];

void dfs(int u, int fa) {
	vector<long long> d;
	d.clear();
	f[u][0] = f[u][1] = 0;
	for (int i = 0;i < g[u].size();i++){
		int v = g[u][i].first, w = g[u][i].second;
		if (v == fa) continue;
		dfs(v, u);
		f[u][0] += f[v][1];
		f[u][1] += f[v][1];
		d.push_back(-(w + f[v][0] - f[v][1]));
	}
	sort(d.begin(), d.end());
	for (int i = 0;i < d.size() && i < k;i ++){
		long long D = -d[i];
		if (D <= 0) break;
		if (i < k - 1) f[u][0] += D;// i = 0->k-2
		f[u][1] += D;// i = 0->k-1
	}
}
void ae(int x, int y, int z) {
	g[x].push_back(make_pair(y, z));
}

void solve() {
	n = read(), k = read();
	for(int i = 1;i <= n;i++) g[i].clear();
	int x, y, z;
	for(int  i= 1;i < n;i++) {
		x = read(), y = read(), z = read();
		ae(x, y, z);
		ae(y, x, z);
	}
	dfs(1, 0);
	printf("%lld\n", f[1][1]);
}

int main() {
	int tc;
	tc = read();
	while(tc--)
		solve();
	return 0;
}

```



---

## 作者：wangyibo201026 (赞：3)

## 前言

作者已经快半年没做过题了，并且去年 CSP 也寄了，希望这篇题解给所有读者保佑qwq。

## 思路代码混讲

我们把这道题加工一下：

对于每个点可以选择 $k$ 种权值，每种权值只能选两次，如果一条边的两个点中有一种权值相同，则把这条边的权值加到答案，问你答案的最大值。

题面很好理解，刚开始看到可以选择父亲的边，就立马着手换根（证明我菜），结果没写出来qwq。看了一眼题解，才感觉很一眼。

我们设状态 $f_{i, {0/1}}$，$f_{i, 0}$ 表示这个点与儿子节点最多只连 $k - 1$ 条边，再给父亲留一条边（选 $k - 1$ 个儿子显然最优），$f_{i, 1}$ 则表示不留给父亲边，与儿子最多连 $k$ 条边。其实上面的说法不严谨，如果儿子没有那么多个，那么就只要搞最多的就行了。

初步转移：$f_{i, 0} = f_{i, 0} + f_{son, 1}, f_{i, 1} = f_{i, 1} + f_{son, 1}$。因为我们初步考虑什么儿子都不选。

我们考虑是否所有的儿子都要选择？其实是不需要的。此时我们考虑加入一个儿子的价值 $tmp = f_{son, 0} + w + f_{son, 1}$。我们把前 $k - 1$ 大的可以加到 $f_{i, 0}$ 里，把前 $k$ 大的可以加到 $f_{i, 1}$ 里。如果儿子没那么多就没必要了，但是如果某一个 $tmp <= 0$，则不要选，因为显然不优。

这部分的代码：

```cpp
void dfs(int x, int fa){
  f[x][0] = f[x][1] = 0;
  priority_queue<int, vector<int> > q; // vector 加快，找出前 k 个
  for(int i = head[x]; i; i = edges[i].next){
    if(edges[i].to != fa){
      dfs(edges[i].to, x);
      f[x][0] += f[edges[i].to][1];
      f[x][1] += f[edges[i].to][1]; // 转移
      q.push(f[edges[i].to][0] + edges[i].w - f[edges[i].to][1]);
    }
  }
  int cnt = 0;
  while(!q.empty() && cnt < k){ //注意这里 cnt 一定小于 k，因为等于 k 时会多循环一次
    ++cnt;
    int tmp = q.top();
    q.pop();
    if(tmp <= 0){
      break;
    }
    if(cnt <= k - 1){   //加代价
      f[x][0] += tmp;
    }
    f[x][1] += tmp;
  }
}
```

最后这个的复杂度大概是 $O(n\log_2 n)$，很玄学。

注意要开 long long 哦。

---

## 作者：caidzh (赞：3)

~~贪心+动态规划连挂5次是什么感受？~~

这是一道很好的思维题，我将分三步来讲解这道题

### $Step.1$ 优美地转化题意

首先看题：一个点可以附上$k$个颜色，有无数种颜色，一个边有贡献当且仅当两个相连点有同样的一种或多种颜色

那么我们考虑对于一个点，对其连出的若干条边，有几条边会对答案有贡献？显然是最多$k$条，由于边权全为正，边我们当然是取得越多越好

所以题意优美地变为：在树上选取若干条边，需要保证加入这些边后没有一个点的度超过$k$，问最大边权和

因为有无数种颜色，所以我们不用担心现在子树的抉择会对其他子树产生影响。对于这个简明的题意，接下来我们考虑树形$dp$

### $Step.2$ 如何定义状态

你会发现这个状态似乎不好定义，因为颜色无限，而且权值在边上

我们仍然有办法解决这个问题：容易想到用$f[i][0/1]$表示在以$i$为根的子树，选与不选$i$的父边时（$1$为选，$0$为不选）可以获得的最大价值

为什么能想到这样做？因为这条父边选与不选是会对这棵子树内的选择情况产生影响的，影响在于$i$这个点度数的限制

状态转移的初步想法是什么？因为子树间互不相干，我们容易想到将每棵子树内的权值相加，再加上选择父边的贡献来得到$f[i][0/1]$的值

### $Step.3$ 如何进行状态转移

我们发现，对于$f[i][1]$，连向儿子的边最多只能选择$k-1$条，而对于$f[i][0]$，则可以选择$k$条

选择一条连向儿子的边的贡献是$f[son][1]+dis$，而不选则是$f[son][0]$

为了得到最大的贡献，我们必须选择最优秀的那几条边，即选择$f[son][1]+dis-f[son][0]$最大的那几条，因此转移之前获取信息后排序后加入贡献即可

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=500010;
int n,T,k,head[maxn],cnt,deg[maxn],used[maxn];LL f[maxn][2];
//f[i][1]选择父边，f[i][0]不选择父边 
struct Edge{int nxt,to,dis;}edge[maxn<<1];
void add_edge(int x,int y,int z){edge[++cnt].nxt=head[x];edge[cnt].to=y;edge[cnt].dis=z;head[x]=cnt;}
struct Node{int val,id;}A[maxn];
bool cmp(Node x,Node y){return x.val>y.val;}
void dfs(int x,int fa){
	int flag=1;
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;if(v==fa)continue;flag=0;dfs(v,x);
	}int tot=0;if(flag)return;
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;if(v==fa)continue;
		A[++tot].id=v;A[tot].val=f[v][1]+edge[i].dis-f[v][0];
	}sort(A+1,A+tot+1,cmp);
	for(int i=1;i<=min(k,tot);i++){
		if(A[i].val<=0)break;
		f[x][0]+=A[i].val+f[A[i].id][0];used[A[i].id]=1;
		if(i!=k)f[x][1]+=A[i].val+f[A[i].id][0];
	}if(k<=tot&&used[A[k].id])f[x][1]+=f[A[k].id][0];
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;if(v==fa)continue;
		if(used[v])continue;f[x][1]+=f[v][0];f[x][0]+=f[v][0];
	}
}
int main()
{
	T=read();
	while(T--){
		n=read();k=read();cnt=0;LL ans=0;
		for(int i=1;i<n;i++){
			int u=read(),v=read(),w=read();
			add_edge(u,v,w);add_edge(v,u,w);deg[u]++;deg[v]++;
		}dfs(1,0);for(int i=1;i<=n;i++)ans=max(ans,max(f[i][0],f[i][1]));cout<<ans<<endl;
		for(int i=1;i<=n;i++)head[i]=deg[i]=f[i][0]=f[i][1]=used[i]=0;
	}
	return 0;
}
```


---

## 作者：GIFBMP (赞：1)

首先补一下一个题目翻译里没有的限制条件：**每种颜色至多用两次**。

那么对于一个节点 $x$，显然至多 $k$ 条边对其有贡献。

那么我们分类讨论，记 $f_{x,0}$ 表示不选 $E(fa,x)$ 时 $x$ 的**子树**对它的贡献，$f_{x,1}$ 表示选 $E(fa,x)$ 时 $x$ 的**子树**对它的贡献。 

那么很显然，对于 $f_{x,0}$，至多会有 $k$ 个 $f_{son,1}$ 对其产生贡献，对于 $f_{x,1}$，至多会有 $k-1$ 个 $f_{son,1}$ 对其产生贡献。

为了方便转移，一开始我们记：

$$f_{x,0}=f_{x,1}=\sum f_{son,0}$$

然后我们考虑将某个 $f_{son,0}$ 替换成 $f_{son,1}$ 产生的贡献，很显然可以得出这个值为 $f_{son,1}+E(x,son)-f_{son,0}$。

但我们还要考虑一个条件，当 $f_{son,1}+E(x,son)-f_{son,0}\le 0$ 的时候，显然不能转移。

于是我们把这个贡献从大到小排序，取满足限制的转移即可。

$\Theta(n\operatorname{log}n)$。

Code:

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std ;
const int MAXN = 5e5 + 10 ;
typedef long long ll ;
struct edge {
	int v , w ;
	edge (int vv = 0 , int ww = 0) {v = vv ; w = ww ;}
} ;
int T , n , k ;
vector <edge> G[MAXN] ; 
ll f[MAXN][2] ; 
bool cmp (int a , int b) {
	return a > b ;
}
void dfs (int x , int fa) {
	vector <ll> tmp ;
	for (int i = 0 ; i < G[x].size () ; i++) {
		int v = G[x][i].v , w = G[x][i].w ;
		if (v == fa) continue ;
		dfs (v , x) ;
		f[x][0] += f[v][0] ;
		f[x][1] += f[v][0] ; 
		tmp.push_back (f[v][1] + w - f[v][0]) ;
	}
	sort (tmp.begin () , tmp.end () , cmp) ;
	for (int i = 0 ; i < tmp.size () && i < k ; i++) {
		if (tmp[i] <= 0) break ;
		if (i < k - 1) f[x][1] += tmp[i] ;
		f[x][0] += tmp[i] ;
	}
}
int main () {
	scanf ("%d" , &T) ;
	while (T--) {
		scanf ("%d %d" , &n , &k) ;
		for (int i = 1 ; i <= n ; i++) 
			G[i].clear () , f[i][0] = f[i][1] = 0 ;
		for (int i = 1 ; i < n ; i++) {
			int u , v , w ;
			scanf ("%d %d %d" , &u , &v , &w) ;
			G[u].push_back (edge (v , w)) ;
			G[v].push_back (edge (u , w)) ;   
		} 
		dfs (1 , 0) ;
		printf ("%lld\n" , f[1][0]) ;
	}
	return 0 ;
}
```

---

## 作者：thostever (赞：1)

很不错的树形 dp 题。

由于每个节点最多染 $k$ 种颜色，所以与这个节点相连且有贡献的边最多有 $k$ 个。

那么题目就转化成了：选择一些边，且对于任意节点来说与其相连且被选中的边的个数不超过 $k$ 个，求选中的边权和最大值。

容易证明，对于任意一种选择方法，都存在合法的染色方法。

------------

步入正题，我们令 $dp_{u,0/1}$ 表示在子树 $u$ 中，节点 $u$ 不能连 $k$ 条边/可以连 $k$ 条边时的最大权值和。

解释一下：只考虑 $u$ 及其子树。对于节点 $u$，我们要在与它相邻的边中选择一些边，那么我们分选的边的个数小于 $k$ 和小于等于 $k$ 两种情况。（即是否还有空去再连一条边）

考虑转移。对于节点 $u$ 和它的儿子节点 $v$ 来说，有连与不连两种选择。如果连，那么贡献为 $dp_{v,0}+w_i$。如果不连那么贡献为 $dp_{v,1}$。并且最多连 $k$ 个节点。（$dp_{u,0}$ 是 $k-1$ 个）

我们先假设 $u$ 与所有的子节点 $v$ 都不连接，贡献为 $\sum dp_{v,1}$。如果一个节点 $v$ 选择了连接，那么贡献将会增加 $dp_{v,0}+w_i-dp_{v,1}$。

那么我们只需要将 $dp_{v,0}+w_i-dp_{v,1}$ 丢进优先队列里，选择最大的 $k$ 个即可。**注意： 只能选贡献为正的。**

答案即为 $dp_{1,1}$。

~~十年 OI 一场空，不开 ll 见祖宗~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int head[500010],to[1000010],nxt[1000010],w[1000010],tot=0;
void add(int x,int y,int z)
{
	to[++tot]=y;
	w[tot]=z;
	nxt[tot]=head[x];
	head[x]=tot;
}
int dp[500010][2];
priority_queue<int,vector<int>,less<int> > q;
void dfs(int u,int f)
{
	dp[u][0]=0;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==f) continue;
		dfs(v,u);
	}
	while(!q.empty()) q.pop();
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==f) continue;
		q.push(dp[v][0]+w[i]-dp[v][1]);
		dp[u][0]+=dp[v][1];
	}
	int t=k-1;
	while(t--&&!q.empty()&&q.top()>0) dp[u][0]+=q.top(),q.pop();
	dp[u][1]=dp[u][0];
	if(!q.empty()&&q.top()>0) dp[u][1]+=q.top(),q.pop();
}
signed main()
{
	int T;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++) head[i]=0;
		tot=0;
		for(int i=1;i<n;i++)
		{
			int x,y,z;
			scanf("%lld%lld%lld",&x,&y,&z);
			add(x,y,z); add(y,x,z);
		}
		dfs(1,1);
		printf("%lld\n",dp[1][1]);
	}
	return 0;
}
/*

*/
```


---

## 作者：船酱魔王 (赞：0)

# CF1223E Paint the Tree 题解

## 题意回顾

给定 $ n $ 个点的树，每个点需要染 $ k $ 种颜色，颜色无限种，但每种颜色最多染两个点。一条边产生贡献当且仅当存在连接的两个点存在至少一种相同颜色。

多测，$ \sum n, \sum k \le 5 \times 10^5 $。

## 分析

首先，题意看起来很复杂。

但是，我们发现一个点的染色可以染一些只出现一次的色，不会影响答案，但可以消耗染色次数，因此染色次数没必要正好 $ k $。

对于出现两次的颜色，当且仅当染在相邻的点上时才有价值。

因此，我们可以转化题意：

给定一棵树，让一些边成为有效边，每个点最多连接 $ k $ 条有效边，使得有效边边权和最大。

树上独立集或覆盖问题考虑设计树形 DP。

本题中，带有后效性的状态显然只有点号 $ u $ 和是否可以与父亲连有效边。

考虑设计树形 DP，$ dp_{u,o} $ 表示点 $ u $ 是否可以向父亲连有效边的情况下，子树中的有效边边权最大值。

我们考虑 $ u $ 的儿子 $ v $ 是否连有效边的贡献，先求出一条不连的答案，再从大到小加上连比不连多的贡献值，可以使用优先队列。

注意 $ k $ 过大和连不如不连这两种情况的特判。

连 $ k $ 次的答案为 $ dp_{u,0} $，连 $ k-1 $ 次的答案为 $ dp_{u,1} $（因为还可以与父亲连一条）。

注意全局变量的初始化。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int N = 5e5 + 5;
int T;
int n, k;
struct node {
    int to;
    int w;
};
node make(int v, int w) {
    node res;
    res.to = v;
    res.w = w;
    return res;
}
vector<node> g[N];
long long dp[N][2];//0 - not link with father, 1 - can link with father
priority_queue<long long> que;
void solve(int u, int fath) {
    long long sum = 0;
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].to;
        if(v == fath) continue;
        solve(v, u);
        sum += dp[v][0];
    }
    while(!que.empty()) que.pop();
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].to;
        int w = g[u][i].w;
        if(v == fath) continue;
        if(dp[v][1] + w <= dp[v][0]) continue;
        que.push(dp[v][1] + w - dp[v][0]);
    }
    for(int i = 1; i <= k - 1; i++) {
        if(que.empty()) break;
        sum += que.top();
        que.pop();
    }
    dp[u][1] = sum;
    if(!que.empty()) {
        sum += que.top();
        que.pop();
    }
    dp[u][0] = sum;
}
int main() {
    scanf("%d", &T);
    for(int ti = 1; ti <= T; ti++) {
        scanf("%d%d", &n, &k);
        int u, v, w;
        for(int i = 1; i <= n; i++) g[i].clear();
        for(int i = 1; i < n; i++) {
            scanf("%d%d%d", &u, &v, &w);
            g[u].push_back(make(v, w));
            g[v].push_back(make(u, w));
        }
        solve(1, 0);
        printf("%lld\n", dp[1][0]);
    }
    return 0;
}

```

---

