# Li Hua and Array

## 题目描述

Li Hua wants to solve a problem about $ \varphi $ — Euler's totient function. Please recall that $ \varphi(x)=\sum\limits_{i=1}^x[\gcd(i,x)=1] $ . $ ^{\dagger,\ddagger} $

He has a sequence $ a_1,a_2,\cdots,a_n $ and he wants to perform $ m $ operations:

- "1 $ l $ $ r $ " ( $ 1\le l\le r\le n $ ) — for each $ x\in[l,r] $ , change $ a_x $ into $ \varphi(a_x) $ .
- "2 $ l $ $ r $ " ( $ 1\le l\le r\le n $ ) — find out the minimum changes needed to make sure $ a_l=a_{l+1}=\cdots=a_r $ . In each change, he chooses one $ x\in[l,r] $ , change $ a_x $ into $ \varphi(a_x) $ . Each operation of this type is independent, which means the array doesn't actually change.

Suppose you were Li Hua, please solve this problem.

 $ ^\dagger $ $ \gcd(x,y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

 $ ^\ddagger $ The notation $ [\textrm{cond}] $ equals $ 1 $ if the condition $ \textrm{cond} $ is true, and $ 0 $ otherwise.

## 说明/提示

Denote $ \varphi^k(x)=\begin{cases}x,&k=0\\\varphi(\varphi^{k-1}(x)),&k > 0\end{cases} $ .

At first, $ a=[8,1,6,3,7] $ .

To make sure $ a_1=a_2=a_3=a_4=a_5 $ , we can change $ a $ to $ a'=[\varphi^3(8),\varphi^0(1),\varphi^2(6),\varphi^2(3),\varphi^3(7)]=[1,1,1,1,1] $ , using $ 3+0+2+2+3=10 $ changes.

To make sure $ a_3=a_4 $ , we can change $ a $ to $ a'=[\varphi^0(8),\varphi^0(1),\varphi^1(6),\varphi^1(3),\varphi^0(7)]=[8,1,2,2,7] $ , using $ 0+0+1+1+0=2 $ changes.

After "1 $ 1 $ $ 3 $ ", $ a $ is changed to $ a=[\varphi^1(8),\varphi^1(1),\varphi^1(6),\varphi^0(3),\varphi^0(7)]=[4,1,2,3,7] $ .

To make sure $ a_3=a_4 $ , we can change $ a $ to $ a'=[\varphi^0(4),\varphi^0(1),\varphi^0(2),\varphi^1(3),\varphi^0(7)]=[4,1,2,2,7] $ , using $ 0+0+0+1+0=1 $ change.

## 样例 #1

### 输入

```
5 4
8 1 6 3 7
2 1 5
2 3 4
1 1 3
2 3 4```

### 输出

```
10
2
1```

# 题解

## 作者：ppip (赞：6)

先报复杂度：时间 $O((n+m)(\log n+\log V) +V)$（$V$ 为值域上界，下同），空间 $\Theta(n+V)$，可以用线性 LCA 去掉 $m\log V$ 这一项，或使用树剖 LCA 使其变为 $m\log\log V$。

按照 $\varphi$ 函数对值域内所有数建树，题意转化为区间跳 father、查询区间所有点的深度之和以及该区间 LCA 的深度，且树高 $O(\log V)$。

深度和是平凡的，线段树区间减一查询区间和。考虑到根不能继续跳 father，暴力更新每个点，跳到根打个单点标记，用个链表维护下删除跳到根的点，$O(n\log V+(n+m)\log n)$。

现在询问可以认为是区间 LCA。这个区间跳 father 区间 LCA 可以用线段树维护。

首先线段树维护区间最小结点深度、区间 LCA。更新时打 tag，然后如果最小结点深度已经小于 LCA 的深度，就暴力跳 LCA 的父亲来更新，正确性显然。一个线段树结点维护的东西最多跳树高次，修改 $O(n\log V+m\log n)$。

查询区间 LCA，就是这棵线段树上若干个结点维护 LCA 的 LCA，由于 LCA 的深度总是在减少，我们又可以用暴力跳 LCA 的方法，在最多树高的时间内得到结果，复杂度 $O(m(\log n+\log V))$。

综合以上复杂度，加上线性筛 $\varphi$ 函数，就得到了开头的复杂度。

有点小麻烦，常数也有点大。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int S{1<<20};
char buf[S],*p1,*p2;
#define endl "\n"
#define all(awa) awa.begin(),awa.end()
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,S,stdin),p1==p2)?EOF:*p1++)
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
constexpr int N(1e5),M(5e6);
int fa[M+5],dep[M+5];
bitset<M+5> p;
vector<int> pr;
vector<int> e[M+5];
void eular(int n) {
    p[1]=1;
    for (int i{2};i<=n;++i) {
        if (!p[i]) pr.push_back(i),fa[i]=i-1;
        for (auto j:pr) {
            if (i*j>n) break;
            p[i*j]=1;
            fa[i*j]=fa[i]*(j-(i%j!=0));
            if (i%j==0) break;
        }
    }
}
int L[M+5],R[M+5];
void init(int u) {
    static int cxx{0};
    L[u]=++cxx;
    for (auto v:e[u]) init(v);
    R[u]=cxx;
}
int LCA(int u,int v) {
    if (!u||!v) return u+v;
    if (dep[u]>dep[v]) swap(u,v);
    while (!(L[u]<=L[v]&&R[u]>=L[v])) u=fa[u];
    return u;
}
int a[N+5];
namespace Tree1 {
    struct node {
        int lc,md,tg;
        void tag(int t=1) {
            md=max(0,md-t);
            while (dep[lc]>md) lc=fa[lc];
            tg+=t;
        }
    } t[N<<2];
    void down(int p) {
        t[p<<1].tag(t[p].tg);
        t[p<<1|1].tag(t[p].tg);
        t[p].tg=0;
    }
    void build(int p,int l,int r) {
        t[p].tg=0;
        if (l==r) {
            t[p].lc=a[l];
            t[p].md=dep[a[l]];
            return;
        }
        int mid{l+r>>1};
        build(p<<1,l,mid);
        build(p<<1|1,mid+1,r);
        t[p].lc=LCA(t[p<<1].lc,t[p<<1|1].lc);
        t[p].md=min(t[p<<1].md,t[p<<1|1].md);
    }
    void modify(int p,int L,int R,int l,int r) {
        if (l<=L&&R<=r) return t[p].tag();
        down(p);
        int mid{L+R>>1};
        if (l<=mid) modify(p<<1,L,mid,l,r);
        if (r>mid) modify(p<<1|1,mid+1,R,l,r);
        t[p].md=min(t[p<<1].md,t[p<<1|1].md);
        while (dep[t[p].lc]>t[p].md) t[p].lc=fa[t[p].lc];
    }
    int query(int p,int L,int R,int l,int r) {
        if (l<=L&&R<=r) return t[p].lc;
        down(p);
        int mid{L+R>>1},ans{0};
        if (l<=mid) ans=query(p<<1,L,mid,l,r);
        if (r>mid) ans=LCA(ans,query(p<<1|1,mid+1,R,l,r));
        return ans;
    }
}
namespace Tree2 {
    struct node {
        int sz,sum,tg;
        void tag(int t=-1) {sum+=sz*t;tg+=t;}
    } t[N<<2];
    void down(int p) {
        t[p<<1].tag(t[p].tg);
        t[p<<1|1].tag(t[p].tg);
        t[p].tg=0;
    }
    void upd(int p) {t[p].sum=t[p<<1].sum+t[p<<1|1].sum;}
    void build(int p,int l,int r) {
        t[p].tg=0;
        t[p].sz=r-l+1;
        if (l==r) {
            t[p].sum=dep[a[l]];
            return;
        }
        int mid{l+r>>1};
        build(p<<1,l,mid);
        build(p<<1|1,mid+1,r);
        upd(p);
    }
    void modify(int p,int L,int R,int l,int r) {
        if (l<=L&&R<=r) return t[p].tag();
        down(p);
        int mid{L+R>>1};
        if (l<=mid) modify(p<<1,L,mid,l,r);
        if (r>mid) modify(p<<1|1,mid+1,R,l,r);
        upd(p);
    }
    void erase(int p,int L,int R,int k) {
        --t[p].sz;
        if (L==R) return;
        down(p);
        int mid{L+R>>1};
        if (k<=mid) erase(p<<1,L,mid,k);
        else erase(p<<1|1,mid+1,R,k);
    }
    int query(int p,int L,int R,int l,int r) {
        if (l<=L&&R<=r) return t[p].sum;
        down(p);
        int mid{L+R>>1},ans{0};
        if (l<=mid) ans=query(p<<1,L,mid,l,r);
        if (r>mid) ans+=query(p<<1|1,mid+1,R,l,r);
        return ans;
    }
}
int f[N+5],g[N+5];
int n;
int find(int x) {return x==f[x]?x:f[x]=find(f[x]);}
void modify(int l,int r) {
    Tree2::modify(1,1,n,l,r);
    for (int i{find(l)};i<=r;i=find(i+1))
        if (--g[i]==0) {
            f[i]=i+1;
            Tree2::erase(1,1,n,i);
        }
}
int main() {
    int m,maxg{0};read(n,m);
    for (int i{1};i<=n;++i) read(a[i]),maxg=max(maxg,a[i]);
    eular(maxg);
    for (int i{2};i<=maxg;++i) dep[i]=dep[fa[i]]+1,e[fa[i]].push_back(i);
    init(1);
    Tree1::build(1,1,n);
    Tree2::build(1,1,n);
    for (int i{1};i<=n+1;++i) {
        f[i]=i;g[i]=dep[a[i]];
        if (a[i]==1) f[i]=i+1,Tree2::erase(1,1,n,i);
    }
    while (m--) {
        int op,l,r;read(op,l,r);
        if (op==1) {
            Tree1::modify(1,1,n,l,r);
            modify(l,r);
        } else {
            cout<<Tree2::query(1,1,n,l,r)-dep[Tree1::query(1,1,n,l,r)]*(r-l+1)<<"\n";
        }
    }
    return 0;
}
```

---

## 作者：Miraik (赞：6)

容易想到让 $i$ 向 $\varphi(i)$ 连边，得到一棵树。这个树的高度不高，是 $O(\log n)$ 的。

于是修改操作可以直接暴力，链表维护，跳到根（即变成 $1$）就从链表中删去就好。

再看询问。找到区间点的 LCA $x$，则答案即为 $\sum_{i=l}^r dep_i - (r-l+1) \times dep_x$。

根据经典结论，一堆点的 LCA 即为它们中 dfs 序最小和最大的点的 LCA。当然就算不知道这个，也是可以直接在线段树上暴力维护的（只是会多一个 $\log$）。

于是线段树维护区间 dfn 的最大最小值，找到 $x$ 就容易了。而 $\sum_{i=l}^r dep_i$ 也很好维护，这些信息直接在修改的时候更新就可以了，树状数组即可。

时间复杂度是 $O(n \log n \log V)$，瓶颈在于 $1$ 操作。

---

## 作者：zzxLLL (赞：5)

线段树。见过[这道题](https://www.luogu.com.cn/problem/P4145)就十分简单了。

---

先看修改操作。

想不出来怎么打懒标记，所以考虑暴力修改。

很显然每次操作后 $a_i \gets \varphi (a_i)$ 都会变小，具体的：

1.$a_i$ 为偶数时，$[1,a_i]$ 中的只有奇数有可能和它互质，所以 $\varphi (a_i) \leq \frac{a_i}{2}$。

2.$a_i$ 为奇数时，$\varphi (a_i) = a_i\prod \frac{p_j-1}{p_j}$，显然为偶数。

综上，对于每个数 $a_i$ 最多操作 $2\log a_i$ 次就会变成 $1$ 。

所以暴力修改复杂度是对的，事实上变换的最大次数仅为 23。维护区间最大值，如果最大值为 $1$ 说明此区间不用再修改。

---

再看查询操作。

事实上可以将值域抽象成一颗树，连边 $a_i \to \varphi (a_i)$，$1$ 为根，这样就变成了一道区间 LCA 的题。

相当于询问区间内每个节点到它们的 LCA 的距离之和。

预处理 $phi_{x,k} = \varphi^{2^k}(x)$ 以及 $x$ 到根节点的距离 $dis_x$，线段树维护区间内数字的 LCA 以及 $dis$ 之和即可。

---

因为修改操作和查询操作合并区间都要修改 LCA，所以时间复杂度为 $O(n \log^2 n)$。

以及倍增数组不必开太大，树高只有23。倍增维护 $2^{19}$ 级祖先最多跑了 2.73s，而维护 $2^6$ 级祖先时仅跑了 951ms。

```cpp
#include<cstdio>
const int M=1e5+10,N=5e6+10;

