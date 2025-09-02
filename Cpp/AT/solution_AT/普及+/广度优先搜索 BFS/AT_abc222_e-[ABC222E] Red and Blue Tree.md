# [ABC222E] Red and Blue Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc222/tasks/abc222_e

$ N $ 頂点の木と、長さ $ M $ の数列 $ A=(A_1,\ldots,A_M) $、整数 $ K $ が与えられます。  
 木の頂点には $ 1 $ から $ N $ の番号がつけられており、$ i $ 番目の辺は頂点 $ U_i $ と $ V_i $ を結んでいます。

この木の $ N-1 $ 個の辺をそれぞれ赤か青のどちらかに塗ります。そのような方法は $ 2^{N-1} $ 通りありますが、そのうち次の条件を満たすような塗り方の個数を $ 998244353 $ で割った余りを求めてください。

条件：  
 最初、駒を頂点 $ A_1 $ におく。$ i=1,\ldots,M-1 $ の順に、駒を頂点 $ A_i $ から頂点 $ A_{i+1} $ まで、辺をたどって最短経路で動かす。 これらの操作を最後まで行ったとき、赤く塗られた辺を通過した回数を $ R $、青く塗られた辺を通過した回数を $ B $ とすると、$ R-B=K $ である。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 1000 $
- $ 2\ \leq\ M\ \leq\ 100 $
- $ |K|\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ N $
- $ 1\leq\ U_i,V_i\leq\ N $
- 与えられるグラフは木である
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ 1,3 $ 番目の辺を赤く、$ 2 $ 番目の辺を青く塗ったとき、 - 頂点 $ 2 $ から頂点 $ 3 $ への移動で赤い辺を $ 0 $ 回、青い辺を $ 1 $ 回 - 頂点 $ 3 $ から頂点 $ 2 $ への移動で赤い辺を $ 0 $ 回、青い辺を $ 1 $ 回 - 頂点 $ 2 $ から頂点 $ 1 $ への移動で赤い辺を $ 1 $ 回、青い辺を $ 0 $ 回 - 頂点 $ 1 $ から頂点 $ 4 $ への移動で赤い辺を $ 2 $ 回、青い辺を $ 1 $ 回 それぞれ通過し、全体では赤い辺を $ 3 $ 回、青い辺を $ 3 $ 回通るため、条件を満たします。 !\[図\](https://img.atcoder.jp/ghi/f9b2b199fb6eedaca02e15ff556b72b1.png) この他、$ 1,3 $ 番目の辺を青く、$ 2 $ 番目の辺を赤く塗るときも条件を満たし、これら以外の塗り方は条件を満たさないため、答えは $ 2 $ 通りです。

### Sample Explanation 2

条件を満たす塗り方が存在しないこともあります。

## 样例 #1

### 输入

```
4 5 0
2 3 2 1 4
1 2
2 3
3 4```

### 输出

```
2```

## 样例 #2

### 输入

```
3 10 10000
1 2 1 2 1 2 2 1 1 2
1 2
1 3```

### 输出

```
0```

## 样例 #3

### 输入

```
10 2 -1
1 10
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10```

### 输出

```
126```

## 样例 #4

### 输入

```
5 8 -1
1 4 1 4 2 1 3 5
1 2
4 1
3 1
1 5```

### 输出

```
2```

# 题解

## 作者：_zzzzzzy_ (赞：4)

# 思路
显然我们可以通过各种手段计算出来每一个边被遍历过的个数，然后我们可以对个数求一个和，先特判掉不合法的情况，就是边的个数小于 $k$ 个数和总和和 $k$ 不同奇同偶的情况，因为 $\frac{sum+k}{2}$ 是红边的个数，问题就转化成了一个简单的背包问题，就是在边的选择个数里面选一些让他的总和等于红边的个数，然后输出 $dp[\text{红边的个数}]$ 就行了。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100050,mod=998244353;
vector<int>e[maxn];
int a[maxn],dp[maxn],c[maxn];
map<pair<int,int>,int>mp;
bool dfs(int S,int f,int T){
	if(S==T)return 1;
	for(int v:e[S]){
		if(v!=f){
			if(dfs(v,S,T)){
				c[mp[{S,v}]]++;
				return 1;
			}
		}
	}
	return 0;
}
signed main(){
	int n,m,k,sum=0;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){cin>>a[i];}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
		mp[{u,v}]=mp[{v,u}]=i;
	}
	for(int i=2;i<=m;i++)dfs(a[i-1],0,a[i]);
	for(int i=1;i<n;i++)sum+=c[i];
	if((sum+k)%2==1||sum<k)return cout<<0,0;
	sum=(sum+k)/2;
	dp[0]=1;
	for(int i=1;i<n;i++){
		for(int j=sum;j>=c[i];j--){
			dp[j]=(dp[j]+dp[j-c[i]])%mod;
		}
	}
	cout<<dp[sum];
	return 0;
}
```

---

## 作者：Misty_Post (赞：3)

# 思路

显然可以先用 $O(n^2)$ 求出每一条边经过的次数。

然后，我们可以用一个动态规划来解决该问题。

设 $f[i][j]$ 的意思为现在在决策第 $i$ 条边，$R$ 和 $B$ 的差值为 $j$ 的方案数。

转移就不难看出了，分情况讨论即可。

因为 $j$ 有可能出现负数，所以要强制加上一个常数处理。

为了保证空间无忧，把第一维滚动掉就可以了。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=998244353;
const ll N=1000000;
ll n,m,k,a[N],num[N],zt;
ll f[2][600001];
struct Edge{
    ll v,id;
};
vector<Edge>g[N];
void adde(ll x,ll y,ll id){
    g[x].push_back({y,id});
    g[y].push_back({x,id});
}
void dfs(ll x,ll zd,ll fa){
    if(x==zd||zt){
        zt=1;
        return;
    }
    for(auto e:g[x]){
        ll v=e.v,id=e.id;
        if(v!=fa){
            dfs(v,zd,x);
            if(zt){
                num[id]++;
                return;
            }
        }
    }
}
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        ll x,y;
        cin>>x>>y;
        adde(x,y,i);
    }
    ll st=a[1];
    for(int i=2;i<=m;i++){
        zt=0;
        dfs(st,a[i],0);
        st=a[i];
    }
    ll summ=0;
    for(int i=1;i<n;i++){
        summ+=num[i];
    }
    ll R=summ;
    memset(f,0,sizeof(f));
    f[0][R]=1;
    for(int i=1;i<n;i++){
        int cc=i%2,pre=(i-1)%2;
        memset(f[cc],0,sizeof(f[cc]));
        for(ll j=0;j<=2*summ;j++){
            if(f[pre][j]){
                if(j>=num[i]){
                    f[cc][j-num[i]]=(f[cc][j-num[i]]+f[pre][j])%mod;
                }
                if(j+num[i]<=2*summ){
                    f[cc][j+num[i]]=(f[cc][j+num[i]]+f[pre][j])%mod;
                }
            }
        }
    }
    cout<<f[(n-1)%2][R+k]%mod<<endl;
    return 0;
}
```

