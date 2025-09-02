# Wonderful Lightbulbs

## 题目描述

你是一个无限大灯泡网格的骄傲拥有者，这些灯泡以[笛卡尔坐标系](https://en.wikipedia.org/wiki/Cartesian_coordinate_system)排列。初始时，所有灯泡都处于关闭状态，除了一个灯泡——那里埋藏着你最骄傲的宝藏。

为了隐藏宝藏的位置，你可以执行以下操作任意次数（包括零次）：
- 选择两个整数 $x$ 和 $y$，然后切换位于 $(x,y)$、$(x,y+1)$、$(x+1,y-1)$ 和 $(x+1,y)$ 的 4 个灯泡的状态。换句话说，对于每个灯泡，如果它原本是关闭的就打开它，如果原本是打开的就关闭它。注意 $x$ 和 $y$ 没有任何限制。

最终，有 $n$ 个灯泡处于打开状态，坐标分别为 $(x_1,y_1), (x_2,y_2), \ldots, (x_n,y_n)$。不幸的是，你已经忘记了宝藏最初埋藏的位置，现在需要找出一个可能的宝藏位置。祝你好运！

## 说明/提示

对于第一个测试用例，一种可能的情况是你将宝藏埋在位置 $(2,3)$。然后你没有执行任何操作。

最终，只有位于 $(2,3)$ 的灯泡是打开的。

对于第二个测试用例，一种可能的情况是你将宝藏埋在位置 $(-2,-2)$。然后你执行了 1 次操作，选择 $x=-2$，$y=-2$。

这次操作切换了位于 $(-2,-2)$、$(-2,-1)$、$(-1,-3)$ 和 $(-1,-2)$ 的 4 个灯泡的状态。

最终，位于 $(-2,-1)$、$(-1,-2)$ 和 $(-1,-3)$ 的灯泡是打开的。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
1
2 3
3
-2 -1
-1 -2
-1 -3
7
7 26
6 27
6 28
7 27
8 26
8 27
7 28
11
70 9
69 8
69 0
73 5
70 -1
70 5
71 7
70 4
73 4
71 3
72 3```

### 输出

```
2 3
-2 -2
7 27
72 7```

# 题解

## 作者：Gold14526 (赞：7)

$\rm Problem:$[Wonderful Lightbulbs](https://codeforces.com/contest/2096/problem/D)

被这个 D 吊打了，想了 $40$ 分钟。

### 题意

平面上每个整点初始有权值 $0$，有一个位置有权值 $1$。

每次操作为：选择一个 $(x,y)$，将 $(x,y),(x,y+1),(x+1,y−1),(x+1,y)$ 上的权值异或 $1$。

现在给出若干次操作后权值为 $1$ 的共 $n$ 个点，求初始权值为 $1$ 的点。

$1\le n\le 2\times10^5$

### 做法

不妨这样看待操作的四个点：

![](https://cdn.luogu.com.cn/upload/image_hosting/y8h1sa7e.png)

发现每条竖线，每条斜线的异或和都不会改变。

于是我们找到异或和为 $1$ 的竖线和斜线即可确定初始的点。

### 代码

```cpp
#include<bits/stdc++.h>
#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ush unsigned short
#define cush const unsigned short
using namespace std;
int read()
{
	int num=0,zf=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')zf=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+(ch-'0');
		ch=getchar();
	}
	return num*zf;
}
void print(cint x)
{
	if(x<10)
	{
		putchar(x+'0');
		return;
	}
	print(x/10);
	putchar(x%10+'0');
}
void princh(cint x,const char ch)
{
	if(x<0)
	{
		putchar('-');
		print(-x);
		putchar(ch);
		return;
	}
	print(x);
	putchar(ch);
}
int n;
map<int,bool>X,Y;
int x[200001],y[200001];
int ansx,ansy;
void solve()
{
	n=read();
	X.clear();
	Y.clear();
	for(int i=1;i<=n;++i)
	{
		x[i]=read();
		y[i]=read();
		X[x[i]]^=1;
		Y[x[i]+y[i]]^=1;
	}
	for(int i=1;i<=n;++i)
	{
		if(X[x[i]])ansx=x[i];
		if(Y[x[i]+y[i]])ansy=x[i]+y[i];
	}
	princh(ansx,' ');
	princh(ansy-ansx,'\n');
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：0)

