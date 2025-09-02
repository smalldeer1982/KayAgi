# [JDWOI-2] 抢救实验数据

## 题目背景

某大型实验中心的一个实验室发生了毒气泄露，现在实验员想要抢救实验数据。

## 题目描述

实验中心可以看做一个 $n$ 个点 $m$ 条边的无向联通图。  
所有实验员每秒可以走到一个相邻的实验室并**收集**其中的数据，毒气每秒会蔓延到所有的相邻实验室。
当一个实验员**回到了大厅 $s$**，我们称他**抢救**了数据。  
实验员不能进入有毒气的实验室（如果他和毒气在同一秒进入实验室也不行）。  
**大厅周围有严格的保护措施，不会被毒气蔓延。（具体可以参考样例二）**  
现在所有实验员都在大厅 $s$，毒气泄露的实验室为点 $t$。假如有**足够多**的实验员同时出发，请问最多能抢救多少个实验室的数据？

## 说明/提示

**请注意常数因子带来的程序效率上的影响。**

【样例解释一】  
只有 2 号实验室可以到达并回来。

【样例解释二】  
因为大厅是坚不可摧的，所以 5,6 两个实验室会被毒气蔓延到，而 2,3 两个实验室永远不会被蔓延到。

【样例解释三】  
可以被抢救的点为：2,3,4,5,11,12。

【数据范围】  
**本题采用捆绑测试**。  
对于 $10\%$ 的数据，$2 \leq n,m \leq 20$；  
对于 $30\%$ 的数据，$2 \leq n \leq 2000,1 \leq m \leq 10000$；  
对于 $70\%$ 的数据，$2 \leq n \leq 2 \times 10^5$；  
对于 $100\%$ 的数据，$2 \leq n,m \leq 5 \times 10^6$。

由于读入量很大，这里提供 std 使用的快读模板（提交时需要选择 C++11 及以上)
```cpp
char gc() {
  static char now[1 << 20], *S, *T;
  if (T == S) {
    T = (S = now) + std::fread(now, 1, 1 << 20, stdin);
    if (T == S) return EOF;
  }
  return *S++;
}
template <typename T>
void Read(T &x) {
  x = 0;
  char c = gc();
  while (c < '0' || c > '9') c = gc();
  x = c - '0';
  while ((c = gc()) >= '0' && c <= '9') x = x * 10 + c - '0';
}
template <typename T, typename... Args>
void Read(T &x, Args &... args) {
  Read(x);
  Read(args...);
}
```
使用方法：`Read(n, m)` 或 `Read(x, y, z)` 等，可以读入任意个数，但是不能与 `std::cin` 和 `std::scanf` 一起使用。读入完成后 Windows 系统按 Ctrl+Z，Linux 系统按 Ctrl+D 结束。

## 样例 #1

### 输入

```
4 3
1 2
2 3
3 4
1 4```

### 输出

```
1```

## 样例 #2

### 输入

```
6 7
1 2
2 3
3 1
4 5
5 6
6 4
1 4
1 4```

### 输出

```
2```

## 样例 #3

### 输入

```
15 14
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
3 11
11 12
12 13
13 14
14 15
1 10```

### 输出

```
6```

# 题解

## 作者：xyf007 (赞：7)

出题人的官方题解

看到这道题可能会有一些错误的想法，典型的就是来回都走最短路，但实际上到一个点去时走最短路，回来则不一定。如下图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/5gsdemgy.png)

1 号点是起点，8 号点是毒气点，可以到达的点为 1~6。

---
首先 BFS 求出每个点到起点和泄露点的距离。简单的想法是暴力枚举每一个点 BFS 看能否回到起点，复杂度 $O(n^2)$，可以拿到 30 分。

