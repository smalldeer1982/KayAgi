# Bro Thinks He's Him

## 题目描述

Skibidus 自认为是"天选之人"！他通过解决这个难题证明了这一点。你也能证明自己吗？

给定一个二进制字符串 $^{\text{∗}}$ $t$，定义 $f(t)$ 为将 $t$ 分割成由相同字符组成的连续子串的最小数量。例如，$f(\texttt{00110001}) = 4$，因为 $t$ 可以被分割为 $\texttt{[00][11][000][1]}$，每个括号内的子串均由相同字符组成。

Skibidus 给你一个二进制字符串 $s$ 和 $q$ 次查询。每次查询会翻转字符串中的一个字符（即 $\texttt{0}$ 变为 $\texttt{1}$，$\texttt{1}$ 变为 $\texttt{0}$），且修改会保留到后续查询。每次查询后，你需要输出所有非空子序列 $^{\text{†}}$ $b$ 的 $f(b)$ 之和模 $998\,244\,353$ 的结果。

 $^{\text{∗}}$ 二进制字符串仅包含字符 $\texttt{0}$ 和 $\texttt{1}$。

 $^{\text{†}}$ 字符串的子序列是指通过删除原字符串中若干（可能为零）个字符得到的新字符串。

## 说明/提示

第一个测试用例在第一次查询后，$s$ 变为 $\texttt{001}$。计算所有子序列的 $f$ 值：
- $f(s_1) = f(\texttt{0}) = 1$
- $f(s_2) = f(\texttt{0}) = 1$
- $f(s_3) = f(\texttt{1}) = 1$
- $f(s_1 s_2) = f(\texttt{00}) = 1$
- $f(s_1 s_3) = f(\texttt{01}) = 2$
- $f(s_2 s_3) = f(\texttt{01}) = 2$
- $f(s_1 s_2 s_3) = f(\texttt{001}) = 2$

