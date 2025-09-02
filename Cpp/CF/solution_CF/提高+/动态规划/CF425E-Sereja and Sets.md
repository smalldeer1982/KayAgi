# Sereja and Sets

## 题目描述

对于一个有 $m$ 条线段的集合 $S$ 来说，定义函数 $f(S)$ 为你最多可以从这个集合中选择多少线段使得他们都不相交。端点重合也算相交。线段的右端点都小于等于 $n$。

对于给定的 $n,k$，求出有多少个满足条件的 $S$ 满足 $f(S)=k$。

## 样例 #1

### 输入

```
3 1
```

### 输出

```
23
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
32
```

## 样例 #3

### 输入

```
2 0
```

### 输出

```
1
```

## 样例 #4

### 输入

```
2 2
```

### 输出

```
2
```

# 题解

## 作者：FreedomKing (赞：7)

写自梦熊模拟赛赛后补题。梦熊模拟赛出原题，望周知。

### 思路

首先思考本题中互不冲突线段选取的最优方案，这是一个非常经典的贪心思路，令 $k$ 为当前已选线段中最右的右端点位置，每次在满足 $k<l_{S_i}$ 的前提下选择最短线段并加入，更新 $pos=r_{S_{minn}}$。

通过上述过程，可以基于线段选取的贪心思路引申出此题的 dp 做法，即设 $dp_{i,j}$ 表示当 $pos=i$ 时已选取 $j$ 条线段的总方案数。

考虑转移，对于 $i<l\le r= k$，共有 $k-i$ 条线段合法，故对于大于 $i$ 的部分共有 $2^{k-i}$ 种方案，其中需要排除一种每条线段都不选择的方案，剩下 $2^{k-i}$ 种方案。此外，我们还需要考虑到一些不会影响方案合法性的未选线段，也就是满足 $i<l\le k<r$ 的线段，共有 $(n-k)\times (k-i)$ 条。

综上所述，可以整理出来完整的 dp 式子 $dp_{i,j}\times(2^{k-i}-1)\times 2^{(n-k)\times(k-i)}=dp_{k,j+1}$。

