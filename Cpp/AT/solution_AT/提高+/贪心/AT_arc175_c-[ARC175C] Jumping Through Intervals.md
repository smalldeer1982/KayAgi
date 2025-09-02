# [ARC175C] Jumping Through Intervals

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc175/tasks/arc175_c

$ N $ 個の整数組 $ (L_1,\ R_1),\ (L_2,\ R_2),\ \dots,\ (L_N,\ R_N) $ が与えられます．ここで，全ての $ 1\leq\ i\leq\ N $ に対して $ L_i\ \leq\ R_i $ が満たされています．

$ N $ 個の整数からなる列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ であって，以下の条件を満たすものを**良い整数列**と呼びます．

- 全ての $ 1\leq\ i\leq\ N $ に対して，$ L_i\ \leq\ A_i\ \leq\ R_i $ である．
 
$ \displaystyle\ \sum_{i\ =\ 1}^{N-1}\ |A_{i+1}\ -\ A_{i}| $ を最小にするような**良い整数列** $ A $ のうち，辞書順で最小のものを求めてください．

  数列の辞書順とは数列 $ S\ =\ (S_1,S_2,\ldots,S_{|S|}) $ が数列 $ T\ =\ (T_1,T_2,\ldots,T_{|T|}) $ より**辞書順で小さい**とは，下記の 1. と 2. のどちらかが成り立つことを言います． ここで，$ |S|,\ |T| $ はそれぞれ $ S,\ T $ の長さを表します．

1. $ |S|\ \lt\ |T| $ かつ $ (S_1,S_2,\ldots,S_{|S|})\ =\ (T_1,T_2,\ldots,T_{|S|}) $．
2. ある整数 $ 1\ \leq\ i\ \leq\ \min\lbrace\ |S|,\ |T|\ \rbrace $ が存在して，下記の $ 2 $ つがともに成り立つ． 
  - $ (S_1,S_2,\ldots,S_{i-1})\ =\ (T_1,T_2,\ldots,T_{i-1}) $．
  - $ S_i $ が $ T_i $ より（数として）小さい．

## 说明/提示

### 制約

- 入力される数値は全て整数
- $ 2\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ 0\ \leq\ L_i\ \leq\ R_i\ \leq\ 10^9 $
 
### Sample Explanation 1

$ (A_1,\ A_2,\ A_3,\ A_4)\ =\ (8,\ 8,\ 4,\ 5) $ は良い整数列です．このとき $ \sum_{i\ =\ 1}^{N-1}\ |A_{i+1}\ -\ A_{i}|\ =\ |8\ -\ 8|\ +\ |4\ -\ 8|\ +\ |5\ -\ 4|\ =\ 5 $ となり，これが $ \sum_{i\ =\ 1}^{N-1}\ |A_{i+1}\ -\ A_{i}| $ の最小の値です．

### Sample Explanation 2

$ \sum_{i\ =\ 1}^{N-1}\ |A_{i+1}\ -\ A_{i}| $ が最小となる良い数列 $ A $ が複数あるときは，そのうち辞書順で最小のものを出力することに注意してください．

## 样例 #1

### 输入

```
4
1 10
8 13
3 4
5 20```

### 输出

```
8 8 4 5```

## 样例 #2

### 输入

```
3
20 24
3 24
1 75```

### 输出

```
20 20 20```

## 样例 #3

### 输入

```
15
335279264 849598327
446755913 822889311
526239859 548830120
181424399 715477619
342858071 625711486
448565595 480845266
467825612 647639160
160714711 449656269
336869678 545923679
61020590 573085537
626006012 816372580
135599877 389312924
511429216 547865075
561330066 605997004
539239436 921749002```

### 输出

```
526239859 526239859 526239859 467825612 467825612 467825612 467825612 449656269 449656269 449656269 626006012 389312924 511429216 561330066 561330066```

# 题解

## 作者：rui_er (赞：11)

先不考虑构造字典序最小的方案，只考虑求出最小的 $\sum\limits_{i=1}^{N-1}|A_{i+1}-A_i|$。

设定义域为 $[L_i,R_i]$ 的函数 $F_i(x)$ 表示考虑后缀 $[i,N]$，令 $A_i=x$ 时上式最小的值。

初值为 $F_N(x)=0,(x\in[L_N,R_N])$。

显然有转移方程：

$$
F_i(x)=\min\limits_{y=L_{i+1}}^{R_{i+1}}\{F_{i+1}(y)+|x-y|\}
$$

