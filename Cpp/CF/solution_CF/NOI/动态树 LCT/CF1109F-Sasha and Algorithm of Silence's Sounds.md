# Sasha and Algorithm of Silence's Sounds

## 题目描述

一天，Sasha 去公园散步。在公园里，他发现自己最喜欢的长椅被人占了，只好坐在旁边的长椅上。他坐下后，开始聆听寂静。突然，他产生了一个疑问：公园的不同地方，寂静的声音会不会不一样？事实的确如此。我们将公园划分为 $1 \times 1$ 米的方格，称之为单元格。行从上到下编号为 $1$ 到 $n$，列从左到右编号为 $1$ 到 $m$。现在，每个单元格可以用一对整数 $(x, y)$ 表示，其中 $x$ 表示行号，$y$ 表示列号。Sasha 知道，单元格 $(i, j)$ 的寂静程度为 $f_{i,j}$，所有 $f_{i,j}$ 组成了 $1$ 到 $n \cdot m$ 的一个排列。Sasha 决定统计有多少个“愉悦的寂静区间”。

我们取一个区间 $[l \ldots r]$。记 $S$ 为所有满足 $l \le f_{i,j} \le r$ 的单元格 $(i, j)$ 的集合。若对于 $S$ 中任意一对单元格，都只存在一条简单路径将它们连接起来（路径不能经过 $S$ 之外的单元格），则称区间 $[l \ldots r]$ 是“愉悦的”。换句话说，集合 $S$ 在平面上应当构成一棵树。Sasha 很快完成了这个任务，并将算法命名为“寂静之声算法”。

时光流逝，如今只剩下这个算法的传说。为了证明这个故事的真实性，你需要帮助 Sasha，统计不同的愉悦的寂静区间的数量。两个区间 $[l_1 \ldots r_1]$ 和 $[l_2 \ldots r_2]$ 被认为是不同的，当且仅当 $l_1 \neq l_2$ 或 $r_1 \neq r_2$ 或两者都不相等。

## 说明/提示

在第一个样例中，所有的寂静区间都是愉悦的。

在第二个样例中，愉悦的寂静区间如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1109F/05bdf79fe44d303126c6f8f19b3d48a216188486.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 5
1 2 3 4 5
```

### 输出

```
15```

## 样例 #2

### 输入

```
2 3
1 2 3
4 5 6
```

### 输出

```
15```

## 样例 #3

### 输入

```
4 4
4 3 2 16
1 13 14 15
5 7 8 12
6 11 9 10
```

### 输出

```
50```

# 题解

## 作者：zzxLLL (赞：5)


*3200(?)

---

考虑一颗树的性质：

- 点数减边数等于 $1$。

- 没有环。

当一张图满足第二点，那么其点数减边数大于等于 $1$。

回到本题，考虑对 $l$ 扫描线。对于一个 $l$，找到一个最大的 $r$，使得 $[l, r]$ 构成的连通块不形成环。

这个显然可以 LCT + 双指针解决，因为对于 $l < l' \leq r$，若 $[l, r]$ 满足第二点，那么 $[l', r]$ 一定满足。

然后就是统计多少个 $x \in [l, r]$，使得 $[l, x]$ 构成的图，点数减边数等于 $1$。

这个可以用线段树解决：对于每个叶子节点 $[i, i]$，记录 $[l, i]$ 构成的图的点数 - 边数，还要支持询问有多少个 $1$。注意到对于任意叶子节点其值都不小于 $1$，故问题转化为求最小值及其个数。

当 $l \gets l + 1$ 时，只需要在线段树上删除这个点和这个点所连边的影响即可。

[Code](https://codeforces.com/contest/1109/submission/224556589)

---

## 作者：Regimes (赞：3)

## 标签：

$LCT$ , 线段树，$Two \ point$

## 来源：

$CF1109F$

## 题意：

给定一个$n*m$的网格。每个格子有一个点权$f_{ij}$,有多

少个连续的值域使得这些点所带表的连通块形成一棵树。

求方案数。($n \leq 2000 , m \leq2000$ , $nm\leq 200000$)

# $solution：$

我们考虑形成一棵树，首先一定不会形成环，由于包括一个

会形成环的区间也一定会有环。所以显然这是满足单调性

的，这里我们可以用$Two \ point$来维护，对于每个左端

点，找到一个最大的右端点，使得其满足条件。对于每次连

边和断边，我们可以用$LCT$维护。于是接下来的问题变成了

要判断对于一个左端点$l$，有多少个右端点$r$满足边数$m=r-l$

也就是点数减$1$。所以我们可以用线段树维护点数$-$边数为$1$

的个数，就是答案。

```cpp

