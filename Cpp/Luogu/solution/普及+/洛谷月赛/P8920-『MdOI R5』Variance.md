# 『MdOI R5』Variance

## 题目背景

Subtask 1~5 为原数据，Subtask 6 为 hack 数据。

## 题目描述

给定两个长度为 $n$ 的整数序列 $a,b$，满足：
- $\forall i\in [1,n),a_i\le a_{i+1},b_i\le b_{i+1}$。

- $\forall i\in [1,n],a_i\le b_i$。

有一个长度为 $n$ 的实数序列 $c$，满足 $c_i\in [a_i,b_i]$，求 $c$ 的方差的最大值。

你只需要输出答案乘上 $n^2$ 之后的结果。容易证明这是一个整数。

### 提示

一个长度为 $n$ 的序列 $a$ 的方差为：$\dfrac{1}{n}\sum\limits_{i=1}^n (a_i-\overline{a})^2$。其中 $\overline{a}=\dfrac{1}{n}\sum\limits_{i=1}^n a_i$。

本题的计算过程中可能会涉及到超过 `long long` 范围的数，此时可能需要用到 `__int128` 进行处理。

我们提供了以下代码，它可以用于输出一个 `__int128` 类型的数：

``` cpp
void print(__int128 x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x<10)
	{
		putchar(x+48);
		return;
	}
	print(x/10);
	putchar(x%10+48);
}
```

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^6$，$1\le a_i,b_i\le 10^9$。

$\operatorname{Subtask} 1(10\%)$：$n\le 2\times 10^3$，$a_i=b_i\le 10^5$。

$\operatorname{Subtask} 2(20\%)$：$n\le 10$，$a_i,b_i\le 5$。

$\operatorname{Subtask} 3(20\%)$：$n\le 2\times 10^3$，$a_i,b_i\le 10^5$。

$\operatorname{Subtask} 4(20\%)$：$n\le 10^5$，$a_i,b_i\le 2\times 10^3$。

$\operatorname{Subtask} 5(30\%)$：无特殊限制。

#### 样例说明 1

$c$ 只可能为 $(1,10)$。

#### 样例说明 2

一种最优的 $c$ 为 $(1,2,5)$。

## 样例 #1

### 输入

```
2
1 10
1 10```

### 输出

```
81```

## 样例 #2

### 输入

```
3
1 2 3
3 4 5```

### 输出

```
26```

# 题解

## 作者：Kubic (赞：11)

结论 $1$：一定存在一种最优方案，满足 $c$ 单调不降。

证明：反证，如果存在 $i<j$ 满足 $c_i>c_j$，我们可以交换 $c_i,c_j$，显然满足条件且方差不变。

结论 $2$：一定存在一种最优方案，满足存在一个 $i$，使得 $c_{1\dots i-1}=a_{1\dots i-1},c_{i+1\dots n}=b_{i+1\dots n}$。

证明：反证，如果存在 $i<j$ 满足 $c_i>a_i$ 且 $c_j<b_j$，那么可以 $c_i\leftarrow c_i-1,c_j\leftarrow c_j+1$，显然方差增大。

结论 $3$：一定存在一种最优方案，满足存在一个 $i$，使得 $c_{1\dots i}=a_{1\dots i},c_{i+1\dots n}=b_{i+1\dots n}$。

根据结论 $2$，我们得到了一个位置 $j$，此时 $c$ 中除了 $c_{j}$ 都已经确定下来了，此时方差是一个关于 $c_j$ 的二次函数。可以发现这个二次函数是下凸的，因此取到最大值时一定有 $c_j=a_j$ 或 $c_j=b_j$。所以 $i=j$ 或 $i=j-1$。

