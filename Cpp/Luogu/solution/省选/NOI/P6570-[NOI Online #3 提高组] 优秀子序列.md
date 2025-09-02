# [NOI Online #3 提高组] 优秀子序列

## 题目描述

给定一个长度为 $n$ 的非负整数序列 $A=\{a_1,a_2,\cdots,a_n\}$，对于 $A$ 的一个子序列 $B=\{a_{b_1},a_{b_2},\cdots,a_{b_m}\}$（$0\le m\le n$，$1\le b_1<b_2<\cdots<b_m\le n$，下同），称 $B$ 是 $A$ 的优秀子序列当且仅当，其任意两个不同元素的按位与结果均为 $0$，即：$\forall 1\le i<j\le m$，满足：$a_{b_i}~\mathrm{and}~a_{b_j}=0$，其中 $~\mathrm{and}~$   是按位与运算。

对于子序列 $B=\{a_{b_1},a_{b_2},\cdots,a_{b_m}\}$，我们定义其价值为 $\varphi(1+\sum_{i=1}^m a_{b_i})$，其中 $\varphi(x)$ 表示小等于 $x$ 的正整数中与 $x$ 互质的数的个数。

现在请你求出 $A$ 的所有优秀子序列的价值之和，答案对 $10^9+7$ 取模。

## 说明/提示

#### 样例 1 解释
符合条件的子序列有：$\emptyset$，$\{1\}$，$\{2\}$，$\{2\}$，$\{3\}$，$\{1,2\}$，$\{1,2\}$，它们价值依次为 $1$，$1$，$2$，$2$，$2$，$2$，$2$，总和为 $12$。

#### 数据规模与约定
- 对于 $10\%$ 的数据，保证 $a_i\le 1$。
- 对于 $30\%$ 的数据，保证 $a_i\le 1000$。
- 对于 $60\%$ 的数据，保证 $a_i\le 30000$。
- 另有 $10\%$ 的数据，保证 $n\le 20$。
- 对于 $100\%$ 的数据，保证 $1\le n\le 10^6$，$0\le a_i\le 2\times 10^5$。

## 样例 #1

### 输入

```
4
1 2 2 3```

### 输出

```
12```

# 题解

## 作者：泥土笨笨 (赞：36)

写一个复杂度$O(3^{18})$的题解吧，思路简单一些，虽然复杂度高，但是能过。部分参考了我校大神@dengyaotriangle 的题解，感谢。

首先，我们把每一个数字看成是一个集合。每个数字可以写成二进制，那么看这个二进制形式中，从右往左的每个位置上的数字。如果第i位上是1，表示这个集合中有$2^i$，否则表示这个集合中没有$2^i$。这里i从0开始。下文中，我们用小写字母表示数字，对应的大写字母表示集合。

举个例子，数字5对应成二进制是$(101)_2$，那么把5看成是集合$\{ 2^0,2^2 \}$。数字9对应二进制是$(1001)_2$，表示$\{ 2^0,2^3 \}$。

现在要求我们找到一个子序列，子序列中任意两个数字a和b，都满足a&b==0，其实我们把a和b看成是两个集合A和B以后，这个条件等价于，A和B的交集是空集。

假设原序列中有一个合法的子序列S，x代表其中包含的数字。现在题目中要求的是$\sum_{x \in S}x$。有意思的是，因为其中任何两个数字的与都是0，所以**它们加在一起不可能产生进位**。那么要求的和可以看成是集合的并，即我们要求转化为$\cup_{X \in S}X$。设一个合法序列S中所有数字的和为sum，那么根据题中的数据范围，我们知道$sum<=4*10^{5}$，大概是$2^{18}$左右。

设dp[i]表示合法序列中所有元素的和为i的方案数，设phi[i]数组表示i的欧拉函数的结果。其中phi数组可以线性求出，如果不会，可以参考模板题[SP4141 ETF - Euler Totient Function](https://www.luogu.com.cn/problem/SP4141)

那么最终答案就是
$$\sum dp[x]phi[x+1]$$

所以问题的关键变成，如何求dp数组？0比较特殊，暂时认为数列里面没有0，后面咱们再单独处理。

假设目前正在求dp[sum]，表示现在合法序列的数字和是sum的方案数。首先观察发现，这些合法数字，一定都是小于等于sum的。而且题目中问我们子序列的方案数，子序列本身是和顺序无关的。所以提示我们，**输入完成以后，可以把数组按照从小到大的顺序排序。**

再考虑，dp[sum]可能从哪些点转移过来？能转移过来的点，一定是sum对应的集合SUM的子集。那么我们枚举SUM的子集X，对应的数字是x。并设X在SUM中的补集是Y，并且设c[x]表示x这个数字在原来序列中出现的次数，那么有
$$dp[sum]=\sum_{X \in SUM} dp[y]c[x]$$

解释一下，X是SUM的子集，Y是补集，那么dp[y]表示的是这个补集的方案数。对于这里的每个方案，加上一个x，都可以得到一个和为sum的方案。而x有多少个，从中任选一个均可，所以乘上一个x的个数c[x]。相信读者现在能理解这个递推式了。因为这里需要按照从小到大的顺序递推，并且需要求每个数字出现的次数，所以提示我们，输入的时候，干脆把这些数字存在桶里面。这样从小到大扫一遍桶，就可以做递推了。

这里还有个问题是如何枚举SUM集合的子集。实现的代码模板是：
```cpp
for (int s = i;/*结束的条件先空着一会儿说*/; s = (s - 1) & i) {
    //s是i的子集
    int bu = i ^s;//bu是s在i中的补集
}
```
这段代码里面是在枚举i的子集s，还顺便求出了补集bu。什么原理呢？

不妨先举个例子，假设i最开始是5，二进制表示是101，第一次s等于i，找到了101这个子集，其实就是它自己。

然后s变成s-1，即为100，然后用它与上i本身，即为100&101，是100，这是第二个子集。

然后s变成s-1，即为11，然后用它与上i本身，即为11&101，是1，这是第三个子集。

我们看这个过程，确实找到了i的每一个子集，如何理解呢？首先s等于i不用解释了，然后我们想，下一个子集肯定要比现在的s小，所以先减掉1肯定是变小了。其实是把最右边一个1变成了0，然后把它后面的0都变成了1.然后子集里面的数字，必须是原来i里面是1的位置，才能是1，所以正好与上i，把刚刚变成1的那些0里面的多余的i去掉，这样就成功得到了下一个更小的子集。

补集bu比较好理解，用i异或一下s，表示把s里面每个1对应的位置，从i中去掉。这样正好是补集。

所以回到求dp[sum]的位置，现在依次枚举SUM的子集，然后转移是不是就可以了呢？其实还有点小问题，这样算其实算重复了。比如3可以拆成1和2，在s等于1的时候算了一次，这时候补集是2。在s等于2的时候算了一次，这时候补集是1。但是其实是一种情况。如何避免算重复呢？我们只要保证s比bu大就行了。这样每次都是s和前面的dp[bu]一起算，就不会重复。所以枚举子集的时候，遇到s<bu就break。

最后考虑一下0，其实原来序列里面如果有cnt个0，那么对于原来每一种方案，都可以从cnt个0里面任取若干个组成新方案，所以方案数要乘一个$2^{cnt}$，这个最后算完了以后统一处理即可。

最后分析一下这么做的时间复杂度。先给出一个结论，n个元素组成的集合的子集的子集的方案数是$O(3^n)$，这道题中因为数据范围限制，每个数最多也就是18位，i依次取18个数的某一个子集，然后又枚举i的子集s，所以恰好总复杂度就是18个数的子集的子集的个数，所以DP过程复杂度大概是$O(3^{18})$

再加上最后枚举一遍DP数组的复杂度，大概是$O(n+3^{18})$

那么如何证明这个结论呢？

> 这个证明不是很难 ————@dengyaotriangle

对于原集合S，它有子集S'，和它的子集S''，那么对于每一个(S',S'')，考虑S中每一个元素u，那么只有三种情况，（u不属于S',u不属于S''）；（u属于S'，u不属于S''）；（u属于S'，u属于S''），这样，每个元素u都有3种可能性，而元素间互相独立，所以一共是$3^n$种可能的(S',S'')，也就是集合的子集的子集的个数为$3^n$

另外提供一种使用二项式定理的证明方式。首先，二项式定理是：

$$(x+y)^n=\sum {n \choose k}x^ky^{n-k}$$

而n个元素中，有k个元素的集合的数量是${n \choose k}$，而k个元素的集合的子集的个数是$2^k$，所以子集的子集的总个数是$\sum {n \choose k}2^k$

它等于
$$ \sum {n \choose k}2^k1^{n-k} = (2+1)^n = 3^n$$

最后是喜闻乐见的代码时间了，注释比较少，有问题可以在评论区里面留言

