# [PKUWC2018] Minimax

## 题目描述

小 $C$ 有一棵 $n$ 个结点的有根树，根是 $1$ 号结点，且每个结点最多有两个子结点。

定义结点 $x$ 的权值为：

1.若 $x$ 没有子结点，那么它的权值会在输入里给出，**保证这类点中每个结点的权值互不相同**。

2.若 $x$ 有子结点，那么它的权值有 $p_x$ 的概率是它的子结点的权值的最大值，有 $1-p_x$ 的概率是它的子结点的权值的最小值。

现在小 $C$ 想知道，假设 $1$ 号结点的权值有 $m$ 种可能性，**权值第 $i$ 小**的可能性的权值是 $V_i$，它的概率为 $D_i(D_i>0)$，求：

$$\sum_{i=1}^{m}i\cdot V_i\cdot D_i^2$$

你需要输出答案对 $998244353$ 取模的值。


## 说明/提示


#### 样例解释
1号结点的权值有 $\frac{1}{2}$ 的概率是 $1$，有 $\frac{1}{2}$ 的概率是 $2$，所以答案是 $\frac{5}{4}$。

#### 数据范围

- 对于 $10\%$ 的数据，有 $1\leq n\leq 20$；  
- 对于 $20\%$ 的数据，有 $1\leq n\leq 400$；  
- 对于 $40\%$ 的数据，有 $1\leq n\leq 5000$；  
- 对于 $60\%$ 的数据，有 $1\leq n\leq 10^5$；  
- 另有 $10\%$ 的数据保证树的形态随机；  
- 对于 $100\%$ 的数据，有 $1\leq n\leq 3\times 10^5$，$1\leq w_i\leq 10^9$。

对于所有数据，满足 $0 < p_i \cdot 10000 < 10000$，所以易证明所有叶子的权值都有概率被根取到。


## 样例 #1

### 输入

```
3
0 1 1
5000 1 2```

### 输出

```
748683266```

# 题解

## 作者：1saunoya (赞：55)

好妙的一个题…

我们设 $f_{i,j}$ 为 $i$ 节点出现 $j$ 的概率

设 $l = ch[i][0] , r = ch[i][1]$
即左儿子右儿子

设 $m$ 为叶子结点的个数

显然，$i$ 出现 $j$ 的概率为
$$f_{i,j} = f_{l,j} * (p_i \sum_{k=1}^{j-1}f_{r,k} + (1-p_i)\sum_{k=j+1}^{m}f_{r,k}) + f_{r,j} * (p_i \sum_{k=1}^{j-1}f_{l,k} + (1-p_i)\sum_{k=j+1}^{m}f_{l,k})$$

不难发现，这个柿子有关前缀和和后缀和，可以用线段树合并的操作来进行转移，从下到上转移，求出根节点的概率就好了…

```cpp
#include <cstdio>
#include <algorithm>

int read() {
  int x = 0;
  char c = 0;
  while (c < 48) c = getchar();
  while (c > 47) x = (x << 1) + (x << 3) + (c & 15), c = getchar();
  return x;
}

const int mod = 998244353;
int qpow(int x, int y) {
  int ans = 1;
  for (; y; y >>= 1, x = 1ll * x * x % mod)
    if (y & 1) ans = 1ll * ans * x % mod;
  return ans;
}

int n;
const int maxn = 3e5 + 10;
int ch[maxn][2], fa[maxn], cnt[maxn], val[maxn], tmp[maxn], qwq = 0, s[maxn];
int rt[maxn], ls[maxn << 5], rs[maxn << 5], sum[maxn << 5], mul[maxn << 5];
int ans = 0, tot = 0;

void pushup(int rt) { sum[rt] = (sum[ls[rt]] +sum[rs[rt]]) % mod; }
void pushmul(int rt, int v) {
  if (!rt) return;
  sum[rt] = 1ll * sum[rt] * v % mod;
  mul[rt] = 1ll * mul[rt] * v % mod;
}

void pushd(int rt) {
  if (mul[rt] == 1) return;
  if (ls[rt]) pushmul(ls[rt], mul[rt]);
  if (rs[rt]) pushmul(rs[rt], mul[rt]);
  mul[rt] = 1;
}

int newnode() {
	int x = ++ tot; 
	ls[x] = rs[x] = sum[x] = 0, mul[x] = 1 ;
	return x ;
}
void upd(int& p, int l, int r, int x, int v) {
  if (!p) p = newnode() ;
  if (l == r) {
    sum[p] = v;
    return;
  }
  pushd(p);
  int mid = l + r >> 1;
  (x <= mid) ? upd(ls[p], l, mid, x, v) : upd(rs[p], mid + 1, r, x, v);
  pushup(p);
}

int merge(int x, int y, int l, int r, int xmul, int ymul, int v) {
  if (!x && !y) return 0;
  if (!x) {
    pushmul(y, ymul);
    return y;
  }
  if (!y) {
    pushmul(x, xmul);
    return x;
  }
  pushd(x), pushd(y);
  int mid = l + r >> 1;
  int lsx = sum[ls[x]], lsy = sum[ls[y]], rsx = sum[rs[x]], rsy = sum[rs[y]];
  ls[x] = merge(ls[x], ls[y], l, mid, (xmul + 1ll * rsy % mod * (1 - v + mod)) % mod,
                (ymul + 1ll * rsx % mod * (1 - v + mod)) % mod, v);
  rs[x] = merge(rs[x], rs[y], mid + 1, r, (xmul + 1ll * lsy % mod * v) % mod,
                (ymul + 1ll * lsx % mod * v) % mod, v);
  pushup(x);
  return x;
}

void out(int x, int l, int r) {
  if (!x) return;
  if (l == r) {
    s[l] = sum[x];
    return;
  }
  int mid = l + r >> 1;
  pushd(x);
  out(ls[x], l, mid);
  out(rs[x], mid + 1, r);
}

void dfs(int u) {
  if (!cnt[u]) upd(rt[u], 1, qwq, val[u], 1);
  if (cnt[u] == 1) dfs(ch[u][0]), rt[u] = rt[ch[u][0]] ;
  if (cnt[u] == 2) dfs(ch[u][0]), dfs(ch[u][1]), rt[u] = merge(rt[ch[u][0]], rt[ch[u][1]] ,1 , qwq , 0 , 0 , val[u]);
}

int main() {
  n = read();
  for (int i = 1; i <= n; i++) fa[i] = read();
  for (int i = 1; i <= n; i++)
    if (fa[i]) ch[fa[i]][cnt[fa[i]]++] = i;
  for (int i = 1; i <= n; i++) val[i] = read();
  for (int i = 1; i <= n; i++) {
    if (cnt[i]) {
      val[i] = 1ll * val[i] * qpow(10000, mod - 2) % mod;
    } else {
      tmp[++qwq] = val[i];
    }
  }
  std ::sort(tmp + 1, tmp + qwq + 1);
  for (int i = 1; i <= n; i++)
    if (!cnt[i]) val[i] = std ::lower_bound(tmp + 1, tmp + qwq + 1, val[i]) - tmp;
  dfs(1);
  out(rt[1], 1, qwq);
  for (int i = 1; i <= qwq; i++) ans = (ans + 1ll * i * tmp[i] % mod * s[i] % mod * s[i]) % mod;
  printf("%d\n", ans);
  return 0;
}
```

---

## 作者：command_block (赞：46)