我们令 $t_x$ 表示能够回到起点到达 $x$ 点的最晚时间，那么起点相邻的点都是它们到毒气点的距离。对于其他的点 $u$ 有 $t_u=\max\limits_{(u,v) \in E}(t_v)-1$。  
把所有起点相邻的点放进一个堆，用一个优先队列 BFS，每个点 $x$ 第一次被更新的时候就得到了 $t_x$，复杂度 $O(n \log n)$，可以获得 70 分。  
然后你会发现 $t_x \leq n$，并且堆中 $t$ 的最大值单调不增，所以可以用一个 `std::vector` 来代替这个堆，复杂度 $O(n+m)$，可以通过此题。
```cpp
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>
struct Edge {
  int to, nxt;
} e[10000001];
int n, m, E, head[5000001], s, t, dis[5000001], h[5000001];
std::vector<int> q2[5000001];
bool vis[5000001];
class Queue {
 public:
  Queue() { head_ = tail_ = 0; }
  bool Empty() { return head_ == tail_; }
  void Clear() { head_ = tail_ = 0; }
  void Push(int x) { a_[tail_++] = x; }
  int Front() { return a_[head_]; }
  void Pop() { head_++; }
  ~Queue() {}

 private:
  int head_, tail_, a_[5000001];
} q;
char gc() {
  static char now[1 << 20], *S, *T;
  if (T == S) {
    T = (S = now) + std::fread(now, 1, 1 << 20, stdin);
    if (T == S) return EOF;
  }
  return *S++;
}
template <typename T>
void Read(T &x) {
  x = 0;
  char c = gc();
  while (c < '0' || c > '9') c = gc();
  x = c - '0';
  while ((c = gc()) >= '0' && c <= '9') x = x * 10 + c - '0';
}
template <typename T, typename... Args>
void Read(T &x, Args &... args) {
  Read(x);
  Read(args...);
}
void checkmax(int &x, int y) {
  if (x < y) x = y;
}
void checkmin(int &x, int y) {
  if (x > y) x = y;
}
void Add(int f, int t) {
  e[E].to = t;
  e[E].nxt = head[f];
  head[f] = E++;
}
int main(int argc, char const *argv[]) {
  std::memset(head, -1, sizeof(head));
  Read(n, m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    Read(u, v);
    Add(u, v);
    Add(v, u);
  }
  Read(s, t);
  std::memset(dis, 0x3f, sizeof(dis));
  dis[s] = 0;
  q.Push(s);
  vis[s] = true;
  while (!q.Empty()) {
    int u = q.Front();
    q.Pop();
    for (int i = head[u]; i != -1; i = e[i].nxt) {
      int v = e[i].to;
      if (vis[v]) continue;
      dis[v] = dis[u] + 1;
      q.Push(v);
      vis[v] = true;
    }
  }
  std::memset(h, 0x3f, sizeof(h));
  std::memset(vis, false, sizeof(vis));
  q.Clear();
  q.Push(t);
  h[t] = 0;
  vis[t] = true;
  while (!q.Empty()) {
    int u = q.Front();
    q.Pop();
    for (int i = head[u]; i != -1; i = e[i].nxt) {
      int v = e[i].to;
      if (vis[v] || v == s) continue;
      h[v] = h[u] + 1;
      q.Push(v);
      vis[v] = true;
    }
  }
  std::memset(vis, false, sizeof(vis));
  vis[s] = true;
  int max = 0;
  for (int i = head[s]; i != -1; i = e[i].nxt) {
    int v = e[i].to;
    if (h[v] > 5000000) continue;
    q2[h[v]].emplace_back(v);
    checkmax(max, h[v]);
    vis[v] = true;
  }
  for (int i = max; i >= 1; i--)
    for (auto &&u : q2[i])
      for (int j = head[u]; j != -1; j = e[j].nxt) {
        int v = e[j].to;
        if (vis[v]) continue;
        checkmin(h[v], h[u] - 1);
        vis[v] = true;
        q2[h[v]].emplace_back(v);
      }
  int ans = 0;
  for (int i = 1; i <= n; i++)
    ans += (vis[i] || h[i] == 0x3f3f3f3f) && (dis[i] < h[i]);
  std::cout << ans - 1;
  return 0;
}
```

---

