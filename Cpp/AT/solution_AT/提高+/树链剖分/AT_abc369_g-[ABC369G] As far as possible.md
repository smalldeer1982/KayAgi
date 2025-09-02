# [ABC369G] As far as possible

## 题目描述

给定一棵包含 $N$ 个顶点的树。顶点编号为 $1, 2, \ldots, N$。  
第 $i$ 条边（$1\leq i\leq N-1$）连接顶点 $U_i$ 和顶点 $V_i$，长度为 $L_i$。

对于 $K=1,2,\ldots,N$，请解决以下问题。

> 高桥君和青木君进行一个游戏。游戏规则如下：
>
> - 首先，青木君在树上指定 $K$ 个互不相同的顶点。
> - 然后，高桥君需要构造一条起点和终点均为顶点 $1$ 的“步道”，并且该步道必须经过青木君指定的所有顶点。
>
> 高桥君构造的步道的长度定义为分数。高桥君希望分数尽可能小，青木君希望分数尽可能大。请你求出当两人都采取最优策略时的分数。

步道的定义：在无向图（包括树）上，步道是指由 $k$ 个顶点（$k$ 为正整数）和 $k-1$ 条边交替组成的序列 $v_1,e_1,v_2,\ldots,v_{k-1},e_{k-1},v_k$，其中每条边 $e_i$ 连接顶点 $v_i$ 和 $v_{i+1}$。序列中同一个顶点或同一条边可以出现多次。步道经过顶点 $x$，是指存在 $1\leq i\leq k$ 使得 $v_i=x$（可以有多个这样的 $i$）。步道的起点和终点分别为 $v_1$ 和 $v_k$，步道的长度为 $e_1,e_2,\ldots,e_{k-1}$ 的长度之和。

## 说明/提示

### 数据范围

- $2\leq N\leq 2\times 10^5$
- $1\leq U_i < V_i\leq N$
- $1\leq L_i\leq 10^9$
- 输入均为整数
- 给定的图为一棵树。

### 样例解释 1

当 $K=1$ 时，青木君最优地指定顶点 $3$，此时高桥君可以构造步道 $1\to 2\to 3\to 2\to 1$，最优分数为 $16$。当 $K=2$ 时，青木君最优地指定顶点 $3,5$，此时高桥君可以构造步道 $1\to 5\to 1\to 2\to 3\to 2\to 1$ 等，最优分数为 $22$。当 $K\geq 3$ 时，双方最优时分数为 $26$。

### 样例解释 2

