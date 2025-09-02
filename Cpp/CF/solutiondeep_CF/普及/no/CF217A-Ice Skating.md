# 题目信息

# Ice Skating

## 题目描述

Bajtek is learning to skate on ice. He's a beginner, so his only mode of transportation is pushing off from a snow drift to the north, east, south or west and sliding until he lands in another snow drift. He has noticed that in this way it's impossible to get from some snow drifts to some other by any sequence of moves. He now wants to heap up some additional snow drifts, so that he can get from any snow drift to any other one. He asked you to find the minimal number of snow drifts that need to be created.

We assume that Bajtek can only heap up snow drifts at integer coordinates.

## 样例 #1

### 输入

```
2
2 1
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
2 1
4 1
```

### 输出

```
0
```

# AI分析结果



# 中文题目重写

## 题目：滑冰

### 题目描述

Bajtek 正在学习滑冰。他是个初学者，唯一移动方式是从某个雪堆向北、东、南或西方向滑行，直到到达另一个雪堆。他发现通过这种方式，有些雪堆之间无法互相到达。现在他想添加最少数量的新雪堆，使得所有雪堆之间都能互相到达。请计算需要添加的最小雪堆数量。

雪堆只能建立在整数坐标处。

## 输入格式

输入第一行包含整数 $n$ (雪堆数量)，接下来 $n$ 行每行给出雪堆的坐标 $(x,y)$。

## 输出格式

输出需要添加的最小雪堆数。

## 样例 #1

### 输入
```
2
2 1
1 2
```

### 输出
```
1
```

## 样例 #2

### 输入
```
2
2 1
4 1
```

### 输出
```
0
```

---

### 算法分类
并查集 或 图论（连通块）

---

## 题解分析与结论

### 核心思路对比
所有题解均将问题转化为连通块计数问题，主要分为两类方法：
1. **并查集**：通过坐标关系建立等价类，最终连通块数-1即为答案（9篇使用）
2. **DFS/BFS**：通过深度/广度优先搜索计算连通块数量（3篇使用）

### 解决难点
1. **坐标关系建模**：将二维坐标的连通性转化为一维集合关系
2. **高效合并**：通过并查集的路径压缩优化，或DFS的邻接关系预处理
3. **连通块计数**：最终统计独立子图的数量

---

## 优质题解推荐

### 1. Edmundino（4星）
**核心亮点**：
- 完整并查集模板实现
- 详细注释路径压缩过程
- 代码结构清晰易扩展

```cpp
int find(int x) {
    if(x != father[x])
        father[x] = find(father[x]); // 路径压缩
    return father[x];
}

// 合并处理逻辑
for(int i=1; i<=n; i++) {
    for(int j=i+1; j<=n; j++) {
        if(x[i]==x[j] || y[i]==y[j]) {
            int q=find(i), p=find(j);
            if(q != p) father[p] = q;
        }
    }
}
```

### 2. EuphoricStar（4星）
**核心亮点**：
- 使用set去重统计连通块
- 边输入边合并的优化处理
- 清晰的代码组织结构

```cpp
for(int i=1; i<=n; ++i) {
    scanf("%d%d", &pts[i].x, &pts[i].y);
    for(int j=1; j<i; ++j) { // 边输入边处理
        if(pts[j].x == pts[i].x || pts[j].y == pts[i].y) {
            int a = find(i), b = find(j);
            if(a != b) parent[a] = b;
        }
    }
}
```

### 3. Ptilopsis_w（3.5星）
**BFS实现亮点**：
- 结构体封装坐标信息
- 显式队列操作过程
- 适合理解图论基础

```cpp
void bfs(int s) {
    queue<node> q;
    q.push({x[s], y[s], s});
    while(!q.empty()) {
        node a = q.front(); q.pop();
        if(vis[a.i]) continue;
        vis[a.i] = true;
        for(int i=1; i<=n; i++) {
            if(!vis[i] && (x[i]==a.x || y[i]==a.y)) 
                q.push({x[i], y[i], i});
        }
    }
}
```

---

## 关键思路总结
1. **连通性转换**：将二维坐标的连通条件（同行/列）转化为图论边关系
2. **集合合并优化**：使用路径压缩的并查集实现O(α(n))的高效合并
3. **结果推导**：最终答案 = 连通块数 - 1，本质是构造最小生成树边数

---

## 同类题目推荐
1. [P1536 村村通](https://www.luogu.com.cn/problem/P1536) - 并查集基础应用
2. [P2330 繁忙的都市](https://www.luogu.com.cn/problem/P2330) - 最小生成树变形
3. [P1197 星球大战](https://www.luogu.com.cn/problem/P1197) - 逆向并查集应用

---

## 题解心得摘录
1. **灵光一闪**：尝试两种DFS实现后发现，虽然理论上遍历整个坐标系的实现更直观，但实际效率低于基于输入点的处理
2. **Edmundino**：强调并查集路径压缩的关键性，通过递归实现简洁的路径压缩
3. **Ptilopsis_w**：在BFS实现中特别指出结构体封装坐标的必要性，便于处理多维数据

---
处理用时：66.39秒