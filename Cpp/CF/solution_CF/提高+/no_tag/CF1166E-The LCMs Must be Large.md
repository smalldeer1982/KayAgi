# The LCMs Must be Large

## 题目描述

题意

有一个长度为$n$（$n<=10^4$）的**内容未知**的序列，再给$m$（$m<=50$）个限制，每个限制会给一个位置集合$S$，需要让$S$中所有位置上的数的$lcm$严格大于序列里剩下的数的$lcm$，求是否存在一个这样的序列满足所有限制。

## 样例 #1

### 输入

```
2 5
3 1 2 3
3 3 4 5
```

### 输出

```
possible
```

## 样例 #2

### 输入

```
10 10
1 1
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
```

### 输出

```
impossible
```

# 题解

## 作者：ywy_c_asm (赞：8)

这题的结论：如果有两个集合交集为空，那么impossible，否则possible。

首先有两个交集为空这个无解的情况是比较显然的，我们以$n=5$的情况为例，序列是$a,b,c,d,e$，比如我们两个集合是$\{a,b\}$和$\{c,d\}$，那么两个限制就是$lcm(a,b)>lcm(c,d,e)$，$lcm(c,d)>lcm(a,b,e)$，显然$lem(c,d,e)>=lcm(c,d)$，$lcm(a,b,e)>=lcm(a,b)$，就出现了矛盾，所以无解。

那么为什么集合两两之间都有交集就一定有解呢？这个我们可以考虑构造，我们对于第$i$个集合把它里面的所有数都乘上一个质数$p_i$，这里我们假设$p_1,p_2\cdots p_m$都是互不相同的质数，考虑第$i$个集合的$lcm$，由于它与剩下的所有集合都有交，所以$lcm$为$\prod_{i=1}^mp_i$，而它的补集的$lcm$显然不会超过这个，并且补集里的数肯定不含$p_i$，所以补集的$lcm<\prod_{i=1}^mp_i$，就可以这样构造出来了。

