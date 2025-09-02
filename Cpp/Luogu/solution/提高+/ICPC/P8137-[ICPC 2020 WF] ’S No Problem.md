# [ICPC 2020 WF] ’S No Problem

## 题目描述

位于斯诺布洛维亚北部的 某·工程技术学院 (YETI) 面临两个问题：雪和金钱。具体来说，他们有太多的前者而没有足够的后者。每年冬天（以及秋天和春天），校园都覆盖着雪毯。维护人员必须清理连接校园建筑的所有人行道，但他们只有两台吹雪机，并且已经明确告知他们在不久的将来不能再获得更多。

为了保持这两台珍贵机器的使用寿命，工作人员决定采用以下除雪程序。每台机器都被分配了一条连接校园内两座建筑物的固定路线。每当必须除雪时，每台吹雪机都会从其路线一端的建筑物中取出并用于清除积雪，最终进入其路线另一端的建筑物中，并存放在那里直到下一次降雪。在下一次除雪活动期间将发生反向运动——每台机器将沿相反方向追踪其分配的路线。这个过程在整个 1 个月的雪季循环。请注意，路线可能涉及翻过已清理的人行道。此外，同一建筑物可能是两条吹雪机路线的终点。

校园人行道以树的形式布置。为了尽可能少地运行机器，工作人员希望尽量减少吹雪机在沿路线引导时必须行驶的总距离。图 J.1 显示了第一个样本输入的人行道布局的最佳解决方案。

YETI 维护人员会要求 YETI 的计算机科学系解决这个问题，但他们在 06 年的大暴雪中失败了，所以他们来找你帮忙。

## 样例 #1

### 输入

```
7
1 4 2
2 4 3
3 4 1
4 5 1
5 6 2
5 7 4```

### 输出

```
15```

## 样例 #2

### 输入

```
4
1 2 1
2 3 2
3 4 3```

### 输出

```
6```

# 题解

## 作者：TemplateClass (赞：1)

$\gdef \dp{\mathrm{dp}}$
$\gdef \son{\mathrm{son}}$

首先你先考虑假设只有一台扫雪机，这个答案最大是 $2 \times \sum d$。因为你可以对于树的每个边都一进一出一次，把路径搞成一个大环。

然后考虑去除掉这个大环中的两段路径，这样这个环就会断成两条路径，于是就可以把这两条路径当作两个扫雪机的路线了。

于是我们希望知道这两条路径是啥，你想一下就会发现去除的一定是树中的两条不相交的路径，否则如果相交的话就会有的边没有被清扫。由于要求和最小，我们自然希望去除的长度最大，也就是我们要找出树中最长的两条不相交的路径。

这个东西比较典，直接 dp。设：

- $\dp _ {i, 0}$ 表示根为 $i$ 的子树中从根出发最长的一条路径的长度；
- $\dp _ {i, 1}$ 表示根为 $i$ 的子树中最长的一条路径的长度；
- $\dp _ {i, 2}$ 表示表示根为 $i$ 的子树中最长的两条路径（其中一条从根出发）的长度和；
- $\dp _ {i, 3}$ 表示表示根为 $i$ 的子树中最长的两条路径的长度和。

之所以这么设，是因为若当前节点所有子树的四个结果都被计算出来，就可以利用子树的四个结果计算当前节点的四个结果。

具体地，依次对于每个 $v \in \son _ u$，我们有：

- $\dp _ {u, 3} \gets \max \!\left\{ \dp _ {u, 3}, \dp _ {u, 2} + \dp _ {v, 0} + d _ {uv}, \dp _ {u, 1} + \dp _ {v, 1}, \dp _ {u, 0} + \dp _ {v, 2} + d _ {uv}, \dp _ {v, 3} \right\}$；
- $\dp _ {u, 2} \gets \max \!\left\{ \dp _ {u, 2}, \dp _ {u, 1} + \dp _ {v, 0} + d _ {uv}, \dp _ {u, 0} + \dp _ {v, 1}, \dp _ {v, 2} + d _ {uv} \right\}$；
- $\dp _ {u, 1} \gets \max \!\left\{ \dp _ {u, 1}, \dp _ {u, 0} + \dp _ {v, 0} + d _ {uv}, \dp _ {v, 1} \right\}$；
- $\dp _ {u, 0} \gets \max \!\left\{ \dp _ {u, 0}, \dp _ {v, 0} + d _ {uv} \right\}$。

