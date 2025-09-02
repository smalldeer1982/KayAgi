# [ABC228H] Histogram

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc228/tasks/abc228_h

長さ $ N $ の整数列 $ A\ =\ (A_1,\ \dots,\ A_N) $ および $ C\ =\ (C_1,\ \dots,\ C_N) $ が与えられます。

あなたは以下の操作を好きな回数（$ 0 $ 回でもよい）行うことができます。

- $ 1\ \leq\ i\ \leq\ N $ を満たす整数 $ i $ を選び、$ A_i $ の値を $ 1 $ 増やす。このとき、$ C_i $ 円の費用を支払う。

好きな回数の操作を行ったあと、$ A $ の要素の種類数を $ K $ として、$ K\ \times\ X $ 円を支払わなければなりません。

支払う金額の合計は最小で何円ですか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ X\ \leq\ 10^6 $
- $ 1\ \leq\ A_i,\ C_i\ \leq\ 10^6\ \,\ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数である。

### Sample Explanation 1

$ A_1 $ に $ 1 $ 加算すると $ A $ の要素の種類数は $ 2 $ になり、支払う金額の合計は $ C_1\ +\ 2\ \times\ X\ =\ 12 $ 円となります。支払う金額をこれより少なくすることはできません。

## 样例 #1

### 输入

```
3 5
3 2
2 4
4 3```

### 输出

```
12```

## 样例 #2

### 输入

```
1 1
1 1```

### 输出

```
1```

## 样例 #3

### 输入

```
7 7
3 2
1 7
4 1
1 8
5 2
9 8
2 1```

### 输出

```
29```

# 题解

## 作者：Fido_Puppy (赞：7)

$$\texttt{Description}$$

