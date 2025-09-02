# [ABC148F] Playing Tag on Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc148/tasks/abc148_f

$ N $ 頂点の木があります。$ i $ 番目の辺は頂点 $ A_i $ と $ B_i $ を双方向に結んでいます。

この木の頂点 $ u $ に高橋君が、頂点 $ v $ に青木君がいます。

$ 2 $ 人は次のような手順で鬼ごっこをします。

- $ 1 $. 高橋君と青木君が同じ頂点にいるときゲームを終了する。そうでないとき、高橋君は隣接する頂点を $ 1 $ つ選んでその頂点に移動する。
- $ 2 $. 高橋君と青木君が同じ頂点にいるときゲームを終了する。そうでないとき、青木君は隣接する頂点を $ 1 $ つ選んでその頂点に移動する。
- $ 3 $. $ 1 $ に戻る。

高橋君はできるだけ遅くゲームが終了するように移動し、青木君はできるだけ早くゲームが終了するように移動します。

高橋君と青木君が常に互いの位置と戦略を把握し最適に移動するとき、ゲームが終了するまでに青木君が移動する回数を求めてください。

なお、ゲームは必ず終了することが証明できます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ u,v\ \leq\ N $
- $ u\ \neq\ v $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- 与えられるグラフは木である

### Sample Explanation 1

互いに最適に移動した場合、ゲームは次のように進行します。 - 高橋君が頂点 $ 3 $ に移動 - 青木君が頂点 $ 2 $ に移動 - 高橋君が頂点 $ 5 $ に移動 - 青木君が頂点 $ 3 $ に移動 - 高橋君が頂点 $ 3 $ に移動 このとき、ゲームが終了するまでの青木君の移動回数は $ 2 $ 回です。 各手番で同じ頂点にとどまることは出来ないことに注意してください。

## 样例 #1

### 输入

```
5 4 1
1 2
2 3
3 4
3 5```

### 输出

```
2```

## 样例 #2

### 输入

```
5 4 5
1 2
1 3
1 4
1 5```

### 输出

```
1```

## 样例 #3

### 输入

```
2 1 2
1 2```

### 输出

```
0```

## 样例 #4

### 输入

```
9 6 1
1 2
2 3
3 4
4 5
5 6
4 7
7 8
8 9```

### 输出

```
5```

# 题解

## 作者：mxjz666 (赞：3)

### 思路
跑两次最短路，一次以逃跑者为根，一次以追捕者为根，如果在 $i$ 号节点追捕者到这里的时间小于逃跑者到这里的时间，那么更新答案。

---------------------
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,su,sv,u[N],v[N],ans;
vector<int> edge[N];
void dfs(int dis[],int x,int fa){
	for(auto i:edge[x]){
		if(i==fa){
			continue;
		}
		dis[i]=dis[x]+1;
		dfs(dis,i,x);
	}
	return;
}
signed main(){
	scanf("%lld%lld%lld",&n,&su,&sv);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	dfs(u,su,0);
	dfs(v,sv,0);
	for(int i=1;i<=n;i++){
		if(u[i]<v[i]){
			ans=max(ans,v[i]); 
		}
	}
	printf("%lld",ans-1);
	return 0;
}
```

---

## 作者：_byta (赞：3)

为了方便处理问题，我们令 A 玩家的初始点为树的根。

首先，我们站在T玩家的立场考虑，由于 A 在根节点， 
 
 T 要尽量使游戏时间长，

所以 T 玩家要在被 A 抓到前达到尽可能深的点。因此，我们先预处理一遍

以A玩家为根节点，每个节点的深度。代码：

```cpp
void dfs1(int u, int fa, int d) 
{
	maxdep[u] = 0;
    disA[u] = d;
	for(int i = head[u]; i; i = nxt[i]) 
	{
		int v = vet[i];
		if(v == fa) continue;
		dfs1(v, u, d+1);
		maxdep[u] = max(maxdep[u], maxdep[v] + 1);
	}
}
```

接着我们枚举每一个T能在不被A抓到时能到达的点，取一个最大深度。

放个代码：

```cpp
void dfs2(int u, int disB) 
{
	if(disB < disA[u]) ans = max(ans, disA[u] + maxdep[u]-1);
	for(int i = head[u]; i; i = nxt[i]) 
	{
		int v = vet[i];
		if(disA[v] < disA[u]) dfs2(v, disB+1);
	}
}
```

最大的的深度即为答案。

最后贴上完整代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int N = 100005;
int n, U, V, x, y, maxdep[N], head[N], vet[2*N], nxt[2*N], num,disA[N], ans;
void add(int u, int v) 
{
	num++;
	vet[num] = v;
	nxt[num] = head[u];
	head[u] = num;
}
void dfs1(int u, int fa, int d) 
{
	maxdep[u] = 0;
    disA[u] = d;
	for(int i = head[u]; i; i = nxt[i]) 
	{
		int v = vet[i];
		if(v == fa) continue;
		dfs1(v, u, d+1);
		maxdep[u] = max(maxdep[u], maxdep[v] + 1);
	}
}
void dfs2(int u, int disB) 
{
	if(disB < disA[u]) ans = max(ans, disA[u] + maxdep[u]-1);
	for(int i = head[u]; i; i = nxt[i]) 
	{
		int v = vet[i];
		if(disA[v] < disA[u]) dfs2(v, disB+1);
	}
}
int main() 
{
	scanf("%d%d%d", &n, &U, &V);
	for(int i = 1; i <= n-1; i++) 
	{
		scanf("%d%d", &x, &y);
		add(x, y);
		add(y, x);
	}
	dfs1(V, 0, 0);
	dfs2(U, 0);
	printf("%d\n", ans);
}
```




