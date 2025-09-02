# 题目信息

# Histogram Ugliness

## 题目描述

Little Dormi received a histogram with $ n $ bars of height $ a_1, a_2, \ldots, a_n $ for Christmas. However, the more he played with his new histogram, the more he realized its imperfections, so today he wanted to modify it to his liking.

To modify the histogram, Little Dormi is able to perform the following operation an arbitrary number of times:

- Select an index $ i $ ( $ 1 \le i \le n $ ) where $ a_i>0 $ , and assign $ a_i := a_i-1 $ .

Little Dormi defines the ugliness score of his histogram (after performing some number of operations) as the sum of the vertical length of its outline and the number of operations he performed on it. And to make the histogram as perfect as possible, he would like to minimize the ugliness score after modifying it with some number of operations.

However, as his histogram is very large, Little Dormi is having trouble minimizing the ugliness score, so as Little Dormi's older brother, help him find the minimal ugliness.

Consider the following example where the histogram has $ 4 $ columns of heights $ 4,8,9,6 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534B/5d4fda0f26b85e9fedc3c103ba4d223f004efdcd.png)The blue region represents the histogram, and the red lines represent the vertical portion of the outline. Currently, the vertical length of the outline is $ 4+4+1+3+6 = 18 $ , so if Little Dormi does not modify the histogram at all, the ugliness would be $ 18 $ .

However, Little Dormi can apply the operation once on column $ 2 $ and twice on column $ 3 $ , resulting in a histogram with heights $ 4,7,7,6 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534B/a49f3980f3c9ed62a810c32f51757eb225af4b4f.png)Now, as the total vertical length of the outline (red lines) is $ 4+3+1+6=14 $ , the ugliness is $ 14+3=17 $ dollars. It can be proven that this is optimal.

## 说明/提示

Example $ 1 $ is the example described in the statement.

The initial histogram for example $ 2 $ is given below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534B/a6df0f8291f71b8395f619c7fb85ca44f7963294.png)The ugliness is currently $ 2+1+6+3+4=16 $ .

By applying the operation once on column $ 1 $ , six times on column $ 3 $ , and three times on column $ 4 $ , we can end up with a histogram with heights $ 1,1,1,1,0,0 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534B/2079ec37e337586787093a1ba717d5a002aae17f.png)The vertical length of the outline is now $ 1+1=2 $ and Little Dormi made $ 1+6+3=10 $ operations, so the final ugliness is $ 2+10=12 $ , which can be proven to be optimal.

## 样例 #1

### 输入

```
2
4
4 8 9 6
6
2 1 7 4 0 0```

### 输出

```
17
12```

# AI分析结果

### 题目内容翻译

# 直方图的丑陋度

## 题目描述

小Dormi收到了一个由$n$个高度为$a_1, a_2, \ldots, a_n$的柱子组成的直方图作为圣诞礼物。然而，他越玩这个直方图，就越觉得它不完美，所以他决定对它进行修改。

为了修改直方图，小Dormi可以进行以下操作任意次：

- 选择一个索引$i$（$1 \le i \le n$），其中$a_i>0$，并将$a_i := a_i-1$。

小Dormi定义直方图的丑陋度（在进行一些操作后）为其轮廓的垂直长度之和加上他进行的操作次数。为了使直方图尽可能完美，他希望在进行一些操作后，直方图的丑陋度最小。

然而，由于直方图非常大，小Dormi难以最小化丑陋度，所以作为他的哥哥，请你帮助他找到最小的丑陋度。

## 说明/提示

示例$1$是题目描述中的例子。

示例$2$的初始直方图如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534B/a6df0f8291f71b8395f619c7fb85ca44f7963294.png)

当前丑陋度为$2+1+6+3+4=16$。

通过在列$1$上操作一次，列$3$上操作六次，列$4$上操作三次，我们可以得到一个高度为$1,1,1,1,0,0$的直方图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534B/2079ec37e337586787093a1ba717d5a002aae17f.png)

现在轮廓的垂直长度为$1+1=2$，小Dormi进行了$1+6+3=10$次操作，因此最终丑陋度为$2+10=12$，这可以证明是最优的。

## 样例 #1

### 输入

```
2
4
4 8 9 6
6
2 1 7 4 0 0
```

### 输出

```
17
12
```

### 算法分类
贪心

### 题解分析与结论

这道题的核心思想是通过贪心策略来最小化直方图的丑陋度。题解们普遍采用了以下思路：

1. **初始丑陋度计算**：首先计算直方图的初始丑陋度，即所有相邻柱子高度差的绝对值之和，再加上最后一根柱子的高度。
2. **贪心操作**：对于每一根柱子，如果它比左右两边的柱子都高，则将其高度降低到左右两边柱子的最大值，这样可以减少丑陋度。
3. **最终答案**：将初始丑陋度减去通过贪心操作减少的丑陋度，得到最终的最小丑陋度。

### 高星题解推荐

#### 题解1：作者：_xbn (赞：3)
- **星级**：5星
- **关键亮点**：代码简洁，思路清晰，直接通过贪心策略减少丑陋度。
- **核心代码**：
```cpp
for(int i = 1; i <= n; i++) {
    if(a[i - 1] < a[i] && a[i + 1] < a[i]) {
        t = max(a[i - 1], a[i + 1]);
        ans -= a[i] - t;
        a[i] = t;
    }
}
```
- **个人心得**：作者通过简单的贪心策略，快速减少了丑陋度，代码实现非常直观。

#### 题解2：作者：BotDand (赞：2)
- **星级**：4星
- **关键亮点**：详细解释了贪心策略的合理性，代码实现清晰。
- **核心代码**：
```cpp
for(int i = 1; i <= n; ++i) {
    x = max(a[i - 1], a[i + 1]);
    if(a[i] > x) ans -= (a[i] - x);
}
```
- **个人心得**：作者通过详细的分析，证明了贪心策略的正确性，代码实现也非常简洁。

#### 题解3：作者：HerikoDeltana (赞：1)
- **星级**：4星
- **关键亮点**：详细分析了不同操作对丑陋度的影响，代码实现清晰。
- **核心代码**：
```cpp
for(R LL i = 1; i <= n; ++i) {
    if(a[i] > a[i - 1] and a[i] > a[i + 1]) {
        LL mid = max(a[i + 1], a[i - 1]);
        ans -= (a[i] - mid);
        a[i] = mid;
    }
}
```
- **个人心得**：作者通过详细的分析，证明了贪心策略的正确性，代码实现也非常简洁。

### 最优关键思路与技巧
- **贪心策略**：通过减少“山峰”柱子的高度，可以有效减少直方图的丑陋度。
- **初始丑陋度计算**：首先计算直方图的初始丑陋度，为后续的贪心操作提供基准。
- **代码实现**：通过简单的循环和条件判断，快速实现贪心策略。

### 拓展与举一反三
- **类似题目**：可以尝试解决其他涉及贪心策略的题目，如最小化操作次数或最大化收益的问题。
- **算法套路**：贪心算法在解决优化问题时非常有效，尤其是在问题可以分解为局部最优解的情况下。

### 推荐题目
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：37.66秒