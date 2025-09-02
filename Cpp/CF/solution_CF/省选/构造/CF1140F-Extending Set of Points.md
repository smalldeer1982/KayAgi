# Extending Set of Points

## 题目描述

给定一个二维点集 $S$，我们定义其扩展 $E(S)$ 为如下算法的结果：

新建一个二维点集 $R$，初始时 $R = S$。然后，只要存在四个数 $x_1$、$y_1$、$x_2$ 和 $y_2$，使得 $(x_1, y_1) \in R$，$(x_1, y_2) \in R$，$(x_2, y_1) \in R$，且 $(x_2, y_2) \notin R$，就将 $(x_2, y_2)$ 加入 $R$。当无法再找到这样的四元组时，$R$ 即为算法的结果。

现在，给定一个初始为空的二维点集 $S$，你需要处理两种操作：向 $S$ 中添加一个点，或从 $S$ 中删除一个点。每次操作后，你需要计算 $E(S)$ 的大小。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
1 1
1 2
2 1
2 2
1 2
1 3
2 1
```

### 输出

```
1 2 4 4 4 6 3 ```

# 题解

## 作者：command_block (赞：17)

很好的一道线段树分治模板题啊！

真心适合入门，纪念我的第一道线段树分治。

------------

先考虑没有删除该怎么做。

对于一个点$(x,y)$，他只能跟同行和同列的点相关。

一系列相关的点会被扩展成一个“表格”。

看到“相关”性，我们可以联想到并查集：

我们可以把$(x,y)$,看成二分图中的边。

如果二分图中的一个联通块包括$xc$个左方节点，$yc$个右方节点，那么该联通快对于答案的贡献就是$xc*yc$。

这可以用并查集方便地维护。

------------

然而这题带删除，这就不是很好办了。

我们考虑维护一个时间轴：

```cpp
如样例：
(1,1) time:1~7
(1,2) time:2~4
(2,1) time:3~6
(2,2) time:4~7
(1,3) time:6~7

