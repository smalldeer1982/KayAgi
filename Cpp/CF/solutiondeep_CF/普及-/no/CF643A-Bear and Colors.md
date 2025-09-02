# 题目信息

# Bear and Colors

## 题目描述

Bear Limak has $ n $ colored balls, arranged in one long row. Balls are numbered $ 1 $ through $ n $ , from left to right. There are $ n $ possible colors, also numbered $ 1 $ through $ n $ . The $ i $ -th ball has color $ t_{i} $ .

For a fixed interval (set of consecutive elements) of balls we can define a dominant color. It's a color occurring the biggest number of times in the interval. In case of a tie between some colors, the one with the smallest number (index) is chosen as dominant.

There are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643A/e72cbeaa17cceea137ec85134680a8c41a08d995.png) non-empty intervals in total. For each color, your task is to count the number of intervals in which this color is dominant.

## 说明/提示

In the first sample, color $ 2 $ is dominant in three intervals:

- An interval $ [2,2] $ contains one ball. This ball's color is $ 2 $ so it's clearly a dominant color.
- An interval $ [4,4] $ contains one ball, with color $ 2 $ again.
- An interval $ [2,4] $ contains two balls of color $ 2 $ and one ball of color $ 1 $ .

There are $ 7 $ more intervals and color $ 1 $ is dominant in all of them.

## 样例 #1

### 输入

```
4
1 2 1 2
```

### 输出

```
7 3 0 0 
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
6 0 0 
```

# AI分析结果

【题目翻译】
# 熊与颜色

## 题目描述
熊利马克（Bear Limak）有 $n$ 个彩色球，排成一长排。球从左到右依次编号为 $1$ 到 $n$。共有 $n$ 种可能的颜色，也从 $1$ 到 $n$ 编号。第 $i$ 个球的颜色为 $t_{i}$。

对于一组连续的球（区间），我们可以定义一种“主导颜色”。主导颜色是在该区间中出现次数最多的颜色。如果有多种颜色出现次数相同，则选择编号最小的颜色作为主导颜色。

总共有 $\frac{n(n + 1)}{2}$ 个非空区间。对于每种颜色，你的任务是统计该颜色作为主导颜色的区间数量。

## 说明/提示
在第一个样例中，颜色 $2$ 在三个区间中是主导颜色：
- 区间 $[2,2]$ 包含一个球。这个球的颜色是 $2$，所以显然它是主导颜色。
- 区间 $[4,4]$ 包含一个球，颜色同样是 $2$。
- 区间 $[2,4]$ 包含两个颜色为 $2$ 的球和一个颜色为 $1$ 的球。

还有 $7$ 个区间，颜色 $1$ 在所有这些区间中都是主导颜色。

## 样例 #1
### 输入
```
4
1 2 1 2
```
### 输出
```
7 3 0 0 
```

## 样例 #2
### 输入
```
3
1 1 1
```
### 输出
```
6 0 0 
```

【算法分类】
枚举

【综合分析与结论】
这些题解的核心思路都是通过枚举所有可能的区间，统计每个区间内各种颜色的出现次数，进而确定每个区间的主导颜色，最后累加每种颜色作为主导颜色的区间数量。

### 思路对比
- 多数题解采用两层循环枚举区间的左右端点，在枚举过程中动态更新每种颜色的出现次数和当前区间的主导颜色。
- 部分题解从左端点开始向右扩展区间，部分题解从右端点开始向左扩展区间，但本质相同。

### 算法要点
- 使用数组记录每种颜色的出现次数。
- 在每次扩展区间时，根据新加入的球的颜色更新出现次数，并判断是否需要更新主导颜色。

### 解决难点
- 处理颜色出现次数相同的情况，确保选择编号最小的颜色作为主导颜色。
- 每次枚举新区间前，需要将记录颜色出现次数的数组清零。

### 评分
- OMITW：3星。思路清晰，代码简洁，但注释较少。
- lizulong：3星。思路明确，有一定注释，使用 `ios::sync_with_stdio` 优化输入输出。
- Zouzhuoxuan：3星。详细分析了暴力做法和优化思路，代码规范。
- happy_zero：3星。思路简洁，代码易懂。
- wind_whisper：3星。有自定义输入函数，代码结构较清晰。
- yangzd：3星。思路正确，注释较详细。
- N_z_：3星。思路清晰，代码简洁。

由于所有题解均不足4星，以下给出通用建议与扩展思路：
### 通用建议
- 增加代码注释，提高代码可读性，方便他人理解。
- 对于输入输出的优化，可以根据实际情况选择合适的方式，如 `ios::sync_with_stdio` 或自定义输入函数。
### 扩展思路
- 当数据范围增大时，$O(n^2)$ 的算法可能会超时，可以考虑更高效的算法，如分治算法。
- 可以尝试将问题扩展到多维空间，例如二维平面上的区域主导颜色问题。

【推荐题目】
1. P1036 选数：https://www.luogu.com.cn/problem/P1036
2. P1157 组合的输出：https://www.luogu.com.cn/problem/P1157
3. P1706 全排列问题：https://www.luogu.com.cn/problem/P1706

【个人心得】
题解中均未包含个人心得。 

---
处理用时：24.30秒