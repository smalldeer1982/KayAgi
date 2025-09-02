# [USACO22DEC] Barn Tree S

## 题目描述

Farmer John 的农场有 $N$ 个牛棚 $(2 \le N \le 2 \times 10^5)$，编号为 $1 \cdots N$。有 $N−1$ 条道路，每条道路连接两个牛棚，并且从任一牛棚均可通过一些道路到达任一其他牛棚。目前，第 $j$ 个牛棚中有 $h_j$ 个干草捆 $(1 \le h_j \le 10^9)$。 

为使他的奶牛们满意，Farmer John 想移动这些干草，使得每个牛棚都有相同数量的干草捆。他可以选择任何一对由一条道路连接的牛棚，并命令他的农场工人将不超过第一个牛棚中干草捆数量的任意正整数个干草捆从第一个牛棚移动到第二个牛棚。 

请求出一个 Farmer John 可以发出的命令序列，以尽可能少的命令数完成这一任务。输入保证存在符合要求的命令序列。 

## 说明/提示

### 样例 1 解释

在这个例子中，共有十二个干草捆和四个牛棚，这意味着每个牛棚最后必须有三个干草捆。输出样例中的命令顺序可以用以下的自然语言表述： 

1. 从牛棚 $3$ 到牛棚 $2$，移动 $1$ 个干草捆。
2. 从牛棚 $4$ 到牛棚 $2$，移动 $2$ 个干草捆。
3. 从牛棚 $2$ 到牛棚 $1$，移动 $1$ 个干草捆。

### 测试点性质

- 测试点 $2-8$ 满足 $N \le 5000$。
- 测试点 $7-10$ 满足 $v_i=u_i+1$。
- 测试点 $11-16$ 没有额外限制。

## 样例 #1

### 输入

```
4
2 1 4 5
1 2
2 3
2 4```

### 输出

```
3
3 2 1
4 2 2
2 1 1```

# 题解

## 作者：Demeanor_Roy (赞：13)

