# Brooklyn Round 1 & NNOI Round 1 D - Apples

## 题目描述

小 X 有一颗 $n$ 个结点的树，树的根结点为 $1$，规定根结点的深度为 $1$。树是指一个由 $n$ 个结点，$n-1$ 条双向边组成的连通块。你通过每条边都需要 $1$ 秒。你在每秒钟可以停在原地，也可以经过 $1$ 条边。

树的结点会随机刷新 $m$ 次，第 $i$ 次在 $t_i$ 时刻在 $w_i$ 号结点刷新出 $p_i$ 个苹果，但存在时间只有 $1$，过后会消失。

这颗树有两个特殊的性质：

+ 最深的结点深度不会超过 $s$。

+ 所有的 $t_i$ 均不相同。

最开始时，你在根结点，请问你最多能采多少个苹果。

## 说明/提示

**本题采用捆绑测试。**
| 子任务编号 | $n$ | $m$ | 特殊性质 | 分值|
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $= 5$ | $= 5$ |无 |$10$|
| $2$ | $= 20$ | $= 20$ | 无 |$10$|
| $3$ | 无 | 无 | A |$20$|
| $4$ | 无 | 无 | B |$20$|
| $5$| $= 10^3$ | $= 10^3$ | 无 |$20$|
| $6$| 无 | 无 | 无 |$20$|

对于 $100\%$ 的数据，$1 \le n \le 8 \times 10^4,1 \le m \le 2 \times 10^4,1 \le s \le 10^3,1 \le p_i,t_i \le 10^9,1 \le w_i \le n$。

特殊性质 A：$s = 2$。

特殊性质 B：这棵树是一条以根节点为端点的链。

## 样例 #1

### 输入

```
5 3 5
1 2
1 3
2 4
2 5
1 5 3
2 7 8
3 8 10```

### 输出

```
13```

# 题解

## 作者：jiangby2011 (赞：3)

这份代码是目前的最优解。

读题，发现是很典型的动态规划。唯一新鲜的东西就是**限制了树的深度。**

转移方程是很显然的。设 $dp_i$ 是在采第 $i$ 个冒出的苹果的前提下，总共能有的最多苹果。

$$dp_i = dp_j + p_i(dis_{w_i , w_j}\leq t_i - t_j )$$

这个转移是 $O(m ^ 2)$ 的。考虑优化，发现两个点的距离不超过 $s \times 2$ 。再读题，发现时间不重复，这意味着如果我们现在处理的是第 $i$ 个冒出的苹果 , $i - s \times 2$ 以前的苹果我们一定可以及时赶到。

所以只需要记录以前 $dp$ 数组的最大值即可。

代码有详细的注释。


