# [BalticOI 2016] Bosses (day1)

## 题目描述

[BalticOI 2016 Day1]上司们


一家有 $n$ 名员工的公司将进行重组。在重组后的层级结构中（表示为一棵有根树），每个节点将作为其子节点的上司。

每位员工都有一个可以接受的上司列表。此外，所有员工都必须被分配一个薪水。薪水必须是一个正整数，并且每位上司的薪水必须大于其直接下属薪水之和。

你的任务是安排公司的结构，以确保满足上述所有条件，并且所有员工的薪水总和尽可能小。

## 样例 #1

### 输入

```
4
1 4
3 1 3 4
2 1 2
1 3
```

### 输出

```
8```

# 题解

## 作者：冷却心 (赞：6)

首先如果这棵树已知，我们考虑怎么求出薪水总和。每位上司的薪水必须大于其直接下属薪水之和，那我们就令其等于下属薪水之和加一，然后手玩可得每个点最少应付的薪水是其子树的大小。

> 性质 1：已知这棵树时，每个点至少付的薪水是其子树大小。
>
> 证明：可以使用类似归纳法。
> - 首先这个结论对叶子结点显然成立，付一份薪水；
> - 然后考虑一个非叶子结点，如果他的子节点都满足这个结论，那么他需要的薪水至少是这些子节点的子树大小之和再加 $1$，也就是自己的子树大小，也满足。
> 
> 所以得证。

> 性质 2：若已知这个树，则最小薪水总和为每个点的深度之和。
>
> 证明：首先根据上面的说明有，每个点的最小薪水是其子树大小，那么最小总和就是子树大小的和。考虑每个点只会对它以及它的祖先的子树大小产生贡献，一共有深度 $d$ 个祖先（包括自己）所以贡献就是 $d$。那么总和就是深度之和。

所以把题目给的“可以接受的上司列表”转换为上司向下属连边的话，答案就是这张有向图的一个有根生成树（其实是树形图），要求所有节点深度之和最小。

注意到 $n\leq 5000$，考虑 $O(n^2)$ 做法。枚举树根，主要在于如何寻找以它为根的深度之和最小的生成树。这里使用 bfs 寻找生成树。

> 性质 3：bfs 得到的树一定不劣。
>
> 证明：（也可能仅仅算感性说明）原因是所求的最小总和即为深度最小总和，而最小的深度就是结点到根的最短路，而 bfs 可以 $O(n)$ 处理无权最短路，所以可以直接做。最后对每个点 bfs 出的生成树深度之和取最小值即可。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 5e3 + 10;
int n; vector<int> G[N];
int depth[N];
int BFS(int S) {
	for (int i = 1; i <= n; i ++) depth[i] = 0;
	queue<int> q; q.push(S); depth[S] = 1; int cnt = 0, sum = 0;
	while (!q.empty()) {
		++ cnt; int u = q.front(); sum += depth[u]; q.pop();
		for (int v : G[u]) if (!depth[v]) {
			depth[v] = depth[u] + 1; q.push(v);
		}
	} return (cnt < n ? 2e9 : sum);
}

