# [POI 2005] SKO-Knights

## 题目描述

一个骑士在一个无限的棋盘上移动。它可以执行的每一个动作都必须由一对整数 $(a,b)$ 来描述——表示这个骑士可以从 $(x,y)$ 移动到 $(x+a,y+b)$ 或者 $(x-a,y-b)$ 。每个骑士都有一组这样的移动描述，表示了骑士可以做出的移动。我们假设每一个骑士从 $(0,0)$ 出发移动到的所有位置不共线。

如果他们能从 $(0,0)$ 到达完全相同的坐标，我们就说两个骑士是等价的。(让我们指出，相同的骑士可以在不同的动作中到达这些方块)。可以看出，对于每一个骑士，都存在一对$(a,b)$，其移动仅由两对数字来描述。

你的任务是写一个程序，读入对骑士移动的表示，确定两对表示等价的骑士移动的整数，并输出这两对整数。


## 样例 #1

### 输入

```
3
24 28
15 50
12 21```

### 输出

```
3 0
0 1```

# 题解

## 作者：Alex_Wei (赞：14)

- Update on 2022.11.30：修改笔误。
- Update on 2025.1.22：修订。

### *[P3421 [POI2005] SKO-Knights](https://www.luogu.com.cn/problem/P3421)

题目要求我们找到两个向量 $d, e$，使得它们的 **整系数** 线性组合得到的线性空间（张成）等于给出的所有向量的整系数张成。

记 $\mathrm{span}(S)$ 表示集合 $S$ 的整系数张成，即
$$
\mathrm{span}(S) = \left\{\sum\limits_{a_i\in S} c_ia_i :c_i\in \mathbb{Z}\right\}
$$

*Sol 1*

如果我们能将三个向量 $a, b, c$ 合并成等价的两个向量 $d, e$，就能解决本题。根据基础的线性代数知识，不改变张成的初等行变换有三种：

- 交换：对应本题即任意交换 $a, b, c$。
- 倍乘：对应本题即乘以任意非 $0$ 整数。
- 倍加：对应本题即向量加上任意整数倍其它向量。

当然，上述性质仅在 **实系数** 线性组合的前提下成立。当要求系数为 **整数** 时：

- 交换显然不改变张成。
- 倍乘变换 **可能改变** 张成，因为整数乘法不可逆。如 $\mathrm{span}\{(0, 1), (1, 0)\}$ 显然不等于 $\mathrm{span}\{(0, 2), (1, 0)\}$。
- 倍加变换 **不改变** 张成。对任意 $p = y(a + xb) + zb\in \mathrm{span}(a + xb, b)$，它仍是 $a, b$ 的整系数线性组合 $ya + (xy + z)b$。对任意 $p = ya + zb \in \mathrm{span}(a, b)$，我们也总可以将其表示为 $a + xb$ 和 $b$ 的整系数线性组合 $y(a + xb) + (z - xy) b$。

很好！如果整系数倍加变换不改变整系数张成，就可以使用 **辗转相减法**。

具体地，考虑两个向量 $a, b$，我们能够在不改变其整系数张成的前提下，将 $b$ 的某一维变为 $0$。只需对 $a, b$ 在这一维进行辗转相减法即可。

考虑三个向量 $a, b, c$，我们对 $a, b$ 在 $x$ 这一维进行辗转相减，再对 $a, c$ 在 $x$ 这一维进行辗转相减。此时 $x_b, x_c$ 均为 $0$，意味着 $b, c$ 共线。因此，对 $b, c$ 在 $y$ 这一维进行辗转相减，即 $y_b\gets \mathrm{gcd}(y_b, y_c)$，此时 $c$ 变成零向量，对 $\mathrm{span}(a, b, c)$ 没有贡献，可以直接舍去，即此时 $\mathrm{span}(a, b, c) = \mathrm{span}(a, b)$。

综上，我们在 $\mathcal{O}(n\log V)$ 的时间内解决了问题，其中 $V$ 是值域。

