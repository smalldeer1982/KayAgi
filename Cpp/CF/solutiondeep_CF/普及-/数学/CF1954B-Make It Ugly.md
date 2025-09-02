# 题目信息

# Make It Ugly

## 题目描述

Let's call an array $ a $ beautiful if you can make all its elements the same by using the following operation an arbitrary number of times (possibly, zero):

- choose an index $ i $ ( $ 2 \le i \le |a| - 1 $ ) such that $ a_{i - 1} = a_{i + 1} $ , and replace $ a_i $ with $ a_{i - 1} $ .

You are given a beautiful array $ a_1, a_2, \dots, a_n $ . What is the minimum number of elements you have to remove from it in order for it to stop being beautiful? Swapping elements is prohibited. If it is impossible to do so, then output -1.

## 说明/提示

In the first testcase, it is impossible to modify the array in such a way that it stops being beautiful. An array consisting of identical numbers will remain beautiful no matter how many numbers we remove from it.

In the second testcase, you can remove the number at the index $ 5 $ , for example.

The resulting array will be $ [1, 2, 1, 2] $ . Let's check if it is beautiful. Two operations are available:

- Choose $ i = 2 $ : the array becomes $ [1, 1, 1, 2] $ . No more operations can be applied to it, and the numbers are not all the same.
- Choose $ i = 3 $ instead: the array becomes $ [1, 2, 2, 2] $ . No more operations can be applied to it either, and the numbers are still not all the same.

Thus, the array $ [1, 2, 1, 2] $ is not beautiful.

In the fourth testcase, you can remove the first three elements, for example. The resulting array $ [5, 3, 3, 3] $ is not beautiful.

## 样例 #1

### 输入

```
4
3
2 2 2
5
1 2 1 2 1
1
1
7
3 3 3 5 3 3 3```

### 输出

```
-1
1
-1
3```

# AI分析结果

### 题目重写
# 让它变丑

## 题目描述

我们称一个数组 $a$ 是“美丽的”，如果可以通过以下操作任意次数（包括零次）使其所有元素相同：

- 选择一个索引 $i$（$2 \le i \le |a| - 1$），使得 $a_{i - 1} = a_{i + 1}$，然后将 $a_i$ 替换为 $a_{i - 1}$。

给定一个美丽的数组 $a_1, a_2, \dots, a_n$。为了使它不再美丽，至少需要删除多少个元素？禁止交换元素。如果无法做到，则输出 -1。

## 说明/提示

在第一个测试用例中，无法通过删除元素使数组不再美丽。一个由相同数字组成的数组无论如何删除元素，都仍然是美丽的。

在第二个测试用例中，可以删除索引为 $5$ 的元素。结果数组为 $[1, 2, 1, 2]$。让我们检查它是否美丽。有两个操作可用：

- 选择 $i = 2$：数组变为 $[1, 1, 1, 2]$。无法再应用操作，且数字不全相同。
- 选择 $i = 3$：数组变为 $[1, 2, 2, 2]$。同样无法再应用操作，且数字不全相同。

因此，数组 $[1, 2, 1, 2]$ 不是美丽的。

在第四个测试用例中，可以删除前三个元素。结果数组 $[5, 3, 3, 3]$ 不是美丽的。

## 样例 #1

### 输入

```
4
3
2 2 2
5
1 2 1 2 1
1
1
7
3 3 3 5 3 3 3```

### 输出

```
-1
1
-1
3```

---

### 题解分析与结论

#### 综合分析与结论
本题的核心在于理解“美丽”数组的性质，即通过操作可以使所有元素相同。为了使数组不再美丽，需要破坏这种性质。大多数题解都围绕以下两个思路展开：
1. **破坏首尾相等**：通过删除元素使数组的首尾元素不再相等。
2. **破坏中间元素的连续性**：通过删除元素使两个与首元素不相等的元素相邻。

#### 最优关键思路
- **最短连续段删除**：找到数组中与首元素相等的最短连续段，删除这些元素可以使数组不再美丽。这种方法的时间复杂度为 $O(n)$，且代码实现简洁。
- **特判全相等情况**：如果数组中所有元素都相等，则无法通过删除元素使数组不再美丽，直接输出 -1。

#### 可拓展之处
- **类似问题**：类似的问题可以考察如何通过删除或修改元素使数组满足或不满足某种性质。例如，通过删除元素使数组变为回文，或通过修改元素使数组满足某种单调性。
- **算法套路**：这类问题通常可以通过贪心或双指针等简单算法解决，关键在于找到问题的核心性质并设计相应的策略。

#### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)

---

### 所选高质量题解

#### 1. 作者：_ckx_ (5星)
**关键亮点**：
- 思路清晰，通过 vector 存储与首元素不相等的下标，计算最小删除数量。
- 代码简洁，逻辑明确，易于理解。

**核心代码**：
```cpp
int ans = (int) 2e9; //初始化ans为无穷大 
int len = v.size();
for (int i = 1;i < len;i++)
{
    ans = min(ans ,v[i] - v[i - 1] - 1); //计算要删掉的数的数量，并计算min 
}
```

#### 2. 作者：xhhhh36 (5星)
**关键亮点**：
- 通过统计与首元素相等的连续段长度，找到最小删除数量。
- 代码简洁，逻辑清晰，易于实现。

**核心代码**：
```cpp
int ans = INT_MAX;
for (int i = 1;i <= n;i++)
{
    if (a[i] == a[1]) tmp++;
    else if (tmp) ans = min(ans,tmp),tmp = 0;
}
```

#### 3. 作者：Wrong_Accept (5星)
**关键亮点**：
- 通过“杀戮者”与“被杀者”的比喻，形象地解释了问题。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
int ans = 3e5 + 1;
for (int i = 0; i < n; i++)
{
    if (a[i] == f) ++cnt;
    else
    {
        ans = std::min(ans, cnt);
        cnt = 0;
    }
}
```

---

### 个人心得摘录
- **调试经历**：部分题解提到在调试过程中发现需要特判全相等的情况，否则会导致错误。
- **顿悟感想**：通过删除与首元素相等的最短连续段，可以有效地破坏数组的“美丽”性质。

---
处理用时：44.38秒