int main() {
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++) {
		int m; cin >> m;
		for (int j = 1, u; j <= m; j ++) {
			cin >> u; G[u].emplace_back(i);
		}
	} int Ans = 2e9;
	for (int i = 1; i <= n; i ++)
		Ans = min(Ans, BFS(i));
	cout << Ans;
	return 0;
}
```

---

## 作者：PragmaGCC (赞：2)

首先由题目给的条件，我们可以建出一张图。

之后考虑这张图的一棵生成树，使其满足题意（即和最小）

不妨思考以下：如果说一个节点可以放在第 $a$ 层和第 $b$ 层 $a<b$，那么，放在哪一层更优呢？

显然应该是 $a$ 层，因为如果放在更下面，就会凭空给上面的节点增加价值。

所以我们要找到树一定要让深度尽量小。

因为`bfs`具有层序性，我们直接从每一个点出发，在这张图上`bfs`即可。最终的搜索树即为所求。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
int read() {
	register int n = 0, f = 1;
	register char ch = getchar();
	while(ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	} 
	while(ch >= '0' && ch <= '9') {
		n = (n << 3) + (n << 1) + (ch ^ '0');
		ch = getchar();
	}
	return f * n;
}
const int N = 5005, M = 10005, INF = 0x3f3f3f3f;
int n;
struct Edge {
	int to, next;
} e[M];
int head[N], ecnt, dep[N];
bool vis[N];
void addedge(int from, int to) {
	e[++ecnt] = (Edge) { to, head[from] };
	head[from] = ecnt;
}
std::queue<int> q;
int bfs(int s) {
	memset(vis, 0, sizeof(vis));
	memset(dep, 0, sizeof(dep));
	int ans = 1, tot = 1;
	q.push(s);
	vis[s] = 1, dep[s] = 1;
	while(!q.empty()) {
		const int x = q.front();
		q.pop();
		for (int i=head[x]; i; i=e[i].next) {
			const int y = e[i].to;
			if (vis[y]) continue;
			vis[y] = 1, dep[y] = dep[x] + 1;
			tot++, ans += dep[y];
			q.push(y);
		}
	} 
	return tot < n ? INF : ans;
}
int main(void) {
	n = read();
	for (int u=1; u<=n; u++) {
		int num = read();
		for (int i=1; i<=num; i++) {
			int v = read();
			addedge(v, u);
		}
	}
	int ans = INF;
	for (int root = 1; root <= n; root++)
		ans = std::min(ans, bfs(root));
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：ADNAP (赞：1)

### Solution
这道题的结论挺好感性理解的，手模一个样例就能猜出来结论了，先说结论：根据 bfs 序能拓展就拓展即可。

至于为什么，我们可以假定 $dep_u < dep_v$，而 $w$ 的权值为 $k$，$w$ 既可以成为 $u$ 的儿子，又可以成为 $v$ 的儿子。那我们把 $w$ 从 $v$ 的儿子变成 $u$ 的儿子时，$v$ 到其祖先 $x$，$dep_x=dep_u$ 的权值都减少了 $k$，但是 $u$ 的权值不变。

所以我们把一个权值为 $k$ 的节点往上挪深度 $d$ 后，总权值会减去 $d \times k$。

换句话说，我们要尽量在第一次拓展到某节点时就将其加入到树上。

这个用 bfs 实现即可，这部分的时间复杂度为 $O(n)$，因此时间还允许我们枚举根节点，那么总的时间复杂度就是 $O(n^2)$ 的。

具体实现的时候我们可以在拓展过程中记录维护 $vis$ 和数组 $d$，从 $u$ 拓展到 $v$ 时我们就记 $vis_v=u$，表示 $v$ 是由 $u$ 拓展得到的，再记 $d_u + 1$，表示 $u$ 的儿子数量增加 $1$。

然后我们利用上述两个数组跑拓扑，维护数组 $f$，$f_i$ 表示节点 $i$ 的权值。
### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef int ll;
const ll N=5e3+1e2,M=1e4+1e2,sup=1e15;
ll n;
ll h[N],t[M],nex[M],cnt;
void add(ll u,ll v)
{
    ++cnt;
    t[cnt]=v;
    nex[cnt]=h[u];
    h[u]=cnt;
}
ll vis[N],d[N],f[N];
ll q[N],hh,tt;
ll bfs(ll s)
{
    hh=1,tt=1;
    q[hh]=s;
    while(hh<=tt)
    {
        ll u=q[hh];
        for(ll i=h[u];i;i=nex[i])
        {
            ll j=t[i];
            if(vis[j])continue;
            vis[j]=u,d[u]++;
            q[++tt]=j;
        }
        hh++;
    }
    if(tt!=n)return sup;
    hh=1,tt=0;
    for(ll i=1;i<=n;i++)
        if(!d[i])q[++tt]=i;
    memset(f,0,sizeof f);
    ll res=0;
    while(hh<=tt)
    {
        ll u=q[hh];
        if(u==n+1)break;
        f[u]++;
        res+=f[u];
        f[vis[u]]+=f[u];
        d[vis[u]]--;
        if(!d[vis[u]])q[++tt]=vis[u];
        hh++;
    }
    return res;
}
signed main()
{
    scanf("%d",&n);
    ll m,u;
    for(ll i=1;i<=n;i++)
    {
        scanf("%d",&m);
        for(ll j=1;j<=m;j++)
        {
            scanf("%d",&u);
            add(u,i);
        }
    }
    ll ans=sup;
    for(ll i=1;i<=n;i++)
    {
        memset(vis,0,sizeof vis);
        memset(d,0,sizeof vis);
        vis[i]=n+1;
        ans=min(ans,bfs(i));
    }
    printf("%d",ans);
}
```