这些值的总和为 $10$，模 $998\,244\,353$ 后结果为 $10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
101
2
1 3
10110
3
1 2 3
101110101
5
7 2 4 4 1```

### 输出

```
10 7 
61 59 67 
1495 1169 1417 1169 1396```

# 题解

## 作者：DengStar (赞：6)

> [$\mathcal{CNBLOGS}$](https://www.cnblogs.com/dengstar/p/18709484)

计数题！难点主要在于第一步的转化，后续的数据结构优化是顺理成章的。

按子序列计数显然是没有前途的，因为子序列的数量是 $O(2^{n})$。按照计数问题的套路，我们先**改变计数对象**。

对于一个序列，它的权值是其极长的 $0$ 和 $1$ 连续段个数，所以我们不妨想想这些极长连续段是怎么出现的。除了第一个极长连续段，所有极长连续段的的开头第一个数必然和它前面一个数不同。也就是说，**两个相邻的不同数贡献一个连续段**。形式化的表述为：
$$
f(s) = 1 + \sum_{i = 1}^{n - 1} [s_{i} \neq s_{i + 1}]
$$
因此可以**枚举值不同的数构成的数对 $(i, j)$**（$i < j$ 且 $s_{i} \neq s_{j}$）。对于一对 $(i, j)$，它对总答案的贡献就是使得 $s_{i}$ 和 $s_{j}$ 相邻的子序列个数。那么有多少个这样的子序列呢？这相当与钦定 $s_{i}$ 和 $s_{j}$ 必须选，$s_{i + 1} \sim s_{j - 1}$ 必须不选，其它位置可以选也可以不选。因此 $(i, j)$ 对答案的贡献为 $2^{i - 1 + n - j}$，总答案为：
$$
\boxed{ans = \sum_{i = 1}^{n} \left(2^{n - i} + \sum_{j = i + 1}^{n} [s_{i} \neq s_{j}] \cdot 2^{i - 1 + n - j}\right)}
$$
（加上 $2^{n - i}$ 是考虑到 $s_{i}$ 作为整个子序列的开头时的贡献，此时只有 $i + 1 \sim n$ 的位置可以任意选。）这样就导出了一个 $O(qn^2)$ 的做法。

考虑优化。把上式提出公因式变成
$$
ans = \sum_{i = 1}^{n} \left(2^{n - i} + 2^{i - 1} \cdot \sum_{j = i + 1}^{n} [s_{i} \neq s_{j}] \cdot 2^{\ n - j}\right)
$$
预处理一下 $2^{n - j}$ 的后缀和，就可以做到 $O(qn)$ 的时间复杂度。这里的瓶颈主要在于每次修改的时候都要重新算一遍后缀和。

到了这一步，已经可以 $O(n)$ 计算出在没有修改时的答案。因此我们先计算出未修改时的答案，然后考虑每次修改对答案的影响，在把答案加上这个影响。

由于我们每次修改一个位置的值，因此我们写出一个位置 $p$ 对答案的贡献 $g(p)$：
$$
g(p) = 2^{n - p} + 2^{n - p} \cdot \sum_{i = 1}^{p - 1} [s_{i} \neq s_{j}] \cdot 2^{i - 1} + 2^{p - 1} \cdot \sum_{i = p + 1}^{n} [s_{i} \neq s_{j}] \cdot 2^{n - i}
$$
第一项代表 $p$ 作为子序列第一个值时的贡献，第二项计算形如 $(i, p)$（$i < p$）的数对的贡献，第三项计算形如 $(p, i)$（$p < i$）的数对的贡献。

（值得一提的是，$ans \neq \sum_{i = 1}^{n} g(i)$，因为 $g(i)$ 统计了所有包含 $i$ 的数对的贡献，所以对于每个数对 $(i, j)$，它在算 $g(i)$ 和 $g(j)$ 的时候都会被统计到，这样会算重。因此计算 $ans$ 的时候一定要保证枚举的数对是有序的。但修改的时候我们考虑 $i$ 的所有贡献，所以任何包含 $i$ 的数对都要被计入其中。）

每次修改时，先减去 $p$ 原来的贡献 $g(p)$，再加上新的贡献 $g'(p)$。$\sum_{i = 1}^{p - 1} [s_{i} \neq s_{j}] \cdot 2^{i - 1}$ 和 $\sum_{i = p + 1}^{n} [s_{i} \neq s_{j}] \cdot 2^{n - i}$ 这两项需要单点修改和区间求值，用树状数组维护即可。（为了计算 $[s_{i} \neq s_{j}]$ 这个因子，需要开两组树状数组分别维护 $0$ 位置和 $1$ 位置的值。说“两组”是因为每组都要开两个线段树分别维护 $2^{i -1 }$ 的和及 $2^{n - i}$ 的和。）

综上所述，我们做到了 $O(n + q \log n)$ 的时间复杂度。[AC 记录](https://codeforces.com/contest/2065/submission/305464861)
综上所述，我们做到了 $O(n + q \log n)$ 的时间复杂度。[AC 记录](https://codeforces.com/contest/2065/submission/305464861)

---

## 作者：yvbf (赞：5)

![](bilibili:BV1eiNhe7EZ9?t=2805)

---

## 作者：未来姚班zyl (赞：4)

## 题目大意

给定一个长度为 $n$ 的 $01$ 串 $S$，与 $m$ 次修改，每次修改为翻转一个位置上的值，在每次结束后，你需要求出 $S$ 的所有子序列的连续段数的总和，对 $998244353$ 取模。

## 题目分析

连续段数就是相邻位置不相等的数量加 $1$，这个加 $1$ 的总和就是 $2^n-1$。

然后考虑位置 $l,r$ 的贡献，显然当且仅当首先 $S_l\neq S_r$ 且 $l$ 到 $r$ 之间没有位置被包含到子序列里，$S_l$ 和 $S_r$ 被包含到子序列里，会产生 $1$ 的贡献。总方案数为 $S_l$ 之前、$S_r$ 之后随便选的方案数，即 $2^{l-1}\times 2^{n-r}$。

把这个拆开来再用树状数组维护前缀和就可以了，$O(n\log n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=2e5+5,M=1e6+5,inf=(1LL<<29)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
string s;
int n,m,a[N],pw[N];
int t[N][2],T[N][2];
inline void ad(int x,int w,int k){
	while(x<=n)add(t[x][w],k),x+=x&-x;
}
inline void Ad(int x,int w,int k){
	x=n-x+1;
	while(x<=n)add(T[x][w],k),x+=x&-x;
}
inline int query(int x,int w){
	int ans=0;
	while(x)add(ans,t[x][w]),x-=x&-x;
	return ans;
}
inline int Query(int x,int w){
	int ans=0;
	x=n-x+1;
	while(x)add(ans,T[x][w]),x-=x&-x;
	return ans;
}
inline void Main(){
	cin>>s,n=s.length(),s='#'+s;
	m=read();
	repn(i)a[i]=s[i]-'0';
	repn(i)rep(j,0,1)t[i][j]=T[i][j]=0;
	int ans=Red(pw[n],1);
	repn(i)ad(i,a[i],pw[i-1]),Ad(i,a[i],pw[n-i]);
	repn(i)add(ans,mul(pw[n-i],query(i-1,a[i]^1)));
	while(m--){
		int i=read();
		red(ans,Add(mul(pw[n-i],query(i-1,a[i]^1)),mul(pw[i-1],Query(i+1,a[i]^1))));
		add(ans,Add(mul(pw[n-i],query(i-1,a[i])),mul(pw[i-1],Query(i+1,a[i]))));
		a[i]^=1;
		ad(i,a[i]^1,mod-pw[i-1]),Ad(i,a[i]^1,mod-pw[n-i]);
		ad(i,a[i],pw[i-1]),Ad(i,a[i],pw[n-i]);
		cout <<ans<<' ';
	}
	cout <<"\n";
}
signed main(){
	pw[0]=1;
	rep(i,1,N-5)pw[i]=mul(pw[i-1],2);
	int T=read();
	while(T--)Main();
	return 0;
}
```

