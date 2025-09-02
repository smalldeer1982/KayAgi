# Qtree4

## 题目背景

数据范围和 SPOJ 略有不同。

## 题目描述

给出一棵边带权的节点数量为 $n$ 的树，初始树上所有节点都是白色。有两种操作：

- `C x`，改变节点 $x$ 的颜色，即白变黑，黑变白。

- `A`，询问树中最远的两个白色节点的距离，这两个白色节点可以重合（此时距离为 $0$）。

## 样例 #1

### 输入

```
3
1 2 1
1 3 1
7
A
C 1
A
C 2
A
C 3
A```

### 输出

```
2
2
0
They have disappeared.```

# 题解

## 作者：hehezhou (赞：22)

## Qtree4
题意:  
$n$个点，每个点有一个颜色，黑或白  
每次查询最大白点间距离  
带修改  
$n=10^5,q=2*10^5$

(相信大家边分治，LCT等 $O(nlog^2n)$做法都会了)

但是这里有一个~~常数巨大的~~$O(nlogn)$做法

#### 前置芝士
1.全局平衡二叉树(详见2007年论文Qtree问题解法的一些研究)

在一些静态树上查询，修改问题中，LCT能做到~~超大常数的~~$O(logn)$,而树链剖分只能做到$O(log^2n)$，原因何在?

因为LCT整棵树可以看做一个大的~~spaly~~$splay$，仍然可以进行势能分析  
而树剖只能做到单条链最优(局部最优)，但是全局并没有最优

全局平衡二叉树 就完成了把LCT强行静态的过程

轻重链剖分的部分是一样的，但是我们对每一条链建立一颗二叉搜索树  
给每一个点一个权值为轻儿子$size$之和$+1$(自己)，然后每次找重心递归建树

证明每个点的深度为$O(logn)$很简单，每次调到父亲子树大小(包括虚子树)至少翻倍

然后就可以开开心心的以一个$log$的做法做树剖题了


2.把任意一棵树转化为树上距离不变的二叉树

~~相信大家都学过边分治吧，那我就不讲了~~

直接上图

