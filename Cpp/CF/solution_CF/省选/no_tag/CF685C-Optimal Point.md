# Optimal Point

## 题目描述

给定一个立体直角坐标系上的$n$个整点，求一个整点满足到这$n$个整点的曼哈顿距离的最大值最小。

## 样例 #1

### 输入

```
1
5
0 0 4
0 0 -4
0 4 0
4 0 0
1 1 1
```

### 输出

```
0 0 0
```

## 样例 #2

### 输入

```
2
1
3 5 9
2
3 5 9
3 5 9
```

### 输出

```
3 5 9
3 5 9
```

# 题解

## 作者：约瑟夫用脑玩 (赞：12)

这篇题解是用来质疑其他题解~~的智商~~为什么没有用 $O(n+\log{W})$ 的，并且所有题解的判断都这么拉胯。

首先二分答案为 $dis$，设答案点为 $(x,y,z)$，然后就有 $n$ 组约束条件 $|x-x_i|+|y-y_i|+|z-z_i| \leq dis$

直接暴力拆开绝对值可以得到：

$\begin{cases}x+y+z-x_i-y_i-z_i \leq dis \\ x+y-z-x_i-y_i+z_i \leq dis \\ x-y+z-x_i+y_i-z_i \leq dis \\ x-y-z-x_i+y_i+z_i \leq dis \\ -x+y+z+x_i-y_i-z_i \leq dis \\ -x+y-z+x_i-y_i+z_i \leq dis \\ -x-y+z+x_i+y_i-z_i \leq dis \\ -x-y-z+x_i+y_i+z_i \leq dis\end{cases}$

移项就可以得到：

$\begin{cases} \max(-dis+x_i+y_i+z_i) \leq x+y+z \leq \min(-dis+x_i+y_i+z_i) \\ \max(-dis-x_i+y_i+z_i) \leq -x+y+z \leq \min(-dis-x_i+y_i+z_i) \\ \max(-dis+x_i-y_i+z_i) \leq x-y+z \leq \min(-dis+x_i-y_i+z_i) \\ \max(-dis+x_i+y_i-z_i) \leq x+y-z \leq \min(-dis+x_i+y_i-z_i)\end{cases} $

这里有个显而易见的事实是：

$\begin{cases}\max(-dis+x_i+y_i+z_i)=-dis+\max(x_i+y_i+z_i)\\\max(-dis-x_i+y_i+z_i)=-dis+\max(-x_i+y_i+z_i)\\\max(-dis+x_i-y_i+z_i)=-dis+\max(x_i-y_i+z_i)\\\max(-dis+x_i+y_i-z_i)=-dis+\max(x_i+y_i-z_i)\end{cases} $
 

$\begin{cases}\min(-dis+x_i+y_i+z_i)=-dis+\min(x_i+y_i+z_i)\\\min(-dis-x_i+y_i+z_i)=-dis+\min(-x_i+y_i+z_i)\\\min(-dis+x_i-y_i+z_i)=-dis+\min(x_i-y_i+z_i)\\\min(-dis+x_i+y_i-z_i)=-dis+\min(x_i+y_i-z_i)\end{cases} $

显然每个 $-dis+\max/\min{\text{?}}$ 后面的东西是可以提前预处理的，也就是说其实这四个不等式只与 $dis$ 有关。

设：

$\begin{cases}l_1=-mid+\max(x_i+y_i+z_i)\\l_2=-mid+\max(-x_i+y_i+z_i)\\l_3=-mid+\max(x_i-y_i+z_i)\\l_4=-mid+\max(x_i+y_i-z_i)\end{cases} $

$\begin{cases}r_1=-mid+\min(x_i+y_i+z_i)\\r_2=-mid+\min(-x_i+y_i+z_i)\\r_3=-mid+\min(x_i-y_i+z_i)\\r_4=-mid+\min(x_i+y_i-z_i)\end{cases} $

则：

$\begin{cases} l_1 \leq x+y+z \leq r_1 \\ l_2 \leq -x+y+z \leq r_2 \\ l_3 \leq x-y+z \leq r_3 \\ l_4 \leq x+y-z \leq r_4\end{cases} $

那么我们每次判断只用 $O(1)$ 的解一个不等式组即可。

解这个不等式组还得有点技巧，首先是一个小奥就能看出来的换元，令 $a=-x+y+z,b=x-y+z,c=x+y-z$，则：

$\begin{cases}x=\frac{b+c}{2}\\y=\frac{a+c}{2}\\z=\frac{a+b}{2}\\x+y+z=a+b+c\end{cases} $

故：

$\begin{cases}l_1\leq a+b+c\leq r_1\\l_2\leq a\leq r_2\\l_3\leq b\leq r_3\\l_4\leq c\leq r_4\end{cases}$

然后是 $a,b,c$ 奇偶性相同，因为 $x,y,z$ 均为整数，令 $f=a\&1$，再令：

$\begin{cases}a'=\frac{a-f}{2} \\ b'=\frac{b-f}{2} \\ c'=\frac{c-f}{2}\end{cases} $

$\begin{cases}l_1'=\lceil\frac{l_1-3f}{2}\rceil \\ l_2'=\lceil\frac{l_2-f}{2}\rceil \\ l_3'=\lceil\frac{l_3-f}{2}\rceil \\ r_1'=\lceil\frac{r_1-3f}{2}\rceil \\ r_2'=\lceil\frac{r_2-f}{2}\rceil \\ r_3'=\lceil\frac{r_3-f}{2}\rceil \\ \end{cases} $

自然得到：

$\begin{cases}l_1' \leq a'+b'+c' \leq r_1' \\ l_2' \leq a' \leq r_2'\\ l_3' \leq b' \leq r_3' \\ l_4' \leq c' \leq r_4'\end{cases}$

这个东西我们并不需要每次判断求解，我们只用判断合法即可，于是判断以下两个不等式：

$\begin{cases}l_2'+l_3'+l_4' \leq r_1' \\ r_2'+r_3'+r_4' \geq l_1'\end{cases}$

最后得到了 $dis$ 的值后再来求解 $a,b,c$ 即可，具体的，先取最小，然后逐个增大即可。

**复杂度 $\color{red}O(n+\log{W})$。**

我反正是没想到为什么题解区一片拉胯，都用的 $O(n\log{W})$ 且每次判断都要构造一次解，就算常数没人要，复杂度也不管管？

---

## 作者：xht (赞：11)

