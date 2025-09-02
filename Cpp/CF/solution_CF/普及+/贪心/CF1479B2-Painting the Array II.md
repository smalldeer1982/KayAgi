# Painting the Array II

## 题目描述

### 题意

  **本题与 CF1480D1 的唯一区别是本题询问最小可能解.**

  给定一个数组 $a$, 你将将 $a_i$ 染为 $b_i$ 色, 其中 $b$ 是由你指定的一个 **01 数组**. 将 $a$ 数组中被染成 0 色的数字取出来并依在 $a$ 中出现的顺序排列, 组成数组 $a^{(0)}$. 同理, 将 $a$ 数组中被染成 1 色的数字取出来并依在 $a$ 中出现的顺序排列, 组成数组 $a^{(1)}$. 我们定义 $seg(c)$ 是一个正整数, 其中 $c$ 是一个数组, $seg(c)$ 的值为在我们将 $c$ 中相邻的所有相同元素合并后, $c$ 数组的大小. 例如, $seg([1, 1, 4, 5, 1, 4]) = |[1, 4, 5, 1, 4]|=5$. 最小化 $seg(a^{(0)})+seg(a^{(1)})$.

## 样例 #1

### 输入

```
6
1 2 3 1 2 2```

### 输出

```
4```

## 样例 #2

### 输入

```
7
1 2 1 2 1 2 1```

### 输出

```
2```

# 题解

## 作者：wsyhb (赞：9)

## 题意简述

定义连续段 $seg(c)$：将序列 $c$ 中的相邻的相同元素合并后的长度。

给定长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$，要求将其分成两个不相交的子序列 $a^{(0)}$ 和 $a^{(1)}$，使得 $seg(a^{(0)})+seg(a^{(1)})$ **最小**，求这个**最小值**。（也可理解为给第 $i$ 个元素涂上颜色 $b_i$，其中 $b_i=0$ 或 $b_i=1$，然后将颜色为 $0$ 和颜色为 $1$ 的元素分别从左到右取出）

**数据范围**：$n \le 10^5$，$1 \le a_i \le n$

## 思路一

### 分析 + 题解

题目可以看作有两个队列 $s$ 和 $t$，从左到右依次选择每个元素是加入 $s$ 队尾，还是加入 $t$ 队尾，使得最后 $seg(s)+seg(t)$ 最大。

设当前 $s$ 队尾元素为 $x$，$t$ 队尾元素为 $y$，要加入的元素为 $z$（为了方便，一开始 $x=y=0$），我们给出下列**贪心**策略：

1. 若 $z$ 与 $x,y$ 中的至少一个相等，我们将 $z$ 加入当前队尾等于 $z$ 的队列。（若 $z=x=y$，可任意选择）

2. 若 $z$ 不与 $x,y$ 中的任意一个相等，我们将 $z$ 加入 $s$ 当且仅当 $next(x)>next(y)$。其中 $next(x)$ 表示 $x$ 这种值下一次出现的位置，若之后没有出现 $next(x)=n+1$。