原树  
![](https://cdn.luogu.com.cn/upload/pic/59214.png)

二叉树  
![](https://cdn.luogu.com.cn/upload/pic/59215.png)


其中红点为新建的虚点，红边的边权均为0  
对于每一个点，它的儿子都这样处理，然后就变成有$2n$个点的二叉树了  
~~感受一下，是不是很神奇?~~

-----

#### 正题开始

首先考虑~~最强的树上分治~~链分治  
对于每一条链维护$lca$在这条链上的最大白点距离  
直接做的做法:

以下为了方便，点$x$的轻子树和表示以$x$为根的子树去掉它的重子树，点$x$的轻子树表示以它的一个轻儿子为根的子树，$dfn$表示$dfs$序

对于每一个点$x$维护一个堆，记录$x$的每个轻子树内任意黑点到$x$的距离的最大值，  

线段树维护答案  
对于$dfn$区间$[l,r]$,记录三个值:  
1.$lmax$:所有$dfn$为$[l,r]$点的轻子树和内的所有黑点到$dfn$为$l$的点的距离最大值  
2.$rmax$:同理，表示所有$dfn$为$[l,r]$点的轻子树和内的所有黑点到$dfn$为$l$的点的距离最大值  
3.$ans$:表示所有$dfn[lca]\in [l,r]$ 的黑点的距离最大值

区间合并:线段树上$x$的左儿子为$ls$，右儿子为$rs$

$$ans_x=max\{ans_{ls},ans_{rs},rmax_{ls}+lmax_{rs}+dis(r_{ls},l_{rs})\}$$
$$lmax_x=max\{lmax_{ls},lmax_{rs}+dist(l_{ls},l_{rs})\}$$
$$rmax_x=max\{rmax_{rs},rmax_{ls}+dist(r_{ls},r_{rs})\}$$

边界:点$x$对应区间$[L,L]$ $D_1=$堆内的最大值，$D_2=$堆内的次大值(来自两个不同轻子树)(若没有为$-\infty$)

若$x$为白点
$$lmax_x=rmax_x=max\{0,D_1\}$$
$$ans_x=max(0,D_1,D_1+D_2)$$
(自己到自己，自己到最远的，最远的到次远的)  
否则  
$$lmax_x=rmax_x=D_1$$
$$ans_x=D_1+D_2$$

然后我们发现其实距离堆内维护的就是每个轻儿子线段树顶的$lmax+dist(x,son)$

每条链的答案可以记在另一个堆里，询问时直接查即可

#### 复杂度分析:  
dist(i,j):发现总是在求祖先-后代距离，所以深度减一下$O(1)$  
建树O(n)  
每次修改$O(logn)$条链，每次线段树$O(logn)$,修改距离堆$O(logn)$，修改记答案的堆$O(logn)$总复杂度$O(nlog^2n)$  
每次查询$O(1)$获取堆顶即可  
总复杂度$O(qlog^2n+n)$

~~愚蠢的$log^2$做法到此结束~~

-----
考虑降为一个$log$

首先直接上全局平衡二叉树可以把线段树部分降为单次询问$O(logn)$  
答案堆直接不要了，全局平衡二叉树的$ans$带上轻子树和内的答案即可

然后是距离堆  
我们发现距离堆内的点的个数为轻儿子个数  
所以把它转成二叉树就不用堆来维护了

#### 惊不惊喜，意不意外  

然后就可以一个$log$愉快的过掉了

其实bb了这么一大堆，代码十分好写  

码风丑，大佬轻喷

另外有一个细节，我的二叉查找树结合了线段树的特点，(有点像宗法树)

```
#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
const int inf = 1000000000;
char buf[1 << 20];
char *S = buf, *T = buf;
inline char gc() {
    if(S == T) T = buf + fread(buf, 1, 1 << 20, stdin), S = buf;
    return S == T ? EOF : *S ++;
}
inline int read() {
    int f = 1, c;
    unsigned a = 0;
    for(c = gc(); c != '-' && (c < '0' || c > '9'); c = gc());
    if(c == '-') c = gc(), f = -1;
    for(; c <= '9' && c >= '0'; c = gc()) a = (a << 1) + (a << 3) + (c ^ '0');
    return f == 1 ? a : (~a) + 1;
} // 快速读入
int size[200010], wson[200010], lson[200010], lsize[200010], dep[200010];
struct node {
    int ls, rs, ans, L, R, lmax, rmax, fa;
} t[400010]; //二叉查找树结构体
int nowcnt;
int st[200010], cnt;//记录当前链
int n, m;
vector<pair<int, int> > son[100010];//记录原树
inline void addedge(int u, int v) {
    if(wson[u] == 0) wson[u] = v;
    else lson[u] = v;
}
inline void dfs(int now, int f) {//建立新树
    addedge(now + n, now);
    for(int i = 0; i < son[now].size(); i++)
        if(son[now][i].first == f) {
            son[now].erase(son[now].begin() + i);
            break;
        }
    for(int i = 0; i < son[now].size(); i++) dep[son[now][i].first + n] = dep[now], dep[son[now][i].first] = dep[now] + son[now][i].second, dfs(son[now][i].first, now);//其实此时dep已经可以求出
    for(int i = 1; i < son[now].size(); i++) addedge(son[now][i - 1].first + n, son[now][i].first + n);
    if(son[now].size()) addedge(now, son[now][0].first + n);
}
inline void dfs1(int now) {//树剖的第一次dfs
    size[now] = 1;
    if(wson[now]) dfs1(wson[now]), size[now] += size[wson[now]];
    if(lson[now]) dfs1(lson[now]), size[now] += size[lson[now]];
    if(size[lson[now]] > size[wson[now]]) swap(lson[now], wson[now]);
    lsize[now] = size[lson[now]] + 1; 
}
inline int build(int l, int r) {//对st[l...r]建立二叉树
    if(l == r) return t[st[l]].L = t[st[l]].R = st[l]; //此处有压行(逃)
    int sum = 0, cnt = 0, ans;
    for(int i = l; i <= r; i++) sum += lsize[st[i]];
    sum >>= 1;
    for(int i = l; i <= r; i++) {
        cnt += lsize[st[i]];
        if(cnt >= sum) {//找到重心
            if(i == l) i++;//要是不加，哼哼
            ans = ++nowcnt;
            t[ans].ls = build(l, i - 1);
            t[ans].rs = build(i, r);
            t[t[ans].ls].fa = t[t[ans].rs].fa = ans;
            t[ans].L = st[l], t[ans].R = st[r];
            return ans;
        }
    }
}
int root;
inline void dfs2(int now) {
//st[1...cnt]保存当前链，st[0]为链头的父亲(为0则链头为根)
    st[++cnt] = now;
    if(wson[now]) dfs2(wson[now]);
    else {
        int rt = build(1, cnt);
        if(st[0] == 0) root = rt;
        else t[rt].fa = st[0], t[st[0]].ls = t[st[0]].rs = rt;
        cnt = 0;
    }
    st[0] = now;
    if(lson[now]) dfs2(lson[now]);
}
int col[200010];
inline void up(int x) {
    node &now = t[x];
    if(now.L == now.R) {//叶子节点
        int D = t[now.ls].lmax + dep[lson[x]] - dep[x];//因为是二叉树，所以不会有D2
        now.ans = t[now.ls].ans;
        if(col[x]) now.ans = max(now.ans, now.lmax = now.rmax = max(D, 0));
        else now.lmax = now.rmax = D;
    }
    else {//非叶子节点
        now.lmax = max(t[now.ls].lmax, t[now.rs].lmax + dep[t[now.rs].L] - dep[now.L]);
        now.rmax = max(t[now.rs].rmax, t[now.ls].rmax + dep[now.R] - dep[t[now.ls].R]);
        now.ans = max(max(t[now.ls].ans, t[now.rs].ans), t[now.ls].rmax + t[now.rs].lmax + dep[t[now.rs].L] - dep[t[now.ls].R]);
    }
}
inline void init(int now) {
    if(t[now].L == t[now].R) {
        if(t[now].ls) init(t[now].ls);
    }
    else init(t[now].ls), init(t[now].rs);
    up(now);
}
int main() {
    // freopen("hehezhou.in", "r", stdin);
    // freopen("hehezhou.out", "w", stdout);
    t[0].lmax = t[0].ans = t[0].rmax = -inf;
    n = read();
    for(int i = 1, u, v, w; i < n; i++) u = read(), v = read(), w = read(), son[u].push_back(make_pair(v, w)), son[v].push_back(make_pair(u, w));
    dfs(1, 0);
    nowcnt = n << 1;
    dfs1(n + 1);
    dfs2(n + 1);
    // for(int i = 1; i <= n << 1; i++) printf("%d %d\n", wson[i], lson[i]);
    for(int i = 1; i <= n; i++) col[i] = 1;
    // for(int i = 1; i <= nowcnt; i++) printf("%d : ls = % d, rs = %d, fa = %d, L = %d, R = %d\n", i, t[i].ls, t[i].rs, t[i].fa, t[i].L, t[i].R);
    init(root);
    nowcnt = n;//在这之前表示二叉搜索树节点当前使用量，之后表示白点个数
    m = read();
    for(int i = 1; i <= m; i++) {
        char opt;
        for(opt = gc(); opt != 'C' && opt != 'A'; opt = gc());
        if(opt == 'A') nowcnt ? printf("%d\n", t[root].ans) : puts("They have disappeared.");
        else {
            int v;
            v = read();
            if((col[v] ^= 1) == 0) nowcnt--;//压行大法好
            else nowcnt++;
            for(; v; v = t[v].fa) up(v);
        }
    }
    return 0;//完结撒花
}
```
最后祝大家$rp$++

---

## 作者：xiaoyaowudi (赞：18)

#### 题意

给定一棵树和一个点集，树有边权，可以为负，要求支持两种操作：

+ 点集增删一个点
+ 询问点集里距离最远的两个点，可以是同一个

数据范围 $n\le 10^5,q\le 2\times 10^5$

#### 分析

由于边权可能是负的，所以求直径的贪心做法都是不成立的。

我们考虑 dp 每个点的子树内的最大深度，直接 dp 肯定是不行的。

第一种操作每次只会增删一个点，因此每个点出现的时刻都是一段连续的区间，且区间总个数是 $\mathcal{O}\left(n\right)$ 的。

考虑将 dp 数组放到以时间为值域的线段树上维护，每次 dp 时将线段树直接合并。

直接将区间修改的每个节点上的标记永久化，记录这个点在这段时间区间内的最大深度。

每个点维护以下三个信息：

1. $max\_ans$ ，表示这个节点的所有历史时刻的答案最大值，即 $dp$ 时子树内的直径最大值
2. $tag$ ，表示所有永久化的这个节点上的标记中的最大值，即一个点集在这段时间区间内的最大深度，$dp$ 时子树内的深度最大值
3. $pushdown\_tag$ 表示历史时刻中父链上合并过 $tag$ 的最大值，用于下传的标记

上面这些标记用于模拟 $Ans\leftarrow\max\left(Ans,f_u+f_v-2dep_u\right)$ 这个过程，每次 $pushdown$ 时 $max\_ans\leftarrow \max\left(max\_ans,tag+pushdown\_tag\right)$

每次合并两个节点 $u,v$ 时，把 $u,v$ 的每个节点在另外一棵树中对应的父链信息更新到这个节点上去。

假设此时 $mx$ 表示对应的父链信息

那么 $max\_ans\leftarrow \max\left(max\_ans,mx+tag-2dep\right)$ $pushdown\_tag\leftarrow \max\left(pushdown\_tag,mx-2dep\right)$

#### Code

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
constexpr int N=100010,M=4000010;
typedef long long ll;
constexpr ll inf=2e18;
struct _z{
	int c[2];
	ll mxa,tg,pdtg;
}z[M];int cnt;
void upd(int &u,int cl,int cr,int ql,int qr,ll v){
	if(!u){u=++cnt;z[u].mxa=z[u].tg=z[u].pdtg=-inf;}if(cl>=ql && cr<=qr){z[u].tg=max(z[u].tg,v);return;}
	int mid=(cl+cr)>>1;if(ql<=mid) upd(z[u].c[0],cl,mid,ql,qr,v);if(qr>mid) upd(z[u].c[1],mid+1,cr,ql,qr,v);
}
void add(int u,ll v){z[u].mxa=max(z[u].mxa,z[u].tg+v),z[u].pdtg=max(z[u].pdtg,v);}
void pd(int u){if(z[u].pdtg!=-inf){if(z[u].c[0]) add(z[u].c[0],z[u].pdtg);if(z[u].c[1]) add(z[u].c[1],z[u].pdtg);z[u].pdtg=-inf;}}
int merge(int u,int v,int cl,int cr,ll mxu,ll mxv,ll bs){
	if(!u && !v) return 0;if(!u){add(v,mxu);return v;}if(!v){add(u,mxv);return u;}
	mxu=max(mxu,bs+z[u].tg),mxv=max(mxv,bs+z[v].tg);add(u,mxv);add(v,mxu);pd(u),pd(v);
	z[u].mxa=max(z[u].mxa,z[v].mxa),z[u].tg=max(z[u].tg,z[v].tg);int mid=(cl+cr)>>1;
	z[u].c[0]=merge(z[u].c[0],z[v].c[0],cl,mid,mxu,mxv,bs);z[u].c[1]=merge(z[u].c[1],z[v].c[1],mid+1,cr,mxu,mxv,bs);return u;
}
int rt[N],m,cur[N],ct,n;ll dep[N],ans[N];
vector<pair<int,int> > es[N];
void dfs(int u,int fa){
	for(auto v:es[u]) if(v.first!=fa)
		dep[v.first]=dep[u]+v.second,dfs(v.first,u);
}
void dfs2(int u,int fa){
	for(auto v:es[u]) if(v.first!=fa)
		dfs2(v.first,u),rt[u]=merge(rt[u],rt[v.first],1,m,-inf,-inf,-2ll*dep[u]);
}
char s[5];bool nok[N];
vector<pair<int,int> > ss[N];
void solve(int u,int cl,int cr,ll curm){
	if(u) pd(u);int mid=(cl+cr)>>1;curm=max(curm,z[u].mxa);
	if(cl==cr){ans[cl]=curm;return;}solve(z[u].c[0],cl,mid,curm);solve(z[u].c[1],mid+1,cr,curm);
}
int main(){
	scanf("%d",&n);ct=n;
	for(int i=1;i<=n;++i)
		cur[i]=1;
	for(int i=1,u,v,w;i<n;++i)
		scanf("%d%d%d",&u,&v,&w),es[u].push_back(make_pair(v,w)),es[v].push_back(make_pair(u,w));
	dfs(1,0);
	int q;scanf("%d",&q);
	for(int i=1,t;i<=q;++i){
		scanf("%s",s);
		if(s[0]=='A'){++m;nok[m]=(ct==0);}
		else{
			scanf("%d",&t);
			if(cur[t]){
				--ct;if(cur[t]<=m) ss[t].push_back(make_pair(cur[t],m));
				cur[t]=0;
			}else{
				++ct;cur[t]=m+1;
			}
		}
	}
	if(!m) return 0;
	for(int i=1;i<=n;++i){
		if(cur[i] && cur[i]<=m) ss[i].push_back(make_pair(cur[i],m));
		for(auto v:ss[i])
			upd(rt[i],1,m,v.first,v.second,dep[i]);
	}
	dfs2(1,0);
	solve(rt[1],1,m,0);
	for(int i=1;i<=m;++i){
		if(nok[i]) printf("They have disappeared.\n");
		else printf("%lld\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：Kelin (赞：16)

题意:问树上最远白色点对,带修改

考虑点分治,每次分治时找到每棵子树深度最大的一个白点,用最大的两个统计一下即可.然后建立出点分树 

考虑暴力一点,在每个点开两个堆

第一个堆插入这个重心管辖的一坨树所有白点到分治树上这个点父亲的距离

第二个堆插入所有点分治树上孩子的堆顶,这样我们就可以对于每个分治重心,找到分属两棵子树的深度最大的两个白点,即这个点堆的最大和次大值

注意一开始对于每一个重心要在自己第二个堆里把自己插入(因为自己也是百点,而且没有统计)

然后要记录答案的话就还要再开一个堆

修改就只要再点分树上从自己的重心往根走,然后维护一下那些堆即可,注意判断条件特别多 

复杂度是$O(n\log^2n)$的,修改搞一个可以删除的堆就好了 

但是特别注意,这道题有负边,所以堆空堆顶不是$0$而是$-inf$

然后这题是$[ZJOI2007]Hide$捉迷藏的加强版

一些实现的细节看代码吧(这题还可以树剖,会快一些)

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(int i=a,I=b;i<=I;++i)
#define go(i,u) for(int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool chkmax(T&a,const T&b){return a<b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c^48;
    while(c=gc(),47<c&&c<58)x=(x<<1)+(x<<3)+(c^48);x*=y;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
    if(C>1<<20)Ot();
}
inline void ge(){strcat(sr,"They have disappeared.\n");C+=23;}
const int N=1e5+5,inf=1e9;
typedef int arr[N];
struct eg{int nx,to,w;}e[N<<1];
struct Hp{
    priority_queue<int>s,t;int sz;
    inline void pop(int x){t.push(x);--sz;}
    inline void push(int x){s.push(x);++sz;}
    inline void pre(){while(t.size()&&s.top()==t.top())s.pop(),t.pop();}
    inline int top(){return pre(),sz?s.top():-inf;}
    inline int len(){
    	if(sz<2)return 0;
        int x=top();pop(x);
        int y=top();push(x);
        return max(x+y,0);
    }
    inline void op(int x,int col){col?pop(x):push(x);}
}a[N],b[N],ans;
int n,m,ce,rt,tot,Sum,Top;arr S,fi,fx,fa,Fa,sz,son,col,top,len,dep,vis;
void dfs(int u){
    dep[u]=dep[fa[u]]+(sz[u]=1);
    go(i,u)if(v^fa[u]){
        fa[v]=u,len[v]=len[u]+e[i].w,
        dfs(v),sz[u]+=sz[v];
        if(sz[v]>sz[son[u]])son[u]=v;
    }
}
void dfs(int u,int t){
    top[u]=t;if(son[u])dfs(son[u],t);
    go(i,u)if(v^fa[u]&&v^son[u])dfs(v,v);
}
inline int lca(int u,int v){
    for(;top[u]^top[v];dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]]);
    return dep[u]<dep[v]?u:v;
}
inline int dis(int u,int v){return len[u]+len[v]-(len[lca(u,v)]<<1);}
void gr(int u,int fa){
    fx[u]=0,sz[u]=1;S[++Top]=u;
    go(i,u)if(!vis[v]&&v^fa)gr(v,u),sz[u]+=sz[v],chkmax(fx[u],sz[v]);
    chkmax(fx[u],Sum-sz[u]);if(fx[u]<fx[rt])rt=u;
}
int sol(int u){
    int p=Fa[u],son;vis[u]=1;b[u].push(0); 
    if(p)fp(i,1,Top)a[u].push(dis(p,S[i]));
    go(i,u)if(!vis[v]){
        Sum=sz[v],gr(v,Top=rt=0),Fa[rt]=u,son=sol(rt);
        b[u].push(a[son].top());
    }return ans.push(b[u].len()),u;
}
inline void mdy(int x,int cl){
    int l1=b[x].len(),l2,s1,s2;b[x].op(0,cl);
    if(l1^(l2=b[x].len()))ans.pop(l1),ans.push(l2);
    for(int u=x,p=Fa[x];p;p=Fa[u=p]){
        s1=a[u].top(),a[u].op(dis(p,x),cl),s2=a[u].top();
        if(s1==s2)continue;
        l1=b[p].len();if(s1!=-inf)b[p].pop(s1);if(s2!=-inf)b[p].push(s2);
        l2=b[p].len();if(l1^l2)ans.pop(l1),ans.push(l2);
    }
}
inline void add(int u,int v,int w){e[++ce]=eg{fi[u],v,w};fi[u]=ce;}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    sd(n);int u,v,w;fx[0]=N;tot=n;
    fp(i,2,n)sd(u),sd(v),sd(w),add(u,v,w),add(v,u,w);
    dfs(1),dfs(1,1),Sum=n;gr(1,0),sol(rt);sd(m);
    while(m--){
        char c;while(c=gc(),c<'A');
        if(c=='A')
            tot?we(tot==1?0:ans.top()):ge();
        else{
            sd(u);tot+=col[u]?1:-1;
            col[u]^=1,mdy(u,col[u]);
        }
    }
return Ot(),0;
}

```

---

## 作者：chen_qian (赞：13)


**现在已经按照题解规范修改题解，求过。**

**我认真仔细的检查了每一个空格，真的麻烦管理员大大申四次蒟蒻的题解**

**真的太感谢管理员大大一点一点指出我的小错误，实在是太谢谢了**

以下做法来自 [漆子超 《分治算法在树的路径问题中的应用》](https://wenku.baidu.com/view/a028126e6d175f0e7cd184254b35eefdc9d31575.html)

本题运用线段树和树剖和平衡树实现。

我们可以将树剖视为**基于链的分治算法**。所以，我们可以考虑类似点分治的算法。

假如我们现在查询到一条链。那么树上路径只会分为两种情况。

1. 经过这条链。

2. 不经过。

不经过的话直接递归即可。

那么我们现在就要处理经过的情况。

考虑对于每一条链维护一颗线段树（要动态开点，不然会炸空间）。

为了更方便描述，我们定义 $d_x$ 表示 $x$ 到其子树的一个白点的最长距离。 $dis(i,j)$ 表示节点 $i$ 到 $j$ 的最短距离。

对于线段树上每一个节点，设其维护的区间是 $[l,r]$，我们考虑维护三个值。

1. $lv=\max_{l \leq x \leq r}(dis(l,x)+d_x)$  即下图

![](https://cdn.luogu.com.cn/upload/image_hosting/jj7foptn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

2. $rv=\max_{l \leq x \leq r}(dis(x,r)+d_x)$  即下图

![](https://cdn.luogu.com.cn/upload/image_hosting/zrp5pa3y.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

3. $mv$ 与当前区间重合的所有路径的最长长度

那么我们考虑如何更新父亲节点的信息 （push_up）。

假设节点 $p$ 的左右两个儿子分别是 $ls_p$,$rs_p$ 维护区间是 $[l,r]$ 那么就有 $mid=\frac{l+r}{2}$。

1. $lv_p=\max(lv_{ls_p},dis(l,mid+1)+lv_{rs_p})$ 即下图

![](https://cdn.luogu.com.cn/upload/image_hosting/e9eaf862.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

2. $rv_p=\max(rv_{rs_p},dis(r,mid)+rv_{ls_p})$ 同上

3. $mv_p=\max\left(\max(mv_{ls_p},mv_{rs_p}),rv_{ls_p}+dis(mid,mid+1)+lv_{rs_p}\right)$ 

即下图

![](https://cdn.luogu.com.cn/upload/image_hosting/sge9byyx.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那么就要考虑边界条件。

当一个节点 $p$ 维护区间 $[l,l]$ 时

假如其是白点：

$lv_p=rv_p=\max(0,d_l)$

这时，考虑到经过这个点的路径可能会往下拐。所以我们定义 $d2[x]$ 表示 $x$ 到其子树的一个白点的次长距离。

所以 $mv_p=\max(0,\max(d_l,d_l+d2_l))$。

假如其是黑点：

 $lv_p=rv_p=d_l$

 $mv_p=d_l+d2_l$

那么我们如何来维护次长和最长呢？

首先看如何找到。

显然，要走到某个白点，必然走到其非重儿子的节点。所以直接考虑用那些轻儿子的信息来寻找。

不难发现那些轻儿子又是一条重链的开端，要经过这个重链的开端并往下走最长的距离，那不就是维护这个链的线段树根节点的的 $lv$ 吗？

这样所有长度都得以计算，可以用堆来维护，但是由于修改操作，我们还是要使用平衡树。

修改操作

当一个点被修改时，对于其所处链的信息直接用线段树来修改即可。

关键是在其链之外的信息受到的影响。我们可以很显然的发现，一个点被修改，只会影响其到根节点路径上的节点的信息，所以我们就一个重链，一个重链的往上跳。

注意我们在初始化堆的时候，我们自上至底是用父亲找其儿子的 $lv$ ,现在我们儿子的 $lv$ 改变了，要更新爸爸。所以现在爸爸的堆里删去原本的贡献。然后再修改时把新的贡献加入堆，然后取最大次大更新信息。所以我们要记录一个 $last$ 表示修改时是从哪一条链跳上来的。

上面的思路要求我们维护一个支持删除任意值的堆，有点难以实现，所以我用了  multiset。

具体实现看代码吧。另外注意以上的 $[l,r]$ 都是新编好后的编号，查询节点信息时记得映射回去。

代码如下：

```cpp
#include<bits/stdc++.h>
#define N 100005
#define INF 0x3f3f3f3f
using namespace std;
int n,m,root[N],w[N];
int head[N],idx;
int size[N],fa[N],top[N],seg[N],rev[N],son[N],cnt,len[N],dep[N],sum;
struct edge{
	int v,next,c;
}e[2*N];
void add(int u,int v,int c){
	e[++idx].v=v;
	e[idx].next=head[u];
	head[u]=idx;
	e[idx].c=c;
}
int ls[N<<2],rs[N<<2],mv[N<<2],lv[N<<2],rv[N<<2],tot;
struct myheap{
	multiset<int,greater<int> > s;
	void insert(int v){
		s.insert(v);
	}
	void del(int v){
		multiset<int, greater<int> > :: iterator it=s.lower_bound(v);
		if(it!=s.end()) s.erase(it);
	}
	int top(){
		if(s.empty()) return -INF;
		return *s.begin();
	}
}h[N],ans;
void dfs1(int x,int f){
	fa[x]=f;
	size[x]=1;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==f) continue;
		dep[y]=dep[x]+e[i].c;
		dfs1(y,x);
		size[x]+=size[y];
		if(size[y]>size[son[x]]) son[x]=y;
	}
}
void dfs2(int x){
	if(x==son[fa[x]]) top[x]=top[fa[x]];
	else top[x]=x;
	len[top[x]]++;//记录长度 
	seg[x]=++cnt;
	rev[cnt]=x;
	if(son[x]) dfs2(son[x]);
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==fa[x]||y==son[x]) continue;
		dfs2(y);
	}
}
void push_up(int p,int l,int r){
	int mid=(l+r)>>1;
	lv[p]=max(lv[ls[p]],dep[rev[mid+1]]-dep[rev[l]]+lv[rs[p]]);//注意映射 
	rv[p]=max(rv[rs[p]],dep[rev[r]]-dep[rev[mid]]+rv[ls[p]]);
	mv[p]=max(max(mv[ls[p]],mv[rs[p]]),rv[ls[p]]+dep[rev[mid+1]]-dep[rev[mid]]+lv[rs[p]]);
}
void build(int p,int l,int r){
	if(l==r){
		int x=rev[l];
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].v;
			if(y==fa[x]||y==son[x]) continue;
			h[x].insert(lv[root[y]]+e[i].c);
		}
		int d1=h[x].top();
		h[x].del(d1);
		int d2=h[x].top();
		h[x].insert(d1);
		lv[p]=rv[p]=max(d1,0);
		mv[p]=max(0,max(d1,d1+d2));
		return ;
	}
	int mid=(l+r)>>1;
	if(!ls[p]) ls[p]=++tot;
	build(ls[p],l,mid);
	if(!rs[p]) rs[p]=++tot;
	build(rs[p],mid+1,r);
	push_up(p,l,r);
}
void modify(int p,int l,int r,int x,int tp){
		if(l==r){
			if(x!=tp) h[x].insert(lv[root[tp]]+dep[tp]-dep[x]);
			int d1=h[x].top();
			h[x].del(d1);
			int d2=h[x].top();
			h[x].insert(d1);
			if(w[x]){ 
				lv[p]=rv[p]=d1;
				mv[p]=d1+d2;
			} 
			else{
				lv[p]=rv[p]=max(d1,0);
				mv[p]=max(0,max(d1,d1+d2));
			}
			return;
		}
		int mid=(l+r)>>1;
		if(seg[x]<=mid) modify(ls[p],l,mid,x,tp);
		else modify(rs[p],mid+1,r,x,tp);
		push_up(p,l,r);
}
void change(int x){
	int last=x; //记录上一个top[x] 
	while(x){
		int tp=top[x];
		int p1=mv[root[tp]];
		if(fa[tp]) h[fa[tp]].del(lv[root[tp]]+dep[tp]-dep[fa[tp]]);
		modify(root[tp],seg[tp],seg[tp]+len[tp]-1,x,last);
		int p2=mv[root[tp]];
		if(p1!=p2){//修改操作 
			ans.del(p1);
			ans.insert(p2);
		}
		last=tp;
		x=fa[top[x]];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		add(x,y,w);
		add(y,x,w);
	}
	dfs1(1,0);
	dfs2(1);
	for(int i=n;i>=1;i--){//从后往前，保证子节点的线段树更新完毕。 
		int x=rev[i];
		if(x==top[x]){
			if(!root[x]) root[x]=++tot;
			build(root[x],seg[x],seg[x]+len[x]-1);
			ans.insert(mv[root[x]]);
		}
	}
	scanf("%d",&m);
	sum=n;
	while(m--){
		string op;
		cin>>op;
		int u;
		if(op[0]=='C'){
			scanf("%d",&u);
			w[u]^=1;
			if(w[u]==0) sum++;
			else sum--;
			change(u); 
		}
		else{
			if(sum==0) puts("They have disappeared.");
			else printf("%d\n",ans.top());
		}
	}
	return 0;
}
```













---

## 作者：ecnerwaIa (赞：13)

## P4115 Qtree4

这题怎么能少的了$LCT$做法呢？

一眼看去觉得和动态DP有点像，于是想了半天错误的转移...



------------

可以先去做下 [P4719 【模板】动态dp](https://www.luogu.org/problemnew/show/P4719) 然后再回来做这题，思路差不多。

下面先把变量列出来$:$（其实看懂后就不难...）

### 一定要区分 原树 和 LCT树 的关系

#### 还有就是注意LCT中splay是按照深度排序的，并且每个splay上的节点的子树对应一条链,第一个点代表链的最顶端，最后一个点代表链的最底端。

$len[x]:$因为是边权，所以要下放到点。  
$lmax[x]:$在splay中以$x$为根的以第一个点为端点的最长链  
$rmax[x]:$在splay中以$x$为根的以最后一个点为端点的最长链(
注：这样可以保证之后合并时是连续的，因为x的右儿子的第一个端点在原树上必定挨着x，左儿子的最后一个也是挨着x的并且是x的父亲，因为是边权下放到点，后面会出现左右儿子不同的地方  
$ss[x]:ss[x]$代表splay中以$x$为根的最远白色点对  
$sum[x]:$代表splay中以$x$为根的所有点的权值和，求$lmax,rmax$要用

$w[x]:$点亮就是$0$,否则是$-inf$

$hfir[x]:x$所有虚儿子中的$lmax$最大值（用$multiset$存,$insert,erase$都更新一下，是为了降常数才记下来的）

$hsec[x]:x$所有虚儿子中的$lmax$次大值

$pfir[x]:x$所有虚儿子中$ss$的最大值（另一个$multiset$存）

#### 注：因为虚儿子或者虚实儿子转化时把虚儿子替换都是深度更大的，既然深度更大，我们要记的就是$lmax$才会保证连续，所以存的是$lmax$

上代码
```cpp
// luogu-judger-enable-o2
#include <cstdio>
#include <cstdlib>
#include <set>
using namespace std;
//inline int max(int a,int b){return a>b?a:b;}
const int N=100010,inf=1<<28;
multiset<int>h[N],p[N];
int ch[N][2],fa[N],len[N],lmax[N],rmax[N],ss[N],sum[N],w[N],ans;
int hfir[N],hsec[N],pfir[N];
inline int fir(multiset<int>&s){return s.size()?*s.rbegin():-inf;}//最大 
inline int sec(multiset<int>&s){return s.size()>1?*(++s.rbegin()):-inf;}//次大 
inline bool rt(int x){int y=fa[x];return (ch[y][0]!=x&&ch[y][1]!=x);}
#define lc ch[x][0]
#define rc ch[x][1]
inline void Mo(int x){hfir[x]=fir(h[x]);hsec[x]=sec(h[x]);pfir[x]=fir(p[x]);}
inline void pushup(int x){
    sum[x]=sum[lc]+sum[rc]+len[x];
    int cha=max(w[x],hfir[x]);
    //lc:左儿子,深度都比x小,rc相反 
    int L=max(cha,rmax[lc]+len[x]);
    //要加len[x]因为是下放过来的,那么他上面包含这条边 
    int R=max(cha,lmax[rc]);//下面不含这条边 
    lmax[x]=max(lmax[lc],sum[lc]+len[x]+R);//直接从lc继承,或者是跨越x的右边有亮的灯(没有的话R=-inf,自然不会算进去) 
    rmax[x]=max(rmax[rc],sum[rc]+L);//同上,但是因为边权变点权的缘故,这里要注意len在哪里加,哪里不加 
    //注:lmax不要求左边有亮灯,rmax也是,因为只有两边都有亮灯才会计算在内 即下一步 
    ss[x]=max(rmax[lc]+len[x]+R,lmax[rc]+L);//这个应该不难理解 
    ss[x]=max(max(ss[lc],ss[rc]),ss[x]);
    ss[x]=max(ss[x],hfir[x]+hsec[x]);//所有虚链中最长+次长 
    ss[x]=max(ss[x],pfir[x]);//所有虚链的ss最大值 
    if(w[x]==0)ss[x]=max(max(ss[x],hfir[x]),0);//本身是亮灯,只要有一条链就可以计算 
}inline void rotate(int x){
    int y=fa[x],z=fa[y],k=ch[y][1]==x;
    if(!rt(y))ch[z][ch[z][1]==y]=x;fa[x]=z;
    fa[ch[y][k]=ch[x][k^1]]=y;
    ch[x][k^1]=y;fa[y]=x;pushup(y);
}inline void splay(int x){
    int y,z;
    while(!rt(x)){
        y=fa[x];z=fa[y];
        if(!rt(y))(ch[y][1]==x)^(ch[z][1]==y)?rotate(x):rotate(y);
        rotate(x);
    }pushup(x);
}inline void access(int x){
    for(int y=0;x;x=fa[y=x]){
        splay(x);
        if(rc)h[x].insert(lmax[rc]),p[x].insert(ss[rc]);//rc从实链变虚链,去掉即可 
        if(y)h[x].erase(h[x].find(lmax[y])),p[x].erase(p[x].find(ss[y]));//加上即可 
        Mo(x);rc=y;pushup(x);//Mo(x)是为了降低常数,不用每次pushup算一次fir,sec什么的 
    }
}inline void modify(int x){
    access(x);splay(x);
    w[x]?w[x]=0:w[x]=-inf;//亮灯为0,灭灯为-inf,方便书写,省去判断 
    pushup(x);ans=ss[x];
}int n,T,d[N],nxt[N<<1],to[N<<1],cost[N<<1],tot;
inline void ins(int a,int b,int c){to[++tot]=b;nxt[tot]=d[a];d[a]=tot;cost[tot]=c;}
inline void dfs(int x){//dfs整棵树从下子上建LCT 
    for(int i=d[x];i;i=nxt[i]){
        int u=to[i];
        if(u^fa[x]){
            fa[u]=x;len[u]=cost[i];dfs(u);
            h[x].insert(lmax[u]);p[x].insert(ss[u]);
        }
    }Mo(x);pushup(x);
}inline void print(){for(int i=1;i<=n;++i)printf("lmax:%d rmax:%d ss:%d len:%d\n",lmax[i],rmax[i],ss[i],len[i]);}//debug
int main(){
    scanf("%d",&n);int a,b,c;
    for(int i=0;i<=n;++i)lmax[i]=rmax[i]=ss[i]=-inf;
    for(int i=1;i<n;++i)scanf("%d%d%d",&a,&b,&c),ins(a,b,c),ins(b,a,c);
    dfs(1);ans=ss[1];
    scanf("%d",&T);char s[5];
    while(T--){
        scanf("%s",s+1);
        if(s[1]=='A')ans<0?printf("They have disappeared.\n"):printf("%d\n",ans);//如果存在的话ans至少为0 
        else scanf("%d",&a),modify(a);
    }
    return 0;
}

