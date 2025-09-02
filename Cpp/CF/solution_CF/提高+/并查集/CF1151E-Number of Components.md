# Number of Components

## 题目描述

克雷姆兰王国是一棵树（一个无环连通无向图），包含 $n$ 个顶点。每个顶点 $i$ 有一个权值 $a_i$。所有顶点通过边依次相连。具体来说，对于每个 $1 \leq i < n$，存在一条连接顶点 $i$ 和 $i+1$ 的边。

定义函数 $f(l, r)$，它接收两个整数 $l$ 和 $r$（$l \leq r$）：

- 只保留权值在 $l$ 到 $r$ 范围内的顶点。
- 该函数的值为新图中的连通块数量。

你的任务是计算如下的和：$$\sum_{l=1}^{n} \sum_{r=l}^{n} f(l, r)$$

## 说明/提示

在第一个样例中，函数值如下：

- $f(1, 1)=1$（只剩下编号为 $2$ 的顶点，形成一个连通块）
- $f(1, 2)=1$（剩下编号为 $1$ 和 $2$ 的顶点，形成一个连通块）
- $f(1, 3)=1$（所有顶点都保留，形成一个连通块）
- $f(2, 2)=1$（只剩下编号为 $1$ 的顶点）
- $f(2, 3)=2$（剩下编号为 $1$ 和 $3$ 的顶点，形成两个连通块）
- $f(3, 3)=1$（只剩下编号为 $3$ 的顶点）

总和为 $7$。

在第二个样例中，函数值如下：

- $f(1, 1)=1$
- $f(1, 2)=1$
- $f(1, 3)=1$
- $f(1, 4)=1$
- $f(2, 2)=1$
- $f(2, 3)=2$
- $f(2, 4)=2$
- $f(3, 3)=1$
- $f(3, 4)=1$
- $f(4, 4)=0$（没有顶点剩下，连通块数量为 $0$）

总和为 $11$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 1 3
```

### 输出

```
7```

## 样例 #2

### 输入

```
4
2 1 1 3
```

### 输出

```
11```

## 样例 #3

### 输入

```
10
1 5 2 5 5 3 10 6 5 1
```

### 输出

```
104```

# 题解

## 作者：wucstdio (赞：34)

感觉和楼下的推出来式子一样但是我的做法应用面更广一些。提供一种新的思路吧。

## 题意

求

$$\sum_{i=1}^n\sum_{j=i}^nf(i,j)$$

其中$f(i,j)$表示只保留权值在$[i,j]$之间的点形成的连通块数量。

## 题解

一看连通块，就考虑转化，连通块数量=点数-边数。

知道了这一点，我们就可以将点数和边数分开统计，然后两个一减就行了。

对于点数，我们考虑每一个点的贡献。对于$i$这个点，它会被算进答案里，当且仅当$l\le a_i\&r\ge a_i$，所以它会被算$a_i(n-a_i+1)$次。

对于边数，我们考虑每一条边的贡献。对于$(i,i+1)$这条边，它会被算进答案里，当且仅当$i$和$i+1$都被算进了答案。所以它会被算$\min(a_i,a_{i+1})(n-\max(a_i,a_{i+1})+1)$次。

然后就做完了，时间复杂度$O(n)$。难度主要在转化。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
int n,a[100005];
ll ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		ans+=1ll*a[i]*(n-a[i]+1);
	}
	for(int i=1;i<n;i++)
	  ans-=1ll*min(a[i],a[i+1])*(n-max(a[i],a[i+1])+1);
	printf("%I64d\n",ans);
	return 0;
}
```

---

## 作者：ChthollyTree (赞：16)

应该是我AC的1000 题，发篇题解祭

