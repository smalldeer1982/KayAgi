# [USACO20FEB] Timeline G

## 题目描述

Bessie 在过去的 $M$ 天内参加了 $N$ 次挤奶。但她已经忘了她每次挤奶是在哪个时候了。

对于第 $i$ 次挤奶，Bessie 记得它不早于第 $S_i$ 天进行。另外，她还有 $C$ 条记忆，每条记忆形如一个三元组 $(a,b,x)$，含义是第 $b$ 次挤奶在第 $a$ 次挤奶结束至少 $x$ 天后进行。

现在请你帮 Bessie 算出在满足所有条件的前提下，每次挤奶的最早日期。

保证 Bessie 的记忆没有错误，这意味着一定存在一种合法的方案，使得：

- 第 $i$ 次挤奶不早于第 $S_i$ 天进行，且不晚于第 $M$ 天进行；
- 所有的记忆都得到满足；

## 说明/提示

- 测试点 $2 \sim 4$ 满足 $N,C \leq 10^3$。
- 测试点 $5 \sim 10$ 没有特殊限制。

## 样例 #1

### 输入

```
4 10 3
1 2 3 4
1 2 5
2 4 2
3 4 4```

### 输出

```
1
6
3
8```

# 题解

## 作者：StudyingFather (赞：37)

对于每个三元组 $(a,b,x)$，从 $a$ 向 $b$ 连一条长度为 $x$ 的边。同时新建一个超级源点 $0$，从 $0$ 向 $i$ 连长度为 $S_i$ 的边。

容易发现这张图是一个 DAG。

