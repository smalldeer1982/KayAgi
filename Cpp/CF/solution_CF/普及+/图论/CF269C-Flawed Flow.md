# Flawed Flow

## 题目描述

Emuskald considers himself a master of flow algorithms. Now he has completed his most ingenious program yet — it calculates the maximum flow in an undirected graph. The graph consists of $ n $ vertices and $ m $ edges. Vertices are numbered from 1 to $ n $ . Vertices $ 1 $ and $ n $ being the source and the sink respectively.

However, his max-flow algorithm seems to have a little flaw — it only finds the flow volume for each edge, but not its direction. Help him find for each edge the direction of the flow through this edges. Note, that the resulting flow should be correct maximum flow.

More formally. You are given an undirected graph. For each it's undirected edge ( $ a_{i} $ , $ b_{i} $ ) you are given the flow volume $ c_{i} $ . You should direct all edges in such way that the following conditions hold:

1. for each vertex $ v $ $ (1&lt;v&lt;n) $ , sum of $ c_{i} $ of incoming edges is equal to the sum of $ c_{i} $ of outcoming edges;
2. vertex with number $ 1 $ has no incoming edges;
3. the obtained directed graph does not have cycles.

## 说明/提示

In the first test case, 10 flow units pass through path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269C/112cc3d7bc5d5ae260d516a02ced6ab796839bee.png), and 5 flow units pass directly from source to sink: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269C/851f40f264708d94590f3171217fe3d9e053dcee.png).

## 样例 #1

### 输入

```
3 3
3 2 10
1 2 10
3 1 5
```

### 输出

```
1
0
1
```

## 样例 #2

### 输入

```
4 5
1 2 10
1 3 10
2 3 5
4 2 15
3 4 5
```

### 输出

```
0
0
1
1
0
```

# 题解

## 作者：灵茶山艾府 (赞：5)

对于非源非汇的点，其入流为其所有边的流量之和的一半。由于题目要求生成的图是一个 DAG，我们完全可以套用拓扑排序的思想，把入流当做入度，跑一遍 BFS 即可得到各个边的方向。

AC 代码 (Golang)：

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n, m, v, w, c int
	Fscan(in, &n, &m)
	type edge struct{ to, i, d, f int }
	g := make([][]edge, n+1)
	f := make([]int, n+1)
	for i := 0; i < m; i++ {
		Fscan(in, &v, &w, &c)
		g[v] = append(g[v], edge{w, i, 0, c})
		g[w] = append(g[w], edge{v, i, 1, c})
		f[v] += c
		f[w] += c
	}
	for i := range f {
		f[i] >>= 1
	}

	ans := make([]int, m)
	for i := range ans {
		ans[i] = -1
	}
	q := []int{1}
	for len(q) > 0 {
		v := q[0]
		q = q[1:]
		for _, e := range g[v] {
			if ans[e.i] == -1 {
				ans[e.i] = e.d
				w := e.to
				f[w] -= e.f
				if w != n && f[w] == 0 {
					q = append(q, w)
				}
			}
		}
	}
	for _, d := range ans {
		Fprintln(out, d)
	}
}
```



---

## 作者：OIer_ACMer (赞：1)

~~网络流什么时候水成绿题了？！~~。

------------
这道题刚刚拿到的时候~~一脸懵逼~~，看到了绿色的标识就觉得自己行了，但是仔细读完题目后，不仅觉得这道题很有意义，而且——太难了（建议升蓝或紫）。同时，此题部分思路借鉴[大佬博客](https://blog.csdn.net/qq_43549984/article/details/95786408?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169192197816800188548017%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169192197816800188548017&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-95786408-null-null.142^v92^insert_down28v1&utm_term=Codeforces%20269C%20Flawed%20Flow&spm=1018.2226.3001.4187)。

------------
## 大致思路：
题目大意为：“给定一个 $n$ 顶带权无向图，指定 $1$ 和 $n$ 分别为源点和汇点，请你根据流量守恒原则（除源点和汇点外流入等于流出）确定每条边的方向。”说实话，这种题面已经很让人头晕了。但是不慌，慢慢来。想要求出方向，那么就**先预处理好两条边，分别代表两种方向**，由于题目要求要保证**一个点的出流量与入流量相等**，那么之后想要平衡某结点的流量，则在此基础上减去一个二倍的边权，相当于是正号变负号。则结点 $i$ 就流量守恒~~为零了嘛~~。

接着，我们就从出发点向着汇聚点广搜，用队列将那些~~不受管教~~不平衡的点进行维护，维护的方法**用一条预处理好的边去进行平衡，同时，将这个边的反向边去除，并将反向边边定为 false，因为我们没有用**。最后，将得到的结果存入 $dirc$ 数组中。

------------
## 具体步骤：
1. 输入数据，建边，还要预处理出这条边的正反方向，同时储存各个节点一开始的流量，用 $liuliang$ 数组存储。

2. bfs，通过队列维护各个点的信息，县全部减去二倍边权，并进行平衡操作，还要将点的 $vis$ 数组赋值为 true，反向边的 $flag$ 标记赋值为 false，将得到的结果存入 $dirc$ 数组中，此外，如果这条边已经确定方向，则不用做别的操作~~懂的都懂~~。



------------
## 代码如下：

```c++

