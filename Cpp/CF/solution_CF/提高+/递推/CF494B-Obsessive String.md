# Obsessive String

## 题目描述

给定两个字符串 $s$ 和 $t$。定义一种合法的截取方案为，在字符串 $s$ 中截取若干（大于 $0$）个互不相交的子串，满足 $t$ 是每个这些子串的子串。

请你输出总方案数模 $10^9 + 7$ 的值。

## 说明/提示

保证 $1 \leq |s|, |t| \leq 10^5$，字符串中只包含小写拉丁字母。

## 样例 #1

### 输入

```
ababa
aba
```

### 输出

```
5
```

## 样例 #2

### 输入

```
welcometoroundtwohundredandeightytwo
d
```

### 输出

```
274201
```

## 样例 #3

### 输入

```
ddd
d
```

### 输出

```
12
```

# 题解

## 作者：RainFestival (赞：12)

$\tt{codeforces}$ 评分 $2000$。

题意：

给你一个字符串 $s$ 和一个字符串 $t$。

求选取任意数量 $(\ge 1)$ 个 $s$ 的不相交的子串，使得每一个子串都包含 $t$ 的方案数，对 $1000000007$ 取模。

$|s|,|t|\le 10^5$

记 $n=|s|,m=|t|$。

记 $p\in q$ 当且仅当字符串 $p$ 是字符串 $q$ 的子串。

首先，我们可以设 $dp_i$ 为当前分配方案的最后一个子串结尾是 $s$ 串第 $i$ 个字符。

考虑枚举当前子串起点 $k$ ，上一个子串终点 $x$。

列出式子 $dp_0=1,dp_i=\sum\limits_{p=1}^{i}\sum\limits_{x=0}^{p-1}[t\in s_{p\dots i}]dp_x,i=1\dots n$。


注意可以先处理 $c_i=[t\in s_{i\dots i+m-1}]$。

这样是 $O(n^3)$ 的。

大概像这样：

```cpp
#include<cstdio>
#include<cstring>
#define mod 1000000007
char st1[100005],st2[100005];
int n,m,can[100005],dp[100005],ans=0;
int check(int x)
{
	for (int now=1;now<=m;now++) if (st2[now]!=st1[x+now-1]) return 0;
	return 1;
}
int solve(int l,int r)
{
	for (int i=l;i+m-1<=r;i++) if (can[i]) return 1;
	return 0;
}
int main()
{
	scanf("%s",st1+1);n=std::strlen(st1+1);
	scanf("%s",st2+1);m=std::strlen(st2+1);
	for (int i=1;i+m-1<=n;i++) if (check(i)) can[i]=1;
	dp[0]=1;
	for (int i=1;i<=n;i++)
    	for (int j=1;j<=i;j++) if (solve(j,i))
    		for (int k=0;k<j;k++) dp[i]=(dp[i]+dp[k])%mod;
        for (int i=1;i<=n;i++) ans=(ans+dp[i])%mod;
        printf("%d\n",ans);
        return 0;
}
```

先优化 $[t\in s_{p\dots i}]$，发现当 $i$ 一定时，只要找到一个最大的 $x$，满足 $x+m-1\le i,t\in s_{x\dots x+m-1}$，那么当且仅当 $p\le x$ 时 $[t\in s_{p\dots i}]=1$，否则 $[t\in s_{p\dots i}]=0$。

而对于每个 $i$ 寻找对应的 $x$ 可以使用 $\tt{Knuth-Morria-Pratt}$ 算法解决，记 $d_i=x$。

这样是 $O(n)$ 的。

转化成这样 $dp_0=1,dp_i=\sum\limits_{p=1}^{d_i}\sum\limits_{x=0}^{p-1}dp_x,i=1\dots n$。

还是 $O(n^3)$ 的。

大概像这样：

