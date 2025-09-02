# [ARC171C] Swap on Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc171/tasks/arc171_c

頂点に $ 1 $ から $ N $ までの番号がついた $ N $ 頂点の木があります。$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結んでいます。  
 また、$ 1 $ から $ N $ までの番号がついた $ N $ 個の駒があります。はじめ駒 $ i $ は頂点 $ i $ に置かれています。  
 あなたは次の操作を $ 0 $ 回以上好きな回数行うことができます。

- 辺を $ 1 $ 本選ぶ。辺の両端点を頂点 $ u,\ v $ として、頂点 $ u $ に載っている駒と頂点 $ v $ に載っている駒を入れ替える。その後、選んだ辺を削除する。
 
頂点 $ i $ に載っている駒を $ a_i $ とします。操作を全て終了した時点における数列 $ (a_1,\ a_2,\ \dots,\ a_N) $ としてあり得るものは何個ありますか？答えを $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ u_i\ \lt\ v_i\ \leq\ N $
- 入力で与えられるグラフは木
 
### Sample Explanation 1

例えば以下の手順により $ (a_1,\ a_2,\ a_3)\ =\ (2,\ 1,\ 3) $ を得ることが出来ます。 - $ 1 $ 番目の辺を選び、頂点 $ 1 $ と頂点 $ 2 $ に載っている駒を入れ替えて辺を削除する。$ (a_1,\ a_2,\ a_3)\ =\ (2,\ 1,\ 3) $ になる。 - 操作を終了する。 また、以下の手順により $ (a_1,\ a_2,\ a_3)\ =\ (3,\ 1,\ 2) $ を得ることが出来ます。 - $ 2 $ 番目の辺を選び、頂点 $ 2 $ と頂点 $ 3 $ に載っている駒を入れ替えて辺を削除する。$ (a_1,\ a_2,\ a_3)\ =\ (1,\ 3,\ 2) $ になる。 - $ 1 $ 番目の辺を選び、頂点 $ 1 $ と頂点 $ 2 $ に載っている駒を入れ替えて辺を削除する。$ (a_1,\ a_2,\ a_3)\ =\ (3,\ 1,\ 2) $ になる。 - 操作を終了する。 操作によって得られる数列は次の $ 5 $ 通りです。 - $ (1,\ 2,\ 3) $ - $ (1,\ 3,\ 2) $ - $ (2,\ 1,\ 3) $ - $ (2,\ 3,\ 1) $ - $ (3,\ 1,\ 2) $

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
5```

## 样例 #2

### 输入

```
5
2 5
3 4
1 3
1 5```

### 输出

```
34```

## 样例 #3

### 输入

```
8
4 5
2 5
3 6
1 3
1 8
2 7
2 8```

### 输出

```
799```

# 题解

## 作者：rui_er (赞：17)

每棵子树内只可能有至多一个外来的数，且外来的数是多少并不影响方案数，因此考虑设 $f_{u,i,0/1}$ 表示考虑以 $u$ 为根的子树，与 $u$ 相连的所有边中断了 $i$ 条，且 $u$ 与其父亲之间的边有没有断的方案数。设 $g_{u,c}=\sum f_{u,i,c}$。

每个节点的初始状态是 $f_{u,0,0}=1,f_{u,1,1}=[u\ne 1]$。

枚举 $u$ 的每个儿子 $v$，进行如下转移：

$$
\begin{aligned}
f'_{u,i,0}&\gets f_{u,i,0}\times g_{v,0}+[i>0]\times f_{u,i-1,0}\times i\times g_{v,1}\\
f'_{u,i,1}&\gets f_{u,i,1}\times g_{v,0}+[i>0]\times f_{u,i-1,1}\times i\times g_{v,1}
\end{aligned}
$$

其中两个转移式的前一项代表不断 $(u,v)$ 这条边，后一项代表断 $(u,v)$ 这条边，乘以 $i$ 是为了确定与 $u$ 相连的 $i$ 条边的断边顺序。

时间复杂度 $O(n^2)$。上文 $f,g,f'$ 分别对应代码中的 $\textrm{dp},\textrm{sum},\textrm{tmp}$。

```cpp
// Problem: C - Swap on Tree
// Contest: AtCoder - AtCoder Regular Contest 171
// URL: https://atcoder.jp/contests/arc171/tasks/arc171_c
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

