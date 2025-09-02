# Passable Paths (easy version)

## 题目描述

给定一棵树，问是否能通过一条简单路径（即在树上找一条路径且不重复走一条边），使其经过给定点集中的所有点。

## 说明/提示

对于 $100\%$ 的数据：

+ $1 \le n \le 2 \cdot 10^5$，$ 1 \le u, v \le n$，$ u \ne v$；

+ $ 1 \le q \le 5$，$ 1 \le k \le n$，$ 1 \le p_i \le n$，所有 $k$ 的和不超过 $2\cdot10^5$。

## 样例 #1

### 输入

```
5
1 2
2 3
2 4
4 5
5
3
3 2 5
5
1 2 3 4 5
2
1 4
3
1 3 5
3
1 5 4```

### 输出

```
YES
NO
YES
NO
YES```

## 样例 #2

### 输入

```
5
1 2
3 2
2 4
5 2
4
2
3 1
3
3 4 5
3
2 3 5
1
1```

### 输出

```
YES
NO
YES
YES```

# 题解

## 作者：王熙文 (赞：2)

## 题意

给一棵树，节点个数为 $n$（$1 \le n \le 2 \times 10^5$），有 $q$（$1 \le q \le 5$）次询问，每一次给出一个节点集合（满足节点集合大小总和 $\le 2 \times 10^5$），判断是否有一条路径，经过了集合里所有的节点（可以经过非集合里的节点）。

## 思路

可以发现，如果存在满足条件的路径，则一定有一条满足条件的路径的起点为最深的点（记为 $ax1$）。因为一条满足条件的路径必然经过 $ax1$，而如果这条路径继续往下伸展，下面没有集合里的点了（因为 $ax1$ 最深），则可以砍掉下面的路径，变成起点为 $ax1$ 的路径。

设集合中不是 $ax1$ 的祖先中的点最深的点 $ax2$。同理可得：如果存在满足条件的路径，则一定有一条满足条件的路径的终点为 $ax2$。

那么我们求出来 $ax1,ax2$ 后，只需要判断 $ax1 \to ax2$ 这条路径是否覆盖集合中所有点即可。

一些细节的实现：

* 如果不存在 $ax2$，则集合中所有点均为 $ax1$ 的祖先或者其自己，$ax1 \to root$ 这条路径即满足了，输出 `YES`。

* 判断一个点是否为另一个点的祖先时，可以求出它们的深度之差，然后通过倍增将更深的点跳上去，看是否是一个点。

* 因为询问次数少，所以判断 $ax1 \to ax2$ 是否覆盖集合中所有点时可以直接暴力跳。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,q;

int tot=0,var[400010],nxt[400010],head[200010];

void add(int u,int v)
{
	var[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}

int dep[200010],fa[200010][20];

void dfs(int u,int fat)
{
	dep[u]=dep[fat]+1;
	fa[u][0]=fat;
	for(int i=1; i<=19; ++i) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=head[u]; i; i=nxt[i])
	{
		int v=var[i];
		if(v==fat) continue;
		dfs(v,u);
	}
}

int qs[200010];

bool cmp(int x,int y)
{
	return dep[x]>dep[y];
}

bool is_fa(int u,int v) // u 是否是 v 的祖先
{
	int cj=dep[v]-dep[u];
	for(int i=0; i<=19; ++i)
	{
		if(cj>>i&1) v=fa[v][i];
	}
	return u==v;
}

bool vis[200010];