```cpp
#include <bits/stdc++.h>
#define int long long
constexpr int N = 8e4 + 5;	
constexpr int M = 2e4 + 5;
using namespace std;
int ans , cnt , n , m , s , u , v , w[M] , t[M] , p[M] , head[N] , dp[M] , Max[M] , deep[N] , father[N] , siz[N] , top[N] , son[N];
struct edge {
	int t , n;
}e[N << 1];
//-----------------------------------------------------这一坨就是lca + 前向星 + 快读，对本题没有特殊性
inline int lca(int u , int v) {
	while(top[u] != top[v]) {
		if(deep[top[u]] < deep[top[v]]) swap(u , v);
		u = father[top[u]];
	}
	return deep[u] < deep[v] ? u : v;
}
inline void add(int x , int y) {
	e[++cnt].t = y , e[cnt].n = head[x] , head[x] = cnt;
}
struct query {
	int w , t , p;
}a[M];
inline bool cmp(query b , query c) {
	return b.t < c.t;
}
inline int dis(int b , int c) {
	return deep[b] + deep[c] - (deep[lca(b , c)] << 1);
}
void dfs(int s , int fa) {
	siz[s] = 1;
	father[s] = fa;
	deep[s] = deep[fa] + 1;
	for(register int i = head[s]; i; i = e[i].n) {
		int to = e[i].t;
		if(to == fa) continue;
		dfs(to , s);
		if(siz[to] > siz[son[s]]) {
			son[s] = to;
		}
		siz[s] += siz[to];
	}
}
void Dfs(int s , int belong) {
	top[s] = belong;
	if(!son[s]) {
		return;
	}
	Dfs(son[s] , belong);
	for(register int i = head[s]; i; i = e[i].n) {
		int to = e[i].t;
		if(to == father[s] || to == son[s]) continue;
		Dfs(to , to);
	}
}
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
//-------------------------------------------------------
signed main() {
	n = read() , m = read() , s = read();
	for(register int i(1); i < n; ++i) {
		u = read() , v = read();
		add(u , v) , add(v , u);
	}
	dfs(1 , 0);
	Dfs(1 , 1);
	for(register int i(1); i <= m; ++i) {
		a[i].w = read() , a[i].t = read() , a[i].p = read();
	} 
	sort(a + 1 , a + m + 1 , cmp);
	for(register int i(1); i <= m; ++i) {
		if(deep[a[i].w] <= a[i].t) {
			dp[i] = a[i].p;//处理出默认值
		}
		for(register int j(i - 1); j >= (max((int)1 , i - s * 2)); --j) {
			if(dis(a[j].w , a[i].w) <= a[i].t - a[j].t) {
				dp[i] = max(dp[i] , dp[j] + a[i].p);//即我上文写的转移方程
			}
			if(a[i].t - a[j].t >= s * 2) {
				dp[i] = max(dp[i] , Max[j - 1] + a[i].p);//本题精华剪枝。i - s * 2 之前的点都一定可以准时到达，没必要判断时间是否来得及
				break;
			}
		}
		Max[i] = max(Max[i - 1] , dp[i]);//记录以前转移的最优解
		ans = max(ans , dp[i]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：ZHR100102 (赞：1)

[Blog](https://www.cnblogs.com/zhr0102/p/18909343)

糖糖题。

容易设计出一个线性 DP：$dp_i$ 表示吃到第 $i$ 个苹果后的最大苹果数，然后 $O(m^2)$ 枚举前一个苹果，计算两个位置间的距离是否在时间差内，在的话就转移即可。

这样是显然不可过的，因此考虑另一个没有用到的限制：树的深度 $\le s$，而 $s\le 10^3$。注意到两点间的距离可以转化为 $u\to lca,lca \to v$ 的两段，每一段都在一条竖着的树链上，而因为深度的限制，所以每一条竖着的树链长度都 $\le s$，则**两点间的距离一定 $\le 2s$**。

因此发现时间差在 $2s$ 以外的都不用判断距离的限制了，而又因为 **$t$ 互不相同**，所以**要判断的苹果也不超过 $2s$ 个**，其余苹果取一个**前缀最大值**直接转移即可。时间复杂度 $O(ms+n\log n)$。

求 LCA 采用了 [DFS 序求 LCA](https://www.cnblogs.com/alex-wei/p/DFN_LCA.html " DFS 序求 LCA ") 的科技，做到了 $O(1)$ 查询的复杂度。

**将 DFS 序求 LCA 发扬光大，让欧拉序求 LCA 成为时代的眼泪！**

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=100005,M=200005;
int n,m,s;
int h[N],idx,dep[N],st[N][20],lg[N],dfn[N],tot;
struct Edge{
    int v,ne;
}e[M];
struct Node{
    ll w,t,p;
    bool operator<(const Node &a)const{
        return t<a.t;
    }
}a[N];
ll dp[N],pre[N];
void add(int u,int v)
{
    e[++idx]={v,h[u]};
    h[u]=idx;
}
void dfs(int u,int fa)
{
    dfn[u]=++tot;
    st[dfn[u]][0]=fa;
    dep[u]=dep[fa]+1;
    for(int i=h[u];i;i=e[i].ne)
    {
        int v=e[i].v;
        if(v==fa)continue;
        dfs(v,u);
    }
}
int getmin(int x,int y)
{
    return (dep[x]<dep[y]?x:y);
}
void init()
{
    for(int i=1;i<=100000;i++)lg[i]=int(log2(1.0*i));
    for(int j=1;j<=19;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            st[i][j]=getmin(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int getlca(int u,int v)
{
    if(u==v)return u;
    u=dfn[u],v=dfn[v];
    if(u>v)swap(u,v);
    ++u;
    return getmin(st[u][lg[v-u+1]],st[v-(1<<lg[v-u+1])+1][lg[v-u+1]]);
}
int getdis(int u,int v)
{
    int lca=getlca(u,v);
    return (dep[u]+dep[v]-2*dep[lca]);
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>s;
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    for(int i=1;i<=m;i++)
        cin>>a[i].w>>a[i].t>>a[i].p;
    sort(a+1,a+m+1);
    dfs(1,0);
    init();
    memset(dp,-0x3f,sizeof(dp));
    memset(pre,-0x3f,sizeof(pre));
    dp[0]=pre[0]=0;
    a[0]={1,0,0};
    for(int i=1;i<=m;i++)
    {
        for(int j=max(0,i-2*s);j<i;j++)
        {
            if(getdis(a[i].w,a[j].w)>a[i].t-a[j].t)continue;
            dp[i]=max(dp[i],dp[j]+a[i].p);
        }
        if(i-2*s>=0)dp[i]=max(dp[i],pre[i-2*s]+a[i].p);
        pre[i]=max(pre[i-1],dp[i]);
    }
    cout<<pre[m];
    return 0;
}
```

