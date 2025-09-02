# Sakurako and Chefir

## 题目描述

给定一棵有 $n$ 个顶点的树，根节点为 $1$。Sakurako 在带着她的猫 Chefir 散步时分心了，Chefir 跑丢了。

为了帮助 Sakurako，Kosuke 记录了他的 $q$ 次猜测。在第 $i$ 次猜测中，他假设 Chefir 在顶点 $v_i$ 处迷路，并且有 $k_i$ 点体力。

此外，对于每一次猜测，Kosuke 假设 Chefir 可以沿着树的边任意次移动：

- 如果从顶点 $a$ 移动到顶点 $b$，且 $a$ 是 $b$ 的祖先，则体力不会减少；
- 如果从顶点 $a$ 移动到顶点 $b$，且 $a$ 不是 $b$ 的祖先，则 Chefir 的体力减少 $1$。

如果 Chefir 的体力为 $0$，则不能进行第二种类型的移动。

对于每一次猜测，你需要求出 Chefir 从顶点 $v_i$ 出发、拥有 $k_i$ 点体力时，能够到达的最远顶点的距离。

$^*$ 如果从 $b$ 到根节点的最短路径经过 $a$，则称 $a$ 是 $b$ 的祖先。

## 说明/提示

在第一个样例中：

- 对于第一个询问，可以从顶点 $5$ 走到顶点 $3$（此时体力减少 $1$ 变为 $0$），然后可以走到顶点 $4$；
- 对于第二个询问，从顶点 $3$ 出发，体力为 $1$，只能到达顶点 $2$、$3$、$4$ 和 $5$；
- 对于第三个询问，从顶点 $2$ 出发，体力为 $0$，只能到达顶点 $2$、$3$、$4$ 和 $5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
5
1 2
2 3
3 4
3 5
3
5 1
3 1
2 0
9
8 1
1 7
1 4
7 3
4 9
3 2
1 5
3 6
7
6 0
2 3
6 2
8 2
2 4
9 2
6 3
6
2 1
2 5
2 4
5 6
4 3
3
3 1
1 3
6 5```

### 输出

```
2 1 2 
0 5 2 4 5 5 5 
1 3 4```

# 题解

## 作者：2huk (赞：7)

令 $fa_u$ 为 $u$ 的父亲，$son_u$ 表示 $u$ 的儿子组成的集合。

首先预处理 $f(u)$ 表示 $u$ 的子树内最深的点的深度。

对于一次询问，首先把答案的初始值设为 $f(u)$，表示一步也不向上走。

考虑处理 $g(u)$，表示从 $u$ 走到 $fa_u$ 后，接下来再从别的子树往下走，能走的最多的步数。其实就是我们强制了原题中只能向上走恰好 $1$ 步的答案。

显然：

$$
g(u) = 1 + \max_{v \in son_{fa_u},v \ne u} f(v) - dep(u)
$$

$g(u)$ 也是不难预处理的。

考虑如何计算一次询问 $(u, k)$ 的答案。最暴力的，我们可以枚举向上走几步（$i = 1\dots k$，$i=0$ 即不向上走的已经特判了）。设从 $u$ 开始向上走 $i$ 步后到达的点为 $u_i$。那么答案为：

$$
\max_{i=1}^k i + g(u_{i-1})
$$

考虑**倍增**优化。

具体的，我们设 $w(u, i)$ 表示从 $u$ 开始向上最多走 $2^i$ 步，然后再从别的子树向下走，最多步数。形式化的：

$$
w(u, i) = \max_{j=1}^{2^i} \color{red}j \color{black} + g(u_{j-1})
$$

有递推：

$$
w(u,i) = \max\{w(u,i-1), w(u_{2^{i-1}}, i-1) \color{red}{{}+ 2^{i-1}}\color{black}\}
$$

这里 $+2^{i-1}$ 对应了上面的 $+j$。这是普通倍增所没有的。

查询与预处理类似。于是总复杂度做到 $\mathcal O((n+q)\log n)$。

```cpp
int n;
vector<int> g[N];
int st[N][20], w[N][20];
int mxdep[N], dep[N];

// 定义一条边 (fa[u], u) 的权值为，fa[u] 的所有除 u 的儿子中，mxdep - dep[fa[u]] 的最大值

void dfs1(int u, int fa) {
	mxdep[u] = dep[u] = dep[fa] + 1;
	int k1 = -1e9, k2 = -1e9;
	for (int v : g[u])
		if (v != fa) {
			dfs1(v, u);
			mxdep[u] = max(mxdep[u], mxdep[v]);
			if (mxdep[v] - dep[u] >= k1) {
				k2 = k1, k1 = mxdep[v] - dep[u];
			} else if (mxdep[v] - dep[u] > k2) {
				k2 = mxdep[v] - dep[u];
			}
		}
	
	for (int v : g[u]) {
		if (v == fa) continue;
		w[v][0] = 1 + (mxdep[v] - dep[u] == k1 ? k2 : k1);
	}
}

void dfs2(int u, int fa) {
	for (int v : g[u]) {
		if (v == fa) continue;
		
		st[v][0] = u;
		for (int i = 1; i < 20; ++ i ) {
			st[v][i] = st[st[v][i - 1]][i - 1];
			w[v][i] = max(w[v][i - 1], w[st[v][i - 1]][i - 1] + (1 << i - 1));
		}
		
		dfs2(v, u);
	}
}

