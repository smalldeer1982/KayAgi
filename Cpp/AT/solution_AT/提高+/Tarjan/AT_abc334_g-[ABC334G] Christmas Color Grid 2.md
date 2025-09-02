# [ABC334G] Christmas Color Grid 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc334/tasks/abc334_g

**本题与问题 E 的设定类似。与问题 E 的不同之处已用红色字体标出。**

有一个 $H$ 行 $W$ 列的网格，每个格子被涂成红色或绿色。

网格中从上往下第 $i$ 行，从左往右第 $j$ 列的格子记作格子 $(i,j)$。

格子 $(i,j)$ 的颜色用字符 $S_{i,j}$ 表示，若 $S_{i,j} = \texttt{.}$，则格子 $(i,j)$ 被涂为红色；若 $S_{i,j} = \texttt{\#}$，则格子 $(i,j)$ 被涂为绿色。

在网格中，将所有被涂为绿色的格子作为顶点集合，将所有相邻的两个绿色格子之间连一条边，构成一个图。该图的连通分量个数称为**绿色连通分量数**。这里，两个格子 $(x,y)$ 和 $(x',y')$ 相邻，指的是 $|x-x'| + |y-y'| = 1$。

**随机等概率选择一个绿色格子，将其重新涂为红色后，网格中的绿色连通分量数的期望值是多少？请将答案对 $998244353$ 取模后输出。**

“将期望值对 $998244353$ 取模后输出”是指，所求的期望值一定是有理数。在本题的约束下，设其值可表示为互质的两个整数 $P, Q$ 的分数 $\frac{P}{Q}$，则一定存在唯一的整数 $R$ 满足 $R \times Q \equiv P \pmod{998244353}$ 且 $0 \leq R < 998244353$。请输出这个 $R$。

## 说明/提示

### 约束条件

- $1 \leq H, W \leq 1000$
- $S_{i,j} = \texttt{.}$ 或 $S_{i,j} = \texttt{\#}$
- 至少存在一个 $(i,j)$ 使得 $S_{i,j} = \texttt{\#}$

### 样例解释 1

将格子 $(1,1)$ 涂为红色后，绿色连通分量数为 $3$。  
将格子 $(1,2)$ 涂为红色后，绿色连通分量数为 $2$。  
将格子 $(2,1)$ 涂为红色后，绿色连通分量数为 $3$。  
将格子 $(2,3)$ 涂为红色后，绿色连通分量数为 $1$。  
将格子 $(3,1)$ 涂为红色后，绿色连通分量数为 $2$。  
因此，随机等概率选择一个绿色格子，将其涂为红色后，绿色连通分量数的期望值为 $(3+2+3+1+2)/5 = 11/5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
##.
#.#
#..```

### 输出

```
598946614```

## 样例 #2

### 输入

```
4 5
..#..
.###.
#####
..#..```

### 输出

```
199648872```

## 样例 #3

### 输入

```
3 4
#...
.#.#
..##```

### 输出

```
399297744```

# 题解

## 作者：rui_er (赞：6)

先求出初始时绿连通块数量。

将一个绿色格子染成红色，会改变绿连通块数量，当且仅当这个绿色格子是孤点或割点。如果是孤点，会使得绿连通块数量减少一；如果是割点，会使得绿连通块数量增加它所在的点双数量减一。根据上述规则可以求出每个绿色格子染红后的绿连通块数量，求平均值即可。

时间复杂度 $O(nm)$。

```cpp
// Problem: G - Christmas Color Grid 2
// Contest: AtCoder - UNIQUE VISION Programming Contest 2023 Christmas (AtCoder Beginner Contest 334)
// URL: https://atcoder.jp/contests/abc334/tasks/abc334_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

typedef Modint<998244353> mint;

const int K = 1e3 + 5, N = 1e6 + 5;
const int nxt[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

int n, m, k, vis[K][K];
string s[K];
int dfn[N], low[N], cut[N], cnt[N], tms;
vector<vector<int>> bcc;
stack<int> stk;
mint ans, tot;

inline int getId(int x, int y) {
    return (x - 1) * m + y;
}

void dfs(int x, int y, int u) {
    vis[x][y] = u;
    rep(d, 0, 3) {
        int nx = x + nxt[d][0], ny = y + nxt[d][1];
        if(s[nx][ny] == '#' && !vis[nx][ny]) dfs(nx, ny, u);
    }
}

struct Edge {
	int v, nxt;
	Edge(int a = 0, int b = 0) : v(a), nxt(b) {}
}e[N * 8];
int h[N], ne = 1;
inline void add(int u, int v) {
	e[++ne] = Edge(v, h[u]); h[u] = ne;
	e[++ne] = Edge(u, h[v]); h[v] = ne;
}

void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++tms;
	stk.push(u);
	int deg = 0;
	for(int i = h[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if(v == fa) continue;
		if(!dfn[v]) {
			++deg;
			tarjan(v, u);
			chkmin(low[u], low[v]);
			if(low[v] >= dfn[u]) {
			    cut[u] = 1;
				bcc.push_back({}); 
				while(true) {
					int w = stk.top(); stk.pop();
					bcc.back().push_back(w);
					++cnt[w];
					if(w == v) break;
				}
				bcc.back().push_back(u);
				++cnt[u];
			}
		}
		else chkmin(low[u], dfn[v]);
	}
	if(!fa && deg == 1) cut[u] = 0;
	if(!fa && !deg) {
	    bcc.push_back({u});
	    cut[u] = -1;
	}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    s[0] = s[n + 1] = string(m + 2, ' ');
    rep(i, 1, n) {
        cin >> s[i];
        s[i] = ' ' + s[i] + ' ';
    }
    rep(i, 1, n) rep(j, 1, m) if(s[i][j] == '#' && !vis[i][j]) dfs(i, j, ++k);
    rep(i, 1, n) {
        rep(j, 1, m) {
            if(s[i][j] == '#') {
                rep(d, 0, 3) {
                    int nx = i + nxt[d][0], ny = j + nxt[d][1];
                    if(s[nx][ny] == '#') add(getId(i, j), getId(nx, ny));
                }
            }
        }
    }
    rep(i, 1, n) {
        rep(j, 1, m) {
            if(s[i][j] == '#' && !dfn[getId(i, j)]) {
                tarjan(getId(i, j), 0);
            }
        }
    }
    rep(i, 1, n) {
        rep(j, 1, m) {
            if(s[i][j] == '#') {
                ++tot;
                ans += k;
                if(cut[getId(i, j)] == 1) ans += cnt[getId(i, j)] - 1;
                else if(cut[getId(i, j)] == -1) --ans;
            }
        }
    }
    cout << ans / tot << endl;
    return 0;
}
```

---

## 作者：ZnPdCo (赞：6)

枚举要修改的点，我们可以把相邻的绿色互相连边。原题就成了一个无向图上删掉一个点剩下的连通块个数。

用 Tarjan 算法，设 $u$ 为当前结点，$v$ 为子节点，若跑完 $v$ 后，得到 $\text{low}_v \ge \text{dfn}_u$ 则说明从 $u$ 的父亲结点，经过 $u$ 才能够到达 $v$ ，如果把结点 $u$ 删掉，则不能到达结点 $v$ 了。

这就相当于删去结点 $u$ 时，$u$ 的父亲结点与结点 $v$ 会被分成两个连通块，即这两部分无法相互到达，因此只需要数一下对于结点 $u$，它有多少个 $v$，满足 $\text{low}_v \ge \text{dfn}_u$，当然其实 $u$ 的父亲结点也算是一个儿子节点，因此需要加上一表示算上父亲节点。但每次 Tarjan 的起点是没有父亲节点的，所以不需要加一。

综上所述，删去一个结点 $u$ 会造成怎样的影响呢？假设删去结点 $u$ 会增加 $\text{block}_u$ 个连通块，这个无向图初始包含 $m$ 个连通块，这个节点原来是属于 $1$ 个连通块的，它删去后会增加 $\text{block}_u$ 个连通块，那么删去这个结点后连通块的数量应为 $m-1+\text{block}_u$。

```c++
/**
 * @file G.cpp
 * @tag: #AtCoder#ABC#ABC334
 * @author: ZnPdCo
 * @date: 2023-12-23 19:50:12
 * @problem: https://atcoder.jp/contests/abc334/tasks/abc334_g
 **/
#include <bits/stdc++.h>
#define P 998244353
#define ll long long
#define N 2000
using namespace std;
ll n, m;
char a[N][N];

const ll dx[4] = {0, 1, 0, -1};
const ll dy[4] = {1, 0, -1, 0};
ll zip(ll x, ll y) {
	return x * (m+10) + y;
}
ll head[N*N];
ll nxt[4*N*N];
ll to[4*N*N], cnt;
ll qpow(ll x, ll y) {
	if(y == 0) return 1;
	if(y % 2 == 1) return x * qpow(x, y - 1) % P;
	ll tmp = qpow(x, y / 2);
	return tmp * tmp % P;
}
void addEdge(ll u, ll v) {
	cnt++;
	to[cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}
void bfs(ll x, ll y) {
	a[x][y] = '*';
	queue<pair<ll, ll> > q;
	q.push(make_pair(x, y));
	while(!q.empty()) {
		x = q.front().first;
		y = q.front().second;
		for(ll i = 0; i < 4; i++) {
			ll xx = x + dx[i];
			ll yy = y + dy[i];
			if(xx > 0 && xx <= n && yy > 0 && yy <= m && a[xx][yy] != '.') {
				addEdge(zip(x, y), zip(xx, yy));
				if(a[xx][yy] == '#') {
					a[xx][yy] = '*';
					q.push(make_pair(xx, yy));
				}
			}
		}
		q.pop();
	}
}
ll dfn[N*N], low[N*N], t;
ll block[N*N];
void tarjan(ll u, ll fa) {
	dfn[u] = low[u] = ++t;
	if(fa) block[u]++;
	for(ll i = head[u]; i; i = nxt[i]) {
		ll v = to[i];
		if(v == fa) continue;
		if(!low[v]) {
			tarjan(v, u);
			if(low[v] >= dfn[u]) block[u]++;
			else low[u]=min(low[u], low[v]);
		} else {
			low[u] = min(low[u], dfn[v]);
		}
	}
}
char s[N];
ll ans;
ll num;
int main() {
	scanf("%lld %lld", &n, &m);
	for(ll i = 1; i <= n; i++) {
		scanf("%s", a[i]+1);
	}
	for(ll i = 1; i <= n; i++) {
		for(ll j = 1; j <= m; j++) {
			if(a[i][j] == '#') {
				bfs(i, j);
				num++;
			}
		}
	}
	for(ll i = 1; i <= n; i++) {
		for(ll j = 1; j <= m; j++) {
			if(a[i][j] == '*' && !dfn[zip(i,j)]) {
				tarjan(zip(i, j), 0);
			}
		}
	}
	ll point = 0;
	for(ll i = 1; i <= n; i++) {
		for(ll j = 1; j <= m; j++) {
			if(a[i][j] == '*') {
				(ans += (num + block[zip(i, j)] - 1)) %= P;
				point++;
			}
		}
	}
	(ans *= qpow(point, P-2))%= P;
	printf("%lld", ans);
}
```

---

## 作者：Kingna (赞：3)

把一个 `#` 变成 `.` 有啥变化？

不太好考虑，考虑对原数组建图（相邻的 # 连边）。

一个 `#` 变成 `.` 等价于删掉这个点和与它相连的所有边。等价于割点。

若一个割点被 $x$ 个点双分量所包含，那么删掉他就会增加 $x-1$ 个连通分量。

注意特判孤立点的情况。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 4e6 + 5, M = 1005, mod = 998244353;
int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1};
vector<int> G[N];

int n, m, low[N], dfn[N], cut[N], idx, sv[N];
stack<int> stk;
char a[M][M];
int p[N], cc[N];

int find(int x)  {
	if (p[x] != x) p[x] = find(p[x]);
	return p[x];
}

void merge(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) p[fx] = fy;
}

int get(int x, int y) {
	return (x - 1) * m + y;
}

int qpow(int a, int k, int p ){
	int res = 1;
	while(k) {
		if (k & 1) res = res * a % p;
		a = a * a % p;
		k >>= 1;
	}
	return res;
}

void tarjan(int root, int u) {
	sv[u] = root;
	dfn[u] = low[u] = ++idx;
	stk.push(u);
	if (u == root && G[u].size() == 0) {
		cc[u]++;
		return;
	}
	
	int cnt = 0;
	for (auto v : G[u]) {
		if (!dfn[v]) {
			tarjan(root, v);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				cnt++;
				if (u != root || cnt > 1) cut[u] = 1;
				int y;	
				do {
					y = stk.top(); stk.pop();
					cc[y]++;
				} while (v != y);
				cc[u]++;
			}
		}
		else low[u] = min(low[u], dfn[v]);
	}
} 

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) cin >> a[i][j];
	}
	for (int i = 0; i <= N - 5; i++) p[i] = i;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k < 4; k++) {
				int dx = i + dir[k][0], dy = j + dir[k][1];
				if (dx < 1 || dx > n || dy < 1 || dy > m) continue;
				if (a[dx][dy] == a[i][j] && a[i][j] == '#') G[get(dx, dy)].push_back(get(i, j)), G[get(i, j)].push_back(get(dx, dy));
			}
		}
	}
	int qq = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!dfn[get(i, j)] && a[i][j] == '#') tarjan(get(i, j), get(i, j)), qq++;
		}
		
	}
	int cnt = 0, ss = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
		 
			if (a[i][j] == '#') {
				ss++;
				if (cut[get(i, j)]) cnt += qq + cc[get(i, j)] - 1;
				else {
					if (G[get(i, j)].size() == 0 && sv[get(i,j)] == get(i, j)) cnt += qq - 1;
					else cnt += qq;
				}
				cnt %= mod;
			}
		} 
	}
	cout << cnt * qpow(ss, mod - 2, mod) % mod << endl;
}
```

---

## 作者：EuphoricStar (赞：2)

考虑相当于把每个标记点的边全部断掉，然后求连通块个数。

考虑一条边 $(u, v)$（设 $u < v$）的出现时间，不难发现是 $[1, u - 1] \cup [u + 1, v - 1] \cup [v + 1, n]$。于是考虑直接套线段树分治和可撤销并查集。

时空复杂度均为 $O(n^2 \log^2 n)$。实现得别太随意就能过了。

[code](https://atcoder.jp/contests/abc334/submissions/48775537)

---

## 作者：Unnamed114514 (赞：2)

对四联通的绿点建图，先求初始连通块数，然后找增量。显然只有删掉的点是割点才能增加连通块数，于是自然想到建圆方树，增加的连通块数就是这个圆点连的方点的数量，统计出度即可。

---

## 作者：Sharpsmile (赞：2)

题面不表。

大家全都是高贵的 tarjan 的 $O(nm)$ 做法啊。

但是点双感觉不是很好写也不是很好调。

观察一下题目性质，$10^6$ 个点，两秒，AT 的机子。

直接赏他一个 $O(nm\log^2 nm)$！

具体的，我们需要对每个点求删掉他的连通块数量，这个形式非常的缺一分治啊。

我们每次加入点的时候就只需要看看那些边的两个端点都被加入了，然后加入这些边就行了。

然后使用带撤销并查集维护一下连通块数量就可以了。

这个做法易于编写，而且无脑好想。如果选手追求 AK 速度且对自己的代码常数有着足够的自信的话是一个非常好的选择！

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define endl "\n"
#define pii pair<int,int>
#define p1(x) ((x).first)
#define p2(x) ((x).second)
int n,m,k;
const int M=998244353;
inline int qp(int a,int  x){
    int res=1;
    while(x){
        if(x&1)res=res*a%M;
        x>>=1;
        a=a*a%M;
    }
    return res;
}
inline int inv(int a){
    return qp(a,M-2);
}
int f[1000300];
int siz[1003000];
bool p[1003][1003];
int id[1003][1003];
vector<int>g[1000300];
inline void add(int u,int v){
    g[u].push_back(v);
    g[v].push_back(u);
}
inline int ff(int x){return f[x]==x?x:ff(f[x]);}
stack<int>S;
int cnt=0;
inline bool  merge(int x,int y){
    x=ff(x),y=ff(y);
    if(x==y)return 0;
    cnt--;
    if(siz[x]<siz[y])swap(x,y);
    f[y]=x,siz[x]+=siz[y],S.push(y);
    return 1;
}
inline void del(){
    int x=S.top();S.pop();
    cnt++,siz[f[x]]-=siz[x],f[x]=x;

}
int res=0;
bool ins[1000300];
inline int INS(int x){
    ins[x]=1;
    int cnt=0;
    for(int v:g[x])
        if(ins[v])cnt+=merge(x,v);
    return cnt;
}
inline void calc(int l,int r){
    if(l==r){
        res+=cnt-1;
        return ;
    }
    int mid=l+r>>1,s=0;
    for(int i=mid+1;i<=r;i++)s+=INS(i);
    calc(l,mid);
    while(s--)del();
    for(int i=mid+1;i<=r;i++)ins[i]=0;
    
    s=0;
    for(int i=l;i<=mid;i++)s+=INS(i);
    calc(mid+1,r);
    while(s--)del();
    for(int i=l;i<=mid;i++)ins[i]=0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cout.flush();
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            char x;cin>>x;
            p[i][j]=x=='#';
            if(p[i][j])id[i][j]=++k,siz[k]=1,f[k]=k;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)if(p[i][j]){
            if(p[i-1][j])add(id[i][j],id[i-1][j]);
            if(p[i][j-1])add(id[i][j],id[i][j-1]);
        }
    cnt=k;
    calc(1,k);
    res%=M;
    cout<<res*inv(k)%M<<endl;
    return 0;
}

```