#include<bits/stdc++.h>
using namespace std ;
struct LCT{
    #define ls ch[x][0]
    #define rs ch[x][1]
    #define N 1000000
    int ch[N][3] , fa[N] , turn[N] ;
    int Get(int x){ return ch[fa[x]][1] == x ; }
    int nroot(int x){ return ch[fa[x]][1] == x || ch[fa[x]][0] == x ; }
    void pushr(int x){ if( !x ) return ; swap( ls , rs ) ; turn[x] ^= 1 ;}
    void pushdown(int x){ if( turn[x] ){ pushr( ls ) , pushr( rs ) ; turn[x] = 0 ; } }
    void pushall(int x){ if( nroot(x) ) pushall( fa[x] ) ; pushdown( x ) ; }
    void rotate(int x){
        int y = fa[x] , z = fa[y] , w = Get( x ) ;
        if( nroot( y ) ) ch[z][ch[z][1] == y] = x ;
        ch[y][w] = ch[x][w ^ 1] ;
        if( ch[y][w] ) fa[ch[y][w]] = y ;
        ch[x][w ^ 1] = y ;
        fa[y] = x ; fa[x] = z ;
    }
    void splay(int x){
        pushall( x ) ;
        while( nroot( x ) ){
            int y = fa[x] ;
            if( nroot( y ) )
                Get(x) ^ Get(y)?rotate( x ):rotate( y ) ;
            rotate( x ) ;
        }
    }
    void access(int x){
        for(int y = 0 ; x ; x = fa[y = x] ){
            splay( x ) ; rs = y ; 
        }
    }
    int findroot(int x){
        access( x ) ; splay( x ) ;
        while( ls ) x = ls ;
        splay( x ) ; return x ;
    }
    void makeroot(int x){
        access( x ) ; splay( x ) ;
        pushr( x ) ; return ;
    }
    int link(int x , int y){
        makeroot( x ) ;
        if( findroot( y ) == x ) return false ;
        fa[x] = y ; return true ;
    }
    void cut(int x , int y){
        makeroot( x ) ;
        if( findroot( y ) == x && fa[y] == x && !ch[y][0] ){
            fa[y] = ch[x][1] = 0 ;
        } return ;
    }
}T;
struct segment_tree{
    #define ls x<<1
    #define rs x<<1|1
    #define N 1000000
    int Min[4*N] , Num[4*N] , lazy[4*N] ;
    void pushdown(int x){
        if( lazy[x] ){
            lazy[ls] += lazy[x] ;
            lazy[rs] += lazy[x] ;
            Min[ls] += lazy[x] , Min[rs] += lazy[x] ;
            lazy[x] = 0 ;
        }
    }
    void pushup(int x){
        if( Min[ls] < Min[rs] ) Min[x] = Min[ls] , Num[x] = Num[ls] ;
        if( Min[ls] > Min[rs] ) Min[x] = Min[rs] , Num[x] = Num[rs] ;
        if( Min[ls] == Min[rs] ) Min[x] = Min[ls] , Num[x] = Num[ls] + Num[rs] ;
    }
    void build(int x , int l , int r){
        if( l == r ){ Min[x] = 0 , Num[x] = 1 ; return ; }
        int mid = l + r >> 1 ;
        build( ls , l , mid ) ; build( rs , mid + 1 , r ) ;
        pushup( x ) ;
    }
    void modify(int x , int l , int r , int ll , int rr , int k ){
        if( l == ll && r == rr ){
            lazy[x] += k ; Min[x] += k ;
            return ;
        }
        pushdown( x ) ;
        int mid = l + r >> 1 ;
        if( rr <= mid ) modify( ls , l , mid , ll , rr , k ) ;
        else if( ll > mid ) modify( rs , mid + 1 , r , ll , rr , k ) ;
        else modify( ls , l , mid , ll , mid , k ) , modify( rs , mid + 1 , r , mid + 1 , rr , k ) ;
        pushup( x ) ;
    }
    int query(int x , int l , int r , int ll , int rr ){
        if( l == ll && r == rr ){
            if( Min[x] == 1 ) return Num[x] ;
            else return 0 ;
        } int mid = l + r >> 1 ;
        pushdown( x ) ;
        if( rr <= mid ) return query( ls , l , mid , ll , rr ) ;
        else if( ll > mid ) return query( rs , mid + 1 , r , ll , rr ) ;
        else return query( ls , l , mid , ll , mid ) + query( rs , mid + 1 , r , mid + 1 , rr ) ;
    }
}S;
#define N 1000000
#define M 3000
#define LL long long
vector<int> V[N] ;
int dx[10] = {1 , 0 , -1 , 0 } ;
int dy[10] = {0 , 1 , 0 , -1 } ;
int n , m , w[M][M] ;
LL ans = 0 ;
int main()
{
    scanf("%d%d" , &n , &m ) ;
    for(int i = 1 ; i <= n ; i++ ) for(int j = 1 ; j <= m ; j++ ) scanf("%d" , &w[i][j] ) ;
    for(int i = 1 ; i <= n ; i++ ){
        for(int j = 1 ; j <= m ; j++ ){
            for(int d = 0 ; d < 4 ; d++ ){
                int x = i + dx[d] , y = j + dy[d] ;
                if( x < 1 || y < 1 || x > n || y > m ) continue ;
                if( w[x][y] > w[i][j] ) continue ;
                V[w[x][y]].push_back( w[i][j] ) ;
                V[w[i][j]].push_back( w[x][y] ) ;
            }
        }
    } int R = 0 ; LL t = n * m ;
    S.build( 1 , 1 , t ) ;
    for(int i = 1 ; i <= t ; i++ ){
        for(int j = R + 1 ; j <= t ; j++ ){
            int now = j , flag = 0 ;
            for(int d = 0 ; d < V[now].size() ; d++ ){
                int now1 = V[now][d] ;
                if( now1 < now && now1 >= i )
                if( !T.link( now1 , now ) ){ flag = 1 ; break ;}
            }
            for(int d = 0 ; d < V[now].size() ; d++ ) T.cut( now , V[now][d] ) ;
            if( flag == 1 ) break ;
            R = j ; int tot = 0 ;
            for(int d = 0 ; d < V[now].size() ; d++ ){
                int now1 = V[now][d] ;
                if( now1 < j && now1 >= i ) T.link( now1 , now ) ;
                if( now1 < j && now1 >= i ) tot++ ;
            }
            S.modify( 1 , 1 , t , R , R , R - i + 1 ) ;
            S.modify( 1 , 1 , t , R , t , -tot ) ;
        }
        ans += 1ll * S.query( 1 , 1 , t , i , R ) ;
        int tot = 0 ;
        for(int d = 0 ; d < V[i].size() ; d++ ){
            if( V[i][d] <= R && V[i][d] > i ){ 
                T.cut( V[i][d] , i ) ; 
                S.modify( 1 , 1 , t , V[i][d] , t , 1 ) ;
            }
        }
        S.modify( 1 , 1 , t , i , R , -1 ) ;
    }
    printf("%lld\n" , ans ) ;
    return 0 ;
}

```



---

## 作者：冷月葬T魂 (赞：2)

> 简要题意：给定一个 $n\times m$ 网格，格子中填有 $1\sim n\times m$ 的互不相同的权值。称一个区间 $[l,r]$ 合法当且仅当权值在 $[l,r]$ 内的格子形成一棵树。求有几个合法区间。$n\times m\le 2\times 10^5$。

### Do NOT use LCT!

首先数合法区间个数要想到考虑有用点对/禁止点对。

在这里“禁止点对”就是那些极小的会形成环的区间，把它们预处理出来（后面再看怎么处理），设 $i$ 向右的极大无环区间是  $[i,R_i]$。

那么扫左端点，问题就变成了类似于“对于每个 $i$，求有几个 $j\le R_i$ 满足 $[i,j]$ 形成一棵树”，隐含条件是当 $j\le R_i$ 时保证 $[i,j]$ 无环。

保证无环有什么好处呢？这样经典“点 $-$ 边”容斥就可以正确地给出这个森林的连通块数量。（如果有环，那么一棵基环树的贡献是 $0$，更复杂的图的贡献是负的，就没法计算连通块数量）

想到把贡献拆成点 $-$ 边之后，我们对每两个相邻的格子 $x$ 和 $y$ 把贡献拍到二维平面 $(x,y)$ 处 $-1$，再在二维平面上每个 $(i,i)$ 处 $+1$，那一个区间 $[l,r]$ 的连通块数就是点 $(l,r)$ 右下角的权值和，那问题就变成了求有几个位置权值为 $1$。进一步观察发现所有位置的权值都 $\ge 1$，于是扫描线，线段树维护区间最小值以及最小值个数即可。

剩下的问题是怎么找出 $i$ 往右的极长无环区间。题解区都是 LCT，很不理解。

首先发现格子越多越可能形成环，所以 $R_i$ 是关于 $i$ 单调的。这样我们就会考虑双指针和决策单调性。

双指针的话就有两种想法：一种是直接双指针，这样需要支持删除，并查集做不了，于是就出来了 LCT 的做法；另一种是过左端点重构（又称尺取/带删双指针），这样需要支持左右两部分的合并，并查集还是做不了。

那并查集能做啥？能做撤销。

把眼光转向决策单调性，从“撤销”就会自然地想到整体二分。定义函数 `solve(l,r,L,R)` 求出 $[l,r]$ 内的答案，已知它们的答案取值范围都在 $[L,R]$ 内。这个是很经典的只需要支持撤销的，递归时保证 $[r+1,L]$（可能为空，分讨）都在并查集内即可。每次求出 $mid$ 的答案，并暴力加入两个子问题 `solve(l,mid-1,L,res)` 和 `solve(mid+1,r,res,R)` 所新需要的点，递归求解。

两部分时间复杂度都为 $O(nm\log nm)$。

```cpp
#include "bits/stdc++.h"
#ifdef DEBUG
#include "PrettyDebug.hpp"
#else
#define debug(...) [](auto...){}(__VA_ARGS__)
#define debuga(...) [](auto...){}(__VA_ARGS__)
#endif
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define Fin(file) freopen(file,"r",stdin)
#define Fout(file) freopen(file,"w",stdout)
using namespace std; typedef long long ll;
constexpr int N=2e5+5;
class STree{
    int n,mn[N<<2],cnt[N<<2],tag[N<<2];
    #define k1 (k<<1)
    #define k2 (k<<1|1)
    void setg(int k,int x) { mn[k]+=x; tag[k]+=x; }
    void pushdown(int k) { if(tag[k]) setg(k1,tag[k]),setg(k2,tag[k]),tag[k]=0; }
    void update(int k) { mn[k]=min(mn[k1],mn[k2]); cnt[k]=(mn[k]==mn[k1]?cnt[k1]:0)+(mn[k]==mn[k2]?cnt[k2]:0); }
    void build(int k,int l,int r){
        if(l==r) return mn[k]=0,cnt[k]=1,void();
        int mid=(l+r)>>1; build(k1,l,mid); build(k2,mid+1,r); update(k);
    }
    void modify(int k,int l,int r,int ql,int qr,int x){
        if(ql<=l&&r<=qr) return setg(k,x),void();
        int mid=(l+r)>>1; pushdown(k);
        if(ql<=mid) modify(k1,l,mid,ql,qr,x);
        if(mid+1<=qr) modify(k2,mid+1,r,ql,qr,x);
        update(k);
    }
    int query(int k,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr) return mn[k]==1?cnt[k]:0;
        int mid=(l+r)>>1,res=0; pushdown(k);
        if(ql<=mid) res+=query(k1,l,mid,ql,qr);
        if(mid+1<=qr) res+=query(k2,mid+1,r,ql,qr);
        return res;
    }
