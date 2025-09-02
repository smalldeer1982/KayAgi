# Exploration plan

## 题目描述

The competitors of Bubble Cup X gathered after the competition and discussed what is the best way to get to know the host country and its cities.

After exploring the map of Serbia for a while, the competitors came up with the following facts: the country has $ V $ cities which are indexed with numbers from $ 1 $ to $ V $ , and there are $ E $ bi-directional roads that connect the cites. Each road has a weight (the time needed to cross that road). There are $ N $ teams at the Bubble Cup and the competitors came up with the following plan: each of the $ N $ teams will start their journey in one of the $ V $ cities, and some of the teams share the starting position.

They want to find the shortest time $ T $ , such that every team can move in these $ T $ minutes, and the number of different cities they end up in is at least $ K $ (because they will only get to know the cities they end up in). A team doesn't have to be on the move all the time, if they like it in a particular city, they can stay there and wait for the time to pass.

Please help the competitors to determine the shortest time $ T $ so it's possible for them to end up in at least $ K $ different cities or print -1 if that is impossible no matter how they move.

Note that there can exist multiple roads between some cities.

## 说明/提示

Three teams start from city 5, and two teams start from city 2. If they agree to move for 3 minutes, one possible situation would be the following: Two teams in city 2, one team in city 5, one team in city 3 , and one team in city 1. And we see that there are four different cities the teams end their journey at.

## 样例 #1

### 输入

```
6 7 5 4
5 5 2 2 5
1 3 3
1 5 2
1 6 5
2 5 4
2 6 7
3 4 11
3 5 3
```

### 输出

```
3```

# 题解

## 作者：BigJoker (赞：2)

考虑如果要将 $x_i$ 移动到 $u$，那么实际上就是在求 $x_i,u$ 之间的最短路，观察到点数不超过 $600$，考虑用 floyd 跑最短路，得到无向图之间两两点之间的最短路，处理到此最短路后，便可以很容易判断出一个团队移动的一个特定点的最小距离。

观察到答案最多不超过 $1731311$，考虑二分答案，即二分最大的点到对应位置上的距离。

考虑如何写 check 函数，假设 check 的值为 $p$，那么对于所有的 $x_i$，将 $i$ 与 $j\in{[1,v]},dis_{x_i,j}\le p$ 连边，意为团队 $i$ 可以花费不超过 $p$ 的时间到达 $j$，接下来考虑如何让至少 $k$ 个点上有团队，本质上可以理解为让 $k$ 个团队通过上述连边到达 $k$ 个不同的位置，这个过程可以用二分图匹配实现：将团队划为一个部分，将 $v$ 个点划为一个部分，将这两个部分进行最大匹配，看最终的匹配对数是否可以达到 $k$，通过这样，即可完成 check 的过程。

判断 $-1$ 可以通过 check 一下最大的答案是否可行实现，这里不展开细说。

```cpp
#include<bits/stdc++.h>
#define mem(a,x) memset(a,x,sizeof(a))
#define re register
#define il inline
using namespace std;
const int N=6e2+5;
int n,m,h,g,vis[N],x[N],cp[N],dis[N][N];
vector<int>G[N];
bool dfs(int pos,int tag){
	if(vis[pos]==tag) return 0;
	vis[pos]=tag;
	for(auto to:G[pos]){
		if(!cp[to] || dfs(cp[to],tag)){
			cp[to]=pos;
			return 1;
		}
	}
	return 0;
}
bool check(int p){
	int res=0;
	for(re int i=1;i<=h;i++) G[i].clear(); 
	for(re int i=1;i<=h;i++)
		for(re int j=1;j<=n;j++) if(dis[x[i]][j]<=p) G[i].push_back(j);
	for(re int i=1;i<=h;i++) vis[i]=0;
	for(re int i=1;i<=n;i++) cp[i]=0;
	for(re int i=1;i<=h;i++) res+=dfs(i,i);
	return res>=g;
}
int solve(int l,int r){
	if(l==r) return l;
	if(l+1==r) return check(l)?l:r;
	int mid=l+r>>1;
	return check(mid)?solve(l,mid):solve(mid+1,r);
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>h>>g;
	mem(dis,0x3f3f3f3f);
	for(re int i=1;i<=h;i++) cin>>x[i];
	for(re int i=1;i<=n;i++) dis[i][i]=0;
	for(re int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		dis[u][v]=dis[v][u]=min(dis[u][v],w);
	}
	for(re int k=1;k<=n;k++)
		for(re int i=1;i<=n;i++)
			for(re int j=1;j<=n;j++) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	if(!check(1731311)){
		cout<<-1;
		return 0;
	}
	cout<<solve(0,1731311);
	return 0;
}
```

---

## 作者：JWRuixi (赞：2)

~~这道题真的是，太坑了~~
## 题意

我觉得已经解释的很清楚了--__--

## 思路

这道题时间上给的最大值让它天然用二分解决

来看一下，发现这个数据能用 Floyd 求最短时间。

所有人乱走可以看成是网络流流来流去，所以加上一波 Dinic 求最大值就行了。

具体来讲就是 $i$ 节点，在 $tx$ 时间里能够到达 $j$ 节点的话就加一条边。

