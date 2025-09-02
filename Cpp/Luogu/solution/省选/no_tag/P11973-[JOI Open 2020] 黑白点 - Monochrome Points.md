# [JOI Open 2020] 黑白点 / Monochrome Points

## 题目描述

在一个环上有 $2n$ 个点，按照顺时针顺序编号为 $1,2,\dots 2n$。每个点是黑点或者白点，一共有 $n$ 个黑点和 $n$ 个白点。

我们画 $n$ 条线段连接环上的点，使其满足以下条件：

- 每个点恰好是一条线段的端点。
- 每条线段连接一个黑点和一个白点。

定义**相交数**为相交的线段对数。

给出每个点的颜色，计算 $n$ 条线段最大的相交数。

## 说明/提示

#### 样例解释 1

如果我们按左图绘制线段，那么相交数就是 $2$。另一方面，如果我们按右图绘制线段，那么相交数是 $3$，然而不满足题目描述中的条件。

![](https://cdn.luogu.com.cn/upload/image_hosting/7q5karom.png)

#### 数据规模与约定

#### 本题采用捆绑测试。

- Subtask 1（4 pts）：$n\le 8$；
- Subtask 2（21 pts）：$n\le 300$；
- Subtask 3（10 pts）：$n\le 2000$；
- Subtask 4（65 pts）：无特殊限制。

对于 $100\%$ 的数据，$1\le n\le 2\times 10^5$，保证 $S$ 的长度是 $2n$ 且只包含 $\mathtt{B}$ 和 $\mathtt{W}$ 两种字符。保证 $\mathtt{B}$ 和 $\mathtt{W}$ 都出现恰好 $n$ 次。

译自 [JOI Open 2020](https://contests.ioi-jp.org/open-2020/index.html) T2 「[白黒の点](https://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2020/monochrome/2020-open-monochrome-statement.pdf) / [Monochrome Points](https://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2020/monochrome/2020-open-monochrome-statement-en.pdf)」

## 样例 #1

### 输入

```
3
BBWWBW```

### 输出

```
2```

## 样例 #2

### 输入

```
5
BWBWBBWBWW```

### 输出

```
8```

## 样例 #3

### 输入

```
10
WBBBWBBWWBWWBWWBWBWB```

### 输出

```
41```

## 样例 #4

### 输入

```
16
WWWBWBBBBWWBWWBWWBBWWBBBWBBBWWBW```

### 输出

```
105```

# 题解

## 作者：Purslane (赞：4)

# Solution

如果一个匹配的两个端点位置分别是 $x$ 和 $y$，他们会把整个圆周化为两个部分——假设一个部分为 $w_1$ 个白点和 $b_1$ 个黑点，另一个部分是 $w_2$ 个白点和 $b_2$ 个黑点。

则这条线最多和 $\min\{w_1,b_2\} + \min\{w_2,b_1\} = \min\{w_1+b_1,w_2+b_2\}$ 条线相交（注意到 $w_1+w_2=b_1+b_2=n$）也就是 $\text{dis}(x,y)-1$，其中 $\rm dis$ 是环上两点的距离。

我们先最大化 $\sum \text{dis} (b_i,w_i) -1$。

看看这个图：

![](https://s21.ax1x.com/2025/04/04/pE60b5Q.png)

如果求红色点之间的距离，我们可以将其中一个红色的点对称到其对径点处，即计算下方红点和橙点的距离（用 $n$ 减去他们）。

因此问题变为：环上给了若干个白点和黑点，将其配对，最小化距离（为什么要最小化而不是直接最大化？因为圆上的距离本质上是两种方案取最小值。而如果先取最小值再尝试最大化一些东西，会导致出很多问题。。）

如果是序列上做这件事情，显然每条边会被经过的次数为：其左边的黑点总数与白点总数差的绝对值。所以我们不难猜测，最终的结果是——先匹配某个黑点和白点，然后不断移动他们顺时针方向下第一个黑点和第一个白点。有了这个结构，我们已经可以证明这种算法取到的解就是答案。

显然至少有一条边不会被经过，所以我们考虑选一个位置出来断环成链。

假设把 $1$ 和 $n+n$ 断开，记录 $pre_i$ 为：$\le i$ 的黑点个数减去白点个位数。

那么假设我们实际上在 $(p,p+1)$ 处断开，则新的 $pre'_i=pre_i - pre_p$。

所以我们要最小化 $\sum_{i=1}^{n+n} |pre_i-pre_p|$。

选中位数就好了。复杂度 $O(n \log n)$，如果换成桶排可以做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
const int MAXN=1e6+10;
int n,pre[MAXN];
string S;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>S,S="&"+S;
	ffor(i,1,n+n) if(S[i]=='B') pre[i]++;
	else pre[(i+n-1)%(n+n)+1]--;	
	ffor(i,1,n+n) pre[i]+=pre[i-1];
	sort(pre+1,pre+n+n+1);
	int ans=(n-1)*n;
	ffor(i,1,n+n) ans-=abs(pre[i]-pre[n]);
	cout<<ans/2;
	return 0;
}
```

---

## 作者：masterhuang (赞：3)

> 在一个环上有 $2n$ 个点，按照顺时针顺序编号为 $1,2,\cdots ,2n$。一共有 $n$ 个黑点和 $n$ 个白点。
>
> 我们画 $n$ 条线段连接环上的点，使其满足以下条件：
>
> - 每个点恰好是一条线段的端点。
> - 每条线段连接一个黑点和一个白点。
>
> 定义**相交数**为相交的线段对数。
>
> 给出每个点的颜色，计算 $n$ 条线段最大的相交数。
>
> $n\le 2\times 10^5$

一个匹配的两个端点会把整个圆周化为两个部分。

假设一个部分为 $w_1$ 个白点和 $b_1$ 个黑点，另一个部分是 $w_2$ 个白点和 $b_2$​ 个黑点。

![](https://dl2.img.timecdn.cn/2025/06/24/image.png)

则这条线最多和 $\min(w_1, b_2) + \min(w_2, b_1) = \min(w_1 + b_1, w_2 + b_2)=\text{dis}(x,y) - 1$ 条线相交。

其中 $w_1 + w_2 = b_1 + b_2 = n$，$\text{dis}$​​ 是环上两点的距离。

----

我们先做最大化 $\sum \text{dis}(b_i, w_i) - 1$​​，**下面会证这个上界能达到**。$\color{red}(*)$

考虑**把白点全部对称到环上对称的位置**，然后再计算距离 $\text{dis}(b_i,w_i')$。

则答案为 $\sum(n-1-\text{dis}(b_i,w_i'))$，于是要求 $\min \sum \text{dis}(b_i,w_i')$。

问题转化为：环上 $n$ 白点 $n$ 黑点，可能重合，两点匹配权值为环上最小距离，求最小权完美匹配。$\color{blue}(*)$

---

**为何要对称白点呢**？因为破环成链错误，方案权值更大，所以你要转成 $\min$​ 做。

具体的：

- 考虑首先一个方案一定能破环成链（答案被计算到）。

- 其次对于一个方案，如果你破环成链的时候破了不应该破的边，那么求的距离 $\text{dis}$ 一定更大，不影响答案。

---

于是你只需枚举破的位置，每次求链的答案即可。

然后转化为序列上的问题：$n$ 个白点，$n$ 个黑点在数轴上，求匹配距离最小值。

这东西经典结论：你按顺序排列 $a_1,\cdots,a_n;b_1,\cdots,b_n$，显然 $(a_1,b_1),\cdots,(a_n,b_n)$​ 匹配最小。

但是你要多次断边，就 ${\mathcal {O}}(n^2)$ 了。

这东西有个经典 **trick**：拆贡献到边。就是对每条边算对距离的贡献，而不是直接绝对值。

- 回到蓝色 $\color{blue}(*)$ 部分。

初始直接把黑白点从编号 $1$ 开始拍到序列上，黑点 $x$ 让 $c_x\gets c_x+1$，白点则 $c_x\gets c_x-1$​。

然后对 $c$ 前缀和，此时从 $1$ 开始的答案就是 $\sum\limits_{i=1}^{2n} \vert c_i\vert$。

- 循环左位移 $1$ 次，**前缀和数组**变成：$[c_2-c_1,\cdots,c_n-c_1,0]$。

- 循环左位移 $2$ 次，**前缀和数组**变成：$[c_3-c_2,\cdots,c_n-c_2,c_1-c_2,0]$​。
- 以此类推，循环位移 $k$ 次后，**答案**变成：$\sum\limits_{i=1}^{2n} \vert c_i-c_k\vert$。

这东西最小值是啥？显然取中位数，做完啦！

于是求解复杂度 ${\mathcal {O}}(n\log n)$，瓶颈在于排序。

---

考虑 $\color{red}(*)$ 部分为啥能取到呢？

考虑破环成链之后的匹配是长啥样的。如下图：

![](https://dl3.img.timecdn.cn/2025/06/24/image.png)

环上把白点，黑点依次拎出来，写成两个序列：$w_1,w_2,\cdots,w_n;b_1,b_2,\cdots,b_n$。

你每次匹配就初始匹配一组 $(w_x,w_y)$，然后 $(w_{x\bmod n+1},b_{y\bmod n+1}),\cdots,(w_{(x-1)\bmod n},w_{(y-1)\bmod n})$。

简单来说：把 $b$ 循环位移，然后和 $w$​ 依次匹配。

---

观察到这个证明就是简单的。

![](https://dl.img.timecdn.cn/2025/06/24/image.png)

考虑一组匹配（黑边），然后你从白点，黑点对循环位移过去，该跨过的相交的线段一定取到相交了（红色）。

特别的空的那些点本来就没有贡献，那么 $\min(w_1,b_2)+\min(b_1,w_2)$ 就显然能取到了。

虽然证明很冗长，但是代码其实很简单。

```cpp
//洛谷 P11973
//https://www.luogu.com.cn/problem/P11973
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=4e5+5;
int n,m,a[N];LL s;string S;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n>>S;
	S='@'+S;m=2*n;
	for(int i=1;i<=m;i++)
	{
		if(S[i]=='B') a[i]++;
		else a[(i+n-1)%m+1]--;
	}partial_sum(a+1,a+1+m,a+1);
	sort(a+1,a+1+m);s=(LL)n*(n-1);
	for(int i=1;i<=m;i++) s-=abs(a[i]-a[n]);
	return cout<<s/2,0;
}
```

---

