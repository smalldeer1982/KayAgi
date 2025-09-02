# [ABC138D] Ki

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc138/tasks/abc138_d

$ 1 $ から $ N $ までの番号がついた $ N $ 個の頂点を持つ根付き木が与えられます。 この木の根は頂点 $ 1 $ で、$ i $ 番目の辺 $ (1\ \leq\ i\ \leq\ N\ -\ 1) $ は頂点 $ a_i $ と頂点 $ b_i $ を結びます。

各頂点にはカウンターが設置されており、はじめすべての頂点のカウンターの値は $ 0 $ です。

これから、以下のような $ Q $ 回の操作が行われます。

- 操作 $ j $ $ (1\ \leq\ j\ \leq\ Q) $: 頂点 $ p_j $ を根とする部分木に含まれるすべての頂点のカウンターの値に $ x_j $ を足す。

すべての操作のあとの各頂点のカウンターの値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ a_i\ <\ b_i\ \leq\ N $
- $ 1\ \leq\ p_j\ \leq\ N $
- $ 1\ \leq\ x_j\ \leq\ 10^4 $
- 与えられるグラフは木である。
- 入力中の値はすべて整数である。

### Sample Explanation 1

この入力中の木は次のようなものです。 !\[図\](https://img.atcoder.jp/ghi/c771b2231be06af79a9994cbe6867552.png) 各操作で、頂点のカウンターの値は次のように変化します。 - 操作 $ 1 $: 頂点 $ 2 $ を根とする部分木に含まれるすべての頂点、すなわち頂点 $ 2,\ 3,\ 4 $ のカウンターの値に $ 10 $ を足す。頂点 $ 1,\ 2,\ 3,\ 4 $ のカウンターの値はそれぞれ $ 0,\ 10,\ 10,\ 10 $ となる。 - 操作 $ 2 $: 頂点 $ 1 $ を根とする部分木に含まれるすべての頂点、すなわち頂点 $ 1,\ 2,\ 3,\ 4 $ のカウンターの値に $ 100 $ を足す。頂点 $ 1,\ 2,\ 3,\ 4 $ のカウンターの値はそれぞれ $ 100,\ 110,\ 110,\ 110 $ となる。 - 操作 $ 3 $: 頂点 $ 3 $ を根とする部分木に含まれるすべての頂点、すなわち頂点 $ 3 $ のカウンターの値に $ 1 $ を足す。頂点 $ 1,\ 2,\ 3,\ 4 $ のカウンターの値はそれぞれ $ 100,\ 110,\ 111,\ 110 $ となる。

## 样例 #1

### 输入

```
4 3
1 2
2 3
2 4
2 10
1 100
3 1```

### 输出

```
100 110 111 110```

## 样例 #2

### 输入

```
6 2
1 2
1 3
2 4
3 6
2 5
1 10
1 10```

### 输出

```
20 20 20 20 20 20```

# 题解

## 作者：_Life_ (赞：3)

### 题意
给定一棵树，每次修改将 $u$ 的子树加上 $val$，输出最后每个节点的值。

### 题解
每次修改的时候只用在子树的根节点上打个标记，最后 `dfs` 遍历整颗树，`x[u]+=x[fa];` 下传标记即可。

时间复杂度 $O(n)$

### 代码
包含 `C++11` 语法，请谨慎食用
```cpp
#include<cstdio>
#include<vector>
using namespace std;
int n,q,x[200005];
vector <int> g[200005];
void dfs(int u,int fa)
{
	x[u]+=x[fa];
	for(int v:g[u])
		if(v!=fa)
			dfs(v,u);
}
int main()
{
	scanf("%d %d",&n,&q);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d %d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1,a,b;i<=q;i++)
		scanf("%d %d",&a,&b),x[a]+=b;
	dfs(1,0);
	for(int i=1;i<=n;i++)printf("%d ",x[i]);
}
```

---

## 作者：_xbn (赞：3)

怎么都是树上差分，树链剖分表示不服，我们来分析这个问题，对于修改

操作，直接套用线段树区间修改，对于最后的询问，我们可以直接询问一个

点到他自己的距离，这就是它修改后的值，其余就是树链剖分的模板啦。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2e5+1e3;
int n,m,temp[N],tag[N*6],tree[N*6],mod,head[N],cnt0=0,root;
int cnt=0;
int siz[N];//   结点的子树大小
int son[N];//   结点的重儿子编号
int fa[N];//    结点的父亲的编号
int deep[N];//    结点的深度
int tp[N];//   节点对应的链的开始节点编号 
int dfn[N];//   节点的dfs序的编号 
int a[N];//    根据dfs序重新建立的数组 
struct edge
{
	int to,nxt;
}e[2*N];
void add(int u,int v)
{
	e[++cnt0].to=v;
	e[cnt0].nxt=head[u];
	head[u]=cnt0;
}
//线段树 begin 
inline void push_up(int k)
{
	tree[k]=(tree[k*2]+tree[k*2+1]);
}
void build(int s,int t,int p)
{
	tag[p]=0;
	if(s==t)
	{
		tree[p]=a[s];
		return;
	}
	int mid=(s+t)/2;
	build(s,mid,p*2);
	build(mid+1,t,p*2+1);
	push_up(p);
}
inline void f(int p,int l,int r,int k)
{
    tag[p]+=k;
    tree[p]+=k*(r-l+1);
}

inline void push_down(int p,int l,int r)
{
	int mid=(l+r)/2;
	f(p<<1,l,mid,tag[p]);
    f(p<<1|1,mid+1,r,tag[p]);
    tag[p]=0;
}
inline void update(int s,int t,int l,int r,int p,int k)
{
	if(l<=s&&t<=r)
	{
		tree[p]+=(t-s+1)*k;
		tag[p]+=k;
		return;
	}
	push_down(p,s,t);
	int mid=(s+t)>>1;
    if(l<=mid)update(s,mid,l,r,p<<1,k);
    if(r>mid) update(mid+1,t,l,r,p<<1|1,k);
    push_up(p);
}
int getsum(int l, int r, int s, int t, int p)
{
    int res=0;
    if(l<=s&&t<=r)return tree[p];
    int mid=(s+t)/2;
    push_down(p,s,t);
    if (l <= mid) res += getsum(l, r, s, mid, p * 2);
    if (r > mid) res += getsum(l, r, mid + 1, t, p * 2 + 1);
    return res;
}
//线段树 end 

//树链剖分 begin
void dfs1(int u,int f)
{
	int MAX=0;
	fa[u]=f;
	deep[u]=deep[f]+1;
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[MAX]) 
		{
			MAX=v;
		}
	}
	son[u]=MAX;
}
void dfs2(int u,int h)
{
	cnt++;
	dfn[u]=cnt;
	tp[u]=h;
	a[cnt]=temp[u];
	if(son[u]==0)return;
	dfs2(son[u],h);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
	
}
void inc(int x,int y,int z)
{
	while (tp[x]!=tp[y])
	{
		if (deep[tp[x]]<deep[tp[y]]) swap(x,y);
		update(1,n,dfn[tp[x]],dfn[x],1,z);
		x=fa[tp[x]];
	}
	if (deep[x]>deep[y]) swap(x,y);
	update(1,n,dfn[x],dfn[y],1,z);
}
int query(int x,int y)
{
	int ans=0;
	while (tp[x]!=tp[y])
	{
		if (deep[tp[x]]<deep[tp[y]]) swap(x,y);
		ans=(ans+getsum(dfn[tp[x]],dfn[x],1,n,1));
		x=fa[tp[x]];
	}
	if (deep[x]>deep[y]) swap(x,y);
	return (ans+getsum(dfn[x],dfn[y],1,n,1));
}
//树链剖分 end 
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n-1;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	root=1;
	dfs1(root,0);
	dfs2(root,root);
	build(1,n,1);
	for(int i=1;i<=m;i++)
	{
		int x,y,z,Q;
			scanf("%lld%lld",&x,&y);
			update(1,n,dfn[x],dfn[x]+siz[x]-1,1,y);
	}
	for(int i=1;i<=n;i++)
	{
		cout<<query(i,i)<<" ";
	}
	return 0;
}
```


---

## 作者：loser_seele (赞：1)

1.94s 卡过去了，喜提最劣解。

看见子树加的题目只有树上差分和树剖怎么能行，于是不难想到 [Sone1](https://www.luogu.com.cn/problem/P5649) 这题的 LCT 做法。

正常的 LCT 是没法实现子树加功能的，但是这题用 LCT 维护虚子树实现了子树加的功能，具体实现那题的题解有讲。实际上原理是在切换虚链和实链的时候维护虚子树和子树的值，虚子树的用法可以参考 [这题](https://www.luogu.com.cn/problem/P4219) 的实现。

于是就得到了一个 $ \mathcal{O}(n\log{n}) $ 的 LCT 做法，实际上因为极度卡常所以不保证每次提交本代码都能通过，并且使用了火车头卡常，具体的火车头代码 [link](https://www.luogu.com.cn/paste/q34v4ssz) 放在这里了。

在具体的实现上参考的是 Sone1 最后一篇题解的代码所以相似度极高。

代码：（已去掉火车头）

```cpp
#import <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int inf=0x7fffffff;
int n,m,x,y,opt,root;
int v,ans;
char ch;
int son[N][2],anc[N],sz[N][3],rt[N],rev[N];
int sum[N][3],w[N],add[N][2],cov[N][2],mn[N][3],mx[N][3];
void read(int &x)
{
	x=0;ch=getchar();
	while(ch<'0'||ch>'9')
    ch=getchar();
	while(ch>='0'&&ch<='9')
    x=x*10+ch-'0',ch=getchar();
}
void write(int x)
{
	if(x>=10)
    write(x/10);
	putchar('0'+x%10);
}
void add_(int x,int v,bool b);
void cov_(int x,int v,bool b);
struct leafy_Splay
{
	int son[N<<2][2],anc[N<<2],sz[N<<2],wsz[N<<2],tot;
    queue<int> q;
	int sum[N<<2],wsum[N<<2],add[N<<2],cov[N<<2];
	void init(int x)
    {
		cov[x]=inf;
		son[x][0]=son[x][1]=anc[x]=sz[x]=wsz[x]=sum[x]=wsum[x]=add[x]=0;
	}
	void add_1(int x,int v)
    {
		add[x]+=v;
		if(sz[x])
        sum[x]+=sz[x]*v;
		if(x<=n)
        wsum[x]+=wsz[x]*v,add_(x,v,1),add_(x,v,0);
	}
	void cov_1(int x,int v)
    {
		cov[x]=v;
        add[x]=0;
		if(sz[x])
        sum[x]=sz[x]*v;
		if(x<=n)
        wsum[x]=wsz[x]*v,cov_(x,v,1),cov_(x,v,0);
	}
	void fix(int x)
    {
		if(!x)
        return;
		sum[x]=sum[son[x][0]]+sum[son[x][1]]+wsum[x];
		sz[x]=sz[son[x][0]]+sz[son[x][1]]+wsz[x];
	}
	bool p(int x){return son[anc[x]][1]==x;}
	int newnode()
    {
		if(!q.empty())
        {
			int x=q.front();
			return q.pop(),x;
		}
		return init(++tot),tot;
	}
	void pushdown(int x)
    {
		if(cov[x]!=inf)
        {
			if(son[x][0])
            cov_1(son[x][0],cov[x]);
			if(son[x][1])
            cov_1(son[x][1],cov[x]);
			cov[x]=inf;
		}
		if(add[x])
        {
			if(son[x][0])
            add_1(son[x][0],add[x]);
			if(son[x][1])
            add_1(son[x][1],add[x]);
			add[x]=0;
		}
	}
	void pushall(int x)
    {
		if(anc[x])
        pushall(anc[x]);
		pushdown(x);
	}
	void rotate(int x)
    {
		int y=anc[x],xx=anc[y];
		bool b=p(x),bb=p(y);
		anc[x]=xx;
		if(xx)
        son[xx][bb]=x;
		son[y][b]=son[x][b^1];
		anc[son[x][b^1]]=y;
		son[x][b^1]=y;
		anc[y]=x;
		fix(y);
		fix(x);
		fix(xx);
	}
	void splay(int x,int y)
    {
		pushall(x);
		for(int i=anc[x];i=anc[x],i!=y;rotate(x))
        if(anc[i]!=y)
        {
			if(p(x)==p(i))
            rotate(i);
			else 
            rotate(x);
		}
	}
	void ins(int x,int y,int sum_,int sz_,int mn_,int mx_)
    {
		wsum[x]=sum_,wsz[x]=sz_;
        fix(x);
		int tmp=rt[y],f=0;
        pushdown(tmp);
		if(!son[rt[y]][0])
        return anc[son[rt[y]][0]=x]=rt[y],fix(rt[y]);
		while(1)
        {
			if(!tmp)
            {
				tmp=newnode();
				anc[son[anc[f]][p(f)]=tmp]=anc[f];
				son[tmp][x>f]=x;
                anc[x]=tmp;
				son[tmp][x<f]=f;
                anc[f]=tmp;
				fix(f);
                fix(tmp);
                fix(anc[tmp]);
				return splay(tmp,rt[y]);
			}
			pushdown(tmp);
			f=tmp;
            tmp=son[tmp][x>tmp];
		}
	}
	void clear(int x)
    {
    init(x);
    if(x>2*n)
    q.push(x);
    }
	void del(int x,int y)
    {
		if(anc[x]==rt[y])
        return son[rt[y]][0]=0,fix(rt[y]),clear(x);
		int yy=anc[x],xx=anc[yy];
        bool b=p(x),bb=p(yy);
		if(xx==rt[y])
        {
			anc[son[rt[y]][0]=son[yy][b^1]]=rt[y];
			clear(x),clear(yy),fix(rt[y]);
			return;
		}
		anc[son[xx][bb]=son[yy][b^1]]=xx;
		clear(x);
        clear(yy);
        fix(xx);
        splay(xx,rt[y]);
        fix(rt[y]);
	}
	void display(int x,int xx,int sum_,int sz_,int mn_,int mx_,int y)
    {
		wsum[xx]=sum_,wsz[xx]=sz_;
        fix(xx);
		int yy=anc[x];
		anc[son[yy][p(x)]=xx]=yy;
		clear(x);
        fix(yy);
        if(yy!=rt[y])
        splay(yy,rt[y]);
        fix(rt[y]);
	}
}S;
void update(int x)
{
	sz[x][2]=sz[x][0]+sz[x][1];
	sum[x][2]=sum[x][0]+sum[x][1];
}
void rev_(int x)
{
rev[x]^=1;
son[x][0]^=son[x][1]^=son[x][0]^=son[x][1];
}
void add_(int x,int v,bool b)
{
	add[x][b]+=v;
	if(sz[x][b])
    sum[x][b]+=sz[x][b]*v;
	if(b)
    S.add_1(rt[x],v);
	else 
    w[x]+=v;
	update(x);
}
void cov_(int x,int v,bool b)
{
	cov[x][b]=v;
    add[x][b]=0;
	if(sz[x][b])
    sum[x][b]=sz[x][b]*v;
	if(b)
    S.cov_1(rt[x],v);
	else 
    w[x]=v;
	update(x);
}
bool p(int x)
{
return son[anc[x]][1]==x;
}
bool isroot(int x)
{
return son[anc[x]][0]!=x&&son[anc[x]][1]!=x;
}
void S_display(int x,int xx,int y)
{
	S.display(x,xx,sum[xx][2],sz[xx][2],mn[xx][2],mx[xx][2],y);
}
void S_ins(int x,int y)
{
	S.ins(x,y,sum[x][2],sz[x][2],mn[x][2],mx[x][2]);
}
void fix(int x)
{
	if(!x)
    return;
	
	sz[x][0]=sz[son[x][0]][0]+sz[son[x][1]][0]+1;
	sz[x][1]=sz[son[x][0]][1]+sz[son[x][1]][1]+S.sz[rt[x]];
	
	sum[x][0]=sum[son[x][0]][0]+sum[son[x][1]][0]+w[x];
	sum[x][1]=sum[son[x][0]][1]+sum[son[x][1]][1]+S.sum[rt[x]];
	
	update(x);
}
void pushdown(int x)
{
	if(rev[x])
    {
		if(son[x][0])
        rev_(son[x][0]);
		if(son[x][1])
        rev_(son[x][1]);
		rev[x]=0;
	}
	if(cov[x][0]!=inf)
    {
		if(son[x][0])
        cov_(son[x][0],cov[x][0],0);
		if(son[x][1])
        cov_(son[x][1],cov[x][0],0);
		cov[x][0]=inf;
	}
	if(add[x][0])
    {
		if(son[x][0])
        add_(son[x][0],add[x][0],0);
		if(son[x][1])
        add_(son[x][1],add[x][0],0);
		add[x][0]=0;
	}
	if(cov[x][1]!=inf)
    {
		if(son[x][0])
        cov_(son[x][0],cov[x][1],1);
		if(son[x][1])
        cov_(son[x][1],cov[x][1],1);
		cov[x][1]=inf;
	}
	if(add[x][1])
    {
		if(son[x][0])
        add_(son[x][0],add[x][1],1);
		if(son[x][1])
        add_(son[x][1],add[x][1],1);
		add[x][1]=0;
	}
}
void pushall(int x)
{
	if(!isroot(x))
    pushall(anc[x]);
	pushdown(x);
}
void pushall_(int x)
{
	if(!isroot(x))
    pushall_(anc[x]);
	else if(anc[x])
    {
		pushall_(anc[x]);
		S.pushall(x);
	}
	pushdown(x);
}
void rotate(int x)
{
	int y=anc[x],xx=anc[y];
	bool b=p(x),bb=p(y);
	anc[x]=xx;
	if(!isroot(y))
    son[xx][bb]=x;
	son[y][b]=son[x][b^1];
	anc[son[x][b^1]]=y;
	son[x][b^1]=y;
	anc[y]=x;
	fix(y);
	fix(x);
	fix(xx);
}
int findrt(int x)
{
	if(isroot(x))
    return x;
	return findrt(anc[x]);
}
void splay(int x)
{
	pushall(x);
	int y=findrt(x);
	if(anc[y]&&x!=y)
    S.display(y,x,sum[y][2],sz[y][2],mn[y][2],mx[y][2],anc[y]);
	for(int i=anc[x];i=anc[x],!isroot(x);rotate(x))
    if(!isroot(i))
    {
		if(p(i)==p(x))
        rotate(i);
		else 
        rotate(x);
	}
}
int access(int x)
{
	int y=0;
	pushall_(x);
	for(;x;y=x,x=anc[x])
    {
		splay(x);
		if(y&&son[x][1])
        S_display(y,son[x][1],x);
		else if(!y&&son[x][1])
        S_ins(son[x][1],x);
		else if(y&&!son[x][1])
        S.del(y,x);
		son[x][1]=y;fix(x);
	}
	return y;
}
void makeroot(int x)
{
	access(x);
	splay(x);
	rev_(x);
}
void split(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
}
void link(int x,int y)
{
	split(x,y);
	anc[x]=y;
	S_ins(x,y);
	fix(y);
}
void subtree_add(int x,int v)
{
	split(root,x);
	w[x]+=v;
	S.add_1(rt[x],v);
	fix(x);
}
void subtree_cov(int x,int v)
{
	split(root,x);
	w[x]=v;
	S.cov_1(rt[x],v);
	fix(x);
}
int pre(int x)
{
	pushdown(x=son[x][0]);
	while(son[x][1])
    pushdown(x=son[x][1]);
	return splay(x),x;
}
int lca(int x,int y)
{
	makeroot(root);
	access(x);
	return access(y);
}
void cut(int x,int y)
{
	split(x,y);
	anc[x]=son[y][0]=0;
	fix(y);
}
void move(int x,int xx)
{
	if(lca(x,xx)==x)
    return;
	split(root,x);
	int y=pre(x);
	cut(x,y);
	link(x,xx);
}
int xx[N],yy[N];
signed main()
{
	read(n);
    read(m);
    root=1;
    S.tot=n<<1;
    for(int i=1;i<=n;i++)
    {
		w[i]=0;
		fix(i);
		S.init(rt[i]=i+n);
		cov[i][0]=cov[i][1]=inf;
	}
	for(int i=1;i<n;i++)
    read(xx[i]),read(yy[i]);
	for(int i=1;i<n;i++)
    link(xx[i],yy[i]);
	while(m--)
    {
        read(x);
        read(v);
        subtree_add(x,v);
    }
    for(int i=1;i<=n;i++)
    split(i,i),write(sum[i][0]),cout<<' ';
}
```


---

## 作者：lkjzyd20 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/AT4848)
___

### 思路

这道题，如果一边输入一边 Dfs，肯定会超时的。

那么，我们注意到题目中说的一句话：

**每次操作将 $p_i$ 的子树中所有点的计数器增加 $x_i$。**

那么可以离线操作，进行**差分**！！！

我们在输入的时候把差分数组弄好，然后进行 Dfs，Dfs 的同时，一边记录答案，一边差分。

代码如下：

```cpp
#include <iostream>

