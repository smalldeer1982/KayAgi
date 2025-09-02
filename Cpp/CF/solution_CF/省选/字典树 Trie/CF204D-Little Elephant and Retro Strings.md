# Little Elephant and Retro Strings

## 题目描述

The Little Elephant has found a ragged old black-and-white string $ s $ on the attic.

The characters of string $ s $ are numbered from the left to the right from $ 1 $ to $ |s| $ , where $ |s| $ is the length of the string. Let's denote the $ i $ -th character of string $ s $ as $ s_{i} $ . As the string is black-and-white, each character of the string is either letter "B", or letter "W". Unfortunately, the string is very old and some characters are damaged. The damaged positions are denoted as "X".

The Little Elephant in determined to restore the string and hang it on the wall. For that he needs to replace each character "X" by a "B" or a "W". The string must look good on the wall, so it must be beautiful. The Little Elephant considers a string beautiful if it has two non-intersecting substrings of a given length $ k $ , such that the left one fully consists of characters "B", and the right one fully consists of characters "W". More formally, there are four integers $ a,b,c,d $ $ (1<=a<=b<c<=d<=|s|; b-a+1=d-c+1=k) $ such that $ s_{i} $ = "B" $ (a<=i<=b) $ and $ s_{j} $ = "W" $ (c<=j<=d) $ .

Help the Little Elephant find the number of different beautiful strings he can obtain from string $ s $ . Two strings are considered different if there is such position, where the character in the first string differs from the corresponding character in the second string. If this string doesn't contain characters «X» and it is already beautiful — the answer is 1.

As the answer can be rather large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
3 2
XXX
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4 2
XXXX
```

### 输出

```
1
```

## 样例 #3

### 输入

```
10 2
XXBXXWXXXX
```

### 输出

```
166
```

# 题解

## 作者：chengni (赞：4)

模拟赛做的一道题，跟这个差不多，正好给那道题写了个题解，顺便也放到这里了。

初始思路便是用 f[i] 表示以 i 为结尾的正好满足 B 要求的方案数，但是奈何没想明白怎么去转移。

先定义几个数组。

f 数组表示i-k+1到i全部为 B 的且之前未满足该条件的方案数，g[i]表示 i 到 i+k-1 全部为W 且之后未满足该条件的方案数。

t1 数组为第 i 天及以前满足 B 要求的方案数，t2 数组表示第 i 天及以后满足 W 要求的方案数。

po 数组在第一次循环中为 1 到 i 所有可能的方案数，第二次循环表示从 i 到 n 所有可能的方案数。

sum 数组在第一次循环中是 f 数组的前缀和，第二次循环中是 g 数组的后缀和。

为了保证 f 数组中不会出现重复的情况，我们求 f 数组的式子为


```cpp
f[i]=po[i-k]-t1[i-k]-(sum[i-1]-sum[i-k]+p);
```

稍微推一下吧。g 数组的求法类似。

很明显答案为所有 f[i] x t2[i+1] 的总和。

在计算过程中需要非常小心取模。

还有就是在计算所有可行方案数的时候判断，如果这一位没有定义，那么需要乘以二。

大概就是这里。

```cpp
if(c[i]=='X') po[i]=(po[i-1]*2)%p;
else po[i]=po[i-1];
if(c[i]=='X') t1[i]=(t1[i-1]*2+f[i])%p;
else t1[i]=(t1[i-1]+f[i])%p;
```
第一个循环和第二个循环大致思想相同，只是一波逆操作。

代码看起来就是这个样子，判断这一位的字母是什么，再进行操作。

```cpp
	int n=read(),k=read();
	scanf("%s",c+1);
	po[0]=1;
	int s=0; 
	for(int i=1;i<=n;i++){
		if(c[i]=='W') s=0;
		else s++;
		if(s>=k){
			f[i]=((po[i-k]-t1[i-k]+p)%p-(sum[i-1]-sum[i-k]+p)%p+p)%p;
		}
		if(c[i]=='X') po[i]=(po[i-1]*2)%p;
		else po[i]=po[i-1];
		if(c[i]=='X') t1[i]=(t1[i-1]*2+f[i])%p;
		else t1[i]=(t1[i-1]+f[i])%p;
		sum[i]=(sum[i-1]+f[i])%p;
	}
	po[n+1]=1;s=0;
	for(int i=n;i>=1;i--){
		if(c[i]=='B') s=0;
		else s++;
		if(s>=k){
			g[i]=((po[i+k]-t2[i+k]+p)%p-(sum[i+1]-sum[i+k]+p)%p+p)%p;
		}
		if(c[i]=='X') po[i]=(po[i+1]*2)%p;
		else po[i]=po[i+1];
		if(c[i]=='X') t2[i]=(t2[i+1]*2+g[i])%p;
		else t2[i]=(t2[i+1]+g[i])%p;
		sum[i]=(sum[i+1]+g[i])%p;
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		ans=(ans+f[i]*t2[i+1])%p;
	}
	cout<<ans;
