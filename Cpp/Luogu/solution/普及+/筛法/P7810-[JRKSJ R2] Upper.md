# [JRKSJ R2] Upper

## 题目描述

有 $n$ 张扑克，第 $i$ 张扑克上写有一个正整数 $a_i$。

现在要把扑克划分成若干个合法的连续子段，其中，一个连续子段 $[l,r]$ “合法”当且仅当这个子段同时满足两个条件： 

* $a_l< a_r$
* $\gcd(a_l,a_r)>1$ 

请问最多能划分多少段。如果没有合法的划分方案，输出 $-1$ 即可。

如果您不知道 $\gcd$ 是什么意思，请看“提示”部分。

## 说明/提示

### 数据范围
本题采用捆绑测试。

对于 $100\%$ 的数据，$2\le n\le 10^5$，$1\le a_i\le 10^9$。

| $\text{Subtask}$ | $n\le$ | $a_i\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $10^9$ | 无 | $5$ |
| $2$ | $3\times10^3$ | $10^9$ | 无 | $15$ |
| $3$ | $2\times10^4$ | $10^6$ | 无 | $20$ |
| $4$ | $2\times 10^4$ | $10^9$ | 无 | $10$ |
| $5$ | $10^5$ | $10^9$ | 数据随机 | $10$ |
| $6$ | $10^5$ | $10^9$ | 无 | $40$ |

### 样例解释
对于样例 $1$，有且仅有一种划分方案 $\{2,1,8\},\{3,9\}$。\
对于样例 $2$，无合法的划分方案。

### 提示
对于两个正整数 $a,b$，$\gcd(a,b)$ 为它们的最大公因数，即满足既是 $a$ 的因数又是 $b$ 的因数的数中最大的数。

## 样例 #1

### 输入

```
5
2 1 8 3 9```

### 输出

```
2```

## 样例 #2

### 输入

```
5
5 4 3 2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
20
20 9 36 36 40 8 3 10 9 20 18 12 30 20 30 15 8 9 27 45```

### 输出

```
7```

# 题解

## 作者：KazamaRuri (赞：6)

题意清晰，~~懒得写~~不再赘述。

## 分析

记 $ V $ 为值域大小。

首先有一个 $ O(n^2 \log V) $ 的暴力 dp，直接按照题意做，状态转移方程如下：
$$
f_i = 1 + \max_{j<i,a_i>a_j,\gcd(a_i,a_j)>1} f_{j-1}
$$
因为 $ \gcd(a_i,a_j)>1 $ 的限制非常难办，又因为我们不在乎 $ \gcd(a_i,a_j) $ 的具体值为多少，只需保证有公共因子，再进一步说，就是存在**公共质因子**。那么就可以对于每个 $ a_i $ 质因数分解一下，转移就在有公共质因子的数里面转移。确定一下质因子的上界以此优化，明显是 $ \sqrt{V} $，不然就没有可能有公因子了。特殊地，每个数最多只有一个大于 $ \sqrt{V} $ 的质因子，需要单独处理。

根据 $ [x \mid \gcd(a_i,a_j)]=[ x \mid a_i] \wedge [x \mid a_j] $。得到新的状态转移方程：
$$
f_i = 1 + \max_{d \mid a_i \wedge d \ne 1 }{ \max_{j<i,a_i>a_j,d \mid a_j} f_{j-1} }
$$
优化方式就很明显了。先解决整除的限制，对于每个 $ d $，开一棵权值线段树，按 $ a_i $ 插入 $ f_{i-1} $ 然后就做出来啦，总时间复杂度大概是 $ O(n \, \omega(V) \log n) $（其中 $ \omega $ 函数表示一个数的本质不同质因子的数量，在 $ 10^9 $ 的范围内最大值只有 $ 19 $，因此跑的飞快）。

## 代码

没有刻意压行，并且是最优解 450ms。

```cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;

char buf[1<<20],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)
inline int read(){
	int x=0; char ch=getchar(); while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar(); return x;
}
const int N=1e5+5,inf=1<<30;
int n,tot,a[N],t[N<<6],f[N],lc[N<<6],rc[N<<6],cnt,h[N],num,p[N],rt[N];
bool isp[N]; vector<int>q[N];
void upd(int &x,int l,int r,int p,int k){
	if(l>p||r<p) return ; x=x?x:++tot,t[x]=max(t[x],k); if(l==r) return ;
	int mid=l+r>>1; upd(lc[x],l,mid,p,k),upd(rc[x],mid+1,r,p,k);
}
int ask(int x,int l,int r,int p){
	if(l>p||!x) return -inf; if(r<=p) return t[x]; int mid=l+r>>1;
	return max(ask(lc[x],l,mid,p),ask(rc[x],mid+1,r,p));
}
void init(int n){
	for(int i=2;i<=n;i++){
		if(!isp[i]) p[++num]=i;
		for(int j=1;j<=num&&p[j]*i<=n;j++){
			isp[i*p[j]]=1; if(i%p[j]==0) break;
		}
	}
}
int main(){ init(31623),n=read();
	for(int i=1,x;i<=n;i++){
		h[++cnt]=x=a[i]=read();
		for(int j=1;j<=num&&p[j]*p[j]<=x;j++)
			if(x%p[j]==0){
				q[i].push_back(p[j]);
				while(x%p[j]==0) x/=p[j];
			}
		if(x<=48000&&x>1) q[i].push_back(x);
	} sort(h+1,h+1+n),cnt=unique(h+1,h+1+n)-h-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(h+1,h+1+cnt,a[i])-h,f[i]=-inf;
	for(int i=1;i<=n;i++)
		for(auto x:q[i]){
			if(rt[x]) f[i]=max(f[i],ask(rt[x],1,n,a[i]-1)+1);
			if(f[i-1]>=0) upd(rt[x],1,n,a[i],f[i-1]);
		}
	return !printf("%d",f[n]>0?f[n]:-1);
}
```

提一嘴，懒得写素数筛可以这样写找质因子（不会 TLE）：
```cpp
if(x%2==0){
	q[i].push_back(2);
	while(x%2==0) x>>=1;
}
for(int j=3;j*j<=x;j+=2)
	if(x%j==0){
		q[i].push_back(j);
		while(x%j==0) x/=j;
	}
if(x>1) q[i].push_back(x);
```

---

## 作者：Spasmodic (赞：4)

666 AC。

考虑一个显然的 dp：
$$
f_i=\min\limits_{j<i,a_j<a_i,(a_j,a_i)>1}f_{j-1}
$$
直接写是 $O(n^2\log v)$ 的，显然会 t。

考虑对其进行优化，我们可以枚举 $p|a_i$，然后就转化为
$$
f_i=\min_{p|a_i}\min_{j<i,a_j<a_i,p|a_j}f_{j-1}
$$
考虑后面这个式子，明显可以用权值线段树做，对 $a$ 离散化的话查询是 $O(\log n)$。

那么我们对于每个质因子，维护一颗权值线段树，并且每次计算完 $f_{i-1}$ 后，枚举 $p|a_i$ 在 $p$ 对应的权值线段树上在 $a_i$ 处更新 $f_{i-1}$。注意到每次更新的时候其实只有 $O(\log n)$ 个结点受到影响，那么采用动态开点线段树就可以把空间控制在 $O(n\omega(v)\log n)$，其中 $\omega(n)$ 表示 $n$ 的不同质因子数。

最后对于质因子分解，我们考虑一个简单的优化，在暴力分解的基础上线性筛出质数，然后试除法就可以只用 $\sqrt v$ 以内的质因子去试，这样复杂度可以少一个 $\log v$。

这样一来时间复杂度就是 $O(n\pi(\sqrt v)+n\omega(v)\log n)$，空间是 $O(n\omega(v)\log n)$，轻松通过。

