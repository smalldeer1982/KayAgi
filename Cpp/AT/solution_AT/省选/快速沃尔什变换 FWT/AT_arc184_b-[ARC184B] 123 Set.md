# [ARC184B] 123 Set

## 题目描述

给定一个正整数 $N$。有一个空集合 $S$，你可以进行如下操作任意次：

- 自由选择一个正整数 $x$。对于 $x,\ 2x,\ 3x$，如果它们不在 $S$ 中，则将它们加入 $S$。

请你求出，最少需要多少次操作，才能使得 $\{1,\ 2,\ \dots,\ N\} \subseteq S$。

## 说明/提示

## 限制

- $1 \leq N \leq 10^{9}$

## 样例解释 1

选择 $1,\ 2,\ 5,\ 7$，可以得到 $S = \{1,\ 2,\ 3,\ 4,\ 5,\ 6,\ 7,\ 10,\ 14,\ 15,\ 21\}$，满足条件。无法用 $3$ 次或更少的操作满足条件。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7```

### 输出

```
4```

## 样例 #2

### 输入

```
25```

### 输出

```
14```

# 题解

## 作者：rui_er (赞：25)

个人认为思维难点相同的三倍经验：[P3226 \[HNOI2012\] 集合选数](https://www.luogu.com.cn/problem/P3226)、[TFSETS - Triple-Free Sets](https://www.luogu.com.cn/problem/SP707)。区别在于状压 DP 的方法。

我们称不包含质因子 $2$ 和 $3$ 的数为 $2,3\texttt{-Free}$ 的。

对于 $[1,n]$ 内每个 $2,3\texttt{-Free}$ 的整数 $u$，可以列出以下的矩阵：

$$
\begin{bmatrix}
2^03^0u & 2^03^1u & \cdots & 2^03^qu & \cdots \\
2^13^0u & 2^13^1u & \cdots & 2^13^qu & \cdots \\
\vdots & \vdots & \ddots & \vdots & \ddots \\
2^p3^0u & 2^p3^1u & \cdots & 2^p3^qu & \cdots \\
\vdots & \vdots & \ddots & \vdots & \ddots \\
\end{bmatrix}
$$

我们只保留矩阵中不超过 $n$ 的元素，得到一个杨表。

例如，对于 $n=12,u=1$ 的情况，对应的杨表如下：

$$
\begin{bmatrix}
1 & 3 & 9 \\
2 & 6 \\
4 & 12 \\
\end{bmatrix}
$$

先考虑对于一个杨表，如何求出最少的操作次数，使得这个杨表中的所有数都在集合中。

容易发现，一次操作等价于选择一个数，把它、它右边、它下边共三个数覆盖，上述问题转化为最少选择多少个数，能覆盖整个杨表。

考虑轮廓线 DP。设 $f_{i,j,S}$ 表示现在考虑到第 $i$ 行第 $j$ 列的格子（下标从 $0$ 开始），轮廓线每个元素是否被覆盖的状态为 $S$ 的最小操作次数。轮廓线的定义如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/7b3q72ed.png)

初始状态 $f_{0,0,0}=0,f_{0,0,S}=+\infty\ (S\ne 0)$。对于每个格子 $(i,j)$ 和状态 $S$，若 $S$ 中表明 $(i,j)$ 已被覆盖，则可以进行一次操作，或者不进行任何操作；若未被覆盖，则必须进行一次操作。容易写出转移方程，可以将 $i,j$ 两维滚掉。

因此，对一个杨表求答案的时间复杂度 $O(\log_2(\frac{n}{u})\log_3(\frac{n}{u})\times2^{\log_3(\frac{n}{u})})=O((\frac{n}{u})^{\log_32}\log^2(\frac{n}{u}))=O((\frac{n}{u})^{0.64}\log^2(\frac{n}{u}))$。

显然，以每个 $2,3\texttt{-Free}$ 的 $u$ 作为杨表左上角，列出的元素互不相同。因此，答案即为每个 $2,3\texttt{-Free}$ 的 $u$ 作为杨表左上角的答案之和。

显然不能对于每个 $2,3\texttt{-Free}$ 的 $u$ 都求一遍答案。动用一下智慧，我们发现有大量的 $u$ 对应的杨表形状是一样的，答案自然也是一样的。我们懒得考虑具体有多少种杨表形状，但是至少 $\lfloor\frac{n}{u}\rfloor$ 相等的所有 $u$ 的杨表形状肯定一样。记忆化一下，如果 $\lfloor\frac{n}{u}\rfloor$ 与上一个杨表相同就不重复求答案，否则再跑轮廓线 DP 即可。

不会分析时间复杂度，但一看就不太大，不到 $5$ 秒就跑完了。

另外，官方题解的 DP 部分好像跟我不一样，官方题解似乎用了子集卷积，我并没有特别理解。而我使用轮廓线 DP 可以直接规避子集卷积的知识，做到了相同的复杂度。

代码：

```cpp
// Problem: B - 123 Set
// Contest: AtCoder - AtCoder Regular Contest 184
// URL: https://atcoder.jp/contests/arc184/tasks/arc184_b
// Memory Limit: 1024 MB
// Time Limit: 8000 ms
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