const int N = 3e3 + 5;

typedef Modint<998244353> mint;

int n;
mint dp[N][N][2], tmp[N][2], sum[N][2];
vector<int> e[N];

void dfs(int u, int fa) {
	dp[u][0][0] = 1;
	int deg = 0;
	if(fa) {
		dp[u][1][1] = 1;
		++deg;
	}
	for(int v : e[u]) {
		if(v != fa) {
			dfs(v, u);
			++deg;
			rep(i, 0, deg) {
				tmp[i][0] = dp[u][i][0];
				tmp[i][1] = dp[u][i][1];
				dp[u][i][0] = dp[u][i][1] = 0;
			}
			rep(i, 0, deg) {
				dp[u][i][0] += tmp[i][0] * sum[v][0];
				dp[u][i][1] += tmp[i][1] * sum[v][0];
				if(i > 0) {
					dp[u][i][0] += tmp[i - 1][0] * i * sum[v][1];
					dp[u][i][1] += tmp[i - 1][1] * i * sum[v][1];
				}
			}
		}
	}
	rep(i, 0, deg) {
		sum[u][0] += dp[u][i][0];
		sum[u][1] += dp[u][i][1];
	}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 1, n - 1) {
    	int u, v;
    	cin >> u >> v;
    	e[u].push_back(v);
    	e[v].push_back(u);
    }
    dfs(1, 0);
    cout << sum[1][0] << endl;
    return 0;
}
```

---

## 作者：Demeanor_Roy (赞：11)

- [原题链接](https://www.luogu.com.cn/problem/AT_arc171_c)

------------

果然还是太菜了吗。

**断言一：对于两轮操作，所得 $a$ 序列相同的一个必要条件是被操作的边所构成的集合相同。**

证明不妨考虑任意一条只在一轮操作中被操作的边，由它连接的树上两个联通块只在一轮中发生过 $a$ 的交换，故 $a$ 序列肯定不同。

固定被操作的边集，令其为 $E$。

**断言二：固定边集后，对于两轮操作，所得 $a$ 序列相同的充要条件是对于任意点 $u$，其在 $E$ 中的所有邻边被操作的相对顺序相同。**

先证明必要性。反证，假设点 $u$ 不满足条件，由它划分出的若干个联通块之间产生的点的轮换肯定不同，故 $a$ 序列肯定不同。

再考虑充分性。不妨用归纳法，对 $\vert E \vert$ 进行归纳。显然当 $\vert E \vert=0$ 时结论成立。假设当 $\vert E \vert=x$ 时结论成立，我们考虑证明 $\vert E \vert=x+1$ 时结论也成立。

考其中一轮操作中最后操作的边 $(u,v)$，删去这条边后，由于 $\vert E \vert = x$，故两轮操作所得 $a$ 一定相同。由于对于点 $u$ 和点 $v$，其邻边在两轮操作中的相对顺序都相同，故对于两轮操作来说，加上边 $(u,v)$ 的效果都是交换 $a_u$ 和 $a_v$。故所得 $a$ 序列相同，充分性得证。

故可得 $a$ 序列的数量，可以表示为 

$$\sum_{E}{\prod_{u}deg_{E,u}!}$$

可以用树形 dp 在 $O(n^2)$ 的时间内求得。

[代码](https://atcoder.jp/contests/arc171/submissions/50027288)



---

## 作者：TLE_Automat (赞：4)


## 题目链接

[https://atcoder.jp/contests/arc171/tasks/arc171_c](https://atcoder.jp/contests/arc171/tasks/arc171_c)

## 题目大意

给定一颗 $N$ 个节点的树，初始时编号为 $i$ 的物品放在编号为 $i$ 的节点上。

你可以进行以下操作任意多次（可以为 $0$ 次）：

- 选择一条未被删除的边，假设这条边的两个端点编号分别为 $u,v$，交换节点 $u, v$ 上的物品，并且将这条边删除。

设 $a_i$ 为最终编号为 $i$ 的节点上的物品编号，那么通过上述操作能形成多少种不同的序列 $(a_1, a_2, \dots, a_n)$，答案对 $998244353$ 取模。

## 数据范围

- $1\le N \le 3\times 10^{3}$

## 解题思路

首先，如果选择的边集不同，那么最终的结果序列一定不同；如果选择的边集相同，那么最终的结果序列有可能相同，也有可能不同。

先从最简单的菊花图的形状开始考虑，假设中间一个节点周围连接了 $deg$ 个节点，容易发现，最终结果序列相同，当且仅当两种选法选边的顺序是一致的，总共能得到 $deg!$ 种结果序列。

那如果是以 $u$ 和 $v$ 为中心的两个菊花中间用一条边连接起来呢？那么最终结果序列相同，当且仅当两种选法中 $u$ 连接的边选择顺序相同，且 $v$ 连接的边的选择顺序相同，总共能得到 $deg_u! \times deg_{v}!$ 种结果序列。

由于一棵树就是一堆小的菊花图连接起来的，所以上面的结论可以推广到整棵树上。即最终结果序列 $(a_1, a_2, \dots, a_n)$ 相同，当且仅当两种选法分别对于树的每个节点 $u$ 连接的边的选择顺序相同。

有了以上结论，假设最终选择的边集为 $S$，对于树上的每个节点 $u$ 统计度数 $deg_u$，那么 $S$ 对答案的贡献为 $\displaystyle\prod_{i = 1}^{n} deg_i$。  

考虑树形 dp 统计贡献，设 $f_{u, i}$ 代表以 $u$ 为根的子树中，连接 $u$ 与 $u$ 的儿子的边总共选了 $i$ 条，对答案的总贡献。设 $g_{u, 0/1}$ 代表连接 $u$ 和 $u$ 的父亲的边是否选了对答案的总贡献。

枚举 $u$ 的儿子 $v$ 时，有转移 $f_{u, i} \leftarrow f_{u, i - 1} \times g_{v, 1}$，$f_{u, i} \leftarrow f_{u, i} \times g_{v, 0}$，$g_{u, 0} = \sum f_{u, i} \times i!$，$g_{u, 1} = \sum f_{u, i} \times (i + 1)!$。

最终答案为 $g_{1, 0}$（假设整棵树以节点 $1$ 为根）。

## 参考代码

[https://atcoder.jp/contests/arc171/submissions/50056781](https://atcoder.jp/contests/arc171/submissions/50056781)

---

## 作者：WrongAnswer_90 (赞：3)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18396740)

### [[ARC171C] Swap on Tree](https://www.luogu.com.cn/problem/AT_arc171_c)

科技改变生活。以 6ms 的速度拿下了目前最优解（

如果已经确定了 $u$ 的一个儿子 $v$ 内部的操作顺序，考虑在某个时刻交换 $(u,v)$。设 $a[1,k]$ 是操作 $v$ 子树内部时 $v$ 上面的颜色，可以发现在第 $i$ 个时刻交换和在第 $j$ 个时刻交换，方案本质不同的充要条件是 $a_i\not= a_j$。

考虑 $i$ 和 $i$ 的所有儿子，如果选择了 $S$ 作为要与 $i$ 交换的子树集合，则权值是 $|S|!\prod_{i\in S}(\sum_j jf_{i,j})\prod_{i\notin S}(\sum_j f_{i,j})$，其中 $f_{i,j}$ 表示 $i$ 子树内颜色改变次数是 $j$ 的方案数。$|S|!$ 是因为在确定 $i$ 和集合内所有点的操作顺序，$jf_{i,j}$ 是因为对于在集合里的点有颜色切换次数个本质不同的交换方案。

暴力做是 $\mathcal O(n^2)$ 的。设 $g_{i,0}=\sum_i f_{x,i},g_{i,1}=\sum_i if_{x,i}$。设多项式 $F_u(x)=g_{u,0}+g_{u,1}x$，则 $f_{u,k+1}$ 即为 $k![x^k]\prod_{v\in\text{son}(u)}F_v(x)$。

注意到要乘的多项式的总个数是 $\mathcal O(n)$ 的，所以可以用你喜欢的方法比如分治 NTT 或者先 ln 再 exp 做到 $\mathcal O(n\log^2 n)$ 或者 $\mathcal O(n\log n)$。

```cpp
int n,fr[200010],g[200010][2];
vi T[200010];
vp F;
vi solve(int l,int r)
{
	if(l==r)return {F[l].fi,F[l].se};
	int mid=(l+r)>>1;
	return FFT(solve(l,mid),solve(mid+1,r));
}
void dfs(int x,int fa=0)
{
	for(auto to:T[x])if(to!=fa)dfs(to,x);
	F.clear();
	for(auto to:T[x])if(to!=fa)F.eb(mp(g[to][0],g[to][1]));
	if(F.empty())return g[x][0]=g[x][1]=1,void();
	vi ve=solve(0,F.size()-1);
	for(int i=1;i<=ve.size();++i)Mmul(ve[i-1],fr[i-1]),Madd(g[x][1],Cmul(ve[i-1],i)),Madd(g[x][0],ve[i-1]);
}
inline void mian()
{
	read(n),init(),fr[0]=1;int x,y;
	for(int i=1;i<=n;++i)fr[i]=Cmul(fr[i-1],i);
	for(int i=1;i<n;++i)read(x,y),T[x].eb(y),T[y].eb(x);
	dfs(1),write(g[1][0]);
}
```

---

## 作者：Union_Find (赞：2)

~~为什么一道蓝也能卡住我呀！！！~~

本题解主要讲解思考过程。

首先看完题目，分析一下，大概率是 dp，且 $n\le  3000$，所以应该是 $O(n^2)$ 的状态。但状态是什么呢？

我们发现，因为互换之后边会断掉，所以最多只有一个数字从外面进来子树，且我们发现，对于一个子树，只要结构没变，答案是不会变化的，也就是说，进来的是什么数字不影响答案。

那什么会影响答案呢？很容易发现，只有互换的顺序影响答案，也就是插入的顺序。如果我们确定 $u$ 和 $v$ 要互换，我们就要考虑什么时候换。

如果说我们确定 $u$ 要和 $cnt$ 个数互换，添加了一个要互换的数，即 $cnt$ 多了 $1$，那么这一数可以在前面 $cnt$ 个数的空隙中任选一个，且形成的答案都不一样。

很快想到一个 dp。设 $f_{u,i}$ 表示 $u$ 这个点已经确定和 $i$ 个子树互换的方案数。

但是这样子有一个问题，我们可能要和父亲互换，与父亲互换的也算作一个 $cnt$，会影响答案，所以给 dp 加一维，$f_{u,i,0/1}$ 表示 $u$ 这个点已经确定和 $i$ 个子树互换，是否和父亲互换的方案数。为了方便转移，设 $s_{u,0/1}$ 表示 $\sum f_{u,0/1}$，并使用滚动数组优化，为了表示方便，下文用 $h$ 数组表示滚动数组上一位。转移如下。

$$f_{u,i-1,0} = h_{u,i-1,0} \times s_{v,0} + [i > 0] \times h_{u,i-1,0} \times i \times s_{v,1}$$

$$f_{u,i-1,1} = h_{u,i-1,1} \times s_{v,0} + [i > 0] \times h_{u,i-1,1} \times i \times s_{v,1}$$

两个式子几乎一样，但是初始化不同，$f_{u,0,0} = 1$，且当 $u \not = 1$ 时 $f_{u,1,1} = 1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 3005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}const ll P = 998244353;
ll n, u, v, f[N][N][2], s[N][2];
vector <ll> e[N];
void dfs(ll u, ll fa){
	f[u][0][0] = 1;
	if (u != 1) f[u][1][1] = 1;
	ll cnt = (u != 1);
	for (int v : e[u]){
		if (v == fa) continue;
		dfs(v, u);
		cnt++;
		for (int i = cnt; i >= 0; i--){
			f[u][i][0] = f[u][i][0] * s[v][0] % P,
			f[u][i][1] = f[u][i][1] * s[v][0] % P;
			if (i > 0)
				f[u][i][0] = (f[u][i][0] + f[u][i - 1][0] * i % P * s[v][1] % P) % P,
				f[u][i][1] = (f[u][i][1] + f[u][i - 1][1] * i % P * s[v][1] % P) % P;
		}
	}for (int i = 0; i <= cnt; i++)
		s[u][0] = (s[u][0] + f[u][i][0]) % P, s[u][1] = (s[u][1] + f[u][i][1]) % P;
}
int main(){
	n = rd();
	for (int i = 1; i < n; i++) u = rd(), v = rd(), e[u].push_back(v), e[v].push_back(u);
	dfs(1, 0);
	printf ("%lld\n", s[1][0]);
	return 0;
}

```