public:
    void init(int _n) { n=_n; build(1,1,n); }
    void modify(int l,int r,int x) { modify(1,1,n,l,r,x); }
    int query(int l,int r) { return query(1,1,n,l,r); }
}T;
class DSU{
    int fa[N],siz[N]; stack<int> S;
    int getfa(int x) { return x==fa[x]?x:getfa(fa[x]); }
public:
    void init(int n) { For(i,1,n) fa[i]=i,siz[i]=1; }
    bool merge(int x,int y){
        x=getfa(x); y=getfa(y); if(x==y) { S.push(0); return false; }
        S.push(y); fa[y]=x; siz[x]+=siz[y]; return true;
    }
    void undo(){
        int y=S.top(); S.pop(); if(y==0) return;
        int x=fa[y]; siz[x]-=siz[y]; fa[y]=y;
    }
}O;
int n,m,a[N],f[N],pi[N],pj[N],vis[N]; vector<int> lis[N];
inline int ID(int i,int j) { return (i-1)*m+j; }
bool Add(int o){
    bool ok=true; vis[o]=1;
    auto work=[&](int u) { if(vis[u]) ok&=O.merge(o,u); };
    if(pi[o]>1) work(a[ID(pi[o]-1,pj[o])]);
    if(pi[o]<n) work(a[ID(pi[o]+1,pj[o])]);
    if(pj[o]>1) work(a[ID(pi[o],pj[o]-1)]);
    if(pj[o]<m) work(a[ID(pi[o],pj[o]+1)]);
    return ok;
}
void Del(int o){
    vis[o]=0;
    auto work=[&](int u) { if(vis[u]) O.undo(); };
    if(pi[o]>1) work(a[ID(pi[o]-1,pj[o])]);
    if(pi[o]<n) work(a[ID(pi[o]+1,pj[o])]);
    if(pj[o]>1) work(a[ID(pi[o],pj[o]-1)]);
    if(pj[o]<m) work(a[ID(pi[o],pj[o]+1)]);
}
void solve(int l,int r,int L,int R){ // guaranteed [r+1,L] filled
    if(l>r) return;
    debug(l,r,L,R);
    if(L==R) { For(i,l,r) f[i]=L;; return; }
    int mid=(l+r)>>1;
    // For(i,1,n*m) assert(vis[i]==(i>r&&i<=L));
    if(r<L){
        Rev(i,r,mid) Add(i);
        int res=L; while(res<R&&Add(res+1)) res++;
        if(res!=R) Del(res+1);
        f[mid]=res; debug(mid,res);
        Rev(i,res,L+1) Del(i);
        solve(l,mid-1,L,res);
        For(i,mid,r) Del(i);
        For(i,L+1,res) Add(i);
        solve(mid+1,r,res,R);
        Rev(i,res,L+1) Del(i);
    }
    else{
        int res=mid-1; while(res<R&&Add(res+1)) res++;
        if(res!=R) Del(res+1);
        f[mid]=res; debug(mid,res);
        Rev(i,res,mid) Del(i);
        For(i,mid,L) Add(i);
        solve(l,mid-1,L,res);
        Rev(i,L,mid) Del(i);
        For(i,r+1,res) Add(i);
        solve(mid+1,r,res,R);
        Rev(i,res,r+1) Del(i);
    }
}
signed main(){
    atexit([](){cerr<<"Time = "<<clock()<<" ms"<<endl;});
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m; For(i,1,n) For(j,1,m) cin>>a[ID(i,j)],pi[a[ID(i,j)]]=i,pj[a[ID(i,j)]]=j;
    For(i,1,n) For(j,1,m-1) { int x=a[ID(i,j)],y=a[ID(i,j+1)]; lis[min(x,y)].push_back(max(x,y)); }
    For(i,1,n-1) For(j,1,m) { int x=a[ID(i,j)],y=a[ID(i+1,j)]; lis[min(x,y)].push_back(max(x,y)); }
    O.init(n*m); solve(1,n*m,1,n*m); debuga(f,1,n*m);
    T.init(n*m); ll ans=0;
    Rev(i,n*m,1){
        T.modify(i,n*m,1); for(int x:lis[i]) T.modify(x,n*m,-1);
        ans+=T.query(i,f[i]);
    }
    cout<<ans<<'\n';
    return 0;
}

// CONTINUE, NON-STOPPING, FOR CHARLIEY
// START TYPING IF YOU DON'T KNOW WHAT TO DO
// STOP TYPING IF YOU DON'T KNOW WHAT YOU'RE DOING