---

## 作者：ZPB2011 (赞：1)

# Bosses

[题目传送门](https://www.luogu.com.cn/problem/P4674)

## 思路

有贪心策略，因为要权值和最小可以把叶子节点的权值设为 $1$，然后我们发现每个节点的值都是由孩子节点转移的，由于叶子节点是权值是 $1$，所以叶子节点传上去的权值就是深度。于是我们就可以发现题目让我们构造一棵深度最小的树。

易错：**在构造时要判断有没有搜到所有的点**。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int n, vis[500005], dep[500005];
vector<int> g[500005];

int bfs(int x) {
	memset(dep, 0, sizeof(dep));//记得清零
	memset(vis, false, sizeof(vis));
	queue<int> que;
	que.push(x);
	int cnt = 1, sum = 1;
	vis[x] = true;
	dep[x] = 1;
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		for(int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if(!vis[v]) {
				dep[v] = dep[u] + 1;
				vis[v] = true;
				cnt++;
				sum += dep[v];
				que.push(v);
			}
		}
	}
	if(cnt == n) return sum;//一定要判断啊！！！
	return 1e9;
}

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int k;
		cin >> k;
		for(int j = 1; j <= k; j++) {
			int x;
			cin >> x;
			g[x].push_back(i);
		}
	}
	int minn = 1e9;
	for(int i = 1; i <= n; i++) minn = min(minn, bfs(i)); //暴力求出答案
	cout << minn << endl;
	return 0;
}
```

---

## 作者：Xiphi (赞：1)

首先观察题面，不难得到工资之和可以用如下式子递归的表示：
$$\sum_{x \in son(1)} f(x)$$

其中 $f(x)=\sum_{i\in son(x)} f(i)$，当 $i$ 为叶子节点时 $f(x)=1$。总结一下就是，所有的节点的深度之和。

那如何构造使得这个最小呢，感性理解一下就是要让所有节点距离根节点最近，不难想到 $\rm bfs$ 树的结构，这样根节点与其他点的距离就是最短的了。然后枚举根节点，建一颗 $\rm bfs$ 树之后求答案最小值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
int n,k[5005];
vector<int> Adj[5005],Adj1[5005],Adj2[5005];
int vis[5005],Val[5005];
queue<int> q;
void solve(int x,int fa){
    for(int i=0;i<Adj1[x].size();++i){
        if(Adj1[x][i]!=fa){
            solve(Adj1[x][i],x);
            Val[x]+=Val[Adj1[x][i]];
        }
    }
    Val[x]++;
}
int solve1(){
    int sum=0;
    for(int i=1;i<=n;++i){
        sum+=Val[i];
        Val[i]=0;
    }
    for(int i=1;i<=n;++i) if(!vis[i]) return 0x3f3f3f3f;
    return sum;
}
signed main(){
    pair<int,int> A={0,0};
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>k[i];
        for(int j=1,x;j<=k[i];++j){
            cin>>x;
            Adj[x].push_back(i);
        }
    }
    int ans=0x3f3f3f3f;
    for(int i=1;i<=n;++i){

    memset(vis,0,sizeof vis);
    A.second=i;
    q.push(A.second);
    vis[i]=1;
    int cnt=0;
    while(!q.empty()){
        int top=q.front();
        q.pop();
        for(int j=0;j<Adj[top].size();++j){
            int v=Adj[top][j];
            if(!vis[v]){
                Adj1[top].push_back(v);
                q.push(v);
                vis[v]=1;
                cnt++;
            }
        }
    }
    solve(i,0);
    ans=min(ans,solve1());
    for(int j=1;j<=n;++j) Adj1[j].clear();
    }
    cout<<ans;
    return 0;
}
/*
4
1 4
3 1 3 4
2 1 2
1 3
*/
```

