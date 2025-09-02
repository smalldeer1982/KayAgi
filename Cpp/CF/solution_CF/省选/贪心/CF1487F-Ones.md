# Ones

## 题目描述

You are given a positive (greater than zero) integer $ n $ .

You have to represent $ n $ as the sum of integers (possibly negative) consisting only of ones (digits '1'). For example, $ 24 = 11 + 11 + 1 + 1 $ and $ 102 = 111 - 11 + 1 + 1 $ .

Among all possible representations, you have to find the one that uses the minimum number of ones in total.

## 样例 #1

### 输入

```
24```

### 输出

```
6```

## 样例 #2

### 输入

```
102```

### 输出

```
7```

# 题解

## 作者：18Michael (赞：12)

## 题意

给定一个正整数 $n$，要求用只由 $1$ 组成的数字的和或差表示 $n$，且使用 $1$ 个数最少。

例如，$24 = 11 + 11 + 1 + 1$，$102 = 111 - 11 + 1 + 1$ 是两种使用 $1$ 个数最少的方案。

## 解法

题目等价于用只由 $1$ 组成的数字来抵消 $n$，最终使 $n$ 变为 $0$。注意到 $n$ 的范围只有 $50$ 位，不难想到用一个朴素的 DP 来解决。

设 $n$ 有 $l$ 位，最高位为第 $1$ 位，最低位为第 $l$ 位，则在第 $i$ 位时想要 $-1$ 或 $+1$，第 $i+1 \sim l$ 位也都要相应地 $-1$ 或 $+1$。

同时，在第 $i$ 位上的变化不可能既有 $-1$ 又有 $+1$，因此我们可以记录第 $i$ 位的变化是 $-1$ 还是 $+1$。

记 $f[pos][c][x][delta(0/1)]$ 表示当前从高位往低位考虑到第 $pos$ 位，前 $pos$ 位还未抵消的和为 $c$，后 $l-pos$ 位都要减去一个数 $x$，当前变化是 $delta$（$-1$ 或 $+1$）时最少要用的 $1$ 的个数。

那么，$f[pos][c][x][delta]=min(f[pos][c][x+(delta? 1:-1)][delta]+l-pos,f[pos+1][c*10+ch[pos+1]-'0'-x][x][1],f[pos+1][c*10+ch[pos+1]-'0'-x][x][0]))$。

- 由 $f[pos][c][x+(delta? 1:-1)][delta]+l-pos$ 转移来是保持当前位 $pos$ 和变化量 $delta$ 不变，在第 $pos$ 位之后全加上 $delta$。

- 由 $f[pos+1][c*10+ch[pos+1]-'0'-x][x][1]$ 和 $f[pos+1][c*10+ch[pos+1]-'0'-x][x][0]$ 转移来是让当前位 $pos$ 后移一位，枚举变化量 $delta$。

同时，我们可以确定 $c$ 和 $x$ 的上下界。

由于在第 $i$ 位时加 $6$ 个 $1$ 要 $6 \times (l-i+1)$ 个 $1$，而在第 $i-1$ 位加 $1$ 个 $1$，在第 $i$ 位减 $4$ 个 $1$，再在第 $l$ 位减 $1$ 个 $1$ 要 $5 \times (l-i)+2$ 个 $1$，效果相同且前者用的 $1$ 一定比后者多，故没有位上用的 $1$ 会大于等于 $6$ 个。

我们需要在 $l$ 位的基础上再往前考虑 $1$ 位，因此每位用的 $1$ 不超过 $5 \times (l+1)$，即 $x \le 5 \times (l+1)$。

再由转移方程知 $c \times 10-x \le \dfrac{5 \times \sum_{i=1}^{l} \underbrace{1 \cdots 1}_{i}}{10^{l-1}} \le \dfrac{500}{81}$，故 $c \le \dfrac{x}{10}+1$。

用记忆化 DP 即可。

