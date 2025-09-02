# Cowmpany Cowmpensation

## 题目描述

Allen, having graduated from the MOO Institute of Techcowlogy (MIT), has started a startup! Allen is the president of his startup. He also hires $ n-1 $ other employees, each of which is assigned a direct superior. If $ u $ is a superior of $ v $ and $ v $ is a superior of $ w $ then also $ u $ is a superior of $ w $ . Additionally, there are no $ u $ and $ v $ such that $ u $ is the superior of $ v $ and $ v $ is the superior of $ u $ . Allen himself has no superior. Allen is employee number $ 1 $ , and the others are employee numbers $ 2 $ through $ n $ .

Finally, Allen must assign salaries to each employee in the company including himself. Due to budget constraints, each employee's salary is an integer between $ 1 $ and $ D $ . Additionally, no employee can make strictly more than his superior.

Help Allen find the number of ways to assign salaries. As this number may be large, output it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first sample case, employee 2 and 3 report directly to Allen. The three salaries, in order, can be $ (1,1,1) $ , $ (2,1,1) $ , $ (2,1,2) $ , $ (2,2,1) $ or $ (2,2,2) $ .

In the second sample case, employee 2 reports to Allen and employee 3 reports to employee 2. In order, the possible salaries are $ (1,1,1) $ , $ (2,1,1) $ , $ (2,2,1) $ , $ (2,2,2) $ , $ (3,1,1) $ , $ (3,2,1) $ , $ (3,2,2) $ , $ (3,3,1) $ , $ (3,3,2) $ , $ (3,3,3) $ .

## 样例 #1

### 输入

```
3 2
1
1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 3
1
2
```

### 输出

```
10
```

## 样例 #3

### 输入

```
2 5
1
```

### 输出

```
15
```

# 题解

## 作者：Marser (赞：16)

## 题意

给定一棵树，你要给每个点定一个 $[1,D]$ 的权值，满足每个点权值不大于父亲。问有多少种方案，答案模 $10^9+7$ 。

## 题解

由于我太菜不会插值，只好用容斥来做了。

我们考虑一个$DP$，用 $ f_{i,j} $ 表示在节点 $i$ 的子树中，令节点 $i$ 的权值为 $j$ 的合法方案数。记 $s_{i,j} = \sum_{k=1}^j f_{i,k}$ ，由于不同子树之间互相独立，很容易导出转移方程：
$$f_{i,j} = \prod_{fa_v = i} s[v][j]$$

但是，由于 $d \leq 10^9$ ，直接上这种做法是肯定不行的。观察发现，题目中 $n \leq 3000$ ，相比之下特别小，所以考虑转换一种思路。实际上，总共只会有至多 $n$ 种本质不同的权值，所以我们可以将它们离散化，然后再计算 $f_{i,j}$ 。此时， $f_{i,j}$ 中 $j$ 的意义就变为节点 $i$ 的权值为离散化之后的第 $j$ 大的权值。

计算出 $f_{i,j}$ 之后，下一步考虑如何计算答案。离散化之后，我们应该计算出恰好用了 $i$ 种权值的方案，记为 $g_i$ 。显然，直接统计会导致重复计数，例如样例一中的 $(2,2,2)$ 就会被同时计入 $g_1$ 与 $g_2$ 。所以，我们可以考虑容斥。

由定义可知， $f_{1,i}$ 指最大权值为 $i$ 的方案数，完全包含了 $g_i$ 。所以， $g_i$ 中我们要删去的不合法方案一定是包含权值 $i$ 的一些方案，其权值种数小于 $i$ 。考虑权值种数恰为 $j$ 的方案数 $g_j$ ，则它的贡献为 $g_i \times C_{i-1}^{i-j}$ 。  
其中，系数 $C_{i-1}^{j-1}$ 表示除了权值 $i$ 必须选中之外，余下的 $i-1$ 种权值中选出 $j-1$ 种权值，组成一种权值种数恰为 $j$ 的权值选取方案的方案数。也就是，对于 $g_j$ 所包含的所有方案数，它们都将在 $f_{1,i}$ 中出现 $C_{i-1}^{j-1}$ 次。