(2,2)              |-----------|
(2,1)          |-----------|
(1,2)      |-------|       |---|(1,3)
(1,1)  |-----------------------|
-------1---2---3---4---5---6---7-->
```

可以看到每个点都有一个出现的时间段。

我们可以采取如下暴力：

下称“状态$t$”为时刻为$t$是所有存在的点加入并查集后，并查集的状态。

弄$m$个链表，暴力把一个点挂在出现区间的链表里。

那么如果我们要获得“状态$t$”，只要把并查集清空然后把第$t$个链表里的操作做一遍就好了。

这样子复杂度高达$O(m^2\alpha(m))$,肯定是布星的。

于是你看到了熟悉的区间，想到了线段树。

我们可以建立一颗时间轴上的线段树，然后每个节点挂一个链表。

然后把一个区间对应的$O(\log m)$个节点挂上该操作。

然后我们用某种奥妙重重的方式让儿子继承父亲的操作，就可以做到在$t$号叶节点达到状态$t$。

一个简单的想法是使用可持久化并查集，然后儿子引用父亲，不过完全没这个必要。

我们发现求答案的过程是个`dfs`的过程，我们退出某个节点的时候，可以把该节点上挂的操作撤回，然后就能得到父节点的状态了。

并查集是支持$O(\log n)$撤回的,按秩合并即可。

理论上来讲所有非均摊的数据结构都是资瓷撤回的，所以这个算法非常的好用。

更多技巧请见 : [一些常用的数据结构维护手法](https://www.luogu.com.cn/blog/command-block/yi-suo-chang-yong-di-shuo-ju-jie-gou-wei-hu-shou-fa)

**Code:**

```cpp
#include<algorithm>
#include<vector>
#include<cstdio>
#include<map>
#define MaxN 300500
using namespace std;
inline int read()
{
  register int X=0;
  register char ch=0;
  while(ch<48||ch>57)ch=getchar();
  while(ch>=48&&ch<=57)X=X*10+(ch^48),ch=getchar();
  return X;
}
int n,m;
struct Point
{int l,r,x,y;}
b[MaxN];
struct xyPoint
{int x,y;}wfc;
vector<xyPoint> g[MaxN<<2];
int tn;
map<pair<int,int>,int> mmp;
int f[MaxN<<1],xc[MaxN<<1],yc[MaxN<<1];
struct Data
{int x,y;}
stk[MaxN];
int top;
long long ans;
int findf(int x)
{return f[x]==x ? x :findf(f[x]);}
void marge(int x,int y)
{
  x=findf(x);y=findf(y);
  if (x==y)return ;
  ans-=1ll*xc[x]*yc[x]+1ll*xc[y]*yc[y];
  if (xc[x]+yc[x]>xc[y]+yc[y])swap(x,y);
  stk[++top]=(Data){x,y};
  f[x]=y;
  xc[y]+=xc[x];
  yc[y]+=yc[x];
  ans+=1ll*xc[y]*yc[y];
}
void undo(int x,int y)
{
  ans-=1ll*xc[y]*yc[y];
  f[x]=x;
  xc[y]-=xc[x];
  yc[y]-=yc[x];
  ans+=1ll*xc[x]*yc[x]+1ll*xc[y]*yc[y];
}
int wfl,wfr;
void addop(int l,int r,int num)
{
  if (wfl<=l&&r<=wfr){
  	g[num].push_back(wfc);
    return ;
  }int mid=(l+r)>>1;
  if (wfl<=mid)addop(l,mid,num<<1);
  if (wfr>mid)addop(mid+1,r,num<<1|1);
}
long long sav[MaxN];
void solve(int l,int r,int num)
{
  int tim=top;
  for (int i=0;i<g[num].size();i++)
    marge(g[num][i].x,g[num][i].y);
  if (l==r)sav[l]=ans;
  else {
    int mid=(l+r)>>1;
    solve(l,mid,num<<1);
    solve(mid+1,r,num<<1|1);
  }
  while(tim<top){
    undo(stk[top].x,stk[top].y);
    top--;
  }
}
pair<int,int> gg;
int main()
{
  m=read();n=300005;
  for (int i=1,x,y;i<=m;i++){
  	x=read();y=read()+n;
  	gg=make_pair(x,y);
  	if (mmp.find(gg)!=mmp.end()){
  	  b[mmp[gg]].r=i-1;
  	  mmp.erase(gg);
    }else 
      b[mmp[gg]=++tn]=(Point){i,0,x,y};
  }
  for (int i=1;i<=tn;i++){
  	wfl=b[i].l;wfr=b[i].r;
  	if (wfr==0)wfr=m;
  	wfc=(xyPoint){b[i].x,b[i].y};
  	addop(1,m,1);
  }
  for (int i=1;i<=n+n;i++){
  	f[i]=i;xc[i]=(i<=n);yc[i]=!xc[i];
  }solve(1,m,1);
  for (int i=1;i<=n+n;i++)
  	if (f[i]!=i||xc[i]!=(i<=n)||yc[i]!=!xc[i])
      {puts("!");break;}
  if (ans!=0)puts("!");
  for (int i=1;i<=m;i++)
    printf("%lld ",sav[i]);
  return 0;
}
```
这种写法的时间复杂度是$O(nlog^2n)$,空间复杂度是$O(nlogn)$。

其实空间复杂度是可以做到$O(n)$的，做法如下：

但是比上面的代码时空双劣，不知为啥……

```cpp
#include<algorithm>
#include<vector>
#include<cstdio>
#include<map>
#define MaxN 600500
using namespace std;
inline int read()
{
  register int X=0;
  register char ch=0;
  while(ch<48||ch>57)ch=getchar();
  while(ch>=48&&ch<=57)X=X*10+(ch^48),ch=getchar();
  return X;
}
int n,m;
struct Point
{int l,r,x,y;}
b[MaxN];
int tn;
map<pair<int,int>,int> mmp;
int f[MaxN],xc[MaxN],yc[MaxN];
struct Data
{int x,y;}
stk[MaxN];
int top;
long long ans;
int findf(int x)
{return f[x]==x ? x :findf(f[x]);}
void marge(int x,int y)
{
  x=findf(x);y=findf(y);
  if (x==y)return ;
  ans-=1ll*xc[x]*yc[x]+1ll*xc[y]*yc[y];
  if (xc[x]+yc[x]>xc[y]+yc[y])swap(x,y);
  stk[++top]=(Data){x,y};
  f[x]=y;
  xc[y]+=xc[x];
  yc[y]+=yc[x];
  ans+=1ll*xc[y]*yc[y];
}
void undo(int x,int y)
{
  f[x]=x;
  xc[y]-=xc[x];
  yc[y]-=yc[x];
}
vector<int> s[MaxN<<1];
void solve(int l,int r,int num)
{
  long long sav=ans;
  int tim=top;
  Point *v;
  for (int i=0;i<s[num].size();i++){
  	v=&b[s[num][i]];
  	if (v->l<=l&&r<=v->r)
      marge(v->x,v->y);
  }
  if (l==r)printf("%lld ",ans);
  else {
    int mid=(l+r)>>1;
    for (int i=0;i<s[num].size();i++){
  	  v=&b[s[num][i]];
  	  if (!(v->l<=l&&r<=v->r)){
  	  	if (v->l<=mid)s[num<<1].push_back(s[num][i]);
        if (v->r>mid)s[num<<1|1].push_back(s[num][i]);
      }
    }s[num].clear();
    solve(l,mid,num<<1);
    solve(mid+1,r,num<<1|1);
  }
  while(tim<top){
    undo(stk[top].x,stk[top].y);
    top--;
  }ans=sav;
}
int main()
{
  m=read();n=300005;
  pair<int,int> sav;
  for (int i=1,x,y;i<=m;i++){
  	x=read();y=read()+n;
  	sav=make_pair(x,y);
  	if (mmp[sav]){
  	  b[mmp[sav]].r=i-1;
  	  mmp[sav]=0;
    }else 
      b[mmp[sav]=++tn]=(Point){i,0,x,y};
  }
  for (int i=1;i<=tn;i++){
  	if (b[i].r==0)b[i].r=m;
  	s[1].push_back(i);
  }
  for (int i=1;i<=n+n;i++){
  	f[i]=i;xc[i]=(i<=n);yc[i]=!xc[i];
  }solve(1,m,1);
  return 0;
}
```

---

## 作者：xtx1092515503 (赞：16)

~~在冬令营没听懂的我又跑来水题解了~~

由于之前见过[某道类似的题](https://www.luogu.com.cn/problem/AT2167)，并且这个转移操作也很相似，我们可以很自然的想到，对于原图的行和列分别建点，并将原图中的一个点看作是连接行和列的一条无向边。显然，无论何时，这都会是一张二分图。

我们发现，这样连边后，题面中的那个操作的要求就是：

对于一条边$(x_1,y_1)$，

所有与$x_1$相连的点，

与所有同$y_1$相连的点，

之间两两连边。

这样一直连下去后，我们会发现，每个原图中的连通块中，所有的行点与所有的列点之间各有一条边。

也就是说，我们要关于每个连通块，维护这个连通块里面行点数量和列点数量，然后答案就是所有连通块的（行点数量与列点数量之积）的和。

观察到操作可以离线。那么我们就进行线段树分治即可。行列点的数量都可以在可撤销冰茶姬里面维护。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mpp make_pair
#define pii pair<int,int>
#define mid ((l+r)>>1)
#define lson x<<1
#define rson x<<1|1
typedef long long ll;
const int N=3e5;
int n;
ll res;
map<pii,int>mp;
vector<pii>v[1200100];
void modify(int x,int l,int r,int L,int R,pii p){
	if(l>R||r<L)return;
	if(L<=l&&r<=R){v[x].push_back(p);return;}
	modify(lson,l,mid,L,R,p),modify(rson,mid+1,r,L,R,p);
}
struct DSU{
	int fa;
	pii sz;
	DSU(int a=0,pii b=mpp(0,0)){fa=a,sz=b;}
}dsu[600100];
int find(int x){
	return dsu[x].fa==x?x:find(dsu[x].fa);
}
struct Query{
	int u,v;
	ll r;
	pii su,sv;
	Query(int a=0,pii b=mpp(0,0),int c=0,pii d=mpp(0,0),ll e=0){u=a,su=b,v=c,sv=d,r=e;}
};
stack<Query>s;
bool merge(int x,int y){
//	printf("%d %d\n",x,y);
	x=find(x),y=find(y);
	if(x==y)return false;
	s.push(Query(x,dsu[x].sz,y,dsu[y].sz,res));
	res-=1ll*dsu[x].sz.first*dsu[x].sz.second+1ll*dsu[y].sz.first*dsu[y].sz.second;
	if(dsu[x].sz.first+dsu[x].sz.second>dsu[y].sz.first+dsu[y].sz.second){
		dsu[x].sz.first+=dsu[y].sz.first;
		dsu[x].sz.second+=dsu[y].sz.second;
		dsu[y].fa=x;
		res+=1ll*dsu[x].sz.first*dsu[x].sz.second;
	}else{
		dsu[y].sz.first+=dsu[x].sz.first;
		dsu[y].sz.second+=dsu[x].sz.second;
		dsu[x].fa=y;
		res+=1ll*dsu[y].sz.first*dsu[y].sz.second;
	}
	return true;
}
void Pop(){
	dsu[s.top().u]=DSU(s.top().u,s.top().su);
	dsu[s.top().v]=DSU(s.top().v,s.top().sv);
	res=s.top().r;
	s.pop();
}
void iterate(int x,int l,int r){
	int tot=0;
	for(int i=0;i<v[x].size();i++)tot+=merge(v[x][i].first,v[x][i].second+N);
	if(l==r)printf("%lld ",res);
	else iterate(lson,l,mid),iterate(rson,mid+1,r);
	while(tot--)Pop();
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=N;i++)dsu[i]=DSU(i,mpp(1,0));
	for(int i=N+1;i<=2*N;i++)dsu[i]=DSU(i,mpp(0,1));
	for(int i=1,x,y;i<=n;i++){
		scanf("%d%d",&x,&y);
		if(mp.find(mpp(x,y))==mp.end())mp[mpp(x,y)]=i;
		else modify(1,1,n,mp[mpp(x,y)],i-1,mpp(x,y)),mp.erase(mpp(x,y));
	}
	for(auto it:mp)modify(1,1,n,it.second,n,it.first);
	iterate(1,1,n);
	return 0;
}
```