```cpp
// Problem: P7810 [JRKSJ R2] Upper
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7810?contestId=48251
// Memory Limit: 256 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define endl '\n' 
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int P=998244353;
void chkmax(int &x,int y){if(x<y)x=y;}
void chkmin(int &x,int y){if(x>y)x=y;}
int qpow(int a,int k){
	int ret=1;
	while(k){
		if(k&1)ret=ret*(long long)a%P;
		a=a*(long long)a%P;
		k>>=1;
	}
	return ret;
}
int qpow(int a,int k,int p){
	int ret=1;
	while(k){
		if(k&1)ret=ret*(long long)a%p;
		a=a*(long long)a%p;
		k>>=1;
	}
	return ret;
}
int norm(int x){return x>=P?x-P:x;}
int reduce(int x){return x<0?x+P:x;}
void add(int&x,int y){if((x+=y)>=P)x-=P;}
struct IO_Tp {
    const static int _I_Buffer_Size = 2 << 22;
    char _I_Buffer[_I_Buffer_Size], *_I_pos = _I_Buffer, *_I_end= _I_Buffer + _I_Buffer_Size;

    const static int _O_Buffer_Size = 2 << 22;
    char _O_Buffer[_O_Buffer_Size], *_O_pos = _O_Buffer;

    IO_Tp() { fread(_I_Buffer, 1, _I_Buffer_Size, stdin); }
    ~IO_Tp() { fwrite(_O_Buffer, 1, _O_pos - _O_Buffer, stdout); }

    IO_Tp &operator>>(int &res) {
    	int f=1;
        while (_I_pos!=_I_end&&!isdigit(*_I_pos)&&(*_I_pos)!='-') ++_I_pos;
        assert(_I_pos!=_I_end);
        if(*_I_pos=='-')f=-1,++_I_pos;
        res = *_I_pos++ - '0';
        while (_I_pos!=_I_end&&isdigit(*_I_pos)) res = res * 10 + (*_I_pos++ - '0');
        res*=f;
        assert(_I_pos!=_I_end);
        return *this;
    }
    
    IO_Tp &operator>>(string &res){
    	res="";
    	auto blank=[&](char ch){
    		if(ch==' '||ch=='\n'||ch=='\r'||ch=='	'||ch=='\0')return 1;
    		return 0;
		};
		while(_I_pos!=_I_end&&blank(*_I_pos)) ++_I_pos;
    	while (_I_pos!=_I_end&&!blank(*_I_pos))res += *_I_pos++;
    	assert(_I_pos!=_I_end);
    	return *this;
	} 

    IO_Tp &operator<<(int n) {
    	if(n<0)*_O_pos++='-',n=-n;
        static char _buf[10];
        char *_pos = _buf;
        do
            *_pos++ = '0' + n % 10;
        while (n /= 10);
        while (_pos != _buf) *_O_pos++ = *--_pos;
        return *this;
    }

    IO_Tp &operator<<(char ch) {
        *_O_pos++ = ch;
        return *this;
    }
    
    IO_Tp &operator<<(string &res){
    	for (char ch:res) *_O_pos++ = ch;
    	return *this;
	} 
} IO;
const int N=1e5+5;
int n,m,a[N],sa[N],ua[N],f[N],cnt[N],pr[N][10];
int cp,p[N];
bool vst[N];
void init(int n){
	rep(i,2,n){
		if(!vst[i])p[++cp]=i;
		for(int j=1;j<=cp&&i*p[j]<=n;j++){
			vst[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
}
void dcp(int id){
	int x=a[id];
	for(int i=1;p[i]*p[i]<=x;i++)if(x%p[i]==0){
		pr[id][++cnt[id]]=p[i];
		while(x%p[i]==0)x/=p[i];
	}
	if(x>1)pr[id][++cnt[id]]=x;
}
unordered_map<int,int>rt;
int tot;
struct node{
	int lc,rc,ma;
}st[N<<5];
void pushup(int k){st[k].ma=max(st[st[k].lc].ma,st[st[k].rc].ma);}
void insert(int&k,int l,int r,int p,int v){
	if(!k)k=++tot;
	if(l==r)return chkmax(st[k].ma,v),void();
	int mid=l+r>>1;
	if(p<=mid)insert(st[k].lc,l,mid,p,v);
	else insert(st[k].rc,mid+1,r,p,v);
	pushup(k);
	return;
}
int ask(int p,int l,int r,int x,int y){
	if(!p)return -2;
	if(x<=l&&r<=y)return st[p].ma;
	int mid=l+r>>1,ret=-2;
	if(x<=mid)chkmax(ret,ask(st[p].lc,l,mid,x,y));
	if(mid<y)chkmax(ret,ask(st[p].rc,mid+1,r,x,y));
	return ret;
}
int main(){
	IO>>n;
	init(1e5);
	rep(i,1,n)IO>>a[i],sa[i]=a[i],dcp(i);
	sort(sa+1,sa+n+1);
	m=unique(sa+1,sa+n+1)-sa-1;
	rep(i,1,n)ua[i]=lower_bound(sa+1,sa+m+1,a[i])-sa;
	memset(f,-1,sizeof f);
	f[0]=0;
	rep(i,1,n){
		rep(j,1,cnt[i]){
			int p=rt[pr[i][j]];
			chkmax(f[i],ask(p,1,m,1,ua[i]-1)+1);
			if(f[i-1]>=0)insert(p,1,m,ua[i],f[i-1]);
			rt[pr[i][j]]=p;
		}
	}
	IO<<f[n]<<endl;
	return 0;
}
```