void solve() {
	cin >> n;
	
	for (int i = 1; i <= n; ++ i ) {
		g[i].clear();
	}
	
	for (int i = 1; i < n; ++ i ) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	dfs1(1, 0);
	dfs2(1, 0);=
	
	int q;
	cin >> q;
	
	while (q -- ) {
		int u, k;
		cin >> u >> k;
		
		k = min(k, dep[u] - 1);
		int res = max(k, mxdep[u] - dep[u]), lst = 0;
		for (int i = 19; ~i; -- i )
			if (k >= (1 << i)) {
				k -= 1 << i;
				res = max(res, w[u][i] + lst);
				u = st[u][i];
				lst += 1 << i;
			}
		
		cout << res << ' ';
	}
	
	cout << '\n';
}
```

---

## 作者：Linge_Zzzz (赞：4)

# Descr

给你一棵 $n$ 个点的有根树，根是 $1$。

共有 $q$ 次询问，每次询问形如 $v,k$，问从 $v$ 开始往上走 $k$ 步到达的点的的子树内距离 $v$ 最远的点有多远。

$n,q\leq 2\times 10^5$。

# Sol

首先 dfs 一遍，把每个点往下走到最深的点有多远，记为 $maxdep_u$。

考虑答案的式子，假设 $v$ 向上走到 $u$ 然后往下走到 $u$ 的子树里最深的点，答案为 $\max_{u}\{maxdep_u+dep_v-dep_u\}$。

把贡献拆出来：$\max_{u}\{maxdep_u-dep_u\}+dep_v$。

但是这样做不对，有可能会出现 $v$ 往上走到 $u$ 再返回 $v$ 往下走这样刷步数的情况。。。所以我们考虑把这种情况的影响消除。

一种解决方法比较聪明，记每个点的点权 $w_u$ 为其父亲往下走除去 $u$ 这个子树的 $maxdep$ 再减去父亲的 $dep$。查询直接树上倍增 $k$ 步查最大值即可。

另一种是离线解法。。考虑把询问挂到点上，然后在树上再 dfs 一遍求出答案。建立一个线段树，dfs 进入一个点的时候求出跟上面类似的东西放到线段树下标 $dep_u$ 的位置，退出的时候清空。遇到一个询问就是线段树区间 $\max$。

# Code

我的是离线做法。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
const int N=2e5+10,T=20,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,q;
struct edge{
	int v,nxt;
}e[N*2];
int head[N],cnt=2;
void add(int u,int v){
	e[cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt++;
}
int mxd[N],dep[N],L[N],R[N],ans[N];
vector<pii> qr[N];
void dfs(int u,int f){
	dep[u]=dep[f]+1;
	vector<int> son;
	for(int i=head[u];i;i=e[i].nxt){
		if(e[i].v!=f){
			son.pb(e[i].v);
			dfs(e[i].v,u);
			mxd[u]=max(mxd[u],mxd[e[i].v]+1);
		}
	}
	if(son.size()==1)L[son[0]]=R[son[0]]=-INF;
	else if(son.size()>=2){
		for(int i=1;i<son.size();i++)L[son[i]]=max(L[son[i-1]],mxd[son[i-1]]+1-dep[u]);
		for(int i=son.size()-2;i>=0;i--)R[son[i]]=max(R[son[i+1]],mxd[son[i+1]]+1-dep[u]);
	}
}
int t[N*4];
void update(int p,int l,int r,int pos,int val){
	if(l==r){
		t[p]=val;
		return;
	}
	int m=(l+r)>>1;
	if(pos<=m)update(p*2,l,m,pos,val);
	else update(p*2+1,m+1,r,pos,val);
	t[p]=max(t[p*2],t[p*2+1]);
}
int query(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[p];
	int m=(l+r)>>1,ans=-INF;
	if(L<=m)ans=max(ans,query(p*2,l,m,L,R));
	if(R>m)ans=max(ans,query(p*2+1,m+1,r,L,R));
	return ans;
}
void build(int p,int l,int r){
	t[p]=-INF;
	if(l==r)return;
	int m=(l+r)>>1;
	build(p*2,l,m);
	build(p*2+1,m+1,r);
}
void dfs2(int u,int fa){
	for(pii q:qr[u]){
		ans[q.se]=max({mxd[u],dep[u]+query(1,1,n,max(1ll,dep[u]-q.fi),dep[u]),dep[u]-max(1ll,dep[u]-q.fi)});
	}
	for(int i=head[u];i;i=e[i].nxt){
		if(e[i].v!=fa){
			update(1,1,n,dep[u],max(L[e[i].v],R[e[i].v]));
			dfs2(e[i].v,u);
		}
	}
	update(1,1,n,dep[u],-INF);
}
void solve(){
	cin>>n;
	fill(L,L+n+10,-INF);
	fill(R,R+n+10,-INF);
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs(1,1);
	cin>>q;
	for(int i=1;i<=q;i++){
		int v,k;cin>>v>>k;
		qr[v].pb(mp(k,i));
	}
	build(1,1,n);
	dfs2(1,1);
	for(int i=1;i<=q;i++)cout<<ans[i]<<' ';
	cout<<'\n';
	for(int i=1;i<=n;i++)qr[i].clear();
	fill(head,head+n+10,0);
	cnt=2;
	fill(mxd,mxd+n+10,0);
	fill(dep,dep+n+10,0);
	fill(t,t+n*4+10,0);
	fill(ans,ans+q+10,0);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Super_Cube (赞：2)

# Solution

上跳 $k$ 次在一开始直接跳到 $k$ 级祖先处一定不劣。

记 $u$ 的 $k$ 级祖先为 $v$。实质上是找 $v$ 及其子树中距离 $u$ 的最远点。对于 $u$ 到 $v$ 的这条链上的每个点，其所在子树中除去链上儿子的子树剩下的所有点与 $u$ 的最近公共祖先都为它本身。而我们知道两点距离为 $\text{dep}_x+\text{dep}_y-2\cdot\text{dep}_{\operatorname{lca}(x,y)}$。于是新建一棵树，将一个点到它父亲的边权置为其所有兄弟节点中子树内深度最大值减去二倍其父亲深度。询问的答案即为新树上 $u$ 到 $v$ 的边权最大值加上 $u$ 的深度。还有种情况是最远点在 $u$ 的子树内，直接是 $u$ 子树内深度最大值减去 $u$ 的深度。

# Code

```cpp
#include<bits/stdc++.h>
std::vector<int>v[200005];
int fa[200005][20];
int dep[200005];
int d[200005];
void dfs(int p){
	d[p]=dep[p]=dep[fa[p][0]]+1;
	for(int i=1;i<20;++i)
		fa[p][i]=fa[fa[p][i-1]][i-1];
	for(const int&i:v[p])
		if(i!=fa[p][0])
			fa[i][0]=p,dfs(i),
			d[p]=std::max(d[p],d[i]);
}
int st[200005][20];
void dfs2(int p){
	for(int i=1;i<20;++i)
		st[p][i]=std::max(st[p][i-1],st[fa[p][i-1]][i-1]);
	for(const int&i:v[p])
		if(i!=fa[p][0])dfs2(i);
}
int T,n,m,ans;
int main(){
	for(int i=0;i<20;++i)
		st[0][i]=st[1][i]=0xc0c0c0c0;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)v[i].clear();
		for(int i=1,x,y;i<n;++i)
			scanf("%d%d",&x,&y),
			v[x].push_back(y),v[y].push_back(x);
		dfs(1);
		for(int i=1;i<=n;++i){
			static int pre[200005],suf[200005];
			pre[0]=suf[v[i].size()-1]=dep[i];
			for(int j=0;j+1<v[i].size();++j)
				pre[j+1]=std::max(pre[j],v[i][j]==fa[i][0]?0:d[v[i][j]]);
			for(int j=v[i].size()-1;j;--j)
				suf[j-1]=std::max(suf[j],v[i][j]==fa[i][0]?0:d[v[i][j]]);
			for(int j=0;j<v[i].size();++j)
				if(v[i][j]!=fa[i][0])st[v[i][j]][0]=std::max(pre[j],suf[j])-(dep[i]<<1);
		}
		dfs2(1);
		scanf("%d",&m);
		for(int x,y,z;m--;){
			scanf("%d%d",&x,&y);z=x;
			ans=0xc0c0c0c0;
			for(int i=19;~i;--i)
				if(y>>i&1)ans=std::max(ans,st[x][i]),x=fa[x][i];
			ans=std::max(ans+dep[z],d[z]-dep[z]);
			printf("%d ",ans);
		}
		putchar(10);
	}
	return 0;
}
```

---

## 作者：chenxi2009 (赞：2)

~~VP 时做了一个多小时。~~
# 思路
首先简化题意，每一次询问相当于问以点 $v$ 的 $k$ 辈祖先（不存在则为根）为根的子树结点，离点 $v$ 的距离的最大值。

首先有暴力算法：跳到 $v$ 的 $k$ 辈然后遍历子树，或者从 $v$ 开始搜索。$O(nq)$ 不能接受。

发现我们可以用倍增快速跳到 $v$ 的 $k$ 辈祖先，但是我们仍然需要遍历子树：$v$ 与最远的点的最近公共祖先可以是 $v$ 的任何一辈祖先。难道倍增优化真的不可行？

仔细想想，这个最远的点要么是 $v$ 的后代，要么是 $v$ 的某个祖先的后代。在后者的情况中，答案相当于每个祖先**到 $v$ 的距离加上与 $v$ 的前一辈祖先不同的最远的点**。这个点要么是这个祖先最深的后代，要么是和这个后代次深祖先（当前祖先的一个儿子）不同的最深的后代。以图为例：
![](https://cdn.luogu.com.cn/upload/image_hosting/kt5nfcko.png)

$1$ 这个结点最深的后代是 $2$（或 $6$），但是当询问点 $1$ 在黑色框起的子树中时，这两个点**均不能取**，可取的最远点是 $9$。

显然 $O(n)$ 可以预处理出每个点作为祖先时的两个最远点深度，即是从两个**不同儿子**继承最远儿子深度的最大值和次大值。同上图中 $7$ 和 $4$ 子树中最深的两个点。问题在于怎么判断该取一个祖先的最大值还是次大值。

~~此时作者从卫生间回到机房，突然灵光一乍：~~

发现 $k$ 辈祖先下的答案满足倍增律。

~~人话：~~

令 $g_{i,j}$ 表示 $i$ 的 $2^j$ 辈祖先的子树中（刨去 $i$ 的子树，因为这部分难以倍增），离 $i$ 最远的点的距离，$f_{i,j}$ 表示 $i$ 的 $2^j$ 辈祖先，则有：

$g_{i,j}=\max(g_{i,j-1},2^{j-1}+g_{f_{i,j-1},j-1})$

看着有点晕？解读一下：$g_{i,j}$ 要么等于 $g_{i,j-1}$，要么表达的路径就一定经过 $f_{i,j-1}$，所以可以倍增。

然后加上一点倍增技巧这道题就被切掉了，倍增跳祖先的过程中取最大值就可以了。复杂度 $O(\sum(n+q)\log n)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,u,v,q,p,k,dep[200001],deps[200001][2],f[200001][19],g[200001][19],ans,tmp;
vector<int>e[200001];
void sch(int u,int fa){
	deps[u][0] = dep[u] = dep[fa] + 1;//该点本身可以作为最深点 
	f[u][0] = fa;
	for(int i = 1;i <= 18;i ++){
		f[u][i] = f[f[u][i - 1]][i - 1];
	}
	for(int i = 0;i < e[u].size();i ++){
		int v = e[u][i];
		if(v == fa){
			continue;
		}
		sch(v,u);
		if(deps[v][0] > deps[u][0]){//更新最大值 
			deps[u][1] = deps[u][0],deps[u][0] = deps[v][0];
		}
		else if(deps[v][0] > deps[u][1]){//更新次大值 
			deps[u][1] = deps[v][0];
		}
	}
	return;
}
void dfs(int u){
	if(f[u][0]){
		g[u][0] = dep[u] + deps[f[u][0]][deps[u][0] == deps[f[u][0]][0]] - 2 * dep[f[u][0]];//两点距离等同与其深度之和减去最近公共祖先深度的两倍 
	}
	for(int i = 1;i <= 18;i ++){//倍增 
		if(!f[u][i]){
			break;
		}
		int v = f[u][i - 1];
		g[u][i] = max(g[u][i - 1],(1 << i - 1) + g[v][i - 1]);
	} 
	for(int i = 0;i < e[u].size();i ++){
		int v = e[u][i];
		if(v == f[u][0]){
			continue;
		}
		dfs(v);
	}
	return;
}
int main(){
	scanf("%d",&T);
	while(T --){
		scanf("%d",&n);
		for(int i = 1;i <= n;i ++){//多测清空 
			deps[i][0] = deps[i][1] = 0;
			e[i].clear();
		}
		for(int i = 1;i < n;i ++){
			scanf("%d%d",&u,&v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		sch(1,0);
		dfs(1);
		scanf("%d",&q);
		for(int i = 1;i <= q;i ++){
			scanf("%d%d",&p,&k);
			k = min(k,dep[p] - 1);//防止跳出树 
			ans = deps[p][0] - dep[p],tmp = 0;//存在答案点为 p 后代的情况 
			for(int i = 18;i >= 0;i --){//倍增跳祖先 
				if(k >= 1 << i){
					ans = max(ans,tmp + g[p][i]);
					k -= 1 << i;
					p = f[p][i];
					tmp += 1 << i; 
				}
			}
			printf("%d ",ans);
		}
	} 
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：2)

## 题目大意

给定一颗树，多次询问，每次询问给出 $x,k$，求 $x$ 往根至多走 $k$ 条边，往叶子走不限制条边，能到的最远距离。

## 题目分析

相当于 $x$ 的 $k$ 级祖先子树内离 $x$ 距离最远的点，根据结论是子树直径端点，在 dfn 序上用线段树维护区间直径即可，$O(n\log n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=4e5+10,M=1e6+5,inf=(1LL<<31)-1,mod=1e9+7;
const ll llf=1e18;
int n,m,h[N],to[N<<1],nxt[N<<1],cnt;
inline void add_(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
int st[N][20],dep[N],Time,fir[N],lg[N],dfn[N],siz[N],Id[N],tim,f[N][20];
inline void dfs(int x,int fa){
	dep[x]=dep[fa]+1,st[fir[x]=++Time][0]=x,lg[Time]=lg[Time>>1]+1;
	Id[dfn[x]=++tim]=x,siz[x]=1;
	f[x][0]=fa;
	rep(i,1,18)f[x][i]=f[f[x][i-1]][i-1];
	e(x)if(y^fa)dfs(y,x),st[++Time][0]=x,lg[Time]=lg[Time>>1]+1,siz[x]+=siz[y];
}
inline int Mn(int x,int y){
	return dep[x]<dep[y]?x:y;
}
inline int get(int l,int r){
	int p=lg[r-l+1];
	return Mn(st[l][p],st[r-(1<<p)+1][p]);
}
inline int lca(int x,int y){
	return get(min(fir[x],fir[y]),max(fir[x],fir[y]));
}
inline int dist(int x,int y){
	return dep[x]+dep[y]-dep[lca(x,y)]*2;
}
struct seg{
	int x,y;
}xd[N<<2];
inline void update(seg &a,int x,int y){
	if(dist(x,y)>dist(a.x,a.y))a={x,y};
}
inline void getup(int x){
	xd[x]=xd[L];
	int a=xd[L].x,b=xd[L].y,c=xd[R].x,d=xd[R].y;
	update(xd[x],a,d),update(xd[x],a,c),update(xd[x],b,d),update(xd[x],b,c),update(xd[x],d,c);
}
inline seg getup(seg x,seg l,seg r){
	x=l;
	int a=l.x,b=l.y,c=r.x,d=r.y;
	update(x,a,d),update(x,a,c),update(x,b,d),update(x,b,c),update(x,d,c);
	return x;
}
inline void build(int x,int l,int r){
	if(l==r)return xd[x]={Id[l],Id[l]},void();
	build(lc),build(rc),getup(x);
}
inline seg query(int x,int l,int r,int Ll,int Rr){
	if(OK)return xd[x];
	if(Rr<=mid)return query(lc,Ll,Rr);
	if(Ll>mid)return query(rc,Ll,Rr);
	return getup({0,0},query(lc,Ll,Rr),query(rc,Ll,Rr));
}
inline int jump(int x,int k){
	k=min(k,dep[x]-1);
	int p=0;
	while(k){
		if(k&1)x=f[x][p];
		k>>=1,p++;
	}
	return x;
}
inline void Main(){
	n=read(),lg[0]=-1;
	rep(i,2,n){
		int x=read(),y=read();
		add_(x,y),add_(y,x);
	}
	dfs(1,0);
	rep(p,1,18)rep(i,1,Time-(1<<p)+1)st[i][p]=Mn(st[i][p-1],st[i+(1<<p-1)][p-1]);
	build(Root);
	m=read();
	while(m--){
		int x=read(),k=read(),y=jump(x,k);
		seg now=query(Root,dfn[y],dfn[y]+siz[y]-1);
		cout <<max(dist(x,now.x),dist(x,now.y))<<' ';
	}
	cout <<'\n';
	repn(i)h[i]=0;
	cnt=Time=tim=0;
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}
```