赛时我做到这里之后，发现是加绝对值和取 $\min$ 的操作，便思考是否可以用类似于 [Slope Trick](https://www.cnblogs.com/ruierqwq/p/18017106/slope-trick) 的方法维护之。

之后，我注意到：$F_i(x)$ 的函数图象一定形如一段斜率为 $-1$ 的线段、一段斜率为 $0$ 的线段和一段斜率为 $+1$ 的线段拼接得到的分段函数。于是，自然地，维护 $f_i,g_i$ 表示斜率为 $-1$ 和 $0$ 的分界点、斜率为 $0$ 和 $+1$ 的分界点。

最后考虑构造出字典序最小的方案。显然 $A_1=f_1$。之后枚举 $i$ 从 $2$ 到 $N$，若 $A_{i-1} < L_i$，显然需要 $A_i=L_i$；若 $A_{i-1} > g_i$，则令 $A_i=g_i$；否则令 $A_i=A_{i-1}$ 即可。

```cpp
// Problem: C - Jumping Through Intervals
// Contest: AtCoder - AtCoder Regular Contest 175
// URL: https://atcoder.jp/contests/arc175/tasks/arc175_c
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

const ll N = 5e5 + 5, inf = 0x3f3f3f3f3f3f3f3fll;

ll n, L[N], R[N], f[N], g[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 1, n) cin >> L[i] >> R[i];
    f[n] = L[n];
    g[n] = R[n];
    per(i, n - 1, 1) {
        f[i] = f[i + 1];
        g[i] = g[i + 1];
        chkmax(f[i], L[i]);
        chkmax(g[i], L[i]);
        chkmin(f[i], R[i]);
        chkmin(g[i], R[i]);
    }
    // rep(i, 1, n) cout << f[i] << " " << g[i] << endl;
    ll val = f[1];
    cout << val << " ";
    rep(i, 1, n - 1) {
        if(val < L[i + 1]) {
            val = L[i + 1];
        }
        else if(val > g[i + 1]) {
            val = g[i + 1];
        }
        cout << val << " \n"[i == n - 1];
    }
    return 0;
}
```

---

## 作者：robinyqc (赞：5)

先构造最优解，再构造字典序最小。

可以发现，假设起始点确定，很容易得到最优解：$A_{i + 1}$ 应该尽量接近 $A_i$。因为如果多了，要么不影响，下一步会少走；要么变劣，要走回路。

一个形象的情景类比这个过程：有 $N$ 层楼，每层都是实心的地板，只有 $[L_i, R_i]$ 是空的可以通过。水从最高层流下。水从 $A_i$ 流下到下一层。

确定起始点也是不难的：如果能不碰到地板，就不碰；如果一定要碰到，就尽量接近。再往后就是固定路线了。

这个过程可以取交集（这样一直不碰到地板）直到为空集。设此时上一步交集为 $[l, r]$，当前可选区间为 $[L, R]$，因为没有交集，所以若 $l > R$ 则起始点选 $R$，否则选 $L$。

得到最优解 $A$ 后，调整为字典序最小：

1. 如果下一层能够往左（$A_{i + 1}$ 可以调整更小），那么 $A_i$ 自然可以调整到更小；
2. 如果 $A_{i + 1} < A_i$，那么$A_i$ 也可以调整到更小。

但如果从 $1$ 到 $n$，我不知道 $A_{i + 1}$ 能不能调整到更小。因此从 $n$ 到 $1$ 调整即可。并且，1 条件可以省略。

### 代码实现

```cpp
#include <iostream>
#include <vector>
using namespace std;

signed main() 
{
    int n;
    cin >> n;
    vector<pair<int, int>> s(n);
    for (auto &[l, r] : s) cin >> l >> r;
    auto [l1, r1] = s[0];
    int x = -1;
    for (auto [l, r] : s) {
        if (r < l1) { x = l1; break; }
        else r1 = min(r1, r);
        if (l > r1) { x = r1; break; }
        else l1 = max(l1, l);
    }
    if (x == -1) x = l1;
    vector<int> raw;
    raw.reserve(n);
    for (auto [l, r] : s) {
        if (x > r) x = r;
        if (x < l) x = l;
        raw.emplace_back(x);
    }
    for (int i = n - 2; i >= 0; i--) {
        if (raw[i] > raw[i + 1]) raw[i] = max(raw[i + 1], s[i].first);
    }
    for (int i : raw) cout << i << ' ';
    return 0;
}
```

---

## 作者：Eraine (赞：4)

编号：AT_arc175_c

tag：贪心

难度：*2116

有点麻烦的贪心。感觉实际难度不止 *2116。但应该是我的方法相对劣。

一场 ARC 前四题都是贪心或结论题是怎么会事啊！！！

设 $f_i$ 为当前答案。

我们先不管字典序最小这一限制条件，只考虑最小化 $\sum_{i=1}^{n-1}\left|a_{i+1}-a_i\right|$。

考虑如下构造答案。

$$
a_i=
\begin{cases}
L_1 &\text{if }i=1
\\
a_{i-1} &\text{if }a_{i-1}\in[L_i,R_i]
\\
L_i &\text{if }L_i\gt a_{i-1}
\\
R_i &\text{if }R_i\lt a_{i-1}
\end{cases}
$$

设这种构造方法为 $\delta$。

这样得到的序列可以看做是若干段上升序列和下降序列交替拼接而成。我们定义 **山峰** 为前面第一个与 $a_i$ 不同的元素 $a_j$ 和后面第一个与 $a_i$ 不同的元素 $a_k$ 使得 $a_j\lt a_i,a_k\lt a_i$。定义 **山谷** 为前面第一个与 $a_i$ 不同的元素 $a_j$ 和后面第一个与 $a_i$ 不同的元素 $a_k$ 使得 $a_j\gt a_i,a_k\gt a_i$。若有多个山峰或山谷，则取最靠左的一个。特别地，若 $i=1$ 或 $i=n$ 只需判断有数值的一遍即可。

设 $a_1$ 到第一个山峰之间的序列为序列 $S$，其余元素为序列 $T$。

通过观察样例 $1$ 很容易发现，对于 $S$ 中的段不满足绝对值差最小。那么我们对 $S$ 进行微调。若要使得绝对值差最小且保持序列不降，则要使得 $a_1$ 尽量大。逆序遍历序列，找到最大的 $a_1$，然后再次正序遍历，按照构造方法 $\delta$ 调整序列 $S$。

易证序列 $T$ 满足相邻元素绝对值差之和最小。容易发现经过这样构造出来的答案序列中山峰一定是 $L_i$，山谷一定是 $R_i$。对于一个山峰 $a_i$，有 $a_{i-1}\lt a_i$，根据构造方法，$L_i\gt a_{i-1}$，则条件 $a_i=L_i$ 必然满足。山谷同理。

贪心地想，对于一个山峰，$a_i$ 值是可取值范围内最小的元素，若取其他元素一定大于原来的 $a_i$，又由于上一段上升序列和下一段下降序列紧挨着此山峰，所以只要取其他元素都会使得答案增大。证得山峰和山谷一定是满足相邻元素差的绝对值之和最小的。

那么对于序列 $T$ 中非山峰山谷元素，可以看做相邻山峰 $i$ 山谷 $j$ 间的一段连续的元素，这些元素满足单调上升或单调下降，得到的差的绝对值之和必定是 $\left|a_i-a_j\right|$。故也满足条件。

对于序列 $S$，由于 $S$ 的最后一个元素必然是山峰，而 $a_1$ 作为整段上升序列的一个最小元素（可视为山谷）最大，那么也可以类似序列 $T$ 的证法证明。

那么此时构造出来的 $a$ 序列已经满足 $\sum_{i=1}^{n-1}\left|a_{i+1}-a_i\right|$ 的条件，考虑最小化。

对于 $a$ 序列的所有上升连续子序列，由于山谷和山峰无法变动，构造方法是尽量往最小的元素构造，显然符合字典序最小。

对于 $a$ 序列的所有下降连续子序列，观察样例 $3$ 的答案序列下降部分，我们发现构造方法是错的。同上升序列，下降序列部分的构造方法会使得字典序最大。考虑对于每个下降序列从后往前调整，按照构造方案 $\delta$ 调整。由于每个元素 $a_i$ 调整后都是符合相邻元素差绝对值之和最小的条件且最小的元素（证明见下文），所以满足字典序最小的条件。

综上，无论对于上升序列还是下降序列均满足子段字典序最小，所以总序列字典序最小。构造方案正确。

$\Theta(n)$。

[submission](https://atcoder.jp/contests/arc175/submissions/51653182)

**附：下降子序列根据构造方案 $\delta$ 得到每个元素都是在符合条件区间中最小元素的证明：**

不用管山峰山谷，因为它们的值是固定的。

假设还有更小的 $b_i\lt a_i$，分两种情况讨论：

$a_i\gt a_{i+1}$，则根据构造方案易得，$a_i=L_i$，可知 $b_i\lt L_i$，不满足条件。

$a_i=a_{i+1}$，则 $b_i\lt a_{i+1}$，这明显不满足下降序列的要求（会使得相邻元素差绝对值之和不是最小）。

假设不成立，结论成立。

各位看官点个赞再走吧 qwq

---

## 作者：StarPatrick (赞：3)

提供一种不需要脑子的做法。

首先考虑如果我们已经确定了 $A_1$，那么我们可以贪心地得到 $ \sum_{i\ =\ 1}^{N-1}\ |A_{i+1}\ -\ A_{i}| $，也就是能使每相邻两个差最小，**能一样就取一样**，**不能一样就取边界**。

那么我们接下来考虑如何确定 $A_1$。$A_1$ 的取值显然只能从 $L,R$ 中出现过的数字中选，枚举，然后算出 $ \sum_{i\ =\ 1}^{N-1}\ |A_{i+1}\ -\ A_{i}| $ ，取最小的就行了。

这样暴力的话复杂度是 $O(n^2)$ 的，考虑优化求 $ \sum_{i\ =\ 1}^{N-1}\ |A_{i+1}\ -\ A_{i}| $ 的过程，我们发现如果在某个位置 $x$ 我们进行了 **“不能一样就取边界”** 的操作，那么之后的贡献我们就可以仅仅通过 $x$ 确定了，这启示我们使用记忆化搜索，或者 dp。

再考虑 **“能一样就取一样”** 这部分，由于没有贡献，因此可以直接二分 + ST 表直接跳到下一个 **“不能一样就取边界”**，配合记忆化搜索算答案即可。

得到 $A_1$ 后，通过前面的贪心得到的方案也许并不是字典序最小的，例如 $L_1=3,R_1=3,L_2=1,R_2=3,L_3=1,R_3=1$，我们选择了 $A_1=3$，那么我们得到的序列就是 $3,3,1$，然而我们显然可以调整成 $3,1,1$，具体调整方法从后往前，能小就小，比较显然。

具体操作可以看代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e6;
int n, d[MAXN+5], tot, print[MAXN+5];
ll dp[MAXN+5][2];
struct e{
	int l, r;
}a[MAXN+5], b[25][MAXN+5];
e merge(e x, e y) {//求区间交 
	return {max(x.l, y.l), min(x.r, y.r)};
}
e get(int l, int r) {//求[l,r]内的区间的区间交 
	int k = __lg(r-l+1);
	return merge(b[k][l], b[k][r-(1<<k)+1]);
}
int f(int l, int r, int x, int st) {
	if (l==r) return l;
	int mid = (l+r)/2+1;
	e temp = get(st, (l+r)/2+1);
	if (x>=temp.l&&x<=temp.r) return f(mid, r, x, st);
	else return f(l, mid-1, x, st);
}
ll dfs(int i, bool flag) {//flag为0表示从Li出发对答案的贡献，为1表示从Ri出发对答案的贡献 
	if (i==n) return 0;
	if (dp[i][flag]!=-1) return dp[i][flag];
	int x;
	if (!flag) x = a[i].l;
	else x = a[i].r;
	int j = f(i, n, x, i+1);
	if (j==n) return dp[i][flag]=0;
	if (x>a[j+1].r) return dp[i][flag]=dfs(j+1, 1)+x-a[j+1].r;
	else return dp[i][flag]=dfs(j+1, 0)+a[j+1].l-x;
}
int main() {
	memset(dp, -1, sizeof(dp));
	scanf("%d", &n);
	for (int p=1;p<=n;p++) {
		scanf("%d %d", &a[p].l, &a[p].r);
		d[++tot] = a[p].l;
		d[++tot] = a[p].r;//把出现过的数字存下来 
		b[0][p] = a[p];
	}
	for (int i=1;(1<<i)<=n;i++) {//st表 
		for (int j=1;j+(1<<i)-1<=n;j++) {
			b[i][j] = merge(b[i-1][j], b[i-1][j+(1<<i-1)]);
		}
	}
	ll ans = 1e18;
	int place;
	for (int p=1;p<=tot;p++) {//枚举 
		if (d[p]>=a[1].l&&d[p]<=a[1].r) {
			int i = f(1, n, d[p], 2);
			ll u = 0;
			if (i==n) u = 0;
			else if (d[p]>a[i+1].r) u = dfs(i+1, 1)+d[p]-a[i+1].r;
			else u = dfs(i+1, 0)+a[i+1].l-d[p];
			if (u<ans||(u==ans&&d[p]<place)) {//取最小 
				ans = u;
				place = d[p];
			}
		}
	}
	int now = place;
	for (int p=1;p<=n;p++) {
		if (now>a[p].r) now = a[p].r;
		if (now<a[p].l) now = a[p].l;
		print[p] = now; 
	}
	for (int p=n-1;p>=1;p--) {
		print[p] = max(min(print[p], print[p+1]), a[p].l);//调整字典序 
	}
	for (int p=1;p<=n;p++) {
		printf("%d ", print[p]);
	}
	return 0;
}
```

---

## 作者：zhengjinyi (赞：2)

题解区好像很多人都想复杂了。本题代码实现非常简短。\
考虑构造 $S=\sum\limits_{i=1}^{N-1}|A_{i+1}-A_i|$ 最小的合法序列 $A$。\
有一个很简单的贪心：在 $A_1$ 确定之后，往后每一位能不动就不动，触碰到边界再改变。\
具体地，先将 $a_i$ 赋值为 $\max(a_{i-1},l_i)$，再赋值为 $\min(a_i,r_i)$。\
然而这样会导致一些位置本来可以取更小值而没有取到。\
考虑另一种简单贪心：从 $A_n$ 开始往前填数。显然单独使用与前一种贪心等价，但是考虑将两种贪心结合起来：\
设第一次在位置 $i$ 填的数是 $f_{i,0}$，第二次是 $f_{i,1}$。不妨设 $f_{i,0}\le f_{i,1}$。发现满足 $S$ 最小的解的序列 $A$ 中，一定满足 $A_i\in [f_{i,0},f_{i,1}]$，证明如下：\
在 $A_1$ 或 $A_n$ 确定的情况下，我们所填的 $f_{i,0},f_{i,1}$ 一定是某个 $L_i$ 或 $R_i$。当正向填的 $f_{i,0}$ 不是最小解时，往后一定有某个在反向遍历中更新了 $f_{j,1}$ 的 $L_j<f_{i,0}$，否则“更优解”从比 $f_{i,0}$ 大的方向来，$S$ 会更大。此时应填 $f_{i,1}=f_{j,1}$。反之亦然。\
现在只需考虑求出 $A_1$ 与 $A_n$ 即可。发现正向跑一遍贪心得到的 $A_n$ 一定满足 $S$ 最小，于是跑三遍贪心即可。\
Code：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb emplace_back
#define R read()
using namespace std;
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x;
}
const int INF=0x3f3f3f3f,N=500005;
int n,l[N],r[N],a[N],w[N][2];
int main(){
	n=R;
	for(int i=1;i<=n;i++)
		l[i]=R,r[i]=R;
	int x=0;
	for(int i=1;i<=n;i++)
		x=max(x,l[i]),x=min(x,r[i]);
	for(int i=n;i;i--)
		x=max(x,l[i]),x=min(x,r[i]),w[i][0]=x;
	for(int i=1;i<=n;i++)
		x=max(x,l[i]),x=min(x,r[i]),w[i][1]=x;
	for(int i=1;i<=n;i++)
		printf("%d ",min(w[i][0],w[i][1]));
	return 0;
}
```

---

## 作者：Sorato_ (赞：1)

# ARC175C  Jumping Through Intervals

## 题目大意

给定 $n$ 个区间 $[l_i,r_i]$。构造一组 $A_i\in[l_i,r_i]$，使得邻的 $A_i$ 的差的和，即 $\sum\limits_{i=1}^{n-1}|A_i+A_{i+1}|$ 最小。若有多组解，输出字典序最小的一组。

## Solve

令 $f_i(x)$ 表示前 $i$ 个数，第 $A_i=x$ 时的最小的相邻两项之差的和。那么 $f_1(x),x\in[l_1,r_1]=0$。即 $f_1(x)$ 的图象是一条在 $y$ 轴上的线段。

而 $f_i(x),i\in[2,n]$ 的图象显然是这样的图象的一部分：

![](https://cdn.luogu.com.cn/upload/image_hosting/mld0z8bi.png)

以 $f_2(x)$ 为例，其图象为：（此时 $[l_1,r_1]=[4,9],[l_2,r_2]=[1,12]$）

![](https://cdn.luogu.com.cn/upload/image_hosting/twkmdwyi.png)

对于 $x\in[l_2,r_2]\cap[l_1,r_1]=[4,9]$，显然可以直接从 $f_1(x)$ 上转移过来，代价为 $0$；否则，从$[l_1,r_1]$ 上最靠近 $x$ 的点，即 $l_1$ 或 $r_1$ 上转移过来最优，代价为 $l_1-x$ 或 $x-r_1$（同无交时）。如果 $[l_2,r_2]\neq[1,12]$，那也不影响图象的总体形状，只是在上边截取一部分或延长一端。

而对于这么个图象，我们只需要记录住它的拐点（即上图中 $(4,0)$ 和 $(9,0)$）就可以知道这个图象长什么样子了。记 $[l_i,r_i]$ 的拐点为 $a_i$ 和 $b_i$，则 $[a_i,b_i]$ 上 $f_i(x)$ 最小，考虑怎么状态转移。

首先，我们有 $[a_1,b_1]=[l_1,r_1]$。

对于 $i\in[2,n]$：

- 若 $r_i<a_{i-1}$，即 $[l_i,r_i]$ 和 $[a_{i-1},b_{i-1}]$ 无交且在其左侧，则此时当且仅当 $x=r_i$ 时 $f_i(x)_{\min}=f_{i-1}(l_{i-1})+l_{i-1}-r_i$，故 $a_i=b_i=r_i$。
- 若 $l_i>b_{i-1}$，即 $[l_i,r_i]$ 和 $[a_{i-1},b_{i-1}]$ 无交且在其右侧，同理有 $a_i=b_i=l_i$。
- 否则 $[l_i,r_i]$ 和 $[a_{i-1},b_{i-1}]$ 有交，则对于 $x\in[l_i,r_i]\cap[a_{i-1},b_{i-1}]$，$f_i(x)_{\min}=f_{i-1}(x)$。故 $[a_i,b_i]=[l_i,r_i]\cap[a_{i-1},b_{i-1}]$，即 $a_i=\max(l_i,a_{i-1})$，$b_i=\min(r_i,b_{i-1})$。

处理完拐点之后，我们来确定这个字典序最小的序列，但这时候就有一个问题：$[a_i,b_i]$ 是由 $[a_{i-1},b_{i-1}]$ 转移来的，但时我们确定字典序是按照从 $1$ 到 $n$ 的顺序确定的，这样就会有后效性。所以我们在处理 $[a_i,b_i]$ 时令 $[a_n,b_n]=[l_n,r_n]$，倒着转移即可。

倒着转移完成后，显然 $A_1=a_1$。那么在确定 $A_2$ 的时候，就变成了这样一个问题：

![](https://cdn.luogu.com.cn/upload/image_hosting/uppo8vni.png)

如图，在 $f_0$ 上给定一点 $P\in\{A,B,C,D,E\}$，在 $f_2(x)$ 上找一点 $(x,f_2(x))$，使得 $g_2(x)=f_2(x)+|x-x_P|$ 最小，若有多个合法的 $x$，取最小的。

- 若 $P=A\in{(-\infty,l_2]}$，对于 $x\in[l_2,a_2]$，$g_2(x)$ 为定值。因为 $x$ 每减小 $1$，$f_2(x)$ 就增大 $1$，$|x-x_A|$ 减小 $1$，和不变。所以应取 $x=l_2$。
- 若 $P=B\in[l2,a_2]$，对于 $x\in[x_B,a_2]$，$g_2(x)$ 为定值，原因同上。故应取 $x=x_B$。
- 若 $P=C\in[a_2,b_2]$，显然当 $x=x_C$ 时 $g_2(x)$ 最小，应取 $x=x_C$。
- 若 $P=D\in[b_2,r_2]$，对于 $x\in[b_2,x_D]$，$g_2(x)$ 为定值，原因与第一种情况类似。应取 $x=b_2$。
- 若 $P=E\in[r_2,+\infty)$，对于 $x\in[b_2,r_2]$，$g_2(x)$ 为定值。应取 $x=b_2$。

整理一下并从 $A_2$ 推广到所有 $A_i,i\in[2,n]$，有：$A_i=\begin{cases}l_i&(A_{i-1}<l_i)\\A_{i-1}&(l_i\leq A_{i-1}\leq b_i)\\b_i&(A_{i-1}>b_i)\end{cases}$。

## Code

（代码中 $[a_i,b_i]$ 和 $[l_i,r_i]$ 意义相反。）

```c++
// LUOGU_RID: 153163957
#include<bits/stdc++.h>
#pragma GCC optimize(1,2,3,"Ofast","inline")
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int a[500010],b[500010],l[500010],r[500010],n,ans[500010];
signed main()
{
	n=read();
	for(int i=1;i<=n;i=-~i)	a[i]=read(),b[i]=read();
	l[n]=a[n];r[n]=b[n];
	for(int i=n-1;i;i--)
	{
		if(b[i]<l[-~i])	l[i]=r[i]=b[i];
		else if(a[i]>r[-~i])	l[i]=r[i]=a[i];
		else	l[i]=max(l[-~i],a[i]),r[i]=min(r[-~i],b[i]);
	}
	printf("%lld ",ans[1]=l[1]);
	for(int i=2;i<=n;i=-~i)	printf("%lld ",ans[i]=clamp(ans[i-1],a[i],r[i]));
	return 0;
}
```

注：`clamp(a,b,c)`：若 $a\in[b,c]$ 则返回 $a$，否则返回 $b,c$ 中与 $a$ 的差较小的一个。

---

## 作者：JackMerryYoung (赞：1)

# 前言

赛时甚至没看，赛后甚至杀穿了。

# 正文

我的感性理解：接不上就别接了，不要砍断自己。这话听起来有点费解，那么来看严谨证明。

借用一下 ATC 官方题解的证明：

我们令 $f_k(x)$ 为 

$$\sum_{i = k}^{N - 1}{|A_{i + 1} - A_i|}$$

的最小值，当 $A_k = x$
且 $\forall i \in [k + 1, N], A_i \in [L_i, R_i]$。我们这里钦定 $f_N(x) = 0$。

接下来我们令 

$$I_k \operatorname{:=} \argmin_{x \in [L_k, R_k]}{f_k(x)}$$

由于 $I_k$ 是一个整数集，我们不妨将其表示为 $[l_k, r_k]$。

当 $I_{k + 1} \cup [L_k, R_k] \neq \varnothing$，则 $I_k$ 为 $I_{k + 1} \cup [L_k, R_k]$；若 $R_k < l_{k + 1}$ 则 $I_k$ 为 $\{R_k\}$，若 $L_k > r_{k + 1}$ 则 $I_k$ 为 $\{L_k\}$。

然后就正着取值了，如果取不到就断开来。

简单说明一下决策的正确性：

因为你前面倒着求 $I$，导致你按照 $I$ 的区间取必然使得后面最优，所以最后正着取值完全没问题。

# 后言

不懂为啥 600。猜这个结论实在是太简单了。

---

## 作者：Jsxts_ (赞：0)

困扰我 $3$ 天。

考虑将序列划分为极长的若干段，其中的每一段都满足对于任意 $i$，前缀 $r$ 的最小值 $\ge$ 后缀 $l$ 的最大值。容易证明这样划分后，除了第一段，每一段 $[x,y]$ 都满足 $a_{x-1}<l_x$，这个重要的性质保证了很多决策的正确性。所以第一段需要另外处理。

我们对每段分别处理，记 $l_i$ 的后缀 $\max$ 为 $suf_i$，前缀 $\max$ 为 $pre_i$，并记区间 $r_i$ 最小值为 $mr$。

对于不是第一段的，分情况考虑：

- 若 $mr\ge suf_x$：此时显然每个数都可以取到 $pre_i$。

- 否则，这一段所有数会这样变动：先递增至 $suf_x$（区间 $l_i$ 最大值），再递减至 $mr$，最后一段都是 $mr$。具体地：

	1. 若 $suf_i<mr$，说明之后不会变，必须取到 $mr$。
   2. 否则，由于 $suf_i\ge mr$，说明还会经历上升和下降，现在可以取到 $\min(pre_i,suf_i)$。
   
对于第一段，也可以类似地考虑：

- 若 $mr\ge suf_x$：此时贡献最小的方案是所有数都取 $mr$，因为 $y+1$ 的位置选的数比 $mr$ 大。但是还有一种可能就是 $y=n$，此时应所有数都选 $suf_x$。

- 否则，由于没有上一个数，所以一开始取递增会使答案变劣，所以一开始的那一段从递增改为一直为后缀最大值。

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
const int inf = 2e9;
const ll INF = 1e15;
const int N = 5e5;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
const int mod = 998244353;
int getmod(int x) {
	return x - (x >= mod) * mod;
}
int qpow(int a,int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % mod;
		b >>= 1, a = 1ll * a * a % mod;
	}
	return res;
}
int n,res[N + 10];
pair<int,int> a[N + 10];
int suf[N + 10];
void solve() {
	for (int i = 1;i <= n;i ++ ) {
		int r1 = i,mr = a[i].y;
		while (r1 < n && a[r1 + 1].x <= mr) mr = min(mr,a[r1 + 1].y), r1 ++;
		suf[r1 + 1] = -inf;
		for (int j = r1;j >= i;j -- ) suf[j] = max(suf[j + 1],a[j].x);
		if (mr >= suf[i]) {
			if (i == 1)
				for (int j = i;j <= r1;j ++ ) res[j] = r1 == n ? suf[i] : mr;
			else {
				int mx = 0;
				for (int j = i;j <= r1;j ++ ) mx = max(mx,a[j].x), res[j] = mx;
			}
		}
		else {
			if (i == 1) {
				for (int j = i;j <= r1;j ++ ) {
					if (suf[j] < mr) res[j] = mr;
					else res[j] = suf[j];
				}
			}
			else {
				int mx = 0;
				for (int j = i;j <= r1;j ++ ) {
					mx = max(mx,a[j].x);
					if (suf[j] < mr) res[j] = mr;
					else res[j] = min(mx,suf[j]);
				}
			}
		}
		i = r1;
	}
}
int main() {
	n = read();
	for (int i = 1;i <= n;i ++ ) a[i].x = read(), a[i].y = read();
	solve();
	for (int i = 1;i <= n;i ++ ) printf("%d ",res[i]);
	return 0;
}
```

---

## 作者：wosile (赞：0)

敢写你就赢了。

首先，我们忽略那个要求字典序最小的条件，想想该怎么构造一个满足 $\sum|a_i-a_{i+1}|$ 最小的序列。

如果已经确定了 $a_i$，显然有一个唯一确定的 $a_{i+1}$ 使得 $|a_i-a_{i+1}|$ 最小，但是这么取会不会导致 $|a_{i+1}-a_{i+2}|$ 很大然后全局答案更大呢？感性理解一下就会发现是不可能的。具体来讲，如果 $a_i\le a_{i+1} \le a_{i+2}$，$a_{i+1}$ 取什么都不影响最终答案；如果有 $a_i \le a_{i+1} \ge a_{i+2}$，那么 $a_{i+1}$ 贪心取最小自然也满足最终答案最小。

解决不能确定 $a_1$ 的方法其实也很简单，把每个位置的最佳取值 $a_i$ 改成一个最优区间 $[l_i,r_i]$ 即可，取 $[l_1,r_1]=[L_1,R_1]$。通过观察即可发现，计算 $[l_{i+1},r_{i+1}]$ 时，如果 $[l_i,r_i]$ 和 $[L_{i+1},R_{i+1}]$ 有交，那么 $[l_{i+1},r_{i+1}]$ 就是它们的交，否则 $[l_{i+1},r_{i+1}]$ 就变成了单个点。最后，反过来确定每个区间应该取什么值就可以了（能取不止一个值就取个最小值咯）。

我们考虑把这个序列调整成字典序最小的，可以发现满足 $a_{i-1} \le a_i \le a_{i+1}$ 或者 $a_{i-1} \ge a_i \ge a_{i+1}$ 的 $a_i$ 是灵活的，那么按 $a_i$ 从小到大调整即可。可能会有若干个相同数处理顺序不对导致出错，注意到我们是从前往后贪心的，那么 $a_{i-1} \le a_i \le a_{i+1}$  的情况 $a_i$ 以 $a_{i-1}$ 为基准贪心，已经取到了最小值。所以 $a_i$ 相同按 $i$ 从大到小排序即可。

时间复杂度 $O(n\log n)$，可以做到 $O(n)$。

```cpp
// 代码中用的是 c[i] 而非 a[i]
#include<bits/stdc++.h>
using namespace std;
int n;
int L[500005],R[500005];
int c[500005];
pair<int,int>p[500005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&L[i],&R[i]);
	int l=L[1],r=R[1];
	memset(c,-1,sizeof(c));
	int v=0;
	for(int i=1;i<=n;i++){
		if(c[i-1]>-1){
			if(L[i]<=c[i-1] && c[i-1]<=R[i])c[i]=c[i-1];
			else if(c[i-1]<L[i])c[i]=L[i];
			else c[i]=R[i];
		}
		else if(max(l,L[i])<=min(r,R[i]))l=max(l,L[i]),r=min(r,R[i]);
		else{
			if(r<L[i])c[i]=L[i],v=1;
			else c[i]=R[i];
		}
	}
	for(int i=1;i<=n;i++)if(c[i]==-1)c[i]=(v?r:l);
	for(int i=1;i<=n;i++)p[i]={c[i],-i};
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++){
		int x=-p[i].second;
		if(x>1 && x<n && 1LL*(c[x-1]-c[x])*(c[x+1]-c[x])<=0){
			c[x]=max(min(c[x-1],c[x+1]),L[x]);
		}
	}
	for(int i=1;i<=n;i++)printf("%d ",c[i]);
	return 0;
	//quod erat demonstrandum
}
```

---