// Started Coding On: March 13 Wed, 15 : 07 : 36
```

---

## 作者：hhhqx (赞：1)

不使用 LCT 的做法。

3.68 KB 的代码，非常好写。

最慢的点 609 ms。

无耻求赞 QwQ

### [CF1109F - Sasha and Algorithm of Silence's Sounds](https://www.luogu.com.cn/problem/CF1109F)
判断是否是树，只需要判断无环且联通。

无环是有单调性的，对每个 $i$ 求出最大 $z_i$ 满足 $[i,z_i]$ 无环。

假设已知 $z_i$，如何求 $[i,z_i]$ 中多少 $j$ 满足 $[i,j]$ 联通？

- 既然已经无环了，判联通转为判是否 $点数 - 边数 = 1$。
- 从小到大枚举 $i$。维护一颗线段树，每个位置 $j$ 的权值就是 $[i,j]$ 的 $点数 - 边数$，每个节点维护最小值和最小值出现次数。
- 查询就是查询 $[i,z_i]$，问题是每次 $i$ 加一如何修改线段树，这是简单的，不解释了。

如何求 $z_i$？

- 显然有单调性 $z_i \le z_{i+1}$。
- 如果双指针，发现很难支持删除，可以考虑撤销，不过这和线段树分治也没啥关系啊？考虑**整体二分**。
- $S(l,r,L,R)$ 表示 $z_L,z_{L+1},\cdots,z_R$ 都在 $[l,r]$ 内。
- 需要找到一个 $pos$ 满足 $z_L,z_{L+1},\cdots,z_{pos}$ 都在 $[l,mid]$ 内且 $z_{pos+1},z_{pos+2},\cdots,z_{R}$ 都在 $[mid + 1,r]$ 内：
	- 转为求最小的 $p$ 满足 $[p,mid+1],[p+1,mid+1],\cdots,[R,mid+1]$ 这几个区间组成的图都无环。 
	- 把 $[R+1,mid+1]$ 并查集建出来，并判断是否有环。
	- 然后从 $p=R$ 开始不断减。
- 递归下去。

提交记录：[Link](https://codeforces.com/contest/1109/submission/306176017)。

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using PII = pair<int, int>;
using PIP = pair<int, PII>;

const int MAXN = 2e5 + 3, inf = 1e9;
const int dx[5] = {1, 0, -1, 0};
const int dy[5] = {0, 1, 0, -1};

int H, W, n, a[2002][2002];
int z[MAXN];
vector<int> eg[MAXN];

struct SGT{
  PII tr[MAXN * 4];
  int lz[MAXN * 4];
  inline PII Merge(PII x, PII y){
    if(x.first == y.first) return {x.first, x.second + y.second};
    return min(x, y);
  }
  inline void Push(int x, int w){
    tr[x].first += w, lz[x] += w;
  }
  inline void Down(int x){
    Push(x * 2, lz[x]), Push(x * 2 + 1, lz[x]), lz[x] = 0;
  }
  void Update(int i, int l, int r, int L, int R, int w){
    if(L <= l && r <= R){
      if(w != inf) tr[i] = {w, 1};
      else Push(i, 1);
      return;
    }
    int mid = (l + r) >> 1;
    Down(i);
    if(L <= mid) Update(i * 2, l, mid, L, R, w);
    if(mid + 1 <= R) Update(i * 2 + 1, mid + 1, r, L, R, w);
    tr[i] = Merge(tr[i * 2], tr[i * 2 + 1]);
  }
  void Query(int i, int l, int r, int L, int R){
    if(L <= l && r <= R){
      tr[0] = Merge(tr[0], tr[i]);
      return;
    }
    int mid = (l + r) >> 1;
    Down(i);
    if(L <= mid) Query(i * 2, l, mid, L, R);
    if(mid + 1 <= R) Query(i * 2 + 1, mid + 1, r, L, R);
  }
}sgt;

struct DSU{
	int fa[MAXN], vis[MAXN], sz[MAXN], _cl[MAXN], ring, nl, nr;
	vector<int> stk;
	vector<PIP> cl[MAXN];

	void init(){ nl = 1, nr = 0, ring = 0; for(int i = 1; i <= n; i++) vis[i] = 0, fa[i] = i, sz[i] = 1; }
	int Getf(int x){ return fa[x] == x ? x : Getf(fa[x]); }

	void Merge(int rt, int x, int y){
		x = Getf(x), y = Getf(y);
		if(x == y){
			ring++, _cl[rt]++;
			return;
		}
		if(sz[x] > sz[y]) swap(x, y);
		cl[rt].push_back({x, {sz[x], fa[x]}}), cl[rt].push_back({y, {sz[y], fa[y]}});
		fa[x] = y, sz[y] += sz[x];
	}
	void Update(int x){
    (x < nl ? nl-- : nr++);
		vis[x] = 1, stk.push_back(x);
		for(int nxt : eg[x]) if(vis[nxt]) Merge(x, x, nxt);
	}
	void To(int l, int r){
		while(!stk.empty() && (nl < l || nr > r)){
			(stk.back() == nl ? nl++ : nr--);
			for(PIP e : cl[stk.back()]) sz[e.first] = e.second.first, fa[e.first] = e.second.second;
			vis[stk.back()] = 0, ring -= _cl[stk.back()], _cl[stk.back()] = 0, cl[stk.back()].clear(), stk.pop_back();
		}
		if(l > r){
		  nl = 1, nr = 0;
		  return;
    }
		if(nl > nr) nl = r, nr = r - 1;
		for(int i = nl - 1; i >= l; i--) Update(i);
		for(int i = nr + 1; i <= r; i++) Update(i);
		nl = l, nr = r;
	}
}dsu;

void Solve(int l, int r, int L, int R){
	if(L > R) return;
	if(l == r){
		for(int i = L; i <= R; i++) z[i] = l;
		return;
	}
	int mid = (l + r) >> 1, pos = min(R + 1, mid + 2);
	dsu.To(pos, mid + 1);
	while(pos - 1 >= L){
		pos--;
		dsu.Update(pos);
		if(dsu.ring > 0){
			pos++;
			break;
		}
	}
	Solve(l, mid, L, pos - 1), Solve(mid + 1, r, pos, R);
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> H >> W, n = H * W;
	for(int i = 1; i <= H; i++){
		for(int j = 1; j <= W; j++){
			cin >> a[i][j];
		}
	}
	for(int i = 1; i <= H; i++){
		for(int j = 1; j <= W; j++){
			for(int h = 0; h < 4; h++){
				int nx = i + dx[h], ny = j + dy[h];
				if(nx > 0 && ny > 0 && nx <= H && ny <= W) eg[a[i][j]].push_back(a[nx][ny]);
			}
		}
	}
	dsu.init(), Solve(1, n, 1, n);
	
	for(int i = 1, w = 0; i <= n; i++){
	  w++;
	  for(int x : eg[i]) w -= (x <= i);
	  sgt.Update(1, 1, n, i, i, w);
  }
  LL ANS = 0;
  for(int i = 1; i <= n; i++){
    sgt.tr[0] = {inf, 0}, sgt.Query(1, 1, n, i, z[i]);
    if(sgt.tr[0].first - (i - 1) == 1) ANS += sgt.tr[0].second;
    
    for(int x : eg[i]) if(x > i) sgt.Update(1, 1, n, x, n, inf); 
  }
  cout << ANS;
	return 0;
}
```

---

## 作者：__vector__ (赞：1)

第一道自己想出做法的 CF Div.1 F，记录一下它的两种维护方式。  
### 问题转化  
$n$ 个点，每个点的度数最多是 $4$。  
求有多少个点对 $(l,r)$ 满足 $1 \le l \le r \le n$，使得 $[l,r]$ 中的点构成的导出子图是一棵树。  
### 考虑合法条件。  
1. 不能存在环。
2. 边数等于点数减一。

考虑编号升序枚举右端点，想一想哪些左端点是符合要求的。  
- 仅考虑条件一  
  注意到，如果 $[l,r]$ 合法，那么 $r \ge \forall l' \gt l$，$[l',r]$ 是合法的。在右端点递增的情况下，最小的符合要求的左端点是单调不降的。  
  基于此性质，可以双指针。右端每新增一个点，就需要从左端弹出若干个点，使得加上新的边后不会形成环，此过程可以 LCT 维护。  
  整体二分同样可以完成任务。  
  至此，求出了每个右端点对应哪些符合条件一的左端点。
- 考虑条件二  
 考虑对每个点维护一个权值，代表其作为左端点时，总点数减去边数是多少。  
枚举右端点的时候使用线段树动态更新就可以。
注意到对于符合条件一的左端点，其权值必然大于等于 $1$，问题可以转化为求最小值及其出现次数。

虽然 LCT 常数巨大，但是在这道题可以吊打普通的整体二分。  

其中 LCT 维护的时间复杂度是 $O(nm \log nm)$，整体二分多一个并查集的复杂度。   

