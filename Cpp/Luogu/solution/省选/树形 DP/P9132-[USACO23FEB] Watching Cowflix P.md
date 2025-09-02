# [USACO23FEB] Watching Cowflix P

## 题目描述

**注意：本题的时间限制为 3 秒，是默认时间的 1.5 倍。**

Bessie 喜欢在 Cowflix 上观看节目，并且她在不同的地方观看。Farmer John's 农场可以表示为一个有 $N(2 \le N \le 2 \cdot 10^5)$ 个节点的树，对于每个节点，Bessie 要么在该节点观看 Cowflix，要么不观看。保证 Bessie 至少在一个节点上观看 Cowflix。

不幸的是，Cowflix 正在引入一种新的订阅模式以打击密码共享。在他们的新模式中，你可以在农场中选择一个大小为 $d$ 的连通分量，然后你需要支付 $d+k$ moonies 来获得一个可以在该连通分量中使用的账户。正式地，你需要选择一组不相交的连通分量 $c_1,c_2, \cdots ,c_C$，使得每个 Bessie 观看 Cowflix 的节点必须包含在某个 $c_i$ 中。组件集的成本为 $\sum\limits^{C}_{i=1}(|c_i|+k)$，其中 $|c_i|$ 是组件 $c_i$ 中的节点数。Bessie 不观看 Cowflix 的节点不必包含在任何 $c_i$ 中。

Bessie 担心新的订阅模式可能对她来说太贵，因为她访问的地方很多，因此她考虑转向 Mooloo。为了帮助她做出决定，计算她需要支付给 Cowflix 的最低金额以维持她的观看习惯。因为 Cowflix 尚未公布 $k$ 的值，所以计算从 $1$ 到 $N$ 的所有整数值的 $k$。

## 说明/提示

### 示例 1 的解释

对于 $k \le 3$，最优方案是拥有两个账户：$c_1=\{1\},c_2=\{5\}$。对于 $k \ge 3$，最优方案是拥有一个账户：$c_1=\{1,2,3,4,5\}$。

### 评分

- 输入 $3-5$：$N \le 5000$
- 输入 $6-8$：$i$ 与 $i+1$ 连接，对于所有 $i \in [1,N)$。
- 输入 $9-19$：$N \le 10^5$
- 输入 $20-24$：无额外限制。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
10001
1 2
2 3
3 4
4 5```

### 输出

```
4
6
8
9
10```

## 样例 #2

### 输入

```
7
0001010
7 4
5 6
7 2
5 1
6 3
2 5```

### 输出

```
4
6
8
9
10
11
12```

# 题解

## 作者：Elma_ (赞：12)

其实我最先注意到的是如果两个关键点距离 $\leq k$，那么他们可以直接被合并。这样合并完之后最多只有 $\mathcal{O}(\frac{n}{k})$ 个关键点。然后发现好像还没最优呢，还可能在关键点的虚树上的某个非关键点处发生合并，那我们就求出虚树，然后树形 DP 一下，就做完了。因为只有 $\mathcal{O}(\frac{n}{k})$ 个关键点，所以虚树上最多也只有 $\mathcal{O}(\frac{n}{k})$ 个点，根据调和级数总时间复杂度 $\mathcal{O}(n \log n)$。

这样说起来是很简单，但写起来还是有不少细节。代码中的实现方法是这样的：我们先求出虚树，然后预处理出每个点及每条边被合并的时间，以及每个点被某个联通块完全包裹在内部的时间。这样我们可以求出每个时刻 DP 前的连通块会新增多少个点，多少条边。用 ```set``` 维护当前剩下的点的 DFS 序以减小 DP 的常数，当一个点被某个连通块完全包裹在内部的时候就可以把它删掉了。具体的细节参见代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5, inf = 2e9;
int n, par[N], val[N], dep[N]; bool key[N], era[N];
set <int> e[N];
void remove(int u) {
	for (auto v : e[u]) {
		par[v] = u, val[v] = 1, dep[v] = dep[u] + 1;
		e[v].erase(e[v].find(u)), remove(v);
	}
	if (!key[u]) {
		bool ok = 1;
		for (auto v : e[u]) ok &= era[v];
		if (ok) era[u] = 1;
	}
}
int dis[N], _dis[N], tim[N], _tim[N], c[N], d[N], f[N][2], ans[N];
vector <int> buk[N];
struct dat {
	int i;
	bool operator < (const dat &p) const {
		return dep[i] != dep[p.i] ? dep[i] > dep[p.i] : i > p.i;
	}
};
set <dat> cur; 
void dfs(int u) {
	dis[u] = _dis[u] = (key[u] ? 0 : inf);
	for (int v : e[u]) {
		dfs(v);
		int L = dis[v] + val[v];
		if (L < dis[u]) _dis[u] = dis[u], dis[u] = L;
		else if (L < _dis[u]) _dis[u] = L;
	}
}
void calc(int u, int L) {
	_tim[u] = dis[u] + L;
	for (int v : e[u]) {
		int _L = (dis[v] + val[v] == dis[u]) ? _dis[u] : dis[u];
		calc(v, min(_L, L) + val[v]);
	}
}
signed main() {  
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
	cin >> n >> s;
	int root = -1;
	for (int i = 1; i <= n; i++) if (s[i - 1] == '1') key[i] = 1, root = i;
	for (int i = 1, x, y; i < n; i++) {
		cin >> x >> y;
		e[x].insert(y), e[y].insert(x);
	}
	remove(root);
	for (int i = 1; i <= n; i++) if (era[i]) e[par[i]].erase(e[par[i]].find(i))
	for (int i = 1; i <= n; i++) {
		if (!era[i] && !key[i] && e[i].size() == 1) { int u = i, v = -1; 
			for (auto z : e[u]) v = z;
			assert(v > 0);
			par[v] = par[u], val[v] += val[u], e[par[u]].erase(e[par[u]].find(u)), e[par[u]].insert(v);
			era[u] = 1;
		}
	}
	dfs(root), calc(root, 0);
	for (int i = 1; i <= n; i++) if (!era[i]) {
		cur.insert((dat){ i });
		tim[i] = key[i] ? 0 : _tim[i];
		int t = _tim[i];
		for (auto v : e[i]) tim[i] = min(tim[i], _tim[v]), t = max(t, _tim[v]);
		buk[t].push_back(i);
		c[tim[i]]++;
		if (dep[i] != 0) c[_tim[i]] += val[i] - 1, d[_tim[i]] += val[i];
	} 
	int C = c[0], D = 0;
	for (int k = 1; k <= n; k++) {
		for (int i : buk[k]) {
			auto it = cur.find((dat){ i });
			assert(it != cur.end());
			cur.erase(it);
		}
		C += c[k], D += d[k];
		ans[k] = k * (C - D) + C;
		for (auto z : cur) {
			int v = z.i;
			if (tim[v] <= k) f[v][0] = inf;
			else f[v][1] += k + 1;
			if (_tim[v] <= k) ans[k] += f[v][1];
			else {
				int u = par[v];
				f[u][0] += min(f[v][0], f[v][1]);
				f[u][1] += min(f[v][0], min(f[v][1], f[v][1] - k + (val[v] - 1)));
			}
			f[v][0] = f[v][1] = 0;
		}
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
    return 0; 
}
```

