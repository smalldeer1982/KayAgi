# Flipping Range

## 题目描述

You are given an array $ a $ of $ n $ integers and a set $ B $ of $ m $ positive integers such that $ 1 \leq b_i \leq \lfloor \frac{n}{2} \rfloor $ for $ 1\le i\le m $ , where $ b_i $ is the $ i $ -th element of $ B $ .

You can make the following operation on $ a $ :

1. Select some $ x $ such that $ x $ appears in $ B $ .
2. Select an interval from array $ a $ of size $ x $ and multiply by $ -1 $ every element in the interval. Formally, select $ l $ and $ r $ such that $ 1\leq l\leq r \leq n $ and $ r-l+1=x $ , then assign $ a_i:=-a_i $ for every $ i $ such that $ l\leq i\leq r $ .

Consider the following example, let $ a=[0,6,-2,1,-4,5] $ and $ B=\{1,2\} $ :

1. $ [0,6,-2,-1,4,5] $ is obtained after choosing size $ 2 $ and $ l=4 $ , $ r=5 $ .
2. $ [0,6,2,-1,4,5] $ is obtained after choosing size $ 1 $ and $ l=3 $ , $ r=3 $ .

Find the maximum $ \sum\limits_{i=1}^n {a_i} $ you can get after applying such operation any number of times (possibly zero).

## 说明/提示

In the first test, you can apply the operation $ x=1 $ , $ l=3 $ , $ r=3 $ , and the operation $ x=1 $ , $ l=5 $ , $ r=5 $ , then the array becomes $ [0, 6, 2, 1, 4, 5] $ .

In the second test, you can apply the operation $ x=2 $ , $ l=2 $ , $ r=3 $ , and the array becomes $ [1, 1, -1, -1, 1, -1, 1] $ , then apply the operation $ x=2 $ , $ l=3 $ , $ r=4 $ , and the array becomes $ [1, 1, 1, 1, 1, -1, 1] $ . There is no way to achieve a sum bigger than $ 5 $ .

## 样例 #1

### 输入

```
3
6 2
0 6 -2 1 -4 5
1 2
7 1
1 -1 1 -1 1 -1 1
2
5 1
-1000000000 -1000000000 -1000000000 -1000000000 -1000000000
1```

### 输出

```
18
5
5000000000```

# 题解

## 作者：CSP_Sept (赞：19)

是我 idea 弱化版 /fn

