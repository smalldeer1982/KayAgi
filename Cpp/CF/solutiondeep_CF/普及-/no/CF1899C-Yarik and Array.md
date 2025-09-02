# 题目信息

# Yarik and Array

## 题目描述

A subarray is a continuous part of array.

Yarik recently found an array $ a $ of $ n $ elements and became very interested in finding the maximum sum of a non empty subarray. However, Yarik doesn't like consecutive integers with the same parity, so the subarray he chooses must have alternating parities for adjacent elements.

For example, $ [1, 2, 3] $ is acceptable, but $ [1, 2, 4] $ is not, as $ 2 $ and $ 4 $ are both even and adjacent.

You need to help Yarik by finding the maximum sum of such a subarray.

## 样例 #1

### 输入

```
7
5
1 2 3 4 5
4
9 9 8 8
6
-1 4 -1 0 5 -4
4
-1 2 4 -3
1
-1000
3
101 -99 101
20
-10 5 -8 10 6 -10 7 9 -2 -6 7 2 -4 6 -1 7 -6 -7 4 1```

### 输出

```
15
17
8
4
-1000
101
10```

# AI分析结果

### 题目翻译
子数组是数组的连续部分。

亚里克（Yarik）最近发现了一个包含 $n$ 个元素的数组 $a$，并对找出非空子数组的最大和非常感兴趣。然而，亚里克不喜欢相邻的连续整数具有相同的奇偶性，因此他选择的子数组中相邻元素的奇偶性必须交替出现。

例如，$[1, 2, 3]$ 是可以接受的，但 $[1, 2, 4]$ 不行，因为 $2$ 和 $4$ 都是偶数且相邻。

你需要帮助亚里克找出这样的子数组的最大和。

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕如何找出满足相邻元素奇偶性交替的子数组的最大和展开。多数题解采用动态规划的思想，通过状态转移方程来更新当前位置结尾的子数组的最大和，实时更新全局最大和。不同题解在处理奇偶性判断、状态转移细节上略有差异，但核心思路一致。

### 所选题解
- **wmrqwq（5星）**
    - **关键亮点**：思路清晰，对序列中全为负数和有正数的情况进行分类讨论，代码可读性高。
- **lailai0916（4星）**
    - **关键亮点**：通过分类讨论相邻元素能否接上，简洁地实现了状态转移。
- **FireRain（4星）**
    - **关键亮点**：明确定义 $dp$ 数组表示以 $i$ 结尾的子串的最大和，逻辑清晰。

### 重点代码
#### wmrqwq
```cpp
for(int i=1;i<=n;i++)
{
    if(sum==0)
    {
        if(a[i]>0)
            sum=a[i];
    }
    else
    {
        if((abs(a[i-1])%2+abs(a[i])%2)==1)
            sum+=a[i];
        else
        {
            if(a[i]>0)
                sum=a[i];
            else
                sum=0;
        }
    }
    sum=max(sum,a[i]);
    ans=max(ans,sum);
}
```
**核心实现思想**：先处理序列中全为负数的情况，直接取最大值。对于有正数的情况，从前往后遍历数组，根据当前和是否为 $0$ 以及相邻元素的奇偶性来更新当前和，同时更新全局最大和。

#### lailai0916
```cpp
for(int i=2;i<=n;i++)
{
    if(a[i]-a[i-1]&1)
    {
        sum=max(sum+a[i],a[i]);
    }
    else
    {
        sum=a[i];
    }
    ans=max(ans,sum);
}
```
**核心实现思想**：从第二个元素开始遍历数组，根据相邻元素的奇偶性判断能否接上，若能接上则取接或不接的最大值，否则直接以当前元素作为新的和，实时更新全局最大和。

#### FireRain
```cpp
for (re int i = 2;i <= n;i++){
    if (abs(arr[i] & 1) != abs(arr[i - 1] & 1)) dp[i] = max(dp[i],max(dp[i - 1],0ll) + arr[i]);
}
for (re int i = 1;i <= n;i++) ans = max(ans,dp[i]);
```
**核心实现思想**：定义 $dp$ 数组表示以 $i$ 结尾的子串的最大和，根据相邻元素的奇偶性更新 $dp$ 数组，最后取 $dp$ 数组中的最大值作为答案。

### 最优关键思路或技巧
- 采用动态规划的思想，定义合适的状态表示，如以当前位置结尾的子数组的最大和。
- 处理相邻元素奇偶性时，通过取模或位运算判断。
- 实时更新全局最大和，避免重复计算。

### 拓展思路
同类型题可以是在其他条件限制下求子数组的最大和，如相邻元素差值满足一定条件等。类似算法套路都是通过动态规划，根据条件进行状态转移。

### 推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [P2679 [NOIP2015 提高组] 子串](https://www.luogu.com.cn/problem/P2679)
- [P1714 切蛋糕](https://www.luogu.com.cn/problem/P1714)

### 个人心得
_没有题解包含个人心得内容_ 

---
处理用时：27.74秒