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



### 中文题目重写
#### 题目名称：Kay和雪花

**题目描述**  
一块恶魔镜子的碎片击中了Kay的眼睛，让他对玫瑰的美景不再感兴趣。现在他喜欢观察雪花。  

某天，他发现一个巨大的雪花，其形态是一棵由$n$个节点构成的树（连通无环图），根节点编号为1。Kay对这个树的结构产生了浓厚兴趣。  

经过研究，他提出了$q$个查询。第$i$个查询要求找出以节点$v_i$为根的子树的重心。你的目标是回答所有查询。  

**子树定义**  
节点的子树由该节点及其所有后代节点（直接或间接）组成。即节点$v$的子树包含所有满足以下条件的节点$u$：在从$u$到根的路径上必须包含$v$。  

**重心定义**  
树（或子树）的重心是一个节点，当将其从树中删除后，最大连通分量的大小不超过原树大小的一半。  

---

### 题解综合分析

#### 关键思路总结
1. **重心位置特性**：以节点$u$为根的子树重心必定位于其最大子树的重心到$u$的路径上  
2. **预处理子树大小**：通过DFS预处理所有节点的子树大小$size[u]$和最大子树  
3. **回溯调整重心**：在DFS回溯时，从最大子树的重心开始向上跳，找到满足条件的最优位置  
4. **时间复杂度优化**：每个节点最多被遍历一次，保证$O(n)$复杂度  

#### 最优技巧提炼
```cpp
// 核心代码逻辑
void dfs(int u) {
    for (子节点v) dfs(v); // 递归处理子树
    int candidate = 最大子树的重心;
    while (向上跳的条件成立) candidate = father[candidate];
    更新u的重心为candidate;
}
```

---

### 高星题解精选

#### 1. mrsrz（★★★★★）  
**核心亮点**  
- 利用重心在父链上移动的特性，通过"向上跳"策略快速定位  
- 时间复杂度严格$O(n)$，代码简洁高效  

**关键代码**  
```cpp
void dfs(int now) {
    sz[now] = 1;
    for (遍历子节点) {
        dfs(子节点);
        sz[now] += sz[子节点];
        维护最大子树大小;
    }
    int id = now; // 初始候选为当前节点
    for (遍历子节点) {
        int it = 子节点的重心;
        while (向上跳条件成立) {
            it = fa[it]; // 向上跳父节点
            更新最优解判断条件;
        }
        if (当前候选更优) 更新id;
    }
    rt[now] = id; // 记录最终重心
}
```

#### 2. Ryan_（★★★★☆）  
**核心亮点**  
- 直接利用重心定义式判断  
- 通过回溯时动态调整重心位置  

**调试心得**  
> "当某节点u的最大子树节点v的size的两倍小于size[u]，该点为重心。否则暴力向上走，时间复杂度O(n)"  

**关键代码**  
```cpp
void dfs(int x) {
    size[x] = 1;
    for (子节点v) {
        dfs(v);
        维护最大子树;
    }
    if (最大子树不满足条件) {
        int now = 最大子树的重心;
        while (向上跳更优) now = fa[now];
        ans[x] = now;
    }
}
```

#### 3. くろねこ（★★★★☆）  
**核心亮点**  
- 在DFS回溯时进行特判调整  
- 使用位运算优化条件判断  

**调试经历**  
> "一开始尝试暴力DFS导致TLE，后发现可以利用重心特性优化，将时间复杂度从$O(n^2)$降为$O(n)$"

**关键代码**  
```cpp
if ((son[res] << 1) > son[x]) { // 位运算优化判断
    int temp = ans[res];
    while (((son[x]-son[temp])<<1) > son[x]) 
        temp = fa[temp]; // 向上迭代
    ans[x] = temp;
}
```

---

### 扩展训练建议
**推荐题目**  
1. P1395 会议（基础重心应用）  
2. P1364 医院设置（带权重心问题）  
3. P5666 树的重心（NOI难度进阶题）  

**思维延展**  
- 对于动态树的重心维护，可结合LCT（Link-Cut Tree）  
- 权值重心问题可将size替换为权值和  
- 多重心判定时需考虑平衡树结构特性

---
处理用时：58.28秒