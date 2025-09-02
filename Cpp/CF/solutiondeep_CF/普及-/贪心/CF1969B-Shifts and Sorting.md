# 题目信息

# Shifts and Sorting

## 题目描述

Let's define a cyclic shift of some string $ s $ as a transformation from $ s_1 s_2 \dots s_{n-1} s_{n} $ into $ s_{n} s_1 s_2 \dots s_{n-1} $ . In other words, you take one last character $ s_n $ and place it before the first character while moving all other characters to the right.

You are given a binary string $ s $ (a string consisting of only 0-s and/or 1-s).

In one operation, you can choose any substring $ s_l s_{l+1} \dots s_r $ ( $ 1 \le l < r \le |s| $ ) and cyclically shift it. The cost of such operation is equal to $ r - l + 1 $ (or the length of the chosen substring).

You can perform the given operation any number of times. What is the minimum total cost to make $ s $ sorted in non-descending order?

## 说明/提示

In the first test case, you can choose the whole string and perform a cyclic shift: 10 $ \rightarrow $ 01. The length of the substring is $ 2 $ , so the cost is $ 2 $ .

In the second test case, the string is already sorted, so you don't need to perform any operations.

In the third test case, one of the optimal strategies is the next:

1. choose substring $ [1, 3] $ : 11000 $ \rightarrow $ 01100;
2. choose substring $ [2, 4] $ : 01100 $ \rightarrow $ 00110;
3. choose substring $ [3, 5] $ : 00110 $ \rightarrow $ 00011.

 The total cost is $ 3 + 3 + 3 = 9 $ .

## 样例 #1

### 输入

```
5
10
0000
11000
101011
01101001```

### 输出

```
2
0
9
5
11```

# AI分析结果



# 题目重写

## 题目描述

定义一个字符串 $s$ 的循环移位操作为：将最后一个字符 $s_n$ 移动到第一个字符的位置，其他字符依次右移。例如，字符串 $s_1 s_2 \dots s_{n-1} s_n$ 经过循环移位后变为 $s_n s_1 s_2 \dots s_{n-1}$。

给定一个二进制字符串 $s$（仅由 '0' 和 '1' 组成），每次操作可以选择任意子串 $s_l s_{l+1} \dots s_r$（$1 \le l < r \le |s|$）进行循环移位，操作的代价为子串长度 $r-l+1$。求将字符串变为非递减序列的最小总代价。

## 说明/提示

- 非递减序列即所有 '0' 在前，'1' 在后
- 样例解释见原题

---

# 题解分析与结论

### 核心思路总结
所有优质题解均采用贪心策略：**遍历字符串，每当遇到 '0' 时累加其前方连续 '1' 的数量加 1 作为代价**。证明关键点在于：
1. 每个 '0' 必须移动到所有 '1' 之前
2. 通过单次操作移动多个 '1' 块比逐次移动更优
3. 代价计算式为 $\sum (cnt\_ones + 1)$，其中 $cnt\_ones$ 是当前 '0' 前的连续 '1' 数

### 最优题解推荐

#### 题解1：_WHITE_NIGHT_（★★★★★）
**亮点**：严谨的数学证明 + 复杂度分析  
**思路**：
- 将问题转化为移动每个 '0' 所需的代价
- 证明合并移动连续 '1' 块的优化效果
- 公式推导总代价为 $\sum_{i=1}^t (d - t - p_i + i)$ 的简化形式

**代码核心**：
```cpp
int ans = 0, cnt_ones = 0;
for (char c : s) {
    if (c == '1') cnt_ones++;
    else if (cnt_ones) ans += cnt_ones + 1;
}
```

#### 题解2：lihongqian__int128（★★★★☆）
**亮点**：代码简洁 + 直观贪心解释  
**思路**：
- 维护 '1' 的计数器
- 遇到 '0' 时直接累加当前 '1' 数加 1

**个人心得**：
> "若遇到的 0 没有及时提到前面去，会导致后续操作代价更高"

#### 题解3：cheng2010（★★★★☆）
**亮点**：最简代码实现  
**代码核心**：
```cpp
int cnt=0, sum=0;
for(char c : s) {
    if(c=='1') cnt++;
    else if(cnt) sum += cnt+1;
}
```

---

# 关键代码实现

所有题解共享同一核心逻辑：
```cpp
int main() {
    int T; cin >> T;
    while(T--) {
        string s; cin >> s;
        int ans = 0, cnt_ones = 0;
        for (char c : s) {
            if (c == '1') cnt_ones++;
            else if (cnt_ones) ans += cnt_ones + 1;
        }
        cout << ans << endl;
    }
}
```
**实现思想**：
- `cnt_ones` 记录当前遇到的连续 '1' 数量
- 遇到 '0' 时，该 '0' 需要跨越前方所有 '1'，代价为 `cnt_ones`（移动每个 '1'） + 1（移动 '0' 本身）

---

# 拓展与练习

### 同类问题套路
- **模式识别**：处理有序性要求的最小操作代价
- **优化思路**：将连续同类型元素的移动合并计算
- **变形方向**：操作代价模型变化（如固定代价、区间反转等）

### 推荐练习题
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 贪心删除策略
2. [P1321 单词覆盖](https://www.luogu.com.cn/problem/P1321) - 子串操作与覆盖问题 
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心优先队列（不同场景相同策略）

---
处理用时：63.08秒