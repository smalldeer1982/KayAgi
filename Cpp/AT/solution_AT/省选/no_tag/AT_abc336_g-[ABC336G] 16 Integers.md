# [ABC336G] 16 Integers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc336/tasks/abc336_g

$ 16 $ 個の非負整数 $ X_{i,\ j,\ k,\ l} $ $ (i,\ j,\ k,\ l\ \in\ \lbrace\ 0,\ 1\ \rbrace) $ が $ (i,\ j,\ k,\ l) $ の昇順に与えられます。  
 また、$ N\ =\ \displaystyle\ \sum_{i=0}^1\ \sum_{j=0}^1\ \sum_{k=0}^1\ \sum_{l=0}^1\ X_{i,j,k,l} $ とします。  
 $ 0 $ または $ 1 $ からなる長さ $ N\ +\ 3 $ の数列 $ (A_1,\ A_2,\ ...,\ A_{N+3}) $ のうち、次の条件を満たすものの個数を $ 998244353 $ で割った余りを求めてください。

- 整数の $ 4 $ つ組 $ (i,\ j,\ k,\ l) $ $ (i,\ j,\ k,\ l\ \in\ \lbrace\ 0,\ 1\ \rbrace) $ 全てについて、次の条件を満たす $ 1 $ 以上 $ N $ 以下の整数 $ s $ はちょうど $ X_{i,j,k,l} $ 個存在する。
  - $ A_s\ =\ i,\ A_{s\ +\ 1}\ =\ j,\ A_{s\ +\ 2}\ =\ k,\ A_{s\ +\ 3}\ =\ l $ である。

## 说明/提示

### 制約

- $ X_{i,\ j,\ k,\ l} $ は全て非負整数
- $ 1\ \leq\ \displaystyle\ \sum_{i=0}^1\ \sum_{j=0}^1\ \sum_{k=0}^1\ \sum_{l=0}^1\ X_{i,j,k,l}\ \leq\ 10^6 $
 
### Sample Explanation 1

この入力は、 $ X_{1,\ 0,\ 1,\ 0} $ と $ X_{1,\ 1,\ 0,\ 1} $ が $ 1 $ でそれ以外は $ 0 $ であるような入力です。 このとき、条件を満たす数列は $ (1,\ 1,\ 0,\ 1,\ 0) $ の $ 1 $ 通りのみです。

## 样例 #1

### 输入

```
0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0```

### 输出

```
1```

## 样例 #2

### 输入

```
1 1 2 0 1 2 1 1 1 1 1 2 1 0 1 0```

### 输出

```
16```

## 样例 #3

### 输入

```
21 3 3 0 3 0 0 0 4 0 0 0 0 0 0 0```

### 输出

```
2024```

## 样例 #4

### 输入

```
62 67 59 58 58 69 57 66 67 50 68 65 59 64 67 61```

### 输出

```
741536606```

# 题解

## 作者：EuphoricStar (赞：11)

首先考虑只要求构造任意一个符合条件的 $a$ 怎么做。考虑建图，$(i, j, k, l)$ 向 $\forall x \in \{0, 1\}, (j, k, l, x)$ 连有向边。那么就是要求固定每个点经过次数的一条哈密顿路径。

但是哈密顿路径仍然不好处理。考虑拆点，把原来的 $(i, j, k, l)$ 看成 $(i, j, k)$ 向 $(j, k, l)$ 连有向边。那么要求固定每条边经过次数的欧拉路径。到这一步直接跑欧拉路径就行了。

考虑如何计数。考虑 BEST 定理，有向欧拉图的本质不同欧拉回路数量（循环同构视为本质相同，每条边互相区分）为：

$$T \prod\limits_{i = 1}^n (out_i - 1)!$$

其中 $T$ 为图的外向生成树个数（注意到有向欧拉图以每个点为根的外向生成树个数相等），$out_i$ 为 $i$ 点的出度。$T$ 可以用矩阵树定理求得。注意去除孤立点。

但是这题统计的是欧拉路径。考虑原图若存在一对入度小于出度和入度大于出度的点，那么以它们为起点和终点，否则枚举每个点作为起点和终点即可。从终点向起点连一条有向边就转化成了欧拉回路。

注意判一些无解的情况。