余下的连一下超源和超汇。

~~还有，我诚挚推荐不要用长长，用整形就行了，不知道咋就错了~~。

## Code

```cpp
#include <bits/stdc++.h>
#define maxn 2005
#define maxm 1500005
using namespace std;

namespace q_wr {
	inline int read() {
		char c = getchar();
		int x = 0, f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + c - '0';
			c = getchar();
		}
		return x * f;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using namespace q_wr;

struct edge {
	int v, nxt, w;
} e[maxm];

int n, m, s, t = 2002, head[maxn], dep[maxn], dis[maxn][maxn], k = 1;
int vs, maxk, a[maxn];

inline void add (int u, int v, int w) {
	e[++k] = {v, head[u], w};
	head[u] = k;
}

inline bool bfs () {
	memset(dep, 0, sizeof dep);
	queue <int> q;
	dep[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			if (e[i].w && !dep[v]) {
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
	}
	return dep[t];
}

inline int dfs (int u, int in) {
	if (u == t) return in;
	int out = 0;
	for (int i = head[u]; i && in; i = e[i].nxt) {
		int v = e[i].v;
		if (e[i].w && dep[v] == dep[u] + 1) {
			int res = dfs(v, min(e[i].w, in));
			in -= res;
			out += res;
			e[i].w -= res;
			e[i ^ 1].w += res;
		}
	}
	if (!out) dep[u] = 0;
	return out;
}//Dinic模板 

inline void floyd () {
	for (int l = 1; l <= vs; l++)
		for (int i = 1; i <= vs; i++)
			for (int j = 1; j <= vs; j++)
				if (dis[i][j] > dis[i][l] + dis[l][j])
					dis[i][j] = dis[i][l] + dis[l][j];
}//Floyd的模板 

inline bool check (int tx) {
	memset(head, 0, sizeof(head)), k = 1;
	for (int i = 1; i <= n; i++)
		add(s, i, 1), add (i, s, 0);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= vs; j++)
			if (dis[a[i]][j] <= tx)//注意位置在a[i] 
				add (i, j + n, 1), add (j + n, i, 0);
	for (int i = 1; i <= vs; i++)
		add (i + n, t, 1), add (t, i + n, 0);
	int res = 0;
	while (bfs())
		res += dfs(s, 1e9);
	return (res >= maxk);
}

signed main () {
	vs = read(), m = read(), n = read(), maxk = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= vs; i++) {
		for (int j = 1; j < i; j++)  {
			dis[i][j] = dis[j][i] = 1e9;
		}
	}
	for (int i = 0; i < m; i++) {
		int u = read(), v = read(), w = read();
		dis[u][v] = dis[v][u] = min(w, dis[u][v]);
	}
	floyd();
	register int mid, l = 0, r = 1731311;
	if (!check(r)) {
		puts("-1");
		return 0;
	}
	while (l < r) {
		mid = (l + r) >> 1;
		if (check(mid))
			r = mid;
		else
			l = mid + 1;
	}
	write(l);
}
```

---

## 作者：happy_dengziyue (赞：2)

### 1 思路

[题意传送门](https://www.luogu.com.cn/discuss/353966)

我们可以首先使用 `Floyd` 算法求出全源最短路。

使用二分算法来求出答案。

设当前判断的时间为 $ti$。

拆点。让 $i$ 点表示第 $i$ 号团队，$j+n$ 表示 $j$ 点。

如果 $dis[x[i]][j]\le ti$，就从 $i$ 到 $j+n$ 连一条容量为 $1$ 的边。

当然了，源点到每个团队与每个点到汇点，都要连容量为 $1$ 的边。

跑一遍网络最大流，如果最大流大于等于 $k$，那么说明花费 $ti$ 的时间是可行的，就往更小的时间二分。

否则说明它不可行，往大的时间二分。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define inf 0x3f3f3f3f
int vs;//点数
int es;//边数
int n;//团队数
int k;//要求点数
#define s 0//源点
#define t 1202//汇点
int x[1220];//团队位置
int dis[1220][1220];//距离
struct E{
	int u,v,w,a,nx;
}e[1000002];//边
int ei;//下标
int fir[1220];//开始路径
int l=0,r=1731312,mid;//二分系列
int de[1220];//深度
inline int mi(int a,int b){
	return a<b?a:b;
}
inline void addedge(int u,int v,int w){
	++ei; e[ei].u=u; e[ei].v=v; e[ei].w=w; e[ei].a=ei+1; e[ei].nx=fir[u]; fir[u]=ei;
	++ei; e[ei].u=v; e[ei].v=u; e[ei].w=0; e[ei].a=ei-1; e[ei].nx=fir[v]; fir[v]=ei;
}
bool bfs(){
	memset(de,0,sizeof(de));
	queue<int>q;
	int u;
	de[s]=1;
	q.push(s);
	while(!q.empty()){
		u=q.front();
		q.pop();
		for(int i=fir[u],v;i;i=e[i].nx){
			v=e[i].v;
			if(e[i].w&&!de[v]){
				de[v]=de[u]+1;
				q.push(v);
			}
		}
	}
	return de[t];
}
int dfs(int u,int f){
	if(u==t||!f)return f;
	int res=0;
	for(int i=fir[u],v,w;i;i=e[i].nx){
		v=e[i].v;
		if(e[i].w&&de[u]+1==de[v]){
			w=dfs(v,mi(f,e[i].w));
			if(w){
				e[i].w-=w;
				e[e[i].a].w+=w;
				f-=w;
				res+=w;
				if(!f)break;
			}else de[v]=0;
		}
	}
	return res;
}
bool check(int ti){
	ei=0;
	memset(fir,0,sizeof(fir));
	for(int i=1;i<=n;++i)addedge(s,i,1);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=vs;++j){
			if(dis[x[i]][j]<=ti)addedge(i,j+n,1);
		}
	}
	for(int i=1;i<=vs;++i)addedge(i+n,t,1);
	int res=0;
	while(bfs())res+=dfs(s,inf);
	return res>=k;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF0852D_1.in","r",stdin);
	freopen("CF0852D_1.out","w",stdout);
	#endif
	scanf("%d%d%d%d",&vs,&es,&n,&k);
	for(int i=1;i<=n;++i){
		scanf("%d",x+i);
	}
	memset(dis,inf,sizeof(dis));
	for(int i=1;i<=vs;++i)dis[i][i]=0;
	for(int i=1,u,v,w;i<=es;++i){
		scanf("%d%d%d",&u,&v,&w);
		dis[u][v]=dis[v][u]=mi(dis[u][v],w);//记得是取最小值
	}
	for(int k=1;k<=vs;++k){
		for(int i=1;i<=vs;++i){
			for(int j=1;j<i;++j){
				dis[i][j]=dis[j][i]=mi(dis[i][j],dis[i][k]+dis[k][j]);//Floyd算法
			}
		}
	}
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	if(l>1731311)printf("-1\n");
	else printf("%d\n",l);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/58170205)

