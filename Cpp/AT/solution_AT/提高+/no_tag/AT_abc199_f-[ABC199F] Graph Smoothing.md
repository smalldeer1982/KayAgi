# [ABC199F] Graph Smoothing

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc199/tasks/abc199_f

$ N $ 頂点 $ M $ 辺の単純無向グラフがあります。頂点には $ 1 $ から $ N $ までの、辺には $ 1 $ から $ M $ までの番号がついています。  
 辺 $ i $ は頂点 $ X_i $ と頂点 $ Y_i $ を結んでいます。また、頂点 $ i $ には最初整数 $ A_i $ が書かれています。  
 あなたは $ K $ 回にわたって以下の操作を行います。

- $ M $ 本ある辺の中から、一様ランダムかつ他の選択と独立に $ 1 $ 本選ぶ。その辺が結ぶ $ 2 $ 頂点に書かれている数の平均を $ x $ として、その $ 2 $ 頂点に書かれている数を両方 $ x $ で置き換える。

各頂点 $ i $ について、$ K $ 回の操作後に頂点 $ i $ に書かれている数の期待値を求め、注記の通り $ \bmod\ (10^9\ +\ 7) $ で出力してください。

## 说明/提示

### 注記

有理数を出力する際は、まずその有理数を分数 $ \frac{y}{x} $ として表してください。  
 ここで、$ x,y $ は整数であり、$ x $ は $ 10^9+7 $ で割り切れてはなりません (この問題の制約下で、そのような表現は必ず可能です)。  
 そして、$ xz\ \equiv\ y\ \pmod\ {10^9+7} $ を満たすような $ 0 $ 以上 $ 10^9+6 $ 以下の唯一の整数 $ z $ を出力してください。

### 制約

- $ 2\ \le\ N\ \le\ 100 $
- $ 1\ \le\ M\ \le\ \frac{N(N\ -\ 1)}{2} $
- $ 0\ \le\ K\ \le\ 10^9 $
- $ 0\ \le\ A_i\ \le\ 10^9 $
- $ 1\ \le\ X_i\ \le\ N $
- $ 1\ \le\ Y_i\ \le\ N $
- 与えられるグラフは単純
- 入力に含まれる値は全て整数である

### Sample Explanation 1

\- 唯一の操作で辺 $ 1 $ が選ばれた場合 : 頂点 $ 1,\ 2,\ 3 $ に書かれている数はそれぞれ $ 2,\ 2,\ 5 $ となります - 唯一の操作で辺 $ 2 $ が選ばれた場合 : 頂点 $ 1,\ 2,\ 3 $ に書かれている数はそれぞれ $ 4,\ 1,\ 4 $ となります 従って、操作後に頂点 $ 1,\ 2,\ 3 $ に書かれている数の期待値はそれぞれ $ 3,\ \frac{3}{2},\ \frac{9}{2} $ となります。 これらを注記に従って $ \bmod\ (10^9\ +\ 7) $ の表現に変換すると、それぞれ $ 3,\ 500000005,\ 500000008 $ となります。

### Sample Explanation 2

\- $ 1 $ 回目の操作で辺 $ 1 $ が選ばれた場合 頂点 $ 1,\ 2,\ 3 $ に書かれている数はそれぞれ $ 30,\ 30,\ 36 $ となります - $ 2 $ 回目の操作で辺 $ 1 $ が選ばれた場合 : 頂点 $ 1,\ 2,\ 3 $ に書かれている数はそれぞれ $ 30,\ 30,\ 36 $ となります - $ 2 $ 回目の操作で辺 $ 2 $ が選ばれた場合 : 頂点 $ 1,\ 2,\ 3 $ に書かれている数はそれぞれ $ 33,\ 30,\ 33 $ となります - $ 1 $ 回目の操作で辺 $ 2 $ が選ばれた場合 頂点 $ 1,\ 2,\ 3 $ に書かれている数はそれぞれ $ 24,\ 48,\ 24 $ となります - $ 2 $ 回目の操作で辺 $ 1 $ が選ばれた場合 : 頂点 $ 1,\ 2,\ 3 $ に書かれている数はそれぞれ $ 36,\ 36,\ 24 $ となります - $ 2 $ 回目の操作で辺 $ 2 $ が選ばれた場合 : 頂点 $ 1,\ 2,\ 3 $ に書かれている数はそれぞれ $ 24,\ 48,\ 24 $ となります これら $ 4 $ 通りのケースが各 $ \frac{1}{4} $ の確率で起こるので、頂点 $ 1,\ 2,\ 3 $ に最終的に書かれている数の期待値はそれぞれ $ \frac{123}{4},\ \frac{144}{4}\ (=36),\ \frac{117}{4} $ となります。

## 样例 #1

### 输入

```
3 2 1
3 1 5
1 2
1 3```

### 输出

```
3
500000005
500000008```

## 样例 #2

### 输入

```
3 2 2
12 48 36
1 2
1 3```

### 输出

```
750000036
36
250000031```

## 样例 #3

### 输入

```
4 5 1000
578 173 489 910
1 2
2 3
3 4
4 1
1 3```

