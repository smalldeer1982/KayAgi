# 题目信息

# Tokitsukaze and Good 01-String (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is that the harder version asks additionally for a minimum number of subsegments.

Tokitsukaze has a binary string $ s $ of length $ n $ , consisting only of zeros and ones, $ n $ is even.

Now Tokitsukaze divides $ s $ into the minimum number of contiguous subsegments, and for each subsegment, all bits in each subsegment are the same. After that, $ s $ is considered good if the lengths of all subsegments are even.

For example, if $ s $ is "11001111", it will be divided into "11", "00" and "1111". Their lengths are $ 2 $ , $ 2 $ , $ 4 $ respectively, which are all even numbers, so "11001111" is good. Another example, if $ s $ is "1110011000", it will be divided into "111", "00", "11" and "000", and their lengths are $ 3 $ , $ 2 $ , $ 2 $ , $ 3 $ . Obviously, "1110011000" is not good.

Tokitsukaze wants to make $ s $ good by changing the values of some positions in $ s $ . Specifically, she can perform the operation any number of times: change the value of $ s_i $ to '0' or '1' ( $ 1 \leq i \leq n $ ). Can you tell her the minimum number of operations to make $ s $ good? Meanwhile, she also wants to know the minimum number of subsegments that $ s $ can be divided into among all solutions with the minimum number of operations.

## 说明/提示

In the first test case, one of the ways to make $ s $ good is the following.

Change $ s_3 $ , $ s_6 $ and $ s_7 $ to '0', after that $ s $ becomes "1100000000", it can be divided into "11" and "00000000", which lengths are $ 2 $ and $ 8 $ respectively, the number of subsegments of it is $ 2 $ . There are other ways to operate $ 3 $ times to make $ s $ good, such as "1111110000", "1100001100", "1111001100", the number of subsegments of them are $ 2 $ , $ 4 $ , $ 4 $ respectively. It's easy to find that the minimum number of subsegments among all solutions with the minimum number of operations is $ 2 $ .

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
3 2
0 3
0 1
0 1
3 1```

# AI分析结果



### 题目翻译

**Tokitsukaze 和好的 01 字符串（困难版）**

**题目描述**  
这是该问题的困难版本。两个版本的唯一区别在于困难版本额外要求最小化子段数量。

Tokitsukaze 有一个长度为 $n$（偶数）的二进制字符串 $s$，仅包含 0 和 1。她希望将 $s$ 分割为最少的连续子段，使得每个子段内字符相同且长度均为偶数。通过修改某些位置的字符（0 变 1 或反之），求：  
1. 使字符串合法所需的最小修改次数。  
2. 在满足最小修改次数的前提下，分割后的最少子段数。

**样例解释**  
例如，输入为 `100110`，输出为 `3 1`。原字符串需修改 3 处，最终可变为全 0 或全 1，形成 1 个子段。

---

### 题解分析与结论

**关键思路**  
1. **最小修改次数**：将字符串每两个字符视为一个块。若块内两字符不同，则需修改其中一个，贡献一次操作。统计所有不同块的数量即为答案。  
2. **最少子段数**：仅考虑原字符串中字符相同的块（即未被修改的块），记录这些块的颜色序列。合并相邻相同颜色块后的序列长度即为最少子段数。若无此类块，则子段数为 1。

**算法优化**  
- **贪心统计**：直接遍历字符串的每个块，统计修改次数和有效颜色序列，时间复杂度 $O(n)$。  
- **去重技巧**：通过记录上一个有效块颜色，合并相邻相同颜色块，避免重复计数。

---

### 精选题解

#### 题解1：jasonliujiahua（⭐⭐⭐⭐⭐）  
**亮点**  
- 简洁高效，两步遍历分别处理两问。  
- 利用数组记录有效颜色，去重后直接统计段数。  
**核心代码**  
```cpp
void work() {
    for (int i=0; i+1<n; i+=2) {
        if (s[i] != s[i+1]) ans++; // 第一问
    }
    for (int i=0; i+1<n; i+=2) {
        if (s[i] == s[i+1]) {      // 处理有效块
            if (la == 0 || a[la] != s[i]-'0') 
                a[++la] = s[i]-'0'; 
        }
    }
    cout << ans << " " << max(la,1) << endl;
}
```

#### 题解2：Tx_Lcy（⭐⭐⭐⭐）  
**亮点**  
- 贪心合并相邻块，动态维护上一个块颜色。  
- 处理修改块时优先与前一个块颜色一致，减少段数。  
**核心代码**  
```cpp
for (int i=1; i<=n; i+=2) {
    if (s[i] == s[i+1]) {
        if (la != (s[i]-'0')) ++ans, la = s[i]-'0';
    } else {
        s[i] = char(la + '0'); // 修改为与前一块相同
        s[i+1] = s[i];
    }
}
```

---

### 关键技巧总结  
1. **分块处理**：将字符串视为多个长度为 2 的块，分别处理修改和段数统计。  
2. **颜色合并**：通过记录前一有效块颜色，动态合并相同颜色块，减少段数。  
3. **特判全修改**：当所有块均需修改时，子段数必为 1。

---

### 同类题目推荐  
1. [CF1520D - Similar Pairs](https://codeforces.com/problemset/problem/1325/B)（分块奇偶性）  
2. [LeetCode 1578 - 使字符串相邻字符不同](https://leetcode.com/problems/minimum-time-to-make-rope-colorful/)（贪心修改）  
3. [洛谷 P1090 - 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心合并策略）

---
处理用时：98.90秒