using namespace std;

const int N = 4e5 + 10;

void add (int, int) ;
void dfs (int, int, int) ;
void Ios () ;

int n, m;
int tot;
int ans[N];
int pre[N], son[N], now[N];
int b[N];

main () {
	Ios () ;
	
	cin >> n >> m;

	for (int i = 1, x, y; i < n; ++ i) {
		cin >> x >> y;
		
		// 连边。
		add (x, y) ;
		add (y, x) ;
	}

	for (int i = 1, x, y; i <= m; ++ i) {
		cin >> x >> y;
		// 差分数组统计答案。
		b[x] += y;
	}

	dfs (1, 0, 0) ;

	for (int i = 1; i <= n; ++ i)
		cout << ans[i] << " ";
}

// 第一个参数代表当前节点的编号，第二个参数代表当前节点的父亲节点，第三个参数代表差分的值。
void dfs (int x, int fa, int sum) {
	// 记录答案。
	ans[x] += b[x] + sum;
	
	// 差分
	sum += b[x];

	// dfs
	for (int i = now[x]; i; i = pre[i])
		if (son[i] != fa)
			dfs (son[i], x, sum) ;
}

// 建图。
void add (int x, int y) {
	pre[++ tot] = now[x];
	son[tot] = y;
	now[x] = tot;
}

