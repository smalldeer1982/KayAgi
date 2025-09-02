# [USACO21DEC]  Convoluted Intervals S

## 题目描述

奶牛们正在努力尝试发明有趣的新游戏来玩。他们目前的工作之一与一组 $N$ 个区间（$1\le N\le 2\cdot 10^5$）有关，其中第 $i$ 个区间从数轴上的 $a_i$ 位置开始，并在位置 $b_i \geq a_i$ 结束。$a_i$ 和 $b_i$ 均为 $0 \ldots M$ 范围内的整数，其中 $1 \leq M \leq 5000$。

这个游戏的玩法是，Bessie 选择某个区间（假设是第 $i$ 个区间），而她的表妹 Elsie 选择某个区间（假设是第 $j$ 个区间，可能与 Bessie 所选的的区间相同）。给定某个值 $k$，如果 $a_i + a_j \leq k \leq b_i + b_j$，则她们获胜。

对范围 $0 \ldots 2M$ 内的每个值 $k$，请计算使得 Bessie 和 Elsie 可以赢得游戏的有序对 $(i,j)$ 的数量。

## 说明/提示

【样例解释】

在这个例子中，对于 $k=3$，有三个有序对可以使得 Bessie 和 Elsie 获胜：$(1, 1)$，$(1, 2)$，和 $(2, 1)$。

【数据范围】

- 测试点 1-2 满足 $N\le 100, M\le 100$。
- 测试点 3-5 满足 $N\le 5000$。
- 测试点 6-20 没有额外限制。

## 样例 #1

### 输入

```
2 5
1 3
2 5```

### 输出

```
0
0
1
3
4
4
4
3
3
1
1
```

# 题解

## 作者：xkcdjerry (赞：16)

首先考虑显然做法：可以枚举 $a_i+a_j$ 和 $b_i+b_j$，那么显然每对 $i,j$ 之间的 $k$ 均可以通过此对 $i,j$ 取胜，则可以说 $i,j$ 对 $a_i+a_j$ 到 $b_i+b_j$ 这个区间的所有 $k$ 的答案**贡献**了 $1$。由于是区间加单点查询可以考虑使用差分数组维护。总复杂度为 $O(n^2)$。  

这里发现 $n$ 非常大但是值域 $m$ 很小，可以开桶维护。

令 $fa_x$ 为 $a_i=x$ 的数目，$fb_x$ 为 $b_i=x$ 的数目，那么由于前缀和的原理可以分别处理所有 $a_i+a_j$ 和所有 $b_i+b_j$。


对于 $a$ 数组，由于对于任意 $x,y$ 都有 `fa[x]` 个不同的 $i$ 使得 $a_i=x$，`fa[y]` 个 $j$ 使得 $a_j=y$，那么对 $x+y$ 产生的总贡献就是 $fa_x \times fa_y$。

$b$ 数组同理，记得因为前缀和的原理所以贡献要加在 $x+y+1$ 的位置上。

最后把差分数组做前缀和即可得到答案。

```c++
#include <cstdio>
#define M 5010
#define N 200010
long long f[2*M];
long long fa[M],fb[M];
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        fa[a]++;
        fb[b]++;
    }
    for(int i=0;i<=m;i++)
        for(int j=0;j<=m;j++)
        {
            f[i+j]+=fa[i]*fa[j];
            f[i+j+1]-=fb[i]*fb[j];
        }
    long long ans=0;
    for(int i=0;i<=2*m;i++)
        printf("%lld\n",ans+=f[i]);
}
```

