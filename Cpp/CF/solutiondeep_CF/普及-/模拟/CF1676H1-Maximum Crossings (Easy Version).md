# 题目信息

# Maximum Crossings (Easy Version)

## 题目描述

The only difference between the two versions is that in this version $ n \leq 1000 $ and the sum of $ n $ over all test cases does not exceed $ 1000 $ .

A terminal is a row of $ n $ equal segments numbered $ 1 $ to $ n $ in order. There are two terminals, one above the other.

You are given an array $ a $ of length $ n $ . For all $ i = 1, 2, \dots, n $ , there should be a straight wire from some point on segment $ i $ of the top terminal to some point on segment $ a_i $ of the bottom terminal. For example, the following pictures show two possible wirings if $ n=7 $ and $ a=[4,1,4,6,7,7,5] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676H1/71a1fe41f3cad0f3cbda88716457eefb4e46b4ca.png)A crossing occurs when two wires share a point in common. In the picture above, crossings are circled in red.

What is the maximum number of crossings there can be if you place the wires optimally?

## 说明/提示

The first test case is shown in the second picture in the statement.

In the second test case, the only wiring possible has the two wires cross, so the answer is $ 1 $ .

In the third test case, the only wiring possible has one wire, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
7
4 1 4 6 7 7 5
2
2 1
1
1
3
2 2 2```

### 输出

```
6
1
0
3```

# AI分析结果

### 题目翻译
# 最大交叉数（简单版本）

## 题目描述
两个版本之间的唯一区别在于，在这个版本中 $ n \leq 1000 $，并且所有测试用例的 $ n $ 之和不超过 $ 1000 $。

一个终端是一排 $n$ 个相等的线段，按顺序编号为 $ 1 $ 到 $ n $。有两个终端，一个在另一个上方。

给定一个长度为 $ n $ 的数组 $ a $。对于所有 $ i = 1, 2, \dots, n $，应该有一条直线从顶部终端的第 $ i $ 段上的某个点连接到底部终端的第 $ a_i $ 段上的某个点。例如，如果 $ n = 7 $ 且 $ a = [4,1,4,6,7,7,5] $，以下图片展示了两种可能的布线方式。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676H1/71a1fe41f3cad0f3cbda88716457eefb4e46b4ca.png)当两条线共享一个公共点时，就会出现交叉。在上面的图片中，交叉点用红色圆圈标记。

如果以最优方式放置这些线，最多会有多少个交叉点？

## 说明/提示
第一个测试用例在题目描述的第二张图片中展示。

在第二个测试用例中，唯一可能的布线方式使两条线交叉，因此答案是 $ 1 $。

在第三个测试用例中，唯一可能的布线方式只有一条线，因此答案是 $ 0 $。

## 样例 #1

### 输入
```
4
7
4 1 4 6 7 7 5
2
2 1
1
1
3
2 2 2
```

### 输出
```
6
1
0
3
```

### 综合分析与结论
- **思路对比**：两位作者思路一致，均发现当 $i<j$ 且 $a_i\ge a_j$ 时两条连线会产生交点，将问题转化为统计满足该条件的 $(i, j)$ 对数。
- **算法要点**：都采用了双重循环枚举的方法，时间复杂度为 $O(n^2)$。
- **解决难点**：核心难点在于找出连线产生交点的条件，两位作者都通过观察样例解决了该问题。

### 题解评分
- 作者：5k_sync_closer，3星。思路清晰，代码规范，但未对代码做详细解释，且提到的 $O(n\log n)$ 解法未在本题代码中实现。
- 作者：include_BM，3星。思路简洁，但代码片段不完整，缺乏输入输出和变量定义等部分。

由于所有题解均不足4星，以下给出通用建议与扩展思路：
- **通用建议**：对于此类问题，可先通过观察样例找出关键规律，再根据数据范围选择合适的算法。若数据范围较大，可考虑更高效的算法，如本题提到的二维偏序问题的 $O(n\log n)$ 解法。
- **扩展思路**：本题属于计数类问题，同类型题常需找出元素之间的关系并进行计数。类似算法套路包括枚举、排序、二分查找等。在处理此类问题时，可先尝试简单的枚举方法，再根据数据规模和时间复杂度要求进行优化。

### 推荐题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
- [P1309 瑞士轮](https://www.luogu.com.cn/problem/P1309)
- [P2279 [HNOI2003]消防局的设立](https://www.luogu.com.cn/problem/P2279)

### 重点代码
```cpp
// 作者：5k_sync_closer
for(int i = 1;i <= n;++i)
    for(int j = i + 1;j <= n;++j)
        s += a[i] >= a[j];

// 作者：include_BM
for(int j=1;j<=n;++j)
    for(int i=1;i<j;++i)
        if(a[i]>=a[j]) ++num;
```
**核心实现思想**：通过双重循环枚举所有可能的 $(i, j)$ 对，判断是否满足 $i<j$ 且 $a_i\ge a_j$，若满足则计数器加1。 

---
处理用时：26.03秒