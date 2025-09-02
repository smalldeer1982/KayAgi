# 题目信息

# Vasily the Bear and Sequence

## 题目描述

Vasily the bear has got a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Vasily the Bear wants to write out several numbers on a piece of paper so that the beauty of the numbers he wrote out was maximum.

The beauty of the written out numbers $ b_{1},b_{2},...,b_{k} $ is such maximum non-negative integer $ v $ , that number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by number $ 2^{v} $ without a remainder. If such number $ v $ doesn't exist (that is, for any non-negative integer $ v $ , number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by $ 2^{v} $ without a remainder), the beauty of the written out numbers equals -1.

Tell the bear which numbers he should write out so that the beauty of the written out numbers is maximum. If there are multiple ways to write out the numbers, you need to choose the one where the bear writes out as many numbers as possible.

Here expression $ x $ $ and $ $ y $ means applying the bitwise AND operation to numbers $ x $ and $ y $ . In programming languages C++ and Java this operation is represented by "&", in Pascal — by "and".

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
2
4 5
```

## 样例 #2

### 输入

```
3
1 2 4
```

### 输出

```
1
4
```

# AI分析结果

### 题目中文重写
# 熊瓦西里与序列

## 题目描述
熊瓦西里得到了一个正整数序列 $ a_{1},a_{2},\cdots,a_{n} $ 。熊瓦西里想在一张纸上写出几个数，使得他写出的数的“美丽值”最大。

写出的数 $ b_{1},b_{2},\cdots,b_{k} $ 的“美丽值”是一个最大的非负整数 $ v $ ，使得 $ b_{1} \text{ and } b_{2} \text{ and } \cdots \text{ and } b_{k} $ 能被 $ 2^{v} $ 整除且没有余数。如果这样的数 $ v $ 不存在（即对于任何非负整数 $ v $ ，$ b_{1} \text{ and } b_{2} \text{ and } \cdots \text{ and } b_{k} $ 都能被 $ 2^{v} $ 整除且没有余数），那么写出的数的“美丽值”等于 -1。

告诉这只熊他应该写出哪些数，使得写出的数的“美丽值”最大。如果有多种写出数字的方法，你需要选择熊写出数字最多的那种方法。

这里的表达式 $ x \text{ and } y $ 表示对数字 $ x $ 和 $ y $ 进行按位与运算。在 C++ 和 Java 编程语言中，此运算用“&”表示，在 Pascal 中用“and”表示。

## 样例 #1
### 输入
```
5
1 2 3 4 5
```
### 输出
```
2
4 5
```

## 样例 #2
### 输入
```
3
1 2 4
```
### 输出
```
1
4
```

### 综合分析与结论
这两个题解思路基本一致，都是采用倒序枚举 $v$ 的贪心策略。通过从大到小枚举 $v$，找到满足条件的最大 $v$ 以及对应的方案。

### 题解对比
| 作者 | 思路要点 | 算法要点 | 解决难点 | 评分 |
| --- | --- | --- | --- | --- |
| Graphcity | 倒序枚举 $v$，找满足 $a_i \ \text{and} \ 2^v$ 为真的数，且第 0 位到第 $v - 1$ 位为 0，全部选入 | 用 `vector` 记录方案，通过位运算判断和筛选 | 如何确定满足整除条件的最大 $v$ 及对应方案 | 4星 |
| Rye_Catcher | 倒序枚举 $k$，贪心选取二进制第 $k$ 位为 1 的数，让除第 $k$ 位外都为 0 | 用数组 `q` 记录方案，通过位运算判断和筛选 | 如何确定满足整除条件的最大 $k$ 及对应方案 | 3星 |

### 所选题解
- **Graphcity（4星）**
  - **关键亮点**：思路清晰，代码可读性高，使用 `vector` 记录方案，方便操作。

### 重点代码
```cpp
// Graphcity 题解核心代码
for(register int i=30;i>=0;--i)
{
    int now=0,res=0; // now:数的个数 res:运算后的值
    v.clear();
    for(register int j=1;j<=n;++j)
        if(a[j]&(1<<i)) // 选取数
        {
            now++,res&=a[j],v.push_back(a[j]);
            if(now==1) res=a[j];
        }
    if(res%(1<<i)==0 && now) // 判断是否合法
    {
        printf("%d\n",now);
        for(auto i:v) printf("%d ",i);
        return 0;
    }
}
printf("-1");
```
**核心实现思想**：倒序枚举 $v$，对于每个 $v$，遍历数组找到二进制第 $v$ 位为 1 的数，将其加入 `vector` 中并进行按位与运算，最后判断运算结果是否能被 $2^v$ 整除，若能则输出方案并结束程序，若都不满足则输出 -1。

### 最优关键思路或技巧
- 采用倒序枚举的贪心策略，从大到小枚举 $v$，可以保证找到的 $v$ 是最大的。
- 利用位运算判断数字的二进制位，高效筛选出满足条件的数字。

### 可拓展之处
同类型题或类似算法套路：涉及位运算和贪心策略的题目，例如求最大按位或、按位异或结果等，都可以考虑从二进制位的角度进行分析，结合贪心思想求解。

### 推荐洛谷题目
1. P1886 滑动窗口 /【模板】单调队列
2. P1090 [NOIP2004 提高组] 合并果子 / [USACO06NOV] Fence Repair G
3. P2123 皇后游戏

### 个人心得
两个题解均未包含个人心得。

---
处理用时：33.39秒