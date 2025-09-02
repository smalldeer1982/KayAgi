# [ABC267E] Erasing Vertices 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc267/tasks/abc267_e

$ N $ 頂点 $ M $ 辺の単純無向グラフ（すなわち、自己辺も多重辺もない無向グラフ）が与えられます。$ i $ 本目の辺は頂点 $ U_i $ と頂点 $ V_i $ を結んでいます。頂点 $ i $ には正整数 $ A_i $ が書かれています。

あなたは、以下の操作を $ N $ 回繰り返します。

- まだ削除されていない頂点 $ x $ を選び、「頂点 $ x $ 」と「頂点 $ x $ を端点に持つ辺全て」を削除する。この操作のコストは、頂点 $ x $ と辺で直接結ばれていて、かつまだ削除されていない頂点に書かれている整数の総和である。

$ N $ 回の操作全体のコストを、$ 1 $ 回ごとの操作におけるコストのうちの最大値として定めます。操作全体のコストとして取り得る値の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 0\ \le\ M\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ 10^9 $
- $ 1\ \le\ U_i,V_i\ \le\ N $
- 与えられるグラフは単純。
- 入力は全て整数。

### Sample Explanation 1

以下のように操作を行うことにより、$ N $ 回の操作のコストのうちの最大値を $ 3 $ にすることができます。 - 頂点 $ 3 $ を選ぶ。コストは $ A_1=3 $ である。 - 頂点 $ 1 $ を選ぶ。コストは $ A_2+A_4=3 $ である。 - 頂点 $ 2 $ を選ぶ。コストは $ 0 $ である。 - 頂点 $ 4 $ を選ぶ。コストは $ 0 $ である。 $ N $ 回の操作のコストのうちの最大値を $ 2 $ 以下にすることはできないため、解は $ 3 $ です。

## 样例 #1

### 输入

```
4 3
3 1 4 2
1 2
1 3
4 1```

### 输出

```
3```

## 样例 #2

### 输入

```
7 13
464 661 847 514 74 200 188
5 1
7 1
5 7
4 1
4 5
2 4
5 2
1 3
1 6
3 5
1 2
4 6
2 7```

### 输出

```
1199```

# 题解

## 作者：Expert_Dream (赞：4)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

首先，出题人非常滴友善，提供了**最大值最小**字样，学过 OI 的选手一样就看出来了！二分！！

确实的，这一题就是**二分**。

我们可以直接二分答案，然后根据 $mid$ 去进行广度优先搜索，遍历到的这个点的所有连接的点权之和必须小于这个 $mid$，不然就是不可以加入，然后在广搜遍历的时候，如果这个点 $i$ 合法，还要将这个点 $i$ 所连向的所有点 $j$ 减去一个 $a_i$，使得实时更新每一个点目前周围的点的点权之和。

于是通过一个搜索板子题目，我们愉快的 AC 了。


