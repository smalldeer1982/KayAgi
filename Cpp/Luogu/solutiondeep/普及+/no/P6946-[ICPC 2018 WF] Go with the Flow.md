# 题目信息

# [ICPC 2018 WF] Go with the Flow

## 题目描述

在字体排印学中，“川流”是由单词之间的间隙组成的连续几列的空格。如图所示为几个用红色高亮标出的“川流”（文本被有意模糊处理来凸显川流）：

![img](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15694/1.png)

知名川流机构 Flo Ng 希望他在新的关于世界河流的书上出现尽可能长的川流。他会使用一种单一字宽的字体（每个字母和空格都具有相同的宽度）且左对齐，单词之间恰用一个空格分隔。对 Flo 来说，一条“川流”指的是连续几行里的空格，且相邻空格在行里出现的位置的距离不超过 $1$。川流不能包含末尾的空格。每行的单词都必须尽可能地紧凑，但不能有单词被拆到两行里。行宽至少不能短于文本中最长的一个单词。下图是同一个文本使用不同行宽的一个例子。

![img](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15694/2.png)

给定文本，你需要求出一个行宽使得该文本最长的川流尽可能长。

## 样例 #1

### 输入

```
21
The Yangtze is the third longest
river in Asia and the longest in
the world to flow
entirely in one country
```

### 输出

```
15 5
```

## 样例 #2

### 输入

```
25
When two or more rivers meet at
a confluence other than the sea
the resulting merged river takes
the name of one of those rivers
```

### 输出

```
21 6
```

# AI分析结果



动态规划

**分析与结论**  
本题需在枚举行宽的基础上，通过动态规划维护最长川流。关键点在于如何高效处理每行的空格位置，并使用滚动数组优化空间。题解通过行模拟生成空格位置，用一维DP数组结合相邻行的状态转移，解决了二维数组空间过大的问题。

---

**⭐题解：LJY_ljy（4星）**  
**关键亮点**  
1. **行模拟与DP结合**：通过模拟排版生成每行空格位置，动态规划计算最长川流。  
2. **滚动数组优化**：仅维护当前行和前一行状态，大幅降低空间复杂度。  
3. **位置标记清理**：用`used`数组标记有效位置，避免全量清零。  
**个人心得**  
> "当处理不同行宽时，只清除相关位置的cnt值，避免O(n)的全量操作。"  

**核心代码思想**  
- 枚举行宽，模拟生成每行的空格位置存入数组`G`。  
- 用`cnt[j]`记录以位置j结尾的最长川流长度，通过前一行j-1/j/j+1的状态转移。  
- 滚动数组`a`和`b`维护相邻行的有效空格位置，减少内存占用。

```cpp
int cnt[MAXN * MAXM]; // 维护当前行的最长川流
bool used[MAXN * MAXM]; // 标记有效位置

for (int gap = maxx; gap < sum + n; gap++) {
    // 模拟生成当前行空格存入bb数组
    while (j <= n) {
        if (当前行可添加空格) {
            G[++eid] = Len;
            bb[++len2] = Len;
            // 状态转移：取上一行的j-1/j/j+1的最大值+1
            cnt[Len] = max({cnt[Len-1], cnt[Len], cnt[Len+1]}) + 1;
            maxx = max(maxx, cnt[Len]);
        }
    }
    // 滚动数组更新
    swap(aa, bb);
}
```

---

**拓展思路**  
类似题型可参考：  
1. **文本排版优化**：如[P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)  
2. **动态规划空间优化**：如[P4059 [Code+#1]找爸爸](https://www.luogu.com.cn/problem/P4059)  
3. **状态转移与滚动数组**：如[P1541 乌龟棋](https://www.luogu.com.cn/problem/P1541)

---
处理用时：39.35秒