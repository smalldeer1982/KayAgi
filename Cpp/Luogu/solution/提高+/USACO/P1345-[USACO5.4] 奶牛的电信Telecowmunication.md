# [USACO5.4] 奶牛的电信Telecowmunication

## 题目描述

农夫约翰的奶牛们喜欢通过电邮保持联系，于是她们建立了一个奶牛电脑网络，以便互相交流。这些机器用如下的方式发送电邮：如果存在一个由 $c$ 台电脑组成的序列$a_1,a_2,\cdots ,a_c$，且 $a_1$ 与 $a_2$ 相连，$a_2$ 与 $a_3$ 相连，等等。那么电脑 $a_1$ 和 $a_c$ 就可以互发电邮。

很不幸，有时候奶牛会不小心踩到电脑上，农夫约翰的车也可能碾过电脑，这台倒霉的电脑就会坏掉。这意味着这台电脑不能再发送电邮了，于是与这台电脑相关的连接也就不可用了。

有两头奶牛就想：如果我们两个不能互发电邮，至少需要坏掉多少台电脑呢？请注意，$c_1,c_2$ 不能被破坏。请编写一个程序为她们计算这个最小值。

以如下网络为例：

```plain
   1*
  /
 3 - 2*
```

这张图画的是有 $2$ 条连接的 $3$ 台电脑。我们想要在电脑 $1$ 和 $2$ 之间传送信息。电脑 $1$ 与 $3$，$2$ 与 $3$ 直接连通。如果电脑 $3$ 坏了，电脑 $1$ 与 $2$ 便不能互发信息了。

## 说明/提示

对于 $100\%$ 的数据：$1\le N \le 100$，$1\le M \le 600$。

## 样例 #1

### 输入

```
3 2 1 2
1 3
2 3```

### 输出

```
1
```

# 题解

## 作者：interestingLSY (赞：92)


#最小の割点 模板题

众所周知， "最小の割边"（也就是最小割）是要求

`为了使原点（记为S）和汇点（记为T）不连通，最少要割几条边`

那么最小の割点要怎么求？

###转化！把最小の割点转为最小の割边！