另外这场也让我的CF[$\color{purple}{Ynoi}$](https://codeforc.es/profile/Ynoi)紫名了

这场其实先开DE的是很赚的，因为其实都不难

闲话不多说，我说一下思路：

考虑每个点的贡献

我们认为一个联通块里让编号最大的点产生贡献

那么，对于一个点i，我们考虑她如果要对答案产生贡献，一定要点 i 存在，而点i + 1 不存在

而点n只用包含这个点就行了

这样我们求出每个点符合条件的区间个数即可

具体是这样子的

如果$a_i > a_{i+1}$ 贡献 = $(a_i - a_{i+1})*(n-a_i+1)$

如果 $a_i < a_{i+1}$ 贡献 = $(a_{i+1}-a_i)*a_i$

```
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define LL long long
#define INF (LL)(0x3f3f3f3f)*(LL)0x3f3f3f3f
#define MAXN 100005

LL n,m;
LL a[MAXN];
LL ans = 0;

signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i ++)
		cin >> a[i];
	for(int i = 1; i < n; i ++)
	{
		int x = a[i],y = a[i+1];
		if(x > y) {
			ans += (x-y)*(n-x+1);
		} else {
			ans += (y-x)*x;
		}
	}
	ans += a[n]*(n-a[n]+1);
	cout<<ans;
	return 0;
 } 
```

---

## 作者：Pengzt (赞：6)

[CF1151E](https://www.luogu.com.cn/problem/CF1151E)

发现每一个 $f(l, r)$ 中的连通块总是一条链（一棵树）。

那么此时连通块的数量就等于点的数量减去边的数量。

先考虑点的**总数**，一个价值为 $a_i$ 的点一定是在 $l \leqslant a_i$ 且 $r\geqslant a_i$ 的 $f(l, r)$ 中才会有一个贡献，根据乘法原理，它会产生 $a_i\times (n - a_i + 1)$ 的贡献。

再考虑边的总数，因为边是从 $i$ 连向 $i + 1$ 的，当且仅当 $l\leqslant \min(a_i, a_{i + 1})$ 且 $r\geqslant \max(a_i, a_{i + 1})$ 时，这条边才会有一个贡献，根据乘法原理，它会产生 $\min(a_i, a_{i + 1})\times (n - \max(a_i,a_{i + 1}) + 1)$ 的贡献。

最后答案就显而易见了。

时间复杂度：$\mathcal{O}(n)$

[评测记录](https://www.luogu.com.cn/record/100213940)

---

## 作者：hs_black (赞：5)

#### 很常见的思想：将整体求改为统计每个部分的贡献

本题中统计[l, r]时， 每个连通块有一个重要特征， 最右端的数在[l,r]中而下一个数不在（好像是句废话

那么我们分别考虑每个点对连通块的贡献， 即它是某个连通块的右端点， 这样可以保证每个连通块只会被算一次

对于序列 $a_1a_2\cdots a_n$ 若$a_i < a_{i+1}$ l的范围是1~$a_i$ r的范围是$a_i$ ~ $ a_j-1$  ans += (a[i+1] - a[i]) * a[i];

否则 同理 ans += (n-a[i]+1) * (a[i] - a[i+1]);

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#define ll long long
using namespace std;
template <typename T>
void read(T &x) {
	x = 0;int f = 1;
	char c = getchar();
	for (;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for (;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x *= f;
}
const int N = 100050;
ll n, a[N], ans;
int main() {
	read(n);
	for (int i = 1;i <= n; i++) read(a[i]);
	for (int i = 1;i <= n; i++) {
		if (a[i+1] > a[i]) 
			ans += (a[i+1] - a[i]) * a[i];
		else ans += (n-a[i]+1) * (a[i] - a[i+1]);
	}
	cout << ans << endl;
	return 0;
}

```



---

## 作者：hank0402 (赞：4)

首先，因为不存在环，所以连通块个数等于点数减边数。

所以我们可以把点数与边数分开来求。

若点 $i$ 被包含，那么符合条件的 $l,r$ 一定满足 $l\leq a_i \leq r$，符合的 $l$ 有 $a_i$ 个，$r$ 有 $n-a_i+1$ 个，根据乘法原理，点数的个数和就是 $\sum_{i=1}^n a_i\times (n-a_i+1)$。

考虑边数的求法，对于每一条边 $i\to i+1$，必须要两边的节点 $i$ 和 $i+1$ 都要被 $l,r$ 包含，则符合条件的 $l$ 有 $\min\{a_i, a_{i+1}\}$ 个，$r$ 有 $n-\max\{a_i, a_{i+1}\}+1$ 个，根据乘法原理，边数的个数和就是 $\sum_{i=1}^{n-1} \min\{a_i, a_{i+1}\}\times (n-\max\{a_i, a_{i+1}\}+1)$ 个。

然后将两数相减即可得出答案。

时间复杂度 $\Theta(n)$。

$\textbf{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 10;
int n, a[N];
int cntp, cnte;
signed main() {
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for(int i = 1; i <= n; ++i) cntp += a[i] * (n - a[i] + 1);
    for(int i = 1; i < n; ++i) cnte += min(a[i], a[i + 1]) * (n - max(a[i], a[i + 1]) + 1);
    cout << cntp - cnte;
    return 0;
}
```

---

## 作者：IceKylin (赞：2)

# CF1151E Number of Components 题解
### [原题链接（in luogu）](https://www.luogu.com.cn/problem/CF1151E)
### [原题链接（in CodeForces）](https://codeforces.com/problemset/problem/1151/E)
### [更好的阅读体验？](https://www.luogu.com.cn/blog/std-IK/cf1151e-ti-xie)

简单 **计算贡献题**，可以将连通块数量转化求解。

由于求的是 **链上** 连通块数量，所以有如下一个常用的关系式：

$\text{连通块数量}=\text{点数}-\text{边数}$。

1. 考虑能使得点 $i$ 产生贡献的 $f(l,r)$，需满足 $l\in [1,a_i],r\in [a_i,n]$，所以一共产生的贡献为 $a_i(n-a_i+1)$。

2. 考虑能使得边 $(i,i+1)$ 产生负贡献的 $f(l,r)$，需满足 $l\in [1,\min\{a_i,a_i+1\}],r\in[\max\{a_i,a_i+1\},n]$，所以一共产生的负贡献为 $\min\{a_i,a_i+1\}(n-\max\{a_i,a_i+1\}+1)$。

综合以上两部分贡献即可。

P.S. 本题的数据规模需要开 long long。

## AC代码

```cpp
//By IceKylin
#include<bits/stdc++.h>
#define ll long long
#define ios ios::sync_with_stdio(false)
#define maxn 114514
using namespace std;
ll n,ans,a[maxn];
int main(){
	ios;
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		ans+=a[i]*(n-a[i]+1);
	}
	for(int i=1;i<n;++i)
		ans-=min(a[i],a[i+1])*(n-max(a[i],a[i+1])+1);
	cout<<ans;
	return 0;
}
```

---

## 作者：xuzz (赞：2)

## 喵喵题

由于 $ \sum\limits_{l=1}^n\sum\limits_{r=l}^nf(l,r)$ 难以求解，考虑转化，

连通块个数 $=$ 点数 $-$ 边数，

可以将所有的点数和所有的边数分开求和处理。

用 $a_i$ 表示第 $i$ 个数的权值，$l_i$ 和 $r_i$ 表示第 $i$ 条边两个端点的编号，

考虑点数：只有 $ l\le a_i $ 且 $r \ge a_i $ 时第 $i$ 个数会被取到，取到次数为 $a_i\times(n+1-a_i)$，

考虑边数：只有 $ l\le \min(a_{l_i},a_{r_i}) $ 且 $r \ge \max(a_{l_i},a_{r_i}) $ 时第 $i$ 条边会被取到，取到次数为 $\min(a_{l_i},a_{r_i}) \times (n-\max(a_{l_i},a_{r_i})+1)$，

最后将点数减去边数即为答案。


```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
int main()
{
	const int n=read(),n1=n+1;
	long long x,pre=read(),ans=pre*(n1-pre);
	for(int i=2;i<=n;i++) x=read(),ans+=x*(n1-x)-((x<pre)?x*(n1-pre):pre*(n1-x)),pre=x;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：JWRuixi (赞：2)

~~代码难度 $800$……~~

- 题意

给定一条长为 $n$ 的链，相邻点之间连边，每个点有一个权值 $a_i$。设 $f(l,r)$ 为权值属于 $[l,r]$ 的点所形成的连通块数量，求 $\sum\limits_{1\le l\le r\le n}f(l,r)$。

- 分析

首先，因为在一条链上求连通块的数量，所以可以改成点数减边数，考虑分开求。

对于第 $i$ 个点，它被算入当且仅当 $a_i\in [l,r]$，所以被算 $a_i\times(n-a_i+1)$ 次。

对于每一条边 $(i,i+1)$，它被算当且仅当 $a_i,a_{i+1}\in[l,r]$，所以被算入 $\min(a_i,a_{i+1})\times(n-\max(a_i,a_{i+1})+1)$ 次。

时间复杂度 $\mathcal O(n)$。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define LL long long
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(1e5 + 500);
int n, a[maxn];
LL ans;

int main () {
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read(), ans += (LL)a[i] * (n - a[i] + 1);
	for (int i = 1; i < n; i++) {
		if (a[i] <= a[i + 1]) ans -= (LL)a[i] * (n - a[i + 1] + 1);
		else ans -= (LL)a[i + 1] * (n - a[i] + 1);
	} 
	write(ans);
}
```

---

## 作者：EuphoricStar (赞：2)

## 思路

由于给出的是一条链，所以可以把它看做森林，因此可以将连通块数量转化成**点数 - 边数**。

对于点数和边数分别计算。

对于权值为 $i$ 的点，设权值为 $i$ 的点共有 $b_i$ 个，显然当 $l \le i \le r$ 这个点才会计入答案中，根据乘法原理可得对点数的贡献为 $b_i \times i \times (n-i+1)$。

对于 $(i,i+1)$ 这条边，只有当 $i$ 和 $i + 1$ 都被激活时，这条边才会计入答案中，根据乘法原理可得对边数的贡献为 $\min(a_i, a_{i+1}) \times (n - \max(a_i, a_{i+1}) + 1)$。

最后再减一下就行了。

## 代码

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 100100;

ll n, a[maxn], b[maxn];

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		++b[a[i]];
	}
	ll edg = 0, ver = 0;
	for (int i = 1; i < n; ++i) {
		ll mx = max(a[i], a[i + 1]);
		ll mn = min(a[i], a[i + 1]);
		edg += mn * (n - mx + 1);
	}
	for (int i = 1; i <= n; ++i) {
		ver += b[i] * (n - i + 1) * i;
	}
	cout << ver - edg << endl;
	return 0;
}
```


---

## 作者：xkcdjerry (赞：1)

记一下我的思考过程，以下为了方便，定义 $c_i=\sum\limits^n_{j=1} [a_j=i]$，$d_{i,j}=\sum\limits_{k=2}^n [a_{k-1}=i]\times[a_k=j]$。

### 算法1：我会暴力！

枚举 $l,r$，然后对于所有 $l,r$ 内的边和点跑并查集，$f(l,r)$ 的值就是总点数减去 merge 成功次数。

复杂度：$O(n^3 \log^*n)\approx O(n^3)$，能过 $n=300$。

### 算法2：我会~~蒙~~推导结论！

考虑每个点最多被左边 merge 一次，右边 merge 一次，而左边和右边不经过这个点不可能存在于同一个连通块内，所以 merge 一定会成功，即 $f(l,r)$ 的值为总点数减去 merge 总次数。

又因为没遇到一个边就 merge 一次，所以 $f(l,r)$ 的值为对应子图内的点数减边数。

因此：
$$
Ans=\sum^n_{l=1}\sum^n_{r=l}(\sum^r_{i=l} c_i+ \sum^r_{i=l}\sum^r_{j=l} d_{i,j})
$$
直接做能喜提 $O(n^4)$ 复杂度。给 $c$ 和 $d$ 作前缀和能优化到 $O(n^2)$，能过 $n=10000$。

### 算法3：我会推式子！

（当时没想到拆贡献所以绕了一大圈）

这个求和符号里的 $c_i$ 和 $d_{i,j}$ 值和 $l,r$ 半毛钱关系没有，$l,r$ 唯一能影响的是它的系数，考虑交换求和符号：
$$
Ans=\sum^n_{l=1}\sum^n_{r=l}\sum^r_{i=l} c_i+ \sum^n_{l=1}\sum^n_{r=l}\sum^r_{i=l}\sum^r_{j=l} d_{i,j}\\
=\sum^n_{i=1}c_i\sum^n_{l=i}\sum^i_{r=l}1+\sum^n_{i=1}\sum^n_{j=1} d_{i,j}\sum^{\min(i,j)}_{l=1}\sum^n_{r=\max(i,j)} 1\\
= \sum^n_{i=1} i\times(n-i+1) \times c_i+ \sum^n_{i=1}\sum^n_{j=1} \min(i,j) \times (n-\max(i,j)+1) \times d_{i,j}
$$
发现这样复杂度还是 $O(n^2)$，但是考虑最多只有 $n$ 个 $d_{i,j}$ 有值，所以可以拆一下 $d_{i,j}$，顺手也把 $c_i$ 也拆了：
$$
Ans=\sum_{i=1}^n i \times (n-i+1) \sum^n_{j=1} [a_j=i] + \sum^n_{i=1}\sum^n_{j=1} \min(i,j) \times (n-\max(i,j)+1) \sum^n_{k=2} [a_{k-1}=i,a_k=j]
$$
翻转求和符号：
$$
Ans=\sum^n_{j=1}\sum^n_{i=1} i \times (n-i+1) \times [i=a_j]+ \sum^n_{k=2} \sum^n_{i=1}\sum^n_{j=1} \min(i,j) \times (n-\max(i,j)+1) \times [a_{k-1}=i,a_k=j]
$$
然后会发现除了最外层的之外内层求和符号都只有一个取值能够使内部非 $0$，整理一下最终得到：
$$
Ans=\sum^n_{i=1} a_i \times (n-a_i+1) + \sum^n_{i=2} \min(a_{i-1},a_{i}) \times (n-\max(a_{i-1},a_{i})+1)
$$
然后就发现可以 $O(n)$ 时间，$O(1)$ 空间的求这玩意。

代码：

```c++
#include <cstdio>
int n; long long last,x,ans;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++,last=x)
	{
		scanf("%lld",&x);
		ans+=x*(n-x+1);
		if(i) ans-=(last<x?last:x)*(n+1-(last>x?last:x));
	}
	printf("%lld",ans);
}
```



---

## 作者：hexu2010 (赞：1)

# CF1151E 题解

## 【题目大意】

给定一个有 $n$ 个顶点的链式图，编号 $1\sim n$，且 $i$ 号节点的权值为 $a_i$. 对所有 $1\leqslant i<n$，编号 $i$ 和 $i+1$ 的点之间连有一条边.

定义函数 $f(l,r)(l\leqslant r)$ 为删除权值范围不在 $l$ 到 $r$ 之间的点（某端为消失点的边也消失）后新图的连通块数量.

求 $\sum_{i=1}^n\sum_{j=i}^nf(i,j)$ 的值。

## 【分析】

注意到此题中的图为一条链，并且求连通块数量，不难想到利用“连通块数量 = 点数 - 边数”$^{(1)}$将原式转化为分别求点数和与边数和之差。（值得注意的是，这个公式只有在森林或树的情况下才成立）我们分别考虑每个点对答案的贡献。根据题意可得，权值为 $a_i$ 的点只有 $l\leqslant a_i$ 且 $a_i\leqslant r$ 时才会做出贡献，而隐藏条件 $1\leqslant l,r\leqslant n$ 可知，该点会做出 $a_i\times(n-a_i+1)$ 次贡献。因此，点数之和为 $\sum_{i=1}^na_i(n-a_i+1)$。边数之和也是如此，两端权值分别为 $a_i$ 和 $a_{i+1}$ 的边做出贡献时需要满足 $l\leqslant a_i\leqslant r$ 且 $l\leqslant a_{i+1}\leqslant r$，也就是 $l\leqslant\min(a_i,a_{i+1})$ 以及 $r\geqslant \max(a_i,a_{i+1})$，所以该边会被计算 $\min(a_i,a_{i+1})\times(n-\max(a_i,a_{i+1})+1)$ 次。所以这题就做完了。

## 【代码】

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int s = 0, w = 1;
	char ch = getchar();
	for(; ch < '0' || ch > '9'; w *= ch == '-' ? -1 : 1, ch = getchar());
	for(; ch >= '0' && ch <= '9'; s = 10 * s + ch - '0', ch = getchar());
	return s * w;
}
const int MAXN = 100005;
int n, a[MAXN];
signed main(){
	n = read();
	for(int i = 1; i <= n; i++){
		a[i] = read();
	}
	int res = 0;
	for(int i = 1; i <= n; i++){
		res += a[i] * (n - a[i] + 1);
	}
	for(int i = 1; i < n; i++){
		res -= min(a[i], a[i + 1]) * (n - max(a[i], a[i + 1]) + 1);
	}
	cout << res << endl;
	return 0;
}
```



---

## 作者：E1_de5truct0r (赞：1)

## 思路

这道题不知道为啥只开到 $10^5$，明明轻松 $O(n)$ 做。

对于一个给定的 $[l,r]$，显然联通块个数可以转化为：

$$\sum_{i=1}^{n}[l \leq a_i \leq r] -\sum_{i=1}^{n}[l \leq a_i,a_{i+1} \leq r]$$

即所有位于这个区间的数的个数，减去会断开的部分。

发现这个东西其实可以对每个数维护一个 $[l,r]$ 的组合数量：如果当前为 $x$，则为 $x \times (n-x+1)$。

而我们也可以对每两个相邻的数进行维护。如果为 $x,y$，则答案为：$\min(x,y) \times (n-\max(x,y)+1)$。

于是分别统计贡献即可。复杂度 $O(n)$。

后话：其实这道题也可以支持带修，我们模拟赛的题就是这道题的带修版本。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int n,ans1=0,ans2=0;
int a[200010];
void calc1(int x){ans1+=a[x]*(n-a[x]+1);} // 记录每个数的贡献
void calc2(int x){ans2+=min(a[x],a[x-1])*(n-max(a[x],a[x-1])+1);} // 记录相邻两个数的贡献

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) calc1(i);
	for(int i=2;i<=n;i++) calc2(i);
	cout<<ans1-ans2;
	return 0;
}