#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int MAXN = 2e5 + 10;
struct Edge
{
    int id, to, next, w;
    bool d, flag;
} edge[MAXN << 1];
int tot;
int head[MAXN << 1];
void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
}
void add(int id, int u, int v, int w)
{
    edge[tot] = (Edge){id, v, head[u], w, 0, 1};
    head[u] = tot++;
    edge[tot] = (Edge){id, u, head[v], w, 1, 1};
    head[v] = tot++;
}
bool vis[MAXN], dirc[MAXN];
int liuliang[MAXN];
int n, m, a, b, c;
void bfs()
{
    queue<int> q;
    q.push(1);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = true;
        for (int i = head[u]; ~i; i = edge[i].next)
        {
            Edge e = edge[i];
            if (!e.flag)
            {
                continue;
            }
            int v = e.to;
            if (vis[v])
            {
                continue;
            }
            liuliang[v] -= 2 * e.w; // 将流量减去二倍
            dirc[e.id] = e.d;
            edge[i ^ 1].flag = false;
            if (!liuliang[v] && v != n)
            {
                q.push(v);
            }
        }
    }
}
int main()
{
    init();
    n = read();
    m = read();
    for (int i = 0; i < m; i++)
    {
        a = read();
        b = read();
        c = read();
        add(i, a, b, c);
        liuliang[a] += c;
        liuliang[b] += c; // 储存各点流量
    }
    bfs();
    for (int i = 0; i < m; i++)
    {
        cout << dirc[i] << '\n';
    }
    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/120699874)

---

## 作者：Graph_Theory (赞：0)

蒟蒻没学过网络流，于是去现学了一下，发现这道题好像只套了个概念，~~好像更加不会了。~~

### 题意

给一个 $n$ 个点，有 $m$ 条边的无向图，你需要规定每一条边的方向使得除 $1$ 与 $n$ 号点之外的所有点的入度边边权等于出度边边权，且不形成环，同时 $1$ 与 $n$ 号点只存在入度或出度。

### 思路

对于除 $1$ 与 $n$ 号点之外的所有点，由于入度边边权等于出度边边权，所以他们出度与入度就是他们连接所有边边权的总和的一半，记为 $flow_i$ 表示。

不难发现根节点连接的所有点中至少有一个点**已知**的入边的数量达到了 $flow_i$ 其余都是出边。原因是若不存在，此时任何边任何的方向都会形成环，但题目中保证了有解，所以成立。

进一步讲，我们最终的图里没有环，且有解，所以我们一定可以拓扑排序，此时由于存在拓扑序，即存在**明确的**父亲儿子关系，可以说明上面正确。

所以我们可以使用广搜从一号点往 $n$ 号点搜，若某一个点实现平衡，则加入队列，此时该点之外的所有点计算，以此类推，若某一个点**已知**的入边的数量达到了 $flow_i$ 时，加入队列，对于其儿子节点 $flow_j-\operatorname{length}(i,j)$ 以此类推，按广搜访问顺序去记录答案。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define maxn 200005
using namespace std;

struct node{int to,length,ref;};
int n,m,flow[maxn],ans[maxn];
vector<node> e[maxn];
queue<int> q;

void _add_(int u,int v,int w,int i)
{
	node a,b;
	a.to=v,a.length=w,a.ref=i;
	b.to=u,b.length=w,b.ref=i+m;
	e[u].push_back(a);
	e[v].push_back(b);
	flow[u]+=w,flow[v]+=w;
}