直接拓扑排序递推计算即可。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
struct edge
{
 int v,w,next;
}e[100005];
int s[100005],t[100005],head[100005],cnt;
queue<int> q;
void addedge(int u,int v,int w)
{
 e[++cnt].v=v;
 e[cnt].w=w;
 e[cnt].next=head[u];
 head[u]=cnt;
}
int main()
{
 freopen("timeline.in","r",stdin);
 freopen("timeline.out","w",stdout);
 ios::sync_with_stdio(false);
 int n,m,c;
 cin>>n>>m>>c;
 for(int i=1;i<=n;i++)
  cin>>s[i];
 for(int i=1;i<=c;i++)
 {
  int u,v,w;
  cin>>u>>v>>w;
  addedge(u,v,w);
  t[v]++;
 }
 for(int i=1;i<=n;i++)
  if(!t[i])q.push(i);
 while(!q.empty())
 {
  int u=q.front();
  q.pop();
  for(int i=head[u];i;i=e[i].next)
  {
   int v=e[i].v,w=e[i].w;
   s[v]=max(s[v],s[u]+w);
   t[v]--;
   if(!t[v])q.push(v);
  }
 }
 for(int i=1;i<=n;i++)
  cout<<s[i]<<endl;
 return 0;
}
```

---

## 作者：一只书虫仔 (赞：21)

#### Description

> [P6145](https://www.luogu.com.cn/problem/P6145)    
> 给定一些如下的不等式，求任意一组不等式的解。
> $$t_i -t_j \ge b$$

#### Solution

差分约束裸题。

首先我们分析差分约束的本来的式子：

$$t_i-t_j \le b$$

左边的这个 $t_i-t_j$ 就是差分。

我们首先把这个不等式化简一下，成 $t_i\le t_j+b$。

假设 $t_j$ 已知，我们可以推出 $t_i$ 的最大值只可能是 $t_j+b$，最小不限。

那我们再次假设如果 $t_i$ 跟 $t_{j'}$，$t_{j''}$，$t_{j'''}$ 都有关，我们就可以得到三个不等式，即一个不等式组

$$\begin{cases}t_i\le t_{j'}+b\\t_i\le t_{j''}+b\\t_i\le t_{j'''}+b\end{cases}$$

那么 $t_i$ 满足所有不等式下的最大值应该是 $\min\{t_{j'}+b,t_{j''}+b,t_{j'''}+b\}$。

因为要满足所有不等式，所以必须要取最小值来满足所有的不等式。

注意，我们上面提到的 $j$ 都可以模拟成 $i$ 的 **前继**。

那么我们可以再次简化模型。

假设有多个 $t_j$ 是 $t_i$ 的前继，那么我们就可以得到一个递推式。

$$t_i=\min\{t_j+b\}$$

那么我们看一下 SPFA 的递推式。

$$dist_i=\min\{dist_j+<i,j>\}$$

好了，破案了。

那么我们只需要找一个超级原点 $\rm super$，然后使得他连到 $i$ 的长度是 $t_i$ 即可。

最后我们求一个最短路即可，输出每个 $dist_i$。

最后无解的情况只需要判断一下负环即可。

那么我们看过了 $t_j-t_i \le b$，那么我们怎么转化成这一题呢？

还是用上面的思路，就可以得到
$$t_j \ge t_i+b$$

然后就可以转化成上面推导的模型就可以了吧 …… 注意 $\ge$ 和 $\le$ 的性质不同，注意最大值和最小值。

这题貌似没有判负环的地方，开心 /cy

注意在执行差分约束造超级原点的时候长度要造为 $S_i$。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

struct node {
	int val, next, len;
} e[1000086];

int n, m, c;
int cnt;
int head[1000086];
int dist[1000086];
int sum[1000086];
int vis[1000086];
int S[1000086];
const int inf = 0x3f3f3f3f;

void AddEdge (int u, int v, int w) {
	e[++cnt].val = v;
    e[cnt].next = head[u];
    e[cnt].len = w;
    head[u] = cnt;
}

bool SPFA () {
	queue <int> q;
	int s = 0;
	for (int i = 1; i <= n; i++)
		dist[i] = -inf;
	dist[s] = 0;
	sum[s] = 1;
	vis[s]++;
	q.push(s);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		sum[cur] = 0;
		for (int p = head[cur]; p > 0; p = e[p].next)
			if (dist[e[p].val] < dist[cur] + e[p].len) {
				dist[e[p].val] = dist[cur] + e[p].len;
				vis[e[p].val]++;
				if (vis[e[p].val] >= n + 1)
					return true;
				if (!sum[e[p].val]) {
					q.push(e[p].val);
					sum[e[p].val] = 1;
				}
			}
	}
	return false;
}

int main () {
	scanf("%d%d%d", &n, &m, &c);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &S[i]);
		AddEdge(0, i, S[i]);
	}
	for (int i = 1, u, v, w; i <= c; i++) {
		scanf("%d%d%d", &u, &v, &w);
		AddEdge(u, v, w);
	}
	bool hahaha = SPFA();
	for (int i = 1; i <= n; i++)
		printf("%d\n", dist[i]);
	return 0;
}

```

By Shuchong    
2020.7.14

---

## 作者：Hexarhy (赞：8)

一道玩了点文字花样的基础图论题。

-------

### 解题思路

