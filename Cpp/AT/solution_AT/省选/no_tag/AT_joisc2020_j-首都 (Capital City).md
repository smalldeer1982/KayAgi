# 首都 (Capital City)

## 题目描述

JOI 国拥有 $N$ 个城镇，编号为 $1$ 到 $N$，这些城镇由 $N-1$ 条双向道路连接。

JOI 国还拥有 $K$ 个城市，编号为 $1$ 到 $K$，第 $i$ 个城镇属于第 $C_i$ 个城市。

现在 JOI 国的总理 JOI 君 114514 世要挑选一个城市作为首都，从首都中的任一个城镇到达另一个首都中的城镇可以只经过首都中的城镇，但这明显是不合理的。

所以 JOI 君 114514 世要进行合并城市，合并城市 $x$ 和城市 $y$ 就会把城市 $y$ 里的所有小镇归为城市 $x$。

求能找到首都的最小合并次数。

## 说明/提示

#### 样例 1 解释

可以将城市 $1$ 和 $3$ 合并，然后选择城市 $1$ 作为首都。

#### 子任务

|子任务|特殊性质|分数|
|:-:|:-:|:-:|
|$1$|$N \le 20$|$1$|
|$2$|$N \le 2000$|$10$|
|$3$|每个城镇最多与两个城镇相连|$30$|
|$4$|无|$59$|

对于 $100\%$ 的数据，$1 \le K,u,v \le N \le 2 \times 10^5$，保证从任何一个城镇出发都能到达其他城镇，$1 \le C_i \le K$。


翻译自 [第１９回日本情報オリンピック　春季トレーニング合宿](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/index.html) [Day4 A 首都](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/day4/capital_city.pdf)。

# 题解

## 作者：__Aaaaaaaa (赞：0)

## 题目描述

给定一棵无根树，树上每个结点都有一个颜色，问最少可以使用多少次形如“将所有颜色为 $a$ 的结点变为颜色为 $b$ 的结点”这样的操作之后使得至少存在一种颜色的所有结点形成一颗连通子树。

## Solution
可以考虑一种颜色 $c$，将它作为目标颜色，将它的所有结点从树中取出来。

这样可以确定最小的一棵连通子树使得所有颜色为 $c$ 的结点都在这棵连通子树上。

但是连通子树上会存在许多其他颜色的结点。这样可以确定很多形如“必须将颜色 $d$ 归为颜色 $c$ 才能达成目标”的颜色之间的关系。然而只将所有 $d$ 变成 $c$ 是不够的。

将这样的颜色关系进行连边。$c$ 连向 $d$ 表示 “必须将颜色 $d$ 归为颜色 $c$ 才能达成所有颜色为 $c$ 的结点组成一棵连通子树”。

根据这样的依赖关系，对所有颜色都去尝试连边，然后将图建立出来。

可以发现，想要满足“所有颜色为 $c$ 的结点组成一棵连通子树”，必须要将点 $c$ 可以到达的所有颜色都变成 $c$。答案等价于点数最少的缩点之后出度为 $0$ 的强连通分量的点数。

而连边可以使用重链剖分+线段树优化建图，建立同色结点形成的连通子树可以使用类似虚树的建立方法。

~~这种方法太丑了不推荐~~，这种方法的时间复杂度是 $O(n\log^2_2n)$，瓶颈在于线段树优化建图和确定连通子树上，这些的常数是低于点分治的，效率良好。

