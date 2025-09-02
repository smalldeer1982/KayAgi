# [AGC049F] Happy Sequence

## 题目描述

给定长度为 $N$ 的整数序列 $A,B,C$。当且仅当满足以下条件时，すぬけ君会感到幸福：

- 对于所有整数 $x$，都有 $\sum_{1 \leq i \leq N} |A_i - x| \leq \sum_{1 \leq i \leq N} |B_i - x|$。

为了让すぬけ君幸福，你可以将 $A$ 的若干（可以为零）个元素修改为任意整数。将 $A_i$ 修改为 $t$ 的代价为 $C_i \times (A_i - t)^2$。修改后的值也必须是整数。

请你求出让すぬけ君幸福所需的最小总代价。

## 说明/提示

## 限制条件

- $1 \leq N \leq 2 \times 10^5$
- $0 \leq A_i \leq 2 \times 10^5$
- $0 \leq B_i \leq 2 \times 10^5$
- $1 \leq C_i \leq 5$
- 输入均为整数。

## 样例解释 1

可以按如下方式操作，总代价为 $6$：

- 将 $A_1$ 修改为 $2$，代价为 $1 \times (0-2)^2 = 4$。
- 将 $A_3$ 修改为 $3$，代价为 $2 \times (4-3)^2 = 2$。

操作后，$A = (2,1,3)$，此时すぬけ君感到幸福。