有了结论 $3$，我们只需要枚举其中的 $i$ 即可得到答案。时间复杂度 $O(n)$。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000005
#define lll __int128
int n,a[N],b[N];lll s1,s2,ans;
void print(lll x)
{
	if(x<10) {putchar(x+48);return;}
	print(x/10);putchar(x%10+48);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) scanf("%d",&b[i]);
	for(int i=1;i<=n;++i) s1+=a[i],s2+=1ll*a[i]*a[i];
	ans=s2*n-s1*s1;
	for(int i=n;i;--i)
	{
		s1+=b[i]-a[i];s2+=1ll*b[i]*b[i]-1ll*a[i]*a[i];
		ans=max(ans,s2*n-s1*s1);
	}print(ans);return 0;
}
```

---

## 作者：David_Mercury (赞：10)

## 题目大意

[传送门](https://www.luogu.com.cn/problem/P8920)


------------

## 分析

其实这差不多是一道数学题。

我们先来看一下什么是方差。网上给的定义是：

> 方差是在概率论和统计方差衡量随机变量或一组数据时离散程度的度量。其计算方法为，序列中数与它们平均数之差的平方的平均值。
>
> 公式表示为：
>
> $$S^2 = \dfrac{(x_1-\overline{x})^2 + (x_2-\overline{x})^2 + \dots + (x_n-\overline{x})^2}{n}$$
>
> 其中，$\overline{x}$ 为：
>
> $$\overline{x} = \dfrac{x_1+x_2+\dots+x_n}{n}$$

根据定义，我们可知要**尽量让数据分散**。即，小的尽量小，大的尽量大。

再来看看题目所给的条件

> - $\forall i\in [1,n),a_i\le a_{i+1},b_i\le b_{i+1}$。
>
> - $\forall i\in [1,n],a_i\le b_i$。

很容易可以想到，**前半段我们应当全选 $a$ 数组，后半段则应全选 $b$ 数组**，这样数据离散程度最大。图像大概是这样的：

![ddddd](https://cdn.luogu.com.cn/upload/image_hosting/mfsebcn9.png)

问题便成为了：找一个位置 $i$，使得 $a_1 \sim a_2, b_{i+1} \sim b_n$ 两段组成的序列，方差最大。这样，对于每一个 $i$，我们逐个进行枚举就行了。但是，为了将每一次计算方差的时间复杂度降到 $O(1)$，我们还要先对方差公式进行一下变形。

$$S^2 = \dfrac{(x_1-\overline{x})^2 + (x_2-\overline{x})^2 + \dots + (x_n-\overline{x})^2}{n}$$

$$S^2 = \dfrac{({x_1}^2+{x_2}^2+\dots+{x_n}^2) - 2*\overline{x}*(x_1+x_2+\dots+x_n) + n*\overline{x}^2}{n}$$

$$S^2 = \dfrac{({x_1}^2+{x_2}^2+\dots+{x_n}^2) - 2*\dfrac{(x_1+x_2+\dots+x_n)^2}{n} + n*\dfrac{(x_1+x_2+\dots+x_n)^2}{n^2}}{n}$$

题目要求的是 $S^2*n^2$，因此可以继续化简：

$$S^2*n^2 = n*({x_1}^2+{x_2}^2+\dots+{x_n}^2) - 2*(x_1+x_2+\dots+x_n)^2 + (x_1+x_2+\dots+x_n)^2$$

$$S^2*n^2 = n*({x_1}^2+{x_2}^2+\dots+{x_n}^2) - (x_1+x_2+\dots+x_n)^2$$

这也顺带证明了为什么 $S^2*n^2$ 一定为整数。

现在，我们手里只要有**数列的平方和**以及**数列的和的平方**就可以求出答案了。


------------

## 实现

我们预处理四个数组：$a$ 的前缀和、$a$ 平方的前缀和、$b$ 的后缀和（本人杜撰的一个名词，就是从后往前的前缀和）以及 $b$ 平方的后缀和。对于每个 $i$，我们将位置 $i$ 的前缀以及位置 $i+1$ 的后缀相加便是这个数列的总和，再带进刚才推导的公式计算就可以了。

#### Coding：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+5;
__int128 ans, qz[MAXN], hz[MAXN], qz2[MAXN], hz2[MAXN];
int n, a[MAXN], b[MAXN];

void print(__int128 x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x < 10){
		putchar(x+48);
		return;
	}
	print(x/10);
	putchar(x%10+48);
}

int main(){
	scanf("%d", &n);
	for(int i=1; i<=n; i++)	scanf("%d", a+i);
	for(int i=1; i<=n; i++)	scanf("%d", b+i);
	for(int i=1; i<=n; i++)	qz[i] = qz[i-1]+a[i];		//前缀和
	for(int i=n; i>=1; i--)	hz[i] = hz[i+1]+b[i];		//后缀和
	for(int i=1; i<=n; i++){							//平方的前缀和
		qz2[i] = a[i];
		qz2[i] = qz2[i]*qz2[i]+qz2[i-1];
	}
	for(int i=n; i>=1; i--){							//平方的后缀和
		hz2[i] = b[i];
		hz2[i] = hz2[i]*hz2[i]+hz2[i+1];
	}
	for(int i=0; i<=n; i++)
		ans = max(ans, (qz2[i]+hz2[i+1])*n-(qz[i]+hz[i+1])*(qz[i]+hz[i+1]));
	print(ans);
	
	return 0;
}
```