**前置知识：**[拓扑排序](https://www.luogu.com.cn/blog/80049/kuai-su-ru-shou-ta-pu-pai-xu)。

首先看到题目，当然要明白它究竟想要干什么。

题目描述的方式很像一个 DAG，于是把每次挤奶看做一个节点，每次挤奶的间隔天数 $x$ 当做边权，从 $a$ 到 $b$ 连边。

至于 $S_i$，可以看做是第 $0$ 次挤奶后，间隔 $S_i$ 天后，再进行后面的挤奶。

实际建图中我们无需新建 $0$ 号节点，因为我们直接用 $S_i$ 递推就行，相当于已经遍历过这些边。

然后根据题意，不难得到一个节点的 $S_i$ 只能由它的前驱或者节点 $0$ 得到。后者其实就是输入时的 $S_i$。

题目要求的是“最早”，实际上要同时满足两个限制（分别为输入时的 $S_i$ 和三元组），我们只能选日期更后的，并为了使其最小，就让它刚好等于那个更后的日期。显然，递推式为：

$$S_i=\max\{S_i,S_{pre}+v\}$$

其中 $pre$ 是 $i$ 的前驱节点，$v$ 是连接这两个点的边权。

用拓扑排序求出前驱节点并递推即可。

### 参考代码

本题并无坑点，放心做就行。~~除非你用邻接矩阵存图我也没办法~~

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN=1e6+5;
int n,m,c;
struct node
{
	int to,v;
};
vector<node> edge[MAXN];
int indeg[MAXN],ans[MAXN],s[MAXN];
bool visit[MAXN];

void input(void)
{
	cin>>n>>m>>c;
	for(int i=1;i<=n;i++)
	 cin>>s[i];
	for(int i=1;i<=c;i++)
	{
		int a,b,x;
		cin>>a>>b>>x;
		edge[a].push_back(node{b,x});
		indeg[b]++;//统计入度
	}
}

void topo_sort(void)//模板
{
	queue <int> q;
	for(int i=1;i<=n;i++)
	 if(!indeg[i])
	  q.push(i);
	while(!q.empty())
	{
		const int t=q.front();
		q.pop();
		if(visit[t])
		 continue;
		visit[t]=true;
		for(auto it:edge[t])
		{
			s[it.to]=max(s[it.to],s[t]+it.v);//递推
			indeg[it.to]--;
			if(!indeg[it.to])
			 q.push(it.to);
		}
	}
}

void output(void)
{
	for(int i=1;i<=n;i++)
	 cout<<s[i]<<endl;
}

int main()
{
	input();
	topo_sort();
	output();
	return 0;
}
```

---

## 作者：UltiMadow (赞：6)

这是一个SPFA复活的故事

这也算是一个暴力碾表算的故事

我们珂爱的SPFA居然过题了！！！

这是一个差分约束裸题，如果不会的话可以看看我的[这篇博客](https://sflsrick.blog.luogu.org/ci-fen-yue-shu-xue-xi-bi-ji)

由于良心出题人没有卡SPFA，于是我们就过掉了这题

看代码吧：
```cpp
#include<bits/stdc++.h>
#define MAXN 100010
using namespace std;
int n,m,C;
struct Node
{
	int to,next,val;
}Edge[MAXN<<1];
int Head[MAXN],cnt_Edge;
void Add_Edge(int u,int v,int w)
{
	Edge[++cnt_Edge].to=v;
	Edge[cnt_Edge].next=Head[u];
	Edge[cnt_Edge].val=w;
	Head[u]=cnt_Edge;
}
int dis[MAXN];bool inq[MAXN];
void SPFA(int st)//SPFA最长路
{
	queue<int>Q;
	memset(dis,-0x3f,sizeof(dis));
	memset(inq,false,sizeof(inq));
	Q.push(st);dis[st]=0;inq[st]=true;
	while(!Q.empty())//题目保证有解，所以不用判正环
	{
		int u=Q.front();Q.pop();inq[u]=false;
		for(int i=Head[u];i;i=Edge[i].next)
		{
			int v=Edge[i].to,w=Edge[i].val;
			if(dis[v]<dis[u]+w)
			{
				dis[v]=dis[u]+w;
				if(!inq[v])Q.push(v),inq[v]=true;
			}
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&C);
	for(int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);
		Add_Edge(0,i,x);//超级源点到每个点建边
	}
	while(C--)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);
	}
	SPFA(0);printf("%d",dis[1]);
	for(int i=2;i<=n;i++)printf("\n%d",dis[i]);
	return 0;
}
```

---

## 作者：king_xbz (赞：5)

这道题总的来说是一道非常基础的**拓扑排序**。下面说一下基本思路：

我们先将每个三元组$ (a,b,x)$存入**有向无环图**，并记录他的**出入度**。然后使用**STL中的queue**，每次让**入度为0**的点进队，然后遍历与之相邻的节点并随时**更新挤奶的最早日期**及该节点入度，然后再让**入度为0**的点进队......以此类推。~~注意：建图请使用vector或链式前向星而不是邻接矩阵。~~

接下来是代码的主体部分：

首先是建图（这里采用链式前向星）
```cpp
struct node
{
	int to;
	int next;
	int val;
}
e[p];
int head[p];
int cnt;
inline void adds(int u,int v,int x)
{
	e[++cnt].to=v;
	e[cnt].next=head[u];
	e[cnt].val=x;
	head[u]=cnt;
	return ;
}
```
然后进行拓扑排序
```cpp
for(fint i=1;i<=c;i++)
  a=read(),b=read(),s=read(),adds(a,b,s),ou[a]++,in[b]++;//存图和度
  for(fint i=1;i<=n;i++)
  if(!in[i])
  q.push(i);//入度为0就入队
  while(!q.empty())
  {
    int tops=q.front();//取队首
    q.pop();
    for(fint i=head[tops];i;i=e[i].next)
    {
    	 ans[e[i].to]=max(ans[e[i].to],ans[tops]+e[i].val),in[e[i].to]--;
       //（本人不喜欢在for里换行）更新挤奶日期及入度
    	 if(!in[e[i].to])
    	 q.push(e[i].to);	
       //接着入队
		}
	}
	for(fint i=1;i<=n;i++)
	printf("%d\n",ans[i]);//输出
