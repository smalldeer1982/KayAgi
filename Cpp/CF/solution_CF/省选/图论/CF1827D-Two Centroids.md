# Two Centroids

## 题目描述

You are given a tree (an undirected connected acyclic graph) which initially only contains vertex $ 1 $ . There will be several queries to the given tree. In the $ i $ -th query, vertex $ i + 1 $ will appear and be connected to vertex $ p_i $ ( $ 1 \le p_i \le i $ ).

After each query, please find out the least number of operations required to make the current tree has two centroids. In one operation, you can add one vertex and one edge to the tree such that it remains a tree.

A vertex is called a centroid if its removal splits the tree into subtrees with at most $ \lfloor \frac{n}{2} \rfloor $ vertices each, with $ n $ as the number of vertices of the tree. For example, the centroid of the following tree is $ 3 $ because the biggest subtree after removing the centroid has $ 2 $ vertices.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827D/ecc06e1bfbfa2b50ddf426bffbad51ace4e5a023.png)In the next tree, vertex $ 1 $ and $ 2 $ are both centroids.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827D/42a5367fe4666594cdbcb007a8104c576dad78f0.png)

## 说明/提示

The illustrations below are of the fourth example test case.

After the third query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827D/15c7a987e93f4191ff93989ce5a5d836a3f65c54.png)  The tree already has vertices $ 2 $ and $ 3 $ as centroids, so no operations are needed.After the fourth query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827D/510bc6f02a1aac0ae1f0e8ae57461166a9b6fabc.png)  Adding vertex $ x $ to the tree makes vertices $ 2 $ and $ 3 $ centroids. Only one operation is needed.After the fifth query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827D/29421eb0f8c94af01daaf309b6ffbeb3c5c65c23.png)  Adding vertex $ x $ and $ y $ to the tree makes vertices $ 5 $ and $ 2 $ centroids. Two operations are needed.After the sixth query:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1827D/276326fe18921ee503ac095502b55c698850d8c6.png)  Adding vertex $ x $ , $ y $ , and $ z $ to the tree makes vertices $ 5 $ and $ 2 $ centroids. Three operations are needed.

## 样例 #1

### 输入

```
5
2
1
3
1 1
4
1 2 3
7
1 2 3 2 5 2
10
1 2 2 4 5 5 7 8 9```

### 输出

```
0
0 1
0 1 0
0 1 0 1 2 3
0 1 2 1 0 1 0 1 2```

# 题解

## 作者：EuphoricStar (赞：18)

考虑固定一个重心，设 $k$ 为重心最大子树大小，答案为 $n - 2k$。构造方法是往最大的子树塞叶子。

树的重心有一个很好的性质，就是加一个叶子，重心最多移动一条边的距离。简单证一下，设重心为 $x$，往儿子 $u$ 的子树中加叶子。

- 如果 $sz_u > \left\lfloor\frac{n}{2}\right\rfloor$，那么 $sz_u - 1 = \left\lfloor\frac{n}{2}\right\rfloor$，并且 $x$ 的其他子树大小 $< \left\lfloor\frac{n}{2}\right\rfloor$，那么 $x$ 会下移到 $u$；
- 否则无事发生。

考虑树状数组维护每个点子树的大小，当前重心和当前的 $k$。只用考虑下移一条边的情况，因此是容易维护的。时间复杂度 $O(n \log n)$。

