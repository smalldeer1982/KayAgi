# 题目信息

# Binary String Sorting

## 题目描述

You are given a binary string $ s $ consisting of only characters 0 and/or 1.

You can perform several operations on this string (possibly zero). There are two types of operations:

- choose two consecutive elements and swap them. In order to perform this operation, you pay $ 10^{12} $ coins;
- choose any element from the string and remove it. In order to perform this operation, you pay $ 10^{12}+1 $ coins.

Your task is to calculate the minimum number of coins required to sort the string $ s $ in non-decreasing order (i. e. transform $ s $ so that $ s_1 \le s_2 \le \dots \le s_m $ , where $ m $ is the length of the string after applying all operations). An empty string is also considered sorted in non-decreasing order.

## 说明/提示

In the first example, you have to remove the $ 1 $ -st element, so the string becomes equal to 00.

In the second example, the string is already sorted.

In the third example, you have to swap the $ 2 $ -nd and the $ 3 $ -rd elements, so the string becomes equal to 0011.

In the fourth example, you have to swap the $ 3 $ -rd and the $ 4 $ -th elements, so the string becomes equal to 00011101, and then remove the $ 7 $ -th element, so the string becomes equal to 0001111.

In the fifth example, you have to remove the $ 1 $ -st element, so the string becomes equal to 001101, and then remove the $ 5 $ -th element, so the string becomes equal to 00111.

In the sixth example, the string is already sorted.

## 样例 #1

### 输入

```
6
100
0
0101
00101101
1001101
11111```

### 输出

```
1000000000001
0
1000000000000
2000000000001
2000000000002
0```

# AI分析结果

### 中文题目重写
# 二进制字符串排序

## 题目描述

给定一个仅由字符 `0` 和/或 `1` 组成的二进制字符串 $s$。

你可以对该字符串执行若干次操作（可能为零次）。操作有两种类型：

- 选择两个相邻的元素并交换它们。执行此操作需要支付 $10^{12}$ 个硬币；
- 选择字符串中的任意一个元素并将其删除。执行此操作需要支付 $10^{12}+1$ 个硬币。

你的任务是计算将字符串 $s$ 按非递减顺序排序所需的最小硬币数（即通过操作将 $s$ 转换为 $s_1 \le s_2 \le \dots \le s_m$，其中 $m$ 是应用所有操作后的字符串长度）。空字符串也被视为按非递减顺序排序。

## 说明/提示

在第一个样例中，你需要删除第一个元素，因此字符串变为 `00`。

在第二个样例中，字符串已经是有序的。

在第三个样例中，你需要交换第二个和第三个元素，因此字符串变为 `0011`。

在第四个样例中，你需要交换第三个和第四个元素，因此字符串变为 `00011101`，然后删除第七个元素，因此字符串变为 `0001111`。

在第五个样例中，你需要删除第一个元素，因此字符串变为 `001101`，然后删除第五个元素，因此字符串变为 `00111`。

在第六个样例中，字符串已经是有序的。

## 样例 #1

### 输入

```
6
100
0
0101
00101101
1001101
11111
```

### 输出

```
1000000000001
0
1000000000000
2000000000001
2000000000002
0
```

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是通过贪心策略，尽量减少操作次数，并在操作次数最少的情况下，尽可能使用交换操作。由于交换和删除的代价都很大，因此我们需要找到一种方式，使得在排序过程中，操作次数最少，并且尽可能使用代价较低的交换操作。

### 评分较高的题解
1. **作者：听取MLE声一片 (赞：8)**
   - **星级：4.5**
   - **关键亮点**：通过枚举交界处，分别计算左边和右边的删除代价，并在交界处进行交换操作优化。思路清晰，代码简洁。
   - **代码核心思想**：预处理前缀和后缀和，枚举交界处，计算最小代价。
   ```cpp
   for(int i=0;i<=n;i++)
       ans=min(ans,(a[i]+b[i+1])*Q);
   for(int i=1;i<=n;i++)
       if(str[i]=='1'&&str[i+1]=='0')
           ans=min(ans,P+(a[i-1]+b[i+2])*Q);
   ```

2. **作者：Esucu (赞：6)**
   - **星级：4**
   - **关键亮点**：使用动态规划的思路，定义状态表示处理到第 $i$ 位时的最小花费，状态转移清晰，代码易读。
   - **代码核心思想**：定义状态 $f_{i,0}$、$f_{i,1}$、$f_{i,2}$，分别表示处理到第 $i$ 位时末尾没有 $1$、只有一个 $1$、有多个 $1$ 的最小花费。
   ```cpp
   if(a[i]){
       f[i][0]=f[i-1][0]+q;	
       f[i][1]=f[i-1][0];
       f[i][2]=min(f[i-1][1],f[i-1][2]);
   }else{
       f[i][0]=f[i-1][0];
       f[i][1]=f[i-1][1]+p;
       f[i][2]=f[i-1][2]+q;	
   }
   ```

3. **作者：CuCl4Loliko (赞：4)**
   - **星级：4**
   - **关键亮点**：通过枚举断点，预处理左右 $0$ 和 $1$ 的数量，计算最小代价，并在断点处进行交换优化。思路清晰，代码简洁。
   - **代码核心思想**：预处理每个点左边 $1$ 的数量和右边 $0$ 的数量，枚举断点，计算最小代价。
   ```cpp
   for(int i=0;i<(int)s.size();i++)
       ans=min(ans,(a[i]+b[i+1])*base-(s[i]=='1'&&s[i+1]=='0'?base+1:0));
   ```

### 最优关键思路与技巧
1. **枚举交界处**：通过枚举 $0$ 和 $1$ 的交界处，分别计算左边和右边的删除代价，并在交界处进行交换操作优化。
2. **预处理前缀和后缀和**：预处理每个位置左边 $1$ 的数量和右边 $0$ 的数量，方便快速计算删除代价。
3. **动态规划**：通过定义状态表示处理到第 $i$ 位时的最小花费，状态转移清晰，适合处理复杂的操作序列。

### 可拓展之处
本题的思路可以拓展到其他类似的排序问题，特别是当操作代价较大时，如何通过贪心或动态规划来优化操作次数和代价。类似的问题包括：
- 通过交换和删除操作将字符串转换为特定模式。
- 在操作代价不同的情况下，如何选择最优的操作序列。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

### 个人心得摘录
- **作者：xujingyu**：在这题上挂得很惨，好累。说明在处理边界条件时需要特别小心，避免不必要的罚时。
- **作者：2018ljw**：多测不清空，罚时两行泪。强调了在多组测试数据中清空数组的重要性。

---
处理用时：49.31秒