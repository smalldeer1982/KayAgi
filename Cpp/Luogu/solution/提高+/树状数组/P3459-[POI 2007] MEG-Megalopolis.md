# [POI 2007] MEG-Megalopolis

## 题目描述

Byteotia has been eventually touched by globalisation, and so has Byteasar the Postman, who once roamedthe country lanes amidst sleepy hamlets and who now dashes down the motorways. But it is those strolls inthe days of yore that he reminisces about with a touch of tenderness.

In the olden days $n$ Byteotian villages (numbered from $1$ to $n$) were connected by bidirectional dirt roadsin such a way, that one could reach the village number $1$ (called Bitburg) from any other village in exactlyone way. This unique route passed only through villages with number less or equal to that of the startingvillage. Furthermore, each road connected exactly two distinct villages without passing through any othervillage. The roads did not intersect outside the villages, but tunnels and viaducts were not unheard of.

Time passing by, successive roads were being transformed into motorways. Byteasar remembers distinctly,  when each of the country roads so disappeared. Nowadays, there is not a single country lane left  in Byteotia - all of them have been replaced with motorways, which connect the villages into Byteotian  Megalopolis.

Byteasar recalls his trips with post to those villages. Each time he was beginning his journey with letters  to some distinct village in Bitburg. He asks you to calculate, for each such journey (which took place in a      specific moment of time and led from Bitburg to a specified village), how many country roads it led through.

TaskWrite a programme which:

reads from the standard input:

descriptions of roads that once connected Byteotian villages,    sequence of events: Byteasar's trips and the moments when respective roads were transformed    into motorways,            for each trip, calculates how many country roads Byteasar has had to walk,        writes the outcome to the standard output.


有一棵节点数为 $n$ 的树，给定 $m + n - 1$ 组询问，每组询问有两种操作。

1. `A x y`，将 $x$ 节点和 $y$ 节点间的边权改为 $0$，每条边会被修改恰好一次。

2. `W x`，求 $1$ 号点到 $x$ 号点路径上的边权和。

初始所有边权值都为 $1$。

## 样例 #1

### 输入

```
5
1 2
1 3
1 4
4 5
4
W 5
A 1 4
W 5
A 4 5
W 5
W 2
A 1 2
A 1 3```

### 输出

```
2
1
0
1```

# 题解

## 作者：浅色调 (赞：19)

### Solution:

　　本题翻译有毒。我解释一波题意：给定一棵根节点为$1$，$n$个节点的树，原本每条边长度为$1$，有$m+n-1$次操作，每次修改一条边使得边权为$0$，或者查询$1$到某个点的距离（边权和）。
  
  $\quad\;\;$**核心思路：$dfs$序+离散+线段树**

　　不难发现，每次修改一条边（假设是$u->v$），到根节点距离会减少的点实际上就是以$v$为根节点的子树上的所有的点。

　　于是我们先求出$dfs$序，得到每棵子树，并统计每个子树的大小。

　　然后对$dfs$序从前往后扫，离散一下，这样保证离散后的$dfs$序从小到大排列，使得子树之间不会有交集，便可以用一棵线段树维护所有子树的信息。

　　那么每次操作时，就是区间修改和单点查询了，每次输出的是所需节点子树大小减去单点查询的值。

