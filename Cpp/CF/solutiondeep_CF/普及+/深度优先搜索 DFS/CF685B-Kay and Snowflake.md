# 题目信息

# Kay and Snowflake

## 题目描述

After the piece of a devilish mirror hit the Kay's eye, he is no longer interested in the beauty of the roses. Now he likes to watch snowflakes.

Once upon a time, he found a huge snowflake that has a form of the tree (connected acyclic graph) consisting of $ n $ nodes. The root of tree has index $ 1 $ . Kay is very interested in the structure of this tree.

After doing some research he formed $ q $ queries he is interested in. The $ i $ -th query asks to find a centroid of the subtree of the node $ v_{i} $ . Your goal is to answer all queries.

Subtree of a node is a part of tree consisting of this node and all it's descendants (direct or not). In other words, subtree of node $ v $ is formed by nodes $ u $ , such that node $ v $ is present on the path from $ u $ to root.

Centroid of a tree (or a subtree) is a node, such that if we erase it from the tree, the maximum size of the connected component will be at least two times smaller than the size of the initial tree (or a subtree).

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF685B/821209b858c843715556bbbb66f001612969fa03.png)The first query asks for a centroid of the whole tree — this is node $ 3 $ . If we delete node $ 3 $ the tree will split in four components, two of size $ 1 $ and two of size $ 2 $ .

The subtree of the second node consists of this node only, so the answer is $ 2 $ .

Node $ 3 $ is centroid of its own subtree.

The centroids of the subtree of the node $ 5 $ are nodes $ 5 $ and $ 6 $ — both answers are considered correct.

## 样例 #1

### 输入

```
7 4
1 1 3 3 5 3
1
2
3
5
```

### 输出

```
3
2
3
6
```

# AI分析结果



# 题目中文翻译

## 题目名称：Kay和雪花

### 题目描述

当恶魔之镜的碎片击中Kay的眼睛后，他不再对玫瑰的美感兴趣，现在喜欢观察雪花。

某天他发现一个巨型雪花，其结构是一棵包含$n$个节点的树（连通无环图），根节点为1号节点。Kay对这棵树的结构产生了浓厚兴趣，提出了$q$个查询，第$i$个查询要求找出以节点$v_i$为根的子树的重心。你需要回答所有查询。

#### 定义说明：
- **子树**：包含某节点及其所有后代（直接或间接）的树结构
- **重心**：删除该节点后，剩余最大连通分量的大小不超过原树大小的一半

### 输入输出样例
（样例输入输出与图示内容保持不变）

---

# 题解综合分析

## 最优关键思路
1. **重心继承性**：子树重心必定位于重儿子子树重心到当前根的链上
2. **线性预处理**：DFS后序遍历时，利用子树信息推导父节点重心
3. **跳跃优化**：从重儿子重心向上跳跃，直到满足重心条件时停止

## 高分题解推荐（≥4星）

### 题解1：mrsrz（⭐⭐⭐⭐⭐）
**核心亮点**：
- 提出重心在重儿子重心链上的核心性质
- 跳跃时利用单调性优化，确保线性时间复杂度
- 代码简洁高效（仅30行）

**核心代码解析**：
```cpp
void dfs(int now) {
    sz[now] = 1;
    // 计算子树大小和最大子树
    for(遍历所有子节点) {
        dfs(e[i].to);
        sz[now] += sz[e[i].to];
        mx[now] = max(mx[now], sz[e[i].to]);
    }
    
    int id = now, me = mx[now];
    // 从各子树的中心向上寻找最优解
    for(遍历所有子节点) {
        int it = 子节点重心;
        while(fa[it] != now) { // 向上跳跃
            int new_val = 计算跳跃后的最大值
            if(更优则更新，否则跳出循环)
        }
        if(当前最优则更新重心)
    }
    rt[now] = id; // 记录当前子树重心
}
```

### 题解2：chen_z（⭐⭐⭐⭐）
**核心亮点**：
- 利用重链剖分特性
- 在重链上二分查找满足条件的深度最大节点
- 时间复杂度$O(n + q\log n)$

**关键代码片段**：
```cpp
void dfs2(int now) {
    // 重链剖分处理
    len[now] = 重链长度;
    // 在DFS序上维护重链信息
}

int query(int u) {
    // 在重链对应的DFS序区间二分查找
    while(l <= r) {
        if(当前mid节点满足条件) 更新答案区间
    }
    return 对应节点;
}
```

### 题解3：Ryan_（⭐⭐⭐⭐）
**核心亮点**：
- 直接应用重心性质判断
- 预处理每个子树的最大子节点
- 利用父子关系回溯寻找重心

**代码特点**：
```cpp
void dfs(int x) {
    if(最大子树不超过半数) ans[x] = x;
    else {
        int now = 重儿子重心;
        while(父节点更优时回溯)
        ans[x] = now;
    }
}
```

---

# 拓展练习
1. [P1395 会议](https://www.luogu.com.cn/problem/P1395) - 树的重心基础应用
2. [P1364 医院设置](https://www.luogu.com.cn/problem/P1364) - 重心相关的最短距离计算
3. [P2634 国家集训队]树上博弈 - 结合重心性质设计策略

---

# 调试经验摘录
**くろねこ的调试历程**：
1. 初版暴力DFS导致TLE，发现$O(n^2)$复杂度不可行
2. 观察性质后改写为线性算法，但错误地将`ans[x]`初始化为0导致错误
3. 通过分析树的重心定义，增加`while(((son[x]-son[temp])<<1)>son[x])`的条件判断，最终AC

**经验总结**：
- 预处理时需注意初始值的合理性
- 利用树的重心单调性可避免冗余计算
- 跳跃终止条件的精确判断是算法正确性的关键

---
处理用时：49.79秒