# Kingdom

## 题目描述

平面有n个城市，初始时城市之间没有任何双向道路连接。你的任务是依次执行以下任务：

road A B:在城市A和城市B之间连接一条双向道路，保证这条道路不和其他道路在非端点处相交。

line C：询问一条y=C的水平线和多少个州相交，以及这些州一共包含几个城市。在任意时刻，每一组连接的城市形成一个州。在本指令中，C的小数部分保证为0.5.

例如，在图中，y=4.5穿过两个州，共八个城市；y=6.5穿过一个州，共5个城市。

# 题解

## 作者：xzlhxc_ed (赞：5)


**[博客中食用更佳](https://www.luogu.org/blog/xzlhxc/solution-uva1455)**    
**upd:博客地址变更，其余内容保持不变。**

------------
[题目链接（luogu）](https://www.luogu.org/problemnew/show/UVA1455)   

预备知识：本题综合了并查集和树状数组（或线段树~~和分块~~）的算法，需要学习的可以参考[【模板】并查集（P3367）](https://www.luogu.org/problemnew/show/P3367)以及[【模板】树状数组2（P3368）](https://www.luogu.org/problemnew/show/P3368)（内含线段树解法）的题解。    
# ①题意
本题抽象成几何问题后，我们可以发现，line的每一次查询都确保**直线与x轴平行**，不管每一个州（点集）的x坐标为何值，只要查询的y坐标在这个州的**最高点与最低点之间**，那么这个州就会被算上，所以，我们**只需要考虑每个点的y坐标**，从而可以把每一个操作看做（投影为）一条数轴（y轴）上的操作，本题就变成区间问题了，即可以用线段树等数据结构高效求解。
# ②数据处理加工
由于我们要维护点与各个不相交集合的关系，自然能想到要用并查集来维护点之间的关系，代码如下：
```cpp
struct DSU //Disjoint Set Union 并查集
{
	int n;
	int root[100001];
	void init(int x)//初始化
	{
		n=x;
		for(int i=0;i<n;i++)
               //本题中点的序号是从0开始的
		 root[i]=i;
		return;
	}
	int Find(int x)
	{
		return root[x]==x?x:root[x]=Find(root[x]);
                //路径压缩
	}
	void Merge(int x,int y)
	{
		int k1=found(x),k2=found(y);
		if(x==y)return;
		root[k2]=k1;
                //并没有按秩合并，主要是因为懒
		return;
	}
}city;
```
我们可以将整个坐标系看做一个网格图，每一个整数y坐标表示区间$[y-1,y)$这一段。  
如图，y表示的就是红色部分的区间信息。
![](https://cdn.luogu.com.cn/upload/pic/56687.png)
然后我们定义：区间$(L,R]$表示y坐标集$L+1,L+2 ...R$，那么我们便可以把每个点的**祖先节点所在州（点集）** 的最高点和最低点的y值用数组
```int pos[MAXN][2]```存起来，就是这个州（点集）所表示的区间($pos[i][1],pos[i][0]$]。  

~~（在我的代码中我用了数组下标为0的数组表示最大值，读者可自行变通 ）~~ 

特别地，当一个点初始化的时候，没有必要开一个数组存，只要
```cpp
pos[i][0]=pos[i][1]=y;
```
就可以了。  

由于我们还要求每个州（点集）的大小，所以我们开一个```int siz[MAXN]```来储存以$i$为祖先的州（点集）大小。  

关于查询，根据定义，设输入的小数为$x$，我们只要查询$(x+0.5)$的y值便可。
# ③区间修改，单点求值
由于题意的操作可以看做是区间修改，单点求值，线段树当然可以，但这里我们用树状数组或许会更快。    

先考虑求（点集）的个数。我们用一个树状差分数组```int cf[MAXN]```来储存每个点所代表的段经过的点集的个数，每一次连接可以等价为一段区间上的操作。   

当2个点（代表的祖先节点设为$i_1,i_2$）连接时，我们可以看做是2个点集求并，所以我们可以分以下3种情况：  
#### (1)$i_1=i_2$
2个点在同一个点集内，不管怎么连，都不会连到这个点集外面去，所以点集外就不必考虑了，而点集内肯定已经算过一遍了，整个点集的点的个数也没有改变，所以不用管，直接```continue```。
### (2)($pos[i_1][1],pos[i_1][0]$]$\bigcap$($pos[i_2][1],pos[i_2][0]$]$= \emptyset $
2个点集的y坐标集有交集，如图：
![](https://cdn.luogu.com.cn/upload/pic/56697.png)
容易发现连接之后（加上黄色虚线之后）对上下2部分不会产生影响，所以这个情况直接把2个点集合并，并将中间部分代表的区间维护的个数$+1$即可。   

**以及维护siz值：
```siz[k1]=siz[k2]=siz[k1]+siz[k2];```**
### (3)($pos[i_1][1],pos[i_1][0]$]$\bigcap$($pos[i_2][1],pos[i_2][0]$]$\ne \emptyset $
2个点集的y坐标集有交集，如图：
![](https://cdn.luogu.com.cn/upload/pic/56691.png)
（图中蓝点和绿点分别为2个点集的最高点和最低点，黄色段为它们的交集）   
与（1）类似，无论怎么连，它们总是影响不到总区间外，所以我们只需要将黄色

段的区间维护的个数$-1$即可。

```//别忘了 siz[k1]=siz[k2]=siz[k1]+siz[k2];```
------------
# ④优化代码长度
### “等等，如果按照上面说的做，分类讨论会把我累死的...”
仔细观察一下（2）与（3）的情况，可以发现2种情况合并后的点集的最高点和最低点就是原来2个点集的最高点和最低点。所以我们直接将2个点集代表的区间维护的个数都$-1$，再把新点集代表的区间维护的个数都$+1$即可。可以理解成重新构造一个点集。

至于州的个数，再开一个树状差分数组，像个数一样维护就可以了。
```cpp
int x=readin(),y=readin(),k1=city.found(x),k2=city.found(y);
if(k1==k2)continue;
if(pos[k1][0]!=pos[k1][1])
//如果只是一个单点就不用取消了，这里判断的是非单点的情况
{
	add(pos[k1][0]+1,1,0);//维护（点集的）个数
	add(pos[k1][1]+1,-1,0);
	add(pos[k1][0]+1,siz[k1],1);//维护大小（点的个数）
	add(pos[k1][1]+1,-siz[k1],1);
}
if(pos[k2][0]!=pos[k2][1])//同上
{
	add(pos[k2][0]+1,1,0);
	add(pos[k2][1]+1,-1,0);
	add(pos[k2][0]+1,siz[k2],1);
	add(pos[k2][1]+1,-siz[k2],1);
}
siz[k1]=siz[k2]=siz[k1]+siz[k2];//点集（大小）合并
add(max(pos[k1][0],pos[k2][0])+1,-1,0);//维护新点集个数、大小
add(min(pos[k1][1],pos[k2][1])+1,1,0);
add(max(pos[k1][0],pos[k2][0])+1,-siz[k1],1);
add(min(pos[k1][1],pos[k2][1])+1,siz[k1],1);
city.merge(k1,k2);//点集合并
pos[k1][0]=pos[k2][0]=max(pos[k1][0],pos[k2][0]);//更新最高（低）点
pos[k1][1]=pos[k2][1]=min(pos[k1][1],pos[k2][1]);
```
# ⑤查询
查询单点就可以了，②中已有提过。
# ⑥AC!
 _觉得好就点个赞吧！_ 

---

## 作者：autoint (赞：1)

# 分析
直线都是$y=\overline{a.5}$这种形式，而只查询州和城市的个数，所以很容易想到对$y$轴做投影，然后转化为区间修改（加减）和单点查询，可以用线段树维护。至于每个州只会合并不会分裂，大小肯定是只增不减的，所以用并查集维护很方便。
### 算法流程
线段树维护区间的州和城市的个数，以及它们的标记。
并查集要维护它的大小，纵坐标范围。
1. road A B：如果A、B本身同属一个州就不管，因为肯定有覆盖A、B纵坐标的路连接它们两个。否则先撤销A、B所属州对线段树的贡献，然后合并两个州，最后把并集的贡献加到线段树上。
2. line C:我规定线段树上$[i,i]$节点管辖$y$轴上$[i,i-1]$区间，也就是$y=\overline{(i-1).5}$这条直线。那么此操作相当于查询$[C+0.5,C+0.5]$这个节点。

### 时间复杂度
建树复杂度$O(n\log n)$。单次操作无论是road A B还是line C都是$O(\log n)$的，而有$m$次操作，所以总时间复杂度为$O(n\log n+m \log n)$。
# 代码
```cpp
#include<iostream>
#include<cstdio>
#define reg register
#pragma GCC optimize(3) 
template<typename T>T read(T&x)
{
    T data=0;
    int w=1;
    char ch=getchar();
    while(ch!='-'&&!isdigit(ch))
        ch=getchar();
    if(ch=='-')
        w=-1,ch=getchar();
    while(isdigit(ch))
        data=data*10+ch-'0',ch=getchar();
    return x=data*w;
}
using namespace std;
const int MAXN=1e5+1,MAXY=1e6+1;

struct SegTree // leaf node i controls y=i->(i-1)
{
    int sums,sumc;
    int adds,addc;
}ST[MAXY<<2];
#define root ST[o]
#define lson ST[o<<1]
#define rson ST[o<<1|1]
inline void pushup(int o)
{
    root.sums=lson.sums+rson.sums;
    root.sumc=lson.sumc+rson.sumc;
}

void build(int o,int l,int r)
{
    if(l==r)
    {
        root.sums=root.sumc=0;
        root.adds=root.addc=0;
        return;
    }
    int mid=(l+r)>>1;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    pushup(o);
    root.adds=root.addc=0;
}

inline void pushdown(int o,int l,int r)
{
    int mid=(l+r)>>1;
    if(root.adds)
    {
        lson.sums+=root.adds*(mid-l+1),
        lson.adds+=root.adds;
        rson.sums+=root.adds*(r-mid),
        rson.adds+=root.adds;
        root.adds=0;
    }
    if(root.addc)
    {
        lson.sumc+=root.addc*(mid-l+1),
        lson.addc+=root.addc;
        rson.sumc+=root.addc*(r-mid),
        rson.addc+=root.addc;
        root.addc=0;
    }
}

void addrg(int o,int l,int r,int ql,int qr,int state,int city)
{
    if(ql<=l&&r<=qr)
    {
        root.sums+=state*(r-l+1),
        root.adds+=state;
        root.sumc+=city*(r-l+1),
        root.addc+=city;
        return;
    }
    pushdown(o,l,r);
    int mid=(l+r)>>1;
    if(ql<=mid)
        addrg(o<<1,l,mid,ql,qr,state,city);
    if(qr>=mid+1)
        addrg(o<<1|1,mid+1,r,ql,qr,state,city);
    pushup(o);
}

SegTree querypt(int o,int l,int r,int q)
{
    if(l==r)
        return root;
    pushdown(o,l,r);
    int mid=(l+r)>>1;
    if(q<=mid)
        return querypt(o<<1,l,mid,q);
    else if(q>=mid+1)
        return querypt(o<<1|1,mid+1,r,q);
}

struct Point
{
    int x,y;
}P[MAXN];
typedef Point Range;

int fa[MAXN],sz[MAXN];
Range rg[MAXN]; // y=x->y(x<y)

int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

inline void unite(int x,int y)
{
    int fx=find(x),fy=find(y);
    if(fx==fy) return;
    if(rg[fx].x+1<=rg[fx].y)
    {
        addrg(1,1,1e6,rg[fx].x+1,rg[fx].y,-1,-sz[fx]);
    }	
    if(rg[fy].x+1<=rg[fy].y)
    {
        addrg(1,1,1e6,rg[fy].x+1,rg[fy].y,-1,-sz[fy]);
    }
    sz[fy]+=sz[fx],sz[fx]=0;
    fa[fx]=fy;
    rg[fy].x=min(rg[fy].x,rg[fx].x),rg[fy].y=max(rg[fy].y,rg[fx].y);
    if(rg[fy].x+1<=rg[fy].y)
    {
        addrg(1,1,1e6,rg[fy].x+1,rg[fy].y,1,sz[fy]);
    }// ->segtree bomb
}

int main()
{
    int T;
    read(T);
    while(T--)
    {
        build(1,1,1e6);
        int n;
        read(n);
        for(reg int i=0;i<n;++i)
        {
            read(P[i].x);read(P[i].y);
            fa[i]=i;
            sz[i]=1;
            rg[i].x=rg[i].y=P[i].y;
        }
        int m;
        read(m);
        for(reg int i=1;i<=m;++i)
        {
            char opt[10];
            scanf("%s",opt);
            if(opt[0]=='r')
            {
                int A,B;
                read(A);read(B);
                unite(A,B);
            }
            else if(opt[0]=='l')
            {
                double C;
                scanf("%lf",&C);
                C+=0.5;
                SegTree t=querypt(1,1,1e6,C);
                printf("%d %d\n",t.sums,t.sumc);
            }
        }
    }
}
```
# Hint
线段树大小还可以继续优化。

---

## 作者：syLph (赞：0)

一直很想做却一直没有下定决心去做的一道题。

发现 $x$ 坐标没有什么用，直接存每个点的 $y$ 坐标即可。

然后就是一个并查集，合并同时维护一下区间的左端点和右端点以及区间内的点的个数，然后如果两个点已经在一个联通块中就直接跳过。

因为值域只有 $10^6$，直接在值域上建立一棵线段树维护一下区间内点的个数和以及覆盖次数和即可。询问时直接单点询问即可。

时间复杂度 $O(n\log{n})$。


写起来也不怎么烦，50 分钟就切了。


Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000010;
char t[8];
int fa[maxn],l[maxn],r[maxn],lazy[2][maxn<<2],dat[2][maxn<<2];
int n,QQ,k[maxn],maxp,siz[maxn];
int find(int x){
	if(x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void pushdown(int p,int l,int r,int o){
	if(lazy[o][p]){
		int mid = (l + r) >> 1;
		dat[o][p*2] += (mid - l + 1) * lazy[o][p];
		dat[o][p*2+1] += (r - mid) * lazy[o][p];
		lazy[o][p*2] += lazy[o][p];
		lazy[o][p*2+1] += lazy[o][p];
		lazy[o][p] = 0; 
	}
}
void update(int p,int l,int r,int L,int R,int k,int o){
	if(L > R) return;
	if(l > R || r < L) return;
	if(L <= l && r <= R){
		dat[o][p] += (r - l + 1) * k;
		lazy[o][p] += k;
		return;
	}
	pushdown(p,l,r,o); int mid = (l + r) >> 1;
	update(p*2,l,mid,L,R,k,o),update(p*2+1,mid+1,r,L,R,k,o);
	dat[o][p] = dat[o][p*2] + dat[o][p*2+1]; 
}
int getpos(int p,int l,int r,int pos,int o){
	if(l > pos || r < pos) return 0;
	if(l == r && l == pos) return dat[o][p];
	pushdown(p,l,r,o); int mid = (l + r) >> 1;
	return getpos(p*2,l,mid,pos,o) + getpos(p*2+1,mid+1,r,pos,o);
}
int main(){
	//freopen("a.txt","r",stdin);
	int T; scanf("%d",&T);
	while(T--){
		memset(dat,0,sizeof dat);
		memset(lazy,0,sizeof lazy);
		maxp = 0; 
		scanf("%d",&n);
		for(int i = 1 ; i <= n ; i ++){
			int x; 
			scanf("%d%d",&x,&r[i]),l[i] = r[i],maxp = max(maxp,l[i]);	
		}
		//for(int i = 1 ; i <= n ; i ++) update(1,1,maxp,r[i],r[i],1,1);
		for(int i = 1 ; i <= n + 1 ; i ++) fa[i] = i,siz[i] = 1;
		scanf("%d",&QQ);
		while(QQ--){
			scanf("%s",t);
			if(t[0] == 'r'){
				int x,y; scanf("%d%d",&x,&y); x += 1,y += 1;
				int fx = find(x),fy = find(y);
				if(fx == fy) continue;
				update(1,1,maxp,l[fx]+1,r[fx],-siz[fx],0);
				update(1,1,maxp,l[fy]+1,r[fy],-siz[fy],0);
				update(1,1,maxp,l[fx]+1,r[fx],-1,1);
				update(1,1,maxp,l[fy]+1,r[fy],-1,1);
				//cout << l[fx] + 1 << ' ' << r[fx] << endl;
				l[fx] = min(l[fx],l[fy]);
				r[fx] = max(r[fx],r[fy]);
				update(1,1,maxp,l[fx]+1,r[fx],siz[fx] + siz[fy],0);
				update(1,1,maxp,l[fx]+1,r[fx],1,1);
				siz[fx] += siz[fy];
				fa[fy] = fx;
			}else{
				double opt; cin >> opt;  int u = opt + 0.51;
				printf("%d %d\n",getpos(1,1,maxp,u,1),getpos(1,1,maxp,u,0));
			}
		}
	}
	return 0;
}
```

---

## 作者：黑影洞人 (赞：0)

第一篇 UVa 的题解，这也是我退役前最后一篇题解了。

观察这道题，发现连线和 $x$ 值无关，于是我们只用记录下 $y$ 值。

然后这题就转化为了平面问题，一个州可以用四个值表示。

- 州的编号（$x$）
- 州的城市数量（$siz[x]$）
- 州的左右端点（$lx[x],rx[x]$）

然后我们用并查集维护每个州，连接操作就看做合并，删除每个州原来的数据，然后合并之后加上新的州的数据，用两个树状数组差分维护即可。

上代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 114514
#define M 1145141
using namespace std;
int T;
int n,m;
int lx[N],rx[N],f[N],siz[N];
struct bit2{
    int c[M];
    void clear(){memset(c,0,sizeof(c));}
    int lowbit(int x){return x&-x;}
    void add(int l,int r,int v){
    	if(l>r)return;
        r++;
        for(;l<M;l+=lowbit(l))c[l]+=v;
        for(;r<M;r+=lowbit(r))c[r]-=v;
    }
    int query(int x){
        int res=0;
        for(;x;x-=lowbit(x))res+=c[x];
        return res;
    }
}a,b;
int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
void merge(int x,int y){
	int u=find(x),v=find(y);
	if(u==v)return;
	if(siz[u]>siz[v])swap(u,v),swap(x,y);
	a.add(lx[u]+1,rx[u],-1);
	b.add(lx[u]+1,rx[u],-siz[u]);
	a.add(lx[v]+1,rx[v],-1);
	b.add(lx[v]+1,rx[v],-siz[v]);
	f[u]=v;
	lx[v]=min(lx[v],lx[u]);
	rx[v]=max(rx[v],rx[u]);
	siz[v]+=siz[u];siz[u]=0;
	a.add(lx[v]+1,rx[v],1);
	b.add(lx[v]+1,rx[v],siz[v]);
}
signed main(){
	scanf("%d",&T);
	while(T--){
		a.clear();
		b.clear();
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			f[i]=i;
			siz[i]=1;
			lx[i]=rx[i]=b; 
		}
		scanf("%d",&m);
		while(m--){
			char s[10];
			int x,y;
			double c;
			scanf("%s",s);
			if(s[0]=='r'){
				scanf("%d%d",&x,&y);
				merge(x+1,y+1);
			}else if(s[0]=='l'){
				scanf("%lf",&c);
				y=1*(c+0.5);
				printf("%d %d\n",a.query(y),b.query(y));
			}
		}
	}
	return 0;
}
```

---

## 作者：_zexal_ (赞：0)

考虑到最后的查询和横轴无关，所以我们只需要记录有多少个城市线路经过那一条线即可。

考虑情况一，将任意两个城市合并，我们不妨直接用并查集表示这集合，如果 $u$ 和 $v$ 本身就在一个集合，那么我们可以不管。

接下来，考虑情况二，因为我们并查集维护了一个城市的信息，那么我们将一个城市群看作一个集合，由于这个集合是可以丢在平面直角坐标系且和纵轴有关系，所以我们还可以把集合看作一个个区间，问题转换为如何维护一段区间信息。考虑同一个城市群的影响范围，显然就是城市群的最上方到最下方，这一部分直接顺带在并查集合并的时候记录即可。

最后，我们考虑怎么计算这个区间，能维护一个区间的数据结构，这不就是线段树或者树状数组就可以维护了的吗？我们直接用树状数组维护纵轴上面的城市个数就可以了。

---

