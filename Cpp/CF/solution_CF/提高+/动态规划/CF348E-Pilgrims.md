# Pilgrims

## 题目描述

A long time ago there was a land called Dudeland. Dudeland consisted of $ n $ towns connected with $ n-1 $ bidirectonal roads. The towns are indexed from $ 1 $ to $ n $ and one can reach any city from any other city if he moves along the roads of the country. There are $ m $ monasteries in Dudeland located in $ m $ different towns. In each monastery lives a pilgrim.

At the beginning of the year, each pilgrim writes down which monastery is the farthest from the monastery he is living in. If there is more than one farthest monastery, he lists all of them. On the Big Lebowski day each pilgrim picks one town from his paper at random and starts walking to that town.

Walter hates pilgrims and wants to make as many of them unhappy as possible by preventing them from finishing their journey. He plans to destroy exactly one town that does not contain a monastery. A pilgrim becomes unhappy if all monasteries in his list become unreachable from the monastery he is living in.

You need to find the maximum number of pilgrims Walter can make unhappy. Also find the number of ways he can make this maximal number of pilgrims unhappy: the number of possible towns he can destroy.

## 样例 #1

### 输入

```
8 5
7 2 5 4 8
1 2 1
2 3 2
1 4 1
4 5 2
1 6 1
6 7 8
6 8 10
```

### 输出

```
5 1
```

# 题解

## 作者：糪眾脦颰罷 (赞：6)

