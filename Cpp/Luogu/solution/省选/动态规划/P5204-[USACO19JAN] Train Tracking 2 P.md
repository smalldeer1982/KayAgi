# [USACO19JAN] Train Tracking 2 P

## 题目背景

USACO 2019 一月月赛铂金组第三题

## 题目描述

每天特快列车都会经过农场。列车有 $N$ 节车厢（$1 \le N \le 10^5$），每节车厢上有一个 $1$ 到 $10^9$ 之间的正整数编号；不同的车厢可能会有相同的编号。
平时，Bessie 会观察驶过的列车，记录车厢的编号。但是今天雾实在太浓了，Bessie 一个编号也看不见！幸运的是，她从城市里某个可靠的信息源获知了列车编号序列的所有滑动窗口中的最小值。具体地说，她得到了一个正整数 $K$ ，以及 $N-K+1$ 个正整数 $c_1,…,c_{N+1-K}$ ，其中 $c_i$ 是车厢 $i,i+1,…,i+K-1$ 之中编号的最小值。

帮助 Bessie 求出满足所有滑动窗口最小值的对每节车厢进行编号的方法数量。由于这个数字可能非常大，只要你求出这个数字对 $10^9+7$ 取余的结果 Bessie 就满意了。

Bessie 的消息是完全可靠的；也就是说，保证存在至少一种符合要求的编号方式。


## 样例 #1

### 输入

```
4 2
999999998
999999999
999999998```

### 输出

```
3```

# 题解

## 作者：λᴉʍ (赞：13)