inline void swap(int &A,int &B){int t=A;A=B;B=t;}
inline int max(int A,int B){return A>B?A:B;}

int n,m,a[M];

bool mark[N];
int pri[N],phi[N][7],dis[N],cnt;
void Sieve(){
	mark[0]=mark[1]=true,phi[1][0]=1;
	for(int i=2;i<N;i++){
		if(!mark[i]) pri[++cnt]=i,phi[i][0]=i-1;
		for(int j=1;j<=cnt && i*pri[j]<N;j++){
			mark[i*pri[j]]=true;
			if(i%pri[j]==0){phi[i*pri[j]][0]=phi[i][0]*pri[j];break;}
			else phi[i*pri[j]][0]=phi[i][0]*(pri[j]-1);
		}
	}
	for(int i=2;i<N;i++) dis[i]=dis[phi[i][0]]+1;
	for(int j=1;j<=6;j++)
		for(int i=1;i<N;i++) phi[i][j]=phi[phi[i][j-1]][j-1];
}
//max{dis} = 23
int LCA(int u,int v){
	if(dis[u]<dis[v]) swap(u,v);
	for(int i=6;i>=0;i--)
		if(dis[phi[u][i]]>=dis[v]) u=phi[u][i];
	if(u==v) return u;
	for(int i=6;i>=0;i--)
		if(phi[u][i]!=phi[v][i]) u=phi[u][i],v=phi[v][i];
	return phi[u][0];
}

struct node{int l,r,mxd,sum,lca;}tr[M<<2];
#define lc (k<<1)
#define rc (k<<1|1)
node merge(node A,node B){
	node C;
	C.l=A.l,C.r=B.r;
	C.mxd=max(A.mxd,B.mxd);
	C.lca=LCA(A.lca,B.lca);
	C.sum=A.sum+B.sum;
	return C;
}
void build(int k,int l,int r){
	tr[k].l=l,tr[k].r=r;
	if(l==r){
		tr[k].mxd=tr[k].sum=dis[a[l]];
		tr[k].lca=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid),build(rc,mid+1,r);
	tr[k]=merge(tr[lc],tr[rc]);
}
void update(int k,int l,int r){
	if(tr[k].mxd==0) return;
	if(tr[k].l==tr[k].r){
		tr[k].lca=a[tr[k].l]=phi[a[tr[k].l]][0];
		tr[k].mxd=tr[k].sum=dis[a[tr[k].l]];
		return;
	}
	int mid=(tr[k].l+tr[k].r)>>1;
	if(l<=mid) update(lc,l,r);
	if(r>mid)  update(rc,l,r);
	tr[k]=merge(tr[lc],tr[rc]);
}
node query(int k,int l,int r){
	if(l<=tr[k].l && tr[k].r<=r) return tr[k];
	int mid=(tr[k].l+tr[k].r)>>1;
	if(r<=mid) return query(lc,l,r);
	else if(l>mid) return query(rc,l,r);
	else return merge(query(lc,l,r),query(rc,l,r));
}

int main(){
	Sieve();
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	build(1,1,n);
	for(int i=1,opt,l,r;i<=m;i++){
		scanf("%d%d%d",&opt,&l,&r);
		if(opt==1){
			update(1,l,r);
		}
		if(opt==2){
			node res=query(1,l,r);
			printf("%d\n",res.sum-(r-l+1)*dis[res.lca]);
		}
	}
	return 0;
}

```

---

## 作者：樱雪喵 (赞：3)

设 $a_i$ 的值域为 $w$。

将任意 $x$ 与 $\varphi(x)$ 连边，形成一棵根节点为 $1$ 的树。可以证明树高为 $\log w$ 级别。

这里简单证一下：

- 若 $x$ 为偶数，所有偶数与其不互质，$\varphi(x)\le \frac{x}{2}$。
- 若 $x$ 为大于 $1$ 的奇数
	- 若 $x$ 为质数，$\varphi(x)=x-1$，为偶数。
   - 否则，设 $x=a\times b$，其中 $a$ 为质数。则 $\varphi(x)=\varphi(a)\varphi(b)$，$\varphi(x)$ 为偶数。
 

则一次修改操作可以转化为在树上跳到它的父亲；一个区间最少次数下能够到达相同的数为区间内所有节点的 LCA。

查询操作转化为 $\sum\limits^{r}_{i=l}deep_{a_i}-(r-l+1)\times deep_{LCA}$，修改操作转化为区间 $deep$ 减一。

所以我们需要维护区间 LCA 与区间深度和，这个东西直接上线段树就好了。

由于每个 $a_i$ 至多只会被修改 $\log w$ 次，可以直接暴力递归两边。树剖求 LCA，时间复杂度 $O(m\log n\log \log w+n \log w)$。

```cpp
#include<bits/stdc++.h>
#define il inline 
using namespace std;
il int read()
{
	int xr=0,F=1; char cr=getchar();
	while(cr<'0'||cr>'9') {if(cr=='-') F=-1;cr=getchar();}
	while(cr>='0'&&cr<='9')
		xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
	return xr*F;
}
const int N=1e5+5,M=5e6+5;
int n,m,a[N],mx=5e6;

int phi[M],flag[M],p[M];
il void init()
{
	int cnt=0; phi[1]=1;
	for(int i=2;i<=mx;i++)
	{
		if(!flag[i]) p[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt&&1ll*i*p[j]<=mx;j++)
		{
			flag[i*p[j]]=1;
			if(i%p[j]==0) {phi[i*p[j]]=phi[i]*p[j];break;}
			else phi[i*p[j]]=phi[i]*phi[p[j]];
		}
	}
}
struct edge{
	int nxt,to;
}e[M<<1];
int head[M],cnt;
il void add(int u,int v) {e[++cnt]={head[u],v};head[u]=cnt;}
int dfn[M],siz[M],dep[M],fa[M],son[M],top[M];
int tot;
void dfs1(int now,int ff)
{
	//cout<<now<<" "<<ff<<endl;
	fa[now]=ff,dep[now]=dep[ff]+1,siz[now]=1;
	for(int i=head[now];i;i=e[i].nxt)
	{
		int v=e[i].to; if(v==ff) continue;
		dfs1(v,now),siz[now]+=siz[v];
		if(siz[v]>siz[son[now]]) son[now]=v;
	}
}
void dfs2(int now,int tp)
{
	//cout<<now<<" "<<tp<<endl;
	dfn[now]=++tot,top[now]=tp;
	if(son[now]) dfs2(son[now],tp);
	for(int i=head[now];i;i=e[i].nxt)
	{
		int v=e[i].to; if(v==son[now]||v==fa[now]) continue;
		dfs2(v,v);
	}
}
il int LCA(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}

