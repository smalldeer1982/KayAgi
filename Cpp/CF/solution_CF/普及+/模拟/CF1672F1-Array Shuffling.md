# Array Shuffling

## 题目描述

oolimry has an array $ a $ of length $ n $ which he really likes. Today, you have changed his array to $ b $ , a permutation of $ a $ , to make him sad.

Because oolimry is only a duck, he can only perform the following operation to restore his array:

- Choose two integers $ i,j $ such that $ 1 \leq i,j \leq n $ .
- Swap $ b_i $ and $ b_j $ .

The sadness of the array $ b $ is the minimum number of operations needed to transform $ b $ into $ a $ .

Given the array $ a $ , find any array $ b $ which is a permutation of $ a $ that has the maximum sadness over all permutations of the array $ a $ .

## 说明/提示

In the first test case, the array $ [1,2] $ has sadness $ 1 $ . We can transform $ [1,2] $ into $ [2,1] $ using one operation with $ (i,j)=(1,2) $ .

In the second test case, the array $ [3,3,2,1] $ has sadness $ 2 $ . We can transform $ [3,3,2,1] $ into $ [1,2,3,3] $ with two operations with $ (i,j)=(1,4) $ and $ (i,j)=(2,3) $ respectively.

## 样例 #1

### 输入

```
2
2
2 1
4
1 2 3 3```

### 输出

```
1 2
3 3 2 1```

# 题解

## 作者：chzhc (赞：10)

### 题意

给出长度为 $n$ 的数组 $a$，你需要构造一个 $a$ 的置换 $b$，使得 $b$ 经过**只交换操作**后成为 $a$ 的**最少交换次数最大**。

数据范围：$2 \leq n \leq 2 \times 10^5$，$1 \leq a_i \leq n$。

### 做法

设 $a$ 数组中，元素 $i$ 出现了 $cnt_i$ 次，我们令 $cnt_1 \geq cnt_2 \geq \cdots \geq cnt_k$（即将元素重编号，按照出现次数排名）。

假设 $b$ 数组已经确定，我们考虑如何求出这个最少交换次数。考虑两个图：

$G_1$：若 $b_i = a_j$ 则连一条 $i \to j$ 的边，表示 $b_i$ 最终有可能移动到位置 $j$。

$G_2$：对于某一种方案，若 $b_i$ 最终要移动到位置 $j$ 则连一条 $i \to j$ 的边，容易发现每个点只会有一条出边和一条入边，那么最终的图一定由若干个环组成。

结论 1. 对于某一张图 $G_2$，该方案的最少交换次数 $F(G_2)$ 是 $\operatorname{size}(G_2) - \operatorname{ring}(G_2)$（其中 $\operatorname{size}(G)$ 是图 $G$ 的大小，$\operatorname {ring}(G)$ 表示图 $G$ 环的个数）。

引理 1. 对于 $\operatorname {size}(G) \geq 2$ 的环 $G$，对任意两个不同结点进行交换后会成为两个环。

证明如下：

对于环 $g_1 \to g_2 \to \cdots \to g_k\to g_1$，考虑交换 $g_i, g_j(1 \leq i < j \leq k)$，图会变为 $g_1 \to \cdots \to g_i \to g_{j+ 1} \to \cdots \to g_k \to  g_1$ 和 $g_{i + 1} \to \cdots \to g_j \to g_{i + 1}$ 这两个环。

引理 2. 对于两个环，在两个环中各取一个结点进行交换后会合并为一个环。

证明如下：

对于环 $g_1 \to g_2 \to \cdots \to g_k \to g_1$ 和 $f_1 \to f_2 \to \cdots \to f_h \to f_1$，考虑交换 $g_i, f_j(1 \leq i \leq k, 1 \leq j \leq h)$，图会变为 $g_1 \to \cdots \to g_i \to f_{j + 1} \to \cdots \to f_h \to f_1 \to \cdots \to f_j \to g_{i + 1} \to \cdots \to g_k \to g_1$ 这一个环。

引理 3. 对于一个环 $G$，它的最少交换次数 $F(G)$ 为 $\operatorname{size}(G) - 1$。

证明如下：

考虑使用数学归纳法证明：