- [原题链接](https://www.luogu.com.cn/problem/P8900)

- 赛时想法，有问题欢迎提出。

------------

考虑将这棵树以 $1$ 为根定形。为了方便表述，令 $cow(x)$,$now(x)$,$sum(x)$ 分别为以 $x$ 为根子树节点数，$x$ 节点干草捆数，以 $x$ 为根子树干草捆总数。

由于一定有解，所以最后每个节点干草捆平分，令其为 $aim$，即 $aim=\frac{sum(1)}{n}$。

自上而下考虑。首先一号节点没有父亲，此处的干草捆不够肯定就由儿子拿，多了肯定就往儿子拿。考虑它的一个儿子 $x$，有以下三种情况：

1. 若 $sum(x)=cow(x)\times aim$ ：这种情况下 $x$ 这棵子树自给自足，递归处理即可。

2. 若 $sum(x)>cow(x)\times aim$ ：这时 $x$ 这棵子树的干草捆数多了，于是在满足自己的需求下，多余部分全部堆到 $x$ 给父亲即可。

3. 若 $sum(x)<cow(x)\times aim$ ：此时父节点补给 $x$ 节点足够的干草捆，使其能够自足。

考虑到时时刻刻干草捆数必须非负，所以我们得到一个这样的策略：先递归处理所有情况一，二的 $x$，将多余的干草捆堆到 $x$ 结点处给父亲，然后从父亲向所有情况三的 $x$ 补干草捆，再递归处理。

于是自上而下，对每个节点的儿子分情况讨论，时时刻刻维护上面三个数组可。

此时还有一个问题是该方案的最优性，这可以通过对每一条边考虑来证明，读者自证不难。

[代码](https://www.luogu.com.cn/paste/55xps0ez)

---

## 作者：yemuzhe (赞：9)

### 解题思路

这道题看起来是 dfs，于是我用了 dfs（分治）来解决。由于题目给的是一颗无根树，那么我们不妨就设根节点为 $1$ 号节点。

#### Part 1：方案

![](https://s1.ax1x.com/2022/12/18/zqS0BT.png)

我们可以从叶子结点入手，如果多于平均值就运到父节点多的部分，如果少于平均值就从父节点运缺的部分给它。

如上图，我们考虑五角星节点，它应该运向它的父节点 $3$ 个干草捆。

于是我们可以用基于 dfs 的分治算法，先递归处理某节点的所有子树，把信息汇总到该节点上，再根据情况向父节点调整。

#### Part 2：顺序

运输的过程中，难免会遇到这样一个问题：**在某时刻某个节点的干草捆数量为一个负数**！于是我们想要优化运输顺序。

由于“给”的一般比“借”的来得更优，于是我们考虑先“给”后“借”。

具体地，我们考虑任意一个节点，先考虑把有多余的子树的多余的部分“拿”过来，再将又缺少的子节点“补”过去。最后此节点如果有多余，就把多余的部分上传到父节点上。总之，就是先“上传”后“下传”。

#### Part 3：具体流程：

1. 若一个节点代表的子树有多余，那么首先处理多余的子节点代表的子树，然后接收上传，再下传给缺少的子节点代表的子树，再处理它们，最后上传给父节点。

2. 若一个节点代表的子树有缺少，那么首先接收来自父节点的下传，然后处理多余的子节点代表的子树，再接收上传，再下传给缺少的子节点代表的子树，最后处理它们。

#### Part 4：证明

先证最优性。当某条边的两边子树有多有少时，这条边一定会被拿来运输；否则这条边一定不会被拿来运输（两边子树自己调整）。而这种思路刚好满足这一点。

再证合法性。按照上面的流程，某个节点的干草捆一定是先加后减的（可能先接收父节点的下传，再接收多余子树的上传，然后下传给不足子树，最后上传给父节点），而刚开始为正数且最后一定为平均值（正数），说明中间过程中一定大于等于平均值即正数，不可能出现负数。

#### AC Code

```c++
#include <cstdio>
#define N 200005
using namespace std;

int n, x, y, tot, ans, head[N], nxt[N << 1], ver[N << 1];
long long ave, a[N], f[N];

void insert (int x, int y) // 构建邻接表
{
	ver[++ tot] = y, nxt[tot] = head[x], head[x] = tot;
	return ;
}

void dfs (int x, int fa) // 处理多余/缺少，顺便统计答案
{
	for (int i = head[x], y; i; i = nxt[i]) // 遍历当前节点所有边
	{
		if ((y = ver[i]) == fa) // 指向父节点的边，跳过
		{
			continue;
		}
		dfs (y, x);
	}
	f[x] = a[x] - ave, a[fa] += f[x], ans += (bool) f[x];
    // f[x]：多余出来多少干草捆，缺少则是负数
    // 把多余或缺少的累计到父节点上，统计答案
	return ;
}

void sol (int x, int fa) // 解决顺序问题，输出具体命令
{
	// 第一遍 for 先扫那些多余干草捆（或刚好）的子节点
	for (int i = head[x], y; i; i = nxt[i])
	{
		if ((y = ver[i]) == fa || f[y] < 0)
		{
			continue;
		}
		sol (y, x);
	}
    // 第二遍 for 再扫那些缺少干草捆的子节点
	for (int i = head[x], y; i; i = nxt[i])
	{
		if ((y = ver[i]) == fa || f[y] >= 0)
		{
			continue;
		}
		printf ("%d %d %lld\n", x, y, -f[y]), sol (y, x);
	}
	if (f[x] > 0) // 上传给父节点干草捆
	{
		printf ("%d %d %lld\n", x, fa, f[x]);
	}
	return ;
}

int main ()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i ++)
	{
		scanf ("%d", &a[i]), ave += a[i];
	}
	ave /= n; // 先求平均值
	for (int i = 1; i < n; i ++)
	{
		scanf ("%d%d", &x, &y), insert (x, y), insert (y, x);
	}
	dfs (1, 0), printf ("%d\n", ans), sol (1, 0);
	return 0;
}
```

---

## 作者：Lantrol (赞：8)

比较有意思的题，考场一刻钟切了。

## 思路

设 $1$ 号结点为根，将每个点的相对点权设为该点实际点权与平均点权的差。

我们需要的策略是最优的，也就是用最少的步数平均分配所有干草块。注意到题目要求，每步只能在一对有边直接相连的点间搬运干草块。我们希望尽可能地在更下层的子树中尽可能做到平均分配干草块，这样搬运干草块所需的步数是更少的。继续思考，在当前子树中，以根节点为中心从下往上接收下层多余的干草块，从上往下发送下层所需的干草块，是效率最高的方法。考虑如下策略：

- 对于相对点权和为正的所有子树，向其父节点贡献出该子树的点权和。

- 对于相对点权和为负的所有子树，从其父节点处下传该子树所需的点权。

- 由于需要保证任意时刻所有点的实际点权是正的，所以先进行完全部的向上贡献操作后，再进行全部的下传操作。

这时候也许感性理解一下就会发现这种策略是最优的。

- 最优性：整个过程分为上传和下传两部分。上传时，相对点权和为正的子树向根节点贡献该子树内多余的点权和，这保证了经过上传操作后，这些子树内的相对点权和为 $0$。此时，这棵子树内所有点权和为负的子树所需的点权和之总和都集中在根结点处，然后按需下传即可。这意味着点权需求问题在最小的子树内即可得到解决。而最小的子树意味着最少的搬运次数，也就代表着最优策略。

## 代码

代码实现难度不大，建树后两遍深搜，第一遍从下往上做上传，第二遍从上往下做下传。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ioc ios::sync_with_stdio(0)
using namespace std;
const int MAXN=2e5+5;
int from[MAXN<<1],to[MAXN<<1],nxt[MAXN<<1],head[MAXN],val[MAXN],tot=0;
void add(int u,int v){
	from[++tot]=u;
	to[tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
int ansu[MAXN<<2],ansv[MAXN<<2],answ[MAXN<<2],ansc;
void dfs1(int u,int fa){
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa) continue;
		dfs1(v,u);
		if(val[v]>0){
			ansu[++ansc]=v;ansv[ansc]=u;answ[ansc]=val[v];
		}
		val[u]+=val[v];
	}
}
void dfs2(int u,int fa){
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa) continue;
		if(val[v]<0){
			ansu[++ansc]=u;ansv[ansc]=v;answ[ansc]=-val[v];
		}
		dfs2(v,u);
	}
}
int n,cnt; 
signed main(){
	ioc;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>val[i];
		cnt+=val[i];
	}
	cnt/=n;
	for(int i=1;i<=n;i++){
		val[i]-=cnt;
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	dfs1(1,0);
	dfs2(1,0);
	cout<<ansc<<"\n";
	for(int i=1;i<=ansc;i++){
		cout<<ansu[i]<<" "<<ansv[i]<<" "<<answ[i]<<"\n";
	}
}
```

---

## 作者：Acoipp (赞：5)

## 解题思路
先谈谈我之前遇到的一道题：
> 给定一个长度为 $n$ 的数组 $a$，你需要从一个 $a_i$ 中减去 $k$，$k$ 可以是负数，使得它旁边的数增加 $k$，这称作为“一次转移”。如果使得最后每个 $a_i$ 相同，那么至少需要转移多少次。

那么再回过头来看这道题，主要有三点不同：
> 1、不允许出现负数。  
> 2、需要输出一种方案。  
> 3、它是一个树上问题。

首先，明确一下方案的最少操作步数。  

我们考虑对这棵树进行一个 DFS，因为它是无根树，此处就采用 $1$ 号节点作为这棵树的根节点。  

假设我们 DFS 到 $i$ 号节点时，如果 $i$ 号节点的子树中的干草捆数量小于应该有的干草捆数量，那么 $i$ 号节点的父亲就一定要运送一定的干草捆到 $i$ 号节点的子树中；如果大于，那么 $i$ 号节点就会将子树中多出来的运送到它的父亲节点进行进一步分配；如果等于就代表 $i$ 号节点的子树就是满足的，即 **子树内可以进行任意交换**。对于前两种情况就让答案加 $1$ 即可。  

思路进行到此处，答案处理完了，接下来是怎么输出方案的问题，因为不允许出现负数，再观察一下我们的处理过程。  

注意到两个节点进行干草捆的运输一定是在树上相邻的两个点，而且不会出现 $a$ 需要给 $b$ 干草捆，$b$ 又需要给 $a$ 干草捆，所以如果我们将 $a$ 需要给 $b$ 运输 $k$ 个干草捆改为在另一张空图上给 $a$ 和 $b$ 连一条权值为 $k$ 的 **有向边**，这就是一个 DAG。  
接着，我们对于这个 DAG 跑一次拓扑排序即可，记住每次输出当前经过的边的起点，终点，以及边权。  

## 一些细节
- 计算每个节点应该有的干草捆是用干草捆总和除以节点总数。

- 计算子树内的干草捆数量可以用预处理记录优化。

- 计算子树内应该有的干草捆数量就是用子树内节点个数乘上每个节点应该有的干草捆数量。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
using namespace std;
struct node{ll x,y,z;};
vector<ll> op[N];
vector<pair<ll,ll> >op1[N]; 
ll n,i,x,y,a[N],son[N],sum[N],fath[N],c,ans,rd[N];
deque<ll> op2;
void dfs1(ll x){        //预处理
	sum[x] = a[x];
	son[x] = 1;
	for(ll i=0;i<op[x].size();i++){
		if(op[x][i]==fath[x]) continue;
		fath[op[x][i]] = x;
		dfs1(op[x][i]);
		son[x] += son[op[x][i]],sum[x] += sum[op[x][i]];
	}
}
void dfs2(ll x){         //拓扑排序初始化记录
	for(ll i=0;i<op[x].size();i++){
		if(op[x][i]==fath[x]) continue;
		dfs2(op[x][i]);
	}
	if(sum[x]<son[x]*c){   //第一种情况
		ans++;
		op1[fath[x]].push_back(make_pair(x,son[x]*c-sum[x]));
		rd[x]++;
	}
	else if(sum[x>son[x]*c){   //第二种情况
		ans++;
		op1[x].push_back(make_pair(fath[x],sum[x]-son[x]*c));
		rd[fath[x]]++;
	}
}
void solve(){      //拓扑排序
	for(i=1;i<=n;i++) if(rd[i]==0) op2.push_back(i);
	while(op2.size()){
		ll tmp = op2.front();
		op2.pop_front();
		for(i=0;i<op1[tmp].size();i++){
			cout<<tmp<<" "<<op1[tmp][i].first<<" "<<op1[tmp][i].second<<endl;     //输出答案
			if(--rd[op1[tmp][i].first]==0){
				op2.push_back(op1[tmp][i].first);
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i],c+=a[i];
	c /= n;
	for(i=1;i<n;i++){
		cin>>x>>y;
		op[x].push_back(y);
		op[y].push_back(x);
	}
	dfs1(1);
	dfs2(1);
	cout<<ans<<endl;
	solve();
}

```

---

## 作者：EXODUS (赞：3)


# Part 1：前言
比较简单的贪心，我感觉在银组算非常良心的了（

# Part 2：正文

每个点最后有多少干草捆是显然的，即 $\dfrac{\sum h_i}{n}$，令其为 $avg$。

注意到，这个题让我们输出方案，这以为着一定存在一种操作较少的方案（即会是 $O(n)$ 级别或 $O(n\log n)$ 级别的，下文会说明是 $O(n)$），我们不妨从这点入手考虑。

**对于一个点，一定只会有至多一次从父节点和他的操作**，这一点是好证明的，如果存在两次操作，我们不妨将其合并，例如 $a\stackrel{1}{\rightarrow} b\ a\stackrel{2}{\rightarrow} b$ 两种操作合并为 $a\stackrel{3}{\rightarrow} b\ $，$a\stackrel{1}{\rightarrow} b\ a\stackrel{2}{\leftarrow} b$ 两种操作合并为 $a\stackrel{1}{\leftarrow} b\ $。

并且，一个点 $u$ 与他父亲进行操作的干草捆数量，一定恰好等于 $\sum\limits_{v\in \text{subtree}(u)} (h_j-avg)$，这里符号代表是从父亲到儿子（负号）还是儿子到父亲（正号）。

那么现在是操作次序的问题，不难发现，一旦有一个点不用向父亲索要，意味着以该节点为根的子树可以输出方案了（这意味着该子树从根节点向下推不会出现一个父子节点 $u$，在父亲节点向其提供权值后，$\sum\limits_{v\in \text{subtree}(u)} (h_j-avg)<0$，否则一定不是最优方案或违反了条件），然后把多的权值贡献到父亲即可。

感性理解其正确性，即优先做别人给他，再做他给别人，一定能使他最后剩的最多。这也是为什么最后要直接把多的给父亲而不是当父亲向下找到时再回溯。

具体细节见代码，**注意特判 $0$ 是不用向父亲贡献的**，~~我自认为写的还是比较优美的。~~
# Part 3：代码
```cpp
#define int long long
#define mpp(a,b,c) make_pair(a,make_pair(b,c))
#define pb push_back
#define eb emplace_back
const int N=4e5+7;
int n;
vector<int>g[N];
int avg=0;
ll ned[N];
int h[N];
vector<pair<int,pair<int,ll> > >opt;


void solve(int u,int fa){
	for(auto v:g[u]){
		if(v==fa||ned[v]<=0)continue;
		opt.eb(mpp(u,v,ned[v]));
		solve(v,u); 
	}
}

void dfs(int u,int fa){
	for(auto v:g[u]){if(v==fa)continue;dfs(v,u);}
	for(auto v:g[u]){if(v==fa)continue;ned[u]+=ned[v];}
	ned[u]+=avg-h[u];
	if(ned[u]<=0){solve(u,fa);if(ned[u]!=0)opt.eb(mpp(u,fa,-ned[u]));}
}

void Main(){
	n=read();ll sum=0;
	for(int i=1;i<=n;i++)h[i]=read(),sum+=h[i];
	avg=sum/n;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		g[u].pb(v),g[v].pb(u);
	}dfs(1,0);
	printf("%lld\n",(int)(opt.size()));
	for(auto x:opt){
		printf("%lld %lld %lld\n",x._1,x._2,x._3);
	}
	return;
}
```

---

## 作者：zhenjianuo2025 (赞：3)

 ### Solve
 首先考虑**链上**的做法。
 
 记标准值为 $\dfrac{\sum a_i}{n}$。
 
 把每个点的点权 $a_i$ 减去标准值，这样只需要把每个点的点权通过转移得到 $0$ 就可以了。
 
 从左往右依次考虑每个点 $i$：
 - 若 $a_i=0$，什么也不做；
 - 若 $a_i>0$，将 $a_{i+1}$ 加上 $a_i$，$a_i$ 设为 $0$。表示由 $i$ 向 $i+1$ **转移**了 $a_i$；
 - 若 $a_i<0$，将 $a_{i+1}$ 加上 $a_i$，$a_i$ 设为 $0$。表示由 $i$ 向 $i+1$ **索取**了 $-a_i$。
 
 先把转移的操作从前往后输出，再把索取的操作从后往前输出。
 
 扩展到树上，按深度从大到小处理即可。
 
 ### Code
 ```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int> 
#define fi first
#define se second 
#define mp make_pair
int n, v[200010], fa[200010], son[200010]; 
int cnt, ans[600010][3];
vector<int> g[200010];
void dfs(int u, int f) {
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v == f) continue;
		dfs(v, u);
		son[u]++;
		fa[v] = u;
	}
}
int hui, zhu[600010][3];
signed main() {
	cin >> n;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
		sum += v[i];
	}
	sum /= n;
	for (int i = 1; i <= n; i++) v[i] -= sum;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v), g[v].push_back(u);
	}
	dfs(1, 0);
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (!son[i]) q.push(i);
	while (q.size()) {
		int u = q.front(); q.pop();
		if (!fa[u]) break;
		if (v[u] > 0) {
			++cnt;
			ans[cnt][0] = u, ans[cnt][1] = fa[u], ans[cnt][2] = v[u];
		} else if (v[u] < 0) {
			++hui;
			zhu[hui][0] = fa[u], zhu[hui][1] = u, zhu[hui][2] = -v[u];
		} 
		v[fa[u]] += v[u], v[u] = 0;
		son[fa[u]]--;
		if (!son[fa[u]]) q.push(fa[u]);
	}
	for (int i = hui; i >= 1; i--) {
		++cnt;
		for (int j = 0; j <= 2; j++) ans[cnt][j] = zhu[i][j];
	}
	cout << cnt << "\n";
	for (int i = 1; i <= cnt; i++)
		cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << "\n";
	return 0;
} 
```

---

## 作者：Untitled10032 (赞：3)

比赛的时候唯一 A 掉的题，感觉好有意思。（虽然其它两题全都寄了）

# 大致题意

给你一棵树，每个节点上有一个权值，可以从一个节点经过某条边传递一定的权值到另一个节点，但是任何时刻不允许出现负权节点。 _（例如有一从点 $u$ 连向点 $v$ 的点，可以做一次操作使 $w_u = w_u - k$，$w_v = w_v + k$，$k$ 需要为正数，且 $k \leq w_u$。）_

输出让所有节点的权值相同的最少操作数和一种操作方案。

# 思路

## 初步想法

使用递归调平点的权值。

递归到每个节点时，把它的所有子节点都调整成整棵树所有点权的平均值（如果少了就从父节点拿走，如果多了就把多的给父节点）。

然后把剩下的烂摊子都堆到正在递归的那个节点上，等回溯的时候再由它的爸爸处理。

看似不错。但如果有一个数据是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/pyobiylh.png)

