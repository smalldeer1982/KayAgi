# Array GCD

## 题目描述

You are given array $ a_{i} $ of length $ n $ . You may consecutively apply two operations to this array:

- remove some subsegment (continuous subsequence) of length $ m<n $ and pay for it $ m·a $ coins;
- change some elements of the array by at most $ 1 $ , and pay $ b $ coins for each change.

Please note that each of operations may be applied at most once (and may be not applied at all) so you can remove only one segment and each number may be changed (increased or decreased) by at most $ 1 $ . Also note, that you are not allowed to delete the whole array.

Your goal is to calculate the minimum number of coins that you need to spend in order to make the greatest common divisor of the elements of the resulting array be greater than $ 1 $ .

## 说明/提示

In the first sample the optimal way is to remove number $ 3 $ and pay $ 1 $ coin for it.

In the second sample you need to remove a segment $ [17,13] $ and then decrease number $ 6 $ . The cost of these changes is equal to $ 2·3+2=8 $ coins.

## 样例 #1

### 输入

```
3 1 4
4 2 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 3 2
5 17 13 5 6
```

### 输出

```
8
```

## 样例 #3

### 输入

```
8 3 4
3 7 5 4 3 12 9 4
```

### 输出

```
13
```

# 题解

## 作者：pigstd (赞：17)

为啥这题的题解都是 `dp` 啊，来发不用 `dp` 的题解。

---

考虑一个子问题：如果已经知道了这个数列的 $\gcd$ 为 $d$，那么应该怎么找到最小值呢？

首先，设一个数列 $d_i$ 表示 $a_i$ 满足条件所需要的花费，显然若 $a_i$ 为 $d$ 的倍数则为 $0$，若 $a_i+1$ 为 $d$  的倍数或者 $a_i -1$ 为 $d$ 的倍数则为 $b$，否则就是 `inf`。

然后分两种情况讨论：

- 没有 `inf`：

那么在这个时候，显然是需要找到一段区间 $[l,r]$ 让 $d_{l \dots r}=a$ 且 $\displaystyle \sum_{i=1}^n d_i$ 最小。考虑点 $i$ 被包括情况，那么会在原来的基础上增加 $a-d_i$ 的贡献。那么相当于就是找到序列 $a-d_i$ 的**最小子段和**，在 $\displaystyle \sum_{i=1}^n d_i$ 的基础上加上这个最小值就可以了。具体操作的时候可以把所有数取负数然后求最大字段和就可以了。

- 存在 `inf`：

设最左边的 `inf` 的位置为 $l$，最右边的 `inf` 的位置为 $r$，那么 $[l,r]$ 这段区间必须要被删除，然后对于区间 $[1,l-1]$ 和 $[r+1,n]$ ，需要各自找到一个分界点使花费最少。设 $d_i$ 的前缀和为 $sum_i$，那么显然前一个区间的最小花费就是 $\min(sum_{i-1}+(l-i) \times a)$，可以 $\mathcal{O}(n)$ 解决。后面也是同理的。

于是我们就解决了这个子问题。

---

再回到原题，因为不能全部删除，所以 $a_1$ 和 $a_n$ 中必有一个数不会被删除，既然不被删除，那么这个 $d$ 就必然是 $a_1,a_1-1,a_1+1,a_n,a_n-1,a_n+1$ 这六个数中任意一个数的约数。

此外，显然当 $d$ 是质数的时候是更优的，那么可行的 $d$ 就很小了（一个数最多由 $9$ 个不同的质数组成），对于每个 $d$ 去查询最小值，就可以轻松解决该问题。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define WT int T=read();while(T--) 
#define NO puts("NO");
#define YES puts("YES");
using namespace std;

inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

const int inf=1e18;
const int M=1e6+10;
int n,a,b,ans=inf;
int c[M],d[M];
vector<int>v;

int work(int x)
{
	int f=0;
	for (int i=1;i<=n;i++)
	{
		if (c[i]%x==0)d[i]=0;
		else if (c[i]%x==1||c[i]%x==x-1)d[i]=b;
		else d[i]=inf,f=1;
	}
	if (f)
	{
		int l=n,r=1;
		for (int i=1;i<=n;i++)
			if (d[i]==inf)
				l=min(l,i),r=max(r,i);
		int ans=(r-l+1)*a,min1=inf,min2=inf,sum1=0,sum2=0;
		for (int i=1;i<=l;i++)
		{
			min1=min(min1,sum1+(l-i)*a);
			sum1+=d[i];
		}
		for (int i=n;i>=r;i--)
		{
			min2=min(min2,sum2+(i-r)*a);
			sum2+=d[i];
		}ans+=min1+min2;
		return ans;
	}
	else
	{
		int res=0,sum=0,maxn=0;
		for (int i=1;i<=n;i++)
		{
			res+=d[i],sum+=d[i]-a;
			sum=max(sum,0ll),maxn=max(maxn,sum);
		}res-=maxn;
		return res;
	}
}

