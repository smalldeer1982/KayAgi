# [NAPC-#1] Stage1 - Simple

## 题目背景

> ![](https://cdn.luogu.com.cn/upload/image_hosting/pon0cylv.png)

## 题目描述

### 【简要题意】
给定 $n,m,k,S$，请构造长度为 $n$ 的整数序列 $a$ 使得：
- $0\leqslant a_i\leqslant m,\forall i\in[1,n]$（即序列 $a$ 内的每个元素均不小于 $0$ 且不大于 $m$）。
- $|a_i-a_{i-1}|\leqslant k,\forall i\in(1,n]$（即序列 $a$ 内的每两个相邻元素之差的绝对值均不大于 $k$）。
- $(\sum_{i=1}^n a_i ) = S$（即序列 $a$ 内的所有元素的和为 $S$）。

**保证有解。**

### 【原始题意】

前面忘了，但是~~你随 kid 穿越到了 ic~~（I wanna be the Creator），来到了一个关卡编辑器面前。该地图宽为 $n$，高为 $(m+1)$，是你不能修改的；里面还有 $S$ 个 $1\times1$ 大小的未摆放的砖。现在你需要帮 kid 摆好这一面，也就是说，将这 $S$ 个砖摆放好，使得他可以通过。有以下要求：

1. ~~砖是有重力的~~，所以**一块砖只能摆放在下边界上或者另一块砖上**。同一横纵坐标不能摆放多块砖。
2. 你至少要给 kid 留一条缝来通过，所以每一列你最高只能放 $m$ 块砖（地图高度为 $m+1$）。但是注意，ic 关卡下边界没有伤害，某一列是可以不放砖块的。
3. kid 的跳跃能力和~~从高处坠落而不受伤的能力~~是有限的，这用一个非负整数 $k$ 来描述：相邻两列摆放的砖的数量之差的绝对值不能超过 $k$，否则该关卡对 kid 来说就是无解的。_（但是注意：该条对第一列高度没有要求，kid 出生点就在第一列。）_
4. 你要把所有 $S$ 块砖都摆进去，不多不少。

Creator 不会为难你，因此一定有一种关卡符合上述所有规则。

为了输出方便，你只需要给出第 $i$ 列有多少砖块（记为 $a_i$），输出 $a$ 序列即可。容易证明，一个合法的 $a$ 序列和一个合法关卡是一一对应的。

## 说明/提示

### 【数据范围】

该题共有 $10$ 个测试点，每个测试点等分。

- 对于 $20\%$ 的数据，$S=n\cdot m$。
- 对于 $20\%$ 的数据，$k=0$。
- 对于 $20\%$ 的数据，$k=10^9$。

对于 $100\%$ 的数据，$1\leqslant n,m\leqslant 10^5$，$0\leqslant k\leqslant 10^9$，$0\leqslant S\leqslant n\cdot m$。

### 【提示】
> 古之有数，其名为 $S$。$S$ 之大，一个 `int` （可能）装不下。

### 【样例解释 #1】
样例输出对应关卡如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/jyttdqal.png)

注意可能有多种合法关卡均符合条件。



## 样例 #1

### 输入

```
4 6 2 11```

### 输出

```
2 4 2 3```

## 样例 #2

### 输入

```
3 4 5 6```

### 输出

```
4 2 0```

# 题解

## 作者：Eason_cyx (赞：5)

一道比较简单的构造题。

我们首先从最简单的情况来看。

当 $S$ 是 $n$ 的倍数的时候，那么问题就转化成了将 $S$ 平均分成 $n$ 份，那么只需要输出 $n$ 个 $\large\frac{S}{n}$ 就可以了。

那么我们来考虑其他情况，即 $S$ 不是 $n$ 的倍数。我们先按前面的方法处理，此时会剩下 $S \bmod n$。此时方法也很简单，将后 $S \bmod n$ 个数 $+1$ 就可以了。

整理一下，得到以下结论：

组成答案序列的 $n$ 个数中，前 $n - (S \bmod n)$ 个数为 $\large\frac{S}{n}$，后 $S \bmod n$ 个数为 $\large\frac{S}{n}\small+1$。

推出了结论，代码就好写了。
```cpp
#include <iostream>
using namespace std;
int main() {
    long long n,m,k,s; cin >> n >> m >> k >> s;
    for(int i = 1; i <= n - (s % n);i++) cout << s / n << ' ';
    for(int i = 1; i <= s % n;i++) cout << s / n + 1 << " \n"[i == (s%n)];
    return 0;
}
```

---

## 作者：FallingFYC_ (赞：4)

# [原题](https://www.luogu.com.cn/problem/P9429)
比赛时 $5$ 分钟就做出来了~

---
### 分析
根据第三条条件和第二条条件，可以发现，最优策略是将 $S$ 平均分到数组 $a$ 中，这样每两个相邻元素之差的绝对值最大为 $1$，题目中还满足至少有一个序列满足题目要求，因此此策略一定满足第二条条件和第一条条件（因为这样分数组 $a$ 中的元素中最大的相较于其他方案中是最小的）。

