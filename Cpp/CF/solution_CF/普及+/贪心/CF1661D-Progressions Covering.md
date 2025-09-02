# Progressions Covering

## 题目描述

You are given two arrays: an array $ a $ consisting of $ n $ zeros and an array $ b $ consisting of $ n $ integers.

You can apply the following operation to the array $ a $ an arbitrary number of times: choose some subsegment of $ a $ of length $ k $ and add the arithmetic progression $ 1, 2, \ldots, k $ to this subsegment — i. e. add $ 1 $ to the first element of the subsegment, $ 2 $ to the second element, and so on. The chosen subsegment should be inside the borders of the array $ a $ (i.e., if the left border of the chosen subsegment is $ l $ , then the condition $ 1 \le l \le l + k - 1 \le n $ should be satisfied). Note that the progression added is always $ 1, 2, \ldots, k $ but not the $ k, k - 1, \ldots, 1 $ or anything else (i.e., the leftmost element of the subsegment always increases by $ 1 $ , the second element always increases by $ 2 $ and so on).

Your task is to find the minimum possible number of operations required to satisfy the condition $ a_i \ge b_i $ for each $ i $ from $ 1 $ to $ n $ . Note that the condition $ a_i \ge b_i $ should be satisfied for all elements at once.

## 说明/提示

Consider the first example. In this test, we don't really have any choice, so we need to add at least five progressions to make the first element equals $ 5 $ . The array $ a $ becomes $ [5, 10, 15] $ .

Consider the second example. In this test, let's add one progression on the segment $ [1; 3] $ and two progressions on the segment $ [4; 6] $ . Then, the array $ a $ becomes $ [1, 2, 3, 2, 4, 6] $ .

## 样例 #1

### 输入

```
3 3
5 4 6```

### 输出

```
5```

## 样例 #2

### 输入

```
6 3
1 2 3 2 2 3```

### 输出

```
3```

## 样例 #3

### 输入

```
6 3
1 2 4 1 2 3```

### 输出

```
3```

## 样例 #4

### 输入

```
7 3
50 17 81 25 42 39 96```

### 输出

```
92```

# 题解

## 作者：SDLTF_凌亭风 (赞：16)

假设你在玩 MC，并且你已经开发出了金苹果农场，现在你掉了一格饱食度，你想补回来，怎么补？

显然的，直接吃一个金苹果是最不耗脑子的做法。

对于这个题，每一个没有达到的数，我们就让他成为等差数列的最后一项一次性满足就好了。

维护等差数列有很多种方法，双差分或者差分树状数组都可以。

由于没看懂讲课人的代码被钉在了耻辱柱上，所以写一个有详细注释的版本。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

// raw : 原始数组
int n, k, raw[300003], tot[300003], ans;

