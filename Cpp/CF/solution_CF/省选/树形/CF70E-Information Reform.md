# Information Reform

## 题目描述

尽管现在已经是21世纪了，但是大众传播媒介在$Walrusland$依然没有普及开来。这里的城市通过能够在城市间的道路来往的信使来互相传递消息。在$Walrusland$，城市间的道路保证信使可以从一座城市到任意另一座城市，而且这些道路是等长的。  
北极政府决定实施一项信息改革。几座城市被选中成为区域信息中心。维护一座区域信息中心每年需要花费$k$个$fishlar$（这是当地的货币）。假设每座区域信息中心总是能即时获得最新的消息。  
每一座不是区域信息中心的城市，都会被安排通过一座区域信息中心来保持信息通达。这样，每年维护费用将会等于$d_{len} \ $个$fishlar$，其中$len$表示这座城市到它的区域信息中心的距离，即一个人从这座城市到它的区域信息中心需要走过的道路条数。  
你的任务是求出实行这项改革的最小开销。

## 样例 #1

### 输入

```
8 10
2 5 9 11 15 19 20
1 4
1 3
1 7
4 6
2 8
2 3
3 5
```

### 输出

```
38
3 3 3 4 3 4 3 3 ```

# 题解

## 作者：_soul_ (赞：11)

首先我们用 Floyd 求出任意两个点之间的距离，记为 dis(i,j)。

考虑 DP 状态：设 f(i,j) 表示在第 i 个点建立信号站使得 j 子树内获得信号的最小代价。

如果我们只考虑 u 点本身，那么有 f(i,u)=dis(i,u)+k。假设我们已经求出了子树 v 的 DP 值：

假设 v 点也从 i 的位置获得信号，由于 u,v 两点重复考虑了 k 的代价，那么子树 v 对子树 u 的贡献为 f(i,v)−k。
假设 v 点不建造在 i 点，那么对 u 子树的贡献为 min1≤j≤n{f(j,v)}。我们记使得 f(i,u) 最小的 i 为 p(u)。那么可以 O(1) 得到贡献值。
最后如何计算答案？我们记点 i 从点 ans(i) 获得信号，那么我们只需要比较 f(p(v),v) 和 f(ans(u),v)−k 的值就可以得到 ans(v) 的值。递归计算即可。

时间复杂度：O(n^3)。
```cpp
#include <cstdio>
#include <algorithm>

const int N = 205, M = 405;

int n, k, tot, d[N], e[N][N], lnk[N], ter[M], nxt[M];
int dis[N][N], f[N][N], p[N], ans[N];

void add(int u, int v) {
    ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot;
}
void Floyd() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}
void dfs(int u, int fa) {
    for (int i = 1; i <= n; i++) {
        f[i][u] = d[dis[i][u]] + k;
    }
    for (int i = lnk[u]; i; i = nxt[i]) {
        int v = ter[i];
        if (v == fa) continue;
        dfs(v, u);
        for (int i = 1; i <= n; i++) {
            f[i][u] += std::min(f[p[v]][v], f[i][v] - k);
        }
    }
    p[u] = 1;
    for (int i = 1; i <= n; i++) {
        if (f[i][u] < f[p[u]][u]) p[u] = i;
    }
}
void getPath(int u, int fa, int pos) {
    for (int i = lnk[u]; i; i = nxt[i]) {
        int v = ter[i];
        if (v == fa) continue;
        ans[v] = (f[p[v]][v] > f[pos][v] - k ? pos : p[v]);
        getPath(v, u, ans[v]);
    }
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dis[i][j] = (i == j ? 0 : 0x3f3f3f3f);
        }
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        dis[u][v] = dis[v][u] = 1;
        add(u, v), add(v, u);
    }
    Floyd();
    dfs(1, 0);
    printf("%d\n", f[p[1]][1]);
    ans[1] = p[1];
    getPath(1, 0, ans[1]);
    for (int i = 1; i <= n; i++) {
        printf("%d%c", ans[i], " \n"[i == n]);
    }
    return 0;
}
```


