# [ICPC 2020 Nanjing R] Monster Hunter

## 题目描述

有一棵有根树，包含 $n$ 个顶点，根顶点是 $1$。每个顶点上都有一个怪物。第 $i$ 个顶点上的怪物的生命值为 $hp_i$。

Kotori 想要消灭所有的怪物。第 $i$ 个顶点上的怪物可以被消灭，当且仅当其直接父节点上的怪物已经被消灭。消灭第 $i$ 个怪物所需的力量是 $hp_i$ 加上所有其他活着的怪物的生命值，这些怪物位于以 $i$ 为直接父节点的顶点 $j$ 上。形式化地，所需的力量等于
$$
hp_i + \sum_{\begin{array}{c}\text{顶点 } j \text{ 上的怪物是\textbf{活着的}} \\ \text{且 } i \text{ 是 } j \text{ 的直接父节点} \end{array}} hp_j
$$

此外，Kotori 可以使用一些魔法咒语。如果她使用一个魔法咒语，她可以在没有任何限制的情况下使用 $0$ 力量消灭任何怪物。也就是说，她可以选择一个怪物，即使其直接父节点上的怪物还活着。

对于每一个 $m=0,1,2,\cdots,n$，Kotori 想要分别知道如果她可以使用 $m$ 个魔法咒语，消灭所有怪物所需的最小总力量。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
5
1 2 3 4
1 2 3 4 5
9
1 2 3 4 3 4 6 6
8 4 9 4 4 5 2 4 1
12
1 2 2 4 5 3 4 3 8 10 11
9 1 3 5 10 10 7 3 7 9 4 9```

### 输出

```
29 16 9 4 1 0
74 47 35 25 15 11 7 3 1 0
145 115 93 73 55 42 32 22 14 8 4 1 0```

# 题解

## 作者：_H17_ (赞：4)

## 题目分析

拿到题看看大概就能想出是树形 DP。

状态：设 $f_{i,j,0\sim1}$ 是以 $i$ 为子树时，一共使用 $j$ 次咒语，该点有、没有使用过咒语时的最小开销。

得到状态转移方程：$f_{i,j,0}=\min(f_{i,j,0},f_{i,j-k,0}+\min(f_{t,k,1},f_{t,k,0}+a_t)),(\max(0,j-siz_i)\le k \le \min(j, siz_v),t \in son_i)$、$f_{i,j,1}=\min(f_{i,j,1},f_{i,j-k,1}+\min(f_{t,k,1},f_{t,k,0})),(\max(0,j-siz_i)\le k \le \min(j, siz_v),t \in son_i)$。~~推了 743014 年，状态转移方程终于推完了。~~

记着，优化应加进加，否则很可能被卡掉。

## 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2001,INF=0x3f3f3f3f3f3f3f3f;
int n, a[N],head[N],tot,siz[N],f[N][N][2];
struct E{//边
    int nxt,tar;
	E(int nxt=0,int tar=0):nxt(nxt),tar(tar){}
}edge[N];
void add(int u,int v){//加边
    edge[++tot]=E(head[u],v),head[u]=tot;
    return;
}
void dfs(int u){//DP
    siz[u]=1;
    for(int i=0;i<=n;i++)
		f[u][i][0]=f[u][i][1]=INF;
	f[u][0][0]=a[u],f[u][1][1]=0;//初始化
    for(int i=head[u],v;i;i=edge[i].nxt){
        dfs(v=edge[i].tar);
        for(int j=siz[u]+siz[v];j>=0;j--){
            if(j)
				f[u][j][1]+=f[v][0][0]; 
            f[u][j][0]+=f[v][0][0]+a[v];
            for(int k=max(0ll,j-siz[u]);k<=min(j,siz[v]);k++){
                f[u][j][0]=min(f[u][j][0],f[u][j-k][0]+min(f[v][k][1],f[v][k][0]+a[v]));
                if(j)
					f[u][j][1]=min(f[u][j][1],f[u][j-k][1]+min(f[v][k][1],f[v][k][0]));//长死的状态转移
            }
        }
        siz[u]+=siz[v];
    }
    return;
}
void Main(){//单组数据
	memset(head,0,sizeof(head));
	tot=0;//清空部分
    cin>>n;
    for(int i=1,u;i<n;i++){
		cin>>u;
		add(u,i+1);//加边
	}
	for(int i=1;i<=n;i++)
		cin>>a[i];//输入需要讲吗？
    dfs(1);//DP
    for(int i=0;i<=n;i++)
    	cout<<min(f[1][i][0],f[1][i][1])<<(i!=n?' ':'\n');//输出需要讲吗？
	return;
}
signed main(){
    int _;
    for(cin>>_;_;--_)//多测
		Main();
    return 0;
}
```