---

## 作者：littlebug (赞：1)

好厉害的数数题 ww

## Solution

首先有结论，一个子树最多从外面进来一个点，因为边用过了就断了；然后进来的是什么点显然是不影响方案数的，虽然这里可能子树内哪个点换出去不一定，但是无论和外面哪个点换，方案数还是都是固定的。

那么对应固定的边集，影响方案数的只有操作顺序。

于是就可以这么 dp 了。状态设计可以这么考虑，显然操作顺序不好枚举，于是考虑枚举边集，放到 dp 状态里就可以转化为枚举边数，然后类似背包做转移。

但是发现是否删连向父亲的那条边是影响转移的，于是再加一维 $0/1$。

转移考虑当前边是否删，以及如果删掉后插到前面操作序列的哪个位置，乘法原理即可。设 $s_{u,0/1} = \sum \limits _i f_{u,i,0/1}$，有方程：

$$
f_{u,i,0} = f_{u,i,0} \times s_{v,0} + f_{u,i-1,0} \times i \times s_{v,1} \\
f_{u,i,1} = f_{u,i,1} \times s_{v,0} + f_{u,i-1,1} \times i \times s_{v,1}
$$

## Code

```cpp
int n,f[N][N][2],s[N][2];
vector <int> p[N];

il void dfs(int u,int ufa)
{
	f[u][0][0]=1,f[u][1][1]=u>1;
	int tot=u>1;
	
	for(auto v:p[u]) if(v!=ufa)
	{
		dfs(v,u);
		++tot;
		
		rpe(i,tot,0)
		{
			f[u][i][0]=mod_(f[u][i][0]*s[v][0]+(i?mod_(f[u][i-1][0]*s[v][1])*i:0ll));
			f[u][i][1]=mod_(f[u][i][1]*s[v][0]+(i?mod_(f[u][i-1][1]*s[v][1])*i:0ll));
		}
	}
	
	rep(i,0,tot) add(s[u][0],f[u][i][0]),add(s[u][1],f[u][i][1]);
}

signed main()
{
	read(n),_::r(p,n-1,false);
	
	dfs(1,0);
	write(s[1][0]);
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：Acoipp (赞：1)

## 题意

有一棵 $n$ 个节点的树，每个节点有一个权值 $i$（就是它的编号），每次你可以选择一条边，删去这条边，然后交换这条边两端节点的权值。

问最后权值数组有多少种不同的形态，$n \le 3000$。

## 分析

首先有一个不太美妙的做法，假如第一次选择了 $u \to v$ 这条边，那么会交换 $u,v$ 的权值，树就会分裂成两个等价类，这让我们发现如果两组方案中用到的边不全相同，最后的序列一定不相同。

然后考虑用到的边相同，序列也相同的情况。

- 结论：如果连向一个点的边的相对使用顺序相同，那么最后生成的序列也相同。

这个结论可以稍微感性理解一下，设权值 $i$ 最后到了节点 $j$ 上，我们可以画出来一条 $i \to j$ 的路径，注意到路径上的边一定是顺次使用的；当然路径可能不止一条，对于每条路径都分开去想这个结论还是比较显然的。

当然笔者太菜了，考场上没想出来这个结论。

最后就是统计方案，因为只要相对使用顺序相同，最后生成的序列也相同，对于每个节点连出去的边，只要随意排列顺序，总能获得一组合法的解。

因此，如果节点 $u$ 连出去了 $d_u$ 条边，那么答案就是 $d_u!$，所以任意一组选边方案的代价就是 $\prod_{u} d_u!$，最后 dp 出所有选边方案的代价就行了。

dp 的过程并不难，此处不再赘述。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 3005
#define mod 998244353
using namespace std;
vector<ll> op[N];
ll n,x,y,i,f[N][N],g[N],ans;
void dfs(ll x,ll fa){
	f[x][0] = 1;
	for(ll i=0;i<op[x].size();i++){
		if(op[x][i]==fa) continue;
		dfs(op[x][i],x);
		for(ll j=0;j<=i+1;j++) g[j]=0;
		for(ll j=0;j<=i;j++){
			for(ll k=0;k<=op[op[x][i]].size();k++){
				g[j]=(g[j]+f[x][j]*f[op[x][i]][k])%mod;
				g[j+1]=(g[j+1]+f[x][j]*f[op[x][i]][k]%mod*(j+1)%mod*(k+1))%mod;
			}
		}
		for(ll j=0;j<=i+1;j++) f[x][j]=g[j];
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(i=1;i<n;i++){
		cin>>x>>y;
		op[x].push_back(y),op[y].push_back(x);
	}
	dfs(1,-1);
	for(i=0;i<=n;i++) ans=(ans+f[1][i])%mod;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

## 题解
两个操作序列得到的 $a$ 相同当且仅当所有选择的边都一样，并且对于一个点，它四周的边选择的顺序也一样。

根据这个我们可以做一个 DP，用 $f_{i, j, 0/1}$ 表示 $i$ 的子树内，与 $i$ 相连的边选择了 $j$ 个，是否选择了父边的方案数。

$$f_{i, j, x} = f_{i, j, x}\times\sum_{k = 0}^{deg_v} f_{v, k, 0}+f_{i, j - 1, x}\times\sum_{k = 0}^{deg_v}f_{v, k, 1}\times j$$

树上背包类型的转移，分讨儿子边是否选择，如果选择就需要在前面 $j - 1$ 条已选择的边里面确定一个顺序，所以要乘 $j$，和式可以预处理。

时间复杂度：$\Theta(n^2)$。
## 代码
```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#define int long long
using namespace std;
const int N = 3e3 + 10, mod = 998244353;

