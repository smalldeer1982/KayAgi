# [EC Final 2020] City Brain

## 题目描述

Pang 教授在首都 Grancel 的城市大脑项目工作。Grancel 的道路网络可以用一个无向图表示。最初，每条道路的限速为 $1$ 米每秒。Pang 教授可以花费 $1$ 美元将某条道路的限速提高 $1$ 米每秒。Pang 教授有 $k$ 美元。他可以在每条道路上花费任意非负整数金额。如果某条道路的限速为 $a$ 米每秒，则任何人通过这条道路需要 $1/a$ 秒的时间。

在 Pang 教授花费完他的资金后，Du 教授开始从城市 $s_1$ 前往城市 $t_1$，而 Wo 教授开始从城市 $s_2$ 前往城市 $t_2$。帮助 Pang 教授明智地花费他的资金，以最小化 Du 教授和 Wo 教授的最短旅行时间之和。保证 $s_1$ 和 $t_1$ 之间至少有一条路径连通，$s_2$ 和 $t_2$ 之间也至少有一条路径连通。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
6 5 1
1 2
3 2
2 4
4 5
4 6
1 5 3 6```

### 输出

```
5.000000000000```

## 样例 #2

### 输入

```
1 0 100
1 1 1 1```

### 输出

```
0.000000000000```

## 样例 #3

### 输入

```
4 2 3
1 2
3 4
1 2 3 4```

### 输出

```
0.833333333333```

# 题解

## 作者：Ahws_rwhy (赞：5)

~~哇，写了 $1$ 个小时，一百多行代码，总算过了。~~

思路：

对于两条路径，一定是中间有重合的一段，而不是有两段，否则，对于两个人中间分开的那一段路径一定可以选择一条更短的路走，从而将两段重合路径合并成了一段。

可以枚举重合的路径的两个端点，那么重合的路径长度以及不重合的路径的长度就可以确定了，假设重复端点为 $N$，那么预处理一下重叠部分为 $N$ 的时候其他路径的最短和 $s_1$，这个 $\mathcal O(n ^ 2)$ 可以处理出来，我们发现我们不好确认分给重叠部分的次数多少，于是，三分给重叠部分的操作次数；之后，处理一下，问题又变成了给长度为 $m$ 的路径分配 $x$ 次操作的最小代价，这个还是比较容易考虑的，首先就是均分次数，多余的，也是均分。

接着处理一些细节即可。


```
double solve(int b, int a) {
	if (a > inff || b > inff) return inff;
	if (a == 0 && b == 0) return 0;
	int k = tempk;
	int v = (k + a + b) / (genhao2 * a + b) ;
	int u = genhao2 * v;
	if (u > 1) u--;
	if (v > 1) v--;
	if (u < 1) u = 1;
	if (v < 1) v = 1;
//	cout << u << " " << v << endl;
	k -= a * (u - 1) + b * (v - 1);
	ans = a * (2.0 / u) + b * (1.0 / v);
//	cout << ans << endl;
	while (k != 0) {
		if (1 * u * (u + 1) < 2 * v * (v + 1)) {
			int time = min(k, a);
			ans -= time * (2.0 / (u * (u + 1)));
			k -= time;
			u++;
		} else {
			int time = min(k, b);
			ans -= time * (1.0 / (v * (v + 1)));
			k -= time;
			v++;
		}
	}
	return ans;
}
void add(int u, int v) {
	to[++sum] = v ;
	next_side[sum] = first_side[u] ;
	first_side[u] = sum;
}
void bfs(int step, int dis[]) {
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++) dis[i] = inff;
	queue <int> Q;
	vis[step] = 1;
	Q.push(step);
	dis[step] = 0;
	while (!Q.empty()) {
		int front_ = Q.front();
		Q.pop();
		for (int i = first_side[front_]; i != 0; i = next_side[i]) {
			int to_ = to[i];
			if (vis[to_]) continue;
			Q.push(to_);
			vis[to_] = 1;
			dis[to_] = dis[front_] + 1;
		}
	}
}
```

---

## 作者：HPXXZYY (赞：3)

$\color{blue}{\texttt{[Problem Discription]}}$

有一个由 $n$ 个点和 $m$ 条边组成的无向图，每条边的长度都是 $1$。

初始时，每条边限速为 $1$。你有 $k$ 次操作，每次操作可以使**某一条边**的限速加 $1$。$k$ 次操作后，如果一条边的**最终**限速为 $a$，那么你需要 $\dfrac{1}{a}$ 的时间通过这条边。

求 $k$ 次操作后从 $s_{1}$ 到 $t_{1}$ 和从 $s_{2}$ 到 $t_{2}$ 的**总时间**最小。求出这个最小总时间。

$1 \leq n,m \leq 5000,1 \leq k \leq 1 \times 10^{9}$。


$\color{blue}{\texttt{[Analysis]}}$

首先，我们要发现这样一个性质：从 $s_{1}$ 到 $t_{1}$ 的路径（记为 $s_{1} \to t_{1}$）和从 $s_{2}$ 到 $t_{2}$ 的路径（记为 $s_{2} \to t_{2}$）如果有公共部分，则**公共部分一定连续**。

> 证明使用反证法：如果公共部分不连续，则从第一段公共部分的最后一个点到第二段公共部分的第一个点在两条路径中选择了不同的方案。
> 
> - 如果两个方案的耗时不相同，我们可以让耗时较多的那一次也走耗时较少的路径，总时间一定会更小，矛盾。
> - 如果两个方案的耗时相同，为什么非要走不同的路径呢？况且我们可以把对两条路径的操作合并起来对同一段路径操作，这样总时间一定会更小。

可以枚举公共部分的起点和终点，分别记为 $u,v$。我们发现公共部分的每条边的地位是相等的，非公共部分的每条边的地位也是相等的。即：具体要走怎样的路径对结果没有影响，有影响的是公共部分的总边数 $\text{share}$ 和非公共部分的总边数 $\text{individual}$。

假设对公共部分进行 $\text{mid}$ 次操作，可以证明这 $\text{mid}$ 次操作应该尽量平均分在 $\text{share}$ 条边上，那么单次行程在公共部分的耗时应该是：

$$\sum\limits_{i=1}^{\text{mid} \bmod \text{share}} \dfrac{1}{ \left \lfloor \frac{\text{mid}}{\text{share}}  \right \rfloor +2}+\sum\limits_{i=1}^{\text{share}-(\text{mid} \bmod \text{share})} \dfrac{1}{\lfloor \frac{\text{mid}}{\text{share}} \rfloor +1}$$

非公共部分同理。显然的是在公共部分相同的情况下，非公共部分的总边数越少答案肯定越小。维护一个数组 $\text{path}_{i}$，表示当公共部分长度为 $i$ 时非公共部分总边数的最小值。这样就可以 $O(1)$ 求出总时间。

$\text{mid}$ 可以用三分求出。

时间复杂度 $O \left (n^{2}+n \log k \right )$。

$\color{blue}{\text{Code}}$

```cpp
int n,m,k;