---

## 作者：篮网总冠军 (赞：1)

考虑 $dp$。

如果直接暴力 $dp$ 是会超时的，因为 $m^2$ 本身很大，还有一个 LCA 的 $\log$。

观察题目，很容易得出一些结论。

因为 $t_i$ 均不相同，所以我们很易得出：每轮需要枚举的个数不会超过 $2 \times s$，如果 $t_i$ 的差距超过 $2 \times s$，直接取 $\max$ 即可。

时间复杂度 $O(ms \log s)$。

std：


```cpp
#include <bits/stdc++.h>
using namespace std;

long long dp[20005],maxdp[200005];
int lca[80005][20],dep[80005],fa[80005];
vector<int>a[80005];
struct node{
	int w,t,p;
}apple[20005];
void dfs(int w,int f){
	fa[w]=f;
	dep[w]=dep[f]+1;
	lca[w][0]=f;
	for(int i=1;(1<<i)<=dep[w];i++){
		lca[w][i]=lca[lca[w][i-1]][i-1];
	}
	for(int i=0;i<a[w].size();i++){
		if(a[w][i]==f) continue;
		dfs(a[w][i],w);
	}
}
bool cmp(node x,node y){
	return x.t<y.t;
}
int qlca(int x,int y){
	if (dep[x]<=dep[y]) swap(x,y);
	if (x==y) return x;
	for(int i=18;i>=0;i--){
		if (dep[lca[x][i]]>=dep[y]) x=lca[x][i];
		if(x==y) return x;
	}
	for(int i=18;i>=0;i--){
		if (lca[x][i]!=lca[y][i]) x=lca[x][i],y=lca[y][i];
	}
	return lca[x][0];
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int n,m,s;
	cin>>n>>m>>s;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	for(int i=2;i<=m+1;i++){
		cin>>apple[i].w>>apple[i].t>>apple[i].p;
	}
	dfs(1,0);
	sort(apple+2,apple+1+m+1,cmp);
	apple[1].w=1,apple[1].t=0,apple[1].p=0;
	int last=1;
	long long ans=0;
	for(int i=2;i<=m+1;i++){
		while(apple[i].t-apple[last].t>2*s) last++;
		for(int j=last;j<i;j++){
			int v=qlca(apple[i].w,apple[j].w);
			int po=dep[apple[i].w]+dep[apple[j].w]-dep[v]*2;
			if (po<=apple[i].t-apple[j].t) dp[i]=max(dp[i],dp[j]+apple[i].p);  
		}
		if (last!=1) dp[i]=max(dp[i],maxdp[last-1]+apple[i].p);
		ans=max(ans,dp[i]);
		maxdp[i]=max(dp[i],maxdp[i-1]);
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：ycy1124 (赞：0)

### 前置知识
[倍增求 lca](https://oi-wiki.org/graph/lca/#%E5%80%8D%E5%A2%9E%E7%AE%97%E6%B3%95)。
### 题意
应该不需要讲了吧。
### 思路
发现这道题与一般的树上问题不同的地方在于这道题限制了树的深度 $s\le 10^3$。我们考虑这个限制有什么用。不难发现如果我们能从某一次操作 $i$ 转移到 $j$ 那么需要满足 $dep_{w_i} + dep_{w_j} - 2\times dep_{lca(w_i, w_j)} \le t_j - t_i$。由于我们任意的的 $dep_i \le s\le 10^3$，因此我们的 $dep_{w_i} + dep_{w_j} - 2 \times dep_{lca(w_i,w_j)}\le 2\times s \le 2\times 10^3$。也就是说，如果我们的 $t_j - t_i \ge 2\times s$ 就一定可以转移。因此我们按 $t_i$ 从小到大排序后 dp。枚举到 $dp_i$ 时给所有 $t_i - t_j \ge 2\times s$ 的 $dp_j$ 做一个前缀 $\max$。然后只需要暴力转移 $t_i - t_j < 2\times s$ 的即可。由于我们的 $t_i$ 互不相同且 $2\times s\le 2 \times 10^3$，因此我们的复杂度为 $\mathcal{O}(m\times s)$。可以通过。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 80000 + 39
#define M 20000 + 39
#define flush() fwrite(obuf,1,O-obuf,stdout)
#define putchar(x) ((O==obuf+(1<<21))&&(flush(),O=obuf)),*O++=x
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
__inline__ int read(){
	register int x=0;
	register char ch=getchar();
	while(!(ch>='0'&&ch<='9'))
		ch=getchar();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch^48),ch=getchar();
	return x;
}
__inline__ void write(register long long x){
    (x>9)?write(x/10):void();
    putchar((x%10)^48);
}
struct Flush{
    ~Flush(){flush();}
}_;
using namespace std;
struct Node
{
	int w, t, p;
}a[N];
int n, m, s, lca[N][39], dep[N], tmp, ma, ans, dp[M];
vector<int>qwq[N];
inline void dfs(int p, int f)
{
	dep[p] = dep[f] + 1;
	for(int i = 1; i < 39; i ++)
	{
		if(!lca[lca[p][i - 1]][i - 1])
		{
			break;
		}
		lca[p][i] = lca[lca[p][i - 1]][i - 1];
	}
	for(auto it : qwq[p])
	{
		if(it == f)
		{
			continue;
		}
		lca[it][0] = p;
		dfs(it, p);
	}
}
inline bool cmp(Node x1, Node x2)
{
	return x1.t < x2.t;
}
inline int Lca(int u, int v)
{
	if(dep[u] > dep[v])
	{
		swap(u, v);
	}
	int x = dep[v] - dep[u];
	for(int i = 0; i < 39; i ++)
	{
		if((x >> i) & 1)
		{
			v = lca[v][i];
		}
	}
	if(u == v)
	{
		return u;
	}
	for(int i = 39 - 1; i >= 0; i --)
	{
		if(lca[u][i] != lca[v][i])
		{
			u = lca[u][i], v = lca[v][i];
		}
	}
	return lca[u][0];//倍增求lca
}
inline int Max(int x, int y)
{
	return x < y ? y : x;
}
signed main()
{
	n = read(), m = read(), s = read();
	for(int i = 1; i < n; i ++)
	{
		int u = read(), v = read();
		qwq[u].push_back(v);
		qwq[v].push_back(u);
	}
	dep[1] = 1;
	dfs(1, 0);
	for(int i = 1; i <= m; i ++)
	{
		a[i].w = read(), a[i].t = read(), a[i].p = read();
	}
	sort(a + 1, a + m + 1, cmp);
	for(int i = 1; i <= m; i ++)
	{
		while(a[tmp + 1].t + 2 * s <= a[i].t)
		{
			tmp ++;
			ma = Max(ma, dp[tmp]);
		}
		dp[i] = Max(dp[i], ma + a[i].p);//转移前缀max
		if(dep[a[i].w] > a[i].t)//如果从根节点都不能直接到达答案显然为0
		{
			dp[i] = 0;
		}
		for(int j = tmp + 1; j < i; j ++)//暴力转移
		{
			if(dep[a[i].w] + dep[a[j].w] - 2 * dep[Lca(a[i].w, a[j].w)] <= a[i].t - a[j].t)
			{
				dp[i] = Max(dp[i], dp[j] + a[i].p);
			}
		}
		ans = Max(ans, dp[i]);
	}
	write(ans);
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/231682307)。

---