注意题目限制坐标绝对值不超过 $10 ^ 4$。辗转相减法得到最终的 $a$ 时，$x_a$ 和 $y_b$ 是原坐标的 $\gcd$，显然满足坐标限制。但 $y_a$ 不一定，因此要对 $y_b$ 取模，相当于做了一步辗转相减（此时 $x_b = 0$ 所以不需要改变 $x_a$）。最终得到的坐标绝对值不超过 $10 ^ 2$，比题目限制优一个数量级。

从上述过程中，我们发现一个有趣的性质：整系数意义下，两个向量可以在不改变其张成的前提下，使其中一个向量的某一维变成 $0$，而另一个向量的对应维变成原来两个向量在这一维上的 $\gcd$。这也是解决本题的关键性质。

*Sol 2*

让我们深入地钻研一下题解区的其它做法。

实际上两者的核心思想是等价的：将两个向量的其中一个的某一维变成 $0$，另一个的对应维变成 $\gcd$。不同点在于，线性代数做法是从倍加变换和辗转相除法推得该性质，即我们使用正确性有保证的方法，最终得到的结果是这样的性质。而题解区的做法是首先令这一条件成立，再根据得到的线性方程组，使用 exgcd 和一些数学推导求解。这体现了 exgcd 与辗转相除的本质联系。

不妨设对于向量 $a, b$，我们要将 $x_b$ 变为 $0$。则 $x_{a'}$ 只能等于 $d_x = \gcd(x_a, x_b)$（不管 $y$ 坐标，由裴蜀定理，能达到的 $x$ 坐标恰为 $d_x$ 的所有倍数）。因此，对于方程 $x_ax + x_by = d_x$，使用 [扩展欧几里得](https://www.cnblogs.com/alex-wei/p/Number_Theory.html) 算法求得一组特解 $(x_0, y_0)$，则 $y_{a'} = y_ax_0 + y_by_0$，因为 $a' = x_0a + y_0b$。

对于 $b'$，观察到 $a'$ 的通解为 $(x_0 + k\frac {x_b} {d_x}, y_0 - k\frac {x_a} {d_x})$，所以保持 $x_{a'} = d_x$ 不变，$y_{a'}$ 的最小变化量为 $\frac {y_a x_b} {d_x} - \frac {y_b x_a}{d_x}$，即让 $k$ 加 $1$ 对 $y_{a'}$ 产生的变化量。因为 $x_{b'} = 0$，所以 $y_{b'}$ 只能等于这个最小变化量。可以验证这样得到的 $a', b'$ 符合要求。

综上，我们将 $a, b$ 写成了 $a', b'$，其中 $x_{a'} = \gcd(x_a, x_b)$，$y_{a'}$ 用 exgcd 求解，$x_{b'} = 0$，$y_{b'} = \frac{y_ax_b - x_ay_b}{\gcd(x_a, x_b)}$。对 $a, c$ 的 $y$ 坐标做类似的操作，再合并 $b, c$ 即可。

*Sol 3*

另一种求解 $y_{b'}$ 的思路（来源 [TheLostWeak 的博客](https://www.cnblogs.com/chenxiaoran666/p/Luogu3421.html)）：$a', b'$ 可以整系数线性组合出 $a, b$。

考虑 $a'$。因为 $x_{a'} = \gcd(x_a, x_b)$，所以为了使横坐标等于 $x_a$，需要将 $a'$ 乘以 $\frac{x_a}{\gcd(x_a, x_b)}$ 即 $\frac{x_a}{x_{a'}}$ 的系数，得到 $(x_a, \frac{x_ay_{a'}}{x_{a'}})$。因为可以通过向量 $b' = (0, y_{b'})$ 得到 $(x_a, y_a)$，因此 $y_{b'}  \mid \ y_a - \frac{x_ay_{a'}}{x_{a'}}$ 。同理 $y_{b'} \mid \ y_b - \frac{x_by_{a'}}{x_{a'}}$。因此
$$
y_{b'} = \frac {\gcd(y_ax_{a'} - x_a y_{a'}, y_bx_{a'} - x_by_{a'})} {x_{a'}} 
$$
若 $y_{b'}$ 小于上述 $\gcd$，将导致存在 $p\in \mathrm{span}(a', b')$，$p\notin \mathrm{span}(a, b)$。若 $y_{b'}$ 大于上述 $\gcd$，$a', b'$ 无法整系数线性组合出 $a, b$ 中的至少一个。

