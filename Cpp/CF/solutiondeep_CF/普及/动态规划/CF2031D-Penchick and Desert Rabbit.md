# 题目信息

# Penchick and Desert Rabbit

## 题目描述

Dedicated to pushing himself to his limits, Penchick challenged himself to survive the midday sun in the Arabian Desert!

While trekking along a linear oasis, Penchick spots a desert rabbit preparing to jump along a line of palm trees. There are $ n $ trees, each with a height denoted by $ a_i $ .

The rabbit can jump from the $ i $ -th tree to the $ j $ -th tree if exactly one of the following conditions is true:

- $ j < i $ and $ a_j > a_i $ : the rabbit can jump backward to a taller tree.
- $ j > i $ and $ a_j < a_i $ : the rabbit can jump forward to a shorter tree.

For each $ i $ from $ 1 $ to $ n $ , determine the maximum height among all trees that the rabbit can reach if it starts from the $ i $ -th tree.

## 说明/提示

In the first test case, the initial heights of trees are $ a = [2, 3, 1, 4] $ .

- If the rabbit starts from the first tree, it can jump to the third tree as $ 3 > 1 $ and $ 1 < 2 $ . Then, the rabbit can jump to the second tree as $ 2 < 3 $ and $ 3 > 1 $ . It can be proved that the rabbit cannot reach the fourth tree; hence, the maximum height of the tree that the rabbit can reach is $ a_2 = 3 $ .
- If the rabbit starts from the fourth tree, it does not need to jump anywhere as it is already at the highest tree.

In the second test case, the rabbit can jump to the first tree regardless of which tree it starts from.

In the fifth test case, if the rabbit starts from the fifth tree, it can jump to the fourth tree. Then the rabbit can jump to the seventh tree and finally reach the sixth tree. Therefore, the maximum height of the tree that the rabbit can reach is $ 8 $ .

## 样例 #1

### 输入

```
5
4
2 3 1 4
5
5 4 3 2 1
4
2 1 1 3
4
1 1 3 1
8
2 4 1 6 3 8 5 7```

### 输出

```
3 3 3 4 
5 5 5 5 5 
2 2 2 3 
1 1 3 3 
8 8 8 8 8 8 8 8```

# AI分析结果

### 题目重写

**题目描述**

Penchick 挑战自己在阿拉伯沙漠的正午阳光下生存！

在沿着一条线性的绿洲行进时，Penchick 发现了一只沙漠兔子准备在一排棕榈树之间跳跃。共有 $n$ 棵树，每棵树的高度为 $a_i$。

兔子可以从第 $i$ 棵树跳到第 $j$ 棵树，当且仅当以下条件之一成立：

- $j < i$ 且 $a_j > a_i$：兔子可以向后跳到更高的树。
- $j > i$ 且 $a_j < a_i$：兔子可以向前跳到更矮的树。

对于每个 $i$ 从 $1$ 到 $n$，确定兔子从第 $i$ 棵树出发后能够到达的树的最大高度。

**说明/提示**

在第一个测试用例中，树的初始高度为 $a = [2, 3, 1, 4]$。

- 如果兔子从第一棵树出发，它可以跳到第三棵树，因为 $3 > 1$ 且 $1 < 2$。然后，兔子可以跳到第二棵树，因为 $2 < 3$ 且 $3 > 1$。可以证明兔子无法到达第四棵树，因此兔子能够到达的树的最大高度为 $a_2 = 3$。
- 如果兔子从第四棵树出发，它不需要跳，因为它已经在最高的树上了。

在第二个测试用例中，无论兔子从哪棵树出发，它都可以跳到第一棵树。

在第五个测试用例中，如果兔子从第五棵树出发，它可以跳到第四棵树。然后，兔子可以跳到第七棵树，最后到达第六棵树。因此，兔子能够到达的树的最大高度为 $8$。

**样例输入**

```
5
4
2 3 1 4
5
5 4 3 2 1
4
2 1 1 3
4
1 1 3 1
8
2 4 1 6 3 8 5 7
```

