# [GCJ 2013 #3] Are We Lost Yet?

## 题目描述

现在是 Google Code Jam 总决赛的时间了，我们都希望能够到场！不幸的是，我们中的几个人却误打误撞去了 Mountain View，而不是正确的地点伦敦。不过别担心——我们可以乘坐 Google 提供的免费穿梭巴士从 Mountain View 前往伦敦！

这项巴士服务由 $M$ 条单向路线组成，连接着不同的城市。对于每一条路线，你知道它是从哪座城市出发、到达哪座城市，但你并不知道这条路线的具体长度。你只知道每条路线的长度可以是从 $a_i$ 到 $b_i$（包含两端）的任意整数值。

我曾多次乘坐 Google 的穿梭巴士，因此我为你规划了一条从 Mountain View 到伦敦的路线。但你担心我的路径规划能力不如你，所以你想检查一下我的方案。

给定我建议的这条路径，它是否有可能是 Mountain View 到伦敦的最短路径？如果不是，那么请指出在我的路径上第一个**肯定不可能**属于最短路径的穿梭巴士路线的编号（假设在此之前的所有路线都已按照我建议的路径依次乘坐）。

例如，假设有如下穿梭路线列表：

| 路线编号 | 起点城市 | 终点城市 | 路线长度 |
| :-: | :-: | :-: | :-: |
| 1 | Mountain View | London | $[100, 1000]$ |
| 2 | Mountain View | Paris | $[500, 5000]$ |
| 3 | Paris | London | $[400, 600]$ |
| 4 | Paris | Moscow | $[500, 5000]$ |
| 5 | Moscow | London | $[1, 10000]$ |

我建议的路径为 Mountain View -> Paris -> Moscow -> London。实际上，最短路径可能是直接从 Mountain View 到 London，也可能是 Mountain View -> Paris -> London。这意味着我建议的路径上第二段（Paris -> Moscow）就是第一个**肯定不可能**属于最短路径的穿梭路线。


## 说明/提示

**限制条件**

- 我的路径保证是从 Mountain View（城市 $1$）到 London（城市 $2$）的一条合法路径。
- 可能会有多条路线连接同一对城市，也可能有从某城市到自身的路线。建议的路径可能会多次经过同一城市，但不会重复使用同一条路线。

**小数据集（12 分，测试集 1 - 可见）**

- $2 \leq N \leq 20$
- $1 \leq M \leq 20$
- $1 \leq P \leq 10$

**大数据集（18 分，测试集 2 - 隐藏）**

- $2 \leq N \leq 1000$
- $1 \leq M \leq 2000$
- $1 \leq P \leq 500$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
3
4 5 3
1 2 100 1000
1 3 500 5000
3 2 400 600
3 4 500 5000
4 2 1 10000
2 4 5
3 3 2
1 3 1 1
3 2 1 1
1 2 1 2
1 2
5 6 3
1 3 1 1
4 2 1 9
1 4 1 1
3 5 2 2
5 2 2 2
3 4 1 2
1 6 2```

### 输出

```
Case #1: 4
Case #2: Looks Good To Me
Case #3: 6```

# 题解

## 作者：Gszfzsf (赞：1)

# P13300 Are We Lost Yet? 题解

## 前言：

这道题思维很难，题意也很难理解，刚开始读了很久的题，对样例还是报有疑惑，但是理解题意后的代码并不难实现。**希望我的题解能对大家有所帮助。**

## 题目大意：

给出 $n$ 个点和 $m$ 条带权有向路径，但只说明边权值的上下界，随后指定 $p$ 条路径的编号。现求这 $p$ 条路径上第一个**肯定不属于**最短路的路径编号，有多组数据。

## 样例分析：

**为了方便理解我们摸走数据，多看样例来理解题目意思。**

### 样例 1:

输入：

```
1
4 5 3
1 2 100 1000
1 3 500 5000
3 2 400 600
3 4 500 5000
4 2 1 10000
2 4 5
```

输出：

```
Case #1: 4
```

