# Excellent Arrays

## 题目描述

Let's call an integer array $ a_1, a_2, \dots, a_n $ good if $ a_i \neq i $ for each $ i $ .

Let $ F(a) $ be the number of pairs $ (i, j) $ ( $ 1 \le i < j \le n $ ) such that $ a_i + a_j = i + j $ .

Let's say that an array $ a_1, a_2, \dots, a_n $ is excellent if:

- $ a $ is good;
- $ l \le a_i \le r $ for each $ i $ ;
- $ F(a) $ is the maximum possible among all good arrays of size $ n $ .

Given $ n $ , $ l $ and $ r $ , calculate the number of excellent arrays modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, it can be proven that the maximum $ F(a) $ among all good arrays $ a $ is equal to $ 2 $ . The excellent arrays are:

1. $ [2, 1, 2] $ ;
2. $ [0, 3, 2] $ ;
3. $ [2, 3, 2] $ ;
4. $ [3, 0, 1] $ .

## 样例 #1

### 输入

```
4
3 0 3
4 -3 5
42 -33 55
69 -42 146```

### 输出

```
4
10
143922563
698570404```

# 题解

## 作者：ZillionX (赞：10)

> 定义长为 $n$ 的整数序列 $a$ 是好的，当且仅当 $a_i \neq i$。设 $F(a)$ 为满足 $a_i + a_j =i+j$ 的 $(i,j)$ 对数。  
定义长为 $n$ 的整数序列 $a$ 是极好的，当且仅当：$a$ 是好的、$a_i \in [l,r]$、$F(a)$ 在所有长度为 $n$ 的好序列中最大。  
给定 $n,l,r$，求极好序列个数，答案对 $10^9+7$ 取模。  
$n \le 2 \times 10^5, -10^9 \le l \le 1 \le n \le r \le 10^9$，2s。

提供一种非常猛的做法。

注意到 $a_i+a_j=i+j$ 可以化为 $a_i-i = -(a_j-j)$，考虑给题目换一种刻画方式。

设 $x_i=a_i-i$，则原题等价于统计 $x_i=-x_j$ 的对数，限制也变为 $x_i \neq 0,x_i \in [l-i,r-i]$。

我们将题目限制画成图，$x_i$ 的范围很显然就是若干个左端点不断左移的长度相同的区间。$F(a)$ 最大的限制相当于选一些 $x \ge 0$，让一些数取 $-x$，一些数取 $x$，使 $F(a)=\sum_x (\sum [x_i=-x]) \times (\sum [x_i=x])$。（下图黄色框框住的即可以取到 $x$ 或 $-x$ 的 $x_i$）。