![](https://cdn.luogu.com.cn/upload/image_hosting/j0gpqofq.png)

（以下内容除了 Hint 选自官方 [Editorial](https://codeforces.com/blog/entry/99384) 帮助理解外，其他均为原创。）

### 视频讲解

![](bilibili:BV1BT4y1k72Q)

### 大意

给定长度为 $n$ 的数列 $a$ 和含有 $m$ 个元素的集合 $B$，其中 $1\le B_i\le \left\lfloor\frac{n}2\right\rfloor$。

你可以进行无限次操作，每次操作：

1. 选择一个 $x$ 和一个区间 $[l,r]$，其中有 $x\in B,1\le l\le r\le n$ 且 $r-l+1=x$。
2. 把所有 $i\in [l,r]$ 的 $a_i$ 变成 $-a_i$。

求操作后 $\sum a_i$ 的最大值。

### Hint 1

最短的可操作区间长度是多少？

### Hint 2

构造长度为 $n$ 的 01 串 $s$，$s_i=0$ 则说明 $a_i$ 会被乘上 $-1$，$s_i=1$ 则反之。什么样的 $s$ 是可以实现的？（下标从 $0$ 开始）

### 解法

以下我们把「选择区间 $[l,r]$ 进行操作」记作「$q(l,r)$」，把「使长度为 $len$ 的一个区间中的所有数变成它的相反数」记作「$p(len)$」。

如果我们有 $x,y\in B$（不妨设 $x>y$），因为 $B$ 的所有元素至多是 $\left\lfloor\frac{n}2\right\rfloor$，所以我们可以实现任意一个 $p(x-y)$，方法如下：

1. 依次进行 $q(k+1,k+x),q(k+x-y+1,k+x)$，即可实现，其中 $k$ 是我们要实现的长度为 $x-y$ 的区间的左端点。
2. 依次进行 $q(k-x+1,k),q(k-x+1,k-x+y)$，即可实现，其中 $k$ 是我们要实现的长度为 $x-y$ 的区间的右端点。

于是我们可以直接把 $x-y$ 弹进 $B'$（即 $B$ 的扩充集合），运用辗转相除法可以得到 $\gcd(x,y)\in B'$。

令 $g=\gcd(B_1,B_2,\ldots,B_m)$，运用上面的证明得到以下性质：

- $g$ 是 $B'$ 中的最小元素。
- $g\mid B_i$，即所有 $p(B'_i)$ 都可以通过若干次 $p(g)$ 实现。

于是问题转化为：

> 进行任意次 $p(g)$，最大化 $\sum a_i$。

考虑「Hint 2」的定义，$s$ 初始为全 0 串，每个 $p(g)$ 都 01 翻转了 $s$ 的一个长度为 $g$ 的区间。

我们定义 $f_x(0\le x< g)$ 表示所有 $i\bmod g=x$ 的 $s_i$ 的异或和，注意到任意一次操作后所有 $f_x$ 都会变化。

所以只有使所有 $f_x$ 都相等的 $s$ 是可以实现的。

于是可以考虑 dp。

设 $dp(i,j)$ 表示 $a_i+a_{i+g}+a_{i+2\cdot g}+\cdots+a_{i+k\cdot g}$ 的最大值，其中 $f_i\oplus f_{i+g}\oplus f_{i+2\cdot g}\oplus\cdots\oplus f_{i+k\cdot g}=j$。

考虑答案，显然是
$$
\max\left\{\sum\limits_{i=0}^{g-1}dp(i,0),\sum\limits_{i=0}^{g-1}dp(i,1)\right\}
$$


时间复杂度 $O(n)$。

### 核心代码

```cpp
for(int i = 0 ; i < m ; i++)
	g = gcd(g, b[i]);
for(int i = 0 ; i < g ; i++)
	dp[i][0] = 0, dp[i][1] = -3e9;
for(int i = 0 ; i < n ; i++){
	ll x1 = dp[i % g][0], x2 = dp[i % g][1];
	dp[i % g][0] = max(x1 + a[i], x2 - a[i]);
	dp[i % g][1] = max(x2 + a[i], x1 - a[i]);
}
sum1 = sum2 = 0;
for(int i = 0 ; i < g ; i++)
	sum1 += dp[i][0], sum2 += dp[i][1];
printf("%lld\n", max(sum1, sum2));
```

[完整版本（$\textit{144625983}$）](https://codeforces.com/contest/1630/submission/144625983)

---

## 作者：Tyyyyyy (赞：11)

## CF1630D

### 题意简述
给你一个长度为 $n$ 的数组 $A$ 和长度为 $m$ 的数组 $B$，你每次可以选择 $B$ 中的一个数 $b_i$，然后将 $A$ 中一段长度为 $b_i$ 的区间取反。求可能的 $\max\sum a_i$。

$1\leq n\leq 10^6,-10^9\leq a_i\leq 10^9,1\leq m,b_i\leq\lfloor\frac{n}{2}\rfloor$。

### 题目分析
首先，我们实际上可以把问题转化为每次选一个长度为 $\gcd(b_1,b_2,\dots,b_m)$ 的区间。因为对于 $B$ 中的任意两个数 $b_i,b_j$，我们都能取反一段长度为 $|b_i-b_j|$ 的区间。于是根据更相减损术可以知道上述结论。

于是问题变为，每次选取一个长度为 $L$ 的区间取反，求 $\max\sum a_i$。

这个条件不太好做。我们可以把它转化为每次选取两个距离为 $L$ 的数取反，即取反 $a_i$ 和 $a_{i+L}$（这显然可以通过对连续的两个区间操作来实现）。那么，我们可以根据 $i\bmod L$ 来把 $a$ 中的数分为几个部分。记 $i\bmod L=j$ 的所有 $a_i$ 分到一个数组 $C_j$。

于是我们的操作相当于是对于每个 $C_i$ 中，连续的两个数取反。那么显然对于每个 $C_i$ 最优操作方案是：

- 如果 $C_i$ 中有奇数个负数，那么可以留下一个绝对值最小的作为唯一的负数。

- 如果 $C_i$ 中有偶数个负数，那么可以全部变成非负数。

但是这还不一定是最优的。我们发现我们可以在原数组上选一个 $[1,L]$ 的区间使得每个 $C_i$ 中的正负数奇偶性互换。所以我们还需要对互换的情况算一遍答案。取两种情况较大的即可。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int t,n,m,a[N];
vector<int>v[N];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		int b=0;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1,x;i<=m;i++)scanf("%d",&x),b=__gcd(b,x);
		for(int i=1;i<=n;i++)v[i%b].push_back(a[i]);
		long long ans1=0,ans2=0,s=0;
		for(int i=1;i<=n;i++)s+=abs(a[i]);
		for(int i=0;i<b;i++)
		{
			int cnt=0,mn=1e9;
			for(int x:v[i])cnt+=(x<0),mn=min(mn,abs(x));
			if(cnt&1)ans1+=mn;
			else ans2+=mn;
			v[i].resize(0);
		}
		printf("%lld\n",s-2*min(ans1,ans2));
	}
	return 0;
}
```

---

## 作者：Gokix (赞：5)

[CF1631F](https://www.luogu.com.cn/problem/CF1630D)

非常妙的一道题

------------

首先考虑记 $x=\gcd(b_1,b_2,...,b_m)$。那么 $x$ 可以表示为 $\sum (q_i \times b_i),q_i \in \mathbb{Z}$，所以我们一定能通过若干次翻转使得其等价于只翻连续 $x$ 个数。

于是问题转化为有 $n$ 个整数，可以进行无限次操作，一次操作可以选择连续的 $x$ 个数变为它的相反数，求最大可能 $\sum a$。

注意到翻 $x$ 个数有些麻烦，考虑一个更强的操作。如果我们连续翻转 $[i,i+x],[i+1,i+x+1]$，就相当于我们只翻转了 $i$ 和 $i+x+1$ 两个数。由此一来，我们就获得了同时翻相距为 $x$ 的两个数的操作。

接下来我们将 $a$ 按照下标对 $x$ 同余分成 $x$ 个小序列 $c_0,c_1,...,c_{n-1}$。即 $1,x+1,2x+1...$ 成为一个小序列，$2,x+2,2x+2$ 成为一个小序列……。对于每个小序列 $c_i$，相当于可以进行 $x=2$ 的操作。

然后我们考虑对于每个 $c_i$ 寻找最优解，目标是让负数剩的尽可能小（不一定是少，是加和小）。我们可以使原来有奇数个负数的序列只剩一个负数，原来有偶数个负数的序列一个负数都不剩。方法是从左向右扫 $c$，遇到一个负数就将它和它右面那个数翻过来，这样就实现了至多只剩一个负数。如果还剩一个负数，就不断翻它和它左面的那个数，直至负号移到了绝对值最小的那个数上。

但是由于我们用了一个过强的操作保证每个 $c_i$ 都取到了最优解，我们还需要保证 $c$ 之间关系最优才能取得全局最优解。$c$ 之间关系无非就是是否剩下一个负数，也就是每个 $c_i$ 负数个数的奇偶性。但注意到在 $a$ 中每进行一次操作，每个 $c$ 负数个数的奇偶性都会被恰好改变。原来剩下一个负数的 $c$ 现在不会剩下负数，原来不剩负数的 $c$ 现在会剩下一个负数。也就是说每个 $c$ 负数个数的奇偶性一共就两种情况，都统计一下求个最优值。最后拿全局绝对值和减去两倍它即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

long long rd(){char ch=getchar();long long x=0,f=1;while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}
                        while('0'<=ch && ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void wr(long long x){if(x<0){putchar('-');x=-x;}if(x>9) wr(x/10);putchar(x%10+'0');}

const long long N=1e6+1,lim=1e18;
long long t,n,m,a[N+10],x,sum,cnt[2],ans;

int main(){
	long long i,j,u,v;
	t=rd();
	while(t--){
		n=rd();m=rd();
		for(i=1;i<=n;i++) a[i]=rd();
		x=rd();m--;
		while(m--) x=__gcd(x,rd());
		cnt[0]=cnt[1]=sum=0;
		for(i=1;i<=n;i++) sum+=abs(a[i]);
		for(i=1;i<=x;i++){
			u=lim;v=0;
			for(j=i;j<=n;j+=x){
				if(a[j]<0) v++;
				u=min(u,abs(a[j]));
			}
			if(v&1) cnt[1]+=u;
			else cnt[0]+=u;
		}
		ans=sum-2*min(cnt[0],cnt[1]);
		wr(ans),putchar('\n');
	}
	return 0;
}
```


---

## 作者：周子衡 (赞：2)

**本篇是 CF1630D 的题解，请管理员暂且从 CF1603D 的题解处撤下本篇，谢谢！**

这题初看起来也许有些无从下手，我们先来分析一些简单的情况。假若存在某个 $b_i=1$，我们知道，每一位上的数字的符号反转与否是相互独立的，答案便是全部数字的绝对值之和。

我们来考虑，如果对一组 $B$，答案一定是全部数字的绝对值之和，这组 $B$ 应该满足什么条件。举例来说，假设有 $B$ 中有两个数 $3,4$，我们可以断言答案一定就是全部数字的绝对值之和，因为如果我们要单独反转某一位，我们一定可以先反转以这个位为左端点 / 右端点的一段长度为 $4$ 的区间，再把本来不应该反转的 $3$ 位去掉。注意这里“一定能找到这样的区间”用到了 $b_i\leq \lfloor \dfrac{n}{2}\rceil$ 的性质。再比如说，如果有两个数 $3,5$，我们可以如法炮制，利用反转 $3,5$ 的“工具”来获得一个反转 $2$ 的“工具”，再利用反转 $3,2$ 的“工具”来获得最终的反转 $1$ 的工具。

从这里实际上已经可以发现此题和辗转相除法的关系了。利用两个权值为 $x,y$ 的“工具”（也就是 $B$ 中的两个元素），我们可以创造出权值为 $x-y$ 的“工具”，进一步地，还能创造出权值为 $(x,y)$ 的工具（这里的小括号指最大公因数，下同）。同样地，设 $d=(b_1,...,b_m)$，那么我们可以创造出权值为 $d$ 的工具。可以发现，这个权值为 $d$ 的工具的反转能力和之前的 $B$ 的反转能力完全一致。也就是说，我们只需要解决 $B$ 中只有一个元素的情况，就解决了原题。

接下来的问题并不困难。观察到每次操作一定恰好反转了下标模 $d$ 余 $0,1,...,(d-1)$ 的元素各一个，记 $c_i(0\leq i < d)$ 表示下表模 $d$ 余 $i$ 的位置有多少个被反转了，那么有解的一个必要条件为 $c_0,...,c_{d-1}$ 奇偶性全部相同。容易证明这也是有解的充分条件。通过 DP 求出对每个 $i$，模 $d$ 余 $i$ 的元素中选出奇数个 / 偶数个取反，各数总和的最大值，最后在 $c_i$ 全为奇数或偶数的总和中取较大值即可。

```cpp
#include<cstdio>
#include<algorithm>
 
using namespace std;
 
int gcd(int x,int y){return y?gcd(y,x%y):x;}
 
long long a[2000000];
long long dp[2000000][2];
 
int main()
{
	int T=0;scanf("%d",&T);
	while(T--)
	{
		int n=0,m=0;scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		int d=0;for(int i=1,b=0;i<=m;i++){scanf("%d",&b);d=gcd(b,d);}
		for(int i=n;i>=1;i--)
		{
			if(i+d>n)dp[i][0]=a[i],dp[i][1]=-a[i];
			else dp[i][0]=max(dp[i+d][0]+a[i],dp[i+d][1]-a[i]),
				dp[i][1]=max(dp[i+d][1]+a[i],dp[i+d][0]-a[i]);
		}
		long long sum1=0,sum2=0;for(int i=1;i<=d;i++)sum1+=dp[i][0],sum2+=dp[i][1];
		printf("%lld\n",max(sum1,sum2));
	}
}
```

---

## 作者：Red_river (赞：1)

### 题目大意
这道题的核心任务是对给定的数组 $a$ 执行若干次操作，每次操作中，可以选择一个长度为 $b_i$ 的子数组并将其所有元素的值取反。目标是最大化操作后数组元素之和。
### 题意分析
不难发现，其实我们所选择的区间肯定时越小越好的，因为这样子的话操作空间更大。于是通过类似于 `gcd` 的更相减损术，我们的最小长度就可以是所有 $b_i$ 的最大公约数。具体参见 [oi-wiki](https://oi.wiki/math/number-theory/gcd/#%E6%9B%B4%E7%9B%B8%E5%87%8F%E6%8D%9F%E6%9C%AF)。设其最大公约数是 $X$，于是对于每一对距离为 $X$ 的点，可以通过两个相邻的区间实现取反。于是我们可以对于对 $X$ 取模位置相同的所有数实现取反。接着对于奇偶不同的情况取最小值就行了。
### CODE
```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 1000005
#define NO printf("No\n")
#define YES printf("Yes\n")

using namespace std;
ll n,m,k,jk,ans,sum,num,cnt,tot;
ll dis[N],vis[N];
vector<int> wis[N];

void read(ll &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(ll x)
{
	if(x==0)
	{
		putchar('0');
		return;
	}
	if(x<0)
	{
		x=-x;
		putchar('-');
	}
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}


signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(k);while(k--){
		read(n),read(m);jk=cnt=tot=ans=0;
		for(int i=1;i<=n;i++) read(dis[i]),ans+=abs(dis[i]);
		for(int i=1;i<=m;i++) read(vis[i]),jk=(jk==0?vis[i]:__gcd(jk,vis[i]));
		for(int i=1;i<=n;i++) wis[i%jk].push_back(dis[i]);
		for(int i=0;i<jk;i++){sum=0;num=2e18;
			for(ll j:wis[i]){
				if(j<0)	sum++;
				num=min(num,abs(j));
			}
			if(sum%2==0) cnt+=num;
			else tot+=num;
            wis[i].resize(0);//记得初始化。
		}wh(ans-2*min(cnt,tot));//输出最优答案。
	}
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

得得得得得我是蚁穴人好吧。

一个直觉是区间长显然越小越可操作。

一个很一眼的结论是任意的 $|b_i - b_j|$ 的长都可以被搞出来，这个是很套路地更相减损法，即全局 $\gcd$ 的定义。

所以最后相当于我们要做一个只有一种区间长为 $k$ 的原问题。

然后就很套路了：直接按 $k$ 分块，把余数模 $k$ 相同的位置抽出来，发现任意的区间都会刚好覆盖一种余数一次。

考虑一步单向归约：做两次相邻的长为 $k$ 的区间操作，相当于操作变成取反 $(a_i,a_{i + k})$。

再扩展，我们假设做了 $(a_i,a_{i+k})$ 和 $(a_{i+k},a_{i+2k})$ 那么相当于做一次 $(a_i,a_{i+2k})$，所以操作被单向归约到了 $(a_i,a_{i+xk})$。

考虑对于余数相同的数单独拿出来看，相当于问负数个数的奇偶性，如果是偶数那么我们可以全变成正数，如果是奇数相当于拿出正负里面绝对值最小的一个数变成负数其余变为正数。

考虑怎么变成双向归约。发现最后的操作我们可以写成若干个 $(a_i,a_{i+xk})$ 类型操作和若干个区间操作。

根据我们做单向归约问题的结论看，区间操作其实至多只会影响一次**每一种余数对应的数中负数的奇偶性**。

那么我们枚举是否需要区间操作影响一次影响一次每一种余数对应的数中负数的奇偶性，跑两次单向归约的问题即可。



```cpp
#include "bits/stdc++.h"
using namespace std;
#define ll long long
const int Len = 1e6 + 5;
int n,m,a[Len],b[Len];
ll as;
inline int read() {
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline int Iabs(int x){if(x < 0) x = -x;return x;}
int main()
{
	//freopen("ex_data4.in","r",stdin);
	//freopen("flipping.in","r",stdin);
	//freopen("flipping.out","w",stdout);
	int T;scanf("%d",&T);
	//T = 1;
	while(T --)
	{
		n = read() , m = read();
		as = 0;
		for(int i = 1 ; i <= n ; i ++) a[i] = read();
		for(int i = 1 ; i <= m ; i ++) b[i] = read();
		sort(b + 1 , b + 1 + m);
		for(int i = 2 ; i <= m ; i ++) b[1] = __gcd(b[1] , b[i]);
		if(b[1] == 1) 
		{
			for(int i = 1 ; i <= n ; i ++) as += Iabs(a[i]);
			printf("%lld\n",as);
			continue;
		}
		ll as = 0 , aas = 0;
		for(int i = 1 ; i <= b[1] ; i ++)
		{
			int mx[2] , rem[2] , zr = 0;rem[0] = rem[1] = 0;mx[0] = mx[1] = 1e9;ll sm[2];sm[0] = sm[1] = 0;
			for(int j = i ; j <= n ; j += b[1])
			{
				if(a[j] < 0) rem[0] ++ , sm[0] += Iabs(a[j]) , mx[0] = min(mx[0] , Iabs(a[j]));
				if(a[j] == 0) zr = 1;
				if(a[j] > 0) rem[1] ++ , sm[1] += Iabs(a[j]) , mx[1] = min(mx[1] , Iabs(a[j]));
			}
			//printf("%lld %lld %lld %lld\n",as,sm[0],sm[1],sm[0] + sm[1] - 2 * mx[0]);
			if(rem[0] % 2 == 0 || zr) as += sm[0] + sm[1];//偶数个负数直接换
			else
			{
				if(rem[1]) as += sm[0] + sm[1] - min(mx[0] , mx[1]) * 2;
				else as += sm[0] + sm[1] - 2 * mx[0];//全是负数把最小的一个扔了 
			}
		}
		aas = as;
		as = 0;
		for(int i = 1 ; i <= b[1] ; i ++) a[i] = -a[i];
		for(int i = 1 ; i <= b[1] ; i ++)
		{
			int mx[2] , rem[2] , zr = 0;rem[0] = rem[1] = 0;mx[0] = mx[1] = 1e9;ll sm[2];sm[0] = sm[1] = 0;
			for(int j = i ; j <= n ; j += b[1])
			{
				if(a[j] < 0) rem[0] ++ , sm[0] += Iabs(a[j]) , mx[0] = min(mx[0] , Iabs(a[j]));
				if(a[j] == 0) zr = 1;
				if(a[j] > 0) rem[1] ++ , sm[1] += Iabs(a[j]) , mx[1] = min(mx[1] , Iabs(a[j]));
			}
			//printf("%lld %lld %lld %lld\n",as,sm[0],sm[1],sm[0] + sm[1] - 2 * mx[0]);
			if(rem[0] % 2 == 0 || zr) as += sm[0] + sm[1];//偶数个负数直接换
			else
			{
				if(rem[1]) as += sm[0] + sm[1] - min(mx[0] , mx[1]) * 2;
				else as += sm[0] + sm[1] - 2 * mx[0];//全是负数把最小的一个扔了 
			}
		}
		printf("%lld\n",max(aas , as));
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2400}$
---
### 解题思路：

没有想象中的那么难。

首先发现可以将问题转化为可以无限次地取反长度为 $k=(b_1,b_2,...,b_m)$ 的一段连续的值，然后求最大的数字和，也就是 $\sum_{i=1}^na_i$ 最大。

更进一步，发现所有能做的其实是两件事，取反一次且仅一次一段长度为 $k$ 的区间，取反两个长度差为 $k$ 的区间。操作一进行多次一定可以转化为若干次操作二，唯有进行一次不行，而且可以发现操作一到底进行在哪一段其实无关紧要，只要关心是否进行就行了。先枚举以确定是否进行操作一，从而能更形式化地思考问题了。

将问题分割为 $k$ 个互不干扰的序列，这样的每一个序列都是由距离恰好为 $k$ 的若干个数构成的，每一次的操作二可以任意取反这些分割后的系列中的连续的两个数。由于要求和尽可能大，这个序列最后只会有最多一个负数，到底有没有取决于原有的负数的奇偶性。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int T,n,m,a[1000005],b[1000005],k,cnt,mx,ans1,ans2,tot;
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=1;i<=m;i++)scanf("%lld",&b[i]);
		k=b[1];for(int i=2;i<=m;i++)k=gcd(k,b[i]);
		ans1=ans2=0;
		for(int i=1;i<=k;i++){
			cnt=0;mx=10000000000000;tot=0;
			for(int j=i;j<=n;j+=k){
				mx=min(mx,abs(a[j]));
				tot+=abs(a[j]);
				if(a[j]<0)cnt^=1;
			}
			ans1+=tot-2*cnt*mx;
			ans2+=tot-2*(!cnt)*mx;
		}
		printf("%lld\n",max(ans1,ans2));
	}
	return 0;
}
```


---

## 作者：vectorwyx (赞：1)

先考虑不相交地拼接所有可能的操作区间，这相当于把区间长度加上或减去 $b_i$。令 $k=\gcd b_i$，由裴蜀定理，最终得到的区间长度一定是 $k$ 的倍数，那么其实只需要保留一个 $k$ 就能表出所有区间了。

现在的问题是处理相交的区间，如果翻转的两个区间为 $[i,i+k),[i+1,i+1+k)$ 相当于把两个相隔 $k$ 的位置 $(i,i+k)$ 都取反。 

如果错开得更多一点，比如翻转 $[i,i+k),[i+2,i+2+k)$ 则是把 $(i,i+1,i+k,i+k+1)$ 这四个位置都取反了，而这个也可以看做是分别把 $(i,i+k),(i+1,i+k+1)$ 取反，其余情况同理。因此相交的区间操作都可以归纳为把相隔 $k$ 的两个位置上的数取反。

按 $k$ 建立同余系，把原序列抽离为 $k$ 个子序列。每个子序列直接是相互独立的，而且同一子序列的两个负号可以抵消，因此最终答案只与子序列上负号数量的奇偶性有关。又因为每次单独的区间操作会把连续的 $k$ 个元素一起取反，所以它正好会把所有子序列的奇偶性改变，于是可能的情况只有两种，分别计算出答案取 max 即可。时间复杂度线性。

代码如下：
```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define ull unsigned long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
ull seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return rnd()%(y-x+1)+x;}
inline int read(){int x=0,fh=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')fh=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=1e6+5;
int a[N],b[N],n,m,k;

void solve(){
	cin>>n>>m;
	ll ans=0;
	fo(i,1,n) a[i]=read(),ans+=abs(a[i]);
	fo(i,1,m) b[i]=read();
	k=b[1];fo(i,2,m) k=__gcd(k,b[i]);
	ll v1=0,v2=0;
	fo(i,1,k){
		int mn=1e9,flg=0;
		for(int j=i;j<=n;j+=k){
			if(a[j]<0) flg^=1,sml(mn,-a[j]);
			else sml(mn,a[j]);
		}
		v1+=flg*mn;
		v2+=(flg^1)*mn;
	}
	cout<<ans-2*min(v1,v2)<<'\n';
}

signed main(){
	int T=read();
	while(T--) solve(); 
	return 0;
}
/*
-------------------------------------------------
*/

```


---

## 作者：liuhongyang123 (赞：1)

#### 前言

一枚无需代码实现能力的思维题。

~~说白了，就是一道肥肠好地的蓝题。~~

# 题目大意

给出一个长度为 $n$ 的数组 $a$，一个大小为 $m$ 的集合 $B$，使得其在 $1\le i\le m$ 的条件下 $1 \leq B_i \leq \lfloor \frac{n}{2} \rfloor$。

您可以在数组 $a$ 上执行**任意次**以下操作：

> 在数组 $a$ 上选择一个长度为 $x$ 的区间且 $x$ 在集合 $B$ 内，把区间中的所有元素乘以 $-1$。

> 更形象地说：
> 
> 在数组 $a$ 上选择一个区间 $l$ 到 $r$，使 $1\leq l\leq r \leq n$ 且 $r-l+1=x$，$x \in B$。

求操作后的 $\sum\limits_{i=1}^n {a_i}$ 的最大值。

# 思路

我们可以发现每次操作变化的就是区间长度和区间位置，区间位置肯定要变，不然都在一个起点上操作，其他的变都没变，这怎么去最大值，所以如果要想优化，就要在区间长度上找突破口。

区间长度那么多，怎么才能将其固定呢？

我们考虑它的本质：

下面为了方便我们将乘以 $-1$ 称为**取反**，但这只是符号取反。

我们假设 $B=\{3,8\}$，令操作的起点始终且 $1$。

> 1. 我们先取 $x=8$，那么 $a[1] \ldots a[8]$ 的值会取反。
>   
> 2. 在取 $x=3$，那么 $a[1] \ldots a[3]$ 的值会再次取反
>   

所以，我们发现这其实相当于 $a[4] \ldots a[8]$ 这长度为 $5$ 的区间取反了。

又因为题目中保证 $1 \leq B_i \leq \lfloor \frac{n}{2} \rfloor$，有了这个保证就可以得出数组 $a$ 上的所有长度为 $5$ 区间做这一组操作后就可被取反，如果我说的有点劝退的话，建议自己手模几个数据。

然后，我们就可以取 $x=5$，接着继续简化，直到不能简化，你就会得到一个数为 $\gcd(B[1],\ldots,B[m])$，我们就让这个数叫 $g$ 吧。

$g$ 就具有最小长度的修改，说人话，就是用 $g$ 就对了，因为你把几个长度为 $g$ 的区间拼起来修改就可得到用任意一个 $B[i]$ ，$1\le i\le m$，修改的效果，$g$ 可是所有修改长度的最小公倍数啊。

那么，我们就这样把每次区间长度的变化固定住了。

# 做法

我们求出 $g$ 以后，就把问题简化成：

> 在数组 $a$ 上取任意一段长度为 $g$ 的区间，将里面所有元素乘以 $-1$，这个操作可以执行任意次。
> 
> 求操作后的 $\sum\limits_{i=1}^n {a_i} $ 的最大值。

这是典型的入门 ```DP``` 题。

我们可以得出一个显而易见的结论：

> 每次操作修改的数组 $a$ 的下标模 $g$ 的余数都两两不同。

如果不懂，还是那句话，手模给你最好的答案。

所以我们可以得知，下标模 $g$ 的余数不同的 $a[i]$ 被修改的总次数是相同的，因为每次修改，每个模 $g$ 的余数都会被改到。

我们根据这个特点，设 $f[i][0/1]$ 为下标模 $g$ 为 $i$ 的$a[i]$ 被修改的次数为偶数或奇数时的最大值。

核心代码：

```cpp
for(int i=n;i>n-Gcd;i--) f[i][0]=a[i],f[i][1]=-a[i]; 
//预处理，第一组余数赋值，你别无选择
for(int i=n-Gcd;i>=1;i--){
    int j=i+Gcd;//上组同余的下标
    f[i][0]=max(f[j][0]+a[i],f[j][1]-a[i]);
    //如果这次修改后，修改总次数是偶数，有两种情况
    //1.上组修改总次数是偶数，那么这次没修改，直接加
    //2.上组修改总次数是奇数，那么这次修改了，取反加
 f[i][1]=max(f[j][0]-a[i],f[j][1]+a[i]);
    //跟上者同理
}
```

然后答案就是所有余数修改总次数为偶数的和与所有余数修改总次数奇数的和的最大值。

这部分讲的有点屎，不过懂我意思就行，推荐边看代码边理解。

# Code

最后，请允许我献上这朴实无华的代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e6+10;
int T,n,m,a[MAXN],f[MAXN][2],Gcd;
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&m);
		Gcd=f[0][0]=f[0][1]=0;
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(int i=1,x;i<=m;i++) scanf("%lld",&x),Gcd=__gcd(Gcd,x);
		for(int i=n;i>n-Gcd;i--) f[i][0]=a[i],f[i][1]=-a[i];
		for(int i=n-Gcd;i>=1;i--){
			int j=i+Gcd;
			f[i][0]=max(f[j][0]+a[i],f[j][1]-a[i]);
			f[i][1]=max(f[j][0]-a[i],f[j][1]+a[i]);
		}
		for(int i=1;i<=Gcd;i++) f[0][0]+=f[i][0],f[0][1]+=f[i][1];
		printf("%lld\n",max(f[0][0],f[0][1])); 
	}
	return 0;
}


```

## 完结散花

---

## 作者：monstersqwq (赞：1)

[CF传送门](https://codeforces.com/contest/1630/problem/D)

首先考虑证明一个很重要的事情：这些 $b$ 的翻转操作等价于可以对于任意连续 $\gcd(b_1,b_2,b_3\cdots b_m)$ 做翻转。

我们只需要证明，当前如果可以用 $x,y(x\le y)$ 长度的两种翻转操作，一定可以在序列上任意一段长为 $y-x$ 的子段上做翻转操作，然后由于辗转相减法，就可以有上面的结论。

由于有 $b\le \left\lfloor\dfrac{n}{2}\right\rfloor$，自己手玩一下可以知道这是显然成立的。

然后就化成了 $m=1$ 的情形。

现在令 $s=\gcd(b_1,b_2,b_3\cdots b_m)$，如果 $s=1$ 显然答案就是所有 $a$ 的绝对值之和。

接下来看 $s>1$ 的情况，如果你想过了两次分别操作 $[1,s],[2,s+1]$ ，就会发现实际上是 $1,s+1$ 这两个位置发生了改变，再玩一下可以发现实际上是使相邻两个模 $s$ 同余的位置发生改变。

显然可以对每个模 $s$ 相同的余数类分别讨论（注意，这里有个小坑点！！！待会再说），于是就变成了 $m=1,s=2$ 的情形，这时实际上已经好做了。会发现可以使任意一组位置发生改变，这样最后的结果按照初始的时候该类中负数个数分类，如果为偶数就是该类中所有数的绝对值之和，奇数的话则是取绝对值（注意这里是绝对值）最小的数作为负数，其它全是正数，然后这题就没了？

call back 一下上文的小坑点：注意到并不能对各个余数类完全分类，考虑如果做一次操作，会改变所有余数类负数个数的奇偶性（因为每个余数类恰好有一个数在这次的操作区间里），然后实际上还要对于改变后的奇偶性再做一遍上述操作，取结果大的即可。

赛时代码：
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<cmath>
#include<stack>
#include<map>
#include<ctime>
#include<bitset>
#define int ll
using namespace std;
typedef long long ll;
const int maxn=1000005;
int T,n,m,a[maxn];
ll ans=0;
int mygcd(int a,int b)
{
	if(b==0) return a;
	else return mygcd(b,a%b);
}
signed main()
{
	cin>>T;
    while(T--)
    {
        scanf("%lld%lld",&n,&m);
        ans=0;
        for(int i=1;i<=n;i++)
    	{
	    	scanf("%lld",&a[i]);
	    	ans+=(a[i]<0?-a[i]:a[i]);
    	}
    	int s=0;
    	for(int i=1;i<=m;i++)
	    {
	    	int tmp;scanf("%lld",&tmp);
	    	s=mygcd(s,tmp);
    	}
    	if(s==1)
    	{
	    	printf("%lld\n",ans);
	    	continue;
    	}
    	ll tmpans1=ans,tmpans2=ans;
    	for(int i=1;i<=s;i++)
    	{
	    	int tot=0,maxx=2e9;
	    	for(int j=i;j<=n;j+=s)
	    	{
	    		if(a[j]<0)
	    		{
	    			tot++;
	    		}
                maxx=min(maxx,(a[j]<0?-a[j]:a[j]));
	    	}
	    	if(tot%2==1) tmpans1-=2*maxx;
	    	else tmpans2-=2*maxx;
    	}
	    printf("%lld\n",max(tmpans1,tmpans2));
    }
	return 0;
}
```


---

## 作者：subcrip (赞：0)

首先可以发现应当把 $B$ 中的所有数取个 $\gcd$，这在别人的题解里已经解释的很明白了。

然后直接贪心就行了。我们把数组按照模 $g$ 的值划分成 $g$ 个桶，每次从每个桶中各取出最小值进行翻转。这是因为我们一定可以先进行一次操作把连续的 $g$ 个元素翻转，然后再在每个桶中把这个翻转的符号传递到我们想要的最小值位置上去。

最多这样做几次？容易发现当一个桶中的元素全变成正数之后，再去在这个桶中重复“选最小值翻转”这个过程，一定是一直在操作这个桶中的同一个元素（也就是一开始绝对值最小的元素）。所以我们至多需要把所有桶中的元素都变成正数，再加上一次操作。也就是一共操作 $\dfrac ng+1$ 次。

用优先队列维护每个桶中的最小值，这样这道题就做完了。

Code:

```cpp
void solve() {
    read(int, n, m);
    readvec(int, a, n);
    readvec(int, b, m);
    int g = b[0];
    for (int i = 1; i < m; ++i) {
        g = gcd(g, b[i]);
    }
    vector<min_heap<int>> bk(g);
    for (int i = 0; i < n; ++i) {
        bk[i % g].emplace(a[i]);
    }
    ll res = accumulate(a.begin(), a.end(), ll(0));
    ll curr = res;
    for (int i = 0; i <= n / g + 1; ++i) {
        for (min_heap<int>& v : bk) {
            int t = v.top();
            v.pop();
            v.push(-t);
            curr -= 2 * t;
        }
        chmax(res, curr);
    }
    cout << res << '\n';
}
```

---

## 作者：I_am_Accepted (赞：0)

### Analysis

**结论：以任意 $B$ 中元素为长度 Flip 一段区间任意次 等价于 $B$ 中元素的 $\gcd$ 为长度做任意次。**

**证明**：（懂了请跳过，证明略长）

设 $\gcd\limits_{i=1}^mb_i$ 为 $g$。

（始终记住，$B$ 是集合，$g$ 是数）

由裴蜀定理得到：存在一组 $\{c_1,\dots,c_m\}$ 使得 $\sum\limits_{i=1}^mb_ic_i=g$。

对于每个 $1\le i\le m$，将 $b_ic_i$ 平铺开，加入多重集合 $C$。 

这里平铺指

$$\begin{cases}
\begin{matrix}\underbrace{\{b_i,b_i,\dots,b_i\}}\\c_i \ times\end{matrix} & c_i\ge 0
\\
\begin{matrix}\underbrace{\{-b_i,-b_i,\dots,-b_i\}}\\|c_i| \ times\end{matrix} & c_i<0
\end{cases}$$

显然通过重排，我们可以使 $C$ 中任意前缀和 $\in[x,x+n-1]\quad(\forall x\in[1-n,0])$

原因是 $B$ 中元素值的上限是 $\left\lfloor\frac{n}{2}\right\rfloor$，每次在 $[x,x+n-1]$ 下半时选正的 $C$ 中元素，上半时选负的。

这样我们在 $\{a\}$ 中 Flip 一段长为 $g$ 的区间（因为 $|\{a\}|=n$）。

然而，$B$ 中每个元素都是 $g$ 的倍数，所以 $B$ 能完成的 $g$ 也能完成。

综上，我们构建了（$B$ 能完成的 Flip）和（$g$ 能完成的 Flip）之间的双射，**原命题得证**。

我们称以 $g$ 长度的 Flip 为 Glip。

发现两次错位为 $1$ 的 Glip 可以使两个间隔为 $g$ 的数同时取相反数。

所以我们将 $\{a\}$ 中元素按照下标 $\pmod{g}$ 划分成 $D_0,D_1,\dots,D_{g-1}$。

同一个 $D_i$ 中元素的“负号”是可以任意传递的，且 $2$ 个“负号”可以抵消。我们将每组“负号”抵消到不足 $2$ 个。

数组 $\{d_0,\dots,d_{g-1}\}$ 记录每组现在是（$1$）否（$0$）仍有“负号”，$\{e_0,\dots,e_{g-1}\}$ 记录每组元素**绝对值**最小值。

由于“负号”最优动到绝对值最小的地方，所以：

$$sum=\sum\limits_{i=1}^n|a_i|$$

$$ans_1=sum-2\sum\limits_{i=0}^{g-1}d_ie_i$$

不过再来任意一次 Glip，会让 $\{d\}$ 全部取反（bool 的取反），所以：

$$ans_2=sum-2\sum\limits_{i=0}^{g-1}(1-d_i)e_i$$

最终：

$$ans=\max\{ans_1,ans_2\}$$

快乐 AC！

### Code

[Link](https://codeforces.com/contest/1631/submission/144329498)

---

