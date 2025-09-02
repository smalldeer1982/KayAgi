# 题目信息

# Middle Duplication

## 题目描述

A binary tree of $ n $ nodes is given. Nodes of the tree are numbered from $ 1 $ to $ n $ and the root is the node $ 1 $ . Each node can have no child, only one left child, only one right child, or both children. For convenience, let's denote $ l_u $ and $ r_u $ as the left and the right child of the node $ u $ respectively, $ l_u = 0 $ if $ u $ does not have the left child, and $ r_u = 0 $ if the node $ u $ does not have the right child.

Each node has a string label, initially is a single character $ c_u $ . Let's define the string representation of the binary tree as the concatenation of the labels of the nodes in the in-order. Formally, let $ f(u) $ be the string representation of the tree rooted at the node $ u $ . $ f(u) $ is defined as follows: $ $$$ f(u) = \begin{cases} \texttt{<empty string>}, & \text{if }u = 0; \\ f(l_u) + c_u + f(r_u) & \text{otherwise}, \end{cases}  $ $  where  $ + $  denotes the string concatenation operation.</p><p>This way, the string representation of the tree is  $ f(1) $ .</p><p>For each node, we can <span class="tex-font-style-it">duplicate</span> its label <span class="tex-font-style-bf">at most once</span>, that is, assign  $ c\_u $  with  $ c\_u + c\_u $ , but only if  $ u $  is the root of the tree, or if its parent also has its label duplicated.</p><p>You are given the tree and an integer  $ k $ . What is the lexicographically smallest string representation of the tree, if we can duplicate labels of at most  $ k $  nodes?</p><p>A string  $ a $  is lexicographically smaller than a string  $ b $  if and only if one of the following holds: </p><ul> <li>  $ a $  is a prefix of  $ b $ , but  $ a \\ne b $ ; </li><li> in the first position where  $ a $  and  $ b $  differ, the string  $ a $  has a letter that appears earlier in the alphabet than the corresponding letter in  $ b$$$.

## 说明/提示

The images below present the tree for the examples. The number in each node is the node number, while the subscripted letter is its label. To the right is the string representation of the tree, with each letter having the same color as the corresponding node.