---

## 作者：CaiXY06 (赞：3)

考虑到 T 想活得久， A 想尽早追上 T ,所以我们就将问题转化为在树上找一条最长链，使得 T 能比 A 先到达这条链，就像这样:

![](https://cdn.luogu.com.cn/upload/image_hosting/ucq0vhu2.png)

所以我们就可以在树上跑两遍单源最短路，因为边权为 $1$，所以用**BFS**就可以了

```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{
	int to,next;
}e[200010];
int n,s,t,cnt,ans,head[100010],a[100010],b[100010],dis[100010];
bool vis[100010];
inline void add(int u,int v){
	cnt++;
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
inline void bfs(int S){
	memset(vis,0,sizeof(vis));
	memset(dis,0,sizeof(dis));
	queue<int>q;
	q.push(S);
	vis[S]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to;
			if(vis[v])continue;
			vis[v]=1;
			dis[v]=dis[u]+1;
			q.push(v);
		}
	}
	if(S==s)memcpy(a,dis,sizeof(dis));
	else memcpy(b,dis,sizeof(dis));
}
int main(){
	scanf("%d%d%d",&n,&s,&t);
	for(int i=1,x,y;i<n;i++){
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	bfs(s);
	bfs(t);
	for(int i=1;i<=n;i++)
	if(a[i]<b[i])ans=max(ans,b[i]);
	printf("%d",ans-1);
	return 0;
}
```


---

## 作者：Tan_Wei_Ye (赞：3)

不难发现，如果一个点到 $u$ 的距离**小于**它到 $v$ 的距离，那么 $T$ 就不会在这个点被 $A$ 追到。

------------

#### 由此可以得到解法:

1. 通过搜索算出 $u$ 和 $v$ 到树上其他点的距离（由于是**树**，路径唯一，只需要 $bfs$ 或 $dfs$ 就彳亍了）。

2. $O(n)$ 枚举找答案就解决了。


------------

#### 时间复杂度：
因为在搜索中每个点只被枚举到 $1$ 遍，所以总体复杂度是 $O(n)$ 的。



------------

还有一些细节在代码里讲，上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,u,v,du[N],dv[N],ans;
vector<int> e[N];//因为比较懒，所以用了邻接表存图
inline void dfs(int dis[],int x,int fa)
{
	for(int i=0;i<e[x].size();i++)
	{
		int v=e[x][i];
		if(v==fa) continue;
		dis[v]=dis[x]+1;
		dfs(dis,v,x);
	}
}
signed main()
{
	cin>>n>>u>>v;
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		e[x].push_back(y);//无向图，建双向边
		e[y].push_back(x);
	}
	dfs(du,u,0);//算出 u 到树上其他点的距离
	dfs(dv,v,0);//算出 v 到树上其他点的距离
	for(int i=1;i<=n;i++)
	{
		if(du[i]<dv[i]) 
			ans=max(ans,dv[i]); 
	}
	cout<<ans-1;
}
```

---

## 作者：f_hxr_ (赞：2)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc148_f) [AT 传送门](https://atcoder.jp/contests/abc148/tasks/abc148_f)

很明显，我们不关心高桥是怎么走的。

我们关心的是高桥**最终会去哪个地方**。

而根据贪心，高桥最终会在他**能到达的结点**中选一个**离青木最远的一个点**作为目标。

这样，我们以青木为根进行 DFS，然后从深到浅枚举每一个叶子结点，判断高桥是否能在被青木抓到之前到达那里即可。

判断高桥是否可达到一个结点，只需要判断他和青木哪个离那个结点近即可。

注意到如果青木和高桥离一个结点的距离相等的话，那么当高桥在去那个结点的路上时肯定会被捉住。

时间复杂度 $O(N\log N)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL maxn=300005;
LL N,U,V,ans;
LL head[maxn],nxt[maxn],to[maxn],dep[maxn],tot;
LL Mu_leaf[maxn],cnt,f[maxn][20];
void add(LL u,LL v){
	nxt[++tot]=head[u];to[tot]=v;head[u]=tot;
	nxt[++tot]=head[v];to[tot]=u;head[v]=tot;
	return;
}
void dfs(LL u,LL fa){
	dep[u]=dep[fa]+1;f[u][0]=fa;
	for(int i=1;i<20;i++)
		f[u][i]=f[f[u][i-1]][i-1];
	LL size=0;
	for(int i=head[u];i;i=nxt[i]){
		if(to[i]==fa)continue;size++;
		dfs(to[i],u);
	}
	if(size==0)Mu_leaf[++cnt]=u;
	return;
}
LL LCA(LL u,LL v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=19;i>=0;i--)
		if(dep[f[u][i]]>=dep[v])u=f[u][i];
	if(u==v)return u;
	for(int i=19;i>=0;i--)
        if(f[u][i]!=f[v][i])
            u=f[u][i],v=f[v][i];
	return f[u][0];
}
LL dis(LL u,LL v){return dep[u]+dep[v]-2*dep[LCA(u,v)];}
int CCF(LL T){
	LL LHQ=LCA(U,T);
	return dis(U,LHQ)<dis(V,LHQ);
}
int main(){
	cin>>N>>U>>V;
	for(int i=1;i<N;i++){
		int a,b;cin>>a>>b;
		add(a,b);
	}
	dfs(V,0);
	for(int i=1;i<=cnt;i++){
		LL L=Mu_leaf[i];
		if(CCF(L))ans=max(ans,dis(V,L));
	}
	cout<<ans-1;
	return 0;
}
```