时间复杂度 $O(n^4 + \sum out_i)$，其中 $n = 8$。

[code](https://atcoder.jp/contests/abc336/submissions/49356465)

---

## 作者：born_to_sun (赞：4)

本篇题解重在解决一些**细节**问题，如果你觉得自己写的很对但是 WA，可以看看是否漏了本题解提到的细节。

### 思路
我们将原序列映射为图上的一条**路径**，图上每一个节点用三元组 $(i,j,k)(0\leq i,j,k\leq 1)$ 表示，序列中下标 $i(i\geq 3)$ 代表的节点为 $(a_{i-2},a_{i-1},a_i)$，那么这条路径会有**恰好** $n$ 条边，每一条边恰好对应了原序列的一个长为 $4$ 的连续子序列。

那么我们的目标就变为：从图上寻找一条路径，使得其经过边 $(i,j,k)\rightarrow(j,k,l)$ 的次数为 $X_{i,j,k,l}$。

这个问题可以使用 BEST 定理求解，分欧拉路径和欧拉回路两种情况统计答案即可。

**请务必理解 BEST 定理计算的结果究竟是什么。**

BEST 定理是在以下条件下算出的结果：

+ 需要实现保证图**存在**欧拉回路。

+ 所有**循环同构**的欧拉回路算作 $1$ 种。

+ 每条边（包括重边）**互不相同。**

它的公式为：
$$T\prod_{i=1}^n (deg_i-1)$$
其中 T 为**内向生成树**的个数，可以用矩阵树定理求解。

所以：

1. 需要先判断图是否存在欧拉回路。欧拉回路存在的充要条件是**图联通，且所有点入度等于出度**。这里，图联通指所有**非孤点**在一个联通块中。

具体地，使用并查集，选择任意一个度数不为 $1$ 的点作为联通块中的一个节点 $u$，然后枚举其他节点，如果这个节点与其他节点存在连边，并且它和 $u$ 不在同一个联通块中，那么无解。

2. 由于我们建出的图中每条重边**本质相同**，都代表同一个子串，所有我们需要消去它们之间的顺序产生的贡献。

具体地，设当前算出的答案为 $ans$，我们需要让
$$ans={{ans}\over{\prod x_{i,j,k,l}!}}$$

3. 如果图中存在欧拉回路，我们需要钦定一个子串作为起始边，因为这条边对应了原序列 $a_1,a_2,a_3,a_4$ 的取值。但是 BEST 定理认为这些方案循环同构，所以我们需要乘上这些贡献。

具体地，设当前算出的答案为 $ans$，我们需要让
$$ans=ans\times \sum x_{i,j,k,l}$$

4. 如果图中不存在欧拉回路，那么如果答案非 $0$，一定存在一条欧拉路径，对于欧拉路径，我们加一条由**终点向起点**的连边，那么它一定构成一条欧拉回路，据此进行求解即可。

5. 即使原图欧拉路径存在，我们不应将孤点也放入矩阵中，这样会使计算出答案为 $0$。手动移除孤点当然可行，更直接的方法是对一些算出来的值与 $1$ 取 $\max$。

具体地，在高斯消元结束后将对角线上的所有值和 $1$ 取 $\max$，在计算 $\prod_{i=1}^n (deg_i-1)$ 时，将 $deg_i$ 和 $1$ 取 $\max$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int qpow(int a,int x){
	int sum=1;
	while(x){
		if(x&1) sum=sum*a%mod;
		a=a*a%mod;
		x>>=1;
	}return sum;
}
const int N=1e6+5;
int fac[N],inv[N];
int a[20];
int ind[20],oud[20];
int b[20][20],c[20][20];
int ans;
int Gause(int n,int a[][20]){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) a[i][j]=(a[i][j]%mod+mod)%mod;
	}
	int ans=1;
	for(int i=1;i<=n;i++){
		int p=0;
		for(int j=i;j<=n;j++){
			if(a[j][i]){p=j;break;}
		}
		if(!p) continue;
		if(i!=p){swap(a[i],a[p]);ans=-ans;}
		for(int j=1;j<=n;j++){
			if(j==i) continue;
			int bs=a[j][i]*qpow(a[i][i],mod-2)%mod;
			for(int k=i;k<=n;k++){
				a[j][k]=(a[j][k]-bs*a[i][k]%mod+mod)%mod;
			}
		}
	}
	for(int i=1;i<=n;i++) ans=ans*max(1ll,a[i][i])%mod;
	return (ans%mod+mod)%mod;
}
void solve(int s){
	for(int i=s;i>=1;i--) swap(c[i],c[i-1]);
	for(int i=1;i<8;i++){
		for(int j=s;j>=1;j--) swap(c[i][j],c[i][j-1]);
	}
	int res=Gause(7,c);
	for(int i=0;i<8;i++) res=res*fac[max(0ll,ind[i]-1)]%mod;
	for(int i=0;i<16;i++) res=res*inv[a[i]]%mod;
	ans+=res;
}
int fa[20];
int find(int x){return fa[x]==x? x: fa[x]=find(fa[x]);}
int rt;
signed main(){
	for(int i=0;i<8;i++) fa[i]=i;
	fac[0]=1;
	for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	for(int s=0;s<16;s++) cin>>a[s];
	for(int s=0;s<16;s++){
		int p1=s>>1,p2=s&0b111;
		if(a[s]){
			rt=p1;
			fa[find(p1)]=find(p2);
			oud[p1]+=a[s];ind[p2]+=a[s];
			b[p1][p1]+=a[s];b[p1][p2]-=a[s];
		}
	}
	for(int i=0;i<8;i++){
		if(find(i)!=find(rt)&&(ind[i]||oud[i])){cout<<0;exit(0);}
	}
	int f0=0;
	for(int k=0;k<8;k++) f0|=ind[k]!=oud[k];
	if(!f0){
		memcpy(c,b,sizeof(b));solve(0);
		int res=ans;ans=0;
		for(int i=0;i<8;i++) ans+=res*ind[i]%mod;
	}
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){//i->j
			if(i==j) continue;
			oud[i]++;ind[j]++;
			int f0=0;
			for(int k=0;k<8;k++) f0|=ind[k]!=oud[k];
			if(!f0){
				memcpy(c,b,sizeof(b));
				c[i][i]++;c[i][j]--;
				solve(j);
			}
			oud[i]--;ind[j]--;
		}
	}
	cout<<(ans%mod+mod)%mod;
	return 0;
}
```

---

## 作者：rui_er (赞：2)

萌萌 BEST 定理练习题。赛时几乎做出来了，但写挂了，现在在火车上没事干就给补了。

考虑建图，图中共有 $8$ 个节点，节点的编号是 $(\mathbb{Z}/2\mathbb{Z})^3$ 的每个元素。对于每个四元组 $(i,j,k,l)\in(\mathbb{Z}/2\mathbb{Z})^4$，在图中连 $X_{i,j,k,l}$ 条 $(i,j,k)\to(j,k,l)$ 的有向边。显然，每个合法的数列 $\{A_i\}$ 恰好一一对应了图中的一条欧拉通路。

欧拉通路即去掉一条边的欧拉回路，对于每种可能的去掉边的方案，我们都把它连上并统计欧拉回路个数即可。边是无序的，所以需要除以一些阶乘。

```cpp
// Problem: G - 16 Integers
// Contest: AtCoder - AtCoder Beginner Contest 336
// URL: https://atcoder.jp/contests/abc336/tasks/abc336_g
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