[link](https://atcoder.jp/contests/abc267/submissions/48870321)。

---

## 作者：Erica_N_Contina (赞：3)

# AT_abc267_e 题解
## **贪心算法**

我们每次选举里面代价最小的点删除即可。因为每进行一次删除，就会让某些点的代价变小。因此代价越高的点我们让它多几次“代价变小”的机会，也就是说越晚把它删除。

我们预处理出初始状态下删除每个点 $i$ 的代价  $sum_i$，也就是每个点的所有邻点的点权之和。

## **数据结构**

我们记录一个**优先队列**，然后把所有点的信息用一个 **pair** 存进优先队列里。pair 存储信息如下：

- 第一位：代价 $(-sum_i)$，使用了取反技巧。  



- 第二位：该点的编号。

优先队列里的 pair 默认按第一位（.first）排序，并且是**大根堆**。所以我们应该 `pq.push(make_pair(-sum[i],i));`，这样就会按照 $sum_i$ 从小到大排序了（使用了简单的取反技巧）。

然后我们每次取出优先队列的 top 的点 $u$，判断它是否被删去（这个我们等下再讲）若没有，将它删去，然后访问它的邻点 $v$。把 $v$ 的 $sum_v$ 减去 $u$ 的点权。然后把 $v$（携带着新的 $sum_v$）push 进优先队列中。

## **一个小小的问题**

这时细心的你就发现了，在优先队列中还存在着那些携带了旧的 $sum_v$ 的点 $v$ 在！不用担心。因为新 push 进去的 $v$（携带着新的 $sum_v$）的 $sum_v$ 一定是小于原有的 $v$ 的 $sum_v$ 的（因为至少新的 $sum_v$ 已经减去了 $u$ 的点权）。

所以在优先队列中我们会**先访问到新的 $v$**，这时我们将 $vis_v$ 标记为 $1$ 表示已经访问过  $v$ 了（或者说 $v$ 已经被删除了），如果后面又访问到 $v$ 这个点，我们就知道这个是过时的，多余的 $v$，直接 `continue` 即可。

## **Code**

```C++
/*
       . Coding by Ntsc .
       . miss Chargcy .
/*

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
#define i1n int i=1;i<=n;i++
#define in1 int i=n;i>=1;i--
using namespace std;

const int N=2e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

vector<int> e[N];
int w[N],n,m,a,b,ans,vis[N];
priority_queue<pair<int,int> > pq;
int sum[N];

void add(int a,int b){
	e[a].push_back(b);
	sum[a]+=w[b];//在建边的时候就计算sum
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		add(a,b);add(b,a);
	}
	for(int i=1;i<=n;i++){//先将所有的点推进去
		pq.push(make_pair(-sum[i],i));
	}
	while(pq.size()){
		int u=pq.top().second;//不断取出当前剩余点中代价(sum)最小的那个
		pq.pop();
		if(vis[u])continue;//如果u之前已经被删去了,跳过
		ans=max(ans,sum[u]);//更新最大值
		vis[u]=1;//记录点u被删除
		for(int i=0;i<e[u].size();i++){//访问u的邻点
			int v=e[u][i];
			if(!vis[v]){
				sum[v]-=w[u];//更新删除v的代价
				pq.push(make_pair(-sum[v],v));//把新的v推进优先队列中
			}
		}
	}
	cout<<ans;
}

```


**其他信息**

代码长度 1.13KB

用时 335ms

内存 22.04MB



---

## 作者：ycy1124 (赞：1)

### 题意
在一张 $n$ 个点 $m$ 条边的无向图上删掉一个点的花费为其连接的所有未被删掉的点的权值和。求删完所有点的过程中单次花费的最大值的最小值。
### 思路
“最大值的最小值”已经提醒得很明显，此题要使用二分。每次二分一个 $mid$，从所有花费小于等于 $mid$ 的点开始删，删的时候给其连接的所有点的花费减少并判断是否小于 $mid$。最后判断是否删完所有点即可完成一次判断。
### 代码
这里使用 bfs 实现。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int>a[200005];
int w[200005],sum[200005],qwq[200005],n,m,ans,mid;
bool bj[200005];
queue<int>q;
inline void bfs(int p){
    bj[p]=0;
    for(auto it:a[p]){
        if(!bj[it]){
            continue;
        }
        qwq[it]+=w[p];
        if(sum[it]-qwq[it]<=mid){
            q.push(it);
            bj[it]=0;
        }
    }
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
        sum[u]+=w[v];
        sum[v]+=w[u];//边连边边加花费
    }
    int l=0,r=1e18;
    while(l<=r){
        mid=(l+r>>1);
        for(int i=1;i<=n;i++){
            qwq[i]=0;//记得清空，qwq表示减少的花费
            bj[i]=1;
            if(sum[i]<=mid){
                bj[i]=0;
                q.push(i);
            }
        }
        while(!q.empty()){
            bfs(q.front());
            q.pop();
        }
        bool pd=0;
        for(int i=1;i<=n;i++){
            pd=(pd|bj[i]);//是否有点每删掉
        }
        if(pd){
            l=mid+1;
            ans=mid+1;
        }
        else{
            r=mid-1;
            ans=mid;
        }
    }
    cout<<ans;
    return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/201582528)。

