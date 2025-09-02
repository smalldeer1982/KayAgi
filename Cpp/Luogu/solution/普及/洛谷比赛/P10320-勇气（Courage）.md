# 勇气（Courage）

## 题目背景

数学家渴求真理的美德，永不停歇的力量的源泉 —— 勇气。
****
「勇气之光」乔伊，是杜沃夫族的接任族长，也是拥有古代战神之力的战士。

## 题目描述

乔伊有一项技能，可以将 $x$ 的攻击力强化为 $x^2$。但这个技能并不完美，除了第一次之外，每一次**使用该技能前**，攻击力都会衰减到之前的一半。

比如最初的攻击力为 $\color{red}6$，强化后变成 $6^2=\color{red}{36}$。而在下一次强化前，会先衰减到 $36/2=18$，然后再强化为 $18^2=\color{red}{324}$。

乔伊想知道，如果最初的攻击力为 $x$，至少需要多少次强化，可以使其**不小于** $2^n$？  
如果无论强化多少次，都不可能达到要求，请输出 `inf`。

## 说明/提示

【样例 $1$ 解释】  
初始攻击力 $x=2$ 就已经达到了 $2^n=2$，不需要使用技能就满足了要求，故答案为 $0$。

【样例 $2$ 解释】  
初始攻击力为 $3$，需要达到 $2^6=64$。第一次用技能后变为 $9$，第二次后变为 $(9/2)^2=81/4$，第三次变为 $((81/4)/2)^2=6561/64$，已经达到了要求，故答案为 $3$。

【数据范围】  
**本题采用捆绑测试。**  

Subtask 1（15 pts）：$n\le 60$；  
Subtask 2（20 pts）：$x=4$；  
Subtask 3（25 pts）：$n\le 10^5$；  
Subtask 4（40 pts）：无特殊限制。

对于全部的数据，$2\le x\le 10^9$，$1\le n \le 10^9$。

## 样例 #1

### 输入

```
2 1```

### 输出

```
0```

## 样例 #2

### 输入

```
3 6```

### 输出

```
3```

## 样例 #3

### 输入

```
16 335```

### 输出

```
7```

# 题解

## 作者：NaCly_Fish (赞：45)

一个比较直观的想法，就是先求出 $k$ 次技能后的攻击力 $a_k$ 为多少，可以列出：
$$x \ , \ x^2 \ , \ \frac{x^4}{2^2} \ , \ \frac{x^8}{2^6} \ , \ \frac{x^{16}}{2^{14}} \ ,  \ \cdots$$
简单找一下规律，就可以发现对于 $k\geq 1$：
$$a_k=\frac{x^{2^k}}{2^{2^k-2}}$$
使用归纳法，根据 $a_k= (a_{k-1}/2)^2$ 就可以证明这个结论。首先如果 $x\geq 2^n$ 答案直接就是零，如果 $x=2$ 而 $n>2$ 则无解。

对于一般的情况，需要找出最小的正整数 $k$ 使得

$$\frac{x^{2^k}}{2^{2^k-2}}\geq 2^n$$
只要学过一些高中数学的内容，我们就知道此不等式可以用**对数**来解决，即转化为：
$$\begin{aligned}2^k\log_2x-(2^k-2) &\geq n  \\ 2^k &\geq \frac{n-2}{\log_2x -1}\end{aligned}$$
可以直接从小到大枚举 $k$ 来判断，也可以对右式再计算 $\log_2$，向上取整即是答案。

---

## 作者：wangbinfeng (赞：10)