```
那么这道题就结束了，还有不懂的可以[点我拿完整代码](https://www.luogu.com.cn/paste/7le43wtf)或者评论区解决。

最后祝大家AC愉快！

---

## 作者：gznpp (赞：4)

拓扑排序做法肥肠妙，考场上没想到差分约束建出来的图是个 DAG，于是只好按部就班写 SPFA 并寄望出题人高抬贵手……最后过了。感谢出题人不杀之恩。

---------------

差分约束不会的看这里：<https://oi-wiki.org/graph/diff-constraints/>

SPFA 不会的看这里：<https://oi-wiki.org/graph/shortest-path/#spfa>

那么，第 $i$ 号挤奶至少在第 $k$ 天之后发生可以视为 $x_i - x_0 \ge k$；第 $b$ 号挤奶至少在第 $a$ 号挤奶后 $t$ 天之后可以视为 $x_b - x_a \ge t$。

如果我们移项，大于号转小于号，有 $x_a - x_b \le -t, x_0 - x_i \le -k$。如果你这么连边，你会发现 $0$ 号点没有出边。

怎么办？

不移项，改跑最长路。最长路满足这样的三角不等式：$dis_{i, j} \ge dis_{i, k} + dis_{k, j}$。这样就可以转换成 $0$ 向 $i$ 连边，$a$ 向 $b$ 连边。最长路的跑法就是把边权全部取反之后跑最短路，最后输出距离时再次取反。

很容易写出代码，如下：
```cpp
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 1e5 + 5, maxm = 2e5 + 5;
int n, m, c, indx, dis[maxn];
int u[maxm], v[maxm], w[maxm], fst[maxn], nxt[maxm];
bool book[maxn];
queue<int> que;