抛砖引玉：联立后两种方法描述 $y_{b'}$ 的式子，稍作化简后得到等式
$$
y_ax_b - x_ay_b = \gcd(y_ax_{a'} - x_a y_{a'}, {y_bx_{a'} - x_by_{a'}})
$$

下方是线性代数辗转相除法的代码，非常容易理解。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100 + 5;
int n, a[N], b[N];
int main() {
	cin >> n >> a[1] >> b[1];
	for(int i = 2; i <= n; i++) {
		cin >> a[i] >> b[i];
		while(a[i]) {
			if(abs(a[1]) < abs(a[i])) swap(a[1], a[i]), swap(b[1], b[i]);
			else b[1] -= b[i] * (a[1] / a[i]), a[1] %= a[i];
		} if(i > 2) b[2] = __gcd(b[2], b[i]), b[1] %= b[2];
	} cout << a[1] << " " << b[1] << endl << a[2] << " " << b[2] << endl;
	return 0;
}
```

---

## 作者：ql12345 (赞：4)

直接看公式过于抽象

**总体思路**：每次找出两个向量合并为一个竖直向量和另一个向量，将竖直向量和已有竖直向量合并为一个纵坐标为gcd的竖直向量，初始竖直向量不存在

如下 ~~（网上找的）~~ 图：

![](https://cdn.luogu.com.cn/upload/image_hosting/51vk0yl4.png)

我们要找出两个绿色向量使得这两个向量与当前的两个向量等价

转换思路：“等价”即满足：横坐标上的所有位置都可以到达，并且同一纵坐标上的位置都可以到达

说明：句中“位置”指当前两个原向量可以到达的点

证明：如果可以到达一个横坐标上的位置，且可以从这个横坐标的位置到达所有同一横坐标的位置则说明所有点都可以到达

可能还是不大清楚，先看怎样找这两个向量，满足上面目标

竖直向量可以让我们满足第二条，竖直向量的纵坐标就为同一横坐标上相邻点纵坐标的差，假设两个原向量为**v1** = (a1,b1)和**v2** = (a2,b2)，显然a2**v1** - a1**v2**在y轴上，也就是与**0**同一横坐标，但这个点不一定与原点相邻，显然a1和a2互质时，它们才相邻，所以这个纵坐标除以一个gcd(a1,a2)即可

于是竖直向量$ = (0, abs(a1 \times b2 - a2 \times b1) / gcd(a1, a2))$

剩下一个向量显然将原点带到每一个横坐标即可，所以它的横坐标显然是gcd(a1,a2)，纵坐标呢？过原点，随便找一个位置即可连出一条直线，得到斜率，即可计算出纵坐标

即$a1 \times x + a2 \times y = gcd(a1,a2)$，将x和y带入求得纵坐标：$b1 \times x + b2 \times y$

#### Code：

```cpp
const int N = 105;

void exgcd(re int a, re int b, re int &x, re int &y)
{
	if(!b) x = 1, y = 0;
	else exgcd(b, a%b, y, x), y -= a/b * x;
}

int n, a[N], b[N];

inline void solve(re int x1, re int y1, re int &x2, re int &y2, re int &y)
{
	if(! x1)
		y = y1;
	if(! x2)
		y = y2, x2 = x1, y2 = y1;
	else
	{
		int d = __gcd(x1, x2);
		y = abs(x2 * y1 - x1 * y2) / d;
		int xx, yy, aa = x1 / d, bb = x2 / d;
		exgcd(aa, bb, xx, yy);
		y2 = y1 * xx + y2 * yy;
		x2 = d;
	}
}

signed main()
{
	n = read();
	for(re int i = 1;i <= n; ++i) a[i] = read(), b[i] = read();
	re int x = a[2], y = b[2], y1, y2;
	solve(a[1], b[1], x, y, y2);
	for(re int i = 3;i <= n; ++i)
	{
		y1 = y2;
		solve(a[i], b[i], x, y, y2);
		y2 = __gcd(y1, y2);
	}

	print(x), putchar(' '), print(y), putchar('\n'), print(0), putchar(' '), print(y2);

	return 0;
}
```

---

## 作者：nofall (赞：1)

因为LATEX挂了，所以重新交一遍

### 分析

![](https://images2018.cnblogs.com/blog/1254625/201808/1254625-20180807130015589-1123985450.png)

我们设原向量为$(a_1, b_1)$,$(a_2, b_2)$。
设新向量为$(a_3, b_3)$，$(0, a_4)$

$\therefore$ $a_3=gcd(a_1,a_2)$

$\therefore$ $a_1x + a_2y = a_3$

$\therefore$ $a_1x + a_2y = gcd(a_1,a_2)$   $b_1x + b_2y = b_3$

$\begin{cases}a_1x + a_2y = 0\\b_1x + b_2y = b_4\end{cases}$ 
 
$\therefore$ $-y = \dfrac{a_1x}{a_2}$

$\because$ $-y$是整数

$\therefore$ $a_2|a_1x$

即$\dfrac{a_2}{gcd(a_1,a_2)}|\dfrac{a_1}{gcd(a_1,a_2)x}$

又$\therefore$ $\dfrac{a_2}{gcd(a_1,a_2)}|\dfrac{a_1}{gcd(a_1,a_2)x}$互质

$\therefore$$\dfrac{a_2}{gcd(a_1,a_2)}|x$

设$x=\dfrac{a_2}{gcd(a_1,a_2)}$

$\therefore$ $-\dfrac{a_1}{gcd(a_1,a_2)}$

$\therefore$ $b_4 = \dfrac{|b_1a_2-b_2a_1|}{gcd(a_1,a_2)}$

我们只需要不断的将向量转变到y轴上使得最终至多一个向量不再y轴上就行了。

代码:

```cpp
#include <cstdio>
int a[510], b[510];
template<class type>type _gcd(type __, type ___) {
	return (!___) ? __ : _gcd(___, __ % ___);
}
template<class type>type _abs(type __) {
	return __ < 0 ? -__ : __;
}
inline void exgcd(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a%b, x, y);
	int z = x;
	x = y;
	y = z - (a / b)*y;
}
int main() {
	int n, m, x, y;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i], &b[i]);
	int a1, b1, a2, b2;
	if (!a[1]) { a1 = a[2]; b1 = b[2]; b2 = b[1]; }
	else if (!a[2]) { a1 = a[1]; b1 = b[1]; b2 = b[2]; }
	else { a1 = _gcd(a[1], a[2]); exgcd(a[1] / a1, a[2] / a1, x, y); b1 = b[1] * x + b[2] * y; b2 = _abs(b[1] * a[2] - b[2] * a[1]) / a1; }
	for (int i = 3; i <= n; i++) {
		if (!a1) { a1 = a[i]; b2 = _gcd(b2, b1); b1 = b[i]; }
		else if (!a[i])b2 = _gcd(b2, b[i]);
		else { int be = a1, be2 = b1; a1 = _gcd(a1, a[i]); exgcd(be / a1, a[i] / a1, x, y); b1 = b1 * x + b[i] * y; b2 = _gcd(b2, _abs(be2*a[i] - b[i] * be) / a1); }
	}
	printf("%d %d\n", a1, b1);
	putchar('0'), putchar(' ');
	printf("%d\n", b2);
	return 0;
}
```

码风较丑，见谅

---