```cpp
#include<cstdio>
#include<cstring>
#define mod 1000000007
char st1[100005],st2[100005];
int n,m,p[100005],s[100005],d[100005],dp[100005],ans=0;
int main()
{
	scanf("%s",st1+1);n=std::strlen(st1+1);
	scanf("%s",st2+1);m=std::strlen(st2+1);
	int j=0;
	for (int i=2;i<=m;i++)
	{
		while (j&&st2[j+1]!=st2[i]) j=p[j];
		if (st2[j+1]==st2[i]) ++j;
		p[i]=j;
	}
	j=0;
	for (int i=1;i<=n;i++)
	{
		while (j&&st2[j+1]!=st1[i]) j=p[j];
		if (st2[j+1]==st1[i]) ++j;
		if (j==m) s[i]=1,j=p[j];
	}
	d[0]=0;
	for (int i=1;i<=n;i++) d[i]=(!s[i]?d[i-1]:i-m+1);
	dp[0]=1;
	for (int i=1;i<=n;i++)
    	for (int j=1;j<=d[i];j++)
    	    for (int k=0;k<j;k++)
    	        dp[i]=(dp[i]+dp[k])%mod;
    for (int i=1;i<=n;i++) ans=(ans+dp[i])%mod;
    printf("%d\n",ans);
    return 0;
}
```

然后进一步改进。

$dp_0=1$

$dp_i=\sum\limits_{p=1}^{d_i}\sum\limits_{x=0}^{p-1}dp_x,i=1\dots n$。

交换求和顺序：

$dp_i=\sum\limits_{x=0}^{d_i-1}\sum\limits_{p=x+1}^{d_i}dp_x,i=1\dots n$

$dp_i=\sum\limits_{x=0}^{d_i-1}dp_x\times (d_i-x),i=1\dots n$

记 $f_i=\sum\limits_{x=0}^{i}dp_x$，$s_i=\sum\limits_{x=0}^{i}dp_x\times x$

则 $dp_i=d_i\times f_{d_i-1}-s_{d_i-1}$

这样就可以 $O(n)$ 求了。

大概像这样:

```cpp
#include<cstdio>
#include<cstring>
#define mod 1000000007
char st1[100005],st2[100005];
int n,m,p[100005],s[100005],d[100005],dp[100005],f[100005],ss[100005];
int main()
{
	scanf("%s",st1+1);n=std::strlen(st1+1);
	scanf("%s",st2+1);m=std::strlen(st2+1);
	int j=0;
	for (int i=2;i<=m;i++)
	{
		while (j&&st2[j+1]!=st2[i]) j=p[j];
		if (st2[j+1]==st2[i]) ++j;
		p[i]=j;
	}
	j=0;
	for (int i=1;i<=n;i++)
	{
		while (j&&st2[j+1]!=st1[i]) j=p[j];
		if (st2[j+1]==st1[i]) ++j;
		if (j==m) s[i]=1,j=p[j];
	}
	d[0]=0;
	for (int i=1;i<=n;i++) d[i]=(!s[i]?d[i-1]:i-m+1);
	dp[0]=1;f[0]=1;ss[0]=0;
	for (int i=1;i<=n;i++)
	{
		if (!d[i]) dp[i]=0;
		else dp[i]=((1ll*d[i]*f[d[i]-1]%mod-ss[d[i]-1])%mod+mod)%mod;
		f[i]=(f[i-1]+dp[i])%mod;
		ss[i]=(ss[i-1]+1ll*dp[i]*i%mod)%mod;
	}
    printf("%d\n",((f[n]-1)%mod+mod)%mod);
    return 0;
}
```

$\tt{632ms,2.29MB}$，在当前 $29$ 份代码中排第 $12$。

---

## 作者：Mav11Young (赞：6)

题意：给定一个字符串$S$，和一个字符串$T$。在$S$中取出任意多个不重叠的子串，使得每个子串都包含$T$，求方案数。

这道题的难点在于定义状态。

首先考虑一个较为朴素的dp设计：
```cpp
dp[i] 表示当前子串以i为结尾的方案数
```
那么可以想到，当前子串是肯定要包含一个$T$串的，因此当前子串的左端点是要满足一定条件的。所以预处理出每个点之前从右往左第一个$T$串的左端点，记为$pos[i]$。那么当前子串的左端点的取值范围为$[1,pos[i]]$。

考虑转移。对于每一个左端点$j$，都可以继承$dp[0,1,...,j-1]$的所有信息（不重叠）。所以可以枚举左端点，再把上式累加。目前的复杂度是$O(n^3)$的。