```

---

## 作者：chlchl (赞：2)

题解区题解普遍老化，补一篇新的，顺便记录一下这类做题方式。

## Solution
难点是啥？显然在于一个字符串，其可能会有多个位置都满足题目的那个条件，直接计算很容易重复。

所以对于这类问题，常见的做法是令每个字符串只在第一次满足这个条件的位置产生贡献，以达到去重的效果。

所以设 $f_i$ 为 $[i-k+1,i]$ 全部为 ``B``，且 $[1,i-1]$ 不存在连续 $k$ 个位置都为 ``B`` 的方案数。这个 $i$ 就是字符串第一次满足条件的位置了。

考虑转移 $f_i$，显然 $[i-k+1,i]$ 的填发是唯一的，所以从 $f_{i-k}$ 转移过来。此时发现仅凭 $f$ 是无法转移的，因为我们需要求出前 $i-k$ 个位置都不满足条件的方案数。

正难则反，$tot_i$ 表示 $[1,i]$ 随便填的方案数，$res1_i$ 表示 $[1,i]$ 已经符合条件（但不强制是以 $i$ 为结尾的后缀第一次符合）的方案数。

那么看起来 $tot_{i-k}-res1_{i-k}$ 就能转移了？其实不然，因为还需要满足的是，不能存在 $j\in[i-k+1,i-1]$，使得 $[j-k+1,j]$ 全 ``B``，因此需要减去 $\sum\limits_{j=i-k+1}^{i-1}f_j$。

剩下的那几个数组也挺好转移的：
- $f_{i}=tot_{i-k}-res1_{i-k}-\sum\limits_{j=i-k+1}^{i-1}f_j$，当且仅当 $[i-k+1,i]$ 有可能为全 ``B`` 的时候才可以转移；
- $tot_i=tot_{i-1}\times k$，$k$ 在 $s_i=$ ``X`` 的时候为 $2$，否则为 $1$；
- $res1_i=res1_{i-1}\times k+f_i$，$k$ 的意义同上。

然后 $f$ 可以用前缀和优化，时间复杂度可以做到线性。

那么类似地，设 $g_i$ 为 $[i,i+k-1]$ 全部为 ``W``，且 $[i+k,n]$ 不存在连续 $k$ 个位置都为 ``W`` 的方案数，$tot_i$ 表示 $[i,n]$ 随便填的方案数，$res2_i$ 表示 $[i,n]$ 已经符合条件（但不强制是以 $i$ 为开头的前缀第一次符合）的方案数。

同理，也可以得到类似 $f$ 的转移，留给读者自行思考。

最后的答案也很容易统计，为 $\sum\limits_{i=0}^{n-1}f_i\times res2_{i+1}$。

时间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll MOD = 1e9 + 7;
const int N = 1e6 + 10;
int n, k;
ll f[N], g[N], tot[N], pre[N], suf[N], res1[N], res2[N];
char s[N];

int main(){
	scanf("%d%d", &n, &k);
	scanf("%s", s + 1);
	int now = 0; tot[0] = 1;
	for(int i=1;i<=n;i++){
		now = (s[i] == 'W' ? 0 : now + 1);
		if(now >= k)//合法才能转移 
			f[i] = ((tot[i - k] - res1[i - k] - (pre[i - 1] - pre[i - k] + MOD)) % MOD + MOD) % MOD;
		res1[i] = (res1[i - 1] * (s[i] == 'X' ? 2 : 1) + f[i]) % MOD;
		pre[i] = (pre[i - 1] + f[i]) % MOD;
		tot[i] = tot[i - 1] * (s[i] == 'X' ? 2 : 1) % MOD;
	}
	memset(tot, 0, sizeof(tot));
	tot[n + 1] = 1;
	for(int i=n;i>=1;i--){
		now = (s[i] == 'B' ? 0 : now + 1);
		if(now >= k)//合法才能转移 
			g[i] = ((tot[i + k] - res2[i + k] - (suf[i + 1] - suf[i + k] + MOD)) % MOD + MOD) % MOD;
		res2[i] = (res2[i + 1] * (s[i] == 'X' ? 2 : 1) + g[i]) % MOD;
		suf[i] = (suf[i + 1] + g[i]) % MOD;
		tot[i] = tot[i + 1] * (s[i] == 'X' ? 2 : 1) % MOD;
	}
	ll ans = 0;
	for(int i=0;i<n;i++)
		(ans += f[i] * res2[i + 1] % MOD) %= MOD;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：MCAdam (赞：1)

[题目](https://www.luogu.com.cn/problem/CF204D)

题意：将给定的字符串中的$X$替换为$B$或$W$，求生成出来的字符串存在长度为$k$的$B$子串和$W$子串，且$B$子串在$W$子串左边的方案数

$1\leq k\leq n\leq 10^6$

首先统计出每个$B$和$X$求出左边离它最近的$W$在哪里，如果它们之间的距离超过$k$，就直接取$k$；同理，求出每个$W$和$X$求出右边离它最近的$B$在哪里

注意到$n\leq 10^6$，所以可以先单独考虑$B$区间和$W$区间的贡献，乘起来后再除掉多余的部分。假设当前要算以$r$为结尾的$B$区间的个数，方案数是$2^{\text{前后X的个数}}$？这样计算，如果$r$往后一位，那么在$r$的这个方案在$r+1$也会被算到

所以为了避免重复计算，应该保证每个合法的区间只出现一次

如果当前考虑的是$[l,r]$这个$B$区间，那么它的方案数应该是$[l,r]$前面不合法的方案数乘上$[l,r]$右边$2^{\text{右边X的个数}}$，之所以不能反过来是因为到时还要考虑$W$子串的方案数，$W$子串就是左边$X$的个数

每次找到一个合法区间时，以这个点为结尾的不合法的方案数要减去它前面$2^{\text{X的个数}}$，因为前面的和当前这个合法区搞在一起都是合法的

最后合并两个答案时，可以对其中一个维护前缀和，乘上另外一个的方案然后除掉多余的就可以了

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <String>
#define ll long long
using namespace std;
const int N=1e6+10;
const ll mod=1e9+7;
char s[N];
ll f[N],g[N],inv[N],sum[N],fp[N];
inline ll power(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1) res=res*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return res;
}
int main()
{
	int n,k; ll ans=0;
	scanf("%d%d%s",&n,&k,s+1);
	fp[n+1]=1;
	for(int i=n;i>=1;i--)
		fp[i]=(fp[i+1]<<(s[i]=='X'))%mod;
	inv[0]=1;
	for(int i=1,last=0;i<=n;i++)
	{
		if(s[i]=='W') last=i;
		inv[i]=(inv[i-1]<<(s[i]=='X'))%mod;
		if(i-last>=k&&s[i-k]!='B')
		{
			f[i]=(i-k>=1?inv[i-k-1]:1);
			inv[i]=(inv[i]-f[i]+mod)%mod;
		}
		sum[i]=(sum[i-1]+f[i]*fp[i+1]%mod)%mod;
	}
	inv[n+1]=1;
	for(int i=n,last=n+1;i>=1;i--)
	{
		if(s[i]=='B') last=i;
		inv[i]=(inv[i+1]<<(s[i]=='X'))%mod;
		if(last-i>=k&&s[i+k]!='W')
		{
			g[i]=(i+k<=n?inv[i+k+1]:1);
			inv[i]=(inv[i]-g[i]+mod)%mod;
			ans=(ans+g[i]*sum[i-1]%mod*power(fp[i],mod-2)%mod)%mod;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：liujiaxi123456 (赞：0)

### 思路：

**显然考虑分成左右两部分分别 DP，最后来拼接答案。**

**关键问题是容易算重，考虑找标志物：**

- 即仅第一次合法的时候计算贡献。

- 于是令 $f_i $ 表示 $[i-K+1, i]$ 全为 'B'，且 $[1, i-1]$ 中没有连续 K 个 'B' 的方案数。

考虑转移：

- 由于 $[i-K+1, i] $ 的填的方式是固定的，所以应从 $i-K $ 转移过来。

- 但如果让前 $i-K$ 随便填显然会错，考虑减掉这些情况。

- 具体的，令 $cnt$ 表示前面乱填的数量，$sum $ 表示前面存在连续的 K 个 'B' 的方案数。

- 则 $f_i = cnt_{i-K} - sum_{i-K} - \sum_{j=i-K+1}^{i-1} f_j $。

- 然后再反过来做一遍，拼接一下答案即可。

### Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 1e6+5;
const ll MOD = 1e9+7;

namespace Josh_zmf {
	
	int N, K; ll sf[Maxn], sg[Maxn]; string s;

	inline int main() {
		cin>> N>> K>> s, s = ' ' + s;
		ll cnt = 1, sum = 0;
		for(int i=1, len=0; i<=N; i++) {
			len = (s[i]=='W' ?0 :len+1);
			if(len < K)	sf[i] = sf[i-1];
			else	sf[i] = (sf[i-1] + cnt - sum - (sf[i-1]-sf[i-K])) %MOD;
			if(i >= K) {
				if(s[i-K+1] == 'X')	cnt = cnt*2 %MOD, sum = sum*2 %MOD;
				sum += sf[i-K+1]-sf[i-K];
			}
		}
		cnt = 1, sum = 0; ll ans = 0;
		for(int i=N, len=0; i; i--) {
			len = (s[i]=='B' ?0 :len+1);
			if(len < K)	sg[i] = sg[i+1];
			else	sg[i] = (sg[i+1] + cnt - sum - (sg[i+1]-sg[i+K])) %MOD;
			if(i <= N-K+1) {
				if(s[i+K-1] == 'X')	cnt = cnt*2 %MOD, sum = sum*2 %MOD;
				sum += sg[i+K-1]-sg[i+K];
				ans += (sf[i+K-2]-sf[i+K-3])*sum %MOD;
			}
			// printf("i:%d, g:%lld, sg:%lld\n", i, sg[i]-sg[i+1], sg[i]);
		}
		cout<< (ans%MOD+MOD)%MOD<< '\n';
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```

