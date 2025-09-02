# 【MX-X9-T6】『GROI-R3』Graph

## 题目描述

给定一张 $n$ 个点的有向图 $G=(V,E)$，点的编号为 $1 \sim n$，其每个点都入度、出度均不大于 $1$。

在出度不大于 $1$ 的有向图中，我们记 $f^k(x)$ 表示点 $x$ 在图上沿着出边走 $k$ 步走到的点（如果走到一个不存在出边的点，则停在该点上）。

进一步定义 $G^k=(V,E')$，其中 $E'=\{(x,f^k(x))\mid x\in V\}$。我们称 $G$ 为 $G^k$ 的 $k$ 次方根。

若一个点入度出度均为 $0$ 则称其为孤立点。

又给定一个正整数 $c$，你需要给 $G$ 增加若干条边得到图 $G'$，使得：

1. 每个节点的入度出度均为 $1$。
2. 若两个非孤立点在 $G'$ 上位于同一连通块$^{\dagger}$，则在 $G$ 上也要位于同一连通块。
3. 图 $G'$ 存在 $c$ 次方根。

求加边的方案总数，答案对 $998244353$ 取模。

$^{\dagger}$：本题中定义有向图连通块为：将所有边视作无向边得到的连通块。

## 说明/提示

令 $a_i$ 表示点 $i$ 的出边指向点的编号。

**【样例解释 #1】**

合法的序列 $a_1,\ldots,a_n$ 有：

- $2,5,1,3,4$。
- $2,5,3,4,1$。
- $2,5,4,1,3$。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | $n\le$ | $c\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $5$ | $5$ |  | $2$ |
| 2 | $1000$ | $2\times10^9$ | A | $3$ |
| 3 | $10$ | $2\times10^9$ |  | $15$ |
| 4 | $20$ | $2\times10^9$ |  | $10$ |
| 5 | $100$ | $2\times10^9$ |  | $25$ |
| 6 | $500$ | $2\times10^9$ | B | $10$ |
| 7 | $500$ | $2\times10^9$ |  | $20$ |
| 8 | $1000$ | $2\times10^9$ |  | $15$ |

- 特殊性质 A：保证不存在 $a_i=-1$。
- 特殊性质 B：保证所有 $a_i=-1$。

对于 $100\%$ 的数据，保证 $1\le n\le 1000$，$1\le c\le 2\times10^9$，$1\le a_i\le n$ 或 $a_i=-1$，不存在 $i\ne j$ 使得 $a_i=a_j$ 且 $a_i \ne -1$。

## 样例 #1

### 输入

```
5 4
2 5 -1 -1 -1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
9 7
7 -1 -1 -1 8 1 -1 -1 5
```

### 输出

```
60
```

## 样例 #3

### 输入

```
8 10
-1 -1 4 -1 -1 -1 -1 -1
```

### 输出

```
1266
```

# 题解

## 作者：Rain_chr (赞：2)

### Part 1 前言

非常考验基本功的一道题，我想到做法用了两个小时，写+优化又用了两个小时，特写题解以记录。

### Part 2 解法

首先预处理出 $A_i,B_i,C$ 分别表示原图中长度为 $i$ 的环数，长度为 $i$ 的链数以及孤立点个数。

首先来推一推 $c$ 次方的性质：

> 引理 1：一个环长为 $x$ 的环 $c$ 次方之后会分裂成 $(x,c)$ 个环长为 $\frac c {(x,c)}$ 的环

证明显然，不再赘述。

所以只有在新图 $G'$ 中环长相等的环才可能拼在一起，不同环长之间互相独立。

再来推一下对于一个二元组 $(a_i,b_i)$ 表示有 $a_i$ 个环长为 $b_i$ 的环，什么情况下才有 $c$ 次方根。

> 引理 2：拼成新环的方式一定是将 $a_i$ 个环分成 $\frac {a_i} k$ 组，每组里有 $k$ 个长度为 $b_i$ 的环。

证明：

假设有两种拼出环的方式，分别用 $p$ 个长为 $b_i$ 的环和用 $q$ 个长为 $b_i$ 的环拼成一个新环，那么根据引理 1 有：

$$
\begin{cases}
(c,qb_i)=q \\
(c,pb_i)=p \\
\end{cases}
$$

也就是

$$

\begin{cases}
(\frac c q,b_i)=1 \\
(\frac c p,b_i)=1 \\
\end{cases}
$$

于是我们可以得到：

$$
(c,b_i)|q,(c,b_i)|p \Rightarrow (c,b_i)|(p,q)
$$

我们惊奇的发现，对于两种合法的方案，他们的 gcd 同样合法，所以我们就证明了最终方案中，我们只会不断的拼成一种长度的环。

更进一步，可以得到引理 2 的一个推论：

> 设 $k_{min}$ 是最小的合法的 $k$，任意合法的 $k'$ 均满足 $k_{min}|k'$

所以我们可以得到判定的最简形式：

暴力求出 $k_{min}$，判断是否 $[k_{min}|a_i]$

现在可以着手来审视 DP 了，我们根据判定形式，枚举环长依次讨论。这个地方我还卡了一下，我一直在想从大往小枚举环长是怎么记录链是否使用了，后来突然想到只需要从小往大枚举环长然后依次加入未使用的连就可以了，于是我们可以设 $f_{i,j,k}$ 表示当前环长为 $i$，有 $j$ 条长度为 $i$ 的链，剩下 $k$ 个孤立点。转移分两步：

1. $f_{i,j+B_i,k-j} \leftarrow f_{i-1,j,k}\times A_k^j$

这是因为当枚举的环长增加时，相应的要在链的末尾添加一个孤立点，选取孤立点对应到每条链的方案是 $A_k^j$。注意这里不应该乘 $2^j$，因为环的缘故我们钦定每次只会加在末尾，不然会算重。

2. $f_{i,j_1,k_1} \leftarrow \frac{f_{i,j_1-j_2,k_1-k_2i}C_{k_2}^{k_1}A_{k_1}^{k_2i}}{i^{k_2}k_2!} [k_{min}|j_1+k_1+A_i]$

式子非常丑陋，考虑枚举闭口的链条数 $j_2$ 以及使用孤立点拼成的环数 $k_2$，自己稍微推一推式子也能得到一样的结果。

然后这样子通过一堆分析可以分析到 $O(n^4)$，详见其他题解，我感性理解这样跑得很快，事实上的确如此，考虑怎么优化到 $O(n^3)$。

我们可以发现除了最后的转移条件，转移式的其余部分是两维互相独立的，无论是下标还是系数都是如此。

于是考虑分步转移，最后的转移条件可以视作只在 $\bmod k_{min}$ 的同余类中进行两步转移，具体实现可以看代码。

### Part 3 总结

这是一道非常考验 DP 基本功的题目，题目未必困难，但是推导过程一环套一环，适合锻炼系统性做题思维。

### Part 4 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int a[N];
int A[N],B[N],C;//分别表示环的个数,链的个数,以及孤立点的个数
int in[N];
bool use[N];
int n,c;
int f[N][N];//设f[i][j][k]表示目前考虑长度为i的环,有j条长为i的链,孤立点数量为k
int tmp1[N][N],tmp2[N][N];
const int mod=998244353;
void add(int &x,int y){x=x+y>=mod?x+y-mod:x+y;}
int jc[N],inv[N],Inv[N];
int F(int x,int y)
{
    if(x<0||y<0||x<y) return 0;
    return 1ll*jc[x]*inv[y]%mod*inv[x-y]%mod;
}
int G(int x,int y)
{
    if(x<0||y<0||x<y) return 0;
    return 1ll*jc[x]*inv[x-y]%mod;
}
signed main()
{
    // freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>c;
    jc[0]=jc[1]=inv[0]=inv[1]=1;
    for(int i=2;i<=n;i++) jc[i]=1ll*jc[i-1]*i%mod;
    for(int i=2;i<=n;i++) inv[i]=mod-1ll*mod/i*inv[mod%i]%mod;
    memcpy(Inv,inv,sizeof(Inv));
    for(int i=2;i<=n;i++) inv[i]=1ll*inv[i-1]*inv[i]%mod;
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i];
        if(a[i]!=-1) in[a[i]]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(in[i]||use[i]) continue;
        if(a[i]==-1) C++;
        else
        {
            int p=i,cnt=0;
            while(p!=-1) in[p]=0,use[p]=1,p=a[p],cnt++;
            B[cnt]++;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(!in[i]) continue;
        int p=i,cnt=0;
        do{cnt++,in[p]=0,p=a[p];}while(p!=i);
        A[cnt]++;
    }
    f[0][C]=1;
    int sumb=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=sumb;j++) for(int k=0;k<=C;k++) tmp2[j][k]=0;
        for(int j=0;j<=sumb;j++)
            for(int k=j;k<=C;k++)
                add(tmp2[j+B[i]][k-j],1ll*f[j][k]*G(k,j)%mod);
        for(int j=0;j<=sumb;j++) for(int k=0;k<=C;k++) f[j][k]=0;
        sumb+=B[i];
        int x=0;
        while(++x) if(__gcd(i,c/__gcd(c,x))==1) break;
        for(int t=0;t<x;t++)
        {
            for(int j=0;j<=min(sumb,n/i);j++) for(int k=0;k<=C;k++) tmp1[j][k]=0;
            for(int j2=(t-A[i]%x+x)%x;j2<=min(sumb,n/i);j2+=x)
                for(int j1=j2;j1<=min(sumb,n/i);j1++)
                    for(int k1=0;k1<=C;k1++)
                        if(tmp2[j1][k1])
                            add(tmp1[j1-j2][k1],1ll*tmp2[j1][k1]*F(j1,j2)%mod);
            int now=1;
            for(int k2=0;i*k2<=C;k2++,now=1ll*now*Inv[i]%mod)
                if((n*x-k2)%x==t)
                    for(int j1=0;j1<=min(sumb,n/i);j1++)
                        for(int k1=i*k2;k1<=C;k1++)
                            if(tmp1[j1][k1])
                                add(f[j1][k1-k2*i],1ll*tmp1[j1][k1]*now%mod*G(k1,k2*i)%mod*inv[k2]%mod);
        }
    }
    cout<<f[0][0]<<'\n';
    return 0;   
}