const ll N = 1e6 + 5, mod = 998244353;

typedef Modint<mod> mint;

ll n, fac[N], a[16], q[8][8], ideg[8], odeg[8], vis[8], A[8][8], id[8];
vector<ll> e[8];

void dfs(int u) {
    vis[u] = 1;
    for(int v : e[u]) if(!vis[v]) dfs(v);
}

ll det(int m) {
	ll now = 1;
	rep(i, 1, m) {
		rep(j, i + 1, m) {
			while(A[i][i]) {
				ll mt = (mod - A[j][i] / A[i][i]) % mod;
				rep(k, i, m) A[j][k] = (A[j][k] + mt * A[i][k] % mod) % mod;
				swap(A[i], A[j]);
                now = mod - now;
			}
			swap(A[i], A[j]);
            now = mod - now;
		}
	}
	rep(i, 1, m) now = now * A[i][i] % mod;
	return now;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    rep(S, 0, 15) {
        cin >> a[S];
        n += a[S];
    }
    fac[0] = 1;
    rep(i, 1, n) fac[i] = fac[i - 1] * i % mod;
    rep(S, 0, 15) {
        ll S1 = S >> 1, S2 = S & 7;
        odeg[S1] += a[S];
        ideg[S2] += a[S];
        q[S1][S2] += a[S];
        rep(i, 1, a[S]) e[S1].push_back(S2);
    }
    mint ans = 0;
    rep(a, 0, 7) {
        rep(b, 0, 7) {
            memset(vis, 0, sizeof(vis));
            memset(A, 0, sizeof(A));
            memset(id, 0, sizeof(id));
            ++odeg[b]; ++ideg[a];
            e[b].push_back(a);
            dfs(b);
            bool ok = true;
            rep(u, 0, 7) if(ideg[u] != odeg[u] || !vis[u] && ideg[u]) ok = false;
            if(ok) {
                ll m = 0;
                rep(u, 0, 7) id[u] = -1;
                rep(u, 0, 7) if(vis[u]) id[u] = m++;
                rep(u, 0, 7) {
                    if(vis[u]) {
                        A[id[u]][id[u]] = odeg[u];
                        for(ll v : e[u]) A[id[u]][id[v]] = (A[id[u]][id[v]] - 1 + mod) % mod;
                    }
                }
                mint now = det(m - 1);
                rep(u, 0, 7) if(vis[u] && odeg[u]) now *= fac[odeg[u] - 1];
                rep(u, 0, 7) rep(v, 0, 7) now /= fac[q[u][v]];
                ans += now;
            }
            --odeg[b]; --ideg[a];
            e[b].pop_back();
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Mars_Dingdang (赞：2)

### 题目描述
$ 16 $ 个非负整数 $ X_{i,\ j,\ k,\ l} $ $ (i,\ j,\ k,\ l\ \in\ \lbrace\ 0,\ 1\ \rbrace) $ 按 $ (i,\ j,\ k,\ l) $ 的升序给出，令 $ N\ =\ \displaystyle\ \sum_{i=0}^1\ \sum_{j=0}^1\ \sum_{k=0}^1\ \sum_{l=0}^1\ X_{i,j,k,l} $。

求由 $0$ 或 $1$ 构成的长为 $ N\ +\ 3 $ 的数列 $ (A_1,\ A_2,\ ...,\ A_{N+3}) $ 中，满足以下条件的个数模 $ 998244353 $ 的余数。

- 对于任意整数 $4$ 元组 $ (i,\ j,\ k,\ l) $ $ (i,\ j,\ k,\ l\ \in\ \lbrace\ 0,\ 1\ \rbrace) $，正好存在 $ X_{i,j,k,l} $ 个整数 $s(1\le s\le N)$ 满足 $ A_s\ =\ i,\ A_{s\ +\ 1}\ =\ j,\ A_{s\ +\ 2}\ =\ k,\ A_{s\ +\ 3}\ =\ l $。

$N\le 10^6$。

### 大体思路
最近的 Codeforces 和 Atcoder 分别考察了一道有关 BEST 定理的题目。

显然我们可以将相邻四位看成一个状态，这样整张图的节点数量一共是 $2^4=16$。此时，对于状态 $(i,j,k,l)$，其后继状态可以是 $(j,k,l,0),(j,k,l,1)$，因此我们向 $(j,k,l,0)$ 和 $(j,k,l,1)$ 连边。此时我们可以感觉到，大概这题要求的是每个点有经过次数限制的欧拉路径问题。

怎么限制点的经过次数呢？在网络流中一个常用的手法是拆点。本题同样可以使用拆点，我们把 $(i,j,k,l)$ 拆成两个点，两个点之间连接 $cnt$ 条相同的有向边（$cnt$ 为该状态被经过的次数），大概长成下面这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/htz14mb8.png)

然后，对于本问题，连接 $\infty$ 条边等价于这两个点是同一个点，因此我们重新设计本题的状态：

对于 $cnt(i,j,k,l)=X$，我们在 $(i,j,k)$ 向 $(j,k,l)$ 连接 $X$ 条边。

然后等价于，我们要从这个 $|V|=2^3=8,|E|=O(N)$ 的图中找出欧拉路径的条数。参考 CF1919E，我们有以下版本的 BEST 定理，即终点为 $k$ 的欧拉回路条数为：

$$ans(k)=t^{root}(G,k)\prod_{v\in V}\dfrac{(\deg_v-[v\neq k])!}{(c_1)!(c_2)!\cdots}$$

其中 $c_1,c_2\cdots$ 表示一类相同的边的数量，本题中即为连出去的 $cnt$；$t^{root}(G,k)$ 表示图 $G$ 以 $k$ 为根的内向树的个数，可以使用矩阵树定理在 $O(n^3)$ 复杂度内求出。

对于固定起点为 $s$，终点为 $t$ 的情况（比如图中出现两个点 $in_s=out_s-1,in_t=out_t+1$），可以在 $t\to s$ 连一条边，转化为欧拉回路问题。对于终点不固定的情况，枚举所有点作为终点，此时时间复杂度为 $O(n^4+N)$，其中 $n=|V|=8$。

实现时，类似 BEST 定理的模板题，需要注意孤立点的情况，用并查集判断即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 20;
const ll mod = 998244353;
template <typename T>
inline void chkmax(T &x, T y) {x = (x > y ? x : y);}
template <typename T>
inline void chkmin(T &x, T y) {x = (x < y ? x : y);}
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
ll n, m, fa[maxn], a[maxn][maxn], b[maxn][maxn], in[maxn], out[maxn];
inline ll Pow(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res % mod;
}
ll fac[1000005], inv[1000005];
inline void init(int N) {
	fac[0] = inv[0] = 1;
	rep(i, 1, N) fac[i] = fac[i - 1] * 1ll * i % mod;
	inv[N] = Pow(fac[N], mod - 2);
	Rep(i, N - 1, 1) inv[i] = inv[i + 1] * 1ll * (i + 1) % mod;
}
inline ll Guass() {
	ll ans = 1, w = 1;
	rep(i, 1, m - 1) {
		rep(j, i + 1, m - 1) {
			while(a[j][i]) {
				ll factor = a[i][i] / a[j][i];
				rep(k, i, m - 1) a[i][k] = (a[i][k] - factor * a[j][k]) % mod;
				swap(a[i], a[j]), w = -w;
			}
		}
	}
	rep(i, 1, m - 1) if(a[i][i]) (ans *= a[i][i]) %= mod;
	return (ans * w + mod) % mod;
}
int X[maxn], rev[maxn], id[maxn];
inline int find(int u) {return u == fa[u] ? u : (fa[u] = find(fa[u]));}
inline void merge(int u, int v) {u = find(u), v = find(v); if(u != v) fa[u] = v;}
inline ll calc(int s, int t) {
	memset(a, 0, sizeof a);
	rep(i, 1, m) {
		int x = i;
		if(i == s || i == m) x ^= (s ^ m);
		a[x][x] = in[rev[i]] + (i == s);
	}
	rep(i, 1, m) {
		int x = i;
		if(i == s || i == m) x ^= (s ^ m);
		rep(j, 1, m) {
			int y = j;
			if(j == s || j == m) y ^= (s ^ m);
			a[x][y] = (a[x][y] - b[rev[i]][rev[j]] + mod) % mod;
			if(i == t && j == s) a[x][y] = (a[x][y] + mod - 1) % mod; // 额外连一条t->s的边
		}
	}
	ll ans = Guass();
	rep(i, 1, m) (ans *= fac[out[rev[i]] - (i != t)]) %= mod; // t向s连边就转化为欧拉回路问题
	return ans;
}
inline void solve() {
	rep(S, 0, 15) read(b[S >> 1][S & 7]);
	rep(i, 0, 7) fa[i] = i;
	rep(i, 0, 7) rep(j, 0, 7) if(b[i][j]) {
		out[j] += b[i][j], in[i] += b[i][j];
		merge(i, j);
	}
	int p = -1, s = -1, t = -1;
	rep(i, 0, 7) {
		if(!in[i] && !out[i]) continue;
		rev[id[i] = ++ m] = i;
		if(in[i] > out[i]) {
			if(in[i] > out[i] + 1 || t != -1) {writeln(0); return;}
			t = m;
		}
		else if(in[i] < out[i]) {
			if(in[i] < out[i] - 1 || s != -1) {writeln(0); return;}
			s = m;
		}
		if(p == -1) p = find(i);
		else if(p != find(i)) {writeln(0); return;} // 只有一个连通块
	}
//	writeln(m);
	ll ans = 0;
	if(s != -1) ans = calc(s, t);
	else rep(i, 1, m) (ans += calc(i, i)) %= mod;
	rep(i, 0, 7) rep(j, 0, 7) (ans *= inv[b[i][j]]) %= mod; // 多重集
	writeln(ans);
}
int main () {
	init(1000000);
	solve();
	
	return 0;
}
```

---

## 作者：Huasushis (赞：1)

## 解题思路

看到这道题很容易想到有一道题，就是构造长度为 $n$ 的 $01$ 串使得子串个数最多。当时那道题就是建图跑哈密顿路还有环啊之类的，启发我们这道题也在图上考虑。直接建图的话会发现限制的是每个点的经过次数，容易想到将点变成边，在 $8$ 个点的图上跑，这样每一条边对应一个串，每条边经过 $X_i$ 次。那么现在我们相当于要在上面去找欧拉路径或者欧拉回路，想到使用 BEST 定理。可以参见 [OI-WIKI](https://oi-wiki.org/graph/matrix-tree/#best-%E5%AE%9A%E7%90%86) 和洛谷[【模板】BEST 定理 | Which Dreamed It ](https://www.luogu.com.cn/problem/P5807)。

这里说一下计数问题，看了一下其它题解在每个点都是偶数度的情况下是每个点作为起点连了一个自环来算的，其实没有那么麻烦。考虑到 BEST 定理本身是没有起点的，重边是两两不同的，所以如何计数是关键。

首先我们都假设所有边都不同，那么答案一定是这样计算除以每一种相同的边的个数的阶乘的乘积。这一步去重比较容易。然后考虑两种情况：

1. 起点终点确定

我们连上起点和终点，会发现，对于每个欧拉回路，我们定位这条边的位置，就能找到起点和终点了，那么数量就相当于欧拉回路的数量。要注意，这条额外边并不算在重复边的里面，因为这条边很特殊，可以说和其它所有边都不一样。

2. 起点终点不确定

那么所有点都可以分别作为起点终点，还是在所有边都不相同的情况下考虑，一个点在环里其实有 $deg^{out}i$ 种起点选择方案，因此以 $s$ 为起点的欧拉图就有 $t^{root}(G,s)\times(deg_s)\times\prod_{u\in V}(deg_u-1)!$ 种路径（具体可以看那道模板题）。那么所有的加起来就是 $t^{root}(G,s)\times\sum_{u\in V}deg_u\times\prod_{u\in V}(deg_u-1)!$。最后还是去重就行。

**code:**

[link](https://atcoder.jp/contests/abc336/submissions/49613819)。代码写得比较丑，见谅。讲一下去除孤立点的问题。最开始我求行列式照着模板题题解里面的打法发现样例过不去，后来发现那篇题解是算的去除最后一行最后一列的行列式然后一行是 $0$ 就直接跳过不乘。但这样可能会有问题，就比如最后一个点是孤立点的话，就不对了。所以我干脆直接把非孤立点存下来跑。

注意判断不合法的情况，连通还是用并查集来来判断就行。

---

## 作者：Leasier (赞：1)

考虑把原题转化为一个图论模型：

- 令 $(i, j, k, l)$ 表示一个 $A_s = i, A_{s + 1} = j, A_{s + 2} = k, A_{s + 3} = l$。
- $(i, j, k, l)$ 向 $(j, k, l, x = 0/1)$ 连边，表示一个 $A_{s + 4} = x$。
- 答案即为这 $16$ 个点的哈密顿通路的方案数，使得恰好 $x_{i, j, k, l}$ 次经过 $(i, j, k, l)$。

套路地，我们进行点边互化：

- 令 $(i, j, k)$ 表示一个 $A_s = i, A_{s + 1} = j, A_{s + 2} = k$。
- $(i, j, k)$ 向 $(j, k, l)$ 连边，表示一个 $A_{s + 3} = l$。
- 答案即为这 $8$ 个点的欧拉通路的方案数，使得恰好 $x_{i, j, k, l}$ 次经过 $(i, j, k) \to (j, k, l)$。

枚举起点和终点后跑 BEST 定理即可。注意这里边是无序的。

代码：
```cpp
#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;

typedef struct Matrix_tag {
	int n;
	ll a[17][17];
	Matrix_tag(){
		memset(a, 0, sizeof(a));
	}
} Matrix;

const int mod = 998244353;
int x[17][17], out[17], in[17], p[17];
ll fac[1000007], inv_fac[1000007];
bool vis[17];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int n){
	fac[0] = 1;
	for (register int i = 1; i <= n; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[n] = quick_pow(fac[n], mod - 2, mod);
	for (register int i = n - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
}

void dfs(int u){
	vis[u] = true;
	for (register int i = 0; i <= 7; i++){
		if (!vis[i] && (x[u][i] > 0 || x[i][u] > 0)) dfs(i);
	}
}

inline ll det(Matrix &a, int pos){
	ll ans = 1;
	for (register int i = 1; i <= a.n; i++){
		if (i == pos) continue;
		if (a.a[i][i] == 0){
			int t = i;
			for (register int j = i + 1; j <= a.n; j++){
				if (j == pos) continue;
				if (a.a[j][i] != 0){
					t = j;
					break;
				}
			}
			if (i == t) return 0;
			ans = (mod - ans) % mod;
			swap(a.a[i], a.a[t]);
		}
		ll cur_inv = quick_pow(a.a[i][i], mod - 2, mod);
		ans = ans * a.a[i][i] % mod;
		for (register int j = i + 1; j <= a.n; j++){
			if (j == pos) continue;
			ll t = cur_inv * a.a[j][i] % mod;
			for (register int k = i; k <= a.n; k++){
				if (k == pos) continue;
				a.a[j][k] = ((a.a[j][k] - t * a.a[i][k] % mod) % mod + mod) % mod;
			}
		}
	}
	return ans;
}

int main(){
	int m = 0;
	ll ans = 0;
	for (register int i = 0; i <= 1; i++){
		for (register int j = 0; j <= 1; j++){
			for (register int k = 0; k <= 1; k++){
				int u = (i << 2) | (j << 1) | k;
				for (register int l = 0; l <= 1; l++){
					int v = (j << 2) | (k << 1) | l;
					cin >> x[u][v];
					out[u] += x[u][v];
					in[v] += x[u][v];
				}
			}
		}
	}
	for (register int i = 0; i <= 7; i++){
		m = max(m, in[i]);
	}
	for (register int i = 0; i <= 7; i++){
		for (register int j = 0; j <= 7; j++){
			m = max(m, x[i][j]);
		}
	}
	init(m);
	for (register int i = 0; i <= 7; i++){
		for (register int j = 0; j <= 7; j++){
			bool flag = true;
			x[j][i]++;
			out[j]++;
			in[i]++;
			for (register int k = 0; k <= 7; k++){
				if (in[k] != out[k]){
					flag = false;
					break;
				}
			}
			if (flag){
				int cnt = 0;
				for (register int k = 0; k <= 7; k++){
					if (in[k] > 0 || out[k] > 0) p[++cnt] = k;
				}
				for (register int k = 1; k <= cnt; k++){
					vis[p[k]] = false;
				}
				dfs(p[1]);
				for (register int k = 1; k <= cnt; k++){
					if (!vis[p[k]]){
						flag = false;
						break;
					}
				}
				if (flag){
					ll prod = 1;
					Matrix a;
					a.n = cnt;
					for (register int k = 1; k <= cnt; k++){
						prod = prod * fac[in[p[k]] - 1] % mod;
					}
					for (register int k = 1; k <= cnt; k++){
						for (register int l = 1; l <= cnt; l++){
							prod = prod * inv_fac[x[p[k]][p[l]] - (p[k] == j && p[l] == i ? 1 : 0)] % mod;
							a.a[k][l] = (mod - x[p[k]][p[l]]) % mod;
						}
						a.a[k][k] = (a.a[k][k] + out[p[k]]) % mod;
					}
					ans = (ans + det(a, 1) * prod % mod) % mod;
				}
			}
			x[j][i]--;
			out[j]--;
			in[i]--;
		}
	}
	cout << ans;
	return 0;
}
```

---