$\quad\; \;$欢迎来踩博客：[five20](http://www.cnblogs.com/five20/p/9045377.html)（蒟蒻写题解不易，转载请注明出处，万分感谢！）
### 代码：
```cpp
#include<bits/stdc++.h>
#define il inline
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define For(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
using namespace std;
const int N=250005;
int n,dfn[N<<2],ct,cnt,h[N],to[N],net[N],dep[N],tot[N];
int mp[N],add[N<<2],sum[N<<2],p,m;
char s[4];
il int gi(){
    int a=0;char x=getchar();
    while(x<'0'||x>'9')x=getchar();
    while(x>='0'&&x<='9')a=(a<<3)+(a<<1)+x-48,x=getchar();
    return a;
}
il void addd(int u,int v){to[++cnt]=v,net[cnt]=h[u],h[u]=cnt;}
il void dfs1(int x){
    dfn[++ct]=x;tot[x]=1;
    for(int i=h[x];i;i=net[i])dep[to[i]]=dep[x]+1,dfs1(to[i]),tot[x]+=tot[to[i]];
    dfn[++ct]=x;
}
il void pushup(int rt){sum[rt]=sum[rt<<1]+sum[rt<<1|1];}
il void pushdown(int rt,int k){
    if(add[rt]){
        add[rt<<1]+=add[rt];
        add[rt<<1|1]+=add[rt];
        sum[rt<<1]+=add[rt]*(k-(k>>1));
        sum[rt<<1|1]+=add[rt]*(k>>1);
        add[rt]=0;
    }
}
il void update(int L,int R,int c,int l,int r,int rt){
    if(L<=l&&R>=r){
        add[rt]+=c;sum[rt]+=c*(r-l+1);
        return;
    }
    pushdown(rt,r-l+1);
    int m=l+r>>1;
    if(L<=m)update(L,R,c,lson);
    if(m<R)update(L,R,c,rson);
    pushup(rt);
}
il int query(int L,int R,int l,int r,int rt){
    if(L<=l&&R>=r)return sum[rt];
    pushdown(rt,r-l+1);
    int m=l+r>>1,ret=0;
    if(L<=m)ret+=query(L,R,lson);
    if(m<R)ret+=query(L,R,rson);
    return ret;
}
int main(){
    n=gi();
    int u,v;
    For(i,1,n-1)u=gi(),v=gi(),addd(u,v);
    dfs1(1);
    For(i,1,ct)
        if(!mp[dfn[i]])mp[dfn[i]]=++p,dfn[i]=p;
        else dfn[i]=mp[dfn[i]];
    m=gi()+n-1;
    while(m--){
        scanf("%s",s);
        if(s[0]=='W'){
            u=gi();
            printf("%d\n",dep[u]-query(mp[u],mp[u],1,n,1));
        }
        else{
            u=gi();v=gi();
            if(u<v)swap(u,v);
            update(mp[u],mp[u]+tot[u]-1,1,1,n,1);
        }
    }
    return 0;
}
```


---

## 作者：M_seа (赞：9)


样例说明：

![](http://www.lydsy.com/JudgeOnline/images/1103.jpg)

算法：dfs序+树状数组

很明显，题目给了我们一颗树(以1为根节点），并在树上进行了查询和修改操作。对于u->v这一条路径，我们可以用v来表示这条路径（当v为1表示该路径为土路，0为公路）。显然，到X点经过土路的数量，就是1->X经过点的权值
当X点被改动时，它影响的范围是以它为根节点的子树

这东西很明显可以用树链剖分做，但这里我们讲的是利用dfs序的方法

Q：什么是dfs序？？ 
A：就是dfs遍历顺序啊，比如样例的dfs序就是：1 4 5 2 3

那么，怎么使用dfs序呢？ 
不难发现dfs序中， 每一颗子树都分别位于一个区间中，我们只要记下区间范围，就可以避免题目中分枝的问题，那么题目就可以转化成 区间修改+单点查询 了。 
做过[洛谷 P3368 【模板】树状数组 2](https://www.luogu.org/problemnew/show/P3368)的人应该都知道，这可以用树状数组维护差分数组， 查询就是统计前缀和。 

这样问题就解决了。

[代码链接](http://blog.csdn.net/qq_36288976/article/details/79364299)


---

## 作者：timsu1104 (赞：8)

DFS+树状数组

用树状数组存储，前缀和代表到达经过的土路数。

用DFS遍历每一个点，记录进入时刻和离开时刻，这样只有在两个时刻之间出现的点才是这个点的子树。

每次修路都用树状数组维护。


    
    
    
    
    
```cpp
    #include<cstdio>
    #include<cstdlib>
    using namespace std;
    const int maxn=250000;
    int n,m,u,v,clock,size;
    int val[maxn],in[maxn],leave[maxn],h[maxn];
    char c;
    int max(int a,int b){return a>b?a:b;}
    //树状数组
    int lowbit(int x) {return x&(-x);}
    void add(int x,int a)
    {
        while(x<=n)
        {
            val[x]+=a;
            x+=lowbit(x);
        }
    }
    int sum(int x)
    {
        int res=0;
        while(x>0)
        {
            res+=val[x];
            x-=lowbit(x);
        }
        return res;
    }
    //边
    struct edge{int v,next;} e[maxn<<1];
    int addedge(int u,int v)
    {
        e[++size].v=v; e[size].next=h[u]; h[u]=size;
        e[++size].v=u; e[size].next=h[v]; h[v]=size;
    }
    void dfs(int p)
    {
        in[p]=++clock;
        for(int i=h[p];i+1;i=e[i].next)
            if(!in[e[i].v]) dfs(e[i].v);
        leave[p]=clock;
    }
    int main()
    {
        scanf("%d",&n);
        for(int i=0;i<=n;i++) h[i]=-1;
        for(int i=1;i<n && scanf("%d%d",&u,&v);i++) addedge(u,v);
        dfs(1);
        for(int i=2;i<=n;i++) add(in[i],1),add(leave[i]+1,-1);
        scanf("%d",&m);
        for(int i=1;i<m+n;i++)
        {
            getchar();
            scanf("%c%d",&c,&v);
            if(c=='A')
            {
                scanf("%d",&u);
                add(in[max(u,v)],-1);
                add(leave[max(u,v)]+1,1);
            }
            else printf("%d\n",sum(in[v]));
        }
        return 0;
}
```

---

## 作者：FlashHu (赞：5)

dfn序上的前缀和，这样的思路真是又玄学又令我惊叹（ ~~我太弱啦，根本想不到）~~Orz各路Dalao

今天考了这道题，数据范围还比洛谷的小，只有$10^5$（害我复制粘贴一波交上去RE），让我很放心地去想树剖了。

然而尴尬的是我不会树剖，却先学了LCT（~~再次暴露蒟蒻的本性~~）

树剖的模型是，把土路视为权值，有修改，然后要查询某节点到根节点的权值和。没有换根的话，边权直接视为点权。

然后我干脆直接用Splay维护链剖分算啦（其实就是弱化板的LCT，有点像[我弹飞绵羊的写法](http://www.cnblogs.com/flashhu/p/8349984.html)，但这里连link和cut都没有）

很明显，常数巨大。。。。。。不过我还是相信，能用树剖的一定不会卡掉Splay链剖分，所以我还是放心大胆地写了。

代码如下
```
#include<cstdio>
#define R register int
#define I inline void
#define lc c[x][0]
#define rc c[x][1]
#define G c=getchar()
#define gc G;while(c<'-')G
#define in(z) gc;z=c&15;G;\
	while(c>'-')z*=10,z+=c&15,G
const int N=250009;
int f[N],c[N][2],s[N];//s表示路径上土路总和
bool tu[N];//是否为土路
inline bool nroot(R x){
	return c[f[x]][0]==x||c[f[x]][1]==x;
}
I pushup(R x){
	s[x]=s[lc]+s[rc]+tu[x];
}
I rotate(R x){
	R y=f[x],z=f[y],k=c[y][1]==x,w=c[x][!k];
	if(nroot(y))c[z][c[z][1]==y]=x;c[x][!k]=y;c[y][k]=w;
	f[w]=y;f[y]=x;f[x]=z;
	pushup(y);
}
I splay(R x){
	R y;
	while(nroot(x)){
		if(nroot(y=f[x]))
			rotate((c[f[y]][0]==y)^(c[y][0]==x)?x:y);
		rotate(x);
	}
	pushup(x);
}
I access(R x){
	for(R y=0;x;x=f[y=x])
		splay(x),rc=y,pushup(x);
}//Splay链剖分（似乎所有函数节选自LCT）
int main(){
	R n,m,u,v,i,t;
	register char c;
	in(n);
	for(i=1;i<n;++i){
		in(u);in(v);
		if(u>v)t=u,u=v,v=t;//题目保证了编号小的为父亲
		f[v]=u;tu[v]=1;
	}
	in(m);
	for(i=n+m-1;i;--i){
		gc;
		if(c=='A'){
			in(u);in(v);
			if(u>v)t=u,u=v,v=t;
			splay(v);tu[v]=0;pushup(v);//转到根再改
		}
		else{
			in(v);
			access(v);splay(v);
			printf("%d\n",s[v]);
		}
	}
	return 0;
}
```

---

## 作者：Starria的脑残粉 (赞：4)

这题有个很好的性质就是一棵树

还有就是父节点一定小于子节点所以我们可以很好的判断谁是子节点

询问求的是有几个父节点被覆盖过了

大概就是dfs序一波之后再树状数组上差分一下

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,f[2000000],d[2000000],last[2000000],a[2000000][2],l[2000000],r[2000000],k,kk,q;
char c;
inline int read(){
    char c=getchar();while (c!='-'&&(c<'0'||c>'9'))c=getchar();
    int k=1,kk=0;if (c=='-')k=-1;else kk=c-'0';c=getchar();
    while (c>='0'&&c<='9')kk=kk*10+c-'0',c=getchar();return k*kk; 
}void doit(int x,int y){a[++kk][0]=last[x];a[kk][1]=y;last[x]=kk;}
void dfs(int x,int fa,int de){
    d[x]=de;l[x]=++k;for (int i=last[x];i;i=a[i][0])
        if (a[i][1]!=fa)dfs(a[i][1],x,de+1);
    r[x]=k;
}
void putit(int x,int y){for (;x<=1000000;x+=x&(-x))f[x]+=y;}
int findit(int x){int ans=0;for (;x;x-=x&(-x))ans+=f[x];return ans;}
int main(){
    n=read();for (int i=1;i<n;i++){
        x=read();y=read();if (x>y)swap(x,y);
        doit(x,y);
    }dfs(1,0,0);q=read();while (q){
        c=getchar();while (c!='W'&&c!='A')c=getchar();
        if (c=='W'){
            x=read();q--;//q次送信所以。。
            printf("%d\n",d[x]-findit(l[x]));
        }else{
            x=read();y=read();if (x>y)swap(x,y);
            putit(l[y],1);putit(r[y]+1,-1);
        }
    }
}
```

---

## 作者：watermonster (赞：2)

### 题意
给定一个$N$个节点的树，以$1$为树的根。树上边权初始都为$1$，有$m$次询问和$n-1$次操作，每次操作将一条边的边权变为$0$，每次询问点到根的路径上边权之和。

### 注意
- 每次只会修改一条边，且每条边只会修改一次，因此正好总共会有$n-1$次修改

### **solution**
将边权看做其连接的子节点的点权，题目则变为链上单点修改$+$区间查询

~~裸的树链剖分~~

### **code**
```
#include <cstdio>
using namespace std;
#define re register
#define il inline
#define isdigit(ch) (ch>='0'&&ch<='9')
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
const int N=250050;
il void read(int &x)
{
	x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
}
il void write(int x)
{
	if(x/10) write(x/10);
	putchar(x%10+48);
}
il void swap(int &a,int &b){int tmp=a;a=b;b=tmp;}
int n,m;
int cnt,h[N];
struct edge{int v,nxt;}e[N];
il void add(int u,int v){e[++cnt]=(edge){v,h[u]};h[u]=cnt;}
int dfn[N],top[N],siz[N],son[N],fa[N];
il void dfs1(int x)
{
	siz[x]=1;
	for(re int i=h[x],v;i;i=e[i].nxt)
	{
		v=e[i].v;
		dfs1(v);
		siz[x]+=siz[v];
		if(siz[v]>siz[son[x]]) son[x]=v;
	}
}
il void dfs2(int x)
{
	dfn[x]=++dfn[0];
	if(son[x])
	{
		top[son[x]]=top[x];
		dfs2(son[x]);
	}
	for(re int i=h[x],v;i;i=e[i].nxt)
	{
		v=e[i].v;
		if(v==son[x]) continue;
		top[v]=v;
		dfs2(v);
	}
}
struct segtree{int l,r,sum;}t[N<<2];
il void build(int p,int l,int r)
{
	t[p]=(segtree){l,r,0};
	if(l==r){t[p].sum=1;return;}
	re int mid=(l+r)>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	t[p].sum=t[ls(p)].sum+t[rs(p)].sum;
}
il void change(int p,int x)
{
	if(t[p].l>x||t[p].r<x) return;
	if(t[p].l==t[p].r){t[p].sum=0;return;}
	change(ls(p),x);change(rs(p),x);
	t[p].sum=t[ls(p)].sum+t[rs(p)].sum;
}
il int query(int p,int l,int r)
{
	if(t[p].l>r||t[p].r<l) return 0;
	if(t[p].l>=l&&t[p].r<=r) return t[p].sum;
	return query(ls(p),l,r)+query(rs(p),l,r);
}
//线段树
int main()
{
	read(n);
	for(re int i=1,a,b;i<n;++i)
	{
		read(a),read(b);
		if(a<b) add(a,b),fa[b]=a;
		else add(b,a),fa[a]=b;
	}
	top[1]=1;
	dfs1(1);dfs2(1);//树链剖分
	build(1,1,n);//线段树建树
	read(m);
	m=n+m-1;//询问次数+操作次数
	while(m--)
	{
		char opt=getchar();
		while(opt!='A'&&opt!='W') opt=getchar();
		if(opt=='A')
		{
			re int u,v;
			read(u),read(v);
			if(dfn[u]>dfn[v]) swap(u,v);
			change(1,dfn[v]);
		}//修改
		else
		{
			re int x,ans=0;
			read(x);
			while(top[x]!=1)
			{
				ans+=query(1,dfn[top[x]],dfn[x]);
				x=fa[top[x]];
			}
			ans+=query(1,2,dfn[x]);
			write(ans);puts("");
		}//询问
	}
	return 0;
}
```


---

## 作者：oscar (赞：2)

【POI补全计划#43 POI2007 MEG】

我们来尝试暴力一点的做法：树剖

基本上就是无脑搞，将问题转换为：

维护树上两个操作

1.树上单条边权-1

2.查询树上点到根路径上权值和

就当是用作树链剖分模板题了

P.S.单点修改链上查询一般可以转化为dfs序，而且dfs序常数一般比树链剖分小（楼下的解法）

贴代码

```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
const int MAXN=250010;
struct node
{
    int l,r,sum;
    node *lson,*rson;
}*root,pool[MAXN*4];
int top;
node* build(int l,int r)
{
    node *tmp=&pool[++top];
    tmp->l=l;tmp->r=r;
    tmp->sum=r-l+1;
    if(l!=r)
    {
        int mid=(l+r)/2;
        tmp->lson=build(l,mid);
        tmp->rson=build(mid+1,r);
    }
    return tmp;
}
void change(node *cur,int pos)//minus 1
{
    cur->sum--;
    if(cur->l==cur->r)return;
    if(cur->lson->r>=pos)change(cur->lson,pos);
    else change(cur->rson,pos);
}
int query(node *cur,int l,int r)
{
    if(cur->l==l&&cur->r==r)
        return cur->sum;
    if(cur->lson->r>=r)return query(cur->lson,l,r);
    else if(cur->rson->l<=l)return query(cur->rson,l,r);
    else return query(cur->lson,l,cur->lson->r)+query(cur->rson,cur->rson->l,r);
}
struct edge
{
    int v,id;
    edge *next;
}*h[MAXN],epool[MAXN*2];
int etop;
inline void addedge(int u,int v)
{
    edge *tmp=&epool[++etop];tmp->v=v;tmp->next=h[u];h[u]=tmp;
    edge *pmt=&epool[++etop];pmt->v=u;pmt->next=h[v];h[v]=pmt;
}
int dep[MAXN],siz[MAXN],pa[MAXN],maxson[MAXN],paedge[MAXN],pathroot[MAXN];
void dfs1(int u)
{
    siz[u]=1;
    for(edge *tmp=h[u];tmp;tmp=tmp->next)
    {
        if(!dep[tmp->v])
        {
            dep[tmp->v]=dep[u]+1;
            pa[tmp->v]=u;
            dfs1(tmp->v);
            siz[u]+=siz[tmp->v];
            if(siz[tmp->v]>siz[maxson[u]])maxson[u]=tmp->v;
        }
    }
}
int cur;
void dfs2(int u)
{
    if(maxson[u])
    {
        paedge[maxson[u]]=++cur;
        pathroot[maxson[u]]=pathroot[u];
        dfs2(maxson[u]);
    }
    for(edge *tmp=h[u];tmp;tmp=tmp->next)
    {
        if(tmp->v!=maxson[u]&&dep[tmp->v]==dep[u]+1)
        {
            paedge[tmp->v]=++cur;
            pathroot[tmp->v]=tmp->v;
            dfs2(tmp->v);
        }
    }
}
inline int qtree(int x)
{
    int ans=0;
    while(x)
    {
        ans+=query(root,paedge[pathroot[x]],paedge[x]);
        x=pa[pathroot[x]];
    }
    return ans;
}
int main()
{
    int n,q,a,b;
    char ch;
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d",&a,&b);
        addedge(a,b);
    }
    dep[1]=1;
    dfs1(1);
    pathroot[1]=1;
    dfs2(1);
    root=build(0,n-1);
    scanf("%d",&q);
    for(int i=1;i<=n+q-1;i++)
    {
        scanf(" %c",&ch);
        if(ch=='W')
        {
            scanf("%d",&a);
            printf("%d\n",qtree(a)-1);
        }
        else
        {
            scanf("%d%d",&a,&b);
            change(root,paedge[b]);
        }
    }
    return 0;
}
```

---

## 作者：kczno1 (赞：2)

题意:

给一棵树 边权都=1

每次将一条边的边权改为0

或者询问一个点到根的边的边权和

题解:

dfs序
修改就是区间修改

询问就是单点询问

树状数组维护

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=l;i<=r;++i)
#define pb push_back

#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'0');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}

const int N=250005;
int f[N],in[N],out[N];
int c[N];
int n,m;
vector<int>link[N];

int tot;
void dfs(int x,int fr)
{
    f[x]=fr;
    in[x]=++tot;
    for(vector<int>::iterator i=link[x].begin();i!=link[x].end();++i)
    {
        if(*i!=fr) dfs(*i,x);
    }
    out[x]=tot;
}

void add(int i,int w)
{
    for(;i<=n;i+=i&-i)c[i]+=w;
}
int qiu(int i)
{
    int ans=0;
    for(;i;i-=i&-i)ans+=c[i];
    return ans;
}

int main()
{
    freopen("1.in","r",stdin);
    n=read();
    rep(i,1,n-1)
    {
        int x=read(),y=read();
        link[x].pb(y);link[y].pb(x);
    }
    
    dfs(1,0);
    
    rep(i,2,n) {++c[in[i]];--c[out[i]+1];}
    rep(i,1,n) 
    {
        int j=i+(i&-i);
        if(j<=n)c[j]+=c[i];
    }
    
    int m=read()+n-1;char type[5];
    while(m--)
    {
        scanf("%s",type);
        int x=read();
        if(*type=='W') printf("%d\n",qiu(in[x]));
        else
        {
            int y=read();
            if(f[y]==x)x=y;
            add(in[x],-1);add(out[x]+1,1);
        }
    }
}
```

---

## 作者：abandentsky (赞：1)

思路：第一次写dfs序+树状数组。修改某个节点的值将会影响以他根的子树的值。什么是dfs序呢？就是遍历的顺序。我刚开始节点编号可以用来充当dfs序。结果wrong。只能通过dfs来得到dfs序。然后就是差分了。（原理和洛谷 P3368这个题目一样）初始时，每条边都为1.如果u-v为土路，就为1.那么这个时候就让c[v]=1。全部处理完。修改某个点会造成以他为跟的子节点的值发生改变。所以就是一个区间发生了改变。如果根为1，最大叶子节点编号为3.那么这个区间就是【1,3】。怎么来的呢？就是以当前节点的dfs序为左端点，以当前节点为跟能走到最远（或者最大的为右端点）。这样就是区间修改，单点查询了。详细看代码。

```c
#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#define MAXN  250005
typedef  long long  LL;
using namespace std;

int n,m,tot;
vector<int> G[MAXN];
bool vis[MAXN];
int Left[MAXN],Right[MAXN];
int c[MAXN];

int lowbit(int x)
{
    return (x&((-1)*x));
}

void add(int x,int d)
{
    while(x<=n)
    {
        c[x]+=d;
        x+=lowbit(x);
    }
}

int sum(int x)
{
    int ans=0;
    while(x>0)
    {
        ans+=c[x];
        x-=lowbit(x);
    }
    return ans;
}

void dfs(int u,int fa)
{
    vis[u]=true;
    Left[u]=++tot;
    //tot=u;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(vis[v])
            continue;
        dfs(v,u);
    }
    Right[u]=tot;
}

int main()
{
    scanf("%d",&n);
    tot=0;
    int uu,vv;
    for(int i=1;i<n;i++)
    {
        scanf("%d %d",&uu,&vv);
        G[uu].push_back(vv);
        G[vv].push_back(uu);
    }
    memset(vis,false,sizeof(vis));
    dfs(1,-1);
    for(int i=2;i<=n;i++)
    {
        add(Left[i],1);
        add(Right[i]+1,-1);
    }
    scanf("%d",&m);
    int mm,nn;
    char ch;
    for(int i=0;i<n+m-1;i++)
    {
        cin>>ch;
        if(ch=='W')
        {
            cin>>mm;
            printf("%d\n",sum(Left[mm]));
        }
        else if(ch=='A')
        {
           cin>>mm>>nn;
            add(Left[nn],-1);
            add(Right[nn]+1,1);
        }
        //getchar();
    }
    return 0;
}

```



---

## 作者：管仲 (赞：1)

//- - - - - - - - - - - - - 申明一下这里面有很多巨佬的题解 

//****************


//********************
 _
//   _ ___我复制了很多人的题解_  __ _ 
_ 

------------


------------


------------


------------


------------


------------


------------


------------


------------
 

//复习与总结  树状数组和dfs序的总结与归纳

//####### ### 如果有人看到请忽略

//对于这样的一道题，明显是一棵树，而且应该用树状数组来解决

//可我出人意料的写了一个单源最短路  只有38分，其余全部TLE;

//代码如下

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,s,dis[100010];
int r,st;
char a;
int b,c;
int sum=0;
struct Edge 
{
	int v,w,nxt;
}e[500010];
int head[100010],cnt=0;
void addEdge(int u,int v,int w) {
	e[++cnt].v=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
struct node { 
	int u,d;
	bool operator <(const node& rhs) const {
	return d>rhs.d;
	}
};
void Dj() 
{
	for (int i=1; i<=n; i++) dis[i]=2147483647;
	dis[s]=0;
	priority_queue<node> Q;
	Q.push((node) {s,0});
	while (!Q.empty()) 
	{
		node fr=Q.top();
		Q.pop();
		int u=fr.u,d=fr.d;
		if (d!=dis[u]) continue;
		for (int i=head[u]; i; i=e[i].nxt) 
		{
			int v=e[i].v,w=e[i].w;
			if (dis[u]+w<dis[v]) 
			{
			dis[v]=dis[u]+w;
			Q.push((node) {v,dis[v]});
			}
		}
	}
}
int main()
{
	s=1;
	cin>>n;
	st=n-1;
	for (int i=1; i<=st; i++) 
	{
	int X,Y;
	cin>>X>>Y;
	addEdge(X,Y,1);
	}
	Dj();
	cin>>m;
	for(int i=1;i<=n+m-1;i++)
	{
	cin>>a;
	if(a=='W') {cin>>b; cout<<dis[b]<<endl;}
	if(a=='A') {cin>>b>>c;addEdge(b,c,0);Dj();}
	}	
	return 0;
}
```

//可如今冷静下来应该如何写

//我看了一位大佬的题解,他是用树状数组和dfs序做的满分

//首先先来说一下这个题的思路

//先求dfs序，in【x】out【x】分别表示x在序列中的位置，x子树结尾再序列中的位置。

//每次修改一条公路u-v，我们记深度更大的那个点为x（x = max(u,v)），再dfs序列中把x的子树这一段区间都-1。

//这么做是因为x的子树中的每一个点到根的路径都会经过这一条修改的边。

//那么查询的时候只需查询dfs序列中的前缀和即可。

//Q：什么是dfs序？？ A：就是dfs遍历顺序啊，比如样例的dfs序就是：1 4 5 2 3


//那么，怎么使用dfs序呢？ 不难发现dfs序中， 每一颗子树都分别位于一个区间中，我们只要记下区间范围，就可以避免题目中分枝的问题，那么题目就可以转化成 区间修改+单点查询 了。

//先来梳理一下dfs序
```cpp
void dfs(int u, int fa) {
	in[u] = ++ Clock;
	for (int i = head[u]; i; i = e[i].nex)
		if (e[i].to != fa) dfs(e[i].to, u);
	out[u] = Clock;
}
```



//最后献上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 250010;
int n, m, Clock = 0, cnt = 0;
int head[N], in[N], out[N], T[N], X[N], Y[N];
char ch[3];
struct Edge {
	int to, nex;
} e[N*2];
int lowbit(int k) {
	return k & -k;
}
void add(int x, int y) {
	e[++ cnt].to = y;
	e[cnt].nex = head[x];
	head[x] = cnt;
}
void dfs(int u, int fa) {
	in[u] = ++ Clock;
	for (int i = head[u]; i; i = e[i].nex)
		if (e[i].to != fa) dfs(e[i].to, u);
	out[u] = Clock;
}
void change(int x,int k) {
	while(x<=n) {
		T[x]+=k;
		x+=lowbit(x);
	}
}
int getSum(int x) {
	int ans=0;
	while(x!=0) {
	ans+=T[x];
	x-=lowbit(x);
	}
	return ans;
}
int main() 
{
	cin>>n;
	for (int i = 1; i < n; i ++) 
	{
	cin>>X[i]>>Y[i];
	add(X[i], Y[i]);
	add(Y[i], X[i]);
	}
	dfs(1, 0);
	for (int i = 1; i < n; i ++) 
	{
	if (in[X[i]] < in[Y[i]]) swap(X[i], Y[i]);
	change(in[X[i]], 1);
	change(out[X[i]]+1, -1); //本来所有边都是公路
	}
	cin>>m;
	for (int i = 1; i <= n+m-1; i ++) 
	{
		scanf("%s", ch);
		if (ch[0] == 'A') 
		{
		int x,y;
		cin>>x>>y;
		if (in[x] < in[y]) swap(x, y);
		change(in[x], -1);
		change(out[x]+1, 1); //修改为土路
		} 
		else 
		{
		int x;cin>>x;
		cout<<getSum(in[x])<<endl;
		}
	}
	return 0;
}
```


---

## 作者：fy0123 (赞：0)

思路和楼下差不多（~~其实是看了楼下的才想到的= =~~）

稍微详细地解释下：

先求dfs序，in[x]out[x]分别表示x在序列中的位置，x子树结尾再序列中的位置。每次修改一条公路u-v，我们记深度更大的那个点为x（x = max(u,v)），再dfs序列中把x的子树这一段区间都-1。这么做是因为x的子树中的每一个点到根的路径都会经过这一条修改的边。那么查询的时候只需查询dfs序列中的前缀和即可。

贴下代码吧

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
using namespace std;

const int N = 250010;
int n, m, clock = 0, cnt = 0;
int head[N], in[N], out[N], T[N], X[N], Y[N];
char ch[3];

struct Edge{
    int to, nex;
}e[N<<1];

inline int read()
{
    char ch = getchar(); int x = 0, flag = 0;
    while (!isdigit(ch)){ if (ch == '-') flag = 1; ch = getchar(); }
    while (isdigit(ch)){ x = x * 10 + ch - '0'; ch = getchar(); }
    return flag ? -x : x;
}

inline void write(int a){ if (a >= 10) write(a/10); putchar('0'+a%10); }
inline void writeln(int a){ write(a); puts(""); }

inline void add(int x, int y){ e[++ cnt].to = y; e[cnt].nex = head[x]; head[x] = cnt; }

inline void dfs(int u, int fa)
{
    in[u] = ++ clock;
    for (int i = head[u]; i; i = e[i].nex)
        if (e[i].to != fa) dfs(e[i].to, u);
    out[u] = clock;
}

inline void change(int k, int v){ for (; k < N; k += k&-k) T[k] += v; }
inline int getSum(int k){ int ret = 0; for (; k; k -= k&-k) ret += T[k]; return ret; }

int main()
{
    n = read();
    for (int i = 1; i < n; i ++){
        X[i] = read(), Y[i] = read();
        add(X[i], Y[i]); add(Y[i], X[i]);
    }
    dfs(1, 0);
    for (int i = 1; i < n; i ++){
        if (in[X[i]] < in[Y[i]]) swap(X[i], Y[i]);
        change(in[X[i]], 1); change(out[X[i]]+1, -1); //本来所有边都是公路
    }
    m = read();
    for (int i = 1; i <= n+m-1; i ++){
        scanf("%s", ch);
        if (ch[0] == 'A'){
            int x = read(), y = read();
            if (in[x] < in[y]) swap(x, y);
            change(in[x], -1); change(out[x]+1, 1); //修改为土路
        } else{
            int x = read();
            writeln(getSum(in[x]));
        }
    }
    return 0;
}
```

---

## 作者：数学系 (赞：0)

dfs+树状数组


dfs记录每个节点进入与离开时间。进入时权值+1，离开时权值-1。

当修路时，权值改为0。



 
 
 
 






```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;
const int maxn=250000;
int value[maxn]={},in[maxn]={},leave[maxn]={},head[maxn]={};
int size=0,Clock=0,ans=0,n=0,m=0;
struct node
{
    int v,next;
}e[maxn*2];
inline int lowbit(int x)
{
    return x&(-x);
} 
inline void add(int x,int a)
{
    while(x<=n)
    {
        value[x]+=a;
        x+=lowbit(x);
    }
}
inline int query(int x)
{
    int a=0;
    while(x>0)
    {
        a+=value[x];
        x-=lowbit(x); 
    }
    return a;
}
void addedge(int u,int v)
{
    size++;
    e[size].v=v;
    e[size].next=head[u];
    head[u]=size;
    size++;
    e[size].v=u;
    e[size].next=head[v];
    head[v]=size;
}
void dfs(int p)
{
    Clock++;
    in[p]=Clock;
    for(int i=head[p];i!=-1;i=e[i].next)
        if(!in[e[i].v])
            dfs(e[i].v);
    leave[p]=Clock;
}
int max(int a,int b)
{
    return a>b?a:b;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<=n;i++)
        head[i]=-1;
    int v,u;
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&v,&u);
        addedge(v,u);
    }
    dfs(1);
    int p;
    for(int i=2;i<=n;i++)
    {
        add(in[i],1);
        add(leave[i]+1,-1);
    } 
    scanf("%d",&m);
    char c;
    for(int i=1;i<m+n;i++)
    {
        getchar();
        scanf("%c",&c);
        scanf("%d",&v);
        if(c=='A')
        {
            scanf("%d",&u);
            p=in[max(v,u)];
            add(p,-1);
            p=leave[max(v,u)]+1;
            add(p,1);
        }
        else
        {
            p=in[v];
            ans=query(p);
            printf("%d\n",ans);
        }
    }
    system("pause");
    return 0;
}
```

---

## 作者：ddwqwq (赞：0)

提供一个新思路，不过懒得写代码了。首先把所有询问和改变以及它们的时间记录下来，之后dfs加动态开点线段树（可持久化权值线段树），记录每个点的祖先结点某个时间建成公路的个数。这样一来，每个结点的祖先中的土路的个数即为深度减T.query(0,time)，time代表当前时间。之后再加上标准的LCA就可以查询了。

---