void find(int x)
{
	for (int i=2;i*i<=x;i++)
	{
		if (x%i==0)
		{
			while(x%i==0)x/=i;
			v.pb(i);
		}
	}
	if (x!=1)v.pb(x);
}

signed main()
{
	n=read(),a=read(),b=read();
	for (int i=1;i<=n;i++)
		c[i]=read();
	find(c[1]),find(c[1]-1),find(c[1]+1);
	find(c[n]),find(c[n]-1),find(c[n]+1);
	for (int i=0;i<v.size();i++)
		ans=min(ans,work(v[i]));//,cout<<v[i]<<' '<<work(v[i])<<endl;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：DarkMoon_Dragon (赞：11)

+ # $CodeForces 623 B-Array GCD$
## 题意:
+ 给出$n,a,b$,和$n$个整数$a_1,a_2\dots a_n$,可以对数组进行一下操作：        
	1、花费$len*a$的代价删除连续的$len$个数，最多删除一段且不能删除整个数组。    
	2、花费$b$的代价将$a[i]$加一或减一，每个数最多执行一次这样的操作。
+ 求这个数组所有数的$gcd>1$的最小花费。        
+ $1\leq n \leq 10^6,0 \leq a,b \leq 10^9$  
## $Solution:$
+ 第一个或最后一个数是一定会剩下来的
+ 考虑对六种情况分解质因子(注意不是因子,暴力找因子肯定跑不过),预处理出来$a[1]+1,a[1]-1,a[1],a[n],a[n]+1,a[n]-1$
+ 讨论一个因子$x$,$cost_i$为加减后的费用  
	1. 若$a_i\% x==0$则$cost_i=0$
   1. 若$a_i+1$或$a_i-1\%x==0$则$cost_i=b$,都不行的话$cost_i=inf$
+ 考虑$dp$维护最小值
+ 以$dp[i][0/1/2]$表示到第$i$个值没删除元素/正在删除元素/结束删除元素的最小花费   
	1. $dp[i][0]=dp[i-1][0]+cost[i]$
   1. $dp[i][1]=min(dp[i-1][0],dp[i-1][1])+a$
   1. $dp[i][2]=min(dp[i-1][2],dp[i-1][1])+cost[i]$
+ 最后的答案$=min(dp[n][0],dp[n][1],dp[n][2])$
+ 有一个细节问题是$cost$赋为$inf$,这时$dp$可能加爆,每次得取一个讨论一下
      
```cpp
#include<iostream>
#include<cstdio> 
#include<cstring>
#include<algorithm>
#include<vector>
#define rr long long
using namespace std;
typedef long long ll;
inline ll read(){
    char i=getchar();
    ll f=1,res=0;
    while(i<'0'||i>'9'){if(i=='-')f=-1;i=getchar();}
    while(i>='0'&&i<='9'){res=res*10+i-'0';i=getchar();}
    return f*res;
}
const ll inf=1e18;;
const int N=1e6+50;
ll n,a,b,v[N];
ll dp[N][3],cost[N];
ll fac[500],res;
inline ll solve(ll x){
	memset(dp,0,sizeof dp);
	for(rr i=1;i<=n;++i){
		if(v[i]%x==0) cost[i]=0;
		else if((v[i]+1)%x==0||(v[i]-1)%x==0) cost[i]=b;
		else cost[i]=inf;
	}
	for(rr i=1;i<=n;++i){
		if(cost[i]==inf){
			dp[i][0]=inf;
			dp[i][1]=min(dp[i-1][0],dp[i-1][1])+a;
			dp[i][2]=inf;
		}else{
		    dp[i][0]=dp[i-1][0]+cost[i];
		    dp[i][1]=min(dp[i-1][0],dp[i-1][1])+a;
		    dp[i][2]=min(dp[i-1][2],dp[i-1][1])+cost[i];
	    }
	}
	return min(dp[n][0],min(dp[n][1],dp[n][2]));
}
inline void init(ll x){//质因子分解 
	for(rr i=2;i*i<=x;++i){
		if(x%i) continue;//continue!!!要不然就是所有数暴力枚举 
		fac[res++]=i;
		while(x%i==0) x/=i;
	}
	if(x>1) fac[res++]=x;
}
int main(){
	while(~scanf("%I64d%I64d%I64d",&n,&a,&b)){
		for(rr i=1;i<=n;++i) v[i]=read();
		res=0;
		init(v[1]+1);init(v[1]);init(v[1]-1);
		init(v[n]+1);init(v[n]);init(v[n]-1);
		sort(fac,fac+res);
		res=unique(fac,fac+res)-fac;//不同质因子个数 
		ll ans=inf;
//		for(rr i=0;i<res;++i) cout<<fac[i]<<' ';
		for(rr i=0;i<res;++i) ans=min(ans,solve(fac[i]));
		printf("%I64d\n",ans);
	}
}
```


---

## 作者：Demeanor_Roy (赞：5)

- 有没有可能其他题解都做复杂了。

------------

前面和其他题解是同样思路，具体细节可以看他们的。这里主要讲讲枚举质因子之后的判断。

令 $p$ 为所枚举质因子，每一次我们把所有数分为能整除 $p$，加减一能整除 $p$，与其他三类。找到所有第三类数在的极小子区间 $[L,R]$，显然最后操作的区间 $[l,r]$ 必须满足 $l \leq L$ 且 $r \geq R$。

令 $pre_i,suc_i$ 分别表示前后缀第二类数个数。显然对于一个区间 $[l,r]$，其代价为 $(r-l+1) \times a + (pre_{l-1}+suc_{r+1}) \times b$。显然可以拆成只与 $l,r$ 有关的式子。于是处理出每个位置的贡献，做一下前后缀 $\min$， 就可以做到线性判断。

注意不存在第三类数时要特判一下不进行区间操作。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N=1e6+10;
int n,a,b,v[N],pre[N],suc[N],T[N];
LL pm[N],sm[N];
vector<int> vec;
inline void divite(int x)
{
	for(int i=2;i*i<=x;i++)	
	{
		if(x%i!=0) continue;
		while(x%i==0) x/=i;
		vec.push_back(i);
	}
	if(x!=1) vec.push_back(x);
} 
inline LL get(int x)
{
	for(int i=1;i<=n;i++) T[i]=(v[i]%x==0?0:((v[i]+1)%x==0||(v[i]-1)%x==0)?1:2);
	int L=n,R=1;bool ex=false;
	for(int i=1;i<=n;i++) pre[i]=pre[i-1]+!!T[i];
	for(int i=n;i>=1;i--) suc[i]=suc[i+1]+!!T[i];
	for(int i=1;i<=n;i++) if(T[i]==2) L=min(L,i),R=max(R,i),ex=true;
	LL res=ex?1e18:(LL)b*pre[n];
	for(int i=1;i<=L;i++) pm[i]=min(pm[i-1],(LL)pre[i-1]*b-(LL)i*a);
	for(int i=n;i>=R;i--) sm[i]=min(sm[i+1],(LL)suc[i+1]*b+(LL)(i+1)*a);
	for(int i=R-1;i>=1;i--) sm[i]=sm[i+1];
	for(int i=1;i<=L;i++) res=min(res,pm[i]+sm[i]);
	return res;
}
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	divite(v[1]-1);divite(v[1]);divite(v[1]+1);
	divite(v[n]-1);divite(v[n]);divite(v[n]+1);
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	LL ans=1e18;pm[0]=sm[n+1]=1e18;
	for(auto x:vec) ans=min(ans,get(x));
	printf("%lld",ans);
	return 0;
} 
```


---

## 作者：zcxxnqwq (赞：3)

为了避免变量重名，题目中的花费 $a$ 和 $b$ 以下统一用 $c$ 和 $d$ 代替qwq

~~首先我们可以省事地特判掉原序列的 $\gcd$ 就大于 $1$ 的情况。~~

对于其它情况，一个重要性质是 $a_1$ 或 $a_n$ 至少其一必定会被保留（可能被修改），所以最终序列的 $\gcd$ 必然是 $a_1,a_1+1,a_1-1,a_n,a_n+1,a_n-1$ 这六个数之一的因数。合数可以被拆成质数考虑，所以我们可以只考虑质数。

我们知道，一个 $1e9$ 以内的数只会有不超过 $8$ 个不同的质因子，所以 $6$ 个数最多也就 $48$ 个，当然实际远远达不到。故我们可以考虑枚举质因数来求解。

考虑 dp，设 $f[i][0/1][0/1]$ 表示前 $i$ 个数，用没用过修改操作，当前在不在用修改操作的答案（其实 $f[i][0][1]$ 是一定不合法的），那么大力分类即可：

- 当 $a_i$ 本身就合法，可以删，一定不修改：

	- $f[i][0][0]=f[i-1][0][0]$；
    - $f[i][1][0]=\min(f[i-1][1][0],f[i-1][1][1])$，即选择上一个删不删；
    - $f[i][1][1]=\min(f[i-1][0][0],f[i-1][1][1])+c$，也是选择上一个删不删。
    
- 当 $a_i$ 本身不合法，且 $a_i+1$ 和 $a_i-1$ 都不合法，必须删：

	- $f[i][0][0]=f[i][1][0]=inf$；
    - $f[i][1][1]=\min(f[i-1][0][0],f[i-1][1][1])+c$。
    
- 当 $a_i$ 本身不合法，且 $a_i+1$ 和 $a_i-1$ 至少有一个合法，可删可修改：
	
    - $f[i][0][0]=f[i-1][0][0]+d$；
    - $f[i][1][0]=\min(f[i-1][1][0],f[i-1][1][1])+d$；
    - $f[i][1][1]=\min(f[i-1][0][0],f[i-1][1][1])+c$，之前一定不能删过。
    
做完之后或许还有个神奇的疑问：这样会不会一不小心把数全删了呢？$p$ 是 $a_1$ 或 $a_n$ 的质因子的时候显然不会，其余情况下把 $a_1$ 或 $a_n$ 改完再删一定是更劣的，所以不会有这种情况。

每个质数 dp 一遍，复杂度即为大大大常数 $O(n)$，然而截止到写这篇题解，代码神奇地跑到了最优解第二名：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ff(i,s,e) for(int i=(s);i<=(e);++i)
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=1e6+5;
int n,a[N],c,d,p[100],tot;
ll f[N][2][2];
inline void work(int x){
	for(int i=2;i*i<=x;++i){
		if(x%i) continue;
		p[++tot]=i;
		while(x%i==0) x/=i;
	}
	if(x>1) p[++tot]=x;
}
inline ll dp(int p){
	ff(i,1,n){
		if(a[i]%p==0){
			f[i][0][0]=f[i-1][0][0];
			f[i][1][0]=min(f[i-1][1][0],f[i-1][1][1]);
			f[i][1][1]=(f[i-1][0][0],f[i-1][1][1])+c;
		}
		else{
			if((a[i]+1)%p!=0&&(a[i]-1)%p!=0){
				f[i][0][0]=f[i][1][0]=1e17;
				f[i][1][1]=min(f[i-1][0][0],f[i-1][1][1])+c;
			}
			else{
				f[i][0][0]=f[i-1][0][0]+d;
				f[i][1][0]=min(f[i-1][1][0],f[i-1][1][1])+d;
				f[i][1][1]=min(f[i-1][0][0],f[i-1][1][1])+c;
			}
		}
	}
	return min(f[n][0][0],min(f[n][1][0],f[n][1][1]));
}
signed main(){
	n=read(),c=read(),d=read();
	int g=0;
	ff(i,1,n) a[i]=read(),g=__gcd(g,a[i]);
	if(g>1) return puts("0"),0;
	work(a[1]),work(a[1]-1),work(a[1]+1);
	work(a[n]),work(a[n]-1),work(a[n]+1);
	sort(p+1,p+tot+1);
	tot=unique(p+1,p+tot+1)-p-1;
	ll ans=1e17;
	ff(i,1,tot) ans=min(ans,dp(p[i]));
	printf("%lld\n",ans);
}
```

 