By **dengziyue**

---

## 作者：Sangber (赞：2)

[$$\Large{\color{CornflowerBlue}{\mathfrak{Blog}}}$$](https://www.cnblogs.com/zsbzsb/p/11684039.html)

----
### 题目描述
给定一张 $V$ 个点，$M$ 条边的边带权无向图，有 $N$ 个人分布在图上的点上，第 $i$ 个人在 $x_i$ 这个点上，定义从一个点走到另一个点的时间为所走的路径上所有边权之和，问至少过多久才可以满足至少有 $K$ 个点上有人。  

数据范围：  
$1\le V \le600,1\le E \le 20000,1\le N \le\min(V,200),1\le K \le N$
### 基本思路
首先可以二分答案。  
对于当前二分到的 $mid$，我们对于每一个人，都向他可以去到的点连一条边（路径的最短距离可以用 $\text{Floyd}$ 预处理一下)，然后直接跑二分图最大匹配就好了。  
### 细节注意事项
记得判无解
### 参考代码
有需要的话可以去看我博客 $\uparrow\uparrow\uparrow$

---

## 作者：SDLTF_凌亭风 (赞：1)

我不明白你们是怎么一眼看出二分答案的……手玩几组数据之后发现确实是单调的。

那么你二分时间，对每一个人，把他和他能去的点连边，然后跑最短路就行了。

观察到 $V$ 很小，大力 Floyd 走起！

**警钟长鸣：如果你跟我的 Floyd 写法一样，请不要在初始化的时候设置为整形最大值！**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, p, k, at[703];
int dis[703][703], vis[703], marker[703], G[703][703];
int dfs(int u) {
	for(int i = 1; i <= n; ++ i) {
		if(vis[i] || !G[u][i]) continue;
		vis[i] = 1;
		if(marker[i] == 0 || dfs(marker[i])) return (marker[i] = u), 1;
	}
	return 0;
}