int dis[N][N];
queue<int> q;
inline void bfs(int s){
	for(int i=1;i<=n;i++)
		dis[s][i]=(i==s?0:inf);
	q.push(s);
	
	while (!q.empty()){
		int u=q.front();q.pop();
		
		for(int i=h[u];i;i=e[i].nxt){
			int v=e[i].to;
			if (dis[s][v]==inf){
				dis[s][v]=dis[s][u]+1;
				q.push(v);
			}
		}
	}
}//边权相同，可以用 bfs 求最短路

double calc(int tot,int val){
	if (tot==0) return 0;
	if (val==0) return 1.0*tot;
	
	int ave=val/tot,lef=val%tot;
	return (1.0*(tot-lef)/(ave+1)+1.0*lef/(ave+2));
}//对 tot 条路可以操作 val 次最小时间 

double check(int sha,int idv,int mid){
	return 2.0*calc(sha,mid)+calc(idv,k-mid);
}//别忘了乘以 2

double solve(int sha,int idv){
	int l=0,r=k;
	double ret=1e30;
	
	while (l<=r){
		int lmid=l+(r-l)/3,rmid=r-(r-l)/3;
		
		if (check(sha,idv,lmid)<check(sha,idv,rmid)){
			r=rmid-1;
			ckmin(ret,check(sha,idv,lmid));
		}
		else{
			l=lmid+1;
			ckmin(ret,check(sha,idv,rmid));
		}
	}
	
	return ret;
}