```cpp
#include <iostream>
#include <cstdio>

using namespace std;
typedef long long ll;
const ll MAXN = 400005;
const ll MOD = 1000000007;
ll n, a[MAXN], dp[MAXN], phi[MAXN], m, ma;//ma是a中的最大值，m是最大值的位数
ll prime[MAXN], pc;

void eulerTable(int x) {
    phi[1] = 1;
    for (int i = 2; i <= x; ++i) {
        if (phi[i] == 0) {
            prime[pc++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; j < pc && prime[j] * i <= x; ++j) {
            if (i % prime[j] == 0) {
                phi[prime[j] * i] = prime[j] * phi[i];
                break;
            } else {
                phi[prime[j] * i] = (prime[j] - 1) * phi[i];
            }
        }
    }
}

int main() {
    scanf("%lld", &n);
    for (int i = 0; i < n; ++i) {
        ll t;
        scanf("%lld", &t);
        a[t]++;
        ma = max(ma, t);
    }
    while ((1 << m) <= ma) { m++; }
    eulerTable(1 << m);
    dp[0] = 1;
    for (int i = 1; i <= (1 << m); ++i) {
        for (int s = i;; s = (s - 1) & i) {
            //s是i的子集
            int bu = i ^s;//bu是s在i中的补集
            if (s < bu) break;
            dp[i] = (dp[i] + dp[bu] * a[s]) % MOD;
        }
    }
    ll ans = 1;//加上空集
    for (int i = 1; i <= (1 << m); ++i) {
        ans = (ans + dp[i] * phi[i + 1]) % MOD;
    }
    for (int i = 0; i < a[0]; ++i) {
        ans = ans * 2 % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
```


---

## 作者：AutumnKite (赞：30)

### 算法一

题意转化后即为选出若干个互不相交的集合，他们的并集的权值之和。那么我们只要考虑每一种集合对应的方案数。

下面我们令 $m$ 表示 $a_i$ 的最大位数。

考虑 DP，令 $f_S$ 表示当前子集为 $S$ 的方案数。

我们只要保证转移的时候加入的数的最高位大于 $S$ 的最高位即可。

时间复杂度 $O(3^m)$。这样已经可以通过本题。

### 算法二

我们考虑集合幂级数 $F_i(x)=x^{a_i}+1$，并且定义两个集合幂级数的乘法为子集卷积，也就是 $i,j$ 转移到 $k$ 的条件是 $i\operatorname{and}j=0,i\operatorname{or}j=k$。

我们要求的就是集合幂级数 $\prod\limits_{i=1}^{n} F_i(x)$ 的各项系数。

子集卷积有一个经典的套路就是把一维变成两维，也就是把 $x^S$ 映射到 $x^Sy^{|S|}$，然后在做卷积时只要对 $x$ 做 $\operatorname{or}$ 卷积，对 $y$ 做加法卷积即可。

我们把 $F_i(x,y)$ 表示成 $\sum\limits_{S}G_{i,S}(y)x^S$ 的形式，即外层是集合幂级数，内层是一个多项式。注意到 $\operatorname{or}$ 卷积有一个很好的性质是乘完以后项数不会变多，那么我们把 $F_i(x,y)$ 外层的集合幂级数用 FWT 转化成点值表示后，$F_i(x,y)$ 的 $x$ 这一维就独立了。也就是说，我们在做卷积时，只需要将对应位的内层的多项式做卷积即可。

这意味着我们需要对于每个 $S$ 求出 $\prod\limits_{i=1}^{n}G_{i,S}(y)\bmod y^{m+1}$ 的各项系数。

多项式的乘法很麻烦，我们尝试把乘法转化为加法，即求 $\exp \sum\limits_{i=1}^{n} \ln G_{i,S}(y) \bmod y^{m+1}$。

手动模拟 FWT 的过程可以发现 FWT 后
$$
G_{i,S}=
\begin{cases}
x^{|a_i|}+1 & a_i\in S \\
1 & \text{otherwise}
\end{cases}
$$

又有
$$
\ln(1+x^k)=-\sum_{i=1}^{\infty} \frac{(-x^k)^i}{i}
$$

直接用高维前缀和即可求出所有的 $\ln G_{i,S}$。

然后再对于每个 $S$ 求 $\exp$。

最后做 IFWT 求出实际的系数即可。

时间复杂度 $O(2^nn^2)$。

### 算法一代码

```cpp
const int N = 300005, P = 1000000007;

int n, mx, m;
int a[N], b[N], f[N];
int cnt, p[N], vis[N], phi[N];

void init(int n) {
	cnt = 0;
	phi[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) {
			p[++cnt] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= cnt && p[j] * i <= n; ++j) {
			vis[p[j] * i] = 1;
			if (i % p[j] == 0) {
				phi[p[j] * i] = phi[i] * p[j];
				break;
			} else {
				phi[p[j] * i] = phi[i] * (p[j] - 1);
			}
		}
	}
}

int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	read(n);
	for (int i = 0; i < n; ++i) {
		int x;
		read(x);
		++a[x];
		mx = std::max(mx, x);
	}
	m = 0;
	while ((1 << m) <= mx) {
		++m;
	}
	init(1 << m);
	f[0] = 1, b[0] = 0;
	for (int i = 1; i < (1 << m); ++i) {
		b[i] = b[i >> 1] << 1 | 1;
		if (a[i]) {
			int mask = b[i] ^ i;
			for (int S = mask; ; S = (S - 1) & mask) {
				f[S | i] = (f[S | i] + 1ll * f[S] * a[i]) % P;
				if (!S) {
					break;
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < (1 << m); ++i) {
		ans = (ans + 1ll * f[i] * phi[i + 1]) % P;
	}
	for (int i = 0; i < a[0]; ++i) {
		ans = 2 * ans % P;
	}
	print(ans);
}
```

### 算法二代码

```cpp
const int N = 300005, P = 1000000007;

int n, mx, m;
int a[N], bitcnt[N];
int f[N][19], inv[19], g[N];
int cnt, p[N], vis[N], phi[N];

void inc(int &a, int b) {
	(a += b) >= P ? a -= P : 0;
}

void dec(int &a, int b) {
	a < b ? a += P - b : a -= b;
}

void init(int n) {
	cnt = 0;
	phi[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) {
			p[++cnt] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= cnt && p[j] * i <= n; ++j) {
			vis[p[j] * i] = 1;
			if (i % p[j] == 0) {
				phi[p[j] * i] = phi[i] * p[j];
				break;
			} else {
				phi[p[j] * i] = phi[i] * (p[j] - 1);
			}
		}
	}
}

int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	read(n);
	for (int i = 0; i < n; ++i) {
		int x;
		read(x);
		++a[x];
		mx = std::max(mx, x);
	}
	m = 0;
	while ((1 << m) <= mx) {
		++m;
	}
	inv[1] = 1;
	for (int i = 2; i <= m; ++i) {
		inv[i] = 1ll * inv[P % i] * (P - P / i) % P;
	}
	bitcnt[0] = 0;
	for (int S = 1; S < (1 << m); ++S) {
		bitcnt[S] = bitcnt[S >> 1] + (S & 1);
		int k = bitcnt[S];
		for (int i = 1; i <= m / k; ++i) {
			int t = 1ll * a[S] * inv[i] % P;
			if (i & 1) {
				inc(f[S][i * k], t);
			} else {
				dec(f[S][i * k], t);
			}
		}
	}
	for (int k = 0; k <= m; ++k) {
		for (int i = 0; i < m; ++i) {
			for (int S = 0; S < (1 << m); ++S) {
				if (S >> i & 1) {
					inc(f[S][k], f[S ^ (1 << i)][k]);
				}
			}
		}
	}
	for (int S = 0; S < (1 << m); ++S) {
		g[0] = 1;
		for (int i = 1; i <= m; ++i) {
			f[S][i] = 1ll * f[S][i] * i % P;
			g[i] = 0;
			for (int j = 0; j < i; ++j) {
				g[i] = (g[i] + 1ll * g[j] * f[S][i - j]) % P;
			}
			g[i] = 1ll * g[i] * inv[i] % P;
		}
		for (int i = 0; i <= m; ++i) {
			f[S][i] = g[i];
		}
	}
	for (int k = 0; k <= m; ++k) {
		for (int i = 0; i < m; ++i) {
			for (int S = 0; S < (1 << m); ++S) {
				if (S >> i & 1) {
					dec(f[S][k], f[S ^ (1 << i)][k]);
				}
			}
		}
	}
	init(1 << m);
	int ans = 0;
	for (int i = 0; i < (1 << m); ++i) {
		ans = (ans + 1ll * f[i][bitcnt[i]] * phi[i + 1]) % P;
	}
	for (int i = 0; i < a[0]; ++i) {
		ans = 2 * ans % P;
	}
	print(ans);
}
```

然而 $O(2^nn^2)$ 被 $O(3^n)$ 摁在地上摩擦...

---

## 作者：热言热语 (赞：17)

与题解无关的吐槽：这 T1、T2 和 T3 的算法难度差距怎么这么大……

### 约定

复杂度分析中，记 $n = 1+\left\lfloor \log_2 \max a_i \right\rfloor$，$m$ 为序列长度（输入格式中的 $n$），不计读入的复杂度。

### 做法 1

显然 $\sum a_{b_i}$ 的取值不会超过 $2^n-1$。

$O(2^n)$ 线筛求出所有的 $\varphi$，$O(2^m)$ 枚举每个数选不选并统计答案，合法性可以枚举过程中判断。