```

刚开始写了个错误转移，写半天调不出来，后来还是看了网上的大神的题解才慢慢自己摸索出来，也许是这类题做少了吧...

---

## 作者：Enoch006 (赞：12)

**Qtree4 毒瘤树剖解法。**

题意：求带修点颜色下最远白点距离。

路径信息，考虑在 **LCA** 处求解，通过**拼接**快速求解所有可能路径。

由于带修，所以需要将所有节点作为 **LCA** 时的答案存放在一个全局堆里维护。

但是修改一个节点会导致他的多个**祖先结点**的答案发生变化，这样的话空间时间复杂度都是 $O(n^2)$。

考虑优化。

显然以每个点作为 LCA 处统计最大值会储存过多的信息，于是可以在一条**重链**上统计以重链上每个点作为 LCA 时的最大值。

设所有可能路径 $(x,y)$ 满足 $LCA(x,y)=z$ 时，此时有两种情况：

 - 若路径 $(x,y)$ 不经过 $z$ 所在重链，则 $x,y$ 到 $z$ 的的祖先链分别位于 $z$ 的两个**不同**轻子树上，如图：![](https://cdn.luogu.com.cn/upload/image_hosting/ow96a9g0.png)
 - 若若路径 $(x,y)$ 经过 $z$ 所在重链，那么 $x,y$ 到 $z$ 的祖先链分别位于 $z$ 的一棵重子树和 $z$ 的一棵轻子树上，如图：![](https://cdn.luogu.com.cn/upload/image_hosting/rhjzslsl.png)
综上，树链全局最优解可以**以重链为单位整体维护存储**，即**链分治**。

再来看到重链上子树内部**最远白点的拼接**的情况：

由于是拼接操作，很自然地想到用线段树维护，例如最大子段和问题。

设 $z=LCA(x,y)$，$(x,y)$ 相当于所有白点拼接的情况。
 - 维护答案时的操作
	 - 若路径 $(x,y)$ 不经过 $z$ 所在重链：在线段树上区间 $[z,z]$ 这个叶节点上维护它轻子树上的最远与次远白点距离。**注意：这两个点不能在同一颗轻子树！**
	 - 若路径 $(x,y)$ 经过 $z$ 所在重链，那就只需在线段树上维护两个在重链上的点的轻子树内最远白点的距离再拼接起来即可。
- 修改操作的影响：
	- 线段树上的信息仅受子树内白点信息影响，考虑修改一个点 $x$。
	- 这个点会在线段树上影响自己，每条 $x$ 的祖先链上的答案，祖先链链头的父亲的轻子树最大次大值。所以可以依次查找 $x$ 的祖先重链，用链头处的后缀最远白点更新链头父亲的信息。
	 - 首先需要更新一个节点子树中最远+次远白点信息。
	   -  带修，所以需要维护轻子树半群信息，因此不能仅仅维护最大值和次大值，还需用数据结构去维护最值。
	   - **注意：虽然这里说是轻子树半群信息，然而一个节点子树中最远+次远白点信息其实还包含他本身，所以也需维护它自己。**
	   - 可以使用手写堆（由于要删除值）或 STL 里的 multiset 来维护一个节点子树中最远+次远白点信息。
	 - 其次，维护每条 $x$ 的祖先链上的答案，这个在线段树 Pushup 时已经处理好了。
- 查询操作：
	- 需要动态查询所有重链信息的最大值，因此将每条重链的最大值扔进全局最值数据结构里查询。
	- 同样的，这里也用手写堆或 multiset。
	
最后是时间复杂度：显然重剖有一只 $\log$，线段树搭配重剖有一只 $\log$，堆或者 multiset 搭配重剖有一只 $\log$。

所以总时间复杂度为 $O(q\log^2n)$

但是由于我懒，用的 STL，所以常数稍微有点大。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 2000005
#define maxn 1005
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
int n,m,Sum,st1,st2,flagg;
int a[maxm],b[maxm];
struct node{
	int to,nxt,data;
}e[maxm];
int cnt,h[maxm];
void add(int x,int y,int z){
	e[++cnt]=(node){y,h[x],z};
	h[x]=cnt;
}
int fa[maxm],son[maxm],depth[maxm],sz[maxm];
void Dfs1(int x,int fath){
	fa[x]=fath;
	depth[x]=depth[fath]+1;
	sz[x]=1;
	for(int i=h[x];i;i=e[i].nxt){
		int y=e[i].to,z=e[i].data;
		if(y==fath)continue;
		Dfs1(y,x);
		sz[x]+=sz[y];
		a[y]=z;
		if(sz[son[x]]<sz[y])son[x]=y; 
	}
}
int dfn,top[maxm],st[maxm],ed[maxm];
void Dfs2(int x,int tp){
	top[x]=tp;
	st[x]=++dfn;
	if(son[x])Dfs2(son[x],tp);
	for(int i=h[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa[x]||y==son[x])continue;
		Dfs2(y,y);
	}
	if(!son[x])ed[tp]=st[x]; 
}
//重链剖分
struct Seg{
	int l,r,sum,lmx,rmx,mx;
}t[maxm],Ans;
bool flag[maxm];
#define lc k<<1
#define rc k<<1|1
void Pushup(int k){
	t[k].sum=t[lc].sum+t[rc].sum;
	t[k].lmx=max(t[lc].lmx,t[rc].lmx+t[lc].sum);
	t[k].rmx=max(t[rc].rmx,t[rc].sum+t[lc].rmx);
	t[k].mx=max(t[lc].mx,t[rc].mx);
	t[k].mx=max(t[k].mx,t[lc].rmx+t[rc].lmx);
}
void Build(int k,int l,int r){
	t[k]=(Seg){l,r,0,-inf,-inf,-inf};
	if(l==r){
		t[k].sum=b[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(lc,l,mid);
	Build(rc,mid+1,r);
	Pushup(k);
}
void Set(int k,int x){
	if(t[k].l>x||t[k].r<x)return;
	if(t[k].l==t[k].r){
		t[k].lmx=st1+t[k].sum;
		t[k].rmx=st1;
		t[k].mx=st2;
		return;
	}
	Set(lc,x);
	Set(rc,x);
	Pushup(k);
}
void Askmx(int k,int l,int r){
	if(t[k].l>r||t[k].r<l)return;
	//cout<<t[k].l<<" "<<t[k].r<<" "<<t[k].lmx<<" "<<t[k].rmx<<" "<<t[k].mx<<" "<<t[k].sum<<"\n";
	if(t[k].l>=l&&t[k].r<=r){
		Ans.mx=max(Ans.mx,t[k].mx);
		Ans.mx=max(Ans.rmx+t[k].lmx,Ans.mx);
		Ans.rmx=max(t[k].rmx,t[k].sum+Ans.rmx);
		Ans.lmx=max(Ans.lmx,t[k].lmx+Ans.sum); 
		Ans.sum+=t[k].sum;
		return;
	}
	Askmx(lc,l,r);
	Askmx(rc,l,r);
}
struct cmp{
	bool operator ()(const int &x,const int &y)const{
		return x>y;
	}
};
multiset<int,cmp>q[maxm],ans;
void Solve(int x){
	int fx=top[x],xx=x,Ansmx,Anslmx=-inf;
	int f=flag[x];
	flag[x]^=1;Sum=0;Ans=(Seg){0,0,0,-inf,-inf,-inf};
	if(!f)q[x].insert(0),flagg++;
	else q[x].erase(q[x].find(0)),flagg--;
	while(x!=0){
		//cout<<"X:"<<x<<" fx:"<<fx<<"\n";
		if(Anslmx>=-1145141919&&q[x].find(Anslmx)!=ans.end())q[x].erase(q[x].find(Anslmx));
		if(Ans.lmx>=-1145141919)q[x].insert(Ans.lmx);
	//	cout<<"轻子树"<<Anslmx<<" "<<Ans.lmx<<"\n";
		Ans=(Seg){0,0,0,-inf,-inf,-inf};
		if(fx)Askmx(1,st[fx],ed[fx]);
		else Askmx(1,st[1],ed[0]);
		//cout<<"删了的最大值："<<Ans.mx<<"\n";
		Ansmx=Ans.mx,Anslmx=Ans.lmx;
		if(q[x].empty())st1=st2=-inf;//轻子树啥一个白点都没有，显然轻子树最大值为-inf 
		else{
			st1=*q[x].begin();	
			q[x].erase(q[x].find(st1));
			if(q[x].empty())st2=0;
			else st2=*q[x].begin()+st1;
			q[x].insert(st1);
		}
	//	cout<<"St1:"<<st1<<" st2:"<<st2<<"\n";
		Set(1,st[x]);
//		cout<<"x"<<st[xx]<<"\n";
//		Check(1);
		Ans=(Seg){0,0,0,-inf,-inf,-inf};
		//cout<<"询问"<<st[fx]<<" "<<ed[fx]<<"\n";
		if(fx)Askmx(1,st[fx],ed[fx]);
		else Askmx(1,st[1],ed[0]);
		x=fa[fx],fx=top[x];
		//cout<<"删："<<Ansmx<<" 加："<<Ans.mx<<"删："<<Anslmx<<" 加："<<Ans.lmx<<"\n";
		if(ans.find(Ansmx)!=ans.end())ans.erase(ans.find(Ansmx));
		if(Ans.mx>=-1145141919)ans.insert(Ans.mx);
	}
//	cout<<"-------------------------------------------\n";
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>n;
    for(int i=1;i<n;i++){
    	int x,y,z;
    	cin>>x>>y>>z;
    	add(x,y,z);
    	add(y,x,z);
	}
	Dfs1(1,1);
	Dfs2(1,0);
//	for(int i=1;i<=n;i++)cout<<st[i]<<" ";
//	cout<<"\n";
//	for(int i=0;i<=n;i++)cout<<ed[i]<<" ";
//	cout<<"\n";
	for(int i=1;i<=n;i++)b[st[i]]=a[i];
	Build(1,1,n);
	for(int i=1;i<=n;i++)Solve(i);
	cin>>m;
	while(m--){
		char op;
		int x;
		cin>>op;
		if(op=='A'){
			if(flagg==1)cout<<"0\n";
			else if(!ans.empty())cout<<*ans.begin()<<"\n";
			else cout<<"They have disappeared.\n";
		}
		else{
			cin>>x;
			Solve(x);	
		}
	}
    return 0;
}
```