### 输出

```
201113830
45921509
67803140
685163678```

# 题解

## 作者：rui_er (赞：4)

本题解提供英文版，位于示例代码之后。

English version of this editorial is provided after the sample code.

设行向量：

$$
A^{(k)}=
\begin{bmatrix}
a_1^{(k)} & a_2^{(k)} & \cdots & a_n^{(k)}
\end{bmatrix}
$$

表示 $k$ 次操作后每个节点点权的期望。特别地，$A^{(0)}$ 表示初始时每个节点的点权。我们希望找出 $A^{(k)}$ 间的递推关系 $A^{(k)}=A^{(k-1)}M$，利用矩阵快速幂解决问题。

设 $d_u$ 表示节点 $u$ 的度数。一轮操作中，$u$ 作为被选中的边的两个端点之一的概率为 $\frac{d_u}{m}$，此时节点 $u$ 的点权被与另一端点的点权取平均，否则节点 $u$ 的点权不变。因此，有 $M_{u,u}=1-\frac{d_u}{2m}$。考察与 $u$ 邻接的每个点 $v$，被选中的边恰为 $(u,v)$ 的概率为 $\frac{1}{m}$，此时由于取平均，$u$ 点权的一半被贡献给 $v$。因此，有 $M_{u,v}=\frac{1}{2m}$。

已知 $A^{(0)}$ 和 $M$，容易通过矩阵快速幂求出 $A^{(k)}$，即可得到答案。

时间复杂度 $O(n^3\log k)$。

示例代码 / Sample code:

```cpp
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

template<typename T> void chkmin(T& x, T y) {if(y < x) x = y;}
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

const int N = 105, mod = 1e9 + 7;
typedef Modint<mod> mint;

int n, m, k;
mint a[N], deg[N];
vector<int> e[N];

struct Matrix {
    mint mat[N][N];
    Matrix() {rep(i, 1, n) rep(j, 1, n) mat[i][j] = 0;}
    friend Matrix operator*(const Matrix& a, const Matrix& b) {
        Matrix c;
        rep(i, 1, n) rep(j, 1, n) rep(k, 1, n) c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
        return c;
    }
    friend Matrix& operator*=(Matrix& a, const Matrix& b) {
        return a = a * b;
    }
    friend Matrix operator^(Matrix a, int k) {
        Matrix r;
        rep(i, 1, n) r.mat[i][i] = 1;
        for(; k; k >>= 1, a *= a) if(k & 1) r *= a;
        return r;
    }
    friend Matrix& operator^=(Matrix& a, int k) {
        return a = a ^ k;
    }
}M;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    rep(u, 1, n) cin >> a[u];
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        ++deg[u]; ++deg[v];
        e[u].push_back(v);
        e[v].push_back(u);
    }
    rep(u, 1, n) {
        M.mat[u][u] = 1 - deg[u] / (m * 2);
        for(int v : e[u]) M.mat[u][v] = ~mint(m * 2);
    }
    M ^= k;
    rep(v, 1, n) {
        mint ans = 0;
        rep(u, 1, n) ans += a[u] * M.mat[u][v];
        cout << ans << endl;
    }
    return 0;
}
```

Let the row vector be defined as:

$$
A^{(k)}=
\begin{bmatrix}
a_1^{(k)} & a_2^{(k)} & \cdots & a_n^{(k)}
\end{bmatrix}
$$

where $A^{(k)}$ represents the expected value of each vertex's weight after $k$ operations. Specifically, $A^{(0)}$ represents the initial weights of each vertex. We aim to find the recurrence relation between $A^{(k)}$ and $A^{(k-1)}$ such that $A^{(k)}=A^{(k-1)}M$, and solve the problem using matrix exponentiation.

Let $d_u$ denote the degree of vertex $u$. During one operation, the probability that the selected edge is adjacent to vertex $u$ is $\frac{d_u}{m}$. In this case, the weight of vertex $u$ is averaged with that of the other vertex connected by the edge; otherwise, the weight of vertex $u$ remains unchanged. Therefore, we have $M_{u,u}=1-\frac{d_u}{2m}$. Now, consider each adjacent vertex $v$ of $u$. The probability that the selected edge is exactly $(u,v)$ is $\frac{1}{m}$, and in this case, half of $u$'s weight is contributed to $v$ due to averaging. Therefore, we have $M_{u,v}=\frac{1}{2m}$.

Given $A^{(0)}$ and $M$, $A^{(k)}$ can be easily computed using matrix exponentiation, thus yielding the answer.

The time complexity is $O(n^3\log k)$.

---

## 作者：Eibon (赞：2)

概率 dp，考虑设 $f_{u,i}$ 表示节点 $u$ 在 $i$ 次操作之后的期望权值。

设 $d_{u}$ 表示点 $u$ 的度数。

则

$$f_{u,i}=\left(\sum \dfrac{1}{m} \times\dfrac{f_{u,i-1}+f_{v,i-1}}{2}\right)+\left(1-\dfrac{d_{u}}{m}\right)\times f_{u,i-1}$$ 

