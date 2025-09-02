# Lattice Optimizing

## 题目描述

考虑一个具有 
$n$ 行和 
$n$ 列的网格图。

对于所有 $x < n$ 的位置有一个权值  $d_{x,y}$

对于所有 $y < n$ 的位置有一个权值 
$r_{x,y}$

从 $(1,1)$ 开始走，每次往下或往右走，最终到 $(n,n)$。

初始有一个空集合 $S$。若从 $(x,y)$ 走到 $(x+1,y)$，将 $d_{x,y}$ 加入 $S$；走到 $(x,y+1)$ 就加入 $r_{x,y}$。

需要最大化走到终点时的 $mex(S)$

其中，$mex(x)$ 定义为 $x$ 中最小未出现的 **非负整数**。

## 样例 #1

### 输入

```
2
3
1 0 2
0 1 3
2 1
0 3
3 0
3
1 2 0
0 1 2
2 0
1 2
0 1```

### 输出

```
3
2```

## 样例 #2

### 输入

```
1
10
16 7 3 15 9 17 1 15 9 0
4 3 1 12 13 10 10 14 6 12
3 1 3 9 5 16 0 12 7 12
11 4 8 7 13 7 15 13 9 2
2 3 9 9 4 12 17 7 10 15
10 6 15 17 13 6 15 9 4 9
13 3 3 14 1 2 10 10 12 16
8 2 9 13 18 7 1 6 2 6
15 12 2 6 0 0 13 3 7 17
7 3 17 17 10 15 12 14 15
4 3 3 17 3 13 11 16 6
16 17 7 7 12 5 2 4 10
18 9 9 3 5 9 1 16 7
1 0 4 2 10 10 12 2 1
4 14 15 16 15 5 8 4 18
7 18 10 11 2 0 14 8 18
2 17 6 0 9 6 13 5 11
5 15 7 11 6 3 17 14 5
1 3 16 16 13 1 0 13 11```

### 输出

```
14```

# 题解

## 作者：lowbit (赞：2)

答案等价于从左上到右下能到达的所有二进制状态里面，最小的没出现过的 bit。

**考虑折半搜素。** 从左上往右下走 $k$ 步，记录所有的二进制状态。然后再从右下往左上走 $2n−1−k$ 步，记录所有的二进制状态。

合并过程使用子集枚举，总复杂度是 $O(\max{3^k, 2^{2n-1-k}})$ 的。取 $k=13$ 时较平衡，可以通过。

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF2002G)

**题目大意**

> 给定 $n\times n$ 网格，边带权，定义路径权值为经过的边权 $\mathrm{mex}$，求从左上走到右下的格路的最大权值。
>
> 数据范围：$n\le 20$。

**思路分析**

很显然无法优化维护 $\mathrm{mex}(S)$ 的过程，必须爆搜，因此需要 Meet-in-Middle 平衡复杂度。

那么思路就是选取一条副对角线，每条路径恰好过其中一个点，爆搜出从起点 / 终点到对角线上每个点的路径对应的权值集合。

求答案是否 $\ge k$ 相当于判断交点两侧路径权值集合进行 $\mathrm{OR}$ 卷积后，是否有元素包含二进制位 $0\sim k-1$。

无法用 FWT 处理 $\mathrm{OR}$ 卷积状物，因此必须在一侧枚举子集。

那么设这条副对角线在 $x+y=k$ 上，那么左侧枚举子集并插入哈希表，右侧每条格路直接在哈希表中查值即可判定答案是否 $\ge k$，如果满足就更新 $k\gets k+1$ 继续判断。