---

## 作者：freeplume (赞：1)

这道题的翻译出锅了，题意大概是：已知每个人能接受自己上司是谁，要你确定这个公司的上司下属关系。

首先分析问题，上司的工资最小自然是下属的工资之和加一。因此我们考虑跑最短路，有一些具体问题：

### 如何转化成最短路？

首先最短路所经过的路径一定是一棵树，和这里上司下属关系一样：除了根节点无父亲，其他节点有且仅有一个父亲，同样地，除了最顶头的上司无上司，其他下属有且仅有一个上司。

但因为我们不确定这棵树的形态，因此我们考虑对所有节点，都将其作为根做一次最短路。

### 关于工资

对于每一个节点，其都为其所有祖先分别做出了 1 点的贡献。那么我们考虑计算每一个节点对祖先的贡献，然后依题意要各加上 1。那么每个节点的贡献就是其深度。

### 关于连边

我们肯定从根节点开始计算，往其下属走。因此我们加边时从上司加到下属。

### 关于计算最短路时的细节

因为工资必须是正整数，因此最小的工资应为1，在最短路中体现为根节点的 $dis$ 值被初始化为 1。另外要注意 n 轮最短路相互独立，每次最短路都要做一次初始化。

可能有多个点不连通，保险起见，为防止溢出还是要特判一波。在这里体现为如果存在一点或多点的最短路为 $\inf$ 则不连通。

在这篇题解写完之后，突然意识到可以直接 bfs，其时间复杂度应该会更优秀，在这里权当一种另解，仅供参考。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=5005,maxm=10005,inf=1e9;
int n,cnte,ans=inf;
int head[maxn],nxt[maxm<<1],to[maxm<<1];
int dis[maxn],vis[maxn];
struct node{
	int pos,dis;
};
priority_queue<node> q;

inline int rd(){
	int s=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}

bool operator<(node u,node v){
	return u.dis>v.dis;
}

inline void adde(int u,int v){
	cnte++;
	nxt[cnte]=head[u];
	head[u]=cnte;
	to[cnte]=v;
}

inline int dijkstra(int x){
	int res=0;
	for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
	q.push((node){x,1});
	dis[x]=1;
	while(!q.empty()){
		int u=q.top().pos;q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				q.push((node){v,dis[v]});
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(dis[i]==inf) return inf;
		res+=dis[i];
	}
	return res;
}