注意答案可能超出 $32$ 位整数范围。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 2 3
2 3 5
2 4 2
1 5 3```

### 输出

```
16
22
26
26
26```

## 样例 #2

### 输入

```
3
1 2 1000000000
2 3 1000000000```

### 输出

```
4000000000
4000000000
4000000000```

# 题解

## 作者：CuteMurasame (赞：7)

题意简述：一棵 $n$ 个点的树，A 选 $k$ 个不同的点，B 从点 $1$ 出发经过这 $k$ 个点再回到点 $1$，经过长度为 $d$ 的路径。A 想让 $d$ 尽量大，B 想让 $d$ 尽量小。对于 $k=1,2,\cdots,n$ 求 $d$。

首先 B 一定走最短路径。

- 先考虑 $k=1$，A 显然会选离点 $1$ 最远的点 $p_1$。
- 然后当 $k=2$，A 为了让 $d$ 最大，选的点一定包括 $p_1$，另一个点是在 $1\sim p_1$ 的路径上任意一个点出发，不经过 $1\sim p_1$ 的路径上任意一条边，能到达的最远的点 $p_2$。
   - 我们举个例子：
   - 例如样例的树长这个样子：![](https://cdn.luogu.com.cn/upload/image_hosting/ri59ys54.png)
   - $k=1$ 显然选 $p_1=3$，因为 $1\sim3$ 的路径更长。
   - $k=2$，除了 $1\sim3$ 的路径外，$1\sim5$ 更长。故选 $3,5$。如果不选 $3,5$，那么路径一定更短。
- 所以其实 $k=K$ 时，就是在 $k=K-1$ 的基础上再选一个使路径最长的点。

那么问题可以转化为，每次选一条未选的最长的链，输出链长${}\times 2$ 的值（因为需要返回到 $1$ 点，链上每条边最少经过 $2$ 次）。

问题是如何求最长的链。我们可以进行一次 dfs，求出每个点子树中最长的链，然后对于其他链不考虑这条链上的边，最后把链长排个序就行了。核心代码：

```cpp
vector<pair<int,int>> g[200001];
multiset<int> len;
int dfs(int x,int fa)
{
	multiset<int> dis;
	for(auto [y,v]:g[x]) if(y!=fa) dis.emplace(dfs(y,x)+v);
	if(dis.empty()) return 0;
	int val=*dis.rbegin();
	dis.erase(prev(dis.end()));
	for(auto i:dis) len.emplace(i);
	return val;
}
```

进行 dfs 后，`len` 中存储的就是把这棵树分成链，使得链最长的链长。

然后每次选最长的链就行了。

[AC 记录](https://atcoder.jp/contests/abc369/submissions/57347250)。

---

## 作者：Genius_Star (赞：6)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18391497)

### 题意：

给定一个 $n$ 个节点且有边权的树，对于每个 $k \in [1,n]$ 求：

- 选取 $k$ 条从根结点出发到叶子结点的简单路径，求这些路径的并集上所有结点的点权之和的最大值。

$1 \le n \le 2 \times 10^5$。

### 思路：

[双倍经验。](https://www.luogu.com.cn/problem/P10641)

明显有一个贪心的思路：

- 每次取叶子到根的路径权值和最大的。

- 清空该链上的点的点权。

模拟 $n$ 次即可，但是复杂度不可取，考虑数据结构优化。

将叶子节点按 dfn 序从小到大编号，令 $l_u,r_u$ 表示 $u$ 子树内叶子节点的编号在 $[l_u,r_u]$ 间。

每次找到路径权值和最大的那个叶子节点，可以直接暴力跳父亲清空路径上的点，每次清空就是将区间 $[l_u,r_u]$ 内的叶子结点到根的权值和减去 $w_u$。

若遇到一个点已经被清空了，故该点到根节点路径上的点肯定也被清空了，就可以直接退出了；这样每个点做多只会清空一次。

考虑使用线段树维护上述操作，时间复杂度均摊为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=2e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll l,r;
	ll tag;
	ll Max;
	ll id;
}X[N<<2];
ll n,k,cnt,ans;
ll a[N],Ans[N],l[N],r[N],d[N],id[N],fa[N];
vector<pi> E[N];
map<pi,ll> F;
bool f[N];
void add(ll u,ll v,ll w){
	E[u].push_back({v,w});
	E[v].push_back({u,w});
}
void dfs(ll u,ll f){
	l[u]=n,r[u]=1;
	bool F=1;
	for(auto t:E[u]){
		ll v=t.fi,w=t.se;
		if(v==f)
		  continue;
		fa[v]=u;
		d[v]=d[u]+w;
		dfs(v,u);
		l[u]=min(l[u],l[v]);
		r[u]=max(r[u],r[v]);
		F=0;
	}
	if(F){
		id[++cnt]=u;
		l[u]=r[u]=cnt;
		a[cnt]=d[u];
	}
}
void pushup(ll k){
	X[k].Max=max(X[k<<1].Max,X[k<<1|1].Max);
	if(X[k].Max==X[k<<1].Max)
	  X[k].id=X[k<<1].id;
	else
	  X[k].id=X[k<<1|1].id;
}
void update(ll k,ll v){
	X[k].Max+=v;
	X[k].tag+=v;
}
void push_down(ll k){
	if(X[k].tag){
		update(k<<1,X[k].tag);
		update(k<<1|1,X[k].tag);
		X[k].tag=0;
	}
}
void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	if(l==r){
		X[k].Max=a[l];
		X[k].id=l;
		return ;
	}
	ll mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
void update(ll k,ll l,ll r,ll v){
	if(X[k].l==l&&r==X[k].r){
		update(k,v);
		return ;
	}
	push_down(k);
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  update(k<<1,l,r,v);
	else if(l>mid)
	  update(k<<1|1,l,r,v);
	else{
		update(k<<1,l,mid,v);
		update(k<<1|1,mid+1,r,v);
	}
	pushup(k);
}
void solve(ll u){
	while(!f[u]&&fa[u]){
		f[u]=1;
		update(1,l[u],r[u],-F[{u,fa[u]}]);
		u=fa[u];
	}
}
int main(){
	n=read();
	for(int u,v,w,i=1;i<n;i++){
		u=read(),v=read(),w=read();
		F[{u,v}]=F[{v,u}]=w;
		add(u,v,w);
	}
	dfs(1,0);
	build(1,1,cnt);
	For(i,1,n){
		if(X[1].Max>0)
		  ans+=X[1].Max;
		if(X[1].Max>0)
		  solve(id[X[1].id]);
		write(ans*2);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：_AyachiNene (赞：5)

# 思路：
一种不用长剖的做法。首先一个明显的贪心，每次加入的点一定是个叶子节点。同时发现这题有一个很好的性质，一条边的权值只会贡献两次，因为如果从一个叶子到另一个叶子，肯定不会走他们 Lca 以上的部分，上面的边只会在第一次走的之后和离开这个子树的时候走。那么就很好做了，每次去找一个深度最大的叶子，把它加入答案就行了。对于这个东西的维护很简单，如果一条边在算贡献时算了两次，那么这条边就不会再产生贡献，所以在找叶子时就把两次贡献算完，再把跟到它的边贡献全删完，发现每条边只会被删除一次，且每次都删的一个前缀，所以直接暴力从找到的叶子向上删，遇到被删过的点就退出。深度就用线段树维护，每次删边就把子树内的所有点深度减去边权，维护区间最大值和区间减就好了。

由于~~用小号测题号被封了~~实现简单就不给代码了。

---

## 作者：wrkwrkwrk (赞：2)

不妨认为 $1$ 是根。

先考虑 $k=1$，此时答案为选择最大深度的两倍。

再考虑 $k=2$，此时答案为选择两个顶点，其到 $\text{lca}$ 的距离和再加上 $\text{lca}$ 的深度最大的两倍。

推广这个结论，答案为以 $1$ 为根，最大的选择 $k$ 个顶点，满足其构成的最小导出子树最大。

此时考虑动态规划，定义 $dp_{i,j}$ 表示 $i$ 顶点下选择 $k$ 个点的答案。

转移为
$$
dp_{i,j}=\max_{k \in [0,j] \cap \Z}{dp_{\text{pre},j-k}+dp_{\text{subtree},k}+\text{cost}[k \neq 0]}
$$

发现这个是一个 $\max +$ 卷积的形式，~~不妨~~认为其有凸性。（因为显然要先选大的）。

故根据此时 $\max +$ 的算法，考虑处理其差分，并做直接归并。

考虑到[暴力合并](https://atcoder.jp/contests/abc369/submissions/57323103)是不行的，由于其符合两块合并的规则，故考虑用 multiset 维护，启发式合并即可。

时间复杂度 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<pair<int,int>>g[1000006];
multiset<int,greater<int>>ans[1000006];
void dfs(int now,int fa){
	ans[now].insert(0);
	for(auto x:g[now]){
		int to=x.first,cost=x.second;
		if(to!=fa){
			dfs(to,now);
			auto x=*ans[to].begin();ans[to].erase(ans[to].begin());
			ans[to].insert(x+cost);
			if(ans[to].size()>ans[now].size())ans[now].swap(ans[to]);
			for(auto x:ans[to]){
				ans[now].insert(x);
			}
		}
	} 
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int a,b,c;
		cin>>a>>b>>c;
		g[a].push_back({b,c});
		g[b].push_back({a,c}); 
	}
	dfs(1,0);
	vector<int>res;
	for(auto x:ans[1])res.push_back(x);
	for(int i=1;i<res.size();i++)res[i]+=res[i-1];
	while(res.size()<=n+1)res.push_back(res.back());
	for(int i=0;i<n;i++)cout<<res[i]*2<<'\n';
	return 0;
}
```
[AC](https://atcoder.jp/contests/abc369/submissions/57331637) 记录

---

## 作者：PineappleSummer (赞：2)

[[ABC369G] As far as possible](https://www.luogu.com.cn/problem/AT_abc369_g)

非常简单的做法。

性质：每次选点肯定是选择叶子节点，每条需要走的边都要走两次。

走两次可以最后乘 $2$，这样只需考虑从上往下走。

考虑每次多选择一个点，在树上多需要走的路径是一条链，并且这条链最下面一定是叶子节点。所以每次选择这个树上没走过的最长的一条链就行。

那么对这棵树做一个长链剖分，保证每条链底部一定是叶子节点。将每条链加入堆里，每次取出堆顶的链即可。

时间复杂度 $O(n\log n)$。

```
priority_queue <int> q;
void dfs (int x) {
    for (auto i : G[x]) {
        int y = i.y, v = i.v;
        if (y == fa[x]) continue;
        fa[y] = x;
        dfs (y);
        if (dep[y] + v > dep[x]) dep[x] = dep[y] + v, son[x] = y;
    }
    for (auto i : G[x]) {
        int y = i.y, v = i.v;
        if (y == fa[x] || y == son[x]) continue;
        q.push (dep[y] + v);
    }
}
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> n;
    for (int i = 1, x, y, v; i < n; i++) {
        cin >> x >> y >> v;
        G[x].push_back ({y, v});
        G[y].push_back ({x, v});
    }
    dfs (1); q.push (dep[1]);
    for (int i = 1; i <= n; i++) {
        if (!q.empty ()) ans += q.top (), q.pop ();
        cout << (ans << 1ll) << '\n';
    }
    return 0;
}

---

## 作者：zibenlun (赞：1)

# 思路

首先思考 Takahashi 如何让自己走过的路径最小。根据题意，一定要从 1 号点出发并回到 1 
号点，所以每一个点到 1 号点之间的边一定是要经过两次的。

知道了计算经过所有点的路径长度的方法之后，就可以根据其特点发现，当选取部分点的时候，选子节点一定比选择他的祖先更优。因为选取子节点后，同样会经过其祖先，所以说选择一个点就相当于选择了其祖先。现在我们只需要统计所有的叶子的权值（到达此处的路径长度和）。此时我们会发现有多个儿子的点会导致路径长度的重复计算，我们需要将有多个儿子的节点的权值转移给它其中的一个儿子。因为选取点的时候是按照路径最长的方式选取，所以每一次都是要选取能使路径增加最长的点，所以我们选择将每个点的权值传递给他的重儿子。之后统计所有的叶子的权值，输出即可。


# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
struct nd{int y,z;};
int s[N],dp[N],n,ans;
priority_queue<int> q;
vector<nd> v[N];
void dfs(int x,int fa){//找重儿子
	int maxx=0;
	for(auto i:v[x]){
		if(i.y==fa) continue;
		dp[i.y]=i.z;
		dfs(i.y,x);
		if(dp[i.y]>maxx)maxx=dp[i.y],s[x]=i.y;
	}
	dp[x]+=maxx;
}
void dfss(int x,int fa){//计算所有点的权值
	for(auto i:v[x]){
		if(i.y==fa) continue;
		if(s[x]==i.y)dp[i.y]=dp[x]+i.z;
		else dp[i.y]=i.z;
        //转移给重儿子
		dfss(i.y,x);
	}if(v[x].size()==1&&fa!=0)q.push(dp[x]);
    //存下叶子
}
signed main() {
	cin>>n;
	for(int i=1,x,y,z;i<n;i++) {
		cin>>x>>y>>z;
		v[x].push_back({y,z});
		v[y].push_back({x,z});
	}
	dfs(1,0);dp[1]=0;dfss(1,0);
    //dp数组用了两次
    //在dfs中用于统计重儿子
    //在dfss中用于存储当前点的权值
	for(int i=1;i<=n;i++){
		if(q.size()) ans+=q.top()*2,q.pop();
        //在所有为选取的叶子中选择最大的
        //选完所有的叶子后，其他的点不在会对答案产生贡献
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Neil_Qian (赞：1)

# [ABC369G] As far as possible 题解

首先一个很显然的贪心：一定选叶子。如果 $k$ 比叶子节点的数量大那么就是叶子节点数量时的答案，此时一定遍历整棵树。

然后对题目进行一定转化。贡献计算显然可以转化为所有点向上到根的路径上的权值之和，不重复统计。可以计算每条边对点的贡献，是更深节点的子树，是连续的。于是我们可以维护当前的最大值，贡献暴力往上消除即可，均摊需要消除 $O(1)$ 次。

为什么当前的最大值一定更优呢？首先证明不可能改变原来选择的最大值，因为改变了以后必然更小（以前是最大值），那改变回去必然更优。因此这样做是正确的。于是每一次选择当前最大，用线段树维护区间加和全局最值即可。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;using ll=long long;using P=pair<ll,ll>;
const int N=2e5+2;ll n,x[N],y[N],z[N],T,dfn[N],ed[N],node[N],F[N],leaf,ans[N],dep[N];
P mx[N<<2];ll tag[N<<2];vector<P> v[N];bool L[N],clear[N];ll w[N];
inline void apply(int x,ll k){mx[x].first+=k,tag[x]+=k;}
inline void pushdown(int x){apply(x<<1,tag[x]),apply(x<<1|1,tag[x]),tag[x]=0;}
inline void pushup(int x){mx[x]=max(mx[x<<1],mx[x<<1|1]);}
inline void init(int x,int l,int r){
	if(l==r){mx[x]=P{(L[node[l]]?0:-1e18),l};return;}
	int mid=(l+r)>>1;init(x<<1,l,mid),init(x<<1|1,mid+1,r),pushup(x);
}
inline void update(int x,int l,int r,int L,int R,ll k){
	if(L<=l&&r<=R){apply(x,k);return;}
	int mid=(l+r)>>1;pushdown(x);
	if(L<=mid)update(x<<1,l,mid,L,R,k);
	if(mid+1<=R)update(x<<1|1,mid+1,r,L,R,k);
	pushup(x);
}
inline P query(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return mx[x];
	int mid=(l+r)>>1;pushdown(x);P ans=P{0,0};
	if(L<=mid)ans=max(ans,query(x<<1,l,mid,L,R));
	if(mid+1<=R)ans=max(ans,query(x<<1|1,mid+1,r,L,R));
	return ans;
}
inline void dfs(int x,int fa){
	L[x]=1,dfn[x]=ed[x]=++T,node[T]=x,F[x]=fa,dep[x]=dep[fa]+1;
	for(P t:v[x]){
		if(t.first!=fa)L[x]=0,dfs(t.first,x),ed[x]=ed[t.first];
		else w[x]=t.second;
	}
	leaf+=L[x];
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n;
	for(int i=1;i<n;i++)cin>>x[i]>>y[i]>>z[i],
		v[x[i]].emplace_back(P{y[i],z[i]}),v[y[i]].emplace_back(P{x[i],z[i]});
	dfs(1,0),init(1,1,n);
	for(int i=1;i<n;i++){
		if(dep[x[i]]>dep[y[i]])swap(x[i],y[i]);
		update(1,1,n,dfn[y[i]],ed[y[i]],z[i]);
	}
	for(int i=1;i<=leaf;i++){
		P res=query(1,1,n,1,n);ans[i]=ans[i-1]+res.first;int x=node[res.second];
		while(!clear[x]&&x!=1)
			update(1,1,n,dfn[x],ed[x],-w[x]),clear[x]=1,x=F[x];
		cout<<ans[i]*2<<"\n";
	}
	for(int i=leaf+1;i<=n;i++)cout<<ans[leaf]*2<<"\n";
	return 0;
}
```

后记：第一次 $7$ 题，比较激动。虽然这次相对简单。

---

## 作者：Night_sea_64 (赞：1)

感觉这次 ABC 是完全可以轻松 AK 的，但我没参加。。。

很显然这样走到的边一定是恰好走两次的。

首先考虑一个结点。一定是走到最深的叶结点。

然后第二个结点要使增加的距离最多，那肯定是选没走过的最长的路径。去掉之前选的显然不会使答案变大。

后面以此类推。

然后显然不难发现是长链剖分。意思是每个点都和其子结点中子树最深的那个连起来。因为每条链的最下方一定恰好有一个叶子结点，所以剖出的链的个数恰好等于叶子结点数。

这题只需要剖一下就行了，没有操作。最后记得把这些链的长度大到小排个序。

时间复杂度 $O(n\log n)$。代码不难，想好了之后十分钟以内就能写完。

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#define int long long
using namespace std;
int n,d[200010],maxd[200010],son[200010];
int cur=1,len[200010];
struct edge{int x,w;};
vector<edge>v[200010];
void dfs1(int x,int last)
{
    for(auto e:v[x])
        if(e.x!=last)
        {
            d[e.x]=d[x]+e.w;
            dfs1(e.x,x);
            if(maxd[e.x]+e.w>maxd[x])
                maxd[x]=maxd[e.x]+e.w,son[x]=e.x;
        }
}
void dfs2(int x,int last,int id)
{
    for(auto e:v[x])
        if(e.x!=last)
        {
            if(e.x==son[x])
            {
                len[id]+=e.w;
                dfs2(e.x,x,id);
            }
            else
            {
                cur++;
                len[cur]=e.w;
                dfs2(e.x,x,cur);
            }
        }
}
bool cmp(const int &x,const int &y){
    return x>y;
}
signed main()
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        v[x].push_back({y,w});
        v[y].push_back({x,w});
    }
    dfs1(1,0);
    dfs2(1,0,1);
    sort(len+1,len+cur+1,cmp);
    for(int i=1;i<=cur;i++)
    {
        len[i]+=len[i-1];
        cout<<len[i]*2<<endl;
    }
    for(int i=cur+1;i<=n;i++)cout<<len[cur]*2<<endl;
    return 0;
}
```

---

## 作者：Dtw_ (赞：0)

# Solution
不难发现，从 $1$ 走然后回到 $1$ 一定是走的每条边的边权 $\times 2$。如果只选一个点，那我们一定是选最长的那条链。

所以每次就会选最长的链，次长的链，然后以此类推。

但是这些链会有重复，如果还是按两倍的边权那显然是错的。因为有些链经过了重复的边，但这些边在博弈的时候只会被算一次贡献，所以我们应该把这个去掉。

考虑我们怎么算每条链无重复的长度？可以对于一个点求他的儿子的贡献，然后在转移到父亲。

其实这就是长链剖分。

具体的：先递归到叶子，然后往上回溯，每次记录最大值，比最大值小的路径就记录一下，最后把最大值记录，然后排序就做完了。
# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 2e5 + 10;

int n;

vector<pii> G[N];

vector<int> res;

int dfs(int u, int fa)
{
	int maxd = 0;
	for (auto e : G[u])
	{
		int v = e.fi, w = e.se;
		if (v == fa) continue;
		int dist = dfs(v, u) + w;
		if (maxd > dist) res.push_back(dist);
		else
		{
			res.push_back(maxd); // 更新的最大值不会记录，这就保证了答案的正确
			maxd = dist;
		}
	}
	return maxd;
}

signed main()
{
	cin >> n;
	for (int i=1; i<n; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}
	res.push_back(dfs(1, 0));
	sort(res.begin(), res.end());
	reverse(res.begin(), res.end()); // 因为第一次一定是选最长的，所以在反转一下
	int ans = 0;
	for (int i=1; i<=n; i++)
	{
		ans += res[i-1] * 2;
		cout << ans << endl;
	}
	return 0;
}



```

