# [ABC220F] Distance Sums 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc220/tasks/abc220_f

$ N $ 頂点の木が与えられます。頂点には $ 1,2,\ldots\ ,N $ の番号がついており、$ i $ 番目の辺は頂点 $ u_i,v_i $ を結ぶ無向辺です。

各整数 $ i\,(1\ \leq\ i\ \leq\ N) $ に対して、$ \sum_{j=1}^{N}dis(i,j) $ を求めてください。

ただし、$ dis(i,j) $ は頂点 $ i $ から頂点 $ j $ に到達する際にたどる必要のある最小の辺数です。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ u_i\ <\ v_i\ \leq\ N $
- 与えられるグラフは木
- 入力は全て整数

### Sample Explanation 1

$ dis(1,1)+dis(1,2)+dis(1,3)=0+1+2=3 $、 $ dis(2,1)+dis(2,2)+dis(2,3)=1+0+1=2 $、 $ dis(3,1)+dis(3,2)+dis(3,3)=2+1+0=3 $、 です。

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
3
2
3```

## 样例 #2

### 输入

```
2
1 2```

### 输出

```
1
1```

## 样例 #3

### 输入

```
6
1 6
1 5
1 3
1 4
1 2```

### 输出

```
5
9
9
9
9
9```

# 题解

## 作者：zjinze (赞：5)

#### 前置知识：换根 dp。

#### 思路：

我们可以先定义一下变量：

$dp[i]$ 表示以 $i$ 为根节点时，其子节点深度的和；

$siz[i]$ 表示以 $i$ 为根节点时，其子树的大小；

$dep[i]$ 表示以 $1$ 为根节点时，所有节点的深度。


如果我们假设 $1$ 为根，将无根树化为有根树。在搜索回溯时统计 $siz[i]$，$dep[i]$ 和 $dp[1]$，其时间复杂度为 $O(n)$。

紧接着，我们考虑在第二次搜索时就完成 $dp[i]$ 的统计。

第二次搜索依旧从 $1$ 号节点出发，若 $1$ 号节点与节点 $x$ 相连，则我们考虑能否通过 $1$ 号节点的答案去推出节点 $x$ 的答案。

在根从 $1$ 号节点变为节点 $x$ 的过程中，我们可以发现以 $x$ 为根结点的树中的节点的深度都降低了 $1$，除 $x$ 为根节点的树，所有的节点的深度都上升了 $1$，而这两部分节点的数量在第一次搜索时就得到了，于是我们就求出了所有的 $dp[i]$。



#### code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=200010;
int n,x,y,siz[N],dep[N],dp[N];
vector<int>ve[N];
void dfs1(int x,int fa){
	siz[x]=1;
	if(fa!=0)dep[x]=dep[fa]+1;
	for(int j=0;j<ve[x].size();j++){
		int to=ve[x][j];
		if(to!=fa){
			dfs1(to,x);
			siz[x]+=siz[to];
		}
	}
	return ;
}
void dfs2(int x,int fa){
	for(int j=0;j<ve[x].size();j++){
		int to=ve[x][j];
		if(to!=fa){
			dp[to]=dp[x]-2*siz[to]+n;
			dfs2(to,x);
		}
	}
	return ;
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>x>>y;
		ve[x].push_back(y);
		ve[y].push_back(x);
	}
	dfs1(1,0);
	for(int i=1;i<=n;i++)dp[1]+=dep[i];
	dfs2(1,0); 
	for(int i=1;i<=n;i++){
		cout<<dp[i]<<"\n";
	}
	return 0;
}
```


---

## 作者：__YSC__ (赞：2)

# 题目描述

给定一颗 $N$ 个节点的树，求对于每个 $1 \le i \le N$ 为根时所有节点的深度之和。这里根节点的深度为 $0$。

# 思路

首先转换题意为求所有节点到 $i$ 的距离之和，考虑使用换根`DP`。

- 状态：$dp_i$ 表示 $i$ 到所有节点的的距离之和。

接下来就是如何转移。我们先将 $1$ 确定为根。