![](https://cdn.luogu.com.cn/upload/image_hosting/ifmfgulj.png)

如果就这样啥性质没有的话，构造出 $x$ 序列是很难的。

然而，我们注意到，题目保证了 $l \le 1 \le n \le r$。因此，很容易想到，为了让乘积对答案的贡献尽量大，最终的 $x$ 只会有 $1$ 个，极好的序列对应的 $x$ 序列必然是 $\lfloor \frac{n}{2} \rfloor$ 个数取 $-x$、$\lceil \frac{n}{2} \rceil$ 个数取 $x$，或者反过来。

那么现在我们就有了一个暴力做法：枚举 $x$，然后暴力计算只能取 $x$ 的 $x_i$ 的个数 $s_1$、可以同时取 $x,-x$ 的 $x_i$ 的个数 $s_2$，只能取 $-x$ 的 $x_i$ 的个数 $s_3$（注意不能出现两个都不能取的 $x_i$）。  
若 $n$ 为奇数，则答案加上 ${s_2 \choose \lceil \frac{n}{2} \rceil-s_1}+ {s_2 \choose \lfloor \frac{n}{2} \rfloor-s_1}$，否则加上 ${s_2 \choose \frac{n}{2}-s_1}$。

现在我们考虑怎么优化这一过程。首先这样需要枚举 $x$ 的个数是 $10^9$ 级别的，事实上我们注意到答案是一个分段函数的形式，中间有一大段相等的平台。而断点显然是 $\mathcal O(n)$ 级别的，它们与 $l-i,r-i$ 的距离都不超过 $1$，为了避免分类讨论，全当作断点就好了。

现在我们枚举 $x$ 的复杂度已经变为 $\mathcal O(n)$ 了。唯一的瓶颈就是暴力计算 $s_1,s_2,s_3$ 的过程。容易想到它们都可以通过数学推导得到，这里写出 $s_1$ 的计算方法，$s_2,s_3$ 同理。

有

$$s_1=\sum _{i=1}^n [x \in [l-i,r-i]] [ -x \in (- \infty,l-i) \cup (r-i,\infty)]$$

相当于统计 $1 \le i \le n, l-x \le i \le r-x, i<l+x,i>r+x$ 的 $i$ 的个数，这就是个简单的区间求并，实现可以参考代码。

时间复杂度 $\mathcal O(n \log n)$，带 $\log$ 是因为给断点排了个序。

```cpp
const int N=3e6+5,mo=1e9+7;
int T,n,l,r,tn,o[N],fc[N],ifc[N];
int qpow(int x,int y=mo-2){
	if(x==1)return 1;
	int mu=1;
	for(;y;y>>=1,x=x*x%mo)if(y&1)mu=mu*x%mo;
	return mu;
}
void init(int n){
	fc[0]=1;for(int i=1;i<=n;i++)fc[i]=fc[i-1]*i%mo;
	ifc[n]=qpow(fc[n]);for(int i=n-1;i>=0;i--)ifc[i]=ifc[i+1]*(i+1)%mo;
}
int C(int n,int m){
	if(n<m||n<0||m<0)return 0;
	return fc[n]*ifc[m]%mo*ifc[n-m]%mo;
}
void slv(){
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++){
		o[++tn]=abs(l-i),o[++tn]=abs(i-l),o[++tn]=abs(r-i+1),o[++tn]=abs(i-r-1);
		o[++tn]=abs(l-i-1),o[++tn]=abs(i-l-1),o[++tn]=abs(r-i+1-1),o[++tn]=abs(i-r-1-1);
		o[++tn]=abs(l-i+1),o[++tn]=abs(i-l+1),o[++tn]=abs(r-i+1+1),o[++tn]=abs(i-r-1+1);
	}
	o[++tn]=0;
	for(int i=1;i<=tn;i++)o[i]=-o[i];
	sort(o+1,o+tn+1);
	tn=unq(o+1,o+tn+1)-o-1;
	int sm=0;
	for(int i=1;i<tn;i++){
		int x=o[i];
		int nl=max(1ll,l-x),nr=min(n,r-x);
		int s1;
		if(nl>nr)s1=0;
		else{
			int kl=l+x-1,kr=r+x+1;
			if(kl>nr)kl=nr;
			if(kr<nl)kr=nl;
			if(kl>=kr)s1=nr-nl+1;
			else s1=max(0ll,kl-nl+1)+max(0ll,nr-kr+1);
		}
		int s2=max(0ll,min(min(r-x,r+x),n)-max(max(l-x,l+x),1ll)+1);
		int s3;
		nl=max(1ll,l+x),nr=min(n,r+x);
		if(nl>nr)s3=0;
		else{
			int kl=l-x-1,kr=r-x+1;
			if(kl>nr)kl=nr;
			if(kr<nl)kr=nl;
			if(kl>=kr)s3=nr-nl+1;
			else s3=max(0ll,kl-nl+1)+max(0ll,nr-kr+1);
		}
		if(s1+s2+s3!=n)continue;
		int as=0;
		if(n&1)mad(as,mpl(C(s2,n/2+1-s1),C(s2,n/2-s1)));
		else mad(as,C(s2,n/2-s1));
		mad(sm,as*(o[i+1]-o[i])%mo);
	}
	cout<<sm<<endl;
}
void mms(){
	for(int i=1;i<=n*12+2;i++)o[i]=0;
	tn=0;
}
signed main(){
	init(N-5);
	cin>>T;
	while(T--)slv(),mms();
	return 0;
}
```


---

## 作者：dztlb (赞：8)

提供一个与官方题解不同的，思路简单不用推结论，~~但是码量更大~~。

首先一个 Good Array 是 $a_i=i$ 序列的每一位加一个偏移量（可正可负）构成的。

考虑限制最大的第三个条件，一个 Excellent Array 必须是相同长度的 Good Array 中满足 $a_i+a_j=i+j$ 对数最多的。

对于一对 $(i,j)$ 不妨设 $a_i=i+x$ 那么 $a_j=j-x$ 则所有偏移量互为相反数都可组成一对满足条件的 $(i,j)$。

构造 $(i,j)$ 对数最多的 Excellent Array 的方案就非常显然了：将所有 $|x|$ 设为相同值，同时满足 $x>0$ 与 $x<0$ 的数各占一半（注意 $n$ 为奇数时要么正的为 $n/2+1$ 要么为 $n/2$ 有两种不同情况）。

我们可以将 $a_i$ 预设为 $i$，再预处理出每一个数在 $l,r$ 限制下的最大正偏移量与最小负偏移量。

满足一元素某一偏移量能够取到 $x_i$ 即满足 $|x|\le|x_i|$，考虑枚举偏移量的绝对值 $|x|$，那么对于一个确定的 $|x|$，设只满足负偏移量的元素数量为 $mi$，只满足正偏移量的元素数量为 $ad$，正负偏移量都满足的元素数量为 $ok$，我们得到：
```cpp
if(mi+ad+ok==n&&mi+ok>=n/2&&ad+ok>=n/2){//满足能够构造出Excellent Array条件
	if(n&1){
		if(mi+ok>=n/2+1) ans+=C(ok,n/2+1-mi);
		if(ad+ok>=n/2+1) ans+=C(ok,n/2-mi);
   	}else ans+=C(ok,n/2-mi);
}//C(n,m)为组合数
```
感性理解一下：所有元素偏移量非负即正，对于只满足了正或负的显然只有一种情况，而 $ok$ 可以通配，那么在 $ok$ 中选定负偏移量还差的，另外一部分自然补给正偏移量。具体细节按照 $n$ 的奇偶性讨论。

$|x|$ 的值域很大，每个枚举必然不能通过，但是注意到在 $mi$，$ad$，$ok$ 不更新时每次算出的答案是一样的，我们可以分段计算贡献，只要选择每个数的偏移量作为标记点，两个标记点中间的段 $mi$，$ad$，$ok$ 始终不变，计算答案相同，都可以一起处理。标记点的数量与 $n$ 同阶，每一段预处理阶乘逆元后可以 $O(1)$ 计算。

```cpp
#define ll long long
const int maxn=200005,mod=1e9+7;
int t,n,L,R,cnt;
long long co[maxn],op[maxn];
ll qpow(ll b,ll k) {
    if (k==0) return 1;
    long long ans=1;
    while(k){
        if (k&1) ans=ans*b%mod;
        k>>=1,b=(b*b)%mod;
    }
    return ans;
}
void init(){
	co[0]=1,op[0]=1;
	for(int i=1;i<=200000;++i){
		co[i]=(co[i-1]*i)%mod;
		op[i]=(op[i-1]*qpow(i,mod-2))%mod;//阶乘逆元 
	}
}
struct node{
	int id,x,ty;
}p[maxn<<1];
bool cmp(node a,node b){
	return a.x<b.x;
}
bool fl[maxn][2];//分别记录正负偏移量限制是否满足
int mi,ok,ad,bon;
void insert(int num){//更新单个标记
	if(p[num].ty==0){//L
		fl[p[num].id][0]=1;
		if(fl[p[num].id][1]) ++ok,--ad;
		else ++mi;
	}else{//R
		fl[p[num].id][1]=1;
		if(fl[p[num].id][0]) ++ok,--mi;
		else ++ad;
	}
}
void In(int &now){//同时将一组|x|相同的标记更新
	while(p[now].x==p[now-1].x)
		insert(now),--now;
	insert(now);
}
long long C(int a,int b){
	return ((co[a]*op[a-b])%mod)*op[b]%mod;
}
long long cal(int l,int r){//统计l<=|x|<=r区间的答案
	long long len=r-l+1,ans=0;
	if(n&1){
		if(mi+ok>=n/2+1) ans+=C(ok,n/2+1-mi);
		if(ad+ok>=n/2+1) ans+=C(ok,n/2-mi);
   	}else ans+=C(ok,n/2-mi);
	ans%=mod;
	return (ans*len)%mod;
}
int main(){
	init();
	t=read();
	while(t--){
		cnt=0;
		memset(fl,0,sizeof(fl));
		mi=0,ad=0,ok=0;
		n=read(),L=read(),R=read();
		long long ans=0;
		for(int i=1;i<=n;++i){
			int l=i-L,r=R-i;//如果偏移量为0则没有意义（不满足good array）
			if(l!=0)p[++cnt].id=i,p[cnt].x=l,p[cnt].ty=0;
			if(r!=0)p[++cnt].id=i,p[cnt].x=r,p[cnt].ty=1;
		}
		p[++cnt].id=0,p[cnt].x=0,p[cnt].ty=2;//插入一个末端，便于统计
		sort(p+1,p+1+cnt,cmp);
		int now=cnt;
		while(now>1){
			In(now);
			if(mi+ad+ok==n&&mi+ok>=n/2&&ad+ok>=n/2){
				int l=p[now-1].x+1,r=p[now].x;
				ans=(ans+cal(l,r))%mod;
			}
			--now;
		}
		printf("%lld\n",(ans+mod)%mod);
	}
	return 0;
}


---

## 作者：白鲟 (赞：3)

## 前言
考场没调完边界。

## 题目分析
题目描述不允许 $i=a_i$，于是从 $i=a_i$ 与 $i\not= a_i$ 的差异思考。可以发现若 $a_1'-a_1=x$，那么其余的 $|a_i'-a_i|=x$，且差为正负的各占一半。这是由于若 $a_i'+a_j'=i+j$，则 $a_i'-a_i=a_j-a_j'$，于是最优的情况下必定有所有的偏移量 $x$ 绝对值均相等。考虑偏移量为正的共 $k$ 个，则总对数为 $\dfrac{(n-k)k}{2}$，取 $k=\dfrac{n}{2}$ 最大。$n$ 为奇数情况下，则上下取整均可最优。

先考虑偶数情况。由于 $a_i'$ 有界，$a_i$ 不一定能够任意偏移。考虑从大到小枚举偏移量绝对值，初始时 $a_i$ 正负偏移均可，固定 $\dfrac{n}{2}$ 个正偏移，则方案数为 $C_n^{\frac{n}{2}}$。该情况对每个偏移量方案数相同，可 $\operatorname{O}(1)$ 计算。

偏移量达到一定大小后，一侧的偏移会受限制，此时偏移量每增加 $1$，只能向一侧偏移的元素也增加 $1$，故方案数为 $C_{n-i}^{\frac{n}{2}-i}$，其中 $i$ 为相比上一情况增加的偏移量。直到所有的元素均只能向一侧偏移，枚举结束。

有时在上一种情况的基础上，偏移量再增加到一定大小时，正负的偏移均会受限，每增加 $1$ 偏移量将增加 $2$ 固定元，故方案数为 $C_{n-i-2j}^{\frac{n}{2}-i-j}$，其中 $i$ 为上一情况的总偏移量，$j$ 为按此情况的偏移量。

各情况的分界可由 $[1,n]$ 与 $[l,r]$ 的关系求得。

在奇数的情况下，$\dfrac{n}{2}$ 上下取整均可作为正偏移原始量，故每一偏移量的方案数均为两情况之和。
## 代码
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
#define int long long
const int maxn=2e5,mod=1e9+7;
int T,n,l,r,ans,factorial[maxn+1],inv[maxn+1];
int power(int base,int exponent)
{
	int res=1;
	while(exponent)
	{
		if(exponent&1)
			res=res*base%mod;
		base=base*base%mod;
		exponent>>=1;
	}
	return res;
}
int C(int x,int y)
{
	if(y<0||x<y)
		return 0;
	return factorial[x]*inv[y]%mod*inv[x-y]%mod;
}
signed main()
{
	scanf("%lld",&T);
	factorial[0]=1;
	for(int i=1;i<=maxn;++i)
		factorial[i]=factorial[i-1]*i%mod;
	inv[maxn]=power(factorial[maxn],mod-2);
	for(int i=maxn-1;~i;--i)
		inv[i]=inv[i+1]*(i+1)%mod;bool check=(T==1000);
	while(T--)
	{
		scanf("%lld%lld%lld",&n,&l,&r);
		ans=0;
		int any=min(1-l,r-n),pos=max(1-l,r-n)-any;
		if(n&1)
			ans=any*(C(n,n>>1)+C(n,(n+1)>>1))%mod;
		else ans=any*C(n,n>>1)%mod;
		if(n&1)
		{
			for(int i=1;i<=pos&&((n+1)>>1)-i>=0;++i)
				ans=((ans+C(n-i,(n>>1)-i))%mod+C(n-i,((n+1)>>1)-i))%mod;
			for(int i=1;((n+1)>>1)-pos-i>=0;++i)
				ans=((ans+C(n-(i<<1)-pos,(n>>1)-pos-i))%mod+C(n-(i<<1)-pos,((n+1)>>1)-pos-i))%mod;
		}
		else
		{
			for(int i=1;i<=pos&&(n>>1)-i>=0;++i)
				ans=(ans+C(n-i,(n>>1)-i))%mod;
			for(int i=1;(n>>1)-pos-i>=0;++i)
				ans=(ans+C(n-(i<<1)-pos,(n>>1)-pos-i))%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
//n/2 add x,n-n/2 minus x
```

---

## 作者：CDFLS_mao_zx (赞：3)

## CF1550D:

~~格式要求好严啊，最后一次专门改格式了。~~

题意省略。

先观察，显然这道题应该从 $F(x)$ 入手，我们考虑构造一个数列，不管 $[l,r]$ 的限制的情况下，$F(x)$ 的最大值。

显然应该是奇数位置 $i+d$，偶数位置 $i-d$，其它任何情况都不可能比这种情况更大。因为，设大于 $i$ 的有 $x$ 个，小于 $i$ 的有 $y$ 个，然后答案上界就是 $x * y$，又有限制 $x + y = n$，显然最大值在 $x = \lfloor \dfrac{n}{2}\rfloor$ 时取到。

而且发现，如果想取到最大，那么每一个数 $a_i$ 都必须是 $i+d$ 的形式，并且 $i+d$ 或 $i-d$ 的个数 $x$ 等于 $\lfloor \dfrac{n}{2}\rfloor$。证明是类似的。

 现在考虑加入 $[l,r]$ 的限制。感性理解一下，当 $d$ 很小的时候，其实每一个数无论怎么取，都是可以的，只要最后的个数一样就可以了。所以，排除怎么选都可以的情况，然后 $[l,r]$ 会造成限制的情况会比较少。

我们先推一下式子，然后画几张。

可以选择 $i+d$ 的条件：$i+d\leq r$，即 $1\leq i\leq r-d$

可以选择 $i-d$ 的条件：$i+d\leq r$，即 $d+l\leq i\leq n$

一定不合法的条件：
$$
r-d < 1 \ | \ | \ n<d+l
$$
也就是：
$$
\max(r-1,n-l) < d 
$$


其实边界应该更严格一些，但是为了方便边界不需要那么严格。

我们考虑会不能任意选，但又合法的方案。

可以画出这样一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/g9b36l8f.png)

