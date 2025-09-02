# [ABC224G] Roll or Increment

## 题目描述

#### 题意
有一个 $N$ 面的骰子，每个骰子都有相等的概率随机出现 $1$ 到 $N$ 之间的整数目。 

在下文中，我们称骰子 "掷出 " $X$ ，是指骰子的上面有一个整数 $X$ 。 
最初，骰子的放置方式是掷出一个整数 $S$ 。
您可以对这些骰子进行 "以下两种操作中的任意一种"，次数不限（甚至可以是零次）。

 - 支付 $A$ 元，掷出的骰子值增加 $1$。 也就是说，当骰子掷出的原数值是 $X$ 时，骰子掷出的数值变更为 $X + 1$ 。 如果操作前掷出的骰子是 $N$ ，则无法执行此操作。
 - 支付 $B$ 圆并重新掷骰子。 掷出的骰子以相等的概率随机变为 $1$ 到 $N$ 之间的任意整数。

考虑通过上述操作将骰子从掷出 $S$ 的初始状态变为掷出 $T$ 的状态。 

输出采取最优策略时的成本的期望值。

## 样例 #1

### 输入

```
5 2 4 10 4```

### 输出

```
15.0000000000000000```

## 样例 #2

### 输入

```
10 6 6 1 2```

### 输出

```
0.0000000000000000```

## 样例 #3

### 输入

```
1000000000 1000000000 1 1000000000 1000000000```

### 输出

```
1000000000000000000.0000000000000000```

# 题解

## 作者：I_LOVE_MATH (赞：2)

### 题目大意

一个骰子，有两种操作：

- 支付 $A$ 元，使掷出的点数 $+1$，但不能超过 $N$。
- 支付 $B$ 元，掷一次骰子，使点数以相等概率随机变为 $1$ 到 $N$ 之间的整数。

一开始点数为 $S$，求最优策略掷出 $T$ 的花费的期望。

### 解题思路

首先先讨论不掷骰子只加点数的情况，当 $s \le T$ 时，就可以花费 $A \cdot (T-S)$ 的代价直接到达 $T$。

然后考虑要掷骰子，重掷骰子后加的点数就会无效，因此一定是**在掷多次后，到达一个离 $T$ 较近的位置，再加到 $T$**。

不妨设一个阈值 $X$，当骰子随机到 $[T-X+1,T]$ 之间时，就加点数。  

于是我们就可以将策略分为两部分：

1. **掷骰子**  
   掷一次骰子，随机到 $[T-X+1,T]$ 之间的概率为 $\frac{X}{N}$。  
   根据伯努利过程的结论，次数的期望就是概率的倒数，为 $\frac{N}{X}$ ，因此此过程花费的期望 $B \cdot \frac{N}{X}$。
2. **加点数**  
   掷出 $[T-X+1,T]$ 中 $i$ 的概率为 $\frac{1}{X}$，这个点走到 $T$ 需要 $T-i$ 次操作，那么它到 $T$ 花费的期望就为 $A\cdot \frac{T-i}{X}$。  
   将其中所有点数的期望求和，化简得 $A\cdot\frac{(X-1)}{2}$。

根据期望的线性性质，全过程的期望即为 $B \cdot \frac{N}{X}+A\cdot\frac{(X-1)}{2}$。

再根据均值不等式：
$$
\begin{aligned}
  B \cdot \frac{N}{X}+A\cdot\frac{(X-1)}{2} &= B \cdot \frac{N}{X}+A\cdot\frac{X}{2}-\frac{A}{2} \\
                 &\ge \sqrt{2BNA} -\frac{A}{2} \text{（当 $X=\sqrt{\frac{2BN}{A}}$ 时取等）}
\end{aligned}
$$

因此取 $X=\sqrt{\frac{2BN}{A}}$ 附近的三个整数代入计算取最小值即可。

值得注意的是，如果取不到函数极值那么函数单调，需要取边界值$X=1$或$X=T$时的最小值。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;

long long n, s, t, a, b;
long double ans;