int path[N],s1,t1,s2,t2;
double ans;

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	scanf("%d%d%d%d",&s1,&t1,&s2,&t2);
	
	for(int i=1;i<=n;i++) bfs(i);
	
	for(int i=0;i<=n;i++) path[i]=inf;
	for(int u=1;u<=n;u++)
		for(int v=1;v<=n;v++)
			if (dis[u][v]!=inf){
				if (dis[s1][u]==inf||dis[s2][u]==inf) continue;
				if (dis[v][t1]==inf||dis[v][t2]==inf) continue;
				ckmin(path[dis[u][v]],dis[s1][u]+dis[s2][u]+dis[v][t1]+dis[v][t2]);
				
				if (dis[t2][u]==inf||dis[v][s2]==inf) continue;
				ckmin(path[dis[u][v]],dis[s1][u]+dis[t2][u]+dis[v][t1]+dis[v][s2]);
			}
	
	ans=check(0,dis[s1][t1]+dis[s2][t2],0);
	for(int i=0;i<=n;i++)
		if (path[i]!=inf)
			ckmin(ans,solve(i,path[i]));
	
	printf("%.20lf",ans);
	
	return 0;
}

h,e 是链式前向星使用的数组
ckmin(a,b) 表示让 a 取得 a,b 中的较小值
```

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/P10819)

**题目大意**

> 给定 $n$ 个点 $m$ 条边的图，初始每条边边权为 $1$，某次操作可以把一条边的边权从 $\dfrac 1p$ 变成 $\dfrac 1{p+1}$，进行 $k$ 次操作，最小化 $\mathrm{dist}(s_1,t_1)+\mathrm{dist}(s_2,t_2)$。
>
> 数据范围：$n,m\le 5000,k\le 10^9$。

**思路分析**

很显然我们只关心路径交和剩余边的数量。

首先两条路径的路径交肯定是连续的一段，否则把较长的一段调整成较短的即可。

预处理出全源最短路，我们只要枚举路径交的起点终点，就可以求出 $f_i$ 表示路径交长度为 $i$ 时剩余边最少有几条。

对每个 $(i,f_i)$ 分别求解，把每个操作看成带来 $\dfrac 2{p(p+1)}$ 或 $\dfrac{1}{p(p+1)}$ 的收益。

查询时二分斜率，求出最大的 $q$ 使得操作 $\le q$ 的所有操作需要次数 $\le k$，然后分讨求答案即可。

时间复杂度 $\mathcal O(nm+n\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ll long long
using namespace std;
const int MAXN=5005;
const ll inf=2e18;
int n,m; ll k;
vector <int> G[MAXN];
int d[MAXN][MAXN],f[MAXN];
ll q1(ll x) {
	ll z=sqrt(x)+10;
	while(z*(z-1)>x) --z;
	return z;
}
ll q2(ll x) {
	ll z=sqrt(2*x)+10;
	while(z*(z-1)/2>x) --z;
	return z;
}
ld qry(ll x,ll z) {
	if(!x&&!z) return 0;
	ll l=1,r=inf,p=0;
	while(l<=r) {
		ll mid=(l+r)>>1;
		if((q2(mid)-1)*z+(q1(mid)-1)*x<=k) l=mid+1,p=mid;
		else r=mid-1;
	}
	ll s1=q1(p),s2=q2(p),q=k-(s2-1)*z-(s1-1)*x;
	ll c1=(s1+1)*s1,c2=(s2+1)*s2/2;
	if(c1<c2) {
		return (ld)q/(s1+1)+(ld)(x-q)/s1+(ld)z/s2*2;
	} else if(c2<c1||q<=z) {
		return (ld)x/s1+((ld)(z-q)/s2+(ld)q/(s2+1))*2;
	} else {
		q-=z;
		return (ld)q/(s1+1)+(ld)(x-q)/s1+(ld)z/(s2+1)*2;
	}
}
signed main() {
	scanf("%d%d%lld",&n,&m,&k);
	for(int i=1,u,v;i<=m;++i) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	memset(d,0x0f,sizeof(d));
	int s1,t1,s2,t2;
	scanf("%d%d%d%d",&s1,&t1,&s2,&t2);
	for(int s=1;s<=n;++s) {
		queue <int> q;
		q.push(s),d[s][s]=0;
		while(q.size()) {
			int u=q.front(); q.pop();
			for(int v:G[u]) if(d[s][v]>d[s][u]+1) d[s][v]=d[s][u]+1,q.push(v);
		}
	}
	memset(f,0x3f,sizeof(f));
	f[0]=d[s1][t1]+d[s2][t2];
	for(int u=1;u<=n;++u) for(int v=1;v<=n;++v) if(d[u][v]<n) {
		f[d[u][v]]=min(f[d[u][v]],d[s1][u]+d[v][t1]+d[s2][u]+d[v][t2]);
		f[d[u][v]]=min(f[d[u][v]],d[s1][u]+d[v][t1]+d[s2][v]+d[u][t2]);
	}
	ld ans=inf;
	for(int i=0;i<n;++i) if(f[i]<=4*n) {
		ans=min(ans,qry(f[i],i));
	}
	printf("%.16Lf\n",ans);
	return 0;
}
```