bool check(int md) {
	memset(G, 0, sizeof G), memset(marker, 0, sizeof marker);
	for(int i = 1; i <= p; ++ i) for(int j = 1; j <= n; ++ j) G[i][j] = (dis[at[i]][j] <= md);
	int res = 0;
	for(int i = 1; i <= p; ++ i) memset(vis, 0, sizeof vis), res += dfs(i);
	return res >= k;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> p >> k;
	for(int i = 1; i <= p; ++ i) cin >> at[i];
	for(int i = 1; i <= n; ++ i) for(int j = 1; j <= n; ++ j) dis[i][j] = ((i == j) ? 0 : 0x3f3f3f3f);
	for(int i = 1, u, v, w; i <= m; ++ i) cin >> u >> v >> w, dis[v][u] = dis[u][v] = min(dis[u][v], w);
	for(int k = 1; k <= n; ++ k) for(int i = 1; i <= n; ++ i) for(int j = 1; j <= n; ++ j) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	int l, r, mid; for(l = 0, r = 1731311 + 1, mid; l < r;) {
		mid = (l + r) >> 1;
		(check(mid)) ? (r = mid) : (l = mid + 1);
	}
	cout << (l > 1731311 ? (-1) : (l));
}
```

---

## 作者：lzyqwq (赞：1)

二分答案 + 二分图匹配。

前言：这题为什么要写网络流啊。

~~其实我会网络流~~。

首先，我们需要发现一个性质：

- 令一个有解的时间为 $t_0$，若一个时间 $t_1>t_0$。则 $t_1$ 有解，因为 $t_1$ 在 $t_0$ 这么多时间的基础上再加上一些时间，显然可以先用 $t_0$ 的时间达到有解状态，然后剩下的时间不破坏有解状态，就是一种有解的方案。

- 令一个无解的时间为 $t_2$，若一个时间 $t_3<t_2$，则 $t_3$ 无解。设 $t_2$ 时间内到达点的人为 $p_2$（$p_3$ 同理），$q$ 为 $t_3+1\sim t_2$ 时间内到达的人，显然有 $p_2=p_3+q$，那么 $p_3=p_2-q$。因为是人数，所以 $q \ge 0$，因此 $p_3\le p_2$，因为 $t_2$ 无解，所以 $p_2<k$，因此 $p_3<k$，$t_3$ 无解。

这个不就是单调性吗？因此考虑二分时间。

用什么作为 `check()` 函数？二分图最大匹配。

为什么呢？因为若不是匹配，相当于是多个人到达同一个点，显然若多出来的那些人不到达这个点，这个点还是被一个人覆盖，覆盖数不变。因此可以让剩余的人去往其它点，扩大覆盖数，从而使当前状态更趋近于有解。一个人对应一个点，这不就是匹配吗？

那么此时一组匹配就相当于一个人对应了一个点，最大匹配相当于最多的人对应了最多的点，即最多被人覆盖的点数。

若最大匹配 $\ge k$，那么按照最大匹配的方式去覆盖就可以得到解，返回有解。否则覆盖点数最多的方案都 $<k$，显然所有的方案都 $<k$，返回无解。

所以我们将人看作左部点，顶点看作右部点，若 $dis_{x_i,j}\le t$（$t$ 是二分的时间），则说明 $i$ 这个人可以在 $t$ 时间内到达 $j$，即可以匹配，连边 $i\rightarrow j$。

因此，我们还需要 `floyd` 预处理出任意两点间的最短路。

`check()` 中的二分图匹配我用的 `Hungary`，不比 `Dinic` 差，`vector` 吸氧可以最优解 `rk2`。

注意判重边，否则喜提 `WA on #6`。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 605;
int n, m, t, k, a[N], f[N][N], ma[N << 1], l, r = 1731311, ans = -1;
vector<int> g[N << 1];
bool vis[N << 1];
bool dfs(int x) {
    for (int i : g[x]) {
        if (!vis[i]) {
            vis[i] = 1;
            if (!ma[i] || dfs(ma[i])) {
                ma[i] = x;
                return 1;
            }
        }
    }
    return 0;
}
inline bool check(int x) {
    memset(g, 0, sizeof(g));
    for (int i = 1; i <= t; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (f[a[i]][j] <= x) {
                g[i].emplace_back(j + t);//避免与左部点冲突
            }
        }
    }
    memset(ma, 0, sizeof(ma));
    int s = 0;
    for (int i = 1; i <= t; ++i) {
        memset(vis, 0, sizeof(vis));
        s += dfs(i);
    }
    return s >= k;
}
int main() {
    memset(f, 0x3f, sizeof(f));
    scanf("%d%d%d%d", &n, &m, &t, &k);
    for (int i = 1; i <= n; ++i) {
        f[i][i] = 0;
    }
    for (int i = 1; i <= t; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1, u, v, w; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        f[u][v] = f[v][u] = min(f[u][v], w);//判重边
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                f[j][k] = min(f[j][k], f[j][i] + f[i][k]);
            }
        }
    }
    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            r = (ans = m) - 1;
        } else {
            l = ++m;
        }
    }
    printf("%d", ans);
}
```


---

## 作者：wgyhm (赞：1)

## 【网络流记录】CF852D Exploration plan

### Description

给定一个 $v$ 个点 $e$ 条边的带权无向图，在图上有 $n$ 个人，第 $i$ 个人位于点 $x_i$，一个人通过一条边需要花费这条边的边权的时间。

现在每个人可以自由地走。求最短多少时间后满足结束后有人的节点数 $\ge m$。

$n,v\le 500$

### solution

$v\le 500$ 首先考虑把两两之间的最短路预处理出来，用 $\text{Floyd}$ 即可做到 $O(v^3)$。

考虑二分，变成一个判定问题。也就是求在一定时间内满足结束后的有人的节点数最大。

考虑最大流，建图比较显然。具体的，$(s,i,1)$ ，然后 $i$ 向每个可在一定时间内到达的地点 $j$ ，$(i,j,1)$，最后 $(j,t,1)$。

### Code

```cpp
#define rg register
#define ll long long 
#define maxn 1005
#define maxm 2000005
#define put() putchar('\n')
const int inf=1e9;
int dis[maxn][maxn],v,e,n,m,f[maxn];
namespace Dinic{
	int head=1,h[maxn*2],now[maxn*2],deep[maxn*2],s,t;
	queue<int>q;
    struct yyy{
    	int to,w,z;
    	inline void add(int x,int y,int W){
    		to=y;z=h[x];h[x]=head;w=W;
		}
	}a[maxm];
	inline void ins(int x,int y,int z){
		a[++head].add(x,y,z);
		a[++head].add(y,x,0);
	}
	inline void clear(void){
		head=1;memset(h,0,sizeof(h));
	}
	inline int bfs(void){
		while (!q.empty()) q.pop();
		memset(deep,0,sizeof(deep));
		rg int i,x;q.push(s);deep[s]=1;
		while (!q.empty()){
			x=q.front();q.pop();now[x]=h[x];
			for (i=h[x];i;i=a[i].z)	if (!deep[a[i].to]&&a[i].w)	deep[a[i].to]=deep[x]+1,q.push(a[i].to);
		}
	    return deep[t];
	}
	inline int dfs(int x,int in){
		if (x==t||!in) return in;
		rg int rest=in,sum,i;
		for (i=now[x];i&&rest;now[x]=i,i=a[i].z)
		    if (a[i].w&&deep[a[i].to]==deep[x]+1){
			    sum=dfs(a[i].to,min(a[i].w,rest));
			    if (!sum) deep[a[i].to]=0;
			    a[i].w-=sum;a[i^1].w+=sum;rest-=sum;
		    }
		return in-rest;
	}
	inline int Dinic(void){
		int ans=0;
		while (bfs()) ans+=dfs(s,inf);
		return ans;
	}
}//Dinic板子
inline int check(int val){
	Dinic::clear();Dinic::s=0;Dinic::t=n+v+1;
	rg int i,j;
	for (i=1;i<=n;i++)
	    for (j=1;j<=v;j++)
	        if (dis[f[i]][j]<=val) Dinic::ins(i,j+n,1);
	for (i=1;i<=n;i++) Dinic::ins(Dinic::s,i,1);
	for (i=n+1;i<=n+v;i++) Dinic::ins(i,Dinic::t,1);
	int sum=Dinic::Dinic();
	return sum>=m;
}
signed main(){
	rg int x,y,z,i,j,k;
	memset(dis,0x3f,sizeof(dis));
	read(v);read(e);read(n);read(m);
	for (i=1;i<=n;i++) read(f[i]);
	while (e--){
		read(x);read(y);read(z);
	    dis[x][y]=dis[y][x]=min(z,dis[x][y]);
	}
	for (i=1;i<=v;i++) dis[i][i]=0;
	for (k=1;k<=v;k++)
	    for (i=1;i<=v;i++)
	        for (j=1;j<=v;j++)
	            if (dis[i][j]>dis[i][k]+dis[k][j]) dis[i][j]=dis[i][k]+dis[k][j];
	rg int mid,l=-1,r=1731312;
	if (!check(r)) return puts("-1"),0;
	while (l+1<r){
		mid=l+r>>1;
		if (check(mid)) r=mid;
		else l=mid;
	}
	printf("%d",r);
	return 0;
}
```



 

---

## 作者：pidan (赞：1)

## 【题意翻译】
给定一个$V$ 个点$E$ 条边的带权无向图，在图上有$N$ 个人，第$i$ 个人位于点$x_ 
i$	，一个人通过一条边需要花费这条边的边权的时间。

现在每个人可以自由地走。求最短多少时间后满足结束后有人的节点数$\geq K$

$N,V \leq 500$
## 【题目分析】
首先发现V很小，直接用$Floyd$跑一遍全源最短路径。

然后考虑如何求时间，这个其实是图论中一个很经典的二分+图论的模型，那么我们可以用一个二分寻找$mid$，连上所有长度$\leq mid$的边，用图论来$check$。

接下来就要选择图论使用的模型了。在一个图上，有一些人从一个点走向另一个点，很容易想到网络流中的最大流。由于每个点只要有人就行，那么让每个点向超级汇点$t$连一条容量为$1$的边，代表这个点对答案能产生$1$的流量，从超级源点$s$向每个点连一条容量为这个点人数的边，代表这个点能流出等同于这个点人数的流量，然后将$\leq mid$的边作为网络中的一条边，容量为$inf$，跑最大流，判断是否$\geq K$。

$tips:$
1. 建图的时候要拆点，拆成入口和出口，不然会出现流量分配的问题
1. 每次check记得memset
1. 重边要取最小值

愉快的贴代码时间
```cpp
#include<bits/stdc++.h>
#define inf 1e15
using namespace std;
int read(){
	int w=0,h=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')h=-h;ch=getchar();}
	while(ch>='0'&&ch<='9'){w=w*10+ch-'0';ch=getchar();}
	return w*h;
}
int n,m,s,t,K,cnt,sum;
int cow[610],barn[610];
int floyd[610][610];
struct Dinic{
	struct node{
		int next,to,cap,flow;
	}edge[3000010];
	int head[10010],num;
	int cur[10010];
	int dist[10010];
	queue<int>q;
	void add(int u,int v,int cap,int flow){
		edge[++num].next=head[u];
		edge[num].to=v;
		edge[num].cap=cap;
		edge[num].flow=flow;
		head[u]=num;
		return;
	}
	void Add(int u,int v,int cap){
		add(u,v,cap,0);
		add(v,u,0,0);
		return;
	}
	bool bfs(){
		memset(dist,0,sizeof(dist));
		dist[s]=1;
		q.push(s);
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int i=head[u];i;i=edge[i].next){
				int v=edge[i].to;
				if(!dist[v]&&edge[i].cap>edge[i].flow){
					dist[v]=dist[u]+1;
					q.push(v);
				}
			}
		}
		return dist[t];
	}
	int dfs(int u,int flow){
		if(u==t)return flow;
		int fl=0;
		for(int i=cur[u];i;i=edge[i].next){
			cur[u]=i;
			int v=edge[i].to;
			if(dist[u]+1==dist[v]&&edge[i].cap>edge[i].flow){
				int p=dfs(v,min(flow,edge[i].cap-edge[i].flow));
				if(p){
					edge[i].flow+=p;
					edge[i^1].flow-=p;
					flow-=p;
					fl+=p;
					if(!flow)break;
				}
			}
		}
		if(!fl)dist[u]=0;
		return fl;
	}
	int solve(){
		int flow=0;
		while(bfs()){
			memcpy(cur,head,sizeof(cur));
			int p;
			while(p=dfs(s,1e9))flow+=p;
		}
		return flow;
	}
	void memst(){
		memset(head,0,sizeof(head));
		num=1;
	}
	bool check(int x){
		memst();
		for(int i=1;i<=n;i++)Add(i+n,t,1);
		for(int i=1;i<=n;i++){
			if(cow[i])Add(s,i,cow[i]);
			for(int j=1;j<=n;j++)
				if(floyd[i][j]<=x)
					Add(i,j+n,1e9);
		}
		return solve()>=K;
	}
}ans;
signed main(){
	n=read();m=read();cnt=read();K=read();
	s=0;t=n+n+2;
    memset(floyd,0x3f,sizeof(floyd));
	for(int i=1;i<=cnt;i++)cow[read()]++;
	for(int i=1;i<=n;i++)floyd[i][i]=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		floyd[u][v]=floyd[v][u]=min(floyd[u][v],w);
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				floyd[i][j]=min(floyd[i][j],floyd[i][k]+floyd[k][j]);
	int l=0,r=1731311,res=-1;
	while(l<=r){
		int mid=l+r>>1;
		if(ans.check(mid))r=mid-1,res=mid;
		else l=mid+1;
	}
	printf("%d\n",res);
	return 0;
}
```


---

## 作者：未来姚班zyl (赞：0)

## 题目大意

在一张无向图上有 $n$ 支团队。对于一条边 $E_i$，一支团队要花 $T_i$ 的时间走过。团队之间互不影响，问至少需要多少时间，能够使得至少有 $k$ 个节点上存在至少一支团队。

## 题目分析

显然，对于一支团队，从其起始点到结束点，用时是两点的最短路。同时可以发现，节点数只有 $600$，所以可以先跑个 floyd 求个最短路。

接下来发现似乎没有什么直接的算法可以求出有 $k$ 个节点上有团队的情况下的最小时间消耗（想过生成树，但发现无法限制住团队的数量）。

显然，~~题目特别强调答案不会很大~~答案满足可二分性，我们可以二分答案，考虑如何判断。

许多算法无法使用，是由于这题的限制互相牵扯。但网络流非常擅长解决这种限制一大堆的问题！

建图还是比较经典的拆点，每个节点拆成入点和出点，且出点向汇点连边。对于每个团队，从源点向起始点连边，从起始点向能到达的点的出点连边。这些边流量均为一，最后判断最大流是否大于等于 $k$ 就行了。

最短路复杂度 $O(v^3)$。网络流时间复杂度：未知。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline ll read(){ll s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =1205,M=2e6+5,inf=2147000000;
const ll llf=1e18,mod=1e9+7;
const ui base=13331;
using namespace std;
int n,m,s,t,h[N],nxt[M],now[N],to[M],cnt=1,dep[N];ll w[M],ans;
void add(int a,int b,ll c){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,w[cnt]=c;
	to[++cnt]=a,nxt[cnt]=h[b],h[b]=cnt,w[cnt]=0;
}
inline bool bfs(){
	queue<int>q;
	memset(dep,-1,sizeof(dep));
	dep[s]=0,q.push(s),now[s]=h[s];
	while(!q.empty()){
		int x=q.front();q.pop();
		e(x){
			if(w[i]==0||dep[y]!=-1)continue;
			dep[y]=dep[x]+1,q.push(y),now[y]=h[y];
			if(y==t)return 1;
		}
	}
	return 0;
}
inline int dfs(int x,ll lim){
	if(x==t)return lim; 
	ll k,tmp=0;
	for(int i=now[x];i&&lim;i=nxt[i]){
		now[x]=i;
		int y=to[i];
		if(!w[i]||dep[y]^(dep[x]+1))continue;
		k=dfs(y,min(lim,w[i]));
		if(k==0)dep[y]=-1;
		w[i]-=k,w[i^1]+=k,tmp+=k,lim-=k;
	}
	return tmp;
}
int k,p[606],d,dis[605][605];
inline bool check(int x){
	memset(h,0,sizeof(h)),memset(now,0,sizeof(now));
	cnt=1,s=0,t=n*2+1,ans=0;
	rep(i,1,k){
		add(s,p[i],1);
		rep(j,1,n)if(dis[p[i]][j]<=x)add(p[i],j+n,1);
	}
	rep(i,1,n)add(i+n,t,1);
	while(bfs())ans+=dfs(s,inf);
	return ans>=d;
}
int main(){
	n=read(),m=read(),k=read(),d=read();
	rep(i,1,k)p[i]=read();
	memset(dis,0x3f,sizeof(dis));
	rep(i,1,n)dis[i][i]=0;
	for(int i=1,x,y,z;i<=m;i++)x=read(),y=read(),z=read(),dis[x][y]=dis[y][x]=min(dis[x][y],z);
	rep(k,1,n)rep(i,1,n)rep(j,1,n)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	int l=0,r=1731311,ans=-1;
	while(l<=r){
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout <<ans;
	return 0;
}
```