---

## 作者：bluewindde (赞：4)

不知道放在题解区 LaTeX 会不会炸，如果炸了请移步文章区查看。

---

线段树维护矩阵形式 DP 转移模板。

设 $dp_{i, 0 / 1}$ 表示处理到第 $i$ 个位置，结尾是 $0 / 1$ 的答案，$f_{i, 0 / 1}$ 表示对应的方案数。

答案是 $dp_{n, 0} + dp_{n, 1}$。

考虑继承前面的子序列、在前面的子序列后加数、新建一个子序列三种形式。若 $a_i = 1$，转移

$$
\begin{align*}
dp_{i, 0} &= dp_{i - 1, 0} \\
dp_{i, 1} &= 2 \cdot dp_{i - 1, 1} + (dp_{i - 1, 0} + f_{i - 1, 0}) + 1 \\
f_{i, 0} &= f_{i - 1, 0} \\
f_{i, 1} &= 2 \cdot f_{i - 1, 1} + f_{i - 1, 0} + 1 \\
\end{align*}
$$

为了动态修改 $a_i$，状态设为

$$
\begin{bmatrix}
dp_{i - 1, 0} & dp_{i - 1, 1} & f_{i - 1, 0} & f_{i - 1, 1} & 1
\end{bmatrix}
$$

转移写成 $5 \times 5$ 矩阵

$$
\begin{bmatrix}
1 & 1 & 0 & 0 & 0 \\
0 & 2 & 0 & 0 & 0 \\
0 & 1 & 1 & 1 & 0 \\
0 & 0 & 0 & 2 & 0 \\
0 & 1 & 0 & 1 & 1 \\
\end{bmatrix}
$$

$a_i = 0$ 是对称的，即

$$
\begin{bmatrix}
2 & 0 & 0 & 0 & 0 \\
1 & 1 & 0 & 0 & 0 \\
0 & 0 & 2 & 0 & 0 \\
1 & 0 & 1 & 1 & 0 \\
1 & 0 & 1 & 0 & 1 \\
\end{bmatrix}
$$

时间复杂度 $O(k^3 q \log n)$，其中 $k = 5$。

