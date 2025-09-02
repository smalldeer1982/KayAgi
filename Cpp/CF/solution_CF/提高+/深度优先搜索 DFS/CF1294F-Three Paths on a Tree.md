# Three Paths on a Tree

## 题目描述

You are given an unweighted tree with $ n $ vertices. Recall that a tree is a connected undirected graph without cycles.

Your task is to choose three distinct vertices $ a, b, c $ on this tree such that the number of edges which belong to at least one of the simple paths between $ a $ and $ b $ , $ b $ and $ c $ , or $ a $ and $ c $ is the maximum possible. See the notes section for a better understanding.

The simple path is the path that visits each vertex at most once.

## 说明/提示

The picture corresponding to the first example (and another one correct answer):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1294F/77ac761e87577c88357c329d0c2cba3e83446e14.png)

If you choose vertices $ 1, 5, 6 $ then the path between $ 1 $ and $ 5 $ consists of edges $ (1, 2), (2, 3), (3, 4), (4, 5) $ , the path between $ 1 $ and $ 6 $ consists of edges $ (1, 2), (2, 3), (3, 4), (4, 6) $ and the path between $ 5 $ and $ 6 $ consists of edges $ (4, 5), (4, 6) $ . The union of these paths is $ (1, 2), (2, 3), (3, 4), (4, 5), (4, 6) $ so the answer is $ 5 $ . It can be shown that there is no better answer.

## 样例 #1

### 输入

```
8
1 2
2 3
3 4
4 5
4 6
3 7
3 8```

### 输出

```
5
1 8 6```

# 题解

## 作者：syksykCCC (赞：14)

介绍一种自己的乱搞做法。

首先设选取的三个点分别为 $du, dv, dw$。

我们可以发现，三条路径的并集可以看作是有唯一的一个交点，例如样例：