int n, f[N][N][2], sz[N], s[N][2];
vector<int> g[N];
void dfs(int u, int fa) {
    sz[u] = 1, f[u][0][0] = 1, f[u][1][1] = (u > 1); // 注意根节点没有父边
    int d = g[u].size();
    for(auto v : g[u]) {
        if(v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        for(int j = d; j >= 0; j --)
            for(int x = 0; x < 2; x ++)
                f[u][j][x] = (f[u][j][x] * s[v][0] % mod + (j ? f[u][j - 1][x] * j % mod * s[v][1] % mod : 0)) % mod;
    }
    for(int j = 0; j <= d; j ++)
        for(int x = 0; x < 2; x ++)
            (s[u][x] += f[u][j][x]) %= mod;
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1, a, b; i < n; i ++) {
        cin >> a >> b;
        g[a].push_back(b), g[b].push_back(a);
    }
    dfs(1, 1);
    cout << s[1][0] << '\n';

    return 0;
}
```

---

## 作者：Judgelight (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_arc171_c)

---

首先考虑一个性质：对于两种删边的方案，如果对于任意点 $i\in [1,n]$ 都有两方案的删边顺序相同，则这两种方案得到的结果一定是相同的。

那么根据这个性质不难得到 DP 方程 $f_{u,i,0/1}$ 表示删去了**与点 $u$ 相连** 的 $i$ 条边，有/没有 删掉 $u$ 到父亲的边的方案数，则有 

$$f'_{u,i,0/1}=f_{u,i,0/1}\cdot\left(\sum\limits_{i}f_{v,i,0}\right)+[i>0]f_{u,i,0/1}\cdot\left(\sum\limits_{i}f_{v,i,1}\right)\cdot i$$

。

这道题解题的关键在于发现删除顺序对最终答案的影响是极其难统计的，进而去发掘性质，当遇到不可做的 DP 题时不妨考虑换一种统计方法而不是去优化 DP 过程。

---

## 作者：NobodyThere (赞：0)

设 $b$ 为被删去的边按删去顺序组成的序列，并称最终使得序列 $a$ 相同的序列 $b$ 在同一个等价类中。原问题即为统计等价类个数。

初步思考：当一些边在原图中不相邻的时候，仅仅改变这些边的先后顺序，不会对最终结果产生影响。反之，如果这些边相邻，那么会对最终结果产生影响。于是猜想有以下结论：

这样的 $b$ 在同一个等价类，当且仅当其元素所构成的集合相同，且从任意一个点引出的被删去的边被删去的顺序均相同。

下面证明这个结论。（证明写得比较繁琐，读者可以自行跳过）

---

引理一：如果 $b$ 中的元素所构成的集合不同，那么这样的 $b$ 不在一个等价类中。

证明：考虑在原图中割去一条边，将原图划分成两个子图，其点集分别为 $S,T$，且 $S'=\{a_i|i\in S\},T'=\{a_i|i\in T\}$。那么若这条边没被删去，则 $S'=S,T'=T$，否则 $S'$ 与 $T'$ 必然由交换 $S,T$ 的一对元素得到，即有 $S'\neq S,T'\neq T$。如果一条边在其中一个序列出现而没在另外一个序列出现，那么必然有点集 $S,T$ 对应的 $S',T'$ 不同，从而序列 $a$ 不同。

引理二：在删边集合相同的前提下，考虑一个点引出的所有被删去的边，若其在 $b$ 中的顺序不同，那么这样的 $b$ 不在一个等价类中。

证明：设该节点为 $u$，其引出的所有被删去的边，按 $b$ 中的顺序排列得到 $s_1,s_2,\cdots,s_k$，对应子树 $S_1,S_2,\cdots,S_k$，$S_i'=\{a_j|j\in S_i\}$。那么 $S_1'$ 一定由 $S_1$ 中的一个元素与 $u$ 交换得到，$S_i(i>1)$ 一定由 $S_i$ 中的一个元素与 $S_{i-1}$ 交换得到。若改变 $s$ 的顺序，则每棵子树 $S_i$ 对应的 $S_i'$ 一定会发生变化，从而序列 $a$ 一定会发生变化。

引理三：在删边集合相同的前提下，若对于任意一个点，其引出的所有被删去的边，在 $b$ 中的顺序均相同，那么这样的 $b$ 在同一个等价类中。

证明：首先，对于某条边，其被删去时，其端点上的物件相同。（否则，参考引理二的证明过程，必然存在某棵子树，满足其存在一条边，其被删去时，其端点上的物件也不同。而在充分小的子树中，该命题不成立。）于是对于原图上的任意一条边，其分割成的两个子图，其上的物件所构成的集合均相同，而这个信息可以唯一确定序列 $a$，于是这样的 $b$ 在同一个等价类中。

综上，结论得证。

---

这个结论将原问题转化为了：

对于任意一个删边集合 $S$，其权值为 $\prod_ud'_u!$，其中 $d'_u$ 表示 $u$ 连出的边有多少条在集合 $S$ 内。求所有删边集合的权值和。

设 $f_{u,0},f_{u,1}$ 分别表示其连向父亲的边没被删去和被删去时，以 $u$ 为根的子树的答案，那么对于一个节点 $u$，状态记录与 $u$ 相邻的被删去的边数，DP 即可得到答案。复杂度 $O(\sum d^2)=O(n^2)$，多项式优化可以做到 $O(\sum d\log^2d)=O(n\log^2n)$，$d$ 表示点的度数。

---

## 作者：JackMerryYoung (赞：0)

# 前言

随便跳到一道典题。

# 正文

~~这道题的对于父亲的决策长得有点像看守皇宫捏（~~

有一个很典的树形 DP 设计方式，考虑每个点，在以其为根节点的子树内或者与其相连的点之间进行转移。本题就是这样。

我们直接设计状态：$f_{u, j, 0/1}$ 表示以 $u$ 为根节点，与 $u$ 相连的砍了 $j$ 条，与父亲相连的那条边砍了没有，如果砍了是 $1$，不砍是 $0$；这个状态下的方案个数。

对于每个儿子 $v$，显然我们可以枚举 $k$ 表示与 $v$ 相连的砍了 $k$ 条，然后累加起来计算，但是显然我们没必要每一次转移都算，维护一个 $g_{u, 0/1} = \sum{f_{u, j, 0/1}}$ 即可。

方程：

$$
\begin{cases}
f_{u, j, 0/1} \leftarrow f_{u, j, 0/1} \times g_{v, 0} + f_{u, j - 1, 0/1} \times g_{v, 1} \times j \quad (j > 0)\\
f_{u, j, 0/1} \leftarrow f_{u, j, 0/1} \times g_{v, 0} \quad (j = 0)
\end{cases}
$$

复杂度 $\mathcal{O}(N^2)$ 可过。

# 代码

不知道为啥我要开 `long long`。

``` cpp
#include <bits/stdc++.h>
#define MOD (long long) (998244353)
using namespace std;