接着，我们就可以推出最终的容斥方程和答案：
$$g_i = f_{1,i} - \sum_{j=1}^{i-1} C_{i-1}^{i-j} \times g_j$$
$$Ans = \sum_{i=1}^{\min(n,d)} C_{d}^{i} \times g_i$$
这里，由于 $i$ 远小于 $d$ ，所以我们可以直接暴力计算 $C_{d}^{i}$ ，得出答案。
## 代码
```cpp
#include<bits/stdc++.h>
#define reg register
typedef long long ll;
using namespace std;
const int MN=3005;
const int mod=1e9+7;
int to[MN],nxt[MN],h[MN],cnt;
inline void ins(int s,int t){
    to[++cnt]=t;nxt[cnt]=h[s];h[s]=cnt;
}
int n,m,f[MN][MN],s[MN][MN],g[MN],C[MN][MN],inv[MN];
void dfs(int st){
    for(reg int i=h[st];i;i=nxt[i]){
        dfs(to[i]);
        for(reg int j=1;j<=n;j++)
            f[st][j]=1ll*f[st][j]*s[to[i]][j]%mod;
    }
    for(reg int i=1;i<=n;i++)
        s[st][i]=(s[st][i-1]+f[st][i])%mod;
}
int main(){
    scanf("%d%d",&n,&m);
    for(reg int i=2,x;i<=n;i++)scanf("%d",&x),ins(x,i);
    for(reg int i=1;i<=n;i++)for(reg int j=1;j<=n;j++)f[i][j]=1;
    dfs(1);C[0][0]=C[1][0]=C[1][1]=1;
    for(reg int i=2;i<=n;i++){
        C[i][0]=1;
        for(reg int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
    inv[0]=inv[1]=1;
    for(reg int i=2;i<=n;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    for(reg int i=2;i<=n;i++)inv[i]=1ll*inv[i-1]*inv[i]%mod;
    for(reg int i=1;i<=n;i++){
        g[i]=f[1][i];
        for(reg int j=1;j<i;j++)
            g[i]=(g[i]-1ll*C[i-1][i-j]*g[j]%mod+mod)%mod;
    }
    reg int Ans=0;
    for(reg int i=1;i<=min(n,m);i++){
        reg int Res=inv[i];
        for(reg int j=m-i+1;j<=m;j++)Res=1ll*Res*j%mod;
        Ans=(Ans+1ll*Res*g[i]%mod)%mod;
    }
    printf("%d\n",Ans);
    return 0;
}
```

---

## 作者：Karry5307 (赞：13)

### 题意

给一棵 $n$ 个节点的树，你需要对每个节点分配一个 $[1,D]$ 的权值，但必须要满足任意节点 $u$ 的权值不小于 $u$ 的任意一个儿子，求分配方案，对 $10^9+7$ 取模。

$\texttt{Data Range:}1\leq n\leq 3000,1\leq D\leq 10^9$

### 题解

套路 DP 加上不寻常的优化。

~~鼓吹一波：多项式大法 yyds！~~

首先考虑暴力 DP。设 $f_{i,j}$ 表示以 $i$ 节点为根的子树中钦定 $i$ 节点分配权值 $j$ 的方案数。转移的时候因为子树相互独立所以可以乘起来。枚举子树的权值有如下转移方程：

$$f_{i,j}=\prod_{fa_u=i}\sum\limits_{k=1}^{j}f_{u,k}$$

然而这个转移暴力是 $O(nD^2)$ 的，如果设 $g_{i,j}$ 为 $f_{i,j}$ 在 $j$ 这个维度上的前缀和可以做到 $O(nD)$，然而还是无法通过。

接下来有一个结论：对于节点 $u$ 来说，$g_{u,i}$ 为一个不超过 $sz_u$ 次多项式在 $i$ 处的点值，我们来证明这个结论。

考虑归纳。对于叶子节点来说 $g_{u,i}=1$ 是一个 $0$ 次多项式，接下来考虑非叶子节点。

注意到有这么个东西：

$$g_{i,j}-g_{i,j-1}=f_{i,j}=\prod_{fa_u=i}g_{u,j}$$

由于右边的乘积式是对应位置的点值乘起来，根据 FFT 那套理论一堆多项式的对应点值乘起来会是某个多项式的对应点值，而且这个多项式的次数为所有被乘起来的多项式次数之和。

所以说 $g_{i,j}-g_{i,j-1}$ 为一个次数不超过 $sz_i-1$ 的多项式，也即 $g_{i,j}$ 为一个次数不超过 $sz_i$ 的多项式。