---

## 作者：kkxacj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc148_f)

#### 思路

考虑记录所有点到 $u$ 和到 $v$ 的最短距离，由于只有 $n - 1$ 条边，dfs 即可，如果 $i$ 到 $v$ 的距离 小于 $i$ 到 $u$ 的距离，说明 $T$ 不可能会来这里，因为 $T$ 要尽可能活的久，而且 $A$ 要早点抓住 $T$，由于问的是 $A$ 的行走次数，所以最后答案要减一。

献上 $20$ 行代码：
#### code

```c
#include<bits/stdc++.h>
using namespace std;
int n,u,v,x,y,v2[114514],v1[114514],ma;
vector<int>w[100010];
void dfs(int xx,int yy,int z){
	if(z) v1[xx] = yy;
	else v2[xx] = yy;
	for(int i = 0;i < w[xx].size();i++){
		if(z && !v1[w[xx][i]] && w[xx][i] != v) dfs(w[xx][i],yy + 1,z);
		else if(!z && !v2[w[xx][i]] && w[xx][i] != u) dfs(w[xx][i],yy + 1,z);
	}
}
int main(){
	scanf("%d%d%d",&n,&u,&v);
	for(int i = 1;i < n;i++) scanf("%d%d",&x,&y),w[x].push_back(y),w[y].push_back(x);
	dfs(v,0,1); dfs(u,0,0); 
	for(int i = 1;i <= n;i++)  if(v1[i] > v2[i]) ma = max(ma,v1[i]);
	printf("%d",ma - 1);
	return 0;
}
```


---

## 作者：iamjcer (赞：1)