---

## 作者：Cry_For_theMoon (赞：8)

[传送门](https://codeforces.com/contest/70/problem/E)

感觉 CF 和洛谷上的评分都虚高，实际应该 2500* 紫左右？

ETHANK：“这也太水了吧”

题意：给定一棵 $n$ 点树，可以令任意节点（至少一个）为关键节点，每多一个关键节点就要付出 $k$ 的代价。非关键节点的代价是 $d_{dis}$. 其中 $dis$ 是该节点离最近关键节点的距离。最小化总代价。$n \le 180$. **保证 $d$ 单调不降**

看到题面容易想到树形 dp，但是我们不会设计状态。

注意到 $d$ 是单调不降的，也就是说对于一个点一定会去找离他最近的关键节点。因此我们得到一个极其重要的引理：

设 $t_i$ 是距离节点 $i$  最近的关键节点。特殊地，$i$ 为关键节点时 $t_i=i$. 则对于树上两点 $(u,v)$，若 $t_u=t_v=k$，那么所有在 $(u,v)$ 路径上的点 $w$ 都满足 $t_w=k$.

证明：

假设 $t_w=k'\neq k$

注意到不管 $k$ 取哪个点，$u,v$ 中至少有一个点到 $k$ 的路径是要经过 $w$ 的。

不妨设 $u$ 到 $k$ 经过 $w$. 既然从 $w$ 出发最近的关键节点是 $k'$，那么 $u\rightarrow w \rightarrow k'$ 显然比 $u \rightarrow w \rightarrow k$ 来的近，与 $t_u=k$ 矛盾。因此假设不成立。

好，那么既然对应关键节点也形成一个连通块的形式，就很容易想到设 $f(u,j)$ 为 $u$ 为根的子树中，$t_u=j$ 的最小代价。注意这里 $j$ 不一定要在 $u$ 子树中。

那么对于 $v \in son(u)$ 我们考虑转移，显然，如果 $t_v \neq j$ 则整颗子树不需要再考虑关键节点 $j$ 了，如果 $t_v=j$，则我们在子树中多建立了一次 $j$，应该减去 $k$. 即：
$$
f(u,j)=\min\{f(u,j)+f(v,k)\} | k \neq j
$$
还要考虑
$$
f(u,j)=\min\{f(u,j)+f(v,j)-k\}
$$
考虑这个复杂度是 $O(n^4)$ 的。但是其实没必要区分 $k$ 是否等于 $j$，直接记录令 $f(v)$ 取到最小值的 $k$ 记作 $g(v)$ 然后把 $f(v,g(v))$ 和 $f(v,j)-k$ 比较一下就可以了，复杂度就变成了 $O(n^3)$.

然后考虑输出方案。

显然我们得到了 $g(u)$ 即根的决策点，那就逆过来考虑，对于 $v \in son(u)$，比较 $f(v,g(u))-k$ 和 $f(v,g(v))$ 得到 $v$ 的决策点然后递归这个过程即可。

总时间复杂度：$O(n^3)$.

```C++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
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
const int MAXN=185;
const ll INF=1e16; 
vector<int>e[MAXN];
int n,k,d[MAXN],u,v;
ll f[MAXN][MAXN],g[MAXN],fa[MAXN]; //g(i)代表令f(i,j)取得最小值的j
ll dis[MAXN][MAXN];
ll sol[MAXN];
void dp(int u){
	for(vit it=e[u].begin();it!=e[u].end();it++){
		int v=*it;
		if(v==fa[u])continue;
		fa[v]=u;dp(v);
	}
	rep(j,0,n)f[u][j]=INF;g[u]=0;
	rep(j,1,n){f[u][j]=k+d[dis[u][j]];}
	for(vit it=e[u].begin();it!=e[u].end();it++){
		int v=*it;
		if(v==fa[u])continue;
		rep(j,1,n){
			int K=g[v]; //v的决策点
			f[u][j]+=Min(f[v][j]-k,f[v][K]);
		}
	}
	rep(j,1,n){
		if(f[u][j]<f[u][g[u]])g[u]=j;
	}
}
void solve(ll u){
	//知道了fa[u]的决策，找到u的决策
	int K=g[u];
	if(f[u][sol[fa[u]]]-k < f[u][K]){
		sol[u]=sol[fa[u]];
	}else sol[u]=K;
	for(vit it=e[u].begin();it!=e[u].end();it++){
		int v=*it;if(v==fa[u])continue;
		solve(v);
	}
}
int main(){
	scanf("%d%d",&n,&k);
	rep(i,1,n)rep(j,1,n)if(i!=j)dis[i][j]=INF;
	rep(i,1,n-1)scanf("%d",&d[i]);
	rep(i,1,n-1){
		scanf("%d%d",&u,&v);
		e[u].pb(v);e[v].pb(u);
		dis[u][v]=dis[v][u]=1;
	}
	rep(k,1,n)rep(i,1,n)rep(j,1,n)dis[i][j]=Min(dis[i][j],dis[i][k]+dis[k][j]);
	dp(1);
	ll k=g[1];
	printf("%lld\n",f[1][k]);
	sol[1]=k;
	for(vit it=e[1].begin();it!=e[1].end();it++){
		int v=*it;
		solve(v);
	} 
	rep(i,1,n){
		printf("%lld ",sol[i]);
	}
	return 0;
}

```



---

## 作者：xukuan (赞：4)

常见套路，floyd+树形dp

解法：

1.先跑一遍floyd求出多源最短路（其实这里是树上多源最短路,可以用LCA把时间复杂度优化到n^2，但数据范围小，所以没有必要）

2.进行树形dp,以f[m][i]表示在i点建立一个中转站之后m点以及子树得到信息的代价最小值,ans[m]表示使得f[m][i]最小的i,d[i][j]表示i到j的距离。所以先让f[m][i]=a[d[m][i]]+k,随后dp[m][i]+=min(dp[Next][ans[Next]],dp[Next][i]-k),其中i属于[1,n]。最后更新ans

3.输出最小值和方案，如果方案有多种，输出任意一种，其中有spj

最后说一下坑点（这些大家都知道，但是根据笔者在学校里给学弟上课的影响，一考死一片）:

1.根据区间dp的思想（最外层循环是区间长度），Floyd的最外层应该是转移的中间点

2.存边可以用邻接矩阵，但请标记一下从那个点转移过来，不要走回头路导致死递归爆栈

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,k,f[190][190],a[190],d[190][190],ans[190],pre[190];
vector<ll> edge[190];

inline void floyd(){
    for(ll k=1; k<=n; k++){
        for(ll i=1; i<=n; i++){
            for(ll j=1; j<=n; j++){
                d[i][j]=d[j][i]=min(d[i][j],d[i][k]+d[k][j]);
            }
        }
    }
}

void dfs(ll m,ll before){
    for(ll i=1; i<=n; i++) f[m][i]=a[d[m][i]]+k;//方程1
    for(ll i=0; i<edge[m].size(); i++){
        ll Next=edge[m][i];
        if(Next!=before){
            dfs(Next,m);
            for(ll j=1; j<=n; j++) f[m][j]+=min(f[Next][ans[Next]],f[Next][j]-k);//方程2
        }
    }
    ans[m]=1;
    for(ll i=2; i<=n; i++){
        if(f[m][i]<f[m][ans[m]]) ans[m]=i;//记下结果
    }
}

void print(ll m,ll before,ll x){
    pre[m]=x;//输出的
    for(ll i=0; i<edge[m].size(); i++){
        ll Next=edge[m][i];
        if(Next!=before){
            if(f[Next][ans[Next]]<f[Next][x]-k) print(Next,m,ans[Next]);
            else print(Next,m,x);
        }
    }
}

int main(){
    cin>>n>>k;
    for(ll i=1; i<n; i++) scanf("%lld",&a[i]);
    memset(d,0x3f,sizeof(d));
    for(ll i=1; i<=n; i++) d[i][i]=0;
    for(ll i=1; i<n; i++){
        ll x,y;
        scanf("%lld %lld",&x,&y);
        d[x][y]=d[y][x]=1;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    floyd();//解法一

    dfs(1,0);//解法2
    printf("%lld\n",f[1][ans[1]]);
    print(1,0,ans[1]);//解法3
    for(ll i=1; i<=n; i++) printf("%lld ",pre[i]);
    return 0;
}
```

---

## 作者：pldzy (赞：3)

这不得来一发题解！！！

自己胡的不用 Floyd 的 $O(n^2)$ 做法！！！

扫了眼题解区，应该是没有这个做法的（？）

## Solution

### 1

联想到这种权值统计在特殊点确定的时候可以用虚树做，经典问题。但这道题是求最优放置方式，无关。

发现每次在当前状态下新加一个点，会产生的贡献的变化记为 $\delta$，那么 $\delta$ 大概就是节省下来的权值减去新增一个特殊点的权值。考虑能不能贪心做，每次选择 $\delta$ 最大且为正的那个点置为特殊点。但显然不行，考虑类似反悔贪心 种树 那样，选一个和选两个的最优策略的交集可能为空。

### 2

无法贪心。考虑 dp，树形 dp 通常按照自底向上的顺序进行。发现难点在于这个代价的统计，即距离这个点最近的特殊点的位置不确定，可能在子树内，也可能在子树外，不好直接 dp。但是观察一个子树，记它的根为 $u$，发现一个子树只有两种情况：

  - 对于子树内若干个点和子树的根，距离它们最近的特殊点在子树外，不妨简称为方向向外；
  - 对于子树外若干个点和子树的根，距离它们最近的特殊点在子树内（含根），不妨简称为方向向内。

以上两种情况不可能同时发生，且必然发生一个。记 $p(x)$ 表示距离点 $x$ 最近的点。显然，所有 $p(v)=p(u)$ 的点构成了一个连通块。

### 3

上述发现启发我们定义状态 $f_{u,0/1,d}$ 表示对于子树 $u$，它的方向是 向内/向外，$dis(u,p(u))=d$。特别地，$f_{u,0,0}$ 表示 $u$ 本身是特殊点的情况，$f_{u,1,0}$ 结果未定义。

转移的细节就比较多了，~~至少我改了四遍~~。

$$f_{u,0,d}=w_d + \min_{v_0\in son_u}(f_{v_0, 0, d-1} + \sum_{v\in son_u,v\ne v_0}\min(f_{v,1,d+1},f_{v,0,d},f_{v,0,d-1},f_{v,0,d+1})),\ d\ne 0$$
$$f_{u,1,d}=w_d+\sum_{v\in son_u}\min(f_{v,1,d+1},f_{v,0,d},f_{v,0,d-1},f_{v,0,d+1}),\ d\ne 0$$
$$f_{u,0,0}=k+\sum_{v\in son_u} \min(f_{v,1,1}, f_{v,0,0}, f_{v,0,1})$$

本质的原理就是，“预支代价”，提前考虑可能会产生的代价。

转移的时候记录一下从哪里转移过来的，直接倒推即可得到最优解中距离每个点最近的特殊点。

复杂度 $O(n^2)$！！！

## Code

非常好 $\text{2 KB}$，但是由于转移式调整了 $4$ 次所以写的比较丑，懒得美化了。

````cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define per(i, a, b) for(int i = a; i >= b; --i)

const int maxn = 200;

int n, D[maxn];
int f[maxn][2][maxn], dep[maxn], mxd[maxn];
int pre[maxn][maxn];
vector<int> e[maxn];

inline void dfs(int x, int fa){
	dep[x] = mxd[x] = dep[fa] + 1;
	
	int res = 0;
	for(int v : e[x]) if(v != fa){
		dfs(v, x); 
		mxd[x] = max(mxd[x], mxd[v]);
		res += min(f[v][1][1], min(f[v][0][0], f[v][0][1]));
		rep(d, 1, n - 1) 
			f[x][1][d] += min(f[v][1][d + 1], min(f[v][0][d + 1], min(f[v][0][d], f[v][0][d - 1])));
	}
	
	rep(d, 0, n) f[x][0][d] = 1e10; 
	f[x][1][0] = f[x][1][n] = 1e10;
	
	for(int v : e[x]) if(v != fa){
		rep(d, 1, n - 1){
			int val = f[v][0][d - 1] + f[x][1][d] - min(f[v][1][d + 1], min(f[v][0][d + 1], min(f[v][0][d], f[v][0][d - 1])));
			if(f[x][0][d] > val){
				f[x][0][d] = val;
				pre[x][d] = v;
			}
		}
	}
	
	f[x][0][0] = res + D[0];
	rep(d, 1, n - 1){
		if(f[x][0][d] == 1e10) f[x][0][d] = 0;
		f[x][0][d] += D[d], f[x][1][d] += D[d];
	}
	
	rep(d, mxd[x] - dep[x] + 1, n - 1) f[x][0][d] = 1e10;
}

int dir[maxn];

inline void fnd(int x, int o, int d, int fa){
	if(!d) dir[x] = x;
	else if(!o){
		fnd(pre[x][d], 0, d - 1, x);
		dir[x] = dir[pre[x][d]];
	} 
	for(int v : e[x]) if(v != fa){
		if(!o and v == pre[x][d]) continue;
		int tmp = 1e10;
		if(d) tmp = f[v][0][d - 1];
		
		if(f[v][1][d + 1] <= min(f[v][0][d], min(f[v][0][d + 1], tmp)))
			dir[v] = dir[x], fnd(v, 1, d + 1, x);
		else if(f[v][0][d] <= min(f[v][1][d + 1], min(f[v][0][d + 1], tmp)))
			fnd(v, 0, d, x);
		else if(f[v][0][d + 1] <= min(f[v][0][d], min(f[v][1][d + 1], tmp)))
			fnd(v, 0, d + 1, x);
		else if(tmp != 1e10) fnd(v, 0, d - 1, x);
	}
}

signed main(){
	scanf("%lld", &n);
	rep(i, 0, n - 1) scanf("%lld", &D[i]);
	rep(i, 2, n){
		int u, v; scanf("%lld%lld", &u, &v);
		e[u].push_back(v); e[v].push_back(u);
	}
	
	dfs(1, 0);
	
	int ans = INT_MAX, dd = 0;
	rep(d, 0, n - 1) if(f[1][0][d] < ans)
		ans = f[1][0][d], dd = d;
	printf("%lld\n", ans);
	fnd(1, 0, dd, 0);
	rep(i, 1, n) printf("%lld ", dir[i]); printf("\n");
	return 0;
}
````

---

## 作者：OIer_ACMer (赞：2)

~~吐了！~~

------------
这道题开了 SPJ，样例没过把我怕吓得半死，后来才发现是 SPJ，唉，这就是实力的差距。

------------
## 大致思路：
这道题是一道经典的树上 DP 题，告诉了我们树上 DP 的~~险恶~~重要性。我们设 $dp[u][i]$ 是在 $i$ 点建立一个中转站之后 $u$ 点以及子树得到信息的代价最小值，好了这就是这个 DP 题的**子问题**，$ans[u]$ 表示使得 $dp[u][i]$ 最小的 $i$（也就是以 $u$ 为**中心站到附近点的距离最小值**）。第二步，设计算法，首先我们跑一遍最短路得出各个点之间的最短距离，并存入 $dis$ 数组，方便之后使用。

接着，我们用循环预处理出**在每个点建立中心站时所花费的金钱**，于是我们便可以推出 $dis[u][i] = d[dis[u][i]] + K$ 的预处理公式。之后，我们考虑 $u$ 的节点 $v$，对于 $v$ 来说，要么选择这届使用 $ans_i$ 中的信息，多建一个中央站，此时的代价为 $dp[v][ans_v]$，要么就直接调用 $i$，那么代价就是 $dp[v][i] - K$，在求出所有 $dp[u][i]$ 就可以得出最小值 $ans[u]$，不断往复。最终就可以得出 $dp[1][ans[1]]$，即为最小代价和。

最后，就是求路径的阶段。在调用函数时，我们先用 $path$ 数组存入 $x$ 节点，接着，我们通过 $dp[v][ans[v]]$ 和 $dp[v][i] - K$ 的大小关系就可以知道 $v$ 点是从那个点获取的信息，也就是路径。



------------
## 具体代码：

```c++

#include <bits/stdc++.h>
using namespace std;
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
const int INF = 0x3f3f3f3f, maxn = 185;
int n, K, d[maxn], dis[maxn][maxn], m[maxn][maxn], dp[maxn][maxn], ans[maxn], path[maxn];
void dfs(int u, int fa)
{
    for (int i = 1; i <= n; i++)
    {
        dp[u][i] = d[dis[u][i]] + K;
    }
    for (int v = 1; v <= n; v++)
    {
        if (m[u][v] && v != fa)
        {
            dfs(v, u);
            for (int i = 1; i <= n; i++)
            {
                dp[u][i] += min(dp[v][ans[v]], dp[v][i] - K);
            }
        }
    }
    ans[u] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (dp[u][i] < dp[u][ans[u]])
        {
            ans[u] = i;
        }
    }
}
void take_down_the_path(int u, int fa, int i)
{
    path[u] = i;
    for (int v = 1; v <= n; v++)
    {
        if (m[u][v] && v != fa)
        {
            if (dp[v][ans[v]] < dp[v][i] - K)
            {
                take_down_the_path(v, u, ans[v]);
            }
            else
            {
                take_down_the_path(v, u, i);
            }
        }
    }
}
void floyd()
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}
int main()
{
    n = read();
    K = read();
    for (int i = 1; i < n; i++)
    {
        d[i] = read();
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i != j)
            {
                dis[i][j] = INF;
            }
            else
            {
                dis[i][j] = 0;
            }
        }
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        u = read();
        v = read();
        dis[u][v] = 1;
        dis[v][u] = 1;
        m[u][v] = 1;
        m[v][u] = 1;
    }
    floyd();
    dfs(1, 0);
    cout << dp[1][ans[1]] << endl;
    take_down_the_path(1, 0, ans[1]);
    for (int i = 1; i <= n; i++)
    {
        cout << path[i] << ' ';
    }
    return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/120906791)