看着很长，实际上很好理解。最后答案就是 $2 \times \sum d - \dp _ {1, 3}$，时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>

constexpr int N = 1e5 + 5;

int n, sum_d = 0, dp[N][4];
std::vector<std::pair<int, int> > G[N];

void solve_dp(int u, int father) {
	for(const auto& [v, d] : G[u]) {
		if(v == father) continue; else solve_dp(v, u);
		dp[u][3] = std::max({dp[u][3], dp[u][2] + dp[v][0] + d, dp[u][1] + dp[v][1], dp[u][0] + dp[v][2] + d, dp[v][3]});
		dp[u][2] = std::max({dp[u][2], dp[u][1] + dp[v][0] + d, dp[u][0] + dp[v][1], dp[v][2] + d});
		dp[u][1] = std::max({dp[u][1], dp[u][0] + dp[v][0] + d, dp[v][1]});
		dp[u][0] = std::max({dp[u][0], dp[v][0] + d});
	}
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> n;
	for(int i = 1; i <= n - 1; ++i) {
		int u, v, d; std::cin >> u >> v >> d; sum_d += d;
		G[u].emplace_back(v, d), G[v].emplace_back(u, d);
	}
	
	solve_dp(1, 0);
	std::cout << (sum_d << 1) - dp[1][3] << "\n";
	
	return 0;
}
```

---

## 作者：Seqfrel (赞：0)

# 题解：P8137 [ICPC2020 WF] ’S No Problem

前置知识：树的直径、树形DP。

## 题目大意

给定一个无向树。有两个扫雪机可以任意选择出发终止点，可以走回头路。求两个扫雪机遍历整个树所需的最短路程。

## 解题思路

不妨先考虑只有一个扫雪机的情况。

我们知道，在无向树上从任意一个结点出发，将所有的边经过两遍，串成一个环，最终都能回到那个结点。就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/ahf6ect3.png)

这也就是这一个扫雪机遍历整个树的最坏情况。

但是所有的路我们都走了两遍，很明显我们并不需要这样做，也不需要回到起始节点。于是我们将这个环去除一条路径，剩下的边就构成了一条简单路径，也就是起点和终点不在一个点上的扫雪机路线。并且这个去除的路径一定不能同时包含原图中一条边的两个方向，否则扫雪机就不能到达所有结点。

那么，自然是去除的路径越长，扫雪机所需走的路程就越短。

显然，要去除的就是树的直径。去除后的路径就是一台扫雪遍历完整棵树所需最短路径。就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/h94s4cy4.png)

接下来就很好办了。既然一台扫雪机的情况我们已经得出，那么将其推广到两台扫雪机甚至 $k$ 台扫雪机就都不是问题。

上面得出，去除一条最长路径就是一台扫雪机的最短路径，那么去除两条**不相交**的最长路径就是两台扫雪机的最短路径（相交了就同时去除了原图一条边的两个方向），去除 $k$ 条不相交最长路径就是 $k$ 台扫雪机的最短路径。

由此，解法已经得出。

## 代码实现

显然使用树形DP求解。

深搜这棵树，记录每个结点 $u$ 的四个状态：

- $f_1$：以 $u$ 为根的子树中，往 $u$ 结点之上延伸的最长的一条路径
- $f_2$：以 $u$ 为根的子树中，不往 $u$ 结点之上延伸的最长的一条路径
- $f_3$：以 $u$ 为根的子树中，往 $u$ 结点之上延伸（当然只能延伸一条）的两条路径
- $f_4$：以 $u$ 为根的子树中，不往 $u$ 结点之上延伸的两条路径

如果是 $k$ 台扫雪机，那么就继续往下以此类推。整棵树根 $root$ 的第 $2\times k$ 个状态即为 $k$ 条不相交最长路径的长度和。

不过这些状态之间转移的关系错综复杂，并且对着方程仔细琢磨一下也好理解，于是这里就把所有的方程都列出来（这里 $u$ 表示子树根节点，$v$ 表示 $u$ 的子结点，$w$ 表示 $u$ 与 $v$ 之间边的边权）：

$$f_4(u)=\max(f_4(u),f_3(u)+f_1(v)+w)$$
$$f_4(u)=\max(f_4(u),f_2(u)+f_2(v))$$
$$f_3(u)=\max(f_3(u),f_2(u)+f_1(v)+w)$$
$$f_4(u)=\max(f_4(u),f_1(u)+f3(v)+w)$$
$$f_3(u)=\max(f_3(u),f_1(u)+f_2(v))$$
$$f_2(u)=\max(f_2(u),f_1(u)+f_1(v)+w)$$
$$f_4(u)=\max(f_4(u),f_4(v))$$
$$f_3(u)=\max(f_3(u),f_3(v)+w)$$
$$f_2(u)=\max(f_2(u),f_2(v))$$
$$f_1(u)=\max(f_1(u),f_1(v)+w)$$

这些方程单独写出来固然清晰明白好理解，但是在敲代码的时候非常容易出错。因此 ICPC judge bruce merry 有一份非常巧妙的代码，使用一个双层循环来完成状态的转移，并且可以直接通过修改 $E$ 的值来求出任意 $k$ 条不相交最长路径。贴在这里：


```cpp
static vector<int> recurse(vector<node> &nodes, int cur, int parent, int E) {
    node &n = nodes[cur];
    vector<int> dp(E + 1, 0);
    for (const auto &ch : n.edges) {
        if (ch.dest == parent) continue;
        auto sub = recurse(nodes, ch.dest, cur, E);
        for (int i = E-1; i >= 0; i--)
            for (int j = E - i; j >= 1; j--) {
                int score = dp[i] + sub[j] + ((j & 1) ? ch.len : 0);
                dp[i + j] = max(dp[i + j], score);
            }
    }
    return dp;
}