---

## 作者：forgotmyhandle (赞：1)

第一次 AK abc，写篇题解记录一下。

[原题传送门](https://atcoder.jp/contests/abc334/tasks/abc334_g)
 
[你谷传送门](https://www.luogu.com.cn/problem/AT_abc334_g)

## 分析
发现实际上是要求删去每个绿点之后会多出几个连通块。发现这跟割点的定义很像，于是考虑建图，在相邻的绿点之间连边。然后就只要知道每个点到底被包含在几个点双里。我们使用圆方树，此时就只需要统计每个点的度数就可以了。

## 代码
```
#include <iostream>
#define int long long
using namespace std;
const int P = 998244353;
char mp[1005][1005];
int n, m;
int f(int x, int y) { return (x - 1) * m + y; }
int head[1000005], nxt[10000005], to[10000005], ecnt;
void add(int u, int v) { to[++ecnt] = v, nxt[ecnt] = head[u], head[u] = ecnt; }
void adde(int x, int y) { add(x, y), add(y, x); }
int dfn[1000005], low[1000005], deg[2000005];
int ncnt;
int stk[1000005], sz;
void tarjan(int x) {
    stk[++sz] = x;
    dfn[x] = low[x] = ++ncnt;
    for (int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            low[x] = min(low[x], low[v]);
            if (low[v] == dfn[x]) {
                int t;
                do {
                    t = stk[sz--];
                    deg[t]++;
                } while (t != x);
                stk[++sz] = x;
            }
        } else 
            low[x] = min(low[x], dfn[v]);
    }
}
int qpow(int x, int y) {
    int ret = 1;
    while (y) {
        if (y & 1) 
            ret = ret * x % P;
        x = x * x % P;
        y >>= 1;
    }
    return ret;
}
signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string str;
        cin >> str;
        for (int j = 1; j <= m; j++) {
            mp[i][j] = str[j - 1];
            if (mp[i][j] == '#') {
                if (mp[i - 1][j] == mp[i][j]) 
                    adde(f(i - 1, j), f(i, j));
                if (mp[i][j - 1] == mp[i][j]) 
                    adde(f(i, j - 1), f(i, j));
            }
        }
    }
    int xcnt = 0, cnt = 0, tot = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cnt += (mp[i][j] == '#');
            if (mp[i][j] == '#' && !dfn[f(i, j)]) 
                tarjan(f(i, j)), ++xcnt;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] == '#') {
                tot += xcnt - 1 + deg[f(i, j)];
                tot >= P ? (tot -= P) : 0;
            }
        }
    }
    cout << tot * qpow(cnt, P - 2) % P;
    return 0;
}
```

---

## 作者：fydj (赞：1)

# [ABC334G] Christmas Color Grid 2

### 题目翻译

这个问题与 E 题相似，不同点原文用红字标出。

有一个 $H$ 行 $W$ 列的网格，网格中每个位置都被涂成红色或绿色，记从上往下数第 $i$ 行、从左往右数第 $j$ 列为 $(i,j)$。

$(i,j)$ 的颜色用符号 $S_{i,j}$ 表示，`.` 表示红色，`#` 表示绿色。

把涂成绿色的位置当成顶点集合，把连接相邻两个绿色位置的边当作边集合，把最后生成的图的连通块个数称为“绿色连通分量数”。在这里，相邻是指两个点 $(x,y)$ 和 $(x',y')$ 满足 $|x-x'|+|y-y'|=1$。

从涂成绿色的位置中等概率地选 $1$ 个出来涂成红色，求涂成红色后“绿色连通分量数”的期望个数模 $998244353$ 的值。

### 思路

按照题目，把绿色位置的点和连接相邻两个绿色位置的边提出来，变成一个图。把绿色点涂成红色相当于删掉一个点。可以想到，删掉割点会使原来一些连通的点变得不连通，所以可以考虑用 [Tanjan](https://oi-wiki.org/graph/cut/) 求割点，具体内容看 [纸质资料](https://oi-wiki.org/graph/cut/)。

对于顶点 $x$，如果有个儿子 $y$ 满足 $low_y \ge dfn_x$，说明它不能回到祖先，因此删掉点 $x$ 后它会变成新的连通块，使连通块个数加 $1$。特别的，在搜索的起始点，删掉这个点后它的所有儿子都会变成新的连通块，因此连通块增加的个数就是它儿子数量减 $1$。如果一个连通块大小为 $1$，它作为起始点进行 DFS 会发现它没有儿子，因此删掉它后连通块个数会增加 $-1$ 个。

用 [Tanjan](https://oi-wiki.org/graph/cut/) 求割点即可。

至于那个取模，会求 [逆元](https://oi-wiki.org/math/number-theory/inverse/) 的话可以轻松解决，这里不再赘述。不会求逆元可以参考 [纸质资料](https://oi-wiki.org/math/number-theory/inverse/)。

### 代码

```cpp
void dfs(int x,int fa) {
	did[x]=true,dfn[x]=++tdfn,low[x]=dfn[x];
	int child=0,i,y;
	for(i=ls[x];i;i=nx[i]) {
		y=e[i];
		if(!did[y]) {
			++child;
			dfs(y,x);
			low[x]=min(low[x],low[y]);
			if(fa!=x&&low[y]>=dfn[x])
				is[x]=true,++jia[x];
		} else if(y!=fa)
			low[x]=min(low[x],dfn[y]);
	}
	if(x==fa) jia[x]=child-1,is[x]=child>1;
	return ;
}
```

### 后记

怀着悲愤的心情写下这篇题解，ABC334 前四题卡了一小时，最后 1 分钟打完 G 题，花 40 秒测完样例，最后 20 秒提交，网络差，交不了，比赛结束，再次提交，交上了，A 了。



---

## 作者：Register_int (赞：1)

建图，则操作相当于在无向图中删去一个点。枚举被删的是哪个点，算出所有情况下的连通块数量，求和后除以方案数即可算出期望。有以下几种情况：

- 这个点本身就是一个连通块，数量 $-1$。
- 我们删的不是一个割点，连通块数量不变。
- 我们删的是割点，连通块数量减少它连接的点双数量 $-1$。

容易发现后两种情况可以合并，跑个 tarjan 求每个点在几个点双里即可、时间复杂度 $O(nm)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;
const int MAXM = 1e3 + 10;
const int mod = 998244353;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	for (; p; p >>= 1, b = b * b % mod) if (p & 1) res = res * b % mod;
	return res;
}

vector<int> g[MAXN]; int d[MAXN];

inline 
void add(int u, int v) {
	g[u].push_back(v), d[u]++;
}

int dfn[MAXN], low[MAXN], id;

stack<int> st; int cnt[MAXN];

inline 
void tarjan(int u, int fa) {
	int son = 0; dfn[u] = low[u] = ++id, st.push(u);
	for (int v : g[u]) {
		if (!dfn[v]) {
			son++, tarjan(v, u), low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) { for (int x = 0; x != v; cnt[x = st.top()]++, st.pop()); cnt[u]++; }
		} else low[u] = min(low[u], dfn[v]);
	}
	if (!fa && !son) cnt[u]++;
}

int n, m; char s[MAXM][MAXM];

inline 
int pos(int i, int j) {
	return (i - 1) * m + j;
}

int tot, x, ans;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s[i][j] != '#') continue;
			if (s[i - 1][j] == '#') add(pos(i, j), pos(i - 1, j));
			if (s[i + 1][j] == '#') add(pos(i, j), pos(i + 1, j));
			if (s[i][j - 1] == '#') add(pos(i, j), pos(i, j - 1));
			if (s[i][j + 1] == '#') add(pos(i, j), pos(i, j + 1));
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) if (s[i][j] == '#' && !dfn[pos(i, j)]) tarjan(pos(i, j), 0), x++;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s[i][j] != '#') continue; tot++;
			if (!d[pos(i, j)]) ans--;
			else ans += cnt[pos(i, j)] - 1;
		}
	}
	printf("%lld", ((ll)tot * x + ans) % mod * qpow(tot, mod - 2) % mod);
}
```

---

## 作者：wosile (赞：1)

ABC 改成 $7$ 题以来最简单的 G 之一。

首先考虑建图，相邻两个 `#` 连边就好。