#define ls (now<<1)
#define rs (now<<1|1)
#define mid ((l+r)>>1)
struct node{
	int s,lc;
}tr[N<<2];
il void push_up(int now)
{
	tr[now].s=tr[ls].s+tr[rs].s;
	tr[now].lc=LCA(tr[ls].lc,tr[rs].lc);
}
void build(int now,int l,int r)
{
	if(l==r) {tr[now]={dep[a[l]],a[l]};return;}
	build(ls,l,mid),build(rs,mid+1,r);
	push_up(now);
}
void modify(int now,int l,int r,int ml,int mr)
{
	//cout<<l<<" "<<r<<" "<<ml<<" "<<mr<<endl;
	if(tr[now].s==r-l+1) return;
	if(l==ml&&r==mr)
	{
		if(l==r) 
		{
			tr[now].s--,tr[now].lc=fa[tr[now].lc];
			return;
		}
		modify(ls,l,mid,ml,mid);
		modify(rs,mid+1,r,mid+1,mr);
		push_up(now); return;
	}
	if(mr<=mid) modify(ls,l,mid,ml,mr);
	else if(ml>mid) modify(rs,mid+1,r,ml,mr);
	else modify(ls,l,mid,ml,mid),modify(rs,mid+1,r,mid+1,mr);
	push_up(now);
}
node query(int now,int l,int r,int ml,int mr)
{
	if(l==ml&&r==mr) return tr[now];
	if(mr<=mid) return query(ls,l,mid,ml,mr);
	else if(ml>mid) return query(rs,mid+1,r,ml,mr);
	else 
	{
		node ansl=query(ls,l,mid,ml,mid),ansr=query(rs,mid+1,r,mid+1,mr);
		node ans;
		ans.s=ansl.s+ansr.s;
		ans.lc=LCA(ansl.lc,ansr.lc); return ans;
	}
}
signed main()
{
	init();
	for(int i=2;i<=mx;i++) add(i,phi[i]),add(phi[i],i);
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read(); 
	dfs1(1,0),dfs2(1,1);
	build(1,1,n);
	while(m--)
	{
		int op=read(),l=read(),r=read();
		if(op==1) modify(1,1,n,l,r);
		else
		{
			node qwq=query(1,1,n,l,r);
			int S=qwq.s,LC=qwq.lc;
			int ans=S-dep[LC]*(r-l+1);
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：__Aaaaaaaa (赞：2)

~~为什么题解区都在建树啊（~~

题面大意：李华有一个长度为 $n$ 的数列 $a$,维护 $m$ 次操作：  
操作1：对于区间 $[l,r]$ 的每个 $a_i$，将其改为 $φ(a_i)$。  
操作2：对于区间 $[l,r]$，求至少需要进行多少次操作，使得区间的所有 $a_i$
 相等。一次操作为选择恰好一个 $a_i$ 并将其改为 $φ(a_i)$
。操作不会真的进行。  
假如你是李华，请解决这一问题。

Solution:  
是这样的，如果把一个低于 $5\times 10^6$ 的数 $x$，将其不断以 $φ(x)$ 替代 $x$ 从而生成的序列，定义其为“phi 序列”（例如 $7$ 的“phi 序列”就是 ${1,2,6,7}$），长度不会超过 $24$，然后我们回到题目，可以感觉得到“区间最长公共前缀 phi 序列”很具有“结合律”（或称可合并性），那么可以考虑线段树（线段树的 pushup 所依赖的就是“结合律”）。


线段树维护两个数和一个序列：


1.$cnt$：需要对序列内的数进行多少次操作可以使得它们一样（即 phi 序列变成一样的，可以通过删去每个序列相比于“最长公共前缀 phi 序列”多出来的末尾元素即可）。   

2.$len$：区间长度（区间内包含了多少个数，即右端点编号-左端点编号+1）。 

3.$PHI$(“最长公共前缀 phi 序列”):区间内所有数生成的“phi 序列”按从小到大排序后取最长公共前缀，需要记录长度。  


pushup 函数详见代码。

那么操作1怎么办呢？这里显然无法用 lazytag 啊。  
是这样的，因为将区间内每个 $a_i$ 变成 $φ(a_i)$ 可以视作把区间内每个数的生成的序列的最后一个数扔掉，当然，如果该数的生成的序列的长度为 $1$ 了，即该数为 $1$ 了，那么就不能操作了，然而之前提到的“phi 序列”的长度不会超过 $24$，那么我们可以用类似“并查集压缩路径”的思想去暴力删除区间内每一个数的序列末尾（这个地方线段树处理单点修改是很轻松的），由于每个序列最多只会被删除 $24$ 次，所以复杂度最坏就是 $O(n \times   log_2n \times 24)$。

本方法综合了大量知识点，不喜轻喷……
### Don't talk much:
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N=1e5+10,M=5e6+10;
int pri[M/11],phi[M],ct;
bool st[M];
void init(int n){//线性筛欧拉函数
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!st[i]){
			pri[++ct]=i;
			phi[i]=i-1;
		}
		for(int j=1;pri[j]<=n/i;j++){
			int t=i*pri[j];
			st[t]=1;
			if(i==i/pri[j]*pri[j]){
				phi[t]=phi[i]*pri[j];
				break;
			}
			phi[t]=phi[i]*(pri[j]-1);
		}
	}
}
struct node{//"phi序列"
	int a[25],tot;
	void init(int x){
		a[++tot]=x;
		while(x>1){
			x=phi[x];
			a[++tot]=x;
		}
		for(int i=1;i<<1<=tot;i++)
			swap(a[i],a[tot-i+1]);
	}
};
int p[N];//并查集
int find(int x){
	if(p[x]!=x)
		p[x]=find(p[x]);
	return p[x];
}
struct tree{
	int l,r,len,cnt;
	node PHI;
}tr[N<<2];
int a[N];
void pushup(tree &U,tree &L,tree &R){//惊为天人的pushup
	U.len=L.len+R.len;
	U.PHI=L.PHI;
	int &n=U.PHI.tot;
	n=0;
	for(int i=1;i<=L.PHI.tot&&i<=R.PHI.tot;++i)
		if(L.PHI.a[i]==R.PHI.a[i])
			++n;
		else
			break;
	U.cnt=L.cnt+R.cnt+(L.PHI.tot-n)*L.len+(R.PHI.tot-n)*R.len;
}
int n;
void pushup(int u){
	pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}
void build(int u,int l,int r){
	tr[u]=(tree){l,r,r-l+1,0};
	if(l==r){
		tr[u].PHI.init(a[l]);
		if(a[l]==1)
			p[find(l)]=l+1;
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u);
}
int Change(int u,int x){//单点修改，返回a[x]所生成的phi序列的剩余长度
	if(tr[u].l==tr[u].r){
		if(tr[u].PHI.tot>1)
			return --tr[u].PHI.tot;
		return 1;
	}
	int mid=tr[u].l+tr[u].r>>1;
	int res;
	if(mid>=x)res=Change(u<<1,x);
	else res=Change(u<<1|1,x);
	pushup(u);
	return res;
}
tree query(int u,int l,int r){//查询[l,r]区间
	if(tr[u].l>=l&&tr[u].r<=r)
		return tr[u];
	int mid=tr[u].l+tr[u].r>>1;
	if(mid>=r)return query(u<<1,l,r);
	if(mid<l)return query(u<<1|1,l,r);
	tree L=query(u<<1,l,r),R=query(u<<1|1,l,r),U;
	pushup(U,L,R);
	return U;
}
void remove(int u,int lim){//并查集压缩路径，进行单点暴力修改
	u=find(u);
	if(u>lim)
		return;
	int remind=Change(1,u);
	remove(u+1,lim);
	if(remind==1)//如果a[u]=1了，那么今后的删除就不考虑它了，并查集路径压缩掉
		p[u]=u+1;
}
int m;
int main(){
	int ans=0;
	init(M-10);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=n;i++)
		p[i]=i;
	p[n+1]=n+1;
	build(1,1,n);
	int opt,l,r;
	while(m--){
		scanf("%d%d%d",&opt,&l,&r);
		if(opt==1)
			remove(l,r);
		else{
			printf("%d\n",query(1,l,r).cnt);
		}
	}
	return 0;
}
```

---

## 作者：zcxxnqwq (赞：2)

### 题目大意：

给定序列 $a$，要求支持以下两个操作：

- 对于每个 $i\in[l,r]$，$a_i\gets\varphi(a_i)$；

- 每次操作可以选择一个 $i$ 使得 $a_i\gets\varphi(a_i)$，求最少需要多少次操作使得 $\forall i,j\in[l,r],a_i=a_j$。

### 题解

因为 $\forall n>2,\varphi(n)$ 为偶数，而对于任意偶数 $n$，显然 $\varphi(n)\le \frac{n}{2}$，所以可知将值域上界为 $w$ 的数变为 $1$ 的操作次数是 $O(\log w)$ 的，所以暴力进行修改操作的复杂度为 $O(n\log w)$，可以接受。

$a_i\gets\varphi(a_i)$ 的形式可以让我们想到建一棵以 $1$ 为根的树，这样每次修改就是在树上向上跳，查询即求 $[l,r]$ 所有点权值的 LCA，容易想到维护区间内节点 dfn 序的最大值和最小值来求 LCA，为了得到答案还要维护区间内节点深度和。

用线段树维护即可，修改操作暴力单点修改，询问区间查询。

不要弄混 dfn 序下标和原下标！！！

时间复杂度 $O(n\log w+m\log n+m\log\log w)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i,s,e) for(int i=(s);i<=(e);++i)
#define Rep(i,s,e) for(int i=(e);i>=(s);--i)
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=1e5+5,M=5e6+5;
int n,m,a[N],mx;
bool vis[M];
int p[M],tot,phi[M];
int head[M],cnt;
struct qwq{
    int v,nxt;
}e[M];
inline void adde(int u,int v){
    e[++cnt]={v,head[u]},head[u]=cnt;
}
inline void shai(int n){
    phi[1]=1;
    rep(i,2,n){
        if(!vis[i]) p[++tot]=i,phi[i]=i-1;
        for(int j=1;j<=tot&&1ll*p[j]*i<=n;++j){
            vis[i*p[j]]=1;
            if(i%p[j]==0){phi[i*p[j]]=phi[i]*p[j];break;}
            phi[i*p[j]]=phi[i]*(p[j]-1);
        }
    }
    rep(i,2,n) adde(phi[i],i);
}
int dep[M],f[M],top[M],dfn[M],son[M],siz[M],yy[M];
void dfs(int x,int fa){
    dep[x]=dep[fa]+1,f[x]=fa,siz[x]=1;
    int mx=0;
    for(int i=head[x];i;i=e[i].nxt){
        int v=e[i].v;
        dfs(v,x),siz[x]+=siz[v];
        if(siz[v]>mx) mx=siz[v],son[x]=v;
    }
}
void dfs1(int x,int tp){
    top[x]=tp,dfn[x]=++tot,yy[tot]=x;
    if(!son[x]) return;
    dfs1(son[x],tp);
    for(int i=head[x];i;i=e[i].nxt){
        int v=e[i].v;
        if(v!=son[x]) dfs1(v,v);
    }
}
inline int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        x=f[top[x]];
    }
    return dep[x]>dep[y]?y:x;
}
int mxx,mnn;
struct segtree{
    int mn[N<<2],mx[N<<2],s[N<<2];
    inline void pushup(int k){
        int ls=k<<1,rs=k<<1|1;
        mn[k]=min(mn[ls],mn[rs]);
        mx[k]=max(mx[ls],mx[rs]);
        s[k]=s[ls]+s[rs];
    }
    void build(int k,int l,int r){
        if(l==r) return mn[k]=mx[k]=dfn[a[l]],s[k]=dep[a[l]],void();
        int mid=l+r>>1;
        build(k<<1,l,mid),build(k<<1|1,mid+1,r);
        pushup(k);
    }
    void upd(int k,int l,int r,int x,int y){
        if(mx[k]==1) return;
        if(l==r){
            a[l]=phi[a[l]],mn[k]=mx[k]=dfn[a[l]],s[k]=dep[a[l]];
            return;
        }
        int mid=l+r>>1;
        if(x<=mid) upd(k<<1,l,mid,x,y);
        if(y>mid) upd(k<<1|1,mid+1,r,x,y);
        pushup(k);
    }
    void query(int k,int l,int r,int x,int y){
        if(x<=l&&y>=r) return mxx=max(mxx,mx[k]),mnn=min(mnn,mn[k]),void();
        int mid=l+r>>1;
        if(x<=mid) query(k<<1,l,mid,x,y);
        if(y>mid) query(k<<1|1,mid+1,r,x,y);
    }
    int qsum(int k,int l,int r,int x,int y){
        if(x<=l&&y>=r) return s[k];
        int mid=l+r>>1,ans=0;
        if(x<=mid) ans+=qsum(k<<1,l,mid,x,y);
        if(y>mid) ans+=qsum(k<<1|1,mid+1,r,x,y);
        return ans;
    }
}t;
signed main(){
    n=read(),m=read();
    rep(i,1,n) a[i]=read(),mx=max(mx,a[i]);
    shai(mx),tot=0,dfs(1,0),dfs1(1,1);
    t.build(1,1,n);
    while(m--){
        int op=read(),l=read(),r=read();
        if(op==1) t.upd(1,1,n,l,r);
        else{
            mxx=0,mnn=1e9,t.query(1,1,n,l,r);
            int zz=lca(yy[mxx],yy[mnn]);
            printf("%d\n",t.qsum(1,1,n,l,r)-dep[zz]*(r-l+1));
        }
    }
}
```


