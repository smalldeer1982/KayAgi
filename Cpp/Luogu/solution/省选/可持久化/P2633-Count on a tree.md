# Count on a tree

## 题目描述

给定一棵 $n$ 个节点的树，每个点有一个权值。有 $m$ 个询问，每次给你 $u,v,k$，你需要回答 $u \text{ xor last}$ 和 $v$ 这两个节点间第 $k$ 小的点权。  

其中 $\text{last}$ 是上一个询问的答案，定义其初始为 $0$，即第一个询问的 $u$ 是明文。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n,m \le 10^5$，点权在 $[1, 2 ^ {31} - 1]$ 之间。

暴力自重。。。

来源：bzoj2588 Spoj10628.

本题数据为洛谷自造数据，使用 [CYaRon](https://github.com/luogu-dev/cyaron) 耗时 5 分钟完成数据制作。


## 样例 #1

### 输入

```
8 5
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5 1
0 5 2
10 5 3
11 5 4
110 8 2```

### 输出

```
2
8
9
105
7```

# 题解

## 作者：tth37 (赞：57)

[更佳阅读体验](https://tth37.cn/2019/05/20/solution-luogu-p2633/)

> 这题不难呀，怎么调了这么久？         ——Mr. G

前置知识是主席树。在利用主席树求解区间第K小数时可以发现，主席树是一种类似前缀和的数据结构，具有和前缀和类似的区间加减及差分等优秀性质。在求解线性区间的第K小数时，我们需要将该区间内的所有数值信息扔到一棵主席树中，并在这棵主席树上左右递归，以找到第K小数；同样的，我们可以类比树上前缀和的操作，定义$s[u]$为从根节点到第$u$号节点的“前缀主席树”（感性理解谢谢）。那么，包含$u$到$v$上所有数值信息的主席树就应该是：
$$
s[u]+s[v]-s[lca(u,v)]-s[fa[lca(u,v)]]
$$
理解上式后，问题基本可以解决了。另外注意离散化和主席树的代码细节。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
// 离散化操作
#define id(x) (lower_bound(b+1,b+L+1,a[x])-b)
#define rid(x) (b[x])

const int MAXN = 100005;

struct Node {
    int l, r, sum;
}node[10000005];
int head[MAXN],cnt;

vector<int> G[MAXN];

int N, M, L, lastans;
int a[MAXN], b[MAXN];
int f[MAXN][19], dep[MAXN];

inline void build(Node &u, int l, int r) {
    u.sum = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(node[u.l = ++cnt], l, mid);
    build(node[u.r = ++cnt], mid + 1, r);
}

inline void insert(Node c, Node &u, int l, int r, int p) {
    u.sum = c.sum + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if(p <= mid)
        insert(node[c.l], node[u.l = ++cnt], l, mid, p), u.r = c.r;
    else
        insert(node[c.r], node[u.r = ++cnt], mid+1, r, p), u.l = c.l;
}

inline void dfs(int u, int fa) {
    insert(node[head[fa]], node[head[u] = ++cnt], 1, L, id(u));
    f[u][0] = fa;
    dep[u] = dep[fa] + 1;
    for (register int i = 1; i <= 18; ++i)
        f[u][i] = f[f[u][i-1]][i-1];
    for (vector<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
        int v = *it;
        if (v == fa) continue;
        dfs(v, u);
    }
}

inline int Lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (register int i = 18; i >= 0; --i) {
        if (dep[f[u][i]] >= dep[v]) u = f[u][i];
    }
    if (u == v) return u;
    for (register int i = 18; i >= 0; --i) {
        if (f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
    }
    return f[u][0];
}

inline int query(Node x, Node y, Node z, Node w, int l, int r, int k) {
    if (l == r) return l;
    int sum = node[x.l].sum + node[y.l].sum - node[z.l].sum - node[w.l].sum;
    int mid = (l + r) >> 1;
    if(sum >= k) return query(node[x.l], node[y.l], node[z.l], node[w.l], l, mid, k);
    return query(node[x.r], node[y.r], node[z.r], node[w.r], mid+1, r, k - sum);
}

inline int querypath(int u, int v, int k) {
    int lca = Lca(u, v);
    return rid(query(node[head[u]], node[head[v]], node[head[lca]], node[head[f[lca][0]]], 1, L, k));
}

int main() {
    scanf("%d%d", &N, &M);
    for (register int i = 1; i <= N; ++i)
        scanf("%d", &a[i]), b[i] = a[i];
    for (register int i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    sort(b + 1, b + N + 1);
    L = unique(b + 1, b + N + 1) - (b + 1);
    build(node[head[0] = ++cnt], 1, L);
    dfs(1, 0);
    for (register int i = 1; i <= M; ++i) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        int nowans = querypath(u^lastans, v, k);
        printf("%d\n", nowans);
        lastans = nowans;
    }
}
```

---

## 作者：夏色祭 (赞：19)

主席树板子题啊。。。

只是把序列的操作改成了树上。。。

序列的主席树维护的是[1-i]这里维护从1到i的这条路径上的结点的值。

查询就套个树上差分：v[ql]+v[qr]-v[lca]-v[lca\_fa]。

lca的话再套个树剖lca就行了。

是不是很简单。。。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<string>
#define For(i,x,y) for (int i=x;i<=y;i++)
#define cross(i,k) for (int i=first[k];i;i=last[i])
#define N 100010
#define il inline
#define vd void
using namespace std;
struct node{
    int num,v;
}a[N];
int rt[N],v[N*20],lson[N*20],rson[N*20],to[N<<1],last[N<<1],first[N],b[N],rk[N];
int n,m,x,y,k,tot,cnt,lastans,lca;
il int read(){
    int x=0;int ch=getchar(),f=1;
    while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) ch=getchar();
    if (ch=='-'){f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
il bool cmp(node x,node y){return x.v<y.v;}
il vd add(int x,int y){to[++tot]=y,last[tot]=first[x],first[x]=tot;}
il vd insert(int &u,int last,int l,int r,int k){
    u=++cnt,v[u]=v[last]+1;
    if (l==r) return;
    lson[u]=lson[last],rson[u]=rson[last];
    int mid=l+r >> 1;
    if (k<=mid) insert(lson[u],lson[u],l,mid,k);
        else insert(rson[u],rson[u],mid+1,r,k);
```
}//插入
```cpp
int size[N],son[N],fa[N],dep[N];
il vd dfs(int k){
    size[k]=1,dep[k]=dep[fa[k]]+1;
    insert(rt[k],rt[fa[k]],1,n,b[k]);
    cross(i,k){
        int v=to[i];
        if (v==fa[k]) continue;
        fa[v]=k,dfs(v);
        size[k]+=size[v];
        if (!son[k]||size[v]>size[son[k]]) son[k]=v;
    }
}
int top[N];
il vd dfs(int k,int tp){
    top[k]=tp;
    if (!son[k]) return;
    dfs(son[k],tp);
    cross(i,k){
        int v=to[i];
        if (v==son[k]||v==fa[k]) continue;
        dfs(v,v);
    }
}
il int Lca(int x,int y){
    while (top[x]!=top[y])
        if (dep[top[x]]>=dep[top[y]]) x=fa[top[x]];
            else y=fa[top[y]];
    if (dep[x]>=dep[y]) return y;
        else return x; 
```
}//树剖lca
il int query(int ql,int qr,int lca,int lca\_fa,int l,int r,int k){

```cpp
    if (l==r) return l;
    int mid=l+r >> 1,t=v[lson[ql]]+v[lson[qr]]-v[lson[lca]]-v[lson[lca_fa]];
    if (t>=k) return query(lson[ql],lson[qr],lson[lca],lson[lca_fa],l,mid,k);
        else return query(rson[ql],rson[qr],rson[lca],rson[lca_fa],mid+1,r,k-t);
```
}//查询
```cpp
int main(){
    n=read(),m=read();
    For(i,1,n){
        b[i]=read();
        a[i].num=i,a[i].v=b[i];
    }
    sort(a+1,a+1+n,cmp),a[0].v=-233333333;
    For(i,1,n)
        if (a[i].v!=a[i-1].v) rk[++x]=b[a[i].num],b[a[i].num]=x;
            else b[a[i].num]=x;//离散
    For(i,1,n-1){
        x=read(),y=read();
        add(x,y),add(y,x);
    }
    dfs(1);
    dfs(1,1);
    For(i,1,m){
        x=read(),y=read(),k=read();
        x^=lastans,lca=Lca(x,y);
        lastans=rk[query(rt[x],rt[y],rt[lca],rt[fa[lca]],1,n,k)];
        printf("%d\n",lastans);
    }
    return 0;
}
```