---

## 作者：lingziyi2025 (赞：0)

# [ABC369G] As far as possible 题解

提供一种新奇的思路。

发现重叠的路径会重复贡献，可以看作一条已经选过的路径上再多“长出”了几条路径。

```
-
       O
old ->/ 
     o  
  ->/ \\ <--new
   o   o
```

于是，我们可以在每次的最优路径上进行“拓展”。

即将路径上还没有贡献过的“树枝”丢进一个堆中。

可以预处理每个点到自己子树的最长路径，这样可以方便处理。

由于每个点最多包含在一条用于贡献的路径中，所以时间复杂度 $O(n\log n)$；

```c++
#include<bits/stdc++.h>
#define rg register int
#define fo(i,l,r) for(rg i=l;i<=r;i++)
#define dfo(i,r,l) for(rg i=r;i>=l;i--)
#define frein freopen("in.txt","r",stdin);
#define freout freopen("out.txt","w",stdout);
#define fre(p) freopen(#p".in","r",stdin),freopen(#p".out","w",stdout);
#define outa(l,r,a) {fo(i,l,r)cout<<a[i]<<" ";cout<<"\n";}
#define BZ cout<<"----------------\n";
#define eb emplace_back
#define ll long long
using namespace std;
const int N=2e5+5;ll ans;
int n,x,y,z;
int sum,to[N<<1],nex[N<<1],hd[N],v[N<<1];
void add(int x,int y,int z){to[++sum]=y,nex[sum]=hd[x],v[sum]=z,hd[x]=sum;}
int dis[N],son[N];bool bz[N];
struct nd{
	ll dis;int x,son;
	friend bool operator<(nd a,nd b){return a.dis<b.dis;}
}a[N],tp;
priority_queue<nd>q;
void dfs(int x,int fa){
	a[x].x=x;
	for(rg i=hd[x];i;i=nex[i]){
		if(to[i]==fa)continue;
		dfs(to[i],x);
		if(a[to[i]].dis+v[i]>a[x].dis)a[x].dis=a[to[i]].dis+v[i],a[x].son=to[i];
	}
}
int main(){
	std::ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	fo(i,2,n)cin>>x>>y>>z,add(x,y,z),add(y,x,z);
	dfs(1,0);q.push(a[1]);
	fo(i,1,n){
		if(!q.empty())tp=q.top(),x=tp.x,ans+=tp.dis,q.pop();
		cout<<2*ans<<"\n";
		for(;x;x=a[x].son){
			bz[x]=1;
			for(rg i=hd[x];i;i=nex[i])if(!bz[to[i]]&&to[i]!=a[x].son)
                tp=a[to[i]],tp.dis+=v[i],q.push(tp);
		}
	}
	return 0;
}
```