---

## 作者：happybob (赞：0)

首先发现答案可以二分，考虑如何判定。

首先用最短路算法跑全源最短路预处理 $d_{i,j}$ 表示 $i$ 到 $j$ 最短路。用 Floyd 做复杂度是 $O(n^3)$ 的，若使用 Dijkstra 算法则是 $O(nm \log m)$ 的，不过几种做法均可，因为复杂度瓶颈不在这里。

对于当前需要判定时间 $x$ 是否可以，我们发现任意一点对 $(i,j)$ 只需满足 $d_{i,j} \leq x$ 即可进行移动。

考虑网络流模型：

- 源点 $S$ 向每个有团队的点连边，容量为在这个点的团队数量。

- 每一对 $(i,j)$ 满足 $i$ 点上有团队且 $d(i,j) \leq x$，连 $i \rightarrow j+n$，容量为 $+\infty$，表示可以移动的人没有限制。我们不需要判断 $j$ 是否有团队。加上 $n$ 是为了区分有团队的点和普通点。

- 对于每个普通点 $j$，连 $j+n \rightarrow T$，容量为 $1$，若满流表示有人在点上，否则没有。

若 $S \rightarrow T$ 的最大流 $\geq k$，则时间 $x$ 可行，否则不可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int M = 605, N = 1e6 + 5;