---

## 作者：Leap_Frog (赞：7)

### P.S.
线段树分治入门题，还算比较基础吧。  
~~来补昨天题的题解了（（（~~

### Problem.
如果有 $(a,x),(a,y),(b,x)$ 那就可以加入 $(b,y)$。  
每次加入一个点或删除一个点。  
求如果当前所有点做上面的操作后，总共会有多少点。  
询问独立。  

### Solution.
首先，如果我们考虑在平面上做题，这题会变得十分困难。  
那么我们考虑经典套路转化：存在 $(x,y)\rightarrow$ $x$ 和 $y$ 之间有连边。  
我们就成功把平面问题转化成了二分图上问题。  

我们考虑一个那个加入点操作意为着什么。  
首先，如果存在一个极大联通二分图，那么它肯定连到最后会变成完全二分图。  
证明如下（可能不是很严谨：  
首先，上面的转化相当于是把两点之间长度为 $3$ 增广路连起来。  
而对于一个长度为 $5$ 的增广路，我们可以把前三条连起来，再处理后三条。  
于是我们就可以类似把任意的一条增广路首尾相接。  
所以最后连成的图就是张完全二分图。  
而完全二分图的边数是 $num_{left}\times num_{right}$。  
所以我们直接 **加边！加边！加边！然后~~可撤销~~并查集维护** 就好了。  

而这种一个点出现时间是个时间轴，我们很显然能想到用线段树分治。  
注意这个并查集需要维护两个 $siz$，分别是左右两部的大小。  
具体还可以参考代码注释。  

### Coding.
```cpp
//愿你和你重要的人能够再次重逢！
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
int n,fa[600005],sz1[600005],sz2[600005],ds[600005];
struct node{int x,y,s1,s2,ds;ll rs;}st[600005];int tp;ll res=0;
map<pair<int,int>,int>mp;vector<pair<int,int> >T[1200005];
inline int getf(int x) {return fa[x]==x?x:getf(fa[x]);}//不路径压缩的并查集
inline void mrg(int x,int y)
{//合并，有两个siz，需要可撤销
	x=getf(x),y=getf(y);if(x==y) return;else if(ds[x]>ds[y]) swap(x,y);
	st[++tp]=(node){x,y,sz1[y],sz2[y],ds[y],res},res-=1ll*sz1[x]*sz2[x]+1ll*sz1[y]*sz2[y];
	ds[y]+=ds[x]==ds[y],fa[x]=y,sz1[y]+=sz1[x],sz2[y]+=sz2[x],res+=1ll*sz1[y]*sz2[y];
}
inline void pop() {int x=st[tp].x,y=st[tp].y;fa[x]=x,ds[y]=st[tp].ds,sz1[y]=st[tp].s1,sz2[y]=st[tp].s2,res=st[tp].rs,tp--;}
inline void back(int x) {while(tp>x) pop();}//（批量）撤销操作
inline void modif(int x,int l,int r,int dl,int dr,pair<int,int>dc)
{//线段树合并中的修改
	if(l>dr||dl>r) return;else if(dl<=l&&r<=dr) return T[x].push_back(dc);
	modif(x<<1,l,(l+r)>>1,dl,dr,dc),modif(x<<1|1,((l+r)>>1)+1,r,dl,dr,dc);
}
inline void solve(int x,int l,int r)
{//线段树合并中遍历时间轴
	int wh=tp;for(int i=0;i<(int)T[x].size();i++) {int a=T[x][i].first,b=T[x][i].second;mrg(a,b);}
	if(l==r) return printf("%lld ",res),back(wh);else solve(x<<1,l,(l+r)>>1),solve(x<<1|1,((l+r)>>1)+1,r);
	back(wh);//线段树合并需要撤销
}
int main()
{
	read(n);for(int i=1,x,y;i<=n;i++)
	{//读入
		read(x),read(y);pair<int,int>p=make_pair(x,y+300000);
		if(mp[p]) modif(1,1,n,mp[p],i-1,p),mp.erase(p);else mp[p]=i;
	}
	for(int i=1;i<=600000;i++) fa[i]=i,(i<=300000?sz1[i]:sz2[i])=1;//初始化
	for(auto i:mp) modif(1,1,n,i.second,n,i.first);//剩余修改
	return solve(1,1,n),putchar('\n'),0;//完结撒花，求赞
}
```