**特别提醒：一定要么[全部开 `long long`](https://www.luogu.com.cn/record/66182081)；要么 `f` 和 `ans` 开 `long long`，[`fa` 和 `fb` 乘的时候转 `long long`](https://www.luogu.com.cn/record/66182113)，否则会收获 [95 分](https://www.luogu.com.cn/record/66182075)的好成绩！！！**

---

## 作者：shiranui (赞：8)

## 题目大意
给你 $N$ 个区间，对于每个 $k$ $( 0≤k≤2M )$，输出满足条件的区间组数。

当两个区间的 **开头之和** $≤k≤$ **结尾之和**，那么这两个区间在当前 $k$ 时满足条件。

## 思路
我们拿样例来说。

```cpp
2 5
1 3
2 5
```

开数组 $a$ 存每个区间的开头，数组 $b$ 存每个区间的结尾。

得到：

```cpp
a[1] = 1
a[2] = 1

b[3] = 1
b[5] = 1
```
开数组 $ha$，$hb$。$ha[i] = j$ 表示两个区间开头之和为 $i$ 有 $j$ 种选择方法，$hb[i]=j$ 表示两个区间结尾之和为 $i$ 有 $j$ 种选择方法。

可得：

```cpp
ha[2]  = 1 : (1,1)
ha[3]  = 2 : (1,2) & (2,1)
ha[4]  = 1 : (2,2)

hb[6]  = 1 : (3,3)
hb[8]  = 2 : (3,5) & (5,3)
hb[10] = 1 : (5,5)
```
使用查分的思想得到差分数组 $f$，然后统计一下输出即可。

$f$ :

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
0| 0 | +1 | +2 | +1 | 0 | 0 | -1 | 0 | -2 | 0 | -1 |  |


$ans$：

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 0 | 0 | 1 | 3 | 4 | 4 | 4 | 3 | 3 | 1 | 1 |

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[200010],b[200010];
long long ha[5010],hb[5010];
long long f[100010],ans[100010];
int main ()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
	for(int i=1;i<=n;i++)ha[a[i]]++,hb[b[i]]++;
	for(int i=0;i<=m;i++)
		for(int j=0;j<=m;j++)
			if(ha[i]!=0&&ha[j]!=0)f[i+j]+=ha[i]*ha[j];
	for(int i=0;i<=m;i++)
		for(int j=0;j<=m;j++)
			if(hb[i]!=0&&hb[j]!=0)f[i+j+1]-=hb[i]*hb[j];
	ans[0]=f[0];
	for(int i=1;i<=2*m;i++)ans[i]=ans[i-1]+f[i];
	for(int i=0;i<=2*m;i++)cout<<ans[i]<<endl;
	return 0;
}
```



---

## 作者：Skyjoy (赞：5)

一些牢骚：由于本人由于各种原因并没有时间打 USACO ，所以考后花了一些时间做题，结果发现这次银组题好难，要是这次来打了还不一定能晋级（（（

# 思路

首先，这道题要求我们对于每一个 $k$ 都要回答一次，这其实说明了我们要**预处理出所有答案**。

由于这道题给我们的不等式成两面包夹之势，所以我们先不妨**从左边的不等式入手**。我们对于 1 到 $m$ 中每一个值都记录 $a,b$ 数组的出现次数，可以得到 $cnta$ 和 $cntb$ 。假设满足 $a_i+a_j=k$ 的 $(i,j)$ 组数是 $sum_k$ ，则有：

$$sum_k=\sum_{i=1}^{k-1}cnta_i\times cnta_{k-i}$$

容易发现，答案就是 $sum$ 数组的前缀和。即：

$$ans_k=\sum_{i=1}^{k}\sum_{j=1}^{i-1}cnta_j\times cnta_{i-j}$$

此时我们要开始考虑加入右边的不等式了。我们需要去掉一些不符合要求的情况。此时我们可以列出式子：

$$ans_k=\sum_{i=1}^{k}(\sum_{j=1}^{i-1}cnta_j\times cnta_{i-j})-\sum_{i=1}^{k-1}\sum_{j=1}^{i-1}cntb_j\times cntb_{i-j}$$

因为 $a_i\leq b_i$ 恒成立，所以当 $b_i+b_j<k$ 时必然有 $a_i+a_j<k$ ，所以这个式子是正确的。

因为我们需要用 $sum$ 的前缀和求出 $ans$ ，所以我们需要逆推回 $sum$ 的式子，如下：

$$sum_k=\sum_{i=1}^{k-1}cnta_i\times cnta_{k-i}-\sum_{i=1}^{k-2}cntb_i\times cntb_{k-i-1}$$

然后我们就完美地解决此题了！复杂度为 $O(n+m^2)$ ，可以通过！

# 代码

（非常简短）

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=200010;
const int M=10010;
ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
ll n,m,a,b,cnta[M],cntb[M],sum[M];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a=read(),b=read();
		cnta[a]++,cntb[b]++;
	}
	for(int i=0;i<=m;i++)for(int j=0;j<=m;j++)sum[i+j]+=1ll*cnta[i]*cnta[j],sum[i+j+1]-=1ll*cntb[i]*cntb[j];
	for(int i=1;i<=2*m;i++)sum[i]+=sum[i-1];
	for(int i=0;i<=2*m;i++)printf("%lld\n",sum[i]);
	return 0;
}
```

2022年要来了，祝各位 OIer 们在新的一年里心想事成，变得更强！

---

## 作者：I_am_Accepted (赞：5)

