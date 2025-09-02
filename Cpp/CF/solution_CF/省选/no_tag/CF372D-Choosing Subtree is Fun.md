# Choosing Subtree is Fun

## 题目描述

There is a tree consisting of $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ .

Let's define the length of an interval $ [l,r] $ as the value $ r-l+1 $ . The score of a subtree of this tree is the maximum length of such an interval $ [l,r] $ that, the vertices with numbers $ l,l+1,...,r $ belong to the subtree.

Considering all subtrees of the tree whose size is at most $ k $ , return the maximum score of the subtree. Note, that in this problem tree is not rooted, so a subtree — is an arbitrary connected subgraph of the tree.

## 说明/提示

For the first case, there is some subtree whose size is at most $ 6 $ , including $ 3 $ consecutive numbers of vertices. For example, the subtree that consists of $ {1,3,4,5,7,8} $ or of $ {1,4,6,7,8,10} $ includes $ 3 $ consecutive numbers of vertices. But there is no subtree whose size is at most $ 6 $ , which includes $ 4 $ or more consecutive numbers of vertices.

## 样例 #1

### 输入

```
10 6
4 10
10 6
2 9
9 6
8 5
7 1
4 7
7 3
1 8
```

### 输出

```
3
```

## 样例 #2

### 输入

```
16 7
13 11
12 11
2 14
8 6
9 15
16 11
5 14
6 15
4 3
11 15
15 14
10 1
3 14
14 7
1 7
```

### 输出

```
6
```

# 题解

## 作者：_sunkuangzheng_ (赞：4)

**【题目分析】**

一句话题解：如果我们能动态维护区间 $[l,r]$ 内的点的连通子图的最小点数，显然原问题就可以双指针求解。而你发现前半部分就是[寻宝游戏](https://www.luogu.com.cn/problem/P3320)，于是这题做完了。(其实是两句 qwq)

---

我们考虑如何动态维护区间 $[l,r]$ 内的点的连通子图的最小点数。有一个很好感性理解的结论：求出树的 dfs 序后按照 dfs 序排序，设区间 $[l,r]$ 内的点的 dfn 序**排序后点的编号**为 $a_1,a_2,a_3,\ldots,a_{r-l},a_{r-l+1}$，那么答案为 $\text{dis}(a_1,a_2)+\text{dis}(a_2,a_3)++\ldots+\text{dis}(a_{r-l},a_{r-l+1})$，其中 $\text{dis}(x,y)$ 指节点 $x,y$ 的树上距离。这样的遍历顺序能够保证一条边最多被遍历两次，且一定是最优方案。

那么我们考虑插入节点 $x$ 对答案的贡献。我们需要找到节点 $x$ dfs 序最相近的两个节点 $u,v$，根据上面的计算式可得，$\Delta ans = \text{dis}(u,x) + \text{dis}(x,v) - \text{dis}(u,v)$。这个式子的含义是答案的变化量等于插入节点 $x$ 后新增的距离减去原本 $u,v$ 的距离。显然删除节点操作同理，只需要修改符号即可。

上面的部分可以很方便的使用 set 维护，set 内存储 dfs 序。接下来是双指针部分。很显然的是，如果区间 $[l,r]$ 计算的答案为 $k$，那么对于 $r' > r$ 一定有 $[l,r']$ 的答案 $\ge k$。$l$ 的变化同理。因此可以使用双指针维护。

---

**【代码】**

计算过程中每条边的权值被算了两次，所以判断时答案要除以 $2$。