int main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	int u,v,k;
	cin>>n;
	for(int i=1; i<=n-1; ++i)
	{
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs(1,0);
	cin>>q;
	while(q--)
	{
		cin>>k;
		for(int i=1; i<=k; ++i)
		{
			cin>>qs[i];
		}
		sort(qs+1,qs+k+1,cmp);
		int ax1=qs[1],ax2=0;
		for(int i=2; i<k; ++i)
		{
			if(!is_fa(qs[i],ax1))
			{
				ax2=qs[i];
				break;
			}
		}
		if(!ax2)
		{
			puts("Yes");
			continue;
		}
		memset(vis,0,sizeof(vis));
		int nowx=ax1,nowy=ax2;
		while(nowx!=nowy)
		{
			if(dep[nowx]<dep[nowy]) swap(nowx,nowy);
			vis[nowx]=1,nowx=fa[nowx][0];
		}
		vis[nowx]=1;
		bool flag=1;
		for(int i=1; i<=k; ++i)
		{
			if(!vis[qs[i]])
			{
				flag=0;
				break;
			}
		}
		puts(flag?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：qwq___qaq (赞：2)

### Update

2022.7.13 加入了实现方法

拿到题目，因为要一次走完，所以所有的点在同一条链上。

看到 $q$ 很小，所以考虑 $O(qn)$ 的搜索。

注意不能从中间开始搜，所以考虑从深度最大的开始，因为它下面没有点，所以它一定是链的端点，然后就是一个普通的 `dfs`。

可以使用一个树形 dp 求出每个节点的深度，然后从深度最大的节点搜索，如果得到了一条链，就是 `YES`；否则就是 `NO`。

---

## 作者：TernaryTree (赞：1)

一眼虚树。$\Theta(k\log n)$ 建个虚树。判断度数都 $\le 2$ 就做完了。

总复杂度 $\Theta((n+\sum k)\log n)$。

```
bool solve() {
	sort(a.begin(), a.end(), [] (int x, int y) {
		return dfn[x] < dfn[y];
	});
	for (int i = 0; i < k - 1; i++) {
		b.push_back(a[i]);
		b.push_back(lca(a[i], a[i + 1]));
	}
	b.push_back(a[k - 1]);
	sort(b.begin(), b.end(), [] (int x, int y) {
		return dfn[x] < dfn[y];
	});
	int m = unique(b.begin(), b.end()) - b.begin();
	bool fl = true;
	for (int i = 0; i < m - 1; i++) {
		++deg[b[i + 1]], ++deg[lca(b[i], b[i + 1])];
		if (deg[b[i + 1]] >= 3) fl = false;
		if (deg[lca(b[i], b[i + 1])] >= 3) fl = false;
	}
	for (int i = 0; i < m - 1; i++) --deg[b[i + 1]], --deg[lca(b[i], b[i + 1])];
	return fl;
}
```

---

## 作者：qnqfff (赞：1)

思路：

如果存在答案,则深度最深的点一定为一个端点,另一个端点则为与该点距离最远的点,所以先找到两个端点,之后在判断其他点是否在两点的简单路径即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char ch=getchar();int s=0,f=1;
	while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
	if(ch=='-') ch=getchar(),f=-1;
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return f*s;
}
int n,q,a[200010],dep[200010],f[200010][21];
vector<int>e[200010];
void dfs(int now,int fa){
	dep[now]=dep[fa]+1;
	f[now][0]=fa;
	for(int i=0;i<e[now].size();i++)
		if(e[now][i]!=fa)
			dfs(e[now][i],now);
}
int lca(int x,int y){//倍增求lca
	if(dep[x]<dep[y])
		swap(x,y);
	for(int i=20;i>=0;i--)
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
	if(x==y)
		return x;
	for(int i=20;i>=0;i--)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0]; 
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0);
	for(int j=1;j<=20;j++)
		for(int i=1;i<=n;i++)
			f[i][j]=f[f[i][j-1]][j-1];
	q=read();
	while(q--){
		memset(a,0,sizeof(a));
		int m=read();
		for(int i=1;i<=m;i++)
			a[i]=read();
		int x=0,maxnx=-1e9,y=0,maxny=-1e9;
		for(int i=1;i<=m;i++)
			if(dep[a[i]]>maxnx) maxnx=dep[a[i]],x=a[i];//取深度最深的点
		for(int i=1;i<=m;i++)
			if(dep[x]+dep[a[i]]-2*dep[lca(x,a[i])]+1>maxny&&a[i]!=x) maxny=dep[x]+dep[a[i]]-2*dep[lca(x,a[i])]+1,y=a[i];//取离深度最深的点最远的点
		bool flag=0;
		for(int i=1;i<=m;i++){
			if(a[i]==x||a[i]==y||lca(x,y)==a[i]||(lca(lca(x,y),a[i])==lca(x,y)&&lca(a[i],x)==a[i])||(lca(lca(x,y),a[i])==lca(x,y)&&lca(a[i],y)==a[i]))//在两点路径上
				continue;
			flag=1;//不在
			break;
		}
		cout<<(flag?"NO":"YES")<<endl;
	}
}
```

---

## 作者：ZLCT (赞：0)

# CF1702G1 Passable Paths (easy version)
## 题目翻译
给定一棵 $n$ 个点的树，$q$ 次询问，每次给定 $k_i$ 个点，求是否能找到一条链把这 $k_i$ 个点全部覆盖。\
$q\le5$。
## 柿子挑软的捏
观察到 $q\le 5$，所以这告诉我们可以几乎忽略 $q$ 的复杂度，也就是问题转化为了如何求一次的答案。\
一种暴力的思路就是每次分别以这 $k_i$ 个点为起点跑一遍 dfs，若其中一个点出发可以一条链走完所有点，则说明可以，否则不行。\
但是这样时间复杂度最差为 $O(nk)$，假设 $k$ 足够大一定会 TLE。并且仔细思考一下会发现这条路径一定是唯一的，也就是说即使随机选择起点，一次的成功概率也只有 $\frac{2}{k}$，更何况若不存在还会跑满。
那么根据上面说的既然这条路径是唯一的，那么假设我们找到了这条路径的一个端点，那么只需要跑一遍就可以找到合法路径；反之若找不到一条合法路径，则说明肯定不存在一条合法路径。\
不难想到路径只有两种形态：
- 从某一节点到其祖先。
- 两个节点分别到它们最近公共祖先的路径并。

不难发现这两条路径都经过深度最小的点，但是在第二种路径中深度最小的点为一个中转点，无法从它开始 dfs。于是我们观察到这两种路径还都经过深度最大的点，而深度最大的点一定是路径的一个起点。\
于是我们就得到一种策略：从深度最大的点出发，能走到一条链把 $k_i$ 个点全部覆盖则说明可以，否则不行。\
那这个策略是对的吗？显然是对的，因为这两种路径的起点一定有一个是深度最大的点，所以从深度最大的点若都找不到合法路径，其他点更不可能。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+666;
int n,dep[N],a[N];
vector<int>G[N],vec;
int mind(int c1,int c2){
    return (dep[c1]>dep[c2]?c1:c2);
}
void build(int u,int fa){
    dep[u]=dep[fa]+1;
    for(int v:G[u]){
        if(v==fa)continue;
        build(v,u);
    }
}
int dfs(int u,int fa){
    int res=a[u];
    for(int v:G[u]){
        if(v==fa)continue;
        res=max(res,dfs(v,u)+a[u]);
    }
    return res;
}
signed main(){
    cin>>n;
    for(int i=1;i<n;++i){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    build(1,1);
    int Q;cin>>Q;
    while(Q--){
        int k;cin>>k;
        int st=0;
        vec.clear();
        for(int i=1;i<=k;++i){
            int x;cin>>x;
            vec.push_back(x);
            a[x]=1;
            st=mind(st,x);
        }
        if(dfs(st,st)==k){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
        for(int p:vec){
            a[p]=0;
        }
    }
}
```

