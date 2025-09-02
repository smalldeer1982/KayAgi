# [AGC005D] ~K Perm Counting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc005/tasks/agc005_d

すぬけ君は順列が大好きなので、長さ $ N $ の順列を作ることにしました。

ただしすぬけ君は整数 $ K $ が嫌いなので、以下の条件を満たす順列を作ることにしました。

- 順列を $ a_1,\ a_2,\ ...,\ a_N $ とする。全ての $ i\ =\ 1,2,...,N $ について、$ |a_i\ -\ i|\ \neq\ K $ を満たす

長さ $ N $ の順列は $ N! $ 通りありますが、そのうち条件をみたすものは何個あるかを求めてください。

ただし答えは非常に大きくなることがあるので、答えを $ 924844033 $(素数) で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 2000 $
- $ 1\ ≦\ K\ ≦\ N-1 $

### Sample Explanation 1

$ (1,\ 2,\ 3) $, $ (3,\ 2,\ 1) $ の $ 2 $ つが条件を満たす。

### Sample Explanation 2

$ (1,\ 2,\ 3,\ 4) $, $ (1,\ 4,\ 3,\ 2) $, $ (3,\ 2,\ 1,\ 4) $, $ (3,\ 4,\ 1,\ 2) $, $ (4,\ 2,\ 3,\ 1) $ の $ 5 $ つが条件を満たす。

## 样例 #1

### 输入

```
3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
4 1```

### 输出

```
5```

## 样例 #3

### 输入

```
4 2```

### 输出

```
9```

## 样例 #4

### 输入

```
4 3```

### 输出

```
14```

## 样例 #5

### 输入

```
425 48```

### 输出

```
756765083```

# 题解

## 作者：Dreamunk (赞：59)

