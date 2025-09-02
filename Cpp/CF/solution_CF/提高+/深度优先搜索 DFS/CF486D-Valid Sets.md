# Valid Sets

## 题目描述

As you know, an undirected connected graph with $ n $ nodes and $ n-1 $ edges is called a tree. You are given an integer $ d $ and a tree consisting of $ n $ nodes. Each node $ i $ has a value $ a_{i} $ associated with it.

We call a set $ S $ of tree nodes valid if following conditions are satisfied:

1. $ S $ is non-empty.
2. $ S $ is connected. In other words, if nodes $ u $ and $ v $ are in $ S $ , then all nodes lying on the simple path between $ u $ and $ v $ should also be presented in $ S $ .
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486D/178986cc3145e106df7e442d141768e61c090be6.png).

Your task is to count the number of valid sets. Since the result can be very large, you must print its remainder modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

In the first sample, there are exactly 8 valid sets: $ {1},{2},{3},{4},{1,2},{1,3},{3,4} $ and $ {1,3,4} $ . Set $ {1,2,3,4} $ is not valid, because the third condition isn't satisfied. Set $ {1,4} $ satisfies the third condition, but conflicts with the second condition.

## 样例 #1

### 输入

```
1 4
2 1 3 2
1 2
1 3
3 4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
0 3
1 2 3
1 2
2 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4 8
7 8 7 5 4 6 4 10
1 6
1 2
5 8
1 3
3 5
6 7
3 4
```

### 输出

```
41
```

# 题解

## 作者：81179332_ (赞：10)

树形 DP

对于每一个连通子图，我们选取 $a$ 值最大的作为代表点，如果有多个 $a$ 值最大的，我们选编号最大的

对于每一个 $root$ 作为代表点，我们设 $dp_i$ 为以 $root$ 为代表点，子树 $i$ 中有多少个合法的连通子图

根据乘法原理，$dp_u=(dp_u+dp_u\times dp_v)$

表示我们要么不要 $v$ 子树中的联通块，此时方案数为 $dp_u$，要么强制选 $v$ 子树中的联通块，此时方案数为 $dp_u\times dp_v$

```cpp
const int N = 2010,M = N;
int n,d,a[N];EE(1);
ll ans,dp[N];
void dfs(int u,int fa,int root)
{
	dp[u] = 1;
	for(int i = head[u],v;i;i = e[i].nxt) if((v = e[i].to) != fa)
		if((a[root] > a[v] || a[root] == a[v] && root >= v) && a[root] - a[v] <= d)
			dfs(v,u,root),dp[u] = (dp[u] + dp[u] * dp[v]) % mod;
}
int main()
{
	d = read(),n = read();
	for(int i = 1;i <= n;i++) a[i] = read();
	for(int i = 1;i < n;i++) add_edge(read(),read());
	for(int i = 1;i <= n;i++) dfs(i,-1,i),ans = Mod(ans + dp[i]);
	fprint(ans);
}

```

---

## 作者：lgswdn_SA (赞：4)

这个树形 DP 挺有意思的。

定义一个点  $u$ 比一个点 $v$ 好，当且仅当 $a_u>a_v$ 或者 $a_u=a_v$ 且 $u<v$。

设 $f(u)$ 为 $u$ 子树中，$u$ 为连通块中的最好的节点且 $a_p$ 比 $a$ 最小的节点大不超过 $d$（注：英文原题面是差 $\le d$ 而非 $<d$）。

为了计算出每一个点 $p$ 作为最大值的情况，我们需要枚举每一个 $p$，然后求出 $p$。

这样设有什么好处呢？方便转移！这样转移的时候，就不需要再去考虑最大值和最小值的差了，只需要考虑最大值和 $u$ 的差即可。

转移方程：

$$
f(u)=\prod (1+f(v)) 
$$

其中 $v$ 必须要满足不比 $p$ 更好且差不大于 $d$。

---

理一下思路，其实就是选取一个“根节点”，然后再这个根节点的环境下去做 DP。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2009,mod=1e9+7;

