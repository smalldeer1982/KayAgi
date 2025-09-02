# Long Legs

## 题目描述

A robot is placed in a cell $ (0, 0) $ of an infinite grid. This robot has adjustable length legs. Initially, its legs have length $ 1 $ .

Let the robot currently be in the cell $ (x, y) $ and have legs of length $ m $ . In one move, it can perform one of the following three actions:

- jump into the cell $ (x + m, y) $ ;
- jump into the cell $ (x, y + m) $ ;
- increase the length of the legs by $ 1 $ , i. e. set it to $ m + 1 $ .

What's the smallest number of moves robot has to make to reach a cell $ (a, b) $ ?

## 说明/提示

In the first testcase, the robot can first jump to $ (0, 1) $ , then to $ (1, 1) $ . If it ever increases the length of its legs, it will only be able to jump past $ (1, 1) $ .

In the second testcase, the robot can jump to $ (1, 0) $ , then increase the length of its length to $ 2 $ and jump three times to reach $ (1, 6) $ .

In the third testcase, the robot can increase the length of its legs three times to make it $ 4 $ . Then jump to $ (0, 4) $ . Then jump twice to reach $ (8, 4) $ .

## 样例 #1

### 输入

```
3
1 1
1 6
8 4```

### 输出

```
2
5
6```

# 题解

## 作者：frelow_poem (赞：24)

### 引用文献