由于该**贪心**策略与[我写的B1的题解](https://www.luogu.com.cn/blog/wsyhb/post-ti-xie-cf1479b1-painting-the-array-i)几乎一模一样，故不对该策略的正确性进行说明——想了解的请去看那篇题解。

### 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+5;
int a[max_n],id[max_n],Next[max_n];
typedef pair<int,int> P;//前一个是元素的值，后一个是元素的编号
vector<P> w,b;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",a+i);
		id[i]=n+1;//注意初始化
	}
	for(int i=n;i>=1;--i)
	{
		Next[i]=id[a[i]];
		id[a[i]]=i;
	}
	w.push_back(P(0,n+1));
	b.push_back(P(0,n+1));
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		if(a[i]==w.back().first)
			w.push_back(P(a[i],Next[i]));
		else if(a[i]==b.back().first)
			b.push_back(P(a[i],Next[i]));
		else
		{
			++ans;
			if(w.back().second>b.back().second)
				w.push_back(P(a[i],Next[i]));
			else
				b.push_back(P(a[i],Next[i]));
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

## 思路二

### 分析 + 题解

为了方便，我们将 $a$ 按照连续段的定义合并，这显然对答案没有影响——即**我们约定 $a$ 中任意相邻元素不相同**。

定义 $f(i)$ 表示当前已加入前 $i$ 个元素，且 $b_i \neq b_{i-1}$，$seg(a^{(0)})+seg(a^{(1)})$ 的最小值。（不知道 $b_i$ 的定义？请回“题意简述”去看一看）

稍加思考可得方程：

$$f(i)=
\begin{cases}
1&(i=1)\\
\min_{j=1}^{i-1}\{f(j)+(i-j-1)+[a_{j-1} \neq a_i]\}&(i>1)
\end{cases}
$$

**说明**：$i=1$ 时显然；$i>1$ 时有 $b_{j-1} \neq b_j = b_{j+1} = \cdots = b_{i-1} \neq b_i$，由于 $a_{j+1}$ 到 $a_{i-1}$ 排在 $a_j$ 的后面，对答案的贡献为 $(i-1)-j$；又因为 $a_i$ 排在 $a_{j-1}$ 的后面，对答案的贡献为 $[a_{j-1} \neq a_i]$。

但这样 **DP** 是 $O(n^2)$ 的，如何优化呢？

由于 $[a_{j-1} \neq a_i]$ 只有 $0/1$ 两种取值，而 $i-1$ 是定值，我们考虑如何选取最优的 $j$ 使得 $f(j)-j$ 尽量小：

$$
\begin{aligned}
f(i)-i &\le (f(j)+(i-j-1)+[a_{j-1} \neq a_i])-i\\
&\le f(j)+(i-j)-i\\
&=f(j)-j
\end{aligned}
$$

因此，对于任意的 $x>y$ 有 $f(x)-x \le f(y)-y$，进一步有：(在 $i>1$ 的情况下)

$$
f(i)=(i-1)+\min
\begin{cases}
f(i-1)-(i-1)+1\\
f(j)-j &(j=\max\{j:a_{j-1}=a_i\})
\end{cases}
$$

用个桶就可以计算 $\max\{j:a_{j-1}=a_i\}$；若不存在 $j$ 使得 $a_{j-1}=a_i$，则不使用第二种更新。

设满足 $b_i=b_{i+1}=\cdots=b_n$ 的最小的 $i=k$，则答案为 $f(k)+(n-k)$，因此**最终答案**为 $\min_{i=1}^{n}\{f(i)+(n-i)\}$。

### 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+5;
int a[max_n],id[max_n],f[max_n];//id 就是上述提到的桶
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",a+i);
		if(a[i]==a[i-1])
			--i,--n;//去掉相同的相邻元素
	}
	for(int i=1;i<=n;++i)
	{
		id[a[i-1]]=i;
		f[i]=f[i-1]-(i-1)+1;
		int j=id[a[i]];
		if(j)
			f[i]=min(f[i],f[j]-j);
		f[i]+=i-1;
	}
	int ans=n;
	for(int i=1;i<=n;++i)
		ans=min(ans,f[i]+(n-i));
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：zjjws (赞：3)

既然是要求最小值，首先第一步我们可以先把相邻相同的直接先合并掉。

那么直接赛到一组里的代价有一个上界，就是总长。

以下用 $p_{x}$ 表示第 $x$ 个元素。

我们不妨设 $f_x$ 表示下标 $1$ 到 $x$ 的所有元素已经分完组的最小代价。

**最小代价定义为最小不同相邻元素数。**

首先，$f_x\le f_{x-1}+1$。这就是不考虑最后一个元素和别的组合的 Simple 的转移。

然后我们考虑当前最后一个元素 $p_x$ 塞入的时候，我们强制钦定其有贡献。也就是说，找到最大的 $y$ 满足 $p_x=p_y$ 且 $y<x$，这就是我们的转移关键点，我们强制把 $p_x$ 和 $p_y$ 放到一起。

那么 $\forall z\in(y,x)$，它们的相对顺序就定了，内部是没有新的贡献的，头和尾可能可以和前面和后面的产生贡献，以下，我们称它顺序连接组成的数字串为 **被限制串**。

**贡献为 $x$ 定义为产生了 $x$ 对相邻的相同元素。**

为什么要最大的 $y$ 呢？因为同样是产生了 $1$ 的贡献，最大的 $y$ 能够使得中间不能产生相对贡献的元素数量增多，具体的，对于：

$a,b,c,d,a,b,c,d,a,c$

我们假设现在在算最后一个位置的 $f$ 值。

最后一个 $c$ 若是和倒数第二个强制钦定，会产生的串为 $\cdots cc $ 和 $\cdots da$。

而最后一个 $c$ 若是和第一个强制钦定，会产生的串为 $\cdots cc$ 和 $\cdots dabcdda$。


这显然上面那个限制条件更少，可以产生更多的贡献。

那么对于 $p_8$，也就是 **被限制串** 的首元素，它也许可以和前面的 $d$ 产生贡献。

我们又该如何去处理这个可能存在的贡献呢？必然是不能不停往前跳的，因为这样复杂度就是 $\operatorname O(n^2)$ 的了。考虑利用之前的 DP 值来寻找。

我们注意到，如果只考虑前 $8$ 个元素，它们只有一个限制条件，就是 $p_7$ 和 $p_8$，最后两个元素不能分在同一组。那么加上这个限制以后 $f_8$ 的值会变化吗？显然不会。

那么我们就得到了递推式：$f_x=f_{y+1}+(x-(y+2)+1)-1$。