int main(){
	n=rd();
	for(int i=1;i<=n;i++){
		int w=rd();
		while(w--){
			int v=rd();
			adde(v,i);
		}
	}
	for(int i=1;i<=n;i++){
		ans=min(ans,dijkstra(i));
	}
	printf("%d\n",ans);
	return 0; 
}
```

---

## 作者：yangwenbin (赞：1)

首先因为同学们去重新翻译下这些东西，洛谷的翻译出锅了。

在输入的时候，输入的是他认为能做他直属上司的人。

所以去改一下自己的连边方向看看，些许就过了。

# 题解 P4674 【[BalticOI 2016 day1]Bosses】

[P4674 【[BalticOI 2016 day1]Bosses】](https://www.luogu.com.cn/problem/P4674)

首先是要从一堆有向边中，选择几个做成已 $i$ 为根节点的树。

这里用 $bfs$ 的算法去实践。

证明 $bfs$ 的正确性与优越性。

首先很显然的事实就是层数越少越优秀，可又为什么呢？？

不妨证明一下，搜索成树后：

$$
\forall x \in \{ x \mid outdegree_i = 0 \}
$$
$$
\therefore \min value_i = 1
$$
即结点 $i$ 作为叶子结点，其对于总工资的贡献是 $1$ 。

$$
\forall x \in \{ x \mid outdegree_i \not = 0 \}
$$
$$
\therefore \min value_i = \sum \limits_{j = 1}^{numson_i} value_{numson \lbrack j \rbrack} + 1
$$
即结点 $i$ 作为叶子结点，其对于总工资的贡献是 $1$ 

同时它的所有的祖先，这个节点都对上司（祖先）的工资做出了 $1$ 点的贡献。

同理可知每一个点都会对其祖先的工资做出总数为自己的直系祖先数的贡献，再加上本生的贡献 $1$ 。

$$
\therefore value_i = deep_i
$$
$$
\because ans = \sum \limits_{i = 1} ^n value_i
$$
$$
\therefore ans = \sum \limits_{i = 1} ^n deep_i
$$

所以从层数越少在计算中是越优化的。

因此 $bfs$ 有其正确性和优越性。

之后就是换根 $bfs$ 

注意还要判联通

# code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
// 其实不用开 long long
const int SIZE = 5050;

inline int read()
{
	int x = 0,f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		f = (ch == '-' ? -1 : 1);
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f * x;
}

int n,num_edge;
int head[SIZE],deep[SIZE];
struct node
{
	int to,nxt;
};
node edge[SIZE * SIZE];

inline void add(int u,int v)
{
	edge[++num_edge].to = v;
	edge[num_edge].nxt = head[u];
	head[u] = num_edge;
}

inline int bfs(int pos)
{
	int ans = 1,num = 1;
	bool vis[SIZE];
	queue <int> que;
	memset(deep,0,sizeof(deep));
	memset(vis,false,sizeof(vis));
	que.push(pos);
	vis[pos] = true;deep[pos] = 1;
	while (!que.empty())
	{
		int u = que.front();
		que.pop();
		for (int i = head[u]; i ; i = edge[i].nxt)
		{
			int v = edge[i].to;
			if (vis[v]) continue;
			vis[v] = true;
			deep[v] = deep[u] + 1;
			que.push(v);
			num++;
			ans += deep[v];
		}
	}
	if (num == n) return ans;
	else return 9223372036854775807;
}

signed main()
{
	n = read();
	for (int i = 1; i <= n; ++i)
	{
		int x = read();
		for (int j = 1; j <= x; ++j)
		{
			int v = read();
			add(v,i);
		}
	}
	int ans = 9223372036854775807;
	for (int i = 1; i <= n; ++i)
	{
		ans = min(ans,bfs(i));
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：JK_LOVER (赞：1)

## 题目描述
在根节点确定的时候，让树的深度总和最小。
## 分析
如何转化这个问题，我们发现我们在确定根的情况下，每个叶节点都要为 $1$ 是最优的。因为要求 $val_{fa} > \sum_{x\in son} val_x$ ，所以 $val_{fa} = 1+\sum_{x \in son} val_x $ ，那么在路径确定的情况下，每个点的值是确定的。我们把第二个式子展开可得：
$$
val_{fa} = 1+\sum_{x \in son_{fa}} (1+\sum_{y\in son_x}val_y)
$$
那么我们考虑每个点的贡献就是当前节点到根的距离，为了让距离最短，我们要让树尽可能的低。所以可以贪心的将叶节点靠近树根。然后一个   $bfs$ 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5010;
int read(){
	int x = 0,f = 0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f?-x:x;
}
vector<int> G[N];
const int inf = 0x3f3f3f3f;
int n,dep[N],q[N<<2],head,tail;
long long ans = inf;
int main()
{
	n = read();
	for(int i = 1;i <= n;i++)
	{
		int j = read();
		while(j--)
		{
			int fa = read();
			G[fa].push_back(i);
		}
	}
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= n;j++)
		dep[j] = inf;
		dep[i] = 1;head = 1,tail = 2;
		q[1] = i; 
		while(head<=tail)
		{
			int x = q[head++];
			for(int j = 0;j < G[x].size();j++)
			{
				int y = G[x].at(j);
				if(dep[y] != inf) continue;
				else dep[y] = dep[x]+1,q[++tail] = y;
			}
		}
		long long sum = 0;
		for(int j = 1;j <= n;j++)
		sum += dep[j];
		ans = min(ans,sum);
	}
	printf("%lld\n",ans);
	return 0;
}
```
[博客链接](https://www.luogu.com.cn/blog/xzc/solution-p4674)

---

## 作者：Dream__Sky (赞：0)

首先有一个很显然的贪心策略，为了让权值和尽量少，树的叶节点权值设为 $1$。

接着我们来分析一下题意求的是什么。设当前位于叶子节点 $i$，它的父节点为 $f(i)$。因为每个父节点的权值是子节点的权值再加一，从叶子节点考虑，当前节点 $i$ 的值会随着它的父亲，父亲的父亲，一直传到根节点，该链上的每个节点权值都会加上一，就相当于它的深度。

再考虑 $f(i)$，这个节点的有一部分值是从子节点转移而来，我们不管。我们要考虑的就是多出来的 $1$，其实这个 $1$ 同前文，也会一直往上传，直到到根节点，上传经过的节点数量，也相当于它的深度。

知道了这个结论，题目就相当于让你构造一棵深度之和最小的数，显然就是 `bfs` 搜索树。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n,vis[N],dep[N];
vector<int> e[N];
int bfs(int root)
{
	memset(dep,0,sizeof dep);
	memset(vis,0,sizeof vis);
	int ans=1,tot=1;
	queue<int> q;
	q.push(root);
	vis[root]=dep[root]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(auto v:e[u])
		{
			if(vis[v]) continue;
			dep[v]=dep[u]+1;
			vis[v]=1;
			tot++,ans+=dep[v];
			q.push(v);
		}
	}
	return tot<n?2e9:ans;
}
int main()
{
	cin>>n;
	for(int i=1,m;i<=n;i++) 
	{
		cin>>m;
		for(int j=1,x;j<=m;j++)
		{
			cin>>x;
			e[x].emplace_back(i);
		}	
	}
	
	int ans=2e9;
	for(int i=1;i<=n;i++) ans=min(ans,bfs(i));
	cout<<ans;
	return 0;
}

