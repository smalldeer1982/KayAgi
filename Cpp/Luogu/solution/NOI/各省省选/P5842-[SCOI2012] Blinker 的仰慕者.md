# [SCOI2012] Blinker 的仰慕者

## 题目描述

Blinker 有非常多的仰慕者，他给每个仰慕者一个正整数编号。而且这些编号还隐藏着特殊的意义，即编号的各位数字之积表示这名仰慕者对 Blinker 的重要度。 现在 Blinker 想知道编号介于某两个值 $A$,$B$ 之间，且重要度为某个定值 $K$ 的仰慕者编号和。

## 说明/提示

- 对于 $20\%$ 的数据，保证： $2 \le A  \le B \le 10^9$，$1 \le N \le 30$；
- 对于 $50\%$ 的数据，保证：$ 2 \le A \le B \le 10^{18}$，$1\le N \le 30$；
- 对于 $100\%$ 的数据，保证：  $ 2 \le A \le B \le 10^{18}$，$1 \le N \le 5000$。

## 样例 #1

### 输入

```
3
1 14 4
1 30 4
10 60 5
```

### 输出

```
18
40
66
```

# 题解

## 作者：slgdsxw (赞：15)

Update on 2020.5.31：极大简化了代码，跑的飞快

小蒟蒻的第一篇题解，望大家支持，如有排版格式问题还请见谅。

此题比较复杂，做的话需要先熟悉数位dp的基本套路，我们慢慢分析。

看到 “各位数字之积” 应该可以想到这是数位dp题，那么最朴素的想法就是 $f(i,j)$ 表示前 $i$ 位数各位数字之积为 $j$ 时的答案，$j$ 最大$10^{18}$，无法通过。

考虑到 K 为 1-9 这些数字的乘积（我们先忽略0），K的质因子就只有 2,3,5,7 四个，因此我们可以用四个下标 a , b , c , d 来表示 $j$ ，即 $j=2^a * 3^b * 5^c * 7^d$ ,但是把四个参数都写到dp数组里的话状态数还是有点大，达到了 1e8 的级别。

为了减少复杂度我们先预处理出 $10^{18}$ 所有以内所有可能的 $j$ （$j=2^a * 3^b * 5^c * 7^d$） ,它可以很暴力（~~反正数很少~~），如下：
```cpp
	int lim2=59,lim3=37,lim5=25,lim7=21;
	ll fac2[60],fac3[60],fac5[60],fac7[60];
	fac2[0]=fac3[0]=fac5[0]=fac7[0]=1;
	fac[0]=1;
	for(int i=1;i<=lim2;i++)fac2[i]=fac2[i-1]*2;
	for(int i=1;i<=lim3;i++)fac3[i]=fac3[i-1]*3;
	for(int i=1;i<=lim5;i++)fac5[i]=fac5[i-1]*5;
	for(int i=1;i<=lim7;i++)fac7[i]=fac7[i-1]*7;
	for(int i=1;i<=18;i++)fac[i]=fac[i-1]*10;
	maxk=fac[18];
	for(int i=1;i<=18;i++)fac[i]%=mod;
	for(int i=0;i<=lim2;i++)
		for(int j=0;j<=lim3&&fac2[i]*fac3[j]<=maxk;j++)
			for(int k=0;k<=lim5&&fac2[i]*fac3[j]*fac5[k]<=maxk;k++)
				for(int l=0;l<=lim7&&fac2[i]*fac3[j]*fac5[k]*fac7[l]<=maxk;l++)
					num[++kcnt]=fac2[i]*fac3[j]*fac5[k]*fac7[l];
	sort(num+1,num+kcnt+1);
```
为了转移方便，某个 $j$ 与1-9中的某数运算的结果在数表num中的位置我们也需要知道，预处理出来，$p_{0-3}$ 对应着2,3,5,7。
```cpp
	for(int i=1;i<=kcnt;i++)to[i][1]=i;
	for(int i=0;i<=3;i++)
		for(int j=1;j<=kcnt;j++)
			if(num[j]%p[i]==0)to[j][p[i]]=id(num[j]/p[i]);
	for(int i=4;i<=9;i++)
	{
		if(i==p[0]||i==p[1]||i==p[2]||i==p[3])continue;
		for(int j=1;j<=kcnt;j++)to[j][i]=getto(j,i);
	}
```
其中 $to(i,j)$ 表示数表中第 $i$ 个数除以 $j$ 的结果在数表中的位置（注意是除不是乘，原因下面讲）id函数使用的stl的二分查找，getto是质因数分解求to的过程，如$to(i,4)=to(to(i,2),2)$ 。
代码如下：
```cpp
int id(ll x)
{
	return lower_bound(num+1,num+kcnt+1,x)-num;
}
int getto(int x,int k)
{
	for(int i=0;i<=3;i++)
		while(k%p[i]==0)
		{
			k/=p[i];
			x=to[x][p[i]];
		}
	return x;
}
```
然后我们的dp状态就可以设计为 $f(i,j)$ 表示前 $i$ 位当前乘积为 $j$ 的答案数，因为如果没有数的大小限制，且没有前导零的影响，$f(i,j)$的值就只与最终数位的乘积K有关系。我们把$f(i,j)$的含义改一下，表示到了第 $i$ 位，还需要的数位乘积为 $j$ 的答案，那么 $f(i,j)$的值与K也没有了关系（把K当初始值来看）。我们求答案用到 $f$ 的时候已经有小于上界和无前导零的条件，这两维不用考虑。

我们再关注一下这个题要求什么：满足题意数的和。如果求个数的话就很简单了，和怎么求呢？我们还要加入一个数组g，$f,g$的最终含义：$f(i,j)$表示到了第 $i$ 位，还需要的数位乘积为 $j$ 时的方案数： $g(i,j)$表示到了第 $i$ 位，还需要的数位乘积为 $j$ 时可以填的数的和（中间两维我略了）。这个 $g$ 指的数是从第 $i$ 位开始计的，比如$i=3$，后三位可以填123,213,321这三个数,，那么$f$的值为3，$g$ 的值即为$123+213+321$

$f(i,j),g(i,j)$如何转移呢？$f$ 的值可以直接从下一位累加，假设第 $i$ 位我们填了a，后面还有3位，$g$ 计算的和即为形如aXXX这样的数的和，这个XXX每有一种方案, $g$ 就加上$1000a$
而后面这些可能的XXX的总和恰是下一位的 $g$ 要所表示的，XXX的方案数则由下一位的 $f$ 表示，那么这个预先dp就可以写出了（边界值按$f,g$的定义很好考虑, $fac(i)$为$10^i$：
```
void dp(int k,int rest)
{
	if(!k)
	{
		f[k][rest]=(rest==1);
		g[k][rest]=0;
		return;
	}
	if(f[k][rest]!=-1)return;
	ll rf=0,rg=0;
	int a1,a2;
	for(int i=9;i>=1;i--)
	{
		a1=k-1;
		a2=(i==0)?rest:to[rest][i];
		if(!a2)continue;
		dp(a1,a2);
		rf+=f[a1][a2];
		rg=(rg+i*f[a1][a2]*fac[k-1]+g[a1][a2])%mod;
	}
	f[k][rest]=rf%mod;
	g[k][rest]=rg;
	return;
}
```

