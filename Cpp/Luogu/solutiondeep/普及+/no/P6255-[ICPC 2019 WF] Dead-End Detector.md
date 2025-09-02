# 题目信息

# [ICPC 2019 WF] Dead-End Detector

## 题目背景

### Warning: If you submit a malicious program, you will be banned.
### 警告：恶意提交本题将被封号。


## 题目描述

The council of your home town has decided to improve road sign placement,especially for dead ends. They have given you a road map, and you must determine where to put up signs to mark the dead ends. They want you to use as few signs as possible.

The road map is a collection of locations connected by two-way streets. The following rule describes how to obtain a complete placement of dead-end signs. Consider a street $S$ connecting a location $x$ with another location. The $x$-entrance of $S$ gets a dead-end sign if, after entering $S$ from $x$, it is not possible to come back to $x$ without making a U-turn. A U-turn is a 180-degree turn immediately reversing the direction.

To save costs, you have decided not to install redundant dead-end signs, as specified by the following rule. Consider a street $S$ with a dead-end sign at its $x$-entrance and another street $T$ with a dead-end sign at its $y$-entrance. If, after entering $S$ from $x$, it is possible to go to $y$ and enter $T$ without making a U-turn, the dead-end sign at the $y$-entrance of $T$ is redundant. See Figure E.1 for examples.

![](https://cdn.luogu.com.cn/upload/image_hosting/33rn5okp.png)

Figure E.1: Illustration of sample inputs, indicating where non-redundant dead-end signs are placed.


## 说明/提示

Source: ICPC World Finals 2019 Problem E.

## 样例 #1

### 输入

```
6 5
1 2
1 3
2 3
4 5
5 6
```

### 输出

```
2
4 5
6 5```

## 样例 #2

### 输入

```
8 8
1 2
1 3
2 3
3 4
1 5
1 6
6 7
6 8
```

### 输出

```
3
1 5
1 6
3 4
```

# AI分析结果



**算法分类**: 图论

---

### 综合分析与结论
题目核心是识别图中满足特定条件的死路。各解法的共同思路是将问题转化为图论中的环检测与树结构分析，通过拓扑排序思想剥离叶节点，最终确定需要标记的边。最优解法采用类似拓扑排序的"剥叶子"策略，无需复杂缩点，直接处理度数即可。

---

### 高星题解推荐

#### 1. **StudyingFather（4.5星）**
**关键亮点**:  
- 分类处理树/非树连通分量
- 用拓扑排序思想剥离叶节点，剩余环结构分析
- 代码简洁高效（仅100行）
**核心代码思想**:
```cpp
void dfs(int u) { // 标记初始叶节点
    if(t[u]==1) q.push(u); 
    /*...*/
}
while(!q.empty()) { // 拓扑剥叶过程
    int u=q.front(); q.pop();
    s.erase(u);
    for(auto v:e[u]) if(--t[v]==1) q.push(v);
}
if(s.empty()) // 树结构处理
else // 环结构处理
```
**代码亮点**: 使用队列维护动态度数，集合`s`记录未被剥离节点，逻辑清晰。

#### 2. **lgswdn_SA（4星）**
**关键亮点**:  
- 提出"环上点"概念，通过度数剥离判定
- 直接操作原图无需缩点
**核心实现**:
```cpp
void topo(int u) {
    queue<int> q;
    for(auto v:c[u]) if(deg[v]==1) q.push(v);
    while(!q.empty()) { // 不断剥离度为1的节点
        int u=q.front(); q.pop();
        /* 更新相邻节点度数 */
    }
}
```
**个人心得**: "类似于拓扑排序但处理度为1的点"的转化思路，简化了问题模型。

#### 3. **Provicy（4星）**
**关键亮点**:  
- 显式区分树与含环连通块
- 使用双重数组记录初始度数与动态度数
**实现技巧**:
```cpp
if(cnt==(int)g.size()) { /* 处理纯树结构 */ }
else { /* 处理环上点与叶节点的连接边 */ }
```
**优化点**: 使用`vis[]`数组记录是否被剥离，避免重复计算。

---

### 关键思路总结
**拓扑剥叶法**：  
1. 对每个连通块进行类似拓扑排序的过程，不断移除度数为1的节点
2. 未被移除的节点构成环或连接环的结构
3. 所有从保留节点指向被移除节点的边即为需要标记的死路

**优势**：避免复杂的双连通分量分析，时间复杂度O(n+m)，空间效率高。

---

### 拓展训练
1. [P3388 割点](https://www.luogu.com.cn/problem/P3388) - 图的割点判定
2. [P2860 Redundant Paths G](https://www.luogu.com.cn/problem/P2860) - 边双连通分量应用
3. [P2921 Trick or Treat on the Farm](https://www.luogu.com.cn/problem/P2921) - 基环树处理

---

### 调试心得摘录
- **比利♂海灵顿**提到"场上对题意一知半解" → 强调先通过样例理解"不掉头"的路径定义
- **StudyingFather**代码中`s.erase(u)`与队列的配合 → 注意容器选择对性能的影响
- **Provicy**使用`d[]`保存初始度数 → 保留原始信息便于后续分类判定

---
处理用时：45.42秒