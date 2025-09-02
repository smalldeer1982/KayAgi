# 「TOCO Round 1」History

## 题目描述

这里有一棵 $n$ 个结点根为 $1$ 号结点的树，每个结点上都有一盏灯，初始状态都是关闭。现在有 $m$ 次事件发生，有以下几种情况：

`1 x` 将 $x$ 位置上的灯打开或关闭（原来如果打开就关闭，否则打开）。

`2 x y` 询问树上与 $x$ 相同深度的点中与 $x$ 结点距离为 $y$ 的点中开着的灯的个数。

`3 x` 回到第 $x$ 次事件发生之后的状态。

对于每个 $2$ 询问请给出回答。





## 说明/提示

**本题采用打包测评。**

* Subtask 1（10 pts）：满足所有询问中 $y \bmod 2=1$。


* Subtask 2（20 pts）：$n,m\leq 10$。

* Subtask 3（30 pts）：$n,m\leq 10^3$。

* Subtask 4（40 pts）：$n,m\leq 10^5$。

对于 $100\%$ 的数据，$1\leq n,m\leq 10^5$，$3$ 操作保证 $0 \leq x$。

## 样例 #1

### 输入

```
3
1 2
1 3
6
1 3
2 2 2
1 2
2 2 2
1 3
2 2 2```

### 输出

```
1
1
0```

# 题解

## 作者：bzy (赞：13)

离线操作树 + bfs序 + 树状数组

首先发现这题要求退回到历史版本而未要求强制在线，而且对树的操作也是可逆的，所以可以把所有操作与询问按影响顺序连成一棵操作树。这样每个对每个询问有影响的操作是操作树上的一个前缀。于是我们只需要对操作树进行 dfs，进入节点时执行对应的操作，退出时则撤销操作。

然后考虑询问的特点，如果 $y$ 为奇数时，答案显然为 $0$；若为偶数，则满足条件的节点一定是 $x$ 的 $\frac{y}{2}$ 级父亲的 $\frac{y}{2}$ 级儿子，但需要注意的是，$x$ 的 $\frac{y}{2}-1$ 级父亲的 $\frac{y}{2}-1$ 级儿子也满足前述条件但不满足询问条件，所以我们可以把一个询问拆成两个形如「$x$ 的 $k$ 级父亲的 $k$ 级儿子上权值和」的问题。

然后可以发现一个性质，被拆解后的询问每次涉及的点是原树 bfs 序上连续的一段，具体证明也不难。

然后问题就被转化为了 bfs 序上单点修改区间求和问题，可以用常数小的树状数组解决。