---

## 作者：Dazlin7 (赞：0)

## 思路

要解决这道路径问题，核心是根据贪心原则将操作次数均分，并利用最短路径预处理和三分法来优化计算。

我们先预处理最短路径，由于图是稀疏图且边权相等，可以通过枚举起点 BFS 预处理任意两点之间的最短路径，复杂度为 $O(n^2)$，得到 $dist[u][v]$ 表示从节点 $u$ 到节点 $v$ 的最短路径长度。假设路径长度为 $l$，总操作次数为 $t$，根据贪心原则，修改次数 $x$ 应该尽可能平均分配。对于重复和不重复的路径部分，假设不重复部分分配 $x$ 次修改，重复部分分配 $k - x$ 次修改。利用三分法在 $O(\log k)$ 时间内求解最优分配方案，确保总用时最短。枚举重复路径的起点和终点，得到重复路径和不重复路径的长度。为了避免超时，筛掉相同重复路径长度中不重复路径长度较大的方案，然后对剩余的路径长度使用三分法进行计算，将复杂度降为 $O(n \log k)$。

最终的时间复杂度为 $O(n^2 + n \log k)$，既考虑了路径预处理的效率，也优化了操作次数的分配过程。

## 代码



```cpp

#include <bits/stdc++.h>
using namespace std;
const int A = 5005, B = 0x3f3f3f3f;
int hd[A], ve[A << 1], ne[A << 1], ec;
int n, m, k, s1, t1, s2, t2, d[A][A], mn[A];
queue<int> q;

inline void ae(int x, int y) {
    ve[++ec] = y;
    ne[ec] = hd[x];
    hd[x] = ec;
}

inline void bf(int s) {
    memset(d[s] + 1, 0x3f, sizeof(int) * n);
    q.push(s), d[s][s] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = hd[x]; i; i = ne[i]) {
            if (d[s][ve[i]] != B) continue;
            d[s][ve[i]] = d[s][x] + 1, q.push(ve[i]);
        }
    }
}

inline double cg(int l, int x) {
    return (l) ? (double((x) % (l)) / double((x) / (l) + 2) + double((l) - (x) % (l)) / double((x) / (l) + 1)) : 0;
}

inline double ch(int l1, int l2, int x) {
    return cg(l1, x) + 2 * cg(l2, k - x);
}

inline double cr(int l1, int l2) {
    if (!l1 && !l2) return 0;
    if (!l2) return cg(l1, k);
    if (!l1) return 2 * cg(l2, k);
    int l = 0, r = k, lm, rm, ans;
    while (l <= r) {
        lm = l + (r - l) / 3, rm = r - (r - l) / 3;
        ch(l1, l2, lm) >= ch(l1, l2, rm) ? (l = lm + 1, ans = rm) : (r = rm - 1);
    }
    return ch(l1, l2, ans);
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, x, y; i <= m; i++) {
        scanf("%d%d", &x, &y);
        ae(x, y), ae(y, x);
    }
    for (int i = 1; i <= n; i++) bf(i);
    scanf("%d%d%d%d", &s1, &t1, &s2, &t2);
    memset(mn + 1, 0x3f, sizeof(int) * n);
    mn[0] = d[s1][t1] + d[s2][t2];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (d[i][j] == B || d[s1][i] == B || d[s2][i] == B || d[j][t1] == B || d[j][t2] == B) continue;
            mn[d[i][j]] = min(mn[d[i][j]], min(d[s1][i] + d[j][t1], d[s1][j] + d[i][t1]) + min(d[s2][i] + d[j][t2], d[s2][j] + d[i][t2]));
        }
    double ans = 1e9;
    for (int i = 0; i < n; i++) {
        if (mn[i] == B) continue;
        ans = min(ans, cr(mn[i], i));
    }
    printf("%.15lf\n", ans);
    return 0;
}
```

---