注意我们代码计算的是边的数量，转化为点的数量时应该 $+1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct edge{int to,nxt,w;}e[500005];
int cnt,ans,u,v,head[500005],dep[500005],fa[500005][50],mx,id[500005],vis[500005],dis[500005],tot,m,n,p[500005],rk[500005],len = 2;
set<int> a;set<int> ::iterator it;
void add(int u,int v,int w){e[++cnt].to = v,e[cnt].w = w,e[cnt].nxt = head[u],head[u] = cnt;}
void dfs(int u,int fat){
	dep[u] = dep[fat] + 1,fa[u][0] = fat,id[u] = ++tot,rk[tot] = u;
	for(int i = 1;i <= 24;i ++) fa[u][i] = fa[fa[u][i-1]][i-1];
	for(int i = head[u];i;i = e[i].nxt){
		int v = e[i].to;if(v == fat) continue;
		dis[v] = dis[u] + e[i].w;dfs(v,u);
	}
}
int lca(int u,int v){
	if(dep[u] < dep[v]) swap(u,v);
	while(dep[u] > dep[v]) u = fa[u][(int)log2(dep[u]-dep[v])];
	if(u == v) return u;
	for(int i = 24;i >= 0;i --) if(fa[u][i] != fa[v][i]) u = fa[u][i],v = fa[v][i];
	return fa[u][0];
}
int dist(int u,int v){return dis[u] + dis[v] - 2 * dis[lca(u,v)];}
void upd(int x,int tp){
    if(tp) a.insert(id[x]);
    int A = (it = a.lower_bound(id[x])) == a.begin() ? *--a.end() : *--it;
    int b = (it = a.upper_bound(id[x])) == a.end() ? *a.begin() : *it;
    if(!tp) a.erase(id[x]);A = rk[A],b = rk[b];
    ans += (dist(A,x) + dist(b,x) - dist(A,b)) * (tp ? 1 : -1);
}
signed main(){
	cin >> n >> m;
	for(int i = 1;i < n;i ++)cin >> u >> v,add(u,v,1),add(v,u,1);
	dfs(1,0),upd(1,1);
    for(int l = 1,r = 1;r <= n;mx = max(mx,r - l + 1),upd(++ r,1)) 
        while(ans/2 >= m && l < r) upd(l++,0);
    cout << mx;
}
```

---

## 作者：xcxcli (赞：3)

考虑如何求包含区间$[l,r]$的子树大小，显然由每个节点到它们的$lca$处子树最小。

我们可以将区间$[l,r]$内所有的点按$dfs$序排序，则子树大小为

$(dis(a_1,a_2)+dis(a_2,a_3)+...+dis(a_{r-l},a_n)+dis(a_{r-l+1},a_1))/2$

考虑二分区间的长度，对于长度$x$，若存在区间$[i,i+x-1]$，满足子树大小小于$k$，则答案一定不小于$x$。

在询问同一长度的区间时，可以用$set$动态维护子树最小值（如何动态维护见[CF176E](https://www.luogu.org/problem/CF176E)）

```cpp
#include<stdio.h>
#include<set>
using namespace std;
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=100001;
struct E{int v,nxt;}e[N<<1];
int n,k,head[N],cnt,u,v,d[N],f[N],son[N],top[N],size[N],id[N],l,r,p,sum,ans;
struct Cmp{bool operator()(int a,int b){return id[a]<id[b];}};
set<int,Cmp>S;set<int,Cmp>::iterator it,IT;
void add(int u,int v){e[++cnt].v=v,e[cnt].nxt=head[u],head[u]=cnt;}
void dfs1(int u,int fa){
	d[u]=d[f[u]=fa]+1,size[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa)continue;
		dfs1(v,u),size[u]+=size[v];
		if(size[son[u]]<size[v])son[u]=v;
	}
}
void dfs2(int u,int t){
	top[u]=t,id[u]=++cnt;
	if(!son[u])return;
	dfs2(son[u],t);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=f[u]&&v!=son[u])dfs2(v,v);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(d[top[x]]>d[top[y]])x=f[top[x]];
		else y=f[top[y]];
	}
	return d[x]<d[y]?x:y;
}
int D(int x,int y){return d[x]+d[y]-2*d[LCA(x,y)];}
void Insert(int x){
	if(S.empty()){S.insert(x);return;}
	S.insert(x),it=S.find(x);
	if(it==S.begin())++it,sum+=D(x,*--S.end())+D(x,*it)-D(*it,*--S.end());
	else if(it==--S.end())--it,sum+=D(x,*S.begin())+D(x,*it)-D(*it,*S.begin());
	else IT=it,++IT,--it,sum+=D(*it,x)+D(*IT,x)-D(*it,*IT);
}
void Delete(int x){
	if(S.size()==1){S.clear();return;}
	it=S.find(x);
	if(it==S.begin())++it,sum-=D(x,*--S.end())+D(x,*it)-D(*it,*--S.end());
	else if(it==--S.end())--it,sum-=D(x,*S.begin())+D(x,*it)-D(*it,*S.begin());
	else IT=it,++IT,--it,sum-=D(x,*it)+D(x,*IT)-D(*it,*IT);
	S.erase(x);
}
bool OK(int x){
	S.clear(),sum=0;
	for(int i=1;i<x;++i)Insert(i);
	for(int i=x;i<=n;++i){
		Insert(i);
		if(sum<=k)return 1;
		Delete(i-x+1);
	}
	return 0;
}
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	n=rd(),k=rd();
	for(int i=1;i<n;++i)u=rd(),v=rd(),add(u,v),add(v,u);
	cnt=0,dfs1(1,0),dfs2(1,1),l=1,r=k,k=(k<<1)-2;
	while(l<=r){
		p=(l+r)>>1;
		if(OK(p))ans=p,l=p+1;
		else r=p-1; 
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：lzqy_ (赞：3)

不需要结论的树剖解法。

首先还是双指针扫 $[l,r]$（$r$ 随 $l$ 的增大而增大），考虑如何在 删点/加点 下动态维护连通块大小。

观察到，包含 $s$ 个点的连通块肯定长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/e0fg6ek7.png)

如果我们能求出 $dis(x,rt)$，那么答案就是每个点到 $x$ 的 路径并 减去 $dis(x,rt)-1$。

进一步发现，若强制让每一个点都跳到根，那么有且仅有 $\{rt \rightarrow x\}$ 路径上的点被经过了 $s$ 次，且这个遍历次数是全树最大的。也就是说，动态维护路径加后，最大值的个数就是 $dis(x,rt)$，用树剖随便搞一下就行。

有一个实现的细节是如何维护路径并。我采用的方法是点数减去遍历次数为 $0$ 的点。遍历次数为 $0$ 的点数显然很难维护，但显然每个点的遍历次数非负，所以可以转化为维护最小值的出现次数，这个就很好维护了。

