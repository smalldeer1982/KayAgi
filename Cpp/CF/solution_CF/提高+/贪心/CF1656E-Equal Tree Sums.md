# Equal Tree Sums

## 题目描述

You are given an undirected unrooted tree, i.e. a connected undirected graph without cycles.

You must assign a nonzero integer weight to each vertex so that the following is satisfied: if any vertex of the tree is removed, then each of the remaining connected components has the same sum of weights in its vertices.

## 说明/提示

In the first case, when removing vertex $ 1 $ all remaining connected components have sum $ 5 $ and when removing vertex $ 3 $ all remaining connected components have sum $ 2 $ . When removing other vertices, there is only one remaining connected component so all remaining connected components have the same sum.

## 样例 #1

### 输入

```
2
5
1 2
1 3
3 4
3 5
3
1 2
1 3```

### 输出

```
-3 5 1 2 2
1 1 1```

# 题解

## 作者：I_am_Accepted (赞：11)

### Preface

$\text{E<D}$ 实锤，$4$ 分钟写掉 $\text{E}$。

### Analysis

无向无根树？首先想到**黑白间隔染色**。

设 $deg_i$ 表示节点 $i$ 在树上的度。

**构造：** 对于节点 $x$，若为黑节点，值设为 $deg_x$，否则设为 $-deg_x$。

显然任意一棵树这样权值和为 $0$。

考虑删掉一个节点后形成多个连通块。每个连通块的权值和一定相同，且为 $\pm1$。（证明留给读者 doge）

### Code