我们先将 $a,b$ 的值分别开桶 $ta,tb$。

由于 $M\leqslant5000$，我们 $O(M^2)$ 枚举 $ta$ 的某对值 $(x,y)$，将 $ans[x+y]+=ta[x]\times ta[y]$，表示不比 $x+y$ 小的 $k$ 可取的区间对(pair)增加了这么多。

再 $O(M^2)$ 枚举 $tb$ 的某对值 $(x,y)$，将 $ans[x+y+1]-=tb[x]\times tb[y]$，表示比 $x+y$ 大的 $k$ 可取的区间对（pair）减少了这么多。

发现我们维护的 $ans$ 是一个差分序列，$O(M)$ 还原序列后输出即可。

代码就不贴了~~太简单了~~。

---

## 作者：Ginger_he (赞：5)

# 题解
**反向考虑**，枚举任意两个区间 $i$ 和 $j$，则 $\forall k\in[a_i+a_j,b_i+b_j]$ 多一种方案，可以使用**差分**实现。  
注意到 $m$ 的值不大，可以用**桶**将所有 $a$ 和 $b$ 存起来。又因为 $a$ 和 $b$ 可以分开处理，与顺序无关，所以可以用**加乘原理**优化。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
int n,m,x,y;
ll a[maxn],b[maxn],p[maxn],s;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		a[x]++,b[y]++;//桶
	}
	for(int i=0;i<=m;i++)
	{
		for(int j=0;j<=m;j++)
		{
			p[i+j]+=a[i]*a[j];//≥i+j
			p[i+j+1]-=b[i]*b[j];//>i+j
		}//差分&加乘原理
	}
	for(int i=0;i<=m*2;i++)
		printf("%lld\n",s+=p[i]);
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：3)

## 写在前面的话

本题过于~~简单~~，但是要求掌握差分（要开长整型）。

## $10pts$ 的做法

直接暴力枚举每个 $k$，然后再花 $O(n^2)$ 的时间来枚举两个区间。

然后，你就可以得到 $10pts$ 的好成绩。