红色框框里的，是可以选择 $i+d$ 的，绿色框框里的是可以选择 $i-d$ 的，每次 $d$ 的移动，都会让方框的边界移动，从全部不在里面移动到全部包含的次数一定不会超过 $O(n)$

所以可以放心大胆的枚举 $d$ 统计答案，统计答案的时候考虑选择可选区间较大的那一个，另一个不能选的它一定要选，选完之后还要选一些重合的地方补上去，第二个过程直接组合数。

然后是两个都能选的部分，统计出又多少个 $d$ ，然后组合一下。

简单证明一下这样是不重不漏的。

第一，每一次枚举 $d$ 的时候，统计都是不重不漏的。~~你在质疑组合数？？~~

然后它显然是不漏的。

至于不重，分两种情况讨论。

奇数的时候显然是不重的，因为它们的和每一次枚举 $d$ 的时候都是不一样的。

偶数的情况，假设出现重复，那么必然是一个的 $+d$ 和另一个的 $-d$ 给匹配上了，一个个追溯下去，最后发现一定有一个匹配不上，矛盾。

所以它是不重不漏的。

### 参考代码：

```c++
#include<bits/stdc++.h>
#define y1 y3647
#define earse erase
#define INF 1000000000
#define LL long long
using namespace std;
inline void read(int &x)
{
	x=0;int f=1;
	char ch=getchar();
	while(ch!=45&&(ch>'9'||ch<'0'))ch=getchar();
	if(ch==45){f=-1,ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
void cmin(int &a,int b)
{
	a=min(a,b);
}
void cmax(int &a,int b)
{
	a=max(a,b);
}
/*



*/
const int N=1e6+10,mod=1e9+7;
int i,j,k,n,s,t,m;
int f[N]={1},inv[N]={1};
int quick(int a,int s)
{
	int ret=1;
	while(s)
	{
		if(s&1)
		ret=1ll*ret*a%mod;
		a=1ll*a*a%mod;
		s>>=1;
	}
	return ret;
}
int C(int n,int m)
{
	if(m<0)return 0;
	if(m>n)return 0;
	return 1ll*f[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main()
{
	for(i=1;i<N;i++)
	f[i]=1ll*i*f[i-1]%mod,inv[i]=quick(f[i],mod-2);
	read(t);
	while(t--) 
	{
		int l,r,ans=0,d;
		read(n),read(l),read(r);
		for(d=min(r-1,n-l);d>=1;d--)
		{
			int c1=min(max(0,r-d),n),c2=min(max(0,n-d-l+1),n);
			if(c1==n&&c2==n)break;
			if(c2>c1)swap(c1,c2);
			if(n%2)
			{
				ans+=C(c1+c2-n,n/2-(n-c1));
				ans%=mod;
				ans+=C(c1+c2-n,n/2+1-(n-c1));
			}
			else
			{
				ans+=C(c1+c2-n,n/2-(n-c1));
			}
			ans%=mod;
		}
		if(n%2)
		ans+=2ll*d*C(n,n/2)%mod;
		else
		ans+=1ll*d*C(n,n/2)%mod;
		
		ans%=mod;
		printf("%d\n",ans);
	}
	return 0;
}

```