[题目Link](https://www.luogu.org/problem/P5298)

题意复杂,难以概括……

------------

肯定首先离散化。

题目中写着这玩意是个二叉树,那么可能是考虑左右子树间贡献什么的。

题目里要求的是这个:$\sum_{i=1}^{m}i\cdot V_i\cdot D_i^2$

直接维护这个东西肯定是布星的(无法转移),我们考虑对于每个点维护$D_{[1...n]}$

采用线段树合并来维护,正好合适$3*10^5$的范围。

对于某个叶节点,就是在$D_{?}$处是1,其他都是0;

然后,如果某个点只有一个儿子,那么直接继承整个$D$数组就好。

对于某个点$u$有两个儿子:

首先,我们设左儿子的概率数组为$DL$,相应地右儿子为$DR$

那么,对于左儿子权为$x$(是离散化之后的)的情况,要以继承到$u$的概率是:

- 最小值:$D_{i}+=DL_i*(1-p_u)\sum\limits_{i=x+1}^nDR_i$

- 最大值:$D_{i}+=DL_i*p_u\sum\limits_{i=1}^{x-1}DR_i$

由于各个叶节点权值不同,左右权相同的情况是不存在的。

总的来说是$D_i+=DL_i*\left((1-p_u)\sum\limits_{i=x+1}^nDR_i+p_u\sum\limits_{i=1}^{x-1}DR_i\right)$

对于右儿子同理。

这么看,需要对$D$维护一个前缀和和后缀和,动态维护好像很麻烦,可以边合并边算(利用区间和),用完就丢掉。

线段树合并时,如果两方都有节点,那么分下去,`pushup`解决。

如果只有一方有节点的话(假设是左方):

贡献关系式是:

$D_i=DL_i*\left((1-p_u)\sum\limits_{i=x+1}^nDR_i+p_u\sum\limits_{i=1}^{x-1}DR_i\right)$

只有一方有节点,表示这个区间内再没有右方节点了。

那么括号里面那个式子是定值,打区间乘法tag即可。

这是一道好题啊!完美的利用了线段树合并的性质!Orz出题人!

**Code:**

假如思路清晰,那么代码并不难写。

莫名其妙跑到了$rk1$?不过应该很快就会被超过去。

```cpp
#include<algorithm>
#include<cstdio>
#define MaxN 300500
#define mod 998244353
#define ll long long
using namespace std;
inline int read()
{
  register int X=0;
  register char ch=0;
  while(ch<48||ch>57)ch=getchar();
  while(ch>=48&&ch<=57)X=X*10+(ch^48),ch=getchar();
  return X;
}
ll powM(ll a,ll t=mod-2)
{
  ll ans=1;
  while(t){
  	if(t&1)ans=ans*a%mod;
  	a=a*a%mod;
  	t>>=1;
  }return ans;
}
const ll inv10=powM(10000);
int n,xx[MaxN],tot;
struct TreeNode
{int l,r,x;}b[MaxN];
struct Node
{
  int l,r;ll x,tag;
  inline void ladd(ll c)
  {tag=tag*c%mod;x=x*c%mod;}
}a[MaxN<<6];
int tn;
inline int create()
{a[++tn].tag=1;return tn;}
inline void up(int num)
{a[num].x=(a[a[num].l].x+a[a[num].r].x)%mod;}
int to;
void change(int l,int r,int &num)
{
  a[num=create()].x=1;
  if (l==r)return ;
  int mid=(l+r)>>1;
  if (to<=mid)change(l,mid,a[num].l);
  else change(mid+1,r,a[num].r);
}
inline void ladd(int num)
{
  if (a[num].tag==1)return ;
  if (a[num].l)a[a[num].l].ladd(a[num].tag);
  if (a[num].r)a[a[num].r].ladd(a[num].tag);
  a[num].tag=1;
}
long long lc,rc;
int marge(int x,int y,ll xl,ll xr,ll yl,ll yr)
{
  if (!x&&!y)return 0;
  if (x&&y){
    ladd(x);ladd(y);
    ll sav1=a[a[x].l].x,sav2=a[a[y].l].x;
    a[x].l=marge(a[x].l,a[y].l,xl,xr+a[a[x].r].x,yl,yr+a[a[y].r].x);
    a[x].r=marge(a[x].r,a[y].r,xl+sav1,xr,yl+sav2,yr);
    up(x);
  }else {
    if (!x){swap(x,y);yl=xl;yr=xr;}
    yr%=mod;yl%=mod;
    a[x].ladd((lc*yr+rc*yl)%mod);
  }return x;
}
int rt[MaxN];
void dfs(int num)
{
  if (!b[num].l){
    to=b[num].x;
    change(1,tot,rt[num]);
  }else if (!b[num].r){
    dfs(b[num].l);
    rt[num]=rt[b[num].l];
  }else {
    dfs(b[num].l);dfs(b[num].r);
    lc=mod+1-b[num].x;rc=b[num].x;
    rt[num]=marge(rt[b[num].l],rt[b[num].r],0,0,0,0);
  }
}
ll ans;
void getans(int l,int r,int num)
{
  ladd(num);
  if (l==r){
    ans=(ans+1ll*l*xx[l]%mod*a[num].x%mod*a[num].x)%mod;
    return ;
  }int mid=(l+r)>>1;
  getans(l,mid,a[num].l);
  getans(mid+1,r,a[num].r);
}
int main()
{
  n=read();
  for (int i=1,fa;i<=n;i++){
    fa=read();
    if (b[fa].l)b[fa].r=i;
    else b[fa].l=i;
  }for (int i=1;i<=n;i++){
    b[i].x=read();
    if (!b[i].l)xx[++tot]=b[i].x;
    else b[i].x=b[i].x*inv10%mod;
  }sort(xx+1,xx+tot+1);
  for (int i=1;i<=n;i++)
    if (!b[i].l)
      b[i].x=lower_bound(xx+1,xx+tot+1,b[i].x)-xx;
  dfs(1);
  getans(1,tot,rt[1]);
  printf("%lld",ans);
  return 0;
}
```

---

## 作者：TheLostWeak (赞：17)

[在博客查看](https://www.cnblogs.com/chenxiaoran666/p/Luogu5298.html)

**大致题意：** 有一棵树，给出每个叶节点的点权（互不相同），非叶节点$x$至多有两个子节点，且其点权有$p_x$的概率是子节点点权较大值，有$1-p_x$的概率是子节点点权较小值。假设根节点$1$号节点的点权有$m$种可能性，其中权值第$i$小的可能点权是$V_i$，可能性为$D_i$，求$\sum_{i=1}^mi\cdot V_i\cdot D_i^2$。

### 前言

好妙的题目，像我这种蒟蒻根本想不到线段树合并还可以这么玩。

同时，在无数个地方漏掉$PushDown$的我感觉自己真是弱到连线段树都不会了......

### 题意转化

由于题目中保证$0<p_x<1$，所以每种点权都可能被取到。

如果我们将点权排个序，那么$i$和$V_i$都是显然的，只要想个办法求出$D_i$即可。

### 推式子

首先，我们把权值离散化。

设$f_{x,i}$表示节点$x$的权值为$i$的概率，则$D_i=f_{1,i}$。

考虑如何转移。

如果$x$没有子节点，设其给定权值为$v$，那么$f_{x,i}=[i=v]$。

如果$x$只有一个子节点，设其为$son$，那么$f_{x,i}=f_{son,i}$。

如果$x$有两个子节点，分别为$lc$和$rc$。

题目告诉我们，权值是互不相同的。

则对于一个权值$i$，若其满足$f_{lc,i}>0$，就说明这个权值在左子树中。

下面便以在左子树中的权值$i$为例，讲讲$f_{x,i}$如何转移，而在右子树中是同理的。

我们知道，有$p_x$的概率，$x$的权值取较大值，则此时$i$应大于右儿子的权值，即概率为$p_x(\sum_{k=1}^{i-1}f_{rc,k})$。

同理，有$(1-p_x)$的概率，$x$的权值取较小值，则此时$i$应小于右儿子的权值，即概率为$(1-p_x)(\sum_{k=i+1}^mf_{rc,k})$。

而这个概率实际上还要乘上$f_{lc,i}$，所以：

$$f_{x,i}=f_{lc,i}\cdot(p_x(\sum_{k=1}^{i-1}f_{rc,k})+(1-p_x)(\sum_{k={i+1}}^mf_{rc,k}))$$

### 线段树合并

仔细观察上面的式子，就可以发现，$\sum_{k=1}^{i-1}f_{rc,k}$和$\sum_{k={i+1}}^mf_{rc,k}$分别是前缀和与后缀和。

现在我们需要一个数据结构，能够维护数组之间的转移，还在前缀和与后缀和的维护方面有优势，于是不难想到动态开点线段树。

而这个转移的过程，可以用线段树合并来实现。

用线段树合并有什么好处呢？

就是在线段树合并的过程中，我们可以同时维护下$f_{lc}$和$f_{rc}$的前缀和与后缀和，这样就能很方便地进行转移了。

当遇到某一个节点，在一棵树中为空，一棵树中非空，我们就可以借助维护下的前缀和与后缀和，打一个乘法标记，便可完成转移了。

具体实现详见代码。

### 代码

```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define Reg register
#define RI Reg int
#define Con const
#define CI Con int&
#define I inline
#define W while
#define N 300000
#define LN 20
#define X 998244353
#define add(x,y) (e[++ee].nxt=lnk[x],e[lnk[x]=ee].to=y)
using namespace std;
int n,ee,dc,a[N+5],dv[N+5],Rt[N+5],lnk[N+5];struct edge {int to,nxt;}e[N+5];
I int Qpow(RI x,RI y) {RI t=1;W(y) y&1&&(t=1LL*t*x%X),x=1LL*x*x%X,y>>=1;return t;}
class FastIO
{
	private:
		#define FS 100000
		#define tc() (A==B&&(B=(A=FI)+fread(FI,1,FS,stdin),A==B)?EOF:*A++)
		#define tn (x<<3)+(x<<1)
		#define D isdigit(c=tc())
		char c,*A,*B,FI[FS];
	public:
		I FastIO() {A=B=FI;}
		Tp I void read(Ty& x) {x=0;W(!D);W(x=tn+(c&15),D);}
}F;
template<int PS> class SegmentTree//动态开点线段树
{
	private:
		#define PD(x) F[x]^1&&\
		(\
			V[S[x][0]]=1LL*V[S[x][0]]*F[x]%X,F[S[x][0]]=1LL*F[S[x][0]]*F[x]%X,\
			V[S[x][1]]=1LL*V[S[x][1]]*F[x]%X,F[S[x][1]]=1LL*F[S[x][1]]*F[x]%X,F[x]=1\
		)
		int Nt,V[PS+5],F[PS+5],S[PS+5][2];
	public:
		I void Ins(int& rt,CI x,CI l=1,CI r=dc)//插入
		{
			if(rt=++Nt,V[rt]=F[rt]=1,l==r) return;int mid=l+r>>1;
			x<=mid?Ins(S[rt][0],x,l,mid):Ins(S[rt][1],x,mid+1,r);
		}
		I int Qry(CI rt,CI x,CI l=1,CI r=dc)//询问
		{
			if(l==r) return V[rt];int mid=l+r>>1;PD(rt);
			return x<=mid?Qry(S[rt][0],x,l,mid):Qry(S[rt][1],x,mid+1,r);
		}
		I int Merge(CI x,CI y,CI p,CI l=1,CI r=dc,CI lx=0,CI rx=0,CI ly=0,CI ry=0)//线段树合并
		{
			if(!x&&!y) return 0;RI rt=++Nt;//皆为空直接返回
			if(!y) return PD(x),F[rt]=(1LL*p*ly+1LL*(1-p+X)*ry)%X,//修改，注意修改前下传标记
				V[rt]=1LL*F[rt]*V[x]%X,S[rt][0]=S[x][0],S[rt][1]=S[x][1],rt;//拷贝信息
			if(!x) return PD(y),F[rt]=(1LL*p*lx+1LL*(1-p+X)*rx)%X,//修改，注意修改前下传标记
				V[rt]=1LL*F[rt]*V[y]%X,S[rt][0]=S[y][0],S[rt][1]=S[y][1],rt;//拷贝信息
			int mid=l+r>>1;PD(x),PD(y),F[rt]=1,//先下传标记
			S[rt][0]=Merge(S[x][0],S[y][0],p,l,mid,lx,(rx+V[S[x][1]])%X,ly,(ry+V[S[y][1]])%X),//递归处理左子树
			S[rt][1]=Merge(S[x][1],S[y][1],p,mid+1,r,(lx+V[S[x][0]])%X,rx,(ly+V[S[y][0]])%X,ry);//递归处理右子树
			return V[rt]=(V[S[rt][0]]+V[S[rt][1]])%X,rt;//注意上传信息
		}
};SegmentTree<N*LN<<1> S;
I void dfs(CI x)
{
	if(!lnk[x]) return S.Ins(Rt[x],lower_bound(dv+1,dv+dc+1,a[x])-dv);//处理叶节点，注意离散化
	for(RI i=lnk[x];i;i=e[i].nxt) dfs(e[i].to),//先处理子节点
		Rt[x]=Rt[x]?S.Merge(Rt[x],Rt[e[i].to],a[x]):Rt[e[i].to];//合并子节点
}
int main()
{
	RI i,x,ans;for(F.read(n),i=1;i<=n;++i) F.read(x),x&&add(x,i);
	for(i=1;i<=n;++i) F.read(a[i]),lnk[i]?(a[i]=1LL*a[i]*Qpow(10000,X-2)%X):(dv[++dc]=a[i]);
	sort(dv+1,dv+dc+1),dfs(1);//排序
	for(ans=0,i=1;i<=dc;++i) x=S.Qry(Rt[1],i),ans=(1LL*i*dv[i]%X*x%X*x+ans)%X;//统计答案
	return printf("%d",ans),0;
}
```

---

## 作者：mrsrz (赞：14)

由于概率不为0且不为1，所以所有点权都可能取到。

设$f_i,g_i$分别表示当前节点的左儿子、右儿子点权为$i$的概率。

若$i$在左儿子中，则当前节点取到$i$的概率为：

$$f_i\times(p\times(\sum_{j=1}^i g_j)+(1-p)\times(\sum_{j=i+1}^m g_j))$$

右儿子同理。

考虑线段树合并，合并到叶子节点的时候显然只会有一个点有值。

边向下传递，边维护左儿子的前缀、后缀，右儿子的前缀、后缀概率和，然后按照上面的方法类似转移即可（此时可能转移到的是一个区间的值）。

线段树上打乘法标记即可。

时间复杂度$O(n\log n)$。

由于合并时需要动态开点（否则前缀、后缀和就会出现问题），所以空间复杂度也是$O(n\log n)$。

## Code：
```cpp
#include<iostream>
#include<algorithm>
#include<vector>
typedef long long LL;
const int md=998244353,N=3e5+5,iv1e4=796898467;
struct edge{
    int to,nxt;
}e[N];
int n,fa[N],head[N],cnt,p[N],rt[N];
std::vector<int>vec;
int ls[N<<6],rs[N<<6],g[N<<6],tag[N<<6],nd,ans;
inline void upd(int&a){a+=a>>31&md;}
inline int mod(int a){return(a>>31&md)+a;}
void pushdown(int o){
    if(tag[o]!=1){
        if(ls[o])
            tag[ls[o]]=(LL)tag[ls[o]]*tag[o]%md,g[ls[o]]=(LL)g[ls[o]]*tag[o]%md;
        if(rs[o])
            tag[rs[o]]=(LL)tag[rs[o]]*tag[o]%md,g[rs[o]]=(LL)g[rs[o]]*tag[o]%md;
        tag[o]=1;
    }
}
void add(int&o,int l,int r,const int&pos){
    if(!o)o=++nd,tag[o]=1;
    upd(g[o]+=1-md);
    if(l<r){
        const int mid=l+r>>1;
        if(pos<=mid)add(ls[o],l,mid,pos);else add(rs[o],mid+1,r,pos);
    }
}
int merge(int ld,int rd,int pl,int pr,int sl,int sr,const int&P){
    if(!ld&&!rd)return 0;
    pushdown(ld),pushdown(rd);
    int o=++nd;tag[o]=1;
    if(!ld){
        g[o]=((LL)P*pl+(md+1LL-P)*sl)%md*g[rd]%md;
        tag[o]=((LL)P*pl+(md+1LL-P)*sl)%md*tag[rd]%md;
        ls[o]=ls[rd],rs[o]=rs[rd];
        return o;
    }
    if(!rd){
        g[o]=((LL)P*pr+(md+1LL-P)*sr)%md*g[ld]%md;
        tag[o]=((LL)P*pr+(md+1LL-P)*sr)%md*tag[ld]%md;
        ls[o]=ls[ld],rs[o]=rs[ld];
        return o;
    }
    ls[o]=merge(ls[ld],ls[rd],pl,pr,mod(sl+g[rs[ld]]-md),mod(sr+g[rs[rd]]-md),P);
    rs[o]=merge(rs[ld],rs[rd],mod(pl+g[ls[ld]]-md),mod(pr+g[ls[rd]]-md),sl,sr,P);
    upd(g[o]=g[ls[o]]+g[rs[o]]-md);
    return o;
}
void dfs(int now){
    if(head[now])
        for(int i=head[now];i;i=e[i].nxt){
            dfs(e[i].to);
            if(!rt[now])rt[now]=rt[e[i].to];else
                rt[now]=merge(rt[now],rt[e[i].to],0,0,0,0,p[now]);
        }
    else
        add(rt[now],1,n,p[now]);
}
void getans(int o,int l,int r){
    if(!o)return;
    if(l==r){
        ans=(ans+(LL)l*vec[l]%md*g[o]%md*g[o])%md;
        return;
    }
    pushdown(o);
    const int mid=l+r>>1;
    getans(ls[o],l,mid),getans(rs[o],mid+1,r);
}
int main(){
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin>>n;
    for(int i=1;i<=n;++i)
        std::cin>>fa[i],e[++cnt]=(edge){i,head[fa[i]]},head[fa[i]]=cnt;
    for(int i=1;i<=n;++i){
        std::cin>>p[i];
        if(head[i])p[i]=(LL)p[i]*iv1e4%md;else vec.push_back(p[i]);
    }
    vec.push_back(0);
    std::sort(vec.begin(),vec.end());
    vec.erase(std::unique(vec.begin(),vec.end()),vec.end());
    for(int i=1;i<=n;++i)if(!head[i])p[i]=std::lower_bound(vec.begin(),vec.end(),p[i])-vec.begin();
    dfs(1);
    getans(rt[1],1,n);
    std::cout<<ans<<std::endl;
    return 0;
}

```

---

## 作者：ppip (赞：13)

考虑求出每个点作为最终答案的概率。

设当前考虑的点权值为 $x$，我们将 $\le x$ 的叶子权值改为 $0$，$>x$ 的权值改为 $1$，然后可以通过简单的树形 DP 求出根节点为 $0$，也就是权值 $\le x$ 的概率。全部求出来之后做一次差分即可得到每个点的权值。

将叶子按照权值从小到大排序，每次只需要将一个叶子权值从 $0$ 改成 $1$，并查询 DP 值，动态 DP 维护即可。复杂度 $O(n\log n)$。注意本题无需矩阵，可以直接维护一次函数。

[动态 DP](/problem/P4719)

[动态 DP 加强版](/problem/P4751)

[我使用的全局平衡二叉树实现](https://return20071007.blog.uoj.ac/blog/8981)

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int Spp{1<<20};
char buf[Spp],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Spp,stdin),p1==p2)?EOF:*p1++)
template <typename T>
void read(T &x) {
	char c;int f{1};
	do x=(c=getchar())^48;
	while (!isdigit(c)&&c!='-');
	if (x==29) f=-1,x=0;
	while (isdigit(c=getchar()))
		x=(x<<3)+(x<<1)+(c^48);
	x*=f;
}
template <typename T,typename ...Args>
void read(T& x,Args&... args) {read(x);read(args...);}
using u32=unsigned;
using u64=unsigned long long;
constexpr u32 N(3e5),b6e0{998244353};
struct matrix {
	u64 x,y;
	matrix(u64 a=1,u64 b=0):x{a},y{b} {}
	friend matrix operator+(matrix a,matrix b) {
		return {a.x*b.x%b6e0,(a.y*b.x+b.y)%b6e0};
	}
} tr[N+5],p[N+5];
int tf[N+5],lb[N+5],fa[N+5],d[N+5];
int son[N+5],sz[N+5];
int st[N+5],tp,sum[N+5];
u32 a[N+5];
vector<int> e[N+5];
matrix mv(matrix t,int u) {
	return {((a[u]-1)*(b6e0+t.y-1)+t.y*a[u])%b6e0,t.y*(b6e0+1-a[u])%b6e0};
}
void pushup(int x) {
	tr[x]=p[x];
	for (int y{fa[x]};tf[y]==x;y=lb[y]) tr[x]=tr[x]+tr[y];
}
void init(int u) {
	d[u]=d[fa[u]]+1;
	sz[u]=1;
	for (auto v:e[u]) {
		init(v);
		sz[u]+=sz[v];
		if (sz[v]>sz[son[u]]) son[u]=v;
	}
}
int build(int l,int r) {
	int u{st[r--]};
	lb[u]=st[l-1];
	if (l<=r) {
		int p{upper_bound(sum+l,sum+r+1,sum[l-1]+sum[r]>>1)-sum};
		tf[build(l,p)]=u;
		if (p<r) tf[build(p+1,r)]=u;
	}
	pushup(u);
	return u;
}
int rt;
void hld(int u,int top) {
	st[++tp]=u;sum[tp]=sum[tp-1]+sz[u];
	if (son[u]) {
		sum[tp]-=sz[son[u]];
		for (auto v:e[u])
			if (v!=fa[u]&&v!=son[u]) hld(v,v);
		hld(son[u],top);
	} else {
		p[u]={0,0};
		build(tp-d[u]+d[top],tp);
		if (top==1) rt=u;
		p[lb[u]]=mv(tr[u],lb[u]);
	}
	--tp;
}
void modify(int u) {
	p[u]={0,1};
	while (u) {
		pushup(u);
		if (!tf[u]) p[lb[u]]=mv(tr[u],lb[u]),u=lb[u];
		else u=tf[u];
	}
}
int c[N+5];
signed main() {
	int n;read(n);
	for (int i{1};i<=n;++i) {
		read(fa[i]);
		e[fa[i]].push_back(i);
	}
	for (int i{1};i<=n;++i) {
		read(a[i]);
		if (e[i].size()) a[i]=a[i]*796898467uLL%b6e0; // 1e4 * 796898467 = 1
	}
	init(1);hld(1,1);
	iota(c+1,c+1+n,1);
	sort(c+1,c+1+n,[](int x,int y){return a[x]<a[y];});
	u64 ans{0},lst{0},tot{0};
	for (int i{1};i<=n;++i) {
		int u{c[i]};
		if (e[u].size()) continue;
		++tot;
		modify(u);
		u64 pro{(tr[rt].y+b6e0-lst)%b6e0};
		lst=tr[rt].y;
		ans=(ans+pro*pro%b6e0*a[u]%b6e0*tot)%b6e0;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：lhm_ (赞：11)

首先发现每个叶子节点的权值都有可能成为最终根节点的权值，观察题目中给出的式子：

$$
	\sum_{i=1}^m i V_i D_i^2
$$

发现只要算出每个权值被根节点取到的概率 $D_i$，然后就能计算答案。

设 $f_{x,i}$ 为节点 $x$ 取到第 $i$ 小权值的概率，根据是从左儿子还是从右儿子取到的权值来进行分类讨论：

$$
f_{x,i} = f_{ls,i}(p_x \sum_{j=1}^{i-1}f_{rs,j}+(1-p_x) \sum_{j=i+1}^m f_{rs,j}) + f_{rs,i}(p_x \sum_{j=1}^{i-1}f_{ls,j}+(1-p_x) \sum_{j=i+1}^m f_{ls,j})
$$

直接进行转移的话，时间和空间都无法接受，由本题为树形 $DP$ 和转移方程的特点得，可以通过整体 $DP$ 来优化。

用动态开点线段树来维护第二维，通过线段树合并实现从左右儿子转移。当一个节点没有儿子时就直接赋初值，只有一个儿子就直接转移。线段树合并时记录前缀和和后缀和，来计算左右区间互相的贡献，线段树上区间乘，打标记即可。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 600010
#define maxm 10000010
#define p 998244353
#define inv 796898467
#define mid ((l+r)>>1)
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,tot,cnt;
ll ans;
int ch[maxn][2],rt[maxn],ls[maxm],rs[maxm];
ll val[maxn],s[maxn],d[maxn],sum[maxm],tag[maxm];
void pushtag(int x,ll v)
{
    sum[x]=sum[x]*v%p,tag[x]=tag[x]*v%p;
}
void pushdown(int x)
{
    if(tag[x]==1) return;
    pushtag(ls[x],tag[x]),pushtag(rs[x],tag[x]),tag[x]=1;
}
void insert(int l,int r,int pos,int &cur)
{
    if(!cur) cur=++tot,tag[cur]=1;
    sum[cur]++;
    if(l==r) return;
    if(pos<=mid) insert(l,mid,pos,ls[cur]);
    else insert(mid+1,r,pos,rs[cur]);
}
int merge(int x,int y,ll lx,ll rx,ll ly,ll ry,ll v)
{
    if(!x&&!y) return 0;
    pushdown(x),pushdown(y);
    if(x&&!y)
    {
        pushtag(x,(v*ly%p+(1-v+p)*ry%p)%p);
        return x;
    }
    if(!x&&y)
    {
        pushtag(y,(v*lx%p+(1-v+p)*rx%p)%p);
        return y;
    }
    ll px=sum[ls[x]],sx=sum[rs[x]],py=sum[ls[y]],sy=sum[rs[y]];
    ls[x]=merge(ls[x],ls[y],lx,(rx+sx)%p,ly,(ry+sy)%p,v);
    rs[x]=merge(rs[x],rs[y],(lx+px)%p,rx,(ly+py)%p,ry,v);
    sum[x]=(sum[ls[x]]+sum[rs[x]])%p;
    return x;
}
void solve(int x)
{
    if(!ch[x][0])
    {
        insert(1,cnt,val[x],rt[x]);
        return;
    }
    if(!ch[x][1])
    {
        solve(ch[x][0]),rt[x]=rt[ch[x][0]];
        return;
    }
    solve(ch[x][0]),solve(ch[x][1]);
    rt[x]=merge(rt[ch[x][0]],rt[ch[x][1]],0,0,0,0,val[x]);
}
void dfs(int l,int r,int cur)
{
    if(l==r)
    {
        d[l]=sum[cur];
        return;
    }
    pushdown(cur),dfs(l,mid,ls[cur]),dfs(mid+1,r,rs[cur]);
}
int main()
{
    read(n);
    for(int i=1;i<=n;++i)
    {
        int fa;
        read(fa);
        if(ch[fa][0]) ch[fa][1]=i;
        else ch[fa][0]=i;
    }
    for(int i=1;i<=n;++i)
    {
        read(val[i]);
        if(ch[i][0]) val[i]=val[i]*inv%p;
        else s[++cnt]=val[i];
    }
    sort(s+1,s+cnt+1);
    for(int i=1;i<=n;++i)
        if(!ch[i][0])
            val[i]=lower_bound(s+1,s+cnt+1,val[i])-s;
    solve(1),dfs(1,cnt,rt[1]);
    for(int i=1;i<=cnt;++i)
        ans=(ans+i*s[i]%p*d[i]%p*d[i]%p)%p;
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Leap_Frog (赞：9)

### P.S.
高质量好题。  
### Discription.
给你一颗**二叉**树，每个叶子节点有一个权值 $V_i$，每个非叶子节点有一个概率 $P_i$。  
现在对于每一个叶子节点，它有 $P_i$ 的概率取它**儿子**的最小值，有 $1-P_i$ 的概率取最大值。  
现在求根节点的取所有值的概率，并把它们按照题目中的 Hash 函数 Hash 起来输出 Hash 值。  
### Solution.
题目重点或容易读错的（至少笔者读错了）的地方已加粗。  

首先，我们考虑朴素递推，假设 $F_{x,i}$ 为第 $x$ 点取权值 $i$ 的概率。  
那么因为它是棵二叉树，所以我们直接分类讨论。  
#### Case 1.
如果它没有孩子。  
很显然，那么只有权值为 $V_x$ 的地方概率为 $1$，其他地方概率为 $0$。  
#### Case 2.
如果它只有一个孩子。  
也很显然，那么它的权值肯定是它孩子的权值，直接把孩子的信息复制过来就好了。  
#### Case 3.
如果它有两个孩子，假设两个孩子是 $a$ 和 $b$。  
我们考虑分类：当前这个权值是从那个孩子转移过来的以及是被当作最大值还是最小值转移过来的。  
1. From a & Max : $(1-P_x)\times F_{a,i}\times\sum_{j=i+1}^{+\infty}F_{b,j}$
2. From b & Max : $(1-P_x)\times F_{b,i}\times\sum_{j=i+1}^{+\infty}F_{a,j}$
3. From a & Min : $P\times F_{a,i}\times\sum_{j=-\infty}^{i-1}F_{b,j}$
4. From b & Min : $P\times F_{b,i}\times\sum_{j=-\infty}^{i-1}F_{a,j}$

别看那里有一个 $\infty$，但是由于这题的操作只会取最小值最大值，所以最终的 $i$ 肯定只会在不超过 $\max_{i=1}^n V_i$ 的范围内有作用。  
***
但是，暴力转移显然是 $O(n\times \max_{i=1}^nV_i)$ 的，离散化一下后还是 $O(n^2)$ 的。  
因为这个方法的瓶颈是在状态数，状态数量就是 $O(n^2)$ 的了。  
那么我们考虑怎么优化状态数，显然这里有很多无用的状态（空状态。  

遇到分布地无规律的空状态，我们肯定能想到一个优良的做法——**线段树合并**。  
~~于是这题就做完了，完结撒花~~

在线段树合并中，对于每个区间，我们都需要考虑分别递归合并左区间和右区间。  
此时，我们就需要按照上面 4 类分类讨论分别计算左区间对右区间、右区间对左区间的贡献。  
然后我们会惊奇地发现，贡献是以倍数形式增加的，于是我们的线段树需要维护一个区间乘积操作。  
然后这题就真做完了，注意给 $V_i$ 离散化一下，毕竟值域这么大。  
~~不过不离散化也能做？毕竟是动态开点线段树，只是复杂度从 logn 变成了 log值域了qwq~~
### Coding.
在这里给出笔者认为最重要的线段树合并操作的代码，其他就不给了（
```cpp
inline int Mrg(int x,int y,int a,int b,int p)
{
	if(!x) return allc(y,b),y;else if(!y) return allc(x,a),x;else down(x),down(y);
	int sxl=t[t[x].ls].sm,sxr=t[t[x].rs].sm,syl=t[t[y].ls].sm,syr=t[t[y].rs].sm,p1=p,p2=(1+P-p)%P;
	t[x].ls=Mrg(t[x].ls,t[y].ls,(a+1ll*p2*syr%P)%P,(b+1ll*p2*sxr%P)%P,p);
	t[x].rs=Mrg(t[x].rs,t[y].rs,(a+1ll*p1*syl%P)%P,(b+1ll*p1*sxl%P)%P,p);
	return up(x),x;
}
```

---

## 作者：TEoS (赞：6)

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/13289222.html)

------------

根据题意，若一个点有子节点，则给出权值；否则可以从子节点转移得来。

若没有子节点，则直接给出权值；

若只有一个子节点，则概率情况与该子节点完全相同；

若有两个子节点，则需要从两个子节点中进行转移。

如何转移？显然，若权值 $i$ 在左子树，要取到它，需要在 $p_i$ 的概率中左子树较大，在 $(1-p_i)$ 的概率中左子树较小，右子树同理。因为当权值 $i$ 在左子树时右子树取到它的概率为 $0$ ，因此可以直接将两个子树的转移式相加合并，没有影响。即：

设节点 $x$ 取到权值 $i$ 的概率为 $f_{x,i}$ ，节点数为 $n$ ，则有：

$$f_{x,i}=f_{lson(x),i}*(p_x*\sum_{j=1}^{i-1} f_{rson(x),j}+(1-p_x)*\sum_{j=i+1}^{n} f_
{rson(x),j})+f_{rson(x),i}*(p_x*\sum_{j=1}^{i-1} f_{lson(x),j}+(1-p_x)*\sum_{j=i+1}^{n} f_
{lson(x),j})$$

如何求值？通过观察可以发现，这个式子同时需要左儿子的值、右儿子的值以及其前缀、后缀和，可以想到用线段树合并进行求值。

如何实现？在线段树合并的同时维护前、后缀和，打上乘法标记即可。记得离散化。

本题需要用到分数取模：$\frac{a}{b}\bmod k=\frac{a}{b}*b^{k-1}\bmod k=a*b^{k-2}\bmod k$ 。

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=3e5+100;
const int P=998244353;
int qpow(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1)
			ans=1LL*ans*x%P;
		x=1LL*x*x%P,y>>=1;
	}
	return ans;
}//快速幂
const int D=qpow(10000,P-2);
struct Seg
{
	int lson,rson,sum,tag;
	#define lson(i) t[i].lson
	#define rson(i) t[i].rson
	#define sum(i) t[i].sum
	#define tag(i) t[i].tag//乘法标记
}t[N<<5];
int n,cnt,h,ans;
int v[N],r[N],a[N],cnts[N],anss[N],s[N][2];
int newp()
{
	int p=++cnt;
	tag(p)=1;
	return p;
}//新建节点
void update(int p,int val)
{
	sum(p)=1LL*sum(p)*val%P;
	tag(p)=1LL*tag(p)*val%P;
}//更新
void pushdown(int p)
{
	if(tag(p)>1)
		update(lson(p),tag(p)),update(rson(p),tag(p)),tag(p)=1;
}//下传标记
void change(int &p,int l,int r,int k,int val)
{
	if(!p)
		p=newp();
	if(l==r)
	{
		sum(p)=val;
		return ;
	}
	pushdown(p);
	int mid=l+r>>1;
	if(k<=mid)
		change(lson(p),l,mid,k,val);
	else
		change(rson(p),mid+1,r,k,val);
	sum(p)=sum(lson(p))+sum(rson(p))%P;
}//修改
void ask(int p,int l,int r)
{
	if(!p)
		return ;
	if(l==r)
	{
		anss[l]=sum(p);
		return ;
	}
	pushdown(p);
	int mid=l+r>>1;
	ask(lson(p),l,mid),ask(rson(p),mid+1,r);
}//输出答案到对应数组
int merge(int x,int y,int l,int r,int xtag,int ytag,int val)
{
	if(!x && !y)
		return 0;
	if(!x)
	{
		update(y,ytag);
		return y;
	}
	if(!y)
	{
		update(x,xtag);
		return x;
	}
	pushdown(x),pushdown(y);//下传标记
	int mid=l+r>>1,lx=sum(lson(x)),ly=sum(lson(y)),rx=sum(rson(x)),ry=sum(rson(y));//先存值，否则之后会被改动
	lson(x)=merge(lson(x),lson(y),l,mid,(xtag+1LL*ry*(1-val+P)%P)%P,(ytag+1LL*rx*(1-val+P)%P)%P,val);
	rson(x)=merge(rson(x),rson(y),mid+1,r,(xtag+1LL*ly*val%P)%P,(ytag+1LL*lx*val%P)%P,val);
	sum(x)=(sum(lson(x))+sum(rson(x)))%P;
	return x;
}
void pre()
{
	sort(a+1,a+h+1);
	for(int i=1;i<=n;i++)
		if(!cnts[i])
			v[i]=lower_bound(a+1,a+h+1,v[i])-a;//权值离散化
		else
			v[i]=1LL*v[i]*D%P;//存概率，分数取模
}//预处理权值
void solve(int x)
{
	if(!cnts[x])
	{
		change(r[x],1,h,v[x],1);
		return ;
	}//没有子节点，插入权值
	if(cnts[x]==1)
	{
		solve(s[x][0]);
		r[x]=r[s[x][0]];
		return ;
	}//只有一个子节点
	solve(s[x][0]),solve(s[x][1]);
	r[x]=merge(r[s[x][0]],r[s[x][1]],1,h,0,0,v[x]);//有两个子节点
}
int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		if(x)
			s[x][cnts[x]++]=i;
	}
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&v[i]);
		if(!cnts[i])
			a[++h]=v[i];
	}
	pre(),solve(1),ask(r[1],1,h);
	for(int i=1;i<=h;i++)
		ans=(ans+1LL*i*a[i]%P*anss[i]%P*anss[i])%P;//计算答案
	printf("%d",ans);
	return 0;
}
```



---

## 作者：Sol1 (赞：6)

线段树合并。

这类线段树合并优化树形 DP 的题一般都是先考虑一个 $O(n^2)$ 的 DP。

不难发现对于每一个节点，其子树内所有的权值都可以取到。

故设 $f_{i,j}$ 为 $i$ 的权值取到所有叶子中第 $j$ 小的权值。

设 $l$ 为 $u$ 的左子，$r$ 为 $u$ 的右子，则有如下转移：

$$f_{u,i}=p_u\left(f_{l,i}\cdot\sum_{j=1}^{i-1}f_{r,j}+f_{r,i}\cdot\sum_{j=1}^{i-1}f_{l,j}\right)+(1-p_u)\left(f_{l,i}\cdot\sum_{j=i+1}^{n}f_{r,j}+f_{r,i}\cdot\sum_{j=i+1}^{n}f_{l,j}\right)$$

初始状态就是叶子取到自己的概率为 $1$。

前缀和优化可以做到 $O(n^2)$。

由于叶子上只有 $1$ 个状态，所以考虑线段树合并。

在合并到空节点的时候，可以知道这一段的所有状态都是 $0$，所以就直接在 $\operatorname{merge}(l,r)$ 过程中保存 $[1,l-1]$ 和 $[r+1,n]$ 的两个和值就可以了。

于是这题就做完了~

时空复杂度均为 $O(n\log n)$。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

const int N = 300005;
const long long mod = 998244353;
struct Edge {
	int to, nxt;
	Edge() {
		nxt = -1;
	}
};
int n, hd[N], pnt, bcnt, scnt[N];
long long p[N], b[N];
Edge e[N << 1];

inline long long Add(long long x, long long y) {return (x + y >= mod ? x + y - mod : x + y);}
inline long long Subt(long long x, long long y) {return (x < y ? x - y + mod : x - y);}

inline long long Power(long long x, long long y) {
	long long ans = 1;
	while (y) {
		if (y & 1) ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}

#define Sum(p) (p ? p->sum : 0)
struct Node {
	long long sum, mul;
	Node *l, *r;
	Node() {
		l = r = NULL;
		sum = 0;
		mul = 1;
	}
	inline void Update() {
		sum = Add(Sum(l), Sum(r));
	}
};
Node nd[N * 40];
int top;
struct Segtree {
	Node *_root[N];
	inline void Pushdown(Node *p, int pl, int pr) {
		if (p->l) {
			p->l->sum = p->l->sum * p->mul % mod;
			p->l->mul = p->l->mul * p->mul % mod;
		}
		if (p->r) {
			p->r->sum = p->r->sum * p->mul % mod;
			p->r->mul = p->r->mul * p->mul % mod;
		}
		p->mul = 1;
	}
	inline void Modify(Node *&p, int pl, int pr, int idx, int v) {
		if (!p) p = &nd[++top];
		if (pl == idx && pr == idx) {
			p->sum = v;
			return;
		}
		Pushdown(p, pl, pr);
		int mid = pl + pr >> 1;
		if (idx <= mid) Modify(p->l, pl, mid, idx, v);
		else Modify(p->r, mid + 1, pr, idx, v);
		p->Update();
	}
	inline long long Query(Node *p, int pl, int pr, int l, int r) {
		if (!p) return 0;
		if (pl == l && pr == r) return Sum(p);
		Pushdown(p, pl, pr);
		int mid = pl + pr >> 1;
		if (mid >= r) return Query(p->l, pl, mid, l, r);
		else if (mid + 1 <= l) return Query(p->r, mid + 1, pr, l, r);
		else return Add(Query(p->l, pl, mid, l, mid), Query(p->r, mid + 1, pr, mid + 1, r));
	}
	inline Node* Merge(Node *p1, Node *p2, int pl, int pr, long long pu, long long ps1, long long ss1, long long ps2, long long ss2) {
		long long lmul = Add(pu * ps2 % mod, Subt(1, pu) * ss2 % mod);
		long long rmul = Add(pu * ps1 % mod, Subt(1, pu) * ss1 % mod);
		if (!p1 && !p2) return NULL;
		if (!p2) {
			//printf("p1 %d %d %lld\n", pl, pr, lmul);
			p1->mul = p1->mul * lmul % mod;
			p1->sum = p1->sum * lmul % mod;
			return p1;
		}
		if (!p1) {
			//printf("p2 %d %d %lld\n", pl, pr, rmul);
			p2->mul = p2->mul * rmul % mod;
			p2->sum = p2->sum * rmul % mod;
			return p2;
		}
		Pushdown(p1, pl, pr); Pushdown(p2, pl, pr);
		int mid = pl + pr >> 1;
		long long s1l = Sum(p1->l), s1r = Sum(p1->r), s2l = Sum(p2->l), s2r = Sum(p2->r);
		p1->l = Merge(p1->l, p2->l, pl, mid, pu, ps1, Add(ss1, s1r), ps2, Add(ss2, s2r));
		p1->r = Merge(p1->r, p2->r, mid + 1, pr, pu, Add(ps1, s1l), ss1, Add(ps2, s2l), ss2);
		p1->Update();
		return p1;
	}
};
Segtree sgt;

inline void AddEdge(int u, int v) {
	e[++pnt].to = v;
	e[pnt].nxt = hd[u];
	hd[u] = pnt;
	scnt[u]++;
}

inline void Read() {
	n = qread();
	for (int i = 1;i <= n;i++) {
		int fa = qread();
		AddEdge(fa, i);
	}
	long long inv1e4 = Power(10000, mod - 2);
	for (int i = 1;i <= n;i++) {
		int x = qread();
		if (!~hd[i]) p[i] = b[++bcnt] = x;
		else p[i] = x * inv1e4 % mod;
	}
}

inline void Prefix() {
	sort(b + 1, b + bcnt + 1);
	bcnt = unique(b + 1, b + bcnt + 1) - b - 1;
	for (int i = 1;i <= n;i++) {
		if (!~hd[i]) p[i] = lower_bound(b + 1, b + bcnt + 1, p[i]) - b;
	}
}

inline void Dfs(int u) {
	if (!~hd[u]) {
		sgt.Modify(sgt._root[u], 1, bcnt, p[u], 1);
		//dp[u][p[u]] = 1;
		return;
	}
	if (scnt[u] == 1) {
		Dfs(e[hd[u]].to);
		//memcpy(dp[e[hd[u]].to], dp[u], sizeof(dp[u]));
		sgt._root[u] = sgt._root[e[hd[u]].to];
		return;
	}
	int ls = e[hd[u]].to;
	int rs = e[e[hd[u]].nxt].to;
	Dfs(ls);
	Dfs(rs);
	sgt._root[u] = sgt._root[ls];
	//sgt._root[u]->mul = sgt._root[u]->mul * p[u] % mod;
	//sgt._root[rs]->mul = sgt._root[rs]->mul * Subt(1, p[u]) % mod;
	sgt._root[u] = sgt.Merge(sgt._root[u], sgt._root[rs], 1, bcnt, p[u], 0, 0, 0, 0);
}

int main() {
	memset(hd, -1, sizeof(hd));
	Read();
	Prefix();
	Dfs(1);
	long long ans = 0;
	for (int i = 1;i <= bcnt;i++) {
		long long val = sgt.Query(sgt._root[1], 1, bcnt, i, i);
		//printf("%lld ", val);
		ans = (ans + 1ll * i * b[i] % mod * val % mod * val % mod) % mod;
	}
	//puts("");
	printf("%lld", ans);
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}

```