很显然，$dp[0,1,...,j-1]$是可以用前缀和维护的，因此复杂度变为$O(n^2)$。

然后可以发现，每次枚举的左端点的区间是连续的，且$pos[i]<i$。所以这一维也可以用前缀和处理，即记录$dp[i]$前缀和的前缀和。复杂度变为$O(n)$

还有就是一些小细节：

- 找串用哈希（或者可以用KMP）
- $dp[0]$的初值赋为1，是因为转移是要用到左边为空的情况。所以最后答案要减1
- 注意取模

$Code:$
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=100005,P=1e9+7,mod=233333333;
LL n,m;
char s[N],t[N];
LL Pow[N],hsh[N];
LL Hash=0;
LL get(LL l,LL r){
	return (hsh[r]-hsh[l]*Pow[r-l]%mod+mod)%mod;
}
namespace P1{
	LL pos[N],dp[N],f[N];
	void solve(){
		for(LL i=1;i<=n;i++){
			if(i>=m&&get(i-m,i)==Hash)pos[i]=i-m+1;
			else pos[i]=pos[i-1];
		}
		dp[0]=f[0]=1;
		for(LL i=1;i<=n;i++){
			dp[i]=dp[i-1];
			if(pos[i])dp[i]=(dp[i]+f[pos[i]-1])%P;
			f[i]=(f[i-1]+dp[i])%P;
		}
		printf("%lld\n",(dp[n]-1+P)%P);
	}
}
int main(){
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	Pow[0]=1;
	for(LL i=1;i<=n;i++){
		hsh[i]=(hsh[i-1]*233+s[i]-'a'+1)%mod;
		Pow[i]=Pow[i-1]*233%mod;
	}
	for(LL i=1;i<=m;i++)
		Hash=(Hash*233+t[i]-'a'+1)%mod;
	P1::solve();
	return 0;
}
```
总的来说，这道题只要想到了dp状态，以及通过枚举左端点的转移，后面的优化就都不难想了。对于这种区间/子串的题要多从端点处考虑。

---

## 作者：djh0314 (赞：5)

[**传送门**](https://www.luogu.com.cn/problem/CF494B)。

## 题意

给定一个字符串 $S$，和一个字符串 $T$。      

在 $S$ 中取出任意多个不重叠的子串，使得每个子串都包含 $T$，求方案数。

## 分析

先分析一下题目，显然，我们使用 DP 来解决这道题。

设计一个状态：$f_i$，$f_i$ 表示最后一个串的最后一位是 $i$ 的方案数。

我们可以枚举最后一个子串的区间，进行转移。

首先要考虑的是，如何判断区间是否包含 $T$。

我们考虑使用字符串哈希，将整一个匹配串哈希，再标记每一个区间，最后，预处理出当前左侧的第一个匹配串，令其为 $L_i$，因此只要左端点处于 $1\sim L_i-m+1$，我们的区间就可以包含 $T$。

~~~cpp
p[0]=1;
for(int i=1; i<=n; ++i) p[i]=p[i-1]*P;
for(int i=1; i<=n; ++i) a[i]=a[i-1]*P+s[i];
for(int i=1; i<=m; ++i) wh=wh*P+t[i];
for(int i=m; i<=n; ++i) if(query(i-m+1,i)==wh) mark[i]=1;
for(int i=m; i<=n; ++i) L[i]=mark[i]?i:L[i-1];
~~~

枚举了我们这一个区间后，考虑继承前面的 $f$。

令枚举的左端点为 $j$，右端点为 $i$。

我们的 $f_i$ 就可以继承 $\forall k\in \left [ 1,j-1 \right ] $ 的 $f$。

~~~cpp

for(int i=1; i<=n; ++i) {
	if(!L[i]) continue;
	for(int j=1; j<=L[i]-m+1; ++j) {
		f[i]++;
		for(int k=1; k<=j-1; ++k) f[i]=(f[i]+f[k])%MOD;
	}
}
for(int i=1; i<=n; ++i) tot=(tot+f[i])%MOD;
~~~

时间复杂度：$O(n^3)$。

接下来考虑优化这个 DP，首先将 $k$ 优化掉。

怎么优化呢，使用前缀和。

~~~cpp
for(int i=1; i<=n; ++i) {
	if(!L[i]) continue;
	for(int j=1;j<=L[i]-m+1;++j) f[i]=(f[i]+qzh[j-1]+1)%MOD;
	qzh[i]=(qzh[i-1]+f[i])%MOD;
}
~~~

时间复杂度：$O(n^2)$。

显然，我们依旧使用前缀和来优化。

~~~cpp
for(int i=1; i<=n; ++i) {
	if(!L[i]) continue;
	f[i]=(sum[L[i]-m]+L[i]-m+1)%MOD;
	qzh[i]=(qzh[i-1]+f[i])%MOD;
	sum[i]=(sum[i-1]+qzh[i])%MOD;
}
~~~

时间复杂度：$O(n)$。

此时就可以愉快的 A 掉此题了。

### 总结一下，这题的重点其实是在优化 DP 上，还附带了一点点的字符串哈希即可。



---

## 作者：忆殇 (赞：2)

先说明一下本题的题意，因为题目太难读了。。。题目大意:给出两个字符串，

求有多少个字符串，包含二串，且为一串的子串，而且互相不重叠，解释一下样例。

一串：ddd

二串：d

这里将一串的ddd分别标号为123

答案为：1 ， 2， 3， 12 3 ，1 23 ， 123 ，1 2，2 3，1 3 ，12 ，23 ，1 2 3。

看到这应该有一些思路了吧，这道题支持两种算法。但是目的是一样的。

用kmp匹配二串在一串中完全成功匹配的位置，设这个位置为flag[i] = 1。

这个会kmp应该不用说了吧，hash的话可以直接判断s1[i-l2+1] == s2时进行操作

至于dp，先介绍一下各数组的含义，f代表以目标串s2为结尾的串的个数，

sum1为f的前缀和，sum2为sum1的前缀和

如果这个位为结尾时没有匹配那么直接f[i] = f[i-1],把这个值传下去。

那么如果i位为结尾时匹配到s2，f[i] = sum2[i-l2]+i-l2+1.

因为以这个这个位为结尾是包含二串的串的开头可以从1~i-l2+1，所以一共有i-l2+1种方案

是只有一个包含这个二串的串的。

而如果有多个呢。

我们可以感性yy一下，当前串起点为2~i-l2+1时，上一个和他组合的串的结尾可以为1~i-l2

如果上一个串终点为k，那么1~k都可以和当前串组合。这就是sum1的含义

因为结尾为1~i-l2，所以sum2为sum1的合
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define mode 1000000007
#define seed 13131
using namespace std;
typedef long long ll;
char s1[100005];
char s2[100005];
unsigned long long p1[100005];
unsigned long long ss1[100005];
unsigned long long ss2;
ll f[100005];
ll sum1[100005];
ll sum2[100005];
int main()
{
    scanf("%s",s1+1);
    scanf("%s",s2+1);
    int l1 = strlen(s1+1),l2 = strlen(s2+1);
    p1[0] = 1;
    for(int i = 1;i <= l1;i++)
    {
        p1[i] = p1[i-1]*seed;
        ss1[i] = ss1[i-1]*seed+s1[i]-'a'+1;
    }
    for(int i = 1;i <= l2;i++)
    {
        ss2 = ss2*seed+s2[i]-'a'+1;
    }
    for(int i = 1;i <= l1;i++)
    {
        if(i-l2+1 >= 1)
        {
            if(ss1[i]-p1[l2]*ss1[i-l2] == ss2)
            {
                f[i] = sum2[i-l2]+i-l2+1;
                f[i] %= mode;
            }else
            {
                f[i] = f[i-1];
            }
            sum1[i] = sum1[i-1]+f[i];
            sum2[i] = sum2[i-1]+sum1[i];
        }
    }
    ll ans = 0;
    for(int i = 1;i <= l1;i++)
    {
        ans += f[i];
        ans %= mode;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：木xx木大 (赞：1)

[CF494B Obsessive String](https://www.luogu.com.cn/problem/CF494B)

本篇题解思路和代码与最后一篇题解差不多，再加上了一些我自己的理解

设两个字符串为 S , T ，长度分别为 $n$ ,$m$ 。首先我们在原串中查找所有的位置 $i$ ，使 S 中以 $i$ 为结尾的子串与 T 匹配。对于所有的位置 $i$ ，如果能以 $i$ 为结尾匹配，标记 $flag[i]=1$ 。这部分可以通过哈希或者 kmp 完成。

然后进行dp：设 $dp[i]$ 表示选取的最后一个集合的结尾为 $i$，开头为 $j$（ $j$ 不体现在状态中，$1\le j\le i-m+1$）的所有方案数。那么答案就是$\sum_{i=1}^{n} dp[i]$。

转移：首先，对于某一位置，如果 $flag[i]=0$，我们有：$dp[i]=dp[i-1]$。即如果到这一位置没有匹配上，那么说明这个位置只能被包含在前一个状态中。

如果 $flag[i]=1$，说明 $[i-m+1,i] $ 与 t 是可以完全匹配的。如果这个集合中新增一个元素，从1到 $i-m+1$ 都可以作为这个元素的起点，方案数为 $i-m+1$ 。原集合中如果有两个以上元素，最后一个元素的起点可以为$[2,i-m+1]$，如果它的起点为 $k$ ，那么上一个元素的终点可以是$[1,k-1]$，总方案数就是$\sum_{i=1}^{k-1} dp[i]$。可以用一个前缀和 $s$ 来维护。

而由于最后一个元素的起点可以是$[2,i-m+1]$，所以一共的总方案数就是 $\sum_{i=2}^{i-m+1}s[i-1]$，即$\sum_{i=1}^{i-m}s[i]$。发现这也是一个前缀和的形式，于是我们把 $s$ 维护成一个前缀和 $s2$ 。那么转移为：$dp[i]=i-m+1+s2[i-m]$。答案为 $s[n]$ 。




```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long 
using namespace std;
const int N=1e5+5;
const int mo=1e9+7;
const ull sed=20040509;
char s1[N],s2[N];
bool fl[N];
ull h[N],ha;
ll dp[N],sum1[N],v=1,sum2[N];
int main()
{
	scanf("%s%s",s1+1,s2+1);
	int n=strlen(s1+1),m=strlen(s2+1);
	for(int i=1;i<=n;i++)
		h[i]=h[i-1]*sed+s1[i]-'a'+1;
	for(int i=1;i<=m;i++)
	{
		ha=ha*sed+s2[i]-'a'+1;
		v*=sed;
	}
	for(int i=m;i<=n;i++)
	{
		ull now=h[i]-h[i-m]*v;
		if(now==ha)fl[i]=1;
	}
	for(int i=1;i<=n;i++)
	{
		if(!fl[i])dp[i]=dp[i-1];
		else dp[i]=(i-m+1+sum2[i-m])%mo;
		sum1[i]=(sum1[i-1]+dp[i])%mo;
		sum2[i]=(sum2[i-1]+sum1[i])%mo;
	}
	printf("%lld",sum1[n]);
	return 0;
}
```



 

---

## 作者：leozhang (赞：1)

很有趣的一道题

这道题提议很难懂，其实就是让你求合法的集合数目。合法的集合定义为：

1、集合中的所有串都是s的子串，且互不重叠 2、集合中的所有串都含有子串t。

看到网上很多题解说要用kmp，但我就不用...

因为仅需进行一个字符串匹配，而hash是很好写的匹配啊

而且kmp的next指针在dp中并没有起到作用。

说一下主体思路吧：

设两个字符串为s，t，长度分别为l1,l2

首先我们在原串中查找所有的位置i，使s中以i为结尾的子串与t匹配

对于所有的位置i，标记flag[i]=1;

然后我们进行dp

设dp[i]表示以选取的最后一个集合的结尾为i，开头为j（j不体现在状态中，1<=j<=i-l2+1）的所有方案数

那么答案就是∑（i=1~l1）dp[i]

接下来我们考虑转移

首先，对于某一位置，如果flag[i]=0，我们有：

dp[i]=dp[i-1]

原因：如果到这一位置没有匹配上，那么说明这个位置只能被包含在前一个状态中。

那么，如果flag[i]=1，怎么办？

我们考虑集合中元素的个数：

如果只有一个元素，那么由于flag[i]=1，说明i-l2+1~i与t是可以完全匹配的，所以从1到i-l2+1都可以作为这个元素的起点，所以方案数为i-l2+1

如果有两个以上元素，那么最后一个元素的起点就可以是2~i-l2+1

那么我们设这个起点是k

于是上一个元素的终点就可以是1~k-1

所以如果终点是k，总方案数就是∑(i=1~k-1)dp[i]

那这个东西就可以用一个前缀和s来维护

而由于终点可以是2~i-l2+1，所以一共的总方案数就是：

∑（i=2-i-l2+1）s[i-1]

也就是：

∑(i=1-i-l2)s[i]

发现这也是一个前缀和的形式，于是我们把s维护成一个前缀和ss

结合以上两个分析，得到转移为：

dp[i]=i-l2+1+ss[i-l2]

边递推边维护即可。

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#define seed 13131
#define ull unsigned long long
#define mode 1000000007
#define ll long long
using namespace std;
ll dp[100005];
ll s1[100005];
ll s2[100005];
char s[100005];
char t[100005];
ull has,has1[100005];
ull v;
bool flag[100005];
int main()
{
	scanf("%s%s",s+1,t+1);
	v=1;
	int l1=strlen(s+1),l2=strlen(t+1);
	for(int i=1;i<=l1;i++)
	{
		has1[i]=has1[i-1]*seed+s[i]-'a'+1;
	}
	v=1;
	for(int i=1;i<=l2;i++)
	{
		has=has*seed+t[i]-'a'+1;
 		v*=seed;
	}
	for(int i=l2;i<=l1;i++)
	{
		int st=i-l2;
		ull hast=has1[i]-has1[st]*v;
		if(hast==has)
		{
			flag[i]=1;
		}
	}
	for(int i=1;i<=l1;i++)
	{
		if(!flag[i])
		{
			dp[i]=dp[i-1];
		}else
		{
			dp[i]=((i-l2+1)+s2[i-l2])%mode;
		}
		s1[i]=(s1[i-1]+dp[i])%mode;
		s2[i]=(s2[i-1]+s1[i])%mode;
	}
	printf("%lld\n",s1[l1]);
	return 0;
}
```

