# [AGC056C] 01 Balanced

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc056/tasks/agc056_c

考虑构造一个由 `0` 和 `1` 组成的长度为 $ N $ 的字符串 $ s $。其中 $ s $ 需要满足 $ M $ 个条件。第 $ i $ 个条件由整数 $ L_i, R_i $（$ 1 \leq L_i < R_i \leq N $）表示，这意味着在 $ s $ 的第 $ L_i $ 个字符到第 $ R_i $ 个字符之间，包含的 `0` 和 `1` 的数量必须相等。

请在所有满足条件的 $ s $ 中找出字典序最小的那个。可以证明，在问题的约束下，满足条件的 $ s $ 一定存在。

## 说明/提示

### 约束条件

- $ 2 \leq N \leq 10^6 $
- $ 1 \leq M \leq 200000 $
- $ 1 \leq L_i < R_i \leq N $
- $ (R_i - L_i + 1) \equiv 0 \pmod{2} $
- $ (L_i, R_i) \neq (L_j, R_j) $（$ i \neq j $）
- 输入中的所有值均为整数

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4 2
1 2
3 4```

### 输出

```
0101```

## 样例 #2

### 输入

```
6 2
1 4
3 6```

### 输出

```
001100```

## 样例 #3

### 输入

```
20 10
6 17
2 3
14 19
5 14
10 15
7 20
10 19
3 20
6 9
7 12```

### 输出

```
00100100101101001011```

# 题解

## 作者：ღꦿ࿐ (赞：13)

好题，考察了对差分约束较深的理解。

首先限制区间 $(l,r]$ 内恰好有 $\frac {r-l} 2$ 个 $1$，可以考虑将限制转化为前缀和数组上的限制，即 $S_r-S_l=\frac {r-l} 2$，又因为前缀和本身的限制关系 $S_{i}-S_{i-1}\in[0,1]$，可以得出一个差分约束的关系：

$$
\left\{
\begin{aligned}
&S_r-S_l=\frac {r-l} 2\\
&S_i\leq S_{i-1}+1\\
&S_{i-1}\leq S_i\\
\end{aligned}
\right.
$$

直接将等于边拆成大于小于边做差分约束求字典序最小的 $S$，因为有负权边会被卡成 $O(n^2)$。

考虑将等号代表的关系使用一个代表元表示（$S_i=S_{del(i)} + c_i$），这样可以避免掉上面的负权边，但是第二类边可能会出现 $S_i+c_i\leq S_j+c_j$ 移项得到 $S_i\leq S_j+c_j-c_i$ 在 $c_i > c_j$ 时同样会出现负权边。

考虑如何避免负权边，之所以会出现负权边是因为第一类的传递关系中会涉及到量的改变，我们试图建立一种直接的等价类关系来描述第一类关系：

考虑式子拆开成一个左侧只和 $l$ 相关右侧只和 $r$ 相关的等式：$2S_r-r=2S_l-l$，这样我们就把传递关系改成了一种等价关系，定义 $x_i=2S_i-i$，则上面三个式子分别变成了：

$$
\left\{
\begin{aligned}
&x_i=x_j\\
&x_i\leq x_{i-1}+1\\
&x_{i-1}\leq x_i+1\\
\end{aligned}
\right.
$$

（当然还有 $x_i\neq x_{i-1}$，这个条件会在后面的差分约束中天然被满足）

所以直接将所有第一种关系相同的 $x_i$ 用同一个变量 $x_{del(i)}$ 表示，然后对所有代表变量解决差分约束问题。

同样的，我们只需要最小化 $x$ 的字典序就可以最小化 $S$ 的字典序，直接 bfs 跑差分约束即可，因为我们求的是字典序最小解，可以证明不会出现 $x_i=x_{i-1}$ 的情况。

接下来我们来证明使用差分约束系统构造出的解天然满足 $x_i\neq x_{i-1}$：首先缩起来的代表元素一定满足代表的都是奇偶性相同的元素，接下来这个差分约束系统只会对若干个奇数下标等价类的 $x$ 的和偶数下标等价类的代表元之间连权为 $1$ 的边，故我们构造出来的差分约束系统是一个有向的二分图（只在奇数代表元和偶数代表元之间有边），所以通过差分约束得到的最短路的奇偶性是确定的，只和下标奇偶性相关，故 $x_i$ 和 $x_{i-1}$ 奇偶性一定不同。

代码：（为方便使用了并查集进行缩等价类，复杂度会多一个 $n\alpha(n)$）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define all(x) x.begin(),x.end()
#define rep(i,x,y) for(auto i(x);i<=(y);++i)
#define Rep(i,x,y) for(auto i(x);i>=(y);--i)
using namespace std;
const int N = 1e6 + 20 ;
int n , m , x[N] , fa[N] , ptr ;
vector <int> ed[N] ;
inline int find (int x) {
	while (x ^ fa[x]) x = fa[x] = fa[fa[x]] ;
	return x; 
}
signed main ( ) {
	ios :: sync_with_stdio(false) , cin.tie(0) , cout.tie(0);
	cin >> n >> m ; iota (fa,fa+n+1,0);
	rep (i,1,m) {
		int l , r ; cin >> l >> r ; -- l ;
		int gl = find (l) , gr = find (r) ;
		if(fa[gl] ^ gr) fa[gl] = gr ;
	}
	rep (i,1,n) {
		ed[find(i)].emplace_back (find(i - 1)) ;
		ed[find(i - 1)].emplace_back (find(i)) ; 
	}
	memset(x,-1,sizeof x);  x[find(0)] = 0;
	vector <int> q = {find(0)} ;
	while (ptr < (int)q.size( )) {
		int u = q[ptr ++];
		for (int v : ed[u]) {
			if (!~x[v]) {
				x[v] = x[u] + 1 ;
				q.emplace_back(v) ;
			}
		}
	} 
	
	rep (i,1,n)
		if (x[find(i)] > x[find(i - 1)]) 
			cout << 0 ;
		else 
			cout << 1 ; 
	
	return 0 ;
}


```

