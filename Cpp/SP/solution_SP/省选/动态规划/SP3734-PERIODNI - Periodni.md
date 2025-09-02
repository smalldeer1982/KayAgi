# PERIODNI - Periodni

## 题目描述

 [English](/problems/PERIODNI/en/) [Vietnamese](/problems/PERIODNI/vn/)Luka is bored in chemistry class so he is staring at a large periodic table of chemical elements hanging from a wall above the blackboard. To kill time, Luka decided to make his own table completely different from the one in the classroom.

His table consists of N columns, each with some height, aligned at the bottom (see example below). After he draws the table he needs to fill it with elements. He first decided to enter the noble gases of which there are K. Luka must put them in the table so that no two noble gases are close to each other.

Two squares in the table are close to each other if they are in the same column or row, and all squares between them exist. In the example below, the 'a' squares are not close, but the 'b' squares are.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP3734/87f0da7d42d32cf3ae36c86030240397dce7472a.png)

Write a program that, given N, K and the heights of the N columns, calculates the total number of ways for Luka to place the noble gases into the table. This number can be large, so output it modulo 1 000 000 007.

## 样例 #1

### 输入

```
5 2
2 3 1 2 4```

### 输出

```
43```

# 题解

## 作者：Imitators (赞：12)

笛卡尔树？我看就是个分治+背包。

还是把原图形划分成矩形，划分方法类似于扫描线。 

如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/5a5qmum6.png)

设 $a_i$ 在 $i\in [l,r]$ 时最小值为 ${Min}$.

按 $Min$ 的位置划分成几个小段。如:

![](https://cdn.luogu.com.cn/upload/image_hosting/2peqmrj6.png)

我们想这么划分的好处是什么，好处就在于每一个块上面的块，都是独立的，彼此不会互相影响。

因为是独立的所以可以通过乘法原理把上面的两块"合并"。

为了叙述方便我们可以把每个矩形编号。

1. 设 $\large{ \mathcal{g_{x,k}}}$ 表示编号为 $x$ 的矩形内不选，它上面一共选 $k$ 个的方案数。
2. 设 $\large{ \mathcal{f_{x,k}}}$ 表示编号位 $x$ 的矩形算内部和上面一共选 $k$ 个的方案数。

把 $x,y$ 合并
$$h_{k}=\sum_{i=0}^{k}g_{x,i}\times g_{y,k-i}$$

那么显然，假如矩形 $x$ 上面可以被分成 $m$ 段。

那 $x$ 的 $g_{x,k}$ 值可以通过 $m-1$ 次合并得到。（因为这个卷积一样的东西满足结合律）

$$f_{x,k}=\sum_{i=0}^{k}g_{x,i}\times\tbinom{H}{k-i}\times\tbinom{L-i}{k-i}\times (k-i)!$$

这里的 $H$ 表示的是底下$Min$ 所在整块的高度,$L$ 表示其长度。

答案即为 $\large{ \mathcal{f_{n,k}}}$。

复杂度:合并一次 $O(n^2)$,合并次数的数量级为 $n$,总复杂度 $O(n^3)$。

[$\mathcal{Code}$](https://www.luogu.com.cn/paste/gkwova9e)

---

## 作者：_luanyi_ (赞：11)

一道十分神奇的题目。

首先，本题中的图形形状过于诡异，我们可以把它拆成若干个矩形，对于每个矩形单独处理，最后合并答案。为了方便处理，笔者使用的方法如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/aej3kk78.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/dqov3xky.png)

从以上图形中不难看出：设这段图形是 $[l,r]$，则图中的 C 和 F 区域长度即为 $r-l+1$，高度即为 $\min\{h_i\},i\in[l,r]$，然后上方的图形分为左右两个区域，递归处理即可。

在这个分图形的过程中，不难发现，这就是一颗笛卡尔树的建树过程，其中 $i$ 满足二叉搜索树，$h_i$ 满足小根堆，于是我们可以优化建树的过程（其实不优化也可以，但跑得可能相对会慢一些）。

***

接下来考虑怎么统计答案。

首先我们先来给各个矩形编号以方便处理。

对于长在 $[l,r]$ 的矩形，我们令其编号为 $u$，当且仅当 $\min\{h_i\}=h_u,i\in[l,r]$，若有多个满足条件的 $u$ 任选其一即可。容易发现，如果我们以 $u$ 为界限，将编号为 $u$ 的矩形上方的图形分为两个并递归处理（即上面所讲的笛卡尔树建树过程），每个矩形的编号不重复。

接下来，设 $f[u][k]$ 表示编号为 $u$ 的**矩形即其上方图形部分**中放入 $k$ 个数且满足题设条件的方案数。

对于上面的 A，不难发现，如果当前矩形上方什么也没有，设 $a$ 为矩形的长（$r-l+1$），$b$ 为矩形的宽，那么

$$
f[u][k]=\dfrac{A_a^kA_b^k}{A_k^k}
$$

解释：从 $a$ 列里有序选 $k$ 列，从 $b$ 行里有序选择 $k$ 行，得到 $k$ 个有序的交点，但由于填入 $k$ 个无序的数，所以要去重。

接下来考虑答案的合并。

设编号为 $u$ 的矩形上方部分中左边部分的编号为 $l$（即笛卡尔树中的该节点的左儿子），右边部分为 $r$（即笛卡尔树中的该节点的右儿子），我们可以枚举在 $l$ 中放了 $i$ 个数，在 $r$ 中放了 $j$ 个数，于是在矩形中便要放 $k-i-j$。不难发现

$$
f[u][k]=\sum_{i=0}^{k}\sum_{j=0}^{k-i}f[l][i]\times f[r][j]\times\dfrac{A_{a-i-j}^{k-i-j}A_b^{k-i-j}}{A_{k-i-j}^{k-i-j}}
$$

其中 $a$ 为矩形的长，$b$ 为矩形的宽。

但是这个式子的时间复杂度是遍历树 $O(n)$ 乘上枚举 $k,i,j$ 共为 $O(nk^3)$，过不了。

考虑设

$$
g[u][p]=\sum_{i+j=p}f[l][i]\times f[r][j]
$$

该式子为 $O(k^2)$。

则

$$
f[u][k]=\sum_{p=0}^{k}g[u][p]\times\dfrac{A_{a-p}^{k-p}A_b^{k-p}}{A_{k-p}^{k-p}}
$$

式子被优化成了 $O(k^2)$。

此时总复杂度已经降为 $O(nk^2)$，可过。

***

**code**

```cpp
#include <bits/stdc++.h>
#define fq(i,a,b) for (int i = (a); i <= (b); i++)
using namespace std;
#define int long long
inline int rd () {
	int f = 1;
	char ch = getchar ();
	while (!isdigit (ch)) (ch == '-' ? (f = -1) : 0), ch = getchar ();
	int num = 0;
	while (isdigit (ch)) num = num * 10 + ch - '0', ch = getchar ();
	return num * f;
}
#define d rd ()

const int maxn = 550;
const int mod = 1e9+7;
int n = d, k = d, h[maxn];
int l[maxn], r[maxn], sk[maxn], top;
int mul[1001000], invm[1001000];
bool cmp (int a, int b) {
    return h[a] < h[b];
}
int f[maxn][maxn], g[maxn], sz[maxn];
void prew (int u) {
    sz[u] = 1;
    if (l[u]) prew (l[u]), sz[u] += sz[l[u]];
    if (r[u]) prew (r[u]), sz[u] += sz[r[u]];
}
int A (int N, int M) {
    if (M > N) return 0;
    return mul[N] * invm[N - M] % mod;
}
int sol (int N, int M, int K) {
    return A (N, K) * A (M, K) % mod * invm[K] % mod;
}
void dfs (int u, int low) {
    int uh = h[u] - low;
    if (!l[u] && !r[u]) {
        f[u][0] = 1;
        fq (i, 1, k) f[u][i] = sol (sz[u], uh, i);
        return;
    }
    if (!l[u] || !r[u]) {
        int v;
        if (!l[u]) v = r[u];
        else v = l[u];
        dfs (v, h[u]);
        memset (g, 0, sizeof g);
        g[0] = 1;
        fq (i, 1, k) fq (j, 0, i) g[i] = (g[i] + f[0][j] * f[v][i - j]) % mod;
        f[u][0] = 1;
        fq (i, 1, k) fq (j, 0, i) f[u][i] = (f[u][i] + g[j] * sol (uh, sz[u] - j, i - j)) % mod;
        return;
    }
    dfs (l[u], h[u]);
    dfs (r[u], h[u]);
    memset (g, 0, sizeof g);
    g[0] = 1;
    fq (i, 1, k) fq (j, 0, i) g[i] = (g[i] + f[l[u]][j] * f[r[u]][i - j]) % mod;
    f[u][0] = 1;
    fq (i, 1, k) fq (j, 0, i) f[u][i] = (f[u][i] + g[j] * sol (uh, sz[u] - j, i - j)) % mod;
}
int power (int a, int b, int p) {
	int c = 1;
	while (b) {
		if (b & 1) c = c * a % p;
		a = a * a % p;
		b >>= 1;
	} return c;
}
signed main () {
    mul[0] = invm[0] = 1;
    fq (i, 1, 1000000) {
        mul[i] = mul[i - 1] * i % mod;
        invm[i] = invm[i - 1] * power (i, mod - 2, mod) % mod;
    }
    fq (i, 1, n) h[i] = d;
    fq (i, 1, n) {
        int kk = top;
        while (kk && h[sk[kk]] > h[i]) --kk;
        if (kk) r[sk[kk]] = i;
        if (kk != top) l[i] = sk[kk + 1];
        sk[top = ++kk] = i;
    } prew (sk[1]); f[0][0] = 1;
    dfs (sk[1], 0); cout << f[sk[1]][k] << endl;
	return 0;
}

```

---

## 作者：Register (赞：10)

1. 看到这是一个类似于直方图最大矩形覆盖的题目，可以想到**笛卡尔树**

笛卡尔树干了些啥？

![](https://cdn.luogu.com.cn/upload/image_hosting/2mcgakym.png)

笛卡尔树把直方图划分成了这样

不会笛卡尔树？请左转百度自行搜索

2. 每个节点相当于是一个矩形

所以把每个矩形分开讨论

- 可以**树形DP**

3. 先看看在 $n\times m$ 的矩形内方 $k$ 个点的方案

由于不能重复，就变成了选择 $k$ 行和 $k$ 列并两两配对的方案数

选 $k$ 行为 $C_n^k$

选 $k$ 列为 $C_m^k$

两两配对相当于全排列为 $k!$

乘法原理，方案数为 $C_n^kC_m^kk!$

4. DP状态

设 $F_{x,i}$ 为笛卡尔树上 $x$ 号结点子树选 $i$ 列的方案数

初始状态： $F_{x,0}=1$

合并子树答案，类似于背包问题，同样也是乘法原理： $F_{x,i}=\sum F_{son,j}\times F_{x,i-j}$

最后再进行一次背包，加上本身对应矩形的方案数： $F_{x,i}=\sum F_{x,i-j}*C_{high}^jC_{size}^jj!$

### 代码：

```cpp
#include <cstdio>
#define int long long
const int mod=1e9+7;
int n,k,top,v,a[501],sz[501],s[501],c[501][2],f[501][501],fa[1000001],p[1000002],inv[1000001];
inline int read(){
	char ch=getchar();int res=0,w=1;
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {res=res*10+ch-'0';ch=getchar();}
	return res*w;
}
inline int Min(int x,int y) {return x<y?x:y;}
inline int qpow(int x,int y){
	int res=1;
	while(y)
	{
		if(y&1) res=res*x%mod;
		x=x*x%mod;y>>=1;
	}
	return res;
}
inline int C(int nn,int mm) {return nn<mm?0:fa[nn]*inv[mm]%mod*inv[nn-mm]%mod;}
void dfs(int x,int t){
	f[x][0]=1;sz[x]=1;
	for(register int i=0;i<2;i++)
		if(c[x][i])
		{
			dfs(c[x][i],a[x]);sz[x]+=sz[c[x][i]];
			for(register int j=Min(sz[x],k);~j;j--)
				for(register int l=1;l<=Min(sz[c[x][i]],j);l++) f[x][j]=(f[x][j]+f[c[x][i]][l]*f[x][j-l]%mod)%mod;
		}
	for(register int i=Min(sz[x],k);~i;i--)
		for(register int j=1;j<=Min(a[x]-t,i);j++)
		f[x][i]=(f[x][i]+f[x][i-j]*fa[j]%mod*C(a[x]-t,j)%mod*C(sz[x]-(i-j),j)%mod)%mod;
}
signed main(){
	n=read();k=read();p[1000000]=1000000;p[1000001]=fa[1]=fa[0]=inv[1]=inv[0]=1;
	for(register int i=999999;i;i--) p[i]=(p[i+1]*i)%mod;
	v=qpow(p[1],mod-2);
	for(register int i=2;i<=1000000;i++) {fa[i]=(fa[i-1]*i)%mod;inv[i]=v*p[i+1]%mod;}
	for(register int i=1,j;i<=n;i++)
	{
		a[i]=read();j=top;
		while(j&&a[s[j]]>a[i]) j--;
		if(j) c[s[j]][1]=i;
		if(j<top) c[i][0]=s[j+1];
		top=j;s[++top]=i;
	}
	dfs(s[1],0);printf("%d\n",f[s[1]][k]);
	return 0;
}
```

~~注：如码风及可读性引起不适，请勿吐槽~~

---

## 作者：AlanSP (赞：9)

### Description

> 给定一个N列的表格，每列的高度各不相同，但底部对齐，然后向表格中填入K个相同的数，填写时要求不能有两个数在同一列，或同一行,求总方案数。

---

笛卡尔树+DP经典题。

考虑简化版的题意：若表格每列行数一定，放入k个数的方案。

不难想到任何一个数必须独占一整行和整列，所以要选出k行和k列。

选出k行和k列，配对成k个点，分别有k,k-1,k-2……1中选择，共 $k!$ 种方案。

故总方案数为：
$$
\binom n k\times\binom n k\times k!
$$

---

那么对于原图种参差不齐的图形，我们可以把它分为很多个矩形。

对于单个矩形，我们可以用上述方式求解。

不难看出，对于高度较低的点，我们总可以拼凑出满足要求的矩形。

我们可以枚举当前矩形所用的数字，并把剩下的数分配给比它大的列。

当前列会把原图分为左右两个部分，两个部分间互不影响，构成子问题。

这隐约形成了一种树形结构。

并且我们要找最小的列作为树根，这不难想到笛卡尔树。

---

设 $f[i][j]$ 表示**以i为根的子树内放了j个数的方案数**，$f[i][0]=1$ 。

那么我们可以递归子树进行拼接，类似树形背包：
$$
f[i][j]=\sum_{k=0}^jf[i][j-k]*f[son_i][k]
$$
最后还要计算当前矩形放数字的方案数，枚举即可。

**一定记住倒序枚举，省去了子树一维，注意枚举边界。**

---

### Code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=509,M=1000000,mod=1e9+7;
int stk[N],top,n,K,a[N],f[N][N],ans;
int inv[M+9],fac[M+9],cur;
struct Node
{
	int ch[2],siz;
} tr[N];

inline void build()
{
	for(int i=1;i<=n;i++)
	{
		cur=top;
		while(cur&&a[stk[cur]]>a[i]) --cur;
		if(cur) tr[stk[cur]].ch[1]=i;
		if(cur<top) tr[i].ch[0]=stk[cur+1];
		stk[++cur]=i;
		top=cur;
	}
}

inline void init()
{
	fac[0]=fac[1]=inv[1]=inv[0]=1;
	for(int i=2;i<=M;i++) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<=M;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=M;i++) inv[i]=1ll*inv[i]*inv[i-1]%mod;
}

inline int C(int n,int m)
{
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}

void dfs(int u,int H)//H表示前一个节点的高度
{
	f[u][0]=1;
	tr[u].siz=1;
	for(int p=0;p<=1; p++)
	{
		int v=tr[u].ch[p];
		if(!v) continue;
		dfs(v,a[u]);
		tr[u].siz+=tr[v].siz;
		for(int i=min(tr[u].siz,K);i>=0;i--)
			for(int j=1;j<=min(tr[v].siz,i);j++)
				f[u][i]=(f[u][i]+1ll*f[u][i-j]*f[v][j]%mod)%mod;
	}
	for(int i=min(K,tr[u].siz);i>=0;i--)
		for(int j=1;j<=min(a[u]-H,i);j++)
			f[u][i]=(f[u][i]+1ll*f[u][i-j]*fac[j]%mod*C(a[u]-H,j)%mod*C(tr[u].siz-(i-j),j)%mod)%mod;
}

int main()
{
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	build();
	init();
	dfs(stk[1],0);
	printf("%d",f[stk[1]][K]);
	return 0;
}
```



---

## 作者：lemir3 (赞：5)

## 题目分析

首先可以发现这个不规则的图形可以用笛卡尔树来表示成树形结构.

首先取最低的矩形作为根,然后在左边找到最低的矩形作为左儿子,在右边找到最低的作为右儿子,取最值可以预处理出一个st表,递归地这样做下去就构出了一颗笛卡尔树,树上的每个节点代表图上一个矩形.

然后在这棵树上考使用树形dp,设f(i,j)表示i点的子树内放j个数的方案数,g(i,j)表示i点代表的矩形里什么都不放,j个数全放在子树里的方案数,设点表示的矩阵宽为b,高为a.

这样就可以得到转移:

> $g[u][i]+=f[c[u][0]][j] \times f[c[u][1]][i-j] ~(0 \leq j \leq i)$
>
> $f[u][i]+=g[u][j] \times C^a_{i-j} \times C^{b-j}_{i-j} \times (i-j)! ~(0 \leq j \leq i)$

第一个很好懂,因为左右子树互不影响,所以直接并起来即可.

第二个就是考虑在子树里放了j个,自己的矩形里放i-j个,因为数放在子树里,所以当前矩形的宽上只剩b-j个位置,高上全都可以放,让后乘上这i-j个的全排列即可.

## 代码

```cpp
#define R register
#define INF 0x3f3f3f3f
#define debug(x) printf("debug:%lld\n",x)
#define debugi(x) printf("debug:%d\n",x)
#define debugf(x) printf("debug:%llf\n",x)
#define endl putchar('\n')
typedef long long lxl;
const lxl maxn=510,maxa=1000010,mod=1e9+7;
lxl n,k,root;
lxl h[maxn],lg[maxn],st[maxn][11],c[maxn][2],a[maxn],b[maxn],f[maxn][maxn],g[maxn][maxn],fac[maxa],inv[maxa],inv2[maxa];
inline lxl read()
{
	char c=getchar();
	lxl f=1,x=0;
	for(;!isdigit(c);(c=='-')&&(f=-1),c=getchar());
	for(;isdigit(c);x=(x<<1)+(x<<3)+(c^48),c=getchar());
	return f*x;
}
inline lxl C(lxl a,lxl b)
{
	if(a<b)return 0;
	return fac[a]*inv2[a-b]%mod*inv2[b]%mod;
}
inline void GetST()
{
	lg[0]=-1;
	for(R int i(1);i<=n;lg[i]=lg[i>>1]+1,st[i][0]=i,++i);
	for(R int j(1);j<=10;++j)
		for(R int i(1);i+(1<<j)-1<=n;++i)
			st[i][j]=h[st[i][j-1]]<=h[st[i+(1<<(j-1))][j-1]]?st[i][j-1]:st[i+(1<<(j-1))][j-1];
}
inline lxl query(lxl l,lxl r)
{
	lxl t=lg[r-l+1];
	return h[st[l][t]]<=h[st[r-(1<<t)+1][t]]?st[l][t]:st[r-(1<<t)+1][t];
}
lxl build(lxl l,lxl r)
{
	if(l>r)return 0;
	lxl mid=query(l,r);
	c[mid][0]=build(l,mid-1),c[mid][1]=build(mid+1,r);
	a[c[mid][0]]=h[c[mid][0]]-h[mid];
	a[c[mid][1]]=h[c[mid][1]]-h[mid];
	b[mid]=r-l+1;
	return mid;
}
inline lxl get(lxl a,lxl b,lxl k)
{
	if(a<k||b<k)return 0;
	lxl res=fac[k]*C(a,k)%mod*C(b,k)%mod;
	return res;
}
void dfs(lxl u)
{
	f[u][0]=g[u][0]=1;
	if(!u)return;
	dfs(c[u][0]),dfs(c[u][1]);
	for(R int i(1);i<=k;++i)
		for(R int j(0);j<=i;++j)
			g[u][i]=(g[u][i]+f[c[u][0]][j]*f[c[u][1]][i-j]%mod)%mod;
	for(R int i(1);i<=k;++i)
		for(R int j(0);j<=i;++j)
			if(g[u][j])f[u][i]=(f[u][i]+(g[u][j]*get(a[u],b[u]-j,i-j)%mod))%mod;
}
int main(void)
{
	fac[0]=inv[0]=inv2[0]=fac[1]=inv[1]=inv2[1]=1;
	for(R int i(2);i<maxa;++i)
		fac[i]=i*fac[i-1]%mod,inv[i]=(mod-(mod/i)*inv[mod%i]%mod)%mod,inv2[i]=inv2[i-1]*inv[i]%mod;
	n=read(),k=read();
	for(R int i(1);i<=n;h[i]=read(),++i);
	GetST();
	root=build(1,n);a[root]=h[root];
	dfs(root);
	printf("%lld\n",f[root][k]);
	return 0;
}
```

---

## 作者：lhm_ (赞：4)

考虑用$DP$和组合数学来解决。

因为原图像不规则的形状不好处理，所以先用笛卡尔树（性质为小根堆）将其划分成一个一个的矩形。

![](https://s2.ax1x.com/2020/01/15/lLBc5j.png)

发现在笛卡尔树上的每个节点都对应一个矩形，矩形高为$h_x-h_{fa_x}$，宽为$size_x$。

结合笛卡尔树的性质，不难得到，红色矩形所对应的节点的两个儿子为绿色矩形和蓝色矩形。

![](https://s2.ax1x.com/2020/01/15/lLBRGn.png)

设$f_{x,i}$为在节点$x$所对应的矩形及其以上的图形中放$i$个点的方案数，那么答案为$f_{root,k}$

与子树合并时只需枚举在子树图像中放的点个数，再用乘法原理乘起来。

再考虑其本身的矩形。

若是在一个$n \times m$的矩形中放$k$个点，其方案数为$C_{n}^kC_{m}^kk!$，因为你需要从$n$行中选$k$行，从$m$列中选$k$列，同时这些选择的顺序可以改变，所以再乘上$k!$。

那么再考虑本身的矩形时，枚举在自身的矩形中放的点个数，再乘上$C_{n}^kC_{m}^kk!$即可

实现细节就看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 5010
#define mod 1000000007
template<typename T> inline void read(T &x)
{
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(flag)x=-x;
}
ll n,k,top,root;
ll ls[maxn],rs[maxn],st[maxn];
ll f[maxn][maxn],h[maxn],siz[maxn],fac[1000050],inv[1000050];
ll qp(ll x,ll y)
{
    ll ans=1;
    while(y)
    {
        if(y&1) ans=(ans*x)%mod;
        x=(x*x)%mod;
        y>>=1;
    }
    return ans%mod;
}
void init()
{
    fac[0]=fac[1]=inv[0]=inv[1]=1;
	fac[2]=2,inv[2]=qp(2,mod-2);
	for(int i=3;i<=1000000;++i)
	{
		fac[i]=(fac[i-1]*i)%mod;
		inv[i]=qp(fac[i],mod-2);
	}
}
ll C(ll n,ll m)
{
    if(n<m) return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int build()
{
    for(int i=1;i<=n;++i)
    {
        while(top&&h[st[top]]>h[i]) ls[i]=st[top--];
        if(top) rs[st[top]]=i;
        st[++top]=i;
    }
    return st[1];
}
void dfs(int x,int val)
{
    f[x][0]=siz[x]=1;
    ll high=h[x]-val;
    if(ls[x])
    {
        ll y=ls[x];
        dfs(y,h[x]),siz[x]+=siz[y];
        for(ll i=min(siz[x],k);i>=0;--i)
            for(ll j=1;j<=min(siz[y],i);++j)
                f[x][i]=(f[x][i]+f[y][j]*f[x][i-j]%mod)%mod;
    }
    if(rs[x])
    {
        ll y=rs[x];
        dfs(y,h[x]),siz[x]+=siz[y];
        for(ll i=min(siz[x],k);i>=0;--i)
            for(ll j=1;j<=min(siz[y],i);++j)
                f[x][i]=(f[x][i]+f[y][j]*f[x][i-j]%mod)%mod;
    }
    for(ll i=min(siz[x],k);i>=0;--i)
        for(ll j=1;j<=min(high,i);++j)
            f[x][i]=(f[x][i]+f[x][i-j]*fac[j]%mod*C(high,j)%mod*C(siz[x]-(i-j),j)%mod)%mod;
}
int main()
{
    init();
    read(n),read(k);
    for(int i=1;i<=n;++i) read(h[i]);
    root=build();
    dfs(root,0);
    printf("%lld",f[root][k]);
	return 0;
}
```

---

## 作者：yijan (赞：3)

### SPOJ PERIODNI 

不知道公式会不会出问题，建议到 [这里](https://www.yijan.co/spoj-periodni/) 或者 Luogu 博客查看。

仍然考虑类笛卡尔树的 dp，我们把整个直方图画成了很多个矩形。首先考虑一个矩形内部的答案，如果这个矩形 $n$ 行 $m$ 列，并且我们要从中选择 $k$ 个点，方案数量就是，从行选择 $k$ 个，从列选择 $k$ 个，然后再任意组合。考虑任意组合的过程，就是从行的 $k$ 个点分别对应到一个列，也就是排列的数量，所以就是 $k!$ ，于是 $n\times m$ 的矩形选择 $k$ 个点的方案就是：
$$
S(n,m,k) = {n\choose k} {m\choose k} k!
$$
然后考虑设 $dp[i][j]$ 表示 $i$ 这个（笛卡尔树的）节点中选择了 $j$ 个点的方案数量。

怎么转移？我们先抛开这个矩形本身，只考虑 $u$ 所有儿子，设初始状态为 $dp[u][0] = 1$，然后我们对于每一个儿子 $v$ ，考虑转移 （式子可能边界有点小问题建议以代码为准），注意树形 dp 要逆序枚举。。
$$
dp[u][i] = \sum_{j=1}^i dp[v][j]\times dp[u][i - j]
$$
对于所有儿子分别跑一次之后，当前的 $dp[u][i]$ 就是从 $u$ 的儿子中选择 $i$ 个点的方案数量，然后考虑怎么把这个位置的矩形也选择上，注意要减去已经通过儿子选择过的列，于是再做一次：
$$
dp[u][i] = \sum_{j=1}^i dp[u][j] S(x - (i - j),y,i-j)
$$
其中 $x,y$ 表示这个矩形的长宽。（这几个柿子看起来都好卷积啊。。但是 $n \leq 500$ 就随便做喽）

复杂度，如果笛卡尔树暴力枚举下一层暴力跑树形 dp 都才 $O(n^3)$ 。。那就暴力一点吧。。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "set"
#include "vector"
#include "map"
#include "cmath"
#define MAXN 506
//#define int long long
using namespace std;
typedef long long ll;
#define P 1000000007

int n , m;

int Pow( int x , int a ) {
    int ans = 1 , cur = x % P;
    while( a ) {
        if( a & 1 ) ans = 1ll * ans * cur % P;
        cur = 1ll * cur * cur % P , a >>= 1;
    }
    return ans;
}
int h[MAXN];
int J[1000006] , invJ[1000006];
int C( int a , int b ) {
    if( a < b ) return 0;
    return 1ll * J[a] * invJ[b] % P * invJ[a - b] % P;
}
int S( int n , int m , int k ) {
    return 1ll * C( n , k ) * C( m , k ) % P * J[k] % P;
}
int dp[506 * 506][506] , cur , k;
int solve( int l , int r , int base ) {
    if( l > r ) return 0;
    int re = 0 , c = ++ cur , L = r - l + 1;
    for( int i = l ; i <= r ; ++ i ) if( !re || h[i] < h[re] ) re = i;
    vector<int> mn;
    mn.push_back( l - 1 );
    for( int i = l ; i <= r ; ++ i ) if( h[i] == h[re] ) mn.push_back( i );
    mn.push_back( r + 1 );
    dp[c][0] = 1;
    for( int i = 1 ; i < mn.size() ; ++ i ) {
        int t = mn[i] , p = mn[i - 1] , l = t - p - 1 , id = solve( p + 1 , t - 1 , h[re] );
        if( id == 0 ) continue;
        for( int j = min( L , k ) ; j >= 0 ; -- j )
            for( int k = 1 ; k <= min( j , l ) ; ++ k )
                ( dp[c][j] += 1ll * dp[id][k] * dp[c][j - k] % P ) %= P;
    }
    int dh = h[re] - base;
    for( int i = min( L , k ) ; i >= 0 ; -- i )
        for( int j = 1 ; j <= min( dh , i ) ; ++ j )
            ( dp[c][i] += 1ll * dp[c][i - j] * S( dh , L - ( i - j ) , j ) % P ) %= P;
    return c;
}

int main() {
    J[0] = 1; invJ[0] = 1;
    for( int i = 1 ; i < 1000006 ; ++ i ) J[i] = 1ll * J[i - 1] * i % P , invJ[i] = Pow( J[i] , P - 2 );
    cin >> n >> k;
    for( int i = 1 ; i <= n ; ++ i ) scanf("%d",h + i);
    int c = solve( 1 , n , 0 );
    cout << dp[c][k] << endl;
}
```



---

## 作者：ywy_c_asm (赞：3)

首先在这里orz一下CQzhangyu神犇，这题是我在[他的博客](https://www.cnblogs.com/CQzhangyu/p/7787236.html)里学到的%%%stOOrz%%%。

这题看上去和用单调栈求的最大子矩形差不多，都是需要考虑一个局部极小值的影响，我们画个图：

![](https://cdn.luogu.com.cn/upload/pic/45714.png )

考虑区间$[1,5]$的方案，我们发现$h_3$为该区间内的最小值，不妨称他“掌控”这个区间，如果我们把这个问题拆成在$[1,2]$内与$[4,5]$内的方案的话，可以发现因为$h_3$的影响，那两个区间如果在$>h_3$的位置放是互不影响的，但是如果放到低于$h_3$的位置就会撞车了……

所以我们的大致思路就是，在处理每个区间的答案的时候，我们不能往上个区间的最小值之下放，然后每个点都对应着一个矩形区域，我们往这里去放。

额……上面那段话应该没人能听明白……所以我还是把这题的主角请出来吧：**笛卡尔树**。

笛卡尔树其实就是广义的$Treap$，每个点都是一个二元组$(a_i,b_i)$，对于$a_i$它有二叉查找树性质，对于$b_i$它有堆性质。

对于这题，我们令下标为$a$，$h$为$b$，构建出一棵笛卡尔树，显然一个子树就能对应一个区间，我们让它的根为这个区间的最小值，这样就很清晰了，根掌控这个子树。

这东西的建树非常有意思，其实就是一个单调栈，我们用一个栈维护已经构造好的笛卡尔树的从根不断走右儿子的一条链，然后当前要插入这个点，就在栈里找到第一个比他小的点，我们相当于要在这条链上“插入”这个点，为了满足二叉查找树性质就让后面的那个点变成他的左儿子，然后把后面的都弹掉，自己成为上面那个点的右儿子，入栈。注意如果栈里都比他大的话就把他变成根。这样建树显然是$O(n)$的，其实通过这个可以看出笛卡尔树其实就是单调栈换了种形态而已，而把单调栈变成树的形态会解决一些单调栈解决不了的问题比如这题。

好了，现在就把最上面两段~~我们都看不懂~~的话代入笛卡尔树里再来分析一下吧。

考虑一棵以$i$为根的子树，它的左右子树的放置方案中，如果不在$h_i$以下放，那么就是互相独立的。但是如果涉及到了$h_i$以下的放置，那么就会同时影响到$i$、$i$的左子树、$i$的右子树三个部分，那么我们不妨不让这两个子树往$h_i$以下放，$h_i$以下的部分要在$i$处考虑。

我们~~运用一下整体意识~~这样的话$h_{fa[i]}$以下的部分就得在$fa[i]$处考虑了，所以我们发现对每个点自身都要对应一个高度为$h_i-h_{fa[i]}$，宽度为$size_i$的矩形区域（可以发现这样建出来的笛卡尔树其实也能和单调栈一样求最大子矩形，利用的差不多就是这个原理）。

于是显然我们就可以在笛卡尔树上进行树形dp了，设$dp[i][j]$为$i$的子树这个区域选了$j$个的方案，我们先像树形背包一样合并两棵子树的dp，然后就到了这个点自身要处理的矩形区域。但是我们发现一个问题，这个矩形区域把整棵子树的下标都覆盖了，但是一个下标的格子只能放一个。别着急，我们慢慢分析。

我们想把两棵子树合并之后的$dp[i][j]$长成啥样子，既然已经选了$j$个，那么换句话说就是有$j$个下标或者说是$j$列已经不能选了，但是别忘了在这个子树里我们还有$size_i-j$列可以用，那么不妨就把这几列看做一个整体，就是把这个矩形区域的高不变，宽重设了一下，就是这样一个简单的图：

![](https://cdn.luogu.com.cn/upload/pic/45721.png )

这个技巧在组合计数中还是挺常用的，然后确定了这个矩形区域，那么在这个里面放$k$个的方案就是：

$k!C_{height}^kC_{width}^k$

这个还是挺好理解的吧……就是我们把横向的和纵向的拆开，先枚举横向放哪$k$列，再在纵向放哪$k$行，然后放的相当于一个排列（每行一个每列一个）就乘个$k!$就好了。

对于当前的每个$dp[i][j]$我们都像背包一样枚举在这个矩形区域放多少个，然后乘上方案数就能转移了。

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define p 1000000007
using namespace std;
namespace ywy{
	int h[501];
	ll dp[501][501];
	inline ll mi(int a,int b){
		ll ans=1,tmp=a;while(b){
			if(b&1)ans=(ans*tmp)%p;tmp=(tmp*tmp)%p;b>>=1;
		}return(ans);
	}
	int ch[501][2],fa[501],stk[502];
	ll jc[2000001],jcny[2000001];
	inline ll cnm(int n,int m){
		if(n<m)return(0);if(n<0)return(0);
		ll cjr=jc[n];cjr*=jcny[m];
		cjr%=p;cjr*=jcny[n-m];
		return(cjr%p);
	}
	int K;
	int size[501];
	void dfs(int tree){//树形dp 
		dp[tree][0]=1;
		if(!tree)return;
		size[tree]=1;
		dfs(ch[tree][0]);
		dfs(ch[tree][1]);
		int he=h[tree]-h[fa[tree]];
		for(register int i=0;i<=1;i++){//合并两棵子树的dp 
			if(!ch[tree][i])continue;
			size[tree]+=size[ch[tree][i]];
			for(register int j=min(K,size[tree]);j>=0;j--){
				for(register int k=1;k<=size[ch[tree][i]]&&k<=j;k++){
					if(!dp[ch[tree][i]][k])continue;
					if(!dp[tree][j-k])continue;
					dp[tree][j]=(dp[tree][j]+dp[ch[tree][i]][k]*dp[tree][j-k])%p;
				}
			}
		}
		for(register int i=min(K,size[tree]);i>=0;i--){//再套上矩形区域进行自我转移 
			if(!dp[tree][i])continue;
			for(register int j=1;j<=min(min(K,size[tree])-i,he);j++){
				ll fan=jc[j];
				fan*=cnm(he,j);fan%=p;
				fan*=cnm(size[tree]-i,j);fan%=p;
				fan*=dp[tree][i];fan%=p;
				dp[tree][i+j]=(dp[tree][i+j]+fan)%p;
			}
		}
	}
	void ywymain(){
		jc[0]=1;
		for(register int i=1;i<=2000000;i++)jc[i]=(jc[i-1]*i)%p;
		jcny[2000000]=mi(jc[2000000],p-2);
		for(register int i=2000000-1;i>=0;i--)jcny[i]=(jcny[i+1]*(i+1))%p;
		int n;cin>>n>>K;
		for(register int i=1;i<=n;i++)cin>>h[i];
		int root=1;
		int sp=0;stk[sp]=1;sp++;
		for(register int i=2;i<=n;i++){//笛卡尔树建树 
			while(sp&&h[stk[sp-1]]>=h[i])sp--;
			if(!sp)fa[root]=i,ch[i][0]=root,root=i;
			else{
				int cjr=stk[sp-1];
				fa[ch[cjr][1]]=i;
				ch[i][0]=ch[cjr][1];
				fa[i]=cjr;
				ch[cjr][1]=i;                             
			}
			stk[sp]=i;sp++;
		}
		dfs(root);
		cout<<dp[root][K]<<endl;
	}
}
int main(){
	ywy::ywymain();return(0);//再见程序 
}
```

---

## 作者：OIerAlbedo (赞：2)

# Preface

神题！（为什么要用什么笛卡尔树呢，暴力不好吗？）

# Description

给你 $ N $ 列的表格，每一列长度为 $ H_i $ ，要你在其中填入 $ K $ 个数，满足 $ K $ 个数不在同一列，同一行，但是注意，如果两个数虽然在同一行，但是中间有断开的表格，就不算在同一行，问你表格有多少种填法。

# Solution

这道题有两个部分分，但是我到现在都没明白是给哪个算法分的。。。。

话不多说，步入正题。

首先我们先从最简单的开始，如果是一个矩形，答案是什么呢？

### Conclusion

令矩形长为 $ n $，宽为 $ m $​，并且有 $ K $ 个点，那么答案为：
$$
C_{n}^{K}\times C_{m}^{K} \times K!
$$

### Prove

在 $ N $ 个点中选出 $ K $ 个纵坐标，在 $ M $ 个点中选出 $ K $ 个横坐标，然后 $ K $ 个横坐标可以有 $ K! $ 种排列与 $ K $ 个纵坐标一一对应，得证。

之后我们可以发现原图形其实是由多个矩形所组成的，如下图。

[![WJoRtU.png](https://z3.ax1x.com/2021/07/19/WJoRtU.png)](https://imgtu.com/i/WJoRtU)

这样子我们就可以用DP的方法，一个一个矩形的合并上去，但是要实现这个算法我们还有三步要走

### 如何实现图中的划分

题解里很多都是说什么笛卡尔数，但完全不用呀，运用搜索的方法，每次找到所求区间的最小值，然后所有的高度都减去这个最小值，原本连在一起的图形就会分成几个部分，在对这几个部分在进行这样的操作，知道所求区间的高度都相同，就好了。

### 如何建立矩形间的关系

我们可以通过建图的方式，因为我们可以发现，图中的 $ 5 $​ 矩形所在的区间是包含其他矩形的，像是 $ 2 $ 是包含 $ 1 $ 区间的，即 $ 1 $ ,$ 2 $ ,$ 3 $ ,$ 4 $ 可以先求出来然后统统与 $ 5 $ 合并，至于怎么连边，在划分的过程中，一段完整的区间分割成若干小区间后，将完整区间与分割成的小区间连边即可。

### 如何DP

我们即 $ f_{x,y} $ 为 $ x $ 所在区间所包含的矩形中有 $ y $ 个点的方案数，那么可以得到下面两个方程。
$$
f[x][y]=\sum_{i=1}^{y} f[x][y-i]\times f[son_x][i]
$$

$$
f[x][y]=\sum_{i=1}^{y} f[x][i]\times C_{Height_x}^{y-i} \times C_{Width_x-i}^{y-i}
$$

其中上面一个方程就是把除他以外的所有矩形合并，下面一个方程就是把其他矩形与自己合并，不过有个注意点，因为其他矩形都是包含在 $ x $ 的区间内的，所以他们所选的列，$ x $​ 矩形不能再选，这就是宽度要减去 $ i $ 的原因。

# Code

```c++
#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
  long long x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
long long pow(long long x,long long y,long long p)
{
	long long ans=1;
	for (;y;y>>=1,x=x*x % p)
		if (y&1) ans=ans*x % p;
	return ans;
}
long long gcd(long long x,long long y)
{
	if (y==0) return x;
	long long ans=gcd(y,x % y);return ans;
}
struct hxz{
	long long height,width;
} E[101000];
int cnt;
long long mn,root,i,n,K,MOD,f[1010][1010],H[100100],a[101000],b[101000],d[101000],fac[1010000],ifac[1010000];
long long C(long long x,long long y)
{
	if (y>x) return 0;
	return fac[x]*ifac[x-y] % MOD*ifac[y] % MOD;
}
void add(int x,int y)
{
	cnt++;a[cnt]=y;b[cnt]=d[x];d[x]=cnt;
}
void sc(int x,int lft,int rit,int val)
{
	int i;
	for (i=lft;i<=rit;i++) H[i]=H[i]-val;
	int L,R;
	for (L=lft;L<=rit;L++)
	    if (H[L]!=0)
	       {
	       	 int mn=1000000000,now=0,l=0;
	       	 for (R=L;R<=rit;R++)
	       	      {
	       	      	if (H[R]==0) break;l=R;
	       	      	if (H[R]<mn)
	       	      	   {
	       	      	   	mn=H[R];now=R;
						}
					 }
			R--;
			add(x,now);E[now].height=mn;E[now].width=R-L+1;sc(now,L,R,mn);
			L=l;
		   }
}
void Make(int x)
{
	int i,j,lst;
	f[x][0]=1;
	for (i=d[x];i;i=b[i])
	       {
	       	  Make(a[i]);
	       	  for (j=min(E[x].width,K);j>=1;j--)
	       	     {
				long long now=0;
	       	     for (lst=min((long long)j,E[a[i]].width);lst>=1;lst--)
	       	         f[x][j]=(f[x][j]+f[x][j-lst]*f[a[i]][lst]) % MOD;
//	       	    f[x][j]=now;
	       	    } 
		   }
	for (i=min(E[x].width,K);i>=1;i--)
	      {
	      	long long now=0;
	      	for (j=i;j>=0;j--)
	      	    now=(now+f[x][j]*C(E[x].height,i-j) % MOD*C(E[x].width-j,i-j) % MOD*fac[i-j] % MOD) % MOD;
	      	f[x][i]=now;
		  }
}
int main()
{
	//ios::sync_with_stdio(0);cin.tie();cout.tie();
	n=read();K=read();MOD=1000000007;
	for (i=1;i<=n;i++) H[i]=read();
	fac[0]=1;
	for (i=1;i<=1000000;i++) fac[i]=fac[i-1]*i % MOD;
	ifac[1000000]=pow(fac[1000000],MOD-2,MOD);
	for (i=1000000-1;i>=0;i--) ifac[i]=ifac[i+1]*(i+1) % MOD; 
    root=0;mn=1000000000;
    for (i=1;i<=n;i++)
        if (H[i]<mn)
           {
           	mn=H[i];root=i;
		   }
	E[root].height=H[root];E[root].width=n;
	sc(root,1,n,H[root]);
	Make(root);
	printf("%lld\n",f[root][K]);
	return 0;
}

```



---

## 作者：lytqwq (赞：2)

~~好妙啊~~

首先建立出高度的小根笛卡尔树，发现这样构成的若干个矩形正好对应小根笛卡尔树上的所有节点（可以看前面题解的那张图）

你会发现，对于一个父节点，它的儿子节点只会影响一些列不能选，而且因为选的地方中间断开是合法的，我们只需要让这一个节点只选**该节点代表的矩阵的高度以内 列**，并且和儿子和节点内部没有列的冲突就完了。

当前矩阵的长度： $size_i$ 

当前矩阵的高度： $h_i-h_{fa}$ 

当 $i$ 节点的儿子选了 $x$ 个时

留给当前节点就是 $size_i-x$ 列可选

在 $size_i-x$ 列可选，矩阵的高度为 $h_i-h_{fa}$ 时，选 $y$ 个的选法有：

$$ \large C_{size_i-x}^{y} \times C_{h_i-h_{fa}}^{y} \times y! $$

设 $f_{i,j}$ 代表在节点 $i$ 的子树中选 $j$ 个的方案数

$$\large f_{i,j}=\sum_{l+r\le j}{f_{ls_i,l}\times f_{rs_i,r}\times ( C_{size_i-(l+r)}^{(j-l-r)} \times C_{h_i-h_{fa}}^{(j-l-r)} \times (j-l-r)! ) } $$

直接这样做是 $O(nk^3)$

发现后面一段只和 $i+j$ 有关，我们把它拿出来


$$\large f_{i,j}=\sum_{o}( C_{size_i-o}^{(j-o)} \times C_{h_i-h_{fa}}^{(j-o)} \times (j-o)! )\times \sum_{l+r=o}{f_{ls_i,l}\times f_{rs_i,r} } $$

后面的我们可以 $O(n^2)$ 预处理一下

这就是 $O(nk^2)$ 了

然后就完了/cy

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long int N=511,p=1e9+7;
long long int n,k;
long long int a[N];
long long int Stack[N],top;
long long int ls[N],rs[N],size[N];
long long int f[N][N],g[N][N];
long long int inv[(int)1e6+10],mul1[(int)1e6+10],mul2[(int)1e6+10];
long long int C(long long int x,long long int y){return y>x?0:mul1[x]*mul2[y]%p*mul2[x-y]%p;}
void dfs(long long int u,long long int fa){
	if(ls[u])dfs(ls[u],u);
	if(rs[u])dfs(rs[u],u);
	size[u]=size[ls[u]]+size[rs[u]]+1;
	for(long long int i=0;i<=size[ls[u]];i++){
		for(long long int o=0;o<=size[rs[u]];o++){
			g[u][i+o]+=f[ls[u]][i]*f[rs[u]][o]%p;
			g[u][i+o]%=p;
		}
	}
	for(long long int i=0;i<=size[u];i++){
		for(long long int o=0;o<=i;o++){
			f[u][i]+=g[u][o]*(C(size[u]-o,i-o)*C(a[u]-a[fa],i-o)%p*mul1[i-o]%p)%p;
			f[u][i]%=p;
		}
	}
}
int main(){
	scanf("%lld%lld",&n,&k);
	inv[0]=mul1[0]=mul2[0]=inv[1]=mul1[1]=mul2[1]=1;
	for(long long int i=2;i<=1e6;i++){
		inv[i]=inv[p%i]*(p-p/i)%p;
		mul1[i]=mul1[i-1]*i%p;
		mul2[i]=mul2[i-1]*inv[i]%p;
	}
	for(long long int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		long long int k=top;
		while(k>0&&a[Stack[k]]>a[i])k--;
		if(k)rs[Stack[k]]=i;
		if(k<top)ls[i]=Stack[k+1];
		Stack[++k]=i;
		top=k;
	}
	f[0][0]=1;
	dfs(Stack[1],0);
	printf("%lld\n",f[Stack[1]][k]);
}
```




















































---

## 作者：dsjkafdsaf (赞：1)

# [My_blog](https://www.cnblogs.com/dsjkafdsaf/)
[更好的阅读体验](https://www.cnblogs.com/dsjkafdsaf/p/11486566.html)

## 题目描述

即给出$n$个$1*h_i$的矩阵，在一条直线上对齐下表面，求放置$k$个互不攻击的车的方案数。

答案有可能很大，所以输出答案对$1000000007$取模。

## Input

第$1$行包括两个正整数$N，K$，表示了棋盘的列数和放的车数。
第$2$行包含$N$个正整数，表示了棋盘每列的高度。

对于$100\%$的数据，有 $N≤500，K≤500，h[i] ≤1000000$。

## Output

包括一个非负整数，表示有多少种放置的方案.

## Sample Input

```
5 2 
2 3 1 2 4 
```
## Sample Output
```
43
```

题意：即给出$n$个$1*h_i$的矩阵，在一条直线上对齐下表面，求放置$k$个互不攻击的车的方案数。

显然是先建出小根笛卡尔树，考虑每个矩形内部的答案。

不会笛卡尔树请转到[笛卡尔树学习笔记](https://www.cnblogs.com/dsjkafdsaf/p/11486579.html)

设 $dp[u][i]$ 表示 $u$ 子树内放 $i$ 个数的方案数， $dp1[i]$ 表示 当前子树$u$内不考虑当前矩形，放 $i$ 个数的方案数，设$H[i]$为当前矩阵可行高度（即$A[u]-A[fa[u]]$）。

显然有 $dp1[] = f[ls]*f[rs]$，即左右子树的卷积。

接下来就是背包的转移了，枚举当前矩形内有多少列还是空的进行转移。

设当前子树放置$i$个棋子，有$j$个在当前矩阵放置。

则$dp[u][i]+=\sum_{j=0}^idp1[i-j]*C(Sz[u]-(i-j),j)*C(H[x],j)*j!$

第一个组合数是枚举矩阵所剩的行，第二个组合数是枚举矩阵所剩的列。

**最后乘上 j! 是因为横纵坐标是两两组合的，因此匹配的方案数为 j!。**

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
#define reg register
#define Raed Read
#define clr(a,b) memset(a,b,sizeof a)
#define Mod(x) (x>=mod)&&(x-=mod)
#define debug(x) cerr<<#x<<"="<<x<<endl;
#define debug2(x,y) cerr<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl;
#define debug3(x,y,z) cerr<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl;
#define rep(a,b,c) for(reg int a=(b),a##_end_=(c); a<=a##_end_; ++a)
#define ret(a,b,c) for(reg int a=(b),a##_end_=(c); a<a##_end_; ++a)
#define drep(a,b,c) for(reg int a=(b),a##_end_=(c); a>=a##_end_; --a)
#define erep(i,G,x) for(int i=(G).Head[x]; i; i=(G).Nxt[i])
 
inline int Read(void) {
    int res=0,f=1;
    char c;
    while(c=getchar(),c<48||c>57)if(c=='-')f=0;
    do res=(res<<3)+(res<<1)+(c^48);
    while(c=getchar(),c>=48&&c<=57);
    return f?res:-res;
}
 
template<class T>inline bool Min(T &a, T const&b) {
    return a>b?a=b,1:0;
}
template<class T>inline bool Max(T &a, T const&b) {
    return a<b?a=b,1:0;
}
const int N=505,M=1e6+5,mod=1e9+7;
 
bool MOP1;
 
int Ans,n,K,stk[N],A[N],son[N][2];
 
int Fac[M],Inv[M],V[M];
 
int C(int a,int b) {
    if(a<b)return 0;
    return Fac[a]*(Inv[a-b]*Inv[b]%mod)%mod;
}
 
int Sz[N],dp1[N],dp[N][N],H[N];
void dfs(int x) {
    Sz[x]=dp[x][0]=1;
    rep(i,0,1)if(son[x][i]) {
        int y=son[x][i];
        dfs(y);
        clr(dp1,0);
        rep(j,0,min(Sz[y],K))rep(k,0,min(Sz[x],K))if(j+k<=K) {
            dp1[j+k]+=dp[x][k]*dp[y][j]%mod,Mod(dp1[j+k]);
        }
        Sz[x]+=Sz[y];
        rep(j,0,min(Sz[x],K))dp[x][j]=dp1[j];
    }
    rep(j,0,min(Sz[x],K))dp1[j]=dp[x][j];
    rep(i,0,min(Sz[x],K)) {
        int temp=0;
        rep(j,0,i) {
            temp+=dp1[i-j]*Fac[j]%mod*C(Sz[x]-(i-j),j)%mod*C(H[x],j)%mod;
            Mod(temp);
        }
        dp[x][i]=temp;
    }
 
}
 
bool MOP2;
 
void _main(void) {
    Fac[0]=Inv[0]=Fac[1]=V[1]=Inv[1]=1;
    ret(i,2,M) {
        Fac[i]=Fac[i-1]*i%mod;
        V[i]=(mod-mod/i)*V[mod%i]%mod;
        Inv[i]=Inv[i-1]*V[i]%mod;
    }
    n=Read(),K=Read();
    rep(i,1,n)A[i]=Read(),son[i][0]=son[i][1]=0;
    int top=0;
    rep(i,1,n) {
        while(top&&A[stk[top]]>A[i])son[i][0]=stk[top--];
        if(top)son[stk[top]][1]=i;
        stk[++top]=i;
    }
    rep(i,0,1)rep(j,1,n)if(son[j][i])H[son[j][i]]=A[son[j][i]]-A[j];
    H[stk[1]]=A[stk[1]];
    dfs(stk[1]);
    printf("%d\n",dp[stk[1]][K]);
}
 
signed main() {
    _main();
    return 0;
}
```

---

## 作者：hegm (赞：0)

### [PERIODNI - Periodni](https://www.luogu.com.cn/problem/SP3734)

计数 dp。

先看前 $40\%$ 的数据，发现可以顺序枚举并且状态压缩。

考虑如何优化这一步，联想到最大子矩形，所以考虑建立出笛卡尔树。（利用性质 $i$ 号节点的子树一定是一个连通块，并且这个连通块的最小高度就是 $i$ 的高度）

按照高度最小的为根，建立笛卡尔树。

现在来考虑如何设计状态，显然，$dp$ 数组要记录一维是位置，那么另一维度就要是 $k$ 了，表示当前选了几个点。

但是这还不够，需要再此基础上添加一些状态方便合并。

现在 $dp_{i,j}$ 表示考虑 $i$ 号节点和他的子树中的连续段，选择 $j$ 个节点的方案数。

这种状态不好向父亲合并，因为父亲的左右孩子可能会重叠，在 $1\sim val_i$ 的区间里面重复。

那么不妨重新定义 dp 数组：

$dp_{i,j}$ 表示考虑 $i$ 极其子树中，选择 $j$ 个点，并且选择区间在 $val_{fa_i}\sim \infty$。

这样一来，合并就不麻烦了，因为左右子树的节点的方案不可能冲突。

但是这样的话，合并到 $i$ 号节点的方案数就不包含 $1\sim val_i$ 选择了，所以我们要添加一些东西。

先列出一个比较暴力的式子。

$dp_{i,j}=\sum\limits_{a,b,c}dp_{ls,a}\times dp_{rs,b}\times \text{C}_{siz_i-a-b}^k\times\text{A}_{val_i}^k$

$a$ 指的是 $ls$ 中选择 $a$ 个填数（$a\le siz_{ls}$），$b$ 与之同理。

$c$ 表示在选择完毕之后，再次选择 $c$ 个数字，填在 $1\sim val_i$ 的范围内。

那么 $j=a+b+c$。

复杂度是很奇怪的。

当然可以使用树上背包复杂度来证明，复杂度是 $O(n^3)$ 的。


### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define N 1005
#define mod 1000000007
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,k,ls[N],rs[N],last,a[N],fa[N],rt,dp[N][N],siz[N],C[N][N];
stack<int> t;
int j[1000005],p[1000005];
int add(int a,int b){return (1ll*a+b)%mod;}
int mul(int a,int b){return (1ll*a*b)%mod;}
int ksm(int d,int z)
{
	int ans=1;
	while(z)
	{
		if(z&1)ans=mul(ans,d);
		d=mul(d,d);
		z>>=1;
	}
	return ans;
}
int A(int x,int y)
{
	if(y>x)return 0;
	return mul(j[x],p[x-y]);
}
void dfs(int now)
{
	siz[now]=1;
	if(!ls[now]&&!rs[now])
	{
		dp[now][0]=1;
		dp[now][1]=a[now]-a[fa[now]];
		return ;
	}
	if(ls[now])dfs(ls[now]),siz[now]+=siz[ls[now]];
	if(rs[now])dfs(rs[now]),siz[now]+=siz[rs[now]];
	dp[now][0]=1;
	if(!ls[now]||!rs[now])
	{
		int to=ls[now]+rs[now];
		for(int i=1;i<=siz[now];i++)
		for(int j=0,con=min(i,siz[now]);j<=con;j++)
		{
			dp[now][i]=add(dp[now][i],mul(dp[to][j],mul(C[siz[now]-j][i-j],A(a[now]-a[fa[now]],i-j))));
		}
	}
	else
	{
		for(int i=1;i<=siz[now];i++)
		for(int j=0,con=min(i,siz[ls[now]]);j<=con;j++)
		for(int k=0,con=min(i-j,siz[rs[now]]);k<=con;k++)
		dp[now][i]=add(dp[now][i],mul(dp[ls[now]][j],mul(dp[rs[now]][k],mul(C[siz[now]-j-k][i-j-k],A(a[now]-a[fa[now]],i-j-k)))));
	}
}
int main()
{
	n=read();k=read();
	C[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
		C[i][j]=add(C[i-1][j-1],C[i-1][j]);
	}
	j[0]=1;p[0]=1;
	for(int i=1;i<=1000000;i++)j[i]=mul(j[i-1],i);
	for(int i=1;i<=1000000;i++)p[i]=ksm(j[i],mod-2);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)
	{
		last=0;
		while(t.size()&&a[t.top()]>a[i])last=t.top(),t.pop();
		ls[i]=last;
		if(last)fa[last]=i;
		if(t.empty())
		{
			t.push(i);
			continue;
		}
		rs[t.top()]=i;
		fa[i]=t.top();
		t.push(i);
	}
	while(t.size()!=1)t.pop();
	rt=t.top();
	dfs(rt);
	cout<<dp[rt][k]<<"\n";
	return 0;
}

```

---

## 作者：Prean (赞：0)

题意：

有 $ n $ 列表格，第 $ i $ 列有 $ a_i $ 个格子，问在 $ n $ 列表格中有多少种放置 $ k $ 个棋子的方法使没有棋子在同一列和同一行。（如果中间有一个“格子”是空的，那么不算在同一行）

思路很妙。

如果所有 $ a_i $ 都相等（一个矩形），答案明显是 $ \binom {a_i} k \times \binom n k \times k! $。

我们发现这个问题棘手的地方在于不能在同一行，所以考虑将答案分为两部分：

1. 去掉最下面的矩形后，剩下两块不规则图形的答案
2. 最下面的矩形

然后我们发现不会做。。。

> 你不会做的题很可能是DP。

考虑 DP，设 $ dp[u][k] $表示以 $ u $ 为分治中心时，放置 $ k $ 个棋子的方案数。

对于两块不规则图形的答案，合并这一部分的答案类似一个背包 DP。

最下面的矩形明显可以直接计算其答案。

于是我们就做完了。。。

对于找最小值，我们发现只需要对序列建笛卡尔树就能很方便地找到最小值。ST表也可以，只不过是 $ O(n\log n) $ 的。

复杂度为 $ O(n^2k) $
```cpp
#include<cstdio>
typedef long long ll;
const int M=505,mod=1e9+7;
int n,k,a[M],L[M],R[M],siz[M],dp[M][M];
int fac[1000005],ifac[1000005];
int top,stk[M];
inline int Add(const int&a,const int&b){
	return a+b>=mod?a+b-mod:a+b;
}
inline void init(const int&M){
	register int i;fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(i=2;i<=M;++i){
		fac[i]=1ll*fac[i-1]*i%mod;
		ifac[i]=1ll*(mod-mod/i)*ifac[mod%i]%mod;
	}
	for(i=2;i<=M;++i)ifac[i]=1ll*ifac[i]*ifac[i-1]%mod;
}
inline int C(const int&n,const int&m){
	return m>n?0:1ll*ifac[m]*ifac[n-m]%mod*fac[n]%mod;
}
void DFS(int u,int f){
	if(!u)return;
	register int i,j,tmp;
	DFS(L[u],u);DFS(R[u],u);siz[u]=siz[L[u]]+siz[R[u]]+1;
	for(i=0;i<=siz[L[u]];++i){
		for(j=0;j<=siz[R[u]];++j){
			dp[u][i+j]=Add(dp[u][i+j],1ll*dp[L[u]][i]*dp[R[u]][j]%mod);
		}
	}
	for(i=siz[u];i>=0;--i){
		tmp=0;
		for(j=0;j<=i;++j){
			tmp=Add(tmp,1ll*dp[u][j]*fac[i-j]%mod*C(a[u]-a[f],i-j)%mod*C(siz[u]-j,i-j)%mod);
		}
		dp[u][i]=tmp;
	}
}
signed main(){
	register int i;
	scanf("%d%d",&n,&k);dp[0][0]=1;init(1e6);
	for(i=1;i<=n;++i)scanf("%d",a+i);
	for(i=1;i<=n;++i){
		if(top&&a[i]<=a[stk[top]]){
			while(top&&a[i]<=a[stk[top]])R[stk[top-1]]=stk[top],--top;
			L[i]=stk[top+1];
		}
		stk[++top]=i;
	}
	while(top)R[stk[top-1]]=stk[top],--top;
	DFS(stk[1],0);
	printf("%d",dp[stk[1]][k]);
}
```

---