代码：[这里](https://www.luogu.com.cn/paste/l82vidp8)。

## $25pts$ 的做法

还是枚举两个区间，我们发现一组区间只有可能对答案 $a_i + a_j$ 到 $b_i + b_j$ 之间的 $k$ 做出贡献，所以此时可以用差分来维护答案序列，时间就是 $O(n^2)$，而不需要判断多余的 $k$，可以获得 $25pts$。

代码：[这里](https://www.luogu.com.cn/paste/akp9ijel)。

## $100pts$ 的做法

我们可以发现，对于我们做的差分操作，是可以**分开**进行的。然后我们又发现，$n$ 很大，$m$ 却很小，这说明在差分数组的一个地方**可能**会有很多次相加，所以考虑将这么多次相加变成一次相加。

我们可以思考，为什么要枚举两个区间呢？枚举这两个区间的左端点和右端点不好吗（在此指的是值）？所以，我们可以用双重循环来枚举两个区间的**端点**，注意，左端点和右端点可以同时枚举，但枚举的不是同一个区间的端点。此时我们发现，根据加乘原理，在枚举端点的值为 $i$ 和 $j$ 的情况下，我们差分数组加的应该是左端点为 $i$ 的个数 $\times$ 左端点为 $j$ 的个数（非常简单，在此不做解释），而右端点呢，也是一样。那么，如何统计端点为 $i$ 的个数呢？很简单，用个桶就行了。

实现方法：

在此设差分数组为 $d$。

设立数组 $ca$ 和 $cb$，分别表示记录左端点和右端点的出现次数。然后枚举 $i$ 和 $j$，在此指的是值。将 $d_{i + j} + (ca_i \times ca_j)$，指的是左端点，将 $d_{i + j + 1} - (cb_i \times cb_j)$，指的是右端点。然后对 $d$ 求前缀和即可。

代码：[这里](https://www.luogu.com.cn/paste/ry4ack5a)。

## 最后的话

为什么要开长整型？因为 $n$ 有 $10^5$ 这么大，然而一个 $k$ 可能会有 $n^2$ 这么大，所以要开长整型。

最后！拒绝抄袭题解，共创美好洛谷。

---

## 作者：lnwhl (赞：1)

## 思路
正向穷举每个 $k$ 的答案比较难，但我们可以**反向穷举**每对 $(a_{i},b_{i})$ 对哪些 $k$ 的答案有贡献。

对于任意两个区间 $i$，$j$，它对 $[a_{i}+a_{j},b_{i}+b_{j}]$ 区间内的所有 $k$ 都有 $1$ 的贡献。我们可以通过**差分**来实现。复杂度 $O(n^2)$。可以通过 $n\le5000$ 的情况。

我们再进一步思考，不难发现 $m$ 的值不大。所以我们可以用一个**桶**把 $a$ 数组和 $b$ 数组存起来，分别计算以当前 $i$，$j$ 开始和结束的贡献。还是通过**差分维护，用乘法原理计算贡献**，就可以通过本题了。时间复杂度 $O(m^2)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long //记得开long long 
int n,m;
ll a[100005],b[100005],cf[100005],sum=0;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int x,y;cin>>x>>y;
		a[x]++;b[y]++;//桶 
	}
	for(int i=0;i<=m;i++)
	{
		for(int j=0;j<=m;j++)
		{
			cf[i+j]+=a[i]*a[j];//以当前i，j开始的贡献 
			cf[i+j+1]-=b[i]*b[j];//以当前i，j结束的的贡献，注意要在下一位减 
		}//差分
	}
	for(int i=0;i<=m+m;i++)
	{
		sum+=cf[i];//前缀和 
		cout<<sum<<endl;
	}
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：1)

模拟赛考到了，这道题是最后一道就没看，但是没想到难度倒序，导致我一道题都没做出来。。。

觉得现有题解并不是很详细，仔细讲讲。

# 题目大意

给定 $n$ 个区间，第 $i$ 个区间起点为 $st_i$，终点为 $ed_i$。

对于值 $k(k\in [0,2\times m])$，找到有序对 $(i,j)$ 满足 $st_i+st_j\le ed_i+ed_j$ 的个数。 

$1\le n\le 2\times 10^5,1\le m \le 5000,st_i,ed_i\in[1,m]$。

# 题目分析

$\rm Subtask~1$：满足 $1\le n\le 100$。

此时直接 $\mathcal{O(mn^2)}$ 暴力即可。

$\rm Subtask~2$：满足 $1\le n\le 5000$。

考虑每个区间会对哪些点会产生贡献，显然 $[st_i,ed_i]$ 和 $[st_j,ed_j]$ 会对点 $st_i+st_j,st_i+st_j+1,\dots,ed_i+ed_j$ 做贡献 $1$。那么我们用差分搞一搞就出来了。

时间复杂度 $\mathcal{O(n^2)}$。

$\rm Subtask~3$：

枚举 $n$ 走不通了，起步 $n^2$，我们转而开始考虑利用 $m$。

看到 $st_i+st_j,ed_i+ed_j$，难道只能枚举 $n$ 吗？不是的，$st_i,ed_i\in[1,m]$，所以我们可以双重循环枚举 $m$，用 $i+j$ 来表示 $st_i+st_j,ed_i+ed_j$！！！

注意到 $m$ 范围很小，于是拿两个桶 $tonga,tongb$ 来记录 $st_i,ed_i$ 的出现次数。

首先 $sub[i+j]$ 加上 $tonga_i\times tonga_j$，表示增加了大于等于 $i+j$ 的 $k$ 可以选择的区间数，再将 $sub[i+j+1]$ 减去 $tongb_i\times tongb_j$，表示减少了比 $i+j$ 大的 $k$ 可以选择的区间数。

$sub$ 是个差分序列，前缀和即为答案。

时间复杂度 $\mathcal{O(m^2)}$

# 代码

```cpp
//2022/2/16
//2022/2/17
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <algorithm>
#define int long long
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	while (x < 0) x += mod;
	while (x >= mod) x -= mod;
	return x;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int ma = 1e5 + 5;
int tonga[ma],tongb[ma],sub[ma];
int n,m;

#undef int
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
    #define int long long
	n = read(),m = read();
	for (register int i = 1;i <= n; ++ i) {
		int x = read(),y = read();
		tonga[x] ++,tongb[y] ++;
	}
	for (register int i = 0;i <= m; ++ i) {
		for (register int j = 0;j <= m; ++ j) {
			sub[i + j] += tonga[i] * tonga[j];
			sub[i + j + 1] -= tongb[i] * tongb[j];
		}
	}
	int sum = 0;
	for (register int i = 0;i <= 2 * m; ++ i) {
		sum += sub[i];
		printf("%lld\n",sum);
	}

	return 0;
}
```

---

## 作者：_Imaginary_ (赞：1)

## Problem

有一些区间，用其中两个的左端点相加，右端点相加组成一些新的区间，求每个数载新区间中出现的次数。

## Solution

看上去能 $\Theta(m^2)$。

首先，我们把每个区间按照前缀和的方式拆解。

其次，我们统计这些区间中各个数的出现个数。

最后，我们分别枚举两个数，将这两个数出现的次数相乘，加到这两个数的和所对应的答案里即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod=1000000007;
const int N=200005,M=10005;
ll a[N],b[N];
ll ans1[M],ans2[M];
ll cnt[M];
int n,m;
void solve(ll a[N],ll ans[M])
{
	memset(cnt,0,sizeof(cnt));
	memset(ans,0,sizeof(ans));
	for(int i=1;i<=n;i++) cnt[a[i]]++;
	for(int i=0;i<=m;i++)
		for(int j=0;j<=m;j++)
			ans[i+j]+=cnt[i]*cnt[j];
	for(int i=2*m-1;i>=0;i--) ans[i]+=ans[i+1];
//	for(int i=0;i<=2*m-1;i++) printf("%lld ",ans[i]); printf("\n");
}
void solve2(ll a[N],ll ans[M])
{
	memset(cnt,0,sizeof(cnt));
	memset(ans,0,sizeof(ans));
	for(int i=1;i<=n;i++) cnt[a[i]]++;
	for(int i=0;i<=m;i++)
		for(int j=0;j<=m;j++)
			if(i||j) ans[i+j-1]+=cnt[i]*cnt[j];
	for(int i=2*m-1;i>=0;i--) ans[i]+=ans[i+1];
//	for(int i=0;i<=2*m-1;i++) printf("%lld ",ans[i]); printf("\n");
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i],&b[i]);
	}
	solve(b,ans1);
	solve2(a,ans2);
	for(int i=0;i<=2*m;i++) printf("%lld\n",ans1[i]-ans2[i]);
	return 0;
}
```

---

## 作者：jimmy2021 (赞：0)

首先，这道题可以先暴力一遍。

## 暴力算法1

可以先枚举 $0 \dots 2 \times M$ 内的所有数，再暴力枚举 $i$ 和 $j$（题目描述中的）， $O(1)$ 判断即可。时间复杂度：$\Theta (2 \times M \times N ^ 2)$ ，前 $2$ 个点到手~~（送分的）~~。

## 暴力算法2

观察题目式子：$a_i + a_j \leq k \leq b_i + b_j$，不难发现：如果给定 $i, j$ ，那么所有的 $k \in [a_i + a_j, b_i + b_j]$ 都合法，也就是说 假设答案数组为 $ans$，那么相当于给 $ans$ 数组中的一段区间 $[a_i + a_j, b_i + b_j]$ 全部加上了 $1$ ，可以用差分算法 $O(1)$ 来维护。时间复杂度： $\Theta (N ^ 2)$ ，前 $5$ 个点到手。

## 正解

观察数据范围： $N$ 是十万级别的， $O(N ^ 2)$ 过不了；但 $O(M ^ 2)$ 是可以过的。这就启发我们不用枚举 $i$ 和 $j$（数组中的下标），转而枚举 $a$ 数组和 $b$ 数组中下标为 $i$ 和 $j$ 的位置上的具体的值（假设枚举的两个数是 $x$ 和 $y$），那么相当于说差分数组（假设是 $d$ 数组）的第 $x + y$ 个位置加上 $a$ 数组中 $(x, y)$ 数对的数量，就是 $a$ 数组中 $x$ 的数量乘上 $a$ 数组中 $y$ 的数量（乘法原理）；然后 $d_{x + y + 1}$ 减去 $b$ 数组中 $x$ 的数量乘上 $b$ 数组中 $y$ 的数量即可。时间复杂度： $\Theta (M ^ 2)$

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <limits.h>
#include <cstring>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f, INF_BIT = 0x3f;

const int M = 5010;

int n, m;
int a, b;

LL cnta[M], cntb[M];

LL d[2 * M];

LL sum;

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1;i <= n;i++){
        scanf("%d%d", &a, &b);
        
        cnta[a]++, cntb[b]++;
    }
    
    for(int i = 0;i <= m;i++){
        for(int j = 0;j <= m;j++){
            d[i + j] += cnta[i] * cnta[j];
            d[i + j + 1] -= cntb[i] * cntb[j];
        }
    }
    
    for(int i = 0;i <= 2 * m;i++){
        sum += d[i];
        printf("%lld\n", sum);
    }
    return 0;
}
```