---

## 作者：Adove (赞：3)

由于一个点最多有两个儿子

所以我们分类讨论，用权值线段树合并得到每个权值的概率；

〇没有儿子：权值插入线段树，return；

①只有一个儿子：直接继承儿子的所有概率

②有两个儿子：

```cpp

某个儿子的某个权值出现的概率

=P[作为最大值出现]+P[作为最小值出现]

=P[该儿子权值是ta]*P[取了最大值]*P[另一儿子权值比ta小]

+P[该儿子权值是ta]*P[取了最小值]*P[另一儿子权值比ta大]
```

递归合并到单一节点时打乘法标记就好了

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=3e5+5;
const int MOD=998244353;

int n,np,ct,cnt;
long long sum;
int h[MAXN],p[MAXN],deg[MAXN],so[2][MAXN];
bool nlf[MAXN];
int rt[MAXN],sn[2][MAXN<<5],siz[MAXN<<5],tag[MAXN<<5];
struct rpg{
	int li,nx;
}a[MAXN];

int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||'9'<ch) ch=getchar();
	while('0'<=ch&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x;
}

void add(int ls,int nx){a[++np]=(rpg){h[ls],nx};h[ls]=np;}
int Fpw(int a,int b)
{
	int x=1;
	while(b){
		if(b&1) x=1ll*x*a%MOD;
		b>>=1;a=1ll*a*a%MOD;
	}return x;
}

