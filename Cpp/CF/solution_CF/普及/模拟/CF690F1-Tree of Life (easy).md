# Tree of Life (easy)

## 题目描述

Heidi has finally found the mythical Tree of Life – a legendary combinatorial structure which is said to contain a prophecy crucially needed to defeat the undead armies.

On the surface, the Tree of Life is just a regular undirected tree well-known from computer science. This means that it is a collection of $ n $ points (called vertices), some of which are connected using $ n-1 $ line segments (edges) so that each pair of vertices is connected by a path (a sequence of one or more edges).

To decipher the prophecy, Heidi needs to perform a number of steps. The first is counting the number of lifelines in the tree – these are paths of length $ 2 $ , i.e., consisting of two edges. Help her!

## 说明/提示

In the second sample, there are four lifelines: paths between vertices $ 1 $ and $ 3 $ , $ 2 $ and $ 4 $ , $ 2 $ and $ 5 $ , and $ 4 $ and $ 5 $ .

## 样例 #1

### 输入

```
4
1 2
1 3
1 4
```

### 输出

```
3```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
3 5
```

### 输出

```
4```

# 题解

## 作者：_sunkuangzheng_ (赞：1)

**【题目分析】**

怎么能没有点分治题解！/fn

点分治几乎板子题，维护路径长度为 $0,1,2$ 的数量，因为长度为 $2$ 的只能由 $0,2$ 或者 $1,1$ 组成，所以算答案的时候乘一下就好了。

这里采用了容斥的写法。

**【代码】**


```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
struct edge{int to,nxt,w;}e[maxn];int cnt,head[maxn],n,k,u,v,w,siz[maxn],vis[maxn],ms[maxn],ans,rt,mx,tot,dis[maxn];
void add(int u,int v,int w){e[++cnt].to = v,e[cnt].nxt = head[u],e[cnt].w = w,head[u] = cnt;}
void dfs1(int u,int fa){
    siz[u] = 1,ms[u] = 0;
    for(int i = head[u];i;i = e[i].nxt){
        int v = e[i].to;if(v == fa || vis[v]) continue;
        dfs1(v,u);siz[u] += siz[v];if(siz[v] > ms[u]) ms[u] = siz[v];
    }
}
void dfs2(int u,int r,int fa){
    ms[u] = max(ms[u],siz[r] - ms[u]);
    if(ms[u] < mx) mx = ms[u],rt = u;
    for(int i = head[u];i;i = e[i].nxt){
        int v = e[i].to;if(v == fa || vis[v]) continue;
        dfs2(v,r,u);
    }
}
void dfs3(int u,int w,int fa){
    dis[++tot] = w;
    for(int i = head[u];i;i = e[i].nxt){
        int v = e[i].to;if(v == fa || vis[v]) continue;
        dfs3(v,w + e[i].w,u);
    }
}
int get_ans(int u,int d){
    tot = 0,dfs3(u,d,0);int res1 = 0,res2 = 0,res3 = 0;
    for(int i = 1;i <= tot;i ++) res1 += (dis[i] == 0),res2 += (dis[i] == 1),res3 += (dis[i] == 2);
    return res1 * res3 + res2 * (res2-1)/2;
}
void dfs4(int u){
    dfs1(u,0);mx = 1e9;dfs2(u,u,0);
    ans += get_ans(rt,0),vis[rt] = 1;
    for(int i = head[rt];i;i = e[i].nxt){
        int v = e[i].to;if(vis[v]) continue;
        ans -= get_ans(v,e[i].w),dfs4(v);
    }
}
int main(){
    cin >> n;
    for(int i = 1;i < n;i ++) cin >> u >> v,add(u,v,1),add(v,u,1);
    dfs4(1),cout << ans;
}
```

---

## 作者：xxxr_2024 (赞：1)

# CF690F1 Tree of Life (easy)
## 分析
题目让你求树上长度为 $2$ 的路径，遍历每个点，用 $ans$ 统计它邻居的邻居的个数，需要注意，它自己也属于邻居的邻居，所以统计时要 $-1$。

输出时，因为每个点都被算了两次，所以要除以 $2$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Raiden
{
	const int N=1e4+5;
	vector<int> g[N];
	signed work()
	{
		int n;
		cin>>n;
		for(int i=1;i<n;i++)
		{
			int a,b;
			cin>>a>>b;
			g[a].push_back(b);
			g[b].push_back(a);
		}
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			for(auto it:g[i])
			{
				ans+=g[it].size()-1;
			}
		}
		cout<<ans/2<<endl;
		return 0;
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return Raiden::work();
}
```