---

## 作者：Feyn (赞：0)

[link](https://www.luogu.com.cn/problem/CF204D)

希望借此题解来总结一下这一类统计问题应当如何做到不重不漏。

这一类题目有共同的特点，即假如单纯的用 $f_{x,0/1}$ 来表示某个前缀是否符合某个性质时的方案数来进行转移的话会出问题，原因在于这类题描述的合法串可能有多个**合法点**（合法点是我们判定这个串合法的依据，比如这道题中就是连续出现的黑白段），“多个”体现在这道题里就是一个串中可能有多个黑白段，这样一来就可能被统计多次。

具有这个特性的最著名的题目之一就是 CSP-S2021 的 T2，那道题的难点之一就是普通的写法可能会导致一个串在多个断点处被贡献，从而导致出错。解决那道题的方法之一就是用 $f_{l,r}$ 来代表区间被一个括号完整包含，而 $g_{l,r}$ 则没有这个限制并加以区分。分析一下这个解法的思想就是强制命令每个合法串只在第一个合法点被贡献，这样一来就能做到不重不漏了。

说回这道题，根据相同的思路，我们可以令 $f_x$ 代表这个前缀长度为 $K$ 的后缀是**第一个出现连续白色**的方案数，而 $num_x$ 代表这个前缀**出现过**连续白色的方案数。相似地，可以令 $g_x$ 代表这个后缀相应的前缀是第一个出现连续黑色的方案，而 $num'_{x}$ 是这个后缀出现过连续黑色的方案数，统计答案的时候应该是 $ans=\sum f_x\times num'_{x+1}$。这样一来，每个合法串只会在第一次出现合法白段的段尾被贡献，就能做到不重不漏了。

至于代码细节和转移方程其它题解说得很清楚，本题解是对这一类题目解法和这一种思想的不成熟的总结。

code:

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
const int N=1000010;
const int mod=1e9+7;
using namespace std;
inline void read(int &wh){
	wh=0;char w=getchar();int f=1;
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}

int m,n,sum[N][2];
char a[N];

int f[N],g[N],num[N],all[N],su[N];

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);scanf("%s",a+1);
	for(int i=1;i<=m;i++){
		for(int j=0;j<2;j++)sum[i][j]=sum[i-1][j];
		if(a[i]^'X')sum[i][a[i]=='W']++;
	}
	all[0]=all[m+1]=1;
	for(int i=1;i<=m;i++){
		all[i]=all[i-1]*(a[i]=='X'?2:1)%mod;
		if(i>=n&&sum[i][1]-sum[i-n][1]==0)f[i]=(all[i-n]-num[i-n]-(su[i-1]-su[i-n]))%mod;
		num[i]=(f[i]+num[i-1]*(a[i]=='X'?2:1))%mod;su[i]=(su[i-1]+f[i])%mod;
	}
	for(int i=m;i;i--){
		all[i]=all[i+1]*(a[i]=='X'?2:1)%mod;
		if(i<=m-n+1&&sum[i+n-1][0]-sum[i-1][0]==0)g[i]=(all[i+n]-num[i+n]-(su[i+1]-su[i+n]))%mod;
		num[i]=(g[i]+num[i+1]*(a[i]=='X'?2:1))%mod;su[i]=su[i+1]+g[i];
	}
	for(int i=1;i<=m;i++)g[i]=num[i];
	int ans=0;
	for(int i=1;i<=m;i++)ans+=f[i]*g[i+1]%mod;
	printf("%I64d\n",(ans%mod+mod)%mod);
	
	return 0;
}
```

---