---

## 作者：_qhbd_ (赞：0)

# 题意
给定一棵由 $N(N\le 2\times10^5)$ 个点构成的树。路人甲和路人乙在玩一个游戏，路人甲选择 $K$ 个点，路人乙规划一条最短的以点 $1$ 为起点和终点的经过路人甲所选择的 $K$ 个点。

对于 $K=1,2,3,…,N$，输出路人甲、乙都做出最优选择的情况下路径的长度。
# 思路
先看路人乙，不难发现无论 $K$ 是多少，他规划的路径上每条边只会经过 $0$ 或者 $2$ 次。

如果你想不通，不妨想想树上深搜，当点 $u$ 需要走到时（其非根），你肯定要经过它与其父节点间的边，然后遍历完 $u$ 的子树你还要回去，那么又要经过一次它与父亲间的边，刚好两次。如果点 $u$ 不需要遍历，那么不必多说。

这时我们不妨把边的贡献转移到点上，点 $u$（除开根）的贡献是 $2\times dis(u,fa_u)$（二倍自己与父亲间距离）。很好理解，一个点与父节点间的边是否会被走两次只与该点是否在路人乙路径上有关，所以该点与边的贡献是可以绑定的。

再看路人甲，对于他而言如果能选择一个节点，那么他一定会选择叶节点。若选择的点非叶节点，那么该点下放，路人乙需要走的路径一定更多。同样的，若还有叶节点可供其选择他也一定优先选择叶节点，但若无叶节点可供选择，他选择的点也不会再有贡献，因为此时路人乙所规划的路径一定已经可以经过所有点了。