毒毒题，对着[嘤文题解](http://usaco.org/current/data/sol_tracking2_platinum_jan19.html)看了贼久

首先考虑此题的一个弱化版本：如果输入的所有$c_i$相等怎么做

现在假设有$len$个数，取值从$v$到$10^9$，而且每连续$k$个数至少有一个是$v$

那么取值就只有$v$和$>v$两种取值了，$>v$的取值有$10^9-v$种，设为$x$

那么有一个显然的dp，$f_i$表示这个问题i个数的答案

枚举这个数列的最后一个取值为$v$的数，假设是第$j$个，那么后面的$i-j$个数有$x$种选法

$f_i=\sum_{j=i-k+1}^{i}x^{i-j}f_{j-1}$

这个dp显然是不行的，还有一个dp，也是设$f_i$表示这个问题i个数的答案

$f_i=(x+1)f_{i-1}-x^kf_{i-k-1}$

第$i$个数随便选，乘$i-1$个数的答案，这时可能出现问题，就是第$i-k+1$个数到第$i$个数都$>v$导致了不合法，所以要减掉这些情况

为什么减掉的是$x^kf_{i-k-1}$呢，显然这$k$个数的放法共$x^k$种没有问题，要注意一下从第$i-k+1$个数到第$i-1$个数都$>v$，那么只有第$i-k$个数取值是$v$才能够满足最小值的条件，所以前面的取值方案数是$f_{i-k-1}$

```cpp
il int solve(int v,int len){
	int x=1000000000-v,xk=pow(x,k);
	f[0]=f[1]=1;
	for(int i=2;i<=len+1;++i){
		f[i]=1ll*(x+1)*f[i-1]%mod;
		if(i-k-1>=0)f[i]=(f[i]-1ll*xk*f[i-k-1]%mod+mod)%mod;
	}
	return f[len+1];
}
```

那么解决了前面的问题，后面的也很好办

设$s(v,len)$表示现在假设有$len$个数，取值从$v$到$10^9$，而且每连续$k$个数至少有一个是$v$问题的答案，可以在$O(len)$时间内球解

首先，可以将一段相等的$c$合并起来

然后（开始口胡）

对于一个段$c_i=\cdots=c_j$，如果只有这一段，方案数为$s(c_i,j-i+k)$

如果有一个$c_{i-1}>c_i$

那么可以知道的是

$\min\{a_{i-1},\cdots,a_{i+k-2}\}=c_{i-1}$

这里可以推出$a_{i-1},\cdots,a_{i+k-2}\geq c_{i-1}$

$\min\{a_{i},\cdots,a_{i+k-1}\}=c_{i}$

前面已经推出$a_{i},\cdots,a_{i+k-2}\geq c_{i-1}>c_{i}$了，所以这些都不可能是最小值

这一段的最小值只能有一个就是$a_{i+k-1}=c_{i}$

前面的数也都在前一段的范围内

所以这一段最前面$k$个数就没了，其中前$k-1$个数会在前面段计算答案，第$k$个数只有一个取值$c_i$

对于后面也同理，如果$c_{j+1}>c_j$则后面$k$个数没了

所以一段的len实际上是$j-i+k$减去0到2个$k$

对于所有的段依次球解最后方案数乘起来即可

代码极为简单

```cpp
#include<bits/stdc++.h>
#define il inline
#define vd void
#define mod 1000000007
typedef long long ll;
il ll gi(){
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int n,k;
int a[100010];
int f[100010];
il int pow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;y>>=1;
	}
	return ret;
}
il int solve(int v,int len){
	int x=1000000000-v,xk=pow(x,k);
	f[0]=f[1]=1;
	for(int i=2;i<=len+1;++i){
		f[i]=1ll*(x+1)*f[i-1]%mod;
		if(i-k-1>=0)f[i]=(f[i]-1ll*xk*f[i-k-1]%mod+mod)%mod;
	}
	return f[len+1];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	n=gi(),k=gi();
	for(int i=1;i<=n-k+1;++i)a[i]=gi();
	int ans=1,len;
	for(int i=1,j;i<=n-k+1;i=j+1){
		j=i;
		while(a[j+1]==a[i])++j;
		len=j-i+k;
		if(i!=1&&a[i-1]>a[i])len-=k;
		if(j!=n-k+1&&a[j+1]>a[i])len-=k;
		if(len>0)ans=1ll*ans*solve(a[i],len)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：i207M (赞：7)

远程orz ywy超强的看不懂的做法。

唔，看了题解之后感觉做法非常巧妙，直观，讨论的情况非常少。

注意到我们要把相同的一段一起考虑，对于不同的一段，我们可以直接确定一个点的值。

我们找到极长的，$c[i]=c[j]$的段，那么这个区间的初始长度是$j+k-i$。然后考虑左右相邻的区间，以i-1为例，若$c[i-1]>c[i]$，那么可知$a[i+k-1]=c[i]$，同时$c[i...i+k-1]$的要求都满足了，相当于我们考虑的实际区间的长度缩短了k；右边同理。事实上，这部分的方案数会在$c[i-1]$那一段被考虑到。

接下来是如何计算$s(len,v)$表示长度为len的区间，每K个的最小值都=v的方案数。

我们设$f[i]$表示之前都满足条件，且$a[i]=v$的方案数。我们可以枚举前一个=v的位置来计算答案。有两种列递推式的方法，一种是暴力错位相减；一种是：

$f[i]=(p+1)f[i-1]-p^kf[i-k-1],p=10^9-x$

前边是i-1随便选的方案。考虑不合法的方案，一定是$[i-k,i-1]$填的都$>v$，减去即可。

最后的方案数为$f[len+1]$，相当于我们强制最后多出来的位置填v。

```cpp
#define N 100005
int n,K;
int f[N];
int calc(int len,int v)
{
	int x=1000000000-v,xk=qpow(x,K);
	f[0]=f[1]=1;
	for(ri i=2; i<=len+1; ++i)
	{
		f[i]=mul(f[i-1],x+1);
		if(i-K-1>=0) dec(f[i],mul(f[i-K-1],xk));
	}
	return f[len+1];
}
int c[N];
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("ot.out","w",stdout);
#endif
	in(n,K);
	for(ri i=1; i<=n-K+1; ++i) in(c[i]);
	LL ans=1;
	for(ri i=1,j; i<=n-K+1; i=j+1)
	{
		j=i;
		while(c[j+1]==c[i]) ++j;
		int len=j+K-i;
		if(i>1&&c[i-1]>c[i]) len-=K;
		if(j<n-K+1&&c[j+1]>c[j]) len-=K;
		if(len>0) ans=mul(ans,calc(len,c[i]));
	}
	out(ans);
	return 0;
}
```


---

## 作者：PhantasmDragon (赞：4)

这道题好神仙啊...
简要题意:给你一个长度为 $n$ 的数列 $a$ 的 $n-k+1$ 个长度为 $k$ 的子区间的最小值 $c_i$, 即 $c_x=\min_{i=x}^{i\leq x+k-1}
a_i$, 求有几种满足给出 $c$ 序列的 $a$ 序列.

拿到这道题不会做,咋办? 先从简单的情况来考虑. 
加入给出的 $c$ 序列中每个 $c$ 都相等,那么显然可以用一个dp去做.

既然每个数都为 $c$ , 那么 $a$ 序列中的每个值肯定也都是 $\geq c$ 的.

设 $>c$ 的数的个数为 $x$, 那么有 $x=10^9-c$.

原问题就转化为了在数列上填数,每连续的 $k$ 格中必须有一个是 $c$ 的方案数.

定义状态 $f_i$ 为序列长度为 $i$ ,第 $i$ 个数必须刚好等于 $c$ 的合法方案数,那么我们有:
$$f_i=\sum_{j=1}^{j\leq k}x^{j-1}*f_{i-j}$$
$j$ 即为枚举当前的 $c$ 与上一次出现的 $c$ 的距离.$j\leq k$ 是因为如果距离超过 $k$ 格,那么就会有一段长度为 $k$ 的区间的最小值不等于 $c$ .

$x^{j-1}$ 即中间空出来的 $j$ 个格子不能刚好填 $c$ 的总填法数.

这样是 $O(nk)$, 经过观察,可以发现这个计算式子长得很像一个等比数列. 那可以进行一些骚操作:
$$x*f_i=\sum_{j=1}^{j\leq k}x^j*f_{i-j}$$
$$f_{i+1}=\sum_{j=1}^{j\leq k}x^j*f_{i-j+1}$$
容易发现,这两个和式中有很多重复的东西,把他们相减抵消掉,就可以得到:
$$f_{i+1}-x*f_i=f_i-x^k*f_{i-k}$$
$$f_{i+1}=(x+1)*f_i-x^k*f_{i-k}$$
好的,现在我们有一个 $O(n)$ 的计算方法了.考虑如何推广到原问题.

对于 $c$ 序列中一段连续一样的数字,我们可以把他们合并在一起.
考虑这样的一个连续段 $c_i=c_i+1=\dots=c_{len}$, 假设 $c_{i-1}>c_i$, 那么就可以有:
$$\min(a_{i-1},a_i,a_{i+1},\dots,a_{i+k-2})=c_{i-1}$$
$$\min(a_i,a_{i+1},a_{i+2},\dots,a_{i+k-1})=c_i$$
可以发现,在多了 $a_{i+k-1}$ 这个数之后,最小值从 $c_{i-1}$ 变为了 $c_i$, 而 $c_{i-1}>c_i$, 所以可以得到 $a_{i+k-1}=c$. 而 $[i,i+k-2]$ 这个区间里的数因为有了 $a_{i+k-1}=c$, 所以并不用去考虑 $c_i$ 这个限制,只需要考虑之前的 $c_{i-1}$ 的限制就好了.

这样,我们相当于把这个长度为 $len$.  的序列的前 $k$ 个数给挖掉了.(前 $k-1$ 个会在之前考虑, 第 $k$ 个已经确定)

那么对于 $c_{len}<c_{len+1}$ 的情况也是这样的,相当于从末尾挖掉 $k$ 个数字. 

挖掉这些数字之后,每一段相对就是独立的了. 那么用上面的dp算出答案,简单相乘即可.

----------
贴上代码(参考了xzz大佬的写法)
```
#include<cstdio>
#include<cstdlib>
#define mod 1000000007
#define maxn 200005
#define LIM 1000000000
using namespace std;
int add(int x,int y){x+=y;return x>=mod?x-mod:x;}
int sub(int x,int y){x-=y;return x<0?x+mod:x;} 
int mul(int x,int y){return 1ll*x*y%mod;}
int ksm(int a,int b)
{
	int s=1;
	for(;b;a=mul(a,a),b>>=1)
		if(b&1) s=mul(s,a);
	return s;
}
int f[maxn],a[maxn],n,k;
int Solve(int len,int v)
{
	f[0]=1,f[1]=1; int pw=ksm(LIM-v,k);
	for(int i=2;i<=len+1;i++)
	{
		f[i]=mul(LIM-v+1,f[i-1]);
		if(i-k-1>=0) f[i]=sub(f[i],mul(pw,f[i-k-1]));
	}
	return f[len+1];
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n-k+1;i++) scanf("%d",&a[i]);
	int ans=1;
	for(int i=1,j=1;i<=n-k+1;i=j+1)
	{
		for(j=i;a[i]==a[j]&&j<=n-k+1;j++);
		j--; int len=j-i+k;
		if(i>1&&a[i-1]>a[i]) len-=k;
		if(j<n-k+1&&a[j+1]>a[j]) len-=k;
		if(len>0) ans=mul(ans,Solve(len,a[i])); 
	}
	printf("%d\n",ans);
}
```

---

## 作者：Kubic (赞：3)

一道有意思的题。

如果所有 $c_i$ 都相同，可以使用 dp 简单求解。于是我们就可以想到把连续的相同 $c_i$ 所代表的区间看作一整段处理。设第 $i$ 段的 $c$ 值为 $b_i$，第 $i$ 段在 $c$ 数组中代表的区间为为 $[L_i,R_i]$。那么第 $i$ 段所控制的 $a$ 数组中的区间为 $[L_i,R_i+k)$。此时两段之间可能会有公共部分，直接做肯定是不对的。

考虑如何解决这个问题。

显然如果 $c_i<c_{i+1}$ 那么 $a_i=c_i$，同理如果 $c_i>c_{i+1}$ 那么 $a_{i+k}=c_i$。

考虑相邻的两段，不妨设 $b_i<b_{i+1}$。显然这两段的公共部分为 $[R_i+1,R_i+k)$，并且 $a_{R_i}=b_i$。

$b_i$ 的限制条件：

- $\forall i\in[R_i+1,R_i+k),a_i\ge b_i$。

$b_{i+1}$ 的限制条件：

- $\forall i\in[R_i+1,R_i+k],a_i\ge b_{i+1}$。

- $\exists i\in[R_i+1,R_i+k],a_i=b_{i+1}$

由于 $b_i<b_{i+1}$，对于 $[R_i+1,R_i+k)$ 这段区间来说，**$b_{i+1}$ 所赋予的限制条件严格强于 $b_i$ 所赋予的限制条件**。于是我们可以只在第 $i+1$ 段保留 $[R_i+1,R_i+k)$！

对于 $b_i>b_{i+1}$ 的情况同理。

经过这样的操作之后 $[1,n]$ 中每一个位置会被唯一一个段覆盖。对于每一段进行 dp，并把答案乘起来即可。

注意因为此时有一些位置被固定了，所以某些段的长度可能会减少 $1$。

时间复杂度 $O(n)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define MOD 1000000007
const int lim=1e9;
int n,m,ans=1,a[N],b[N],cnt[N],pw[N],dp[N];
int slv(int n,int w)
{
	pw[0]=dp[0]=1;
	for(int i=1;i<=n;++i) pw[i]=1ll*pw[i-1]*w%MOD;
	for(int i=1,t=1;i<=n+1;++i)
	{
		if(i>m) t=(t-1ll*dp[i-m-1]*pw[m])%MOD;
		dp[i]=t;t=(1ll*t*w+dp[i])%MOD;
	}return dp[n+1];
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1,x;i<=n-m+1;++i)
	{
		scanf("%d",&a[i]);
		if(a[i]!=a[i-1]) b[++b[0]]=a[i],cnt[b[0]]=0;
		++cnt[b[0]];
	}cnt[b[0]]+=m-1;
	for(int i=1;i<b[0];++i) if(b[i]<b[i+1]) --cnt[i];
		else cnt[i]+=m-1,cnt[i+1]-=m;
	for(int i=1;i<=b[0];++i) if(cnt[i]>0)
		ans=1ll*ans*slv(cnt[i],lim-b[i])%MOD;
	printf("%d\n",(ans+MOD)%MOD);return 0;
}
```

