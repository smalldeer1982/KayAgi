# [ABC133F] Colorful Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc133/tasks/abc133_f

$ 1 $ から $ N $ までの番号がつけられた $ N $ 個の頂点を持つ木があります。 この木の $ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結び、その色は $ c_i $、長さは $ d_i $ です。 ここで各辺の色は $ 1 $ 以上 $ N-1 $ 以下の整数で表されており、同じ整数は同じ色に、異なる整数は異なる色に対応します。

以下の $ Q $ 個の問いに答えてください。

- 問 $ j $ ($ 1\ \leq\ j\ \leq\ Q $): 色 $ x_j $ のすべての辺の長さが $ y_j $ に変更されたと仮定して、二頂点 $ u_j,\ v_j $ 間の距離を求めよ。(辺の長さの変更はこれ以降の問いには影響しない。)

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ N $
- $ 1\ \leq\ c_i\ \leq\ N-1 $
- $ 1\ \leq\ d_i\ \leq\ 10^4 $
- $ 1\ \leq\ x_j\ \leq\ N-1 $
- $ 1\ \leq\ y_j\ \leq\ 10^4 $
- $ 1\ \leq\ u_j\ <\ v_j\ \leq\ N $
- 与えられるグラフは木である。
- 入力中のすべての値は整数である。

### Sample Explanation 1

