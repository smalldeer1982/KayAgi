# 题目信息

# Alternative Thinking

## 题目描述

Kevin has just recevied his disappointing results on the USA Identification of Cows Olympiad (USAICO) in the form of a binary string of length $ n $ . Each character of Kevin's string represents Kevin's score on one of the $ n $ questions of the olympiad—'1' for a correctly identified cow and '0' otherwise.

However, all is not lost. Kevin is a big proponent of alternative thinking and believes that his score, instead of being the sum of his points, should be the length of the longest alternating subsequence of his string. Here, we define an alternating subsequence of a string as a not-necessarily contiguous subsequence where no two consecutive elements are equal. For example, $ {0,1,0,1} $ , $ {1,0,1} $ , and $ {1,0,1,0} $ are alternating sequences, while $ {1,0,0} $ and $ {0,1,0,1,1} $ are not.

Kevin, being the sneaky little puffball that he is, is willing to hack into the USAICO databases to improve his score. In order to be subtle, he decides that he will flip exactly one substring—that is, take a contiguous non-empty substring of his score and change all '0's in that substring to '1's and vice versa. After such an operation, Kevin wants to know the length of the longest possible alternating subsequence that his string could have.

## 说明/提示

In the first sample, Kevin can flip the bolded substring '10000011' and turn his string into '10011011', which has an alternating subsequence of length 5: '10011011'.

In the second sample, Kevin can flip the entire string and still have the same score.

## 样例 #1

### 输入

```
8
10000011
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2
01
```

### 输出

```
2
```

# AI分析结果



# 题目中文翻译

## 题目描述

Kevin 收到他在美国奶牛识别奥林匹克竞赛（USAICO）中的失望成绩，形式为一个长度为 $n$ 的二进制字符串。字符串的每个字符代表 Kevin 在一道题上的得分——'1' 表示正确识别奶牛，'0' 表示错误。

但并非全无希望。Kevin 提倡"替代思维"，认为他的分数应该是字符串中最长交替子序列的长度。交替子序列定义为相邻元素不同的非连续子序列。例如，$0,1,0,1$ 是交替序列，而 $1,0,0$ 则不是。

Kevin 可以翻转一个连续子串（将子串中的 '0' 变为 '1'，'1' 变为 '0'）。求翻转后可能的最长交替子序列长度。

## 样例 #1

### 输入
```
8
10000011
```

### 输出
```
5
```

## 样例 #2

### 输入
```
2
01
```

### 输出
```
2
```

---

**算法分类**  
动态规划 | 贪心

---

**题解分析与结论**  
本题存在两种核心解法：

1. **动态规划**：通过定义三种状态（未翻转/已结束翻转/正在翻转）处理所有可能的翻转情况，时间复杂度 $O(n)$。
2. **贪心策略**：通过观察发现答案最多增加 2，统计连续相同字符段的数量分情况处理，时间复杂度 $O(n)$。

两种方法均能高效解决问题，但贪心解法代码更简洁，动态规划解法更易扩展其他变形问题。

---

**优质题解推荐**

1. **zplqwq（动态规划）** ⭐⭐⭐⭐⭐  
   - 关键思路：设计三个状态 `f[i][0]`、`f[i][1]`、`f[i][2]` 分别表示未翻转、已结束翻转、正在翻转时的最大长度。通过当前字符与前一个字符的关系分情况转移状态。  
   - 代码亮点：状态转移方程清晰，覆盖所有翻转可能。  
   ```cpp
   // 核心状态转移逻辑
   if (a[i] == a[i-1]) {
       f[i][0] = f[i-1][0];
       f[i][1] = max(f[i-1][2] + 1, f[i-1][1]);
       f[i][2] = max(f[i-1][2], f[i-1][0] + 1);
   } else {
       f[i][0] = f[i-1][0] + 1;
       f[i][1] = max(f[i-1][1] + 1, f[i-1][2]);
       f[i][2] = max(f[i-1][2] + 1, f[i-1][0]);
   }
   ```

2. **jch123（贪心）** ⭐⭐⭐⭐  
   - 关键思路：统计原始交替子序列长度，若有≥3的连续相同字符则答案+2，其他情况根据连续段数量调整。  
   - 代码亮点：简洁高效，仅需一次遍历统计关键特征。  
   ```cpp
   // 统计原始长度与连续段
   for (int i=1; i<n; i++) {
       if (a[i] != a[i-1]) ans++;
       else cnt++;
       if (a[i]==a[i-1] && i<n-1 && a[i]==a[i+1]) flag=1;
   }
   // 分情况输出
   if (flag || cnt >= 2) ans += 2;
   else if (cnt >= 1) ans++;
   ```

3. **查无此人（动态规划）** ⭐⭐⭐⭐  
   - 关键思路：与 zplqwq 类似但更简洁的状态设计，直接通过三个状态递推，代码可读性强。  
   - 代码亮点：利用布尔标志简化条件判断。  
   ```cpp
   bool flag = (a[i] == a[i-1]);
   f[i][0] = flag ? f[i-1][0] : f[i-1][0] + 1;
   f[i][1] = flag ? max(f[i-1][2]+1, f[i-1][1]) : max(f[i-1][1]+1, f[i-1][2]);
   ```

---

**关键技巧总结**  
1. **状态设计**：动态规划中通过状态分离翻转阶段，典型的三段式设计（未翻转/已结束翻转/正在翻转）。  
2. **贪心观察**：任何翻转最多使答案增加 2，通过统计连续段特征快速计算最优解。  

**拓展思考**  
- 类似问题可考虑状态分离（如区间操作问题）。  
- 若允许多次翻转，需重新设计状态或贪心策略。  

**相似题目推荐**  
1. [P1095 守望者的逃离 - 动态规划状态设计](https://www.luogu.com.cn/problem/P1095)  
2. [P1352 没有上司的舞会 - 状态转移与选择](https://www.luogu.com.cn/problem/P1352)  
3. [CF626C Block Towers - 贪心与数学结合](https://www.luogu.com.cn/problem/CF626C)

---
处理用时：162.60秒