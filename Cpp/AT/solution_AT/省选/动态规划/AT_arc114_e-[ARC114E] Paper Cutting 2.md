# [ARC114E] Paper Cutting 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc114/tasks/arc114_e

$ H\ \times\ W $ のマス目に区切られた長方形の紙があり，このうちちょうど $ 2 $ マスが黒く，残りの部分は白く塗られています．マス目の $ i $ 行目，$ j $ 列目にあるマスを $ (i,\ j) $ で表すと，黒く塗られているのはマス $ (h_1,\ w_1) $ とマス $ (h_2,\ w_2) $ です．

maroon 君はこれから以下の手順で紙を切断する操作を繰り返します．

- 現在の紙のマス目が $ h\ \times\ w $ の時，紙の辺に平行でマスの境界を通るような直線には，$ (h\ -\ 1) $ 本の横線と $ (w\ -\ 1) $ 本の縦線がある．この中から $ 1 $ 本を一様ランダムに選んで，その直線に沿って紙を $ 2 $ 枚に切断する．このとき，
  - $ 2 $ つの黒いマスが同じ紙に存在するとき，もう片方の紙を捨て，操作を続ける
  - そうでなければ，操作を終了する

maroon 君が操作を終了するまでに紙を切断する回数の期待値を $ {\bmod}\ 998244353 $ で求めてください．

## 说明/提示

### 注記

求める期待値は必ず有理数になることが証明できます．またこの問題の制約のもとでは，その値を既約分数 $ \frac{P}{Q} $ で表した時，$ Q\ \not\ \equiv\ 0\ \pmod{998244353} $ となることも証明できます．よって，$ R\ \times\ Q\ \equiv\ P\ \pmod{998244353},\ 0\ \leq\ R\ <\ 998244353 $ を満たす整数 $ R $ が一意に定まります．この $ R $ を答えてください．

### 制約

- $ 1\ \leq\ H,\ W\ \leq\ 10^5 $
- $ H\ \times\ W\ \geq\ 2 $
- $ 1\ \leq\ h_1,\ h_2\ \leq\ H $
- $ 1\ \leq\ w_1,\ w_2\ \leq\ W $
- $ (h_1,\ w_1)\ \neq\ (h_2,\ w_2) $
- 入力は全て整数

### Sample Explanation 1

まず，$ 1 $ 回目の切断で確率 $ 2/3 $ で操作が終了します．残りの $ 1/3 $ については，次の切断で操作が終了します． よって，紙を切断する回数の期待値は，$ 1\ \times\ 2/3\ +\ 2\ \times\ 1/3\ =\ 4/3 $ です．

### Sample Explanation 3

操作は $ 1 $ 回の切断で必ず終了します．

## 样例 #1

### 输入

```
2 3
2 2 1 1```

### 输出

```
332748119```

## 样例 #2

### 输入

```
1 5
1 2 1 3```

### 输出

```
332748120```

## 样例 #3

### 输入

```
2 1
2 1 1 1```

### 输出

```
1```

## 样例 #4

### 输入

```
10 10
3 4 5 6```

### 输出

```
831078040```

# 题解

## 作者：APJifengc (赞：15)

首先第一件事，发现从现有的线段里选一个隔开这个东西太丑了。我们考虑转化一下题意。我们仍然在原矩形上划线，但是划完线后并不割开，而是一直在原矩形上操作。可以发现，这个操作是和原来的操作是等价的，因为我们可以看做是每次选了一条线，如果这个线已经不在当前矩形上了就重新选一个，容易发现这个操作的选中每一条线的概率是和原来相等的。

同时，发现原问题的操作次数等价于这个矩形**缩小了多少次**，那么根据期望的线性性，我们可以将期望拆为**对于每一条线，矩形的边界在某一时刻变为这一条线的概率之和**。

