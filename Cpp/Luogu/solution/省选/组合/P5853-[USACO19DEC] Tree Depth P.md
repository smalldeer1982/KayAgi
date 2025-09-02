# [USACO19DEC] Tree Depth P

## 题目背景

For the new year, Farmer John decided to give his cows a festive binary search tree
(BST)! 

To generate the BST, FJ starts with a permutation $a=\{a_1,a_2,\ldots,a_N\}$
of the integers $1\ldots N$, where $N\le 300$.  He then runs the following
pseudocode with arguments $1$ and $N.$

```
generate(l,r):
  if l > r, return empty subtree;
  x = argmin_{l <= i <= r} a_i; // index of min a_i in {a_l,...,a_r}
  return a BST with x as the root, 
    generate(l,x-1) as the left subtree,
    generate(x+1,r) as the right subtree;
```
For example, the permutation $\{3,2,5,1,4\}$ generates the following BST:

```
    4
   / \
  2   5
 / \ 
1   3
```
Let $d_i(a)$ denote the depth of node $i$ in the tree corresponding to $a,$ 
meaning the number of nodes on the path from $a_i$ to the root. In the above
example, $d_4(a)=1, d_2(a)=d_5(a)=2,$ and $d_1(a)=d_3(a)=3.$

The number of inversions of $a$ is equal to the number of pairs of integers
$(i,j)$ such that $1\le i<j\le N$ and $a_i>a_j.$ The cows know that the $a$ that
FJ will use to generate the BST has exactly $K$ inversions
$(0\le K\le \frac{N(N-1)}{2})$.  Over all $a$ satisfying this condition, compute
the remainder when $\sum_ad_i(a)$ is divided by $M$ for each $1\le i\le N.$

## 题目描述

为了迎接新年，Farmer John 决定给他的奶牛们一个节日二叉搜索树！

为了生成这个二叉搜索树，Farmer John 从一个 $1 \dots N$ 的排列 $a= \{1,2, \dots ,N\}$ 开始，然后以参数 $l$ 和 $r$ 开始运行如下的伪代码：
```
generate(l,r):
  if l > r, return empty subtree;
  x = argmin_{l <= i <= r} a_i; // index of min a_i in {a_l,...,a_r}
  return a BST with x as the root, 
    generate(l,x-1) as the left subtree,
    generate(x+1,r) as the right subtree;
```
例如，排列 $\{ 3,2,5,1,4 \}$ 将产生如下的二叉搜索树：