$p_{y+1}$ 以前的个数不用考虑，因为 $f_{y+1}$ 里面已经包括了，$[y+2,x]$ 内的元素要把它们的个数加上去，所以是 $(x-(y+2)+1)$，而对于 $p_x$，我们因为强制钦定了其和前面组合，所以最后代价要减 $1$。


---

代码：

```cpp

#include <queue>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define LL long long
using namespace std;
const int N=3e5+3;
inline LL rin()
{
    LL s=0;
    bool bj=false;
    char c=getchar();
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')bj=true,c=getchar();
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)return -s;
    return s;
}
inline void jh(int &x,int &y){if(x!=y)x^=y^=x^=y;}
inline int min(int x,int y){return x<y?x:y;}
inline int max(int x,int y){return x>y?x:y;}
inline LL min(LL x,LL y){return x<y?x:y;}
inline LL max(LL x,LL y){return x>y?x:y;}

int n;
int a[N];
int f[N];
int lst[N];
inline void work()
{
    n=rin();
    for(int i=1;i<=n;i++)a[i]=rin();
    int nam=0;
    for(int i=1,j;i<=n;i=j){for(j=i+1;j<=n&&a[j]==a[i];j++);a[++nam]=a[i];}
    n=nam;
    for(int i=1;i<=n;i++)f[i]=i;
    for(int i=1,j;i<=n;i++)
    {
        f[i]=min(f[i],f[i-1]+1);
        if(lst[a[i]])j=lst[a[i]],f[i]=min(f[i],f[j+1]+(i-j-2));
        lst[a[i]]=i;
    }
    printf("%d\n",f[n]);
    return;
}
int main()
{
    work();
    return 0;
}

```

---

## 作者：2huk (赞：2)

> 给定一个长度为 $n$ 的序列 $a$。请你将其划分成两个序列 $a^{(0)}$ 和 $a^{(1)}$，使得 $\operatorname{seg}(a^{(0)}) + \operatorname{seg}(a^{(1)})$ 的值最小。
>
> 对于一个序列 $a$ 而言，定义 $\operatorname{seg}(a)$ 表示为在我们将 $a$ 中相邻的所有相同元素合并后，$a$ 数组的大小。