另外，为了防止整棵树都被遍历到，我在根节点下多挂了一个节点，保证最小值为 $0$（其实判一下最小值的大小也可以）。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=100010;
const int N=maxn<<2;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
struct edge{
	int v,to;
}e[maxn<<1];
int head[maxn],ecnt;
void addedge(int u,int v){
	e[++ecnt].v=v,e[ecnt].to=head[u],head[u]=ecnt;
}
int d1[N],d2[N];
int D1[N],D2[N];
int lz[N];
int zson[maxn],fa[maxn],dep[maxn],dfn[maxn],DFN[maxn],top[maxn],sz[maxn];
int n,k,rt,ans,idx;
void dfs1(int fath,int x){
	sz[x]=1;
	fa[x]=fath,dep[x]=dep[fa[x]]+1;
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v^fa[x]){
			dfs1(x,e[i].v),sz[x]+=sz[e[i].v];
			if(sz[e[i].v]>sz[zson[x]]) zson[x]=e[i].v;
		}
}
void dfs2(int x){
	dfn[x]=++idx,DFN[idx]=x;
	if(zson[fa[x]]^x) top[x]=x;
	else top[x]=top[fa[x]];
	if(zson[x]) dfs2(zson[x]); 
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v!=fa[x]&&e[i].v!=zson[x]) dfs2(e[i].v);
}
il void pushup1(int i){
	d1[i]=min(d1[i<<1],d1[i<<1|1]);
	if(d1[i<<1]<d1[i<<1|1]) d2[i]=d2[i<<1];
	else if(d1[i<<1]>d1[i<<1|1]) d2[i]=d2[i<<1|1];
	else d2[i]=d2[i<<1]+d2[i<<1|1];
}
il void pushup2(int i){
	D1[i]=max(D1[i<<1],D1[i<<1|1]);
	if(D1[i<<1]>D1[i<<1|1]) D2[i]=D2[i<<1];
	else if(D1[i<<1]<D1[i<<1|1]) D2[i]=D2[i<<1|1];
	else D2[i]=D2[i<<1]+D2[i<<1|1];	
}
il void pushdown(int i){
	if(!lz[i]) return ;
	d1[i<<1]+=lz[i],D1[i<<1]+=lz[i];
	d1[i<<1|1]+=lz[i],D1[i<<1|1]+=lz[i];
	lz[i<<1]+=lz[i],lz[i<<1|1]+=lz[i],lz[i]=0;
}
void build(int i,int l,int r){
	if(l==r){
		d2[i]=D2[i]=1;
		return ;
	}int mid=l+r>>1;
	if(mid>=l) build(i<<1,l,mid);
	if(mid<r) build(i<<1|1,mid+1,r);
	pushup1(i),pushup2(i);
}
void Modify(int i,int l,int r,int L,int R,int x){
	if(l>=L&&r<=R){
		d1[i]+=x,D1[i]+=x,lz[i]+=x;
		return ;
	}pushdown(i);
	int mid=l+r>>1;
	if(mid>=L) Modify(i<<1,l,mid,L,R,x);
	if(mid<R) Modify(i<<1|1,mid+1,r,L,R,x);
	pushup1(i),pushup2(i);
}
void Add(int x,int k){while(x) Modify(1,1,n+1,dfn[top[x]],dfn[x],k),x=fa[top[x]];} 
int main(){
	int x,y;
	n=read(),k=read();
	for(int i=1;i<n;i++){
		x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	addedge(1,n+1);
	dfs1(0,1),dfs2(1),build(1,1,n+1);
	for(int l=1,r=1;l<=n;Add(l++,-1)){
		if(r==l) Add(r++,1); 
		while(r<=n){
			Add(r,1);
			if(n+2-d2[1]-D2[1]<=k) r++;
			else{Add(r,-1);break;}
		}ans=max(ans,r-l);
	}printf("%d\n",ans);
	return 0;
}
```


---

## 作者：wind_whisper (赞：2)

## $\text{Description}$
有一棵 $n$ 个结点的树，树上结点从 $1$ 到 $n$ 标号。

定义树上一个连通子图的权值为最长的区间 $[l,r]$ 的长度，满足标号在 $[l,r]$ 之间的结点均在这个连通子图中。

现在请你求出树上所有的结点数量不超过 $k$ 的连通子图的权值最大值。

## $\text{Solution}$
大结论题。  
做完本题可以水一下[这个](https://www.luogu.com.cn/problem/P3320)。  

结论：一棵给定的树，若给出若干关键点，将其按照 dfs 序排序后为 $a_{1...k}$，则它们的最小导出子图的边权和为 $dis(a_1,a_2)+dis(a_2,a_3)+...+dis(a_k,a_1)$ 的一半。  
证明：每条边都会被算两遍。（~~感性理解一下~~）  

有这个结论后，本题就简单了。二分答案，然后双指针扫一遍，不断维护一个 set 计算当前导出图的边权和即可，点数就是再加一。  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1e5+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m;
struct node{
  int to,nxt;
}p[N<<1];
int fi[N],cnt;
inline void addline(int x,int y){
  p[++cnt]=(node){y,fi[x]};fi[x]=cnt;
}
int pl[N][20],pos[N],siz[N],tim,dep[N];
void dfs(int x,int fa){
  pos[x]=++tim;siz[x]=1;
  dep[x]=dep[fa]+1;
  pl[x][0]=fa;
  for(int k=1;pl[x][k-1];k++) pl[x][k]=pl[pl[x][k-1]][k-1];
  for(int i=fi[x];~i;i=p[i].nxt){
    int to=p[i].to;
    if(to==fa) continue;
    dfs(to,x);
    siz[x]+=siz[to];
  }
  return;
}
inline int Lca(int x,int y){
  if(pos[x]<=pos[y]&&pos[y]<=pos[x]+siz[x]-1) return x;
  for(int k=17;k>=0;k--){
    int o=pl[x][k];
    if(!o||(pos[o]<=pos[y]&&pos[y]<=pos[o]+siz[o]-1)) continue;
    x=pl[x][k];
    //printf("k=%d x=%d\n",k,x);
  }
  return pl[x][0];
}
inline int dis(int x,int y){
  int lca=Lca(x,y);
  //printf("  dis: x=%d y=%d lca=%d res=%d\n",x,y,lca,dep[x]+dep[y]-2*dep[lca]);
  return dep[x]+dep[y]-2*dep[lca];
}
struct cmp{
  bool operator ()(const int a,const int b){return pos[a]<pos[b];}
};
set<int,cmp>s;
set<int,cmp>::iterator it;
int now;
inline int Pre(int x){
  it=s.find(x);
  if(it==s.begin()) return (*s.rbegin());
  else{
    it--;return (*it);
  }
}
inline int Nxt(int x){
  it=s.find(x);
  it++;
  if(it==s.end()) return (*s.begin());
  else return (*it);
}
inline void add(int x){
  if(s.empty()){
    s.insert(x);return;
  }
  s.insert(x);
  int pre=Pre(x),nxt=Nxt(x);
  now-=dis(pre,nxt);
  now+=dis(pre,x)+dis(x,nxt);
  return;
}
inline void del(int x){
  if(s.size()==1){
    s.erase(x);return;
  }
  int pre=Pre(x),nxt=Nxt(x);
  now-=dis(pre,x)+dis(x,nxt);
  now+=dis(pre,nxt);
  s.erase(x);
  return;
}
bool check(int k){
  now=0;s.clear();
  for(int i=1;i<=k;i++) add(i);
  if(now/2+1<=m) return true;
  //printf("(%d %d) now=%d\n",1,k,now);
  for(int i=k+1;i<=n;i++){
    del(i-k);add(i);
    //printf("(%d %d) now=%d\n",i-k+1,i,now);
    if(now/2+1<=m) return true;
  }
  return false;
}

signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  memset(fi,-1,sizeof(fi));cnt=-1;
  n=read();m=read();
  for(int i=1;i<n;i++){
    int x=read(),y=read();
    addline(x,y);addline(y,x);
  }
  dfs(1,0);
  //printf("lca=%d\n",Lca(2,1));
  //printf("check=%d\n",check(3));
  //return 0;
  int st=1,ed=n;
  while(st<ed){
    int mid=(st+ed+1)>>1;
    if(check(mid)) st=mid;
    else ed=mid-1;
  }
  printf("%d\n",st);
  return 0;
}
/*
*/

```


---

## 作者：封禁用户 (赞：1)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF372D)

[CF](https://codeforces.com/problemset/problem/372/D)

### 分析

要求选一个大小不超过 $k$ 的连通块，使得最长的区间 $[l,r]$ 都在连通块中。我们可以转化成，一个包含所有 $[l,r]$ 的最小连通块的大小小于等于 $k$。

从区间最长这个要求，不难发现可以尺取 $[l,r]$，然而现在的问题是如何判断 $[l,r]$ 所在的最小连通块的大小。

我们先把所有的关键点按照 dfs 序排序，插入或删除一个点时，找到它的前驱和后继。特别地，没有前驱时最后一个点被认为是它的前驱；没有后继时，第一个点被认为是它的后继。

它对连通块边数的贡献就是 $\dfrac{\operatorname{dis}(u,x) + \operatorname{dis}(x,v) - \operatorname{dis}(u,v)}{2}$。

注意最后边数转化为点数应当加一。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1;
	x = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
	x *= p;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 100010
int head[N],nxt[N<<1],to[N<<1],cnt = 0;
inline void add(int u,int v)
{
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}
int dep[N],f[N][20],dfn[N],times = 0,sum = 0,ans = 1;
class cmp
{
	public:
		inline bool operator()(const int &u,const int &v)
			{return dfn[u] < dfn[v];}
};
set<int,cmp> s;
int n,k;
void dfs(int u,int fa)
{
	dfn[u] = ++times;
	f[u][0] = fa;
	dep[u] = dep[fa] + 1;
	for(register int i = head[u];i;i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs(v,u); 
	}
}
inline int lca(int u,int v)
{
	if(dep[u] < dep[v]) swap(u,v);
	D(i,18,0)
		if(dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if(u == v) return u;
	D(i,18,0)
		if(f[u][i] != f[v][i])
			u = f[u][i],v = f[v][i];
	return f[u][0]; 
}
inline int dis(int u,int v)
{
	return dep[u] + dep[v] - 2 * dep[lca(u,v)];
}
inline int val(int x)
{
	if(!s.size()) return 0;	
	auto it = s.lower_bound(x);
	int u,v;
	if(it == s.end()) v = *s.begin();
	else v = *it;
	if(it == s.begin()) u = *(--s.end());
	else u = *(--it);
	return dis(u,x) + dis(x,v) - dis(u,v);
}
inline void add(int x)
{
	sum += val(x);
	s.insert(x);
}
inline void del(int x)
{
	s.erase(x);
	sum -= val(x);
}
int main()
{
	read(n),read(k);
	F(i,1,n-1)
	{
		int u,v;
		read(u),read(v);
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	F(i,1,18)
		F(j,1,n)
			f[j][i] = f[f[j][i-1]][i-1]; 
	int l = 1,r = 0;
	while(l <= n)
	{
		while(r <= n&&sum/2+1 <= k) 
		{
			++r;
			if(r <= n) add(r);
		}
		ans = max(ans,r-l);
		del(l++);
	}
	write(ans);
	return 0;
}
```

---

## 作者：Acc_Robin (赞：1)

# CF372D Choosing Subtree is Fun 题解

[更高更妙的阅读体验](https://accrobin.github.io/2021/11/10/solver/372D/)

[传送门](https://www.luogu.com.cn/problem/CF372D)

## 题意

给定一棵 $n$ 个节点的树和定值 $k$ ，要求求出最大的 $r-l+1$ 满足 $[l,r]$ 区间中所有点构成的虚树的大小不超过 $k$。

$1\le k\le n\le 10^5$

## 题解

注意到：随着区间左端点增大，右端点也是单调的，所以可以使用**双指针**。

现在我们要做的就是维护一个点集的虚树大小，支持插入和删除。使用 `set` 维护 dfs 序，像 CF176E 一样做即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
enum{N=100009};
vector<int>G[N];
set<pair<int,int>>s;
int d[N],f[N][20],p[N],t;
void dfs(int u){
 p[u]=++t,d[u]=d[*f[u]]+1;
 for(int i=0;f[u][i];++i)f[u][i+1]=f[f[u][i]][i];
 for(int v:G[u])if(v!=*f[u])*f[v]=u,dfs(v);
}
auto LCA=[](int x,int y){
 if(d[x]<d[y])swap(x,y);
 for(int i=18;~i;--i)if(d[f[x][i]]>=d[y])x=f[x][i];
 if(x==y)return x;
 for(int i=18;~i;--i)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
 return *f[x];
};
auto wk=[](auto i){return make_pair(i==s.begin()?--s.end():prev(i),i==--s.end()?s.begin():next(i));};
auto ds=[](int x,int y){return d[x]+d[y]-2*d[LCA(x,y)];};
auto cal=[](int x,int y,int z){return ds(x,y)+ds(y,z)-ds(x,z);};
int main(){
 ios::sync_with_stdio(0),cin.tie(0);
 int n,k,i,j,x,y,z=0;set<pair<int,int>>::iterator it,i1,i2;
 for(cin>>n>>k,i=1;i<n;++i)cin>>x>>y,G[x].emplace_back(y),G[y].emplace_back(x);
 for(x=0,dfs(i=j=1);j<=n;z=max(z,j-i+1),++j){
  tie(i1,i2)=wk(it=s.emplace(p[j],j).first),x+=cal(i1->second,j,i2->second);
  for(;i<=n&&x/2+1>k;++i)tie(i1,i2)=wk(it=s.find({p[i],i})),x-=cal(i1->second,i,i2->second),s.erase(it);
 }
 cout<<z<<'\n';
}
```

## 小细节

发现枚举左端点并不好实现，所以可以枚举右端点。

---

## 作者：CQ_Bab (赞：0)

# 思路
首先我们发现如果正着做不是很好做，所以我们考虑二分答案然后我们发现现在需要求将每一段区间 $l\sim l+mid-1$ 两两配对求出它们能覆盖到的点的数量，一开始可能会觉得不太好做，但是如果你学过虚树，可能知道一种按 dfs 序排序的方法，就是指把在区间中的所有点都按 dfs 序排序然后加上相邻之间的边数（第一个和最后一个也要）最后将数量除以二就是总边数。而这道题求的是点数所以考虑将答案加一即可。至于维护这个过程其实很简单只需要开一个 set 然后对于每一次插入和删除分别将贡献变一下即可。
# 代码
~~石山代码~~。
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int n,k;
const int N=1e5+10;
vector<int>v[N];
int dep[N],dfn[N],idx,f[N][20];
void dfs(int x,int fa) {
	dfn[x]=++idx;
	dep[x]=dep[fa]+1;
	f[x][0]=fa;
	for(auto to:v[x]) {
		if(to==fa) continue;
		dfs(to,x);
	}
}
struct node{
	int x;
	friend bool operator<(const node&a,const node&b) {
		return dfn[a.x]<dfn[b.x];
	}
};
set<node>s;
void init() {
	rep(j,1,19) rep(i,1,n) f[i][j]=f[f[i][j-1]][j-1];
}
int lca(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	rep1(i,19,0) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	rep1(i,19,0) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
int dis(int x,int y) {
	int fa=lca(x,y);
	return dep[x]+dep[y]-2*dep[fa];
}
bool check(int x) {
	int l=1,sum=false;
	s.clear();
	rep(i,1,x) s.insert({i});
	for(auto it=s.begin();it!=s.end();it++) {
		auto it1=it;
		it1++;
		if(it1==s.end()) break;
		sum+=dis((*it).x,(*it1).x);
	}
	auto itt=s.begin(),it2=s.end();
	it2--;
	sum+=dis(itt->x,it2->x);
	if(sum/2+1<=k) return 1;
	rep(i,x+1,n) {
		auto it=s.find({l});
		auto lst=it,nxt=it;
		auto ed=s.end();
		ed--;
		auto chu=s.begin();
		sum-=dis(ed->x,chu->x);
		if(it!=s.begin()) {
			lst--;
			sum-=dis(it->x,lst->x);
		}
		if(it!=ed) {
			nxt++;
			sum-=dis(nxt->x,it->x);
		}
		if(it!=ed&&it!=s.begin()) {
			sum+=dis(lst->x,nxt->x);
		}
		s.erase({l});
		l++;
		s.insert({i});
		it=s.find({i});
		lst=nxt=it;
		if(it!=s.begin()) {
			lst--;
			sum+=dis(it->x,lst->x);
		}
		ed=s.end();
		ed--;
		if(it!=ed) {
			nxt++;
			sum+=dis(nxt->x,it->x);
		}
		if(it!=ed&&it!=s.begin()) {
			sum-=dis(lst->x,nxt->x);
		}
		chu=s.begin();
		ed=s.end();
		ed--;
		sum+=dis(chu->x,ed->x);
		if(sum/2+1<=k) {
			return 1;
		}
	}return false;
}
void solve() {
	in(n),in(k);
	rep(i,1,n-1) {
		int x,y;
		in(x),in(y);
		v[x].pb(y);
		v[y].pb(x);
	}
	dfs(1,0);
	init();
	int l=1,r=n,res=0;
	while(l<=r) {
		int mid=l+r>>1;
		if(check(mid)) l=mid+1,res=mid;
		else r=mid-1;
	}
	printf("%lld\n",res);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：yqr123YQR (赞：0)

先二分一个区间长度，再枚举区间 $[l,r]$，现在只需验证最小的包含各个点的连通块大小是否小于等于 $k$。（当然可以用双指针，但是我没想到）

很容易想到，直接采用虚树的架构即可，而虚树的总边权就是 dfn 序下的关键点相邻两项距离和的一半；对应到原树上，总点数即总边权 $+1$。所以用一个 set 维护，插入、删除时讨论一下前驱后继的贡献即可。

若是按这种方法，就是这样的：
```cpp
bool check(int mid)
{
	ans = 0;
	std::set<int> S;
	auto ins = [&](int i) {
		auto it = S.lower_bound(dfn[i]);
		if(it != S.end() && it != S.begin()) ans -= dist(rk[*it], rk[*prev(it)]);
		if(it != S.end()) ans += dist(rk[*it], i);
		if(it != S.begin()) ans += dist(rk[*prev(it)], i);
		S.insert(dfn[i]);
	};
	auto del = [&](int i) {
		S.erase(dfn[i]);
		auto it = S.lower_bound(dfn[i]);
		if(it != S.end()) ans -= dist(rk[*it], i);
		if(it != S.begin()) ans -= dist(rk[*prev(it)], i);
		if(it != S.end() && it != S.begin()) ans += dist(rk[*it], rk[*prev(it)]);
	};
	for(int i = 1; i <= mid; i++) ins(i);
	for(int i = mid; i <= n; i++)
	{
		if((ans + dist(rk[*S.begin()], rk[*S.rbegin()]) >> 1) < k) return true;
		if(i == n) return false;
		ins(i + 1);
		del(i - mid + 1);
	}
}
```

（如果不嫌麻烦，可以另用一个 set 维护虚树的所有结点，以此统计虚树边权和（每个点到其与前一个点的 LCA 的距离和），类似下面代码：）
```cpp
//...
void erase(int k, std::set<int> &T)
{
	if(!--vis[k])//vis 记录每个点被重复插入多少次
	{
		T.erase(dfn[k]);
		auto it = T.lower_bound(dfn[k]);
		if(it != T.begin()) ans -= dep[k] - dep[lca(rk[*prev(it)], k)];
		if(it != T.end()) ans -= dep[rk[*it]] - dep[lca(rk[*it], k)];
		if(it != T.end() && it != T.begin()) ans += dep[rk[*it]] - dep[lca(rk[*it], rk[*prev(it)])];
	}
}
void insert(int k, std::set<int> &T)
{
	if(++vis[k] == 1)
	{
		auto it = T.lower_bound(dfn[k]);
		if(it != T.end() && it != T.begin()) ans -= dep[rk[*it]] - dep[lca(rk[*it], rk[*prev(it)])];
		if(it != T.begin()) ans += dep[k] - dep[lca(rk[*prev(it)], k)];
		if(it != T.end()) ans += dep[rk[*it]] - dep[lca(rk[*it], k)];
		T.insert(dfn[k]);
	}
}
bool check(int mid)
{
	for(int i = 1; i <= n; i++) vis[i] = 0;
	ans = 1;
	std::set<int> S, whole;
	auto ins = [&](int i) {
		auto it = S.lower_bound(dfn[i]);
		if(it != S.end() && it != S.begin()) erase(lca(rk[*it], rk[*prev(it)]), whole);
		if(it != S.end()) insert(lca(rk[*it], i), whole);
		if(it != S.begin()) insert(lca(rk[*prev(it)], i), whole);
		S.insert(dfn[i]), insert(i, whole);
	};
	auto del = [&](int i) {
		S.erase(dfn[i]), erase(i, whole);
		auto it = S.lower_bound(dfn[i]);
		if(it != S.end()) erase(lca(rk[*it], i), whole);
		if(it != S.begin()) erase(lca(rk[*prev(it)], i), whole);
		if(it != S.end() && it != S.begin()) insert(lca(rk[*it], rk[*prev(it)]), whole);
	};
	for(int i = 1; i <= mid; i++) ins(i);
	for(int i = mid; i <= n; i++)
	{
		if(ans <= k) return true;
		if(i == n) return false;
		ins(i + 1);
		del(i - mid + 1);
	}
}
int main()
{
	// init
	int l = 1, r = n;
	while(l < r)
	{
		int mid = l + r + 1 >> 1;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", l);
	return 0;
}
```

---

## 作者：liujiaxi123456 (赞：0)

## 关键词：正难则反
### 思路：
直接用连通子图求节点区间做显然不好做，**正难则反**，考虑通过节点区间来构造连通子图。

考虑如何枚举区间，较为显然的是二分答案，但复杂度会稍微高一点，这里采用的是双指针。当 $l$ 尽可能靠左且 $\left[l, r+1\right]$ 满足条件时，$\left[ll<l,r\right]$ 显然不存在满足条件的区间（否则 $l$ 就不是尽可能靠左了），而 $\left[ll\ge l,r\right]$ 则显然不优秀，所以 $r$ 必然只增不减。$l$ 的证明同理。

此时需要维护动态加点/删点的最小连通子图大小，而这实际上跟[寻宝游戏](https://www.luogu.com.cn/problem/P3320)是一样的。

当我们知道一个区间的最小连通子图大小，只需要把它跟 $k$ 比较即可知道是否满足条件了。
### Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 1e5+5;

namespace EDGE {
	int sz, head[Maxn];
	struct Edge { int next, to; } edge[Maxn*2];
	inline void Add_edge(int u, int v) {
		edge[++sz] = {head[u], v};
		head[u] = sz;
	}
} using namespace EDGE;

namespace Josh_zmf {
	
	int N, K, st[Maxn][20], logg[Maxn]; set <int> s; bool flag[Maxn];
	int dfnnum, dfn[Maxn], nfd[Maxn], dep[Maxn];

	inline void dfs(int u, int faa) {
		dep[u] = dep[faa]+1, nfd[dfn[u] = ++dfnnum] = u, st[dfn[u]][0] = faa;
		for(int i=head[u]; i; i=edge[i].next) if(edge[i].to^faa) dfs(edge[i].to, u);
	}

	inline int main() {
		cin>> N>> K;
		for(int i=1, u, v; i<N; i++)	cin>> u>> v, Add_edge(u, v), Add_edge(v, u);
		auto get = [&](const int &u, const int &v) { return dfn[u] < dfn[v] ?u :v; };
		auto Build_LCA = [&]() {
			dfs(1, 0);
			for(int i=2; i<=N; i++)	logg[i] = logg[i/2] + 1;
			for(int j=1; j<=logg[N]; j++)
				for(int i=1; i+(1<<j)-1<=N; i++)
					st[i][j] = get(st[i][j-1], st[i+(1<<(j-1))][j-1]);
		}; Build_LCA();
		auto LCA = [&](int u, int v) {
			if(u == v)	return u;
			if(dfn[u] > dfn[v])	swap(u, v);
			u = dfn[u]+1, v = dfn[v];
			int k = logg[v-u+1];
			return get(st[u][k], st[v-(1<<k)+1][k]);
		};
		auto dis = [&](const int &u, const int &v) { return dep[u] + dep[v] - 2*dep[LCA(u, v)]; };
		int ans = 0; set <int>::iterator it; 
		auto update = [&](int u, bool type) {
			if(type)	s.insert(dfn[u]);
			int pre = nfd[(it=s.lower_bound(dfn[u])) == s.begin() ?*--s.end() :*--it];
			int nxt = nfd[(it=s.upper_bound(dfn[u])) == s.end() ?*s.begin() :*it];
			if(!type)	s.erase(dfn[u]);
			ans += (type ?1 :-1)*(dis(pre, u) + dis(u, nxt) - dis(pre, nxt));
		};
		int res = 0;
		for(int l=1, r=1; r<=N; res=max(res, r-l+1), r++) {
			update(r, 1);
			for(; ans/2>=K && l<r; update(l++, 0));
		}
		cout<< res;
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```
### 结语：
都看到这里了，点个赞再走吧。：）

---

## 作者：IkunTeddy (赞：0)

# 题目分析

像这种连续区间为答案的，我们考虑双指针求解。

现在就是考虑如何用最少的边把这 $\left[l,r \right]$ 的连起来，我们发现这好像就是[P3320 [SDOI2015] 寻宝游戏](https://www.luogu.com.cn/problem/P3320)。

按照 dfs 序的大小关系，由小到大去走点一定最优，所以我们用一个 set 维护相邻两点的距离和即可。

# Code

目前最优解。

```cpp
#include<bits/stdc++.h>
using namespace std;
//
const int maxn=1e5+10;
int n,k,pl,pr,ans,mx;
struct Edge{
	int v,next;
}edge[maxn<<1];
int head[maxn],tot;
void add_edge(int u,int v){
	edge[++tot].v=v;
	edge[tot].next=head[u];
	head[u]=tot;
}
int fa[maxn],dfn[maxn],dfncnt,st[maxn][20],Log[maxn],vis[maxn],dis[maxn];
void dfs(int u,int f){
	fa[u]=f;
	dfn[u]=++dfncnt;
	dis[u]=dis[fa[u]]+1;
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].v;
		if(v==fa[u])continue ;
		dfs(v,u);
	}
}
int get(int x,int y){return dfn[x]<dfn[y]?x:y;}
void init_ST(){
	Log[0]=-1;
	for(int i=1;i<=n;i++)Log[i]=Log[i>>1]+1;
	for(int i=1;i<=n;i++)st[dfn[i]][0]=fa[i];
	for(int j=1;j<=Log[n];j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=get(st[i][j-1],st[i+(1<<j-1)][j-1]);
		}
	}
}
int LCA(int x,int y){
	if(x==y)return x;
	if(dfn[x]>dfn[y])swap(x,y);
	int l=dfn[x]+1,r=dfn[y];
	int k=Log[r-l+1];
	return get(st[l][k],st[r-(1<<k)+1][k]);
}
ll dist(int x,int y){return dis[x]+dis[y]-2*dis[LCA(x,y)];}
struct SET{
	int x;
	bool operator < (const SET &it)const{
		return dfn[x]<dfn[it.x];
	}
};
set<SET>s;
#define Set set<SET>::iterator
void insert(int x){
	Set it=s.insert({x}).first,pre,nxt;
	pre=nxt=it;
	pre--,nxt++;
	if(pre!=s.begin()&&nxt!=s.end())ans-=dist(pre->x,nxt->x);
	if(pre!=s.begin())ans+=dist(pre->x,x);
	if(nxt!=s.end())ans+=dist(x,nxt->x);
}
void delet(int x){
	Set it=s.lower_bound({x}),pre,nxt;
	pre=nxt=it;
	pre--,nxt++;
	if(pre!=s.begin()&&nxt!=s.end())ans+=dist(pre->x,nxt->x);
	if(pre!=s.begin())ans-=dist(pre->x,x);
	if(nxt!=s.end())ans-=dist(x,nxt->x);
	s.erase(it);
}
ll getsum(){ //计算头尾
	if(s.size()<3)return 0;
	Set head=s.begin(),tail=s.end();
	head++,tail--;
	return dist(head->x,tail->x);
}
int main(){
	cin>>n>>k;
	s.insert({0});
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	init_ST();
	pl=1,pr=1;
	for(;pr<=n;pr++){
		insert(pr);
		while(pl<pr&&(ans+getsum())/2+1>k)delet(pl),pl++;
		mx=max(mx,pr-pl+1);
	}
	cout<<mx<<'\n';
	
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

一天一道水题题解，$\color{red} \rm IGM$ 远离我。

包含 $[l,r]$ 的最小子树是 $l$，$l+1$，$\dots$，$r$ 构成的虚树。一眼发现要用双指针，于是变成动态维护虚树的问题。

然后？~~我明明做过寻宝游戏，我咋忘记了这道题的题意？一看就是年少无知贺的。~~

考虑新加入一个点，分为两种情况；删除一个点，对应上文两种情况的逆操作：

![](https://s21.ax1x.com/2024/03/26/pF5LPl6.png)

模拟即可。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,k,tot,sze[MAXN],dfn[MAXN],tr[MAXN],fa[MAXN][20],dep[MAXN],rev[MAXN],tans;
vector<int> G[MAXN];
set<int> st; //用来求虚树的根
void dfs(int u,int f) {
	dfn[u]=++tot,sze[u]=1,fa[u][0]=f,dep[u]=dep[f]+1,rev[tot]=u;
	ffor(i,1,19) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(auto v:G[u]) if(v!=f) dfs(v,u),sze[u]+=sze[v];
	return ;
}
int lca(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);
	int dt=dep[u]-dep[v],id=0;
	while(dt) {if(dt&1) u=fa[u][id];dt>>=1,id++;}
	if(u==v) return u;
	roff(i,19,0) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
void update(int pos,int v) {while(pos<=n) tr[pos]+=v,pos+=pos&-pos;return ;}
int query(int pos) {int ans=0;while(pos) ans+=tr[pos],pos-=pos&-pos;return ans;}
int calc_rt(void) {if(st.empty()) return -1;return lca(rev[*st.begin()],rev[*(--st.end())]);}
int is_anc(int u,int f) {return dfn[u]>=dfn[f]&&dfn[u]<=dfn[f]+sze[f]-1;}
int qtree(int u) {return query(dfn[u]+sze[u]-1)-query(dfn[u]-1);}
void add(int u) {
	if(st.empty()) return st.insert(dfn[u]),update(dfn[u],1),tans=1,void();
	int ort=calc_rt(),flg1=is_anc(u,ort);
	if(qtree(u)&&is_anc(u,calc_rt())) return st.insert(dfn[u]),update(dfn[u],1),void();
	if(!flg1) {int nrt=lca(ort,u);return tans+=dep[ort]+dep[u]-2*dep[nrt],st.insert(dfn[u]),update(dfn[u],1),void();}
	if(!qtree(u)) {
		int v=u;
		roff(i,19,0) if(fa[v][i]&&qtree(fa[v][i])==0) v=fa[v][i];
		return update(dfn[u],1),st.insert(dfn[u]),tans+=dep[u]-dep[v]+1,void();
	}
	else return update(dfn[u],1),st.insert(dfn[u]),void();
}
void del(int u) {
	int ort=calc_rt();
	st.erase(dfn[u]);
	int nrt=calc_rt();
	if(st.empty()) return update(dfn[u],-1),tans=0,void();
	if(ort==nrt) {
		if(qtree(u)==1) {
			int v=u;
			roff(i,19,0) if(fa[v][i]&&qtree(fa[v][i])==1) v=fa[v][i];
			return update(dfn[u],-1),tans-=dep[u]-dep[v]+1,void();
		}
		else return update(dfn[u],-1),void();
	}
	else return update(dfn[u],-1),tans-=dep[u]+dep[nrt]-2*dep[ort],void();
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k; ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);} dfs(1,0);
	int l=1,r=0,ans=0;
	while(r<=n) {
		ans=max(ans,r-l+1);
		while(r<n) {
			add(++r);
			if(tans>k) break ;
//			cout<<l<<' '<<r<<' '<<tans<<'\n';
			ans=max(ans,r-l+1);
		}
		if(r==n) break ;
		while(tans>k) del(l++);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

套个双指针，转化成求 $[l,r]$ 之间编号的节点的最小连通子图大小。

首先有一个结论，即将 $[l,r]$ 按照 dfs 序排序，设为 $p_1\sim p_{r-l+1}$，设 $p_{r-l+2}=p_1$，则最小连通子图大小为 $\frac{\sum_{i=1}^{r-l+1}\operatorname{dis}(p_i,p_{i+1})}{2}+1$。使用虚树容易证明。

考虑双指针要求添加和删除节点。只需要找到大于 $x$ 节点 dfs 序的第一个点 $p$，小于 $x$ 节点 dfs 序的第一个点 $q$，在答案上加上 $\operatorname{dis}(x,p)+\operatorname{dis}(x,q)-\operatorname{dis}(p,q)$ 即可，容易使用 set 维护。删除类似，注意特判 $x$ 最小与 $x$ 最大的情况。

总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
vector<int> vc[100005];
int dep[100005],f[100005][20],id[100005],cnt,rl[100005];
void dfs1(int now,int fa){
	f[now][0]=fa,dep[now]=dep[fa]+1,id[now]=++cnt,rl[cnt]=now;
	for(int i=1;i<=19;i++) f[now][i]=f[f[now][i-1]][i-1];
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs1(v,now);
	}
}
int dis(int u,int v){
	int ou=u,ov=v;
	if(dep[u]>dep[v]) swap(u,v);
	for(int i=19;i>=0;i--) if(dep[f[v][i]]>=dep[u]) v=f[v][i];
	if(u==v) return dep[ou]+dep[ov]-2*dep[u];
	for(int i=19;i>=0;i--) if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return dep[ou]+dep[ov]-2*dep[f[u][0]];
}
set<int> st;
int tmp;
void add(int now){
	if(!st.size()){
		st.insert(id[now]);
		return ;
	}
	auto lst=st.lower_bound(id[now]),nxt=st.lower_bound(id[now]);
	if(lst!=st.begin()) lst=prev(lst);
	else lst=prev(st.end());
	if(nxt==st.end()) nxt=st.begin();
	int p=*lst,q=*nxt;
	tmp-=dis(rl[p],rl[q]);
	tmp+=dis(now,rl[p])+dis(now,rl[q]);
	st.insert(id[now]);
}
void del(int now){
	if(st.size()==1){
		st.erase(st.find(id[now]));
		return ;
	}
	st.erase(st.find(id[now]));
	auto lst=st.lower_bound(id[now]),nxt=st.lower_bound(id[now]);
	if(lst!=st.begin()) lst=prev(lst);
	else lst=prev(st.end());
	if(nxt==st.end()) nxt=st.begin();
	int p=*lst,q=*nxt;
	tmp+=dis(rl[p],rl[q]);
	tmp-=dis(now,rl[p])+dis(now,rl[q]);
}
signed main(){
	int n,k; cin>>n>>k;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	dfs1(1,0);
	int m=0,maxv=0;
	for(int i=1;i<=n;i++){
		while(1){
			if(m==n) break;
			add(++m);
			if(tmp/2+1>k){
				del(m--);
				break;
			}
		}
		maxv=max(maxv,m-i+1);
		del(i);
	}
	cout<<maxv;
	return 0;
}
```

---