---

## 作者：WhitD (赞：3)

## 题目大意
给定一棵树和每个点的点权 $hp_i$，标记一个点 $u$ 的代价为 $hp_u+\sum_{v\texttt{是}u\texttt{的直接子节点}} hp_v$，必须先标记父节点才能标记子节点。你可以使用魔法，每使用一次魔法，可以选定一个点 $x$ 无代价标记（即使 $x$ 的父节点没被标记）。求标记所有点的最小代价。
## 思路
考虑不使用魔法，需要的总代价是 $sum=\sum_{i=1}^n hp_i+\sum_{i=2}^n hp_i$（模拟下就明白了）。如果我们使用魔法标记了点 $u$，代价会少（$hp_u+\sum_{v\texttt{是}u\texttt{的直接子节点}} hp_v$），于是我们可以通过枚举一个点的直接子节点来求代价。如果 $u$ 的父节点没被标记，那么当它的父亲被标记时代价就不用计算 $u$ 的了，代价还会少 $hp_u$；如果父亲节点已经被标记过，那么代价不会变化。

于是我们可以设 $dp(i,m,0/1)$ 表示当前点编号为 $i$，已经标记了 $m$ 个节点，当前节点是否标记，来求出使用魔法标记，会使总代价最多减少的值，最后用 $sum$ 减去 $dp$ 就得到答案了。可以通过枚举子树大小从而保证时间复杂度是 $O(n^2)$。

### 转移方程
设当前转移到的点为 $x$，子节点为 $v$，子树大小分别为 $i,j$

$\begin{cases}  
dp[x][i+j][0]=\max(dp[x][i+j][0],dp[x][i][0]+\max(dp[v][j][0],dp[v][j][1])) \\  
dp[x][i+j][1]=\max(dp[x][i+j][1],dp[x][i][1]+\max(dp[v][j][0],dp[v][j][1]-hp[v])) \\ \end{cases}$