---

## 作者：Endline (赞：1)

# AT-ABC222-E题解

## 重链剖分+差分+背包dp

显然，对于一个树上两点间路径问题，立刻可以想到树剖。

题目询问每条边经过多少次，将边的信息放在它所连接的下层（儿子节点）上，我们可以利用差分维护区间修改，然后把树剖后每个节点的权值传回树的节点。

那么问题就转化成了给定一个数组 $w_i$，对于每一个位置 $i$ 我们可以选定一个权值 $0/1$，求使得原数组 $\sum\limits_{i=1}^nw_i=k$ 的选择方案数。

这显然是一个背包问题，设 $dp_{i,j}$ 表示选择到了第 $i$ 个物品，总和为 $j$ 的方案数，转移方程：

$$
dp_{i,j} = dp_{i-1,j-w_i}+dp_{i-1,j+w_i}
$$

注意到转移时第一维 $i$ 仅跟 $i-1$ 有关，可以用滚动数组优化空间，而答案的 $k$ 有可能为负数，我们可以将值域整体加上 $100000$，使其全部成为正数，就可以用数组存下来啦。

代码实现如下：

```cpp
#include<bits/stdc++.h>
#define MAXN 1002
#define MAXM 102
#define ls(x) x<<1
#define rs(x) x<<1|1
using namespace std;
const int mod=998244353;
int n,m,k,cnt,tot;
int a[MAXM],head[MAXN],dep[MAXN],siz[MAXN],son[MAXN],fa[MAXN],top[MAXN],dfn[MAXN];
int d[MAXN],w[MAXN],dp[2][200002];
struct edge
{
    int to,nxt;
}e[MAXN<<1];
inline void addedge(int u,int v)
{
    e[++cnt]={v,head[u]};
    head[u]=cnt;
    return;
}
void dfs1(int u)
{
    siz[u]=1;
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==fa[u])continue;
        fa[v]=u;
        dep[v]=dep[u]+1;
        dfs1(v);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
    return;
}
void dfs2(int u,int topn)
{
    top[u]=topn;
    dfn[u]=++tot;
    if(son[u])dfs2(son[u],topn);
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==fa[u]||v==son[u])continue;
        dfs2(v,v);
    }
    return;
}
inline void update(int u,int v)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]])swap(u,v);
        d[dfn[top[u]]]++;d[dfn[u]+1]--;
        u=fa[top[u]];
    }
    if(dep[u]>dep[v])swap(u,v);
    d[dfn[u]+1]++;d[dfn[v]+1]--;
    return;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)
        cin>>a[i];
    for(int i=1,u,v;i<n;i++)
    {
        cin>>u>>v;
        addedge(u,v);addedge(v,u);
    }
    dep[1]=1;
    dfs1(1);dfs2(1,1);
    for(int i=1;i<m;i++)
        update(a[i],a[i+1]);
    for(int i=2;i<=n;i++)
        d[i]=d[i-1]+d[i];
    for(int i=1;i<=n;i++)
        w[i]=d[dfn[i]];
    dp[1][100000]=1;
    for(int i=2;i<=n;i++)
        for(int j=w[i];j<=200000-w[i];j++)
            dp[i&1][j]=(dp[(i&1)^1][j-w[i]]+dp[(i&1)^1][j+w[i]])%mod;
    printf("%d\n",dp[n&1][100000+k]);
    return 0;
}
```