那么这里不得不说到一道题 [P10641 BZOJ3252 攻略](https://www.luogu.com.cn/problem/P10641)，它的题意是，选择 $k$ 个叶节点，求这些叶节点到根节点路径上点的并集的点权值和的最大值。

分析到现在，它们的题意已经几乎一致了，你可以直接把这道题的做法套用过来，不过不再是只是求选择 $K$ 个叶子节点，而是求 $K=1,2,3,…,N$ 时的结果，当然对于大于等于叶节点数量的 $K$ 而言结果是一样的。

攻略这道题有很多方法，感兴趣的可以自己去看看了解。

我们对于每个叶节点维护它的贡献，也就是它到根路径上的点的权值和。然后每次贪心选择一个贡献最大的叶节点，清零它到根节点路径上点的权值，我们把这些点看做被删去，不难发现会构成更多的树，于是可以继续贪心。

贪心的正确性显然，用线段树维护即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5; 
int n,k,fa[N],del[N],dfn[N],End[N],sfn,cnt,a[N];
long long c[N],val[N],ans[N];
vector<pair<int,int>>e[N];
inline void dfs(int u,int f){
	fa[u]=f;
	dfn[u]=cnt+1;
	if(e[u].size()==1&&u!=1){a[++cnt]=u;}
	for(auto t:e[u])if(t.first^f){
		c[t.first]=t.second*2;
		val[t.first]=val[u]+c[t.first];
		dfs(t.first,u);
	}
	End[u]=cnt;
}
struct SGT{
	long long mx[N<<2],id[N<<2],lz[N<<2];
	inline void pushup(int p){
		if(mx[p<<1]>mx[p<<1|1])mx[p]=mx[p<<1],id[p]=id[p<<1];
		else mx[p]=mx[p<<1|1],id[p]=id[p<<1|1];
	}
	inline void build(int p,int l,int r){
		if(l==r)return mx[p]=val[a[l]],id[p]=a[l],void();
		build(p<<1,l,l+r>>1);
		build(p<<1|1,(l+r>>1)+1,r);
		return pushup(p);
	}
	inline void uplz(int p,int w){
		mx[p]+=w;
		lz[p]+=w;
	}
	inline void pushdown(int p){
		if(lz[p]){
			uplz(p<<1,lz[p]);
			uplz(p<<1|1,lz[p]);
			lz[p]=0; 
		}
	}
	inline void modify(int p,int l,int r,int L,int R,int w){
		if(l>R||L>r)return;
		if(L<=l&&r<=R)return uplz(p,w);
		pushdown(p);
		modify(p<<1,l,l+r>>1,L,R,w);
		modify(p<<1|1,(l+r>>1)+1,r,L,R,w);
		return pushup(p);
	}
}t;
int rt=0;
long long res=0;
signed main(){
	del[1]=1;
	scanf("%lld",&n);
	for(int i=1,u,v,w;i<n;i++){
		scanf("%lld%lld%lld",&u,&v,&w);
		e[u].emplace_back(v,w);
		e[v].emplace_back(u,w);
		res+=w*2;
	}
	dfs(1,0);
	t.build(1,1,cnt);
	for(int i=cnt;i<=n;i++)
		ans[i]=res;
	for(int i=1;i<cnt;i++){
		ans[i]=ans[i-1]+t.mx[1];
		int u=t.id[1];
		while(!del[u]){
			t.modify(1,1,cnt,dfn[u],End[u],-c[u]);
			del[u]=1;
			u=fa[u];
		}
	}
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[i]);
	return 0;
} 
```

---

## 作者：Gordon_Song (赞：0)

钦定边不好处理，转化成对于点的限制。一看就很像虚树，所以可以用这个结论：

假设已经选定了 $k$ 个必须经过的点 $p_1,\dots p_k$，将他们按 dfn 排序，则最小需经过的边权和即为两两之间的距离。

但是这样还是不容易处理。由于路径上每一条边都被经历了 $2$ 次，于是先求出答案除以 $2$ 的结果。然后就变成了选定 $k$ 个点，求它们到 $1$ 的路径上的边的交集的权值和。

此时好像还没有正解思路，只有一个 $O(n^2)$ 的解法：每次找到一个点 $x$ 使得 $x$ 到 $1$ 的路径上未被遍历的边的权值和最大，然后更新选过的边集。

但是由于边一共只有 $n-1$ 条，也就是更新选过的边集最多只会更新 $O(n)$ 次。所以只要我们能快速查询这个最优的点 $x$ 就是正解了。

尝试使用数据结构维护这个东西。这个数据结构要支持查询全局最大值，子树减一个值。使用线段树就好了。

[AC Code](https://atcoder.jp/contests/abc369/submissions/57327273)

---

## 作者：lilong (赞：0)

题目给定的是边权，不好处理，考虑把它转化为点权。具体地，在 dfs 的过程中，把边权当做子节点的点权即可，效果是一样的。接下来都以点权代替边权。

首先存在一个事实，任何一个点都不会经过 $3$ 次或以上。从根节点向下遍历，从子节点向上回溯，一定会先遍历完一棵子树内的点，再去走另一棵子树内的点，因此上述事实正确性显然。接下来只考虑单程，那么每个点权只能使用一次。后面就好办了。

有一个显然的贪心，即每次都取剩余权值和最大的一条路径。由于每个点的权值都只计算一次，因此这样做能够确保前面若干次得到的答案最大。假如不取大的而先取小的，那么答案一定不会优于前者（大的可能没取到），从而保证了贪心的正确性。

接下来考虑如何维护最大值。每一次求出最大值后，同时记录最大值对应的点的编号。对于一个点 $u$，它的权值 $w_u$ 被取走后将会导致以 $u$ 为根的子树中每个点的总权值减少 $w_u$。子树修改？使用 dfs 序加线段树维护即可！

但是如果我们每次都暴力修改会超时。注意到每个权值只能用一次，也就是说只有一次修改是有效的！那么我们使用一个标记数组记录每个点是否被修改，遇到一个点已经被修改时，说明它的祖先也已经修改了（因为都是向根节点跳），直接退出即可。

注意题目要求最后原路返回到根节点，因此答案要乘 $2$。

总时间复杂度 $O(n\log n)$。


```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#define int long long