关于第二行最后为什么要减 $hp_v$：其实通过上面的分析可以知道，如果一个点的父亲节点被标记了，那么最后代价是不会减少 $hp$ 的，因此需要给他减掉。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2005;
const ll inf=1ll<<60;
vector<int> G[N];
ll a[N],sz[N],sum[N],dp[N][N][2],ans[N],T,n;
void dfs(int x,int fa)
{
    dp[x][0][0]=0;
	dp[x][1][1]=sum[x];
	sz[x]=1;
    for(auto &v:G[x])
	{
        if(v==fa) 
			continue;
        dfs(v,x);
        for(int i=sz[x];i>=0;i--)
            for(int j=sz[v];j>=0;j--)
                dp[x][i+j][0]=max(dp[x][i+j][0],dp[x][i][0]+max(dp[v][j][0],dp[v][j][1])),dp[x][i+j][1]=max(dp[x][i+j][1],dp[x][i][1]+max(dp[v][j][0],dp[v][j][1]-a[v]));
        sz[x]+=sz[v];
    }
}
int main()
{
	cin>>T;
    while(T--)
	{
		memset(ans,0,sizeof(ans));
        cin>>n;
        for(int i=1;i<=n;i++)
		{
            G[i].clear();
            for(int j=0;j<=n;j++)
                dp[i][j][0]=dp[i][j][1]=-inf;
        }
        for(int i=2,x;i<=n;i++)
            cin>>x,G[x].push_back(i);
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<=n;i++)
		{
            sum[i]=a[i];
            for(auto &j:G[i]) 
				sum[i]+=a[j];
            ans[0]+=sum[i];
            if(i>1)
				sum[i]+=a[i];
        }
        dfs(1,0);
        for(int i=1;i<=n;i++)
            ans[i]=ans[0]-max(dp[1][i][0],dp[1][i][1]);
        for(int i=0;i<n;i++) 
			cout<<ans[i]<<" ";
        cout<<ans[n]<<endl;
    }
    return 0;
}
```

---

## 作者：SDLTF_凌亭风 (赞：1)

题解来源于一位和我组队且不愿透露姓名的好兄弟。

一开始我写了个贪心然后发现不能过样例，后面想起来发现这个贪心是假的，老老实实去 DP。

拿到题目，发现做法大致应该是 $O(n^2)$ 的，所以最初的想法是设一个 $f_{i,j}$ 表示到 $i$ 然后这个子树内部用了 $j$ 次魔法。但是问题是发现转移很不方便，因为一个节点是否使用魔法会对父亲产生影响，于是还得设一个 $f_{i,j,0/1}$ 表示 $i$ 是否使用魔法。

很明显我们在 DP 的时候可以用类似于背包的方法逐一合并每个子树。对于每一个子树的合并，我们有

$$
\begin{cases}
    f_{u,j+k,0}=\min(f_{u,j+k,0},f_{u,j,0}+\min(f_{v,k,0}+hp_v,f_{v,k,1}))
    \\
    f_{u,j+k,1}=\min(f_{u,j+k,1},f_{u,j,1}+\min(f_{v,k,0},f_{v,k,1}))
\end{cases}
$$

第一行的那个 $+hp_v$ 指的是没有用魔法点掉的时候需要加上子节点的 $hp$，然后就没有了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace  std;
typedef long long int ll;
const ll MAXN=2e3+51;
struct Edge{
	ll to,prev;
};
Edge ed[MAXN];
ll test,n,tot;
ll last[MAXN],fa[MAXN],hp[MAXN],sz[MAXN];
ll f[MAXN][MAXN][2],g[MAXN][2];
inline ll read()
{
	register ll num=0,neg=1;
	register char ch=getchar();
	while(!isdigit(ch)&&ch!='-')
	{
		ch=getchar();
	}
	if(ch=='-')
	{
		neg=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		num=(num<<3)+(num<<1)+(ch-'0');
		ch=getchar();		
	}
	return num*neg;
}
inline void addEdge(ll u,ll v)
{
	ed[++tot]=(Edge){v,last[u]},last[u]=tot;
}
inline void dfs(ll x)
{
	ll to,d1,d2;
	sz[x]=1,f[x][0][0]=hp[x],f[x][1][1]=0;
	for(register int i=last[x];i;i=ed[i].prev)
	{
		to=ed[i].to,dfs(to);
		for(register int j=0;j<=sz[x]+sz[to];j++)
		{
			g[j][0]=g[j][1]=1e15;
		}
		for(register int j=0;j<=sz[x];j++)
		{
			for(register int k=0;k<=sz[to];k++)
			{
				d1=min(f[to][k][0]+hp[to],f[to][k][1]);
				d2=min(f[to][k][0],f[to][k][1]);
				g[j+k][0]=min(g[j+k][0],f[x][j][0]+d1);
				g[j+k][1]=min(g[j+k][1],f[x][j][1]+d2);
			}
		}
		for(register int j=0;j<=sz[x]+sz[to];j++)
		{
			f[x][j][0]=g[j][0],f[x][j][1]=g[j][1];
		}
		sz[x]+=sz[to];
	}
}
inline void solve()
{
	n=read(),tot=0;
	for(register int i=2;i<=n;i++)
	{
		fa[i]=read(),addEdge(fa[i],i);
	}
	for(register int i=1;i<=n;i++)
	{
		hp[i]=read();
		for(register int j=0;j<=n;j++)
		{
			f[i][j][0]=f[i][j][1]=1e15;
		}
	}
	dfs(1);
	for(register int i=0;i<n;i++)
	{
		printf("%lld ",min(f[1][i][0],f[1][i][1]));
	}
	printf("%lld\n",min(f[1][n][0],f[1][n][1]));
	for(register int i=1;i<=n;i++)
	{
		last[i]=0;
	}
}
int main()
{
	test=read();
	for(register int i=1;i<=test;i++)
	{
		solve();
	}
}
```

---

## 作者：lfxxx (赞：1)

考试出了这道题目，直接场切了。

不难一眼看出是树形 dp。

考虑设计状态 $dp_{u,i,0/1}$ 表示考虑以 $u$ 为根的子树用了 $i$ 次魔法且其自身有没有使用魔法的答案。