时间复杂度 $O(2^n+2^m)$，空间复杂度 $O(2^n+m)$，期望得分 10 分。

### 做法 2

$0$ 和其它数有点不一样，先特判掉，去掉所有 $0$ 后答案乘上 $2$ 的（$0$ 的个数）次幂即可。

设 $f(S)$ 表示选出的子序列中 $\sum a_{b_i}=S$ 的方案数，则答案即为
$$
\sum_{S=0}^{2^n-1} f(S)\varphi(1+S)
$$
把 $S$ 看作 $0 \ldots n-1$ 组成的集合，$S$ 的每一位代表对应的元素是否在集合中，可以利用子集 DP 求出所有的 $f(S)$，复杂度 $O(3^n)$。

具体地，设 ${\rm cnt}(S)$ 表示序列中 $S$ 的个数，令 $f(0)=1$，则有转移方程
$$
f(S) = \sum_{x \in T \subseteq S} {\rm cnt}(T) f(S-T)
$$
其中 $x$ 是 $S$ 中任意一个元素，这是为了确保选出集合的无序性，否则 $(1,2)$ 和 $(2,1)$ 会被算成两种不同的方案。实现时可以令 $x$ 为 $S$ 中最大的元素，这样条件可以简化为 $T \gt S-T$。

时间复杂度 $O(3^n)$，空间复杂度 $O(2^n)$，期望得分 60 ~ 100 分。

### 做法 3

**前置知识：** 快速莫比乌斯变换（FMT，也有说法把 FMT 统一归类为 FWT），快速子集变换（FST），形式幂级数（俗称多项式？），集合幂级数。

同样先特判掉所有的 $0$。

转移方程类似集合幂级数的子集卷积，考虑利用 FST 优化。

下面关于集合幂级数的内容参考了 2015 年 vfleaking 的国家集训队论文《集合幂级数的性质与应用及其快速算法》。

定义数列 $f(S)$ 的集合幂级数为 $\displaystyle F({\bf v}) = \sum_S f(S){\bf v}^S$，其中 ${\bf v}$ 是一个 $n$ 维向量，$\displaystyle {\bf v}^S = \prod_{i \in S} {\bf v}_i$。

由定义可以发现，$F$ 是关于 ${\bf v}_{0 \ldots n-1}$ 的 $n$ 元形式幂级数，并且 $F({\bf v})$ 和 $f(S)$ 是一一对应的。

把 ${\rm v}_{0 \ldots n-1}$ 取遍所有 $0,1$ 的组合可以得到 $2^n$ 个 $F({\bf v})$，观察每个 $f(S)$ 的贡献可以发现，这就是把 $f(S)$ 做 FMT 的结果。反过来，由所有的 $F({\bf v})$ 求出 $f(S)$ 的过程即为 IFMT。

当 ${\bf v}_i \in \{0,1\}$ 时有 ${{\bf v}_i}^2 = {\bf v}_i$，因此 ${\bf v}^S{\bf v}^T = {\bf v}^{S \cup T}$。

考察两个集合幂级数 $F({\bf v})$ 和 $G({\bf v})$ 的卷积：
$$
\begin{aligned}
F({\bf v})G({\bf v})
&= \sum_S \sum_T f(S)g(T) {\bf v}^S{\bf v}^T \\
&= \sum_S \sum_T f(S)g(T) {\bf v}^{S \cup T} \\
&= \sum_P {\bf v}^P \sum_{S \cup T = P} f(S)g(T)
\end{aligned}
$$
这就从另一个角度解释了集合并卷积的原理：FMT 相当于把所有 $0,1$ 的组合代入求出点值，卷积即对应点值相乘，IFMT 则相当于把点值代入插值出系数。

接下来考虑子集卷积。

定义数列 $f(S)$ 的集合占位幂级数为 $\displaystyle F(z,{\bf v}) = \sum_S f(S)z^{|S|}{\bf v}^S$。

由于 $S+T=P$ 等价于 $|S|+|T|=|P|$ 且 $S \cup T = P$，两个集合占位幂级数的卷积就对应了子集卷积。注意卷积结果中可能存在 $z$ 的次数大于 $|S|$ 的项，但它们不会影响我们需要的部分的系数。基于这个原因，若要严谨定义集合占位幂级数，还需要增加关于余项的描述。

计算两个集合占位幂级数的卷积可以利用 FMT 做到 $O(n^22^n)$，详情可参考 [P6097](https://www.luogu.com.cn/problem/P6097)，此处从略。

回到题目，可以发现我们需要求出 ${\rm cnt}(S)$ 的无序子集卷积。所谓无序，是指 $1,2$ 和 $2,1$ 只会被统计一次。

设 $F,G$ 分别为 $f(S),{\rm cnt}(S)$ 的集合占位幂级数，容易发现题目所求恰好对应了形式幂级数 exp 的组合意义，即
$$
F = \exp G = \sum_{k=0}^\infty {G^k \over k!} = 1 + G + {G^2 \over 2!} + {G^3 \over 3!} + \cdots
$$
和普通的形式幂级数 exp 一样，这里要求 $[z^0{\bf v}^\varnothing]G=0$，否则结果未定义。

首先可以发现 $k$ 只需要枚举到 $n$，因为最多有 $n$ 个子集。这样我们就有了一个 $O(n^32^n)$ 的做法。

考虑利用点值表示搞点事情。

先把 $G$ 看成是关于 ${\bf v}_{0 \ldots n-1}$ 的形式幂级数，那么它的每一项系数都是关于 $z$ 的形式幂级数。

如果把一组 ${\bf v}_i$ 代入 $G$，可以得到一个关于 $z$ 的形式幂级数，而一元形式幂级数的 exp 看上去则友好得多。所以，先利用 FMT 求出 $G$ 的点值，再把所有的点值 exp 后利用 IFMT 还原出系数，我们就得到了 $\exp G$。

于是这题就做完……了？

不对劲，模数是 $10^9+7$ 怎么 exp，难不成上个任意模数 NTT 吗……

注意到 $n$ 很小，$O(n^2)$ 暴力 exp 即可。具体地，设 $B(z) = \exp A(z)$，那么
$$
\begin{aligned}
B'(z) &= A'(z) \exp A(z) \\
[z^n]B'(z) &= [z^n]\big(A'(z) B(z)\big) \\
(n+1)[z^{n+1}]B(z) &= \sum_{k=0}^n (k+1)[z^{k+1}]A'(z) \cdot [z^{n-k}]B(z) \\
[z^n]B(z) &= {1 \over n} \sum_{k=1}^n k[z^k]A'(z) \cdot [z^{n-k}]B(z)
\end{aligned}
$$
边界为 $[z^0]B(z)=1$。

于是，我们得到了一个渐进复杂度比做法 2 更优、但在题目所给的数据范围下实际跑起来可能差不多的算法。

~~算得上是子集卷积 exp 的模板题？~~

时间复杂度 $O(n^22^n)$，空间复杂度 $O(n2^n)$，期望得分 60 ~ 100 分。

#### 核心代码

```cpp
int n, N = 0;
for (int i = fin.read_int(); i--; ) {
	int x = fin.read_int();
	++buk[x];
	N = std::max(N, x);
}

for (n = 0; 1 << n <= N; ++n);
N = 1 << n;

sieve(N);
init_inv(n);

popcnt[0] = 0;
for (int i = 1; i < N; ++i) {
	popcnt[i] = popcnt[i >> 1] + (i & 1);
	A[popcnt[i]][i] = buk[i];
}

for (int i = 1; i <= n; ++i) {
	FMT(A[i], N);
	for (int j = 0; j < N; ++j) A[i][j] = (ll)A[i][j] * i % cIz;
}

for (int i = 0; i < N; ++i) {
	B[0][i] = 1;
	for (int j = 1; j <= n; ++j) {
		int sum = 0;
		for (int k = 1; k <= j; ++k) {
			sum = (sum + (ll)A[k][i] * B[j - k][i]) % cIz;
		}
		B[j][i] = (ll)sum * inv[j] % cIz;
	}
}

for (int i = 0; i <= n; ++i) IFMT(B[i], N);

int ans = 0;
for (int i = 0; i < N; ++i) {
	ans = (ans + (ll)B[popcnt[i]][i] * phi[1 + i]) % cIz;
}
ans = (ll)ans * Pow(2, buk[0]) % cIz;

printf("%d\n", ans);
```


---

## 作者：皎月半洒花 (赞：15)

考虑最后求的是 $\varphi$ 套起来的东西。所以必然要从权值入手。

于是就是考虑有多少个合法子序列的和为 $x$ 。那么就考虑设 $f_{i}$ 表示和为 $i$ 的合法子序列的方案数。考虑如何转移出 $f_i$ 来。不难发现如果一个元素 $j$ 和前面的所有元素的 $\&$ 都为 $0$，这个条件等价于
$$
a_{b_j}\&\left(\bigcup_{k=1}^{j-1} a_{b_k}\right)=0\qquad(1)
$$
于是就可以对着这个式子来进行 dp。暴力复杂度可能是 $O(n\cdot \max\{a_i\})$ 的。稍微预处理一下可以通过 $40\%$ 的数据。