[code](https://codeforces.com/contest/1827/submission/206074138)

---

## 作者：liangbowen (赞：3)

[problem](https://www.luogu.com.cn/problem/CF1827D) & [blog](https://www.cnblogs.com/liangbowen/p/17541713.html)。

很好的题。用到一些关于重心的 trick。

---

不妨认为只有一个重心 $\text{maxx}$。设当前节点数为 $n$，重儿子所在的子树的大小为 $\text{maxsiz}$，那么答案即 $n - 2\times\text{maxsiz}$，方法是往重儿子的那个子树爆加节点。

因此需要在线维护 $\text{maxx}$ 与 $\text{maxsiz}$。假设已知上一次操作的 $\text{maxx}$ 与 $\text{maxsiz}$，分类讨论以求出新的值。

+ $u$ 在 $\text{maxx}$ 的子树里。若新的子树超过了 $\left\lfloor\dfrac n2\right\rfloor$，更新 $\text{maxx}=u,\text{maxsiz}=\left\lfloor\dfrac n2\right\rfloor$。否则，直接更新 $\text{maxsiz}$。
+ $u$ 不在 $\text{maxx}$ 的子树里。过程和上面类似，只是添加到 $fa_u$ 对应的地方。

新的子树的 $\text{siz}$ 用树状数组维护维护 dfs 序即可。实现方面，还要写个倍增跳 $k$ 级祖先的操作，整体细节不多。

[代码](https://codeforces.com/contest/1827/submission/213088474)，时间复杂度 $O(n\log n)$。


---

## 作者：luogubot (赞：2)

初始只有根节点的树，每次加叶子之后询问至少再添加多少个叶子能使得树有两个重心。不强制在线。

$\sum n\leq 5\times 10^5$。

有两个重心 $\to$ 一条边把树分成大小均为 $\frac{|V|}{2}$ 的两部分 $\to$ 找到原树中的一条边使得两部分点数差距最小。

到这里就卡住了，因为不能动态维护子树 size 最接近 $\frac{i}{2}$ 的值（$i$ 是当前点数），继续分析性质：暂时忽略不用加点的情况，则这条边的两端一定有点数 $< \frac{i}{2}$ 的，那么点数 $> \frac{i}{2}$ 的另一边如果仍然存在一棵子树满足点数 $>\frac{i}{2}$，则整体向那棵子树移动一步更优。也就是端点一定有一个是原树重心。对于不用加点的情况，两个端点都是重心。

如果能动态维护重心，其另一端的 size 不超过它，所以只需要求它的邻边中对应 size 最大的，父边可以特判，儿子只需要在子树里找 size 最大的，都可以用树剖维护 size 以及子树 size 最大值。最后处理重心，发现添加一个叶子之后重心至多朝着这个叶子移动一步，所以时刻也只需要维护一个重心（即使实际有两个，添加叶子之后也只是切换到另一个，可以从维护的那个重心走一步得到），全都可以借助树剖结构来实现。

$O(n\log^2n)$，[Submission](https://codeforc.es/contest/1827/submission/206039557)。

---

## 作者：Super_Cube (赞：1)

# Solution

先不考虑修改，只给定一棵树，求使其拥有两个重心最少加几个叶子能满足？个人认为答案很容易得出：如果现在只有一个重心，那么往以其为根得到的子树大小最大的儿子节点一直挂叶子肯定最优，设那个点的子树大小为 $m$，最少挂 $n-2m$ 个点，使得两部分皆为 $\dfrac{n+(n-2m)}{2}=n-m$ 个点。

现在这棵树在“动态”加点（并没有强制在线），对重心会有何影响呢？假设原重心在 $x$，由于每次只加了 $1$ 个点，最坏情况下会使 $x$ 进行距离为 $1$ 的位移，因为只有加入的那个点刚好使得重心对应出边那一坨子树大小达到临界值迫使重心异位。

其实这个题分析到这里基本结束了。

输入后先把最终树的形态确定下来。维护当前重心所在位置，加点时若在重心子树内，判断当前点祖先且是重心儿子的那个点现在子树大小是否超过临界，超过了重心会下跳，否则重心不会变；要不然不在重心子树内，是类似的判断，超过了重心就上跳。过程中顺便维护重心所有儿子的子树大小最大值。

在动态加点过程中查询子树大小可用 dfs 序与树状数组维护。

# Code

```cpp
#include<bits/stdc++.h>
inline int lowbit(int x){
	return x&-x; 
}
std::vector<int>v[500005];
int fa[500005][20];
int dep[500005];
int L[500005],R[500005],tdx;
void dfs(int p){
	L[p]=++tdx;
	dep[p]=dep[fa[p][0]]+1;
	for(int i=1;i<20;++i)
		fa[p][i]=fa[fa[p][i-1]][i-1];
	for(const int&i:v[p])
		fa[i][0]=p,dfs(i);
	R[p]=tdx;
}
inline int up(int x,int y){
	for(int i=19;~i;--i)
		if(dep[fa[x][i]]>dep[y])x=fa[x][i];
	return x;
}
int bit[500005];
int n;
inline void add(int x){
	for(;x<=n;x+=lowbit(x))++bit[x];
}
inline int ask(int x){
	static int res;res=0;
	for(;x;x^=lowbit(x))res+=bit[x];
	return res;
}
int T,rt,w;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)v[i].clear();
		for(int i=2,x;i<=n;++i)
			scanf("%d",&x),v[x].push_back(i);
		tdx=0;dfs(rt=1);
		memset(bit+1,w=0,n<<2);
		for(int i=2,j,k;i<=n;++i){
			add(L[i]);
			if(L[rt]<=L[i]&&L[i]<=R[rt]){
				j=up(i,rt);k=ask(R[j])-ask(L[j]-1);
				if(k>(i>>1))rt=j,w=i>>1;
				else w=std::max(w,k);
			}else{
				k=i-ask(R[rt])+ask(L[rt]-1);
				if(k>(i>>1))rt=fa[rt][0],w=i>>1;
				else w=std::max(w,k);
			}
			printf("%d ",i-(w<<1));
		}
		putchar(10);
	}
	return 0;
}
```

---

## 作者：lzqy_ (赞：1)

当一棵树有两个重心时，一定存在一条边，其两侧的点数相同。

所以题目转化为，设 $S_x$ 表示子树大小，最小化 $|2S_x-n|$ 的值。

一个最直接的想法是在值域线段树上二分。但加点造成的链加操作是平凡的，值域线段树不太好维护。

考虑维护两棵线段树 $T_1,T_2$。$T_1$ 里放满足 $2S \le n$ 的点，$T_2$ 里放满足 $2S>n$ 的点，这样只需要支持查询最大值就行了。

但加入一个新点时，$T_1$ 中的点可能移动到 $T_2$ 中，$T_2$ 中的点也可能移动到 $T_1$ 中。

考虑对这部分直接暴力，即 $O(\log n)$ 暴力移动一个点。

这从直观上感受是正确的，证明也不难。分析一个点什么时候会跨线段树，当且仅当 $2S_x=n$ 或 $2S_x=n+1$，即 $x$ 是原树的重心。所以每次最多有 $O(1)$ 个点跨树，所以这部分是单 $\log$ 的，常数会比较大。

总时间复杂度 $O(n\log^2n)$，加 fread 才过。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=500010;
const int MAXN=maxn<<2;
const int inf=1<<28;
namespace io{
    const int S=1<<20;
    char ib[S],*s=ib,*t=ib;
    inline char gc(){ return (s==t)&&(t=(s=ib)+fread(ib,1,S,stdin)),s==t?-1:*s++; }
    inline int read(){
        int x=0,f=1;char c=gc();
        while(c<'0'||c>'9') f=(c=='-')?-1:1,c=gc();
        while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c&15),c=gc();
        return x*f;
    }
    char ob[S],*p=ob;
    inline void flush(){fwrite(ob,p-ob,1,stdout),p=ob;}
    inline void pt(char x){(p-ob>=S)&&(flush(),1);*p++=x;}
    inline void write(int x){
        static char t[46];static int ct=0;
        if(x<0) pt('-'),x=-x;
        do{t[++ct]=x%10+'0';x/=10;}while(x);
        while(ct) pt(t[ct]),ct--;
    }
}
using io::read;using io::write;using io::flush;using io::pt;
struct edge{
	int v,to;
}e[maxn<<1];
int head[maxn],ecnt;
void addedge(int u,int v){
	e[++ecnt].v=v,e[ecnt].to=head[u],head[u]=ecnt;
}
int T,n,tot=1;
int d1[MAXN],d2[MAXN];
int lz1[MAXN],lz2[MAXN];
int dfn[maxn],DFN[maxn],top[maxn],idx;
int sz[maxn],zson[maxn],dep[maxn],fa[maxn];
void dfs1(int fath,int x){
	dep[x]=dep[fath]+1,fa[x]=fath;
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v^fath){
			dfs1(x,e[i].v),sz[x]+=sz[e[i].v];
			if(sz[zson[x]]<sz[e[i].v]) zson[x]=e[i].v;
		}
	sz[x]++;
}
void dfs2(int x){
	dfn[x]=++idx,DFN[idx]=x;
	if(zson[fa[x]]^x) top[x]=x;
	else top[x]=top[fa[x]];
	if(zson[x]) dfs2(zson[x]);
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v!=fa[x]&&e[i].v!=zson[x]) dfs2(e[i].v);
}
void pushdown1(int i){
	if(!lz1[i]) return ;
	d1[i<<1]+=lz1[i],d1[i<<1|1]+=lz1[i];
	lz1[i<<1]+=lz1[i],lz1[i<<1|1]+=lz1[i];
	lz1[i]=0;
}
void pushdown2(int i){
	if(!lz2[i]) return ;
	d2[i<<1]+=lz2[i],d2[i<<1|1]+=lz2[i];
	lz2[i<<1]+=lz2[i],lz2[i<<1|1]+=lz2[i];
	lz2[i]=0; 
}
void M1(int i,int l,int r,int x,int k){
	if(l==r){
		d1[i]=k;
		return ;
	}pushdown1(i);
	int mid=l+r>>1;
	if(mid>=x) M1(i<<1,l,mid,x,k);
	else M1(i<<1|1,mid+1,r,x,k);
	d1[i]=max(d1[i<<1],d1[i<<1|1]);
}
void M2(int i,int l,int r,int x,int k){
	if(l==r){
		d2[i]=k;
		return ;
	}pushdown2(i);
	int mid=l+r>>1;
	if(mid>=x) M2(i<<1,l,mid,x,k);
	else M2(i<<1|1,mid+1,r,x,k);
	d2[i]=min(d2[i<<1],d2[i<<1|1]);
}
void A1(int i,int l,int r,int L,int R){
	if(l>=L&&r<=R){
		d1[i]++,lz1[i]++;
		return ;
	}pushdown1(i);
	int mid=l+r>>1;
	if(mid>=L) A1(i<<1,l,mid,L,R);
	if(mid<R) A1(i<<1|1,mid+1,r,L,R);
	d1[i]=max(d1[i<<1],d1[i<<1|1]);
}
void A2(int i,int l,int r,int L,int R){
	if(l>=L&&r<=R){
		d2[i]++,lz2[i]++;
		return ;
	}pushdown2(i);
	int mid=l+r>>1;
	if(mid>=L) A2(i<<1,l,mid,L,R);
	if(mid<R) A2(i<<1|1,mid+1,r,L,R);
	d2[i]=min(d2[i<<1],d2[i<<1|1]);
}
void Push1(int i,int l,int r){
	if(2*d1[i]<=tot) return ;
	if(l==r){
		M2(1,1,n,l,d1[i]),d1[i]=-inf;
		return ;
	}pushdown1(i);
	int mid=l+r>>1;
	Push1(i<<1,l,mid);
	Push1(i<<1|1,mid+1,r);
	d1[i]=max(d1[i<<1],d1[i<<1|1]);
}
void Push2(int i,int l,int r){
	if(2*d2[i]>tot) return ;
	if(l==r){
		M1(1,1,n,l,d2[i]),d2[i]=inf;
		return ;
	}pushdown2(i);
	int mid=l+r>>1;
	Push2(i<<1,l,mid);
	Push2(i<<1|1,mid+1,r);
	d2[i]=min(d2[i<<1],d2[i<<1|1]);
}
void build(int i,int l,int r){
	d2[i]=inf,d1[i]=-inf;
	if(l==r) return ;
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
}
void clear(int i,int l,int r){
	d1[i]=d2[i]=lz1[i]=lz2[i]=0;
	if(l==r) return ;
	int mid=l+r>>1;
	clear(i<<1,l,mid),clear(i<<1|1,mid+1,r);
}
void Add(int x){
	while(x){
		A1(1,1,n,dfn[top[x]],dfn[x]);
		A2(1,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
}
int p[maxn];
int main(){
	T=read();
	int ttt=0,TT=T;
	while(T--){
		n=read();
		for(int i=2;i<=n;i++){
			p[i]=read();
			addedge(p[i],i);
			addedge(i,p[i]);
		}dfs1(0,1),dfs2(1);
		build(1,1,n);
		M2(1,1,n,1,1);
		for(int i=2;i<=n;i++){
			M1(1,1,n,dfn[i],1);
			Add(p[i]),tot++;
			Push1(1,1,n),Push2(1,1,n);
			write(min(tot-2*d1[1],2*d2[1]-tot));
			pt(' ');
		}
		pt('\n');
		for(int i=1;i<=n;i++)
			head[i]=zson[i]=sz[i]=0;
		clear(1,1,n);
		ecnt=idx=0,tot=1;
	}
	flush();
	return 0;
}
```

---

## 作者：BreakPlus (赞：1)

神秘题，不知道怎么评的 *2800。

由于有两个重心等价于有一颗子树的大小为 $\dfrac{n}{2}$，我们会找到一条边，将其断开分成两部分后，在小的那一部分补点直到两部分大小相等。

也就是我们要找到一颗子树，使得其大小与 $\dfrac{n}{2}$ 越接近越好。

好像没办法直接维护，推推性质：

+ 最优的子树一定是删去重心及其连边后，剩余的某个连通块（即一定是与重心相邻的点所代表的子树）。

+ 重心的移动总次数是 $\mathcal{O}(n)$ 的。

至此我们可以动态维护重心，这样考虑范围缩小为重心的邻域。

但是不能直接暴力枚举其邻域。发现如果重心不动，那么只有当前加入的点所在子树可能会成为新的更优子树，没必要遍历其邻域。

若移动，那么现在的最优子树一定是上一个重心。

也就是说，最优子树也能动态维护了。问题得以解决。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> Pr;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define mid ((l+r)>>1)
#define popcnt __builtin_popcountll

inline ll read(){
	ll x=0, f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
ll n,p[500005],dfn[500005],out[500005],seq[500005],tim,cent,son,val;
vector<ll>E[500005]; set<ll>S[500005];

ll c[500005];
inline void upd(ll x,ll w=1){
	for(; x<=n; x+=(x&(-x))){
		c[x] += w;
	}
}
inline ll query(ll x){
	ll res = 0;
	for(; x; x-=(x&(-x))){
		res += c[x];
	}
	return res;
}
void dfs(ll x){
	dfn[x]=(++tim); seq[tim]=x;
	for(auto y: E[x]){
		dfs(y);
		S[x].insert(dfn[y]);
	}
	out[x]=tim;
}
inline ll sub_tree(ll x){
	return query(out[x]) - query(dfn[x]-1);
}
inline ll out_tree(ll x){
	return query(n) - query(out[x]) + query(dfn[x]-1);
}
inline ll find_subtree(ll x,ll y){
	if(dfn[x] <= dfn[y] && dfn[y] <= out[x]){
		return seq[*(--S[x].upper_bound(dfn[y]))];
	}else return -1;
}
inline ll get_val(ll x,ll id){
	if(id == -1) return out_tree(x);
	else return sub_tree(id);
}
void Main(){
	n=read();
	for(ll i=1;i<=n;i++) c[i]=0, E[i].clear(), S[i].clear();
	tim=son=val=0; cent=1;
	for(ll i=2;i<=n;i++){
		p[i]=read();
		E[p[i]].pb(i);
	}
	dfs(1); upd(dfn[1]);
	for(ll i=2;i<=n;i++){
		upd(dfn[i]);
		ll id = find_subtree(cent, i);
		if(2 * get_val(cent, id) > i){
			ll cent2 = (id == -1)? p[cent]: id;
			son = (cent == p[cent2])? -1: cent2;
			val = i - get_val(cent, id);
			cent = cent2;
		}else if(get_val(cent, id) > val){
			son = id;
			val = get_val(cent, id);
		}
		printf("%lld ", i-val*2);
	}
	puts("");
}

int main(){
	ll T=read();
	while(T--) Main();
	return 0;
}

```

---

## 作者：hgzxwzf (赞：1)

### [CF1827D](https://www.luogu.com.cn/problem/CF1827D)

设 $w_i$ 表示以 $i$  为根时，$i$ 的儿子子树的大小的最大值，$s_i$ 表示该子树的根。

> 性质：假设重心为 $u$，即 $w_u$ 是 $w$ 的最小值，对于和 $u$ 相连的点 $v$，$s_v=u$。
>
> 证明：如果 $s_v\ne u$，显然以 $u$ 为根时，$siz_{s_v}<siz_v$，又因为 $w_u\ge siz_v$，所以有 $w_v< w_u$，此时重心应该是 $v$，矛盾。

> 结论：当树中有 $n$ 个点时，答案为 $n-2\times \min w_i$。
>
> 证明：如果有两个点 $w_i$ 都最小，说明此时有两个重心，设为 $x,y$，此时有 $s_x=y,s_y=x$，显然 $2\times w_x=2\times w_y=n$；如果只有一个点 $w_i$ 最小，设 $u=s_i,mi=w_i$，需要让 $w_u=w_i$，则在 $u$ 子树中加点，每加一个点，$w_i+1$，$w_j$ 不变，最后 $w_i=n-mi$，加了 $w_i-mi=n-mi-mi$ 个点。

需要维护动态重心 $cen$，这里有个比较经典的结论是加入 $p$ 的一个儿子 $u$，重心要么不动，要么向 $p$ 移动。

如果 $u$ 是 $cen$ 的子树内的点（以 $1$ 为根，下同），通过倍增得到 $cen$ 向 $u$ 移动一步走到的节点 $v$，用 $siz_v$ 更新 $\min w_i$，如果 $min_{w_i}>\lfloor \frac{n}{2}\rfloor$，将 $cen$ 改成 $v$。这时还要将 $\min w_i$ 改成 $w_v$，根据上面的性质可以推出 $w_i=n-siz_{cen}$。

否则，向 $p$ 移动的第一个点就是 $cen$ 的父亲了，类似上面的方法更新就行了。

查询子树大小，用树状数组维护。

[代码](https://codeforces.com/contest/1827/submission/206062499)。

---

## 作者：Coffee_zzz (赞：0)

考虑动态维护下面的信息：

- 树的其中一个重心 $r$；
- 以 $r$ 为根时，$r$ 的重儿子的子树大小 $s$；

则我们可以通过不断往 $r$ 的重儿子中添加结点的方式，使得 $r$ 的重儿子也变成树的重心。简单计算可得答案为 $n-2s$。

每次添加一个结点 $u$ 时，显然重心 $r$ 要么不变，要么向结点 $u$ 移动一步。通过倍增找到结点 $v$ 满足 $v$ 是 $r$ 的儿子且是 $u$ 的祖先，特殊处理 $v$ 是 $r$ 的父亲的情况，设 $v$ 的子树大小为 $x$，分类讨论：

- 若 $x \lt \left\lceil\frac n 2\right\rceil$，则重心 $r$ 不变，$s$ 的值变为 $\max(s,x)$；
- 若 $x \ge \left\lceil\frac n 2\right\rceil$，则重心 $r$ 变成 $v$，$s$ 的值变为 $\left\lfloor\frac n 2\right\rfloor$。

其中，求 $v$ 的子树大小可以通过预处理 dfn 并用树状数组维护完成。时间复杂度 $\mathcal O(n \log n)$。

```c++
#include <bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define i128 __int128
#define endl '\n'
#define pb push_back
#define pf push_front
#define pii pair<int,int>
#define fi first
#define se second
#define vei vector<int>
#define pq priority_queue
#define lb lower_bound
#define ub upper_bound
#define yes puts("yes")
#define no puts("no")
#define Yes puts("Yes")
#define No puts("No")
#define YES puts("YES")
#define NO puts("NO")
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
using namespace std;
const int N=5e5+5,L=19;
int n,r,s,p[N],dfn[N],sum[N],tot,dep[N],siz[N],fa[N][L];
vector <int> ve[N];
int lowbit(int x){
	return x&-x;
}
void add(int x){
	for(int u=x;u<=n;u+=lowbit(u)) sum[u]++;
}
int query(int x){
	int res=0;
	for(int u=x;u>0;u-=lowbit(u)) res+=sum[u];
	return res;
}
void init(int u){
	dfn[u]=++tot,dep[u]=dep[p[u]]+1,siz[u]=1;
	for(auto v:ve[u]) init(v),siz[u]+=siz[v];
}
int jump(int u,int k){
	for(int i=L-1;i>=0;i--) if(dep[fa[u][i]]>k) u=fa[u][i];
	return u; 
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) ve[i].clear(),sum[i]=0;
	for(int u=2;u<=n;u++) cin>>p[u],ve[p[u]].pb(u),fa[u][0]=p[u];
	tot=0,init(1),r=1,s=1,add(1);
	for(int i=1;i<L;i++) for(int u=1;u<=n;u++) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int u=2;u<=n;u++){
		add(dfn[u]);
		int v=jump(u,dep[r]),x;
		if(p[v]==r) x=query(dfn[v]+siz[v]-1)-query(dfn[v]-1);
		else v=p[r],x=u-(query(dfn[r]+siz[r]-1)-query(dfn[r]-1));
		if(x<(u+1)/2) s=max(s,x);
		else r=v,s=u/2;
		cout<<u-2*s<<' ';
	}
	cout<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	signed T=1;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

学弟给的题。他说这是 $300$ 行大数据结构……

一棵树有两个重心的充要条件是存在一条边把整棵树分成两棵大小相同的子树。

假设当前树为 $T$，树的大小为 $t$，那么答案是：

$$
\min_{u \in T} | t - 2sze_u|
$$

考虑把树的重心 $c$ 找出来。

显然，只有 $c$ 和 $c$ 的儿子可能是决策点。因此我们只需要：

1. 动态维护树的重心。根据重心的性质，新增加一个叶子节点，重心最多向这个节点移动 $1$ 的距离。
2. 维护一个点所有儿子的子树大小的最大值。考虑树链剖分，只有轻儿子能对他的父亲产生修改。那么维护所有链头的大小，以及每个节点所有轻儿子大小的最大值。

总体复杂度 $O(n \log n)$。

我第一次写代码的时候不小心把 $2$ 中的求轻儿子子树大小写成了 $O(\log n)$ 的，不过发现和 $O(1)$ 的速度差不多（大概是树状数组常数很小）。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int T,n,tot,core,dfn[MAXN],sze[MAXN],osze[MAXN],mx[MAXN],top[MAXN],son[MAXN],fa[MAXN],tr[MAXN];
void update(int pos,int v) {
	while(pos<=n) tr[pos]+=v,pos+=pos&-pos;
	return ;	
}
int query(int pos) {
	int ans=0;
	while(pos) ans+=tr[pos],pos-=pos&-pos;
	return ans;	
}
vector<pair<int,int>> st[MAXN]; 
vector<int> G[MAXN];
void dfs(int u) {
	st[u].clear(),mx[u]=0,osze[u]=0,tr[u]=0,dfn[u]=++tot,sze[u]=1,son[u]=0;
	for(auto v:G[u]) {
		dfs(v),st[u].push_back({dfn[v],v}),sze[u]+=sze[v];
		if(sze[v]>sze[son[u]]) son[u]=v;
	}
	return ;
}
void Dfs(int u) {
	if(son[u]) top[son[u]]=top[u],Dfs(son[u]);
	for(auto v:G[u]) if(v!=son[u]) top[v]=v,Dfs(v);
	return ;
}
int get_sze(int u) {return query(dfn[u]+sze[u]-1)-query(dfn[u]-1);}
void update(int u) {
	update(dfn[u],1);
	int v=top[u];
	while(v!=1) osze[v]++,mx[fa[v]]=max(mx[fa[v]],osze[v]),v=top[fa[v]];	
	return ;
}
int legal(int u,int t) {
	if(t-get_sze(u)>t/2) return 0;
	if(mx[u]>t/2) return 0;
	if(son[u]&&get_sze(son[u])>t/2) return 0;
	return 1;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n,tot=0;
		ffor(i,1,n) G[i].clear();
		ffor(i,2,n) cin>>fa[i],G[fa[i]].push_back(i);
		dfs(1),top[1]=1,Dfs(1);
		update(1),core=1;
		ffor(i,2,n) {
			update(i);
			while(!legal(core,i)) {
				if(dfn[core]<=dfn[i]&&dfn[i]<=dfn[core]+sze[core]-1) {
					int nxt=(--upper_bound(st[core].begin(),st[core].end(),make_pair(dfn[i]+1,0)))->second;
					core=nxt;
				}
				else core=fa[core];
			}
			int ans=i+1;
			ans=min(ans,2*get_sze(core)-i);
			ans=min(ans,i-2*mx[core]);
			if(son[core]) ans=min(ans,i-2*get_sze(son[core]));
			cout<<ans<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：0)

本文 $size_x$ 均表示结点 $x$ 代表的子树当前所包含的结点数量，用树状数组可以维护单点求 $size_x$。

考虑实时维护 $1/2$ 个重心。这是可以线性对数做到的。因为加一个点后，只会出现：

1. 双重心中一个重心变为非重心（在加点的子树方向上的保留）。

2. 单重心不变。

3. 单重心不变，且多一个相邻的重心（在加点的子树方向上）。

设当前共 $m$ 个点，当且仅当存在大小恰为整体一半的子树时，有双重心。则需找出 $\displaystyle\min_{v\in \text{Tree}}(|2size_v-m|)$。

对于只有一个重心 $x$ 的情况，考虑向某个方向加点。往父方向加点的答案是好算的：$|2size_x-m|$。

根据重心的的性质，现在只需要再找到当前重心，$size$ 最大的儿子子树即可。做一个比较。

线性对数平方的算法是简单的。求出 dfs 序后。用树剖 + 线段树维护所有子树的 $size_x$。只要一个区间加 $1$，区间查 $\max$ 的线段树即可。当然显然不能过。能过也不是优秀解。

现在考虑降掉 $1$ 个 $\log$。一种思路是离线。本质上我们需要用总体线性对数的复杂度处理 $n$ 次“考虑前 $k$ 个点，结点 $x$ 的最大儿子子树的 $size$ 是多少”的询问。这个看起来也没什么好的处理办法。而且仔细想想这个离线根本没用。因为本来在线做的 $k$ 也是递增的。

发现对于儿子很多的结点，不能每次 check 其所有儿子是最大的麻烦。于是考虑先对整棵树重剖。维护两个普通线性数组：$cursize_x$ 和 $mx_x$。分别表示 $x$ 子树的当前大小（只考虑所有是轻儿子的 $x$）和 $x$ 的轻儿子 $v$ 中，最大的 $cursize_v$ 是多少。

那么加入结点 $m$ 的时候，轻子树暴力向上跳，更新 $cursize$ 和 $mx$ 可以做到。

而若此时只有一个重心 $x$，分别求出在其重儿子方向加点的答案 $|2size_{hson_x}-m|$ 和在父方向加点的答案 $|2size_x-m|$，以及在其他轻子树方向加点的答案 $|2mx_x-m|$，取 $\min$ 即可。

总复杂度线性对数。

[for reference only.](https://www.luogu.com.cn/paste/t412bkgz)

---