---

## 作者：Arrtan_73 (赞：1)

# 题目大意
[传送门](https://www.luogu.com.cn/problem/CF690F1)

求一棵树上面长度为 $2$ 的路径条数。

# 题目思路
首先我们先来画一画图，便于思考。

![树](https://i.postimg.cc/5NyRJ8xM/2023-04-25-195731.png)

可以看到以 $1$ 号节点上长度为 $2$ 的路径条数有 $6$ 条，也就是 $1$ 号的孙子节点的数目，为什么会这样呢？

如果我们把每一条路径分为两个阶段，也就是从源节点到子节点和子节点到孙子节点两部分路径，就可以想明白了。

![树](https://i.postimg.cc/Ghzd7FXw/2023-04-25-201057.png)

距离为 $2$ 的路径就相当于两条距离为 $1$ 的路径连接，距离为 $1$ 的路径条数就是其子节点数，那么距离为 $2$ 的路径条数就是其子节点的子节点数，也就是孙子节点的数目。只需要把每个节点的孙子节点数目累加一遍即可。

PS1：例如两个节点 $u,v$，我们会把 $u$ 到 $v$ 和 $v$ 到 $u$ 的路径都算一遍，但实际上这是同一条路径，所以最后要除以 $2$ 再输出。

PS2：本题数据很小，用邻接数组存即可。
# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> G[10005];
int n, ans;

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int v, u;
		cin >> v >> u;
		G[v].push_back(u);
		G[u].push_back(v);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < G[i].size(); j++)
			ans += G[G[i][j]].size() - 1;
	cout << ans / 2;
	return 0;
}
```


---

## 作者：oddy (赞：1)

## 题意解释

给定一棵树，求它上面长度为 $2$ 的路径条数。

## 解题思路

枚举每个点的邻居的邻居个数，把答案累加。

## 代码

```cpp
#include <cstdio>
#include <vector>

int n, u, v, ans;
std::vector<int> e[10005];

int main() {
    scanf("%d", &n);

    for(int i = 1; i < n; i++) scanf("%d%d", &u, &v), e[u].push_back(v);
    for(int i = 1; i <= n; i++) for(const int &j : e[i]) ans += e[j].size();

    printf("%d\n", ans);

    return 0;
}
```

---

## 作者：Swiftie_wyc22 (赞：1)

一道比较简单的无人问津的题目。

简化题意：求一棵树上长度为 $2$ 的路径条数.

在第二个示例中，有四条生命线：顶点 $1$ 和 $3$、$2$ 和 $4$、$2$ 和 $5$ 以及 $4$ 和 $5$ 之间的路径。

# 思路

对于这道数据量不大的题目，我们可以用邻接表存下这个树。

由于要求的是长度为 $2$ 的路径条数，也就是起点与终点之间隔开一个点。那么遍历 $n$ 个点，对于第 $i$ 个点，累加第 $i$ 个点的每个邻居连接了多少个点即可。

这句话比较不好懂，画个图就可以看懂。

![](https://cdn.luogu.com.cn/upload/image_hosting/2muin1l3.png)

我们目前遍历到 $4$ 号点了，那么 $4$ 的邻居只有 $1$ 号点，那么我们看 $1$ 号点连接了 $2$、$3$ 号顶点，那么 $4$ 号点有两条路径，即 4-2、4-3。

但是由于我们会遍历到每一个点，所以每两个点之间会产生重复，故最后累加的结果要除 2。

上代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
vector<int>f[10010]; // 邻接表
int ans;
int main()
{
	ios::sync_with_stdio(false); // 当做空气即可
    int n;
    cin >> n;
    int _, __;
    for (int i = 1; i <= n - 1; i++)
    {
    	cin >> _ >> __;
        f[_].push_back(__); // 存储双向边
        f[__].push_back(_);
    }
    for (int i = 1; i <= n; i++)
    {
    	for (int j = 0; j < f[i].size(); j++)
    	{
    		ans += f[f[i][j]].size() - 1;
		}
	}
	cout << ans / 2 << endl;
    return 0;
}
```


---

## 作者：Ryan_Adam (赞：0)

## 思路分析
题目要求你求出树上长为 $2$ 的路径的个数，即就是算出每一个点邻居的邻居的个数之和。遍历每个点统计即可，注意每个点邻居的邻居包括它自己，统计时需要减一。并且对于两个点，都会被对方当做邻居的邻居统计，所以每条路径多统计了一次，最后要将答案变量 $s$ 除以二。

考虑到需要知道每个点的邻居个数，用 `vector` 存图，链式前向星过于麻烦。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define N 10010
#define pb push_back
std::vector<int> v[N];
int n,s,i,x,y;
int main(){
    std::cin>>n;
    for(i=1;i<n;++i){
        std::cin>>x>>y;
        v[x].pb(y),v[y].pb(x);
    }
    for(i=1;i<=n;++i)for(auto j:v[i])s+=v[j].size()-1;
    std::cout<<(s>>1)<<'\n';
}
```

---

## 作者：filletoto (赞：0)

## 思路

定义一个 `vector` 数组来存储每个节点与它联通的其他节点，然后 `for` 循环遍历每一个节点与它长度为 $2$ 的路径条数，注意计算时需要将结果减 $1$，因为他自己也是邻居的邻居，但我们不能计算在内。

最后 $ans$ 要除以 $2$ 再输出。

## 代码
~~~cpp
#include <iostream>
#include <vector>
using namespace std;
int n,u,v,ans;
vector<int> g[10005];
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<n;i++)
	{
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u); 
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<g[i].size();j++)
		{
			ans+=g[g[i][j]].size()-1;
		}
	}
	cout << ans/2 << endl;



	return 0;
}
~~~

---

## 作者：NightmareAlita (赞：0)

## 简要题意

给你一棵树，求树上长度为 $2$ 的路径条数

## 策略分析

我们看下面这张图：

![](https://s1.ax1x.com/2023/08/29/pPdSEL9.png)

我们发现对于点 $u,v$，$v$ 是与 $u$ 相连的一个点，从 $u$ 出发的长度为 $2$ 的路径条数就等于 $v$ 的度数减去 $1$，因为 $u$ 本身也和 $v$ 相连，所以要把自己减掉。比如说上面这张图中，与 $1$ 距离为 $2$ 的点有 $6,7,8,9,5$ 这 $5$ 个，而 $1$ 的三个子节点的度数分别为 $3,3,2$，分别减去 $1$ 再相加刚好是 $5$。

我们对这整张图统计以后，其实对于每一个点我们都统计了与它距离为 $2$ 的点，因为存图时是无向图，所以同一条路径一定计算了两次，累加的答案要减半。

时间复杂度 $O(n^2)$。

## 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

namespace SHAWN {
    const int N = 1e4 + 7;
    vector<int> edge[N];
    int n, sum;
    int work()
    {
        cin >> n;
        for (int i = 1, x, y; i < n; ++i) {
            cin >> x >> y;
            edge[x].emplace_back(y);
            edge[y].emplace_back(x);
        }
        for (int i = 1; i <= n; ++i) {
            for (auto it : edge[i]) { 
                sum += edge[it].size() - 1; 
            }
        }
        sum >>= 1;
        cout << sum << '\n';
        return 0;
    }
}

signed int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    return SHAWN :: work();
}
```



---

## 作者：asas111 (赞：0)

## 思路
这题相当于求树上每一个点邻居的邻居的总和。只需要计算每一个点邻居的邻居的数量减去 $1$（因为邻居的邻居包含这个点，显然这种是不满足要求的），再相加。因为每条路径会被算 $2$ 次，所以最后除以 $2$ 就可以了。用邻接表来存储。
## 代码
```
#include<bits/stdc++.h>
#define N 10009
using namespace std;
vector<int> t[N];
int n,ans=0;
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		t[u].push_back(v);
		t[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<t[i].size();j++)
			ans+=t[t[i][j]].size()-1;
	cout<<ans/2;
	return 0;
}
```


---