---

## 作者：王熙文 (赞：2)

感觉这道题 cdq 思路非常显然啊……为什么没人写？

## 思路

首先我们有一个很显然的 dp：设 $dp_i$ 表示前 $i$ 个最多分的段数。那么 $dp_0=0, dp_i = \max\limits_{j<i,a_j<a_i,\gcd(a_j,a_i)>1} dp_{j-1}$。

首先，我们可以对于每个数分解质因数来得到它的所有质因数。对于每个数需要遍历小于等于 $\sqrt{a_i}$ 的所有质数，大约有 $4000$ 个，这样需要运算大约 4e8 次，但是能过（我也不知道为啥能过，如果读者觉得过不了就没想到做法，建议再想想）。

先考虑如果没有 $a_j<a_i$ 的限制，该如何做。我们可以对于每个质数都记录拥有这个质数的所有数的 $dp$ 值的最大值。对于 $dp_i$，找到 $a_i$ 的所有质因数，然后更新 $dp_i$，最后再更新 $a_i$ 的所有质因数。

现在有了 $a_j<a_i$ 这个限制。众所周知，cdq 分治对于 dp 转移中有偏序关系的可以优化，所以它也可以优化这个问题。

设现在分治的区间为 $[l,r]$，此时有一个要求是 $[1,l-1
]$ 的值已经对当前区间 $[l,r]$ 做完贡献了。此时这个操作是要把当前区间内的所有值都求出来。取 $mid=\lfloor \dfrac{l+r}{2}\rfloor$，然后递归求解  $[l,mid]$ 这个区间。接下来，考虑 $[mid+1,r]$ 这个区间的贡献来自哪里。一种是它自己的贡献，另一种则是 $[l,mid]$ 这个区间对于 $[mid+1,r]$ 这个区间的贡献。对于自己的贡献可以递归求解，但是注意我们要满足第一行的那个要求，所以需要先处理 $[l,mid]$ 对于 $[mid+1,r]$ 的贡献。

可以发现这样有一个好处，下标的关系不用管了。这样转移就只有值的一个限制了。可以将 $[l,mid]$ 中的值和 $[mid+1,r]$ 中的值分别排序，然后双指针扫一下记录贡献。具体来说，顺序遍历 $[mid+1,r]$ 中的每个元素，设当前遍历到了 $i$，然后记录一个下标 $now$ 表示此时 $[l,now-1]$ 中的值全都小于 $a_i$。首先从 $a_{i-1}$ 到 $a_i$ 会有一些 $\ge a_{i-1}$ 但 $<a_i$ 的数，我们先要更新这些数的贡献。更新方式与上文说的不看 $a_j<a_i$ 这个限制的方法是相同的。接下来要计算 $a_i$ 的贡献。这个计算的方式也是相同的。

最后再递归 $[mid+1,r]$ 即可。

综上，我们可以发现 cdq 分治的主要思路是：使用分治取消下标的限制，再排序双指针取消值的限制。剩下的直接更新。

## 代码