---

## 作者：lam_dyr (赞：0)

## 题意

给出一棵 $N$ 个结点的树，以及一个长度为 $N$ 的顶点序列 $A$ 和整数 $K$。我们把树上所有边染成红色或蓝色（总染色方法有 $2^{N-1}$ 种)，对于每一种染色方案，如果沿着 $A_i$ 到 $A_{i+1}$ 的最短路径走，红边走过次数记作 $R$，蓝边走过次数记作 $B$，要求满足 $R-B=K$。

我们的目标是求满足条件的染色方法数。

## 问题转化

对于树上的每一条边 $e$，令它在走所有相邻 $A_i$ 至 $A_{i+1}$ 的最短路径中的出现次数为 $c_e$。

考虑两种染色的贡献。如果染成红色则边 $e$ 贡献 $+c_e$，若染成蓝色则贡献 $-c_e$。所以总贡献就是

$$
\sum_{e=1}^{N-1}x_e\,c_e
$$

其中 $x_e\in\{+1,-1\}$。要求

$$
\sum_{e=1}^{N-1}x_e\,c_e=K
$$

由于不同边的染色独立，答案即为所有 ${x_e}$ 方案数（共 $2^{N-1}$ 种）中满足上述等式的方案数。

## 思路

设 $S$ 为所有边中 $c_e>0$ 的 $c_e$ 之和，此外若某条边从未被经过则 $c_e=0$，其贡献固定为 $0$，算答案时需乘上一个因子 $2$（仍能任意染色）。
因此，将边分为两类：

- 非零边（$c_e>0$）：设个数为 $P$。我们需要从这些边中选取正负号，使得 $\sum_{i=1}^{P}x_i\,c_i=K$。
- 零边（$c_e=0$）：设个数为 $Z$。它们无论如何染色均不影响总贡献 $K$；总方法数额外乘 $2^Z$ 即可。

针对非零边，考虑动态规划。
令 $dp1_s=$ 经过某些边赋值后能得到贡献和为 $s$ 的方案数，我们需要计算 $dp1_K$。

由于各个边的贡献都是 $c$ 或 $-c$，若将所有贡献平移一个偏移量 $S$（使下标非负），则 $s\in[0,2S]$，（原来的和在 $[-S,S]$）。初始状态：$dp1_S=1$。

转移时对每个非零边 $c_e$，

$$
dp2_{s+c
}=dp2_{s+c}+dp1_s,dp2_{s-c}=dp2_{s-c}+dp1_s
$$

最后答案即为 $dp1_{K+S}\times2^Z$。
注意取模 $998244353$。