考虑确定询问的区间，可以先把询问离线，用 [[Cnoi2019]雪松果树](https://www.luogu.com.cn/problem/P5384) 中的 dfs + 差分 的方法求出询问节点的 $k$ 级父亲的 $k$ 级儿子的数量，然后用被 dfs 到的时间差确定该节点在区间内的相对位置，从而确定询问的区间，这部分时间复杂度为 $O(n+m)$，具体可以参考下方的代码。

总时间复杂度 $O(m\log n)$，空间复杂度 $O(n+m)$。

参考代码(略丑勿喷) :

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100000;

vector<int> to[200005];
int deep[200005];
int id  [200005];       // bfs 序
int stk [200005];
int bin [200005];

int que[200005][3];
int len[200005];        // 区间长度
int lef[200005];        // 时间差

vector<int> ct[200005];
vector<int> q1[200005];
vector<int> q2[200005];

int val[200005];
int ans[200005];

namespace BIT{
    int c[100005], N = 100004;
    int lowbit( int x ) { return x & -x; }
    void modify( int x, int v ) { for( ;x < N; x += lowbit(x) ) c[x] += v; } 
    int query( int x ) { int r = 0; for( ; x; x -= lowbit(x) ) r += c[x]; return r; }
}

void dfs1( int x, int f ) {
    deep[x] = deep[f] + 1; stk[ deep[x] ] = x;
    for( auto Q : q1[x] ) if( que[Q][2] < deep[x] ) 
      { q2[ stk[ deep[x] - que[Q][2] ] ].push_back(Q); }
    for( auto N : to[x] ) if( N ^ f ) dfs1( N, x );
}

void dfs2( int x, int f ) {
    for( auto Q : q2[x] ) len[Q] -= bin[ deep[x] + que[Q][2] ];
    bin[ deep[x] ] ++;
    for( auto Q : q1[x] ) lef[Q] = len[Q] + bin[ deep[x] ];
    for( auto N : to[x] ) if( N ^ f ) dfs2( N, x );
    for( auto Q : q2[x] ) len[Q] += bin[ deep[x] + que[Q][2] ];
}

void dfs3( int x ) {
    int y = que[x][1], z = N + x;
    if( que[x][0] == 1 ) BIT::modify( id[y], val[y] ? -1 : 1 ), val[y] ^= 1;
    if( que[x][0] == 2 ) if( len[x] )
      { ans[x] += BIT::query( id[y] - lef[x] + len[x] ) - BIT::query( id[y] - lef[x] );
        ans[x] -= BIT::query( id[y] - lef[z] + len[z] ) - BIT::query( id[y] - lef[z] ); }
    for( auto N : ct[x] ) dfs3(N);
    if( que[x][0] == 1 ) BIT::modify( id[y], val[y] ? -1 : 1 ), val[y] ^= 1;
}

void bfs() {
    queue<int> Q; Q.push(1);
    int cnt = 0;
    while( Q.size() ) {
        int x = Q.front(); Q.pop(); id[x] = ++ cnt;
        for( auto N : to[x] ) if( !id[N] ) Q.push(N);
    }
}

int main() {
    int n, m; cin >> n;
    for( int i = 1; i < n; i ++ )
      { int u, v; cin >> u >> v;
        to[u].push_back(v);	
        to[v].push_back(u); }
    cin >> m;
    for( int i = 1; i <= m; i ++ ) {
        cin >> que[i][0];
        if( que[i][0] == 1 or que[i][0] == 2 )
          { ct[i - 1].push_back(i); }
        if( que[i][0] == 1 ) cin >> que[i][1];
        if( que[i][0] == 2 ) cin >> que[i][1] >> que[i][2];
        if( que[i][0] == 3 ) 
          { int k; cin >> k; ct[k].push_back(i); }
        if( que[i][0] == 2 ) if( que[i][2] % 2 == 0 ) 
          { q1[ que[i][1] ].push_back(i); 
            q1[ que[i][1] ].push_back(i + N);
            que[i][2] /= 2;
            que[i + N][1] = que[i][1];
            que[i + N][2] = que[i][2] - 1; }
    }
    bfs(); dfs1( 1, 0 ); dfs2( 1, 0 ); dfs3(0);
    for( int i = 1; i <= m; i ++ ) if( que[i][0] == 2 ) cout << ans[i] << "\n";
}
```


---

## 作者：Lynkcat (赞：9)

官方的laji题解。

有一个很显然易见的结论，$y$ 只有可能是偶数。于是你拿到了 $10 pts$ 。

接下来的问题分两部分考虑：

如果没有 $3$ 操作，该怎么做？

我们显然可以转化一下问题，询问树上与 $x$ 相同深度的点中与 $x$ 结点距离为 $y$ 的点中开着的灯的个数其实就是 与 $x$ 深度相同且与 $x$ 的 $LCA$ 是 $x$  的 $y/2$ 级组先。

接着再考虑如何维护一颗子树内深度为 $k$ 的开着的灯的个数。

我们可以考虑维护 $dfs$ 序，我们知道一个节点的子树一定是在 $dfs$ 序中连续的一段，那么我们可以考虑维护这一段中 $dep$ 与 $x$ 相等中开着的点的个数。这个东西可以用平衡树、动态开点线段树等东西直接维护。值得注意的是这一段里有一部分节点与 $x$ 的 $LCA$ 是 $fa[x][y/2]$ 的子孙，所以答案应该是 $query(fa[x][y/2])-query(fa[x][y/2-1])$。

加上 $3$ 操作其实就是个强行二合一。我们会发现其实回到第 $x$ 个时刻就是从第 $x$ 个时刻转移过来，我们只需要连边后在树上跑 $dfs$ 即可。

总时间复杂度 $O(n \log n)$ 。

---

## 作者：panyanppyy (赞：6)

学校[dd_d](https://www.luogu.com.cn/user/167999)的模拟赛，赛时直接寄了，赛后听 Ta 讲了三遍才会 Orz。
## 题面

```1 x``` 将 $x$ 位置上的灯打开或关闭（原来如果打开就关闭，否则打开）。

```2 x y``` 询问树上与 $x$ 相同深度的点中与 $x$ 结点距离为 $y$ 的点中开着的灯的个数。

```3 x``` 回到第 $x$ 次事件发生之后的状态。
## 题解
先不考虑操作 $3$ 会在下面提到。

* $10pts$ 在考场上想出来的做法，因为树同层的点之间的距离显然是偶数，如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/mn94dfkm.png)

手玩发现 $len_{2\rightarrow3}=2,len_{6\rightarrow7}=4,len_{5\rightarrow8}=4\dots$

所以当操作 $2$ 中 $y=0$ 时，答案就是 $0$。

* $20\sim30pts$ $\mathcal O(n^3)$ 对于每次询问做一遍搜索，找出距离等于 $y$ 的点，统计答案，对于操作 $1$ 直接暴力修改即可。

* $50\sim60pts$ $\mathcal O(n^2)$ 想到 $20pts$ 的做法以后就很容易想到 $60pts$ 做法了吧（~~就我没想到~~）。

先以每个点为起点预处理出所有点到它的距离，每次询问这些点。

* $100pts$ $\mathcal O(n\log n)$ 对于每个点之间的距离可以用 ST 表 $f_{i,j}$ 维护 $i$ 向上 $j$ 级的祖先，区间修改查询则可以用动态开点线段树维护。

## 维护方法
由于 dfs 序是连续的一段，那么我们可以维护这一段中深度等于 $x$ 的点中开着的点的个数，先 $\mathcal O(n)$ 枚举出所有子树的 dfs 序起点和终点。

然后由于向上的距离是 $y/2$ 所以统计 $x$ 向上 $y/2$ 级为根的子树中亮着的节点数即可。

**但是**相同深度的还有其他子树，如上图中 $4$ 和 $4$ 在相同深度，假设 $y=4$ 但是他们的距离显然不是 $4$，需要统计的是 $8$ 和 $9$，所以在统计深度时还要减去它向上 $y/2-1$ 级为根的子树中亮着的节点数：
$$ans\leftarrow query(f_{x,y/2})-query(f_{x,y/2-1})$$
$query$ 表示动态开点线段树的询问操作。

## 操作3
最后就是操作 $3$ 的解决方法，因为要回到第 $x$ 次所以讲所有询问离线，把操作 $3$ 中的 $x$ 和 $i$ 连边，对于其他操作直接由上一次向下一次连边，最后**从0开始**对于每条边做一遍 dfs 遍历并进行操作，操作 $3$ 就迎刃而解了。

[Code](https://www.luogu.com.cn/paste/wwhildah)

---

## 作者：Charlie_ljk (赞：4)

# 做法一，bfs 序

双 log 做法，目前最优解，吊打单 log。

## bfs 序的一些性质

- 对于一段单调递增的 bfs 序的对应节点的 k 级祖先的 bfs 序是单调不下降的，证明显然。

- 对于节点 $x$，他的 $k$ 级子孙组成的 bfs 序是连续的一段区间。

## 对于本题

显然当 $y$ 是奇数的时候答案为 $0$，每次查询即查询 $x$ 的 $\frac{y}{2}$ 级祖先的 $\frac{y}{2}$ 级子孙中开灯的个数，对于这些点中在 $x$ 的 $\frac{y}{2}-1$ 级祖先子树内的节点到 $x$ 的距离并不是 $y$，所以再减去其贡献即可。

那么我们可以利用 bfs 序的这两个性质，二分出该连续区间的左右端点，这个复杂度是 $\log^2$ 的，随后可以用树状数组维护 bfs 序的单点修改区间查询。

对于操作 $3$，可以建操作树或主席树完成，对于操作树，将操作离线，若为操作 $3$ 则 $x$ 向 $i$ 连边，否则 $i-1$ 向 $i$ 连边。最后 dfs 遍历一遍进行相应操作并回溯即可。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define endl '\n'
#define sort stable_sort
#define pb push_back
#define lowbit(x) (x&-x)
using namespace std;
const int N=1e5+10;
template<typename Tp> inline void read(Tp&x)
{
	x=0;register bool z=true;
	register char c=getchar_unlocked();
	for(;!isdigit(c);c=getchar_unlocked()) if(c=='-') z=0;
	for(;isdigit(c);c=getchar_unlocked()) x=(x<<1)+(x<<3)+(c^48);
	x=(z?x:~x+1);
}
template<typename T,typename ...Tp> inline void read(T &x,Tp &...y){read(x);read(y...);}
template<typename Tp> inline void wt(Tp x){if(x>9)wt(x/10);putchar_unlocked((x%10)+'0');}
template<typename Tp> inline void write(Tp x){if(x<0)putchar_unlocked('-'),x=~x+1;wt(x);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y){write(x);putchar_unlocked(' ');write(y...);}
int n,m,tot,c[N],to[N],bfn[N],pos[N],dep[N],yet[N],ans[N],fa[N][20];
bool a[N]; vector<int>e[N],g[N];
struct aa {int op,x,y;}que[N];
void add(int x) {for(x++;x<=n+1;x+=lowbit(x)) c[x]++;}
void del(int x) {for(x++;x<=n+1;x+=lowbit(x)) c[x]--;}
int ask(int x) {int res=0; for(x++;x;x-=lowbit(x)) res+=c[x]; return res;}
int ask(int l,int r) {return ask(r)-ask(l-1);}
void bfs()
{
	queue<int>q; q.push(1);
	while(!q.empty())
	{
		int x=q.front(); q.pop(),dep[pos[bfn[x]=++tot]=x]=dep[fa[x][0]]+1;
		for(int i=1;i<=__lg(dep[x])+1;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
		for(int y:e[x]) if(!bfn[y]) q.push(y),fa[y][0]=x;
	}
}
int find(int x,int k)
{
	if(dep[x]-1<k) return 0;
	for(int i=__lg(dep[x])+1;i>=0;i--) if((k>>i)&1) x=fa[x][i]; 
	return bfn[x];
}
int solve(int x,int k)
{
	int l=1,r=n,pre=0,suf=0;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(find(pos[mid],k)>=x) pre=mid,r=mid-1;
		else l=mid+1;
	}
	l=1,r=n;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(find(pos[mid],k)<=x) suf=mid,l=mid+1;
		else r=mid-1;
	}
	return ask(pre,suf);
}
void dfs(int i)
{
	int op=que[i].op,x=que[i].x,y=que[i].y;
	if(op==1) a[x]?del(bfn[x]):add(bfn[x]),a[x]^=1;
	else if(op==2)
	{
		if(y&1) ans[i]=0; else if(!y) ans[i]=a[x];
		else if(dep[x]-1<(y>>=1)) ans[i]=0;
		else ans[i]=solve(find(x,y),y)-solve(find(x,y-1),y-1);
	}
	for(int j:g[i]) dfs(j);
	if(op==1) a[x]?del(bfn[x]):add(bfn[x]),a[x]^=1;
}
signed main()
{
	read(n);
	for(int i=1,x,y;i<n;i++) read(x,y),e[x].pb(y),e[y].pb(x);
	bfs(); read(m);
	for(int i=1,op,x,y;i<=m;i++)
	{
		read(op,x); if(op==2) read(y);
		op!=3?g[i-1].pb(i):g[x].pb(i),que[i]={op,x,y};
	}
	dfs(0);
	for(int i=1;i<=m;i++) if(que[i].op==2) write(ans[i]),puts("");
}
```

# 做法二，dfs 序

单 log 做法，但是线段树维护常数较大。

## dfs 序的一些性质

对于节点 x，他的子树上所有节点构成的 dfs 序是连续的一段区间。

## 对于本题

做法一说过的这里不再说，只是如何维护的区别。

给每个深度开一棵 dfs 序的动态开点线段树，那么对于查询操作，即在对应深度的线段树上查询 $x$ 的 $\frac{y}{2}$ 级祖先的子树对应的 dfs 序区间。

同样需减去 $x$ 的 $\frac{y}{2}-1$ 级祖先贡献，建操作树或主席树维护操作 $3$。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define endl '\n'
#define sort stable_sort
#define pb push_back
using namespace std;
const int N=1e5+10,M=2e6+10;
template<typename Tp> inline void read(Tp&x)
{
	x=0;register bool z=true;
	register char c=getchar_unlocked();
	for(;!isdigit(c);c=getchar_unlocked()) if(c=='-') z=0;
	for(;isdigit(c);c=getchar_unlocked()) x=(x<<1)+(x<<3)+(c^48);
	x=(z?x:~x+1);
}
template<typename T,typename ...Tp> inline void read(T &x,Tp &...y){read(x);read(y...);}
template<typename Tp> inline void wt(Tp x){if(x>9)wt(x/10);putchar_unlocked((x%10)+'0');}
template<typename Tp> inline void write(Tp x){if(x<0)putchar_unlocked('-'),x=~x+1;wt(x);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y){write(x);putchar_unlocked(' ');write(y...);}
int n,m,tot,rt[N],ls[M],rs[M],in[N],out[N],dep[N],val[M],ans[N],fa[N][20];
struct aa {int op,x,y;}q[N]; vector<int>e[N],g[N]; bool a[N];
void change(int &p,int l,int r,int x,int d)
{
	if(!p) p=++tot;
	if(l==r) return val[p]+=d,void();
	int mid=l+r>>1;
	x<=mid?change(ls[p],l,mid,x,d):change(rs[p],mid+1,r,x,d);
	val[p]=val[ls[p]]+val[rs[p]];
}
int ask(int p,int l,int r,int vl,int vr)
{
	if(!p) return 0;
	if(vl<=l&&vr>=r) return val[p];
	int res=0,mid=l+r>>1;
	if(vl<=mid) res+=ask(ls[p],l,mid,vl,vr);
	if(vr>mid) res+=ask(rs[p],mid+1,r,vl,vr);
	return res;
}
int ask(int x,int k) {return ask(rt[k],1,n,in[x],out[x]);}
void dfs(int x,int t)
{
	in[x]=++tot,dep[x]=dep[fa[x][0]=t]+1;
	for(int i=1;i<=__lg(dep[x]);i++) fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int y:e[x]) if(y!=t) dfs(y,x); out[x]=tot;
}
int find(int x,int k)
{
	if(dep[x]-1<k) return 0;
	for(int i=__lg(dep[x]);~i;i--) if((k>>i)&1) x=fa[x][i];
	return x;
}
void solve(int i)
{
	int op=q[i].op,x=q[i].x,y=q[i].y,tmp;
	if(op==1) change(rt[dep[x]],1,n,in[x],a[x]?-1:1),a[x]^=1;
	if(op==2) if(!(y&1))
	{
		if(!y) ans[i]=a[x];
		else if(fa[tmp=find(x,(y>>1)-1)][0])
			ans[i]=ask(fa[tmp][0],dep[x])-ask(tmp,dep[x]);
	}
	for(int j:g[i]) solve(j);
	if(op==1) change(rt[dep[x]],1,n,in[x],a[x]?-1:1),a[x]^=1;
}
signed main()
{
	read(n);
	for(int i=1,x,y;i<n;i++) read(x,y),e[x].pb(y),e[y].pb(x);
	dfs(1,0),tot=0; read(m);
	for(int i=1,op,x,y;i<=m;i++)
	{
		read(op,x); if(op==2) read(y);
		op!=3?g[i-1].pb(i):g[x].pb(i),q[i]={op,x,y};
	}
	solve(0);
	for(int i=1;i<=m;i++) if(q[i].op==2) write(ans[i]),puts("");
}
```

---

## 作者：ccxswl (赞：2)

操作树加二分，目前题解区没有这种做法。

发现操作一可逆，可以用操作树，操作三解决。

操作一单点修改没什么好说的。

接下来看操作二。令 $fa_{x,k}$ 为 $x$ 的 $k$ 级祖先。

发现对于每个询问中，如果 $y$ 为奇数那么答案为 $0$。如果 $y$ 为偶数，那么答案就是 $fa_{x,y/2}$ 的 $y/2$ 级儿子的开灯的个数减 $fa_{x,y/2-1}$ 的 $y/2-1$ 级儿子的开灯的个数。

具体实现方法就是先对这棵树跑出每个点的 bfs 序和 dfs 序，记树的第 $i$ 层最大的 bfs 序为 $lst_i$。所有深度为 $d$ 的点的 bfs 序都在 $[lst_{d-1}+1,lst_d]$，在这个区间二分。

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/6ghk4dkk.png)

现在的询问 $x=5,y=4$，那么 $fa_{x,y/2}=2$，二分时如果二分出的点在以 $fa_{x,y/2}$ 为根的子树内，视想要哪边的端点移动二分区间。如果不在这棵子树内，则与 $fa_{x,y/2}$ 的 dfs 序比较。如果小，二分区间右移；如果大，二分区间左移。例如，目前二分到了 $11$ 号节点，它的 dfs 序小于 $2$ 的 dfs 序，那么二分区间右移。

最终答案为红色区间中的开灯个数减蓝色中的开灯个数。

用支持单点修改，区间求和的数据结构（例如树状数组）维护下就好了。

复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

int read() {
    int s = 0, w = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            w = -w;
        c = getchar();
    }
    while (isdigit(c)) {
        s = s * 10 + c - 48;
        c = getchar();
    }
    return s * w;
}
void pr(int x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        pr(x / 10);
    putchar(x % 10 + 48);
}
#define end_ putchar('\n')
#define spc_ putchar(' ')

const int maxN = 1e5 + 7;

int n, m;

vector<int> E[maxN];

int bfn[maxN], dfn[maxN], tot;
int dep[maxN], siz[maxN], lst[maxN], rk[maxN];

int fa[25][maxN];

void dfs(int x, int f) {
	dep[x] = dep[f] + 1;
	siz[x] = 1;
	dfn[x] = ++tot;
	
	fa[0][x] = f;
	for (int t = 1; t <= 20; t++)
		fa[t][x] = fa[t - 1][fa[t - 1][x]];
		
	for (int to : E[x])
		if (to != f) {
			dfs(to, x);
			siz[x] += siz[to];
		}
}
void bfs() {
	tot = 0;
	queue<int> Q;
	Q.push(1);
	while (!Q.empty()) {
		int f = Q.front();
		Q.pop();
		bfn[f] = ++tot;
		rk[tot] = f;
		for (int to : E[f])
			if (dep[to] > dep[f])
				Q.push(to);
	}
}

int find(int x, int k) {
	for (int i = 0; k; i++, k >>= 1)
		if (k & 1)
			x = fa[i][x];
	return x;
}

int cnt;
struct node {
	int to, x, y, id;
	node(int a, int b) {
		to = a, x = b;
		y = id = -1;
	}
	node(int a, int b, int c, int d) {
		to = a, x = b, y = c, id = d;
	}
};
vector<node> mo[maxN];

int qcnt;
struct ques {
	int x, y, id;
};
vector<ques> q[maxN];
int ans[maxN];

int v[maxN];
int t[maxN];
void add(int x, int v) {
	for (; x <= n; x += x & -x)
		t[x] += v;
}
int ask(int x) {
	int res = 0;
	for (; x > 0; x -= x & -x)
		res += t[x];
	return res;
}

int solve(int x, int y) {
	if (y == 0)
		return v[x];
	if (y & 1)
		return 0;
	y >>= 1;
	
	int f = find(x, y);
	if (!f)
		return 0;
	
	auto erfen = [x](bool ty, int f) {
		int L = lst[dep[x] - 1] + 1, R = lst[dep[x]];
		int ans = -1;
		while (L <= R) {
			int mid = (L + R) >> 1;
			int p = rk[mid];
			if (dfn[f] <= dfn[p] && dfn[p] <= dfn[f] + siz[f] - 1) {
				ans = p;
				if (ty)
					R = mid - 1;
				else
					L = mid + 1;
			}
			else if (dfn[p] < dfn[f])
				L = mid + 1;
			else
				R = mid - 1;
		}
		return ans;
	};
	
	int l = erfen(true, f), r = erfen(false, f);
	int res = ask(bfn[r]) - ask(bfn[l] - 1);
	
	f = find(x, y - 1);
	
	l = erfen(true, f), r = erfen(false, f);
	int tmp = ask(bfn[r]) - ask(bfn[l] - 1);
	
	return res - tmp;
}

void calc(int x) {
	for (auto i : mo[x]) {
		if (i.x != -1 && i.id == -1) {
			if (v[i.x])
				v[i.x] = 0, add(bfn[i.x], -1);
			else
				v[i.x] = 1, add(bfn[i.x], 1);
		}
		if (i.id != -1)
			ans[i.id] = solve(i.x, i.y);
		
		calc(i.to);
		
		if (i.x != -1 && i.id == -1) {
			if (v[i.x])
				v[i.x] = 0, add(bfn[i.x], -1);
			else
				v[i.x] = 1, add(bfn[i.x], 1);
		}
	}
}

int main() {
	n = read();
	for (int i = 1; i < n; i++) {
		int u = read(), v = read();
		E[u].push_back(v);
		E[v].push_back(u);
	}
	dfs(1, 0);
	bfs();
	for (int i = 1; i <= n; i++)
		lst[dep[i]] = max(lst[dep[i]], bfn[i]);
	
	memset(ans, 255, sizeof(ans));
	
	m = read();
	for (int i = 1; i <= m; i++) {
		int op = read();
		if (op == 1) {
			int x = read();
			mo[cnt].emplace_back(cnt + 1, x);
			++cnt;
		}
		if (op == 2) {
			int x = read(), y = read();
			mo[cnt].emplace_back(cnt + 1, x, y, i);
			++cnt;
		}
		if (op == 3) {
			int x = read();
			mo[x].emplace_back(cnt + 1, -1);
			++cnt;
		}
	}
	
	calc(0);
	
	for (int i = 1; i <= m; i++)
		if (ans[i] != -1)
			pr(ans[i]), end_;
}
```

