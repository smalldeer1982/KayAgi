# 题目信息

# Xor-tree

## 题目描述

Iahub is very proud of his recent discovery, propagating trees. Right now, he invented a new tree, called xor-tree. After this new revolutionary discovery, he invented a game for kids which uses xor-trees.

The game is played on a tree having $ n $ nodes, numbered from $ 1 $ to $ n $ . Each node $ i $ has an initial value $ init_{i} $ , which is either 0 or 1. The root of the tree is node 1.

One can perform several (possibly, zero) operations on the tree during the game. The only available type of operation is to pick a node $ x $ . Right after someone has picked node $ x $ , the value of node $ x $ flips, the values of sons of $ x $ remain the same, the values of sons of sons of $ x $ flips, the values of sons of sons of sons of $ x $ remain the same and so on.

The goal of the game is to get each node $ i $ to have value $ goal_{i} $ , which can also be only 0 or 1. You need to reach the goal of the game by using minimum number of operations.

## 样例 #1

### 输入

```
10
2 1
3 1
4 2
5 1
6 2
7 5
8 6
9 8
10 5
1 0 1 1 0 1 0 1 0 1
1 0 1 0 0 1 1 1 0 1
```

### 输出

```
2
4
7
```

# AI分析结果



### 题目重写
**题目名称**：Xor树

**题目描述**  
Iahub 最近发现了一种传播树，称为异或树。他设计了一个基于异或树的游戏：  
游戏在一棵有 $n$个节点的树上进行，节点编号从1到n，根为1号节点。每个节点初始值 $init_i$ 为0或1。玩家可进行若干次操作：选取节点x，翻转x及其孙子、曾孙等（深度差为偶数的后代）的值。目标是通过最少操作使所有节点的值变为目标值 $goal_i$。

**输入格式**  
- 第一行：节点数 $n$  
- 接下来 $n-1$ 行：每行两个整数表示树的边  
- 第 $n+1$ 行：$n$ 个整数表示初始值  
- 第 $n+2$ 行：$n$ 个整数表示目标值  

**输出格式**  
- 第一行：操作次数  
- 第二行：按升序排列的操作节点  

**样例输入**  
```
10
2 1
3 1
4 2
5 1
6 2
7 5
8 6
9 8
10 5
1 0 1 1 0 1 0 1 0 1
1 0 1 0 0 1 1 1 0 1
```
**样例输出**  
```
2
4
7
```

---

### 算法分类  
**深度优先搜索（DFS）**

---

### 题解分析与结论

#### 核心思路  
通过DFS维护奇偶层翻转标记：  
1. **奇偶性分层**：操作节点x时，仅影响与x深度差为偶数的后代节点  
2. **标记传递**：DFS时维护两个标记，分别表示当前奇/偶层是否需要翻转  
3. **实时判断**：根据当前标记判断是否需要操作，避免实际修改子树  

#### 最优解法关键  
- **标记继承**：用两个布尔变量（如`f0`, `f1`）记录奇偶层累计翻转次数  
- **动态决策**：当当前节点值与目标值不符时，进行翻转并切换对应奇偶标记  

---

### 精选题解

#### 题解1：泥土笨笨（5星）  
**亮点**  
- 通过`f0`和`f1`的巧妙切换实现奇偶层标记  
- 代码简洁，逻辑清晰  
```cpp
void dfs(int u, int fa, int f0, int f1) {
    if ((s[u] ^ f0) != t[u]) {  // 判断是否需要翻转
        ans.push_back(u);
        f0 ^= 1;  // 切换当前层标记
    }
    for (int v : adj[u]) {
        if (v != fa) 
            dfs(v, u, f1, f0);  // 交换奇偶标记传递给子节点
    }
}
```

#### 题解2：_Weslie_（4星）  
**亮点**  
- 显式区分奇偶层标记（`jchang`, `ochang`）  
- 通过位运算高效实现翻转判断  
```cpp
void dfs(int x, int fa, int dep, int jchang, int ochang) {
    if (dep % 2) {
        if ((jchang ^ col[x]) != to[x]) {
            jchang ^= 1;  // 翻转奇数层标记
            ans.push_back(x);
        }
    } else {
        if ((ochang ^ col[x]) != to[x]) {
            ochang ^= 1;  // 翻转偶数层标记
            ans.push_back(x);
        }
    }
    // ... 递归子节点 ...
}
```

#### 题解3：Zinc_acetate（4星）  
**亮点**  
- 通过参数`c1`, `c2`的交替实现标记传递  
- 代码结构紧凑  
```cpp
void dfs(int i, int c1, int c2) {
    if (a[i] ^ c1 ^ x[i]) {
        c1 ^= 1;
        ans.push_back(i);
    }
    for (auto j : b[i]) {
        dfs(j, c2, c1);  // 交替传递标记
    }
}
```

---

### 关键技巧总结  
1. **奇偶分层标记**：通过两个变量维护不同深度的翻转状态  
2. **动态决策翻转**：仅在当前值与目标不符时操作，避免冗余计算  
3. **标记传递**：递归时交换奇偶标记（如`f0`和`f1`交替传递）  

---

### 拓展练习  
1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)（树形DP）  
2. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)（树形DP）  
3. [P3384 树链剖分](https://www.luogu.com.cn/problem/P3384)（树结构操作）

---
处理用时：77.20秒