我们画一个图：\
![](https://cdn.luogu.com.cn/upload/image_hosting/pb66qbvd.png)\
题目指定的路径是：$1\rightarrow3\rightarrow4\rightarrow2$。

假设所选路径价格均最优，它的花费是：$500+500+1=1001$。

考虑其他最短路径：

可以走 $1\rightarrow2$，此时最优花费为 $100$，最劣为 $1000$，肯定属于最短路。

也可以走 $1\rightarrow3\rightarrow2$，最优花费为 $900$，而最劣为 $1100$，也属于最短路的一种可能。

具体为什么分析中会讲。

---

### 样例 2:

输入：

```
1
6 8 4
1 5 3 15
3 2 1 1
5 2 4 5
1 6 10 20
4 2 6 15
2 3 1 1
1 4 2 5
6 2 10 20
4 8 6 2
```

输出：

```
Case #1 : 6
```

类似的，画一张图出来：

![](https://cdn.luogu.com.cn/upload/image_hosting/hty61xhg.png)\
这其实也算一个小 **Hack**，~~当时没过这个气笑了~~。

我们发现了一个很有意思的性质，指定的路径到了终点没有停下来，反而继续遍历了其他点。

所以这个样例输出的 $6$ 不难理解，走多余的路径**肯定不可能**是最短路。

# 解题思路：

## 思路分析：

### 对题意的深入转化：

转化为图论，就是想让我们求得指定路径的最长前缀，使得经过这个前缀仍有最短路。

---

### 样例中的关键点：

***问：路径最优和最劣是怎样计算的？第二条路径为什么仍然是最短路的一种呢？***

想要回答这些问题，首先有一个**前提**，我们所有的路径都是在**同一张图**上进行的。（敲黑板

什么意思？其实就是在边 $(1,3)$ 上，我们的权值不能既是最小也是最大值，算不同路径时，它的值永远是唯一的！

所以路径二会是已经取了最小权值的 $v_{1,3}$ 再加上 $v_{3,2}$。

其次，如果一条路径的最优值是短于最短路的，那么他就是可能的最短路，有点绕对吧？

因为这道题的**最短路定义不同于平常**，它指的是 **花费比从源点出发到终点所走边权除固定值外取最劣的最优路径更少** 的路径。（划重点

---

### 实现的思路：

***我们结合前面，拆开长难句再看看：***

因为我们想要确定的是最长前缀，那么假设我们前缀上的边权尽可能优，而其他边的尽可能劣是显然有利的。

最短路就是一条从源点到终点的路径，它的花费是路径上所有最劣花费，除了前缀上的路径应该保持无论如何都保持是最优值。

首先我们肯定有一个最短路的候选前缀，我们想判断它是否合法。

那么我们要求的就是从这个前缀的终点出发，每条边选取最优的权值，是否能不劣于上述最短路。

***这是一个典型的双机器人模型！***

设想一下，两个机器人试图尽快到达终点。

一个先沿着指定的路径从起点到前缀的终点，再尝试前往终点。我们称之为“好” 机器人，当这个机器人经过一条边时，它总是以最优的价格（这个机器人代表了我们希望构建的最短路径）。

另一个机器人从起点出发，试图通过其他路径到达终点。我们称之为“坏” 机器人，并会尝试迫使它尽可能劣势的前进，当这个机器人经过一条边时，它总是以最劣的价格。

问题就转化为我们是否能让“好” 机器人至少和“坏” 机器人一样快（“坏” 机器人显然可以通过简单地跟随“好” 机器人使得一样快）。

根据前面所提到的前提，相当于机器人每走一条边，就要确定一条边的边权，稍显麻烦。

***但是我们再转化一下呢？***

如果他们在不同的时间到达同一个节点，且最短路径包含该节点，则较早到达的机器人将始终击败另一个机器人。

因为它会始终遵循另一个机器人的路线（因为先到的机器人已经把所以连边更新完全了，两个机器人走向其他节点的时间是一样的）。

那么我们就可以看作两个机器人的**抢点争夺赛**！

共用同一组节点访问标记，则此时不会有两个机器人遍历同一条边！

***这样我们就可以共用一个 $dis$ 和 $vis$ 数组。且只用额外一个 $flag$ 标记维护抢点的结果，然后愉快的跑 Dijkstra 啦！***

## 具体实现：

***虽然上面讲了这么多，但是代码其实并不困难：***

**首先在输入数据时：**

```cpp
int idx[N];	 // 边编号对应链式前向星
inline void Insert(int x, int y, int l, int r, int id) {
	ll++;  // l 和 r 分别对应上下界
	Edge[ll] = {y, l, r, Link[x]};
	Link[x] = idx[id] = ll;	 // 将编号对应边
}
```

**然后我们从小往大枚举边集合的前缀：**

每次修改“好” 机器人初始花费，并且修改新的边的边权，直到“坏” 机器人抢到了终点。

这说明加入这条边后，“好” 机器人已经劣于“坏” 机器人了，那么这就是我们所找的那条边。

当然，如果追求程序效率，这里也可以使用二分路径前缀来求解。

不过一看 $p$ 才区区 $500$，懒狗作者选择更加方便的枚举了，大佬们可以自行尝试二分。

```cpp
int js() {
	int best = 0;  // 表示“好”机器人出发时的花费
	for (int i = 1; i <= p; i++) {
		int Eid = idx[pth[i]];		  // 找出当前对应的边的编号
		best += Edge[Eid].l;		  // “好”机器人的起始价值
		Edge[Eid].r = Edge[Eid].l;	  // 更改边的价值
		Dijkstra(Edge[Eid].y, best);  // 开始抢点
		if (!flag[Ed]) return i;	  // “坏”机器人抢到了终点
	}
	return -1;
}
```

**最后就是关键的 Dijkstra 了：**

和正常的区别只有几点：

1. 在开始时，同时加入两个机器人。

2. 在进行时，根据机器人的类型分配边权。

3. 如果两个机器人到达同一个节点的时间一样，“好” 机器人优先。

具体细节参考下面的代码。

```cpp
void Dijkstra(int Bs, int best) {
	// 这里写的堆优化Dijkstra
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	memset(flag, -1, sizeof(flag));	 // 初始化为 -1 表示没有抢点
	priority_queue<pair<int, int>, vector<pair<int, int> >,
				   greater<pair<int, int> > >
		Q;
	flag[St] = 0;
	dis[St] = 0;
	Q.push({dis[St], St});	// Worse Robot
	flag[Bs] = 1;
	dis[Bs] = best;
	Q.push({best, Bs});	 // Better Robot
	while (Q.empty() != true) {
		int dq = Q.top().second;
		Q.pop();
		if (vis[dq]) continue;
		vis[dq] = true;
		for (int i = Link[dq]; i; i = Edge[i].nxt) {
			int yy = Edge[i].y;
			// 根据机器人的不同分配路径权值
			int dt = ((flag[dq]) ? Edge[i].l : Edge[i].r);
			if (dis[yy] >= dis[dq] + dt) {
				// “好”机器人优先，所以一样时判“好”机器人抢点成功
				if (dis[yy] == dis[dq] + dt)
					flag[yy] |= flag[dq];  // 或运算实现
				else {
					// 机器人抢点
					flag[yy] = flag[dq];
					dis[yy] = dis[dq] + dt;
					Q.push({dis[yy], yy});
				}
			}
		}
	}
}
```

**时间复杂度：$O(T\times P\times N\log{N})$。**

**二分的话可以达到：$O(T\times \log{P}\times N\log{N})$。**

**空间复杂度：$O(N)$。**

**挺优秀的，可以通过此题！**

**而且数据还是比较水的。我总共不到 $100ms$。（喜**

# 完整代码：

下面给出完整代码，码风丑陋，大佬们看个思路就行。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 10007;
const int M = 20007;
const int St = 1;
const int Ed = 2;
int T, n, m, p;
int idx[N];	  // 边编号对应链式前向星
int pth[N];	  // 路径 pth[i] 指第i条路径是哪条边
int flag[N];  // “好”机器人和“坏”机器人抢点
int dis[N];	  // Dijkstra跑出来的最短路
int vis[N];	  // Dijkstra访问标记

// 链式前向星
int Link[N], ll;
struct edge {
	int y, l, r, nxt;
} Edge[M << 1];
inline void Insert(int x, int y, int l, int r, int id) {
	ll++;  // 存 x 是为了在枚举中找边的起点
	Edge[ll] = {y, l, r, Link[x]};
	Link[x] = idx[id] = ll;	 // 将编号对应边
}

// Dijkstra验证
void Dijkstra(int Bs, int best) {
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	memset(flag, -1, sizeof(flag));
	priority_queue<pair<int, int>, vector<pair<int, int> >,
				   greater<pair<int, int> > >
		Q;
	flag[St] = 0;
	dis[St] = 0;
	Q.push({dis[St], St});	// Worse Robot
	flag[Bs] = 1;
	dis[Bs] = best;
	Q.push({best, Bs});	 // Better Robot
	while (Q.empty() != true) {
		int dq = Q.top().second;
		Q.pop();
		if (vis[dq]) continue;
		vis[dq] = true;
		for (int i = Link[dq]; i; i = Edge[i].nxt) {
			int yy = Edge[i].y;
			// 根据机器人的不同分配路径权值
			int dt = ((flag[dq]) ? Edge[i].l : Edge[i].r);
			if (dis[yy] >= dis[dq] + dt) {
				// “好”机器人优先，所以一样时判“好”机器人抢点成功
				if (dis[yy] == dis[dq] + dt)
					flag[yy] |= flag[dq];
				else {
					// 机器人抢点
					flag[yy] = flag[dq];
					dis[yy] = dis[dq] + dt;
					Q.push({dis[yy], yy});
				}
			}
		}
	}
}

// 枚举边
int js() {
	int best = 0;  // 表示“好”机器人出发时的花费
	for (int i = 1; i <= p; i++) {
		int Eid = idx[pth[i]];
		best += Edge[Eid].l;
		Edge[Eid].r = Edge[Eid].l;
		Dijkstra(Edge[Eid].y, best);
		if (!flag[Ed]) return i;
	}
	return -1;
}

// 解决问题的函数
void solve(int id) {
	cin >> n >> m >> p;
	ll = 0;
	memset(idx, 0, sizeof(id));
	memset(Link, 0, sizeof(Link));
	for (int i = 1; i <= m; i++) {
		int x, y, l, r;
		cin >> x >> y >> l >> r;
		Insert(x, y, l, r, i);
	}
	for (int i = 1; i <= p; i++) cin >> pth[i];
	int ans = js();	 // 返回-1表示是优秀的路径
	cout << "Case #" << id << ": ";
	if (~ans)
		cout << pth[ans] << '\n';
	else
		cout << "Looks Good To Me\n";
	return;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;  // 多测一定要清空
	for (int id = 1; id <= T; id++) solve(id);
	return 0;
}
```

**好了，到此结束了（逃**

---