---

## 作者：tongziyu (赞：0)

## Description
给定 $n$ 个区间，第 $i$ 个区间的左端点为 $a_i$，右端点为 $b_i$。 

给定一个 $m$，求对于每个 $k$ $(0 \le k \le 2 \cdot m)$，满足 $a_i + a_j \le k \le b_i + b_j $ 的有序对 $(i,j)$ 的数量。


------------


## Solution

首先看数据范围，这题的 $n$ 可以达到 $2 \times 10^5$，暴力肯定是不行的。

接下来考虑题目给出的不等式。可以发现 $a_i + a_j$，$b_i + b_j \le 10^4$，而答案又只与 $a_i + a_j$ 和 $b_i + b_j$ 有关。

那么是不是可以将 $a_i + a_j$ 和 $b_i + b_j$ 取到每个值的数量统计出来，从而得出答案？

数据范围告诉我们，我们需要暴力。

首先开两个数组 $x$，$y$，$x_i$ 表示以 $i$ 为左端点的区间有多少个， $y_i$ 表示以 $i$ 为右端点的区间有多少个，一边读入一边统计。

再开两个数组 $ca$，$cb$。$ca_i$ 表示 $a_i + a_j = i$ 的组合的有序对 $(i,j)$ 的数量，$cb_i$ 表示 $b_i + b_j = i$ 的有序对 $(i,j)$ 的数量。然后枚举选取的两个区间的端点 $i$，$j$，可以发现以 $i$，$j$ 为左端点的区间组合数有 $x_i \cdot x_j$ 种，以 $i$，$j$为右端点的区间组合数有 $ y_i \cdot y_j$ 种。因此得到两个式子 $ca[i + j] = ca[i + j] + x[i] \cdot x[j]$，$cb[i + j] = cb[i + j] + y[i] \cdot y[j]$。