剩余的数位乘积是减少的，$to$在这里就用上了（这就是为什么$to$处理的是除）。

需要 $f,g$ 的值时调用这个dp：
```
if(f[k][rest]==-1)dp(k,rest);
```

那么对于输入的A,B,K，先转化成前缀相减：
```cpp
cout<<((solve(r)-solve(l-1))%mod+mod)%mod<<endl;
```
在上界的限制下dfs每一位填什么，并传递当前前缀值，如果满足已经小于上界、没有前导零影响了，直接返回答案，计算方法与 $g$ 的推导类似，可以把当前的前缀值pre看做我们刚才讨论 $g$ 时的a。dfs代码如下：
```
ll dfs(int k,int low,int zero,int rest,ll pre)
{
	if(!rest)return 0;
	if(low&(!zero))
	{
		if(f[k][rest]==-1)dp(k,rest);
		return (pre*fac[k]%mod*f[k][rest]+g[k][rest])%mod;
	}
	if(!k)return pre*(rest==1);
	ll res=0;
	for(int i=low?9:a[k];i>=(!zero);i--)
		res+=dfs(k-1,low|(i<a[k]),zero&(i==0),(i==0)?rest:to[rest][i],(pre*10+i)%mod);
	return res;
}
```

这个题做完了？似乎我们还忽略了零。。。

如果$K=0$ ,问题可以看做求在A到B中所有至少有一位为零的数的和，（~~和上面那些比这还不简单~~）与$f,g$的定义类似，$f0(i,j,k,l)$表示到了第 $i$ 位 是（1）否（0）小于上界值，是（1）否（0）有前导零， 前面已经有 $l$ 个零时的填的方案数，$g0$ 表示填的数的和，注意前导零。
```cpp
void dp0(int k,int low,int zero,int cnt0)
{
	if(!k)
	{
		f0[k][low][zero][cnt0]=(cnt0>0);
		g0[k][low][zero][cnt0]=0;
		return;
	}
	if(f0[k][low][zero][cnt0]!=-1)return;
	ll rf=0,rg=0;
	int b1,b2,b3,b4;
	for(int i=low?9:a[k];i>=0;i--)
	{
		b1=k-1;
		b2=low|(i<a[k]);
		b3=zero&(i==0);
		b4=cnt0+((!zero)&(i==0));
		dp0(b1,b2,b3,b4);
		rf=(rf+f0[b1][b2][b3][b4])%mod;
		rg=(rg+i*f0[b1][b2][b3][b4]*fac[k-1]%mod+g0[b1][b2][b3][b4])%mod;
	}
	f0[k][low][zero][cnt0]=rf;
	g0[k][low][zero][cnt0]=rg;
	return;
}
```
还有一些细节如判断K是否可以被2,3,5,7质因数分解等不一一赘述了，看完整代码吧，少用些取模运算速度提升很大。