（节点里面写的是点权）

而如果你恰好先递归了左边那一堆点权为 $0$ 的点，那你就寄了。因为显然在操作过程中会出现负权的点。

所以，递归的时候应该遵循一些顺序。

## 最终解法

**确定一个递归顺序，让正被递归到的那个节点的点权尽量大。**

输入的时候先计算出所有点权的平均数，作为**目标点权 $t$**。

之后给树定一个根，跑一遍 DFS，处理出数组 $v_i$，$v_i$ 表示只考虑以 $i$ 为根的子树时，把以 $i$ 为根的子树中除了 $i$ 号节点之外的所有点都调成最终的目标值 $t$，根节点的值会是多少。

再跑一遍 DFS 处理出答案（记得把每步操作记录一下）：

- 对于每一个点，遍历其子节点，如果一个子节点的 $v_i$ 值大于目标值 $t$，也就是说它最后会往外送权值，那就先递归它。

- 递归完了上述子节点之后，再调整所有子节点的权值。注意要先操作 $v_i > t$ 的点，把该拿的权值都拿了，之后再操作 $v_i < t$ 的节点。这样能保证权值非负。

- 最后再递归处理那些 $v_i$ 的值小于 $t$ 的节点。

- **注意别忘了递归 $v_i = t$ 的节点，这个没有顺序要求，可以随便放在哪。**

