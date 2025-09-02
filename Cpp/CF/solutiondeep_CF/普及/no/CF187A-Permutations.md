# 题目信息

# Permutations

## 题目描述

Happy PMP is freshman and he is learning about algorithmic problems. He enjoys playing algorithmic games a lot.

One of the seniors gave Happy PMP a nice game. He is given two permutations of numbers $ 1 $ through $ n $ and is asked to convert the first one to the second. In one move he can remove the last number from the permutation of numbers and inserts it back in an arbitrary position. He can either insert last number between any two consecutive numbers, or he can place it at the beginning of the permutation.

Happy PMP has an algorithm that solves the problem. But it is not fast enough. He wants to know the minimum number of moves to convert the first permutation to the second.

## 说明/提示

In the first sample, he removes number 1 from end of the list and places it at the beginning. After that he takes number 2 and places it between 1 and 3.

In the second sample, he removes number 5 and inserts it after 1.

In the third sample, the sequence of changes are like this:

- 1 5 2 3 4
- 1 4 5 2 3
- 1 3 4 5 2
- 1 2 3 4 5

 So he needs three moves.

## 样例 #1

### 输入

```
3
3 2 1
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1 5 2 3 4
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
1 5 2 3 4
1 2 3 4 5
```

### 输出

```
3
```

# AI分析结果



# Permutations

## 题目描述

Happy PMP 是一名大一新生，他正在学习算法问题。他非常喜欢玩算法游戏。

一位学长给 Happy PMP 一个有趣的游戏。他获得两个由数字 $1$ 到 $n$ 组成的排列，需要将第一个排列转换为第二个排列。每次操作中，他可以从排列末尾移除数字，并将其插入到任意位置（可以放在开头，或任意两个相邻数字之间）。

现在需要计算将第一个排列转换为第二个排列所需的最小操作次数。

## 说明/提示

第一个样例中，将末尾的 1 移到开头，再将末尾的 2 插入到 1 和 3 之间，共 2 次操作。

## 样例 #1

### 输入
```
3
3 2 1
1 2 3
```

### 输出
```
2
```

---

**算法分类**：贪心

**核心思路**：寻找两个排列的最长连续匹配前缀。操作次数 = 总长度 - 匹配长度

---

### 精选题解分析

#### 题解1（作者：nightwatch.ryan） ★★★★☆
**核心思路**：将第一个排列视为目标，遍历第二个排列，统计能连续匹配到目标排列开头的元素个数  
**代码亮点**：  
```cpp
int currentIndex = 1;
for (j=1 to n) {
    if (b[j] == a[currentIndex]) currentIndex++;
}
cout << n - currentIndex + 1;
```
**评分理由**：代码简洁，时间复杂度 O(n)，空间 O(1)

#### 题解2（作者：_txb_） ★★★★☆  
**核心思路**：与题解1思路一致，变量命名更直观  
**代码亮点**：  
```cpp
if(a[sum] == x) sum++;
cout << n-sum+1;
```
**个人心得**：通过样例3验证了正确性，强调"一样就累加"的直观逻辑

#### 题解3（作者：zhang_Jimmy） ★★★★☆  
**代码亮点**：使用更清晰的变量名 cnt 表示匹配位置  
**关键实现**：
```cpp
int cnt = 1;
for (i=1 to n) {
    if (b[i] == a[cnt]) cnt++;
}
cout << n - cnt + 1;
```

---

### 关键技巧总结
1. **逆向思维**：将问题转化为寻找最长连续匹配序列，而非直接模拟操作  
2. **贪心策略**：维护匹配指针，只需线性扫描即可得出结果  
3. **复杂度优化**：O(n) 时间 + O(1) 空间，完美处理 2e5 数据量

---

### 相似题目推荐
1. [P1439 最长公共子序列](https://www.luogu.com.cn/problem/P1439) - 同样需要寻找序列间的特殊匹配关系  
2. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102) - 双指针处理有序序列  
3. [CF1175E Minimal Segment Cover](https://codeforces.com/problemset/problem/1175/E) - 贪心策略的区间覆盖问题

---
处理用时：55.61秒