最后好心的我给一个对拍代码吧：

```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 500005
#define maxn 1005
#define inf 0x3f3f3f3f3f3f
using namespace std;
int t,n,m,sum;
int fa[maxm];
void init(){
	for(int i=1;i<=n;i++)fa[i]=i;
}
int Getfa(int x){
	if(fa[x]==x)return x;
	return fa[x]=Getfa(fa[x]);
}
bool Check(int x,int y){
	int fx=Getfa(fa[x]),fy=Getfa(fa[y]);
	return fx==fy;
}
void Merge(int x,int y){
	int fx=Getfa(fa[x]),fy=Getfa(fa[y]);
	fa[fx]=fy;
}
signed main(){
	freopen("in.in","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	n=6,m=10;
	init();
	srand(time(0));
	cout<<n<<"\n";
	for(int i=1;i<n;i++){
		while(1){
			int x=rand()%n+1,y=rand()%n+1,z=rand()%2000-1000;
			if(Check(x,y))continue;
			Merge(x,y);
			cout<<x<<" "<<y<<" "<<z<<"\n";
			break;
		}
	}
	cout<<m<<"\n"; 
	for(int i=1;i<=m;i++){
		int rk=rand()%2;
		if(rk)cout<<"A\n";
		else{
			cout<<"C ";
			int x=rand()%n+1;
			cout<<x<<"\n";
		}
	}
    return 0;
}
```

---

## 作者：TBSF_0207 (赞：10)

# 全局平衡二叉树

本文可能较长，但请相信仅仅是因为较详细的缘故，而不是有多复杂。

这是一种（较）纯正的全局平衡二叉树解法。