// cin 加速。
void Ios () {
	ios :: sync_with_stdio (0) ;
	cin.tie () ;
	cout.tie () ;
}
```

### 完结撒花 $\sim\sim\sim$

---

## 作者：lsj2009 (赞：1)

## 题目大意
给定一个有 $n$ 个节点的树，进行 $m$ 次操作，每次操作形如 ``x val``，把以 $x$ 节点为根的子树的所有节点的权值 $+val$。
## 思路
我们可以参考线段树区间修、区间查时所用的****懒标记——或者说是延迟标记****，它将一个改动 $x$ 但暂时用不到的值保存在 $x$ 节点的若干级祖先 $y$ 上，等需要查询 $x$ 节点的值的时候，在把保存在 $y$ 的值传给 $x$，以保证优秀的复杂度。

那么在本题中，我们将 $val$ 加到以 $x$ 节点为根的子树的所有节点上时，我们暂时并不会查询这些节点的值（而是在最终查询），那么我们可以仿照“懒标记”，暂时性的把 $val$ 值保存在 $x$ 节点上，最终再把保存在该节点上的值以优秀的复杂度传给它的所有子节点。

考虑到每个节点只遍历一次，所以复杂度为 $O(n)$。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int f[N],tag[N],n,head[N],tot,m;
struct node { //链式前向星存图
	int to,nxt;
}; node Edge[N<<1];
void Add_Edge(int u,int v) {
	++tot; Edge[tot]=node{v,head[u]}; head[u]=tot;
}
void Dfs(int u,int fa) { 
	int x=tag[u]; tag[u]=0; f[u]+=x; //将懒标记的值加在该节点的答案上（话说不区分 tag 和 f也行）
	for(int i=head[u];i;i=Edge[i].nxt) {
		int v=Edge[i].to; 
		if(v!=fa) {
			tag[v]+=x; Dfs(v,u); //传给子节点 v
		}
	}
}
signed main() {
	cin>>n>>m;
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	while(m--) {
		int u,val;
		cin>>u>>val;
		tag[u]+=val; //懒标记
	}
	Dfs(1,0); //下传所有懒标记
	for(int i=1;i<=n;i++)
		cout<<f[i]<<" ";
	return 1;
}
```
完美撒花！

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc138_d)
## 思路
这题是一道树的搜索板子题


