# [ARC169F] Large DP Table

## 题目描述

给定长度为 $N$ 的整数序列 $A=(A_1,A_2,\cdots,A_N)$、$B=(B_1,B_2,\cdots,B_N)$、$X=(X_1,X_2,\cdots,X_N)$、$Y=(Y_1,Y_2,\cdots,Y_N)$。其中，$A$ 和 $B$ 满足以下性质：

- $A_1=1$。
- $B_1=2$。
- $(A_1,A_2,\cdots,A_N,B_1,B_2,\cdots,B_N)$ 是 $(1,2,\cdots,2N)$ 的一个排列。

定义整数 $d_{i,j}$（$1\leq i,j\leq N$）如下：

- $d_{1,1}=0$。
- 当 $(i,j)\neq (1,1)$ 且 $A_i < B_j$ 时：$d_{i,j}=d_{i,j-1}+X_i$。
- 当 $(i,j)\neq (1,1)$ 且 $A_i > B_j$ 时：$d_{i,j}=d_{i-1,j}+Y_j$。

请计算 $\sum_{1\leq i\leq N}\sum_{1\leq j\leq N}d_{i,j}$，并输出其对 $998244353$ 取模的结果。

## 说明/提示

## 限制条件

- $2\leq N\leq 250000$。
- $A_1=1$。
- $B_1=2$。
- $(A_1,A_2,\cdots,A_N,B_1,B_2,\cdots,B_N)$ 是 $(1,2,\cdots,2N)$ 的一个排列。
- $1\leq X_i\leq 10^9$。
- $1\leq Y_i\leq 10^9$。
- 输入的所有值均为整数。

## 样例解释 1

$d_{i,j}$ 的值如下：

- $d_{1,1}=0$
- $d_{1,2}=d_{1,1}+X_1=0+2=2$
- $d_{2,1}=d_{1,1}+Y_1=0+1=1$
- $d_{2,2}=d_{1,2}+Y_2=2+3=5$