最后照格式输出就行了。别忘了第一行要输出操作总数。

# 源代码

```cpp
#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
ll h[200005], v[200005];    //h[x]: 点权（干草捆数）; v[x]:不考虑其它节点，将本子树除根节点的权值处理好后根节点会是多少
vector<int> g[200005];      //g: 存图
struct Opt {
    int from, to;
    ll val;
};
vector<Opt> ans;

ll target = 0;  //target: 所有点权平均值

/*
dfssum: 计算v[i]。
return:
    first: 子树权值和
    second: 子树里有几个节点
*/
pair<ll, ll> dfssum(int x, int fa) {
    ll val = 0, cnt = 0;
    for (auto i : g[x])
        if (i != fa) {
            const pair<ll, ll> t = dfssum(i, x);
            val += t.first;
            cnt += t.second;
        }
    v[x] = (val - cnt * target) + h[x];
    return {val + h[x], cnt + 1};
}

// 处理最终答案
void dfs(int x, int fa) {
    for (auto i : g[x])
        if (i != fa && v[i] >= target)
            dfs(i, x);

    
    for (auto i : g[x]) 
        if (i != fa) {
            const ll t = v[i] - target;
            if (t > 0) {
                ans.push_back({i, x, t});
            }
        }
    for (auto i : g[x]) 
        if (i != fa) {
            const ll t = v[i] - target;
            if (t < 0) {
                ans.push_back({x, i, -t});
            }
        }

    for (auto i : g[x])
        if (i != fa && v[i] < target)
            dfs(i, x);
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        target += h[i];
    }
    target /= n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfssum(1, 0);
    dfs(1, 0);
    cout << ans.size() << '\n';
    for (auto i : ans)
        cout << i.from << ' ' << i.to << ' ' << i.val << '\n';
    return 0;
}
```