------------

## 后记

才开始写题解，请多多包涵。

最后的最后，感谢您的观看！

:)

---

## 作者：strcmp (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P8920)

**前言**

在赛时，本人通过~~根据样例猜测结论~~的方法，耗时 1h 通过了本题，但是对于本题的很多结论都没有证明，所以写了这篇题解填了这道题的坑。

如果想知道为什么最后答案必然是整数，这里给了一个[数学归纳法的证明](https://www.luogu.com.cn/paste/t1krqea0)。

**题目大意：** 给定两个长度为 $n$ 的序列 $a,\,b$，满足 $a_i \le a_{i + 1},\,b_i \le b_{i + 1},\,a_i \le b_i$。要求给出序列 $c$ 满足 $c_i \in [a_i,\,b_i]$ 且对于所有可能的序列 $c$ 中方差最大，求其方差。

### Solution

首先根据 NOIP2021T3 的经验，将答案化一下，设 $\mathcal S = \sum^{n}_{i=1}c_i$。方便进行之后的推导。

$$
\begin{aligned}

& n \cdot \sum^{n}_{i=1}\left(c_i-\frac1n \mathcal S\right)^2 \\
& =n \cdot \left(\sum^{n}_{i=1}\left(c^2_i + \frac{1}{n^2} \mathcal S^2 - \frac2nc_i\mathcal S\right)\right)\\
& =n \cdot \sum^{n}_{i=1}c_i^2 + \mathcal S^2 - 2 \mathcal S^2\\
& = n \cdot \sum^{n}_{i=1}c_i^2 - \left(\sum^{n}_{i=1}c_i\right)^2
\end{aligned}
$$

方便起见，设 $\mathcal A \leftarrow \sum^{n}_{i=1}c^2_i,\, \mathcal B \leftarrow \left(\sum^{n}_{i=1}c_i\right)^2$。

**引理 $1$：** 最优的序列 $c$ 中存在单调不减的序列，即存在最优序列，满足 $\forall c_i \in c,\, c_{i - 1} \le c_i$，默认 $c_0$ 为 $-\infty$。

证明：设存在 $i,\,j$ 满足 $c_i > c_j \wedge i < j$，显然根据题目条件 $a_i \le c_i \le b_i,\,a_j \le c_j \le b_j,\,a_i \le a_j,\,b_i \le b_j$。

则交换 $c_i$ 和 $c_j$，对于 $c_j$ 显然 $a_i \le a_j \le c_j$，$c_j \le c_i \le b_i$，所以 $a_i \le c_j \le b_i$。对于 $c_i$ 显然 $a_j \le c_j \le c_i$，$c_i \le b_i \le b_j$，所以 $a_j \le c_i \le b_j$。都满足要求，且显然方差不变，所以可以通过交换使得 $c$ 不存在逆序对，即存在 $c$ 单调不减，引理得证。

**引理 $2$：** 最优的序列 $c$ 中至少有 $n - 1$ 个元素，满足 $c_i = a_i \vee c_i = b_i$。

证明：假设存在 $i < j \wedge c_i \le c_j$，且 $c_i \ne a_i,\,c_j \ne b_j$。则可以使得 $c_i \leftarrow c_i - 1,\,c_j \leftarrow c_j + 1$，显然满足要求。此时 $c_i$ 对 $\mathcal A$ 的贡献降低 $c_i^2 - (c_i - 1)^2 = 2c_i-1$，$c_j$ 对 $\mathcal A$ 的贡献上升 $(c_j + 1)^2 - c_j^2 = 2c_j + 1$。由于 $c_i \le c_j$ 所以 $2c_i-1 < 2c_j + 1$，所以操作后对 $\mathcal A$ 的增量大于减量，所以 $\mathcal A$ 增加。而操作后加减一互相抵消，$\mathcal B$ 不变。所以 $\mathcal {A-B}$ 增加，即答案增加。对 $c$ 中 $\lfloor \frac{n}{2} \rfloor$ 对元素不断进行操作后，必然至少有 $n-1$ 个元素，满足 $c_i = a_i \vee c_i = b_i$，引理得证。

**引理 $3$：** 必然存在一个最优序列 $c$，满足存在 $k$，使得 $c_{1\dots k - 1} = a_{1\dots k - 1}$ 且 $c_{k + 1 \dots n} = b_{k + 1 \dots n}$。

证明：因为要满足引理 $2$，就必须满足当 $i < j$ 时有 $c_i \le c_j$，而由引理 $1$，当且仅当 $c$ 单调不减时满足要求，也就是当且仅当存在断点 $k$ 满足 $c_{1\dots k - 1} = a_{1\dots k - 1}$ 且 $c_{k + 1 \dots n} = b_{k + 1 \dots n}$ 时符合邀请。引理易证。

**引理 $4$：** 必然存在一个最优序列 $c$，满足存在 $k$，**使得 $c_{1\dots k} = a_{1\dots k}$ 且 $c_{k + 1 \dots n} = b_{k + 1 \dots n}$。**

证明：根据引理 $3$，我们只剩下了一个 $c_k$，其余的元素已经确定，只需要考虑 $c_k$ 对答案取值的影响。

加入 $c_k$ 之后，对于 $\mathcal A$ 的增量为 $n \cdot c_k^2$，对于 $\mathcal B$ 的增量为 $c_k \cdot \sum^{n}_{i=1}c_i$，可以化为 $(n - 1)c_k$ 与一个跟 $c_k$ 有关的一次函数的差，是一个上凹的二次函数，取到极值点必然是 $a_k$ 或者 $b_k$。所以 $c_k = a_k$ 或者 $c_k = b_k$，引理得证。（想要详细证明的可以回去看那个用数学归纳法的证明）

枚举断点 $k$，可以通过预处理前缀和后缀和的方式得到 $\Theta(n)$ 的算法。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define re register
typedef __int128 ll;
const int maxn = 1e6 + 10;
__int128 a[maxn], b[maxn], s1, s2, ans = 0; int n;
inline void read(ll &x){
	x=0;char e=0;
	while (!isdigit(e))e=getchar();  
	while (isdigit(e)) x=x*10+(e^48),e=getchar();  
}
void print(__int128 x){
	if(x < 10){
		putchar(x + 48);
		return;
	}
	print(x / 10);
	putchar(x % 10 + 48);
}
int main() { scanf("%d", &n);
    for (re int i = 1; i <= n; i++)read(a[i]);
    for (re int i = 1; i <= n; i++)read(b[i]);
    for (re int i = 1; i <= n; i++)s1 += a[i], s2 += a[i] * a[i];
    ans = s2 * n - s1 * s1;
    for (re int i = n; i >= 1; i--){
        s1 += b[i] - a[i], s2 += b[i] * b[i] - a[i] * a[i];
        ans = max(ans, s2 * n - s1 * s1);
    }
    print(ans);
    return 0;
}
```
实际上这道题应该还存在三分的 $\Theta(n \log n)$ 的做法，但是还需要证明一个更强的结论，而且常数不优，并且正确性没有太大的保证，个人不建议这种做法。（~~虽然赛时我写的就是这个做法~~）

---

## 作者：reclusive (赞：2)

[my blog](https://www.cnblogs.com/reclusive2007/p/17704967.html)

## 题目描述

给你两个长度为 $n$ 的序列 $a$ 和 $b$，让你选 $n$ 个 $c_i \in [a_i,b_i]$，使得 $\frac{1}{n} \sum_{i=1}^n (c_i- \overline c)^2$ 最大。

## 具体思路

首先我们从方差的定义出发，方差代表了数据的波动程度，公式为：$$s^2=\frac{1}{n} \sum_{i=1}^n (a_i- \overline a)^2$$

其中， $\overline a =\frac{1}{n} \sum_{i=1}^n a_i$，$s$ 为方差。

那么我们要让波动程度最大，那就直接选区间的两个端点，但是我们肯定不能直接去枚举选每个区间选左端点还是右端点。

通过思考发现，前一部分我们选左端点，后面部分选右端点，可以导致波动程度最大。但是我们不知道断点应该设在哪里，所以通过枚举断点即可。

那我们显然不可能每次都求一次和，于是考虑化式子然后前缀和解决。

$$s^2=\frac{1}{n}(\sum_{i=1}^n a_i^2+n \times (\frac{\sum_{i=1}^n a_i}{n})^2-2 \times \frac{\sum_{i=1}^n a_i}{n} \times \sum_{i=1}^n a_i)$$

$$s^2=\frac{1}{n}(\sum_{i=1}^n a_i^2+\frac{(\sum_{i=1}^n a_i)^2}{n}-2 \times \frac{(\sum_{i=1}^n a_i)^2}{n})$$

$$s^2=\frac{1}{n}(\sum_{i=1}^n a_i^2-\frac{(\sum_{i=1}^n a_i)^2}{n})$$

$$s^2 \times n^2=n \times (\sum_{i=1}^n a_i^2-\frac{(\sum_{i=1}^n a_i)^2}{n})$$

$$s^2 \times n^2=n \times \sum_{i=1}^n a_i^2-(\sum_{i=1}^n a_i)^2$$

由于我们求的是 $a$ 的前一段和 $b$ 的后一段的信息和，因此需要预处理 $a$ 的前缀和，$b$ 的后缀和，$a$ 的前缀平方和，$b$ 的后缀平方和。

## Code

```
#include<bits/stdc++.h>
using namespace std;
typedef __int128 LL;
inline void write(LL x){
	static int sta[35];int top=0;
	do{sta[++top]=x%10;x/=10;}while(x);
	while(top)putchar(sta[top--]+'0');
}
const int N=1e6+5;
int a[N],b[N];
LL sa1[N],sa2[N],sb1[N],sb2[N];
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	for(int i=1;i<=n;i++){
		sa1[i]=sa1[i-1]+a[i];
		sa2[i]=sa2[i-1]+(LL)a[i]*a[i];
	}
	for(int i=n;i>=1;i--){
		sb1[i]=sb1[i+1]+b[i];
		sb2[i]=sb2[i+1]+(LL)b[i]*b[i];
	}
	LL ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,n*(sa2[i]+sb2[i+1])-(sa1[i]+sb1[i+1])*(sa1[i]+sb1[i+1]));
	}
	write(ans);
	return 0;
}
```

---

## 作者：an_ancient_ghoul (赞：1)

# My Solution for P8920『MdOI R5』Variance
赞美欧姆弥赛亚！

## 题目描述

给定两个长度为 $n$ 的整数序列 $a,b$，满足：
- $\forall i\in [1,n),a_i\le a_{i+1},b_i\le b_{i+1}$。

- $\forall i\in [1,n],a_i\le b_i$。 

令 $c$ 为我们选取的结果，

求：$\dfrac{1}{n}\sum\limits_{i=1}^n (c_i-\overline{c})^2$ 的最大值，并将其 $\times n^2$ 后输出。其中 $\overline{c}=\dfrac{1}{n}\sum\limits_{i=1}^n c_i$。

## Start！
我们首先对 $\dfrac{1}{n}\sum\limits_{i=1}^n (c_i-\overline{c})^2$ 下手，可知：   
$$\dfrac{1}{n}\sum\limits_{i=1}^n (c_i-\overline{c})^2 \times n^2$$  
$$=\sum\limits_{i=1}^n (c_i-\overline{c})^2 \times n$$    
$$=\sum\limits_{i=1}^n (c_i^2-2c_i\overline{c}+\overline{c}^2) \times n$$  
$$=n \times \sum\limits_{i=1}^n c_i^2 
-\sum\limits_{i=1}^n2c_i\overline{c}\times n
+n\times \sum\limits_{i=1}^n\overline{c}^2 $$
其中 $\overline{c}\times n = \sum c,\sum\limits_{i=1}^nc_i=\sum c$，则上式
$$=n \times \sum\limits_{i=1}^n c_i^2 
-2 \times (\sum c)^2 + (\sum c)^2 $$
$$=n \times \sum\limits_{i=1}^n c_i^2 -(\sum c)^2 $$ 
接下来，因为 $c$ 所满足的两项性质，我们可以知道 $c$ 的前半段一定全来自 $a$，后半段一定全来自 $b$ （这样一定更离散，即方差更大）。
所以我们做前缀和枚举分割点即可。
## Code
```cpp
//waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaagh!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include<bits/stdc++.h>
#define maxn 1001000
#define llg unsigned long long 
#define reg register
using namespace std;
llg n,m,k,t1,t2,y;
__int128 sum1[maxn],sum2[maxn],a[maxn],b[maxn],av1[maxn],av2[maxn],ans,tmp;
inline __int128 mx(__int128 a,__int128 b)
{
	if(a>b)return a;
	return b;
}
void print(__int128 x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x<10)
	{
		putchar(x+48);
		return;
	}
	print(x/10);
	putchar(x%10+48);
}
int main()
{
	cin>>n;
	for(reg int i=1;i<=n;i++)
	{
		cin>>y;
		a[i]=y;
	}
	for(reg int i=1;i<=n;i++)
	{
		cin>>y;
		b[i]=y;
	}	
	for(reg int i=1;i<=n;i++)
	{
		av1[i]=av1[i-1]+a[i];
		av2[i]=av2[i-1]+b[i];
		sum1[i]=sum1[i-1]+a[i]*a[i];
		sum2[i]=sum2[i-1]+b[i]*b[i];
	}
	for(reg int i=0;i<=n;i++)
	{
		tmp=n*(sum1[i]+sum2[n]-sum2[i])-(av1[i]+av2[n]-av2[i])*(av1[i]+av2[n]-av2[i]);
		ans=mx(ans,tmp);
	}
	print(ans);
	return 0;
}
``` 

---

## 作者：RNTBW (赞：0)

### 序
无序。

看到我的引理证明，被打回来也是正常的。
## 题意
给出两个长度为 $n$ 的序列 $a,b$，求在满足 $c_i \in [a_i,b_i]$ 的所有序列 $c$ 中方差的最大值。

- $1\leqslant n \leqslant 10^6$。

- 对于 $i\in[1,n-1]$，$a_i \le a_{i+1},b_i \le b_{i+1}$。

- 对于 $i\in[1,n]$，$a_i \le b_i$。
## 思路
首先我们来考虑如何取 $c_i$。

显然，方差尽可能大，意味着序列间各个数大小的差距
要尽可能大。

那么：

1. 最优的序列 $c$ 中一定有一种单调不降的序列。

证明：反证，如果在最优序列中存在两个位置 $i,j$，满足 $i<j,c_i>c_j$，那么将 $c_i$ 与 $c_j$ 交换，不会影响方差。

2. $c_i=a_i$ 或 $b_i$，不会等于它们中间的数。

显然，要使差距最大，$c_i$ 只能在边界中选。


~~太弱了不会给出完整的证明....~~

那么有了 1 和 2，再看到这两个条件：

- 条件 1：$a,b$ 单调不降。

- 条件 2：对于 $i\in[1,n]$，$a_i\le b_i$。

同时又要满足方差最大，那么就推出了 3：

3. 一定存在一个数 $i$ 满足 $c_{1..i}=a_{1..i}$，$c_{i+1..n}=b_{i+1..n}$。

证明：反证，假设存在一对数 $i,j$，满足 $i<j,c_i=b_i,c_j=a_j$，那么由于上述条件 2 的存在，所以令 $c_i=a_i$，$c_j=b_j$ 可使方差更大。

对于更加详细的证明，楼下的各位大佬已经讲清楚了，各位可以参考一下，毕竟本人的水平实在有限。

那么既然如此，我们就可以先默认 $c=b$，枚举每个断点 $i$，每次将 $c_i$ 更新为 $a_i$，求出此时的方差再取最大值，这一步的复杂度为 $O(n)$。

如何 $O(1)$ 求出任意序列 $a$ 的方差呢？

先来看一下这个柿子：$\dfrac{1}{n}\sum\limits_{i=1}^n (a_i-\overline{a})^2$，其中 $\overline{a}=\dfrac{1}{n}\sum\limits_{i=1}^n a_i$。

我们不妨设 $k=\sum\limits_{i=1}^n a_i$，$s=\sum\limits_{i=1}^n a_i^2$，那么在乘上了 $n^2$ 的条件下，此时的方差 $ans={n}\sum\limits_{i=1}^n (a_i-\dfrac{k}{n})^2$。

考虑化简这个柿子：

${n}\sum\limits_{i=1}^n (a_i-\dfrac{k}{n})^2$

$=n[(a_1-\dfrac{k}{n})^2+(a_2-\dfrac{k}{n})^2+....]$

$=n[(a_1^2-2\dfrac{a_1k}{n}+\dfrac{k^2}{n^2})+(a_2^2-2\dfrac{a_2k}{n}+\dfrac{k^2}{n^2})+....]$

$=n[s-2\dfrac{k}{n}(a_1+a_2+....)+\dfrac{k^2}{n}]$

（毕竟 $a_1^2+a_2^2+....=s$ 嘛）

$=ns-2k^2+k^2$

（毕竟 $a_1+a_2+....=k$ 嘛）

$=ns-k^2$。

接下来，我们就可以初始化 $\forall i \in [1,n],c_i=b_i$，计算出此时的 $k,s,ans$。

对于断点 $i$，此时的 $k,s$ 可以由上一次的 $k,s$ 转移而来。

这样，我们就可以实现 $O(n)$ 啦！

## 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll __int128
ll a[1000005],b[1000005];
ll n,i,j,k,s,ans;
/*
k:c1+c2+....cn
s:c1^2+c2^2+....cn^2
*/
inline ll read()
{
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
	{
        if(c=='-')f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9') x=x*(ll)10+c-'0',c=getchar();
    return x*f;
}
inline void write(ll x)
{
	if(!x)return;
	write(x/10);
	putchar(x%10+'0');
}
int main()
{
	n=read();
	for(i=1;i<=n;i++) a[i]=read();
	for(i=1;i<=n;i++) b[i]=read();
	for(i=1;i<=n;i++) k+=b[i],s+=b[i]*b[i];
	ans=s*n-k*k;//初始时默认c=b
	for(i=1;i<=n;i++)
	{
		k-=b[i];k+=a[i];//计算出现在的k
		s-=b[i]*b[i];s+=a[i]*a[i];//计算出现在的s
		ans=max(ans,s*n-k*k);//套用上面的柿子，k,s的定义参见代码顶部
	}
	write(ans);
	return 0;
}
```
呼....打这么多 $\LaTeX$ 好累....