---

## 作者：Empty_Dream (赞：1)

# ABC267E 解题报告

## 题意

有一个有 $n$ 个顶点 $m$ 条边的无向图，每个点有一个点权 $a_i$，现在你需要进行以下操作 $n$ 次：

- 选择一个**未被删除**的点 $u$

- 将这个点及其相连的边删除，代价为与它所有**直接相连**的**未被删除的**的点的点权之和

现在请你求出删除整个无向图，单次操作代价**最大值的最小值**。

## 分析

根据题面，最大值的最小值，很容易想到二分答案，去二分单次操作的代价。

二分答案中的 check 可以直接通过 bfs 搜一遍看是否每个点都符合要求。但在每次 bfs 都统计一遍子节点的点权和很明显就会 TLE，所以这里采用~~打制表格~~预处理，在 bfs 前处理出来点权和。

对于 bfs，类似于拓扑排序的思路，把点权和小于 $mid$ 的节点加入队列中，然后按 bfs 的思路向下一层搜。设当前节点为 $u$，子节点为 $v$，则 $v$ 的点权和要减去 $a_u$（因为 $u$ 已经访问过了）。再判断 $v$ 是否符合需求，如果符合，那么加入队列。最后判断是否全部节点都被遍历过了，只有全部都能遍历，才满足要求。

在遍历 $v$ 时，不需要去看其他已经在队列中的节点权值。如果 $v$ 节点满足要求，那么直接加入，否则在遍历另一个在队列中与 $v$ 相关的节点 $u_1$ 时也会减去相应权值，不需要在 $u$ 一步减去。

不开 `long long` 见祖宗。

二分时 $l$ 记得设为 $0$，警钟敲烂。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m, sum;
int a[200005], s[200005], vis[200005], t[200005];
vector<int> g[200005];

bool check(int mid){//直接bfs
    queue<int> q;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++){
        t[i] = s[i];
        if (s[i] <= mid){//符合要求加入队列
            q.push(i);
            vis[i] = 1;
        }
    }
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (int i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            t[v] -= a[u];//只看u节点的权值
            if (t[v] <= mid && vis[v] == 0){//符合要求加入队列
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= n; i++){//判断是否全部遍历过
        if (vis[i] == 0) return 0;
    }
    return 1;
}

signed main(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, u, v; i <= m; i++){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++){//预处理子节点权值和
        for (int j = 0; j < g[i].size(); j++) s[i] += a[g[i][j]];
    }
    int l = 0, r = 1e18;//l为0！！！！！
    while (l < r){//二分答案
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << r;
    return 0;
}
```

---

## 作者：CYZZ (赞：1)

# [Erasing Vertices 2](https://www.luogu.com.cn/problem/AT_abc267_e)
这道题可以用二分或贪心做。
# 思路分析
结论：每次都选代价最小的删除。

因为每次删除一个点只会让与其相连的点代价变小，所以删除代价小的点和删除代价大的点对其他点的影响本质上一样。所以我们优先删除代价最小的点。

删除一个点的代价可以用优先队列维护，每次把连接且还未删除的点加入堆中即可。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,x,y,a[200005],sum[200005],d[200005],head[200005],tot,ans;
bool bk[200005];
struct node
{
    int id,val;
    bool operator < (const node &tmp) const
	{
		return val>tmp.val;
	}
};
priority_queue<node>q;
struct edge
{
    int next,to;
}e[400005];
void add_edge(int u,int v)
{
    e[++tot].next=head[u];
    e[tot].to=v;
    head[u]=tot;
}
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%lld%lld",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
        sum[x]+=a[y];
        sum[y]+=a[x];
    }
    for(int i=1;i<=n;i++)
    {
        d[i]=sum[i];
        q.push({i,d[i]});
    }
    while(!q.empty())
    {
        int u=q.top().id;
        q.pop();
        if(bk[u])
            continue;
        ans=max(ans,d[u]);
        bk[u]=1;
        for(int i=head[u];i;i=e[i].next)
        {
            int v=e[i].to;
            if(!bk[v])
            {
                d[v]-=a[u];
                q.push({v,d[v]});
            }
        }
    }
    printf("%lld",ans);
}

```

