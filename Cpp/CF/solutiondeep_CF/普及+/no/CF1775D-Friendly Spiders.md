# 题目信息

# Friendly Spiders

## 题目描述

Mars is home to an unusual species of spiders — Binary spiders.

Right now, Martian scientists are observing a colony of $ n $ spiders, the $ i $ -th of which has $ a_i $ legs.

Some of the spiders are friends with each other. Namely, the $ i $ -th and $ j $ -th spiders are friends if $ \gcd(a_i, a_j) \ne 1 $ , i. e., there is some integer $ k \ge 2 $ such that $ a_i $ and $ a_j $ are simultaneously divided by $ k $ without a remainder. Here $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

Scientists have discovered that spiders can send messages. If two spiders are friends, then they can transmit a message directly in one second. Otherwise, the spider must pass the message to his friend, who in turn must pass the message to his friend, and so on until the message reaches the recipient.

Let's look at an example.

Suppose a spider with eight legs wants to send a message to a spider with $ 15 $ legs. He can't do it directly, because $ \gcd(8, 15) = 1 $ . But he can send a message through the spider with six legs because $ \gcd(8, 6) = 2 $ and $ \gcd(6, 15) = 3 $ . Thus, the message will arrive in two seconds.

Right now, scientists are observing how the $ s $ -th spider wants to send a message to the $ t $ -th spider. The researchers have a hypothesis that spiders always transmit messages optimally. For this reason, scientists would need a program that could calculate the minimum time to send a message and also deduce one of the optimal routes.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775D/cbd40cc2068feef6a151db4f398da64f76e37f80.png)

## 说明/提示

The first example is shown above. It shows that the message from the $ 5 $ -th spider (with eight legs) to the $ 6 $ -th spider (with $ 15 $ legs) is optimal to pass through the $ 4 $ -th spider (with six legs).

In the second example, the spider number $ 7 $ (with $ 11 $ legs) is not friends with anyone, so it is impossible to send him a message.

## 样例 #1

### 输入

```
7
2 14 9 6 8 15 11
5 6```

### 输出

```
3
5 4 6```

## 样例 #2

### 输入

```
7
2 14 9 6 8 15 11
5 7```

### 输出

```
-1```

## 样例 #3

### 输入

```
7
2 14 9 6 8 15 11
5 5```

### 输出

```
1
5```

# AI分析结果

### 题目重写
**题目名称：友好的蜘蛛**

**题目描述：**

火星上生活着一种特殊的蜘蛛——二进制蜘蛛。

现在，火星科学家正在观察一个由 $n$ 只蜘蛛组成的群体，其中第 $i$ 只蜘蛛有 $a_i$ 条腿。

某些蜘蛛之间是朋友关系。具体来说，第 $i$ 只和第 $j$ 只蜘蛛是朋友，当且仅当 $\gcd(a_i, a_j) \ne 1$，即存在某个整数 $k \ge 2$，使得 $a_i$ 和 $a_j$ 都能被 $k$ 整除。这里 $\gcd(x, y)$ 表示整数 $x$ 和 $y$ 的最大公约数。

科学家发现蜘蛛可以传递消息。如果两只蜘蛛是朋友，那么它们可以直接在一秒钟内传递消息。否则，蜘蛛必须将消息传递给它的朋友，朋友再传递给它的朋友，依此类推，直到消息到达接收者。

例如，假设一只拥有 8 条腿的蜘蛛想要向一只拥有 15 条腿的蜘蛛发送消息。它不能直接发送，因为 $\gcd(8, 15) = 1$。但它可以通过拥有 6 条腿的蜘蛛发送消息，因为 $\gcd(8, 6) = 2$ 且 $\gcd(6, 15) = 3$。因此，消息将在两秒钟内到达。

现在，科学家正在观察第 $s$ 只蜘蛛想要向第 $t$ 只蜘蛛发送消息。研究人员假设蜘蛛总是以最优方式传递消息。因此，科学家需要一个程序来计算传递消息的最短时间，并推导出其中一条最优路径。

**输入格式：**

第一行包含一个整数 $n$，表示蜘蛛的数量。

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$，表示每只蜘蛛的腿数。

第三行包含两个整数 $s$ 和 $t$，表示消息的起点和终点。

**输出格式：**

如果消息可以传递，则第一行输出最短时间，第二行输出一条最优路径。如果消息无法传递，则输出 `-1`。

**样例输入 1：**
```
7
2 14 9 6 8 15 11
5 6
```

**样例输出 1：**
```
3
5 4 6
```

**样例输入 2：**
```
7
2 14 9 6 8 15 11
5 7
```

**样例输出 2：**
```
-1
```

**样例输入 3：**
```
7
2 14 9 6 8 15 11
5 5
```

**样例输出 3：**
```
1
5
```

### 算法分类
**图论、最短路**