## Code
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N=2e5+10,L=N*4,M=1e7+10;
char buf[1<<20],*p1=buf,*p2=buf;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
inline int read(){int x=0;char ch=gc();while(ch>'9'||ch<'0'){ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48),ch=gc();}return x;}
int n,m;
int h[N],h2[L],e[M],ne[M],ct=1;
void add(int h[],int x,int y){
	e[ct]=y,ne[ct]=h[x],h[x]=ct++;
}
int depth[N],dfn[N],fa[N],top[N],son[N],sz[N],ts;
void dfs1(int u,int v){
	depth[u]=depth[v]+1,fa[u]=v;
	sz[u]=1;
	for(int i=h[u];i;i=ne[i])if(e[i]!=v){
		dfs1(e[i],u);
		sz[u]+=sz[e[i]];
		if(sz[e[i]]>sz[son[u]])son[u]=e[i];
	}
}
int idf[N];
void dfs2(int u,int t){
	top[u]=t,dfn[u]=++ts;
	idf[ts]=u;
	if(!son[u])return;
	dfs2(son[u],t);
	for(int i=h[u];i;i=ne[i]){
		if(e[i]!=fa[u]&&e[i]!=son[u])
			dfs2(e[i],e[i]);
	}
}
int mark,root;
int idx;
struct tree{
	int l,r;
}tr[L];
void query(int s,int u,int l,int r,int L,int R){
	if(l>=L&&r<=R){
		add(h2,s,u);
		return;
	}
	int mid=l+r>>1;
	if(mid>=L)query(s,tr[u].l,l,mid,L,R);
	if(mid<R)query(s,tr[u].r,mid+1,r,L,R);
}
int c[N];
void build(int &u,int l,int r){
	u=++idx;
	if(l==r){
		add(h2,u,c[idf[l]]);
		return;
	}
	int mid=l+r>>1;
	build(tr[u].l,l,mid);
	build(tr[u].r,mid+1,r);
	add(h2,u,tr[u].l);
	add(h2,u,tr[u].r);
}
void update(int x,int y){
	int res=0,t=c[x];
	while(top[x]!=top[y]){
		if(depth[top[x]]<depth[top[y]])swap(x,y);
		query(t,root,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])swap(x,y);
	query(t,root,1,n,dfn[x],dfn[y]);
}
vector<int>v[N];
int cnt[L],scc,bel[L],ind[L];
int Dfn[L],Low[L],timestamp;
int stk[L],tt;
bool ins[L];
void tarjan(int u){
	Dfn[u]=Low[u]=++ts;
	stk[++tt]=u,ins[u]=true;
	for(int i=h2[u];i;i=ne[i]){
		int j=e[i];
		if(!Dfn[j]){
			tarjan(j);
			Low[u]=min(Low[u],Low[j]);
		}
		else if(ins[j])
			Low[u]=min(Low[u],Dfn[j]);
	}
	if(Dfn[u]==Low[u]){
		int j;
		++scc;
		do{
			ins[j=stk[tt--]]=false,cnt[scc]+=(j<=m),bel[j]=scc;
		}while(j!=u);
	}
}
bool dead[L];
int main(){
	n=read(),m=read();
	for(int i=1,x,y;i<n;++i){
		x=read(),y=read();
		add(h,x,y),add(h,y,x);
	}
	for(int i=1;i<=n;++i){
		c[i]=read();
		v[c[i]].emplace_back(i);
	}
	dfs1(1,0),dfs2(1,1);
	idx=m;
	build(root,1,n);
	for(int c=1;c<=m;++c){
		sort(v[c].begin(),v[c].end(),[](const int x,const int y){return dfn[x]<dfn[y];});
		++mark;
		if(v[c].size()==1){
			puts("0");
			return 0;
		}
		for(int i=0;i<v[c].size()-1;++i){
			update(v[c][i],v[c][i+1]);
		}
	}
	for(int i=1;i<=idx;++i)
		if(!Dfn[i])tarjan(i);
	for(int i=1;i<=idx;++i)if(!dead[bel[i]]){
		for(int j=h2[i];j;j=ne[j]){
			if(bel[e[j]]!=bel[i]){
				dead[bel[i]]=true;
				break;
			}
		}
	}
	int ans=1e9;
	for(int i=1;i<=scc;++i)if(!dead[i])
		ans=min(ans,cnt[i]-1);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# JOISC2020J 题解

[Problem Link](https://qoj.ac/problem/3561)

**题目大意**

> 给 $n$ 个点的树，每个点有一个 $[1,m]$ 之间的颜色，求一个最小的颜色集合 $S$，使得颜色在 $S$ 中的点两两连通。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

考虑从一个点 $u$ 开始确定一个极小联通块，先加入 $c_u$，然后把所有该颜色的点到根的颜色加入，直到无法拓展，容易证明这样会得到包含 $u$ 的最小的联通块。

然后我们要考虑不包含 $u$ 的最小联通块，显然对 $u$ 的每个子树问题都是独立的，我们对每个子树递归求解。

容易发现这是标准的点分治形式，每次取 $u$ 为当前连通块的根即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int MAXN=2e5+5;
vector <int> G[MAXN],C[MAXN];
int n,m,ans,siz[MAXN],cur[MAXN],col[MAXN],que[MAXN],ti[MAXN],fa[MAXN];
bool vis[MAXN],inq[MAXN];
inline void solve(int u) {
	function<void(int,int)> dfs3=[&](int x,int fz) {
		ti[x]=u,fa[x]=fz,inq[col[x]]=0;
		for(int y:G[x]) if(!vis[y]&&y!=fz) dfs3(y,x);
	};
	dfs3(u,0);
	int hd=1,tl=1,ok=1;
	inq[que[1]=col[u]]=true;
	while(hd<=tl) {
		int x=que[hd++];
		for(int v:C[x]) if(ti[v]!=u) return ;
		for(int v:C[x]) for(;v!=u&&!inq[col[fa[v]]];v=fa[v]) inq[que[++tl]=col[fa[v]]]=true;
	}
	if(ok) ans=min(ans,tl-1);
}
inline void dfs0(int u) {
	vis[u]=true,solve(u);
	for(int v:G[u]) if(!vis[v]) {
		function<void(int,int)> dfs1=[&](int x,int fz) {
			siz[x]=1;
			for(int y:G[x]) if(y!=fz&&!vis[y]) dfs1(y,x),siz[x]+=siz[y];
		};
		dfs1(v,u);
		int cet=0,alls=siz[v];
		function<void(int,int)> dfs2=[&](int x,int fz) {
			cur[x]=alls-siz[x];
			for(int y:G[x]) if(y!=fz&&!vis[y]) dfs2(y,x),cur[x]=max(cur[x],siz[y]);
			if(!cet||cur[x]<cur[cet]) cet=x;
		};
		dfs2(v,u),dfs0(cet);
	}
}
signed main() {
	scanf("%d%d",&n,&m),ans=m;
	for(int i=1,u,v;i<n;++i) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	for(int i=1;i<=n;++i) scanf("%d",&col[i]),C[col[i]].push_back(i);
	dfs0(1);
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：myee (赞：0)

### 思路

显然答案可以认为是将若干个城市拼成一个城市后会联通。

考虑如果一个城市被选入答案中，则其对应所有节点构成的**虚树**上的所有城市均需被选择。

我们把这种关系连有向边，然后缩点，那么**无出度的最小 SCC 即为答案**；注意还要减 $1$。

直接连边是 $O(n^2)$ 的，怎么优化？

我们考虑直接倍增优化建图，从而点数、边数均为 $O(n\log n)$ 级别的。

注意倍增优化建图时的虚点贡献不能被计入答案中。

总复杂度 $O(n\log n)$。

### Code

这份实现的常数很大。

```cpp
const uint B=17;
uint F[B+1][200005],Dfn[200005],Dep[200005],n,k;
std::vector<uint>Way[200005],P[200005];
uint To[28000005],Last[28000005],End[4000005],REnd[4000005],cnt;
inline voi insert(uint u,uint v)
{
    Last[cnt]=End[u],To[cnt]=v,End[u]=cnt++;
    Last[cnt]=REnd[v],To[cnt]=u,REnd[v]=cnt++;
}
voi dfs(uint p,uint f)
{
    static uint cnt=0;Dfn[p]=cnt++,F[0][p]=f;
    for(uint i=1;(1u<<i)<=Dep[p]+1;i++)
        F[i][p]=F[i-1][F[i-1][p]],insert(i*n+k+p,(i-1)*n+k+p),insert(i*n+k+p,(i-1)*n+k+F[i-1][p]);
    for(auto s:Way[p])if(s!=f)Dep[s]=Dep[p]+1,dfs(s,p);
}
uint lca(uint u,uint v)
{
    if(Dep[u]<Dep[v])std::swap(u,v);
    for(uint i=B;~i;i--)if(Dep[u]-Dep[v]>=(1u<<i))u=F[i][u];
    if(u==v)return u;
    for(uint i=B;~i;i--)if(F[i][u]!=F[i][v])u=F[i][u],v=F[i][v];
    return F[0][u];
}
bol G[4000005];uint S[4000005],Id[4000005],Cnt[4000005];
voi dfs1(uint p)
{
    static uint cnt=0;
    G[p]=true;
    for(uint e=End[p];~e;e=Last[e])if(!G[To[e]])dfs1(To[e]);
    S[cnt++]=p;
}
voi dfs2(uint p,uint c)
{
    G[p]=false,Cnt[Id[p]=c]+=p<k;
    for(uint e=REnd[p];~e;e=Last[e])if(G[To[e]])dfs2(To[e],c);
}
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    freopen("QAQ.out","w",stdout);
#endif
    scanf("%u%u",&n,&k);
    for(uint i=0;i<n*B+k;i++)End[i]=REnd[i]=-1;
    for(uint i=1,u,v;i<n;i++)scanf("%u%u",&u,&v),Way[--u].push_back(--v),Way[v].push_back(u);
    for(uint i=0,v;i<n;i++)scanf("%u",&v),P[--v].push_back(i),insert(i+k,v);
    dfs(0,0);
    for(uint i=0;i<k;i++)
    {
        std::sort(P[i].begin(),P[i].end(),[&](uint a,uint b){return Dfn[a]<Dfn[b];});
        for(uint j=1,u,v,r;j<P[i].size();j++)
        {
            r=lca(u=P[i][j-1],v=P[i][j]);
            for(uint t=B;~t;t--)if(Dep[u]-Dep[r]>=(1u<<t))insert(i,t*n+k+u),u=F[t][u];
            for(uint t=B;~t;t--)if(Dep[v]-Dep[r]>=(1u<<t))insert(i,t*n+k+v),v=F[t][v];
            insert(i,k+r);
        }
    }
    for(uint i=0;i<n*B+k;i++)if(!G[i])dfs1(i);
    uint c=0;
    for(uint i=n*B+k-1;~i;i--)if(G[S[i]])dfs2(S[i],c++);
    for(uint i=0;i<cnt;i+=2)if(Id[To[i]]!=Id[To[i|1]])Cnt[Id[To[i|1]]]=0;
    uint ans=-1;
    while(c--)_min(ans,Cnt[c]-1);
    printf("%u\n",ans);
    return 0;
}
```


---

## 作者：_Diu_ (赞：0)

题意：一棵树，每个点有颜色，要求选出一个颜色集合，使得所有是这些颜色的点并起来在树上是一个连通块，要求选择颜色数量最小。

---

非常优美的点分治做法。

先想个暴力，我们枚举每个点，统计包含每个点 $u$ 的颜色数量最少的连通块。一个很朴素的做法就是以这个点为根搜一次，建立一个颜色队列，首先把该点的颜色入队，每次弹出一个颜色，把所有是这个颜色的点遍历一次，每次从这个点往父亲跳，如果出现新颜色就把它入队，如果出现已经遍历过的点说明它网上的点都遍历过了，就直接跳。

分析复杂度每次是 $O(n)$ 的，总时间是 $O(n^2)$ 的。

我们可以放到点分治上维护这个操作，每次以当前分治中心为枚举的点，不过如果在枚举过程中出现当前连通块外的点就直接结束，因为如果经过外面的点，那么相当于经过了某一级分治祖先，那么那级的颜色队列一定会被当前的遍历包含，要么相同，要么更劣，所以直接不用考虑。

每一层复杂度和该层点数相关，总时间复杂度 $O(n\log n)$，空间 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,k,c[N],d[N];
struct edge{
	int v,nxt;
}e[N<<1];
int hd[N],tot;
void add(int u,int v){e[++tot]={v,hd[u]},hd[u]=tot,d[v]++;}
vector<int> g[N];
int Sz,Rt,sz[N],mx[N],vis[N],vic[N];
int ans;
void get_sz(int u,int fa){
	++Sz;
	for(int i=hd[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa||vis[v])continue;
		get_sz(v,u);
	}
}
void get_rt(int u,int fa){
	sz[u]=1,mx[u]=0;
	for(int i=hd[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa||vis[v])continue;
		get_rt(v,u);
		sz[u]+=sz[v];
		mx[u]=max(mx[u],sz[v]);
	}
	mx[u]=max(mx[u],Sz-sz[u]);
	if(!Rt||mx[u]<mx[Rt])Rt=u;
}
int fa[N],dep[N],Vis[N];
void get_fa(int u,int k){
	Vis[u]=k;
	for(int i=hd[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa[u]||vis[v])continue;
		fa[v]=u,dep[v]=dep[u]+1;
		get_fa(v,k);
	}
}
int st[N],tp;
void get_ans(int u){
	if(!c[u])return;
	dep[u]=1,fa[u]=0;
	get_fa(u,u);
	st[tp=1]=c[u],vic[c[u]]=u;
	for(int k=1;k<=tp;k++){
//		printf("Col:%d\n",st[k]);
		for(int i=0;i<g[st[k]].size();i++){
			int v=g[st[k]][i];
			if(Vis[v]!=u)return;
			while(dep[v]){
				if(!c[v])return;
				if(vic[c[v]]!=u)vic[c[v]]=u,st[++tp]=c[v];
//				printf("Find:%d\n",v);
				dep[v]=0,v=fa[v];
			}
		}
	}
	ans=min(ans,tp-1);
//	printf("%d\n",tp-1);
}
void divide(int u){
//	printf("Divide:%d\n",u);
	get_ans(u);
	vis[u]=1;
	for(int i=hd[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(vis[v])continue;
		Sz=0;get_sz(v,u);
		Rt=0;get_rt(v,u);
		divide(Rt);
	}
}
signed main(){
	scanf("%d%d",&n,&k),ans=k-1;
	for(int u,v,i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++)scanf("%d",&c[i]),g[c[i]].push_back(i);
	Sz=n;get_rt(1,0);
	divide(Rt);
	printf("%d\n",ans);
}
```


---