时间复杂度 $\mathcal O(n(3^k+2^{2n-k}))$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct HshT {
	static const int MAXN=(1<<26)+5,P=3e7+1;
	int sz,hd[P],to[MAXN];
	ll w[MAXN];
	void ins(ll x) {
		int p=x%P;
		for(int i=hd[p];i;i=to[i]) if(w[i]==x) return ;
		w[++sz]=x,to[sz]=hd[p],hd[p]=sz;
	}
	bool qry(ll x) {
		int p=x%P;
		for(int i=hd[p];i;i=to[i]) if(w[i]==x) return true;
		return false;
	}
	void init() {
		for(int i=1;i<=sz;++i) hd[w[i]%P]=0,to[i]=w[i]=0;
		sz=0;
	}
}	H;
int n,k,z,a[45][45],b[45][45];
const ll B=1ll<<40;
void dfs(int x,int y,ll s) {
	if(x+y==k+2) {
		while(H.qry((x*B)|(((1ll<<z)-1)&(~s)))) ++z;
		return ;
	}
	if(x>1) dfs(x-1,y,s|1ll<<a[x-1][y]);
	if(y>1) dfs(x,y-1,s|1ll<<b[x][y-1]);
}
void solve() {
	scanf("%d",&n),H.init(),z=1;
	for(int i=1;i<n;++i) for(int j=1;j<=n;++j) scanf("%d",&a[i][j]);
	for(int i=1;i<=n;++i) for(int j=1;j<n;++j) scanf("%d",&b[i][j]);
	k=2*(n-1)/3;
	for(int p=0;p<(1<<k);++p) {
		int i=1,j=1; ll s=0;
		for(int o=0;o<k;++o) {
			if(p>>o&1) s|=1ll<<a[i++][j];
			else s|=1ll<<b[i][j++];
		}
		for(ll t=s;;t=(t-1)&s) {
			H.ins((i*B)|t);
			if(!t) break;
		}
	}
	dfs(n,n,0);
	printf("%d\n",z-1);
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Gordon_Song (赞：1)

首先有一种很暴力的做法，直接 dfs 枚举。

然而这么做是不优的，考虑折半搜索。

然而合并两个 mex 的信息极其困难（几乎不可能），所以只能使用一些玄学做法。

搜索左上部分时，将所有结果的所有子集的状态都存起来（由于 $d$，$r$ 都很小所以直接状压），搜索下半部分的时候查询是否存在对应的补集即可，可以用哈希表维护是否存在。

看上去这个折半搜索的复杂度是 $2 ^{2n} + 2^n$。但是转念一想，可以调整对应的阈值。假设阈值为 $x+y=k$，那么复杂度是 $2^{2k} + 2^{2n-k}$。当 $k$ 取 $\frac{2n}{3}$ 时此式取得最小值 $2^{\frac{4n}{3}}$。

---

## 作者：Arghariza (赞：0)

这纯诈骗吧。

考虑 meed in the middle，状压一下路径上出现的权值。那么我们枚举右半边路径 $R$，跑到对角线上的时候从小到大枚举答案 $x$，需要知道左半边是否存在某一个路径的权值为 $w(R)$ 的补集只取 $1\sim x-1$ 的前缀的超集。

使用哈希表记录左半边路径的权值的所有子集，枚举 $x$ 也不用从 $0$ 开始枚举而是从当前求出的最大答案开始，复杂度为 $O(2^{2n}+2^n)$ 的。平衡一下，左半边只走 $B$ 步，复杂度为 $O(2^{2B}+2^{2n-B})$，取 $B=\frac{2n}{3}$ 即可。

如果被卡常了可以发动一下脑子，比如用 dfs 代替二进制枚举，这样的话大的那边的路径数是跑不满的，就能快很多。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define R(i, x, y) for (int i = (x); i >= (y); i--)
#define FIO(FILE) freopen(FILE".in", "r", stdin), freopen(FILE".out", "w", stdout)

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

const int N = 25;
const int P = 1e7 + 7;
const int M = (1 << 26) + 5;

int n, B;
int r[N][N], d[N][N];

struct Hash {
	
	int tot, cnt;
	int hd[P], p[P], nxt[M];
	ll to[M];
	
	void clear() {
		F (i, 1, cnt) {
			hd[p[i]] = 0;
		}
		F (i, 1, tot) {
			nxt[i] = 0;
		}
		tot = 0;
	}
	
	void i(ll x) {
		int u = x % P;
		if (!hd[u]) {
			p[++cnt] = u;
		}
		for (int i = hd[u]; i; i = nxt[i]) {
			if (to[i] == x) {
				return;
			}
		}
		tot++;
		nxt[tot] = hd[u];
		to[tot] = x;
		hd[u] = tot;
	}
	
	bool q(ll x) {
		int u = x % P;
		for (int i = hd[u]; i; i = nxt[i]) {
			if (to[i] == x) {
				return 1;
			}
		}
		return 0;
	}
	
};

Hash S;

ll val(int x, ll s) {
	return ((ll)x << 40) | s;
}

void solve() {
	cin >> n, B = 2 * n / 3;
	F (i, 0, n - 2) {
		F (j, 0, n - 1) {
			cin >> d[i][j];
		}
	}
	F (i, 0, n - 1) {
		F (j, 0, n - 2) {
			cin >> r[i][j];
		}
	}
	S.clear();
	F (i, 0, (1 << B) - 1) {
		int x, y;
		ll s;
		x = y = s = 0;
		F (j, 0, B - 1) {
			if ((i >> j) & 1) {
				s |= (1ll << d[x][y]);
				x++;
			} else {
				s |= (1ll << r[x][y]);
				y++;
			}
		}
		for (ll t = s; ; t = (t - 1) & s) {
			S.i(val(x, t));
			if (!t) {
				break;
			}
		}
	}
	int res = 1;
	ll U = 1;
	auto dfs = [&](auto dfs, int x, int y, ll s) -> void {
		if (x + y == B) {
			while (res <= 2 * n - 1 && S.q(val(x, U ^ (U & s)))) {
				res++;
				U = (1ll << res) - 1;
			}
			return;
		}
		if (x) {
			dfs(dfs, x - 1, y, s | (1ll << d[x - 1][y]));
		} 
		if (y) {
			dfs(dfs, x, y - 1, s | (1ll << r[x][y - 1]));
		}
	};
	dfs(dfs, n - 1, n - 1, 0);
	cout << res - 1 << '\n';
}

bool Med;
int main() {
	// FIO("");
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	int T = 1;
	cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：xwh_Marvelous (赞：0)

很有创意的 meet-in-mid 题。

把 mex 丢图上非常难做，只剩搜索。

直接搜大概是 $O(2^{2n})$，考虑折半。

发现要做集合有交并，这很困难。

如果是无交并就可以视实现做到 $O(1)-O(\log)$ 级别。

这提示我们暴力枚举一边的子集，插入一个表里。

此时发现搜索两边的复杂度不一样了，考虑平衡一下。

设要枚举子集那边做 $B$ 步，另一半就是 $2n-B$。

那么复杂度即为 $O(2^{2B}+2^{2n-B})$。

手模一下发现 $B$ 取 $\frac 2 3 n$ 最优。

ed.


```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define N 22
using namespace std;
int n,t;
int d[N][N],r[N][N];
int ans;
int tot;
int x[1<<26];
signed nt[1<<26];
struct opssw{
	signed hd[1<<21];
	int hsh(int x){
		int p=((x^(x>>11))^(x>>25)^(x<<1)^(x>>9))&((1<<21)-1);
		return p;
	}
	queue<int>q;
	void clear(){while(q.size())hd[q.front()]=0,q.pop();tot=0;}
	void insert(int xx){
		int op=hsh(xx);
		int k=hd[op];
		if(!hd[op])q.push(op);
		while(k){
			if(x[k]==xx)return;
			k=nt[k];
		}
		tot++;
		nt[tot]=hd[op];
		x[tot]=xx;
		hd[op]=tot;
	}
	bool count(int xx){
		int op=hsh(xx);
		int k=hd[op];
		while(k){
			if(x[k]==xx)return 1;
			k=nt[k];
		}
		return 0;
	}
}qwq[N];
int p;
void dfs1(int x,int y,int z){
	if(x<1||y<1)return;
	if(x-1+y-1==p){
		for(int k=z;k>0;k=((k-1)&z)){
			qwq[x].insert(k);
		}
		return;
	}
	dfs1(x-1,y,z|(1ll<<d[x-1][y]));
	dfs1(x,y-1,z|(1ll<<r[x][y-1]));
}
void dfs2(int x,int y,int z){
	if(x>n||y>n)return;
	if(x+y-2==p){
		// cout<<bitset<5>(z)<<endl;
		while(qwq[x].count(((1ll<<(ans+1))-1)&(~z)))ans++;
		return;
	}
	dfs2(x+1,y,z|(1ll<<d[x][y]));
	dfs2(x,y+1,z|(1ll<<r[x][y]));
}
void work(){
	for(int i=1;i<=20;i++)qwq[i].clear();
	p=n*4/3;
	// p=3;
	ans=0;
	dfs1(n,n,0);
	for(int i=1;i<=n;i++)qwq[i].insert(0);
	dfs2(1,1,0);
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<n;i++){
			for(int j=1;j<=n;j++){
				cin>>d[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<n;j++){
				cin>>r[i][j];
			}
		}
		work();
	}
	return  0;
}
```

---