---

## 作者：___OccDreamer___ (赞：2)

### $\text{Solution}$

提供一个 $O(n\log n)$，但是推广性更强的做法。

滑动窗口的限制相当于 $\forall i\in [1,n-k+1],\min\limits_{j=i}^{i+k-1} a_x=c_i$ 且 $\forall i\in[1,n], a_i\in[1,10^9]$。

这样本题就转化为了 [[ABC262Ex] Max Limited Sequence](https://www.luogu.com.cn/problem/AT_abc262_h) 的弱化版（因为本题不存在区间包含）。

------------


先通过区间覆盖得到每个点的最严格限制，也就是最大限制。每个限制 $x$ 是独立的，不妨从小到大分别处理。

根据离散化后的坐标，我们可以得到新的区间。

考虑 dp 求解，我们只关心一个位置是 $=x$ 还是 $<x$，并不关心具体数值，设 $f_{i,j}$ 表示前 $i$ 位，上一个填 $x$ 的位置是 $j$ 的方案数。

第 $i$ 位填 $x$：$f_{i,j}\to f_{i+1,i+1}$。

第 $i$ 为不填 $x$：$f_{i,j}\times (10^9-x) \to f_{i+1,j}$。

对于右端点为 $i$ 的区间，如果上一次填 $x$ 的位置 $<l$ 是不合法的：$f_{i,j}=0,j<l$。


发现转移可线段树优化，支持单点修改，区间乘，区间赋值，查询全局和。

### $\text{Code}$
                                  
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define debug cout<<"debug"<<endl;
using namespace std;
const int N=1e5+5;
const int T=N<<2;
const int mod=1e9+7;
const int inf=1e9;
int n,m=inf,k,c[N],tot;
int b1[N];
vector<int> p[N];
int pp[N];
ll ans=1;
struct query {
	int l,r,v;
	bool friend operator < (const query &x,const query &y) {
		if(x.v==y.v) {
			if(x.r==y.r) return x.l>y.l;
			else return x.r<y.r;
		}
		else return x.v<y.v;
	}
}x[N];
vector<query> y[N];
inline int read() {
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=1; ch=getchar();}
	while(isdigit(ch)) {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return f?-x:x;
}
inline void inc(ll &x,int y) {x+=y-mod;x+=(x>>63)&mod;}

struct SGT1 {
	int a[T],tset[T];
	inline void pushset(int rt,int v) {
		tset[rt]=max(tset[rt],v);
		a[rt]=max(a[rt],v);
	}
	inline void pushdown(int rt) {
		if(tset[rt]!=0) {
			pushset(rt<<1,tset[rt]);
			pushset(rt<<1|1,tset[rt]);
			tset[rt]=0;
		}
	}
	inline void sett(int rt,int l,int r,int L,int R,int v) {
		if(L<=l&&R>=r) {
			pushset(rt,v);
			return ;
		}
		pushdown(rt);
		if(L<=mid) sett(rt<<1,l,mid,L,R,v);
		if(R>mid) sett(rt<<1|1,mid+1,r,L,R,v);
		a[rt]=min(a[rt<<1],a[rt<<1|1]);
	}
	inline int ask(int rt,int l,int r,int p) {
		if(l==r) return a[rt];
		pushdown(rt);
		if(p<=mid) return ask(rt<<1,l,mid,p);
		else return ask(rt<<1|1,mid+1,r,p);
	}
}tr1;

struct SGT2 {
	ll sum[T],tmul[T];
	inline void clear(int n) {
		for(int i=1;i<=(n+1)*4;i++) sum[i]=0,tmul[i]=1;
	}
	inline void pushmul(int rt,int v) {
		tmul[rt]=1LL*tmul[rt]*v%mod;
		sum[rt]=1LL*sum[rt]*v%mod;
	}
	inline void pushdown(int rt) {
		if(tmul[rt]!=1) {
			pushmul(rt<<1,tmul[rt]);
			pushmul(rt<<1|1,tmul[rt]);
			tmul[rt]=1;
		}
	}
	inline void mul(int rt,int l,int r,int L,int R,int v) {
		if(L<=l&&R>=r) {
			pushmul(rt,v);
			return ;
		}
		pushdown(rt);
		if(L<=mid) mul(rt<<1,l,mid,L,R,v);
		if(R>mid) mul(rt<<1|1,mid+1,r,L,R,v);
		sum[rt]=(sum[rt<<1]+sum[rt<<1|1])%mod;
	}
	inline void update(int rt,int l,int r,int p,int v) {
		if(l==r) {
			sum[rt]=v;
			return ;
		}
		pushdown(rt);
		if(p<=mid) update(rt<<1,l,mid,p,v);
		else update(rt<<1|1,mid+1,r,p,v);
		sum[rt]=(sum[rt<<1]+sum[rt<<1|1])%mod;
	}
}tr2;

inline ll solve(int t) {
	int siz=p[t].size();
	if(!siz) return 1;
	for(int i=0;i<siz;i++) pp[i]=-1;
	for(int i=0;i<y[t].size();i++) pp[y[t][i].r]=y[t][i].l;
	tr2.clear(siz);
	tr2.update(1,0,siz,0,1);
	for(int i=1;i<=siz;i++) {
		ll f;
		f=tr2.sum[1];
		tr2.mul(1,0,siz,0,i-1,inf-c[t]);
		if(pp[i-1]>=0) tr2.mul(1,0,siz,0,pp[i-1],0);
		tr2.update(1,0,siz,i,f);
	}
	return tr2.sum[1];
}

int main()
{
	n=read(),k=read();
	for(int i=1;i+k-1<=n;i++) {
		x[i].l=i,x[i].r=i+k-1,x[i].v=read();
		c[++tot]=x[i].v;
		tr1.sett(1,1,n,x[i].l,x[i].r,x[i].v);
	}
	sort(c+1,c+tot+1),tot=unique(c+1,c+tot+1)-c-1;
	for(int i=1;i<=n;i++) {
		b1[i]=lower_bound(c+1,c+tot+1,tr1.ask(1,1,n,i))-c;
	}
	for(int i=1;i<=n;i++) p[b1[i]].push_back(i);
	for(int i=1;i+k-1<=n;i++) {
		int z=x[i].v;
		z=lower_bound(c+1,c+tot+1,z)-c;
		x[i].l=lower_bound(p[z].begin(),p[z].end(),x[i].l)-p[z].begin();
		x[i].r=upper_bound(p[z].begin(),p[z].end(),x[i].r)-p[z].begin()-1;
		y[z].push_back(x[i]);
	}
	for(int i=1;i<=tot;i++) {
		if(p[i].size()) ans=ans*solve(i)%mod;
	}
	printf("%lld",ans);
	return 0;
}
                                  
```

---

## 作者：Red_river (赞：0)

### 题目大意
给你 $n$ 和 $m$ 且一共有 $n-m+1$ 组数据。第 $i$ 组数据代表 $ \min\{\sum_{i=i+m-1}^{i}val_{i}\}$ 然后让你求**符合要求**的方案数。
### 题意分析
这时我们可以由它的**性质**，即第 $i$ 组数据代表 $ \min\{\sum_{i=i+m-1}^{i}val_{i}\}$ 来思考，可以发现：

1. **两个相同且相邻的区间的方案数**与他们共同的 $V$ 值有关，即设 $V= \min\{\sum_{i=i+m-1}^{i}val_{i}\}=val_i=val_{i+1}$ 为 $V$ 的值，接着用递推直接求，时间复杂度是 $O(n^2)$ 的,但可以用数学方法变成 $O(n)$ 的时间复杂度。
1. 如果我们发现两个**不相等但相邻的区间**，我们就可以发现这时就可以固定住一个数，而这个数的值则听 $S=\max\{val_{i},val_{i+1}\}$ 接着推出就行了。

具体可参考代码理解。

### CODE
```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define int long long
#define ull unsigned long long
#define ri register int
#define mod 1000000007
#define N 100005
using namespace std;
const int INF=1e9;
int n,m,jk,ans,num,cnt,tot;
int dis[N],vis[N],wis[N],f[N];

void read(int &x){//快读
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9')){
		if(ty=='-') ff=-1;ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x){//快输
	if(x<0){x=-x;putchar('-');}
	if(x>=10) write(x/10);putchar('0'+x%10);
	return;
}

int ksm(int a,int b)
{
	int result=1;
	while(b>0){
		if(b&1) result=result*a%mod;
		a*=a;b>>=1;a%=mod;
	}
	return result%mod;
}
signed main(){
//	freopen("tracking2.in","r",stdin);
//	freopen("tracking2.out","w",stdout);
	read(n);read(m);ans=1;int i1=1,j=1;
	for(int i=1;i<=n-m+1;i++) read(dis[i]);
	while(j<=n-m+1)
	{
		while(dis[i1]==dis[j]&&j<=n-m+1) j++;
		j--;int len=j-i1+m;
		if(i1>1&&dis[i1-1]>dis[i1]) len-=m;
		if(j<n-m+1&&dis[j+1]>dis[j]) len-=m;
		f[0]=f[1]=1;int sum=ksm(INF-dis[i1],m)%mod;
		for(int i=2;i<=len+1;i++)//判断贡献
		{
			f[i]=(INF-dis[i1]+1)%mod*f[i-1]%mod;
			f[i]<0?f[i]+=mod:0;f[i]%=mod;
			if(i-m-1>=0) f[i]=f[i]-sum*f[i-m-1]%mod;
			f[i]<0?f[i]+=mod:0;f[i]%=mod;
		}
		if(len>0) ans=ans*f[len+1]%mod;ans%=mod;
		i1=j+1;j++;
	}
//	for(int i=1;i<=n;i++) wk(f[i]);
	wh(ans);
	return 0;
}
```

---

## 作者：居然有个高手 (赞：0)

啥 P8500 和 P9871 的结合体。

考虑 $[l_1,r_1]$ 和 $[l_2,r_2]$ 的交集，若两个区间的限制最小值相同则无视，反之缩小其中最小值较小的区间，原因显然。发现所有区间长度相等，所以一个区间在缩小后只会形成 $1$ 个有效子区间，并且每个位置只会被一种值覆盖，可以并查集维护。

现在，每两个相交区间的限制最小值必然相同。把所有限制最小值 $v$ 相同的位置一起拿出来处理，并把最小值视为 $1$，权值为 $1$，把其余值视为 $0$，权值为 $10^9-v$，则问题转化为要求每个区间至少有一个 $1$ 的方案的权值和。对于此类问题，可以找上个 $1$ 的位置处理。令 $f_i$ 表示 $i$ 为结尾且 $i$ 填 $1$ 时方案权值和，则 $f_i = \sum_{j=0}^{i-1} f_j \times v^{i-j-1}[\forall [l,r],[l,r] \not \subset  [j+1,i-1] ]$。

容易发现，当 $i$ 不断右移时，满足条件的 $j$ 的区间也在右移。并且上式可以被拆为 $f_i = v^{i} \times \sum_{j=0}^{i-1} \frac{f_j}  {v^{j+1}}[\forall [l,r],[l,r] \not \subset  [j+1,i-1] ]$，所以我们可以分离贡献，维护 $\frac{f_j}  {v^{j+1}}$ 的和即可。把所有区间挂在其右端点处，不断排除非法的 $j$ 并更新贡献，既可在 $O(n \log n)$ 的时间内完成 DP。（复杂度瓶颈在于快速幂）

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,mod=1e9+7;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
inline int ksm(int a,int b){
	int ans = 1;
	while(b){
		if(b&1)ans=1ll*a*ans%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}return ans;
}
int n,k,w[N],p[N],len,cnt,f[N];
struct DSU{
	int fa[N];
	inline int find(int x){
		return x==fa[x]?x:fa[x]=find(fa[x]);
	}
	inline void merge(int x,int y){
		fa[find(x)]=find(y);
	}
	inline void init(){
		for(int i = 1;i<=n;i++)fa[i]=i;
		fa[n+1]=n+1;
	}
}L,R;
struct query{
	int l,r,v;
}q[N];
vector<pair<int,int>>v[N];
vector<int>g;
int main(){
	n=read(),k=read();
	if(k==1){
		printf("1");
		return 0;
	}
	L.init(),R.init();
	for(int i = 1;i<=n-k+1;i++)q[i]={i,i+k-1,read()},p[++len]=q[i].v;
	sort(p+1,p+len+1),len=unique(p+1,p+len+1)-p-1;
	for(int i = 1;i<=n-k+1;i++)q[i].v=lower_bound(p+1,p+len+1,q[i].v)-p,v[q[i].v].push_back({q[i].l,q[i].r});
	cnt=0;
	int ans = 1;
	for(int i = len;i>=1;i--){
		g.clear();
		for(auto[l,r]:v[i]){
			int ql = R.find(l),qr=L.find(r);
			if(ql>qr){
				printf("0");
				return 0;
			}
			if(!w[qr] || w[qr]<ql)w[qr]=ql;
		}
		g.push_back(0);f[0]=1;
		for(auto[l,r]:v[i]){
			for(int j = L.find(r);j>=l;j=L.find(j))L.merge(j,j-1);
			for(int j = R.find(l);j<=r;j=R.find(j))R.merge(j,j+1),g.push_back(j);
		}
		g.push_back(n+1);
		int b = 1e9-p[i];
		int pre = 0,val=ksm(b,mod-2);
		for(int z = 1;z<g.size();z++){
			int j = g[z];
			f[j]=ksm(b,z)*1ll*val%mod;
			val=(val + f[j]*1ll*ksm(ksm(b,z+1),mod-2))%mod;
			if(w[j]){
				while(g[pre]<w[j])val=(val-f[g[pre]]*1ll*ksm(ksm(b,pre+1),mod-2))%mod,pre++;
			}
		}
		ans=1ll*ans*f[n+1]%mod;
	}
	cout<<(ans+mod)%mod;
	return 0;
}

```

---

## 作者：Prean (赞：0)

怎么没有人用我这个神秘做法啊.jpg

最小值看着有点怪，先转化成最大值吧。。。反正没啥区别。。。

考虑把最大值相同的区间和限制为这个最大值的区间都拿出来。然后离散化。问题变为让所有区间都满足最值为 $c$。

考虑 DP。设 $dp[n][k]$ 表示到序列上的第 $n$ 个位置后，上一个 $c$ 在第 $k$ 个位置。

设 $L[n]$ 表示右端点为 $n$ 的区间中，左端点最靠右的那个的左端点。如果没有就为 $0$。

转移：
$$dp[n][k]=[L[n]\leq k]dp[n-1][k]\times(c-1)$$
$$dp[n][n]=\sum_{i=1}^{n-1}dp[n-1][k]$$
可以直接令 $dp[n]$ 继承 $dp[n-1]$，然后动态维护这个有值的区间。每次操作的时候只需要支持全局乘和单点加就行了。

可以通过打标记的方法将复杂度降低至期望 $O(n)$，具体见代码。
```cpp
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
typedef unsigned ui;
typedef __uint128_t LL;
typedef unsigned long long ull;
const ui M=1e5+5,mod=1e9+7;
ui n,k,c[M],V[M],iV[M],cl[M];std::vector<ui>t[M],Q[M];
struct Hash_Table{
	const ui P[20]={
		110881,581551,319477,140869,307759,536729,791159,503851,614693,375127,
		450299,263429,300761,796303,397373,732731,847009,913687,435401,665201
	};
	ui mod;ull B;
	ui cnt,h[1000000];
	struct Node{
		ui V,nx;
	}t[M];
	inline void init(){
		ui id=rand()%20;
		mod=P[id];B=((LL(1)<<64)+mod-1)/mod;
	}
	inline ui Find(const ui&x){
		for(ui E=h[x-mod*ui(LL(B)*x>>64)];E;E=t[E].nx)if(t[E].V==x)return E;return-1;
	}
	inline void Insert(const ui&x){
		ui&head=h[x-mod*ui(LL(B)*x>>64)];t[++cnt]=(Node){x,head};head=cnt;
	}
}Hash;
ui L(1),R(0),q[M];
inline ui max(const ui&a,const ui&b){
	return a>b?a:b;
}
inline ui Solve(const ui&x){
	static ui L[M],q[M],p[M],dp[M],pre1[M],pre2[M];
	const ui&v=V[x]-1,&iv=iV[x],&len=t[x].size();
	for(ui id(1),i=0;i<Q[x].size();++i){
		while(id<len&&t[x][id]<Q[x][i])++id;pre1[i]=id;
	}
	for(ui id(1),i=0;i<Q[x].size();++i){
		while(id<len&&t[x][id]<=Q[x][i]+k-1)++id;pre2[i]=id-1;
	}
	for(ui i=0;i<len;++i)L[i]=q[i]=p[i]=0;
	for(ui i=0;i<Q[x].size();++i)L[pre2[i]]=max(L[pre2[i]],pre1[i]);
	ui l(0),sum(1),mul(1);dp[0]=1;
	for(ui i=1;i<len;++i){
		while(l<L[i-1]){
			while(q[l]--)mul=1ull*mul*v%mod;while(p[l]--)mul=1ull*mul*iv%mod;
			sum=(sum+1ull*(mod-mul)*dp[l++])%mod;
		}
		dp[i]=sum;sum=(1ull*sum*v+dp[i])%mod;++q[L[i-1]];++p[i];
	}
	while(l<L[len-1]){
		while(q[l]--)mul=1ull*mul*v%mod;while(p[l]--)mul=1ull*mul*iv%mod;
		sum=(sum+1ull*(mod-mul)*dp[l++])%mod;
	}
	return sum;
}
inline ui pow(ui a,ui b){
	ui ans(1);for(;b;b>>=1,a=1ull*a*a%mod)if(b&1)ans=1ull*ans*a%mod;return ans;
}
inline void swap(ui&a,ui&b){
	ui c=a;a=b;b=c;
}
inline void getinv(){
	static ui s[M],t[M];const ui&n=Hash.cnt;s[0]=1;
	for(ui i=1;i<=n;++i)t[i]=V[i]-1,s[i]=1ull*s[i-1]*t[i]%mod;s[n]=pow(s[n],mod-2);
	for(ui i=n;i>=1;--i)swap(s[i],s[i-1]),s[i]=1ull*s[i]*s[i-1]%mod,s[i-1]=1ull*s[i-1]*t[i]%mod;
	for(ui i=1;i<=n;++i)iV[i]=s[i];
}
signed main(){
	srand(time(NULL));srand(rand()*rand());
	ui ans(1);
	scanf("%u%u",&n,&k);Hash.init();
	for(ui i=1;i<=n-k+1;++i){
		scanf("%u",c+i);c[i]=1000000000-c[i]+1;
		cl[i]=Hash.Find(c[i]);
		if(!~cl[i])Hash.Insert(c[i]),V[Hash.cnt]=c[i],t[Hash.cnt].push_back(0),cl[i]=Hash.cnt;
		Q[cl[i]].push_back(i);
	}
	for(ui i=1;i<=n;++i){
		if(L<=R&&q[L]+k<=i)++L;
		if(i+k-1<=n){
			while(L<=R&&c[q[R]]>=c[i])--R;q[++R]=i;
		}
		t[cl[q[L]]].push_back(i);
	}
	getinv();
	for(ui i=1;i<=Hash.cnt;++i)ans=1ull*ans*Solve(i)%mod;printf("%u",ans);
}
```

---

## 作者：joe19025 (赞：0)

## Solution

### 切入

先考虑一个简单的问题，如何计算一个长度为n的序列，使得其中长度为K的滑窗内任意一段中的最小值都小与v。把这样的序列成为以v结尾，长度为i的滑窗序列。

先设DP[i]为以v结尾，长度为i的滑窗序列的方案数。
$$
x=MaxNum-v
$$
我们现在枚举在这次v出现之前。上一次v出现的位置，这两次位置中间的部分可以是大于v的任意整数。上一次出现最早只能是i-k否则最小值就不是v了。
$$
DP[i]=DP[i-1]+DP[i-2]\times x+DP[i-3]\times x^2+...DP[i-k]\times x^{k-1}
$$
但这个算法每一次更新都是$O(i)$,求出一个DP[n],需有$O(n^2)$的时间，所以不太可行。我们可以把式子做一个简单的变形，就可以简化为下面的式子，这样转移的复杂度变为常数。求解变为线性。
$$
DP[i]=DP[i-1]+x(DP[i-1]-DP[i-k-1]\times x^{k-1})
$$

### 深化

我们这个问题可以发现这样一个突破口。当我们发现当滑窗向左或向右移动一个单位后，最小值或最大值发生变化，这时我们便可以确定一个值了。

这个道理不难理解，下面用数学说明一下。
$$
a=min(x_{1},x_{2}...x_{k})
$$

$$
b=min(x_{2},x_{3},...x_{k+1})
$$

假设a>b
$$
min(x_{2},x_{3}...x_{k})>=a
$$

$$
min(x_{2},x_{3},...x_{k+1})=b<a<=min(x_{2},x_{3}...x_{k})
$$

$$
x_{k+1}=b
$$

所以我们可以通过一些滑窗值的变化，来确定一些值的变化。

### 大成

那么对于那些不确定的值，该怎么办？其实就用到我们之前在第一部分所需要的内容了。
$$
\{a,..........,b\}
$$
对于确定的a,b,中间打点部分不定的情况，我们使他们满足对应的滑窗即可，而且由于他们滑窗的值相同，否则就会有确定值的存在。所以我们就只需要计算长度为l，滑窗值为v的滑窗序列的方案数。最后通过乘法原理将每一部分乘起来，便得到答案。

### 复杂度O(n)

对于确定位置，O(n)扫一遍便可求解。

而对于中间不确定位置，长度为l的情况，O(l)可以求解。又因为l的和小于等于n，所以O(n)

O(n)+O(n)=O(n)

## Code

```c++
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#define MAXN 100005
#define int long long
using namespace std;

const int MX=1e9;
const int mod=1e9+7;
int add(int a,int b)
{
    return (a+b)%mod;
}
int sub(int a,int b)
{
    return (a-b+mod)%mod;
}
int mul(int a,int b)
{
    return (a*b)%mod;
}

int calc(int val,int K,int len)
{
    int x=MX-val;
    int pow[MAXN],spow[MAXN],dp[MAXN];
    pow[0]=spow[0]=1;
    for(int i=1;i<=K;i++)
    {
        pow[i]=mul(pow[i-1],(x+1));
        spow[i]=mul(spow[i-1],x);
    }
    dp[0]=dp[1]=1;
    for(int i=2;i<=min(K,len);i++)
    {
        dp[i]=pow[i-1];
    }
    if(len<K)
        return pow[len];
    for(int i=K;i<=len;i++)
    {
        dp[i+1]=dp[i];
        dp[i+1]=sub(dp[i+1],mul(dp[i-K],spow[K-1]));
        dp[i+1]=mul(dp[i+1],x);
        dp[i+1]=add(dp[i+1],dp[i]);
    }
    return dp[len+1];
}



pair<int,int>b[MAXN];
int cnt=0,tot=0;
int n,k;
int a[MAXN];

signed main()
{
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n-k+1;i++)
        scanf("%lld",&a[i]);
    int cur=-1;
    for(int i=1;i<=n-k+1;i++)
    {
        if(a[i]==cur)
        {
            cnt++;
        }
        else
        {
            if(cnt)b[++tot]=make_pair(cur,cnt);
            cur=a[i];
            cnt=1;
        }
        
    }
    b[++tot]=make_pair(a[n-k+1],cnt);
    // for(int i=1;i<=tot;i++)
    // {
    //    cout<<b[i].first<<" " <<b[i].second<<endl;
    // }
    int ans=1;
    if(tot==1)
    {
        printf("%lld",calc(b[1].first,k,n));
    }
    else
    {
        for(int i=1;i<=tot;i++)
        {
            int len;
            if(i==1)
            {
                if(b[i].first<b[i+1].first)
                {
                    len=b[i].second-1;
                }
                else
                {
                    len=b[i].second+k-1;
                }
            }
            else if(i==tot)
            {
                if(b[i].first<b[i-1].first)
                {
                    len=b[i].second-1;
                }
                else
                {
                    len=b[i].second+k-1;
                }
            }
            else
            {
                if(b[i].first<b[i+1].first)
                {
                    if(b[i].first<b[i-1].first)
                    {
                        len=max(0ll,b[i].second-k-1);
                    }
                    else
                    {
                        len=b[i].second-1;
                    }
                }
                else
                {
                    if(b[i].first<b[i-1].first)
                    {
                        len=b[i].second-1;
                    }
                    else
                    {
                        len=b[i].second+k-1;
                    }
                }
            }
            //printf("%d\n",len);
            ans=mul(ans,calc(b[i].first,k,len));    
        }
        printf("%lld",ans);
    }
    return 0;
}
```



---