并且考虑 $(1)$ 式的本质，发现如果存在 $\geqslant 2$ 个数在某个二进制位上均为 $0$，那么一定是不合法的。 所以一个优秀的子序列，必然满足二进制下每一位，至多有一个数为 1 。那么考虑此时这个序列的和，在二进制下本质上不存在进位。于是可以发现 $f_i$ 同样也是**异或和**为 $i$ 的合法子序列方案数。

于是考虑对着这个 dp。发现实际上子序列并没有安排序列的选择顺序。于是考虑对于每一种异或和为 $x$ 的方案数，都可以在其中加入某个 $=y$ 的位置使得异或和变为 $x \operatorname{xor} y$ 。于是有转移

$$
f_i=\sum _{j\subseteq i} f_{i}\cdot \operatorname{count}(i\setminus j)
$$

其中 $\operatorname{count}(i)$ 表示 $i$ 的出现次数。

但注意这样转移其实是转移了俩方向。于是可以判掉那些和 $i$ 有相同 $\rm lowbit$ 的 $j$ 进行转移。设 $k=\log_2(\max\{a_i\}) $，那么这样做的复杂度是 $O(3^k)$ 。

之后不难发现这就是一个子集卷积的形式。可以考虑枚举 $\rm lowbit$ 来实现转移，复杂度 $O(2^k\cdot k^2)$ 。

```cpp
int cnt = 1 ;
bool check[M] ;
int prime[M] ;
int phi[M] ;
inline void init(int n){
    phi[1] = 1 ;
	for(int i=2;i<=n;i++){
		if(!check[i]){
			phi[i]=i-1;
			prime[cnt++]=i;
		}
		for(int j=1;j<=cnt;j++){
			if(prime[j]*i>n)break;
			check[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				phi[i*prime[j]]=prime[j]*phi[i];
				break;
			}
			else
			phi[i*prime[j]]=phi[i]*phi[prime[j]];
		}
	}
}

ll ans ;
int n, m ;
int f[N] ;
int buc[M] ;
int base[N] ;

int expow(int x, int y){
	int res = 1 ; 
	while (y){
		if (y & 1) res = 1ll * res * x % P ; 
		x = 1ll * x * x % P ; y >>= 1 ; 
	}
	return res ;
}

int low(int x){ return x & -x ; }

int main(){
    init(400000) ; int v ; cin >> n ;
    for (int i = 1 ; i <= n ; ++ i)
        buc[base[i] = qr()] ++, chkmax(m, base[i]) ;
	f[0] = expow(2, buc[0]) ;
    v = 1 ; while (v <= m) v <<= 1 ;
    for (int i = 1 ; i <= v ; ++ i)
        for (int j = i ; j >= 0 ; j = (j - 1) & i){
            if (low(i) != low(j))
                add(f[i], 1ll * f[j] * buc[i ^ j] % P) ;
            if (!j) break ;
        }
//    debug(f, 0, 50) ;
    for (int i = 0 ; i <= v ; ++ i)
        if (f[i]) add(ans, 1ll * f[i] * phi[1 + i] % P) ;
    cout << ans << '\n' ; return 0 ;
}
```




---

## 作者：StudyingFather (赞：8)

容易发现本题的实质是这样的：给若干个集合，从中选择一些集合，要求被选择的集合间两两没有交集，求所有合法选择方案中被选集合的权值和。

我们设 $f_i$ 表示选出的集合的并集为 $i$ 的合法选择方案数，则答案为 $\sum f_i \varphi(i+1)$。

现在考虑如何计算 $f_i$。

设 $cnt_x$ 表示 $x$ 集合出现的次数。

则有：

$$
f_x=\sum_{y \in x} f_y \times cnt_{x-y}
$$

边界是 $f_0=2^{cnt_0}$。

设集合包含的元素的个数的最大值为 $s$，则时间复杂度为 $O(3^s)$（看起来不太能过的样子，不过事实上还是过了）。

当然可以用子集卷积的方法做到 $O(s^2 2^s)$ 的时间复杂度，~~不过因为不会子集卷积~~就不展开讲了。

```cpp
#include <iostream>
#include <algorithm>
#define MOD 1000000007
using namespace std;
int phi[400005],pri[400005],a[400005],cnt;
long long f[400005];
int fpow(int x,int y)
{
 int ans=1;
 for(int i=1;i<=y;i++)
  ans=ans*x%MOD;
 return ans;
}
int main()
{
 int n,mx=0;
 cin>>n;
 for(int i=1;i<=n;i++)
 {
  int x;
  cin>>x;
  a[x]++;
  mx=max(mx,x);
 }
 phi[1]=1;
 int w=0;
 while(mx>=(1<<w))
  w++;
 for(int i=2;i<=(1<<w);i++)
 {
  if(!phi[i])
   pri[++cnt]=i,phi[i]=i-1;
  for(int j=1;j<=cnt&&i*pri[j]<=(1<<w);j++)
  {
   if(i%pri[j]!=0)
    phi[i*pri[j]]=phi[i]*phi[pri[j]];
   else
   {
    phi[i*pri[j]]=phi[i]*pri[j];
    break;
   }
  }
 }
 f[0]=fpow(2,a[0]);
 int p=0;
 for(int i=1;i<=mx;i++)
  if(a[i])
  {
   p|=i;
   int s=p^i;
   for(int t=s;;t=(t-1)&s)
   {
    f[i|t]=(f[i|t]+f[t]*a[i])%MOD;
    if(!t)break;
   }
  }
 long long ans=0;
 for(int i=0;i<(1<<w);i++)
  ans=(ans+f[i]*phi[i+1])%MOD;
 cout<<ans<<endl;
 return 0;
}
```

---

## 作者：Caro23333 (赞：8)

主要讲两个做法，分别是考场的 sb 做法和考后得知的 _渐进最优但常数堪忧_ 的做法。