int n, m, p, k;
vector<pair<int, int> > G[N];

int dis[M][M], S = 0, T;
bool vis[N];

int e[N], h[N], c[N], ne[N], idx;
int g[N], pdd[N];
int d[N], cur[N];

inline void add(int u, int v, int w)
{
	e[idx] = v, ne[idx] = h[u], c[idx] = w, h[u] = idx++;
	e[idx] = u, ne[idx] = h[v], c[idx] = 0, h[v] = idx++;
}

struct Node
{
	int u, d;
	Node(int _u, int _d): u(_u), d(_d){}
	bool operator<(const Node& g) const
	{
		return d > g.d;
	}
};

inline void dijkstra(int s)
{
	for (int i = 1; i <= n; i++) vis[i] = 0;
	dis[s][s] = 0;
	priority_queue<Node> q;
	q.push(Node(s, 0));
	while (q.size())
	{
		int u = q.top().u;
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto j : G[u])
		{
			if (dis[s][j.first] > dis[s][u] + j.second)
			{
				dis[s][j.first] = dis[s][u] + j.second;
				q.push(Node(j.first, dis[s][j.first]));
			}
		}
	} 
}

inline bool bfs()
{
	for (int i = 0; i <= T; i++) d[i] = cur[i] = -1;
	queue<int> q;
	q.push(S);
	d[S] = 0, cur[S] = h[S];
	while (q.size())
	{
		int u = q.front();
		q.pop();
		for (int i = h[u]; ~i; i = ne[i])
		{
			int j = e[i];
			if (c[i] > 0 && d[j] == -1)
			{
				d[j] = d[u] + 1;
				cur[j] = h[j];
				if (j == T) return 1;
				q.push(j);
			}
		}
	}
	return 0;
}