---

## 作者：Roshin (赞：0)

### 给一份看起来字数比较少的题解？

### 题意

给一个字符串 $s$，和一个字符串 $t$。在 $s$ 中取出任意多个不重叠的子串 （可以有子串没有被取出），使得每个子串都包含 $t$ ，求方案数。

具体题意见原题面。

### 思路

+ 由于需要每个子串中都包含 $t$，必然需要一个字符串匹配算法，kmp 或者 hash 找出来所有的匹配位置即可，代码中用 pos 来记录了所有位置。
+ 求方案数考虑下 dp，注意题目图片中的公式，每一小段 $ab$ 序列，都由**一个** $b_i$ 来结尾。
+ **设计状态**：$dp_i$ 表示后面子串不取，只考虑前 $i$ 个字符，第 $i$ 位作为 $b_x$ 的方案数。
+ **考虑转移**：若 $i$ 位作为 $b_x$ ，那么我们需要找到对应的 $a_x$ ，显然 $a_x$ 到 $b_x$ 势必包含一个匹配位置，可以二分或者线性记录找到对应的最近匹配位置 $p$ 。
  + 如果没有找到一个匹配位置。
  $$dp_i:=0$$
  + 否则有一个显然的方案，整个子串只有一个 ab 序列。
  $$\mathit{dp}_{i,j} := p$$
  + 然后考虑从前面的状态转移，设 $i$ 对应 b 序列前一个 $b_y$ 在下标 $j$ ，则 
  $$dp_i = dp_i + dp_j \times (p - j)$$
  + 解释一下转移，对于下标 [j+1, p] 位置的所有下标，都可以作为 $b_x$ 对应的 $a_x$ ，再用乘法原理计算。
  + 发现对于任意 $j \leq p-1$ 都有以上转移，即
  $$dp_i =dp_i+ (\sum_{j=1}^{p-1} (p - j) \times dp_j)$$
  + 发现可以前缀和优化，维护 $i \times dp_i$ 和 $dp_i$ 两个前缀和即可。