---

## 作者：EuphoricStar (赞：2)

考虑将每个 $a_i$ 一直 $x \gets \varphi(x)$ 得到的所有数从小到大写成一个序列，则问题可以被简化成：

> 给定 $n$ 个长度不超过 $\log V$ 的序列，有两种操作：
> 1. 删除 $[l,r]$ 序列的末尾元素（如果序列只有一个元素就不删）
> 2. 查询 $[l,r]$ 序列的 $\operatorname{LCP}$

考虑所有序列总长为 $O(n \log V)$，删除操作时暴力枚举 $l$ 到 $r$ 即可，使用并查集维护每个元素下一个非 $1$ 元素的位置。

考虑从末尾删元素只会对 $\operatorname{LCP}$ 在长度方面有影响，所以可以认为是静态查询。

既然是静态，那么对于每个位置预处理出最大的 $nxt_{k,i}$ 表示 $[i,nxt_{k,i}]$ 在第 $k$ 位相等。询问直接枚举 $\operatorname{LCP}$，最大的满足 $\forall p \in [1,k],nxt_{p,l} \ge r$ 且 $\forall i \in [l,r], k \le len_i$ 的 $k$ 就是 $\operatorname{LCP}$。

实现时需要一个线段树维护序列长度的区间 $\min$ 和区间和。时间复杂度 $O(n (\log n + \log V) + m \log n \log V)$。