[LCT submission](https://codeforces.com/contest/1109/submission/303456762)，[整体二分 submission](https://codeforces.com/contest/1109/submission/304031080)。

---

## 作者：ywy_c_asm (赞：1)

~~定义不严谨，爆0两行泪~~

我一开始的时候觉得只要有$n-1$条边那不就是树了吗？然后就把所有边提出来去搞成区间维护的经典问题，结果写完之后发现连样例都过不去……

因为实际上树的严谨定义是由$n-1$条边构成的**连通图**……如果图不连通的话会发生一些有趣的事情：

![](https://cdn.luogu.com.cn/upload/pic/59265.png)

比如这个就有6个点，5条边，但是它有环，它还不连通……

但是你如果要加上“只统计与之连通的部分”这个限制的话那可能会非常困难，因为这个没有任何单调性之类的可言，所以我们要想办法从一些别的角度修锅。

我们发现出现这种情况的原因不仅是它不连通，还因为它有环。而**有环**这个东西是具有单调性的，因为往一个有环的图里面再加边还是有环的，所以，我们不妨就枚举$l$（如果枚举的是$r$可能会非常麻烦），右端点$r$用单调不降的双指针维护，这样就知道了$[l,r]$内的作为右端点都是无环的。$l$在往右移动的时候是要删边的（删去的一定是树边），$r$在往右移动的时候是要加边并且判断是否有环的，这个用$LCT$维护就好了。

这样的话，我们知道现在的区间里肯定是没环的，然后我们找有多少区间内的边是点数-1的就没有任何问题了。其实这个可以转化成**点数-边数=1**然后维护点数-边数，这个最小值本来就是1所以线段树维护区间最小值个数即可。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define ll long long
#define ls(_o) (_o << 1)
#define rs(_o) ((_o << 1) | 1)
#define isroot(_o) (_o != ch[fa[_o]][0] && _o != ch[fa[_o]][1])
#define opp(_o) (_o == ch[fa[_o]][1])
#define up(_o) data[_o] = data[ls(_o)] + data[rs(_o)]
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	vector<int> vec[200001];
	int v[2001][2001], lx[4] = { 1, -1, 0, 0 }, ly[4] = { 0, 0, 1, -1 };
	int ch[200001][2], fa[200001], stk[200001];
	unsigned char bj[200001];
	typedef struct _n {
	    int minn;
	    int cnt;
	    friend _n operator+(const _n &a, const _n &b) {
	        _n c;
	        c.minn = min(a.minn, b.minn);
	        c.cnt = 0;
	        if (a.minn == c.minn)
	            c.cnt = a.cnt;
	        if (b.minn == c.minn)
	            c.cnt += b.cnt;
	        return (c);
	    }
	} node;
	node data[1000001];
	int adds[1000001];
	inline void down(int tree) {
	    if (bj[tree])
	        bj[tree] = 0, bj[ch[tree][0]] ^= 1, bj[ch[tree][1]] ^= 1, swap(ch[tree][0], ch[tree][1]);
	}
	inline void pushdown(int tree) {
	    if (!adds[tree])
	        return;
	    adds[ls(tree)] += adds[tree];
	    adds[rs(tree)] += adds[tree];
	    data[ls(tree)].minn += adds[tree];
	    data[rs(tree)].minn += adds[tree];
	    adds[tree] = 0;
	}
	inline void xuan(int me) {
	    int tree = fa[me], cjr = fa[tree];
	    down(cjr);
	    down(tree);
	    down(me);
	    int op = opp(me), ls = ch[me][op ^ 1];
	    ch[tree][op] = ls;
	    fa[ls] = tree;
	    ch[me][op ^ 1] = tree;
	    if (!isroot(tree))
	        ch[cjr][opp(tree)] = me;
	    fa[tree] = me;
	    fa[me] = cjr;
	}
	inline void splay(int tree) {
	    if (isroot(tree)) {
	        down(tree);
	        return;
	    }
	    int sp = 0, tmp = tree;
	    while (!isroot(tmp)) stk[sp] = tmp, sp++, tmp = fa[tmp];
	    down(tmp);
	    while (sp) sp--, down(stk[sp]);
	    while (!isroot(tree)) {
	        int cjr = fa[tree];
	        if (!isroot(cjr))
	            xuan((opp(cjr) == opp(tree)) ? cjr : tree);
	        xuan(tree);
	    }
	}
	inline void access(int tree) {
	    splay(tree);
	    down(tree);
	    ch[tree][1] = 0;
	    while (fa[tree]) {
	        int cjr = fa[tree];
	        splay(cjr);
	        down(cjr);
	        ch[cjr][1] = tree;
	        splay(tree);
	    }
	}
	inline void makeroot(int tree) {
	    access(tree);
	    splay(tree);
	    bj[tree] ^= 1;
	}
	inline int findroot(int tree) {
	    access(tree);
	    splay(tree);
	    down(tree);
	    while (ch[tree][0]) tree = ch[tree][0], down(tree);
	    splay(tree);
	    return (tree);
	}
	inline void link(int a, int b) {
	    makeroot(a);
	    fa[a] = b;
	}
	inline void cut(int a, int b) {
	    makeroot(a);
	    access(b);
	    splay(a);
	    down(a);
	    fa[b] = ch[a][1] = 0;
	}
	node query(int rl, int rr, int l, int r, int tree) {
	    if (rl == l && rr == r)
	        return (data[tree]);
	    int mid = (l + r) >> 1;
	    pushdown(tree);
	    if (rl > mid)
	        return (query(rl, rr, mid + 1, r, rs(tree)));
	    if (rr <= mid)
	        return (query(rl, rr, l, mid, ls(tree)));
	    return (query(rl, mid, l, mid, ls(tree)) + query(mid + 1, rr, mid + 1, r, rs(tree)));
	}
	void add(int rl, int rr, int l, int r, int tree, int x) {
	    if (rl == l && rr == r) {
	        adds[tree] += x;
	        data[tree].minn += x;
	        return;
	    }
	    int mid = (l + r) >> 1;
	    pushdown(tree);
	    if (rl > mid)
	        add(rl, rr, mid + 1, r, rs(tree), x);
	    else {
	        if (rr <= mid)
	            add(rl, rr, l, mid, ls(tree), x);
	        else {
	            add(rl, mid, l, mid, ls(tree), x);
	            add(mid + 1, rr, mid + 1, r, rs(tree), x);
	        }
	    }
	    up(tree);
	}
	int links[200001];
	void build(int l, int r, int tree) {
	    if (l == r) {
	        data[tree].minn = 0;
	        data[tree].cnt = 1;
	        return;
	    }
	    int mid = (l + r) >> 1;
	    build(l, mid, ls(tree));
	    build(mid + 1, r, rs(tree));
	    up(tree);
	}
	void ywymain() {
	    int n = get(), m = get();
	    for (register int i = 1; i <= n; i++) {
	        for (register int j = 1; j <= m; j++) v[i][j] = get();
	    }
	    for (register int i = 1; i <= n; i++) {
	        for (register int j = 1; j <= m; j++) {
	            for (register int k = 0; k < 4; k++) {
	                int ix = j + lx[k], iy = i + ly[k];
	                if (ix < 1 || iy < 1 || ix > m || iy > n)
	                    continue;
	                if (v[i][j] > v[iy][ix])
	                    vec[v[i][j]].push_back(v[iy][ix]), vec[v[iy][ix]].push_back(v[i][j]);
	            }
	        }
	    }
	    n *= m;
	    build(1, n, 1);
	    add(1, n, 1, n, 1, 1);
	    int ptr = 1;
	    ll ans = 0;
	    for (register int i = 1; i <= n; i++) {
	        while (ptr < n) {
	            int sp = 0;
	            for (register int j = 0; j < vec[ptr + 1].size(); j++) {
	                if (vec[ptr + 1][j] < i || vec[ptr + 1][j] > ptr + 1)
	                    continue;
	                makeroot(ptr + 1);
	                if (findroot(vec[ptr + 1][j]) == ptr + 1) {
	                    while (sp) sp--, cut(ptr + 1, links[sp]);
	                    goto s;
	                }
	                link(ptr + 1, vec[ptr + 1][j]);
	                links[sp] = vec[ptr + 1][j], sp++;
	            }
	            ptr++;
	            for (register int j = 0; j < vec[ptr].size(); j++) {
	                if (vec[ptr][j] >= i && vec[ptr][j] < ptr)
	                    add(ptr, n, 1, n, 1, -1);
	            }
	            add(ptr, n, 1, n, 1, 1);
	        }
	    s:;
	        node cjr = query(i, ptr, 1, n, 1);
	        if (cjr.minn == 1)
	            ans += cjr.cnt;
	        add(i, n, 1, n, 1, -1);
	        for (register int j = 0; j < vec[i].size(); j++) {
	            if (vec[i][j] >= i && vec[i][j] <= ptr) {
	                add(vec[i][j], n, 1, n, 1, 1);
	                cut(i, vec[i][j]);
	            }
	        }
	    }
	    cout << ans << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：Luciylove (赞：0)

很经典的 LCT 数生成树，吗？

考虑维护左端点 $l$ 的最大可以扩张到的右端点 $r$，使得不存在环，不难使用 LCT 维护连通性问题。

那么就是数 $[l, r]$ 内有多少个区间 $[l, i]$ 满足区间的点在四连通性的情况下数一棵树。

考虑对于树这种特殊形态使用森林经典结论 $V - E = 1$。

那么我们就可以计算在左端点为 $l$ 的情况下，每个点连了多少条边，注意到这个是对一个后缀的区间产生贡献。

那么我们可以使用线段树维护区间加来维护 $V - E$，怎么数 $ = 1$ 呢？

根据 CF526F 的想法，借助最小值维护，发现 $V - E = 1$ 的时候是左式最小值，可以维护最小值个数。

然后就做完了。

[Implement](https://codeforces.com/contest/1109/submission/236604774)

---

## 作者：SrsgPrince_ (赞：0)

# CodeForces CF1109F Sasha and Algorithm of Silence's Sounds Solution

题面传送门：[CodeForces CF1109F Sasha and Algorithm of Silence's Sounds(Luogu)](https://www.luogu.com.cn/problem/CF1109F)。

CodeForces 题面传送门：[CodeForces CF1109F Sasha and Algorithm of Silence's Sounds(CodeForces)](https://codeforces.com/problemset/problem/1109/F)。

推荐在我的 [博客](https://www.luogu.com.cn/blog/fy123333/CodeForcesCF1109FSolution) 中查看。

## 题目分析 Hint

题目如下：

给定一个 $n \times m$ 的网格，每个格子上有一个权值 $f_{i,j}$，保证 $f_{i,j}$ 构成一个 $1 \sim nm$ 的排列。问有多少区间满足这个权值在区间的格子构成的连通块是一棵树。

数据范围：$1 \leq n,m \leq 2 \times 10^3, 1 \leq nm \leq 2 \times 10^5$。

首先因为连通块是一棵树，所以一个可能会形成环的区间也一定会有环，这满足单调性，于是我们可以用双指针来维护。加边删边用 LCT 维护，答案（构成树的子区间个数的维护）用线段树维护（这两点具体思路里会讲）。

## 思路 Solution

双指针做法是枚举区间左端点 $l$，固定之后然后右端点 $r$ 用单调不降的双指针维护对应的树的状态，找到一个满足条件最大的右端点，那么就可以使得 $[l,r]$ 区间作为右端点无环，并且统计区间最小值数量。注意在指针移动的时候需要动态加边删边，并判断是否有环，用 LCT 维护，具体来说，当左端点移动时，分别修改不断开边，断开一条或多条边时的答案，使用线段树维护这三种操作，询问时根据树的定义统计点数与边数之差为 $1$ 的子区间（就是能构成树的子区间的个数），相加得到最终答案。

接下来给出代码。

```cpp
const int maxn=1e6+10;
const int maxm=3e3+10;
int n,m,w[maxm][maxm];
long long res=0;
int dx[10]={1,0,-1,0},dy[10]={0,1,0,-1};
vector<int>vct[maxn];
struct LinkCutTree{
    int chd[maxn][3],fa[maxn],rev[maxn];
    inline int nRoot(register int x){
        return chd[fa[x]][0]==x||chd[fa[x]][1]==x;
    }
    inline void reverse(register int x){
        if(!x)
            return;
        swap(chd[x][0],chd[x][1]);
        rev[x]^=1;
    }
    inline void pushDown(register int x){
        if(rev[x]){
            reverse(chd[x][0]);
            reverse(chd[x][1]);
            rev[x]=0;
        }
    }
    inline void pushAll(register int x){
        if(nRoot(x))
            pushAll(fa[x]);
        pushDown(x);
    }
    inline void rotate(register int x){
        register int y=fa[x],z=fa[y],k=(chd[fa[x]][1]==x);
        if(nRoot(y))
            chd[z][chd[z][1]==y]=x;
        chd[y][k]=chd[x][!k];
        if(chd[y][k])
            fa[chd[y][k]]=y;
        chd[x][!k]=y;
        fa[y]=x;
        fa[x]=z;
    }
    inline void splay(register int x){
        pushAll(x);
        while(nRoot(x)){
            register int y=fa[x];
            if(nRoot(y))
                rotate((chd[x][1]==x^chd[y][1]==y)?x:y);
            rotate(x);
        }
    }
    inline void access(register int x){
        for(register int y=0;x;x=fa[y=x]){
            splay(x);
            chd[x][1]=y;
        }
    }
    inline int findRoot(register int x){
        access(x);
        splay(x);
        while(chd[x][0])
            x=chd[x][0];
        splay(x);
        return x;
    }
    inline void makeRoot(register int x){
        access(x);
        splay(x);
        reverse(x);
    }
    inline int link(register int x,register int y){
        makeRoot(x);
        if(findRoot(y)==x)
            return false;
        fa[x]=y;
        return true;
    }
    inline void cut(register int x,register int y){
        makeRoot(x);
        if(findRoot(y)==x&&fa[y]==x&&!chd[y][0]){
            fa[y]=chd[x][1]=0;
        }
        return;
    }
}lct;
struct SegmentTree{
    int mn[maxn<<2],sum[maxn<<2],lazyTag[maxn<<2];
    inline void pushDown(register int p){
        if(lazyTag[p]){
            lazyTag[p<<1]+=lazyTag[p];
            lazyTag[p<<1|1]+=lazyTag[p];
            mn[p<<1]+=lazyTag[p];
            mn[p<<1|1]+=lazyTag[p];
            lazyTag[p]=0;
        }
    }
    inline void pushUp(register int p){
        if(mn[p<<1]<mn[p<<1|1]){
            mn[p]=mn[p<<1];
            sum[p]=sum[p<<1];
        }
        if(mn[p<<1]>mn[p<<1|1]){
            mn[p]=mn[p<<1|1];
            sum[p]=sum[p<<1|1];
        }
        if(mn[p<<1]==mn[p<<1|1]){
            mn[p]=mn[p<<1];
            sum[p]=sum[p<<1]+sum[p<<1|1];
        }
    }
    inline void buildTree(register int p,register int lft,register int rgt){
        if(lft==rgt){
            mn[p]=0;
            sum[p]=1;
            return;
        }
        register int mid=(lft+rgt)>>1;
        buildTree(p<<1,lft,mid);
        buildTree(p<<1|1,mid+1,rgt);
        pushUp(p);
    }
    inline void update(register int p,register int lft,register int rgt,register int l,register int r,register int w){
        if(lft==l&&rgt==r){
            lazyTag[p]+=w;
            mn[p]+=w;
            return;
        }
        pushDown(p);
        register int mid=(lft+rgt)>>1;
        if(r<=mid)
            update(p<<1,lft,mid,l,r,w);
        else if(l>mid)
            update(p<<1|1,mid+1,rgt,l,r,w);
        else{
            update(p<<1,lft,mid,l,mid,w);
            update(p<<1|1,mid+1,rgt,mid+1,r,w);
        }
        pushUp(p);
    }
    inline int query(register int p,register int lft,register int rgt,register int l,register int r){
        if(lft==l&&rgt==r){
            if(mn[p]==1)
                return sum[p];
            else
                return 0;
        }
        register int mid=(lft+rgt)>>1;
        pushDown(p);
        if(r<=mid)
            return query(p<<1,lft,mid,l,r);
        else if(l>mid)
            return query(p<<1|1,mid+1,rgt,l,r);
        else
            return query(p<<1,lft,mid,l,mid)+query(p<<1|1,mid+1,rgt,mid+1,r);
    }
}sgt;
signed main(){
    quickRead(n,m);
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=m;++j)
            quickRead(w[i][j]);
    for(register int i=1;i<=n;++i){
        for(register int j=1;j<=m;++j){
            for(register int d=0,x,y;d<4;++d){
                x=i+dx[d],y=j+dy[d];
                if(x<1||y<1||x>n||y>m)continue;
                if(w[x][y]>w[i][j])continue;
                vct[w[x][y]].push_back(w[i][j]);
                vct[w[i][j]].push_back(w[x][y]);
            }
        }
    }
    register int r=0;
    register long long t=n*m;
    sgt.buildTree(1,1,t);
    for(register int i=1;i<=t;++i){
        for(register int j=r+1;j<=t;++j){
            int now=j,flag=0;
            for(auto now1:vct[now]){
                if(now1<now&&now1>=i)
                    if(!lct.link(now1,now)){
                        flag=1;
                        break;
                    }
            }
            for(auto now1:vct[now])
                lct.cut(now,now1);
            if(flag==1)
                break;
            r=j;
            register int tot=0;
            for(auto now1:vct[now]){
                if(now1<j&&now1>=i)
                    lct.link(now1,now);
                if(now1<j&&now1>=i)
                    tot++;
            }
            sgt.update(1,1,t,r,r,r-i+1);
            sgt.update(1,1,t,r,t,-tot);
        }
        res+=1ll*sgt.query(1,1,t,i,r);
        register int tot=0;
        for(auto now:vct[i]){
            if(now<=r&&now>i){
                lct.cut(now,i);
                sgt.update(1,1,t,now,t,1);
            }
        }
        sgt.update(1,1,t,i,r,-1);
    }
    quickWrite(res,'\n');
    return 0;
}
```
AC 记录：

![](https://cdn.luogu.com.cn/upload/image_hosting/ziqgre0b.png)


---

## 作者：Erotate (赞：0)

### Solutions

我们先固定左端点，然后对每一个左端点都找到可以满足条件的最大的右端点。显然这是有单调性的，因为对于一个区间如果包含了可以形成环的子区间，那这个区间也一定有环。

连边和断边可以用 LCT 解决，之后我们用线段树维护一个区间内能构成树的子区间的个数，即点数与边数之差为 $1$ 的子区间。

最后将每一种情况的答案累计起来就是最终答案。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int N=4e5+5;
const int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
struct Link_Cut_Tree{
	int ch[N][2],fa[N],tag[N];
	bool isroot(int x){
		return ch[fa[x]][1]!=x && ch[fa[x]][0]!=x;
	}
	void pushr(int x){
		if(!x) return;
		swap(ch[x][0],ch[x][1]);
		tag[x]^=1;
	}
	void push_down(int x){
		if(!tag[x]) return;
		pushr(ch[x][0]);
		pushr(ch[x][1]);
		tag[x]=0;
	}
	void push_all(int x){
		if(!isroot(x)) push_all(fa[x]);
		push_down(x);
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=(ch[y][0]==x);
		if(!isroot(y)) ch[z][ch[z][1]==y]=x;
		fa[x]=z;
		fa[y]=x,fa[ch[x][k]]=y;
		ch[y][k^1]=ch[x][k],ch[x][k]=y;
	}
	void splay(int x){
		push_all(x);
		while(!isroot(x)){
			int y=fa[x],z=fa[y];
			if(!isroot(y)) rotate((ch[y][1]==x)^(ch[z][1]==y)?x:y);
			rotate(x);
		}
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x]){
			splay(x);
			ch[x][1]=y;
		}
	}
	void makeroot(int x){
		access(x),splay(x),pushr(x);
	}
	int findroot(int x){
		access(x),splay(x);
		while(ch[x][0]) x=ch[x][0];
		splay(x);
		return x;
	}
	bool link(int x,int y){
		makeroot(x);
		if(findroot(y)==x) return 0;
		fa[x]=y;
		return 1;
	}
	void cut(int x,int y){
		makeroot(x);
		if(findroot(y)!=x || fa[y]!=x || ch[y][0]) return;
		fa[y]=ch[x][1]=0;
	}
}lct;
struct Segment_Tree{
	struct tree{
		int l,r,sum,mn,add;
	}tr[N<<2];
	void pushdown(int k){
		if(!tr[k].add) return;
		tr[ls].add+=tr[k].add,tr[rs].add+=tr[k].add;
		tr[ls].mn+=tr[k].add,tr[rs].mn+=tr[k].add;
		tr[k].add=0;
	}
	void pushup(int k){
		if(tr[ls].mn<tr[rs].mn) tr[k].mn=tr[ls].mn,tr[k].sum=tr[ls].sum;
		else if(tr[ls].mn>tr[rs].mn) tr[k].mn=tr[rs].mn,tr[k].sum=tr[rs].sum;
		else tr[k].mn=tr[ls].mn,tr[k].sum=tr[ls].sum+tr[rs].sum;
	}
	void build(int k,int l,int r){
		tr[k].l=l,tr[k].r=r;
		if(l==r){
			tr[k].mn=0,tr[k].sum=1;
			return;
		}
		int mid=l+r>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(k);
	}
	void update(int k,int l,int r,int v){
		if(tr[k].l>=l && tr[k].r<=r){
			tr[k].add+=v,tr[k].mn+=v;
			return;
		}
		pushdown(k);
		int mid=tr[k].l+tr[k].r>>1;
		if(l<=mid) update(ls,l,r,v);
		if(r>mid) update(rs,l,r,v);
		pushup(k);
	}
	int query(int k,int l,int r){
		if(tr[k].l>=l && tr[k].r<=r){
			if(tr[k].mn==1) return tr[k].sum;
			return 0;
		}
		pushdown(k);
		int mid=tr[k].l+tr[k].r>>1,res=0;
		if(l<=mid) res+=query(ls,l,r);
		if(r>mid) res+=query(rs,l,r);
		return res;
	}
}T;
vector<int>g[N];
int n,m,a[3005][3005],ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j) cin>>a[i][j];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=0;k<4;++k){
				int x=i+dx[k],y=j+dy[k];
				if(x<1 || x>n || y<1 || y>m) continue;
				if(a[x][y]>a[i][j]) continue;
				g[a[x][y]].push_back(a[i][j]);
				g[a[i][j]].push_back(a[x][y]);
			}
	int r=0,lst=n*m;
	T.build(1,1,lst);
	for(int i=1;i<=lst;++i){
		for(int j=r+1;j<=lst;++j){
			int cur=j,flg=0;
			for(int k=0;k<g[cur].size();++k){
				int tmp=g[cur][k];
				if(tmp<cur && tmp>=i && !lct.link(tmp,cur)){
					flg=1;
					break;
				}
			}
			for(int k=0;k<g[cur].size();++k) lct.cut(cur,g[cur][k]);
			if(flg) break;
			r=j;
			int eja=0;
			for(int k=0;k<g[cur].size();++k){
				int tmp=g[cur][k];
				if(tmp<j && tmp>=i) lct.link(tmp,cur);
				if(tmp<j && tmp>=i) eja++;
			}
			T.update(1,r,r,r-i+1);
			T.update(1,r,lst,-eja);
		}
		ans+=T.query(1,i,r);
		int eja=0;
		for(int j=0;j<g[i].size();++j)
			if(g[i][j]<=r && g[i][j]>i){
				lct.cut(g[i][j],i);
				T.update(1,g[i][j],lst,1);
			}
		T.update(1,i,r,-1);
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Piwry (赞：0)

# 题意

给定 $n*m$ 的网格图，每格有一个值在 $[1, n*m]$ 范围内且不重复。现问有多少个值域 $[l, r]$ 使由所有有该值域范围中的值的方格上下左右连接形成的图为一颗树。


# 一些废话

网上几篇大佬题解都是简单提一下思路就简单带过，但我这种刚学完lct想拿道比赛题试试手的蒟蒻完全不懂a（

于是下面我会详细讲下思考过程及实现，不想看我的废话的话可以看看其他两篇简洁的题解

以及因为实在看不懂网上几篇题解的代码，这里对答案的维护可能会比较繁琐（分类讨论）。谁能看懂另外几篇简化的代码是什么意思请务必告诉我！

# 解法

题目让我们求区间数，可以暴力地想到枚举 $l, r$ 。于是我们固定 $l$，可以发现若图中有环，继续增加节点（增大 $r$）环依然存在；然后又发现随着 $l$ 的增大 $r$ 是不减的：这样我们就可以有一种 $O(n)$ 的统计答案可能存在的区间的方法。

那么现在的问题就是如何检查环和维护答案（说实话我也不知道为什么这个思考方向就一定是对的...完全是看标程推出这个方向的 ）。维护图我们需要用到 LCT （维护树边，动态边操作）；而维护答案可以考虑用线段树：

我们设区间 $[1, m*n]$ 为以 **当前$l$** 为左边界时 右边界 $r$ 为对应值时的树数目（状态）。这样我们只需统计区间最小值数量，查询时若最小值非 $1$ 返回 $0$ 即可。

发现 对于$r_2=r_1+1$，$r_2$答案是可以由$r_1$递推出来的（增加一个点）。于是如何**在增大 $r$ 时对答案进行维护**就显而易见：每次增加新的点（增大 r）就判断是否合并了树并在线段树中修改对应的点的答案（程序中为了避免多次访问上一个 r 的答案直接增减了区间 $[r, m*n]$）。

当 $l$ 增大时（删除点），我们可以想到有三种情况：

1. 不断开边
2. 断开一条边
3. 断开多条边


这三种情况我们要对答案做不同的修改。注意：对于正维护的不同的线段树点状态不同（区间-状态集），可能分别对应不同的情况。体现到实现就是**对线段树的几段区间做不同的操作**。

我们记录断开的边连接的方格并将值从小到大排序，设为 $[v1, v2, v3, v4]$。可以发现：

1. 对于 $[l+1, v1-1]$，删去该点（$l$）会使树数目减少$1$
2. 对于$[v1, v2-1]$，删去该点不会有任何影响
3. 对于$[v2, v3-1]$，$[v3, v4-1]$，$[v4, m*n]$，删去该点会增加树的数目，每经过一段（状态）区间就多增加一棵树。我们可以直接用类似维护 r 的方法去修改它


![1](https://cdn.luogu.com.cn/upload/image_hosting/w8fwtla2.png)

（ $7$ 为删去的点，没有区间$-1$，$[8, 16]$不变，$[17, 18]$$+1$，$[19, m*n]$$+2$。注意维护 $l$ 时 $r$ 是不动的，即可以知道除了 $7$ 不可能有节点将 $17, 19, 8$ 分别连起来（保证无环）） 

若记录的点数目不够就修改至 $m*n$ 就可以了：

举例，只找到 v1 就仅修改 $[l+1, v1-1]$ 减一、 $[v1, m*n]$ 不修改。

# Code

代码的结构和上文分析的都差不多

几个小细节是：
1. 设置 r2 简单地避免 r 越界
2. 右移 r 时"模拟连边"以判环，若找到环断边
3. 右移 l 并维护答案时为避免操作越界（$l>r$），实际修改的区间左边界为 $[l, $

```cpp
#include <cstdio>
#include <algorithm>
using std::sort;

const int MAXN =2*1e5+50;

int c[2][MAXN], f[MAXN];
bool rev[MAXN];

inline void pushdown(int x){
	if(rev[x]){
		rev[c[0][x]] ^=1, rev[c[1][x]] ^=1;
		c[0][x] ^=c[1][x] ^=c[0][x] ^=c[1][x];
		rev[x] =0;
	}
}

inline bool isroot(int x){ return (!(c[0][f[x]] == x || c[1][f[x]] == x) || f[x] == 0/*避免未知错误*/); }

inline bool get(int x){ return c[1][f[x]] == x; }

inline void rotate(int x){
	bool r =get(x), rf =get(f[x]);
	int y =f[x], z =f[y], a =c[!r][x];
	f[x] =z; if(!isroot(y)) c[rf][z] =x;
	f[y] =x, c[!r][x] =y;
	f[a] =y, c[r][y] =a;
}

inline void pushall(int x){
	if(!isroot(x)) pushall(f[x]);
	pushdown(x);
}

inline void splay(int x){
	pushall(x);
	for(; !isroot(x); rotate(x))
		if(!isroot(f[x])) rotate((get(f[x]) == get(x)) ? f[x] : x);
}

inline void access(int x){
	for(int pre =0; x; pre =x, x =f[x]){
		splay(x);/*这里的x不一定是初始的*/
		c[1][x] =pre;
	}
}

inline void setroot(int x){
	access(x), splay(x);
	rev[x] =1;
}

inline bool connected(int x, int y){
	if(x == y) return 1;
	access(x), splay(x);
	access(y), splay(y)/*可能根splay就x，x本就是根*/;
	return f[x] != 0;
}

inline void cut(int x, int y){
	/*可能不必要地改变 x树的根*/
	setroot(x), access(y), splay(x)/*access前 x,y可能在同一splay*/;
	//if(c[1][x] != y) return 0;
	c[1][x] =f[y] =0;
}

inline void link(int x, int y){
	//if(connected(x, y)) return 0;
	setroot(x); f[x] =y;
}

int N =1, min[3*MAXN], cnt[3*MAXN], det[3*MAXN];
bool lazy[3*MAXN];

inline void pushupSeg(int v){
	if(min[v<<1] == min[(v<<1)|1]){
		min[v] =min[v<<1];
		cnt[v] =cnt[v<<1]+cnt[(v<<1)|1];
	}
	else if(min[v<<1] < min[(v<<1)|1]) min[v] =min[v<<1], cnt[v] =cnt[v<<1];
	else min[v] =min[(v<<1)|1], cnt[v] =cnt[(v<<1)|1];
}

inline void pushdownSeg(int v){
	if(lazy[v]){
		min[v<<1] +=det[v], min[(v<<1)|1] +=det[v];
		det[v<<1] +=det[v], det[(v<<1)|1] +=det[v];
		lazy[v<<1] =lazy[(v<<1)|1] =1;
		lazy[v] =0;
		det[v] =0;/**/
	}
}

inline void updata(int l, int r, int d, int v =1, int nl =1, int nr =N){
	if(l > r) return;
	if(l == nl && r == nr){
		min[v] +=d;
		det[v] +=d;
		lazy[v] =1;
		return;
	}
	pushdownSeg(v);
	int mid =(nl+nr)>>1;
	if(r <= mid) updata(l, r, d, v<<1, nl, mid);
	else if(l > mid) updata(l, r, d, (v<<1)|1, mid+1, nr);
	else updata(l, mid, d, v<<1, nl, mid), updata(mid+1, r, d, (v<<1)|1, mid+1, nr);
	pushupSeg(v);
}

inline int query(int l, int r, int v =1, int nl =1, int nr =N){
	if(l == nl && r == nr){
		//printf("[%d]\n", min[v]);
		if(min[v] != 1/*!*/) return 0;
		else return cnt[v];
	}
	pushdownSeg(v);
	int mid =(nl+nr)>>1;
	if(r <= mid) return query(l, r, v<<1, nl, mid);
	else if(l > mid) return query(l, r, (v<<1)|1, mid+1, nr);
	else return query(l, mid, v<<1, nl, mid) + query(mid+1, r, (v<<1)|1, mid+1, nr);
}

int posx[MAXN], posy[MAXN], dx[4] ={0, 1, 0, -1}, dy[4] ={1, 0, -1, 0};
int map[2000][2000], n, m;

inline int read(){
	int x =0; char cc =getchar();
	while(cc < '0' || cc > '9') cc =getchar();
	while(cc >= '0' && cc <= '9') x =(x<<3)+(x<<1)+(48^cc), cc =getchar();
	return x; 
}

inline int outmap(int x, int y){
	if(x < 0 || x >= n) return -1;
	if(y < 0 || y >= m) return -1;
	return map[x][y];
}

int main(){
	n =read(), m =read();
	while(N < n*m) N <<=1;
	for(int i =0; i < n; ++i) for(int j =0; j < m; ++j){
		map[i][j] =read();
		posx[map[i][j]] =i, posy[map[i][j]] =j;
	}
	/*preseg(SegmentTree)*/
	for(int k =1, count =N, d =1; k <= N; d +=k, k <<=1, count >>=1)
		for(int i =0; i < k; ++i)
			cnt[d+i] =count;
	long long ans =0;
	for(int l =1, r =0/*到 r为止无环*/; l <= n*m; ++l){
		for(int r2 =r+1/*避免越界*/; r2 <= n*m; ++r2){
			int lnk[4], tot =0, count =0;
			bool brek =0;
			for(int d =0; d < 4; ++d){
				int to =outmap(posx[r2]+dx[d], posy[r2]+dy[d]);
				if(to == -1 || to > r2 || to < l) continue;
				if(!connected(r2, to)) link(r2, to)/*先模拟连*/, lnk[tot++] =to, ++count;
				else{
					brek =1;
					break;/*不一定要*/
				}
			}
			if(brek){
				for(int i =0; i < tot; ++i) cut(r2, lnk[i]);
				break;
			}
			updata(r2, n*m, 1-count);
			r =r2;
		}
		ans +=query(l, r);
		int lnk[4], tot =0;
		for(int d =0; d < 4; ++d){
			int to =outmap(posx[l]+dx[d], posy[l]+dy[d]);
			if(to == -1) continue;
			if(connected(l, to)) cut(l, to), lnk[tot++] =to;
		}
		sort(lnk, lnk+tot);
		if(tot > 0) updata(l, lnk[0]-1, -1);/*l避免越界*/
		else updata(l, m*n, -1);/*!*/
		for(int i =1; i < tot; ++i){
			if(!connected(lnk[i-1], lnk[i])) updata(lnk[i], n*m, 1);
		}
	}
	printf("%lld", ans);
}
```


---

