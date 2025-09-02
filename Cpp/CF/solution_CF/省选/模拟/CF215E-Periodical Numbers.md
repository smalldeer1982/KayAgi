# Periodical Numbers

## 题目描述

A non-empty string $ s $ is called binary, if it consists only of characters "0" and "1". Let's number the characters of binary string $ s $ from 1 to the string's length and let's denote the $ i $ -th character in string $ s $ as $ s_{i} $ .

Binary string $ s $ with length $ n $ is periodical, if there is an integer $ 1<=k&lt;n $ such that:

- $ k $ is a divisor of number $ n $
- for all $ 1<=i<=n-k $ , the following condition fulfills: $ s_{i}=s_{i+k} $

For example, binary strings "101010" and "11" are periodical and "10" and "10010" are not.

A positive integer $ x $ is periodical, if its binary representation (without leading zeroes) is a periodic string.

Your task is to calculate, how many periodic numbers are in the interval from $ l $ to $ r $ (both ends are included).

## 说明/提示

In the first sample periodic numbers are $ 3 $ , $ 7 $ and $ 10 $ .

In the second sample periodic numbers are $ 31 $ and $ 36 $ .

## 样例 #1

### 输入

```
1 10
```

### 输出

```
3
```

## 样例 #2

### 输入

```
25 38
```

### 输出

```
2
```

# 题解

## 作者：AladV (赞：4)

## 题意分析
就是让你找出在区间 $[l,r]$ 范围内有多少个数的二进制表示是周期性的。

## 做法分析
看到这样的题立马就可以想到答案是 $calc(r)-calc(l-1)$，已经成套路了。那么如何计算 calc 呢？

首先我们想到，整个二进制串的长度不会太大，所以我们先把 calc 函数传进去的参数做二进制拆分，然后根据这个二进制串的长度 len 我们枚举一下循环节的长度 $j$。

我们想到，如果当前枚举的位置 i 还不到 len，那么这个长度为 j 的循环节定然可以随便取，取多大都不会超过我们传进去的参数，因为长度是硬伤。所以在这个情况下，我们的答案就要加上 $2^{j-1}$。

那如果 $i=len$ 呢？我们想到了数位 $dp$，在枚举循环节长度之后我们发现，如果一个二进制周期串是如下所示的：

$1\ \ 0\ \ 1\ \ 1\ \ 1\ \ 0\ \ 1\ \ 1\ \ 1\ \ 0\ \ 1\ \ 1\ \ 1\ \ 0\ \ 1\ \ 1\ \ $

那么，他的十进制表示是多少呢？显然，是最低位的循环节的大小再乘上很多的很多个 2.所以我们计算在当前循环节长度下，这个数是多少，也就是：

`for(int i=1;i<=j;i++) c+=(a[len-i+1]<<(j-i));`

这是一个最低位循环节的和，总共的则是：

`b=c,for(int i=1;i<=len/j-1;i++) b<<=j,b+=c;`

之后我们只需判断一下这个数字是否大于 limit 即可。

最后一个重点：我们再观察一个二进制串：

$1\ \ 0\ \ 1\ \ 0\ \ 1\ \ 0\ \ 1\ \ 0\ \ 1\ \ 0\ \ 1\ \ 0\ \ 1\ \ 0\ \ 1\ \ 0$

发现没有？问题出在哪里？这个数字被长度为 2，4，8的循环节都计算了一遍！所以我们在统计的时候还要把当前循环节长度 j 的所有因子的答案都减掉，细节详见代码：

```c++
#include<stdio.h>
#include<string.h>
#include<iostream> 
using namespace std;
#define ll long long
int a[100];
ll dp[100];
ll cal(int len,int j,ll o)
{
	ll c=0,b=1;
	for(int i=1;i<=j;i++) c+=(a[len-i+1]<<(j-i));
	b=c;
	for(int i=1;i<=len/j-1;i++) b<<=j,b+=c;
	ll sum=1<<(j-1);
	return c-sum+(b<=o);
	
}
ll solve(ll w)
{
	int len=0;
	ll ww=w;
	ll ans=0;
	while(w)
	{
		a[++len]=w%2;
		w/=2;		
	}
	for(int i=2;i<=len;i++)
	{
		memset(dp,0,sizeof(dp));
		for(int j=1;j<=i/2;j++)
		{
			if(i%j!=0) continue;
			if(i<len) dp[j]+=(1<<(j-1));
			else dp[j]+=cal(len,j,ww);
			for(int k=1;k<j;k++)
			{
				if(j%k==0)
				dp[j]-=dp[k];
			}
			ans+=dp[j];
		}
	}
	return ans;
}
int main()
{
	ll n,m;
	cin>>n>>m;
	printf("%lld\n",solve(m)-solve(n-1));
	return 0;
}
```

---

## 作者：_edge_ (赞：3)

我不会数位 DP！

反正我用组合数学的方法也 A 掉了。