+ 时间复杂度 $O(n)$，代码中的二分查找可以优化掉，~~这里就懒得写了~~。

  
### Code

```cpp
const int N = 1e5 + 10, mod = 1e9 + 7;
ll dp[N], pre[N], ipre[N];
// dp[i] 表示第 i 位作为 b_j 的方案数。pos 记录匹配起始位置
int main() {
    string s, t;
    IOS;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    s = " " + s, t = " " + t;
    kmp.get_ne(t.c_str(), SZ(t) - 1);
    pos.pb(-m);
    kmp.match(s.c_str(), t.c_str(), n, m);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1];
        ipre[i] = ipre[i - 1];
        auto p = *prev(upper_bound(ALL(pos), i - m + 1));
        if (p == pos[0]) continue;
        dp[i] = p;
        dp[i] = (dp[i] + p * pre[p - 1] % mod - ipre[p - 1] + mod) % mod;
        pre[i] += dp[i];
        ipre[i] = (ipre[i] + i * dp[i]) % mod;
        if (pre[i] >= mod) pre[i] -= mod;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) ans = (ans + dp[i]) % mod;
    printf("%lld\n", ans);
    return 0;
}
```


---

## 作者：a___ (赞：0)

我来写一下我自己的做法。   

规定：字符串中左边是小的、前面；右边是大的、后面；字符串位置从1标起。