**样例输出**

```
3 3 3 4 
5 5 5 5 5 
2 2 2 3 
1 1 3 3 
8 8 8 8 8 8 8 8
```

### 题解分析与结论

#### 题解对比与评分

1. **TonviaSzt 的题解**（4星）
   - **亮点**：提供了三种不同的解题思路，包括赛时做法、分段法和 Editorial 的最优解法。思路清晰，代码实现较为简洁。
   - **关键思路**：通过维护前缀最大值和后缀最小值，实现了 $O(Tn)$ 的复杂度，避免了复杂的图论操作。
   - **代码实现**：使用并查集和树状数组优化了跳跃路径的处理。

2. **w9095 的题解**（4星）
   - **亮点**：通过动态规划的思路，维护前缀最大值和后缀最小值，简化了问题的复杂度。
   - **关键思路**：从后往前扫描，利用前缀最大值和后缀最小值来判断跳跃的可能性，避免了复杂的图论操作。
   - **代码实现**：代码简洁，逻辑清晰，易于理解。

3. **Lyw_and_Segment_Tree 的题解**（4星）
   - **亮点**：通过维护前缀最大值和后缀最小值，实现了 $O(Tn)$ 的复杂度，思路清晰，代码实现简洁。
   - **关键思路**：从后往前扫描，利用前缀最大值和后缀最小值来判断跳跃的可能性，避免了复杂的图论操作。
   - **代码实现**：代码简洁，逻辑清晰，易于理解。

#### 最优关键思路与技巧

- **前缀最大值与后缀最小值**：通过维护前缀最大值和后缀最小值，可以快速判断兔子从某个位置出发后能够到达的最大高度。这种方法避免了复杂的图论操作，大大简化了问题的复杂度。
- **从后往前扫描**：从后往前扫描可以有效地利用已经计算好的结果，避免重复计算，提高算法的效率。

#### 可拓展之处

- **类似问题**：这种通过维护前缀最大值和后缀最小值来简化问题的方法，可以应用于其他需要判断跳跃或连通性的问题，如跳跃游戏、连通块问题等。
- **数据结构优化**：在处理跳跃路径时，可以使用树状数组或并查集等数据结构来优化路径的处理，提高算法的效率。

#### 推荐题目

1. **洛谷 P1091 跳跃游戏**（https://www.luogu.com.cn/problem/P1091）
2. **洛谷 P3379 连通块**（https://www.luogu.com.cn/problem/P3379）
3. **洛谷 P3388 最大跳跃**（https://www.luogu.com.cn/problem/P3388）

#### 个人心得摘录

- **TonviaSzt**：赛时并查集不用 dsu 超时了一发，难绷。
- **w9095**：赛时 A,B,C 共计吃了 $5$ 发罚时，这就是我的真实实力！来补篇题解。
- **Lyw_and_Segment_Tree**：这个题的思路其实是比较显然的，可以维护前缀最大值和后缀最小值来计算答案。

### 核心代码片段

**TonviaSzt 的代码片段**

```cpp
for (int i = n; i >= 1; i--) {
    if (pre[i] > suf[i + 1]) {
        ans[i] = ans[i + 1];
    } else {
        ans[i] = pre[i];
    }
}
```

**w9095 的代码片段**

```cpp
for (int i = n; i >= 1; i--) {
    if (mx[i] > mi[i + 1]) {
        ans[i] = ans[i + 1];
    } else {
        ans[i] = mx[i];
    }
}
```

**Lyw_and_Segment_Tree 的代码片段**

```cpp
for (int i = n; i >= 1; i--) {
    if (pre[i] > suf[i + 1]) {
        ans[i] = ans[i + 1];
    } else {
        ans[i] = pre[i];
    }
}
```

这些代码片段展示了如何通过维护前缀最大值和后缀最小值来判断跳跃的可能性，并更新每个位置的答案。

---
处理用时：46.00秒