```cpp
#include <array>
#include <iostream>
#include <string>

#define int long long

using namespace std;

const int mod = 998244353;

struct matrix {
    array<array<int, 5>, 5> a;
    matrix() {
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                a[i][j] = 0;
    }
    matrix(const matrix &mat) { a = mat.a; }
    ~matrix() {}
    inline matrix &operator=(const matrix &mat) {
        a = mat.a;
        return *this;
    }
    inline const array<int, 5> &operator[](int x) const { return a[x]; }
    inline array<int, 5> &operator[](int x) { return a[x]; }
    friend inline matrix operator*(const matrix &A, const matrix &B) {
        matrix C;
        for (int i = 0; i < 5; ++i)
            for (int k = 0; k < 5; ++k)
                for (int j = 0; j < 5; ++j)
                    C[i][j] += A[i][k] * B[k][j];
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                C[i][j] %= mod;
        return C;
    }
};

int n, q;
int a[200005];

matrix d[800005];
static inline void init(int x, int p) {
    if (a[x]) {
        d[p][0] = {1, 1, 0, 0, 0};
        d[p][1] = {0, 2, 0, 0, 0};
        d[p][2] = {0, 1, 1, 1, 0};
        d[p][3] = {0, 0, 0, 2, 0};
        d[p][4] = {0, 1, 0, 1, 1};
    } else {
        d[p][0] = {2, 0, 0, 0, 0};
        d[p][1] = {1, 1, 0, 0, 0};
        d[p][2] = {0, 0, 2, 0, 0};
        d[p][3] = {1, 0, 1, 1, 0};
        d[p][4] = {1, 0, 1, 0, 1};
    }
}
static inline void build(int s, int t, int p) {
    if (s == t) {
        init(s, p);
        return;
    }
    int mid = (s + t) >> 1;
    build(s, mid, p << 1);
    build(mid + 1, t, p << 1 | 1);
    d[p] = d[p << 1] * d[p << 1 | 1];
}
static inline void update(int x, int s, int t, int p) {
    if (s == t) {
        init(s, p);
        return;
    }
    int mid = (s + t) >> 1;
    if (x <= mid)
        update(x, s, mid, p << 1);
    else
        update(x, mid + 1, t, p << 1 | 1);
    d[p] = d[p << 1] * d[p << 1 | 1];
}

static inline void solve() {
    string s;
    cin >> s >> q;
    n = (int)s.size();
    for (int i = 0; i < n; ++i)
        a[i + 1] = s[i] == '1';
    build(1, n, 1);
    while (q--) {
        int x;
        cin >> x;
        a[x] ^= 1;
        update(x, 1, n, 1);
        cout << (d[1][4][0] + d[1][4][1]) % mod << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
    cout.flush();
    return 0;
}
```

---

## 作者：wfc284 (赞：3)

首先，段数等于相邻不等的数量加一。  
如：`0011101101` 中，有 $(2,3),(5,6),(6,7),(8,9),(9,10)$ 相邻不等，于是段数为 $6$。  
有了这个转化，我们就可以拆贡献到每一组【相邻不等】上了。

我们计算一个下标 $i$ 的贡献：  
找到一个 $j \in [1,i)$ 且 $a_j \ne a_i$，我们要让这一组 $i,j$ 在一些子序列中是相邻的。显然，$i,j$ 必选，$i,j$ 之间的不选，$j$ 之前或 $i$ 之后的任选，于是贡献就是 $2^{j-1} \times 2^{n-i}$。
所以 $i$ 的贡献就是 $\sum_{1 < j \le i} ( \left [a_i \ne a_j \right ] 2 ^ {j-1} \times 2 ^ {n-i}) = 2 ^ {n-i}\sum_{1 < j \le i} \left [a_i \ne a_j \right ] 2 ^ {j-1}$。这个式子是很好算的，得到初始答案。

那修改怎么处理呢？  
我们考虑一次修改会对答案产生哪些变动。  
先考虑 $1 \le j < i$ 且 $ a_i \ne a_j$：  
对于 $i$ 的 flip 操作，$j$ 会损失 $2^{j-1} \times 2 ^{n-i}$ 的贡献，所有的 $j$ 一共损失 $2 ^ {n-i}\sum_{1 < j \le i} \left [a_i \ne a_j \right ] 2 ^ {j-1}$；
同理，翻转之后（$a_i \gets \neg a_i$，$a_i$ 不是原来的 $a_i$ 了）会加上 $2^{j-1} \times 2 ^{n-i}$ 的贡献，总共加上了。$2 ^ {n-i}\sum_{1 < j \le i} \left [a_i \ne a_j \right ] 2 ^ {j-1}$；