> [CF685C Optimal Point](https://codeforces.com/contest/685/problem/C)

## 题意

- 立体直角坐标系中有 $n$ 个整点。
- 求一个整点满足到这 $n$ 个整点的曼哈顿距离的最大值最小。
- $n \le 10^5$。

## 题解

显然先二分答案。

考虑如何 check，假设此时二分到的值为 $d$。

则我们可以得到 $n$ 个限制 $|x - x_i| + |y - y_i| + |z - z_i| \le d$。

不妨设 $x_i = y_i = z_i = 0$，我们考虑 $|x| + |y| + |z| \le d$ 的情况。

枚举每个绝对值取正取负，我们可以列出 $2^3 = 8$ 个不等式。

合并这 $8n$ 个不等式，最终会得到一个不等式组：

$$\begin{cases}l \leq x+y+z \leq r \\lx \leq-x+y+z \leq rx \\ly \leq x-y+z \leq ry \\lz \leq x+y-z \leq rz\end{cases}$$

设 $a=-x+y+z$，$b=x-y+z$，$c=x+y-z$，则 $x=\frac{b+c}{2}$，$y=\frac{a+c}{2}$，$z=\frac{a+b}{2}$，且 $x+y+z = a+b+c$，且 $a,b,c$ 奇偶性相同。

令 $a = 2a^{\prime} + r$，$b = 2b^{\prime} + r$，$c = 2c^{\prime} + r$，其中 $r \in [0,1]$，则我们最终得到的不等式组为：

$$\begin{cases}l^{\prime} \leq a^{\prime}+b^{\prime}+c^{\prime} \leq r^{\prime} \\lx^{\prime} \leq a^{\prime} \leq rx^{\prime} \\ly^{\prime} \leq b^{\prime} \leq ry^{\prime} \\lz^{\prime} \leq c^{\prime} \leq rz^{\prime}\end{cases}$$

我们要求出这个不等式组的一组解。

先贪心的设 $a^{\prime} = lx^{\prime}$，$b^{\prime} = ly^{\prime}$，$c^{\prime} = lz^{\prime}$，若不满足 $l^{\prime} \leq a^{\prime}+b^{\prime}+c^{\prime} \leq r^{\prime}$，则一个一个调大 $a^{\prime}, b^{\prime}, c^{\prime}$。

这样我们就可以 $\mathcal O(n)$ check 并构造了，时间复杂度 $\mathcal O(n \log w)$。

说句题外话，代码不太会写，偷偷看一眼兔兔的，发现他偷偷看了题解代码（

## 代码

```cpp
const int N = 1e5 + 7;
const ll inf = 4e18;
#define Max(a, b) (a = a > b ? a : b)
#define Min(a, b) (a = a < b ? a : b)
int n;
ll x[N], y[N], z[N], X, Y, Z, mx, mxx, mxy, mxz, mn, mnx, mny, mnz;

inline bool pd(ll o) {
	mx = mxx = mxy = mxz = inf, mn = mnx = mny = mnz = -inf;
	for (int i = 1; i <= n; i++)
		Min(mx, o + x[i] + y[i] + z[i]),
		Min(mxx, o - x[i] + y[i] + z[i]),
		Min(mxy, o + x[i] - y[i] + z[i]),
		Min(mxz, o + x[i] + y[i] - z[i]),
		Max(mn, -o + x[i] + y[i] + z[i]),
		Max(mnx, -o - x[i] + y[i] + z[i]),
		Max(mny, -o + x[i] - y[i] + z[i]),
		Max(mnz, -o + x[i] + y[i] - z[i]);
	for (int i = 0; i < 2; i++) {
		ll l = mn + ((mn & 1) ^ i), r = mx - ((mx & 1) ^ i);
		ll lx = mnx + ((mnx & 1) ^ i), rx = mxx - ((mxx & 1) ^ i);
		ll ly = mny + ((mny & 1) ^ i), ry = mxy - ((mxy & 1) ^ i);
		ll lz = mnz + ((mnz & 1) ^ i), rz = mxz - ((mxz & 1) ^ i);
		if (l > r || lx > rx || ly > ry || lz > rz) continue;
		ll a = lx, b = ly, c = lz;
		if (a + b + c > r) continue;
		if (a + b + c < l) a = rx < l - b - c ? rx : l - b - c;
		if (a + b + c < l) b = ry < l - a - c ? ry : l - a - c;
		if (a + b + c < l) c = rz < l - a - b ? rz : l - a - b;
		if (a + b + c < l) continue;
		return X = (b + c) >> 1, Y = (a + c) >> 1, Z = (a + b) >> 1, 1;
	}
	return 0;
}

inline void solve() {
	rd(n);
	for (int i = 1; i <= n; i++) rd(x[i]), rd(y[i]), rd(z[i]);
	ll l = 0, r = inf;
	while (l <= r) {
		ll mid = (l + r) >> 1;
		if (pd(mid)) r = mid - 1;
		else l = mid + 1;
	}
	print(X, ' '), print(Y, ' '), print(Z);
}

int main() {
	int T;
	rd(T);
	while (T--) solve();
	return 0;
}
```

---

## 作者：chen_zhe (赞：11)

# CF685C Optimal Point

这个题，我看到的第一眼以为是个三分。因为 $x$ 轴固定一个位置，$y$ 轴固定一个位置，去扫 $z$ 轴，会发现距离是一个单峰的函数，对于 $x$ 轴和 $y$ 轴也类似处理，类似 [UVA10228](https://www.luogu.com.cn/problem/UVA10228) 的处理方式即可。那么我们得到了一个 $O(n \log^3 v)$ 的做法，而且是正确的。但是看一眼数据规模，$n=10^5,v=10^{18}$，会被卡掉，这就很令人不爽。

然后我们看一眼题意，它是要求距离的最大值最小，而最大值最小又可以提示我们这个题可能需要二分，那么我们就可以很显然地去二分这个最大距离 $dis$，然后就有 $n$ 组约束条件 $|x-x_i|+|y-y_i|+|z-z_i| \leq dis$

我们会发现这是个很不好处理的不等式关系组，因为有一堆变量，还套个绝对值。我们考虑拆绝对值，根据正负关系，应该会得到 $2^3=8$ 组不等式关系：

$\begin{cases}x+y+z-x_i-y_i-z_i \leq dis \\ x+y-z-x_i-y_i+z_i \leq dis \\ x-y+z-x_i+y_i-z_i \leq dis \\ x-y-z-x_i+y_i+z_i \leq dis \\ -x+y+z+x_i-y_i-z_i \leq dis \\ -x+y-z+x_i-y_i+z_i \leq dis \\ -x-y+z+x_i+y_i-z_i \leq dis \\ -x-y-z+x_i+y_i+z_i \leq dis\end{cases}$

看起来是组很恐怖的式子。考虑移项合并，则有：

$\begin{cases} l_1 \leq x+y+z \leq r_1 \\ l_2 \leq -x+y+z \leq r_2 \\ l_3 \leq x-y+z \leq r_3 \\ l_4 \leq x+y-z \leq r_4\end{cases}$

其中 $l_{1 \dots 4},r_{1 \dots 4}$ 在后续计算中可被视作常数，分别为：

$\begin{cases}l_1=\max(-mid+x_i+y_i+z_i)\\l_2=\max(-mid-x_i+y_i+z_i)\\l_3=\max(-mid+x_i-y_i+z_i)\\l_4=\max(-mid+x_i+y_i-z_i)\end{cases}$

$\begin{cases}r_1=\min(-mid+x_i+y_i+z_i)\\r_2=\min(-mid-x_i+y_i+z_i)\\r_3=\min(-mid+x_i-y_i+z_i)\\r_4=\min(-mid+x_i+y_i-z_i)\end{cases}$

这里的 $\max()$ 和 $\min()$ 其实本质上是给区间取交集。

我们考虑换元，令 $a=-x+y+z,b=x-y+z,c=x+y-z$，那么可以代换出

$\begin{cases}x=\frac{b+c}{2}\\y=\frac{a+c}{2}\\z=\frac{a+b}{2}\\x+y+z=a+b+c\end{cases}$

我们还会发现另外一点，就是 $a,b,c$ 的奇偶性是一致的，因为 $a,b,c$ 的奇偶性取决于 $x,y,z$ 的奇偶性，符号只是增加或者减少了两倍的 $x$ 或 $y$ 或 $z$，不影响对 $2$ 取模的余数。这也就告诉了我们，其实我们可以去枚举 $a \bmod 2$，这样可以再换元：

$\begin{cases}a'=\frac{a-a\bmod 2}{2} \\ b'=\frac{b-a\bmod 2}{2} \\ c'=\frac{c-a\bmod 2}{2}\end{cases}$

这样我们再带回第二个不等式组，则有：

$\begin{cases}l_1' \leq a'+b'+c' \leq r_1' \\ l_2' \leq a' \leq r_2'\\ l_3' \leq b' \leq r_3' \\ l_4' \leq c' \leq r_4'\end{cases}$

那么问题就在于如何求解这个不等式组了。其实也不要想得太复杂，因为我们只要求出一组解，所以可以考虑我们平时做数学题的策略：令 $a'=l_2',b'=l_3',c'=l_4'$，这样可以保证后三个不等式的约束，然后再看这个时候的 $a'+b'+c'$ 是否满足 $l_1' \leq a'+b'+c' \leq l_2'$，若满足就是一组解；

若不满足条件，而且 $a'+b'+c' < l_1'$，我们就可以考虑，在不超过后三组约束条件的同时，适当增加一下 $a',b',c'$ 的大小，也就是先加 $a'$，如果 $a'$ 被加到最大还不满足 $l_1'$，就去加 $b'$，以此类推即可。如果是 $a'+b'+c' > r_1'$ 那么就无解了。

最后的时间复杂度应该是 $O(n \log_2 v)$ 了，比开场的那个三分不知道快到哪里去了。注意一下 C++ 特色取模可能造成一些意想不到的诡异问题。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <queue>
#include <vector>

using namespace std;

inline long long read()
{
	long long x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int n;

long long x[100050],y[100050],z[100050],xans,yans,zans;

inline void Init()
{
	for (int i=1;i<=n;i++)
		x[i]=y[i]=z[i]=0;
	//memset(x,0,sizeof(x));
	//memset(y,0,sizeof(y));
	//memset(z,0,sizeof(z));
	xans=yans=zans=0;
}

inline bool check(long long mid)
{
	long long r1=4e18,r2=4e18,r3=4e18,r4=4e18;
	long long l1=-4e18,l2=-4e18,l3=-4e18,l4=-4e18;
	for (int i=1;i<=n;i++)
	{
		r1=min(r1,mid+x[i]+y[i]+z[i]);
		r2=min(r2,mid-x[i]+y[i]+z[i]);
		r3=min(r3,mid+x[i]-y[i]+z[i]);
		r4=min(r4,mid+x[i]+y[i]-z[i]);
		l1=max(l1,-mid+x[i]+y[i]+z[i]);
		l2=max(l2,-mid-x[i]+y[i]+z[i]);
		l3=max(l3,-mid+x[i]-y[i]+z[i]);
		l4=max(l4,-mid+x[i]+y[i]-z[i]);
	}
	for (int i=0;i<=1;i++)
	{
		long long l11=l1+((l1&1)^i);
		long long r11=r1-((r1&1)^i);
		long long l21=l2+((l2&1)^i);
		long long r21=r2-((r2&1)^i);
		long long l31=l3+((l3&1)^i);
		long long r31=r3-((r3&1)^i);
		long long l41=l4+((l4&1)^i);
		long long r41=r4-((r4&1)^i);
		if (l11<=r11 && l21<=r21 && l31<=r31 && l41<=r41)
		{
			long long a=l21;
			long long b=l31;
			long long c=l41;
			if (a+b+c<=r11)
			{
				if (a+b+c<l11)
				{
					if (r21<l11-b-c)
						a=r21;
					else
						a=l11-b-c;
				}
				if (a+b+c<l11)
				{
					if (r31<l11-a-c)
						b=r31;
					else
						b=l11-a-c;
				}
				if (a+b+c<l11)
				{
					if (r41<l11-a-b)
						c=r41;
					else
						c=l11-a-b;
				}
				if (a+b+c>=l11)
				{
					xans=(b+c)>>1;
					yans=(a+c)>>1;
					zans=(a+b)>>1;
					return 1;
				}
			}
		}
	}
	return 0;
}

int main()
{
	int T=read();
	while (T--)
	{
		n=read();
		Init();
		for (int i=1;i<=n;i++)
		{
			x[i]=read();
			y[i]=read();
			z[i]=read();
		}
		if (n==1)
		{
			cout << x[1] << " " << y[1] << " " << z[1] << endl;
			continue;
		}
		long long left=0,right=4e18;
		while (left<=right)
		{
			long long mid=(left+right)>>1; 
			if (check(mid))
				right=mid-1;
			else
				left=mid+1;
		}
		cout << xans << " " << yans << " " << zans << endl;
	}
	return 0;
}

```



---

## 作者：duyi (赞：7)

# CF685C Optimal Point

## 题目大意

[题目链接](https://codeforces.com/contest/685/problem/C)

给出三维空间里的 $n$ 个点。求一个坐标是整数的点，最小化它到 $n$ 个点的曼哈顿距离的最大值。

$1\leq n\leq 10^5$，坐标的绝对值 $\leq 10^{18}$。

## 本题题解

最小化最大值，容易想到二分答案。设当前需要判断的答案为 $d$，即判断是否存在一个点 $(x,y,z)$，使得它到 $n$ 个点的曼哈顿距离都 $\leq d$。形式化地写为：
$$
\forall i: |x_i - x| + |y_i - y| + |z_i - z| \leq d
$$
$|p|\leq q$，可以等价于 $p\leq q$ 且 $-p\leq q$。因为负数对这个判断没有影响。于是可以把绝对值拆开。则每个条件变成 $2^3 = 8$ 个条件：
$$
\begin{cases}
x_i - x + y_i - y + z_i - z \leq d\\
x_i - x + y_i - y + z - z_i \leq d\\
x_i - x + y - y_i + z_i - z \leq d\\
x_i - x + y - y_i + z - z_i \leq d\\
x - x_i + y_i - y + z_i - z \leq d\\
x - x_i + y_i - y + z - z_i \leq d\\
x - x_i + y - y_i + z_i - z \leq d\\
x - x_i + y - y_i + z - z_i \leq d
\end{cases}
$$
我们关心的是 $(x,y,z)$，所以整理一下：
$$
\begin{cases}
-x - y - z \leq d - x_i - y_i - z_i\\
-x - y + z \leq d - x_i - y_i + z_i\\
-x + y - z \leq d - x_i + y_i - z_i\\
-x + y + z \leq d - x_i + y_i + z_i\\
x - y - z \leq d + x_i - y_i - z_i\\
x - y + z \leq d + x_i - y_i + z_i\\
x + y - z \leq d + x_i + y_i - z_i\\
x + y + z \leq d + x_i + y_i + z_i\\
\end{cases}
$$
进一步整理得：
$$
\begin{cases}
-d + x_i + y_i + z_i\leq x + y + z \leq d + x_i + y_i + z_i\\
-d - x_i + y_i + z_i \leq -x + y + z\leq d - x_i + y_i + z_i\\
-d + x_i - y_i + z_i \leq x - y + z \leq d + x_i - y_i + z_i\\
-d + x_i + y_i - z_i \leq x + y - z \leq d + x_i + y_i - z_i
\end{cases}
$$
设：
$$
l_1 = \max_{i = 1}^{n}(-d + x_i + y_i + z_i)\\
l_2 = \max_{i = 1}^{n}(-d - x_i + y_i + z_i)\\
l_3 = \max_{i = 1}^{n}(-d + x_i - y_i + z_i)\\
l_4 = \max_{i = 1}^{n}(-d + x_i + y_i - z_i)\\
r_1 = \min_{i = 1}^{n}(d + x_i + y_i + z_i)\\
r_2 = \min_{i = 1}^{n}(d - x_i + y_i + z_i)\\
r_3 = \min_{i = 1}^{n}(d + x_i - y_i + z_i)\\
r_4 = \min_{i = 1}^{n}(d + x_i + y_i - z_i)
$$
$l_1,l_2,l_3,l_4,r_1,r_2,r_3,r_4$ 都可以看做常数。上述 $\min, \max$ 的本质是对 $n$ 个条件求交。

于是条件可以改写成：
$$
\begin{cases}
l_1 \leq x + y + z \leq r_1\\
l_2 \leq -x + y + z \leq r_2\\
l_3 \leq x - y + z \leq r_3\\
l_4 \leq x + y - z \leq r_4
\end{cases}
$$
换元。设 $a = -x + y + z$，$b = x - y + z$，$c = x + y - z$。则 $a + b + c = x + y + z$。

因为 $a + b = (-x + y + z) + (x - y + z) = 2z$，所以 $a,b$ 奇偶性相同。同理可知 $a,b,c$ **奇偶性都相同**。

知道一组 $a,b,c$ 后，我们可以通过 $x = \frac{b + c}{2}$, $y = \frac{a + c}{2}$, $z = \frac{a + b}{2}$，求出其对应的 $x,y,z$。于是问题从判断是否存在 $(x,y,z)$，转化为判断是否存在整数三元组 $(a,b,c)$，使其满足如下条件：
$$
\begin{cases}
l_1 \leq a + b + c \leq r_1\\
l_2 \leq a \leq r_2\\
l_3 \leq b \leq r_3\\
l_4 \leq c \leq r_4\\
a\equiv b\equiv c \pmod{2} 
\end{cases}
$$
设 $a',b',c'$，满足：
$$
a = 2a' + t\\
b = 2b' + t\\
c = 2c' + t
$$
其中 $t \in\{0,1\}$，是我们可以任取的。不妨枚举 $t$。那么再设：
$$
l_1' = \lceil\frac{l_1 - 3t}{2}\rceil,\  r_1' = \lfloor\frac{r_1 - 3t}{2}\rfloor\\
l_2' = \lceil\frac{l_2 - t}{2}\rceil,\ r_2' = \lfloor\frac{r_2 - t}{2}\rfloor\\
l_3' = \lceil\frac{l_3 - t}{2}\rceil,\ r_3' = \lfloor\frac{r_3 - t}{2}\rfloor\\
l_4' = \lceil\frac{l_4 - t}{2}\rceil,\ r_4' = \lfloor\frac{r_4 - t}{2}\rfloor
$$
注意，对负数来说，这里的上、下取整，是真的取更大、更小的数，而不是 $\texttt{C++}$ 中默认的向 $0$ 取整。

则问题转化为，判断是否存在整数三元组 $(a',b', c')$，满足：
$$
\begin{cases}
l_1'\leq a' + b' + c'\leq r_1'\\
l_2'\leq a' \leq r_2'\\
l_3'\leq b' \leq r_3'\\
l_4'\leq c' \leq r_4'
\end{cases}
$$
用取先极值，再调整的方法。可以发现条件等价于：
$$
\begin{cases}
l_1'\leq r_1'\\
l_2'\leq r_2'\\
l_3'\leq r_3'\\
l_4'\leq r_4'\\
l_2' + l_3' + l_4'\leq r_1'\\
r_2' + r_3' + r_4'\geq l_1'
\end{cases}
$$
直接判断即可。

单次判断的时间复杂度 $\mathcal{O}(n)$。因为还要二分答案，所以总时间复杂度 $\mathcal{O}(n\log \text{ans})$。

参考代码：

```cpp
// problem: CF685C
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

/* --------------- fast io --------------- */ // begin
namespace Fread {
const int SIZE = 1 << 21;
char buf[SIZE], *S, *T;
inline char getchar() {
	if (S == T) {
		T = (S = buf) + fread(buf, 1, SIZE, stdin);
		if (S == T) return '\n';
	}
	return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 21;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
	fwrite(buf, 1, S - buf, stdout);
	S = buf;
}
inline void putchar(char c) {
	*S++ = c;
	if (S == T) flush();
}
struct NTR {
	~ NTR() { flush(); }
} ztr;
} // namespace Fwrite
#ifdef ONLINE_JUDGE
	#define getchar Fread :: getchar
	#define putchar Fwrite :: putchar
#endif
namespace Fastio {
struct Reader {
	template<typename T>
	Reader& operator >> (T& x) {
		char c = getchar();
		T f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		x = 0;
		while (c >= '0' && c <= '9') {
			x = x * 10 + (c - '0');
			c = getchar();
		}
		x *= f;
		return *this;
	}
	Reader& operator >> (char& c) {
		c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		return *this;
	}
	Reader& operator >> (char* str) {
		int len = 0;
		char c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		while (c != '\n' && c != ' ') {
			str[len++] = c;
			c = getchar();
		}
		str[len] = '\0';
		return *this;
	}
	Reader(){}
} cin;
const char endl = '\n';
struct Writer {
	template<typename T>
	Writer& operator << (T x) {
		if (x == 0) { putchar('0'); return *this; }
		if (x < 0) { putchar('-'); x = -x; }
		static int sta[45];
		int top = 0;
		while (x) { sta[++top] = x % 10; x /= 10; }
		while (top) { putchar(sta[top] + '0'); --top; }
		return *this;
	}
	Writer& operator << (char c) {
		putchar(c);
		return *this;
	}
	Writer& operator << (char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer& operator << (const char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer(){}
} cout;
} // namespace Fastio
#define cin Fastio :: cin
#define cout Fastio :: cout
#define endl Fastio :: endl
/* --------------- fast io --------------- */ // end

const int MAXN = 1e5;
const ll MAX_ANS = 3e18;
const ll LL_INF = 9e18;

int n;
struct Point {
	ll x, y, z;
} p[MAXN + 5];

ll c(ll x) {
	// ceil(x / 2)
	
	if (x >= 0) {
		return (x + 1) / 2;
	} else {
		return -((-x) / 2);
	}
}
ll f (ll x) {
	// floor(x / 2)
	
	if (x >= 0) {
		return x / 2;
	} else {
		return -((-x + 1) / 2);
	}
}

Point ans;
bool check(ll d, bool _calc_ans = false) {
	ll l1 = -LL_INF, l2 = -LL_INF, l3 = -LL_INF, l4 = -LL_INF;
	ll r1 = LL_INF, r2 = LL_INF, r3 = LL_INF, r4 = LL_INF;
	for (int i = 1; i <= n; ++i) {
		ckmax(l1, -d + p[i].x + p[i].y + p[i].z);
		ckmax(l2, -d - p[i].x + p[i].y + p[i].z);
		ckmax(l3, -d + p[i].x - p[i].y + p[i].z);
		ckmax(l4, -d + p[i].x + p[i].y - p[i].z);
		ckmin(r1, d + p[i].x + p[i].y + p[i].z);
		ckmin(r2, d - p[i].x + p[i].y + p[i].z);
		ckmin(r3, d + p[i].x - p[i].y + p[i].z);
		ckmin(r4, d + p[i].x + p[i].y - p[i].z);
	}
	for (int t = 0; t <= 1; ++t) {
		ll _l1 = c(l1 - 3 * t), _r1 = f(r1 - 3 * t);
		ll _l2 = c(l2 - t), _r2 = f(r2 - t);
		ll _l3 = c(l3 - t), _r3 = f(r3 - t);
		ll _l4 = c(l4 - t), _r4 = f(r4 - t);
		
		if (_l1 <= _r1 && _l2 <= _r2 && _l3 <= _r3 && _l4 <= _r4 && _l2 + _l3 + _l4 <= _r1 && _r2 + _r3 + _r4 >= _l1) {
			if (!_calc_ans) {
				return true;
			}
			
			ll _a = _l2;
			ll _b = _l3;
			ll _c = _l4;
			
			ll rest = max(0LL, _l1 - (_l2 + _l3 + _l4));
			ll add;
			add = min(rest, _r2 - _l2);
			_a += add, rest -= add;
			add = min(rest, _r3 - _l3);
			_b += add, rest -= add;
			add = min(rest, _r4 - _l4);
			_c += add, rest -= add;
			assert(rest == 0);
			
			ll a = _a * 2 + t;
			ll b = _b * 2 + t;
			ll c = _c * 2 + t;
			
			assert(l1 <= a + b + c); assert(a + b + c <= r1);
			assert(l2 <= a); assert(a <= r2);
			assert(l3 <= b); assert(b <= r3);
			assert(l4 <= c); assert(c <= r4);
			
			ans.x = (b + c) / 2;
			ans.y = (a + c) / 2;
			ans.z = (a + b) / 2;
			
			return true;
		}
		
	}
	return false;
}

void solve_case() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i].x >> p[i].y >> p[i].z;
	}
	
	// for (int i = 0; i <= 10; ++i) cerr << check(i); cerr << endl;
	ll l = 0, r = LL_INF;
	while (l < r) {
		ll mid = (l + r) >> 1;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}
	cerr << l << endl;
	check(l, true);
	cout << ans.x << " " << ans.y << " " << ans.z << endl;
}
int main() {
	int T; cin >> T; while (T--) {
		solve_case();
	}
	return 0;
}
```





---

## 作者：Kinandra (赞：7)

[请在博客中查看](https://dra.blog.luogu.org/solution-cf685c)

标签: 二分答案.

这道题居然没有 xht 大神的题解?

容易想到二分答案, 考虑如何判断一个二分的值 $Ans$ 的可行性.

列出不等式组: 
$$\left\{\begin{aligned}
x+y+z-x_i-y_i-z_i\geqslant Ans\\
x+y-z-x_i-y_i+z_i\geqslant Ans\\
x-y+z-x_i+y_i-z_i\geqslant Ans\\
x-y-z-x_i+y_i+z_i\geqslant Ans\\
-x+y+z+x_i-y_i-z_i\geqslant Ans\\
-x+y-z+x_i-y_i+z_i\geqslant Ans\\
-x-y+z+x_i+y_i-z_i\geqslant Ans\\
-x-y-z+x_i+y_i+z_i\geqslant Ans\\
\end{aligned}\right.$$

移项后的到这样的形式: 
$$\left\{\begin{aligned}
x+y+z\in [l_0,r_0]\\
x+y-z\in [l_1,r_1]\\
x-y+z\in [l_2,r_2]\\
x-y-z\in [l_3,r_3]\\
\end{aligned}\right.$$

设 $a=x+y-z, b=x-y+z,c=x-y-z$ , 则 $a+b-c=x+y+z$ , 这里隐含了 $a\equiv b\equiv c\pmod 2$ , 于是我们枚举 $a\bmod 2$ , 那么不等式组可以转化成关于 $a,b,c$ 的不等式组, 这个不等式组很好解.

时间复杂度 $\mathcal O(n\log x)$.

实际实现中将 $c$ 设为 $-x+y+z$ .

```cpp
#include <bits/stdc++.h>
using namespace std;
long long read();

int T, n;
long long x[100005], y[100005], z[100005], l[4], r[4], L[4], R[4];
void chmax(long long &x, long long y) { x < y ? x = y : x; }
void chmin(long long &x, long long y) { x > y ? x = y : x; }

bool check(long long p, bool prt) {
    for (int i = 0; i < 4; ++i) l[i] = -6e18, r[i] = 6e18;
    for (int i = 1; i <= n; ++i) {
        chmin(r[0], x[i] + y[i] + z[i] + p);
        chmax(l[0], x[i] + y[i] + z[i] - p);
        chmin(r[1], -x[i] + y[i] + z[i] + p);
        chmax(l[1], -x[i] + y[i] + z[i] - p);
        chmin(r[2], x[i] - y[i] + z[i] + p);
        chmax(l[2], x[i] - y[i] + z[i] - p);
        chmin(r[3], x[i] + y[i] - z[i] + p);
        chmax(l[3], x[i] + y[i] - z[i] - p);
    }

    for (int i = 0; i < 4; ++i)
        if (l[i] > r[i]) return 0;
    for (int A = 0, flag; A < 2; ++A) {
        L[0] = l[0] - 3 * A, R[0] = r[0] - 3 * A;
        for (int i = 1; i < 4; ++i) L[i] = l[i] - A, R[i] = r[i] - A;
        for (int i = 0; i < 4; ++i) L[i] = L[i] + 1 >> 1, R[i] >>= 1;

        flag = 1;
        for (int i = 0; i < 4; ++i)
            if (L[i] > R[i]) {
                flag = 0;
                break;
            }
        if (!flag) continue;
        long long L0 = L[1] + L[2] + L[3], R0 = R[1] + R[2] + R[3];
        if (R[0] >= L0 && R0 >= L[0]) {
            if (prt) {
                long long a = L[1], b = L[2], c = L[3];
                if (a + b + c < L[0]) a += min(R[1] - L[1], L[0] - a - b - c);
                if (a + b + c < L[0]) b += min(R[2] - L[2], L[0] - a - b - c);
                if (a + b + c < L[0]) c += min(R[3] - L[3], L[0] - a - b - c);
                printf("%lld %lld %lld\n", b + c + A, a + c + A, a + b + A);
            }
            return 1;
        }
    }
    return 0;
}

int main() {
    T = read();
    while (T--) {
        n = read();
        for (int i = 1; i <= n; ++i)
            x[i] = read(), y[i] = read(), z[i] = read();
        long long l = 0, r = 6e18, rs = r, mid;
        while (l <= r)
            check(mid = l + r >> 1, 0) ? rs = mid, r = mid - 1 : l = mid + 1;
        check(rs, 1);
    }
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
long long read() {
    long long x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```



---

## 作者：whiteqwq (赞：5)

[CF685C Optimal Point](https://www.luogu.com.cn/problem/CF685C)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1807921)

## 题意

给定 $n$ 个立体三维坐标系的整点（坐标范围 $[-10^{18},10^{18}]$ ），求一个点使得其与所有点的曼哈顿距离最大值最小。（ $1\leqslant n\leqslant 10^5$ ）

## 分析

优美的胖题。

首先求最大值最小就可以知道要二分这个距离最大值。

考虑怎么 check 这个距离 $mid$ ，发现这等价于解这个方程组的解（其中 $x_0,y_0,z_0$ 为未知数）：

$$\begin{cases}|x_1-x_0|+|y_1-y_0|+|z_1-z_0|\leqslant mid\\|x_2-x_0|+|y_2-y_0|+|z_2-z_0|\leqslant mid\\\cdots\\|x_n-x_0|+|y_n-y_0|+|z_n-z_0|\leqslant mid\end{cases}$$

发现这个绝对值很难拆，但由于 $\max\{a-b,b-a\}=|a-b|$ ，所以每个不等式可以等价为：

$$\begin{cases}x_i-x_0+y_i-y_0+z_i-z_0\leqslant mid\\x_0-x_i+y_i-y_0+z_i-z_0\leqslant mid\\x_i-x_0+y_0-y_i+z_i-z_0\leqslant mid\\x_0-x_i+y_0-y_i+z_i-z_0\leqslant mid\\x_i-x_0+y_i-y_0+z_0-z_i\leqslant mid\\x_0-x_i+y_i-y_0+z_0-z_i\leqslant mid\\x_i-x_0+y_0-y_i+z_0-z_i\leqslant mid\\x_0-x_i+y_0-y_i+z_0-z_i\leqslant mid\end{cases}$$

然后不难发现这个不等式可以化作：

$$\begin{cases}x_i+y_i+z_i-mid\leqslant x_0+y_0+z_0\leqslant x_i+y_i+z_i+mid\\-x_i+y_i+z_i-mid\leqslant -x_0+y_0+z_0\leqslant -x_i+y_i+z_i+mid\\x_i-y_i+z_i-mid\leqslant x_0-y_0+z_0\leqslant x_i-y_i+z_i+mid\\x_i+y_i-z_i-mid\leqslant x_0+y_0-z_0\leqslant x_i+y_i-z_i+mid\end{cases}$$

设 $al,bl,cl,dl$ 为前四个式子的最大值， $ar,br,cr,dr$ 为后四个式子的最小值，， $a=-x_0+y_0+z_0,b=x_0-y_0+z_0,c=x_0+y_0-z_0$ ，那么等价于：

$$\begin{cases}al\leqslant a+b+c\leqslant ar\\bl\leqslant a\leqslant br\\cl\leqslant b\leqslant cr\\dl\leqslant c\leqslant dr\end{cases}$$

由于 $x_0=\frac{b+c}{2},y_0=\frac{a+c}{2},z_0=\frac{a+b}{2}$ ，且它们都是整数，所以还有 $a\equiv b\equiv c\pmod 2$ 。

此时套路地枚举 $a,b,c$ 的最后一个二进制位 $t\in\{0,1\}$ 再处理一下边界，那么模 $2$ 相同的限制就没了，最后不难用调整法算出一个答案。

时间复杂度： $O(n\log v)$ 。

## 代码

```
#include<stdio.h>
#include<iostream>
#define inf 6000000000000000000
using namespace std;
const int maxn=100005;
int T,n;
long long ansx,ansy,ansz;
long long x[maxn],y[maxn],z[maxn];
inline long long ceil(long long x){
	return x>=0? (x+1)/2ll:-((-x)/2ll);
}
inline long long floor(long long x){
	return x>=0? x/2ll:-((-x+1)/2ll);
}
int check(long long mid){
	long long al=-inf,bl=-inf,cl=-inf,dl=-inf,ar=inf,br=inf,cr=inf,dr=inf;
	//al<=a+b+c<=ar,bl<=a<=br,cl<=b<=cr,dl<=c<=dr
	for(int i=1;i<=n;i++){
		al=max(al,x[i]+y[i]+z[i]-mid),ar=min(ar,x[i]+y[i]+z[i]+mid);
		bl=max(bl,-x[i]+y[i]+z[i]-mid),br=min(br,-x[i]+y[i]+z[i]+mid);
		cl=max(cl,x[i]-y[i]+z[i]-mid),cr=min(cr,x[i]-y[i]+z[i]+mid);
		dl=max(dl,x[i]+y[i]-z[i]-mid),dr=min(dr,x[i]+y[i]-z[i]+mid);
	}
	for(int t=0;t<=1;t++){
		long long wl=ceil(al-3*t),wr=floor(ar-3*t);
		long long xl=ceil(bl-t),xr=floor(br-t);
		long long yl=ceil(cl-t),yr=floor(cr-t);
		long long zl=ceil(dl-t),zr=floor(dr-t);
		if(wl<=wr&&xl<=xr&&yl<=yr&&zl<=zr&&xl+yl+zl<=wr&&xr+yr+zr>=wl){
			long long x=xl,y=yl,z=zl,up=max(0ll,wl-xl-yl-zl);
			x+=min(up,xr-xl),up-=min(up,xr-xl);
			y+=min(up,yr-yl),up-=min(up,yr-yl);
			z+=min(up,zr-zl),up-=min(up,zr-zl);
			x=((x<<1)|t),y=((y<<1)|t),z=((z<<1)|t);
			ansx=(y+z)>>1,ansy=(x+z)>>1,ansz=(x+y)>>1;
			return 1;
		}
	}
	return 0;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld%lld%lld",&x[i],&y[i],&z[i]);
		long long L=-1,R=inf+1;
		while(L+1<R){
			long long mid=L+(R-L)/2ll;
			if(check(mid))
				R=mid;
			else L=mid;
		}
		check(R);
		printf("%lld %lld %lld\n",ansx,ansy,ansz);
	}
	return 0;
}
```

[整场比赛的题解](https://zybuluo.com/xiaoziyao/note/1807911)

---

## 作者：tzc_wk (赞：2)

[Codeforces 题面传送门](https://codeforces.ml/contest/685/problem/C) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF685C)

分类讨论神题。

首先看到最大值最小，一眼二分答案，于是问题转化为判定性问题，即是否 $\exists x_0,y_0,z_0$ 满足 $\forall i,|x_0-x_i|+|y_0-y_i|+|z_0-z_i|\le mid$。

柿子中带个绝对值，不好直接转化。不过注意到对于任意实数 $x$ 都有 $x\le |x|,-x\le |x|$，因此 $|x-y|\le v$ 的充要条件即是 $x-y\le v,y-x\le v$，因此上式可以把绝对值拆开得到：
$$
\begin{cases}
x_0-x_i+y_0-y_i+z_0-z_i\le mid\\
x_0-x_i+y_0-y_i+z_i-z_0\le mid\\
x_0-x_i+y_i-y_0+z_0-z_i\le mid\\
x_0-x_i+y_i-y_0+z_i-z_0\le mid\\
x_i-x_0+y_0-y_i+z_0-z_i\le mid\\
x_i-x_0+y_0-y_i+z_i-z_0\le mid\\
x_i-x_0+y_i-y_0+z_0-z_i\le mid\\
x_i-x_0+y_i-y_0+z_i-z_0\le mid
\end{cases}
$$
将上式整理一下可以得到：
$$
\begin{cases}
x_i+y_i+z_i-mid\le x_0+y_0+z_0\le x_i+y_i+z_i+mid\\
-x_i+y_i+z_i-mid\le -x_0+y_0+z_0\le -x_i+y_i+z_i+mid\\
x_i-y_i+z_i-mid\le x_0-y_0+z_0\le x_i-y_i+z_i+mid\\
x_i+y_i-z_i-mid\le x_0+y_0-z_0\le x_i+y_i-z_i+mid
\end{cases}
$$
记 $A_{l}=\max\limits_{i=1}^nx_i+y_i+z_i-mid,A_{r}=\min\limits_{i=1}^nx_i+y_i+z_i-mid$，$B_{l},B_r,C_l,C_r,D_l,D_r$ 也同理，那么显然上述柿子可以等效于：
$$
\begin{cases}
A_l\le x_0+y_0+z_0\le A_r\\
B_l\le -x_0+y_0+z_0\le B_r\\
C_l\le x_0-y_0+z_0\le C_r\\
D_l\le x_0+y_0+z_0\le D_r
\end{cases}
$$
注意到这四个不等式中间一项都带三个未知数，不好处理，不过这三个未知数之间又存在某种联系，因此考虑记 $a=-x_0+y_0+z_0,b=x_0-y_0+z_0,c=x_0+y_0-z_0$，那么有 $x_0=\dfrac{b+c}{2},y_0=\dfrac{a+c}{2},z_0=\dfrac{a+b}{2}$。我们还可以注意到 $x_0+y_0+z_0=a+b+c$，因此柿子又转化为
$$
\begin{cases}
A_l\le a+b+c\le A_r\\
B_l\le a\le B_r\\
C_l\le b\le C_r\\
D_l\le c\le D_r
\end{cases}
$$
当然这里有一个 restriction 是 $x_0,y_0,z_0$ 必须都是整数，因此必须有 $a\equiv b\equiv c\pmod{2}$。故考虑枚举 $r=a\bmod 2$，记 $a'=\dfrac{a-r}{2},b'=\dfrac{b-r}{2},c'=\dfrac{c-r}{2}$，那么上式又变为：
$$
\begin{cases}
\lceil\dfrac{A_l-3r}{2}\rceil\le a'+b'+c'\le\lfloor\dfrac{A_r-3r}{2}\rfloor\\
\lceil\dfrac{B_l-r}{2}\rceil\le a'\le\lfloor\dfrac{B_r-r}{2}\rfloor\\
\lceil\dfrac{C_l-r}{2}\rceil\le b'\le\lfloor\dfrac{C_r-r}{2}\rfloor\\
\lceil\dfrac{D_l-r}{2}\rceil\le c'\le\lfloor\dfrac{D_r-r}{2}\rfloor
\end{cases}
$$
这个随便求一求就行了，~~我相信即便刚学过 OI 的应该也会罢~~。

时间复杂度 $n\log A$，其中 $A=\max\{a_i\}$

```cpp
const int MAXN=1e5;
const ll INF=7e18; 
int n;ll x[MAXN+5],y[MAXN+5],z[MAXN+5],X,Y,Z;
ll down(ll x){return (x>=0)?(x>>1):(-(-x+1>>1));}//\lfloor x/2 \rfloor
ll up(ll x){return (x>=0)?(x+1>>1):(-(-x>>1));}//\lceil x/2 \rceil
bool check(ll mid){
	ll al=-INF,ar=INF,bl=-INF,br=INF;
	ll cl=-INF,cr=INF,dl=-INF,dr=INF;
	for(int i=1;i<=n;i++){
		chkmax(al,x[i]+y[i]+z[i]-mid);chkmin(ar,x[i]+y[i]+z[i]+mid);
		chkmax(bl,-x[i]+y[i]+z[i]-mid);chkmin(br,-x[i]+y[i]+z[i]+mid);
		chkmax(cl,x[i]-y[i]+z[i]-mid);chkmin(cr,x[i]-y[i]+z[i]+mid);
		chkmax(dl,x[i]+y[i]-z[i]-mid);chkmin(dr,x[i]+y[i]-z[i]+mid);
	}
	for(int r=0;r<2;r++){
		ll wl=up(al-3*r),wr=down(ar-3*r);
		ll xl=up(bl-r),xr=down(br-r);
		ll yl=up(cl-r),yr=down(cr-r);
		ll zl=up(dl-r),zr=down(dr-r);
		if(wl<=wr&&xl<=xr&&yl<=yr&&zl<=zr&&xl+yl+zl<=wr&&xr+yr+zr>=wl){
			ll a=xl,b=yl,c=zl,need=max(0ll,wl-xl-yl-zl);
			a+=min(need,xr-xl);need-=min(need,xr-xl);
			b+=min(need,yr-yl);need-=min(need,yr-yl);
			c+=min(need,zr-zl);need-=min(need,zr-zl);
			a=(a<<1|r);b=(b<<1|r);c=(c<<1|r);
			X=b+c>>1;Y=c+a>>1;Z=a+b>>1;return 1;
		}
	} return 0;
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld%lld",&x[i],&y[i],&z[i]);
	ll l=0,r=INF>>1,p=-1;
	while(l<=r){
		ll mid=l+r>>1;
		if(check(mid)) p=mid,r=mid-1;
		else l=mid+1;
	} check(p);//printf("%lld\n",p);
	printf("%lld %lld %lld\n",X,Y,Z);
}
int main(){
	int qu;scanf("%d",&qu);
	while(qu--) solve();
	return 0;
}
```



---

## 作者：Nelofus (赞：1)

哈密顿距离最大值最小，这不是我们二分答案吗。

假设当前答案为 $len$，那么有：
$$
\forall i\in[1, n],|x_i-x|+|y_i-y|+|z_i-z|\le len
$$
拆掉绝对值：
$$
\max(x-x_i,x_i-x)+\max(y-y_i,y_i-y)+\max(z-z_i,z_i-z)\le len
$$
这实际上是 $2^3=8$ 条不等式。
$$
\begin{cases}
x-x_i+y-y_i+z-z_i\le len\\
x_i-x+y-y_i+z-z_i\le len\\
x-x_i+y_i-y+z-z_i\le len\\
x-x_i+y-y_i+z_i-z\le len\\
x_i-x+y_i-y+z_i-z\le len\\
x-x_i+y_i-y+z_i-z\le len\\
x_i-x+y-y_i+z_i-z\le len\\
x_i-x+y_i-y+z-z_i\le len\\
\end{cases}
$$
如果最大的那一条满足，那就意味着**八条均满足**。

那么我们把 $n$ 条绝对值不等式变成 $8n$ 条不带绝对值的不等式，通过右边不断 $\operatorname{chkmin}$ 最终可以得到的是形如：
$$
\begin{aligned}
\begin{cases}
x+y+z&\le& a_1\\
-x+y+z&\le& a_2\\
x-y+z&\le& a_3\\
x+y-z&\le& a_4\\
-(x+y+z)&\le& a_5\\
-(-x+y+z)&\le& a_6\\
-(x-y+z)&\le& a_7\\
-(x+y-z)&\le& a_8\\
\end{cases}
\end{aligned}
$$
这里注意的是我们一般会选择凑 $n+1$ 条式子作为同号的，其中有一条全部都是正数的，以及每个变量一条符号为负其余为正的，这样的好处是方便凑相互之间的关系，例如上面的 $1\sim 4$。

所以：
$$
\begin{aligned}
-a_5&\le +x+y+z\le  a_1\\
-a_6&\le -x+y+z\le a_2\\
-a_7&\le +x-y+z\le a_3\\
-a_8&\le +x+y-z\le a_4
\end{aligned}
$$
这里我们不能把每个元单独地表示出来，**因为每个式子的极值可能不在同一处取到的缘故，这样会使得我们不等式的解集扩大（也就是既使一式取得到右边的等于号，此时另外一式可能此时取不到等于）**。

既然不能每个独立求出取值范围，那么我们就只能考虑把每个式子当成一个整体，现在我们假设 $p_1=x+y+z,p_2=x+y-z,p_3=x-y+z,p_4=-x+y+z$，那么：
$$
\begin{aligned}
-a_5\le p_1\le a_1\\
-a_6\le p_2\le a_2\\
-a_7\le p_3\le a_3\\
-a_8\le p_4\le a_4\\
\end{aligned}
$$
而且 $x=\frac{p_3+p_4}{2},y=\frac{p_2+p_4}{2},z=\frac{p_2+p_3}{2}$。

这里操作是合法的，因为我们加减的不是不等式而是变量。

这看起来有些奇怪，因为我们原先只使用了三个元，现在却有四个元，而且这四个元看起来毫无联系，不知道该怎么解——也就是说没有体现每个 $p$ 表现的是一组相互有关的变量的性质，那么我们就要用其他三个变量取代一个变量来表达它们之间的关系，这个时候就用到上面所说的好处了，不难发现：
$$
p_1=p_2+p_3+p_4
$$
那么式子就是：
$$
\begin{aligned}
-a_5&\le p_2+p_3+p_4\le a_1\\
-a_6&\le p_2\le a_2\\
-a_7&\le p_3\le a_3\\
-a_8&\le p_4\le a_4\\
\end{aligned}
$$
这个时候就可以解了！只是注意这个时候因为 $x,y,z$ 都是整数，所以 $p_2\equiv p_3\equiv p_4\pmod 2$，这个问题枚举末尾就能解决。

在判断时我们先暴力令 $p_2=-a_6,p_3=-a_7,p_4=-a_8$，如果第一条不等式不满足，那么把 $p_2$ 调整到 $a_2$，如果还不满足，那就把 $p_3$ 调整到 $a_3$，接下来是把 $p_4$ 调整为 $a_4$，从而构造出答案。

```cpp
#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 1e5 + 10;
constexpr i64 inf = 3e18;

i64 x[N], y[N], z[N];
int n;

i64 a[9];
i64 xmn, xmx, ymn, ymx, zmn, zmx;
i64 low[5], hig[5];
i64 ansx, ansy, ansz;

template<typename T>
inline void chkmin(T &a, const T &b) {if (a > b)	a = b;}

bool check(const i64 &len) {
	for (int i = 1; i <= 8; i++)
		a[i] = inf;

	for (int i = 1; i <= n; i++) {
		chkmin(a[1], len + x[i] + y[i] + z[i]);
		chkmin(a[2], len - x[i] + y[i] + z[i]);
		chkmin(a[3], len + x[i] - y[i] + z[i]);
		chkmin(a[4], len + x[i] + y[i] - z[i]);
		chkmin(a[5], len - x[i] - y[i] - z[i]);
		chkmin(a[6], len + x[i] - y[i] - z[i]);
		chkmin(a[7], len - x[i] + y[i] - z[i]);
		chkmin(a[8], len - x[i] - y[i] + z[i]);
	}
	
	low[1] = -a[5], hig[1] = a[1];
	low[2] = -a[6], hig[2] = a[2];
	low[3] = -a[7], hig[3] = a[3];
	low[4] = -a[8], hig[4] = a[4];
	for (int bit = 0; bit < 2; bit++) {
		// 如果不同就 +1
		i64 l1 = low[1] + ((low[1] & 1) ^ bit);
		i64 l2 = low[2] + ((low[2] & 1) ^ bit);
		i64 l3 = low[3] + ((low[3] & 1) ^ bit);
		i64 l4 = low[4] + ((low[4] & 1) ^ bit);
		// 如果不同就 -1
		i64 r1 = hig[1] - ((hig[1] & 1) ^ bit);
		i64 r2 = hig[2] - ((hig[2] & 1) ^ bit);
		i64 r3 = hig[3] - ((hig[3] & 1) ^ bit);
		i64 r4 = hig[4] - ((hig[4] & 1) ^ bit);
		if (l1 > r1 || l2 > r2 || l3 > r3 || l4 > r4)
			continue;
		i64 ans[3];

		ans[0] = l2, ans[1] = l3, ans[2] = l4;

		if (ans[0] + ans[1] + ans[2] > r1)
			continue;

		(ans[0] + ans[1] + ans[2] < l1) && (ans[0] = (r2 + ans[1] + ans[2] < l1 ? r2 : l1 - ans[1] - ans[2]));
		(ans[0] + ans[1] + ans[2] < l1) && (ans[1] = (ans[0] + r3 + ans[2] < l1 ? r3 : l1 - ans[0] - ans[2]));
		(ans[0] + ans[1] + ans[2] < l1) && (ans[2] = (ans[0] + ans[1] + r4 < l1 ? r4 : l1 - ans[0] - ans[1]));

		if (ans[0] + ans[1] + ans[2] < l1)
			continue;

		ansx = ans[1] + ans[2];
		ansy = ans[0] + ans[2];
		ansz = ans[0] + ans[1];
		return true;
	}
	return false;
}

void solve() {
	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> x[i] >> y[i] >> z[i];

	i64 l = 0, r = 3e18;
	while (l < r) {
		i64 mid = (l + r) >> 1;
		if (check(mid))
			r = mid;
		else
			l = mid + 1;
	}

	check(l);
	i64 ax = ansx, ay = ansy, az = ansz;
	std::cout << ax / 2 << ' ' << ay / 2 << ' ' << az / 2 << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int T;
	std::cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```



---

