# Timofey and remoduling

## 题目描述

Little Timofey likes integers a lot. Unfortunately, he is very young and can't work with very big integers, so he does all the operations modulo his favorite prime $ m $ . Also, Timofey likes to look for arithmetical progressions everywhere.

One of his birthday presents was a sequence of distinct integers $ a_{1},a_{2},...,a_{n} $ . Timofey wants to know whether he can rearrange the elements of the sequence so that is will be an arithmetical progression modulo $ m $ , or not.

Arithmetical progression modulo $ m $ of length $ n $ with first element $ x $ and difference $ d $ is sequence of integers $ x,x+d,x+2d,...,x+(n-1)·d $ , each taken modulo $ m $ .

## 样例 #1

### 输入

```
17 5
0 2 4 13 15
```

### 输出

```
13 2
```

## 样例 #2

### 输入

```
17 5
0 2 4 13 14
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5 3
1 2 3
```

### 输出

```
3 4
```

# 题解

## 作者：LXl491214 (赞：5)

## **题目大意**

给出一个长度为$n$的元素两两不同的序列和一个质数$m$。若该序列是由一个等差数列在模$m$意义下打乱而得到的，请尝试求出原数列的首项和公差。若可能的原数列不唯一，请随便输出一个可行数列的首项和公差；若序列不是由任何一个等差数列变换而来的，请输出```-1```。

对于$100\%$的数据，$2 \leq m \leq 10^9+7$，$1 \leq n \leq 10^5$，$0 \leq 序列中的每一个数<m$。

要求输出的两个数在$[0,m)$之间。

## **分析**

这道题目不考什么困难的算法，但是考脑洞。

首先，考虑$2n \leq m$的情况。记变换前的数列为$s,s+d,s+2d, \cdots ,s+(n-1)d$，并设$x$为变换前的数列中某两个元素（记为$a,b$，且$a<b$）的差，于是我们有$x \equiv b-a \pmod m$。记$a$在变换前的数列中的位置为$i$，$b$在变换前的数列中的位置为 $i+k$，则有$x \equiv dk \pmod m$。当$2n \leq m$时，变换后的序列中一定有$(n-k+1)$对数的差为$x$。于是我们可以借助二分查找找出变换后的序列中差为$x$的数对的数量，并由此算出$k$的值。因为$x \equiv dk \pmod m$，所以$d \equiv \dfrac{x}{k} \pmod m$；又因为$m$为质数，所以我们可以用费马小定理（$a^{p-1} \equiv 1 \pmod p$，其中$p$为质数，且$\gcd(a,p)=1$）算出$d$。

知道$d$后，我们遍历变换后的序列以寻找合适的$s$。当我们发现对于序列中的某个数$t$满足$(t-d+m) \mod m$不在序列中，那么它就可能是$s$。但是当我们发现序列中有不止一个数满足时，我们可以确定这个序列不是由任何一个等差数列变换而来的（一个数列的开头只有一个）。

但是，当$2n>m$时，情况不一样了。因为差最大的两组数是$s,s+(n-1)d$以及$s,s+(n-2)d$，它们的差之和为$(2n-3)d$。如果$2n-3 \geq m$，那么就会存在两个差，它们的和模$m$为$0$，就会多统计；但是当$2n \leq m$时却不会。这时，我们算出变换后的序列在$\{ x \in Z|0 \leq x<m \}$中的补集，并用上述的方法求出补集所对的变换前的等差数列，再将$s$加上$(m-n) \mod d$。因为补集的大小$n'=m-n<m-\dfrac{m}{2}$，所以有$2n'<m$，可以使用上述的方法，同时，因为只要$m$与$d$互质，补集所对的原数列就可以为$s+nd,s+(n+1)d,s+(n+2)d, \cdots ,s+(m-1)d$，那么该序列与补集上得到的原数列可以有同样的公差。

## **代码**

根据思路，可以写出如下代码：