分析该题，经典套路是把 $[l,r]$ 拆成 $[1,r]-[1,l-1]$ 然后两个区间计算前缀和。

然后我们需要做的即为，求出所有 $\le x$ 合法的数。

然后我们会发现这个长度，循环节都特别小，那我们不妨去枚举它。

枚举的长度和循环节之后，我们只需要关心循环节内部填了什么即可。

对于长度小于 $x$ 的长度的，我们可以随便乱填。

对于长度等于 $x$ 的长度的，类似于数位 DP 的套路一样，我们对于每一位都按位考虑，如果这一位是 $1$，那么我们填 $0$ 之后后面的可以随便乱填。

对于这一位是 $0$，那没办法只能跑路。

需要注意的是最后一次我们填进去也有可能合法，需要单独计算。

然后，我们考虑一下有点小问题要处理。

首先，这个方法容易算重，比如说 `1111` 会被循环节 $1$ 算一次，被循环节 $2$ 算一次。

处理算重的问题很简单，只需要把它的因数以及长度全都枚举一遍就可以了，注意这里需要判断条件。

条件就是长度需要被两个都整除，且不能等于其中任意一个。

注意这里开 long long，同时按照数位 DP 的思想，每次应该都卡着上限，因此如果填 $1$ 的话，需要把循环节后面的也给搞成 $1$，判一下是否超出上限即可。

细节读者可以自行揣摩，这里不再做过多赘述。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long 
using namespace std;
const int INF=129;
int l,r,g[INF],f[INF][INF];
int calc1(int x,int y,int z) {
	int xx=0;
	for (int i=z;i<=y;i+=x) 
		xx|=(1ll<<(i-1));
	return xx;
}
int calc(int x){
	memset(f,0,sizeof f);
	int xx=x;g[0]=0;
	while (xx) {
		g[++g[0]]=xx%2;
		xx/=2;
	}
	for (int k=1;k<=g[0];k++) {
		f[k][0]=0;// k 为循环节长度 
		for (int i=k+k;i<=g[0];i+=k) {
			if (i<g[0]) f[k][i]+=(1ll<<(k-1));
			else {
				int p=0;
				for (int l=g[0];l>=1;l--) {
					if (l==g[0]) {p+=calc1(k,i,k);continue;}
					if (g[0]-l+1>k) continue;
					if (p>x) break;
					if (g[l]==1) {
						f[k][i]+=1ll<<(k-(g[0]-l+1));
						p+=calc1(k,i,k-(g[0]-l));
					}
				}
				if (p<=x) f[k][i]++;
			}
		}
	}
	int res=0;
	for (int i=0;i<=g[0];i++)
		for (int j=1;j<=g[0];j++)
			for (int k=j+j;k<=g[0];k+=j)
				if (i%k==0 && i%j==0 && i!=k) f[k][i]-=f[j][i];
	
	for (int i=0;i<=g[0];i++)
		for (int j=1;j<=g[0];j++)
			res+=f[j][i];
	return res;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>l>>r;
	cout<<calc(r)-calc(l-1)<<"\n";
	return 0;
}
```


---

## 作者：MyukiyoMekya (赞：2)

我们枚举数的长度 $len$，循环节长度 $k$ ，算出范围内有多少个数的二进制是长度为 $len$ 并且循环节长度为 $k$ 的，记为 $Ans_{len,k}$ ，这个可以用数位dp快速求，做法和 [SP10649 Mirror Number](https://www.luogu.com.cn/problem/SP10649) 类似，就是在数位dp的过程中开一个辅助数组来记录当前状态对应的循环节是什么。

求出了 Ans 数组后，发现直接把 Ans 数组里所有的数的和加起来会出现算重的情况，比如长度为 8，循环节长度为 4 的情况中一定包含了长度为 8，循环节长度为 2 的情况，那么把他们减去就行了。也就是
$$
Ans_{len,k} \leftarrow Ans_{len,k}-\sum _{g<k,g|k} Ans_{len,g}
$$
注意删的顺序，要从小到大删，也就是保证删 k 的时候 k 的因子已经不存在算重了。

$\texttt{Code:}$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define mem(x,y) memset(x,y,sizeof x)
#define ln puts("")
using namespace std;
template <class t> inline void read(t &s){
s=0;reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);return;}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;int buf[21],top=0;
while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;while(top)putchar(buf[top--]^'0');
return;}
int a[70],t[70],f[70][70],Len,D;// Len：枚举的数在二进制下的长度， D：枚举的循环节长度，t辅助数组
int Ans[70][70];
inline int dfs(int dep,int zero,bool lim)
    //dep：当前枚举到的位数，zero表示从哪一位开始的算的，用来弄前导0之类的
{
	if(!dep)
		return zero==Len;	// 长度是否跟枚举的长度一样
	if(!lim&&~f[dep][zero])
		return f[dep][zero];
	reg int maxi=lim?a[dep]:1,res=0;
	for(int i=0;i<=maxi;++i)
	{
		reg int nzero=zero;
		if(i&&!nzero)
			nzero=dep;		// 当前位置开始算，之前都是前导零
		if(nzero-dep<D)		// 还没有填满 D 个数
		{
			t[nzero-dep]=i;
			res+=dfs(dep-1,nzero,lim&&(i==maxi));
		}
		else if(t[(nzero-dep)%D]==i)	// 看是否能跟循环节一样
			res+=dfs(dep-1,nzero,lim&&(i==maxi));
	}
	if(!lim)
		f[dep][zero]=res;
	return res;
}
inline int calc(int x,int l,int d)
{
	reg int cnt=0;
	while(x)
		a[++cnt]=(x&1),x>>=1;
	mem(f,-1);
	Len=l;
	D=d;
	return dfs(cnt,0,true);
}
signed main(void)
{
	reg int l,r;read(l,r);
	for(int i=1;i<=64;++i)
		for(int j=1;j<i;++j)
			if(!(i%j))
				Ans[i][j]=calc(r,i,j)-calc(l-1,i,j);
	for(int i=1;i<=64;++i)		// 去重
		for(int j=1;j<i;++j)
			if(!(i%j))
				for(int k=1;k<j;++k)
					if(!(j%k))
						Ans[i][j]-=Ans[i][k];
	reg int ans=0;
	for(int i=1;i<=64;++i)
		for(int j=1;j<i;++j)
			ans+=Ans[i][j];
	write(ans),ln;
	return 0;
}
```



