# 题目信息

# Vasya and Golden Ticket

## 题目描述

Recently Vasya found a golden ticket — a sequence which consists of $ n $ digits $ a_1a_2\dots a_n $ . Vasya considers a ticket to be lucky if it can be divided into two or more non-intersecting segments with equal sums. For example, ticket $ 350178 $ is lucky since it can be divided into three segments $ 350 $ , $ 17 $ and $ 8 $ : $ 3+5+0=1+7=8 $ . Note that each digit of sequence should belong to exactly one segment.

Help Vasya! Tell him if the golden ticket he found is lucky or not.

## 说明/提示

In the first example the ticket can be divided into $ 7 $ , $ 34 $ and $ 52 $ : $ 7=3+4=5+2 $ .

In the second example it is impossible to divide ticket into segments with equal sum.

## 样例 #1

### 输入

```
5
73452
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
1248
```

### 输出

```
NO
```

# AI分析结果

### 题目内容重写（中文）

#### Vasya和黄金票

**题目描述**

最近，Vasya发现了一张黄金票——一个由$n$个数字$a_1a_2\dots a_n$组成的序列。Vasya认为这张票是幸运的，如果它可以被分成两个或更多个不相交的段，且每个段的和相等。例如，票$350178$是幸运的，因为它可以被分成三个段$350$、$17$和$8$：$3+5+0=1+7=8$。注意，序列中的每个数字必须恰好属于一个段。

帮助Vasya！告诉他他找到的黄金票是否是幸运的。

**说明/提示**

在第一个例子中，票可以被分成$7$、$34$和$52$：$7=3+4=5+2$。

在第二个例子中，无法将票分成和相等的段。

**样例 #1**

输入：
```
5
73452
```
输出：
```
YES
```

**样例 #2**

输入：
```
4
1248
```
输出：
```
NO
```

---

### 题解分析与结论

#### 综合分析

本题的核心问题是如何判断一个数字序列是否可以被分成多个段，且每个段的和相等。题解中主要采用了以下几种思路：

1. **暴力搜索**：通过递归或迭代的方式，尝试将序列分成多个段，并检查每段的和是否相等。
2. **枚举分段数**：通过枚举可能的分段数，计算每段的和，并检查是否可以将序列分成满足条件的段。
3. **前缀和优化**：利用前缀和来快速计算任意子段的和，从而减少计算量。

#### 最优关键思路

1. **枚举分段数**：通过枚举可能的分段数$k$，计算每段的和$sum/k$，然后检查是否可以将序列分成$k$段，每段的和为$sum/k$。这种方法的时间复杂度较低，且易于实现。
2. **前缀和优化**：利用前缀和数组来快速计算任意子段的和，从而在枚举分段数时减少计算量。

#### 推荐题解

1. **作者：XUQING (4星)**
   - **关键亮点**：采用了递归搜索的方式，通过剪枝优化了搜索过程，代码清晰易懂。
   - **核心代码**：
     ```cpp
     bool dfs(string s, int tot, int f) {
         if(s.length() == 1 && s[0] - '0' == tot)
             return true;
         for(int i = 1; i <= s.length(); i++) {
             int ans = sum(s.substr(0, i));
             if(i == s.length() && ans == tot)
                 return true;
             if(ans > tot && f)
                 return false;
             if(ans == tot || !f) {
                 bool b = dfs(s.substr(i, s.length()+1), ans, f + 1);
                 if(b)
                     return true;
             }
         }
         return false;
     }
     ```

2. **作者：lichenfan (4星)**
   - **关键亮点**：通过枚举分段数，直接模拟分段过程，代码简洁高效。
   - **核心代码**：
     ```cpp
     if(sum%i==0){
         for(int j=1;j<=n;j++){
             ans+=a[j];
             if(ans==sum/i) ans=0;
             if(ans>sum/i) break;
             if(j==n){
                 cout<<"YES";
                 return 0;
             }
         }
     }
     ```

3. **作者：_Qer (4星)**
   - **关键亮点**：通过枚举分段数，利用前缀和优化了分段检查过程，代码简洁且高效。
   - **核心代码**：
     ```cpp
     bool check(int s) {
         int tsum = 0;
         for (int i = 1; i <= n; ++i) {
             tsum += a[i];
             if (tsum == s) {
                 tsum = 0;
             } else if (tsum > s) {
                 return false;
             }
         }
         return !tsum;
     }
     ```

#### 扩展思路

- **同类型题**：类似的分段求和问题可以通过枚举分段数或利用前缀和优化来解决。
- **类似算法套路**：在涉及分段求和的问题中，前缀和和枚举分段数是常见的优化手段。

#### 推荐题目

1. [P1042 分段求和](https://www.luogu.com.cn/problem/P1042)
2. [P1043 数字分段](https://www.luogu.com.cn/problem/P1043)
3. [P1044 分段最大值](https://www.luogu.com.cn/problem/P1044)

#### 个人心得摘录

- **XUQING**：通过递归搜索的方式，结合剪枝优化，成功解决了问题。调试过程中发现，特判长度为1的情况非常重要。
- **lichenfan**：直接枚举分段数，模拟分段过程，代码简洁高效。调试时发现，特判分段数为1的情况可以避免不必要的计算。
- **_Qer**：利用前缀和优化了分段检查过程，代码简洁且高效。调试时发现，特判全零情况可以避免WA。

---
处理用时：38.75秒