```c++
#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
char buf[16777216];
inline ll Read() //快速读入
{
	static char* c = buf;
	while (*c > '9' || *c < '0')
	{
		++c;
	}
	ll ans = *c ^ 48ll;
	while (*(++c) >= '0' && *c <= '9')
	{
		ans = (ans * 10) + (*c ^ 48ll);
	}
	return ans;
}
ll a[200002], b[200002];
inline bool Find(const ll val) //二分查找给定数值是否在a中
{
	ll l = 1, r = a[0];
	while (l < r)
	{
		const ll mid = (l + r) >> 1;
		if (a[mid] < val)
		{
			l = mid + 1;
		}
		else
		{
			r = mid;
		}
	}
	return a[r] == val;
}
int main()
{
	fread(buf, 1, 16777216, stdin); //读入所有输入
	const ll m = Read(), n = Read(); //读入n和m
	if(n == 1) //特判当n=1时的答案
	{
		printf("%lld 0", Read());
		return 0;
	}
	if(n == m) //特判当n=m时的答案
	{
		putchar('0');
		putchar(' ');
		putchar('1');
		return 0;
	}
	for (ll i = 1; i <= n; ++i) //读入变换后的序列
	{
		a[i] = Read();
	}
	sort(a + 1, a + (n + 1)); //对序列排序
	a[0] = n;
	const bool mode = (n * 2 > m);
	if (mode) //当2n>m时
	{
		for (ll i = 0; i < m; ++i) //计算补集
		{
			if (!Find(i))
			{
				b[++b[0]] = i;
			}
		}
		for (ll i = 0; i <= b[0]; ++i)
		{
			a[i] = b[i];
		}
	}
	ll start, d;
	if (a[0] == 1) //特判序列长度为1的情况
	{
		start = a[1];
		d = 1;
	}
	else
	{
		d = a[2] - a[1]; //寻找x
		ll cnt = 0;
		for (ll i = 1; i <= a[0]; ++i) //统计变换后的序列中差为x的数对的数量
		{
			if (Find((a[i] + d) % m))
			{
				++cnt;
			}
		}
		for (ll t1 = (a[0] - cnt) % m, t2 = m - 2; t2 >= 1; d = ((t2 & 1) == 1 ? d * t1 % m : d), t1 = t1 * t1 % m, t2 >>= 1); //计算d
		start = -1;
		for (ll t = m - d, i = 1; i <= a[0]; ++i) //寻找s
		{
			if (!Find((a[i] + t) % m)) //找到可能的s
			{
				if (start != -1) //如果有多个可能的s
				{
					start = -1; //无解
					break;
				}
				start = a[i]; //保存s
			}
		}
	}
	if (mode && start != -1) //当2n>m时
	{
		start = (start + d * b[0]) % m; //改变s
	}
	printf((start == -1 ? "-1" : "%lld %lld"), start, d); //输出答案
	return 0;
}
```

## **总结**

这道题虽然对算法的难度要求不高，但对思维的要求很高。做对这道题需要很好的思维。

---

## 作者：zcz0263 (赞：2)

## 题意

给出一个 $n$ 和一个质数 $m$，以及一个长度为 $n$，互不相同的 $a$ 序列，求是否存在一种 $a$ 的排列方式使得 $a$ 是一个 $\bmod\ m$ 意义下的等差数列。如果存在，输出任意一组可能的首项 $x$ 及公差 $d$，否则输出 $-1$。

## 做法

下文假设 $n\not=m$ 且 $n\not=1$。记 $p_i$ 表示 $a_i$ 在对应等差数列的项数，$f_i$ 表示对应未取模等差数列的第 $i$ 项，即 $f_i=x+(i-1)d$。

令 $t=a_2-a_1,k=p_2-p_1$，可以看出 $t\equiv k\times d\pmod m$。