---

## 作者：Daniel_yao (赞：1)

# [CF2033G Sakurako and Chefir](https://www.luogu.com.cn/problem/CF2033G) 全新做法

题解区大多都是倍增，少部分树链，但是好像都和我的做法不太一样。所以我决定写一篇题解。

以下令 $fa_{k}(a)$ 表示 $a$ 向根跳 $k$ 步到达的节点编号，$dep_a$ 为节点 $a$ 的深度，树的最大深度记为 $maxdep$。

首先可以暴力的考虑，对于查询 $(u,k)$，我们枚举 $fa_{0}(u)\to fa_{k}(u)$ 路径上的所有点 $v$。然后考虑 $v$ 的贡献，会发现贡献即为从 $u$ 到 $v$ 跳跃的步数加上从 $v$ 向下不与 $fa_{0}(a)\to fa_{k}(u)$ 重合的路径中能到达的最大深度的节点所需的步数。

发现前后的刻画都非常的暴力。我们先优化后面的计算贡献。

考虑 “不与 $fa_{0}(a)\to fa_{k}(u)$ 重合的路径中能到达的最大深度的节点所需的步数” 如何快速计算。假设从 $u$ 到 $v$，$v=fa_{x}(u)$。令 $y=fa_{x-1}(u)$，则原问题可刻画为：在 $v$ 的子树中除去 $y$ 的子树所留下来所有节点的 $dep$ 的最大值减去 $dep_v$。于是考虑对树进行树剖，然后可以发现 “在 $v$ 的子树中除去 $y$ 的子树所留下来所有节点” 的编号一定可以分为两段：$[dfn_v+1,dfn_y-1],[dfn_y+siz_y,dfn_u+siz_u-1]$。由于不带修，故用 $st$ 表维护 $dep$ 取最大值即可，此时的 $v$ 的贡献记为 $w_v$。

