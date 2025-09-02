# [ABC321G] Electric Circuit

## 题目描述

有 $N$ 个编号为 $1$ 到 $N$ 的部件和 $M$ 根电缆，打算用它们制作电路。这些部件上共有 $M$ 个红色端子和 $M$ 个蓝色端子，第 $i$ 个红色端子在部件 $R_i$ 上，第 $i$ 个蓝色端子在部件 $B_i$ 上。每根电缆连接一个红色端子和一个蓝色端子。特别地，允许连接同一个部件上的两个端子。同时，一个端子不能连接超过一根电缆。因此，$M$ 根电缆的所有连接方式共有 $M!$ 种（注意电缆之间不区分）。

将部件视为顶点，电缆视为边，把这个电路看作一个图，记其连通分量数为 $s$。从 $M!$ 种电缆连接方式中随机选择一种时，$s$ 的期望值是多少？请将结果对 $998244353$ 取模后输出。

  关于对 $998244353$ 取模的期望值  
  可以证明，所求期望值一定是有理数。在本题的约束下，设其化为最简分数 $\frac{P}{Q}$，则存在唯一的整数 $R$ 满足 $R\times Q\equiv P\pmod{998244353}$ 且 $0\leq R<998244353$。请输出这个 $R$。

## 说明/提示

## 限制

- $1\leq N\leq 17$
- $1\leq M\leq 10^5$
- $1\leq R_i, B_i\leq N$
- 输入均为整数

## 样例解释 1

用 $(i, j)$ 表示第 $i$ 个红色端子和第 $j$ 个蓝色端子用电缆连接的情况。
- $(1,1), (2,2)$ 的情况下：形成 $\lbrace 1,3\rbrace$ 和 $\lbrace 2\rbrace$ 两个连通分量，所以 $s=2$。
- $(1,2), (2,1)$ 的情况下：整体为一个连通分量，所以 $s=1$。

因此，$s$ 的期望值为 $\frac{3}{2}\equiv 499122178\pmod{998244353}$。

## 样例解释 2