inline int dfs(int u, int lim)
{
	if (u == T) return lim;
	int sum = 0;
	for (int i = cur[u]; ~i && sum < lim; i = ne[i])
	{
		cur[u] = i;
		int j = e[i];
		if (c[i] > 0 && d[j] == d[u] + 1)
		{
			int w = dfs(j, min(c[i], lim - sum));
			if (!w) d[j] = -1;
			sum += w;
			c[i] -= w;
			c[i ^ 1] += w;
		}
	}
	return sum;
}

inline int dinic()
{
	int res = 0;
	while (bfs())
	{
		int p;
		while (p = dfs(S, INT_MAX)) res += p;
	}
	return res;
}

inline bool check(int x)
{
	for (int i = 0; i <= T + 5; i++) h[i] = -1;
	idx = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!pdd[i]) continue;
		for (int j = 1; j <= n; j++)
		{
			if (dis[i][j] <= x)
			{
				add(i, j + n, INT_MAX);
			}
		}
		add(S, i, pdd[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		add(i + n, T, 1);
	}
	return (dinic() >= k);
}

int main()
{
	memset(h, -1, sizeof h);
	memset(dis, 0x3f, sizeof dis);
	scanf("%d%d%d%d", &n, &m, &p, &k);
	T = n + n + 1;
	for (int i = 1; i <= p; i++) scanf("%d", &g[i]), pdd[g[i]]++;
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u].emplace_back(make_pair(v, w));
		G[v].emplace_back(make_pair(u, w));
	}
	for (int i = 1; i <= n; i++)
	{
		dijkstra(i);
	}
	int l = 0, r = 1731312, ans = -1;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：UperFicial (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF852D)