---

## 作者：joke3579 (赞：13)

直接做不好做，考虑将条件转化。令 $d_i$ 为 $1\sim i$ 中 $0$ 的个数减去 $1$ 的个数。   
容易发现，想要最小化原串的字典序，其实就是让 $0$ 尽可能多，也就是让 $d_i$ 尽可能大。这就转化为如何使得 $d_i$ 的字典序最大。

我们发现，给定的条件 $(l_i,r_i)$ 可以表述为 $d_{r_i} = d_{l_i - 1}$，因为 $[l_i,r_i]$ 段中 $0,1$ 个数是相等的，体现在 $d_i$ 上就是 $[l_i,r_i]$ 段有 $0$ 的贡献。    
同时根据定义可得 $\forall \ 1< i \le n,\ |d_i - d_{i-1}| = 1$。这与 $\forall \ 1< i \le n,\ |d_i - d_{i-1}| \le 1$ 等价。

列出我们已知的条件：
1. $\forall \ 1\le i \le m, \ d_{l_i - 1} = d_{r_i}$
2. $\forall \ 1< i \le n,\ |d_i - d_{i-1}| \le 1$

条件的特殊性启发我们采用差分约束系统求解本题，同时差分约束系统也可以很好地满足使 $d_i$ 字典序最大的需要。     
对 $1.$ 条件建 $(l_i - 1, r_i)$，边权为 $0$ 的双向边；对 $2.$ 条件建 $(i - 1, i)$，边权为 $1$ 的双向边。    
由于边权的特殊性，我们可以通过 01bfs 求解所有 $d_i$。这给出了构造方案。

总时间复杂度 $O(n +m)$。