![](https://cdn.luogu.com.cn/upload/image_hosting/gw6ursc0.png)

令 $d_i(a)$ 表示节点 $i$ 在用排列 $a$ 生成的二叉搜索树中的深度。深度定义为这个节点到根节点的路径上的点数。在上述例子中，$d_4(a)=1,d_2(a)=d_5(a)=2,d_1(a)=d_3(a)=3$。

$a$ 中的逆序对数等于满足 $1 \le i<j \le N$ 且 $a_i>a_j$ 的数对 $(i,j)$ 的个数。奶牛们知道 Farmer John 用来生成二叉搜索树的排列 $a$ 中恰好有 $K$ 个逆序对。对于所有满足条件的 $a$，请计算对于每个 $1 \le i \le N$，$\sum_a d_i(a)$ 对 $M$ 取模后的结果。

## 说明/提示

#### 样例解释 1

对于这个样例，唯一满足条件的排列为 $a=\{1,2,3\}$。

#### 样例解释 2

对于这个样例，满足条件的两个排列分别为 $a=\{1,3,2\}$ 和 $a=\{2,1,3\}$。

#### 数据范围

对于全部数据，$1\le N\le 300$，$0\le K\le \frac{N(N-1)}{2}$，保证 $M$ 是一个 $\left[ 10^8,10^9+9 \right]$ 范围中的质数。

对于测试点 $3,4$，满足 $N \le 8$；

对于测试点 $5-7$，满足 $N \le 20$；

对于测试点 $8-10$，满足 $N \le 50$。

USACO 2019 December 铂金组T3

## 样例 #1

### 输入

```
3 0 192603497
```

### 输出

```
1 2 3
```

## 样例 #2

### 输入

```
3 1 144408983
```

### 输出

```
3 4 4
```

# 题解

## 作者：7KByte (赞：24)

更好的体验尽在[**我的博客**](https://www.cnblogs.com/7KByte/p/15883285.html)。

不用生成函数，目前比 rank2 快四倍。

首先这是一道不简单的数数思维题。

我们要统计对于所有排列的深度之和，直接做非常不方便。而数数题一般将条件化简，或找到等价的容易处理的条件。

这里求深度，等价于枚举一个点的祖先，它的祖先个数 $+1$ 就是它的深度。这样问题转化为求数对 $(u,v)$ 的贡献，即有多少排列使得 $v$ 是 $u$ 的祖先。

如果 $v$ 是 $u$ 的祖先，等价于 $a_v < a_u$，且 $u,v$ 之间没有小于 $a_v$ 的数。

如果不考虑其它限制条件，先求有多少个排列恰好有 $K$ 个逆序对。这是一个经典题目，直接定义状态 $f_{i,j}$ 表示长度为 $i$ 的逆序对数为 $j$ 的排列个数。枚举最后一位的 $i$ 种选择，分别是逆序对增加 $x\in[0,i - 1]$ 个，典型的背包模型，可以前缀和优化至 $\mathcal{O}(N^3)$。

现在有 $(u,v)$ 的限制条件，我们可以先固定 $u,v$ 之间的数，再固定 $u,v$，最后固定外面的数。不难发现除了位置 $v$，其余的数可以随便填，和上面的转移一模一样。对于位置 $v$，如果在 $u$ 后面，一定会产生 $v-u$ 个逆序对，否则一定不产生逆序对。

所以我们先跑 DP 求出 $f$。然后枚举 $v-u$，然后在背包中撤销 $(v-u)$，撤销后的 $f_{n - 1,K-\max(0,v-u)}$ 就是我们要求的贡献。

时间复杂度 $\mathcal{O}(N^3)$，代码没有一次乘法和取模，跑的飞快。

```cpp
#define M 46600
#define N 305
int n, k, f[2][M], s[M], g[M], sz, ans[N];
#define ck(x) (x >= P ? x - P : x)
void undo(int x){
	memset(g, 0, sizeof(g));
	int cur = P - 1; g[0] = 1;
	rp(i, sz - x){
		if(i > x)ad(cur, g[i - x - 1]);
		su(cur, g[i] = ck(f[n & 1][i] + cur));
	}
}
int main() {
	read(n, k, P);
	f[0][0] = 1;
	rp(i, n){
		s[0] = f[i & 1][0] = 1, sz += i - 1;
		rp(j, sz){
			f[i & 1][j] = s[j] = ck(s[j - 1] + f[1 & (i - 1)][j]);
			if(j >= i)su(f[i & 1][j], s[j - i]);
		}
	}
	rp(i, n)ans[i] = f[n & 1][k];
	rp(t, n - 1){
		undo(t);
		rp(i, n - t){
			if(t <= k)ad(ans[i], g[k - t]);
			ad(ans[i + t], g[k]);
		}
	}
	rp(i, n)printf("%d ", ans[i]); el;
	return 0;
}

```

---

## 作者：Karry5307 (赞：9)

### 题意

给定 $n,k$，对于 $1\leq i\leq n$ 求

$$\sum\limits_{\pi}\text{depth}(\pi,i)$$

其中 $\pi$ 是长度为 $n$ 且逆序对数为 $k$ 的排列，$\text{depth}(\pi,i)$ 为排列 $\pi$ 构建出的笛卡尔树上 $i$ 的深度。

数据范围：$n\leq 300$。

### 题解

先考虑如何用一些比较能够求和的方法去计算树上某个点的深度，注意到有这么一个非常明显的式子：

$$\text{depth}(u)=\sum\limits_{v}[\text{lca}(u,v)=v]$$

也即枚举有多少个祖先，这个时候注意到这个式子与树的形态无关，所以可以方便算出大量树上某个点的深度之和。

于是现在需要考虑的问题就是如何计算有多少个排列满足 $u$ 是 $v$ 的祖先。

然后考虑如何构造一个排列，每次钦定一个位置并且将大于等于自己的数加一，这样得到 $n$ 个排列有 $k$ 个逆序对的 OGF：

$$F_n(x)=\prod\limits_{i=1}^{n-1}\sum\limits_{j=0}^{i}x^j$$

考虑将两者结合起来。注意到一个点 $v$ 是点 $u$ 的祖先当且仅当 $\pi_v$ 是 $[\min(u,v),\max(u,v)]$ 这段区间的最小值，于是我们考虑换一种方法钦定位置：

首先从 $u$ 开始向着 $v$ 的方向逐一确定一直到整个序列的一段，再从 $u$ 开始向着 $v$ 的反方向逐一确定。

这个时候依次每个位置可能的贡献为 $[0,0],[0,1],\cdots,[0,n-1]$，但是除了 $v$ 这个位置，他要保证是 $[\min(u,v),\max(u,v)]$ 中最小的，所以这个位置的贡献当 $u<v$ 时为 $0$，否则为 $v-u$。

因为这里只与 $u,v$ 的差值有关系，所以可以直接枚举差值然后将 GF 除掉，这个时候得到了不考虑 $u,v$ 两个位置的 GF，接下来根据 $u,v$ 的大小关系决定是乘上 $x^0$ 还是 $x^{v-u}$ 即可。

但是注意到 $u=v$ 时也有一个贡献，加起来就好了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n,kk,MOD,fd;
ll f[MAXN],res[MAXN];
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
inline void mul(ll d)
{
	static ll g[MAXN];
	for(register int i=fd;i<fd+d;i++)
	{
		f[i]=0;
	}
	fd+=d;
	for(register int i=0;i<fd;i++)
	{
		g[i]=(g[i-1]+f[i])%MOD;
	}
	for(register int i=0;i<fd;i++)
	{
		f[i]=(g[i]-(i<=d?0:g[i-d-1])+MOD)%MOD;
	} 
}
inline void div(ll d)
{
	static ll g[MAXN];
	for(register int i=0;i<fd;i++)
	{
		g[i]=(f[i]+(i<=d?0:g[i-d-1]))%MOD;
	}	
	for(register int i=0;i<fd;i++)
	{
		f[i]=(g[i]-(i?g[i-1]:0)+MOD)%MOD;
	}
	fd-=d;
}
int main()
{
	n=read(),kk=read(),MOD=read(),fd=f[0]=1;
	for(register int i=1;i<n;i++)
	{
		mul(i);
	}
	for(register int i=1;i<n;i++)
	{
		div(i);
		for(register int j=i+1;j<=n;j++)
		{
			res[j]=(res[j]+f[kk])%MOD;
		}
		if(kk>=i)
		{
			for(register int j=1;j<=n-i;j++)
			{
				res[j]=(res[j]+f[kk-i])%MOD;
			}
		}
		mul(i);
	}
	for(register int i=1;i<=n;i++)
	{
		printf("%d ",(res[i]+f[kk])%MOD);
	}
}
```

---

## 作者：Missa (赞：5)

写一点对 <https://www.luogu.com.cn/blog/_post/412202> 的补充。

这篇文章解释不了为什么要想到去这样想，因此只能对它的正确性做补充说明。

快进到，我们维护一个分组背包，第 $i$ 组物品是 $0 \sim i-1$ 中的所有整数，则若 $v > u$，$v$ 对 $u$ 产生的贡献，恰好是钦定分组背包 $v-u$ 一组选 $v-u$ 的方案数；否则，恰好是钦定分组背包中 $v-u$ 这一组选 $0$ 的方案数。

考虑这样一件事：当 $i-1$ 个数已经排好时，插入一个新的数字到末尾，根据这个新的数字与原来的数字的相对大小顺序，可以新增 $0 \sim i-1$ 个逆序对，同时这个结论对插入到最前面也是成立的，对插入到中间不一定成立。

假设现在只看 $u \sim v$（当 $v < u$ 时视作 $v \sim u$）组成的一段，从左往右插入，第 $i$（$1 \leq i < u-v$）次插入会带来 $0 \sim i-1$ 的贡献，对应分组背包的第 $i$ 组物品，注意这里的 $u, v$ 全部是原序列中的下标，第 $i$ 次插入的元素在原序列的下标是 $u+i-1$。考虑到 $v$ 时，取决于 $v$ 是否大于 $u$，贡献一定是 $u-v$ 或 $0$。现在把序列剩下的部分加入。因为新增的逆序对数是 $0 \sim (\text{已经插入的数字的个数})$ 的结论仅在拓展序列边缘时成立，我们按 $u-1 \to 1, v+1 \to n$ 的顺序插入所有点，注意到每一步都是拓宽某个边界，因此第 $i$ 次插入恰好可以对逆序对贡献 $0 \sim i-1$，也可以对应分组背包的第 $i$ 组物品。但是第 $u-v$ 次只能贡献 $0/u-v$，这就是要撤销第 $u-v$ 组的原因。

因为背包可以理解为很多个 OGF 的卷积，最后得到的背包与处理每一组的贡献的顺序无关。倒着做一次贡献，把第 $u-v$ 组撤销，此时第 $k-i$ 项即为钦定这一组选 $i$ 后的贡献，就能得到我们需要的答案。

---

## 作者：_SeeleVollerei_ (赞：5)

先考虑一个严格弱于原问题的问题，求逆序对为 $k$ 的排列个数。

一种比较方便的数排列方法是从小到大类似插板地去填数，但是这个做法没有什么前途，不太好扩展到别的问题，所以先 pass 掉。

另一种方式就是直接从左往右扫，令 $f_{i,j}$ 表示填完了前 $i$ 个数，逆序对个数为 $j$ 的方案数。转移的时候发现我们只关心第 $i+1$ 和前面 $i$ 个数的大小关系，所以每次对逆序对的贡献为 $[0,i]$。

深度的贡献是复杂的，所以考虑拆这个贡献。然后发现深度就是祖先个数 +1。考虑枚举 $v$ 和 $u$，求 $v$ 是 $u$ 的祖先的方案数。

这里为了方便我们假设 $v<u$。对于 $v>u$ 的情况我们将整个序列翻转一下再做一次即可。

考虑是祖先的充要条件。肯定是在某个区间中，$v$ 和 $u$ 都在，然后 $v$ 是最小值。形式化地说，就是 $a_v<a_u$ 且不存在 $v<i<u$ 满足 $a_i<a_v$。然后考虑在这个基础上填数。

现在问题分为三个部分，一个是 $[v,u]$ 的数，一个是 $[1,v-1]$ 的数，一个是 $[u+1,n]$ 的数。

先填两边再填中间太困难了，因为要同时考虑两个方向。一个很好的想法是先把 $[v,u]$ 填了，然后往左填 $[1,v-1]$,然后往右填 $[u+1,n]$。

然后我们会发现这个虽然填的方向会有改变，但是每次填的数的贡献依然只会和已经填了的数的个数有关。然后会发现和最开始的弱化的问题的 dp 是差不多的。

唯一的不同是因为 $a_v$ 是 $a_{[v,u]}$ 的最小值，所以 $v$ 的贡献会有不同，固定为 0。

现在问题是有很多个物品，每个物品可以选 $[0,i]$ 的方案数。每次将其中一个物品强制设为 0，求和为 $k$ 的方案数。本质是一个带删除的背包，直接反着删一下就好了。

我们发现删除的这个物品对应的 $i$ 就是原问题中的 $u-v$。也就是说对于相同的 $u-v$，贡献是一样的。我们考虑枚举 $u-v$，然后跑一个背包内的删除操作。然后算出答案后再枚举 $u$ 贡献答案。

枚举 $u-v$ 是 $O(n)$ 的，背包内删除是 $O(k)$，枚举 $u$ 是 $O(n)$，所以总的复杂度为 $O(nk+n^2)$ 且常数极小。

空间复杂度 $O(nk)$，但是背包显然可以滚成 $O(k)$。

注意因为深度是祖先个数+1，所以最后还要加上一个总方案数。

```cpp
#include<cstdio>
const int N=305;
int n,k,Mod;
int f[N*N];
inline int Read(){
	char ch;
	int f=1;
	while((ch=getchar())<'0'||ch>'9')
		if(ch=='-') f=-1;
	int x=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
		x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
inline void print(int x){
	if(x>=10) print(x/10);
	putchar(x%10+48);
	return ;
}
inline void Print(int x,char ch='\n'){
	if(x<0){
		putchar('-');
		print(-x);
	}
	else print(x);
	putchar(ch);
	return ;
}
inline int addv(int x,int y){
	int s=x+y;
	if(s>=Mod) s-=Mod;
	return s;
}
inline int subv(int x,int y){
	int s=x-y;
	if(s<0) s+=Mod;
	return s;
}
inline void add(int&x,int y){
	x=addv(x,y);
	return ;
}
inline void sub(int&x,int y){
	x=subv(x,y);
	return ;
}
inline void Init(){
	n=Read(),k=Read(),Mod=Read();
	return ;
}
inline void Add(int i){
	for(int j=1;j<=k;j++)
		add(f[j],f[j-1]);
	for(int j=k;j>i;j--)
		sub(f[j],f[j-i-1]);
	return ;
}
inline void Del(int i){
	for(int j=i+1;j<=k;j++)
		add(f[j],f[j-i-1]);
	for(int j=k;j;j--)
		sub(f[j],f[j-1]);
	return ;
}
int ans[N];
inline void GetDp(bool flg){
	f[0]=1;
	for(int i=1;i<=k;i++)
		f[i]=0;
	//[0,i]
	for(int i=1;i<n;i++)
		Add(i);
	for(int i=1;i<n;i++){
		Del(i);
		for(int u=i+1;u<=n;u++)
			if(!flg) add(ans[u],f[k]);
			else add(ans[n-u+1],f[k]);
		Add(i);
	}
	return ;
}
inline void Solve(){
	GetDp(0);
	k=n*(n-1)/2-k;
	GetDp(1);
	for(int i=1;i<=n;i++)
		Print(addv(ans[i],f[k]),' ');
	putchar('\n');
	return ;
}
#include<ctime>
int main(){
	//#define LOCAL
	#ifdef LOCAL
	int st=clock();
	#endif
	Init();
	Solve();
	#ifdef LOCAL
	int en=clock();
	printf("cost %d ms\n",en-st);
	#endif
	return 0;
}
```

---

## 作者：Lgx_Q (赞：2)

题意：对一个排列 $a_{1...n}$ 构建笛卡尔树，对 $\forall i\in [1,n]$，求：对于所有逆序对个数为 $k$ 的排列 $a$，点 $i$ 的深度（其到根节点的点数）之和，答案对 $m$ 取模。

$1\le n\le 300,\space 0\le k\le \frac {n(n-1)}2,\space 10^8\le m\le 10^9+9$

---

逆序对个数为 $k$ 的排列个数是容易求的，设 $f[i,j]$ 表示前 $i$ 个数逆序对个数为 $j$ 的方案数，每次确定 $a_{1...i-1}$ 中多少个数比 $a_i$ 大，转移为 $f[i,j]=\sum\limits_{k=0}^{i-1}f[i-1,j-k]$。

考虑拆贡献，计算对于 $i$，$j(j\not =i)$ 是他的祖先的方案数。

发现条件 $a_i>a_j$，且 $i,j$ 之间的所有数字都要 $>a_j$。

那么 $a_j$ 是这一段的最小值，考虑计算方案数，我们先在 $a$ 中放一个 $a_j$。

然后放 $i\sim j$ 这一段的其他数字，这个方案数可以通过上面的 dp 求。

最后是 $i\sim j$ 之外的数字。放一个数字在前面，转移枚举后面多少个数比他小；放一个数字在后面，转移枚举前面多少个数字比他大。我们发现不管是前面还是后面放，枚举的数的范围是一样的，转移式都是一样的。

而且还发现上面的转移式其实相当于分组背包，第 $i$ 组为 $\{1,2,...,i-1\}$，背包可以用 GF 来搞。设 $F_i(x)=\sum\limits_j f[i,j]x^j$，设 $G_i(x)=\sum\limits_{j=0}^{i-1} x^j$，有 

$$F_i(x)=F_{i-1}(x)\cdot G_i(x)$$

设 $i\sim j$ 这一段的长度 $l=|i-j|+1$，钦定 $j<i$（即 $j$ 和这一段的其他数字没有产生逆序对），那么不难发现我们要求的东西就是

$$[x^k]G_1(x)G_2(x)...G_{l-1}(x)G_{l+1}(x)G_{l+2}(x)...G_n(x)$$

也就是 $[x^k]\frac{F_n(x)}{G_l(x)}$，$j>i$ 同理。预处理所有 $l$ 的答案，由于数据范围很小，暴力递推就行。时间复杂度 $O(nk)$.

```cpp
#include<bits/stdc++.h>
#define ls(p) a[p].lc
#define rs(p) a[p].rc
#define fi first
#define se second
#define mkp make_pair
#define ll long long
#define pir pair<ll,ll>
#define pb push_back
using namespace std;
const ll maxn=310;
ll n,k,mod,f[maxn*maxn],s[maxn*maxn],res[maxn][2],ans;
void add(ll x){
	s[0]=f[0];
	for(ll i=1;i<=k;i++) s[i]=(s[i-1]+f[i])%mod;
	for(ll i=k;i;i--){
		f[i]=(f[i]+s[i-1]+(i-x>=0? mod-s[i-x]:0))%mod;
	}
}
void del(ll x){
	s[0]=f[0];
	for(ll i=1;i<=k;i++){
		f[i]=(f[i]-s[i-1]+mod+(i-x>=0? s[i-x]:0))%mod;
		s[i]=(s[i-1]+f[i])%mod;
	}
}
int main(){ 
	scanf("%lld%lld%lld",&n,&k,&mod);
	f[0]=1;
	for(ll i=1;i<=n;i++){
		add(i);
	}
	for(ll l=2;l<=n;l++){
		del(l);
		res[l][0]=f[k];
		if(l-2<k) res[l][1]=f[k-(l-2)-1];
		add(l);
	}
	for(ll i=1;i<=n;i++){
		ans=f[k];
		for(ll j=1;j<=n;j++)
			if(i!=j){
				ans=(ans+res[abs(i-j)+1][i<j])%mod;
			}
		printf("%lld ",ans);
	}
	return 0;
}
```

---

## 作者：kuikuidadi (赞：1)

# 思路
$u$ 是 $v$ 的祖宗的充要条件：$u$ 是 $[u,v]$ 中最小的，从小往大加元素，第 $i$ 个加入的元素贡献为 $[0,i-1]$。然后我们枚举 $i$，和 $j-i=len$。然后就是求这个多项式的第 $\frac{k}{k-(|len|-1)}$ 项：$$\prod_{t=0}^z \sum_{i=0}^tx^i\times \prod_{t=z+1}^n \sum_{i=0}^tx^i$$。

我们可以分别对前缀和后缀搞一个背包，前缀和优化一下就可以 $O(NK)$ 做到。

设 $pre_{i,j}$ 表示前 $i$ 个，总和为 $j$ 的方案数。$suf_{i,j}$ 表示后 $i$ 个，总和 $j$ 的方案数。

然后两个部分卷积的时候可以发现，我们只关心两项：

$A_i$ 表示 $pre_{i,j}\times suf_{n-i}$ 的第 $k$ 项。

$B_i$ 表示 $pre_{i,j}\times suf_{n-i}$ 的第 $k-(i-1)$ 项。

最后 $O(NK)$ 计算。

---

## 作者：Anonymely (赞：1)

笛卡尔树形态非常难维护，考虑如何处理最后的答案，考虑一个点 $u$，它的深度相当于它的祖先个数，于是枚举一个点 $v$，计算 $v$ 是 $u$ 祖先时有多少方案。

$v$ 是 $u$ 祖先的条件是 $a_v < a_u$，且满足 $a_v$ 是 $[\min(u,v),\max(u,v)]$ 这一段中的最小值。

接下来考虑逆序对数量为 $k$ 的限制，若没有 $u,v$ 的要求则是经典问题，考虑每次插入 $i$，能造成逆序对数量为 $[0,i-1]$，于是答案就是 $[x^k] \prod_{i=0}^{n-1} \sum_{j=0}^i x^j$。

有了 $u,v$ 限制怎么办呢，先插入 $[\min(u,v),\max(u,v)]$ 这一段，再插入前缀，再插入后缀，不难发现除了插入 $v$ 的时候有问题，剩下的贡献一模一样。而插入 $v$ 时的贡献由于钦定 $v$ 是最小值，所以 $u<v$ 是贡献为 $x^{v-u}$，否则为 $x^0$。

答案只跟 $v-u$ 差值有关！于是暴力维护多项式，每次初掉一项，复杂度 $O(n^3)$。

---

## 作者：tzc_wk (赞：1)

[洛谷题面传送门](https://www.luogu.com.cn/problem/P5853)

神仙题。

首先考虑一个点的深度是什么，注意到对于笛卡尔树而言直接从序列的角度计算一个点的深度是不容易的，因为这样会牵扯到序列中多个元素，需要 fixed 的东西太多，计算起来太复杂了。因此考虑从**树本身**的角度计算一个点的深度。注意到对于一棵树上所有点 $u$​ 而言都有 $dep_u=\sum\limits_{v}[\text{LCA}(u,v)=v]$​，因此我们求解一个点 $x$​ 的答案时，可以枚举所有 $u,v$​ 并计算 $v$​ 对 $u$​ 的贡献，即，有多少个排列满足逆序对个数为 $k$​，且笛卡尔树上 $v$​ 为 $u$​​ 的祖先。并且我们还可以注意到，对于一个序列而言，其笛卡尔树上某两点存在祖先关系是存在充要条件转化的，具体来说，$\text{LCA}(u,v)=v$ 当且仅当 $a_v$ 为 $a[\min(u,v)…\max(u,v)]$ 的最小值，因此我们只需求解以下问题：

> 有多少个排列 $p$，满足其逆序对个数为 $k$，且 $a_v=\min\limits_{i=\min(u,v)}^{\max(u,v)}a_i$

这个问题看似难以下手，因为外面就已经枚举了两维 $u,v$ 了，里面这东西也无法直接组合数求解，需要用 DP 之类的东西，一弄最低就是 $n^3$，直接爆炸，不过细想其实不用复杂度那么高。我们首先考虑如果没有第二个条件怎么求，我们设 $dp_{i,j}$ 表示有多少个长度为 $i$ 的排列有 $j$ 个逆序对，考虑怎么转移，不难发现，对于长度为 $i+1$ 的排列，我们总能找到唯一的 $a_{i+1}$，满足 $a_{i+1}$ 与前面 $i$ 个数产生的逆序对数为 $x(x\in[0,i])$，也就是说 $dp_{i+1,j}=\sum\limits_{x=0}^idp_{i,j-x}$，前缀和优化一下即可，这个在 CF1542E2 Abnormal Permutation Pairs (hard version) 中就已经见过了。对于此题亦是如此，与经典问题不同的一点是，直接按照 $1,2,3,\cdots,n$ 的位置填数会爆炸，因此考虑换个顺序，如果 $u<v$ 那么我们就按照 $u,u+1,u+2,\cdots,v,u-1,u-2,\cdots,1,v+1,v+2,\cdots,n$ 的顺序填数，否则我们按照 $u,u-1,u-2,\cdots,v,u+1,u+2,\cdots,n,v-1,v-2,\cdots,1$ 的顺序填。不难发现按照这样的顺序填数之后，其他位置上的填法都和前面一样，即第 $i$ 个填的数可以为排列逆序对数产生 $[0,i-1]$ 中任意一个数的贡献，唯独 $v$ 只有一种填法。而两种情况的差别的，前一种情况 $v$ 会对排列逆序对数产生 $|u-v|$ 的贡献，而后一种不会，因此如果写成生成函数的形式，就是前一种情况的方案数为 $[x^k]·x^{|u-v|}\prod\limits_{i=0}^{|u-v|-1}(\sum\limits_{j=0}^ix^j)·\prod\limits_{i=|u-v|+1}^{n-1}(\sum\limits_{j=0}^ix^j)$，后一种情况的方案数为 $x^{|u-v|}\prod\limits_{i=0}^{|u-v|-1}(\sum\limits_{j=0}^ix^j)·\prod\limits_{i=|u-v|+1}^{n-1}(\sum\limits_{j=0}^ix^j)$，注意到对于一对 $u,v$ 而言，上面两个式子的值只与 $|u-v|$ 有关，因此可以对所有 $|u-v|$ 预处理一波答案，复杂度 $\mathcal O(n^4)$。如果你观察能力再强一些，你还能发现这式子可以写成背包的形式，你对前后缀各做一遍背包就可以 $n^3$ 求解了。

```cpp
const int MAXN=300;
const int MAXK=44850;
int n,k,mod;
int pre[MAXN+5][MAXK+5],suf[MAXN+5][MAXK+5];
int sum[MAXK+5],c1[MAXN+5],c2[MAXN+5];
int getsum(int l,int r){return (sum[r]-((!l)?0:sum[l-1])+mod)%mod;}
int main(){
	scanf("%d%d%d",&n,&k,&mod);pre[0][0]=1;
	for(int i=0;i<=k;i++) sum[i]=1;
	for(int i=1;i<n;i++){
		for(int j=0;j<=k;j++) pre[i][j]=getsum(j-i,j);
		memset(sum,0,sizeof(sum));sum[0]=pre[i][0];
		for(int j=1;j<=k;j++) sum[j]=(sum[j-1]+pre[i][j])%mod;
	} suf[n][0]=1;
	for(int i=0;i<=k;i++) sum[i]=1;
	for(int i=n-1;~i;i--){
		for(int j=0;j<=k;j++) suf[i][j]=getsum(j-i,j);
		memset(sum,0,sizeof(sum));sum[0]=suf[i][0];
		for(int j=1;j<=k;j++) sum[j]=(sum[j-1]+suf[i][j])%mod;
	} c1[0]=c2[0]=pre[n-1][k];
	for(int i=1;i<n;i++){
		for(int j=0;j<=k;j++) c1[i]=(c1[i]+1ll*pre[i-1][j]*suf[i+1][k-j])%mod;
		for(int j=0;j<=k-i;j++) c2[i]=(c2[i]+1ll*pre[i-1][j]*suf[i+1][k-i-j])%mod;
	} for(int i=1;i<=n;i++){
		int res=0;
		for(int j=1;j<=n;j++){
			if(j<=i) res=(res+c1[i-j])%mod;
			else res=(res+c2[j-i])%mod;
		} printf("%d%c",res," \n"[i==n]);
	}
	return 0;
}
```



---

