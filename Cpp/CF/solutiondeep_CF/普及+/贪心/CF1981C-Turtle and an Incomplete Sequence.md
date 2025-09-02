# 题目信息

# Turtle and an Incomplete Sequence

## 题目描述

Turtle was playing with a sequence $ a_1, a_2, \ldots, a_n $ consisting of positive integers. Unfortunately, some of the integers went missing while playing.

Now the sequence becomes incomplete. There may exist an arbitrary number of indices $ i $ such that $ a_i $ becomes $ -1 $ . Let the new sequence be $ a' $ .

Turtle is sad. But Turtle remembers that for every integer $ i $ from $ 1 $ to $ n - 1 $ , either $ a_i = \left\lfloor\frac{a_{i + 1}}{2}\right\rfloor $ or $ a_{i + 1} = \left\lfloor\frac{a_i}{2}\right\rfloor $ holds for the original sequence $ a $ .

Turtle wants you to help him complete the sequence. But sometimes Turtle makes mistakes, so you need to tell him if you can't complete the sequence.

Formally, you need to find another sequence $ b_1, b_2, \ldots, b_n $ consisting of positive integers such that:

- For every integer $ i $ from $ 1 $ to $ n $ , if $ a'_i \ne -1 $ , then $ b_i = a'_i $ .
- For every integer $ i $ from $ 1 $ to $ n - 1 $ , either $ b_i = \left\lfloor\frac{b_{i + 1}}{2}\right\rfloor $ or $ b_{i + 1} = \left\lfloor\frac{b_i}{2}\right\rfloor $ holds.
- For every integer $ i $ from $ 1 $ to $ n $ , $ 1 \le b_i \le 10^9 $ .

If there is no sequence $ b_1, b_2, \ldots, b_n $ that satisfies all of the conditions above, you need to report $ -1 $ .

## 说明/提示

In the first test case, $ [4, 2, 1, 2, 1, 2, 1, 3] $ can also be the answer, while $ [4, 2, 5, 10, 5, 2, 1, 3] $ and $ [4, 2, 1, 2, 1, 2, 1, 4] $ cannot.

In the second test case, $ [1, 2, 5, 2] $ can also be the answer.

From the fourth to the sixth test cases, it can be shown that there is no answer, so you should output $ -1 $ .

## 样例 #1

### 输入

```
9
8
-1 -1 -1 2 -1 -1 1 -1
4
-1 -1 -1 -1
6
3 -1 -1 -1 9 -1
4
-1 5 -1 6
4
2 -1 -1 3
4
1 2 3 4
2
4 2
5
-1 3 -1 3 6
13
-1 -1 3 -1 -1 -1 -1 7 -1 -1 3 -1 -1```

### 输出

```
4 9 4 2 4 2 1 2
7 3 6 13
3 1 2 4 9 18
-1
-1
-1
4 2
6 3 1 3 6
3 1 3 1 3 7 3 7 3 1 3 1 3```

# AI分析结果



### 题目内容中文翻译

**题目名：乌龟与不完整序列**

**题目描述**

乌龟在玩一个由正整数组成的序列 $a_1, a_2, \ldots, a_n$。不幸的是，玩耍过程中有些整数丢失了。

现在序列变得不完整。可能存在任意数量的索引 $i$ 使得 $a_i$ 变为 $-1$。新序列记为 $a'$。

乌龟很伤心。但他记得在原始序列 $a$ 中，对于每个 $1 \le i \le n-1$，要么 $a_i = \left\lfloor\frac{a_{i+1}}{2}\right\rfloor$，要么 $a_{i+1} = \left\lfloor\frac{a_i}{2}\right\rfloor$。

乌龟希望你帮他补全序列。若无法补全则需报告。

**形式化要求**

构造新序列 $b_1, b_2, \ldots, b_n$，满足：

1. 若 $a'_i \ne -1$，则 $b_i = a'_i$。
2. 相邻元素满足除法关系。
3. $1 \le b_i \le 10^9$。

若无解输出 $-1$。

**样例与说明**

（样例输入输出详见原题）

---

### 题解分析与结论

#### 核心思路
1. **二进制路径模型**：将数值变化视为满二叉树的边操作（除2为父节点，乘2或乘2+1为子节点），问题转化为寻找起点到终点的路径。
2. **LCA最短路径**：通过计算两个数值的最近公共祖先（LCA），确定最小步数。剩余步数需满足奇偶性要求。
3. **奇偶性填充**：若剩余步数为偶数，可在终点附近反复横跳（交替乘2/除2）填充多余位置。

#### 最优题解

1. **EuphoricStar（★★★★★）**
   - **亮点**：利用满二叉树模型，通过LCA计算最短路径，清晰处理奇偶性约束。
   - **核心代码**：
     ```cpp
     vector<int> path(int x, int y) {
         // 计算x到y的路径（类似LCA路径合并）
         while (x > y) x >>= 1;
         while (y > x) y >>= 1;
         // ...合并路径返回
     }
     void solve() {
         // 处理前缀和后缀的-1，填充中间段
     }
     ```

2. **Disjoint_cat（★★★★☆）**
   - **亮点**：二进制位操作视角，通过公共前缀快速计算最小步数，利用`__builtin_clz`优化。
   - **技巧**：直接操作二进制位，减少数值运算次数。

3. **Louis_lxy（★★★★☆）**
   - **亮点**：详细注释与分段处理逻辑，适合理解填充细节。
   - **代码片段**：
     ```cpp
     // 处理中间段填充
     for (int j = l + (int)p.size(), o = 1; j <= r; ++j, o ^= 1) {
         a[j] = (o ? a[j-1] * 2 : a[j-1] / 2);
     }
     ```

---

### 关键技巧总结

1. **二进制树模型**：将数值变化建模为树结构，快速计算路径。
2. **奇偶性判定**：剩余步数必须为偶数才能填充。
3. **分段处理**：独立处理每个非-1段之间的区域，确保局部合法。

---

### 推荐相似题目

1. **CF1353E** - 构造满足相邻位关系的二进制序列。
2. **P1430** - 序列变换与区间操作。
3. **CF1099E** - 树形结构下的路径构造问题。

---
处理用时：44.58秒