using namespace std;

map<int,map<int,int> > mp;
vector<int> G[200001];
int n,k,a[200001],b[200001],Lx[200001],Rx[200001],rev[200001],fa[200001],vis[200001],tot,ans;

struct T
{
	int mx,lzy,id;
}t[1000001];

void pushdown( int u )
{
	if( t[u].lzy )
	{
		t[u << 1].mx += t[u].lzy;
		t[u << 1].lzy += t[u].lzy;
		t[u << 1 | 1].mx += t[u].lzy;
		t[u << 1 | 1].lzy += t[u].lzy;
		t[u].lzy = 0;
	}
	return;
}

void pushup( int u )
{
	if( t[u << 1].mx >= t[u << 1 | 1].mx ) t[u].mx = t[u << 1].mx,t[u].id = t[u << 1].id;
	else t[u].mx = t[u << 1 | 1].mx,t[u].id = t[u << 1 | 1].id;
	return;
}

void dfs( int u , int f )
{
	fa[u] = f;
	Lx[u] = ++ tot;
	rev[tot] = u;
	for( auto v : G[u] )
	{
		if( v == f ) continue;
		a[v] += a[u] + mp[u][v];
		b[v] = mp[u][v];
		dfs( v , u );
	}
	Rx[u] = tot;
}

