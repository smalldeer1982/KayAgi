# 题目信息

# PackDrop

## 题目描述

# PackDrop


[问题链接](https://atcoder.jp/contests/tenka1-2016-quala/tasks/tenka1_2016_qualA_b)

山本同学发明了一种名为 PackDrop 的设备，它有 $0.01$ 的概率丢弃数据包，用于在通信环境不佳的网络中验证应用程序的运行。

山本同学需要在由 $N$ 台设备组成的网络中安装一些 PackDrop，以满足以下条件。并且，他希望使用的 PackDrop 的数量最少。

这个网络中的每个设备都有一个从 $0$ 到 $N-1$ 的编号。

除设备 $0$ 外，每个设备都有一个父设备，设备 $i$ 的父设备是设备 $P_i$。设备 $P_i$ 被称为设备 $i$ 的子设备。

直接具有父子关系的设备可以直接连接，或者通过串联几个 PackDrop 来连接。

当父设备和子设备之间有 $n$ 个 PackDrop 时，从父设备到子设备的数据包到达率为 $0.99^n$。换句话说，直接连接时，数据包到达率为 $1$。

设设备 $x$ 到设备 $y$ 的数据包到达率为 $p$，设备 $y$ 到设备 $z$ 的数据包到达率为 $q$，则设备 $x$ 到设备 $z$ 的数据包到达率为 $p × q$。

除了 PackDrop 丢弃数据包外，没有其他因素会影响数据包的到达率。

没有子设备的设备共有 $M$ 台，它们的编号为 $B_0, B_1, \ldots, B_{M-1}$。对于每个 $i$ ($0 \leq i \leq N-1$)，当希望设备 $0$ 到设备 $B_i$ 的到达率为 $0.99^{C_i}$ 时，求出最少需要的 PackDrop 数量。

## 说明/提示

### 约束条件

- $2 \leq N \leq 1000$
- $1 \leq M \leq N - 1$
- $0 \leq P_i \leq i - 1$
- $1 \leq B_i \leq N - 1$
- $1 \leq C_i \leq 100000$
- 如果 $i \neq j$，则 $B_i \neq B_j$。
- 存在 $i, j$ 使得 $P_i = B_j$。
- 整数 $k$ ($1 \leq k \leq N - 1$) 如果不在 $P_1, P_2, \ldots, P_{N-1}$ 中，则它一定在 $B_0, B_1, \ldots, B_{M-1}$ 中。
- $N, M, P_i, B_i, C_i$ 均为整数。

## 样例 #1

### 输入

```
3 2
0
0
1 5
2 10```

### 输出

```
15```

## 样例 #2

### 输入

```
5 3
0
1
0
1
2 5
3 3
4 7```

### 输出

```
10```

## 样例 #3

### 输入

```
7 4
0
0
2
2
3
3
1 3
4 2
5 8
6 6```

### 输出

```
11```

# AI分析结果



# PackDrop

## 题目描述

山本同学发明了一种名为 PackDrop 的设备，它有 0.01 的概率丢弃数据包，用于在通信环境不佳的网络中验证应用程序的运行。

山本同学需要在由 $N$ 台设备组成的网络中安装一些 PackDrop，以满足以下条件，并且希望使用的 PackDrop 数量最少。

网络中的每个设备都有一个从 $0$ 到 $N-1$ 的编号。除设备 $0$ 外，每个设备都有一个父设备 $P_i$。父设备与子设备之间可以通过直接连接或串联 PackDrop 连接。当父设备和子设备之间有 $n$ 个 PackDrop 时，数据包到达率为 $0.99^n$。

给定 $M$ 个无子设备的终端设备 $B_0, B_1, \ldots, B_{M-1}$，要求从设备 $0$ 到 $B_i$ 的到达率为 $0.99^{C_i}$，求最少需要的 PackDrop 数量。

---

**算法分类**：贪心

---

### 题解分析与结论

#### 关键思路
1. **树形结构建模**：将设备网络视为树结构，根节点为设备 0。每个非叶子节点的 PackDrop 数量由其子节点的约束决定。
2. **后序遍历贪心**：自底向上计算每个节点到根路径的最小 PackDrop 总数。非叶子节点的值取子节点最小值，确保父边 PackDrop 数量最小。
3. **动态累加**：每条边的 PackDrop 数为其节点值与父节点值的差，总和即为答案。

#### 最优代码核心逻辑
```python
n, m = map(int, input().split())
children = [[] for _ in range(n)]
parent = [0] * n
for i in range(1, n):
    p = int(input())
    parent[i] = p
    children[p].append(i)

leaves = set()
c = [0] * n
for _ in range(m):
    b_i, c_i = map(int, input().split())
    leaves.add(b_i)
    c[b_i] = c_i

d = [0] * n
# 后序遍历计算每个节点的 d 值
stack = [(0, False)]
while stack:
    u, visited = stack.pop()
    if not visited:
        stack.append((u, True))
        for v in reversed(children[u]):
            stack.append((v, False))
    else:
        if u in leaves:
            d[u] = c[u]
        else:
            min_d = min(d[v] for v in children[u])
            d[u] = min_d

total = 0
for u in range(1, n):
    total += d[u] - d[parent[u]]
print(total)
```

#### 题解亮点
- **贪心策略**：通过后序遍历确保子节点先处理，父节点取子节点最小值，保证全局最优。
- **简洁高效**：时间复杂度 $O(N)$，完美处理树结构约束。

---

### 类似题目推荐
1. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)  
   **考察点**：树形结构遍历与动态规划结合。
2. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)  
   **考察点**：树形 DP 与边权约束处理。
3. [P3177 树上染色](https://www.luogu.com.cn/problem/P3177)  
   **考察点**：贪心策略在树形结构中的组合优化应用。

---
处理用时：295.13秒