この入力中のグラフは次のようなものです。 !\[図\](https://img.atcoder.jp/ghi/ca75688b08f73eb63a30ce6daa54a781.png) ここで、色 $ 1 $ の辺は赤い実線で、色 $ 2 $ の辺は緑の太線で、色 $ 4 $ の辺は青い破線で示されています。 - 問 $ 1 $: 色 $ 1 $ のすべての辺の長さが $ 100 $ に変更されたと仮定すると、頂点 $ 1,\ 4 $ 間の距離は $ 100\ +\ 30\ =\ 130 $ です。 - 問 $ 2 $: 色 $ 1 $ のすべての辺の長さが $ 100 $ に変更されたと仮定すると、頂点 $ 1,\ 5 $ 間の距離は $ 100\ +\ 100\ =\ 200 $ です。 - 問 $ 3 $: 色 $ 3 $ のすべての辺の長さが $ 1000 $ に変更されたと仮定すると (そのような辺は存在しません)、頂点 $ 3,\ 4 $ 間の距離は $ 20\ +\ 10\ +\ 30\ =\ 60 $ です。この問いでは色 $ 1 $ の辺の長さが元に戻っていることに注意してください。

## 样例 #1

### 输入

```
5 3
1 2 1 10
1 3 2 20
2 4 4 30
5 2 1 40
1 100 1 4
1 100 1 5
3 1000 3 4```

### 输出

```
130
200
60```

# 题解

## 作者：b6e0_ (赞：11)

[题](https://www.luogu.com.cn/problem/AT4809)

只想到了主席树。其实就是可持久化数组。

建一棵主席树，第 $i$ 个节点的主席树表示的是它到树根的路径中，相同颜色的边条数和长度和的线段树。查询转换成 $u_i$ 和 $v_i$ 到树根减去两倍的 $u$ 和 $v$ 的最近公共祖先。权值和的话，减去原有的权值和，加上 $y_i$ 乘路径条数。没有思维难度。时间复杂度 $\mathcal O(n\log n)$。代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct edg//边
{
	int to,col,len;
};
struct zxs//主席树
{
	int lc,rc,tot,sum;
}tree[4000010];
vector<edg>g[100010];
int n,cnt,root[100010],dep[100010],fa[100010][20],dis[100010];
inline int read()//快读
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return x;
}
inline void write(int x)//快写
{
	int sta[10],tp=0;
	while(x)
	{
		sta[++tp]=x%10;
		x/=10;
	}
	while(tp)
		putchar(sta[tp--]+'0');
	putchar('\n');
}
int build(int l,int r)//建树
{
	int p=++cnt;
	tree[p].sum=tree[p].tot=0;
	if(l!=r)
	{
		int mid=(l+r)>>1;
		tree[p].lc=build(l,mid);
		tree[p].rc=build(mid+1,r);
	}
	return p;
}
int change(int q,int l,int r,int x,int y)//修改
{
	int p=++cnt;
	tree[p]=tree[q];
	tree[p].tot++;
	tree[p].sum+=y;
	if(l!=r)
	{
		int mid=(l+r)>>1;
		if(x>mid)
			tree[p].rc=change(tree[q].rc,mid+1,r,x,y);
		else
			tree[p].lc=change(tree[q].lc,l,mid,x,y);
	}
	return p;
}
int ask(int p,int l,int r,int x,int y)//查询
{
	if(l==r)
		return tree[p].tot*y-tree[p].sum;
	int mid=(l+r)>>1;
	if(x>mid)
		return ask(tree[p].rc,mid+1,r,x,y);
	return ask(tree[p].lc,l,mid,x,y);
}
void dfs(int x,int f)
{
	dep[x]=dep[f]+1;
	fa[x][0]=f;
	for(int i=1;i<19;i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=0;i<g[x].size();i++)
		if(g[x][i].to!=f)
		{
			dis[g[x][i].to]=dis[x]+g[x][i].len;
			root[g[x][i].to]=change(root[x],1,n,g[x][i].col,g[x][i].len);
			dfs(g[x][i].to,x);
		}
}
inline int LCA(int u,int v)//最近公共祖先
{
	if(dep[u]<dep[v])
		swap(u,v);
	for(int i=18;~i;i--)
		if(dep[fa[u][i]]>=dep[v])
			u=fa[u][i];
	if(u==v)
		return u;
	for(int i=18;~i;i--)
		if(fa[u][i]!=fa[v][i])
		{
			u=fa[u][i];
			v=fa[v][i];
		}
	return fa[u][0];
}
int main()
{
	int q,i,x,y,z,Z;
	n=read();
	q=read();
	for(i=1;i<n;i++)
	{
		x=read();
		y=read();
		z=read();
		Z=read();
		g[x].push_back((edg){y,z,Z});
		g[y].push_back((edg){x,z,Z});
	}
	root[1]=build(1,n);
	dfs(1,1);
	while(q--)
	{
		x=read();
		y=read();
		z=read();
		Z=read();
		int l=LCA(z,Z);
		write(dis[z]+dis[Z]-2*dis[l]+ask(root[z],1,n,x,y)+ask(root[Z],1,n,x,y)-2*ask(root[l],1,n,x,y));
	}
	return 0;
}
```

---

## 作者：Red_Lantern (赞：8)

前置知识：线段树、树链剖分和在线转离线思想。

我一个很强的同学评价这是一道没什么思维难度的套路题，可是对我来说还是很难的（而且码量很大），参考了大佬 tzc_wk 的做法后就恍然大悟了。下面的话有点多，请谅解。

首先看到询问 $u,v$ 的距离，想到了可以先树剖完了再线段树维护，对于第 $i$ 次询问：

先暴力弄个线段树 A 号用来维护边权，如果边 $e$ 的颜色为 $x_i$ ，则用线段树把 $e$ 的边权单点修改为 $0$ ，否则就是原来给的边权，再弄个线段树 B 号维护 $e$ 的颜色是否为 $x_i$ ，如果是那就单点修改为 1 。

关于颜色 $x_i$ 的线段树建好后，第 $i$ 次询问的答案可以 区间查询 $u,v$ 路径在线段树 A 上的和 $+$ 线段树 B 的和 $×$ $y_i$ 。

这个直接的做法复杂度非常的糟糕（因为很多边为了询问的颜色不同而反反复复地修改），但是我们可以发现有可以优化的地方：

如果先对于每条边和每个查询关于颜色分组，也就是进行离线处理（可以丢 vector 里），那么同一组询问中的同一组边会变得很好处理，做法如下：

先对所有询问离散化后树剖，不考虑颜色地建出原始的线段树 A 和 B ，然后枚举颜色 $i:1...n-1$ ，总体分成以下三个小步骤：

1. 用 vector 枚举颜色为 $i$ 的边，对于这些边都在线段树 A 修改成 0 ，在线段树 B 上修改成 1 。 $\mathcal{O}(\log_n)$ 。
2. 用 vector 枚举颜色为 $i$ 的询问，对于这些询问用树剖求出 LCA 后再用线段树 A 和 B 算出答案并记录下来。 $\mathcal{O}((\log_n)^2)$ 。
3. 把线段树 A 和 B 复原成原始状态，相当于做步骤 1 的逆操作。 $\mathcal{O}(\log_n)$ 。

最后再把记录好的询问答案依次输出就好了。

因为每条边只有一种颜色，所以不会被反反复复地修改，所以总时间复杂度为 $\mathcal{O}(n(\log_n)^2)$ ，可以通过这题。

细节就看代码吧，应该不难理解。
```cpp
#include<bits/stdc++.h>
#define reg register
#define writeln(a) write(a),putchar('\n')
#define foor(x,l,r) for (reg int x=l; x<=r; x++)
#define forr(x,l,r) for (reg int x=l; x<r; x++) 
#define N 100006
#define l(x) (t[x].l)
#define r(x) (t[x].r)
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define mid (l(x)+r(x)>>1)
using namespace std;
void read(reg int &x){
	x=0; reg int f=1; reg char c=getchar();
	while (!isdigit(c)){if (c=='-') f=-1; c=getchar();}
	while (isdigit(c)) x=x*10+c-48,c=getchar(); x*=f;
}
void write(reg int x){
	if (x<0) {putchar('-'); x=-x;}
	if (x>9) write(x/10); putchar(x%10+48);
}
int n,m,r,p,o,x,y,z,tot,ev[N],son[N],fa[N],sz[N],a[N],d[N],top[N],dfn[N],id[N],ans[N];
struct edge{ int u,v,c,w,id; }e[N<<1];
struct ques{ int x,y,u,v; }q[N<<1];
struct node{ int l,r,val1,val2; }t[N<<2];
vector<edge>g[N]; // 我用的是邻接表存边，也可以链式前向星
vector<int>es[N]; // 边的离散化数组
vector<int>qs[N]; // 询问的离散化数组
// 对于边进行树剖（其实和点差不多）
void dfs1(int u,int v){
	d[v]=d[u]+1,fa[v]=u,sz[v]=1;
	forr(i,0,g[v].size()){
		edge E=g[v][i]; int vv=E.v;
		if (vv==u) continue;
		ev[E.id]=vv;
		a[vv]=E.w;
		dfs1(v,vv);
		sz[v]+=sz[vv];
		if (sz[vv]>sz[son[v]]) son[v]=vv;
	}
}
void dfs2(int u,int v){
	dfn[v]=++tot,id[tot]=v,top[v]=u;
	if (son[v]) dfs2(u,son[v]);
	forr(i,0,g[v].size()){
		int vv=g[v][i].v;
		if (vv==fa[v]||vv==son[v]) continue;
		dfs2(vv,vv);
	}
}
void pushup1(int x){ t[x].val1=t[ls(x)].val1+t[rs(x)].val1; }
void pushup2(int x){ t[x].val2=t[ls(x)].val2+t[rs(x)].val2; }
// 建树
void build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if (l==r){ t[x].val1=a[id[l]],t[x].val2=0; return; }
	build(ls(x),l,mid),build(rs(x),mid+1,r);
	pushup1(x);
}
// 单点修改线段树 A ，把第 idx 条边的边权改为 xx
void modify1(int x,int idx,int xx){
	if (l(x)==r(x)){ t[x].val1=xx; return; }
	if (idx<=mid) modify1(ls(x),idx,xx);
	else modify1(rs(x),idx,xx);
	pushup1(x);
}
// 单点修改线段树 B
void modify2(int x,int idx,int xx){
	if (l(x)==r(x)){ t[x].val2=xx; return; }
	if (idx<=mid) modify2(ls(x),idx,xx);
	else modify2(rs(x),idx,xx);
	pushup2(x);
}
// 区间查询线段树 A ，l,r 为给定的范围 
int query1(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return t[x].val1;
	int res=0;
	if (l<=mid) res+=query1(ls(x),l,r);
	if (r>mid) res+=query1(rs(x),l,r);
	return res;
}
// 区间查询线段树 B  
int query2(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return t[x].val2;
	int res=0;
	if (l<=mid) res+=query2(ls(x),l,r);
	if (r>mid) res+=query2(rs(x),l,r);
	return res;
}
// 链上查询 u,v 的答案 = 线段树 A 的答案 + k * 线段树 B 的答案 
int query(int x,int y,int k){
	int ans=0;
	while (top[x]!=top[y]){
		if (d[top[x]]<d[top[y]]) swap(x,y);
		ans+=query1(1,dfn[top[x]],dfn[x]);
		ans+=k*query2(1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if (d[x]>d[y]) swap(x,y);
    // 这里与点不同，当 x 和 y 为同一条边就不用计算
    // 如果不是同一条边就要从 LCA 下面那条（dfn[x]+1）边开始算，可以草稿纸上画一画
	if (x!=y){
		ans+=query1(1,dfn[x]+1,dfn[y]);
		ans+=k*query2(1,dfn[x]+1,dfn[y]);
	}
	return ans;
}
int main(){
	read(n),read(m);
	forr(i,1,n){
		read(e[i].u),read(e[i].v),read(e[i].c),read(e[i].w),e[i].id=i;
		// 邻接表存图: c 为颜色 ，w 为边权 
		g[e[i].u].push_back({e[i].u,e[i].v,e[i].c,e[i].w,i});
		g[e[i].v].push_back({e[i].v,e[i].u,e[i].c,e[i].w,i});
		// 把同一颜色的边丢到一个 vector 里离线处理 
		es[e[i].c].push_back(i);
	}
	foor(i,1,m){
		read(q[i].x),read(q[i].y),read(q[i].u),read(q[i].v);
		// 把每个关于同一颜色的询问也离线处理 
		qs[q[i].x].push_back(i);
	}
	dfs1(1,1),dfs2(1,1),build(1,1,n);
	forr(i,1,n){ // 枚举第 i 种颜色 
		forr(j,0,es[i].size()){ // 步骤 1
			int k=ev[es[i][j]];
			modify1(1,dfn[k],0);
			modify2(1,dfn[k],1);
		}
		forr(j,0,qs[i].size()){ // 步骤 2
			int k=qs[i][j];
			// ans[i] 记录第 i 次询问的答案 
			ans[k]=query(q[k].u,q[k].v,q[k].y);
		}
		forr(j,0,es[i].size()){ // 步骤 3
			int k=ev[es[i][j]];
			modify1(1,dfn[k],e[es[i][j]].w);
			modify2(1,dfn[k],0);
		}
	}
	foor(i,1,m) writeln(ans[i]);
	return 0;
}
```

---

## 作者：Minecraft万岁 (赞：5)

考虑正常的 $u$ 和 $v$ 之间的距离怎么去求：我们可以维护每个值到根的距离 $dist_i$ ，然后通过计算 $dist_u+dist_v-2 \times dist_{lca}$ 得到，这里就不过多赘述。

考虑本题，我们发现只要能够求出改变后的 $dist_i$ 的值即可，不妨利用主席树维护每个点 $i$ 到根节点 $1$ 的每种颜色的出现次数 $cnt$ 以及权值和 $sum$ ，那么此时真正的 $dist'_i=dist_i-sum+cnt \times y$ 。

而主席树的每个点的权值可以继承其父亲的权值。时空复杂度均为 $O(N \log N)$ 。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n,q,x,y,z,w;
struct node{
	int nxt;int to;int dist;int col;
}e[N*2];
int head[N],tot;
struct Chair{
	int ls;int rs;int sum;int cnt;
}Tree[N*32];
int root[N],Tcnt;

int fa[N],dep[N],sz[N],hson[N],top[N];
int val[N],col[N],dist[N];
/*这里使用了树剖求lca*/

inline void read(int &x) 
{
	int f=1;char c;
	for(x=0,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48); x*=f;
} 
inline int mn(int _x,int _y){return _x<_y?_x:_y;}
inline int mx(int _x,int _y){return _x>_y?_x:_y;}
inline int ab(int _x){return _x<0?-_x:_x;}
inline void add(int from,int to,int col,int dist)
{
	e[++tot].to=to;
	e[tot].dist=dist;e[tot].col=col;
	e[tot].nxt=head[from];
	head[from]=tot;
}

inline int New(int x)
{
	++Tcnt;
	Tree[Tcnt]=Tree[x];
	return Tcnt;
}
inline int update(int x,int l,int r,int pos,int v)
{
	x=New(x);Tree[x].sum+=v;Tree[x].cnt++;
	if(l==r) return x;
	int mid=l+r>>1;
	if(pos<=mid) Tree[x].ls=update(Tree[x].ls,l,mid,pos,v);
	if(pos>mid) Tree[x].rs=update(Tree[x].rs,mid+1,r,pos,v);
	return x;
}
inline pair<int,int> query(int x,int l,int r,int pos)
{
	if(l==r) return make_pair(Tree[x].sum,Tree[x].cnt);
	int mid=l+r>>1;
	if(pos<=mid) return query(Tree[x].ls,l,mid,pos);
	if(pos>mid) return query(Tree[x].rs,mid+1,r,pos);
}
/*主席树的修改与查询*/
inline void dfs1(int x)
{
	sz[x]=1;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa[x]) continue;
		fa[v]=x;dep[v]=dep[x]+1;
		val[v]=e[i].dist;col[v]=e[i].col;
		dist[v]=dist[x]+e[i].dist;
		dfs1(v);
		sz[x]+=sz[v];
		if(sz[v]>sz[hson[x]]) hson[x]=v;
	}
	return ;
}
inline void dfs2(int x,int tp)
{
	top[x]=tp;
	if(x!=1) root[x]=update(root[fa[x]],1,n,col[x],val[x]);
    /*如果不是根节点1就要继承父亲并且加入自己的值*/
	if(hson[x]) dfs2(hson[x],tp);
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa[x]||v==hson[x]) continue;
		dfs2(v,v);
	}	
}
inline int lca(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]>dep[top[v]]) u=fa[top[u]];
		else v=fa[top[v]];
	}
	if(dep[u]<dep[v]) return u;
	else return v;
}


inline int getd(int x,int z,int w)
{
	pair<int,int> tmp=query(root[x],1,n,z);
	return dist[x]-tmp.first+w*tmp.second;//计算改变后的权值
}
int main()
{
	read(n);read(q);
	for(int i=1;i<n;i++)
	{
		read(x);read(y);read(z);read(w);
		add(x,y,z,w);add(y,x,z,w);
	}
	dep[1]=1;dfs1(1);dfs2(1,1);
	while(q--)
	{
		read(z);read(w);read(x);read(y);
		/这里注意读入的顺序 x,y才是查询的节点*/
		int lc=lca(x,y);
		printf("%d\n",getd(x,z,w)+getd(y,z,w)-2*getd(lc,z,w));
	}
	return 0;	
}  

```


---

## 作者：EnofTaiPeople (赞：4)

发现只需要记录所有颜色边权和，单个颜色边权和，单个颜色边的个数，使用树上莫队可以做到 $O(n\sqrt q)$，使用树剖可以做到 $O(n\log_2n+q\log_2^2n)$，使用 $\text{WBTT}$ 或可持久化线段树可以做到 $O((n+q)\log_2n)$。

但如果离线下来，这道题的瓶颈就只在于求 $\text{LCA}$，故可以做到 $O(n+q)$，然而为了节省码量，我采用了 $\text{LCT}$ 求 $\text{LCA}$，这样是 $O(n+q\log_2n)$ 的，可以通过：
```cpp
#include<icecream>
using namespace std;
const int N=1e5+5;
int ed[N<<1],cl[N],w[N];
int n,q,ans[N],f[N];
vector<int>lk[N];
int q1[N],q2[N],sm[N],ct[N],als;
struct DT{int k,id;};
vector<DT>qr[N];
namespace LCA{
    int f[N],t[N][2];
#define tp(x) (t[f[x]][1]==x)
#define in(x) (t[f[x]][0]==x||tp(x))
    void rot(int x){
        int y=f[x],k=tp(x),w=t[x][!k];
        t[f[w]=t[x][!k]=y][k]=w;
        if(in(y))t[f[y]][tp(y)]=x;
        f[x]=f[y],f[y]=x;
    }int acs(int x){
        int y;
        for(y=0;x;t[x][1]=y,x=f[y=x])
            for(int z=f[x];in(x);rot(x),z=f[x])
                if(in(z))rot(tp(x)^tp(z)?x:z);
        return y;
    }int lca(int x,int y){return acs(x),acs(y);}
}using LCA::lca;basic 的 LCT 求 LCA，可以用 倍增/树剖/Tarjan/Four Russian(O(n)-O(1)!) 代替
void dfs1(int x,int pr){
    int y;
    for(int i:lk[x])
        if((y=ed[i])!=pr){
            dfs1(y,x);
            LCA::f[y]=x;
        }
}
void dfs(int x,int pr){
    int y,g;
    for(auto at:qr[x])
        if(at.k){表示需要加
            ans[at.id]+=als;
            ans[at.id]-=sm[q1[at.id]];
            ans[at.id]+=ct[q1[at.id]]*q2[at.id];
        }else{LCA 需要减两倍
            ans[at.id]-=als<<1;
            ans[at.id]+=sm[q1[at.id]]<<1;
            ans[at.id]-=ct[q1[at.id]]*q2[at.id]*2;
        }
    for(int i:lk[x])
        if((y=ed[i])!=pr){
            g=i>>1;
            sm[cl[g]]+=w[g],als+=w[g],++ct[cl[g]];
            dfs(y,x);
            sm[cl[g]]-=w[g],als-=w[g],--ct[cl[g]];
        }
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;int i,x,y,a,b;
    for(i=1;i<n;++i){
        cin>>x>>y>>cl[i]>>w[i];
        lk[ed[i+i+1]=x].push_back(i+i);
        lk[ed[i+i]=y].push_back(i+i+1);
    }dfs1(1,0);预处理父亲，用于求 LCA
    for(i=1;i<=q;++i){
        cin>>q1[i]>>q2[i]>>x>>y;
        qr[x].push_back({1,i});
        qr[y].push_back({1,i});
        x=lca(x,y);
        qr[x].push_back({0,i});
    }dfs(1,0);离线处理答案
    for(i=1;i<=q;++i)printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：251Sec (赞：3)

题解怎么全是 poly log 啊。提供一种好想的根号做法。（虽然其实 poly log 貌似也很一眼

看到颜色数我们考虑根号分治。

对于出现次数很少的颜色，我们可以在询问的时候，先求出不改变边权时候两个点的距离，然后枚举每条边判断是否出现在询问的两点的路径上，如果出现就更改答案。

对于出现次数很多的颜色，那么颜色种类数很少，考虑对每种颜色预处理答案。我们发现我们的询问本质上是要求两个点之间将指定颜色边权改为 $0$ 后的距离，以及求两个点之间指定颜色的个数。对于我们给定的颜色，这两个东西都可以通过一遍 DFS $O(n)$ 预处理，然后询问的时候只需要求个 LCA 即可。

设出现次数 $\ge B$ 的颜色为出现次数多的颜色，那么总复杂度 $O(qB \log n+\dfrac{n^2}{B})$。设 $n,q$ 同阶，那么 $B$ 取 $\sqrt{\dfrac{n}{\log n}}$ 时复杂度达到 $O(n \sqrt{n \log n})$。如果使用 $O(n \log n) - O(1)$ 的 LCA 那么块长取 $\sqrt{n}$ 时复杂度为 $O(n \sqrt n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int B = 350;
struct Edge {
    int to, next;
    int c; ll w;
} e[200005];
int head[100005], len;
void Insert(int u, int v, int c, ll w) {
    if (!len) len = 1;
    e[++len] = { v, head[u], c, w };
    head[u] = len;
}
int n, q;
int prt[100005][20], dep[100005];
void PreLCA(int u, int fa) {
    dep[u] = dep[fa] + 1; prt[u][0] = fa;
    for (int i = 1; i < 20; i++) prt[u][i] = prt[prt[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        PreLCA(v, u);
    }
}
int LCA(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    int d = dep[v] - dep[u];
    for (int i = 0; i < 20; i++) if (d >> i & 1) v = prt[v][i];
    if (u == v) return u;
    for (int i = 19; ~i; i--) {
        if (prt[u][i] != prt[v][i]) {
            u = prt[u][i]; v = prt[v][i];
        }
    }
    return prt[u][0];
}
int id[100005], iCnt;
ll dN[305][100005], dC[305][100005];
void DFS(int u, int fa, int col) {
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        dC[id[col]][v] = dC[id[col]][u]; dN[id[col]][v] = dN[id[col]][u];
        if (e[i].c == col) dC[id[col]][v]++;
        else dN[id[col]][v] += e[i].w;
        DFS(v, u, col);
    }
}
int cCnt[100005];
vector<int> eC[100005];
bool PointOnPath(int u, int v, int x) { return (LCA(u, x) == x || LCA(v, x) == x) && dep[x] >= dep[LCA(u, v)]; }
bool EdgeOnPath(int u, int v, int i) { return PointOnPath(u, v, e[i].to) && PointOnPath(u, v, e[i ^ 1].to); }
int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i < n; i++) {
        int u, v, c; ll w;
        scanf("%d%d%d%lld", &u, &v, &c, &w);
        Insert(u, v, c, w); Insert(v, u, c, w);
        cCnt[c]++; eC[c].emplace_back(len);
    }
    PreLCA(1, 0); DFS(1, 0, 0);
    for (int i = 1; i < n; i++) if (cCnt[i] >= B) id[i] = ++iCnt, DFS(1, 0, i);
    while (q--) {
        int x, u, v; ll y;
        scanf("%d%lld%d%d", &x, &y, &u, &v);
        if (id[x]) {
            ll diN = dN[id[x]][u] + dN[id[x]][v] - 2 * dN[id[x]][LCA(u, v)];
            ll diC = dC[id[x]][u] + dC[id[x]][v] - 2 * dC[id[x]][LCA(u, v)];
            printf("%lld\n", diN + diC * y);
        }
        else {
            ll ans = dN[0][u] + dN[0][v] - 2 * dN[0][LCA(u, v)];
            for (int i : eC[x]) {
                if (EdgeOnPath(u, v, i)) {
                    ans += y - e[i].w;
                }
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
```

---

## 作者：lzyqwq (赞：3)

**[更好的阅读体验](https://www.cnblogs.com/MnZnOIerLzy/articles/17484995.html)**

**[洛谷链接](https://www.luogu.com.cn/problem/AT_abc133_f "洛谷链接")**

**[AtCoder 链接](https://atcoder.jp/contests/abc133/tasks/abc133_f "AtCoder 链接")**

> - 给出 $N$ 个节点的树，每条边有颜色、边权。处理 $Q$ 个询问，第 $i$ 次询问给出 $x_i,y_i,u_i,v_i$，表示先将所有颜色为 $x_i$ 的边边权变成 $y_i$，再求出 $u_i$ 到 $v_i$ 的路径边权和。**询问之间相互独立，即不会真的修改**。
>
> - $N,Q\le 10^5$。

首先，路径上的边修改后才会影响答案。考虑树剖，先边转点。使用动态开点技巧在树剖后的序列上对每种颜色维护线段树，记录当前区间内有效边的个数 $tot$ 以及有效边的边权和 $sum$。同时维护前缀和。

跳链时，先用前缀和查询原边权和，再在线段树上查询该区间的信息，记查询到的和为 $a$，个数为 $b$。则要**将 $a$ 那一部分的贡献换成 $b\times y_i$**，对应的答案加上 $b\times y_i-a$。特判颜色不存在的情况。

时间复杂度为 $\mathcal{O}(Q\log^2 N)$，空间复杂度为 $\mathcal{O}(N)$。

**[评测记录](https://atcoder.jp/contests/abc133/submissions/42275163 "评测记录")**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,f[N],sz[N],d[N],val[N],col[N],dfn[N],id,h[N],t[N],qzh[N],rt[N],sum[N*20],tot[N*20],cnt,ls[N*20],rs[N*20];
struct edge{
    int v,c,w;
};
vector<edge>g[N];
void insert(int&x,int l,int r,int k,int v){
    if(!x){
        ++cnt;
        x=cnt;
    }
    sum[x]+=v;
    ++tot[x];
    if(l^r){
        int mid=(l+r)>>1;
        if(k<=mid){
            insert(ls[x],l,mid,k,v);
        }else{
            insert(rs[x],mid+1,r,k,v);
        }
    }
}
pair<int,int>query(int x,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){
        return make_pair(sum[x],tot[x]);
    }
    int mid=(l+r)>>1,fi=0,se=0;
    if(ql<=mid&&ls[x]){
        auto[a,b]=query(ls[x],l,mid,ql,qr);
        fi+=a;
        se+=b;
    }
    if(qr>mid&&rs[x]){
        auto[a,b]=query(rs[x],mid+1,r,ql,qr);
        fi+=a;
        se+=b;
    }
    return make_pair(fi,se);
}
void dfs1(int u,int fa){
    sz[u]=1;
    for(auto[v,c,w]:g[u]){
        if(v^fa){
            d[v]=d[u]+1;
            f[v]=u;
            val[v]=w;
            col[v]=c;
            dfs1(v,u);
            sz[u]+=sz[v];
        }
    }
}
void dfs2(int u,int fa){
    for(auto[v,c,w]:g[u]){
        if(v^fa){
            if((sz[v]<<1)>sz[u]){
                h[u]=v;
                t[v]=t[u];
            }else{
                t[v]=v;
            }
            dfs2(v,u);
        }
    }
}
void dfs3(int u,int fa){
    ++id;
    dfn[u]=id;
    qzh[id]=qzh[id-1]+val[u];
    insert(rt[col[u]],1,n,id,val[u]);
    if(h[u]){
        dfs3(h[u],u);
    }
    for(auto[v,c,w]:g[u]){
        if((v^h[u])&&(v^fa)){
            dfs3(v,u);
        }
    }
}
void pathquery(int x,int y,int u,int v){
    int ans=0;
    while(t[u]^t[v]){
        if(d[t[u]]<d[t[v]]){
            swap(u,v);
        }
        ans+=qzh[dfn[u]]-qzh[dfn[t[u]]-1];
        if(rt[x]){
            auto[a,b]=query(rt[x],1,n,dfn[t[u]],dfn[u]);
            ans+=b*y-a;
        }
        u=f[t[u]];
    }
    if(u^v){
        if(d[u]>d[v]){
            swap(u,v);
        }
        ans+=qzh[dfn[v]]-qzh[dfn[u]];
        if(rt[x]){
            auto[a,b]=query(rt[x],1,n,dfn[u]+1,dfn[v]);
            ans+=b*y-a;
        }
    }
    printf("%d\n",ans);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,u,v,c,d;i^n;++i){
        scanf("%d%d%d%d",&u,&v,&c,&d);
        g[u].emplace_back(edge{v,c,d});
        g[v].emplace_back(edge{u,c,d});
    }
    dfs1(1,0);
    t[1]=1;
    dfs2(1,0);
    dfs3(1,0);
    for(int i=1,x,y,u,v;i<=m;++i){
        scanf("%d%d%d%d",&x,&y,&u,&v);
        pathquery(x,y,u,v);
    }
    return 0;
}
```

---

## 作者：louhao088 (赞：3)

树剖 $+$ 树状数组。

观察题意我们发现答案其实就是两点原来距离 $-$ 路径上 $x_i$ 颜色的边权和 $+$ $x_i$ 颜色路径的数量 $\times y_i$ 。

两点原来距离只需求 $Lca$ 很容易实现，$x_i,y_i$ 都是已给出的量。那么问题就转化为求路径上  $x_i$ 颜色的边权和与 $x_i$ 颜色路径的数量。我们很容易想到用对每个颜色用树剖维护。

具体的，我们先离线，把同种颜色放在一起处理。我们把边看成点，每次修改一个点的值。然后区间查询 $u \to v$ 上的信息。单点修改区间查询，很明显可以使用树状数组。由于每条边最多只会改两次，所以总时间复杂度是树剖复杂度 $O(n \log^2 n)$ 虽然是 $log^2$ 但是比一般的 $\log$ 跑的快，空间复杂度也是线性。

注意因为把边看成点，所以要把 $Lca$ 这条边不算，要特判。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define int long long
#define fi first
#define se second
#define lowbit(i) (i&(-i))
inline int read()
{
	char ch=getchar();int x=0;bool f=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
const int maxn=1e5+5;
int x,y,z,w,n,m,dis[maxn],idx=0,p[maxn],h[maxn],ans,res,f[maxn],o[maxn],c[maxn],c2[maxn];
int id[maxn],son[maxn],d[maxn],top[maxn],siz[maxn],fa[maxn];
struct node
{
	int x,y,w,z;
}b[maxn];
struct que
{
	int x,y,s,t,id;
}q[maxn];
vector<pair<int,int> >e[maxn];
vector<int>g[maxn];
bool cmp(que a,que b){return a.x<b.x;}
void dfs1(int x,int f)
{
	siz[x]=1;fa[x]=f;d[x]=d[f]+1;
	for(auto i:e[x])
	{
		if(i.fi==f)continue;dis[i.fi]=dis[x]+i.se;
		dfs1(i.fi,x);siz[x]+=siz[i.fi];p[i.fi]=i.se;
		if(siz[son[x]]<siz[i.fi])son[x]=i.fi;
	}
}
void dfs2(int x,int tf)
{
	top[x]=tf;id[x]=++idx;h[idx]=p[x];
	if(son[x])dfs2(son[x],tf);	
	for(auto i:e[x])
	{
		if(fa[x]!=i.fi&&son[x]!=i.fi)
			dfs2(i.fi,i.fi);
	}
}
void add(int x,int z)
{
	for(int i=x;i<=n;i+=lowbit(i))c[i]+=z;
}
void add2(int x,int z)
{
	for(int i=x;i<=n;i+=lowbit(i))c2[i]+=z;
}
int Q(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i))res+=c[i];
	return res;
}
int Q2(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i))res+=c2[i];
	return res;
}
int query(int rt,int l,int r)
{
	return Q(r)-Q(l-1);
}
int query2(int rt,int l,int r)
{
	return Q2(r)-Q2(l-1);
}
int Lca(int x,int y)
{
	while(top[x]!=top[y])
    {
        if(d[top[x]]<d[top[y]])swap(x,y);
        x=fa[top[x]];
    }
    if(d[x]>d[y])swap(x,y);
    return x;
}
int getdis(int x,int y)
{
	return dis[x]+dis[y]-2*dis[Lca(x,y)];
}
void treequery(int x,int y)
{
	ans=0,res=0;
	while(top[x]!=top[y])
    {
        if(d[top[x]]<d[top[y]])swap(x,y);
        ans=(ans+query(1,id[top[x]],id[x]));
        res=(res+query2(1,id[top[x]],id[x]));
        x=fa[top[x]];
    }
    if(d[x]>d[y])swap(x,y);
    ans=(ans+query(1,id[x],id[y]));
    res=res+query2(1,id[x],id[y]);
}
signed main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<n;i++)
	{
		x=read(),y=read(),z=read(),w=read();b[i].x=x,b[i].y=y,b[i].w=w;b[i].z=z;
		e[x].push_back(mp(y,w)),e[y].push_back(mp(x,w));
		g[z].push_back(i);
	}
	dfs1(1,0);dfs2(1,1);
	
	for(int i=1;i<n;i++)
	{
		if(d[b[i].x]>d[b[i].y])f[b[i].x]=i;
		else f[b[i].y]=i;
	}
	for(int i=1;i<=m;i++)
		q[i].x=read(),q[i].y=read(),q[i].s=read(),q[i].t=read(),q[i].id=i;
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		if(q[i].x!=q[i-1].x)
		{
			for(auto j:g[q[i].x])
			{
				int x=b[j].x,y=b[j].y,w=b[j].w;
				if(d[x]<d[y])swap(x,y);
				//cout<<x<<endl;
				add(id[x],w);
				add2(id[x],1);
			}
		}
		treequery(q[i].s,q[i].t);
		int lca=Lca(q[i].s,q[i].t);
		if(b[f[lca]].z==q[i].x)
		{
			ans-=b[f[lca]].w,res--;
		}
		ans=getdis(q[i].s,q[i].t)-ans+res*q[i].y;
		o[q[i].id]=ans;
		if(q[i].x!=q[i+1].x)
		{
			for(auto j:g[q[i].x])
			{
				int x=b[j].x,y=b[j].y,w=b[j].w;
				if(d[x]<d[y])swap(x,y);
				add(id[x],-w);
				add2(id[x],-1);
			}
		}	
	}
	for(int i=1;i<=m;i++)
	{
		printf("%d\n",o[i]);
	}
	return 0;
}

```






---

## 作者：xtx1092515503 (赞：3)

一般般的树剖题吧（如果它要再支持修改边权、边的颜色说不定会更难一点，可是很遗憾它没有）

首先进行树剖。我们将边权和边的颜色转到点上（树剖常规操作）。

我们考虑对于每种颜色建立一棵动态开点线段树，储存所有该颜色的边的信息。

对于每次询问，我们要找到$3$个信息：

原树中该路径的长度，设为$len$（树剖最经典的操作）

原树中这条路径上被询问颜色的边的数量，设为$num$（可以在动态开点线段树里面维护）

原树中这条路径上被询问颜色的边的长度之和，设为$sum$。

再设我们将所有该颜色的边的长度全都修改成$dis$，则此次询问答案就是：

$len+num*dis-sum$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mid ((l+r)>>1)
int n,m,val[100100],col[100100],root[100100],tsz,dis[100100];
int dfn[100100],rev[100100],fa[100100],dep[100100],son[100100],top[100100],sz[100100],head[100100],cnt,tot;
struct node{
	int to,next,val,col;
}edge[200100];
void ae(int u,int v,int c,int w){
	edge[cnt].next=head[u],edge[cnt].to=v,edge[cnt].val=w,edge[cnt].col=c,head[u]=cnt++;
	edge[cnt].next=head[v],edge[cnt].to=u,edge[cnt].val=w,edge[cnt].col=c,head[v]=cnt++;
}
void dfs1(int x,int Fa){
	fa[x]=Fa,dep[x]=dep[Fa]+1,sz[x]=1;
	for(int i=head[x],y;i!=-1;i=edge[i].next){
		if((y=edge[i].to)==fa[x])continue;
		dis[y]=dis[x]+edge[i].val,dfs1(y,x),sz[x]+=sz[y],val[y]=edge[i].val,col[y]=edge[i].col;
		if(sz[son[x]]<sz[y])son[x]=y;
	}
}
void dfs2(int x){
	if(son[x])top[son[x]]=top[x],dfn[son[x]]=++tot,rev[tot]=son[x],dfs2(son[x]);
	for(int i=head[x],y;i!=-1;i=edge[i].next){
		y=edge[i].to;
		if(y==fa[x]||y==son[x])continue;
		top[y]=y,dfn[y]=++tot,rev[tot]=y,dfs2(y);
	}
}
struct SegTree{
	int lson,rson,sum,sz;
	SegTree(){lson=rson=sum=sz=0;}
	friend SegTree operator +(const SegTree &x,const SegTree &y){
		SegTree z;
		z.sum=x.sum+y.sum;
		z.sz=x.sz+y.sz;
		return z;
	}
}seg[20001000];
void modify(int &x,int l,int r,int P,int val){
	if(!x)x=++tsz;
	seg[x].sum+=val,seg[x].sz++;
	if(l==r)return;
	if(mid>=P)modify(seg[x].lson,l,mid,P,val);
	else modify(seg[x].rson,mid+1,r,P,val);
}
SegTree query(int x,int l,int r,int L,int R){
	if(!x)return SegTree();
	if(l>R||r<L)return SegTree();
	if(L<=l&&r<=R)return seg[x];
	return query(seg[x].lson,l,mid,L,R)+query(seg[x].rson,mid+1,r,L,R);
}
int ask(int x,int y,int c,int w){
	int X=x,Y=y;
	SegTree res;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		res=res+query(root[c],1,n,dfn[top[x]],dfn[x]),x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	if(x!=y)res=res+query(root[c],1,n,dfn[x]+1,dfn[y]);
	return dis[X]+dis[Y]-2*dis[x]+w*res.sz-res.sum;
}
int main(){
	scanf("%d%d",&n,&m),memset(head,-1,sizeof(head));
	for(int i=1,a,b,c,d;i<n;i++)scanf("%d%d%d%d",&a,&b,&c,&d),ae(a,b,c,d);
	dfs1(1,0),dfn[1]=rev[1]=tot=top[1]=1,dfs2(1);
	for(int i=2;i<=n;i++)modify(root[col[i]],1,n,dfn[i],val[i]);
	for(int i=1,a,b,c,d;i<=m;i++)scanf("%d%d%d%d",&a,&b,&c,&d),printf("%d\n",ask(c,d,a,b));
	return 0;
}
```


---

## 作者：small_john (赞：2)

## 思路

本蒟蒻不会写持久化，用离线算法竟然对了！

由于每个操作是独立的，所以可以用下面的方法求出每一个答案：

- 设原本的路径长度为 $dis$，在路径中有 $k$ 个颜色为 $x$ 的边，这些边原来的长度和是 $s$，那么答案就是 $dis-s+k\times y$。由于我们提前知道了要处理哪些点，深搜扫一遍就行了。
- 直接算路径长度有点麻烦，就把答案拆成三部分：
	1. $u$ 到根节点的距离，贡献权值为 $1$；
   2. $v$ 到根节点的距离，贡献权值为 $1$；
   3. $u,v$ 的最近公共祖先到根节点的距离，贡献权值为 $-2$（最近公共祖先用树剖求）。
   
最后输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n,q,head[2*N],nxt[2*N],to[2*N],w[2*N],col[2*N],Cnt;
int f[N],son[N],dep[N],dis[N],vis[N],tp[N],ans[N];
int cnt[N],len[N];
vector<int> qx[N],qy[N],qt[N],qid[N];
void dfs1(int x)
{
	vis[x] = 1;
	for(int i = head[x];i;i = nxt[i])
	{
		int u = to[i];
		if(u==f[x]) continue;
		dep[u] = dep[x]+1,dis[u] = dis[x]+w[i],f[u] = x;
		dfs1(u);
		vis[x]+=vis[u];
		if(vis[u]>vis[son[x]]) son[x] = u;
	}
}
void dfs2(int x)
{
	for(int i = head[x];i;i = nxt[i])
	{
		int u = to[i];
		if(u==f[x]) continue;
		if(u==son[x]) tp[u] = tp[x];
		else tp[u] = u;
		dfs2(u);
	}
}
int lca(int x,int y)//树剖求lca
{
	while(tp[x]!=tp[y])
		if(dep[tp[x]]<dep[tp[y]])
			y = f[tp[y]];
		else x = f[tp[x]];
	if(dep[x]<dep[y]) return x;
	else return y;
}
void add(int a,int b,int c,int d)//增加一条边
{
	nxt[++Cnt] = head[a];
	head[a] = Cnt;
	to[Cnt] = b;
	col[Cnt] = c;
	w[Cnt] = d;
}
void add_q(int u,int x,int y,int t,int id)//增加一个问题
{
	qx[u].push_back(x);
	qy[u].push_back(y);
	qt[u].push_back(t);
	qid[u].push_back(id);
}
void dfs(int x)
{
	for(int i = 0;i<qx[x].size();i++)
		ans[qid[x][i]]+=qt[x][i]*(dis[x]+cnt[qx[x][i]]*qy[x][i]-len[qx[x][i]]);
	for(int i = head[x];i;i = nxt[i])
	{
		int u = to[i];
		if(u==f[x]) continue;
		cnt[col[i]]++,len[col[i]]+=w[i];
		dfs(u);
		cnt[col[i]]--,len[col[i]]-=w[i];
	}
}
signed main()
{
	cin>>n>>q;
	for(int i = 1,a,b,c,d;i<n;i++)
		cin>>a>>b>>c>>d,add(a,b,c,d),add(b,a,c,d);
	dfs1(1),dfs2(1);
	for(int i = 1,x,y,u,v;i<=q;i++)
		cin>>x>>y>>u>>v,add_q(u,x,y,1,i),add_q(v,x,y,1,i),add_q(lca(u,v),x,y,-2,i);
	dfs(1);
	for(int i = 1;i<=q;i++)
		cout<<ans[i]<<'\n';
	return 0;
}
```

## 后记

感谢 @[Mu_leaf](/user/701254) 帮忙调树剖代码。

---

## 作者：AK_heaven (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT4809)

看了各位大佬的可持久化线段树以及树上莫队和根号分治，但是，这道题好像不需要如此复杂。

普通线段树就可以维护！！！

先常规操作，将树进行重链剖分，顺便来个边转点。

然后用线段树来维护每条链。考虑到题目本质是求路径上的某种颜色其边数和边权和，答案是总边权减去指定颜色边权和，然后加上指定颜色边数与修改后的边权的乘积。我们可以用线段树维护每个区间内每种颜色对应的边数和边权和以及不分颜色的边权和。

怎么维护呢？开桶肯定是不行的。树上启发式合并？不需要！！！我们直接用 map 即可。

为什么 map 行？首先考虑时间复杂度，$ O(Q \log^{2} n + n \log^2 n)$ ，前者为查询时间复杂度，后者为建树时间复杂度。看看时限，虽说 map 常数大了点，但是四秒十万的数据还是随便过的。

现在最担心的是空间了，我们考虑最坏情况，每个边的颜色都不一样，此时我们会发现线段树的每层都恰好有 n 个节点，而一共有 $\log$ 层节点，所以空间复杂度也可行。

剩下的就是代码有点小小的复杂。


```cpp
#include <bits/stdc++.h>

#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
#define pii pair<ll, ll>
#define ll long long
#define vi vector<int>

#define int long long

using namespace std;

const int N = 1e5 + 10;

int h[N], tot;

struct Edge {
	ll v, w, c, last;
}e[N<<2];

void add(int u, int v, ll w, ll c) {
	e[++tot] = {v, w, c, h[u]};
	h[u] = tot;
}

ll dep[N], dfn[N], top[N], rk[N], w[N], col[N], dfc, fa[N], sz[N], son[N], n, q;

void dfs1(int u) {
	sz[u] = 1, son[u] = -1;
	for(int i = h[u]; i; i = e[i].last) {
		int v = e[i].v, c = e[i].c, W = e[i].w;
		if(v == fa[u]) continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		w[v] = W;
		col[v] = c;
		dfs1(v);
		sz[u] += sz[v];
		if(son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
	}
}

void dfs2(int u, int t) {
	top[u] = t;
	dfn[u] = ++dfc;
	rk[dfc] = u;
	if(son[u] == -1) return ;
	dfs2(son[u], t);
	for(int i = h[u]; i; i = e[i].last) {
		int v = e[i].v;
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}

#define ls (p<<1)
#define rs (p<<1|1)

struct Seg {
	map<ll, pii> cnt;
	ll l, r, s;
}tr[N<<2];

void work(Seg &p, ll id, ll f, ll s) {
	p.cnt[id].first += f;
	p.cnt[id].second += s;
}

void pushup(int p) {
	tr[p].cnt.clear();
	for(auto x : tr[ls].cnt)
	  work(tr[p], x.first, x.second.first, x.second.second);
	for(auto x : tr[rs].cnt)
	  work(tr[p], x.first, x.second.first, x.second.second);
	tr[p].s = tr[ls].s + tr[rs].s;
}

void build(int p, int l, int r) {
	tr[p].l = l, tr[p].r = r;
	if(l == r) {
		tr[p].cnt[col[rk[l]]] = make_pair(1, w[rk[l]]);
		tr[p].s = w[rk[l]];
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid);
	build(rs, mid+1, r);
	pushup(p);
}

ll query1(int p, int x, int y) {
	if(x <= tr[p].l && tr[p].r <= y)
	  return tr[p].s;
	ll mid = (tr[p].l + tr[p].r) >> 1;
	ll ret = 0;
	if(x <= mid) ret += query1(ls, x, y);
	if(y >  mid) ret += query1(rs, x, y);
	return ret;
}

pii query2(int p, int x, int y, int id) {
	if(x <= tr[p].l && tr[p].r <= y)
	  return tr[p].cnt[id];
	int mid = (tr[p].l + tr[p].r) >> 1;
	pii ret = make_pair(0, 0);
	pii tem;
	if(x <= mid) tem = query2(ls, x, y, id), ret.first += tem.first, ret.second += tem.second;
	if(y >  mid) tem = query2(rs, x, y, id), ret.first += tem.first, ret.second += tem.second;
	return ret;
}

ll q1(int u, int v, ll id, ll qwq) {
	ll ret = 0, cnt = 0, sum = 0;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		pii tem = query2(1, dfn[top[u]], dfn[u], id);
		cnt += tem.first, sum += tem.second;
		ret += query1(1, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u, v);
	if(u != v) {
		pii tem = query2(1, dfn[u]+1, dfn[v], id);
		cnt += tem.first, sum += tem.second;
		ret += query1(1, dfn[u]+1, dfn[v]);
	}
	ret -= sum;
	ret += cnt*qwq;
//	cout << cnt << ' ' << sum << '\n';
	return ret;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> q;
	L(i, 2, n) {
		int u, v, c, w;
		cin >> u >> v >> c >> w;
		add(u, v, w, c);
		add(v, u, w, c);
	}
	dfs1(1);
	dfs2(1, 1);
	build(1, 1, n);
	L(i, 1, q) {
		int u, v, c, w;
		cin >> c >> w >> u >> v;
		cout << q1(u, v, c, w) << '\n';
	}
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：1)

根据题意，询问 $x,y,u,v$ 的答案等于 $u\to v$ 上原本的边权和 $-u\to v$ 上原本的颜色 $=x$ 的边权和 $+y\times u\to v$ 上颜色 $=x$ 的边的数量。

主席树维护之。维护 $P_i$ 表示根到 $i$ 的版本，在 $x$ 位置的节点上维护颜色 $=x$ 的总边权和总数量，

则 $u\to v$ 上原本的颜色 $=x$ 的边权和、$u\to v$ 上颜色 $=x$ 的边的数量都可以由 $P_u,P_v,P_{\operatorname{LCA}(u,v)}$ 上 $x$ 位置的信息树上差分得到。

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
struct E{int v, c, w, nxt;}e[200050];
int n, q, o, cnt, head[100050], dep[100050], fa[100050][20], a[100050], P[100050], c[100050 << 7], z[100050 << 7], ls[100050 << 7], rs[100050 << 7];
void add(int u, int v, int c, int w) {e[++cnt] = {v, c, w, head[u]};head[u] = cnt;}
void dfs(int u)
{
    for(int i = head[u];i;i = e[i].nxt)
        if(e[i].v != fa[u][0]) dep[e[i].v] = dep[u] + 1, fa[e[i].v][0] = u, dfs(e[i].v);
}
int lca(int x, int y)
{
    if(dep[x] < dep[y]) swap(x, y);
    while(dep[x] > dep[y])
        x = fa[x][(int)log2(dep[x] - dep[y])];
    if(x == y) return x;
    for(int k = 18;k >= 0;--k)
        if(fa[x][k] != fa[y][k])
            x = fa[x][k], y = fa[y][k];
    return fa[x][0];
}
int bld(int s, int t)
{
    int p = ++o;
    if(s == t) return p;int m = s + t >> 1;
    ls[p] = bld(s, m);rs[p] = bld(m + 1, t);
    return p;
}
int chg(int x, int y, int s, int t, int d)
{
    int p = ++o;
    ls[p] = ls[d];rs[p] = rs[d];c[p] = c[d] + 1;z[p] = z[d] + y;
    if(s == t) return p;int m = s + t >> 1;
    if(x <= m) ls[p] = chg(x, y, s, m, ls[p]);
    else rs[p] = chg(x, y, m + 1, t, rs[p]);
    return p;
}
int Q(int x, int s, int t, int p)
{
    if(s == t) return p;
    int m = s + t >> 1;
    if(x <= m) return Q(x, s, m, ls[p]);
    else return Q(x, m + 1, t, rs[p]);
}
void dfs1(int u)
{
    for(int i = head[u], v;i;i = e[i].nxt)
        if((v = e[i].v) != fa[u][0]) P[v] = chg(e[i].c, e[i].w, 1, n, P[u]), dfs1(v);
}
int main()
{
    scanf("%d%d", &n, &q);
    P[1] = bld(1, n);
    for(int i = 1, x, y, c, w;i < n;++i)
        scanf("%d%d%d%d", &x, &y, &c, &w), add(x, y, c, w), add(y, x, c, w);
    dfs(dep[1] = 1);dfs1(1);
    for(int j = 1;j <= 18;++j)
        for(int i = 1;i <= n;++i)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
    for(int i = 0, k, o, u, v, l, U, V, L;i < q;++i)
        scanf("%d%d%d%d", &k, &o, &u, &v), U = Q(k, 1, n, P[u]), V = Q(k, 1, n, P[v]), L = Q(k, 1, n, P[l = lca(u, v)]),
        printf("%d\n", z[P[u]] + z[P[v]] - (z[P[l]] << 1) - (z[U] + z[V] - (z[L] << 1)) + o * (c[U] + c[V] - (c[L] << 1)));
    return 0;
}
```


---

## 作者：yizhiming (赞：1)

这道题不用树剖也是能做的吧，本人除了 LCA 用了树剖外，代码中没有用到任何和树剖相关的部分，貌似是和第一篇题解做法一样，但是他没有详细说明，所以我展开说一下。

## 题面描述

给定一棵树，边有边权和颜色，每次询问 $u$ 到 $v$ 在所有颜色为 $x$ 的边权视作 $y$ 的条件下的路径和。

读入不超过 $10^5$，边权不超过 $10^4$。

## 题目分析

我们先摒弃掉颜色的限制，只考虑边权和怎么做？

显然设 $dis_i$ 为节点 $i$ 到根节点的路径和，设 $L = LCA(u,v)$，那么就有路径和为 $dis_u+dis_v-2\times dis_L$。

所以现在问题就变成了找出这段路径上颜色 $x$ 的边数和对应的边权和，我们还是可以只维护每个节点到根节点的这两个值，然后用上面的方法求得路径总和。

所以说我们现在只需要维护出来每个节点到根节点的路径上，每种颜色的出现次数和对应边权和即可。我们既要维护每种颜色的和，还要维护边权和的和，想到什么？

值域线段树可以很好地处理这一点，我们在值域线段树上下标为 $i$ 的节点处，记录颜色为 $i$ 的边权的出现次数和边权和即可。

但是我们自然不能开 $n$ 棵值域线段树，空间直接爆炸，所以我们考虑如何将贡献统计到儿子上，注意到每次修改是单点修改，且仅与父亲节点有关，所以我们可以用可持久化值域线段树来维护，考虑每次以父节点为蓝本建树，这样每次最多新建 $\log V$ 个节点，复杂度正确。

## Code

具体做法就是 dfs 一遍建树，在建树过程中维护可持久化，查询的时候查询对应树的权值和，和 $cnt_x\times k-val_x$ 的值即可。

因为我比较懒不想返回两个值，所以在 ask 函数里直接求出了答案。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 1e5+5;
struct aa{
	int nxt,to,val,col;
}edge[N*2];
int tote,head[N];
void add(int u,int v,int c,int w){
	edge[++tote].nxt = head[u];edge[tote].to = v;head[u] = tote;edge[tote].col = c;edge[tote].val = w;
}
int tot,rt[N];
struct bb{
	int lc,rc,val,siz;
}node[N*20];
void ins(int &u,int v,int l,int r,int x,int y){
	u = ++tot;
	node[u] = node[v];
	node[u].val+=y;
	node[u].siz++;
	if(l==r){
		return;
	}
	int mid = (l+r)/2;
	if(x<=mid){
		ins(node[u].lc,node[v].lc,l,mid,x,y);
	}else{
		ins(node[u].rc,node[v].rc,mid+1,r,x,y);
	}
}
int ask(int u,int l,int r,int x,int y){
	if(l==r){
		return node[u].siz*y-node[u].val;
	}
	int mid = (l+r)/2;
	if(x<=mid){
		return ask(node[u].lc,l,mid,x,y);
	}else{
		return ask(node[u].rc,mid+1,r,x,y);
	}
}
int top[N],siz[N],son[N],fa[N],dep[N];
void dfs(int u,int f){
	siz[u] = 1;
	for(int i=head[u];i;i=edge[i].nxt){
		int now = edge[i].to;
		if(now==f){
			continue;
		}
		fa[now] = u;
		dep[now] = dep[u]+1;
		ins(rt[now],rt[u],1,1e5,edge[i].col,edge[i].val);
		dfs(now,u);
		siz[u]+=siz[now];
		if(siz[now]>siz[son[u]]){
			son[u] = now;
		}
	}
}
void dfs2(int u,int t){
	top[u] = t;
	if(!son[u]){
		return;
	}
	dfs2(son[u],t);
	for(int i=head[u];i;i=edge[i].nxt){
		int now = edge[i].to;
		if(now==fa[u]||now==son[u]){
			continue;
		}
		dfs2(now,now);
	}
}
int Lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]){
			swap(u,v);
		}
		u = fa[top[u]];
	}
	if(dep[u]<dep[v]){
		swap(u,v);
	}
	return v;
}
int n,q; 
int getval(int u,int c,int w){
	int res = node[rt[u]].val;
	res+=ask(rt[u],1,1e5,c,w);
	return res;
}
int ask(int u,int v,int c,int w){
	int L = Lca(u,v);
	return getval(u,c,w)+getval(v,c,w)-2*getval(L,c,w);
}