void build( int u , int l , int r )
{
	if( l == r )
	{
		t[u].mx = a[rev[l]];
		t[u].id = rev[l];
		return;
	}
	int mid = ( l + r ) >> 1;
	build( u << 1 , l , mid );
	build( u << 1 | 1 , mid + 1 , r );
	pushup( u );
}

void update( int u , int l , int r , int L , int R , int x )
{
	if( L <= l && r <= R )
	{
		t[u].mx += x;
		t[u].lzy += x;
		return;
	}
	pushdown( u );
	int mid = ( l + r ) >> 1;
	if( L <= mid ) update( u << 1 , l , mid , L , R , x );
	if( R > mid ) update( u << 1 | 1 , mid + 1 , r , L , R , x );
	pushup( u );
}

T ma( T x , T y )
{
	if( x.mx >= y.mx ) return x;
	return y;
}

T query( int u , int l , int r , int L , int R )
{
	if( L <= l && r <= R )
		return t[u];
	pushdown( u );
	int mid = ( l + r ) >> 1;
	T res;
	res.mx = 0;
	if( L <= mid ) res = ma( res , query( u << 1 , l , mid , L , R ) );
	if( R > mid ) res = ma( res , query( u << 1 | 1 , mid + 1 , r , L , R ) );
	return res;
}

