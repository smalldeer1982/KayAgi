# [USACO22DEC] Strongest Friendship Group G

## 题目描述

Farmer John 有 $N$ 头奶牛（$2 \le N \le 10^5$），编号为 $1\cdots N$。这些奶牛中有 $M(1 \le M \le 2\times 10^5)$ 对朋友。

一组奶牛被称为是「小团体」，如果该组中的每头奶牛都可以从该组中的每头其他奶牛出发通过完全位于该组内的一系列朋友关系到达（连接到组外奶牛的朋友关系无效）。小团体的「强度」是组内奶牛的最小组内朋友数乘以组内奶牛的数量（同样，注意连接到组外奶牛的朋友关系不计入此定义）。

求所有小团体的最大强度。 

## 说明/提示

### 样例 1 解释

可以观察到最大强度来自编号为 $1,2,3,4$ 的奶牛组。该组内奶牛的最小朋友数为 $3$，故答案为 $4 \times 3=12$。

### 测试点性质

 - 对于 $1 \le T \le 3$，测试点 $T$ 满足 $N \le 16$。
 - 对于 $4 \le T \le 9$，测试点 $T$ 满足 $N \le 1000$。
- 对于 $10 \le T \le 20$，测试点 $T$ 没有额外限制。 

## 样例 #1

### 输入

```
8 10
1 2
1 3
1 4
2 3
2 4
3 4
1 5
2 6
3 7
4 8```

### 输出

```
12```

# 题解

## 作者：Demeanor_Roy (赞：8)

