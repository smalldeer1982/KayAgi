# 题目信息

# Meaning Mean

## 题目描述

Pak Chanek has an array $ a $ of $ n $ positive integers. Since he is currently learning how to calculate the floored average of two numbers, he wants to practice it on his array $ a $ .

While the array $ a $ has at least two elements, Pak Chanek will perform the following three-step operation:

1. Pick two different indices $ i $ and $ j $ ( $ 1 \leq i, j \leq |a| $ ; $ i \neq j $ ), note that $ |a| $ denotes the current size of the array $ a $ .
2. Append $ \lfloor \frac{a_i+a_j}{2} \rfloor $ $ ^{\text{∗}} $ to the end of the array.
3. Remove elements $ a_i $ and $ a_j $ from the array and concatenate the remaining parts of the array.

For example, suppose that $ a=[5,4,3,2,1,1] $ . If we choose $ i=1 $ and $ j=5 $ , the resulting array will be $ a=[4,3,2,1,3] $ . If we choose $ i=4 $ and $ j=3 $ , the resulting array will be $ a=[5,4,1,1,2] $ .

After all operations, the array will consist of a single element $ x $ . Find the maximum possible value of $ x $ if Pak Chanek performs the operations optimally.

 $ ^{\text{∗}} $ $ \lfloor x \rfloor $ denotes the floor function of $ x $ , which is the greatest integer that is less than or equal to $ x $ . For example, $ \lfloor 6 \rfloor = 6 $ , $ \lfloor 2.5 \rfloor=2 $ , $ \lfloor -3.6 \rfloor=-4 $ and $ \lfloor \pi \rfloor=3 $

## 说明/提示

In the first test case, the array is initially $ a=[1,7,8,4,5] $ . Pak Chanek will perform the following operations:

1. Pick $ i=1 $ and $ j=2 $ , then $ a=[8,4,5,4] $ .
2. Pick $ i=3 $ and $ j=2 $ , then $ a=[8,4,4] $ .
3. Pick $ i=2 $ and $ j=3 $ , then $ a=[8,4] $ .
4. Pick $ i=1 $ and $ j=2 $ , then $ a=[6] $ .

After all the operations, the array consists of a single element $ x=6 $ . It can be proven that there is no series of operations that results in $ x $ greater than $ 6 $ in the end.

## 样例 #1

### 输入

```
3
5
1 7 8 4 5
3
2 6 5
5
5 5 5 5 5```

### 输出

```
6
4
5```

# AI分析结果



### 题目内容中文翻译

#### 题目描述

Pak Chanek 有一个包含 $n$ 个正整数的数组 $a$。他正在学习如何计算两个数的向下取整平均值，并希望在自己的数组 $a$ 上练习。

当数组 $a$ 中至少有两个元素时，Pak Chanek 会执行以下三步操作：

1. 选择两个不同的下标 $i$ 和 $j$（$1 \leq i, j \leq |a|$；$i \neq j$），其中 $|a|$ 表示当前数组 $a$ 的长度。
2. 将 $\lfloor \frac{a_i + a_j}{2} \rfloor$ 添加到数组末尾。
3. 从数组中移除元素 $a_i$ 和 $a_j$，并连接剩余部分。

例如，假设 $a = [5,4,3,2,1,1]$。如果选择 $i=1$ 和 $j=5$，结果数组变为 $a = [4,3,2,1,3]$。若选择 $i=4$ 和 $j=3$，则数组变为 $a = [5,4,1,1,2]$。

当所有操作完成后，数组只剩一个元素 $x$。求 Pak Chanek 通过最优操作可能得到的 $x$ 的最大值。

#### 样例 #1

##### 输入

```
3
5
1 7 8 4 5
3
2 6 5
5
5 5 5 5 5
```

##### 输出

```
6
4
5
```

---

### 题解分析与结论

#### 关键思路与算法

本题的核心在于如何通过合并操作最大化最终剩余的元素。通过分析，最优策略是**每次合并当前最小的两个元素**。这一策略可以通过最小堆（优先队列）高效实现：

1. **贪心策略**：每次合并最小的两个元素，保留较大的元素，使得后续合并中较大的值能更晚被处理，从而最大化最终结果。
2. **数学性质**：合并两个较小的数后，较大的数保留到后续步骤，最终合并时的最大值会更接近原数组的最大值。

#### 最优题解代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            pq.push(x);
        }
        while (pq.size() > 1) {
            int a = pq.top(); pq.pop();
            int b = pq.top(); pq.pop();
            pq.push((a + b) / 2);
        }
        cout << pq.top() << endl;
    }
    return 0;
}
```

#### 实现要点
- **最小堆维护**：使用优先队列（`priority_queue`）快速获取当前最小的两个元素。
- **循环合并**：每次取出两个最小元素，合并后放回堆中，直到只剩一个元素。
- **时间复杂度**：$O(n \log n)$，适用于较大规模数据。

#### 总结与扩展

- **类似问题**：哈夫曼编码问题（合并策略不同，但数据结构类似）。
- **举一反三**：当需要动态维护极值并频繁合并时，优先队列是常用工具。
- **洛谷推荐题目**：
  - P1090（合并果子，哈夫曼树）
  - P6033（合并果子加强版）
  - P2168（荷马史诗，哈夫曼树扩展）

---
处理用时：150.52秒