[[ABC228H] Histogram](https://www.luogu.com.cn/problem/AT_abc228_h)

给定一个长度为 $N$ 的数组 $A_1, A_2, \cdots, A_N$ 和一个长度为 $N$ 的数组 $C_1, C_2, \cdots, C_N$。

可以进行任意次如下操作：

选择一个下标 $i$，将 $A_i$ 加 $1$，此次操作花费代价 $C_i$。

在操作完之后，你需要额外花费 $K \times X$ 的代价，其中 $K$ 表示操作完后 $A$ 数组中不同数字的个数，$X$ 为一个给定的数。

$$\texttt{Solution}$$

我们先按 $A$ 数组从小到大排序，然后可以考虑 $\text{DP}$。

容易发现最优方案一定是把 $A$ 数组排序后分成若干段，每一段都把段内的数加到段内最大值。

由于按 $A$ 数组从小到大排序了，所以区间 $[L, R]$ 的最大值为 $A_R$。

设 $f_i$ 表示前 $i$ 个数分段后产生的最小代价，则可以列出转移方程：

$$f_i = \min_{j = 0}^{j < i} \{ f_j + \left(\sum_{k = j + 1}^i C_k \times (A_i - A_k)\right) + x \}$$

把转移方程中间部分提出来：

$$\sum_{k = j + 1}^{i} C_k \times (A_i - A_k) = A_i \times \sum_{k = j + 1}^{i} C_k - \sum_{k = j + 1}^{i} C_k \times A_k$$

可以预处理出前缀和数组 $sum, sumC$，其中：

$$sum_i = \sum_{j = 1}^i C_j \times A_j$$

$$sumC_i = \sum_{j = 1}^i C_j$$

转移方程就变成了如下形式：

$$f_i = \min_{j = 0}^i \{ f_j + A_i \times (sumC_i - sumC_j) - sum_i + sum_j + x \}$$

显然可以斜率优化，具体可以参考 [P3195 [HNOI2008]玩具装箱](https://www.luogu.com.cn/problem/P3195)。

```cpp
#include <bits/stdc++.h>

int main() {
    std :: ios_base :: sync_with_stdio(false);
    std :: cin.tie(nullptr);

    std :: istream &fin = std :: cin;
    std :: ostream &fout = std :: cout;

    int n, x;
    fin >> n >> x;

    std :: vector < std :: pair <int, int> > a(n + 1);
    for (int i = 1; i <= n; ++i) {
        fin >> a[i].first >> a[i].second;
    }

    using ll = long long;

    std :: sort(a.begin() + 1, a.begin() + n + 1);
    std :: vector <ll> f(n + 1), sum(n + 1), sc(n + 1);

    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[ i - 1 ] + 1ll * a[i].first * a[i].second;
        sc[i] = sc[ i - 1 ] + a[i].second;
    }

    std :: vector <int> q(n + 1);
    int head = 1, tail = 1; q[1] = 0;

    auto slope = [&] (int i, int j) {
        return 1.0 * (f[j] + sum[j] - f[i] - sum[i]) / (sc[j] - sc[i]);
    };

    for (int i = 1; i <= n; ++i) {
        while (head < tail && slope(q[head], q[ head + 1 ]) < a[i].first) ++head;
        f[i] = f[ q[head] ] + x + (sc[i] - sc[ q[head] ]) * a[i].first - sum[i] + sum[ q[head] ];
        while (head < tail && slope(q[ tail - 1 ], q[tail]) >= slope(q[tail], i)) --tail;
        q[ ++tail ] = i;
    }

    fout << f[n] << '\n';

    return 0;
}
```

$$\texttt{Thanks for watching!}$$

---

## 作者：panxz2009 (赞：4)

## 题意简述
给定两个正整数序列 $A$ 与 $C$ , 你可以做任意次操作, 每次操作你可以花费 $C_i$ 的代价给 $A_i$ 加上 $1$ .  
设操作完后的序列 $A$ 有 $K$ 个不同的元素, 这会造成 $K\times X$ 的代价, 其中 $X$ 为给定常数.  
最小化总代价.
## 解题思路
首先，可以得到一个初步直接的贪心策略：两数数值越接近，就越应该将他们修改成一样的值。由于题中所给操作只能加，那么设两数分别为 $i,j$，其中 $i< j$，则贡献为 $j-i$。  
这么讲可能略显抽象，具体的，先将序列 $A$ 升序排序，目标就是将序列分成若干段，将每段的值全部变为此段的最大值。  
假设分成 $K$ 段，每段的右端点下标记录在 $p$ 数组，那么最终代价为 $\sum_{j = 1}^{K} \sum_{t = p_{j - 1} + 1}^{p_j}((a_{p_j} - a_t)\times c_t) +K\times X$。  
但是如果大力求这个式子复杂度过高，应该优化。

考虑 DP。设 $f_{i}$ 表示序列 $A$ 前 $i$ 个数在若干次操作后得到的最小总代价，注意此处的序列 $A$ 已经过升序排序。  
朴素转移：
$$f_i = \min_{0\le j < i}\{f_{j-1}+\sum_{t = j}^{i}(a_{i} - a_t)\times c_t+x\}$$
令 $s_i=\sum_{j=1}^i c_j$，同时令 $p_i=\sum_{j=1}^i a_j\times c_j$，那么上述转移可化为：
$$\begin{aligned}
f_i &= \min_{0\le j < i}\{f_{j-1}+(a_i\times \sum_{t = j}^{i}c_t) - (\sum_{t = j}^{i}a_t\times c_t)+x\}\\
    &= \min_{0\le j < i}\{f_{j-1}+a_i\times (s_i-s_{j-1}) - (p_i - p_{j - 1})+x\}
\end{aligned}$$
化简到这一步，看到形如 $f_i = \min_{0\le j < i}\{f_{j-1}+val(j,i)\}$ 的式子，有三种套路的化简方式：
- 单调队列。但 $val(j,i)$ 的每一项都必须只关于 $i$ 或 $j$，显然不满足本转移方程。
- 决策单调性。需要证明 $val(j,i)$ 满足四边形不等式，~~可能可以用在本题，但是我不是很会~~。
- 斜率优化。

那么接下来就是斜率优化的套路化简了。  
先去掉 $\min$，即
$$\begin{aligned}
f_i &= f_{j-1}+a_i\times (s_i-s_{j-1}) - (p_i - p_{j - 1})+x\\
    &= f_{j-1}+a_i\times s_i-a_i\times s_{j-1} - p_i + p_{j - 1}+x\\
    &= f_{j}+a_i\times s_i-a_i\times s_{j} - p_i + p_{j}+x
\end{aligned}$$
然后移项：
$$\begin{aligned}
f_i -a_i\times s_i+a_i\times s_{j}+ p_i-x &= f_{j}  + p_{j}
\end{aligned}$$
整理：
$$\begin{aligned}
f_{j}  + p_{j} &= a_i\times s_{j} + f_i -a_i\times s_i+ p_i-x
\end{aligned}$$
那么可以看作一个斜率为 $a_i$，$x$ 轴表示 $s_j$，$y$ 轴表示 $f_j+p_j$ 的一次函数，维护下凸壳即可。  
然后就是单调队列维护。  
如果你不会单调队列做斜率优化，可以先做一做[模板题](https://www.luogu.com.cn/problem/P5785)。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch))
	{
		if(ch == '-')
			f = -1;
		ch = getchar();
	}
	while(isdigit(ch))
	{
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
const int maxn = 2e5 + 10;
int n, x, s[maxn], p[maxn], f[maxn];
int q[maxn], head, tail;
struct node {
	int a, c;
	bool operator < (const node &y) const {
		return a < y.a;
	}
}num[maxn];
int val(int i, int j)
{
	return f[j] + (s[i] - s[j]) * num[i].a - (p[i] - p[j]) + x;
}
double K(int x, int y)
{
	return 1.0 * (f[x] + p[x] - f[y] - p[y]) / (s[x] - s[y]);
}
signed main()
{
	n = read(), x = read();
	for(int i = 1; i <= n; i++)
	{
		num[i].a = read(), num[i].c = read();
	}
	sort(num + 1, num + 1 + n);
	for(int i = 1; i <= n; i++)
	{
		s[i] = s[i - 1] + num[i].c;
		p[i] = p[i - 1] + num[i].c * num[i].a;
	}
	head = 1, tail = 0;
	q[++tail] = 0;
	for(int i = 1; i <= n; i++)
	{
		while(head < tail && K(q[head + 1], q[head]) <= num[i].a) head++;
		f[i] = val(i, q[head]);
//		printf("f[%lld] = %lld\n", i, f[i]);
		while(head < tail && K(q[tail - 1], q[tail]) >= K(q[tail], i)) tail--;
		q[++tail] = i;
	}
	printf("%lld\n", f[n]);
	return 0;
}
```

---

## 作者：Reunite (赞：2)

比较套路的题。

## 一
---

直接做肯定是不行的，根据这种在数值上有贡献的题，套路地把 $A_i$ 升序排一下，然后我们来找性质。

- 最终序列的每一个值都在原序列中出现过。否则肯定可以把每个值向下调整。

- 若最后 $A_i$ 调整为 $A_i'$，则 $\forall j,A_j \in[A_i,A_i'],A_j'=A_i'$。因为最终序列已经存在 $A_i'$ 了，$A_j$ 只需调整到最近的存在于最终序列的值即可。

上面两个性质可以推出，最终的序列一定是形如把排序后的 $A_i$ **划分**成若干段，每一段都调整到其最大值。

因此可以列出 dp 转移方程：

$$f_i=\min\limits_{j<i}f_j+val(j+1,i)$$

若记 $S1_i=\sum_i A_iC_i$，$S2_i=\sum_i C_i$，$a=A_i$，则可写为：

$$f_i=\min \limits_{j<i}f_j+S1_j-S1_i+a(S2_i-S2_j)$$

直接做是 $n^2$ 的，注意到排序后，$a$ 单调不降，且转移可以写成 $kx+b$ 的形式，所以可以使用斜率优化降到 $O(n)$。

---
## 二
---

我相信大家都会斜率优化，所以我就不讲斜率优化了。

时空复杂度 $O(n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;

int n,x;
int f[200005];
int q[200005];
int s1[200005];
int s2[200005];
pair <int,int> a[200005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline int X(int i){return s2[i];}
inline int Y(int i){return f[i]+s1[i];}

inline double slope(int i,int j){return X(i)==X(j)?1e18:1.*(Y(i)-Y(j))/(X(i)-X(j));}

signed main(){
	in(n),in(x);
	for(int i=1;i<=n;i++) in(a[i].first),in(a[i].second);
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++) s1[i]=s1[i-1]+a[i].first*a[i].second,s2[i]=s2[i-1]+a[i].second;
	int h=1,t=1;
	for(int i=1;i<=n;i++){
		f[i]=1e18;
		int a=::a[i].first;
		while(h<t&&slope(q[h],q[h+1])<a) h++;
		int j=q[h];
		f[i]=(f[j]+s1[j])-a*s2[j]+a*s2[i]+x-s1[i];
		while(h<t&&slope(q[t],i)<slope(q[t-1],i)) t--;
		q[++t]=i;
	}
	printf("%lld\n",f[n]);

	return 0;
}
```

---

## 作者：Z1qqurat (赞：2)

我想把它当作斜率优化 dp 的板子来讲解一下斜优 dp，顺便解释下原理。那啥看到有人说他不太会 Slope 相关是吧，这位大哥记得点个赞（

首先将 $a$ 排序，那么会发现 $a$ 最后一定是一段一段相同的，然后靠后的段比靠前的段大。这东西显然可以 dp 啊，考虑设 $f_i$ 表示将前 $i$ 个数处理好了的最小贡献，那么显然有：
$$
f_i = \min\limits_{0 \le j < i} f_j + \sum\limits_{k = j + 1} ^ {k = i} (c_k \times (a_i - a_k) + x)
$$
你把式子拆拆拆，设 $sum1_i = \sum\limits_{j = 1} ^ {i} c_j, sum2_i = \sum\limits_{j = 1} ^ {i} c_j \times a_j$，发现右边是：
$$
f_j + a_i \times(sum1_i - sum1_j) - sum2_i + sum2_j + x
$$


再拆拆。
$$
a_i \times sum1_i - sum2_i + x + (-a_i \times sum1_j + f_j + sum2_j)
$$


可以发现后面那一坨很斜率优化，考虑设 $X_i = sum1_i, Y_i = f_i + sum2_i$。假设 $j_1 < j_2$ 且决策点 $j_2$ 优于 $j_1$，那么：
$$
Y_{j_1} - a_{j_1} \times X_{j_1} > Y_{j_2} - a_{i} \times X_{i}
$$
又因为 $j_1 < j_2$，所以 $X_{j_1} < X_{j_2}$，
$$
Y_{j_1} - Y_{j_2} > a_{i} \times (X_{j_1} - X_{j_2})
$$
所以就是 $\frac{Y_{j_1} - Y_{j_2}}{X_{j_1} - X_{j_2}} < a_i$。而 $\operatorname {slope}(j_1, j_2) = \frac{Y_{j_1} - Y_{j_2}}{X_{j_1} - X_{j_2}}$，这玩意儿就是斜率优化。

$f$ 是凸的，考虑用双端队列给 $f$ 维护下凸壳。那么当我们加入点 $i$ 的时候：

* 弹出无用的队首，如果 $head + 1$ 优于 $head$（是对于 $i$ 的决策而言），那么可以毫不留情地把 $head$ 删掉了：这种时候直接判 $\operatorname{slope}(head, head + 1) < a_i$ 就可以了。（注意，$\operatorname{slope}(j_1, j_2) < a_i$ 是正确的判定 $j_2$ 优于 $j_1$ 的条件，需要满足 $j_1 < j_2$。）

* 弹掉无用的队尾。自然会将 $i$ 放进队尾，所以拿队尾 $tail$ 和 $i$ 比较。如果 $\operatorname{slope}(tail - 1, tail) \ge \operatorname{slope}(tail, i)$，那在中间当电灯泡的 $tail$ 没点用，直接删掉。这个看图：

  ![](https://pic.imgdb.cn/item/650814f6204c2e34d39a77f4.png)

  如果是这样，就完全没必要把 $tail$ 留下来了不是吗！

* 最后你只需要用 $head$ 的值来更新 $f_i$ 就可以了。

希望能让你明白斜率优化 dp！这里强推[这篇](https://www.cnblogs.com/Xing-Ling/p/11210179.html)！

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
using namespace std;
const int N = 2e5 + 5;
int n, k, q[N], head = 1, tail = 1;
ll sum1[N], sum2[N], f[N];
struct Rinne{
    int a, c;
    bool operator<(const Rinne &d) const{
        return a < d.a;
    }
}b[N];

db X(int i) {
    return sum1[i];
}

db Y(int i) {
    return f[i] + sum2[i];
}

db slope(int i, int j) {
    return 1.0 * (Y(j) - Y(i)) / (X(j) - X(i));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
    cin >> n >> k;
    head = tail = 1;
    for (int i = 1; i <= n; ++i) cin >> b[i].a >> b[i].c;
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; ++i) {
        sum1[i] = sum1[i - 1] + b[i].c;
        sum2[i] = sum2[i - 1] + (ll)b[i].a * b[i].c;
    }
    for (int i = 1; i <= n; ++i) {
        while(head < tail && slope(q[head + 1], q[head]) < b[i].a) head++;
        int j = q[head];
        f[i] = f[j] + (ll)b[i].a * (sum1[i] - sum1[j]) - sum2[i] + sum2[j] + k;
        while(head < tail && slope(q[tail - 1], q[tail]) >= slope(q[tail], i)) tail--;
        q[++tail] = i;
    }
    cout << f[n] << "\n";
    return 0;
}
```



---

## 作者：_HCl_ (赞：1)

非常巧妙的一道题。（可能是因为我太菜了才会觉得巧妙吧） 
# ABC228H 题解

**题意简述**

给定序列 $A$ 与 $C$，每次操作可以选择 $i$，并给 $A_i$ 加上 $1$，代价是 $C_i$。若干次操作后的 $A$ 中若有 $K$ 个不同是数，则需再付出 $KX$ 的代价，其中 $X$ 是常数。最小化总代价。

**思路引导**

首先考虑，经过操作后的 $A$ 有 $K$ 个不同的数，$A$ 具有什么性质？容易想到，经过排序后，$A$ 可以被分成 $K$ 段，每一段内的数相同。

由此可以想到，先将 $A$ 排序，考虑将其分成若干段，通过操作使其每一段内数相同，即将每个数都变成区间中的最后一个数（最大的数）。这种分段计算代价的问题是我们所熟悉的。

设 $f_i$ 表示考虑到第 $i$ 位，且第 $i$ 位是段的终点，需要的最小代价。可以列出如下转移方程：

$$
f_i=\min{\{f_j+\sum_{k=j+1}^i(A_i-A_k)C_k+x\}}
$$

中间的求和可以使用前缀和 $\mathcal{O}(1)$ 处理。设 $SumC_i=\sum\limits_{k=1}^i C_i$，$Sum_i=\sum\limits_{k=1}^iA_iC_i$。则有
$$
\sum_{k=j+1}^i(A_i-A_k)C_k=A_i(SumC_i-SumC_j)-(Sum_i-Sum_j)
$$

考虑斜率优化，对转移方程进行处理，得到：

$$
f_i-A_iSumC_i+Sum_i-x=\min\{{(f_j+Sum_j)-A_iSumC_j}\}
$$

维护下凸壳。时间复杂度 $\mathcal{O}(n)$。

**代码**

代码写起来还是很简单的，就不写注释了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200001;
int n,x;
int f[N],sumc[N],sum[N],q[N<<1];
int Y(int i){return f[i]+sum[i];}
int X(int i){return sumc[i];}
double slope(int i,int j){
	return 1.0*(Y(i)-Y(j))/(X(i)-X(j));
}
struct typ{
	int a,c;
}num[N];
bool cmp(typ a,typ b){
	return a.a<b.a;
}
signed main(){
	cin>>n>>x;
	for(int i=1;i<=n;++i)
		scanf("%lld%lld",&num[i].a,&num[i].c);
	sort(num+1,num+n+1,cmp);
	for(int i=1;i<=n;++i){
		sumc[i]=sumc[i-1]+num[i].c;
		sum[i]=sum[i-1]+num[i].a*num[i].c;
	}
	int hd=1,tl=1;
	for(int i=1;i<=n;++i){
		while(hd<tl&&slope(q[hd],q[hd+1])<=num[i].a)hd++;
		int j=q[hd];
		f[i]=f[j]+num[i].a*(sumc[i]-sumc[j])-(sum[i]-sum[j])+x;
		while(hd<tl&&slope(q[tl],q[tl-1])>=slope(q[tl],i))tl--;
		q[++tl]=i;
	}
	cout<<f[n];
	return 0;
}
```

---

## 作者：ax_by_c (赞：0)

为什么是 *2700+ 啊/yiw

首先分析一下，发现是排序后分成段，每一段里面的数全部加到最大值。（证明考虑调整法）

于是考虑 DP，设 $f_i$ 表示前 $i$ 个元素的最小答案。

转移：$f_i=\min\limits_{j=0}^{i-1}(f_j+\sum\limits_{k=j+1}^{i}(A_i-A_k)C_k+X)$。

令 $s_i=\sum\limits_{j=1}^{i}C_j,S_i=\sum\limits_{j=1}^{i}A_jC_j$。

则 $f_i=\min\limits_{j=0}^{i-1}(f_j+A_i(s_i-s_j)-(S_i-S_j)+X)$。

即 $f_i=A_is_i-S_i+X+\min\limits_{j=0}^{i-1}(-A_is_j+f_j+S_j)$。

min 里面是个关于 $A_i$ 的一次函数，李超线段树即可。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
typedef pair<ll,ll> pii;
const ll inf=1e18;
const int N=1e6+5;
struct LINE{
	ll k,b;
	ll get(ll x){
		return k*x+b;
	}
};
struct seg{
	LINE tr[N*4];
	void bld(int u,int l,int r){
		tr[u]={0,inf};
		if(l==r)return ;
		int mid=l+((r-l)>>1);
		bld(u<<1,l,mid);
		bld(u<<1|1,mid+1,r);
	}
	void upd(int u,int l,int r,LINE x){
		if(l>r)return ;
		int mid=l+((r-l)>>1);
		if(tr[u].get(mid)>x.get(mid))swap(tr[u],x);
		if(tr[u].get(l)>x.get(l))upd(u<<1,l,mid,x);
		if(tr[u].get(r)>x.get(r))upd(u<<1|1,mid+1,r,x);
	}
	ll Q(int u,int l,int r,int p){
		if(l==r)return tr[u].get(p);
		int mid=l+((r-l)>>1);
		ll res=tr[u].get(p);
		if(p<=mid)res=min(res,Q(u<<1,l,mid,p));
		else res=min(res,Q(u<<1|1,mid+1,r,p));
		return res;
	}
}tr;
int n;
ll m,s,S,f[N];
pii a[N];
void main(){
	scanf("%d %lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld %lld",&a[i].first,&a[i].second);
	sort(a+1,a+1+n);
	tr.upd(1,1,1000000,(LINE){-s,f[0]+S});
	for(int i=1;i<=n;i++){
		s+=a[i].second;
		S+=a[i].first*a[i].second;
		f[i]=a[i].first*s-S+m+tr.Q(1,1,1000000,a[i].first);
		tr.upd(1,1,1000000,(LINE){-s,f[i]+S});
	}
	printf("%lld\n",f[n]);
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：qnqfff (赞：0)

### 思路

考虑按 $a_i$ 排序，问题变成将序列分成若干段，每段的每个数都要变成最后那个数的最小代价。

设 $dp_i$ 表示考虑前 $i$ 个数的答案，转移枚举上一段的结尾 $j$，$dp_i=\min(dp_j+\sum\limits_{k=j+1}^{i}((a_i-a_k)\times c_k)+X)$。

$dp_i=\min(dp_j+a_i\times\sum\limits_{k=j+1}^{i}c_k+\sum\limits_{k=j+1}^{i}a_k\times c_k+X)$。

令 $sum_i$ 表示 $\sum\limits_{j=1}^{i}a_j\times c_j$，$sumC_i$ 表示 $\sum\limits_{j=1}^{i}c_j$。

$dp_i=\min(dp_j+a_i\times(sumC_i-sumC_j)-sum_i+sum_j+X)$。

容易发现可以斜率优化，然后做完了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){char c=getchar();int p=0,flg=1;while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,cost,dp[200010],sum[200010],sumC[200010],q[200010];struct Info{int a,c;}a[200010];
int Y(int i){return dp[i]+sum[i];}int X(int i){return sumC[i];}
double slope(int i,int j){return 1.*(Y(i)-Y(j))/(X(i)-X(j));} 
signed main(){
	n=read();cost=read();for(int i=1;i<=n;i++) a[i]={read(),read()};sort(a+1,a+1+n,[&](Info x,Info y){return x.a<y.a;});
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i].a*a[i].c,sumC[i]=sumC[i-1]+a[i].c;
	for(int i=1,l=1,r=1;i<=n;i++){
		while(l<r&&slope(q[l],q[l+1])<a[i].a) l++;dp[i]=dp[q[l]]+a[i].a*(sumC[i]-sumC[q[l]])-sum[i]+sum[q[l]]+cost;
		while(l<r&&slope(q[r-1],q[r])>slope(q[r],i)) r--;q[++r]=i;
	}cout<<dp[n];
	return 0;
}
```

---

## 作者：Raisen_zx (赞：0)

简述题意：给定序列 $A$ ,可以用 $C_i$ 的代价使得 $A_i+1\to A_i$ ，对于最终的序列 $A'$，要最小化 $\sum C_{i}\cdot (A'_i-A_i)+(A'$ 中本质不同数个数)。 

显然有个很唐的暴力，定义 $f_{i,j,0/1}$ 为 $i$ 最后加到 $j$ ，$j$ 在 $[1,i]$ 是否出现过的最小代价。

不可做，复杂度穿了，跟因为值域相关，而改相同显然不能往值域上靠。

先考虑答案形式，对于最终的序列排序后显然是个连续段，我们要做的是 **用 $C$ 来削掉不同数的代价**
由于数是不能变小的，所以我们对于数按 $A$ 排序，最后连续段就是这个序列加数后的结构，也就是：加数后按 $A$ 排的最优方案等价于按 $A$ 排后再加数的最优方案，怎么证：

按 $A$ 排后得到的信息就是 $A_i\le A_j\to A'_i\le A'_j$ ，假设有 $A_i\le A_j$ 但是 $A'_i>A'_j$ ，就算 $i$ 消除了作为不同数的贡献，也不如 $A'_i= A'_j$ ，得证。

然后会存在一些点不会改，显然，改了不如不改。

假设有 $K$ 段，每一段的末尾形成序列为 $P$ ，答案为 
$$\begin{align}
&\sum\limits_{i=1}^{k}(X+\sum\limits_{j=P_{i-1}+1}^{P_i}C_j(A_{P_i}-A_{j}))\\
=&\sum\limits_{i=1}^{k}(X+\sum\limits_{j=P_{i-1}+1}^{P_i}C_j\cdot A_{P_i})-\sum A_i\cdot C_i\\
\end{align}$$
显然我们只需最优化左边这一坨，对于这一坨就用高贵的 $DP$ 求解。

为了方便，记 $C$ 前缀和为 $sumc$。

定义 $f_{i}$ 为把 $i$ 为结尾的修改成连续段的最小代价，枚举连续段的开头。

$f_i=\min\limits_{j\le i}(f_{j-1}-sumc_{j-1}\cdot A_i)+sumc_i\cdot A_i+X$。

考虑斜率优化。

来转化式子 
$$\begin{align}
f_i=f_{j-1}-sumc_{j-1}\cdot A_i+sumc_i\cdot A_i+X\\
f_{i}-sumc_i\cdot A_i-X+sumc_{j-1}\cdot A_i=f_{j-1}
\end{align}$$

得到了 $b=f_i-sumc_i\cdot A_i-X,k=A_i,y=f_{j-1},x=sumc_{j-1}$。

单调队列优化斜率优化的常见形式，直接套模版即可。
```cpp
#include<algorithm>
#include<cstdio>
#include<cctype>
#include<cstring>
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
using namespace std;
typedef long long ll;
char buf[1<<20],*p1=buf,*p2=buf;
template<typename type>
inline void read(type &x)
{
    x=0;bool flag=0;char ch=gc();
    while(!isdigit(ch)) flag=ch=='-',ch=gc();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=gc();
    flag?x=-x:0;
}
const int MAXN=2e5+10;
int n,hd,tl,que[MAXN];
ll f[MAXN],sumc[MAXN],X,sum;
struct Item
{
    ll a,c;
    bool operator<(const Item &x)const{return a<x.a;}
}it[MAXN];
inline ll Calc(int x,int pos)
{
    return f[pos]+(sumc[x]-sumc[pos])*it[x].a+X;
}
inline double K(int x,int y)
{
    return (1.0*(f[x]-f[y]))/(1.0*(sumc[x]-sumc[y]));
}
int main()
{
    read(n),read(X);
    for(int i=1;i<=n;++i) read(it[i].a),read(it[i].c);
    sort(it+1,it+n+1);
    for(int i=1;i<=n;++i)
    {
        sumc[i]=sumc[i-1]+it[i].c;
        sum+=it[i].a*it[i].c;
    }
    que[hd=tl=1]=0;
    for(int i=1;i<=n;++i)
    {
        while(hd<tl&&K(que[hd+1],que[hd])<=(1.0*it[i].a)) hd++;
        f[i]=Calc(i,que[hd]);
        while(hd<tl&&K(que[tl-1],que[tl])>=K(que[tl],i)) tl--;
        que[++tl]=i;
    }
    printf("%lld\n",f[n]-sum);
    return 0;
}
```

---

## 作者：NATO (赞：0)

### 思路浅析：

显然我要改某个值，我一定是把它加成一个已经出现了的数（如果是加成某个未出现的数，那么我还要把一些小于这个未出现的数加成这个才有用，显然不如就加成那些小于这个未出现数的那些出现了的数有用）。

那么考虑从小到大排序，最后整个序列必然是分成了好几段值域上相邻的数，然后每段内通通变成段内数的最大值，这就可以动归启动了，设 $dp_i$ 表示排序后以第 $i$ 小的数为最后一段的结尾，可以得到的最小代价。

转移是简单的，枚举上一个转移点即可：

$dp_i=X+\min\limits_{j=1}^{i-1}(dp_j+\sum\limits_{k=j+1}^{i}C_k\times(A_i-A_k))$

考虑优化，对 $\sum\limits_{k=j+1}^{i}C_k\times(A_i-A_k)$ 下手：

$$\sum\limits_{k=j+1}^{i}C_k\times(A_i-A_k)=\sum\limits_{k=1}^{i}C_k\times A_i-\sum\limits_{k=1}^{j}C_k\times A_i-(\sum\limits_{k=1}^{i}(C_k\times A_k)-\sum\limits_{k=1}^{j}(C_k\times A_k))$$

观察到当枚举到 $i$ 的时候，$\sum\limits_{k=1}^{i}C_k\times A_i,\sum\limits_{k=1}^{i}(C_k\times A_k)$ 全是常数，可以预处理，$-\sum\limits_{k=1}^{j}C_k\times A_i+\sum\limits_{k=1}^{j}(C_k\times A_k)$ 是斜率优化中标准的 $kx+b$ 的形式，套上斜率优化板子即可。

#### 参考代码：

笔者无脑写了个李超树上去，将就着看吧。


```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 214748364719260817ll
using namespace std;
ll n,x;
ll dp[200005],val[200005],sum[200005];
ll fc[1000005];
struct px
{
	ll a,c;
}what[200005];
struct tree
{
	ll k,b;
	tree()
	{
		k=0;b=INF;
	}
}tr[800005];
#define ls(id) id*2
#define rs(id) id*2+1
ll get_val(tree k,ll where)
{
	return k.k*what[where].a+k.b;
}
void pushdown(ll id,ll l,ll r,tree a)
{
	ll mid=l+r>>1;
	ll nl=get_val(a,l),nr=get_val(a,r),nmid=get_val(a,mid);
	ll yl=get_val(tr[id],l),yr=get_val(tr[id],r),ymid=get_val(tr[id],mid);
	if(nl<yl&&nr<yr)
	{
		tr[id]=a;return;
	}
	if(nl>=yl&&nr>=yr)return;
	if(nmid<ymid)swap(tr[id],a),swap(nl,yl),swap(nr,yr);
	if(nl<yl)pushdown(ls(id),l,mid,a);
	if(nr<yr)pushdown(rs(id),1+mid,r,a);
}
ll query(ll id,ll l,ll r,ll ml)
{
	if(l==r)return get_val(tr[id],ml);
	ll mid=l+r>>1;
	if(ml<=mid)return min(get_val(tr[id],ml),query(ls(id),l,mid,ml));
	return min(get_val(tr[id],ml),query(rs(id),1+mid,r,ml));
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>x;
	ll a,c;
	for(ll i=1;i<=n;++i)
	{
		cin>>a>>c;
		fc[a]+=c;
	}
	n=0;
	for(ll i=1;i<=1000000;++i)
		if(fc[i])
		what[++n].a=i,what[n].c=fc[i],val[n]=val[n-1]+what[n].a*what[n].c,sum[n]=sum[n-1]+what[n].c;
	tree ls;ls.b=0;
	pushdown(1,1,n,ls);
	for(ll i=1;i<=n;++i)
	{
		dp[i]=query(1,1,n,i)+x+what[i].a*sum[i]-val[i];
		ls.k=-sum[i];ls.b=dp[i]+val[i];
		pushdown(1,1,n,ls);
	}
	cout<<dp[n];
}//dp_i=\min\limits_{j=1}^{i}dp_{j-1}+x+what[i].a*(sum_i-sum_{j-1})-(val_i-val_{j-1})
//dp_i=\min\limits_{j=1}^{i}-sum_{j-1}*what[i].a+(dp_{j-1}+val_{j-1})+(x+what[i].a*sum_i-val_i)
```

---

## 作者：Jerrywang09 (赞：0)

很好的斜率优化。斜率优化题大多数与序列分段有关。考虑转化题目：将原数组 $a$ 排序，分成若干段，每一段的最后一个数就是最大值，将这一段内的其它数改为这个最大值。

写出转移方程：
$$
f(i)=\min(f(j)+x+\sum_{k=j+1}^i (a_i-a_k)c_k)
$$
拆项，得
$$
f(i)=\min(f(j)+x+a_i\sum_{k=j+1}^i c_k-\sum_{k=j+1}^ia_kc_k)
$$
写成前缀和的形式：
$$
f(i)=\min(f(j)+x+a_i(sc(i)-sc(j))-(s(i)-s(j)))
$$
继续推导：
$$
f(i)=f(j)+x+a_i sc(i)-a_i sc(j)-s(i)+s(j)\\
f(i)-x-a_i sc(i)+a_i sc(j)+s(i)=f(j)+s(j)\\
f(j)+s(j)=a_i sc(j)+(f(i)-x-a_i sc(i)+s(i))
$$
维护一个下凸包，然后就可以斜率优化了。

```cpp
// Title:  Histogram
// Source: ABC228H
// Author: Jerrywang
#include <bits/stdc++.h>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=200010;
using namespace std;

int n; ll x, s[N], f[N], sc[N];
struct node {ll a, c;} a[N];
int q[N], hh, tt;
#define Y(j) (s[j]+f[j])
#define K(i) a[i].a
#define X(j) sc[j]
double slope(int i, int j)
{
	return 1.*(Y(i)-Y(j))/(X(i)-X(j));
}
bool cmp(node a, node b) {return a.a<b.a;}

int main()
{
#ifdef Jerrywang
	freopen("E:/OI/in.txt", "r", stdin);
#endif
	scanf("%d%lld", &n, &x);
	rep(i, 1, n) scanf("%lld%lld", &a[i].a, &a[i].c);
	sort(a+1, a+n+1, cmp);
	rep(i, 1, n) sc[i]=sc[i-1]+a[i].c, s[i]=s[i-1]+a[i].a*a[i].c;
	rep(i, 1, n)
	{
		while(hh<tt && slope(q[hh+1], q[hh])<=K(i)) hh++;
		int j=q[hh];
		f[i]=f[j]+a[i].a*(sc[i]-sc[j])-s[i]+s[j]+x;
		while(hh<tt && slope(i, q[tt])<=slope(q[tt], q[tt-1]))
			tt--;
		q[++tt]=i;
	}
	printf("%lld", f[n]);
	
	return 0;
}
```

---