- [原题链接](https://www.luogu.com.cn/problem/P8905)

------------

首先直接求肯定很难做，指数级做法不说还很难优化。考虑换一个角度，一个比较常见的想法就是从特殊的小团体入手。

将奶牛间的朋友关系看作一幅无向图，我们令点 $u$ 为度数最小的点（有很多点的情况下任意取一个），让我们首先考虑所有包含点 $u$ 的点集中最优的一个。这里给出结论：包含点 $u$ 的极大联通子图便是所有包含点 $u$ 的点集中最优的一个。证明的话考虑小团体强度的构成因素，不难发现在所有包含点 $u$ 的点集中，点数当然是此时取到最大，而由于点 $u$ 本身便是度数最小的点，所以此时度数最小点度数也取到最大，因此小团体强度取到最大，证明完毕。

有了上面那个结论，我们就不难得到以下做法：每次取出当前度数最小的点，计算包含其的极大联通子图的答案，再将当前点及其相关边删去，反复操作直至所有点被删完。

思考实现以上操作需要什么：我们需要动态维护度数最小点及其度数，已经其所在极大联通子图的点数。前面两点可以用一个优先队列维护，每删一个点就动态维护与其相邻点的信息，关键是后者。发现直接做并查集无法实现删边操作，考虑先正序求出前者时同时记录删点顺序，再倒序并查集加点，得到想要的信息。

于是这道题就完成了。时间复杂度 $O((n+m)(\log n + \alpha(n)))$。

[代码](https://www.luogu.com.cn/paste/2hgjg0ds)

---

## 作者：DengDuck (赞：5)

决定小团体强度的值有两个：

- 团体内的最小度。
- 团体人数。

我们可以考虑枚举最小度求最大的团体人数。

我们发现小于原图最小度的度肯定不优，因为原图最小度可以直接选择包含全图使团体人数最大，这给了我们一个启发。

在之后，由于我们要增大团体内的最小度，所以最小度的点不会被包含，因此可以考虑删掉这些点。

这个时候问题由变回了原样，我们可以继续找最小度的点，如此类推。

注意到动态删点加维护连通块大小不好做，但是动态维护点的度数不难，我们先利用 `set` 维护删点顺序，再倒着加点，变成动态加点维护连通块大小，并查集即可维护。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e5+5;
LL n,m,x,y,ans,fa[N],a[N],du[N],d[N],sz[N],vis[N];
vector<LL>v[N];
stack<LL>s;
set<pair<LL,LL>>p;
LL find(LL x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i,a[i]=i,sz[i]=1;
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
		du[x]++,du[y]++;	
	}
	for(int i=1;i<=n;i++)
	{
		p.insert({du[i],i});
	}
	while(!p.empty())
	{
		LL t=(*p.begin()).second;
		p.erase(p.begin());
		s.push(t);
		d[t]=du[t];
		for(LL i:v[t])
		{
			if(d[i])continue;
			p.erase(p.lower_bound({du[i],i}));
			du[i]--;
			p.insert({du[i],i});
		}
	}
	for(int i=1;i<=n;i++)
	{
		LL t=s.top();
		vis[t]=1;
		s.pop();
		for(LL j:v[t])
		{
			if(vis[j]==0)continue;
			LL fx=find(t),fy=find(j);
			if(fx!=fy)
			{
				fa[fx]=fy;
				sz[fy]+=sz[fx];
			}
		}
		ans=max(ans,sz[find(t)]*d[t]);
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：EnofTaiPeople (赞：5)

没错，这道题的贪心是十分自然的。

将奶牛的关系看作一张图，朋友个数就是点的度数。

考虑如果没有那个最小度数的参数，那么最大连通块大小就是答案。

容易发现，随着度数下界增大，一些点就变得不可用了，而这些点删掉之后又会减少其他点的度数，所以需要一直找出最小度数点，直到产生新的度数下界为止。

于是我们可以逐步增大度数的下界，即每一次选取度数最小的节点，将其度数是为下界，暴搜找到最大连通块，则度数与连通块大小是一个候选答案。

容易发现，超过 $\sqrt m$ 的度数下界最多会有 $\sqrt m$ 个，于是这样总复杂度为 $O(m(\sqrt m+\log_2n))$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
using ll=long long;
ll ans,szt;
int n,m,g[N],lm,q[N],l,r;
vector<int>lk[N];
bitset<N>vs,ct;
struct cmpI{
	bool operator()(const int &x,const int &y)
	const{return g[x]==g[y]?x<y:g[x]<g[y];}
};
set<int,cmpI>st;
void cut(int x){
	if(!ct[x]){
		st.erase(x);
		if(--g[x]<=lm)ct[q[++r]=x]=1;
		else st.insert(x);
	}
}
void dfs(int x){
	++szt,vs[x]=1;
	for(int y:lk[x])
		if(!ct[y]&&!vs[y])dfs(y);
}
int main(){
#ifdef MYdef
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	cin>>n>>m;
	int i,x,y;
	for(i=1;i<=m;++i){
		cin>>x>>y;
		++g[x],++g[y];
		lk[x].push_back(y);
		lk[y].push_back(x);
	}
	for(x=1;x<=n;++x)st.insert(x);
	while(st.size()){
		lm=g[*st.begin()];
		vs.reset();
		for(x=1;x<=n;++x)
			if(!ct[x]&&!vs[x]){
				szt=0,dfs(x);
//				printf("%lld %d\n",szt,lm);
				ans=max(ans,szt*lm);
			}
		l=1,r=0;
		while(st.size()&&g[*st.begin()]<=lm)
			ct[q[++r]=*st.begin()]=1,st.erase(st.begin());
		while(l<=r){
//			printf("ql:%d\n",q[l]);
			x=q[l++];
//			printf("cut:%d\n",x);
			for(int y:lk[x])cut(y);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：EXODUS (赞：4)

# Part 1：前言
一道好玩的图论，个人感觉是一个套路的时间倒流。

# Part 2：正文

不难发现题面等价于在图中选一个子图，最大化最小度数乘子图大小。

我们去枚举度数，设 $deg$ 表示度数，原答案即为

$$
\max_{deg=0}^n siz_{deg}\times deg
$$

其中 $siz_i$ 表示删去最少数目的点使得所有点度数不小于 $i$ 后的最大连通块大小。注意到如果一个点度数在某一时刻度数变的小于 $i$，它必然会在接下来为了保证所有点度数不小于 $i$ 这一过程中被删掉，否则这个点将一直不会删掉（即不会出现一个点在 $deg=x$ 时被删掉，在 $deg=y$ 时出现且 $x<y$），也就是说，我们在枚举到 $deg=x$ 时的流程可以这样描述。

1. 将所有度数小于 $x$ ，且没有被删掉的点入队。
2. 依次删去其中的每一个点。
3. 重复 1,2 操作，直到队列为空。

注意到删边维护最大连通块是不好做的，我们令所有点被删掉的时刻为 $t$，并记下当 $deg=[1,t]$ 时被删掉的边是哪几条，从 $t$ 向 $1$ 跑，每次统计答案后加上在这一时刻被删去的边，用带权并查集维护连通块大小即可，复杂度 $O(m\log n)$


# Part 3：代码
```cpp
const int N=1e5+7;
int n,m;
set<int>g[N];
set<np>q;
vector<np>edge[N];
int deg[N];
int fa[N],siz[N];
int Siz;

int find(int x){
	while(x!=fa[x])x=fa[x]=fa[fa[x]];return x;
}
void merge(int u,int v){
	int fu=find(u),fv=find(v);
	if(fu==fv)return;
	fa[fv]=fu;siz[fu]+=siz[fv];
	Siz=max(Siz,siz[fu]);
}

void Main(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		g[u].insert(v),g[v].insert(u);
		deg[u]++,deg[v]++;
	}
	for(int i=1;i<=n;i++)q.insert(mp(deg[i],i));
	int cnt=1;
	for(;!q.empty();cnt++){
		while(!q.empty()&&(*q.begin()).first<cnt){
			int u=(*q.begin()).second;q.erase(q.begin());
			for(auto v:g[u])if(g[v].find(u)!=g[v].end())
				q.erase(mp(deg[v],v)),g[v].erase(u),deg[v]--,edge[cnt].pb(mp(u,v)),q.insert(mp(deg[v],v));
			deg[u]=0;g[u].clear();
		}
	}
	for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;
	ll ans=0;
	for(int i=cnt-1;i>=0;i--){
		if(i==cnt-1)goto there;
		ans=max(ans,1ll*Siz*i);
		there:;
		for(auto e:edge[i]){merge(e.fi,e.se);}
	}
	cout<<ans;
	return;
}
```

---

## 作者：_ANIG_ (赞：3)

[题目链接](https://www.luogu.com.cn/problem/P8905)

## 并查集+深搜
很容易想到一个思路：枚举最小组内朋友数，然后求出满足出度都大于一个数的最大的连通块。这样看起来是 $O(mn)$ 的，实际上，当枚举到的 $x$ 大于 $\sqrt m$ 的时候，就不可能合法了。所以只需要枚举到 $\sqrt m$ 即可，并且最终答案几乎不会达到这个上界，所以如果需要卡常，可以枚举到 $\frac{\sqrt m}{2}$。

然后就是判断的部分。设当前枚举到 $x$，显然，如果一个点的出度小于 $x$，这个点可以直接排除。此时，要把这个点删掉。删掉这个点后，可能有一些点的出度减小了。如果一个点出度减少后小于 $x$，那么就可以把这个点也删掉。为了方便，记录下每个点的出度 $cd_i$，采用深搜删点。如果删到点 $i$，把与 $i$ 相连的点的出度减少 $1$，在此过程中，如果发现一个点的出度小于 $x$ 且没有删过，就从这个点开始继续 DFS。所有应删的点删完后，剩余的所有点的出度都不小于 $x$。然后直接并查集求连通块即可。

由于每个点最多被删除一次，所以单次复杂度为 $O(n+m)$，总复杂度 $O(n+m)\sqrt m$。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,cd[200005],fa[200005],siz[200005],mk[200005],ans;
vector<int>p[100005];
int f(int x){
	if(x==fa[x])return x;
	return fa[x]=f(fa[x]);
}
void he(int a,int b){
	if(f(a)!=f(b))siz[f(b)]+=siz[f(a)],fa[f(a)]=f(b);
}
void dfs(int x,int y){
	mk[x]=1;
	for(int i=0;i<p[x].size();i++){
		int c=p[x][i];
		if(mk[c])continue;
		cd[c]--;
		if(cd[c]<y)dfs(c,y);
	}
}
int solve(int x){
	memset(mk,0,sizeof(mk));
	for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;
	int res=0;
	for(int i=1;i<=n;i++)cd[i]=p[i].size();
	for(int i=1;i<=n;i++)if(cd[i]<x&&mk[i]==0)dfs(i,x);
	for(int i=1;i<=n;i++){
		if(!mk[i]&&cd[i]>=x)
		for(int j=0;j<p[i].size();j++){
			int c=p[i][j];
			if(!mk[c]&&cd[c]>=x)he(i,c);
		}
	}
	for(int i=1;i<=n;i++)if(!mk[i]&&fa[i]==i){
		res=max(res,siz[i]);
	}
	return res;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		p[a].push_back(b);
		p[b].push_back(a);
	}
	for(int i=1;i*i*((n>1000)+1)<=m;i++)ans=max(ans,i*solve(i));
	cout<<ans;
} 
```


---

## 作者：vectorwyx (赞：3)

考虑最小度数肯定小于等于 $\sqrt{2m}$，那么暴力枚举它，用 https://www.luogu.com.cn/problem/CF1439B 这题的思路，拓扑排序，每次把度数 $<k$ 的删掉，如果新产生了度数 $<k$ 的点就继续删，最终剩下的点形成的连通块就是满足条件的连通块。暴力 dfs 取最大的那个即可。复杂度 $O((n+m)\sqrt m)$。

代码如下：
```cpp
#include<bits/stdc++.h>
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}


//16:28~16:33,16:33~16:47

const int N=1e5+5;
vector<int> e[N];
int n,m,deg[N],stk[N],top,ok[N],tmp[N],vis[N],ti;

int dfs(int x){
	vis[x]=ti;
	int ret=1;
	for(int i:e[x]) if(!ok[i]&&vis[i]<ti) ret+=dfs(i);
	re ret;
}

int calc(int k){
	top=0;fo(i,1,n) ok[i]=0,deg[i]=tmp[i];
	fo(i,1,n) if(deg[i]<k) stk[++top]=i,ok[i]=1;
	fo(i,1,top){
		int x=stk[i];
		for(int j:e[x]) if(!ok[j]&&(--deg[j])<k) stk[++top]=j,ok[j]=1;
	}
	++ti;
	int ret=0;
	fo(i,1,n) if(!ok[i]&&vis[i]<ti) big(ret,dfs(i));
	re ret;
}

signed main(){
//	freopen("gen.txt","r",stdin);
	cin>>n>>m;
	fo(i,1,m){
		int x=read(),y=read();
		e[x].eb(y),e[y].eb(x);
		deg[x]++,deg[y]++;
	}
	fo(i,1,n) tmp[i]=deg[i];
	int B=(int)sqrt(2*m);
	ll ans=0;
	fo(i,1,B) big(ans,(ll)i*calc(i));//,cout<<i<<'\n';
	cout<<ans;
	return 0;
}
}
/*
-------------------------------------------------
*/










signed main(){re vectorwyx::main();}
```

---

## 作者：yszs (赞：2)

[传送门](
https://www.luogu.com.cn/problem/P8905)

题意：给定一个无向图，选出几个点，去掉连向外面的边，权值为选出的点数 $\times$ 和每个点的度数最小值。

考虑一个最优的情况，就是完全图，这时候它的第二个系数最大值才是 $\sqrt m$，所以我们考虑深入去想第二个系数。

选点，不去想，考虑所有点都存在，每次把不优秀的点删掉。

考虑第二个系数为 $i$ 时，那每个度数 $< i$ 的点就需要被删除，那我们直接拓扑排序。

我们枚举第二个系数从 $1-\sqrt m$，我们每次都把度数为 $i-1$ 的点全删掉然后dfs求一下连通块最大个数就做完了。  

代码很短

复杂度 $O((n+m) \sqrt m)$。 

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=b;i>=a;i--)
#define endl "\n"
#define For(i,u) for(int i=head[u];i;i=e[i].next)
#define itr(it,awa) for(auto it=awa.begin();it!=awa.end();it++)
#define add(u,v) G[u].push_back(v);
const int MOD=1e9+7;
int n,m;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
using namespace std;
const int N=1e5+5;
int du[N],vis[N],del[N];
vector<int>G[N];
int cnt=0;
void dfs(int u)
{
	cnt++;
	vis[u]=1;
	for(int v:G[u])
	{
		if(!vis[v]&&!del[v])
		{
			dfs(v);
		}
	}
}
int ans;
void slove(int k)
{
	queue<int>q;
	memset(vis,0,sizeof(vis));
	rep(i,1,n)
	{
		if(!del[i]&&!vis[i])
		{
			cnt=0;
			dfs(i);
//			cout<<"QwQ "<<cnt<<endl;
			ans=max(ans,cnt*k);
		}
	}
	rep(i,1,n)
	{
		if(du[i]==k) q.push(i);
	}
	while(!q.empty())
	{
		int u=q.front();
		del[u]=1;
		q.pop();
		for(int v:G[u])
		{
			if(!del[v])
			{
				du[v]--;
				if(du[v]==k)
				{
					q.push(v);
				}
			}
		}
	}
}
int main()
{
	n=read(),m=read();
	rep(i,1,m)
	{
		int u=read(),v=read();
		add(u,v);
		add(v,u);
		du[u]++;
		du[v]++;
	}
	rep(i,1,sqrt(m))
	{
		slove(i);
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：LJ07 (赞：1)

影响答案的有两个因素：点的度数和连通块大小。

从点的度数这一维度入手，每次得到当前点的度数最小值，然后不断删点使得存在的点的度数的最小值比当前的大。

正着做发现难以维护连通块大小。那就倒过来用并查集维护即可。

时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define U(i,a,b) for(int i(a),i##e(b);i<=i##e;++i)
#define D(i,b,a) for(int i(b),i##e(a);i>=i##e;--i)
using namespace std;
const int N(1e5);
using pii=pair<int,int>;
#define fi first
#define se second
int n,m,deg[N+5];
vector<int> g[N+5];
set<pair<int,int> > s;
int minn[N+5],cnt;
vector<int> p[N+5];
int f[N+5],sz[N+5];
int getf(int x) {return x==f[x]?x:f[x]=getf(f[x]);}
void merge(int x,int y)
{
	if ((x=getf(x))==(y=getf(y))) return ;
	sz[x]+=sz[y],f[y]=x;
}
LL ans;
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	for (int i(1),u,v;i<=m;++i)
		cin>>u>>v,++deg[u],++deg[v],g[u].push_back(v),g[v].push_back(u);
	U(i,1,n) s.insert({deg[i],i});
	while (s.size())
	{
		int td(s.begin()->fi);
		minn[++cnt]=td;
		for (pii t;s.size()&&(t=*s.begin()).fi<=td;)
		{
			s.erase(t);
			for (int v:g[t.se]) if (deg[v]) s.erase({deg[v]--,v}),s.insert({deg[v],v});
			deg[t.se]=0;
			p[cnt].push_back(t.se);
		}
	}
	U(i,1,n) sz[i]=1,f[i]=i;
	for (;cnt;--cnt)
	{
		for (int u:p[cnt]) deg[u]=1;
		for (int u:p[cnt])
			for (int v:g[u])
			if (deg[v])	merge(u,v);
		for (int u:p[cnt]) ans=max(ans,1ll*minn[cnt]*sz[getf(u)]);
	}cout<<ans;
}
```

---

## 作者：VictorChen (赞：1)

显而易见，对于一个给定的组内奶牛最小朋友数 $x$，我们要尽可能多地选取满足要求的奶牛。

因此我们考虑从小到大遍历 $x$；对于每个 $x$，我们删去所有出度小于 $x$ 的牛并统计当前牛所在的连通块大小即可。

所以我们可以利用优先队列，每次统计出度最小的点所在的连通块大小并更新答案，随后删除此点并更新其它点的出度。

在实现上，由于删除边相对难以实现，可以反向思考；

我们在操作时先存储删边和查询操作，随后逆序执行每个操作；此时删除边即为加边，我们可以考虑用并查集维护；

本题核心代码如下：

```cpp
// 并查集维护连通块
class MergeSet
{
    private:
        int fa[100010], siz[100010];
    
    public:
        void init()
        {
            memset(fa, -1, sizeof(fa));
            for(int i=1; i<=n; i++)
                siz[i] = 1;
        }

        int find(int x)
        {
            if(fa[x] == -1)
                return x;
            else
                return fa[x] = find(fa[x]);
        }

        void merge(int x, int y)
        {
            x = find(x);
            y = find(y);

            if(x == y)
                return;
            
            if(siz[x] > siz[y])
                swap(x, y);
            
            fa[x] = y;
            siz[y] += siz[x];
            siz[x] = 0;
        }

        int findSize(int x)
        {
            return siz[find(x)];
        }
}mset;

int val[100010];
bool vis[100010];

int ans;

int cnt2;
struct Operation
{
    int type; // type为0表示查询操作，为1表示修改操作
    
    // 查询操作使用
    int mult, pos;

    // 修改操作使用
    int x, y;
}p[500010];

void newOp(int type, int x, int y)
{
    p[++cnt2].type = type;
    if(type == 0)
        p[cnt2].mult = x, p[cnt2].pos = y;
    else
        p[cnt2].x = x, p[cnt2].y = y;
}

int main()
{
    scanf("%d%d", &n, &m);
	
    // 读入信息，把所有点放入优先队列中
    mset.init();
    for(int i=1; i<=m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);

        AddEdge(x, y);
        AddEdge(y, x);

        val[x]++, val[y]++;
    }
	
    for(int i=1; i<=n; i++)
        q.push(Node(i, val[i]));

    while(!q.empty())
    {
        Node tp = q.top(); // 取当前度数最小的点
        q.pop();
		
        if(vis[tp.id] == true)
            continue;
        else
            vis[tp.id] = true;
        
        // 查询当前点所在连通块大小，尝试更新答案
        newOp(0, tp.val, tp.id);
        for(int i=head[tp.id]; i!=0; i=e[i].nxt)
            if(vis[e[i].to] == false)
            {
            	// 模拟删边操作
                newOp(1, tp.id, e[i].to);
                val[e[i].to]--;
				
                // 更新相关点的出度
                q.push(Node(e[i].to, val[e[i].to]));
            }
    }
	
    // 逆序执行操作序列
    for(int i=cnt2; i>=1; i--)
        if(p[i].type == 0)
            ans = max(ans, p[i].mult * mset.findSize(p[i].pos));
        else
            mset.merge(p[i].x, p[i].y);
    
    printf("%d\n", ans);

    return 0;
}
```

---

## 作者：qzhwlzy (赞：0)

### 题目大意

给定一张 $n$ 个点 $m$ 条边的无向图。找到其所有连通子图中点的度数最小值乘子图大小的最大值。

### 思路

发现答案是两个东西乘积的形式。偶们不妨固定一个，例如固定度数最小的点是哪个。此时，要想乘积最大，子图点数一定最大。

于是，我们假设原图中度数最小的点为 $u$，则包含 $u$ 的子图能够贡献的答案最大是 $u$ 的度数乘上其所在连通块的大小。而对于不含 $u$ 的子图，我们可以在原图中删掉 $u$ 及其所连出的边，重复上述过程即可。

维护连通块大小可以使用并查集，但是并查集无法维护删点。于是先用优先队列处理出来删点的顺序，然后倒着跑，用并查集维护加点即可。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#define maxn 100005
#define maxm 200005
#define pii pair<int,int>
#define m_p make_pair
#define a_f first
#define a_s second
using namespace std;
int n,m,u,v,deg[maxn],f[maxn],siz[maxn],ord[maxn],num=0,ans; bool vis[maxn];
priority_queue<pii,vector<pii>,greater<pii> > q;
struct edge{int to,nex;}a[maxm*2]; int head[maxn],cnt=0;
void add(int from,int to){a[++cnt].to=to; a[cnt].nex=head[from]; head[from]=cnt;}
int getfa(int x){if(f[x]==x) return f[x]; return f[x]=getfa(f[x]);}
void unionn(int p1,int p2){int r1=getfa(p1),r2=getfa(p2); if(r1==r2) return; f[r2]=r1; siz[r1]+=siz[r2];}
int main(){
	scanf("%d%d",&n,&m); for(int i=1;i<=m;i++) scanf("%d%d",&u,&v),deg[u]++,deg[v]++,add(u,v),add(v,u);
	for(int i=1;i<=n;i++) f[i]=i,siz[i]=1,q.push(m_p(deg[i],i));
	while(!q.empty()){ // 用类似 dijkstra 的东西处理删点的顺序
		pii top=q.top(); q.pop(); if(deg[top.a_s]!=top.a_f||vis[top.a_s]) continue;
		ord[++num]=top.a_s; vis[top.a_s]=1;
		for(int i=head[top.a_s];i;i=a[i].nex) if(!vis[a[i].to]) deg[a[i].to]--,q.push(m_p(deg[a[i].to],a[i].to));
	} // for(int i=1;i<=num;i++) printf("%d ",ord[i]);
	for(int i=1;i<=n;i++) deg[i]=vis[i]=0; for(int i=num;i>=1;i--){
		vis[ord[i]]=1; for(int j=head[ord[i]];j;j=a[j].nex) if(vis[a[j].to])
			unionn(ord[i],a[j].to),deg[ord[i]]++,deg[a[j].to]++;
		ans=max(ans,deg[ord[i]]*siz[getfa(ord[i])]);
	} printf("%d",ans);
	return 0;
}
```

---

## 作者：Find_Yourself (赞：0)

显然不同连通块互不影响，答案分开算。

对于当前连通块，假如我们希望所选的子图中最小的度数为 $x$，那么只需要保留度数大于等于 $x$ 的所有点，然后将这些点能连的边连上，再保留其中度数合法的，以此类推，最后剩下的点数就是子图最大的大小。

这些操作就相当于，对于当前图，如果度数最小的点不满足，那么将它及其所连的边删除，直到满足停止。

实时维护节点度数可以用 `set`，如果对于每一种最小度数都按照这种方法算一遍，那么复杂度为 $O(n^2\log n)$。

但观察发现，对于当 $x<y$ 时，度数小于 $x$ 的节点必定小于 $y$，所以复杂度能降至 $O(n\log n)$。

为了写起来更方便，每次删除一个点前，都以它算一遍答案。

又因为过程中图可能会分裂，而分裂后子图的大小不好维护，所以考虑用并查集倒序加边来做。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
ll n,m,tot,fa[N],d[N],vis[N],siz[N],f[N];
ll ans;
int ff(int x){return fa[x]==x?x:fa[x]=ff(fa[x]);}
int ff2(int x){return f[x]==x?x:f[x]=ff2(f[x]);}
vector<int>adj[N],g[N];
struct node{
	int u,d;
	node(int u=0,int d=0):u(u),d(d){}
	bool operator<(const node &x)const{return d!=x.d?d<x.d:u<x.u;}
}e[N];
set<node>st;
void get(){
	tot=0;
	while(st.size()){
		node t=(*st.begin());st.erase(t);
		vis[t.u]=1;d[t.u]=0;
		e[++tot]=node(t.u,0);
		for(int i=0;i<adj[t.u].size();++i){
			int v=adj[t.u][i];if(vis[v])continue;
			e[++tot]=node(t.u,v);
			st.erase(node(v,d[v]));--d[v];
			st.insert(node(v,d[v]));
		}
	}
	for(int i=tot;i>=1;--i){
		if(e[i].d==0){
			int u=e[i].u;
			ans=max(ans,d[u]*siz[ff2(u)]);
		}else{
			int u=e[i].u,v=e[i].d;
			++d[u];++d[v];
			if(ff2(u)==ff2(v))continue;
			siz[ff2(u)]+=siz[ff2(v)];
			f[ff2(v)]=ff2(u);
		}
	}
} 
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)fa[i]=f[i]=i,siz[i]=1;
	for(int i=1;i<=m;++i){
		int u,v;cin>>u>>v;++d[u];++d[v];
		adj[u].push_back(v);adj[v].push_back(u);
		fa[ff(u)]=ff(v);
	}
	for(int i=1;i<=n;++i)g[ff(i)].push_back(i);
	for(int i=1;i<=n;++i){
		if(!vis[i]){
			int w=ff(i);
			for(int j=0;j<g[w].size();++j){
				st.insert(node(g[w][j],d[g[w][j]]));
			}
			get();
		}
	}
	cout<<ans<<endl;
  return 0;
}

```


---

## 作者：Glacial_Shine (赞：0)

# 思路

考场上前面没思路，后面灵光一现，突然就想到了。

我们可以先枚举小团体的「强度」$fr$，即组内奶牛的最小组内朋友数，从 $1$ 开始枚举。

这个的好处就是我们只用考虑一个一个的删点，而不用多个一起考虑。

然后我们每次将组内朋友数小于 $fr$ 的节点删除即可。

然后 $O(n)$ 暴力求最大连通块，相乘枚举数即可。

这里有个小优化，即每次删完节点后可以将 $fr$ 设为当前留下来的节点的组内朋友的最小值，这样可以少枚举一些没有用的状态。

具体实现可以看代码。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, m, last[100005], Ecnt, num[100005], bz[100005], flag[100005];
LL ans;
struct Edge { int to, next; } E[400005];
void addedge(int u, int v) { Ecnt++, E[Ecnt].next = last[u], last[u] = Ecnt, E[Ecnt].to = v; }
struct People {
    int fr, id;
    friend bool operator< (People a, People b) { return a.fr > b.fr; }
} p;
priority_queue <People> q;
int dfs(int x) {
    flag[x] = 1;
    int sum = 1;
    for (int xy = last[x]; xy; xy = E[xy].next)
        if (!bz[E[xy].to] && !flag[E[xy].to])
            sum += dfs(E[xy].to);
    return sum;
}
int main() {
    // freopen("C.in", "r", stdin);
    // freopen("C.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addedge(u, v), addedge(v, u), num[u]++, num[v]++;
    for (int i = 1; i <= n; i++)
        p.fr = num[i], p.id = i, q.push(p);
    for (int fr = 1; fr <= n; fr++) {
        while (!q.empty() && q.top().fr < fr) {
            if (bz[q.top().id]) {
                q.pop();
                continue;
            }
            int id = q.top().id;
            bz[id] = 1;
            q.pop();
            for (int xy = last[id]; xy; xy = E[xy].next)
                num[E[xy].to]--, p.fr = num[E[xy].to], p.id = E[xy].to, q.push(p);
        }
        while (!q.empty() && bz[q.top().id])
            q.pop();
        if (q.empty())
            break;
        fr = q.top().fr;
        int sum = 0;
        for (int i = 1; i <= n; i++)
            if (!bz[i] && !flag[i])
                sum = max(sum, dfs(i));
        ans = max(ans, 1ll * sum * fr);
        for (int i = 1; i <= n; i++)
            flag[i] = 0;
    }
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：Na2PtCl6 (赞：0)

## Observation
首先我们知道，不可能去枚举每个子图，子图之间也不好转移转态因为这不是树。

然后研究一些性质可以发现：当前我们在处理所有子图的度数的最小值可以作为一个很好的限制，只要我们钦定我们在处理所有子图的度数的最小值为一个定值，那么当前的候选答案 $=$ 度数最小值 $×$ 删掉一些点使得原图中没有点的度数小于限定值后，新图的最大连通块大小。

怎么实现？直接暴力枚举限定值，然后暴力删点，暴力删边。删完之后确认一下当前度数最小值是否为设定值，如果不是还要往后更新，完了就是 `dfs` 搜当前图上的最大联通块。

考虑用 `set` 维护点当前的度数，以及现存的边。暴力删点复杂度 $O(n\operatorname{log}n)$，暴力删边复杂度 $O(m\operatorname{log}m)$（实际上达不到），由于当限定值为 $i$ 时，图中点数是 $O(\frac{m}{i})$ 级别的，遍历全图是 $O(p \operatorname{log} p)$ 的( $p$ 是当前点数)。

所以最终的复杂度就是两个 log 的，虽然常数有点大（狗头

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100004;
char vis[maxn];
int n,m,u,v,cnt,maxsz,deg[maxn],nxt[maxn],pre[maxn];
long long res;
struct item{
	int id,e;
	bool operator < (const item &comp)const{
		if(e==comp.e)
			return id<comp.id;
		return e<comp.e;
	}
};
set< int > g[maxn];
set< item > pts;

void read(int &x){
	char c=getchar();x=0;
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c^48);
}

void dfs(int ver){
	vis[ver]=1;
	++cnt;
	for(int i:g[ver])
		if(!vis[i])
			dfs(i);
}

void del(int x){
	nxt[pre[x]]=nxt[x];
	pre[nxt[x]]=pre[x];
}

signed main(){
	read(n),read(m);
	while(m--){
		read(u),read(v);
		g[u].insert(v);
		g[v].insert(u);
		++deg[u],++deg[v];
		maxsz=max(maxsz,(int)g[v].size());
		maxsz=max(maxsz,(int)g[u].size());
	}
	for(int i=0;i<=n;i++){
		pre[i]=i-1;
		nxt[i]=i+1;
	}
	for(int i=1;i<=n;i++)
		pts.insert((item){i,(int)g[i].size()});
	for(int i=1;i<=maxsz;i++){
		while(pts.size()&&pts.begin()->e<i){
			int tar=pts.begin()->id;
			for(int j:g[tar]){
				pts.erase((item){j,deg[j]});
				--deg[j];
				pts.insert((item){j,deg[j]});
				g[j].erase(tar);
			}
			g[tar].clear();
			pts.erase((item){tar,deg[tar]});
			del(tar);
		}
		if(pts.size())
			i=pts.begin()->e;
		else
			break;
		for(int j=nxt[0];j!=n+1;j=nxt[j])
			if(vis[j]==0){
				cnt=0;
				dfs(j);
				res=max(res,1ll*cnt*i);
			}
		for(int j=nxt[0];j!=n+1;j=nxt[j])
			vis[j]=0;
	}
	printf("%lld\n",res);
	return 0;
}

```

---