[官方题解](https://codeforces.com/blog/entry/114854)

---
### 题意简述

[题目传送门](https://www.luogu.com.cn/problem/CF1814B)

平面直角坐标系内有一机器人位于 $(x,y)$，该机器人的步长为 $m$。每一步中，可以选择如下三种操作中的一种：

- 移动至 $(x+m,y)$；
- 移动至 $(x,y+m)$；
- 将 $m$ 的值增加 $1$，即将 $m$ 赋值为 $m+1$。

$m$ 的初始值为 $1$，机器人最开始位于 $(0,0)$。

给定坐标 $(a,b)$，求出到达 $(a,b)$ 最少需要几步。$t$ 组询问。

---
### 思路点拨

**以下内容大部分来自官方题解，根据叙述需要改动了一部分。**

在本题中，我们应该用什么样的策略控制总步数最小呢？如果第三种操作进行的很少，那么 $m$ 就较小，一次行进的距离有限，步数就会多；反之 $m$ 过大时，选择第三种操作浪费了太多步数，也会得不偿失。

考虑终点为 $(10,20)$ 的情况。假如丝毫不选择增加 $m$，一直保持 $m=1$，总步数为 $30$；花费 $9$ 步将 $m$ 增加到 $10$ 再移动，总步数为 $12$；而相对折中的，将 $m$ 增加到 $5$ 再移动，总步数为 $10$。可以证明最小步数恰好为 $10$。

因此，我们的目标就变成了在这种策略下，找到一个最合适的 $m$，使得将步长增加至这个 $m$ 之后再移动总步数最小。不妨设这个最终的 $m$ 的值为 $k$。下面，给出这一策略的详细证明过程。

注意到在 $(10,20)$ 的例子中，最终的 $k$ 为 $5$，而 $10$ 和 $20$ 恰好为 $5$ 的倍数。这是否意味着上文的策略仅适用于 $a,b$ 为 $k$ 的整数倍的情况？

分别考虑 $a$ 和 $b$。若 $a$ 不是 $k$ 的倍数，此时我们在 $x$ 轴方向上只能移动 $\left\lfloor\dfrac{a}{k}\right\rfloor$ 步，还剩下 $a - \left\lfloor\dfrac{a}{k}\right\rfloor \times k$ 的距离没有走。这个剩余的距离一定小于 $k$。

由于 $m$ 的值每次只能增加 $1$，因此对于满足 $1 \le m \le k$ 的所有 $m$，都会至少取到一次。所以，$m$ 也一定会在某一步结束时，刚好为 $a - \left\lfloor\dfrac{a}{k}\right\rfloor \times k$，此时沿 $x$ 轴方向移动一步即可恰好在 $m=k$ 的时候用整数次移动到达 $x=a$。

总结得到：当 $a$ 不是 $k$ 的倍数时，在 $x$ 轴方向的移动包含 $\left\lfloor\dfrac{a}{k}\right\rfloor$ 次步长为 $k$ 的移动和 $1$ 次步长为 $a - \left\lfloor\dfrac{a}{k}\right\rfloor \times k$ 的移动，共 $\left\lfloor\dfrac{a}{k}\right\rfloor +1$ 次。

当 $a$ 为 $k$ 的倍数时，共移动 $\dfrac{a}{k}$ 次。因此对于任意的 $a$，都有在 $x$ 轴方向上的总移动次数为 $\left\lceil\dfrac{a}{k}\right\rceil$。

$y$ 轴方向的 $b$ 同理。加上将步长增加到 $k$ 需要的 $k-1$ 步，总步数为 $\left\lceil\dfrac{a}{k}\right\rceil + \left\lceil\dfrac{b}{k}\right\rceil + (k-1)$。仅需求整数 $k$ 使得该式最小即可。

那么，$k$ 取何值时原式有最小值呢？因为即使在 $a,b$ 接近 $10^9$ 时，$k$ 太大也不是最优情况，又因为询问次数 $t \le 100$，所以可以直接从 $1$ 开始枚举 $k$，到 $3 \times 10^5$ 都不会超时。

**以上内容大部分来自官方题解，根据叙述需要改动了一部分。**

---
### 完整代码

```cpp
#include <cstdio>
using namespace std;

inline int _setmin(int &_a, int _b){return _a = (_a < _b) ? _a : _b;}

const int inf = 2147483647;
int T, a, b;

inline int Solve(int x)
{
    return (a / x) + (a % x != 0) + (b / x) + (b % x != 0) + (x - 1);
}

//电脑看不见
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &a, &b);
        int ans = inf;
        for (int i = 1; i <= 3e5; i++)
        {
            _setmin(ans, Solve(i));
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---
### 后记

> 可以直接从 $1$ 开始枚举 $k$，到 $3 \times 10^5$ 都不会超时。

为什么？为什么 $k$ 的最大取值不会超过 $3 \times 10^5$？我们离真相还有最后一步。

观察 $\left\lceil\dfrac{a}{k}\right\rceil + \left\lceil\dfrac{b}{k}\right\rceil + (k-1)$ 与 $\dfrac{a}{k} + \dfrac{b}{k} + (k-1)$ 的区别，发现这两个式子的差最大为 $2$。化简第二个式子，得到 $(\dfrac{a+b}{k}+k)-1$。接下来运用[均值不等式](https://baike.baidu.com/item/%E5%9D%87%E5%80%BC%E4%B8%8D%E7%AD%89%E5%BC%8F)即可求出最小值。

**引理：** $m+n \ge 2\sqrt{mn}$

**证明：** 

$$
\begin{aligned}
  (\sqrt{m}-\sqrt{n})^2 &\ge 0 \\
  (\sqrt{m})^2 - 2\sqrt{mn} + (\sqrt{n})^2 &\ge 0 \\
  m+n &\ge 2\sqrt{mn}
\end{aligned}
$$
注意该不等式取等**当且仅当** $m=n$。

令 $m = \dfrac{a+b}{k}$，$n = k$，得：

$$
\begin{aligned}
\dfrac{a+b}{k}+k &\ge 2\sqrt{a+b} \\
\dfrac{a+b}{k}+k-1 &\ge 2\sqrt{a+b} -1
\end{aligned}
$$

该式取最小值时，$k=\dfrac{a+b}{k}$，即 $k=\sqrt{a+b}$。

当 $a=b=10^9$ 时，$k$ 最大为 $\sqrt{2 \times 10^9} = 2\sqrt{5} \times 10^4 \le 5 \times 10^4 \le 3 \times 10^5$。因此，枚举上限为 $3 \times 10^5$ 时的正确性得以证明。同样也可以看出此代码仍有优化空间。

```cpp
//按照上面的式子，将枚举上限调整为5e4
//202ms -> 46ms
for (int i = 1; i <= 5e4; i++)
{
    _setmin(ans, Solve(i));
}
```

然后呢？还有优化空间吗？我想，OI 的魅力就在于此。

为什么我们要从 $1$ 开始枚举呢？既然已经知道了 $k$ 大致为 $\sqrt{a+b}$，便只需要在这个估测的大小附近枚举即可，在 $k$ 偏大时能节省不少时间。具体实现详见代码。

```cpp
#include <cstdio>
#include <cmath>
using namespace std;

inline int _max(int _a, int _b){return (_a > _b) ? _a : _b;}
inline int _setmin(int &_a, int _b){return _a = (_a < _b) ? _a : _b;}

const int delta = 100; //枚举偏移量
const int inf = 2147483647;
int T, a, b;

inline int Solve(int x)
{
    return (a / x) + (a % x != 0) + (b / x) + (b % x != 0) + (x - 1);
}

//电脑看不见
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &a, &b);
        int ans = inf;
        int base = (int)sqrt(a+b); //估测值
        //在估测值两端枚举k, 注意k>=1
        for (int i = _max(1, base - delta); i <= base + delta; i++)
        {
            _setmin(ans, Solve(i));
        }
        //最多只枚举(2*delta + 1)个可能的取值, 46ms -> 15ms
        printf("%d\n", ans);
    }
    return 0;
}
```

 `delta` 的取值并不十分重要，稍微大一点就行，取 $100$ 或 $200$ 都可以，不过是一个较大的常数。这样，我们就找到了对于更强数据的通用解法。
 
---

这大概是我写过最长的题解了，感谢您的阅读。

---

## 作者：Xy_top (赞：6)

其实这场 edu CF 质量不错的，就是因为 CF 被黑客入侵了所以变成 unr 了，不然上大分（

这道题放在 B 有点怪。

首先一个显然的转换是，伸长手臂为 $m$ 后，我们可以走 $1$ 到 $m$ 中任意的格子，因为你可以在没伸长的时候走啊。

然后推一波公式：假设最终伸长手臂到 $m$，那么 $x$ 就要移动 $\lceil\frac{x}{m}\rceil$，$y$ 就要移动 $\lceil\frac{y}{m}\rceil$ 次，证明十分简单。

最终答案就是 $\min\limits_{m=1}^{10^9}(\lceil\frac{x}{m}\rceil+\lceil\frac{y}{m}\rceil+m)$ 啦，但是这样过不去，我们要考虑优化。

不难发现，当 $m$ 取 $10^4$ 时答案不劣，就算 $x$ $y$ 都取到最大的 $10^9$，两者之和才是 $2\times 10^5$。

而当 $m$ 比 $2\times 10^5$ 大的时候，只看伸长到 $2\times 10^5$ 就需要这些步数了，显然不会是最优答案了，就退出循环即可。

事实上，这个下限可以取到 $2\times \sqrt{10^9}$，上代码：

```cpp
#include <cmath>
#include <iostream>
using namespace std;
int t, n, m;
int main () {
	cin >> t;
	while (t --) {
		int ans = 2000000000;
		cin >> n >> m;
		if (n > m) swap (n, m);
		for (int i = 1; i <= 500000; i ++) {
			ans = min (ans, int (ceil (n * 1.0 / i) ) + int (ceil (m * 1.0 / i) ) + i - 1);
		}
		cout << ans << "\n";
	}
	return 0;
}
```


---

## 作者：VitrelosTia (赞：2)

一道比较搞笑的题。

为了方便，单讨论横坐标的情况。假如我们最终的步长是 $m$，一个非常好的想法是一开始直接变成 $m$，这样显然是可以走得最快的，但是问题是这样最后可能会走不完，还剩 $a - \lfloor \dfrac a m \rfloor \times m$，这个东西是在 $(0, m)$ 范围内的，那调整的办法就是在一开始直接变成 $m$ 的过程中，变到这个值的时候走一步，这样问题就解决了。

纵坐标同理的。容易得到要走的步数是 $m - 1 + \lceil \dfrac a m \rceil + \lceil \dfrac b m \rceil$。问题来到了如何确定 $m$。枚举显然并不是很现实，不妨进行估算。

我们发现这个式子大概等于 $m + \dfrac {a + b} m$，我们知道“积一定，差小和小（其实就是均值不等式的取等条件）”，于是当 $m = \dfrac {a + b} m$ 即 $m = \sqrt{a + b}$ 时这个东西是最小的。

那我们直接枚举这附近的所有数，看看哪个 $m$ 算出来的答案最小就好了。

```
void solve() {
	int a, b; cin >> a >> b;
	int qwq = sqrt(1.0 * (a + b)), ans = INT_MAX;
	for (int m = max(1, qwq - 114); m <= qwq + 114; m++) {
		int now = m - 1 + ceil(1.0 * a / m) + ceil(1.0 * b / m);
		ans = min(ans, now);
	}
	cout << ans << '\n';
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

假设最终的 $m=x$，那么最少需要花费 $x-1+\left\lceil\dfrac{a}{x}\right\rceil+\left\lceil\dfrac{b}{x}\right\rceil$ 次操作，因为要把腿伸长 $x-1$ 次，用最终腿的长度进行移动更优，但是无法整除就要在前面腿伸长到余数时补一次移动。

上取整看着不舒服，换掉：$x+1+\left\lfloor\dfrac{a-1}{x}\right\rfloor+\left\lfloor\dfrac{b-1}{x}\right\rfloor$。

考虑 $f(x)=x+1+\dfrac{a-1}{x}+\dfrac{b-1}{x}$ 的极小值如何取到。由均值不等式得到当 $x=\dfrac{a+b-2}{x}$ 有最小值，即 $x=\sqrt{a+b-2}$。

但是原题并非 $f(x)$，是在 $f(x)$ 里面套了些下取整的，这意味着 $f(x)$ 的极值点不一定为原题的最优解，但肯定在附近，于是取 $\left[\sqrt{a+b-2}-100,\sqrt{a+b-2}+100\right]$ 代入求出最小值即可。

---

## 作者：__ikun__horro__ (赞：1)

题目要求从 $(0,0)$ 走到 $(A,B)$ ，而且可以改变步长。我们先要确定一个步长，因为如果 $t_1$ 的步长走几步然后再 $t_2$ 的步长走几步是没有意义的，可以直接用较长的步长替代。

假如步长是 $m$，我们先考虑 $A$ 和 $B$ 都是 $m$ 的倍数的情况，这样所需的步数就是 $\dfrac{A}{m}+\dfrac{B}{m}$，再加上从 $1$ 的步长加到 $m$ 的步长所需的步数 $m-1$，最后加起来就是 $\dfrac{A}{m}+\dfrac{B}{m}+(m-1)$ 步。

然后再考虑 $A$ 或 $B$ 不是 $m$ 的倍数的情况，我们先在 $x$ 坐标走 $\left\lfloor \dfrac{A}{m} \right\rfloor$ 步，然后在 $y$ 坐标走 $\left\lfloor \dfrac{B}{m} \right\rfloor$ 步，我们分别会在 $x$ 和 $y$ 坐标上差 $A\bmod m$ 和 $B\bmod m$ 的距离，那么这段怎么办呢？首先这两段距离肯定小于 $m$，所以我们可以在增加步长时顺便把这段路走掉。最后一共是 $\left\lfloor \dfrac{A}{m} \right\rfloor+1+\left\lfloor \dfrac{B}{m} \right\rfloor+1+(m-1)$。

最后我们把两种情况结合起来，可以得到公式 $\left\lceil \dfrac{A}{m} \right\rceil+\left\lceil \dfrac{B}{m} \right\rceil+(m-1)$。

题目中 $A,B\le10^9$，所以一一便利肯定不行，我们看公式取最小值时 $m$ 是在 $\sqrt{A}$ 左右，所以我们枚举到 $10^5$ 即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T, a, b, ans;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> a >> b;
		ans = a + b;           //初始化 ans 最大值 
		for (int i = 1; i <= 100000; i++) {           //枚举到 10^5 即可 
			ans = min(ans, (a + i - 1) / i + (b + i - 1) / i + (i - 1));   //带入公式 
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
一道暴力题。因为 $t\le100$，所以我们只要循环枚举 $m$ 的最大值就行了。然后贪心，肯定是先把 $m$ 加到最大再移动，除非不能整除了。加 $m$ 需要 $m-1$ 次，移动 $x$ 需要 $\lceil\frac xm\rceil$ 次，移动 $y$ 需要 $\lceil\frac ym\rceil$ 次，总共 $m-1+\lceil\frac xm\rceil+\lceil\frac ym\rceil$ 次，最后取个 $\min$。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
const int x = 5e5;
int t, n, m, minx;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> m;
		minx = 1e9;
		for (int i = 1; i <= x; ++ i)
			minx = min (minx, (n + i - 1) / i + (m + i - 1) / i + i - 1);
		cout << minx << '\n';
	}
	return 0;
}
```

---

## 作者：jr_inf (赞：0)

~~建议降黄~~

令 $m$ 最后的值为 $a$，那么此时最佳答案为 $a-1+ \left \lceil \frac{x}{a} \right \rceil + \left \lceil \frac{y}{a} \right \rceil$，每次加尽量大的 $m$ 一定最优。

当 $x,y$ 增大时，答案显然不降，考虑找到 $a$ 的上界。用 $O(n)$ 的暴力跑极限数据，发现答案不到 $45000$，又发现 $t \leq 100$，所以可以对于每一个点，从 $1$ 到上界 $45000$ 暴力枚举 $a$，即可通过此题。

代码很好写，不放。

------------

不严谨证明：

令 $c=x+y$（上面的 $x,y$）

记 $f(x)=x-1+\frac{c}{x}$（忽略取整符号）

则 $f'(x)=\frac{c}{x^2}-1$

当 $x=\sqrt c$ 时，$f'(x)=0$，此时有最小值 $f(x)=2\sqrt c-1$。


把原来的取整符号加上，最优的 $a$ 的值应该也在 $\sqrt c$ 附近，实测对于所有的测试点，最优的 $a \in [\sqrt c-100,\sqrt c+100]$。

---