# 思路
我们知道，T 的最优策略就是尽量离 A 远。

那么我们可以从 A 点出发跑一遍深搜，找到每个点到 A 的距离，然后再从 T 点出发跑一遍深搜，找到每个点到 T 的距离，那么因为一个点如果一个点到 A 的距离比到 T 的距离大，那么A肯定是能先走到那个结点的，然后能够堵住 T，所以现在的问题转化成了：找到一个到 T 距离最大，且到 A 的距离小于到 T 的距离的点。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
using namespace std;
int n,a,b,dis[N],dis2[N],ans=INT_MIN;
vector<int> v[N];
void dfs(int father,int now){
	for(int i=0;i<v[now].size();i++){
		int son=v[now][i];
		if(son==father) continue;
		dis[son]=dis[now]+1;
		dfs(now,son);
	}
}
void dfs2(int father,int now){
	for(int i=0;i<v[now].size();i++){
		int son=v[now][i];
		if(son==father) continue;
		dis2[son]=dis2[now]+1;
		dfs2(now,son);
	}
}
signed main(){
	scanf("%lld %lld %lld",&n,&a,&b);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%lld %lld",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(0,a);
	dfs2(0,b);
	for(int i=1;i<=n;i++){
		if(dis[i]<dis2[i]){
			ans=max(ans,dis2[i]);
		}
	}
	printf("%lld",ans-1);
	return 0;
}
```

---

## 作者：EatBread (赞：0)

学校的欢乐赛出现的题目，怪有意思的，来写篇题解。

这里提供一种 $O(N)$ 的简便的只跑一遍 dfs 的做法。

首先以 A 所在的点为根，这样 T 就只可以在自己所属的子树乱跑，方便统计。

算出 A 到 T 之间的距离 $m$，也就是 T 的深度，然后将距离除以 $2$ ，表示 T 最多往上走多少步。

但这里有个细节，如果 $m$ 为偶数的话，往上走 $m/2$ 的话 T 刚好被抓住，所以这种情况下 $m$ 要减 $1$。

然后我们贪心的直接让 T 往上走 $m$ 步先，可以证明，在走的过程中，答案不会变劣，最后输出 T 的深度加 T 子树的最长链减去 $1$ 即可（最长链在 dfs 时预处理出来）。

关于为什么减去 $1$：因为 A 是后手，所以当 A 把 T 逼到某个角落时，T 会自投罗网（自己模拟一下，这个很简单）。

代码（用了 vector 存图，跑的有点慢，但是很短，只有 525b）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=1500;
int n,a,b,dep[N],ma[N],f[N];
vector<int>e[N];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	f[u]=fa;
	for(auto v:e[u]){
		if(v==fa)continue;
		dfs(v,u);
		ma[u]=max(ma[u],ma[v]+1);
	}
}
signed main(){
	cin>>n>>a>>b;
	for(int i=1; i<n; i++){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(b,0);
	int m=(dep[a]-2)>>1;
	for(int i=1; i<=m; i++)a=f[a];
	printf("%d",dep[a]+ma[a]-2);
	return 0;
}
```

---

## 作者：iamajcer (赞：0)

# 思路

方便说明，我们令追的人是 A，被追的人是 B。

我们定根方便讨论。令 A 是根。

我们肯定想要 B 尽可能的往最远的点走，走到之后来回走即可。

所以我们要先处理出来 B 点能走到的点的步数，这样就可以求出距离 B 的最远点。