inline void addedge(int p, int q, int r) {
    u[++indx] = p, v[indx] = q, w[indx] = r;
    nxt[indx] = fst[u[indx]];
    fst[u[indx]] = indx;
}
signed main() {
    scanf("%d %d %d", &n, &m, &c);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        addedge(0, i, -x);
    }
    for (int i = 1; i <= c; ++i) {
        int a, b, x;
        scanf("%d %d %d", &a, &b, &x);
        addedge(a, b, -x);
    }
    // SPFA
    memset(dis, 0x3f, sizeof(dis));
    dis[0] = 0, book[0] = 1;
    que.push(0);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        book[x] = 0;
        for (int i = fst[x]; i; i = nxt[i]) {
            int y = v[i];
            if (dis[y] > dis[x] + w[i]) {
                dis[y] = dis[x] + w[i];
                if (!book[y]) que.push(y), book[y] = 1;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        printf("%d\n", -dis[i]);
    return 0;
}
```

---

## 作者：sukimo (赞：3)

思路：拓扑排序+递推。把每一次挤奶的时间抽象为点，时间差关系抽象为有向边，就得到了一个DAG。对此DAG拓扑排序，每一次删点时尝试更新与该点相连的点的最早时间，由于要满足所有情况且最小，所以要用max比较。思路还是很经典的。

代码献上：

```
#include<bits/stdc++.h>
using namespace std;
const int MX=100005;int dp[MX],fir[MX],in_cnt[MX];queue<int>q;struct STR{int val,next,to;}edge[MX];
void add(int u,int v,int x,int cnt){
	in_cnt[v]++;edge[cnt].val=x;edge[cnt].to=v;edge[cnt].next=fir[u];fir[u]=cnt;
}
int main(){
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)scanf("%d",&dp[i]);
	for(int i=1;i<=k;i++){
		int u,v,x;scanf("%d%d%d",&u,&v,&x);add(u,v,x,i);
	}
	for(int i=1;i<=n;i++)if(!in_cnt[i])q.push(i);
	while(!q.empty()){
		int fr=q.front();
		for(int i=fir[fr];i;i=edge[i].next){
			if(!--in_cnt[edge[i].to])q.push(edge[i].to);dp[edge[i].to]=max(dp[edge[i].to],dp[fr]+edge[i].val);
		}
		q.pop();
	}
	for(int i=1;i<=n;i++)printf("%d\n",dp[i]);
	return 0;
}
```


---

## 作者：pocafup (赞：3)

抢第一篇题解

这题思路主要是有些点必然在另外的点后执行.所以,我们可以做一个数组记录哪些点可以动(也就是没有点需要在他之前动).

在这个点动了之后,我们就将所有他所对应的点更新(也就是将那个点的限制条件-1).然后我们判断那个点的限制条件是否为0.如果为0,我们将其加入队列

每个点的最早动的时间就是他自己能动的最早值和每个在他之前动的点加上他俩距离的最大值

```cpp
for (pp v : adj[qf]){
      constrain[v.f]--;//限制条件--
      pos[v.f] = max(pos[v.f],pos[qf]+v.s);//他自己本身的时间和在他前面动的点和他的时间差的最大值
      if (constrain[v.f]==0) q.push(v.f);//如果没有限制条件了
    }
```
为什么正确:

这个应该是dp的核心思想.如果某个点的所有有关联的数字都已经有了确定的值,那么这时候动这个点就100%是最小答案

完整代码:

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define pp pair<int,int>
#define f first
#define s second
int n,m,k;
int pos[100005];
vector<pp> adj[100005];
bool vis[100005];
int constrain[100005];
queue<int> q;
void setIO(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
	ios_base::sync_with_stdio(0);
}

int main(){
  // setIO("timeline");
  cin>> n >>m >> k;
  for (int i=1;i<=n;i++) cin >> pos[i];
  for (int i=0;i<k;i++){
    int a,b,c; cin >> a >> b >> c;
    adj[a].push_back(make_pair(b,c));
    constrain[b]++;//要去的点的限制条件+1(因为假设a没去,我们不能判断b最早能动的时间)
  }
  for (int i=1;i<=n;i++) if (constrain[i]==0) q.push(i);//将所有没有限制条件的点放入队列
  while(!q.empty()){
    int qf = q.front();q.pop();
    for (pp v : adj[qf]){
      constrain[v.f]--;
      pos[v.f] = max(pos[v.f],pos[qf]+v.s);
      if (constrain[v.f]==0) q.push(v.f);
    }
  }
  for (int i=1;i<=n;i++) cout << pos[i] << endl;//输出答案
}

```


---

## 作者：45dino (赞：2)

~~在金组还能看到绿题好鸡冻~~

一开始的想法：先定初值$(s)$，对于每一条记忆$(a,b,x)$,修改s[b];

问题：
1. 会TLE
1. 如果有三次挤奶：a,b,c;

第一条记忆是关于b,c的，调c；

第二条记忆是关于a,b的，调b；

这时，会惊奇地发现：b,c之间又要再调一次；

可以想到，如果通过某种顺序排列这些记忆，使得没有矛盾（在这里是把1，2两条记忆调换）就可以圆满地解决问题，时间复杂度约为$O(C)$;