int main(){
	int u,v,c,w;
	n = read();q = read();
	for(int i=1;i<n;i++){
		u = read();v = read();c = read();w = read();
		add(u,v,c,w);add(v,u,c,w);
	}
	dfs(1,0);
	dfs2(1,1);
	while(q--){
		c = read();w = read();u = read();v = read();
		cout<<ask(u,v,c,w)<<"\n";
	}
	return 0;
}
```


---

## 作者：Rushroom (赞：1)

树状数组 ×

树链剖分 ×

码力题 √

很容易想到，对于一个查询：$x_i,y_i,u_i,v_i$，设 $u_i$ 到 $v_i$ 简单路径上为 $route$，那么查询的答案就是：($route$ 的长度）$-$（$route$ 上颜色为 $x_i$ 的长度和）$+$（$route$ 上颜色为 $x_i$ 的边的个数）$\cdot$ $y_i$。 

对于第一项，可以用 **树链剖分** 简单地解决。

对于后面两项，可以把操作离线下来，对于每个颜色 $x$ 分别处理，把所有颜色为 $x$ 的边放到树状数组上去维护。

**注意：**

1. BIT update 后要还原

2. 树剖不能维护边的信息，所以用每个点 $i$ 维护 $i$ 到 $fa_i$ 的边的长度。

3. LCA 的权值不能计入答案里，因为 $x$ 到 $y$ 的路径上不包含 LCA 到它的父亲的那条边。

4. 树剖不要写错，这里给出 FGgirl 的错误：

树剖求 LCA 的时候，每次应该把 $x$ 和 $y$ 中 $dep_{top}$ 更大的一者往上跳，而 FGgirl 写成了比较 $dep$。如果您只对了 $\frac{1}{3}$ 的测试点，那大概就是这个错误。

另外对代码的说明：因为 FGgirl 懒得写两个 BIT，所以她一直反复用同一个 BIT，注意清空。

[**Code**](https://www.luogu.com.cn/paste/5d474new)

---

## 作者：EastPorridge (赞：1)

我方对题解区清一色的 $\log$ 算法表示强烈谴责，然后写了个 $O(n \sqrt n)$ 的树上莫队，也跑的飞快。

### 题目分析：

对于莫队来说，比较棘手的地方就在每次同颜色改变权值的操作，但同时也说了每次询问独立，所以我们可以额外存储一下对于当前询问路径，这个颜色 $i$ 的个数 $num_i$ 和其所对应的权值 $sum_i$，对于答案就简单容斥，假设把所有颜色 $x_i$ 的权值都变成 $y$，就相当于在原答案上减去 $sum_{x_i}$，加上 $num_{x_i} \times y$，这样就可以解决了。

又因为这是个边权问题，所以我们要把边权化点权，把树拍成欧拉序，也不需要记录 lca 的信息了，如果一个点是另外一个点的 lca，就直接用入序 $st[lca]+1$ 规避掉就可以了。

需要注意的是，拍成欧拉序的树长度是 $2 \times n$ 的，对应块长也应该是 $\sqrt{2 \times n}$，不然会损失效率。

### Code.

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e5+10; pair<int,int> pl[N];
int yl[N],res,ans[N],len,h[N],ne[N<<1],e[N<<1],w[N<<1],col[N<<1],idx,n,m,num[N],sum[N],st[N],vis[N],ed[N],top[N],dep[N],fa[N],sz[N],son[N],cnt;
int get(int x) {return x/len;}
struct node
{
	int l,r,x,y,id;
	bool operator < (const node &o) const {
		if(get(l) == get(o.l)) return get(l)&1 ? r < o.r : r > o.r;
		return get(l) < get(o.l);
	}
} q[N];
void add(int u,int v,int co,int c) {ne[++idx]=h[u],e[idx]=v,col[idx]=co,w[idx]=c,h[u]=idx;}
void dfs(int u,int father,int depth)
{
	dep[u]=depth; sz[u]=1; fa[u]=father; yl[++cnt]=u; st[u]=cnt;
	for(int i=h[u];~i;i=ne[i])
	{
		int j=e[i]; if(j == father) continue ;
		pl[j]=make_pair(col[i],w[i]); dfs(j,u,depth+1);
		sz[u]+=sz[j]; if(sz[son[u]] < sz[j]) son[u]=j;
	}
	yl[++cnt]=u; ed[u]=cnt;
}
void dfs2(int u,int t)
{
	top[u]=t; if(! son[u]) return ; dfs2(son[u],t);
	for(int i=h[u];~i;i=ne[i])
	{
		int j=e[i];
		if(j == fa[u] || j == son[u]) continue ;
		dfs2(j,j);
	}
}
int lca(int u,int v)
{
	while(top[u] != top[v])
	{
		if(dep[top[u]] < dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}
void work(int u)
{
	if(vis[u]) {num[pl[u].x]--; sum[pl[u].x]-=pl[u].y; res-=pl[u].y;}
	else {num[pl[u].x]++; sum[pl[u].x]+=pl[u].y; res+=pl[u].y;}
	vis[u]^=1;
}
int main()
{
	memset(h,-1,sizeof h); scanf("%d%d",&n,&m); len=(int)sqrt(2*n);
	for(int i=1,u,v,co,c;i<n;i++) {scanf("%d%d%d%d",&u,&v,&co,&c); add(u,v,co,c); add(v,u,co,c);}
	dfs(1,0,1); dfs2(1,1);
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d%d%d",&q[i].x,&q[i].y,&u,&v); q[i].id=i;
		if(st[u] > st[v]) swap(u,v);
		if(lca(u,v) == u) q[i].l=st[u]+1,q[i].r=st[v];
		else q[i].l=ed[u],q[i].r=st[v];
	}
	stable_sort(q+1,q+1+m);
	for(int i=1,l=1,r=0;i<=m;i++)
	{
		int l1=q[i].l,r1=q[i].r;
		while(l > l1) work(yl[--l]);
		while(r < r1) work(yl[++r]);
		while(l < l1) work(yl[l++]);
		while(r > r1) work(yl[r--]);
		ans[q[i].id]=res-sum[q[i].x]+num[q[i].x]*q[i].y;
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Clover_BY (赞：0)

# [ABC133F  Colorful Tree](https://www.luogu.com.cn/problem/AT_abc133_f)
## 题目描述
给定一棵 $n$ 个节点的树，树上每条边都有一个颜色 $c_i$ 和一个权值 $d_i$。  
要求支持 $m$ 次询问，每次查询若将所有颜色为 $x$ 的权值改为 $y$，节点 $u$ 到 $v$ 简单路径上所有边的权值之和将变为多少。注意询问并不会对边的权值做出真实修改。
## 题目分析
再来一发树剖+主席树题解。  

貌似大家都是先找了 LCA 捏……  
其实按照传统树剖形式边跳链边统计也是可行的。

先来分析一下询问。  
考虑能否在不作出修改的前提下得到询问的答案。  
注意到每次只有一种颜色的边被修改，因此我们可以分开维护各种颜色的边。  
每次操作相当于将路径上所有颜色为 $x_i$ 的边的贡献去掉，记录这些边的总数 $cnt$，再把 $cnt\times y$ 累计到贡献中。其他颜色边的贡献不变。

因此我在树剖过程中记录了三个值：原树上 $u$ 到 $v$ 路径上所有边权之和 $ans_1$，路径上颜色为 $x$ 的边权之和 $ans_2$ 以及上述 $cnt$。  
三者可以同时用一棵主席树维护。按照 dfn 序顺次插入每条边的权值，在每种颜色对应的位置上维护其边权和及边的条数，查询时为基本主席树操作。  
单次查询的答案即为 $ans_1-ans_2+cnt\times y$。

细节：注意到需要边权转点权并同时确定 dfn 序对应的边，因此可以另开一个数组记录每个点是由哪一条边进行遍历的，主席树修改时会更方便地确定要插入的值。

## Code
```cpp
#include <cstdio>
#include <cctype>
#define ls tree[u].lson
#define rs tree[u].rson
#define sm tree[u].sum
#define ut tree[u].tot
#define tls tree[rt].lson
#define trs tree[rt].rson
#define tsm tree[rt].sum
#define tut tree[rt].tot
using namespace std;