---

## 作者：花淇淋 (赞：14)

第一步：离散化

即：把节点的点权换成它在所有点权中的排名（它是第几小的）

将存储点权的数组复制一份之后排序，去重，然后将原先的每个点权在去重后的数组里进行二分查找，就可以得到它的排名。


第二步：建主席树

每个节点维护它到根的路径上的权值线段树，所以每个节点可以利用它的父节点更新，所以将整棵树dfs一遍，在此过程中建树。


第三步：求解

用u点的主席树+v点的主席树-lca(u,v)的主席树-lca(u,v)父节点的主席树，在这样产生的主席树上查找第k小的排名，最后输出它原来的点权。


代码如下

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int e=1e5+5;
struct point
{
    int l,r,w;
}c[e*30];
int fa[e][21],a[e],h[e],tot,num,deep[e],n,m,rt[e],xxx,val[e];
int next[e<<1],head[e],go[e<<1];
inline int read()
{
    char ch;
    int res=0;
    bool f=false;
    while(ch=getchar(),(ch<'0'||ch>'9')&&ch!='-');
    if(ch=='-')f=true;
    else res=ch-48;
    while(ch=getchar(),ch>='0'&&ch<='9')
    res=(res<<3)+(res<<1)+ch-48;
    return f? -res:res;
}
inline void insert(int y,int &x,int l,int r,int p)
{
    c[x=++num]=c[y];
    c[x].w++;
    if(l==r)return;
    int mid=l+r>>1;
    if(p<=mid)insert(c[y].l,c[x].l,l,mid,p);
    else insert(c[y].r,c[x].r,mid+1,r,p);
    c[x].w=c[c[x].l].w+c[c[x].r].w;
}
inline int query(int x,int y,int z,int d,int l,int r,int k)
{
    if(l==r)return l;
    int ret=c[c[x].l].w+c[c[y].l].w-c[c[z].l].w-c[c[d].l].w;
    int mid=l+r>>1;
    if(k<=ret)
    return query(c[x].l,c[y].l,c[z].l,c[d].l,l,mid,k);
    else return query(c[x].r,c[y].r,c[z].r,c[d].r,mid+1,r,k-ret);
}
inline void add(int x,int y)
{
    next[++tot]=head[x];
    head[x]=tot;
    go[tot]=y;
    next[++tot]=head[y];
    head[y]=tot;
    go[tot]=x;
}
inline void dfs2(int u)
{
    insert(rt[fa[u][0]],rt[u],1,n,val[u]);
    for(int i=head[u];i;i=next[i])
    {
        int v=go[i];
        if(v==fa[u][0])continue;
        dfs2(v);
    }
}
inline void dfs(int u,int father)
{
    deep[u]=deep[father]+1;
    for(int i=0;i<=19;i++)
    fa[u][i+1]=fa[fa[u][i]][i];
    for(int i=head[u];i;i=next[i])
    {
        int v=go[i];
        if(v==father)continue;
        fa[v][0]=u;
        dfs(v,u);
    }
}
inline int lca(int x,int y)
{
    if(deep[x]<deep[y])swap(x,y);
    for(int i=19;i>=0;i--)
    {
        if(deep[fa[x][i]]>=deep[y])
        x=fa[x][i];
        if(x==y)return x;
    }
    for(int i=19;i>=0;i--)
    {
        if(fa[x][i]!=fa[y][i])
        {
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
inline int find(int x)
{
    int l=1,r=xxx,mid;
    while(l<=r)
    {
        mid=l+r>>1;
        if(x>h[mid])
        l=mid+1;
        else r=mid-1;
    }
    return l;
}
int main()
{
    int i,j,u,v,k;
    n=read();
    m=read();
    for(i=1;i<=n;i++)
    {
        val[i]=read();
        a[i]=val[i];
    }
    for(i=1;i<n;i++)
    {
        u=read();
        v=read();
        add(u,v);
    }
    sort(a+1,a+n+1);
    h[1]=a[1];
    xxx=1;
    for(i=2;i<=n;i++)
    if(a[i]!=a[i-1])h[++xxx]=a[i];
    for(i=1;i<=n;i++)
    val[i]=find(val[i]);
    dfs(1,0);
    int ans=0;
    dfs2(1);
    for(i=1;i<=m;i++)
    {
        u=read();
        v=read();
        k=read();
        u^=ans;
        int z=lca(u,v);
        int last=query(rt[u],rt[v],rt[z],rt[fa[z][0]],1,n,k);
        ans=h[last];
        printf("%d",ans);
        if(i!=m)putchar('\n');
    }
    return 0;
}
```

---

## 作者：bztMinamoto (赞：5)

安利一发我的[blog](https://www.cnblogs.com/bztMinamoto/p/9392425.html)

其实就是个很简单的主席树，只要把在序列上的建树改成在树上建就可以了
虽然我也是今天看到这道题看完题解才知道怎么在树上建主席树

关于路径，可以在树上差分一下用$sum[l]+sum[r]-sum[lca]-sum[lca_fa]$

然后因为要求lca，所以在树剖dfs的时候顺便建一下主席树就好了

具体实现请参考代码
```
//minamoto
#include<bits/stdc++.h>
#define N 100005
#define M 2000005
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
int sum[M],L[M],R[M];
int a[N],b[N],rt[N];
int fa[N],sz[N],d[N],ver[N<<1],Next[N<<1],head[N],son[N],top[N];
int n,q,m,cnt=0,tot=0,ans=0;
void update(int last,int &now,int l,int r,int x){
    sum[now=++cnt]=sum[last]+1;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(x<=mid) R[now]=R[last],update(L[last],L[now],l,mid,x);
    else L[now]=L[last],update(R[last],R[now],mid+1,r,x);
}
inline void add(int u,int v){
    ver[++tot]=v,Next[tot]=head[u],head[u]=tot;
    ver[++tot]=u,Next[tot]=head[v],head[v]=tot;
}
void dfs(int u){
    sz[u]=1,d[u]=d[fa[u]]+1;
    update(rt[fa[u]],rt[u],1,m,a[u]);
    for(int i=head[u];i;i=Next[i]){
        int v=ver[i];
        if(v==fa[u]) continue;
        fa[v]=u,dfs(v);
        sz[u]+=sz[v];
        if(!son[u]||sz[v]>sz[son[u]]) son[u]=v;
    }
}
void dfs(int u,int tp){
    top[u]=tp;
    if(!son[u]) return;
    dfs(son[u],tp);
    for(int i=head[u];i;i=Next[i]){
        int v=ver[i];
        if(v==son[u]||v==fa[u]) continue;
        dfs(v,v);
    }
}
int LCA(int x,int y){
    while(top[x]!=top[y])
    d[top[x]]>=d[top[y]]?x=fa[top[x]]:y=fa[top[y]];
    return d[x]>=d[y]?y:x;
}
int query(int ql,int qr,int lca,int lca_fa,int l,int r,int k){
    if(l>=r) return l;
    int x=sum[L[ql]]+sum[L[qr]]-sum[L[lca]]-sum[L[lca_fa]];
    int mid=(l+r)>>1;
    if(x>=k) return query(L[ql],L[qr],L[lca],L[lca_fa],l,mid,k);
    else return query(R[ql],R[qr],R[lca],R[lca_fa],mid+1,r,k-x);
}
int main(){
    //freopen("testdata.in","r",stdin);
    n=read(),q=read();
    for(int i=1;i<=n;++i)
    b[i]=a[i]=read();
    sort(b+1,b+1+n);
    m=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;++i)
    a[i]=lower_bound(b+1,b+1+m,a[i])-b;
    for(int i=1;i<n;++i){
        int u=read(),v=read();
        add(u,v);
    }
    dfs(1),dfs(1,1);
    while(q--){
        int x,y,z,lca;
        x=read(),y=read(),z=read();
        x^=ans,lca=LCA(x,y);
        ans=b[query(rt[x],rt[y],rt[lca],rt[fa[lca]],1,m,z)];
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Aleph1022 (赞：5)

第 K 大？主席树！

考虑树上静态求路径信息（具有区间减法性质）：  
$s_x + s_y - s_{lca} - s_{fa_{lca}}$，其中 $s_x$ 表示结点 $x$ 到根的信息。

那么扩展到主席树即可。

注意离散化！

注意重复元素！我就是因为这一点在 BZOJ RE，SPOJ 原题 WA 的，不过洛谷数据没有重复的。

代码：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int BUFF_SIZE = 1 << 20;
char BUFF[BUFF_SIZE],*BB,*BE;
#define gc() (BB == BE ? (BE = (BB = BUFF) + fread(BUFF,1,BUFF_SIZE,stdin),BB == BE ? EOF : *BB++) : *BB++)
template<class T>
inline void read(T &x)
{
    x = 0;
    char ch = 0,w = 0;
    while(ch < '0' | ch > '9')
        w |= ch == '-',ch = gc();
    while(ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + (ch ^ '0'),ch = gc();
    w ? x = -x : x;
}
     
#define ls(p) seg[p].lson
#define rs(p) seg[p].rson
#define cnt(p) seg[p].cnt
const int N = 1e5;
long long lastans;
int n,m,rt[N + 10],len;
long long a[N + 10],ind[N + 10];
int to[(N << 1) + 10],pre[(N << 1) + 10],first[N + 10];
inline void add(int u,int v)
{
    static int tot = 0;
    to[++tot] = v;
    pre[tot] = first[u];
    first[u] = tot;
}
struct segnode
{
    int cnt,lson,rson;
} seg[(N << 5) + 10];
int insert(int x,int tl,int tr,int p)
{
    static int tot = 0;
    int cur = ++tot;
    seg[cur] = seg[p];
    if(tl == tr)
    {
        ++cnt(cur);
        return cur;
    }
	int mid = tl + tr >> 1;
    if(x <= mid)
        ls(cur) = insert(x,tl,mid,ls(cur));
    else
        rs(cur) = insert(x,mid + 1,tr,rs(cur));
    cnt(cur) = cnt(ls(cur)) + cnt(rs(cur));
    return cur;
}
int query(int k,int tl,int tr,int x,int y,int lca,int fa_lca)
{
    if(tl == tr)
        return tl;
    int mid = tl + tr >> 1;
    int cnt = cnt(ls(x)) + cnt(ls(y)) - cnt(ls(lca)) - cnt(ls(fa_lca));
    if(k <= cnt)
        return query(k,tl,mid,ls(x),ls(y),ls(lca),ls(fa_lca));
    else
        return query(k - cnt,mid + 1,tr,rs(x),rs(y),rs(lca),rs(fa_lca));
}
int fa[N + 10],dep[N + 10],sz[N + 10],son[N + 10],top[N + 10];
int q[N + 10],head,tail;
inline int getlca(int x,int y)
{
    while(top[x] ^ top[y])
        dep[top[x]] > dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
    return dep[x] < dep[y] ? x : y;
}
int main()
{
    read(n),read(m);
    for(register int i = 1;i <= n;++i)
        read(a[i]),ind[i] = a[i];
    sort(ind + 1,ind + n + 1);
    len = unique(ind + 1,ind + n + 1) - ind - 1;
    for(register int i = 1;i <= n;++i)
        a[i] = lower_bound(ind + 1,ind + len + 1,a[i]) - ind;
    int u,v;
    for(register int i = 1;i < n;++i)
        read(u),read(v),add(u,v),add(v,u);
    rt[1] = insert(a[1],1,n,0);
    q[++tail] = dep[1] = 1;
    while(head < tail)
    {
        int p = q[++head];
        for(register int i = first[p];i;i = pre[i])
            if(to[i] ^ fa[p])
            {
                fa[to[i]] = p;
                dep[to[i]] = dep[p] + 1;
                rt[to[i]] = insert(a[to[i]],1,n,rt[p]);
                q[++tail] = to[i];
            }
    }
    for(register int i = n;i;--i)
    {
        sz[fa[q[i]]] += sz[q[i]];
        if(!son[fa[q[i]]] || sz[q[i]] > sz[son[fa[q[i]]]])
            son[fa[q[i]]] = q[i];
    }
    for(register int i = 1;i <= n;++i)
        top[q[i]] = son[fa[q[i]]] == q[i] ? top[fa[q[i]]] : q[i];
    int x,y,k,lca;
    while(m--)
    {
        read(x),read(y),read(k);
        x ^= lastans;
        lca = getlca(x,y);
        printf("%lld\n",lastans = ind[query(k,1,n,rt[x],rt[y],rt[lca],rt[fa[lca]])]);
    }
    return 0;
}
```

---

## 作者：Ireliaღ (赞：4)

**值域主席树能做的事情，可持久化Trie都能做到**

所以，我们可以用可持久化Trie来做这道题

## 解题思路

- 对于每一个树上的点，建一个版本的Trie，来存储从根到该点路径上的所有数。可见，在每一个节点上，我们需要以父节点的Trie作为原版本来添加

- 为了得到$a$、$b$路径上的所有数的信息，我们可以用$a+b-lca-lcafa$来求出。直接在这几个Trie上一起往下走路，对$size$做和差即可，基本框架和Trie求全局第$k$小一样，关于Trie求区间第$k$小可以看[这篇题解](https://www.luogu.org/blog/126376/solution-p3834)

## 程序实现

树剖+Trie

```cpp
// luogu-judger-enable-o2
#include <iostream>

using std :: cin;
using std :: cout;
using std :: swap;
using std :: cerr;
typedef unsigned int U;

const int MAXN = 1e5 + 5;

struct Edge{
    int to;
    Edge *nxt;

    Edge() {}

    Edge(int to, Edge *nxt) : to(to), nxt(nxt) {}
}epool[MAXN << 1];

Edge *head[MAXN];

Edge *NewEdge(int to, Edge *nxt) {
    static int cnt = 0;
    epool[cnt] = Edge(to, nxt);
    return &epool[cnt++];
}

void AddEdge(int u, int v) {
    head[u] = new Edge(v, head[u]);
}

int n, m;
int a[MAXN];
int fa[MAXN], dep[MAXN], son[MAXN], siz[MAXN], top[MAXN], idx[MAXN];
int idcnt;

void Dfs1(int u, int las, int depth) {
    fa[u] = las;
    dep[u] = depth;
    siz[u] = 1;
    for (Edge *e = head[u]; e; e = e->nxt) {
        int v = e->to;
        if (v == fa[u]) continue;
        Dfs1(v, u, depth + 1);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void Dfs2(int u, int topf) {
    top[u] = topf;
    idx[u] = ++idcnt;
    if (!son[u]) return;
    Dfs2(son[u], topf);
    for (Edge *e = head[u]; e; e = e->nxt) {
        int v = e->to;
        if (v == fa[u] || v == son[u]) continue;
        Dfs2(v, v);
    }
}

int Lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] > dep[top[y]]) swap(x, y);
        y = fa[top[y]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return x;
}

struct Node{
    int siz;
    Node *ch[2];
}npool[10000000];

void Update(Node *now) {
    now->siz = (now->ch[0] ? now->ch[0]->siz : 0) + (now->ch[1] ? now->ch[1]->siz : 0);
}

Node *NewNode() {
    static int cnt = 0;
    npool[cnt].siz = 0;
    npool[cnt].ch[0] = NULL;
    npool[cnt].ch[1] = NULL;
    return &npool[cnt++];
}

Node *Copy(Node *now) {
    Node *ret = NewNode();
    *ret = *now;
    return ret;
}

Node *rt[MAXN];

void Insert(Node *&now, U num, int base) {
    if (!now) now = NewNode();
    else now = Copy(now);
    if (base == 0) {
        now->siz++;
        return;
    }
    int f = (num & (1U << base - 1)) ? 1 : 0;
    Insert(now->ch[f], num, base - 1);
    Update(now);
}

U QueryKth(Node *now1, Node *now2, Node *now3, Node *now4, int base, int k, U res) {
    if (base == 0) return res;
    int ls1 = (now1 && now1->ch[0]) ? now1->ch[0]->siz : 0;
    int ls2 = (now2 && now2->ch[0]) ? now2->ch[0]->siz : 0;
    int ls3 = (now3 && now3->ch[0]) ? now3->ch[0]->siz : 0;
    int ls4 = (now4 && now4->ch[0]) ? now4->ch[0]->siz : 0;
    int ls = ls1 + ls2 - ls3 - ls4;
    if (k <= ls) return QueryKth(now1 ? now1->ch[0] : NULL, now2 ? now2->ch[0] : NULL, now3 ? now3->ch[0] : NULL, now4 ? now4->ch[0] : NULL, base - 1, k, res);
    else return QueryKth(now1 ? now1->ch[1] : NULL, now2 ? now2->ch[1] : NULL, now3 ? now3->ch[1] : NULL, now4 ? now4->ch[1] : NULL, base - 1, k - ls, res + (1U << base - 1));
}

void Print(Node *now, int base, U res) {
    if (!now) return;
    if (base == 0) cerr << res << " ";
    Print(now->ch[0], base - 1, res);
    Print(now->ch[1], base - 1, res | (1U << base - 1));
}

void Dfs3(int u) {
    rt[u] = rt[fa[u]];
    Insert(rt[u], a[u], 31);
    for (Edge *e = head[u]; e; e = e->nxt) {
        int v = e->to;
        if (v == fa[u]) continue;
        Dfs3(v);
    }
}

void Init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        cin >> x >> y;
        AddEdge(x, y);
        AddEdge(y, x);
    }
    Dfs1(1, 0, 1);
    Dfs2(1, 1);
    rt[0] = NewNode();
    Dfs3(1);
    // for (int i = 0; i <= n; i++) {
    //     cerr << i << " :\n";
    //     Print(rt[i], 31, 0);
    //     cerr << "\n";
    // }
    // cerr << "*";
}

void Work() {
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        int x, y, k;
        cin >> x >> y >> k;
        x ^= ans;
        int lca = Lca(x, y);
        ans = QueryKth(rt[x], rt[y], rt[lca], rt[fa[lca]], 31, k, 0);
        cout << ans << "\n";
    }
}

int main() {
    Init();
    Work();
    return 0;
}
```

---

## 作者：rainygame (赞：3)

本题不用树上差分，直接暴力即可。

对于路径查询，考虑树剖。对于查第 $k$ 小，考虑离散化+主席树。

但是如果像普通线段树那样做的话，会发现这里的每个区间都不是连续的，直接上主席树做不了。所以不能像模板那样直接在线段树内查询第 $k$ 小。

但是可以在主席树外面求呀！模板其实还用了“主席树上二分”这个技巧，但是现在只能把它剥掉，在外面二分。

二分需要支持查询“在 $u \rightarrow v$ 的路径上 $\le m$ 的点权有多少个”，这个就很好办了，可以直接像树剖板子那样，只需要把普通线段树改成主席树即可。具体看代码，作者语文不好说不清。

时间复杂度是 $O(n \log^3 n)$，最慢点是 $450$ ms。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100001

int n, m, u, v, k, las, cnt;
int a[MAXN], id[MAXN], b[MAXN], rt[MAXN];
int fa[MAXN], dep[MAXN], siz[MAXN], son[MAXN], top[MAXN];
vector<int> vec;
vector<int> e[MAXN];

void init(){
    for (int i(1); i<=n; ++i) vec.push_back(a[i]);
    sort(vec.begin(), vec.end());
    auto it(unique(vec.begin(), vec.end()));
    for (int i(1); i<=n; ++i) a[i] = lower_bound(vec.begin(), it, a[i])-vec.begin()+1;
}

void dfs1(int x, int f){
    siz[x] = 1;
    fa[x] = f;
    dep[x] = dep[f] + 1;
    for (auto i: e[x]){
        if (i ^ f){
            dfs1(i, x);
            siz[x] += siz[i];
            if (siz[son[x]] < siz[i]) son[x] = i;
        }
    }
}

void dfs2(int x, int tp){
    top[x] = tp;
    b[id[x]=++cnt] = a[x];
    if (son[x]) dfs2(son[x], tp);
    for (auto i: e[x]){
        if (i != son[x] && i != fa[x]) dfs2(i, i);
    }
}

namespace Seg{
    int cnt;
    struct Node{int lson, rson, sum;}tree[MAXN<<5];
    void build(int &p, int l, int r){
        p = ++cnt;
        if (l == r) return;
        int mid((l+r)>>1);
        build(tree[p].lson, l, mid);
        build(tree[p].rson, mid+1, r);
    }

    void modify(int &p, int l, int r, int k){
        tree[++cnt] = tree[p];
        ++tree[p=cnt].sum;
        if (l == r) return;
        int mid((l+r)>>1);
        if (k <= mid) modify(tree[p].lson, l, mid, k);
        else modify(tree[p].rson, mid+1, r, k);
    }

    int query(int u, int v, int l, int r, int L, int R){
        if (l >= L && r <= R) return tree[v].sum-tree[u].sum;
        int mid((l+r)>>1), res(0);
        if (L <= mid) res += query(tree[u].lson, tree[v].lson, l, mid, L, R);
        if (R > mid) res += query(tree[u].rson, tree[v].rson, mid+1, r, L, R);
        return res;
    }
    int query(int l, int r, int k){return query(rt[l-1], rt[r], 1, n, 1, k);};
}

int query(int x, int y, int k){
    int res(0);
    while (top[x] ^ top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        res += Seg::query(id[top[x]], id[x], k);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return res + Seg::query(id[x], id[y], k);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i(1); i<=n; ++i) cin >> a[i];
    for (int i(1); i<n; ++i){
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    init();
    dfs1(1, 0);
    dfs2(1, 1);

    Seg::build(rt[0], 1, n);
    for (int i(1); i<=n; ++i) Seg::modify(rt[i]=rt[i-1], 1, n, b[i]);

    while (m--){
        cin >> u >> v >> k;
        u ^= las;
        // cout << u << ' ' << v << ' ' << k << '\n';
        // assert(1 <= u && u <= n);

        int l(1), r(n), mid;
        while (l < r){
            mid = (l+r)>>1;
            // cout << mid << ' ' << query(u, v, mid) << '\n';
            if (query(u, v, mid) >= k) r = mid;
            else l = mid+1;
        }
        cout << (las = vec[l-1]) << '\n';
    }

    return 0;
}
```


---

## 作者：Refun (赞：3)

~~emmmLCA求错了然后debug了1h的丢人事迹我是不会说的~~

一开始看到这个题以为是点分，后来发现没法做。

现在做主席树的时候做到这个题了 

就想在DFS序上搞事情……就像链剖一样……然后GG了

偷看了一眼题解的第一行(划掉)发现用Root[i]表示路径[1,i]情况

然后就没什么思维难度了……

对于路径[u,v]的离散化后的值域情况
我们可以用segt[v]+segt[u]-segt[lca]-segt[father[lca]]来计算

然后就是求第k大的模板了

建树的时候有点小技巧(见[代码](http://www.cnblogs.com/refun/p/8685692.html)) 

---

## 作者：BJpers2 (赞：3)

## 你全部RE了吗？

很正常，因为我也连续全RE了6次

那re的原因呢？有很多，但要注意的是，并不只有数组开小这一种可能！由于u要……上lastans,所以很可能是你上次算错，算出的u就数组越界了。

因此对于这道题目$ WA\subset RE$

说回这道题目，以往在做主席树的题时，一般与“区间第k小”有关。在面对这类问题时，我们常会转化为$[1,l-1]$,$[1,r]$中分别有多少小于x的数（即对应线段树中第mid大的数），便可考察$[l,r]$中有多少小于x的数，从而确定第k小的范围。

把问题转移到树上，自然想到链root~u就是我们要的“前缀”，这样在链上小于x的数字个数便是

$ sum=su[ls[u]]+su[ls[v]]-su[ls[lca(u,v)]]-su[ls[fa[lca(u,v)]]]; $

考察sum是否大于k就能判定分治的方向。

```
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#define lson ls[u],l,md
#define rson rs[u],md+1,r
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(u) for(int i=hd[u],v=e[i].v;i;i=e[i].n,v=e[i].v)
using namespace std;
const int N=1001000,LG=30,M=LG*N;
struct edge{int n,v;}e[N<<1];
int n,T,u,v,k,fl,totv,cnt,tot,u1,u2,u3,u4,pre,ls[M],rs[M],su[M],rt[N];
int b[N],hd[N],va[N],d[N],fa[N],wes[N],top[N],sz[N];
void add(int u,int v){e[++fl]=(edge){hd[u],v};hd[u]=fl;}
void DEBUG(){
	cout<<"--------------"<<endl;
	cout<<"rt:";FOR(i,0,n) cout<<setw(3)<<rt[i]<<' ';cout<<endl;
	cout<<"id:";FOR(i,1,cnt) cout<<setw(3)<<i<<' ';cout<<endl;
	cout<<"ls:";FOR(i,1,cnt) cout<<setw(3)<<ls[i]<<' ';cout<<endl;
	cout<<"rs:";FOR(i,1,cnt) cout<<setw(3)<<rs[i]<<' ';cout<<endl;
	cout<<"su:";FOR(i,1,cnt) cout<<setw(3)<<su[i]<<' ';cout<<endl;
	cout<<"--------------"<<endl;
}
void bld(int &u,int l,int r){
	u=++cnt;
	if(l==r) return;
	int md=l+r>>1;
	bld(lson),bld(rson);
}
void cha(int &u,int l,int r,int v,int p,int x){
    u=++cnt;ls[u]=ls[v],rs[u]=rs[v];su[u]=su[v]+1;
	if(l==r) return;
	int md=l+r>>1;
	p<=md?cha(lson,ls[v],p,x):cha(rson,rs[v],p,x);	
}
int ask(int l,int r,int k){
	if(l==r) return l;
	int md=l+r>>1,sum;
	sum=su[ls[u1]]+su[ls[u2]]-su[ls[u3]]-su[ls[u4]];
	if(k<=sum){
		u1=ls[u1],u2=ls[u2],u3=ls[u3],u4=ls[u4];
		return ask(l,md,k);
	}
	else{
		u1=rs[u1],u2=rs[u2],u3=rs[u3],u4=rs[u4];
		return ask(md+1,r,k-sum);
	}
}
void dfs1(int u){
	sz[u]=1;
	int pp=lower_bound(b+1,b+totv+1,va[u])-b;
	cha(rt[u],1,totv,rt[fa[u]],pp,1);
	REP(u)if(v!=fa[u]){
		d[v]=d[u]+1,fa[v]=u;
		dfs1(v);sz[u]+=sz[v];
		if(sz[v]>sz[wes[u]]) wes[u]=v;
	}
}
void dfs2(int u,int TP){
	top[u]=TP;
	if(wes[u]) dfs2(wes[u],TP);
	REP(u)if(v!=wes[u] && v!=fa[u]) dfs2(v,v);
}
int asklca(int u,int v){
	for(;top[u]!=top[v];u=fa[top[u]])
		if(d[top[u]]<d[top[v]]) swap(u,v);
	if(d[u]<d[v]) swap(u,v);
	return v;
}
int main(){
	scanf("%d%d",&n,&T);
	FOR(i,1,n) scanf("%d",&va[i]),b[i]=va[i];
	FOR(i,1,n-1) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	sort(b+1,b+n+1);
	totv=unique(b+1,b+n+1)-b-1;
	bld(rt[0],1,totv);
	dfs1(1);dfs2(1,1);
	while(T--){
		scanf("%d%d%d",&u1,&u2,&k);
		u1^=pre,u3=asklca(u1,u2),u4=fa[u3];
	    u1=rt[u1],u2=rt[u2],u3=rt[u3],u4=rt[u4];
	    printf("%d\n",pre=b[ask(1,totv,k)]);
	}
}
```

---

## 作者：Hzxleo4 (赞：2)

强制在线的话就只能主席树了。


学的主席树只能处理序列， 怎么办呢？


其实dfs序也是个序列2333， 于是我们就可以对dfs序建主席树了


只不过root[i] 不是指向 root[i-1]， 而是指向了dfn[fa[re[i]]], i 是当前点的dfs序，re[i]是当前点， 前缀和也不是序列前缀和了， 是树上前缀和


```cpp
#include <cstdio>
#include <algorithm>
#define lson l, m, lch[now]
#define rson m+1, r, rch[now]
#define N 100005
using namespace std;
struct node{
    int a, b, c, n;
}d[N * 2];
int lch[N * 20], rch[N * 20], rt[N * 20], sum[N * 20], dfn[N], h[N], re[N];
int siz[N], top[N], son[N], fa[N], dep[N], w[N], tot, cnt, z, p, sz;
int pai[N], v[N];
void cr(int a, int b){
    d[++z].a = a; d[z].b = b; d[z].n = h[a]; h[a] = z;
}
void dfs1(int a){
    int i, b;
    siz[a] = 1;
    dfn[a] = ++cnt;
    re[cnt] = a;
    for(i = h[a]; i; i = d[i].n){
        b = d[i].b;
        if(b != fa[a]){
            dep[b] = dep[a] + 1;
            fa[b] = a;
            dfs1(b);
            if(siz[b] >= siz[son[a]]) son[a] = b;
            siz[a] += siz[b];
        }
    }
}
void dfs2(int a, int tp){
    int i, b;
    top[a] = tp;
    if(son[a]) dfs2(son[a], tp);
    for(i = h[a]; i; i = d[i].n){
        b = d[i].b;
        if(b != fa[a] && son[a] != b) dfs2(b, b);
    }
}
void update(int l, int r, int &now, int las, int pos){
    now = ++p;
    sum[now] = sum[las] + 1;
    if(l == r) return;
    lch[now] = lch[las];
    rch[now] = rch[las];
    int m = l+r>>1;
    if(pos <= m) update(lson, lch[las], pos);
    else update(rson, rch[las], pos);
}
int getlca(int a, int b){
    int f1 = top[a], f2 = top[b];
    while(f1 != f2){
        if(dep[f1] < dep[f2]) swap(f1, f2), swap(a, b);
        a = fa[f1], f1 = top[a];
    }
    return dep[a] < dep[b] ? a : b;
}
int query(int l, int r, int k){
    int a = l, b = r, c = getlca(a, b), d = fa[c], mid, cntt;
    a = rt[dfn[a]], b = rt[dfn[b]], c = rt[dfn[c]], d = rt[dfn[d]];
    l = 1, r = sz;
    while(l < r){
        mid = l+r>>1;
        cntt = sum[lch[a]] + sum[lch[b]] - sum[lch[c]] - sum[lch[d]];
        if(cntt >= k) r = mid, a = lch[a], b = lch[b], c = lch[c], d = lch[d];
        else l = mid+1, a = rch[a], b = rch[b], c = rch[c], d = rch[d], k -= cntt;
    }
    return v[l];
}
int main(){
    int i, j, n, m, lastans = 0, k, t, a, b, c;
    scanf("%d%d", &n, &m);
    for(i = 1; i <= n; i++) scanf("%d", &w[i]);
    for(i = 1; i < n; i++){
        scanf("%d%d", &a, &b);
        cr(a, b); cr(b, a);
    }
    dfs1(1); 
    dfs2(1, 1);
    for(i = 1; i <= n; i++) v[i] = pai[i] = w[i];
    sort(v + 1, v + i);
    sz = unique(v + 1, v + 1 + n) - (v + 1);
    for(i = 1; i <= n; i++) pai[i] = lower_bound(v + 1, v + 1 + sz, w[i]) - v;
    for(i = 1; i <= n; i++){
        t = re[i];
        update(1, sz, rt[i], rt[dfn[fa[t]]], pai[t]);
    }
    while(m--){
        scanf("%d%d%d", &a, &b, &k);
        a ^= lastans;
        lastans = query(a, b, k);
        if(m >= 1) printf("%d\n", lastans);
        else printf("%d", lastans);
    }
    return 0;
}
```

---

## 作者：破忆 (赞：2)

### 【题目大意】
在线求两点间的k小值


------------

### 【分析】
显然可以**二分**枚举k小值，然后借助某种数据结构判断链上有多少个小于等于此值的数


------------

### 【解法】

#### 【解法1】

既然和链有关，很容易想到**树剖**

平常树剖可以套个**线段树**，然后二分

二分 * 树剖 * 线段树 * n

log  * log * log * n

复杂度O（n*log2（n）^3）

#### 【解法2】

既然想到二分+线段树，然后又是区间k小值

这两个合起来就是**主席树**

可以树剖套主席树，主席树上二分

树剖 * 主席树 * n

log * log * n

复杂度O（n*log2（n）^2）

#### 【解法3】

树剖是在线数据结构，但此题并不要求修改

可以考虑用离线的方法把树剖的这层复杂度削减下来

![](https://cdn.luogu.com.cn/upload/image_hosting/9chrgvkt.png)

仔细观察，可以发现x，y之间的信息可以描述成

x+y−lca(x,y)−fa[lca(u,v)]


于是我们利用了**树上差分**的思想，这便是**LCA**

LCA可以提前构造

（ LCA + 主席树 ）* n

( log + log ) * n

复杂度O（n*log2（n））


------------


### 【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5,maxe=maxn<<1,maxt=maxn<<5;
int n,m;
int num[maxn],b[maxn],cnt;
int f[maxn][20],dep[maxn];
int tote,lnk[maxn];
int tot,rot[maxn];
int ans;
struct why{
	int x,id;
}a[maxn];
bool cmp1(why x,why y){
	return x.x<y.x;
}
bool cmp2(why x,why y){
	return x.id<y.id;
}
struct edge{
	int to,nxt;
}e[maxe];
struct ct{
	int l,r,s;
}t[maxt];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
void add_e(int x,int y){
	e[++tote]=(edge){y,lnk[x]};
	lnk[x]=tote;
}
/*以下为LCA*/
int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=19;i>=0;i--){
		if(dep[f[x][i]]>=dep[y]) x=f[x][i];
		if(x==y) return x;
	}
	for(int i=19;i>=0;i--)
	if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
/*以下为主席树*/
int build(int l,int r){
	int now=++tot,mid=l+r>>1;
	if(l<r){
		t[now].l=build(l,mid);
		t[now].r=build(mid+1,r);
	}
	return now;
}
int update(int pre,int L,int R,int x,int v){
	int now=++tot,mid=L+R>>1;
	t[now]=t[pre];
	t[now].s+=v;
	if(L<R){
		if(x<=mid) t[now].l=update(t[pre].l,L,mid,x,v);
		else t[now].r=update(t[pre].r,mid+1,R,x,v);
	}
	return now;
}
int query(int x,int y,int a,int b,int L,int R,int k){
	if(L==R){
		return L;
	}
	int mid=L+R>>1,sum=t[t[x].l].s+t[t[y].l].s-t[t[a].l].s-t[t[b].l].s;
	if(k<=sum) return query(t[x].l,t[y].l,t[a].l,t[b].l,L,mid,k);
	else return query(t[x].r,t[y].r,t[a].r,t[b].r,mid+1,R,k-sum);
}
/*以下为预处理*/
void DFS(int x,int fa){
	rot[x]=update(rot[fa],1,cnt,b[x],1);
	dep[x]=dep[fa]+1;
	for(int i=1;i<20;i++) f[x][i]=f[f[x][i-1]][i-1];
	for(int j=lnk[x];j;j=e[j].nxt){
		int y=e[j].to;
		if(y!=fa){
			f[y][0]=x;
			DFS(y,x);
		}
	}
}
int main(){
	freopen("P2633.in","r",stdin);
	freopen("P2633.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i].x=read(),a[i].id=i;
	sort(a+1,a+1+n,cmp1);
	num[++cnt]=a[1].x;
	b[a[1].id]=cnt;
	for(int i=2;i<=n;i++){
		if(a[i].x!=a[i-1].x) ++cnt;
		num[cnt]=a[i].x;
		b[a[i].id]=cnt;
	}
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		add_e(x,y),add_e(y,x);
	}
	rot[0]=build(1,cnt);
	sort(a+1,a+1+n,cmp2);
	DFS(1,0);
	while(m--){
		int x=read()^ans,y=read(),k=read();
		int lca=LCA(x,y);
		printf("%d\n",ans=num[query(rot[x],rot[y],rot[lca],rot[f[lca][0]],1,cnt,k)]);
	}
	return 0;
}
```


---

## 作者：I_AM_HelloWord (赞：1)

此题我交了20次，一共A了3次，第一次是用别人代码刷掉的，第二次是自己把自己RE了十几次的程序硬是从11:40调到15:20，饭都没吃，终于给debug出来了，就是离散化打的不对= =，可是那种离散化打发我打了好几年，都没错过，又没数据，头疼。第三次A是加了输出优化，结果还慢了4ms，(╥╯^╰╥)


推一波广告：http://blog.csdn.net/no1\_terminator/article/details/77601599


我的博客写的是入门教程，这里就简洁的讲一下吧：


考虑一个树上差分，我们需要计算u到v的路径上的第k，而我们构建的主席树都是维护u到根，v到根的路径上的，根据容斥原理的一小部分，这里我们把sum[u]+sum[v]-sum[lca[u]]-sum[father[lca[u,v]]]就是我们需要的数字的个数，与k比较一下大小，递归到左右儿子里搞一搞就行了。


参考代码（提交代码时务必手动将语言调成C++，而C++11会编译错误）：


```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
const int Logn=20;
const int N=201000;
const int INF=0x3f3f3f3f;
const int M=4100000;
struct Array{
    int x,idx;
    bool operator < (const Array &rhs) const{
        return x<rhs.x;
    }
}a[N];
struct TreeNode{
    int L,R,sum;
}T[M];
struct Edge{
    int to,next;
}e[N*2];
int b[N],head[N],root[N],fa[N][Logn+5],rank[N],dep[N];
int tn,n,m,EdgeCnt=0,T_cnt=1;
int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0' || ch>'9'){if (ch=='-')f=-1;ch=getchar();}
    while ('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
void write(int x){
    if (x<0)x=-x;
    if (x>=10)write(x/10);
    putchar(x%10+48);
}
void addedge(int u,int v){
    int p=++EdgeCnt;
    e[p].to=v;e[p].next=head[u];
    head[u]=p;
}
void insert(int &now,int val,int l=1,int r=tn){
    T[T_cnt++]=T[now];now=T_cnt-1;
    T[now].sum++;
    if (l==r)return;
    int mid=(l+r)>>1;
    if (val<=mid)insert(T[now].L,val,l,mid);
        else insert(T[now].R,val,mid+1,r);
}
int query(int a,int b,int c,int d,int k,int l=1,int r=tn){
    if (l==r)return l;
    int t=T[T[a].L].sum+T[T[b].L].sum-T[T[c].L].sum-T[T[d].L].sum;
    int mid=(l+r)>>1;
    if (k<=t)return query(T[a].L,T[b].L,T[c].L,T[d].L,k,l,mid);
        else return query(T[a].R,T[b].R,T[c].R,T[d].R,k-t,mid+1,r);
}
void dfs(int u){
    root[u]=root[fa[u][0]];
    insert(root[u],rank[u]);
    for (int p=head[u];p;p=e[p].next){
        int v=e[p].to;
        if (v!=fa[u][0]){
            fa[v][0]=u;
            dep[v]=dep[u]+1;
            dfs(v);
        }
    }
}
int LCA(int u,int v){
    if (dep[u]<dep[v])swap(u,v);
    for (int k=Logn-1;k>=0;k--)
        if (dep[fa[u][k]]>=dep[v])u=fa[u][k];
    if (u==v)return u;
    for (int k=Logn-1;k>=0;k--)
        if (fa[u][k]!=fa[v][k]){u=fa[u][k],v=fa[v][k];}
    return fa[u][0];
}
int main(){
    n=read(),m=read();
    for (int i=1;i<=n;i++){
        a[i].x=read(),a[i].idx=i;
    }
    sort(a+1,a+n+1);
    a[0].x=-INF;
    for (int i=1;i<=n;i++){
        rank[a[i].idx]=rank[a[i-1].idx]+(a[i].x!=a[i-1].x);
        b[rank[a[i].idx]]=a[i].x;
    }
    tn=rank[a[n].idx];
    for (int i=1;i<n;i++){
        int u=read(),v=read();
        addedge(u,v);addedge(v,u);
    }
    fa[1][0]=0;root[0]=0;dep[1]=1;dfs(1);
    for (int i=1;i<Logn;i++)
        for (int j=1;j<=n;j++)
            fa[j][i]=fa[fa[j][i-1]][i-1];
    int ans=0;
    for (int i=1;i<=m;i++){
        int u=read(),v=read(),k=read();
        u^=ans;
        int tt=LCA(u,v);
        int tmp=query(root[u],root[v],root[tt],root[fa[tt][0]],k);
        ans=b[tmp];
        write(ans);puts("");
    }
    return 0;
}
```

---

## 作者：kkxhh (赞：0)

看到查询$k$小我们可以想到主席树

主席树的主要思想就是通过维护一个前缀和内的信息来支持区间查询并且节约空间开销，于是我们可以维护一个树上前缀和，查询时就处理端点以及 $lca$ 处的信息就好了

代码如下：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

typedef struct node{
    int ls,rs,sum;
}node;

typedef struct edge{
    int next,to;
}edge;

edge e[200010];
node t[8000010];
int n,m,v[100010],siz,dep[100010],fa[18][100010],et,tot,head[100010],root[100010],a[100010],lasans;

inline int read(){
    int num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?0:k,c=getchar();
    while(c>='0' && c<='9') num=num*10+c-'0',c=getchar();
    return k?num:-num;
}

inline int readopt(){
    char c=getchar();
    while(c!='Q' && c!='L') c=getchar();
    return c=='Q';
}

void addegde(int u,int v){
    e[++et].to=v; e[et].next=head[u]; head[u]=et;
    e[++et].to=u; e[et].next=head[v]; head[v]=et;
}

void update(int x) {t[x].sum=t[t[x].ls].sum+t[t[x].rs].sum;}

int build(int l,int r){
    if(l==r) return ++tot;
    int cur=++tot,mid=(l+r)>>1;
    t[cur].ls=build(l,mid); t[cur].rs=build(mid+1,r);
    update(cur);
    return cur;
}

int modify(int o,int l,int r,int q){
    if(l==r) {t[++tot].sum=t[o].sum+1; return tot;}
    int mid=(l+r)>>1,cur=++tot;
    if(q<=mid) t[cur].ls=modify(t[o].ls,l,mid,q),t[cur].rs=t[o].rs;
    else t[cur].ls=t[o].ls,t[cur].rs=modify(t[o].rs,mid+1,r,q);
    update(cur);
    return cur;
}

int find(int x){
    int l=0,r=siz+1,mid;
    while(l+1<r){
        mid=(l+r)>>1;
        if(v[mid]<x) l=mid;
        else r=mid;
    }
    return r;
}

int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    int dp=dep[x]-dep[y];
    for(int i=17;i>=0;i--) if(dp>=(1<<i)) x=fa[i][x],dp-=(1<<i);
    if(x==y) return x;
    for(int i=17;i>=0;i--){
        if(!fa[i][x] || fa[i][x]==fa[i][y]) continue;
        x=fa[i][x]; y=fa[i][y];
    }
    return fa[0][x];
}

void dfs(int x,int f){
    dep[x]=dep[f]+1; fa[0][x]=f; root[x]=modify(root[f],1,siz,find(a[x]));
    for(int i=1;i<=17;i++) fa[i][x]=fa[i-1][fa[i-1][x]];
    for(int i=head[x];i;i=e[i].next) if(e[i].to!=f) dfs(e[i].to,x);
}

int query(int x,int y,int k,int l,int r){
    int cur[4],ll=lca(x,y),lw,mid;
    cur[0]=root[x]; cur[1]=root[y]; cur[2]=root[ll]; cur[3]=root[fa[0][ll]];
    while(l!=r){
        mid=(l+r)>>1;
        lw=t[t[cur[0]].ls].sum+t[t[cur[1]].ls].sum-t[t[cur[2]].ls].sum-t[t[cur[3]].ls].sum;
        if(k<=lw){
            r=mid;
            for(int i=0;i<4;i++) cur[i]=t[cur[i]].ls;
        }
        else{
            l=mid+1; k-=lw;
            for(int i=0;i<4;i++) cur[i]=t[cur[i]].rs;
        }
    }
    return v[l];
}

int main(){
    n=read(); m=read();
    for(int i=1;i<=n;i++) v[++siz]=a[i]=read();
    sort(v+1,v+1+siz);
    siz=unique(v+1,v+1+siz)-1-v;
    for(int i=1;i<n;i++) addegde(read(),read());
    root[0]=build(1,siz); dfs(1,0);
    while(m--){
        int u=read()^lasans,v=read(),k=read();
        printf("%d\n",lasans=query(u,v,k,1,siz));
    }
}

```

---

## 作者：Taduro (赞：0)

### 题意：

求静态树上第k小，强制在线。

### 做法：

刚学了主席树开始做这题，一开始以为是树剖还在想零零碎碎的区间怎么合并，但实际上用树上差分就好了。

在树上建主席树，把a结点基于fa[a]结点建树。

查询的时候用$sum[x]+sum[y]-sum[lca]-sum[fa[lca]]$判断

```c++
#include<cstdio>
#include<iostream>
#include<algorithm>
#define maxn 100001
using namespace std;
struct node{
	int h,z;
}a[maxn];
struct edge{
	int next,to;
}w[maxn<<1];
int head[maxn*25],edg,cnt,top[100010*25],sum[maxn*25];
int c[maxn],hs[maxn],size[maxn],ls[maxn*25],n,m;
int b[maxn],deep[maxn],fa[maxn],rs[maxn*25],bs[maxn];
inline bool cmp(node c,node d){
	return c.z<d.z;
}
inline void add(int x,int y){
	w[++edg].next=head[x];
	w[edg].to=y; head[x]=edg;
}
void built(int &rt,int l,int r){
	rt=++cnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	built(ls[rt],l,mid);
	built(rs[rt],mid+1,r);
}
int build(int rt,int l,int r,int p){
	int t=++cnt;
	ls[t]=ls[rt],rs[t]=rs[rt],sum[t]=sum[rt]+1;
	if (l==r) return t;  int mid=(l+r)>>1;
	if (p<=mid) ls[t]=build(ls[rt],l,mid,p);
	else rs[t]=build(rs[rt],mid+1,r,p);
	return t;
}
//void build(int rt,int &now,int l,int r,int p){
//	now=++cnt; sum[now]=sum[rt]+1;
//	if (l==r) return;
//	int mid=(l+r)>>1;
//	if (p<=mid) rs[now]=rs[rt],build(ls[rt],ls[now],l,mid,p);
//	else ls[now]=ls[rt],build(rs[rt],rs[now],mid+1,r,p);
//}
void dfs1(int x,int da){
	fa[x]=da; size[x]=1;
	bs[x]=build(bs[da],1,b[a[n].h],b[x]);
	for (int i=head[x]; i; i=w[i].next){
		if (w[i].to!=da){
			deep[w[i].to]=deep[x]+1;
			dfs1(w[i].to,x);
			size[x]+=size[w[i].to];
			if (size[w[i].to]>size[hs[x]]) hs[x]=w[i].to;
		}
	}
}
void dfs2(int x,int tp){
	top[x]=tp;
	if (hs[x]) dfs2(hs[x],tp);
	for (int i=head[x]; i; i=w[i].next)
		if (w[i].to!=fa[x]&&w[i].to!=hs[x])
			dfs2(w[i].to,w[i].to);
}
inline int lca(int x,int y){
	while (top[x]!=top[y]){
		if (deep[top[x]]<deep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if (deep[x]<deep[y]) swap(x,y);
	return y;
}
int query(int x,int y,int da,int gr,int l,int r,int k){
	if (l>=r) return l; int mid=(l+r)>>1;
	int num=sum[ls[x]]+sum[ls[y]]-sum[ls[da]]-sum[ls[gr]];
	if (num>=k) return query(ls[x],ls[y],ls[da],ls[gr],l,mid,k);
	else return query(rs[x],rs[y],rs[da],rs[gr],mid+1,r,k-num);
}
int main(){
	int last=0,x,y,z;
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++){
		scanf("%d",&a[i].z);
		a[i].h=i;
	}
	sort(a+1,a+n+1,cmp); a[0].z=-1;
	for (int i=1; i<=n; i++){
		b[a[i].h]=b[a[i-1].h];
		if (a[i].z!=a[i-1].z) b[a[i].h]++;
		c[b[a[i].h]]=a[i].z;
	}
	for (int i=1; i<=n-1; i++){
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
//	built(bs[0],1,b[a[n].h]);
	deep[1]=1; dfs1(1,0); dfs2(1,1);
	while (m--){
		scanf("%d%d%d",&x,&y,&z);
		x^=last; int lc=lca(x,y);
		last=c[query(bs[x],bs[y],bs[lc],bs[fa[lc]],1,b[a[n].h],z)];
		printf("%d\n",last);
	}
	return 0;
}
```

---

## 作者：良月澪二 (赞：0)

怎么还是没有用$vector$的呢，$sort+unique$去重多方便

老久就学了主席树，竟然漏了它，既然智推到就做了

它把主席树的区间第$k$大放到了树上

这样就不能单纯的按照序列来更新（建树）了

所以按照$dfs$的顺序更新$root$，传参传上一个节点，因为要沿用上一个节点的树

询问的时候就是树上两点距离公式的小变形

求$lca$用的是好写的树剖

刚开始疯狂$RE$，然后就开到了九千万的数组

最后只是个$zz$错误而已

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <algorithm>
#include <climits>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#define A 500010
#define B 2010

using namespace std;
typedef long long ll;
struct node {
    int next, to;
}edge[A];
struct OO {
    int l, r, w;
}tree[A << 4]; //我的原则是往大了开，这里浪费了不少
int head[A], num_edge; //可自行尝试
void add_edge(int from, int to) {
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
vector<int> v;
int n, m, a[A], b[A], x, y, z, cnt, tot, k;
int siz[A], dep[A], fa[A], son[A], top[A], tp, dfn[A], pre[A], root[A << 4];
/******************************************************/
/**********************树剖求lca***********************/
/******************************************************/
void prepare(int fr) {
    siz[fr] = 1;
    for (int i = head[fr]; i; i = edge[i].next) {
        int ca = edge[i].to;
        if (ca == fa[fr]) continue;
        fa[ca] = fr;
        dep[ca] = dep[fr] + 1;
        prepare(ca);
        siz[fr] += siz[ca];
        if (siz[ca] > siz[son[fr]]) son[fr] = ca;
    }
}
void dfs(int fr, int tp) {
    dfn[fr] = ++cnt, pre[cnt] = fr, top[fr] = tp;
    if (!son[fr]) return;
    dfs(son[fr], tp);
    for (int i = head[fr]; i; i = edge[i].next) {
        int ca = edge[i].to;
        if (ca == fa[fr] or ca == son[fr]) continue;
        dfs(ca, ca);
    }
}
int lca(int x, int y) {
    while (top[x] != top[y])
        if (dep[top[x]] >= dep[top[y]])
            x = fa[top[x]];
        else y = fa[top[y]];
    return dep[x] < dep[y] ? x : y;
}
/******************************************************/
/******************************************************/
/******************************************************/
void build(int &k, int l, int r) {
    k = ++tot;
    tree[k].w = 0;
    if (l == r) return;
    int m = (l + r) >> 1;
    build(tree[k].l, l, m);
    build(tree[k].r, m + 1, r);
}
void change(int l, int r, int &x, int &y, int k) {
    tree[++tot] = tree[y];
    tree[tot].w++;
    x = tot;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (k <= m) change(l, m, tree[x].l, tree[y].l, k);
    else change(m + 1, r, tree[x].r, tree[y].r, k);
}
int query(int t1, int t2, int t3, int t4, int l, int r, int k) {
    if (l == r) return l;
    int m = (l + r) >> 1; //看要往哪边走
    int xx = tree[tree[t2].l].w + tree[tree[t1].l].w - tree[tree[t3].l].w - tree[tree[t4].l].w;
    if (k <= xx) return query(tree[t1].l, tree[t2].l, tree[t3].l, tree[t4].l, l, m, k);
    else return query(tree[t1].r, tree[t2].r, tree[t3].r, tree[t4].r, m + 1, r, k - xx);
}
void open(int fr, int faa) { //沿用faa建自己
    change(1, v.size(), root[fr], root[faa], a[fr]);
    for (int i = head[fr]; i; i = edge[i].next) {
        int ca = edge[i].to;
        if (ca == fa[fr]) continue;
        open(ca, fr);
    }
}

int main(int argc, char const *argv[]) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    build(root[0], 1, v.size());
    for (int i = 1; i <= n; i++) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    dep[1] = 1; prepare(1); dfs(1, 1);
    open(1, 0);
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &k); x ^= ans;
        int ll = lca(x, y);
        int xx = v[query(root[x], root[y], root[ll], root[fa[ll]], 1, v.size(), k) - 1];
        printf("%d\n", xx);
        ans = xx;
    }
}
```

---