我们来讲一下怎么写这个 validator。出题人为啥不会写 validator 然后把 hack 关了。

首先，我们把这个平行四边形的操作平移成正方形。然后这样我们发现把一个正方形平移的操作和重复的线性组合的操作看起来很像卷积，所以我们尝试使用多项式建模。

所以我们有空间
$$
S = \mathbb F_2^{\oplus\mathbb Z^2} = \mathbb F_2[X^{\pm 1}, Y^{\pm 1}],
$$
单次操作
$$
X^n Y^m (X+1)(Y+1),
$$
多次操作
$$
(X+1)(Y+1)S,
$$
因此一个状态的标准型为 $S/(X+1)(Y+1)S$。考虑同态
$$
\varphi : S \to S/(X+1) \oplus S/(Y+1), \quad f \mapsto (f(1, \cdot), f(\cdot, 1)).
$$
有
$$
\ker \varphi = (X+1)(Y+1)S, \quad \operatorname{im} \varphi = \{(f, g) \in S/(X+1) \oplus S/(Y+1) : f(1) = g(1)\}.
$$
因此
$$
S/(X+1)(Y+1)S \simeq \{(f, g) \in S/(X+1) \oplus S/(Y+1) : f(1) = g(1)\}.
$$
不难发现 $f \bmod (Y+1) = g \bmod (X+1)$。因此这个环同构于
$$
\mathbb F_2 \oplus (X+1) \mathbb F_2[X^{\pm 1}] \oplus (Y+1) \mathbb F_2[Y^{\pm 1}].
$$

然后，$X^n Y^m$ 在其中的像为
$$
\begin{aligned}
X^nY^m \bmod (X+1)(Y+1) S &= 1 \\
&+ (X+1) G(X, n) \\
&+ (Y+1) G(Y, n),
\end{aligned}
$$
其中
$$
G(X, n) = \begin{cases}
\displaystyle \sum_{k=0}^{n-1} X^k & n > 0, \\
\displaystyle \sum_{k=-n}^{-1} X^k & n \le 0.
\end{cases}
$$
因此我们对于输入的 $(x, y)$，计算出 $X^xY^y$ 的像的和就行了。然后发现这些像都形如一个区间求和。因此考虑差分。这样我们得到一个最后的差分数组 $\delta_X, \delta_Y$。

我们知道，这个 $S/(X+1)(Y+1)S$ 的标准型是某一个 $X^xY^y$ 当且仅当 $\delta_X, \delta_Y$ 种均至多两项为 $1$（注意，$G(X,0) = 0$），且 $n \equiv 1 \pmod 2$。对于 $\delta_X$ 的 $1$ 项 $\alpha, \beta$，其中必有一个为 $0$，而另一个是所求 $x$ 的值。同理可得所求 $y$ 的值。而注意到 $n \equiv 1 \pmod 2$ 时，$0$ 那一项一定为 $1$，无需讨论。因此，我们同时完成了 validator 和 solution 的任务。

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n;
    m = n;
    map<int, bool> mp0, mp1, mp2, mp3;
    for (int x, y; n--;) cin >> x >> y, mp0[x] ^= 1, mp1[x + y] ^= 1;
    auto x_v = find_if(mp0.begin(), mp0.end(), [](auto &x) { return x.second; })
                   ->first,
         y_v = find_if(mp1.begin(), mp1.end(), [](auto &x) {
                   return x.second;
               })->first;
    auto x_n =
             count_if(mp0.begin(), mp0.end(), [](auto &x) { return x.second; }),
         y_n =
             count_if(mp1.begin(), mp1.end(), [](auto &x) { return x.second; });
    assert(x_n <= 1 && y_n <= 1);
    cout << x_v << " " << y_v - x_v << "\n";
}

int main() {
    int t;
    for (cin >> t; t; t--) solve();
}
```

---