long long N;

long long cnt, head[3005];
struct Edge {
	long long nxt, to;
} edge[6005];

void add(long long u, long long v)
{
	++ cnt;
	edge[cnt].nxt = head[u];
	edge[cnt].to = v;
	head[u] = cnt;
}

long long f[3005][3005][2], g[3005][2], tmp[3005][2];

void dfs(long long u, long long fa)
{
	long long edge_cnt = 0;
	f[u][0][0] = 1;
	if(u == 1) f[u][1][1] = 0;
	else ++ edge_cnt, f[u][1][1] = 1;
	for(long long i = head[u]; i; i = edge[i].nxt)
	{
		long long v = edge[i].to;
		if(v == fa) continue;
		dfs(v, u);
		++ edge_cnt;
		for(long long j = 0; j <= edge_cnt; ++ j)
			tmp[j][0] = f[u][j][0] % MOD, tmp[j][1] = f[u][j][1] % MOD;

		for(long long j = 0; j <= edge_cnt; ++ j)
			f[u][j][0] = (((tmp[j][0] * g[v][0]) % MOD) + (j > 0 ? 1 : 0) * ((tmp[j - 1][0] * g[v][1] * j) % MOD)) % MOD, f[u][j][1] = (((tmp[j][1] * g[v][0]) % MOD) + (j > 0 ? 1 : 0) * ((tmp[j - 1][1] * g[v][1] * j) % MOD)) % MOD;
	}
	
	for(long long j = 0; j <= edge_cnt; ++ j)
		g[u][0] = (g[u][0] + f[u][j][0]) % MOD, g[u][1] = (g[u][1] + f[u][j][1]) % MOD;

}

signed main()
{
	cin >> N;
	for(long long i = 1; i < N; ++ i)
	{
		long long u, v;
		cin >> u >> v;
		add(u, v); add(v, u);
	}
	
	dfs(1, 0);
	cout << g[1][0] << endl;
	return 0;
}
```

# 后言

菜就多练。

---