void ins(int &k,int l,int r,int v)
{
	if(!k) k=++ct;siz[k]=tag[k]=1;
	if(l==r) return;
	int mid=l+r>>1;
	if(v<=mid) ins(sn[0][k],l,mid,v);
	else ins(sn[1][k],mid+1,r,v);
}

void pushdown(int x)
{
	if(tag[x]==1) return;
	if(sn[0][x]){
		tag[sn[0][x]]=1ll*tag[sn[0][x]]*tag[x]%MOD;
		siz[sn[0][x]]=1ll*siz[sn[0][x]]*tag[x]%MOD;
	}if(sn[1][x]){
		tag[sn[1][x]]=1ll*tag[sn[1][x]]*tag[x]%MOD;
		siz[sn[1][x]]=1ll*siz[sn[1][x]]*tag[x]%MOD;
	}tag[x]=1;
	return;
}

int un(int x,int y,int p,int srx,int sry)
{
	if(!x||!y){
		if(x){
			int v=(1ll*(1-sry+MOD)*p+1ll*sry*(1-p+MOD))%MOD;
			tag[x]=1ll*tag[x]*v%MOD;
			siz[x]=1ll*siz[x]*v%MOD;
			return x;
		}if(y){
			int v=(1ll*(1-srx+MOD)*p+1ll*srx*(1-p+MOD))%MOD;
			tag[y]=1ll*tag[y]*v%MOD;
			siz[y]=1ll*siz[y]*v%MOD;
			return y;
		}return 0;
	}pushdown(x);pushdown(y);
	int tp1=siz[sn[1][x]],tp2=siz[sn[1][y]];
	sn[0][x]=un(sn[0][x],sn[0][y],p,(srx+tp1)%MOD,(sry+tp2)%MOD);
	sn[1][x]=un(sn[1][x],sn[1][y],p,srx,sry);
	siz[x]=siz[sn[0][x]]+siz[sn[1][x]];siz[x]%=MOD;
	return x;
}