无法以低于 $6$ 的总代价达成目标，因此答案为 $6$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
0 1 4
1 2 3
1 3 2```

### 输出

```
6```

## 样例 #2

### 输入

```
20
185 89 216 105 56 383 193 161 75 196 322 180 390 15 206 78 275 338 225 167
161 77 294 117 22 382 218 140 57 231 343 160 397 8 264 68 301 349 295 157
3 1 3 5 2 1 3 4 1 4 2 2 2 2 5 1 1 5 4 3```

### 输出

```
3758```

## 样例 #3

### 输入

```
1
0
0
1```

### 输出

```
0```

# 题解

## 作者：zhoukangyang (赞：31)

[cnblogs](https://www.cnblogs.com/zkyJuruo/p/17592721.html)。

## 题面

给定长度为 $n$ 的整数序列 $A$，$B$ 和 $C$。snuke 是开心的，当且仅当下面的条件满足：

- 对于任意整数 $x$，均有 $\sum_{1 \le i \le n} |A_i - x| \le \sum_{1 \le i \le n} |B_i - x|$。

他决定改变 $A$ 中的一些元素来变得开心。把 $A_i$ 改成 $t$ 需要花费 $C_i \times (A_i-t)^2$ 的代价。其中，$t$ 必须得是整数。

为了使 snuke 变得开心，至少要花费多少代价呢？

数据范围：$1 \le n \le 2 \times 10^5$，$0 \le A_i,B_i,C_i \le \color{red}{10^9}$。

## 题解

首先考虑维护 $g(x) = \sum_i |a_i-x| - \sum_i |b_i-x|$。最后的要求就是 $g(x) \le 0$。

可以把 $A_i,B_i$ 看成数轴上的点。对于一个 $A_p = x$，将 $A_p$ 改成 $y(y \ge x)$ 的过程可以看成是不停地把  $A_p$ 往右移。每次对 $A_p$ 的移动 $i \to i+1(i \ge A_p)$，相当于是给 $x \le i$ 的 $g(x)$ 增加 $1$，给 $x > i$ 的 $g(x)$ 减少 $1$。其代价为 $C_p(2i-2A_p+1)$。

注意到 $x \to x+1$ 和 $x+1 \to x+2$ 中，后者增加的代价更大，而前者的操作优于后者。因此虽然我们要求执行完 $x \to x+1$ 后才能执行 $x+1 \to x+2$，但是事实上把他们独立开来仍然是正确的。减小的操作是对称的。

又注意到如果有操作 $u \to u-1$，和操作 $v \to v+1$，那么必然有 $u-1 \ge v+1$：如果不满足条件，则把两个操作都删了肯定更优秀。

这就意味着存在一个分界线 $mid$，使得只有 $u > mid$ 的 $u \to u-1$ 操作和 $v<mid$ 的 $v \to v+1$ 操作。在这里，如果存在多个 $mid$，选择 $g(mid)$ 最大的那个。

然后可以发现，操作后必然满足 $g(mid)=0$。这是因为，我们找到 $mid$ 左边第一个向右的操作，和 $mid$ 右边的第一个操作，同时删去他们，答案一定变小（由于奇偶性，$g(mid) \neq 1$）。

观察到所有操作都让 $g(mid)$ 减小了，这说明 $mid$ 是被操作最多的元素。而由于操作后 $g(mid) = 0$，说明 $g(mid)$ 是操作后最大的元素。减的最多，结果最大，说明 $g(mid)$ 初始时就是最大的！因此我们就能够找到 $mid$ 了。

找到后，考虑把问题分成左右两部分，左边增加，右边减小。而两边中唯一会影响另一边的因素是两边的操作次数。

带入 $g(-\infty)$ 和 $g(\infty)$ 可知 $\sum a_i = \sum b_i$，因此我们可以知道两边操作个数的差。我们又知道两边操作次数的和：总和为 $g(mid)$。这样就可以解出来两边的操作次数。因此两部分就是完全独立的了。更具体地，两边操作后均满足 $\sum a_i = \sum b_i$。

所以现在我们的问题就转化成了一个只有增加的问题了。

二分一个斜率 $M$，然后执行所有代价 $\le M$ 的操作。每个点移动到了一个新点，我们从把每个点都看成从新点出发移动。

注意到改成从新点移动后，之前的大部分结论都还是是成立的！也就是说，这里同样存在一个 $mid$，使得之后做的操作，$mid$ 左边的只向右，$mid$ 右的只向左。$mid$ 仍然满足 $g(mid)$ 是最大的。我们仍然可以按照 $mid$ 把数轴切成两半，两半互不相关！

注意到切完之后，两边操作的代价范围都减半了，因此不停地做一些类似整体二分的东西，递归下去即可！

时间复杂度 $\Theta(n \log n (\log A + \log B + \log C))$。

[aclink](https://atcoder.jp/contests/agc049/submissions/41176875)。

---

## 作者：UltiMadow (赞：1)

记 $L=2\times 10^5$ 为值域，显然所有 $a_i$ 的取值都在 $[0,L]$ 之间

首先令所有 $p_i=0$，然后通过操作调整 $p$ 使得 $p$ 作为答案序列合法且代价最小

若 $p_i=k$，使 $p_i$ 变为 $k+1$ 的代价为 $c_i(-2(a_i-k)+1)$，我们用二元组 $(i,k)$ 代表进行此操作，显然进行完 $(i,k)$ 操作之后才能进行 $(i,k+1)$ 操作

记 $g(x)=\sum|b_i-x|-\sum|p_i-x|$，则题目条件等价于对于任意 $x\in[0,L]$ 有 $g(x)\ge 0$

将 $p_i$ 从 $k$ 变为 $k+1$ 的效果为使所有 $x\in [0,k]$ 的 $g(x)$ 减去 $1$，所有 $x\in (k,L]$ 的 $g(x)$ 加上 $1$，那么显然 $k$ 越大对于 $g$ 的正贡献越小，负贡献越大；又 $k$ 越大 $(i,k)$ 操作的代价越大，所以 $(i,k+1)$ 比 $(i,k)$ 先操作一定不优，所以不用特别限制 $(i,k)$ 要在 $(i,k+1)$ 前面操作

那么问题就变成了有若干形如 $(i,k)$ 的操作，每个操作有一个代价，作用是使 $[0,k]$ 中的 $g(x)$ 减去 $1$，$(k,L]$ 中的 $g(x)$ 加上 $1$，所有要求在所有 $g(x)\ge 0$ 的情况下代价最小

不妨对于每个 $x\in[0,L]$ 考虑操作应该满足什么条件才能使 $g(x)\ge 0$

记 $g_0(x)=\sum|b_i-x|-\sum|0-x|$，即初始状态下 $g(x)$ 的取值

记 $f_k$ 为形如 $(i,k)$ 的操作进行的次数，则 $g(x)=g_0(x)+\sum\limits_{i=0}^{x-1}f_i-\sum\limits_{i=x}^Lf_i\ge0$

记 $sum=\sum f_i$，则 $g_0(x)+sum-2\sum\limits_{i=x}^Lf_i\ge 0\Leftrightarrow \sum\limits_{i=x}^Lf_i\le\lfloor\frac{g_0(x)+sum}{2}\rfloor$

带入 $x=0$，可得 $sum\le g_0(0)$，带入 $x=L+1$ 可得 $sum\ge g_0(L+1)=g_0(0)$

所以 $sum=g_0(0)=\sum b_i$，那么 $\sum\limits_{i=x}^Lf_i$ 的上界就确定了，记其为 $lmt_x$

那么就可以得到一个朴素的做法：

维护一个堆，从后往前枚举 $x$，把所有形如 $(i,x)$ 的操作加入堆中，不断删除堆中代价最大的操作使得堆中元素个数 $\le lmt_x$

这样做的时间复杂度为 $\mathcal O(nL\log nL)$，需要优化

记 $c_i$ 值域为 $m=5$

记当前堆中最大操作代价为 $mx$，堆大小为 $sz$

对于所有 $i\le mx$，记 $del_i$ 为代价为 $i$ 的操作被删除的次数

记 $C_{i,k}$ 为 $(i,k)$ 操作的代价，$f(k,v)=\sum [C_{i,k}=v]$

枚举到 $x$ 时，先加入所有代价 $\le mx$ 的 $(i,x)$ 操作，即把 $sz$ 加上 $\sum\limits_{i\le v}f(x,v)$，然后分类讨论：

1. 若 $sz>lmt_x$，则考虑计算堆中代价为 $mx$ 的操作个数，即 $\sum\limits_{i\ge x}f(i,mx)-del_{mx}$，若其 $> sz-lmt_x$，则删除 $sz-lmt_x$ 个 $mx$，否则把 $mx$ 全部删完，并把 $mx$ 减去 $1$

2. 若 $sz<lmt_x$，则把 $mx$ 加上 $1$，加入的操作个数为 $f(x,mx)$，并把 $del_{mx}$ 设置为 $\sum\limits_{i>x}f(i,mx)$，若 $f(x,mx)>lmt_x-sz$，则删除一些值为 $mx$ 的操作使得最后 $sz=lmt_x$

在预处理 $sum_{i,j}$ 表示 $c_k=i$，$a_k\le j$ 的 $k$ 的个数之后，就可以在 $\mathcal O(m)$ 的时间内求出 $f(x,v)$ 关于 $v$ 的前缀和和关于 $x$ 的后缀和

记 $mx$ 的变化次数为 $T$，则总复杂度为 $\mathcal O(mT)$

下证 $T$ 为 $\mathcal O(mL)$ 级别

记 $mx_k$ 为 $x=k$ 时的 $mx$，$\Delta_k=lmt_k-lmt_{k+1}$

记 $f_k$ 为 $(i,k)$ 操作中代价第 $\Delta_k$ 小的，$g_{k}$ 为 $(i,k)$ 操作中代价第 $\Delta_{k+1}$ 小的

不难发现 $|mx_k-mx_{k+1}|\le |f_k-f_{k+1}|$ 对于任意 $k$ 成立

所以只需证 $\sum |f_k-f_{k+1}|$ 为 $\mathcal O(mL)$ 级别即可

由于 $\Delta_k$ 大约和 $\frac{g_0(k)-g_0(k+1)}2$ 相等，所以有 $\Delta_k\ge \Delta_{k+1}$，且 $0\le \Delta_k\le n$

考虑 $(i,k-1)$ 和 $(i,k)$ 两组操作，则有后面那组操作的代价为前面那组操作的代价加上 $2c_i$

不难发现 $f_k-2m\le g_{k-1}$，又 $\Delta_{k-1}\ge \Delta_k$，则 $g_{k-1}\le f_{k-1}$，则有 $f_{k}-f_{k-1}\le 2m$

又对于任意 $k$ 有 $|f_k|\le mL$ 成立，可推得 $\sum|f_{k}-f_{k-1}|$ 为 $\mathcal O(mL)$ 级别

所以总复杂度 $\mathcal O(m^2L)$

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 200010
using namespace std;
const int z=2000005;
const int L=200000;
int n,sum,ans,a[MAXN],b[MAXN],c[MAXN];
int del[MAXN*20],sa[6][MAXN],sb[MAXN];
int g0[MAXN],lmt[MAXN];
int getx(int x,int v){//C_{k,i}=v(i>=x)
	int ret=0;
	for(int i=1;i<=5;i++){
		if(v%i||!(v%(2*i)))continue;
		int now=(v/i-1)/2;
		ret+=sa[i][min(L-now,L)]-(x-now<=0?0:sa[i][min(x-now-1,L)]);
	}return ret;
}
int divdn(int x,int y){return (int)floor(1.0*x/y);}
int getv(int x,int v){//C_{k,x}=i(i<=v)
	int ret=0;
	for(int i=1;i<=5;i++){
		int now=x-divdn((divdn(v,i)-1),2);
		ret+=sa[i][L]-(now<=0?0:sa[i][min(L,now-1)]);
	}return ret;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]),sum+=b[i];
	for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
	for(int i=1;i<=n;i++)sa[c[i]][a[i]]++,sb[b[i]]++;
	for(int i=1;i<=5;i++)
		for(int j=1;j<=L;j++)sa[i][j]+=sa[i][j-1];
	for(int i=1;i<=L;i++)sb[i]+=sb[i-1];
	g0[0]=sum;for(int i=1;i<=L;i++)g0[i]=g0[i-1]+2*sb[i-1]-n;
	for(int i=1;i<=L;i++)g0[i]-=i*n;
	for(int i=0;i<=L;i++)lmt[i]=(sum+g0[i])/2;
	int mx=0,sz=0;
	for(int i=L;i>=0;i--){
		sz+=getv(i,mx);
		while(sz>lmt[i]){
			int now=getx(i,mx)-del[mx+z];
			if(now>sz-lmt[i]){
				del[mx+z]+=sz-lmt[i];
				sz=lmt[i];break;
			}mx--;sz-=now;
		}
		while(sz<lmt[i]){
			mx++;del[mx+z]=getx(i+1,mx);
			int now=getx(i,mx)-del[mx+z];
			if(now>lmt[i]-sz){
				del[mx+z]+=now-(lmt[i]-sz);
				sz=lmt[i];break;
			}sz+=now;
		}
	}
	for(int i=1;i<=n;i++)ans+=c[i]*a[i]*a[i];
	for(int i=-z;i<=mx;i++)ans+=(getx(0,i)-del[i+z])*i;
	printf("%lld",ans);
	return 0;
}
```

---