[Link](https://codeforces.com/contest/1656/submission/150891549)

---

## 作者：Shunpower (赞：8)

## 思路

首先看到相等，我们就能想到各种 $1$ 和 $-1$ 相互抵消变成 $0$。

所以我们令 $sum_x$ 表示 $x$ 为顶点的子树和。那么原来的要求其实就是：

$$
sum_{son_1}=sum_{son_2}=\cdots=sum_{son_k}=sum_1-sum_x
$$

$son_1,son_2,\cdots,son_k$ 分别表示 $x$ 的 $k$ 个儿子。当然，$x\neq 1$。

令 $x$ 的权值为 $a_x$，很容易发现：

$$
\ a_x=sum_x-\sum\limits_{i=1}^{k}sum_{son_i}
$$

接下来令 $x$ 的度数为 $p$，那么它儿子的个数 $k$ 其实可以化掉了，化成 $k=p-1$，而计算 $a_x$ 的柿子也可以随之变化为：
$$
a_x=sum_x-(p-1)(sum_1-sum_x)=sum_1-p(sum_1-sum_x)
$$

到这里我们的基础部分就搞完了！接下来我们要用我们最开始的想法来处理这个柿子。

> 首先看到相等，我们就能想到各种 $1$ 和 $-1$ 相互抵消变成 $0$。

那么我们令 $sum_1=0$。

回代，分别回代到转化 $sum_{son}$ 的那个式子和刚刚转化 $a_x$ 的那个式子，我们可以得到这样的两个柿子：

$$
\begin{cases}
a_x=0-p(0-sum_x)=p\cdot sum_x\\
\forall i\in[1,k],sum_{son_i}=0-sum_x=-sum_x
\end{cases}
$$

我们来用第二个柿子，令 $x$ 的深度为 $d_x$ 并以此类推，使 $sum_x=(-1)^{d_x}$，就可以满足第二个柿子的要求了。之所以我们这样转化 $sum_x$，是因为我们发现我们可以让它和深度挂钩，以使得在 $x=1$ 的时候依然成立。

那么继续回代，可以得到 $a_x=p\cdot (-1)^{d_x}$。

那么问题就结束了。容易发现这样构造出来的点权在菊花上时，根节点的点权可以在满足要求的 $-99999\leqslant a_1\leqslant 99999$ 之间，这个就看 $d_1$ 的取值是 $1$ 还是 $0$ 了。

而由于树上任何一点 $p\geqslant1$，并且 $\forall i\in \mathbb{R}, (-1)^i>0$，所以这个构造方案是对的。

## 代码

```
//Author:Zealous_YH
#include <bits/stdc++.h>
#define ET return 0
#define pb push_back
#define vr vector
#define pt puts("")
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
using namespace std;
const int N=1e5+10;
int T;
int n;
int a[N];
vr <int> p[N];
void dfs(int x,int f,int dep){
	a[x]=p[x].size()*pow(-1,dep);
	fv(i,p[x]){
		if(p[x][i]!=f){
			dfs(p[x][i],x,dep+1);
		}
	}
}
void solve(){
	cin>>n;
	fr1(i,1,n){
		p[i].erase(p[i].begin(),p[i].end());
	}
	fr1(i,1,n-1){
		int x,y;
		cin>>x>>y;
		p[x].pb(y);
		p[y].pb(x);
	}
	dfs(1,1,0);
	fr1(i,1,n){
		cout<<a[i]<<" ";
	}
	pt;
}
int main(){
	cin>>T;
	while(T--){
		solve();
	}
	ET;
}
//Teens-in-Times
//HJL 2004.06.15
//Everything For Ji.
//Everything For Lin.
//Everything For You.
```

[AC 记录](https://www.luogu.com.cn/record/73557664)

---

## 作者：王熙文 (赞：2)

## 思路

结论：将树黑白染色（与 father 异色）后若为黑色则点的权值为度数否则为相反数，此时满足要求。

证明：

首先，根据每一条边会同时产生 $-1$ 和 $1$ 的贡献（增加了黑点和白点的读书）可知，整棵树的权值为 $0$。

对于一个点 $u$，满足要求的条件是它的所有子树的权值和均相等（其实也得算父亲上面的连通块，不过如果将这个点设为根则那个连通块也是它的一个子树）。对于每个子树，如果 $u$ 的在那个子树中的儿子节点不与 $u$ 有边，则这个树的权值之和为 $0$。因为每个儿子节点与 $u$ 异色，所以它们之间同色，与 $u$ 的边产生的贡献就抵消了。因为剩下的权值之和为 $0$，所以每一棵子树的权值和是相等的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;

int tot=0,var[200010],nxt[200010],head[100010];

void add(int u,int v)
{
	var[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}

int in[100010];

int color[100010];

void dfs(int u,int fa)
{
	color[u]=(!color[fa]);
	for(int i=head[u]; i; i=nxt[i])
	{
		int v=var[i];
		if(v==fa) continue;
		dfs(v,u);
	}
}

int main()
{
	int t; cin>>t; while(t--)
	{
		tot=0;
		int u,v;
		cin>>n;
		for(int i=1; i<=n; ++i) head[i]=in[i]=0;
		for(int i=1; i<=n-1; ++i) cin>>u>>v,add(u,v),add(v,u),++in[u],++in[v];
		dfs(1,0);
		for(int i=1; i<=n; ++i) cout<<(color[i]?1:-1)*in[i]<<' '; cout<<'\n';
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：2)

## 思路

上来一眼，对树进行黑白染色。染色之后，对于 $u$，如果是黑色，那么权值就是度数；否则就是度数相反数。然后就做完了。

时间复杂度 $O(n)$。

证明：

对于一个点 $u$，它的父亲和儿子一定都是和它相反的颜色。因此，它的度数 $d$，在每个父亲和儿子中都会有体现。而 $u$ 和它的父亲和儿子的颜色显然不同，所以这个度数就一正一负求一个总和抵消了。对于每一个 $u$，它的度数都能抵消，因此，整个树的权值和就是 $0$。

然后，考虑去掉 $u$ 会发生什么。假设 $u$ 的度数是 $d$，那么去掉之后，它的父亲和所有的儿子都会分开，父亲和每一个儿子所在的连通块，都会少 $u$ 这一个度，所以相对值是不变的，要么是 `-1` 要么是 `1`（这个取决于 $u$ 是黑色还是白色，但并不影响结果）。

证毕。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=100005;
int col[MAXN],d[MAXN];
vector<int> E[MAXN];
void dfs(int u,int fa){
	col[u]=!col[fa];
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		if(v==fa) continue;
		dfs(v,u);
	}
}
int main(){
	int T; cin>>T;
	while(T--){
		int n; cin>>n;
		for(int i=1;i<=n;i++) E[i].clear(),col[i]=d[i]=0;
		for(int i=1;i<n;i++){
			int u,v; cin>>u>>v;
			E[u].push_back(v);
			E[v].push_back(u);
			d[u]++; d[v]++;
		}dfs(1,0);
		for(int i=1;i<=n;i++){
			if(col[i]) cout<<d[i]<<" ";
			else cout<<-d[i]<<" "; 
		}cout<<endl;
	}
	return 0;
}

```

---

## 作者：是青白呀 (赞：1)

## 方法一.自定权值倒推
关键词：列方程。

读完题后，想到每个点的权值有一定**规律性**，考虑画出一棵树并尝试填入权值以找规律。

![](https://cdn.luogu.com.cn/upload/image_hosting/ejyoj1rm.png)

这是样例中第一组数据的树。设编号1-5的结点权值分别为 $a$、$b$、$c$、$d$、$e$。很容易想到在移除叶子节点时，一定满足连通块权值相等，因为移除叶子节点不会产生新的连通块。所以我们只考虑移除非叶子节点的情况。

分别移除结点1和结点3，可以得到下面的方程：

$\begin{cases}b=c+d+e\\d=e\\a+b=d\end{cases}$ 

如果满足权值上述方程，则一定满足题目要求。

**观察可得出结论：删除度为 $x$ 的结点可以得到 $x-1$ 个可用方程。由于有 $y$ 个结点的树上结点度的和为 $2y-2$，所以每棵树我们都能得到 $y-2$ 个方程。故确定树上任两个点的权值后，仍可以找到解。**

故可以找到方法一：**选择父节点不相同的两个叶子节点赋任意满足条件的值，后从叶子节点往根节点逐步推导每个点的值。**

## 方法二.规律归纳

顺方法一的思路继续往下，多次试验方程可行取值可以发现——相邻两节点权值**必定一负一正**，可以想到给树**染色**。同时，在确定权值时可以发现下图情况。
![](https://cdn.luogu.com.cn/upload/image_hosting/4398lp3c.png)

根据等式的性质，**每一个点权扩大或缩小相同的倍数后结果依然成立。** 所以可以得到下图的结果。
![](https://cdn.luogu.com.cn/upload/image_hosting/esz1k6qc.png)

进一步观察发现，结点的权值可被表示为 $k×x$，其中，$x$ 是结点的度，参数 $k$ 满足层数奇偶性不同时正负不同，且树上所有结点对应的 $k$ 的绝对值相同。为了方便计算，默认 $k=1$ 或 $k=-1$。此时可通过dfs算法求得结点的权值。

### 正确性证明
根据权值的计算方式可以发现，每一条边带给两端节点权值的贡献互为相反数。所以答案的权值和应为 $0$。删去任意一个结点后，随之消失的边会导致结点权值和不再为 $0$，原因在于消失边给删去结点相邻的结点的权值影响依然存在。若删除节点的参数为 $k$，则影响值均为 $-k$，每个连通块内的权值和便也为 $-k$。

默认 $k=1$ 或 $k=-1$ 可以直接理解成删去边给结点度带去影响。

下面是方法二的代码。方法一的时间复杂度及操作难度较大，不贴代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+2;
struct edge{
	int to,next;
}e[2*N];
int n,ans[N],np=0,first[N],deg[N];
bool vis[N];

void add(int u,int v){
	e[++np]=(edge){v,first[u]};
	first[u]=np;
}

void dfs(int i,int depth){
	vis[i]=1;
	if(depth%2==1)ans[i]=deg[i];
	else ans[i]=-1*deg[i];
	for(int p=first[i];p;p=e[p].next){
		int j=e[p].to;
		if(!vis[j])dfs(j,depth+1);
	}
}

void work(){
	scanf("%d",&n);
	np=0;
	for(int i=1;i<=n;i++){
		ans[i]=0;
		first[i]=0;
		vis[i]=0;
		deg[i]=0;
	}
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
		deg[x]++;
		deg[y]++;
	}
	dfs(1,1);
	
	for(int i=1;i<=n;i++)
	    printf("%d ",ans[i]);
	printf("\n");
}

int t;
int main(){
	cin>>t;
	while(t--){
		work();
	}
	return 0;
}
```


---

## 作者：bulijoijiodibuliduo (赞：1)

其实这道题不难

首先假设 $1$ 是根节点

我看到这道题第一反应就是直接假设整棵树权值之和是某一个定值，然后再dfs造每一个 $a_x$ 。(其实到这里就可以a了，但是不优雅)

我们发现，由于去掉某一个节点之后，它所有的儿子所在的子树之和都和它上面那一部分之和是一样的，于是我们就有了：$sum_{x's\ son}=sum_1-sum_x$ 其中($x\ne1$，下同)

又因为：$a_x=sum_x-\sum sum_{x's\ son}$

结合一下就成了$a_x=sum_1-deg_x\times(sum_1-sum_x)$

当我们令 $sum_1=0$ 时，发现：

- $sum_{x's\ son}=-sum_x$
- $a_x=deg_x*sum_x$

我们再令 $sum_x=(-1)^{dep_x}$ ，就可以发现 $a_x=deg_x(-1)^{dep_x}$

不难发现，这个结论在 $x=1$ 时也成立

再手动构造几组小数据后发现构造方法正确，就可以优雅的写代码了，芜湖起飞！

最后献上我其丑无比的代码：
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,ans[N];
vector<int>ed[N];
void dfs(int x,int fa,int k){
  ans[x]=ed[x].size()*k;
  for(int y:ed[x])if(fa!=y)dfs(y,x,-k);
}
void solve(){
  cin>>n;
  for(int i=1;i<=n;i++)ed[i].clear();
  for(int i=1,u,v;i<n;i++){
    cin>>u>>v;
    ed[u].emplace_back(v);
    ed[v].emplace_back(u);
  }
  dfs(1,1,1);
  for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
  cout<<'\n';
}
int main(){
  int t;
  cin>>t;
  while(t--)solve();
}
```

---

## 作者：Lates (赞：0)

注意到树是个二分图。

不妨二分图染色一下。

断 $x$ 时，考虑让每个连通块只有连 $x$ 这条边的贡献。

将黑白点分别设为 $deg_x, -deg_x$ 不难发现其他边的贡献都没了。

```cpp
#include <bits/stdc++.h>
#include <assert.h>
using namespace std;
typedef long long ll;
#define ep emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define fin freopen("in.in","r",stdin);
inline int read() {
	int x=0, v=1,ch=getchar();
	while('0'>ch||ch>'9') {
		if(ch=='-') v=0;
		ch=getchar();
	}while('0'<=ch&&ch<='9') {
		x=(x*10)+(ch^'0');
		ch=getchar();
	}return v?x:-x;
}
const int MAX=1e5+5;
int T,ans[MAX],n; vector<int>G[MAX];
void dfs(int x,int f,int l) {
	if(l&1) {
		ans[x]=G[x].size();
	}else {
		ans[x]=-G[x].size();
	}
	for(int y:G[x]) if(y!=f)dfs(y,x,l^1);
}
void clr() {
	for(int i=1;i<=n;++i)vector<int>().swap(G[i]);
}
signed main() {
	T=read();
	while(T--){
		n=read();
		for(int i=1,x,y;i<n;++i){
			x=read(),y=read();
			G[x].ep(y), G[y].ep(x);
		}
		dfs(1,0,0);
		for(int i=1;i<=n;++i) printf("%d ",ans[i]); puts("");
		clr();
	}
	return 0;
}

```


---

## 作者：Yukinoshita_Yukino (赞：0)

构造题。

考虑将树黑白染色，黑色节点赋值为它的度数，白色节点赋值为它的度数的相反数。

证明一下正确性：首先很显然，这棵树点权总和为 $0$，因为一条边会对整棵树的权值增加一个 $1$ 和一个 $-1$，总和为 $0$。

设一个点的度数为 $s$，删除它对把这棵树变成 $s$ 个联通块，并删除 $s$ 条边。因为只把这些边两端的一个节点删去了，而另一端的节点权值没变，所以一条边会使树的权值总和变大/变小 $1$。即因为删去这条边的连通块的权值和为 $1$ 或 $-1$。这 $s$ 个连通块权值都一样，为 $1$ 或 $-1$（具体按照删去节点权值的正负判断）。

```cpp

#include<bits/stdc++.h>
using namespace std;
int T,n;
const int maxn=1e5+5;
vector<int> cnt[maxn];
int col[maxn];
void dfs(int u,int fa)
{
	col[u]=-col[fa];
	for(int i=0;i<cnt[u].size();i++)
	{
		if(cnt[u][i]==fa) continue;
		dfs(cnt[u][i],u);
	}
}
void solve()
{
	
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		cnt[u].push_back(v);
		cnt[v].push_back(u);
	}
	col[0]=1;
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		if(col[i]==-1) cout<<(int)cnt[i].size()<<' ';
		else cout<<(int)-cnt[i].size()<<' ';
	}
	cout<<endl;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cnt[i].clear();
		solve();
	}
	return 0;
 }


```

---

## 作者：enucai (赞：0)

## Preface

膜拜 @[Daniel777](https://www.luogu.com.cn/user/310317)。

## Analysis

考虑子树值的和，分三类讨论：高度为**奇数**，高度为**偶数** 与 **根**。高度为**偶数**的子树和为 $1$，高度为**奇数**的子树和为 $-1$，**根**的子树和为 $0$ 即可。Dfs 的时候记录一下深度是奇数还是偶数，再记录一下子树值的和即可。复杂度 $O(n)$。

## Code

**Talk is cheap, show me the code.**

[Codeforces Status](https://codeforces.com/contest/1656/submission/150796320)

```cpp
// And in that light, I find deliverance.
#define int long long
int n,a[100010],sum[100010];
vi e[100010];
int col[100010];
void dfs(int u,int fa){
	col[u]=col[fa]^1;
	for(auto v:e[u]) if(v!=fa) dfs(v,u);
}
void solve(int u,int fa){
	for(auto v:e[u]) if(v!=fa) solve(v,u),sum[u]+=sum[v];
	if(u==1) a[u]=0-sum[u];
	else if(col[u]==0) a[u]=1-sum[u];
	else a[u]=-1-sum[u];
	sum[u]+=a[u];
}
void work(){
	read(n);
	For(i,1,n) a[i]=0,e[i].clear(),sum[i]=0;
	For(i,1,n-1){
		int u,v;read(u,v);
		e[u].pb(v),e[v].pb(u);
	}
	col[0]=1;
	dfs(1,0);
	solve(1,0);
	For(i,1,n) cout<<a[i]<<" ";puts("");
}
signed main(){
	int T;read(T);
	while(T--) work();
}
```

---

## 作者：OrezTsim (赞：0)

可以用归纳法解题。

首先发现，删掉一个点，剩下的块数就是它的度数。

不妨使得 $\sum a_i=0$，一个点的点权等于其他所有点权的和的相反数。

发现度数是相互提供的，则相邻的点的正负性一定相反。

考虑如何进行具体构造。

设当前点 $\text{cur}$，其父亲为 $\text{f}$，$\text{cur}$ 的 $p$ 棵子树的和均为 $x$，剩余连通块的和也为 $x$。

那么 $a_{\text{cur}}=-(p+1)x$。

考虑转移到 $\text{f}$，其以 $\text{cur}$ 为根的子树和为 $-(p+1)x+px=-x$。

同理有其余子树（加上 $\text{cur}$ 的共 $q$ 个）和连通块的和为 $-x$。

那么 $a_{\text f}=(q+1)x$。

以 $\text{f}$ 为根的子树和为 $(q+1)x-qx=x$。

那么你会发现，子树和呈交替的 $x,-x$ 的状态。这是什么原因呢？

其实对于每一棵子树来说，它自己本身就是一个合法状态。

那么此时它只有一个父亲，会贡献 $1$ 的度数，且由于相邻点权正负性相反，于是存在 $x,-x$。

这样构造，子树和就与点权没关系了，只和深度有关，为 $x$ 或 $-x$。

将叶子节点均赋为 $1$ 或 $-1$，往上递归即可（为了保证点权不超过限制）。

稍微想一下发现不需要反过来求和，点权的绝对值其实就是它的度数，正负性由深度决定。

```cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = N << 4;
int t, n, cnt, qu[N], dep[N], lst[N], res[N], head[N];
struct Edge { int to, nxt; } e[N << 1];

namespace fast_io {
    int it, ed, ot, t; char stk[20], bf[N + 50], ob[N + 50];
    #define gc (it == ed && (ed = (it = 0) + fread(bf, 1, N, stdin), it == ed))? EOF : bf[it++]
    template <typename T> inline void read(T &x) {
        x = 0; char ch = gc; int f = 1;
        for (; !isdigit(ch); ch = gc) if (ch == '-') f = -1;
        for (; isdigit(ch); ch = gc) x = x * 10 + (ch ^ 48); x *= f; return ;
    } template <typename T, typename ...Args>
    inline void read(T &x, Args &...args) { read(x), read(args...); }
    inline void fls() { fwrite(ob, 1, ot, stdout), ot = 0; }
    template <typename T> inline void write(T x, char opt) {
        if (x < 0) ob[ot++] = '-', x = -x;
        while (x > 9) stk[++t] = 48 ^ (x % 10), x /= 10;
        for (ob[ot++] = 48 ^ x; t; ob[ot++] = stk[t--]);
        ob[ot++] = opt; if (ot > N) fls(); return ;
    }
} using fast_io::read; using fast_io::write;

inline void addEdge(int u, int v) {
    e[++cnt].to = v, e[cnt].nxt = head[u];
    head[u] = cnt;
}

inline void solve() {
    read(n); cnt = 0; for (int i = 1; i <= n; ++i) head[i] = res[i] = 0;
    for (int i = 1, u, v; i < n; ++i)
        read(u, v), addEdge(u, v), addEdge(v, u), ++res[u], ++res[v];
    int l = 1, r = 1; qu[l] = dep[l] = lst[l] = 1;
    while (l <= r) {
        int f = lst[l], cur = qu[l], dp = dep[l]; ++l;
        for (int i = head[cur]; i; i = e[i].nxt) {
            int to = e[i].to;
            if (to ^ f) ++r, lst[r] = cur, qu[r] = to, dep[r] = -dp;
        }
        res[cur] *= dp;
    }
    for (int i = 1; i <= n; ++i) write(res[i], i == n? '\n' : ' ');
}

int main() {
    read(t); while (t--) solve(); fast_io::fls(); return 0;
}
```

---