$\text{code : }$
```cpp
#include <bits/stdc++.h>
using namespace std; 
template <typename T> void get(T & x) {
	x = 0; char ch = getchar(); bool f = false; while (ch < '0' or ch > '9') f = f or ch == '-', ch = getchar();
	while ('0' <= ch and ch <= '9') x = (x << 1) + (x << 3) + ch - '0', ch = getchar(); f && (x = -x); 
} template <typename T, typename ... Args> void get(T & a, Args & ... b) { get(a); get(b...); }
#define rep(i,s,t) for (register int i = (s), i##_ = (t) + 1; i < i##_; ++ i)
#define pre(i,s,t) for (register int i = (s), i##_ = (t) - 1; i > i##_; -- i)
const int N = 1e6 + 10;
int n, m, l, r; 
vector <pair<int,int> > g[N];

int dis[N];
deque<int> que;
void bfs(int st) {
	memset(dis, -1, sizeof dis);
	dis[st] = 0; que.push_back(st); 
	while (que.size()) {
		int u = que.front(); que.pop_front();
		for (auto [v, w] : g[u]) {
			if (dis[v] == -1) {
				dis[v] = dis[u] + w;
				if (w == 0) que.push_front(v);
				else que.push_back(v);
			}
		}
	}
}

int main() {
	get(n, m); 
	rep(i,1,m) get(l, r), g[r].emplace_back(l - 1, 0), g[l - 1].emplace_back(r, 0);
	rep(i,1,n) g[i - 1].emplace_back(i, 1), g[i].emplace_back(i - 1, 1);
	bfs(0);
	rep(i,1,n) cout << (dis[i] < dis[i - 1]);
}
```

---

## 作者：gaochunzhen (赞：4)

直接做肯定不好做，所以考虑转化成类似前缀和的形式。设 $v_i$ 表示 $s$ 的前 $i$ 个字符中，$0$ 的数量减去 $1$ 的数量的值。换句话说，$v$ 就是把 $s$ 中的 $0$ 换成 $1$、$1$ 换成 $-1$ 之后的前缀和。

所以，对于限制 $[l,r]$，就转化为了 $v_{l-1}=v_r$。并且，对于相邻的元素，也有 $|v_i-v_{i-1}|=1$ 的限制。如此，我们所求的就变成了字典序最大的 $v$。

由于 $|v_i-v_{i-1}|=1$ 的限制不好处理，所以我们不妨把它改为 $|v_i-v_{i-1}|\leq1$。所以现在我们的限制如下：

1. $v_{l-1}=v_r$；
2. $|v_i-v_{i-1}|\leq1\Rightarrow v_i-v_{i-1}\leq1,v_{i-1}-v_i\leq1$。

现在就可以固定 $v_0=0$ 为起点，然后连边建图，跑差分约束了。可以证明跑出来的一定是合法且字典序最大的解。

因为边权只有 $0$ 和 $1$，所以可以跑 0-1 BFS，时间复杂度 $\mathcal O(n+m)$。

---------

问题来了：为什么它合法（为什么 $s_i\neq s_{i-1}$），又为什么它字典序最大？

先来证明后者。它其实是差分约束的一个性质：如果跑的是最短路，那么在固定一个值时，其余的值都会取到能取到的最大值。

证明：假设从 $v_0$ 到 $v_u$ 的最短路经过的路径是：$v_{i_1}-v_0\leq l_0$、$v_{i_2}-v_{i_1}\leq l_1$、$\cdots$、$v_u-v_{i_k}\leq l_k$，那么把它们加起来可以得到 $v_n-v_0\leq l_0+l_1+\cdots l_k$。并且，从 $0$ 到 $u$ 的最短路长度也是 $l_0+\cdots+l_k$，所以 $v_u$ 取到了它的最大值。

所以，对于所有 $v_1$ 到 $v_n$，全部都取到了最大值，字典序必然最大。证毕。

现在看前者。设 $t_i=v_i-v_{i-1}$，那么我们要证明的是 $t_i\neq0$。

考虑反证法，如果 $v$ 中出现 $v_i=v_{i-1}$，那么我们可以将所有 $t_i=0$ 的位置按顺序取出，并分别赋值为 $1,-1,1,-1,\cdots$。这么做仍能够满足限制，因为如果原来的 $v$ 满足限制，那么 $t$ 在 $[l,r]$ 中必定有偶数个 $0$，在改完之后它们的和仍然是 $0$。并且这么做可以得到字典序更大的 $v$，故原来的 $v$ 不满足字典序最大，不可能被差分约束系统跑出来。证毕。

