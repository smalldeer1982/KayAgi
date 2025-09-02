# 题目信息

# Minimum Difficulty

## 题目描述

Mike is trying rock climbing but he is awful at it.

There are $ n $ holds on the wall, $ i $ -th hold is at height $ a_{i} $ off the ground. Besides, let the sequence $ a_{i} $ increase, that is, $ a_{i}<a_{i+1} $ for all $ i $ from 1 to $ n-1 $ ; we will call such sequence a track. Mike thinks that the track $ a_{1} $ , ..., $ a_{n} $ has difficulty ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF496A/6c4805b013b934a5f994bca3651000871cc18881.png). In other words, difficulty equals the maximum distance between two holds that are adjacent in height.

Today Mike decided to cover the track with holds hanging on heights $ a_{1} $ , ..., $ a_{n} $ . To make the problem harder, Mike decided to remove one hold, that is, remove one element of the sequence (for example, if we take the sequence $ (1,2,3,4,5) $ and remove the third element from it, we obtain the sequence $ (1,2,4,5) $ ). However, as Mike is awful at climbing, he wants the final difficulty (i.e. the maximum difference of heights between adjacent holds after removing the hold) to be as small as possible among all possible options of removing a hold. The first and last holds must stay at their positions.

Help Mike determine the minimum difficulty of the track after removing one hold.

## 说明/提示

In the first sample you can remove only the second hold, then the sequence looks like $ (1,6) $ , the maximum difference of the neighboring elements equals 5.

In the second test after removing every hold the difficulty equals 2.

In the third test you can obtain sequences $ (1,3,7,8) $ , $ (1,2,7,8) $ , $ (1,2,3,8) $ , for which the difficulty is 4, 5 and 5, respectively. Thus, after removing the second element we obtain the optimal answer — 4.

## 样例 #1

### 输入

```
3
1 4 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
1 2 3 7 8
```

### 输出

```
4
```

# AI分析结果

### 题目翻译
# 最小难度

## 题目描述
迈克正在尝试攀岩，但他攀岩技术很差。

岩壁上有 $n$ 个岩点，第 $i$ 个岩点距离地面的高度为 $a_{i}$。此外，序列 $a_{i}$ 是递增的，即对于从 1 到 $n - 1$ 的所有 $i$，都有 $a_{i} < a_{i + 1}$，我们将这样的序列称为一条攀爬路径。迈克认为攀爬路径 $a_{1}, \cdots, a_{n}$ 的难度为 $\max\limits_{1\leq i\leq n - 1}(a_{i + 1} - a_{i})$。换句话说，难度等于高度相邻的两个岩点之间的最大距离。

今天，迈克决定攀爬这条由高度为 $a_{1}, \cdots, a_{n}$ 的岩点组成的路径。为了增加难度，迈克决定移除一个岩点，即移除序列中的一个元素（例如，如果我们有序列 $(1, 2, 3, 4, 5)$ 并移除其中的第三个元素，我们将得到序列 $(1, 2, 4, 5)$）。然而，由于迈克攀岩技术很差，他希望移除一个岩点后的最终难度（即移除岩点后相邻岩点高度的最大差值）在所有可能的移除岩点的方案中尽可能小。第一个和最后一个岩点的位置必须保持不变。

帮助迈克确定移除一个岩点后攀爬路径的最小难度。

## 说明/提示
在第一个样例中，你只能移除第二个岩点，然后序列变为 $(1, 6)$，相邻元素的最大差值为 5。

在第二个测试中，移除任何一个岩点后难度都为 2。

在第三个测试中，你可以得到序列 $(1, 3, 7, 8)$、$(1, 2, 7, 8)$、$(1, 2, 3, 8)$，它们的难度分别为 4、5 和 5。因此，移除第二个元素后我们得到最优答案——4。

## 样例 #1
### 输入
```
3
1 4 6
```
### 输出
```
5
```

## 样例 #2
### 输入
```
5
1 2 3 4 5
```
### 输出
```
2
```

## 样例 #3
### 输入
```
5
1 2 3 7 8
```
### 输出
```
4
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是通过枚举移除不同位置的岩点，计算移除后相邻岩点高度的最大差值，最后取所有情况中的最小值作为答案。
- **思路对比**：大部分题解是直接模拟移除岩点的过程，重新计算相邻元素的最大差值；而 codemap 的题解先计算相邻元素的差值并排序，再根据不同情况更新最小值。
- **算法要点**：都需要枚举 2 到 $n - 1$ 位置的岩点移除情况，计算每种情况下的最大差值。
- **解决难点**：如何正确处理移除岩点后的相邻元素差值计算，以及如何高效地更新最小难度值。

### 题解评分
- Reobrok_Kk：4 星。思路清晰，代码可读性高，使用数组和指针模拟移除过程。
- Insouciant21：4 星。使用 STL 容器，代码简洁，易于理解。
- 清小秋ovo：3 星。代码结构较清晰，但 `solve` 函数的逻辑可能需要一些思考。
- flywan123：3 星。代码逻辑较复杂，可读性一般。
- codemap：3 星。思路独特，但代码中对情况的判断和处理可能较难理解。

### 所选题解
- Reobrok_Kk（4 星）：关键亮点是使用指针记录上一个没被删的数，在枚举到被删的数时直接跳过，逻辑清晰。
- Insouciant21（4 星）：关键亮点是使用 STL 的 `vector` 容器和 `erase` 函数，代码简洁，利用迭代器计算差值。

### 重点代码
#### Reobrok_Kk
```cpp
for (int i = 2; i < n; ++i) { //枚举2~n-1每个数被删的情况
    int chayi = -1, last = 1; //last指针初始化，差异值初始化
    for (int j = 2; j <= n; ++j) {
        if (j == i) continue; //枚举到了要删的数，跳过
        chayi = max(abs(a[j] - a[last]), chayi); //更新差异值
        last = j; //这个数不被删，last指针才会赋值，避免没有删掉
    }
    ans = min(chayi, ans); //更新答案
}
```
核心思想：通过两层循环，外层枚举要移除的岩点，内层模拟移除该岩点后计算相邻岩点高度的最大差值，最后更新最小难度值。

#### Insouciant21
```cpp
for (int i = 1; i < n - 1; i++) {
    int diff = -1;
    vector<int> s(num);
    s.erase(next(s.begin(), i));
    for (auto iter = s.begin() + 1; iter != s.end(); iter++) diff = max(diff, *iter - *(iter - 1)); // 求每一个排列的差值
    ans = min(ans, diff);
}
```
核心思想：使用 `vector` 容器复制原序列，然后移除指定位置的元素，再通过迭代器计算移除元素后相邻元素的最大差值，最后更新最小难度值。

### 最优关键思路或技巧
- 使用枚举法，遍历所有可能移除的岩点位置。
- 对于移除岩点后的情况，直接计算相邻元素的最大差值。
- 可以使用指针或 STL 容器来简化代码实现。

### 可拓展之处
同类型题可能会有更多的限制条件，如移除多个岩点、岩点高度序列不是严格递增等。类似算法套路可以用于解决一些需要枚举所有可能情况并求最优解的问题，如排列组合问题、子集问题等。

### 推荐洛谷题目
- P1002 过河卒
- P1048 采药
- P1216 [USACO1.5] 数字三角形 Number Triangles

### 个人心得
- flywan123：这道题在黄题中算比较简单的，但难倒了本蒟蒻。总结：即使题目看起来简单，也可能存在一些容易出错的地方，需要仔细思考和调试。 

---
处理用时：38.07秒