```


---

## 作者：TheCliffSwallow (赞：0)

赛时 T3，忘记特判不是树+数据捆绑->0pts

### 题意
给一棵树可能的一些父亲与儿子的关系，每个点的点权为儿子节点点权和加 $1$，叶子节点的点权为 $1$，求可能的构造树的方案中总点权数最小为多少。
### 思路
分析样例，在计算固定的一棵树的答案时，每个节点都会对从根节点到这个点的路径上的点产生影响，最后能发现其实一棵树的答案就是每个节点的深度总和，因为点数不变，所以要让答案最小就让整体的图更加靠近根节点，即从根节点开始的 BFS 序。枚举根节点并进行 BFS 并输出即可，别忘了特判无法构成树的情况。
### Code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<queue>
#define int long long
using namespace std;
int n;
set<int>s[5005];
int d[5005];
bool vis[5005];
vector<int>vec[5005];
int ans=1e18;
void dfs(int x){
    //cout<<x<<endl;
    for(int i=0;i<vec[x].size();++i){
        int v=vec[x][i];
        dfs(v);
        d[x]+=d[v];
    }
}
int solve(int x){
    queue<int>q;
    for(int i=1;i<=n;i++)vec[i].clear();
    memset(vis,0,sizeof(vis));
    q.push(x);
    vis[x]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        //cout<<u<<endl;
        for(set<int>::iterator it=s[u].begin();it!=s[u].end();it++){
            int v=*it;
           // cout<<v<<endl;
            if(vis[v])continue;
            vis[v]=true;
            q.push(v);
            vec[u].push_back(v);
          //  cout<<114514<<u<<' '<<v<<endl;
        }
    }
   // for(int i=1;i<=n;i++)cout<<vis[i]<<' ';
    for(int i=1;i<=n;i++)if(!vis[i])return 1e18;
    dfs(x);
    int sum=0;
    for(int i=1;i<=n;i++){
        sum+=d[i];
      //  cout<<i<<' '<<d[i]<<endl;
    }
    //cout<<x<<' '<<sum<<endl<<endl<<endl;
    return sum;
}
signed main(){
   // freopen("boss.in","r",stdin);
   // freopen("boss.out","w",stdout);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        int tmp1;
        scanf("%lld",&tmp1);
        for(int j=1;j<=tmp1;j++){
            int tmp;
            scanf("%lld",&tmp);
            s[tmp].insert(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)d[j]=1;
        ans=min(ans,solve(i));
    }
    printf("%lld\n",ans);
    return 0;
}
/*
4
1 4
3 1 3 4
2 1 2
1 3
*/

```