[题目链接](https://codeforces.com/problemset/problem/348/E)
## 树的性质（O(n)写法）
很好的一道题。
当然，还有树上差分，点分治等写法。
联想树的直径，不难发现有这样一个性质：
>所有教徒到离他最远的修道院的路径必定相交于一个节点。而这个节点就是一条最长路径的中点。我们称这个点为**中心**（特别的中点在于某条两点间的边上时，这条边的两个端点都可以作为中心）

有了这个性质，我们先找到中心，再把中心作为根节点，这样的话，所有教徒走到目的地都需要**经过根节点。**

然后我们再处理出根节点所有儿子的子树中距离根节点最远的修道院的距离。

接着，就是重点了。

我们枚举一个要毁掉的非修道院的点，那么，其子树中所有的教徒都无法达到目的地（**无法到根节点**）。

那对于子树外的点呢？

分类讨论！

有如下情况:（我们先标记根节点的儿子，若其子树中有最大深度，记为A，若有次达深度，记为B，都没有，则记为C，同时最大深度和次大深度严格不相等）

**1.A和B的数量都为1**
![](https://cdn.luogu.com.cn/upload/pic/65269.png)

由图知，除了A要到B外，其他的点都是到A。

也就是说，如果断了A内的点，将会隔断除A外**其他所有子树的教徒**

如果断了B内的点，那么只会隔断**A内的所有教徒**

**2.A的数量为1，B的数量大于等于2**

![](https://cdn.luogu.com.cn/upload/pic/65270.png)
由图知，A可以到2个B，而其他的点都是到A。

那么，如果断了A内的点，仍将会隔断除A外**其他所有子树的教徒**

而断了B内的点呢？那么A依然可以走到一个符合条件的B，也就是说，**此时不会影响到其他点**

**3.A的数量大于等于2**

![](https://cdn.luogu.com.cn/upload/pic/65272.png)

由图知，断了A内的点，其他子树的教徒依然不会被隔断

而断了B内的点，**A内的教徒还可以到另一个A**，依然不会有影响
**也就是说，当A的数量大于等于2时，我们只用考虑子树内有多少个教徒被隔断了即可**

真的这样吗？

再来看下一个。

#### 4.A的数量为2，B的数量为0
![](https://cdn.luogu.com.cn/upload/pic/65273.png)
显然，C中是没有教徒的（如果有的话，那么其就变成B了）
这种情况我们要特判。

因为，当隔断的点在一个A中时，**另一个A中的教徒会被隔断**

最后，在处理一下隔断的点在根节点时的情况即可。

#### 最后，注意细节！注意细节！注意细节！

代码:(巨丑无比，建议不要看，最好拿去对拍)
```c++
#include<bits/stdc++.h>
#define MAXN 100010
using namespace std;
int n,m,duan1,duan2,Len_D,deep[MAXN],dis[3][MAXN],root,max_deep[MAXN],size[MAXN],MaxMax,MinMax,MaxCnt,MinCnt,sumMax[MAXN],sumMin[MAXN],ans,ans_can;
int TreeCntMax,TreeCntMin,TreeKind[MAXN],Add1,Add2;
struct node {
	int ed,v;
};
vector<node>G[MAXN];
bool mark[MAXN];
void Get_D(int x,int fa,int sum,int pos) {
	if(sum>=Len_D&&mark[x]) {
		Len_D=sum;
		if(!pos)duan1=x;
		else duan2=x;
	}
	for(int i=0; i<G[x].size(); i++) {
		int t=G[x][i].ed,v=G[x][i].v;
		if(t==fa)continue;
		Get_D(t,x,sum+v,pos);
	}
}
void BL(int x,int fa,int sum,int pos) {
	dis[pos][x]=sum;
	for(int i=0; i<G[x].size(); i++) {
		int t=G[x][i].ed,v=G[x][i].v;
		if(t==fa)continue;
		BL(t,x,sum+v,pos);
	}
}
void Get_root() { //找类中心
	int st;
	for(int i=1;i<=n;i++){
		if(mark[i]){
			st=i;
			break;
		}
	}
	Get_D(st,0,0,0);
	Get_D(duan1,0,0,1);
	BL(duan1,0,0,1);
	BL(duan2,0,0,2);
	for(int i=1,cha=2e9+7; i<=n; i++) {
		if(dis[1][i]+dis[2][i]==Len_D) {
			if(abs(dis[1][i]-dis[2][i])<cha) {
				cha=abs(dis[1][i]-dis[2][i]);
				root=i;
			}
		}
	}
}
void DFS(int x,int fa) {
	for(int i=0; i<G[x].size(); i++) {
		int t=G[x][i].ed,v=G[x][i].v;
		if(t==fa)continue;
		deep[t]=deep[x]+v;
		DFS(t,x);
	}
}
void DFS2(int x,int fa) {
	if(mark[x]) {
		size[x]++;
		if(deep[x]==MaxMax)sumMax[x]++;
		if(deep[x]==MinMax)sumMin[x]++;
	}
	for(int i=0; i<G[x].size(); i++) {
		int t=G[x][i].ed;
		if(t==fa)continue;
		DFS2(t,x);
		size[x]+=size[t];
		sumMax[x]+=sumMax[t];
		sumMin[x]+=sumMin[t];
	}
}
void Get_Max(int x,int fa) {
	if(mark[x])max_deep[x]=max(max_deep[x],deep[x]);
	for(int i=0; i<G[x].size(); i++) {
		int t=G[x][i].ed;
		if(t==fa)continue;
		Get_Max(t,x);
		max_deep[x]=max(max_deep[x],max_deep[t]);
	}
}
void solve(int x,int fa,int Add,int Kind) {
	if(!mark[x]) {
		int res=0;
		res+=size[x];
		if(Kind==1) {
			if(TreeCntMax==1) {
				if(sumMax[x]==MaxCnt)res+=Add;
			}
		} else if(Kind==2) {
			if(TreeCntMax==1&&TreeCntMin==1) {
				if(sumMin[x]==MinCnt)res+=Add;
			}
		}
		if(res>ans) {
			ans=res;
			ans_can=1;
		} else if(ans==res)ans_can++;
	}
	for(int i=0; i<G[x].size(); i++) {
		int t=G[x][i].ed;
		if(t==fa)continue;
		solve(t,x,Add,Kind);
	}
}
void tepan(){
	int t1,t2;
	for(int i=0,p=1;i<G[root].size();i++){
		int t=G[root][i].ed;
		if(max_deep[t]==MaxMax){
			if(p==1)t1=t,p=-1;
			else t2=t;
		}
	}
	sumMin[t2]=sumMax[t2],sumMax[t2]=0;
	MaxCnt=sumMax[t1],MinCnt=sumMin[t2];
	TreeKind[t2]=2;
	Add1=size[t2],Add2=size[t1];
}
void Calc(int x,int fa,int &Ma,int &tot){
	if(mark[x]){
		if(deep[x]>Ma){
			Ma=deep[x];
			tot=1;
		}
		else if(deep[x]==Ma)tot++;
	}
	for(int i=0;i<G[x].size();i++){
		int t=G[x][i].ed;
		if(t==fa)continue;
		Calc(t,x,Ma,tot);
	}
}
int main() {
	scanf("%d %d",&n,&m);
	for(int i=1,x; i<=m; i++)scanf("%d",&x),mark[x]=true;
	for(int i=1; i<=n-1; i++) {
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		G[x].push_back((node) {y,z});
		G[y].push_back((node) {x,z});
	}
	Get_root();
	DFS(root,0);
	Get_Max(root,0);
	for(int i=0; i<G[root].size(); i++) {
		int t=G[root][i].ed;
		if(max_deep[t]>MaxMax) {
			MinMax=MaxMax;
			MaxMax=max_deep[t];
		} else if(max_deep[t]>MinMax) {
			MinMax=max_deep[t];
		}
	}
	for(int i=0;i<G[root].size();i++){
		int t=G[root][i].ed;
		int Ma=0,tot=0;
		Calc(t,root,Ma,tot);
		if(Ma==MaxMax)MaxCnt+=tot;
		else if(Ma==MinMax)MinCnt+=tot;
	}
	for(int i=0; i<G[root].size(); i++) {
		int t=G[root][i].ed;
		if(max_deep[t]==MaxMax)TreeCntMax++,TreeKind[t]=1;
		else if(max_deep[t]==MinMax)TreeCntMin++,TreeKind[t]=2;
	}
	DFS2(root,0);
	Add1=m;
	for(int i=0; i<G[root].size(); i++) {
		int t=G[root][i].ed;
		if(TreeKind[t]==1)Add1-=size[t],Add2+=size[t];
	}
	if(TreeCntMax==2&&TreeCntMin==0){
		tepan();
		TreeCntMax=TreeCntMin=1;
	}
	for(int i=0; i<G[root].size(); i++) {
		int t=G[root][i].ed;
		if(TreeKind[t]==1)solve(t,root,Add1,1);
		else if(TreeKind[t]==2)solve(t,root,Add2,2);
		else solve(t,root,0,0);
	}
	if(!mark[root]) {
		if(m>ans) {
			ans=m;
			ans_can=1;
		} else if(ans==m)ans_can++;
	}
	cout<<ans<<" "<<ans_can;
	return 0;
}
```



---

## 作者：George1123 (赞：5)

更魔法棒的阅读体验 $\to $ [`George1123`](https://www.cnblogs.com/George1123/p/14035139.html)

---

## 题面

> [CF348E Pilgrims](https://www.luogu.com.cn/problem/CF348E)

> 有一棵 $n$ 个点的 **带权** 树和 $m$ 个关键点，要求杀了一个不关键的点，满足最多的关键点到离它最远的所有关键点的路径都被打断。求可以满足的最多关键点数和此时的杀点方案数。

> 数据范围：$2\le m<n\le 10^5$。

---

## 题解

写了个奇怪的做法调了一个上午，写篇不行的题解。

很明显所有关键点到所有离它最远的关键的所有路径都经过一个点：

距离最远的一对关键点的中点（不需要取 $\frac{dist}{2}$ 的位置建出一个新点！如果真正的中心在边上，边上的两点都行！）。

对于每个点 $u$，如果以它为根，离它最远的所有点的 $\rm lca$ 为 $v$，只有杀 $u$ 和 $v$ 路径上的点才能杀死 $u$。

所以目标就是对于每个 $u$ 找 $v$，然后最后树上差分就可以了。

可以以上文中的中点为根，边 `dfs` 边找，这个 $v$ 是可以动态维护的。

如果当前 `dfs` 到节点 $u$，这个 $v$ 绝不会是它的子树点，甚至不可能是和 $u$ 在根的同一棵子树内的点。

所以所有离 $u$ 最远的点的当前 $\rm lca$ 就是 $v$。

可以线段树，维护区间最大值和最大值点的 $\rm lca$，支持区间加减。

然后就解决了。如果嫌弃 $\Theta(\log n)$ 的 `pushup`，可以用 `ST` 表 $\Theta(1)$ `lca`。

---

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define x first
#define y second
#define bg begin()
#define ed end()
#define pb push_back
#define mp make_pair
#define sz(a) int((a).size())
#define R(i,n) for(int i(0);i<(n);++i)
#define L(i,n) for(int i((n)-1);~i;--i)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1e5+1;
int n,m,rt=-1,mon[N];
bool imon[N],newed;

//Tree_0
const int D=20;
vector<int> e[N],to,we;
void adde(int u,int v,int w){
    e[u].pb(sz(to)),to.pb(v),we.pb(w);
    e[v].pb(sz(to)),to.pb(u),we.pb(w);
}
int dep[N],pre[N],in,dfn[N],lim[N],no[N];
int in2,dfn2[N],lg[N<<1]; pair<int,int> st[D][N<<1];
void dfs0(int u){
    for(int v:e[u])if(to[v]^to[pre[u]])
        dep[to[v]]=dep[u]+we[v],pre[to[v]]=v^1,dfs0(to[v]);
}
void dfs1(int u){
    no[dfn[u]=in++]=u,st[0][dfn2[u]=in2++]=mp(dep[u],u);
    for(int v:e[u])if(to[v]^pre[u])
        dep[to[v]]=dep[pre[to[v]]=u]+we[v],dfs1(to[v]),
            st[0][in2++]=mp(dep[u],u);
    lim[u]=in;
}
void linit(){
    R(i,D-1)R(u,in2-(2<<i)+1)
        st[i+1][u]=min(st[i][u],st[i][u+(1<<i)]);
    R(i,in2+1)if(i>1) lg[i]=lg[i>>1]+1;
}
int lca(int u,int v){
    u=dfn2[u],v=dfn2[v];
    if(u>v) swap(u,v); v++; int i=lg[v-u];
    return min(st[i][u],st[i][v-(1<<i)]).y;
}

//SegmentTree
const int sN=N<<2;
#define mid ((l+r)>>1)
int mx[sN],tag[sN],anc[sN];
void pushup(int u){
    if(mx[u*2+1]>mx[u*2+2]) mx[u]=mx[u*2+1],anc[u]=anc[u*2+1];
    else if(mx[u*2+2]>mx[u*2+1]) mx[u]=mx[u*2+2],anc[u]=anc[u*2+2];
    else mx[u]=mx[u*2+1],anc[u]=lca(anc[u*2+1],anc[u*2+2]);
}
void pushtag(int u,int v){tag[u]+=v,mx[u]+=v;}
void pushdown(int u){tag[u]&&(pushtag(u*2+1,tag[u]),
    pushtag(u*2+2,tag[u]),tag[u]=0);}
void sinit(int u=0,int l=0,int r=n){
    if(r-l==1) return mx[u]=imon[no[l]]?dep[no[l]]:-iinf,anc[u]=no[l],void();
    sinit(u*2+1,l,mid),sinit(u*2+2,mid,r),pushup(u);
}
void fixr(int x,int y,int v,int u=0,int l=0,int r=n){
    if(r<=x||y<=l) return; if(x<=l&&r<=y) return pushtag(u,v);
    pushdown(u),fixr(x,y,v,u*2+1,l,mid),fixr(x,y,v,u*2+2,mid,r),pushup(u);
}
void print(int u=0,int l=0,int r=n){
    if(r-l==1) return void(cout<<"["<<l<<"]:"<<mx[u]<<" ");
    pushdown(u),print(u*2+1,l,mid),print(u*2+2,mid,r);
}
#undef mid

//Tree_1
int mk[N];
void dfs2(int u){
    if(imon[u]) mk[u]++,mk[anc[0]]++,mk[rt]--;
    for(int v:e[u])if(to[v]^pre[u]){
        fixr(0,n,we[v]),fixr(dfn[to[v]],lim[to[v]],-2*we[v]);
        dfs2(to[v]),fixr(0,n,-we[v]),fixr(dfn[to[v]],lim[to[v]],2*we[v]);
    }
}
void dfs3(int u){
    for(int v:e[u])if(to[v]^pre[u]) dfs3(to[v]),mk[u]+=mk[to[v]];
}

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    R(i,m) cin>>mon[i],--mon[i],imon[mon[i]]=true;
    R(i,n-1){int u,v,w; cin>>u>>v>>w,--u,--v,adde(u,v,w);}
    R(u,n) sort(e[u].bg,e[u].ed);
    int s=-1,t=-1,now=0;
    R(u,n) pre[u]=-1; dep[mon[0]]=0,dfs0(mon[0]);
    R(i,m)if(!~s||dep[mon[i]]>dep[s]) s=mon[i];
    R(u,n) pre[u]=-1; dep[s]=0,dfs0(s);
    R(i,m)if(!~t||dep[mon[i]]>dep[t]) t=mon[i];
    for(int u=t;u^s;u=to[pre[u]]){
        if(now>=dep[t]/2){rt=u;break;}
        now+=we[pre[u]];
    }
    if(!~rt) rt=s;
    R(u,n) pre[u]=-1;
    dep[rt]=0,dfs1(rt),linit(),sinit(),dfs2(rt),dfs3(rt);
    int mx=-1,cnt=0;
    R(u,n)if(!imon[u]){
        if(mk[u]>mx) mx=mk[u],cnt=1;
        else if(mk[u]==mx) cnt++; 
    }
    cout<<mx<<" "<<cnt<<'\n';
    return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：panyf (赞：5)

树形 dp + 树上差分。

枚举摧毁的城镇不方便处理，考虑枚举修道院。

设以修道院 $x$ 为根，所有距离 $x$ 最远的修道院的 lca 为 $y$。$x$ 的朝圣者不高兴当且仅当 $y$ 到 $x$ 的路径上有城镇被摧毁。

先一遍 dfs 预处理 $f_{i,x}$ ($0<=i<=2$) 表示以 $1$ 为根，每个点向下的最长链，次长链，第三长链；$g_{i,x}$ 表示 $f_{i,x}$ 对应的 $y$；$h_{i,x}$ 表示 $g_{i,x}$ 位于点 $x$ 的儿子 $h_{i,x}$ 的子树中；$p_x$ 表示 $x$ 子树内距离 $x$ 最远的修道院的 lca。

若点 $x$ 的子树内和子树外都有距离 $x$ 最远的修道院，则点 $x$ 不可能被破坏。

若距离 $x$ 最远的修道院在子树内，则 $y=p_x$。

若在子树外，在第二遍 dfs 的过程中维护三个变量 $u$,$v$,$w$ 分别表示当前距离最远的修道院的 lca(以 $x$ 为根)，$x$ 和 $u$ 的 lca(以 $1$ 为根)，以及最远的距离，则 $y=u$。维护 $v$ 是为了避免倍增求 lca。

接下来，问题转化为给定一棵树，每次对一条链的点点权 +1 ，最后询问所有点的点权。树上差分打 tag，最后再 dfs 一遍即可。

时间复杂度 $O(n)$ 。

具体 dp 转移方程和实现细节见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+3,M=2e5+3;
bool b[N];
int he[N],to[M],len[M],ne[M],f[3][N],g[3][N],h[2][N],p[N],fa[N],s[N];
void pre(int x,int y){
	if(b[x])f[0][x]=0,g[0][x]=x;
	for(int i=he[x],j,k,l;i;i=ne[i])if((j=to[i])!=y){
		fa[j]=x,pre(j,x),k=f[0][j]+len[i],l=p[j];
		if(k>f[0][x])f[2][x]=f[1][x],f[1][x]=f[0][x],f[0][x]=k,g[2][x]=g[1][x],g[1][x]=g[0][x],g[0][x]=l,h[1][x]=h[0][x],h[0][x]=j;
		else if(k>f[1][x])f[2][x]=f[1][x],f[1][x]=k,g[2][x]=g[1][x],g[1][x]=l,h[1][x]=j;
		else if(k>f[2][x])f[2][x]=k,g[2][x]=l;
	}
	p[x]=f[0][x]==f[1][x]?x:g[0][x];//若最长链和次长链一样长，则lca为x，否则 lca 为原来的 lca
}
void dp(int x,int u,int v,int w){
	if(b[x])if(f[0][x]>w)++s[p[x]],--s[fa[x]];else if(f[0][x]<w)++s[u],++s[x],--s[v],--s[fa[v]];//树上差分打 tag
	for(int i=he[x],j,k,l;i;i=ne[i])if((j=to[i])!=fa[x]){
		if(j==h[0][x])k=f[1][x],l=f[1][x]==f[2][x]?x:g[1][x];
		else if(j==h[1][x])k=f[0][x],l=f[0][x]==f[2][x]?x:g[0][x];
		else k=f[0][x],l=p[x];//k,l 分别表示点x向下不经过j的最长链长度和 lca
		if(k>w)dp(j,l,x,k+len[i]);
		else if(k==w)dp(j,x,x,k+len[i]);//若 k 与 w 相等，则 lca 即为 x
		else dp(j,u,v,w+len[i]);
	}
}
void dfs(int x){for(int i=he[x],j;i;i=ne[i])if((j=to[i])!=fa[x])dfs(j),s[x]+=s[j];}
int main(){
	int n,m,i,j,k,l,t=0;
	scanf("%d%d",&n,&m),memset(f,-9,sizeof(f));//注意初值赋 -inf
	for(i=1;i<=m;++i)scanf("%d",&j),b[j]=1;
	for(i=1;i<n;++i){
		scanf("%d%d%d",&j,&k,&l);
		ne[++t]=he[j],to[t]=k,len[t]=l,he[j]=t;
		ne[++t]=he[k],to[t]=j,len[t]=l,he[k]=t;
	}
	pre(1,0),dp(1,0,0,-1e9),dfs(1);
	for(i=1,j=k=0;i<=n;++i)if(!b[i])if(s[i]>j)j=s[i],k=1;else if(s[i]==j)++k;
	printf("%d %d\n",j,k);
	return 0;
}
```


---

## 作者：forgotmyhandle (赞：2)

[原题传送门](http://codeforces.com/problemset/problem/348/E)

[你谷传送门](https://www.luogu.com.cn/problem/CF348E)

直径做法没看懂，所以来篇树形 dp 的题解。

## 分析
约定：钦定 $1$ 为根。下称修道院所在点为黑点，城镇所在点为白点。记 $F(x)$ 为 $x$ 的父亲。

对于每个黑点 $x$，我们可以求出将哪些白点删去会使得其要求无法达成。显然，删去以 $x$ 为根时 到 $x$ 所有距离最远的点的 LCA 与 $x$ 的路径上的点一定会使 $x$ 的要求无法达成。于是，我们可以求出以 $x$ 为起点的最长链，以及**以 $x$ 为根时**所有到 $x$ 距离最远点的 LCA。

以下暂时不考虑点的黑白。

以一个点为起点的链可以分为两种：终点在其子树内的，和终点在其子树外的。我们将两种情况分开计算。即，算出以该点为起点，终点在其子树内的最长链及 LCA 和终点在其子树外的最长链和 LCA。子树内的问题是平凡的，只需要记录最长链和次长链及其出处即可。问题主要在于终点在其子树外的最长链。

显然，对于每个点 $x$，其子树外的点有两种。一种在 $F(x)$ 的子树内，一种在 $F(x)$ 的子树外。于是最长链也分为两种：终点在 $F(x)$ 子树外的，和终点在 $F(x)$ 子树内而在 $x$ 子树外的。于是我们可以 dfs。过程中维护当前点 $x$ 到其子树外的点的最长链与其（以 $x$ 为根时的） LCA。接下来我们要将这两个信息转移到其某个儿子 $v$。

设 $x$ 子树内不经过 $v$ 的最长链的长度为 $a$，$x$ 到其子树外点的最长链长度为 $len$。

1. $len > a$：显然，$v$ 到其子树外的最长链就是 $x$ 到其子树外的最长链加上边 $(x, v)$，而 LCA 不变。

2. $len  = a$：此时最长链有两条，它们交于 $x$。所以此时 LCA 变为 $x$，而最长链与情况 $1$ 相同。

3. $len < a$：此时我们并不知道最长链有几条，因为 $x$ 到其子树内不经过 $v$ 的最长链可以有多条。于是再记录 $x$ 到其子树内的第三长链，这样就一定可以知道 $x$ 到其子树内不经过 $v$ 的次长链。若次长链与最长链相等，则 LCA 也为 $x$。否则设最长链位于 $x$ 的儿子 $y$ 的子树中，则 LCA 为 $y$ 到其子树内所有最远点的 LCA。

这样我们就求出了每个点 $x$ 子树内外的最长链及其 LCA。接下来比较两边的最长链。若两边相等，则 $x$ 的要求不可能不满足。否则将 $x$ 到较长链所在侧的 LCA 的路径都加上 $1$，以说明这些点可以使 $x$ 的要求不被满足。这可以树上差分。于是就 ok 了。

总的来说，我们要求出 $f[i][0 / 1 / 2]$ 表示 $i$ 到其子树内最长、次长、第三长链的长度，$g[i][0 / 1 / 2]$ 表示 $f[i][0 / 1 / 2]$ 来自 $i$ 的哪一棵子树。$p[x]$ 表示 $x$ 到其子树内所有最远点的 LCA。这些都可以一遍 dfs 完成。

考虑黑点也很简单，只需要将 $f$ 和 $g$ 的定义变成到子树内黑点的三条链的长度和出处，$p$ 变成子树内最远黑点的 LCA。第二次 dfs 中 $len$ 变成到子树外最远黑点的距离，LCA 也类似。于是就真 ok 了。

## 代码
由于写了树剖求 LCA，所以看起来可能非常长。

```cpp
#include <iostream>
using namespace std;
int n, m;
int head[100005], nxt[200005], to[200005], ew[200005], ecnt;
void add(int u, int v, int ww) { to[++ecnt] = v, nxt[ecnt] = head[u], head[u] = ecnt, ew[ecnt] = ww; }
int f[100005][3], g[100005][3], p[100005];
int F[100005];
int dfn[100005];
int _dfn[100005], ncnt;
// 这个 namespace 可以略过不看
namespace LCA {
    int top[100005], son[100005], dep[100005], sz[100005], f[100005];
    void dfs1(int x, int fa, int d) {
        f[x] = fa;
        sz[x] = 1;
        dep[x] = d;
        for (int i = head[x]; i; i = nxt[i]) {
            int v = to[i];
            if (v != fa) {
                dfs1(v, x, d + 1);
                sz[x] += sz[v];
                if (sz[v] > sz[son[x]]) 
                    son[x] = v;
            }
        }
    }
    void dfs2(int x, int t) {
        top[x] = t;
        if (!son[x]) 
            return;
        dfs2(son[x], t);
        for (int i = head[x]; i; i = nxt[i]) {
            int v = to[i];
            if (v != son[x] && v != f[x]) 
                dfs2(v, v);
        }
    }
    void ini() { dfs1(1, 0, 1), dfs2(1, 1); }
    int LCA(int x, int y) {
        while (top[x] ^ top[y]) (dep[top[x]] < dep[top[y]]) ? (y = f[top[y]]) : (x = f[top[x]]);
        return (dep[x] < dep[y] ? x : y);
    }
}
// 以上 namespace 可以略过不看
bool b[100005];
int S[100005];
int sb[100005];
void dfs1(int x, int fa) {
    _dfn[dfn[x] = ++ncnt] = x;
    F[x] = fa;
    sb[x] = b[x];
    for (int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) {
            dfs1(v, x);
            sb[x] += sb[v];
            if (sb[v]) {
                int k = f[v][0] + ew[i];
                if (k > f[x][0]) 
                    f[x][2] = f[x][1], f[x][1] = f[x][0], f[x][0] = k, g[x][2] = g[x][1], g[x][1] = g[x][0], g[x][0] = v;
                else if (k > f[x][1]) 
                    f[x][2] = f[x][1], f[x][1] = k, g[x][2] = g[x][1], g[x][1] = v;
                else if (k > f[x][2]) 
                    f[x][2] = k, g[x][2] = v;
            }
        }
    }
    p[x] = ((f[x][0] == f[x][1]) ? x : p[g[x][0]]);
}
void dfs2(int x, int fa, int len, int lca) {
    if (m - sb[x] == 0) // 如果子树外没有黑点！直接清掉，因为下面传递信息时没考虑黑点
        len = lca = 0;
    if (b[x]) {
        if (len > f[x][0]) {
            int tmp = LCA::LCA(x, lca);
            S[x]++, S[lca]++, S[tmp]--, S[F[tmp]]--;
        } else if (len < f[x][0]) 
            S[F[x]]--, S[p[x]]++;
        // 两边相等时这个黑点一定不可能被隔断，所以不用加
    }
    for (int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) { // 这里先不考虑黑点
            int a, b, c;
            v == g[x][0] ? (a = f[x][1], b = f[x][2]) : (v == g[x][1] ? (a = f[x][0], b = f[x][2]) : (a = f[x][0], b = f[x][1]));
            c = g[x][v == g[x][0]];
            if (len > a) 
                dfs2(v, x, len + ew[i], lca);
            else if (len == a) 
                dfs2(v, x, len + ew[i], x);
            else if (len < a) 
                dfs2(v, x, a + ew[i], a == b ? x : p[c]);
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1, x; i <= m; i++) cin >> x, b[x] = 1;
    for (int i = 1, u, v, ww; i < n; i++) {
        cin >> u >> v >> ww;
        add(u, v, ww);
        add(v, u, ww);
    }
    LCA::ini();
    dfs1(1, 0);
    dfs2(1, 0, 0, 0);
    int mxc = 0, cnt = 0; // 答案和答案个数
    for (int i = n; i; i--) { // dfs 序枚举代替 dfs 做子树和
        int x = _dfn[i];
        S[F[x]] += S[x];
        if (!b[x]) {
            S[x] > mxc ? (mxc = S[x], cnt = 0) : 0;
            cnt += (mxc == S[x]);
        }
    }
    cout << mxc << " " << cnt << "\n";
    return 0;
}
```

---

## 作者：lfxxx (赞：1)

考虑对于一个点 $u$，假设距离其距离最远的点构成的点集为 $S$，你发现我们并不需要求出这个点集，只需要求出点集中的点到 $u$ 的路径交即可。又因为路径交的一个端点一定是 $u$，所以求解另一个端点即可。

而你发现树形 dp 合并两个儿子的 dp 数组时，其路径交的另一个端点一定是其父亲，所以考虑设计状态 $dp_i$ 表示点 $i$ 到子树内最长链距离与所有最长链交的另一个端点，然后按照上面的推论从下往上 dp 和从上往下换根 dp 时都可以快速合并状态，求解所有 dp 数组后再用一次树上差分求出割去每个点的贡献即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
struct info{
	int u,dis;
	info(int U=0,int Dis=-1e18){
		u=U,dis=Dis;
	}
	info operator+(const int &x)const{
		return info(u,dis==-1e18?dis:dis+x);
	}
}dp[maxn],g[maxn];
info merge(info x,info y,int u){
	return info((x.dis!=y.dis?(x.dis>y.dis?x.u:y.u):u),max(x.dis,y.dis));
}
int vis[maxn];
int tr[maxn],n,m;
vector< pair<int,int> > E[maxn];
int dep[maxn];
int sz[maxn],son[maxn],top[maxn];
int father[maxn];
void dfs1(int u,int fa){
	sz[u]=1;
	dep[u]=dep[fa]+1;
	father[u]=fa;
	for(pair<int,int> nxt:E[u]){
		int v=nxt.first,w=nxt.second;
		if(v!=fa){
			dfs1(v,u);
			sz[u]+=sz[v];
			son[u]=(sz[v]>sz[son[u]]?v:son[u]);
		}
	}
}
void dfs2(int u,int fa,int tp){
	top[u]=tp;
	if(son[u]!=0) dfs2(son[u],u,tp);
	for(pair<int,int> nxt:E[u]){
		int v=nxt.first,w=nxt.second;
		if(v!=fa&&v!=son[u]){
			dfs2(v,u,v);
		}
	}
}
int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=father[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	return v;
}
void DP1(int u,int fa){
	dp[u]=info(u,vis[u]==1?0:-1e18);
	for(pair<int,int> nxt:E[u]){
		int v=nxt.first,w=nxt.second;
		if(v!=fa){
			DP1(v,u);
			dp[u]=merge(dp[u],dp[v]+w,u);
		}
	}
}
void DP2(int u,int fa){
	info pre=info(0,-1e18);
	for(pair<int,int> nxt:E[u]){
		int v=nxt.first,w=nxt.second;
		if(v!=fa){
			g[v]=merge(g[v],pre+w,u);
			pre=merge(pre,dp[v]+w,u);
		}
	}
	info suf=info(0,-1e18);
	reverse(E[u].begin(),E[u].end());
	for(pair<int,int> nxt:E[u]){
		int v=nxt.first,w=nxt.second;
		if(v!=fa){
			g[v]=merge(g[v],suf+w,u);
			suf=merge(suf,dp[v]+w,u);
		}
	}
	for(pair<int,int> nxt:E[u]){
		int v=nxt.first,w=nxt.second;
		if(v!=fa){
			g[v]=merge(g[v],g[u]+w,u);
			g[v]=merge(g[v],info(v,vis[v]==1?0:-1e18),v);
			DP2(v,u);
		}
	}
}
void DP3(int u,int fa){
	for(pair<int,int> nxt:E[u]){
		int v=nxt.first,w=nxt.second;
		if(v!=fa){
			DP3(v,u);
			tr[u]+=tr[v];
		}
	}
}
void add(int u,int v){
	tr[u]++,tr[v]++;
	tr[LCA(u,v)]--;
	tr[father[LCA(u,v)]]--;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) dp[i]=info(),g[i]=info();
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		vis[x]=1;
	}
	for(int i=1;i<n;i++){
		int u,v,c;
		cin>>u>>v>>c;
		E[u].push_back(make_pair(v,c));
		E[v].push_back(make_pair(u,c));
	}
	dfs1(1,0);
	dfs2(1,0,1);
	DP1(1,0);
	g[1]=info(1,vis[1]==1?0:-1e18);
	DP2(1,0);
	for(int i=1;i<=n;i++){
		if(vis[i]==1){
			info end=merge(dp[i],g[i],i);
			add(i,end.u);	
		}
	}
	DP3(1,0);
	int mx=0;
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(vis[i]==0) mx=max(mx,tr[i]);
	}
	for(int i=1;i<=n;i++)
		if(vis[i]==0&&tr[i]==mx) cnt++;
	cout<<mx<<' '<<cnt<<'\n';
	return 0;
}
```

---

## 作者：SentoAyaka (赞：1)

来一个大力维护的做法。

考虑 dfs 过程中用线段树维护出其到每个点距离，这可以通过在 $dfn$ 序上区间加减实现。

我们找到所有距离最大且为修道院的点，能对当前点 $x$ 造成影响都就是这些点到 $x$ 的路径交。

将其分成 $x$ 子树内和子树外考虑，注意到子树内外不能同时有，否则路径交为空。

- 点都在子树内：根据经典结论：点集的 $LCA$ 就是 $dfn$ 序上最小最小值对应点的 $LCA$。那么我们维护距离最大点的 $dfn$ 序最大最小值即可。
- 点都在子树外：还是取 $dfn$ 序列最大最小点 $a,b$
  - 如果 $LCA(LCA(a,b),x)=x$，也就是说其与 $x$ 的 $LCA$ 都在一个点上，那和第一种情况是一样的。
  - 否则考虑要找 $LCA(p,x)$ 最深的点，其一定是 $dfn_p<dfn_x$ 的最大值或 $dfn_p>dfn_x$ 的最小值。使用线段树二分可以轻松解决。

于是我们求出了所有贡献路径，树上差分即可。复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define db double
#define int ll
#define ll long long
#define ull unsigned long long
#define pb emplace_back
#define MP make_pair
#define pii pair<int, int>
#define vec vector<int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define CLK (double)clock()/(double)CLOCKS_PER_SEC
using namespace std;
mt19937 rnd(time(0));
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline void write(int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const int N=1e5+5,inf=1e18;
int n,m,mk[N],d[N],mn[22][N],L[N],R[N],dfn[N],Dfn,pos[N],dis[N];
int v[N],dif[N],ans,res;
vector<pii> G[N];
void chkmin(int &x,int y){x=min(x,y);}
void chkmax(int &x,int y){x=max(x,y);}
int get(int x,int y){return dfn[x]<dfn[y]?x:y;}
void dfs(int x,int fa){
    d[x]=d[fa]+1,mn[0][L[x]=dfn[x]=++Dfn]=fa,pos[Dfn]=x;
    for(auto [y,w]:G[x])if(y!=fa)dis[y]=dis[x]+w,dfs(y,x);R[x]=Dfn;
}
void Init(){
    dfs(1,0);
    for(int i=1;i<=20;i++)for(int j=1;j+(1<<i)-1<=n;j++)
        mn[i][j]=get(mn[i-1][j],mn[i-1][j+(1<<i-1)]);
}
int LCA(int x,int y){
    if(!x||!y)return 0;
    if(x==y)return x;
    if((x=dfn[x])>(y=dfn[y]))swap(x,y);
    int d=__lg(y-x++);
    return get(mn[d][x],mn[d][y-(1<<d)+1]);
}
int Dis(int x,int y){return dis[x]+dis[y]-2*dis[LCA(x,y)];}
struct node{
    int v,mn,mx;
    node(int _v=-inf,int _mn=inf,int _mx=-inf):v(_v),mn(_mn),mx(_mx){}
    friend node operator +(node a,node b){
        node c;c.v=max(a.v,b.v);
        if(a.v==c.v)chkmin(c.mn,a.mn),chkmax(c.mx,a.mx);
        if(b.v==c.v)chkmin(c.mn,b.mn),chkmax(c.mx,b.mx);
        return c;
    }
}t[N<<2];
int tag[N<<2];
void pushup(int k){t[k]=t[ls]+t[rs];}
void build(int k,int lt,int rt){
    if(lt==rt)return t[k]=mk[pos[lt]]?(node){v[pos[lt]],lt,lt}:(node){-inf,inf,-inf},void();
    int mid=lt+rt>>1;
    build(ls,lt,mid),build(rs,mid+1,rt);
    pushup(k);
}
void f(int k,int val){t[k].v+=val,tag[k]+=val;}
void pushdown(int k){
    if(tag[k])f(ls,tag[k]),f(rs,tag[k]),tag[k]=0;
}
void modify(int k,int lt,int rt,int qx,int qy,int val){
    if(qx>qy||qx>rt||qy<lt)return ;
    if(qx<=lt&&rt<=qy)return f(k,val),void();
    int mid=lt+rt>>1;pushdown(k);
    modify(ls,lt,mid,qx,qy,val),modify(rs,mid+1,rt,qx,qy,val);
    pushup(k);
}
node query(int k,int lt,int rt,int qx,int qy){
    if(qx<=lt&&rt<=qy)return t[k];
    int mid=lt+rt>>1;pushdown(k);
    if(qx>mid)return query(rs,mid+1,rt,qx,qy);
    if(qy<=mid)return query(ls,lt,mid,qx,qy);
    return query(ls,lt,mid,qx,qy)+query(rs,mid+1,rt,qx,qy);
}
void Work(int x,int y){
    int tmp=LCA(x,y);
    dif[x]++,dif[y]++,dif[tmp]--,dif[mn[0][dfn[tmp]]]--;
}
int Find1(int k,int lt,int rt,int qx,int qy,int val){
    if(lt==rt)return t[k].v==val?lt:0;
    int mid=lt+rt>>1;pushdown(k);
    if(qx<=lt&&rt<=qy){
        if(t[ls].v!=val)return Find1(rs,mid+1,rt,qx,qy,val);
        else return Find1(ls,lt,mid,qx,qy,val);
    }
    if(qx>mid)return Find1(rs,mid+1,rt,qx,qy,val);
    if(qy<=mid)return Find1(ls,lt,mid,qx,qy,val);
    int res=Find1(ls,lt,mid,qx,qy,val);
    if(res)return res;
    else return Find1(rs,mid+1,rt,qx,qy,val);
}
int Find2(int k,int lt,int rt,int qx,int qy,int val){
    if(lt==rt)return t[k].v==val?lt:0;
    int mid=lt+rt>>1;pushdown(k);
    if(qx<=lt&&rt<=qy){
        if(t[rs].v!=val)return Find2(ls,lt,mid,qx,qy,val);
        else return Find2(rs,mid+1,rt,qx,qy,val);
    }
    if(qx>mid)return Find2(rs,mid+1,rt,qx,qy,val);
    if(qy<=mid)return Find2(ls,lt,mid,qx,qy,val);
    int res=Find2(rs,mid+1,rt,qx,qy,val);
    if(res)return res;
    else return Find2(ls,lt,mid,qx,qy,val);
}
void Do(int x){
    if(!mk[x])return ;
    node glo=t[1];if(glo.v==0)return ;
    node tre=query(1,1,n,L[x],R[x]);
    int pl=pos[glo.mn],pr=pos[glo.mx];
    if(tre.v==glo.v){
        if(glo.mn<L[x]||glo.mx>R[x])return ;
        int p=LCA(pl,pr);Work(x,p);
    }
    else {
        int p=LCA(pl,pr),a=LCA(pl,x),b=LCA(pr,x);
        if(a==b)Work(x,p);
        else {
            int la=Find2(1,1,n,1,L[x]-1,glo.v),lb=Find1(1,1,n,R[x]+1,n,glo.v);
            la=LCA(x,pos[la]),lb=LCA(x,pos[lb]);
            if(!la)Work(x,lb);else if(!lb)Work(x,la);
            else Work(x,d[la]>d[lb]?la:lb);
        }
    }
}
void Solve(int x,int fa){
    Do(x);
    for(auto [y,w]:G[x])if(y!=fa){
        modify(1,1,n,1,L[y]-1,w),modify(1,1,n,R[y]+1,n,w),modify(1,1,n,L[y],R[y],-w);
        Solve(y,x);
        modify(1,1,n,1,L[y]-1,-w),modify(1,1,n,R[y]+1,n,-w),modify(1,1,n,L[y],R[y],w);
    }
}
void find(int x,int fa){
    for(auto [y,w]:G[x])if(y!=fa)find(y,x),dif[x]+=dif[y];
    if(mk[x])return ;
    if(dif[x]>ans)ans=dif[x],res=1;
    else if(dif[x]==ans)res++;
}
void MAIN(){
    n=read(),m=read();
    for(int i=1;i<=m;i++)mk[read()]=1;
    for(int i=1,x,y,w;i<n;i++)x=read(),y=read(),w=read(),G[x].pb(y,w),G[y].pb(x,w);
    Init();
    for(int i=1;i<=n;i++)v[i]=Dis(1,i);
    build(1,1,n);Solve(1,0);find(1,0);
    cout<<ans<<' '<<res;
}
signed main(){
    // freopen("read.in","r",stdin);
	// freopen("write.out","w",stdout);
    int T=1;while(T--)MAIN();
//  printf("\nTIME:%lf\n",(double)clock()/CLOCKS_PER_SEC);
    return 0;
}
```


---

## 作者：phil071128 (赞：0)

## 简化题意

> 给定一棵已经确定黑白染色的树，边有边权，其中有 $m$ 个黑点，其它都是白点。
>
> 对于一个黑点，我们定义他的好朋友是离他最远的黑点。显然，一个黑点可能有多个好朋友。
>
> 现在要删除一个白点，使得删除后，不能到达**任意**一个好朋友的黑点数量尽可能多，求出这个数量的最大值，以及多少个白点删掉后满足这个最大值。

## Solution
看到最远点想到树的直径两端点，但是显然此时的树并非原树，我们只会用到黑点，因此求直径时，实际上这棵树是只有黑点的虚树。我们两遍 `dfs` 跑出树的直径 $len$ 。

树的直径的长度是抽象的，但是直径两端点却是不唯一的，一个常见的技巧是树的直径的中点是唯一的（NOIP2007 树网的核），注意这里的中点是 离 $\frac{len}{2}$ 最近的点，如果是两个点则任取一个。这里的中点有可能是白点。

找到中点后，我们把中点提拉成根，变成一棵有根树，此时任何一个黑点想要到达他的好朋友，一定要经过根。

然后我们枚举要删除的白点 $u$ ，白点子树的所有黑点肯定都算入答案，另外我们要分类讨论。其依据是，整个树的直径，要么是一条从根往下延伸的最长链和另一条次长链，要么是两条最长链。（实际情况可能是若干条）

1. 这棵树由一条最长链和若干次长链组成，且 $u$ 在最长链上：

   此时，这条最长链上的，非 $u$ 子树的黑点，仍然可以到达他们的好朋友，即次长链的最深黑点。而除了他们，其他黑点都到达不了他们的好朋友，即最长链的最深黑点。

2. 这棵树由一条最长链和若干次长链组成，且 $u$ 在次长链上：

   此时，这条次长链上的，非 $u$ 子树的黑点，仍然可以到达他们的好朋友，即最长链的最深黑点。但是，唯一的最长链上的黑点都到达不了他们的好朋友，即次长链的最深黑点。

3. 这棵树由且仅由两条最长链组成，且 $u$ 在最长链上：

   此时， $u$ 这条最长链上的，非 $u$ 子树的黑点，仍然可以到达他们的好朋友，即另一条最长链的最深黑点。但是，另一条最长链的所有点都到达不了他们的好朋友，即 $u$ 这条最长链的最深黑点。

   当然，如果有多条最长链则不会出现此情况。

对于上述信息，笔者的处理方式是若干遍 `dfs` 分别处理出 在以直径中点为根的树中，$dp_i$ 表示 $i$ 子树的最深黑点的深度，$anc_i$ 表示 $i$ 的祖先是根的哪个儿子，最长链的数量 $cnt$。这样如果 $dp_u=dp_{root}$ ，则说明 $u$ 在最长链；若 $dp_u+dp_{root}=len$ 则说明 $u$ 在次长链。 

[评测记录](https://codeforces.com/contest/348/submission/227608771)

---

