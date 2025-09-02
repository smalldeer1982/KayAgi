# 题目信息

# Jzzhu and Chocolate

## 题目描述

Jzzhu has a big rectangular chocolate bar that consists of $ n×m $ unit squares. He wants to cut this bar exactly $ k $ times. Each cut must meet the following requirements:

- each cut should be straight (horizontal or vertical);
- each cut should go along edges of unit squares (it is prohibited to divide any unit chocolate square with cut);
- each cut should go inside the whole chocolate bar, and all cuts must be distinct.

The picture below shows a possible way to cut a $ 5×6 $ chocolate for $ 5 $ times.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF449A/f603977ae2da90c32a153ce408d6e4d1586349b7.png)Imagine Jzzhu have made $ k $ cuts and the big chocolate is splitted into several pieces. Consider the smallest (by area) piece of the chocolate, Jzzhu wants this piece to be as large as possible. What is the maximum possible area of smallest piece he can get with exactly $ k $ cuts? The area of a chocolate piece is the number of unit squares in it.

## 说明/提示

In the first sample, Jzzhu can cut the chocolate following the picture below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF449A/9c469c7998d7372246af19aeed82d0eba53211c4.png)In the second sample the optimal division looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF449A/4201d969cba3a3158e29e86ca8b9fbb2d41819d5.png)In the third sample, it's impossible to cut a $ 2×3 $ chocolate $ 4 $ times.

## 样例 #1

### 输入

```
3 4 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
6 4 2
```

### 输出

```
8
```

## 样例 #3

### 输入

```
2 3 4
```

### 输出

```
-1
```

# AI分析结果



### 中文题目重写

# Jzzhu和巧克力

## 题目描述

Jzzhu有一块由$n×m$个单位正方形组成的大长方形巧克力。他想要恰好切$k$次，每次切割必须满足以下要求：

- 每刀必须是直线（水平或垂直）；
- 每刀必须沿单位正方形的边缘切割（禁止切割任何单位正方形内部）；
- 每刀必须完全贯穿整块巧克力，且所有切割线不能重复。

想象Jzzhu完成$k$次切割后，巧克力被分成若干块。考虑所有巧克力块中面积最小的那一块，Jzzhu希望这个最小值尽可能大。求在恰好切$k$刀的情况下，最小块的最大可能面积是多少？若无法完成切割，输出-1。

## 样例

### 输入1
```
3 4 1
```
### 输出1
```
6
```

### 输入2
```
6 4 2
```
### 输出2
```
8
```

### 输入3
```
2 3 4
```
### 输出3
```
-1
```

---

### 算法分类
**贪心、数学**

---

### 题解分析与结论

各题解核心思路对比：
1. **数论分块法**：通过枚举横向切割的块数，利用整除分块优化遍历次数（$\sqrt{n}$级别），计算纵向切割的块数，取面积最大值。
2. **分类讨论法**：根据$k$与$n-1$、$m-1$的大小关系分四种情况处理，优先全切一个方向，剩余刀数切另一方向。
3. **贪心构造法**：证明最优解产生于全切横向或全切纵向，或先切满一个方向再切另一个方向的情况。

共同难点在于如何高效寻找最优切割分配，确保计算的正确性及边界处理。

---

### 推荐题解（评分≥4星）

#### 1. ZLCT（数论解法） ⭐⭐⭐⭐⭐
**关键亮点**：
- 数学推导严谨，覆盖所有切割情况
- 代码简洁高效，利用分类判断避免无效切割
- 处理边界条件完善（如`k-n+2>0`的检查）

**核心代码**：
```cpp
if(k < n) ans = max(ans, (n/(k+1))*m);
if(k < m) ans = max(ans, (m/(k+1))*n);
if(k-n+2 > 0) ans = max(ans, m/(k-n+2));
if(k-m+2 > 0) ans = max(ans, n/(k-m+2));
```

#### 2. 是个汉子（数论分块） ⭐⭐⭐⭐
**关键亮点**：
- 利用数论分块优化遍历次数
- 代码逻辑清晰，通过分块计算横向切割的候选值
- 时间复杂度优化到$O(\sqrt{n})$

**核心代码**：
```cpp
ll calc(ll n, ll m, ll k) {
    ll ans = 1;
    for (int i=1, pre=0; i<=n; i=pre+1) {
        pre = n / (n/i);
        if (pre > k+1) {
            ans = max(ans, n/(k+1)*m);
            break;
        }
        ans = max(ans, (n/pre) * (m/(k-pre+2)));
    }
    return ans;
}
```

---

### 最优关键思路
优先在一个方向切最多刀（全切横向或纵向），剩余刀数切另一方向，取所有可能切割方式中的最大值。通过数学推导证明最优解的分布特性，避免无效枚举。

---

### 拓展与心得
- **同类型题**：类似的最优化切割问题常结合贪心与数学分析，如洛谷P1577（木棍切割）
- **调试心得**：需特别注意切割次数与块数的转换关系（刀数+1=块数），以及分母非正的边界检查。

---

### 推荐相似题目
1. P1577 切绳子（二分答案）
2. P2249 木材加工（贪心+二分）
3. P4343 [SHOI2015]自动刷题机（边界条件处理）

---
处理用时：107.14秒