```

---

## 作者：_Clown_ (赞：1)

[更好的阅读体验！](https://www.cnblogs.com/Xsmyy/p/13553191.html)
$$\huge\mathcal{Solution}$$
~~简单题！~~

首先，我们需要将**连通块个数**转换成**点数减边数**

然后，我们考虑每一个点对答案的贡献。

第$i$个点，它被录用，当且仅当$Left$≤$A_i$&$A_i$≤$Right$

所以，第$i$个点对答案的贡献是$A_i(N-A_i+1)$

同理，我们可以算出每一条边的贡献。

减一减就好了呀！
$$\huge\mathcal{Code}$$
```cpp
#include<bits/stdc++.h>
using namespace std;
int TotalPoint;
int Array[100001];
int main(void)
{
	register int i;
	cin>>TotalPoint;
	register long long Ans;
	Ans=0;
	for(i=1;i<=TotalPoint;i++)
	{
		cin>>Array[i];
		Ans+=1LL*Array[i]*(TotalPoint-Array[i]+1);
	}
	for(i=1;i<TotalPoint;i++)
	{
		Ans-=1LL*min(Array[i],Array[i+1])*(TotalPoint-max(Array[i],Array[i+1])+1);
	}
	cout<<Ans<<endl;
	return 0;
}

```

---

## 作者：快斗游鹿 (赞：0)

## 思路

因为是一条链，所以连通块数等于点数减去边数，总答案等价于总点数减去总边数，所以点数边数可以分开统计。

若一个点的点权为 $a_i$，则在 $l\le a_i\le r$ 时，它会被统计。根据乘法原理，一共有 $a_i\times(n-a_i+1)$ 次。

若一条边两个端点点权分别为 $a_i,b_i(a_i<b_i)$，则当 $l\le a_i,b_i \le r$ 时，它会被统计。同理，一共有 $a_i\times(n-b_i+1)$ 次。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,a[N];
long long ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),ans=ans+1ll*a[i]*(n-a[i]+1);
	for(int i=1;i<n;i++){
		int mi=min(a[i],a[i+1]);
		int mx=max(a[i],a[i+1]);
		ans=ans-1ll*mi*(n-mx+1);
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：TernaryTree (赞：0)

首先链森林的连通块数量为点数减去边数，即 $v-e$。

将 $v$ 与 $e$ 分开拆贡献计算。

对于前者，当且仅当 $l\le a_i\le r$ 时 $a_i$ 对答案有贡献，即答案为 $\sum\limits_{i=1}^n (n-a_i+1)a_i$。

对于后者，当且仅当 $l\le a_{i},a_{i+1}\le r$，即 $l\le \min(a_{i},a_{i+1})$ 且 $ \max(a_{i},a_{i+1})\le r$ 时对答案有贡献，答案为 $\sum\limits_{i=1}^{n-1}(n-\max(a_i,a_{i+1})+1)(\min(a_{i},a_{i+1}))$。两者相减即可。

---

## 作者：cppcppcpp3 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1151E)。

## Solution

其实和[这道题](https://www.luogu.com.cn/problem/AT_abc173_f)并没有太大区别，一个在链上，一个在树上，但要求的答案都是 $\sum
\limits_{l=1}^{n}\sum\limits_{r=l}^{n} f(l,r)$，统计权值区间内连通块的数量。

这两道题的共同思路是：因为不方便直接统计连通块的数量，我们可以**找其中一个特殊位置的点代表一个连通块**。进而连通块的数量被转换成了所有特殊点的贡献之和。因此，就可以对每个点计算它在多少个区间里做出了 $1$ 的贡献。

在本题中，不妨以连通块最右边的点作为特殊点。为了做到不重不漏，下面讨论点 $u$（$1 \le u \le n-1$） 有贡献的条件：

- $a_u=a_{u+1}$，显然这时 $u$ 总会与 $u+1$ 在同一连通块内，又 $u+1>u$，所以 $u$ 的贡献为 $0$。

- $a_u<a_{u+1}$，此时区间右端点 $R$ 应满足 $a_u \le R \le a_{u+1}-1$（小于 $a_u$ 则 $u$ 不在连通块内， 大于等于 $a_{u+1}$ 则 $u+1$ 也在块内）；左端点 $L \in [1,a_u]$。贡献为 $a_u \times (a_{u+1}-a_u)$。

- $a_u>a_{u+1}$，此时 $a_{u+1}+1\le L \le a_u$，$a_u \le R \le n$，贡献为 $(n-a_u+1)(a_u-a_{u+1})$。

此外，点 $n$ 的贡献为 $a_n(n-a_n+1)$。全部加起来即可。复杂度 $O(n)$。

代码很短。

```cpp
int n,ans,a[100005];