---

## 作者：Sandwich_ (赞：2)

每个节点最终干草捆个数为 $k=tot/n$，其中 $tot$ 是总个数。

考虑去掉一条边，树被割成两个独立的子图。

设子图内节点个数是 $siz$，总共需要 $siz\times k$ 个干草捆。但不论其内部怎么调，其干草捆总数 $hs$ 都不变。所以可以判断出一个子图干草捆总数过剩还是不足，还是正好。

如果这两块都正好，就不需要使用被去掉的这条边；否则，这条边一定会被使用，从过剩的子图运送到不足的子图那里。

于是，可以计算出每条边是否要使用，运送方向和运送量。

另外，本题给的是一个以 1 为根的树。上文中的两个子图，其中一个就是子树。考虑树形dp进行上文的计算，维护 $siz(u),hs(u)$。

知道了每条边怎么用，相当于建了一个新图。如果运送的顺序不当，运出时可能是干草捆个数变成负数。显然，一个正确的顺序就是拓扑序。这个方法保证了每条必须使用的边都被使用了 1 次，且没有使用其他的边，所以命令数一定是最小的。

```cpp
const int MAXN = 2e5 + 5;

struct Edge {
	int v; ll w;
	Edge(int _v, ll _w): v(_v), w(_w){}
};

int n, siz[MAXN], in[MAXN];
ll k, h[MAXN], hs[MAXN];
vector<int> g[MAXN];
vector<Edge> ng[MAXN];

void dfs(int u, int par) {
	siz[u] = 1; hs[u] = h[u];
	for (int i = 0; i < g[u].size(); ++i) {
		int v = g[u][i];
		if (v == par) continue;
		dfs(v, u);
		siz[u] += siz[v]; hs[u] += hs[v];
	}
	ll d = hs[u] - siz[u] * k;
	if (d > 0) ng[u].push_back(Edge(par, d));
	else if (d < 0) ng[par].push_back(Edge(u, -d));
}

void toposort() {
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		cnt += ng[i].size();
		for (int j = 0; j < ng[i].size(); ++j) {
			++in[ng[i][j].v];
		}
	}
	printf("%d\n", cnt);
	queue<int> q;
	for (int i = 1; i <= n; ++i) {
		if (!in[i]) q.push(i);
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < ng[u].size(); ++i) {
			Edge e = ng[u][i];
			printf("%d %d %lld\n", u, e.v, e.w);
			if (!--in[e.v]) {
				q.push(e.v);
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", h + i);
		k += h[i];
	} k /= n;
	for (int i = 1; i < n; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		g[u].push_back(v); g[v].push_back(u);
	}
	
	dfs(1, 0);
	toposort();
	
	return 0;
}
```

