# [AGC062D] Walk Around Neighborhood

## 题目描述

高桥君手持一本记事本，站在二维平面上的原点 $(0,0)$。记事本上写有 $N$ 个**偶数** $D_i\ (1\leq i \leq N)$。

接下来，高桥君将在二维平面上进行 $N$ 次如下操作：

- 从记事本上选择并划去一个偶数。设选中的偶数为 $d$，则他会移动到与当前位置曼哈顿距离恰好为 $d$ 的某个点。更准确地说，若当前坐标为 $(x, y)$，则他会移动到满足 $|x-x'|+|y-y'|=d$ 的某个点 $(x', y')$。

高桥君必须在 $N$ 次操作后回到原点 $(0,0)$。

请判断是否存在一种操作顺序和移动方式，使得高桥君能够完成上述 $N$ 次操作并回到原点。如果存在，请求出所有可能方案中，$i$ 次操作后高桥君所在坐标为 $(x_i, y_i)$ 时，$\displaystyle\max_{1\leq i\leq N}(|x_i|+|y_i|)$ 的最小值（可以证明该值为整数）。

## 说明/提示

## 限制条件

- $1\leq N\leq 2\times 10^5$
- $2\leq D_i\leq 2\times 10^5$
- $D_i$（$1\leq i\leq N$）均为偶数
- 所有输入均为整数

## 样例解释 1

高桥君依次选择 $2,6,4$ 并划去，移动路径为 $(0,0)\rightarrow (0,2)\rightarrow (-4,0)\rightarrow (0,0)$，此时 $\displaystyle\max_{1\leq i\leq N}(|x_i|+|y_i|)$ 为 $4$，且这是最小值。

## 样例解释 2

高桥君依次选择 $2,2,6,2,2$ 并划去，移动路径为 $(0,0)\rightarrow (\frac{1}{2},\frac{3}{2})\rightarrow (0,3)\rightarrow (0,-3)\rightarrow (-\frac{1}{2},-\frac{3}{2})\rightarrow (0,0)$，此时 $\displaystyle\max_{1\leq i\leq N}(|x_i|+|y_i|)$ 为 $3$，且这是最小值。高桥君可以移动到非格点的位置。

## 样例解释 3

高桥君无法在 $N$ 次操作后回到原点。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 4 6```

### 输出

```
4```

## 样例 #2

### 输入

```
5
2 2 2 2 6```

### 输出

```
3```

## 样例 #3

### 输入

```
2
2 200000```

### 输出

```
-1```

# 题解

## 作者：tzc_wk (赞：7)

csy/bx wjz/bx

首先将 $a$ 排序，如果 $\sum\limits_{i=1}^{n-1}a_i<a_n$ 显然就是 $-1$，否则必然有解。

先发现一个 trivial 的事情，就是答案一定位于 $[\dfrac{a_n}{2},a_n]$ 中，这是因为我们判掉无解的条件之后，我们必然可以用前面的步数走到以 $(a_n,0),(0,a_n),(-a_n,0),(0,-a_n)$ 为顶点的正方形上然后在边界上来回徘徊用掉剩下的步数，最后用掉 $a_n$ 回到原点。而如果边长小于 $\dfrac{a_n}{2}$，那那个 $a_n$ 一用就横跨整个正方形了，肯定没法完成任务。

现在考虑枚举这个半径 $d$，考虑 meet-in-the-middle，等价于我们要将所有步数分成两个集合 $S,T$，使得它们都能走到以 $(d,0),(0,d),(-d,0),(0,-d)$ 为顶点的正方形上——显然只要能走上去，由于 $\dfrac{a_n}{2}\le d\le a_n$，剩下的步数肯定都可以在边界上来回徘徊，而且根据对称性，两部分肯定可以汇合。因此我们现在只要 check 什么样的集合能够走到边界上即可，考虑 $\le d$ 的那些元素，如果它们的和超过 $d$ 那显然可以，否则，如果存在一个 $>d$ 的元素 $x$，满足 $\le d$ 的元素之和 $\ge x-d$，那我们肯定可以先走到 $(x-d,0)$ 然后一步走到 $(-d,0)$，否则可以证明是不行的。

从全局的角度考虑，因为 $d$ 是超过最大元素的一半的，所以如果存在元素 $>d$ 那肯定限制更松，显然是更有利的，并且这个元素肯定是越小越好，因此考虑找到 $>d$ 的最小和次小元素 $x,y$，显然 $x$ 必然存在，因为 $a_n\ge d$，但 $y$ 有可能不存在，因此分情况讨论：

- 如果 $y$ 不存在，那么相当于我们要将 $\le d$ 的元素分成两部分，大小分别 $\ge x-d,\ge d$，直接 bitset 优化背包找到可能组合出来的和然后在里面 `_Find_next` 即可。
- 如果 $y$ 存在，那么要求分成的两部分大小分别 $\ge x-d,\ge y-d$，同理 bitset 做。

时间复杂度 $\dfrac{n^2}{\omega}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN=2e5;
int n,a[MAXN+5];bitset<MAXN+5>f;
int main(){
	scanf("%d",&n);for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);ll sum=0;for(int i=1;i<n;i++)sum+=a[i];
	if(sum<a[n])return puts("-1"),0;
	f[0]=1;
	for(int i=a[n]/2,j=0,s=0;i<=a[n];i++){
		while(j<n&&a[j+1]<i)f|=(f<<a[++j]),s+=a[j];
		int x=a[j+1]-i,y=(j==n-1)?i:(a[j+2]-i),pos=f._Find_next(x-1);
		if(s-pos>=y)return printf("%d\n",i),0;
	}
	return 0;
}
```



