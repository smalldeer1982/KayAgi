# Water Tree

## 题目描述

Mad scientist Mike has constructed a rooted tree, which consists of $ n $ vertices. Each vertex is a reservoir which can be either empty or filled with water.

The vertices of the tree are numbered from 1 to $ n $ with the root at vertex 1. For each vertex, the reservoirs of its children are located below the reservoir of this vertex, and the vertex is connected with each of the children by a pipe through which water can flow downwards.

Mike wants to do the following operations with the tree:

1. Fill vertex $ v $ with water. Then $ v $ and all its children are filled with water.
2. Empty vertex $ v $ . Then $ v $ and all its ancestors are emptied.
3. Determine whether vertex $ v $ is filled with water at the moment.

 Initially all vertices of the tree are empty.Mike has already compiled a full list of operations that he wants to perform in order. Before experimenting with the tree Mike decided to run the list through a simulation. Help Mike determine what results will he get after performing all the operations.

## 样例 #1

### 输入

```
5
1 2
5 1
2 3
4 2
12
1 1
2 3
3 1
3 2
3 3
3 4
1 2
2 4
3 1
3 3
3 4
3 5
```

### 输出

```
0
0
0
1
0
1
0
1
```

# 题解

## 作者：Dilute (赞：13)

[$$\huge\texttt{在本人blog食用更佳}$$](https://dilute.xyz/2019/03/29/Solutions/Solution-CF343D/)

## 似乎莫得人是不用树剖的w

~~但是为什么的一只log乱搞被树剖的两只log爆踩啊~~

~~是因为我实现的太丑了吗~~

不管了直接讲做法好了

首先，我们考虑一个很显然的结论：

> 如果我们对于节点x他上次被灌水的时间位x，上次被清除水的时间是y
>
> 那么若有x > y则此时这个节点有水
>
> 否则这个节点没水

然后我们再考虑如何维护x和y

我们把两种修改分别讨论，分别用树上差分和`dfs`序维护，就可以愉快地以$O(n \log n)$的复杂度切掉此题。

如果不会的可以具体看代码，不会树上查分的可以看看[这题](https://www.luogu.org/problemnew/show/P2936)学学

## 代码

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647
#define lc(a) (a << 1)
#define rc(a) (a << 1 | 1)

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

struct SEG_Tree{
    struct SEG{
        int l;
        int r;
        int max;
        int lazy;
    }t[2000000];
    
    void push_up(int cur){
        t[cur].max = std::max(t[lc(cur)].max, t[rc(cur)].max);
    }

    void push_down(int cur){
        if(!t[cur].lazy)
            return ;
        t[lc(cur)].max = t[rc(cur)].max = t[lc(cur)].lazy = t[rc(cur)].lazy = t[cur].lazy;
        t[cur].lazy = 0;
    }

    void build(int cur, int l, int r){
        t[cur].l = l;
        t[cur].r = r;
        t[cur].max = 0;
        t[cur].lazy = 0;
        if(l == r)
            return ;
        int mid = (l + r) >> 1;
        build(lc(cur), l, mid);
        build(rc(cur), mid + 1, r);
    }

    void modify(int cur, int l, int r, int c){
        if(t[cur].l > r || t[cur].r < l)
            return ;
        if(t[cur].l >= l && t[cur].r <= r){
            t[cur].max = c;
            t[cur].lazy = c;
            return ;
        }
        push_down(cur);
        modify(lc(cur), l, r, c);
        modify(rc(cur), l, r, c);
        push_up(cur);
    }

    int query(int cur, int l, int r){
        if(t[cur].l > r || t[cur].r < l)
            return 0;
        if(t[cur].l >= l && t[cur].r <= r)
            return t[cur].max;
        push_down(cur);
        return std::max(query(lc(cur), l, r), query(rc(cur), l, r));
    }
}t1, t2;
int dfn[500010], size[500010], head[500010], nxt[1000010], end[1000010];
int cou = 0;
void link(int a, int b){
    nxt[++cou] = head[a];
    head[a] = cou;
    end[cou] = b;
}

int idx = 0;
void dfs(int cur, int last){
    dfn[cur] = ++idx;
    size[cur] = 1;
    for(int x = head[cur]; x != -1; x = nxt[x])
        if(end[x] != last){
            dfs(end[x], cur);
            size[cur] += size[end[x]];
        }
}

int main(){
    memset(head, -1, sizeof(head));
    int n = inp();
    for(int i = 1; i < n; i++){
        int u = inp();
        int v = inp();
        link(u, v);
        link(v, u);
    }
    int m = inp();
    dfs(1, 0);
    t1.build(1, 1, n);
    t2.build(1, 1, n);
    for(int i = 1; i <= m; i++){
        int op = inp();
        if(op == 1){
            int x = inp();
            t1.modify(1, dfn[x], dfn[x] + size[x] - 1, i);
        } else if(op == 2){
            int x = inp();
            t2.modify(1, dfn[x], dfn[x], i);
        } else {
            int x = inp();
            int a1 = t1.query(1, dfn[x], dfn[x]);
            int a2 = t2.query(1, dfn[x], dfn[x] + size[x] - 1);
            // printf("%d %d\n", a1, a2);
            if(a1 > a2)
                printf("1\n");
            else
                printf("0\n");
        }
    }
}
```





---

## 作者：yzhang (赞：10)

## [更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/9763060.html)

#### 原题传送门：[CF343D Water Tree](https://www.luogu.org/problemnew/show/CF343D)

#### 这明显是弱智题

#### 树剖套珂朵莉树多简单啊

## 前置芝士：珂朵莉树

### [窝博客里对珂朵莉树的介绍](https://www.cnblogs.com/yzhang-rp-inf/p/9443659.html )

### 没什么好说的自己看看吧

#### 先树剖一下

#### 第一种操作，把一个点的子树全部变成1

#### 因为做了树剖，所以珂朵莉树区间赋值就可以了

#### 第二种操作就重链往上跳，重链全变成0，珂朵莉树也能完成

#### 第三种操作直接split一下就行

#### 这道题真的很简单，细节看代码~~（珂朵莉树实际就是一种暴力）~~

#### ~~因为数据随机，所以有可能会有点慢~~

```cpp
#pragma GCC optimize("O3") 
#include <bits/stdc++.h>
#define N 500005
using namespace std;
inline int read()
{
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
struct edge{
    int to,next;
}e[N<<1];
int head[N],cnt=0;
inline void add(register int u,register int v)
{
    e[++cnt]=(edge){v,head[u]};
    head[u]=cnt;
}
int n,m;
int size[N],l[N],son[N],dep[N],fa[N],top[N],tot=0;
inline void dfs1(register int x)
{
    size[x]=1;
    for(register int i=head[x];i;i=e[i].next)
    {
        int v=e[i].to;
        if(!dep[v])
        {
            dep[v]=dep[x]+1;
            fa[v]=x;
            dfs1(v);
            size[x]+=size[v];
            if(size[v]>size[son[x]])
                son[x]=v;
        }
    }
}
inline void dfs2(register int x,register int t)
{
    l[x]=++tot;
    top[x]=t;
    if(son[x])
        dfs2(son[x],t);
    for(register int i=head[x];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v!=fa[x]&&v!=son[x])
            dfs2(v,v);
    }
}
struct node
{
    int l,r;
    mutable int v;
    node(int L, int R=-1, int V=0):l(L), r(R), v(V) {}
    bool operator<(const node& o) const
    {
        return l < o.l;
    }
};
set<node> s;
#define IT set<node>::iterator
IT split(register int pos)
{
    IT it = s.lower_bound(node(pos));
    if (it != s.end() && it->l == pos) 
        return it;
    --it;
    int L = it->l, R = it->r;
    int V = it->v;
    s.erase(it);
    s.insert(node(L, pos-1, V));
    return s.insert(node(pos, R, V)).first;
}
inline void assign_val(register int l,register int r,register int val)
{
    IT itr = split(r+1),itl = split(l);
    s.erase(itl, itr);
    s.insert(node(l, r, val));
}
inline void query(register int pos)
{
    IT itpos = split(pos);
    printf("%d\n",itpos->v);
}
inline void cal(register int pos)
{
    int fpos=top[pos];
    while(fpos!=1)
    {
        assign_val(l[fpos],l[pos],0);
        pos=fa[fpos],fpos=top[pos];
    }
    assign_val(l[1],l[pos],0);
}
int main()
{
    n=read();
    for(register int i=1;i<n;++i)
    {
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    dep[1]=fa[1]=1;
    dfs1(1);
    dfs2(1,1);
    s.insert(node(0,500000+233));
    int m=read();
    while(m--)
    {
        int opt=read(),pos=read();
        if(opt==1)
            assign_val(l[pos],l[pos]+size[pos]-1,1);
        else if(opt==2)
            cal(pos);
        else
            query(l[pos]);
    }
    return 0;
}
```

---

## 作者：Treaker (赞：9)

## 一个树剖题。

我们可以对于线段树的每一个节点，维护区间覆盖 和 区间清空 即可

这里采用数组写法，指针写法详见[我博客](https://www.luogu.org/blog/Treaker/#)其他树剖题。

顺便推荐做一下模板[【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)  

完整代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 500500;
int ls(int x) {return x << 1;}
int rs(int x) {return x << 1 | 1;}
int n , m , cnt;
int head[N] , top[N] , fa[N] , dfn[N] , id[N] , size[N] , dep[N] , hs[N];
int col[N << 2] , tag[N << 2];
struct Edge {int to , nxt;} e[N << 1];
void add(int from,int to) 
{
	e[++cnt] = (Edge){to,head[from]};
	head[from] = cnt;
}
void get_tree(int now)
{
	size[now] = 1;
	for(int i = head[now];i;i = e[i].nxt)
	{
		int to = e[i].to;
		if(dep[to])	continue;
		fa[to] = now;
		dep[to] = dep[now]  +1;
		get_tree(to);
		size[now] += size[to];
		if(size[to] > size[hs[now]])	hs[now] = to;
	}
}
void dfs(int now,int topfa)
{
	dfn[now] = ++cnt;
	id[cnt] = now;
	top[now] = topfa;
	if(hs[now])	dfs(hs[now],topfa);
	for(int i = head[now];i;i = e[i].nxt)
	{
		int to = e[i].to;
		if(fa[now] == to || to == hs[now])	continue;
		dfs(to,to);
	}
}
void push_down(int p,int l,int r)
{
	col[ls(p)] = col[rs(p)] = col[p];
	tag[ls(p)] = tag[rs(p)] = tag[p];
	tag[p] = -1;
}
void chenge(int p,int l,int r,int x,int y,int k)
{
	if(x <= l && r <= y)	
	{
		col[p] = k;
		tag[p] = k;
		return ;
	}
	int mid = (l + r) >> 1;
	if(tag[p] >= 0)	push_down(p,l,r);
	if(x <= mid)	chenge(ls(p),l,mid,x,y,k);
	if(y > mid)		chenge(rs(p),mid+1,r,x,y,k);
}
void sec_cover(int x,int y)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]])	swap(x,y);
		chenge(1,1,n,dfn[top[x]],dfn[x],0);
		x = fa[top[x]];
	}
	if(dep[x] < dep[y])	swap(x,y);
	chenge(1,1,n,dfn[y],dfn[x],0);
}
int query(int p,int l,int r,int x)
{
	if(l == r)	return col[p];
	int mid = (l + r) >> 1;
	if(tag[p] >= 0)	push_down(p,l,r);
	if(x <= mid)	return query(ls(p),l,mid,x);
	else	return query(rs(p),mid+1,r,x);
}	
int main()
{
	scanf("%d",&n);
	for(int i = 1 , x , y;i < n;i ++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);  add(y,x);
	}
	cnt = 0;  dep[1] = 1;
	get_tree(1);
	dfs(1,1);
	memset(tag,-1,sizeof tag);
	scanf("%d",&m);
	for(int i = 1 , c , v;i <= m;i ++)
	{
		scanf("%d%d",&c,&v);
		if(c == 1)	chenge(1,1,n,dfn[v],dfn[v]+size[v]-1,1);
		else if(c == 2)	sec_cover(1,v);
		else printf("%d\n",query(1,1,n,dfn[v]));
	}
	return 0;
}
```


---

## 作者：UhhhQQQU (赞：7)

其实这题是可以不用树链剖分的，用dfs序建出线段树就可以水过。

以下是过程：

首先，我们先dfs一遍，求出一个节点的dfs序、它的父亲节点、它的子树的大小。

我们可以根据dfs的顺序建一棵线段树。dfs序就对应这个节点在线段上的编号。然后我们容易发现，这个节点的子树其实就对应线段树上的一个区间（可以手造一个数据来看一下，这个区间的左右节点是什么）。

然后，不就是几个简单的操作了吗？

对于操作1，我们把这棵子树在线段树上的区间全部涂黑（也就是改为1）

对于操作2，直接把x的对应区间改为0

对于操作3，用区间求和，然后看结果是否等于这棵子树的大小，因为对于一个节点，只要它有一个白色的子节点，它也是白色的。（具体可以看题目的操作2）

最后，我们还要在操作1加上一个特判，如果这个x不为根节点，而且它的子树里面有白色的节点，我们就立刻把它转移到x的父节点去，这样子就可以避免某些错误了（我错了好几次呀。。。）。

```
#include<cstdio>
#include<cstring>
#define ls (k<<1)
#define rs (k<<1|1)
#define mid ((l+r)>>1) 
int n,q;
int cnt1,num[500010],size[500010];
int t[2000010],tag[2000010],fa[2000010];
int head[500010],cnt;
struct edge{
	int next,go;
}e[1000010];
void add(int u,int v){e[++cnt]=(edge){head[u],v},head[u]=cnt;}
void dfs(int u,int pre) //预处理 
{
	num[u]=++cnt1,size[u]=1,fa[u]=pre;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].go;
		if(v!=pre)
			dfs(v,u),size[u]+=size[v];
	}
	return ;
}
void pushdown(int k,int l,int r) //标记下传 
{
	if(tag[k]!=-1)
	{
		tag[ls]=tag[rs]=tag[k];
		t[ls]=tag[k]*(mid-l+1);
		t[rs]=tag[k]*(r-mid);
		tag[k]=-1;
	}
	return ;
}
void change(int k,int l,int r,int x,int y,int val) //区间修改 
{
	if(x<=l&&r<=y)
	{
		t[k]=(r-l+1)*val;
		tag[k]=val;
		return ;
	}
	pushdown(k,l,r);
	if(x<=mid)
		change(ls,l,mid,x,y,val);
	if(y>mid)
		change(rs,mid+1,r,x,y,val);
	t[k]=t[ls]+t[rs];
	return ;
}
int query(int k,int l,int r,int x,int y) //区间求和 
{
	if(x<=l&&r<=y)
		return t[k];
	pushdown(k,l,r);
	int ret=0;
	if(x<=mid)
		ret+=query(ls,l,mid,x,y);
	if(y>mid)
		ret+=query(rs,mid+1,r,x,y);
	return ret;
}
int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d %d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs(1,0);
	memset(tag,-1,sizeof(tag));
	scanf("%d",&q);
	for(int i=1,opt,x;i<=q;i++)
	{
		scanf("%d %d",&opt,&x);
		if(opt==1)
		{
			if(x!=1&&query(1,1,n,num[x],num[x]+size[x]-1)<size[x]) //特判 
				change(1,1,n,num[fa[x]],num[fa[x]],0);
			change(1,1,n,num[x],num[x]+size[x]-1,1); //区间修改 
		}
		else if(opt==2)
			change(1,1,n,num[x],num[x],0); //区间修改 
		else
			printf("%d\n",query(1,1,n,num[x],num[x]+size[x]-1)==size[x]); //区间求和 
	}
	return 0; //结束 
}
```


---

## 作者：流逝丶 (赞：3)

~~然而并不会珂朵莉树，也不会珂朵莉树上树~~

这树剖裸题啊!感觉难度应该是提高+/省选-

我们将这棵树剖完之后,再看三个操作：

操作1：区间覆盖1

操作2：区间覆盖0

操作3：单点查询

用线段树维护区间1的数量

如果中途访问到的区间1的数量等于区间长度，直接返回1，否则访问线段树叶子结点，注意laz数组初始值为-1,0为0覆盖整个区间，1为1覆盖整个区间。

这样down的时候可以直接用区间长度乘laz，down完之后laz回归初始值-1。

然后就完了。

```cpp
#include<iostream>
#include<cstdio>
#define mid ((l+r)>>1)
#define lson k<<1,l,mid
#define rson k<<1|1,mid+1,r
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int N=500005;
int n,m,cnt,tot;
int head[N],dep[N],fa[N],siz[N],son[N],id[N],top[N];
int tr[N<<2],laz[N<<2];
struct node{
	int to,nxt;
}e[N<<1];
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline void add(int from,int to){
	e[++cnt]=(node){to,head[from]};
	head[from]=cnt;
}
void dfs1(int x,int f,int deep){
	fa[x]=f;siz[x]=1;dep[x]=deep;
	int maxson=-1,to;
	for(int i=head[x];i;i=e[i].nxt)
		if(e[i].to!=f){
			to=e[i].to;
			dfs1(to,x,deep+1);
			siz[x]+=siz[to];
			if(siz[to]>maxson)son[x]=to,maxson=siz[to];
		}
}
void dfs2(int x,int topf){
	id[x]=++tot;top[x]=topf;
	if(!son[x])return ;
	dfs2(son[x],topf);
	for(int i=head[x];i;i=e[i].nxt)
		if(e[i].to!=fa[x]&&e[i].to!=son[x])
			dfs2(e[i].to,e[i].to);
}
inline void update(int k){
	tr[k]=tr[ls]+tr[rs];
}
inline void down(int k,int l,int r){
	tr[ls]=(mid-l+1)*laz[k];
	tr[rs]=(r-mid)*laz[k];
	laz[ls]=laz[rs]=laz[k];
	laz[k]=-1;
}
void change(int k,int l,int r,int x,int y,int z){
	if(x==l&&y==r){
		tr[k]=(r-l+1)*z;
		laz[k]=z;
		return ;
	}
	if(laz[k]!=-1)down(k,l,r);
	if(y<=mid)change(lson,x,y,z);
	else if(x>mid)change(rson,x,y,z);
	else change(lson,x,mid,z),change(rson,mid+1,y,z);
	update(k);
}
int ask(int k,int l,int r,int x){
	if(tr[k]==(r-l+1))return 1;
	if(l==r&&l==x){
		return tr[k];
	}
	if(laz[k]!=-1)down(k,l,r);
	if(x<=mid)return ask(lson,x);
	else return ask(rson,x);
}
inline void chenge(int x,int y){
	while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        change(1,1,n,id[top[x]],id[x],0);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    change(1,1,n,id[x],id[y],0);
}
int main(){
	n=read();
	int x,y;
	for(int i=1;i<n;++i){
		x=read();y=read();
		add(x,y);add(y,x);
	}
	dfs1(1,0,1);
	dfs2(1,1);
	for(int i=1;i<=(n<<2);++i)laz[i]=-1;
	m=read();
	int opt;
	while(m--){
		opt=read();x=read();
		if(opt==1)change(1,1,n,id[x],id[x]+siz[x]-1,1);
		else if(opt==2)chenge(x,1);
		else printf("%d\n",ask(1,1,n,id[x]));
	}
	return 0;
}
```


---

## 作者：Tethys (赞：2)

[题面](https://www.luogu.com.cn/problem/CF343D)

这是一道树剖的裸题

~~（第一次水紫题有点快乐）~~

这道题其实就是轻重链剖分的操作拿出来罢了

我们看到这道题区间修改，单点查询

不难想到线段树吧

然后我们可以想到轻重链剖分那道题

我们会发现操作$1$就是将$dfn[x]$~$dfn[x]+siz[x]-1$这段区间都赋值为$1$

这样的话我们就可以$O(log)$地维护了

然后我们考虑一下操作$2$我们发现，跳重链地过程其实就是不断向$1$移动的过
程

所以我们在每次跳重链的时候，顺便在线段树上修改一下值就好了

操作$3$其实就是线段树单点查询 

话不多说，直接放代码
```cpp
#include<bits/stdc++.h>		
const int N = 5e5 + 5;
using namespace std;
int n, m, head[N], cnt, dfn[N], hev[N], dep[N], siz[N], top[N], sum, fa[N];
struct node{
	int u, v, nxt;
}edge[N << 1];
void add(int u, int v){
	edge[++ cnt].u = u;
	edge[cnt].v = v;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
}
struct tree{
	protected:
		#define ls(o) (o << 1)
		#define rs(o) (o << 1 | 1)
		#define mid ((l + r) >> 1)
		int tr[N << 2], laz[N << 2];
		void up(int o){ tr[o] = tr[ls(o)] + tr[rs(o)];}
		void down(int o, int l, int r){
			laz[ls(o)] = laz[rs(o)] = laz[o];
			tr[ls(o)] = laz[o] * (mid - l + 1);
			tr[rs(o)] = laz[o] * (r - mid);
			laz[o] = -1;
		}
		void build(int o, int l, int r){
			if(l == r){ tr[o] = 0; return ;}
			build(ls(o), l, mid); build(rs(o), mid + 1, r);
			up(o);
		}
	public:
		void change(int o, int l, int r, int L, int R, int val){
			if(L <= l && r <= R){
				tr[o] = val * (r - l + 1); laz[o] = val;
				return ;
			}
			if(laz[o] != -1) down(o, l, r);
			if(L <= mid) change(ls(o), l, mid, L, R, val);
			if(R > mid) change(rs(o), mid + 1, r, L, R, val);
			up(o);
		}
		int query(int o, int l, int r, int x){
			if(l == r){ return laz[o];}
			if(laz[o] != -1) down(o, l, r);
			if(x <= mid) return query(ls(o), l, mid, x);
			else return query(rs(o), mid + 1, r, x);
		}
		void cz(int x){ build(1, 1, x);}
}St_tree;
struct Powtree{
	void Ps(int x){
		siz[x] = 1;
		for(int i = head[x]; i; i = edge[i].nxt){
			int to = edge[i].v;
			if(to == fa[x]) continue;
			dep[to] = dep[x] + 1;
			fa[to] = x;
			Ps(to);
			siz[x] += siz[to];
			if(siz[to] > siz[hev[x]]) hev[x] = to;
		}
	}
	void dfs(int x, int topp){
		top[x] = topp;
		dfn[x] = ++ sum;
		if(hev[x]) dfs(hev[x], topp);
		for(int i = head[x]; i; i = edge[i].nxt){
			int to = edge[i].v;
			if(to == fa[x] || to == hev[x]) continue;
			dfs(to, to);
		}
	}
	void cz(){
		dep[1] = 1;
		Ps(1);
		dfs(1, 1);
	}
}Pow_tree;
int read(){
	int op = 0, opp = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') opp = -1; ch = getchar();}
	while(ch <= '9' && ch >= '0'){ op = (op << 1) + (op << 3) + (ch ^ 48); ch = getchar();}
	return op * opp;
}
void Build_tree(){
	Pow_tree.cz();
	St_tree.cz(n);
}
void Jump(int x){
	while(x){
		St_tree.change(1, 1, n, dfn[top[x]], dfn[x], 0);
		x = fa[top[x]];
	}
}
void maiin(){
	n = read();
	for(int i = 1, x, y; i < n; i ++){
		x = read(); y = read();
		add(x, y); add(y, x);
	}
	Build_tree();
	m = read();
	for(int i = 1, x, y; i <= m; i ++){
		x = read(); y = read();
		if(x == 1) St_tree.change(1, 1, n, dfn[y], dfn[y] + siz[y] - 1, 1);
		if(x == 2) Jump(y);
		if(x == 3) printf("%d\n", St_tree.query(1, 1, n, dfn[y]));
	}
}
int main(){
	maiin();
	return 0;
}
```

这道题有个地方很细节，就是在线段树里，没有标记的时候，$laz$会被标记为$-1$，这样就会防止没有$0$的标记，却操作中下放了$0$的标记，导致了无故的$WA$


---

## 作者：yu__xuan (赞：1)

### 题目
[CF343D Water Tree](https://www.luogu.com.cn/problem/CF343D)

### 思路
树链剖分。
样例中的树长这样:

![](https://cdn.luogu.com.cn/upload/image_hosting/7a68f6sv.png)

加粗的是经过 $dfs$ 找到的重儿子。所以放到线段树上之后是这样:
![](https://cdn.luogu.com.cn/upload/image_hosting/p418z8vq.png)

以 $x$ 为根的子树可以用 $dfn[x] \sim dfn[x]+size[x]-1$ 来表示。$1$ 到 $x$ 的路径：如果 $1$ 和 $x$ 不在一条重链上就把 $x$ 跳到链顶的父亲结点。如 $1$ 和 $4$，因为 $4$ 号点和 $1$ 号点不在一条重链上，$4$ 号点先跳到 $2$ 号点，并在线段树上维护 $dfn[top[4]] \sim dfn[4]$（top表示链顶），这样 $4$ 号点跳到了 $2$ 号点并且和 $1$ 号点在一条链上用线段树维护 $dfn[1] \sim dfn[2]$。

### Code
```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#define MAXN 500001

inline void read(int &T) {
	int x=0;bool f=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=!f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	T=f?-x:x;
}

int n,q,dfn[MAXN],pre[MAXN],size[MAXN];

namespace Seg {
	#define lson now<<1
	#define rson now<<1|1
	struct Node {
		int l,r,w,lazy;
	}tree[MAXN<<2];
	void pushdown(int now) {
		tree[lson].lazy=tree[now].lazy;
		tree[rson].lazy=tree[now].lazy;
		tree[lson].w=tree[now].lazy;
		tree[rson].w=tree[now].lazy;
		tree[now].lazy=-1;
	}
	void build(int l,int r,int now) {
		tree[now].l=l,tree[now].r=r;
		tree[now].lazy=-1;
		if(tree[now].l==tree[now].r) {
			tree[now].w=0;return;
		}
		int mid=(tree[now].l+tree[now].r)>>1;
		build(l,mid,lson),build(mid+1,r,rson);
	}
	void update(int x,int y,int k,int now) {
		if(tree[now].l>=x&&tree[now].r<=y) {
			tree[now].w=k,tree[now].lazy=k;
			return;
		}
		if(tree[now].lazy!=-1) pushdown(now);
		int mid=(tree[now].l+tree[now].r)>>1;
		if(x<=mid) update(x,y,k,lson);
		if(y>mid) update(x,y,k,rson);
	}
	int ask(int x,int now) {
		if(tree[now].l==tree[now].r) return tree[now].w;
		if(tree[now].lazy!=-1) pushdown(now);
		int mid=(tree[now].l+tree[now].r)>>1;
		if(x<=mid) return ask(x,lson);
		else return ask(x,rson);
	}
}

namespace Cut {
	int cnt,pthn,head[MAXN],dep[MAXN];
	int fa[MAXN],son[MAXN],top[MAXN];
	struct Edge {
		int next,to;
	}pth[MAXN<<1];
	void add(int from,int to) {
		pth[++pthn].to=to,pth[pthn].next=head[from];
		head[from]=pthn;
	}
	void dfs1(int u,int father) {
		fa[u]=father,dep[u]=dep[father]+1,size[u]=1;
		for(int i=head[u];i;i=pth[i].next) {
			int x=pth[i].to;
			if(x!=father) {
				dfs1(x,u),size[u]+=size[x];
				if(size[son[u]]<size[x]) son[u]=x;
			}
		}
	}
	void dfs2(int u,int tp) {
		top[u]=tp,dfn[u]=++cnt,pre[cnt]=u;
		if(son[u]) dfs2(son[u],tp);
		for(int i=head[u];i;i=pth[i].next) {
			int x=pth[i].to;
			if(x!=fa[u]&&x!=son[u]) dfs2(x,x);
		}
	}
	void change(int x,int y) {
		while(top[x]!=top[y]) {
			if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
			Seg::update(dfn[top[x]],dfn[x],0,1);
			x=fa[top[x]];
		}
		if(dep[x]>dep[y]) std::swap(x,y);
		Seg::update(dfn[x],dfn[y],0,1);
	}
}

int main() {
	read(n);
	for(int i=1,u,v;i<n;++i) {
		read(u),read(v);
		Cut::add(u,v),Cut::add(v,u);
	}
	Cut::dfs1(1,1),Cut::dfs2(1,1),Seg::build(1,n,1);
	read(q);
	for(int i=1,opt,x;i<=q;++i) {
		read(opt),read(x);
		if(opt==1) Seg::update(dfn[x],dfn[x]+size[x]-1,1,1);
		else if(opt==2) Cut::change(1,x);
		else printf("%d\n",Seg::ask(dfn[x],1));
	}
	return 0;
}
```

---

## 作者：henrytb (赞：1)

# 珂朵莉太可爱了！

这道题显然要用树剖，但是我懒得写线段树，怎么办？

当然要先拿珂朵莉树尝试骗骗分啊！

树剖完了之后，所有操作都很简单了：两个区间覆盖、一个单点查询。

区间覆盖是珂朵莉树的核心操作啊！那这题用珂朵莉树只套个板子就行了。

**注意珂朵莉树只能应对随机数据的情况！**

具体操作见代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define grep(u) for(int ptr=last[u];ptr;ptr=pre[ptr])
using namespace std;
const int N=1e6+5;
int n,target[N],pre[N],last[N],tot=0,q;
int deep[N],bel[N],dfn[N],sz[N],fa[N],_dfnclock=0;
void add(int u,int v) {
    target[++tot]=v;
    pre[tot]=last[u];
    last[u]=tot;
}
void dfs1(int u,int f,int dep) {
    deep[u]=dep;fa[u]=f;sz[u]=1;
    grep(u) if(target[ptr]!=f) {
        dfs1(target[ptr],u,dep+1);
        sz[u]+=sz[target[ptr]];
    }
}
void dfs2(int u,int chain) {
    bel[u]=chain;
    dfn[u]=++_dfnclock;
    int maxx=0;
    grep(u) if(deep[target[ptr]]==deep[u]+1&&sz[target[ptr]]>sz[maxx]) maxx=target[ptr];
    if(maxx) dfs2(maxx,chain);
    grep(u) if(deep[target[ptr]]==deep[u]+1&&maxx!=target[ptr]) dfs2(target[ptr],target[ptr]);
}
struct node{
    int l,r;
    mutable int v;
    node(int l,int r,int val):l(l),r(r),v(val){}
    bool operator <(const node& rhs) const{
        return l<rhs.l;
    }
};
typedef set<node>::iterator iter;
set<node> odt;
iter split(int x) {
    iter ii=odt.lower_bound(node(x,-1,-1));
    if(ii!=odt.end()&&ii->l==x) return ii;
    --ii;
    int ll=ii->l,rr=ii->r,vv=ii->v;
    odt.erase(ii);
    odt.insert(node(ll,x-1,vv));
    return odt.insert(node(x,rr,vv)).first;
}
void assign(int l,int r,int v) {
    iter ri=split(r+1),li=split(l);
    odt.erase(li,ri);
    odt.insert(node(l,r,v));
}
void cover(int u,int v,int val) {
    while(bel[u]!=bel[v]) {
        if(deep[bel[u]]<deep[bel[v]]) swap(u,v);
        assign(dfn[bel[u]],dfn[u],val);
        u=fa[bel[u]];
    }
    if(deep[u]>deep[v]) swap(u,v);
    assign(dfn[u],dfn[v],val);
}
int ask(int x) {
    int ans=0;
    iter ri=split(x+1),li=split(x);
    for(;li!=ri;++li) ans+=li->v;
    return ans;
}
int main(){
    scanf("%d",&n);
    rep(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    dfs1(1,0,1);
    dfs2(1,1);
    odt.insert(node(1,n,0));
    scanf("%d",&q);
    rep(i,1,q) {
        int cmd,v;
        scanf("%d%d",&cmd,&v);
        if(cmd==1) {
            assign(dfn[v],dfn[v]+sz[v]-1,1);
        }
        else if(cmd==2) {
            cover(v,1,0);
        }
        else if(cmd==3) {
            printf("%d\n",ask(dfn[v]));
        }
    }
    return 0;
}
```

---

## 作者：JBLee (赞：1)

其实就是树剖的模板题，区间覆盖搞一搞就过了

坑点：1.区间覆盖时的$lazy$标记需要设为-1 2.单点修改直接变成区间修改就可以了 3.修改子树由于树剖的顺序是连续的区间，直接修改$id[x]~id[x]+size[x]-1$这一段区间中的数即可。

话不多说，直接上代码，~~大佬们也懒得看，这么水的题~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+7;
struct node{
	int l,r,sum,lazy;
}tree[maxn*4];
struct node1{
	int nxt,to;
}edge[maxn*3];
int head[maxn],cnt;
int n,m,x,y;
void add(int x,int y){
	edge[++cnt].nxt=head[x];
	edge[cnt].to=y;
	head[x]=cnt;
}
int fa[maxn],dep[maxn],id[maxn],val[maxn],size[maxn],son[maxn],top[maxn],Time;
void dfs1(int x,int f){
	fa[x]=f;
	size[x]=1;
	dep[x]=dep[f]+1;
	int maxson=-1;
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa[x]) continue;
		dfs1(v,x);
		size[x]+=size[v];
		if(size[v]>maxson){
			maxson=size[v];
			son[x]=v;
		}
	}
}
void dfs2(int x,int topf){
	top[x]=topf;
	id[x]=++Time;
	if(!son[x]) return;
	dfs2(son[x],topf);
	for(int i=head[x];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==son[x]||v==fa[x]) continue;
		dfs2(v,v);
	}
}
void build(int now,int l,int r){
	tree[now].l=l,tree[now].r=r,tree[now].lazy=-1;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(now<<1,l,mid);
	build(now<<1|1,mid+1,r);
}
void pushdown(int now){
	if(tree[now].lazy!=-1){
		tree[now<<1].sum=(tree[now<<1].r-tree[now<<1].l+1)*tree[now].lazy;
		tree[now<<1|1].sum=(tree[now<<1|1].r-tree[now<<1|1].l+1)*tree[now].lazy;
		tree[now<<1].lazy=tree[now].lazy;
		tree[now<<1|1].lazy=tree[now].lazy;
		tree[now].lazy=-1;
	}
}
void update(int now,int l,int r,int v){
	if(tree[now].l>=l&&tree[now].r<=r){
		tree[now].sum=(tree[now].r-tree[now].l+1)*v;
		tree[now].lazy=v;
		return;
	}
	pushdown(now);
	int mid=(tree[now].l+tree[now].r)>>1;
	if(l<=mid) update(now<<1,l,r,v);
	if(r>mid) update(now<<1|1,l,r,v);
	tree[now].sum=tree[now<<1].sum+tree[now<<1|1].sum;
}
int query(int now,int l,int r){
	if(tree[now].l>=l&&tree[now].r<=r) return tree[now].sum;
	pushdown(now);
	int mid=(tree[now].l+tree[now].r)>>1;
	int val=0;
	if(l<=mid) val+=query(now<<1,l,r);
	if(r>mid) val+=query(now<<1|1,l,r);
	return val; 
}
void link1(int x,int y,int v){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,id[top[x]],id[x],v);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	update(1,id[y],id[x],v);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs1(1,0);dfs2(1,1);build(1,1,n);
	scanf("%d",&m);
	int opt,ljb;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&opt,&ljb);
		if(opt==1) update(1,id[ljb],id[ljb]+size[ljb]-1,1); 
		else if(opt==2) link1(ljb,1,0);
		else printf("%d\n",query(1,id[ljb],id[ljb]));
	}
	return 0;
}
```


---

## 作者：Fuko_Ibuki (赞：0)


```cpp
/*
这题的操作,询问的类型是区间覆盖.一看就知道这个题可以用树链剖分(瞎搞)过去.
我在机房写了30分钟,调了一会,发现我理解错了题意,操作2是清空到根节点的路径. 
(没想到我把操作2理解成清空子树,操作3理解成询问以u为根的子树是否全都是有水的强行能过样例)
然后还是不对.后来我看到了我线段树里的push_down这个函数,大笑不止.
我不知道这题的代码有什么好解释的,模板里的比这个还复杂一些.
*/
#include<bits/stdc++.h> //Ithea Myse Valgulious
namespace chtholly{
typedef long long ll;
#define re0 register int
#define rec register char
#define rel register ll
#define gc getchar
#define pc putchar
#define p32 pc(' ')
#define pl puts("")
/*By Citrus*/
inline int read(){
  re0 x=0,f=1;rec c=gc();
  for (;!isdigit(c);c=gc()) f^=c=='-';
  for (;isdigit(c);c=gc()) x=x*10+c-'0';
  return x*(f?1:-1);
  }
inline void read(rel &x){
  x=0;re0 f=1;rec c=gc();
  for (;!isdigit(c);c=gc()) f^=c=='-';
  for (;isdigit(c);c=gc()) x=x*10+c-'0';
  x*=f?1:-1;
  }
template <typename mitsuha>
inline int write(mitsuha x){
  if (!x) return pc(48);
  if (x<0) x=-x,pc('-');
  re0 bit[20],i,p=0;
  for (;x;x/=10) bit[++p]=x%10;
  for (i=p;i;--i) pc(bit[i]+48);
  }
inline char fuhao(){
  rec c=gc();
  for (;isspace(c);c=gc());
  return c;
  }
}using namespace chtholly;
using namespace std;
const int yuzu=5e5;
typedef int fuko[yuzu|10];
vector<int> lj[yuzu|10];
int n,m;

namespace shu_lian_pou_fen{
fuko sz,fa,dep,son,dfn,ord,top;int cnt;

void dfs1(int u,int f){//树剖专用dfs
  fa[u]=f,dep[u]=dep[f]+1,sz[u]=1;
  for (int v:lj[u]) if (v^f){
    dfs1(v,u),sz[u]+=sz[v];
    if (sz[v]>sz[son[u]]) son[u]=v;
    }
  }

void dfs2(int u,int _top){
  top[u]=_top,dfn[u]=++cnt,ord[cnt]=u;
  if (son[u]) dfs2(son[u],_top);
  for (int v:lj[u]){
    if (v^fa[u]&&v!=son[u]) dfs2(v,v);
    }
  }

typedef int yuki[yuzu<<2|13];
struct segtree{//线段树处理区间覆盖.
#define le rt<<1
#define ri le|1
#define ls le,l,mid
#define rs ri,mid+1,r
yuki val,lazy;
void build(int rt=1,int l=1,int r=n){
  lazy[rt]=-1;
  if (l==r) val[rt]=0;
  else{
    int mid=l+r>>1;
    build(ls),build(rs);
    val[rt]=0;
    }
  }
void push_down(int rt,int l,int r){
  /*好吧.这里注意标记一定要处理成-1.*/
  if (~lazy[rt]){
    lazy[le]=lazy[ri]=lazy[rt];
    val[le]=val[ri]=lazy[rt];
    lazy[rt]=-1;  
    }
  }
void update(int ql,int qr,int v,int rt=1,int l=1,int r=n){
  if (ql>r||qr<l) return;
  if (ql<=l&&qr>=r) val[rt]=lazy[rt]=v;
  else{  
    int mid=l+r>>1;
    push_down(rt,l,r);
	update(ql,qr,v,ls),update(ql,qr,v,rs);
	}
  }
int query(int u,int rt=1,int l=1,int r=n){
  if (u<l||u>r) return 1;
  if (l==r) return val[rt];
  int mid=l+r>>1;
  push_down(rt,l,r);
  return query(u,ls)&query(u,rs);
  }
}my_;

void update(int u,int v){
  for (;top[u]!=top[v];u=fa[top[u]]){
    if (dep[top[u]]<dep[top[v]]) swap(u,v);
    my_.update(dfn[top[u]],dfn[u],0);//不断处理u所在的链并向上跳.
    }
  if (dep[u]>dep[v]) swap(u,v);
  my_.update(dfn[u],dfn[v],0);
  }

int main(){
  re0 i;
  n=read();
  for (i=1;i<n;++i){
    int u=read(),v=read();
    lj[u].push_back(v);
    lj[v].push_back(u);
    }
  dfs1(1,0),dfs2(1,1);
  my_.build();
  for (m=read();m--;){
    int k=read(),u=read();
    if (k==1){
      my_.update(dfn[u],dfn[u]+sz[u]-1,1);
	  }
	if (k==2){
	  update(1,u);
	  }
	if (k==3){
	  write(my_.query(dfn[u])),pl;
	  }
    }
  }
}

int main(){
shu_lian_pou_fen::main();
}
```
这个题没有洛谷模板难,居然放在div.1的D,做出来1000多人也是正常的.  
对没错,我看到了我写的push_down函数,真的笑出了声.
```cpp
void push_down(int rt,int l,int r){
  if (~lazy[rt]){
    lazy[l]=lazy[r]=lazy[rt];
    val[l]=val[r]=lazy[rt];
    lazy[rt]=-1;  
    }
  }
```

---

## 作者：Lates (赞：0)

## 一道树剖板子题。

- 注意线段树的懒标记初始值为$-1$，如果是$0$，那后面区间制空或区间灌水就会出问题。

不会树剖的可以去[模板](https://www.luogu.com.cn/problem/P3384)看看。

$Code$：

```cpp
#include <iostream>
#include <cstdio>
#define mid (l+r>>1)
#define ls x<<1,l,mid
#define rs x<<1|1,mid+1,r
#define R 1,1,n
using namespace std;
inline int read(){
	register int x=0,v=1,ch=getchar();
	while(!isdigit(ch)){if(ch=='-')v=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^'0');ch=getchar();}
	return x*v;
}
const int MAX=500005;
int dep[MAX],siz[MAX],fa[MAX],son[MAX];
int cnt,id[MAX],top[MAX],n,m;
struct E{int e,next;}e[MAX<<1];int tot=1,head[MAX];
inline void Add(int u,int v){
	e[tot]=(E){v,head[u]};
	head[u]=tot++;
}
struct Node{int sum,tag;}tree[MAX<<2]; 
void dfs1(int x,int f){
	dep[x]=dep[f]+1;fa[x]=f,siz[x]=1;
	for(register int i=head[x];i;i=e[i].next){
		if(e[i].e!=f){
			dfs1(e[i].e,x);
			siz[x]+=siz[e[i].e];
			if(!son[x]||siz[e[i].e]>siz[son[x]])son[x]=e[i].e;
		}
	}
}
void dfs2(int x,int t){
	id[x]=++cnt,top[x]=t;
	if(son[x]){
		dfs2(son[x],t);
		for(register int i=head[x];i;i=e[i].next){
			if(e[i].e!=fa[x]&&e[i].e!=son[x])dfs2(e[i].e,e[i].e);
		}
	}
} 
inline void pushup(int x){
	tree[x].sum=tree[x<<1].sum+tree[x<<1|1].sum;
}
inline void pushdown(int x,int len){
	if(tree[x].tag==1){
		tree[x<<1]=(Node){(len-(len>>1)),1};
		tree[x<<1|1]=(Node){(len>>1),1};
	}
	if(tree[x].tag==0){
		tree[x<<1]=(Node){0,0};
		tree[x<<1|1]=(Node){0,0};
	} 
	tree[x].tag=-1;
}
void build(int x,int l,int r){
	tree[x].tag=-1;
	if(l==r)return ;
	build(ls);build(rs);
}
void modify(int x,int l,int r,int s,int t,int v){
	if(s<=l&&r<=t){
		tree[x]=(Node){(r-l+1)*v,v};
		return ;
	}
	pushdown(x,r-l+1);
	if(s<=mid)modify(ls,s,t,v);
	if(mid<t)modify(rs,s,t,v);
	pushup(x); 
}
int query(int x,int l,int r,int s,int t){
	if(s<=l&&r<=t)return tree[x].sum;
	pushdown(x,r-l+1);register int res=0;
	if(s<=mid)res+=query(ls,s,t);
	if(mid<t)res+=query(rs,s,t);
	return res;
}
void Tree_modify(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		modify(R,id[top[u]],id[u],0);
		u=fa[top[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	modify(R,id[v],id[u],0); 
}
void Son_modify(int u){
	modify(R,id[u],id[u]+siz[u]-1,1);
}
int s,t;
int main(){
	n=read();
	for(register int i=1;i<n;++i){
		s=read(),t=read();
		Add(s,t);Add(t,s);
	}
	dfs1(1,0);dfs2(1,1);build(1,1,n); 
	m=read();
	while(m--){
		s=read(),t=read();
		if(s==1){
			Son_modify(t);
		}else if(s==2){
			Tree_modify(t,1);
		}else{
			printf("%d\n",query(R,id[t],id[t]));
		}
	}
	return 0;
}
```


---

## 作者：Setsugesuka (赞：0)

不难发现，题目要我们维护以下三种操作。

1. 链赋值

2. 子树赋值

3. 单点查询

$ODT$ 可以很好的解决这类问题，我们只需要用 $ODT$ 来维护树剖的 $DFS$ 序即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

template <class T>
inline bool read(T &ret)
{
    char c;
    int sgn;
    if (c = getchar(), c == EOF)
    {
        return 0;
    }
    while (c != '-' && (c < '0' || c > '9'))
    {
        c = getchar();
    }
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9')
    {
        ret = ret * 10 + (c - '0');
    }
    ret *= sgn;
    return 1;
}

template <class T>
inline void write(T x)
{
    if (x > 9)
    {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}

const int MAXN=1e6+10;

struct node
{
    int l,r;
    mutable int v;
    node(int L,int R=-1,int V=0):l(L),r(R),v(V) {}
    bool operator <(const node &o) const
    {
        return l<o.l;
    }
};

struct edge
{
    int u,v,nex;
};

set<node> s;
edge e[MAXN<<1];
int head[MAXN],cnt=0;
int dep[MAXN],sz[MAXN],son[MAXN],top[MAXN],fa[MAXN],id[MAXN],tot=0;
int n,m;

inline void add(int u,int v)
{
    e[++cnt].u=u;
    e[cnt].v=v;
    e[cnt].nex=head[u];
    head[u]=cnt;
}

inline set<node>::iterator split(int pos)
{
    set<node>::iterator it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos)
        return it;
    --it;
    int L=it->l,R=it->r,V=it->v;
    s.erase(it);
    s.insert(node(L,pos-1,V));
    return s.insert(node(pos,R,V)).first;
}

inline void assignval(int l,int r,int v)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,v));
}

inline int sum(int pos)
{
    set<node>::iterator it=split(pos);
    write(it->v);
    putchar('\n');
}

void dfs1(int u)
{
    sz[u]=1;
    for(int i=head[u];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(v==fa[u]) continue;
        dep[v]=dep[u]+1;
        fa[v]=u;
        dfs1(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]])
            son[u]=v;
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    id[u]=++tot;
    if(!son[u])
        return;
    dfs2(son[u],tp);
    for(int i=head[u];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
}

inline void update(int pos)
{
    int tpos=top[pos];
    while(tpos!=1)
    {
        assignval(id[tpos],id[pos],0);
        pos=fa[tpos],tpos=top[pos];
    }
    assignval(id[1],id[pos],0);
}

int main()
{
    read(n);
    for(int i=1;i<n;i++)
    {
        int x,y;
        read(x),read(y);
        add(x,y);
        add(y,x);
    }
    dfs1(1);
    dfs2(1,1);
    s.insert(node(0,500010));
    read(m);
    while(m--)
    {
        int op,sr;
        read(op),read(sr);
        if(op==1)
            assignval(id[sr],id[sr]+sz[sr]-1,1);
        else if(op==2)
            update(sr);
        else
            sum(id[sr]);
    }
    return 0;
}
```


---

## 作者：qiyue7 (赞：0)

很水的一道题 大力树剖就完事了 nlog^2n跑50w最大case才700ms (树剖实际上跑不满的复杂度)这题就是很显然的区间覆盖+树剖 如果板子封装的好，边界条件都有良性的定义，这题甚至连细节难度都没有了。。。 如果还想更快的话不建立全局线段树而是针对每个重链建线段树应该就能得到更优的复杂度了 如果考虑代码长度的话还是考虑ODT+树剖好（1800ms）

线段树+树剖代码：

```cpp

#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<deque>
#include<iomanip>
#include<sstream>
#include<stack>
#include<iostream>
#include<limits>
#include<bitset>
#include<list>
#include<queue>
#include<memory>
#include<functional>
#include<cstdio>
#include<array>
using namespace std;
using namespace std;
const int N = 602000;
namespace tree_split1
{
	//前向星部分
	struct graph
	{
		int Begin[N * 2], to[N * 2], Next[N * 2], e, weight[N * 2];
		void add(int u, int v)
		{
			to[++e] = v;
			Next[e] = Begin[u];
			Begin[u] = e;
		}
		void add(int u, int v, int w)
		{
			to[++e] = v;
			Next[e] = Begin[u];
			Begin[u] = e;
			weight[e] = w;
		}
		void init_graph()
		{
			e = 0;
			memset(Begin, -1, sizeof(Begin));
		}
	};
	int id[N];
	class tree_split
	{
	public:
		long long dep[N], fa[N], top[N], size1[N], son[N], weight[N], new_weight[N];
		int len;
		graph g;
		tree_split()
		{
			memset(fa, 0, sizeof(fa));
			memset(top, 0, sizeof(top));
			memset(size1, 0, sizeof(size1));
			memset(son, 0, sizeof(son));
			memset(g.Begin, -1, sizeof(g.Begin));
			memset(weight, 0, sizeof(weight));
			len = 0;
		}
		void init(int root)
		{
			dep[root] = 0;
			dfs1(root, root);
			dfs2(root, root);
		}
		void add_weight(int i, int w)
		{
			weight[i] = w;
		}
		void add_edge(int u, int v)
		{
			g.add(u, v);
			g.add(v, u);
		}
		void dfs1(int u, int father)//一和二是完整树链剖分的预处理
		{
			dep[u] = dep[father] + 1;
			fa[u] = father;
			size1[u] = 1;
			for (int i = g.Begin[u]; i != -1; i = g.Next[i])
			{
				if (g.to[i] != father)
				{
					dfs1(g.to[i], u);
					size1[u] += size1[g.to[i]];
					if (size1[g.to[i]] > size1[son[u]])
						son[u] = g.to[i];
				}
			}
		}
		void dfs2(int u, int topf)
		{
			id[u] = ++len;
			new_weight[len] = weight[u];
			top[u] = topf;
			if (son[u] == 0)return;
			dfs2(son[u], topf);
			for (int i = g.Begin[u]; i != -1; i = g.Next[i])
			{
				if (g.to[i] == fa[u] || g.to[i] == son[u]) continue;
				dfs2(g.to[i], g.to[i]);
			}
		}
		int find(int u)
		{
			return top[u] = top[u] == u ? u : find(top[u]);
		}
		int LCA(int u, int v) {
			if (find(u) != find(v))
				return dep[top[u]] > dep[top[v]] ? LCA(fa[top[u]], v) : LCA(u, fa[top[v]]);
			else return dep[u] > dep[v] ? v : u;
		}
	}tp;
}
using namespace tree_split1;
namespace segment_tree
{
	/**
	*    基础部分
	**/
	struct node
	{
		int L, R, sum, sum2, modify;
		bool lazy;
	};
	struct tree
	{
		node tree_pool[N * 4];
		int pool[N];
		void clear_tree(int sum)
		{
			memset(pool, 0, sizeof(pool));
			for (int i = 0; i < sum * 4; ++i)
				tree_pool[i].lazy = false;
		}
		void update(int cur)
		{
			tree_pool[cur].sum = tree_pool[cur << 1].sum + tree_pool[(cur << 1) + 1].sum;
		}
		void build(int cur, int L, int R)
		{
			int mid = (L + R) / 2;
			tree_pool[cur].L = L;
			tree_pool[cur].R = R;
			tree_pool[cur].sum2 = 0;
			tree_pool[cur].modify = 0;
			if (L == R)
			{
				tree_pool[cur].sum = pool[L];
				return;
			}
			build(cur << 1, L, mid);
			build((cur << 1) + 1, mid + 1, R);
			update(cur);
		}
		void push_down_modify(int cur)
		{
			tree_pool[cur].sum = tree_pool[cur].sum2*(tree_pool[cur].R - tree_pool[cur].L + 1);
			tree_pool[cur].lazy = false;
			if (tree_pool[cur].L != tree_pool[cur].R)
			{
				tree_pool[cur << 1].lazy = true;
				tree_pool[(cur << 1) + 1].lazy = true;
				tree_pool[cur << 1].sum2 = tree_pool[cur].sum2;
				tree_pool[cur << 1].sum = tree_pool[cur << 1].sum2*(tree_pool[cur << 1].R - tree_pool[cur << 1].L + 1);
				tree_pool[(cur << 1) + 1].sum2 = tree_pool[cur].sum2;
				tree_pool[(cur << 1) + 1].sum = tree_pool[(cur << 1) + 1].sum2*(tree_pool[(cur << 1) + 1].R - tree_pool[(cur << 1) + 1].L + 1);
			}
		}
		void range_modify(int cur, int L, int R, int k)
		{
			int ans = 0, mid = (tree_pool[cur].L + tree_pool[cur].R) / 2;
			if (tree_pool[cur].lazy == true)
				push_down_modify(cur);
			if (L == tree_pool[cur].L && R == tree_pool[cur].R)
			{
				tree_pool[cur].sum2 = k;
				tree_pool[cur].sum = k * (tree_pool[cur].R - tree_pool[cur].L + 1);
				tree_pool[cur].lazy = true;
				return;
			}
			if (L <= mid && R > mid)
			{
				range_modify((cur << 1), L, mid, k);
				range_modify((cur << 1) + 1, mid + 1, R, k);
			}
			else if (R <= mid)
				range_modify((cur << 1), L, R, k);
			else if (L >= mid + 1)
				range_modify((cur << 1) + 1, L, R, k);
			update(cur);
		}
		int range_ask_sum_modify(int cur, int L, int R)
		{
			int ans = 0, mid = (tree_pool[cur].L + tree_pool[cur].R) / 2;
			if (tree_pool[cur].lazy)
				push_down_modify(cur);
			if (L == tree_pool[cur].L && R == tree_pool[cur].R)
				return tree_pool[cur].sum;
			if (L <= mid && R > mid)
				ans += range_ask_sum_modify((cur << 1), L, mid) + range_ask_sum_modify((cur << 1) + 1, mid + 1, R);
			else if (R <= mid)
				ans += range_ask_sum_modify((cur << 1), L, R);
			else if (L >= mid + 1)
				ans += range_ask_sum_modify((cur << 1) + 1, L, R);
			return ans;
		}
	}tree;
}
using namespace segment_tree;
struct FastIO {
	static const int S = 1e7;
	int wpos;
	char wbuf[S];
	FastIO() : wpos(0) {}
	inline int xchar() {
		static char buf[S];
		static int len = 0, pos = 0;
		if (pos == len)
			pos = 0, len = fread(buf, 1, S, stdin);
		if (pos == len) exit(0);
		return buf[pos++];
	}
	inline int xuint() {
		int c = xchar(), x = 0;
		while (c <= 32) c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
		return x;
	}
	inline int readint()
	{
		int s = 1, c = xchar(), x = 0;
		while (c <= 32) c = xchar();
		if (c == '-') s = -1, c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
		return x * s;
	}
	inline void xstring(char *s)
	{
		int c = xchar();
		while (c <= 32) c = xchar();
		for (; c > 32; c = xchar()) * s++ = c;
		*s = 0;
	}
	inline void wchar(int x)
	{
		if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
		wbuf[wpos++] = x;
	}
	inline void wint(int x)
	{
		if (x < 0) wchar('-'), x = -x;
		char s[24];
		int n = 0;
		while (x || !n) s[n++] = '0' + x % 10, x /= 10;
		while (n--) wchar(s[n]);
		//wchar('\n');
	}
	inline void wint(long long x)
	{
		if (x < 0) wchar('-'), x = -x;
		char s[24];
		int n = 0;
		while (x || !n) s[n++] = '0' + x % 10, x /= 10;
		while (n--) wchar(s[n]);
		//wchar('\n');
	}
	inline void wstring(string &s)
	{
		for (auto &p : s)
			wchar(p);
	}
	~FastIO()
	{
		if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
	}
} io;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, q,op,x,u,v;
	n = io.readint();
	for (int i = 1; i < n; ++i)
	{
		u = io.readint();
		v = io.readint();
		tp.add_edge(u, v);
	}
	tp.init(1);
	tree.clear_tree(n);
	tree.build(1, 1, n);
	q = io.readint();
	while (q--)
	{
		op = io.readint();
		x = io.readint();
		if (op == 1)
			tree.range_modify(1,id[x], id[x] + tp.size1[x] - 1, 1);
		else if (op == 2)
		{
			int y=tp.top[x];
			while (y != 1)
			{
				tree.range_modify(1,id[y], id[x], 0);
				x = tp.fa[tp.top[x]];
				y = tp.top[x];
			}
			tree.range_modify(1,id[y], id[x], 0);
		}
		else
			io.wint(tree.range_ask_sum_modify(1,id[x], id[x])),io.wchar('\n');
	}
	return 0;
}



```


---

## 作者：周子衡 (赞：0)

思路：树链剖分

树剖后，随便瞎做做不就行了吗……

这里只说几个细节

看到楼下有人说只会“区间加”不会“区间赋值”，其实两者很类似，把+=改成=就行了

我的代码里对于add标记是这么处理的：若$add=-1$，表示没有标记，否则表示对应标记

另外单独写单点查询很麻烦，于是我写的是区间查询（调用时类似$query(i,i)$）

写的时候犯了一个$SB$错误：居然没有建线段树就开始跑了，死磕样例（莫名尴尬）

~~我才不会告诉你我是把之前几道树剖代码拼在一起呢~~

代码：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

int w[500001]={};
vector<int> ed[500001]={};
int fa[500001],dep[500001],sz[500001],son[500001],top[500001],seg[500001],rev[500001];

void dfs_bas(int pos=1,int f=0)
{
    sz[pos]=1,fa[pos]=f,dep[pos]=dep[f]+1;
    for(int i=0,v=0;i<ed[pos].size();i++)
    {
        v=ed[pos][i];
        if(v!=f)
        {
            dfs_bas(v,pos);
            sz[pos]+=sz[v];
            if(sz[v]>sz[son[pos]])
            {
                son[pos]=v;
            }
        }
    }
}
void dfs_sec(int pos=1,int f=0)
{
    if(son[pos])
    {
        seg[son[pos]]=++seg[0];
        top[son[pos]]=top[pos];
        rev[seg[0]]=son[pos];
        dfs_sec(son[pos],pos);
    }
    for(int i=0,v=0;i<ed[pos].size();i++)
    {
        v=ed[pos][i];
        if(top[v])
        {
            continue;
        }
        
        seg[v]=++seg[0];
        rev[seg[0]]=v;
        top[v]=v;
        dfs_sec(v,pos);
    }
}

struct nd
{
    int l,r,sum,add;
}t[2000001]={};
void build(int l,int r,int k=1)
{
    t[k].l=l,t[k].r=r,t[k].add=-1,t[k].sum=0;
    if(l==r)
    {
        return;
    }
    int mid=(l+r)/2;
    build(l,mid,k*2),build(mid+1,r,k*2+1);
}
void spread(int k)
{
    if(t[k].add==-1)
    {
        return;
    }
    t[k*2].sum=(t[k*2].r-t[k*2].l+1)*t[k].add,t[k*2+1].sum=(t[k*2+1].r-t[k*2+1].l+1)*t[k].add;
    t[k*2].add=t[k*2+1].add=t[k].add;
    t[k].add=-1;
}

int query(int l,int r,int k=1)
{
    if(l>t[k].r||r<t[k].l)
    {
        return 0;
    }
    if(l<=t[k].l&&r>=t[k].r)
    {
        return t[k].sum;
    }
    spread(k);
    return query(l,r,k*2)+query(l,r,k*2+1);
}
void change(int l,int r,int v,int k=1)
{
    if(l>t[k].r||r<t[k].l)
    {
        return;
    }
    if(l<=t[k].l&&r>=t[k].r)
    {
        t[k].sum=v*(t[k].r-t[k].l+1),t[k].add=v;return;
    }
    spread(k);change(l,r,v,k*2),change(l,r,v,k*2+1);
    t[k].sum=t[k*2].sum+t[k*2+1].sum;
}
int ask_road(int x,int y)
{
    int fx=top[x],fy=top[y],ans=0;
    while(fx!=fy)
    {
        if(dep[fx]<dep[fy])
        {
            swap(fx,fy),swap(x,y);
        }
        ans+=query(seg[fx],seg[x]);
        x=fa[fx];fx=top[x];
    }
    if(dep[x]>dep[y])
    {
        swap(x,y);
    }
    return ans+query(seg[x],seg[y]);
}
void change_road(int x,int y,int v)
{
    int fx=top[x],fy=top[y];
    while(fx!=fy)
    {
        if(dep[fx]<dep[fy])
        {
            swap(fx,fy),swap(x,y);
        }
        change(seg[fx],seg[x],v);
        x=fa[fx];fx=top[x];
    }
    if(dep[x]>dep[y])
    {
        swap(x,y);
    }
    change(seg[x],seg[y],v);
}

int ask_sbt(int x)
{
    return query(seg[x],seg[x]+sz[x]-1);
}
void change_sbt(int x,int v)
{
    change(seg[x],seg[x]+sz[x]-1,v);
}

int main()
{
	int n=0;scanf("%d",&n);
    for(int i=1,a=0,b=0;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        ed[a].push_back(b),ed[b].push_back(a);
    }
    dfs_bas();
    
    
    seg[0]=seg[1]=top[1]=rev[1]=1;
    dfs_sec();
    
    build(1,n);//千万别忘了这个！！！
    
    int q=0;scanf("%d",&q);
    int c=0,v=0;
    while(q--)
    {
    	scanf("%d%d",&c,&v);
    	switch(c)
    	{
    		case 1:
    			change_sbt(v,1);
    			break;
    		case 2:
    			change_road(1,v,0);
    			break;
    		case 3:
    			printf("%d\n",ask_road(v,v));
    			break;
		}
	}
	return 0;
}
```

---

## 作者：Styx (赞：0)

### @ Fuko_Ibuki orz !!! 竟然用了区间覆盖的线段树，不愧是大佬啊！

像我这种蒟蒻只会用最简单的区间加线段树啊QAQ

好的，其实吧，区间加线段树也能完全胜任这这道题的，毕竟是单点查询嘛~

之后就只是最基本的树链剖分操作：路径修改和子树修改了，查询是单点查询的，连push_up都不用写啊……

复杂度的话应该是nlognlogn的，感觉50w有点虚，但事实上最大的点也只跑了不到1s，基本上还是稳得啦

代码如下：
```cpp
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define lson root<<1
#define rson root<<1|1
using namespace std;

struct node
{
	int l,r,sum,lazy;
}tr[2000020];
vector<int> g[500050];
int deep[500050],size[500050],fa[500050],son[500050],id[500050],top[500050],cnt;

void push_down(int root)
{
	int mid=(tr[root].l+tr[root].r)>>1;
	tr[lson].sum=tr[root].lazy*(mid-tr[root].l+1);
	tr[lson].lazy=tr[root].lazy;
	tr[rson].sum=tr[root].lazy*(tr[root].r-mid);
	tr[rson].lazy=tr[root].lazy;
	tr[root].lazy=-1;
}

void build(int root,int l,int r)
{
	if(l==r)
	{
		tr[root].l=l;
		tr[root].r=r;
		tr[root].lazy=-1;
		tr[root].sum=0;
		return ;
	}
	tr[root].l=l;
	tr[root].r=r;
	tr[root].lazy=-1;
	int mid=(l+r)>>1;
	build(lson,l,mid);
	build(rson,mid+1,r);
}

void update(int root,int l,int r,int val)
{
	if(tr[root].l==l&&tr[root].r==r)
	{
		tr[root].sum=val;
		tr[root].lazy=val;
		return ;
	}
	if(~tr[root].lazy)
	{
		push_down(root);
	}
	int mid=(tr[root].l+tr[root].r)>>1;
	if(mid<l)
	{
		update(rson,l,r,val);
	}
	else
	{
		if(mid>=r)
		{
			update(lson,l,r,val);
		}
		else
		{
			update(lson,l,mid,val);
			update(rson,mid+1,r,val);
		}
	}
}

int query(int root,int l,int r)
{
	if(tr[root].l==l&&tr[root].r==r)
	{
		return tr[root].sum;
	}
	if(~tr[root].lazy)
	{
		push_down(root);
	}
	int mid=(tr[root].l+tr[root].r)>>1;
	if(mid<l)
	{
		return query(rson,l,r);
	}
	else
	{
		if(mid>=r)
		{
			return query(lson,l,r);
		}
		else
		{
			return query(lson,l,mid)+query(rson,mid+1,r); 
		}
	}
}

void dfs1(int now,int f,int dep)
{
	fa[now]=f;
	size[now]=1;
	deep[now]=dep;
	int maxson=-1;
	for(int i=0;i<g[now].size();i++)
	{
		if(g[now][i]==f)
		{
			continue;
		}
		dfs1(g[now][i],now,dep+1);
		size[now]+=size[g[now][i]];
		if(size[g[now][i]]>maxson)
		{
			maxson=size[g[now][i]];
			son[now]=g[now][i];
		}
	}
}

void dfs2(int now,int topf)
{
	id[now]=++cnt;
	top[now]=topf;
	if(!son[now])
	{
		return ;
	}
	dfs2(son[now],topf);
	for(int i=0;i<g[now].size();i++)
	{
		if(g[now][i]==son[now]||g[now][i]==fa[now])
		{
			continue;
		}
		dfs2(g[now][i],g[now][i]);
	}
}

void sub_update(int x)
{
	update(1,id[x],id[x]+size[x]-1,1);
}

void path_update(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(deep[top[u]]<deep[top[v]])
		{
			swap(u,v);
		}
		update(1,id[top[u]],id[u],0);
		u=fa[top[u]];
	}
	if(deep[u]>deep[v])
	{
		swap(u,v);
	}
	update(1,id[u],id[v],0);
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int from,to;
		scanf("%d%d",&from,&to);
		g[from].push_back(to);
		g[to].push_back(from);
	}
	dfs1(1,0,1);
	dfs2(1,1);
	build(1,1,n);
	int m;
	scanf("%d",&m);
	while(m--)
	{
		int kd,u;
		scanf("%d%d",&kd,&u);
		if(kd==1)
		{
			sub_update(u);
		}
		else
		{
			if(kd==2)
			{
				path_update(1,u);
			}
			else
			{
				printf("%d\n",query(1,id[u],id[u]));
			}
		}
	}
}

```

---