那么我们只需要bitset判交即可。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll unsigned long long
using namespace std;
namespace ywy {
	int size = 160;
	typedef struct _bitset {
	    ll data[161];
	    _bitset() { memset(data, 0, sizeof(data)); }
	    friend _bitset operator&(const _bitset &a, const _bitset &b) {
	        _bitset c = a;
	        for (register int i = 0; i <= size; i++) c.data[i] &= b.data[i];
	        return (c);
	    }
	    inline int empty() {
	        for (register int i = 0; i <= size; i++)
	            if (data[i])
	                return (0);
	        return (1);
	    }
	    inline void set(int x) { data[x >> 6] |= (1ll << (x & 63)); }
	} bitset;
	bitset dat[111];
	void ywymain() {
	    int m, n;
	    cin >> m >> n;
	    for (register int i = 1; i <= m; i++) {
	        int k;
	        cin >> k;
	        while (k) {
	            k--;
	            int x;
	            cin >> x;
	            dat[i].set(x);
	        }
	        for (register int j = 1; j < i; j++) {
	            if ((dat[i] & dat[j]).empty()) {
	                printf("impossible\n");
	                return;
	            }
	        }
	    }
	    printf("possible\n");
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：mraymes (赞：8)

本文章将同步到 [Hexo 博客](https://mraymes.github.io).

注意: 本题解是基于**原始题意**的, 和**当前**翻译也许有不符. 有能力的先阅读原始题意, 若带来不便请谅解.

这题目第一反应:  
这是个什么鬼哟  
算了算了做 D 题

但最后发现这题目的代码非常短, 因为这题有个神奇的结论. 就是只要输入的区间两两有交集, 那么答案就是 "possible", 否则就是 "impossible" 了. 在下面给出证明.

## 如何证明无交集答案就是不可能

设 Dora 在第 $i$ 选择的商店编号为 $b_{i, 1}, b_{i, 2}, b_{i, 3}, \cdots, b_{i, s_i}$.

定义一个**多重**集合 $S = \{ a_1, a_2, a_3, a_4, \cdots, a_n \}$, 即那个内容未知的 $a$ 数组. 对于每两天第 $i$ 天和第 $j$ 天, 定义两个多重集合 $A = \{ a_{b_{i, k}} : 1 \leqslant k \leqslant s_i \}$, $B = \{ a_{b_{j, k}} : 1 \leqslant k \leqslant s_j \}$, 即 Dora 在第 $i$ 天与第 $j$ 天购买的数字.  
这里再定义 $A$ 与 $B$ 相对于 $S$ 的补集, $C = S \setminus A$, $D = S \setminus B$.

当 $A \cap B = \emptyset$ 时, 可以看出 $B \subseteq C$, $A \subseteq D$.

$\operatorname{lcm} S$ 为 $S$ 内所有数字的 LCM 值.

接下来, 我们就需要证明这一点:  
- 当 $A \subseteq B$ 时, $\operatorname{lcm} A \leqslant \operatorname{lcm} B$ (注: 此处 $A$ 与 $B$ 和上述定义的集合无关).

----------------

### 证明

注: 这里所有的数, 集合等与上述定义的均无关.

已知集合 $A$, $B$, 并且 $A \subseteq B$, $x = \operatorname{lcm} A$.  
另有一个实数 $y$, 满足 $y \in B$, $y \notin A$.

设 $A' = A \cup \{ y \}$, $x' = \operatorname{lcm} A'$.

如果 $y \mid x$, 即 $x \bmod y = 0$, 则 $\operatorname{lcm} A' = \operatorname{lcm} A$ .

如果 $y \nmid x$, 即 $x \bmod y \neq 0$, 那么 $x' = x \cdot \dfrac{y}{\gcd(x, y)}$. $\gcd(x, y)$ 是整除 $y$ 又整除 $x$ 的最大数, 所以 $\dfrac{y}{\gcd(x, y)}$ 是整除 $y$ 且不整除 $x$ 的最小数. 因此 $x$ 与这个数相乘得到 $x'$.

又因为 $gcd(x, y) \mid y$, 因此 $gcd(x, y) \leqslant y$, $\dfrac{y}{\gcd(x, y)} \geqslant 1$, $x' \geqslant x$.

当所有满足条件的 $y$ 都一个个加进 $A$ 时, $\operatorname{lcm} A$ 只会变大或不变. 因此 $\operatorname{lcm} A \leqslant \operatorname{lcm} B$. 证明完毕.

----------------

假设 $\operatorname{lcm} A > \operatorname{lcm} C$.

$\because B \subseteq C$  
$\therefore \operatorname{lcm} B \leqslant \operatorname{lcm} C$  
$\therefore \operatorname{lcm} A > \operatorname{lcm} C \geqslant \operatorname{lcm} B$  
$\because A \subseteq D$  
$\therefore \operatorname{lcm} A \leqslant \operatorname{lcm} D$  
$\because \operatorname{lcm} A > \operatorname{lcm} B$  
$\therefore \operatorname{lcm} B < \operatorname{lcm} A \leqslant \operatorname{lcm} D$

如果 Dora 在第 $i$ 天选择了集合 $A$, Swiper 选择了集合 $C$ 并且 $\operatorname{lcm} A > \operatorname{lcm} C$, 那么在她第 $j$ 天选集合 $B$, Swiper 选集合 $D$ 时 $\operatorname{lcm} B < \operatorname{lcm} D$. 因此每次 Dora 选的集合中所有数字的 LCM 值都大于 Swiper 的是不可能的. 输出 `impossible`.

## 如何证明每两个集合都有交集就有可能

设 Dora 每天购买的数字的集合分别为 $S_1, S_2, S_3, \cdots, S_m$.

因为对于每两个集合 $S_i, S_j$ 来说, 只要保证 $S_i \cap S_j \neq \emptyset$, 便能保证 $(S \setminus S_i) \cap (S \setminus S_j) = \emptyset$, 因为 $S_i \cap S_j$ 中的数是两个补集均不能包含的.  
这样便能保证 Swiper 每天取的数的集合中必定两两交集为空集.

假设 Swiper 取的每个集合的 $\operatorname{lcm}$ 值为 $c_1, c_2, c_3, \cdots, c_m$.

- $m \leqslant 2$ 不满足 Dora 取的数的集合中两两交集不为空集的大前提.
- $m = 3$ 时可以使 $c = \{2, 3, 5\}$.
- $m \geqslant 4$ 时使 $c = \{1, 2, 3, \cdots, m\}$, 必定可行.
  - 易证对于所有满足 $1 \leqslant i < m$ 的 $i$ 来说, 除 $i$ 外所有数的 $\operatorname{lcm}$ 大于 $i$.
  - 当 $m$ 等于 $4$ 时, $\operatorname{lcm} \{1, 2, 3\} > 4$.
  - 当 $m$ 为大于 $4$ 的合数时, 必定有两个更小的数乘积为 $m$ ($m$ 最小的质因数以及 $m$ 与之相除所得的数). 剩余的数中, 其中的质数必定能使它们的 $\operatorname{lcm}$ 大于 $m$.
  - 当 $m$ 为质数时, 能保证 $m + 1$ 为合数. 因为 $m \nmid m + 1$, 所以 $m + 1$ 的两个因数必定在其他数 ($1$ 到 $m - 1$ 之间的正整数) 之中. 因此可得出 $1$ 到 $m - 1$ 的正整数的 $\operatorname{lcm}$ 值大于等于 $m + 1$, 大于 $m$.


最后上代码 (惊人地短).

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m; // 这里与题意中的 n, m 定义相反
int a[10001];
int c[10001];
bitset<100001> st[60]; // 用 bitset 来存集合

template <typename T>
inline T read() {
    T x = 0;
    T multiplier = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            multiplier = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch & 15);
        ch = getchar();
    }
    return x * multiplier;
}

int main() {
    n = read<int>(), m = read<int>();

    for (int i = 1; i <= n; i++) {
        int len = read<int>();

        for (int j = 1; j <= len; j++) {
            int x = read<int>();
            st[i][x] = 1;
        }

        for (int j = 1; j < i; j++) {
            if (!(st[i] & st[j]).count()) { // 判断是否有交集
                puts("impossible");
                exit(0);
            }
        }
    }

    puts("possible");

    return 0;
}
```

注意: 代码中虽然存的不是具体的数字, 而是编号, 但是也有同样的意思.

Update on 17th Jun, 2019:  
感谢 @ZUTTER_ @wucstdio 指出的错误, 已修改.


---

## 作者：rizynvu (赞：2)

[我的博客](https://www.cnblogs.com/rizynvu/p/18523767)。

2024.11.22：修改了一处笔误。

看着合法不是很好判断，不如先去想一些不合法的情况。

可以通过手玩之类知道，若存在 $i\not = j, S_i \cap S_j = \varnothing$，那么必然无解。  
证明考虑令 $x = \operatorname{lcm}_{k\in S_i}(a_k), y = \operatorname{lcm}_{k\in S_j}(a_k), z = \operatorname{lcm}_{k\not\in S_i, k\not\in S_j} (a_k)$，那么就是要满足 $x > \operatorname{lcm}(y, z), y > \operatorname{lcm}(x, z)$，但是注意到 $\operatorname{lcm}(x, z) \ge x, \operatorname{lcm}(y, z) \ge y$，所以无解。

那么剩下就是两两都有交的情况了，感受一下会感觉大抵是有解的，然后如果直接猜这个结论就过了（。  
但是还是需要个证明的，考虑到满足的相当于是 $\operatorname{lcm}_{j\in S_i}(a_j) > \operatorname{lcm}_{j\not \in S_i}(a_j)$，那么一个想法是给 $S_i$ 中的值赋一个与 $i$ 有关的值。  
并且考虑到 $\operatorname{lcm}$ 中 $\gcd$ 的存在太特殊，不妨直接特化，钦定每一个跟 $i$ 有关的值都是个质数（例如第 $i$ 个质数 $\operatorname{pr}_i$），且直接特化 $>$ 为成倍数关系。

考虑构造，那么根据之前的想法，可以初始值都赋为 $1$。  
然后对于 $j\in S_i$，令 $a_j\leftarrow a_j\times \operatorname{pr}_i$。  

考虑这为什么是对的，首先是因为 $\operatorname{lcm}_{j\in S_i}(a_j)$ 中一定含 $\operatorname{pr}_i$，而 $\operatorname{lcm}_{j\not \in S_i}(a_j)$ 不含。  
同时对于 $S_k(k\not = i)$，因为 $S_i\cap S_k\not = \varnothing$，所以若 $S_k\subseteq S_i$，那么 $\operatorname{pr}_k$ 只贡献给了 $\operatorname{lcm}_{j\in S_i}(a_j)$，否则两部分都贡献了，一定满足条件。

时间复杂度 $\mathcal{O}(\frac{nm^2}{\omega})$。

```cpp
#include<bits/stdc++.h>
const int maxn = 1e4 + 10, maxm = 50 + 2;
std::bitset<maxn> b[maxm];
int main() {
   int n, m;
   scanf("%d%d", &m, &n);
   for (int i = 1, k; i <= m; i++) {
      scanf("%d", &k);
      for (int x; k--; ) {
         scanf("%d", &x), b[i].set(x);
      }
   }
   for (int i = 1; i <= m; i++) {
      for (int j = i + 1; j <= m; j++) {
         if ((b[i] & b[j]).none()) {
            return puts("impossible"), 0;
         }
      }
   }
   return puts("possible"), 0;
}
```

---

## 作者：ConstantModerato (赞：0)

* 证明 $1$：若选择的集合 $s_i,s_j$ 没有交集，则一定无解。

> 由题意不难知道 $\operatorname{lcm}x < \operatorname{lcm} s_j,x \notin s_j$。

> 相当于是往 $s_i$ 中加入了不属于 $s_j$，也不属于 $s_i$ 的新元素。

> 显然往 $\operatorname{lcm} s_i$ 中加入新的数求最小公倍数是单调不减的。

> 即 $\operatorname{lcm}(x_1,x_2,\cdots,x_k) \le \operatorname{lcm}(x_1,x_2,\cdots,x_k,y_1,y_2,\cdots ,y_{k'})$。

> 所以由上不难推出 $\operatorname{lcm} s_i <\operatorname{lcm} s_j$。

> 将上述证明的 $i$，$j$ 调换，同时可以证明出 $\operatorname{lcm} s_i >\operatorname{lcm} s_j$。矛盾。

> 固，若选择的集合 $s_i,s_j$ 没有交集，则一定无解。

* 证明 $2$：若选择的集合 $s_i,s_j$ 两两有交集，则一定有解。

> 思考一个比较直接的构造方法。

> 初始化原序列全部为 $1$。

> 对于每一个集合 $s_i$，其中每一个元素乘上一个相同的质数 $p_i$，并且满足 $p_i \neq p_j$。

> 设 $P = \prod_{i = 1}^m p_i$，则对于每一个集合 $s_i$，$\operatorname{lcm} s_i = P$。

> 因为 $s_i$ 与任意 $s_j \space(1 \le j \le m)$ 有交集，则说明 $p_j$ 一定有对 $\operatorname{lcm} s_i$ 贡献。

> 而对于 $s_i$ 的补集，并没有 $p_i$ 的贡献。考虑存在 $s_j$ 包含于 $s_i$ 时，$s_j$ 也没有对它有贡献，所以是小于等于。

> 所以 $\operatorname{lcm}x \le \frac{P}{p_i} < \operatorname{lcm} s_i = P,x \notin s_i$。

> 综上，构造必然成立。

---

## 作者：Star_Cried (赞：0)

## CF1166E The LCMs Must be Large

思维好题，结论好题。

### 题意

一个长度为 $n$ 的未知长度的序列，有 $m$ 个限制，每个限制形如给定一个集合 $S$ ，使集合内元素的 $lcm$ 严格大于其补集元素的 $lcm$ 。问是否存在这一序列。

### 思路

要注意我们是要尽可能使序列有解。

先给出结论：若所有集合两两间有交，则有解。否则一定无解。

首先有一个结论：若 $A\subseteq B$，那么 $lcmB \geq lcmA$ 。

因为考虑 $B$ 比 $A$ 多的元素，只可能增加贡献而不可能减少贡献，所以上述结论显然。

然后我们回到题目：若一个限制的集合 $A$ 与另一个限制的集合 $B$ 不交，假设 $lcmA>lcmA\setminus S$ ($S$表示整个序列集合)，那么一定有 $B\subseteq A\setminus S$,即有 $lcmA\setminus S\geq lcm B$ 。显然不符合要求。

然后证明结论的充分性。这里我们考虑一个构造的方法：假设所有元素初始都为1，我们将每个给定的集合内的元素都乘上一个互不相同的质数，那么如果集合两两相交，每个集合的$lcm$就是整个序列的$lcm$，并且每个集合的补集因为没有乘该集合的质数所以$lcm$一定小。如果有两个集合不相交，因为两个集合的质数不同，所以一定会出现一个集合的$lcm$大于另一个集合的情况，一定无解。

### 实现

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<cmath>
#include<bitset>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=x*10+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=1e4+10;
	int m;
	bitset<maxn> a[55],now;
	inline void work(){
		m=read();read();
	    for (int x,i=1;i<=m;i++) {
	        x=read();
	        while(x--)
	        	a[i].set(read());
	        for (int j=1;j<i;j++) {
	            if ((a[i] & a[j]).none())
					return (void)puts("impossible");
	        }
	    }
	    puts("possible");
	}
}
signed main(){
	star::work();
	return 0;
}
```



---

## 作者：Suzt_ilymtics (赞：0)

找一下这题的切入点，先考虑一下集合之间不同关系下可能需要怎样构造。

发现如果两个集合 $A,B$ 没有重合的位置，那么一定无解。

因为不可能出现我比你大，同时你比我大的情况。

那么合法的情况一定是所有的集合的交不为空。

其实构造方案也非常简单，这个交的位置设为 $2$，其他为 $1$ 就好了。~~不过题目没要求这个，所以就不管啦~~。

实现的时候直接暴力去比较一下就好。~~只要你不头铁~~ $\mathcal O(n^2m^2)$ ~~的复杂度都是能过的。~~

---