与 [CF1479B1](https://www.luogu.com.cn/problem/CF1479B1) 几乎一模一样。

我们用两个队列维护当前的 $a^{(0)}$ 和 $a^{(1)}$。那么考虑当前枚举的 $a_i$ 应当放入哪个队列中。

可以发现一个性质，答案的计算只与两个队列中的相邻两项有关。因此我们在考虑将 $a_i$ 放入哪个队列里时只需要看它的队尾元素即可。

不妨令 $t^{(0)}$ 表示当前 $a^{(0)}$ 队列的队尾，$t^{(1)}$ 表示当前 $a^{(1)}$ 队列的队尾。分情况讨论：

- $a_i \ne t^{(0)}$  且 $a_i \ne t^{(1)}$：放入哪个队列中对后续影响都是相同的；

- $a_i = t^{(0)}$ 且 $a_i \ne t^{(1)}$：放入 $a^{(0)}$ 队列中显然更优；

- $a_i \ne t^{(0)}$ 且 $a_i = t^{(1)}$：放入 $a^{(1)}$ 队列中显然更优；

- $a_i \ne t^{(0)}$ 且 $a_i \ne t^{(1)}$：我们可以维护 $ne_i$ 表示 $i$ 之后第一个与 $a_i$ 相等的位置 $j$。那么我们只需要判断 $ne_{t^{(0)}}$ 和 $ne_{t^{(1)}}$ 谁更大，就放在哪个队列里。相当于是哪个队列当前更危险，就**不**放在哪个队列中。具体的与 [B1. Painting the Array I](https://www.luogu.com.cn/blog/748509/solution-cf1479b1) 类似，可以对比来看。

根据这样的策略计算即可。

[代码](https://www.luogu.com.cn/paste/zomqilsr)。



---

## 作者：chlchl (赞：2)

感觉题不错，写两发题解纪念一下。

## Solution
本题求的是最小可能解，那我们就要求放进去的尽可能有相邻两数相等的情况。

将题意转化为一个把 $n$ 个数按顺序丢进两个数组里的过程。

很容易可以想到一个点：假设有相等的两个数，下标分别为 $i,j$。如果要使 $i,j$ 被删掉，那么我们要求 $[i+1,j-1]$ 的数全部被扔进另一个数组里。

但是这样可能不会出现最优解，因为 $[i+1,j-1]$ 中可能会出现若干个类似这样的情况，全部把它们丢进同一个数组可能会让你得不偿失。

例如 $[1,2,3,2,4,5,4,1]$，假设你要把俩 $1$ 消掉，那么两个数组只能是 $\{1,1\},\{2,3,2,4,5,4\}$，最后的答案是 $7$。

但是，如果我们这样放：$\{1,2,2,4,4\},\{3,5,1\}$，答案会变成 $6$。

所以我们有了以下的贪心：假设当前数下标为 $i$，那么我们可以选择把 $a_i$ 放进 $0$ 数组或 $1$ 数组中。

显然如果这俩队列尾元素（设为 $c,d$）有一个与 $a_i$ 相等，自然是直接放进去，直接消，爽歪歪。

如果都不相同，现在必然要牺牲 $c,d$ 其中一个消除的机会。这时需要比较 $c$ 和 $d$ 在原数组中下一次出现的下标（记为 $nxt_c$ 和 $nxt_d$）。如果 $nxt_c<nxt_d$，证明 $c$ 能够更快被消除，对后面损失比较小，所以我们把 $a_i$ 放到 $d$ 的后面。

否则就放 $c$ 后面了。

整个过程其实就是一个“损失最小化”的思想而已。

实现不是难点，代码不贴了。

---

## 作者：XSean (赞：1)

[Problem - 1479B2 - Codeforces](https://codeforces.com/problemset/problem/1479/B2)

## 基本思路：

思路：

可以将题目转化为一个数组中的数向两个数组中插入的题型。本题的思路主要为贪心。

定义 $nxt[i]$ 为和以 $i$ 为下标的字母的后一个相同相同字母的下标。

- 当插入的数与两个数组结尾中的一个数相同时直接接上即可，$ans$ 不变。
- 没有相同时考虑插入哪一个数组，思考若 $nxt[x] > nxt[y]$，是不是接在 $x$ 的后面更优。原因是 $nxt[x]$ 越近，说明 $x$ 更快消除。
  - 深度解释就是：两个数组总会留两个数在结尾，但新加进来的数一定在其中之一，所以问题就转化为原来的结尾的两个数留哪一个，自然如果 $nxt[x] > nxt[y]$，放 $x$ 那里。否则（选 $y$ 的话）从 $nxt[y]\sim nxt[x]$ 那部分的数字可能又将 $x$ 覆盖了，得不偿失。

**时间复杂度：$O(N)$**。

## 代码实现：

核心代码：

```cpp
//bool stt;
const int N = 1e5 + 10;
int n;
int a[N];
int nxt[N], Nxt[N];
int ed[2];
//bool edd;
int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
//	cerr << (&edd - &stt) / 1024.0 / 1024.0 << endl;
	rd(n);
	rep(i, 1, n) rd(a[i]), Nxt[a[i]] = N;
	pre(i, n, 1) nxt[i] = Nxt[a[i]], Nxt[a[i]] = i;
	
	int ans = 0;
	nxt[0] = N + 1;
	rep(i, 1, n){
		if(a[ed[0]] == a[i]) ed[0] = i;
		else if(a[ed[1]] == a[i]) ed[1] = i;
		else{
			if(nxt[ed[0]] > nxt[ed[1]]) ed[0] = i;
			else ed[1] = i;
			ans++; 
		} 
	}
	prf("%d\n", ans);
	return 0;
}
```

**[完整代码](https://codeforces.com/contest/1479/submission/219896179)**

---

## 作者：Werner_Yin (赞：1)

## Problem

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/CF1480-solution.html)

[传送门CF1480D2 CF1479B2](http://codeforces.com/problemset/problem/1479/B2)

对一个序列 $A$ （$|A| <= 10^5 $）黑白染色,记一个位置上一个与它同色的位置为 $las$(没有则为 $0$),若 $las = 0 \space or \space a[las] \neq a[i]$ , 你将的到一的贡献，求最 **小** 贡献。

## Sol

WA 了 $\inf$ 发，一直没调出。

因为比赛的时候是 DP 解法，想讲 DP 的吧。

首先要去重，将 $a[i] = a[i-1] $ 的合并成一个数（因为没有贡献），设 $f[i]$  代表以 $i$  结尾最小贡献。

$f[i] = \min{(f[p]+i-p-1+a[p-1] != a[i])} ,p \in [1,i-1]$

然后 $p$ 有用的转移点一定不多，$p = i-1 \space or \space las[a[i]]+1$ , (比赛时想到了，但是搞得有点复杂，不好合并，就一直WAWAWA）

```cpp
#define in read()

// DP Sol

const int N = 1e5+10;

int n,a[N],f[N],en[N],val[N],las[N],m;

int main(){
	n = in;
	for(int i = 1;i <= n;i++) a[i] = in;
	for(int i = 1;i <= n;i++) if(a[i] != a[m]) a[++m] = a[i];
	int ans = m; f[1] = 1;las[a[1]] = 1;
	for(int i = 2;i <= m;i++){
		f[i] = f[i-1] + (a[i] != a[i-1]);
		if(las[a[i]]){
			int l = las[a[i]]+1;
			f[i] = min(f[i],f[l]+i-l-1);
		}
		las[a[i]] = i;
		ans = min(ans,f[i] + m - i);
	}
	printf("%d\n",ans);
	return 0;
}
```

当然，贪心的解法更妙。官方题解大概说此题就是 ```Bélády's algorithm```。

大概就是记个 $nxt[i]$ , 表示 $a[i]$ 下一次出现的地方，类似于上一题，当一个数放在两个序列末尾时，都会有 1 的贡献时，我们优先放那个 $nxt$ 更远的位置，因为$nxt$  更进的位置更加有 "活" 下来的机会使得贡献不增(感性理解吧）。

```cpp
#define in read()

const int N = 1e5+10;

int n,a[N],en[2],nxt[N],p[N];

int main(){
	n = in;
	for(int i = 1;i <= n;i++) a[i] = in,p[a[i]] = N;
	for(int i = n;i >= 1;i--) nxt[i] = p[a[i]],p[a[i]] = i;
	int ans = 0; nxt[0] = N+1;
	for(int i = 1;i <= n;i++){
		if(a[en[1]] == a[i]) en[1] = i;
		else if(a[en[0]] == a[i]) en[0] = i;
		else{
			if(nxt[en[0]] > nxt[en[1]]) en[0] = i;
			else en[1] = i;
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：AK_400 (赞：0)

我们先把连续相同元素合并，因为染同色一定不比不染同色劣。

看到黑白染色，价值只和上一个同色的有关，想到 [P11233 [CSP-S 2024] 染色](https://www.luogu.com.cn/problem/P11233)。

考虑 dp，记 $dp_{i,j}$ 表示当前考虑到第 $i$ 个元素，上一个和第 $i$ 个元素不同色的元素是第 $j$ 个元素的最小价值。

有

$$
dp_{i,i-1}=\min_{k=0}^{i-2}dp_{i-1,k}+[a_i\ne a_k]\\
dp_{i,j}=dp_{i-1,j}+[a_i\ne a_{i-1}](j<i-1)
$$

发现 $i$ 只和 $i-1$ 有关，可以压掉，即

$$
dp_{i-1}=\min_{k=0}^{i-2}dp_{k}+[a_i\ne a_k]\\
dp_{j}=dp_{j}+[a_i\ne a_{i-1}](j<i-1)
$$

上面的式子还是不是很好看，注意到如果要和相同元素染成相同颜色，一定是和最后一个相同元素染成相同颜色最优，记 $lst_i$ 表示最后一次元素 $i$ 的出现位置，有

$$
dp_{i-1}=\min(\min_{k=0}^{i-2}dp_{k}+1,dp_{lst_{a_i}})
$$

区间最小值，区间加，单点赋值，可以线段树优化。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[100005],ans;
vector<int>b;
int lst[100005];
int dp[100005];
int t[400005],lz[400005];
#define ls (p<<1)
#define rs (p<<1|1)
#define mid (l+r>>1)
inline void pu(int p){
    t[p]=min(t[ls],t[rs]);
}
inline void pd(int p){
    if(!lz[p])return;
    t[ls]+=lz[p];
    t[rs]+=lz[p];
    lz[ls]+=lz[p];
    lz[rs]+=lz[p];
    lz[p]=0;
}
void bd(int l,int r,int p){
    if(l==r){
        t[p]=(l?2e9:1);
        return;
    }
    bd(l,mid,ls);
    bd(mid+1,r,rs);
    pu(p);
}
void upd(int l,int r,int id,int x,int p){
    if(l==r){
        t[p]=x;
        return;
    }
    pd(p);
    if(mid>=id)upd(l,mid,id,x,ls);
    else upd(mid+1,r,id,x,rs);
    pu(p);
}
void upd(int l,int r,int ml,int mr,int x,int p){
    if(ml<=l&&r<=mr){
        t[p]+=x;
        lz[p]+=x;
        return;
    }
    pd(p);
    if(mid>=ml)upd(l,mid,ml,mr,x,ls);
    if(mid<mr)upd(mid+1,r,ml,mr,x,rs);
    pu(p);
}
int qu(int l,int r,int ml,int mr,int p){
    if(ml<=l&&r<=mr)return t[p];
    pd(p);
    int res=2e9;
    if(mid>=ml)res=min(res,qu(l,mid,ml,mr,ls));
    if(mid<mr)res=min(res,qu(mid+1,r,ml,mr,rs));
    return res;
}
void slv(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    b.push_back(0);
    for(int i=2;i<=n;i++){
        if(a[i]!=a[i-1]){
            b.push_back(a[i-1]);
        }
    }
    b.push_back(a[n]);
    int mn=b.size()-1;
    bd(0,mn,1);
    lst[b[1]]=1;
    for(int i=2;i<=mn;i++){
        int x=qu(0,mn,0,i-2,1)+1;
        if(lst[b[i]])x=min(x,qu(0,mn,lst[b[i]],lst[b[i]],1));
        upd(0,mn,i-1,x,1);
        upd(0,mn,0,i-2,1,1);
        lst[b[i]]=i;
    }
    cout<<qu(0,mn,0,mn,1)<<endl;
}
signed main(){
    slv();
    return 0;
}
```

---

## 作者：subcrip (赞：0)

这里提供另一种理解方式。题目的意思等价于将数组划分为若干段，然后分别计算奇数段和偶数段的 $seg$ 数量。

这样就变成一个常规的 DP 题。去重之后，设 $dp_i$ 表示考虑前 $i$ 个元素、并且把第 $i$ 个元素单独开一段的最小总 $seg$ 值。那么显然有两种情况：要么 $a_i$ 隔了一段跟之前的段的最后一个元素恰好相等，此时需要把 $a_i$ 和上一个等于 $a_i$ 的元素（设为 $prev_i$）之间的所有元素新分成一段；要么没有任何优化，直接 $dp_i=dp_{i-1}+1$。

对于第一种情况，是否会出现新划出来的那段的第一个元素 $a_{prev_i+1}$ 也会跟它隔一段之前那段的最后一个元素相等、而并没有被我们考虑的情况呢？答案是不会，因为通过从 $dp_{prev_i+1}$ 转移就可以涵盖这种情况。

代码相当短。

Code:

```cpp
void solve() {
    read(int, N);
    readvec(int, a, N);

    int n = unique(a.begin(), a.end()) - a.begin();

    vector<int> oc(N + 1, -1);
    vector<int> dp(n + 1);
    int res = INF;
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1] + 1;
        int prev = oc[a[i - 1]];
        if (prev != -1) {
            chmin(dp[i], dp[prev + 1] + i - 1 - prev - 1);
        }
        chmin(res, dp[i] + n - i);
        oc[a[i - 1]] = i;
    }

    cout << res << endl;
}
```

---

## 作者：xz001 (赞：0)

- 首先我们发现只有相邻两个元素之间是有关系的，所以我们可以用两个栈分别维护目前 $a^{(0)}$ 和 $a^{(1)}$ 内的元素下标。
- 然后我们依次放入元素，判断一下：
   - 如果这个元素和其中一个栈顶的元素相等（指其指向的元素），更新下标为当前所在的位置。
   - 否则我们考虑一个问题，为了让元素尽量少，我们肯定是想让相同的元素尽量碰撞在一起，所以我们看一看两个栈顶哪个指向的元素，在其位置的后面第一次出现的位置最大，就把元素丢进那个栈里（下一个位置小的我们为了让它碰上下一个，肯定是要先保留它，而让下一个位置小的去碰上下一个肯定比让下一个位置大的去碰上下一个合算）。
- 最后输出两个栈的长度和即可。
- 然后就以 $O(n)$ 的复杂度切了此题，代码如下。

```cpp
#include <bits/stdc++.h>

using namespace std;

// define
#define re register
#define fi first
#define se second
#define il inline
#define co const
#define ls (u << 1)
#define rs (u << 1 | 1)
#define fup(x, l, r) for (re int x = (l), eNd = (r); x <= eNd; ++ x )
#define fdw(x, r, l) for (re int x = (r), eNd = (l); x >= eNd; -- x )
#define int long long

int s1[1000005], s2[1000005], top1, top2, n, a[1000005], nxt[1000005], p[1000005];

signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++ i) scanf("%lld", a + i);
    for (int i = n; i >= 1; -- i) {  //预处理每个位置的其元素在其后面第一次出现的位置
    	nxt[i] = p[a[i]] ? p[a[i]] : n + 1;
    	p[a[i]] = i;
	}
	nxt[0] = n + 1;
	for (int i = 1; i <= n; ++ i) {
		if (a[i] == a[s1[top1]]) s1[top1] = i;
		else if (a[i] == a[s2[top2]]) s2[top2] = i;
		else {
			if (nxt[s1[top1]] > nxt[s2[top2]]) {
				s1[ ++ top1] = i;
			} else {
				s2[ ++ top2] = i;
			}
		}
	}
	printf("%lld", top1 + top2);
	return 0;
}


```

---

## 作者：fanfansann (赞：0)

**Problem  1479B2 - Painting the Array II**

给你一个序列 $a$，请你将这个序列撕开分成两个序列 $a^{(0)}$ 和 $a^{(1)}$，使得将 $a^{(0)}$ 和 $a^{(1)}$ 合并所有相邻且相同的元素之后，两个序列剩余的元素个数和最小。


**Solution**


我们先按照上面 D1 的贪心策略分析。



我们首先设 $a^{(0)}$ 序列的最后一个元素为 $x$ ，$a^{(1)}$ 的最后一个元素为 $y$ 。

分类讨论，我们分别考虑什么情况的时候，把当前元素分配给哪一个序列会更优，使得序列最短。

对于当前准备去分配的元素 $z1$，以及 $z1$ 后面一位元素 $z2$。

(1) 首先考虑对前面的贡献：

1. 当 `x == y` 时，上下两个序列给谁都无所谓。
2. 当 `x == z1 && y != z1` 时，很明显分配给 $x$ 会更优。
3. 当 `y == z1 && x != z1` 时，很明显分配给 $y$ 会更优。

(2) 若上述条件均为达到就考虑对后面的贡献：

1. 当 `x == z2 && y != z2` 时，很明显分配给 $y$ 会更优。
5. 当 `y == z2 && x != z2` 时，同理很明显分配给 $x$ 会更优。

**最后一种情况**：若`x != z2 && y != z2`，以及其他的所有剩余情况，这时候就有讲究了。

看上去放到哪里都区别不大，但是我们想要最终的答案尽可能地小，也就是让**元素尽可能合并**，也就是：

 $a[i]$ 以后和 $x$ 相同的元素（假设是 $xx$）尽量能和 $x$ 合并，也就是以后 $x$ 后面都不添加数。
 
 $a[i]$ 以后和 $y$ 相同的元素（假设是 $yy$）尽量能和 $y$ 合并， 也就是以后 $y$ 后面都不添加数。
 
但是我们总归是要在 $x$ 或者 $y$ 后面选择一个数放进去，假设我们放到了 $x$ 后面，这样也就断绝了后面的那个与 $x$ 相同的元素 $xx$ 与 $x$ 合并的可能性。

所以我们应该取两个队列末尾元素：$x$ 和 $y$ 中 **与它们相同的数 $xx$ 或者 $yy$ 的距离更近的那个队列**。

我们假设是 $y$ ，这样与 $y$ 相同的数 $yy$ 比与 $x$ 相同的数 $xx$ 距离更近，也就是一个一个来放的话，更先到达两个队列面前，是距离更短的那个数，也就意味着最终可以和 $y$ 合并的可能性就更大，因此我们就把 $a[i]$   放到 $x$ 的后面，让 $y$ 去追逐合并的梦想。 

应该很好理解，非常形象。

我们预处理一下下标 $i$ 的最近的下一个相同元素的下标 $\tt nex[i]$ 就行了，如何实现具体看代码，很好理解。

总结一下就是：

若`x != z2 && y != z2`，以及其他的所有剩余情况时：若`nex[x] < nex[y]` ，我们分配给 $y$ 更优。

若`x != z2 && y != z2`，以及其他的所有剩余情况时：若`nex[x] > nex[y]` ，我们分配给 $x$ 更优。

----------

所有条件按照我分析的时候的先后顺序`if else` 判断即可，因为越往前优先级越大，后面只是有合并的可能性，而前面是直接已经可以合并了。


最后简单实现一下就行了。


**Code**

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
typedef int itn;
const int N = 5e5 + 7, M = 6e6 + 7, mod = 1e9 + 7;
const ll INF = 1e18 + 7;

int n, m, t, k;
itn a[N], b[N];
vector<int> v[N];
int nex[N];

void solve()
{
    int ans = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
        v[a[i]].push_back(i);
    }
    for(int i = 1; i <= n; ++ i)
        nex[i] = n + 1;

    for(int i = 1; i <= n; ++ i) {
        for(int j = 0; j < (int)v[i].size() - 1; ++ j) {
            nex[v[i][j]] = v[i][j + 1];
        }
    }
    int x = 0, y = 0, nex_x = n + 1, nex_y = n + 1;
    for(int i = 1; i <= n; ++ i) {
        int z1 = a[i], z2 = a[i + 1];
        if(z1 == x) {
            nex_x = nex[i];
        }
        else if(z1 == y) {
            nex_y = nex[i];
        }
        else {
            ans ++ ;
            if(z2 == x && z2 != y) {
                y = z1;
                nex_y = nex[i];
            }
            else if(z2 == y && z2 != x) {
                x = z1;
                nex_x = nex[i];
            }
            else {
                if(nex_x < nex_y) {
                    y = z1;
                    nex_y = nex[i];
                }
                else {
                    x = z1;
                    nex_x = nex[i];
                }
            }
        }
    }
    printf("%d\n", ans);
}

int main()
{
    solve();
    return 0;
}
```


---

## 作者：lightup37 (赞：0)

### CF1480D2

### 题意

  **本题与 CF1480D1 的唯一区别是本题询问最小可能解.**

  给定一个数组 $a$, 你将将 $a_i$ 染为 $b_i$ 色, 其中 $b$ 是由你指定的一个 **01 数组**. 将 $a$ 数组中被染成 0 色的数字取出来并依在 $a$ 中出现的顺序排列, 组成数组 $a^{(0)}$. 同理, 将 $a$ 数组中被染成 1 色的数字取出来并依在 $a$ 中出现的顺序排列, 组成数组 $a^{(1)}$. 我们定义 $seg(c)$ 是一个正整数, 其中 $c$ 是一个数组, $seg(c)$ 的值为在我们将 $c$ 中相邻的所有相同元素合并后, $c$ 数组的大小. 例如, $seg([1, 1, 4, 5, 1, 4]) = |[1, 4, 5, 1, 4]|=5$. 最小化 $seg(a^{(0)})+seg(a^{(1)})$.

### 输入格式

  第一行包括一个正整数 $n(1\leq n\leq 10^5)$.

  第二行包括 $n$ 个正整数 $a_1, a_2, \cdots,a_n(1\leq a_i\leq n)$.

### 输出格式

  仅输出一个正整数, 代表最小的 $seg(a^{(0)})+seg(a^{(1)})$.

### 解法

  我们考虑贪心. 假设现在是第 $k$ 位, 考虑将其加入 $a^{(0)}$ 或者 $a^{(1)}$. 我断言我们将会将其加入 $a^{(0)}$, 当且仅当 $a^{(0)}$ 的最后一位等于 $a_k$, 或者 $a^{(0)}$ 的最后一位在 $a$ 中下一次出现的位置**大于** $a^{(1)}$ 的最后一位在 $a$ 中下次出现的位置. 否则, 如果我们将 $a_k$ 加入 $a^{(0)}$, 则一定不优于我们将 $a_k$ 加入 $a^{(1)}$, 因为我们将其加入 $a^{(1)}$ 选择更多.

### 代码

```cpp
#include<bits/stdc++.h>
#define f(i,x,y) for(int i=x, i##end=y; i<=i##end; ++i)
#define d(i,x,y) for(int i=y, i##end=x; i>=i##end; --i)
#define ll long long
char ch;
int rd() {
  int f=1, x=0; ch=getchar();
  while(!isdigit(ch)) { f=((ch=='-')?-1:f); ch=getchar(); }
  while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
  return x*f;
}
void rd(int& x) { x=rd(); }
using namespace std;
#define _ 1000005
int a[_], a0[_], a1[_], n, tot0, tot1;
int pos0[_], pos1[_], nxt[_], Nxt[_], ans;
std::vector<int> pos[_];
int main() {
  rd(n); f(i,1,n) rd(a[i]); d(i,1,n) { nxt[i]=Nxt[a[i]] ? Nxt[a[i]] : n+1; Nxt[a[i]]=i; } nxt[0]=n+1;
	f(i,1,n) {
		int xp=nxt[pos0[tot0]], yp=nxt[pos1[tot1]];
		if(a0[tot0] == a[i]) xp=n+2;
		if(a1[tot1] == a[i]) yp=n+2;
		if(xp > yp) { ans+=(a0[tot0]!=a[i]); a0[++tot0]=a[i]; pos0[tot0]=i; }
		else { ans+=(a1[tot1]!=a[i]); a1[++tot1]=a[i]; pos1[tot1]=i; }
	}
	printf("%d\n", ans);
  return 0;
}
```

---

## 作者：K_Madoka (赞：0)

## 题意

把数组 $a$ 分成两个不相交的子数组 $a^0$ 和 $a^1$。

定义 $seg(a)$ 为数组 $a$ 中不同的连续段。

例如 $[1,1,2,2,3,3,3,2]$ 的 $seg$ 为 $4$ ，为 $[1,2,3,2]$。

现要求分出来的 $seg(a^0) + seg(a^1)$ 最小。

## 解法

建议先看[我的D1题解](https://www.luogu.com.cn/blog/Oaklimy/cf1480d1-painting-the-array-i)。

和上题正好相反，只不过判断的细节和计算答案的方式有些变化。

现在还是分为几类：

现在可以把不同的情况分一下类：

$1.$ $a_{a0} = a_{a1}$

这时候把 $a_i$ 放到任意一边都可以。

$2.$ $a_{a0}\neq a_i$ 且 $a_{a1} = a_i$

显然放 $a_{a1}$。

$3.$ $a_{a1}\neq a_i$ 且 $a_{a0} = a_i$

显然放 $a_{a0}$。

$4.$ $a_{a0}\neq a_i$ 且 $a_{a0} \neq a_i$

设 $nxt_{a0}$ 为下一个 $a_{a0}$ 出现的位置， $a1$ 同理。

和D1反着来，优先挑离下一个出现远的，也就是 $nxt$ 值小的。

```cpp
#define MAXN 100010
ll n,a[MAXN],nxt[MAXN],lst[MAXN],a0,a1;
int main(){
	n=readll();
	for(int i=1;i<=n;i++)a[i]=readll();
	nxt[0]=n+1;
	for(int i=1;i<=n;i++)lst[a[i]]=n+1;
	for(int i=n;i>=1;i--){
		nxt[i]=lst[a[i]];
		lst[a[i]]=i;
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		if(a[a0]!=a[i]&&a[a1]!=a[i]){
			if(nxt[a0]>nxt[a1])a0=i;
			else a1=i;
			ans++;
		}
		else if(a[i]==a[a0])a0=i;
		else if(a[i]==a[a1])a1=i;
		else a0=i,a1=i;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

