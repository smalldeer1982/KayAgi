# Lucky Subsequence

## 题目描述

Petya loves lucky numbers very much. Everybody knows that lucky numbers are positive integers whose decimal record contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya has sequence $ a $ consisting of $ n $ integers.

The subsequence of the sequence $ a $ is such subsequence that can be obtained from $ a $ by removing zero or more of its elements.

Two sequences are considered different if index sets of numbers included in them are different. That is, the values ​of the elements ​do not matter in the comparison of subsequences. In particular, any sequence of length $ n $ has exactly $ 2^{n} $ different subsequences (including an empty subsequence).

A subsequence is considered lucky if it has a length exactly $ k $ and does not contain two identical lucky numbers (unlucky numbers can be repeated any number of times).

Help Petya find the number of different lucky subsequences of the sequence $ a $ . As Petya's parents don't let him play with large numbers, you should print the result modulo prime number $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample all $ 3 $ subsequences of the needed length are considered lucky.

In the second sample there are $ 4 $ lucky subsequences. For them the sets of indexes equal (the indexation starts from $ 1 $ ): $ {1,3} $ , $ {1,4} $ , $ {2,3} $ and $ {2,4} $ .

## 样例 #1

### 输入

```
3 2
10 10 10
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 2
4 4 7 7
```

### 输出

```
4
```

# 题解

## 作者：Epoch_L (赞：2)

题目链接：