## 

---

## 作者：MatrixGroup (赞：2)

## 题意

有多少个值域 $[l,r]$（$l\le 1,n\le r$） 的长度为 $n$ 的数组 $a$，使得 $\forall i:a_i\neq i$，而且其 $a_i+a_j=i+j$ 的对数在所有这样的数组中最大。

多测。$\sum n\le2\times10^5$。

## 题解

不难发现最大的对数一定在有 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 个 $a_i=a_i+k$，$\left\lceil\dfrac{n}{2}\right\rceil$ 个 $a_i=a_i-k$ （如果 $n$ 为奇数，可以交换个数）时取到。

证明：把 $a_i+a_j=i+j$ 连边，这一定是二分图（显然如果有奇环一定不符合条件），即证。

考虑枚举 $k$ 计算符合条件的数组个数求和，复杂度爆炸。发现一开始一段的值一直是相等的，接下来有 $O(n)$ 个值，接下来都是 $0$。于是就可以 $O(n)$ 地求了。

---

## 作者：LJ07 (赞：2)

又是题号打错找到的一道水题。

$a_i+a_j=i+j$ 稍作变形 $a_i-i=j-a_j$。

然后发现按照 $a_i-i$ 分类，那么答案就是 $\sum (\sum [a_i-i=v])\times (\sum [i-a_i=v])~~(v\ge 1)$。 