记录每个质数拥有这个质数的所有 dp 值的最大值可以用 ```map``` 或者 ```gp_hash_table```，但是不要用 ```unordered_map```，会 T 飞。具体原因我也不知道。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;

struct CDQ
{
	int x,id;
} a[100010];
bool cmp1(CDQ x,CDQ y)
{
	return x.x<y.x;
}
bool cmp2(CDQ x,CDQ y)
{
	return x.id<y.id;
}

vector<int> zys[100010];

bool vis[40010]; int tot=0,prime[10010];

void init()
{
	for(int i=2; i<=40000; ++i)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			for(int j=i*i; j<=40000; j+=i) vis[j]=1;
		}
	}
}

void cf(int wz,int x)
{
	for(int i=1; prime[i]*prime[i]<=x; ++i)
	{
		if(x%prime[i]==0)
		{
			zys[wz].push_back(prime[i]);
			while(x%prime[i]==0) x/=prime[i];
		}
	}
	if(x!=1) zys[wz].push_back(x);
}

int dp[100010];

map<int,int> mp;

void cdq(int l,int r)
{
	if(l==r) return;
	sort(a+l,a+r+1,cmp2);
	int mid=(l+r)>>1;
	cdq(l,mid);
	sort(a+l,a+mid+1,cmp1),sort(a+mid+1,a+r+1,cmp1);
	int now=l;
	mp.clear();
	for(int i=mid+1; i<=r; ++i)
	{
		while(now<=mid && a[now].x<a[i].x)
		{
			for(int j=0; j<zys[a[now].id].size(); ++j)
			{
				mp[zys[a[now].id][j]]=max(mp[zys[a[now].id][j]],dp[a[now].id-1]+1);
			}
			++now;
		}
		for(int j=0; j<zys[a[i].id].size(); ++j)
		{
			dp[a[i].id]=max(dp[a[i].id],(!mp[zys[a[i].id][j]]?(int)-1e9:mp[zys[a[i].id][j]]));
		}
	}
	cdq(mid+1,r);
}

int main()
{
	memset(dp,-0x3f,sizeof(dp)); dp[0]=0;
	init();
	cin>>n;
	for(int i=1; i<=n; ++i) cin>>a[i].x,cf(i,a[i].x),a[i].id=i;
	cdq(1,n);
	cout<<(dp[n]<=0?-1:dp[n]);
	return 0;
}
```

---

## 作者：ZillionX (赞：2)

# Description

给定长为 $n$ 的序列 $a$，要求将序列分为若干个区间，其中区间 $[l,r]$ 满足 $a_l<a_r$ 且 $\gcd(a_l,a_r)>1$，最大化区间个数。

$n \le 10^5, V \le 10^9$，时限 1.5s。

# Solution

显然考虑套路地 DP，不妨设 $f_i$ 表示将 $[1,i]$ 划分的最大方案数，有转移

$$f_i=\max_{l<i,a_l<a_i,\gcd(a_l,a_i)>1} f_{l-1}+1$$

注意到 $\gcd(a_l,a_i)>1$ 的条件很松，化开 $\gcd$

$$f_i=\max_{p \in {\rm Prime}, p \mid a_i}\max_{l<i,a_l<a_i,p \mid a_l} f_{l-1}+1$$

推到这里已经可以做了，我们首先对序列 $a$ 离散化。

不难想到用权值线段树来维护，我们可以给每一个出现过的不同的质因子开一棵线段树，这样乍一看空间复杂度不对，实际上最多只会有 $\mathcal O(\log n + \log V)$ 棵线段树。

为什么呢？考虑粗略计算一下上界，序列 $a$ 中的元素和最大是 $nV$，然后我们把质数从小到大一个个乘起来，超过 $nV$ 时停止，那么个数的上界就是 $\mathcal O(\log nV)$，即 $\mathcal O(\log n + \log V)$，使用动态开点，每次最多新增 $\log n$ 个点，空间复杂度就是 $\mathcal O(n (\log n+\log V)\log n)$，而且必然跑不满。

回到原题，具体地说，我们预处理出 $\sqrt V$ 内的质数，然后 $\mathcal O(\dfrac{\sqrt {a_i}}{\log a_i})$ 地分解质因数，对于每个 $p \mid a_i$，查询 $p$ 的线段树内 $[1,i)$ 的前缀最大值，并更新 $f_i$，同时把 $f_{i-1}$ 的值单点加一下。

至此我们在 $\mathcal O(\sqrt V + n \dfrac{\sqrt {V}}{\log V} + n \log V \log n)$ 的时间复杂度内完成了本题。

# Code

加了个 [Exact Division](https://www.luogu.com.cn/blog/ZillionX/solution-p5071)，直接跑到了最优解 rk1。

```cpp
typedef unsigned int ui;
const int N=1e5+1,V=31623,P=3411,D=11;