然后对这个图建圆方树（其实是圆方森林），考虑删去一个原图上的点（圆点）的影响。

发现我们删去一个圆点 $u$ 后，与之相邻的每个点都会形成一个独立的连通块，也就是会形成 $d(u)$ 个连通块，其中 $d(u)$ 表示 $u$ 的度。

故而，对于每一个 `#`，把它变成 `.` 之后就会多出来 $d(u)-1$ 个连通块，直接求平均值即可。

时间复杂度 $O(n)$，但是我的实现比较弱智是 $O(n\alpha(n))$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
vector<int>G[1000005],T[2000005];
int dep[1000005],st[1000005],top=0;
int f[1000005],fa[1000005],vis[1000005]; 
int c[1000005];
int mp[1000005];
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
typedef long long ll;
char s[1005][1005];
void dfs(int x){
	fa[x]=x;
	vis[x]=1;
	dep[x]=dep[f[x]]+1;
	st[++top]=x;
	for(int i=0;i<G[x].size();i++){
		int v=G[x][i];
		if(!vis[v]){
			f[v]=x;
			dfs(v);
		}
		else if(dep[v]<dep[x]){
			c[x]++;
			c[st[dep[v]+1]]--;
		}
	}
	for(int i=0;i<G[x].size();i++)if(f[G[x][i]]==x)c[x]+=c[G[x][i]];
	if(c[x]>0)fa[find(x)]=find(f[x]);
	top--;
}
int h,w;
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};
inline int id(int x,int y){
	return (x-1)*w+y;
}
void visit(int x){
	vis[x]=1;
	for(int v:G[x])if(vis[v]==0)visit(v);
}
#define mod 998244353
ll qp(ll x,ll y){
	ll ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
int isrt[1000005];
int main(){
	scanf("%d%d",&h,&w);
	for(int i=1;i<=h;i++)scanf("%s",s[i]+1);
	n=h*w;
	for(int i=1;i<=h;i++)for(int j=1;j<=w;j++)if(s[i][j]=='#'){
		for(int d=0;d<2;d++){
			int nx=i+dx[d];
			int ny=j+dy[d];
			if(s[nx][ny]=='#'){
				G[id(i,j)].push_back(id(nx,ny));
				G[id(nx,ny)].push_back(id(i,j));
			}
		}
	}
	int cnt=0;
	for(int i=1;i<=h;i++)for(int j=1;j<=w;j++)if(vis[id(i,j)]==0 && s[i][j]=='#')visit(id(i,j)),++cnt;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)if(!vis[i]){
		dfs(i);
		isrt[i]=1;
	}
	int tot=n;
	for(int i=1;i<=n;i++)if(!isrt[i] && fa[i]==i){
		mp[i]=++tot;
		T[tot].push_back(f[i]);
		T[f[i]].push_back(tot);
	}
	for(int i=1;i<=n;i++)if(!isrt[i]){
		int sq=mp[find(i)];
		T[sq].push_back(i);
		T[i].push_back(sq);
	}
	ll ans=0,fuck=0;
	for(int i=1;i<=h;i++)for(int j=1;j<=w;j++)if(s[i][j]=='#'){
		++fuck;
		ans+=cnt-1+T[id(i,j)].size();
	}
	printf("%lld",ans%mod*qp(fuck,mod-2)%mod);
	return 0;
}
```

---

## 作者：happybob (赞：0)

对于这个网格图四联通建边，然后建圆方树。

很显然一个图中删掉一个点增加的连通块数量为圆方树上这个点的度数 $-1$。

于是直接就做完了。每个点累加答案，求个平均数就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1005, MOD = 998244353, HSMOD = 1610612741, HSMOD2 = 998244353; // Remember to change

int n, m, q, t, a[N];
char c[N][N];

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

int qpow(int a, int b)
{
	int res=1LL,base=a;
	while(b)
	{
		if(b&1LL)
		{
			res=res*base%MOD;
		}
		base=base*base%MOD;
		b>>=1LL;
	}
	return res;
}

int get(int x, int y)
{
	return (x-1)*m+y;
}

class Union_Find
{
public:
	int fa[N*N],sz[N*N];
	void Init()
	{
		for(int i=1;i<N*N;i++) fa[i]=i,sz[i]=1;
	}
	int find(int u)
	{
		return (fa[u]==u?u:find(fa[u])); 
	}
	pair<int, int> merge(int u, int v)
	{
		if((u=find(u))==(v=find(v))) return make_pair(-1,-1);
		if(sz[u]<sz[v]) swap(u,v);
		sz[u]+=sz[v];
		fa[v]=u;
		return make_pair(u,v);
	}
	void del(int u, int v)
	{
		sz[u]-=sz[v];
		fa[v]=v;
	}
}uf;

bool vis[N][N];
int dx[]={0,0,-1,1};
int dy[]={-1,1,0,0};

void dfs(int x, int y)
{
	vis[x][y]=1;
	for(int i=0;i<4;i++)
	{
		int nx=x+dx[i],ny=y+dy[i];
		if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&!vis[nx][ny]&&c[nx][ny]=='#')
		{
			dfs(nx,ny);
			uf.merge(get(x,y),get(nx,ny));
		}
	}
}

int dfn[5*N*N],low[5*N*N];
vector<int> NG[5*N*N];
int idx;
int stk[5*N*N],top;
vector<int> G[5*N*N];
int CC;

void tarjan(int u)
{
	dfn[u]=low[u]=++idx;
	stk[++top]=u;
	for(auto&j:G[u])
	{
		if(!dfn[j])
		{
			tarjan(j);
			low[u]=min(low[u],low[j]);
			if(low[j]==dfn[u])
			{
				CC++;
				for(int y=0;y^j;top--)
				{
					y=stk[top];
					NG[CC].emplace_back(y);
					NG[y].emplace_back(CC);
				}
				NG[u].emplace_back(CC);
				NG[CC].emplace_back(u);
			}
		}
		else low[u]=min(low[u],dfn[j]);
	}
}

signed main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	CC=n*m;
	uf.Init();
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>c[i][j];
			cnt+=(c[i][j]=='#');
		}
	}
	int cc=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int k=0;k<4;k++)
			{
				int ni=i+dx[k],nj=j+dy[k];
				if(ni>=1&&ni<=n&&nj>=1&&nj<=m&&c[i][j]=='#'&&c[ni][nj]=='#')
				{
					G[get(i,j)].emplace_back(get(ni,nj));
				}
			}
			if(c[i][j]=='#'&&!vis[i][j]) 
			{
				dfs(i,j),cc++;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(c[i][j]=='#')
			{
				if(!dfn[get(i,j)])
				{
					top=0;
					tarjan(get(i,j));
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(c[i][j]=='#')
			{
				if(!dfn[get(i,j)])
				{
					top=0;
					tarjan(get(i,j));
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(c[i][j]=='#')
			{
				int nc=cc+NG[get(i,j)].size()-1;
				ans=(ans+nc*qpow(cnt,MOD-2LL)%MOD)%MOD; 
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
}


```


