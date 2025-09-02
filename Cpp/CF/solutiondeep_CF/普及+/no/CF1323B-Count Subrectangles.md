# 题目信息

# Count Subrectangles

## 题目描述

You are given an array $ a $ of length $ n $ and array $ b $ of length $ m $ both consisting of only integers $ 0 $ and $ 1 $ . Consider a matrix $ c $ of size $ n \times m $ formed by following rule: $ c_{i, j} = a_i \cdot b_j $ (i.e. $ a_i $ multiplied by $ b_j $ ). It's easy to see that $ c $ consists of only zeroes and ones too.

How many subrectangles of size (area) $ k $ consisting only of ones are there in $ c $ ?

A subrectangle is an intersection of a consecutive (subsequent) segment of rows and a consecutive (subsequent) segment of columns. I.e. consider four integers $ x_1, x_2, y_1, y_2 $ ( $ 1 \le x_1 \le x_2 \le n $ , $ 1 \le y_1 \le y_2 \le m $ ) a subrectangle $ c[x_1 \dots x_2][y_1 \dots y_2] $ is an intersection of the rows $ x_1, x_1+1, x_1+2, \dots, x_2 $ and the columns $ y_1, y_1+1, y_1+2, \dots, y_2 $ .

The size (area) of a subrectangle is the total number of cells in it.

## 说明/提示

In first example matrix $ c $ is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1323B/e15101752e569619838a0f9859eb0706f1619714.png)There are $ 4 $ subrectangles of size $ 2 $ consisting of only ones in it:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1323B/980c0eb5f8be8a323efa10a6215da0fcea6f84eb.png)In second example matrix $ c $ is:

 ![](https://espresso.codeforces.com/3109dd0bc266b26bdd9a8a0f1f6c5f6f8cd64093.png)

## 样例 #1

### 输入

```
3 3 2
1 0 1
1 1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
3 5 4
1 1 1
1 1 1 1 1```

### 输出

```
14```

# AI分析结果

### 题目翻译
# 统计子矩形

## 题目描述
给定一个长度为 $n$ 的数组 $a$ 和一个长度为 $m$ 的数组 $b$，两个数组都仅由整数 $0$ 和 $1$ 组成。考虑一个大小为 $n \times m$ 的矩阵 $c$，其构造规则如下：$c_{i, j} = a_i \cdot b_j$（即 $a_i$ 乘以 $b_j$）。显然，矩阵 $c$ 也仅由 $0$ 和 $1$ 组成。

矩阵 $c$ 中，面积为 $k$ 且仅由 $1$ 组成的子矩形有多少个？

子矩形是连续行段和连续列段的交集。即，考虑四个整数 $x_1, x_2, y_1, y_2$（$1 \le x_1 \le x_2 \le n$，$1 \le y_1 \le y_2 \le m$），子矩形 $c[x_1 \dots x_2][y_1 \dots y_2]$ 是行 $x_1, x_1 + 1, x_1 + 2, \dots, x_2$ 和列 $y_1, y_1 + 1, y_1 + 2, \dots, y_2$ 的交集。

子矩形的面积是其中单元格的总数。

## 说明/提示
在第一个样例中，矩阵 $c$ 如下：
![图片1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1323B/e15101752e569619838a0f9859eb0706f1619714.png)
其中有 $4$ 个面积为 $2$ 且仅由 $1$ 组成的子矩形：
![图片2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1323B/980c0eb5f8be8a323efa10a6215da0fcea6f84eb.png)
在第二个样例中，矩阵 $c$ 如下：
![图片3](https://espresso.codeforces.com/3109dd0bc266b26bdd9a8a0f1f6c5f6f8cd64093.png)

## 样例 #1
### 输入
```
3 3 2
1 0 1
1 1 1
```
### 输出
```
4
```

## 样例 #2
### 输入
```
3 5 4
1 1 1
1 1 1 1 1
```
### 输出
```
14
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是将问题转化为分别统计数组 $a$ 和数组 $b$ 中连续 $1$ 的区间长度，然后通过枚举满足 $x \times y = k$ 的 $x$ 和 $y$，计算相应的子矩形数量。不同题解的差异主要体现在具体的实现方式和优化技巧上。
- **思路对比**：多数题解都采用了先统计连续 $1$ 的区间长度，再枚举因数的思路。部分题解使用了二分查找、树状数组等数据结构来优化查找过程。
- **算法要点**：关键在于准确统计数组中连续 $1$ 的区间长度，并合理枚举因数，计算满足条件的子矩形数量。
- **解决难点**：处理连续 $1$ 的区间长度统计，避免重复计算，以及优化枚举过程以减少时间复杂度。

### 所选题解
- **作者：yunsenl (4星)**
  - **关键亮点**：思路清晰，使用二分查找优化查找过程，代码结构较为规范。
  - **个人心得**：无
- **作者：TEoS (4星)**
  - **关键亮点**：在统计列的情况时，利用递推关系从 $z - 1$ 的情况拓展而来，减少了重复计算。
  - **个人心得**：无
- **作者：流绪 (4星)**
  - **关键亮点**：详细解释了子段细分的原理，通过预处理记录子段能分的更小段种数，优化了计算过程。
  - **个人心得**：无

### 重点代码
#### yunsenl 的题解
```cpp
inline LL search(LL x) {
    int left = 1, right = m, ret = 0;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (s[mid].pre >= x) ret = mid, right = mid - 1;
        else left = mid + 1;
    }
    return ret ? (m - ret + 1) : 0;
}
```
**核心实现思想**：二分查找第一个满足条件的 $y$，返回 $b$ 序列中长度大于等于 $y$ 的区间个数。

#### TEoS 的题解
```cpp
for(int i=1;i<=m;i++)
{
    scanf("%d",&b[i]);
    if(b[i])
    {
        ans+=now;
        if(k%(ll)(i-la)==0 && k/(ll)(i-la)<=n)
            ans+=cnt[k/(ll)(i-la)],now+=cnt[k/(ll)(i-la)];
    }
    else
        la=i,now=0;
}
```
**核心实现思想**：在统计列的情况时，利用递推关系从 $z - 1$ 的情况拓展而来，同时统计答案。

#### 流绪的题解
```cpp
for(int i=1;i<=n;i++)
{
    cin >> a[i];
    if(a[i])
        cnt++;
    else
    {
        for(int j=1;j<=k&&j<=cnt;j++)
            sum[j]+=cnt-j+1;
        cnt=0;
    }
}
for(int i=1;i<=cnt&&i<=k;i++)
    sum[i]+=cnt-i+1;
```
**核心实现思想**：预处理 $a$ 数组连续的一段长度，记录其能分的更小段种数。

### 最优关键思路或技巧
- 利用因数枚举，减少不必要的计算。
- 预处理连续 $1$ 的区间长度，避免重复统计。
- 部分题解使用二分查找、树状数组等数据结构优化查找过程。

### 可拓展之处
同类型题或类似算法套路：
- 统计矩阵中满足特定条件的子矩阵数量，如子矩阵的和、子矩阵的最大元素等。
- 处理二维数组中连续元素的问题，如连续相同元素的最大长度、连续递增元素的个数等。

### 推荐题目
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)
- [P2701 巨大的牛棚](https://www.luogu.com.cn/problem/P2701)
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)

---
处理用时：49.11秒