得到转移方程：

$$dp_{u,,i+j,,0}=\min(dp_{u,,i+j,,0},\min(dp_{v,j,0}+hp_{v},dp_{v,j,1})+dp_{u,i,0})$$

$$dp_{u,i+j,1}=\min(dp_{u,i+j,1},\min(dp_{v,j,0},dp_{v,j,1})+dp_{u,i,1})$$

直接转移是 $O(n^3)$ 的，但是我们发现在加入儿子 $v$ 前父亲 $u$ 的状态第二维始终是不大于 $sz_{u} - sz_{v}$ 所以枚举的复杂度变为 $\sum_{u} \sum_{v} (sz_{u} - sz{v}) \times sz_{v}$。

推一下式子：

$$\sum_{u} \sum_{v} (sz_{u} - sz{v}) \times sz_{v} = \sum_{u} \sum_{v} sz_{u} \times sz_{v} - sz^2_{v}$$

$$\sum_{u} \sum_{v} sz_{u} \times sz_{v} - sz^2_{v} = \sum_{u} (sz_{u} \times \sum_{v} sz_{v}) - \sum_{v} sz^2_{v}$$

$$\sum_{u} (sz_{u} \times \sum_{v} sz_{v}) - \sum_{v} sz^2_{v} < \sum_{u} sz^2_{u} - \sum_{v} sz^2_{v} = sz^2_{1} = n^2$$