---

## 作者：Jμdge (赞：3)

还是有点 ``♂ `` 的...【虽说应该紫色差不多就是了】

题目就是说一个序列可以去掉中间一段区间以及让每个数加一或减一，但操作有代价，求能让操作后的序列 gcd 不为 1 的最小代价

考虑枚举一个质因子，然后线性 dp 

但枚举哪个质因子却是个问题，于是我们考虑到序列不能全部去除，那么首尾两个元素必有一个留下来，那么 gcd 从这两个元素以及他们加一减一的值里面去筛就好了，元素个数很少（可以视为一个 log？）

且 dp 时常数较小（假装），可以通过此题


dp 设计：

>令 $F[0][i]$ 表示处理到第 i 个元素，尚未使用删除区间的操作 的最小代价

>令 $F[1][i]$ 表示处理到第 i 个元素，正在使用删除区间的操作 的最小代价

>令 $F[2][i]$ 表示处理到第 i 个元素，已经使用删除区间的操作 的最小代价

另外要预处理某个元素能否被当前枚举的质因子整除的信息，如果能被整除就让其 cost 值为 b ，否则 inf

具体转移式不难理解，可参照代码


# code

```cpp
//by Judge
#include<bits/stdc++.h>
#define Rg register
#define fp(i,a,b) for(Rg int i=(a),I=(b)+1;i<I;++i)
#define ll long long
using namespace std;
const int M=1e6+3;
typedef ll arr[M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline ll Min(ll x,ll y){return x<y?x:y;}
inline bool cmin(ll& a,ll b){return a>b?a=b,1:0;}
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} int n,m,a,b; arr v,p,c,f[3]; ll ans=1e18;
inline void init(ll x){
	for(Rg ll i=2;i*i<=x;++i)if(!(x%i)){
		p[++m]=i; while(!(x%i)) x/=i;
	} if(x>1) p[++m]=x;
}
inline ll solv(ll x){
	fp(i,1,n){
		if(!(v[i]%x)) c[i]=0;
		else if(!((v[i]+1)%x)||!((v[i]-1)%x)) c[i]=b;
		else c[i]=-1;
	}
	f[0][0]=f[1][0]=f[2][0]=0;
	fp(i,1,n){
		if(c[i]<0){
			f[0][i]=f[2][i]=1e18;
			f[1][i]=Min(f[0][i-1],f[1][i-1])+a;
		} else{
			f[0][i]=f[0][i-1]+c[i];
			f[1][i]=Min(f[0][i-1],f[1][i-1])+a;
			f[2][i]=Min(f[2][i-1],f[1][i-1])+c[i];
		}
	} return Min(f[0][n],Min(f[1][n],f[2][n]));
}
int main(){
	n=read(),a=read(),b=read();
	fp(i,1,n) v[i]=read();
	init(v[1]+1),init(v[1]),init(v[1]-1);
	init(v[n]+1),init(v[n]),init(v[n]-1);
	sort(p+1,p+1+m),m=unique(p+1,p+1+m)-p-1;
	fp(i,1,m) cmin(ans,solv(p[i])); return !printf("%lld\n",ans);
}


```