很快就能想到应该用$(a,b,x)$中b来排序：如果该次挤奶没有出现在b的位置上，应该先考虑。就把问题转化为[拓扑排序](https://blog.csdn.net/qq_41713256/article/details/80805338)。经过一点优化，问题就圆满解决了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,c,cnt,a[100001],in[100001],head[100001];
bool vis[100001];
queue<int> q;
struct day{
	int to;
	int next;
	int val;
} mp[100001];
void add(int x,int y,int w)
{
	mp[++cnt].val=w;
	mp[cnt].to=y;
	mp[cnt].next=head[x];
	head[x]=cnt;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	cin>>n>>m>>c;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=c;i++)
	{
		int x,y,w;
		cin>>x>>y>>w;
		add(x,y,w);
		in[y]++;
	}
	for(int i=1;i<=n;i++)
  		if(!in[i])q.push(i);
	while(!q.empty())
	{
		int f=q.front();
		q.pop();
		for(int i=head[f];i;i=mp[i].next)
		{
			int v=mp[i].to;
			in[v]--;
			a[v]=max(a[v],a[f]+mp[i].val);
			if(!in[v])
				q.push(v);
		}
	}
	for(int i=1;i<=n;i++)
		cout<<a[i]<<endl;
	return 0;
}
```


---

## 作者：子翮 (赞：2)

### 前言
看到大佬们写的都是拓扑排序，我来说一说**差分约束**的做法吧

这题可以说是板子题了，只要您会差分约束，思考量几乎为 $ 0 $

### 具体实现

由于这道题要求的是每次挤奶的最早时间，考虑一个约束：

$$ B \geq A \ + \ w$$

那么我们就连一条从 $A$ 到 $B$ 边权为 $w$ 的边，至于第 $i$ 次挤奶不早于 $S_i$  天，我们可以看成：

$$i \geq 0 \ + \ S_i$$

建立一个超级源点 $0$ , 以此为起点跑一遍**最长路**即可（注意，要求的是最早的时间，所以跑最长路）

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#define R register
#define INF 0x3fffffff
#define MAXN 100010 
using namespace std;
struct edge
{
	int v,w;
	edge(int a,int b):v(a),w(b){}//构造函数
};
int n,m,c;
int d[MAXN],inq[MAXN];
vector<edge> adj[MAXN];
void spfa()
{
	queue<int> q;
	for(R int i=1;i<=n;i++)//初始化
		d[i]=-INF,inq[i]=0;
	d[0]=0;inq[0]=1;
	q.push(0);
	while(!q.empty())
	{
		int u=q.front();q.pop();inq[u]=0;
		for(R int i=0;i<adj[u].size();i++)
		{
			int v=adj[u][i].v;
			int w=adj[u][i].w;
			if(d[u]+w>d[v])//最长路
			{
				d[v]=d[u]+w;
				if(!inq[v])
				{
					q.push(v);
					inq[v]=1;
				}
			}
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&c);
	for(R int i=1;i<=n;i++)
	{
		int w;
		scanf("%d",&w);
		adj[0].push_back(edge(i,w));//超级源点
	}
	for(R int i=1;i<=c;i++)
	{
		int a,b,x;
		scanf("%d%d%d",&a,&b,&x);
		adj[a].push_back(edge(b,x));//约束
	}
	spfa();
	for(R int i=1;i<=n;i++)
		printf("%d\n",d[i]);
	return 0;
}


```


---

## 作者：_Fontainebleau_ (赞：0)

~~这道题貌似可以用**拓扑**做。~~

~~但是我不会。~~

于是就有了**差分约束**的做法。