答案最大时，$|a_i-i|$ 为同一个值。且为 $+$ 和 $-$ 的个数为 $\lfloor \frac{n}{2}\rfloor$ 和 $\lceil \frac{n}{2}\rceil$。（为了方便描述， $+$ 和 $-$ 表示 $a_i-i$ 的符号）。

正确性显然（若 $|a_i-i|=1$ 时一定成立）。

暴力：枚举 $|a_i-i|$ 求解，存在三类数：只能 $+$；只能 $-$；$+$ 和 $-$ 皆可。如果存在 $+$ 和 $-$ 都不行的位置那么对答案的贡献为 $0$。组合一下就可以求出对答案的贡献。

如何优化？发现对于多个连续 $|a_i-i|$ 对答案的贡献是相同，而这样出现贡献突变的拐点个数只有 $2\times n$ 个。拐点为 $\{ i-l+1\}$ 和 $\{ r+1-i\}$。直接类似归并求解即可。求解时注意一下 $n$ 为奇数的情况。

时间复杂度为 $O(\sum n)$。细节看代码。

```cpp
#include <bits/stdc++.h>
#define GC c=getchar()
#define IG isdigit(c)
template<class T=int>T frd(T x=0,char GC,bool f=1)
{
	for(;!IG;GC)f=c!='-';for(;IG;GC)x=x*10+(c^48);return f?x:-x;
}
using namespace std;
const int N(2e5+5),P(1e9+7);
int t,n,l,r,_n,a[N+5],ans,fac[N+5],ifac[N+5];
inline int fpw(int a,int b)
{
	int t(1);
	for(;b;b>>=1,a=1ll*a*a%P) if(b&1) t=1ll*t*a%P;
	return t;
}
inline int C(int a,int b)
{
	return (b<0||a<b)?0:1ll*fac[a]*ifac[b]%P*ifac[a-b]%P;
}
signed main()
{
	fac[0]=1;
	for(int i(1);i<=N;++i) fac[i]=1ll*fac[i-1]*i%P;
	ifac[N]=fpw(fac[N],P-2);
	for(int i(N);i;--i) ifac[i-1]=1ll*ifac[i]*i%P;
	for(t=frd();t--;)
	{
		n=frd(),l=frd()-1,r=frd()+1,_n=n>>1;
		ans=1ll*(min(1-l,r-n)-1)*(C(n,_n)+((n&1)?(C(n,_n+1)):0))%P;
		for(int i(1),j(n);i<=j;)
		{
			int I(i-l),J(r-j),T(j-i);
			if(I<J) ans=(1ll*(min(i-l+1,r-j)-I)*(C(T,_n-i)+((n&1)?C(T,_n+1-i):0))%P+ans)%P,++i;
			else ans=(1ll*(min(i-l,r-j+1)-J)*(C(T,_n-i+1)+((n&1)?C(T,_n-i+2):0))%P+ans)%P,--j;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：2)

[传送门](https://codeforces.com/contest/1550/problem/D)

这是我离 Master 最近的一场比赛，可惜被 C 题卡太久+写错一个变量名没看出来。

##### 题意：

对于一个长度为 $n$ 的整数序列称其为 good 当且仅当 $\forall i,a_i \neq i$.（注意 $a_i$ 可为负数）

定义 $f(a)=\sum_{i=1}^n \sum_{j=i+1}^n[a_i+a_j=i+j]$

定义 $g(n)$ 为长度为 $n$ 的 good 序列所能取到的最大的 $f$ 的值。

试求满足条件的长度为 $n$ 的序列 $a$ 的个数，满足 $\forall i,l \le a_i \le r$ 且 $f(a)=g(n)$.

Data Range：$2 \le n \le 2\,\times 10^5,-10^9 \le l \le 1,n \le r \le 10^9$.

##### 分析：

考虑研究令 $f$ 取得最大值的 $a$ 的条件。容易构造出一组解：$1-x,2+x,3-x,...,n+(-1)^nx$. 说人话，就是一半加上一个不变的常数，剩下一半减去一个不变的常数。（我们称这个常数为“差”）。

由样例 $1$ 的解释可得，我们只要求有一半是加上固定常数，另一半是减去固定常数，而**并不对加上和减去的位置做要求**。比如说 $1+1,2-1,3+1$ 可以令 $f$ 取到最大值，同样 $1-1,2+1,3+1$ 也能让 $f$ 取到最大值。

方便起见，我们设 $llim_i$ 是 $i$ 最大减去多少可以保证依旧 $\ge l$；类似地定义 $rlim_i$ 是 $i$ 最大加上多少可以保证 $\le r$.

容易发现 $llim$ 和 $rlim$ 分别形如：
$$
llim_1,llim_1+1,llim_1+2,...,llim_1+n-1
$$

$$
rlim_1,rlim_1-1,rlim_1-2,...,rlim_1-n+1
$$

那么“加”就等价于在 $rlim$ 中减，“减”就等价于在 $llim$ 中减。所以我们统一成了减法。同时要求 $llim$ 和 $rlim$ 中最后不能有负数。

同时我们考虑枚举差 $x$（由 $l,r$ 决定上界，下界为 $1$).  看上去 $x$ 是 $10^9$ 级别的。显然暴毙。

但是注意到，对于绝大多数的 $x$，对每个位置 $i$ 来说，$llim_i$ 和 $rlim_i$ 都是大于等于 $x$ 的。形式化地，在 $x \le \min\{llim_1,rlim_n\}$ 的时候，对任意的 $i$，不管它最后加 $x$ 还是减 $x$ 都是在 $[l,r]$ 范围内的。

显然可以求出这样的 $x$ 的个数。记作 $cnt$ 。那么答案就应该加上
$$
\begin{cases} cnt \cdot \dbinom{n}{n/2} ,2 \mid n \\
2cnt \cdot \dbinom{n}{(n+1)/2},otherwise\end{cases}
$$
（因为如果 $n$ 为奇数，比如说 $n=5$，既可以是 $2$ 个加 $3$ 个减也可以是 $3$ 个加 $2$ 个减，所以奇偶需要分类讨论）。

同时应该注意到，对于一个 $x$。如果 $llim_n<x$ 或者 $rlim_1<x$ 那么 $x$ 本身和再大的 $x$ 都不再合法。

那么容易发现，还会剩下一些 $x$ 使得对于某些位置 $i$，要么这个位置只能加 $x$ 要么这个位置只能选择减 $x$. 值得注意的是这样的 $x$ 个数是 $O(n)$ 级别的。这里给出一个简短的说明：

还记得上文里的 $x \le \min\{llim_1,rlim_1\}$ 吗？我们不妨设这个 $\min$ 的值等于 $llim_1$. 这意味着 $x>llim_1$ 的时候 $1$ 处只能选择加 $x$ 不能选择减 $x$. 同时注意到 $x$ 有意义的话必须不超过 $llim_n$ . 也就是说此时 
$$
llim_1 \lt x \le llim_n
$$
又因为 $llim_n=llim+n-1$，显然这种情况的 $x$ 是 $O(n)$ 级别的。

同理，$\min$ 值等于 $rlim_n$ 的时候意味着 $rlim_n \le x \le rlim_1$ 也是 $O(n)$ 级别的。

考虑对于暴力枚举的 $x$ 怎么统计。显然在 $llim$ 上二分可以求出只能选择加 $x$ 的个数，因为是在 $llim$ 上二分我记作 $lcnt$；同理 $rlim$ 上二分求出只能选择减 $x$ 的个数，记作 $rcnt$. 那么答案此时加上
$$
\begin{cases}\dbinom{n-lcnt-rcnt}{n/2-rcnt},2 \mid n \\
\dbinom{n-lcnt-rcnt}{(n+1)/2-rcnt}+\dbinom{n-lcnt-rcnt}{(n-1)/2-rcnt},otherwise
\end{cases}
$$
预处理阶乘逆元，总复杂度即成为 $O(n \log n)$. 足以通过此题。

不过注意到 $lcnt$ 和 $rcnt$ 应该是每次 $+1$ 的没必要二分。但是阶乘逆元的瓶颈我不太会优化到线性 qwq

```c++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=2e5+10,mod=1e9+7;
ll t,n,l,r,ans;
ll llim[MAXN],rlim[MAXN],fact[MAXN],inv[MAXN];
ll rtmp[MAXN];
ll power(ll a,ll n){
	if(!n)return 1;
	ll tmp=power(a,n/2);tmp=tmp*tmp%mod;
	if(n&1)tmp=tmp*a%mod;
	return tmp; 
}
ll C(ll n,ll m){
	if(n<0 || m<0)return 0; 
	if(m>n)return 0;
	return fact[n]*inv[m]%mod*inv[n-m]%mod;
}
int main(){
	fact[0]=1;
	rep(i,1,2e5)fact[i]=fact[i-1]*i%mod;
	rep(i,0,2e5)inv[i]=power(fact[i],mod-2);
	cin>>t;
	while(t--){
		cin>>n>>l>>r;
		rep(i,1,n){
			llim[i]=i-l;
			rlim[i]=r-i;
		}
		rep(i,1,n){
			rtmp[i]=rlim[n-i+1];
		}
		ans=0;
		ll L=1,R=Min(llim[n],rlim[1]);
		if(L>R){
			printf("0\n");continue;
		}
		//差在[L,R]之间
		ll lim=Min(llim[1],rlim[n]); //最大选到lim都没有限制 
		if(lim>=L){
			ans=(ans+(lim-L+1)*C(n,(n+1)/2)*(1+odd(n))%mod)%mod;
		} 
		rep(j,Max(L,lim+1),R){
			//考虑暴力计算合法方案个数
		//	printf("差为%d\n",j);
			int lcnt=lower_bound(llim+1,llim+1+n,j)-llim-1; //前lcnt个只能选r
			int rcnt=lower_bound(rtmp+1,rtmp+1+n,j)-rtmp-1; //后rcnt个只能选l
		//	printf("lcnt:%d rcnt:%d\n",lcnt,rcnt);
		//	printf("%d %d\n",(n+1)/2,n-(n+1)/2);
			if(lcnt+rcnt>n)break;
			ans=(ans+C(n-lcnt-rcnt,(n+1)/2-rcnt))%mod;
			if(odd(n))ans=(ans+C(n-lcnt-rcnt,n-(n+1)/2-rcnt))%mod; 
		//	printf("ans:%d\n",ans);
		}
		printf("%lld\n",ans);
	}

	return 0;
}
```



---

## 作者：TernaryTree (赞：0)

考虑 $a_i-i\in\{d,-d\}$，设 $a_i-i=d$ 个数为 $x$，为 $-d$ 个数为 $y$，则满足条件的对数为 $xy$。根据均值不等式得到 $|x-y|$ 越小越好，即 $|x-y|=n\bmod 2$，$\min(x,y)=\lfloor\dfrac n2\rfloor$。换句话说，在 $a_i=i$ 中选择 $\dfrac n2$ 个数加上 $d$，剩下减去 $d$。

枚举 $d\in [1,r-l+1]$。计算出 $[1,n]$ 中只能 $+d$ 的数与只能 $-d$ 的数个数，并算出都可以的数的个数。然后组合数。这里是 $\Theta(\sum (r-l))$ 的。

对于每个 $d$ 输出答案，发现有很多答案是重复的，关键在于上面所说的几个有关组合的量都相同。对不等式进行推导，得到前 $\min(-l,r-n)$ 个答案是相同的，计算一次即可。另外，如果当前 $d$ 答案为 $0$ 即可直接退出循环。

时间复杂度 $\Theta(\sum n)$。

[Code](https://www.luogu.com.cn/paste/zsibfbd2)

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2300}$
---
### 解题思路：

$F(a)$ 和 $a_i$，$a_j$，$i$ 和 $j$ 都有关系，不好处理，考虑通过将 $a$ 变化为 $b_i=a_i-i$ 来转化问题。

那么原来的 $a_i+a_j=i+j$ 也就被转化为了 $b_i+b_j=0$。由此轻松得出要 $F(a)$ 最大就是要 $b_i$ 中有一半是 $-x$ 一半是 $x$，如果长度为奇数，可以差一个。而且 $b$ 中不存在 $0$，也就是满足 $a_i\neq i$。

然后考虑数值的范围 $[l,r]$，不妨设当前的 $|b_i|=u$，$u$ 和 $-u$ 都能取到的有 $x$ 个，只能取到正的有 $y$ 个，只能取到负的有 $z$ 个。如果有数两个都不能取到，那么总方案数为 $0$。当 $x+z\le \dfrac{x+y+z}{2}$ 或者 $x+y\le\dfrac{x+y+z}{2}$ 的时候也没有解。

此时需要分情况讨论：

1. 如果 $n$ 是偶数，那么能取到方案数有：$C(x,\dfrac{(x-y+z)}{2})$，或者 $C(x,\dfrac{(x+y-z)}{2})$，两者显然相等。

2. 否则就需要知道是正的多一点还是负的多一点了。再分情况讨论，当 $x+y\ge \dfrac{x+y+z}{2}+1$，也就是有可能正的多，就有 $C(x,\dfrac{x+y+z}{2}-y+1)$。另一种就是当 $x+z\ge\dfrac{x+y+z}{2}+1$ 时，能够产生 $C(x,\dfrac{x+y+z}{2}-z+1)$ 的方案数。

---

仅仅这样是不能通过这道题的，数据范围很大，直接枚举复杂度显然爆炸。

但是可以发现只要 $x$，$y$ 和 $z$ 是相等的，计算出来的结果也就是一样的，可以考虑中间跳过大段的计算过程，直接根据有值变化的点计算结果。

那么就计算出每一个点的变化范围 $[l,r]$，然后将每一个 $l$ 或者 $r$ 设置为可能的变化点，排序并记录下当前三个变量的值就好了。

---
### 代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=400005,MOD=1000000007;
int F[MAXN],F_[MAXN],n,l,r,T,f[MAXN][2],cnt,x,y,z,ans;
struct str{
	int id,x,type;
	bool operator < (str a){
		return x<a.x;
	}
}num[MAXN];
int pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
void init(){
	F[0]=1;F_[0]=1;
	for(int i=1;i<=200000;i++)F[i]=(F[i-1]*i)%MOD;
	for(int i=1;i<=200000;i++)F_[i]=pow(F[i],MOD-2)%MOD;
}
int C(int n,int m){return (F[n]*F_[n-m]%MOD)*(F_[m])%MOD;}
void calc(int len){
	if(x+y+z==n&&x+y>=n/2&&x+z>=n/2){
		if(n%2==0)ans=(ans+C(x,n/2-y)*len)%MOD;
		else{
			if(x+y>=n/2+1)ans=(ans+C(x,n/2-y+1)*len)%MOD;
			if(x+z>=n/2+1)ans=(ans+C(x,n/2-z+1)*len)%MOD;
		}
	}
}
void fit(int p){
	if(num[p].type==1){
		f[num[p].id][1]=1;
		if(f[num[p].id][0]==1)x++,z--;
		else y++;
	}
	if(num[p].type==2){
		f[num[p].id][0]=1;
		if(f[num[p].id][1]==1)x++,y--;
		else z++;
	}
}
signed main(){
	init();
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d%I64d%I64d",&n,&l,&r);
		cnt=1;num[1].type=114514;
		memset(f,0,sizeof(f));
		for(int i=1;i<=n;i++){
			int L=abs(i-l),R=abs(r-i);
			if(L!=0){
				num[++cnt].id=i;
				num[cnt].type=1;
				num[cnt].x=L;
			}
			if(R!=0){
				num[++cnt].id=i;
				num[cnt].type=2;
				num[cnt].x=R;
			}
		}
		sort(num+1,num+cnt+1);
		x=0;y=0;z=0;ans=0;
		for(int i=cnt;i>1;i--){
			while(num[i-1].x==num[i].x)fit(i),i--;
			fit(i);
			calc(num[i].x-num[i-1].x);
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
/*

1
2 -2 5

*/
```



---