void dfs(int x)
{
	if(!nlf[x]){ins(rt[x],1,1e9,p[x]);return;}
	if(so[0][x]) dfs(so[0][x]);
	if(so[1][x]) dfs(so[1][x]);
	if(deg[x]==1) rt[x]=rt[so[0][x]];
	else rt[x]=un(rt[so[0][x]],rt[so[1][x]],p[x],0,0);
}

void ddfs(int k,int l,int r)
{
	pushdown(k);
	if(l==r){
		++cnt;
		sum+=1ll*siz[k]*siz[k]%MOD*l%MOD*cnt%MOD;
		return;
	}int mid=l+r>>1;
	if(sn[0][k]) ddfs(sn[0][k],l,mid);
	if(sn[1][k]) ddfs(sn[1][k],mid+1,r);
	return;
}

int main()
{
	n=read();int inv=Fpw(10000,MOD-2);
	for(int i=1;i<=n;++i){
		int f=read();
		if(i>1) add(f,i),nlf[f]=1,so[deg[f]++][f]=i;
	}for(int i=1;i<=n;++i){
		p[i]=read();
		if(nlf[i]) p[i]=1ll*p[i]*inv%MOD;
	}dfs(1);
	ddfs(rt[1],1,1e9);
	printf("%lld\n",sum%MOD);
	return 0;
}
```

---

## 作者：徐致远 (赞：1)


[本蒟蒻的Blog](https://www.chnxuzhiyuan.cn/2019/12/19/%E3%80%8CPKUWC2018%E3%80%8D%E9%A2%98%E8%A7%A3-Solution/)

### 题解

答案的表达式看上去极其诡异，但是观察过后，不难发现，只要求出每种权值出现的概率，问题就迎刃而解了（废话）。

首先需要抓住题目中保证的两个性质，一个是权值互不相同，另一个是有儿子的节点最多只有两个儿子。

设第$i$个节点出现权值$j$的概率为$g_{i,j}$，那么由于权值互不相同，左右儿子中最多只有一个节点可能出现权值$j$。

设左儿子的编号为$L$，右儿子为$R$，如果左儿子可能出现权值$j$，那么就有：
$$
g_{i,j}=g_{L,j}\cdot(\sum_{k=1}^{j-1}{g_{R,k}\cdot p_i}+\sum_{k=j+1}^{n}{g_{R,k}\cdot(1-p_i))}
$$
右儿子可能出现权值$j$的情况同理。

考虑这个转移的过程，相当于权值$j$出现的概率被乘上了$(\sum_{k=1}^{j-1}{g_{R,k}\cdot p_i}+\sum_{k=j+1}^{n}{g_{R,k}\cdot(1-p_i))}$。

仔细观察这个式子，里面是一个前缀和和一个后缀和，所以可以通过对支持乘法操作的线段树进行合并操作来实现转移，不断向上合并之后就可以求出根节点每种权值出现的概率了。具体实现参见代码（感觉还是挺妙的）。

时间复杂度和空间复杂度都是$O(n\log n)$。

### 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=300005,TT=998244353,inv=796898467;
int n,P[maxn],W[maxn],num[maxn],tot,lnk[maxn],son[maxn],nxt[maxn],ans;
inline int read()
{
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
inline void add_e(int x,int y){tot++;son[tot]=y;nxt[tot]=lnk[x];lnk[x]=tot;}
struct SegmentTree
{
	int tot,R[maxn];
	inline int New(){tot++;Tree[tot].Tag=1;return tot;}
	struct Node{int Sum,Tag,L,R;}Tree[maxn*40];
	inline void PushUp(int rt){Tree[rt].Sum=(Tree[Tree[rt].L].Sum+Tree[Tree[rt].R].Sum)%TT;}
	inline void PushDown(int rt)
	{
		Tree[Tree[rt].L].Sum=(LL)Tree[Tree[rt].L].Sum*Tree[rt].Tag%TT;Tree[Tree[rt].L].Tag=(LL)Tree[Tree[rt].L].Tag*Tree[rt].Tag%TT;
		Tree[Tree[rt].R].Sum=(LL)Tree[Tree[rt].R].Sum*Tree[rt].Tag%TT;Tree[Tree[rt].R].Tag=(LL)Tree[Tree[rt].R].Tag*Tree[rt].Tag%TT;
		Tree[rt].Tag=1;
	}
	inline int Merge(int rt1,int rt2,int P,int Pre1=0,int Suf1=0,int Pre2=0,int Suf2=0)
	{
		if(!rt1&&!rt2) return 0;
		PushDown(rt1);PushDown(rt2);
		int rt=New();
		if(!rt1)
		{
			int mul=((LL)P*Pre1+(LL)(1-P+TT)*Suf1)%TT;
			Tree[rt]=Tree[rt2];
			Tree[rt].Sum=(LL)Tree[rt2].Sum*mul%TT;
			Tree[rt].Tag=(LL)Tree[rt2].Tag*mul%TT;
		}
		else if(!rt2)
		{
			int mul=((LL)P*Pre2+(LL)(1-P+TT)*Suf2)%TT;
			Tree[rt]=Tree[rt1];
			Tree[rt].Sum=(LL)Tree[rt1].Sum*mul%TT;
			Tree[rt].Tag=(LL)Tree[rt1].Tag*mul%TT;
		}
		else
		{
			Tree[rt].L=Merge(Tree[rt1].L,Tree[rt2].L,P,Pre1,(Suf1+Tree[Tree[rt1].R].Sum)%TT,Pre2,(Suf2+Tree[Tree[rt2].R].Sum)%TT);
			Tree[rt].R=Merge(Tree[rt1].R,Tree[rt2].R,P,(Pre1+Tree[Tree[rt1].L].Sum)%TT,Suf1,(Pre2+Tree[Tree[rt2].L].Sum)%TT,Suf2);
			PushUp(rt);
		}
		return rt;
	}
	inline int NewTree(int P,int L=1,int R=num[0])
	{
		int rt=New();
		if(L==R){Tree[rt].Sum=1;return rt;}
		int M=(L+R)>>1;
		if(P<=M) Tree[rt].L=NewTree(P,L,M);
		else Tree[rt].R=NewTree(P,M+1,R);
		PushUp(rt);
		return rt;
	}
}ST;
void DFS(int now)
{
	if(!lnk[now]){ST.R[now]=ST.NewTree(W[now]);return;}
	for(int i=lnk[now];i;i=nxt[i])
	{
		DFS(son[i]);
		if(!ST.R[now]) ST.R[now]=ST.R[son[i]];
		else ST.R[now]=ST.Merge(ST.R[now],ST.R[son[i]],P[now]);
	}
}
void Solve(int L=1,int R=num[0],int rt=ST.R[1])
{
	if(L==R){ans=(ans+(LL)L*num[L]%TT*ST.Tree[rt].Sum%TT*ST.Tree[rt].Sum%TT)%TT;return;}
	int M=(L+R)>>1;
	ST.PushDown(rt);
	Solve(L,M,ST.Tree[rt].L);
	Solve(M+1,R,ST.Tree[rt].R);
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		int fi=read();
		if(fi) add_e(fi,i);
	}
	for(int i=1;i<=n;i++)
	{
		if(lnk[i]) P[i]=(LL)read()*inv%TT;
		else W[i]=num[++num[0]]=read();
	}
	sort(num+1,num+1+num[0]);
	for(int i=1;i<=n;i++)
		if(!lnk[i])
			W[i]=lower_bound(num+1,num+1+num[0],W[i])-num;
	DFS(1);Solve();
	printf("%d\n",ans);
	return 0;
}
```

---