放个图方便理解下（~~图有点丑大佬轻喷~~）。
![](https://cdn.luogu.com.cn/upload/image_hosting/ie3sihea.png)

这时 B 点肯定会走到它父亲节点，然后往里深入。不然就会被 A 抓到，且不是最优。

所以判断 B 满足条件的点的集合中，离 A 最远的点，在同一步数的前提下，A 能走到的最远点不包括 B 点经过的点。

所以我们还要处理 A 能走到的点的步数。

最终答案就是满足上述条件的前提下，离 B 点最远的点，与 B 点的距离。

注意，最终答案要减去一。为什么？

因为 B 最终到的点肯定不是最远那个点，而是最远那个点的前面一个点。毕竟 A，B 的轮次不一样。我们可以用反证法。如果 B 最终到了最远点并且被 A 抓住，那么证明在上一步，B 和 A 也在一起，不然就不会一起走到最深一个点，那么就不合法了。

注意一下，我代码的 A 和 B 顺序是相反的了。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;

int n, s, t, u1, v1, A, B, disA[N], disB[N], ans=0;
vector<int> a[N];
void dfs(int u, int fa)
{
	for (int i=0; i<a[u].size(); i++)
	{
		int v=a[u][i];
		if (v==fa) continue;
		
		disA[v]=disA[u]+1;
		dfs(v, u);
	}
}
void dfs2(int u, int fa)
{
	for (int i=0; i<a[u].size(); i++)
	{
		int v=a[u][i];
		if (v==fa) continue;
		
		disB[v]=disB[u]+1;
		dfs2(v, u);
	}
}
int main()
{
	scanf("%d%d%d", &n, &A, &B);
	for (int i=1; i<n; i++)
	{
		scanf("%d%d", &u1, &v1);
		a[u1].push_back(v1);
		a[v1].push_back(u1);
	}
	dfs(A, -1);
	dfs2(B, -1);
	
	for (int i=1; i<=n; i++)
		if (disA[i]<disB[i]) ans=max(ans, disB[i]);
	
	printf("%d", ans-1);
	return 0;
}
/*
9 5 1
1 2
2 3
3 4
4 5
4 6
6 7
7 8
8 9

6

*/
```

---

## 作者：zheng_zx (赞：0)

## [ABC148F] Playing Tag on Tree

[题目传送门](https://www.luogu.com.cn/problem/AT_abc148_f)

### 题意

---

有两个人 $T$ 和 $A$ 分别站在 $u$ 号节点和 $v$ 号节点上，两个人轮流移动，$T$ 为先手，$A$ 为后手。如果某人发现自己和对方站在了同一个节点，那么游戏结束。

### 分析

---

根据题意描述，我们不难发现，若一个点到 $u$ 的距离小于它到 $v$ 的距离，那么 $T$ 就不会在这个点被 $A$ 追到。

所以我们可算出 $v$ 和 $u$ 到其他点的距离（```dfs``` 即可），然后再枚举出答案就可以了。

时间复杂度 $O(n)$。

#### AC code：
```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e5 + 7;
int n, u, v, x, y, vis[N], ans[N], m;
vector<int> w[N];
void dfs(int a, int b, int c){
    if(c) 
    	vis[a] = b;
    else 
    	ans[a] = b;
    for(int i = 0; i < w[a].size(); i++){
        if(c && !vis[w[a][i]] && w[a][i] != v) 
        	dfs(w[a][i], b + 1, c);
        else if(!c && !ans[w[a][i]] && w[a][i] != u) 
        	dfs(w[a][i], b + 1, c);
    }
}
int main(){
    IOS;
    cin >> n >> u >> v;
    for(int i = 1; i < n; i++)
    cin >> x >> y, w[x].push_back(y), w[y].push_back(x);
    dfs(v, 0, 1), dfs(u, 0, 0); 
    for(int i = 1; i <= n; i++)  
    if(vis[i] > ans[i])
        m = max(m, vis[i]);
    printf("%d", m - 1);
    return 0;
} 
```


---

## 作者：PCCP (赞：0)

## 思路

我们称 T 为猎物，A 为猎手。以猎手所在的点为根，固定树的形态，我们发现猎物只能向上或向下走。以普遍理性而言，向下走只会被步步紧逼走进死胡同缩小自己的活动范围。猎物不如向上走到最后一个在自己下一步移动前不会被抓的祖先节点，这样可以大大增加自己的活动空间，然后极限拉扯向最长的子链逃跑。

分情况讨论，如果猎物和猎手间的距离为 $ 1 $，那向上移动完两人间距离为奇数，向下逃跑到叶子节点时，猎物无处可去只能送货上门，而猎手无需多走；如果距离为偶数，那向上移动完两人间距离为 $ 2 $，向下逃跑到叶子节点时，猎物往上走，猎手也需要往下一步才能够着。

## 证明

为什么这样构造博弈方法是对的呢？可以发现，无论如何移动，树上两点间距离的变化情况只可能是 $ +2 $、$ 0 $、$ -2 $，而猎手想要尽快结束不可能会让距离加二，所以距离只可能越来越小。距离减少到相遇的步数是固定的，只能想方设法延长距离不变的步数。因为猎手决策是只会向下走，想要距离不变猎物就只能向下走。所以向上走到深度浅的地方，使得向下走的路径更长显然更优。

## 实现

就是按上面说的方法分讨一下，然后求个树上 $ K $ 级祖先，最后求子树最大深度即可，我用的树剖，其实可以直接暴力跳还更快。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<list>
#include<set>
using namespace std;
const int N=1e5+10;
const int MOD=1e9+7;
int n,s,t,ans;
int he[N],ne[N<<1],to[N<<1],tot=1;
void addedge(int x,int y){
	to[++tot]=y;
	ne[tot]=he[x];
	he[x]=tot;
}
int fa[N],son[N],siz[N],top[N],dep[N],dfo[N],seq[N],cnt;
void dfs1(int x,int f){
	dep[x]=dep[f]+1;
	fa[x]=f;
	for(int i=he[x];i;i=ne[i]){
		int v=to[i];
		if(v==fa[x]){
			continue;
		}
		dfs1(v,x);
		siz[x]+=siz[v];
		if(siz[v]>siz[son[x]]){
			son[x]=v;
		}
	}
}
void dfs2(int x,int t){
	dfo[x]=++cnt,top[x]=t,seq[cnt]=x;
	if(son[x]){
		dfs2(son[x],t);
	}
	for(int i=he[x];i;i=ne[i]){
		int v=to[i];
		if(v==son[x]||v==fa[x]){
			continue;
		}
		dfs2(v,v);
	}
}
int query(int x,int k){
	while(dep[x]-dep[top[x]]<k){
		k-=dep[x]-dep[top[x]]+1;
		x=fa[top[x]];
	}
	return seq[dfo[x]-k];
}
int dfs3(int x){
	int res=dep[x];
	for(int i=he[x];i;i=ne[i]){
		int v=to[i];
		if(v==fa[x]){
			continue;
		}
		res=max(res,dfs3(v));
	}
	return res;
}
int main(){
//	freopen("same.in","r",stdin);
//	freopen("same.out","w",stdout);
	scanf("%d%d%d",&n,&s,&t);
	int x,y;
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		addedge(x,y);
		addedge(y,x);
	}
	if(s==t){
		puts("0");
		exit(0);
	}
	dfs1(t,0);
	dfs2(t,t);
	int rt=query(s,(dep[s]-2)>>1);
	ans+=((dep[s]-2)>>1);
	int dist=((dep[s]-1)&1)?(1):(2);
	int lst=dfs3(rt)-dep[rt];
	ans+=lst;
	if(dist==2){
		++ans;
	}
	printf("%d\n",ans);
}
```

---

## 作者：StevenLiTheOIer (赞：0)

## 思路：
因为我们要站在两个玩家的角度想问题，所以先通过两遍 dfs 求出每个点相对于两个人的最短距离 $dist1_i$ 和 $dist2_i$。然后开始贪心：如果 $dist1_i<dist2_i$，那么逃跑的人被追上至少要走 $dist2_i-1$ 步；而如果两个人同时到达，那么走了 $dist1_i$ 同时也是 $dist2_i$ 步。对每个点用上述两种方式更新答案，求最大值即可。
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int dist1[100006], dist2[100006];
vector <int> e[100006];
void dfs1(int now, int fa)
{
	dist1[now] = dist1[fa] + 1;
	for (int i = 0; i < e[now].size(); i++)
	{
		int to = e[now][i];
		if (to != fa) dfs1(to, now);
	}
}
void dfs2(int now, int fa)
{
	dist2[now] = dist2[fa] + 1;
	for (int i = 0; i < e[now].size(); i++)
	{
		int to = e[now][i];
		if (to != fa) dfs2(to, now);
	}
}
int main()
{
	int n, u, v;
	cin >> n >> u >> v;
	for (int i = 1; i <= n - 1; i++)
	{
		int x, y;
		cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dist1[0] = dist2[0] = -1;
	dfs1(u, 0);
	dfs2(v, 0);
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (dist1[i] < dist2[i]) ans = max(ans, dist2[i] - 1);
		else if (dist1[i] == dist2[i]) ans = max(ans, dist1[i] / 2);
	}
	cout << ans << endl;
	return 0;
}
```

---