---

## 作者：DengDuck (赞：1)

这道题可以用贪心做，先说结论，我们每次都选代价最小的一项。

如何证明？这道题让我们求的是最大值最小，那么选最小值是局部最优的，而选了最小值之后，只可能使别的值变小，从而使别的值性价比更高，所以最小值是最好的。

如何维护出最小值？这里我用的是 `set`,对于每次修改，先删除对应的值，再把更新后的值加进去。当然优先队列也可以用一种巧妙的思路维护。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node {
    long long x, val;
    bool operator<(const node y) const {
        if (val == y.val) {
            return x < y.x;
        }
        return val < y.val;
    }
};
set<node> s;
long long n, m, x, y, a[200005], val[200005], mx;
vector<long long> v[200005];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
        val[x] += a[y];
        val[y] += a[x];
    }
    for (int i = 1; i <= n; i++) {
        s.insert({ i, val[i] });
    }
    while (!s.empty()) {
        node t = *s.begin();
        s.erase(s.begin());
        mx = max(mx, t.val);
        for (auto i : v[t.x]) {
            auto p = s.find({ i, val[i] });
            if (p != s.end()) {
                s.erase(p);
                val[i] -= a[t.x];
                s.insert({ i, val[i] });
            }
        }
    }
    cout << mx << endl;
    return 0;
}
```

---

## 作者：AbsMatt (赞：1)

## [题目传送器](https://www.luogu.com.cn/problem/at_abc267_e)
## [更爽的阅读体验](https://yaohaoyou.blog.luogu.org/solution-at-abc267-e)

## 题意
翻译题面已经很清楚了，这里就不解释了。
## 思路
看到 $n \le 2 \times 10^5$ 的数据和求``单次操作代价最大值的最小值``的题面时，作为一位拥有许多**挂分**经验的 Oier 来说，第一个想的思路就是**二分答案**。

想到二分答案就要思考二分的值和时间复杂度为 $O(n) $ 的 check 函数，接下来就分别分析这两部分。

#### 二分的值
很明显，就是最后输出的单次操作代价最大值的最小值。
#### check 函数
令每次操作的最大值的最小值为 $x$，由题意得每次删点的代价都要 $\le x$，那此时可以开一个队列来存放符合条件的点 $\le x$，每次删边时都要判断另一个点是否可以加入队列，若还没执行 $n$ 次队列就为空则返回 false，反之为 true。

参考代码：
```cpp
bool check(int x)
{
    mem();
    for (int i = 1; i <= n; i++)
    {
        if (point[i] <= x){
            q.push(i);
            inque[i]=1;
        }
    }
    if (q.size() == 0)
        return 0;
    for (int i = 1; i <= n; i++)
    {
        if (q.empty())
            return 0;
        int id = q.front();
        q.pop();
        used[id] = 1;
        inque[id] = 0;
        for (int j = head[id]; j; j = e[j].nxt)
        {
            int t = e[j].to;
            // printf("%d %d\n",id,t);
            point[t] -= a[id];
            if (point[t] <= x && !inque[t] && !used[t])
            {
                q.push(t);
                inque[t] = 1;
            }
        }
    }
    return 1;
}
```
## 注意事项
1. 最后输出的答案会爆 int，要开 long long（考时亲身体会）。
2. 边数组要开两倍空间。
3. 边和入度都要初始化。

## 总结
时间复杂度为 $O(n \log_2n)$。

## AC Code
```cpp
#include <bits/stdc++.h>  // 开始了
#define int long long // 开 long long
using namespace std;
const int maxn = 2e5 + 10;
int n, m, l = 0, r, ans, a[maxn], point[maxn], point2[maxn];
int cnt, head[maxn];
queue<int> q;
bool inque[maxn], used[maxn];
struct edge
{
    int nxt, to;
} e[maxn << 1];  // 双倍空间
void add(int u, int v)  // 建图
{
    e[++cnt] = {head[u], v};
    head[u] = cnt;
}
void mem()  // 初始化
{
    memcpy(point, point2, sizeof(point));
    memset(used, 0, sizeof(used));
}
bool check(int x)  // check 函数
{
    mem();
    for (int i = 1; i <= n; i++)
    {
        if (point[i] <= x){
            q.push(i);
            inque[i]=1;
        }
    }
    if (q.size() == 0)
        return 0;
    for (int i = 1; i <= n; i++)
    {
        if (q.empty())
            return 0;
        int id = q.front();
        q.pop();
        used[id] = 1;
        inque[id] = 0;
        for (int j = head[id]; j; j = e[j].nxt)
        {
            int t = e[j].to;
            // printf("%d %d\n",id,t);
            point[t] -= a[id];
            if (point[t] <= x && !inque[t] && !used[t])
            {
                q.push(t);
                inque[t] = 1;
            }
        }
    }
    return 1;
}
signed main()
{
    // freopen("ex_data1.in","r",stdin);
    scanf("%lld%lld", &n, &m);  // 输入
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        r += a[i];
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%lld%lld", &u, &v);
        point[u] += a[v];
        point[v] += a[u];
        add(u, v);
        add(v, u);
    }
    memcpy(point2, point, sizeof(point));
    while (l <= r)  // 二分
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    printf("%lld", ans);  // 输出
}
```


---

## 作者：Tsawke (赞：1)

#  [[ABC267E] Erasing Vertices 2](https://www.luogu.com.cn/problem/AT_abc267_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC267E)

## 题面

给定 $ n $ 个点 $ m $ 条边的无向图，给定点权，每次可以删除一个点，定义其花费为与其相连的所有没被删除的点的点权和，你需要删除所有点。最小化花费最大值，输出最小的最大值。

## Solution

第一眼看完以为是维护删除能节省的对于其它点的花费（即点权乘度数）减去删除的花费，每次删去最大的并动态维护相连点的该值，可以用平衡树维护，当然假了，因为后来才发现最小化的不是花费和，而是最大值。

然后想到的是每次删花费最大的点相连的花费最小的点，即想办法降低最大点的最大值，并动态维护，当然也可以用平衡树，不过这个东西仔细想一下就发现假了，最大点连结的最小点或许可能可以通过最小点连结的次小点更新，以此类推，如果一直找到最小没有分析，不过复杂度基本上是完全不可接受的。

于是在浪费了不少时间后我才想到了这个十分显然的正解，即显然我们直接删除花费最小的即可。因为如果你删除其它的任意点一定会使最大花费变大，那么这个点一定可以被删除且不贡献花费。于是我们每次找到花费最小的点，并动态维护相连其它点的花费即可。这个过程我使用了平衡树维护，即支持插入，删除，找第 $ k $ 小（即找最小）。

另外此题仍然存在思路，即二分答案，然后 $ O(n) $ 验证即可，这个思路也不难想到。

Tips：后来被机房同学提醒了一下之后我才愕然发现这东西用不到平衡树，直接正常维护优先队列，记录一下 $ idx $ 然后不用删除，直接记录，如果 $ idx $ 对应值于优先队里里的不同那么就丢弃即可。

Tips(again)：如果要使用平衡树维护的话，最普通的任意平衡树即可，因为这个用到的真的很浅，所以我们不难想到也可以直接用 `__gnu_pbds::tree` 维护，这里我用的是 `tree < pair < ll, int >, null_type, less < pair < ll, int > >, rb_tree_tag, tree_order_statistics_node_update > tr;`，需要注意我们这里不能用默认的参数，需要手动改为 `tree_order_statistics_node_update`，否则平衡树将不再支持 `find_by_order(x)` 以及 `order_of_key(x)` 等操作。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N, M;
ll A[210000];
ll cost[210000];
ll ans(LONG_LONG_MIN);
bitset < 210000 > vis;

struct Edge{
    Edge* nxt;
    int to;
    OPNEW;
}ed[410000];
ROPNEW;
Edge* head[210000];

tree < pair < ll, int >, null_type, less < pair < ll, int > >, rb_tree_tag, tree_order_statistics_node_update > tr;

int main(){
    N = read(), M = read();
    for(int i = 1; i <= N; ++i)A[i] = read();
    for(int i = 1; i <= M; ++i){
        int s = read(), t = read();
        head[s] = new Edge{head[s], t};
        head[t] = new Edge{head[t], s};
        cost[s] += A[t], cost[t] += A[s];
    }make_pair(cost[1], 1);
    for(int i = 1; i <= N; ++i)tr.insert({cost[i], i});
    for(int c = 1; c <= N; ++c){
        auto it = tr.find_by_order(0);
        ans = max(ans, it->first);
        vis[it->second] = true;
        for(auto i = head[it->second]; i; i = i->nxt)
            if(!vis[SON])
                tr.erase({cost[SON], SON}),
                tr.insert({cost[SON] -= A[it->second], SON});
        tr.erase({it->first, it->second});
    }printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_01_14 初稿

---

## 作者：_shine_ (赞：1)

$1\le n\le 2\times 10^5$ 而且最大值最小，最先想到的也只能二分了。

每次可以直接使用二分出来的 $mid$ 表示为单次删点的最大代价，即每次删点的代价不得超过 $mid$，这样每次边做边进行处理能使的时间较少。

但发现这样实时处理的容器必然为优先队列，但从最简单的来看每次就无法及时进行更新，这时可尝试把新的点的代价优先进行加入，而对于一个相同的点显然新加入的点会比老加入的点所在队列里的位置更靠前，此时尝试用数组标记当前点是否算过即可。

显然再思考一下就能发现一个更简单的方法。

只有 $n$ 个点却要删去 $n$ 个点，意思其实就是要把所有点都删完，其实就可以直接从代价最小的开始删，动态更新每一个点并维护一个优先队列直到把所有点从中删完即可。

这里维护优先队列的方法与上种方法相同。

---

## 作者：liuyi0905 (赞：0)

题意说的很清楚了，没读懂的童鞋多读几遍。
## 分析：
得知道此题要采用什么算法，看到**最大值的最小值**，即**最大值最小化**，经验丰富的 OI 选手就可得知改采用**二分答案**。
### 主函数：
1. 读入、建图。
2. 预处理点权和，因为每一次 `bfs` 求点权和会 TLE。
3. 二分答案，注意答案为 $r$。

代码：
```cpp
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(;m;m--){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	for(int u=1;u<=n;u++)
		for(int i=head[u];i;i=e[i].nxt)s[u]+=a[e[i].to];
	int l=-1,r=1e18+1;
	for(;l+1<r;){
		int mid=l+r>>1;
		if(check(mid))r=mid;
		else l=mid;
	}
	cout<<r;
	return 0;
}
```
### `check` 函数：
1. 清空 `vis` 数组。
2. 跑 `bfs`（这个蒟蒻忘跑 `bfs` 调了半小时）。
3. 只要有地方没跑过就返回 `false`，否则返回 `true`。

代码：
```cpp
bool check(int x){
	fill(vis+1,vis+n+1,0);
	bfs(x);
	for(int i=1;i<=n;i++)
		if(!vis[i])return 0;
	return 1;
}
```
### `bfs` 函数：
1. 将点权和小于等于 $mid$ 的数放入队列。
2. 每次遍历时，将点 $u$ 的点权和减去 $a_v$（$u$ 为根节点，$v$ 为子节点）。若点权和小于等于 $mid$ 且没走过，就入队。

代码：
```cpp
void bfs(int x){
	queue<int>q;
	for(int i=1;i<=n;i++)
		if((t[i]=s[i])<=x)vis[i]=1,q.push(i);
	for(;!q.empty();){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if((t[v]-=a[u])<=x&&!vis[v])vis[v]=1,q.push(v);
		}
	}	
}
```
### 注意事项：
+ 由于此题建的是无向边，链式前向星数组要开两倍。
+ 十年 OI 一场空，不开 `long long` 见祖宗。
+ $l$ 初始要设为 $-1$。

---

## 作者：chengning0909 (赞：0)

# abc 267 e

## 题意

给定一个 $N$ 个点 $M$ 条边的简单无向图，第 $i$ 条边连接 $U_i, V_i$，点 $i$ 的点权为 $A_i$。

重复以下操作 $N$ 次：

- 选择一个未被移除的点 $x$，移除 $x$ 和与 $x$ 相连的所有边。这次操作的代价为所有与 $x$ 直接相连的点的点权之和。

请你求出 $N$ 次操作代价的最大值的最小可能值。

## 思路

### 二分

我们可以发现，答案越小，越难达到，有单调性，可以想到 **二分**。

那么，我们应该如何判断每个值是否可行呢？

设我们当前要判断 $X$ 是否可行，那么，我们肯定是先选择产生代价 $\le x$ 的点删除。

而每次删除点，都只会使得与它直接相连的点所产生的代价变小，所以，每次只需要判断那些与它直接相连的点所产生的代价是否 $\le X$ 即可。

令 $V$ 为所有点权之和。

每次 `Check()` 的时间复杂度为 $O(N + M)$，二分的时间复杂度为 $O(\log V)$，所以总时间复杂度为 $O((N + M) \times \log V)$。

#### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e5 + 10;

int n, m, a[N];
bool f[N];
vector<int> g[N];
ll s[N];

bool Check(ll x) {
  queue<int> que;
  int c = 0; 
  for (int i = 1; i <= n; i++) {
    s[i] = f[i] = 0;
    for (int j : g[i]) {
      s[i] += a[j];
    }
    if (s[i] <= x) {
      que.push(i), f[i] = 1;
    }
  }
  while (!que.empty()) {
    int u = que.front();
    que.pop(), c++;
    for (int v : g[u]) {
      s[v] -= a[u];
      if (s[v] <= x && !f[v]) {
        que.push(v), f[v] = 1;
      }
    }
  }
  return c == n;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  while (m--) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }
  ll l = 0, r = 2e14;
  while (l < r) {
    ll mid = (l + r) >> 1;
    if (Check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  cout << l;
  return 0;
}
```

