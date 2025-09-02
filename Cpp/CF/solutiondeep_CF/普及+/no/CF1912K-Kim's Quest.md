# 题目信息

# Kim's Quest

## 题目描述

In the long-forgotten halls of Kombinatoria's ancient academy, a gifted mathematician named Kim is faced with an unusual challenge. They found an old sequence of integers, which is believed to be a cryptic message from the legendary Kombinatoria's Oracle, and Kim wants to decipher its hidden meaning.

Kim's mission is to find specific patterns within the sequence, known as Harmonious Subsequences. These are extraordinary subsequences where the sum of every three consecutive numbers is even, and each subsequence must be at least three numbers in length.

Given a sequence $ a_i $ ( $ 1 \le i \le n $ ) of length $ n $ , its subsequence of length $ m $ is equal to $ a_{b_1}, a_{b_2}, \ldots, a_{b_m} $ and is uniquely defined by a set of $ m $ indices $ b_j $ , such that $ 1 \le b_1 < b_2 < \ldots < b_m \le n $ . Subsequences given by different sets of indices $ b_j $ are considered different.

There's a twist in Kim's quest: the number of these Harmonious Subsequences could be overwhelming. To report the findings effectively, Kim must calculate the total number of these subsequences, presenting the answer as a remainder after dividing by the number $ 998\,244\,353 $ .

## 说明/提示

In the provided input data for the fifth sample, the sequence of numbers is split into three separate lines for clarity, but it should be understood that in the actual test data, the sequence is given in one line. The actual number of Harmonious Subsequences in this example is $ 4\,991\,221\,765 = 5 \times 998\,244\,353 $ , hence the output is zero as a result of finding its remainder after dividing by the number $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
1```

## 样例 #2

### 输入

```
5
2 8 2 6 4```

### 输出

```
16```

## 样例 #3

### 输入

```
5
5 7 1 3 5```

### 输出

```
0```

## 样例 #4

### 输入

```
11
3 1 4 1 5 9 2 6 5 3 6```

### 输出

```
386```

## 样例 #5

### 输入

```
54
2 1 1 1 1 2 1 2 2 2 2 1 1 1 2 1 1 2
2 1 2 2 2 2 2 2 2 1 1 1 2 2 1 1 1 1
2 2 1 1 2 2 2 2 2 1 1 1 2 2 1 2 1 1```

### 输出

```
0```

# AI分析结果

### 题目重写
在Kombinatoria古老学院的长廊中，一位名叫Kim的天才数学家面临着一个不寻常的挑战。他们发现了一个古老的整数序列，据信是来自传说中的Kombinatoria神谕的加密信息，Kim想要破译其中的隐藏含义。

Kim的任务是在序列中找到特定的模式，称为“和谐子序列”。这些子序列非常特殊，其中每三个连续数字的和都是偶数，并且每个子序列的长度必须至少为三个数字。

给定一个长度为$n$的序列$a_i$（$1 \le i \le n$），其长度为$m$的子序列等于$a_{b_1}, a_{b_2}, \ldots, a_{b_m}$，并由一组$m$个索引$b_j$唯一定义，使得$1 \le b_1 < b_2 < \ldots < b_m \le n$。由不同索引集$b_j$给出的子序列被认为是不同的。

Kim的任务有一个转折：这些和谐子序列的数量可能非常庞大。为了有效地报告发现，Kim必须计算这些子序列的总数，并将答案除以$998\,244\,353$后取余数。

### 算法分类
动态规划

### 题解分析与结论
该题目要求计算满足特定条件的子序列数量，核心在于如何高效地统计这些子序列。三位作者都采用了动态规划的方法，但具体实现和优化方式有所不同。

1. **sordio的题解**：
   - 使用状态压缩的思想，将两个二进制数压缩到一个十进制数中，简化了状态表示。
   - 通过分类讨论转移过程，确保每三个连续数字的和为偶数。
   - 时间复杂度为$O(n)$，效率较高。

2. **IGA_Indigo的题解**：
   - 将子序列的长度限制在3，简化了问题。
   - 通过定义四种满足条件的子序列状态，进行状态转移。
   - 代码简洁，思路清晰，但时间复杂度稍高。

3. **zhouzihang1的题解**：
   - 使用前缀和优化，减少了重复计算。
   - 通过定义不同长度的子序列状态，进行状态转移。
   - 时间复杂度为$O(n)$，效率较高。

### 所选高分题解
1. **sordio的题解**（4星）
   - 关键亮点：状态压缩和分类讨论转移过程，代码简洁高效。
   - 核心代码：
     ```cpp
     for(int i=1;i<=n;i++){
         for(int j=0;j<4;j++) dp[i][j]=dp[i-1][j]; //整体赋值
         if(a[i]==0){
             dp[i][2]+=dp[i-1][3];
             dp[i][0]+=dp[i-1][0];
             if(s0>=2) dp[i][0]+=(s0*(s0-1)/2)%mod;
             if(s1>=2) dp[i][2]+=(s1*(s1-1)/2)%mod;
             s0++;s10=(s10+s1)%mod;
         }else{
             dp[i][1]+=dp[i-1][2]+s10;
             dp[i][3]+=dp[i-1][1]+s01;
             s1++;s01=(s0+s01)%mod;
         } //分类讨论转移
         for(int j=0;j<4;j++) dp[i][j]%=mod; //整体取模
     }
     ```

2. **zhouzihang1的题解**（4星）
   - 关键亮点：前缀和优化，减少了重复计算，代码简洁。
   - 核心代码：
     ```cpp
     if(x&1)
     {
         f[3][3]+=f[2][1]+f[3][5];f[3][3]%=Mod;
         f[3][5]+=f[2][2]+f[3][6];f[3][5]%=Mod;
         f[2][1]+=f[1][0];f[2][1]%=Mod;
         f[2][3]+=f[1][1];f[2][3]%=Mod;
         f[1][1]++;
     }
     else
     {
         f[3][6]+=f[2][3]+f[3][3];f[3][6]%=Mod;
         f[3][0]+=f[2][0]+f[3][0];f[3][0]%=Mod;
         f[2][2]+=f[1][1];f[2][2]%=Mod;
         f[2][0]+=f[1][0];f[2][0]%=Mod;
         f[1][0]++;
     }
     ```

### 最优关键思路
- **状态压缩**：将两个二进制数压缩到一个十进制数中，简化了状态表示。
- **分类讨论转移**：根据当前数字的奇偶性，进行不同的状态转移，确保每三个连续数字的和为偶数。
- **前缀和优化**：通过前缀和减少重复计算，提高效率。

### 可拓展之处
- 类似问题可以扩展到更长的子序列或更复杂的条件，如每四个连续数字的和为偶数等。
- 可以使用其他优化方法，如滑动窗口或双指针，进一步优化时间复杂度。

### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：44.57秒