1. 题意：   
	给定字符串 ` S ` 和字符串 ` T ` ，求 在 ` S ` 中选择 **若干个（至少一个）** 互不相交（**不能有重复** 选的位置，但 **可以有空选** 位置）的 **包含 ` T ` 的** **子串** ，有 **多少种** 不同的选法。（这题翻译好像出了点问题。。。）   
	- 对样例 #3 的解释：（中括号里的是所在位置）  
    - ` S ` : $ \mathtt{d_{[1]}d_{[2]}d_{[3]}} $   
    - ` T ` : $ \mathtt{d} $   
    - 方案：$ \{\mathtt{d_{[1]}}\} $，$ \{\mathtt{d_{[1]}d_{[2]}}\} $，$ \{\mathtt{d_{[1]}d_{[2]}d_{[3]}}\} $，$ \{\mathtt{d_{[2]}}\} $，$ \{\mathtt{d_{[2]}d_{[3]}}\} $，$ \{\mathtt{d_{[3]}}\} $，$ \{\mathtt{d_{[1]},d_{[2]}}\} $，$ \{\mathtt{d_{[2]},d_{[3]}}\} $，$ \{\mathtt{d_{[1]},d_{[3]}}\} $，$ \{\mathtt{d_{[1]},d_{[2]}d_{[3]}}\} $，$ \{\mathtt{d_{[1]}d_{[2]},d_{[3]}}\} $，$ \{\mathtt{d_{[1]},d_{[2]},d_{[3]}}\} $。