------------

代码的核心部分bfs搜索：
```cpp
void bfs(){
	vis[1] = true;//起点标记
	queue<int> q;
	q.push(1);//起点进队
	while(!q.empty()){
		int t = q.front();
		q.pop();
		for(auto i : g[t]){
			if(i == t || vis[i])continue;
			vis[i] = true;//标记，防止重复计算导致MLE和TLE
			st[i] += st[t];//加上它父亲的值
			q.push(i);//新的父亲入队
		}
	}
	return ;
}
```
首先，先将起点标记和入队，然后是标准的广搜式的树的搜索。
### 注意事项
- 别忘了用vis数组来标记，否则会 MLE 或者 TLE 
- st数组每次加的值是它父亲的值，而不是加 1

最后贴上我的AC代码。
# AC 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, q, st[N];

bool vis[N];

vector<int> g[N];

void bfs(){
	vis[1] = true;
	queue<int> q;
	q.push(1);
	while(!q.empty()){
		int t = q.front();
		q.pop();
		for(auto i : g[t]){
			if(i == t || vis[i])continue;
			vis[i] = true;
			st[i] += st[t];
			q.push(i);
		}
	}
	return ;
}

int main(){
	cin >> n >>q;
	for(int i = 1; i <= n - 1; i++){
		int x, y;
		cin >> x >> y;
		//按照题目建双边
		g[x].push_back(y);
		g[y].push_back(x);
	}
	//Q次操作
	while(q--){
		int x, y;
		cin >> x >> y;
		st[x] += y;
	}
	bfs();//BFS搜索
	for(int i = 1; i <= n; i++)cout << st[i] << " ";//按题目要求输出
	cout << endl;//别忘了回车
}
```
### [已AC](https://www.luogu.com.cn/record/96965323)

---

## 作者：TLEWA (赞：0)

## 简要题意

给定一个树，$Q$ 次修改，每次修改将 $u$ 的子树节点权值增加 $w$，求最后每个节点的值

## 思路

很明显，这道题目暴力 $O(QN)$ 的，妥妥超时，考虑使用树上差分来优化。

以下内容默认读者学过树上差分：

对于每次操作，我们给 $u$ 打上一个标记，之前的标记合并，最后进行一次 dfs 更新标记，预处理 $O(Q)$，下传标记 $O(N)$，总时间复杂度 $O(Q+N)$。

代码如下：
```cpp
#include<iostream>
using namespace std;