---

## 作者：wenge (赞：2)

这道题看上去要gcd，实际上完全不需要。

由“不能删除整个数组”可知，$a_1$和$a_n$至少要留下一个，所以只需枚举$a_1,a_n,a_1+1,a_n+1,a_1-1,a_n-1$的每一个不同约数，作为整个数组的gcd，进行dp。

$dp[i][0]$表示考虑到第i个数，还没有开始删数时的最小花费

$dp[i][1]$表示考虑到第i个数，表示正在删数时的最小花费

$dp[i][2]$表示考虑到第i个数，表示删数已经用完时的最小花费

状态转移方程见代码。

因为$n<=1000000,a_i<=10^9$，所以计算可知，$a_1,a_n,a_1+1,a_n+1,a_1-1,a_n-1$的每一个不同约数的个数最多28个，所以最坏时间复杂度为$O(28n)$，但是常数貌似很大。

至于为什么可以通过本题，也许是因为数据比较水吧。

AC代码：
```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
#include <queue>
#include <iomanip>
using namespace std;
typedef long long ll;
ll n,a,b,p,ans=(1ll<<62);
ll ai[1000005],dp[1000005][3];
/*
ll gcd(ll x,ll y){
    if(y==0)return x;
    return gcd(y,x%y);
}
*/
void dp1(ll,ll);
void solve(ll n,ll cost,ll pos){
    ll i=2,m=sqrt(n);
    while(n>1&&i<=m){
        if(n%i==0){
            while(n%i==0)n/=i;
            memset(dp,0x7f,sizeof(dp));
            dp[1][0]=cost;
            dp1(i,pos);
        }
        i++;
    }
    if(n>1){
        memset(dp,0x7f,sizeof(dp));
        dp[1][0]=cost;
        dp1(n,pos);
    }
}
void dp1(ll p,ll pos){
    if(pos){
        reverse(ai+1,ai+n+1);
    }
    for(int i=2;i<=n;i++){
        if(ai[i]%p==0)
            dp[i][0]=dp[i-1][0];
        else if((ai[i]+1)%p==0||(ai[i]-1)%p==0)
            dp[i][0]=dp[i-1][0]+b;
        
        dp[i][1]=min(dp[i-1][0],dp[i-1][1])+a;
        
        if(ai[i]%p==0){
            dp[i][2]=min(dp[i-1][1],dp[i-1][2]);
        }
        else if((ai[i]+1)%p==0||(ai[i]-1)%p==0){
            dp[i][2]=min(dp[i-1][1],dp[i-1][2])+b;
        }
    }
    /*
    for(int i=1;i<=n;i++)cout<<dp[i][0]<<" ";
    cout<<endl;
    for(int i=1;i<=n;i++)cout<<dp[i][0]<<" ";
    cout<<endl;
    for(int i=1;i<=n;i++)cout<<dp[i][0]<<" ";
    cout<<endl;
    */
    
    ans=min(min(ans,dp[n][0]),min(dp[n][1],dp[n][2]));
    if(pos){
        reverse(ai+1,ai+n+1);
    }
}
int main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++){
        cin>>ai[i];
    }
    solve(ai[1],0,0);
    solve(ai[1]+1,b,0);
    solve(ai[1]-1,b,0);
    solve(ai[n],0,1);
    solve(ai[n]+1,b,1);
    solve(ai[n]-1,b,1);
    cout<<ans;
    return 0;
}
```