至此复杂度被优化至 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e3+14;
const long long inf = 1e15+7;
long long dp[maxn][maxn][2],f[maxn][maxn][2],hp[maxn];
int sz[maxn];
int n;
vector<int> edge[maxn];
void DP(int u){
	sz[u]=1;
	for(int v:edge[u]){
		DP(v);
		sz[u]+=sz[v];
	}
	for(int i=0;i<=sz[u];i++) dp[u][i][0]=dp[u][i][1]=f[u][i][0]=f[u][i][1]=0;
	for(int v:edge[u]){
		for(int j=0;j<=sz[v];j++) 
			for(int i=0;i<=sz[u]-sz[v];i++) dp[u][i+j][0]=dp[u][i+j][1]=inf; 
		for(int j=0;j<=sz[v];j++){
			for(int i=0;i<=sz[u]-sz[v];i++){
				dp[u][i+j][0]=min(dp[u][i+j][0],min(dp[v][j][0]+hp[v],dp[v][j][1])+f[u][i][0]);
				dp[u][i+j][1]=min(dp[u][i+j][1],min(dp[v][j][0],dp[v][j][1])+f[u][i][1]);
			}
		} 
		for(int j=0;j<=sz[v];j++) 
			for(int i=0;i<=sz[u]-sz[v];i++) f[u][i+j][0]=dp[u][i+j][0],f[u][i+j][1]=dp[u][i+j][1];
	}	
	for(int i=0;i<=sz[u];i++) dp[u][i][0]+=hp[u];
	for(int i=sz[u];i>=1;i--) dp[u][i][1]=dp[u][i-1][1];
	dp[u][0][1]=inf;
	return ;
} 
void work(){
	cin>>n;
	for(int i=0;i<=n;i++){
		hp[i]=sz[i]=0;
		for(int j=0;j<=n;j++) dp[i][j][0]=dp[i][j][1]=inf;
	}
	for(int i=2;i<=n;i++){
		int p;
		cin>>p;
		edge[p].push_back(i);	
	}
	for(int i=1;i<=n;i++) cin>>hp[i];
	DP(1);
	for(int i=0;i<=n;i++) cout<<min(dp[1][i][0],dp[1][i][1])<<' ';
	cout<<'\n';
	for(int i=1;i<=n;i++) edge[i].clear();
	return ;
}
signed main(){
	//freopen("T2.in","r",stdin);
	//freopen("T2.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--) work();
	return 0;
}
/*
9
1 2 3 4 3 4 6 6
8 4 9 4 4 5 2 4 1
*/
/*
3
5
1 2 3 4
1 2 3 4 5
9
1 2 3 4 3 4 6 6
8 4 9 4 4 5 2 4 1
12
1 2 2 4 5 3 4 3 8 10 11
9 1 3 5 10 10 7 3 7 9 4 9
*/
```


---

## 作者：zheng_zx (赞：0)

## P9634 [ICPC2020 Nanjing R] Monster Hunter

[题目传送门](https://www.luogu.com.cn/problem/P9634)

### 分析

---

一道树上 dp 题。令 $\operatorname{dp}[u][0/1][j]$ 表示以 $u$ 为根的子树中，$u$ 这个点用了/没用咒语，且整棵子树内共用了 $j$ 次咒语的情况下，杀掉所有怪的最小化费。


而转移的时候考虑的是从 $u$ 的所有孩子转移，即给孩子们 $v$ 次分配咒语次数，于是可列出下列动态转移方程：

$$\operatorname{dp}[u][0][j]=\min 
\begin{Bmatrix} 
\underset{\Sigma k_i=j}{\sum}
\operatorname{dp}[v][0/1][k]+a[v] \times [flg_v=0]
\end{Bmatrix} +a[u],$$

$$\operatorname{dp}[u][1][j]=\min 
\begin{Bmatrix} 
\underset{\Sigma k_i=j-1}{\sum}
\operatorname{dp}[v][0/1][k]
\end{Bmatrix}$$

如果把每个孩子 $v$ 的 dp 值看成物品，那就是一个分组背包：对于每个孩子，只能从 $\operatorname{dp}[v][0/1][k]$ 中选一个，而每个孩子又必须选一个。那么就变成了比较显然的树形背包了。这题稍有一些区别的地方在于，每组物品必须选一个，因此在枚举 $k$ 之前向 $u$ 中放任意一个，再进行 dp。

### Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define enter puts("")
#define space putchar(' ')
#define forE(i, x, y) for(int i = head[x], y; ~i && (y = e[i].to); i = e[i].nxt)
typedef long long ll; 
const int maxn = 2e3 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3f;
inline ll read(){
    ll ans = 0;
    char ch = getchar(), las = ' ';
    while(!isdigit(ch)) las = ch, ch = getchar();
    while(isdigit(ch)) ans = (ans << 1) + (ans << 3) + (ch ^ 48), ch = getchar();
    if(las == '-') ans = -ans;
    return ans;
}
inline void write(ll x){
    if(x < 0) putchar('-'), x = -x;
    if(x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}

int n, a[maxn];
struct Edge{
    int nxt, to;
}e[maxn];
int head[maxn], ecnt = -1;
inline void addEdge(int x, int y){
    e[++ecnt] = (Edge){head[x], y};
    head[x] = ecnt;
}

int siz[maxn];
ll dp[maxn][2][maxn];
inline void dfs(int now){
    siz[now] = 1;
    for(int i = 0; i <= n; ++i) dp[now][0][i] = dp[now][1][i] = INF;
    dp[now][0][0] = a[now]; dp[now][1][1] = 0;
    forE(i, now, v){
        dfs(v);
        for(int j = siz[now] + siz[v]; j >= 0; --j){
        	if(j) dp[now][1][j] += dp[v][0][0]; 
            dp[now][0][j] += dp[v][0][0] + a[v];
            for(int k = max(0, j - siz[now]); k <= min(j, siz[v]); ++k){
                dp[now][0][j] = min(dp[now][0][j], dp[now][0][j - k] + min(dp[v][1][k], dp[v][0][k] + a[v]));
                if(j) dp[now][1][j] = min(dp[now][1][j], dp[now][1][j - k] + min(dp[v][1][k], dp[v][0][k]));
            }
        }
		siz[now] += siz[v];
    }
}

int main(){
    int T = read();
    while(T--){
        memset(head, -1, sizeof(head)), ecnt = -1;
        n = read();
        for(int i = 2; i <= n; ++i) addEdge(read(), i);
        for(int i = 1; i <= n; ++i) a[i] = read();
        dfs(1);
        for(int i = 0; i <= n; ++i){
            write(min(dp[1][0][i], dp[1][1][i]));
            i == n ? enter : space;
        }
    }
    return 0;
}
```

---

## 作者：happybob (赞：0)

考虑树上背包。但是直接设 $f_{i,j}$ 表示以 $i$ 为根的子树中用了 $j$ 次魔法难以转移，问题在于难以确定 $i$ 的儿子是否呗魔法标记。

于是加一维，$f_{i,j,0/1}$ 表示以 $i$ 为根的子树中用了 $j$ 次魔法，$i$ 点被魔法标记了或没有被标记。$0$ 表示被标记，$1$ 表示没有被标记。