**注意：卡 `int`，要开 `long long`。**

---
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n , m , k , s , ans[100005];
int main()
{
    cin >> n >> m >> k >> s;
    for (int i = 1 ; i <= n ; i++) ans[i] = s / n; //将S平均分到数组a中
    for (int i = 1 ; i <= s % n ; i++) ++ans[i]; //将余数再平均分到数组a中 
    for (int i = 1 ; i <= n ; i++) cout << ans[i] << ' ';
	return 0; 
}
```
[评测记录](https://www.luogu.com.cn/record/list?pid=P9429&user=923403&page=1)

---

## 作者：wangbinfeng (赞：2)

![](https://img.shields.io/badge/题目-P9429-green)
![](https://img.shields.io/badge/难度-入门-red)
![](https://img.shields.io/badge/考点-构造-blue)
![](https://img.shields.io/badge/题型-Special_Judge(SPJ)-yellow)
![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)

------------
先分析题目，长度为 $n$ 的序列 $a$ 的所有元素（均小于 $m$）之和为 $S$ 且相邻元素之差小于定值 $k$，则令 $a_i=\frac{S}{n}\left(\forall i\in \left[1,n\right]\right)$ 即可。因为 $a_i\in \mathbb N,0\le a_i\le m$，所以应修改 $a_i$ 至整数，那么微调一下就好。把一部分 $a_i$ 下取整，其余的上取整，使得 $(\sum_{i=1}^n a_i ) = S$。具体微调方法如下：
$$a_i=\begin{cases}
  \lceil\frac{S}{n}\rceil & i\le \left(s\;\bmod\;n\right) \\
  \lfloor\frac{S}{n}\rfloor & i> \left(s\;\bmod\;n\right)
\end{cases}$$  

因为题目说了，保证至少有一个序列满足题目要求，所以无需证明答案是否存在。

------------

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,s;
inline long long read(){
    char c;
    long long ret=0,f=1;
    for(c=getchar();c<'0'||c>'9';c=getchar())if(c=='-')f=-f;
    for(;c>='0'&&c<='9';c=getchar())ret=ret*10+c-'0';
    return ret*f;
}//快读模板（似乎没什么用。。。
int main() {
	n=read(),m=read(),k=read(),s=read();
	for(int i=1;i<=n;i++)
		if(i>s%n)printf("%lld ",s/n);//用整除代替下取整
		else printf("%lld ",s/n+1);//用整除加一代替上取整
}
```

---

## 作者：y_kx_b (赞：2)

## Stage1 - Simple

预计难度：\*900 左右，红。

前置芝士：无。

---

部分分就不讲了吧/fad

简单签到，一种构造方案为直接构造 $a=\left\{\left\lfloor\dfrac Sn\right\rfloor,\left\lfloor\dfrac Sn\right\rfloor,\dots,(\left\lfloor\dfrac Sn\right\rfloor+1)\right\}$（可以任意重排），其中 $(\left\lfloor\dfrac Sn\right\rfloor+1)$ 的个数为 $S\bmod n$。

显然当 $k\geqslant1$ 时该构造方案一定符合要求（$\left|(\left\lfloor\dfrac Sn\right\rfloor+1)-\left\lfloor\dfrac Sn\right\rfloor\right|\leqslant1\leqslant k$）；当 $k=0$ 时必须有 $S\bmod n=0$，否则无解（必定有相邻两个元素不同）。

至于 $m$，因为 $S\leqslant n\cdot m$ 所以必须有 $m\geqslant\left\lceil\dfrac Sn\right\rceil$，所以上面的构造一定符合要求。

code：
```cpp
#include<cstdio>
long long read() {long long x; scanf("%lld", &x); return x;}
int main() {
	int n = read(), m = read(), k = read();
	long long S = read();
	for(int i = 1; i <= n; i++)
		printf("%lld%c", S / n + (i <= S % n), " \n"[i == n]);
	return 0;
}
```

---

## 作者：Vct14 (赞：1)

可以直接跳过部分分做法。

### $20$ 分做法

因为 $S=n\times m$，让每个数均为 $m$ 即可。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	long long n,m,k,S;
	cin>>n>>m>>k>>S;
	while(n--) cout<<m<<" ";
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/113308792)见此。

### $40$ 分做法（可得 $50$ 分）

对于 $k=0$，又保证至少有一个序列满足题目要求，则数据必有 $n\mid S$，让每个数均为 $\dfrac{S}{n}$ 即可。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	long long n,m,k,S;
	cin>>n>>m>>k>>S;
	for(int i=1; i<=n; i++) cout<<S/n<<" ";
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/113308848)见此。按理说应该是 $40$ 分，但是却有 $50$ 分。

这已经很接近正解了。

### $60$ 分做法