表示该点被选中以及没有选中的情况。

因为 $\sum \frac{1}{m}=\frac{d_{u}}{m}$。

所以原式可化简为

$$f_{u,i}=\left(1-\dfrac{d_{u}}{2\times m}\right)\times f_{u,i-1}+\left(\sum \dfrac{1}{2\times m} \times f_{v,i-1}\right)$$

考虑使用矩阵快速幂进行加速。

则 $a_{i,i}=1-\dfrac{d_{u}}{2\times m}$，$a_{i,j}=\dfrac{1}{2\times m}$。

将初始序列也当做矩阵，与最后转移矩阵相乘即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=100+5;
const int mod=1e9+7;
int T=1,n,m,k;
int a[maxn],ru[maxn];
struct mul
{
	int n,m,mp[105][105];
	mul()
	{
		n=m=0;
		memset(mp,0,sizeof mp);
	}
	mul(int x,int y)
	{
		n=x,m=y;
		memset(mp,0,sizeof mp);
	}
};
mul c;
mul operator * (const mul &a,const mul &b)
{
	c=mul(a.n,b.m);
	for(int i=1;i<=a.n;i++){
		for(int j=1;j<=b.m;j++){
			for(int k=1;k<=a.m;k++){
				c.mp[i][j]+=a.mp[i][k]*b.mp[k][j]%mod;
				c.mp[i][j]%=mod;
			}
		}
	}
	return c;
}
mul init(mul a)
{
	for(int i=1;i<=n;i++){
		a.mp[i][i]=1;
	}
	return a;
}
mul power(mul a,int b)
{
	mul res(n,n);
	res=init(res);
	while(b){
		if(b&1){
			res=res*a;
		}
		a=a*a;
		b>>=1;
	}
	return res;
}
int power(int a,int b)
{
	int res=1;
	while(b){
		if(b&1){
			res=res*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
void solve()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	mul a(n,n),res(n,n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a.mp[1][i]);
	}
	int inv=power(m*2%mod,mod-2);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%lld%lld",&u,&v);
		ru[u]++;ru[v]++;
		res.mp[u][v]=res.mp[v][u]=inv;
	}
	for(int i=1;i<=n;i++){
		res.mp[i][i]=(1-inv*ru[i]%mod+mod)%mod;
	}
	res=a*power(res,k);
	for(int i=1;i<=n;i++){
		printf("%lld\n",res.mp[1][i]);
	}
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	//scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：Register_int (赞：1)

根据期望线性性，我们可以搞出转移矩阵 $A$ 表示进行一次操作后每个点的数值期望，完了直接快速幂。

接下来构造转移矩阵。设点 $i$ 的度数为 $d_i$，则一次操作影响该点的概率为 $\dfrac{d_i}m$。与周围其他点取平均时会使 $a_i\rightarrow\dfrac{a_i}2$，所以 $A_{i,i}=1-\dfrac{d_i}{2m}$。而对于该点连接的点 $j$，选到边 $(i,j)$ 的概率均为 $\dfrac1m$，选到 $(i,j)$ 会使 $a_i\rightarrow a_i+\dfrac{a_j}2$，所以 $A_{i,j}=\dfrac1{2m}$。

那么转移矩阵就构造完了，直接快速幂即可，复杂度 $O(n^3\log k)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e2 + 10;
const int mod = 1e9 + 7;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) res = res * b % mod;
		b = b * b % mod, p >>= 1;
	}
	return res;
}

struct matrix {
	
	int n; ll a[MAXN][MAXN];
	
	matrix() { memset(a, 0, sizeof a); }
	
	matrix(int n, ll k = 0) : n(n) {
		memset(a, 0, sizeof a);
		for (int i = 1; i <= n; i++) a[i][i] = k;
	}
	
	matrix operator * (const matrix &rhs) const {
		matrix res(n);
		for (int k = 1; k <= n; k++) {
			for (int j = 1; j <= n; j++) {
				for (int i = 1; i <= n; i++) res.a[i][j] = (res.a[i][j] + a[i][k] * rhs.a[k][j]) % mod;
			}
		}
		return res;
	}
	
	ll *operator [] (const int k) { return a[k]; }
	
	void print() {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) printf("%lld ", a[i][j]); puts("");
		}
		puts("");
	}
} base, a;

inline 
matrix qpow(matrix b, int p) {
	matrix res(b.n, 1);
	while (p) {
		if (p & 1) res = res * b;
		b = b * b, p >>= 1;
	}
	return res;
}

int n, m, k, d[MAXN]; ll p;

int main() {
	scanf("%d%d%d", &n, &m, &k), p = qpow(m << 1, mod - 2), a = base = n;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[1][i]);
	for (int i = 1, u, v; i <= m; i++) scanf("%d%d", &u, &v), d[u]++, d[v]++, base[u][v] = base[v][u] = p;
	for (int i = 1; i <= n; i++) base[i][i] = mod + 1 - d[i] * p % mod; a = a * qpow(base, k);
	for (int i = 1; i <= n; i++) printf("%lld\n", a[1][i]);
}
```

---