## Code

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define ll long long
using namespace std;
const int N=100010,mod=998244353;
int n,m,k,a[N];
ll ans;
vector<int> g[N];
vector<pii> e;
ll qpow(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1; 
	}
	return res;
} 
ll en(int u,int v){
	return ((ll)u<<32) | v;
}
//求s到t的路径 
vector<pii> dfs(int s,int t){
	vector<int> fa(n+1,-1);
	vector<bool> vis(n+1,0);
	queue<int> q;
	q.push(s);
	vis[s]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		if(u==t) break;
		for(int v : g[u]){
			if(!vis[v]){
				vis[v]=1;
				fa[v]=u;
				q.push(v);
			}
		}
	}
	vector<pii> path;
	int cur=t;
	while(cur!=s){
		int p=fa[cur];
		int u=min(p,cur),v=max(p,cur);
		path.push_back({u,v});
		cur=p;
	}
	reverse(path.begin(),path.end());
	return path;
}
unordered_map<ll,int> mp;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=0;i<m;++i)
		cin>>a[i];
	for(int i=1;i<n;++i){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
		e.push_back({min(u,v),max(u,v)});
	}
	//对每条边统计被经过次数 c_e
	for(int i=0;i<m-1;++i){
		int s=a[i],t=a[i+1];
		vector<pii> path=dfs(s,t);
		for(auto j : path){
			ll key=en(j.fi,j.se);
			mp[key]++;
		}
	}
	//分离非零边与零边 
	vector<int> cnt;
	int cnt1=0;
	for(auto i : e){
		ll key=en(i.fi,i.se);
		int t=mp.count(key) ? mp[key] : 0;
		if(t==0) cnt1++;
		else cnt.push_back(t);
	}
	//令总和偏移 S=sum(非零边的c_e) 
	int S=0;
	for(int c : cnt) S+=c;
	int sz=2*S+1;
	vector<ll> dp1(sz,0),dp2(sz,0);
	dp1[S]=1;
	for(int c : cnt){
		fill(dp2.begin(),dp2.end(),0);
		for(int s=0;s<sz;++s){
			if(dp1[s]){
				int add=s+c;//染红色：贡献+c 
				int sub=s-c;//染蓝色：贡献-c 
				if(add<sz)
					dp2[add]=(dp2[add]+dp1[s])%mod;
				if(sub>=0)
					dp2[sub]=(dp2[sub]+dp1[s])%mod;
			}
		}
		dp1=dp2;
	}
	//统计答案 
	int p=k+S;
	if(p>=0 && p<sz) ans=dp1[p];
	ans=ans*qpow(2,cnt1)%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：ben090302 (赞：0)

我们考虑处理出每条边被经过的次数，可以树上差分但是我没写过正好试试。树剖套差分差不多应该也行但是没那么好写吧，有点牛刀了我觉得，~~于是我写了个树剖求 LCA~~。

然后每条边的贡献就是被经过次数或其相反数。

然后后半段加一个偏移就是一个很典的 dp，大致是 01 背包的变体吧，把可选可不选换成选正还是选负，但是这种变体没有那么好的拓扑序了，只能滚动数组了。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1005;
const int mod=998244353;
int n,m,k;

int a[N];
vector<int> e[N];
int fa[N],dep[N],siz[N],son[N],dfn[N];
int top[N];
void dfs1(int u,int f){
    fa[u]=f,dep[u]=dep[f]+1;
    siz[u]=1;
    for(int v:e[u]){
        if(v!=f){
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[v]>siz[son[u]]) son[u]=v;
        }
    }
}
void dfs2(int u,int tp){
    top[u]=tp;
    if(son[u]) dfs2(son[u],tp);
    for(int v:e[u]){
        if(v!=fa[u] and v!=son[u]){
            dfs2(v,v);
        }
    }
}
int LCA(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        u=fa[top[u]];
    }
    return dep[u]>dep[v]?v:u;
}

int d[N];
int w[N];
int cnt;

void dfs(int u){
    for(int v:e[u]){
        if(v!=fa[u]){
            dfs(v);
            d[u]+=d[v];  
        }
    }
    if(u!=1 and d[u]!=0) w[++cnt]=d[u];
}
int dp[2 ][200005];
const int W=100000;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++) cin>>a[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<m;i++){
        d[a[i]]++,d[a[i+1]]++,d[LCA(a[i],a[i+1])]-=2;
    }
    dfs(1);
    dp[0][W]=1;
    for(int i=1;i<n;i++) {
        for(int j=0;j<=W*2;j++){
            dp[i&1][j]=0;
            if(j-w[i]>=0)  dp[i&1][j]+=dp[i&1^1][j-w[i]];
            if(j+w[i]<=W*2)dp[i&1][j]+=dp[i&1^1][j+w[i]];
            dp[i&1][j]%=mod;
        }
    }
    cout<<dp[(n-1)&1][k+W];
}   
```

---

## 作者：aimcf (赞：0)

首先用树链剖分预处理出每一条边走过的次数 $d_i$。

然后设 $f_i$ 是两组物体的差是 $x$ 的时候有多少种方案。

初始条件：$f_{\sum_{i=1}^{n-1} d_i} = 1$，一开始将所有的物品都放在一个组里。

然后进行 DP。如果现在要将在第一组里的 $i$ 物品放到第二组，那么容易发现状态是 $f_{j-2\times d_i}$。也就是 $f_j = f_j + f_{j - 2\times d_i}$。

由于有越界的问题，然而又懒得写平衡树，所以采用了别人转移到自己的方法，也就是 $f_j = f_j + f_{j + 2\times d_i}$，$j$ 从 $0$ 枚举即可。

[AC](https://atcoder.jp/contests/abc222/submissions/35989398)

---