---

## 作者：zhangxy__hp (赞：0)

看到“回到 $x$ 后的状态”，显然考虑可持久化线段树。记开灯的为 $1$，关灯的为 $0$，对于每个询问只需去查某些点的权值和即可。

考虑怎么将符合条件的点转化为区间。询问的是同一深度的点，可以考虑 bfs 序。考虑如果 $y$ 是奇数，显然答案为 $0$；否则询问的点就是 $x$ 的 $\frac{y}{2}$ 级祖先在 $x$ 这一层的后代，再去掉 $x$ 的 $\frac{y}{2}-1$ 级祖先在 $x$ 这一层的后代。考虑怎么去找到询问对应的区间。对于同一棵子树的同一深度，其 bfs 序是连续的。因此可以将询问先存下来，对于每个节点建线段树，存储某一深度的 bfs 序最大值和最小值。线段树合并即可。

时间复杂度分析，处理操作时每次都为 $O(\log n)$，所有线段树合并的总时间复杂度为 $O(n\log n)$，于是总的时间复杂度就为 $O((n+m)\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
using namespace std;
namespace asbt{
namespace cplx{bool begin;}
const int maxn=1e5+5;
const int inf=0x3f3f3f3f;
int n,m,dep[maxn];
int anc[maxn][22];
int bfn[maxn];
queue<int> q;
vector<int> e[maxn];
vector<pii> quj[maxn];
struct{
	int opt,x,y;
	int l1,r1,l2,r2;
}wt[maxn];
il void dfs1(int u,int fa){
	dep[u]=dep[fa]+1;
	anc[u][0]=fa;
	for(int i=1;i<=20;i++){
		anc[u][i]=anc[anc[u][i-1]][i-1];
	}
	for(int v:e[u]){
		if(v==fa){
			continue;
		}
		dfs1(v,u);
	}
}
il int ganc(int u,int k){
	int tmp=0;
	while(k){
		if(k&1){
			u=anc[u][tmp];
		}
		k>>=1,tmp++;
	}
	return u;
}
il void bfs(){
	int cnt=0;
	q.push(1);
	while(q.size()){
		int u=q.front();
		q.pop(),bfn[u]=++cnt;
		for(int v:e[u]){
			if(!bfn[v]){
				q.push(v);
			}
		}
	}
}
int rt[maxn],tot,ls[maxn*40],rs[maxn*40],sum[maxn*40],mn[maxn*40],mx[maxn*40];
il int New(){
	tot++;
	ls[tot]=rs[tot]=sum[tot];
	mn[tot]=inf,mx[tot]=-inf;
	return tot;
}
il void pushup(int id){
	sum[id]=sum[ls[id]]+sum[rs[id]];
}
il void build(int &id,int l,int r){
	id=New();
	if(l==r){
		return ;
	}
	int mid=(l+r)>>1;
	build(ls[id],l,mid);
	build(rs[id],mid+1,r);
}
il void add(int &id,int l,int r,int p,int v){
	if(!id){
		id=New();
	}
	if(l==r){
		mn[id]=min(mn[id],v);
		mx[id]=max(mx[id],v);
		return ;
	}
	int mid=(l+r)>>1;
	if(p<=mid){
		add(ls[id],l,mid,p,v);
	}
	else{
		add(rs[id],mid+1,r,p,v);
	}
	mn[id]=min(mn[ls[id]],mn[rs[id]]);
	mx[id]=max(mx[ls[id]],mx[rs[id]]);
}
il void upd(int &id,int fr,int l,int r,int p){
	id=New();
	if(l==r){
		sum[id]=sum[fr]^1;
		return ;
	}
	int mid=(l+r)>>1;
	if(p<=mid){
		rs[id]=rs[fr];
		upd(ls[id],ls[fr],l,mid,p);
	}
	else{
		ls[id]=ls[fr];
		upd(rs[id],rs[fr],mid+1,r,p);
	}
	pushup(id);
}
il int merge(int p,int q,int l,int r){
	if(!p||!q){
		return p+q;
	}
	if(l==r){
		int x=New();
		mn[x]=min(mn[p],mn[q]);
		mx[x]=max(mx[p],mx[q]);
		return x;
	}
	int mid=(l+r)>>1,x=New();
	ls[x]=merge(ls[p],ls[q],l,mid);
	rs[x]=merge(rs[p],rs[q],mid+1,r);
	mn[x]=min(mn[ls[x]],mn[rs[x]]);
	mx[x]=max(mx[ls[x]],mx[rs[x]]);
	return x;
}
il int query(int id,int L,int R,int l,int r){
	if(l>r||!id){
		return 0;
	}
	if(L>=l&&R<=r){
		return sum[id];
	}
	int mid=(L+R)>>1,res=0;
	if(l<=mid){
		res+=query(ls[id],L,mid,l,r);
	}
	if(r>mid){
		res+=query(rs[id],mid+1,R,l,r);
	}
	return res;
}
il int qmn(int id,int l,int r,int p){
	if(l==r){
		return mn[id];
	}
	int mid=(l+r)>>1;
	return p<=mid?qmn(ls[id],l,mid,p):qmn(rs[id],mid+1,r,p);
}
il int qmx(int id,int l,int r,int p){
	if(l==r){
		return mx[id];
	}
	int mid=(l+r)>>1;
	return p<=mid?qmx(ls[id],l,mid,p):qmx(rs[id],mid+1,r,p);
}
il void dfs2(int u,int fa){
	add(rt[u],1,n,dep[u],bfn[u]);
	for(int v:e[u]){
		if(v==fa){
			continue;
		}
		dfs2(v,u);
		rt[u]=merge(rt[u],rt[v],1,n);
	}
	for(pii v:quj[u]){
		int k=v.fir,id=v.sec;
		if(id>0){
			wt[id].l1=qmn(rt[u],1,n,k);
			wt[id].r1=qmx(rt[u],1,n,k);
		}
		else{
			id=-id;
			wt[id].l2=qmn(rt[u],1,n,k);
			wt[id].r2=qmx(rt[u],1,n,k);
		}
	}
}
namespace cplx{
	bool end;
	il double usdmem(){return (&begin-&end)/1048576.0;}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].pb(v),e[v].pb(u);
	}
	dfs1(1,0),bfs();
	cin>>m;
	for(int i=1,opt,x,y;i<=m;i++){
		cin>>opt>>x;
		wt[i].opt=opt,wt[i].x=x;
		if(opt==2){
			cin>>y;
			wt[i].y=y;
			if((y&1)||!y){
				continue;
			}
			y>>=1;
			if(y>=dep[x]){
				continue;
			}
			x=ganc(wt[i].x,y);
			quj[x].pb(mp(dep[wt[i].x],i));
			x=ganc(wt[i].x,y-1);
			quj[x].pb(mp(dep[wt[i].x],-i));
		}
	}
	mn[0]=inf,mx[0]=-inf;
	dfs2(1,0);
	tot=0;
	build(rt[0],1,n);
	for(int i=1,opt,x,y;i<=m;i++){
		opt=wt[i].opt,x=wt[i].x,y=wt[i].y;
		switch(opt){
			case 1:{
				upd(rt[i],rt[i-1],1,n,bfn[x]);
				break;
			}
			case 2:{
				rt[i]=rt[i-1];
				if(y&1){
					cout<<"0\n";
				}
				else if(!y){
					cout<<query(rt[i],1,n,bfn[x],bfn[x])<<"\n";
				}
				else{
					y>>=1;
					if(y>=dep[x]){
						cout<<"0\n";
					}
					else{
						cout<<query(rt[i],1,n,wt[i].l1,wt[i].l2-1)+query(rt[i],1,n,wt[i].r2+1,wt[i].r1)<<"\n";
					}
				}
				break;
			}
			default:{
				rt[i]=rt[x];
				break;
			}
		}
	}
	return 0;
}
}
int main(){return asbt::main();}
```

---