1. $\operatorname{size}(G) = 1$ 时，$F(G) = 0$，$\operatorname{size}(G) = 2$ 时，$F(G) = 1$；
2. 假设当 $\operatorname{size}(G) \leq k, k \geq 2$ 时，引理 3 成立，当 $\operatorname{size}(G) = k + 1$ 时，肯定是交换两个不同结点，根据引理 1 可知，会分裂出两个环，每个环的大小一定 $\leq k$，即分裂出的两个环都满足引理 3，那么就有 $F(G) = F(G_1) + F(G_2) + 1 = \operatorname{size}(G_1) - 1 + \operatorname{size}(G_2) - 1 + 1 = \operatorname{size}(G) - 1$。即 当 $\operatorname{size}(G) = k + 1$ 时，$F(G) = \operatorname{size}(G) - 1$ 也成立。故引理 3 得证。

结论 1 证明如下：

若每次操作仅对一个环内的结点进行操作，那么根据引理 3 可知，至少要进行 $\operatorname{size}(G) - \operatorname{ring}(G)$ 次，若对不同环的结点进行操作，根据引理 2 可知环会合并，容易发现这样操作一定更劣。

结论 2. 最终方案的图中不会出现一个环内出现两个值相同的元素的情况。

证明如下：

考虑出现两个相同值元素的环：$g_1 \to g_2 \to \cdots \to g_s \to \cdots \to g_t \to \cdots \to g_k \to g_1$（其中 $\operatorname{val}(g_s) = \operatorname{val}(g_t)$），那么根据结论 1，我们会最大化环的个数从而使得交换次数最少，那么上述的环可以分为两个环：$g_1 \to \cdots \to g_s \to g_{t + 1} \to \cdots \to g_k \to g_1$ 和 $g_{s + 1} \to \cdots \to g_t \to g_{s + 1}$，故不可能出现一个环内出现两个值相同的元素的情况。

回到本题，根据结论 1 容易发现我们需要最小化**最大化环**的个数。设 $cnt$ 为 $a$ 中出现次数最多的数的个数。那么根据结论 2，这个环的个数至少有 $cnt$ 个，即最少交换次数最多为 $n - cnt$，下面给出一种构造方案使得答案为 $n - cnt$。

构造如下：

1. 尽可能多地选定各不相同的几个数；
2. 将它们按照 **大小顺序** 循环移动，每个数移动到恰好大于它的那个位置（最大的数移动到 $1$ )。

如：
$$
a = (1, 3, 2, 4, 2, 1, 4)
$$
$$
b = (*, *, *, *, *, *, *)
$$

$$
a = (\mathbf1, \mathbf3, \mathbf2, \mathbf4, 2, 1, 4)
$$

$$
b = (4, 2, 1, 3, *, *, *)
$$
$$
a = (1, 3, 2, 4, \mathbf2, \mathbf1, \mathbf4) 
$$
$$
b = (4, 2, 1, 3, 1, 4, 2)
$$
结论 3. 按照上述构造的 $b$，对应的图 $G_1$ 中不存在环不经过出现次数最多的元素 $1$。

证明如下：

若存在这么一个环，我们考虑这个环 $g_1 \to g_2 \to \cdots \to g_k \to g_1$，因为不经过 $1$，所以满足如下式子：
$$
b_{g_1} = a_{g_2} > b_{g_2} = a_{g_3} > \cdots > b_{g_k} = a_{g_1} > b_{g_1}
$$
显然矛盾，故结论 3 得证。

考虑如何方便的构造出上述的 $b$，我们将 $a$ 进行排序，然后按照 $cnt$ 进行循环分组（$a_1$ 放到 $a_{1 + cnt}$ 下，$a_2$ 放到 $a_{2 + cnt}$ 下 ... $a_{n - cnt + 1} \sim a_n$ 均放到 $a_1$ 下），这样便能构造出 $cnt$ 个环，且满足上述条件。

时间复杂度：$\mathcal O(n \log n)$。