---

## 作者：xz001 (赞：0)

- 我们先预处理出所有绿连通块，然后对于每个绿连通块，我们跑一遍 ```Tarjan```，求出割点以及每个割点去除后分成的连通块数量。
- 然后对于每个绿点，我们看看它是不是割点，是的话答案加上绿连通块数和会产生的连通块个数减一（本身处于一个连通块），否则答案加上绿连通块数。
- 还有一点，若这个点四周都没有绿点，那么答案加上绿连通块数后要减一（直接去除了一个连通块）。
- 最后将答案乘上绿点数的逆元，取模输出即可。

---

## 作者：harmis_yz (赞：0)

## 分析

和 T5 差不多的思路。把所有的绿色格子看做图上的点，对于将每个绿色格子变成红色时连通块增加的数量，实际上就是无向图中删掉某个点连通分量变化量的问题。

对于删掉某个点后连通分量变化量，有三种情况：

1. 节点是孤点，删掉后连通分量增加 $-1$。
2. 节点是割点，删掉后连通分量增加其所在点双数量 $-1$。
3. 节点既不是孤点也不是割点，删掉后连通分量增加 $0$。

跑 Tarjan 求割点即可，最后的期望同 T5。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

const int N=4005,p=998244353,M=7e6+10;
int n,m;
char ch[N][N];
int dx[5]={0,0,1,-1},dy[5]={1,-1,0,0};
int ne[M],e[M],h[M],idx;
int dfs_clock;
int dfn[M],low[M],cut[M];