---

## 作者：guosoun (赞：2)

首先，注意到 $d$ 是递增的，也就是说每个城市会选择距离他最近的「区域信息中心」。

可以发现在此时，对于每个「区域信息中心」，**把他选定**的城市一定是一个**联通块**。

我们考虑将问题转化为：把树分为若干个联通块，对于每个联通块，选择一个「区域信息中心」，表示这个「联通块内的所有点」都选择了这个「区域信息中心」。每种方案的代价为：「每个点的 $d_{len}$」+「联通块个数」乘 $k$。

这个转化显然有一些问题：并不是所有情况，都对应这一种合法的「区域信息中心选择方案」。

但是可以发现，每种「区域信息中心」选择方案，都被上述问题考虑了，而那些不合法的方案，都不可能成为最优的（感性理解）。

所以，我们求出新问题的最优解，一定是原问题的最优解。

新问题的 DP 就非常简单了，我们考虑对于每个联通块，在其根部计算 $k$ 的贡献。

 $dp(i, j)$ 表示 $i$ 的子树里，$i$ 选定的「区域信息中心」为 $j$，转移很简单不说了，由于 $n$ 的范围，$O(n)$ 转移即可，但容易做到 $O(1)$。

[代码](https://codeforces.com/contest/70/submission/209955535)。





---

## 作者：Moyou (赞：1)

> 通常和到关键点的距离有关的一些树形 DP，初见可能比较棘手，容易在状态设计上卡住。

## [CF70E] Information Reform

设置若干关键点，使得所有点到距离最近的关键点的代价之和最小，$i$ 到 $j$ 的代价定义为 $D(i, j) = d_{dist(i, j)}$，需要输出方案。

$\bcancel{n\le 180}\color{red}n\le 5000$，存在 $O(n^2)$ 做法。

仔细思考，由于题目中的距离代价很鬼畜，没法拆贡献，一种可能性是我们需要对于一个点确切找到它对应的关键点。

考虑状态设计 $f_{u, i}$ 表示考虑 $u$ 子树内点的贡献，且距离 $u$ 最近的点是 $i(i\in \text{subtree}_u)$，$g_{u, i}$ 表示考虑 $u$ 子树内点的贡献，且距离 $u$ 最近的点是 $i(i\notin \text{subtree}_u)$，辅助数组 $F_u = \min_i f_{u, i}$。

考虑转移，设 $p$ 是 $u$ 的儿子，且 $i$ 在 $p$ 的子树里面，则：
$$
\begin{aligned}
f_{u, u} &= k + \sum_{(u, v)\in \text E}\min(F(v), g_{v, u})\\
f_{u, i} &= D(u, i) + f_{p, i} + \sum_{v \ne p,(u, v)\in \text E} \min(F(v), g_{v, i})\\
g_{u, i} &= D(u, i) + \sum_{(u, v)\in \text E} \min(F_v, g_{v, i})
\end{aligned}
$$

记录前驱即可完成这道题。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
#define int long long
using namespace std;
const int N = 3000 + 10, INF = 1e18, mod = 998244353;

int n, m, k, c[N], f[N][N], F[N], g[N][N], ft[N], dep[N], dis[N], lca[N][N], dfn[N], sz[N], timestamp, pos[N], d[N], to[N];
vector<int> G[N];
void dfs(int u, int fa) {
    ft[u] = fa, dep[u] = dep[fa] + 1, dfn[u] = ++ timestamp, sz[u] = 1, pos[timestamp] = u;
    for(auto v : G[u]) if(v != fa) dfs(v, u), sz[u] += sz[v];
}
void LCA(int u) {
    lca[u][u] = u;
    for(auto v : G[u]) {
        if(v == ft[u]) continue;
        LCA(v);
        for(int i = dfn[u]; i < dfn[v]; i ++)
            for(int j = dfn[v]; j < dfn[v] + sz[v]; j ++)
                lca[pos[i]][pos[j]] = lca[pos[j]][pos[i]] = u;
    }
}
int dist(int a, int b) {
    return d[dep[a] + dep[b] - 2 * dep[lca[a][b]]];
}
int sum[N], coef[N];
void dfs2(int u) {
    for(auto v : G[u]) if(v != ft[u]) dfs2(v);
    for(int i = 1; i <= n; i ++) sum[i] = 0, coef[i] = 0;    
    for(auto v : G[u]) {
        if(v == ft[u]) continue;
        for(int i = 1; i <= n; i ++) {
            sum[i] += min(g[v][i], F[v]);
            if(lca[i][v] == v) coef[i] = f[v][i] - min(g[v][i], F[v]);
        }
    }
    f[u][u] = k + sum[u];
    F[u] = f[u][u], to[u] = u;
    for(int i = 1; i <= n; i ++) if(u != i) {
        if(lca[u][i] == u) {
            f[u][i] = dist(u, i) + sum[i] + coef[i], F[u] = min(F[u], f[u][i]);
            if(f[u][i] == F[u]) to[u] = i;
        }
        else {
            g[u][i] = sum[i] + dist(u, i);
        }
    }
}
int bel[N];
void print(int u, int i) {
    if(i == -1 || (g[u][i] >= F[u])) bel[u] = to[u];
    else bel[u] = i;
    for(auto v : G[u]) if(v != ft[u]) print(v, bel[u]);
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i < n; i ++) cin >> d[i];
    for(int i = 1, a, b, c; i < n; i ++) cin >> a >> b, G[a].push_back(b), G[b].push_back(a);
    dfs(1, 0), LCA(1);
    dfs2(1); 
    cout << F[1] << '\n';
    print(1, -1);
    for(int i = 1; i <= n; i ++) cout << bel[i] << ' '; cout << '\n';
    return 0;
}
```

---

## 作者：zhangxy__hp (赞：0)

设 $f_{u,i}$ 表示 $u$ 接受 $i$ 的信号，$u$ 的子树内的答案。那么可以枚举 $u$ 的儿子 $v$ 接受信号的节点来转移。注意当 $v$ 也枚举到 $i$ 时要减去重复的 $k$。

考虑构造方案，设 $ans_u$ 表示答案。首先可以求出 $ans_1$。对于 $u$ 的每个儿子 $v$，计算 $u$ 是怎么从 $v$ 转移来的即可。仍然注意当 $v$ 枚举到 $ans_u$ 时要减去重复的 $k$。

用 Floyd 计算两两之间的距离，时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define pb push_back
using namespace std;
namespace asbt{
namespace cplx{bool begin;}
const int maxn=205,inf=0x3f3f3f3f3f3f3f3f;
int n,m,a[maxn],ans[maxn];
int dis[maxn][maxn];
int f[maxn][maxn];
vector<int> e[maxn];
il void dfs1(int u,int fa){
	for(int i=1;i<=n;i++){
		f[u][i]=a[dis[u][i]]+m;
	}
	for(int v:e[u]){
		if(v==fa){
			continue;
		}
		dfs1(v,u);
		for(int i=1,tmp;i<=n;i++){
			tmp=f[u][i];
			f[u][i]+=f[v][i]-m;
			for(int j=1;j<=n;j++){
				f[u][i]=min(f[u][i],tmp+f[v][j]);
			}
		}
	}
}
il void dfs2(int u,int fa){
	for(int v:e[u]){
		if(v==fa){
			continue;
		}
		int res=inf;
		for(int i=1;i<=n;i++){
			if(res>f[v][i]){
				res=f[v][i],ans[v]=i;
			}
		}
		if(f[v][ans[u]]-m<f[v][ans[v]]){
			ans[v]=ans[u];
		}
		dfs2(v,u);
	}
}
namespace cplx{
	bool end;
	il double usdmem(){return (&begin-&end)/1048576.0;}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		cin>>a[i];
	}
	memset(dis,0x3f,sizeof dis);
	for(int i=1;i<=n;i++){
		dis[i][i]=0;
	}
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].pb(v),e[v].pb(u);
		dis[u][v]=dis[v][u]=1;
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=n;j++){
//			cout<<dis[i][j]<<" ";
//		}
//		puts("");
//	}
	dfs1(1,0);
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=n;j++){
//			printf("%2d ",f[i][j]);
//		}
//		puts("");
//	}
	int res=inf;
	for(int i=1;i<=n;i++){
		if(res>f[1][i]){
			res=f[1][i],ans[1]=i;
		}
	}
	cout<<res<<"\n";
	dfs2(1,0);
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	}
	return 0;
}
}
signed main(){return asbt::main();}
```

---