因为 $k$ 是多少跟后续处理没太大关系，考虑求出 $k$ 并解出公差。  
如果这个等差数列不取模，易得其中满足 $a_i-a_j=k\times d$ 的 $(i,j)$ 对数恰为 $n-k$ 个，因为这个条件等价于 $(i,j)$ 在等差数列中相距 $k$ 个位置，直接统计即可得到 $k$；但是因为已知的是取模后的序列，所以需要考虑一下什么时候结果会不一样：  
存在 $i$ 使得 $p_i\le k$（即未取模时不存在对应的 $j$ 使得 $a_j=a_i-k\times d$），并且存在正整数 $z\le n-p_i$ 使得 $a_i-k\times d\equiv f_{z+p_i}\pmod m$（即存在一个只是和对应值同余却不相等的数），又因为 $d\perp m$，所以 $z$ 如果存在，那么一定唯一。  
所以出现错误的必要不充分条件是存在一组 $(i,z)$ 使得 $a_i-k\times d\equiv f_{z+p_i}\pmod m$，把式子变形一下：

$$
\begin{aligned}
a_i-k\times d&\equiv f_{z+p_i}&\pmod m\\
a_i-k\times d&\equiv a_i+z\times d&\pmod m\\
-k\times d&\equiv z\times d&\pmod m\\
-k&\equiv z&\pmod m\\
z+k&\equiv0&\pmod m\\
m&\mid(z+k)
\end{aligned}
$$

因为 $0\le z,k\le n-1$，所以当 $m>2n-2$ 的时候，可以直接使用相同的方法求 $k$。

考虑 $m\le 2n-2$ 的时候怎么做：

注意到 $f$ 在模意义下有周期性，即：  
对于 $1\le i<j\le m$，

$$
\begin{aligned}
i\times d&\not\equiv j\times d&\pmod m\\
x+i\times d&\not\equiv x+j\times d&\pmod m\\
f_i&\not\equiv f_j&\pmod m
\end{aligned}
$$

对于 $1\le i\le m$，

$$
\begin{aligned}
i\times d&\equiv i\times d&\pmod m\\
x+i\times d&\equiv x+(m+i)d&\pmod m\\
f_i&\equiv f_{m+i}&\pmod m
\end{aligned}
$$

这表明 $f_1\sim f_m$ 在模意义下是一个 $0\sim m-1$ 的排列，并且 $f$ 中所有相邻值连起来形成一个环，环上每个连续段都是合法的。注意到 $a$ 的合法性与 $a$ 相对于 $[0,m)$ 的补集的合法性相同，而取补集之后的序列长度 $n^\prime=m-n$，考虑它和 $m$ 的大小关系：

$$
\begin{aligned}
m&\le2n-2\\
m-2n+2&\le0\\
2(m-n)+2&\le m\\
2n^\prime+2&\le m\\
2n^\prime-2&<m
\end{aligned}
$$

满足前文中直接统计方法的正确条件，可以直接按照补集处理套回去求 $k$。

根据已知的 $k$ 和 $k\times d$，可以直接求出 $d$，然后找到唯一的一个 $i$ 使得 $a$ 中不存在 $(a_i-d+m)\mod m$，因为这和前文求 $k$ 部分的方式形式是一样的，所以若 $a$ 有解，满足条件的 $i$ 一定唯一，以它为首项即可。如果前面过程中取了补集，真正的首项只需要加一个 $d\times n^\prime$，公差不变。

---

## 作者：Mr_Wu (赞：2)

有一个很无脑的做法...

由 $\sum_{i=0}^{n-1} (x+di)\equiv \sum_{i=0}^{n-1} a_i$ 得 $nx+\frac{n(n-1)}{2}d\equiv \sum_{i=0}^{n-1} a_i$，在排除 $n=m$ 的边界情况后得到 $x+\frac{n(n-1)}{2}d\equiv \frac{\sum_{i=0}^{n-1} a_i}{n}$。

由 $\sum_{0\le i<j\le n-1} ((x+di)-(x+dj))^2\equiv \sum_{1\le i<j\le n} (a_i-a_j)^2$ 得 $d^2\frac{(n-1)n^2(n+1)}{12}\equiv \sum_{1\le i<j\le n} (a_i-a_j)^2$。

易知 $n\le m$。$n=m,n=m-1$ 的情况都容易解决。当这两者都不成立时容易发现 $(n-1)n^2(n+1)$ 存在逆元，所以可以得到 $d^2$ 模 $m$ 的值，用 Cipolla 算法求出 $d$ 可能的值（至多两个），再依次验证。时间复杂度 $O(\log p+n\log n)$

---

