# 题目信息

# Parsa's Humongous Tree

## 题目描述

Parsa has a humongous tree on $ n $ vertices.

On each vertex $ v $ he has written two integers $ l_v $ and $ r_v $ .

To make Parsa's tree look even more majestic, Nima wants to assign a number $ a_v $ ( $ l_v \le a_v \le r_v $ ) to each vertex $ v $ such that the beauty of Parsa's tree is maximized.

Nima's sense of the beauty is rather bizarre. He defines the beauty of the tree as the sum of $ |a_u - a_v| $ over all edges $ (u, v) $ of the tree.

Since Parsa's tree is too large, Nima can't maximize its beauty on his own. Your task is to find the maximum possible beauty for Parsa's tree.

## 说明/提示

The trees in the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528A/7830790d968daee501b061b313ebb6586c6b6ca7.png)In the first test case, one possible assignment is $ a = \{1, 8\} $ which results in $ |1 - 8| = 7 $ .

In the second test case, one of the possible assignments is $ a = \{1, 5, 9\} $ which results in a beauty of $ |1 - 5| + |5 - 9| = 8 $

## 样例 #1

### 输入

```
3
2
1 6
3 8
1 2
3
1 3
4 6
7 9
1 2
2 3
6
3 14
12 20
12 19
2 12
10 17
3 17
3 2
6 5
1 5
2 6
4 6```

### 输出

```
7
8
62```

# AI分析结果

### 题目翻译
# Parsa的巨型树

## 题目描述
Parsa 有一棵包含 $n$ 个顶点的巨型树。
在每个顶点 $v$ 上，他写下了两个整数 $l_v$ 和 $r_v$。
为了让 Parsa 的树看起来更加雄伟，Nima 想给每个顶点 $v$ 分配一个数字 $a_v$（$l_v \le a_v \le r_v$），使得 Parsa 的树的美观度最大化。
Nima 对美的感知相当奇特。他将树的美观度定义为树中所有边 $(u, v)$ 上的 $|a_u - a_v|$ 之和。
由于 Parsa 的树太大了，Nima 无法独自最大化其美观度。你的任务是找出 Parsa 的树的最大可能美观度。

## 说明/提示
示例中的树：
![示例中的树](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528A/7830790d968daee501b061b313ebb6586c6b6ca7.png)
在第一个测试用例中，一种可能的分配是 $a = \{1, 8\}$，这将得到 $|1 - 8| = 7$。
在第二个测试用例中，一种可能的分配是 $a = \{1, 5, 9\}$，这将得到美观度为 $|1 - 5| + |5 - 9| = 8$。

## 样例 #1
### 输入
```
3
2
1 6
3 8
1 2
3
1 3
4 6
7 9
1 2
2 3
6
3 14
12 20
12 19
2 12
10 17
3 17
3 2
6 5
1 5
2 6
4 6
```

### 输出
```
7
8
62
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是利用树形动态规划来解决问题。首先通过证明或分析得出每个节点的点权取边界值（$l_v$ 或 $r_v$）时能使树的美观度最大。然后定义状态 $dp[i][0/1]$ 表示以 $i$ 为根节点的子树中，$i$ 节点选择 $l[i] / r[i]$ 时答案的最大值，再通过深度优先搜索（DFS）进行状态转移，最后取 $dp[1][0]$ 和 $dp[1][1]$ 中的最大值作为最终结果。

各题解的不同主要体现在证明每个节点取边界值的方式、代码实现细节（如建图方式、输入输出方式）上，但整体思路和核心算法一致。

### 所选题解
- **Forever1507（5星）**
    - **关键亮点**：思路清晰，直接点明这是树形动态规划问题，详细说明了状态定义和状态转移方程，代码简洁易懂，注释较少但逻辑清晰。
- **iMya_nlgau（4星）**
    - **关键亮点**：对题目大意进行了准确概括，用货仓选址的经典结论证明了每个节点取边界值的正确性，思路严谨，给出了状态转移方程的数学表达式。
- **mazy（4星）**
    - **关键亮点**：用调整法证明了每个节点取边界值的结论，并给出了证明的图片，代码实现中对一些小问题（如加无向边）进行了详细说明。

### 重点代码
```cpp
// Forever1507 的核心代码
void dfs(int cur,int fa){
    for(int i=0;i<v1[cur].size();i++){
        int son=v1[cur][i];
        if(fa==son)continue;
        dfs(son,cur);
        dp[cur][0]+=max(dp[son][0]+abs(l[cur]-l[son]),dp[son][1]+abs(l[cur]-r[son]));
        dp[cur][1]+=max(dp[son][0]+abs(r[cur]-l[son]),dp[son][1]+abs(r[cur]-r[son]));
    }
}
```
**核心实现思想**：通过深度优先搜索遍历以 `cur` 为根节点的子树，对于每个子节点 `son`，根据 `cur` 节点取 $l[cur]$ 或 $r[cur]$ 分别计算状态转移方程，更新 `dp[cur][0]` 和 `dp[cur][1]` 的值。

### 扩展思路
同类型题或类似算法套路：这类树形动态规划问题通常会给定树的结构和节点的一些属性，要求在树的结构上进行状态转移以求解最优值。常见的变化包括节点属性的不同、状态定义的不同、状态转移方程的不同等。例如，可能会给定节点的权值范围和边的权值，要求最大化树的某种价值和；或者给定节点的不同状态，要求满足一定条件下的最优解等。

### 推荐题目
1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
2. [P2014 选课](https://www.luogu.com.cn/problem/P2014)
3. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)

### 个人心得
各题解中均未包含个人心得内容。

---
处理用时：36.78秒