那么我们枚举每一条线，然后考虑选中它的概率。设上下左右分别有 $u, d, l, r$ 条可以选的线，总线段数为 $s$。假设我们枚举的是左边的第 $i$ 条线，那么不难发现每次选中其它线的概率为 $\dfrac{u+d+r+i-1}{s}$。那么某一时刻选中这条线的概率就是 $\displaystyle \sum_{j=0}^{\infty} \left(\dfrac{u+d+r+i-1}{s}\right)^j \frac{1}{s} = \frac{1}{s-(u+d+r+i-1)}$。直接对这个东西求和即可，复杂度 $O(n \log n)$ 或 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int P = 998244353;
int h, w;
int h1, h2, w1, w2;
int l, r, u, d, s;
int qpow(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % P;
        a = 1ll * a * a % P;
        b >>= 1;
    }
    return ans;
}
int main() {
    scanf("%d%d%d%d%d%d", &h, &w, &h1, &w1, &h2, &w2);
    l = min(h1, h2) - 1;
    r = h - max(h1, h2);
    u = min(w1, w2) - 1;
    d = w - max(w1, w2);
    s = h + w - 2;
    int ans = 1;
    for (int i = 1; i <= l; i++) {
        ans = (ans + qpow(s - r - u - d - i + 1, P - 2)) % P;
    }
    for (int i = 1; i <= r; i++) {
        ans = (ans + qpow(s - l - u - d - i + 1, P - 2)) % P;
    }
    for (int i = 1; i <= u; i++) {
        ans = (ans + qpow(s - r - l - d - i + 1, P - 2)) % P;
    }
    for (int i = 1; i <= d; i++) {
        ans = (ans + qpow(s - r - u - l - i + 1, P - 2)) % P;
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：LinkWish (赞：7)

发现直接算每种情况算感觉比较不可做，所以考虑对于每一条竖着的和横着的线算单独的贡献。

一条线在操作序列中只有两种情况：被选与不被选，所以它对期望的贡献即为它被选中的概率。

一条线可以被选中的条件是：

1.在 $h_1,h_2$ 之间的任意一条横线没有被选过。

2.在 $w_1,w_2$ 之间的任意一条竖线没有被选过。

3.如图所示：

如果这是一条竖线，如果它在黄色区域内，则不造成贡献，最后再对答案加一；否则比他靠近黄色区域的线都不能被选过。横线同理，只不过倒过来了而已。
设不能在一条线之前被选走的线的个数为 $x$，则这条线的贡献即为 $\frac{1}{x}$。
![](https://cdn.luogu.com.cn/upload/image_hosting/bozpz0d3.png)

程序只给出主体部分，主要是前面一部分的模板有一些影响观感，而且给出主体已经能够辅助理解。
```cpp
//Linkwish's code
const int mod=998244353;
int n,m;
inline int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=x*res%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
signed main(){
	read(n),read(m);
	int x,y,_x,_y;
	read(x),read(y),read(_x),read(_y);
	int ans=0,l=max(x,_x)-min(x,_x)+max(y,_y)-min(y,_y);
	for(int i=1;i<n;i++){
		if(i<min(x,_x))ans=(ans+qpow(min(x,_x)-i+l,mod-2))%mod;
		else if(i>=max(x,_x))ans=(ans+qpow(i-max(x,_x)+1+l,mod-2))%mod;
	}
	for(int i=1;i<m;i++){
		if(i<min(y,_y))ans=(ans+qpow(min(y,_y)-i+l,mod-2))%mod;
		else if(i>=max(y,_y))ans=(ans+qpow(i-max(y,_y)+1+l,mod-2))%mod;
	}
	writeln((ans+1)%mod);
	return 0;
}
```


---

## 作者：fangzichang (赞：4)

和题比唐氏系列！所以我咋这都能写挂。  

---
给出一个我觉得简单的思考方法。  
注意到整个过程中有 $(h+w-2)$ 条线可能被切到，其中 $cnt=(|x_1-x_2|+|y_1-y_2|)$ 条线切割后两个黑色点会分开，游戏结束。  
根据期望的线性性，最终切的刀数的期望，就等于网格内部每条线被切到的概率的和。按照算贡献的思路理解也行。  

考虑对每条线计算它被切到的概率。  
考虑所有的可能到达的状态，对于每条线 $x$ 分别考虑，将所有状态分成两类：一类状态中 $x$ 还可能被切到，二类状态中 $x$ 处在边缘或已经被去掉了，并且钦定所有的结束状态属于第二类。  
显然初始状态对于任意 $x$ 属于一类状态，且二类状态不可能变回一类状态。因为任意合法的切割方案都以二类状态结束，所以切割过程中必然存在一步使这条线的状态变化；其他操作对这条线没有任何影响。  
考虑这一步可能是怎样的：可能是切完游戏就结束了，根据前面的推论知道有 $cnt$ 种方案；可能是切到了 $x$，有 $1$ 种方案；可能是切完之后 $x$ 被去掉了，如果你没有一眼数出来，不妨画个图。  
![](https://cdn.luogu.com.cn/upload/image_hosting/n6x4u366.png)  
红线是 $x$，绿线是切了会导致 $x$ 被去掉的线。  
可以发现，以两个黑点为顶点画一个矩形，则矩形四个方向上的线分别独立，计算时数一下这个方向上在 $x$ 之前的线数量即可。假设有 $i$ 条这样的线，那么 $x$ 被切到的概率就是 $\frac{1}{cnt+i+1}$。  

代码 be like：  
```cpp
int n,m,x,y,a,b,ct;
int q_pow(int a,int b=mod-2){int res=1;for(;b;b>>=1,a=a*1ll*a%mod)if(b&1)res=res*1ll*a%mod;return res;}
int calc(int a,int b,int c,int d){
	int res=1;
	for(int i=0;i<max({a,b,c,d});i++)
		res=(res+q_pow(i+ct+1)*1ll*((i<a)+(i<b)+(i<c)+(i<d)))%mod;
	return res;
}
int main(){
	cin(n,m,x,y,a,b),ct=abs(x-a)+abs(y-b),
	print(calc(n-max(x,a),min(x,a)-1,m-max(y,b),min(y,b)-1)),putchar(endl);
	return 0;
}
```

---

## 作者：Argon_Cube (赞：2)

题目的过程等价于：

> 等概率随机一个 $H+W-2$ 条网格线的排列。从前往后遍历每条网格线，如果能剪当前的网格线就剪。

考虑每次操作不只从合法的网格线中选取，而是从所有网格线中等概率选取。如果选到的不合法就不算贡献重新选。同时维护一个序列，如果当前选到的格线没有在序列中出现过就将其加到序列的末端，即使这条格线不合法。容易发现这个过程与原问题等价，而序列每次增加的格线都是在剩下的格线中等概率选取的，所以每个排列是等概率的。

于是对于某条格线，如果除了自己，还有 $a$ 条格线使得割了它们中的任意一个就不可能再割自己了，那么这条格线在排列中一定要在这 $a$ 条格线的前面才会有贡献，概率为 $\frac 1{a+1}$。将每条格线被割的概率加起来就是答案。

---

## 作者：_Cheems (赞：0)

题意：一张 $n\times m$ 的网格纸，$(x_1,y_1),(x_2,y_2)$ 是黑色其它白色。每次沿格线平行于边缘剪一刀，假如分开了两个黑色格子就结束，否则进入有黑色格子的部分继续进行，求期望次数。$n,m\le 10^5$。

原题这个切换纸的过程很烦，考虑换一个等价的随机方式。

trick：允许非法操作出现，但不算入期望。

在本题体现为等概率地选取任意一条线，假如是非法（即之前已经被剪掉了）就不算入操作次数。容易发现，一条合法线的概率与原先的随机方法一样！

由期望线性性，拆开来计算每条线合法的概率，记 $cnt$ 为剪掉后这条线非法的线数量，注意包括剪开两个黑色格子的线，概率即为 $\frac 1{cnt}$。

$O(n)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 998244353;
int n, m, a, b, x, y, yyc, lby, _yyc, _lby, ans, cnt;

inline int qstp(int a, int k) {int res = 1; for(; k; a = a * a % mod, k >>= 1) if(k & 1) res = res * a % mod; return res;}
signed main(){
	cin >> n >> m >> a >> b >> x >> y;
	yyc = min(a, x) - 1, lby = max(a, x);
	_yyc = min(b, y) - 1, _lby = max(b, y);
	cnt = lby - yyc + _lby - _yyc - 2; 
	for(int i = 1; i <= yyc; ++i) ans = (ans + qstp(yyc - i + 1 + cnt, mod - 2)) % mod;
	for(int i = lby; i < n; ++i) ans = (ans + qstp(i - lby + 1 + cnt, mod - 2)) % mod;
	
	for(int i = 1; i <= _yyc; ++i) ans = (ans + qstp(_yyc - i + 1 + cnt, mod - 2)) % mod;
	for(int i = _lby; i < m; ++i) ans = (ans + qstp(i - _lby + 1 + cnt, mod - 2)) % mod;
	cout << (ans + 1) % mod;
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

下文设矩形规模是 $n \times m$。显然一共有 $n+m-2$ 条线。

**我们可以将问题等效为：将这 $n+m-2$ 随机排列，按顺序枚举，判断是否能切割，能切就切，求期望切割次数**。

对于能将 $(x_1,y_1)$ 和 $(x_2,y_2)$ 分开的线段，显然最多被操作一次。对于其他线段，相当于给出了**如果它排在另外 $k$ 条线之后就能产生贡献**，其概率为 $\frac{1}{k+1}$。

直接累加求和即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MOD=998244353;
int n,m,x,y,xx,yy,ans=1; 
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>x>>y>>xx>>yy;
	int ot=abs(x-xx)+abs(y-yy);
	ffor(i,1,min(x,xx)-1) ans=(ans+qpow(ot+i,MOD-2))%MOD;
	ffor(i,1,n-max(x,xx)) ans=(ans+qpow(ot+i,MOD-2))%MOD;
	ffor(i,1,min(y,yy)-1) ans=(ans+qpow(ot+i,MOD-2))%MOD;
	ffor(i,1,m-max(y,yy)) ans=(ans+qpow(ot+i,MOD-2))%MOD;
	cout<<ans;
	return 0;
}
```

---

## 作者：freoepn (赞：0)

只要算出每条线被选中的概率就能计算出操作次数的期望，当一条线没有被选中，则一定是两黑点被分开或这条线被隔离出去，能满足这两个条件的线可以简单计算出来，考虑这条线和能使得这条线不能选中的线的相对顺序，只有在这条线在最前的时候才能被选上，设加上这条线有 $n$ 条线，则有 $\frac{1}{n}$ 期望被选，求和即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
int qpow(int x, int y) {
  int ans = 1, p = x;
  while (y) {
    if (y & 1) {
      ans = (ans * p) % mod;
    }
    p = (p * p) % mod;
    y >>= 1;
  }
  return ans;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m, x, y, xx, yy, num = 0, ans = 1;
  cin >> n >> m >> x >> y >> xx >> yy;
  num = abs(x - xx) + abs(y - yy);
  for (int i = 1; i < n; i++) {
    if (i < min(x, xx)) ans = (ans + qpow(num + min(x, xx) - i, mod - 2)) % mod;
    if (i >= max(x, xx)) ans = (ans + qpow(num +  i -max(x, xx) + 1, mod - 2)) % mod;
  }
  for (int i = 1; i < m; i++) {
    if (i < min(y, yy)) ans = (ans + qpow(num + min(y, yy) - i, mod - 2)) % mod;
    if (i >= max(y, yy)) ans = (ans +  qpow(num + i -max(y, yy) + 1, mod - 2)) % mod;
  }
  cout << ans;
  return 0;
}
```

---

## 作者：柳易辰 (赞：0)

题目中如果两个黑点没有被分开，网格会被扔掉一半，这个非常麻烦。

我们考虑并不扔掉另一半，而是把它考虑成一个缩小的边界，每次选到了边界的外的割线不产生贡献。

这样的好处在于：**上下左右独立**了。我们可以对上下左右分别计算贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/9yk5rjns.png)

那么产生贡献的什么？应该是**前缀最值**。假设我们统计图中下侧的贡献，那么产生贡献的割线就需要满足 $y$ 是前缀最小值。我们令每条割线只能选一次（选两次后面那次必然没贡献）。假设选了 $t$ 条不同的割线，考虑第 $i$ 条割线的贡献，它是最值的概率就是 $\frac 1i$，于是这 $t$ 条的贡献就是 $f_t=\sum_{i=1}^t\frac1i$。

我们再枚举每个方向的不同的割线在终止之前割了几条，设该方向总共有 $a$ 条，割了 $x(x>0)$ 条，共有 $b$ 条终止割线，则概率是 $\frac b{a+b-x}\prod_{i=0}^{x-1}\frac{a-i}{a+b-i}$。所以贡献就是 $\sum_{x=1}^a\frac b{a+b-x}f_x\prod_{i=0}^{x-1}\frac{a-i}{a+b-i}$，其实概率可以递推计算，那么一个方向就可以在 $O(n)$ 的时间复杂度内计算出期望。四个方向相加再加一就是答案。

---

## 作者：流水行船CCD (赞：0)

根据期望的不知道什么性，切割次数的期望 = 每条线段被切到的概率之和。

讨论线段的概率。

- 该线段区分开黑点：每一种合法方案最终一定由这些线段结尾，这些线段被选到的概率之和就是 $1$，平均一下每一条线段被选中概率为 $\frac{1}{\operatorname{Index}}$，其中 $\operatorname{Index} = x2 - x1 + y2 - y1$，就是这些线段的条数。

- 该线段不分开黑点：它能被选当且仅当在它的内侧没有线段被选且能区分开黑点的线段都没有被选。换句话说，就是它是它内侧的线段（包括它本身）及能区分开黑点的线段中第一个被选中的，至于它外侧的线段和其他方向的线段和它根本没有关系，无论怎么选都不会影响它的选择。因此概率为 $\frac{1}{x + \operatorname{Index}}$，其中 $x$ 为内侧线段（包括它本身）的条数。

![](https://cdn.luogu.com.cn/upload/image_hosting/xkdhz7dt.png)

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define CONSTEXPR14 constexpr
namespace OY {template <uint32_t P, bool IsPrime, typename = typename std::enable_if<(P > 1 && P < uint32_t(1) << 31)>::type>struct StaticModInt32 {using mint = StaticModInt32<P, IsPrime>;using mod_type = uint32_t;mod_type m_val;static constexpr mod_type _reduce_norm(int32_t x) { return x < 0 ? x + mod() : x; }static constexpr mod_type _mul(mod_type a, mod_type b) { return uint64_t(a) * b % mod(); }constexpr StaticModInt32() = default;template <typename Tp, typename std::enable_if<std::is_signed<Tp>::value>::type * = nullptr>constexpr StaticModInt32(Tp val) : m_val(_reduce_norm(val % int32_t(mod()))) {}template <typename Tp, typename std::enable_if<std::is_unsigned<Tp>::value>::type * = nullptr>constexpr StaticModInt32(Tp val) : m_val(val % mod()) {}static CONSTEXPR14 mint raw(mod_type val) {mint res{};res.m_val = val;return res;}static constexpr mod_type mod() { return P; }constexpr mod_type val() const { return m_val; }CONSTEXPR14 mint pow(uint64_t n) const {mod_type res = 1, b = m_val;while (n) {if (n & 1) res = _mul(res, b);b = _mul(b, b), n >>= 1;}return raw(res);}CONSTEXPR14 mint inv() const {if constexpr (IsPrime)return inv_Fermat();else return inv_exgcd();}CONSTEXPR14 mint inv_exgcd() const {mod_type x = mod(), y = m_val, m0 = 0, m1 = 1;while (y) {mod_type z = x / y;x -= y * z, m0 -= m1 * z, std::swap(x, y), std::swap(m0, m1);}if (m0 >= mod()) m0 += mod() / x;return raw(m0);}constexpr mint inv_Fermat() const { return pow(mod() - 2); }CONSTEXPR14 mint &operator++() {if (++m_val == mod()) m_val = 0;return *this;}CONSTEXPR14 mint &operator--() {if (!m_val) m_val = mod();m_val--;return *this;}CONSTEXPR14 mint operator++(int) {mint old(*this);++*this;return old;}CONSTEXPR14 mint operator--(int) {mint old(*this);--*this;return old;}CONSTEXPR14 mint &operator+=(const mint &rhs) {m_val += rhs.m_val;if (m_val >= mod()) m_val -= mod();return *this;}CONSTEXPR14 mint &operator-=(const mint &rhs) {m_val += mod() - rhs.m_val;if (m_val >= mod()) m_val -= mod();return *this;}CONSTEXPR14 mint &operator*=(const mint &rhs) {m_val = _mul(m_val, rhs.m_val);return *this;}CONSTEXPR14 mint &operator/=(const mint &rhs) { return *this *= rhs.inv(); }constexpr mint operator+() const { return *this; }constexpr mint operator-() const { return raw(m_val ? mod() - m_val : 0); }constexpr bool operator==(const mint &rhs) const { return m_val == rhs.m_val; }constexpr bool operator!=(const mint &rhs) const { return m_val != rhs.m_val; }constexpr bool operator<(const mint &rhs) const { return m_val < rhs.m_val; }constexpr bool operator>(const mint &rhs) const { return m_val > rhs.m_val; }constexpr bool operator<=(const mint &rhs) const { return m_val <= rhs.m_val; }constexpr bool operator>=(const mint &rhs) const { return m_val >= rhs.m_val; }template <typename Tp>constexpr explicit operator Tp() const { return Tp(m_val); }friend CONSTEXPR14 mint operator+(const mint &a, const mint &b) { return mint(a) += b; }friend CONSTEXPR14 mint operator-(const mint &a, const mint &b) { return mint(a) -= b; }friend CONSTEXPR14 mint operator*(const mint &a, const mint &b) { return mint(a) *= b; }friend CONSTEXPR14 mint operator/(const mint &a, const mint &b) { return mint(a) /= b; }};template <typename Istream, uint32_t P, bool IsPrime>Istream &operator>>(Istream &is, StaticModInt32<P, IsPrime> &x) { return is >> x.m_val; }template <typename Ostream, uint32_t P, bool IsPrime>Ostream &operator<<(Ostream &os, const StaticModInt32<P, IsPrime> &x) { return os << x.val(); }}
//using mint998244353 = StaticModInt32<998244353, true>;using mint1000000007 = StaticModInt32<1000000007, true>;
namespace fast_IO{
    #define IOSIZE (1<<20)
    char ibuf[IOSIZE],obuf[IOSIZE];char*p1=ibuf,*p2=ibuf,*p3=obuf;
    #ifdef ONLINE_JUDGE
    #define putchar(x)((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
    #endif
    #define isdigit(ch)(ch>47&&ch<58)
    #define isspace(ch)(ch<33)
    template	<typename T>inline T    read(){T s=0;int w=1;char ch;while(ch=getchar(),!isdigit(ch)and(ch!=EOF))if(ch=='-')w=-1;if(ch==EOF)return false;while(isdigit(ch))s=s*1+ch-48,ch=getchar();return s*w;}template<typename T>inline bool read(T&s){s=0;int w=1;char ch;while(ch=getchar(),!isdigit(ch)and(ch!=EOF))if(ch=='-')w=-1;if(ch==EOF)return false;while(isdigit(ch))s=s*10+ch-48,ch=getchar();return s*=w,true;}template<typename T>inline void print(T x){if(x<0)putchar('-'),x=-x;if(x>9)print(x/10);putchar(x%10+48);}inline bool read(char&s){while(s=getchar(),isspace(s));return true;}inline bool read(char*s){char ch;while(ch=getchar(),isspace(ch));if(ch==EOF)return false;while(!isspace(ch))*s++=ch,ch=getchar();*s='\000';return true;}inline void print(char x){putchar(x);}inline void print(char*x){while(*x)putchar(*x++);}inline void print(const char*x){for(int i=0;x[i];i++)putchar(x[i]);}inline bool read(std::string&s){s="";char ch;while(ch=getchar(),isspace(ch));if(ch==EOF)return false;while(!isspace(ch))s+=ch,ch=getchar();return true;}inline void print(std::string x){for(int i=0,n=x.size();i<n;i++)putchar(x[i]);}inline bool read(bool&b){char ch;while(ch=getchar(),isspace(ch));b=ch^48;return true;}inline void print(bool b){putchar(b+48);}template<typename T,typename...T1>inline int read(T&a,T1&...other){return read(a)+read(other...);}template<typename T,typename...T1>inline void print(T a,T1...other){print(a),print(other...);}struct Fast_IO{~Fast_IO(){fwrite(obuf,p3-obuf,1,stdout);}}jyt;template<typename T>Fast_IO&operator>>(Fast_IO&jyt,T&b){return read(b),jyt;}template<typename T>Fast_IO&operator<<(Fast_IO&jyt,T b){return print(b),jyt;}
    struct IO{static const int S=1<<21;char buf[S],obuf[S],*p1,*p2;int st[105],Top;~IO(){clear();}inline void clear(){fwrite(obuf,1,Top,stdout);Top=0;}inline void pc(const char c){Top==S&&(clear(),0);obuf[Top++]=c;}inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}IO&operator>>(char&x){while(x=gc(),x==' '||x=='\n');return*this;}template<typename T>IO&operator>>(T&x){x=0;bool f=0;char ch=gc();while(ch<'0'||ch>'9'){if(ch=='-')f^=1;ch=gc();}while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=gc();f?x=-x:0;return*this;}IO&operator<<(const char c){pc(c);return*this;}template<typename T>IO&operator<<(T x){if(x<0)pc('-'),x=-x;do{st[++st[0]]=x%10,x/=10;}while(x);while(st[0]){pc('0'+st[st[0]--]);}return*this;}}ld;
} using namespace fast_IO;
#define ll long long
#define ull unsigned long long
#define REP(i, l, r) for (int i = l; i <= r; ++i)
#define PER(i, l, r) for (int i = l; i >= r; --i)
#define rep(i, l, r) for (int i = l; i < r ; ++i)
#define per(i, l, r) for (int i = l; i > r ; --i)
#define pf(x) (1ll * (x) * (x))
#define bitcount(x) __builtin_popcount(x)
#define albit(x) ((1 << (x)) - 1)
#define mkbit(x) (1 << (x - 1))
#define gtbit(x, id) (((x) >> (id - 1)) & 1)
// #define ld cin
// #define jyt cout
// #define int long long
const int N = 2e5 + 7;
const int inf = 1e9 + 7;
const ll linf = 1e18 + 7;
const int P = 998244353;
namespace MG42 {
    using mint = OY::StaticModInt32<998244353, true>;
    int n, m, x1, y1, x2, y2, Index;
    mint fac[N], inv[N];
    inline mint qpow(mint x, long long y) {
        mint Res = 1;
        while (y) {
            if (y & 1) Res *= x;
            x *= x, y >>= 1;
        } return Res;
    } 
    inline mint C(int x, int y) {return fac[x] * inv[y] * inv[x - y];}
    signed main() { fac[0] = inv[0] = 1;
        ld >> n >> m >> x1 >> y1 >> x2 >> y2, --n, --m;
        if (x1 > x2) swap(x1, x2); if (y1 > y2) swap(y1, y2);
        REP(i, 1, 200000) fac[i] = fac[i - 1] * i;
        inv[200000] = qpow(fac[200000], P - 2);
        PER(i, 200000, 1) inv[i - 1] = inv[i] * i;
        mint Ans = 0;
        REP(i, 1, n) {
            if (i < x1) Ans += qpow(x1 - i + x2 - x1 + y2 - y1, P - 2);
            else if (i < x2) Ans += qpow(x2 - x1 + y2 - y1, P - 2);
            else Ans += qpow(i - x2 + x2 - x1 + y2 - y1 + 1, P - 2);
        }
        REP(i, 1, m) {
            if (i < y1) Ans += qpow(y1 - i + x2 - x1 + y2 - y1, P - 2);
            else if (i < y2) Ans += qpow(x2 - x1 + y2 - y1, P - 2);
            else Ans += qpow(i - y2 + x2 - x1 + y2 - y1 + 1, P - 2);
        } cout << Ans << '\n';
        return 0; 
    }
}
signed main() {
//	freopen("std.in", "r", stdin);
//	freopen("user.out", "w", stdout);
//	ios::sync_with_stdio(false);
//	cin.tie(0), cout.tie(0);
    MG42::main();
    return 0;
}
```

---