---------

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 9;
struct node {int v, w;};
vector<node> G[N];
int n, m, dis[N];
deque<pair<int, int> > q;
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int l, r; scanf("%d%d", &l, &r);
        G[l - 1].push_back({r, 0});
        G[r].push_back({l - 1, 0});
    }
    for (int i = 1; i <= n; i++) {
        G[i - 1].push_back({i, 1});
        G[i].push_back({i - 1, 1});
    }
    memset(dis, 0x3f, sizeof(dis));
    q.push_back(make_pair(0, 0)), dis[0] = 0;
    while (!q.empty()) {
        int u = q.front().first, p = q.front().second;
        q.pop_front();
        for (auto e : G[u]) {
            int v = e.v, w = e.w;
            if (dis[v] > dis[u] + w) {
              dis[v] = dis[u] + w;
              if (w) dis[v] = p + 1, q.push_back(make_pair(v, p + 1));
              else dis[v] = p, q.push_front(make_pair(v, p));
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        putchar((dis[i] - dis[i - 1] < 0) + '0');
    }
    return 0;
}
```

---

## 作者：Otue (赞：3)

普通差分约束会有负权边，为了规避这种情况，设 $s_i$ 表示前 $i$ 个字符中 $0$ 的个数减去 $1$ 的个数。为了使字典序最小，则 $s_i$ 则尽可能大，即跑最短路。

题目中给的 $[l_i,r_i]$ 条件 $0,1$ 个数相等可以转化成 $d_{l_i-1}=d_{r_i}$。这种情况可以连边 $(l_i-1,r_i,0)$ 和 $(r_i,l_i-1,0)$。

有一个隐含限制：$|d_i-d_{i-1}|\leq 1$。这种情况可以理解成 $-1\leq d_i-d_{i-1}\leq 1$。这种情况可以连边 $(i-1,i,1)$ 和 $(i,i-1,1)$。但有一种问题：$d_i=d_{i-1}$。因为我们求的是字典序最小解，则可以证明这种情况不存在。

因为边权只有 $0,1$，那么可以直接 01bfs。复杂度线性。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 1e6 + 5;

int n, m, l, r, dist[N];
vector<PII> G[N];

void bfs() {
	deque<int> q;
	q.push_front(0); dist[0] = 0;
	while (q.size()) {
		int u = q.front(); q.pop_front();
		for (auto e : G[u]) {
			int v = e.first, d = e.second;
			if (dist[v] == -1) {
				dist[v] = dist[u] + d;
				if (d == 0) q.push_front(v);
				else q.push_back(v); 
			} 
		}
	}
}

signed main() {
	memset(dist, -1, sizeof dist);
	cin >> n >> m;
	_for(i, 1, m) {
		int l, r;
		cin >> l >> r;
		G[l - 1].push_back({r, 0});
		G[r].push_back({l - 1, 0});
	}
	_for(i, 1, n) G[i].push_back({i - 1, 1}), G[i - 1].push_back({i, 1}); 
	bfs();
	_for(i, 1, n) cout << (dist[i] < dist[i - 1]);
}
```

---

## 作者：yzysdTNT (赞：3)

看到要满足 $m$ 个条件就想到差分约束了。
## 建图
考虑使用前缀和维护区间 $0/1$ 数量，因为题目操作与相对个数有关，考虑将其记为 $1/-1$ 维护相对值；因为题目要使序列字典序最小，即让 $0$ 尽可能多，因此可以将 $s_i$ 记为区间 $[1,i]$ 中 $0$ 的数量减 $1$ 的数量，使其尽可能大；  
如上处理，因为序列每一个值 $x \in {0,1}$，所以每一个 $s_i$ 都有 $s_i = s_{i - 1} + 1$ 或 $s_i = s_{i - 1} - 1$，即 $|s_i - s_{i - 1}| = 1$；对于每个操作，有 $s_r = s_{l - 1}$。
将这两个等式转化为差分约束的条件（不等式），则对于每一次操作，有
$$
s_r - s_{l - 1} \ge 0\\
s_r - s_{l - 1} \le 0
$$
对于前缀和数组 $s$，因为 $s_i - s_{i - 1} \in {1,-1}$，所以可以将绝对值转为
$$
s_i - s_{i - 1} \ge -1\\
s_i - s_{i - 1} \le 1
$$  
据此连边建图即可。  
CODE:

```cpp
for(int i = 1,l,r;i <= m;i++){
		cin >> l >> r;
		add(l - 1,r,0);
		add(r,l - 1,0);
	}
	for(int i = 1;i <= n;i++){
		add(i,i - 1,1);
		add(i - 1,i,1);
	}
```
## 求解
~~当然食用最短路啦~~。从前面的建图可以看出这是没有负权边的，所以可以直接用 Dijkstra 来处理，~~才不是SPFA死了呢~~。直接套板子就行。


## 输出
我们最短路跑出来的是 $s$，前缀和数组，所以要将其转化为序列。如果当前位置 $0$ 的数量小于上一个位置，即 $s_i < s_{i - 1}$，当前位置就应该是 $1$，否则为 $0$。  
CODE:

```cpp
for(int i = 1;i <= n;i++) cout << (s[i] < s[i - 1]);
```
然后就没啦。

## [完整代码](https://www.luogu.com.cn/record/172016320)


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n,m,s[N],cnt[N],hd[N],t;
bool vis[N];
struct E{
	int to,nxt,val;
}e[N * 5];

void add(int u,int v,int w){
	e[++t] = {v,hd[u],w};
	hd[u] = t;
} 
void dij(){
	priority_queue<pair<int,int>> q;
	q.push({0,0});
	s[0] = 0;
	while(!q.empty()){
		auto x = q.top();
		q.pop();
		int ew = -x.first,u = x.second;
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = hd[u];i;i = e[i].nxt){
			int v = e[i].to,w = e[i].val;
			if(s[v] > s[u] + w){
				s[v] = s[u] + w;
				q.push({-s[v],v});
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); 
	cin >> n >> m;
	for(int i = 1;i <= n;i++) s[i] = 1e9;
	for(int i = 1,l,r;i <= m;i++){
		cin >> l >> r;
		add(l - 1,r,0);
		add(r,l - 1,0);
	}
	for(int i = 1;i <= n;i++){
		add(i,i - 1,1);
		add(i - 1,i,1);
	}
	dij();
	for(int i = 1;i <= n;i++) cout << (s[i] < s[i - 1]);
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：2)

## Solution

考虑差分约束。

考虑令 $\tt0$ 为 $-1$，限制变为了区间和为 $0$。记 $s_i$ 为前缀和，限制相当于 $s_{l-1}=s_r$，$l-1$ 和 $r$ 之间连两条权值为 $0$ 的边即可。

另一个限制是 $\lvert s_i-s_{i-1}\rvert=1$。我们只考虑 $\lvert s_i-s_{i-1}\rvert=1$，$i-1$ 和 $i$ 之间连两条权值为 $1$ 的边，01BFS 跑出最短路，反转 $\tt01$ 即为答案。

正确性：
- 可以发现如果 $u,v$ 连边，边权必为 $(u-v)\bmod2$，故 $s_i$ 和 $i$ 奇偶性相同，保证了没有 $s_i=s_{i-1}$。
- 差分约束跑出最短路每个变量都取到上界，故反转 $\tt01$ 即为字典序最小答案。

## Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	int n, m, x, y, d[N]; deque<int> q; vector<pii> G[N];
	int main() {
		cin >> n >> m;
		REP(i, 1, m) cin >> x >> y, x --, G[x].pb(y, 0), G[y].pb(x, 0);
		REP(i, 1, n) G[i].pb(i - 1, 1), G[i - 1].pb(i, 1), d[i] = -1;
		q.pb(0);
		while (SZ(q)) {
			int x = q.front(); q.pop_front();
			for (auto [y, w] : G[x]) {
				if (~d[y]) continue;
				if (!w) d[y] = d[x], q.push_front(y);
				else d[y] = d[x] + 1, q.pb(y);
			}
		}
		DEP(i, n, 1) d[i] -= d[i - 1];
		REP(i, 1, n) cout << (d[i] > 0 ? 0 : 1);
		cout << '\n';
		return 0;
	}
}
```

---