## Code
```
#include<cstdio>
#include<cstring>
#define inf 0x7f7f7f7f
int l,Test_num,mxc,mxx;
char ch[53];
int f[53][53][511][2];
inline int min(int a,int b)
{
	return a<b? a:b;
}
inline int dp(int pos,int c,int x,int delta)
{
	if(pos==l)return c? inf:0;if(c>mxc || c<-mxc || x>mxx || x<-mxx)return inf;
	if(!(~f[pos][c+mxc][x+mxx][(delta==1)]))f[pos][c+mxc][x+mxx][(delta==1)]=min(dp(pos,c,x+delta,delta)+l-pos,min(dp(pos+1,c*10+ch[pos+1]-x,x,1),dp(pos+1,c*10+ch[pos+1]-x,x,-1)));
	return f[pos][c+mxc][x+mxx][(delta==1)];
}
int main()
{
	scanf("%s",ch+2),l=strlen(ch+2)+1,ch[1]=0,mxx=5*l,mxc=mxx/10+1;
	for(int i=2;i<=l;++i)ch[i]^=48;
	memset(f,-1,sizeof(f)),printf("%d",dp(0,0,0,1));
	return 0;
}
```



---

## 作者：Rhodoks (赞：5)

这是一个和出题人标解不太一样的做法，并且好像复杂度更优？


令$m_i=111...1$($i$位)，$|n|$是$n$的位数.此问题可以理解成：让$x=x+m_i/ x-m_i$花费$i$的代价，令$x=0$花费最小的代价。

记$dp_{y,x}$代表你加减完所有$m_i (i > y)$并且当前值为$x$的最小代价. 使用```map/unordered_map```和高精度整数来实现$dp_y$. 初始时$dp_{|n|+1,n}=0$

对每个状态$x$在$dp_{y}$中，对$dp_{y-1}$的转移只有两种选择。 不妨设$x$非负那么可能的转移只有$x-km_y$和$x-(k+1)m_y$，此处$x-km_y$非负而$x-(k+1)m_y$为负。即在做完$m_y$的加减之后必然有$|x|<m_y$，其他情况均不优，证明如下：

每个$m_y$都不应该被使用超过$10$次(实际上这个界很松，可以继续下放),否则你总是可以把$10m_y$($10y$个$1$)变成$m_{y+1}-m_1$($y+2$个$1$).如果$|x| \geq m_y$而不使用$m_y$来减少它, 考虑到$\sum_{i=1}^{y-1} 9m_i < \sum_{i=1}^{y-1}10^{i+1} = m_y$, 必然存在$m_i(i<y)$被使用超过$10$次否则你无法将$x$归零。此时必然存在更优解。


回到正题，看上去状态数最多能到$2^{50}$但实际上最多只有$O(|n|)$个，证明如下：