第一次 DP 我们能够求出满足 $1\leq i\leq n+1$ 的所有 $g_{1,i}$，然后拉格朗日插值就可以求出答案。由于点值比较特殊是连续的一段所以可以预处理然后 $O(n)$ 求，当然 $O(n^2)$ 也可以过。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=3e3+51,MOD=1e9+7;
ll n,m,u,v,res;
vector<ll>vg[MAXN];
ll f[MAXN][MAXN],g[MAXN][MAXN],pl[MAXN],pr[MAXN],fact[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll qpow(ll base,ll exponent)
{
	ll res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
inline void dfs(ll node)
{
	for(register int i=1;i<=n+5;i++)
	{
		f[node][i]=1;
	}
	for(register int i:vg[node])
	{
		dfs(i);
		for(register int j=1;j<=n+5;j++)
		{
			f[node][j]=(li)f[node][j]*g[i][j]%MOD;
		}
	}
	for(register int i=1;i<=n+5;i++)
	{
		g[node][i]=(g[node][i-1]+f[node][i])%MOD;
	}
}
int main()
{
	n=read(),m=read();
	for(register int i=2;i<=n;i++)
	{
		vg[read()].push_back(i);
	}
	dfs(1),pl[0]=pr[n+2]=fact[0]=1;
	for(register int i=1;i<=n+1;i++)
	{
		pl[i]=(li)pl[i-1]*(m-i+MOD)%MOD,fact[i]=(li)fact[i-1]*i%MOD;
	}
	for(register int i=n+1;i;i--)
	{
		pr[i]=(li)pr[i+1]*(m-i+MOD)%MOD;
	}
	for(register int i=1;i<=n+1;i++)
	{
		v=(li)fact[i-1]*fact[n+1-i]%MOD,v=(n-i)&1?v:MOD-v;
		u=(li)pl[i-1]*pr[i+1]%MOD;
		res=(res+(li)g[1][i]*u%MOD*qpow(v,MOD-2)%MOD)%MOD;
	}
	printf("%d\n",res);
}
```

---

## 作者：Rainybunny (赞：9)

### 题意简述

&emsp;&emsp;[link](https://www.luogu.com.cn/problem/CF995F).

&emsp;&emsp;给定一棵 $n$ 个结点的有根树，用 $[1,d]$ 为每个结点染色，要求子结点颜色不大于父节点颜色，求方案数。对大素数取模。

### 数据规模

&emsp;&emsp;$n\le3000;~d\le10^9$。

### Solution

#### Step 1

&emsp;&emsp;我们还是先列出一个暴力的 DP。令 $f(u,i)$ 表示以 $u$ 为根的子树用 $[1,i]$ 染色的方案数，转移显然有：
$$
f(u,i)=f(u,i-1)+\prod_{v\in son_u}f(v,i)
$$
&emsp;&emsp;直接 DP，复杂度 $O(nd)$，不可过。

#### Step 2

&emsp;&emsp;~~大声说出你的猜想！~~  

&emsp;&emsp;Bingo！**设 $u$ 的子树大小为 $s_u$，则 $f(u,x)$ 是关于 $x$ 的 $s_u$ 次函数**。

##### 证明

&emsp;&emsp;仍考虑归纳：

- $1).$ 当 $u$ 为叶子结点时，$f(u,x)=1$，成立。

- $2).$ 当 $v\in son_u$  时成立，考虑 $u$：
    $$
    f(u,x)-f(u,x-1)=\prod_{v\in son_u}f(v,x)
    $$
    &emsp;&emsp;由于 $v$ 满足结论，即 $f(v,x)$ 的次数为 $s_v$，则 $f(u,x)-f(u,x-1)$ 的次数为 $\sum_{v\in son_u}s_v$，即 $s_u-1$。再还原差分，次数 $+1$，有 $f(u,x)$ 是关于 $x$ 的 $s_u-1+1=s_u$ 次函数。

    &emsp;&emsp;由 $1).~2).$ 证毕。

    

&emsp;&emsp;所以，只需要处理出 $f(u,1..n)$，最后利用 $\left(x,f(1,x)\right)~(x\in[0,n])$ 求出 $f(1,x)$ 的曲线方程，再代入 $d$ 即可。

&emsp;&emsp;连续插值部分可以优化到 $O(n)$，不过这并不是唯一的瓶颈复杂度。最终复杂度仍是 $O(n^2)$。

#### 代码

```cpp
#include <cstdio>

const int MAXN = 3000, MOD = 1e9 + 7;
int n, d, ecnt, head[MAXN + 5], x[MAXN + 5], f[MAXN + 5][MAXN + 5];

struct Edge { int to, nxt; } graph[MAXN + 5];

inline int qkpow ( int a, int b, const int p = MOD ) {
	int ret = 1;
	for ( ; b; a = 1ll * a * a % p, b >>= 1 ) ret = 1ll * ret * ( b & 1 ? a : 1 ) % p;
	return ret;
}

inline int lagrange ( const int n, const int* x, const int* y, const int k ) {
	int ret = 0;
	for ( int i = 1; i <= n; ++ i ) {
		int num = y[i], den = 1;
		for ( int j = 1; j <= n; ++ j ) {
			if ( i ^ j ) {
				num = 1ll * num * ( k - x[j] + MOD ) % MOD;
				den = 1ll * den * ( x[i] - x[j] + MOD ) % MOD;
			}
		}
		ret = ( ret + 1ll * num * qkpow ( den, MOD - 2 ) ) % MOD;
	}
	return ret;
}

inline void link ( const int s, const int t ) { graph[++ ecnt] = { t, head[s] }, head[s] = ecnt; }

inline void DFS ( const int u ) {
	for ( int i = 1; i <= n; ++ i ) f[u][i] = 1;
	for ( int i = head[u], v; i; i = graph[i].nxt ) {
		DFS ( v = graph[i].to );
		for ( int j = 1; j <= n; ++ j ) f[u][j] = 1ll * f[u][j] * f[v][j] % MOD;
	}
	for ( int i = 2; i <= n; ++ i ) f[u][i] = ( f[u][i] + f[u][i - 1] ) % MOD;
}

int main () {
	scanf ( "%d %d", &n, &d );
	for ( int i = 1; i <= n; ++ i ) x[i] = i;
	for ( int i = 2, f; i <= n; ++ i ) scanf ( "%d", &f ), link ( f, i );
	printf ( "%d\n", ( DFS ( 1 ), d <= n ? f[1][d] : lagrange ( n + 1, x - 1, f[1] - 1, d ) ) );
	return 0;
}
```

---

## 作者：foreverlasting (赞：5)

[题面](https://www.luogu.org/problemnew/show/CF995F)

拉格朗日插值。

这题主要在于证明。设$dp[i][j]$表示$i$号节点选择的值为$j$的子树方案数。显然的转移方程：$dp[i][j]$=$\prod_{q∈tox} \sum_{k=0}^j dp[q][j]$。所以我们对于$dp$数组维护一个前缀和。然后发现$DP$实在是太大了，直接$DP$是不现实的，观察式子，发现可以证明这是一个最高次为$n$关于$j$多项式。证明如下：叶子节点的$dp$式显然是一个一次函数(都是1），他们的父亲因为维护了一个乘积所以变成了一个他们最高次为叶子节点个数关于$j$的多项式。以此类推，根节点就是一个最高次为$n$关于$j$的多项式，然后就可以套用拉格朗日插值了。

code:
```
//2018.10.11 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int kcz=1e9+7;
const int N=3e3+10;
namespace MAIN{
    int n,d;
    struct E{
        int next,to;
        E() {}
        E(res next,res to):next(next),to(to) {}
    }edge[N];
    int head[N],cnt;
    inline void addedge(const res &u,const res &v){
        edge[++cnt]=E(head[u],v),head[u]=cnt;
    }
    int dp[N][N];
    inline int qpow(res x,res y){
        res ret=1;
        while(y){
            if(y&1)ret=1LL*ret*x%kcz;
            y>>=1,x=1LL*x*x%kcz;
        }
        return ret%kcz;
    }
    inline void add(res &x,const res &y){
        x+=y;
        x>=kcz?x-=kcz:1;
        x<0?x+=kcz:1;
    }
    inline int calc(const res &x){
        res tmp=1,ret=0,p=(n&1)?kcz-1:1;
        for(res i=1;i<=n;i++)tmp=1LL*tmp*(x-i)%kcz*qpow(i,kcz-2)%kcz;
        for(res i=0;i<=n;i++,p=kcz-p)
            add(ret,1LL*p*dp[1][i]%kcz*tmp%kcz),tmp=1LL*tmp*(x-i)%kcz*qpow(x-i-1,kcz-2)%kcz*(n-i)%kcz*qpow(i+1,kcz-2)%kcz;
        return ret;
    }
    void dfs(const res &x){
        for(res i=1;i<=n;i++)dp[x][i]=1;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            dfs(tox);
            for(res j=1;j<=n;j++)dp[x][j]=1LL*dp[x][j]*dp[tox][j]%kcz;
        }
        for(res i=1;i<=n;i++)add(dp[x][i],dp[x][i-1]);
    }
    inline void MAIN(){
        memset(head,-1,sizeof(head));
        n=read(),d=read();
        for(res i=2;i<=n;i++){
            res fa=read();
            addedge(fa,i);
        }
        dfs(1);
        if(d<=n)printf("%d\n",dp[1][d]);
        else printf("%d\n",calc(d));
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：Regimes (赞：3)

## 标签：

数学，容斥，$Dp$

## 来源：

$CF995F$

## 题意：

$given \ a \ tree$

$given \ a \ number \ D$

询问有多少方案使得，每个点的取值在$[1,D]$之间

且每个节点的值小于等于父亲。$(D\leq 10^9 , n \leq 3000)$

# $Solution$

我们考虑，若$D$非常的小，应该怎么做。一个显然的树形$Dp$

$$Dp_{i,j}=\prod{v \in son}\sum_{k=1}^iDp_{v,k}$$

对于后面那个$sum$，我们直接前缀和优化一下就好了。

但是我们现在的问题是$D$非常的大，但相对于来说$n$比较

的小。于是我们这样考虑。

假设我们取出了一个大小为$j$的数列，使得这棵树合法的方

案数，就是将每个数离散化后的$Dp_{1,j}$，但是对于这个

而言我们其实只是在大小为$j$的数列中去取数，且根为$j$

的方案。如果我们直到确切的每一个$g_j$，表示选出恰好

$j$个数的方案，我们就可以直接用组合数乘一下，算出答案。

即：

$$Ans=\sum_{i=1}^{min(D,n)}g_i \dbinom{D}{i} $$

于是我们考虑求出每一个$g_j$,利用容斥原理。

我们考虑对于每一个$g_j$

$$g_i=Dp_{1,i}-\sum_{j=1}^{i-1}g_j \dbinom{i - 1}{j-1}$$



---

## 作者：ListenSnow (赞：2)

[原题链接](http://https://codeforces.com/problemset/problem/995/F "原题链接")

## 题意

一棵 $n$ 个节点的树，给每个节点分配工资（$[1, D]$），子节点不能超过父亲节点的工资，问有多少种分配方案。

$ 1 \le n \le 3000 $ , $ 1 \le D \le 10^9 $

## 思路

注意到可分配的工资数很多，但实际能用到的至多只有 $n$ 种。可以考虑先记录相对大小关系，最后再乘上一个组合数。

令 $f_{i,j}$ 表示在以 $i$ 为根的子树中，节点 $i$ 的权值是**离散化后**第 $j$ 大时的合法方案数。可以得出转移方程：

$$f_{i,j}=\prod_{v \in son_i}\left ( \sum_{k=1}^{j} f_{v,k} \right )$$

其中 $\sum_{k=1}^{j} f_{v,k} $ 可以用前缀和优化掉，总的转移复杂度为 $O(n^2)$。

然而，假设当前节点的权值是 $j$，儿子节点的权值是 $k$。在转移的过程中，我们并不能保证 $k+1,k+2,\ldots,j-1$ 这些权值都被取到，在原始状态下这些权值不被取到是不影响正确性的，但是离散化后显然就会算重。根据题意，根节点的权值是最大的，那么 $f_{1,i}$ 的实际定义就是**至多用了** $i$ 种权值，且最大值为 $i$ 的方案数。

考虑容斥，设 $g_i$ 为恰好用了 $i$ 种权值的方案数。根据定义，其一定被 $f_{1,i}$ 完全包含。考虑减去实际用了 $j$ 种权值的方案，由于根节点一定为 $i$，那么剩下的 $j-1$ 种权值就一定在 $1 \sim i-1$ 中选取，于是可以得到容斥方程：

$$g_i=f_{1,i}-\sum_{j=1}^{i-1} \binom{i-1}{j-1} g_j$$

那么最终的答案就是：

$$\sum_{i=1}^{\min(n,d)} \binom{d}{i} g_i$$

## code：

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=3010,mod=1e9+7;
int s[N][N],n,d,h[N],idx,f[N][N],ans,fac[N],g[N],inv[N],infac[N];
struct edge{int v,nex;}e[N];
void add(int u,int v){e[++idx]=edge{v,h[u]};h[u]=idx;}
void init()
{
	fac[0]=fac[1]=infac[0]=infac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<N;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<N;i++) infac[i]=1ll*infac[i-1]*inv[i]%mod;
}
int C(int n,int m){if(n<0||m<0||n<m) return 0;return 1ll*fac[n]*infac[m]%mod*infac[n-m]%mod;}
void Add(int &a,int b){a+=b;if(a>=mod) a-=mod;}
void Sub(int &a,int b){a-=b;if(a<0) a+=mod;}
void Mul(int &a,int b){a=1ll*a*b%mod;}
void dfs(int u)
{
	for(int i=h[u];i;i=e[i].nex)
	{
		int v=e[i].v;dfs(v);
		for(int j=1;j<=min(n,d);j++) Mul(f[u][j],s[v][j]);
	}
	for(int i=1;i<=min(n,d);i++) s[u][i]=(s[u][i-1]+f[u][i])%mod;
}
int main()
{
	scanf("%d%d",&n,&d);for(int i=1;i<=n;i++) for(int j=1;j<=min(n,d);j++) f[i][j]=1;init();
	for(int u,v=2;v<=n;v++) scanf("%d",&u),add(u,v);dfs(1);g[1]=f[1][1];
	for(int i=2;i<=min(n,d);i++)
	{
		g[i]=f[1][i];for(int j=1;j<i;j++) Sub(g[i],1ll*C(i-1,j-1)*g[j]%mod);
		}
	for(int i=1;i<=min(n,d);i++)
	{
		int tmp=infac[i];for(int j=d;j>=d-i+1;j--) Mul(tmp,j);//C(n,i)
		Add(ans,1ll*tmp*g[i]%mod);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：JiaY19 (赞：1)

最近才会了拉格朗日插值的一些东西。

还是写一篇题解巩固一下。

### 思路

考虑暴力如何去写。

$$dp_{i,j}=dp_{i,j-1}+\prod_{x\in son(i)}dp_{x,j}$$

这是一个暴力 $dp$ 的方程，时间复杂度 $O(nd)$。

考虑如何优化。

我们将答案看做一个多项式 $f(x)$ 表示 $dp_{1,x}$。

拓展到整棵树上即，$f(u,x)$ 表示 $dp_{u,x}$。

我们猜测 $f(u,x)$ 是一个 $siz_u$ 项多项式。

证明：

使用归纳法。

- 当 $u$ 为叶子是原式成立。
- 当 $v\in son(u)$，且 $v$ 成立时：

$$f(u,x)-f(u,x-1)=\prod_{v\in son(u)}f(v,x)$$

那么 $f(u,x)-f(u,x-1)$ 为 $\sum_{v\in son(u)}siz_v$ 项多项式。

将差分还原，次数加一即 $\sum_{v\in son(u)}siz_v+1=siz_u$ 项多项式。

证毕。

使用拉格朗日插值进行优化。

由于一个 $n$ 次多项式可以用 $n+1$ 个点表示。

那么我们可以求出 $f(1,0\cdots n)$ 后。

使用拉格朗日插值快速求出 $f(1,d)$ 的答案：

$$f(d)=\sum_{i=0}^n f(i)\prod_{j\ne i}\frac{d-j}{i-j}$$

代码比较简单。

[code](https://www.luogu.com.cn/record/104959333)

---

## 作者：霖ux (赞：1)

### 题意
树形结构，给每个节点分配工资（ $[1, d]$ ），子节点不能超过父亲节点的工资，问有多少种分配方案，答案模 $10^9+7$ 。( $ 1 \le n \le 3000 $ , $ 1 \le D \le 10^9 $ )。
### 题解

看到 $\text D$ 那么大，我们肯定不能把 $\text D$ 写到复杂度里面去。  
注意到 $n$ 比较小，可以用到的值也就那么多，我们可以把值域"离散化"成 $\mathcal O(n)$ 的，再写进复杂度里。  
具体来说，我们用 $f_{u,m}$ 表示填完 $u$ 的子树取了 $m$ 种值的方案，最后再贡献到答案中。

考虑在不算$u$的贡献时的转移 $f_{u,m}'=\sum_i \sum_j f_{u,i}f_{v,j}V(i,j,m)$  
其中 $V(i,j,m)$ 表示把两个离散化后大小为 $i,j$ 的两个值域合并为一个离散化后大小为 $m$ 的值域。可以理解为把 $i$ 个红球和 $j$ 个蓝球放到 $m$ 个盒子里，且每个盒子每种球最多放一个且不能为空的方案数。  
简单容斥下我们可以得到 $V(i,j,n)=\sum_{k\ge0}(-1)^k {n-k\choose i}{n-k \choose j}{n \choose k}$

写到我们的转移方程中 $f_{u,m}'=\sum_i \sum_j f_{u,i} f_{v,j} \sum_{k \ge 0}(-1)^k {m-k\choose i}{m-k \choose j}{m \choose k}$  
把组合数拆成阶乘，再移动一下 $\sum$ ，可以得到  
$f_{u,m}'=\sum_{k \ge 0} \dfrac{m!(-1)^k(m-k)!}{k!}(\sum_i \dfrac {f_{u,i}}{i!}\dfrac 1 {(m-k-i)!})(\sum_j \dfrac {f_{v,j}}{j!}\dfrac 1 {(m-k-j)!})$  
$\dfrac{f_{u,m}'}{m!}=\sum_{k \ge 0} \dfrac{(-1)^k}{k!}\times(m-k)!(\sum_i \dfrac {f_{u,i}}{i!}\dfrac 1 {(m-k-i)!})(\sum_j \dfrac {f_{v,j}}{j!}\dfrac 1 {(m-k-j)!})$ 

$\dfrac {f_{u,i}} {i!}$ 格外显眼，我们写出它的生成函数  $\text F_u(x)= \sum_{i \ge 1} \dfrac {f_{u,i}}{i!}x^i$  
就有 $[x^m]\text F_u'(x)=\sum_{k \ge 0} \dfrac {(-1)^k}{k!}\times (m-k)![x^{m-k}](\text F_u(x)e^x)[x^{m-k}](\text F_v(x)e^x)$  
注意：我们用 $\text F_u'(x)$ 表示转移后的 $\text F_u(x)$ ，而非求导。其中$[x^n]$表示提取一个多项式$x^n$项的系数。  
这还是一个卷积，我们继续化简。  $[x^m]\text F_u'(x)=[x^m]e^{-x}(\sum_{k \ge0}k![x^k](\text F_u(x)e^x)[x^k](F_v(x)e^x)x^k)$  
也就是说  $\text F_u'(x)=e^{-x}(\sum_{k \ge0}k![x^k](\text F_u(x)e^x)[x^k](F_v(x)e^x)x^k)$  
$e^x\text F_u'(x)=\sum_{k \ge0}k![x^k](\text F_u(x)e^x)[x^k](F_v(x)e^x)x^k$  
不妨设 $\text G_u(x)=\sum_{k \ge 0}g_{u,k}x^k=\text F_u(x)e^x$ ,于是有 $g_{u,i}'=i!g_{u,i}g_{v,i}$   
于是正如我们期待的那样，我们可以在 $\mathcal O(n)$ 的时间完成 $G_u(x)$ 的转移。  
我们可以通过 $\text F_u(x)=\text G_u(x)e^{-x}$ 和 $\text G_u(x)=\text F_u(x)e^x$ 实现 $\text F_u,\text G_u$ 之间的变换，可惜这是 $\mathcal O(n^2)$ 的，所以我们只能先求出 $\text G_1(x)$ 再通过它还原出 $\text F_1(x)$。  
再考虑加上 $u$ 的贡献，$u$ 要么填当前的最大值，要么填一个新的最大值，所以   $f_{u,i}'=f_{u,i}+f_{u,i-1}$。   
体现在 $\text F_u(x)$ 上就是 $\text F_u'(x)=\text F_u(x)+\int \text F_u(x)dx$  
于是 $\text G_u'(x)=e^x\text F_u'(x)=e^x\text F_u(x)+e^x\int \text F_u(x)dx=G_u(x)+e^x\int \text F_u(x)dx$

我们现在需要求出 $e^x\int \text F_u(x)dx$ ,我们对它求导可以得到 $(e^x\int \text F_u(x)dx)'=e^x\text F(x)+e^x\int \text F_u(x)dx$  
提取出两边 $x^i$ 项的系数，设 $[x^i]e^x\int \text F_u(x)dx$ 为 $h_i$ ,于是有 $(i+1)h_{i+1}=g_{u.i}+h_i$ ，也就是 $h_i=\dfrac {g_{u,i-1}+h_{i-1}}i$ 。
这样我们就可以 $\mathcal O(n)$ 地求出 $e^x\int \text F_u(x)dx$ 并完成转移了。

关于初始化，对于叶子节点，因为 $f_{u,1}=1$ 且其他位置都为 $0$ ,根据定义可以得到 $g_{u,i}=\dfrac 1 {(i-1)!}$ ；对于其他节点，为了消除第一次转移多出来的 $i!$ ,我们让 $g_{u,i}=\dfrac 1 {i!}$。

关于答案，显然有 $ans=\sum_{k \ge 1} {\text D\choose k}f_{1,k}=\sum_{k \ge 1}\text D^{\underline k}[x^k]\text F_ 1(x)$

复杂度自然是 $\mathcal O(n^2)$ 的  
最后给上代码（略去快读和头文件）
```
//德丽莎世界第一可爱
#define int long long
const int maxn=4000,mod=1e9+7;
int fac[maxn],ifc[maxn],n,m,g[maxn][maxn],f[maxn],h[maxn],ans;
int qpow(int a,int x){int ans=1;while(x){if(x&1)ans=ans*a%mod;a=a*a%mod,x>>=1;}return ans;}
vector<int> son[maxn];
void dfs(int u){
    if(!son[u].size()){for(int i=1;i<=n;i++)g[u][i]=ifc[i-1];return;}
    for(int i=1;i<=n;i++)g[u][i]=ifc[i];
    for(int v:son[u]){dfs(v);for(int i=1;i<=n;i++)g[u][i]=g[u][i]*g[v][i]%mod*fac[i]%mod;}
    for(int i=1;i<=n;i++)h[i]=(g[u][i-1]+h[i-1]+mod)%mod*fac[i-1]%mod*ifc[i]%mod;//偷个懒，1/n=(n-1)!/n!
    for(int i=1;i<=n;i++)g[u][i]=(g[u][i]+h[i])%mod;
}
signed main(){
    n=read(),m=read();for(int i=2;i<=n;i++)son[read()].push_back(i); 
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;//预处理阶乘
    ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;i--)ifc[i]=ifc[i+1]*(i+1)%mod;//阶乘的逆元
    dfs(1);for(int i=1;i<=n;i++)for(int j=0;j<=i;j++)f[i]=(f[i]+g[1][i-j]*ifc[j]%mod*((j&1)?mod-1:1)%mod)%mod;
    for(int i=1,t=m;i<=n;i++)ans=(ans+f[i]*t)%mod,t=t*(m-i)%mod;
    return printf("%lld",ans),0;
}   
```





---

## 作者：_SeeleVollerei_ (赞：0)

考虑 $D<n$ 的情况是简单的，直接令 $f_{u,i}$ 表示点 $u$ 填数 $i$ 时，$u$ 的子树的答案。转移是简单的。

$$f_{u,i}=\prod_{v\in son(u)}\sum_{j=1}^if_{v,j}$$

然后直接查询 $\sum_{i=1}^df_{1,i}$ 即可。

那么问题的瓶颈在于 $D$ 很大，但是我们发现实际上树内的数的种数不超过 $n$，那么只要我们知道 $g_i$ 表示用刚好 $i$ 种数的答案，那么题目的答案可以用下面的式子表示。

$$ans=\sum_{i=1}^ng_i\binom{D}{i}$$

组合数暴力 $O(n)$ 求即可。问题转化为如何求 $g_i$。

我们考虑最开始的做法。

直接调用 $f_{1,i}$ 显然是错的，因为可能是用了少于 $i$ 种，但是又不包含所有 $\le i$ 种的。

但是发现 $f_{1,i}$ 包含了所有恰好把 $[1,i]$ 的 $i$ 种都用过的方案，所以只需要取一个前缀和。或者从另一个角度来讲，不能直接调用的原因是这个 $f_{1,i}$ 钦定了根的值，那么我们只需要把 $a_1=i$ 的形式变成 $a_1\le i$ 即可，这也会走到前缀和。

取完后 $f_{1,i}$ 就变成了在 $[1,i]$ 内的所有方案了，考虑从小到大求解，显然 $g_j$ 会在 $f_{1,i}$ 里贡献 $\binom{i}{j}$ 次，所以有下面的式子。

$$g_i=f_{1,i}-\sum_{j=1}^{i-1}g_j\binom{i}{j}$$

然后就没了，复杂度 $O(n^2)$。

https://codeforces.com/contest/995/submission/171687696

---

## 作者：Leap_Frog (赞：0)

### P.S.
真的高妙题。。。  

### Description.
给定一棵树，对每个结点加权，使得 $\forall x\in[1,n],a_x\in[1,D]$ 且 $\forall x\in[1,n],\forall y\in\text{son}_x,a_x\ge a_y$。  
求方案数。  

### Solution.
看到这种题，一眼线段树合并。（虽然这个数据范围……  
考虑在值域上进行 $dp$，有如下式子。  
$$dp_{x,i}=\prod_{y\in \text{son}_x}\sum_{j=1}^idp_{x,i}$$  
初始值为 $dp_{x,i}=1$。  
但是注意这初始状态不是一个点，而是一个区间，要考虑一个套路。  
就是把当前只被修改一次的区间打个结束标记，不建立下面的子树。  
然后每次 pushdown 再建立下面的内容。  
这样空间复杂度和时间复杂度和普通线段树合并是一样的，可以通过。  
突然发现有点不对劲。  
考虑两个重合的结束结点，转移一次后就相当于加上了一个等差数列。  
那是不是还需要区间加等差数列 ![](//xn--9zr.tk/xia)  
但是，冷静思考一下，发现两个等差数列合并起来就不只是等差数列了，**线段树算法假咯**  

但是，我们能从线段树合并的思路中得到启发，发现一些特殊性质。  
考虑合并一次是等差数列是 $a_i=i$，合并两次打表发现是 $a_i=i^2$。  
我们发现合并 $n-1$ 次是一个至多 $n-1$ 次的多项式。  
那么我们带 $n$ 个点值就能确定这个多项式，设为 $dp(i)$。  
注意我们最后需要求 $S(D)=\sum_{i=1}^Ddp(i)$。  
根据多项式那套理论，$S(x)$ 肯定是至多 $n+1$ 项的多项式。  
然后直接上 $O(n^2)$ 插值就好了。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
const int P=1e9+7;int n,D,dp[3005][3005],s[3005][3005],res;
struct edge{int to,nxt;}e[3005];int et,head[3005],iv[3005];
inline int ksm(int x,int q=P-2) {int r=1;for(;q;q>>=1,x=1ll*x*x%P) if(q&1) r=1ll*r*x%P;return r;}
inline void adde(int x,int y) {e[++et]=(edge){y,head[x]},head[x]=et;}
inline void dfs(int x)
{
	for(int i=1;i<=n;i++) dp[x][i]=1;
	for(int i=head[x];i;i=e[i].nxt)
	{
		dfs(e[i].to);for(int j=1;j<=n;j++)
			dp[x][j]=1ll*dp[x][j]*s[e[i].to][j]%P;
	}
	for(int i=1;i<=n;i++) s[x][i]=(s[x][i-1]+dp[x][i])%P;
}
inline int inv(int x) {return x<0?P-iv[-x]:iv[x];}
int main()
{
	read(n),read(D);for(int i=2,f;i<=n;i++) read(f),adde(f,i);
	iv[1]=1;for(int i=2;i<=n;i++) iv[i]=1ll*iv[P%i]*(P-P/i)%P;
	dfs(1);for(int i=1,w=1;i<=n;(res+=1ll*w*s[1][i]%P)%=P,w=1,i++)
		for(int j=1;j<=n;j++) if(i^j) w=1ll*w*(D-j)%P*inv(i-j)%P;
	return printf("%d\n",(res+P)%P),0;
}
```

---

## 作者：crashed (赞：0)

# 题目
&emsp;&emsp;[点这里](https://www.luogu.com.cn/problem/CF995F)看题目。  
# 分析
&emsp;&emsp;不难看出一个暴力 DP ：     
&emsp;&emsp;$f(u,i)$：当$u$取$i$时，$u$的子树内的方案数。   
&emsp;&emsp;转移显然：   
$$f(u,i)=\prod_{v\in son(u)}\sum_{j\le i} f(v,j)$$  
&emsp;&emsp;再设$S(u,i)=\sum_{j\le i}f(u,j)$，即前缀和。答案就是$S(1,D)$。$S$的转移也很好想：   
$$S(u,i)=\sum_{j\le i}f(u,i)=\sum_{j\le i}\prod_{v\in son(u)}S(v,j)$$    
&emsp;&emsp;显然，当$u$确定的时候，$S(u,i)$就是$i$的**多项式函数**。我们只需要计算出它的次数，就可以用插值法，得到$S(u,D)$的答案。  
&emsp;&emsp;设$g(u)$为$S(u)$的次数，根据转移方程，可以得到$g(u)$为：  
$$g(u)=1+\sum_{v\in son(u)}g(v)$$   
&emsp;&emsp;所以$S(1)$的次数就是$n$，我们只需要求出$S(1,1)\sim S(1,n+1)$，即可进行插值，求出$S(1,D)$。时间复杂度$O(n^2)$。  
# 代码
```cpp
#include<cstdio>

const int mod = 1e9 + 7;
const int MAXN = 3005;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

struct edge
{
	int to, nxt;
}Graph[MAXN << 1];

int f[MAXN][MAXN];
int head[MAXN];
int N, M, D, cnt;

void addEdge( const int from, const int to )
{
	Graph[++ cnt].to = to, Graph[cnt].nxt = head[from];
	head[from] = cnt;
}

int qkpow( int base, int indx )
{
	int ret = 1;
	while( indx )
	{
		if( indx & 1 ) ret = 1ll * ret * base % mod;
		base = 1ll * base * base % mod, indx >>= 1;
	}
	return ret;
}

int inver( const int a ) { return qkpow( a, mod - 2 ); }
int fix( const int a ) { return ( a % mod + mod ) % mod; }
void add( int &x, const int v ) { x = ( x + v >= mod ? x + v - mod : x + v ); }

void DFS( const int u )
{
	for( int i = 1 ; i <= M ; i ++ ) f[u][i] = 1;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
	{
		DFS( v = Graph[i].to );
		for( int j = 1 ; j <= M ; j ++ ) 
			f[u][j] = 1ll * f[u][j] * f[v][j] % mod;
	}
	for( int i = 1 ; i <= M ; i ++ ) add( f[u][i], f[u][i - 1] );
}

int Lagrange()
{
	if( D <= M ) return f[1][D];
	int ans = 0, w = 1, L = 1;
	for( int i = 1 ; i <= M ; i ++ ) L = 1ll * L * ( D - i ) % mod;
	for( int i = 2 ; i <= M ; i ++ ) w = 1ll * w * inver( fix( 1 - i ) ) % mod;
	for( int i = 1 ; i <= M ; i ++ )
	{
		add( ans, 1ll * L * w % mod * inver( D - i ) % mod * f[1][i] % mod );
		if( i < M ) w = 1ll * w * fix( i - M ) % mod * inver( i ) % mod;
	}
	return ans;
}

int main()
{
	read( N ), read( D );
	for( int i = 2, p ; i <= N ; i ++ ) read( p ), addEdge( p, i );
	M = N + 1, DFS( 1 );
	write( Lagrange() ), putchar( '\n' );
	return 0;
}
```

---