由于 $k$ 约等于没限制，所以特判 $n\mid S$ 的情况，再随便写一个每个元素不大于 $m$ 且和等于 $S$ 的 $n$ 个数的加法算式即可。

由于 $40$ 分做法太接近正解，想到的人应该也快想到正解了，所以这里就不放代码了。

### $100$ 分做法

由于每两个相邻元素之差有限制，所以我们尽量让它变小。那么最容易想到的方法就是**平均分**，即每个数均为 $\left\lfloor\dfrac{S}{n}\right\rfloor$。

但是，如果 $n\nmid S$，就无法平均分了。这时，我们可以让前面的的 $S \bmod n$ 个数为 $\left\lfloor\dfrac{S}{n}\right\rfloor+1$，这样就可以做到和为 $S$。

我们考虑这种方法的可行性。

------------

#### 条件 $1$

需满足 $0\leqslant a_i\leqslant m,\forall i\in[1,n]$，即每个元素均不小于 $0$ 且不大于 $m$。

由于 $S$ 和 $n$ 都大于或等于 $0$，所以 $a_i\geqslant0$。

而 $S\leqslant n\times m$，若 $n\mid S$，则 $a_i=\dfrac{S}{n}\leqslant m$ 成立；若 $n\nmid S$，必有 $\left\lceil\dfrac{S}{n}\right\rceil \leqslant m$，而最大的 $a_i=\left\lfloor\dfrac{S}{n}\right\rfloor+1=\left\lceil\dfrac{S}{n}\right\rceil\leqslant m$ 也成立。所以 $a_i\leqslant m$。

综上，第一条成立。

#### 条件 $2$

满足 $|a_i-a_{i-1}|\leqslant k,\forall i\in(1,n]$，即序列 $a$ 内的每两个相邻元素之差的绝对值均不大于 $k$。

由于 $n\mid S$ 时，每两个相邻元素之差的绝对值为 $0$，必然满足。

而此构造方法可以保证 $n\nmid S$ 时每两个相邻元素之差的绝对值均不大于 $1$，即当 $k\geqslant 1$ 时，均可以满足。

若 $k=0$，则每个元素必须相同，若还有 $n\nmid S$，则肯定无解。由于题目保证至少有一个序列满足题目要求，则不会有这种情况。

综上，第二条成立。

#### 条件 $3$

满足 $(\sum_{i=1}^n a_i ) = S$，即序列 $a$ 内的所有元素的和为 $S$。

在构造此序列时，我们第一个满足的条件就是所有元素的和为 $S$。故不用考虑，第三条成立。

------------

因此可以这样构造。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	long long n,m,k,S;
	cin>>n>>m>>k>>S;
	if(S%n) for(int i=1; i<=S%n; i++) cout<<S/n+1<<" ";//不能整除
	for(int i=1; i<=n-S%n; i++) cout<<S/n<<" ";
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/113308493)见此。

---

## 作者：Bc2_ChickenDreamer (赞：0)

# P9429 [NAPC-#1] Stage1 - Simple 题解

## 题目分析

### $20\ pts$ 方法

因为 $S = nm$，所以直接构造 $[m, m, \cdots, m]$ 即可。

### $40\ pts$ 方法

判断 $k = 0$ 的情况，这种情况直接构造 $\big[\big\lfloor \dfrac{S}{n}\big\rfloor, \big\lfloor \dfrac{S}{n}\big\rfloor, \cdots, \big\lfloor \dfrac{S}{n}\big\rfloor\big]$ 即可。

### $100\ pts$ 方法

我们可以发现，当构造 $\big[\big\lfloor \dfrac{S}{n}\big\rfloor, \big\lfloor \dfrac{S}{n}\big\rfloor, \cdots, \big\lfloor \dfrac{S}{n}\big\rfloor\big]$ 时还要加上 $S \bmod n$ 才能等于 $S$。所以我们可以构造 $S \bmod n$ 个 $\big\lfloor \dfrac{S}{n} + 1\big\rfloor$，$n - S \bmod n$ 个 $\big\lfloor \dfrac{S}{n}\big\rfloor$。这样可以保证绝对值 $\le k$，特别的，$k = 0$ 时保证 $S \bmod n = 0$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define qwq ios::sync_with_stdio(false),cin.tie(0),cout.tie(0) 
const int N = -1;

signed main()
{
	qwq;
	int n, m, k, s;
	cin >> n >> m >> k >> s;//输入 n, m, k, s
	int t = s % n; //求出 s % n 的值
	for (int i = 1; i <= n; ++ i)//循环输出
	{
		if (t != 0)//如果 t 不是 0（也就是构造的 s / n + 1 还没到 s % n 个）
		{
			cout << s / n + 1 << " ";//输出 s / n + 1
			-- t;//把 t 减 1
		}
		else
			cout << s / n << " ";//否则输出 s / n
	}
	return 0;
}
/*pbl nbr：*/
```


---