```

最后输出二倍边权和减去除的路径总长即可求出答案。

完整代码：


```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1e5+10;
struct Node{
	int to,nxt,w;
}e[2*maxn];
int n,sum,ans;
int h[maxn],tot;
int f1[maxn],f2[maxn],f3[maxn],f4[maxn]; 
void Add(int u,int v,int w){
	tot++;
	e[tot].to=v;
	e[tot].nxt=h[u];
	e[tot].w=w;
	h[u]=tot;
} 
void Dfs(int root,int fa){
	for(int i=h[root];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		Dfs(v,root);
		f4[root]=max(f4[root],f3[root]+f1[v]+e[i].w);
		f4[root]=max(f4[root],f2[root]+f2[v]);
		f3[root]=max(f3[root],f2[root]+f1[v]+e[i].w);
		f4[root]=max(f4[root],f1[root]+f3[v]+e[i].w);
		f3[root]=max(f3[root],f1[root]+f2[v]);
		f2[root]=max(f2[root],f1[root]+f1[v]+e[i].w);
		f4[root]=max(f4[root],f4[v]);
		f3[root]=max(f3[root],f3[v]+e[i].w);
		f2[root]=max(f2[root],f2[v]);
		f1[root]=max(f1[root],f1[v]+e[i].w);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);
		Add(b,a,c);
		sum+=2*c;
	}
	Dfs(1,0);
	ans=f4[1];
	cout<<sum-ans;
	return 0;
} 
```

## 注意事项

无向边开二倍数组。

---