我们可以通过转化，把最小の割点转为最小の割边。假设原来的点编号为i，总共有n个点，那么我们就把每个点拆成两个点，编号分别为i和i+n。其中点i负责连接原图中连入这个点的边，点i+n负责连原图中连出这个点的边。就像下边这样：

 ![](https://cdn.luogu.com.cn/upload/pic/11779.png) 

通过这种奇怪的手♂段，我们就华丽丽的把 最小の割点 转为 最小の割边

###边权？

由于一个点只能被删一次~~（废话）~~，故点i和点i+n之间有一条边权为1的**有向边**，而原图中的边的边权则为INF

举个例子：

 ![](https://cdn.luogu.com.cn/upload/pic/12142.png) 

（黑边的边权为INF，黄边的边权为1）

###为什么要这样做？

如果一条黄色的边（就是点i和点i+n之间的边）被删了，那么所有进入这个点的边就不能和从这个点出去的边相连，就等价于这个点不存在。

###完整の代码

    
    
    
    
    
    
    
    

```cpp
    #include <bits/stdc++.h>
    #define vc vector
    #define INF ((int)(1e9))
    #define LINF ((ll)(1e18))
    #define pb push_back
    #define mp make_pair
    #define ll long long
    #define _tp template
    #define _tyn typename
    #define sint short int
    #define ull unsigned ll
    #define pii pair<int,int>
    #define uint unsigned int
    #define ms(_data) memset(_data,0,sizeof(_data))
    #define fin(_filename) freopen(_filename,"r",stdin)
    #define fout(_filename) freopen(_filename,"w",stdout)
    #define msn(_data,_num) memset(_data,_num,sizeof(_data))
    using namespace std;
    _tp<_tyn T>void mymax( T &_a , T _b ){ if( _a < _b ) _a = _b; }
    _tp<_tyn T>void mymin( T &_a , T _b ){ if( _a > _b ) _a = _b; }
    void print(int _x){printf("%d\n",_x);}
    void print(ll _x){printf("%I64d ",_x);}
    #define il inline
    il int in(){
        char c = getchar();
        int ret = 0;
        while( c < '0'  ||  c > '9' ) c = getchar();
        while( c >= '0'  &&  c <= '9' ){
            ret *= 10;
            ret += c-'0';
            c = getchar();
        }
        return ret;
    }
    il void read( int &x ){
        x = in();
    }
    il void read( int &x, int &y ){
        x = in(); y = in();
    }
    il void read( int &x1 , int &x2 , int &x3 ){
        x1 = in(); x2 = in(); x3 = in();
    }
    il void read( int &x1 , int &x2 , int &x3 , int &x4 ){
        x1 = in(); x2 = in(); x3 = in(); x4 = in();
    }
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    #define MAXN 110
    struct Edge{
        int to,cap,rev;
        Edge(){}
        Edge( int tt , int cc , int rr ){
            to = tt;
            cap = cc;
            rev = rr;
        }
    };
    int n,m,s,t;
    vc<Edge> e[MAXN<<1];
    vc<Edge> inp[MAXN<<1];
    il void addedge( int f , int t , int c ){
        inp[f].pb( Edge(t,c,inp[t].size()) );
        inp[t].pb( Edge(f,0,inp[f].size()-1) );
        e[f].pb(Edge());
        e[t].pb(Edge());
    }
    il void f5(){
        for( int i = 1 ; i <= n+n+1 ; i++ )
            for( uint j = 0 ; j < inp[i].size() ; j++ )
                e[i][j] = inp[i][j];
    }
    int lev[MAXN<<1];    //Level
    il void bfs( int st ){
        ms(lev);
        queue<int> q;
        q.push(st);
        lev[st] = 1;
        while( !q.empty() ){
            int now = q.front();
            q.pop();
            for( uint i = 0 ; i < e[now].size() ; i++ ){
                if( e[now][i].cap <= 0 ) continue;
                int v = e[now][i].to;
                if( !lev[v] ){
                    lev[v] = lev[now]+1;
                    q.push(v);
                }
            }
        }
    }
    bool vis[MAXN<<1];
    il int dfs( int pos , int flow ){
        if( pos == t ) return flow;
        for( uint i = 0 ; i < e[pos].size() ; i++ ){
            Edge x = e[pos][i];
            int u = x.to;
            if( vis[u] ) continue;
            if( x.cap <= 0 ) continue;
            if( lev[u] != lev[pos]+1 ) continue;
            vis[u] = 1;
            int tans = dfs( u , min(flow,x.cap) );
            vis[u] = 0;
            if( tans > 0 ){
                e[pos][i].cap -= tans;
                e[u][x.rev].cap += tans;
                return tans;
            }
        }
        return 0;
    }
    int ans = 0;
    int main(){
        read(n,m,s,t);
        for( int i = 1 ; i <= n ; i++ ){
            addedge(i,n+i,1);
        }
        for( int i = 1 ; i <= m ; i++ ){
            int a,b;
            read(a,b);
            addedge(a+n,b,INF);
            addedge(b+n,a,INF);
        }
        f5();
        while(1){
            bfs(s+n);
            if( !lev[t] ) break;
            ms(vis);
            int tans;
            while( ( tans = dfs(s+n,INF) ) > 0 ){
                ans += tans;
                ms(vis);
            }
            //cout << "[Tans] " << tans << endl;
        }
        printf("%d\n",ans);
        return 0;
    }
###如果对题解有不明白的地方或者感觉题解不对，一定要在“评论区”提出。
```

---

## 作者：GoldenPotato137 (赞：42)

蒟蒻博客：[QAQ](https://www.cnblogs.com/GoldenPotato/p/9131025.html)



------------

### Solution

这道题,需要一个小技巧来解决问题。

 

我相信很多像我这样接蒟蒻，看到这道题，不禁兴奋起来：“这道题是裸的割边，我会做！！！”

然后兴冲冲的打了个DINIC，交一发，80分。

所以说我们有时候还是太naive。

.

.


重新读题，会发现这题**割的不是边，是点**。~~这样还有80分，数据真水~~

 

所以说，我们需要一个割边转割点的小技巧。

我们可以考虑**“拆点”**，即把一个点拆成两个点，中间连一条边权为1的边。

**
前一个点作为“入点”，别的点连边连入这里。**

**后一个点作为“出点”，出去的边从这里出去。**

这样，只要我们**切断中间那条边，就可以等效于除去这个点**

如图
![QAQ](https://cdn.luogu.com.cn/upload/pic/20620.png)

红色的边边权为1，黑色的边边权为inf。

原点和汇点的内部边权为inf，因为显然这两个点不能删除。

题面给的边删除没意义（因为我们要删点），所以也设为inf(事实上设为1也没问题，因为删除这条边的权值可以理解为删除了一个点)

 
 .
 
 .
 
 .
 

至于怎么算割边，**可以证明割边在数值上等于最大流**（本蒟蒻不会证）

至于怎么求最大流........可以参考这个博客：[借用SYCdalao的博客](http://www.cnblogs.com/SYCstudio/p/7260613.html)

 

最后记得**双倍空间**

然后就OjbK了



------------
### Code
```cpp
//Luogu P1345 [USACO5.4]奶牛的电信Telecowmunication
//June,3rd,2018
//割边转割点
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
long long read()
{
    long long x=0,f=1; char c=getchar();
    while(!isdigit(c)){if(c=='-') f=-1; c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int N=200+10;
const int inf=0x3f3f3f3f;
struct road
{
    int to,w,rev;
    road (int A,int B,int C)
    {
        to=A,w=B,rev=C;
    }
};
vector <road> e[N];
int n,m,c1,c2,depth[N];
queue <int> dl;
bool bfs()
{
    memset(depth,0,sizeof depth);
    depth[c1]=1;
    dl.push(c1);
    while(dl.empty()==false)
    {
        int now=dl.front();
        dl.pop();
        for(int i=0;i<int(e[now].size());i++)
            if(e[now][i].w>0 and depth[e[now][i].to]==0)
            {
                depth[e[now][i].to]=depth[now]+1;
                dl.push(e[now][i].to);
            }
    }
    if(depth[c2]==0) return false;
    return true;
}
int dfs(int now,int f)
{
    if(now==c2) return f;
    int ans=0;
    for(int i=0;i<int(e[now].size());i++)
        if(e[now][i].w>0 and depth[e[now][i].to]==depth[now]+1)
        {
            int temp=dfs(e[now][i].to,min(f,e[now][i].w));
            e[now][i].w-=temp;
            e[e[now][i].to][e[now][i].rev].w+=temp;
            f-=temp,ans+=temp;
            if(f==0) break;
        }
    return ans;
}
int Dinic()
{
    int ans=0;
    while(bfs()==true)
        ans+=dfs(c1,inf);
    return ans;
}
inline void AddLine(int s,int t,int w)
{
    e[s].push_back(road(t,w,e[t].size()));
    e[t].push_back(road(s,0,e[s].size()-1));
}
int main()
{
    n=read(),m=read(),c1=read(),c2=read();
    for(int i=1;i<=n;i++) e[i].reserve(8);
    for(int i=1;i<=n;i++)
        if(i==c1 or i==c2)
            AddLine(i,i+n,inf);
        else
            AddLine(i,i+n,1);
    for(int i=1;i<=m;i++)
    {
        int s=read(),t=read();
        AddLine(s+n,t,inf);
        AddLine(t+n,s,inf);
    }
    
    printf("%d",Dinic());
    return 0;
}

```



---

## 作者：GoAway (赞：32)

这题难在建模啊

～～不知道光说怎么连边不说原因的网络流题解有什么意义～～

不难看出，这道题是求最小割点集的大小。

显然的是，对于一个点，它只能被删一次。～～废话～～

那么，对于每一个点i，我们都要复制它（设为i+n），并且从i到i+n连1的边（因为只能删一次）。（反向连0不要忘记）

```cpp
add ( i, i+n, 1 ) ; add ( i+n, i, 0 ) ;
```
然后怎么看待原图中本来就存在的边呢？它们只是有一个联通的作用，对于流量并没有限制，所以明确一点：这些边加入网络中限制应该为无限大。

假设现在要从原图中添加一条从x到y的有向边（这道题是无向边，再依下面的方法添加一个y到x的就行了）到网络中去，对于点y来说，这条边的加入不应该影响通过它的流量限制（就是前面连的那个1）发生变化，所以前面那条y到y+n的边应该接在这条边的后面，所以这条边的终点连向网络中的y，相反的，这条边应该受到x的（前面连的1）限制。因为，假设x已经被删（x到x+n满流），那么这条边再加不加都是没有变化的。所以，这条边在网络中的起点应该是x+n，这样才保证受到限制。

```cpp
add ( y+n, x, 无限大 ) ;
add ( x, y+n, 0 ) ;
add ( x+n, y, 无限大 ) ;
add ( y, x+n, 0 ) ;
```
不要忘记反向的。

最后贴一个完整的代码吧

dinic写的

```cpp
#include <bits/stdc++.h>

using namespace std ;
bool Read ( int &x, char c = getchar(), bool fg = 0 ) {
    for ( x = 0 ; !isdigit(c) ; c = getchar() ) if ( c == EOF ) return false ; else if ( c == '-' ) fg = 1 ;
    for ( ; isdigit(c) ; c = getchar() ) x = 10*x + c - '0' ;
    if (fg) x = -x ; return true ; //手写个读入不要嫌弃
}
const int maxn = 210, maxm = 3510, zhf = 1<<29 ;
int n, m, be[maxn], to[maxm], nxt[maxm], w[maxm], e = 1, dis[maxn], s, t ;

void add ( int x, int y, int z ) {
    to[++e] = y ;
    nxt[e] = be[x] ;
    be[x] = e ;
    w[e] = z ;
}

queue <int> Q ;
bool bfs() {
    memset ( dis, -1, sizeof(dis) ) ;
    int i, u, x ;
    while ( !Q.empty() ) Q.pop() ;
    Q.push(s) ;
    dis[s] = 0 ;
    while ( !Q.empty() ) {
        x = Q.front() ;
        Q.pop() ;
        if ( x == t ) return true ;
        for ( i = be[x] ; i ; i = nxt[i] ) {
            u = to[i] ;
            if ( dis[u] == -1 && w[i]>0 ) {
                dis[u] = dis[x]+1 ;
                if ( u == t ) return true ;
                Q.push(u) ;
            }
        }
    }
    return false ;    
}

int dfs ( int x, int val ) {
    int i, u, rec ;
    if ( x == t ) return val ;
    for ( i = be[x] ; i ; i = nxt[i] ) {
        u = to[i] ;
        if ( dis[u]==dis[x]+1 && w[i]>0 && (rec = dfs(u,min(val,w[i]))) ) {
            w[i] -= rec ;
            w[i^1] += rec ;
            return rec ;
        }
    }
}

int max_flow() {
    int rec = 0, u ;
    while ( bfs() ) { 
/*        for ( int i = 1 ; i <= 2*n ; i ++ )
            printf ( "dis[%d] = %d\n", i, dis[i] ) ;*/
        while (u = dfs(s,zhf))
            rec += u ;
    }
    return rec ;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen ( "P1345.in", "r", stdin ) ;
    freopen ( "P1345.out", "w", stdout ) ;
#endif
    int i, j, k, x, y, z ;
    Read(n) ; Read(m) ;
    Read(s) ; Read(t) ;
    s += n ;
    for ( i = 1 ; i <= n ; i ++ ) {
        add ( i, i+n, 1 ) ;
        add ( i+n, i, 0 ) ;
    }
    
    for ( i = 1 ; i <= m ; i ++ ) {
        Read(x) ; Read(y) ;
        add ( y+n, x, zhf ) ;
        add ( x, y+n, 0 ) ;
        add ( x+n, y, zhf ) ;
        add ( y, x+n, 0 ) ;
    }
    
    printf ( "%d\n", max_flow() ) ;
    return 0 ;
}
```

---

## 作者：天上一颗蛋 (赞：10)

## P1345 [USACO5.4]奶牛的电信Telecowmunication

题目描述

农夫约翰的奶牛们喜欢通过电邮保持联系，于是她们建立了一个奶牛电脑网络，以便互相交流。这些机器用如下的方式发送电邮：如果存在一个由c台电脑组成的序列a1,a2,...,a(c)，且a1与a2相连，a2与a3相连，等等，那么电脑a1和a(c)就可以互发电邮。

很不幸，有时候奶牛会不小心踩到电脑上，农夫约翰的车也可能碾过电脑，这台倒霉的电脑就会坏掉。这意味着这台电脑不能再发送电邮了，于是与这台电脑相关的连接也就不可用了。

有两头奶牛就想：如果我们两个不能互发电邮，至少需要坏掉多少台电脑呢？请编写一个程序为她们计算这个最小值。

以如下网络为例：

1* / 3 - 2*

这张图画的是有2条连接的3台电脑。我们想要在电脑1和2之间传送信息。电脑1与3、2与3直接连通。如果电脑3坏了，电脑1与2便不能互发信息了。

输入输出格式

输入格式：
第一行 四个由空格分隔的整数：N,M,c1,c2.N是电脑总数(1<=N<=100)，电脑由1到N编号。M是电脑之间连接的总数(1<=M<=600)。最后的两个整数c1和c2是上述两头奶牛使用的电脑编号。连接没有重复且均为双向的(即如果c1与c2相连，那么c2与c1也相连)。两台电脑之间至多有一条连接。电脑c1和c2不会直接相连。

第2到M+1行 接下来的M行中，每行包含两台直接相连的电脑的编号。

输出格式：
一个整数表示使电脑c1和c2不能互相通信需要坏掉的电脑数目的最小值。

---

# 分析

首先介绍一下最小割：

给定一个网络，若把一个边集删去之后，源点$S$与汇点$T$不再联通，那么我们称这个边集为此网络的**割**。边容量之和的最小的割成为此网络的最小割

然后有定理：最大流 = 最小割 ~~（蒟蒻不会证明）~~

分析题意可得：这题求的就是把给定两点作为源点和汇点的网络的最小割

可是这题是点被割掉而不是边，怎么办呢？我们就要用到边换点的知识了

# 点边转换

对于一个点，我们可以把它拆成 **点--边--点** 的形式，

理解：我们把每个点比作城市，边比作城市间道路，那么点权就是你进入城市要收钱，边权就是你进过路要交过路费，那么点--》边不就是在入城口和出城口之间设一条路，路费为进入城市收的钱了吗？

而在最大流类题目中，**流量（也就是边权）是遭到限制的**，所以有些地方会与路费这个比喻略有不同，具体实现如下图：

![](https://cdn.luogu.com.cn/upload/pic/17306.png)

值得注意的是：这题中网线为无向边，所以连边的时候要练反向边，具体参见代码

懂得了点边转换和最小割建模，这题就迎刃而解了

# AC代码

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int RD(){
    int out = 0,flag = 1;char c = getchar();
    while(c < '0' || c >'9'){if(c == '-')flag = -1;c = getchar();}
    while(c >= '0' && c <= '9'){out = out * 10 + c - '0';c = getchar();}
    return flag * out;
    }
const int maxn = 10019,INF = 1e9;
int num,nr,nume = 1,s,t;
int maxflow;
int head[maxn];
struct Node{int v,dis,nxt;}E[maxn << 2];
void add(int u,int v,int dis){
    E[++nume].nxt = head[u];
    E[nume].v = v;
    E[nume].dis = dis;
    head[u] = nume;
    }
int lev[maxn];
bool bfs(){
    queue<int>Q;
    while(!Q.empty())Q.pop();
    memset(lev,0,sizeof(lev));
    lev[s] = 1;
    Q.push(s);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for(int i = head[u];i;i = E[i].nxt){
            int v = E[i].v;
            if(E[i].dis && !lev[v]){
                lev[v] = lev[u] + 1;
                if(v == t)return 1;
                Q.push(v);
                }
            }
        }
    return 0;
    }
int Dinic(int u,int flow){//最大流板子
    if(u == t)return flow;
    int rest = flow,k;
    for(int i = head[u];i;i = E[i].nxt){
        int v = E[i].v;
        if(lev[v] == lev[u] + 1 && E[i].dis){
            k = Dinic(v,min(rest,E[i].dis));
            if(!k)lev[v] = 0;
            rest -= k;
            E[i].dis -= k;
            E[i ^ 1].dis += k;
            }
        }
    return flow - rest;
    }
int main(){
    num = RD();nr = RD();s = RD();t = RD();
    for(int i = 1;i <= num;i++){
        add(i,i + num,1);
        add(i + num,i,0);//点分裂，拆为边
        }
    int u,v;
    for(int i = 1;i <= nr;i++){
        u = RD();v = RD();
        add(u + num,v,INF);
        add(v,u + num,0);
        add(v + num,u,INF);//注意连反向边
        add(u,v + num,0);
        }
    s += num;
    int flow = 0;
    while(bfs()){
        while(flow = Dinic(s,INF))maxflow += flow;//跑最大流求最小割
        }
    printf("%d\n",maxflow);
    return 0;
    }
```

---

## 作者：Siyuan (赞：8)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[Luogu 1345](https://www.luogu.org/problemnew/show/P1345)

农夫约翰的奶牛们喜欢通过电邮保持联系，于是他们建立了一个奶牛电脑网络，以便互相交流。这个网络包括 $n$ 台电脑和 $m$ 个电脑之间的连接。这些电脑用如下的方式发送电邮：如果存在一个由 $c$ 台电脑组成的序列 $a_1,a_2,\dots,a_c$，且 $a_1$ 与 $a_2$ 相连，$a_2$ 与 $a_3$ 相连……那么电脑 $a_1$ 和 $a_c$ 就可以互发电邮。

很不幸，有时候某些倒霉的电脑会坏掉。说这意味着这台电脑不能再发送电邮了，于是与这台电脑相关的连接也就不可用了。

有两头奶牛就想：如果我们两个不能互发电邮，至少需要坏掉多少台电脑呢？你需要计算出这个最小值。

数据范围：$1\le n\le 100$，$1\le m\le 600$

------

## Solution

这道题和[「BalticOI 2008」Mafia](https://hydingsy.github.io/articles/problem-BalticOI-2008-Mafia/) 的本质是一样的，都是割掉一部分点，使得源点和汇点不连通，只是源点和汇点是不能割掉的。于是根据 [Mafia](https://hydingsy.github.io/articles/problem-BalticOI-2008-Mafia) 的思路，我们有一个小变化：源点为 $s_2$，汇点为 $t_1$。之后直接跑最小割就行了。

**时间复杂度**：$O(n^2m)$

------

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int N=205,M=5e3+5;
int n,m,tot=1,lnk[N],ter[M],nxt[M],val[M],dep[N],cnr[N];

int id(int x,int y) {
    return (x-1)*m+y;
}
void add(int u,int v,int w) {
    ter[++tot]=v,nxt[tot]=lnk[u],lnk[u]=tot,val[tot]=w;
}
void addedge(int u,int v,int w) {
    add(u,v,w),add(v,u,0);
}
int bfs(int s,int t) {
    memset(dep,0,sizeof(dep));
    memcpy(cnr,lnk,sizeof(lnk));
    std::queue<int> q;
    q.push(s),dep[s]=1;
    while(!q.empty()) {
        int u=q.front(); q.pop();
        for(int i=lnk[u];i;i=nxt[i]) {
            int v=ter[i];
            if(val[i]&&!dep[v]) q.push(v),dep[v]=dep[u]+1;
        }
    }
    return dep[t];
}
int dfs(int u,int t,int flow) {
    if(u==t) return flow;
    int ans=0;
    for(int i=cnr[u];i&&ans<flow;i=nxt[i]) {
        cnr[u]=i;
        int v=ter[i];
        if(val[i]&&dep[v]==dep[u]+1) {
            int x=dfs(v,t,std::min(val[i],flow-ans));
            if(x) val[i]-=x,val[i^1]+=x,ans+=x;
        }
    }
    if(ans<flow) dep[u]=-1;
    return ans;
}
int dinic(int s,int t) {
    int ans=0;
    while(bfs(s,t)) {
        int x;
        while((x=dfs(s,t,1<<30))) ans+=x;
    }
    return ans;
}
int main() {
    int s,t;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=n;++i) addedge(i,i+n,1);
    while(m--) {
        int u,v;
        scanf("%d%d",&u,&v);
        addedge(u+n,v,1<<30);
        addedge(v+n,u,1<<30);
    }
    printf("%d\n",dinic(s+n,t));
    return 0;
}
```



---

## 作者：shenbear (赞：2)

首先，这道题看着像网络流，读着像网络流，打着像网络流

那么它就是网络流

于是之间建边跑，然后居然有70，仔细一看，发现是割点而不是割边。

于是我们要转换一下：

我们用i->i+n这两边一点来代替一个点，保证从i进从i+n出。**然后我们就会发现，只要进出的权值>=1那么最小割一定就在i->i+n上为1，这样我们就成功的把割点变成了割边**

然后我们只要按照上述原则将图连起来即可：

1.i进，i+n出

2.其他容量>=1



------------
代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
int n,m;
struct edge
{
	int next,to,w;
}p[6666];
int head[555],num;
il void ad(int x,int y,int z){p[++num]=edge{head[x],y,z};head[x]=num;}
il void add(int x,int y,int z){ad(x,y,z);ad(y,x,0);}
il int qfj(int x){return ((x-1)^1)+1;}
int dep[555];
bool bfs(int s,int t)
{
	queue<int> q;
	q.push(s);
	memset(dep,-1,sizeof(dep));
	dep[s]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i;i=p[i].next)
		{
			int v=p[i].to;
			if(dep[v]==-1&&p[i].w)
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return dep[t]!=-1;
}
int dfs(int u,int t,int limit)
{
	if(u==t||!limit) return limit;
	int w,flow=0;
	for(int i=head[u];i;i=p[i].next)
	{
		int v=p[i].to;
		if(dep[v]==dep[u]+1&&(w=dfs(v,t,min(limit,p[i].w))))
		{
			flow+=w;
			p[i].w-=w;
			p[qfj(i)].w+=w;
			limit-=w;
			if(!limit) break;
		}
	}
	return flow;
}
int dinic(int s,int t)
{
	int mxfl=0;
	while(bfs(s,t)) mxfl+=dfs(s,t,1e9);
	return mxfl;
}
int ans,s,t;
int main()
{
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++)
	{
		int x,y,a,b;
		scanf("%d%d",&x,&y);
		a=x;b=y;
		if(x!=s&&x!=t) a+=n;
		if(y!=s&&y!=t) b+=n;
		add(a,y,1);add(b,x,1);//i进,i+n出
			  //其实这里只要是个>=1的容量都可以 
	//	if(x!=s&&x!=t) add(x+n,y,1),add(y+n,x,1);
	//	else add(x,y,1),add(y,x,1);
	}
	for(int i=1;i<=n;i++) if(i!=s&&i!=t) add(i,i+n,1); //转点为边 
	ans=dinic(s,t);
	cout<<ans;
	return 0;
}
```


---

## 作者：bugaile (赞：2)

题目大意$:$

给定一张图,给出源点和汇点,最少删去多少个点使两点不连通.

这个题定义上有点像网络流中的最小割,不过这个题中是点,最小割是边,只要想办法转化一下,考虑如何将点变为边.

这个时候就要用到网络流中的一个常用的技巧$:$拆点法.

我们可以将每一个点拆成入点和出点,将一个点删除,等价于将该店入点和出点之间的边删除.

如图$:$

![](https://cdn.luogu.com.cn/upload/image_hosting/3hh0cxvq.png)

而我们只要将每个点入点和出点之间的边的容量设为1,其他边的容量设为$INF$,再跑一边最大流即可,因为其他边容量均为$inf$,所以可以保证优先选出点和入点之间的边,而不会删去本来的边.

代码如下$:$

``` cpp

#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#define mian main
#define inf 0x3f3f3f3f
using namespace std;
const int N=201,M=20000;

queue<int>Q;

int n,m,s,t,depth[N],max_flow;

int tt,to[M],nex[M],w[M],head[N];

inline void add(int x,int y,int W){
	w[tt]=W;
	to[tt]=y;
	nex[tt]=head[x];
	head[x]=tt++;
	return ;
}

inline bool bfs(){//网络流模板;
	memset(depth,0,sizeof depth);
	Q=queue<int>();
	Q.push(s);
	depth[s]=1;
	while(Q.size()){
		int q=Q.front();
		Q.pop();
		for(int i=head[q],u;~i;i=nex[i])
			if(w[i]){
				u=to[i];
				if(!depth[u]){
					depth[u]=depth[q]+1;
					if(u==t)
						return true;
					Q.push(u);
				}
			}
	}
	return false;
}

int dfs(int g,int flow){
	if(g==t)
		return flow;
	int now_flow,rest=flow;
	
	for(int i=head[g],u;~i&&rest;i=nex[i]){
		u=to[i];
		if(w[i]&&depth[u]==depth[g]+1){
			now_flow=dfs(u,min(rest,w[i]));
			if(!now_flow)
				depth[u]=0;
			w[i]-=now_flow;
			w[i^1]+=now_flow;
			rest-=now_flow;
		}
	}
	
	return flow-rest;
}

inline void dinic(){
	int now_flow;
	
	while(bfs())
		while(now_flow=dfs(s,inf))
			max_flow+=now_flow;
	
	return ;
}

int mian(){
	memset(head,-1,sizeof head);
	
	cin>>n>>m>>s>>t;
	
	s+=n;//以源点的出点为真实源点,汇点入点为真实入点,
    	 //防止删到源点和汇点的出点和入点之间的边;
	
	for(int i=1;i<=n;++i)
		add(i,i+n,1),
		add(i+n,i,0);
	
	int x,y;
	
	for(int i=1;i<=m;++i)
		cin>>x>>y,
		add(x+n,y,inf),
		add(y,x+n,0),
		add(y+n,x,inf),
		add(x,y+n,0);
	
	dinic();
	
	cout<<max_flow<<endl;
	
	return 0;
}


```

---

## 作者：lizbaka (赞：2)

[这里是我的博客$OwO$](https://www.cnblogs.com/lizbaka/p/10521737.html)

# Solution

题目要求找到最小数量的若干个点，使得这些点被去掉之后，点$c_1$和$c_2$不连通。

与最小割模型十分类似，考虑转化

---

约定$(u,v,f)$表示$u$向$v$连边，流量为$f$。  
$S$为源，$T$为汇

先说模型

对于每个点$u$，将其拆成$u\times2,u\times2+1$两个点，建边$(u\times2,u\times2+1,1)$

对于原图上的每条边$(u,v)$，建边$(u\times2+1,v\times2,inf)$

最后令$S=c_1\times2+1,T=c_2\times2$，求出最小割即可

---

为什么这样建模？

首先我们割的是**点**而不是**边**，我们需要在模型中将这个决策体现出来，因此需要将点拆成一个“入点”和一个“出点”。  
去掉每个点对答案的贡献为$1$，所以入点和出点之间连一条流量为$1$的边。割掉这条边的意义即为去掉了这个点。

然后对于原图上的无向边，可以视作两条方向相反的有向边  
对于每条有向边$(u,v)$，相当于是从$u$“出来”，“进入”了$v$，所以从$u$对应的出点向$v$对应的入点连边，流量为正无穷

由于我们是从$c_1$出发到达$c_2$，所以源是$c_1$对应的出点，汇是$c_2$对应的入点

显然最小割一定只包括流量为$1$的边

# Code
```
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#define i(u) ((u)<<1)//入
#define o(u) (((u)<<1)|1)//出
using namespace std;
typedef long long ll;

template <typename T> void read(T &t)
{
	t=0;int f=0;char c=getchar();
	while(!isdigit(c)){f|=c=='-';c=getchar();}
	while(isdigit(c)){t=t*10+c-'0';c=getchar();}
	if(f)t=-t;
}

const int inf=0x3f3f3f3f;
const int maxn=1005,maxm=6005;
int n,m;
int S,T,c1,c2;
int ans;
 
struct edge
{
	int u,v,f,nxt;
}g[maxm*2];

int head[maxn],ecnt=1;
void eADD(int u,int v,int f)
{	g[++ecnt].u=u;g[ecnt].v=v;g[ecnt].f=f;g[ecnt].nxt=head[u];head[u]=ecnt;
	g[++ecnt].u=v;g[ecnt].v=u;g[ecnt].f=0;g[ecnt].nxt=head[v];head[v]=ecnt;
}

int dep[maxn];
bool BFS()
{
	queue<int> q;
	memset(dep,0,sizeof(dep));
	dep[S]=1;
	q.push(S);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();	
		for(register int i=head[u];i;i=g[i].nxt)
		{
			int v=g[i].v;
			if(!dep[v] && g[i].f)
			{
				dep[v]=dep[u]+1;
				if(v==T)return true;
				q.push(v);
			}
		}
	}
	return false;
}

int dfs(int u,int infl)
{
	if(u==T)return infl;
	int rest=infl;
	for(register int i=head[u];i && rest;i=g[i].nxt)
	{
		int v=g[i].v;
		if(dep[v]==dep[u]+1 && g[i].f)
		{
			int flow=dfs(v,min(g[i].f,rest));
			rest-=flow;
			g[i].f-=flow;
			g[i^1].f+=flow;
		}
	}
	return infl-rest;
}

int main()
{
	read(n),read(m),read(c1),read(c2);
	for(register int i=1;i<=n;++i)
		eADD(i(i),o(i),1);
	for(register int i=1;i<=m;++i)
	{
		int u,v;
		read(u),read(v);
		eADD(o(u),i(v),inf);
		eADD(o(v),i(u),inf);
	}
	S=o(c1),T=i(c2);
	while(BFS())
		ans+=dfs(S,inf);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：arfa (赞：1)

题面讲了一堆东西让我们来理解最小割。

首先 **最大流 $=$ 最小割** 没错吧。

然后发现这里是割点而不是割边。我们就可以把一个点拆成入点和出点,然后把边权套进去。这题跟 [教辅的组成](https://www.luogu.org/problemnew/show/P1231) 很像,大家可以去看我的 [$Blog$](https://www.luogu.org/blog/acking/solution-p1231)。

跑的 $ISAP$,竟然被卡到了 $20ms$ (总共)

```pascal
// luogu-judger-enable-o2
Uses math;

var
    value,reach,next:array[-1..3100] of longint;
    gap,dis,cnt:array[-1..1400] of longint;
    n,m,z,l,r,k,i,j,sum,tot,sink,source,number,maxflow:longint;

procedure add(l,r,sum:longint);
begin
    inc(tot); reach[tot]:=r; value[tot]:=sum; next[tot]:=cnt[l]; cnt[l]:=tot;
end;

function Dfs(now,flow:longint):longint;
var i,k,mindis,ret:longint;
begin
    mindis:=n-1; ret:=flow;
    if now=sink then exit(flow);
    i:=cnt[now];
    while i<>-1 do
    begin
        if value[i]>0 then
        begin
            if dis[now]=dis[reach[i]]+1 then
            begin
                k:=Dfs(reach[i],min(ret,value[i]));
                dec(value[i],k);inc(value[i xor 1],k);
                dec(ret,k);
                if dis[source]>=n then exit(flow-ret);
                if ret=0 then break;
            end;
             mindis:=min(mindis,dis[reach[i]]);
        end;
        i:=next[i];
    end;
    if ret=flow then
    begin
        dec(gap[dis[now]]);
        if gap[dis[now]]=0 then dis[source]:=n;
        dis[now]:=mindis+1;
        inc(gap[dis[now]]);
    end;
    exit(flow-ret);
end;

begin
    filldword(cnt,sizeof(cnt) div 4,maxlongint*2+1); tot:=1;
    read(n,m,source,sink);
    for i:=1 to n do begin add(i,i+n,1); add(i+n,i,0); end;
    for i:=1 to m do
    begin
        read(l,r);
        add(l+n,r,maxlongint div 843); add(r,l+n,0);
        add(r+n,l,maxlongint div 843); add(l,r+n,0);
    end;
    inc(source,n); n:=n*2+2; gap[source]:=n;
    while dis[source]<n do inc(maxflow,Dfs(source,maxlongint)); 
    writeln(maxflow); 
end.
```

---

## 作者：hncsyjc (赞：1)

先把每个点i拆成两个点，编号分别为i和i+n，把i到i+n连一条容量为1的边，然后若i到j有一条边，则连接i+n->j,i->j+n，边权为无穷大，然后求s+n到t的最大流即是答案


---

## 作者：_121017_ (赞：1)

# 思路
因为这题并不是简单的最小割，所以我们考虑拆点。

如果我们把 $a_i$ 与 $a_{i+n}$ 之间连一条容量为 $1$ 的边，入边连向 $a_i$，出边由 $a_{i+n}$ 连出会发生什么呢？这样如果我们割掉 $a_i$ 与 $a_{i+n}$ 之间的边，就起到了割点的效果。

这样我们根据最小割 $=$ 最大流定理不就可以轻松加愉快的切掉这一题了吗。
# code
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000005
#define INF 0x7f7f7f7f7f7f7f7f
using namespace std;
int cnt=1,head[N],to[N],w[N],next[N],deep[N];
int maxflow,used,gap[N];
int n,m,s,t;
queue<int>q;
void add(int u,int v,int c){
	cnt++;
	to[cnt]=v;
	w[cnt]=c;
	next[cnt]=head[u];
	head[u]=cnt;
}
void bfs(){
	memset(gap,0,sizeof(gap));
	memset(deep,-1,sizeof(deep));
	q.push(t);
	deep[t]=0;
	gap[0]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=next[i]){
			int v=to[i];
			if(deep[v]==-1){
				deep[v]=deep[u]+1;
				gap[deep[v]]++;
				q.push(v);
			}
		}
	}
	return;
}
int dfs(int u,int flow){
	if(u==t){
		maxflow+=flow;
		return flow;
	}
	int used=0;
	for(int i=head[u];i;i=next[i]){
		int v=to[i];
		if(w[i]&&deep[v]+1==deep[u]){
			int quan=dfs(v,min(w[i],flow-used));
			if(quan){
				w[i]-=quan;
				w[i^1]+=quan;
				used+=quan;
			}
			if(flow==used) return used;
		}
	}
	--gap[deep[u]];
	if(gap[deep[u]]==0){
		deep[s]=n*2+1;
	}
	deep[u]++;
	gap[deep[u]]++;
	return used;
}
int ISAP(){
	maxflow=0;
	bfs();
	while(deep[s]<n*2){
		dfs(s+n,INF);
	}
	return maxflow;
}
signed main(){
	cin>>n>>m>>s>>t;
	for(int i=1;i<=n;i++){
		add(i,i+n,1);
		add(i+n,i,0);
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(v+n,u,INF);
		add(u,v+n,0);
		add(u+n,v,INF);
		add(v,u+n,0);
	}
	cout<<ISAP();
	return 0;
}
```


---

## 作者：GIFBMP (赞：1)

（提示：在所有关于连边的图中，反向边都被作者省略了）

首先看题，很明显的一道最小割。

然而求的是割点，该怎么办呢？

对于这种题目，我们一般可以想到**拆点**。

即对于一个点（如下图）：

![tijie1.PNG](https://i.loli.net/2019/08/18/Tpw3OKsGvI5nBDd.png)

我们将它拆成两个点，分别为入点和出点（如下图），再连一条边权为1的边：

![tijie2.PNG](https://i.loli.net/2019/08/18/2ERha8AotjKLBMP.png)

把所有点都拆成两个点后，对于两两台电脑之间有连接的部分，在它们之间连一条边权为$INF$的边，然后求最小割即可。

然而，在两个已经被拆过的点之间连双向边有坑……

如果我们直接连边的话，效果如下图：

![tijie3.PNG](https://i.loli.net/2019/08/18/32lXIUrus5cpGQk.png)

而这很明显是错的。

所以我们应该这样连边（如下图）：

![tijie4.PNG](https://i.loli.net/2019/08/18/qJCmUjxPipAZOKw.png)

细节都讲完了，附上代码：
```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x3f3f3f3f
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
int n,m,k,s,t,fir[200010],next[800010],to[800010],cost[800010],tot=1,dep[200010];
bool inq[200010];
void add(int u,int v,int w){
	to[++tot]=v;
	next[tot]=fir[u];
	fir[u]=tot;
	cost[tot]=w;
}
bool bfs(){
	memset(dep,0x3f,sizeof(dep));
	memset(inq,0,sizeof(inq));
	dep[s]=0;
	queue<int>q;
	q.push(s);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		inq[x]=0;
		for(int i=fir[x];i;i=next[i]){
			int v=to[i];
			if(dep[v]>dep[x]+1&&cost[i]){
				dep[v]=dep[x]+1;
				if(!inq[v]){
					q.push(v);
					inq[v]=1;
					if(v==t)return 1;
				}
			}
		}
	}
	if(dep[t]!=0x3f3f3f3f)return 1;
	return 0;
}
int dfs(int x,int low){
	int rlow=low;
	if(x==t)
		return low;
	for(int i=fir[x];i;i=next[i]){
		if(rlow<=0)break;
		int v=to[i];
		if(cost[i]&&dep[v]==dep[x]+1){
			int flow=dfs(v,min(rlow,cost[i]));
			if(!flow)continue;
			rlow-=flow;
			cost[i]-=flow;
			cost[i^1]+=flow;
		}
	}
	if(low-rlow==0)dep[x]=0x3f3f3f3f;
	return low-rlow;
}
int Dinic(){
	int maxflow=0,lowflow;
	while(bfs()){
		while(lowflow=dfs(s,INF)){
			maxflow+=lowflow;
		}
	}
	return maxflow;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	t+=n;
	for(int i=1;i<=n;i++){
		if(i!=s&&i!=t-n){
			add(i,i+n,1);
			add(i+n,i,0);
		}
		else{
			add(i,i+n,INF);
			add(i+n,i,0);
		}
	}
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u+n,v,INF);
		add(v,u+n,0);
		add(v+n,u,INF);
		add(u,v+n,0);
	}
	printf("%d",Dinic());
	return 0;
}
```

---

## 作者：noiplao (赞：1)

# 本题重点在于拆点

蒟蒻一开始一眼切最小割，然后放个了最大流模板上去

居然有$80pts$......你咕的数据不是吹的

后来发现是删点

具体方法：将一个点拆成入度$(i)$和出度$(i+n)$两个点（入点和出点），入度和出度间再连一条权值为1的边（点只能删一次），然后就转化为求最小割了

一些理解：首先题目给的边要连权值$INF$的，因为边只表示联通，并没有限定容量。所以求最小割时割边只有可能是出点和入点之间的边。

然后最大流最小割定理有最大流等于最小割，套最大流模板就行了（话说最大流算法实际是求最小割的）

模板打的是$dinic$(码风略丑)

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f;
const int N=2*1e5+10; 
struct edges
{
	int u,v,w;
}p[N];
int head[N],nxt[N],cnt=-1,cur[N];
inline void add(int x,int y,int z)
{
	p[++cnt].u=x;
	p[cnt].v=y;
	p[cnt].w=z;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
int h[N],n,m,s,t;
bool in[N];
inline bool bfs()
{
	for(int i=1;i<=n;i++)
	{
		cur[i]=head[i];//当前弧优化
		h[i]=INF;
		in[i]=0;
	}
	queue<int> q;
	h[s]=0;
	q.push(s);
	int k;
	while(!q.empty())
	{
		k=q.front();q.pop();in[k]=0;
		for(int i=head[k];i!=-1;i=nxt[i])
		{
			int dd=p[i].v;
			if(h[dd]>h[k]+1&&p[i].w)
			{
				h[dd]=h[k]+1;
				if(!in[dd])
				{
					q.push(dd);
					in[dd]=1;
				}
			}
		}
	}
	if(h[t]!=INF)
		return true;
	else
		return false;
}
inline int dfs(int flow,int x)
{
	int rflow=0,used=0;
	if(!flow)
		return 0;
	if(x==t)
		return flow;
	for(int i=cur[x];i!=-1;i=nxt[i])
	{
		cur[x]=i;
		int dd=p[i].v;
		if(h[dd]==h[x]+1)
		{
			int temp=min(p[i].w,flow-used);
			if((rflow=(dfs(temp,dd))))
			{
				p[i].w-=rflow;
				p[i^1].w+=rflow;
				used+=rflow;
			}
		}
		if(used==flow)
			break;
	}
	return used;
}
inline int dinic()
{
	int maxflow=0;
	while(bfs())
		maxflow+=dfs(INF,s);
	return maxflow;
}
int main()
{
	memset(head,-1,sizeof(head));
	memset(nxt,-1,sizeof(nxt));
	int t1,t2;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	s+=n;
	for(int i=1;i<=n;i++)
	{
		add(i,i+n,1);//拆出点和入点
		add(i+n,i,0);//反向边
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&t1,&t2);
		add(t1+n,t2,INF);
		add(t2,t1+n,0);//反向边
		add(t2+n,t1,INF);
		add(t2+n,t1,0);
	}
	n+=n;
	printf("%d",dinic());
	return 0;
}

```