signed main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for(int i = 1; i <= n; ++ i) cin >> raw[i];
	
	// 由于我们只关心等差数列的最后一项落到了谁身上
	// 于是直接枚举等差数列的最后一项的位置
	for(int i = n, sum = 0, now = 0; i >= 1; -- i) {
		// 坑：倒着枚举的时候请注意
		// 该位置的下标可能小于 k
		// pos 是等差数列第一项的位置，len 是该数列的长度
		int pos = max(1ll, i - k + 1ll), len = i - pos + 1ll;
		raw[i] -= sum;

		// opcnt 是理论需要的操作次数，当 opcnt > 0 的时候，说明一次还搞不完
		int opcnt = (raw[i] + len - 1) / len;
		if(opcnt > 0) ans += opcnt, now += opcnt, sum += 1ll * len * opcnt, tot[pos] += opcnt;
		sum -= now, now -= tot[i];
	}
	cout << ans;
}
```

---

## 作者：XL4453 (赞：6)

### $\text{Difficulty : 1900}$
---
场上第三，差一点就抢到一血了。

---
### 解题思路：

考虑贪心。

从后往前依次考虑每一个位置，如果这个位置上的值还没有达到要求，则尽可能地用更高（也就是增加的值更大的位置）的位置对这个位置进行增加。

这样的正确性是比较显然的，因为一个位置后面的所有的位置都已经满足了，不需要任何形式的增加，所以尽可能地增加前面的就好了。

---
但是直接这样做的复杂度会很高，不能接受，考虑对其进行优化。

记录下当前位置上增加的值 $sum$，以及这个位置在的值在传递到下一个位置会减少多少 $cnt$，同时记录下每一个位置上增加的次数 $a_i$ 用以更新 $cnt$ 的值。

对于每一个位置，先比较当前值和需要的值的大小关系并完成对于当前值增加，然后更新下一个位置的 $sum$，也就是减去 $cnt$，再更新 $cnt$，也就是减去 $a_{i+k-1}$。

这样的总复杂度就是 $O(n)$ 的了，可以通过。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
#define int long long
int n,b[600005],k,op,sum,ans,a[600005];
signed main(){
	scanf("%I64d%I64d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%I64d",&b[i]);
	for(int i=n;i>=k;i--){
		if(b[i]>sum){
			a[i]=(b[i]-sum)/k+((b[i]-sum)%k!=0);
			op+=a[i];
			ans+=a[i];
			sum+=a[i]*k;
		}
		sum-=op;
		op-=a[i+k-1];
	}
	for(int i=k-1;i>=1;i--){
		if(b[i]>sum){
			a[i]=(b[i]-sum)/i+((b[i]-sum)%i!=0);
			op+=a[i];
			ans+=a[i];
			sum+=a[i]*i;
		}
		sum-=op;
		op-=a[i+k-1];
	}
	printf("%I64d\n",ans);
	return 0;
}
```


---

## 作者：yinhy09 (赞：4)

## CF1661D 题解

看到没有多少 $O(n)$ 做法的题解，于是乎我来发一个清晰一点的。

可以考虑贪心，但是不能从前向后，因为当我们需要给一个数加上 $x$ 时，我们不知道应该从第几个数开始加，都有可能是最优解。如果从后向前就可以解决这个问题，每一次想要给一个数加 $x$ 时，直接把他选做增加段的最后一个，这样他加的最多，且没有加数浪费到后面已经加好的数上。

这个操作可以用差分线段树维护，但是这有悖 CF div.2 D 小清新思维的结论，所以想一想简便方法。

我们发现，相邻两个加数差都是 $1$（这也是为什么我们可以用差分线段树），所以是不是可以通过后一个数加了多少算出前面一个数加了多少呢？我们唯一需要特判的是后面的数作为第一个加数的情况。

我们用 $now$ 记录当前位置已经被后面操作加了多少，然后用 $tot$ 记录从当前位置到下一位置，多加了多少。因为需要特判我们说的情况，所以还需要用 $a$ 数组记录每个点作为最后一个加了多少次。

我们每次先判断需不需要加，如果需要，那么将 $tot$ 加上 $a_i$（$i$ 是当前位置，因为每次操作都会造成 $1$ 的差距），将 $now$ 加上 $a_i\times num$。（$num$ 表示这一次需要进行的操作次数）加完之后，我们需要转移到前一个，所以把 $now$ 减掉 $cnt$ 得出下一位加过的量，然后把 $cnt$ 减掉 $a_{i+k-1}$，因为下一个数已经不在 $i\sim i+k-1$ 的管辖范围内了。

Total time complexity：$O(n)$。

### 注意！

1. $a$ 数组需要开到 $n+k$ 防止 $a_{i+k-1}$ 越界（你就会 WA on 15）

2. $num$ 的计算一定不要直接 $\lceil\frac{b_i-sum}{k}\rceil$，当 $i<k$ 的时候分母应该是 $i$。

### AC Code：