---

## 作者：infinities (赞：0)

这题翻译有误，正确的输入格式：

第一行包含一个整数 $n$，表示职员的个数，职员依次编号为 $1,2,3...,n$。

接下来 $n$ 行，第 $i$ 行包含一个整数 $k_i$，接下来 $k_i$ 个数，表示可以作为第 $i$ 个人上司(在树上表现为父亲)的人。

因为 $n \le 5000$ ，而且是有根树，所以我们可以枚举一下每个点作为根节点，使用BFS贪心使得所有点尽可能靠近根节点。

计算答案比较显然，我们肯定使得所有叶子节点工资全部为一。因为要求每个上司的工资大于其所有下属之工资和，所以深度每增加一，其到根节点的距离也就加一，所以它的上司所需要加的钱也就加一，这样每个点的贡献就是它的深度了。

说几个注意点：

- 根节点的深度设为1，因为根节点需要比它的直接下属的工资和大1。

- 不用开long long，因为就算最坏情况是一条链，其深度为 $1,2,3...,n$，因为 $n \le 5000$，根据等差数列公式 $\frac{n(n-1)}{2}$ 可发现答案也不过是个 $10^8$ 级别的数。

- 注意特判以一个点为根节点，所有点构不成一棵树的情况，这种情况根据题目意思要舍去。

code：