无论如何连接，$s=N$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2
1 2
3 2```

### 输出

```
499122178```

## 样例 #2

### 输入

```
17 5
1 1 1 1 1
1 1 1 1 1```

### 输出

```
17```

## 样例 #3

### 输入

```
8 10
2 4 7 1 7 6 1 4 8 1
5 1 5 2 5 8 4 6 1 3```

### 输出

```
608849831```

# 题解

## 作者：樱雪喵 (赞：20)

吃一车罚时，输麻了。

## Description

给两个长度为 $m$，值域为 $[1,n]$ 的数列 $A,B$。定义一种合法匹配为 $A$ 中的每个下标和 $B$ 一一匹配，并将这 $m$ 对 $(A_i,B_j)$ 分别连边。易知一共有 $m!$ 种不同的匹配。

同一个数视为同一个点，求随机一个匹配，期望形成的连通块个数。

$1\le n\le 17,1\le m\le 10^5$。

## Solution

也许做得有点麻烦？不过无所谓，能过。

观察到 $n\le 17$，这是一个经典状压 dp 的范围。所以我们考虑设 $f_i$ 表示 **点集 $i$ 与外面的点没有连边**，即点集 $i$ 独立存在的方案数。

这代表着，所有在点集 $s$ 中的 $A_i$ 都要恰好匹配一个在点集中的 $B_j$。那么，$f_i$ 不为的 $0$ 的充要条件为 $A,B$ 数组在点集中的权值出现次数相同（否则必然有一个点要跟点集外的点匹配）。此时它们之间任意匹配均合法，方案数为 $cnt!$。

设 $g_i$ 表示点集 $i$ **恰好形成一个连通块** 的方案数。观察到 $g_i$ 本质就是 $f_i$ 除掉点集里有很多个不相交的连通块的情况。那么我们枚举最后一个连通块，有这样的式子：

$$
g_i=f_i-\sum_{j\subsetneq i} g_j \times f_{i\oplus j}
$$

观察到这个式子会重复计算，因为很多连通块各被钦定成了最后一个一次。那么我们钦定 **包含了集合内最小元素** 的连通块是最后一个即可。

现在我们求得了每个连通块出现的方案数，可以开始统计答案了。

设 $s_i$ 表示当前点集 $i$ 的 **所有方案的连通块数之和**。那么我们依旧枚举当前点集 **独立存在** 的最后一个连通块（同理钦定它包含最小元素），那么分别考虑新加入的连通块对方案数和连通块数量的贡献，有：

$$
s_i=\sum_{j\subsetneq i} s_{i\oplus j}\times g_j + f_{i\oplus j}\times g_j
$$

时间复杂度瓶颈在枚举子集，$O(3^n)$。

一开始写了设 $s_{i,j}$ 点集 $i$ 有 $j$ 个连通块的 $O(n3^n)$，T 得很惨，大家引以为戒。

```cpp
#define int long long
const int N=(1<<17)+5,mod=998244353;
int f[N],g[N],h[N],s[N];
int n,m,jc[N];
int a[N],b[N];
il int get(int x,int k) {return (x>>k)&1;}
il int qpow(int n,int k=mod-2)
{
    int res=1;
    for(;k;n=n*n%mod,k>>=1) if(k&1) res=res*n%mod;
    return res;
}
int tota[N],totb[N];
signed main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++) a[i]=read(),tota[a[i]]++;
    for(int i=1;i<=m;i++) b[i]=read(),totb[b[i]]++;
    jc[0]=1;
    for(int i=1;i<=m;i++) jc[i]=jc[i-1]*i%mod;
    for(int i=1;i<(1<<n);i++)
    {
        int cnta=0,cntb=0;
        for(int j=0;j<n;j++) if(get(i,j)) cnta+=tota[j+1],cntb+=totb[j+1];
        if(cnta!=cntb) continue;
        f[i]=jc[cnta];
    }
    for(int i=1;i<(1<<n);i++)
    {
        g[i]=f[i];
        int x=0;
        for(int j=0;j<n;j++) if(get(i,j)) {x=j;break;}
        for(int j=i-1;j;j=(i&(j-1)))
        {
            if(!get(j,x)) continue;
            g[i]=(g[i]-g[j]*f[i^j]%mod+mod)%mod;
        }
    }
    f[0]=1;
    for(int i=1;i<(1<<n);i++)
    {
        int x=0;
        for(int j=0;j<n;j++) if(get(i,j)) {x=j;break;}
        for(int k=i;k;k=i&(k-1))
        {
            if(!get(k,x)) continue;
            s[i]=(s[i]+s[i^k]*g[k]%mod+f[i^k]*g[k]%mod)%mod;
        }
    }
    int all=(1<<n)-1;
    cout<<s[all]*qpow(jc[m])%mod<<endl;
    return 0;
}
```

---

## 作者：是青白呀 (赞：7)

## 分析

首先不难想到用期望的线性性拆分贡献，转化为求每种不同的连通块会在多少种不同的连边方式中出现。加和后除以连边方式总数即为答案。

于是枚举每种不同的连通块，考虑如何计算它在多少种不同的连边方式中出现过，显然应该是内部连边方案数的乘上外部的连边方案数。设点集 $i$ 在内部连边后**形成一个连通块**的方案数为 $g_i$，发现它不好计算，但我们不难计算在一个点集内部连边的总方案数 $f_i$，于是可以容斥，减去它内部连边后**形成多个连通块**的方案数即可。

首先，我们统计一个点集 $i$ 中所有的点在 $R$ 序列中的总出现次数 $cntr_i$ 和在 $B$ 序列中的总出现次数 $cntb_i$。若 $cntr_i\neq cmtb_i$，则这个点集一定不能形成独立的连通块，$f_i=0$；否则 $f_i=cntr_i !$。

接下来考虑计算点集 $i$ 内部连边，形成多个连通块的方案数。我们可以考虑枚举点集 $i$ 的真子集 $j$ 作为其中的一个连通块。由于有多个连通块存在，为了避免每个连通块都被枚举到一次，导致算重，我们可以规定 $i$ 中最小的点必须在 $j$ 中也出现。则有 $g_i=f_i-\sum_j g_j\times f_{i\oplus j}$。只需要通过记忆化搜索算出 $g$ 的值即可。

最终答案不要忘记乘上外部任意连边的方案数。即为 $\displaystyle\frac{\sum_ig_i\times (m-cntr_i)!}{m!}$。

时间复杂度 $O(n2^n+3^n)$。

## Code
```cpp
#include<bits/stdc++.h> 
#define int long long
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define mp make_pair
#define fir first
#define sec second
#define pvv pair<vector<int>,vector<int>>
#define lowbit(x) x&-x
#define qingbai666 QwQ
using namespace std;
typedef long long ll;
const int N=20,M=1e5+5,S=(1<<17)+2,mo=998244353,inf=1e9+7;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
} 
int quick_power(int base,int x){
	int ret=1;
	while(x){
		if(x&1)ret*=base,ret%=mo;
		base*=base,base%=mo;
		x>>=1;
	}
	return ret;
} 
int n,m,r[M],b[M],f[S],g[S],tot,cntr[N],cntb[N],jc[M],cntot[S];
int dfs(int st){
	if(g[st]!=-1)return g[st];
	int low=lowbit(st),sum=0;
	for(int nw=st;nw;nw=st&(nw-1)){
	    if(nw==st)continue;
		if((nw&low)!=low)continue;
		sum+=dfs(nw)*f[st^nw]%mo,sum%=mo;
	}
	g[st]=(f[st]-sum+mo)%mo;
	return g[st];
}
signed main(){
	read(n),read(m),tot=(1<<n)-1;
	jc[0]=1;
	rep(i,1,m)
	    jc[i]=jc[i-1]*i%mo;
	rep(i,1,m)
	    read(r[i]),cntr[r[i]]++;
	rep(i,1,m)
	    read(b[i]),cntb[b[i]]++;
	rep(i,1,tot){
		g[i]=-1;
		int rnum=0,bnum=0;
		rep(j,1,n){
			if(!((i>>(j-1))&1))continue;
			rnum+=cntr[j],bnum+=cntb[j];
		}
		if(rnum!=bnum)continue;
		f[i]=jc[rnum],cntot[i]=jc[m-rnum];
	}
	int ans=0;
	rep(i,1,tot)
		ans+=dfs(i)*cntot[i]%mo,ans%=mo;
	printf("%lld",ans*quick_power(jc[m],mo-2)%mo);
	return 0;
} 
```

---

## 作者：shinkuu (赞：6)

其实赛时可能可以做出来的，只是打了前 6 道想下班了，有点小小遗憾。

首先问题看起来很唬人，考虑转换一下。考虑已经固定 $m$ 条边，对于一个集合 $S$，什么时候会不与其他点有边。容易发现，此时需要满足 $\sum[R_i\in S]=\sum [B_j\in S]$。记这个数为 $c_S$。但是这还不够，因为 $S$ 中点连边方案数还没有计算。

这个答案显然不是 $c_S!$。因为 $S$ 可能可以分成两个集合 $s,t$ 都满足上述条件，则会重复计算。考虑如何去重。设 $dp_s$ 为集合 $S$ 的答案。我们钦定 $t$ 包含 $S$ 里最小的元素，则有 $dp_s=c_s!-\sum_{t\in S} dp_t\times (c_s-c_t)!$。

然后怎么办呢？

作者表示再做一遍 dp，$O(m3^m)$ 解决。还真过了。

但是事实上 $ans=\sum dp_s\times (m-c_s)!$。解决。

code：

```cpp
int n,m,e[23],d[23],f[N],g[N],h[N],c[N];
il int Mod(int x,int y){return x+y>=mod?x+y-mod:x+y;}
il int lowbit(int x){return x&(-x);}
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;y>>=1;
	}
	return ret;
}
void Yorushika(){
	scanf("%d%d",&n,&m);
	f[0]=1;
	rep(i,1,m){
		int x;scanf("%d",&x);
		e[x]++;
		f[i]=1ll*f[i-1]*i%mod;
	}
	rep(i,1,m){
		int x;scanf("%d",&x);
		d[x]++;
	}
	const int k=1<<n;
	int ans=0;
	rep(i,1,k-1){
		rep(j,0,n-1){
			g[i]+=e[j+1]*(i>>j&1);
			h[i]+=d[j+1]*(i>>j&1);
		}
		if(g[i]!=h[i])
			continue;
		c[i]=f[g[i]];
		for(int j=(i-1)&i;j;j=(j-1)&i){
			if(g[j]!=h[j]||lowbit(i)!=lowbit(j))
				continue;
			c[i]=Mod(c[i],mod-1ll*c[j]*f[g[i]-g[j]]%mod);
		}
		ans=Mod(ans,1ll*c[i]*f[m-g[i]]%mod);
	}
	printf("%lld\n",1ll*ans*qpow(f[m],mod-2)%mod);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：SoyTony (赞：5)

一个经典的连通容斥。

看到数据范围容易想到一个 $O(3^n)$ 的枚举子集，问题现在变成求一个中间点集合 $S$ 连通的方案数，设为 $h_S$，首先 $S$ 的红蓝点个数应当相等，记作 $sum_S$，容斥枚举 $\mathrm{lowbit}(S)=x$ 所在集合 $T$，形如：

$$h_S=sum_S!-\sum_{T\subsetneq S,x\in T} h_T\times sum_{S\setminus T}!$$

之后就是把连通块拼起来，设 $f_S$ 为连通块个数总和，$g_S$ 为总方案数，这里防止算重也要加入 $\mathrm{lowbit}(S)=x$ 所在集合 $T$，形如：

$$f_S\leftarrow f_{S\setminus T}\times h_T+g_{S\setminus T}\times h_T$$

$$g_S\leftarrow g_{S\setminus T}\times h_T$$

答案就是 $\frac{1}{m!}f_S$。

提交记录：[Submission - AtCoder](https://atcoder.jp/contests/abc321/submissions/45871383)

---

## 作者：Zi_Gao (赞：4)

## 前言

没怎么写过概率、期望的题，做不了一点。并且感觉其他题解写的有点简略了，有点看不懂，结合自己的理解记录一下。

## 正文

### 0x00 题目分析

简述一下题意：给定一个 $2m+n$ 个点的无向图，其中有 $m$ 个红色点、$m$ 个蓝色点、$n$ 个黑色点，每个红或蓝点连接了一个黑色点，现在你要连接 $m$ 条边，使得每个红点连接了一个蓝点，并且每个蓝点连接了一个红点。相当于是一个排列，求随机连出来这个图期望联通分量个数。

发现这个题每一个黑点连接哪些蓝点和红点是不重要的，只需要关注每一个黑点连接了几个蓝点和红点就可以了，那么后续的讨论本质是对黑点的讨论，并且黑点的数量十分少。不妨记 $R_i$ 表示 $i$ 这个黑点连接的红点数量；$B_i$ 表示 $i$ 这个黑点连接的蓝点数量。

### 0x01 拆分贡献

发现这个题是求期望，那么要想到期望的性，当然比较重要的就是期望的线性性，也正是这个题的入手点。相当于是把一个整体计算性的问题，拆分成了一个一个小的局部问题计算贡献，而把大问题转化为小问题，往往就是突破题目的关键。

具体来说就是先把分母算完，分母很多时候更好就算，对于拆分出来的一个小局部问题，对分母的贡献就是，这个局部的答案乘上包含这个局部的情况数量，最后除一下总的情况数量就是分母，就可以了。

不妨先考虑每一个黑点子集 $S$ 能否恰好构成一个独立的连通分量，也就是 $S$ 中的点不会向外部连边并且 $S$ 连通，这样就可以只关注这一个连通分量了。满发现这个事情的必要条件的是：

$$\sum_{i\in S}R_i=\sum_{i\in S}B_i$$

记整数是 $d_S$，显然这个东西不是充分条件，因为这个子集内部还可能分成两个联通分量，这样并不好统计贡献，但是这个东西至少保证了 $S$ 不与外部连边。

### 0x02 算方案数

先看看这个子集可能形成恰好一个联通分量的方案数有多少，记这个值是 $dp_s$，也就是子集内部的方案数，不考虑外面，显然最多有 $d_S!$，但是这个只是上界，考虑把多的方案减出去。尝试枚举每一个 $S$ 的子集 $T$，若 $T$ 恰好形成一个单独的联通分量时对 $d_s!$ 的贡献有多少，这个值是：

$$dp_T\times(d_T-d_S)!$$

可以理解为，$T$ 自己形成一个联通分量的方案数，这时不管外边怎么连边它 $S$ 都至少有两个联通分量。但是这个式子还是会算重，具体来说就是 $S$ 形成多个连通分量时，其中每个连通分量都会被计算一次，这肯定是不想看到的，钦定这个 $T$ 时多个连通分量的最后一个连通分量，有一个好的方式就是钦定 $T$ 包含 $S$ 中编号最小的那个点，这样显然不会重复计算了，并也不会算少，因为 $T'$ 只要不包含 $S$ 的最小编号的那个点，这个 $T'$ 成为一个连通分量时的答案已经在 $T$ 包含 $S$ 的最小编号的那个点的 $T$ 时计算了。当然不一定时最小编号的那个点，其他都可以只是这样比较方便。最后得出一个式子：

$dp_T=d_S!-\sum_{T\in S,Smin\in T} dp_T\times(d_T-d_S)!$

### 0x03 算贡献

算了方案数还没算贡献呢，其实这里和算 $dp_T$ 的思路很像，最终 $S$ 对分母的贡献就是：

$$dp_S\times d_S!$$

但是这里不会算重，因为算的时期望的贡献，对于每个联通分量他就会贡献 $1$ 的答案。最终答案就是：

$$\frac{\sum_S dp_S\times d_S!}{m!}$$

### 0x04 代码实现

写起来很简单，跑得也很快，时间复杂度 $\mathcal{O}\left(m3^m\right)$ 。

AC CODE

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

#define INV_DATA_TYPE long long
INV_DATA_TYPE exgcd(INV_DATA_TYPE a,INV_DATA_TYPE b,INV_DATA_TYPE&x,INV_DATA_TYPE&y){if(!b){x=1;y=0;return a;}INV_DATA_TYPE d=exgcd(b,a%b,y,x);y-=a/b*x;return d;}INV_DATA_TYPE inv(INV_DATA_TYPE n,INV_DATA_TYPE p){INV_DATA_TYPE x,y;exgcd(n,p,x,y);x%=p;return x>=0?x:x+p;}

const long long mod=998244353;
int rsiz[1<<17],bsiz[1<<17],rdeg[17],bdeg[17];
long long fact[100010],dp[1<<17];

int lowbit(int x){return x&-x;}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i,s,maxs,subs;
    register long long res=0;
    int n=read();
    int m=read();
    fact[0]=1;
    for(i=1;i<=m;++i) fact[i]=fact[i-1]*i%mod;
    for(i=0;i<m;++i) ++rdeg[read()-1];
    for(i=0;i<m;++i) ++bdeg[read()-1];
    maxs=1<<n;
    for(s=1;s<maxs;++s){
        for(i=0;i<n;++i)
            if((s>>i)&1)
                rsiz[s]+=rdeg[i],
                bsiz[s]+=bdeg[i];
        if(rsiz[s]!=bsiz[s]) continue;
        dp[s]=fact[rsiz[s]];
        for(subs=s&(s-1);subs;subs=(subs-1)&s){
            if(lowbit(subs)!=lowbit(s)||rsiz[subs]!=bsiz[subs]) continue;
            (dp[s]+=mod-dp[subs]*fact[rsiz[s]-rsiz[subs]]%mod)%=mod;
        }
        (res+=dp[s]*fact[m-rsiz[s]])%=mod;
    }

    print(res*inv(fact[m],mod)%mod);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

## 总结

抓住概率和期望的性质，对问题进行拆分贡献，可以尝试选择用总的方案数减去不合法方案数，这样的结构对问题进一次拆分简化问题。

---

## 作者：tytyty (赞：2)

### $\text{Solution}$

$b$ 序列一共有 $m!$ 种重排方案。所以问题转化为：

给你 $n$ 个点和两个长度为 $m$ 的序列 $r,b$，表示点 $r_i$ 向点 $b_i$ 连一条边。你可以将 $b$ 序列重排，求所有连边方案的连通块个数和。最后除 $m!$ 即为期望。

我们肯定不能对每个序列求答案，所以考虑计算每个连通块对答案的贡献。$n\leq 17$ 容易想到状压，枚举子集。

设 $cr_i=\sum\limits_j[r_j=i],cb_i=\sum\limits_j[b_j=i],R(S)=\sum\limits_{i\in S} cr_i,B(S)=\sum\limits_{i\in S}cb_i$。

设 $f(S)$ 表示点集 $S$ 为一个独立连通块的方案数。你发现这说明点集 $S$ 里的点只能在内部连边，也就是 $R(S)=B(S)$。在集合内连边的总方案数为 $R(S)!$，要减去 $S$ 是若干独立连通块的情况，枚举独立的连通块 $T$，**经典钦定 $lowbit(S)\in T$ 去重一种方案被多个子集枚举到。**

$$
f(S)=R(S)!-\sum\limits_{T,lowbit(S)\in T} f(T)\times R(S/T)!
$$

一开始我以为这样就做完了，但是把若干连通块拼起来，方案数应该要乘起来。

我觉得比较自然的应该是先想到设 $g(S,i)$ 表示将 $S$ 拆成 $i$ 个连通块的方案数复杂度为 $O(n3^n)$。

发现不能枚举个数，转而直接求个数和，设 $g(S)$ 表示 $S$ 拆成若干连通块的不同方案的块数之和。枚举 $T$ 作为新加入一个独立连通块。

$$
g(S)=\sum\limits_{T,lowbit(S)\in T}f(T)\times R(S)!+g(S/T)\times f(T)
$$

$g(S)$ 即为所求，复杂度 $O(3^n)$。

### $\text{Code}$
                                  
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define cout cerr
#define debug cout<<"debug"<<endl;
using namespace std;
const int N=18;
const int M=1e5+5;
const int mod=998244353;
int n,m,r[M],b[M],lim;
int cr[N],cb[N],R[1<<N],B[1<<N];
ll f[1<<N],g[1<<N],fac[M];
inline int read() {
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=1; ch=getchar();}
	while(isdigit(ch)) {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return f?-x:x;
}
inline void inc(ll &x,int y) {x+=y-mod;x+=(x>>63)&mod;}
inline void init() {
	fac[0]=1;
	for(int i=1;i<=m;i++) fac[i]=1LL*fac[i-1]*i%mod;
}
inline ll qpow(ll x,int y) {
	ll ret=1;
	while(y) {
		if(y&1) ret=ret*x%mod;
		x=x*x%mod,y>>=1;
	}
	return ret;
}
inline int lowbit(int x) {return x&(-x);}
int main()
{
	n=read(),m=read();
	init();
	for(int i=1;i<=m;i++) r[i]=read(),cr[r[i]]++;
	for(int i=1;i<=m;i++) b[i]=read(),cb[b[i]]++;
	lim=1<<n;
	for(int i=1;i<lim;i++) {
		for(int j=1;j<=n;j++) {
			if(i>>(j-1)&1) R[i]+=cr[j],B[i]+=cb[j];
		}
	}
	for(int s=1;s<lim;s++) {
		if(R[s]!=B[s]) continue;
		f[s]=fac[R[s]];
		for(int t=s&(s-1);t;t=s&(t-1)) {
			if(lowbit(s)&t) {
				inc(f[s],mod-f[t]*fac[R[s^t]]%mod);
			}
		}
	}
	for(int s=1;s<lim;s++) {
		g[s]=f[s];
		for(int t=s&(s-1);t;t=s&(t-1)) {
			if(lowbit(s)&t) {
				inc(g[s],(f[t]*fac[R[s^t]]%mod+f[t]*g[s^t]%mod)%mod);
			}
		}
	}
	printf("%lld",g[lim-1]*qpow(fac[m],mod-2)%mod);
	return 0;
}
                                  
```

---

## 作者：喵仔牛奶 (赞：1)

## Solution

没咋看懂其它题解在干啥。

设 $f_{S}$ 表示 $S$ 不和外面连边的**方案数**，考虑求出 $f$。对于一个 $S$，设 $A_S$ 为有多少 $a_i$ 在 $S$ 中，$B_S$ 为有多少 $b_i$ 在 $S$ 中。显然，$f_S=A_S!\cdot[A_S=B_S]$，原因是在 $S$ 内的 $a_i$ 能且仅能和 $S$ 内的 $b_i$ 匹配，$b_i$ 连 $a_i$ 也一样。

为什么要求方案数呢？因为方案数组合起来是相乘的，因此设 $g_{S}$ 表示 $S$ 是一整个连通块（不和外面连边且连通）的**方案数**，有 $g=\ln f$。

设 $h_S$ 为 $S$ 是一整个连通块的**概率**，有 $\displaystyle h_S=\frac{g_S\cdot(m-A_S)!}{m!}$。根据期望线性性，答案即为 $\sum h_S$。

复杂度 $\mathcal O(n^22^n)$。

## Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace math { ... }
namespace Milkcat {
	using namespace math;
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 17, M = 1 << N, mod = 998244353;
	typedef mint<mod> MI;
	int n, m, k, x, A[M], B[M]; MI rs, fac[M], f[M], g[M];
	void fwt(auto f, int n, int o) {
		REP(i, 0, n - 1) REP(j, 0, (1 << n) - 1)
			if (j >> i & 1) f[j] += f[j ^ 1 << i] * o;
	}
	int ppc(int x) { return __builtin_popcount(x); }
	void ln(MI* f, MI* g, int n) {
		static MI A[N + 1][1 << N], B[N + 1][1 << N];
		int m = (1 << n); memset(g, 0, m * 4);
		REP(i, 0, m - 1) A[ppc(i)][i] = f[i];
		REP(i, 0, n) fwt(A[i], n, 1);
		REP(i, 1, n) {
			REP(j, 1, i - 1) REP(S, 0, m - 1)
				B[i][S] += B[j][S] * A[i - j][S] * j;
			MI iv = (MI)1 / i;
			REP(S, 0, m - 1) B[i][S] = A[i][S] - B[i][S] * iv;
		}
		REP(i, 0, n) fwt(B[i], n, -1);
		REP(i, 0, m - 1) g[i] = B[ppc(i)][i];
		REP(i, 0, n) memset(A[i], 0, m * 4), memset(B[i], 0, m * 4);
	}
	int main() {
		cin >> n >> k, m = (1 << n), fac[0] = 1;
		REP(i, 1, k) cin >> x, A[1 << (x - 1)] ++;
		REP(i, 1, k) cin >> x, B[1 << (x - 1)] ++;
		REP(i, 1, k) fac[i] = fac[i - 1] * i;
		fwt(A, n, 1), fwt(B, n, 1);
		REP(i, 0, m - 1)
			f[i] = (A[i] == B[i] ? fac[A[i]] : 0);
		ln(f, g, n);
		REP(i, 0, m - 1)
			rs += g[i] * fac[k - A[i]];
		cout << rs / fac[k] << '\n';
		return 0;
	}
}
```

---

## 作者：Erine (赞：1)

独立写出来的，终于会一点数数题了。

首先期望转求和，最后答案除以 $m!$。

拆贡献，枚举点集 $S$，计算使得 $S$ 是一个极大连通块的边排列数。令 $f_S$ 是这个值，同时令 $g_S$ 是存在几个极大连通块的并是 $S$ 的边重排方案数。注意这里的边只考虑 $u\in S, v\in S$ 的边。假设在 $a$ 序列中 $i\in S$ 的 $i$ 有 $sa_S$ 个，$b$ 序列有 $sb_S$ 个。显然的，$g_S=sb_S![sa_S=sb_S]$。

对于计算 $f_S$，考虑容斥。一开始总方案数为 $g_S$，枚举一个子集，钦定这个子集 $T$ 是一个极大连通块，则应该去掉的为 $f_Tg_{S/T}$。但是注意到这样会算重，因为同一种方案会被所有连通块都减一次，就寄了。于是我们钦定，$S$ 中的一个元素必须出现在 $T$ 里面，这样即可做到不重不漏。最后总和应该是 $\sum f_S(m-sa_S)!$。

---

## 作者：zhongpeilin (赞：1)

## 题目大意：
有一个长度为 $N$，值域为 $1 \sim m$ 的两个序列 A，B 现在将 B 任意排列，然后将 $A_{i}$ 连接 $B_{i}$，请问最后连通块的个数。  
## 解题思路：
首先 $m \leq 17$ 而 $n \leq 10^5$，所以突破口应该在 $m$ 上。  
虽然 $m$ 很小，但是不能直接枚举排列，但是可以 $2^{17}$ 的二进制枚举，也可以状压。 

因为我们求得是期望，B 是可以随便排的，所以我们只关心个数，不关心顺序，那么我们尝试设 $dp_{S}$ 表示值域为 $S$ 的期望连通块个数。  
因为求得是期望连通块个数，所以我们通过期望公式可得：所有方案的连通块个数除以 $n!$。  
所以我们可以将 dp 的状态变成总方案个数。  
那么转移就是枚举 $S$ 的一个子集，那么 $dp_{S} = $ S 合法匹配的方案数$- \sum_{T \subset S}dp_{T} \times (S - T)$ 合法匹配的方案数。  
但是这个是有问题的，因为举个简单的例子：当 $S$ 枚举到 $T$ 时，将 $S-T$ 是一个连通块的方案数算一遍，然后枚举到 $S-T$ 时，又将 $T$ 是一个连通块的答案算了一遍，共算了两遍。  
那为什么会出现这种情况呢？因为我们会枚举 $T$，也会枚举 $S-T$，也就是说我们枚举的子集中，会出现互为补集的情况。  
怎么处理呢？我们可以强行制定枚举的 $T$ 中一定包含某个数字，那么这样就不会出现补集了，为了方便，我们令他必须包含 $S$ 的最小元素。  
那么 dp 就被我们解决了，但是还有个合法匹配的方案数怎么求？这里因为只令他合法匹配，那么我们先判断这个值域的 A 和 B 的个数是否相同，如果相同就是在 A 中出现的次数的阶乘，如果不相同就是 `0`。  
答案就是 $\sum_{S} dp_{S} \times ({1 \sim m - S})$ 合法匹配的方案数。 

## CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 998244353;
inline int read(){
	int x = 0;
	char op = getchar();
	while(op < '0' || op > '9') op = getchar();
	while(op >= '0' && op <= '9'){
		x = x * 10 + (op - '0');
		op = getchar();
	}
	return x;
}

int qp(int a, int b){
	int ans = 1;
	while(b){
		if(b % 2) ans = ans * a % mod;
		a = a * a % mod;
		b /= 2;
	}
	return ans;
}
int jc[100005], dp[170000];
int n, m, a[100005], b[100005];
int cnta[20], cntb[20], Sa[170000], Sb[170005];
signed main(){
	m = read(); n = read();
	for(int i = 1; i <= n; i++){
		a[i] = read(), cnta[a[i]]++;
	}
	for(int i = 1; i <= n; i++){
		b[i] = read(); cntb[b[i]]++;
	}
	
	jc[0] = 1;
	for(int i = 1; i <= 100000; i++) jc[i] = jc[i - 1] * i % mod;
	
	for(int i = 0; i < (1 << m); i++){
		for(int j = 1; j <= m; j++){
			if((i & (1 << (j - 1)))){
				Sa[i] += cnta[j];
				Sb[i] += cntb[j];
			}
		}
	}
	
	int ans = 0;
	for(int i = 1; i < (1 << m); i++){
		if(Sa[i] != Sb[i]) continue;
		dp[i] = jc[Sa[i]];
		
		for(int j = ((i - 1) & i); j > 0; j = (i & (j - 1))){
			if((j & (i & (-i))) > 0 && Sa[j] == Sb[j]){
				dp[i] = (dp[i] - dp[j] * jc[Sa[i] - Sa[j]] % mod + mod) % mod;
			}
		}
		ans = (ans + dp[i] * jc[n - Sa[i]] % mod) % mod;
	}
	cout << ans * qp(jc[n], mod - 2) % mod << endl;
	return 0;
}

---

## 作者：Otomachi_Una_ (赞：0)

状压，$f_S$ 表示图中 $S$ 为一个极大连通块的概率。

首先要求 $a[S]=b[S]$。其中 $a[S]=\sum_{i=1}^n [a_i\in S]$。

首先 $a[S]$ 的点仅和 $b[S]$ 相连的概率就是 $\dfrac{1}{\binom{m}{a[S]}}$。然后只有一个连通块，可以容斥。随便找个 $i\in S$。枚举所有 $i\in T\subsetneq S$。然后减掉 $f_T\times\dfrac{1}{\binom{a[S]}{a[T]}}$ 即可。

---

## 作者：xpz0525 (赞：0)

### [ABC321G] Electric Circuit 题解

由于我们不可能枚举线缆连接方式，因此只能考虑每个联通块对答案的贡献。

令 $f_{st}$ 代表使 $st$ 联通（$st$ 的第 $i$ 位为 1 则代表第 $i$ 个组件在联通块内），且仅考虑 $st$ 内部连线的连线⽅案数。$cnt_{st}$ 为集合中的节点之间的连线⽅案数（不要求联通）。则答案为
$$
\frac {\sum \nolimits_{st} f_{st} \cdot cnt_{(2^N-1-st)}}{m!}
$$

$cnt_{st}$ 很好计算，只要 $st$ 中红蓝端点总数均为 $m$，那么 $cnt_{st} = m!$，否则为 0。

$f_{st}$ 如何计算呢？可以通过总的方案数减去存在多于 1 个联通块的方案数来计算。我们可以枚举 $st$ 的子集 $sub$（这里只枚举包含编号最大/最小的节点的子集，以避免重复计算），然后减去 $f_{sub} \cdot cnt_{st-sub}$（即 $sub$ 为其中一个包含编号最大/最小的节点的联通块，其他节点随意连接的方案数）。
#### 小Tips:
> 如何枚举子集？——见 [OI-WiKi](https://oi-wiki.org/math/binary-set/#子集遍历)

最后是 AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
ll qpow(ll x,int p){
    ll res=1;
    while(p){
        if(p&1)res=res*x%mod;
        p>>=1;
        x=x*x%mod;
    }
    return res;
}
ll inv(ll x){
    return qpow(x,mod-2);
}
int n,m;
ll fac[100001];
int r[17],b[17];
ll f[1<<17], cnt[1<<17];
int main(){
    cin>>n>>m;
    for(int i=1,x;i<=m;i++){
        cin>>x;
        r[x-1]++;
    }
    for(int i=1,x;i<=m;i++){
        cin>>x;
        b[x-1]++;
    }
    fac[0]=1;cnt[0]=1;
    for(int i=1;i<=m;i++)fac[i]=fac[i-1]*i%mod;
    for(int st=1;st<(1<<n);st++){
        int rcnt=0,bcnt=0;
        for(int j=0;j<n;j++){
            if(st&(1<<j)){
                rcnt+=r[j];
                bcnt+=b[j];
            }
        }
        if(rcnt==bcnt)cnt[st]=fac[rcnt];
    }
    ll ans=0;
    for(int st=1;st<(1<<n);st++){
        f[st]=cnt[st];
        for(int sub=(st-1)&st;sub>st-sub;sub=(sub-1)&st){
            f[st]=(f[st]-f[sub]*cnt[st-sub]%mod+mod)%mod;
        }
        ans=(ans+f[st]*cnt[(1<<n)-1-st]%mod)%mod;
    }
    ans=ans*inv(fac[m])%mod;
    cout<<ans<<endl;
}
```

---

## 作者：c1120241919 (赞：0)

提供不同的做法：

看到题解区都是容斥，这里提供一个不同的做法。

首先可以把这 $m$ 个点缩到 $n$ 个点上面，每个点对应的维护左部点和右部点的个数。

因为 $n$ 很小，考虑状压，发现需要求解一个集合的连通图计数。

发现不要求联通的图的数量很好算，记 $suml$ 表示这个集合左部点的个数之和，$sumr$ 同理。

那么方案数为：$[suml=sumr]\times suml!$。

和城市规划一个原理，对集合幂级数取 $\ln$ 即可求得集合内连通图的数量。

然后有一个很显然的 $3^nn$ 的状压，设 $f_{i,s}$ 表示选了点集为 $s$ 的点，有 $i$ 个连通块的方案数。

发现是子集卷积的形式，可以做到 $2^nn^3$。

实测能跑，但比 $3^n$ 要慢一些。

[提交记录](https://atcoder.jp/contests/abc321/submissions/55468187)

---