[评测链接](https://codeforces.com/contest/1672/submission/155039032)。

---

## 作者：Alex_Wei (赞：5)

假设 $a$ 是一个排列，连边 $a_i\to b_i$。注意到一个环恰好需要环长减 $1$ 步归位，因此答案为 $n$ 减去环的个数，只需保证 $a_i\to b_i$ 形成一个大环即可。

若 $a$ 不是排列，不失一般性地，假定 $i$ 为 $a$ 中出现次数第 $i$ 多的数，其数量为 $c_i$。类似地，我们发现环的个数至少为 $c_1$，因为一个环不会经过同一个数两次。进一步地，若存在一个环不经过 $1$，则必然不优，因为此时图上出现了大于 $c_1$ 个环。

考虑这样一个构造：设 $k = \max a_i$，则构造环 $1\to 2\to\cdots  \to k \to 1$，然后删去 $1\sim k$ 各一个得到新的环。容易发现若删去 $1$，则剩余部分不可能有环。

时间复杂度 $\mathcal{O}(n\log n)$，可以桶排做到线性。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
inline int read() {
  int x = 0;
  char s = getchar();
  while(!isdigit(s)) s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return x;
}
constexpr int N = 2e5 + 5;
int n, a[N], cnt[N];
vector<int> buc[N];
void solve() {
  n = read();
  for(int i = 1; i <= n; i++) cnt[i] = 0, buc[i].clear();
  for(int i = 1; i <= n; i++) buc[++cnt[a[i] = read()]].push_back(i);
  for(int i = 1; i <= n; i++) {
    sort(buc[i].begin(), buc[i].end(), [&](int x, int y) {return a[x] < a[y];});
    for(int j = 1; j < buc[i].size(); j++) swap(a[buc[i][j - 1]], a[buc[i][j]]);
  }
  for(int i = 1; i <= n; i++) cout << a[i] << " ";
  cout << "\n";
}
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  int T;
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：dead_X (赞：4)

## 思路
注意到最优交换策略一定是将这个序列拆成若干段，每段 $a,b$ 组成的可重集相等，然后每段通过 $|S|-1$ 次操作还原。

于是 F1 就是叫你构造使得段数最大值最小，F2 就是让你判断最大值是否取到最小。

段数最大值最小可以通过出现次数最多的那个数来做，不难证明答案即为每个数出现次数的最大值，我们只需要设计一种方案让它取到。

假设现在有 $a_1$ 个 $1$，$a_2$ 个 $2$，以此类推，记 $a_1\geq a_2\geq\cdots$，一种策略就是每次先把 $a_i\neq 0$ 的全取出来一个，循环位移一位，不难证明这样的构造需要至少分成 $a_1$ 段。

对于 F2，我们考虑 F1 中每段的末尾都一定是 $i\to 1$，我们可以抓住这一点，考虑所有连向 $1$ 的边。手模可以发现，可以分成 $a_1$ 段当且仅当去掉所有连向 $1$ 的边之后图是 DAG。

---

## 作者：DaiRuiChen007 (赞：2)

# CF1672F1 题解



## 思路分析

先考虑如何计算一个 $\{a_i\}$ 的排列 $\{b_i\}$ 的权值：对于个 $i$，建立有向边 $a_i\to b_i$，得到一张有向图 $\mathbf G$。

定义 $\operatorname{cyc}(\mathbf G)$ 表示 $\mathbf G$ 的最大环拆分的大小，即把 $\mathbf G$ 拆成尽可能多的环使得每条边都恰好在一个环中时拆分成环的数量。

注意到如下的观察：

> 观察一：
>
> 那么 $\{b_i\}$ 的权值等于 $n-\operatorname{cyc}(\mathbf G)$。
>
> 证明如下：
>
> 注意到交换 $(b_i,b_j)$ 等价于交换 $a_i\to b_i$ 和 $a_i\to b_j$ 的终点，我们的目标就是使得 $\mathbf G$ 中产生 $n$ 个环。
>
> 而一次操作可以根据 $b_i,b_j$ 在 $\operatorname{cyc(\mathbf G)}$ 对应的分解中分成是否在同一个环中的两种情况。
>
> [![pSCKeKg.png](https://s1.ax1x.com/2023/01/01/pSCKeKg.png)](https://imgse.com/i/pSCKeKg)
>
> 由上图可得，只要 $b_i,b_j$ 在同一个环中，无论如何 $\mathbf G$ 中的环数会 $+1$，而如果 $b_i,b_j$ 不在同一个环中，那么 $\mathbf G$ 中的环数一定会 $-1$。
>
> 因此对于任意的大小为 $k$ 的环分解，至少需要操作 $n-k$ 次，而不断操作两个相邻的 $b_i,b_j$ 给了我们一种操作 $n-k$ 次的方法。
>
> 综上所述，将 $\{b_i\}$ 还原至少需要 $n-\operatorname{cyc}(\mathbf G)$ 次操作。

那么原问题就转化为了最小化 $\operatorname{cyc}(\mathbf G)$ 的问题。

记 $cnt_x$ 为 $x$ 在 $\{a_i\}$ 中的出现次数。

注意到如下的观察：

> 观察二：
>
> 对于所有 $\mathbf G$ 和正整数 $x\in [1,n]$，$\operatorname{cyc}(\mathbf G)\ge cnt_{x}$。
>
> 事实上 $cnt_x$ 等于 $\mathbf G$ 中 $x$ 的入度和出度，那么原命题可以等价于证明：
>
> 对于每个 $\mathbf G$ 的最大环拆分，不存在一个环经过某个 $x$ 两次。
>
> 而根据最大环拆分的定义，经过 $x$ 两次的环会在最大环拆分中拆成两个环，因此原命题得证。

我们假设 $\{a_i\}$ 中的众数 $m$ 出现了 $c$ 次，根据观察二，那么答案 $\ge n-c$。

猜测答案 $=n-c$，即我们需要构造一个 $\mathbf G$ 使得 $\operatorname{cyc}(\mathbf G)=c$。

考虑什么时候 $\operatorname{cyc}(\mathbf G)=c$，注意到如下的观察：

> 观察三：
>
> $\operatorname{cyc}(\mathbf G)=c \iff \operatorname{cycle}(\mathbf G-\mathbf G_m)=0$ 其中 $\operatorname{cycle}$ 定义为图中的环的数量，$\operatorname{cycle}(\mathbf G-\mathbf G_m=0)$ 即在 $\mathbf G$ 中删除 $m$ 和所有与 $m$ 相邻的边得到的新图 $\mathbf G-\mathbf G_m$ 中不存在环。
>
> 证明如下：
>
> 1. 证 $\operatorname{cyc}(\mathbf G)=c \implies \operatorname{cycle}(\mathbf G-\mathbf G_m)=0$：
>
> 考虑逆否命题 $\operatorname{cycle}(\mathbf G-\mathbf G_m)>0\implies \operatorname{cyc}(\mathbf G)>c $。
>
> 那么考虑 $\operatorname{cycle}(\mathbf G-\mathbf G_m)$ 中的一个环 $\mathbf C$：在子图 $\mathbf G-\mathbf C$ 中，最大的度（等价于众数的出现个数）依然是 $c$，根据观察二，得到 $\operatorname{cyc}(\mathbf G-\mathbf C)\ge c$。
>
> 所以 $\operatorname{cyc}(\mathbf G)=\operatorname{cyc}(\mathbf G-\mathbf C)+1\ge c+1>c$。
>
> 2. 证 $\operatorname{cycle}(\mathbf G-\mathbf G_m)=0\implies \operatorname{cyc}(\mathbf G)=c$。
>
> 考虑逆否命题 $\operatorname{cyc}(\mathbf G)>c \implies \operatorname{cycle}(\mathbf G-\mathbf G_m)>0$。
>
> 由于抽屉原理，在 $\operatorname{cyc}(\mathbf G)$ 个环中必然至少有一个不经过 $m$，那么这个环的存在会使得 $\operatorname{cycle}(\mathbf G-\mathbf G_m)>0$。

显然，构造出一个 $\mathbf G$ 使得 $\mathbf G$ 存在一个大小为 $c$ 的环剖分是简单的：考虑第 $i$ 个环中包含所有 $cnt_x\ge i$ 的 $x$，这样每个 $x$ 会出现在 $cnt_x$ 个环中。

那么接下来就是确定每个环的方向使得 $\mathbf G-\mathbf G_m$ 是一个 DAG。

有这样的一个想法，在值域 $[1,n]$ 上构造一个偏序关系 $\succeq$ 满足：

- 对于任意 $i,j\in [1,n]$，$(i,j)$ 在 $\succeq$ 的定义域中。
- 对于所有 $k\in [1,n],k\ne m$，$m\succ k$ 成立，即 $m=\max_\succeq\{1,2,3,\cdots,n\}$。

那么对于每个环，我们将每个点按 $\succeq$ 的顺序排序，然后从大到小连边，最小的一定会连到 $m$ 处。

此时如果删去 $m$，剩下的所有边的方向与 $\succeq$ 的方向相同，那么这样的图一定是 DAG。

此处取偏序关系 $\succeq$ 等价于按 $cnt_x$ 为第一关键字，$x$ 为第二关键字从大到小排序，$m$ 为最大的众数。

时间复杂度 $\Theta(n\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
int a[MAXN],cnt[MAXN];
vector <int> buc[MAXN];
inline bool cmp(const int &id1,const int &id2)  {
	if(cnt[a[id1]]==cnt[a[id2]]) return a[id1]>a[id2];
	return cnt[a[id1]]>cnt[a[id2]];
}
inline void solve() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) buc[i].clear(),cnt[i]=0;
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		++cnt[a[i]];
		buc[cnt[a[i]]].push_back(i);
	}
	for(int i=1;i<=n;++i) {
		sort(buc[i].begin(),buc[i].end(),cmp);
		for(int j=1;j<(int)buc[i].size();++j) swap(a[buc[i][j-1]],a[buc[i][j]]);
	} 
	for(int i=1;i<=n;++i) printf("%d ",a[i]);
	puts("");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：Legitimity (赞：2)

[或许更好的阅读体验](https://www.cnblogs.com/tiatto/p/16188280.html)

### Description

给定一个序列 $a$，定义一次操作为交换序列中的两个位置上的元素，求 $a$ 的一个排列 $b$，满足将 $b$ 还原成 $a$ 所需最少操作数最多。

$1\leq n\leq 2\times 10^5$，$a_i\leq n$。


------------
### Solution

官方题解不太能懂欸……


------------


定义 $swap(x,y)$ 为交换 $x$ 和 $y$ 两个数。

首先根据我们小学二年级学的置换的知识，无论怎么交换 $b$ 的元素最后都等价于对 $b$ 的一次置换，我们设其为 $p$。

置换是由若干个轮换复合成的，对于一个大小为 $m$ 的轮换，不难得出想要实现它则需要 $m-1$ 次操作。那么我们对 $p$ 进行分解，设分出了 $k$ 个轮换，那么实现这个置换则需要 $n-k$ 次操作。

假设 $a$ 是 $[1,n]$ 的一个排列，那么问题就转化为求一个置换 $p^{-1}$，使得 $p^{-1}$ 的分解尽量小，于是直接将一个轮换作为 $p^{-1}$ 即可。（$b$ 通过置换 $p$ 得到 $a$，则 $a$ 通过置换 $p^{-1}$ 得到 $b$；逆置换和原置换结构是一样的，分解也一样。）


------------


如果 $a$ 可重，那么就不行了，因为通过 $p^{-1}$ 置换出的 $b$ 想还原成 $a$ 所用的置换就不一定为 $p$ 了。

假设出现次数最多的数 $x$ 出现了 $k$ 次，那么我们可以得到答案的上界即为 $n-k$，因为无论 $b$ 长什么样，我们都可以强制将除了 $x$ 以外的数用 $n-k$ 次操作归位，剩下的 $k$ 个 $x$ 也就回到了自己的位置。

于是我们可以就猜测这个上界是紧的，想办法去构造达到这个上界。


------------


随即就有了一个很 naive 的想法：那么我们对于每个 $1\leq i\leq k$，处理一批位置 $\{j|j\text{ 为 }a_j \text{ 第 }i \text{ 次出现的位置}\}$。这样就满足了对于每个 $i$ 的位置集合所对应的 $a$ 的值互不相同，那么我们对于每个 $i$ 的位置集合随便搞个轮换，整个 $p^{-1}$ 就由 $k$ 个轮换复合成，答案似乎就能取到 $n-k$。

~~然后 `WA on pretest 2` 了。~~

hack：
```latex
1
7
1 2 4 3 1 3 2
```
假设我们随便取轮换，取到了：
```latex
3 1 2 4 | 2 1 3
```
我们发现这样只要 $4$ 次操作就能还原，小于 $n-k=5$。

------------
**Lemma1：** 

$p^{-1}$ 分解为 $k$ 个轮换，并且不存在一对位置 $(i,j)$ 满足 $i$ 和 $j$ 所在轮换的大小大于 $2$ 且 $a_i=b_j,a_j=b_i$ （即等价于在两个轮换中如果令 $p_{g1}=i$，$p_{g2}=j$，那么有 $a_{g1}=a_j$，$a_{g2}=a_i$），是答案取到上界的充要条件。

**proof：** 

充分性显然，必要性证一下。

说人话就是将这两个位置交换 就正好还原了这两个位置，那么我们考虑这两个位置交换后的影响，设 $i$ 所在的轮换为 $t_i$，$j$ 所在的轮换为 $t_j$，当前未还原位置个数为 $n$，对应的轮换有 $k$ 个，则剩余还需要 $ans=n-k$ 次操作。

删掉 $i$ 和 $j$ 两个位置，$n'=n-2$，然后考虑 $k$ 的变化，假设能将残缺的 $t'_i$ 或 $t'_j$ （为方便我们假设为 $t'_i$）和另一个轮换 $t_k$ 合并，那么一定满足 $t'_i$ 和 $t_k$ 有重复元素。若 $t_i$ 变为 $t'_i$ 删掉的数不是 $x$，由我们构造轮换的方法可知 $t'_i$ 和 $t_k$ 都含有 $x$，矛盾；假设删掉了 $x$，由我们构造轮换的方法可知任意两个 $t$ 一定存在包含关系，若 $t_i\subset t_k$ 显然不满足，$t_k\subset t_i$ 的话，想要满足 $t_k$ 一定只要一个数 $x$，与假设矛盾。那么可得删完后 $k'=k$ ，新答案为 $ans'=n'-k'=ans-2$，用一次操作减小了 $2$ 的代价，则答案一定取不到上界。



------------
我们就只要在上面的构造的基础上满足这个限制一个，似乎想去用数据结构维护，但发现也找不到合适的，于是继续贪。

假设我们当前要处理的位置集合 $s_i$，我们将 $j\in s_i$ 按 $a_j$ 出现次数大小降序排序，那么 $s_i$ 一定是 $s_{i-1}$ 的一个前缀（可能相等）。

那么我们直接按 $s$ 的顺序构造整体左移一个位置的轮换即可。因为对于当前不是 $s_i$ 的最后一个数的 $j$，$p_g=j$ 的 $g$ 是固定的，不会出现上面的情况；若 $j$ 是最后一个，那么 $p_g=j$ 的 $g$ 变成了 $s_i$ 的第一个元素，除非 $s_i$ 的大小为 $2$，也不会出现上面那种情况，但大小为 $2$ 的轮换对上面的 lemma 没有影响。

于是构造完了。



------------
### Code

代码是真的好写，证明也是真的难证。

```cpp
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x&(-x))
#define djq 998244353
const double eps=1e-8;
const int inf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;
const double alpha=0.73;
inline void file(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
}
char buf[1<<21],*p1=buf,*p2=buf;
inline int getc(){
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,(1<<20)+5,stdin),p1==p2)?EOF:*p1++;
}
//#define getc getchar
inline int read(){
	rg int ret=0,f=0;char ch=getc();
    while(!isdigit(ch)){if(ch==EOF)exit(0);if(ch=='-')f=1;ch=getc();}
    while(isdigit(ch)){ret=ret*10+ch-48;ch=getc();}
    return f?-ret:ret;
}
#define epb emplace_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define it iterator
#define mkp make_pair
typedef vector<int> vec;
typedef pair<int,int> pii;
struct point{ int x,y; point(int x=0,int y=0):x(x),y(y) {} inline bool operator<(const point& T)const{ return x^T.x?x<T.x:y<T.y; }; };
inline int ksm(int base,int p){int ret=1;while(p){if(p&1)ret=1ll*ret*base%djq;base=1ll*base*base%djq,p>>=1;}return ret;}
int n,a[200005],b[200005];
int cnt[200005],mx;
vec x[200005];
signed mian(){
	n=read(); mx=0; 
	for(rg int i=1;i<=n;++i) a[i]=read(),cnt[i]=0,x[i].clear();
	for(rg int i=1;i<=n;++i) ++cnt[a[i]],mx=max(mx,cnt[a[i]]),x[cnt[a[i]]].epb(i);
	for(rg int i=1;i<=mx;++i){
		const int m=x[i].size();
		sort(all(x[i]),[&](const int& x,const int& y){return (cnt[a[x]]^cnt[a[y]])?cnt[a[x]]>cnt[a[y]]:a[x]<a[y]; });
		for(rg int j=0;j<m;++j) b[x[i][j]]=a[x[i][(j+1)%m]];
	}
	for(rg int i=1;i<=n;++i) printf("%d ",b[i]);
	return puts(""),0;
}
signed main(){
	int _=read();
	while(_--) mian();
	return 0;
}
/*
*/ 
```


---

## 作者：YxYe (赞：1)

写篇题解标记构造妙题。

## [Array Shuffling](https://www.luogu.com.cn/problem/CF1672F1)

给出一个长度为 $n$ 的数组 $a$，求数组 $b$ 使得 $b$ 中通过若干次交换任意两个元素得到 $a$ 所需的交换最少次数的值最大。

## Pre

考虑给定的数组 $b$ 如何得到原数组 $a$。

假设给定了 $b$ 数组对应原来在 $a$ 数组的位置：令 $b_i$ 原来在 $a_j$ 处。

那么我们可以建图，将 $i$ 向 $j$ 连一条有向边。

可以发现这张图有以下的性质：

1. 该图一定由若干个环组成。

2. 若要交换次数最小，不可能让相同的数连边。

3. 可以通过交换两个相同环的数将一个环拆分。

4. 可以通过交换两个不同环的数将两个环合并。

因为有性质 3，所以我们可以拆分一个环直到为自环。

显然可以计算一个环 $C$，其最小交换次数为其点数减一。

又因为有性质 4，所以我们不会合并两个环（显然更劣）。

那么对于一个图，其最小交换次数为其点数减其环的个数。

## Sol

由引入部分可知，我们要构造一张满足性质 1、2 且环个数最少的图。

以下为本人的一种构造方法：

将 $a$ 中元素按照是否相同分组。进行建边操作直到用完所有元素：每次建边从每一组中选出一个，然后将他们按照大小顺序依次连成一个环。

## Code

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(int i=(a);i<=(b);i++)
#define pii pair<int, int>
#define fir first
#define sec second
using namespace std;
inline int rd(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
const int maxn=2e5+10;
int T,n,m,a[maxn],p[maxn];
pii b[maxn],tmp[maxn];
int main(){
	T=rd();
	while(T--){
		n=rd();
		fo(i,1,n)a[i]=rd(),b[i]=pii(a[i],i);
		sort(b+1,b+n+1);
		int sta[n+10],tp=0;
		fo(i,1,n){
			if(i==1||b[i].fir!=b[i-1].fir){//分组
				sta[++tp]=i;
			}
		}
		int stb[n+10];
		while(tp){//建边
			int tq=0;
			fo(i,1,tp){
				if(i==1)p[b[sta[i]].sec]=b[sta[tp]].fir;
				else p[b[sta[i]].sec]=b[sta[i-1]].fir;
				if(sta[i]!=n&&b[sta[i]].fir==b[sta[i]+1].fir){//找该组下一个元素
					stb[++tq]=sta[i]+1;
				}
			}
			fo(i,1,tq)sta[i]=stb[i];
			tp=tq;
		}
		fo(i,1,n){
			printf("%d ",p[i]);
		}
		puts("");
	}
	return 0;
}
```

## More

[升级版](https://www.luogu.com.cn/blog/YxYe/solution-cf1672f2)

---