---

## 作者：Alex_Wei (赞：5)

### [[AGC062D] Walk Around Neighborhood](https://www.luogu.com.cn/problem/AT_agc062_d)

将 $D$ 排序，无解判断是显然的。

考虑检查半径 $r$ 是否合法。

考虑 MITM，将 $D$ 分成两个集合，让它们在边界处汇合：显然，最优方案一定经过边界。

首先易证 $r$ 满足 $\frac {D_n} 2 \leq r \leq D_n$，所以 $2D_i\leq 2r$。这就说明，只要能走到边界，接下来怎么走都无所谓。

进一步地，可知只要边界上任意一点可达，则整个边界可达。

> 考虑判定集合 $X$ 能否走到边界。
>
> 考虑所有 $X_i < r$，如果它们的和 $S \geq r$，显然已经胜利了。否则，考虑最小的 $X_i \geq r$。若 $X_i$ 不存在，那么寄了，否则如果 $S$ 太小，发现怎么走都会走出边界，也寄了。当 $S\geq X_i - r$ 时，根据介值定理容易证明可以走到边界（以落在中心为原点，半径为 $S$ 的正方形上的任意一点为中心，$X_i$ 为半径画正方形，该正方形和边界一定有交），反之易证走出去回不来了。

因此，设 $x, y$ 分别是最小和第二小的 $\geq r$ 的数。

- 若 $x, y$ 均存在，相当于将 $<  r$ 的数分成两部分，一部分之和 $\geq x - r$，另一部分 $\geq y - r$。
- 若 $y$ 不存在，相当于一部分之和 $\geq x - r$，另一部分 $\geq r$。
- 因为 $r\leq D_n$，所以 $x$ 一定存在。

这样可以判定能否走到边界，如何转化为判定合法？发现如果存在 $r' < r$ 满足 $r'$ 合法但 $r$ 走不到边界，那么 $r > D_n$。否则考虑 $D_n$ 所在集合，走 $D_n$ 时如果合法，那么一定能走到边界，矛盾。

因此，在 $\frac {D_n} 2 \leq r \leq D_n$ 的限制下，合法当且仅当能走到边界。

二分套 bitset 优化背包的时间复杂度为 $\mathcal{O}(\frac {n D\log D} {w})$。从小到大枚举 $r$ 并依次往背包加入物品即可做到 $\mathcal{O}(\frac {(n + D)D} w)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ull = unsigned long long;

bool Mbe;

constexpr int mod = 1e9 + 7;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

