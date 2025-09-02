# [AGC054E] ZigZag Break

## 题目描述

给定整数 $N,A$。请计算满足以下条件的 $(1,2,\cdots,N)$ 的排列 $P=(P_1,P_2,\cdots,P_N)$ 的个数，并将结果对 $998244353$ 取模。

- $P_1=A$。
- 通过重复以下操作，可以将 $P$ 的元素个数变为 $2$：
  - 选择 $3$ 个**连续的**元素 $x,y,z$。此时，要求 $y<\min(x,z)$ 或 $y>\max(x,z)$ 成立。然后，将 $y$ 从 $P$ 中删除。

对于每个输入文件中的 $T$ 个测试用例，请输出答案。

## 说明/提示

### 限制条件

- $1\leq T\leq 5\times 10^5$
- $3\leq N\leq 10^6$
- $1\leq A\leq N$
- 输入的所有值均为整数

### 样例解释 1

例如，当 $N=4,A=2$ 时，$P=(2,1,4,3)$ 满足条件。以下是操作的一个例子：
- 选择 $(x,y,z)=(2,1,4)$，删除 $1$，$P$ 变为 $(2,4,3)$。
- 选择 $(x,y,z)=(2,4,3)$，删除 $4$，$P$ 变为 $(2,3)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8
3 1
3 2
3 3
4 1
4 2
4 3
4 4
200000 10000```

### 输出

```
1
2
1
3
5
5
3
621235018```

# 题解

## 作者：UnyieldingTrilobite (赞：2)

这年头真是什么牛鬼蛇神都能数数了。

不失一般性，我们先考虑 $P_1\lt P_n$ 的情况。

我们试图找到一个 $P$ 可以被消到只剩两个数的充要条件。我们将会证明接下来展示的条件是充分必要的：

+ 存在 $P$ 中相邻的两个数 $P_i$，$P_{i+1}$，前者 $\le P_1$，后者 $\ge P_n$。

充分性：

考虑从 $P_1$ 遍历到 $P_i$，维护一个单调栈，考虑到有 $P_i\lt P_1$ 卡住，最后栈中一定是从 $P_1$ 到 $P_i$ 单调降的，实际上这个单调栈可以模拟题目的流程。从 $P_n$ （反向）遍历到 $P_{i+1}$ 同理。于是我们发现，最后一定至多是俩递降序列拼起来，可以从中间开始简单处理，于是 $P$ 可以被消到只剩两个数。

必要性：

我们归纳证明，只要 $P$ 上的一个左端点小于右端点的区间能内部消到只剩头尾，那么区间内一定存在一组相邻的数，前者不大于区间左端点的数，后者不大于区间右端点的数。归纳边界区间长度等于二在此省略，归纳流程在此省略，只展示关键的化归步骤。

对于一个长度不小于 $3$ 的区间，考虑最后一次被消去的数，它要么小于区间左端点，要么大于区间右端点，不妨为前者（后者同理）。那么我们考虑这个数的位置到区间右端点，它一定能被内部消完，由归纳假设，一定存在一组相邻的数，前者不大于该最后一次被消去的数，进而不大于区间左端点，右者不小于区间右端点。

现在我们证明了这个条件是充要的。考虑从反面入手，那么我们需要计数的 $P$ 实际上就是不存在这样的相邻数组。由于 $P_1=A$，我们不妨设 $P_n=A+k$。注意到当 $k=1$ 时，$P_2$ 为了不大于 $P_n$ 必须填小于 $P_1$ 的数，同理 $P_3$ 到 $P_n$ 都必须填小于 $P_1$ 的数，与 $P_n\gt P_1$ 矛盾。于是我们需要保证 $k\ge2$。

考虑将序列初始化为只有 $P_1$ 和 $P_n$，接下来我们会展示如何向序列里插入新数。考虑到介于 $P_1$ 和 $P_n$ 的数的顺序实际上对贡献没有任何影响，于是我们可以直接以 $(k-1)!$ 的方案数将这些数全部插入序列中。

接下来考虑插入小于 $P_1$ 的数。我们发现，原本有 $k-1$ 个空位可以插入（$P_n$ 之前那一个空位不能），而每插入一个数，空位就会多一个。换而言之，对于第 $i$ 个数，我们有 $k-i+2$ 种插法。对于大于 $P_n$ 的数，我们注意到每次插入小于 $P_1$ 的数的时候会新增两个空位但同时废掉两个空位（原来的空位和小插入数后面的空位，如果插入在 $P_1$ 之后那一个空位则改为增一废一），对插入方案数没有任何影响，那么依然是对于第 $i$ 个数有 $k-i+2$ 种插法。

那么对于给定的 $k$，它对答案的贡献就是：

$$\frac{(A+k-3)!(n-A-2)!(k-1)!}{(k-2)!^2}$$

那么总的答案就是

$$\sum_{k=2}^{N-A}\frac{(A+k-3)!(n-A-2)!(k-1)!}{(k-2)!^2}$$

简单化简一下

$$(n-A-2)!(A-1)!\sum_{k=0}^{n-A-2}\binom{A+k-1}k(k+1)$$

注意到 $\binom{A+k-1}k\times k=\binom{A+k-1}{k-1}\times A$，那么后面那个 $\sum$ 可以改写成 $A\times\sum_{k=0}^{n-A-3}\binom{A+k}k+\sum_{k=0}^{n-A-2}\binom{A-1+k}k$。

记 $f(x,y)=\sum_{i=0}^{x}\binom{y+i}i=1+\sum_{i=1}^{x}(\binom{y+i+1}{i}-\binom{y+i}{i-1})=\binom{x+y+1}{x}$，则容易发现要求的式子变成了

$$(n-A-2)!(A-1)!(A\times f(n-A-3,A)+f(n-A-2,A-1))$$

也就是

$$(n-A-2)!(A-1)!(A\times\binom{n-2}{n-A-3}+\binom{n-2}{n-A-2})$$

化简一下

$$(n-2)!(\frac{n-A-2}{A+1}+\frac1A)$$

然后这个人畜无害的东西就非常好算了，记得特判 $A\ge n-1$。注意以上所有讨论都基于文章开头的一句“我们先考虑 $P_1\lt P_n$ 的情况”，记得反过来再做一遍，最后别忘了还要拿总的方案数减掉我们计算出来的答案。然后就做完了，代码非常好写。

```cpp
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef modint998244353 mint;
constexpr int N = 1e6 + 9;
mint fac[N], ifc[N];
void init_fac() {
  fac[0] = 1;
  for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i;
  ifc[N - 1] = fac[N - 1].inv();
  for (int i = N - 1; i; --i) ifc[i - 1] = ifc[i] * i;
}
mint inv(int x) { return ifc[x] * fac[x - 1]; }
mint calc(int n, int a) {
  if (a >= n - 1) return 0;
  return fac[n - 2] * ((n - a - 2) * inv(a + 1) + inv(a));
}
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init_fac();
  int t, n, a;
  for (cin >> t; t; --t) {
    cin >> n >> a;
    cout << (fac[n - 1] - calc(n, a) - calc(n, n - a + 1)).val() << '\n';
  }
  return cout << flush, 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc054_e)