我们思考如何用数据结构优化这件事。  
我们要做的事情就是维护 $i$ 之后与 $a_i$ 不相等的下标 $j$ 的 $2^{j-1}$ 之和。  
可以开两个线段树 `tr[2]`（树状数组），这两个分别表示前缀中，$a_j=0$ 的 $2^{j-1}$ 之和和 $a_j=1$ 的 $2^{j-1}$ 之和。每一次 $i$ 修改 $0$ 到 $1$ 就是将 `tr[0]` 单点减 $2^{i-1}$，`tr[1]` 单点加 $2^{i-1}$。
$1$ 到 $0$ 同理。

算贡献变动就是将 $\sum_{1 < j \le i} \left [a_i \ne a_j \right ] 2 ^ {j-1}$ 转化成 `tr[a[i]^1]` 的前缀查询。

$j < i \le n$ 同理。

统一使用树状数组实现，后缀和的查询就是将下标关于 $[1,n]$ 的中点对称一下。

时间复杂度 $O(n + q \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)
#define multi_cases 1

#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
template<class T> bool vmax(T &a, T b) { return b > a ? a = b, true : false; }
template<class T> bool vmin(T &a, T b) { return b < a ? a = b, true : false; }
template<class T> void clear(T &x) { T().swap(x); }

#define int long long

const int N = 2e5+2, P = 998244353;
void reduce(int &a) { if(a >= P) a -= P; }
void enlarge(int &a) { if(a < 0) a += P; }
void vadd(int &a, int b) { a += b, reduce(a); }
void vsub(int &a, int b) { a -= b, enlarge(a); }

int pw[N];

char s[N];
int n, a[N];

struct BIT {
	int n, c[N];
	void init(int n = 0) {
		this->n = n;
		memset(c, 0, sizeof(int) * (n+1));
	}
	void add(int idx, int v) { for(; idx <= n; idx += idx & -idx) vadd(c[idx], v); }
	int query(int idx) {
		int res = 0;
		for(; idx; idx -= idx & -idx) vadd(res, c[idx]);
		return res;
	}
} pretr[2], suftr[2];

int calc() {
	int ans = pw[n] - 1, c[2] = { };
	for(int i = 1; i <= n; ++i) {
		vadd(ans, c[a[i] ^ 1] * pw[n-i] % P);
		vadd(c[a[i]], pw[i-1]);
	}
	return ans;
}

void Traveller() {
	scanf("%s", s+1);
	n = strlen(s+1);
	for(int i = 1; i <= n; ++i) a[i] = s[i] ^ 48;
	pw[0] = 1;
	for(int i = 1; i <= n; ++i) reduce(pw[i] = pw[i-1] << 1);
	
	pretr[0].init(n), pretr[1].init(n);
	for(int i = 1; i <= n; ++i) pretr[a[i]].add(i, pw[i-1]);
	suftr[0].init(n), suftr[1].init(n);
	for(int i = 1; i <= n; ++i) suftr[a[i]].add(n-i+1, pw[n-i]);
	
	int ans = calc(), q;
	scanf("%lld", &q);
	for(int i = 1, p; i <= q; ++i) {
		scanf("%lld", &p);
		
		vsub(ans, pw[n-p] * pretr[a[p] ^ 1].query(p) % P);
		pretr[a[p]].add(p, -pw[p-1] + P);
		
		vsub(ans, pw[p-1] * suftr[a[p] ^ 1].query(n-p+1) % P);
		suftr[a[p]].add(n-p+1, -pw[n-p] + P);
		
		a[p] ^= 1;
		
		vadd(ans, pw[n-p] * pretr[a[p] ^ 1].query(p) % P);
		pretr[a[p]].add(p, pw[p-1]);
		
		vadd(ans, pw[p-1] * suftr[a[p] ^ 1].query(n-p+1) % P);
		suftr[a[p]].add(n-p+1, pw[n-p]);
		
		printf("%lld ", ans);
	}
	puts("");
}

signed main() {
#ifdef filename
	FileOperations();
#endif
	
	signed _ = 1;
#ifdef multi_cases
	scanf("%d", &_);
#endif
	while(_--) Traveller();
	return 0;
}
```

---