1. 思路：   
	考虑字符串 ` S ` 中的每一个字符 $ s_i $，如果我们知道 所有选法中 **所选的最后一个字符串 的结尾在 $ [1,i-1] $ 中 的数量 $ sum $** ，以及 **以位置 $ i $ 开头的字符串中 包含 ` T ` 的最早位置 $ x $** ，那么依据题意，我们可以发现，可以选择所有 **单个字符串** $ s_{i...x}, s_{i..x+1}, ..., s_{i...n} $ （因为都包含 ` T `），同时可以在选择这其中的任意一个串的时候 **一并加上** 之前的 $ sum $ 种选法的 **任意一种** （因为不重叠）。   
    例如， ` S ` 是 $ \mathtt{aaaabcaa} $， ` T ` 是 $ \mathtt{abc} $，在位置 $ 3 $ 开始向后选单个字符串只有 $ \{\mathtt{aabc}\} $，$ \{\mathtt{aabca}\} $，$ \{\mathtt{aabcaa}\} $ 是符合要求的。    
    例如， ` S ` 是 $ \mathtt{abaabaa} $， ` T ` 是 $ \mathtt{ab} $，在位置 $ 3 $ 开始向后选单个字符串只有 $ \{\mathtt{aab}\} $，$ \{\mathtt{aaba}\} $，$ \{\mathtt{aabaa}\} $ 是符合要求的；而在位置 $ 3 $ 前面有方案 $ \{\mathtt{ab}\} $，于是方案 $ \{\mathtt{ab},\mathtt{aab}\} $，$ \{\mathtt{ab},\mathtt{aaba}\} $，$ \{\mathtt{ab},\mathtt{aabaa}\} $ 也符合要求。    
    例如， ` S ` 是 $ \mathtt{abaab} $， ` T ` 是 $ \mathtt{ab} $，在位置 $ 4 $ 开始向后选单个字符串只有 $ \{\mathtt{ab}\} $ 是符合要求的；而在位置 $ 4 $ 前面有方案 $ \{\mathtt{ab}\} $，$ \{\mathtt{aba}\} $，于是方案 $ \{\mathtt{ab},\mathtt{ab}\} $，$ \{\mathtt{aba},\mathtt{ab}\} $ 也符合要求。    