---

## 作者：JackMerryYoung (赞：0)

# 前言

感觉有中位绿。

分档：

- 30pts 3 级 暴力

- 100pts 5 级 找性质

可恶怎么是 JV 出的...

# 正文

有送分的爆搜诶 20pts. 然后 Subtask 1 也是送的，于是可拿 30pts.

不甘于这么点分，考虑正解。题目问了什么呢：给你 $N$ 个闭区间，然后让你选 $N$ 个数，使其方差最大。

然后这 $N$ 个闭区间有些性质，就是前一个左端点比这个左端点左，前一个右端点比这个右端点左，考虑运用这些性质。

一句废话：一定有解，全删光即可。

结论一：一定有个最优解单调不降，因为如果有个最优解不满足的话，交换逆序对的值仍可以使得该解合法且方差不变，成为一个新的满足单调不降的最优解。

结论二：一定有个最优解有个 $i$，使得 $c_{1 \to i - 1}$ 为 $a_{1 \to i - 1}$，$c_{i + 1 \to N}$ 为 $b_{i + 1 \to N}$。为啥嘞？

反证法，先证右边。我们考虑这个结论的假想敌 $j$，认为有这么一个 $j$ 使得：

$$i < j, c_i > a_i, c_j < b_j$$

如果是这样的话，我方差并没有到最大，因为这组数据的波动程度显然可以更大，令 $c_i$ 变小，$c_j$ 变大即可。左半部分亦然。

这样子 $c$ 画出来就是个单调不降的家伙。注意上述结论没有考虑恰好是 $i$ 时选谁方差大。

继续刚才的思路，我们发现根据此时只有 $c_j$ 不确定，其他家伙都为常数。这个时候方差为关于 $c_j$ 的二次函数！

根据第一个结论发现 $c_j$ 的两个边界为 $a_j, b_j$，然后又易得这个二次函数开口向上，所以最大在边界取得。那么其实 $j$ 就为 $i$ 或者 $i + 1$。

于是乎就可以枚举 $i$ 了，复杂度约为 $\mathcal{O}(N)$。

~~喂喂喂不会有人连前缀和都不会吧...~~

# 后言

还是有点意思的。

---