感觉自己写的复杂度很高，常数很大，有可优化之处还望各位dalao赐教qwq。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define ll long long
using namespace std;
const int mod=20120427;
int kcnt;
int to[70000][10],a[20],p[4]={2,3,5,7};
ll l,r,K,maxk;
ll fac[20],num[70000],f[20][70000],g[20][70000];
ll f0[20][2][2][20],g0[20][2][2][20];
int id(ll x)
{
	return lower_bound(num+1,num+kcnt+1,x)-num;
}
int getto(int x,int k)
{
	for(int i=0;i<=3;i++)
		while(k%p[i]==0)
		{
			k/=p[i];
			x=to[x][p[i]];
		}
	return x;
}
void dp(int k,int rest)
{
	if(!k)
	{
		f[k][rest]=(rest==1);
		g[k][rest]=0;
		return;
	}
	if(f[k][rest]!=-1)return;
	ll rf=0,rg=0;
	int a1,a2;
	for(int i=9;i>=1;i--)
	{
		a1=k-1;
		a2=(i==0)?rest:to[rest][i];
		if(!a2)continue;
		dp(a1,a2);
		rf+=f[a1][a2];
		rg=(rg+i*f[a1][a2]*fac[k-1]+g[a1][a2])%mod;
	}
	f[k][rest]=rf%mod;
	g[k][rest]=rg;
	return;
}
void init()
{ 
	int lim2=59,lim3=37,lim5=25,lim7=21;
	ll fac2[60],fac3[60],fac5[60],fac7[60];
	fac2[0]=fac3[0]=fac5[0]=fac7[0]=1;
	fac[0]=1;
	for(int i=1;i<=lim2;i++)fac2[i]=fac2[i-1]*2;
	for(int i=1;i<=lim3;i++)fac3[i]=fac3[i-1]*3;
	for(int i=1;i<=lim5;i++)fac5[i]=fac5[i-1]*5;
	for(int i=1;i<=lim7;i++)fac7[i]=fac7[i-1]*7;
	for(int i=1;i<=18;i++)fac[i]=fac[i-1]*10;
	maxk=fac[18];
	for(int i=1;i<=18;i++)fac[i]%=mod;
	for(int i=0;i<=lim2;i++)
		for(int j=0;j<=lim3&&fac2[i]*fac3[j]<=maxk;j++)
			for(int k=0;k<=lim5&&fac2[i]*fac3[j]*fac5[k]<=maxk;k++)
				for(int l=0;l<=lim7&&fac2[i]*fac3[j]*fac5[k]*fac7[l]<=maxk;l++)
					num[++kcnt]=fac2[i]*fac3[j]*fac5[k]*fac7[l];
	//cout<<kcnt<<endl;
	sort(num+1,num+kcnt+1);
	for(int i=1;i<=kcnt;i++)to[i][1]=i;
	for(int i=0;i<=3;i++)
		for(int j=1;j<=kcnt;j++)
			if(num[j]%p[i]==0)to[j][p[i]]=id(num[j]/p[i]);
	for(int i=4;i<=9;i++)
	{
		if(i==p[0]||i==p[1]||i==p[2]||i==p[3])continue;
		for(int j=1;j<=kcnt;j++)to[j][i]=getto(j,i);
	}
	memset(f,-1,sizeof(f));
	return;
}
ll check(ll x)
{
	for(int i=0;i<=3;i++)
		while(x%p[i]==0)x/=p[i];
	return x;
}
ll dfs(int k,int low,int zero,int rest,ll pre)
{
	if(!rest)return 0;
	if(low&(!zero))
	{
		if(f[k][rest]==-1)dp(k,rest);
		return (pre*fac[k]%mod*f[k][rest]+g[k][rest])%mod;
	}
	if(!k)return pre*(rest==1);
	ll res=0;
	for(int i=low?9:a[k];i>=(!zero);i--)
		res+=dfs(k-1,low|(i<a[k]),zero&(i==0),(i==0)?rest:to[rest][i],(pre*10+i)%mod);
	return res;
}
void dp0(int k,int low,int zero,int cnt0)
{
	if(!k)
	{
		f0[k][low][zero][cnt0]=(cnt0>0);
		g0[k][low][zero][cnt0]=0;
		return;
	}
	if(f0[k][low][zero][cnt0]!=-1)return;
	ll rf=0,rg=0;
	int b1,b2,b3,b4;
	for(int i=low?9:a[k];i>=0;i--)
	{
		b1=k-1;
		b2=low|(i<a[k]);
		b3=zero&(i==0);
		b4=cnt0+((!zero)&(i==0));
		dp0(b1,b2,b3,b4);
		rf=(rf+f0[b1][b2][b3][b4])%mod;
		rg=(rg+i*f0[b1][b2][b3][b4]*fac[k-1]+g0[b1][b2][b3][b4])%mod;
	}
	f0[k][low][zero][cnt0]=rf;
	g0[k][low][zero][cnt0]=rg;
	return;
}
ll solve(ll x)
{
	int len=0;
	while(x)
	{
		a[++len]=x%10;
		x/=10;
	}
	return dfs(len,0,1,id(K),0);
}
ll solve0(ll x)
{
	int len=0;
	while(x)
	{
		a[++len]=x%10;
		x/=10;
	}
	memset(f0,-1,sizeof(f0));
	dp0(len,0,1,0);
	return g0[len][0][1][0];
}
int main()
{
	int T;
	init();
	cin>>T;
	while(T--)
	{
		cin>>l>>r>>K;
		if(!K)
		{
			cout<<((solve0(r)-solve0(l-1))%mod+mod)%mod<<endl;
			continue;
		}
		ll x=check(K);
		if(x!=1)
		{
			cout<<0<<endl;
			continue;
		}
		cout<<((solve(r)-solve(l-1))%mod+mod)%mod<<endl;
	}
	return 0;
}
```









---

## 作者：I_AM_CIMOTA (赞：5)

很显然，这道题需要用数位dp，按照套路转化成求 $[1..X]$ 中重要度为 $K$ 的编号和。

在不考虑空间的情况下，我们定义 $f(i,j,0/1,0/1)$ 表示现在正在考虑从高到低的第 $i$ 位，当前位和更低位上的数码乘积需要等于 $j$（即更高位的乘积为 $\frac K j$），目前贴/没贴上界，目前在/不在前导零阶段，重要度为 $K$ 的编号和。答案就是 $f(1,K,1,1)$ 。

因为求的是编号和，所以还需要记一个 $g(i,j,0/1,0/1)$ 表示上述情况下的重要度为 $k$ 的人数。

如果这道题的 $K$ 很小，那么这道题就是数位dp模板了，但是这道题的 $K$ 显然是可以非常大的，所以按常规方法开数组肯定开不下。但是，不难发现有些状态是肯定不会出现的，即状态中的 $j$ 不是若干数码的乘积，于是考虑离散化。



分析一下某个人重要度 $K$ 的组成，发现一个合法的 $j$ 一定可以表示成这样（此处为了方便假设 $0^0=1$）：
$$
j=0^{a_0}\times1^{a_1}\times2^{a_2}\times...\times9^{a_9}
$$
其中 $a_i$ 表示 $i$ 这个数码在 $j$ 中出现了多少次。

通过这个发现，就可以暴力枚举指数 $a_i$ ，得到所有可能出现的乘积，这样就成功完成了离散化。可是这时又出现了一个问题：离散化后的数没法正常进行运算！

所以，我们的处理工作还未结束。定义 $to_{i,j}$ 表示 $i$ 这个离散化后的数的原值除以数码 $j(1\le j\le9)$ 得到的结果离散化后的值。因为 $i$ 能表示成若干个数码之积，所以 $to_{i,j}$ 也可以，这就保证了 $to_{i,j}$ 也在离散化后的那些数之中。

你可能会问：$j$ 不能等于 $0$ ，这样会少考虑一些情况啊！

不用担心，$0$ 的问题稍后解决。

现在我们先考虑 $K\not=0$ 的情况下 $f$ 的状态转移方程，这时肯定不能有任何数码为 $0$ ，所以设 $p$ 为当前位的上界， $x=p\land[k=up],y=q\land[k=0]$：
$$
g(i,j,p,q)=\sum_{k=1}^{up}g(i+1,to_{j,k},x,y)
$$

$$
f(i,j,p,q)=\sum_{k=1}^{up}g(i+1,to_{j,k},x,y)\times k\times10^{19-i}+f(i+1,to_{j,k},x,y)
$$

对于第二个式子中 $10$ 的幂次，因为我计算的是从高到低第 $i$ 位，所以应该用总位数减去 $i$ 作为指数。在这道题中我的总位数为 $19$ 。

这样，对于 $K\not=0$ 的情况就讨论完了，下面看应该如何处理 $0$ 。

如果一个数中有任意一个数码是 $0$ ，那么这个数所有位的乘积一定是 $0$ 。那么 $K=0$ 的情况就可以简化为求含有至少一个 $0$ 的数的编号和。

进一步可以用容斥简化为更好求的：不含 $0$ 的数的编号和。

这样就按照类似求 $f$ 和 $g$ 的套路再做一遍，便可求出这种情况的答案。

实现起来很简单，记忆化深搜即可。

代码如下，求个赞支持一下QWQ

```cpp
#include <bits/stdc++.h>
#define int long long
#define g(x,y,z) (z?x:to[x][y])
using namespace std;

const int N=5e6+3,upK=1e18,Mod=20120427;
struct node{
	int num,sum;
}f[25][60005],dp[25];
int T,A,B,K,tp=1,tot,nw,a[25],lsh[N],pow10[25],to[60005][10];
bool vis[25][60005],viss[25];
unordered_map<int,int>mp;

void pre(int i,int prod,int j){
	if(j<0)return;
	if(i>9){lsh[++tp]=prod;return;}
	int cnt=prod;
	for(int k=0;k<=j&&cnt<=upK;k++,cnt*=i)pre(i+1,cnt,j-k);
}

node F(int i,int j,bool up,bool pre0){
	if(j==0)return {0,0};
	if(i>19)return (node){j==2,0};
	if(!up&&!pre0&&vis[i][j])return f[i][j];
	int r=up?a[i]:9;
	node res={0,0};
	for(int k=0;k<=r;k++){
		node add=F(i+1,g(j,k,pre0&(k==0)),up&(k==r),pre0&(k==0));
		(res.num+=add.num)%=Mod;
		(res.sum+=(add.num*pow10[19-i]%Mod*k%Mod+add.sum)%Mod)%=Mod;
	}
	if(!up&&!pre0)vis[i][j]=1,f[i][j]=res;
	return res;
}

node DP(int i,bool up,bool pre0){
	if(i>19)return {1,0};
	if(!up&&!pre0&&viss[i])return dp[i];
	int r=up?a[i]:9;
	node res={0,0};
	for(int k=0;k<=r;k++){
		if(k==0&&!pre0)continue;
		node add=DP(i+1,up&(k==r),pre0&(k==0));
		(res.num+=add.num)%=Mod;
		(res.sum+=(add.num*pow10[19-i]%Mod*k%Mod+add.sum)%Mod)%=Mod;
	}
	if(!up&&!pre0)viss[i]=1,dp[i]=res;
	return res;
}

int solve(int x){
	if(x==0)return 0;
	for(int i=19;i>=1;i--)a[i]=x%10,x/=10;
	return F(1,K,1,1).sum;
}

int work(int x){
	int p=x%Mod*((x+1)%Mod)%Mod*10060214ll%Mod;
	if(x==0)return 0;
	for(int i=19;i>=1;i--)a[i]=x%10,x/=10;
	return p-DP(1,1,1).sum;
}

