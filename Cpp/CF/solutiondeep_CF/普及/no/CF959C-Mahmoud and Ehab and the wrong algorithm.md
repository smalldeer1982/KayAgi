# 题目信息

# Mahmoud and Ehab and the wrong algorithm

## 题目描述

Mahmoud was trying to solve the vertex cover problem on trees. The problem statement is:

Given an undirected tree consisting of $ n $ nodes, find the minimum number of vertices that cover all the edges. Formally, we need to find a set of vertices such that for each edge $ (u,v) $ that belongs to the tree, either $ u $ is in the set, or $ v $ is in the set, or both are in the set. Mahmoud has found the following algorithm:

- Root the tree at node $ 1 $ .
- Count the number of nodes at an even depth. Let it be $ evenCnt $ .
- Count the number of nodes at an odd depth. Let it be $ oddCnt $ .
- The answer is the minimum between $ evenCnt $ and $ oddCnt $ .

The depth of a node in a tree is the number of edges in the shortest path between this node and the root. The depth of the root is 0.

Ehab told Mahmoud that this algorithm is wrong, but he didn't believe because he had tested his algorithm against many trees and it worked, so Ehab asked you to find 2 trees consisting of $ n $ nodes. The algorithm should find an incorrect answer for the first tree and a correct answer for the second one.

## 说明/提示

In the first sample, there is only 1 tree with 2 nodes (node $ 1 $ connected to node $ 2 $ ). The algorithm will produce a correct answer in it so we printed $ -1 $ in the first section, but notice that we printed this tree in the second section.

In the second sample:

In the first tree, the algorithm will find an answer with 4 nodes, while there exists an answer with 3 nodes like this: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959C/080040c1176abdd5ada4ff45524faae8f6709ce5.png) In the second tree, the algorithm will find an answer with 3 nodes which is correct: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959C/2d5dc2017c538f7d5b27b72e32312118454ea6c6.png)

## 样例 #1

### 输入

```
2
```

### 输出

```
-1
1 2
```

## 样例 #2

### 输入

```
8
```

### 输出

```
1 2
1 3
2 4
2 5
3 6
4 7
4 8
1 2
1 3
2 4
2 5
2 6
3 7
6 8```

# AI分析结果

### 题目内容
Mahmoud 和 Ehab 的错误算法

#### 题目描述
Mahmoud 试图解决树上的顶点覆盖问题。问题描述如下：

给定一个由 $n$ 个节点组成的无向树，找到覆盖所有边的最小顶点数。形式上，我们需要找到一个顶点集合，使得对于树中的每条边 $(u,v)$，$u$ 或 $v$ 或两者都在集合中。Mahmoud 找到了以下算法：

- 将树以节点 $1$ 为根。
- 计算偶数深度的节点数，记为 $evenCnt$。
- 计算奇数深度的节点数，记为 $oddCnt$。
- 答案是 $evenCnt$ 和 $oddCnt$ 中的最小值。

节点在树中的深度是从该节点到根的最短路径中的边数。根的深度为 $0$。

Ehab 告诉 Mahmoud 这个算法是错误的，但 Mahmoud 不相信，因为他已经在许多树上测试了这个算法并且它都有效，所以 Ehab 请你找到两棵由 $n$ 个节点组成的树。算法应该在第一棵树上找到错误的答案，在第二棵树上找到正确的答案。

#### 说明/提示
在第一个样例中，只有一棵由 $2$ 个节点组成的树（节点 $1$ 连接到节点 $2$）。算法将产生一个正确的答案，因此我们在第一部分输出 $-1$，但请注意我们在第二部分输出了这棵树。

在第二个样例中：
- 在第一棵树中，算法将找到 $4$ 个节点的答案，而存在一个 $3$ 个节点的答案。
- 在第二棵树中，算法将找到 $3$ 个节点的答案，这是正确的。

#### 样例 #1
##### 输入
```
2
```
##### 输出
```
-1
1 2
```

#### 样例 #2
##### 输入
```
8
```
##### 输出
```
1 2
1 3
2 4
2 5
3 6
4 7
4 8
1 2
1 3
2 4
2 5
2 6
3 7
6 8
```

### 算法分类
构造

### 题解分析与结论
题目要求构造两棵树，使得给定的算法在第一棵树上产生错误答案，在第二棵树上产生正确答案。题解主要通过构造特定的树结构来实现这一目标。

### 所选题解
#### 题解作者：attack (赞：2)
- **星级**：4
- **关键亮点**：通过构造一个“上面三个点，下面一个菊花”的树结构，成功地展示了算法的错误性。代码简洁，思路清晰。
- **核心实现思想**：首先输出一个特定的树结构，使得算法产生错误答案，然后输出一个链式结构，使得算法产生正确答案。
```cpp
int N = read();
if(N == 2 || N == 3 || N == 4 || N == 5) printf("-1\n");
else {
    printf("1 2\n");
    printf("1 3\n");
    printf("1 4\n");
    for(int i = 5; i <= N; i++) 
        printf("3 %d\n", i);
}
for(int i = 1; i <= N - 1; i++) 
    printf("%d %d\n", i, i + 1);
```

#### 题解作者：OcTar (赞：0)
- **星级**：4
- **关键亮点**：通过将编号为偶数的点连在 $1$ 上，将编号为奇数的点连在 $2$ 上，构造了一个反例树，并说明了链式结构可以满足算法的正确性。
- **核心实现思想**：首先输出一个反例树，然后输出一个链式结构。
```cpp
if (n <= 5) cout << -1 << '\n';
else {
    for (int i = 2; i <= n; i++) {
        if (i & 1) cout << 2 << " " << i << '\n';
        else cout << 1 << " " << i << '\n';
    }
}
for (int i = 1; i < n; i++) cout << i << " " << i + 1 << '\n';
```

### 最优关键思路或技巧
1. **构造反例树**：通过将节点按照特定规则连接，使得算法的计算结果与实际最小顶点覆盖数不符。
2. **构造正确树**：使用链式结构或菊花图等简单结构，使得算法的计算结果与实际最小顶点覆盖数一致。

### 可拓展之处
1. **树的结构多样性**：可以通过构造不同的树结构来测试算法的鲁棒性。
2. **算法优化**：可以进一步研究如何在更复杂的树结构中找到最小顶点覆盖数。

### 推荐题目
1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
2. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
3. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)

### 个人心得
- **调试经历**：在构造反例树时，需要仔细考虑树的结构，确保算法的计算结果与实际不符。
- **踩坑教训**：在构造正确树时，选择简单的结构可以避免复杂的计算和错误。

---
处理用时：34.14秒