main(){
	n=wrd();
	for(int i=1;i<=n;++i) a[i]=wrd();
	for(int i=1;i<=n;++i){
		if(i==n) ans+=a[n]*(n-a[n]+1);
		else if(a[i]==a[i+1]) continue;
		else if(a[i]<a[i+1]) ans+=(a[i+1]-a[i])*a[i];
		else ans+=(a[i]-a[i+1])*(n-a[i]+1);
	}
	return printf("%lld",ans),0;
}
```

其实个人感觉另一道题更难一点。

---

## 作者：xfrvq (赞：0)

因为是链，考虑转连通块个数为点数减边数。

于是分开数，一个点 $i$ 的次数就是 $(n-a_i+1)\times a_i$，一条边 $i\to i+1$ 的次数就是 $(n-\max\{a_i,a_{i+1}\}+1)\times\min\{a_i,a_{i+1}\}$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n,a[N];
long long c1,c2;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;++i) scanf("%d",a + i);
	for(int i = 1;i <= n;++i) c1 += 1LL * (n - a[i] + 1) * a[i];
	for(int i = 1;i < n;++i) c2 += 1LL * (n - max(a[i],a[i + 1]) + 1) * min(a[i],a[i + 1]);
	printf("%lld\n",c1 - c2);
	return 0;
}
```