---

## 作者：VenusM1nT (赞：0)

读题，发现要求的是删去多少点后图不连通，那么很容易想到的就是求最小割

但是最小割求出的是割去的**边数**，而这题问的是割去多少个点，于是我们需要把点转换为边

那么我们就要用网络流中常用的手法——拆点了

我们将一个点$x$拆成$x$和$x+n$两个点，在连边时将$x$和$y+n$，$x+n$和$y$分别连起来，再将$x$和$x+n$连起来，求一遍最小割即可

见代码

```cpp
#include<bits/stdc++.h>
#define inf 2147400000
using namespace std;
queue <int> q;
int cnt=1,fst[505],nxt[5005],to[5005],w[5005],cur[505];
int n,m,S,T,dep[505];
void AddEdge(int u,int v,int c)
{
    to[++cnt]=v;
    nxt[cnt]=fst[u];
    fst[u]=cnt;
    w[cnt]=c;
}
bool Bfs()
{
    memset(dep,0,sizeof(dep));
    q.push(S);
    dep[S]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=fst[u];i;i=nxt[i])
        {
            int v=to[i];
            if(!dep[v] && w[i])
            {
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[T];
}
int Dfs(int u,int flow)
{
    if(u==T || !flow) return flow;
    int used=0;
    for(int i=cur[u];i;i=nxt[i])
    {
        cur[u]=i;
        int v=to[i];
        if(dep[v]==dep[u]+1 && w[i])
        {
            int fl=Dfs(v,min(flow,w[i]));
            if(fl)
            {
                used+=fl;
                flow-=fl;
                w[i]-=fl;
                w[i^1]+=fl;
                if(!flow) break;
            }
        }
    }
    return used;
}
int Dinic()//弧优化Dinic，不谈
{
    int sum=0;
    while(Bfs())
    {
        memcpy(cur,fst,sizeof(fst));
        sum+=Dfs(S,inf);
    }
    return sum;
}
int main()
{
    scanf("%d %d %d %d",&n,&m,&S,&T);
    S+=n;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        AddEdge(y+n,x,inf);
        AddEdge(x,y+n,0);
        AddEdge(x+n,y,inf);
        AddEdge(y,x+n,0);//拆点后连边
    }
    for(int i=1;i<=n;i++)
    {
        AddEdge(i,i+n,1);//将拆出的两个点之间连一条边
        AddEdge(i+n,i,0);
    }
    int ans=Dinic();//求解
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：秋日私语 (赞：0)

个人blog：http://blog.csdn.net/A_Comme_Amour/article/details/79543249

题目
-
[传送门](https://www.luogu.org/problemnew/show/P1345)
最小割的点的数量
题解
-
一般的最小边求的是边的权值和，这里要求割掉的最少的点的数量。
原本以为割掉的最少的边的数量就是割掉的最少的点的数量。于是写了个最小割跑，失败了。
后来看到没有建双向边，于是建了但还是GG；
错误之处在于这张图
![](http://img-blog.csdn.net/20180314094933254?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L0FfQ29tbWVfQW1vdXI=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
如果割点的话，我们只需要割掉红色的点；如果割边的话需要割掉两条边，这就是问题所在。那么如何处理呢？
#####我们采用拆点的思想；
对于每一个点都复制。比如要从x向y连边，先从x向x+n连一条边，长度为1（因为每个点只能被割掉一次）；再从x+n向y连一条边，长度为inf。然后从S+n到T跑最大流（最小割）即可；
对于为什么这样进行建边，在进行一些解释：因为一个点可以连许多条边，两点之间只能连一条边（意会一下？），所以我们就把割点转化成了割边。
如下图
![](http://img-blog.csdn.net/20180314095254577?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L0FfQ29tbWVfQW1vdXI=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
代码
-

```
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn=10001;
const int inf=1e9;