不清楚差分约束的，建议去看看[这道模板题](https://www.luogu.com.cn/problem/P5960)，还有[这道](https://www.luogu.com.cn/problem/P1993)，都是差分约束的模板。



------------

好，我们假设您已经 $A$ 了上述两题（~~中的一题~~），那么，再看看这道题。

是不是觉得很水呢。

$1.$ 第 $i$ 次挤奶不早于 $S_i$ 天进行。那么就让它在第 $S_i$ 天进行。

$2.$ 第 $b$ 次挤奶在第 $a$ 次后至少 $x$ 天进行，那么就让它在后 $x$ 天进行。

要实现 $1.$ 的建图，需要建一个**超级源点** $s$ 。

因为题目保证有解（保证 Bessie 的记忆没有错误，这意味着**一定存在一种合法的方案**），所以可以放心的跑**最长路**，不用判断正环。

于是就是代码（队列是手写的）。


------------


```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
using namespace std;
int n,m,c,s,cnt;
int h[100010],t[200001],nxt[200001],val[200001];
int dis[100010];
bool inq[100010];
int f,e,q[100010001];
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}//快读
inline void addedge(int a,int b,int c)
{
	t[++cnt]=b,val[cnt]=c,nxt[cnt]=h[a],h[a]=cnt;
}
inline void spfa()
{
	while(f<=e)
	{
		int u=q[f++];
		for(int p=h[u];p;p=nxt[p])
		{
			int v=t[p];
			if(dis[v]<dis[u]+val[p])
			{
				dis[v]=dis[u]+val[p];
				if(!inq[v])	inq[v]=true,q[++e]=v;
			}
		}
		inq[u]=false;
	}
	return ;
}
int main()
{
	memset(dis,-1,sizeof(dis));
	n=read(),m=read(),c=read(),s=n+1;
	for(int i=1;i<=n;i++)
	{
		int x=read();
		addedge(s,i,x); //超级源点
	}
	for(int i=1;i<=c;i++)
	{
		int u=read(),v=read(),w=read();
		addedge(u,v,w);
	}
	dis[s]=0,f=e=1,q[1]=s,inq[s]=true;
	spfa();
	for(int i=1;i<=n;i++)
		printf("%d\n",dis[i]);
	return 0;
}

```
❀完结撒花❀

---

## 作者：那一条变阻器 (赞：0)

这道题难就难在建图吧，建图懂了之后，跑一遍最长路就好了（也就是关键路径，但是不会用拓补排序求qnq，wtcl）。

------------

怎么建图呢？先不管输入的S，看下面的输入，直接建有向边即可，权值为x。如果现在跑最长路的话，没有一个出发点，那是不行的，所以我们可以想到建一个点，去连接一下入度为0的点，边权为多少呢？这就跟S挂钩了，推下样例，很容易发现边权即为输入的S。这个点的其实就叫超级源点，是一个很重要的思想，在这种题里面建超级源点很常见，当然，还有超级汇点，就是把所有出度为0的点连向一个点，这道题还用不上。现在，我们就可以写下最长路啦（因为是最长路所以不能用迪杰斯特拉算法！！！）。

交上去，好，只有80分。为什么呢？

~~连输入的S都没用完你想得满分？~~当我们建超级源点时，只向入度为0的点连了边，那么可不可以给其他点连呢？答案是可以的。设$dis_i$为超级源点到i的最长路，那么一定有可能$dis_i$小于一开始给出的S，这时肯定选择S啊，所以我们可以把超级源点向其他的点连一条S的边，这样就把所有情况考虑完了。

满分代码~
```cpp
#include <bits/stdc++.h>
using namespace std;
int n , m , c , ans;
int dis[100010] , vis[100010];
vector<pair<int , int> > e[100010];
void spfa(int s){
	vis[s] = 1;	//最长路dis赋值为0 
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int x = q.front();
		q.pop();
		vis[x] = 0;
		for(int i = 0; i < e[x].size(); i++){
			int nx = e[x][i].first , w = e[x][i].second;
			if(dis[nx] < dis[x] + w){	//注意是最长路哦！！！ 
				dis[nx] = dis[x] + w;
				if(!vis[nx]){
					vis[nx] = 1;
					q.push(nx);
				}
			}
		}
	}
}
int main(){
	cin >> n >> m >> c;
	for(int i = 1; i <= n; i++){
		int x;
		cin >> x;
		e[0].push_back(make_pair(i , x));	//建超级源点 
	}
	for(int i = 1; i <= c; i++){
		int x , y , z;
		cin >> x >> y >> z;
		e[x].push_back(make_pair(y , z));
	}
	spfa(0);	//从超级源点开始跑，而不是1 
	for(int i = 1; i <= n; i++) cout << dis[i] << endl;
	return 0;
}
```

------------

双倍经验时间：

[P1113](https://www.luogu.com.cn/problem/P1113)

---

