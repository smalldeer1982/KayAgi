# 题目信息

# Equal XOR Segments

## 题目描述

Let us call an array $ x_1,\dots,x_m $ interesting if it is possible to divide the array into $ k>1 $ parts so that [bitwise XOR](http://tiny.cc/xor_wiki_eng) of values from each part are equal.

More formally, you must split array $ x $ into $ k $ consecutive segments, each element of $ x $ must belong to exactly $ 1 $ segment. Let $ y_1,\dots,y_k $ be the XOR of elements from each part respectively. Then $ y_1=y_2=\dots=y_k $ must be fulfilled.

For example, if $ x = [1, 1, 2, 3, 0] $ , you can split it as follows: $ [\color{blue}1], [\color{green}1], [\color{red}2, \color{red}3, \color{red}0] $ . Indeed $ \color{blue}1=\color{green}1=\color{red}2 \oplus \color{red}3\oplus \color{red}0 $ .

You are given an array $ a_1,\dots,a_n $ . Your task is to answer $ q $ queries:

- For fixed $ l $ , $ r $ , determine whether the subarray $ a_l,a_{l+1},\dots,a_r $ is interesting.

## 说明/提示

Explanation for the first test case:

The first query is described in the statement.

In the second query, we should divide $ [1,2,3] $ . A possible division is $ [1,2],[3] $ , since $ 1\oplus 2=3 $ .

It can be shown that for queries $ 3,4,5 $ , the subarrays are not interesting.

## 样例 #1

### 输入

```
4
5 5
1 1 2 3 0
1 5
2 4
3 5
1 3
3 4
5 5
1 2 3 4 5
1 5
2 4
3 5
1 3
2 3
7 4
12 9 10 9 10 11 9
1 5
1 7
2 6
2 7
11 4
0 0 1 0 0 1 0 1 1 0 1
1 2
2 5
6 9
7 11```

### 输出

```
YES
YES
NO
NO
NO

YES
NO
NO
YES
NO

NO
NO
NO
NO

YES
NO
YES
YES```

# AI分析结果



### 题目中文重写

#### Equal XOR Segments

**题目描述**  
我们称一个数组 $x_1,\dots,x_m$ 为"有趣的"，若其可被划分为 $k>1$ 个连续部分，使得每部分的异或值相等。

具体来说，需将数组 $x$ 划分为 $k$ 个连续段，每段的异或值 $y_1=y_2=\dots=y_k$。例如 $x = [1,1,2,3,0]$ 可划分为三段：$[1], [1], [2,3,0]$，每段异或值均为1。

给定数组 $a_1,\dots,a_n$，回答 $q$ 次询问：子数组 $a_l,a_{l+1},\dots,a_r$ 是否为有趣的。

---

### 题解综合分析

#### 核心思路
所有题解均基于**前缀异或和**与分情况讨论：
1. **整体异或为0**：当 $s_r = s_{l-1}$ 时（$s$ 为前缀异或数组），总能分割为两部分。
2. **异或非零时需分三段**：寻找两个分割点 $x,y$ 满足：
   - $s_x = s_r$（第一段异或值等于整体）
   - $s_y = s_{l-1}$（第三段异或值等于整体）
   - 且 $x < y$

#### 最优题解选评

1. **LEE114514（5星）**
   - **亮点**：代码简洁高效，利用map直接存储异或值位置，通过两次二分快速定位分割点。
   - **关键代码**：
     ```cpp
     posy=lower_bound(mp[a[x-1]].begin(),mp[a[x-1]].end(),y);
     posx=lower_bound(mp[a[y]].begin(),mp[a[y]].end(),x);
     if(posy==...||*posx<*posy..."YES":"NO");
     ```
   - **心得**：逆向思维通过等式变形快速推导分割条件。

2. **Special_Tony（4星）**
   - **亮点**：离散化处理提升查找效率，详细证明分三段必要性。
   - **关键优化**：将异或值映射到连续整数，减少哈希冲突。

3. **lin_er（4星）**
   - **亮点**：通过贪心选择最左最右分割点，确保判断逻辑完备。
   - **代码特色**：双重二分分别处理左右边界，逻辑清晰。

---

### 关键思路总结
1. **前缀异或性质**：将区间异或转化为前缀异或差。
2. **分情况讨论**：异或为零时直接可分；非零时需找三段分割。
3. **高效查找**：利用哈希表或离散化存储位置，通过二分快速验证分割点存在性。

---

### 相似题目推荐
1. [P3131 Subsequences Summing to Sevens](https://www.luogu.com.cn/problem/P3131)  
   **相似点**：前缀和取模性质+区间划分

2. [P3405 [USACO16DEC] Cities and States S](https://www.luogu.com.cn/problem/P3405)  
   **相似点**：哈希映射处理特殊配对关系

3. [CF1176F Destroy it!](https://www.luogu.com.cn/problem/CF1176F)  
   **相似点**：动态规划结合位运算优化

---

### 关键代码片段（LEE114514版）
```cpp
// 前缀异或预处理
for(int i=1;i<=n;++i) a[i]^=a[i-1], mp[a[i]].emplace_back(i);

// 查询处理
if(a[y] == a[x-1]) puts("YES"); 
else {
    auto posy = lower_bound(mp[a[x-1]].begin(), mp[a[x-1]].end(), y);
    auto posx = lower_bound(mp[a[y]].begin(), mp[a[y]].end(), x);
    // 判断是否存在有效分割点
    puts(*posx < *posy ? "YES" : "NO");
}
```
**实现思想**：两次二分分别查找满足条件的最小最大分割点，验证其位置关系。

---
处理用时：57.15秒