int n,tot,p[P],dv[N][D],f[N];
ui a[N],cp[N],pv[P],pm[P];
bitset<V> vs;
unordered_map<int,int> mp;

inline char gc() {
    static char buf[100000],*p1(buf),*p2(buf);
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++; 
}

inline int rd() {
	int x(0);
	char ch(gc());
	while (ch<'0' || ch>'9') ch=gc();
	while (ch>='0' && ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=gc();
	}
	return x;
}

inline ui inv32(ui n) {
	ui x(1);
	x*=2u-n*x,x*=2u-n*x,x*=2u-n*x,x*=2u-n*x,x*=2u-n*x;
	return x;
}

void Init(int n) {
	vs[1]=1;
	tot=1,p[1]=2,vs[4]=1;
	for (int i=3;i<=n;i++) {
		if (vs[i]==0)
			p[++tot]=i,pv[tot]=inv32(i),
			pm[tot]=ui(-1)/i;
		if (i*2<=n) vs[i*2]=1;
		else continue;
		if (!(i&1)) continue;
		for (int j=2;j<=tot && i*p[j]<=n;j++) {
			vs[i*p[j]]=1;
			if (i*pv[j]<=pm[j]) break;
		}
	}
}

struct Seg {
	int tot,rt[N*51],ls[N*51*16],rs[N*51*16],v[N*51*16];
	
	void Up(int x) {
		v[x]=max(v[ls[x]],v[rs[x]]);
	}
	
	void Upd(int &x,int l,int r,int pos,int k) {
		if (!x) x=++tot;
		if (l==r) {
			v[x]=max(v[x],k);
			return;
		}
		int mid((l+r)>>1);
		if (pos<=mid) Upd(ls[x],l,mid,pos,k);
		else Upd(rs[x],mid+1,r,pos,k);
		Up(x);
	}
	
	int Qry(int x,int l,int r,int L,int R) {
		if (!x) return -1e9;
		if (L<=l && r<=R) return v[x];
		int mid((l+r)>>1),Sum(-1e9);
		if (L<=mid) Sum=Qry(ls[x],l,mid,L,R);
		if (R>mid) Sum=max(Sum,Qry(rs[x],mid+1,r,L,R));
		return Sum;
	}
}T;