---

## 作者：Schwarzkopf_Henkal (赞：7)

是看了线段树分治模板题题解里面的推荐例题来的。但是在开始做这道题之前，我突然觉得，题目的“内涵”也许比这些算法要重要一些。

我先去做了 [AT2167](https://www.luogu.com.cn/problem/AT2167)，发现这种绕着把边说成点已经是一种套路了，尤其这题还直白得多。

这题贴心地帮我们把点分成了 $x$ 和 $y$ 两个集合，于是我们猜想并且根据后面给的拓展边的条件，我们发现这的确是个二分图。或者说，不管什么图，拆点之后就是个二分图。 ~~说了跟没说一样~~

我们观察拓展的条件，发现：

![](https://cdn-warfare-1302619124.file.myqcloud.com/rgngtuk7.png)

对于一个在右边集合的节点，如果有两个节点都引了一条边到这个节点，那么我们有，任意一个其中一个节点有边到达的节点，另外一个节点都会引一条边到那个节点。非常类似于，缩点（跟WC2021 T1 也很像）。

也就是说，我们不断拓展，最后得到的结果将会是几个相互独立的连通块。并且对于一个连通块中任意一个左边集合的点到右边集合所有的点都有一条边。这样的一个集合的贡献将会是 $l\times r$，分别对应左集合大小和右集合大小。

并且，我们可以用并查集维护这样的集合！我们需要维护一个连通块内左集合的大小和右集合的大小。

我们把每条边的的操作变成一堆影响区间，这是线段树分治基操，随后考虑加入边的影响。

如果对应的右集合的点还没有一条连向它的边，那么这并不需要合并集合，右集合大小++即可。

如果已经有了，那么需要合并集合，$ans=ans+(l_u+l_v)\times(r_u+r_v)-l_u\times r_u-l_v\times r_v$。

整好了！

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,map<int,int> >mp;
int n;
struct Seg{
    int l,r;
    vector<pair<int,int> >v;
    #define l(o) C[o].l
    #define r(o) C[o].r
    #define mid(o) ((C[o].l+C[o].r)/2)
    #define v(o) C[o].v
}C[1200005];
void build(int o,int l,int r){
    l(o)=l;
    r(o)=r;
    if(l>=r)
        return;
    build(o*2,l,mid(o));
    build(o*2+1,mid(o)+1,r);
}
void update(int o,int l,int r,pair<int,int> v){
    if(l(o)>=l&&r(o)<=r){
        v(o).push_back(v);
        return;
    }
    if(l<=mid(o))
        update(o*2,l,r,v);
    if(r>mid(o))
        update(o*2+1,l,r,v);
}
struct State{
    long long typ,u,v,s,t;
};
stack<State>sta;
int mk[300005],f[300005];
long long s[300005],t[300005];
int find(int p){
    return f[p]==p?p:find(f[p]);
}
long long res,ans[300005];
void Resolve(int o){
    int siz=sta.size();
    long long _rev=res;
    for(int i=0,u,v;i<v(o).size();i++){
        u=v(o)[i].first;
        v=v(o)[i].second;
        if(mk[v]==0){
            mk[v]=u;
            u=find(u);
            t[u]++;
            res+=s[u];
            sta.push({0,u,v,0,1});
        }else if(find(mk[v])!=find(u)){
            u=find(u);
            v=find(mk[v]);
            if(s[u]>s[v])
                swap(u,v);
            res+=(s[u]+s[v])*(t[u]+t[v])-s[u]*t[u]-s[v]*t[v];
            sta.push({1,u,v,s[u],t[u]});
            s[v]+=s[u];
            t[v]+=t[u];
            f[u]=v;
        }
    }
    if(l(o)>=r(o)){
        ans[l(o)]=res;
        goto Karkov;
    }
    Resolve(o*2);
    Resolve(o*2+1);
    Karkov:;
    while(sta.size()>siz){
        //Distribute
        State u=sta.top();
        if(u.typ==0){
            t[u.u]-=u.t;
            mk[u.v]=0;
        }
        if(u.typ==1){
            s[u.v]-=u.s;
            t[u.v]-=u.t;
            f[u.u]=u.u;
        }
        sta.pop();
    }
    res=_rev;
}
int main(){
    scanf("%d",&n);
    build(1,1,n);
    for(int i=1,u,v;i<=n;i++){
        scanf("%d%d",&u,&v);
        if(mp[u][v]==0)
            mp[u][v]=i;
        else {
            // cout<<"("<<u<<","<<v<<")"<<mp[u][v]<<"-"<<i-1<<'\n';
            update(1,mp[u][v],i-1,make_pair(u,v));
            mp[u][v]=0;
        }
    }
    for(auto s:mp)
        for(auto t:s.second)
            if(t.second){
                // cout<<"("<<s.first<<","<<t.first<<")"<<t.second<<"-"<<n<<'\n';
                update(1,t.second,n,make_pair(s.first,t.first));
            }
    for(int i=1;i<=n;i++){
        f[i]=i;
        s[i]=1;
    }
    Resolve(1);
    for(int i=1;i<=n;i++)
        printf("%lld ",ans[i]);
}/*
首先这是一个二分图
随后如果我们有u->v<-w，那么w连什么，u也连什么。等于说是缩点。
贡献是这个连通块左边的siz*右边的siz。
并且，显然整个连通块是独立的，不存在相连，但是不被缩到一个点里面去的情况
所以整好了！！！！！！！！！！！！！！！！！！！
*/
```



---

## 作者：Llx2022 (赞：4)

# 题意

有 $n$ 次操作，每次给定一个元素 $(a,b)$，若集合 $S$ 中包含该元素则删除，不包含则添加，求每次操作之后扩展集合的大小，**注意这里的扩展集合中的元素并非是实际添加到 $S$ 中，扩展集合的元素的存在性，是当且仅当该次操作存在，对后续操作无影响**。

定义一个点集合 $S=\{(x_i,y_i)\}(1\leq i\leq n)$ 的**拓展操作**为将符合以下条件的 $(x_0,y_0)$ 加入 $S$：

- 存在 $a,b$，使得 $(a,b),(a,y_0),(x_0,b)\in S$。



# 思路
我们通过手动模拟样例可以发现其实就是把每个二元组放到二维平面中，对于每个点横纵坐标划一道直线，所有原集合元素的交点就是新扩展出来的元素，那么我们显然就可以发现就是横纵坐标所在联通块的乘积就是答案。



**如图所示**，会更加清晰，红线所在的交点就是对答案的贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/arjxx31p.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/flpkc0q4.png)
这样我们还是考虑线段树分治，以时间轴建线段树，依次处理每次答案，每次从根结点递归时记得撤销原操作。并查集的话我们可以考虑横坐标建立 $[1,x_{max}]$ 范围的并查集，纵坐标建立 $(x_{max},x_{max}+y_{max}]$ 范围的并查集，这样在合并答案的时候可以方便操作。
# 代码实现

```cpp
#include<iostream>
using namespace std;
const int N=3e5+9;
int fa[N*2];
int sz1[N*2],sz2[N*2];
int height[N*2];
int n;
#include<vector>
#include<utility>
#include<map>
vector<pair<int,int> >t[N*4*2];
map<pair<int,int>,int> mp;
int find(int x){
	while(x!=fa[x]) x=fa[x];
	return fa[x];
}
int top;
long long ans;
struct stack{
	int x,y,sz1,sz2,add;
	long long ans;
}st[N*2];
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(height[fx]>height[fy]) swap(fx,fy);
	st[++top]={fx,fy,sz1[fy],sz2[fy],height[fx]==height[fy],ans};
	ans-=1ll*sz1[fx]*sz2[fx]+1ll*sz1[fy]*sz2[fy];
	sz1[fy]+=sz1[fx];
	sz2[fy]+=sz2[fx];
	fa[fx]=fy;
	if(height[fx]==height[fy]) height[fy]++;
	ans+=1ll*sz1[fy]*sz2[fy];
}
void update(int u,int l,int r,int ql,int qr,const pair<int,int> x){
	if(ql>r||qr<l) return ;
	if(ql<=l&&r<=qr){t[u].push_back(x);return;}
	int mid=l+r>>1;
	if(l<=mid) update(u<<1,l,mid,ql,qr,x);
	if(r>mid) update(u<<1|1,mid+1,r,ql,qr,x);
}
void solve(int u,int l,int r){
	int lasttop=top;
	int sz=t[u].size();
	for(int i=0;i<sz;i++){
		int a=find(t[u][i].first);
		int b=find(t[u][i].second);
		if(a!=b) merge(t[u][i].first,t[u][i].second);
	}
	if(l==r) printf("%lld ",ans);
	else{
		int mid=l+r>>1;
		solve(u<<1,l,mid);
		solve(u<<1|1,mid+1,r);
	}
	while(top>lasttop){
		height[fa[st[top].x]]-=st[top].add;
		sz1[st[top].y]=st[top].sz1;
		sz2[st[top].y]=st[top].sz2;
		fa[st[top].x]=st[top].x;
		ans=st[top].ans;
		top--;
	}
	return ;
}
int main(){
	scanf("%d",&n);
	int x,y;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		y+=3e5;
		if(mp[{x,y}]){
			update(1,1,n,mp[{x,y}],i-1,{x,y});
			mp.erase({x,y});
		}
		else mp[{x,y}]=i;
	}
	for(int i=1;i<=3e5;i++){
		fa[i]=i;
		height[i]=1;
		sz1[i]=1;
	}
	for(int i=3e5+1;i<=6e5;i++){
		fa[i]=i;
		height[i]=1;
		sz2[i]=1;
	}
	for(map<pair<int,int>,int>::iterator i=mp.begin();i!=mp.end();i++){
		update(1,1,n,(*i).second,n,(*i).first);
	}
	solve(1,1,n);
	return 0;
}
```


---

## 作者：Umbrella_Leaf (赞：4)

### 简要题面

二维平面上有若干个点，定义一个点集 $S$ 的**张集**为满足以下条件的最小集合 $T$ ：

- 对任意 $(x,y)\in S$ ， $(x,y)\in T$ ；
- 对任意 $(x_0,y_0)\in T,$ 若存在 $(x_0,y_1)\in T$ 且 $(x_1,y_0)\in T$ ，则 $(x_1,y_1)\in T$ 。
现在有 $n$ 个操作，每次插入或删除一个点，求每次操作后当前点集的张集大小。

### 分析

考虑如何求出一个点集的张集大小。

我们~~按照套路~~，把一个点 $(x,y)$ 看成在一个图中，从 $1$ 类点 $x$ 连向 $2$ 类点 $y$ 。显然在任意时刻，这个图都是个**二分图**。

这时候如果左边 $x$ 与右边 $y$ 联通，那么 $T$ 中一定存在 $(x,y)$ 这个点。

一共有多少个点呢？设一个连通块左边有 $s_1$ 个点，右边有 $s_2$ 个点，那么一共有 $\sum s1\times s2$ 。

也就是把问题转化成：一张二分图，支持插入删除边以及维护这个和。

我们把每条边弄出来一个存在区间，然后做线段树分治。

也就是，我们用类似线段树的遍历方式维护一个按秩合并并查集，用并查集维护每个连通块的 $s_1,s_2$ 。

而这个并查集需要支持可撤销（遍历线段树时需要回溯），因此用栈存下每次合并操作之前被合并点的状态。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
map<pair<int,int>,int> mp;
vector<pair<int,int> >v[1200005];
int n;
int fa[600005],siz1[600005],siz2[600005],dis[600005];
ll now;
struct node{
	int x,y,s1,s2,ds;ll now;
};
stack<node> st;
int get(int x){
	if(x==fa[x])return x;
	else return get(fa[x]);
}
void add(int x,int y){
	x=get(x),y=get(y);
	if(x==y)return;
	if(dis[x]>dis[y])swap(x,y);
	fa[x]=y;
	st.push({x,y,siz1[y],siz2[y],dis[y],now});
	now-=(long long)siz1[x]*siz2[x]+(long long)siz1[y]*siz2[y];
	siz1[y]+=siz1[x],siz2[y]+=siz2[x];
	if(dis[y]==dis[x])dis[y]++;
	now+=(long long)siz1[y]*siz2[y];
}
void pop(){
	int x=st.top().x,y=st.top().y;
	siz1[y]=st.top().s1,siz2[y]=st.top().s2,dis[y]=st.top().ds;
	fa[x]=x;
	now=st.top().now;
	st.pop();
}
void insert(int k,int l,int r,int x,int y,pair<int,int> z){
	if(l>=x&&r<=y){
		v[k].push_back(z);
		return;
	}
	int mid=l+r>>1;
	if(mid>=x)insert(k*2,l,mid,x,y,z);
	if(mid<y)insert(k*2+1,mid+1,r,x,y,z);
}
void solve(int k,int l,int r){
	int ht=st.size();
	for(int i=0;i<v[k].size();i++)add(v[k][i].first,v[k][i].second);
	if(l==r){
		printf("%lld ",now);
		while(st.size()>ht)pop();
		return;
	}
	int mid=l+r>>1;
	solve(k*2,l,mid);
	solve(k*2+1,mid+1,r);
	while(st.size()>ht)pop();
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		y+=300000;
		if(mp[make_pair(x,y)]){
			insert(1,1,n,mp[make_pair(x,y)],i-1,make_pair(x,y));
			mp.erase(make_pair(x,y));
		}
		else mp[make_pair(x,y)]=i;
	}
	for(int i=1;i<=300000;i++)fa[i]=i,siz1[i]=1;
	for(int i=300001;i<=600000;i++)fa[i]=i,siz2[i]=1;
	for(map<pair<int,int>,int>::iterator i=mp.begin();i!=mp.end();i++)
		insert(1,1,n,(*i).second,n,(*i).first);
	solve(1,1,n);
	return 0;
}
```

