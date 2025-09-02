# 题目信息

# Permutation Transformation

## 题目描述

A permutation — is a sequence of length $ n $ integers from $ 1 $ to $ n $ , in which all the numbers occur exactly once. For example, $ [1] $ , $ [3, 5, 2, 1, 4] $ , $ [1, 3, 2] $ — permutations, and $ [2, 3, 2] $ , $ [4, 3, 1] $ , $ [0] $ — no.

Polycarp was recently gifted a permutation $ a[1 \dots n] $ of length $ n $ . Polycarp likes trees more than permutations, so he wants to transform permutation $ a $ into a rooted binary tree. He transforms an array of different integers into a tree as follows:

- the maximum element of the array becomes the root of the tree;
- all elements to the left of the maximum — form a left subtree (which is built according to the same rules but applied to the left part of the array), but if there are no elements to the left of the maximum, then the root has no left child;
- all elements to the right of the maximum — form a right subtree (which is built according to the same rules but applied to the right side of the array), but if there are no elements to the right of the maximum, then the root has no right child.

For example, if he builds a tree by permutation $ a=[3, 5, 2, 1, 4] $ , then the root will be the element $ a_2=5 $ , and the left subtree will be the tree that will be built for the subarray $ a[1 \dots 1] = [3] $ , and the right one — for the subarray $ a[3 \dots 5] = [2, 1, 4] $ . As a result, the following tree will be built:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1490D/0aafe2e3bc6081fb6190b15e93678e9e1d0a0393.png)The tree corresponding to the permutation $ a=[3, 5, 2, 1, 4] $ .Another example: let the permutation be $ a=[1, 3, 2, 7, 5, 6, 4] $ . In this case, the tree looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1490D/5e7d3506add8fba00a43e087fca1d5c43d5b6f50.png)The tree corresponding to the permutation $ a=[1, 3, 2, 7, 5, 6, 4] $ .Let us denote by $ d_v $ the depth of the vertex $ a_v $ , that is, the number of edges on the path from the root to the vertex numbered $ a_v $ . Note that the root depth is zero. Given the permutation $ a $ , for each vertex, find the value of $ d_v $ .

## 样例 #1

### 输入

```
3
5
3 5 2 1 4
1
1
4
4 3 1 2```

### 输出

```
1 0 2 3 1 
0 
0 1 3 2```

# AI分析结果

### 题目内容
# 排列变换

## 题目描述
排列是一个长度为 $n$ 的整数序列，其中的整数取值范围是从 $1$ 到 $n$，且每个数字恰好出现一次。例如，$[1]$，$[3, 5, 2, 1, 4]$，$[1, 3, 2]$ 是排列，而 $[2, 3, 2]$，$[4, 3, 1]$，$[0]$ 不是。

Polycarp 最近得到了一个长度为 $n$ 的排列 $a[1 \dots n]$。Polycarp 喜欢树胜过排列，所以他想将排列 $a$ 转换为一棵有根二叉树。他将一个由不同整数组成的数组转换为树的方法如下：
- 数组中的最大元素成为树的根；
- 最大元素左边的所有元素形成左子树（按照相同的规则构建，但应用于数组的左半部分），但如果最大元素左边没有元素，则根没有左子节点；
- 最大元素右边的所有元素形成右子树（按照相同的规则构建，但应用于数组的右半部分），但如果最大元素右边没有元素，则根没有右子节点。

例如，如果他根据排列 $a = [3, 5, 2, 1, 4]$ 构建一棵树，那么根将是元素 $a_2 = 5$，左子树将是为子数组 $a[1 \dots 1] = [3]$ 构建的树，右子树将是为子数组 $a[3 \dots 5] = [2, 1, 4]$ 构建的树。结果将构建出如下的树：

![树对应排列 a=[3, 5, 2, 1, 4]](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1490D/0aafe2e3bc6081fb6190b15e93678e9e1d0a0393.png)

另一个例子：设排列为 $a = [1, 3, 2, 7, 5, 6, 4]$。在这种情况下，树如下所示：

![树对应排列 a=[1, 3, 2, 7, 5, 6, 4]](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1490D/5e7d3506add8fba00a43e087fca1d5c43d5b6f50.png)

我们用 $d_v$ 表示顶点 $a_v$ 的深度，即从根到编号为 $a_v$ 的顶点的路径上的边数。注意根的深度为零。给定排列 $a$，求每个顶点的 $d_v$ 值。

## 样例 #1
### 输入
```
3
5
3 5 2 1 4
1
1
4
4 3 1 2
```
### 输出
```
1 0 2 3 1 
0 
0 1 3 2
```

### 算法分类
深度优先搜索 DFS

### 综合分析与结论
这些题解的核心思路都是基于题目给定的规则，通过递归的方式构建二叉树并计算节点深度。算法要点在于每次在给定区间内找到最大值作为根节点，然后分别对其左右区间递归构建子树，并在递归过程中记录节点深度。解决难点主要在于对递归边界条件的处理以及深度的正确记录。

多数题解思路清晰，直接按照题目描述进行模拟实现。不同之处主要在于代码实现的细节，如记录深度的方式、递归函数的参数设置等。

### 通用建议与扩展思路
对于此类题目，关键在于理解题目给定的构建规则，并通过合适的递归或分治策略实现。可以进一步拓展的方向包括优化算法复杂度，例如当数据范围增大时，如何通过更高效的数据结构（如线段树等）来快速找到区间最大值，从而降低时间复杂度。同时，可以思考如何将这种基于排列构建二叉树的模型应用到其他实际问题中。

### 洛谷相似题目推荐
- [P1030 求先序排列](https://www.luogu.com.cn/problem/P1030)：通过中序和后序遍历结果求先序遍历，同样涉及树的构建与遍历相关知识。
- [P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)：根据给定的表达式构建二叉树并进行遍历，考察对二叉树构建和遍历的理解。
- [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)：在二叉树上进行动态规划，虽然涉及知识点更多，但基础是对二叉树结构的处理，与本题构建二叉树有一定关联。

### 个人心得摘录与总结
- **冰糖鸽子**：提到因数据范围小，即使DFS复杂度高达 $n^2$ 也能通过，强调了数据范围对解题策略的影响。
- **Fa1thful**：指出有人误将此题当作并查集问题，强调了准确理解题意，避免思路偏差。
- **_caiji_**：对DFS建树复杂度进行了分析，指出最小 $O(n\log n)$，最大 $O(n^2)$，让读者对算法复杂度有更清晰认识。
- **Wuyanru**：强调在递归函数中加入边界判断语句的重要性，否则会进入死循环，提醒注意递归边界条件处理。 

---
处理用时：49.42秒