struct edge {int to,nxt;}e[N*2]; int hd[N],tot;
void add(int u,int v) {e[++tot]=(edge){v,hd[u]};hd[u]=tot;}

int n,d,a[N],f[N],ans;
bool better(int u,int v) {return a[u]>a[v]||a[u]==a[v]&&u<v;}
void dfs(int u,int fa,int p) {
	f[u]=1;
	for(int i=hd[u],v;i;i=e[i].nxt) {
		if((v=e[i].to)==fa) continue;
		if((!better(p,v))||a[p]-a[v]>d) continue;
		dfs(v,u,p);
		(f[u]*=(f[v]+1))%=mod;
	}
}

signed main() {
	scanf("%lld%lld",&d,&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1,u,v;i<n;i++)
		scanf("%lld%lld",&u,&v), add(u,v), add(v,u);
	for(int i=1;i<=n;i++) dfs(i,0,i), (ans+=f[i])%=mod;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：dgdyrkst (赞：3)

# 树形 DP

## 思路
观察数据范围，发现 $O(n^2)$ 可过，考虑枚举每个点并统计贡献。
## 实现
因为枚举每个子图求可行性复杂度不可接受，所以就枚举每个点并 __钦定其为子图内最大值__ ，然后遍历一遍树，求出符合条件的最大子图，只需一直向外扩展。

设当前考虑的点为 $x$，点权为 $val$，当遇到权值比 $val$ 大或比 $val-d$ 小的点就要停下，否则就继续扩展。

但是权值会有重复，如果忽略这种情况的话，两个同样权值的点就会分别计算一遍对方的答案，就 WA 了。

解决方法也很简单，只需定比较的第二关键字。具体地，若扩展到的节点 $y$ 和 $x$ 的权值相等，就再比较编号大小，若 $x<y$ 继续扩展，否则停止。

然后我们需要求出这个最大联通子图中含有多少个 __包含__ $x$ 的子图，考虑树形 DP，当然应将 $x$ 设为根。

对于一个点，它的每个子树可选可不选，各个子树之间乘起来就是总数量，设每个节点的子树包含根节点的子图总数为 $f$，于是不难推出 DP 方程。
$$f_x=\prod_{v\in\operatorname{son}(x)}f_v+1$$

此时记 $cnt_x=f_x$，则最后答案就是 $\sum_{i=1}^{n}cnt_i$。
## 代码
以下为代码参考。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2005,mod=1e9+7;
int n,d,a[N],x,y,vis[N],ans,st;
vector<int> v[N];
int dfs(int now,int fa)
{
	if (a[now]>a[st] || a[now]<a[st]-d || (a[now]==a[st] && now>st))return 0;
	int ret=1;
	for (int i=0;i<v[now].size();i++)
	{
		int w=v[now][i];
		if (w==fa)continue;
		ret=ret*(dfs(w,now)+1)%mod;
	}
	return ret;
}
signed main()
{
	cin >> d >> n;
	for (int i=1;i<=n;i++)cin >> a[i];
	for (int i=1;i<n;i++)
	{
		cin >> x >> y;
		v[x].push_back(y),v[y].push_back(x);
	}
	for (int i=1;i<=n;i++)
	{
		st=i;
		ans=(ans+dfs(i,0))%mod;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Mr_cold (赞：3)

定义dp[i]表示杆节点i的子树中有多少个节点，对于一割接点的所有联通块的个数就是$dp[u]*=(dp[v]+1)$,对于这道题，观察数据范围可得知复杂度是$O(n^2)$的，我们可以每次固定一个点，确定它为当前最小值，然后保证每次向下递归的时候保证val[v]大于当前的根就行了，但是有个很坑的地方是，权值是可以相等的，那么就会造成多次统计，所以我们这里强行规定权值相等的只能和比他序号大的点进行计数，这样就不会错了、

~~~
#include<bits/stdc++.h>
#define pts putchar('\n');
#define ptc putchar(' ');
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
typedef long long ll;
typedef long long ll;
const int maxm=2e6+9;
const int maxn=2e6+9;
const int N=200+9;
const int inf=0x3f3f3f3f;
const int base=131;
const int mod=1e9+7;
const double eps=1e-4;
int n,d;
int val[maxn],sze[maxn];
vector<int>G[maxn];
ll ans=0;
int read(){
    int a=1,b=0;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') a=-1;c=getchar();}
    while(c>='0'&&c<='9'){b=(b<<1)+(b<<3)+(c^'0');c=getchar();}
    return a*b;
}
void print(ll x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
ll dfs(int now,int fa,int root){
	ll ret=1;
	for(int i=0,k=G[now].size();i<k;++i){
		int to=G[now][i];
		if(to==fa) continue;
		if(val[to]-val[root]>d||val[root]>val[to]) continue;
		if(val[to]==val[root]&&to<root) continue;
		ret+=(ret*(dfs(to,now,root))%mod)%mod;
		ret%=mod;
	}
	return ret;
}
int main(){
//	freopen("4.in","r",stdin);
//	freopen("test.txt","w",stdout); 
  	d=read(),n=read();
  	rep(i,1,n) val[i]=read();
  	rep(i,1,n-1){
  		int u=read(),v=read();
  		G[u].push_back(v);
  		G[v].push_back(u);
	}
	rep(i,1,n){
		ans=(ans+dfs(i,0,i))%mod;
	}
	print(ans);
    return 0;
}

~~~

---

## 作者：Umbrella_Leaf (赞：3)

### 题意简述

> 给你一棵树，点有点权，求这棵树的满足最大点权与最小点权之差小于等于 $k$ 的连通子图的个数。
> 
> （貌似洛谷题面里没写）$1\le n\le 2000$。

### 分析

比较简单的一道题。

首先我们考虑枚举最小点权出现在哪个点（当然，枚举最大点权也能做）。

那么因为 $n\le 2000$ 所以我们直接从这个点出发开始 `dfs`，找以它为最小节点的连通子图最大扩展到哪里。

`dfs`的方法很简单，如果枚举的最小点权是 $x$，那么只能在当前搜到的节点权 $v$ 满足 $x\le v\le x+d$ 时才能接着搜。

然后这里如果有两个点点权重复会重算，所以我们应该在 $v=x$ 时检查搜到的节点编号大于最小点权的编号（或者说把点权的比较弄一个第二优先级是点的编号，这样就不会重复）。

找出这个子图之后我们可以在上面树形 DP，$f_i$ 表示以 $i$ 为根的子树内取到 $i$ 的连通子图有多少种方案，则

$$f_x=\prod_{y\in son_x}f_y+1$$

然后就没有然后了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1e9+7;
int n,d;
int a[2005];
vector<int> edge[2005];
ll dp[2005];
void dfs(int x,int f,int v){
	if(a[x]<a[v]||a[x]==a[v]&&x>v||a[x]>a[v]+d)return;
	dp[x]=1;
	for(int y:edge[x])
		if(y!=f){
			dfs(y,x,v);
			dp[x]=dp[x]*(dp[y]+1)%mod;
		}
}
int main(){
	scanf("%d%d",&d,&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		memset(dp,0,sizeof(dp));
		dfs(i,0,i);
		ans=(ans+dp[i])%mod;
	}
	printf("%lld\n",ans);
	// system("pause");
	return 0;
}
```

---

## 作者：xiezheyuan (赞：2)

## 简要题意

给出一个 $n$ 个点的树，点有点权。求极差小于等于 $d$ 的连通子图数目。对 $10^9+7$ 取模。

$1 \leq n,d \leq 2 \times 10^3$

## 思路

你发现如果设 $f(x,y)$ 表示以 $x$ 为根的连通块极差为 $y$ 的方案数转移是指数级的。考虑 $d$ 固定的意义。

如果点权互不相同，有一种做法就是枚举每一个最大 / 最小值，然后以这个点为根 dp。这样就可以解决极差限制问题。最后统计答案时用乘法原理即可。时间复杂度为 $O(n^2)$。

但是你发现这样子连样例都过不去。发现相同的点权如果可以同时出现在连通块里，那么这个连通块会算 2 次。解决方法：钦定与根相同的元素中，只有编号大于 / 小于 根才可以被贡献。

时间复杂度 $O(n^2)$ 可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define debug(fmt,...) do{fprintf(stderr,fmt,##__VA_ARGS__);fprintf(stderr,"\n");}while(0)
#define error(expr,fmt,...) do{if((expr)){debug(fmt,##__VA_ARGS__);exit(0);}}while(0)
using namespace std;

int n,d;
const int N = 2005,mod = 1e9+7;
int f[N],w[N];

int M(int x){
    return (x%mod+mod)%mod;
}

struct edge{
    int nxt,to;
} g[N<<1];
int head[N],ec;

void add(int u,int v){
    g[++ec].nxt=head[u];
    g[ec].to=v;
    head[u]=ec;
}

void dfs(int u,int fa,int now){
    f[u] = 1;
    for(int i=head[u];i;i=g[i].nxt){
        int v = g[i].to;
        if(w[v] < w[now] || v == fa || (w[v]-w[now]) > d || w[now] == w[v] && now <= v) continue;
        dfs(v, u, now);
        f[u] = M(f[u] * (f[v] + 1));
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>d>>n;
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        add(u,v);add(v,u);
    }
    int ans = 0;
    for(int i=1;i<=n;i++){
        dfs(i, 0, i);
        ans = M(ans + f[i]);
    }
    cout<<ans;
    return 0;
}

// Country Roads, take me home to the place I belong
// West Virginia, mountain mamma, take me home, country roads
```

---

## 作者：Honor誉 (赞：2)

[我的博客](https://blog.csdn.net/qq_35019468/article/details/101900500)

树形DP。

设$dp[i]$表示在以$i$为根的子树中能有多少个联通子图。

每次以一个点为根，求出最大联通子图数量。

因为我们要有顺序（去重），所以我们要将每一次的根设为$a$值最大的一个，去DP。

但是这样还是会有重复，因为当$a[root]==a[son]$时，$root$可以更新$son$,$son$也可以更新$root$,所以我们要在$a[root]==a[son]$时，限制只能从编号大的访问编号小的。

状态转移方程：

#### $dp[u]+=dp[u]*dp[v]$（由儿子中可以的联通子图和自己中的联通子图，乘法原理）。

判断条件：
```cpp
if(v!=fa&&(a[root]>a[v]||(a[root]==a[v]&&v<=root))&&a[root]-a[v]<=k)
{
	dfs(v,u,root);
	dp[u]=(dp[u]+1ll*dp[u]*dp[v])%mod;
}
```

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define N 2010
using namespace std;
int ans,dp[N],head[N],to[N<<1],nxt[N<<1],a[N],n,k,x,y,cnt;
void adde(int x,int y)
{
	to[++cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
void dfs(int u,int fa,int root)
{
	dp[u]=1;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v!=fa&&(a[root]>a[v]||(a[root]==a[v]&&v<=root))&&a[root]-a[v]<=k)//这些判断条件都是为了去重
		{
			dfs(v,u,root);
			dp[u]=(dp[u]+1ll*dp[u]*dp[v])%mod;
		}
	}
}
int main()
{
	scanf("%d%d",&k,&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		adde(x,y);
		adde(y,x);
	}
	for(int i=1;i<=n;i++)//以每一个点为根
	{
		dfs(i,-1,i);
		ans=(ans+dp[i])%mod;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：yuyc (赞：0)

## 解析

看了一下，现有题解的做法都是钦定最大 / 最小值然后跑 $n$ 遍 DFS。

我一开始也是这么想的，然后发现不会去重，所以憋出了另一种状态设计。

一个最暴力的想法是设 $dp_{i,j,k}$ 表示以 $i$ 为根的子树内，必选点 $i$，最大值为 $j$ 且最小值为 $k$ 时的方案数。

考虑怎么样减掉一维，我们发现，定了最大值就定了可以取的最小值，所以尝试只在状态里记录最大值。

这样就变成了 $dp_{i,j}$ 表示以 $i$ 为根的子树内，必选点 $i$，最大值为 $j$ 的方案数。但是我们发现这个东西好像并不能转移——要转移肯定要枚举儿子子树内最大值 $k$，此时如果 $k < j$，则对于儿子子树内，最小值的下界限制会更低。

不妨只限制值的范围，不要求这个最大值一定取到。
于是 $dp_{i,j}$ 的含义变成以 $i$ 为根的子树内，必选点 $i$，选的权值小于等于 $j$，大于等于 $j - d$ 的方案数。

然而我们还要统计答案，所以要多加一维表示有没有取到最大值 $j$。

转移时分类讨论：

若 $j = a_i$，则必定能取到最大值，儿子的子树取不取得到最大值无所谓，注意也可以不选。

$$dp_{i,j,1} = \prod_{k \in son_i} (dp_{k,j,0} + dp_{k,j,1} + 1)$$

$$dp_{i,j,0} = 0$$

若 $j > a_i \ge j - d$，先考虑取不到最大值的情况，此时儿子的子树内也必定取不到最大值。

$$dp_{i,j,0} = \prod_{k \in son_i} (dp_{k,j,0} + 1)$$


如果取得到最大值，则儿子的子树内至少有一个取到最大值 $j$，正难则反，我们用总方案减去全都没取到最大值的方案，可以发现后面这部分其实就是 $dp_{i,j,0}$。

$$dp_{i,j,1} = \prod_{k \in son_i} (dp_{k,j,0} + dp_{k,j,1} + 1) - dp_{i,j,0}$$

~~现在我才发现分类讨论的这两种情况其实是可以合并的。~~

最终答案就是 $\sum_{i=1}^n\sum_{j=1}^{2000} dp_{i,j,1}$。

## 代码

```cpp
#include <bits/stdc++.h>
#define eps 0.000001
using namespace std;
typedef __int128 i128;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,int> pii;
const int N = 2e3 + 5, M = 2e5 + 5,mod = 1e9 + 7,base1 = 13331,base2 = 131;
vector<int> t[N];
int dp[N][N][2],a[N],d,n;
int res;
void dfs(int x,int fa){
//	cerr<<x<<'\n';
	for(int j=a[x];j<=min(2000,a[x] + d);j++){
		dp[x][j][0] = dp[x][j][1] = 1;
	}
	dp[x][a[x]][0] = 0;
	for(int nx : t[x])if(nx != fa){
		dfs(nx,x);
		dp[x][a[x]][1] = 1ll * dp[x][a[x]][1] * (dp[nx][a[x]][0] + dp[nx][a[x]][1] + 1) % mod;
		for(int j=a[x] + 1;j<=min(2000,a[x] + d);j++){
			dp[x][j][1] = 1ll * dp[x][j][1] * (dp[nx][j][0] + dp[nx][j][1] + 1) % mod;
			dp[x][j][0] = 1ll * dp[x][j][0] * (dp[nx][j][0] + 1) % mod;
		}
	}
	res = (res + dp[x][a[x]][1]) % mod;
	for(int j=a[x] + 1;j<=min(2000,a[x] + d);j++){
		dp[x][j][1] = (dp[x][j][1] + mod - dp[x][j][0]) % mod;
		res = (res + dp[x][j][1]) % mod;
	}
//	for(int j=a[x];j<=min(2000,a[x] + d);j++){
//		cout<<x<<" "<<j<<" "<<dp[x][j][0]<<" "<<dp[x][j][1]<<'\n';
//	}
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
//  freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	cin>>d>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		t[u].push_back(v);
		t[v].push_back(u);
	}
	dfs(1,0);
	cout<<res;
	return 0;
}

```

---

## 作者：ivyjiao (赞：0)

对于这种题有一个常见的 trick，对于本题就是：固定最大值，找最小值。

我们对于每个 $a_i$ 设其为最大值，以它为根 dfs，只搜索 $a_v<a_i$ 且 $a_i-a_v\leq d$ 的点，设 $dp_u$ 为这次搜索中确定的树以 $u$ 为根的方案，初值为 $1$，即搜到就停止。对于搜到的每个点 $u$，只有向下搜和不向下搜两种方案，不向下搜就是初值 $1$，向下搜根据乘法原理就是 $dp_u\times dp_v(v~\text{is a son of}~u)$，因为一种方案能和子树中的每一种方案匹配。所以对于每个合法的儿子 $v$ 有 $dp_u=dp_u+dp_u\times dp_v$。

但是我们要考虑到 $a_i=a_j$ 的问题，所以遇到这种情况只搜编号小于 $root$ 的点，保证不重复。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+1,p=1e9+7;
int d,n,a[N],u,v,dp[N],ans;
vector<int>G[N];
void dfs(int u,int fa,int rt){
    dp[u]=1;
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(v==fa||a[v]>a[rt]||a[rt]-a[v]>d) continue;
        if(a[v]==a[rt]&&rt>v) continue;
        dfs(v,u,rt);
        (dp[u]+=dp[u]*dp[v])%=p;
    }
}
signed main(){
    cin>>d>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++){
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        dfs(i,0,i);
        (ans+=dp[i])%=p;
    }
    cout<<ans;
}
```

---

## 作者：Msents (赞：0)

计数题，第一眼看上去很难，~~已微距~~。

注意到 $n$ 顶天 2000，猜测最终复杂度是 $O(n^2)$ 的，也就是可以从每个点出发对全树进行扫描。

考虑遍历每个点，钦定当前点的权值最小，然后从该点出发，碰到了权值减去起点的权值大于 $d$ 的点就回头，这样就能得到一棵树，且能发现这棵树的每个包含了起点的联通子图都是合法的，于是从起点 DP，设 DP 式子为 $f_u=\prod_{son }f_{son}+1$，就可以得到这样的联通子图的个数，最后将所有结果求和就是答案。

如果树中有两个点权值相同，答案就有可能算重，解决方法很简单，遍历一棵树时碰到了权值相同的点且该点的编号小于起点编号就回头，这样就只会被算一遍。

码，很短：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxN=2000,Mod=1000000007;
int n,d,a[MaxN+1];
vector<int>g[MaxN+1];
long long DFS(int u,int prt,int r){
	long long res=1;
	for(int v:g[u]){
		if(v==prt)continue;
		if(a[v]<a[r])continue;
		if(a[v]==a[r]&&v<r)continue;
		if(a[r]+d<a[v])continue;
		res=res*(DFS(v,u,r)+1)%Mod;
	}
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>d>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n-1;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	long long ans=0;
	for(int i=1;i<=n;i++)ans=(ans+DFS(i,0,i))%Mod;
	cout<<ans;
	return 0;
}

```

---

## 作者：快斗游鹿 (赞：0)

## 思路

发现 $n$ 较小，所以我们可以对每个点统计答案。设 $f_i$ 表示点 $i$ 的子树的答案，初始 $f_i=1$。显然在满足条件时，有 $f_u=f_u*(f_v+1)$，其中 $v$ 是 $u$ 的儿子。但这样会算重。所以我们每次统计时，要保证被统计到的所有 $i$ 满足 $val_i\le val_{root}$，$root$ 是当前树根。但这样还会出现 $val$ 相等的情况。所以还得判断 $i$ 是否大于 $root$ 编号。这样就可以不重不漏地统计所有方案了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+5;
const int mod=1e9+7;
struct edge{
	int to,nxt;
}e[N<<1];
int n,d,w[N],cnt,head[N],f[N],ans,mx,root;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int u,int fa,int nowmin){
	if(mx-nowmin>d){
		return;
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		int minn=min(nowmin,w[v]);
		if(mx-minn>d)continue;
		if(v==fa||w[v]>mx||(w[v]==mx&&root>v))continue;//防止算重
		dfs(v,u,min(nowmin,w[v]));
		f[u]=f[u]*(f[v]+1)%mod;f[u]%=mod;
	}
}
signed main(){
	freopen("std.in","r",stdin);
	d=read();n=read();
	for(int i=1;i<=n;i++)w[i]=read();
	for(int i=1;i<n;i++){
		int u,v;u=read();v=read();add(u,v);add(v,u);
	}
	for(int i=1;i<=n;i++){
		mx=w[i];root=i;
		for(int j=1;j<=n;j++)f[j]=1;
		dfs(i,0,w[i]);
		//for(int j=1;j<=n;j++)cout<<f[j]<<" ";
		//cout<<endl;
		ans=ans+f[i];ans%=mod;
	}
	cout<<ans;
	return 0;
}


```


---

## 作者：Erotate (赞：0)

不妨设 $f_i$ 为强制选 $i$ 号节点为最大值时以 $i$ 为根的子树可以构成的合法联通子图的数目，则每一个 $f_i$ 都应该初始化为 $1$，因为自己一个节点也是联通子图。由计数原理可得转移方程为

$$f_u=f_u + f_u \times f_v$$

其中 $v$ 为 $u$ 的儿子节点。为了保证子图是合法的，并且不重复计数，我们只有当 $u$ 的权值和每个子树里的节点的权值的差都小于等于 $d$ 且 $u$ 的权值是最大的时候才转移。如果子树里有节点的权值和 $u$ 的权值相等，那就必须 $u$ 的编号比那个节点的编号大才转移。

```cpp
const int N=2e3+5,P=1e9+7;
struct edge{
	int v,nxt;
}e[N<<1];
int n,d,head[N],cnt;
LL f[N],val[N],ans;
void add(int x,int y){
	e[++cnt]=((edge){y,head[x]});
	head[x]=cnt;
}
void dfs(int u,int fa,int rt){
	f[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		if(val[rt]-val[v]<=d && (val[rt]>val[v] || val[rt]==val[v] && v>rt)){
			dfs(v,u,rt);
			f[u]=(f[u]+f[u]*f[v]%P)%P;
		}
	}
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    d=read(),n=read();
    for(int i=1;i<=n;++i) val[i]=read();
    for(int i=1;i<n;++i){
    	int x=read(),y=read();
    	add(x,y),add(y,x);
	}
	for(int i=1;i<=n;++i){
		dfs(i,0,i);
		ans=(ans+f[i])%P;
	}
	write(ans);
    return 0;
}
```


---

## 作者：Yizhixiaoyun (赞：0)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/17301307.html)

[题目传送门](https://www.luogu.com.cn/problem/CF486D)

## 题目分析

不算很难的树形 $\text{dp}$。

令 $dp_i$ 表示以 $i$ 为根的子树中联通子图的个数。

在更新的时候，考虑儿子的联通子图和自己的，则有：

$$dp_u = dp_u \times (dp_v + 1)$$

选根的时候将 $a$ 最大的作为根节点。还要注意另外一点，就是当 $a_{fa}=a_{v}$ 时，双方互相都可以更新，所以会出现问题。此时将根节点设为编号大的那个即可。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define debug puts("Shiina_Mashiro_kawaii")
#define ok puts("Yes")
#define no puts("No")
#define inf 1e9
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int maxn=2e5+5;
const int mod=1e9+7;
int n,d;
int ans;
int a[maxn];
int dp[maxn];
int cnt_edge,head[maxn];
struct edge{
	int to,nxt;
}e[maxn<<1];
void add(int u,int v){
	e[++cnt_edge].nxt=head[u];
	e[cnt_edge].to=v;
	head[u]=cnt_edge;
}
void dfs(int u,int fa,int rt){
	dp[u]=1;
	for(register int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		if((a[v]==a[rt]&&v<rt)||(a[v]-a[rt]>d||a[rt]>a[v])) continue;
		dfs(v,u,rt);
		dp[u]*=dp[v]+1;dp[u]%=mod;
	}
}
inline void init(){
	d=read();n=read();
	for(register int i=1;i<=n;++i) a[i]=read();
	for(register int i=1;i<n;++i){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
}
signed main(){
	init();
	for(register int i=1;i<=n;++i){
		dfs(i,0,i);
		ans+=dp[i];ans%=mod;
	}
	printf("%d",ans);
}
```

---