[Code](https://codeforces.com/contest/1797/submission/201400978)

---

## 作者：Hisaishi_Kanade (赞：1)

注意到对一个数进行 $x\gets\varphi(x)$ 的次数是 $\log_2 x$ 级别的。

~~联想到一个花神游历，我们直接分块~~实际上笔者写了一个 5.29k 的分块用了几天调不出来后来就摆了。~~今天一个小时写个线段树就过了。~~

那么我们直接钦定一棵树 $\varphi(x)$ 作为 $x$ 的父亲，树高 $\log V$，我们叫他叉三树。

如何查询？我们发现最小变化中的 $x$ 必然是这个区间的 $a_i$ 在叉三树上的最近公共祖先，因为你再往上爬只会花费更多。那么考虑到你爬一层就是做一次操作，所以最后的答案就是每个数在叉三树上层数的和减去它们最近公共祖先的层数乘上区间长度，即 $\sum dep_{a}-(r-l+1)\times dep_{lca}$。

那么需要求出 $lca$ 和 $\sum dep_{a}$，这个可以使用线段树求解，$lca$ 的求法就直接暴力即可，树高是一只 $\log$ 而已！

肯定是暴力修改了，直接在线段树上查一个区间的数在叉三树上最大深度是不是 $1$，如果如此，那么直接润不改了，因为你改了也没用 $\varphi(1)=1$。否则直接递归下去嗯改。

首先细节看代码吧，嗯讲也讲不了很详细。

```cpp 
#include <bits/stdc++.h>
#define rep(i,l,r) for(i=l;i<=r;++i)
using namespace std;
const int N=1e5+5,V=5e6+5;
bool np[V];
int pr[V],phi[V],dep[V];
int a[N];
int i,j;
#define lc(id) (id<<1)
#define rc(id) (id<<1|1)
#define mid (l+r>>1)
int cnt;
inline void Eular(int n)
{
	phi[1]=1;
	np[0]=np[1]=true;dep[1]=1;
	rep(i,2,n)
	{
		if(!np[i])
		{
			pr[++cnt]=i;
			phi[i]=i-1;
		}
		for(j=1;j<=cnt && 1ll*i*pr[j]<=n;++j)
		{
			np[i*pr[j]]=true;
			if(i%pr[j]==0)
			{
				phi[i*pr[j]]=phi[i]*pr[j];
				break;
			}else
				phi[i*pr[j]]=phi[i]*(pr[j]-1);
		}
	}
	rep(i,2,n)dep[i]=dep[phi[i]]+1;//不需要真的建立叉三树，我们只需要深度啊！
	return ;
}//求出 phi
inline int lca(int u,int v)
{
	if(u==1 || v==1) return 1;
	if(dep[u]<dep[v])swap(u,v);
	while(dep[u]>dep[v])u=phi[u];
	if(u==v)return u;
	else
		while(u!=v)
		{
			u=phi[u];
			v=phi[v];
		}
	return u;
}//暴力 lca
class Eti
{
public:
	bool fl;//我们定义 fl=true 时下面的 push_up 无效，方便写 query
	int mx,lca,sum;
}tr[N<<2];
Eti epy;
Eti ans;
Eti push_up(const Eti &x,const Eti &y)
{
	Eti rans;rans.fl=false;
	if(x.fl)return y;
	if(y.fl)return x;//query 时访问到空区间就不进行加法了。
	rans.mx=max(x.mx,y.mx);
	rans.lca=lca(x.lca,y.lca);
	rans.sum=x.sum+y.sum;
//	printf("add x   %d %d %d %d\n",x.mx,x.lca,x.sum,x.fl);
//	printf("add y   %d %d %d %d\n",y.mx,y.lca,y.sum,y.fl);
//	printf("add ans %d %d %d %d\n",rans.mx,rans.lca,rans.sum,rans.fl);
	return rans;
}//将两个 Eti 相加
inline void build(int id,int l,int r)
{
	if(l==r)
	{
		tr[id].lca=a[l];
		tr[id].mx=tr[id].sum=dep[a[l]];
		return ;
	}
	build(lc(id),l,mid);
	build(rc(id),mid+1,r);
	tr[id]=push_up(tr[lc(id)],tr[rc(id)]);
//	printf("build %d %d %d %d\n",l,r,tr[id].sum,tr[id].lca);
	return ;
}
inline void pointupd(int id,int pos)
{
	tr[id].lca=a[pos]=phi[a[pos]];
	tr[id].mx=tr[id].sum=dep[a[pos]];
	return ;
}//单点更新
inline void update(int id,int ql,int qr,int l,int r)
{
	if(r<ql || l>qr) return ;
	if(tr[id].mx==1) return ;
	if(l==r){pointupd(id,l);return ;}
	update(lc(id),ql,qr,l,mid);
	update(rc(id),ql,qr,mid+1,r);
	tr[id]=push_up(tr[lc(id)],tr[rc(id)]);
}
inline Eti query(int id,int ql,int qr,int l,int r)
{
	if(r<ql || l>qr)return epy;//直接返回一个空，类似零。
	if(ql<=l && r<=qr)return tr[id];
	return push_up(query(lc(id),ql,qr,l,mid),query(rc(id),ql,qr,mid+1,r));//这样写不是很简洁吗！
}
int main()
{
	int n,m,op,l,r;epy.fl=true;//初始化 epy(empty) 的 fl 为 true
	scanf("%d %d",&n,&m);
	Eular(V-5);
	rep(i,1,n)scanf("%d",a+i);//rep(i,1,n)printf("%d\n",dep[a[i]]);
	build(1,1,n);
//	puts("ok");
//printf("%d %d.\n",phi[6],dep[6]);
	rep(i,1,m)
	{
		scanf("%d %d %d",&op,&l,&r);
		if(op==1)
			update(1,l,r,1,n);
		else
		{
			ans=query(1,l,r,1,n);
//			printf("%d %d %d\n",ans.sum,ans.lca,r-l+1);
			printf("%d\n",ans.sum-dep[ans.lca]*(r-l+1));
		}
	}
}
```

---

## 作者：童年的小翼龙 (赞：1)

## 思路
考虑将**正整数 $i$** 作为一个节点，并用边连接 $\varphi(i)$ 和 $i$。因为 $\varphi(i)<i$，且对任意正整数 $i$ 取若干次欧拉函数值后一定会变成 $1$，所以这构成了一棵树。除了 $1$ 以外，每个节点 $i$ 的父节点均为 $\varphi(i)$。

那么对于第二问，容易发现，最终的数取**所有 $a_i(l\leq i\leq r)$** 的 $lca$ 的时候所需要步数最小。记 $i$ 在上述的树上的深度为 $dep_i$，则第二问的答案就是：
$$\sum_{i=l}^rdep_{a_i}-(r-l+1)\times lca$$
考虑用线段树维护。每个线段树节点记录当前区间的 $lca$ 和 深度和 $alldep$，将两个子节点 $ls$ 和 $rs$ 合并到当前节点 $ro$，则：
$$lca_{ro} = lca(lca_{ls} , lca_{rs})$$
$$alldep_{ro} = alldep_{ls} + alldep_{rs}$$
由于树高为 $\log$，所以使用倍增求取 $lca$ 的时间复杂度为 $O(\log_2\log_2V)$，其中 $V$ 是 $a_i$ 的值域。

现在考虑修改。发现：对于正整数 $i$：
- 若 $i$ 为偶数，则 $\varphi(i)\leq \frac{i}{2}$。
- 若 $i$ 为奇质数，则 $\varphi(i) = i-1$，是偶数。
- 若 $i$ 为奇合数，由于欧拉函数为奇性函数 $\varphi(i) = \varphi(p) \times \varphi(\frac{i}{p})$，其中 $p$ 为 $i$ 的一个奇质因子，可以证明这个奇质因子一定存在。由于 $\varphi(p)$ 为偶数，所以 $\varphi(i)$ 为偶数。

所以对于正整数 $i$，一直取它的欧拉函数值，直到取到 $1$ 为止，这样的次数是 $O(\log_2i)$。因此，我们可以用一个 ```set``` 维护一个还没有变成 $1$ 的 $a_i$ 的集合，每次从这个集合中找到满足 $i\in [l,r]$ 的 $a_i$ 去在线段树更新，并在当前 $a_i$ 变为 $1$ 的时候将其从集合中删除。由于每一个 $a_i$ 最多更新 $O(\log_2a_i)$ 次，每次在集合中查找 $a_i$ 的时间复杂度为 $O(\log_2n)$，更新的时间复杂度为 $O(\log_2n \cdot \log_2\log_2V)$。所以更新的总时间复杂度为 $O(n\log_2^2n\cdot \log_2\log_2V)$。

AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Slongod{
const int N = 1e6+6 , MAXN = 5e6+7 , MX = 7;
int n , m , cnt;
int vis[MAXN] , fa[MAXN] , prim[N] , f[N][MX] , dep[N] , a[N];
vector <int> g[N];
unordered_map <int,int> mymap;
//建出树
void prepare()
{
    vis[1] = 1;
    for (int i = 2; i < MAXN; i++)
    {
        if (!vis[i]){prim[++cnt] = i; fa[i] = i;}
        for (int j = 1; j <= cnt and prim[j] * i < MAXN; j++)
        {
            vis[prim[j] * i] = 1; fa[prim[j]*i] = prim[j];
            if (i % prim[j] == 0){break;}
        }
    }
}
void phi(int x)
{
    if (mymap.count(x)){return;}
    mymap.insert(make_pair(x , ++cnt));
 
    if (x == 1){return;}
    int re = x , tmp = x;
    while(x != 1)
    {
        int t = fa[x];
        re = re - re / t;
        while(x % t == 0){x /= t;}
    }
    phi(re);
    g[mymap[re]].push_back(mymap[tmp]);
}
void dfs(int u)
{
    for (int i = 1; i < MX; i++){f[u][i] = f[f[u][i-1]][i-1];}
    for (auto v : g[u]){f[v][0] = u; dep[v] = dep[u] + 1; dfs(v);}
}
int lca(int x , int y)
{
    if (dep[x] < dep[y]){swap(x , y);}
    int cont = dep[x] - dep[y] , num = 0;
    while(cont){if (cont & 1){x = f[x][num];} num++; cont >>= 1;}
    if (x == y){return x;}
    for (int i = MX-1; i >= 0; i--){if (f[x][i] != f[y][i]){x = f[x][i]; y = f[y][i];}}
    return f[x][0];
}
//线段树
#define ls ro*2
#define rs ro*2+1
struct TREE{int lca , alldep;}tree[N];
TREE pushup(TREE l , TREE r)
{
    TREE re; re.lca = lca(l.lca , r.lca);
    re.alldep = l.alldep + r.alldep;
    return re;
}
void build(int ro , int l , int r)
{
    if (l >= r){tree[ro].lca = a[l]; tree[ro].alldep = dep[a[l]]; return;}
    int mid = (r - l) / 2 + l; build(ls , l , mid); build(rs , mid+1 , r);
    tree[ro] = pushup(tree[ls] , tree[rs]);
}
void update(int ro , int lt , int rt , int x)
{
    if (lt >= rt){tree[ro].lca = f[tree[ro].lca][0]; tree[ro].alldep = dep[tree[ro].lca]; return;}
    int mid = (rt - lt) / 2 + lt;
    if (x <= mid){update(ls , lt , mid , x);}
    else{update(rs , mid+1 , rt , x);}
    tree[ro] = pushup(tree[ls] , tree[rs]);
}
TREE query(int ro , int lt , int rt , int l , int r)
{
    if (l <= lt and r >= rt){return tree[ro];}
    int mid = (rt - lt) / 2 + lt;
    if (r <= mid){return query(ls , lt , mid , l , r);}
    else if (l > mid){return query(rs , mid+1 , rt , l , r);}
    else{return pushup(query(ls , lt , mid , l , r) , query(rs , mid+1 , rt , l , r));}
}
//朱晗树
set <int> myset , tmp;
void init()
{
    prepare(); cnt = 0;
    for (int i = 1; i <= n; i++){phi(a[i]);}
    dep[1] = 1; f[1][0] = 1; dfs(mymap[1]);
    for (int i = 1; i <= n; i++){a[i] = mymap[a[i]]; myset.insert(i);}
    build(1 , 1 , n);
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++){cin >> a[i];}
    init();
 
    for (int i = 1 , t , l , r; i <= m; i++)
    {
        cin >> t >> l >> r;
        if (t == 1)
        {
            auto it = myset.lower_bound(l);
            while(it != myset.end() and *it <= r)
            {
                update(1 , 1 , n , *it);
                a[*it] = f[a[*it]][0];
                if (a[*it] == mymap[1]){tmp.insert(*it);}
                it++;
            }
            for (auto j : tmp){myset.erase(j);} tmp.clear();
        }
        else
        {
            auto p = query(1 , 1 , n , l , r);
            cout << p.alldep - (r - l + 1) * dep[p.lca] << '\n';
        }
    }
 
    return 0;
}
}int main()
{
    ios :: sync_with_stdio(0);
    cin.tie(0) , cout.tie(0);
    return Slongod :: main();
}
```

---

## 作者：jasonliujiahua (赞：0)

# CF1797E

[题目传送门](https://www.luogu.com.cn/problem/CF1797E)
## 题意简述：
给定一个长度为 $1\le n\le 10^5$ 的数列，$1\le a_i\le 5\times 10^6$。

有 $m\le 10^5$ 次操作 `o l r`，
1. $o=1$ 时， $\forall\ l\le i\le r$，$a_i\gets\varphi(a_i)$
2. $o=2$ 时，找出使 $a_l=a_{l+1}\dots=a_r$ 的最小变化。在每次变化中，选择一个 $x\in[l,r],a_i\gets \varphi(a_i)$。修改独立。

对于每个操作 $2$ 输出最小答案。
## 题目分析：
### Step 1：线段树做法可行性
看到区间修改和区间查询，自然可以想到用线段树进行处理。可以看到显然无法直接在一个区间上对每个数执行 $\varphi$ 操作，因此考虑不写懒标记，直接暴力地递归到叶子结点进行修改。那么，复杂度怎么保证呢？

可以发现一个数执行 $\varphi$ 操作的次数是 $O(\log V)$ 的。
- 若 $x$ 为偶数，则 $\varphi(x)\le \frac{x}{2}$。这是因为所有偶数都不对 $\varphi(x)$ 进行贡献。
- 若 $x$ 为奇数，则 
$$\varphi(x)=x\prod_{p_i\in P,p_i\bmod 2=1}\left(1-\frac{1}{p_i}\right) $$
$$=x\prod_{p_i\in P,p_i=2k+1}\left(\frac{p_i-1}{p_i}\right) $$
$$=x\prod_{p_i\in P,p_i=2k+1}\left(\frac{2k}{p_i}\right) $$
$$=2\left(x\prod_{p_i\in P,p_i=2k+1}\left(\frac{k}{p_i}\right)\right) $$
$$=2A$$
其中 $A=\left(x\prod_{p_i\in P,p_i=2k+1}\left(\frac{k}{p_i}\right)\right)$。由于 $p_i|x$，可以发现 $A\in \mathbb{Z}$，因此 $\varphi(x)$ 为偶数，又回到了上一种情况。

因此每 $1$ 至 $2$ 次操作就会使 $x$ 规模减半，所以操作次数自然是 $O(\log V)$ 的。
### Step 2：对 $\varphi$ 操作建树
我们可以对 $\varphi$ 操作建树，就可以发现若干个数最早变成相同时，它们都将等于它们在这棵树上的 LCA。因此就可以将该操作转换成树上问题求解。具体地，我用树剖求得 LCA。
### Step 3：线段树维护
我们用线段树维护一下信息：
1. $all$：区间是否全为 $1$，保证势能线段树复杂度。
2. $LCA$：区间所有数在上面建的树中的 LCA。
3. $ans$：该区间的答案，即该区间所有数在上面建的树中距离 LCA 的距离和。
4. $len$：区间长度，在回答询问时会用到。

剩下的细节在代码里。
## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e6+10,N=2e5+10;
int n,m,cnt,b[N],p[maxn],sum,v[maxn],phi[maxn];
int dep[maxn],fa[maxn],sz[maxn],son[maxn],top[maxn];
bool mark[maxn];
struct edge
{
    int u,v,nxt;
}e[maxn];//对phi建树
int head[maxn];
struct node
{
    bool all;
    int LCA,ans,len;
}a[N<<2];
inline void add(int x,int y)
{
    e[++cnt].u=x;
    e[cnt].v=y;
    e[cnt].nxt=head[x];
    head[x]=cnt;
}
void prime()//线性筛欧拉函数
{
    phi[1]=1;
    for(int i=2;i<maxn;i++)
    {
        if(!v[i])
        {
            v[i]=i;
            p[++sum]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=sum && i*p[j]<maxn;j++)
        {
            v[i*p[j]]=p[j];
            if(i%p[j]==0)
            {
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
            phi[i*p[j]]=phi[i]*phi[p[j]];
        }
    }
}
void init()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
}
void build_tree()对phi建树
{
    for(int i=1;i<=n;i++)
    {
        int tmp=b[i];
        while(tmp>1)
        {
            if(mark[tmp]) break;
            mark[tmp]=1;
            add(phi[tmp],tmp);
            tmp=phi[tmp];
        }
    }
}
void dfs1(int u,int f)//树剖预处理
{
    dep[u]=dep[f]+1,fa[u]=f,sz[u]=1;
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(v==f) continue;
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[son[u]]<sz[v]) son[u]=v;
    }
}
void dfs2(int u)//树剖预处理
{
    if(u==son[fa[u]]) top[u]=top[fa[u]];
    else top[u]=u;
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(v==fa[u]) continue;
        dfs2(v);
    }
}
inline int lca(int x,int y)//求LCA
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
        else y=fa[top[y]];
    }
    if(dep[x]<dep[y]) return x;
    return y;
}
inline int pushup(int id,int l,int r)
{
    int mid=(l+r)>>1;
    a[id].all=(a[id<<1].all&a[id<<1|1].all);
    a[id].LCA=lca(a[id<<1].LCA,a[id<<1|1].LCA);
    //ans：左右子树的贡献加上左右区间内各数到LCA的距离
    a[id].ans=a[id<<1].ans+(dep[a[id<<1].LCA]-dep[a[id].LCA])*(mid-l+1)+
        a[id<<1|1].ans+(dep[a[id<<1|1].LCA]-dep[a[id].LCA])*(r-mid);
    a[id].len=a[id<<1].len+a[id<<1|1].len;
}
void build(int id,int l,int r)
{
    if(l==r) 
    {
        if(b[l]==1) a[id].all=1;
        else a[id].all=0;
        a[id].ans=0;
        a[id].LCA=b[l];
        a[id].len=1;
        return;
    }
    int mid=(l+r)>>1;
    build(id<<1,l,mid);
    build(id<<1|1,mid+1,r);
    pushup(id,l,r);
}
inline void modify(int id,int l,int r,int x,int y)
{
    if(a[id].all) return;
    if(l==r)
    {
        a[id].LCA=fa[a[id].LCA];
        if(a[id].LCA==1) a[id].all=1;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) modify(id<<1,l,mid,x,y);
    if(y>mid) modify(id<<1|1,mid+1,r,x,y);
    pushup(id,l,r);
}
inline node query(int id,int l,int r,int x,int y)
{
    if(l>=x && r<=y) return a[id];
    int mid=(l+r)>>1;
    node res=(node){0,0,0,0},ls=(node){0,0,0,0},rs=(node){0,0,0,0};
    if(x<=mid) ls=query(id<<1,l,mid,x,y);
    if(y>mid) rs=query(id<<1|1,mid+1,r,x,y);
    if(ls.LCA==0) return rs;
    if(rs.LCA==0) return ls;
    res.LCA=lca(ls.LCA,rs.LCA);
    res.ans=ls.ans+(dep[ls.LCA]-dep[res.LCA])*ls.len+
    rs.ans+(dep[rs.LCA]-dep[res.LCA])*rs.len;
    //类比pushup中对ans的更新
    //区别是这里的len不是原区间长度，而是区间内对答案有贡献的数的长度
    res.len=ls.len+rs.len;
    return res;
}
void work()
{
    for(int i=1;i<=m;i++)
    {
        int o,l,r;
        cin>>o>>l>>r;
        if(o==1) modify(1,1,n,l,r);
        else cout<<query(1,1,n,l,r).ans<<endl;
    }
}
signed main()
{
    prime();
    init();
    build_tree();
    dfs1(1,0);
    dfs2(1);
    build(1,1,n);
    work();
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

简单题。

首先转化题意，相当于所有的 $i$ 对 $\varphi(i)$ 连边，建出一颗树。$q$ 次操作，求一个区间所有点到其 $\text{LCA}$ 的距离和，支持区间求 $\varphi$。

- 结论：对于任意整数 $x$，一定在不超过 $\lceil2\log_2x\rceil$ 次 $x \leftarrow \varphi(x)$ 之后变成 $1$。

	证明比较显然，如果 $x$ 是偶数，则 $\varphi(x) \leq \dfrac{x}{2}$；否则 $\varphi(x)=x\prod\limits_{p_i\mid x}(\frac{p_i-1}{p_i})$，而 $p_i$ 一定为奇数，所以最后一定是一个小于等于 $x-1$ 的偶数。

因此操作 $1$ 可以直接使用势能线段树维护，对于一个全部为 $1$ 的连续段就跳过，否则暴力单点修改。这是比较基础的操作。

考虑怎么维护操作 $2$ 的答案。假设 $i$ 的深度为 $d_i$，我们可以维护区间的深度和 $S_{l,r}=\sum_{i=l}^{r} d_i$，以及区间的 $\text{LCA}$ $L_{l,r}=\operatorname{LCA}_{i=l}^{r} d_i$。区间 $(l,r)$ 的答案就是 $(r-l+1)d_{L{l,r}}-S_{l,r}$。

而操作 $2$ 我们只需要在线段树的每个节点上维护这个区间的 $\text{LCA}$ 以及这个区间的点的深度和即可，这是容易的。

由于 $\varphi$ 建出来的树高为 $\log V$，$\text{LCA}$ 直接暴力往上跳即可。使用埃筛或线性筛求 $\varphi(i)$，总复杂度可做到 $O(V \log V+n \log n \log V)$ 或 $O(V+n \log n \log V)$，$V$ 为值域。

代码还是比较好写的，但是不知道为啥有人写了特别长。

[Code & Submission](https://codeforces.com/contest/1797/submission/225198577)

---

## 作者：Xy_top (赞：0)

势能法的一道题，场上卡 C 就没做，可见我有多菜。

维护一个线段树表示这个序列，维护区间 $lca$ 和区间 $dep$ 的 $sum$。

求 $lca$ 可以用倍增，注意这里倍增数组开到 $4$ 就够了，树不会很深。

每次修改暴力改，每个点最多被改 $\log n$ 次，而改某个点需要递归 $\log n$ 次，故修改总时间 $n\log ^2 n$。

查询也是很简单，用区间 $dep$ 的 $sum$ 减去区间长度乘以区间 $lca$ 的深度即可。

最终复杂度为 $O(m\log^2n)$

代码：

```cpp
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
#define int long long
using namespace std;
int n, m, k, cnt;
int c[100005], dep[5000005], phi[5000005], sum[400005], lc[400005], primes[5000005];
int f[5000005][5];
bool prime[5000005];
void init () {
	phi[1] = 1;
	for (int i = 2; i <= 5000000; i ++) {
		if (!prime[i]) {
			primes[++ cnt] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= cnt && i * primes[j] <= 5000000; j ++) {
			prime[i * primes[j] ] = 1;
			if (i % primes[j] == 0) {
				phi[i * primes[j] ] = phi[i] * primes[j];
				break;
			} else phi[i * primes[j] ] = phi[i] * (primes[j] - 1);
		}
	}
}
int pre[5000080];
struct Edge {int v, nxt;}a[5000080];
void dfs (int u) {
	f[1][0] = 0;
	For (i, 1, 4) f[u][i] = f[f[u][i - 1] ][i - 1];
	for (int i = pre[u]; i; i = a[i].nxt) {
		int v = a[i].v;
		dep[v] = dep[u] + 1;
		f[v][0] = u;
		dfs (v);
	}
}
int lca (int x, int y) {
	if (dep[x] <= dep[y]) swap (x, y);
	foR (i, 4, 0) if (dep[f[x][i] ] >= dep[y]) x = f[x][i];
	if (x == y) return x;
	foR (i, 4, 0) {
		if (f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	}
	return f[x][0];
}
void build (int l, int r, int k) {
	if (l == r) {
		sum[k] = dep[c[l] ];
		lc[k] = c[l];
		return;
	}
	int mid = l + r >> 1;
	build (l, mid, k << 1);
	build (mid + 1, r, k << 1 | 1);
	sum[k] = sum[k << 1] + sum[k << 1 | 1];
	lc[k] = lca (lc[k << 1], lc[k << 1 | 1]);
}
void update (int l, int r, int k, int x, int y) {
	if (sum[k] == r - l + 1) return;
	if (l == r) {
		lc[k] = f[lc[k] ][0];
		-- sum[k];
		return;
	}
	int mid = l + r >> 1;
	if (x <= mid) update (l, mid, k << 1, x, y);
	if (y > mid) update (mid + 1, r, k << 1 | 1, x, y);
	sum[k] = sum[k << 1] + sum[k << 1 | 1];
	lc[k] = lca (lc[k << 1], lc[k << 1 | 1]);
}
int querysum (int l, int r, int k, int x, int y) {
	if (x <= l && y >= r) return sum[k];
	int mid = l + r >> 1, res = 0;
	if (x <= mid) res = querysum (l, mid, k << 1, x, y);
	if (y > mid) res += querysum (mid + 1, r, k << 1 | 1, x, y);
	return res;
}
int querylca (int l, int r, int k, int x, int y) {
	if (x <= l && y >= r) return lc[k];
	int mid = l + r >> 1, res = 0;
	if (x <= mid) res = querylca (l, mid, k << 1, x, y);
	if (y > mid) res = (res == 0 ? querylca (mid + 1, r, k << 1 | 1, x, y) : lca (res, querylca (mid + 1, r, k << 1 | 1, x, y) ) );
	return res;
}
signed main () {
	dep[1] = 1;
	init ();
	For (i, 2, 5000000) {
		a[++ k] = {i, pre[phi[i] ]};
		pre[phi[i] ] = k;
	}
	dfs (1);
	cin >> n >> m;
	cnt = n;
	For (i, 1, n) cin >> c[i];
	build (1, n, 1);
	For (i, 1, m) {
		int op, x, y;
		cin >> op >> x >> y;
		if (op == 1) update (1, n, 1, x, y);
		else cout << querysum (1, n, 1, x, y) - (y - x + 1) * dep[querylca (1, n, 1, x, y)] << '\n';
	}
	return 0;
}
```


---

## 作者：ZillionX (赞：0)

> 给定一个长度为 $n$ 的数组 $a$，有 $m$ 次操作。操作 1 是将所有 $i \in [l,r]$ 的 $a_i$ 赋值为 $\varphi(a_i)$；操作 2 是询问将 $[l,r]$ 中的数变为同一个数，最少需要多少次“任取 $i \in [l,r]$，将 $a_i$ 赋值为 $\varphi(a_i)$”的操作。  
$n,m \le 10^5,V \le 5 \times 10^6$，3s，500MB。

小清新 DS 题，赛时想了几分钟就会了，但是没写。

设 $V$ 为值域，我们对 $[1,V]$ 间的所有数连边 $\varphi(i) \to i$。显然这样连出来的图一定是一棵树，因为 $\varphi(i) \in [1,i-1]$。

那么我们考虑题目中的操作映射到这棵树上是什么样的。容易发现，这相当于维护 $n$ 个指向树中结点的指针，操作 1 即将 $[l,r]$ 中的所有指针向父亲方向移动一步，操作 2 即询问 $[l,r]$ 中所有指针指向的所有节点的 LCA。

可以猜想这棵树的一定有一些特殊性质，否则操作 1 是非常难做的，事实上也的确如此：这棵树的树高最高仅为 23，也就是说树高是 $\mathcal O(\log V)$ 的。这也是一个经典结论，可以通过奇数变为其 $\varphi(x)$ 后一定为偶数，偶数变为其 $\varphi(x)$ 后一定减半证明。

现在我们只需要忽略掉操作 1 中所有已经跳到结点 $1$ 的指针，对剩下的指针暴力修改，这样的复杂度就是 $\mathcal O(n \log V)$，这部分具体可以通过在线段树上为一个值 $d$ 表示区间指针所指结点下标的最大值，递归时推出 $d=1$ 的区间来实现。

对于操作 2，直接在线段树上递推维护区间 LCA 即可，用树剖 LCA 容易实现，注意不要用 ST 表 LCA，否则会炸空间。

时间复杂度 $\mathcal O(n \log V + m \log^2 n)$。


```cpp
const int N=1e5+5,M=5e6+5,inf=1e9;
int n,m,a[N],tn,p[M],ph[M];
bool e[M];
void sev(int n){
	ph[1]=1,e[1]=1;
	for(int i=2;i<=n;i++){
		if(!e[i])ph[i]=i-1,p[++tn]=i;
		for(int j=1;j<=tn&&i*p[j]<=n;j++){
			if(!(i%p[j])){ph[i*p[j]]=ph[i]*p[j],e[i*p[j]]=1;break;}
			ph[i*p[j]]=ph[i]*ph[p[j]],e[i*p[j]]=1;
		}
	}
}
int V,tim,df[M],dep[M],fa[M],zs[M],sz[M],tp[M];
vct g[M];
void dfs1(int u){
	sz[u]=1;
	for(int v:g[u]){
		dep[v]=dep[u]+1,fa[v]=u,dfs1(v);
		if(sz[v]>sz[zs[u]])zs[u]=v;
		sz[u]+=sz[v];
	}
}
void dfs2(int u,int tf){
	df[u]=++tim,tp[u]=tf;
	if(!zs[u])return;
	dfs2(zs[u],tf);
	for(int v:g[u])if(v!=zs[u])dfs2(v,v);
}
int LCA(int x,int y){
	while(tp[x]!=tp[y]){
		if(dep[tp[x]]<dep[tp[y]])swap(x,y);
		x=fa[tp[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
int v[N*4],mn[N*4],mx[N*4],d[N*4],sm[N*4],lc[N*4];
#define ls (x<<1)
#define rs (x<<1|1)
void up(int x){
	d[x]=max(d[ls],d[rs]);
	mn[x]=min(mn[ls],mn[rs]);
	mx[x]=max(mx[ls],mx[rs]);
	sm[x]=sm[ls]+sm[rs];
	lc[x]=LCA(lc[ls],lc[rs]); 
}
void bd(int x,int l,int r){
	if(l==r){
		v[x]=d[x]=a[l];
		mn[x]=mx[x]=df[a[l]];
		sm[x]=dep[a[l]];
		lc[x]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	bd(ls,l,mid),bd(rs,mid+1,r);
	up(x);
}
void upd(int x,int l,int r,int L,int R){
	if(d[x]==1)return;
	if(l==r){
		v[x]=ph[v[x]];
		d[x]=v[x];
		mn[x]=df[v[x]];
		mx[x]=df[v[x]];
		sm[x]=dep[v[x]];
		lc[x]=v[x];
		return;
	}
	int mid=(l+r)>>1;
	if(L<=mid)upd(ls,l,mid,L,R);
	if(R>mid)upd(rs,mid+1,r,L,R);
	up(x);
}
int qrymn(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return mn[x];
	int mid=(l+r)>>1,as=inf;
	if(L<=mid)cmn(as,qrymn(ls,l,mid,L,R));
	if(R>mid)cmn(as,qrymn(rs,mid+1,r,L,R));
	return as;
}
int qrymx(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return mx[x];
	int mid=(l+r)>>1,as=-inf;
	if(L<=mid)cmx(as,qrymx(ls,l,mid,L,R));
	if(R>mid)cmx(as,qrymx(rs,mid+1,r,L,R));
	return as;
}
int qrysm(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return sm[x];
	int mid=(l+r)>>1,as=0;
	if(L<=mid)as=qrysm(ls,l,mid,L,R);
	if(R>mid)as+=qrysm(rs,mid+1,r,L,R);
	return as;
}
int qrylc(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return lc[x];
	int mid=(l+r)>>1,as=0;
	if(L<=mid)as=qrylc(ls,l,mid,L,R);
	if(R>mid){
		if(!as)as=qrylc(rs,mid+1,r,L,R);
		else as=LCA(as,qrylc(rs,mid+1,r,L,R));
	}
	return as;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],cmx(V,a[i]);
	sev(V);
	for(int i=2;i<=V;i++)g[ph[i]].pb(i);
	dfs1(1),dfs2(1,1);
	bd(1,1,n);
	while(m--){
		int op,l,r;
		cin>>op>>l>>r;
		if(op==1)upd(1,1,n,l,r);
		else{
			int lc=qrylc(1,1,n,l,r);
			cout<<qrysm(1,1,n,l,r)-dep[lc]*(r-l+1)<<endl;
		}
	}
	return 0;
}
/*
Coder: ZillionX
Code Time: 17min 35s
Debug Time: 19min 44s
done by ZillionX absolutely
solve by 2 admission
*/
```


---

## 作者：smallpeter (赞：0)

## 前言
赛场上没看的一道题，补题时被卡常了，所以来写一发题解~~咒骂~~记录一下。

## 题目大意

给你一个长度为 $n(n\le10^5)$ 的序列 $(a_i\le 5\times10^6)$，你需要支持两个操作：操作一，询问区间 $[l,r]$ 需要进行几次区间 $\varphi$ 赋值操作才能使得序列所有数都相同。$\varphi$ 覆盖操作指的是对一个数 $v$ 覆盖成 $\varphi(v)$。（注意，询问并不会真的对序列操作。）操作二，将区间 $[l,r]$ $\varphi$ 覆盖。

## 前置知识：欧拉函数计算方式

当 $x=\prod_{i=1}^k{a_i}^{b_i}$，$a_i$ 为质数且 $b_i$ 不为 0。

则 $\varphi(x)=x\times\prod_{i=1}^k\dfrac{a_i-1}{a_i}$

## 解法

我们可以转化一下题意，对某个数 $v$，向他的父节点 $\varphi(v)$ 连一条边。那么这个问题变成了支持区间 $\varphi$ 覆盖以及求一段区间的 $lca$。我们先看询问，我们知道一些数的 $lca$ 等同于 $dfn$ 最大的节点与 $dfn$ 最小的节点的 $lca$，于是我们可以维护一段区间内 $dfn$ 最大的节点与 $dfn$ 最小的节点。再看修改，通过打表我们发现一个数经过大约 $\log$ 次修改后就会变成 1（我其实没发现这点，别人提示了我才意识到的（））。这两个操作启示我们用 $ds$ 来维护，显然线段树是比较适合做这个东西的。由于每个节点修改的次数不会很多，我们可以考虑用势能线段树来维护。然后好像就没了？？

顺便一提由于树高大约是 $\log$ 级别的，所以可以暴力求 $lca$。

upd：复杂度近似 $V \times \log V+n\times \log n \times \log V$。

## 代码
```
// LUOGU_RID: 107739597
#include<bits/stdc++.h>
#pragma comment(linker, "/STACK:102400000,102400000") 
using namespace std;

#define LL long long

const LL N=1e5+10,M=5e6+10;

LL n,m,a[N],turn[M],p[M],dfn[M],f[M],dep[M],ys[M];

bool vis[M];

vector<LL> g[M];

struct Tree{
	LL mx;
	LL mn;
	LL mxv;
	LL sum;
}tree[N<<2];

LL cnt[M],cnting;

void dfs(LL u,LL fa){
	if(fa==-1) dep[u]=0;
	else dep[u]=dep[fa]+1;
	dfn[u]=++cnting;
	ys[cnting]=u;
	LL sz=g[u].size();
	for(LL i=0;i<sz;i++){
		LL v=g[u][i];
		if(v==fa) continue;
		dfs(v,u);
	}
}

LL lca(LL u,LL v){
	while(u!=v){
		if(dep[u]>dep[v]) swap(u,v);
		v=f[v];
	}
	return u;
}

void init(){
	vis[0]=vis[1]=true;
	for(LL i=2;i<M;i++){
		for(LL j=i*i;j<M;j+=i){
			vis[j]=true;
			if(p[j]==0) p[j]=i;
		}
	}
	turn[1]=1;
	for(LL i=2;i<M;i++){
		LL ans=i,nw=i;
		while(vis[nw]){
			LL gt=p[nw];
			cnt[gt]=0;
			nw/=gt;
		}
		cnt[nw]=0;
		nw=i;
		while(vis[nw]){
			LL gt=p[nw];
			if(!cnt[gt]){
				ans/=gt;
				ans*=(gt-1);
			}
			cnt[gt]++;
			nw/=gt;
		}
		if(!cnt[nw]){
			ans/=nw;
			ans*=(nw-1);
		}
		turn[i]=ans;
		g[ans].push_back(i);
		f[i]=ans;
	}
	dfs(1,-1);
	return ;
}

const LL INF=1e9;

void merge(Tree &nw,Tree lf,Tree rt){
	nw.sum=lf.sum+rt.sum;
	nw.mn=min(lf.mn,rt.mn);
	nw.mx=max(lf.mx,rt.mx);
	nw.mxv=max(lf.mxv,rt.mxv);
}

void pushup(LL w,LL l,LL r){
	merge(tree[w],tree[w<<1],tree[w<<1|1]);
	return ;
}

Tree initx(){
	Tree ans;
	ans.mn=INF;
	ans.mx=-INF;
	ans.mxv=-1;
	return ans;
}

void build(LL l,LL r,LL w){
	tree[w]=initx();
	if(l==r){
		tree[w].sum=dep[a[l]];
		tree[w].mn=dfn[a[l]];
		tree[w].mx=dfn[a[l]];
		tree[w].mxv=a[l];
		return ;
	}
	LL mid=l+r>>1;
	build(l,mid,w<<1);
	build(mid+1,r,w<<1|1);
	pushup(w,l,r);
	return ;
}

Tree query(LL l,LL r,LL w,LL lx,LL rx){
	if(lx>rx) return initx();
	if(l>=lx&&r<=rx){
		return tree[w];
	} 
	LL mid=l+r>>1;
	if(mid<lx) return query(mid+1,r,w<<1|1,lx,rx);
	if(mid>=rx) return query(l,mid,w<<1,lx,rx);
	Tree lf=query(l,mid,w<<1,lx,rx),rt=query(mid+1,r,w<<1|1,lx,rx),ans;
	merge(ans,lf,rt);
	return ans;
}

void modify(LL l,LL r,LL w,LL lx,LL rx){
	LL mid=l+r>>1;
	if(l>=lx&&r<=rx){
		if(tree[w].mxv==1) return ;
		if(l==r){
			LL v=tree[w].mxv;
			LL tv=turn[v];
			tree[w].mn=dfn[tv];
			tree[w].mx=dfn[tv];
			tree[w].mxv=tv;
			tree[w].sum=dep[tv];
			return ;
		} 
	}
	if(mid>=lx) modify(l,mid,w<<1,lx,rx);
	if(mid<rx) modify(mid+1,r,w<<1|1,lx,rx);
	pushup(w,l,r);
}

int main(){
	init();
	scanf("%lld%lld",&n,&m);
	for(LL i=1;i<=n;i++) scanf("%lld",&a[i]);
	build(1,n,1);
	while(m--){
		LL op,l,r;
		scanf("%lld%lld%lld",&op,&l,&r);
		if(op==2){
			Tree ask=query(1,n,1,l,r);
			printf("%lld\n",ask.sum-dep[lca(ys[ask.mn],ys[ask.mx])]*(r-l+1));
		}
		else{
			modify(1,n,1,l,r);
		}
	}
	return 0;
} 
```

我一开始建了双向边导致我疯狂 TLE，警钟敲烂 /hsh/hsh/hsh

---

## 作者：小木虫 (赞：0)

### Preface  
前排拜谢尺子姐姐！  
本题为简单题，但是比较麻烦。  
### Problem  
给你一个数列 $a$，需要维护两种操作：  
1.将 $[l,r]$ 内的数字全部变为自身的 $\varphi$。  
2.每次操作你可以将 $[l,r]$ 内任意一个数字变为自身的 $\varphi$，问你最少需要几次这样的操作使 $[l,r]$ 内的数字相同，询问相互独立。  

### Solution  
首先，经典结论，$\varphi$ 函数每两次至少折半，这意味着我们最多会对一个数进行 $\log V$ 次变换操作，对于操作 1，我们每次抓出子段内最大的数字对它进行操作，然后打上已操作标记，若抓到的最大已经是 1，这意味着我们可以停止操作了。这个操作可以借助线段树实现。  

然后我们考虑操作 2。  
你考虑，这些数字在操作过程中会逐渐合并到一起，直到他们都变成一个数，这和树的形式很像。  
我们发现我们可以将一个数的 $\varphi$ 看成他的父亲，这样所有值域内的数字就会组成一棵树。  

这样的话，我们的操作 2 就是求出所有区间内数字的 LCA 的深度 $v$ 之后，求出区间内所有数字的深度之和 $sum$，答案就是 $sum-v\times (r-l+1)$。  

这些操作也可以通过线段树解决。  
由于树高是 $\log V$ 的，所以求 LCA 不需要倍增。  

现在的问题就是如何求所有区间内数字的 LCA。  
你发现，所有数字的 LCA 就是 dfs 序最小的数和 dfs 序最大的数的 LCA。  

然后我们再在线段树上维护一个 dfs 序的信息。  

那么这个题就做完了，常数比较大，如果 C++14 过不去可以试试 C++20。  

code：  
```cpp
#include <bits/stdc++.h>
#define int long long
#define mp make_pair
#define fir first
#define sec second
using namespace std;
const int N=2e5+10;
const int M=5e6+10;
int n,m,a[N],op,l,r,phi[M],is_prime[M],dep[M],dfn[M],fa[M],cnt;
vector <int> prime;
vector <int> edge[M];
void dfs(int u){
	dfn[u]=++cnt;dep[u]=dep[fa[u]]+1;
	for(auto v:edge[u])dfs(v);
}
void init(){
	for(int i=2;i<=5e6;i++){
		if(!is_prime[i])prime.push_back(i),phi[i]=i-1;
		for(auto j:prime){
			if(i*j>5e6)break;
			is_prime[i*j]=1;
			if(i%j==0){phi[i*j]=phi[i]*j;break;}
			phi[i*j]=phi[i]*(j-1);
		}
	}
	for(int i=1;i<=5e6;i++)
		edge[phi[i]].push_back(i),fa[i]=phi[i];
	dfs(1);
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]>dep[y])x=fa[x];
	if(x==y)return x;
	while(x!=y)x=fa[x],y=fa[y];
	return x;
}
int maxval[N<<2],maxpos[N<<2],minpos[N<<2],depsum[N<<2];
void pushup(int rt){
	if(a[maxval[rt*2]]>a[maxval[rt*2+1]])
		maxval[rt]=maxval[rt*2];
	else maxval[rt]=maxval[rt*2+1];
	if(dfn[a[maxpos[rt*2]]]>dfn[a[maxpos[rt*2+1]]])
		maxpos[rt]=maxpos[rt*2];
	else maxpos[rt]=maxpos[rt*2+1];
	if(dfn[a[minpos[rt*2]]]<dfn[a[minpos[rt*2+1]]])
		minpos[rt]=minpos[rt*2];
	else minpos[rt]=minpos[rt*2+1];
	depsum[rt]=depsum[rt*2]+depsum[rt*2+1];
}
void build(int rt,int left,int right){
	if(left==right){
		minpos[rt]=maxpos[rt]=maxval[rt]=left;
		depsum[rt]=dep[a[left]];
		return ;
	}int mid=(left+right)/2;
	build(rt*2,left,mid);
	build(rt*2+1,mid+1,right);
	pushup(rt);
}
void update(int rt,int left,int right,int x){
	if(left==right){depsum[rt]=dep[a[x]];return;}
	int mid=(left+right)/2;
	if(x<=mid)update(rt*2,left,mid,x);
	else update(rt*2+1,mid+1,right,x);
	pushup(rt);
}
int query_maxval(int rt,int left,int right,int L,int R){
	if(left>=L&&right<=R)return maxval[rt];
	int mid=(left+right)/2;
	if(L<=mid&&R>mid){
		int lval=query_maxval(rt*2,left,mid,L,R);
		int rval=query_maxval(rt*2+1,mid+1,right,L,R);
		if(a[lval]>a[rval])return lval;
		else return rval;
	}else if(L<=mid){
		return query_maxval(rt*2,left,mid,L,R);
	}else return query_maxval(rt*2+1,mid+1,right,L,R);
}
pair <int,int> query_maxipos(int rt,int left,int right,int L,int R){
	//if(rt)cout<<left<<" "<<right<<" "<<L<<" "<<R<<" "<<rt<<endl;
	if(left>=L&&right<=R)return mp(minpos[rt],maxpos[rt]);
	int mid=(left+right)/2;
	if(L<=mid&&R>mid){
		pair <int,int> lval=query_maxipos(rt*2,left,mid,L,R);
		pair <int,int> rval=query_maxipos(rt*2+1,mid+1,right,L,R);
		pair <int,int> res;
		if(dfn[a[lval.fir]]<dfn[a[rval.fir]])
			res.fir=lval.fir;
		else res.fir=rval.fir;
		if(dfn[a[lval.sec]]>dfn[a[rval.sec]])
			res.sec=lval.sec;
		else res.sec=rval.sec;
		return res;
	}else if(L<=mid){
		return query_maxipos(rt*2,left,mid,L,R);
	}else return query_maxipos(rt*2+1,mid+1,right,L,R);
}
int query_sum(int rt,int left,int right,int L,int R){
	if(left>=L&&right<=R)return depsum[rt];
	int mid=(left+right)/2;int res=0;
	if(L<=mid)res+=query_sum(rt*2,left,mid,L,R);
	if(mid+1<=R)res+=query_sum(rt*2+1,mid+1,right,L,R);
	return res;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;init();
	for(int i=1;i<=n;i++)
		cin>>a[i];
	build(1,1,n);
	while(m--){
		cin>>op>>l>>r;
		if(op==1){
			vector < pair<int,int> > upd;
			int Q=query_maxval(1,1,n,l,r);
			while(a[Q]!=1){
				//cout<<Q<<" "<<a[Q]<<"\n";
				upd.push_back(mp(Q,phi[a[Q]])),a[Q]=1;
				update(1,1,n,Q),Q=query_maxval(1,1,n,l,r);
			}
			for(auto now:upd)
				a[now.fir]=now.sec,update(1,1,n,now.fir);
		}else{
			pair <int,int> maxi=query_maxipos(1,1,n,l,r);
			int lca=LCA(a[maxi.fir],a[maxi.sec]);
			//cout<<a[maxi.fir]<<" "<<a[maxi.sec]<<"\n";
			//cout<<lca<<" "<<dep[lca]<<"\n";
			cout<<query_sum(1,1,n,l,r)-dep[lca]*(r-l+1)<<"\n";
		}
	}
	return 0;
}
```


---

## 作者：Rainsleep (赞：0)

首先拜谢 [Jiyuu_no_Tsubasa ](https://www.luogu.com.cn/user/261981) 和 [qidirj](https://www.luogu.com.cn/user/371468)，码力思维好题。

看到这样在序列上的区修，首先想到用线段树和一些懒标记这样的东西维护，不过发现 $\varphi$ 这东西并不具有任何性质可以打标记，于是类似于区间开根的操作，我们考虑一个数最多经过几次取 $\varphi$ 可以变成 $1$。

考虑一个上界，令 $p$ 为质数，则 $\varphi(p) = p -1$，因为当 $p \ne3$ 时， $p - 1$ 必然为偶合数，而小于 $p - 1$ 的偶数都不可能对下一次取 $\varphi$ 造成贡献，则 $\varphi(p - 1) \le \dfrac{p - 1}{2}$。如此迭代下去，不难上界即为 $O(2\log) = O(\log)$，即不超过 $\log$ 次取 $\varphi$ 我们就能将一个数字归一，这位我们接下来的暴力操作提供了复杂度的支撑。

还是类似于维护区间开根的做法，我们对线段树里每个区间维护一个 $\max$，当区间 $\max \le 1$ 时不需要再操作该区间。

对于操作 $2$，我们需要一些启发式的思想。

对于每一次取 $\varphi$，若将该过程看作是连一条从 $x$ 到 $\varphi(x)$ 的边，那么使得区间归一的询问，实际上就是询问这一串数在以 $\varphi$ 建树的树上 LCA。那么线性筛预处理出 $\varphi$ 树，再预处倍增 LCA 即可。

如果你尝试分析 $\varphi$ 树的高度，你会发现，因为不超过 $\log$ 次迭代就能归一，所以这恰好说明了树高恰好为 $\log W$，这同时为我们的 LCA 提供了优秀的性质，套上倍增即可做到 $O(\log\log W)$ 的复杂度。

对于时间复杂度，令 $W$ 为值域，对于线性筛与建树的部分，我们有 $O(W)$ 的开销；对于预处理倍增的过程，我们有 $O(W\log W)$ 的开销；对于操作，我们发现由于线段树和维护 LCA 的修改查询，所以两者复杂度都为 $O(\log n\log\log W)$，所以总
时间复杂度即为 $O(W + W\log W+m\log n\log\log W) = O(W \log W + m\log n\log\log W)$。

[code](https://codeforces.com/contest/1797/submission/213450927)

---