constexpr int Z = 1e6 + 5;
int fc[Z], ifc[Z];
int bin(int n, int m) {
  if(n < m) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
void init_fac(int Z) {
  for(int i = fc[0] = 1; i < Z; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[Z - 1] = ksm(fc[Z - 1], mod - 2);
  for(int i = Z - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
}

constexpr int N = 2e5 + 5;
int n, d[N];
bitset<N> f;

bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin); 
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> d[i];
  sort(d + 1, d + n + 1);
  ll sum = 0;
  for(int i = 1; i < n; i++) sum += d[i];
  if(sum < d[n]) cout << "-1\n", exit(0);
  f[0] = 1, sum = 0;
  for(int i = d[n] / 2, pt = 0; i <= d[n]; i++) {
    while(pt < n && d[pt + 1] < i) f |= f << d[++pt], sum += d[pt];
    int x = d[pt + 1] - i;
    int y = pt < n - 1 ? d[pt + 2] - i : i;
    int pos = f._Find_next(x - 1);
    if(pos != -1 && sum - pos >= y) {
      cout << i << endl;
      exit(0);
    }
  }
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
/*
g++ a.cpp -o a -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：Para (赞：3)

把曼哈顿距离转换为切比雪夫距离，这样到达的最远距离就转换为 $\max(|x_i|,|y_i|)$，移动 $d$ 的距离转换为某一维变化恰好为 $d$，另一维变化 $\le d$。

假设我们最终的答案为 $m$。首先对于边界 $m$，范围为 $\frac {\max(D_i)} {2} \le m \le \max(D_i)$，无解情况显然只会在 $2\max(D_i) > \sum D_i$ 时出现。此外，行走过程一定是先到达一个边界点再返回原点。

如果我们可以通过一个 $\{D\}$ 集合到其中的一个边界点，一定能够到所有的边界点，现在就可以转换为将点集分为两部分，其中的每一部分都可以到达边界。

那么对于一个点集 $\{D\}$ ，如何判断其可以到达边界？我们应该首先走完 $D_i \le m$ 的部分，如果 $sd = \sum [D_i \le m]D_i \ge m$，则该点集一定满足要求。否则，判断最小的 $D_i(D_i > m)$ 是否满足 $sd + m \ge D_i$。当且仅当这样的 $D_i$ 存在且满足条件才有解。

最后就只用考虑如何划分点集。只需要从小到大的枚举答案 $m$ 并检查，使用 `bitset` 维护我们可以将 $D_i \le m$ 分成的两个集合，剩余 $D_i > m$ 的部分只与最小值与次小值有关，检测在满足最小值构成的 $\{D\}$ 集合合法的情况下，最大的剩余和能否满足次小值构成的集合。

记 $k = \max(D_i)$，时间复杂度为 $O(\frac {k(k+n)} {w})$。

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 18, stdin), p1 == p2) ? EOF : *p1++)
inline ll read() {
	ll x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x;
}
ll n;
ll d[200005];
bitset <200005> f;
int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	n = read();
	for(ll i = 1; i <= n; i++) d[i] = read();
	sort(d + 1, d + 1 + n);
	ll sum = 0;
	for(ll i = 1; i <= n; i++) sum += d[i];
	if(sum - d[n] < d[n]) return printf("-1\n") & 0;
	sum = 0;
	f[0] = 1;
	for(ll m = d[n] / 2, i = 1; m <= d[n]; m++) {
		while(i <= n && d[i] <= m) sum += d[i], f |= (f << d[i]), i++;
		if(i == n + 1) return printf("%lld\n", m) & 0;
		ll x = f._Find_next(d[i] - m - 1);//找到满足 sd + m >= d_i 最小值的 sd 
		if(x != -1 && (sum - x >= m || (i != n && (sum - x) + m >= d[i+1]))) return printf("%lld\n", m) & 0;//检查另一个集合 
	}
	return 0;
}
/*
*/
```



---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc062_d)

**题目大意**

> 给定 $n$ 和 $a_1\sim a_n$，选择一个排列 $p_1\sim p_n$，第 $i$ 步恰好移动 $a_{p_i}$的曼哈顿距离。
>
> 找到一条从原点出发返回原点的路径，最小化路径到原点的最大曼哈顿距离。
>
> 数据访问：$n,a_i\le 2\times 10^5$。

**思路分析**

先对 $a$ 升序排序，考虑什么时候无解，显然 $\sum_{i=1}^{n-1}a_i<a_n$ 时必然无解，假如第一步走 $a_n$，那么无论如何也回不去。

设答案为 $d$，那么一步移动最多 $2d$，因此 $\dfrac{a_n}2\le d\le a_n$，显然最优解一定会经过边界，按这个过程分成两条原点到边界的路径。

由于 $a_i\le a_n\le 2d$，那么只要找到这两条路径，剩余的步数可以直接在边界上移动掉。

根据调整法，一条路径可以走到边界上，那么这条路径能走到边界上的任意一个点。

那么我们找到一个 $S$，一个 $T$，使得 $S\cap T=\varnothing$ 并且用这两个集合里的移动分别能走到边界上。

先进行所有 $<d$ 的操作，如果这些距离的和 $\ge d$，那么直接合法，否则我们考虑用一个 $\ge d$ 的操作 $a_k$，我们只要用 $\le d$ 的操作走到 $a_k-d$ 上即可。

显然两个 $a_k$ 分别要取 $\ge d$ 的最小值 $x$ 和次小值 $y$，不存在 $y$ 则取 $y=2d$。

然后我们要把 $\le d$ 的元素分成两部分分别大于 $x-d,y-d$，维护 $<d$ 的数对应的背包，求出 $\ge x-d$ 的最小子集，剩余的判断是否 $\ge y-d$ 即可，这个过程可以 `std::bitset ` 维护。

容易发现所求的子集和 $<y-d+d\le a_n$，那么只要维护 $\mathcal O(V)$ 个位置的背包。

时间复杂度 $\mathcal O\left(\dfrac{nV}\omega\right)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5;
bitset <MAXN*2> f,g;
int n,a[MAXN];
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	if(accumulate(a+1,a+n,0ll)<a[n]) return puts("-1"),0;
	ll s=0; f[0]=1;
	for(int d=a[n]/2,i=0;d<=a[n];++d) {
		while(i<n&&a[i+1]<d) s+=a[++i],g=f,g<<=a[i],f|=g;
		int x=a[i+1]-d,y=(i+2>n?d:a[i+2]-d);
		if(s<x) continue;
		int q=f._Find_next(x-1);
		if(s-q>=y) return printf("%d\n",d),0;
	}
	puts("-1");
	return 0;
}
```

---

## 作者：Larunatrecy (赞：0)

神秘思维题，感觉有点像是二维的摩尔投票。

我们先从小到大排序，如果前 $n-1$ 个数的和 $<a_n$ 一定无解，因为 $a_n$ 不管咋走都会超。

否则，一定有解，并且答案一定在 $[\frac{a_n}{2},a_n]$ 中，这是因为：上界 $a_n$ 的构造很简单，我们先走到 $a_n$ 所在的正方形上，然后剩下的步长一定与这个正方形都有交，因此我们能一直保持在边界上，最后用 $a_n$ 走回去就好了。下界 $\frac{a_n}{2}$ 也是因为小于这个，$a_n$ 不管咋走都会出去。

那么我们枚举答案 $r\in[\frac{a_n}{2},a_n]$，注意到我们走的过程形如：

- 先用若干步数走到 $r$ 的正方形上
- 中间一些步数在正方形边界上跳
- 再用一些步数走回去

并且因为 $r\in[\frac{a_n}{2},a_n]$ 所以只要能走到边界上就一定能保持在边界上，所以我们只需要找两个集合，满足一个集合能走过去，一个集合能走回来就行了。

判断一个集合 $S$ 能否走到 $r$ 的正方形边界：

- 若 $S$ 中小于 $r$ 的数的和 $\geq r$，那么显然一定能走到 $r$。
- 否则，我们一定要用 $\geq r$ 的数，因为用了它之后一定要么走出去要么走到边界上，所以用一个就够了，记为 $x$。考虑什么时候不合法，发现若 $x$ 很大，$r$ 很小，我们就很容易跳出去，故 $x$ 一定保留最小的一个，并且此时可以发现跳 $x$ 的位置越偏越不容易跳出去，所以我们一定把 $<r$ 的数沿着同一个方向走，所以记这些数的和为 $s$，那么合法的充要条件是 $s\geq x-r$。

因为我们要分成两个集合，并且可以发现如果有 $\geq r$ 的数一定用比不用好，因为 $r\in [\frac{a_n}{2},a_n],x-r\leq r$ 更容易满足，并且因为 $r\leq a_n$，所以一定至少有一个 $x$ 可以用，如果还有就再保留次小的，否则就只能选择第一种。

现在我们要找两个集合，第一个大小 $\geq A$，第二个 $\geq B$，那么一定每个数都被选进某一个里。

用 `bitset` 维护可能集合大小，每次 `_Find_next` 找到 $\geq A$ 的最小的子集，然后判断剩下的数是不是 $\geq B$ 就行了。

复杂度 $O(\frac{n^2}{w})$。

---

## 作者：zhiyin123 (赞：0)

复杂度 $O(M\sqrt M)$（其中 $\displaystyle M = \max_i D_i$）的**官方做法**。本篇包含官方题解的翻译和本人的代码。

# 正文

*by [evima](https://atcoder.jp/users/evima)*

让 $\displaystyle \max_{1\leq i \leq N}D_i=M$。我们知道从三角不等式可知，当 $\displaystyle \sum_{i=1}^{N}D_i < 2M$ 时，无法在 $N$ 次动作后返回原点。从现在开始，我们将假设 $\displaystyle 2M \leq \sum_{i=1}^{N}D_i$。

## [1] 考虑由于移动而导致的离原点距离的变化

对于实数 $D$、$R$、$R'\ (R' \leq R)$ 和 $(a, b)\ (0 \leq a, b)$ 满足 $|a|+|b|=R$，我们考虑在什么条件下存在满足以下条件的 $(a', b')$：

* $|a'|+|b'|=R'$，且
* $|a-a'|+|b-b'|=D$。

从三角不等式可知，必须满足 $R-R' \leq D \leq R+R'$。

（在下图中，日文文字说："A 和 B 之间的距离是 $R-R'$，A 和 C 之间的距离是 $R+R'$。"）

![0494c054ffbed0a07634863f97dee5ec.jpg (641×508)](https://img.atcoder.jp/agc062/0494c054ffbed0a07634863f97dee5ec.jpg)

对于 $D=R-R'$，当 $0 \leq a \leq R'$ 时，两个条件由 $(a', b')=(a, b-(R-R'))$ 满足，当 $R' \leq a \leq R$ 时，它们由 $(a', b')=(a-(R-R'), b)$ 满足（图中的 $A$ 和 $B$）。

此外，对于 $D=R+R'$，当 $0 \leq a \leq R'$ 时，两个条件由 $(a', b')=(-a, (R-R')-b)$ 满足，当 $R' \leq a \leq R$ 时，它们由 $(a', b')=((R-R')-a, -b)$ 满足（图中的 $A$ 和 $C$）。

从上述情况可知，对于任何 $(a, b)$，当 $D=R-R', R+R'$ 时，总存在满足条件的 $(a', b')$，而且由于 $(a', b')$ 在 $|x|+|y|=R'$ 上连续移动时，$|a-a'|+|b-b'|$ 也连续变化，所以当 $R-R' \leq D \leq R+R'$ 时，总能找到这样的一对。

对于 $R < R'$ 的情况，可以通过反向考虑得到同样的结论。

到目前为止讨论的特别重要的点可以总结为以下两点：

* 对于任何 $(a, b)$ 和 $D$ 满足 $|R'-R| \leq D \leq|R+R'|$ 且 $|a|+|b|=R$，上述 $(a', b')$ 都存在；
* 对于任何 $(a, b)$ 和 $D$ 满足 $0 \leq D \leq 2R$ 且 $|a|+|b|=R$，都存在满足 $|a'|+|b'|=R$ 和 $|a-b'|+|a-b'|=D$ 的 $(a', b')$。

## [2] 固定顺序的决策问题

我们考虑当每次移动距离 $D_i$ 是固定的情况下，是否可能完成 $N$ 次动作并满足 $|x_i|+|y_i| \leq K$ 的决策问题。首先必须满足 $D_i \leq 2K$。

设 $S_i=D_1+D_2+\dots+D_i$ 和 $T_i=D_i+D_{i+1}+\dots+D_N$。

设 $L$ 为最小的满足 $K \leq S_i$ 的 $i$。从三角不等式可知，必须满足 $D_L \leq S_{L-1}+K$。如果满足这一条件，在进行了 $L$ 次动作后，你可以位于任意在外圆周（$|x|+|y|=K$）的点上，这可以从 [1] 中的讨论看出。同样地，设 $R$ 为最大的满足 $K \leq T_i$ 的 $i$，则必须满足 $D_{R} \leq T_{R+1}+K$。如果满足这一条件，无论你在外圆周的哪个位置，在进行了 $R-1$ 次动作后都可以返回原点。

那么，如果你可以在外圆周上开始并完成第 $(L+1)$ 到第 $(R-1)$ 次动作，你也可以完成 $N$ 次动作并满足条件。这确实是可能的，因为从 [1] 末尾的讨论可以看出，你总是可以停留在外圆周上。

因此，如果 $L$ 和 $R$ 存在且 $L < R$，以下是必要且充分的条件：

* $D_i \leq 2K$
* $D_L \leq S_{L-1}+K$
* $D_R \leq T_{R+1}+K$

让我们考虑其他情况。

如果 $D_i$ 的和小于或等于 $2K$，目标总是可以实现的。

（证明略）

如果和大于 $2K$，那么 $L$ 和 $R$ 确实存在，且 $L=R$。首先必须满足上述三个条件。如果满足这些条件，可以考虑以下方式进行 $N$ 次动作：移动到距原点 $S_{L-1}$ 的格点 $\to$ 精确移动 $D_L$ 到距原点 $T_{R+1}$ 的格点 $\to$ 返回原点，这是可能的，因为 $|S_{L-1}-T_{R+1}| \leq D_L \leq S_{L-1}+T_{R+1}$ 成立。因此，在这种情况下，上述三个条件也是必要且充分的。

## [3] 没有固定顺序的决策问题

基于 [2] 中的讨论，我们考虑 $D_i$ 顺序不固定的决策问题。首先，如果 $M \leq K$，总是可以完成 $N$ 次动作并满足条件。从现在开始，我们将处理 $\displaystyle \frac{M}{2} \leq K < M$ 的情况。

在这种情况下，[2] 中考虑的 $L$ 和 $R$ 总是存在。如果只有一个 $D_i$ 大于 $K$（即只有 $M$），决策问题的答案不会改变，因为我们可以将另一个 $M$ 放在 $D_i$ 中，并连续执行距离为 $M$ 的移动。因此，我们只需考虑至少有两个 $D_i$ 大于 $K$ 的情况。

在这种情况下，由于 $L < R$ 总是成立，决策问题可以简化为是否可以创建两个集合 $\{i_1, i_2, \dots, i_n\}$（没有公共元素）满足以下条件：

* $D_{i_1} + D_{i_2} + \dots D_{i_{n-1}} < K$，
* $K \leq D_{i_1} + D_{i_2} + \dots D_{i_{n-1}}+D_{i_n}$，且
* $D_{i_n} \leq K+D_{i_1} + D_{i_2} + \dots D_{i_{n-1}}$。

从第一个条件可知 $D_{i_k} < K\ (k\neq n)$。如果 $D_{i_n} \leq K$，第三个条件总是成立。现在，如果第一个条件不成立而 $D_{i_k} < K\ (k\neq n)$ 满足，我们可以通过适当删除 $i_k$ 来重新创建一个满足这些条件的集合。因此，我们只需创建一个满足以下条件的集合：

* $D_{i_k} < K\ (k\neq n)$，
* $K \leq D_{i_1} + D_{i_2} + \dots D_{i_{n-1}}+D_{i_n}$，且
* $D_{i_n} \leq K+D_{i_1} + D_{i_2} + \dots D_{i_{n-1}}$。

此外，当 $D_{i_n} \leq K$ 成立时，我们可以添加另一个大于 $K$ 的 $D_i$ 而不违反这些条件（因为至少有两个 $D_i$ 大于 $K$）。在这种情况下，第二个条件总是成立，所以问题变为是否可以创建两个集合 $\{i_1, i_2, \dots, i_n\}$ 满足以下条件：

* $D_{i_k} < K\ (k\neq n)$，且
* $D_{i_n} \leq K+D_{i_1} + D_{i_2} + \dots D_{i_{n-1}}$。

很明显，$D_{i_n}$ 应尽可能小，所以我们应该选择两个最小的大于 $K$ 的 $D_i$。因此，我们可以将问题简化为以下部分和问题，其中 $S$ 是小于或等于 $K$ 的 $D_i$ 之和，$A$ 和 $B$ 是大于 $K$ 的两个最小 $D_i$：

* 判断是否存在 $D_i$ 的部分和 $s$ 满足 $K$ 以下，且 $A-K \leq s \leq S-(B-K)$。

让我们考虑 $S$ 很大的情况。我们将按升序添加小于或等于 $K$ 的 $D_i$，并在和大于或等于 $A-K$ 时停止添加来创建部分和 $s$。由于添加的 $D_i$ 小于或等于 $K$，我们有 $s < A$，如果 $A+(B-K) \leq S$，这个部分和满足上述不等式。特别是，如果 $2M \leq S$，这个不等式总是成立，所以我们只需考虑 $S < 2M$ 的情况。在这种情况下，不同 $D_i$ 的数量是 $O(\sqrt{M})$，所以部分和问题可以在 $O(M\sqrt{M})$ 时间内解决。

使用这种方法进行二分搜索，整个问题可以在 $O(M\sqrt{M}\log M)$ 时间内解决。但是，考虑到当 $\displaystyle \frac{M}{2}$ 和 $K$ 之间（包括端点）有两个 $D_i$ 时，总是存在满足上述条件的部分和，所以问题可以在 $O(M\sqrt{M})$ 时间内解决。

# 代码

```cpp
#include<cassert>
#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<utility>
#include<numeric>
#include<algorithm>
using std::cerr; using std::setw; using std::endl;
using std::cin; using std::cout;
constexpr int MAXN=2e5;
using ll=long long;
constexpr int INFi=0x3f3f3f3f;
int N=0,D[MAXN+5]={};
int M=0;
void output(int ans){
    cout<<ans<<'\n';
    exit(0);
    return ;
}
constexpr int MAXV=MAXN<<1;
bool f[MAXV+5]={}; int V=0;
int Pre[MAXV+5];
bool check(int l,int r){
    l=std::max(l,0); r=std::min(r,V);
    if(l>r) return 0;
    if(l==0) return Pre[r]>0;
    return Pre[r]-Pre[l-1]>0;
}
void checkdp(int p){
    static bool tmp[MAXV+5];
    std::fill(tmp,tmp+MAXV+5,0);
    tmp[0]=1;
    for(int i=1;i<=p;i++){
        for(int j=V;j>=D[i];j--){
            if(tmp[j-D[i]]==1) tmp[j]=1;
        }
    }
    for(int j=0;j<=V;j++) assert(tmp[j]==f[j]);
    return ;
}
void update(int v,int cnt){
    static int buc[MAXN+5];
    static bool g[MAXV+5];
    std::fill(buc,buc+v,0);
    std::copy(f,f+V+1,g);
    ll delt=v*(cnt+1);
    for(int i=0;i<=V;i++){
        if(g[i]==1) buc[i%v]++;
        if(i-delt>=0&&g[i-delt]==1) buc[i%v]--;
        if(buc[i%v]>0) f[i]=1;
    }
    std::copy(f,f+V+1,Pre);
    std::partial_sum(Pre,Pre+V+1,Pre);
    return ;
}
void solve(){
    int p=0,S=0;
    for(int k=1;k<=M;k++){
        int cnt=0;
        while(p+1<=N&&D[p+1]==k){
            ++p; ++cnt;
            S+=k;
            if(S>=(M<<1)){
                output(std::max(M>>1,k));
            }
        }
        if(cnt>0){
            update(k,cnt);
        }
        if(k>=(M>>1)){
            if(check(D[p+1]-k,std::min(S-D[p+2]+k,S+D[p+2]-k))){
                output(k);
            }
        }
    }
    output(M);
    return ;
}
int main(){
    std::ios::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);
    cin>>N; for(int i=1;i<=N;i++) cin>>D[i];
    std::sort(D+1,D+N+1);
    M=D[N];
    if((M<<1)>std::accumulate(D+1,D+N+1,0ll)) output(-1);
    V=M<<1;
    f[0]=1; std::fill(Pre,Pre+V+1,1);
    solve();
    return 0;
}
```

---