void add_ans(int x)
{
	if(x>m)	      ans[x-m]=1;	
	else if(x<=m) ans[x]=0;
}

signed main()
{
	cin>>n>>m;
	for (int i=1; i<=m; i++){
		int u,v,w;
		cin>>u>>v>>w;
		_add_(u,v,w,i);
	}
	flow[1]=0;
	for (int i=2; i<=n-1; i++) flow[i]/=2;
	q.push(1);
	while (!q.empty())
	{
		int x=q.front(); 
		q.pop();
		int x_size=e[x].size();
		for(int i=0;i<x_size;i++)
		{
			int to=e[x][i].to,length=e[x][i].length,ref=e[x][i].ref;
			if (flow[to]==0) continue;
			add_ans(ref);		
			flow[to]-=length;
			if(flow[to]==0)	q.push(to);
		}
	}
	for (int i=1;i<=m;i++) cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：SFlyer (赞：0)

比较重要的几点是：

- 你可以确定原点都是出去的。

- 如果你确定了所有的进来的，其他的一定是出去的。

我们发现我们在处理完原点以后，一定有至少一个点进来的部分已经算好了（否则就没有拓扑排序第二个，会有环），因此我们又可以确定这个点的所有情况。

以此类推，我们可以保证每一次都会存在这样的点。用拓扑排序即可。注意 $n=2$ 的情况。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e5+5;

struct node {
	int t,c,id;
};

int n,m,deg[N],ans[N];
vector<node> g[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>m;
	for (int i=1; i<=m; i++){
		int a,b,c;
		cin>>a>>b>>c;
		g[a].push_back({b,c,i});
		g[b].push_back({a,c,i+m});
		deg[a]+=c;
		deg[b]+=c;
	}
	for (int i=1; i<=n-1; i++){
		deg[i]/=2;
	}
	deg[1]=0;
	queue<int> q;
	q.push(1);
	while (!q.empty()){
		int x=q.front();
		q.pop();
		for (auto p : g[x]){
			int y=p.t,c=p.c,id=p.id;
			if (deg[y]==0){
				continue;
			}
			ans[(id>m?(id-m):id)]=(id>m);
			deg[y]-=c;
			if (deg[y]==0){
				q.push(y);
			}
		}
	}
	for (int i=1; i<=m; i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

我们记数组 $f_i$ 表示点 $i$ 的流量。那么当且仅当 $f_i=0$ 时该点的收支平衡。源点和汇点的收支我们不管。

那么我们首先可以确定的就是源点出去的边的方向。

我们先假设地把每个 $f_i$ 设置为与 $i$ 相连的所有边的权值和（权值就是该边的流量），那么假设我们要把i的一条边改成出边，我们就把 $f_i$ 减去两倍的其边权即可。

我们使用 bfs，先把源点加入。每一次从队列中取出一个点 $u$，这个点是满足收支平衡的。我们扫描 $u$ 的邻点 $v$ （跳过已经收支平衡的点），边为 $e$，边权为 $w_e$，如果发现 $f_v≠0$，那么就把 $f_v$ 减去 $2\times w_e$ 并且标记边 $e$ 的方向且标记 $e$ 已经确定了方向，下次访问时就跳过。这样做是标记边 $e$ 从 $v→u$。注意，这样操作是不会影响到 $f_u$ 的，因为原来我们的 $f_u,f_v$ 都加了 $2\times w_e$，我们把其中一个点（如 $v$）减去 $2\times w_e$ 就相当于一个点出一个点入，恰好人这条边合法了。如果在操作后我们发现 $v$ 的收支平衡了，就加入队列并标记。

因为最后的图中无环、且每条边都被分配了方向，因此是 DAG，可用拓扑排序解决，所以上述的 bfs 是可以求得最终的答案的。

---

```C++

    q.push(1);
    while (!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=true;
        for (int i=h[u];~i;i=e[i].nxt){
            edge E=e[i];
            if (!E.used) continue;
            int v=E.to;
            if (vis[v]) continue;
            flow[v]-=2*E.w;
            ans[E.id]=E.d;
            e[i^1].used=false;
            if (!flow[v]&&v!=n)q.push(v);
        }
    }

```




---

