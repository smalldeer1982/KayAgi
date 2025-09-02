# 题目信息

# [USACO06JAN] Corral the Cows G

## 题目描述

Farmer John wishes to build a corral for his cows. Being finicky beasts, they demand that the corral be square and that the corral contain at least C (1 <= C <= 500) clover fields for afternoon treats. The corral's edges must be parallel to the X,Y axes.


FJ's land contains a total of N (C <= N <= 500) clover fields, each a block of size 1 x 1 and located at with its lower left corner at integer X and Y coordinates each in the range 1..10,000. Sometimes more than one clover field grows at the same location; such a field would have its location appear twice (or more) in the input. A corral surrounds a clover field if the field is entirely located inside the corral's borders.


Help FJ by telling him the side length of the smallest square containing C clover fields.

Farmer John 希望为他的奶牛们建立一个畜栏。

这些挑剔的奶牛要求畜栏必须是正方形的，而且至少要包含 $C$ 片三叶草，来当做它们的下午茶。

约翰的土地里一共包含 $N$ 片三叶草，每单位三叶草位于一个 $1\times 1$ 的土地区域内。坐标都为整数，范围在 $1$ 到 $10000$ 以内。

**多片的三叶草可能会位于同一个 $1\times 1$ 的区域内，所以在输入内，同一个区域坐标可能出现多次。**

请你帮 Farmer John 计算一下，在能包含至少 $C$ 片三叶草的情况下，畜栏的最小边长是多少。

$1\le C\le N\le 500$。

## 说明/提示

Explanation of the sample:



```php
|*   *
| * *
+------
```

Below is one 4x4 solution (C's show most of the corral's area); many others exist.

```php
|CCCC
|CCCC
|*CCC*
|C*C*
+------
```

## 样例 #1

### 输入

```
3 4
1 2
2 1
4 1
5 2```

### 输出

```
4```

# AI分析结果



### 综合分析与结论
本题核心思路为二分答案结合离散化与二维前缀和优化判定过程。所有题解均围绕如何高效判断边长合法性展开，关键难点在于处理坐标范围过大问题。离散化将坐标映射到有限空间，结合双指针或前缀和快速统计区域内点数，是主流解法。

---

### 精选题解分析

#### 1. RyexAwl（★★★★★）
**关键亮点**  
- 离散化坐标+二维前缀和预处理，将时间复杂度优化至可接受范围  
- 双指针滑动窗口维护合法区域，避免暴力枚举所有可能性  
- 代码结构清晰，变量命名规范，离散化与二分逻辑分离易理解  
**核心代码片段**  
```cpp
bool check(int len){
    for (int x1 = 0,x2 = 1; x2 < numbers.size(); x2++){
        while(numbers[x2] - numbers[x1 + 1] + 1 > len)x1++;
        for (int y1 = 0, y2 = 1; y2 < numbers.size(); y2++){
            while(numbers[y2] - numbers[y1 + 1] + 1 > len)y1++;
            if (sum[x2][y2] - sum[x1][y2] - sum[x2][y1] + sum[x1][y1] >= c) return true;
        }
    }
    return false;
}
```
**实现思想**  
离散化后维护x轴和y轴的双指针，计算当前窗口内的三叶草数量。利用前缀和的差分特性快速计算区域和。

#### 2. zhzh2001（★★★★☆）
**关键亮点**  
- 扫描线+线段树巧妙转化为一维区间覆盖问题  
- 时间复杂度优化至O(N log²N)，适合更大数据规模  
- 事件驱动思想值得借鉴  
**核心思想**  
将每个草场视为两个事件（起始和结束），按x排序后扫描，线段树维护y轴覆盖次数。当覆盖最大值≥C时说明存在合法正方形。

#### 3. qinyiyang2012（★★★★☆）
**关键亮点**  
- 双轴离散化+二维前缀和实现简洁  
- 对离散化后的坐标范围进行严格数学推导  
- 代码中巧用lower_bound处理坐标映射  
**个人心得**  
作者强调离散化后坐标的数学关系需精确处理，例如`numbers[x2]-numbers[x1+1]+1 > len`的判断，避免边界遗漏。

---

### 关键技巧总结
1. **离散化压缩空间**：将稀疏坐标映射为密集索引，二维前缀和数组大小从10^8降至500²  
2. **二分答案框架**：将最优化问题转化为判定问题，时间复杂度从O(N^3)降至O(N² logN)  
3. **双指针维护窗口**：在离散化后的坐标轴上滑动，避免重复计算区域和  
4. **事件驱动思维**：将二维问题转化为一维扫描线，结合线段树动态维护极值  

---

### 推荐相似题目
1. [P2218 [HAOI2007] 覆盖问题](https://www.luogu.com.cn/problem/P2218) - 二分答案+几何覆盖判断  
2. [P2285 [HNOI2004] 打鼹鼠](https://www.luogu.com.cn/problem/P2285) - 二维坐标离散化+动态规划  
3. [P3745 [六省联考2017] 期末考试](https://www.luogu.com.cn/problem/P3745) - 二分答案结合贪心策略

---
处理用时：59.51秒