const int LOG2 = 30, LOG3 = 19, N = 1000000000, inf = 0x3f3f3f3f;

int n, btm, lim[LOG2], f[1 << LOG3], g[1 << LOG3], lst, mem, ans;
ll a[LOG2][LOG3];

void init(int x) {
    btm = 0;
    memset(lim, 0, sizeof(lim));
    a[0][0] = x;
    lim[0] = 0;
    rep(j, 1, LOG3 - 1) {
        a[0][j] = a[0][j - 1] * 3;
        if(a[0][j] > n) break;
        lim[0] = j;
    }
    rep(i, 1, LOG2 - 1) {
        a[i][0] = a[i - 1][0] * 2;
        if(a[i][0] > n) break;
        lim[i] = 0;
        ++btm;
        rep(j, 1, LOG3 - 1) {
            a[i][j] = a[i][j - 1] * 3;
            if(a[i][j] > n) break;
            lim[i] = j;
        }
    }
}

int solve() {
    rep(S, 0, (1 << LOG3) - 1) f[S] = +inf;
    f[0] = 0;
    rep(i, 0, btm) {
        rep(j, 0, lim[i]) {
            int U = (1 << (lim[i] + 1)) - 1;
            rep(S, 0, U) g[S] = +inf;
            if(j < lim[i]) {
                rep(S, 0, U) {
                    if((S >> j) & 1) {
                        chkmin(g[S ^ (1 << j)], f[S]);
                        chkmin(g[S | (1 << j) | (1 << (j + 1))], f[S] + 1);
                    }
                    else chkmin(g[S | (1 << j) | (1 << (j + 1))], f[S] + 1);
                }
            }
            else {
                rep(S, 0, U) {
                    if((S >> j) & 1) {
                        chkmin(g[S ^ (1 << j)], f[S]);
                        chkmin(g[S | (1 << j)], f[S] + 1);
                    }
                    else chkmin(g[S | (1 << j)], f[S] + 1);
                }
            }
            rep(S, 0, U) f[S] = g[S];
        }
    }
    return *min_element(f, f + (1 << (lim[btm] + 1)));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 1, n) {
        if(i % 2 != 0 && i % 3 != 0) {
            if(n / i != lst) {
                lst = n / i;
                init(i);
                ans += (mem = solve());
            }
            else ans += mem;
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：10)

考场上一直没画图，画完就会了，如何呢？

### Solution

考虑这样一张图：若 $2x\le n$，则 $x$ 向 $2x$ 连一条有向边；若 $3x\le n$，则 $x$ 向 $3x$ 连一条有向边。

我们先看一下这张图长什么样（以下为 $n=18$ 的情况）：

![](https://cdn.luogu.com.cn/upload/image_hosting/vrelp7ui.png)

可以发现，整张图由若干个类似最左边的结构组成，且每个结构之间相互独立。我们考虑每个结构的答案如何计算。

发现此时的问题是这样：

> 选出若干个点。一个点被覆盖当且仅当它被选中或者它的任意一个前驱被选中，求最小的选出点数。

这是好做的：由于每层至多 $\lfloor\log_3 n\rfloor+1\le 19$ 个节点，考虑直接状压 DP。

设 $f_{i,s}$ 表示第 $i+1$ 行以后的行已经全覆盖，且第 $i$ 的选中状态为 $s$。将转移写出来后发现转移就是一个超集 $\min$，可以类似 FWT 做。这部分的复杂度是 $O(2^{\log_3n}\log_2n\log_3n)=O(n^{\log_32}\log^2n)=O(n^{0.64}\log^2n)$。

我们再考虑如何合并结构的贡献，显然答案是所有结构答案的和。但枚举所有结构的复杂度显然爆炸。

注意到我们有很多个结构的贡献是相同的，而以 $x$ 为根的结构与以 $y$ 为根的结构贡献相同的充分条件是 $\lfloor\dfrac nx\rfloor=\lfloor\dfrac ny\rfloor$，于是我们可以在外面再套一个整除分块。

总的复杂度积一下是 $O(n^\frac {1+\log_32}2\log^2n)=O(n^{0.82}\log^2n)$ 的，但是快的神秘。打表可以做到 $O(\sqrt n)$ 或更低。

### Code

$O(n^{0.82}\log^2n)$ 的朴素实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=1e9+5,A=35,B=20;
int n,f[1<<B],g[1<<B],cnt[A];
void FWT(int *F,int n){
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=i<<1)
			for(int k=0;k<i;k++)
				F[j|k]=min(F[j|k],F[i|j|k]);
}
int solve(int n){
	int dep=0;
	for(int i=0;i<A;i++)cnt[i]=0;
	for(ll a=1,i=0;a<=n;a*=2,i++){
		dep=max(dep,(int)i);
		for(ll b=1,j=0;a*b<=n;b*=3,j++)
			++cnt[i+j];
	}
	for(int i=0;i<(1<<cnt[dep]);i++)
		f[i]=__builtin_popcount(i);
	for(int i=dep-1;i>=0;i--){
		int s1=1<<cnt[i],s0=1<<cnt[i+1],U=s0-1;
		FWT(f,s0);
		for(int j=0;j<s1;j++)
			g[j]=f[((j|(j<<1))&U)^U]+__builtin_popcount(j);
		for(int j=0;j<s1;j++)
			f[j]=g[j];
	}
	return f[1];
}
inline int calc(int x){return x-x/2-x/3+x/6;}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	int ans=0;
	for(int l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		ans+=(calc(r)-calc(l-1))*solve(n/l);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：liangbowen (赞：7)

[blog](https://www.cnblogs.com/liangbowen/p/18431855)。算是单杀 * 2800 了（虽然做过 [HNOI2012] 集合选数）。来写一个题解区复杂度最劣做法。

## 思路

考虑很多元素是可以分开处理的。例如 $\{1,2,3,4,6,9,\cdots\}$ 需要一起处理，而 $5,10$ 等数并不会影响到这个集合。

对于每一个集合，考虑构造如下矩阵：

$$\begin{matrix}x & 3x & 9x & 27x & \cdots\\2x & 6x & 18x & 54x & \cdots\\4x & 12x & 36x & 108x & \cdots\\8x & 24x & 72x & 216x & \cdots\\\vdots & \vdots & \vdots & \vdots\end{matrix}$$

就是 $a_{x,y}=2a_{x-1,y}=3a_{x,y-1}$，元素超出 $n$ 就停止（所以这个实际是楼梯状物）。

那么考虑转换后的问题：**选择一个 $(x,y)$，覆盖 $(x,y)(x+1,y)(x,y+1)$，求最少几次可以覆盖全部位置**。

并不好做。但是**这个东西的大小只有 $\log_2 10^9 \times \log_3 10^9=30\times19$**，所以可以暴力状压啦！

设 $dp_{i,s}$ 表示前 $i$ 行，当前行的选择状态为 $s$，最小次数。转移容易：

$$dp_{i,s}=\min(dp_{i-1,t})+1 \qquad \Large(\normalsize t\cup s\cup (s\texttt{ << }1)\Large)\normalsize\text{ cover this line}$$

```cpp
for (int s = 0, U = (1 << len[1]) - 1; s <= U; s++)
    if (((s | (s << 1)) & U) == U) dp[1][s] = __builtin_popcount(s); else dp[1][s] = 1e9;

for (int i = 2; i <= 30; i++)
    for (int s = 0, U = (1 << len[i]) - 1; s <= U; s++) {
        int qwq = 1e9;
        for (int t = 0; t < (1 << len[i - 1]); t++)
            if (((t | s | (s << 1)) & U) == U) qwq = min(qwq, dp[i & 1 ^ 1][t]);
        dp[i & 1][s] = qwq + __builtin_popcount(s);
    }

int ans = 2e9;
for (int s = 0; s < (1 << len[30]); s++) ans = min(ans, dp[0][s]);
return ans;
```

其中 $len_i$ 表示第 $i$ 行需要覆盖的长度。答案是所有集合贡献的和。

## 优化

呃这个代码 8s 只能跑 3e7，非常菜。考虑找小性质：

_C1：矩阵开头的数为 $6k+1$ 或 $6k+5$。原因显然。（其实就是无法整除 $2,3$ 的数。）_

_C2：对于 $a_{1,1}=x$ 且最大值为 $n$ 的矩阵，**等价于 $a_{1,1}=1$ 且最大值为 $\dfrac nx$ 的矩阵**。_

所以，记 $\operatorname{sol}(n)$ 表示 $a_{1,1}=1$ 且最大值为 $n$ 的矩阵的最小值，答案即为

$$\sum\limits_{i=6k+1\text{ 或 }6k+5}\operatorname{sol}(\dfrac ni)$$

这玩意可以很快枚举，但是求个 $\operatorname{sol}(10^9)$ 就要很久了，更别说其他的了啊？？？

_C3：**本质不同的矩阵只有极少个**。证明：最多只会有 $30\times 19$ 个元素，而随着 $n$ 变小，数量只会变小，因此本质不同的矩阵不超过 $570$ 个。实际只有 $300$ 个左右。_

依据这个，可以对矩阵的 $len_i$ 们**哈希**起来，然后**打表**直接获取所有可能的 hash 值对应的答案。

打表跑了一个小时。实现精细点其实可以快很多的 qwq（

---

[code](https://atcoder.jp/contests/arc184/submissions/58109261)。里面包含了打表程序与最终程序。

最终程序为 $O(n)$（或 $O(\sqrt n)$ 整除分块）。

---

## 作者：not_clever_syl (赞：4)

一眼题。

发现可以把 $1 \sim n$ 分成很多个类，其中每个类可以选择一个代表元 $x$ 满足 $x$ 中不含 $2,3$ 因子，我们把这个类记为 $S_x$，答案即为所有 $S_x$ 的答案和。

记 $maxnum(x)=\frac{\max_{u \in S_x}{u}}{x}$。

然后可以发现如果 $maxnum(x)=maxnum(y)$，那么 $S_x,S_y$ 这两个类所贡献的答案是一样的。

可以算出 $10^9$ 内不同的 $maxnum(x)$ 个数只有 $306$ 个。

于是我们可以算出 $maxnum(x)=i$ 的 $x$ 数量，然后乘上 $maxnum(x)=i$ 的答案，再加上答案。

记 $f(n)$ 表示 $1 \sim n$ 中不含 $2,3$ 因子的数的个数，$\operatorname{next}(n)$ 表示所有 $maxnum(x)$ 中最小的严格大于 $x$ 的数，那么对于 $maxnum(x)=i$ 的 $x$ 的数量，我们可以用 $f(\lfloor \frac{n}{x} \rfloor)-f(\lfloor \frac{n}{\operatorname{next}(x)} \rfloor)$ 算出。

这里根据容斥原理，可以知道 $f(n)=n-\lfloor \frac{n}{2} \rfloor - \lfloor \frac{n}{3} \rfloor + \lfloor \frac{n}{6} \rfloor$。

对于 $maxnum(x)=i$ 的答案，我们可以算出所有 $y=2^a3^b \leq i$。

然后考虑在网格图上把 $2^a3^b \leq i$ 的 $(a,b)$ 涂色，就可以发现这是一个阶梯状物，原问题相当于用最少的 L 形骨牌可重叠可超边界覆盖所有涂色点，一个放置在 $(x,y)$ 的骨牌可以覆盖 $(x,y),(x+1,y),(x,y+1)$。

这个东西明显可以使用状压 dp，设 $f_{i,S}$ 表示 dp 到 $a=i$，这一行 $S$ 中位置没有选。

那么 $f_{i+1,T}+\operatorname{popcount}(S)$ 可以转移给 $f_{i,(2^{cnt_i}-1)-(S|2S)}$，这里需要满足 $T \subset S$。

答案为 $f_{0,0}$。

转移使用高位前缀和优化，可以做到 $O(306 \times c_2 \times c_3 \times 2^{c_3})$，其中$c_2=\log_2{10^9},c_3=\log_3{10^9}$。

这个数看起来挺大的，所以可以打个表再算。

[AC code](https://atcoder.jp/contests/arc184/submissions/58032849)

---

## 作者：Purslane (赞：2)

# Solution

这个题都能紫 + *2800 吗。感觉最多二十分钟就可以想 + 写完啊。

显然每个数都可以写成 $k = 2^{\alpha}3^{\beta} \gamma$ 的形式，其中 $\gcd(\gamma,6)=1$。那么两个数 $a$ 和 $b$ 存在相互影响，当且仅当 $\gamma_a = \gamma_b$。

对于每个 $\gamma$，我们把他对应的 $k$ 找出来，并且按照 $(\alpha,\beta)$ 的形式描到二维平面上，形成了一个阶梯的形状。

我们问题就变为了：在每个阶梯上选一些关键点，使得每个点、它的左边、它的下面的格子中至少有一个被选中。

首先发现，阶梯的形状只受 $\lfloor \dfrac{n}{k} \rfloor$ 影响，所以可以整除分块。

对于每种阶梯，注意到它的较短边只有 $18$，因此可以对他进行状压，使用高维前缀和优化。

> 刚开始想用人脑处理这个最优化问题，发现人脑完全不够用啊 /ll

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=(1<<19)+10;
int n,ans,dp[2][MAXN];
int calc(int n) {return n-n/2-n/3+n/6;}
void get_pre(int op,int n) {
	ffor(i,0,n-1) roff(j,(1<<n)-1,0) dp[op][j]=min(dp[op][j],dp[op][j|(1<<i)]);
	return ;
}
int solve(int v) {
	int mul=1,len=1,lst;
	while(mul*3<=v) mul*=3,len++;
	lst=len;
	ffor(i,0,(1<<len)-1) {
		int anti=(1<<len)-1-i;
		if((anti&(anti<<1|1))==0) dp[0][i]=__builtin_popcount(i);
		else dp[0][i]=0x3f3f3f3f;
	}
	int tval=v/2,op=0;
	while(tval>=1) {
		op^=1,lst=len,get_pre(op^1,lst);
		len=1,mul=1;
		while(mul*3<=tval) mul*=3,len++;
		ffor(i,0,(1<<len)-1) {
			int anti=(1<<len)-1-i,need=anti&(anti<<1|1);
			dp[op][i]=dp[op^1][need]+__builtin_popcount(i);
		}
		tval/=2;
	}
	get_pre(op,len);
	return dp[op][0];
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	int l=1;
	while(l<=n) {
		int r=n/(n/l),mul=calc(r)-calc(l-1);
		ans+=mul*solve(n/l),l=r+1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Lgx_Q (赞：2)

考虑对于一个数 $x\in[1,n]$，我们可以写成 $x = 2^i3^jk$ 的形式，设 $S_k = \{x |x = 2^i3^jk\}$，可以发现对于两个不同的 $k_1,k_2$，$S_{k_1}$ 与 $S_{k_2}$ 互不相交且所有 $S_k$ 的并集恰好为 $\{1, 2, ..., n\}$。所以，我们可以枚举每个 $k$，独立计算答案。

设 $D_k = \{(i,j) | 2^i3^jk\le n\}$，发现对于不同的 $k$，$D_k$ 可以划分为 $|D_1|$ 个等价类，每个等价类内部的 $D$ 集合都相同。这样可以枚举每个等价类，计算有多少个 $D_k$ 属于该等价类，以及计算该等价类的答案，二者相乘即可。

计算一个等价类内部有多少个集合是容易的，发现每个等价类中的 $k$ 恰好是所有合法的 $k$ 的连续一段。可以找到 $k$ 的上下界 $[l,r]$，容斥计算出 $[l,r]$ 中不是 $2$ 也不是 $3$ 的倍数的数的个数即可。

剩下的问题为：对于一个 $D_k$，如何计算答案。考虑对于每个 $i(0\le i\le \lfloor \log_2 \frac nk\rfloor)$，设 $c_i = \max\{j | 2^i3^jk \le n\}$。

我们相当于考虑对于一个二元组 $(i,j)$，他是否被选择。如果 $(i,j),(i-1,j),(i,j - 1)$ 都不选则不合法，求最少需要选择多少个二元组。

这个可以状压 DP 解决：设 $dp[i,S]$ 表示考虑了 $(0...i,\_)$ 的二元组，且 $(i, 0...c_i)$ 是否被选的二进制状态为 $S$，此时的答案。转移考虑求出 $T$ 表示 $(i - 1,0...c_{i - 1})$，其中 $T$ 中的二元组必须选，这个可以超集求 $\min$ 解决。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define mkp make_pair
#define pir pair <ll, ll>
#define pb emplace_back
#define i128 __int128
using namespace std;
const ll maxn = 1010, inf = 1e12;
ll n, dp[32][1 << 20], popcnt[1 << 20];
ll sum[1 << 20], ans, c[1 << 20];
vector <ll> vec;
int main() {
	scanf("%lld", &n);
	for(ll S = 1; S < (1 << 20); S++)
		popcnt[S] = popcnt[S & (S - 1)] + 1;
	for(ll i = 0; (1 << i) <= n; i++)
		for(ll j = 0, x = 1; (x << i) <= n; x *= 3, ++j)
			vec.pb(x << i);
	sort(vec.begin(), vec.end());
	vec.pb(n + 1); memset(sum, 0x3f, sizeof sum);
	for(ll o = 0; o < vec.size() - 1; o++) {
		ll l = n / vec[o + 1], r = n / vec[o];
		ll lim = vec[o + 1] - 1, k = 0;
		ll tmp = r - r / 2 - r / 3 + r / 6
		- l + l / 2 + l / 3 - l / 6;
		for(ll i = 0; (1 << i) <= lim; i++) {
			ll j = 0, p = 1; k = i;
			while(((p * 3) << i) <= lim)
				++j, p *= 3;
			c[i] = j + 1;
		}
		for(ll S = 0; S < (1 << c[0]); S++) {
			ll T = ((1 << c[0]) - 1) ^ S;
			if((T & 1) || (T & (T << 1))) dp[0][S] = inf;
			else dp[0][S] = popcnt[S];
		}
		for(ll i = 1; i <= k; i++) {
			for(ll S = 0; S < (1 << c[i - 1]); S++)
				sum[S] = min(sum[S], dp[i - 1][S]);
			for(ll j = 0; j < c[i - 1]; j++)
				for(ll S = 0; S < (1 << c[i - 1]); S++)
					if(!(S & (1 << j)))
						sum[S] = min(sum[S], sum[S | (1 << j)]);
			for(ll S = 0; S < (1 << c[i]); S++) {
				ll T = ((1 << c[i]) - 1) ^ S;
				T = (T & (T << 1)) | (T & 1);
				dp[i][S] = sum[T] + popcnt[S];
			}
			for(ll S = 0; S < (1 << c[i - 1]); S++) sum[S] = inf;
		}
		ll w = inf;
		for(ll S = 0; S < (1 << c[k]); S++)
			w = min(w, dp[k][S]);
		ans += tmp * w;
	} printf("%lld", ans);
	return 0;
}
```

---

## 作者：forest114514 (赞：2)

没想到 ARC 还有类似的题，昨晚没打真是亏麻了。

我们把 $i$ 向 $2i$ 和 $3i$ 连边，不难 $1\sim n$ 的点的导出子图构成了若干阶梯网格。

然后对于每个网格图显然答案是独立的，分开算就好了，不过这个问题类似一个有向的最小点覆盖，直接做不太好做，不过注意网格图的长宽范围分别只有 $O(\log_{2}n)$ 和 $O(\log_3 n)$，其中 $\log_{3}n\leq 19$，可以考虑状压，这又是一个网格图，考虑轮廓线 DP，设 $f_{i,j,S}$ 表示现在考虑到 $i$ 行 $j$ 列，当前轮廓选择的状态是 $S$ 的最小代价，转移是容易的（好像有 FWT 的做法？）。

然后发现每个网格图的左上端点恰好是一个不含 $2,3$ 作为质因子的数，直接做数量是 $O(n)$ 的，每个数直接 DP 的复杂度只能过 $n=10^5$ 左右的级别，详见 **P3226 [HNOI2012] 集合选数**，不过还有一个显著的观察就是对于 $\lfloor\frac{n}{i}\rfloor$ 相同的 $i$，其网格图是同构的，所以只用套个数论分块对 $O(\sqrt n)$ 种网格图做即可，每个网格图大小为 $n$ 的复杂度是 ，$T(n)=O(2^{\log_{3}n}\log_{2}n\log _{3}n)=O(n^{0.63}\log^2 n)$，大概复杂度就是做 $O(\sqrt n)$ 次这个，不过每次时间不一样，不会分析，大概是 $O(n^{1-\epsilon}poly(\log n))$ 的级别，反正能过，不过我人傻常数大，跑了 4s。

[Submission](https://atcoder.jp/contests/arc184/submissions/58053752)

---

## 作者：Phartial (赞：1)

套路地将每个数表示成 $2^i \times 3^j \times r$ 的形式，其中 $r \perp 6$。显然我们可以将 $[n]$ 中的数根据 $r$ 划分成若干个互不干扰的独立集。只需单独对这些独立集求解即可。

以 $(i,j)$ 作为坐标，注意到每个独立集都形如一个长宽相当小的阶梯状矩形，在其上应用轮廓线 dp 即可得到一个 $\Theta(2^{\log_3 s}\operatorname{polylog}(s))$ 的做法，其中 $s$ 是这个独立集的大小，大概是 $\Theta(\frac{n}{r})$ 这个量级的。

显然对每个 $r$ 都跑一遍轮廓线 dp 不现实，但我们其实并不在乎 $r$ 的具体取值，而只在乎独立集的形态（或者说，大小），由于本质不同的独立集个数只有至多 $306$ 个，对每种形态的独立集跑一遍 dp 即可，算出现次数是简单的。

时间复杂度大概是什么 $\Theta(2^{\log_3 n}\operatorname{polylog}(n))$ 状物，反正跑得飞快。

[code](https://atcoder.jp/contests/arc184/submissions/58576733)。

---

## 作者：Kreado (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc184_b)。

## 思路

对于一个 $x$，若 $2x\le n$，连有向边 $(x,2x)$，若 $3x\le n$，连有向边 $(x,3x)$。

我们能得到若干个类似这样的有向图：

![](https://cdn.luogu.com.cn/upload/image_hosting/b26d4at9.png)

问题就转换成了在这若干个有向图中，每个有向图选出最少的点使得所有点被覆盖，覆盖一个点的定义为选中了这个点或者这个点的某个前驱被选中。

不妨考虑一个图的时候，可以发现如下性质：

- 两个点 $x,y$ 在同一层当且仅当 $v_2(x)+v_3(x)=v_2(y)+v_3(y)$。

- 一个点 $x$ 为根节点当且仅当 $2\nmid x,3\nmid x$。

- 两个有向图同构，假设两个图根节点为 $x,y$，那么一定有 $\lfloor\frac{n}{x}\rfloor=\lfloor\frac{n}{y}\rfloor$。

根据上述性质，容易发现一个有向图中一层的节点数是很少的，不会超过 $19$，且层数也很小。

那么大体思路就出现了，对 $n$ 数论分块，求出区间 $[l,r]$ 中有多少个根节点，并乘上其对应的答案。

对于每个根节点，考虑状压 DP，令 $f_{i,S}$ 表示第 $i$ 层，状态为 $S$（即 $S$ 集合中的点被选中），显然有转移 $f_{i,S}=\min(\min\limits_{T\subseteq U\oplus S}f_{i+1,T},\min\limits_{T\subseteq U\oplus (S<<1)}f_{i+1,T})+\mathrm{popcount}(S)$。

这个可以用 FWT 优化，然后就做完了。

---

## 作者：Petit_Souris (赞：0)

口胡一个先，没做过那个思想类似的原题，想了得有四十分钟吧，不是简单题。

将每个数分解成 $2^x3^yz$ 的形式，平铺在一个平面上，向下 $\times 3$，向右 $\times 2$，会形成一个杨表状物：

![](https://cdn.luogu.com.cn/upload/image_hosting/i8kl097j.png)

每个不同的 $x=0,y=0$ 的数对应一个不同的左上角，所以 $1\sim n$ 会被分成很多个杨表。

考虑 $x,2x,3x$ 在杨表上的形态，发现这就是一个 L 字形状物，而题目要求的就是用最少的 L 形覆盖所有杨表。可以对每个杨表独立求解，用轮廓线 dp 求答案即可，状压比较短的那端（$3$ 的次幂），状态数不会很多（$\lfloor\log_3 10^9\rfloor=19$）。

但是现在对每个杨表都求解一遍复杂度无论如何也不会低于 $\mathcal O(n)$，不能接受。观察到 $\lfloor\frac{n}{z}\rfloor$ 相同的 $z$ 对应的杨表形态相同，于是套一个整除分块就行了。复杂度看起来比较难以表示，但是应该是能过的。


通过了，补个代码：

```cpp
#pragma GCC optimize(2,3,"Ofast","inline","unroll-loops")
#include<bits/stdc++.h>
typedef int ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
ll n,f[2][(1<<20)+9];
ll Getlen(ll x){
    ll p=1,c=0;
    while(p*3<=x)p*=3,c++;
    return c;
}
ll solve(ll t){
    ll v=n/t,p=1,Len=Getlen(v)+1;
    rep(i,0,1){
        rep(j,0,(1<<Len))f[i][j]=1e9;
    }
    f[0][0]=0;
    ll cur=0;
    while(p<=v){
        ll curlen=Getlen(v/p)+1;
        rep(i,0,curlen-1){
            rep(j,0,(1<<Len))f[cur^1][j]=1e9;
            rep(j,0,(1<<Len)-1){
                if(f[cur][j]==(ll)1e9)continue;
                if((j>>i)&1){
                    f[cur^1][j^(1<<i)]=min(f[cur^1][j^(1<<i)],f[cur][j]);
                    if(i<curlen-1)f[cur^1][j|(1<<(i+1))]=min(f[cur^1][j|(1<<(i+1))],f[cur][j]+1);
                    else f[cur^1][j]=min(f[cur^1][j],f[cur][j]+1);
                }
                else {
                    if(i<curlen-1)f[cur^1][j|(1<<i)|(1<<(i+1))]=min(f[cur^1][j|(1<<i)|(1<<(i+1))],f[cur][j]+1);
                    else f[cur^1][j|(1<<i)]=min(f[cur^1][j|(1<<i)],f[cur][j]+1);
                }
            }
            cur^=1;
        }
        p*=2;
    }
    ll ans=1e9;
    rep(i,0,(1<<Len)-1)ans=min(ans,f[cur][i]);
    return ans;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    ll l=1,ans=0;
    while(l<=n){
        ll r=n/(n/l),cnt=r-l+1-(r/2-(l-1)/2)-(r/3-(l-1)/3)+(r/6-(l-1)/6);
        if(!cnt){
            l=r+1;
            continue;
        }
        ll t=l;
        while(t%2==0||t%3==0)t++;
        ans+=solve(t)*cnt;
        l=r+1;
    }
    write(ans);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：0)

# [My Blogs]()

### [[ARC184B] 123 Set](https://www.luogu.com.cn/problem/AT_arc184_b)

首先一个最基本的性质是如果 $x$ 不是 $2$ 或者 $3$ 的倍数则 $x$ 一定会被操作。基于这个简单观察，可以进一步的发现：取出所有不是 $2,3$ 的倍数的数 $x$，则对于不同的 $x$，$2^i3^jx$ 之间是没有关系的。所以可以对于不同的 $x$ 分别处理。

考虑操作了 $x$ 之后可以覆盖掉 $2x,3x$，很深刻的想法是看成一个矩形，左上角是 $x$，每向右一格 $\times 3$，每向下一格 $\times 2$。显然对于一个 $x$ 如果只保留 $\leq n$ 的表中的数，则其随着行数的增加，列数在减小。这是一个杨表，而操作一个数相当于把格子 $(i,j),(i,j+1),(i+1,j)$ 覆盖，而要求的就是用尽量少的操作数把这个杨表全都覆盖。

因为列数不会很多（最多 $19$ 列，$3^{19}>10^9$），所以可以直接轮廓线 DP，状压记录轮廓线上的每个格子是否被操作了，转移也比较简单。

如何计算最终答案？考虑计算每个杨表对应了多少个 $x$。把杨表中的数从小到大加入，设其中最大的数是 $v_i$，则其对应了 $\lfloor\frac n{v_i}\rfloor-\lfloor \frac n{v_{i+1}}\rfloor$。而不同杨表的个数显然不会太多，对每个暴力求就能过，当然也可以进行打表。

```cpp
int n;
int f[2][20][1<<19];
int a[31],pw2[40],pw3[40];
inline int solve()
{
	for(int i=0;i<2;++i)for(int j=0;j<=a[1];++j)
	for(int k=0;k<(1<<a[1]);++k)f[i][j][k]=inf;
//		for(int i=1;i<=30;++i)write(a[i]);
//		puts("");
	int now=1,pre=0;
	f[0][0][0]=0;
	for(int i=1;i<=31;++i)
	{
		swap(now,pre);
		if(!a[i])return f[now][0][0];
		for(int j=0;j<a[i];++j)
		{
			for(int k=0;k<(1<<a[i]);++k)
			{
				int lef=j?((k>>(j-1))&1):0,up=(k>>j)&1;
				if(lef|up)Mmin(f[now][j+1][k&(~(1<<j))],f[now][j][k]);
				Mmin(f[now][j+1][k|(1<<j)],f[now][j][k]+1);
			}
		}
		for(int j=0;j<=a[i+1];++j)
		{
			for(int k=0;k<(1<<a[i+1]);++k)
			f[pre][j][k]=inf;
		}
		int lim=(1<<a[i+1])-1;
		for(int k=0;k<(1<<a[i]);++k)
		Mmin(f[pre][0][k&lim],f[now][a[i]][k]);
	}
	assert(0);
	return 0;
}
inline int get(int x){return x-x/2-x/3+x/6;}
int F[500]={
	//...
};
inline void mian()
{
	vt ve;
	read(n);
	pw2[1]=pw3[1]=1;
	for(int i=2;i<=34;++i)pw2[i]=pw2[i-1]*2;
	for(int i=2;i<=22;++i)pw3[i]=pw3[i-1]*3;
	for(int i=1;pw2[i]<=n;++i)
	{
		for(int j=1;pw2[i]*pw3[j]<=n;++j)
		ve.eb(tup(pw2[i]*pw3[j],i,j));
	}
//		exit(0);
	sort(ve.begin(),ve.end(),[&](tup x,tup y){return x.x<y.x;});
	ve.eb(tup(n+1,0,0));
	int ans=0;
	for(int i=0;i<(int)ve.size()-1;++i)
	{
		int tmp=get(n/ve[i].x)-get(n/ve[i+1].x);
		a[ve[i].y]=ve[i].z;
		//F[i]=solve()
		ans+=tmp*solve();
	}
	write(ans);
}
```

---

## 作者：xwh_Marvelous (赞：0)

不难发现操作只对一个数 $2$ 和 $3$ 的指数部分有影响。于是对于若干形如 $C2^a3^b$ （$C$ 满足不被 $2$ 和 $3$ 整除）的数，可以根据 C 分成若干子问题。

现在变成了给点上界 $\left\lfloor \frac N C \right\rfloor$ 求将所有 $2^a3^b$ 这样的数选进集合所花的代价。

记 $f_{i,S}$ 表示 $2$ 的指数选到第 i 位，对于 $a<i$ 已经全部选完，对于 $a=i$，所有 $b\in S$ 已经被选了的最小代价。

发现有个集合有交并，枚一下子集变无交并会快一些。

复杂度大概是 $O(2^{\log_3(N/C)}\log_3(N/C)\log_2 (N/C))$。

最后套个类整除分块的东西就行了。

复杂度 $O(能过)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define mod 1000000007
//#define N 200005
//#define pii pair<int,int>
//#define fi first
//#define se second
//#define rep(i,j,k) for(int i=j;i<=k;i++)
#define inf 0x3f3f3f3f3f3f3f3f
#define popc __builtin_popcount
int n;
int f[32][1<<21];
int cr,tot;
int ans;
void work(int *f,int n){
	for(int j=(1<<n)-1;~j;j--)
		for(int i=0;i<n;i++)
			f[j&(~(1<<i))]=min(f[j],f[j&(~(1<<i))]);
}
void sol(int n){
	int u=0,v=0;
	int op=1;
	while(op<=n)u++,op*=2;
	op=1;
	while(op<=n)v++,op*=3;
	for(int i=0;i<=u+1;i++){
		for(int j=0;j<(1<<(v+1));j++)f[i][j]=inf;
	}
	f[0][0]=0;
	for(int i=0,k=1;i<=u;i++,k<<=1){
		int p=0;
		op=1;
		while(op<=n/k)p++,op*=3;
		int u=(1<<p)-1;
		for(int s=0;s<(1<<(p+1));s++)f[i][s&u]=min(f[i][s&u],f[i][s]);
		work(f[i],p);
		for(int s=0;s<(1<<p);s++){
			int o=((s<<1)|s);
			o&=u;
			o^=u;
			f[i+1][s]=min(f[i+1][s],f[i][o]+popc(s));
		}
	}
	tot=inf;
	for(int i=0;i<(1<<v);i++)tot=min(f[u][i],tot);
	cr=n;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i+=6){
		int x;
		x=i;
		if(x>n)break;
		if(cr!=(n/x))sol(n/x);
		ans+=tot;
		x=i+4;
		if(x>n)break;
		if(cr!=(n/x))sol(n/x);
		ans+=tot;
	}
	cout<<ans;
	return 0;
}
```

---