signed main(){
	scanf("%lld",&T);
	pow10[0]=1;
	for(int i=1;i<=19;i++)pow10[i]=pow10[i-1]*10%Mod;
	pre(2,1,18);
	sort(lsh+1,lsh+tp+1);
	tot=unique(lsh+1,lsh+tp+1)-lsh-1;
	for(int i=1;i<=tot;i++)mp[lsh[i]]=i;
	for(int i=1;i<=tot;i++){
		for(int j=1;j<=9;j++){
			if(lsh[i]%j!=0)continue;
			to[i][j]=mp[lsh[i]/j];
		}
	}
	while(T--){
		scanf("%lld%lld%lld",&A,&B,&K);
		K=mp[K];
		if(K!=1)printf("%lld\n",((solve(B)-solve(A-1))%Mod+Mod)%Mod);
		else printf("%lld\n",((work(B)-work(A-1))%Mod+Mod)%Mod);
	}
	return 0;
} 
```

---

## 作者：Infiltrator (赞：5)

[$\Large\color{#FFBBFF}\textit{Tian-Xing's blog}$](https://Tian-Xing.github.io)

------------

# Description

[传送门](https://www.luogu.com.cn/problem/P5842)

------------

# Solution

不难想到这题用数位$dp$解决。

那么首先可以想到$dp_{i, j, num2, num3, num5, num7}$表示从高到低填了$i$位，是否卡位，乘积中的每个质因子数量是多少此时的方案数，$sum_{i, j, num2, num3, num5, num7}$表示这些数的和。

这样子的转移是很好想的不再赘述，但是这样定义状态空间会爆炸，大概需要$\log_2 {2 ^ {64}} \times \log_3 {2 ^ {64}} \times \log_5 {2 ^ {64}} \times \log_7 {2 ^ {64}} \times 2 \times 19 \times 2= 125296640$的空间。

这时注意到实际上没必要用这么多状态，所有可行的状态只有大概$66061$个，那么我们可以把所有的可行状态都扔到一个哈希表里，就解决了空间的问题。

接下来就可以按照套路先预处理出$f_{i, j}$表示从低到高$i$位，乘积在哈希表里的位置是$j$的方案数，$sum_{i, j}$表示此时的和。

剩下的就是如何卡位以及算贡献。

从高位到低位枚举一下$lcp$然后枚举这位填的数字$j$。先判断填$j$是否可行，也就是说看看$lcp$和$j$的积是否整除$k$。只要这一位不是填的最高位那么后面可以随便填，所以这一位如果可行就在最终的答案里加上$(lcp \times 10 + j) * 10^{i - 1} * f_{i - 1, k / lcp / j} + g_{i - 1, k / lcp / j}$。

最后别忘了加上$\sum_{i = 1}^{n - 1}g_{i, k}$。

对于卡位，每一位都卡到最高数字要求只算一遍贡献。我们每次枚举每一位填什么的时候填小于当前位的数字，这时我们发现所有位都卡位的情况没有算上，那么可以将要算的数先加一，这样保证只在最后一位的时候算上了贡献。

注意$k$的取值可能是$0$，这是我们就要求至少有一位是$0$并且有数字出现过，这就是一个基础的数位$dp$，此处不再赘述。

------------

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MOD = 20120427, HashMOD = 1000037, zt = 66062;

#define ll long long

int head[HashMOD + 50], num, f[19][zt], g[19][zt], cnt, zhi[20], pow[19], dp[20][2][2][2], sum[20][2][2][2];

struct Node
{
	int next;
	ll zhi;
} hash[HashMOD + 50];

template <class T>
void Read(T &x)
{
	x = 0; int p = 0; char st = getchar();
	while (st < '0' || st > '9') p = (st == '-'), st = getchar();
	while (st >= '0' && st <= '9') x = (x << 1) + (x << 3) + st - '0', st = getchar();
	x = p ? -x : x;
	return;
}

template <class T>
void Put(T x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) Put(x / 10);
	putchar(x % 10 + '0');
	return; 
}

int Ins(ll x)
{
	int bh = x % HashMOD;
	for (int i = head[bh]; i; i = hash[i].next)
		if (hash[i].zhi == x) return i;
	hash[++num] = (Node){head[bh], x};
	head[bh] = num;
	return num;
} 

int Ask(ll x)
{
	int bh = x % HashMOD;
	for (int i = head[bh]; i; i = hash[i].next)
		if (hash[i].zhi == x) return i;
	return 0;
}

void Prework()
{
	pow[0] = 1;
	for (int i = 1; i <= 18; i++) pow[i] = (pow[i -1] * 10) % MOD;
	int tmp;
	f[0][Ins(1)] = 1;
	for (int i = 0; i < 18; i++)
		for (int j = 1; j <= num; j++)
			for (int k = 1; k <= 9; k++)
			{
				if (hash[j].zhi * k > 1000000000000000000LL) break;
				(f[i + 1][tmp = Ins(hash[j].zhi * k)] += f[i][j]) %= MOD,
				(g[i + 1][tmp] += g[i][j] * 10 % MOD + f[i][j] * k) %= MOD;
			}
	return;
} 

int Work(ll x, ll k)
{
	cnt = 0;
	while (x)
	{
		zhi[++cnt] = x % 10;
		x /= 10;
	}
	ll ans = 0, pre = 0, mul = 1;
	for (int i = cnt; i; i--)
	{
		if (!zhi[i]) break;
		for (int j = 1; j < zhi[i]; j++)
			if ((k % (mul * j)) == 0)
			{
				ll tmp = k / mul / j;
				int t = Ask(tmp);
				(ans += (pre * 10 + j) * pow[i - 1] % MOD * f[i - 1][t] % MOD + g[i - 1][t]) %= MOD; 
			}
		pre = pre * 10 + zhi[i];
		mul = mul * zhi[i];
	}
	int tmp = Ask(k);
	for (int i = 1; i < cnt; i++) (ans += g[i][tmp]) %= MOD;
	return ans;
} 

int Work0(ll x)
{
	cnt = 0;
	memset(dp, 0, sizeof(dp));
	memset(sum, 0, sizeof(sum));
	while (x)
	{
		zhi[++cnt] = x % 10;
		x /= 10;
	}
	dp[cnt + 1][1][0][0] = 1;
	for (int i = cnt + 1; i >= 2; i--)
	{
		if (i != cnt + 1) dp[i][0][0][0] = 1;
		for (int j = 0; j <= 1; j++)
			for (int t = 0; t <= 1; t++)
				for (int q = 0; q <= 1; q++)
					if (dp[i][j][t][q])
						for (int k = 0; k <= 9; k++)
						{
							if (j && k > zhi[i - 1]) break;
							if (!t && !q && !k) continue; 
							(dp[i - 1][j && (k == zhi[i - 1])][t || (!k)][q || k] += dp[i][j][t][q]) %= MOD; 
							(sum[i - 1][j && (k == zhi[i - 1])][t || (!k)][q || k] += sum[i][j][t][q] * 10 + dp[i][j][t][q] * k) %= MOD;
 						}
	}
 	return (sum[1][1][1][1] + sum[1][0][1][1]) % MOD;
}

int main()
{
	Prework();
	int t;
	ll l, r, k;
	Read(t);
	while (t--)
	{
		Read(l); Read(r); Read(k);
		if (k) Put((Work(r + 1, k) - Work(l, k) + MOD) % MOD), putchar('\n');
		else Put((Work0(r) - Work0(l - 1) + MOD) % MOD), putchar('\n');
	}
	return 0;
}
```