queue <int> q;
int n,m,s,t,deep[maxn],maxflow;
struct Edge{
	int next,to,dis;
}edge[maxn<<1];
int num_edge=-1,head[maxn],cur[maxn];

void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}

bool bfs(int s,int t)
{
	memset(deep,0x7f,sizeof(deep));
	for (int i=0; i<=n; i++) cur[i]=head[i];
	while (!q.empty()) q.pop();
	deep[s]=0; q.push(s);
	
	while (!q.empty())
	{
		int now=q.front(); q.pop();
		for (int i=head[now]; i!=-1; i=edge[i].next)
		{
			int to=edge[i].to;
			if (deep[to]>inf && edge[i].dis)
			{
				deep[to]=deep[now]+1;
				q.push(to);
				if (to==t) return true;
			}
		}
	}
	return deep[t]<inf;
}

int dfs(int now,int t,int limit)
{
	if (now==t || !limit) return limit;
	int flow=0,f;
	for (int i=cur[now]; i!=-1; i=edge[i].next)
	{
		cur[now]=i; int to=edge[i].to;
		if (deep[to]==deep[now]+1 && (f=dfs(to,t,min(edge[i].dis,limit))))
		{
			flow+=f;
			limit-=f;
			edge[i].dis-=f;
			edge[i^1].dis+=f;
			if (!limit) break;
		}
	}
	return flow;
}

