# 「MCOI-Zero / AC6-M07」Selumna Peak

## 题目背景

「Now that's what I call squadron！」

「Come on, it's payback time.」

**「Gracemeria is dead ahead！！」**

$$_{{\frac{\large\text{ACE COMBAT }\Large6}{\tiny{\text{F i r e s\quad O f\quad L i b e r a t i o n}}}}}\\ \text{Mission 07} \\\Large\text{Selumna Peak}\\\tiny-\textit{ Shimmering Death }-$$

![](https://cdn.luogu.com.cn/upload/image_hosting/owa6qtg4.png)

## 题目描述

给定 $1\sim n$ 的排列 $a_{[1,n]}$。

请对于每一个 $i$，考虑如下操作序列：

1. 首先在 $[1,i]$ 中选取一个子序列（可以为空）；
2. 然后将这个子序列内的数重新排列。

求出 **所有不同的操作序列产生的排列** 的逆序对数总和是多少，答案模 $20051131$。

两个操作序列不同当且仅当选取的子序列不同或重新排列的方式不同。

操作不会真正被执行到排列上。

## 说明/提示

样例 1 解释：

- 对于 $[1,1]$，无法产生逆序对，答案为 $0$。
- 对于 $[1,2]$，只有一种操作序列可以产生 $2,1,3$，答案为 $1$。
- 对于 $[1,3]$：
	- 有 $8$ 种操作序列产生 $1,2,3$；
   - 有 $2$ 种操作序列产生 $1,3,2$；
   - 有 $2$ 种操作序列产生 $2,1,3$；
   - 有 $1$ 种操作序列产生 $2,3,1$；
   - 有 $1$ 种操作序列产生 $3,1,2$；
   - 有 $2$ 种操作序列产生 $3,2,1$；
- 答案为 $0\times 8+1\times 2+1\times 2+2\times 1+2\times 1+2\times 3=14$。

样例 2 解释：

- 对于 $i=1$，只有两种操作序列，产生的排列都有 $8$ 个逆序对，故答案是 $16$。
- 对于 $i=2$，有 $4$ 种操作序列产生 $3, 2, 4, 1, 6, 8, 7, 5$，有 $1$ 种操作序列产生 $2,3,4,1,6,8,7,5$，答案为 $8\times 4+7\times 1=39$。

数据范围：

- Subtask 1（10%）：$n\leq 8$。
- Subtask 2（20%）：$n\leq 50$。
- Subtask 3（20%）：$n\leq 300$。
- Subtask 4（20%）：$n\leq 3\times 10^3$。
- Subtask 5（30%）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n\leq 10^6$。

idea：Sol1，solution：Sol1，code：Sol1，data：Sol1

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
0
1
14```

## 样例 #2

### 输入

```
8
3 2 4 1 6 8 7 5```

### 输出

```
16
39
132
476
2842
21137
172002
1427424```

# 题解

## 作者：Sol1 (赞：3)

upd. 把那个大公式改得稍微好看一点…要不然太长了

---

~~idea 为原题改编~~

设 $I$ 为全局逆序对数量，以及：

$$\begin{cases}f(n)=\sum_{i=0}^n[n]_i\\g(n)=\sum_{i=0}^n(i+1)[n]_i\\h(n)=\sum_{i=0}^n(i+1)^2[n]_i\end{cases}$$

其中 $f,g,h$ 均有线性递推式：

$$\begin{cases}f(n)=1+nf(n-1)\\g(n)=1+n[g(n-1)+f(n-1)]\\h(n)=1+n[h(n-1)+2g(n-1)+f(n-1)]\end{cases}$$

对于 $i<j\leq n$，考虑在哪些方案中 $a_i$ 和 $a_j$ 会被交换。

情况 $1$：子序列中同时出现 $i,j$，且重新排列之后 $j$ 换到 $i$ 前面。

考虑枚举子序列长度，得到方案数为：

$$\begin{aligned}&\sum_{k=0}^{n-2}\binom{n-2}{k}\cdot \dfrac{(k+2)!}{2}\\=&\sum_{k=0}^{n-2}\dfrac{(n-2)!}{k!(n-2-k)!}\cdot\dfrac{k!\cdot(k+1)\cdot(k+2)}{2}\\=&\sum_{k=0}^{n-2}\dfrac{(k+1)\cdot(k+2)}{2}[n-2]_k\\=&\dfrac{g(n-2)+h(n-2)}{2}\end{aligned}$$

情况 $2$：$i$ 在子序列里面，$j$ 不在子序列里面，重新排列后 $i$ 被放到了 $j$ 后面。

考虑枚举有几个子序列的元素出现在 $j$ 前面，以及有几个出现在 $j$ 后面。

得到下式：

$$\sum_{k=1}^{n-j}\sum_{l=0}^{j-2}\binom{n-j}{k}\binom{j-2}{l}k(k+l)!$$

拆定义式变形：

$$\sum_{k=1}^{n-j}\sum_{l=0}^{j-2}\dfrac{(n-j)!}{k!(n-j-k)!}\cdot\dfrac{(j-2)!}{l!(j-l-2)!}\cdot k(k+l)!$$

提出 $n-j$，约去 $k$：

$$(n-j)\sum_{k=1}^{n-j}\sum_{l=0}^{j-2}\dfrac{(n-j-1)!}{(k-1)!(n-j-k)!}\cdot\dfrac{(j-2)!}{l!(j-l-2)!}\cdot (k+l)!$$

组合数定义式变形：

$$(n-j)\sum_{k=0}^{n-j-1}\sum_{l=0}^{j-2}\binom{n-j-1}{k}\binom{j-2}{l}(k+l+1)!$$

调换枚举顺序（先枚举 $k+l$）：

$$(n-j)\sum_{k=0}^{n-3}(k+1)!\sum_{l=0}^{j-2}\dbinom{n-j-1}{k-l}\dbinom{j-2}{l}$$

沃德你蒙德恒等式变形：

$$(n-j)\sum_{k=0}^{n-3}(k+1)!\dbinom{n-3}{k}$$

拆定义式变形：

$$(n-j)\sum_{k=0}^{n-3}(k+1)[n-3]_k$$

代入预设函数：

$$(n-j)g(n-3)$$

情况 $3$：$j$ 在子序列里面，$i$ 不在子序列里面，重新排列后 $j$ 被放到了 $i$ 前面。

类似情况 $2$ 可以得到情况数为 $(i-1)g(n-3)$

全部合起来再加上全局逆序对的贡献就得到区间 $[1,n]$ 的答案式：

$$\text{Ans}(1,n)=f(n)\cdot I-\sum_{i=1}^n\sum_{j=i+1}^n \operatorname{sgn}(a_i-a_j)\cdot\left[\dfrac{h(n-2)+g(n-2)}{2}+(i-1+n-j)g(n-3)\right]$$

预处理 $f,g,h$，树状数组即可。

复杂度 $O(n\log n)$。

---

## 作者：5ab_juruo (赞：2)

给一种简单一点的推法。

定义 $F_k$ 为只选取 $[1,k]$ 的子序列进行操作的方案数。显然：

$$
F_k=\sum\limits_{c=0}^k \binom{k}{c}c!
$$

考虑算每一对 $(a_i,a_j)$ 对 $k$ 位置答案的贡献。若初始 $a_i>a_j$，则先给答案加上 $F_k$，并将下面所有的贡献取反。下面的计算默认 $i<j\le k$。

考虑选择的子序列包含 $a_i,a_j$ 的情况：

- 包含了 $a_i$ 和 $a_j$

对于任何一个子序列的所有重排列，必然有一半 $a_i$ 在 $a_j$ 前，另一半相反。对答案的额外贡献即为：

$$
\frac{1}{2}\sum_{c=2}^k \binom{k-2}{c-2}c!
$$

- 包含了 $a_i$ 或 $a_j$ 中的恰好一个

以选中 $a_j$ 为例。要对答案产生贡献，必然要把 $a_j$ 换到 $a_{j'}$ 且 $j'<i<j$。则先考虑钦定 $j'$ 再确定其余的排列，即：

$$
(i-1)\sum_{c=1}^{k-2}\binom{k-3}{c-1}c!
$$

直接做可能会有 $\mathcal{O}(n^3)$ 甚至 $\mathcal{O}(n^4)$ 的复杂度。

---

定义 $I_k$ 为前 $k$ 个元素的逆序对个数，且令：

$$
\begin{aligned}
G_k&=\sum_{c=1}^k \binom{k-1}{c-1}c!\\
H_k&=\sum_{c=2}^k \binom{k-2}{c-2}c!
\end{aligned}
$$

~~OEIS~~ 平凡推导可得：

$$
\begin{aligned}
F_k&=kF_{k-1}+1\\
G_k&=F_k-F_{k-1}\\
H_k&=G_k-G_{k-1}
\end{aligned}
$$

前两类贡献的和可以直接计算：

$$
F_kI_n+\frac{1}{2}H_k\left(\frac{l(l-1)}{2}-2I_k\right)
$$

第三类贡献无法直接计算，还需要维护当前前缀的所有数对较大位置的下标和，BIT 维护是平凡的。复杂度 $\mathcal{O}(n\log n)$。

```cpp
typedef long long ll;
const int max_n = 1000000, mod = 20051131;

int p[max_n], prec[max_n], n;
mint fac[max_n + 1], ifac[max_n + 1], F[max_n + 1], G[max_n + 1], H[max_n + 1];
ll pinvc[max_n + 1], tr[max_n + 1];

void initfac(int _lim)
{
	fac[0] = 1;
	for (int i = 0; i < _lim; i++)
		fac[i + 1] = fac[i] * (i + 1);
	ifac[_lim] = fac[_lim].inv();
	for (int i = _lim; i > 0; i--)
		ifac[i - 1] = ifac[i] * i;
}

int lowbit(int x) { return x & -x; }
void add(int x, int v)
{
	for (x++; x <= n; x += lowbit(x))
		tr[x] += v;
}
ll get(int x)
{
	ll ret = 0;
	for (x++; x; x -= lowbit(x))
		ret += tr[x];
	return ret;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> p[i], p[i]--;
	initfac(n);
	
	F[0] = 1;
	for (int i = 1; i <= n; i++)
		F[i] = F[i - 1] * i + 1;
	adjacent_difference(F, F + n + 1, G), G[0] = 0;
	adjacent_difference(G, G + n + 1, H), H[0] = H[1] = 0;
	
	pinvc[0] = 0;
	for (int i = 0; i < n; i++)
	{
		int res = get(p[i]);
		prec[i] = res;
		pinvc[i + 1] = i - res + pinvc[i];
		add(p[i], 1);
	}
	
	fill(tr, tr + n + 1, 0);
	mint cpc = 0;
	for (int l = 1; l <= n; l++)
	{
		mint ans = pinvc[n] * F[l] + (1ll * l * (l - 1) / 2 - 2 * pinvc[l]) * H[l] / 2;
		cpc += 1ll * (l - 1) * prec[l - 1] + 1ll * (l - 2) * (l - 1) / 2 - get(p[l - 1]);
		ans += (l <= 2 ? 0 : G[l - 2]) * ((l - 1) * (1ll * l * (l - 1) - 2 * pinvc[l]) - 2 * cpc);
		cout << ans << "\n";
		add(p[l - 1], l - 1);
	}
	
	return 0;
}
```

---