[题目](https://www.luogu.com.cn/problem/AT2062)

如果你看过一些关于组合数学的书，你可能会想到，这种排列计数可以对应到这样的图上：

![_5__RIUYDMY5KS@6@T____Q.png](https://i.loli.net/2020/08/07/ATHUYM3WDXGkua4.png)

所求的排列个数，就等于在这样的棋盘格子内放 $n$ 个互不攻击的車，且阴影格子不能放的方案数。上图是 $n=7,k=2$ 的情况。

这又怎么求呢？考虑容斥。设 $f_i$ 表示我硬要在阴影里放 $i$ 个車，剩下随便放的方案数，那么答案等于 $\sum_{i=0}^n (-1)^if_i(n-i)!$ 。

那现在只要求 $f_i$ 就好了。

考虑现在的还有什么限制，你发现同一行同一列的阴影格子还是不能同选。把不能同选的格子连上边：

![W2B96`T2GG__F_YY@4_E_AS.png](https://i.loli.net/2020/08/07/Yzba5WgrJsjqZXQ.png)

那 $f_i$ 其实就是这个图大小为 $i$ 的独立集个数。

很明显这个图就是若干条链。

考虑把这些链连起来。转为求从这一排结点中选 $i$ 个，拼接的位置可以相邻，其他位置不能相邻 的方案数。于是它变为了一个简单的 DP 问题。

$O(n^2)$ 解决。

当然这题可以用多项式方法做到 $O(n\log n)$。不讲。

```cpp
#include<cstdio>
typedef long long ll;
const int N=2003,M=924844033;
int n,m,fac[N],f[N+N][N],t,a[N+N],ans;
int main(){
	scanf("%d%d",&n,&m);
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=(ll)fac[i-1]*i%M;
	a[t=0]=1;
	for(int i=1;i<=(n-m)%m;i++)
	  a[t+=(n-m)/m+1]=1,a[t+=(n-m)/m+1]=1;
	for(int i=1;i<=m-(n-m)%m;i++)
	  a[t+=(n-m)/m]=1,a[t+=(n-m)/m]=1;
	f[0][0]=1;
	for(int i=1;i<=t;i++)
	  for(int j=0;j<=n;j++)
		f[i][j]=(f[i-1][j]+(j?f[i-1-(!a[i-1])][j-1]:0))%M;
	for(int j=0;j<=n;j++)
	  ans=(ans+(ll)f[t][j]*fac[n-j]%M*(j&1?M-1:1))%M;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：ez_lcw (赞：33)

首先正面做不太好做，考虑容斥。

设 $f(m)$ 表示排列中至少有 $m$ 处 $|P_i-i|=k$ 的方案数。

那么答案就是 $\sum\limits_{i=0}^n(-1)^if(i)$。

原题可以看成一个二分图的形式：（$n=5$ 时）

![](https://cdn.luogu.com.cn/upload/image_hosting/opabe72v.png)

左边是排列的编号，右边是权值，那么现在要做的就是连 $n$ 条边，补全这个二分图，使得每个点的度数都是 $1$。

那么考虑什么时候会出现 $|P_i-i|=k$ 的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/5s8onaw1.png)

如图，当 $k=1$ 时，连出上图中的任意一条边都会使得 $|P_i-i|=k$。

我们考虑选出一些边，而且任意两条边都不能接在同一个端点上（因为每个点的度数要为 $1$）。

发现图中的边构成了若干条链且互不影响，于是把他们拿出来铺平：

![](https://cdn.luogu.com.cn/upload/image_hosting/86viqgbi.png)

此时如果要使得 $|P_i-i|=k$，只有相邻两个点之间才会连边，而且 $a_5$ 和 $1$ （第 $5$ 个点和第 $6$ 个点）之间不会连边。

设 $dp(i,j,01/0)$ 表示已经考虑了前 $i$ 个点，其中连了 $j$ 条边，第 $i-1$ 个点和第 $i$ 个点之间是/否连边的方案数。

那么容易得到：

$$
\begin{cases}
dp(i,j,0)=dp(i-1,j,0)+dp(i-1,j,1)\\
dp(i,j,1)=dp(i-1,j-1,0)
\end{cases}
$$

但是还有一种特殊情况，那就是 $i=6$ 时，第 $5$ 个点和第 $6$ 个点之间不能连边，所以此时 $dp(i,j,1)$ 不存在。

所以我们需要开一个数组判断一下某一个点是否是链的开头。

按着这个 dp，那么有 $f(m)=(n-m)!\times dp(2n,m)$。

意思就是先把满足有 $m$ 个 $|P_i-i|=k$ 的方案数算出来，剩下的数随便排列。

代码如下：

```cpp
#include<bits/stdc++.h>

#define N 2010
#define ll long long
#define mod 924844033

using namespace std;

int n,k,tot,a[N];
ll fac[N],dp[N<<1][N][2];
bool vis[N<<1];

int main()
{
	scanf("%d%d",&n,&k);
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<=k;i++)
	{
		for(int t=0;t<2;t++)
		{
			for(int j=i;j<=n;j+=k)
			{
				tot++;
				if(i!=j) vis[tot]=1;
			}
		}
	}
	dp[0][0][0]=1;
	for(int i=1;i<=(n<<1);i++)
	{
		for(int j=0;j<=n;j++)
		{
			dp[i][j][0]=(dp[i-1][j][0]+dp[i-1][j][1])%mod;
			if(vis[i]&&j) dp[i][j][1]=dp[i-1][j-1][0];
		}
	}
	ll ans=0;
	for(int i=0;i<=n;i++)
	{
		if(i&1) ans=(ans-(dp[n<<1][i][0]+dp[n<<1][i][1])*fac[n-i]%mod+mod)%mod;
		else ans=(ans+(dp[n<<1][i][0]+dp[n<<1][i][1])*fac[n-i]%mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：xzggzh1 (赞：32)


问满足对于所有的 $i$ 都有 $|P_i-i|\neq k$ 的排列 $P$ 的个数。$n\le 2000$。

---

正着不好求，那我直接容斥，用 $f(i)$ 来表示钦定至少 $i$ 个地方冲突的方案数。答案就是 $\sum_{i=1}^n (-1)^i \times f(i)$。

我们看到一个点 $x$ 和位置 $x± k$ 有关系，我们可以抽象看做边，这样可以把原序列分成若干条链（链中一半是点一半是位置）。

这里偷一张 ez_lcw 巨佬的图方便理解 ![](https://cdn.luogu.com.cn/upload/image_hosting/5s8onaw1.png)

这里可以分成 **两条路**。

其一 $dp$:


我们可以对每一个链分别考虑：$f[i][j][0/1]$ 表示前 $i$ 个节点选了 $j$ 个边且，第 $i$ 节点和 $i-1$ 节点是否连边的方案数。有：

$$f[i][j][0]=f[i-1][j][0]+f[i-1][j][1]$$

$$f[i][j][1]=f[i-1][j-1][0]$$

在实现的时候可以把所有链首尾相接一起处理（但是这样新链的起点无法向旧链的终点连边），最终就有 $f(i)=(n-i)!\times f[2n][i]$。（因为 $i$ 是钦定的，所以剩下的随便选）。

其二卷积：

我们知道对于每一个节点数为 $m$ 的链取 $i$ 个互不相邻的边的方案数是 $\dbinom{m-i}{i}$。（类似于隔板法）。每个链方案独立的，把所有链的 OGF 卷积起来即可。如果用的是暴力卷积 是 $\mathcal{O}(n\times \frac{n}{k} \times k)$ 的，如果用多项式科技加速可以到 $\mathcal{O}(n\log n)$。


---

这里给出一个暴力卷积的核心代码：

```cpp
//这里省去modint和预处理
modint S[MaxN],G[MaxN],tmp,n,k;
int main()
{
	cin>>n>>k;
	S[0]=1;
	for (int r=1;r<=min(2*k,n);r++){
		modint m=(r>k)-1;
		for (int i=r;i<=n;i+=k)m++;
		for (int i=0;i<=n;i++){G[i]=S[i];S[i]=0;}
		for (int i=0;i<=m;i++){
			tmp=C(m-i+1,i);
			for(int j=0;i+j<=n;j++)
			S[i+j]=S[i+j]+tmp*G[j];
		}
	}
	modint ans=0;
	for (int t=0;t<=n;t++){
		tmp=fac[n-t]*S[t];
		if (t&1)ans-=tmp;else ans+=tmp;  
	}
	cout<<ans;
}
```

---

## 作者：Siyuan (赞：14)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[AGC 005D](https://agc005.contest.atcoder.jp/tasks/agc005_d)

给出 $n$ 和 $k$，求有多少个长度为 $n$ 的排列 $a$ 使得对于任意的 $1\leqslant i\leqslant n$，都满足 $|a_i-i|\neq k$。

数据范围：$2\leqslant n\leqslant 2000$，$1\leqslant k<n$

---

## Solution

很显然本题正着做很麻烦，于是我们考虑容斥的方法。

记 $f(i)$ 表示至少有 $i$ 个位置不满足条件的方案数，则答案为

$$\sum_{i=0}^n (-1)^i\times f(i)$$

注意到对于每个数，与它的差的绝对值为 $k$ 的数不超过 $2$ 个，也就是说如果在 $x$ 和 $x+k$ 之间连边，那么会形成 $k$ 条链，每个点只能和与它有相连的边配对（如果要不满足条件，$x$ 要放在下标为 $x\pm k$ 的位置）。

考虑对每条链 $\text{DP}$，设 $f[i][j]$ 表示前 $i$ 个点选了 $j$ 个不满足条件的数的方案数。

但是注意到一点：每个数 $x$ 可以和 $x\pm k$ 配对，所以我们需要记录下当前点和下一个点是否被配对。

考虑对于每条链 $\text{DP}$，我们记 $f[i][j][p][q]$ 表示前 $i$ 个点选了 $j$ 个不满足条件的数，当前数字 $x$ 和下一个 $x+k$ 是否被选上的方案。

具体 $\text{DP}$ 转移详见代码（注意有些转移要求差为 $k$）。

**时间复杂度**：$\Theta(n^2)$

---

## Code

```cpp
#include <cstdio>
#define FOR(i,a,b) for(int i=a;i<=b;++i)

const int N=2005;
const int P=924844033;
int n,k,a[N],fac[N];
long long f[N][N][2][2];
bool vis[N];

int main() {
    scanf("%d%d",&n,&k);
    fac[0]=1;
    FOR(i,1,n) fac[i]=1LL*fac[i-1]*i%P;
    int tot=0;
    FOR(i,1,n) if(!vis[i]) for(int j=i;j<=n;j+=k) vis[j]=1,a[++tot]=j;
    f[0][0][0][0]=1;
    a[0]=-(1<<30);
    FOR(i,1,n) {
        f[i][0][0][0]=1;
        FOR(j,1,i) {
            f[i][j][0][0]=(f[i-1][j][1][0]+f[i-1][j][0][0]+(a[i]-a[i-1]==k)*f[i-1][j-1][0][0])%P;
            f[i][j][0][1]=(a[i+1]-a[i]==k)*(f[i-1][j-1][1][0]+f[i-1][j-1][0][0])%P;
            f[i][j][1][0]=(f[i-1][j][0][1]+f[i-1][j][1][1]+(a[i]-a[i-1]==k)*f[i-1][j-1][0][1])%P;
            f[i][j][1][1]=(a[i+1]-a[i]==k)*(f[i-1][j-1][0][1]+f[i-1][j-1][1][1])%P;
        }
    }
    int ans=0;
    FOR(i,0,n) {
        int sum=(f[n][i][0][0]+f[n][i][0][1]+f[n][i][1][0]+f[n][i][1][1])%P;
        if(i&1) (ans+=P-1LL*sum*fac[n-i]%P)%=P;
        else (ans+=1LL*sum*fac[n-i]%P)%=P;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：奇卡 (赞：7)

这个题我们校内测试考了加强版($n,k\leq 10^5$)，然后我把我的校内OJAC代码复制过来，四个小样例全错……

改过之后，在惊叹校内OJ数据水的同时，也发篇题解讲讲$O(nlogn)$做法~ 当作给省选涨RP~

----

首先设$G_i$表示钦定$i$个位置满足$|p_i-i|=k$，其余不管的方案数。求出$G_i$就能二项式反演出答案。有$G_i=g_i(n-i)!$，$g_i$表示有$i$个位置满足$|p_i-i|=k$的方案数，问题转化成求$g_i$.

发现对于每个模$k$的同余类，方案是互相独立的。于是可以对于每个$x\in[0,k-1]$，求出$g_{x,i}$再卷积合并。

对于每个同余类，我们可以建一张二分图，左边是值，右边是位置，左边的每个数$x$往右边的$x+k,x-k$连边，然后钦定每条边的方向是大数连向小数，这样就得到了两条互不相交的链。

于是问题转换成了：在一条链上，选一些边，满足这些边互不相邻的方案数。这有个经典结论：在$i$条边的链上选$j$条边满足条件的方案数是$\binom{i-j}{j}$，[证明走这](https://www.luogu.com.cn/blog/wohaocaia/solution-p5339)

然而我考场上并不知道这个结论，~~睿智选手石锤~~，于是我写了个DP来求这个组合数：设$h_{i,0/1,j}$表示当前dp到第$i$条链，这条链有没有选，选了$j$条边的方案数，$H_{i,0/1}(x)$表示$h_{i,0/1}$的生成函数。

有
$$ H_{i,0}(x)=H_{i-1,0}(x)+H_{i-1,1}(x)$$
$$ H_{i,1}(x)=xH_{i-1,0}(x)$$

可以矩阵快速幂+$NTT$维护

于是这题就做完了

AtCoder亲测能过，洛谷remote judge挂了所以没交。

代码
```cpp
#include <bits/stdc++.h>
#define For(i,x,y) for(register int i=(x);i<=(y);++i)
#define Rof(i,x,y) for(register int i=(x);i>=(y);--i)
#define Edge(i,x) for(register int i=head[x];i;i=e[i].nxt)
const int N=4e5+10020;
const int mod=924844033;
using namespace std;

vector<int> _1,_x,_x1,_0;//G(x)=1,G(x)=x,G(x)=x+1
int adD(int x,int y){ return x+y>=mod?x+y-mod:x+y; }
int mnS(int x,int y){ return x-y<0?x-y+mod:x-y; }

int qpow(int x,int y){
	int res=1;
	for(;y;y>>=1,x=1ll*x*x%mod) if(y&1) res=1ll*res*x%mod;
	return res;
}
int len,bit,invlen,rev[N],fac[N],invf[N];

void NTT(vector<int> &a,int f){
	For(i,0,len-1) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int i=2;i<=len;i<<=1){
		int omega=qpow(5,(mod-1)/i),mid=i>>1;
		if(f==-1) omega=qpow(omega,mod-2);
		for(int j=0;j<len;j+=i)
			for(int k=j,w=1;k<j+mid;++k,w=1ll*w*omega%mod){
				int u=a[k],v=1ll*a[k+mid]*w%mod;
				a[k]=adD(u,v),a[k+mid]=mnS(u,v);
			}		
	}
	if(f==-1) For(i,0,len-1) a[i]=1ll*a[i]*invlen%mod;
}

void init(int n){
	for(len=1,bit=0;len<=n;len<<=1,++bit);
	For(i,0,len-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	fac[0]=1;
	For(i,1,n) fac[i]=1ll*fac[i-1]*i%mod;
	invf[n]=qpow(fac[n],mod-2);
	Rof(i,n-1,0) invf[i]=1ll*invf[i+1]*(i+1)%mod;	
	invlen=qpow(len,mod-2);
}

struct Poly{
	vector<int> a;
	const int operator [] (const int &x) const {return a[x];}
	const int size()const{ return a.size(); }
	void resize(int x){ a.resize(x); }
	void clear(){ a.clear(); }
	const Poly operator +(const Poly &x)const{
		Poly res; res.resize(len);
		For(i,0,len-1) res.a[i]=a[i];
		For(i,0,len-1) res.a[i]=adD(res[i],x[i]);
		return res;
	}
	const Poly operator * (const Poly &x)const{
		Poly res;res.resize(len);
		For(i,0,len-1) res.a[i]=1ll*a[i]*x.a[i]%mod;
		return res;
	}
};

struct Mat{
	Poly a[2][2];
	void clear(){
		For(i,0,1) For(j,0,1){
			a[i][j].resize(1);
			a[i][j].a[0]=0;
		}	
	}
};
void debug(vector<int> &x){
	For(i,0,(int)x.size()-1) printf("%d ",x[i]);puts("");	
}
Mat mat[20],res,oo,aa;

Poly tmp,G,H;
void Minit(){
	mat[0].a[0][0].a=_1;
	mat[0].a[1][0].a=_1;
	mat[0].a[0][1].a=_x;
	mat[0].a[1][1].a=_0;
	For(x,1,16){
		mat[x]=oo;
		For(i,0,1) For(k,0,1) For(j,0,1){
			mat[x].a[i][j]=mat[x].a[i][j]+mat[x-1].a[i][k]*mat[x-1].a[k][j];
		}
	} 	
}
void getpow(int x,int y){
	if(x<0) return;
	y=2*y;
	res.a[0][0].a=_1;
	res.a[0][1].a=_x;
	res.a[1][1].a=_0;
	res.a[1][0].a=_0;
	For(p,0,16) if((x>>p)&1){
		aa=oo;
		For(i,0,1) For(k,0,1) For(j,0,1){
			aa.a[i][j]=aa.a[i][j]+res.a[i][k]*mat[p].a[k][j];
		}
		res=aa;				
	}			
	For(i,0,len-1) tmp.a[i]=res.a[0][0].a[i]+res.a[0][1].a[i];
	
	for(;y;y>>=1){
		if(y&1) G=G*tmp;
		tmp=tmp*tmp;
	} 
}
int ans[N],cnt[2],pos[2]={-1,-1};
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	
	init(2*n);
	tmp.resize(len);
	_1.resize(len),_1[0]=1;
	_x.resize(len),_x[0]=0,_x[1]=1;
	_x1.resize(len),_x1[0]=1,_x1[1]=1;
	_0.resize(len);
	NTT(_1,1),NTT(_x,1),NTT(_x1,1);
	
	For(i,0,1) For(j,0,1) oo.a[i][j].a=_0;
	Minit();
	G.a=_1;
	For(i,1,m){
		int p=0;
		for(int j=i;j<=n;j+=m) ++p;
		--p;
		if(pos[0]!=p){
			if(pos[0]==-1) pos[0]=p,cnt[0]=1;
			else{
				if(pos[1]==-1) cnt[1]=1,pos[1]=p;
				else cnt[1]++;
			}
		} else cnt[0]++;
	}
	getpow(pos[0]-1,cnt[0]);
	getpow(pos[1]-1,cnt[1]);
	
	NTT(G.a,-1);
	For(i,0,n) G.a[i]=1ll*G[i]*fac[n-i]%mod*fac[i]%mod;
	For(i,n+1,len-1) G.a[i]=0;
	For(i,0,n/2) swap(G.a[i],G.a[n-i]);
//	debug(G.a);
	H.resize(len);
	For(i,0,n){
		if(i&1) H.a[i]=mod-invf[i];
		else H.a[i]=invf[i];
	}
	NTT(G.a,1),NTT(H.a,1);
	G=G*H;
	NTT(G.a,-1);
//	debug(G.a);
	
	For(i,0,n) ans[i]=1ll*invf[i]*G[n-i]%mod;
	printf("%d\n",ans[0]);
}
```



---

## 作者：myee (赞：5)

### 前言

![CMLL02_AK_DSPOLY.jpg](https://cdn.luogu.com.cn/upload/image_hosting/0mabjd42.png)

### 思路

考虑把“不能”的关系对应上图的一条有向边，我们怎么做。

不妨记 $f_k$ 表示从图中选出 $k$ 条边的可行方案数。

那么我们由**子集反演**，立刻得到：

$$Ans=\sum_k(-1)^k(n-k)!f_k$$

于是我们要做的是快速统计 $f$。

仔细观察这张图中**哪些边会冲突**。

显然就是**起点或终点相同的边**。

由于这张图是由许多链组成的，考察每一条链状结构；具体地，形如：

$$a\rightarrow b\leftarrow c\rightarrow d\rightarrow\cdots \leftarrow z$$

这样的链不能取相邻项，且除此之外的链均与此链无冲突关系。

记链上有 $p$ 个顶点，那就是统计对于每种边数，链上有几种取法。

显然这就是所谓无标号 $\operatorname{SEQ}$ 构造的形式，不难得其为：

$$\\
[u^p]{1\over1-u-zu^2}
\\={({1+\sqrt{1+4z}\over2})^{p+1}-({1-\sqrt{1+4z}\over2})^{p+1}\over\sqrt{1+4z}}
\\$$

对每条这样的链都做一遍，然后暴力乘起来就好了。

顺带提一句，其实 $924844033$ 也是 NTT 模数。

### Code

$n$ 较小，采取了暴力多项式。

以下放核心代码。

```cpp
using namespace BF_POLY;
poly Pow(poly base,uint index,uint prec)
{
    base.chg_siz(prec);
    poly ans(modvec{1});
    while(index)
    {
        if(index&1)ans*=base,ans.chg_siz(prec);
        base*=base,base.chg_siz(prec);index>>=1;
    }
    return ans;
}
int main()
{
    AnyMod::ChgMod(924844033);
    uint n,k;scanf("%u%u",&n,&k);
    poly User({1,4});
    User=User.sqrt(n+2);
    poly Inv=User.inv(n+2);
    poly QAQ(modvec{1});
    for(uint i=0;i<k;i++)
    {
        uint p=(n-i-1)/k+1;
        poly P=
            (Pow((modint(1)+User)*modint(2).inv(),p+1,p+1)-
            Pow((modint(1)-User)*modint(2).inv(),p+1,p+1))
            *cpd().chg_siz(Inv,p+1);
        P.chg_siz(p+1);
        QAQ*=P*P;
    }
    modint ans=0,v(1);
    for(uint i=n;~i;i--)
    {
        ans+=(i&1?AnyMod::Mod-1:1)*v*QAQ.val(i);
        v*=n-i+1;
    }
    ans.println();
    return 0;
}
```




---

## 作者：Weng_Weijie (赞：3)

这里描述一下我的 $O(n^2)$ 做法，可以使用多项式科技优化到 $O(n\log n)$。

**题意：**

求有多少个大小为 $n$ 的排列 $p_i$ 满足 $|p_i-i|\neq k$。

**题解：**

首先第一步肯定是使用容斥原理：

设 $f(S)$ 为对 $i\in S$ 都有 $|p_i-i|=k$ （其余任意）的排列数量。

答案即为 $\sum\limits_{S}f(S)(-1)^{|S|}$。

容易发现，当 $i\in S$ 时，确定 $p_i$ 的值对 $S$ 以外元素没有影响（即其他元素的 $p$ 值的方案数仍是全排列）。

于是考虑枚举 $n-|S|$ 的大小。

$$\sum_{t=0}^ng(i)(-1)^{n-t}\cdot t!$$

其中 $g(i)$ 表示 $|S|$ 大小为 $n-i$（即未被确定元素个数为 $i$ 个）时 **$|S|$中的那些元素有多少种可能的取值**。

由 $p_i\equiv i\pmod{k}$，启示我们对每个 $\bmod k$ 的同余类计算，之后再做一个**背包合并**即可。

对每一个同余类考虑之后就是类似 $(1,4,7,10),(2,5,8,11),(3,6,9)$ 这样的（此时$n=11,k=3$）。

容易发现大小相等的同余类其实是等价的，不妨考虑其中一个大小为 $m$ 的同余类，将它们重编号为 $(1,2,3,\dots,m)$。

当一个元素属于 $S$ 时，$p_i=i-1$ 或 $p_i=i+1$。

接着便可以 DP，设 $f[i][j]$ 表示前 $i$ 个元素，有多少个元素**不在** $|S|$ 内。

1. $i\not\in S$，则 $f[i][j]\gets f[i-1][j-1]$

2. $i\in S$，且 $p_i=i-1,p_{i-1}=i$，则 $f[i][j]\gets f[i-2][j]$

3. $i\in S$，且 $p_i=i-1,p_{i-1}\neq i$：

则此时一定形成一条链：

（$p_i=i-1;p_{i-1}=i-2; \dots ;p_{k+1}=p_k;k\not\in S$）

或

（$k\not\in S;p_k=k+1;\dots;p_{i-2}=i-1,p_{i-1}=i$）

枚举链长：

$f[i][j]\gets\sum\limits_{t\geq 1}2\cdot f[i-t-1][j-1]$

使用前缀和优化即可，复杂度 $O(n^2)$。

注意：这里的背包合并复杂度为 $O\left(n\cdot\left(\dfrac nk\right)\cdot k\right)=O\left(n^2\right)$
（因为背包大小即同余类大小为 $\frac nk$ 级别）


接着经过一些操作（扰动法），我们可以得到 $f$ 本身的递推式：

$f[i][j]=f[i-1][j]+f[i-1][j-1]+f[i-2][j]+f[i-2][-1]-f[i-3][j]$

若将 $f[i][0..i]$ 看成一个多项式（即 $f[i]$ 的生成函数）：

$$F_n(x)=(1+x)(F_{n-1}(x)+F_{n-2}(x))-F_{n-3}(x)$$

其实是一个常系数线性齐次递推的形式。

至于这个有没有通解，有是有的（并且特征值的式子中没有出现虚数）~~，但对解题意义不大~~（也可以尝试一下）。

所以可以使用矩阵快速幂 + FFT 做到 $O(n\log n)$ 的复杂度（注意不是 $\Theta(n\log^2n)$）。

这里背包合并其实是生成函数的幂次（同余类的大小最多只有 2 种），因此可以用多项式科技优化。

~~不知道有没有神仙会去写~~

```cpp
#include <bits/stdc++.h>

const int N = 2005, mod = 924844033;
typedef long long LL;

void reduce(int &x) { x += x >> 31 & mod; }

int n, k, dp[N][N], max, f[N];
void calc(int n) {
	dp[0][0] = 1;
	dp[1][1] = 1;
	dp[2][0] = 1;
	dp[2][1] = 2;
	dp[2][2] = 1;
	
	for (int i = 3; i <= n; ++i) {
		for (int j = 0; j <= i; ++j) {
			int &ret = dp[i][j] = dp[i - 1][j];
			if (j) reduce(ret += dp[i - 1][j - 1] - mod);
			if (i > 1) reduce(ret += dp[i - 2][j] - mod);
			if (i > 1 && j) reduce(ret += dp[i - 2][j - 1] - mod);
			if (i > 2) reduce(ret -= dp[i - 3][j]);
		}
	}
}
void update(int *A) {
	static int B[N];
	for (int i = 0; i <= n; ++i) B[i] = 0;
	for (int i = 0; i <= max; ++i)
		for (int j = 0; j <= n - i; ++j)
			B[i + j] = (B[i + j] + (LL) A[i] * f[j]) % mod;
	for (int i = 0; i <= n; ++i) f[i] = B[i];
}
int main() {
	std::ios::sync_with_stdio(0), std::cin.tie(0);
	std::cin >> n >> k, calc(max = (n + k - 1) / k);
	int t = (n - 1) % k + 1;
	f[0] = 1;
	for (int i = 0; i < t; ++i) update(dp[max]);
	for (int i = t; i < k; ++i) update(dp[max - 1]);
	int factor = 1, ans = 0;
	for (int i = 0; i <= n; ++i) {
		if (n - i & 1)
			reduce(ans -= (LL) f[i] * factor % mod);
		else
			ans = (ans + (LL) f[i] * factor) % mod;
		factor = (LL) factor * (i + 1) % mod;
	}
	std::cout << ans << '\n';
	return 0;
}
```

---

## 作者：lizehon (赞：3)

[我的博客内查看效果更佳](https://www.cnblogs.com/lizehon/p/11211599.html)

[AT2602](https://agc005.contest.atcoder.jp/tasks/agc005_d) , [Luogu](https://www.luogu.org/problemnew/show/AT2062) 

求对于 $n$ 个数的排列 , 有多少种方案满足对于所有的 $i$ , $|P_i - i| != K$ , 答案对 $924844033$ 取模 .
$n,K \le 2000$

设 $g[i]$ 表示至少有 $i$ 个数不满足题意的方案数 , 则 $ans = \sum_{i=0}^n (-1)^{i} g[i]$ .
可以画一个二分图 , **左边表示下标 , 右边表示取值** , 相隔 $K$ 格的左右连一条边 . 网上有一个图 :

![](http://image.bubuko.com/info/201812/20181221210424134696.png)

**对于每一条链 , 每个点只能连一条边 .** 所以在每一条链上有转移 : 设 $f[i][j][0/1]$ 表示选到第 $i$ 个数 , 已经连了 $j$ 条边 , $i$ 与 $i-1$ 是否连边的方案数 , 在链的内部转移 .
对于所有的链 , 可以拼接在一起 , **链之间也可以转移 $f[i][j][0]$ 的方案数** , 这就相当于继承之前的结果继续 $DP$ .

要特别注意的是 , **拼接的链的长度是 $2n$** .
时间复杂度 $O((2n)^2)$ 

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cassert>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define Debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
typedef long long LL;
const int INF=1e9+7;
inline LL read(){
    register LL x=0,f=1;register char c=getchar();
    while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
    while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c&15),c=getchar();
    return f*x;
}

const int N = 4005;
const int mod = 924844033;

int a[N], g[N], f[N][N][2], fac[N];
int n, K, cnt, ans;

inline int add(int x, int y){return (x+y)%mod;}
inline int dec(int x, int y){return (x-y+mod)%mod;}
inline int mul(LL x, int y){return x*y%mod;}

int main(){
	n = read(), K = read();
	fac[0] = fac[1] = 1;
	for(int i = 2; i <= n; ++i) fac[i] = mul(fac[i-1], i);
	for(int i = 1; i <= K; ++i){
		for(int j = i; j <= n; j += K)
			a[++cnt] = j;
		for(int j = i; j <= n; j += K)
			a[++cnt] = j;
	}
	assert(cnt == (n << 1));
	f[1][0][0] = 1;
	for(int i = 2; i <= (n << 1); ++i){
		for(int j = 0; j <= min(n, i/2); ++j){
			f[i][j][0] = add(f[i-1][j][0], f[i-1][j][1]);
			if(j > 0 && a[i] - a[i-1] == K) f[i][j][1] = f[i-1][j-1][0];
		}
	}
	for(int i = 0; i <= n; ++i){
		g[i] = add(f[n << 1][i][0], f[n << 1][i][1]);
		if(!(i&1)) ans = add(ans, mul(g[i], fac[n - i]));
		else ans = dec(ans, mul(g[i], fac[n - i]));
	}
	printf("%d\n", ans);
}
```

---

## 作者：Arghariza (赞：2)

经典题。

考虑 dp，然后发现你根本 d 不动。

冷静思考，发现原因在于，无法在较小的复杂度内确定选数的状态。

遇到这种情况可以考虑容斥。设 $f(i)$ 表示强制选 $i$ 个位置满足 $|p_j-j|=k$。

显然 $\text{ans}=\sum\limits_{i=0}^n(-1)^if(i)(n-i)!$，因为根据容斥，剩下的位置可以随便填。问题变成了计算 $f(i)$。

以行为下标，列为值，画出网格图，发现使得 $|p_j-j|=k$ 的位置如下图灰色区域：

![](https://cdn.luogu.com.cn/upload/image_hosting/y5ebrbrg.png)

（这是 $k=1$ 的情况。）

选一个格子 $(x,y)$ 意味着 $a_x=y$，显然如果选了一个格子，那么与其同行或同列的格子就由于与其冲突而不能选，我们的目标是选出 $i$ 个灰色格子。

给冲突的格子画上边：

![](https://cdn.luogu.com.cn/upload/image_hosting/sphmjdlz.png)

显然这是几条链的形式，$f(i)$ 即求大小为 $i$ 的独立集个数。

对每条链分别考虑，我们知道一条点数为 $n$ 的链上取出 $m$ 个互不相邻的点的方案数为 $\dbinom{n-m+1}{m}$。

然后暴力卷积就做完了。

[link.](https://atcoder.jp/contests/agc005/submissions/38877911)

---

## 作者：cirnovsky (赞：2)

做一步容斥让 $\forall i,|p(i)-i|\neq k$ 的限制弱化成大于等于，即设 $f(x)$ 为排列中至少有 $x$ 个索引 $i$ 满足 $|p(i)-i|=k$ 的方案数，答案即 $\sum\limits_{i=0}^n(-1)^if(i)$。接下来考虑如何求解 $f(x)$。

若根据一些置换群（当然和这题没关系）的套路把 $i\rightarrow p(i)$ 的边连出来，你会发现这里面是一些链。

不妨把链拍在一个序列上，设 $g(i,j,1/0)$ 表示前 $i$ 个点，连了 $j$ 条边，第 $i$ 个点和第 $i-1$ 个点是否连边的方案数，转移显然。

于是答案即 $\sum\limits_{i=0}^n(-1)^i(g(2n,i,0)+g(2n,i,1))(n-i)!$，意义可见。

---

## 作者：Infiltrator (赞：2)


最开始不难想到这题应该是用容斥去做  
设g[i]表示至少i个位置是冲突的方案数  
那么答案就是
$$
\sum_{i=0}^n(-1)^i g[i] (n-i)!
$$  
首先可以发现一个显然的性质，每个排列里的点最多只有两个点和它冲突(根据绝对值的性质  
那么一个很妙的方法就是我们把和一个点冲突的点连边  
这样就形成了一张图，这张图有一些很妙的性质  
首先这是一张二分图，它的两个子集里都有n个节点
我们尝试画出这个二分图
以样例"3 1"为例
>$(A_1,B_2)$  
>$(A_2,B_1)$  
>$(A_2,B_3)$  
>$(A_3,B_2)$  

我们发现这张二分图里的一些边连接在一起就形成了一些链，现在我们把这些链提出来
下面这个样子
>$A_1->B_2->A_3$  
>$B_1->A_2->B_3$  

接着很显然可以看出这些链是互不影响的且每条链上只能选择一条边  
那么我们可以对图进行重构,将它按%k的余数重新排列(因为只在%k相同的情况下存在连边  
这样的话记录边就只用记录这个点和上个点有没有连边就行  
接着开始dp
重构图之后一共有n*2个点  
设dp[i][j][0]表示前i个点,选择了j条边,i和i-1有连边的方案数
dp[i][j][1]表示前i个点,选择了j条边,i和i-1没有连边的方案数
接着可以推出dp式子
>dp[i][j][0]=dp[i-1][j-1][0]+dp[i-1][j-1][1]  
>dp[i][j][1]=dp[i-1][j-1][0] 如果i和i-1有连边  

注意不能选择相邻的两条边因为同一个位置只能有一个数值  
那么g[i]=dp[n\*2][i][0]+dp[n\*2][i][1]  
最后容斥即可
# CODE
```cpp
#include <iostream>
#include <cstdio> 
#include <cstring>
using namespace std;
#define MOD 924844033
#define ll long long
#define N 2050
ll dp[N<<1][N][2],n,k,link[2*N],tot,sum,jc[N];
int main()
{
	scanf("%lld%lld",&n,&k);
	jc[0]=1;dp[0][0][0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%MOD; 
	for(int i=1;i<=k;i++)
		for(int t=1;t<=2;t++)
			for(int j=i;j<=n;j+=k)
				j!=i?link[++tot]=1:++tot;
	for(int i=1;i<=tot;i++)
		for(int j=0;j<=n;j++)
		{
			dp[i][j][0]=(dp[i-1][j][1]+dp[i-1][j][0])%MOD;
			if(link[i])dp[i][j][1]=dp[i-1][j-1][0];
	 	}
	for(int i=0;i<=n;i++)
	{
		ll tmp=(dp[n<<1][i][0]+dp[n<<1][i][1])%MOD;
		tmp=tmp*jc[n-i]%MOD;
		i%2==1?sum=((sum-tmp)%MOD+MOD)%MOD:sum=(sum+tmp)%MOD;
	}
	printf("%lld",sum);
	return 0;
}
```

---

## 作者：Fading (赞：1)

口胡一个不知道对不对的$O(n\log_2n)$生成函数解法，感觉其他人都思维定式了。

首先二项式反演一定要（容斥）。我们设$f_i$表示强制固定$i$个位置满足$|P_j-j|=k$，这个大家都会。

然后我们画一个二分图，左部点表示$i$，右部点表示$P_i$的取值，这个可以看其他题解。

问题转化成了求有多少种二分图匹配满足其大小$=i$。

首先这个二分图是由$2K$条链构成的（假设一个点也是一条链）我们发现链和链之间毫无关联，也就是说我们可以用乘法原理，对于每条链求出答案，用背包合并就可以了。

接下来就和他们完全不一样：

一条有$i$条边的链的大小为$j$的匹配数是

$$C_{i-j+1}^{j}$$

~~也就是说我们连dp都不用~~

那么构造生成函数

$$F_n=\sum_{i=0}^{\infty}C_{n-i+1}^ix^i$$

$f_i$就是$2K$条链的生成函数之积的第$i$项。

然后怎么搞呢？~~分治FFT~~

发现链长只有$2$种。所以我们直接用多项式快速幂求出幂次的生成函数，两者卷积一下就可以了。

时间复杂度$O(n\log_2n)$。

有谁用这种解法过的？不知道是不是新解法...

upd：不需要多项式快速幂，由于最终的生成函数的项数是$O(n)$的，直接对$FFT$点值进行快速幂就行了。

---

## 作者：bai_tang (赞：0)

只要有信念，就一定能成功！
- 吐槽一下，很难想象我当时做这题的精神状态。

### [题意](https://www.luogu.com.cn/problem/AT_agc005_d)
给定 $n,k$，求出长度为 $n$ 的排列，满足不存在 $|p_i-i|=k$  的情况的方案数，$0<k<n\le 2\times 10^3$，答案对 $441\times 2^{21}+1$ 取模。

### 分析
其实我们也可以算恰好 $m$ 个不满足的。

考虑一种套路是棋盘问题，那么我们假设往棋盘的禁止位置放 $m$ 个棋子，满足排列性质的方案为 $f(m)$，那么由容斥可得答案：
$$\sum_{m\ge 0}f(m)(-1)^m(n-m)!$$
怎么算排列方案数呢？其实很简单，由于这个容斥系数比较不太好搞，所以就不搞，直接算方案数。

容易发现，问题按照模 $2k$ 分成了多个不同的链，我们可以对每个链单独计算贡献，然后再卷起来，[代码](https://www.luogu.com.cn/paste/uh05r1gz)。

---

## 作者：daniEl_lElE (赞：0)

## 思路

考虑 $dp_{i,j}$，表示看到第 $i$ 位，强制 $j$ 位 $|P_i-i|=k$ 的方案数。

转移的话，$dp_{i,j}$ 可以从 $dp_{i-k,j}$ 转移。

为了方便转移，我们可以考虑定义 $dp_{i,j,0/1,0/1}$ 表示 $i$ 位是否被占，$i+k$ 位是否被占。转移的时候我们可以考虑 $P_i=i-k,P_i=i+k$ 或均不是。这样计算 $dp$ 复杂度是 $O(n^2)$ 的。

发现有 $k$ 个不同的分离的部分，我们考虑使用类似合并的思想去计算 $f_{j}$ 表示整个序列选了 $j$ 个强制要求 $|P_i-i|=k$ 的位置。使用类似树上依赖背包的证明可知复杂度是 $O(n^2)$ 的。

最后进行容斥，容易计算出没有 $|P_i-i|=k$ 方案数。CF285E 题也是类似的思路 。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls i*2
#define rs i*2+1
#define Ls ls,l,mid
#define Rs rs,mid+1,r
using namespace std;
const int mod=924844033;
int dp[2005][4005][2][2],f[4005];
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int fac[100005],inv[100005];
void init(){
	fac[0]=1;
	for(int i=1;i<=100000;i++) fac[i]=fac[i-1]*i%mod;
	inv[100000]=qp(fac[100000],mod-2);
	for(int i=99999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<j||i<0||j<0) return 0;
	return fac[i]*inv[j]%mod*inv[i-j]%mod;
}
signed main(){
	init();
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		if(i<=k){
			dp[i][0][0][0]=1;
			dp[i][1][0][1]=1;
			continue;
		}
		for(int j=0;j<=n;j++){
			//dp i-k j 0 0
			dp[i][j+1][0][0]=(dp[i][j+1][0][0]+dp[i-k][j][0][0])%mod;
			dp[i][j+1][0][1]=(dp[i][j+1][0][1]+dp[i-k][j][0][0])%mod;
			dp[i][j][0][0]=(dp[i][j][0][0]+dp[i-k][j][0][0])%mod;
			//dp i-k j 0 1
			dp[i][j+1][1][0]=(dp[i][j+1][1][0]+dp[i-k][j][0][1])%mod;
			dp[i][j+1][1][1]=(dp[i][j+1][1][1]+dp[i-k][j][0][1])%mod;
			dp[i][j][1][0]=(dp[i][j][1][0]+dp[i-k][j][0][1])%mod;
			//dp i-k j 1 0
			dp[i][j+1][0][1]=(dp[i][j+1][0][1]+dp[i-k][j][1][0])%mod;
			dp[i][j][0][0]=(dp[i][j][0][0]+dp[i-k][j][1][0])%mod;
			//dp i-k j 1 1
			dp[i][j+1][1][1]=(dp[i][j+1][1][1]+dp[i-k][j][1][1])%mod;
			dp[i][j][1][0]=(dp[i][j][1][0]+dp[i-k][j][1][1])%mod;
		}
	}
	f[0]=1;
	for(int i=n-k+1;i<=n;i++){
		int f2[4005];
		memset(f2,0,sizeof(f2));
		for(int j=0;j<=((n+k)/k)*(i-(n-k)-1);j++){
			for(int l=0;l<=((n+k)/k);l++){
				f2[j+l]=(f2[j+l]+f[j]*(dp[i][l][0][0]+dp[i][l][1][0]))%mod;
			}
		}
		for(int j=0;j<=((n+k)/k)*(i-(n-k));j++){
			f[j]=f2[j];
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		if(i%2==0) ans=(ans+f[i]*fac[n-i])%mod;
		else ans=(ans+mod-f[i]*fac[n-i]%mod)%mod;
	} 
	cout<<ans; 
	return 0;
}
```

---

## 作者：1saunoya (赞：0)

每一个点只能对两个点连边。

大概是这样。

然后不难想到。

$g_i$ 为冲突大于等于 $i$ 的方案数。

最后容斥就可以了。

然后考虑怎么求 $g_i$。

我们考虑拆成若干条链。

$a_{i-2k}, i-k, a_i, i + k...$

这样就变成了 $2n$ 个点，其中 $2n-1$ 条边。

但是不能选同一条链上的方案数。

最后容斥就做完了。

```cpp

/*
 _      _  _ _ _ _ _   _      _
\_\   /_/ \_\_\_\_\_\ \_\   /_/
 \_\ /_/      \_\      \_\ /_/
  \_\_/       \_\       \_\_/
   \_\         \_\       \_\
   \_\     \_\ \_\       \_\
   \_\      \_\\_\       \_\
*/
#include <bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rp(i,y) for(int i=1;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define pr(i,y) for(int i=y;i>=1;i--)
#define sz(v) (int)v.size()
using namespace std;
const int SIZE=1<<26;
char gc[SIZE],*pgc=gc;
char pc[SIZE],*ppc=pc;
clock_t clk=clock();
struct flusher{
	flusher(){
#ifdef WHX_TXDY
		freopen("fuck.in","r",stdin);
#endif
		fread(gc,true,SIZE,stdin);
	}
	~flusher(){
		fwrite(pc,true,ppc-pc,stdout);
#ifdef WHX_TXDY
		std::cerr<<"TIME:"<<(clock()-clk)/1000.<<"s\n";
#endif
	}
}Flusher;
int _Neg=0;
template<class T>
void rd(T&x){
	x=_Neg=0;
	while(!isdigit(*pgc)){
		if((*pgc++)=='-'){
			_Neg=1;
		}
	}
	while(isdigit(*pgc)){
		x=x*10+*pgc++-48;
	}
	if(_Neg){
		x=-x;
	}
}
int _Stk[233],_Top=0;
template<class T>
void pt(T x,char c='\n'){
	if(x<0){
		*ppc++='-';
		x=-x;
	}
	do{
		_Stk[++_Top]=x%10;
		x/=10;
	}while(x);
	while(_Top){
		*ppc++=_Stk[_Top--]+48;
	}
	*ppc++=c;
}
void pts(const string&str){
	int len=sz(str);
	rep(i,0,len-1){
		*ppc++=str[i];
	}
	*ppc++='\n';
}
template<class T>
void cmax(T&x,const T&y){
	x=(x>y)?x:y;
}
template<class T>
void cmin(T&x,const T&y){
	x=(x<y)?x:y;
}
int n, k;
const int N = 4e3 + 5;
int f[N][N][2];
bool vis[N];
int tmp[N];
int cnt = 0;
int fac[N + 1];

const int P = 924844033;

int mul(int x, int y) {
	return 1ll * x * y % P;
}
void init() {
	fac[0] = 1;
	rp(i,N) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
}

void upd(int&x, const int &y) {
	x += y;
	if (x >= P){
		x -= P;
	}
}

int main() {
	init();
	rd(n);
	rd(k);
	rp(i,k){
		rp(t,2){
			for(int j=i;j<=n;j+=k){
				++cnt;
				if (i != j) {
					vis[cnt] = 1;
				}
			}
		}
	}
	assert(cnt == 2 * n);
	f[0][0][0] = 1;
	rp(i,cnt) {
		rep(j,0,n) {
			upd(f[i][j][0] = f[i - 1][j][0], f[i - 1][j][1]);
			if (vis[i] && j) {
				f[i][j][1] = f[i - 1][j - 1][0];
			}
		}
	}
	int ans = 0, sgn = 1;
	rep(i,0,n){
		int tmp = f[cnt][i][0];
		upd(tmp, f[cnt][i][1]);
		if (sgn == 1) {
			upd(ans, mul(fac[n - i], tmp));
		} else {
			upd(ans, P - mul(fac[n - i], tmp));
		}
		sgn ^= 1;
	}
	pt(ans);
	return 0;
}
```

---