需要加而不是直接等于是因为 $i + j$ 这个数也可以变成 $(i - 1) + (j + 1)$ 等其它两个整数的相加结果。

已经算出了 $ca$ 和 $cb$ 数组，怎么得出答案？

题目要求的是对于数轴上的整数 $k$ $(0 \le k \le 2 \cdot m)$，满足 $a_i + a_j \le k$ 且 $b_i + b_j \ge k$ 的有序对 $(i,j)$ 数量，也就是满足 $a_i + a_j \le k$ 的有序对数量减去 $b_i + b_j \lt k$ 的有序对数量（由于 $a_i \le b_i$ 且 $a_j \le b_j$，所以如果 $b_i + b_j \lt k$，一定有 $a_i + a_j \lt k$）。

满足 $a_i + a_j \le k$ 的有序对数量，就是 $ca_0 + ca_1 + ...  + ca_k$ 的结果。而满足 $b_i + b_j \lt k$ 的有序对数量，就是 $cb_0 + cb_1 + ... + cb_{k-1}$ 的结果。

利用前缀和求解即可。


### 一点优化

可以利用差分的思想，直接开一个差分数组，不开 $ca$，$cb$ 数组，直接将 $ca$ 和 $cb$ 数组的计算反映到差分数组上，节省空间。

------------
## Code
有些地方写的跟题解中不太一样，可以结合题解自行理解。

### 前缀和写法：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
long long a[N], b[N];
long long ca[N], cb[N];
int n, m; 
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) 
	{
		int x, y;
		scanf("%d%d", &x, &y);
		++a[x], ++b[y];
	}
	for (int i = 0; i <= m; ++i) 
	{
		for (int j = 0; j <= m; ++j)
		{
			ca[i + j] += a[i] * a[j];
			cb[i + j] += b[i] * b[j];
 		}
	}
	printf("%lld\n", ca[0]);
	for (int i = 1; i <= (m << 1); ++i) 
	{
	    ca[i] += ca[i - 1];
	    cb[i] += cb[i - 1];
	    printf("%lld\n", ca[i] - cb[i - 1]);
	}
 } 
```
### 差分写法：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 10;
long long a[N], b[N];
long long cf[N << 1];
int n, m; 
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) 
	{
		int x, y;
		scanf("%d%d", &x, &y);
		++a[x], ++b[y];
	}
	for (int i = 0; i <= m; ++i) 
	{
		for (int j = 0; j <= m; ++j)
		{
			cf[i + j] += a[i] * a[j];
			cf[i + j + 1] -= b[i] * b[j];
 		}
	}
	long long ans = 0;
	for (int i = 0; i <= (m << 1); ++i) 
	{
		ans += cf[i];
		printf("%lld\n", ans);
	}
 } 
```




---