void Dinic(int s,int t)
{
	while (bfs(s,t))
		maxflow+=dfs(s,t,inf);
}

int main()
{
	memset(head,-1,sizeof(head));
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for (int i=1; i<=n; i++) {add_edge(i,i+n,1); add_edge(i+n,i,0);}//复制节点 
	for (int i=1; i<=m; i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add_edge(x+n,y,inf); add_edge(y,x+n,0); 
		add_edge(y+n,x,inf); add_edge(x,y+n,0);
	}
//	for (int i=0; i<=num_edge; i++) printf("%d %d %d\n",edge[i^1].to,edge[i].to,edge[i].dis);
	s+=n; n*=2;
	Dinic(s,t);
	printf("%d\n",maxflow);
	return 0;
}
```

总结
-
考虑一下这种“拆点”“把点转化成边”的思想，还是挺常用的
该建双向边的时候建双向边
写完题目及时总结

---

## 作者：feng_chengjie (赞：0)

##来一发EK做法，只需一个dfs()即可

基本思路还是同先先先先辈，其实发现同时创立i和i+n两个点有这样的奇妙之处：

1、把i~i+n 的边权存成最小的1，就保证了删边时只会删除i~i+n这样的边

2、再仔细想想，若是删除了i~i+n 这样的边，就代表已经删除了i这个点，而又因为边权是1，因此说明花费是一个点。


参考代码：





```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=300;
const int inf=1e9;
struct point
{
    int to;
    int nxt;
    int c;
}edge[(maxn<<4)+100];
int n,m,tot=0,ans=0,pf,s,t;
int vis[maxn<<1],head[maxn<<1];
void add(int u,int v,int ww)
{
    edge[tot].to=v;
    edge[tot].nxt=head[u];
    edge[tot].c=ww;
    head[u]=tot++;
}
bool dfs(int x,int f)
{
    if(x==t)
    {
        ans+=f;
        pf=f;
        return 1;
    }
    vis[x]=1;
    for(int i=head[x];~i;i=edge[i].nxt)
    {
        int v=edge[i].to;
        if(!vis[v] && edge[i].c>0)
        {
            if(dfs(v,min(f,edge[i].c)))
            {
                edge[i].c-=pf;
                edge[i^1].c+=pf;
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    memset(head,-1,sizeof(head));
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++)
    {
        int a,b;
        cin>>a>>b;
        add(a+n,b,inf); add(b,a+n,0);
        add(b+n,a,inf); add(a,b+n,0);
    }
    for(int i=1;i<=n;i++) 
        add(i,i+n,1),add(i+n,i,0);
    while(dfs(s+n,inf))
    {
        pf=0;
        memset(vis,0,sizeof(vis));
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：远航之曲 (赞：0)

用的楼下的思想【其实就是最小点割。

引用楼下”先把每个点i拆成两个点，编号分别为i和i+n，把i到i+n连一条容量为1的边，然后若i到j有一条边，则连接i+n->j,i->j+n，边权为无穷大，然后求s+n到t的最大流即是答案“

具体实现用的dinic求最大流


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define MAXN 1000000
#define INF 100000000
using namespace std;
int n,m,s,t;
int tot=2,g[MAXN],num[MAXN],nnext[MAXN],flow[MAXN];
int team[MAXN],head,tail,d[MAXN];
void Add(int x,int y,int z){nnext[tot]=g[x];g[x]=tot;num[tot]=y;flow[tot]=z;tot++;}
bool bfs()
{
    head=tail=0;memset(d,0,sizeof(d));
    d[s]=1;team[++tail]=s;
    while(head<tail)
    {
        int x=team[++head];
        for(int i=g[x];i;i=nnext[i])
            if(d[num[i]]==0&&flow[i]!=0)
                d[num[i]]=d[x]+1,team[++tail]=num[i];
    }
    if(d[t]==0) return false;
    return true;
}
int dfs(int x,int mmin)
{
    if(x==t) return mmin;
    int tmp,f=0;
    for(int i=g[x];i;i=nnext[i])
        if(d[num[i]]==d[x]+1&&flow[i]&&(tmp=dfs(num[i],min(mmin,flow[i]))))
        {
            flow[i]-=tmp,flow[i^1]+=tmp;
            f+=tmp,mmin-=tmp;
            if(mmin==0) return f;
        }
    return f;
}
int main()
{
    scanf("%d %d %d %d",&n,&m,&s,&t);
    for(int x,y,i=1;i<=m;i++)
    {
        scanf("%d %d",&x,&y);
        Add(x+n,y,INF),Add(y,x+n,0);
        Add(y+n,x,INF),Add(x,y+n,0);
    }
    for(int i=1;i<=n;i++) Add(i,i+n,1),Add(i+n,i,0);
    int ans=0;while(bfs()) ans+=dfs(s+n,INF);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：f337889 (赞：0)

# 最小割问题
## 求最大流
要注意对每个点都要拆成两个点 中间通一条容量为1的边

比如a点 就要拆成 S[a]--->E[a] 当然 a的终点号就是 a+n

a如果通向b点

则要把 E[a]-->S[b] E[b]-->S[a] 这样就能满足题目中有关双向联通的要求

由于起始点st与终点ed不能删


则本问题变成了求E[st] 到 S[ed] 的最小割问题 就是求最大流

代码如下：```cpp
#include<cstdio>
    #include<iostream>
    #include<algorithm>
    #include<vector>
    #include<queue>
    #include<cstring>
    using namespace std;
    #define maxn 40000
    #define inf 0x7fffffff
    struct edg{
        int t,cap,flow,rev;
    };
    vector<edg> M[maxn];
    int cur[maxn],d[maxn],st,ed,n,m;
    void addedge(int a,int b,int cp){
        M[a].push_back((edg){b,cp,0,M[b].size()});
        M[b].push_back((edg){a,0,0,M[a].size()-1});
    }
    bool bfs(int s,int t){
        memset(d,0,sizeof(d));
        queue<int> Q;
        d[s]=1;
        Q.push(s);
        while(!Q.empty()){
            int hd=Q.front();
            if(hd==t) return 1;
            Q.pop();
            for(int i=0;i<M[hd].size();i++){
                edg t=M[hd][i];
                if(t.cap>t.flow && d[t.t]==0){
                    Q.push(t.t);
                    d[t.t]=d[hd]+1;
                }
            }
        } 
        return 0;
    }
    int dfs(int s,int t,int fl){
        if(s==t){
            return fl;
        }
        for(int &i=cur[s];i<M[s].size();i++){
            edg &e=M[s][i];
            if(d[e.t]==d[s]+1 && e.cap>e.flow){
                int di=dfs(e.t,t,min(fl,e.cap-e.flow));
                if(di>0){
                    e.flow+=di;
                    M[e.t][e.rev].flow-=di;
                    return di;
                }
            }
        }
        return 0;
    }
    int Dinic(int st,int ed)
    {
        int Ans=0;
        while (bfs(st,ed))
        {
            memset(cur,0,sizeof(cur));
            while (int dlta=dfs(st,ed,inf))
                        Ans+=dlta;
            //cout<<Ans<<endl;
        }
        return Ans;
    }
    int main(){
        cin>>n>>m>>st>>ed;
        for(int i=1,a,b;i<=m;i++){
            cin>>a>>b;
            addedge(a+n,b,inf);
            addedge(b+n,a,inf);
        }
        for(int i=1;i<=n;i++){
            addedge(i,i+n,1);
        }
        int mxf=Dinic(st+n,ed);
        cout<<mxf;
}
```
###### ---分割线-----
蒟蒻第一次写题解，大佬勿喷

---