然后我们再优化前面的 “枚举 $fa_{0}(a)\to fa_{k}(u)$ 路径上的所有点 $v$” 的过程。考虑能不能在跳 $k$ 级祖先时快速利用连续的 $dfn$ 区间求得答案。你会发现存在一定的问题：如果单纯的用每一个 $w_v$ 取最大值是不行的，因为贡献还有前半部分 “从 $u$ 到 $v$ 跳跃的步数”。

集中注意力，可以得知将每一个 $w_v$ 加上 $maxdep + dep_v - 1$，一同放入 $st$ 表中查询最大值。即若某次询问 $(u,k)$，则答案为 $\max\limits_{v\in{fa_{0}(u)\to fa_{k}(u)}}\{w_v\}-(maxdep + dep_u - 1)$。前半部分就树剖维护 $st$ 表最大值快速求即可。

总结一下就是用两个 $st$ 表，一个维护 $dep$，一个维护 $w$，配合树剖计算总贡献即可。

时间复杂度 $O((n+q)\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls p<<1
#define rs p<<1|1
#define reg register 
#define For(i,l,r) for(reg int i=l;i<=r;++i)
#define FOR(i,r,l) for(reg int i=r;i>=l;--i)

using namespace std;

const int N = 2e5 + 10;

struct Node {
  int v, nx;
} e[N << 1];

int T, n, q, tot, idx, h[N], siz[N], son[N], dep[N], fa[N], top[N], dfn[N], id[N], st[N][24], w[N], maxdep, Dep[N];

void add(int u, int v) {
  e[++tot] = (Node){v, h[u]};
  h[u] = tot;
}

void clear_st() {
  For(i,1,n) {
    For(j,0,23) st[i][j] = 0;
  }
}

void clear() {
  tot = idx = maxdep = 0;
  For(i,1,n) {
    h[i] = siz[i] = son[i] = dep[i] = fa[i] = top[i] = dfn[i] = id[i] = w[i] = Dep[i] = 0;
  }
  clear_st();
}

void dfs(int x, int f) {
  fa[x] = f;
  dep[x] = dep[f] + 1;
  maxdep = max(maxdep, dep[x]);
  siz[x] = 1;
  int maxi = 0;
  for (int i = h[x]; i; i = e[i].nx) {
    int y = e[i].v;
    if(y == f) continue;
    dfs(y, x);
    Dep[x] = max(Dep[x], Dep[y] + 1);
    siz[x] += siz[y];
    if(maxi < siz[y]) {
      maxi = siz[y];
      son[x] = y;
    }
  }
}

void dfs1(int x, int tp) {
  top[x] = tp;
  dfn[x] = ++idx;
  id[idx] = x;
  if(son[x]) dfs1(son[x], tp);
  for (int i = h[x]; i; i = e[i].nx) {
    int y = e[i].v;
    if(y == fa[x] || y == son[x]) continue;
    dfs1(y, y);
  }
}

int ask(int l, int r) {
  if(l > r || r > n || l < 1) return 0;
  int k = __lg(r-l+1);
  return max(st[l][k], st[r-(1<<k)+1][k]);
}

void dfs2(int u) {
  for (int i = h[u]; i; i = e[i].nx) {
    int v = e[i].v;
    if(v == fa[u]) continue;
    if(fa[v]) {
      w[v] = max(0ll, max(ask(dfn[u]+1, dfn[v]-1), ask(dfn[v]+siz[v], dfn[u]+siz[u]-1)) - dep[u]) + maxdep - dep[u] + 1;
    }
    dfs2(v);
  }
}

int jp(int u, int k) {
  int ans = Dep[u];
  int x = u;
  k--;
  if(k == -1 || u == 1) return Dep[u];
  while(1) {
    if(k > (dfn[x] - dfn[top[x]])) {
      k -= (dfn[x] - dfn[top[x]] + 1);
      ans = max(ans, ask(dfn[top[x]], dfn[x]) - (maxdep - dep[u] + 1));
      x = fa[top[x]];
    } else {
      ans = max(ans, ask(dfn[x] - k, dfn[x]) - (maxdep - dep[u] + 1));
      break;
    }
  }
  return ans;
}

void solve() {
  cin >> n;
  clear();
  For(i,1,n-1) {
    int u, v;
    cin >> u >> v;
    add(u, v);
    add(v, u);
  }
  dfs(1, 0);
  dfs1(1, 1);

  For(i,1,n) st[i][0] = dep[id[i]];

  for (reg int j = 1; (1 << j) <= n; ++j) {
    for(reg int i = 1; i + (1 << j) - 1 <= n; ++i) {
      st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
    }
  }
  
  dfs2(1);

  For(i,1,n) st[i][0] = w[id[i]];

  for (reg int j = 1; (1 << j) <= n; ++j) {
    for(reg int i = 1; i + (1 << j) - 1 <= n; ++i) {
      st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
    }
  }

  cin >> q;
  while(q--) {
    int u, k;
    cin >> u >> k;
    k = min(k, dep[u] - 1);
    cout << jp(u, k) << ' ';
  }
  cout << '\n';
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：CJ_Fu (赞：1)

## [CF2033G Sakurako and Chefir](https://codeforces.com/problemset/problem/2033/G)

给定一个 $n$ 个节点以 1 为根的树，$q$ 次询问，给定 $u,k$，对于每次询问，你需要操作节点 $u$ 顺着边进行移动操作，满足：

1. 最多向树根（深度减小）方向移动 $k$ 次；
2. 向叶子（深度增加）方向移动任意次。

问操作结束后与原点 $u$ 的距离最大值。多组询问。

$\sum n\le 2\times 10^5,k\le n$

记 $f(0/1,u)$ 为 $u$ 的儿子中，子树内深度最/次深的 儿子节点编号，这个预处理下深度就能求了。这样可以做到 $O(qk)$。

搞个倍增 $g(i,u)$ 表示跳 $[0,2^i]$ 次的最大答案。

则有转移 $g(i,u)=\max(g(i-1,u),g(i-1,fa(i-1,u))+maxdep(fa(u))-dep(u))$。 $g(0,u)$ 为不为他自己的 $f$ 距离 $u$ 的距离。

就做完了，往上跳的时候累加跳过的距离并取 max 即可。注意不要走包含自己节点的子树（这就是为什么处理 $f(1,u)$）。时间复杂度 $O((n+q)\log k)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+7;
vector<int>e[maxn];
int n,q;
int dep[maxn],mxdep[maxn],f[maxn][2],g[19][maxn],fa[19][maxn];
void update(int u,int v){
    if(mxdep[f[u][0]]<=mxdep[v]){
        f[u][1]=f[u][0];
        f[u][0]=v;
        return;
    }
    if(mxdep[f[u][1]]<=mxdep[v]) f[u][1]=v;
}
void dfs(int u,int Fa){
    dep[u]=dep[Fa]+1;
    mxdep[u]=dep[u];
    fa[0][u]=Fa;
    for(int v:e[u]) if(v!=Fa)
        dfs(v,u),mxdep[u]=max(mxdep[u],mxdep[v]);
}
void dfs1(int u,int Fa){for(int v:e[u]) if(v!=Fa) dfs1(v,u),update(u,v);}
void init(){
    for(int i=1;i<=n;i++){
        if(f[fa[0][i]][0]==i){
            if(!f[fa[0][i]][1])g[0][i]=1;
            else g[0][i]=mxdep[f[fa[0][i]][1]]-dep[fa[0][i]]+1;
        }else
            g[0][i]=mxdep[f[fa[0][i]][0]]-dep[fa[0][i]]+1;
    }
    for(int i=1;i<=n;i++) f[i][0]=f[i][1]=0;
    for(int j=1;j<=17;j++)
        for(int i=1;i<=n;i++)
            fa[j][i]=fa[j-1][fa[j-1][i]];
    for(int j=1;j<=17;j++)
        for(int i=1;i<=n;i++)
            g[j][i]=max(g[j-1][i],g[j-1][fa[j-1][i]]+dep[i]-dep[fa[j-1][i]]);
}
void solve(){
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    dfs(1,0);
    dfs1(1,0);
    init();
    cin>>q;
    for(int i=1,u,k;i<=q;i++){
        cin>>u>>k; k=min(k,dep[u]-1);
        int res=mxdep[u]-dep[u],now=0;
        for(int j=17;~j;j--)
            if(k&(1<<j)) res=max(res,g[j][u]+now),now+=dep[u]-dep[fa[j][u]],u=fa[j][u];
        cout<<res<<" \n"[i==q];
    }
    for(int i=1;i<=n;i++) e[i].clear();
}
signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

给定一个 $n$ 个点的树，$q$ 次询问，每次询问给出一个点 $u$ 和一个自然数 $k$，你需要从 $u$ 出发走到树上的某一个节点（要求至多从儿子走向父亲 $k$ 次），求你可以走到的节点离 $u$ 的最大距离。

$T$ 组数据。$1\leq \sum n,\sum q\leq 2\times 10^5$。

## 思路

很有启发意义的一道题。提供一个基于重链剖分的做法。

首先我们发现最优的走法一定形如先选定一个 $t$（要求 $0\leq t\leq k$），走到 $u$ 的 $t$ 级祖先 $p$ 上，然后从 $p$ 出发，不走回头路，走到以 $p$ 为根的子树内的某一个节点，则走的距离就是答案。

考虑对原树进行重链剖分，然后用它去模拟这个过程。

![](https://cdn.luogu.com.cn/upload/image_hosting/09re8ls8.png)

重链剖分可以求树上 $k$ 级祖先（如果你不会，出门左转 [模板题](https://www.luogu.com.cn/problem/P5903)，虽然这道题理论上是为长链剖分准备的）。大致思想就是不停的跳重链，直到所求的点的重链上，然后通过 dfn 序计算出所求的点。我们可以利用这个过程去求解这道题。

对于每个点，我们可以一遍 dfs 求出从每个点 $i$ 出发，不离开以 $u$ 为根的子树，可以走的最远距离 $h_0(i)$。然而你发现这个东西用处不大，因为可能会引来走回头路的问题。由于对于每个点，回头路只会是一条边，所以不妨再记录一个 $h_1(i)$ 表示每个点 $i$ 出发，不离开以 $u$ 为根的子树，不走 $h_0(i)$ 中 $i$ 的儿子，可以走出的最远距离。显然这个也可以在 dfs 的时候求得。

然后可以考虑怎么求一段重链的答案，对于重链的底端我们需要特殊讨论（因为我们不知道这个点从哪个点跳过来的），而对于重链的剩余部分，我们不妨求出一个 $h^*(i)$ 表示不走 $i$ 的重儿子可以走出的最远距离（这个可以由 $h_0,h_1$ 分类讨论得到）。那么从 $u$ 走到重链上的点 $i$（除底端）的距离就是 $\mathrm{dep}(u)-\mathrm{dep}(i)+h^*(i)$。所以我们需要用一个数据结构来维护 $-\mathrm{dep}(i)+h^*(i)$ 的最大值，线段树或 ST 表均可。实现用的是线段树。

时间复杂度 $O(n\log n)$ 或 $O(n\log^2 n)$，假设 $n,q$ 同阶。

Bonus：利用这个做法，我们可以支持修改一条边的边权，或求出最后走到哪个点最优。

## 代码

```cpp
#include <bits/stdc++.h>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

const int N = 2e5 + 5;
int n, q;
vector<int> g[N];
int top[N], seg[N], rev[N], son[N], siz[N], dep[N], father[N];
int hgt[N][2], pos[N][2];

void dfs1(int u, int fa){
    dep[u] = dep[fa] + 1, father[u] = fa, siz[u] = 1;
    for(int v : g[u]){
        if(v == fa) continue;
        dfs1(v, u);
        if(hgt[v][0] + 1 > hgt[u][0]){
            hgt[u][1] = hgt[u][0], pos[u][1] = pos[u][0];
            hgt[u][0] = hgt[v][0] + 1, pos[u][0] = v;
        }
        else if(hgt[v][0] + 1 > hgt[u][1]) hgt[u][1] = hgt[v][0] + 1, pos[u][1] = v;
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int fa){
    if(son[u]){
        top[son[u]] = top[u], seg[son[u]] = ++seg[0], rev[seg[0]] = son[u];
        dfs2(son[u], u);
    }
    for(int v : g[u]){
        if(v == fa || v == son[u]) continue;
        top[v] = v, seg[v] = ++seg[0], rev[seg[0]] = v;
        dfs2(v, u);
    }
}

struct sgt{
    int t[N << 2];

    void build(int i, int l, int r){
        t[i] = INT_MIN;
        if(l == r) return;
        build(ls, l, mid), build(rs, mid + 1, r);
        t[i] = max(t[ls], t[rs]);
    }

    void update(int p, int v, int i, int l, int r){
        if(l == r) return (t[i] = v), void();
        if(p <= mid) update(p, v, ls, l, mid);
        else update(p, v, rs, mid + 1, r);
        t[i] = max(t[ls], t[rs]);
    }

    int query(int ql, int qr, int i, int l, int r){
        if(ql > qr) return INT_MIN;
        if(ql <= l && r <= qr) return t[i];
        int res = INT_MIN;
        if(ql <= mid) res = max(res, query(ql, qr, ls, l, mid));
        if(mid < qr) res = max(res, query(ql, qr, rs, mid + 1, r));
        return res;
    }
} t;

int query(int u, int k){
    int exp = dep[u] - k, ans = -dep[u], lst = 0;
    while(dep[top[u]] > exp){
        if(pos[u][0] != lst) ans = max(ans, -dep[u] + hgt[u][0]);
        else ans = max(ans, -dep[u] + hgt[u][1]);
        ans = max(ans, t.query(seg[top[u]], seg[u] - 1, 1, 1, seg[0]));
        lst = top[u], u = father[top[u]];
    }
    if(pos[u][0] != lst) ans = max(ans, -dep[u] + hgt[u][0]);
    else ans = max(ans, -dep[u] + hgt[u][1]);
    ans = max(ans, t.query(seg[u] - (dep[u] - exp), seg[u] - 1, 1, 1, seg[0]));
    return ans;
}

void solve(){
    cin >> n;
    for(int i=1,u,v;i<n;i++){
        cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    top[1] = seg[0] = seg[1] = rev[1] = 1;
    dfs1(1, 0), dfs2(1, 0);
    t.build(1, 1, seg[0]);
    for(int i=1;i<=n;i++){
        if(pos[i][0] == son[i]) t.update(seg[i], hgt[i][1] - dep[i], 1, 1, seg[0]);
        else t.update(seg[i], hgt[i][0] - dep[i], 1, 1, seg[0]);
    }
    cin >> q;
    while(q--){
        int u, k; cin >> u >> k;
        cout << query(u, min(k, dep[u] - 1)) + dep[u] << ' ';
    }
    cout << '\n';
}

void clear(){
    seg[0] = 0;
    for(int i=1;i<=n;i++){
        g[i].clear();
        hgt[i][0] = hgt[i][1] = 0;
        pos[i][0] = pos[i][1] = 0;
        son[i] = 0;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t; cin >> t;
    while(t--) solve(), clear();
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：_Fatalis_ (赞：1)

写一手题解纪念一下第一次 div.3 赛时切 G。

题意：给定一个 $n$ 个节点的树，$q$ 次询问，给定 $u,k$，对于每次询问，你需要操作节点 $u$ 顺着边进行移动操作，满足： 最多向树根（深度减小）方向移动 $k$ 次；向叶子（深度增加）方向移动任意次。 问操作结束后与原点 $u$ 的距离最大值。多组询问。

分两类维护，一类路径为直接向子树走最深的点，一类为向上跳 $x (\le k)$ 次然后再向子树内走最深的点。

第一类好维护，考虑第二类如何维护：

记号：$dep_u$：深度，$h_u$：以 $u$ 为根节点的子树的最深节点深度。

先离线询问，dfs 整棵树（按点 dfs 序处理询问），对于访问到的点维护一个数据结构，支持单点查，区间最大值：维护从当前节点到根节点路径上每一个节点的 $h_u - 2\cdot dep_u$。

于是对于每一个点的询问即可化为在线段树上查 $[\max\{1, dep_u - k\}, dep_u - 1]$ 这个区间内最大的 $h_v - 2\cdot dep_v$，与 $h_u$ 加和即 $h_u + h_v - 2\cdot dep_v$。

注意到 $v$ 是这条简单路径的 $lca$ 那么这条式子表达的就是这条简单路径的长度。于是求最大值即可。

需要注意的是：这条式子 $h_v$ 不能计入 dfs 进入的某个子树的贡献，因为你不能先往上跳到祖先又跳回来（不属于该类贡献）。所以需要用 set 简单维护一下当前所有子节点的 $h_v$ 值，每次进子树就删除这个子节点的 $h_v$ 并重新计算最大 $h_v$。

具体实现请看代码。

```cpp
// Copyright 2024 Lotuses
#include <bits/stdc++.h>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

// #define int long long
typedef long long ll;
typedef unsigned long long ull;
typedef std::vector<int> vi;
typedef std::pair<int, int> pii;
#define sint static int

const int maxn = 2e5 + 10, inf = 0x3f3f3f3f;
vi G[maxn];
std::vector<pii> qq[maxn];

std::multiset<int, std::greater<int> > hs[maxn];
int dep[maxn], fa[maxn], maxh, h[maxn];
void dfs(int u) {
    maxh = std::max(maxh, dep[u]);
    hs[u].clear();
    for (int v : G[u]) {
        if (v == fa[u]) continue;
        fa[v] = u; dep[v] = dep[u] + 1;
        dfs(v);
        hs[u].insert(h[v]);
    }
    h[u] = dep[u];
    for (int v : G[u]) {
        if (v == fa[u]) continue;
        h[u] = std::max(h[u], h[v]);
    }
}
struct Tree {
    struct Node {
        int l, r, lc, rc, max;
    } t[maxn << 2];
    int cnt;
    int bt(int l, int r) {
        int u = ++cnt;
        t[u] = { l, r, -1, -1, -inf };
        if (l < r) {
            int mid = (l + r) >> 1;
            t[u].lc = bt(l, mid);
            t[u].rc = bt(mid + 1, r);
        }
        return u;
    }
    void mod(int u, int p, int x) {
        if (t[u].l == t[u].r) t[u].max = x;
        else {
            int mid = (t[u].l + t[u].r) >> 1;
            if (p <= mid) mod(t[u].lc, p, x);
            else mod(t[u].rc, p, x);
            t[u].max = std::max(t[t[u].lc].max, t[t[u].rc].max);
        }
    }
    int query(int u, int l, int r) {
        if (l > r) return -inf;
        if (t[u].l == l && t[u].r == r) {
            return t[u].max;
        } else {
            int mid = (t[u].l + t[u].r) >> 1;
            if (r <= mid) return query(t[u].lc, l, r);
            else if (l > mid) return query(t[u].rc, l, r);
            else return std::max(query(t[u].lc, l, mid), query(t[u].rc, mid + 1, r));
        }
    }
} t;
int ans[maxn];
void qdfs(int u) {
    for (auto [k, i] : qq[u]) {
        ans[i] = h[u] - dep[u];
        ans[i] = std::max(ans[i], dep[u] + t.query(1, std::max(1, dep[u] - k), dep[fa[u]]));
    }
    for (int v : G[u]) {
        if (v == fa[u]) continue;
        hs[u].erase(hs[u].find(h[v]));
        if (!hs[u].empty()) t.mod(1, dep[u], *hs[u].begin() - dep[u] * 2);
        else t.mod(1, dep[u], dep[u] - dep[u] * 2);
        qdfs(v);
        hs[u].insert(h[v]);
    }
}

int main() {
    int T;
    read(T);
    while (T--) {
        int n, q;
        read(n);
        for (int i = 1; i <= n; i++) G[i].clear();
        for (int i = 1; i < n; i++) {
            sint u, v; read(u, v);
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        dep[1] = 1; fa[1] = 1;
        maxh = 0; t.cnt = 0;
        dfs(1);
        t.bt(1, maxh);
        
        read(q);
        for (int i = 1; i <= n; i++) qq[i].clear();
        for (int i = 1; i <= q; i++) {
            sint v, k; read(v, k);
            qq[v].push_back({k, i});
        }
        qdfs(1);
        for (int i = 1; i <= q; i++) {
            printf("%d ", ans[i]);
        }
        puts("");
    }
    return 0;
}

```

---

## 作者：MattL (赞：1)

~~本以为很难的div3G~~

难度 2200，树，倍增

---
题意很简单，转化题意反而会影响思考，这里不再转述。

注意到，一定是先往上跳，再往下走，这样子一定是不劣的，否则往下走了再往上跳就走回头路了。

（下文深度指节点到叶子节点的最大距离）

不难想到 $\mathcal O(nq)$ 做法：从每个点开始，往上跳 $k$ 次，统计最大的除 $u$ （询问节点）所在子树外的所有子树内最大的深度。

形式化地，我们用 $fa_{u,i}$ 表示节点 $u$ 的 $i$ 级祖先、$tree_u$ 表示以 $u$ 为根的子树，即：

$$ans_{u,k}=\max_{i=0}^{k}\max_v^{v\in tree_{{fa}_{u,k}},v\notin tree_{{fa}_{u,k-1}}}i+dep_v$$

考虑优化，不难发现往上跳 $k$ 次的这个过程可以用树上倍增来代替，时间复杂度 $\mathcal O(q\log n)$

附上官方英文题解，跟本题解是一个意思，~~没有翻译，思路及本题解也是自己想的，无抄袭，侵权删。~~
>In each query, Chefir can ascend from vertex $v$ by no more than $k$. To maximize the distance, we need to first ascend $x$ times ($0 \le x \le k$), and then descend to the deepest vertex.
>
>For each vertex $u$, we will find $maxd[v].x$ — the distance to the farthest descendant of vertex $u$. We will also need $maxd[v].y$ — the distance to the farthest descendant of vertex $u$ from a **different** subtree of vertex $v$, which will allow us to avoid counting any edges twice when searching for the answer.
>
>Now we can construct binary lifts. The lift by $2^i$ from vertex $u$ will store information about all vertices from $u$ to the $(2^i)$\-th ancestor, excluding vertex $u$ itself.
>
>The value of the lift from vertex $u$ by $1$ (i.e., to its ancestor $p$) will be calculated as follows: if $maxd[v].x + 1 < maxd[p].x$, then the value is equal to $maxd[p].x - h(p)$, and $maxd[p].y - h(p)$ otherwise. Here, $h(p)$ is the distance from vertex $p$ to the root. The subsequent lifts will be computed as the maximums of the corresponding values. The constructed maximums will not account for cases where any edge was traversed twice.
>
>Thus, by ascending from vertex $v$ by $k$, we will be able to find the best value of the form $max_{depth}-h(u)$, and by adding $h(v)$ to it, we will obtain the distance to the desired vertex.

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ls (now<<1)
#define rs (now<<1|1)
#define LL long long
#define f(i,n) for(int i=1;i<=n;i++)
#define f_(i,n) for(int i=n;i>=1;i--)
#define ff(i,a,b) for(int i=a;i<=b;i++)
#define ff_(i,a,b) for(int i=a;i>=b;i--)
#define pi pair<int,int> 
#define pb push_back
#define vi vector<int>
#define yes cout<<"YES"<<endl
#define no cout<<"NO"<<endl
#define fs(i,s) for(int i=0;i<s.size();i++)
#define re return
#define con continue
#define bre break
#define mkp make_pair



const int N=2e5+10,LO=25;
int ans[N][LO],fa[N][LO];
int n,q,a[N],dep[N],maxn[N],maxx[N],maxi[N],maxxi[N];
vector<int> to[N];
void dfs(int k,int faa){
	dep[k]=dep[faa]+1;
	maxn[k]=0;
	maxx[k]=-INT_MAX;
	fa[k][0]=faa;
	for(auto i:to[k])if(i!=faa){
		dfs(i,k);
		if(maxn[i]+1>maxn[k])maxx[k]=maxn[k],maxn[k]=maxn[i]+1,maxi[k]=i;
		else if(maxn[i]+1>maxx[k])maxx[k]=maxn[i]+1;
		else if(maxx[i]+1>maxn[k])maxx[k]=maxn[k],maxn[k]=maxx[i]+1,maxi[k]=i;
		else if(maxx[i]+1>maxx[k])maxx[k]=maxx[i]+1;
	}
}void dfss(int k){
	for(auto i:to[k])if(i!=fa[k][0]){
		dfss(i);
	}if(maxi[fa[k][0]]!=k)ans[k][0]=maxn[fa[k][0]];
	else if(maxx[fa[k][0]]>=0)ans[k][0]=maxx[fa[k][0]];
}
void solve(){
	cin>>n;
	f(i,n)to[i].clear();
	int u,v,k,kk;
	f(i,n-1)cin>>u>>v,to[u].pb(v),to[v].pb(u);
	dfs(1,0);
	dfss(1);
	for(int i=1;i<=__lg(n);i++)
		for(int o=1;o<=n;o++)
			fa[o][i]=fa[fa[o][i-1]][i-1],
			ans[o][i]=max(ans[o][i-1]-(1<<(i-1)),ans[fa[o][i-1]][i-1]);
	cin>>q;
	while(q--){
		cin>>u>>k;
		k=min(dep[u]-1,k);kk=k;
		int tmp=0;int anss=maxn[u];
		while(k){
			if(k&(1<<tmp)){
				k^=(1<<tmp);
				anss=max(anss,ans[u][tmp]+(kk-k));
//				cout<<ans[u][tmp]<<' '<<(kk-k)<<'\n';
				u=fa[u][tmp];
			}tmp++;
		}
		cout<<anss<<' ';
	}cout<<'\n';
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    int T;
    
    cin>>T;
//     T=1;
    
	while(T--)
        solve();


    return 0;
}
```
---
除此之外，我们还可以发现往上跳 $k$ 次的，实际上是在一条链上统计答案，故可以先树链剖分，再用 st 表或者线段树等数据结构维护链上的最大值。时间复杂度 $\mathcal O(q \log n)$

~~树剖太难写了就没写~~

---

## 作者：迟暮天复明 (赞：0)

长链剖分题解。

长链剖分把每个点往下最深的子结点视为重儿子，可以证明从叶子节点走到根节点的切换次数不超过 $O(\sqrt N)$ 次。

本题中，考虑向上跳的过程中，如果经过的边 $\{u,fa(u)\}$ 是重边，那么从 $fa(u)$ 往下走就只能走次长链。否则，就可以走最长链。

跳轻边的次数不超过 $\sqrt N$，可以暴力跳。跳重链的过程中，就需要整体维护整一条链上的最优解了。

设 $F(u),G(u)$ 分别为 $u$ 往下的最长链长和次长链长，则从点 $u$ 走到点 $X$ 再往下走的话，最终答案就是 $dep(u)-dep(X)+F(X)/G(X)$。在重链上的时候，此式就可以改成 $dep(u)-dep(X)+G(X)$。所以只需要求出一条链上 $G(X)-dep(x)$ 的最大值即可。用线段树或者 ST 表维护都可以。

于是从 $u$ 开始不断往上跳，过程中维护答案即可。时间复杂度 $O(N\sqrt N)$，但是我写的线段树 $O(N\sqrt N\log N)$ 跑的也很快。

---

## 作者：bluewindde (赞：0)

奶龙题。

> 题意：给定一棵树，多次询问在以节点 $v$ 的 $k$ 级祖先为根的子树内，从点 $v$ 出发的最长简单路径。

显然可以将所求路径分为终点在 $v$ 的子树内和终点在 $v$ 的子树外，前者容易处理。

考虑其他节点贡献的路径，容易想到枚举 $v$ 每个合法祖先 $u$ 作为 LCA，查询 $v$ 所在的子树与 $u$ 的其他子树之间的贡献。贡献可以使用主席树处理。具体而言，由树上路径计算方式 $d = dis_u + dis_v - 2 \cdot dis_{lca}$，设 $rt_u$ 表示记录节点 $u$ 的子树内所有点的深度的主席树，查询时减去 $v$ 所在子树的所有点的深度，并查询最大深度。

于是得到一个 $O(qn \log n)$ 的做法，考虑优化。

发现每次查询时跳了很多祖先，而对于一个确定的祖先与其确定的子树，没有必要查询多次。使用树上启发式合并：预处理重儿子的答案作为该节点的权值，树剖查询链最大值，跳轻链时再使用前述方法。优化至 $O(q \log^2 n)$，可以通过。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int inf = 1e9;

int lg[200005];

int n, q;
vector<int> vec[200005];

int rt[200005];
struct node {
    int ls, rs, val;
} d[16000005];
int cnt;
static inline int clone(int p) {
    d[++cnt] = d[p];
    return cnt;
}
static inline int insert(int x, int s, int t, int c, int p) {
    p = clone(p);
    if (s == t) {
        d[p].val += c;
        return p;
    }
    int mid = (s + t) >> 1;
    if (x <= mid)
        d[p].ls = insert(x, s, mid, c, d[p].ls);
    else
        d[p].rs = insert(x, mid + 1, t, c, d[p].rs);
    d[p].val = d[d[p].ls].val + d[d[p].rs].val;
    return p;
}
static inline int merge(int s, int t, int u, int v) {
    if (!u || !v)
        return clone(u | v);
    int p = ++cnt;
    if (s == t) {
        d[p].val = d[u].val + d[v].val;
        return p;
    }
    int mid = (s + t) >> 1;
    d[p].ls = merge(s, mid, d[u].ls, d[v].ls);
    d[p].rs = merge(mid + 1, t, d[u].rs, d[v].rs);
    d[p].val = d[d[p].ls].val + d[d[p].rs].val;
    return p;
}
static inline int query(int s, int t, int u, int v) {
    if (s == t)
        return d[v].val - d[u].val > 0 ? s : -inf;
    int mid = (s + t) >> 1;
    if (d[d[v].rs].val - d[d[u].rs].val > 0)
        return query(mid + 1, t, d[u].rs, d[v].rs);
    return query(s, mid, d[u].ls, d[v].ls);
}

int dep[200005];
int st[200005][20];
int siz[200005];
int son[200005];
int top[200005];
int dfn[200005], dfn_clock;
int nfd[200005];
int pre[200005][20];
static inline void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    st[u][0] = fa;
    for (int i = 1; i <= 18; ++i)
        st[u][i] = st[st[u][i - 1]][i - 1];
    siz[u] = 1;
    rt[u] = insert(dep[u], 1, n, 1, rt[u]);
    for (auto v : vec[u]) {
        if (v == fa)
            continue;
        dfs(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
        rt[u] = merge(1, n, rt[u], rt[v]);
    }
}
static inline void dfs2(int u) {
    nfd[dfn[u] = ++dfn_clock] = u;
    if (!son[u]) {
        pre[dfn[u]][0] = -inf;
        return;
    }
    top[son[u]] = top[u];
    dfs2(son[u]);
    pre[dfn[u]][0] = query(1, n, rt[son[u]], rt[u]) - 2 * dep[u];
    for (auto v : vec[u]) {
        if (v == st[u][0] || v == son[u])
            continue;
        top[v] = v;
        dfs2(v);
    }
}
static inline int jump(int x, int k) {
    for (int i = 0; i <= 18; ++i)
        if ((k >> i) & 1)
            x = st[x][i];
    return x;
}
static inline int LCA(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    u = jump(u, dep[u] - dep[v]);
    if (u == v)
        return u;
    for (int i = 18; i >= 0; --i)
        if (st[u][i] != st[v][i]) {
            u = st[u][i];
            v = st[v][i];
        }
    return st[u][0];
}

static inline void build() {
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int j = 1; j <= 18; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            pre[i][j] = max(pre[i][j - 1], pre[i + (1 << (j - 1))][j - 1]);
}
static inline int query(int l, int r) {
    int len = lg[r - l + 1];
    return max(pre[l][len], pre[r - (1 << len) + 1][len]);
}

static inline void solve() {
    cin >> n;
    for (int i = 1; i <= cnt; ++i)
        d[i] = {0, 0, 0};
    cnt = dfn_clock = 0;
    for (int i = 1; i <= n; ++i) {
        vec[i].clear();
        rt[i] = son[i] = top[i] = 0;
        for (int j = 0; j <= 18; ++j)
            st[i][j] = pre[i][j] = 0;
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs(1, 0);
    top[1] = 1;
    dfs2(1);
    build();
    cin >> q;
    while (q--) {
        int x, k;
        cin >> x >> k;
        int u = st[x][0];
        int v = max(jump(x, k), 1);
        int ans = min(k, dep[u]);
        while (u && dep[u] > dep[v] && top[u] != top[v]) { // DSU on tree
            int w = query(1, n, rt[jump(x, dep[x] - dep[u] - 1)], rt[u]);
            ans = max(ans, dep[x] + w - 2 * dep[u]);
            if (dfn[top[u]] < dep[u])
                ans = max(ans, dep[x] + query(dfn[top[u]], dfn[u] - 1));
            u = st[top[u]][0];
        }
        if (dep[u] >= dep[v]) {
            int w = query(1, n, rt[jump(x, dep[x] - dep[u] - 1)], rt[u]);
            ans = max(ans, dep[x] + w - 2 * dep[u]);
            if (dfn[v] < dfn[u])
                ans = max(ans, dep[x] + query(dfn[v], dfn[u] - 1));
        }
        // 这是暴力的实现方式
        // int ans = 0;
        // int u = st[x][0];
        // --k;
        // while (u && k >= 0) {
        //     int w = query(1, n, rt[jump(x, dep[x] - dep[u] - 1)], rt[u]);
        //     ans = max(ans, dep[x] + w - 2 * dep[u]);
        //     u = st[u][0];
        //     --k;
        // }
        ans = max(ans, query(1, n, 0, rt[x]) - dep[x]);
        cout << ans << ' ';
    }
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    cout.flush();
    return 0;
}
```

---