1. 做法：   
	考虑先用 kmp（或 hash）得出 ` T ` 在 ` S ` 中的所有匹配位置，设为 $ [l_{1...tot},r_{1...tot}] $ 。（这点不会的自己去[P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)）   
    这时，可以发现每个位置 $ i $ 后的第一个 $ l_j $ 对应的 $ r_j $ 即为前面所说的最小位置 $ x_i $，所以我们先预处理出 $ x_{1...n} $。   
    然后是关键部分，即怎样维护一个 “所选的最后一个字符串结尾在 $ [1,i-1] $ 中的数量 $ sum_i $” 。我们发现，假如我们知道 所有位置 $ j \in [1,i-1] $ 的 $ sum_j $ 以及 $ x_j $ 我们可以更新出所有最后一个串从 $ j $ 开始的方案（如上2.）。这样，从 $ 1 $ 更新到 $ i-1 $ 就一定可以得出在 $ i $ 之前结束（因为在 $ i $ 之前开始）的所有方案。而得到在一个位置结束的方案数显然的办法是每次更新在相应位置加上方案数（将这个结果记为 $ a_{1...n} $，则为 $ a_k = a_k + sum_j + 1 (k \in [x_j,n]) $）。这样，由于后面不会向前更新，在 $ i-1 $ 位置结束的方案数必定已全部得出，则 $ sum_i = sum_{i-1}+a_{i-1} $。显然 $ sum_1 = 0 $，所以 $ sum_{2..n+1} $ 可求，而 $ sum_{n+1} $ 即为答案。   
    由于上面的过程实际为将 $ [x,n] $ 位置记录的数值加上 $ sum + 1 $，所以我们可以使用差分轻松解决（原理一样是只从前向后更新，不影响前面计算好的结果）。    
    时间复杂度 $ \mathbf{O}(n) $。

实际代码实现如下：
```cpp
#include<cstdio>
const int N=1e5+10,p=1e9+7;
int n,m,c[N],nxt[N],x[N],sum;
char s[N],t[N];
int main()
{
    int i,j;
    do s[1]=getchar(); while(s[1]<=32);
    for(n=0;s[n+1]>32;n++)s[n+2]=getchar();
    do t[1]=getchar(); while(t[1]<=32);
    for(m=0;t[m+1]>32;m++)t[m+2]=getchar();
    //读入
    for(nxt[0]=-1,i=1;i<=m;nxt[i++]++)
        for(nxt[i]=nxt[i-1];(~nxt[i])&&t[nxt[i]+1]!=t[i];nxt[i]=nxt[nxt[i]]);
    for(i=1,j=0;i<=n+1;i++,j++)
    {
        if(j==m)x[i-m]=i-1;
        if(s[i]!=t[j+1])  for(j=nxt[j];(~j)&&s[i]!=t[j+1];j=nxt[j]);
    }
    //kmp（也可以 hash ，但我觉得 kmp 好写）
    for(x[n+1]=n+1,i=n;i;i--)
    if(!x[i])x[i]=x[i+1];
    //求x[i]
    for(i=1;i<=n;i++)
    {
        c[x[i]]=(c[x[i]]+sum+1)%p;//差分
        c[i]=(c[i]+c[i-1])%p;//求a[i]
        sum=(sum+c[i])%p;//sum[i] -> sum[i+1]
    }
    printf("%d\n",sum);
    return 0;
}
```

---

