# 题目信息

# Not Assigning

## 题目描述

You are given a tree of $ n $ vertices numbered from $ 1 $ to $ n $ , with edges numbered from $ 1 $ to $ n-1 $ . A tree is a connected undirected graph without cycles. You have to assign integer weights to each edge of the tree, such that the resultant graph is a prime tree.

A prime tree is a tree where the weight of every path consisting of one or two edges is prime. A path should not visit any vertex twice. The weight of a path is the sum of edge weights on that path.

Consider the graph below. It is a prime tree as the weight of every path of two or less edges is prime. For example, the following path of two edges: $ 2 \to 1 \to 3 $ has a weight of $ 11 + 2 = 13 $ , which is prime. Similarly, the path of one edge: $ 4 \to 3 $ has a weight of $ 5 $ , which is also prime.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627C/3add991eaafca4c0491e3513c8ebd38f1627bca9.png)Print any valid assignment of weights such that the resultant tree is a prime tree. If there is no such assignment, then print $ -1 $ . It can be proven that if a valid assignment exists, one exists with weights between $ 1 $ and $ 10^5 $ as well.

## 说明/提示

For the first test case, there are only two paths having one edge each: $ 1 \to 2 $ and $ 2 \to 1 $ , both having a weight of $ 17 $ , which is prime.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627C/22666e3c2f70cbd5edc23fd608081fffda0715fc.png)The second test case is described in the statement.

It can be proven that no such assignment exists for the third test case.

## 样例 #1

### 输入

```
3
2
1 2
4
1 3
4 3
2 1
7
1 2
1 3
3 4
3 5
6 2
7 2```

### 输出

```
17
2 5 11
-1```

# AI分析结果



---

## **算法分类**  
图论、构造、树的性质

---

## **题解思路与核心难点**

### **核心思路**  
1. **树必须是链状结构**：若存在度数 ≥3 的节点，则无法构造合法解。  
2. **交替赋权**：对链状结构交替赋值为 `2` 和 `3`，使得单边和相邻边和均为质数。

### **解决难点**  
- **结构约束的证明**：若存在度数 ≥3 的节点，其连接的边无法满足“相邻边和为质数”的要求。  
- **遍历与赋值**：链状结构的遍历需确定端点，并通过 DFS/BFS 交替赋值。

---

## **题解评分 (≥4星)**

| 作者          | 评分 | 亮点                                                         |
|---------------|------|--------------------------------------------------------------|
| LEE114514     | ★★★★☆ | 代码简洁，DFS交替赋值逻辑清晰，邻接表存储结构合理           |
| wosile        | ★★★★☆ | 数学证明严谨，代码中显式处理链的遍历与交替赋值               |
| zhaoyp        | ★★★★  | 反证法说明结构限制，构造链的交替赋值方法直观                |

---

## **最优思路与技巧提炼**

### **关键思路**  
- **结构判断**：所有节点度数 ≤2 → 树为链。  
- **交替赋值**：链上边权按 `2, 3, 2, 3…` 交替填充，保证单边质数、相邻边和为质数（2+3=5）。

### **实现技巧**  
1. **度数检查**：遍历每个节点的度数，若有 ≥3 直接输出 `-1`。  
2. **端点选择**：任选一个度数为 1 的节点作为链的起点。  
3. **DFS遍历**：通过 DFS 递归赋值，交替使用 `col` 变量标记当前权值类型。

---

## **同类型题拓展**  
- **相似题目**：构造满足特定条件的树边权（如奇偶性、路径和约束）。  
- **通用解法**：  
  - 分析边权约束条件，推导树的结构限制。  
  - 通过链或特定结构的遍历进行构造。

---

## **推荐题目**  
1. [CF1003E Tree Constructing](https://codeforces.com/problemset/problem/1003/E)（构造特定直径的树）  
2. [P1359 租用游艇](https://www.luogu.com.cn/problem/P1359)（最短路径构造）  
3. [P2294 狡猾的商人](https://www.luogu.com.cn/problem/P2294)（约束条件下的图构造）

---

## **个人心得摘录**  
> "若存在度数为3的节点，与其相连的边中必有两个奇质数，其和为偶，矛盾。因此必须为链。"  
> —— wosile 的数学证明简洁有力，避免冗长推导。

---

## **可视化算法演示**

### **算法流程动画**  
1. **结构检查**：高亮所有节点，若某个节点度数 ≥3，显示红色警告并终止。  
2. **链遍历**：  
   - 以绿色高亮当前遍历的节点和边。  
   - 交替显示 `2`（蓝色）和 `3`（橙色）的赋值过程。  
3. **路径验证**：动态计算单边和相邻边和，以绿色勾/红色叉标记是否质数。

### **复古像素风格设计**  
- **颜色方案**：8位色调（绿、蓝、橙、红）。  
- **音效**：  
  - 边赋值时播放“哔”声（8-bit音效）。  
  - 结构检查失败时播放低沉警告音。  
- **自动演示**：按步进速度自动遍历链并赋值，可暂停/调速。

### **代码实现片段（关键逻辑）**  
```cpp
void dfs(int rt, int fa, int col) {
    for (auto &edge : T[rt]) {
        if (edge.first != fa) {
            ans[edge.second] = col + 2; // 赋值为2或3
            dfs(edge.first, rt, col ^ 1); // 交替col
        }
    }
}
```

---

## **完整代码参考**  
```cpp
#include<bits/stdc++.h>
using namespace std;
int d[100005], u[100005], v[100005];
vector<pair<int,int>> T[100005];
int ans[100005];

void dfs(int rt, int fa, int col) {
    for (auto &edge : T[rt]) {
        if (edge.first != fa) {
            ans[edge.second] = col + 2;
            dfs(edge.first, rt, col ^ 1);
        }
    }
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        memset(d, 0, sizeof(d));
        for (int i=1; i<=n; i++) T[i].clear();
        
        for (int i=1; i<n; i++) {
            scanf("%d %d", &u[i], &v[i]);
            d[u[i]]++, d[v[i]]++;
            T[u[i]].emplace_back(v[i], i);
            T[v[i]].emplace_back(u[i], i);
        }
        
        bool invalid = false;
        for (int i=1; i<=n; i++) 
            if (d[i] > 2) invalid = true;
        
        if (invalid) {
            printf("-1\n");
            continue;
        }
        
        int start = 1;
        for (int i=1; i<=n; i++)
            if (d[i] == 1) { start = i; break; }
        
        dfs(start, 0, 0);
        for (int i=1; i<n; i++) printf("%d ", ans[i]);
        printf("\n");
    }
    return 0;
}
```

---
处理用时：71.39秒