![](https://cdn.luogu.com.cn/upload/image_hosting/lrvp0wuf.png)

可以发现，当我们从 $u$ 转移到 $v$ 时，红色部分的距离都会 $-1$，绿色部分都会 $+1$，这样我们就可以得到转移。

- 转移：$dp_i = dp_f + N - 2 \times sz_i$，其中 $f$ 为 $i$ 的父亲，$sz_i$ 表示以 $i$ 为根的子树大小。
- 拓扑序：$i$ 的深度从小到大。
- 初始状态：$dp_1$。
- 目标状态：$dp_{1,2,\dots,N}$。

时空复杂度均为 $O(N+M)$。

## 细节

无。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200001;

int n, sz[MAXN];
long long sum, ans[MAXN];
vector<int> e[MAXN];

void dfs(int u, int fa, long long dis) {
  sum += dis;
  sz[u] = 1;
  for(int v : e[u]) {
    if(v != fa) {
      dfs(v, u, dis + 1);
      sz[u] += sz[v];
    }
  }
}

void DFS(int u, int fa) {
  for(int v : e[u]) {
    if(v != fa) {
      ans[v] = ans[u] + n - 2ll * sz[v];
      DFS(v, u);
    }
  }
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n;
  for(int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  dfs(1, 0, 0);
  ans[1] = sum;
  DFS(1, 0);
  for(int i = 1; i <= n; ++i) {
    cout << ans[i] << "\n";
  }
  return 0;
}
```

---

## 作者：appear_hope (赞：2)

题目给定了一颗无根树，那么为了让此题有拓扑序，我们先让 $1$ 作为根。

令 $dep_i$ 为以 $1$ 为根时节点 $i$ 的深度，$siz_i$ 表示以 $1$ 为根时以 $i$ 为根的子树大小。

其他点到 $1$ 号节点的距离是 $\sum_{i = 1} ^{i = n} dep_i$。

那么如果点 $i$ 做为根时，在以 $i$ 为根的子树的节点深度都会少 $1$，不在以 $i$ 为根的子树的深度都会增加一。

所以得到转移方程：

$$dp_v = dp_u - siz_v + (n - siz_v)$$

其中 $u$ 和 $v$ 有一条连边。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e5 + 5;

ll sum;
ll dp[N];
vector<int> g[N];
int n, siz[N], dep[N];

void dfs(int x, int fa, int op){
  siz[x] += !op, dep[x] = (!op ? dep[fa] + 1 : dep[x]), sum += (!op) * dep[x];
  for(int v : g[x]){
    if(v != fa){
      if(!op){
        dfs(v, x, 0);
        siz[x] += siz[v];
      }
      else{
        dp[v] = dp[x] - siz[v] + (n - siz[v]);
        dfs(v, x, 1);
      }
    }
  }
}

int main(){
  cin >> n;
  for(int i = 1, u, v; i < n; i++){
    cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }
  dfs(1, 0, 0);
  dp[1] = sum - n, dfs(1, 0, 1);
  for(int i = 1; i <= n; i++){
    cout << dp[i] << '\n';
  }
  return 0;
}
```

---

## 作者：Gao_l (赞：1)

**换根大法好！**

### -1. 前置芝士
[换根DP](https://zhuanlan.zhihu.com/p/348349531)
### 1.思路

#### 1.1第一遍DFS

求出当以 $1$ 为根节点时 $i$ 的子树的节点个数，与它的深度。

```cpp
void dfs1(int cur,int fa){
    siz[x]=1;//siz表示子树的节点个数
    for(int i=0;i<nbr[cur].size();i++){
        int nxt=nbr[cur][i];
        if(fa==nxt)continue;
        dfs(nxt,fa);
        siz[cur]+=siz[nxt];
        dep[nxt]=dep[cur]+1;//dep表示深度
    }
}
```

#### 1.1.5第二遍DFS之前的初始化

求出以 $1$ 为根节点时，所有节点的深度和。

```cpp
for(int i=1;i<=n;i++){
    dp[1]+=dep[i];//dp为以i为根节点时，所有节点的深度和。
}
```

#### 1.2第二遍DFS

求出以 $i$ 为根节点时，所有节点的深度和。

![](https://cdn.luogu.com.cn/upload/image_hosting/m5w9m1eg.png)

如图，当要求 $dp_0$ 时，易得出公式

$$dp_0=dp_1-siz_0+(siz_1-siz_0)$$

简化得：

$$dp_0=dp_1+siz_1-2siz_0$$

所以递推公式为：

$$dp_{cur}=dp_{nxt}+siz_1-2siz_{nxt}$$

所以代码为：

```cpp
void dfs2(int cur,int fa){
	for(int j=0;j<nbr[cur].size();j++){
		int nxt=cur[x][j];
		if(nxt!=fa){
			dp[nxt]=dp[x]-2*siz[nxt]+n;
			dfs2(nxt,x);
		}
	}
	return ;
}
```


---

## 作者：hgzxHZR (赞：1)

换根大法板子题。

首先，第一遍 DFS 求所有点到节点 $1$ 的距离和。

这部分代码如下

```cpp
int DFS(const int &r,const int &fa)//第一次DFS求所有点到1的距离和
{
	int cnt=0;
	for(int i=head[r];i;i=E[i].Next)
	{
		int v=E[i].To;
		if(v==fa) continue;
		int tmp1=DFS(v,r);
		cnt+=siz[v];
		dis[r]+=dis[v]+siz[v]*E[i].W;
	}
	return siz[r]=cnt+c[r];
}
```

然后，如图所示
![](https://cdn.luogu.com.cn/upload/image_hosting/nbjx99nq.png)
我们已经得出了所有点到 $1$ 的距离之和，记作 $dis[1]$，以 $(1,2)$ 这条边为例，节点 $2,5,6,7$ 到 $1$ 共经历了 $4$ 次。

假设我们接下来求 $dis[4]$，那么对于 $
(1,4)$ 之外的边，其余边经历的次数不变，而对于 $(1,4)$ 这条边，节点 $4$ 及其子树不用再经历一次，那么 $dis[4]$ 相较于 $dis[1]$ 先要减去 $siz[4]\times w(1,4)$，接着其余节点到 $4$ 分别又要多走 $w(1,4)$，那么 $dis[4]$ 相较于 $dis[1]$ 先要加上 $(n-siz[4])\times w(1,4)$。

综上有，如果 $u$ 是 $v$ 的父亲，那么就有 $dis[v]=dis[u]+(n-siz[v]\times 2)\times w(u,v)$，即换根递推式。

这部分代码如下

```cpp
void DFS2(const int &r,const int &fa)//第二次DFS换根大法 
{
	for(int i=head[r];i;i=E[i].Next)
	{
		int v=E[i].To;
		if(v==fa) continue;
		dis[v]=dis[r]+(sum-2*siz[v])*E[i].W;
		DFS2(v,r);
	}
	return ;
}
```

最终代码如下

```cpp
#include<bits/stdc++.h>

#define int long long
using namespace std;
const int MAXN=2e5+5;

int tot,head[MAXN];
struct tEdge{
	int Next,To;
	int W;
	void ADD(const int &u,const int &v,const int &dis)
	{
		Next=head[u],To=v;W=dis;
		head[u]=tot;
		return ;
	}
}E[MAXN<<1];//链式前向星存树，建双向边 
int n,c[MAXN],u,v,w,sum;

int siz[MAXN],dis[MAXN];
int DFS(const int &r,const int &fa);
void DFS2(const int &r,const int &fa);//这部分代码如上

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;++i) {c[i]=1;sum+=c[i];}
	for(int i=1;i<n;++i) {cin>>u>>v;w=1;E[++tot].ADD(u,v,w),E[++tot].ADD(v,u,w);}//输入 
	
	DFS(1,0);DFS2(1,0);
	for(int i=1;i<=n;++i) cout<<dis[i]<<"\n";
	
	return 0;
}
```



---

## 作者：EityDawn (赞：1)

## 题面描述

给你一颗无根树，求各节点为根时，树上所有点到此节点的距离总和。

### 解题思路

先进行一次 dfs，求出以节点 $i_1$ 为根时，各子树的大小，设 $size_i$ 表示以 $i$ 为根的子树大小，$w_{(u,v)}$ 为节点 $u$ 到节点 $v$ 的权值，$v∈son_{u}$，以 $dis_u$ 表示 $u$ 为根时子树到根节点的距离之和。
$$
 f_u=∑_{v,v∈son(u)}f_v+size_v
$$
且有
$$
 dis_u=dis_u+dis_{v}+size_v×w_{(u,v)}
$$
第二遍 dfs，在第一遍搜索的基础上，利用换根大法，求各节点为根时，其他节点到该节点的距离和，也就是广为人知的换根 dp，则有以下方程
$$
dis_v=dis_v+dis_u+(n-2×size_v)×w_{(u,v)}
$$
最后，遍历一遍 dis 数组，全部输出就可以啦。

时间复杂度 $O(n)$。

## AC代码
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
const int N=5e5;
inline void read(int &x){x=0;int w=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') w=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}x=x*w;return;}
inline void write(int x){x<0?x=-x,putchar('-'):x=x;if(x>=10) write(x/10);putchar(x%10^48);return;}
struct node{
	int nt,to,w;
} e[N+10];
int hd[N],siz[N],dis[N],cow[N];
int u,v,w,n,ans=0,sum=0;
void dfs1(int u,int fa)
{
	siz[u]=1;
	for(int i=hd[u];i;i=e[i].nt)
	{
		if(e[i].to!=fa) 
		{
			dfs1(e[i].to,u); 
			siz[u]+=siz[e[i].to];
			dis[u]+=dis[e[i].to]+siz[e[i].to]*e[i].w;
		}		
	}
	return;
}
void dfs2(int u,int fa)
{
	for(int i=hd[u];i;i=e[i].nt)
	{
		if(e[i].to!=fa) 
		{
			dis[e[i].to]=dis[u]+(n-2*siz[e[i].to])*e[i].w;
			dfs2(e[i].to,u);
		}		
	}
	return;
}
signed main()
{
	read(n);int cnt=0;
	for(int i=1;i<n;i++) 
	{
		read(u),read(v);
		e[++cnt]=(node){hd[u],v,1},hd[u]=cnt;
		e[++cnt]=(node){hd[v],u,1},hd[v]=cnt;
	}
	dfs1(1,0);
	dfs2(1,0);
	for(int i=1;i<=n;i++)
		write(dis[i]),putchar('\n');
	return 0;
}
```

---

## 作者：zhzkiller (赞：1)

## 题目描述 / 翻译
给定一颗无根树，要求求出以每个点为根时树上所有点到根节点的距离总和。

## 解题思路
距离好求，跑一次 dfs 即可。

设 $size_i$ 表示以 $i$ 为根的子树大小，$f_i$ 表示以 $i$ 为根的子树上所有点到 $i$ 的距离总和，则有方程

$$f_u=\sum_{v,v\in son(u)}f_v+size_v$$

意思就是再往上向根走的话就要再让一个整个子树都再走 $1$。

但数据范围告诉我们最多让你带个 $\log$。既然如此，我们可以考虑在已有线索基础上继续快速转移。

我们再设 $F_i$ 表示以 $i$ 为根时整棵树上节点到 $i$ 的距离总和，也就是我们要求的答案，那么易知对于在第一次 dfs 中选取的根节点 $x$ 而言，有

$$F_x=f_x$$

接下来我们利用已知的 $F_i$ 继续转移。有方程

$$F_v=F_u+(size_x-size_v)-size_v=F_u+size_x-2\times size_v,v\in son(u)$$

其实$F_u$ 就是以 $v$ 为子树的所有点到 $u$ 的距离总和加上除 $v$ 的子树以外所有点到 $u$ 的距离总和。对于我们而言，有用的信息是以上内容中根换为 $v$ 的内容。如何转移？根换为 $v$ 后，等于让 $v$ 的子树以外的点都再走 $1$，让 $v$ 的子树的点都少走 $1$，这才有了如上方程。

再跑一次 dfs 就行啦。总体时间复杂度 $O(n)$。

这类在树上进行的要求对每个根统计一次全树答案的类似线性复杂度的算法就是**换根 dp**，也叫**二次扫描与换根法**。

完结撒花~

献上蒟蒻的 AC 代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=200010;

int n;
int h[N],cnt;
ll siz[N],f[N],F[N];

struct node
{
	int ne,to;
}edg[N<<1];

void adds(int x,int y)
{
	cnt++;
	edg[cnt].ne=h[x];
	edg[cnt].to=y;
	h[x]=cnt;
}

void dfs(int x,int fa)
{
	siz[x]=1;
	for(int i=h[x];i;i=edg[i].ne)
	{
		int y=edg[i].to;
		if(y==fa) continue;
		dfs(y,x);
		siz[x]+=siz[y];
		f[x]+=f[y]+siz[y];
	}
}

void dp(int x,int fa)
{
	for(int i=h[x];i;i=edg[i].ne)
	{
		int y=edg[i].to;
		if(y==fa) continue;
		F[y]=F[x]+siz[1]-2*siz[y];
		dp(y,x);
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%d %d",&u,&v);
		adds(u,v);adds(v,u); 
	}
	
	dfs(1,0);
	F[1]=f[1];
	dp(1,0);
	
	for(int i=1;i<=n;i++) printf("%lld\n",F[i]);
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：1)

dp，思路挺简单的。

------------

很快想到，可以维护根的转移。

首先一次深搜求出 $1$ 为根时的答案，同时求出第 $i$ 个点为根的子树大小 $size_i$。

如果根从 $x$ 变为它的子节点 $y$，答案会减少 $size_y$ 增加 $n-size_y$。

于是再深搜一次求出各点的答案即可。

复杂度 $\operatorname{O}(n)$。

------------

就挺板的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=4e5+84;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
inline void write(register ll x){
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return ;
}
struct Edge{
    ll to,ne;
}e[maxn];
ll n,x,y,ecnt=1,ans[maxn],head[maxn],sizE[maxn];
inline void add(ll u,ll v){
    e[ecnt]={v,head[u]};
    head[u]=ecnt++;
    return ;
}
inline ll dfs(ll x,ll dep,ll fa){
    ll cnt=dep;
    sizE[x]=1;
    for(ll i=head[x];i;i=e[i].ne){
        if(e[i].to==fa)
            continue;
        cnt+=dfs(e[i].to,dep+1,x);
        sizE[x]+=sizE[e[i].to];
    }
    return cnt;
}
inline void dfs_q(ll x,ll fa){
    if(x!=1)
        ans[x]=ans[fa]-sizE[x]+(n-sizE[x]);
    for(ll i=head[x];i;i=e[i].ne)
        if(e[i].to!=fa)
            dfs_q(e[i].to,x);
    return ;
}
int main(){
    n=read();
    for(ll i=1;i<n;i++){
        x=read();
        y=read();
        add(x,y);
        add(y,x);
    }
    ans[1]=dfs(1,0,0);
    dfs_q(1,0);
    for(ll i=1;i<=n;i++){
        write(ans[i]);
        putchar('Sherry');
    }
    return 0;
}
```


---

## 作者：loser_seele (赞：1)

首先先计算出 $ 1 $ 到每个点的距离之和，dfs 一遍即可。

然后考虑根节点从 $ 1 $ 换到一个相邻的点 $ a $ 的时候答案发生的变化：

如果 $ j $ 在 $ a $ 的子树中，则显然距离会 $ -1 $，否则距离会 $ +1 $，这步是显然的。

所以设 $ siz_a $ 为 $ a $ 的子树大小，某节点到其他节点的距离之和为 $ ans $，则有 $ ans_s=ans_1+n-2 \times sub_a $。

于是在第一遍 dfs 的时候计算出距离之和和子树大小，第二遍 dfs 计算答案即可，时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define ll long long
ll N, a, b, sz[200010], ans[200010], par[200010], total;
bool vis[200010], vis2[200010];
vector<int> D[200010];
void dfs(ll x, ll dist)
{
	vis[x]=1;
	total+=dist;
	sz[x]=1;
	for(auto i:D[x])
	{
		if(!vis[i]) 
		{
			dfs(i,dist+1);
			par[i]=x;
			sz[x] += sz[i];
		}
	}
}
void dfs2(ll x)
{
	if(vis2[x]) 
	return; 
	vis2[x]=1;
	if(x!=1)
		ans[x]=ans[par[x]]+N-2*sz[x];
	for(auto i:D[x])
		dfs2(i);
}
int main()
{
	cin>>N;
	for(int i=1;i<N;i++)
	{
		cin>>a>>b;
		D[a].push_back(b);
		D[b].push_back(a);
	}
	dfs(1,0);
    ans[1]=total;
    dfs2(1);
	for(int i=1;i<=N;i++)
	cout<<ans[i]<<'\n';
}
```


---

## 作者：ruanwentao666 (赞：0)

# [ABC220F] Distance Sums 2 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc220_f)
- 
## 题意分析
给定一个树，求以任意节点为根时，所有结点深度的和。

## 解题方式
树形 DP，准确来说是换根 DP。

## 动规四部曲
1. 设计状态：定义 $f_u$ 为以 $u$ 为根时，所有结点深度的和。
2. 确定状态转移方程：设 $u$ 的子结点为 $v$，则有 $f_v = f_u + n - 2 \times s_v$，稍后会做说明。
3. 设置初始条件和边界：我们发现，状态转移方程是从父结点推到子结点，那么必定需要先计算出 $f_1$
4. 确定计算顺序：根据状态转移方程，我们可以得出计算顺序是自顶向下。

## 状态转移方程的推导
设 $s_i$ 来表示以 $i$ 为根的子树中的结点个数，并且有 $s_u=1+\sum s_v$。显然需要一次 DFS 来计算所有的  $s_i$，这次的 DFS 就是预处理，我们得到了以某个结点为根时其子树中的结点总数。

显然在换根的转移过程中，以 $v$ 为根或以 $u$ 为根会导致其子树中的结点的深度产生改变。具体表现为：

- 所有在 $v$ 的子树上的结点深度都减少了一，那么总深度和就减少了 $s_v$。
- 所有不在 $v$ 的子树上的结点深度都增加了一，那么总深度和就增加了 $n-s_v$。

根据这两个条件就可以推出状态转移方程 $f_v = f_u - s_v + n - s_v=f_u + n - 2 \times s_v$。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, u, v;
vector<int>g[N];
long long s[N], f[N], d[N];
void dfs(int u, int fa) {
	s[u] = 1;
	d[u] = d[fa] + 1;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v != fa) {
			dfs(v, u);
			s[u] += s[v];
		}
	}
}
void dfs2(int u, int fa) {
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v != fa) {
			f[v] = f[u] + n - 2 * s[v];
			dfs2(v, u);
		}
	}
}
int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 1);
	for (int i = 1; i <= n; i++) {
		f[1] += d[i] - 1;
	}
	dfs2(1, 1);
	long long ans = 0, id;
	for (int i = 1; i <= n; i++) {
		cout << f[i] << "\n";
	}
	return 0;
}
```



---

## 作者：rainygame (赞：0)

换根板子题。

暴力非常简单，只需要对于每个点为根跑一遍 dfs 统计深度和之后输出即可。

但是这样是 $O(n^2)$ 的，考虑优化。

我们可以先求出以 $1$ 为根的深度和，然后通过以 $1$ 为根的答案求出其它的答案。

假设我们有已经求出以 $u$ 为根的答案，它在以 $1$ 为根的有根树上有一个儿子 $v$。考虑求出以 $v$ 为根的答案。

我们可以发现，共有 $siz_v$ 个节点的深度减了 $1$，有 $n-siz_v$ 个节点的深度加了 $1$（$siz_v$ 表示以 $1$ 为根时 $v$ 的子树大小）。所以它增加的贡献为 $n-2siz_v$。

按照这样推下去即可，只需要再进行一次 dfs 即可求出所有答案。时间复杂度 $O(n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 200001

int n, u, v;
int siz[MAXN], f[MAXN];
vector<int> e[MAXN];

void dfs(int x, int fa, int dep){
    f[1] += dep;
    siz[x] = 1;
    for (auto i: e[x]){
        if (i ^ fa){
            dfs(i, x, dep+1);
            siz[x] += siz[i];
        }
    }
}

void dfs2(int x, int fa){
    for (auto i: e[x]){
        if (i ^ fa){
            f[i] = f[x]+n-(siz[i]<<1);
            dfs2(i, x);
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i(1); i<n; ++i){
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 0, 0);
    dfs2(1, 0);

    for (int i(1); i<=n; ++i) cout << f[i] << '\n';

    return 0;
}

```


---

## 作者：ttq012 (赞：0)

考虑换根dp。

首先设 $dep_x$ 表示 $1$ 为根的时候 $x$ 的深度，$sz_x$ 表示 $1$ 为根的时候 $x$ 子树的大小。

然后设 $ans_x$ 表示 $x$ 为根的时候的答案。容易发现 $u\to x$ 从父亲节点到儿子节点的时候，$x$ 子树节点全部往上移动一个，其他节点全部往下移动一个。$ans_v=ans_u-sz_v+(n-sz_v)$。

初始条件 $ans_1 = \sum dep_i$。

两遍 dfs 搜索即可。时间复杂度 $O(n)$。


---

## 作者：cppcppcpp3 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc220_f)。

## Solution
换根 dp 的板子题。

由于 $n \le 2 \times 10^5$，不可能直接分别枚举每个点为根来搜索，故使用换根 dp。

我们通过对无根树两次 dfs 得到每个节点为根时的答案。

不妨先令 $1$ 为根。第一次，搜索整棵树，得到每个节点的深度 $dep_i$，子树大小 $son_i$。此时我们得到以 $1$ 为根的答案 $tot_1=\sum\limits_{i=1}^{n} dep_i$。

第二次要得到以其他点为根时的深度总和。考虑**把根从节点 $u$ 移到某个儿子 $v$，$tot_u$ 和 $tot_v$ 之间的关系**（换根 dp 的关键，根转移到后的答案可以由已知推得）。不难发现根移动后，在 $v$ 的子树内的点离根节点更近一步，同时其他点的的深度加 $1$。此时 $son_i$ 就发挥了作用，有 $tot_v=tot_u+(n-son_v)-son_v$。

最后顺序输出 $tot_i$ ，复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=2e5+5;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,cnt,head[N],dep[N],son[N],tot[N];

struct edge{
	int to,nxt;
}e[N<<1];

il void add(int u,int v){
	e[++cnt]=edge{v,head[u]},head[u]=cnt;
}

void dfs(int u,int fa){
	if(u^1) dep[u]=dep[fa]+1;
	son[u]=1,tot[1]+=dep[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v^fa) dfs(v,u),son[u]+=son[v];
	}
}

void solve(int u,int fa){
	if(u^1) tot[u]=tot[fa]-son[u]+(n-son[u]);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v^fa) solve(v,u);
	}
}

main(){
	n=wrd();
	for(int i=1;i<n;++i){
		int u=wrd(),v=wrd();
		add(u,v),add(v,u);
	}
	dfs(1,0),solve(1,0);
	for(int i=1;i<=n;++i) printf("%lld\n",tot[i]);
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

# 思路
这一道题可以用树上 DP 来做，一个节点可以用父节点 $O(1)$ 的推出来，就相当于整体向儿子节点的子树靠近 $1$，然后剩下的节点远离 $1$，我们可以推出来 $ans_x=ans[fa_x]+(n-sz_x)-sz_x$，最后 dfs 遍历一遍就好了。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=500500;
vector<int>e[maxn];
int n,dep[maxn],sz[maxn],ans[maxn];
void dfs1(int u,int f){
	sz[u]=1;
	dep[u]=dep[f]+1;
	for(int v:e[u]){
		if(v!=f){
			dfs1(v,u);
			sz[u]+=sz[v];
		}
	}
}
void dfs2(int u,int f){
	if(u!=1){
		ans[u]=ans[f]+(n-sz[u])-sz[u];
	}
	for(int v:e[u]){
		if(v!=f){
			dfs2(v,u);
		}
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dep[0]=-1;
	dfs1(1,0);
	for(int i=1;i<=n;i++){
		ans[1]+=dep[i];
	}
	dfs2(1,0);
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}
```

---