---

## 作者：PosVII (赞：8)

**前言**

------------

完全没有思维难度的方法，但是无论从理论上还是实际上都能过。

场上秒了，但是被卡常了。。。

根号分治 $O(n^{\frac{3}{2}})$ 做法。

**思路**

------------

拿到这种算代价的题第一步就是分析上界，显然，答案上界为 $n+k$。

上界与 $n$ 同阶，考虑当一个连通块代价为 $k$ 时，联通块的数量最多为 $\frac{n+k}{k+1}$ 个。

考虑根号分治，设 $B$，用 $O(nB)$ 的树形 dp 暴力枚举 $k$ 为 $[1,B]$ 时的代价，然后用 $O(\frac{n^2}{B})$ 的树形 dp 预处理连通块数量为 $[1,\frac{n}{B}]$ 时的代价。

平衡复杂度，算出 $B = \sqrt{n}$。

当然，由于会被卡空间，所以还是只能把块长开到 $120$ 左右。

upd：

感谢 @mazihang2022 的帮助，我纠正了该背包的复杂度不是 $O(n^{\frac{2}{3}})$ 而是 $O(n^{\frac{1}{2}})$。

同时，他也提供了一种卡树形背包空间的方法，详见 [某期洛谷日报](https://www.luogu.com.cn/blog/over-knee-socks/post-bag)。可以用重链剖分优化空间至 $O(n \log n)$。

于是，该根号分治的最终复杂度是 $O(n \sqrt{n})$。

**code**

------------

略微卡常，有两点优化。

1. 用 dfs 序预处理 dp 顺序。
1. 不用 vector 从父亲向儿子递推，而是记录父亲从儿子往父亲递推。

膜拜 @DeepSkyCore 帮我卡常！！！！111

```
#include<bits/stdc++.h>
using namespace std;
template<typename G> inline void read(G &x) {x=0;G f=1;char ch=getchar();while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();if(ch=='-') f=-1,ch=getchar();while(ch>='0'&&ch<='9') {x=x*10+(ch^48);ch=getchar();}x*=f;}
const int MAXN=2e5+5,MAXM=126;
int fa[MAXN];
vector<int> E[MAXN],G[MAXN];
int f[MAXN][MAXM][2],g[MAXN][2],siz[MAXN],dfn[MAXN],cnt;
bitset<MAXN> vis;
void bdfs(int u,int las) {
	dfn[++cnt]=u;
	for(auto v:E[u]) {
		if(v!=las) {
			fa[v]=u;
			G[u].emplace_back(v);
			bdfs(v,u);
		}
	}
}
void bfs(int u) {
	siz[u]=1;
	f[u][1][1]=1;
	if(!vis[u]) f[u][0][0]=0;
	for(auto v:G[u]) {
		bfs(v);
		siz[u]+=siz[v];
		for(int i=min(100,siz[u]);i>=0;--i) {
			int f0=1e9,f1=1e9;
			for(int j=0;j<=siz[v]&&j<=i;++j) {
				f0=min(f0,f[u][i-j][0]+min(f[v][j][0],f[v][j][1]));
				f1=min(f1,f[u][i-j][1]+min(f[v][j][0],min(f[v][j+1][1],f[v][j][1])));
			}
			f[u][i][0]=f0,f[u][i][1]=f1;
		}
	}
}
int n,u,v;
signed main() {
	memset(f,63,sizeof(f));
	read(n);
	for(int i=1;i<=n;++i) {
		char ch=getchar();
		while(ch!='0'&&ch!='1') ch=getchar();
		vis[i]=ch-'0';
	}
	for(int i=2;i<=n;++i) {
		read(u),read(v);
		E[u].emplace_back(v);
		E[v].emplace_back(u);
	}
	bdfs(1,0);
	for(int j=n;j>=1;--j){
		g[j][1]=2;
	}
	g[1][0]=(vis[1]?1e9:0);
	for(int i=1;i<=1.6e3&&i<=n;++i) {
		for(int j=n;j>=2;--j) {
			u=dfn[j];
			if(vis[u]) g[u][0]=1e9;
			g[fa[u]][0]+=min(g[u][0],g[u][1]);
			g[fa[u]][1]+=min(g[u][0],g[u][1]-i);
			g[u][0]=0,g[u][1]=i+2;
		}
		printf("%d\n",min(g[1][0],g[1][1]));
		g[1][0]=(vis[1]?1e9:0),g[1][1]=i+2;
	}
	bfs(1);
	for(int i=1.6e3+1;i<=n;++i) {
		int ans=1e9;
		for(int j=0;j<=125&&j<=n/i+1;++j) ans=min(ans,min(f[1][j][0],f[1][j][1])+j*i);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：UltiMadow (赞：8)

考虑先钦定一个 $k$ 计算答案。

此时有一个显然的 dp：记 $f_{u,0/1}$ 为以 $u$ 为根的子树，$u$ 不在/在某一个连通块中的最优解，转移显然。

如果对于每个 $k$ 暴力进行一次 dp，复杂度是 $\mathcal O(n^2)$ 的，需要优化。

记 $g_i$ 表示 $k=i$ 时取到最优解的最小连通块数，不难发现 $g_i$ 单调不增。

若对一个区间 $[l,r]$ 有 $g_l=g_r$，那么 $\forall i\in[l,r]$ 有 $g_i=g_l$，此时我们只需要对 $k=l$ 进行一次 dp 之后便可以 $\mathcal O(r-l)$ 求出所有 $[l,r]$ 中的答案。

自然想到分治，记状态 $(l,r,ql,qr)$ 表示当前处理 $[l,r]$ 区间，之前已经求出 $g_{l-1}=ql,g_{r+1}=qr$。

取分治中心 $mid=\lfloor\frac{l+r}2\rfloor$ 并对 $k=mid$ 进行一次 dp 求出 $g_{mid}$，若 $g_{mid}=ql$ 则不需要继续处理左侧区间；右侧区间同理。

考虑分析这个算法的时间复杂度，对于 $k$，不难发现所有距离 $\le k$ 的关键点对一定在同一连通块中，于是考虑把这些点缩起来，此时所有关键点对之间的距离均 $> k$。

记 $cnt$ 为关键点个数 $dis(u,v)$ 表示关键点 $u$ 与关键点 $v$ 之间的距离，序列 $u_i$ 表示所有关键点按 dfs 序排序之后的结果，$u_{cnt+1}=u_1$。

那么有 $2n\ge \sum_idis(u_i,u_{i+1})\ge k\cdot cnt\Rightarrow cnt\le \frac {2n}{k}$（此时直接在关键点组成的虚树上进行 dp 即可得到一个 $\mathcal O(n\ln n)$ 的解法，但是感觉不太好写），即 $g_k\le \frac {2n}k$

考虑 $k\le\sqrt{2n}$ 时，只需进行 $\mathcal O(\sqrt n)$ 次 dp；$k\ge \sqrt{2n}$ 时，有 $g_k\le \sqrt {2n}$，即最多只有 $\mathcal O(\sqrt n)$ 种不同的连通块个数，而分治相当于不断二分找到这 $\mathcal O(\sqrt n)$ 个断点，总复杂度即为 $\mathcal O(n\sqrt n\log n)$。

（官方题解说这种算法是 $\mathcal O(n\sqrt n)$ 的，不是很理解（

代码需要一定卡常，例如把每次 dp 放在 dfs 序上。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 200010
using namespace std;
const int inf=0x3f3f3f3f3f3f3f3f;
int n,ans[MAXN];
char c[MAXN];
struct Node{int to,nxt;}Edge[MAXN<<1];
int Head[MAXN],cnt_Edge;
void Add_Edge(int u,int v){
	Edge[++cnt_Edge]=(Node){v,Head[u]};
	Head[u]=cnt_Edge;
}
int dfn[MAXN],pre[MAXN],id[MAXN],tot;
void dfs(int u,int fa){
	dfn[u]=++tot;id[tot]=u;pre[tot]=dfn[fa];
	for(int i=Head[u];i;i=Edge[i].nxt){
		int v=Edge[i].to;if(v==fa)continue;
		dfs(v,u);
	}
}
int f[MAXN][2],cnt[MAXN][2];
void dp(int val){
	for(int i=1;i<=n;i++)f[i][0]=(c[id[i]]=='0'?0:inf),f[i][1]=1,cnt[i][0]=cnt[i][1]=0;
	for(int v=n;v>1;v--){
		int u=pre[v];
		if(f[v][0]<f[v][1]+val||(f[v][0]==f[v][1]+val&&cnt[v][0]<cnt[v][1]+1))
			f[u][0]+=f[v][0],cnt[u][0]+=cnt[v][0];
		else f[u][0]+=f[v][1]+val,cnt[u][0]+=cnt[v][1]+1;
		if(f[v][0]<f[v][1]||(f[v][0]==f[v][1]&&cnt[v][0]<cnt[v][1]))
			f[u][1]+=f[v][0],cnt[u][1]+=cnt[v][0];
		else f[u][1]+=f[v][1],cnt[u][1]+=cnt[v][1];
	}
}
void solve(int l,int r,int ql,int qr){
	if(l>r)return;
	int mid=(l+r)>>1;dp(mid);
	int res=0,sum=0;
	if(f[1][0]<f[1][1]+mid||(f[1][0]==f[1][1]+mid&&cnt[1][0]<cnt[1][1]+1))
		res=f[1][0],sum=cnt[1][0];
	else res=f[1][1]+mid,sum=cnt[1][1]+1;
	ans[mid]=res;res-=mid*sum;
	if(ql==sum)
		for(int i=l;i<mid;i++)ans[i]=res+i*sum;
	else solve(l,mid-1,ql,sum);
	if(qr==sum)
		for(int i=mid+1;i<=r;i++)ans[i]=res+i*sum;
	else solve(mid+1,r,sum,qr);
}
signed main(){
	scanf("%lld%s",&n,c+1);
	for(int i=1;i<n;i++){
		int u,v;scanf("%lld%lld",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}dfs(1,0);
	solve(1,n,n,1);
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Skykguj (赞：6)

对于链（链可以跳过不看）：

设 $f[i][0/1]$ 表示当前到了第 $i$ 个人，不看/看电视的最小代价。

- $f[i][1]=\min\{f[i-1][0]+k+1, f[i-1][1]+1\}$
- $f[i][0]=\min\{f[i-1][0],f[i-1][1]\}, s[i] = 0$

初始状态 $f[0][0]=0$，目标状态 $\min\{f[n][1], f[n][0]\}$。

对于树：

设 $f[u][0/1]$ 表示以 $u$ 为根的子树，根节点是否在一个联通块里的最小代价。

- $f[u][1]=f[u][1]+\sum_{j\in Son_u}{\min\{f[j][0],f[j][1]}\}$
- $f[u][0]=f[u][0]+\sum_{j\in Son_u}{\min\{f[j][0],f[j][1]+k}\}$

初始状态每个节点的 $f[u][1]=1$，当 $s[u]=0$ 时，$f[u][0]=0$，否则 $f[u][0]=\inf$。

首先注意到答案是单调上升的，相邻两个答案之间的差值是不上升的。

当 $k < \sqrt{n}$ 时，差值递减的很快，当 $k \ge \sqrt{n}$ 时，有很长一段答案有相同的差值，并且差值之间相差 $1$，考虑根号分治。

- 对于 $k \le \sqrt{n}$，直接暴力求答案。
- 对于 $k > \sqrt{n}$，二分差值变化的点。记 $d_t$ 表示差值为 $t$ 的最后一个答案的位置，那么与前一个答案相差为 $t$ 的答案的个数为 $d_t - d_{t+1}$ 个。

时间复杂度 $O(n \sqrt{n} + d \times n \log n)$，$d$ 为 $k=\sqrt{n}$ 时 $ans_k-ans_{k-1}$ 的值，需要加 dfs 序优化。

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) f -= (ch == '-') * 2;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x * f;
}

const int N = 200010, M = N << 1;

int n;
char s[N];

namespace Chain {
	int f[N][2], d[N];

	int dp(int k) {
		memset(f, 0x3f, sizeof f);
		f[0][0] = 0;
		for (int i = 1; i <= n; i ++ ) {
			if (s[i] == '0') f[i][0] = min(f[i - 1][0], f[i - 1][1]);
			f[i][1] = min(f[i - 1][0] + k + 1, f[i - 1][1] + 1);
		}
		return min(f[n][0], f[n][1]);
	}

	void solve() {
		int b = sqrt(n), lst = 0;
		for (int k = 1; k <= b; k ++ ) {
			lst = dp(k);
			printf("%d\n", lst);
		}
		int maxd = dp(b + 1) - dp(b);
		d[maxd + 1] = b;
		for (int i = maxd; i; i -- ) {
			int l = b + 1, r = n, ans = b + 1;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (dp(mid) - dp(mid - 1) >= i) l = mid + 1, ans = mid;
				else r = mid - 1;
			}
			d[i] = ans;
		}
		for (int i = maxd; i; i -- ) {
			int cnt = d[i] - d[i + 1];
			while (cnt -- ) lst = lst + i, printf("%d\n", lst);
		}
	}
}

namespace STD {
	const int INF = 0x3f3f3f3f;
	const int N = 200010;

	int h[N], e[N << 1], ne[N << 1], idx;
	int f[N][2], id[N], d[N], fa[N], ts;

	void add(int a, int b) {
		e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx;
	}

	void dfsx(int u, int f) {
		id[ ++ ts] = u;
		for (int i = h[u]; i; i = ne[i]) {
			int j = e[i];
			if (j == f) continue;
			fa[j] = u;
			dfsx(j, u);
		}
	}

	int dp(int k) {
		for (int i = 1; i <= n; i ++ ) {
			f[i][0] = INF, f[i][1] = 1;
			if (s[i] == '0') f[i][0] = 0;
		}
		for (int i = n; i > 1; i -- ) {
			int j = id[i], u = fa[j];
			if (s[u] == '0') f[u][0] += min(f[j][0], f[j][1] + k);
			f[u][1] += min(f[j][0], f[j][1]);
		}
		return min(f[1][1] + k, f[1][0]);
	}

	void solve() {
		for (int i = 1; i < n; i ++ ) {
			int a = read(), b = read();
			add(a, b), add(b, a);
		}
		dfsx(1, -1);
		int b = sqrt(n), lst = 0;
		for (int k = 1; k <= b; k ++ ) {
			lst = dp(k);
			printf("%d\n", lst);
		}
		int maxd = dp(b + 1) - dp(b);
		d[maxd + 1] = b;
		for (int i = maxd; i; i -- ) {
			int l = b + 1, r = n, ans = b + 1;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (dp(mid) - dp(mid - 1) >= i) l = mid + 1, ans = mid;
				else r = mid - 1;
			}
			d[i] = ans;
		}
		for (int i = maxd; i; i -- ) {
			int cnt = d[i] - d[i + 1];
			while (cnt -- ) lst = lst + i, printf("%d\n", lst);
		}
	}
}

int main() {
	n = read();
	scanf("%s", s + 1);
	STD::solve();
	return 0;
}
```


---

## 作者：Yansuan_HCl (赞：4)

有一种显然的合法方案是每个点建一个连通块，另一种是所有点在一个连通块，其他方案介于这两种方案之间。

考虑一个大力做法：按 $k$ 从小到大扫描，建出询问点之间的虚树，边权为两点间的点数，跑树 DP 以决策是否在当点合并连通块或新建连通块。

这样 DP 的结果就是，若决策出两点不属同一连通块，则两点之间距离 $\ge k$，否则合并起来一定不劣。等价地，有任意两决策出的连通块间距离 $\ge k$。

因此，把属同一个连通块的点缩起来，这样对于每个 $k$ 只会有 $O(n/k)$ 个点在虚树上。复杂度 $O(n \log n)$。

[最优解](https://www.luogu.com.cn/record/104349713)。

```cpp
const int N = 200005, INF = 0x3f3f3f3f;
// 联通之后直接缩点
// 未被联通的边都 >=k
// 所以块数 <= n/k
// O(nlogn)

int n; char key[N];
list<pair<int, int>> g[N];
int root, siz[N], k;

void init() {
	BS<int> tr[N];
	rd(n); scanf("%s", key + 1); U (i, 1, n) key[i] -= '0';
	U (i, 2, n) {
		int u, v; rd(u, v);
		tr[u] += v; tr[v] += u;
	}
	int beg[N], st[20][N * 2], ptr, mp[N * 2], Lg[N * 2] {-1}, dep[N] {};
	function<void(int, int)> dfs = [&](int u, int f) {
		beg[u] = ++ptr; mp[ptr] = u; st[0][ptr] = beg[u]; dep[u] = dep[f] + 1;
		for (int v : tr[u]) if (v != f) {
			dfs(v, u);
			st[0][++ptr] = beg[u];
		}
	};
	dfs(1, 0);
	U (i, 1, n * 2 - 1) Lg[i] = Lg[i >> 1] + 1;
	for (int k = 1; (1 << k) <= 2 * n - 1; ++k)
		U (i, 1, (n * 2 - 1) - (1 << k) + 1)
			st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
	auto lca = [&](int u, int v) {
		u = beg[u]; v = beg[v]; if (u > v) swap(u, v);
		int g = Lg[v - u + 1];
		return mp[min(st[g][u], st[g][v - (1 << g) + 1])];
	};
	
	vector<int> pt(1, 1);
	U (i, 1, n) if (key[i]) pt.push_back(i);
	sort(pt.begin(), pt.end(), [&](int u, int v) {
		return beg[u] < beg[v]; });
	
	U (i, 0, pt.size() - 2)
		pt.push_back(lca(pt[i], pt[i + 1]));
	sort(pt.begin(), pt.end(), [&](int u, int v) {
		return beg[u] < beg[v]; });
	pt.erase(unique(pt.begin(), pt.end()), pt.end());
	
	U (i, 0, pt.size() - 2) {
		int l = lca(pt[i], pt[i + 1]);
		g[l].push_back({pt[i + 1], dep[pt[i + 1]] - dep[l] - 1});
	}
	for (int u : pt) siz[u] = 1;
	
	root = (g[1].size() > 1 || key[1]) ? 1 : g[1].begin()->first;
}

int f[N][2]; // f(0/1) 当前点是否有连通块，要考虑 lca 的情况
void dp(int u) {
	for (auto [v, w] : g[u])
		dp(v);
	
	f[u][1] = siz[u] + k;
	for (auto [v, w] : g[u])
		f[u][1] += min({f[v][0], f[v][1], f[v][1] + w - k});
	if (key[u]) { // 必然要建一个连通块
		f[u][0] = INF;
	} else {
		f[u][0] = 0;
		for (auto [v, w] : g[u])
			f[u][0] += min({f[v][0], f[v][1]});
	}
}
void cons(int u, int t) { // 选择 f(u)
	if (t) {
		list<pair<int, int>> tmp;
		for (auto it = g[u].begin(); it != g[u].end(); ) {
			auto [v, w] = *it;
			if (f[v][1] + w - k <= min(f[v][0], f[v][1])) {
				cons(v, 1);
				siz[u] += siz[v] + w; siz[v] = 0;
				key[u] |= key[v];
				tmp.splice(tmp.end(), g[v]);
				g[u].erase(it++);
			} else if (f[v][0] < min(f[v][1] + w - k, f[v][1])) {
				cons(v, 0);
				++it;
			} else {
				cons(v, 1);
				++it;
			}
		}
		g[u].splice(g[u].end(), tmp);
	} else {
		for (auto [v, w] : g[u])
			if (f[v][1] < f[v][0])
				cons(v, 1);
			else
				cons(v, 0);
	}
}

int main() {
	init();
	
	for (k = 1; k <= n; ++k) {
		dp(root);
		cons(root, f[root][1] <= f[root][0]);
		printf("%d\n", min(f[root][0], f[root][1]));
	}
}
```

---

## 作者：小木虫 (赞：2)

### Preface
这题没想清楚的话有点难写的。  
### Problem
Bessie 喜欢在 Cowflix 上看节目，并且喜欢在农场里的不同地方看。

Farmer John 的农场可以被描述成一颗 $n$ 个节点的树，并且 Bessie 只可能在树上的一些指定的节点处看节目。每个节点是否要看节目将在初始时给定；保证至少在一个节点处会看节目。

不幸的是，Cowflix 为了避免奶牛们使用公用账号，采取了一个新的会员策略：
* Bessie 将多次付款，每次选择树上任意一个大小为 $d$ 的**连通块**，为其支付 $d+k$ 的代价，才能够在这些位置看节目。

换言之，Bessie 将选取若干**连通块** $c_1,c_2,\dots,c_C$，支付 $\sum_{i=1}^C(|c_i|+k)$ 的代价，才可以在这些连通块的各个节点处看节目；即，**被指定的节点必须被某个连通块包含，不被指定的节点不必被包含**。

Bessie 觉得这个策略的代价太昂贵了，考虑是否要改在 Mooloo 上看节目。为了帮助其决策，你应当告诉之 $k$ 取遍 $1\sim n$ 时看节目的最小总代价。

$1\le n\le2\times10^5$。
### Solution  
首先注意到一个事，在一棵树上若 $k$ 确定，则两个距离小于等于 $k$ 的点可以被直接合并（也包括他们路径上的点），基于此我们可以证明有用的点的数量为 $O(\dfrac{n}{k})$ 的，在 $k\in[1,n]$ 时总量为 $O(n\log n)$。  
我们可以基于那个简化过的树结构在上面 dp，这部分不多做赘述，主要讲解如何维护简化的树结构，我们需要用到并查集维护点。  

对于 $k\in[1,n]$，我们重复如下步骤：  

拿出所有的特殊点，将他们按照 dfn 序排序。  
然后我们考虑一对在这个序列中相邻的特殊点，如果他们之间的距离小于 $k$ 则让他们轮流向上跳，类似求 LCA，边跳边用并查集合并路径上的点直到两个点相同，注意要将路径上的点全部染为特殊点。  
然后我们再两两拿出他们的 LCA，建出虚树并在上面 DP。

容易注意到虽然在这个过程中点的相对位置不会发生改变，但是树的结构会发生改变，前面我们在合并和动态规划中都要用到**两点距离**这个数据，于是我们需要动态维护这个数据，我们可以求 LCA，所以我们实质上是在维护点的深度。  

所幸我们不需要在一个动态的结构上维护信息，由于点的相对位置不改变，我们只需要在把儿子合并到父亲上的时候把儿子对其子树的深度贡献撤销即可，这部分我们可以使用线段树维护。  

最终的复杂度是 $O(n\log^2 n)$ 的，不可优化的地方有两个，一个 $\log$ 是调和级数的，一个是线段树的，他们两个相乘便有两个 $\log$。  

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,k,C,fa[N],u,v,dp[N][2];string s;
vector <int> edge[N];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
int Tree[N<<2]; 
void update(int rt,int left,int right,int L,int R,int x){
	if(left>=L&&right<=R){
		Tree[rt]+=x;
		return;
	}int mid=(left+right)>>1;
	if(L<=mid)update(rt<<1,left,mid,L,R,x);
	if(mid<R)update(rt<<1|1,mid+1,right,L,R,x);
}
int query(int rt,int left,int right,int x){
	if(left==right)return Tree[rt];
	int res=Tree[rt],mid=(left+right)>>1;
	if(x<=mid)res+=query(rt<<1,left,mid,x);
	else res+=query(rt<<1|1,mid+1,right,x);
	return res;
}
int dep[N],dfn[N],End[N],par[N],cnt;
vector <int> o,p,tmp;
namespace distance{
	int st[N][18];
	void dfs(int u,int fa){
		dfn[u]=End[u]=++cnt;
		dep[u]=dep[fa]+1;
		st[u][0]=fa;
		for(int i=1;i<=17;i++)
			st[u][i]=st[st[u][i-1]][i-1];
		for(auto v:edge[u]){
			if(v==fa||v==u)continue;
			dfs(v,u);par[v]=u;
			End[u]=End[v];
		}
		update(1,1,n,dfn[u],End[u],1);
	}
	int lca(int x,int y){
		if(dep[x]<dep[y])swap(x,y);
		for(int i=17;i>=0;i--){
			if(dep[st[x][i]]>=dep[y])x=st[x][i];
		}
		if(x==y)return x;
		for(int i=17;i>=0;i--){
			if(st[x][i]!=st[y][i])
				x=st[x][i],y=st[y][i];
		}
		return st[x][0];
	}
	int calc(int x,int y){
		return query(1,1,n,dfn[x])+query(1,1,n,dfn[y])-2*query(1,1,n,dfn[lca(x,y)]);
	}
}
void merge(int x,int y){
	x=find(x);y=find(y);
	if(x!=y){
		if(s[x]!='1')s[x]='1',C++,tmp.push_back(x);
		update(1,1,n,dfn[y],End[y],-1);
	}
	fa[y]=x;
}
void init(int u,int fa){
	if(s[u]=='1')o.push_back(u);
	p.push_back(u);
	for(auto v:edge[u]){
		if(v==fa||v==u)continue;
		init(v,u);
	}
}
void Merge(int x,int y){
	while(x!=y){
		x=find(x);y=find(y);
		if(x==y)break;
		if(dep[x]<dep[y])swap(x,y);
		assert(par[x]==distance::st[x][0]);
		merge(par[x],x);
	}
}
vector <int> tree[N];
void dfs(int u,int fa){
	if(s[u]=='1')dp[u][0]=1e9,dp[u][1]=k;
	else dp[u][0]=0,dp[u][1]=k+1;
	for(auto v:tree[u]){
		if(v==fa||v==u)continue;
		dfs(v,u);
		dp[u][0]+=min(dp[v][0],dp[v][1]);
		dp[u][1]+=min(dp[v][0],min(dp[v][1],dp[v][1]-k+(distance::calc(u,v)-1)));
		dp[u][0]=min(dp[u][0],(int)1e9);
	}
}
bool cmp(int x,int y){return dfn[x]<dfn[y];}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>s;s=" "+s;
	for(int i=1;i<=n;i++)C+=s[i]-'0';
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dep[0]=-1;
	distance::dfs(1,0);
	for(k=1;k<=n;k++){
		par[1]=0;
		cnt=0;o.clear();p.clear();
		init(1,0);tmp.clear();
		sort(o.begin(),o.end(),cmp);
		for(int i=1;i<o.size();i++){
			if(distance::calc(o[i-1],o[i])<=k){
				int LCA=distance::lca(o[i-1],o[i]);
				Merge(o[i-1],LCA);
				Merge(o[i],LCA);
			}
		}
		for(int i=1;i<o.size();i++){
			tmp.push_back(distance::lca(o[i-1],o[i])); 
		}
		for(auto u:tmp){
			o.push_back(u),p.push_back(u);
		}
		for(auto &u:o)u=find(u);
		sort(o.begin(),o.end(),cmp);
		for(auto i:p)tree[i].clear();
		stack <int> st;
		st.push(1);
		for(int i=0;i<o.size();i++){
			if(i>0&&o[i-1]==o[i])continue;
			if(st.size()==0){
				st.push(o[i]);
			}else{
				assert(st.size());
				while(st.top()!=o[i]&&distance::lca(st.top(),o[i])!=st.top()){
					int now=st.top();
					st.pop();
					assert(st.size());
					tree[now].push_back(st.top());
					tree[st.top()].push_back(now);
				}
				if(!(st.size()&&st.top()==o[i]))st.push(o[i]);
			}
		}
		while(st.size()){
			int now=st.top();
			st.pop();
			if(!st.size())break;
			tree[now].push_back(st.top());
			tree[st.top()].push_back(now);
		}
		for(auto i:p)edge[i]=tree[i];
		dfs(1,0);
		cout<<min(dp[1][0],dp[1][1])+C<<"\n";
	}
	return 0;
}

```

---

## 作者：Purslane (赞：0)

# Solution

显然如果 $k \ge \sqrt n$，我们最多选 $\sqrt n$ 个连通块。因此可以做一个 $O(n \sqrt n)$ 的树形背包，记录 $k$ 个连通块。

$k< \sqrt n$ 时，做一个 $O(n)$ 的简单背包也就行了。

整体复杂度 $O(n \sqrt n)$。

卡常。放弃递归，直接排到 DFS 序上做即可，能过。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,sze[MAXN],ans[MAXN],dfn[MAXN],tot,rev[MAXN],fa[MAXN];
vector<int> G[MAXN],T[MAXN];
string S;
int g[MAXN][2];
vector<int> dp[MAXN][2];
void dfs1(int k) {
	ffor(u,1,n) {
		g[u][0]=g[u][1]=0x3f3f3f3f;
		if(S[u]=='0') g[u][0]=0,g[u][1]=1;
		else g[u][1]=1;
	}
	roff(mzx,n,1) {
		int v=rev[mzx],u=fa[v];
		g[v][0]=min(g[v][0],g[v][1]+k);
		g[u][1]=min(g[u][1]+g[v][0],g[u][1]+g[v][1]),g[u][0]+=g[v][0];
	}
	return ;
}
const int B=120;
int tmp[B+2][2];
void dfs(int u,int f) {
	dfn[u]=++tot,rev[tot]=u,fa[u]=f;
	ffor(i,0,1) dp[u][0].push_back(0x3f3f3f3f),dp[u][1].push_back(0x3f3f3f3f);
	if(S[u]=='0') dp[u][0][0]=0,dp[u][1][1]=1;
	else dp[u][1][1]=1;
	sze[u]=1;
	for(auto v:G[u]) if(v!=f) {
		T[u].push_back(v);
		dfs(v,u);
		memset(tmp,0x3f,sizeof(tmp));
		ffor(i,0,min(B,sze[u])) ffor(j,0,min(B-i,sze[v])) ffor(o1,0,1) ffor(o2,0,o1) if(i+j>=o2) tmp[i+j-o2][o1]=min(tmp[i+j-o2][o1],dp[u][o1][i]+dp[v][o2][j]);
		sze[u]+=sze[v];
		dp[u][0].resize(min(sze[u],B)+1),dp[u][1].resize(min(sze[u],B)+1);
		vector<int> ().swap(dp[v][0]);
		vector<int> ().swap(dp[v][1]);
		ffor(j,0,min(sze[u],B)) dp[u][0][j]=tmp[j][0],dp[u][1][j]=tmp[j][1];
	}
	ffor(i,0,min(sze[u],B)) dp[u][0][i]=min(dp[u][0][i],dp[u][1][i]);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>S,S="&"+S;
	ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	dfs(1,0);
	ffor(i,1,n/B) dfs1(i),ans[i]=g[1][0];
	ffor(i,n/B+1,n) {
		ans[i]=INT_MAX;
		ffor(j,1,dp[1][0].size()-1) ans[i]=min(ans[i],dp[1][0][j]+j*i);	
	}
	ffor(i,1,n) cout<<ans[i]<<'\n';
	
	return 0;
}
```

---

## 作者：541forever (赞：0)

思路同 [CF1039D](https://codeforces.com/problemset/problem/1039/D)。考虑根号分治。设阈值为 $K$，小于 $K$ 的部分直接暴力做，若值大于 $K$，可以发现我们取的电视个数不会超过 $n \over K$。同时随着 $K$ 的变大，选的电视个数会逐渐变少，从大往小枚举电视个数 $i$，二分选 $i$ 个电视所对应的 $k$ 的区间。将 $K$ 取到 $\sqrt{n \log n}$，时间复杂度为 $O(n \sqrt{n \log n})$，但事实上 $K$ 取到 $500$ 在本题的表现较优，但要想通过本题，还需要一些卡常技巧，如将整棵树拍成一个 dfs 序并使用链式前向星存图。

[Code](https://www.luogu.com.cn/paste/agg85qq5)。

---