int main() {
	Init(V-1);
	n=rd();
	int idt(tot);
	for (int i=1;i<=n;i++) {
		a[i]=cp[i]=rd();
		int k(0);
		ui x(a[i]);
		if (!(x&1)) {
			k++,dv[i][k]=1,x>>=1;
			while (!(x&1)) x>>=1;
		}
		for (int j=2;j<=tot;j++)
			if (x*pv[j]<=pm[j]) {
				k++,dv[i][k]=j,x*=pv[j];
				while (x*pv[j]<=pm[j]) x*=pv[j];
				if (x==1) break;
			}
		if (x>1) {
			k++;
			if (!mp[x]) mp[x]=++idt;
			dv[i][k]=mp[x];
		}
		dv[i][0]=k;
	}
	sort(cp+1,cp+n+1);
	int sn(unique(cp+1,cp+n+1)-cp-1);
	for (int i=1;i<=n;i++) a[i]=lower_bound(cp+1,cp+sn+1,a[i])-cp;
	
	for (int i=1;i<=n;i++) f[i]=-1e9;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=dv[i][0];j++) {
			if (T.rt[dv[i][j]])
				f[i]=max(f[i],T.Qry(T.rt[dv[i][j]],1,sn,1,a[i]-1)+1);
			if (f[i-1]>=0) T.Upd(T.rt[dv[i][j]],1,sn,a[i],f[i-1]);
		}
	
	printf("%d",f[n]<0?-1:f[n]);
	return 0;
}
```


---

## 作者：Na2PtCl6 (赞：1)

### 本题解法
首先，我们可以想到设 $f(i)$ 为 $[1, i]$ 的元素最多能分成几份，然后就可以列出一下状态转移方程
$$ f(j)=\operatorname{max}{\{f(j),f(i)+1\}}(j>i,\operatorname{gcd}(a_i,a_j)>1,a_j>a_i)$$

我们发现，如果把每个数质因数分解，然后对每个质因数分别维护，就成了实现

$$ f(p,j)=\operatorname{max}\{f(p,j),f(p,i)+1\}(j>i,a_j>a_i)$$

考虑对每一个质因数开一颗区间取 max ，单点求值的线段树去维护这个东西。可以这么做的原因是前面对后面没有影响，且贡献可以重复计算。

### 本题代码
```cpp
#include<bits/stdc++.h>
#define ls lver[ver]
#define rs rver[ver]
using namespace std;
const int maxn=1e5+4;
char notpr[maxn];
int n,cnt,a[maxn],cpy[maxn],rk[maxn],f[maxn],lver[maxn<<8],rver[maxn<<8],val[maxn<<8];
vector< int > compo,pr; 
map< int,int > rt; 

void getpr(){
	int lim=100000;
	for(int i=2;i<=lim;i++){
		if(!notpr[i])
			pr.push_back(i);
		for(int j:pr){
			if(i%j==0||i*j>lim)
				break;
			notpr[i*j]=1;
		}
	}
}

void sep(int k){
	compo.clear();
	for(int i:pr){
		if(i*i>k)
			break;
		if(k%i==0)
			compo.push_back(i);
		while(k%i==0)	
			k/=i;
	}
	if(k>1)
		compo.push_back(k);
}

void modify(int l,int r,int &ver,int start,int end,int v){
	if(!ver)
		ver=++cnt;
	if(start<=l&&r<=end){
		val[ver]=max(val[ver],v);
		return ;
	}
	int mid=(l+r)>>1;
	if(start<=mid)
		modify(l,mid,ls,start,end,v);
	if(end>mid)
		modify(mid+1,r,rs,start,end,v);
}

int query(int l,int r,int ver,int p){
	int ret=-2;
	while(l<r){
		if(!ver)
			return ret;
		ret=max(ret,val[ver]);
		int mid=(l+r)>>1;
		if(p<=mid)
			r=mid,ver=ls;
		else
			l=mid+1,ver=rs;
	}
	if(!ver)
		return ret;
	ret=max(ret,val[ver]);
	return ret;
}

void init(){
	for(int i=1;i<=n;i++)
		cpy[i]=a[i];
	sort(cpy+1,cpy+n+1);
	int R=unique(cpy+1,cpy+n+1)-cpy;
	for(int i=1;i<=n;i++)
		rk[i]=lower_bound(cpy+1,cpy+R,a[i])-cpy;
}

void dp(){
	memset(val,-0x3f,sizeof(val));
	memset(f,-1,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++){
		sep(a[i]);
		for(int j:compo){
			f[i]=max(f[i],query(1,n,rt[j],rk[i])+1);
			if(f[i-1]>=0)
				modify(1,n,rt[j],rk[i]+1,n,f[i-1]);
		}
	}
}

int main(){
	getpr();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	init();
	dp();
	printf("%d\n",f[n]);
	return 0;
} 
```
### Bonus Version
如果把 $\operatorname{gcd}(a_l,a_r)>1$ 改成 $\operatorname{gcd}(a_l,a_{l+1}...,a_{r-1},a_r)$ 呢？

其实转移方程就只有一点点不一样的地方，实现起来区别也不会很大。

先建维护区间 $\operatorname{gcd}$ 的 st 表，用 st 表上二分求出每个 $l$ 最远能取的 $r$ 的范围，然后就用二维线段树维护区间取 $\operatorname{max}$ 和单点求值来维护 $f$。

---