---

## 作者：_Day_Tao_ (赞：1)

来一种抽象的非正解做法。

首先我们可以发现一个性质，存在一个阈值 $P$，满足 $< P$ 的数三次拼接小于等于 $10^{18}$，$\ge P$ 的数三次拼接大于 $10^{18}$，由于 $\lfloor\log_210^{18}\rfloor=60$，所以可以猜测这个阈值在 $2^{20}$ 左右。经过验证（可以另外写一份代码），可以得出 $P=909494$。发现这个值比较小，可以直接枚举循环节 $< P$ 的数并暴力更新，拿个 set 存一下已经确定的数，这部分的时间复杂度为 $O(P \log^2 P)$，但是跑不满。

剩下的数就是只能组成循环节为 2 的数字了。又不难发现一个性质：在循环节个数相同时，循环节越大，组合出的数也就越大。这个还是比较显然的。这就有了单调性，可以二分出符合条件的左右端点 $L,R$，具体的，就是一个循环节循环两次组成的数在区间 $[l,r]$ 中。找到这个 $[L,R]$ 区间之后，再与之前 set 中值在这个区间里的数容斥一下就可以得出答案了。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
inline ll read()
{
	ll x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
ll l,r;
int lg[N],ans;
inline void init(){for(int i=2;i<N;i++) lg[i]=lg[i>>1]+1;}
set<ll>S;
inline bool check(int l,ll x,int r)
{
	int y=(__lg(x)+1)/2;
	if((x&((1<<y)-1))==(x>>y)&&l<=(x>>y)&&(x>>y)<=r)return 1;
	return 0;
}
inline void solve()
{
	l=read(),r=read();
	for(int i=1;i<=r;i++)
	{
		ll t=i;int x=lg[i]+1;
		if((((t<<x)+i)<<x)+i>1e18)break;
		while(log10(1ll<<x)+log10(t)<=18)
		{
			t<<=x,t+=i;
			if(t>r)break;
			if(l<=t&&t<=r&&S.find(t)==S.end()) S.insert(t),ans++;
		}
	}
	if(r<(909494ll<<20)+909494)return printf("%lld\n",ans),void();
	// (931322574<<30)+931322574>1e18
	// (931322573<<30)+931322573<1e18
	int L=0,R=0,ll=909494,rr=931322573;
	while(ll<=rr)
	{
		int mid=(ll+rr)>>1;
		if((1ll*mid<<(__lg(mid)+1))+mid<l) ll=mid+1;
		else L=mid,rr=mid-1;
	}
	ll=909494,rr=931322573;
	while(ll<=rr)
	{
		int mid=(ll+rr)>>1;
		if((1ll*mid<<(__lg(mid)+1))+mid>r) rr=mid-1;
		else R=mid,ll=mid+1;
	}
	auto it=S.lower_bound((1ll*L<<(__lg(L)+1))+L);
	while(it!=S.end()&&*it<=(1ll*R<<(__lg(R)+1))+R){if(check(L,*it,R))ans--;++it;}
	printf("%lld\n",ans+R-L+1);
	return ;
}
signed main(){init();int T=1;while(T--) solve();return 0;}
```

~~[卡常之后还是最劣解](https://codeforces.com/contest/215/submission/282843650)~~

---

## 作者：Eric998 (赞：0)

观察到将 $x$ 重复一定次数的结果是单调的。

枚举重复次数，二分最大合法值即可。

注意可能会被算重，用莫反稍微容斥一下。我写了，用脚维护，不需要任何脑子！

---

