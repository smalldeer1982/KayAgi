# 题目信息

# Permutation Minimization by Deque

## 题目描述

In fact, the problems E1 and E2 do not have much in common. You should probably think of them as two separate problems.

A permutation $ p $ of size $ n $ is given. A permutation of size $ n $ is an array of size $ n $ in which each integer from $ 1 $ to $ n $ occurs exactly once. For example, $ [1, 4, 3, 2] $ and $ [4, 2, 1, 3] $ are correct permutations while $ [1, 2, 4] $ and $ [1, 2, 2] $ are not.

Let us consider an empty [deque](https://tinyurl.com/pfeucbux) (double-ended queue). A deque is a data structure that supports adding elements to both the beginning and the end. So, if there are elements $ [1, 5, 2] $ currently in the deque, adding an element $ 4 $ to the beginning will produce the sequence $ [\color{red}{4}, 1, 5, 2] $ , and adding same element to the end will produce $ [1, 5, 2, \color{red}{4}] $ .

The elements of the permutation are sequentially added to the initially empty deque, starting with $ p_1 $ and finishing with $ p_n $ . Before adding each element to the deque, you may choose whether to add it to the beginning or the end.

For example, if we consider a permutation $ p = [3, 1, 2, 4] $ , one of the possible sequences of actions looks like this:

 $ \quad $ 1.add $ 3 $ to the end of the deque:deque has a sequence $ [\color{red}{3}] $ in it; $ \quad $ 2.add $ 1 $ to the beginning of the deque:deque has a sequence $ [\color{red}{1}, 3] $ in it; $ \quad $ 3.add $ 2 $ to the end of the deque:deque has a sequence $ [1, 3, \color{red}{2}] $ in it; $ \quad $ 4.add $ 4 $ to the end of the deque:deque has a sequence $ [1, 3, 2, \color{red}{4}] $ in it;Find the lexicographically smallest possible sequence of elements in the deque after the entire permutation has been processed.

A sequence $ [x_1, x_2, \ldots, x_n] $ is lexicographically smaller than the sequence $ [y_1, y_2, \ldots, y_n] $ if there exists such $ i \leq n $ that $ x_1 = y_1 $ , $ x_2 = y_2 $ , $ \ldots $ , $ x_{i - 1} = y_{i - 1} $ and $ x_i < y_i $ . In other words, if the sequences $ x $ and $ y $ have some (possibly empty) matching prefix, and the next element of the sequence $ x $ is strictly smaller than the corresponding element of the sequence $ y $ . For example, the sequence $ [1, 3, 2, 4] $ is smaller than the sequence $ [1, 3, 4, 2] $ because after the two matching elements $ [1, 3] $ in the start the first sequence has an element $ 2 $ which is smaller than the corresponding element $ 4 $ in the second sequence.

## 说明/提示

One of the ways to get a lexicographically smallest permutation $ [1, 3, 2, 4] $ from the permutation $ [3, 1, 2, 4] $ (the first sample test case) is described in the problem statement.

## 样例 #1

### 输入

```
5
4
3 1 2 4
3
3 2 1
3
3 1 2
2
1 2
2
2 1```

### 输出

```
1 3 2 4 
1 2 3 
1 3 2 
1 2 
1 2```

# AI分析结果



**唯一算法分类**：贪心

---

### **题解思路、算法要点与解决难点**

- **核心思路**：贪心策略，每次将当前元素与队首比较，若更小则插入队首，否则插入队尾。  
- **解决难点**：如何保证每一步的局部最优选择最终得到全局字典序最小的队列。  
- **数据结构**：使用双端队列（`deque`）高效支持队首/队尾插入操作。  
- **关键变量**：维护当前队列的队首元素，作为插入位置的判断依据。  
- **正确性证明**：贪心策略确保每一步的队首尽可能小，从而保证字典序最小。

---

### **题解评分 (≥4星)**

1. **kimidonatsu**（⭐️⭐️⭐️⭐️⭐️）  
   - **亮点**：代码简洁，处理初始条件清晰（`i == 1` 特判），使用 `deque` 高效实现。  
   - **个人心得**：“字典序问题只需比较队首元素”。

2. **Leonid**（⭐️⭐️⭐️⭐️）  
   - **亮点**：代码逻辑与核心思路完全一致，无冗余操作。  
   - **优化点**：直接使用 `scanf` 输入，适合大规模数据。

3. **MYFJWHR**（⭐️⭐️⭐️⭐️）  
   - **亮点**：代码结构清晰，队列清空处理完善。  
   - **实践性**：注释明确，适合初学者理解。

---

### **最优思路或技巧提炼**

- **贪心决策**：始终比较当前元素与队首元素，选择更小的位置插入。  
- **边界处理**：初始元素直接插入，避免空队列访问异常。  
- **数据结构选择**：双端队列（`deque`）支持高效两端插入。

---

### **同类型题或类似算法套路**

- **通用解法**：字典序最小化问题常通过贪心策略，每一步选择最左可能的最小值。  
- **类似题目**：合并有序链表生成最小字典序序列、字符串拼接最小字典序等。

---

### **推荐题目**

1. **CF1157B**（字符串替换生成最大数）  
2. **Luogu P1090**（合并果子，贪心选择最小堆）  
3. **LeetCode 402**（移掉K位数字，单调栈贪心）

---

### **个人心得摘录**

- **Jerrlee**：“样例对的，但不代表只能是样例！”（强调贪心策略的普适性）  
- **Jairon314**：“直接递归即可做到 $O(n^2)$，但优化为 $O(n)$ 更优。”（对比不同复杂度实现）

---

### **可视化与算法演示**

**核心流程动画设计**：  
1. **初始状态**：空队列，高亮第一个元素准备插入。  
2. **插入步骤**：  
   - **当前元素 < 队首**：红色箭头指向队首，元素插入队首。  
   - **当前元素 ≥ 队首**：蓝色箭头指向队尾，元素插入队尾。  
3. **动态颜色**：队首元素黄色高亮，插入操作红/蓝闪烁。  

**复古像素风格**：  
- **颜色方案**：8-bit 调色板，队列显示为像素方块，插入动效配以经典音效。  
- **音效触发**：插入时播放“哔”声，完成时播放胜利音效。  

---

### **代码实现（核心逻辑）**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t, n, x;
    cin >> t;
    while (t--) {
        deque<int> dq;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> x;
            // 初始元素直接插入，后续比较队首
            if (dq.empty() || x < dq.front()) dq.push_front(x);
            else dq.push_back(x);
        }
        for (int v : dq) cout << v << " ";
        cout << endl;
    }
    return 0;
}
```

---
处理用时：88.43秒