```cpp
#include<bits/stdc++.h>
#define rint register int
const int maxn = 2e4 + 10;
const int INF = 2e9;
int read(){
    int x = 0,f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}//快读板子 
using namespace std;

int n, k, nxt[maxn], to[maxn], fr[maxn], cnt, vis[maxn >> 1], minn = 2147483645, dep[maxn];
void add(int u, int v){
	to[++cnt] = v, nxt[cnt] = fr[u], fr[u] = cnt;
}
queue<int>q;
void bfs(int now){//bfs贪心计算答案 
	q.push(now);
	while(!q.empty()){
		int u = q.front();
		q.pop();
	    for(int i = fr[u]; i; i = nxt[i]){
		    if(vis[to[i]] == 0){//贪心，如果这个节点没有被用过，就把它加到自己的儿子上 
		    	vis[to[i]] = 1;
		    	if(!dep[to[i]])dep[to[i]] = dep[u] + 1;//更新深度 
			    q.push(to[i]);
		    }
	    }
    }
}

signed main(){
	n = read();
	for(int i = 1; i <= n; i++){
		k = read();
		for(int j = 1; j <= k; j++){
			int v = read();
			add(v, i);//注意输入的是可以当其上司的人 
		}
	}
	
	for(int i = 1; i <= n; i++){
		int minx = 0;
		memset(vis, 0, sizeof(vis));
		memset(mon, 0, sizeof(mon));
		memset(dep, 0, sizeof(dep));//每次计算重新赋初值 
		dep[i] = 1;//根节点深度一定为1 
		vis[i] = 1;
		bfs(i);
		for(int j = 1; j <= n; j++){if(!dep[j])minx = 1234567890; minx += dep[j];}
		//如果构不成树就不存在这种情况，要舍去，否则只有60-70pts
        //当然也可以不用把minx设成无穷大，直接在dep赋初值的时候赋值为无穷大，不过这样就需要开long long了。
		minn = min(minn, minx);
	}
	
	cout << minn;
}
```

---

## 作者：木木！ (赞：0)

思维题，除非实在没头绪，建议再想十分钟QwQ。

（题意翻译有误，正确翻译见讨论版）

首先，对于一颗树，很容易通过一次bfs求出这棵树的最小薪资和。如果将节点的贡献提前计算，则一个节点对答案的贡献就等于它的深度。

所以，对于一棵树，最小薪资和就是它的节点深度之和（根节点深度为1）

再看数据范围，$n\leq 5000$，就很容易想到用$\Theta(n^2)$的算法。

因此，算法就是枚举每个点为根，然后计算以该点为根时的最小薪资和。

当确定一个点为根时，需要让深度和最小。很容易想到，我们贪心将所有可能的子节点都挂上去。因为如果该子节点不挂上去的话肯定不优。

于是，如果以有向边<i,j>表示i可以做j的上司建图，当节点x为根时，易证y的最小深度就是x->y的最短路径。

由于边权固定为1，所以最短路径可以直接用bfs求。求一次薪资和是$\Theta(n+\Sigma k_i)$的。

于是，总时间复杂度就是$\Theta(n^2+n\times \Sigma k_i)$

附AC代码

```cpp
#include <queue>
#include <cstdio>
using namespace std;

void chkmin(int& a,int b)
{
	if(b<a)
	{
		a = b;
	}
}

int beg[5005];
int ed[10005];
int nxt[10005];
int top;

void addedge(int a,int b)
{
	++top;
	ed[top] = b;
	nxt[top] = beg[a];
	beg[a] = top;
}

int n;
int ans = 0x7f7f7f7f;
int depth[5005];

void bfs(int x)
{
	for(int i=1; i<=n; ++i)
	{
		depth[i] = 0;
	}
	
	queue<int> q;
	q.push(x);
	depth[x] = 1;
	
	while(!q.empty())
	{
		int th = q.front();
		q.pop();
		
		for(int p=beg[th]; p; p=nxt[p])
		{
			if(!depth[ed[p]])
			{
				depth[ed[p]] = depth[th]+1;
				q.push(ed[p]);
			}
		}
	}
	
	int curans = 0;
	for(int i=1; i<=n; ++i)
	{
		if(!depth[i])
		{
			goto die; //以i为根无解，直接狗带
		}
		curans += depth[i];
	}
	
	chkmin(ans,curans);
	
	die:;
}

int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
	{
		int k;
		scanf("%d",&k);
		for(int j=1; j<=k; ++j)
		{
			int tmp;
			scanf("%d",&tmp);
			addedge(tmp,i);
		}
	}
	
	for(int i=1; i<=n; ++i)
	{
		bfs(i);
	}
	
	printf("%d",ans);
}
```

---