inline void qswap(int &u, int &v)
{
    int t = u; u = v;
    v = t; return ;
}

inline int read()
{
    int x = 0; char c;
    while(!isdigit(c = getchar()));
    do{
        x = (x << 1) + (x << 3) + (c ^ 48);
    }while(isdigit(c = getchar()));
    return x;
}

int p = 0, stk[20];
inline void write(int x)
{
    do{
        stk[++p] = x % 10;
        x /= 10;
    }while(x);
    for(register int i = p; i; --i)
        putchar(stk[i] | 48);
    putchar('\n'); p = 0;
    return ;
}

int n, m, x, y, u, v, cnt = 1, tim = 0, tot = 0;
int head[100010], root[100010], siz[100010];
int depth[100010], father[100010], son[100010];
int top[100010], dfn[100010], rev[100010], rec[100010];
int from[100010], to[100010], col[100010], dist[100010];
struct edge
{
    int to;
    int next;
}e[200010];
struct node
{
    int lson;
    int rson;
    int sum;
    int tot;
}tree[2000010];

inline void insert(int u, int v)
{
    e[++cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
    return ;
}

inline void modify(int rt, int &u, int l, int r, int pos, int val)
{
    u = ++tot; tree[u] = tree[rt];
    sm += val; ++ut; if(l == r) return ;
    int mid = l + r >> 1;
    if(pos <= mid) modify(tls, ls, l, mid, pos, val);
    else modify(trs, rs, mid + 1, r, pos, val);
    return ;
}

inline node query(int rt, int u, int l, int r, int pos)
{
    if(l == r) return (node){0, 0, sm - tsm, ut - tut};
    int mid = l + r >> 1;
    if(pos <= mid) return query(tls, ls, l, mid, pos);
    else return query(trs, rs, mid + 1, r, pos);
}

inline void dfs1(int u, int fa)
{
    siz[u] = 1;
    for(register int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        if(v == fa) continue;
        father[v] = u;
        depth[v] = depth[u] + 1;
        dfs1(v, u); siz[u] += siz[v];
        if(siz[son[u]] < siz[v])
        {
            son[u] = v;
            rec[v] = i >> 1;
        }
    }
    return ;
}

inline void dfs2(int u, int tp)
{
    top[u] = tp;
    if(son[u])
    {
        dfn[son[u]] = ++tim;
        rev[tim] = rec[son[u]];
        dfs2(son[u], tp);
    }
    for(register int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        if(v == father[u] || v == son[u]) continue;
        dfn[v] = ++tim;
        rev[tim] = i >> 1; dfs2(v, v);
    }
    return ;
}

inline int query(int u, int v, int col, int val)
{
    if(u == v) return 0;
    int ans1 = 0, ans2 = 0, num = 0;
    while(top[u] != top[v])
    {
        if(depth[top[u]] < depth[top[v]]) qswap(u, v);
        x = dfn[top[u]] - 1; y = dfn[u];
        ans1 += tree[root[y]].sum - tree[root[x]].sum;
        node tmp = query(root[x], root[y], 1, n, col);
        ans2 += tmp.sum; num += tmp.tot;
        u = father[top[u]];
    }
    if(depth[u] > depth[v]) qswap(u, v);
    x = dfn[son[u]] - 1; y = dfn[v];
    ans1 += tree[root[y]].sum - tree[root[x]].sum;
    node tmp = query(root[x], root[y], 1, n, col);
    ans2 += tmp.sum; num += tmp.tot;
    return ans1 - ans2 + num * val;
}

int main()
{
    n = read(); m = read();
    for(register int i = 1; i < n; ++i)
    {
        from[i] = read(); to[i] = read();
        col[i] = read(); dist[i] = read();
        insert(from[i], to[i]);
        insert(to[i], from[i]);
    }
    dfs1(1, 0); dfs2(1, 1);
    for(register int i = 1; i <= tim; ++i)
        modify(root[i - 1], root[i], 1, n, col[rev[i]], dist[rev[i]]);
    for(register int i = 1; i <= m; ++i)
    {
        x = read(); y = read(); u = read(); v = read();
        write(query(u, v, x, y));
    }
    return 0;
}
```

---

## 作者：tzc_wk (赞：0)

> AT4809 Colorful Tree

> 题意：有一棵树，边上有边权，每条边还有颜色。然后给你 $q$ 次询问，每次询问给你四个数 $u,v,x,y$，问你：**如果**将 $u$ 到 $v$ 路径上所有颜色为 $x$ 的边的边权都变为 $y$，那么 $u$ 到 $v$ 路径上边权的和。

> $1 \leq n \leq 10^5$，$1 \leq q \leq 10^5$。

一道树剖题

首先，我们要求的答案就是 $u$ 到 $v$ 的路径上颜色 $\neq x$ 的边权和，加上 $u$ 到 $v$ 的路径上颜色 $= x$ 的边的个数 $\times y$。

我们将询问离线下来。然后枚举每一种颜色。开两棵线段树，一棵表示权值和，一棵表示个数。每次枚举颜色 $i$，然后将所有颜色 $=i$ 的边在第一棵线段树上的值改为 $0$，第二棵线段树上的值改为 $1$。回答所有 $x=i$ 的询问。枚举结束的时候，将所有颜色 $=i$ 的边在第一棵线段树上的值改为它原本的边权，第二棵线段树上的值改为 $0$。

这样均摊下来就是 $\mathcal O(n)$ 次修改操作和询问操作。加上树剖的复杂度，就可以过了。

然后你就可以嘲讽出题人：有本事强制在线啊。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n=read(),m=read();
struct edge{
	int u,v,c,d,id;
} e[100005];
struct query{
	int u,v,x,y;
} q[100005];
vector<edge> g[100005];
vector<int> es[100005];
vector<int> qs[100005];
int fa[100005],sz[100005],dfn[100005],dep[100005],wson[100005],id[100005],idx=0;
int eid[100005],w[100005],top[100005];
inline void dfs1(int x,int prev){
	fa[x]=prev;sz[x]=1;
	for(int i=0;i<g[x].size();i++){
		edge E=g[x][i];
		int y=E.v;
		if(y==prev)	continue;
		eid[E.id]=y;w[y]=E.d;
		dep[y]=dep[x]+1;
		dfs1(y,x);
		sz[x]+=sz[y];
		if(sz[y]>sz[wson[x]])	wson[x]=y;
	}
}
inline void dfs2(int x,int tp){
	top[x]=tp;
	dfn[x]=++idx;
	id[idx]=x;
	if(wson[x])	dfs2(wson[x],tp);
	for(int i=0;i<g[x].size();i++){
		edge e=g[x][i];
		int y=e.v;
		if(y==fa[x]||y==wson[x])	continue;
		dfs2(y,y);
	}
}
struct SegTree{
	struct node{
		int k,l,r,val1,val2;
	} s[100005<<2];
	inline void build(int k,int l,int r){
		s[k].l=l;s[k].r=r;
		if(l==r){
			s[k].val1=w[id[l]];
//			cout<<"setup "<<l<<" "<<w[id[l]]<<endl;
			s[k].val2=0;
			return;
		}
		int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		s[k].val1=s[k<<1].val1+s[k<<1|1].val1;
	}
	inline void modify_1(int k,int ind,int x){
		if(s[k].l==s[k].r){
//			cout<<"modify_1 "<<s[k].l<<" "<<x<<endl;
			s[k].val1=x;
			return;
		}
		int mid=(s[k].l+s[k].r)>>1;
		if(ind<=mid)	modify_1(k<<1,ind,x);
		else			modify_1(k<<1|1,ind,x);
		s[k].val1=s[k<<1].val1+s[k<<1|1].val1;
	}
	inline void modify_2(int k,int ind,int x){
		if(s[k].l==s[k].r){
//			cout<<"modify_2 "<<s[k].l<<" "<<x<<endl;
			s[k].val2=x;
			return;
		}
		int mid=(s[k].l+s[k].r)>>1;
		if(ind<=mid)	modify_2(k<<1,ind,x);
		else			modify_2(k<<1|1,ind,x);
		s[k].val2=s[k<<1].val2+s[k<<1|1].val2;
	}
	inline int query_1(int k,int l,int r){
		if(l>r)	return 0;
		if(l<=s[k].l&&s[k].r<=r){
			return s[k].val1;
		}
		int mid=(s[k].l+s[k].r)>>1;
		if(r<=mid)		return query_1(k<<1,l,r);
		else if(l>mid)	return query_1(k<<1|1,l,r);
		else			return query_1(k<<1,l,mid)+query_1(k<<1|1,mid+1,r);
	}
	inline int query_2(int k,int l,int r){
		if(l>r)	return 0;
		if(l<=s[k].l&&s[k].r<=r){
			return s[k].val2;
		}
		int mid=(s[k].l+s[k].r)>>1;
		if(r<=mid)		return query_2(k<<1,l,r);
		else if(l>mid)	return query_2(k<<1|1,l,r);
		else			return query_2(k<<1,l,mid)+query_2(k<<1|1,mid+1,r);
	}
} st;
inline int query(int u,int v,int x){
//	cout<<u<<" "<<v<<" "<<x<<endl;
	if(dep[u]<dep[v])	swap(u,v);
	int ans=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])	swap(u,v);
//		cout<<"query "<<dfn[top[u]]<<" "<<dfn[u]<<endl;
		ans+=st.query_1(1,dfn[top[u]],dfn[u]);
		ans+=x*st.query_2(1,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dep[u]<dep[v])	swap(u,v);
	if(u!=v){
//		cout<<"query "<<dfn[v]+1<<" "<<dfn[u]<<endl;
		ans+=st.query_1(1,dfn[v]+1,dfn[u]);
		ans+=x*st.query_2(1,dfn[v]+1,dfn[u]);
	}
	return ans;
}
int q_ans[100005];
signed main(){
	fz(i,1,n-1){
		e[i].u=read();e[i].v=read();e[i].c=read();e[i].d=read();
		e[i].id=i;
		g[e[i].u].push_back({e[i].u,e[i].v,e[i].c,e[i].d,i});
		g[e[i].v].push_back({e[i].v,e[i].u,e[i].c,e[i].d,i});
		es[e[i].c].push_back(i);
	}
	fz(i,1,m){
		q[i].x=read();q[i].y=read();q[i].u=read();q[i].v=read();
		qs[q[i].x].push_back(i);
	}
	dfs1(1,0);dfs2(1,1);
//	fz(i,1,n)	cout<<w[id[i]]<<endl;
	st.build(1,1,n);
	fz(i,1,n-1){
		foreach(it,es[i]){
			int j=eid[*it];
//			cout<<i<<" "<<j<<endl;
			st.modify_1(1,dfn[j],0);
			st.modify_2(1,dfn[j],1);
		}
//		cout<<i<<endl;
		foreach(it,qs[i]){
			int j=*it;
			q_ans[j]=query(q[j].u,q[j].v,q[j].y);
		}
		foreach(it,es[i]){
			int j=eid[*it];
			st.modify_1(1,dfn[j],e[*it].d);
			st.modify_2(1,dfn[j],0);
		}
	}
	fz(i,1,m)	cout<<q_ans[i]<<endl;
	return 0;
}
```

---

