# 题目信息

# [ICPC 2016 WF] Ceiling Function

## 题目描述

Advanced Ceiling Manufacturers (ACM) is analyzing the properties of its new series of Incredibly Collapse-Proof Ceilings (ICPCs). An ICPC consists of $n$ layers of material, each with a different value of collapse resistance (measured as a positive integer). The analysis ACM wants to run will take the collapse-resistance values of the layers, store them in a binary search tree, and check whether the shape of this tree in any way correlates with the quality of the whole construction. Because, well, why should it not?

To be precise, ACM takes the collapse-resistance values for the layers, ordered from the top layer to the bottom layer, and inserts them one-by-one into a tree. The rules for inserting a value $v$ are:

If the tree is empty, make $v$ the root of the tree.

If the tree is not empty, compare $v$ with the root of the tree. If $v$ is smaller, insert $v$ into the left subtree of the root, otherwise insert $v$ into the right subtree.

ACM has a set of ceiling prototypes it wants to analyze by trying to collapse them. It wants to take each group of ceiling prototypes that have trees of the same shape and analyze them together.

For example, assume ACM is considering five ceiling prototypes with three layers each, as described by Sample Input 1 and shown in Figure 1. Notice that the first prototype’s top layer has collapse-resistance value 2, the middle layer has value 7, and the bottom layer has value 1. The second prototype has layers with collapse-resistance values of 3, 1, and 4 – and yet these two prototypes induce the same tree shape, so ACM will analyze them together.

Given a set of prototypes, your task is to determine how many different tree shapes they induce.

![](https://cdn.luogu.com.cn/upload/image_hosting/xvdteesl.png)

   Figure 1: The four tree shapes induced by the ceiling prototypes in Sample Input 1. 

## 说明/提示

Time limit: 5000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016

## 样例 #1

### 输入

```
5 3
2 7 1
3 1 4
1 5 9
2 6 5
9 7 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 4
3 1 2 40000
3 4 2 1
33 42 17 23
```

### 输出

```
2
```

# AI分析结果



**算法分类**: 模拟、树的结构处理

---

### 题解分析与结论
题目要求统计不同二叉搜索树形状的数量。各题解核心思路均为**构建二叉搜索树后，编码树的结构信息以去重**。关键在于如何唯一表示树的结构。

---

### 精选题解与评分
1. **题解作者：whhsteven (4星)**  
   **关键思路**：用四进制数记录每个节点的子节点状态（0~3表示叶子/左儿子/右儿子/双儿子），按先序遍历生成唯一标识。  
   **亮点**：数学化编码保证唯一性，利用数值哈希高效去重。  
   **核心代码思想**：  
   ```cpp
   // 伪代码：遍历树时记录每个节点的状态
   int encode_tree(Node* root) {
       if (!root) return;
       int state = (root->left ? 1 : 0) + (root->right ? 2 : 0);
       code = code * 4 + state;
       encode_tree(root->left);
       encode_tree(root->right);
   }
   ```

2. **题解作者：maokaiyu (4星)**  
   **关键思路**：记录每个节点的子节点状态（'a'~'d'），中序遍历拼接字符串哈希。  
   **亮点**：字符串哈希直观易实现，调试输出便于验证。  
   **核心代码**：  
   ```cpp
   void dfs(node a[], int root) {
       if (root == 0) return;
       tmp += a[root].c; // 记录当前节点状态
       dfs(a, a[root].l);
       dfs(a, a[root].r);
   }
   ```

---

### 最优思路总结
**关键技巧**：  
1. **结构编码**：通过节点子节点状态（如四进制或字符）唯一描述树形。  
2. **遍历顺序**：先序/中序等遍历顺序确保结构信息的唯一性。  
3. **哈希去重**：将编码结果存入哈希表（数值或字符串），统计不同哈希值的数量。

**适用场景**：需要快速比较树、图等复杂结构的题目，如判断同构树、统计不同结构出现次数等。

---

### 推荐习题
1. [P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)（结构表示）  
2. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)（结构统计与DP）  
3. [P5018 对称二叉树](https://www.luogu.com.cn/problem/P5018)（结构比较与递归）  

---

### 题解心得摘录
- **maokaiyu**提到用中序遍历记录状态，并在代码中添加`//cout<<tmp<<endl;`调试，强调验证中间结果的重要性。  
- **whhsteven**指出数值编码的数学严谨性，避免哈希碰撞问题。  
- **a___**的`sin`哈希法虽新颖，但存在精度隐患，需注意测试边界情况。

---
处理用时：40.19秒