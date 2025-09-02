# 题目信息

# Pyramid of Glasses

## 题目描述

Mary has just graduated from one well-known University and is now attending celebration party. Students like to dream of a beautiful life, so they used champagne glasses to construct a small pyramid. The height of the pyramid is $ n $ . The top level consists of only $ 1 $ glass, that stands on $ 2 $ glasses on the second level (counting from the top), then $ 3 $ glasses on the third level and so on.The bottom level consists of $ n $ glasses.

Vlad has seen in the movies many times how the champagne beautifully flows from top levels to bottom ones, filling all the glasses simultaneously. So he took a bottle and started to pour it in the glass located at the top of the pyramid.

Each second, Vlad pours to the top glass the amount of champagne equal to the size of exactly one glass. If the glass is already full, but there is some champagne flowing in it, then it pours over the edge of the glass and is equally distributed over two glasses standing under. If the overflowed glass is at the bottom level, then the champagne pours on the table. For the purpose of this problem we consider that champagne is distributed among pyramid glasses immediately. Vlad is interested in the number of completely full glasses if he stops pouring champagne in $ t $ seconds.

Pictures below illustrate the pyramid consisting of three levels.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF676B/ed339075e4609507dba05c150b7d4a59f8205147.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF676B/26451ba18b38a1279a26b3d7ab7f9bf63116bb12.png)

## 说明/提示

In the first sample, the glasses full after $ 5 $ seconds are: the top glass, both glasses on the second level and the middle glass at the bottom level. Left and right glasses of the bottom level will be half-empty.

## 样例 #1

### 输入

```
3 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 8
```

### 输出

```
6
```

# AI分析结果

### 题目内容
# 酒杯金字塔

## 题目描述
玛丽刚从一所知名大学毕业，现在正在参加庆祝派对。学生们喜欢憧憬美好的生活，所以他们用香槟杯搭建了一个小金字塔。金字塔的高度为 $n$ 。顶层只有 $1$ 个杯子，它放在第二层的 $2$ 个杯子上（从顶部开始数），接着第三层有 $3$ 个杯子，以此类推。底层由 $n$ 个杯子组成。

弗拉德在电影中多次看到香槟从顶层美妙地流到下层，同时填满所有杯子的场景。于是他拿了一瓶香槟，开始往金字塔顶部的杯子里倒酒。

每秒，弗拉德往顶层杯子倒入的香槟量正好等于一个杯子的容量。如果杯子已经满了，但仍有香槟流入，那么多余的香槟会从杯子边缘溢出，并平均分配到下面的两个杯子中。如果溢出的杯子在底层，那么香槟就会流到桌子上。为了解决这个问题，我们假设香槟会立即在金字塔的杯子中分配。弗拉德想知道如果他在 $t$ 秒后停止倒香槟，完全满的杯子有多少个。

下面的图片展示了一个三层的金字塔。
![图片1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF676B/ed339075e4609507dba05c150b7d4a59f8205147.png)
![图片2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF676B/26451ba18b38a1279a26b3d7ab7f9bf63116bb12.png)

## 说明/提示
在第一个样例中，$5$ 秒后满的杯子有：顶层的杯子、第二层的两个杯子以及底层中间的杯子。底层的左右两个杯子将是半满的。

## 样例 #1
### 输入
```
3 5
```
### 输出
```
4
```

## 样例 #2
### 输入
```
4 8
```
### 输出
```
6
```

### 算法分类
模拟

### 题解综合分析与结论
这些题解的核心思路都是基于模拟酒杯中香槟的倒入和流动过程。由于题目数据范围小（$n \leq 10$，$t \leq 10^4$），使得暴力模拟成为可行的方法。
 - **思路方面**：多数题解选择直接模拟香槟倒入和溢出的过程，部分题解先将 $t$ 秒的香槟一次性倒入顶层杯子，再模拟溢出分配；还有通过递归方式模拟每一步倒入和传递。
 - **算法要点**：用二维数组表示酒杯金字塔，根据香槟倒入和溢出规则更新每个酒杯中的香槟量，最后统计满杯数量。
 - **解决难点**：主要难点在于准确模拟香槟溢出后的分配过程，部分题解使用分数运算确保精度，避免小数运算带来的精度问题；还有通过“让酒浮空”等方式优化模拟过程，减少不必要计算。

### 通用建议与扩展思路
对于此类模拟题，关键在于清晰理解题目规则并准确实现。在数据范围允许时，暴力模拟是可行的策略，但也应思考优化方向。如本题可通过一次性倒入 $t$ 单位香槟减少时间复杂度中的 $t$ 因素。若数据范围增大，可考虑进一步优化，如使用滚动数组减少空间复杂度。同类型题通常围绕特定规则下的状态变化模拟，类似算法套路是仔细分析规则，用合适数据结构存储状态，按规则逐步更新状态。

### 推荐题目
 - [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)：通过模拟纸牌移动过程解决均分问题，与本题模拟状态变化思路类似。
 - [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)：模拟后缀表达式计算过程，涉及按特定规则处理数据，锻炼模拟能力。
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同购买方案模拟计算，选择最优方案，同样是基于规则的模拟。 

---
处理用时：38.00秒