il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il int get(int x,int y){return (x-1)*m+y;}
il int qmi(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%p;
		a=a*a%p;b>>=1;
	}
	return ans;
}
il int tj(int now,int fa){
	if(fa==-1) --cut[now];
	int nowl=dfn[now]=++dfs_clock;
	int siz=0;
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		if(!dfn[j]){
			++siz;int lowj=tj(j,now);
			nowl=min(nowl,lowj);
			if(lowj>=dfn[now]) ++cut[now];
		}
		else nowl=min(nowl,dfn[j]);
	}
	return low[now]=nowl;
}

il void solve(){
	cin>>n>>m;int cnt=0,P=0,Q=0;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		cin>>ch[i][j];
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		if(ch[i][j]=='#')
			for(re int k=0;k<4;++k){
				int nowx=i+dx[k],nowy=j+dy[k];
				if(ch[nowx][nowy]=='#') add(get(i,j),get(nowx,nowy));
			}
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		if(ch[i][j]=='#'&&!dfn[get(i,j)]) ++cnt,tj(get(i,j),-1);
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		if(ch[i][j]=='#'){
			int now=get(i,j);
			P=(P+cnt+cut[now])%p,++Q;
		}
	cout<<P*qmi(Q,p-2)%p;
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：FReQuenter (赞：0)

首先将原图建图。即相邻的绿色格子连边。

不难发现如果要使分割后连通块数量发生变化这个点一定是原图的割点。

那么只需要在求割点的时候额外记录当前点能额外产生几个连通块即可。

具体记录就是当触发一次 `dfn[u]<=low[v]` 是即满足这个点是割点一次，额外分割当前连通块一个。其余和普通的 tarjan 求割点相同。

[code。](https://atcoder.jp/contests/abc334/submissions/48792162)

---