---

## 作者：Flash_Man (赞：2)

（感谢洛谷第一篇题解）

暴力 dp 是 $f(i,j)$ 表示 $n$ 到 $i$ 位（设最高位为第 $n$ 位）剩下的数乘积需要为 $j$ 的方案数，$g(i,j)$ 表示 $n$ 到 $i$ 位剩下的数乘积需要为 $j$ 的所有数和。但是每一位的数都不会大于 $9$，所以乘积的质因数一定只有 $2,3,5,7$，所以可以把所有合法状态都预处理出来，然后状态里就只用开合法状态个数的大小（$6\text e 4$ 个左右）。正常记忆化深搜即可。转移如下（转移方程是暴力 dp 的转移，自己把它转化成 map 离散化的即可）：
$$
\begin{aligned}
&f(i,j)=\sum_{x\in[1..9]}f\left(i-1,\frac{j}{x}\right)\\
&g(i,j)=\sum_{x\in[1..9]}f\left(i-1,\frac{j}{x}\right)\times x\times 10^{i-1}+g\left(i-1,\frac{j}{x}\right)
\end{aligned}
$$
有几个需要注意的点：

1. 记忆化深搜里，除了要记 `lim` 表示是否卡到上界，还要记 `st` 表示现在还是不是前导零阶段；如果是，$x$ 就可以继续取 $0$，反之则不行（如果数中间取 $0$，乘积就变成 $0$ 了）；
2. 因为本题有点卡时间，所以要预处理一些东西和剪枝：预处理 `to[i][x]` 表示 map 的第 $i$ 项如果除以 $x$（$x\in[0..9]$）会变成 map 的哪一项，和 `stp[i]` 表示 map 的第 $i$ 项最少需要多少步才能除到 $1$（这个东西可以枚举这一步除以什么，然后 dp 转移）；在深搜的时候，如果发现剩下能走的次数小于 `stp[s]`，就直接剪枝；
3. 本题中有 $k=0$ 的情况很恶心，需要单独再写一个数位 DP。$f(i,j)$ 表示前 $i$ 位有 $j$ 个 $0$ 的方案数，$g(i,j)$ 表示前 $i$ 位有 $j$ 个 $0$ 的所有数的和，转移跟本来的 DP 类似。

```cpp
#include <cstdio>
#include <map>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lld;
const lld mod = 20120427;
const lld ths = 1e18;
const int maxl = 18 + 1;
const int maxs = 1e5 + 1;
const int maxc = 1e7 + 1;
struct Result { lld f, g; };
struct Node {
	int p1, p2, p3, p4;
	bool operator <(const Node &x) const {
		return p1 != x.p1 ? p1 < x.p1 : (p2 != x.p2 ? p2 < x.p2 : (p3 != x.p3 ? p3 < x.p3 : p4 < x.p4));
	}
};
int t, k1, k2, k3, k4;
lld l, r, k, pw[maxl];
Node mp[maxs];
int cnt = 0, n, a[maxl], to[maxs][10], stp[maxs], pstk = 0;
Result dp[maxl][maxs], dp0[maxl][maxl], stk[maxc];
int find(int p1, int p2, int p3, int p4) {
	return std::lower_bound(mp + 1, mp + cnt + 1, Node{ p1, p2, p3, p4 }) - mp;
}
Result dfs(int id, bool lim, bool st, int s, lld sum) {
	if (!id) return { !st && sum == 1, 0 };
	if (!lim && !st && ~dp[id][s].f) return dp[id][s];
	if (stp[s] > id) return { 0, 0 };
	int mxv = lim ? a[id] : 9;
	Result res = { 0, 0 }, tmp;
	for (int x = !st; x <= mxv; x++) {
		if (!x) res = dfs(id - 1, false, true, s, sum);
		else if (!(sum % x)) {
			tmp = dfs(id - 1, lim && x == mxv, false, to[s][x], sum / x);
			res.f = res.f + tmp.f;
			res.g = res.g + tmp.f * pw[id - 1] * x + tmp.g;
		}
	}
	res.f %= mod, res.g %= mod;
	if (!lim && !st) { dp[id][s] = res; stk[++pstk] = { id, s }; }
	return res;
}
Result dfs0(int id, bool lim, bool st, int cnt) {
	if (!id) return { !st && cnt, 0 };
	if (!lim && !st && ~dp0[id][cnt].f) return dp0[id][cnt];
	int mxv = lim ? a[id] : 9;
	Result res = { 0, 0 }, tmp;
	for (int x = 0; x <= mxv; x++) {
		tmp = dfs0(id - 1, lim && x == mxv, st && !x, cnt + (!st && !x));
		res.f = res.f + tmp.f;
		res.g = res.g + tmp.f * pw[id - 1] * x + tmp.g;
	}
	res.f %= mod, res.g %= mod;
	if (!lim && !st) dp0[id][cnt] = res;
	return res;
}
lld solve(lld x) {
	n = 0;
	while (x) a[++n] = x % 10ll, x /= 10ll;
	if (k) return dfs(n, true, true, find(k1, k2, k3, k4), k).g;
	else return dfs0(n, true, true, 0).g;
}
signed main() {
	int p1, p2, p3, p4; lld s1, s2, s3, s4;
	for (p1 = 0, s1 = 1; s1 <= ths; p1++, s1 <<= 1ll)
		for (p2 = 0, s2 = s1; s2 <= ths; p2++, s2 *= 3ll)
			for (p3 = 0, s3 = s2; s3 <= ths; p3++, s3 *= 5ll)
				for (p4 = 0, s4 = s3; s4 <= ths; p4++, s4 *= 7ll)
					mp[++cnt] = { p1, p2, p3, p4 }, to[cnt][1] = cnt;
	std::sort(mp + 1, mp + cnt + 1);
	for (int i = 1; i <= cnt; i++) {
		if (mp[i].p1) to[i][2] = find(mp[i].p1 - 1, mp[i].p2, mp[i].p3, mp[i].p4);
		if (mp[i].p2) to[i][3] = find(mp[i].p1, mp[i].p2 - 1, mp[i].p3, mp[i].p4);
		to[i][4] = to[to[i][2]][2];
		if (mp[i].p3) to[i][5] = find(mp[i].p1, mp[i].p2, mp[i].p3 - 1, mp[i].p4);
		to[i][6] = to[to[i][2]][3];
		if (mp[i].p4) to[i][7] = find(mp[i].p1, mp[i].p2, mp[i].p3, mp[i].p4 - 1);
		to[i][8] = to[to[i][2]][4];
		to[i][9] = to[to[i][3]][3];
		stp[i] = maxs;
		for (int x = 2; x < 10; x++)
			if (to[i][x]) stp[i] = std::min(stp[i], stp[to[i][x]] + 1);
		if (stp[i] == maxs) stp[i] = 0;
	}
	pw[0] = 1;
	for (int i = 1; i < maxl; i++) pw[i] = pw[i - 1] * 10 % mod;
	for (int i = 1; i < maxl; i++)
		for (int j = 0; j < maxl; j++) dp0[i][j].f = -1;
	for (int i = 1; i < maxl; i++)
		for (int j = 1; j <= cnt; j++) dp[i][j].f = -1;
	scanf("%d", &t);
	while (t--) {
		scanf("%lld%lld%lld", &l, &r, &k);
		lld tmp = k;
		if (k) {
			k1 = k2 = k3 = k4 = 0;
			while (!(tmp & 1)) k1++, tmp >>= 1;
			while (!(tmp % 3)) k2++, tmp /= 3;
			while (!(tmp % 5)) k3++, tmp /= 5;
			while (!(tmp % 7)) k4++, tmp /= 7;
		}
		if (tmp > 1) puts("0");
		else printf("%lld\n", (solve(r) - solve(l - 1) + mod) % mod);
		Result tp;
		while (pstk) {
			tp = stk[pstk--];
			dp[tp.f][tp.g].f = -1;
		}
	}
	return 0;
}
```

