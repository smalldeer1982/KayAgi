# 题目信息

# Party

## 题目描述

A company has $ n $ employees numbered from $ 1 $ to $ n $ . Each employee either has no immediate manager or exactly one immediate manager, who is another employee with a different number. An employee $ A $ is said to be the superior of another employee $ B $ if at least one of the following is true:

- Employee $ A $ is the immediate manager of employee $ B $
- Employee $ B $ has an immediate manager employee $ C $ such that employee $ A $ is the superior of employee $ C $ .

The company will not have a managerial cycle. That is, there will not exist an employee who is the superior of his/her own immediate manager.

Today the company is going to arrange a party. This involves dividing all $ n $ employees into several groups: every employee must belong to exactly one group. Furthermore, within any single group, there must not be two employees $ A $ and $ B $ such that $ A $ is the superior of $ B $ .

What is the minimum number of groups that must be formed?

## 说明/提示

For the first example, three groups are sufficient, for example:

- Employee 1
- Employees 2 and 4
- Employees 3 and 5

## 样例 #1

### 输入

```
5
-1
1
2
1
-1
```

### 输出

```
3
```

# AI分析结果



# Party

## 题目描述

某公司有 $n$ 个编号为 $1$ 到 $n$ 的员工。每个员工要么没有直接上级，要么恰好有一个直接上级（该上级是另一个不同编号的员工）。称员工 $A$ 是员工 $B$ 的上级，当且仅满足以下条件之一：

- 员工 $A$ 是员工 $B$ 的直接上级
- 员工 $B$ 存在直接上级员工 $C$，且员工 $A$ 是员工 $C$ 的上级

公司保证不会出现管理循环（即不存在某个员工是其直接上级的上级的情况）。

现公司要举办派对，需将所有员工分成若干组，满足：
1. 每个员工恰好属于一个组
2. 同一组中不存在两个员工 $A$ 和 $B$ 使得 $A$ 是 $B$ 的上级

求最少需要组成多少个组？

## 说明/提示

样例1解释：三个组满足条件，例如：
- 组1：员工1
- 组2：员工2和4
- 组3：员工3和5

## 样例 #1

### 输入
```
5
-1
1
2
1
-1
```

### 输出
```
3
```

---

**算法分类**: 树的最大深度（DFS/BFS/递归）

---

### 题解综合分析

所有题解的核心思路均基于以下关键点：
1. **树形结构建模**：将员工关系建模为多棵有根树（每个没有直接上级的员工视为一棵树的根）
2. **最大深度定理**：所需最少组数等于所有树的最大深度（最长链长度）
3. **实现方法差异**：
   - **递归法**：直接沿父节点链向上遍历统计深度（O(n²)）
   - **DFS/BFS**：显式构建树结构后遍历（O(n)）
   - **SPFA法**：将问题转化为最长路径问题（非常规解法）

---

### 精选题解

#### 1. StudyingFather（★★★★★）
**核心思路**：暴力递归计算每个节点的深度  
**亮点**：
- 代码简洁直观（仅需15行）
- 利用题目数据规模（n≤2000）允许O(n²)复杂度
- 无需显式建树，直接操作父节点数组

**关键代码**：
```cpp
int find(int x) {
    int cnt=0;
    while(x!=-1)
        x=fa[x],cnt++;
    return cnt;
}
// 遍历所有节点取最大深度
```

#### 2. xiaomuyun（★★★★☆）
**核心思路**：显式建树后DFS计算深度  
**亮点**：
- 时间复杂度优化到O(n)
- 演示了标准树遍历的实现方法
- 包含树根处理细节（只从根节点开始DFS）

**关键代码**：
```cpp
void dfs(int u) {
    for(int v : g[u]) {
        dep[v] = dep[u] + 1;
        mx = max(mx, dep[v]);
        dfs(v);
    }
}
// 建立邻接表后遍历所有根节点
```

#### 3. fengxiaoyi（★★★☆☆）
**核心思路**：虚拟根节点+BFS层序遍历  
**亮点**：
- 通过虚拟根节点统一处理森林
- 演示BFS求树深度的标准方法
- 代码结构清晰易扩展

**关键代码**：
```cpp
q.push({0,0});
while(!q.empty()) {
    auto [v, dep] = q.front();
    ans = max(ans, dep);
    // 遍历所有子节点并入队
}
```

---

### 最优思路总结
**核心技巧**：将问题转化为树的最大深度计算  
**关键步骤**：
1. 将每个员工视为树节点，父指针构成多棵有根树
2. 对于每个节点，计算其到根节点的路径长度（深度）
3. 所有节点深度的最大值即为答案

**实现建议**：
- 小数据（n≤1e4）可用直接递归法，代码最简
- 大数据（n≥1e5）应使用DFS/BFS显式遍历
- 虚拟根节点技巧可简化多棵树处理

---

### 拓展训练
1. [P1047 二叉树的最大深度](https://www.luogu.com.cn/problem/P1047)  
   - 练习树深度的基础计算
2. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)  
   - 树形DP与层次关系的进阶应用
3. [P1305 树的直径](https://www.luogu.com.cn/problem/P1395)  
   - 练习树的最长路径计算

---

### 调试心得摘录
- **WinterRain208**：注意递归边界条件（父节点为-1时返回当前深度）
- **动态WA**：SPFA解法中边权设置为负数巧妙转换了最长路径问题
- **Nozebry**：错误地将父指针指向自己导致循环引用，需注意初始化处理

---
处理用时：61.02秒