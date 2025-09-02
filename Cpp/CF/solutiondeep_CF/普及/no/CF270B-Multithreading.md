# 题目信息

# Multithreading

## 题目描述

Emuskald is addicted to Codeforces, and keeps refreshing the main page not to miss any changes in the "recent actions" list. He likes to read thread conversations where each thread consists of multiple messages.

Recent actions shows a list of $ n $ different threads ordered by the time of the latest message in the thread. When a new message is posted in a thread that thread jumps on the top of the list. No two messages of different threads are ever posted at the same time.

Emuskald has just finished reading all his opened threads and refreshes the main page for some more messages to feed his addiction. He notices that no new threads have appeared in the list and at the $ i $ -th place in the list there is a thread that was at the $ a_{i} $ -th place before the refresh. He doesn't want to waste any time reading old messages so he wants to open only threads with new messages.

Help Emuskald find out the number of threads that surely have new messages. A thread $ x $ surely has a new message if there is no such sequence of thread updates (posting messages) that both conditions hold:

1. thread $ x $ is not updated (it has no new messages);
2. the list order 1, 2, ..., $ n $ changes to $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ .

## 说明/提示

In the first test case, threads 2 and 5 are placed before the thread 1, so these threads must contain new messages. Threads 1, 3 and 4 may contain no new messages, if only threads 2 and 5 have new messages.

In the second test case, there may be no new messages at all, since the thread order hasn't changed.

In the third test case, only thread 1 can contain no new messages.

## 样例 #1

### 输入

```
5
5 2 1 3 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
4 3 2 1
```

### 输出

```
3
```

# AI分析结果



# Multithreading（题目翻译）

## 题目描述

Emuskald 沉迷于 Codeforces，不断刷新主页以免错过“最近动态”列表中的任何变化。他喜欢阅读线程对话，每个线程包含多条消息。

最近动态显示一个包含 $n$ 个不同线程的列表，按线程最新消息的时间排序。当线程收到新消息时，该线程会跳到列表顶部。不同线程的消息不会同时发布。

Emuskald 刚读完所有打开的线程并刷新主页。他发现列表中没有新增线程，且刷新后第 $i$ 位的线程是刷新前第 $a_i$ 位的线程。他只想打开有新消息的线程。

请帮助确定必定有新消息的线程数量。若存在满足以下条件的更新序列，则线程 $x$ 必定有新消息：
1. 线程 $x$ 未被更新（无新消息）
2. 列表顺序从 1,2,...,n 变为 $a_1,a_2,...,a_n$

## 说明/提示

第一个样例中，线程 2 和 5 出现在线程 1 之前，说明它们必须有新消息。线程 1、3、4 可能没有新消息，如果只有线程 2 和 5 被更新。

第二个样例中，可能没有新消息，因为列表顺序未变。

第三个样例中，只有线程 1 可能没有新消息。

---

**算法分类**：贪心

---

### 题解综合分析

所有题解均围绕**寻找最后一个逆序位置**的核心思路：
1. 通过遍历数组找到最后一个满足 $a[i] > a[i+1]$ 的位置 $i$
2. 答案即为 $i$，表示前 $i$ 个元素需要被操作

**关键结论**：最长递增后缀前的元素数量即为最小操作次数。该思路基于贪心策略，确保后续序列已有序，只需处理前面的元素。

---

### 精选题解（评分≥4★）

#### 1. FeiYu32（4★）
**亮点**：  
- 提出最长递增后缀思路，类比LIS问题  
- 代码简洁高效，时间复杂度 $O(n)$

**代码核心**：
```cpp
int main() {
    for(int i=1; i<=n; i++) {
        if(a[i]<a[i-1]) b = i-1;
    }
    cout << b;
}
```

#### 2. Leap_Frog（5★）
**亮点**：  
- 逆向思维转化题意（将目标序列变为初始序列）  
- 详细分步骤证明贪心策略  
- 代码清晰，包含关键注释

**个人心得**：  
"转化后的题意只允许操作第一个元素，即使当前位已满足，后续不满足也必须操作"

**代码核心**：
```cpp
for(int i=2; i<=n; i++) 
    if(a[i-1] > a[i]) r = i-1;
```

#### 3. 陈嘉逸2012（4★）
**亮点**：  
- 通过具体例子解释操作必要性  
- 强调题目约束条件的重要性

**代码核心**：
```cpp
for(int i=1; i<n; i++) 
    if(a[i] > a[i+1]) ans = i;
```

---

### 最优思路总结

**关键技巧**：  
- **逆向遍历法**：从后往前找到第一个破坏递增的位置  
- **单次遍历记录**：正向遍历时动态更新最后逆序位置

**思维模式**：  
将问题转化为寻找已有序的后缀子序列，利用贪心思想确定最小操作范围。

---

### 拓展练习
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)  
2. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)  
3. [P1102 最大子段和](https://www.luogu.com.cn/problem/P1115)

---
处理用时：72.54秒