---

## 作者：yingkeqian9217 (赞：0)

## 前言

如何评价我做 G1 结果做出来的解法 G2 也能过。。。

## 题目描述

给定一棵树，问是否能通过一条简单路径（即在树上找一条路径且不重复走一条边），使其经过给定点集中的所有点。

## 分析

显然要先转化为有根树，不妨以 $1$ 做根，然后遍历树。

可以发现，对于树上的一条简单路径，设其左右端点为 $x,y$，这两个端点的最近公共祖先为 $f$，则它肯定由 $p(x,f)$ 与 $p(f,y)$ 拼接而成，其中 $p$ 表示两点间的最短路径，此处的路径上的点都是深度递增的。不理解可以看图。

![](https://cdn.luogu.com.cn/upload/image_hosting/n5cn1sym.png)

那么，如何找到对应的 $x,y$ 呢？其实也不难，因为显然 $x,y$ 中有一个是整条链的深度最大的点，不妨设 $x$ 更深，那么我们只要在点集中找到除了 $x$ 的祖先以外的深度最大的点，它就是 $y$。我们可以将点集按深度从大到小排序，然后遍历即可。

显然如果不存在 $y$，也就是说它就是一条垂直的链，那么是合法的，特判输出。

而一个点想要在链上的充要条件它是 $x,y$ 中一个的祖先且深度 $\le f$ 的深度。后者我们只要限制深度最大的点，判断它是否满足即可。前者以及前文中提到的祖先判断，我们可以直接求两点的 lca 判断是否是它本身。

lca 可以用树剖实现，总时间复杂度 $O(n\log n)$。

## AC Code
```
#include<bits/stdc++.h>
#define maxn 1000001
using namespace std;
int n,m,cnt,q,a[maxn],sz[maxn],top[maxn],hson[maxn],dep[maxn],f[maxn];
int head[maxn];
bool vis[maxn];
struct edge{
	int nxt,to;
}e[maxn];
int cmp(int x,int y){return dep[x]>dep[y];}//深度从小到大排序
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int x,int fa,int _dep){
	int maxx=0;
	f[x]=fa;
	sz[x]=1;
	dep[x]=_dep;
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dfs(v,x,_dep+1);
			sz[x]+=sz[v];
			if(sz[v]>maxx)
			 maxx=sz[v],hson[x]=v;
		}
	}//记录深度和重儿子等信息
}
void dfss(int x,int fa){
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa&&!top[v]){
			if(hson[x]==v) top[v]=top[x];
			else top[v]=v;
			dfss(v,x);
		}
	}//树剖
}
int lca(int x,int y){
	if(!x||!y) return -1;//不知道有没有用的特判
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]) x=f[top[x]];
		else y=f[top[y]];
	}
	return (dep[x]>dep[y]?y:x);
}
void solve(){
	int x=1,y=0;
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d",&a[i]);
	if(m==2) return void(puts("YES"));//特判两点，必然成立
	sort(a+1,a+m+1,cmp);//排序
	for(int i=2;i<=m;i++)
	 if(lca(a[x],a[i])!=a[i]){
	 	y=i;//记录另一个端点
	 	break;
	 }
	if(!y) return void(puts("YES"));//特判
	if(dep[a[m]]<dep[lca(a[x],a[y])]) return void(puts("NO"));//特判最高点
	for(int i=1;i<=m;i++)
	 if(lca(a[i],a[x])!=a[i]&&lca(a[i],a[y])!=a[i])//是否为祖先
	  return void(puts("NO"));
	puts("YES");
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	cnt=0,dfs(1,0,1);
	top[1]=1,dfss(1,0);//树剖求解lca板子
	scanf("%d",&q);
	while(q--) solve();
	return 0;
}
```

---