因此，所求答案为 $0+2+1+5=8$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
1 4
2 3
2 2
1 3```

### 输出

```
8```

## 样例 #2

### 输入

```
3
1 3 5
2 6 4
1 10 100
1000 10000 100000```

### 输出

```
108153```

## 样例 #3

### 输入

```
3
1 6 5
2 4 3
1 10 100
1000 10000 100000```

### 输出

```
333009```

## 样例 #4

### 输入

```
10
1 17 4 7 16 18 9 3 12 6
2 19 20 14 5 11 13 8 15 10
744280520 249168130 239276621 320064892 910500852 164832983 245532751 198319687 715892722 967824729
769431650 80707350 459924868 257261830 777045524 583882654 950300099 438099970 322288793 532405020```

### 输出

```
746075419```

# 题解

## 作者：xuanxuan001 (赞：5)

没人搬官方题解，来搬一波，感觉这题还是比较妙的。

考虑每个位置在这个“DP Table”上的转移形成的路径，然后转而考虑有多少个位置的路径会经过形如```(a,b)->(a,b-1)```这个转移。

考虑所有满足 $x \ge a,y \ge b$ 的 $(x,y)$ 组成的区域 $S$（官方题解称之为 $R(a,b)$），那么考虑观察一个点 $(c,d)$，当然要满足 $c \ge a,d \ge b$，它的转移路径一定会有一步是从 $S$ 内跨到 $S$ 外，那么考虑这一步是向下（$x$ 减去 $1$）还是向左（$y$ 减去 $1$）。

设 $\min A[l,r]$ 表示 $A$ 数组下标在 $[l,r]$ 的所有元素的最小值，$\min B[l,r]$ 同理，那么 $(c,d)$ 会向左离开 $S$ 当且仅当满足 $\min A[a,c] < \min B[b,d]$，证明显然，$A$ 的最小值的位置会干掉所有 $B$ 的对应位置。

但从左边离开也不代表就一定走的是```(a,b)->(a,b-1)```，所以要求出这个还需要减去从左边离开 $(a+1,b)$ 为左下角的区域的方案数，所以它被经过的方案数就是

$$
\sum\limits_{c=a}^n\sum\limits_{d=b}^n[\min A[a,c] < \min B[b,d]] - \sum\limits_{c=a+1}^n\sum\limits_{d=b}^n[\min A[a+1,c] < \min B[b,d]]
$$

然后再乘上系数 $X_a$ 即可。

发现两部分是类似的，那么可以给系数 $X$ 做处理，给每个 $X_i(2 \le i \le n)$ 同时进行 $X_i \leftarrow X_i - X_{i-1}$ 即可，然后可以得到所有向左的转移的带权和就是

$$
\sum\limits_{a=1}^n\sum\limits_{b=1}^n\sum\limits_{c=a}^n\sum\limits_{d=b}^nX_a[\min A[a,c] < \min B[b,d]]
$$

同理可以计算出向下转移的带权和。

发现上面的式子其实只比较两个 $\min$ 的大小关系，那么可以处理出 $F_{A.i} = \sum\limits_{l=1}^n\sum\limits_{r=l}^n[\min A[l,r]==i]$，$G_{A.i} = \sum\limits_{l=1}^n\sum\limits_{r=l}^nX_l[\min A[l,r]==i]$，$F_B,G_B$ 同理。

那么答案就是

$$
\sum\limits_{i=1}^{2n}\sum\limits_{j=i+1}^{2n}G_{A,i}F_{B,j} + G_{B,i}F_{A,j}
$$

$F,G$ 可以用各种方法求出，如笛卡尔树等，我用的是从大到小插入值然后并查集合并信息的思路。

代码

```
#include<cstdio>
#define TY int
#define MAXN 250002
#define MAXM 500002
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
#define EDG(i,u) for(TY i=hed[u];i;i=nxt[i])
using namespace std;
typedef long long ll;
const TY M=998244353;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
inline void updmx(TY &x,TY y){if(x<y)x=y;}
inline void updmn(TY &x,TY y){if(x>y)x=y;}
inline void add(TY &x,TY y){if((x+=y)>=M)x-=M;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(1&b)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n'||ch=='\r')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a){if(a>9)qw(a/10);putchar(a%10+'0');}
void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY n=qr(),m,a[MAXN],b[MAXN],x[MAXN],y[MAXN],ps[MAXM],u,p,q;
TY fa[MAXN],sz[MAXN],sm[MAXN],nma[MAXM],sma[MAXM],nmb[MAXM],smb[MAXM],ans;
TY getfa(TY u){return fa[u]!=u?fa[u]=getfa(fa[u]):u;}
//代码中nma=FA,nmb=FB,sma=GA,smb=GB
int main(){
	FOR(i,1,n)a[i]=qr();FOR(i,1,n)b[i]=qr();
	FOR(i,1,n)x[i]=qr();FOR(i,1,n)y[i]=qr();
	ROF(i,n,2){add(x[i],M-x[i-1]);add(y[i],M-y[i-1]);}
	ans=1ll*((M<<1)-x[1])*n%M*n%M;//先去掉从(1,1)向左转移的贡献
	m=n<<1;FOR(i,1,n)ps[a[i]]=i;
	ROF(i,m,1)if(u=ps[i]){
		sm[fa[u]=u]=x[u];sz[u]=1;p=q=0;
		if(fa[u-1])fa[p=getfa(u-1)]=u;
		if(fa[u+1])fa[q=getfa(u+1)]=u;
		add(sm[u],sm[p]);add(sm[u],sm[q]);sz[u]+=sz[p]+sz[q];
		add(sma[i],1ll*(sm[p]+x[u])*(sz[q]+1)%M);
		add(nma[i],1ll*(sz[p]+1)*(sz[q]+1)%M);
	}FOR(i,1,m)ps[i]=0;
	FOR(i,1,n)fa[ps[b[i]]=i]=0;
	ROF(i,m,1)if(u=ps[i]){
		sm[fa[u]=u]=y[u];sz[u]=1;p=q=0;
		if(fa[u-1])fa[p=getfa(u-1)]=u;
		if(fa[u+1])fa[q=getfa(u+1)]=u;
		add(sm[u],sm[p]);add(sm[u],sm[q]);sz[u]+=sz[p]+sz[q];
		add(smb[i],1ll*(sm[p]+y[u])*(sz[q]+1)%M);
		add(nmb[i],1ll*(sz[p]+1)*(sz[q]+1)%M);
	}ROF(i,m-1,1){
		add(nma[i],nma[i+1]);
		add(nmb[i],nmb[i+1]);
	}FOR(i,1,m){
		add(ans,1ll*sma[i]*nmb[i+1]%M);
		add(ans,1ll*smb[i]*nma[i+1]%M);
	}qw(ans);return 0;
}
```

---

## 作者：dead_X (赞：3)

## 思路
考虑对每个格子 $(x,y)$ 算贡献，也就是其右下角点数减掉被这行这列剩下点截胡的点数。

第 $a$ 行会截胡 $(x_0,y_0)$，当且仅当 $A_a$ 是最后一个比 $B_{[y,y_0]}$ 都小的点。因为我们并不关心到底哪个 $a$ 截胡了，所以只需要 $A_{(x,x_0]}$ 存在比 $B_{[y,y_0]}$ 都小的点，$(x_0,y_0)$ 就会被截胡。

因此，如果 $(x_0,y_0)$ 能到达 $(x,y)$ 当且仅当 $B_y<\min(A_{(x,x_0]})<\min(B_{(y,y_0]})$ 或者其互换维度的情况，问题数据结构了起来！

直接列出 $A_x$ 的所有贡献，发现就是 $A_x<\min(B_{[y,y_0]})<\min(A_{(x,x_0]})$。

这个显然就是 $\min(A_{[x,x_0]})<\min(B_{[y,y_0]})$ 减 $\min(A_{(x,x_0]})<\min(B_{[y,y_0]})$。

于是只需要求出以下子问题：

> 给定长度为 $n$ 的排列，每个位置有权值，对于每个 $i$ 求最小值等于 $i$ 的所有区间的左端点权值之和。

建笛卡尔树即可。
## 代码
```cpp
// Problem: F - Large DP Table
// Contest: AtCoder - estie Programming Contest 2023 (AtCoder Regular Contest 169)
// URL: https://atcoder.jp/contests/arc169/tasks/arc169_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//泥の分際で私だけの大切を奪おうだなん
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int a[250003],b[250003];
int xv[250003],yv[250003];
int n=read();
int xa[500003],xb[500003];
int ya[500003],yb[500003];
int stk[250003],top;
int ls[250003],rs[250003];
void dfsx(int l,int r,int x)
{
	xb[a[x]]=1ll*(x-l+1)*(r-x+1)%p,
	xa[a[x]]=1ll*(p+xv[x]-xv[l-1])*(r-x+1)%p;
	if(ls[x]) dfsx(l,x-1,ls[x]);
	if(rs[x]) dfsx(x+1,r,rs[x]);
	return ;
}
void dfsy(int l,int r,int x)
{
	ya[b[x]]=1ll*(x-l+1)*(r-x+1)%p,
	yb[b[x]]=1ll*(p+yv[x]-yv[l-1])*(r-x+1)%p;
	if(ls[x]) dfsy(l,x-1,ls[x]);
	if(rs[x]) dfsy(x+1,r,rs[x]);
	return ;
}
signed main()
{
	for(int i=1; i<=n; ++i) a[i]=read();
	for(int i=1; i<=n; ++i) b[i]=read();
	for(int i=1; i<=n; ++i) xv[i]=read();
	for(int i=1; i<=n; ++i) yv[i]=read();
	int ans=0;
	for(int i=1; i<=n; ++i)
	{
		while(top&&a[i]<a[stk[top]]) ls[i]=stk[top--];
		if(top) rs[stk[top]]=i;
		stk[++top]=i;
	}
	dfsx(1,n,stk[1]),top=0,
	memset(stk,0,sizeof(stk)),
	memset(ls,0,sizeof(ls)),
	memset(rs,0,sizeof(rs));
	for(int i=1; i<=n; ++i)
	{
		while(top&&b[i]<b[stk[top]]) ls[i]=stk[top--];
		if(top) rs[stk[top]]=i;
		stk[++top]=i;
	}
	dfsy(1,n,stk[1]);
	for(int i=1,s=0; i<=n*2; ++i)
		s=(s+xa[i])%p,ans=(ans+1ll*ya[i]*s)%p;
	for(int i=1,s=0; i<=n*2; ++i)
		s=(s+yb[i])%p,ans=(ans+1ll*xb[i]*s)%p;
	ans=(ans+p-1ll*n*n%p*xv[1]%p)%p;
	puts("HaitangSuki");
	return 0;
}
```

---

## 作者：qiuzx (赞：1)

## 题意

给定长为 $n$ 的数列 $a_i,b_i,x_i,y_i$，保证 $a_1=1,b_1=2$ 且它们构成一组 $\{1,\ldots,2n\}$ 的排列。定义数组 $d_{i,j}$，其中 $d_{1,1}=0$，若 $a_i<b_j$，则 $d_{i,j}=d_{i,j-1}+x_i$，否则 $d_{i,j}=d_{i-1,j}+y_j$，求 $\sum_{i=1}^n\sum_{j=1}^n d_{i,j}$ 模 $998244353$ 的结果。$n\le 2.5\times 10^5$。

## 思路

首先若 $d_{i,j}=d_{i,j-1}+x_i$ 就从 $(i,j-1)$ 向 $(i,j)$ 连边权为 $x_i$ 的边，另一种情况同理，则构成了一棵外向树，容易将答案转化为求每条边的权值乘上它子树的大小。

考虑将这个问题的规模不断缩小，直到变成 $1\times 1$ 的情形。那么要么找到最小的值消除这一行或这一列，要么找到最大的消除，都尝试一下可以发现消除最大值是可做的。具体来说，不妨假设剩余的数中最大值对应了某一列，假设是第 $c$ 列，那么可以发现对于所有的 $i$，有边 $(i,c-1)\to (i,c)$，权值为 $x_i$。那么如果把第 $c$ 列删掉，会对答案产生什么样的影响呢？

对于某个 $i$，若原来有边 $(i,c)\to (i,c+1)$，则删掉这一列之后会有边 $(i,c-1)\to (i,c+1)$，假设 $(i,c+1)$ 的子树大小为 $s$，那么现在 $(i,c-1)\to (i,c)$ 和 $(i,c)\to (i,c+1)$ 的贡献是 $x_i\times s+x_i\times (s+1)=2x_i\times s+x_i$。所以将 $(i,c-1)\to (i,c+1)$ 的权值设为 $2x_i$，然后给答案加上 $x_i$ 就能解决这部分的贡献。此外由于删了一个点，所以对于 $(i,c-1)$ 前面的边，它们的子树大小会增加 $1$，解决这个问题的方法是给每个点带权，初始全部为 $1$，将子树大小定义为子树中点权之和，定义 $v_{i,j}$ 为点权，$w_{i,j}$ 为 $(i,j)$ 父边的边权，则一次这样的操作可以看作将答案加上 $v_{i,c}\times w_{i,c}$，然后 $w_{i,c+1}+=w_{i,c}$，$v_{i,c-1}+=v_{i,c}$。如果原本没有这条边，那么 $(i,c+1)$ 从上面连过来，删除这一列不对它产生影响，此时将答案加上 $v_{i,c}\times w_{i,c}$，然后仅执行 $v_{i,c-1}+=v_{i,c}$。

但是这样搞得人很不爽，因为分这两种情况讨论就没法接着优化了，所以考虑将两种情况统一一下。发现两种情况的区别在于 $w$ 的更新，所以我们重新定义两个数组 $wx_{i,j}$ 和 $wy_{i,j}$，其中若 $(i,j)$ 父边从上面连过来，那么 $wy_{i,j}=w_{i,j}$，否则 $wx_{i,j}=w_{i,j}$，其它的值无定义，所以不管其值是多少都不重要。这样的好处是什么呢？由于删除一列的时候所有边都是从左侧来的，所以将答案的更新式子变为 $\sum v_{i,c}\times wx_{i,c}$ 即可，而在更新时只需要将所有的 $wx_{i,c+1}+=wx_{i,c}$ 即可，容易说明这样和原来是等价的，对于删除行的情况也是同理，这样我们就得到了一个具有很好形式的 $O(n^2)$ 做法。

考虑进一步优化这个做法，首先容易发现若设 $nxtx_i,nxty_i$ 分别表示 $i$ 的下一个未被删除的行与列，则 $v_{i,j}=(nxtx_i-i)(nxty_j-j)$，可以使用归纳法证明，其组合意义是这个删除的过程相当于在折叠这个矩阵，$v_{i,j}$ 就表示它右下方有多少个点被折叠了。然后发现若设 $lstx_i,lsty_i$ 表示 $i$ 的上一个未被删除的行与列，则 $wx_{i,j}=(j-lsty_j)x_i,wy_{i,j}=(i-lstx_i)y_j$，也可以从折叠的角度说明这一点。于是问题就变成了维护 $lstx,lsty,nxtx,nxty$，求 $\displaystyle\sum_{i} (nxtx_i-i)(nxty_j-j)(j-lsty_j)x_i$。对于每个 $i$ 维护 $(nxtx_i-i)x_i$ 的结果即可，修改是单点修改，使用 set 维护，另一侧对 $j$ 的维护也是同理，复杂度 $O(n\log n)$。

[代码](https://atcoder.jp/contests/arc169/submissions/48335586)

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc169_f)

**题目大意**

> 给定 $1\sim 2n$ 排列 $a_1\sim a_n,b_1\sim b_n$，定义 $f_{i,j}=\begin{cases}f_{i,j-1}+x_i&a_i<b_j\\f_{i-1,j}+y_j&\mathrm{otherwise}\end{cases}$，其中 $f_{1,1}=0$，求 $\sum_{i,j} f_{i,j}$。
>
> 数据范围：$n\le 2.5\times 10^5$。

**思路分析**

题目相当于给出一个 $n\times n$ 的转移网格，每个点从左侧或上侧转移并附带一个额外权值。

考虑 $x_i$ 在 $(i,j)$ 处的贡献，如果 $a_i<b_j$，那么我们就是要数 $(i,j)$ 右下方有多少个点和 $(i,j)$ 连通。

不难发现如果 $(i,j)$ 和 $(p,q)$ 不连通，一定是存在一行或一列的边都不存在。

分析发现如果某一行 $a_k$ 满足 $a_k<\min b(j,q]$，那么 $k$ 这一行就不会和之前的点连通，如果某一列 $b_k$ 满足 $b_k<\min a(i,p]$，那么 $k$ 这一列就不会和之前的点连通。

因此 $a[i,p],b[j,q]$ 中的最小值一定是 $a_i$ 或 $b_j$，由于钦定了 $a_i<b_j$，因此 $x_i$ 在 $(i,j)$ 处对 $(p,q)$ 有贡献当且仅当 $a_i<\min b[j,q]<\min a(i,p]$。

我们要对这样的区间计数，设 $f_w$ 表示 $\min b[j,q]\le w$ 的元素个数，可以用单调栈预处理。

然后就是要求 $x_i\sum_p f_{\min a(i,p]}-f_{a_i}$，注意到 $\min a(i,p]$ 一定是 $a[i,n]$ 的后缀单调栈上的元素，并且因为 $\min a(i,p]>a_i$，因此一定是后缀单调栈上被 $a_i$ 弹出的元素，答案是容易计算的，加上 $p=i$ 的贡献即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2.5e5+5,MOD=998244353;
int n,stk[MAXN],tp;
void solve(int *a,int *l,int *r,ll *f) {
	stk[tp=0]=0;
	for(int i=1;i<=n;++i) {
		while(tp&&a[stk[tp]]>a[i]) r[stk[tp--]]=i;
		l[i]=stk[tp],stk[++tp]=i;
	}
	while(tp) r[stk[tp--]]=n+1;
	for(int i=1;i<=n;++i) f[a[i]]=1ll*(r[i]-i)*(i-l[i])%MOD;
	for(int i=2*n;i;--i) f[i]=(f[i]+f[i+1])%MOD;
}
int a[MAXN],b[MAXN],la[MAXN],ra[MAXN],lb[MAXN],rb[MAXN],wa[MAXN],wb[MAXN];
ll fa[MAXN<<1],fb[MAXN<<1];
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) scanf("%d",&b[i]);
	for(int i=1;i<=n;++i) scanf("%d",&wa[i]);
	for(int i=1;i<=n;++i) scanf("%d",&wb[i]);
	solve(a,la,ra,fa),solve(b,lb,rb,fb);
	ll ans=0;
	stk[tp=0]=n+1;
	for(int i=n;i>=1;--i) {
		for(;tp&&a[stk[tp]]>a[i];--tp) {
			ans+=wa[i]*(fb[a[i]]-fb[a[stk[tp]]])%MOD*(stk[tp-1]-stk[tp])%MOD;
		}
		ans+=wa[i]*fb[a[i]]%MOD,stk[++tp]=i;
	}
	stk[tp=0]=n+1;
	for(int i=n;i>=1;--i) {
		for(;tp&&b[stk[tp]]>b[i];--tp) {
			ans+=wb[i]*(fa[b[i]]-fa[b[stk[tp]]])%MOD*(stk[tp-1]-stk[tp])%MOD;
		}
		ans+=wb[i]*fa[b[i]]%MOD,stk[++tp]=i;
	}
	ans-=1ll*n*n%MOD*wa[1]%MOD;
	printf("%lld\n",(ans%MOD+MOD)%MOD);
	return 0;
}
```

---

