# Lostborn

## 题目描述

小Biu最近喜欢上一款角色扮演游戏，游戏中的每一款武器有 $ k $ 个参数 $ a_{1},...,a_{k} $ ，并且根据游戏说明，这些参数两两互质。

游戏中的主角为英雄，英雄发起攻击时，造成的伤害不仅与武器有关，还与英雄的力量有关。如果英雄的力量为 $ n $ ，那么一次攻击造成的伤害为区间 $[1,n]$ 中不能被武器参数整除的数的个数。

现在小Biu获得了一把新的武器装备，他想知道用某个英雄发起攻击时，造成的伤害值为多少。

## 样例 #1

### 输入

```
20 3
2 3 5
```

### 输出

```
6
```

## 样例 #2

### 输入

```
50 2
15 8
```

### 输出

```
41
```

# 题解

## 作者：yinqf (赞：18)

~~在学长的感召下，我也来写题解了~~

[题目传送门](https://www.luogu.com.cn/problem/CF93E)

### Part1 题目大意

给定一个 $n$，再给一个数组 $a_i$，要求你求出 $1 \backsim n$ 之间不能被数组 $a_i$ 中任意一个数整除的数的个数。

一眼丁真，**容斥**。

### Part2 做法介绍

[容斥](https://baike.baidu.com/item/%E5%AE%B9%E6%96%A5%E5%8E%9F%E7%90%86/10146840)都会吧，可是根据普通数学解法需要 $O(k!)$，$k\leq100$ 会 T 的飞起。

那该怎么做呢？

不难想到，排除暴力，只有寄希望于 **DP**。

$dp{(i,j)}$ 表示前 $i$ 个数中，被前 $j$ 个 $a_j$ 中任意一个数整除的数的数量。

由此便得到转移方程：

$dp{(i,j)} = \lfloor \dfrac{i}{a_j} \rfloor + dp{(i,j-1)} - dp{(\lfloor {i\over a_j} \rfloor,j-1)}$

前两项不用解释，最后一项表示的是前 $i$ 个数中，被前 $j-1$ 个 $a_j$ 中任意一个数整除且被 $a_j$ 整除的数的数量，也就是第一项和第二项的交集，应该减去。

至于最后一项怎么理解，假设是 $x$ 一个满足条件的数，因为两两互质，所以 $x$ 可以写成 $x=a_j\times t$，其中 $t$ 为一个可以被前 $j-1$ 个 $a_j$ 中任意一个数整除的数。现在 $a_j$ 已经确定不变，只要知道有多少个 $t$ 就可以，而这个数量就是 $dp{(\lfloor {i\over a_j} \rfloor,j-1)}$。

可是，虽然已经变成 $O(nk)$，但是还是会 T，所以我们观察一下有没有对答案没有贡献的 $dp{(i,j)}$。

经过观察，何止是一点，可以说是大部分全没有贡献，~~真是比宋朝还冗兵冗管冗费~~。

$dp{(n,k)} = \lfloor \dfrac{n}{a_k} \rfloor + dp{(n,k-1)} - dp{(\lfloor {n\over a_k} \rfloor,k-1)}$

$dp{(\lfloor {n\over a_k} \rfloor,k-1)} = \lfloor \dfrac{\lfloor {n\over a_k} \rfloor }{a_{k-1}} \rfloor + dp{(\lfloor {n\over a_k} \rfloor,k-2)} - dp{( \lfloor {{\lfloor {n\over a_k} \rfloor }\over 
{a_{k-1}}} \rfloor,k-2)}$

……

发现同一个 $j$（也就是公式中的 $k$） 下的 $i$（也就是公式中的 $n$）中，有用的并不多，最多 $O(2\sqrt{n})$ 个，只有 $i \in \{\lfloor \dfrac{n}{i} \rfloor | 1 \le i \le n \}$ 才可能有用。

这时候时间复杂度为 $O(\sqrt{n}k)$，本题时限 2 秒，差不多能过。

可是，还要考虑空间啊！

$O(\sqrt{n}k)\approx 3\times 10^8$ 肯定开不下，那就和时间商量一下，一部分存储，一部分使用搜素计算，虽然降低效率，但空间问题解决，时间也过得去。

最后就是**半记忆化搜索**，计算 $dp{(n,k)}$，最后答案就是 $dp{(n,k)}$ 与 $n$ 的差。

### Part3 完整代码

```cpp
#include<bits/stdc++.h>
#define LL long long
#define faster ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
LL n,k,a[105],ans,cnt,cdp[200005][105];
LL dp(LL i,LL j)
{
	if(i==0)
	{
		return 0;
	}
	else if(j==1)
	{
		return i/a[j];
	}
	else if(i<200000&&cdp[i][j])
	{
		return cdp[i][j];
	}
	LL ret=i/a[j]+dp(i,j-1)-dp(i/a[j],j-1);
	if(i<=200000)
	{
		return cdp[i][j]=ret;
	}
	else
	{
		return ret;
	}
}
bool cmp(LL a,LL b)
{
	return a<b;
}
int main()
{
	faster;
	cin >> n >> k;
	for(int i=1;i<=k;i++)
	{
		cin >> a[i]; 
	}
	sort(a+1,a+k+1,cmp);
	ans=n-dp(n,k);
	cout << ans;
	return 0;
}
```
UPD: 普素数学解法时间复杂度写错了

---

## 作者：xuanxuan001 (赞：8)

# Update

- 2024.8.14 怎么被撤了，本来不想管的，~~但一看居然是第一篇题解，就还是管一下吧~~，更正了一下 dp 转移，之前的转移时直接依据代码中的倒序处理写的。感谢@FreedomKing 和@Xiphi 的提醒。

这题显然是个容斥，但是 $k \le 100$ ，直接容斥会 T 飞。

然后我学校的教练提示我要 DP，我就想了个最初步的：用 $dp_{i,j}$ 表示区间 $[1,i]$ 中被前 $j$ 个数中至少一个数整除的数的个数，答案就是 $n-dp_{n,k}$。然后转移方程就是

$$
dp_{i,j} = \lfloor \dfrac{i}{a_j} \rfloor + dp_{i,j-1} - dp_{\lfloor {i\over a_j} \rfloor,j-1}
$$

边界就在 $j = 0$ 上。

没什么好解释的，就是最后一项是由于 $a$ 两两互质，所以那 $\lfloor \dfrac{i}{a_j} \rfloor$ 个 $a_j$ 的倍数在后面直接变成 $[1,\lfloor \dfrac{i}{a_j} \rfloor]$ 对整除不影响，也就不影响答案。

但是 $O(nk) = 10^{13} \times 100$ 显然不行。

这时我联想到了数论分块（就那个 $O(\sqrt{n})$ 计算 $\sum\limits_{i=1}^n \lfloor \dfrac{n}{i} \rfloor$ 的算法），可以发现能影响答案的只有 $i \in \{\lfloor \dfrac{n}{i} \rfloor | 1 \le i \le n \}$ 的部分，而这种 $i$ 只有 $O(\sqrt{n})$ 个，虽然 $O(k \sqrt{n})$ 比较极限，但也是可以的。

于是我就用一个 map 来进行记忆化，然后因为多一个 $\log$ 而 TLE 了。

于是我又开了个 $O(k \sqrt{n})$ 的数组，然后因为开得太大连编译都过不了（都 $3 \times 10^8$ 了，而且还要再乘个 2）

最后教练告诉我可以只把 $i$ 比较小的记忆化并把 $a$ 倒序排序，我算了一下，决定以 $2 \times 10^5$ 为界，因为我用递归实现的记忆化搜索，如果用循环还能大一点，但没必要，然后就 A 了。

之后我试了 $n = 10^{13},k = 100$ 然后 $a$ 为前一百个质数的数据，过了，所以复杂度应该是正确的。

代码（因为倒序排序不方便，所以我是直接排序然后倒着处理的）：
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#define MAXN 102
#define MAXM 200002
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define fOR(i,a,b) for(int i=a;i<b;i++)
#define rOF(i,a,b) for(int i=a;i>b;i--)
using namespace std;
typedef long long ll;
ll qr(){
	ll x=1,s=0;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';
	return x*s;
}ll n,k,B,a[MAXN],dp[MAXM][MAXN];
ll dfs(ll n,ll now){
	if(n==0)return 0;if(now==1)return n/a[1];
	if(n<MAXM&&dp[n][now]!=-1)return dp[n][now];
	ll ans=n/a[now]+dfs(n,now-1)-dfs(n/a[now],now-1);
	if(n<MAXM)dp[n][now]=ans;return ans;
}
int main(){
	fOR(i,0,MAXM)fOR(j,0,MAXN)dp[i][j]=-1;
	n=qr();k=qr();
	FOR(i,1,k)a[i]=qr();
	sort(a+1,a+k+1); 
	printf("%I64d",n-dfs(n,k));
	return 0;
}
```

---

## 作者：断清秋 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF93E)

如果直接大力容斥枚举子集，由于 $a_i$ 两两互质那么 $\operatorname {lcm}$ 即为乘积，因此增长速度极快，很快就大于 $n$ 了，所以跑得意外地快，不过依然只能过 $n=10^{11}$，不可能过 $10^{13}$。

考虑一下正经做法，设 $dp_{i,j}$ 表示 $[1,i]$ 中会被前 $j$ 个 $a$ 中的数整除的个数。

注意到对于 $[1,i]$ 中能被 $a_j$ 整除的 $\left\lfloor\dfrac{i}{a_j}\right\rfloor$ 个数，由于 $a_i$ 两两互质，对于除 $a_j$ 以外的 $a$ 来说等价于 $[1,\left\lfloor\dfrac{i}{a_j}\right\rfloor]$。

观察到这个性质，立得转移方程 $dp[i][j]=\left\lfloor\dfrac{i}{a_j}\right\rfloor+dp[i][j-1]-dp[\left\lfloor\dfrac{i}{a_j}\right\rfloor][j-1]$。

然后经典结论， $\dfrac{n}{i}$ 的取值最多 $\sqrt{n}$ 个，所以时间复杂度和空间复杂度均为 $O(k\sqrt{n})$。时间复杂度可以接受但空间不行，如果使用哈希表进行记忆化会直接寄掉。

考虑时间换空间，可以进行小范围记忆化，即对于状态 $dp_{i,j}$，只在 $1 \le i \le lim$ 时记录状态值，其他部分直接递推下来。

考虑一个 $lim \times k$ 的数组能开多大，实际上 $lim$ 开到 2e5 就能过了。

---

## 作者：hellolin (赞：3)

# CF93E Lostborn 题解

题意是给你长度为 $k$ 的序列 $a$，求 $[1,n]$ 内不能被任何一个 $a_i$ 整除的数的数量。$1\le n\le 10^{13}, 1\le k\le 100, 1\le a_i\le 1000$。

首先不难根据容斥原理得出答案：

$$
\sum\limits_{S\in \{a_1, a_2, \dots, a_k\}}(-1)^{ |S|-1 }\frac{n}{\prod\limits_{a_i\in S}a_i}
$$

硬算复杂度带个 $2^k$，直接爆了。考虑优化。

我们设 $f(i,j)$ 表示 $[1,i]$ 中能被 $a_1, a_2, \dots, a_j$ 中任意一个数整除的个数，再根据容斥得出转移：

$$
f(i,j)=\lfloor\frac{i}{a_j}\rfloor + f(i,j-1) - f(\lfloor\frac{i}{a_j}\rfloor,j-1)
$$

复杂度 $O(nk)$，还是爆了。

注意到转移里的 $\lfloor\frac{i}{a_j}\rfloor$，不难发现 $\lfloor\frac{n}{x}\rfloor$ 只有 $O(\sqrt n)$ 种不同的取值，也就是说其实有贡献的状态只有 $O(k\sqrt n)$ 种，算下来在 $3\times 10^8$ 左右。

最后一个问题，用 map 记忆化时间会爆，用数组记忆化空间会爆，这种情况我们可以设计一个上限（比如 $2\times 10^5$），仅当 $i\le 2\times 10^5$ 时记忆化，这时时间和空间都可以接受。另外，把 $a$ 序列升序排序，先处理大的 $a_i$ 也会减少很多运算。

``` cpp
static constexpr int N = 2e5;

i64 dfs(i64 n, int k) {
  if (n == 0) return 0;
  if (k == 1) return n / a[1];
  if (n < N && ~f[n][k]) return f[n][k];

  i64 ans = n / a[k] + dfs(n, k - 1) - dfs(n / a[k], k - 1);
  return n < N ? f[n][k] = ans : ans;
}
```

---

## 作者：FreedomKing (赞：2)

### 思路

#### 暴力容斥

很容易想到容斥做法，考虑枚举序列 $a$ 的子集，根据基本容斥和状态贡献可以列出:

$$\sum_{S\in a}(-1)^{\left |S\right |-1}\tfrac{n}{ \prod_{a_i\in S}a_i}$$

显然时间复杂度是 $2^k$ 级别的。

#### 朴素 dp

考虑设 $dp_{i,j}$ 表示前 $i$ 个数中有多少数会被 $a$ 序列中前 $j$ 个数整除，答案即为 $n-dp_{n,k}$。

转移是一个小容斥，即 $dp_{i,j}=\lfloor\tfrac{n}{a_i}\rfloor+dp_{i,j-1}-dp_{\lfloor\tfrac{n}{a_i}\rfloor,j-1}$，相当于是直接加上贡献然后减去重复的部分。

时间复杂度 $O(nk)$，显然对于 $n=10^{13},k=100$ 的数据范围是不能接受的。

#### 优化

先进行一个排序的优化。

考虑使用记忆化进行优化，显然全部的状态是存不下的，思考可以发现每个 $dp_{i,j}$ 对后面答案的贡献是一个类似数论分块的东西，也就是说有效状态事实上只有 $\sqrt n k$ 级别种，可以考虑类似根号分治的思想，对于 $i<3\times 10^5$ 的部分进行记忆化。

### Code

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
bool M1;
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<" MB\n"
#define look_time cerr<<(clock()-Time)*1.0/CLOCKS_PER_SEC<<'\n'
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=3e5+5,mN=1e2+5,mod=1e9+7;
namespace FreedomKing_qwq{
#define lowbit(_) (_&-_) 
	struct Tree{
		int tree[N];
		inline void add(int x,int j){
			for(int i=1;i<=x;i+=lowbit(i)) tree[i]+=j;
			return;
		}
		inline int query(int x){
			int ans=0;
			for(int i=x;i>1;i-=lowbit(i)) ans+=tree[i];
			return ans;
		}
	};
	struct Dset{
		int fa[N];
		inline void init(int x){
			for(int i=1;i<=x;i++) fa[i]=i;
			return;
		}
		inline int find(int x){
			return (fa[x]==x?x:fa[x]=find(fa[x]));
		}
		inline void update(int x,int y){
			x=find(x);y=find(y);
			fa[y]=x;
			return;
		}
	};
#define lc (p<<1)
#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}	
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline __int128 qpow(__int128 x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		__int128 t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
	inline int abss(int x){return (x>=0?x:-x);}
}
int a[N],dp[N][mN];
inline int dfs(int n,int k){
	if(!n) return 0;
	if(k==1) return (n/a[1]);
	if(n<N&&(~dp[n][k])) return dp[n][k];
	int ans=n/a[k]+dfs(n,k-1)-dfs(n/a[k],k-1);
	return (n<N?dp[n][k]=ans:ans);
}
bool M2;
signed main(){
	int n=qr,k=qr;
	for(int i=1;i<=k;i++) a[i]=qr;
	memset(dp,-1,sizeof(dp));
	sort(a+1,a+k+1);
	qw(n-dfs(n,k));
	return 0;
}
```

---

## 作者：2huk (赞：2)

MX-C day1 T2。

### 题意

给定 $k$ 个两两互质的正整数，求 $1 \sim n$ 中有多少数不能被任意一个数整除。

### 做法

「多少数不能被任意一个数整除」= $n - $ 「多少数能被任意一个数整除」。

考虑 DP。设 $f(n, k)$ 表示有多少个 $1 \sim n$ 的数，能被 $a_1,a_2\dots a_k$ 中的任意一个数整除。

很妙的转移！
$$
f(n, k) = \lfloor n / a_k\rfloor + f(n, k - 1) - f(\lfloor n / a_k\rfloor, k - 1)
$$
其中，$\lfloor n / a_k\rfloor$ 表示 $1 \sim n$ 中能被 $a_k$ 整除的数的个数，$f(n, k - 1)$ 表示 $1 \sim n$ 中能被 $a_1\dots a_{k-1}$ 整除的数的个数。

显然这两个集合可能有交，即 $1 \sim n$ 中既能被 $a_k$ 整除，又能被 $a_1 \dots a_{k-1}$ 中任意一个数整除的数。

如果一个数 $x$ 是这两个集合的交，那么 $\frac x{a_k}$ 一定能被 $a_1 \dots a_{k-1}$ 中任意一个数整除。那么 $\frac x{a_k}$ 的数量为 $f(\lfloor n / a_k\rfloor, k - 1)$。因为 $x$ 和 $\frac x{a_k}$ 一一对应，所以 $x$ 的数量也是 $f(\lfloor n / a_k\rfloor, k - 1)$。

直接用 (u)map 转移空间复杂度会爆。优化方案有两种：

> 方法一：整除分块。
>
> 前排提醒，这种做法在时间上被卡常乐【】
>
> 对于每一个有效的状态 $f(i, j)$，这个 $i$ 一定是由给定的 $n$ 开始，不断除以某个 $a_k$ 下取整得到的。根据 [知识](https://oi-wiki.org/math/number-theory/sqrt-decomposition/) 我们得知这样的 $i$ 的数量是根号级别的。
>
> 因此我们可以双指针得到 $n$ 除以某个数下取整可能的得到的值（如上所述，数量是根号级别的），将其离散化即可。
>
> 离散化后转移可以双指针，一个指向 $n$，一个指向 $\lfloor n / a_k\rfloor$。
>
> 而且这个状态的第二维可以滚动优化。空间复杂度做到了根号。
>
> 后排提醒，这种做法在时间上被卡常乐【】

> 方法二：暴力 + 记忆化。
>
> 我们设一个阈值 $B$，然后记忆化转移。对于状态 $f(i, j)$ 若 $i < B$ 则用数组记忆化。否则直接转移不记忆了。这里我取的 $B = 10^6$。不难（？）证明这样的复杂度是正确的。
>
> 极其相似的题有 [CF1806E](https://www.cnblogs.com/2huk/p/18194174#-cf1806e-tree-master)，比较相似的题有 [ABC365G](https://www.bilibili.com/video/BV1noiFeHEJi/?share_source=copy_web&vd_source=e1044e7a01b4b54d479c00e7fea3f47d&t=2716)。

---

## 作者：Sun_wtup (赞：2)

# CF93E Lostborn 题解
[题目传送](https://www.luogu.com.cn/problem/CF93E)
## 题目描述
概括一下，就是：给出 $k$ 个两两互质的正整数 $a_1, a_2, ...a_k$，求 $[1, n]$ 这个区间中有多少个数不能被给出的任意一个数整除。
## 题目分析和思路
首先看这个题，不能被任意一个数整除，直接做显然很不好做，那就正难则反，也就是考虑容斥，这是比较容易想到的，但也是比较重要的。所以就算有多少个数可以被其中至少一个数整除.考虑 dp,设出状态，找出转移方程，求出 $f_{n,k}$，在拿 $n$ 减掉就行了。但是这道题还需要考虑优化，具体见下方实现。
## 实现
首先设状态设状态，设 $f_{i,j}$ 为区间 $[1,i]$ 中被前 $j$ 个数中至少一个数整除的数的个数。易得转移方程 

$$\large{f_{i,j} = f_{i,j - 1} - f_{\lfloor\frac{i}{a_{j}}\rfloor, j - 1} + \lfloor\frac{i}{a_{j}}\rfloor}$$

这时候就会发现，他时间会爆，考虑优化。把 $a_i$ 升序排序或者倒着处理，可以减少一些计算，但这不是重点。不难发现，$\lfloor\frac{n}{i}\rfloor$，最多只有 $\sqrt{n}$ 种取值。这样时间复杂度就可以优化到 $\mathcal{O}(k \sqrt{n})$。这时候又有问题了，map 的常数比较大，直接记忆化还是会超时，哈希也不行。这时候就需要一个设一个阈值，对于数据范围的大小进行分类处理，~~谁家正解长这样~~，只有在 $i \leq 2 \times 10^5$ 时，才记忆化。
## Code
```cpp
void init()
{
    memset(f, -1, sizeof(f));
}
int dfs(int idx, int now)
{
    if (idx == 0)
    {
        return 0;
    }
    if (now == 1)
    {
        return idx / a[1];
    }
    if (idx < 200000 and f[idx][now] != -1)
    {
        return f[idx][now];
    }
    ans = idx / a[now] + dfs(idx, now - 1) - dfs(idx / a[now], now - 1);
    return idx < 200000 ? f[idx][now] = ans : ans;
}
```

---

## 作者：Ghosty_Neutrino (赞：1)

## 分析
$dp_{i,j}$ 表示前 $j$ 个数字中不能被 $a_j, \cdots,  a_n$ 整除的数字个数，那么该值即为前 $j$ 个数字中不能被 $a_{j+1}, \cdots, a_n$ 整除的数字个数减去前 $j$ 个数字中可以被 $a_j$ 整除但是不能被 $a_{j+1},\cdots,a_n$ 整除的数字个数，进而得出以下转移：
$$
dp_{i,j}=dp_{i+1,j}-dp_{i+1,\lfloor \frac{j}{a_i} \rfloor}
$$
$j$ 比较小时存下来，较大值递归求解，注意为使第二维下降更快，将 $a$ 序列排序使得 $a_1>a_2> \cdots>a_n$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>P;
const int INF=0x3f3f3f3f,maxn=105;
ll n;
int k,a[maxn],M=200000,dp[maxn][200001]; 
ll Sl(int m,ll n){
    if(m>k||n==0) return n;
    if(n<=M&&dp[m][n]!=-1) return dp[m][n];
    ll ans=Sl(m+1,n)-Sl(m+1,n/a[m]);
    if(n<=M)dp[m][n]=ans;
    return ans;
}
bool cmp(int x,int y){return x>y;}
int main(){
    scanf("%I64d%d",&n,&k);
    for(int i=1;i<=k;i++) scanf("%d",&a[i]);
    sort(a+1,a+k+1,cmp);
    memset(dp,-1,sizeof(dp));
    printf("%I64d\n",Sl(1,n));
    return 0;
}
```

---

## 作者：C_Pos_Princess (赞：1)

### 题意简述
给出 $k$ 个正整数 $a_1,a_2,a_3 \cdots a_k$，保证其两两互质，求 $[1,n]$ 中有多少个数不能别给出的任意一个整数整除。

####  数据范围

$ 1\le n\le 10^{13} $，$ 1\le k\le 100 $，$ 1\le a_{i}\le 1000 $。

#### 题解
首先，看到这种整除有关的，我们考虑容斥，讲题目转化为求能被其中至少一个数整除的数的个数。

考虑动规。

不难写出转移：

$$
f_{i,j} = \lfloor \frac{n}{a_i}\rfloor + f_{i,j-1}-f_{\lfloor \frac{n}{a_i}\rfloor,j-1}
$$

直接做的话复杂度为 $O(nk)$。
注意到，$\lfloor \frac{n}{a_i}\rfloor$ 的取值只有 $O(\sqrt n)$ 个，所以其实有效的状态也只有 $O(\sqrt nk)$ 个。

如果直接记忆化，那么空间复杂度不能接受，所以我们考虑设置一个阈值，在这个阈值以内进行记忆化。

由于互质的性质再加上过程中所用到的除法，其实小范围的记忆化能够优化的是很多的，可以过。

#### 代码

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,a[10010];
int k;
ll f1[10010][110];

ll f(int k,ll n){
	if(n<=10000 && f1[n][k])
		return f1[n][k];
	
	if(k == 0)
		return n;
	if(n == 0)
		return 0;			
	return f(k-1,n)-f(k-1,n/a[k]);
}

int main() {
	scanf("%lld%d",&n,&k);
	for(int i = 1;i<=k;i++){
		scanf("%lld",&a[i]);
	}
	
	sort(a+1,a+1+k);
	for(int i = 1;i<=10000;i++){
		f1[i][0] = i;
	}
	for(int j = 1;j<=k;j++){
		for(int i = 1;i<=10000;i++){
			f1[i][j] = f1[i][j-1]-f1[i/a[j]][j-1];
		}
	}
	printf("%lld\n",f(k,n));

	return 0;
}
```

---