### 贪心

每次选择产生代价最小的点删除，用堆或者 `set` 维护。

时间复杂度为 $O((N + M) \times \log (N + M))$。

#### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, m, a[N];
long long sum[N], ans;
bool f[N];
vector<int> g[N];

struct Node {
  long long s;
  int id;
  bool operator < (const Node &i) const {
    return s > i.s;
  }
};

priority_queue<Node> pq;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  while (m--) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    for (int j : g[i]) {
      sum[i] += a[j];
    }
    pq.push({sum[i], i});
  }
  while (!pq.empty()) {
    Node u = pq.top();
    pq.pop();
    if (!f[u.id]) {
      f[u.id] = 1, ans = max(ans, u.s);
      for (int v : g[u.id]) {
        sum[v] -= a[u.id], pq.push({sum[v], v});
      }
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

[AT_abc267_e](https://www.luogu.com.cn/problem/AT_abc267_e)

[Erasing Vertices 2](https://atcoder.jp/contests/abc267/tasks/abc267_e)

### 思路

最大的最小一类的问题，通常用二分答案。

设答案值域为 $v$，复杂度 $O(\log v)$。

```cpp

	l=0,r=inf;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
```

注意此题答案值可以为 $0$。

需要 $O(n)$ 实现判断 答案 $mid$ 是否可行的 check 函数。

数组 $val_i$ 记录点 $i$ 最开始的花费。对于每个 $val_u \leq mid$ 的点可以直接删去，并使得与 $u$ 相邻的 $v$ 的 $val_v$ 减去 $a_u$。这个过程等同于模拟删点。

在这个过程中，只有与被删点相邻的点的权值会受到影响，并有可能进一步被删去。

将每个被删点推入队列，改变其邻点后再删去。如果邻点被改变后也可以被删去，则邻点也加入队列。

用计数器记录删了几个点。如果删了 $n$ 个，说明 $mid$ 可行。

每个点最多会被经过一次，每条边最多被经过一次，check 复杂度 $O(n+m)$，总复杂度 $O(\log v \times n)$。

```cpp

bool check(int x){
	int cnt=0;
	for(int i=1;i<=n;i++)w[i]=val[i],vis[i]=0;
	for(int i=1;i<=n;i++){
		if(w[i]<=x)q.push(i),++cnt,vis[i]=1;
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!vis[v]){
				w[v]-=a[u];
				if(w[v]<=x)q.push(v),++cnt,vis[v]=1;
			}
		}
	}
	return cnt==n;
}
```

### code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;
const int inf=1e12;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,m,a[maxn];
int l,r,mid,ans;
struct nd{
	int nxt,to;
}e[maxn<<1];
int head[maxn],tot;
void add(int u,int v){
	e[++tot].nxt=head[u];e[tot].to=v;
	head[u]=tot;
}
int val[maxn],w[maxn],vis[maxn];
queue<int> q;
bool check(int x){
	int cnt=0;
	for(int i=1;i<=n;i++)w[i]=val[i],vis[i]=0;
	for(int i=1;i<=n;i++){
		if(w[i]<=x)q.push(i),++cnt,vis[i]=1;
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!vis[v]){
				w[v]-=a[u];
				if(w[v]<=x)q.push(v),++cnt,vis[v]=1;
			}
		}
	}
	return cnt==n;
}
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		add(u,v);add(v,u);
		val[u]+=a[v];val[v]+=a[u];
	}
	l=0,r=inf;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	printf("%lld\n",ans);
}
```


---

## 作者：DaiRuiChen007 (赞：0)

# ABC267E 题解

## 思路分析

考虑二分删除的时候的最大花费 $w$，check 的时候每次把删除点 $u$ 的花费 $\le w$ 的所有点 $u$ 加入队列，删除之后价差所有与 $u$ 相邻的点是否花费 $\le w$，做一遍 BFS 即可，最终检查有没有没有删除的点即可。

时间复杂度 $\Theta((n+m)\log w)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+1,INF=1e18;
int a[MAXN],val[MAXN],cost[MAXN];
int n,m;
bool vis[MAXN];
vector <int> edge[MAXN];
inline bool check(int limit) {
	queue <int> q;
	memset(vis,false,sizeof(vis));
	memcpy(cost,val,sizeof(cost));
	int cnt=0;
	for(int i=1;i<=n;++i) {
		if(cost[i]>limit) continue;
		vis[i]=true;
		++cnt;
		q.push(i);
	}
	while(!q.empty()) {
		int p=q.front();
		q.pop();
		for(int v:edge[p]) {
			if(vis[v]) continue;
			cost[v]-=a[p];
			if(cost[v]>limit) continue;
			vis[v]=true;
			++cnt;
			q.push(v);
		}
	}
	return cnt==n;
}
signed main() {
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(int i=1;i<=m;++i) {
		int u,v;
		scanf("%lld%lld",&u,&v);
		val[u]+=a[v];
		val[v]+=a[u];
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	int l=0,r=INF,res=-1;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid)) res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",res);
	return 0;
}
```

---