转移时朴素地类似树上背包转移即可。

时间复杂度 $O(n^2)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int N = 2e3 + 5;

long long f[N][N][2], hp[N], tmp[N][N][2];
// f[i][j][0]: 根不存在，f[i][j][1]：根存在
vector<int> G[N];
int t, n;
int sz[N];

void dfs(int u, int fa)
{
	f[u][1][0] = 0LL;
	f[u][0][1] = hp[u];
	sz[u] = 1;
	int c = 0;
	for (auto& j : G[u])
	{
		if (j == fa) continue;
		c++;
		dfs(j, u);
		for (int i = 0; i <= sz[u] + sz[j]; i++) tmp[u][i][0] = tmp[u][i][1] = (long long)1e18;
		for (int i = 0; i <= sz[j]; i++) // 枚举子树 j 删的个数
		{
			for (int k = 0; k <= sz[u]; k++) // 枚举当前子树删的个数
			{
				int tot = i + k;
				tmp[u][tot][0] = min(tmp[u][tot][0], min(f[j][i][0], f[j][i][1]) + f[u][k][0]);
			}
		}
		for (int i = 0; i <= sz[j]; i++) // 枚举子树 j 删的个数
		{
			for (int k = 0; k <= sz[u]; k++) // 枚举当前子树删的个数
			{
				int tot = i + k;
				tmp[u][tot][1] = min(tmp[u][tot][1], min(f[j][i][0], f[j][i][1] + hp[j]) + f[u][k][1]);
			}
		}
		sz[u] += sz[j];
		for (int i = 0; i <= sz[u]; i++) f[u][i][0] = tmp[u][i][0], f[u][i][1] = tmp[u][i][1];
	}
	if (f[u][sz[u]][0] != 0) cout << "error: " << u << "\n";
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 1; i <= n; i++) G[i].clear(), G[i].shrink_to_fit();
		for (int i = 2; i <= n; i++)
		{
			int fa;
			cin >> fa;
			G[fa].emplace_back(i);
		}
		for (int i = 1; i <= n; i++) cin >> hp[i];
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j <= n; j++) f[i][j][0] = f[i][j][1] = (long long)1e18;
		}
		dfs(1, 0);
		for (int i = 0; i <= n; i++) cout << min(f[1][i][0], f[1][i][1]) << " ";
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：0)

## 题意

给定一棵树，每个点有点权。初始时每个点都是白点。

将一个点变黑需要满足它的父亲是黑的，还要花费它的点权加上它所有白儿子的点权和的代价。

你可以使用 $m$ 次魔法，每个魔法可以花费 $0$ 代价将某个点变黑。

输出 $m=0,1,2\cdots,n$ 时让整棵树全黑需要的最小代价。

## 思路

很容易发现我们一开始用完所有魔法是不劣的。用完魔法之后后面的过程就确定了。

又根据儿子黑白对父亲的影响，以及求最小代价，很容易想到考虑 dp。

先非常经典地设一个 $f_{i,j}$ 表示以 $i$ 为根的子树全黑，花费了 $j$ 次魔法需要的最小代价。然而你发现这不好转移，因为父亲需要知道儿子是否早已通过魔法变黑，才能考虑是否要加上这个儿子的点权。于是加一维 $0/1$，设 $f_{i,j,0/1}$ 表示以 $i$ 为根的子树全黑，花费了 $j$ 次魔法，且点 $i$ 为白或黑需要的最小代价。

发现第三维是 $0$ 和是 $1$ 的转移是独立的，不可能加了一部分儿子的点权又非常荒谬地突然变黑。因此转移比较简单。

$$
\begin{cases}
f_{u,i+j,0}\gets f_{u,i,0}+\min(f_{v,j,0}+hp_{v},f_{v,j,1})\\
f_{u,i+j,1}\gets f_{u,i,1}+\min(f_{v,j,0},f_{v,j,1})\\
\end{cases}
,v\in son_u
$$

初值即为 $f_{u,1,1}=0,f_{u,0,0}=hp_u$，对于每个 $m$，答案为 $\min(f_{1,m,0},f_{1,m,1})$。

用树形背包的方式转移即可做到 $\mathcal O(n^2)$。

---