刚学这个东西，这里主要借鉴了[hehezhou大佬的题解](https://www.luogu.com.cn/article/xz5zpquh)。该题解末尾提到，作者的全局平衡二叉树融入了**宗法树**的特征，即**数字都存储在叶子结点**里的一种类线段树。那么本篇题解将有所不同，提供一个较为普适的全局平衡二叉树写法，顺便详细展开一些自己关于该结构适用性与这题细节的一些想法（顺便修一下之前题解可能出现的一些笔误）。如有差错，敬请指出。

## 朴素解法

我们都知道（？）存在这么一种解法，对原树进行重链剖分，然后对每条重链维护一个线段树，每个点维护一个堆。线段树内由于是链状结构，可以直接对信息进行合并。堆维护的是每个节点到自己**轻子树**内所有节点的所有距离。这样每次修改需要向上跳 $O(\log n)$ 条链，线段树修改每次为 $O(\log n)$，每次对堆内（仅需修改每条链链顶的父亲）信息的修改为 $O(\log n)$，总共就是 $O(n\log^2 n)$ 的。

这里我们可以展开讲一下线段树的维护（可删堆就不讲了）。对于一个线段树上节点 $u$ 及其代表的区间 $[u_l,u_r]$，它的左儿子 $ls$，右儿子 $rs$，分别维护三个信息。

- $u_{lmax}$ 表示 $[u_l,u_r]$ 内白点到 $u_l$ 的最大距离。
- $u_{rmax}$ 表示 $[u_l,u_r]$ 内白点到 $u_r$ 的最大距离。
- $u_{ans}$ 表示 $[u_l,u_r]$ 内白点两两最大距离。

那么就有合并：

$$
\begin{aligned}
u_{lmax}&=\max\{ls_{lmax},dis(ls_l,rs_l)+rs_{lmax}\}
\\ u_{rmax}&=\max\{rs_{rmax},dis(ls_r,rs_r)+ls_{rmax}\}
\\ u_{ans}&=\max\{ls_{ans},rs_{ans},ls_{rmax}+rs_{lmax}+dis(ls_r,rs_l)\}
\end{aligned}
$$

显然对于一条链上的维护是容易的。

## 全局平衡二叉树的应用

这里我们降复杂度主要有几个阻碍。

1.  一个节点可能有**多个轻儿子**，导致需要开一个堆来维护，这让我们非常不悦。
2.  我们在树剖的时候居然要跳 $O(\log n)$ 次并且每次进行 $O(\log n)$ 的操作，这让我们非常不悦。

第一个的解决方法就是@[hehezhou](https://www.luogu.com.cn/user/67371) 大佬提到的一般树二叉化。

![原树](https://cdn.luogu.com.cn/upload/image_hosting/bkd0bcym.png)

![新二叉树](https://cdn.luogu.com.cn/upload/image_hosting/hit4yi9l.png)

具体地，对于每个节点 $u$，我们将它的每个儿子 $v$ 都复制一个节点 $rep(v)$，然后分类讨论，用 $dep$ 记录距离。如果 $v$ 是第一个儿子，连接 $u\rightarrow rep(v)$ 和 $rep(v)\rightarrow v$。否则，令上一个儿子为 $pre$，连接 $rep(v)\rightarrow rep(pre),v\rightarrow rep(v)$。

这样就完成了一般树向二叉树的转化。

第二个问题的解决方法就是**全局平衡二叉树**。这个东西实际上是一个静态的 LCT，要对一棵树进行重链剖分。对转化成的二叉树，先进行重链剖分。对于每条重链，每次 `build` 求它的加权重心（每个点的点权是轻儿子 $siz+1$），然后递归建树。

树高是 $O(\log n)$ 的，这是全局平衡二叉树的复杂度保证。证明分类讨论即可，无论是跳重边还是跳轻边，子树大小至少都会翻倍。

我们建出了一颗全局平衡二叉树。由于第一个问题提供的解决方法，这棵树上的每一个节点至多有一个轻儿子，这是一个很好的性质。

下面就是和一般全局平衡二叉树和原有题解不同的地方。原有题解由于叶子节点没有儿子，可以直接把轻儿子接在二叉树的任意儿子上变成一个**伪儿子**，目的仅是便利访问和更新信息。但是我不想写宗法树！（这样我们就可以少开一半的节点）于是对每个节点额外开了一个 $u_{vt}$，记录它的**轻（虚）儿子所在二叉搜索树的根**。

接下来的合并也有所不同。对于一个节点 $u$，我们要先合并 $ls,u$，再用合并过的 $u$ 与 $rs$ 合并，具体实现如下：


```cpp
void merge(Node &ls,Node &rs,bool tf){//线段树的合并
	Node u;
	if(!tf)u=ls;
	else u=rs;
	u.lmax=max(ls.lmax,dep[rs.L]-dep[ls.L]+rs.lmax);
	u.rmax=max(rs.rmax,dep[rs.R]-dep[ls.R]+ls.rmax);
	u.ans=max(max(ls.ans,rs.ans),dep[rs.L]-dep[ls.R]+ls.rmax+rs.lmax);
	if(!tf)u.R=rs.R,ls=u;
	else u.L=ls.L,rs=u;
}

u.L=u.R=p;u.ans=u.lmax=u.rmax=(col[p]?0:-INF);
if(u.ch[0])merge(t[u.ch[0]],u,1);//先合并左儿子
if(u.ch[1])merge(u,t[u.ch[1]],0);//再合并右儿子
```

然后就是关于轻儿子的问题。这里我们要对线段树的信息定义做一些稍微的变形，$u_{lmax}$ 表示 $u_l$ 到当前所处集合中的距离最大值，$u_{rmax},u_{ans}$ 同理。这样我们维护的就不再是一条链，但是由于每次合并都是在链首或者链尾进行的，所以只需要保证链首链尾信息的正确性，这个做法就是对的。

我们要怎么维护它们呢？令 $lson_u$ 表示 $u$ 的轻儿子。

$$
\begin{aligned}
D&=u_{vt_{lmax}}+dis(lson_u,u)
\\u_{lmax}&=\max\{u_{lmax},D+dis(u,u_l)\}
\\u_{rmax}&=\max\{u_{rmax},D+dis(u,u_r)\}
\\D_1&=ls_{rmax}+D+dis(u,ls_r)
\\D_2&=rs_{lmax}+D+dis(u,rs_l)
\\u_{ans}&=\max\{u_{ans},D_1,D_2,vt_{ans}\}
\end{aligned}
$$

实现如下：


```cpp
if(u.vt){
		int D=t[u.vt].lmax+dep[lson[p]]-dep[p];
		u.ans=max(u.ans,t[u.vt].ans);
		u.lmax=max(u.lmax,D+dep[p]-dep[u.L]);
		u.rmax=max(u.rmax,D+dep[u.R]-dep[p]);
		int D1=(t[u.ch[0]].rmax)+dep[p]-dep[t[u.ch[0]].R]+D,
			D2=(t[u.ch[1]].lmax)+dep[t[u.ch[1]].L]-dep[p]+D;
		u.ans=max(u.ans,max(D1,D2));
	}
```

另外还要注意叶子节点的分讨，这里就不作详细展开了。

最后需要注意的是，本篇题解着重强调了 $lson_u$ 和 $u_{vt}$ 的区别，希望没有人像我一样混淆。

完整代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,INF=1e9;
int n,head[N],idx,lson[N],rson[N],dep[N];
int siz[N],lsiz[N],root;
struct Node{int ch[2],L,R,fa,lmax,rmax,ans,vt;}t[N];
struct Edge{int v,next,w;}e[N<<1];
void ins(int x,int y,int z){
	e[++idx].v=y;
	e[idx].next=head[x];
	e[idx].w=z;
	head[x]=idx;
}
void ins1(int x,int y){
	if(!lson[y])lson[y]=x;
	else rson[y]=x;
}
void dfs(int u,int fa){
	int lst=0;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v,w=e[i].w;
		if(v==fa)continue;
		dep[v]=dep[u]+w;
		dep[v+n]=dep[u];
		if(!lst){
			ins1(v+n,u);
			ins1(v,v+n);
		}
		else {
			ins1(v+n,lst);
			ins1(v,v+n);
		}
		dfs(v,u);
		lst=v+n;
	}
}
void dfs0(int u){
	siz[u]=1;
	if(lson[u])dfs0(lson[u]);
	siz[u]+=siz[lson[u]];
	if(rson[u])dfs0(rson[u]);
	siz[u]+=siz[rson[u]];
	if(siz[lson[u]]>siz[rson[u]])
		swap(lson[u],rson[u]);
	lsiz[u]=siz[lson[u]]+1;
}
int stk[N],tp,pre[N];
int ef(int l,int r,int &sum){
	int res=r;
	while(l<=r){
		int mid=(l+r)>>1;
		if(pre[mid]>=sum)res=mid,r=mid-1;
		else l=mid+1;
	}
	return res;
}
int build(int l,int r){
	if(l>r)return 0;
	if(l==r)return t[stk[l]].L=t[stk[l]].R=stk[l];
	int sum=((pre[r]-pre[l-1])>>1)+pre[l-1];
	int i=ef(l,r,sum);
	t[stk[i]].ch[0]=build(l,i-1);
	t[stk[i]].ch[1]=build(i+1,r);
	t[t[stk[i]].ch[0]].fa=t[t[stk[i]].ch[1]].fa=stk[i];
	t[stk[i]].L=stk[l],t[stk[i]].R=stk[r];
	return stk[i];
}
void dfs1(int u){
	stk[++tp]=u;
	if(rson[u])dfs1(rson[u]);
	else {
		for(int i=1;i<=tp;i++)pre[i]=pre[i-1]+lsiz[stk[i]];
		int rt=build(1,tp);
		if(!stk[0])root=rt;
		else t[rt].fa=stk[0],t[stk[0]].vt=rt;
		tp=0;
	}
	stk[0]=u;
	if(lson[u])dfs1(lson[u]);
}
int cntw;
bool col[N];
void merge(Node &ls,Node &rs,bool tf){
	Node u;
	if(!tf)u=ls;
	else u=rs;
	u.lmax=max(ls.lmax,dep[rs.L]-dep[ls.L]+rs.lmax);
	u.rmax=max(rs.rmax,dep[rs.R]-dep[ls.R]+ls.rmax);
	u.ans=max(max(ls.ans,rs.ans),dep[rs.L]-dep[ls.R]+ls.rmax+rs.lmax);
	if(!tf)u.R=rs.R,ls=u;
	else u.L=ls.L,rs=u;
}
void pushup(int p){
	Node &u=t[p];
	if(u.L==u.R){
		int D=t[u.vt].lmax+dep[lson[p]]-dep[p];
		u.ans=t[u.vt].ans;
		if(col[p])u.ans=max(u.ans,u.lmax=u.rmax=max(D,0));
		else u.lmax=u.rmax=D;
		return ;
	}
	u.L=u.R=p;u.ans=u.lmax=u.rmax=(col[p]?0:-INF);
	if(u.ch[0])merge(t[u.ch[0]],u,1);
	if(u.ch[1])merge(u,t[u.ch[1]],0);
	if(u.vt){
		int D=t[u.vt].lmax+dep[lson[p]]-dep[p];
		u.ans=max(u.ans,t[u.vt].ans);
		u.lmax=max(u.lmax,D+dep[p]-dep[u.L]);
		u.rmax=max(u.rmax,D+dep[u.R]-dep[p]);
		int D1=(t[u.ch[0]].rmax)+dep[p]-dep[t[u.ch[0]].R]+D,
			D2=(t[u.ch[1]].lmax)+dep[t[u.ch[1]].L]-dep[p]+D;
		u.ans=max(u.ans,max(D1,D2));
	}
}
void init(int p){
	if(!p)return ;
	init(t[p].vt);
	init(t[p].ch[0]),init(t[p].ch[1]);
	pushup(p);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;cntw=n;
	t[0].lmax=t[0].rmax=t[0].ans=-INF;
	for(int i=1;i<n;i++){
		int a,b,c;
		cin>>a>>b>>c;
		ins(a,b,c);
		ins(b,a,c);
	}
	dfs(1,0);
	dfs0(1);
	dfs1(1);
	for(int i=1;i<=n;i++)col[i]=1;
	init(root);
	int Q;cin>>Q;
	while(Q--){
		char c;cin>>c;
		if(c=='C'){
			int x;cin>>x;
			col[x]^=1;
			if(!col[x])cntw--;
			else cntw++;
			for(;x;x=t[x].fa)pushup(x);
		}
		else {
			if(cntw)cout<<t[root].ans<<'\n';
			else cout<<"They have disappeared.\n";
		}
	}
	return 0;
}
```

经过实测，由于每个节点两次合并的常数原因，本做法虽然比原做法少开一半的节点，但在评测时间上并无优势甚至更劣，读者可自行选择。

---

## 作者：Pengzt (赞：7)

**[cnblogs](https://www.cnblogs.com/Pengzt/p/17839453.html)**

**[P4115](https://www.luogu.com.cn/problem/P4115)**

看到单点修改，求全局白色的最远距离，可以使用点分树。

考虑维护这棵点分树，想想树的直径的 dp 求法：$f_u = \max\{f_v + w(u, v)\}$，答案为 $\max(f_v+f_{v'})(v,v'\in \{\text{son}_u\})$，$\{\text{son}_i\}$ 表示 $i$ 的孩子集合。

这时候维护就十分简单了，对于每个点都记录两个可重集，分别表示 $u$ 的儿子的子树的最大深度和 $u$ 的子树内所有点到 $fa_u$ 的距离，$fa_u$ 表示 $u$ 在点分树上的父亲节点，分别记这两个可重集为 $A_i,B_i$，则 $A_i = \{x|x=\max(B_v)\}$。每次直接进行更新即可。最后还需记录一个可重集表示 $\{f_i\}$。

但是 ```multiset``` 速度太慢，有一个小技巧，就是记录两个堆，一个是原集合，一个是懒惰删除的堆，这样速度可以快很多。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector < int >
#define eb emplace_back
#define pii pair < int, int >
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
bool Mbe;
mt19937_64 rng(35);
constexpr int N = 1e5 + 10;
struct Heap {
	priority_queue < int > pq, del;
	void push(int x) {
		pq.push(x);
	}
	void ers(int x) {
		del.push(x);
	}
	int top() {
		while(!del.empty() && pq.top() == del.top()) {
			pq.pop();
			del.pop();
		}
		return pq.top();
	}
	void pop() {
		while(!del.empty() && pq.top() == del.top()) {
			pq.pop();
			del.pop();
		}
		pq.pop();
	}
	int sstop() {
		int tmp = top();
		pop();
		int res = tmp + top();
		push(tmp);
		return res;
	}
	int size() {
		return pq.size() - del.size();
	}
};
struct edge {
	int to, w, nxt;
} e[N << 1];
int n, q, rt, dn;
int dep[N];
int a[N], mx[N], sz[N], vis[N], dfn[N], mi[20][N], fa[N];
int head[N], cnt_e;
void adde(int u, int v, int w) {
	++cnt_e, e[cnt_e].to = v, e[cnt_e].w = w, e[cnt_e].nxt = head[u], head[u] = cnt_e;
}
void dfs(int u, int ff) {
	mi[0][dfn[u] = ++dn] = ff;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == ff) continue;
		dep[v] = dep[u] + e[i].w;
		dfs(v, u);
	}
}
int get(int u, int v) {
	return dfn[u] < dfn[v] ? u : v;
}
int lca(int u, int v) {
	if(u == v) return u;
	if((u = dfn[u]) > (v = dfn[v])) swap(u, v);
	int d = __lg(v - u++);
	return get(mi[d][u], mi[d][v - (1 << d) + 1]);
}
int dis(int u, int v) {
	return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}
void findroot(int u, int ff, int num) {
	sz[u] = 1, mx[u] = 0;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == ff || vis[v]) continue;
		findroot(v, u, num);
		sz[u] += sz[v];
		mx[u] = max(mx[u], sz[v]);
	}
	mx[u] = max(mx[u], num - sz[u]);
	if(mx[u] < mx[rt]) rt = u;
}
Heap Ans, tx[N], di[N]; // 答案; 所有儿子的子树的最大深度; 子树内所有点到其父亲的距离.
void getdep(int u, int fath, int anc) {
	di[anc].push(dis(u, fa[anc]));
	sz[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == fath || vis[v]) continue;
		getdep(v, u, anc);
		sz[u] += sz[v];
	}
}
void divide(int u) {
	vis[u] = 1;
	tx[u].push(0);
	getdep(u, 0, u);
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(vis[v]) continue;
		rt = 0;
		findroot(v, u, sz[v]);
		fa[rt] = u;
		int tmp = rt;
		divide(rt);
		tx[u].push(di[tmp].top());
	}
	if(tx[u].size() >= 2) Ans.push(tx[u].sstop());
}
void ers(int u) {
	if(tx[u].size() >= 2) Ans.ers(tx[u].sstop());
}
void push(int u) {
	if(tx[u].size() >= 2) Ans.push(tx[u].sstop());
}
void update0(int u) {
	ers(u);
	tx[u].push(0);
	push(u);
	for(int x = u; fa[x]; x = fa[x]) {
		ers(fa[x]);
		if(di[x].size()) tx[fa[x]].ers(di[x].top());
		di[x].push(dis(u, fa[x]));
		tx[fa[x]].push(di[x].top());
		push(fa[x]);
	}
}
void update1(int u) {
	ers(u);
	tx[u].ers(0);
	push(u);
	for(int x = u; fa[x]; x = fa[x]) {
		ers(fa[x]);
		tx[fa[x]].ers(di[x].top());
		di[x].ers(dis(u, fa[x]));
		if(di[x].size()) tx[fa[x]].push(di[x].top());
		push(fa[x]);
	}
}
bool Med;
int main() {
	fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
//	freopen("data.in", "r", stdin);
//	freopen("myans.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i < n; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		adde(u, v, w);
		adde(v, u, w);
	}
	dfs(1, 0);
	for(int i = 1; i <= __lg(n); ++i)
		for(int j = 1; j + (1 << i) - 1 <= n; ++j)
			mi[i][j] = get(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
	mx[0] = N;
	findroot(1, 0, n);
	divide(rt);
	cin >> q;
	for(int qi = 1, tot = n; qi <= q; ++qi) {
		char opt;
		cin >> opt;
		if(opt == 'C') {
			int x;
			cin >> x;
			a[x] ^= 1;
			if(a[x]) update1(x), --tot;
			else update0(x), ++tot;
		} else {
			if(!tot) cout << "They have disappeared.\n";
			else if(tot == 1) cout << 0 << "\n";
			else cout << max(Ans.top(), 0) << "\n";
		}
	}
	cerr << TIME << "ms\n";
	return 0;
}
```

---

## 作者：灵乌路空 (赞：7)

点分树，堆

原题面：[Luogu](https://www.luogu.com.cn/problem/P4115)。

## 简述

>给定一棵 $n$ 个节点的的树，边有边权。初始树上所有节点都是白色。给定 $m$ 次操作：  
>1. 反转给定点的颜色。  
>2. 询问树上最远的两个白色节点的距离，两点可以重合（距离为 0）。  
>
>$1\le n\le 10^5$，$1\le m\le 2\times 10^5$，$-10^3\le$ 边权 $\le 10^3$。  
>1S，512MB。  

## 分析

预处理 $\operatorname{lca}$ 后即可快速求得两点距离，先考虑如何处理静态问题。可以考虑在点分治的过程中对每个节点都维护一个堆，储存分治块内该点子树节点中的所有白点到重心的距离，使用其中的分属**不同分治块**的最大值与次大值拼接路径求最大值即可，单次询问时间复杂度 $O(n\log^2 n)$ 级别。  

考虑动态问题，把上述过程放到点分树上自底向下进行。对于每个节点预处理两个堆：$t_1$ 维护该点**子树内**所有白点到**父亲**的距离（对应点分治中求得各点到重心最大值），$t_2$ 维护所有**儿子**的 $t_1$ 的最大值（对应维护分属**不同分治块**的最值过程）。特别地，若 $u$ 为白点，则 $0 \in t_1(u)$。即有：  

$$\begin{aligned}
  t_1(u) &= \{\operatorname{dis}(u, v)\mid v\in \operatorname{subtree}(u) , \operatorname{color}_v\texttt{is white}\}\\
  t_2(u) &= \begin{cases}
     \{\max(t_1(v))\mid v \in \operatorname{son}(u)\} \cup \{0\}&\operatorname{color}(u)\texttt{ is white}\\
    \{\max(t_1(v))\mid v \in \operatorname{son}(u)\} &\text{otherwise}
  \end{cases}\\
\end{aligned}$$

同时处理一个堆 $all$，储存所有节点路径拼接后的值，即有 $all = \{ \max(t_2(u)) + \operatorname{secmax}(t_2(u))\}$，每次询问的答案即 $\max(all)$。初始时所有节点均为白点，在建立点分树时对每个节点初始化上述三个堆即可，复杂度 $O(n\log^2 n)$ 级别。  
对于修改操作，自指定节点向上跳父亲，在 $t_1$ 中添加/删除父亲到指定节点的链，并更新父亲的 $t_2$ 与 $all$ 即可，单次修改复杂度 $O(\log^2 n)$ 级别。注意添加/删除指定节点 $t_2$ 中的 $0$。上述过程中的堆需要支持插入、删除、查询最大值、次大值，可以使用 `mulitiset` 或堆+懒惰删除实现。  

特别地，此题的树上可能有负权边且允许白点重合。答案要对 $0$ 取最大值。

总时间复杂度是常数极大的 $O((n + m)\log^2 n)$。  
然后是一些卡常技巧：树剖求 $\operatorname{lca}$ 常数较小，实际表现比 RMQ 更优；`multiset` 常数过大不如堆 + 懒惰删除。但还是被色批 OJ 卡常了呜呜，下面的代码只能在 Luogu 上过。

## 代码

```cpp
//知识点：点分树
/*
By:Luckyblock
*/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <queue>
#define LL long long
const int kN = 1e5 + 10;
const int kM = kN << 1;
const int kInf = 1e9 + 2077;
//=============================================================
int n, m, e_num, head[kN], v[kM], w[kM], ne[kM], dep[kN];
int cnt, root, sumsz, sz[kN], maxsz[kN], newfa[kN];
bool vis[kN], val[kN];
//=============================================================
inline int read() {
  int f = 1, w = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + (ch ^ '0');
  return f * w;
}
void Chkmax(int &fir_, int sec_) {
  if (sec_ > fir_) fir_ = sec_;
}
void Chkmin(int &fir_, int sec_) {
  if (sec_ < fir_) fir_ = sec_;
}
void AddEdge(int u_, int v_, int w_) {
  v[++ e_num] = v_, w[e_num] = w_;
  ne[e_num] = head[u_];
  head[u_] = e_num;
}
namespace Cut {
  int fa[kN], son[kN], dep[kN], dis[kN], size[kN], top[kN];
  void Dfs1(int u_, int fa_) {
    fa[u_] = fa_;
    size[u_] = 1;
    dep[u_] = dep[fa_] + 1;
    for (int i = head[u_]; i; i = ne[i]) {
      int v_ = v[i], w_ = w[i];
      if (v_ == fa_) continue ;
      dis[v_] = dis[u_] + w_;
      Dfs1(v_, u_);
      if (size[v_] > size[son[u_]]) son[u_] = v_;
      size[u_] += size[v_];
    }
  }
  void Dfs2(int u_, int top_) {
    top[u_] = top_;
    if (son[u_]) Dfs2(son[u_], top_);
    for (int i = head[u_]; i; i = ne[i]) {
      int v_ = v[i];
      if (v_ == fa[u_] or v_ == son[u_]) continue ;
      Dfs2(v_, v_);
    }
  }
  int Lca(int u_, int v_) {
    for (; top[u_] != top[v_]; u_ = fa[top[u_]]) {
      if (dep[top[u_]] < dep[top[v_]]) {
        std::swap(u_, v_);
      }
    }
    return dep[u_] < dep[v_] ? u_ : v_;
  }
  int Dis(int u_, int v_) {
    return dis[u_] + dis[v_] - 2 * dis[Lca(u_, v_)];
  }
  void Prepare() {
    Dfs1(1, 0), Dfs2(1, 1);
  }
}
struct Heap { //懒惰删除堆
  std::priority_queue <int> heap, delt;
  void Insert(int val_) {
    heap.push(val_);
  }
  void Erase(int val_) {
    delt.push(val_);
  }
  int Size() {
    return heap.size() - delt.size(); 
  }
  void Update() {
    while (delt.size() && heap.top() == delt.top()) {
      heap.pop(); 
      delt.pop();
    }
  }
  int Top() {
    Update();
    return Size() ? heap.top() : -kInf;
  }
  int Sectop() {
    int t1 = Top(), t2;
    Update(), heap.pop();
    t2 = Top();
    Insert(t1);
    return t2;
  }
  int Get() {
    if (Size() >= 2) return Top() + Sectop();
    if (Size() == 1) return std::max(Top(), 0);
    return -kInf;
  }
} all, dis[kN], disfa[kN];
void AddAll(int pos_) {
  if (dis[pos_].Size() >= 2) all.Insert(dis[pos_].Get());
}
void DeleteAll(int pos_) {
  if (dis[pos_].Size() >= 2) all.Erase(dis[pos_].Get());
}
void CalcSize(int u_, int fa_) { //找重心
  sz[u_] = 1, maxsz[u_] = 0;
  for (int i = head[u_]; i; i = ne[i]) {
    int v_ = v[i];
    if (v_ == fa_ || vis[v_]) continue;
    CalcSize(v_, u_);
    Chkmax(maxsz[u_], sz[v_]);
    sz[u_] += sz[v_];
  }
  Chkmax(maxsz[u_], sumsz - sz[u_]);
  if (maxsz[u_] < maxsz[root]) root = u_;
}
void CalcDis(int u_, int fa_, int dis_, int pos_) {
  disfa[pos_].Insert(dis_); //预处理
  for (int i = head[u_]; i; i = ne[i]) {
    int v_ = v[i], w_ = w[i];
    if (v_ == fa_ || vis[v_]) continue;
    CalcDis(v_, u_, dis_ + w_, pos_);
  }
}
void Dfs(int u_, int fa_) { //建立点分树
  vis[u_] = true;
  for (int i = head[u_]; i; i = ne[i]) {
    int v_ = v[i], w_ = w[i];
    if (v_ == fa_ || vis[v_]) continue;
    sumsz = sz[v_], root = 0, maxsz[root] = kN;
    CalcSize(v_, u_);
    CalcDis(v_, u_, w_, root);

    newfa[root] = u_;
    dis[u_].Insert(disfa[root].Top()); //预处理
    CalcSize(root, 0), Dfs(root, 0);
  }
  dis[u_].Insert(0);
  AddAll(u_);
}
void Add(int pos_) { //添加白点
  ++ cnt;
  DeleteAll(pos_); //以当前节点为一端点的情况
  dis[pos_].Insert(0);
  AddAll(pos_);
  for (int now_ = pos_; newfa[now_]; now_ = newfa[now_]) { 
    int f = newfa[now_], d = Cut::Dis(pos_, f);
    DeleteAll(f); //削除更新前的贡献
    if (disfa[now_].Size()) dis[f].Erase(disfa[now_].Top());

    disfa[now_].Insert(d); //插入父亲到指定节点的链
    
    if (disfa[now_].Size()) dis[f].Insert(disfa[now_].Top());
    AddAll(f); //更新贡献
  }
}
void Delete(int pos_) { //删除白点
  -- cnt;
  DeleteAll(pos_);
  dis[pos_].Erase(0);
  AddAll(pos_);
  for (int now_ = pos_; newfa[now_]; now_ = newfa[now_]) { 
    int f = newfa[now_], d = Cut::Dis(pos_, f);
    DeleteAll(f); //削除更新前的贡献
    if (disfa[now_].Size()) dis[f].Erase(disfa[now_].Top());

    disfa[now_].Erase(d); //插入父亲到指定节点的链

    if (disfa[now_].Size()) dis[f].Insert(disfa[now_].Top());
    AddAll(f); //更新贡献
  }
}
void Modify(int pos_) { //单点修改，更新点分树上该点到根路径上各点的 子树信息
  val[pos_] ? Add(pos_) : Delete(pos_);
  val[pos_] ^= 1;
}
int Query() {
  return std::max(all.Top(), 0);
}
//=============================================================
int main() {
  cnt = n = read();
  for (int i = 1; i < n; ++ i) {
    int u_ = read(), v_ = read(), w_ = read();
    AddEdge(u_, v_, w_), AddEdge(v_, u_, w_);
  }
  Cut::Prepare();
  sumsz = n, root = 0, maxsz[root] = kN;
  CalcSize(1, 0), CalcSize(root, 0), Dfs(root, 0);

  m = read();
  for (int i = 1; i <= m; ++ i) {
    char opt[5]; scanf("%s", opt + 1);
    if (opt[1] == 'C') {
      Modify(read());
    } else {
      if (!cnt) {
        printf("They have disappeared.\n");
      } else {
        printf("%d\n", cnt == 1 ? 0 : Query());
      }
    }
  }
  return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：5)

来个严格单 $\log n$ 做法。

首先建出静态 Top tree。

如何建出这个玩意呢？

仿照全局平衡二叉树的建法，先重链剖分一下，然后对于一个点的所有轻儿子全部收缩成一个簇，然后按照簇的大小带权分治，每次把左右区间的簇 rake 成一个，然后 rake 到重儿子所在簇上，再对重链按照簇大小（子树大小减去重儿子子树大小）带权分治，每次把左右区间 compress 成一个簇，再向上递归。由于这个过程中总是重量平衡的，所以建立出来的 Top tree 树高是 $O(\log n)$。

然后在 Top tree 上 dp。

具体而言，每个簇包含的点信息就是代表的联通子图中除了界点外的所有点，然后记录簇内白点最大距离与白点到两个界点最大距离，每次 compress 或者 rake 时将被删去的界点的信息合并到簇内，并将两个簇的路径合并起来，再将这个簇与被删去的界点关联起来，关于这个点的修改就从这个簇开始向上更新父亲的 dp 数组。

总复杂度是 $O(q \log n + n \log n)$ 的。

```cpp
#include<bits/stdc++.h>
#define int long long
//#define lowbit(x) (x&(-x))
using namespace std;
const int maxn = 2e5+114;
const int inf = 1e13+114;
struct node{
	int u,v,ans,maxu,maxv,id,dis;//簇内答案（不包括界点） 到界定的距离最大的白点的距离
	char type;
	//u 在上面 v 在下面
}cluster[maxn];
int n,m,col[maxn];
int pos[maxn],fa[maxn],ls[maxn],rs[maxn];
char type[maxn];//P 是边点 C 是 compress 点 R 是 rake 点
int root=1;//根簇
void compress(node x,node y,node &w){
    if(x.id==0||y.id==0) assert(0);
	//x 在上面 y 在下面
	w.ans=w.maxu=w.maxv=-inf;
	w.u=x.u,w.v=y.v;
	w.dis=x.dis+y.dis;
	w.ans=max(x.ans,y.ans);
	w.ans=max(w.ans,x.maxv+y.maxu);
    w.maxu=max(x.maxu,y.maxu+x.dis);
    w.maxv=max(x.maxv+y.dis,y.maxv);
    if(col[x.v]==0){
        w.ans=max(w.ans,max(x.maxv,y.maxu));
        w.ans=max(w.ans,0*1ll);
        w.maxu=max(w.maxu,x.dis);
        w.maxv=max(w.maxv,y.dis);
    }
	pos[x.v]=w.id;
	fa[x.id]=fa[y.id]=w.id;
	ls[w.id]=x.id;
	rs[w.id]=y.id;
	//cout<<"compress"<<w.u<<" "<<w.v<<" "<<w.ans<<'\n';
	w.type='C';
	root=w.id;
}
void rake(node x,node y,node &w){
    if(x.id==0||y.id==0) assert(0);
	//把 x rake 到 y 上
	w.ans=w.maxu=w.maxv=-inf;
	w.u=y.u,w.v=y.v;
	w.dis=y.dis;
	w.ans=max(x.ans,y.ans);
	w.ans=max(w.ans,x.maxu+y.maxu);
    w.maxu=max(x.maxu,y.maxu);
    w.maxv=max(x.maxu+y.dis,y.maxv);
    if(col[x.v]==0){
        w.ans=max(w.ans,max(x.maxv,y.maxu+x.dis));
        w.ans=max(w.ans,0*1ll);
        w.maxu=max(w.maxu,x.dis);
        w.maxv=max(w.maxv,x.dis+y.dis);
    }
	pos[x.v]=w.id;
	fa[x.id]=fa[y.id]=w.id;
	ls[w.id]=x.id;
	rs[w.id]=y.id;
	//cout<<"rake"<<w.u<<' '<<w.v<<' '<<w.ans<<'\n';
	w.type='R';
	root=w.id;
}
void update(int u){
    if(u==0) return ;
    if(cluster[u].type=='C'){
        compress(cluster[ls[u]],cluster[rs[u]],cluster[u]);
        update(fa[u]);
    }else{
        rake(cluster[ls[u]],cluster[rs[u]],cluster[u]);
        update(fa[u]);
    }
}
vector< pair<int,int> > E[maxn];
int father_pos[maxn];//一个点到其父亲的边的簇编号
int father[maxn];
int son[maxn],sz[maxn],tot;
vector<int> st[maxn];//重链上的点存到链顶
void dfs1(int u){
	sz[u]=1;
	for(pair<int,int> nxt:E[u]){
	    int v=nxt.first,w=nxt.second;
		if(v==father[u]) continue;
		father[v]=u;
		father_pos[v]=++tot;
		cluster[tot].u=u,cluster[tot].v=v,cluster[tot].id=tot,cluster[tot].dis=w,cluster[tot].ans=cluster[tot].maxu=cluster[tot].maxv=-inf;
		dfs1(v);
		if(sz[v]>sz[son[u]]) son[u]=v;
		sz[u]+=sz[v];
	}
}
void dfs2(int u,int tp){
	st[tp].push_back(u);
	if(son[u]!=0) dfs2(son[u],tp);
	for(pair<int,int> nxt:E[u]){
	    int v=nxt.first;
		if(v==father[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
//需要虚拟节点 n+1 作为根 只在第一次 dfs 以及最后根簇时调用
vector<int> vec[maxn];
vector<int> pre[maxn];
int solve(int l,int r,int u){
    if(l>r) return 0;
	if(l==r) return father_pos[vec[u][l]];
	int L=l,R=r;
	while(L+1<R){
		int mid=(L+R)>>1;
		if((pre[u][mid]-pre[u][l-1])*2<=(pre[u][r]-pre[u][l-1])) L=mid;
		else R=mid;
	}
	int mid=L;
	int lson=solve(l,mid,u);
	int rson=solve(mid+1,r,u);
	int res=++tot;
	cluster[tot].id=tot;
	rake(cluster[lson],cluster[rson],cluster[res]);
	return res;
}
int calc(int l,int r,int u){
    if(l>r) return 0;
    if(l==r) return father_pos[vec[u][l]];
	int L=l,R=r;
	while(L+1<R){
		int mid=(L+R)>>1;
		if((pre[u][mid]-pre[u][l-1])*2<=(pre[u][r]-pre[u][l-1])) L=mid;
		else R=mid;
	}
	int mid=L;
	int lson=calc(l,mid,u);
	int rson=calc(mid+1,r,u);
	int res=++tot;
    cluster[tot].id=tot;
	compress(cluster[lson],cluster[rson],cluster[res]);
	return res;
}
void dfs3(int u){
	for(int x:st[u]){
        if(son[x]==0) continue;
		pre[x].push_back(0);
		vec[x].push_back(0);
		for(pair<int,int> nxt:E[x]){
		    int v=nxt.first;
			if(v!=son[x]&&v!=father[x]){
				dfs3(v);
				//收缩 (x,v) 一个簇
				vec[x].push_back(v);
			}
		}
		//在对这些轻儿子簇按中点分治的方法合并起来
		for(int i=1;i<=vec[x].size()-1;i++){
			pre[x].push_back(pre[x][i-1]+sz[vec[x][i]]);
		}
		int rt=solve(1,vec[x].size()-1,x);
		if(rt!=0){
		    tot++;
		    cluster[tot].id=tot;
            rake(cluster[rt],cluster[father_pos[son[x]]],cluster[tot]);
            father_pos[son[x]]=tot;//rake 到重链上		    
		}
	}
	vec[u].clear();
	pre[u].clear();
	pre[u].push_back(0);
	vec[u].push_back(0);
	for(int x:st[u]){
		vec[u].push_back(x);
	}
	for(int i=1;i<=vec[u].size()-1;i++){
		pre[u].push_back(pre[u][i-1]+sz[father[vec[u][i]]]-sz[vec[u][i]]);
	}
	if(u!=1) father_pos[u]=calc(1,vec[u].size()-1,u);//把重链上的边 compress 成一条
	else father_pos[u]=calc(2,vec[u].size()-1,u);
	E[u].clear();
	E[u].push_back(make_pair(father[u],0));
	return ;
}
int sum;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=2;i<=n;i++){
        int u,v,c;
        cin>>u>>v>>c;
        E[u].push_back(make_pair(v,c));
        E[v].push_back(make_pair(u,c));
    }
    cin>>m;
    dfs1(1);
    dfs2(1,1);
    dfs3(1);
    while(m--){
        char opt;
        cin>>opt;
        if(opt=='C'){
            int x;
            cin>>x;
            sum-=col[x];
            col[x]^=1;
            sum+=col[x];
            update(pos[x]);
        }else{
            if(sum<n) cout<<max(max(cluster[root].ans,max((col[cluster[root].u]==0?max(0*1ll,cluster[root].maxu):-inf),(col[cluster[root].v]==0?max(0*1ll,cluster[root].maxv):-inf))),((col[cluster[root].u]==0&&col[cluster[root].v]==0)?cluster[root].dis:-inf))<<'\n';
            else cout<<"They have disappeared.\n";
        }
    }
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：4)

在点分树的每个点上维护 $C_u$ 表示 $u$ 子树内的点到 $fa_u$ 的距离集合，

$P_u$ 表示 $u$ 到其每个子树的距离最大值集合。特别地，若 $u$ 是白点，还要在 $P_u$ 中加入 $0$，

即 $P_u=\begin{cases}\{\max\{C_v\}|fa_v=u\}&u\text{ 是黑点}\\\{\max\{C_v\}|fa_v=u\}\cup\{0\}&u\text{ 是白点}\end{cases}$。

维护 $S$ 表示以每个点为 LCA 的最长路径长度集合，即 $S=\{\max\{P_u\}+\operatorname{secondmax}\{P_u\}\}$。

反转点 $u$ 的颜色时更新 $u$ 到根上的 $C_i$，用 $C_i$ 更新 $P_{fa_i}$，用 $P_{fa_i}$ 更新 $S$。

一共要更新 $O(\log n)$ 个 集合，用 `multiset` 维护这些集合，总复杂度 $O(m\log^2n)$。

然后你就会发现这东西常数太大很难过题，所以用可删堆代替 `multiset`。

具体地，维护原堆 $S$ 和删除堆 $D$，删除 $x$ 时在 $D$ 中加入 $x$，

查询堆顶时若两堆堆顶相同就一直弹出两堆堆顶，直到两堆堆顶不同时输出 $S$ 的堆顶即可。

```cpp
#include <queue>
#include <cstdio>
using namespace std;
struct E
{
    int v, w, t;
} e[200050];
struct multiset
{
    priority_queue<int> S, D;
    int R() { return S.size() - D.size(); }
    void I(int x) { S.push(x); }
    void O(int x) { D.push(x); }
    int T()
    {
        if (!R())
            return 1e9;
        while (D.size() && S.top() == D.top())
            S.pop(), D.pop();
        return S.top();
    }
    int C()
    {
        if (R() < 2)
            return 1e9;
        int x = T(), y;
        O(x);
        y = T();
        I(x);
        return x + y;
    }
} S, C[100050], P[100050];
bool b[100050];
char V;
int n, m, c, R, pR, z, o, a[100050], s[100050], g[100050], d[100050], k[100050], f[32][200050], H[100050], h[100050];
void A(int u, int v, int w)
{
    e[++c] = {v, w, h[u]};
    h[u] = c;
}
void D(int u)
{
    ++o;
    k[f[0][o] = u] = o;
    for (int i = h[u], v; i; i = e[i].t)
        if (!d[v = e[i].v])
        {
            d[v] = d[u] + 1;
            H[v] = H[u] + e[i].w;
            D(v);
            f[0][++o] = u;
        }
}
int L(int x, int y)
{
    if ((x = k[x]) > (y = k[y]))
        swap(x, y);
    int k = __lg(y - x + 1);
    return d[f[k][x]] < d[f[k][y - (1 << k) + 1]] ? f[k][x] : f[k][y - (1 << k) + 1];
}
int D(int x, int y) { return H[x] + H[y] - (H[L(x, y)] << 1); }
void X(int u, int k, int t)
{
    s[u] = 1;
    int p = 0;
    for (int i = h[u], v; i; i = e[i].t)
        if (!b[v = e[i].v] && v != k)
            X(v, u, t), s[u] += s[v], p = max(p, s[v]);
    if (pR > (p = max(p, t - s[u])))
        R = u, pR = p;
}
void B(int u, int k)
{
    b[u] = 1;
    for (int i = h[u], v; i; i = e[i].t)
        if (!b[v = e[i].v] && v != k)
            pR = 1e9, X(v, u, s[v]), X(R, 0, s[v]), B(R, g[R] = u);
}
int main()
{
    S.I(0);
    scanf("%d", &n);
    for (int i = 1, u, v, w; i < n; ++i)
        scanf("%d%d%d", &u, &v, &w), A(u, v, w), A(v, u, w);
    D(d[1] = 1);
    for (int i = 1; 1 << i <= o; ++i)
        for (int j = 1; j + (1 << i) - 1 <= o; ++j)
            f[i][j] = d[f[i - 1][j]] < d[f[i - 1][j + (1 << i - 1)]] ? f[i - 1][j] : f[i - 1][j + (1 << i - 1)];
    pR = 1e9;
    X(1, 0, n);
    X(R, 0, n);
    B(R, 0);
    for (int i = 1; i <= n; ++i)
    {
        for (int u = i; u; u = g[u])
            if (g[u])
                C[u].I(D(g[u], i));
        P[i].I(0);
    }
    for (int i = 1; i <= n; ++i)
        if (g[i])
            P[g[i]].I(C[i].T());
    for (int i = 1; i <= n; ++i)
        if (P[i].R() >= 2)
            S.I(P[i].C());
    scanf("%d", &m);
    z = n;
    for (int i = 0, x, p, q; i < m; ++i)
    {
        scanf(" %c", &V);
        if (V == 'C')
        {
            scanf("%d", &x);
            p = P[x].C();
            if (a[x])
                P[x].I(0);
            else
                P[x].O(0);
            q = P[x].C();
            if (p != q)
            {
                if (p != 1e9)
                    S.O(p);
                if (q != 1e9)
                    S.I(q);
            }
            for (int u = x, o, p, q, c, d; u; u = g[u])
                if (g[u])
                {
                    o = D(g[u], x);
                    c = P[g[u]].C();
                    p = C[u].T();
                    if (a[x])
                        C[u].I(o);
                    else
                        C[u].O(o);
                    q = C[u].T();
                    if (p != q)
                    {
                        if (p != 1e9)
                            P[g[u]].O(p);
                        if (q != 1e9)
                            P[g[u]].I(q);
                    }
                    d = P[g[u]].C();
                    if (c != d)
                    {
                        if (c != 1e9)
                            S.O(c);
                        if (d != 1e9)
                            S.I(d);
                    }
                }
            z += a[x];
            z -= a[x] ^= 1;
        }
        else if (!z)
            puts("They have disappeared.");
        else if (z == 1)
            puts("0");
        else
            printf("%d\n", S.T());
    }
    return 0;
}
```


---

## 作者：Acee (赞：3)

~~点分治应该都会了吧，我就不写了。~~

### 长链剖分

我们将原树剖作很多重链，并在每条重链上各建一颗线段树，而不是整体建一棵线段树。

我们规定对于一条重链上的一条子链，其左端点为这条子链上 $dfn$ 最小的点，右端点为这条子链上 $\text{dfn}$ 最大的点。

对于线段树上一个节点，维护：

$\text{LmaxDis}$，表示区间左端点所能到达最远的白点的距离。

$\text{RmaxDis}$，表示区间右端点所能到达最远的白点的距离。

$\text{MaxDis}$，表示任意两个 LCA 在区间中的白点（这两个点并不一定在区间内）间的最大距离。

`pushup` 就可以这样写:

```cpp
void pushup(int p, int l, int r) {
	int mid = (l + r) >> 1;
	t[p].lmax = max(t[t[p].ls].lmax, dep[dfn[mid + 1]] - dep[dfn[l]] + t[t[p].rs].lmax);
	t[p].rmax = max(t[t[p].rs].rmax, dep[dfn[r]] - dep[dfn[mid]] + t[t[p].ls].rmax);
	t[p].maxx = max(max(t[t[p].ls].maxx, t[t[p].rs].maxx), t[t[p].ls].rmax + t[t[p].rs].lmax + dep[dfn[mid + 1]] - dep[dfn[mid]]);
}
```

跟最大子段和比较类似。

再对于每个点 $x$ 都用一个数据结构维护 $x$ 向下第一步不走重边能到的所有白点的极大距离，可以使用 $lmax$ + 深度距离差来求。

这个数据结构需要支持插入、删除、求最大值，所以选择堆。

线段树维护好了。

然后在考虑修改。设修改点为 $x$，先修改它所在的链上，再一直向上跳更新。

我们用一个大根堆 $heapans$ 维护每条重链线段树的 $MaxDis$，便可 $O(1)$ 查询。

代码：

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
namespace Main {
	const int N = 100000 + 5; 
	int n, m;
	struct edge {
		int nxt, to, val;
	} e[N * 2];
	int col[N];
	int h[N], num;
	void addedge(int x, int y, int z) {
		e[++num].nxt = h[x];
		e[num].to = y;
		e[num].val = z;
		h[x] = num;
	}
	
	int fa[N], top[N], son[N], dep[N];
	int len[N], cnt, sz[N];
	int id[N], dfn[N];
	
	void dfs1(int x, int f) {
		fa[x] = f;
		sz[x] = 1;
		for (int i = h[x]; i; i = e[i].nxt) {
			int y = e[i].to;
			if (y == f) continue;
			dep[y] = dep[x] + e[i].val;
			dfs1(y, x);
			sz[x] += sz[y];
			if (sz[y] > sz[son[x]]) son[x] = y;
		}
	}
	void dfs2(int x, int f) {
		top[x] = f;
		++len[top[x]];
		id[x] = ++cnt;
		dfn[cnt] = x;
		if (son[x]) dfs2(son[x], f);
		for (int i = h[x]; i; i = e[i].nxt) {
			int y = e[i].to;
			if (y == fa[x] || y == son[x]) continue;
			dfs2(y, y);
		}
	}
	struct Heap {
		multiset<int,greater<int> > s;
		void insert(int v) {
			s.insert(v);
		}
		void del(int v) {
			multiset<int, greater<int> > :: iterator it=s.lower_bound(v);
			if(it!=s.end()) s.erase(it);
		}
		int top() {
			if(s.empty()) return -0x3f3f3f3f;
			return *s.begin();
		}
	};
	Heap ans, stk[N];
	
	struct tree {
		int ls, rs;
		int maxx, lmax, rmax;
	} t[N << 2];
	int TreeCnt;
	int rt[N];
	void pushup(int p, int l, int r) {
		int mid = (l + r) >> 1;
		t[p].lmax = max(t[t[p].ls].lmax, dep[dfn[mid + 1]] - dep[dfn[l]] + t[t[p].rs].lmax);
		t[p].rmax = max(t[t[p].rs].rmax, dep[dfn[r]] - dep[dfn[mid]] + t[t[p].ls].rmax);
		t[p].maxx = max(max(t[t[p].ls].maxx, t[t[p].rs].maxx), t[t[p].ls].rmax + t[t[p].rs].lmax + dep[dfn[mid + 1]] - dep[dfn[mid]]);
	}
	void build(int p, int l, int r) {
		if (l == r) {
			int x = dfn[l];
			for (int i = h[x]; i; i = e[i].nxt) {
				int y = e[i].to;
				if (y == fa[x] || y == son[x]) continue;
				stk[x].insert(t[rt[y]].lmax + e[i].val);
			} 
		//	int jk = 0;
		//	while (stk[x].s.lower_bound(1) != stk[x].s.end()) ++jk, stk[x].s.erase(1);
		//	cout << "jk = " << jk << '\n';
			int max1 = stk[x].top();
			stk[x].del(max1);
			int max2 = stk[x].top();
			stk[x].insert(max1);
			t[p].lmax = t[p].rmax = max(max1, 0);
			t[p].maxx = max(0, max(max1, max1 + max2));
		//	cout << "#####" << max1 << ' ' << max2 << '\n';
			return;
		}
		int mid = (l + r) >> 1;
		if (!t[p].ls)t[p].ls = ++TreeCnt;
		build(t[p].ls, l, mid);
		if (!t[p].rs)t[p].rs = ++TreeCnt;
		build(t[p].rs, mid + 1, r);
		pushup(p, l, r);
	}
	void change(int p, int l, int r, int x, int y) {
		if (l == r) {
			if (x != y) stk[x].insert(t[rt[y]].lmax + dep[y] - dep[x]);
			int max1 = stk[x].top();
			stk[x].del(max1);
			int max2 = stk[x].top();
			stk[x].insert(max1);
			if (col[x]) {
				t[p].lmax = t[p].rmax = max1;
				t[p].maxx = max1 + max2;
			}
			else {
				t[p].lmax = t[p].rmax = max(max1, 0);
				t[p].maxx = max(0, max(max1, max1 + max2));
			}
			return;
		}
		int mid = (l + r) >> 1;
		if (id[x] <= mid) change(t[p].ls, l, mid, x, y);
		else change(t[p].rs, mid + 1, r, x, y);
		pushup(p, l, r); 
	}
	void update(int x) {
		int lst = x;
		while (x) {
			int top_max1 = t[rt[top[x]]].maxx;
			if (fa[top[x]]) {
				stk[fa[top[x]]].del(t[rt[top[x]]].lmax + dep[top[x]] - dep[fa[top[x]]]);
			}
			change(rt[top[x]], id[top[x]], id[top[x]] + len[top[x]] - 1, x, lst);
			int top_max2 = t[rt[top[x]]].maxx;
			//	cout << "Del = " << top_max2 <<'\n'; 
			if (top_max1 != top_max2) {
				ans.del(top_max1);
				ans.insert(top_max2);
			}
			lst = top[x];
			x = fa[top[x]];
		}
	}
	int main() {
		ios::sync_with_stdio(false);
		cin.tie(0), cout.tie(0);
		cin >> n;
		for (int i = 1, x, y, z; i < n; ++i) {
			cin >> x >> y >> z;
			addedge(x, y, z);
			addedge(y, x, z);
		}
		dfs1(1, 0);
		dfs2(1, 1);
//		return 0;
//		for (int i = 1; i <= n; ++i)	 {
//			cout << id[i] << '\n';
//		}
//		return 0;
		for (int i = n; i >= 1; --i) {
			int x = dfn[i];
			if (x == top[x]) {
				if (!rt[x]) rt[x] = ++TreeCnt;
				build(rt[x], id[x], id[x] + len[x] - 1);
				ans.insert(t[rt[x]].maxx);
			}
		} 
//		return 0;
		cin >> m;
		char op;
		int Cnt = n;
		for (int ti = 1, x; ti <= m; ++ti) {
			cin >> op;
			if (op == 'C') {
				cin >> x;
				col[x] ^= 1;
				if (col[x] == 0) ++Cnt;
				else --Cnt;
				update(x);
			}
			else {
				if (Cnt == 0) cout << "They have disappeared.\n";
				else cout << ans.top() << '\n';
			}
		}
		return 0;
	}
}
int main() {
	Main :: main();
	return 0;
}
```

---

## 作者：SrsgPrince_ (赞：1)

# P4115 Qtree4 Solution

题目传送门：[P4115 Qtree4](https://www.luogu.com.cn/problem/P4115)。

推荐在 [博客](https://www.luogu.com.cn/blog/fy123333/P4115Solution) 中查看。

## 题目分析 Hint

题目中有两个操作：

1. `C x`，改变节点 $x$ 的颜色，即白变黑，黑变白。
2. `A`，询问树中最远的两个白色节点的距离，这两个白色节点可以重合。

第一个操作是修改节点颜色，这个很水，第二个操作是询问点集里距离最远的两个点，可以是同一个。那么我们用线段树+树链剖分+平衡树进行实现。而这个树链剖分看做成链上的分治。

## 思路 Solution

我们考虑对于每一条链维护一棵线段树，这里注意要动态开点，否则 MLE。根据题意，我们需要维护三个值 $lv$，$rv$ 和 $mv$。其中 $lv$ 表示某一个点 $u$ 在 $[l,r]$ 区间中，$u$ 到其子树白点的最长距离加上点 $l$ 到点 $u$ 的最短距离之和的最大值。即 $lv = \max_{l \leq u \leq r}(dist(l, u)+ dist2_u)$，其中 $dist(l,u)$ 表示点 $l$ 到点 $u$ 的最短距离之和，$dist2_u$ 表示 $u$ 到其子树白点的最长距离。下面的式子中亦是如此。$rv$ 表示的是某一个点 $u$ 在 $[l,r]$ 区间中，$u$ 到其子树白点的最长距离加上点 $u$ 到点 $r$ 的最短距离之和的最大值。即 $rv = \max_{l \leq u \leq r}(dist(u, r)+ dist2_u)$。$mv$ 表示与当前区间重合的所有路径的最长长度。

接下来考虑 $\operatorname{pushUp()}$。假设 $u$ 点的左右儿子是 $lson_p$，$rson_p$，$mid = \left\lfloor \frac{l + r}{2} \right\rfloor$，那么就有 $$lv_p = \max(lv_{lson_{u}}, dist(l,mid+1)+lv_{rson_u})$$ $$rv_p = \max(rv_{rson_{u}}, dist(mid, r) + rv_{lson_u})$$ $$mv_p = \max(\max(mv_{lson_u}, mv_{rson_u}), rv_{lson_u} + dist(mid,mid+1)+lv_{rson_u})$$

维护最长和次长的方法就是维护这个链的线段树根节点的的 $lv$。考虑到带修，我们使用平衡树。

修改直接用线段树来做。这里直接用 multiset 来进行维护。

代码如下。

```cpp
struct Heap {
    multiset<int, greater<int>> s;
    inline void insert(int v) {
        s.insert(v);
    }
    inline void Delete(int v) {
        multiset<int, greater<int>>:: iterator iter = s.lower_bound(v);
        if (iter != s.end()) s.erase(iter);
    }
    inline int top() {
        if (s.empty()) return -inf;
        return *s.begin();
    }
}hp[maxn], res;
struct Edge {
    int v, nxt, c;
}ed[maxn << 1];
inline void addEdge(int u, int v, int c) {
    ed[++idx].v = v;
    ed[idx].nxt = head[u];
    head[u] = idx;
    ed[idx].c = c;
}
inline void dfs1(int x, int f) {
    fa[x] = f;
	siz[x] = 1;
	for (int i = head[x]; i; i = ed[i].nxt) {
		int y = ed[i].v;
		if (y == f) continue;
		dep[y] = dep[x] + ed[i].c;
		dfs1(y, x);
		siz[x] += siz[y];
		if (siz[y] > siz[son[x]]) son[x] = y;
	}
}
inline void dfs2(int x) {
    if (x == son[fa[x]]) top[x] = top[fa[x]];
	else top[x] = x;
	len[top[x]]++;
	segTree[x] = ++cnt;
	rev[cnt] = x;
	if (son[x]) dfs2(son[x]);
	for(int i = head[x]; i; i = ed[i].nxt){
		int y = ed[i].v;
		if (y == fa[x] || y == son[x]) continue;
		dfs2(y);
	}
}
inline void pushUp(int rt, int lft, int rgt) {
    int mid = (lft + rgt) >> 1;
    lftv[rt]=max(lftv[lson[rt]], dep[rev[mid + 1]] - dep[rev[lft]] + lftv[rson[rt]]);
	rgtv[rt]=max(rgtv[rson[rt]], dep[rev[rgt]] - dep[rev[mid]] + rgtv[lson[rt]]);
	midv[rt]=max(max(midv[lson[rt]], midv[rson[rt]]), rgtv[lson[rt]] + dep[rev[mid + 1]] - dep[rev[mid]] + lftv[rson[rt]]);
}
inline void buildTree(int rt, int lft, int rgt) {
    if (lft == rgt) {
        int x = rev[lft];
        for (int i = head[x]; i; i = ed[i].nxt) {
            int y = ed[i].v;
            if (y == fa[x] || y == son[x]) continue;
            hp[x].insert(lftv[root[y]] + ed[i].c);
        }
        int d1 = hp[x].top();
        hp[x].Delete(d1);
        int d2 = hp[x].top();
        hp[x].insert(d1);
        lftv[rt] = rgtv[rt] = max(d1, 0);
        midv[rt] = max(0, max(d1, d1 + d2));
        return;
    }
    int mid = (lft + rgt) >> 1;
    if (!lson[rt])
        lson[rt] = ++tot;
    buildTree(lson[rt], lft, mid);
    if (!rson[rt])
        rson[rt] = ++tot;
    buildTree(rson[rt], mid + 1, rgt);
    pushUp(rt, lft, rgt);
}
inline void update(int rt, int lft, int rgt, int x, int tp) {
    if (lft == rgt) {
        if (x != tp)
            hp[x].insert(lftv[root[tp]] + dep[tp] - dep[x]);
        int d1 = hp[x].top();
        hp[x].Delete(d1);
        int d2 = hp[x].top();
        hp[x].insert(d1);
        if (wgt[x]) {
            lftv[rt] = rgtv[rt] = d1;
            midv[rt] = d1 + d2;
        } else {
            lftv[rt] = rgtv[rt] = max(d1, 0);
            midv[rt] = max(0, max(d1, d1 + d2));
        }
        return;
    }
    int mid = (lft + rgt) >> 1;
    if (segTree[x] <= mid) update(lson[rt], lft, mid, x, tp);
    else update(rson[rt], mid + 1, rgt, x, tp);
    pushUp(rt, lft, rgt);
}
inline void modify(int x) {
    int lst = x;
    while (x) {
        int tp = top[x];
        int p1 = midv[root[tp]];
        if (fa[tp]) hp[fa[tp]].Delete(lftv[root[tp]] + dep[tp] - dep[fa[tp]]);
        update(root[tp], segTree[tp], segTree[tp] + len[tp] - 1, x, lst);
        int p2 = midv[root[tp]];
        if (p1 != p2) {
            res.Delete(p1);
            res.insert(p2);
        }
        lst = tp;
        x = fa[top[x]];
    }
}
```


---

## 作者：happybob (赞：1)

提供点分树做法。

先考虑静态问题，发现可以点分治做。具体的，对于每个分治重心，求出每个儿子子树内白点到当前重心的距离最大值。将最大和次大加起来即为两条路径拼接。

考虑动态怎么做？首先建出点分树，每个点维护两个 `multiset`，记为 $s_u$ 和 $t_u$，分别维护 $u$ 子树内每个白点到 $fa_u$ 的距离，以及 $u$ 的每一个儿子的 $s_u$ 的最大值。注意需要处理这个点的贡献，即为 $0$。

那么每一个 $t_u$ 的最大和次大值之和即为答案。

考虑修改的时候，只维护这个点到根的路径的 $s$ 和 $t$。由于点分树树高 $O(\log n)$，所以就可以在 $O(q \log^2 n)$ 的复杂度内做完。

然而常数比较大，可以考虑使用懒惰删除堆替代 `multiset`。

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;

const int N = 1e5 + 5, INF = 2e9;

int n, m;
vector<pair<int, int> > G[N];
vector<int> NG[N];
int fa[N], sz[N], dep[N], sum[N];
bool del[N];
bool col[N];
int tot, wc;

class My_Heap
{
public:
	priority_queue<int> p, q;
	void insert(int x)
	{
		p.push(x);
	}
	void erase(int x)
	{
		q.push(x);
	}
	void update()
	{
		if (p.size() < q.size()) exit(-1);
		while (q.size() && p.top() == q.top())
		{
			p.pop(), q.pop();
		}
	}
	int sz()
	{
		if (p.size() < q.size()) exit(-1);
		return p.size() - q.size();
	}
	int top()
	{
		update();
		return p.top();
	}
	int sec()
	{
		int x = top();
		update();
		if (p.empty()) exit(-1);
		p.pop();
		int y = top();
		insert(x);
		return y;
	}
	int res()
	{
		return top() + sec();
	}
}st[N], st2[N], ans;

class TreeCut
{
private:
	int dep[N], fa[N], son[N], top[N], id[N], sz[N], cnt = 0;
	void dfs1(int u, int father, int depth)
	{
		dep[u] = depth;
		fa[u] = father;
		sz[u] = 1;
		for (int i = 0; i < G[u].size(); i++)
		{
			int nx = G[u][i].first;
			if (nx == father) continue;
			dfs1(nx, u, depth + 1);
			sz[u] += sz[nx];
			if (sz[son[u]] < sz[nx]) son[u] = nx;
		}
	}
	void dfs2(int u, int tf)
	{
		top[u] = tf;
		id[u] = ++cnt;
		if (!son[u]) return;
		dfs2(son[u], tf);
		for (int i = 0; i < G[u].size(); i++)
		{
			int nx = G[u][i].first;
			if (nx == fa[u] || nx == son[u]) continue;
			dfs2(nx, nx);
		}
	}
public:
	void build()
	{
		dfs1(1, 1, 1);
		dfs2(1, 1);
	}
	int LCA(int x, int y)
	{
		while (top[x] ^ top[y])
		{
			if (dep[top[x]] < dep[top[y]])
			{
				x ^= y;
				y ^= x;
				x ^= y;
			}
			x = fa[top[x]];
		}
		if (dep[x] < dep[y]) return x;
		return y;
	}
}tc;

void calc_sz(int u, int f)
{
	sz[u] = 0;
	if (del[u]) return;
	sz[u] = 1;
	for (auto& j : G[u])
	{
		if (j.first != f)
		{
			calc_sz(j.first, u);
			sz[u] += sz[j.first];
		}
	}
}

void find_wc(int u, int f)
{
	if (del[u]) return;
	int maxn = tot - sz[u];
	for (auto& j : G[u])
	{
		if (j.first != f)
		{
			find_wc(j.first, u);
			maxn = max(maxn, sz[j.first]);
		}
	}
	if (maxn <= tot / 2) wc = u;
}

int in[N];
vector<int> subtree[N];

void solve(int u, int f)
{
	if (del[u]) return;
	calc_sz(u, 0);
	wc = tot = 0;
	tot = sz[u];
	find_wc(u, 0);
	u = wc;
	del[u] = 1;
	if (f)
	{
		NG[f].emplace_back(u);
		in[u]++;
		fa[u] = f;
		//cout << "!!!: " << f << " " << u << "\n";
	}
	for (auto& j : G[u]) solve(j.first, u);
}

void predfs(int u, int f, int w)
{
	if (!f) dep[u] = 0;
	else dep[u] = dep[f] + 1;
	sum[u] = sum[f] + w;
	for (auto& j : G[u])
	{
		if (j.first != f)
		{
			predfs(j.first, u, j.second);
		}
	}
}

inline int get_dist(const int& x, const int& y)
{
	return sum[x] + sum[y] - 2 * sum[tc.LCA(x, y)];
}

void dfs(int u)
{
	if (col[u] == 0)
	{
		if (fa[u]) st[u].insert(get_dist(u, fa[u]));
		subtree[u].emplace_back(u), st2[u].insert(0);
	}
	for (auto& j : NG[u])
	{
		dfs(j);
		int maxn = -INF;
		for (auto& k : subtree[j])
		{
			subtree[u].emplace_back(k);
			int g = get_dist(u, k);
			maxn = max(maxn, g);
			if (fa[u]) st[u].insert(get_dist(k, fa[u]));
		}
		if (maxn == -INF) continue;
		st2[u].insert(maxn);
	}
}

int rtt = 0;

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		G[u].emplace_back(make_pair(v, w));
		G[v].emplace_back(make_pair(u, w));
	}
	tc.build();
	solve(1, 0);
	predfs(1, 0, 0);
	//if (!dbg.check()) return -1;
	cin >> m;
	int cnt = n;
	for (int i = 1; i <= n; i++) if (!fa[i]) rtt = i;
	dfs(rtt);
	for (int i = 1; i <= n; i++)
	{
		if (st2[i].sz() >= 2) ans.insert(st2[i].res());
	}
	while (m--)
	{
		char opt;
		cin >> opt;
		if (opt == 'C')
		{
			int x;
			cin >> x;
			if (col[x] == 0)
			{
				if (st2[x].sz() >= 2) ans.erase(st2[x].res());
				st2[x].erase(0);
				if (st2[x].sz() >= 2) ans.insert(st2[x].res());
				for (int i = x; fa[i]; i = fa[i])
				{
					if (st2[fa[i]].sz() >= 2) ans.erase(st2[fa[i]].res());
					int pre = st[i].top();
					st2[fa[i]].erase(pre);
					st[i].erase(get_dist(x, fa[i]));
					if (st[i].sz()) st2[fa[i]].insert(st[i].top());
					if (st2[fa[i]].sz() >= 2) ans.insert(st2[fa[i]].res());
				}
				cnt--;
			}
			else
			{
				if (st2[x].sz() >= 2) ans.erase(st2[x].res());
				st2[x].insert(0);
				if (st2[x].sz() >= 2) ans.insert(st2[x].res());
				for (int i = x; fa[i]; i = fa[i])
				{
					if (st2[fa[i]].sz() >= 2) ans.erase(st2[fa[i]].res());
					if (st[i].sz())
					{
						int pre = st[i].top();
						st2[fa[i]].erase(pre);
					}
					st[i].insert(get_dist(x, fa[i]));
					st2[fa[i]].insert(st[i].top());
					if (st2[fa[i]].sz() >= 2) ans.insert(st2[fa[i]].res());
				}
				cnt++;
			}
			col[x] ^= 1;
		}
		else
		{
			if (cnt == 0) cout << "They have disappeared.\n";
			else if (ans.sz() == 0) cout << "0" << "\n";
			else
			{
				cout << max({ ans.top(), 0 }) << "\n";
			}
		}
	}
	return 0;
}
```


---

## 作者：justalearner (赞：0)

来一篇边分树（动态边分治）的题解！

大部分能够用点分治/点分树解决的问题其实都能够用边分治/边分树解决，而且会更好写一点。

可能有人会问这个边分树是什么~~因为 OIWiki 还没有~~。相信大家都学过点分树以及边分治吧，其实这个边分树也差不多，它的枝干节点是边分治里面的分治中心的那条边，叶节点是原图每个点。

接下来对每条边维护两个堆，维护两边的连通块中的白点的距离。然后对每条边维护它在点分树中的子树的最优答案。

修改也很简单：变成白点就插进去（可以用`unordered_map`预处理距离，当然你喜欢用 $O(1)$ LCA 什么的也可以啦），变成黑点就打个标记。在边分树中从底向上地维护答案即可。

时间复杂度大概是 $\Theta(n\log n)$？不过至少也是 $O(n\log^2 n)$ 啦。

[双倍经验](https://www.luogu.com.cn/problem/P2056)

[代码](https://www.luogu.com.cn/paste/orm8r3qy)

---