signed main()
{
	int u,v,w,nw;
	T tt;
	cin >> n;
	for( int i = 1 ; i < n ; i ++ )
	{
		cin >> u >> v >> w;
		G[u].push_back( v );
		G[v].push_back( u );
		mp[u][v] = mp[v][u] = w;
	}
	dfs( 1 , -1 );
	build( 1 , 1 , n );
	for( int i = 1 ; i <= n ; i ++ )
	{
		tt = query( 1 , 1 , n , 1 , n );
		ans += tt.mx;
		nw = tt.id;
		while( nw != -1 )
		{
			if( vis[nw] ) break;
			vis[nw] = 1;
			update( 1 , 1 , n , Lx[nw] , Rx[nw] , -b[nw] );
			nw = fa[nw];
		}
		cout << ans * 2 << '\n';
	}
	return 0;
}
```

---

## 作者：cancan123456 (赞：0)

原题：[luogu P10641](https://www.luogu.com.cn/problem/P10641)。

显然，Takahashi 选择的路径一定是 $k$ 个点到根的路径并的边权之和乘 $2$（乘 $2$ 是因为构造环路）。

那么 Aoki 就要选择 $k$ 个顶点使其到根的路径的并集权值和最大，考虑贪心，每次选择一个最远的叶子节点，加入答案然后清空到根的路径上的边权，可以使用 exchange argument 证明正确性。

可以用树剖维护贪心，时间复杂度为 $O(n\log^2n)$，但我们考虑对树进行长链剖分，容易发现前 $k$ 长的长链就是答案，时间复杂度为 $O(n\log n)$，瓶颈在于排序。

```cpp
#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long ll;
const int N = 200005;
struct Edge {
	int v, w, next;
} edge[2 * N];
int head[N], cnt;
void add_edge(int u, int v, int w) {
	cnt++;
	edge[cnt].v = v;
	edge[cnt].w = w;
	edge[cnt].next = head[u];
	head[u] = cnt;
}
ll len[N], p[N];
int son[N], m;
void dfs(int u, int fa) {
	for (int v, i = head[u]; i != 0; i = edge[i].next) {
		v = edge[i].v;
		if (v != fa) {
			dfs(v, u);
			ll now = len[v] + edge[i].w;
			if (len[u] < now) {
				son[u] = v;
				len[u] = now;
			}
		}
	}
	for (int v, i = head[u]; i != 0; i = edge[i].next) {
		v = edge[i].v;
		if (v != fa && v != son[u]) {
			m++;
			p[m] = len[v] + edge[i].w;
		}
	}
}
int main() {
//	freopen("in.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int u, v, w, i = 1; i < n; i++) {
		scanf("%d %d %d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	dfs(1, 0);
	m++;
	p[m] = len[1];
	sort(p + 1, p + m + 1, greater < ll > ());
	for (int i = 2; i <= n; i++) {
		p[i] += p[i - 1];
	}
	for (int i = 1; i <= n; i++) {
		printf("%lld\n", p[i] * 2);
	}
	return 0;
}
```

---

## 作者：wangyishan (赞：0)

极限！最后 2 分钟拿下 ABC G！

![](https://cdn.luogu.com.cn/upload/image_hosting/dpypsjgo.png)

### 题解

首先让我们考虑一下二人的最优策略是什么。

首先，`Takahashi` 的策略很简单：按照 DFS 序从小到大遍历一遍每一个标记的点。

正确性是显然的，考虑最坏情况：每个点都被涂色，这时树上的每条边都要被遍历 2 次。所以，令 $s$ 表示所有边的边权和，则答案不会超过 $2s$。

观察 `Aoki` 的策略，我们首先发现一个事实：优先选叶子结点一定更优。这也是很显然的。

还有一个结论：令 $k$ 为这棵树的叶子数量，则答案在 $k$ 轮过后一定会变成 $2s$。因为你如果选了所有的叶子，那么每一条边一定都会被你遍历到，答案即为 $2s$。

总结一下，`Takahashi` 的最优策略就是按照 DFS 序遍历每个结点，`Aoki` 的最优策略就是优先选叶子。

现在考虑 `Aoki` 选叶子的顺序。不难发现，`Aoki` 每次一定要选离根或已经被选的叶子到根的路径上的点最远的点。由于每次我们选一个点其实是在选一条链，所以我们就有了一个类似长链剖分的思路：记录每个叶子所在的长链的长度是多少，然后每次贪心选最长的那个。

我代码里是从后往前枚举的，时间复杂度在于排序的 $\mathcal{O}(n\log n)$。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
struct node{
	int v,w;
	node(int a,int b){v=a,w=b;}
	node(){}
};
vector<node>e[500050];
node l[500050];
int cnt=0;
int f[500050],mx[500050];
void dfs0(int x,int pre){
	for(auto i:e[x]){
		if(i.v==pre)continue;
		dfs0(i.v,x);
		if(!mx[x])mx[x]=i.v,f[x]=f[i.v]+i.w;
		else if(f[i.v]+i.w>f[x])mx[x]=i.v,f[x]=f[i.v]+i.w;
	}
	if(!mx[x])mx[x]=x;
}
void dfs(int x,int pre,int ww){
	if(e[x].size()==1&&x!=1)l[++cnt]=node(x,ww);
	for(auto i:e[x]){
		if(i.v==pre)continue;
		if(i.v==mx[x])dfs(i.v,x,ww+i.w);
		else dfs(i.v,x,i.w);
	}
}
int ans[500050];
bool cmp(node a,node b){return a.w>b.w;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n;
	int res=0;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		e[u].push_back(node(v,w));
		e[v].push_back(node(u,w));
		res+=w;
	}
	dfs0(1,1);
	dfs(1,1,0);
	sort(l+1,l+cnt+1,cmp);
	for(int i=n;i>cnt;i--)ans[i]=res*2;
	for(int i=cnt;i>=1;i--){
		ans[i]=res*2;
		int x=l[i].v;
		res-=l[i].w;
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：qcode_aya (赞：0)

啊赛时我没看到从 $1$ 出发回到 $1$ ……

---

首先将题意转化为对于每一条边，选取了其子树内的点就会使答案加上两倍边权。

显然是可以贪心的，每次选取一个使答案增加最大化的叶子然后暴力往上跳父亲直至父边已被选，选取的时候做一个子树减，使用线段树维护可以做到线性对数。站内已经有这个做法的题解。

我们发现如果从叶子考虑会变得异常麻烦。不妨再发现一下若我们选取了一条边，说明其子树内都没被选过，此时我们可以自由自在地往下选取到任意一个叶子。

仿照树剖的思想，dfs 时维护每个点往下剖出的最优答案，当前节点只继承最优儿子的链上答案，其他儿子已是链头。把所有链的答案加入 vector 排序后，从大往小选即可。

代码的话可以参见 atcoder 官方题解。

---

## 作者：Linge_Zzzz (赞：0)

# Sol

观察样例发现先选叶子节点把所有的边都用上之后再怎么选答案都不会变，所以一定是先把叶子选完。

考虑贪心地选叶子，一个叶子对答案的贡献是两倍的其到根节点的边权之和，选了这个叶子就把这些边的边权清空。

考虑到一个点管辖的叶子节点是一段连续的区间，我们可以方便地用线段树维护每个叶子的贡献。

因为每条边只会被贡献一次，所以复杂度是 $O(n\log n)$ 的。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n;
struct edge{
	int v,w,nxt;
}e[N*2];
int head[N],cnt=2;
void add(int u,int v,int w){
	e[cnt].v=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt++;
}
int fa[N],faw[N],L[N],R[N],d[N],rnk[N],num;
void dfs(int u,int f){
	L[u]=INF,R[u]=0;
	bool lf=1;
	for(int i=head[u];i;i=e[i].nxt){
		if(e[i].v!=f){
			lf=0;
			fa[e[i].v]=u,faw[e[i].v]=e[i].w;
			d[e[i].v]=d[u]+e[i].w;
			dfs(e[i].v,u);
			L[u]=min(L[u],L[e[i].v]);
			R[u]=max(R[u],R[e[i].v]);
		}
	}
	if(lf)L[u]=R[u]=++num,rnk[num]=u;
}
struct node{
	int val,lazy,id;
}t[N*4];
node operator+(node x,node y){
	node res=x.val>y.val?x:y;
	res.lazy=0;
	return res;
}
void pushdown(int p){
	t[p*2].val+=t[p].lazy;
	t[p*2].lazy+=t[p].lazy;
	t[p*2+1].val+=t[p].lazy;
	t[p*2+1].lazy+=t[p].lazy;
	t[p].lazy=0;
}
void build(int p,int l,int r){
	if(l==r){
		t[p].val=d[rnk[l]]*2;
		t[p].id=l;
		return;
	}
	int m=(l+r)>>1;
	build(p*2,l,m);
	build(p*2+1,m+1,r);
	t[p]=t[p*2]+t[p*2+1];
}
void update(int p,int l,int r,int L,int R,int val){
	if(L<=l&&r<=R){
		t[p].val+=val;
		t[p].lazy+=val;
		return;
	}
	int m=(l+r)>>1;
	pushdown(p);
	if(L<=m)update(p*2,l,m,L,R,val);
	if(R>m)update(p*2+1,m+1,r,L,R,val);
	t[p]=t[p*2]+t[p*2+1];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w),add(v,u,w);
	}
	dfs(1,0);
	build(1,1,num);
	int ans=0;
	for(int i=1;i<=num;i++){
		ans+=t[1].val;
		int p=rnk[t[1].id];
		while(fa[p]&&faw[p]){
			update(1,1,num,L[p],R[p],-2*faw[p]);
			faw[p]=0;
			p=fa[p];
		}
		cout<<ans<<'\n';
	}
	for(int i=num+1;i<=n;i++)cout<<ans<<'\n';
	return 0;
}
```

---