**题目大意**

> 对于一个 $n$ 阶排列 $a$，一次操作可以删除 $a_i>\max(a_{i+1},a_{i-1})$ 或 $a_i<\min(a_{i+1},a_{i-1})$ 的 $a_i$。
>
> 求有多少 $a_1=x$ 的 $n$ 阶排列可以通过操作删成 $2$ 个元素。
>
> 数据范围：$n\le 10^6$。

**思路分析**

不妨设 $a_1<a_n$，$a_1>a_n$ 等价于统计 $a_1=n-x+1$ 的方案数。

一个排列能被删成两个元素的充分必要条件是存在 $i$ 使得 $a_i\le a_1<a_n\le a_{i+1}$：

考虑充分性：不断删除 $(1,i)$ 和 $(i+1,n)$ 内部元素，最终得到的序列一定有 $a_1>a_2>\cdots>a_i<a_{i+1}>a_{i+2}>\cdots>a_n$，先删 $a_i\sim a_2$，再删 $a_{i+1}\sim a_{n-1}$ 就是一组方案。

必要性可以归纳法证明。

计算不合法排列数，相当于 $[1,a_1]$ 的元素后面不能是 $[a_n,n]$ 的元素，设 $a_n=a_1+k$，得到方案数 $(k-1)!(k-1)^{\overline{k-2}}(k-1)^{\overline{x-1}}$。

化简得到 $(n-x-2)!(x-1)!\sum_{k=0}^{n-x-2}\binom{x+k-1}{k}(k+1)$，把 $\binom{x+k-1}{k}(k+1)$ 看成 $\binom{x+k-1}{k}+x\binom{x+k-1}{k-1}$。

分别用组合数上指标前缀和得到答案为 $(n-2)!\left(\dfrac 1x+\dfrac{n-x-2}{x+1}\right)$。

时间复杂度 $\mathcal O(1)$。

**代码呈现**

```cpp
#include<bits/stdc++.h> 
#define ll long long
using namespace std;
const int MAXN=1e6+5,MOD=998244353;
ll fac[MAXN],inv[MAXN];
ll solve(int n,int p) {
	if(p>=n-1) return 0;
	return (inv[p+1]*(n-p-2)+inv[p])%MOD*fac[n-2]%MOD;
}
signed main() {
	for(int i=fac[0]=1;i<MAXN;++i) fac[i]=fac[i-1]*i%MOD;
	inv[1]=1;
	for(int i=2;i<MAXN;++i) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
	int T; scanf("%d",&T);
	for(int n,p;T--;) {
		scanf("%d%d",&n,&p);
		printf("%lld\n",(fac[n-1]+MOD-solve(n,p)+MOD-solve(n,n-p+1))%MOD);
	}
	return 0;
}
```

---