---

## 作者：HMZHMZHMZ (赞：2)

显然的，我们有一种操作数不多于 $n-1$ 的方法。就是多余的给父亲，不够的找父亲要。

但是这样有可能出现超额支出的操作，直接输出是不行的。

我们对于每一个起始节点的操作，拿一个优先队列来维护他剩下的操作，将所有当前合法的操作都放入一个队列中。

然后在你做队列中操作的时候，只有当前操作的结束节点有可能有新的操作出去，判断一下就好。

因为每个操作最多进出队列以及优先队列一次，所以总复杂度是 $O(n\log n)$ 的。

```cpp
 #include<bits/stdc++.h>
#define ll long long
#define int long long
#define vi vector<int>
#define pii pair<int,int>
#define pb(x) push_back(x)
#define lowbit(x) x&-x
using namespace std;
const int N=2e5+10;
struct node{
	int to,nxt;
}a[N<<1];
struct que{
	int from,to,val;
};
ll ans;
queue<que> q;
priority_queue<pii> got[N];
int n,m,T,head[N],cnt,arv,c[N],w[N],tot;
inline int read(){
	int s=0,f=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return f?-s:s;
}
inline void add(int from,int to){
	a[++cnt]=(node){to,head[from]};
	head[from]=cnt;
}
inline bool operator < (que a,que b){
	return w[a.from]-a.val<w[b.from]-b.val;
}
inline void dfs(int x,int fa){
	for(register int i=head[x];i;i=a[i].nxt){
		int to=a[i].to;
		if(to==fa) continue;
		dfs(to,x);
	}
	c[fa]+=(w[x]+c[x]-arv);
	if(w[x]+c[x]>arv) got[x].push((pii){arv-w[x]-c[x],fa}),++tot;
	if(w[x]+c[x]<arv) got[fa].push((pii){w[x]+c[x]-arv,x}),++tot;
}
inline void insert(int i){
	while(!got[i].empty()&&-got[i].top().first<=w[i]){
		q.push((que){i,got[i].top().second,-got[i].top().first});
		w[i]+=got[i].top().first;
		got[i].pop();
	}
}
signed main(){
	n=read();
	for(register int i=1;i<=n;++i) w[i]=read(),arv+=w[i];
	arv/=n;
	for(register int i=1;i<n;++i){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,0);
	printf("%lld\n",tot);
	for(register int i=1;i<=n;++i) insert(i);
	while(!q.empty()){
		que f=q.front();q.pop();
		printf("%lld %lld %lld\n",f.from,f.to,f.val);
		w[f.to]+=f.val;
		insert(f.to);
	}
	for(register int i=1;i<=n;++i) if(w[i]!=arv) while(1);
	return 0;
}

```