![image.png](https://i.loli.net/2020/01/26/cV27jt4s6IOTCxm.png)

交点为 $4$。

那么，问题就变成了，找到一个 $u$  作为交点，$du, dv, dw$ 一定是到 $u$ 距离最远的，**且不在同一棵子树里** 的三个点。

为什么不在同一棵子树里？

因为如果 $du, dv$ 在一棵子树里，显然，我们可以找到它们分叉的地方，比如叫做 $v$，那 $u \to v \to du$ 和 $u \to v \to dv$ 两条路径就有 $u \to v$ 这一段相交的地方，那么交点就大可以设成 $v$ 了。

于是 $\mathcal O(n^2)$ 的做法不难想到：枚举 $u$，$n$ 次 BFS，暴力求出最远点更新答案。

这个做法显然是会 TLE 的，正解需要下面这个结论：

> $du, dv$ 一定是树的直径的两个端点。

为什么呢？

比如我们有这么一棵树，它的直径用红色标出。

![image.png](https://i.loli.net/2020/01/26/HBsaVyfD4bkZeEG.png)

分两种情况：

* 枚举到的 $u$ 在直径上。

那么我们要证明的就是最远的两条链 $du, dv$ 一定是树的直径的端点。

![image.png](https://i.loli.net/2020/01/26/tpsJc5EeOjnBdzY.png)

比如我们枚举到了这样的 $u$，我们发现 $u$ 除了直径还有一棵子树，这个里面离 $u$ 最远的叫做 $w$。

那么我们有：

$$ dis(u, a) \ge dis(u, w) \cdots \cdots (1)$$
$$ dis(u, b) \ge dis(u, w) \cdots \cdots (2) $$

![image.png](https://i.loli.net/2020/01/26/c1vCHywILkZ48fp.png)

$(1)$ 是因为，如果有 $dis(u, w) > dis(u, b)$ 了，那么树的直径就不可能是 $a \to b$，而是 $a \to w$ 了；$(2)$ 也同理可证。

那么，$u$ 除了子树里面的点，也就 $a, b$ 两个选择了，所以 $du = a$，$dv = b$。

* 枚举到的 $u$ 不在直径上。

![image.png](https://i.loli.net/2020/01/26/tFBTa3VHPOseoj2.png)

我们还是设 $u$ 的子树（这次有两棵）离 $u$ 最远的点为 $w$。再设 $u$ 不断沿着父亲追溯到直径上的点为 $v$。

同上，可以得到：

$$ dis(v, a) \ge dis(v, w) = dis(u, v) + dis(u, w) $$
$$ dis(v, b) \ge dis(v, w) = dis(u, v) + dis(u, w) $$

![image.png](https://i.loli.net/2020/01/26/sxE7qrlVRITZ1jd.png)

右边去掉一个 $dis(u, v)$ 不影响不等式，所以：

$$ dis(v, a) \ge dis(u, w) $$
$$ dis(v, b) \ge dis(u, w) $$

左边再加上一个 $dis(u, v)$ 也不影响不等式，所以：

$$ dis(v, a) + dis(u, v) = dis(u, a) \ge dis(u, w) $$
$$ dis(v, b) + dis(u, v) = dis(u, b) \ge dis(u, w) $$

所以我们还是会先选 $du = a$，$dv = b$！

然后既然这样了，我们就可以先找到直径，于是 $du, dv$ 就出来了。

然后记录直径上的点为 $\text{path}$，在 $\text{path}$ 上枚举 $u$，找到「不在直径上」且 「距离 $u$ 最远」的点 $w$，用来更新答案。

具体怎么实现呢？我们可以把直径拉出来，比如样例，$1 \to 5$ 是直径，那么我们就：

![image.png](https://i.loli.net/2020/01/26/fwQXGCT8a6xY2Ov.png)

把直径拉出来，然后我们从上至下记录为 $\text{path}_{1 \to len}$，我们发现，只要 $\text{path}_i$ 的儿子不是 $\text{path}_{i + 1}$，就是可以更新的。

容易设计出一个树形 DP，$f_{u}$ 表示 $u$ 最佳的长度，$g_{u}$ 表示来源，显然：

$\textbf{if } u \not \in \text{path } \textbf{then } f_u = \max\limits_{v \in \text{sons(u)}} \{f_v +1\}$   
$\textbf{else } \text{let } u \text{ be path}_i, f_u = \max\limits_{v \in \text{sons(u)}, v \text{ isn't path}_{i + 1} }\{ f_v +1\}$

$g_u$ 相应更新。

时间复杂度 $\mathcal O(n)$，代码如下，仅供参考：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, dep[N], fa[N], du, dv, dlen;
vector<int> G[N];
void dfs(int u) // 预处理
{
	for(int v : G[u]) if(v ^ fa[u])
	{
		dep[v] = dep[u] + 1;
		fa[v] = u;
		dfs(v);
	}
}
int tmp[N], cur, path[N];
void find_path(int u) // 拉出直径
{
	tmp[++cur] = u;
	if(u == dv)
	{
		for(int i = 1; i <= cur; i++) path[i] = tmp[i];
		return;
	}
	for(int v : G[u]) if(v ^ fa[u]) find_path(v);
	cur--;
}
int f[N], g[N], maxl = -1, dw;
void solve(int u, int pos) // DP
{
	if(u ^ path[pos])
	{
		for(int v : G[u]) if(v ^ fa[u])
		{
			solve(v, pos);
			if(f[u] < f[v] + 1)
				f[u] = f[v] + 1, g[u] = g[v];
		}
	}
	else
	{
		for(int v : G[u]) if(v ^ fa[u])
		{
			solve(v, pos + 1);
			if(v ^ path[pos + 1] && f[u] < f[v] + 1)
				f[u] = f[v] + 1, g[u] = g[v];
		}
	}
	if(f[u] > maxl && g[u] != du && g[u] != dv) // 注意，如果来源是 du 或 dv 就重复了，所以不行
		maxl = f[u], dw = g[u];
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dep[1] = fa[1] = 0;
	dfs(1);
	for(int i = 1; i <= n; i++) if(dep[i] > dep[du]) du = i;
	dep[du] = fa[du] = 0;
	dfs(du);
	for(int i = 1; i <= n; i++) if(dep[i] > dep[dv]) dv = i;
	dlen = dep[dv];
	find_path(du);
	cur = n;
	for(int u = 1; u <= n; u++) g[u] = u;
	solve(du, 1);
	cout << maxl + dlen << endl;
	cout << du << ' ' << dv << ' ' << dw << endl;
	return 0;
}
```

---

## 作者：两年打铁 (赞：5)

题意：找出三个点，使得两两点之间路径中边的并的集合尽量大。

把其中一个点看成根的话，就可以发现，其中一个点一定是一条直径。

为什么?

由于是并的关系，我们不用再考虑链叠一起的情况，相反，长的链贡献一定大，所以我们会先选直径。

然后把直径上的点都标记出来，去掉这些点的贡献，以直径其中一个点为根，再找出离直径这条链最远的点，没了。



```
#include<bits/stdc++.h>
#define pr putchar
#define kong putchar(' ')
#define huan putchar('\n')
using namespace std;

void read(int &x)
{
	x=0;register char ch=getchar();int pd=1;
	while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x*=pd;
}

void write(int x)
{
	if(x<0)x=-x,putchar('-');
	if(x<10)pr(x+'0');
	else write(x/10),pr(x%10+'0');
}

void wrl(int x)
{
	write(x);
	huan;
}

void wrs(int x)
{
	write(x);
	kong;
}

const int N=1e6+233;
int n;
int h[N],vis[N],deep[N],k,mx;
int ans,t,f[N],a,b;
struct dd
{
	int end,nt;
}e[1<<21];
inline void add(int begin,int end)
{
	++t;
	e[t].end=end;
	e[t].nt=h[begin];
	h[begin]=t;
}

void dfs(int x,int fa)
{
	if(vis[x])deep[x]=1;
	if(deep[x]>deep[k]&&x!=a&&x!=b)k=x,mx=deep[x];
	for(register int i=h[x];i;i=e[i].nt)
	{
		int u=e[i].end;
		if(u==fa)continue;
		f[u]=x;
		deep[u]=deep[x]+1;
		dfs(u,x);
	}
}
int main()
{
	int x,y;
	read(n);
	for(register int i=1;i<n;++i)
	{
		read(x);
		read(y);
		add(x,y);
		add(y,x);
	}
	for(register int i=1;i<=n;++i)f[i]=0;
	dfs(1,0);
	a=k;
	vis[a]=1;
	k=0;
	for(register int i=1;i<=n;++i)f[i]=0;
	dfs(a,0);
	b=k;
	int now=b;
	ans=mx-1;
	while(now)
	{
		vis[now]=1;
		now=f[now];
	}
	k=0;
	dfs(a,0);
	ans+=mx-1;
	
	cout<<ans<<endl<<a<<" "<<b<<" "<<k<<endl;
	return 0;
}


```



---

## 作者：tommymio (赞：4)

求路径并集长度最大，必然优先选一条最长的，也就是树的直径，记两端点为 $u,v$。然后考虑从直径上延伸一条路径，这条路径无论与直径交集大小为何值都没有意义，只要交集大小不小于 $1$ 即可。不妨认为它和直径的交集只有一个点。那么两遍 $\text{dfs}$ 后从直径开始 $\text{bfs}$，在 $\text{bfs}$ 过程中找到这条能够延伸出去的最长路径即可。时间复杂度为 $O(n)$。

值得注意的是，可能存在找不到这条延伸出去的路径，这时在直径上任意取不为直径两端点的点即可。

```cpp
#include<cstdio>
#include<queue>
std::queue<std::pair<int,int> > Q;
int cnt=0,pos;
int vis[200005],sum[200005],pre[200005];
int h[200005],to[400005],ver[400005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int max(const int &x,const int &y) {return x>y? x:y;} 
inline void add(int x,int y) {to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline void dfs(int x,int fa) {pos=sum[x]>sum[pos]? x:pos;  for(register int i=h[x];i;i=ver[i]) {int y=to[i]; if(y==pre[x]) continue; pre[y]=x; sum[y]=sum[x]+1; dfs(y,x);}}
int main() {
	int n=read(),mx=0,st,ed,p=0;
	for(register int i=1;i<n;++i) {int x=read(),y=read();add(x,y);add(y,x);}
	sum[1]=0; dfs(1,-1); st=pos; pre[st]=-1; sum[st]=0; dfs(st,-1); ed=pos; //printf("Never\n");
	int cur=ed; p=pre[ed]; while(cur!=-1) {Q.push(std::make_pair(cur,0)); vis[cur]=1; cur=pre[cur];} //printf("\n");
	while(Q.size()) {
		int x=Q.front().first,step=Q.front().second; Q.pop(); if(mx<step) mx=step,p=x;
		for(register int i=h[x],y;i;i=ver[i]) if(!vis[y=to[i]]) Q.push(std::make_pair(y,step+1)),vis[y]=1; 
	}
	printf("%d\n%d %d %d",sum[ed]+mx,st,ed,p);
	return 0;
}
```

---

## 作者：wizardMarshall (赞：1)

## 题意

求三点间两两路径的边的并集的最大大小。

## 思路

提供一种较容易理解的思路。

首先需要三点间路径尽可能大，我们拟定前两个点 $u$，$v$ 为树的直径的端点。这样就最大化了前两个点的距离。反证法可得如果选择其他点不会比这两个点更优。

之后再来考虑第三个点。这时候需要让它到达 $u$，$v$ 间路径的长度最长。别的题解使用的都是 $O(n)$ 的 bfs。这里我们可以挨个枚举每个点，然后判断它们的距离。

![graph](https://cdn.luogu.com.cn/upload/image_hosting/gw9rx3ac.png)

从图中可以看到，$w$ 点到 $u$，$v$ 间路径的长度即为它的深度减去它与 $v$ 的最近公共祖先的深度（两点距离）。

于是只要求一下直径然后预处理最近公共祖先就完事了。

## 代码

```c++


#include <bits/stdc++.h>
using namespace std;


vector <int> edge[200005];
int deep[200005];
int dp[200005][20];
int mx, id;
void dfs(int x, int fa) {
	deep[x] = deep[fa] + 1;
	dp[x][0] = fa;
	if (deep[x] > mx) {
		mx = deep[x];
		id = x;
	}
	for (auto i : edge[x]) {
		if (i != fa) {
			dfs(i, x);
		}
	}
	return;
}
int LCA(int a, int b) {//dp求lca
	if (deep[a] < deep[b])swap(a, b);
	int temp = deep[a] - deep[b];
	for (int j = 18; j >= 0; j--) {
		if (temp & (1 << j)) {
			a = dp[a][j];
			temp -= (1 << j);
		}
	}
	if (a == b)return a;
	for (int j = 18; j >= 0; j--) {
		if (dp[a][j] != dp[b][j]) {
			a = dp[a][j];
			b = dp[b][j];
		}
	}return dp[a][0];
}
signed main() {
	
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	deep[0] = -1;
	mx = 0, id = 0;
	dfs(1, 0);
	int u = id;
	mx = 0, id = 0;
	dfs(u, 0);//两遍dfs求出直径
	int v = id;
	for (int j = 1; j <= 18; j++) {
		for (int i = 1; i <= n; i++) {
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
		}
	}
	int ans = -1, id = -1;//初值要赋负数
	for (int i = 1; i <= n; i++) {
		if (i != u && i != v) {
			int e = deep[v] + deep[i] - deep[LCA(i, v)];//u->v长度+i->lca长度。i即为上文中的w
			if (e > ans) {
				ans = e;
				id = i;
			}
		}
	}
	cout << ans << endl;
	cout << u << " " << v << " " << id;
    return 0;
}



```

---

## 作者：glorious_dream (赞：1)

[传送门（洛谷）](https://www.luogu.com.cn/problem/CF1294F)

看到大佬们都是用的 $O(n)$ 的做法，本蒟蒻不会，就按合情合理的思路写了一个 $O(n\log n)$ 的做法。

首先可以确定，其中的两个点肯定是直径的两个端点。感性理解一下，如果不是的话，那么把其中的点换成直径的一个端点，答案一定不会更差，因为直径已经是树上的最长路径了。然后问题就变成了在树上找到一个点，使它到直径的两个端点的路径和直径的并所经过的边数最多。我们考虑一个简单的不能算容斥的容斥。

![在这里插入图片描述](https://img-blog.csdnimg.cn/6fd4ceeca3044eb796ef84ecca964a85.png)
拿这棵树来说，假如直径的两个端点是 $1$ 和 $6$，我们要找 $5$ 这个点，那么分别记录下来直径的两个端点到其余点的距离，然后我们将其中的一个端点设为根，把其余点的深度和求 $lca$ 用的数组预处理出来。那么我们可以求出 $5$ 和深度较深的那个端点的 $lca$，然后就是一个小的容斥，假设两个端点到 $5$ 的距离分别为 $dis1$ 和 $dis2$，那么答案就是 $dis1+dis2+dep[5]-dep[lca]$。所以这道题的过程就变成了求出树的直径，然后对于两个端点分别求出到其余点的距离，然后根据上面的那个式子求出每一个点的答案，最后的答案就是最大值。

```cpp
#include <bits/stdc++.h>
#define re register
#define ll long long
#define rep(a,b,c)  for(re int a(b) ; a<=c ; ++a)
#define drep(a,b,c) for(re int a(b) ; a>=c ; --a)
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48) ; ch=getchar();}
    return x*f;
}
const int M = 2e5+10;
int head[M],dep[M],f[M][25],dis1[M],dis2[M];
int n,cnt,rt1,rt2,po,maxlen,ans;
struct edge{
	int to,nxt;
}e[M<<1];
inline void add(int u,int v){
	e[++cnt].to = v;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
void dfs(int u,int fa){
	dep[u] = dep[fa] + 1;
	f[u][0] = fa;
	rep(i,1,20) f[u][i] = f[f[u][i-1]][i-1];
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(v == fa) continue;
		dfs(v,u);
	}
}
inline int getlca(int x,int y){
	if(dep[x] < dep[y]) swap(x,y);
	drep(i,20,0) if(dep[f[x][i]] >= dep[y]) x = f[x][i];
	if(x == y) return x;
	drep(i,20,0) if(f[x][i] != f[y][i]) x = f[x][i],y = f[y][i];
	return f[x][0];
}
void dfs1(int u,int fa){
	if(dis1[u] > maxlen){
		maxlen = dis1[u];
		rt1 = u;
	}
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(v == fa) continue;
		dis1[v] = dis1[u] + 1;
		dfs1(v,u);
	}
}
void dfs2(int u,int fa){
	if(dis1[u] > maxlen){
		maxlen = dis1[u];
		rt2 = u;
	}
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(v == fa) continue;
		dis1[v] = dis1[u] + 1;
		dfs2(v,u);
	}
}
void dfs3(int u,int fa){
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(v == fa) continue;
		dis2[v] = dis2[u] + 1;
		dfs3(v,u);
	}
}
signed main(){
	n = read();
	rep(i,1,n-1){
		int u = read(),v = read();
		add(u,v),add(v,u);
	}
	dfs1(1,0);
	memset(dis1,0,sizeof(dis1));
	maxlen = 0;
	dfs2(rt1,0);
	dfs3(rt2,0);
	dfs(rt1,0);
	rep(i,1,n){
		if(i == rt1 || i == rt2) continue;
		int s1 = getlca(i,rt1),s2 = getlca(i,rt2);
		int lca = (dep[s1] > dep[s2] ? s1 : s2);
		if(dis1[i]+dis2[i]+dep[lca]-dep[i] > ans){
			ans = dis1[i]+dis2[i]-abs(dep[i]-dep[lca]);
			po = i;
		}
	}
	printf("%d\n",ans);
	printf("%d %d %d\n",rt1,rt2,po);
	return 0;
}
```



---

## 作者：123456zmy (赞：1)

~~这题好像不求直径也可以做...~~
___
如果题目求的是两个点之间的最长路径，那就可以直接求直径(~~废话~~)。三个点只需要改一点就可以了。

题意可以转化成求三条有一共同端点链的长度的和最大值和此时的另外三个端点，于是可以照搬 $DP$ 求直径的方法~~我代码就是从[SP1437](https://www.luogu.com.cn/problem/SP1437)复制来改的~~，记录最长链、次长链和次次长链的长度并维护和的最大值~~然而连样例都过不了...~~。

会 $WA$ 是因为这三条链中可能有一条是从父节点连过来的，只要再加一遍 $DFS$ 就能过了，最后注意对一条链的情况的特判。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,answ[3],a[400001],a1[400001],a2[200001],u,v,ans,ans1[200001],ans2[200001],ans3[200001],ansn1[200001],ansn2[200001],ansn3[200001];
int ansa1[200001];
bool a4[200001],vis[200001];		//极度邪教的迷之变量名
void abc(int i)				//第一遍DFS
{
	a4[i]=1;
	int a3=a2[i];
	if(a1[a3]==0)ansn1[i]=i;
	while(a3)			//邪教DFS
	{
		if(a4[a[a3]])
		{
			a3=a1[a3];
			continue;
		}
		abc(a[a3]);
		if(ans1[a[a3]]>=ans1[i])//其实是可以用优先队列的
		{
			ans3[i]=ans2[i];
			ans2[i]=ans1[i];
			ans1[i]=ans1[a[a3]]+1;
			ansn3[i]=ansn2[i];
			ansn2[i]=ansn1[i];
			ansn1[i]=ansn1[a[a3]];
//			ansa3[i]=ansa2[i];
//			ansa2[i]=ansa1[i];
			ansa1[i]=a[a3];
		}
		else if(ans1[a[a3]]>=ans2[i])
		{
			ans3[i]=ans2[i];
			ans2[i]=ans1[a[a3]]+1;
			ansn3[i]=ansn2[i];
			ansn2[i]=ansn1[a[a3]];
//			ansa3[i]=ansa2[i];
//			ansa2[i]=a[a3];
		}
		else if(ans1[a[a3]]>=ans3[i])
		{
			ans3[i]=ans1[a[a3]]+1;
			ansn3[i]=ansn1[a[a3]];
//			ansa3[i]=a[a3];
		}
		a3=a1[a3];
	}
}
void dfs(int i,int fa)			//第二遍DFS
{
	vis[i]=1;
	if(ansa1[fa]!=i)			//放在DFS前面，不然会WA
	{
		if(ans1[fa]>=ans1[i])
		{
			ans3[i]=ans2[i];
			ans2[i]=ans1[i];
			ans1[i]=ans1[fa]+1;
			ansn3[i]=ansn2[i];
			ansn2[i]=ansn1[i];
			ansn1[i]=ansn1[fa];
//			ansa3[i]=ansa2[i];
//			ansa2[i]=ansa1[i];
			ansa1[i]=fa;
		}
		else if(ans1[fa]>=ans2[i])
		{
			ans3[i]=ans2[i];
			ans2[i]=ans1[fa]+1;
			ansn3[i]=ansn2[i];
			ansn2[i]=ansn1[fa];
//			ansa3[i]=ansa2[i];
//			ansa2[i]=a[a3];
		}
		else if(ans1[fa]>=ans3[i])
		{
			ans3[i]=ans1[fa]+1;
			ansn3[i]=ansn1[fa];
//			ansa3[i]=a[a3];
		}
	}
	else
	{
		if(ans2[fa]>=ans1[i])
		{
			ans3[i]=ans2[i];
			ans2[i]=ans1[i];
			ans1[i]=ans2[fa]+1;
			ansn3[i]=ansn2[i];
			ansn2[i]=ansn1[i];
			ansn1[i]=ansn2[fa];
//			ansa3[i]=ansa2[i];
//			ansa2[i]=ansa1[i];
			ansa1[i]=fa;
		}
		else if(ans2[fa]>=ans2[i])
		{
			ans3[i]=ans2[i];
			ans2[i]=ans2[fa]+1;
			ansn3[i]=ansn2[i];
			ansn2[i]=ansn2[fa];
//			ansa3[i]=ansa2[i];
//			ansa2[i]=a[a3];
		}
		else if(ans2[fa]>=ans3[i])
		{
			ans3[i]=ans2[fa]+1;
			ansn3[i]=ansn2[fa];
//			ansa3[i]=a[a3];
		}
	}
	if(ans1[i]+ans2[i]+ans3[i]>ans)
	{
		ans=ans1[i]+ans2[i]+ans3[i];
		answ[0]=ansn1[i];
		answ[1]=ansn2[i];
		answ[2]=ansn3[i];
	}
	int a3=a2[i];
	while(a3)			//邪教DFS*2
	{
		if(vis[a[a3]])
		{
			a3=a1[a3];
			continue;
		}
		dfs(a[a3],i);
		a3=a1[a3];
	}
}
int main()
{
	ans1[0]=-1;			//预处理，不加会WA on test 16
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		a[(i<<1)-1]=v;		//邪教存图
		a1[(i<<1)-1]=a2[u];
		a2[u]=(i<<1)-1;
		a[i<<1]=u;		//邪教存图*2
		a1[i<<1]=a2[v];
		a2[v]=i<<1;
	}
	abc(1);				//DFS1
//	for(int i=1;i<=n;i++)printf("%d %d %d\n",ansn1[i],ansn2[i],ansn3[i]);
	dfs(1,0);			//DFS2
//	for(int i=1;i<=n;i++)printf("%d %d %d\n",ansn1[i],ansn2[i],ansn3[i]);
	if(answ[2]==0)			//迷之特判
	{
		if(answ[0]!=1&&answ[1]!=1)answ[2]=1;
		else if(answ[0]!=2&&answ[1]!=2)answ[2]=2;
		else answ[2]=3;
	}
	sort(answ,answ+3);		//不加也行
	if(answ[0]==0)			//迷之特判*2
	{
		answ[0]=1;
		if(answ[1]==1)
		{
			if(answ[2]==2)answ[2]=3,answ[1]=2;
			else answ[1]=2;
		}
	}
	printf("%d",ans);
	printf("\n%d %d %d",answ[0],answ[1],answ[2]);
	return 0;			//爆0
}
```

---

## 作者：览遍千秋 (赞：1)

### 前言

根据 dp/trees 的 tag 刷 Codeforces ，遇到的一个题。

做法类似于乱搞？

---

### 题意简述

要求选取三个点，使得这三个点简单路径上包含的边数最多。

---

### 题解

看到题目，很容易联想到树的直径——这个问题简化为两个点的版本。

考虑能否拓展到三个点上，在树上再寻找一个到直径距离最大的点，输出即可。

---

### $\mathrm{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

template <typename Tp>
void read(Tp &x) {
	x=0;char ch=1;int fh=1;
	while(ch!='-'&&(ch>'9'||ch<'0'))ch=getchar();
	if(ch=='-')fh=-1,ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	x*=fh;
}

const int maxn=200007;
const int maxm=400007;

int n;
int Head[maxn],to[maxm],Next[maxm],tot;

void addedge(int x,int y) {
	to[++tot]=y,Next[tot]=Head[x],Head[x]=tot;
}
void add(int x,int y) {
	addedge(x,y);addedge(y,x);
}

int maximum,pos,cnt;

void dfs1(int x,int f,int dp) {
	if(dp>maximum) maximum=dp,pos=x;
	for(int i=Head[x];i;i=Next[i]) {
		int y=to[i];
		if(y==f) continue;
		dfs1(y,x,dp+1);
	}
}

int tag[maxn];

void mark(int x,int f) {
	if(x==pos) {
		tag[x]=1;
		return;
	}
	for(int i=Head[x];i;i=Next[i]){
		int y=to[i];
		if(y==f) continue;
		mark(y,x);
		if(tag[y]) tag[x]=1;
	}
}

void Init(void) {
	read(n);
	for(int i=1,x,y;i<n;i++) {
		read(x);read(y);
		add(x,y);
	}
}

void search(int x,int f,int dp){
	if(tag[x]&&dp) return;
	if(dp>maximum) maximum=dp,cnt=x;
	for(int i=Head[x];i;i=Next[i]){
		int y=to[i];
		if(y==f) continue;
		search(y,x,dp+1);
	}
}



void Work(void) {
	dfs1(1,0,1);
	maximum=0; int p=pos; pos=0;
	dfs1(p,0,1);
	mark(p,0);
	maximum=0;
	int ans=0;
	for(int i=1;i<=n;i++){
		if(tag[i]==1) {
			search(i,0,0);
			++ans;
		}
	}
	--ans;
	if(ans==n-1) {
		for(int i=1;i<=n;i++){
			if(i!=p&&i!=pos) {
				cnt=i;break;
			}
		}
	}
	ans+=maximum;
	printf("%d\n%d %d %d\n",ans,p,pos,cnt);
//	int ans=
}

int main(void) {
	Init();
	Work();
	return 0;
}
```

---

### 讨论

是否可以将这个做法拓展到在 $n$ 个点中选取 $k$ 个点的情况？可以私信我讨论。

---

## 作者：__stick (赞：0)

# 题意

给出一棵树，让你找出树上的 $3$ 个点，使得这三个点的路径之并所包含的边最大。

# 思路

读懂题意后很自然的一个想法就是找出树的一条直径，选取直径的两个端点，然后再贪心的选择第三个点，这样就能最大化答案了。

考虑感性理解，由于三个点的路径之并其实就是一条链加上链上的某一个点往外延伸出去的一条链，所以想要最大化答案，使这个链最长一定会更优。

下面是证明（严不严谨我不知道），假设链的两个端点为 $u,v$ ，记链的长度为 $\operatorname{dis}(u,v)$，我们假设从链上一点 $x$ 向外延伸出一条链，另一个端点是 $w$，则答案就是$\operatorname{dis}(u,v)+\operatorname{dis}(x,w)$。

考虑反证法，我们假设 $u$ 到 $v$ 的链是树的一条直径，且 $\operatorname{dis}(x,w)$ 为在满足 $x$ 在 $u$ 到 $v$ 的链上的最大值，如果这个答案不是最大的，则一定会出现另外一条链，使得$\operatorname{dis}(x',w')>\operatorname{dis}(x,w)$（$x',w'$ 含义同上）。 
因为我们已经找出直径了，其他链一定不会比直径长，要想答案更大，这个延伸出去的链一定要更长。

同时，由于答案更优，所以有：

$$\operatorname{dis}(x',w')+\operatorname{dis}(x',u')+\operatorname{dis}(x',v')>\operatorname{dis}(x,w)+\operatorname{dis}(x,u)+\operatorname{dis}(x,v)$$

这时我们可以不妨设 $\operatorname{dis}(x,w)\le\operatorname{dis}(x,u)\le \operatorname{dis}(x,v)$(不满足的话交换一下即可)。这时浏览上面三个条件，
我们会发现 ：$\operatorname{dis}(x',w')+\operatorname{dis}(x',u')> \operatorname{dis}(u,v)$，这与题设矛盾，所以得出一定是取直径最优。

# 代码

wa 39 的话记得判一下树是一个链的情况。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<functional>
#include<map>
#include<queue>
#include<bitset>
#include<cmath>
#include<unordered_map>
#include<array>
#include<iomanip>
#include<numeric>
using namespace std;
template<typename T>
inline bool cmax(T& a,const T& b){return a<b?a=b,1:0;}
template<typename T>
inline bool cmin(T& a,const T& b){return b<a?a=b,1:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
const int mod=998244353;
const ll INF=0x3f3f3f3f3f3f3f3f;
int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	vii e(n+1);
	int u,v;
	for(int i=1;i<n;i++)cin>>u>>v,e[u].emplace_back(v),e[v].emplace_back(u);
	function<void(int,int)>dfs,dfs2;
	vi d(n+1),pa(n+1);
	int k1,k2=0,id=0;
	dfs=[&](int u,int  fa)
	{
		if(d[id]<d[u])id=u;
		pa[u]=fa;
		for(const int& v:e[u])
		{
			if(v==fa)continue;
			d[v]=d[u]+1;
			dfs(v,u);
		}
	};
	vector<bool>book(n+1);
	dfs(1,0),k1=id,d[k1]=0,dfs(k1,0),k2=id;
	int len=d[k2];
	for(int u=k2;u;u=pa[u])
	{
		book[u]=1;
	}
	fill(d.begin(),d.end(),0);
	dfs2=[&](int u,int  fa)
	{
		for(const int& v:e[u])
		{
			if(v==fa||book[v])continue;
			d[v]=d[u]+1;
			dfs2(v,u);
		}
	};
	for(int u=k2;u;u=pa[u])
	{
		dfs2(u,0);
	}
	int w=max_element(d.begin(),d.end())-d.begin();
	//cout<<len<<' '<<w<<'\n';
	int ans=len+d[w];
	if(w==0)w=pa[k2];
	cout<<ans<<'\n';
	cout<<k1<<' '<<k2<<' '<<w;
	return 0;
}

```


---

## 作者：activeO (赞：0)

## 题意

就是让你求三个点，他们的距离并最大。

## 思路

如果将一个点规定为根的话，其中一个要选的点一定是直径。

因为是求并，长的链贡献一定大，就肯定会选直径。

这就是两个点了，还有一个点就从这条链找一个最远的点就可以了。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=2e5+10;
struct edge{
	int to,nxt;
}e[maxn<<1];
int head[maxn];
bool vis[maxn];
int dep[maxn],fa[maxn];
int k,mx,s,t,cnt,ans=0;

inline void init(){//个人习惯问题
	memset(head,-1,sizeof(head));
	cnt=0;
}
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

void dfs(int u,int f){
	if(vis[u]) dep[u]=1;
	if(dep[u]>dep[k]&&u!=s&&u!=t){
		k=u;
		mx=dep[u];
	}
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if(v==f) continue;
		fa[v]=u;
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
}

void solve(){
	for(int i=1;i<=n;i++) fa[i]=0;
	dfs(1,0);
	s=k;
	vis[s]=1;
	for(int i=1;i<=n;i++) fa[i]=0;
	k=0;
	dfs(s,0);
	t=k;
	int now=t;
   ans=mx-1;
	while(now){
		vis[now]=1;
		now=fa[now];
	}
	
	k=0;
	dfs(s,0);
	ans+=mx-1;
}

int main(){
	
	init();
	
	int n;
	
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		add(u,v);
		add(v,u);
	}
	
   solve();
	
	printf("%d\n%d %d %d",ans,s,t,k);
	
	return 0;
}


```


---

## 作者：Plozia (赞：0)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/118368428)

这是一道思维题。

本文约定：$u \to v$ 表示从 $u$ 到 $v$ 的路径。

---------

首先简化一下题意：给出一棵树，求出三个点使得三个点之间两两路径并的长度最大。

显然我们不能枚举这三个点，复杂度 $O(n^3)$ 过大，不能接受。

做这道题需要一个重要结论：树的直径的两个端点一定是要被选中的。

简单证明：

假设树的直径的两个端点是 $u_1,v_1$，选的是 $u,v,w$ 三个点，$u \to v$ 并不是树的直径。

设 $u \to v$ 和 $u \to w$ 交于 $P$ 点，如果 $u_1 \to v_1$ 也经过 $P$ 点，那么显然将 $u,v,w$ 中的其中两个点换成直径一定更优。

如果 $u_1 \to v_1$ 不经过 $P$ 点，那么就会出现如下图几种情况：

1. 树的直径在 $P$ 的第四棵子树上：

情况 1：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210630200859924.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JXemh1emVoYW8=,size_16,color_FFFFFF,t_70)

但显然这个时候 $u_1 \to v_1$ 根本就不是直径。

情况 2：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210630201324937.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JXemh1emVoYW8=,size_16,color_FFFFFF,t_70)

对于这一种情况，大可以把 $u,v,w$ 中的其中一个点换成 $u_1,v_1$，因为这么做一定能够增加路径长度。

既然换了一个点能够增加路径长度，假设现在的点是 $u_1,v,w$，那么如果把 $v$ 换成 $v_1$ 也能够增加路径长度（否则就不是树的直径了）

综上，原命题成立。

---------

在证明了这个结论之后，那么 $u \to v$ 就一定是直径了。

怎么确定 $w$ 呢？看图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021063020165413.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JXemh1emVoYW8=,size_16,color_FFFFFF,t_70)

对于 $u \to v$ 上的每一个点 $P$ 而言（除去 $u,v$），我们将其旁边的几棵子树拎出来，直接在这几棵子树上面找出离 $P$ 最远的点就可以了。

---------

代码里面需要注意的细节：

- 小心链的数据，细节处理不当一条链就会把你卡成 $w=v$ 或者 $w=u$。

Code：[GitHub CodeBase-of-Plozia CF1294F Three Paths on a Tree.cpp](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/Codeforces%20%E5%88%B7%E9%A2%98%E5%90%88%E9%9B%86/CF1294F%20Three%20Paths%20on%20a%20Tree.cpp)

```cpp
/*
========= Plozia =========
    Author:Plozia
    Problem:CF1294F Three Paths on a Tree
    Date:2021/6/30
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e5 + 5;
int n, dep[MAXN], u, v, w, Head[MAXN], cnt_Edge = 1, f[MAXN], Root = 0, ans, fa[MAXN];
int Path[MAXN], cnt;
bool book[MAXN];
struct node { int to, Next; } Edge[MAXN * 2 + 1];

int Read()
{
    int sum = 0, fh = 1; char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
    return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

void dfs(int now, int father, int Tag)
{
    if (f[now] > ans) { Root = now; ans = f[now]; }
    if (Tag) fa[now] = father;
    for (int i = Head[now]; i; i = Edge[i].Next)
    {
        int u = Edge[i].to;
        if (u == father) continue ;
        f[u] = f[now] + 1;
        dfs(u, now, Tag);
    }
}

void dfs2(int now, int father, int depth)
{
    dep[now] = depth;
    for (int i = Head[now]; i; i = Edge[i].Next)
    {
        int u = Edge[i].to;
        if (u == father || book[u]) continue ;
        dfs2(u, now, depth + 1);
    }
}

int main()
{
    n = Read();
    for (int i = 1; i < n; ++i)
    {
        int x = Read(), y = Read();
        add_Edge(x, y); add_Edge(y, x);
    }
    f[Root = 1] = 0; dfs(1, 0, 0); ans = 0; u = Root;
    f[Root] = 0; dfs(Root, 0, 1); v = Root;
    for (int i = v; i != u; i = fa[i]) book[i] = 1, dep[i] = -1;
    book[u] = 1, dep[u] = -1;
    for (int i = fa[v]; i != u; i = fa[i]) { dep[i] = 0; dfs2(i, 0, 0); }
    int t = -1;
    for (int i = 1; i <= n; ++i)
        if (dep[i] > t) { t = dep[i]; w = i; }
    printf("%d\n%d %d %d\n", ans + t, u, v, w); return 0;
}
```

---

## 作者：傅思维666 (赞：0)

## 题解：

贪心+树。

首先简单想一想能发现：答案应该是树的直径加上所有不在直径上的节点中，距离直径最长的距离。

那么只需要模拟这个过程就可以：

先两次DFS求出树的直径（记录路径长和两个端点），然后把直径上所有节点打上标记，然后枚举所有非直径上的节点，更新最大距离，就可以过了。

复杂度是$O(n)$级别。

代码：

```cpp
#include<cstdio>
using namespace std;
const int maxn=2e5+5;
int n;
int tot,head[maxn],nxt[maxn<<1],to[maxn<<1];
int maxx,pos[4],ans;
int deep[maxn],fa[maxn];
bool v[maxn];
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void dfs(int x,int f,int p)
{
	if(p==2)
		fa[x]=f;
	deep[x]=deep[f]+1;
	if(deep[x]>maxx)
	{
		maxx=deep[x];
		pos[p]=x;
	}
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==f)
			continue;
		dfs(y,x,p);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	deep[0]=-1;
	dfs(1,0,1);
	maxx=0;
	dfs(pos[1],0,2);
	int x=pos[2];
	while(x)
	{
		v[x]=1;
		x=fa[x];
	}
	ans+=maxx;
	maxx=0;
	int tmp=0;
	for(int i=1;i<=n;i++)
	{
		if(v[i])
			continue;
		else
		{
			x=i;
			tmp=0;
			while(!v[x])
			{
				x=fa[x];
				tmp++;
			}
			if(maxx<tmp)
			{
				maxx=tmp;
				pos[3]=i;
			}
		}
	}
	if(!maxx)
		for(int i=1;i<=n;i++)
			if(v[i]&&i!=pos[1]&&i!=pos[2])
			{
				pos[3]=i;
				break;
			}
	ans+=maxx;
	printf("%d\n%d %d %d\n",ans,pos[1],pos[2],pos[3]);
	return 0;
}
```




---