```

---

## 作者：lsj2009 (赞：2)

## Preface

出题人题解。

为啥这个题只过了 $3$ 个人啊？？其实根本不难啊。

## Description

有一些环、链、孤立点，你需要将后两者直接相互连边得到若干个环（链与链不能合并在一个环中），使得最终得到的图存在 $c$ 次方根。

求方案总数，向 $998244353$ 取模。

$1\le n\leq 1000$，$1\le c\le 10^9$。

## Solution

### Part 1
		
我们先考虑然后判断一个图是否存在 $c$ 次方根（这个可能是比较典的？）。
		
考虑一个图取 $c$ 方后会有啥变化。首先对于每个环我们可以分开了考虑；考察一个环，有经典结论：
- 一个长度 $len$ 的环会分裂成 $\gcd(c,len)$ 个长为 $\frac{len}{\gcd(c,len)}$ 的环。
		
> **Proof：**
>
> 对环重标号，考虑从节点 $x$ 在新图上向后走 $k$ 步又回到了 $x$，则有 $x+kc\equiv x\pmod{len}$。
>
> 解得 $k_{\min}=\frac{len}{\gcd(c,len)}$，则我们就得到了上面的结论。

即 **原图上的一个环会在新图上变成若干个长度相同的环**；那么我们倒过来考虑，则我们需要把新图上的若干个长度相同的环给合并回去。
		
具体的，考虑当前环长为 $len$，根据上面结论，$p$ 个长度为 $len$ 的环合并的充要条件是 $\gcd(c,p\cdot len)=p$。
		
我们找出所有满足条件的 $p$，若他们可以拼凑出 $cnt_{len}$（一个 $p$ 可以多次是用），那么就是合法的。
		
实现上我们跑一个可行性完全背包即可。

但是我们可以做到更优：有结论是：
- 我们找到最小的满足条件的 $p$，则可以拼凑出 $m$ 满足条件 **当且仅当 $m$ 是 $p$ 的倍数**。
		
> **Proof：**
>
> 记 $t=p_{\min}$。
> 
> 观察条件：$\gcd(c,p\cdot len)=p\Rightarrow c\equiv 0\pmod{p}\wedge \gcd(\frac{c}{p},len)=1$。
> 
> 写出 $p,len,c$ 的唯一分解形式：
> - $p=\prod q_i^{\alpha_i}$。
> - $len=\prod q_i^{\beta_i}$。
> - $c=\prod q_i^{\gamma_i}$。
> 
> 则上面条件等价于：对于任意的 $i$ 有 $\min(\gamma_i-\alpha_i,\beta_i)=0$。
>
> 如果 $\beta_i=0$，我只需要有 $0\le \alpha_i\le \gamma_i$；否则我们要有 $\alpha_i=\gamma_i$。
> 		
> 考虑 $t$ 关于 $q_i$ 的指数 $\delta_i$，显然为前者情况时必有 $\delta_i=0$，否则 $\delta_i=\gamma_i$。
>
> 则我们可以得到，对于任意 $i$ 有 $\alpha_i\ge \delta_i$，也就是 $p$ 必然是 $t$ 的倍数（并且由于 $t$ 是 $p$ 的 $\min$，所以存在一个 $p$ 可以取等）。
>
> 那么接下来根据平凡的分析，我们就可以得到上面的结论。

### Part 2

接下来我们来考虑计数问题。

下面记 $m$ 为孤立点个数，$a_i$ 为长为 $i$ 的链的个数，$b_i$ 为长为 $i$ 的环的个数，$t_i$ 为上面提到的当 $len=i$ 时的 $p_{\min}$。
		
计数的一个比较困难的点是我两条长度分别为 $2,3$ 的环补全为 $3,4$ 和补全为 $4,3$ 是不同的，也就是我每次考虑最终补全的一个大小为 $x$ 的环，如果从这个角度再进行计数的话，需要考虑的是前面选的环是有影响的。

那么我们这样子考虑：记录状态 $f_{i,j,k}$ 表示的是我当前考虑到了所有 $len\le i$ 的最终环的情况，然后还有 $j$ 个孤立点没有使用，还有 $k$ 条链没有封闭成环的方案总数。

考虑我们对于每个链到环的补全不是我在环的角度去选择一个链变成他，而是 **我每次往我现在还没有确定长度的链（也就是长度要 $>i$）的后面塞一个节点**。

而我们在最开始将 dp 数组初始化为 $m!$，这样子所有的孤立点也就变得 **不同**，即对应我们接下来 **依次取第一个孤立点塞到最后面**。

即我们要保证说我当前没有封闭成环的 $k$ 条链长度均为 $i$。

给出转移方程：

$$
\frac{f_{i-1,j,k}}{k!}\cdot(k+a_i)!\to f_{i,j+k,k+a_i}
$$
		
对于其中系数的解释是：我们认为这 $k$ 条链的是 **不同的**（其实和上面孤立点的处理是一样的），这一点是因为我们每次将不同的链封闭成环的方案数是不同的，这样子我们将链封闭成环只需要取一个前缀。
		
然后等把这些链都封闭成长为 $i'$ 的环的时候，再除掉前缀的长度的阶乘消除这些环又是相同的影响即可。

那么接下来我们也就要考虑把组成环的转移。
		
我们考虑枚举：我们用 $is$ 个孤立点组成了只有孤立点构成的 $s$ 个环，又拿出了前 $p$ 个环把他们封闭成环，则我们有：
		
$$
\frac{f_{i,j,k}}{i^ss!p!}[(s+p+b_i)\equiv 0 \pmod{t_i}]\to f_{i,j+is,k-p}
$$

对于系数的解释大概是：
- 这里的 $p!$ 就是上面提到的，这取出的 $p$ 条链封闭成环后又是 **相同** 的。
- $s!$ 与 $p!$ 同理。
- $i^s$ 是因为我们注意到这 $s$ 个环实际上都是个 **圆**，注意到圆排列方案数，我们要除掉一个 $\frac{(i-1)!}{i}=\frac{1}{i}$ 的系数。

分析上面那个算法的复杂度：注意到我们有 $p,s,k\le \lfloor\frac{n}{i}\rfloor$，所以复杂度即为：
		
$$
\mathcal{O}\left(\sum\limits_{i=1}^n \left (\frac{n}{i}\right )^3n\right)=\mathcal{O}\left(n^4\int_{1}^n \left (\frac{1}{x}\right )^3\mathrm{d}x\right)=\mathcal{O}(n^4)
$$
		
这个算法常数非常小并且跑不满（如果实现优秀的话），出题人尝试卡掉这个做法，不知道有没有成功（

### Part 3

考虑进一步优化：我们注意到其实最上面那个转移复杂度已经是 $\mathcal{O}(n^3)$，可以接受，考虑优化后面那步转移。

观察到其实对于 $p$ 和 $s$，除了 $[(s+p+b_i)\equiv 0 \pmod{t_i}]$ 这个系数之外，其系数和影响的维度都是互相独立的，我们可以对其进行分步卷积，注意到是 $\mathcal{O}(n^3)$ 的。

而如果其实考虑到这个系数关系也不大，我们将 $p$ 和 $s$ 按模 $t_i$ 进行划分等价类，我们每次取出对于 $p$ 的余 $r$ 和对于 $s$ 的余 $-r-b_i$ 的两个类，进行卷积即可。

由于每个 $p$ 和 $s$ 都还是之后进行一次卷积，所以复杂度仍然是 $\mathcal{O}(n^3)$ 的。
		
常数很小，可以通过所有测试点。

## Code

```cpp
#include<bits/stdc++.h>
//#define int long long
//#pragma GCC optimize(3,"Ofast","inline")
#define ll long long
#define i128 __int128
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
void file_IO() {
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
}
bool M1;
template<int p>
struct mint {
	int x;
	mint() {
		x=0;
	}
	mint(int _x) {
		x=_x;
	}
	friend mint operator + (mint a,mint b) {
		return a.x+b.x>=p? a.x+b.x-p:a.x+b.x;
	}
	friend mint operator - (mint a,mint b)  {
		return a.x<b.x? a.x-b.x+p:a.x-b.x;
	}
	friend mint operator * (mint a,mint b) {
		return 1ll*a.x*b.x%p;
	}
	friend mint operator ^ (mint a,ll b) {
		mint res=1,base=a;
		while(b) {
			if(b&1)
				res*=base;
			base*=base; b>>=1;
		}
		return res;
	}
	friend mint operator ~ (mint a) {
		return a^(p-2);
	}
	friend mint operator / (mint a,mint b) {
		return a*(~b);
	}
	friend mint & operator += (mint& a,mint b) {
		return a=a+b;
	}
	friend mint & operator -= (mint& a,mint b) {
		return a=a-b;
	}
	friend mint & operator *= (mint& a,mint b) {
		return a=a*b;
	}
	friend mint & operator /= (mint& a,mint b) {
		return a=a/b;
	}
	friend mint operator ++ (mint& a) {
		return a+=1;
	}
	friend mint operator -- (mint& a) {
		return a-=1;
	}
};
const int MOD=998244353;
#define mint mint<MOD>
const int N=3e3+5;
int p[N],n,k,cnt1[N],cnt2[N],in[N],g[N],c;
bool used[N];
mint f[2][N][N],jc[N],inv_jc[N],inv_p[N][N],h[N][N],tmp[N][N];
vector<int> vecs[N],vecp[N];
void init(int n=3e3) {
	jc[0]=1;
	rep(i,1,n)
		jc[i]=jc[i-1]*i;
	inv_jc[n]=~jc[n];
	per(i,n-1,0)
		inv_jc[i]=inv_jc[i+1]*(i+1);
}
mint C(int n,int m) {
	if(n<m)
		return 0;
	return jc[n]*inv_jc[n-m]*inv_jc[m];
}
void dfs(int x,int len) {
	if(x==-1) {
		++cnt1[len];
		return;
	}
	if(used[x]) {
		++cnt2[len];
		return;
	}
	++c;
	used[x]=true;
	dfs(p[x],len+1);
}
void solve() {
	scanf("%d%d",&n,&k);
	rep(i,1,n) {
		int d=__gcd(i,k);
		if(!g[i/d])
			g[i/d]=d;
	}
	rep(i,1,n) {
		scanf("%d",&p[i]);
		if(p[i]!=-1)
			++in[p[i]];
	}
	rep(i,1,n) {
		if(p[i]!=-1&&!in[i])
			dfs(i,0);
	}
	rep(i,1,n) {
		if(p[i]!=-1&&!used[i])
			dfs(i,0);
	}
	c=n-c;
	int tot=0;
	rep(i,0,c)
		f[1][i][0]=jc[c]*inv_jc[i];
	rep(i,2,n) {
		int m=n/i,d=g[i];
		tot+=cnt1[i];
		rep(j,0,m)
			inv_p[i][j]=~(mint(i)^j);
		rep(j,0,c) {
			rep(k,0,tot)
				f[i&1][j][k]=h[j][k]=0;
		}
		rep(j,0,c) {
			rep(k,0,min(tot-cnt1[i],c-j))
				h[j+k][k+cnt1[i]]+=f[(i-1)&1][j][k]*inv_jc[k]*jc[k+cnt1[i]];
		}
		if(!d) {
			if(cnt2[i]) {
				puts("0");
				return;
			}
			rep(j,0,c) {
				rep(k,0,tot)
					f[i&1][j][k]=h[j][k];
			}
			continue;
		}
		rep(i,0,d-1) {
			vecp[i].clear();
			vecs[i].clear();
		}
		rep(p,0,min(tot,n/i))
			vecp[p%d].push_back(p);
		rep(s,0,c/i)
			vecs[s%d].push_back(s);
		rep(pm,0,d-1) {
			vector<int> vp=vecp[pm],vs=vecs[((d-pm-cnt2[i])%d+d)%d];
			if(vp.empty()||vs.empty())
				continue;
			rep(j,0,c) {
				rep(k,0,tot)
					tmp[j][k]=0;
			}
			for(auto p:vp) {
				rep(j,0,c) {
					rep(k,p,min(tot,n/i))
						tmp[j][k-p]+=h[j][k]*inv_jc[p];
				}
			}
			for(auto s:vs) {
				rep(j,0,c-i*s) {
					rep(k,0,min(tot,n/i))
						f[i&1][j+i*s][k]+=tmp[j][k]*inv_jc[s]*inv_p[i][s];
				}
			}
		}
	}
	printf("%d\n",f[n&1][c][0].x);
}
bool M2;
// g++ T6.cpp -std=c++14 -Wall -O2 -o T6
signed main() {
//	file_IO();
	int testcase=1;
	init();
	//scanf("%d",&testcase);
	while(testcase--)
		solve();
	cerr<<"used time = "<<1000*clock()/CLOCKS_PER_SEC<<"ms\n";
	cerr<<"used memory = "<<(&M2-&M1)/1024/1024<<"MB\n";
	return 0;
}
```

---

## 作者：_lmh_ (赞：1)

参考了官方题解。

先考虑置换的 $c$ 次方的性质，不难发现一个长为 $x$ 的环被拆成了多个长为 $\frac{x}{(x,c)}$ 的环。并且可以证明，如果 $y=\frac{x}{(x,c)}$ 为定值，那么 $x$ 一定是其可能的最小值 $x_{\min}$ 的倍数。（证明：看 $c$ 质因子分解后的每一项 $p^\alpha$，一定有 $(x,p)=1$ 或 $p^\alpha|x$，而可以 $(x,p)=1$ 当且仅当 $(y,p)=1$。）

给定 $y$ 时，令这个最小的 $x_{\min}=h_y$。

对每种长度的置换环进行计数，假设最后有 $S_i$ 个长为 $S$ 的环，如果它存在 $c$ 次方根，那么一定有 $h_i|S_i$。

预处理出孤立点的个数 $m$，长为 $i$ 的链个数 $l_i$，长为 $i$ 的环个数 $r_i$。

考虑 dp，令 $f_{i,j,k}$ 代表选出了所有长度 $\le i$ 的环，用了 $j$ 个孤立点，还剩下 $k$ 个长度为 $i$ 的链没有封闭。初始时 $f_{0,0,0}=m!$。我们认为剩余孤立点已经按照之后被选择的顺序排好，并且所有链也按照之后封闭的顺序排好。

需要一个辅助数组 $g_{i,j,k}$ 代表选出了所有长度 $<i$ 的环，用了 $j$ 个孤立点，还剩下 $k$ 个长度为 $i$ 的链没有封闭。

考虑转移，先从 $f$ 向 $g$ 转移，给每个没有封闭的链拼上一个点，$g_{i,j+k,k+l_i}\leftarrow f_{i,j,k}\cdot\binom{k+l_i}{l_i}l_i!$。这里这个转移系数是为了把 $a_i$ 条新链选择一个顺序并插入原来的 $k$ 条链当中。

再从 $g$ 向 $f$ 转移，选择一些环把它们封口。假设有 $x$ 个只由孤立点组成的环，$y$ 个从 $k$ 条链中变出来的环，那么 $f_{i,j+ix,k-y}\leftarrow g_{i,j,k}\frac{1}{i^xx!y!}(h_i|x+y+r_i)$。链变成环之后不再区分，所以要除以 $x!y!$；同时一个环有 $i$ 种等价的破环为链的方式，还要再除以 $i^x$。

这个复杂度看上去不太对。$i,j\in [1,n]$，但 $k,x,y\in [1,\frac{n}{i}]$，所以第一个转移是 $O(n^2\log n)$ 的，而第二个转移次数为 $n\sum_{i=1}^{n}(\frac{n}{i})^3$，这是 $O(n^4)$ 的，确实没法通过。

但是常数非常小，写出来一看可以过除了最后一个子任务外的所有测试点。经过一些优化之后极限数据依然需要 2.5s，怎么办？

发现 $h_i=1$ 的时候转移最慢，但此时 $x+y+r_i$ 没有限制，所以可以把 $x,y$ 分两步转移。否则，优化 $y$ 的枚举过程，让它每次增大 $h_i$。这个复杂度不太好算，但写出来可以轻松通过，在本题数据下和正解一样快。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1007,MOD=998244353;
ll n,m,c,f[2][N][N],h[N],p[N],s[N],a[N],b[N],vis[N],fac[N],ifac[N],nP,pri[N],cpri[N],coef[N][N],A[N][N];
ll qpow(ll x,ll k){
	ll sum=1;
	while(k){
		if (k&1) (sum*=x)%=MOD;
		(x*=x)%=MOD;k>>=1;
	}
	return sum;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	for (int i=fac[0]=1;i<N;++i) fac[i]=fac[i-1]*i%MOD;
	ifac[N-1]=qpow(fac[N-1],MOD-2);
	for (int i=N-1;i;--i) ifac[i-1]=ifac[i]*i%MOD;
	cin>>n>>c;
	m=c;
	while(m!=1){
		bool fl=0;
		for (ll i=2;i*i<=m;++i) if (m%i==0){
			pri[++nP]=i;cpri[nP]=1;
			while(m%i==0){cpri[nP]*=i;m/=i;}
			fl=1;break;
		}
		if (!fl){
			pri[++nP]=m;cpri[nP]=m;break;
		}
	}
	for (int i=1;i<=n;++i){
		h[i]=1;
		for (int j=1;j<=nP;++j) if (i%pri[j]==0) h[i]*=cpri[j];
	}
	m=0;
	for (int i=1;i<=n;++i){
		cin>>p[i];
		if (p[i]==-1) p[i]=0;
		if (p[i]) s[p[i]]=i;
	}
	for (int i=1;i<=n;++i) if (p[i]==0&&s[i]==0) ++m;
	for (int i=1;i<=n;++i) if (p[i]&&vis[i]==0){
		int x=i,c=0;
		do{
			++c;vis[x]=1;x=p[x];
		}while(x&&x!=i);
		if (x==i) ++b[c];
		else{
			x=s[i];
			while(x){++c;vis[x]=1;x=s[x];}
			++a[c];
		}
	}
	f[0][0][0]=fac[m];
	for (int i=1;i<=n;++i){
		coef[i][0]=1;
		ll x=qpow(i,MOD-2);
		for (int j=1;j<=n;++j) coef[i][j]=coef[i][j-1]*x%MOD;
		for (int j=1;j<=n;++j) (coef[i][j]*=ifac[j])%=MOD;
	}
	for (int i=0;i<=n;++i) for (int j=0;j<=i;++j) A[i][j]=fac[i]*ifac[j]%MOD;
	for (int i=1;i<=n;++i){
		int now=i&1,pre=(i&1)^1;
		for (int j=0;j<=m;++j){
			int lim=min(m-j,n-a[i]);
			for (int k=0;i*k<=n;++k) if (f[pre][j][k]){
				if (k<=lim) (f[now][j+k][k+a[i]]+=f[pre][j][k]*A[k+a[i]][k])%=MOD;
				f[pre][j][k]=0;
			}
		}
		if (h[i]==1){
			for (int j=m;~j;--j) for (int k=0;i*k<=n;++k) if (f[now][j][k]){
//				cout<<"trans "<<i<<' '<<j<<' '<<k<<' '<<f[now][j][k]<<endl;
				ll tmp=f[now][j][k];f[now][j][k]=0;
				for (int lim,s=0,t=j;t<=m;++s,t+=i) (f[now][t][k]+=tmp*coef[i][s])%=MOD;
			}
			for (int j=m;~j;--j) for (int k=0;i*k<=n;++k) if (f[now][j][k]){
//				cout<<"trans "<<i<<' '<<j<<' '<<k<<' '<<f[now][j][k]<<endl;
				ll tmp=f[now][j][k];f[now][j][k]=0;
				for (int p=0;p<=k;++p) (f[now][j][k-p]+=tmp*ifac[p])%=MOD;
			}
		}
		else{
			for (int j=m;~j;--j) for (int k=0;i*k<=n;++k) if (f[now][j][k]){
//				cout<<"trans "<<i<<' '<<j<<' '<<k<<' '<<f[now][j][k]<<endl;
				ll tmp=f[now][j][k];f[now][j][k]=0;
				for (int lim,s=0,t=j;t<=m;++s,t+=i){
					lim=h[i]-(s+b[i])%h[i];if (lim==h[i]) lim=0;
					for (int p=lim;p<=k;p+=h[i]) (f[now][t][k-p]+=tmp*coef[i][s]%MOD*ifac[p])%=MOD;
				}
			}
		}
	}
	cout<<f[n&1][m][0]<<endl;
	return 0;
}
```

---

