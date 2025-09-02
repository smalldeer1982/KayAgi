# 题目信息

# Tokitsukaze and Good 01-String (easy version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is that the harder version asks additionally for a minimum number of subsegments.

Tokitsukaze has a binary string $ s $ of length $ n $ , consisting only of zeros and ones, $ n $ is even.

Now Tokitsukaze divides $ s $ into the minimum number of contiguous subsegments, and for each subsegment, all bits in each subsegment are the same. After that, $ s $ is considered good if the lengths of all subsegments are even.

For example, if $ s $ is "11001111", it will be divided into "11", "00" and "1111". Their lengths are $ 2 $ , $ 2 $ , $ 4 $ respectively, which are all even numbers, so "11001111" is good. Another example, if $ s $ is "1110011000", it will be divided into "111", "00", "11" and "000", and their lengths are $ 3 $ , $ 2 $ , $ 2 $ , $ 3 $ . Obviously, "1110011000" is not good.

Tokitsukaze wants to make $ s $ good by changing the values of some positions in $ s $ . Specifically, she can perform the operation any number of times: change the value of $ s_i $ to '0' or '1'( $ 1 \leq i \leq n $ ). Can you tell her the minimum number of operations to make $ s $ good?

## 说明/提示

In the first test case, one of the ways to make $ s $ good is the following.

Change $ s_3 $ , $ s_6 $ and $ s_7 $ to '0', after that $ s $ becomes "1100000000", it can be divided into "11" and "00000000", which lengths are $ 2 $ and $ 8 $ respectively. There are other ways to operate $ 3 $ times to make $ s $ good, such as "1111110000", "1100001100", "1111001100".

In the second, third and fourth test cases, $ s $ is good initially, so no operation is required.

## 样例 #1

### 输入

```
5
10
1110011000
8
11001111
2
00
2
11
6
100110```

### 输出

```
3
0
0
0
3```

# AI分析结果



# Tokitsukaze and Good 01-String (easy version)

## 题目描述

Tokitsukaze 有一个长度为 $n$（偶数）的 01 字符串 $s$。定义「好的 01 字符串」为所有连续相同字符子段的长度均为偶数的字符串。求将给定字符串变为「好的」所需的最小修改次数。

**输入样例：**
```
5
10
1110011000
8
11001111
2
00
2
11
6
100110
```
**输出样例：**
```
3
0
0
0
3
```

---

### 综合题解分析

#### 关键思路总结
1. **相邻配对法**：每两个字符为一组，若不同则需修改其中一个，操作次数+1。最终保证每个子段长度为偶数。
   - **正确性**：处理后每对字符相同，连续相同字符的段长度必为偶数。
   - **复杂度**：$O(n)$ 时间，$O(1)$ 空间。

2. **分段处理法**：将字符串分割为连续子段，调整奇数长度段为偶数。
   - **实现**：每次遇到奇数段时，将当前段长度-1，下一段长度+1，操作次数+1。
   - **复杂度**：$O(n)$ 时间，$O(n)$ 空间。

---

### 高星题解推荐

#### 题解一（5星）：相邻配对法
**作者**：_acat_  
**亮点**：代码简洁高效，直接统计相邻不同对的数量。
```cpp
for(int i=1; i<n; i+=2) {
    if(a[i] != a[i-1]) cnt++;
}
```
**思路**：每两个字符一组，不同则修改，操作次数即不同对数。

#### 题解二（4星）：分段处理法
**作者**：accomplishment  
**亮点**：通过分割段处理问题本质，适合理解奇偶调整过程。
```cpp
vector<int> list; // 存储每段长度
rep(i,0,list.size()-2) {
    if(list[i]%2 ==1) {
        list[i]--; list[i+1]++; res++;
    }
}
```
**思路**：处理每段奇偶性，通过相邻段调整保证全偶。

#### 题解三（5星）：简化配对法
**作者**：SSqwq_  
**亮点**：与题解一同思路，代码风格更紧凑。
```cpp
for(int i=1; i<n; i+=2) {
    if(a[i] != a[i-1]) ans++;
}
```
**技巧**：遍历时跳步处理，确保每对字符同步判断。

---

### 最优思路提炼
**核心技巧**：相邻字符配对统计差异。  
**正确性证明**：每次修改保证两个字符相同，形成的连续段长度必为偶数。  
**算法选择**：优先采用相邻配对法，时空最优且实现简单。

---

### 拓展与相似题目
1. **CF1678B2**（本题困难版）：在求最小操作次数的同时，还需最小化子段数量。
2. **洛谷P1141**（01迷宫）：处理连续块相关问题。
3. **洛谷P5018**（对称二叉树）：利用奇偶性质分析结构。
4. **洛谷P5661**（公交换乘）：通过分段处理优化策略。

---
处理用时：227.80秒