[![](https://img.shields.io/badge/题目-P10320_勇气（Courage）-green)
![](https://img.shields.io/badge/难度-普及/提高−-yellow)
![](https://img.shields.io/badge/考点-数学-blue)
![](https://img.shields.io/badge/题型-传统题-red)](https://www.luogu.com.cn/problem/P10320)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009)

------------
由于除了第一次强化外每次都要衰变，可以想到如果初始值翻倍且第一次强化也要衰变，则对结果没有影响。具体地，令 $y=2x$，强化次数为 $k\left(k\in\R^*\right)$。

设第 $k$ 次强化后攻击力为 $f\left(k\right)=\dfrac{y^{b_k}}{2^{a_k}}=\left(\dfrac{f\left(k-1\right)}{2}\right)^2=\dfrac{y^{2b_{k-1}}}{2^{2+2a_{k-1}}}=\dfrac{y^{2^k}}{2^{2^{\left(k+1\right)}-2}}$。

则题目可转化为 $f\left(k\right)=\dfrac{y^{2^k}}{2^{2^{\left(k+1\right)}-2}}\ge 2^n$。

由数学知识可知：

$$
\begin{aligned}
&\begin{aligned}
\text{原不等式} 
&\implies \log_2\left(\dfrac{y^{2^k}}{2^{2^{\left(k+1\right)}-2}}\right)\ge n\\
&\implies \log_2 y^{2^k}-\log_2 2^{2^{\left(k+1\right)-2}}\ge n\\
&\implies \log_2 y^{2^k}-2^{k+1}+2\ge n\\
&\implies 2^k\log_2 y^-2^{k+1}\ge n-2\\
&\implies \log_2 y-2\ge \dfrac{n-2}{2^k}\\
&\implies \dfrac{\log_2 y-2}{n-2}\ge \dfrac{1}{2^k}\\
&\implies \dfrac{n-2}{\log_2 y-2}\le 2^k\\
&\implies k\ge\log_2\dfrac{n-2}{\log_2 y-2}
\end{aligned}
\\
&\begin{aligned}
& \because \mathrm{ans}\in\N^*\\
& \therefore \mathrm{ans}=\lceil k\rceil\\
& \therefore \mathrm{ans}=\lceil \log_2\dfrac{n-2}{\log_2 y-2}\rceil\\
& \therefore \mathrm{ans}=\lceil \log_2\dfrac{n-2}{\log_2 2x-2}\rceil
\end{aligned}
\end{aligned}
$$

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
double n,x,y;
signed main(){
	cin>>x>>n;
	if(x==2 && n>2){cout<<"inf";return 0;}
	else if(x==2 && n==2){cout<<1;return 0;}
	else if(n==1){cout<<0;return 0;}
	cout<<static_cast<int>(ceil(log2((n-2.0)/(log2(x*2)-2))));
	return 0;  
}
```

---

## 作者：YuYuanPQ (赞：8)

Update on 2024.6.20:

讲个笑话：

![](https://cdn.luogu.com.cn/upload/image_hosting/qfh6gz8t.png)

但是

![](https://cdn.luogu.com.cn/upload/image_hosting/6hidj4v0.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/zywr7vp5.png)

感谢这位老哥发现了我的错误。

遂改。

## 题目大意

给定一个数 $x$，除了第一次把 $x$ 变为 $x^2$ 外，每次把 $x$ 变为 $(x/2)^2$。

问最少需要几次更改，才可以使得 $x\geq2^n$？

如果不可能，输出 `inf`。

## 前言

我不懂如何用数学含量很高的方法解决。

所以在此分享一种赛时 AC 的，通俗易懂的做法。

## 做法

设 $k=\log_{2}x$。

定义 $s$，表示已经使用的 $2$ 的个数。

初始时，$s=k$。

每次更改，$s$ 先 $\times 2$，再 $-1$。

分别对应强化攻击力、攻击力衰减到之前的一半。

$s\geq n$ 时输出就可以啦~ 

完结撒花~

## 注意

- 用 `double`，不要用 `long long`。（赛时因为这个，吃了 $3$ 发罚时）

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int x,n;
double k,s;
ll ans;
void solve()
{
    k=log2(x);
    s=k;
    while(ceil(s)<n)
    {
        s*=2;//对应强化攻击力
        s--;//对应攻击力衰减到之前的一半
        ans++;
    }
    printf("%lld\n",ans);
    return;
}
int main()
{
    scanf("%d%d",&x,&n);
    if(x==1)
    {
        if(n>0) printf("inf\n");
        else printf("0\n");
    }
    else if(x==2)
    {
        if(n>2) printf("inf\n");
        else if(n==2) printf("1\n");
        else printf("0\n");
    }
    //上面是特判
    else
    {
        solve();
    }
    return 0;
}
```

---

## 作者：littlebug (赞：8)

## Description

给定 $x,n$，定义函数
$$\displaystyle f(k)=\begin{cases} 
x & k=0\\
x^2 & k=1 \\
(\frac{f(k-1)}{2})^2 & k>1
\end{cases}$$

求一个**最小的** $k$，使得 $f(k)\ge 2^n$。

## Solution

这里直接分析满分做法。

看数据范围，$n\le10^9$，所以想要直接求 $2^n$ 是不可能的，所以要另寻解题方案。

再回来看函数 $f(k)$，根据已知可以求出 $f(k)$ 的前几项分别为（从 $k=1$ 开始）：

$$\displaystyle x^2,\frac{x^4}{2^2},\frac{x^8}{2^6},\frac{x^{16}}{2^{14}},\frac{x^{32}}{2^{30}},\dots$$

所以我们容易发现规律：在上面每一项中，分母的指数为 $2^k$，分子的指数为分母的指数 $-2$，即 $2^k-2$。对于 $f(1)$，可以把 $x^2$ 想成 $\displaystyle \frac{x^2}{2^0}$，也满足上面发现的规律。所以可以得出：

$$\displaystyle f(k)=\frac{x^{2^k}}{2^{2^k-2}}$$

但很显然，这个值非常大，和 $2^n$ 一样，肯定不能直接求。于是我们可以想到，既然 $2^n$ 是 $2$ 的正整数次幂，而 $f(k)$ 也和 $2$ 的幂有关，可以**用对数函数来缩小数的规模，同时保证大小关系不变**啊。

所以，我们可以按照酱紫的思路，通过对 $2^n$ 和 $f(k)$ 求对数来推理。

- 对于 $2^n$，一定：

$$\log_2(2^n)=n$$

- 对于 $f(k)$：

$$\displaystyle \log_2(f(k))=\log_2(\frac{x^{2^k}}{2^{2^k-2}})$$
$$=\log_2(x^{2^k})-\log_2(2^{2^k-2})$$
$$=\sum_{i=1}^{2^k}\log_2(x)-(2^k-2)$$
$$=2^k\log_2(x)-2^k+2$$
$$=2^k(\log_2(x)-1)+2$$

这里用到了对数函数的一些性质，不会的请自行百度，这里就不再赘述了。

而因为 $2^k(\log_2(x)-1)+2$ 里有一个 $2^k$，所以增长的会很快，直接从小到大枚举，再依次判断是否 $\ge n$ 就可以了。

然后就是无解的情况。无解的情况当且仅当 $x=1$ 或 $x=2$，因为只有取这两个值时函数 $f(k)$ 不是递增的，所以**可能无法**到达 $2^n$。

接下来就是分类讨论 $x=1$ 和 $x=2$ 的情况：

- 当 $x=1$ 时：\
即使 $n$ 取最小值 $1$，也有 $2^n=2$，无解，所以 $x=1$ 时一定无解。

- 当 $x=2$ 时：
	- 如果 $n=1$，那么 $2^n=2$，此时 $x$ 已经满足要求了，于是有解，且答案是 $0$。
	- 如果 $n=2$，那么 $2^n=4$，此时在进行 $1$ 次操作后，$f(1)=x^2=4$，满足要求，有解，答案是 $1$。
   - 否则，$f(k)$ 的最大值就是 $4$，于是无解。

然后注意 $k$ 的值要从 $0$ 开始即可。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
#define il inline
using namespace std;
ll x,n;
double lg;
il ll fpow(ll a,ll b)
{
	ll ans=1;
	while(b)
	{
		if(b&1) ans*=a;
		b>>=1;
		a*=a;
	}
	return ans;
}
il double check(ll k)
{
	double now=fpow(2,k)*(lg-1)+2;
	return now;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>x>>n;
	if(x==1)
	{
		cout<<"inf";
		return 0;
	}
	if(x==2)
	{
		if(n==1) cout<<0;
		else if(n==2) cout<<1;
		else cout<<"inf";
		return 0;
	}
	lg=log2(x);
	ll ck=0;
	while(check(ck)<n)
		++ck;
	cout<<ck;
	return 0;
}
```

---

## 作者：2huk (赞：7)

- 最开始你的等级为 $x$。你可以进行若干次「强化」操作。第一次「强化」会将 $x \gets x^2$，之后的「强化」会将 $x \gets \left(\dfrac x2\right)^2$。求至少多少次「强化」操作后使得 $x \ge 2^n$。若不可能达到要求输出 `inf`。
- $2 \le x \le 10^9$，$1 \le n \le 10^9$。

最开始等级为 $x$。可以打表观察第 $t$ 次「强化」操作后 $x$ 将变成什么：



| 「强化」次数 | $0$  |  $1$  |         $2$         |         $3$         |            $4$            |           $5$            | $\dots$ | $t(t \ge 2)$                          |
| :----------: | :--: | :---: | :-----------------: | :-----------------: | :-----------------------: | :----------------------: | :-----: | ---------------------------- |
|     等级     | $x$  | $x^2$ | $\dfrac {x^4}{2^2}$ | $\dfrac {x^8}{2^6}$ | $\dfrac {x^{16}}{2^{14}}$ | $\dfrac{x^{32}}{2^{30}}$ | $\dots$ | $\dfrac{x^{2^t}}{2^{2^t-2}}$ |

可以发现在 $t \ge 2$ 时，第 $t$ 次「强化」操作后等级将变为 $\dfrac{x^{2^t}}{2^{2^t-2}}$。所以可以首先特判「强化」$0$ 次或 $1$ 次是否可行。若不可行，我们希望解这样一个不等式：

$$
\dfrac{x^{2^t}}{2^{2^t-2}} \ge 2^n (t \ge 2, x \ge 2, n \ge 1)
$$

求 $t$ 最小是多少。

做一些推导：

$$
\dfrac{x^{2^t}}{2^{2^t-2}} \ge 2^n\\
\Rightarrow x^{2^t} \ge 2^{n+2^t-2}\\
\Rightarrow (2^{\log_2x})^{2^t} \ge 2^{n+2^t-2}\\
\Rightarrow 2^{2^t\log_2 x} \ge 2^{n+2^t-2}\\
\Rightarrow 2^t\log_2 x \ge n+2^t-2\\
\Rightarrow 2^t \ge \dfrac{n-2}{\log_2 x  - 1}
$$

由于 $\dfrac{n-2}{\log_2 x  - 1}$ 不会很大，所以我们可以直接枚举 $t \in [1, 30]$ 并判断是否合法即可。

```cpp
void solve() {
	int x, n; cin >> x >> n;
	if (n <= 60 && x >= (1ll << n)) puts("0");
	else if (n <= 60 && x * x >= (1ll << n)) puts("1");
	else {
		double y = (n - 2) / (log2(x) - 1);
		for (int t = 2; t <= 30; ++ t )
			if ((1ll << t) >= y) {
				cout << t;
				return;
			}
		puts("inf");
	}
}
```

---

## 作者：forever_nope (赞：4)

### 形式化题面

给定 $x_0$ 和 $n$，$x_1={x_0}^2$，对于 $i>1$ 有：
$$
x_i=\left({x_{i-1}\over2}\right)^2
$$
问最小的非负整数 $k$，使得 $x_k\ge2^n$。

### 题解

我们发现：
$$
\begin{aligned}
x_1&&&={x_0}^2\\
x_2&={{x_1}^2\over4}&&={{x_0}^4\over4}\\
x_3&={{x_2}^2\over4}&&={{x_0}^8\over4^3}\\
x_4&={{x_3}^2\over4}&&={{x_0}^{16}\over4^7}\\
\end{aligned}
$$
容易得出：
$$
x_i={{x_0}^{2^i}\over4^{2^{i-1}-1}}={{x_0}^{2^i}\over2^{2^i-2}}
$$
我们尝试直接带入不等式 $x_k\ge2^n$：
$$
\begin{aligned}
{{x_0}^{2^k}\over2^{2^k-2}}&\ge2^n\\
{x_0}^{2^k}&\ge2^{2^k-2+n}\\
\end{aligned}
$$
注意到两边都是正数，因此考虑两边同时取对数：
$$
\begin{aligned}
2^k\log_2x_0&\ge2^k-2+n\\
2^k(\log_2x_0-1)&\ge n-2
\end{aligned}
$$
注意到如果 $n=1$，那么等式一定成立，且 $k\ge0$​。

注意到如果 $n=2$，那么等式一定成立，且 $k\ge1$。

注意到如果 $x_0=2$，那么只有 $n=2$​，不等式成立。

否则，注意到两边都是正数，我们移项、取对数：
$$
\begin{aligned}
2^k&\ge{n-2\over\log_2x_0-1}\\
k&\ge\log_2\left({n-2\over\log_2x_0-1}\right)\\
k&\ge\log_2(n-2)-\log_2(\log_2x_0-1)
\end{aligned}
$$
然后上取整即可。

代码（Python3）：

```py
from math import log2, ceil
x, n = map(int, input().split())
if n == 1: print(0)
elif n == 2: print(1)
elif x == 2: print('inf')
else: print(ceil(log2(n - 2) - log2(log2(x) - 1)))
```

---

## 作者：kairuigg (赞：3)

# P10320 勇气（Courage）
## 题目大意
对于一个数 $x$ 都可以将其变为 $x^2$，但除第一次变化外，之后每一次变化都要先变为原来的一半。问经过多少次变化可以到达 $2^n$。

## 思路
因为 $2^n$ 会特别大（大到会爆 long long），所以我们不能直接和 $2^n$ 比较，所以我们可以换一种思考方式：直接比较指数。我们可以把底数都换成 2，则 $x$ 就可以表示为 $2^{\log_2{x}}$，所以我们就可以将 $\log_2{x}$ 和 $n$ 比较。
## 过程
我们可以把每个的操作转换成指数上的操作。所以每一次的 $x=x^2$ 的操作都可以变成 $\log_2{x}\cdot2$，$x\div2$ 可以变成 $\log_2{x}-1$，然后根据题目模拟就行了。我们还需要考虑一种 $inf$ 的情况。当 $x=2$（因为保证 $x\geq2$ 所以不考虑 $x<2$ 的情况）并且 $n>2$ 时 $x^2$ 会和 $x\div2$ 的操作相互抵消 $x$ 的值不会发生变化，所以永远不会比 $2^n$ 大，故此需要输出 $inf$。
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double //注意样例2的解释，会有小数情况，如果不用double会死循环导致TLE
using namespace std;
inline int read(){//可有可无的快读
    int x=0,ff=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            ff=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*ff;
}
int n;
double x;
int ans;
signed main(){
    x=read();
    n=read();
    double cnt=log2(x);//cnt表示指数
    if(log2(x)>=n){//如果在没有操作前log2(x)就大于等于n，就没必要操作了，直接输出0；
        cout<<0;
    }
    else if(x==2&&n>2){
        cout<<"inf";
    }
    else{
        cnt*=2;//第一次平方操作让指数乘2
        ans++;//操作次数+1
        while(cnt<n){//如果没有满足cnt>=n就一直操作
            ans++;//操作次数+1
            cnt-=1;//每次操作前衰减为原来的一半所以（就是原数除以2），所以指数-1
            cnt*=2;//平方操作指数乘以2
        }
        cout<<ans;//最后输出操作次数 
    }
    return 0;
}

---

## 作者：selcouth (赞：3)

由于想要达到的攻击力为 $2^n$，我们可以将 $x$ 转化 $x = 2^{\log_2x}$，通过比较指数来直接得出 $2^n$ 与 $x$ 之间的大小关系。

因此题目中的两种操作就变成了：

- 强化：指数部分乘 $2$​。
- 衰减：指数部分减 $1$。

而无解只存在一次技能使用之后没有效果的情况，也就是当 $x = 2$ 同时 $n > 2$​ 的时候。（如果指数部分一开始就比 $n$​ 大，则不需要操作就得到了答案）

然后只需要模拟指数部分的操作即可：

```cpp
#include <bits/stdc++.h>
#define double long double
#define int long long
using namespace std;
double x, n;
int t = 1;

signed main()
{
	cin >> x >> n;
	if(x == 2 && n > 2)
	{
		cout << "inf";
		return 0;
	}

	double target = log2(x);
	if(target >= n) t = 0;
	else
	{
		target *= 2;
		while(target < n)
		{
			target -= 1;
			target *= 2;
			t++;
		}
	}

	cout << t;
	return 0;
}
```

---

## 作者：DFM_O (赞：3)

## [P10320 题目](https://www.luogu.com.cn/problem/P10320)


### 解题思路
首先，若 $x\ge2^n$，则直接输出 $0$，若 $n\le2$，则直接输出 $1$，若 $x=2$ 且 $n>2$，则直接输出 `inf`。

然后我们可以列出第 $m$ 次操作后的情况：
$$x^2,\frac{x^4}{4},\frac{x^8}{64},\frac{x^{16}}{16384}$$
不难发现，第 $m$ 次操作后，此数变为：
$$\frac{x^{2^m}}{4^{2^{m-1}-1}}=\frac{x^{2^m}}{2^{2^m-2}}$$
令 $x=2^k$，则第 $m$ 次操作后此数变为：
$$\frac{(2^k)^{2^m}}{2^{2^m-2}}=\frac{2^{2^m\times k}}{2^{2^m-2}}=2^{2^m\times k-2^m+2}=2^{2^m\times(k-1)+2}$$
现在我们需要找到一个 $m$ 使得 $2^{2^m\times(k-1)+2}=2^n$，即使得 $2^m\times(k-1)=n-2$，把 $m$ 解出来并向上取整即可。

### Code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
long long poww(long long a,long long b)
{
    long long ss=1;
    while(b)
    {
        if(b&1)
            ss=ss*a;
        a=a*a;
        b>>=1;  
    }
    return ss;
}
signed main()
{
	ios::sync_with_stdio(false);
	int x,n;
	cin>>x>>n;
	if(n<32)
	{
		if(x>=poww(2,n))
		{
			cout<<"0";
			return 0;
		}
	}
	if(n<=2)
	{
		cout<<"1";
		return 0;
	}
	if(x==2)
	{
		cout<<"inf";
		return 0;
	}
	n-=2;
	double xx=x*1.0;
	double k=log2(xx);
	double m1=n*1.0/(k-1);
	double m=log2(m1)+0.5;
	cout<<fixed<<setprecision(0)<<m;
    return 0;
}
```

---

## 作者：Mier_Samuelle (赞：2)

设第 $k$ 次发动技能后的攻击力为 $f_k$，那么根据 $f_k=\begin{pmatrix}\dfrac{f_{k-1}}{2}\end{pmatrix}^2$，有 $f_k=\dfrac{x^{2^k}}{2^{2^k-2}}\,(k\ge1)$。

根据下表找规律也能得出上述结论：

| $k=$ | $0$ | $1$ | $2$ | $3$ | $4$ | $5$ | $\dots$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $f_k=$ | $x$ | $x^2$ | $\dfrac{x^4}{2^2}$ | $\dfrac{x^8}{2^6}$ | $\dfrac{x^{16}}{2^{14}}$ | $\dfrac{x^{32}}{2^{30}}$ | $\dots$ |


几种特殊情况：

- 若 $x=2$ 且 $n>2$，可以证明无论如何都不可能满足要求，输出 ``inf``。
- 若 $x\ge2^n$ 则答案直接为 $0$，但是由于 $2^n$ 太大所以要两边都取 $\log_2$ 来判断，即判断 $\log_2x\ge n$。

对于其它情况，需要找出最小正整数 $k$，使得

$$\dfrac{x^{2^k}}{2^{2^k-2}} \ge 2^n$$

根据 $x=2^{\log_2x}$，可以将上面这个不等式转化为

$$\dfrac{\begin{pmatrix}2^{\log_2x}\end{pmatrix}^{2^k}}{2^{2^k-2}}\ge2^n$$

化简得

$$\begin{aligned} 2^k \log_2x-(2^k-2) &\ge n  \\ 2^k &\ge \dfrac{n-2}{\log_2x-1} \\ k &\ge \log_2 \dfrac{n-2}{\log_2x-1} \\  \end{aligned}$$

将右式向上取整即为答案。

---

## 作者：Hulless_barley (赞：2)

# [P10320 勇气（Courage）](https://www.luogu.com.cn/problem/P10320)

# 思路
很容易发现，当 $x=2,n>2$ 时 $x$ 无论怎么变化，最终会在 $4$ 时止步，所以无解。当 $x=2,n\le2$ 时，就两种情况，手算一下。

当 $x>2^n$ 时，已经满足要求，直接输出 $0$，考虑到精度问题，可以比较 $\log_2x$ 和 $n$ 的大小。

几种特殊情况特判一下。

```cpp
if(x==2){
	if(n==1)cout<<0;
	else if(n==2)cout<<1;
	else cout<<"inf";
	return 0;
}
if(log2(x)>=n){
    cout<<0;
    return 0;
}
```

第一次变化是 $x\to x^2$，之后则是 $x\to \frac{x^2}{4}$。只需要运用切题基本打法之一——暴力枚举即可。还是因为精度问题，所以取其对数，比较 $\log_2x$ 与 $n$ 的大小。设 $\log_2x=t$，则第二次或之后的变化为 $t\to (t-1)\times2$，一顿暴力水过。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,n,ans=1;
double t;
int main(){
	cin>>x>>n;
	if(x==2){
		if(n==1)cout<<0;
		else if(n==2)cout<<1;
		else cout<<"inf";
		return 0;
	}
	if(log2(x)>=n){
	    cout<<0;
	    return 0;
	}
	x*=x;
	t=log2(x);
	while(t<n)
		t=(t-1)*2,ans++;
	cout<<ans;
	return 0;
}
```

---

## 作者：zjpwdyf (赞：2)

首先发现到 $2^n$ 十分庞大，连 `double` 都存不下，所以不难想到此题为数学结论题。

设 $F_i$ 表示 $x$ 经过 $i$ 次强化后所得的值，根据题目易得：

$$F_i = \begin{cases} x^2, \hspace{1cm} i=1 
\\
(\frac {F_{i-1}}{2})^2,\hspace{0.42cm} i > 1 \end{cases}$$


先考虑几种特殊情况：

当 $x=1$ 时，$F=[1, \frac 1 4, \frac{1}{64} \dots]$，显然对于任意 $n \ge 1$，都无解。

当 $x=2$ 时：$F=[4, 4, 4, \dots]$，显然仅 $n \le 2$ 时有解，$n > 2$ 时也无解。

接下来回到一般情况：

观察到对于任意的 $x$，都有 $F=  [x^2, \large\frac{x^4}{2^2}, \frac{x^8}{2^6}, \frac{x^{16}}{2^{14}} \dots]$

不难发现 $F_i = \large \frac{x^{2^k}}{2^{2^k-2}} \normalsize =  4 \times \large (\frac x 2)^{2^k}$，也就是说问题转化为求 $4 \times \large (\frac x 2)^{2^k} \normalsize \ge 2^n$ 的最小整数解。

将指数化为对数，得 $2^k \ge \log_{\frac x 2} 2^{n-2} = (n-2)\times \log_{\frac x 2}2$。

继续转化，得 $k \ge \log_{2}((n-2)\times \log_{\frac x 2}2)) = \log_{2}\frac{n-2}{\log_2 \frac x 2}$，记其为 $M$。

由于答案为整数，所以答案为 $\max(0, \lceil M \rceil)$。

为什么要与 $0$ 取 $\max$ 呢？因为存在一开始就满足 $x\ge2^n$ 的情况，此时 $M \le 0$，若直接输出则会出错。

考场代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	double x, n, ans;
	cin >> x >> n;
	if(x == 1) cout << "inf";
	else if(x == 2 && n > 2) cout << "inf";
	else if(n <= 2) cout << n - 1;
	else{
		double ans = log2((n - 2) * (1 / log2(x / 2)));
		if(ans < 0) ans = 0;
		cout << (int)ceil(ans);
	}
	return 0;
}
```

---

## 作者：sbno333 (赞：2)

考虑列式子。

由于 $n\le10^9$，因此不能暴力。

假设进行了 $s$ 次操作。

如果没有除以 $2$，则操作后变为 $x^{2^s}$。

第一次操作后又进行了 $s-1$ 次操作。

因此第一次操作后的除以二影响为 $2^{2^{s-1}}$。

最后一次除以 $2$ 的影响为 $2^{2^1}$，因为最后一次操作后不需要除以 $2$。

那么 $s$ 此操作后答案为 $\cfrac{x^{2^s}}{\prod\limits_{i=1}^{s-1}2^{2^i}}=\cfrac{x^{2^s}}{2^{\sum\limits_{i=1}^{s-1}2^i}}=\cfrac{x^{2^s}}{2^{2^s-2}}$。

如果需要 $s$ 次操作成立，则有不等式 $\cfrac{x^{2^s}}{2^{2^s-2}}\ge 2^n$。

接着就是愉快的推式子了！

$\cfrac{x^{2^s}}{2^{2^s-2}}\ge2^n$ 移项得 $x^{2^s}\ge2^n\times2^{2^s-2}$。

整理得到 $x^{2^s}\ge2^{n+2^s-2}$。

接着是关键的一步。

计算得出如下：

$2^{\log_2x\times{2^s}}\ge2^{n+2^s-2}$。

然后底数相同，次数越大幂越大。

$\log_2x\times{2^s}\ge n+2^s-2$。

移项得到 $(\log_2x-1)\times{2^s}\ge n-2$。

再次移项，此时特判 $\log_2x=1$，即 $x=2$，发现每次操作完并处以二后仍然会变回 $2$，所以这是容易计算的。

剩下的情况，得到 ${2^s}\ge\cfrac{n-2}{\log_2x-1}$。

然后简单得到 $s\ge\log_2\cfrac{n-2}{\log_2x-1}$。

由于最小化 $s$，于是 $s$ 取为 $\lceil\log_2\cfrac{n-2}{\log_2x-1}\rceil$。

相信精度，毕竟比暴力好。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int x,n;
	cin>>x>>n;
	if(x==2){
		if(n==1){
			cout<<0<<endl;
		}else if(n==2){
			cout<<1<<endl;
		}else{
			cout<<"inf"<<endl;
		}
	}else{
		long double s;
		s=log(x*1.0)/log(2.0);
		s--;
		s=(n-2.0)/s;
		s=log(s)/log(2.0);
		cout<<int(ceil(s))<<endl;
	}
	return 0;
} 
```

---

## 作者：封禁用户 (赞：2)

考虑每次操作后的 $\log_2 x$。若设 $p = \log_2 x$。

每一次乘 $x$ 后，若设现在的 $p$ 为 $np$，那么 $np = p \times 2$；

每一次除以 $2$ 后，若设现在的 $p$ 为 $np$，那么 $np = p -1$。

什么时候是无解状态呢？

发现 $x=2$ 时，每次操作后的 $x$ 只能是 $2$ 或 $2^2 =4$。其中 $2$ 是没有操作的 $x$。

即当 $x = 2$ 时，答案仅为 $x = 2^1$，或是 $x = 2^2$，不会出现更大的情况。

而其它的 $x$，都会因为操作而慢慢增加，所以它们一定能增加到 $2^n$ 及以上。

所以只有这种情况，即 $x = 2$ 且 $n > 2$ 时无解。

另外如果操作前 $2^n \le x$，要特判，输出 $0$。

第一次操作与以后的操作不同，所以要单写出来。

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int x, n, cnt = 0;
	cin >> x >> n; 
	if (x == 2 && n > 2)
	{
		cout << "inf";
		return 0;
	}
    double result = log2(x);
    if (result >= n)
    {
    	cout << 0;
    	return 0;
	}
    result *= 2, cnt++;
	while (1)
	{
		if (result >= n)
		{
			cout << cnt;
			return 0;
		}
		result--;
		result *= 2, cnt++;
	}
}
```

---

## 作者：xingshuyan000 (赞：2)

update on 2024/12/22：重新排版了一下 LaTeX，然后更新了一下码风。

# 题目分析
其实这道题就是个纯数学题，先要找到规律，然后再对解这道题的公式进行推导，把公式推出来以后，再考虑一下一些特殊情况，然后这道题基本就解决了。此题编程不难，但就是推导过程比较麻烦（其实也不算特别麻烦），需要用到**高一上学期的数学**内容，主要是**指数和对数**部分。

可以先列举前面几种情况，找一下规律。

设攻击力的初始值为 $x$。

经过第一次变换，攻击力变为 $x^2$，其实可以看成是 $\frac{x^2}{1}$，也就是$\frac{x^2}{2^0}$；经过第二次变换，攻击力变为 $(\frac{x^2}{2})^2$，也就是 $\frac{x^4}{2^2}$；经过第三次变换后，攻击力变为 $(\frac{x^4}{8})^2$，也就是 $\frac{x^8}{2^6}$；经过第四次变换，攻击力变为 $(\frac{x^8}{128})^2$，也就是 $\frac{x^{16}}{2^{14}}$。

看到这里以后，其实已经不难发现，经过 $i(i\in \mathbb N^*)$ 次强化以后，攻击力的分子值变为 $x^{2^i}$，分母的值变为 $2^{2^i-2}$，整个式子变为 $\frac{x^{2^i}}{2^{i-2}}$，并且要满足 $\frac{x^{2^i}}{2^{i-2}} \ge 2^n$。

把分母乘到不等号右边并化简，得

$$x^{2^i} \ge 2^{n-2+2^i}$$

可以把 $2^i$ 看成一个整体，作 $x$ 的指数，然后进行对数运算并化简，得 _（后面的为了方便计算，我就把不等号变成等号了，最后记得向上取整）_ 

$$2^i = (n-2+2^i)\log_x2$$

把 $\log_x2$ 移到等号左边，得

$$2^i·\log_2x = n-2+2^i$$

再进行移项、合并同类项，得

$$2^i(\log_2x-1) = n-2$$

把 $\log_2x-1$ 移到等号右边，得

$$2^i=\frac{n-2}{\log_2x-1}$$

再对 $i$ 取对数并向上取整，得

$$i=\lceil\log_2{\frac{n-2}{\log_2x-1}}\rceil$$

其实这就已经出来了，直接编程，算出来 $\log_2{\frac{n-2}{\log_2x-1}}$ 的值，并对其进行向上取整就解得 $i$ 的值，然后再输出答案即可。

不过这道题当中有一些特殊情况需要判断：

- 当 $x=2$时，因为无论经过多少次变换，$x$ 的值一直是 $2$ 或 $4$，所以此时当 $n > 2$ 的时候，无解，输出 `inf`。

- 当 $x\ge 2^n$ 时，经过指对数互化，可以得到 $\log_2x \ge n$，此时不用经过强化就可以满足要求，所以直接输出 $0$，然后结束程序。

- 当 $x^2 \ge 2^n$ 时，经过指对数互化，可以得到  $2\log_2x \ge n$，此时只需要强化一次就可以满足要求，所以直接输出 $1$，然后结束程序。

而且请注意：**先判断特殊情况，而且一定要按照上面这三个特殊情况的顺序编程，即先判断输出 `inf`，再判断输出 $0$，最后再判断输出 $1$，否则会导致有几个测试点过不去**。~~（我最开始特判顺序就搞错了，就导致一直有3个测试点过不去）~~

好了，分析完了，上代码。

# Code
```cpp
#include<bits/stdc++.h> 
using namespace std;
int x, n;
int main()
{
	cin >> x >> n;
	if(x == 2 && n > 2){ //特判输出inf的情况
		cout << "inf";
		return 0;
	}
	if(log2(x) >= n){ //特判输出0的情况
		cout << "0";
		return 0;
	}
	if(2 * log2(x) >= n){ //特判输出1的情况
		cout << "1";
		return 0;
	} 
	double a1, a2; //a1是等号右边对数的真数中的分母，a2是等号右边整个对数的值，记得开double
	int ans; //存储答案
	a1 = log2(x) - 1;	
	a2 = log2((n - 2) * 1.0 / a1);
	ans = ceil(a2); //记得答案要向上取整
	cout << ans;
	return 0;
}
```

---

## 作者：modfish_ (赞：1)

## 思路
设 $a_i$ 表示强化 $i$ 次后的攻击力。则 $a_0=x,a_1=x^2$。

对于任意 $i\ge 2$，有：

$$a_i=(\frac{a_{i-1}}{2})^2=\frac{a_{i-1}^2}{4}$$

然后很容易得到：

$$a_i=\frac{x^{2^i}}{2^{2^i-2}}$$

设最终结果为 $t$，则：

$$\frac{x^{2^t}}{2^{2^t-2}}\ge 2^n$$

两边同时取以 $2$ 为底的对数：

$$2^t\log_2x-(2^t-2)\ge n$$

$$(\log_2x-1)2^t\ge n-2$$

题目保证 $x\ge 2$，所以 $\log_2x-1\ge 0$，分情况讨论：

- $x=2$，即 $\log_2x-1=0$。当且仅当 $n\le 2$ 时有解。$n=1$ 时，答案为 $0$，$n=2$ 时，答案为 $1$。

- $x>2$，则：

$$2^t\ge \frac{n-2}{\log_2x-1}$$

$$t\ge \log_2\frac{n-2}{\log_2x-1}$$

求出 $\log_2\frac{n-2}{\log_2x-1}$ 向上取整即可。

## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
	long double x, n;
	cin >> x >> n;
	if(n == 1){
		printf("0\n");
		return 0;
	}
	if(x == 2){
		if(n < 2) printf("0\n");
		else if(n < 3) printf("1\n");
		else printf("inf\n");
		return 0;
	}
	ll ans = ceil(logl((n - 2) / (logl(x) / logl(2) - 1.0)) / logl(2));
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：zzx114514 (赞：1)

# 题目大意
给定正整数 $x,n$，对 $x$ 进行多次操作，第一次使得 $x\gets x^2$，接下来每次操作使得 $x\gets \frac{x^2}{2}$，求最小操作数 $k$ 使得操作 $k$ 次后 $x\ge 2^n$。
# 解题思路
注意到 $2\le x\le 10^9,1\le n\le 10^9$，暴力显然会超出 `long long` 存储上限，考虑数学推导（毕竟这是道数学题）。  
## 推导过程
设 $x$ 操作 $k$ 次后为 $x_k$，先列一下前几项：
$$x_1=x^2=\frac{x^2}{2^0}$$
$$x_2=(\frac{x_1}{2})^2=\frac{x^4}{2^2}$$
$$x_3=(\frac{x_2}{2})^2=\frac{x^8}{2^6}$$
$$x_4=(\frac{x_3}{2})^2=\frac{x^{16}}{2^{14}}$$
$$\cdots$$
通过找规律我们可以得到
$$x_k=\frac{x^{2^k}}{2^{2^k-2}}$$
题目要求最小的 $k$ 使得 $k$ 满足
$$x_k\ge2^n$$
即
$$\frac{x^{2^k}}{2^{2^k-2}}\ge2^n$$
去分母
$$x^{2^k}\ge 2^{2^k-2+n}$$
由于
$$x=2^{log_2x}$$
其中 $\log$ 是对数函数，当 $a^c=b$ 时 $c=\log_ab$，因此 $\log_2x$ 就是指当这个数是 $2$ 的指数时该幂等于 $x$，不懂的可以[点这里](https://baike.baidu.com/item/%E5%AF%B9%E6%95%B0/91326?fromtitle=log&fromid=39110&fr=aladdin)进一步了解。  

所以原式可化为
$$(2^{\log_2x})^{2^k}\ge2^{2^k-2+n}$$
即
$$2^{\log_2x\times2^k}\ge2^{2^k-2+n}$$
因为指数函数具有单调性，同底数幂比较大小只需比较指数即可，得
$$\log_2x\times2^k\ge2^k-2+n$$
显然，当 $x=2$ 时原式化为
$$2^k\ge2^k-2+n$$
即
$$n-2\le0$$
即
$$n\le2$$
此时若 $n>2$，则不等式矛盾，$k$ 无解。

当 $x>2$ 时，由于 $2\le x\le 10^9,1\le n\le 10^9$，显然原不等式有解，因为左边乘法的增长速度比右边加法的增长速度快（这么说可能不严谨，但是本人初一牲还没学函数，体谅一下），从 $1$ 开始枚举 $k$ 即可。

注意有特殊情况，即无需操作直接达到要求，此时要特判，详细见下面的**代码写法**。
## 代码写法
先特判是否无需操作，因为 $\log_210^9<30$，所以要先判断 $n$ 是否小于 $30$，再判断 $x$ 是否小于 $2^n$，否则会溢出。

接下来判断是否无解，只需判断 `x==2 && n>2` 即可，此时根据上述推导是无解的。

最后从 $1$ 开始枚举 $k$，若 $k$ 满足 $\log_2x\times2^k\ge2^k-2+n$ 就直接输出并 `return 0;`，此时找到的一定是最小的。

注意 C++ 自带 `log2` 函数，可以直接拿来用，前提是要有 `math.h` 头文件。而且底数为 $2$ 的幂运算可以使用二进制左移，这样节省时间，并且避免了 `pow` 函数的各种问题，$2^k$ 可以表示为 `1ll<<k`，这里的 `1ll` 表示 `long long` 类型的 $1$，不然会炸。
# 完整代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll x,n,k;//不开long long见祖宗
int main()
{
	cin>>x>>n;
	if (n<30 && x>=(1ll<<n))//特判不用操作的情况，这里用二进制和long long类型的数字
	{
		cout<<0;
		return 0;
	}
	if (x==2 && n>2)//特判无解
	{
		cout<<"inf";
		return 0;
	}
	while(true)
	{
		k++;
		if (log2(x)*(1ll<<k)>=(1ll<<k)-2ll+n)//如果找到k
		{
			cout<<k;//直接输出
			return 0;
		}
	}
	return 0;
}

```

---

## 作者：mystic_qwq (赞：1)

简化题意：给定两整数 $x$ , $n$，第一次 $x\gets x^2$，之后的每次 $x\gets (\frac x 2)^2$，问最少多少次 $x\ge 2^n$ $(2\leq x\leq 10^9)$，或报告无解。

这道题考的是数字的相对变化。

将 $x$ 变为 $x^2$ 等价于将 $2^n$ 开根号，即 $n\gets \frac n 2$。注意这里不能向下取整。之后的 强化中 $x\gets(\frac x 2)^2$ 等效于右式 $2$ 的次数先 $+1$ ，再 $/2$ 。也就是令 $n\gets \frac{n+1}2$。这样一直重复，最后看 $n$ 经过多少次后 $\leq x$ 即可。

然后注意一下细节：观察知，当 $x=2$ 时，最高强化到 $4$，也就是 $n=2$ 的情况。此时次数为 $1$ 。$x>2$ 时，则可以无限增长。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define double long double
double Pow(double x){
  if(x>=30) return 0x7f7f7f7f; //大约2.13*1e9
  return pow(2,x); //可以防越界
}
main(){
  int x,n;
  cin>>x>>n;
  if(x>=pow(2,n)){ //意味着一次都不需要
    cout<<0;
    return 0;
  }
  //cout<<Pow(100.)<<endl;
  if(x==2){
    if(n==2) return cout<<1,0; //特殊情况
    else return cout<<"inf",0; //返回的是逗号后面的
  } 
  double r=n/2; //第一次先折半
  int ans=1;
  while(Pow(r)>x)
    r=(r+1)/2,++ans;
  cout<<ans;
}
```

---

## 作者：Autumn_Rain (赞：1)

赛时做出来的，水篇题解。
### 20 tps

这个思路很好想，直接模拟即可。每次平方再除以二，运行若干次还没结束就直接输出 ```inf```。

然而数据这么大，肯定是 TLE 了，于是我们开始分析数据范围。
### 100 tps
发现 $n$ 的范围已经很大了，那么我们反其道而行之。

- 不比较 $x$ 和 $2^{n}$，比较 $\log_{2}{x} $ 和 $\log_{2}{2^{n}} $ 即  $\log_{2}{x} $ 和 $n$。

- 改 $x^{2}$ 这个操作为 $2^{n}$ 开方，其实等同于把指数  $n$ 除以 2。

- 如果此时满足条件就输出，否则执行 $x$ 除 2 这个操作。

- 转换一下，变成 $2^{n}$ 乘 2，也就是指数 $n$ 加一。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
long double x,n;
ll ans; 
int main(){
	cin>>x>>n;
	while(log2(x)<n){
		ans++;
		n=n/2.0;
		if(log2(x)>=n){
			cout<<ans;
			return 0;
		}
		n++;
		if(ans>=50){
			cout<<"inf";
			return 0;
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Six_chestnuts (赞：0)

# 题意

给定两个数 $n,x$，你可以将 $x$ 先除以 $2$ 再把 $x$ 变为 $x^2$（第一次不用除以 $2$），问最少要多少次操作才能让 $x \ge 2^n$，若永远无法完成目标就输出 `inf`。

# 分析

1. 我们可以简单算一下 $x$ 大约为 $2$ 的多少次方，再每一次将这个值乘以 $2$ 再减 $2$ 最后算到这个值大于 $n$ 时即可。

2. 但是题目还有一个 `inf` 的情况，只需在循环中判断，如果这个值 $\le 2$ 则把直接输出 `inf` 同时，如果开始时就完成了的话就输出 $0$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x,n,ans=1; 
signed main()
{
	cin>>x>>n;
	int y=x*x;
	if(y==x)
	{
		cout<<"inf";
		return 0;
	}
	else if(log2(x)>=n)
	{
		cout<<0;
		return 0;
	}
	x=y;
	double cnt=log2(x);
	while(cnt<n)
	{
		if(cnt<=2)
		{
			cout<<"inf";
			return 0;
		}
		cnt*=2,cnt-=2,ans++;
	}
	cout<<ans;
	return 0;
 } 
```

---

## 作者：Elhaithan (赞：0)

首先观察 $n$ 的范围：$1\le n \le 10^9$，可知，用普通的知（bao）识（li）是解决不了这道题的。

那应该怎么做呢？这时候就要引入[对数](https://baike.baidu.com/item/%E5%AF%B9%E6%95%B0/91326)的概念。

简单地说，若 $a^n=b$，则 $n=\log_ab$，对数运算就是求指数 $n$ 的过程。

如果将攻击力 $x$ 转化为以 $2$ 为底的幂，每一次强化相当于攻击力的指数乘以二，每一次衰减相当于攻击力的指数减一。特别的，第一次强化不会衰减。

设 $d$ 为以 $2$ 为底 $x$ 的对数，即 $d=\log_2x$，再对 $d$ 进行模拟，若 $d\ge n$ 说明已达到要求。

另外，还需要注意特判。当 $x=2$ 时，无论如何强化其值始终不变；注意 $n=1$ 时不需要强化就能达到要求，$n=2$ 时恰好强化一次就能满足要求，其余情况皆达不到要求。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int x, n, cnt = 0;
double d;
signed main()
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> x >> n;
	if(x == 2){
		if(n == 1){
			cout << 0;//不需要强化
			return 0;
		}
		else if(n == 2){
			cout << 1;//恰好强化一次
			return 0;
		}
		else{
			cout << "inf";//不可能达到要求
			return 0;
		}
	}
	d = log2(x);//对数
	while(1){
		if(d >= n){
			cout << cnt;
			return 0;
		}
		cnt ++;
		if(cnt != 1) d -= 1;//第一次不衰减
		d *= 2;
	}
	return 0;
}
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10320)
## 题目意思
给你一个数 $x$，第一次操作 $x \gets x^2$，第二次操作 $x \gets {(\dfrac{x}{2})}^2$，第三次操作 $x \gets {(\dfrac{x}{2})}^2$……问几次后，$x \ge 2^n$。
## 解题思路
一看到题目，我就兴奋得不得了：这么简单，暴力！

结果，15pts（AC,WA,TLE），因为 $1 \le n \le 10^9$。

~~然后我又好不容易骗了 20 分。~~

那他为什么要给出 $2^n$，而不是 $n$ 呢？

其实我们可以把 $x$ 转化为 $2^s$ 加一些东西，再把这些东西舍去（因为是 $x \ge 2^n$，舍去后 $x=2^n$），这样，第一次操作后 $x=2^{2 \times s}$，第二次操作后 $x=2^{2 \times(2\times s-1)}$……

这样就可以分类讨论了。

- $x<2$，显然刚开始就可以，输出 $0$；
- $x=2$，如果 $n \le 2$，一次操作就可以，输出 $1$,否则多少次都不可能，输出 `inf`；
- 否则，模拟，先求出 $\log_2 x$，如果 $\log_2 x \ge n$，刚开始就可以，输出 $0$，否则先乘 $2$，当 $s<n$，计数器加一，$s\gets (s-1)\times 2$。计数器初始值为 $1$。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int x,n,s=0,ss=1;
	cin>>x>>n;
	if(n<2)cout<<0;
	else if(x==2)
	{
		if(n<=2)cout<<1;
		else cout<<"inf";
	}
	else
	{
		for(int i=x;i!=1;i/=2)s++;
		if(s>=n)cout<<0;
		else
		{
			s*=2;
			for(;s<n;s=(s-1)*2)ss++;
			cout<<ss;
		}
	}
	return 0;
}

```

---

## 作者：Mortidesperatslav (赞：0)

先用对数换底公式把 $x$ 的幂转化为 $2$ 的幂，然后每次进行如下变换：

若当前的值为 $2^x$，则变换为 $2^{2x-1}$。

然后指数就变成了 P10252 的 线性变换。详见我的 [这篇题解](https://www.luogu.com.cn/article/9gbf2qf8)。

于是我们暴力模拟即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
double log(double b, double n){
	return log2(n) / log2(b);
}
int main(){
	int x, n, cs = 0;
	cin >> x >> n;
	double l2x = log2(x * 1.00);
	double nn = n, nw = l2x;
	if (nw >= nn - 0.01){
		cout << 0;
		return 0;
	}
	if (x == 2 && n == 2){//特判，否则会死循环
		cout << "1";
		return 0;
	}
	while (1){//暴力模拟
		if (nw * 2.0 - 1.0 <= nw + 0.1){
			cout << "inf";
			return 0;
		}
		nw = nw * 2.0;
		cs++;
		if (nw >= nn - 0.01){
			cout << cs;
			return 0;
		}
		nw -= 1.0;
	}
}
```

---

## 作者：zyn_ (赞：0)

# P10320 勇气（Courage）

## 题目大意

有一个数 $x$，第一次操作将 $x$ 变为 $x^2$，以后每次操作将 $x$ 变为 $(\dfrac{x}{2})^2$。求至少几次操作可以让 $x\ge 2^n$。

### 情况一：$x\le 2$

若 $x=1$，无论如何操作 $x\le 1$，输出 `inf`。

若 $x=2$ 则第一次操作后 $x=4$，以后 $x$ 不变。如果 $n=1$ 输出 $0$，如果 $n=2$ 输出 $1$，否则输出 `inf`。

### 情况二：$x\ge 3$

这时候不可能输出 `inf`。

考虑将 $x$ 和 $2^n$ 取**对数**，设 $y=\log_{2}x$。

那么，第一次操作，$y$ 变成 $2y$。以后的操作，$y$ 变成 $2y-2$。目标是使 $y\ge n$。

由于 $y$ 指数级增长，故答案在对数级别，模拟即可。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
ll n,k,l,r,mid;double d,e;
int main(){
	cin>>k>>n;
	if(k==1)puts("inf");
	else if(k==2){
		if(n==1)puts("0");
		else if(n==2)puts("1");
		else puts("inf");
	}
	else{
		d=log2(k);
		if(n<=d)puts("0");
		else{
			int i=0;
			d*=2;
			for(i=1;;++i){
				if(d>n-1e-9)break;
				d=(d-1)*2;
			}
			cout<<i;
		}
	}
	return 0;
}
```

---

## 作者：zzcsmart (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10320)

由题可知，最简单明了的做法是暴力枚举每一次技能后的攻击力，但是 $1 \leq n \leq 10^9$ 会超时，所以只能对于子任务一和子任务三。

接下来讲正解。对于第 $k$ 次使用技能后的攻击力 $a_k$， 递推可知 $a_k= \left( \frac{a_{k-1}}{2} \right)^2$。

一般情况下，要求最小的 $k$ 使得 $\frac{x^{2^k}}{2^{{2^k}-2}} \geq 2^n$。

即 $k \geq \lceil \log2 \frac{n-2}{\log_2 x-1} \rceil$。

但是还有特殊情况：

+ 当 $x \geq 2^n$ 时，不用技能，输出 $0$。 
+ 当 $x=2$ 且 $n>2$，输出无解。
+ 当 $x=n=2$，用一次技能，输出 $1$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,m;
	cin>>n>>m;
	if(n>=pow(2,m)){//特殊情况1
		cout<<0;
		return 0;
	}
	if(n==2&&m>2){//特殊情况2
		cout<<"inf";
		return 0;
	}
	if(n==2&&m==2){//特殊情况3
		cout<<1;
		return 0;
	}
	double l=(m-2)/(log2(n)-1);
	long long k=(long long)(ceil((double)(log2(l))));//套公式
	cout<<k;
	return 0;
}
```

谢谢观看。

---

## 作者：TigerTanWQY (赞：0)

# [P10320 勇气（Courage）](https://www.luogu.com.cn/problem/P10320) 题解

如果直接模拟，可以发现就算是 `__int128` 也存不下 $2^{10^9}$。

然后再看，可以发现，设 $k=\log_2 n$，则无论是 $n\leftarrow n\div2$ 还是 $n\leftarrow n\times n$，答案都会直接作用于 $k$。

具体来说，如果是 $n\leftarrow n\div 2$，那么 $k\leftarrow k-1$；如果 $n\leftarrow n\times n$，那么 $k\leftarrow k\times 2$。

于是你只需要将 $k$ 初始设为 $\log_2 x$，然后进行 $n$ 次以下操作：

1. $k\leftarrow k-1$

2. $k\leftarrow k\times 2$

最后输出操作了几次即可。

**P.S.** 如果 $x=2$ 且 $n>2$，则输出 `inf`；如果 $x=2$ 且 $n=2$，则输出 `1`。原理大家自己想一想。

## AC Code

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	long long x, n;
	cin >> x >> n;
	if(x == 2 && n > 2) {
		cout << "inf";
		return 0;
	} else if(x == 2 && n == 2) {
		cout << "1";
		return 0;
	}
	long double k = log(x) / log(2) + 1;
	long long ans = 0;
	while(k < n) {
		k -= 1;
		k *= 2;
		++ans;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：zxh923 (赞：0)

# P10320 勇气（Courage）题解

[题目传送门](https://www.luogu.com.cn/problem/P10320)

### 思路

赛时脑子一热，想到了一个奇怪的做法。

我们用自带的 $\log_2$ 函数求出 $x$ 是二的几次方，注意这是个浮点数。然后我们按照题目模拟，如果发现次数已经很多就输出不可能。

注意在开始模拟之前特判 $0$ 次和 $1$ 次的情况。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
double n,x;
int cnt;
signed main(){
	cin>>x>>n;
	x=log2(x);//先把x转换成与n相同意义 
	if(x>=n){//如果已经可以就输出 
		cout<<0;
		return 0;
	}
	x*=2.0;//特殊的第一次操作 
	if(x>=n){
		cout<<1;
		return 0;
	}
	while(x<n){//开始循环模拟 
		x--;
		x*=2;
		cnt++;
		if(cnt>1e6){//如果次数太多返回 
			cout<<"inf";
			return 0;
		}
	}
	cout<<cnt+1;//愉快的写完了 
	return 0;
}
```

---

## 作者：koobee (赞：0)

考察：数列。

设 $m=\text{log}_2$ $x$。如果 $n \le m$，什么也不用干，输出 $0$。

否则，就可以推一下。`inf` 的情况之后再考虑。我们先手动强化一次，让 $m=2m$。

设 $t_k$ 为强化了 $k+1$ 次后的攻击力（加一是我们手动强化的），设 $a_k$ 为 $\text{log}_2$ $t_k$，$a_0=m$。递推式为：$a_{k+1}=2a_k-2$。两边减 $2$，得 $a_{k+1}-2=2(a_k-2)$，因此 $a_k-2 = 2^k(m-2)$，即 $a_k=2^k(m-2)+2$。最后，我们只需要二分查找最小的满足要求的 $k$ 了。

注意！最后若 $\text{check}(k)=0$，说明答案为 `inf`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
typedef long long ll;
int x, n;
double m;
ll Pow(ll a, ll b){
	ll mul = 1;
	while(b > 0){
		if(b % 2 == 1) mul = mul * a;
		a = a * a;
		b /= 2;
	}
	return mul;
}//快速幂
bool check(int x){
	ll sum = Pow(2, x) * (m-2) + 2;//公式
	if(sum >= n) return 1;
	return 0;
}
int main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>x>>n;
	m = log2(x);
	if(m >= n){
		cout<<0;
		return 0;
	}//特判
	m += m;//手动强化
	int l = 0, r = 64;
	while(l < r){
		int mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}//二分
	if(!check(r)){
		cout<<"inf";//inf
		return 0;
	}
	cout<<r+1;
	return 0;
}
```

---

## 作者：GXZJQ (赞：0)

# P10320 勇气（Courage） 题解

[题目传送门](https://www.luogu.com.cn/problem/P10320)

## 题目大意

给定两个整数 $x,n$ 和一种变换方式，要求求出最少经过多少次变换之后 $x$ 的值不小于 $2^n$。

上面所提到的“变换方式”如果使用函数来进行刻画的话，其表达式为：


$$ f(x_i)=\left\{
\begin{array}{rcl}
x^2,       &      &	& i=1\\
(\frac{f(x_{i-1})}{2})^2, & &&i > 1
\end{array} \right. $$

其中， $f(x_i)$ 代表的是经过第 $i$ 次变换后得到的数值。

## 变换分析

首先，我们先在小范围内进行模拟计算，其初始值为 $x$。为了更加直观的展示每组数据的由来，特地列出了原始的表达式和最后化简的表达式，如下表所示：

| 变换次数 | 原始表达式 | 化简表达式 |
| :----------: | :----------: | :----------: |
| $0$ | $x$ | $x$ |
| $1$ | $\left(\frac{x}{2^0}\right)^2$ | $\frac{x^2}{2^0}$ |
| $2$ | $\left(\frac{x^2}{2}\right)^2$ | $\frac{x^4}{2^2}$|
| $3$ | $\left(\frac{\left(\frac{x^4}{2^2}\right)}{2}\right)^2$ | $\frac{x^8}{2^6}$ |
| $4$ |  $\left(\frac{\left(\frac{x^8}{2^6}\right)}{2}\right)^2$ | $\frac{x^{16}}{2^{14}}$ |

观察上面的格式特征，我们不妨记经过第 $i$ 次变换后得到的结果为 $\frac{x^m}{2^n}$。对 $m,n$ 分别进行分析，如下所示：
| $i$ | $1$ | $2$ | $3$ | $4$ | $5$ | $……$ | $k$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $m$ | $2$ | $4$ | $8$ | $16$ | $32$ | $……$ | $2^k$ |
| $n$ | $0$ | $2$ | $6$ |  $14$| $30$ |$……$  | $2^k-2$ |

通过上表，我们可以得到结果的一个通用表达式。记经过第 $i$ 次变换后的结果为 $x_i$，则有：

$$x_i=\frac{x^{2^i}}{2^{2^i-2}}$$

## 题目分析

截至目前，我们已经得出了对于题目给定的变换方法的通式：

$$x_i=\frac{x^{2^i}}{2^{2^i-2}}$$

由于题目要求的是一个最小的正整数 $k$，使得经过 $k$ 次变换后得到的答案大于 $2^n$，于是就会有下面的不等式：

$$\frac{x^{2^k}}{2^{2^k-2}} \geq 2^n$$

这时，我想到了高中数学中的对数，其中有一条定理：

> 对于一个不等式 $m \geq n$，将其两边同时取以同一数字为底的对数之后，不等号方向不变，即满足 $\log_k{m} \geq \log_k{n}$。

上述结论可以利用对数函数的单调性证明，在这里不过多阐述。所以对于这道题，由代数知识可有如下推导过程，应该是足够详细了：

$$\frac{x^{2^k}}{2^{2^k-2}} \geq 2^n$$

$$x^{2^k} \geq 2^n \times {2^{2^k-2}}$$

$$x^{2^k} \geq 2^{n+2^k-2}$$

$$\log_2{x^{2^k} }\geq \log_2{2^{n+2^k-2}}$$

$$2^k\log_2{x}\geq (n+2^k-2) \times \log_2{2}$$

$$2^k \log_2{x}\geq n+2^k-2$$

$$2^k \log_2{x} - 2^k \geq n - 2$$

$$2^k \geq \frac{n-2}{ \log_2{x} -1}$$

$$k \geq \log_2{\frac{n-2}{ \log_2{x} -1}}$$

看到这里，终于是拨开云雾了。经过我们的推导，发现对于给定的 $x,n$，在一般情况下，程序只要输出一个 
$\lceil \log_2{\frac{n-2}{ \log_2{x} -1}} \rceil$ 即可。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int x, n;
int main() {
	cin >> x >> n;
	if(x == 2 && n == 2){
		cout << 1 << endl;
		return 0;
	}
	if (x == 2 && n > 2) {
		cout << "inf" << endl;
		return 0;
	}
	if (x >= pow(2, n)) {
		cout << 0 << endl;
		return 0;
	}
	if (log2((n - 2) / (log2(x) - 1))< 0) {
		cout << "inf" << endl;
		return 0;
	}
	cout << ceil(log2((n - 2) / (log2(x) - 1))) << endl;
	return 0;
}
```
这道题特判特别多，所以很考验我们对细节的理解，选手们要多加注意。

完结撒花~

---

## 作者：2021zjhs005 (赞：0)

对于无解的情况有两种：

  - $x=1$，但是数据中 $x\ge 2$，可以不用考虑。
  
  - $x=2$，但是 $n\ge 3$，无解，可以手动模拟，发现会循环。

------------

首先去除无解的情况，其次分 $\texttt{Subtask}$ 讨论：

- 对于 $\texttt{Subtask}\ 1$，直接拿 $\texttt{double}$ 模拟即可。

- 对于 $\texttt{Subtask}\ 2$，不难发现 $4=2^2$，因此可以直接模拟，先将其化为 $2^x = 4$，然后直接模拟即可。

$\texttt{Subtask}\ 2$ 的方法给了我们启发，我们能否一开始就将 $x$ 化为 $2^y = x$ 呢？显然是可以的，其中 $y = \log_2(x)$ 或者 $\frac{\log_{10}(x)}{\log_{10}(2)}$，这是底数 $2$ 已经对计算结果不影响，影响的只有 $y$ 和 $n$。

第一次变换为 $x^2$，这时候 $y$ 需要变为 $y \times  2$，因为 $2^y \times 2^y = 2^{2\times y}$。

随后的变换为 $y\to (y-1)\times 2$，因为 $(\frac{2^y}{2})^2 = 2^{(y-1)\times 2}$。

但是这样需要特判第一次，我们可以提前让 $y$ 加 $1$，这样就只用计算一种公式。

这些操作的停止条件很明显，为 $y\ge n$，答案在计算过程中直接统计即可。

虽然时间复杂度高于 $\Theta(\log_2 n)$，但是一定远低于 $\Theta(n)$，不会 T。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rrep(i,x,y) for(int i=x;i>=y;i--)
#define sc scanf
#define pr printf
#define max(a,b) a>b?a:b
#define endline pr("\n")

inline int read() {
	int s = 0, w = 1;
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') w = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		s = (s << 1) + (s << 3) + (c ^ 48);
		c = getchar();
	}
	return s * w;
}

int n,x,sum;

signed main() {
  x=read();n=read();
  if(x==2){//特判 2。
    if(n==1) pr("0\n");//不用操作。
    else if(n==2) pr("1\n");//一次。
    else pr("inf\n");//无解。
    exit(0);
  }
  double y=1.0*log(x)/log(2)+1;//+1 简洁代码。
  while(y<n){
    y=((y - 1) * 2.0);//公式。
    sum++;//累加。
  }
  pr("%lld\n",sum);
}
```

---