```cpp
/*******************************
| Author:  yinhy09
| Problem: D. Progressions Covering
| Contest: Educational Codeforces Round 126 (Rated for Div. 2)
| URL:     https://codeforces.com/contest/1661/problem/D
| When:    2023-02-01 19:37:20
| 
| Memory:  256 MB
| Time:    2000 ms
*******************************/

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define multicase() ll T;scanf("%lld",&T);while(T--)
ll read()
{
	char c;
	ll x=0;
	ll f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f*=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
ll n,k;
const int maxn=3e5+10;
ll b[maxn],a[maxn<<1],now=0,tot=0,ans=0;
ll up(ll x,ll y)
{
	if(x%y==0)return x/y;
	else return (x/y)+1;
}
int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
	ll add=0;
	for(int i=n;i>=1;i--)
	{
		if(b[i]>now)
		{
			add=k;
			if(i<k)add=i;
			a[i]=up(b[i]-now,add);
			tot+=a[i];
			now+=a[i]*add;
			ans+=a[i];
		}
		now-=tot;
		tot-=a[i+k-1];
	}
	printf("%lld\n",ans);
	return 0;
}
```

谢谢观看。

---

## 作者：Po7ed (赞：3)

**[题目传送门](https://www.luogu.com.cn/problem/CF1661D)**
### 前言
本篇题解亮点在于解释如何一遍从后往前扫一边双重差分。
### 解法
贪心，从右往左依次满足每个数。至于贪心的正确性其他题解已经讲得很清楚了，不再赘述。
而题目中将数组 $a$ 加到 $a_i\ge b_i$ 等价于把 $b_i+\Delta b_i\le0$。

**重点是如何维护贪心过程中进行的区间减等差数列。**
暴力减等差数列十分麻烦，有没有替代的方法？

先看这张图，数组 $\Delta b$ 初始时全是 $0$，我们减去一个等差数列（用大括号括起来的）后变成：
$$
\cdots~0~\overbrace{-d~{-2d}~{-3d} ~{-4d}}^{[l,i]}~0\cdots
$$

对它进行差分两次（从右往左）：

| 下标 | $l-2$ | $l-1$ | $l$ | $l+1$ | $i-1$ | $i$ |$i+1$|
|-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| 数组 $\Delta b$ | $0$ | $0$ | $-d$ | $-2d$ | $-3d$ | $-4d$ | $0$ |
| 差分数组 | $0$ | $+d$ | $+d$ | $+d$ | $+d$ | $-4d$ | $0$ |
| 双重差分数组 $c$ | $-d$ | $0$ | $0$ | $0$ | $+5d$ | $-4d$ | $0$ |

我们发现，只要在 $c$ 上标记 $3$ 个位置即可：$l-2,i-1,i$。
我们可以用 $c$ 对应 $\Delta b$，需要 $\Delta b$ 时进行对 $c$ 进行两次前缀和还原出 $\Delta b$。

但是麻烦还没完，我们要一边维护 $c$，一边算出 $\Delta b_i$ 的值。

将操作分为三部分：
1. 进行还原，通过 $c$ 算出 $\Delta b_i$，即代码中的 `sum2`。
2. 计算 $b_i+\Delta b_i$ 和应该贪心地减去几个等差数列。
3. 如果要减，那么对 $c$ 进行标记，表示出减去的等差数列，并修正一些中间变量如代码中的 `sum1` 和 `sum2`。因为如果要减，就要更新 $c_i$，而在第 $1$ 步中根据 $c_i$ 算的 `sum1` 和 `sum2`（即 $\Delta b$）也要修正。

具体见代码。
### 代码
```cpp
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;
const int N=300005;
int n,k;
ll ans,sum1,sum2;
ll b[N],c[N];// 原数组和双重差分数组。注意双重差分数组两次前缀和（“解码”）后
// 得出的是原数组要减去的值（即差值）。

int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",b+i);
	}
	for(int i=n;i>0;i--)// 从后往前扫
	{
    	// 还原
		sum1+=c[i];// 一次前缀和
		sum2+=sum1;// 两次前缀和
        // 计算要减去多少个等差数列（用 d 表示）。注意不要越界。
		ll l=max(1,i-k+1),len=i-l+1,d=(b[i]+sum2+len-1)/len;
		if(d>0)// 如果要减
		{
			ans+=d;// 记录答案
            // 标记 c 数组。
			if(l-2>0)
			{
				c[l-2]-=d;
			}
			c[i-1]+=(len+1)*d;
            // 修正两个前缀和。可以看上面的表格理解。
			sum1-=len*d;
			sum2-=len*d;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：ZLRest (赞：3)

## 分析：
不难看出此题需要贪心。

考虑如果 $a_i<b_i$，则把 $a_i$ 作为下一次操作的尾显然更优，这样可以尽可能覆盖多的数并使 $a_i$ 在一次操作中变得尽可能的大。

~~贪心思想其他题解讲的很清楚了我不过多赘述。~~
## 实现：

暴力的复杂度很显然是 $O(n^2)$ 的，无法通过此题，我们考虑用差分。将操作从对 $a_i$ 加转化为对 $b_i$ 减，最后当 $\forall b_i\leqslant 0$ 时即满足题意。

在进行一次操作后，$b$ 数组为 $b_i -1,b_{i+1} -2\cdots b_{i+k} -k$;

差分后，变为 $b_i -1,b_{i+1} -1\cdots b_{i+k} -1+k$。

此时还是需要修改  $i \sim i+k$ 显然不行，于是我们考虑二次差分。

可以参考二次差分例题  [P4231 三步必杀](https://www.luogu.com.cn/problem/P4231)

 [友链](https://www.luogu.com.cn/blog/450246/solution-p4231)

此题我们二次差分后就只需要修改 $b_i$ 和 $b_{i+k}$ 就可以了。

其余看代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
int a[300010],c[300010];
int now,sum;
int ans;
inline int read(){
	   int x=0,f=1;
	   char c=getchar();
	   while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	   while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	   return x*f;
}
signed main(){
	n=read();
	k=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=n;i>=1;i--){
		int l=max(1ll,i-k+1),len=i-l+1;
		a[i]-=sum;
		int he=(a[i]+len-1)/len;
		if(he>0){
			ans+=he;
			sum+=len*he;
			now+=he;
			c[l]+=he;
		}
		sum-=now;
		now-=c[i];
	}
	printf("%lld",ans);
	return 0;
}

```
蒟蒻第一次交题解，有什么错误还望 dalao 指正~~~

---

## 作者：I_am_Accepted (赞：2)

### Preface

前置知识：差分，树状数组（单点询问，区间加），贪心。

### Analysis

显然的贪心：从右往左满足各个元素。

但是修改是区间加等差序列，比较头疼（当然线段树也是能做的）。

所以我们将原序列进行差分，用树状数组维护这个差分数组，$n\to 1$ 枚举时元素值可以从上一个值加差分得来。

这样，我们的修改变为区间加（当然不同的差分方式可能有单点加），可行。

时间 $O(n\log n)$，常数小。

### Code

[Link](https://codeforces.com/contest/1661/submission/153598871)

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 300010
#define low (x&(-x))
int n,k,a[N],b[N],ans=0,c[N];
void add(int x,int y){
	while(x<=n+1){
		c[x]+=y;
		x+=low;
	}
}
int que(int x){
	int res=0;
	while(x){
		res+=c[x];
		x-=low;
	}
	return res;
}
signed main(){IOS;
	cin>>n>>k;
	For(i,1,n) cin>>a[i];
	For(i,1,n) a[i]=-a[i];
	reverse(a+1,a+1+n);
	Rof(i,n,1) a[i]-=a[i-1];
	For(i,1,n) add(i,a[i]-a[i-1]);
	int now=0,lim;
	For(i,1,n-k+1){
		now+=que(i);
		if(now>=0) continue;
		lim=(-now+k-1)/k;
//		cerr<<i<<" "<<now<<":"<<lim<<endl;
		now+=lim*k;
		ans+=lim;
		add(i+1,-lim);
		add(min(n,i+k)+1,lim);
	}
	int res=0;
	For(i,n-k+2,n){
		now+=que(i);
//		cerr<<i<<"!"<<now<<endl;
		ckmx(res,((-now+(n-i))/(n-i+1)));
	}
	cout<<ans+res<<endl;
return 0;}
```

---

## 作者：scp020 (赞：1)

# CF1661D Progressions Covering 题解

比较套路的贪心，与之类似的题不少。本篇题解不需要差分。

## 解法

显然，对这些选定区间的操作顺序不影响答案且没有后效性，所以考虑贪心。

这里选择从后向前贪心。对于位置 $i$，有如图的不超过 $k$ 种区间对 $a_i$ 有影响，且下面的区间对答案的贡献是严格优于上面的区间对答案的贡献的。值得注意的是每种区间可能不止 $1$ 个。

![img](https://cdn.luogu.com.cn/upload/image_hosting/yn8d2fk7.png)

注意到每个区间都是对 $k$ 个位置有影响的，因为我们从后向前贪心，所以对于位置 $i$，对以 $i$ 结尾的长度为 $k$ 的区间需要几个有影响的区间是以 $i + 1$ 结尾到 以 $i + k - 1$ 结尾的长度为 $k$ 的区间。我们统计这些区间的个数和，方法类似于滑动窗口。

统计每种以 $i$ 结尾的长度为 $k$ 的区间有多少个，最后累加即可获得答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace fast_IO
{
	/*
	fast Input/Output
	*/
};
using namespace fast_IO;
#define int long long
int n,k,a[300010],ans,num[300010],sum,in;
signed main()
{
	read(n),read(k);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=n;i-k+1>=1;i--)
	{
		if(a[i]>sum) num[i]=ceil((a[i]-sum)*1.0/k),sum+=num[i]*k,in+=num[i];
		sum-=in;
		if(i+k-1<=n) in-=num[i+k-1];
	}
	for(int i=k-1,delta;i;i--)
	{
		if(a[i]>sum) delta=ceil((a[i]-sum)*1.0/i),sum+=delta*i,in+=delta,num[k]+=delta;
		sum-=in;
		if(i+k-1<=n) in-=num[i+k-1];
	}
	for(int i=1;i<=n;i++) ans+=num[i];
	cout<<ans;
	return 0;
}
```


---

## 作者：under_the_time (赞：1)

## upd
- 2023-10-3 对二次差分进行补充解释。感谢 [pig_pig_](https://www.luogu.com.cn/user/749114) 的指正。
## 题意

> 给定长度为 $n$ 的数组 $a$ 和 $b$，$a$ 数组初始为 $0$，每次可以执行一个操作：选定一段长度为 $k$ 的区间，区间左端点大于 $0$，右端点小于等于 $n$，将区间内第一个元素加 $1$，第二个元素加 $2$，以此类推，给定 $n$，数组 $b$ 和 $k$，求满足 $a_i\ge b_i$ 的最小操作次数，其中 $1\le i\le n$。

## 思路

考虑贪心算法。

如果 $a_i<b_i$，即没有满足条件，则最优的操作方案显然为将 $a_i$ 放在长度为 $k$ 的操作区间尽量末尾处。这样操作可以使操作区间产生的影响最大化，且 $a_i$ 的增加程度最大化。

做法就出来了。考虑从后往前做，假设当前做到了第 $i$ 个元素，且该元素没有满足条件，$[i+1,n]$ 的元素都满足条件了。我们选择一个前面所说的最优区间进行操作，直到该元素满足条件。

维护区间加的过程考虑差分。我们将对于数组 $a$ 的区间加转化为 对于数组 $b$ 的区间减，当 $b_i\le 0$ 时满足题意，其中 $1\le i\le n$ 。

因为前后元素增加的量差总为 $1$，所以我们考虑将修改量数组进行二次差分：

- 假设当前增加量数组为
  $$
  0,0,0,1,2,3,4,5,6,0,0,0
  $$

- 对原数组进行第一次差分，得到
  $$
  0,0,0,1,1,1,1,1,1,-6,0,0
  $$

- 再进行一次差分，得到
  $$
  0,0,0,1,0,0,0,0,0,-7,6,0
  $$

- 因为我们是从后往前做的，$-7$ 后的 $6$ 不会对当前和还未被扫描的元素产生影响，所以我们不用太在意这个 $6$。
- 此时发现我们只需要修改两处二次差分后的增加量数组，就可以实现区间加公差为一的等差序列。

注意到我们是从后往前进行操作，所以我们可以动态的计算当前元素增加的量。

时间复杂度 $O(n)$。具体实现可以看代码。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 3e5 + 5;
int n, k, a[maxn], c[maxn]; // c数组用于记录操作的次数
int now, sum; // now表示当前操作的次数，sum表示未执行操作的总次数（也就是对当前元素产生的影响大小）
int ans; // ans表示最终的答案
signed main(){
    scanf("%lld%lld",&n,&k);
    for(int i = 1; i <= n; i++) scanf("%lld",&a[i]);
    for(int i = n; i >= 1; i --){ // 从后往前扫
        int pos = max(i - k + 1ll, 1ll); // 操作区间的左端点
        int len = i - pos + 1; // 操作区间的长度
        a[i] -= sum;
        int tot = (a[i] + len - 1) / len; // 还需要的操作次数
        if(tot > 0){ // 如果仍需要操作
            ans += tot; 
            sum += len * tot; // 更新操作的总次数
            now += tot; // 更新当前操作的次数
            c[pos] += tot; // 记录操作次数到c数组中
        }
        sum -= now; // 减去已经执行的操作的总次数
        now -= c[i]; // 减去当前操作的次数
    }
    printf("%lld", ans); 
}
```

- Codeforces 测评结果：
![](https://cdn.luogu.com.cn/upload/image_hosting/a74sh0ap.png)

---

## 作者：ChengJY_ (赞：1)

[link](https://www.luogu.com.cn/problem/CF1661D)

### 简化题意

给定一个长度为 $n$ 的数组 $A$ ，和一种操作。

- 每次操作选定长度为 $k$ 的区间 $[L,R]$ , 将 $A_L-1$，$A_{L+1}-2$ …… $A_R-k$ 。

求使 $A$ 中所有元素小于等于0所需的最小操作个数。

### Sulution

一个显然的贪心思路：

- 从后往前枚举，对于每个大于等于1的 $A_i$，将区间 $[i-k+1,k]$ 操作 $\left\lfloor\dfrac{A_i}{k}\right\rfloor$ 次。  

证明略。

暴力实现是 $O(n^2)$ 的，我们考虑维护这个操作。

因为需要区间修改，单点查询，考虑线段树，但是每次修改的值不一定，考虑转化。

发现每次修改对于区间的差分数组改变一致，于是将原数组转化为差分数组。

那么我们就需要区间修改，区间查询，可以线段树实现。

### Code

```cpp
#include<bits/stdc++.h>
#define N 300005
#define int long long
#define ls(p) p<<1
#define rs(p) p<<1|1
using namespace std;

inline int read(){
    int x=0,w=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*w;
}

int n,k,ans;
int a[N];
struct node{int sum,tag,len;}tree[N<<2];

void push_up(int p) {tree[p].sum=tree[ls(p)].sum+tree[rs(p)].sum;}
void push_down(int p){
    if(!tree[p].tag) return ;
    tree[ls(p)].tag+=tree[p].tag;tree[ls(p)].sum+=tree[ls(p)].len*tree[p].tag;
    tree[rs(p)].tag+=tree[p].tag;tree[rs(p)].sum+=tree[rs(p)].len*tree[p].tag;
    tree[p].tag=0;
}
void build(int p,int l,int r){
    tree[p].len=r-l+1;
    if(l==r){tree[p].sum=a[l];return ;}
    int mid=(l+r)>>1;
    build(ls(p),l,mid);build(rs(p),mid+1,r);
    push_up(p);
}
void update(int p,int l,int r,int L,int R,int k){
    if(L<=l&&r<=R){
        tree[p].tag+=k; tree[p].sum+=tree[p].len*k;
        return ;
    }
    push_down(p);
    int mid=(l+r)>>1;
    if(mid>=L) update(ls(p),l,mid,L,R,k);
    if(mid<R) update(rs(p),mid+1,r,L,R,k);
    push_up(p);
}
int query(int p,int l,int r,int L,int R){
    if(L<=l&&r<=R) return tree[p].sum;
    push_down(p);
    int mid=(l+r)>>1,res=0;
    if(mid>=L) res+=query(ls(p),l,mid,L,R);
    if(mid<R) res+=query(rs(p),mid+1,r,L,R);
    return res;
}

signed main(){
    n=read();k=read();
    for(int i=1;i<=n;++i) a[i]=read();
    for(int i=n;i>=1;--i) a[i]=a[i]-a[i-1];
    build(1,1,n);

    for(int i=n;i>k;--i){
        int w=query(1,1,n,1,i);
        if(w<=0) continue;
        update(1,1,n,i-k+1,i,-ceil(w*1.0/k));
        ans+=ceil(w*1.0/k);
    }
    int t=0;
    for(int i=1;i<=k;++i) {
        int w=query(1,1,n,1,i);
        t=max(t,(int)(ceil(w*1.0/i)));
    }

    printf("%lld\n",ans+t);
    return 0;
}
```



---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1661D](luogu.com.cn/problem/CF1661D)

* **【解题思路】**

考虑贪心。

从后往前扫，每一次如果当前的 $a_i<b_i$，那么就多加一次操作，区间尾部是 $a_i$。如果前面数字不够，那么就把区间开始设为 $a_1$，不把区间为设为 $a_i$。可以知道这是最优策略。

问题变为如何快速计算出当前 $a_i$。我们可以用队列维护当前能影响到 $a_i$ 的等差数列（同一个尾部的等差数列可以压缩信息），设能影响到当前的等差序列数为 $k$，则每一个都会等差序列当前的值都会减一，总共下来就是减 $k$，即 $a_i=a_{i+1}-k$。然后，如果有等差序列已经影响不到 $a_i$，我们就将它出队。然后，如果当前 $a_i<b_i$，我们就将操作数增加并入队。

注意前 $k$ 个数要特殊处理。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>
#include <queue>

using namespace std;

array<long long,300000> target;
queue<pair<long long,long long>> points;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	long long cnt,len;
	cin>>cnt>>len;
	for(int i=0;i<cnt;i++)
		cin>>target[i];
	long long sum_inc=0,cur_sum=0,ans=0,remain=0,tmp;
	for(int i=cnt-1;i>=len;i--)
	{
		cur_sum-=sum_inc;
		if(!points.empty()&&points.front().first-i>=len)
			sum_inc-=points.front().second,points.pop();
		if(cur_sum<target[i])
			points.push(make_pair(i,tmp=(target[i]-cur_sum+len-1)/len)),sum_inc+=tmp,ans+=tmp,cur_sum+=tmp*len;
	}
	for(int i=len-1;~i;i--)
	{
		cur_sum-=sum_inc;
		if(!points.empty()&&points.front().first-i>=len)
			sum_inc-=points.front().second,points.pop();
		remain=max(remain,(target[i]-cur_sum+i)/(i+1));
	}
	cout<<ans+remain;
	return 0;
}


```

---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1661D)

## 题意

有一个 $n$ 个数的整数序列 $b_{1\sim n}$，每次可以选择一个长度为 $k$ 的**连续**子区间从左到右分别减去 $1,2,3,…,k-1,k$，求最少操作多少次可以使所有的 $b_i\le0$。

## 分析

我们先抛开如何求解，先想想怎样快速执行一次操作。

执行那么诡异的操作的数据结构肯定是没有的，不过如果我们求出 $b$ 数组的**差分数组的相反数数组** $a_i=b_{i-1}-b_{i}$，那么一次操作 $[l,r]$ 就相当于把 $a_{l\sim r}$ 加 $1$，再把 $a_{r+1}$ 减去 $k$，且 $b_i=-\sum_{j=1}^ia_j$，转化成了我们常见的形式，我这里使用了一种直观而通用的数据结构——~~树状数组~~**分块**。

接下来尝试求解，第一种容易想到的思路是我们从 $1\sim n$ 分别考虑每个 $b_i$，在之前做过的操作的基础上执行 $b_i$ 次操作 $[i,i+k-1]$ 使 $b_i\le0$，并对后面的数产生影响，边界情况要特殊处理。

不过这个做法过不了最后一个样例，显然到 $b_i$ 时每次操作只减少 $1$ 是一个极大的浪费，为了尽可能节省次数，我们可以倒序执行操作，在前面的基础上，对于每个 $b_i$，执行 $\left\lceil\frac{b_i}{k}\right\rceil$ 次 $[i-k+1,i]$，边界情况仍要特殊处理。

倒序处理还有一个好处，就是当处理 $b_i$ 时，$b_{i+1\sim n}$ 已经处理完了，因此将 $a_{i+1}$ 减去 $k$ 这个过程可有可无，我们可以偷懒省略掉。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=3e5+10;
int n,k;
ll b[N],a[N],ad[N],sum[N],len,ans;
void add(int l,int r,ll v){//分块的区间修改 
	int kl=l/len,kr=r/len;
	if(kl==kr){
		for(int i=l;i<=r;i++){
			a[i]+=v;
			sum[kl]+=v;
		}
		return;
	}
	for(int i=l;i<=kl*len+len-1;i++){
		a[i]+=v;
		sum[kl]+=v;
	}
	for(int i=kl+1;i<kr;i++){
		ad[i]+=v;
		sum[i]+=len*v;
	}
	for(int i=kr*len;i<=r;i++){
		a[i]+=v;
		sum[kr]+=v;
	}
}
ll ask(int l,int r){//分块的区间求和 
	ll ans=0;
	int kl=l/len,kr=r/len;
	if(kl==kr){
		for(int i=l;i<=r;i++)
			ans+=a[i]+ad[kl];
		return ans;
	}
	for(int i=l;i<=kl*len+len-1;i++)
		ans+=a[i]+ad[kl];
	for(int i=kl+1;i<kr;i++)
		ans+=sum[i];
	for(int i=kr*len;i<=r;i++)
		ans+=a[i]+ad[kr];
	return ans;
}
int main(){
	n=read();k=read();
	len=sqrt(n);
	for(int i=1;i<=n;i++){
		b[i]=read();
		add(i,i,0-b[i]+b[i-1]);
	}
	for(int i=n;i>=1;i--){
		ll v=ask(1,i);//v就是b[i] 
		if(v>=0)//已经满足要求就不用计算 
			continue;
		v=-v;//把负数改为正数便于计算 
		if(i>=k){
			add(i-k+1,i,(v/k)+(v%k>0));//(v/k)+(v%k>0)相当于v/k向上取整
			ans+=(v/k)+(v%k>0);
		}
		else{//边界情况 
			add(1,k,(v/i)+(v%i>0)); 
			ans+=(v/i)+(v%i>0);
		}
	}
	write(ans);
	return 0;
}
```


---

