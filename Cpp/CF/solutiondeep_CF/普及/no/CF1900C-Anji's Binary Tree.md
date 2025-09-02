# 题目信息

# Anji's Binary Tree

## 题目描述

Keksic keeps getting left on seen by Anji. Through a mutual friend, he's figured out that Anji really likes binary trees and decided to solve her problem in order to get her attention.

Anji has given Keksic a binary tree with $ n $ vertices. Vertex $ 1 $ is the root and does not have a parent. All other vertices have exactly one parent. Each vertex can have up to $ 2 $ children, a left child, and a right child. For each vertex, Anji tells Keksic index of both its left and its right child or tells him that they do not exist.

Additionally, each of the vertices has a letter $ s_i $ on it, which is either 'U', 'L' or 'R'.

Keksic begins his journey on the root, and in each move he does the following:

- If the letter on his current vertex is 'U', he moves to its parent. If it doesn't exist, he does nothing.
- If the letter on his current vertex is 'L', he moves to its left child. If it doesn't exist, he does nothing.
- If the letter on his current vertex is 'R', he moves to its right child. If it doesn't exist, he does nothing.

 Before his journey, he can perform the following operations: choose any node, and replace the letter written on it with another one. You are interested in the minimal number of operations he needs to do before his journey, such that when he starts his journey, he will reach a leaf at some point. A leaf is a vertex that has no children. It does not matter which leaf he reaches. Note that it does not matter whether he will stay in the leaf, he just needs to move to it. Additionally, note that it does not matter how many times he needs to move before reaching a leaf.

Help Keksic solve Anji's tree so that he can win her heart, and make her come to Čačak.

## 说明/提示

In the first test case, vertex $ 1 $ has $ 2 $ as its left child and $ 3 $ as its right child. Vertices $ 2 $ and $ 3 $ do not have children and are therefore leaves. As 'L' is written on vertex $ 1 $ , Keksic will go to vertex $ 2 $ , therefore he has to do no operations.

In the second test case, vertex $ 1 $ has $ 3 $ as its left child and $ 2 $ as its right child. Vertices $ 2 $ and $ 3 $ are leaves. As 'U' is written on vertex $ 1 $ , Keksic needs to change it to either 'L' or 'R' in order for him to reach a leaf.

In the third case, vertex $ 1 $ has only a right child, which is vertex $ 2 $ . As 'L' is written on it, Keksic needs to change it to 'R', otherwise he would be stuck on vertex $ 1 $ .

In the fourth case, he can change $ 3 $ characters so that letters on the vertices are "LURL", which makes him reach vertex $ 2 $ .

In the fifth case, there are $ 3 $ leaves, $ 3 $ , $ 6 $ and $ 7 $ . To reach either leaf $ 6 $ or leaf $ 7 $ , he needs to change $ 2 $ characters. However, if he changes character on vertex $ 1 $ to 'R', he will reach leaf $ 3 $ , therefore the answer is $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1900C/9018896e1391d18f63af647e477e71929a6a2577.png) The initial tree in test case 5.

## 样例 #1

### 输入

```
5
3
LRU
2 3
0 0
0 0
3
ULR
3 2
0 0
0 0
2
LU
0 2
0 0
4
RULR
3 0
0 0
0 4
2 0
7
LLRRRLU
5 2
3 6
0 0
7 0
4 0
0 0
0 0```

### 输出

```
0
1
1
3
1```

# AI分析结果



# Anji的二叉树

## 题目描述

Keksic为了引起Anji的注意，需要解决一个二叉树问题。给定一棵以1号节点为根的二叉树，每个节点标有字母'U'、'L'或'R'。移动规则如下：
- 'U'：移动到父节点（不存在则不移动）
- 'L'：移动到左子节点（不存在则不移动）
- 'R'：移动到右子节点（不存在则不移动）

任务是通过修改最少的节点字母，使得从根节点出发至少能到达一个叶子节点。叶子节点定义为没有子节点的节点。

## 算法分类
动态规划（树形DP）

---

## 题解对比分析

### 核心思路
所有题解均围绕树形遍历展开，主要分为两类：
1. **自顶向下路径计数**：计算从根到各节点的修改次数（如_smart_stupid_、IOI_AK_TLR）
2. **自底向上动态规划**：以叶子节点为基准，递推每个节点的最小修改代价（如CuteChat、Phartial）

### 关键难点
1. **避免向上移动**：所有有效路径必须形成从根到叶子的单向路径，'U'操作本质上是无效路径
2. **最优子结构**：每个节点的最优解仅依赖子节点的最优解
3. **叶节点判定**：需要精确处理没有左右子节点的边界条件

---

## 高分题解推荐

### 1. [CuteChat] 动态规划解法（⭐⭐⭐⭐⭐）
**核心思路**：定义`dp[u]`为从节点u出发到达叶子的最小修改次数。状态转移方程：
```cpp
dp[u] = min(dp[left] + (s[u]!='L'), dp[right] + (s[u]!='R'))
```
**亮点**：
- 严格的数学化状态定义
- 时间复杂度O(n)的线性遍历
- 天然处理空子树边界条件

**代码核心**：
```cpp
int dfs(int u) {
    if(!u) return INF;
    if(无子节点) return 0;
    return min(dfs(l[u]) + (s[u]!='L'), dfs(r[u]) + (s[u]!='R'));
}
```

### 2. [Phartial] 精简动态规划（⭐⭐⭐⭐⭐）
**核心优化**：
- 使用全局数组直接存储子树结果
- 显式处理空节点返回极大值
- 函数式递归结构清晰

**代码亮点**：
```cpp
void D(int x) {
    if(!x) return;
    if(叶子节点) { f[x]=0; return; }
    D(l[x]); D(r[x]);
    f[x] = min(f[l[x]] + (s[x]!='L'), f[r[x]] + (s[x]!='R'));
}
```

### 3. [AlexandreLea] 记忆化递推（⭐⭐⭐⭐）
**创新点**：
- 从叶节点反向计算到根的代价
- 记忆化存储已计算路径
- 预处理父节点关系加速查询

**关键实现**：
```cpp
int func(int x) {
    if(记忆化存在) return step[x];
    int res = 需修改父节点字符的代价;
    return step[x] = res + func(fa[x]);
}
```

---

## 最优技巧总结
1. **树形DP范式**：定义节点状态→递归处理子树→合并子问题结果
2. **状态压缩**：利用二叉树特性，仅需判断左右子节点即可确定转移方向
3. **剪枝优化**：空节点直接返回极大值，避免无效递归
4. **记忆化技巧**：对已计算节点直接返回结果，消除重复计算

---

## 拓展训练
1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352) - 经典树形DP
2. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015) - 带权树形DP
3. [P2014 [CTSC1997] 选课](https://www.luogu.com.cn/problem/P2014) - 树形依赖背包问题

---

## 调试心得摘录
1. **叶节点判定陷阱**：注意题目定义叶子节点为左右子节点都不存在，而非任一子节点不存在
2. **空指针处理**：递归时需显式处理空子树返回极值，否则会导致错误传递
3. **初始化技巧**：全局数组复用需注意多测清空问题
4. **字符比较优化**：使用布尔表达式直接计算修改代价，避免if-else分支

---
处理用时：52.49秒