int n,q,u,v;
int first[2000005],p;
struct Node {
	int to,next;
}arr[2000005];

void add(int u,int v) {
	arr[++p].next=first[u];
	first[u]=p;
	arr[p].to=v;
}

int jsq[2000005];

void dfs(int now,int fa,int las) {
	jsq[now]+=las;
	for(int i=first[now];i;i=arr[i].next) if(arr[i].to!=fa) dfs(arr[i].to,now,jsq[now]);
}

int main() {
	cin >> n >> q;
	for(int i=1;i!=n;++i) {
		cin >> u >> v;
		add(u,v);
		add(v,u);
	}
	for(int i=0;i!=q;++i) {
		cin >> u >> v;
		jsq[u]+=v;
	}
	dfs(1,0,0);
	for(int i=1;i<=n;++i) cout << jsq[i] << ' ';
	cout << endl;
	return 0;
}
```


---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4848)
## 思路
刚看到这题以为是把树拍扁到序列上用线段树维护的的板子题，但是，我们发现这只是一个 ABC 的 D 题，而且它没有边修改边查询，所以我们可以合并到最后一起做。

每次修改都在某个节点上打上标记，某个数的权值即是它到根节点路径上的权值之和。

这样这题就做完了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int c[N];
vector<int>a[N];
inline void dfs(int x,int fa,int p){
    for (auto v:a[x]) if (v!=fa) dfs(v,x,p+c[x]);
    c[x]+=p;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,q;cin>>n>>q;
    for (int i=1;i<n;++i){
        int u,v;cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    while (q--){
        int x,v;cin>>x>>v;
        c[x]+=v;
    }
    dfs(1,-1,0);
    for (int i=1;i<=n;++i) cout<<c[i]<<' ';
    cout<<'\n';
    return 0;
}
```