---

## 作者：CDFLS_mao_zx (赞：1)

## 题解：$CF1140F$

### 吐槽：

为啥同机房的奆佬的题都只有$2700$，然后我$2600$。。。

万里长征刚刚开始，这是第一篇。

### 题意：

维护一个平面上点的集合，支持插入，删除，查询扩展集合的大小。

扩展集合的定义：反复进行如下操作，直到不能加入点为止。

将符合以下条件的(x2,y2)加入S（条件：存在x1,y1使得(x1,y1),(x1,y2),(x2,y1)属于S）。

### 思路：

我们先考虑给出一个点集，如何计算它拓展集合的大小。

![1.png](https://image.blackwhitetony.com/2020/12/29/67941093a2b78.png)

上面是最初的集合。

![2.png](https://image.blackwhitetony.com/2020/12/29/b4bea39f798d9.png)

红色是第一次加入的点。

绿色是第二次加入的点。

橙色是第三次加入的点。

蓝色是第四次加入的点。

我们发现其实它拓展成了一个矩形。

我们再画一些图。

![3.png](https://image.blackwhitetony.com/2020/12/29/1bb8cc026d2fa.png)

- ![4.png](https://image.blackwhitetony.com/2020/12/29/342bcf9abc6c1.png)

观察到也是拓展成一个矩阵。

而且所有的点横竖连边的话图就会联通。

也就是说，一个点会和它同横坐标竖坐标的点联通，而观察上述二例，其集合大小就是一个连通块中不同横坐标点的个数乘上不同纵坐标点的个数，于是我们用并查集维护连通块，对于横纵坐标分别维护集合大小，答案就是其乘积之和。加入一个点就相当于横坐标和纵坐标连边，然后，没了？

停停停，还有删除来着，嗯嗯并查集似乎不支持删除吧，但并查集看上去是那么的可行诶。

于是，线段树分治登场，它能将带删除操作的题目以一个$log$的代价转化为不带删除的题目。

### 线段树分治：

我们考虑一个点，它加入了又删除，很容易用$map$求出它覆盖的时间段，当然，这需要一个点删除后对答案的影响消失。

很容易想到开一颗维护时间的线段树，将一个操作覆盖的时间段上的节点打上这个操作，查询时对线段树进行$dfs$就可以在叶子节点得到答案了。

别忙，回溯怎么办，不还是要删点吗？嗯，好好想想，它只需要撤销前一个操作啊，可撤销并查集啊。

于是我们快乐地搞定了这道题。

### 代码和实现中的细节问题：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<stack>
#include<vector>
#define next nxt
#define itn int
#define y1 y3647
#define LL long long
using namespace std;
inline void read(int &x)
{
	x=0;
	int f=1;
	char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')
	ch=getchar();
	if(ch=='-')
	{
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}
const int N=3e5+10;
int i,j,k,m,n,s,t,top,tc;
map <pair<int,int>,int> mp;
map <pair<int,int>,int> ::iterator it;
vector <pair<int,int> > a[N<<2];
struct bc{
	int v,fv,u,s1u,s2u;
}sta[N<<6];
int fa[N<<1],size1[N<<1],size2[N<<1],root[N<<1];
int find(int x)
{
	if(fa[x]==x)
	return x;
	return find(fa[x]);
}
void updata(int l,int r,int rt,int x,int y,pair<int,int> op)
{
	if(x<=l&&y>=r)
	{
		a[rt].push_back(op);//vector真的很香
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid)
	updata(l,mid,rt<<1,x,y,op);
	if(y>mid)
	updata(mid+1,r,rt<<1|1,x,y,op);
}
long long put(int u,int v,long long c)
{
	u=find(u),v=find(v);
	if(u==v)
	return c;
	tc++;
	if(size1[u]+size2[u]>size1[v]+size2[v])
	swap(u,v);
	sta[++top]=(bc){u,fa[u],v,size1[v],size2[v]};//改变的有以下：u的fa，v的size1,size2。
	fa[u]=v;
	c-=(long long)size1[v]*size2[v];
	c-=(long long)size1[u]*size2[u];
	size1[v]+=size1[u];
	size2[v]+=size2[u];
	c+=(long long)size1[v]*size2[v];//第一发WA没开longlong
	return c;
}
void dfs(int l,int r,int rt,long long ans)
{
	tc=0;
	for(int i=0;i<a[rt].size();i++)
	ans=put(a[rt][i].first,a[rt][i].second,ans);
	int cc=tc;
	if(l==r)
	{
		printf("%lld ",ans);
		for(int i=0;i<cc;i++)
		{
			fa[sta[top].v]=sta[top].fv;
			size1[sta[top].u]=sta[top].s1u;
			size2[sta[top].u]=sta[top].s2u;
			top--;
		}
		return;
	}
	int mid=(l+r)/2;
	dfs(l,mid,rt<<1,ans);
	dfs(mid+1,r,rt<<1|1,ans);
	for(int i=0;i<cc;i++)
	{
		fa[sta[top].v]=sta[top].fv;
		size1[sta[top].u]=sta[top].s1u;
		size2[sta[top].u]=sta[top].s2u;
		top--;
	}
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",stdout);
	read(n);
	for(i=1;i<=n;i++)
	{
		int x,y;
		read(x),read(y);
		int tmp=mp[make_pair(x,y)];
		if(tmp)
		{
			updata(1,n,1,tmp,i-1,make_pair(x,y+3e5));//注意是i-1因为在i处已经删去了这个点
			mp.erase(make_pair(x,y));
		}
		else
		mp[make_pair(x,y)]=i;
	}
	for(it=mp.begin();it!=mp.end();it++)
	updata(1,n,1,(*it).second,n,make_pair(it->first.first,it->first.second+3e5));//在最后的时间把所有操作加入。
	for(i=1;i<=3e5;i++)
	{
		fa[i]=i;
		size1[i]=1;
	}
	for(i=3e5+1;i<=6e5;i++)
	{
		fa[i]=i;
		size2[i]=1;
	}
	dfs(1,n,1,0);
	return 0;
}
```

### 各位看官看到这里就可以了，下面是给自己看的。

某大牛代码：

```cpp
px[top]=x; py[top]=y; fa[y]=x;
sz1[x]+=sz1[y]; sz2[x]+=sz2[y];
------------------------------
int x=px[top],y=py[top];
fa[y]=y;
sz1[x]-=sz1[y];
sz2[x]-=sz2[y];
```

我自己的对应部分：

```cpp
sta[++top]=(bc){u,fa[u],v,size1[v],size2[v]};
--------------------------------------------
for(int i=0;i<cc;i++)
{
	fa[sta[top].v]=sta[top].fv;
	size1[sta[top].u]=sta[top].s1u;
	size2[sta[top].u]=sta[top].s2u;
	top--;
}
```

显然维护的信息有些冗余，这又是空间复杂度瓶颈，于是。。。

### 反思：

这种题要多画图想一想，其实最开始我就考虑了线段树分治，但是我似乎不会静态问题。

$vector$相当的好用。

可撤销并查集实现还有些不熟练。





---

## 作者：LinkyChristian (赞：1)

[前往我的博客获取更好的阅读体验](https://lookcatbox.github.io/)

线段树分治好题。

首先我们转换一下题意：将点 $(x,y)$ 看做是连接第 $x$ 行和第 $y$ 列的一条边。题目所说的拓展集合大小即为每一个连通块中行和列能形成交点数。设连通块中有 $x_n$ 个行点，$y_n$ 个列点，则该连通块对答案的贡献为 $x_n \times y_n$

考虑修改操作，一个点会在某个时候出现，某个时候消失。也就是说，每个点在时间轴上是以一些**区间**的形式存在的。我们可以尝试用一个并查集来维护连通块以及其贡献，并把修改离线到时间轴上。

但我们发现并查集并不是一种利于删除的操作，它只支持回退最新的操作。如果我们要直接离线查询，那要删除并查集里一条边的时候这条边都不知道跑到哪里去了。所以我们需要一种方法来避免删除操作，只留下添加和撤回操作。

这里我们可以使用 **线段树分治**。在时间轴上建一棵线段树，把每一个点的存在区间下放到线段树上。然后我们从区间 $[1,n]$ 开始二分，每进入一个区间时处理挂在这个区间上的修改操作。这样当我们到达$[i,i]$ 这个时间点时，所有覆盖在 $i$ 这个时间上的修改操作都已经处理完了。之后在退出一个区间的时候将修改全部撤回即可。

```cpp
// Problem: CF1140F Extending Set of Points
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1140F
// Memory Limit: 1000 MB
// Time Limit: 3500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ls k*2
#define rs k*2+1
#define mid (l+r)/2
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define int long long
#define N 600010
using namespace std;
typedef pair<int,int> pii;
int read() {
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)) f=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch)) res=res*10+ch-'0',ch=getchar();
	return f*res;
}
int n,fa[N],size[N],tp;
pii siz[N];
int find(int x) {
	while(fa[x]!=x) x=fa[x];
	return x;
}
map<pii,int> pt;
vector<pii> p[N<<2];
int res;
struct node{
	int x,y;
	pii siz;
	int size,res;
}sk[N];
void merge(int x,int y) {
	x=find(x),y=find(y);
	if(x==y) return ;
	if(size[x]>size[y]) swap(x,y);
	sk[++tp]=node{x,y,siz[y],size[y],res};
	res-=1ll*siz[x].fi*siz[x].se+1ll*siz[y].fi*siz[y].se;
	fa[x]=y,size[y]+=size[x];
	siz[y]=mp(siz[y].fi+siz[x].fi,siz[y].se+siz[x].se);
	res+=1ll*siz[y].fi*siz[y].se;
}
void modify(int k,int l,int r,int L,int R,pii val) 
{
	if(L<=l&&r<=R) {p[k].pb(val);return ;}
	if(L<=mid) modify(ls,l,mid,L,R,val);
	if(R>mid) modify(rs,mid+1,r,L,R,val);
}
void solve(int k,int l,int r) {
	int las=tp;
	for(int i=0; i<p[k].size(); i++) 
		merge(p[k][i].fi,p[k][i].se);
	if(l==r) printf("%lld ",res);
	else solve(ls,l,mid),solve(rs,mid+1,r);
	while(tp>las) {
	    int x=sk[tp].x,y=sk[tp].y;
	    fa[x]=x,size[y]=sk[tp].size;
	    siz[y]=sk[tp].siz;
	    res=sk[tp].res;
	    tp--;
	}
}
signed main()
{
	n=read();
	for(int i=1; i<=n; i++) {
		pii tmp=mp(read(),read()+300000);
		if(pt[tmp]) modify(1,1,n,pt[tmp],i-1,tmp),pt.erase(tmp);
		else pt[tmp]=i;
	}
	for(int i=1; i<=600000; i++) 
	    fa[i]=i,siz[i]=((i<=300000)?mp(1,0):mp(0,1)),size[i]=1;
	for(auto i:pt) modify(1,1,n,i.se,n,i.fi);
	solve(1,1,n);
	return 0;
}
```





---

## 作者：TernaryTree (赞：0)

线段树分治练手题。

这个点什么的看着很不爽，考虑转成边：对于行和列分别建点，然后一个点所表示的边，连接它的行点和它的列点。

注意到显然黑白染色后，行点是同一个颜色，列点是同一个颜色，所以这是一张二分图。

题目中所给的扩展一个点，实际上就是在一个二分图连通块中加边，使其仍为二分图。也就是说，我们最多扩展 $cnt_0\times cnt_1$ 个点，其中 $cnt_i$ 表示这个联通块中黑点/白点的个数。

于是在一个时刻的答案即为：$\sum cnt_0\times cnt_1$。

出现/消失的点，引导我们去往线段树分治考虑。维护一个线段树，对于每个点出现的时间段，丢到 $\log n$ 个线段树上的结点。dfs 一遍，并且用可撤销并查集维护每个连通块的信息即可。这部分和线段树分治的洛谷模板区别不大。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define fs first
#define sc second

using namespace std;

const int maxn = 1e6 + 10;
typedef pair<int, int> pii;

struct op {
	int u, h, p, q;
	op() = default;
	op(int u, int h, int p, int q): u(u), h(h), p(p), q(q) {}
};

int n, m = 415411;
map<pii, pii> lst;
pii e[maxn];
int tot;
vector<int> tr[maxn];

void insert(int u, int l, int r, int ql, int qr, int id) {
	if (ql <= l && r <= qr) {
		tr[u].push_back(id);
		return;
	}
	if (ql <= mid) insert(lc, ql, qr, id);
	if (qr > mid) insert(rc, ql, qr, id);
}

int ans;
int fa[maxn];
int h[maxn];
int p[maxn], q[maxn];
int res[maxn];
op st[maxn];
int top;

int find(int x) {
	return x == fa[x] ? x : find(fa[x]);
}

void merge(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return;
	if (h[u] < h[v]) swap(u, v);
	fa[v] = u;
	st[++top] = op(v, h[u] == h[v], p[v], q[v]);
	ans -= p[u] * q[u] + p[v] * q[v];
	p[u] += p[v];
	q[u] += q[v];
	ans += p[u] * q[u];
	h[u] += h[u] == h[v];
}

void dfs(int u, int l, int r) {
	int lst = top;
	for (int i : tr[u]) merge(e[i].fs, e[i].sc);
	if (l == r) res[l] = ans;
	else dfs(lc), dfs(rc);
	while (top > lst) {
		h[fa[st[top].u]] -= st[top].h;
		ans -= p[fa[st[top].u]] * q[fa[st[top].u]];
		p[fa[st[top].u]] -= st[top].p;
		q[fa[st[top].u]] -= st[top].q;
		ans += p[fa[st[top].u]] * q[fa[st[top].u]] + p[st[top].u] * q[st[top].u];
		fa[st[top].u] = st[top].u;
		top--;
	}
}

signed main() {
	cin >> n;
	for (int i = 1, x, y; i <= n; i++) {
		cin >> x >> y;
		if (lst.count({x, y})) {
			insert(1, 1, n, lst[{x, y}].fs, i - 1, lst[{x, y}].sc); 
			lst.erase(lst.find({x, y}));
		} else {
			lst[{x, y}] = {i, ++tot};
			e[tot] = {x, y + m};
		}
	}
	for (auto i : lst) insert(1, 1, n, i.sc.fs, n, i.sc.sc); 
	for (int i = 1; i < maxn; i++) fa[i] = i, h[i] = 1;
	for (int i = 1; i <= m; i++) p[i] = 1;
	for (int i = m + 1; i < maxn; i++) q[i] = 1;
	dfs(1, 1, n);
	for (int i = 1; i <= n; i++) cout << res[i] << " ";
	return 0;
}

```

---

## 作者：Arghariza (赞：0)

### Description

定义一个点集合 $S=\{(x_i,y_i)\}(1\leq i\leq n)$ 的拓展操作为将符合以下条件的 $(x_0,y_0)$ 加入 $S$：

- 存在 $a,b$，使得 $(a,b),(a,y_0),(x_0,b)\in S$。

不断执行以上操作直到不能操作，此时得到的集合即为拓展集合。现在给定 $q$ 个操作，每次加入或删除一个点，输出每个操作之后的拓展集合大小。

- $q,x_i,y_i\le 3\times10^5$。

### Solution

条件为存在 $a,b$，使得 $(a,b),(a,y_0),(x_0,b)\in S$，那么可以转化成图论问题。考虑建二分图，左部为行，右部为列。每个点 $(x,y)$ 即将 $l_x$ 和 $r_y$ 连边（$l_i$ 表示左部第 $x$ 个点，$r_i$ 同理）。找规律后不难发现这个二分图补全后，每个连通块各会变成一个**完全二分图**。

这个完全二分图的边数就是左部的大小乘上右部的大小。

只有加边操作时，我们可以使用并查集维护这个二分图，并时刻求出答案。

考虑删边，发现每条边都有出现区间，这些区间数是 $O(q)$ 的，并且上面只有加边的弱化版可以使用并查集解决，这启发我们使用线段树分治。把并查集替换成可撤销并查集即可。

复杂度 $O(q\log q\log w)$，$w$ 为 $x_i,y_i$ 值域，题目中与 $q$ 同阶。

[评测记录。](https://codeforces.com/contest/1140/submission/180703650)

---