Here is the tree for the first example. Here we duplicated the labels of nodes $ 1 $ and $ 3 $ . We should not duplicate the label of node $ 2 $ because it would give us the string "bbaaab", which is lexicographically greater than "baaaab".

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623E/8e9bc3e39a0385947c6f1b7db86d59f03e67d645.png)In the second example, we can duplicate the labels of nodes $ 1 $ and $ 2 $ . Note that only duplicating the label of the root will produce a worse result than the initial string.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623E/dca73cc51ea6acbb902f1315cd4594d96b4d3160.png)In the third example, we should not duplicate any character at all. Even though we would want to duplicate the label of the node $ 3 $ , by duplicating it we must also duplicate the label of the node $ 2 $ , which produces a worse result.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623E/967abfb10aaf17f05381c2a0e362eea9288d9011.png)There is no way to produce string "darkkcyan" from a tree with the initial string representation "darkcyan" :(.

## 样例 #1

### 输入

```
4 3
abab
2 3
0 0
0 4
0 0```

### 输出

```
baaaab```

## 样例 #2

### 输入

```
8 2
kadracyn
2 5
3 4
0 0
0 0
6 8
0 7
0 0
0 0```

### 输出

```
daarkkcyan```

## 样例 #3

### 输入

```
8 3
kdaracyn
2 5
0 3
0 4
0 0
6 8
0 7
0 0
0 0```

### 输出

```
darkcyan```

# AI分析结果



# 算法分类
**贪心算法**

## 题解思路与解决难点

### 核心思路
1. **中序遍历预处理**：通过中序遍历确定节点顺序，预处理每个节点复制是否能使字典序更小（`good[u]`）。
2. **DFS贪心选择**：优先处理左子树，若左子树需要复制，则当前节点必须复制；否则，若当前节点值得复制且剩余k允许，则选择复制。
3. **父节点条件约束**：复制的节点必须满足父节点已复制（根节点例外），通过DFS传递复制状态`isDup`。

### 解决难点
- **字典序优化判断**：通过比较当前节点字符与后续第一个不同字符的大小，确定复制是否有利。
- **父节点约束处理**：通过DFS递归传递父节点复制状态，确保复制条件满足。
- **贪心策略实现**：优先处理左子树，动态更新剩余k值，保证每一步选择最优。

---

## 题解评分（≥4星）
1. **Tyyyyyy的题解（5星）**  
   - 思路清晰：通过中序序列预处理`good`数组，DFS贪心选择复制节点。  
   - 代码简洁：仅需两次遍历，时间复杂度O(n)。  
   - 核心代码逻辑紧凑，可读性强。

2. **PosVII的题解（4星）**  
   - 类似贪心思路，预处理`ok`数组。  
   - 递归处理左子树，动态维护k值，代码简洁高效。

3. **Otomachi_Una的题解（4星）**  
   - 预处理`val`数组标记复制价值。  
   - 递归中维护`cst`和`vis`，逻辑清晰。

---

## 最优思路提炼
1. **中序遍历预处理**：确定节点顺序，标记每个节点复制是否有利。
2. **贪心DFS遍历**：  
   - 优先处理左子树，左子树需复制则强制当前节点复制。  
   - 左子树不复制时，若当前节点有利且k足够，则复制当前节点并消耗k。  
   - 若当前节点被复制，则递归处理右子树（否则右子树无法复制）。

---

## 同类型题与算法套路
- **相似题目**：  
  1. [CF1144G - Two Merged Sequences](https://codeforces.com/problemset/problem/1144/G)（贪心选择递增/递减序列）  
  2. [LeetCode 968. 监控二叉树](https://leetcode.cn/problems/binary-tree-cameras/)（贪心覆盖树节点）  
  3. [洛谷 P5018 对称二叉树](https://www.luogu.com.cn/problem/P5018)（树的结构判断）

---

## 推荐题目
1. **CF1110E Magic Stones**（贪心、差分）  
2. **P3942 将军令**（树的最优覆盖）  
3. **P2585 三色二叉树**（树形DP）

---

## 可视化算法演示
### 核心算法流程
1. **中序遍历**：生成节点序列，标记`good`数组（绿色表示有利，红色不利）。  
2. **DFS递归**：  
   - 左子树递归（蓝色高亮），处理完毕后回溯到父节点。  
   - 若左子树需复制，父节点强制复制（黄色高亮）。  
   - 若当前节点有利，消耗k值（显示剩余k），复制后进入右子树。  
3. **字符串构建**：动态拼接最终字符串，复制节点显示双字符。

### 复古像素风格实现
- **颜色方案**：8位色（绿、红、黄、蓝），节点用方块表示，字符居中。  
- **音效**：复制时播放“滴”声，k耗尽时播放低沉音效。  
- **Canvas动画**：树结构网格化，递归时显示路径，复制节点闪烁。  
- **交互控制**：暂停/继续按钮，速度滑动条调节递归速度。

---

## 核心代码实现
```cpp
// 预处理中序序列和good数组
vector<int> seq;
void precalc(int u) {
    if (l[u]) precalc(l[u]);
    seq.push_back(u);
    if (r[u]) precalc(r[u]);
}
// 标记复制有利的节点
char lst = c[seq.back()];
for (int i = n-2; i >= 0; i--) {
    int u = seq[i], v = seq[i+1];
    if (c[u] != c[v]) lst = c[v];
    good[u] = (c[u] < lst);
}
// DFS贪心选择复制节点
void dfs(int u, int cost) {
    if (!u || cost > k) return;
    dfs(l[u], cost + 1);
    if (isDup[l[u]]) isDup[u] = 1; // 左子树复制则强制复制
    else if (good[u] && k >= cost) {
        isDup[u] = 1;
        k -= cost;
    }
    if (isDup[u]) dfs(r[u], 1); // 复制后处理右子树
}
```

**关键点**：`good`数组标记、DFS中的`cost`传递和`k`的动态更新。

---
处理用时：71.78秒