---

## 作者：sickbot (赞：0)

# 思路
如题，Lazy Tag+DFS 就能过。\
具体就是：先把标记打在每个节点上，再通过dfs,把标记往下面所有的节点放。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<(n);i++)
struct node
{
	vector<int> son;//子节点
	int curv=0;// current_value 在lazy tag中用到的
	int var=0;
	bool vis=0;
} ver[200000+5];
void dfs(int nno=1,int nval=0)//dfs
{
	int val=nval+ver[nno].curv;
	ver[nno].var=val;
	ver[nno].vis=1;
	rep(i,0,ver[nno].son.size())
	{
		if(ver[ver[nno].son[i]].vis==0)dfs(ver[nno].son[i],val);
	}
}
signed main()
{
	ios::sync_with_stdio(0);
  cin.tie(0);cout.tie(0);
	int n,q;
	cin>>n>>q;
	rep(i,1,n)
	{
		int a,b;
		cin>>a>>b;
		ver[a].son.push_back(b);//建树
		ver[b].son.push_back(a);//建树
	}
	rep(i,0,q)
	{
		int a,b;
		cin>>a>>b;
		ver[a].curv+=b;//lazy tag标记
	}
	dfs();//dfs
	rep(i,1,n+1)
	{
		cout<<ver[i].var;
		cout<<" ";
	}
  return 0;
}
```


---

## 作者：RainFestival (赞：0)

我们这道题目可以这么做：

首先一遍 dfs 求出 id , sz

设 $l_i=id_i$ , $r_i=id_i+sz_i-1$

因为可以离线，所以我们运用差分

每次 $x$ 子树加 $v$

```cpp
s[l(x)]=s[l(x)]+v;s[r(x)+1]=s[r(x)+1]-v;

