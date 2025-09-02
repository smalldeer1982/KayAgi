# Forced Online Queries Problem

## 题目描述

给你一个有$n$个点的无向图,点的编号从$1$到$n$,最初图中没有边

给定两种操作:

- $1\ x\ y(1\le n,x\neq y)$如果在点$(x+lstans-1)mod\ n+1$与边$(y+lstans-1)mod\ n+1$之间有边,则删,无边则加

- $2\ x\ y(1\le x,y \le n,x\neq y)$检查点$(x+lstans-1)mod\ n+1$与点$(y+lstans-1)mod\ n+1$之间的连通性,联通则输出1,否则输出0

(这里定义$lastans$为上一次操作$2$的结果,特别的,在第一次操作$2$之前,$lastans=0$)

## 说明/提示

对于样例$1$,输入所代表的实际询问如下:

- 1 1 2
- 1 1 3
- 2 3 2
- 1 3 5
- 2 4 5
- 1 2 4
- 2 3 4
- 1 2 4
- 2 5 4

对于样例$2$,输入所代表的实际询问如下:

- 1 1 2
- 1 2 3
- 1 3 1
- 2 1 3
- 1 1 3
- 2 3 1
- 1 2 3
- 2 2 3
- 2 1 2

## 样例 #1

### 输入

```
5 9
1 1 2
1 1 3
2 3 2
1 2 4
2 3 4
1 2 4
2 3 4
1 1 3
2 4 3
```

### 输出

```
1010
```

## 样例 #2

### 输入

```
3 9
1 1 2
1 2 3
1 3 1
2 1 3
1 3 2
2 2 3
1 1 2
2 1 2
2 1 2
```

### 输出

```
1101
```

# 题解

## 作者：cccgift (赞：5)

## 好一个Forced Online Queries Problem……

第一眼看过去$LCT$模板题，但是本题维护的是动态图而不是动态树。

动态图怎么维护连通性呢？我能想到的只有线段树分治了……（事实上是因为最近刚学线段树分治）

这里具体讲一下线段树分治的过程。

我们暂时不考虑强制在线（因为线段树分治是离线的）。

首先考虑维护连通性，直接用并查集维护就好了。

但是，并查集只能够加入边，不能删除边，而本题有删除操作……

那么，我们能不能考虑$[1,m]$每个时间，考虑当前每一条边存在的时间段（显然这些时间段构成了一个个区间，区间个数不超过$m$），只在这些时间段把边加入即可。

说得好听，实现复杂度和时间复杂度都很高……

考虑如何优化，我们能不能快速加入边呢？

既然是不超过$m$个区间，我们可以用线段树加入区间！

具体实现就和区间修改差不多，开一个邻接表记录线段树节点上的加边情况。

接下来就是询问了，我们也可以用线段树查询的方式递归到单位区间节点，直接统计答案就好了。

现在问题关键：怎么确保递归到单位区间节点时，所有存在于当前时间点的边都被加入到并查集中了呢？

考虑当前递归到$(q,l,r)$，我们先把$q$邻接表内的边加入，因为到$(q*2,l,mid)$和$(q*2+1,mid+1,r)$时这些边也肯定存在。当然题目中是把边存在的状态取反，所以我们再开一个$vis$数组，记录当前每一条边是否已经存在，每次加边时看$vis$数组的值，同时取反，表明状态。

先递归$(q*2,l,mid)$，然后递归$(q*2+1,mid+1,r)$，但是$(q*2,l,mid)$中存在的边不一定存在于$(q*2+1,mid+1,r)$，我们需要**删除**这些边，但这里有一个特殊的性质：我们要删的边都是新加入的。也就是说，只要维护一个带撤销并查集即可，这是可以做到的。

那么，问题就这样结束了……吗？

别忘了强制在线！

难道前面的思路都没用了吗？

题目中有个很坑的点：$last$只可能为$0$或$1$！

于是，对于每一次操作只有两种情况：$(x,y)$和$((x-1) \mod n+1,(y-1) \mod n+1)$。

那么，我们可以把这两种情况都维护一遍，至于最后答案是哪种情况，由于我们线段树查询时获取答案是从$1$到$m$的，对于每一个$l$，只要考虑$l-1$的答案即可。