---

## 作者：Nightingale_OI (赞：1)

## P5842 [SCOI2012] Blinker 的仰慕者

### 大意

求 $L\leq x \leq R$ 且 $x$ 各位数字之积为 $K$ 的合法 $x$ 之和。

每个测试点至多询问 $5000$ 次。

### 思路

估计答案非 $0$ 的 $K$ 数量非常少，毕竟因子只能有 $2,3,5,7$。枚举一下发现只有 $44101$ 个。

记 $f_{i,j}$ 表示任意填 $i$ 个数位，它们的积是 $j$ 的方案数，$g_{i,j}$ 表示这些方案对应的 $x$ 之和。

转移枚举下一位填什么即可，用哈希表存储可以非常快速地预处理完。

---

经典数位 DP，肯定要先差分，问题变为 $1\leq x\leq R$ 求合法 $x$ 之和。

那么肯定是前面几位卡上界，某一位对应位置小一些，后面随意。

由于 $K$ 可能为 $0$，不妨设 $K=-1$ 表示这些数字的积是什么都行，$K=-2$ 表示这些数的积是什么都不行。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(int i=j;i<=k;++i)
#define g(i,j,k) for(int i=j;i>=k;--i)
int n,m,s,l;
const int mo=20120427,m2=10060214;
unordered_map<int,int>f[30],g[30];
int a[30],b[30];
inline void Add(int&x,int y){x=(x+y)%mo;}
inline void ycl(){
	f[0][1]=1;
	f(i,1,19){
		for(auto e:f[i-1])f(c,0,9){
			s=e.first;l=s*c;m=e.second;
			Add(f[i][l],m);
			Add(g[i][l],g[i-1][s]*10+m*c);
		}
	}
	int x=f[0][-1]=1;
	f(i,1,19){
		b[i]=x;x=x*10%mo;
		f[i][-1]=x;
		g[i][-1]=x*(x-1)%mo*m2%mo;
	}
}
inline int nxt(int m,int c){
	if(m<0)return m;
	if(c==0)return m?-2:-1;
	return m%c?-2:m/c; 
}
inline int h(int up,int i,int m){return (up%mo*f[i][m]+g[i][m])%mo;}
inline int ask(int x,int m){
	f(i,1,20)a[i]=x%10,x/=10;
	for(n=20;n&&!a[n];--n);
	int re=0,up=0;
	g(i,n,1){
		f(c,0,a[i]-1){
			if(i==n&&!c){
				f(j,1,n-1)f(c,1,9)Add(re,h(c*b[j],j-1,nxt(m,c))); 
				continue;
			}
			Add(re,h(up+c*b[i],i-1,nxt(m,c)));
		}
		m=nxt(m,a[i]);up=(up+a[i]*b[i])%mo;
	}
	return re;
}
inline void doing(){
	cin>>s>>l>>m;
	printf("%lld\n",(ask(l+1,m)+mo-ask(s,m))%mo);
}
signed main(){
	ycl();
	int t;
	cin>>t;
	while(t--)doing();
	return 0;
}
```

---

## 作者：Gmt丶FFF (赞：1)

#### 题意简述：

求 $[l,r]$ 内各个数位积为 $k$ 的数的和。

---

#### 解：

在看题解前，请先确认自己是否精通了数位 dp 模板题，否则会很难理解。

对于朴素的数位 dp，我们可以记录 $f_{i,j}$ 代表枚举到第 $x$ 位，还需要的乘积为 $j$ 的数之和。

只有一个状态处理数的个数，但本题要求数的和，这样我们比较难用一位去处理。

所以再定义 $g_{i,j}$ 为枚举到第 $x$ 位，还需要的乘积为 $j$ 的数个数。

那么合并上来即是：

$g_{i,j}=\sum g_{i-1,j/k}$

$f_{i,j}=\sum f_{i-1,j/k}+k\times g_{i-1,j/k}\times 10^{i-1}$

那么直接枚举向下搜索即可，如果搜到底部 $j=1$，那么所有应该除的数已除完，直接返回和为 $0$，个数为 $1$，否则返回个数为 $0$。

特殊处理一下 $K=0$。

当 $K=0$ 时就记录状态为当前数是否有 $0$ 这一位，然后同样记录 $f,g$ 两个数组的值，往下搜即可。

用 map 存储记忆化来解决空间问题，期望得分 $20pts$。（不愧是黑，部分分都那么难拿）。

---

考虑朴素 dp 的缺陷。

1、调用 map 开销大量时间。

2、有许多冗余状态。

说白了就是数存多了，所以我们对此进行优化。

由于数位只有 $0$ 到 $9$，那么质数只有 $2,3,5,7$，所以对我们来说有用的数仅仅只有 $2^a\times3^b\times5^c\times7^d$。

那么我们可以把状态压成 $f_{i,a,b,c,d}$ 代表枚举到第 $i$ 位我们还剩下的因子为 $2^a\times3^b\times5^c\times7^d$ 的和，$g_{i,a,b,c,d}$ 同理。

转移比较容易，直接预处理出来每个数包含哪些质因子，在对应的质因子上减去即可。

期望得分：$50pts$，实际得分：$20pts$，被卡空间了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;
const int mod=20120427;
int n,cnt,a[20],f[20][55][37][20][20],g[20][55][37][20][20],t2,t3,t5,t7,power[20],k,f2[20][2][2][2],g2[20][2][2][2];
int s[10][4]={
{0,0,0,0},
{0,0,0,0},
{1,0,0,0},
{0,1,0,0},
{2,0,0,0},
{0,0,1,0},
{1,1,0,0},
{0,0,0,1},
{3,0,0,0},
{0,2,0,0}
};
pair<int,int>dfs(int x,int k2,int k3,int k5,int k7,bool flag,bool zero,bool zero2)
{
	//cout<<x<<" "<<k2<<" "<<k3<<" "<<k5<<" "<<k7<<" "<<flag<<" "<<zero<<" "<<f[x][k2][k3][k5][k7]<<endl;
	if(x==0&&zero2)return {0,1};
	if(x==0&&!k2&&!k3&&!k5&&!k7)return {0,1};
	if(x==0)return {0,0};
	if(!flag&&!zero&&f[x][k2][k3][k5][k7]!=-1)return {f[x][k2][k3][k5][k7],g[x][k2][k3][k5][k7]};
	int ed=9;
	if(flag)ed=a[x];
	int sum=0,tot=0;
	for(int i=0;i<=ed;i++)
	{
		if(!zero&&i==0&&k!=0)continue;
		int p2=k2-s[i][0],p3=k3-s[i][1],p5=k5-s[i][2],p7=k7-s[i][3];
		if((p2<0||p3<0||p5<0||p7<0))continue;
		pair<int,int>res=dfs(x-1,p2,p3,p5,p7,flag&(i==a[x]),zero&(i==0),zero2|((!zero)&(!i)));
		tot+=res.second;
		tot%=mod;
		sum+=res.first+i*power[x-1]%mod*res.second%mod;
		sum%=mod;
	}
	if(!flag&&!zero)f[x][k2][k3][k5][k7]=sum,g[x][k2][k3][k5][k7]=tot;
	return {sum,tot};
}
pair<int,int>dfs2(int x,bool flag,bool zero,bool zero2)
{
	if(x==0)return {0,zero2};
	if(f2[x][flag][zero][zero2]!=-1)return {f2[x][flag][zero][zero2],g2[x][flag][zero][zero2]};
	int ed=9;
	if(flag)ed=a[x];
	int tot=0,sum=0;
	for(int i=0;i<=ed;i++)
	{
		pair<int,int>res=dfs2(x-1,flag&(i==a[x]),zero&(i==0),zero2|((!zero)&(!i)));
		tot+=res.second;
		tot%=mod;
		sum+=res.first+i*power[x-1]%mod*res.second%mod;
		sum%=mod;
	}
	f2[x][flag][zero][zero2]=sum,g2[x][flag][zero][zero2]=tot;
	return {sum,tot};
}
int solve(int x)
{
	cnt=0;
	while(x)
	{
		a[++cnt]=x%10;
		x/=10;
	}
	if(k==0)
	{
		memset(f2,-1,sizeof(f2));
		memset(g2,0,sizeof(g2));
		int res=dfs2(cnt,1,1,0).first;
		return res;
	}
	int t=k;
	t2=t3=t5=t7=0;
	while(t%2==0)t/=2,t2++;
	while(t%3==0)t/=3,t3++;
	while(t%5==0)t/=5,t5++;
	while(t%7==0)t/=7,t7++;
	//if(t2>3*cnt||t3>2*cnt||t5>cnt||t7>cnt)return 0;
	if(k!=0&&t!=1)return 0;
	for(int i=0;i<=cnt;i++)
		for(int j=0;j<=t2;j++)
			for(int sp=0;sp<=t3;sp++)
				for(int q=0;q<=t5;q++)
					for(int l=0;l<=t7;l++)f[i][j][sp][q][l]=-1,g[i][j][sp][q][l]=0;
	int res=dfs(cnt,t2,t3,t5,t7,1,1,0).first;
	return res;
}
signed main()
{
// 	freopen("fans.in","r",stdin);
// 	freopen("fans.out","w",stdout);
	scanf("%lld",&n);
	power[0]=1;
	for(int i=1;i<=18;i++)power[i]=power[i-1]*10,power[i]%=mod;
	for(int i=1;i<=n;i++)
	{
		int l,r;
		scanf("%lld%lld%lld",&l,&r,&k);
		int ans=solve(r)-solve(l-1);
		ans=(ans%mod+mod)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
```
考虑上述方法缺陷：有特别多状态是用不到的，如 $2^{54}\times 3^{36}$，而我们把它们都压入了数组。