---

## 作者：lg_zhou (赞：0)

这题的其他题解好像都是一个做法..... 做完一看题解才发现我的思路和题解全不相同。

我们考虑每加进来一个权值的所有点会新产生多少连通块。对于算到权值 $i$ 时，假设它对应着编号为 $j_1,j_2$ 两个点。

加进来点 $j_1$ 时，先假设它会对 $[st,i],st \in [1,i]$ 这 $i$ 段权值区间都产生 $1$ 的贡献，假如点 $j_1-1$ 的权值小于 $i$，权值为 $m$，那么对于 $st\in [1,m]$ 的所有区间 $[st,i]$，是不会产生贡献的（和原来连上了），将其减掉。$j_1+1$ 同理。

加进来点 $j_2$ 时，和 $j_1$ 同理，只不过要注意他还有可能和 $j_1$ 连通。

代码：

```cpp
#include<iostream>
#include<vector>
using namespace std;
const int maxn = 1e5+5;
vector<int> v[maxn];
long long f[maxn],pos[maxn];
int main(){
//	freopen("a.in","r",stdin);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++){
		int t;
		cin >> t;
		v[t].push_back(i);		
	}
	for (int i = 1; i <= n; i++){
		f[i] = f[i-1];
		for (int j = 0; j < v[i].size(); j++){
			int p = v[i][j];
			f[i] += i; //先加上 i 的贡献
			if (pos[p-1]) f[i] -= pos[p-1]; // 这之前就不会产生贡献了
			if (pos[p+1]) f[i] -= pos[p+1];
			pos[p] = i;
		}
	}

	long long ans = 0;
	for (int i = 1; i <= n; i++){
		ans += f[i];
	}
	cout << ans << endl;
	return 0;
} 
```