---

## 作者：Trafford1894 (赞：2)

由于此树为无根树，所以先钦定 $1$ 号结点为根节点。

题目中保证一定存在解，因此可以计算出每个结点最终要打到的值，记为 $ave$。

记以 $x$ 号结点的父亲为 $fa_x$，以其为根的子树的结点个数为 $sum_x$，子树的干草个数总和为 $sumbarn_x$。

因为在以 $x$ 号结点为根的子树内移动干草，并不改变 $sumbarn_x$，这些操作是无用的。

因此，我们记 $\delta (x)$ 为 $sumbarn_x- ave \times sum_x$，即以 $x$ 号结点为根的子树中，和我们想要达到的情况差多少捆干草。

如果 $\delta(x) > 0$，则意味着 $x$ 要向 $fa_x$ 输送 $\delta(x)$ 捆干草。如果 $\delta(x) < 0$，则意味着 $fa_x$ 要向 $x$ 输送 $|\delta(x)|$ 捆干草。如果 $\delta(x) = 0$，则只用在子树内部调整即可。

由此，我们可以得到一个操作序列。但是它们的顺序没有规定，而且某些顺序可能是不合法的。因此，我们需要规划操作的顺序。

我们可以模拟一下操作：$\delta(x) = 0$ 的子树是自给自足的，只需遍历底下的子树即可。$\delta(x) > 0$ 的子树是富余的，所以当访问到这种子树时，要第一时间向上输送干草，这时这颗子树也变为 $\delta(x) = 0$ 的情况。$\delta(x) < 0$ 的子树是缺失的，所以 $fa_x$ 必须第一时间向下输送干草，使 $\delta(x)$ 变为 $0$。

另外地，在一颗树中，必然是先收集干草再输送干草，所以先访问 $\delta(x) > 0$ 的结点，最后访问 $\delta(x) < 0$ 的结点，可以保证不出现没有干草可以输送的情况。

[参考代码](https://www.luogu.com.cn/paste/nzltgfcz)

---