---

## 作者：Lucky_Xiang (赞：1)

## 题目

[CF623B](https://www.luogu.com.cn/problem/CF623B)

## 分析

观察可以发现，无论如何删除，$a_1$ 或 $a_n$ 会被保留，也就是说 $\gcd$ 一定是 $a_1$ 或 $a_n$ 的约数。直接枚举约数太多了，不妨只枚举是**质数**的约数 $d$，并将限制变成所有数都是 $d$ 的**倍数**。注意到 $\forall x\le 10^9$，$\omega(x)\le 9$，所以这样做时间复杂度是可以接受的。

确定 $d$ 以后，序列被分成了三种数：

1. 已经满足条件的数；
2. $+1$ 或 $-1$ 后满足条件的数；
3. $+1$ 或 $-1$ 后也不能满足条件的数。

对于第三种数，必须使用**区间删除**。

### 情况一

假设存在第三种数，则区间 $[L,R]$ 必须被删除。

设实际被删除的区间为 $[l,r]$，则一定满足 $[L,R]\subseteq [l,r]$。

注意到 $l$ 的选择和 $r$ 的选择是**独立的**。于是可以枚举 $l<L$ 尝试将 $[l,L-1]$ 也进行**区间删除**，找到最优的 $l$；同时枚举 $r>R$ 尝试将 $[R+1,r]$ 也进行**区间删除**，找到最优的 $r$。

这样最优的 $[l,r]$ 就被 $O(n)$ 找到了。

### 情况二

那么没有第三种数怎么处理呢？设第二种数的位置分别为 $x_1\sim x_k$。答案显然可以为 $B\times k$，但是可以使用**区间删除**操作使答案更优。

最终被删除的区间一定是 $[x_l,x_r]$ 的形式。可以枚举 $x_r$ 的值，找到对应最优的 $x_l$ 的位置。设 $x_i$ 的**最优位置**是 $x_{y_i}$（如果有多个值相同，取最左边的值）。

注意到这个 dp 非常特殊。假设现在已知 $y_1\sim y_{i-1}$ 的值：

- 如果 $y_i<y_{i-1}$，则 $y_{i-1}$ 取 $y_i$ 显然更优，**不可能**出现这种情况；
- 如果 $y_{i-1}<y_i<i$，则 $y_{i-1}$ 取 $y_i$ 也更优，**不可能**出现这种情况。

因此 $y_i$ **要么**等于 $y_{i-1}$，**要么**等于 $i$。直接比较一下即可，也可以 $O(n)$ 求解。

-----

总时间复杂度 $O\Big(\omega(x)n\Big)$，其中 $\omega(x)\le 9$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mn=1000010;
int n;
int a[mn];
LL A,B;
LL res;
void dp(vector<int>&vec)
{
    int N=vec.size();
    res=min(res,N*B);
    int pos=0;
    for(int i=0;i<N;i++)
    {
        if((i-pos)*B<(vec[i]-vec[pos])*A)pos=i;
        res=min(res,(vec[i]-vec[pos]+1)*A+(pos+N-i-1)*B);
    }
}
void solve(int d)
{
    if(d==1)return;
    vector<int>vec;
    int L=n+1, R=0;
    for(int i=1;i<=n;i++)
    {
        if((a[i]+1)%d && a[i]%d && (a[i]-1)%d)
        {
            L=min(L,i);
            R=max(R,i);
        }
        else if(a[i]%d)vec.push_back(i);
    }
    LL ans=0;
    if(L<=R)
    {
        ans+=A*(R-L+1);
        
        int cnt=0;
        for(int i=L-1;i>=1;i--)if(a[i]%d)cnt++;
        LL tmp=cnt*B;
        for(int i=L-1;i>=1;i--)
        {
            if(a[i]%d)
            {
                cnt--;
                tmp=min(tmp,cnt*B+(L-i)*A);
            }
        }
        ans+=tmp;

        cnt=0;
        for(int i=R+1;i<=n;i++)if(a[i]%d)cnt++;
        tmp=cnt*B;
        for(int i=R+1;i<=n;i++)
        {
            if(a[i]%d)
            {
                cnt--;
                tmp=min(tmp,cnt*B+(i-R)*A);
            }
        }
        ans+=tmp;

        res=min(res,ans);
    }
    else dp(vec);
}
void SOLVE(int x)
{
    for(int k=2;k*k<=x;k++)
    {
        if(x%k==0)solve(k);
        while(x%k==0)x/=k;
    }
    solve(x);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>A>>B;
    for(int i=1;i<=n;i++)cin>>a[i];
    if(n==1)
    {
        cout<<0<<endl;
        return 0;
    }
    res=A*(n-1);
    for(int x=-1;x<=1;x++)
    {
        SOLVE(a[1]+x);
        SOLVE(a[n]+x);
    }
    cout<<res<<endl;
    return 0;
}
```

---

## 作者：tder (赞：0)

翻译翻了个啥。

---

对于给定的序列 $\{v_n\}$，可以进行以下操作：

- 选定 $[l,r]$，删除 $v_l$ 至 $v_r$，只能进行一次，且需要保证 $r-l+1<n$；
- 选定 $x$，将 $v_x$ 变为 $v_x+1$ 或 $v_x-1$，对于每个 $x$ 只能进行一次。

第一种操作的代价为 $a\times(r-l+1)$，而第二种操作的代价为 $b$。

求使得 $\gcd(v_i)>1$ 的最小代价。

---

由于我们删除的区间长度小于 $n$，则 $v_1$ 或 $v_n$ 必定有一个未被删除，因此最后的 $\gcd$ 一定是 $v_1$ 或 $v_n$ 进行第二种操作后的值的因数，即在 $S=\text{div}(v_1)\cup\text{div}(v_1-1)\cup\text{div}(v_1+1)\cup\text{div}(v_n)\cup\text{div}(v_n-1)\cup\text{div}(v_n+1)$ 中，其中 $\text{div}(x)$ 表示 $x$ 的所有因数所组成的集合。

另有显然结论：若 $\gcd(x,y)=t\times p$，则 $p$ 一定也是 $x$ 和 $y$ 的一个因数，因此只需考虑质因数即可。

那么，我们不妨枚举 $S$ 中的每个质因数 $k$，计算代价取最小值。

我们用 $c_i$ 表示使得 $v_i$ 变为 $k$ 的倍数时的代价，显然有：

$$
c_i=
\begin{cases}
0,&v_i\equiv 0\pmod k \\
1,&(v_i-1)\equiv 0\pmod k \\
1,&(v_i+1)\equiv 0\pmod k \\
+\infty,&\text{otherwise}. \\
\end{cases}
$$

因此可以计算 $\text{mn}=\displaystyle\min_{c_i=+\infty}i$ 和 $\text{mx}=\displaystyle\max_{c_i=+\infty}i$，则最终我们选择删除的区间 $[l,r]$ 必须满足 $l\le\text{mn}$ 且 $r\ge\text{mx}$。

那么，假设我们删除区间 $[l,r]$ 时，其代价为：

$$
\text{cost}=\sum_{i=1}^{l-1}c_i+a\times(r-l+1)+\sum_{i=r+1}^{n}c_i
$$

显然其中的两个 $\sum c_i$ 均可使用前后缀和预处理。

于是取最小代价即可。

---

## 作者：Purslane (赞：0)

# Solution

$\rm DP$ 是啥，能吃吗，不会欸。

显然我们只需要考虑让整个区间的 $\gcd$ 是某个质数的倍数。
而这个数只可能在 $P(a_1) \cup P(a_1+1) \cup P(a_1-1) \cup P(a_n) \cup P(a_n+1) \cup P(a_n-1)$ 中出现，不然必定要把整个序列给删光光。

考虑固定了 $p$。现在只有三种数：$p$ 的倍数；调整之后可以成为 $p$ 的倍数；无论怎么做都不是 $p$ 的倍数。

对于第三类数，我们找到最左边的那一个和最右边的那一个，记为 $l$ 和 $r$，则 $[l,r]$ 这一段区间都必定要给删掉。

那么考虑我们要删掉 $[1,l-1]$ 的一段后缀。很容易扫描一遍看看哪个后缀是最优的，另一端同理。

复杂度 $O(n |P|_{\max})$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000000+10;
int n,a,b,ans=LONG_LONG_MAX,v[MAXN],mzx[MAXN];
int solve(int p) {
	int l=n+1,r=0;
	ffor(i,1,n) if(v[i]%p!=0&&(v[i]-1)%p!=0&&(v[i]+1)%p!=0) l=min(l,i),r=max(r,i);
	if(l==n+1) {
		int ans=0x3f3f3f3f3f3f3f3f;
		ffor(i,1,n) if(v[i]%p!=0) mzx[i]=b; else mzx[i]=0;
		ffor(i,1,n) mzx[i]+=mzx[i-1];
		int mn=0;
		ffor(r,1,n-1) {
			mn=min(mn,mzx[r]-r*a);
			ans=min(ans,mzx[n]-mzx[r]+mn+r*a);
		}
		roff(i,n,1) mzx[i]-=mzx[i-1];
		reverse(mzx+1,mzx+n+1);
		ffor(i,1,n) mzx[i]+=mzx[i-1];
		mn=0;
		ffor(r,1,n-1) {
			mn=min(mn,mzx[r]-r*a);
			ans=min(ans,mzx[n]-mzx[r]+mn+r*a);
		}
		return ans;	
	}
	int vall1=0,valr1=0,vall2=0x3f3f3f3f3f3f3f3f,valr2=0x3f3f3f3f3f3f3f3f,pre=0;
	ffor(i,0,l-1) {
		if(i) if(v[i]%p!=0) pre+=b;
		if(i==0) vall1=pre+(l-1-i)*a;
		else vall2=min(vall2,pre+(l-1-i)*a);
	}
	pre=0;
	roff(i,n+1,r+1) {
		if(i!=n+1) if(v[i]%p!=0) pre+=b;
		if(i==n+1) valr1=pre+(i-r-1)*a;
		else valr2=min(valr2,pre+(i-r-1)*a);
	}
	return max(0ll,(r-l+1))*a+min({vall1+valr2,valr1+vall2,vall2+valr2});
}
void check(int n) {
	if(n==0) return ;
	ffor(i,2,n/i) if(n%i==0) {
		ans=min(ans,solve(i));
		while(n%i==0) n/=i;
	}
	if(n>=2) ans=min(ans,solve(n));
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>a>>b; ffor(i,1,n) cin>>v[i];
	if(n==1) return cout<<(v[1]==1)?1:0,0;
	check(v[1]),check(v[1]+1),check(v[1]-1),check(v[n]),check(v[n]-1),check(v[n]+1);
	cout<<ans;
	return 0;
}
```

---

## 作者：RiceFruit (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF623B)

## 题目大意

给你一个长度为 $n$ 的序列 $a$，你可以进行以下操作：

$1.$ 删除一个区间，代价为区间长度 $\times a$，只能使用一次

$2.$ 将一个数 $±1$，代价为 $b$，对于每个数只能使用一次

## 主体思路

我们考虑 $1$ 操作，若将数组全部删光，肯定不如留一个数优，所以 $a_1$ 或 $a_n$ 一定会留下来，而 $a_1$ 可能变为 $a_1-1$，$a_1$，$a_1+1$，$a_n$ 同理。

那么 $\gcd$ 肯定是这六个数（$a_1-1,a_1,a_1+1,a_n-1,a_n,a_n+1$）的一个数的质因子的倍数，则我们就枚举这个质因子：

设当前这个质因子为 $p$，则对于每个数，要么让它被删掉，要么让他成为 $p$ 的倍数。

则我们定义一个数组 $val$，表示让 $a$ 成为 $p$ 的倍数的花费。

若 $a_i\bmod p=0$，则 $val_i=0$

否则若 $(a_i-1)\bmod p=0||(a_i+1)\bmod p=0$，则 $val_i=b$

否则 $val_i=inf$。

在定义数组 $dp$，含义如下：

+ $dp_{i,0}$ 第 $1$ 位到第 $i$ 位都没有被删除时，所对的答案
+ $dp_{i,1}$ 从某一位开始删除（可以为 $i$），删到了 $i$ 所对的答案
+ $dp_{i,2}$ 第 $i$ 位之前已经删除完了，且第 $i$ 位不删除所对的答案。

转移如下：

+ $dp_{i,0}=dp_{i-1,0}+val_i$
+ $dp_{i,1}=\min(dp_{i-1,0},dp_{i-1,1})+a$
+ $dp_{i,2}=\min(dp_{i-1,1},dp_{i-1,2})+val_i$

那么此题就解决了。

## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register
#define ri register int
#define int long long
#define ull unsigned long long
#define lid (id<<1)
#define rid (id<<1|1)
void swap(int &x,int &y){int t=x;x=y;y=t;}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
const int N=2e6+5,inf=1e10;
inline int read();
inline void write(int ans);
inline void put(int x,char c);
int n,x,y;
int a[N];
int dp[N][3];
int cost[N];
int ans=inf*137777;
void dothis(int p){
	memset(dp,0,sizeof dp);
	for(int i=1;i<=n;i++){
		if(a[i]%p==0) cost[i]=0;
		else if((a[i]-1)%p==0||(a[i]+1)%p==0) cost[i]=y;
		else cost[i]=inf;
	}
	for(int i=1;i<=n;i++){
		dp[i][0]=dp[i-1][0]+cost[i];
		dp[i][1]=min(dp[i-1][0],dp[i-1][1])+x;
		dp[i][2]=min(dp[i-1][1],dp[i-1][2])+cost[i];
	}
	int val=min(min(dp[n][0],dp[n][1]),dp[n][2]);
	ans=min(ans,val);
	return ;
}
void gx(int x){
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			dothis(i);
			x/=i;
			while(x%i==0)x/=i;
		}
	}
	if(x>1) dothis(x);
	return ;
}
signed main(){
	n=read(),x=read(),y=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	gx(a[1]-1),gx(a[1]),gx(a[1]+1);
	if(n!=1) gx(a[n]-1),gx(a[n]),gx(a[n]+1);
	printf("%lld\n",ans);
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x % 10+'0');return;}
inline void put(int x,char c){write(x);putchar(c);return;}
```

---