[洛谷](https://www.luogu.com.cn/problem/CF145C "洛谷")

[Codeforces](http://codeforces.com/problemset/problem/145/C "Codeforces")
## Problem
这题目翻译真的神了，好多歧义，看不懂。给一个本人翻译：

给你一个长度为 $n$ 的序列 $a$，定义幸运数为**仅**含有 $4$ 或 $7$ 的数，你需要取出它的一个的子序列，满足以下条件：
+ 长度为 $k$。
+ 不能出现相同的幸运数，即最多 $1$ 次，其它数可出现任意次数。

问有多少种取法，对 $10^9+7$ 取模。
## Solution
计数题，首先要想好策略，这题只有两种数，所以肯定是枚举其中一种数的个数。

对于幸运数，其数量显然不会很多，所以设 $f(i,j)$ 为前 $i$ 种幸运数选 $j$ 个的方案，由于每种只能选一个，有选或不选，所以：
$$
f(i,j)=f(i-1,j)+f(i-1,j-1)\times s_i
$$
其中 $s_i$ 表示第 $i$ 种幸运数的个数。然后很容易像 01 背包一样把第一维滚掉。

对于非幸运数，直接组合数就可以了。

令 $t$ 为非幸运数的个数，枚举选 $i$ 个幸运数，所以最后的答案为：
$$
\sum_{i=0}^kf_i\times \binom{t}{k-i}
$$
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void read(int &x)
{
	char ch=getchar();
	int r=0,w=1;
	while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
	x=r*w;
}
const int N=1e5+7,mod=1e9+7;
int f[N],s[N],cnt,p[N];
map<int,int>mp;
void init()
{
	p[0]=1;
	for(int i=1;i<=1e5;i++)p[i]=p[i-1]*i%mod;
}
int Pow(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
int C(int n,int m)
{
	if(m==0)return 1;
	if(n<m)return 0;
	return p[n]*Pow(p[m],mod-2)%mod*Pow(p[n-m],mod-2)%mod;
}
bool check(int x)
{
	while(x)
	{
		if(x%10!=4&&x%10!=7)return false;
		x/=10;
	}
	return true;
}
main()
{
	init();
	int n,k,t=0;
	read(n);read(k);
	for(int i=1,x;i<=n;i++)
	{
		read(x);
		if(check(x))
		{
			if(!mp[x])mp[x]=++cnt;
			s[mp[x]]++;
		}
		else t++;
	}
	f[0]=1;
	for(int i=1;i<=cnt;i++)
	for(int j=cnt;j>=1;j--)
		f[j]=(f[j]+f[j-1]*s[i]%mod)%mod;
	int ans=0;
	for(int i=0;i<=k;i++)
		ans=(ans+f[i]*C(t,k-i)%mod)%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：ran_qwq (赞：1)

朴素的做法是枚举选中的幸运数集合 $S$，设 $c_x$ 为 $x$ 出现次数，$t$ 为非幸运数个数。有

$$\sum\limits_S\binom t{k-|S|}\prod\limits_{x\in S}c_x$$

种方案。其中 $\binom t{k-|S|}$ 是非幸运数方案数，$\prod\limits_{x\in S}c_x$ 是幸运数方案数。

容易发现如果枚举 $|S|$，前面那项是定值，只用考虑

$$\sum\limits_{|S|=i}\prod\limits_{x\in S}c_x$$

的值。

这是一个典型的可以 $n^2$ dp 的形式。$f_{i,j}$ 为前 $i$ 种幸运数取了 $j$ 种的方案数，可从 $f_{i-1,j}$ 和 $f_{i-1,j-1}$ 转移。

$a_i\le10^9$，所以幸运数只有 $2^0+2^1+2^2+\dots+2^9=1023$ 个，可以通过。

```cpp
int n,m,ln,tt,as,b[M],f[M][M],fc[N],ifc[N],ct[N]; map<int,int> mp;
void dfs(int k,int x) {
	if(k!=1) b[++ln]=x,mp[x]=ln;
	if(k<=9) dfs(k+1,x*10+4),dfs(k+1,x*10+7);
}
il int c(int x,int y) {return x<0||y<0||x<y?0:vmul(fc[x],vmul(ifc[y],ifc[x-y]));}
void QwQ() {
	n=rd(),m=rd(),dfs(1,0);
	for(int i=1,x;i<=n;i++) {
		x=rd();
		if(mp[x]) ct[mp[x]]++;
		else tt++;
	}
	f[0][0]=1;
	for(int i=1;i<=ln;i++) for(int j=0;j<=ln;j++) f[i][j]=vadd(f[i-1][j],j?vmul(f[i-1][j-1],ct[i]):0);
	fc[0]=1;
	for(int i=1;i<=n;i++) fc[i]=vmul(fc[i-1],i);
	ifc[n]=qpow(fc[n],MOD-2);
	for(int i=n-1;~i;i--) ifc[i]=vmul(ifc[i+1],i+1);
	for(int i=0;i<=min(ln,m);i++) cadd(as,vmul(f[ln][i],c(tt,m-i)));
	wr(as,"\n");
}
```

---

## 作者：white_tiger_yyyy (赞：1)

首先，我们对这个幸运数进行分析，发现：

+ $10^9$ 以内只有 $1023$ 个幸运数，即 $\sum\limits_{i=0}^92^i$ 个。

考虑对幸运数和非幸运数分类讨论。

1. 幸运数部分：
   01 背包裸题，$dp_{i,j}$ 表示前 $i$ 个幸运数里选了 $j$ 个，转移方程为 $dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-1}\times num_i$，可滚动数组。
2. 非幸运数部分
   设选了 $j$ 个幸运数，一共有 $m$ 个非幸运数，则有 $C_m^{k-i}$ 种可能性。

所以答案就是 $\sum\limits_{i=0}^{\min(l,k)}dp_{l,i}\times C_m^{k-i}$，其中 $l$ 为幸运数的种类数。

时间复杂度 $O(l^2+n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll p=1e9+7;
const int N=1e5+5,M=1025;
ll qpow(ll x,int y){
    ll re=1;
    while(y){
        if(y&1) re=re*x%p;
        x=x*x%p;
        y>>=1;
    }return re;
}int n,k,m,l;
ll jc[N],inv[N],dp[M],num[M],ans;
unordered_map<int,int>a;
void init(){
	jc[0]=inv[0]=1;
	for(ll i=1;i<=n;i++){
		jc[i]=jc[i-1]*i%p;
		inv[i]=qpow(jc[i],p-2);
	}
}ll C(int x,int y){
	if(x<y) return 0;
	return jc[x]*inv[y]%p*inv[x-y]%p;
}int check(int x){
	while(x){
		int y=x%10;
		if(y!=4&&y!=7)
			return 0;
		x/=10;
	}return 1;
}int main(){
	cin>>n>>k;
	init();
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(check(x)){
			if(!a[x]) a[x]=++l;
			num[a[x]]++;
		}else m++;
	}dp[0]=1;
	for(int i=1;i<=l;i++)
		for(int j=min(i,k);j;j--)
			dp[j]=(dp[j]+dp[j-1]*num[i])%p;
	for(int i=0;i<=min(l,k);i++)
		ans=(ans+dp[i]*C(m,k-i))%p;
	cout<<ans;
    return 0;
}
```

---

## 作者：Styx (赞：1)

啊，好久没有做到这么水的E题了

仍然先是题意：

定义神仙数为只含4和7的数字

给出n个数字，让你从里面取k个，同一个神仙数不能重复取，求取法数

首先如果没有重复取这个限制，这就是一道线性求组合数。

就算有这个限制，全部不能重复取也是可做的，所以自然会感觉这种部分可重复部分不能的题很难受，于是会想到将原来的数组拆成两组，一组只有神仙数，一组只有非神仙数

然后答案就是在神仙数中取i个，在非神仙数中取k-i个的方案相乘，再将i=1~n的所有方案相加起来，就是答案

非神仙数显然可以线性处理组合数，O(1)查询

如今的问题是如何解决神仙数

首先需要搞清楚神仙数的一个性质：他非常少

这是可以证明的

一位的时候有4/7两种，两位有4种，反正1e9内大概不到3000个

这可以n^2DP

令dp[i][j]表示到第i位取j个数的方案数

显然dp[i][j]=dp[i-1][j]+dp[i-1][j-1]*num[a[i]]

num[a[i]]表示大小为a[i]的神仙数个数

于是就可以A掉这题了

代码如下：
```cpp
#include<map>
#include<cmath>
#include<stack>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define mod 1000000007
using namespace std;

long long fac[100010],inv[100010],n,m,ans;
map<long long,int> m1;
vector<long long> a,b;
long long dp[3010][3010];

long long kasumi(long long a,long long b)
{
	long long ans=1;
	while(b)
	{
		if(b&1)
		{
			ans=ans*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

long long c(int n,int m)
{
	if(n>m) return 0ll;
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}

int check(long long x)
{
	while(x)
	{
		if(x%10!=4&&x%10!=7) return 0;
		x/=10;
	}
	return 1;
}

int main()
{
	fac[0]=1;
	inv[0]=1;
	for(int i=1; i<=100000; i++)
	{
		fac[i]=fac[i-1]*i%mod;
	}
	inv[100000]=kasumi(fac[100000],mod-2);
	for(int i=99999; i>=1; i--)
	{
		inv[i]=inv[i+1]*(i+1)%mod;
	}
	scanf("%lld%lld",&n,&m);
	long long tmp;
	for(int i=1; i<=n; i++)
	{
		scanf("%lld",&tmp);
		if(check(tmp))
		{
			if(m1.count(tmp))
			{
				m1[tmp]++;
			}
			else
			{
				m1[tmp]++;
				a.push_back(tmp);
			}
		}
		else
		{
			b.push_back(tmp);
		}
	}
	for(int i=0;i<=3000;i++)
	{
		dp[i][0]=1;
	}
	if(a.size()>=1)
	{
		dp[0][1]=m1[a[0]];
		for(int i=1; i<a.size(); i++)
		{
			for(int j=1; j<=a.size(); j++)
			{
				dp[i][j]=dp[i-1][j]+dp[i-1][j-1]*m1[a[i]];
				dp[i][j]%=mod;
			}
		}
	}
	int lena=a.size(),lenb=b.size();
	ans+=c(m,lenb);
	for(int i=1; i<=min(lena*1ll,m); i++)
	{
		ans+=dp[lena-1][i]*c(m-i,lenb);
		ans%=mod;
	}
	printf("%lld\n",ans);
}
```



---

## 作者：N1K_J (赞：0)

首先要注意到幸运数非常少（$2^9$ 个左右），考虑 $dp[i][j]$ 前 $i$ 中幸运数选 $j$ 个，共有幸运数 $S$ 个。

那么会有 $dp[i][j] = dp[i-1][j]+dp[i-1][j-1] \cdot tot_i$，$tot_i$ 表示第 $i$ 个幸运数的出现次数。

那么不妨设取出的 $k$ 个数里面有 $i$ 个幸运数，此时有 $dp[i] \cdot C(n-S,k-i)$ 种取法，全部加起来就好了。

注意代码里 dp 数组被滚动了第一维。

[Code](https://codeforces.com/contest/145/submission/250027284)

---

## 作者：dxrS (赞：0)

考虑到幸运数字特别少，只有 $2^9=512$ 个，可以考虑枚举幸运数字的数量 $i$，然后乘上在非幸运数字里面选择 $k-i$ 个的方案。

定义 $s$ 为 $[1,n]$ 中不同的幸运数字的数量，$cnt_i$ 表示第 $i$ 个幸运数字的出现次数，$c$ 表示非幸运数字的个数。

设 $dp_{i,j}$ 表示前 $i$ 个幸运数中选择 $k$ 个的方案数，那么这个数可以选，也可以不选，就有 $dp_{i,j}\gets dp_{i-1,j}+dp_{i-1,j-1}\times cnt_i$。

答案就是 $\sum\limits_{i=0}^kdp_{s,i}\times C_c^{k-i}$。

---

## 作者：XL4453 (赞：0)

### 解题思路：

数数题，显然分组处理。

将所有的数分为幸运数和一般数，每一次枚举取的幸运数的个数 $i$。

所有的非幸运数（就是翻译里的神仙数，也不知道怎么翻的）都好处理，啥都不需要考虑，直接就一个组合：$\dbinom{cnt}{k-i}$，其中 $cnt$ 表示非幸运数的个数，$k$ 表示总共要取的数的个数。

然后是幸运数的处理。对于每一个幸运数，我们其实并不关心这个数到底是多少，而只关心这个数到底有多少个，不妨将每一个数的数量记为 $tot_i$。这时就要看一下可能的幸运数的个数了，发现 $a_i$ 是不超过 $10^9$ 的，也就是说可能的幸运数一共有：$\sum_{i=1}^92^i$ 个，也就是 $2^{10}-1=1023$ 个。

这里用动态规划计数，$f_{i,j}$ 表示考虑到第 $i$ 个幸运数，已经取了 $j$ 个数的方案数。第一维随便优化掉，就和那个 01 背包一样。

发现这个也没有必要每一次都重新算，一开始算完然后 $O(1)$ 取出就行了。

---

注意取模。

我的数组是为了告诉你一共有 $1023$ 种幸运数才开这么大的，建议开大一点呢。

---
### 代码：

```cpp
#include<cstdio>
#include<map>
#define int long long
using namespace std;
const int MOD=1e9+7;
int n,tot[1025],x,k,cnt,m,f[100005],F[100005],inv[100005],ans;   
map<int,int> mp;
bool check(int num){
	while(num){
		if(num%10!=7&&num%10!=4)return 0;
		num/=10;
	}
	return 1;
}
int pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
int C(int n,int m){
	if(n<m)return 0;
	return F[n]*inv[m]%MOD*inv[n-m]%MOD;
}
signed main(){
	F[0]=1;
	for(int i=1;i<=1e5;i++)
	F[i]=(F[i-1]*i)%MOD;
	inv[100000]=pow(F[100000],MOD-2);
	for(int i=99999;i>=0;i--)
	inv[i]=(inv[i+1]*(i+1))%MOD;
	scanf("%I64d%I64d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%I64d",&x);
		if(check(x)){
			if(mp[x]==0)mp[x]=++m;
			tot[mp[x]]++;
		}
		else cnt++;
	}
	f[0]=1;
	for(int i=1;i<=m;i++)
	for(int j=m;j>=1;j--)
	f[j]=(f[j]+(f[j-1]*tot[i])%MOD)%MOD;
	for(int i=0;i<=k;i++)
	ans=(ans+f[i]*C(cnt,k-i))%MOD;
	printf("%I64d",ans);
	return 0;
}
```


---

## 作者：AladV (赞：0)

## 题意分析
就是问有多少个满足条件的子序列。

## 做法分析
感觉样例 2 非常有价值。设我们这个长度为 k 的子序列包含 x 个幸运数和 y 个非幸运数。显然，这 y 个非幸运数的范围是 $y\in [0,k]$，而且可以随便取，所以我们设有 tot 个非幸运数（总共），那么 y 这个部分的方案数就是 $C_{tot}^y$。

那么对于 x 的部分呢？我们想，对于一种幸运数（比如，4算一种，7 就算第二种），我们最多取一个。所以问题可以转化为在 cnt 种物品中，每种物品有 $siz_i$ 个，取 x 个，有多少种方法。标准的背包。 

之后再处理一下组合数即可。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=1e9+7;
const int N=1e5+5;
int a[N],cnt,n,k,tot,num[N],sum;
int dp[2010][2010];
int fac[N],inv[N];
int ans;
std::map<int,int> appear;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
bool iflucky(int x)
{
	while(x)
	{
		if(x%10!=4 && x%10!=7) return false;
		x/=10;
	}
	return true;
}
int qpow(int x,int n) 
{
	int res=1;
	while(n)
	{
		if(n&1) res=(res*x)%MOD;
		x=(x*x)%MOD;
		n>>=1;
	}
	return res;
}
int C(int n,int m)
{
    return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
signed main()
{
	n=1e5;
	fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=i*fac[i-1]%MOD;
    inv[1]=1;
    for(int i=2;i<=n;i++) inv[i]=MOD-(MOD/i)*inv[MOD%i]%MOD;
    inv[0]=1;
    for(int i=1;i<=n;i++) inv[i]=inv[i-1]*inv[i]%MOD;
	n=read(),k=read();
	// if(n==100 && k==7) cout<<334870375<<endl,exit(0);
	for(int i=1;i<=n;i++) a[i]=read();
	// sort(a+1,a+n+1);
	tot=0,cnt=0;
	// for(int i=1;i<=n;i++)
	// {
	// 	int j=i;
	// 	while(j<n && a[j]==a[j+1]) j++;
	// 	if(iflucky(a[i])) cnt++,num[cnt]=j-i+1;
	// 	else tot+=j-i+1;
	// 	i=j;
	// }
	for(int i=1;i<=n;i++)
	{
		if(iflucky(a[i]))
		{
			if(appear[a[i]]) num[appear[a[i]]]++;
			else appear[a[i]]=++cnt,num[appear[a[i]]]++;
		}
		else tot++;
	}
	// for(int i=1;i<=cnt;i++) sum+=num[i];
	// for(int i=1;i<=cnt;i++) cout<<num[i]<<" ";
	dp[0][0]=1;
	for(int i=1;i<=cnt;i++)
	{
		for(int j=0;j<=i;j++)
		{
			dp[i][j]=dp[i-1][j];
			if(!j) continue;
			dp[i][j]=(num[i]*dp[i-1][j-1]+dp[i][j])%MOD;
		}
	}
	for(int i=0;i<=min(tot,k);i++)
	{
		if((k-i)<=cnt)
		{
			int tmp=C(tot,i)*dp[cnt][k-i]%MOD;
			ans=(ans+tmp)%MOD;
			// ans%=MOD;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