同步发表于我的 [$\text{cnblog}$](https://www.cnblogs.com/UperFicial/p/16038158.html)。

### $\texttt{Description}$

给你 $v$ 个点 $e$ 条边的带权无向图，$n$ 个人位于若干个点上且可以地走，最少多长时间至少有 $m$ 个点上至少有一个人。

### $\texttt{Solution}$

~~瞄了一眼题解才知道可以二分做。~~

直接做是不好做的，但是观察可得答案具有单调性，于是可以二分答案。

考虑二分一个 $k$，表示每个人的行走时间都不大于 $k$。

这样我们可以通过这个 $k$ 来建图，对于每个人与能走到的点连一条边。

连出来的图就是一个二分图了，左边是人，右边是图上的点，需要求的就是二分图最大匹配，因为一个人只能走到一个点上。

这样我们建立源点 $s$ 和汇点 $t$，对于 $s$ 连向每一个人，容量为 $1$，每个点连 $t$，容量同样为 $1$，跑一遍 $\text{Dinic}$ 即可。

另外需要预处理一个 $\Theta(n^3)$ 的 $\text{Floyd}$，建图时需要判断两点的距离是否不大于 $k$。

贴一下代码：

```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<climits>
#include<queue>
#include<vector>
using namespace std;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' or ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' and ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
const int INF=1e9+10;
inline int Max(int x,int y){return x>y?x:y;}
inline int Min(int x,int y){return x<y?x:y;}
inline void Swap(int&x,int&y){x^=y;y^=x;x^=y;}
inline int Abs(int x){return x>0?x:-x;}
const int MAXN(520000);
const int MAXM(610);
int V,M,N,m;
int a[MAXN];
int G[MAXM][MAXM];
inline void Floyd()
{
	for(register int k=1;k<=V;k++)
		for(register int i=1;i<=V;i++)
			for(register int j=1;j<=V;j++)
				G[i][j]=Min(G[i][j],G[i][k]+G[k][j]);
	return;
}
struct E{int to,nxt,flow;};
E edge[MAXN];
int head[MAXN],tot(1);
int s,t;
inline void add(int u,int v,int f)
{
	edge[++tot].nxt=head[u];
	head[u]=tot;
	edge[tot].to=v;
	edge[tot].flow=f;
	return;
}
inline void add_edge(int u,int v,int f)
{
	add(u,v,f);
	add(v,u,0);
	return;
}
int dep[MAXN];
queue<int>q;
inline bool bfs()
{
	memset(dep,0,sizeof(dep));
	dep[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(register int i=head[u];i;i=edge[i].nxt)
		{
			E e=edge[i];
			if(!dep[e.to]&&e.flow)
			{
				dep[e.to]=dep[u]+1;
				q.push(e.to);
			}
		}
	}
	return dep[t];
} 
inline int dfs(int u,int in)
{
	if(u==t) return in;
	int out(0);
	for(register int i=head[u];i&&in;i=edge[i].nxt)
	{
		E e=edge[i];
		if(e.flow&&dep[e.to]==dep[u]+1)
		{
			int now=dfs(e.to,Min(e.flow,in));
			edge[i].flow-=now;
			edge[i^1].flow+=now;
			in-=now;
			out+=now;
		}
	}
	if(!out) dep[u]=0;
	return out;
}
inline void Clear()
{
	tot=1;
	memset(head,0,sizeof(head));
	memset(edge,0,sizeof(edge));
	return;
}
inline bool check(int lim)
{
	Clear();
	int ans(0);
	for(register int i=1;i<=N;i++)
		for(register int j=1;j<=V;j++)
			if(G[a[i]][j]<=lim) add_edge(i,j+N,1);
	for(register int i=1;i<=N;i++) add_edge(s,i,1);
	for(register int i=1;i<=V;i++) add_edge(i+N,t,1);
	while(bfs()) ans+=dfs(s,INF);
	return ans>=m;	
}
int main()
{
	V=read(),M=read(),N=read(),m=read();
	s=0,t=V+N+1;
	for(register int i=1;i<=N;i++) a[i]=read();
	for(register int i=1;i<=V;i++)
		for(register int j=1;j<=V;j++) if(i!=j)
			G[i][j]=INF;
	for(register int i=1;i<=M;i++)
	{
		int u=read(),v=read(),w=read();
		G[u][v]=G[v][u]=Min(G[u][v],w);
	}
	Floyd();
	int l=0,r=10000000,res(-1);
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1,res=mid;
		else l=mid+1;
	}
	printf("%d\n",res); 
	return 0;
}
```

$$\texttt{The End.by UF}$$

---