---

## 作者：thostever (赞：0)

~~虽然思路跟别人相同，但我觉得我讲的清楚一点~~

考虑递推。

我们只考虑前 $i$ 个数，答案为 $\sum_{l=1}^i\sum_{r=l}^i f(l,r)$。

现在我们加入一个数：$a_{i+1}$。那么对于所有 $f(l,r)$ 来说，有哪些可以产生贡献呢？即加入 $a_{i+1}$ 后哪些 $f(l,r)$ 的连通块数量会增加。

对于 $f(l,r)$ 来说，如果连通块个数增加，当且仅当 $a_{i+1}$ 独自构成了一个新的连通块。即 $l\leq a_{i+1}\leq r$ 且（ $a_i<l$ 或 $r<a_i$ ）。

那么所有包含 $a_{i+1}$ 且不包含 $a_i$ 的 $f(l,r)$ 的数量，便是答案增加的量。

分别考虑 $a_i>a_{i+1}$ 和 $a_i<a_{i+1}$ 两种情况。

若 $a_i>a_{i+1}$，则增加 $(a_i-a_{i+1})\times a_{i+1}$。

若 $a_i<a_{i+1}$，则增加 $(a_{i+1}-a_i)\times(n-a_{i+1}+1)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[100010];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i-1]>a[i]) ans+=(a[i-1]-a[i])*a[i];
		if(a[i-1]<a[i]) ans+=(a[i]-a[i-1])*(n-a[i]+1);
	}
	cout<<ans<<"\n";
}
/*

*/
```


---

## 作者：苏幕寒 (赞：0)

本蒟蒻讲下这题怎么做，首先如果打暴力的话是只有60分；

接下来，我讲讲从隔壁大佬那学来的正解：

考虑每个点对答案的贡献，我们认为一个连通块里让编号最大的点

产生贡献，对于点 i，要产生贡献就一定要这个点存在，而点 i+1不

存在而点n只用包含这个点就行了

具体是这样的：

当 a i>a i+1 贡献=（a i-a i+1)*(n-a i+1)

当 a i<a i+1 贡献=(a i+1-a i)*a i;

具体代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long ans;
long long a[1000005];
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<n;i++)
    {
        int x=a[i],y=a[i+1];
        if(x>y)
        {
            ans=(long long)ans+(x-y)*(n-x+1);
        }
        else
        {
            ans=ans+(long long)(y-x)*x;
        }
    }
    ans+=(long long)a[n]*(n-a[n]+1);
    cout<<ans;
    return 0;
}
```


---