我断言对$dp_y$的所有状态$x$所有$x \mod m_{y}$的值恰好只落在一个长度为$O(|n|)$的区间$[a,b]$. (鉴于是模意义下，$[a,m_{y}-1] \cup [0,b]$也认为是一个区间）

初始时刻$x$只有一种可能，显然是满足的。

既然对$x\pm km_{y}$不影响$x \mod m_{y}$,那么对$dp_{y-1}$的状态$x$，所有$x \mod m_{y}$也落在$[a,b]$.

又因为如我们之前所说$dp_{y-1}$的状态$x$都是满足$|x|<m_y$, 这意味着$x$的可能取值范围只有两个区间的并：$[a-m_y,b-m_y] \cup [a,b]$. 

注意到$a-m_y=a-10m_{y-1}-1\equiv a-1 (\mod m_{y-1})$. 所以$x \mod m_{y-1}$的范围实际上就是$[a-1,b-1] \cup [a,b] =[a-1,b]$, 比$[a,b]$长度只增大了$1$.所以可以得出结论$[a,b]$的长度是$O(|n|)$的.既然如此$x$的可能取值范围$[a-m_y,b-m_y] \cup [a,b]$也只有$O(|n|)$个数。

那么我们的算法也就出来了，从$|x|+1$到$1$枚举$y$($O(|n|)$次), 枚举$dp_y$里的状态$x$并且更新$dp_{y-1}$ (最多$O(|n|)$个), 高精度运算$O(|n|)$和```map```复杂度$O(log|n|)$,总的时间复杂度是$O(|n|^3log|n|)$.


[my code](https://codeforces.com/contest/1487/submission/107625296)

---

## 作者：Jayun (赞：2)

## 题目大意

记 $m_i=\underbrace{1\cdots1}_{i\text{ times}}$，即十进制下 $i$ 个连续的 $1$。

现在给定一个正整数 $n$，找到一个无限长的整数序列 $(x_1,x_2,\cdots)$ 满足：

1. $\sum_{i=1}^\infty m_ix_i=n$。
1. 最小化 $\sum_{i=1}^\infty i|x_i|$。

$n\leq10^{50}.$

## 思路

本题是 [CCPC 2020 Final Number Theory](https://qoj.ac/problem/2835) 弱化版。加强版的范围 $n\leq10^{5000}$。因为我的优化**过不了**加强版，而且我还为此花费了两天时间，所以我要为这道题送上我最**儒雅**的**赞叹**。本篇以 $|n|$ 表示 $n$ 的长度。

令 $f_{y,x}$ 表示加减所有 $m_i(i>y)$ 剩下 $x$ 的最小代价。

对于 $f_{y,x}$ 中的每一个 $x$，在转移至下一位中至多有两种选择：假设 $x$
为非负的，这两种选择为 $x-km_y$ 和 $x-(k+1)m_y$，其中 $x-km_y$ 非负，$x-(k+1)m_y$ 非正。否则 $|x-km_y|>m_y$ 总可以减掉（加上）一个 $m_y$ 使得代价更小。

可以证明从 $f_y$ 转移到 $f_{y-1}$ 最多创造 $\mathcal{O}(1)$ 个多出来的 $x$，则共有 $\mathcal{O}(|n|)$ 个不同的 $x$。这样可以得到 $\mathcal{O}(|n|^3\log|n|)$ 的复杂度。

考虑优化掉高精度运算的 $\mathcal{O}(|n|)$：把数字都乘上 $9$，则 $m_i=\underbrace{9\cdots9}_{i\text{ times}}=1\underbrace{0\cdots0}_{i\text{ times}}-1$。那么每次高精度运算只用加减两位，修改位数是均摊 $\mathcal{O}(1)$ 的。

直接这么做还有一个问题：由于 $x-km_y<m_y$，则计算 $x-(k+1)m_y$ 就不是 $\mathcal{O}(1)$ 的了。

发现 $m_i\bmod m_{i-1} = 1$，可以以此引出一条性质：在 $i > 2$ 层中，由 $x$ 以正负划分可以组成两组连续的数列（如果不乘 $9$），乘上 $9$ 则是两个公差为 $9$ 的等差数列。如下（未乘 $9$）：

```text
           3453                 i=1
   120            -991          i=2
9      -102     8     -103      i=3
9 -2   -3  8   8 -3   -4 7      i=4
```

那么我们随便取一个数 $x$，$\mathcal{O}(|n|)$ 算 $m_y-x$，然后用哈希存储。

这样我们消掉了高精度运算的 $\mathcal{O}(|n|)$，总时间复杂度是 $\mathcal{O}(|n|^2\log|n|)$……吗？并不。注意到 `map` 在 $\log|n|$ 以外，比较两数大小也需要 $|n|$，因此时间复杂度还是 $\mathcal{O}(|n|^3\log|n|)$。似乎用 `pb_ds` 也只能简单消掉一个 $\log|n|$。接下来的超出我的能力了……

## 我的代码

```cpp
const int N = 5010;

inline ll Read() {
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

namespace Main {
	char s[N];
	int n;

	struct Number {
		public:
		vector<int> v;

		Number() {}
		Number(int x) {
			for (; x--; v.push_back(0));
			v.push_back(1);
		}

		void CharToNumber(char *s) {
			int len = strlen(s);
			for (int i = 0; i < len; i++)
				v.push_back(s[i] - '0');
			reverse(v.begin(), v.end());
		}
		
		int& operator[](int x) { return v[x]; }
		int length () { return v.size(); }
	};

	bool operator< (Number a, Number b) {
		if (a.length() != b.length()) return a.length() < b.length();
		for (int i = a.length() - 1; i >= 0; i--)
			if (a[i] != b[i]) return a[i] < b[i];
		return 0;
	}
	Number operator+ (Number a, Number b) {
		if (b < a) swap(a, b);
		for (int i = 0; i < a.length() || (i < b.length() && b[i] > 9); i++) {
			if (i < a.length()) b[i] += a[i];
			if (b[i] > 9) {
				if (i + 1 < b.length()) b[i + 1] += b[i] / 10;
				else b.v.push_back(b[i] / 10);
				b[i] %= 10;
			}
		}
		return b;
	}
	Number operator- (Number a,Number b) {
		if (b < a) swap(a, b);
		for (int i = 0; i < b.length(); i++) {
			if (i < a.length()) b[i] -= a[i];
			if (b[i] < 0) {
				b[i] += 10;
				b[i + 1]--;
			}
		}
		for (int i = b.length() - 1; i >= 1; i--)
			if (b[i] == 0) b.v.resize(i);
			else break;
		return b;
	}
	Number PlusInt (Number a, int x = 1) {
		a[0] += x;
		for (int j = 0; a[j] >= 10; j++) {
			if (j + 1 >= a.length()) a.v.push_back(a[j] / 10);
			else a[j + 1] += a[j] / 10;
			a[j] %= 10; 
		}
		return a;
	}
	Number MinusBit (Number a, int x, int val = 1) {
		a[x] -= val;
		for (int j = x; a[j] < 0; j++) {
			a[j] += 10, a[j + 1]--;
		}
		for (int i = a.length() - 1; i >= 1; i--)
			if (a[i] == 0) a.v.resize(i);
			else break;
		return a;
	}

	map<Number, int> f[N];

	int main () {
		for (int t = 1; t--; ) {
			for (int i = 0; i <= 5000 + 1; i++) f[i].clear();
			scanf ("%s", s);
			Number n, m;
			n.CharToNumber(s);
			m = n;
			for (int i = 1; i <= 8; i++) n = n + m;
			f[n.length() + 1][n] = 0;
			for (int i = n.length() + 1; i; i--) {
				map<Number, Number> hash;
				auto fir = *f[i].begin();
				Number key = fir.first;
				Number antiKey;
				if (key.length() == 0) key.v.push_back(0);
				while (PlusInt(key).length() >= i + 1) {
					key = PlusInt(key);
					key = MinusBit(key, i);
				}
			
				antiKey = Number(i) - PlusInt(key);
			
				if (!(key.length() == 1 && key[0] == 0)) {
					key = MinusBit(key, 0, 9);
					antiKey = PlusInt(antiKey, 9);
				}
				hash[key] = antiKey;
				hash[antiKey] = key;

				Number tmp1 = key, tmp2 = antiKey;
				for (int j = 0; j <= f[i].size() / 2 && !(antiKey.length() == 1 && antiKey[0] == 0); j++) {
					key = PlusInt(key, 9);
					antiKey = MinusBit(antiKey, 0, 9);
					if (hash.find(key) != hash.end()) break;
					hash[key] = antiKey;
					hash[antiKey] = key;
				}
				key = tmp1, antiKey = tmp2;
				for (int j = 0; j <= f[i].size() / 2 && !(key.length() == 1 && key[0] == 0); j++) {
					antiKey = PlusInt(antiKey, 9);
					key = MinusBit(key, 0, 9);
					if (hash.find(key) != hash.end()) break;
					hash[key] = antiKey;
					hash[antiKey] = key;
				}

				for (auto u: f[i]) {
					Number tmp = u.first;
					int val = u.second;
					while (PlusInt(tmp).length() >= i + 1) {
						tmp = PlusInt(tmp);
						tmp = MinusBit(tmp, i);
						val += i;
					}
					if (f[i - 1].find(tmp) == f[i - 1].end()) f[i - 1][tmp] = val;
					else f[i - 1][tmp] = min(f[i - 1][tmp], val);
					tmp = hash[tmp];
					if (f[i - 1].find(tmp) == f[i - 1].end()) f[i - 1][tmp] = val + i;
					else f[i - 1][tmp] = min(f[i - 1][tmp], val + i);
				}
			}
			Number Zero;
			Zero.CharToNumber((char*)"0");
			printf ("%d\n", f[0][Zero]);
		}
		return 0;
	}
}

int main () {
//	freopen("ones.in", "r", stdin);
//	freopen("ones.out", "w", stdout);
	Main::main();
	return 0;
}
```

## 加强版满分代码


[MoQZ 莫队的代码](https://www.luogu.com.cn/paste/2jgpljv7)

---

## 作者：OrientDragon (赞：1)

# 序言
老师上课讲完这道题，感觉正解思路确乎非常人之所能及也。

看了看题解区，有一个四维 dp，别的好像都要用到高精度。

其实没有那么复杂/kk。
# 题意
记 $\displaystyle M(i)=\sum_{k=0}^{i-1}10^k=\overbrace{11\cdots1}^{k 个 1}$，例如 $M(3)=111,M(2)=11$。找到最小的 $x$ 使得存在一种 $\displaystyle \sum_{\sum k=x} M(k)=t$，其中 $t$ 为给定正整数。
# 解法
最开始容易想到一般的贪心策略：从高位开始凑数，但有显然的反例。

> 反例 $\text{e.g.}\quad 77\xlongequal{贪心}7\times M(2)\xlongequal{最优}M(3)-3\times M(2)-M(1)$。

由于 $t\leq 10^{50}$，超过了一般的数据范围，所以这道题基本锁定数位 dp。那么不妨将 $t$ 分解为 $\overline{t_{l}t_{l-1}\cdots t_1}$，其中 $t$ 是 $l$ 位整数。

通过上面的反例，我们得到一条结论：

> 若最优解为 $\displaystyle t=\sum_{i=1}^{l+1} k_iM(i)$，则 $|k_1|\leq 6,\forall i>1,|k_i|\leq5$。特别地，$k_{l+1} \in\{0,1\}$。

下面给出证明。

> 对于 $66$ 这个数，发现 $6M(2)$ 和 $M(3)-4M(2)-M(1)$ 对应的 $x$ 相等（$x=12$）。
>
> 更一般地，$n>1$ 时，考虑 $6M(n)$，发现其对应的 $x$ 大于等于 $M(n+1)-4M(n)-M(1)$ 对应的 $x$（$6n\geq5n+2$）。
>
> 所以对于 $kM(n)\text{ s.t. }6\leq k \leq 9,n>1$ ，第二种拆法总不劣于第一种：因为 $kn \geq (k-1)n+2$。当且仅当 $n=1$ 时，存在 $|k_1|=6$ 的情况。
>
> $k_{l+1} \in\{0,1\}$ 的正确性是显然的。

反向发现原问题等价为：给 $t$ 加（减）去若干个 $M(k)$，使其变为 $0$。结合上述结论，可以想到一种 dp 状态如下。

设 $dp_{i,S,j}$ 表示满足以下 $3$ 个条件时，最小的 $x$：

+ 已经考虑完了 $M(l)$ 到 $M(l-i+1)$。特殊地，当 $i=0$ 时，没有考虑过任何操作。
+ $|\overline{t_lt_{l-1}\cdots t_{l-i+1}}-\overline{f_lf_{l-1}\cdots f_{l-i+1}}| = S$，其中 $f$ 为当前前缀。
+ 对于 $f_{l-i}$ 到 $f_1$ 的每个数有 $j$ 的贡献。

举例说明：$t=24$ 时，$dp_{1,0,2}\xlongequal{2M(2)}4$。dp 中 $1$ 表示从左往右考虑完了 $1$ 位，$0$ 表示这一位上 $|t_2-f_2|=0$，$2$ 表示对于之后的每一位（$f_1$）产生了 $2$ 个贡献，其实指代的就是 $11+11=22$。

一个显然的边界：$dp_{l+1,0,\cdots}=0$。可以理解为，从 $t$ 上加（减）去 $0$ 个 $M$ 就可以变成 $t$。由此，得到我们的转移方程：

$\displaystyle dp_{i,S,j}=\min_{-6\leq k\leq 6}\{dp_{i+1,10S+j+k-t_i,j+k}\times|k|(l-i+1)\}$

关于转移方程的解释如下。

> 枚举 $M(l-i+1)$ 的系数 $k$，表示加（减）了 $|k|$ 次 $M(l-i+1)$（实质上这个上限可以压缩到 $|k|\leq5$，但需要特判 $i=l$ 时的特殊情况）。
>
> 考虑与 $dp_{i+1}$ 之间的联系。由于 $dp_i$ 考虑的是从高到低前 $i$ 位的 $f$ 与 $t$ 的差记为 $S$，那么 $dp_i$ 考虑的是从高到低前 $i+1$ 位的 $f$ 与 $t$ 的差 $10S+j+k-t_i$。$10S$ 表示前 $i$ 位的差左移一位，$j+k-t_i$ 表示的是第 $i+1$ 位数字的差。
>
> 最后，$dp_i$ 需要在 $dp_{i+1}$ 的花费上加上 $M(l-i+1)$ 的花费。

比较容易混淆的是 $dp_i$ 实际上统计的是 $\displaystyle \sum_{k\leq l-i+1} M(k)$ 的最小花费。

那么答案就比较明确了：$dp_{0,0,0}$ 统计了 $\displaystyle \sum_{k\leq l+1} M(k)$ 的最小花费，也就是最终答案。
# 优化
我们分析时间复杂度应该是 $\mathcal O(\max\{i\times S\times j\})$，其中 $i\leq l,|j|\leq 6l$。但是 $S$ 就有点不对了，如果不做处理的话必然超时。

我们思考：当 $S$ 为多少时，对答案一定没有贡献？也就是说，无论之后的转移加（减）了多少，都不可能让 $t$ 归零。根据转移方程，有

$10S-j \leq \dfrac{5 \times \sum_{i=1}^{l} \overbrace{11 \cdots 1}^{i 个 1}}{10^{l-1}} < 5$。然后有 $S\leq \dfrac{j}{10}+1$。

此时时间复杂度是 $\mathcal O(l^3)$ 加上亿点常数（？），实质上可以卡过 $l\leq 100$ 的情况。
# 代码
记忆化 dp。

注意：$dp_{i,S,j}$ 的下标可能为负，需要让下标偏移一段距离。

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

int l,mx_S,mx_j;
char t[55];
// 这里空间可以开大点，但必须满足需求 
int dp[105][105][1005];

int dfs(int i,int S,int j){
	if(i==l+1)return S?inf:0; // 递归边界
	if(abs(S)>mx_S||abs(j)>mx_j)return inf; // 超出有意义范围
	int &ret=dp[i][S+mx_S][j+mx_j]; // 引用，方便修改
	if(~ret)return ret;
	ret=inf;
	for(int k=-6;k<=6;k++)
		ret=min(ret,dfs(i+1,10*S+j+k-t[i],j+k)+(k>0?k:-k)*(l-i+1));
	return ret;
}

int main(){
	memset(dp,-1,sizeof dp);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	t[0]='0';
	cin>>(t+1);
	l=strlen(t+1);
	for(int i=0;i<=l;i++)
		t[i]^=48; // 转数字
	mx_j=5*(l+1)+1,mx_S=mx_j/10+1; // 有意义范围 
	cout<<dfs(0,0,0);
}
```

---