解决上述问题：直接预处理出来 $10^{18}$ 以内满足 $2^a\times3^b\times5^c\times7^d$ 的数，直接循环枚举就好。

那么现在我们转移状态时要知道下一个状态的编号为多少，这个提前用二分预处理出来即可，注意清空数组时得用栈先存储哪些状态发生了变化，再清空。

期望得分：$100pts$，实际得分：$50pts$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#define int long long
using namespace std;
const int mod=20120427;
const int N=7e4+5;
const int M=1e18+5;
int n,cnt,a[20],f[20][N],g[20][N],t2,t3,t5,t7,power[20],f2[20][2][2][2],g2[20][2][2][2],num[N],lent,to[N][10],cnp;
int s[10][4]={
{0,0,0,0},
{0,0,0,0},
{1,0,0,0},
{0,1,0,0},
{2,0,0,0},
{0,0,1,0},
{1,1,0,0},
{0,0,0,1},
{3,0,0,0},
{0,2,0,0}
};
pair<int,int>q[N];
pair<int,int>dfs(int x,int k,bool flag,bool zero)
{
	if(k==0)return {0,0};
	//cout<<x<<" "<<k<<" "<<flag<<" "<<zero<<endl;
	if(x==0&&k==1)return {0,1};
	if(x==0)return {0,0};
	if(!flag&&!zero&&f[x][k]!=-1)return {f[x][k],g[x][k]};
	int ed=9;
	if(flag)ed=a[x];
	int sum=0,tot=0;
	for(int i=0;i<=ed;i++)
	{
		if(!zero&&i==0)continue;
		if(!to[k][i])continue;
		pair<int,int>res=dfs(x-1,to[k][i],flag&(i==a[x]),zero&(i==0));
		tot+=res.second;
		tot%=mod;
		sum+=res.first+i*power[x-1]%mod*res.second%mod;
		sum%=mod;
	}
	if(!flag&&!zero)f[x][k]=sum,g[x][k]=tot,q[++cnp]={x,k};
	return {sum,tot};
}
pair<int,int>dfs2(int x,bool flag,bool zero,bool zero2)
{
	if(x==0)return {0,zero2};
	if(f2[x][flag][zero][zero2]!=-1)return {f2[x][flag][zero][zero2],g2[x][flag][zero][zero2]};
	int ed=9;
	if(flag)ed=a[x];
	int tot=0,sum=0;
	for(int i=0;i<=ed;i++)
	{
		pair<int,int>res=dfs2(x-1,flag&(i==a[x]),zero&(i==0),zero2|((!zero)&(!i)));
		tot+=res.second;
		tot%=mod;
		sum+=res.first+i*power[x-1]%mod*res.second%mod;
		sum%=mod;
	}
	f2[x][flag][zero][zero2]=sum,g2[x][flag][zero][zero2]=tot;
	return {sum,tot};
}
int numfind(int x)
{
	int l=1,r=lent;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(num[mid]<x)l=mid+1;
		else r=mid;
	}
	return l;
}
int solve(int x,int k)
{
	cnt=0;
	while(x)
	{
		a[++cnt]=x%10;
		x/=10;
	}
	if(k==0)
	{
		memset(f2,-1,sizeof(f2));
		memset(g2,0,sizeof(g2));
		int res=dfs2(cnt,1,1,0).first;
		return res;
	}
	int t=k;
	t2=t3=t5=t7=0;
	while(t%2==0)t/=2,t2++;
	while(t%3==0)t/=3,t3++;
	while(t%5==0)t/=5,t5++;
	while(t%7==0)t/=7,t7++;
	if(t!=1)return 0;
	cnp=0;
	int res=dfs(cnt,numfind(k),1,1).first;
	for(int i=cnp;i>0;i--)f[q[i].first][q[i].second]=-1,g[q[i].first][q[i].second]=0;
	return res;
}
void prepare()
{
	int num2=1;
	for(int i=0;i<=54;i++)
	{
		if(num2>M)break;
		int num3=1;
		for(int j=0;j<=36;j++)
		{
			if(num2*num3>M)break;
			int num5=1;
			for(int q=0;q<=18;q++)
			{
				if(num2*num3*num5>M)break;
				int num7=1;
				for(int l=0;l<=18;l++)
				{
					if(num2*num3*num5*num7>M)break;
					num[++lent]=num2*num3*num5*num7;
					num7*=7;
				}
				num5*=5;
			}
			num3*=3;
		}
		num2*=2;
	}
	sort(num+1,num+1+lent);
	for(int i=1;i<=lent;i++)
	{
		to[i][0]=to[i][1]=i;
		for(int j=2;j<=9;j++)
		{
			if(num[i]%j)continue;
			to[i][j]=numfind(num[i]/j);
		}
	}
}
int read()
{
	char ch=getchar();
	int sum=0;
	while(ch>'9'||ch<'0')ch=getchar();
	while(ch>='0'&&ch<='9')sum=(sum<<1)+(sum<<3)+(ch^48),ch=getchar();
	return sum;
}
void write(int x)
{
	if(x/10)write(x/10);
	putchar((x%10)^48);
}
signed main()
{
	//freopen("fans.in","r",stdin);
	//freopen("fans.out","w",stdout);
	prepare();
	n=read();
	power[0]=1;
	memset(f,-1,sizeof(f));
	for(int i=1;i<=18;i++)power[i]=power[i-1]*10,power[i]%=mod;
	for(int i=1;i<=n;i++)
	{
		int l,r,k;
		l=read(),r=read(),k=read();
		int ans=solve(r,k)-solve(l-1,k);
		ans=(ans%mod+mod)%mod;
		write(ans);
		putchar('\n');
	}
	return 0;
}
```
那么剩下的也不好弄了，直接上剪枝。

记录一下每个状态搜到 $1$ 的最小步数，如果现在状态的步数已经大于了剩下的位数，说明无法达到，直接返回。

记录最小步数就从自己可能的下一个状态转移上来，取最小值。

期望得分：$100pts$，实际得分：$100pts$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#define int long long
using namespace std;
const int mod=20120427;
const int N=7e4+5;
const int M=1e18+5;
int n,cnt,a[20],f[20][N],g[20][N],t2,t3,t5,t7,power[20],f2[20][2][2][2],g2[20][2][2][2],num[N],lent,to[N][10],cnp,dep[N];
pair<int,int>q[N];
pair<int,int>dfs(int x,int k,bool flag,bool zero)
{
	if(k==0)return {0,0};
	if(dep[k]>x)return {0,0};
	//cout<<x<<" "<<k<<" "<<flag<<" "<<zero<<endl;
	if(x==0&&k==1)return {0,1};
	if(x==0)return {0,0};
	if(!flag&&!zero&&f[x][k]!=-1)return {f[x][k],g[x][k]};
	int ed=9;
	if(flag)ed=a[x];
	int sum=0,tot=0;
	for(int i=0;i<=ed;i++)
	{
		if(!zero&&i==0)continue;
		if(!to[k][i])continue;
		pair<int,int>res=dfs(x-1,to[k][i],flag&(i==a[x]),zero&(i==0));
		tot+=res.second;
		tot%=mod;
		sum+=res.first+i*power[x-1]%mod*res.second%mod;
		sum%=mod;
	}
	if(!flag&&!zero)f[x][k]=sum,g[x][k]=tot,q[++cnp]={x,k};
	return {sum,tot};
}
pair<int,int>dfs2(int x,bool flag,bool zero,bool zero2)
{
	if(x==0)return {0,zero2};
	if(f2[x][flag][zero][zero2]!=-1)return {f2[x][flag][zero][zero2],g2[x][flag][zero][zero2]};
	int ed=9;
	if(flag)ed=a[x];
	int tot=0,sum=0;
	for(int i=0;i<=ed;i++)
	{
		pair<int,int>res=dfs2(x-1,flag&(i==a[x]),zero&(i==0),zero2|((!zero)&(!i)));
		tot+=res.second;
		tot%=mod;
		sum+=res.first+i*power[x-1]%mod*res.second%mod;
		sum%=mod;
	}
	f2[x][flag][zero][zero2]=sum,g2[x][flag][zero][zero2]=tot;
	return {sum,tot};
}
int numfind(int x)
{
	int l=1,r=lent;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(num[mid]<x)l=mid+1;
		else r=mid;
	}
	return l;
}
int solve(int x,int k)
{
	cnt=0;
	while(x)
	{
		a[++cnt]=x%10;
		x/=10;
	}
	if(k==0)
	{
		memset(f2,-1,sizeof(f2));
		memset(g2,0,sizeof(g2));
		int res=dfs2(cnt,1,1,0).first;
		return res;
	}
	int t=k;
	t2=t3=t5=t7=0;
	while(t%2==0)t/=2,t2++;
	while(t%3==0)t/=3,t3++;
	while(t%5==0)t/=5,t5++;
	while(t%7==0)t/=7,t7++;
	if(t!=1)return 0;
	cnp=0;
	int res=dfs(cnt,numfind(k),1,1).first;
	for(int i=cnp;i>0;i--)f[q[i].first][q[i].second]=-1,g[q[i].first][q[i].second]=0;
	return res;
}
void prepare()
{
	int num2=1;
	for(int i=0;i<=54;i++)
	{
		if(num2>M)break;
		int num3=1;
		for(int j=0;j<=36;j++)
		{
			if(num2*num3>M)break;
			int num5=1;
			for(int q=0;q<=18;q++)
			{
				if(num2*num3*num5>M)break;
				int num7=1;
				for(int l=0;l<=18;l++)
				{
					if(num2*num3*num5*num7>M)break;
					num[++lent]=num2*num3*num5*num7;
					num7*=7;
				}
				num5*=5;
			}
			num3*=3;
		}
		num2*=2;
	}
	sort(num+1,num+1+lent);
	for(int i=1;i<=lent;i++)
	{
		if(i!=1)dep[i]=1e18;
		to[i][0]=to[i][1]=i;
		for(int j=2;j<=9;j++)
		{
			if(num[i]%j)continue;
			int lim=numfind(num[i]/j);
			to[i][j]=lim;
			dep[i]=min(dep[i],dep[lim]+1);
		}
	}
}
int read()
{
	char ch=getchar();
	int sum=0;
	while(ch>'9'||ch<'0')ch=getchar();
	while(ch>='0'&&ch<='9')sum=(sum<<1)+(sum<<3)+(ch^48),ch=getchar();
	return sum;
}
void write(int x)
{
	if(x/10)write(x/10);
	putchar((x%10)^48);
}
signed main()
{
	//freopen("fans.in","r",stdin);
	//freopen("fans.out","w",stdout);
	prepare();
	n=read();
	power[0]=1;
	memset(f,-1,sizeof(f));
	for(int i=1;i<=18;i++)power[i]=power[i-1]*10,power[i]%=mod;
	for(int i=1;i<=n;i++)
	{
		int l,r,k;
		l=read(),r=read(),k=read();
		int ans=solve(r,k)-solve(l-1,k);
		ans=(ans%mod+mod)%mod;
		write(ans);
		putchar('\n');
	}
	return 0;
}
```


---