时间复杂度$O(m(logn+logm))$，其中$logn$表示按秩合并的复杂度（不能路径压缩，不然撤销的信息就会被破坏，导致答案错误）。

### 代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<utility>
#include<algorithm>
#include<cmath>
using namespace std;
#define res register int
#define ll long long
//#define cccgift
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
namespace wode{
    template<typename T>
    inline void read(T &x)
    {
        static char ch;bool f=1;
        for(x=0,ch=getchar();!isdigit(ch);ch=getchar()) if(ch=='-') f=0;
        for(;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=getchar());x=f?x:-x;
    }
    template<typename T>
    void print(T x)
    {
        if (x<0) putchar('-'),x=-x;
        if (x>=10) print(x/10);
        putchar(x%10+'0');
    }
    template<typename T>
    inline void print(T x,char ap) {print(x);if (ap) putchar(ap);}
    template<typename T>
    inline T max(const T &x,const T &y) {return x<y?y:x;}
    template<typename T>
    inline T min(const T &x,const T &y) {return x<y?x:y;}
    template<typename T>
    inline void chkmax(T &x,const T &y) {x=x<y?y:x;}
    template<typename T>
    inline void chkmin(T &x,const T &y) {x=x<y?x:y;}
}
using wode::read;using wode::chkmin;using wode::chkmax;using wode::print;
#define stack qscweadzx
struct edge{
	int x,y;
	edge() {}
	edge(int x,int y):x(x),y(y) {}
} ed[800001];
struct que{
	int x,y;
	que() {}
	que(int x,int y):x(x),y(y) {}
} Q[200001];
struct node{
	int x,y,q,id;
	node() {}
	node(int x,int y,int q,int id):x(x),y(y),q(q),id(id) {}
	bool operator <(const node &b)const {
		if(x!=b.x) return x<b.x;
		if(y!=b.y) return y<b.y;
		return id<b.id;
	}
	bool operator !=(const node &b)const {return x!=b.x||y!=b.y;}
} a[400001];
int n,m,x,y,id,len1,mp[200001][2],ver[5000001],nxt[5000001],head[800001],ans,fa[200001],len[200001],stack[400001],stack1[400001],stack2[400001],top,tot[200001];
bool vis[400001];
inline void add(int x,int y) {ver[++ans]=y,nxt[ans]=head[x],head[x]=ans;}
int find(int x) {return fa[x]==x?x:find(fa[x]);} //注意不能写成fa[x]=find(fa[x])
inline void hebing(int x,int y) {
	x=find(x),y=find(y);if(len[x]<len[y]) x^=y^=x^=y;
	if(x!=y) {
		stack[++top]=x,stack1[top]=fa[x],stack2[top]=len[x];
		stack[++top]=y,stack1[top]=fa[y],stack2[top]=len[y];
		fa[y]=x,len[x]+=len[y];
	} //用栈维护可撤销并查集的信息，要撤销时只要把栈顶信息重置即可。
}
#define chexiao fa[stack[top]]=stack1[top],len[stack[top]]=stack2[top],--top
void change(int q,int l1,int r1,int l,int r,int k) { //区间加边
	if(l<=l1&&r1<=r) return (void)(add(q,k));
	int mid=l1+r1>>1;
	if(l<=mid) change(q<<1,l1,mid,l,r,k);
	if(r>mid) change(q<<1|1,mid+1,r1,l,r,k);
}
void ask(int q,int l,int r) {
	int old=top;
	for(res i=head[q];i;i=nxt[i]) if(vis[ver[i]]) hebing(ed[ver[i]].x,ed[ver[i]].y); //加边
	if(l==r) {
		if(!Q[l].x) tot[l]=tot[l-1],vis[mp[l][tot[l]]]^=1; //vis数组取反，mp[i][j]表示第i个询问，last=j时边的编号
		else tot[l]=(find((Q[l].x+tot[l-1]-1)%n+1)==find((Q[l].y+tot[l-1]-1)%n+1));
		while(old<top) chexiao;
		return;
	}
	int mid=l+r>>1;
	ask(q<<1,l,mid),ask(q<<1|1,mid+1,r);
	while(old<top) chexiao; //撤销回去
}
int main()
{
	read(n),read(m);
	for(res i=1;i<=n;++i) fa[i]=i,len[i]=1;
	for(res i=1;i<=m;++i) {
		read(id),read(x),read(y);
		if(id==1) {
			if(x>y) x^=y^=x^=y;a[++len1]=node(x,y,0,i);
			x%=n,y%=n,++x,++y;if(x>y) x^=y^=x^=y;a[++len1]=node(x,y,1,i);
		}
		else Q[i]=que(x,y);
	}
	sort(a+1,a+1+len1);
	int len2=1;ed[1]=edge(a[1].x,a[1].y),mp[a[1].id][a[1].q]=1;
	for(res i=2;i<=len1;++i) { //把相同的边放在一起进行区间加边，同时去重并编号，一举两得。
		int now=(a[i]!=a[i-1])?m:a[i].id;
		if(a[i-1].id<now) change(1,1,m,a[i-1].id+1,now,len2);
		if(a[i]!=a[i-1]) ed[++len2]=edge(a[i].x,a[i].y);
		mp[a[i].id][a[i].q]=len2;
	}
	if(a[len1].id<m) change(1,1,m,a[len1].id+1,m,len2);
	ask(1,1,m);
	for(res i=1;i<=m;++i) if(Q[i].x) putchar(48+tot[i]);puts("");
	return 0;
}
```

---

## 作者：shinkuu (赞：4)

强制在线是诈骗，还是很有意思的。

首先，如果没有强制在线就是一个 SGT 分治板子。强制在线看起来做不了，但是发现 $lastans=0/1$。这启示我们不同的加边可能性不会太多。考虑先记录两种加边可能。

容易发现，如果当前时刻 $j$ 可能操作 $(u,v)$，上一次可能的时刻是 $i$，则 $[i,j)$ 时间内该边的状态都是一定不会变化的。反之可能变化，所以设 $(u,v)$ 可能出现的时刻是 $i_1,i_2,i_3,\cdots,i_k$，则在线段树上对 $[i_1,i_2),[i_2,i_3),\cdots,[i_{k-1},i_k),[i_k,m]$ 进行区间插入一个加入 $(u,v)$ 的操作。

现在就要考虑怎么判断某条边是否被操作，发现这由进行加边操作前的某一次询问决定，而线段树分治最后处理答案刚好是满足在时间轴上从前往后进行的，所以可以在每次递归到叶子时分两种情况：

- 该时间进行了加/删边操作。

此时已经知道 $lastans$，所以可以知道实际操作的是哪一条边，直接将这条边的存在状态取反即可。用 map 维护。

- 查询。

求出实际查询的两点之后查询答案，记录新的 $lastans$。

每次在某个节点上面有加边操作就判断当前边是否存在，然后操作即可。

一个小细节是 $[l,r)$ 区间的 $(u,v)$ 加边是否进行取决于在 $l$ 代表的叶子节点操作后，边 $(u,v)$ 的状态，则先要求出 $l$ 的答案才能决定 $(u,v)$ 加边不加。此时可以将 $[l,r)$ 变成 $(l,r)$，因为 $l$ 位置一定不是查询，所以是不影响的。

code：

```cpp
int n,m,top,st[N];
pii a[N];
bool lans,pd[N],ans[N];
map<pii,int> lst,vis;
mt19937 rnd(time(0));
struct SGT{
	int tot,head[N<<2];
	struct node{pii x;int nxt;}e[N<<5];
	il void add(int o,pii k){e[++tot]={k,head[o]},head[o]=tot;}
	struct BCJ{
		int fa[N],c[N];
		void init(){rep(i,1,n)c[i]=rnd(),fa[i]=i;}
		int find(int x){return fa[x]==x?x:find(fa[x]);}
		il void merge(int x,int y){
			x=find(x),y=find(y);
			if(c[x]>c[y])swap(x,y);
			fa[x]=y,st[++top]=x;
		}
		il void del(int x){while(top>x)fa[st[top]]=st[top],top--;}
	}S;
	void update(int l,int r,int o,int x,int y,pii k){
		if(x>y)return;
		if(l>=x&&r<=y)return add(o,k);
		int mid=(l+r)>>1;
		if(x<=mid)update(l,mid,o<<1,x,y,k);
		if(y>mid)update(mid+1,r,o<<1|1,x,y,k);
	}
	void solve(int l,int r,int o){
		int npos=top;
		go(i,o){
			pii x=e[i].x;
			if(vis[x])S.merge(x.fi,x.se);
		}
		if(l==r){
			int u=a[l].fi,v=a[l].se;
			if(lans)u=u%n+1,v=v%n+1;
			if(u>v)swap(u,v);
			if(pd[l]){
				if(S.find(u)==S.find(v))ans[l]=lans=1;
				else ans[l]=lans=0;
			}else vis[Mp(u,v)]^=1;
			return S.del(npos);
		}
		int mid=(l+r)>>1;
		solve(l,mid,o<<1),solve(mid+1,r,o<<1|1);
		S.del(npos);
	}
}T;
void Yorushika(){
	scanf("%d%d",&n,&m);
	rep(i,1,m){
		int op,u,v;scanf("%d%d%d",&op,&u,&v);
		if(u>v)swap(u,v);
		a[i]=Mp(u,v);
		if(op==1){
			if(lst[Mp(u,v)])T.update(1,m,1,lst[Mp(u,v)]+1,i-1,Mp(u,v));
			lst[Mp(u,v)]=i;
			u=u%n+1,v=v%n+1;
			if(u>v)swap(u,v);
			if(lst[Mp(u,v)])T.update(1,m,1,lst[Mp(u,v)]+1,i-1,Mp(u,v));
			lst[Mp(u,v)]=i;
		}else pd[i]=1;
	}
	for(auto i:lst)T.update(1,m,1,i.se+1,m,i.fi);
	T.S.init(),T.solve(1,m,1);
	rep(i,1,m)if(pd[i])pc(ans[i]+'0');
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：zjftxdy (赞：4)

# [Codeforces] Forced Online Queries Problem

题意给你$m$操作，支持删边加边，查询连通性，强制在线(可能也不那么强制在线)。

如果不强制在线我们可以考虑线段树分治。一种做法是大力$LCT$，感觉比较麻烦。还有一种做法是分块。

显然的按时间分块。对于一个块$x$，我们假设它前面所有块的答案都已经计算过了，考虑如何计算当前块。我们先把$x$之前所有还存在的边暴力加入一个并查集，这部复杂度是$O(\frac{n}{T}m\log m)$($T$为块的大小)。

对于块内的一组询问$i$，我们暴力把块内在$i$之前加入且在$i$时刻还存在的边加入并查集，然后直接询问连通性即可。注意每次询问要把先把块内的边全部清空，因此这部分复杂度是$O(T^2\log m)$。





```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <set>
#include <vector>
#define ll long long
#define db double
#define rint register int
#define re register
#define pint pair<int,int>
#define eps 1e-10
#define Son 26
#define inf 1000000007
#define mk make_pair
#define IT set<pint>::iterator
#define fs first
#define sd second
#define N 400005
#define block 3000
using namespace std;
inline char get(){
	const int TOP=1<<20;
	static char T[TOP],*x=T,*y=T;
	return x==y&&(y=(x=T)+fread(T,1,TOP,stdin),x==y)?EOF:*x++;
}
inline int read (){
	register int num,sign=1;register char c;
	while (((c=get())<'0'||c>'9')&&c!='-');c=='-'?num=sign=0:num=c-48;
	while ((c=get())>='0'&&c<='9')num=(num<<3)+(num<<1)+(c-48);
	return sign?num:-num;
}
int n,m,top,last;
int opt[N];
set<pint>a,b,c;
pint q[N][2],st[N];
int ans[N],size[N],father[N];
inline void add(set<pint>&s,pint x){if(s.count(x)<1)s.insert(x);else s.erase(x);}
inline int find(rint x){if(father[x]==x)return x;return find(father[x]);}
inline void merge(rint x,rint y){
	x=find(x);y=find(y);if(x==y)return;
	if(size[x]<size[y])swap(x,y);st[++top]=mk(x,y);
	size[x]+=size[y];father[y]=x;
}
inline void cal(rint time){
	while(top!=time){
		rint x=st[top].fs,y=st[top].sd;
		father[y]=y;size[x]-=size[y];--top;
	}
}
inline void solve(){
	for(rint i=1;i<=n;++i)father[i]=i,size[i]=1;top=0;
	for(IT it=c.begin();it!=c.end();++it)merge((*it).fs,(*it).sd);last=top;
}
int main(){
	n=read();m=read();
	for(rint pos=1,x,y;pos<=m;pos+=block){
		rint l,r;l=pos,r=min(m,l+block-1);
		a.clear();b.clear();c.clear();
		for(rint i=l;i<=r;++i){
			opt[i]=read();x=read();y=read();
			if(x>y)swap(x,y);q[i][0]=mk(x,y);
			x=x%n+1;y=y%n+1;
			if(x>y)swap(x,y);q[i][1]=mk(x,y);
			if(opt[i]==1)a.insert(q[i][0]),a.insert(q[i][1]);
		}
		for(rint i=1;i<l;++i)if(opt[i]==1){if(a.count(q[i][ans[i]])<1)add(c,q[i][ans[i]]);else add(b,q[i][ans[i]]);}
		solve();
		for(rint i=l;i<=r;++i){
			if(opt[i]==1){ans[i]=ans[i-1];add(b,q[i][ans[i]]);continue;}
			cal(last);
			for(IT it=b.begin();it!=b.end();++it)merge((*it).fs,(*it).sd);
			ans[i]=(find(q[i][ans[i-1]].fs)==find(q[i][ans[i-1]].sd));
		}
	}
	for(rint i=1;i<=m;++i)if(opt[i]==2)putchar(ans[i]+'0');
}

```


---

## 作者：Cry_For_theMoon (赞：2)

给出 $n$ 个点，初始无边，接下来给定 $m$ 次操作：

$1\,\,x\,\,y$，表示如果 $(x,y)$ 之间无边则连，有边则删。边无向。

$2\,\,x\,\,y$，查询 $(x,y)$ 是否连通。连通则答案为 $1$，否则答案为 $0$。

此外，本题对输入加密。设 $lastans$ 是上一次 $2$ 操作的答案，初始 $lastans=0$。则每次真实的 $x'$ 是 $(x+lastans-1)\bmod n+1$，$y$ 同理。

$n,m\le 2\times 10^5$。

------------

这个题实际上还是挺难用文字解释的......

首先，如果没有对输入加密，则变成线段树分治的模板。可以 $O(m\log^2 n)$ 地解决。不再赘述。

由于对输入进行了加密，我们可以考虑万能的分块，是可以在 $O(m \sqrt m \log n)$ 时间内解决的。

我们现在寻求一个更优秀的做法。考虑这个问题显然强于纯离线，所以不太可能有什么全新的做法，不然离线的问题就被橄榄了。考虑能不能把线段树分治套进这个问题。

思考，为什么线段树分治不能在线处理这个问题。因为我们加入边的时候，只知道它的出现时刻是不够的，还要求知道其结束时刻，这样你才能确切地知道在哪些区间加入这条边。

需要注意到的一个特性是 $lastans$ 要么为 $0$，要么为 $1$。所以对于任意一个时刻来说，它最后的真实的 $(x',y')$ 只有两种可能。

我们来研究一条单一的边 $(u,v)$。这条边出现，在第一次 $(u,v)$ 出现后出现；在第二次 $(u,v)$ 出现后消失，第三次又出现，第四次又消失...

注意到，影响一条边的存在状态的时刻，都是在 $1\,\,u\,\,v$ （此处是真实值）这个东西出现的时刻。假设时刻 $i_1,i_2,...,i_k$ 的时候都是 $1$ 操作，且两种可能的 $(x',y')$ 里有一种是 $(u,v)$。那么 $(u,v)$ 存在状态的改变，就只**可能**会在这些时刻。之所以是“可能”，因为也许某个时刻的真实值并不是 $(u,v)$，而是另一对候选的真实值，那就不会使得 $(u,v)$ 的存在性取反。

所以我们其实可以对于这条边 $(u,v)$，把它存在的时间分为 $k-1$ 条线段：$[i_1,i_2],[i_2,i_3],...,[i_{k-1},i_k]$。根据上面的分析，不难看出，最后 $(u,v)$ 真实存在的时间，是从这 $k-1$ 条线段里选出若干条形成的并集。

更进一步的，当我们知道时刻 $i_j$ 的真实值后，其实马上可以确定在时间段 $[i_j,i_{j+1}]$ 这条边是否存在：如果 $i_j$ 时刻的真实值就是 $(u,v)$，显然其存在性是 $[i_{j-1},i_j]$ 时间段存在性的取反；否则其存在性就是 $[i_{j-1},i_j]$ 时间段内边 $(u,v)$ 的存在性。

然后我们发现一个问题：你要想知道时刻 $i_j$ 的答案，说明线段树上已经遍历到了节点 $[i_j,i_j]$ 了。但是这样，你遍历到这个节点之前，$[i_j,i_{j+1}]$ 这条边会被挂到某个父亲（或节点本身）上面去的。所以会出现一个循环：我要知道当前节点存储的一条边能不能加，得先知道某个子树内叶子的答案；但是想知道这个叶子的答案，我要把当前节点内要加的边给加了...

此时，十分巧妙的想法是把线段修改为 $[i_{j}+1,i_{j+1}]$ 的形式，容易发现左端点的调整并不会影响答案，反正时刻 $i_j$ 并不是询问。而这样，又利用到一个十分浅显的性质：在正常线段树遍历到节点 $[l,l]$ 的时候，是不会遍历过一个左边界 $\gt l$ 的节点的。（有人说这个做法是“半在线”的，这个“在线”就体现在这里。）

所以由上就可以想到并说明以下流程的正确性：

- 一开始把 $k-1$ 个时刻都打进线段树节点存储。

- 维护一个标记数组 $f$，初始都是 $0$。在加入节点存储的边过程中，如果 $f(x,y)$ 为 $1$，就加入这条边 $(x,y)$，否则不加。

- 遍历到叶子的时候，如果是询问，并查集直接查询并且更新答案即可；如果是第一类操作，设算出来的真实值是 $(x,y)$，则 $f[x,y]=f[x,y]\oplus 1$。

时间复杂度 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const int MAXN=2e5+10;
int n,m,op[MAXN],x[MAXN],y[MAXN],ans[MAXN],lastans;
map<array<int,2>,int>pre;
struct DSU{
    int fa[MAXN],sz[MAXN];
    vector<array<int,2> >op;
    int find(int x){while(fa[x]!=x)x=fa[x];return x;}
    void merge(int x,int y){
        x=find(x),y=find(y);if(x==y){op.push_back({0,0});return;}
        if(sz[x]<sz[y])swap(x,y);
        op.push_back({x,y});
        fa[y]=x;sz[x]+=sz[y];
    }
    void back(){
        int x=op.back()[0],y=op.back()[1];op.pop_back();if(!x)return;
        fa[y]=y;sz[x]-=sz[y];
    }
}dsu;
vector<array<int,2> >edge[MAXN<<2];
void upd(int x,int l,int r,int ql,int qr,int u,int v){
    if(ql<=l && qr>=r){edge[x].push_back({u,v});return;}
    int mid=(l+r)>>1;
    if(ql<=mid)upd(lc(x),l,mid,ql,qr,u,v);
    if(qr>mid)upd(rc(x),mid+1,r,ql,qr,u,v);
}
void solve(int X,int l,int r){
    int cnt=0;
    for(auto e:edge[X]){
        int x=e[0],y=e[1];
        if(pre[{x,y}]){
            cnt++;
            dsu.merge(x,y);
        }
    }
    if(l==r){
        int u=(x[l]+lastans-1)%n+1,v=(y[l]+lastans-1)%n+1;
        if(u>v)swap(u,v);
        if(op[l]==2)ans[l]=lastans=(dsu.find(u)==dsu.find(v));
        else pre[{u,v}]=pre[{u,v}]^1;
        while(cnt--)dsu.back();
        return;
    }
    int mid=(l+r)>>1;
    solve(lc(X),l,mid);solve(rc(X),mid+1,r);
    while(cnt--)dsu.back();
}
int main(){
    cin>>n>>m;
    rep(i,1,n)dsu.fa[i]=i,dsu.sz[i]=1;
    rep(i,1,m){cin>>op[i]>>x[i]>>y[i];}
    rep(i,1,m){
        if(op[i]==1){
            int x1=x[i]%n+1,y1=y[i]%n+1;if(x1>y1)swap(x1,y1);
            int x2=(x[i]-1)%n+1,y2=(y[i]-1)%n+1;if(x2>y2)swap(x2,y2);
            if(pre.find({x1,y1})!=pre.end())upd(1,1,m,pre[{x1,y1}]+1,i,x1,y1);
            if(pre.find({x2,y2})!=pre.end())upd(1,1,m,pre[{x2,y2}]+1,i,x2,y2);
            pre[{x1,y1}]=i;pre[{x2,y2}]=i;
        }
    }
    for(auto p:pre){
        if(p.second==m)continue;
        upd(1,1,m,p.second+1,m,p.first[0],p.first[1]);
    }
    pre.clear();
    solve(1,1,m);
    rep(i,1,m)if(op[i]==2)cout<<ans[i];
    return 0;
}
```

---

## 作者：happybob (赞：1)

看题目名字就知道不对。

如果真的是强制在线，等价于动态图连通性，鉴于我们不会科技，考虑这个强制在线是不是假的。

发现 $lastans$ 总是等于 $0$ 或 $1$，于是每次操作只有两种可能，把每种边按照操作分开成若干区间然后线段树分治即可。容易发现在决策一条边是否选的时候，其对应的 $lastans$ 已经在进入区间前处理出来，故这个做法是对的。时间复杂度 $O(n \log^2 n)$。

---

## 作者：Shunpower (赞：0)

简单题。

----------

考虑这个没有强制在线就是简单的线段树分治。强制在线 $las$ 只有 $0$ 和 $1$，肯定有问题。

假设我们有一项科技支持在线段树分治的同时进行加删边。线段树分治的过程是按照时间顺序进行的，所以我们总是可以算出每个操作实际上是干了什么。这时造成的影响是，一条边在时间轴上的覆盖长度收缩到这里，或者新增一条边在此之后。

考虑收缩不好做，但是新增我们是好做的。因为线段树上那 $\log$ 个用来表示 $(i,m]$ 的区间根本不会和 $[1,i]$ 有交，所以说我们新增进去的边在时间轴上覆盖的位置我们能够在之后正确地扫到。具体可以看 [CF576E Painting Edges](https://www.luogu.com.cn/problem/CF576E)，利用了这个已维护区间和修改区间不交的性质。

考虑我们怎么不收缩。可以发现，每条边在被加入的时候至多只有四种可能的被删掉的地方。我们拿一个链表或者队列单独维护每种操作还剩下的位置，就能找出这些地方中最靠前的那个。

显然这条边至少能够覆盖到那里。所以我们先覆盖掉它之前的位置，并把这个区间挂在那里。这样当我们操作一条边的时候，还要将它身上挂的区间再遍历一遍，如果不是被删掉了就要再往后找最靠前的可能被删掉的地方，同理得延长过去。

这样就只有新增区间没有收缩区间了。

看上去复杂度似乎很有问题哇？每条操作的边都可能会往后挂若干次？事实上复杂度是正确的。考虑每个操作在被解除强制在线前都只可能被四种边挂到，这四种边一定来自于至多四个操作（否则一定存在一个操作挂了相同的边，而这显然不可能），所以说每个操作上至多只挂 $\mathcal O(1)$ 个。

时间复杂度 $\mathcal O(n\log^2 n)$。实现的时候注意一下边不区分顺序，有点烦人。

```cpp
int n,m;
struct queries{
	int op,x,y;
} Q[N];
map <pii,queue<int>> p;
vector <pii> hang[N];
vector <pii> ofl[N<<2];
int f[N],sz[N];
stack <pair<int&,int>> his_f,his_sz;
bool ans[N];
int las;
int find(int x){
	if(f[x]==x) return x;
	return find(f[x]);
}
void rollback(int gl){
	while(his_f.size()!=gl){
		his_f.top().fi=his_f.top().se;
		his_f.pop();
		his_sz.top().fi=his_sz.top().se;
		his_sz.pop();
	}
}
void merge(int u,int v){
	u=find(u),v=find(v);
	if(u==v) return;
	if(sz[u]>sz[v]) swap(u,v);
	his_sz.push({sz[v],sz[v]});
	his_f.push({f[u],f[u]});
	sz[v]+=sz[u];
	f[u]=v;
}
int getnext(pii E){
	int nx=(E.fi-1==0?n:E.fi-1)+1;
	int ny=(E.se-1==0?n:E.se-1)+1;
	int minn=1e9;
	if(p.count(mp(nx-1,ny-1))&&!p[mp(nx-1,ny-1)].empty()) minn=min(minn,p[mp(nx-1,ny-1)].front());
	if(p.count(mp(nx,ny))&&!p[mp(nx,ny)].empty()) minn=min(minn,p[mp(nx,ny)].front());
	return minn;
}
#define mid (l+r>>1)
void modify(int rt,int l,int r,int ml,int mr,pii E){
	if(ml>mr) return;
	if(ml<=l&&r<=mr){
		return ofl[rt].pb(E),void();
	}
	if(ml<=mid) modify(rt<<1,l,mid,ml,mr,E);
	if(mid<mr) modify(rt<<1|1,mid+1,r,ml,mr,E);
}
void calc(int rt,int l,int r){
	int tsz=his_f.size();
	for(auto i:ofl[rt]) merge(i.fi,i.se);
	if(l==r){
		if(Q[l].op==2){
			Q[l].x=(Q[l].x+las-1)%n+1;
			Q[l].y=(Q[l].y+las-1)%n+1;
			ans[l]=(find(Q[l].x)==find(Q[l].y)),las=ans[l];
		}
		else{
			p[mp(Q[l].x,Q[l].y)].pop();
			Q[l].x=(Q[l].x+las-1)%n+1;
			Q[l].y=(Q[l].y+las-1)%n+1;
			bool flg=0;
			for(auto i:hang[l]){
				if(i!=mp(Q[l].x,Q[l].y)&&i!=mp(Q[l].y,Q[l].x)){
					int nxt=min(getnext(i),getnext(mp(i.se,i.fi)));
					if(nxt<=m){
						hang[nxt].pb(i);
						modify(1,1,m,l+1,nxt-1,i);
					}
					else modify(1,1,m,l+1,m,i);
				}
				else flg=1;
			}
			if(!flg){
				int nxt=min(getnext(mp(Q[l].x,Q[l].y)),getnext(mp(Q[l].y,Q[l].x)));
				if(nxt<=m){
					hang[nxt].pb(mp(Q[l].x,Q[l].y));
					modify(1,1,m,l+1,nxt-1,mp(Q[l].x,Q[l].y));
				}
				else modify(1,1,m,l+1,m,mp(Q[l].x,Q[l].y));
			}
		}
		rollback(tsz);
		return;
	}
	calc(rt<<1,l,mid);
	calc(rt<<1|1,mid+1,r);
	rollback(tsz);
}
#undef mid
int main(){
#ifdef Shun
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	cin>>n>>m;
	fr1(i,1,n) f[i]=i,sz[i]=1;
	fr1(i,1,m){
		cin>>Q[i].op>>Q[i].x>>Q[i].y;
		if(Q[i].op==1) p[mp(Q[i].x,Q[i].y)].push(i);
	}
	calc(1,1,m);
	fr1(i,1,m){
		if(Q[i].op==2) cout<<ans[i];
	}
	ET;
}
//ALL FOR Zhang Junhao.
```

---

## 作者：Mashu77 (赞：0)

动态图连通性。但无需 
LCT + ETT，因为这是假加密。注意到 
$l
s
t
a
n
s$
 为 
$0$
 或 
$1$，则真实值只有两种情况。

$O
(
n
\log
n
)$
 的方法是线段树分治，但我看不懂。这里只说 
$O
(
n
^{\frac{4}{3}}
\log
n
)$
 的分块。

并查集支持撤销，但图上删边不是撤销。一种 
$O
(
n^
2
)$
 的暴力是，对于每个询问，将它前面的所有还存在的线段提出来，重新构建并查集。

受此启发，我们考虑分块，设块大小为 
$T$。对每个块，将前面的所有还存在的线段提出来：这其中有两种，一种是此块中不可能出现的，状态一定不变；另一种是可能出现的，状态可能会变。我们对第一种先构建并查集。将第二种加入一个集合中（第一次加，第二次减，类似异或 
$1$）。

接着考虑块内的询问。用类似暴力的方法，将在块内且在此询问前的修改操作加入上面的集合中（方法同上）。此时，我们可以保证此集合大小不超过 
$T$。于是可以在上面的并查集中加入此集合内的线段，得出答案后撤销。

分析复杂度，为 
$O
(
\frac{n}{
T}
n
\log
n
)
+
O
(
T^
2
\log
n
)$。当 
$T=
n^{\frac{
2}{
3}}$
 时，为 
$O
(
n^{\frac{
4}{
3}}
\log
n
)$。

---