### 题解分析与结论
本题的核心是通过构建图模型来求解最短路径问题。由于直接建图的时间复杂度较高，因此大多数题解都采用了质因数分解的方法，通过质因数作为中间节点来优化图的构建和搜索过程。

### 精选题解
#### 1. 作者：Ray1 (赞：30)
**星级：5星**
**关键亮点：**
- 通过质因数分解优化建图，将时间复杂度从 $O(n^2\log a)$ 降低到 $O(n\log^2a)$。
- 使用虚点连接起点和终点的质因数，简化了 BFS 的实现。
- 详细解释了如何通过 BFS 记录路径，并输出最优路径。

**核心代码：**
```cpp
// 质因数分解并建图
for (int i = 1; i <= n; i++) {
    int x = a[i];
    for (int j = 2; j * j <= x; j++) {
        if (x % j == 0) {
            while (x % j == 0) x /= j;
            g[i].pb({j + N, 1});
            g[j + N].pb({i, 0});
        }
    }
    if (x != 1) {
        g[i].pb({x + N, 1});
        g[x + N].pb({i, 0});
    }
}
// BFS 求解最短路
priority_queue<pii, vector<pii>, greater<pii>> q;
memset(dis, 0x3f, sizeof(dis));
dis[st] = 0;
q.push({0, st});
while (!q.empty()) {
    int x = q.top().sec, d = q.top().fir;
    q.pop();
    if (dis[x] < d) continue;
    if (x == en) break;
    for (auto v : g[x]) {
        if (dis[v.fir] > dis[x] + v.sec) {
            dis[v.fir] = dis[x] + v.sec;
            fa[v.fir] = x;
            q.push({dis[v.fir], v.fir});
        }
    }
}
```

#### 2. 作者：Mine_King (赞：2)
**星级：4星**
**关键亮点：**
- 通过质因数作为虚点，优化了图的构建，减少了边数。
- 使用 BFS 求解最短路，并记录路径。
- 代码简洁，易于理解。

**核心代码：**
```cpp
// 质因数分解并建图
for (int i = 1; i <= n; i++) {
    int x = a[i];
    for (int j = 2; j * j <= x; j++) {
        if (x % j == 0) {
            while (x % j == 0) x /= j;
            g.add(i, n + j);
            g.add(n + j, i);
        }
    }
    if (x != 1) {
        int pos = lower_bound(prime + 1, prime + cnt + 1, x) - prime;
        g.add(i, n + pos);
        g.add(n + pos, i);
    }
}
// BFS 求解最短路
memset(dis, -1, sizeof(dis));
q.push(s);
dis[s] = 0;
while (!q.empty()) {
    int now = q.front(); q.pop();
    for (int i = g.hd[now]; i; i = g.nxt[i]) {
        if (dis[g.to[i]] == -1) {
            dis[g.to[i]] = dis[now] + 1;
            pre[g.to[i]] = now;
            q.push(g.to[i]);
        }
    }
}
```

#### 3. 作者：happybob (赞：3)
**星级：4星**
**关键亮点：**
- 通过质因数分解优化建图，减少了边数。
- 使用 BFS 求解最短路，并记录路径。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
// 质因数分解并建图
for (int i = 1; i <= n; i++) {
    int rr = a[i], p = a[i];
    for (int j = 2; j * j <= rr; j++) {
        int c = 0;
        while (p % j == 0) {
            c++;
            p /= j;
        }
        if (c) {
            int nx = id[j] == 0 ? (id[j] = ++idx) : id[j];
            G[i].emplace_back(nx);
            G[nx].emplace_back(i);
        }
    }
    if (p > 1) {
        int c = p;
        int nx = id[c] == 0 ? (id[c] = ++idx) : id[c];
        G[i].emplace_back(nx);
        G[nx].emplace_back(i);
    }
}
// BFS 求解最短路
queue<int> q;
memset(dis, 0x7f, sizeof dis);
dis[s] = 0;
q.push(s);
while (q.size()) {
    int u = q.front();
    q.pop();
    for (int j : G[u]) {
        if (dis[j] == dis[0]) {
            dis[j] = dis[u] + 1;
            q.push(j);
            from[j] = u;
        }
    }
}
```

### 最优关键思路
通过质因数分解优化建图，将蜘蛛之间的连接关系转化为质因数之间的连接关系，从而大大减少了图的边数。通过 BFS 求解最短路，并记录路径，最终输出最优路径。

### 可拓展之处
类似的问题可以通过质因数分解或其他数学优化方法来减少图的复杂度，例如在求解最大公约数、最小公倍数等问题时，质因数分解常常是一个有效的优化手段。

### 推荐题目
1. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)
2. [P3376 【模板】网络最大流](https://www.luogu.com.cn/problem/P3376)
3. [P3381 【模板】最小费用最大流](https://www.luogu.com.cn/problem/P3381)

---
处理用时：73.55秒