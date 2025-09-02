# 题目信息

# Network Topology

## 题目描述

This problem uses a simplified network topology model, please read the problem statement carefully and use it as a formal document as you develop the solution.

Polycarpus continues working as a system administrator in a large corporation. The computer network of this corporation consists of $ n $ computers, some of them are connected by a cable. The computers are indexed by integers from $ 1 $ to $ n $ . It's known that any two computers connected by cable directly or through other computers

Polycarpus decided to find out the network's topology. A network topology is the way of describing the network configuration, the scheme that shows the location and the connections of network devices.

Polycarpus knows three main network topologies: bus, ring and star. A bus is the topology that represents a shared cable with all computers connected with it. In the ring topology the cable connects each computer only with two other ones. A star is the topology where all computers of a network are connected to the single central node.

Let's represent each of these network topologies as a connected non-directed graph. A bus is a connected graph that is the only path, that is, the graph where all nodes are connected with two other ones except for some two nodes that are the beginning and the end of the path. A ring is a connected graph, where all nodes are connected with two other ones. A star is a connected graph, where a single central node is singled out and connected with all other nodes. For clarifications, see the picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF292B/4b8e00a09b5404153c7328227c396879fd344c8f.png)(1) — bus, (2) — ring, (3) — starYou've got a connected non-directed graph that characterizes the computer network in Polycarpus' corporation. Help him find out, which topology type the given network is. If that is impossible to do, say that the network's topology is unknown.

## 样例 #1

### 输入

```
4 3
1 2
2 3
3 4
```

### 输出

```
bus topology
```

## 样例 #2

### 输入

```
4 4
1 2
2 3
3 4
4 1
```

### 输出

```
ring topology
```

## 样例 #3

### 输入

```
4 3
1 2
1 3
1 4
```

### 输出

```
star topology
```

## 样例 #4

### 输入

```
4 4
1 2
2 3
3 1
1 4
```

### 输出

```
unknown topology
```

# AI分析结果



# Network Topology

## 题目描述

本题使用简化的网络拓扑模型，请仔细阅读题目说明并按正式文档要求开发解决方案。

Polycarpus 继续在一家大型公司担任系统管理员。该公司的计算机网络由 $n$ 台计算机组成，部分计算机通过电缆连接。计算机编号为 $1$ 到 $n$。已知任意两台计算机都可以直接或通过其他计算机间接连接。

Polycarpus 希望确定网络的拓扑类型。网络拓扑主要分为三种类型：总线型、环形和星型。具体定义为：

- **总线型**：所有节点形成一条链，其中仅有两个端点节点的度数为 1，其他节点度数为 2
- **环形**：所有节点构成环，每个节点的度数均为 2
- **星型**：存在一个中心节点连接所有其他节点，中心节点度数为 $n-1$，其他节点度数为 1

给定一个连通无向图，判断其拓扑类型，若不符合上述任一类型则输出"unknown topology"。

## 样例输入输出

样例 #1 输入：
```
4 3
1 2
2 3
3 4
```
输出：
```
bus topology
```

样例 #2 输入：
```
4 4
1 2
2 3
3 4
4 1
```
输出：
```
ring topology
```

样例 #3 输入：
```
4 3
1 2
1 3
1 4
```
输出：
```
star topology
```

---

**算法分类**：图论

---

### 精选题解分析

#### 题解作者：sto__Liyhzh__orz（★★★★★）
**核心思路**：
1. 统计每个节点的度数
2. 分别验证三种拓扑结构的度数特征：
   - 总线型：恰好 2 个度数为 1 的节点，其余均为 2
   - 环形：所有节点度数均为 2
   - 星型：1 个节点度数为 $n-1$，其他均为 1

**代码亮点**：
```cpp
bool bus() {
    int cnt1 = 0;
    for(int i=1; i<=n; i++) {
        if(a[i].size() >= 3) return false;
        if(a[i].size() == 1) cnt1++;
    }
    return cnt1 == 2;
}

bool ring() {
    for(int i=1; i<=n; i++)
        if(a[i].size() != 2) return false;
    return true;
}

bool star() {
    int center = 0;
    for(int i=1; i<=n; i++) {
        if(a[i].size() == n-1) center++;
        else if(a[i].size() != 1) return false;
    }
    return center == 1;
}
```

---

#### 题解作者：Citlali_qwq（★★★★☆）
**核心思路**：
- 使用桶排序统计不同度数的节点数量
- 通过预计算度数为1、2、$n-1$ 的节点数直接判断

**代码亮点**：
```cpp
int cnt1 = 0, cnt2 = 0, cntn = 0;
for(int i=1; i<=n; i++) {
    if(deg[i] == 1) cnt1++;
    else if(deg[i] == 2) cnt2++;
    else if(deg[i] == n-1) cntn++;
}

if(cnt1 == 2 && cnt2 == n-2) cout << "bus topology";
else if(cnt2 == n) cout << "ring topology";
else if(cntn == 1 && cnt1 == n-1) cout << "star topology";
```

---

#### 题解作者：wang_freedom（★★★★☆）
**核心实现技巧**：
- 直接遍历邻接表统计度数
- 使用简洁的条件判断链式结构

**关键代码**：
```cpp
int cnt1 = 0, cnt2 = 0;
for(int i=1; i<=n; i++) {
    if(e[i].size() == 1) cnt1++;
    if(e[i].size() == 2) cnt2++;
}

if(cnt1 == 2 && cnt2 == n-2) cout << "bus topology";
```

---

### 关键思路总结
1. **度数特征法**：所有拓扑类型均可通过节点度数分布判断
2. **优化验证顺序**：优先检查星型（存在唯一 $n-1$ 度节点）可减少计算量
3. **边界处理**：注意当 $n=2$ 时总线型与环形的兼容情况

---

### 拓展练习
1. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)（图的遍历与距离分析）
2. [P2921 Trick or Treat on the Farm](https://www.luogu.com.cn/problem/P2921)（基环树结构判断）
3. [P2661 信息传递](https://www.luogu.com.cn/problem/P2661)（最小环检测）

---
处理用时：58.68秒