```

最后扫一遍
```cpp
for (int i=1;i<=n;i++) ans[i]=ans[i-1]+s[i];

```
$ans_{id_i}$ 就是第 $i$ 个点的答案

代码：
```cpp
#include<cstdio>
#include<vector>
#define l(x) id[x]
#define r(x) id[x]+sz[x]-1
std::vector<int> a[200005];
int n,q,cnt,fa[200005],id[200005],sz[200005],ans[200005],s[200005];
void add(int x,int y){a[x].push_back(y);a[y].push_back(x);}
void dfs(int v)
{
	id[v]=++cnt;sz[v]=1;
	for (int i=0;i<a[v].size();i++)
	{
	    int u=a[v][i];
	    if (u==fa[v]) continue;
	    fa[u]=v;
	    dfs(u);
	    sz[v]=sz[v]+sz[u];
	}
}
void tag(int x,int v){s[l(x)]=s[l(x)]+v;s[r(x)+1]=s[r(x)+1]-v;}
int main()
{
	scanf("%d%d",&n,&q);
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1);
	while (q--)
	{
		int x,v;
		scanf("%d%d",&x,&v);
		tag(x,v);
	}
	for (int i=1;i<=n;i++) ans[i]=ans[i-1]+s[i];
	for (int i=1;i<=n;i++) printf("%d ",ans[id[i]]);
	return 0;
}
```

然后就 AC 了

QAQ


---