**前置知识：**[子集卷积](https://www.luogu.com.cn/problem/P6097)

### 做法0

令 $v=\max a_i, k=\lfloor\log_2 v+1\rfloor$。

首先很明显，$\varphi$ 就是个吓唬人的幌子。因为每个二进制位最多在子序列中出现一次，那么一个子序列的和不会超过 $2^{18}$，所以可以尝试求出 $f_x$ 有多少个子序列和为 $x$。

为了方便起见，设原序列中 $0$ 的个数为 $c$ 并在后续计算中忽略所有的 $0$，那么我们只要将得到的 $f_1,f_2,\dots$ 都乘上 $2^c$（可以任意添加一些 $0$），再单独加上全 $0$ 子序列的贡献（易于计算）即可。

分析题目条件：对于一个二进制数 $x$，我们可以将其等效地看作一个 $\{0,1,\dots,k\}$ 的子集，同理原序列就是一系列的子集。为了方便，后续可能会将集合与二进制数混用。

那么 $f_x$ 就表示从序列中选取若干互不相交的集合使得它们的并为 $x$ 的方案数。令 $g_x$ 表示原序列中 $x$ 的个数，不难发现有递推式:

$$f_x=\sum_{y\subset x}f_yg_{x-y}$$

直接计算即可，复杂度 $O(3^k)$。实际上好像可以过？

### 做法1

递推式让我们想到了子集卷积。对于序列 $a$ 与 $b$，定义它们的子集卷积 $a*b$ 为：

$$(a*b)_x=\sum_{y\subset x}a_yb_{x-y}$$

对于原序列的一个集合 $a_i$，构造序列 $p^{(i)}$ 使得 $p^{(i)}_j=1$ 当且仅当 $j=0$ 或 $j=a_i$，那么就有 $f=p^{(1)}*p^{(2)}*\dots *p^{(n)}$。根据前置知识，如果全集大小为 $k$，计算一次子集卷积的时间复杂度为 $O(k^22^k)$。而直接计算这个递推式需要运用 $n$ 次子集卷积，完全无法接受。

优化的思想是分组。直观上来讲，每个 $p^{(i)}$ 里面非 $0$ 的项相当少，十分浪费，所以我们可以将某些 $p^{(i)}$ 分组合并到一起。

考虑 $q^{(j)}$，表示所有最高位为第 $j$ 位的 $a_i$，它们 $p^{(i)}$ 的和。由于最高位相同的集合必定有交，那么它们之间不会互相贡献，这样的话不会影响答案。形式化地来说，我们不难验证

$$q^{(0)}*q^{(1)}*\dots *q^{(k-1)}=p^{(1)}*p^{(2)}*\dots *p^{(n)}$$

那么只要从左到右计算左式即可。这样看起来是 $O(k^32^k)$ 的，但因为计算到 $q^{(j)}$ 时，当前序列的规模不会超过 $2^{j+1}$（最高位至多只有 $j$），这样我们可以逐步扩大子集卷积的规模来计算，总复杂度为

$$\sum_{j=0}^{k-1} O((j+1)^22^{j+1})<\sum_{j=0}^{k-1} O(k^22^{j+1})=O(k^22^k)$$

经过艰难的卡常可以通过此题（洛谷，无O2）。细节见代码。

### 做法2

sb 的考场做法。复杂度和常数均差，没兴趣可以不看。

考虑子集卷积的实现细节。对于序列 $a,b$，计算 $c=a*b$ 时我们需要先按照集合大小将 $a,b,c$ 分为 $a^{(0)},a^{(1)},\dots,a^{(k)},b^{(0)},b^{(1)},\dots,b^{(k)},c^{(0)},c^{(1)},\dots,c^{(k)}$，然后将 $a,b$ 的各组分别 FMT。然后有：

$$c^{(i)}_k=\sum_{j=0}^i a^{(j)}_kb^{(i-j)}_k$$

然后对 $c$ 的各组做 IFMT 即可。回顾上一个做法中的 $p^{(0)},p^{(1)},\dots,p^{(n)}$，令 $s$ 为它们的和，同样将 $s$ 分组并 FMT，那实际上我们可以类比地推出

$$f^{(m)}_x=\sum_{i_1+2i_2\dots+ki_k=m} \frac{(s^{(1)}_x)^{i_1}(s^{(2)}_x)^{i_2}\dots(s^{(k)}_x)^{i_k}}{i_1!i_2!\dots i_k!}$$

（除掉 $i_j!$ 是因为要求无序）

很明显这是一个背包的形式。首先从 $1$ 到 $k$ 枚举 $j$，再枚举 $x$，再枚举 $i_j$，最后再枚举 $m$，利用调和级数可以证明总复杂度是 $O(k^22^k\log k)$。洛谷O2可过，考场爆零。细节见代码。

### 做法3

其实思考一下组合意义，发现上面那一坨东西很像是生成函数中的 $\exp$ 操作。

然后其实还真有这么个东西，叫子集卷积 $\exp$。详见 [LOJ 154](https://loj.ac/problem/154) 及其题解。

复杂度 $O(k^22^k)$，具体速度没实现过就不妄议了。

**做法1代码：**
```cpp
#include <bits/stdc++.h>
#define mod 1000000007

using namespace std;
typedef long long ll;
const int MAXN = 1000005, MAXS = 270005;
namespace io{
 const int size=1<<22|1;
 char iBuf[size],*iS,*iT,c;
 char oBuf[size],*oS=oBuf,*oT=oBuf+size;
 #define getc() (iS==iT?iT=iBuf+fread(iS=iBuf,1,size,stdin),(iS==iT?EOF:(*iS++)):(*iS++))
 template<class T>void qread(T &x){
  int f=1;
  for(c=getc();c<'0'||c>'9';c=getc())
   if(c=='-')f=-1;
  for(x=0;c>='0'&&c<='9';c=getc())
   x=(x<<3)+(x<<1)+(c&15);
  x*=f;
 }
 void flush(){
  fwrite(oBuf,1,oS-oBuf,stdout);
  oS=oBuf;
 }
 void putc(char x){
  *oS++=x;
  if(oS==oT)flush();
 }
 template<class T>void qwrite(T x){
  static char qu[55];
  char *tmp=qu;
  do *tmp++=(x%10)^'0';while(x/=10);
  while(tmp--!=qu)putc(*tmp);
 }
 struct flusher{
  ~flusher(){flush();}
 }_;
}
int n,a[MAXN];
inline int modd(int x)
	{ return x>=mod?x-mod:x; }
int f[19][MAXS],res[19][MAXS],tmp[19][MAXS],cc[MAXS],bin[MAXS];
inline void fwt(int *a, int deg)
{
	for(int i = 1; i<deg; i <<= 1)
		for(int j = 0; j<deg; j += i<<1)
			for(int k = j; k<j+i; k++)
				a[k+i] = modd(a[k+i]+a[k]);
}
inline void ifwt(int *a, int deg)
{
	for(int i = 1; i<deg; i <<= 1)
		for(int j = 0; j<deg; j += i<<1)
			for(int k = j; k<j+i; k++)
				a[k+i] = modd(a[k+i]-a[k]+mod); 
}
inline int qpow(int a, int b)
{
	int res = 1;
	for(; b; a = 1ll*a*a%mod, b >>= 1)
		if(b&1)
			res = 1ll*res*a%mod;
	return res;
}
int prime[MAXS],phi[MAXS],tot;
bool vis[MAXS];
inline void makeTable()
{
	phi[1] = 1;
	for(int i = 2; i<MAXS; i++)
	{
		if(!vis[i])
			prime[++tot] = i, phi[i] = i-1;
		for(int j = 1; j<=tot&&prime[j]*i<MAXS; j++)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j]==0)
			{
				phi[i*prime[j]] = phi[i]*prime[j];
				break;
			}
			else
				phi[i*prime[j]] = phi[i]*(prime[j]-1);
		}
	}
}

int main()
{
	//freopen("sequence.in","r",stdin);
	io::qread(n);
	int cnt = 0;
	for(int i = 1; i<=n; i++)
		io::qread(a[i]);
	for(int i = 1; i<=n; i++)
		cnt += a[i]==0;
	for(int i = 0; i<MAXS; i++)
		cc[i] = __builtin_popcount(i);
	bin[0] = -1;
	for(int i = 2; i<MAXS; i++)
		bin[i] = bin[i>>1]+1;
	res[0][0] = 1;
	fwt(res[0],1<<0);
	memcpy(tmp[0],res[0],(1<<0)*4);
	for(int i = 0; i<18; i++)
	{
		int lim = 1<<i, mil = 1<<i+1;
		for(int j = 0; j<=i; j++)
			for(int k = 0; k<lim; k++)
				res[j][k+lim] = modd(res[j][k+lim]+res[j][k]);
		for(int j = 0; j<=i; j++)
			memcpy(tmp[j],res[j],mil*4);
		for(int j = 1; j<=n; j++)
			if(bin[a[j]]==i)
				f[cc[a[j]]][a[j]]++;
		for(int j = 1; j<=i+1; j++)
			fwt(f[j],mil);
		for(int j = 1; j<=i+1; j++)
			for(int k = 1; k<=j; k++) 
				for(int p = 0; p<mil; p++)
					if(tmp[j-k][p]&&f[k][p])
						res[j][p] = modd(res[j][p]+1ll*tmp[j-k][p]*f[k][p]%mod); 
		for(int j = 1; j<=i+1; j++)
			memset(f[j],0,mil*4);
	}
	for(int i = 1; i<=18; i++)
		ifwt(res[i],1<<18);
	makeTable();
	int ans = 0, r = qpow(2,cnt);
	for(int i = 1; i<1<<18; i++)
		ans = modd(ans+1ll*r*res[cc[i]][i]%mod*phi[i+1]%mod);
	cout << modd(ans+r) << endl;
	return 0;
}

```
**做法2代码：**
```cpp
#pragma GCC optimize(2)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define mod 1000000007

using namespace std;
typedef long long ll;
const int MAXN = 1000005, MAXS = 270005;
inline int readint()
{
	int res = 0, f = 1;
	char c = 0;
	while(!isdigit(c))
	{
		c = getchar();
		if(c=='-')
			f = -1;
	}
	while(isdigit(c))
		res = res*10+c-'0', c = getchar();
	return res*f;
}
namespace io{
 const int size=1<<22|1;
 char iBuf[size],*iS,*iT,c;
 char oBuf[size],*oS=oBuf,*oT=oBuf+size;
 #define getc() (iS==iT?iT=iBuf+fread(iS=iBuf,1,size,stdin),(iS==iT?EOF:(*iS++)):(*iS++))
 template<class T>void qread(T &x){
  int f=1;
  for(c=getc();c<'0'||c>'9';c=getc())
   if(c=='-')f=-1;
  for(x=0;c>='0'&&c<='9';c=getc())
   x=(x<<3)+(x<<1)+(c&15);
  x*=f;
 }
 void flush(){
  fwrite(oBuf,1,oS-oBuf,stdout);
  oS=oBuf;
 }
 void putc(char x){
  *oS++=x;
  if(oS==oT)flush();
 }
 template<class T>void qwrite(T x){
  static char qu[55];
  char *tmp=qu;
  do *tmp++=(x%10)^'0';while(x/=10);
  while(tmp--!=qu)putc(*tmp);
 }
 struct flusher{
  ~flusher(){flush();}
 }_;
}
int n,a[MAXN],cc[MAXN],inv[MAXN];
int f[19][MAXS],g[19][MAXS],h[19][MAXS];
inline int modd(int x)
	{ return x>=mod?x-mod:x; }
inline void fwt(int *a, int deg)
{
	for(int i = 1; i<deg; i <<= 1)
		for(int j = 0; j<deg; j += i<<1)
			for(int k = j; k<j+i; k++)
				a[k+i] = modd(a[k+i]+a[k]);
}
inline void ifwt(int *a, int deg)
{
	for(int i = 1; i<deg; i <<= 1)
		for(int j = 0; j<deg; j += i<<1)
			for(int k = j; k<j+i; k++)
				a[k+i] = modd(a[k+i]-a[k]+mod);
}
inline int count(int x)
{
	int res = 0;
	for(; x; x -= x&-x)
		res++;
	return res;
}
int prime[MAXS],phi[MAXS],tot;
bool vis[MAXS];
inline void makeTable()
{
	phi[1] = 1;
	for(int i = 2; i<MAXS; i++)
	{
		if(!vis[i])
			prime[++tot] = i, phi[i] = i-1; 
		for(int j = 1; j<=tot&&prime[j]*i<MAXS; j++)
		{
			vis[prime[j]*i] = true;
			if(i%prime[j]==0)
			{
				phi[prime[j]*i] = phi[i]*prime[j];
				break;
			}
			else
				phi[prime[j]*i] = phi[i]*(prime[j]-1);
		}
	}
}
inline ll qpow(ll a, int b)
{
	ll res = 1;
	for(; b; a = a*a%mod, b >>= 1)
		if(b&1)
			res = res*a%mod;
	return res;
}
inline ll getInv(ll x)
	{ return qpow(x,mod-2); }

int main()
{
	freopen("sequence.in","r",stdin); 
	freopen("sequence.out","w",stdout);
	io::qread(n);
	for(int i = 1; i<=n; i++)
		io::qread(a[i]);
	int maxa = 0;
	for(int i = 1; i<=n; i++)
		maxa = max(maxa,a[i]);
	for(int i = 0; i<1<<18; i++)
		cc[i] = count(i);
	inv[0] = 1;
	for(int i = 1; i<=20; i++)
		inv[i] = inv[i-1]*getInv(i)%mod;
	int cnt = 0;
	for(int i = 1; i<=n; i++)
		f[cc[a[i]]][a[i]]++;
	for(int i = 1; i<=n; i++)
		cnt += a[i]==0; 
	for(int i = 1; i<=18; i++)
		fwt(f[i],1<<18);
	for(int i = 1; i<=18; i++)
	h[0][0] = 1;
	fwt(h[0],1<<18);
	for(int i = 1; i<=18; i++)
	{
		memcpy(g,h,sizeof(h)); 
		for(int k = 0; k<1<<18; k++)
		{
			int now = 1;
			for(int p = 1; p*i<=18; p++)
			{
				now = 1ll*now*f[i][k]%mod;
				for(int j = p*i; j<=18; j++)
					h[j][k] = modd(h[j][k]+1ll*g[j-p*i][k]*now%mod*inv[p]%mod); 
			}
		}
	}
	for(int i = 1; i<=18; i++)
		ifwt(h[i],1<<18);
	makeTable();
	int ans = 0;
	int tmp = qpow(2,cnt);
	for(int i = 1; i<1<<18; i++)
		ans = modd(ans+1ll*tmp*h[cc[i]][i]%mod*phi[i+1]%mod)%mod;
	ans = modd(ans+tmp);
	cout << ans << endl; 
	return 0;
}

```


---

## 作者：dqa2022 (赞：7)

## NOI Online #3 提高组 优秀子序列 题解

* 子序列合法相当于用若干个子集恰好拼成了一个集合，注意这里需要特殊考虑 $a_i=0$ 的情况，届时它只是凑数的，可以出现或不出现在任何一个拼凑方案中。下面假设 $\forall 1\le i\le n,a_i>0$。
* 容易想到求出拼凑出每个集合的方案数，这样最后乘上 $\varphi$ 函数就做完了。
***
* 设 $dp_S$ 表示拼凑出 $S$ 的方案数，转移的时候枚举超集转移。注意这样会算重，可以强制每个子集的开头/结尾位置要递减/递增解决这个问题。这个过程的时间复杂度是 $O(3^m)$ 的。$m$ 是最小的非负整数使得 $2^m>\max a_i$，即集合的大小，下同。感觉卡卡常可以过。
* 推测更多人、更多题解选择这种方法，且该方法不是本文重点，因此可能比较简略，见谅。
***
* 还有另一种基于子集卷积的方法。子集卷积利用popcount（二进制下 $1$ 的个数）以及or卷积来体现交为空的限制。具体可以看看洛谷的模板题。
* 现在考虑子集卷积怎么做，由于fwt之后的运算是对位相乘，可以独立考虑每个位置。对于每个位置 $k$，写出关于popcnt的普通生成函数，那么每个 $a_i$ 的贡献是 $(1+c_{k,i}x^{d_{i}})$，其中 $c_{k,i}$ 表示仅将位置 $a_i$ 设为 $1$ 进行fwt之后第 $k$ 位的系数（显然为 $0$ 或 $1$；下文省略下标 $k$），$d_{i}$ 表示 $a_i$ 的popcnt。因此位置 $k$ 的生成函数为
$$\prod_{i=1}^n (1+c_ix^{d_i})$$
* 我们需要知道这个生成函数的 $i\in[0,m]$ 项（作为每个popcnt的最终fwt值）。考虑如何快速计算。
$$
\prod_{i=1}^n (1+c_ix^{d_i})
$$
$$
=\exp( \sum_{i=1}^n \ln(1+c_ix^{d_i}))
$$
$$=\exp( \sum_{i=1}^n \sum_{j=1}^{+\infty}\frac{(-1)^{i-1}x^i}{i})$$
* 括号内的部分可以在不高于 $O(m^2)$ 的时间内计算，计算完之后直接exp即可。注意这里exp不需要牛顿迭代，不需要ntt，可以直接 $O(m^2)$ 递推（DP）计算：
$$F(x)=e^{G(x)}$$
* 两边求导：
$$F'(x)=e^{G(x)}G'(x)$$
$$F'(x)=F(x)G'(x)$$
* 两边积分：
$$F(x)=\int F(x)G'(x)$$
* 因此对于 $i>0$ ：
$$f_i=\frac{1}{i}\sum_{j=0}^{i-1}(i-j)f_jg_{i-j}$$
* 最后再取这 $m+1$ 项作为第 $k$ 位上每个popcnt的最终fwt值，分别ifwt回来。
* 这个过程的复杂度是 $O(m^22^m)$ 的。

```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
#define G getchar()
int read()
{
	int x=0; char ch=G;
	for (;!isdigit(ch);ch=G);
	for (;isdigit(ch);ch=G) x=(x<<3)+(x<<1)+(ch^48);
	return x;
}
#undef G
typedef long long ll;
const int Mod=1e9+7;
const ll SMod=1LL*Mod*Mod;
int qpow(int x,int y){
	int res=1;
	for (;y;y>>=1,x=1LL*x*x%Mod)
		if (y&1) res=1LL*res*x%Mod;
	return res;
}
inline int upd(int x){return x+(x>>31&Mod);}
inline ll supd(ll x){return x+(x>>63&SMod);}
bool vis[1<<18|100]; int prm[1<<18|100],phi[1<<18|100];
void sieve(int x){
	phi[1]=1;
	for (int i=2;i<=x;i++){
		if (!vis[i]) prm[++*prm]=i,phi[i]=i-1;
		for (int j=1,t;j<=*prm&&i*prm[j]<=x;j++){
			vis[t=i*prm[j]]=1;
			if (i%prm[j]==0){phi[t]=phi[i]*prm[j];break;}
			phi[t]=phi[i]*phi[prm[j]];
		}
	}
}
int inv[32];

int n,w[1000010],c[1<<18],maxc,maxw,btw;
int popcnt[1<<18];
int f[19][1<<18];
inline void add(int &x,int y){x=upd(x+y-Mod);}
inline void iadd(int &x,int y){x=upd(x-y);}
void fwt(int *f){
	for(int i=0;i<btw;i++)
		for (int j=0;j<maxw;j++)
			if (!(j>>i&1))
				add(f[1<<i|j],f[j]);
}
void ifwt(int *f){
	for(int i=0;i<btw;i++)
		for (int j=0;j<maxw;j++)
			if (!(j>>i&1))
				iadd(f[1<<i|j],f[j]);
}
inline void work(int x){
	static int d[19],g[19]; static ll _d[19];
	for (int i=0;i<=btw;i++) g[i]=f[i][x],_d[i]=0;
	for (int i=1;i<=btw;i++)
		for (int j=i,t=1;j<=btw;j+=i,t++){
			if (t&1) _d[j]=supd(_d[j]+1LL*g[i]*inv[t]-SMod);
			else _d[j]=supd(_d[j]-1LL*g[i]*inv[t]);
		}
	for (int i=0;i<=btw;i++) d[i]=_d[i]%Mod*i%Mod,g[i]=0;
	f[0][x]=g[0]=1;
	for (int i=1;i<=btw;i++){
		ll C=0;
		for (int j=0;j<i;j++)
			C=supd(C+1LL*g[j]*d[i-j]-SMod);
		f[i][x]=g[i]=C%Mod*inv[i]%Mod;
	}
}
int ans;
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	
	n=read();
	for (int i=1;i<=n;i++) c[w[i]=read()]++;
	for (maxc=(1<<18)-1;!c[maxc];maxc--);
	if (!maxc) return printf("%d\n",qpow(2,c[0])),0;
	for (maxw=1,btw=0;maxw<=maxc;maxw<<=1,btw++);
	inv[1]=1; for (int i=2;i<=btw;i++) inv[i]=1LL*(Mod-Mod/i)*inv[Mod%i]%Mod;
	sieve(maxw);
	for (int i=1;i<maxw;i++) popcnt[i]=popcnt[i>>1]+(i&1);
	for (int i=1;i<=n;i++) if (w[i]) f[popcnt[w[i]]][w[i]]++;
	for (int i=1;i<=btw;i++) fwt(f[i]);
	for (int i=0;i<maxw;i++) work(i);
	for (int i=0;i<=btw;i++) ifwt(f[i]);
	for (int i=0;i<maxw;i++) ans=(ans+1LL*f[popcnt[i]][i]*phi[i+1])%Mod;
	ans=1LL*ans*qpow(2,c[0])%Mod;
	printf("%d\n",ans);
	return 0;
}
```
***
* 请不吝指正或补充！

---

## 作者：dengyaotriangle (赞：7)

我们首先把数列中的数作为集合看待，具体来说，$x$ 的二进制表示中第 $i$ 位的 $0$ 代表不包含 $i$，第 $i$ 位的 $1$ 代表包含 $i$，也就是状压 $dp$ 的那种表示方式。

那么 $a\operatorname{and} b=0\Leftrightarrow a\cap b=\varnothing$，也就是说合法的子序列中任意两个数交集为空，这就意味着对于一个合法子序列 $S$，$\sum_{x\in S} x= \bigcup_{x\in S} x$，而根据数据范围  $S\subseteq 2^{18}-1$

所以我们只需要求出 $\bigcup_{x\in S} x=0,1,\cdots,2^{18}-1$ 的所有子序列 $S$ 的个数，就可以直接乘以那个 $\varphi(x)$ 的系数求和得到答案。

考虑朴素 $dp$，$dp_{i,j}$ 代表前 $i$ 个数中，$\bigcup_{x\in S} x=j$ 的 $S$ 的个数。

有 $dp_{0,0}=1$

$$dp_{i,j}=dp_{i-1,j}+\begin{cases}0& a_i\not\subseteq j\\ dp_{i-1,j\setminus a_i} & a_i \subseteq j\end{cases}$$

就是说，如果 $a_i$ 不是 $j$ 的子集，显然不能加，否则，转移之前的那个集合和 $j$ 的交集必须为空，否则就不合法，故只能包含 $j$ 与 $a_i$ 的差集。

我们发现，由于子序列没有顺序关系，我们可以假装原序列是从小到大排序的，这样我们可以直接消去一维。

$dp_i$ 表示 $\bigcup_{x\in S} x=i$ 的子序列个数，我们发现这样的子序列一定是只由 $\leq i$ 的数组成的。

设 $c_i$ 为 $a_x=i$ 的 $x$ 的个数，即 $i$ 在原序列出现次数

显然，$dp_0=2^{c_0}$，因为 $0$ 随便咋选都没问题。

$$dp_i=\sum_{j\subseteq i,k=i\setminus j,j>k} dp_k\times c_j$$

考虑枚举子序列中最大的那个数 $j$，显然 $j$ 有 $c_j$ 个，选任意一个都没问题，剩下的就是 $dp_k$，而 $j$ 是最大的，故必须要求 $j>k$

我们发现这样 $dp$ 就能过，这是因为一个结论：$n$ 个元素的集合的子集的子集的个数为 $3^n$，而这个 $dp$ 的复杂度显然就是子集的子集个数（因为对于每一个 $i$ 都枚举了它的所有子集 $j$）

所以总复杂度 $O(n+3^{18})$，常数较小，大概可以通过

当然你也可以写一些子集卷积之类的东西，但没必要。

---

## 作者：Marser (赞：7)

考场上似乎一发做出来了，开心。
### 题意
给定一个长度为 $n$ 的非负整数序列 $A=\{a_1,a_2,\cdots,a_n\}$，对于 $A$ 的一个子序列 $B=\{a_{b_1},a_{b_2},\cdots,a_{b_m}\}$（$0\le m\le n$，$1 \le b_1 \lt b_2 \lt \cdots \lt b_m \le n$，下同），称 $B$ 是 $A$ 的优秀子序列当且仅当，其任意两个不同元素的按位与结果均为 $0$，即：$\forall 1\le i \lt j\le m$，满足：$a_{b_i}~\mathrm{and}~a_{b_j}=0$，其中 $\mathrm{and}$ 是按位与运算。

对于子序列 $B=\{a_{b_1},a_{b_2},\cdots,a_{b_m}\}$，我们定义其价值为 $\varphi \left(1+\sum\limits_{i=1}^m a_{b_i}\right)$，其中 $\varphi(x)$ 表示小等于 $x$ 的正整数中与 $x$ 互质的数的个数。

现在请你求出 $A$ 的所有优秀子序列的价值之和，答案对 $10^9+7$ 取模。

### 题解
首先，我们可以选择任意个 $0$，并且不会对结果造成任何影响，所以我们先不考虑选择 $0$ 的情况。  
我们发现，由于 $a_{b_i}~\mathrm{and}~a_{b_j}=0$ 这一限制，最终选出的数列之和不会很大，最大只有可能达到 $2^{18}$。同时，对于每个二进制位，最多只有一个被选中的数该位上为 $1$。  
发现数列的价值与数列的总和有关，我们考虑算出和为 $x$ 的不同合法序列的方案数，由于它们的贡献是一定的，我们就可以直接计算了。

令 $f_i$ 为和为 $i$ 的不同合法序列的方案数，容易看出，由于题目的限制，状态的转移构成一张有向无环图。因此，我们可以按照一定的顺序更新。  
简单推导可以知道，从 $0$ 开始枚举到上界是可行的方法，且每次枚举到的 $f_i$ 一定已经更新完毕。那么我们每次只要考虑当前的 $i$ 能转移到哪些位置即可。  
根据约束条件，令 $U=2^{18}$ ，我们可以枚举 $s \in \complement_U^i$，则 $f_i$ 可以转移到 $f_{i\cup s}$。由二项式定理可知，这一过程的复杂度是 $O(3^{18})$ 的。

注意到上述转移全部建立在不选择 $0$ 的基础上。记 $cnt_0$ 表示数列中 $0$ 的个数，对于每一种不选择 $0$ 的方案，都存在 $2^{cnt_0}$ 种可以选择 $0$ 且非 $0$ 数与原方案相同的方案。同时，新的方案数列和不变，因此总价值不变。  
我们处理出 $[1,U]$ 的 $\varphi$ 函数值，即可轻松计算贡献。

### 代码
```cpp
#include<cstdio>
#include<algorithm>
#define reg register
typedef long long ll;
using namespace std;
namespace IO{
    char buf[1<<15],*S,*T;
    inline char gc(){
        if(S==T){
            T=(S=buf)+fread(buf,1,1<<15,stdin);
            if(S==T)return EOF;
        }
		return *S++;
    }
    inline int read(){
        reg int x;reg char c;
        for(;(c=gc())<'0'||c>'9';);
        for(x=c^'0';(c=gc())>='0'&&c<='9';x=x*10+c-'0');
        return x;
    }
}
const int mod=1e9+7;
const int MN=262150;
inline ll qpow(ll a,ll b){
	reg ll res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;b>>=1;
	}
	return res;
}
int n,m,a[MN],f[MN];
int pcnt,pri[MN],phi[MN];
bool vis[MN];
using IO::read;
int main(){
//	freopen("sequence.in","r",stdin);
//	freopen("sequence.out","w",stdout);
	n=read();
	for(reg int i=1,x;i<=n;i++)
		a[x=read()]++,m=max(m,x);
	reg int U=1;
	while(U<=m)U<<=1;
	for(reg int i=1;i<U;i++)f[i]=a[i];
	for(reg int i=1;i<U;i++)
		if(f[i])for(reg int s=(U-1)^i,S=s;S>i;S=(S-1)&s)
			if(a[S])f[i+S]=(f[i+S]+1ll*f[i]*a[S])%mod;
	f[0]=qpow(2,a[0]);
	for(reg int i=1;i<U;i++)f[i]=1ll*f[i]*qpow(2,a[0])%mod;
	phi[1]=1;
	for(reg int i=2;i<=U;i++){
		if(!vis[i])pri[++pcnt]=i,phi[i]=i-1;
		for(reg int j=1;i*pri[j]<=U&&j<=pcnt;j++){
			vis[i*pri[j]]=true;
			if(i%pri[j])phi[i*pri[j]]=phi[i]*(pri[j]-1);
			else{phi[i*pri[j]]=phi[i]*pri[j];break;}
		}
	}
	reg int Ans=0;
	for(reg int i=0;i<U;i++)Ans=(Ans+1ll*f[i]*phi[i+1])%mod;
	printf("%d\n",Ans);
	return 0;
}
```

---

## 作者：良心WA题人 (赞：3)

# 简洁题意
要求从 $A$ 选出子集 $B$ 使得 $B$ 中没有两个数按位与等于 $0$。每个子集 $B$ 的价值是集合内所有数的和加一的 $\varphi$ 值。求所有子集 $B$ 的价值之和。
# 分析
可以思考，因为要知道所有的集合 $B$ 不容易，所以考虑计算价值相同的 $B$ 的个数。

设 $f_i$ 表示所有值为 $i$ 的子集 $B$ 的数量，我们算出 $f_i$  后乘上 $\varphi_{i+1}$ 就是这个方案的价值和，把每个价值和加在一起就是答案。

考虑怎么计算这个 $f$ ，我们可以把 $f$ 拆成两部分，然后一部分直接用 $f_j$ ，另一部分用集合 $A$ 的一个数来补上就行。因为题目要 $B$ 中所有数的按位与均等于 $0$ ，所以不会出现有两个数的某一位都是 $1$ 的情况。所以我们在拆 $i$ 的时候可以把 $i$ 中为 $1$ 的位分成两半来计算。为了方便处理，我们把 $num_x$ 表示 $a_j$ 中值为 $x$ 的个数， $s$ 表示 $i$ 分出来的一个数， $t$ 为剩余的部分，为了保证不重复计算，要求 $s\ge t$ ，根据乘法原理，则有状态转移方程 $f_i=\sum f_s\times num_t$ 。

可是这样就有一个问题：这些数的和的上限很大，内存装不下啊！不用担心，因为我们选出来的数不会有两位都是$1$的情况，所以选出来的和自然小于 $2^{\lfloor\log_2(\max\{a_i\})+1\rfloor}$ ，以 $2^{\lfloor\log_2(\max\{a_i\})+1\rfloor}$ 为上限即可。

但是这样就会出现一个情况：$a_i=0$ 算漏了！其实 $a_i$ 等于 $0$ 时用不用都没关系，根据乘法原理，所以答案要乘上 $2^{num_0}$ 。至于筛法求 $\varphi$ （就是在筛质数时筛 $\varphi$ 函数）和求一个集合的子集（要拆 $i$ ），大家应该都会吧？
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=300000,P=1e9+7;
int num[NN],phi[NN],f[NN];
bool vis[NN];
int main()
{
	int n,maxx=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		num[x]++;
		maxx=max(maxx,x);
	}
	int m=0;
	while((1<<m)<=maxx)
		m++;
	phi[1]=1;
	for(int i=2;i<=(1<<m);i++)
		if(!vis[i])
			for(int j=i;j<=(1<<m);j+=i)
			{
				vis[j]=true;
				if(!phi[j])
					phi[j]=j;
				phi[j]=phi[j]/i*(i-1);
			}
	f[0]=1;
	for(int i=1;i<=(1<<m);i++)
		for(int s=i;;s=(s-1)&i)
		{
			int t=i^s;
			if(s<t)
				break;
			f[i]=(f[i]+1ll*f[t]*num[s])%P;
		}
	int ans=0;
	for(int i=0;i<=(1<<m);i++)
		ans=(ans+1ll*f[i]*phi[i+1])%P;
	for(int i=1;i<=num[0];i++)
		ans=ans*2ll%P;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：s_r_f (赞：3)

题目里的式子很像子集卷积$,$但我不会$,$所以就写暴力了$.$

首先$0$这个数没有任何意义$,$可以看做把答案乘以$2$然后删去这个$0.$

然后数列中的数字非零$,$不难发现数字的顺序没有意义$,$所以我们可以把数列中的数记录一个$cnt_x$表示数字$x$出现了多少次$.$

考虑从小到大加入数字并$dp.$

记$dp_S$为当前所有数的$or$为$S$的方案数$,$那么加入数字$x$的转移就是

$dp_T=dp_T+dp_{T-x}\times cnt_x,$其中$x ∈T.$

那么就可以枚举$x$的补集的子集$,$就可以转移了$.$

$dp$求完之后$,$筛个$φ$就可以得到答案了$.$

---

关于枚举子集的方式$:$

```cpp
int S;
for (int T = S; T >= 0; T = (T-1)&S){
	//do something
	if (!S) break;
}
```
就可以$O(1)$枚举一个子集$.$

---

复杂度$<O(3^{log_2n}),$本地测满数据$1.7s-1.8s.$

代码$:$

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
template <typename T> void read(T &x){
	x = 0; int f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - '0'; ch = getchar();}
	x *= f;
}
inline void write(int x){if (x > 9) write(x/10); putchar(x%10+'0'); }

const int N = 1<<18,P = 1e9 + 7;

int phi[341413],p[230005],cntp;
inline void sieve(int n){
	int i,j;
	phi[1] = 1;
	for (i = 2; i <= n; ++i){
		if (!phi[i]) phi[i] = i-1,p[++cntp] = i;
		for (j = 1; i * p[j] <= n; ++j){
			if (i % p[j]) phi[i*p[j]] = phi[i] * (p[j]-1);
			else{ phi[i*p[j]] = phi[i] * p[j]; break; }
		}
	}
}

inline void upd(int &x,int v){ x = (x+v>=P)?(x+v-P):(x+v); }
int n,m;
int cnt[(1<<18)+50],temp = 1,F[(1<<18)+50],suma;

int main(){
	register int i,j,x;
//	freopen("sequence.in","r",stdin); freopen("sequence.out","w",stdout);
	read(n);
	for (i = 1; i <= n; ++i) read(x),++cnt[x];
	F[0] = 1;
	for (i = 1; i <= cnt[0]; ++i) temp = (temp * 2) % P; cnt[0] = 0;
	for (n = 0,i = (1<<18)-1; i ; --i) if (cnt[i]){ n = i; break; }
	i = n; n = 1; while (n <= i) n <<= 1; sieve(300000);
	m = 1;
	for (i = 1; i <= 200000; ++i) if (cnt[i]){
		m |= i;
		int s = m^i;
		for (register int t = s; ; t = (t-1)&s){
			upd(F[i|t],(LL)F[t]*cnt[i]%P);
			if (!t) break;
		}
	}
	for (suma = i = 0; i < n; ++i) upd(suma,(LL)phi[i+1] * F[i] % P); cout << (LL)suma * temp % P << '\n';
//	cerr<<clock()<<'\n'; 
	return 0;
}
```

---

## 作者：strcmp (赞：0)

**题目大意：** 给定 $n$ 和非负整数可重集 $a$。求 $\sum{\varphi(\sum\limits_{b \subseteq a \wedge \forall b_i,\,b_j,\,b_i \text{and} b_j = 0} b + 1)}$。其中 $\text{and}$ 代表二进制意义下的位与。

------------

合法的子序列中任意两数的 $\text{and}$ 为零，代表每一位上都只有有一个子序列中的数，满足这一位是 $1$。

对合法子序列中的所有数求和，不会产生任何进位，所以子序列和 $\le 2^{18}$。同理，我们可以将求和看作求位或。

我们可以直接暴力枚举所有可能的和。

设 $f_i$ 表示和为 $i$ 时有多少合法子序列。

考虑 $f_i$ 必然是由 $j < i$ 且 $j$ 是 $i$ 的子集的 $f_j$ 转移过来。

设 $a$ 中值为 $i$ 的数有 $c_i$ 个，则 $f_i \leftarrow f_i + f_{i \backslash j} \times c_j$。

零可以任意选择，最终答案要乘上 $2^{c_0}$。

对于时间复杂度，显然对于 $i$，枚举其子集的复杂度是 $2^{\text{popcnt}(i)}$ 级别的，所以当 $n$ 位的二进制位中有 $i$ 个 $1$ 的时候，对时间复杂度的贡献是 $\binom{n}{i} \times 2^i$。$\sum_{i = 0}^{n}\binom{n}{i} \times 2^i = (2 + 1)^n = 3^n$。

时间复杂度 $\Theta(3^{\log_2({\max\{a\}})})$，大概是 $3^{18}$ 级别的，可以稳过。

注意到转移式很像子集卷积的式子，但不会，等学会了再补吧。

```cpp
#include <bits/stdc++.h>
#define re register
using namespace std;
typedef long long int ll;
const int maxn = 1e6 + 10;
const ll mod = 1000000007LL;
const ll inf = 1145141919810LL;
ll f[maxn], a[maxn]; int n;
int vis[maxn], p = 0; ll pri[maxn], phi[maxn];
void init() {
	for (int i = 2; i <= (1 << 18) + 1; i++) {
		if (!vis[i]) pri[++p] = i, phi[i] = i - 1;
		for (int j = 1; i * pri[j] <= (1 << 18) + 1; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) { phi[i * pri[j]] = phi[i] * pri[j]; break; }
			else phi[i * pri[j]] = phi[i] * (pri[j] - 1);
		}
	}
}
ll cnt[maxn];
int main() {
	scanf("%d", &n); init();
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), ++cnt[a[i]]; f[0] = 1;
	for (int i = 1; i < (1 << 18); i++) {
		for (re int j = i; j; j = (j - 1) & i) {
			if (j < (i ^ j)) break;
			f[i] = f[i] + f[i ^ j] * cnt[j];
		}
		f[i] %= mod;
		//if (f[i]) cout << i << " " << f[i] << "\n";
	}
	ll ans = 1;
	for (int i = 1; i < (1 << 18); i++) ans = (ans + f[i] * phi[i + 1] % mod) % mod;
	while (cnt[0]--) ans = (ans << 1) % mod;
	printf("%lld\n", ans);
	return 0;
}
```

---