inline long double get(int x)
{
	return 1.0 * b * n / x + a * (x - 1) / 2.0;
}

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> s >> t >> a >> b;
	if (s == t)
	{
		cout << 0 << endl;
		return 0;
	}
	ans = 1.0 * b * n;
	if (s < t)
	{
		ans = min(ans, (long double)(t - s) * a);
	}
	ans = min(ans, min(get(1), get(t)));
	long long x = sqrtl(2.0 * b * n / a);
	if (x <= t)
	{
		ans = min(ans, get(x));
		if (x >= 1)
		{
			ans = min(ans, get(x - 1));
		}
		if (x <= t)
		{
			ans = min(ans, get(x + 1));
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：SunburstFan (赞：2)

### G - Roll or Increment

#### 题目大意

有一个 $N$ 面骰子，最初，骰子 $S$ 面朝上。

可以进行以下两次操作，次数不限。

- 操作一：花费 $A$ 代价，使骰子显示的数值 增加 $1$。

- 操作二：花费 $B$ 代价，重新投掷骰子。

要让骰子从初始状态显示 $S$ 变为显示 $T$。  

求当使用最优策略使该期望值最小时，这样做**所需花费的最小期望值**。

#### 解题思路

显然，应该**操作一**还是**操作二**，只取决于**骰子当前显示的数字**。

对于每一个 $i = 1, 2, \ldots, N$，试求 当骰子显示 $i$ 时，我们应该选择哪个选项。

注意到：

- 如果骰子显示的数字大于 $T$，那么显然**操作二**是最佳选择。

- 在**操作一**之后立即**操作二**显然比仅仅**操作二**更劣。

因此，在最优策略中，如果当骰子显示的数字为 $P$ 时选择**操作一**，那么当骰子显示的数字为 $P'$ 使得 $P \leq P'$ 时，应该选择**操作一**。

根据上述两点，开始思考最优策略：

存在一个满足 $1 \leq X \leq T$ 的整数 $X$：

如果骰子显示 $T-X$ 和 $T$ 之间的任意一个数，则选择 **操作一**；

否则，选择 **操作二**。

问题转化为：

**求选择一个整数 $X$，使得 $1 \leq X \leq T$，从而使得 将骰子所示的骰子从 $S$ 改为 $T$ 的期望值最小。**

开始分类讨论：

- 在 $T-X+1\leq S \leq T$ 成立的条件下选择 $X$。
- 在 $T-X+1\leq S \leq T$ 不成立的条件下选择 $X$。

**第一种情况**：在成立 $T-X+1\leq S \leq T$ 的条件下选择 $X$ 时。

因为我们选择 **操作一**，直到骰子显示的数字从 $S$ 变为 $T$，所以所需的代价是 $A(T-S)$，与 $X$ 无关。

**第二种情况**：在$T-X+1\leq S \leq T$ 不成立的条件下选择 $X$ 时。

骰子上的数字从 $S$ 到 $T$ 的转换过程包括以下两个步骤。

- 首先，重复**操作二**，直到骰子显示的数字在 $T-X+1$ 和 $T$ 之间。
- 然后，重复**操作一**，直到数字变成 $T$。

每一步所需的花费如下。

1. 进行一次操作二后，骰子显示 $T-X+1$ 和 $T$ 之间数字的概率为 $X/N$，因此第一步中操作二的预期次数为 $N/X$。**第一步的花费为 $BN/X$**。  
    
2. 第一步结束后，模具有可能出现介于 $T-X+1$ 和 $T$ 之间的任何整数。因此，第二步的花费为 $\lbrace\sum_{i = T-X+1}^{T} A(T-i)\rbrace/X = A(X-1)/2$。  
    

**将骰子显示的数字从 $S$ 变为 $T$ 所需的花费为 $A(X-1)/2 + BN/X$**。  

那么如何在 $T-X+1\leq S \leq T$ 不成立的条件下，求出选择整数 $X$ 时 $T-X+1\leq S \leq T$ 的最小值呢？

考虑函数 $f(x) = A(x-1)/2 + BN/x$ 定义为正实数 $x$。

可以观察图像计算可得，函数 $f(x)$ 在 $x = \sqrt{2BN/A}$ 处最小。

另外，由于 $f''(x) = 2BN/x^3$ , $f(x)$ 是一个凸函数。

因此，只需计算 $f(X)$ 在 $\sqrt{2BN/A}$ 附近的若干个 $X$ ，使得不成立 $T-X+1\leq S \leq T$ 和 $1 \leq X \leq T$。

时间复杂度 $O(1)$。

---

## 作者：zxdjmq (赞：1)

# ABC224G.Roll or Increment

[更好的阅读体验](https://www.cnblogs.com/zxdjmq/p/18670980)

## 题意：

有一个 $N$ 面的骰子，掷出 $1$ 到 $N$ 的概率相等。初始数字为 $S$，目标数字为 $T$。有两种操作：

1. 花费 $A$，使当前数字加一；

2. 花费 $B$，重掷。

询问最优策略下到达 $T$ 的期望花费。

$1 \le S,T \le N \le 10^9,1\le A,B \le 10^9$

## 解法：

由于操作 2 前的操作 1 是无效的，所以最优策略一定分为两部分：

1. 一直进行操作 2 使当前数字距离 $T$ **足够近**（或在 $S\leq T$ 且距离足够近时不进行操作 2）；
2. 一直进行操作 1 使当前数字到达 $T$。

**足够近**的概念比较模糊，所以我们定义**足够近**为当前数字小于 $T$ 且二者差小于等于 $K$，那么当数字落在区间 $[T-K,T]$ 内时达到**足够近**条件，于是我们可以得到期望花费为 $\frac{BN}{K+1}+\frac{1}{K+1}\times A\times \sum\limits_{i=T-K} ^T (T-i)$，即 $\frac {BN}{K+1}+\frac{AK}{2}$。

观察到这个式子里只有 $K$ 未确定，且形式非常像均值不等式里的 $x+\frac{1}{x}$，故考虑使用均值不等式去掉 $K$：
$$
\begin{aligned} \frac {BN}{K+1}+\frac{AK}{2}&=\frac {BN}{K+1}+\frac{A(K+1)}{2}-\frac{A}{2} \\ &\geq2\sqrt{\frac {BN}{K+1} \cdot \frac{A(K+1)}{2}}-\frac{A}{2}\\&\geq\sqrt{2ABN}-\frac{A}{2}\end{aligned}
$$
当 $\frac {BN}{K+1}=\frac{A(K+1)}{2}$ 即 $K=\sqrt{\frac{2BN}{A}}-1$ 时取等。

但是发现在 $N < \frac{A}{2B}$ 或 $N>\frac{AT^2}{2B}$ 时取等条件不能成立，由于 $\frac {BN}{K+1}+\frac{AK}{2}$ 在前两个情况下在区间 $[0,T-1]$ 具有单调性，所以将 $K=0$ 或 $T-1$ 算一下即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ld long double
ld n,s,t,a,b,ans;

inline ld cal(int k){
    return 1.0*b*n/(k+1)+1.0*a*k/2.0;
}

int main(){
    cin>>n>>s>>t>>a>>b;
    ans=min(cal(0),cal(t-1));

    if(s<=t)ans=min(ans,a*(t-s));

    int mink=sqrtl(2.0*b*n/a)-1;
    if(mink>=0 && mink<t)ans=min(ans,cal(mink));
    if(mink-1>=0 && mink-1<t)ans=min(ans,cal(mink-1));
    if(mink+1>=0 && mink+1<t)ans=min(ans,cal(mink+1));

    printf("%.16Lf\n",ans);
    return 0;
}
```

---

## 作者：CrTsIr400 (赞：0)

[[ABC224G] Roll or Increment](https://www.luogu.com.cn/problem/AT_abc224_g)

给你一个 $n$ 面的骰子，每次点值完全随机，投一次 $B$ 代价，给点值加一 $A$ 代价。初始朝上的点值为 $S$，现在要求点值为 $T$，求最优策略下的期望代价。都是 $10^9$ 量级。

显然最优策略一定是丢多次之后全部加一。

我们假设丢某些次之后骰子的点值终于能出现在 $[S,T]$ 之内，然后直接加到 $T$。而这个 $S$ 是我们自己可以决定的。

$S$ 太小的时候浪费的次数比较少，但是这一次加到 $T$ 可能很大代价；

$S$ 太大的时候浪费的次数比较多，但是这一次加到 $T$ 代价就比较小。

所以考虑对于 $S$ 求期望代价，答案是 $\dfrac{nB}{T-S+1}+\dfrac{A\times (T-S)}{2}$。

发现 $n,A,B$ 其实是给定的且大于 $0$，设 $x=T-S+1(1\le x\le T,x\in \mathrm Z)$ 实际上答案就是 $\dfrac{nB}{x}+\dfrac{Ax-A}{2}$。

想一下 $y=\dfrac{1}{x}+x$ 这种函数图像，对勾函数。

直接代入，基本不等式求解是可行的，但这是 OI，我们三分一下这个函数峰值即可。

---

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
I n,s,t,a,b;
using D=long double;
D f(I x){return 1.0l*n*b/x+1.0l*a*(x-1)/2.0l;}
D calc(I len){I l=1,r=len-1,mid;
	D ans=f(len);
	while(l<=r){mid=l+r>>1;
		if(f(mid-1)<f(mid))r=mid-1;
		else if(f(mid)>f(mid+1))l=mid+1;
		else {ans=min(ans,f(mid));break;}
	}return ans;
}
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>s>>t>>a>>b;
	if(s==t)printf("0\n");
	else if(s>t)printf("%.10Lf\n",calc(t));
	else printf("%.10Lf\n",min(calc(t-s),1.0l*a*(t-s)));
	return 0;}
```

---



---

## 作者：hellolin (赞：0)

# ABC224G Roll or Increment 题解

建议前往 [note.hellolin.cf](https://note.hellolin.cf/solutions/abc224g/) 获得更好的阅读体验！

## 前置分析

下面设当前投出的值是 $D$，我们先仔细考虑一下题目中两种操作：显然的，我们不应该在增加之后重投，并且当 $D>T$ 时，我们应该立即重投。

结合上面两点，我们应选择在一些重投之后增加，或者直接增加。

### 直接增加？

显然这种方法仅当 $S<T$ 时适用，此时要花费的代价就是 $A\cdot(T-S)$。

### 先重投再增加？

不妨设区间 $[E, T]$ 并规定只有当 $D\in [E, T]$ 时才执行增加。现在的任务就是该如何选择这个 $E$。

考虑重投部分：设这个区间大小 $L=T-E+1$，重投时投中这个区间的概率是 $\dfrac{L}{N}$，所以我们所有重投的期望成本就是 $\dfrac{BN}{L}$。

考虑增加部分：此时 $D$ 满足 $D\in [E, T]$，所以我们增加的期望成本就是 $\dfrac{\sum\limits^{T}_{i=E}A\cdot (T-i)}{L}=\dfrac{A\cdot (L-1)}{2}$。

综上，完成整个操作的期望成本是 $\dfrac{BN}{L}+\dfrac{A\cdot (L-1)}{2}$。下面提供两种求解答案的方式。

## 二分

时间复杂度 $O(\log T)$，可以通过。

``` cpp
using ld = long double;
ld search(int l, int r) {
    auto f = [&](const int l) {
        return 1.0l * n * b / l + a * (l - 1) / 2.0l;
    };
    while (l < r) {
        int mid = (l + r) >> 1;
        if (f(t - mid + 2) < f(t - mid + 1))
            l = mid + 1;
        else
            r = mid;
    }
    return f(l);
}
void solve() {
    std::cout << std::fixed << std::setprecision(10);
    std::cin >> n >> s >> t >> a >> b;
    if (t == s)
        std::cout << 0 << '\n';
    else if (s > t)
        std::cout << search(1, t) << '\n';
    else
        std::cout << std::min(search(s + 1, t), 1.0l * a * (t - s)) << '\n';
}
```

## 不等式

设定义在 $\R$ 上的函数 $f(x)=\dfrac{BN}{x}+\dfrac{A\cdot (x-1)}{2}$，这里的自变量也即我们前面提到的 $L$。将该式化简：

$$
\begin{aligned}
f(x) &= \dfrac{BN}{x}+\dfrac{A\cdot (x-1)}{2} \\
&= \dfrac{BN}{x}+\dfrac{Ax}{2}-\dfrac{A}{2} \\
\end{aligned}
$$

不管这个常数项 $\dfrac{A}{2}$，发现前面这两项都是非负实数，我们可以利用均值不等式求出该函数的最小值（梦回高一数学）：

$$
\begin{aligned}
\dfrac{BN}{x}+\dfrac{Ax}{2}-\dfrac{A}{2} &\ge \sqrt{2\times \dfrac{BN}{x}\times\dfrac{Ax}{2}}-\dfrac{A}{2} \\
\sqrt{2\times \dfrac{BN}{x}\times\dfrac{Ax}{2}}-\dfrac{A}{2} &=\sqrt{NAB}-\dfrac{A}{2} \\
\end{aligned}
$$

综上，$f(x)$ 在 $x=\sqrt{\dfrac{2\times NB}{A}}$ 处最小。又易证 $f(x)$ 为凸函数，在代码实现中我们只需计算 $f(x-1),\ f(x),\ f(x+1)$ 几个值就行了。

时间复杂度 $O(1)$，可以通过。

``` cpp
void solve() {
    auto f = [&](const int l) {
        return 1.0l * n * b / l + a * (l - 1) / 2.0l;
    };
    std::cout << std::fixed << std::setprecision(10);
    std::cin >> n >> s >> t >> a >> b;
    ld ans = 0;
    if (s != t) {
        ans = 1.0l * n * b;
        if (s <= t)
            chmin(ans, 1.0l * a * (t - s));
        chmin(ans, std::min(f(1), f(t)));
        p = std::sqrt(2.0l * n * b / a);
        if (p <= t) {
            chmin(ans, f(p));
            if (p >= 1) chmin(ans, f(p - 1));
            if (p <= t) chmin(ans, f(p + 1));
        }
    }
    std::cout << ans << '\n';
}
```

## 后记

推式子真的太爽啦！！！但这题 *2374 多少有点虚高了罢。

---