### AC Code

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=1e6+5,mN=5e2+5,mod=1e9+7;
namespace FreedomKing_qwq{
#define lowbit(_) (_&-_)
	struct Tree{
		int tree[N];
		inline void add(int x,int k){
			for(int i=1;i<=x;i+=lowbit(i)) tree[i]+=k;
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
	//#define lc (p<<1)
	//#define rc (p<<1|1)
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
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
//	inline int max(int x,int y){return (x>y?x:y);}
//	inline int min(int x,int y){return (x<y?x:y);}
	inline int abss(int x){return (x>=0?x:-x);}
}
int dp[mN][mN],f[N];
signed main(){
//	freopen("seg.in","r",stdin);
//	freopen("seg.tou","w",stdout);
	f[0]=1;
	for(int i=1;i<N;i++) f[i]=(f[i-1]<<1)%mod;
	int n=qr,k=qr;
	dp[0][0]=1;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=i;j++)
			for(int k=i+1;k<=n;k++)
				dp[k][j+1]=(dp[k][j+1]+(dp[i][j]*(f[k-i]-1)%mod)*f[(n-k)*(k-i)]%mod)%mod;
	int ans=0;
	for(int i=k;i<=n;i++) ans=(ans+dp[i][k])%mod;
	qw(ans);
	return 0;
}
```

---

## 作者：断清秋 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF425E)

直接计数！

考虑如果已知线段情况，是一个经典贪心，每次选当前右端点最小的线段即可。

然后设 $dp_{i,j}$ 表示当前右端点为 $i$，已经选了 $j$ 条线段的方案数，枚举下一个右端点 $k$ 进行转移。

计数思路肯定是确定能放的线段，然后找可放可不放的线段有多少。

那么考虑一条线段 $[l,r]$，只需要考虑 $l>i$ 的情况。那么对于 $i<l \le r=k$ 的线段，这种线段有 $k-i$ 条，至少要选择其中一条，所以方案数是 $2^{k-i}-1$。

对于 $i<l \le r <k$ 的线段，都不能选。

对于 $i<l \le k < r$ 的线段，不影响当前状态，可选可不选，所以方案数是 $ 2^{(n-k)(k-i)}$。

所以转移就是把这些方案数都乘起来，即 $dp_{k,j+1}=dp_{i,j}\times (2^{k-i}-1)\times 2^{(n-k)(k-i)}$。

初始态 $dp_{0,0}=1$，注意要从 $i=0,j=0$ 开始转移。

预处理 $2$ 的幂可以省掉一个 $\log$，时间复杂度 $O(n^3)$。

代码：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return 
#define ri register int
using namespace std;
ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	back x*f;
}
const int mod=1e9+7;
ll n,m,ans,dp[1005][1005],f[500005];
int main()
{
	n=read(),m=read();
	f[0]=1,dp[0][0]=1;
	for(ri i=1;i<=n*n;i++)
		f[i]=f[i-1]*2%mod;
	for(ri i=0;i<=n;i++)
		for(ri j=0;j<=i;j++)
			for(ri k=i+1;k<=n;k++)
				dp[k][j+1]=(dp[k][j+1]+dp[i][j]*(f[k-i]-1+mod)%mod*f[(n-k)*(k-i)]%mod)%mod;
	for(ri i=m;i<=n;i++)
		ans=(ans+dp[i][m])%mod;
	cout<<ans<<"\n";
    back 0;
}
```

---

## 作者：2huk (赞：1)

MX-C day1 T1。

### 题意

数轴上有 $n$ 个点，构成了 $\frac{n(n+1)}2$ 个线段。令所有线段为全集。问有多少子集，满足这个子集内的线段，在两两不交的情况下能选出的最多线段数恰好为 $k$。$k \le n \le 500$。

### 做法

如果暴力 dfs，那么 check 的做法是经典贪心。即将所有线段按照**右端点**排序，然后顺次判断能不能选这条线段。见 [AcWing 908.](https://www.acwing.com/problem/content/910/)。

数据范围不大，考虑狠狠地 DP。

设 $f(i, j)$ 表示当前贪心得到的最大右端点的位置 $\le i$，且最优策略中选择的线段数量为 $j$ 时的总方案数。

或者，$f(i, j)$ 即有多少个原题的答案的线段集合，使得这个集合的最优选择中最靠右的线段的右端点 $\le i$，且最优方案选择的线段数量为 $j$。

转移。枚举倒数第二大的最优选择中的线段的右端点 $p$。我们考虑线段 $[l, r]$（$l \le r \le i$）：

- 若 $r \le p$：那么这条线段在 $f(p, j - 1)$ 中已经被计算过了。
- 若 $l \le p$ 且 $p < r < i$：这条线段一定不在 $f(i, j)$ 的最优选择中。所以这样的线段可有可无，方案是 $2^{p (i-p-1)}$。
- 若 $p \le l < r < i$：这条线段如果存在，就不满足「最优选择中最靠右的线段的右端点为 $i$」这个条件。所以这样线段不能出现。
- 若 $l \le p$ 且 $r = i$：这条线段一定不在 $f(i, j)$ 的最优选择中。所以这样的线段可有可无，方案是 $2^p$。
- 若 $p < l$ 且 $r = i$：这条线段可能是 $f(i, j)$ 状态中所说的「最优选择中最靠右的线段的右端点为 $i$」的线段，但是这条线段只能有一条，而剩下的线段可有可无。方案是 $(2^{i-p} - 1)$。

综上转移：
$$
f(i, j) = \sum_{p=0}^{i-1} f(p,j-1)\times 2^{p(i-p-1)} \times 2^p \times (2^{i-p}-1)
$$
初始化：

- $f(i, 0)$：表示最优方案选择的线段数量为 $0$。显然只用空集一个，答案为 $1$。
- $f(0, i)$：表示线段右端点为 $0$。仍然只用空集一个，答案为 $1$。

快速幂是过不掉的。我们考虑预处理一些 $2$ 的幂：

- $2^p$，$2^{i-p}$：线性递推。
- $2^{p(i-p-1)}$：设 $g_{i, j} = 2^{ij}$，那么转移 $g_{i, j} = g_{i - 1, j} \times 2^j$ 或 $g_{i, j} = g_{i, j - 1} \times 2^i$。

---

## 作者：C_Pos_Princess (赞：0)

# 题解：CF425E Sereja and Sets

我们设 $dp_{i,j}$ 表示当前 $pos = i$, 已经选了 $j$ 条线段的方案数，接着我们枚举下一个右端点 $k$ 进行转移。

对于 $i<l\le r = k$ 的线段有 $k-i$ 条，其至少有一条线段存在，则贡献为 $2^{k-i} -1$。

$i<l<r = k$ 的线段都不能存在；因为，如果存在，就会在前面更新。

$i<l\le k<r$ 的线段有 $(n-k)\times (k-i)$ 条，其存在不存在无所谓（因为要选最多的，必然不会选），贡献为 $2^{(n-k)\times (k-i)}$。

则转移方程：

$$
f_{k,j+1} = f_{i,j} \times (2^{k-i}-1) \times 2^{(n-k)\times(k-i)}
$$


代码奉上：
```
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
const int N= 510;
int n,k,dp[N][N],e[N*N],ans;


int main(){
//	freopen("seg.in","r",stdin);
//	freopen("seg.out","w",stdout);
	cin>>n>>k;
	if(!k) {
		cout<<1;
	}else{
		e[0] = 1;
		for(int i = 1;i<=n*(n+1)/2;i++){
			e[i] = e[i-1]*2%mod;
		}
		for(int i = 1;i<=n;i++){
			dp[i][1] = e[i]-1;
			for(int j = 2;j<=min(k,i);j++){
				for(int l = 1;l<i;l++){
					dp[i][j] = (dp[i][j]+1ll*dp[l][j-1]*e[l*(i-1-l)]%mod*e[l]%mod*(e[i-l]-1))%mod;
				}
			}
			ans = (ans+1ll*dp[i][k]*e[i*(n-i)])%mod;
		}
		cout<<ans;
	}
	
	fclose(stdin);
	fclose(stdout);
	
	return 0;
}

```

---

## 作者：Fireworks_Rise (赞：0)

# 前言

想到 dp 的定义了，却没能想出转移方程...

# 分析

题意不用多说了，一眼计数问题，动态规划求解。

很套路，容易想到定义 $f_{i,j}$ 表示集合 $S$ 中最后一个线段的右端点恰好是 $i$，取 $j$ 条线段的方案数。

尝试枚举 $i$ 前面的右端点 $k$ 进行转移，每次转移无论选多少个不同的 $[k,i]$ 都只会产生一点贡献（不能不选），那就是讨论每个线段选或不选的问题了，方案数为 $2^{i-k}-1$。

但这还没完，假设加入当前状态的线段集合中有线段区间为 $[l,r]$，是否会有满足 $l \le k < r$ 的呢？明显的这些都不会影响当下状态能取最多的线段个数，小小贪心，发现 $f_{k,j-1}$ 所取的线段会更优，那符合条件的选择有 $2^{(i-k) \times k}$ 种，最后利用乘法原理即可。

整理上述，可以得到转移方程为：

$f_{i,j}+=f_{k,j-1} \times (2^{i-k}-1) \times 2^{(i-k) \times k}$

最后的答案为 $Ans = f_{n,k}$。

注：记得勤取模 $10^9+7$！！！

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7; 
const int N=5e2+20;
int n,k,f[N][N],p[N*N];
signed main() {
	scanf("%lld%lld",&n,&k);
	p[0]=1,f[0][0]=1;
	for(int i=1;i<=n*n;i++)
		p[i]=p[i-1]*2%mod;
	for(int i=1;i<=n;i++) {
		f[i][0]=1;
		for(int j=1;j<=min(i,k);j++) {
			for(int k=j-1;k<=i;k++)
				f[i][j]=(f[i][j]+f[k][j-1]*(p[i-k]-1)%mod*p[(i-k)*k]%mod)%mod;
		}
	}
	printf("%lld\n",f[n][k]);
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
动态规划题，注意取模情况即可。

题意简述：有一个集 $S$ 包括了很多个区间 $\left[l,r\right]$ 同时 $1\leq l \leq r\leq n$ 的范围。同时有 $f\left(S\right)$ 个不相交的区间，现在给出 $n$ 和 $f\left(S\right)$ 问有几种可能的 $S$ 集合。
## 分析。
很经典的贪心。我们可以从集合数入手。所以我们定义 $dp\left[i\right]\left[j\right]$ 表示当 $n=i$ 且 $f\left(S\right)=j$ 时的 $S$ 集合数。

那么当 $j-1\leq k\leq i$ 时，我们可以通过 $dp\left[k\right]\left[j-1\right]$ 来求得。考虑转移方程。  
首先我们考虑区间。将 $j-1$ 转移到 $j$ 则不相交的区间有 $\left[k+1,k+1\right]\left[k+1,k+2\right]\ldots$ 所以那么一共有 $2^{i-k}-1$ 种可能性，其中的 $-1$ 是因为存在所有的这种区间都不取的情况。

注意到不从 $k-2$ 的区间开始取，我们可以这样理解：首先该转移方程遍历的是 $k$ 那么当遍历到 $k+1$ 时我们能转移出以 $k+2$ 为区间的集合数。如果不明白可以自己做一做。

那么我们不妨随便取几个区间，这些区间一定和之前的相交，那么仅仅要一端在 $k$ 以内就好了，所以一共同有 $2^{\left(i-k\right)\times k}$ 种取法。

综上所述，转移方程就是最后得出 $dp\left[i\right]\left[j\right]=\sum\left(dp\left[k\right]\left[j-1\right]\times2^{\left(i-k\right)-1}\times 2^{\left(i-k\right)\times k}\right)$ 的式子，注意取模。

代码如下，仅供参考：
```
#include<iostream>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
const ll mod=1e9+7;
ll n,k;
ll dp[505][505],sum[505*505];
int main(){
    cin>>n>>k;
    sum[0]=1;
    for(ll i=1;i<505*505;i++){
    	sum[i]=(sum[i-1]<<1)%mod;
	}
    for(ll i=0;i<=n;i++){
    	dp[i][0]=1;
    }
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=min(k,i);j++){
            for(ll z=j-1;z<=i;z++){
                dp[i][j]=(dp[i][j]+dp[z][j-1]*(sum[i-z]-1)%mod*sum[z*(i-z)]%mod)%mod;
                //cout<<i<<" "<<j<<" "<<dp[i][j]<<"\n";
            }
        }
    }
    //cout<<dp[n][k]%mod<<"\n";
    cout<<dp[n][k]<<"\n";
    return 0;
}
```
## 后记。
这道题还是值得一做的。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

