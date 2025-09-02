# 题目信息

# Sushi for Two

## 题目描述

Arkady invited Anna for a dinner to a sushi restaurant. The restaurant is a bit unusual: it offers $ n $ pieces of sushi aligned in a row, and a customer has to choose a continuous subsegment of these sushi to buy.

The pieces of sushi are of two types: either with tuna or with eel. Let's denote the type of the $ i $ -th from the left sushi as $ t_i $ , where $ t_i = 1 $ means it is with tuna, and $ t_i = 2 $ means it is with eel.

Arkady does not like tuna, Anna does not like eel. Arkady wants to choose such a continuous subsegment of sushi that it has equal number of sushi of each type and each half of the subsegment has only sushi of one type. For example, subsegment $ [2, 2, 2, 1, 1, 1] $ is valid, but subsegment $ [1, 2, 1, 2, 1, 2] $ is not, because both halves contain both types of sushi.

Find the length of the longest continuous subsegment of sushi Arkady can buy.

## 说明/提示

In the first example Arkady can choose the subsegment $ [2, 2, 1, 1] $ or the subsegment $ [1, 1, 2, 2] $ with length $ 4 $ .

In the second example there is no way but to choose one of the subsegments $ [2, 1] $ or $ [1, 2] $ with length $ 2 $ .

In the third example Arkady's best choice is the subsegment $ [1, 1, 1, 2, 2, 2] $ .

## 样例 #1

### 输入

```
7
2 2 2 1 1 2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6
1 2 1 2 1 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
9
2 2 1 1 1 2 2 2 2
```

### 输出

```
6
```

# AI分析结果

### 中文题目重写
# 寿司双人餐

## 题目描述

Arkady邀请Anna去一家寿司餐厅共进晚餐。这家餐厅有点特别：它提供$n$块寿司排成一排，顾客需要选择一段连续的寿司来购买。

这些寿司有两种类型：金枪鱼寿司和鳗鱼寿司。我们用$t_i$表示从左数第$i$块寿司的类型，其中$t_i = 1$表示金枪鱼寿司，$t_i = 2$表示鳗鱼寿司。

Arkady不喜欢金枪鱼，Anna不喜欢鳗鱼。Arkady希望选择一段连续的寿司，使得这段寿司中两种类型的数量相等，并且每一半只包含一种类型的寿司。例如，子段$[2, 2, 2, 1, 1, 1]$是有效的，但子段$[1, 2, 1, 2, 1, 2]$是无效的，因为每一半都包含两种类型的寿司。

请找出Arkady可以购买的最长连续寿司子段的长度。

## 说明/提示

在第一个例子中，Arkady可以选择子段$[2, 2, 1, 1]$或子段$[1, 1, 2, 2]$，长度为$4$。

在第二个例子中，只能选择子段$[2, 1]$或子段$[1, 2]$，长度为$2$。

在第三个例子中，Arkady的最佳选择是子段$[1, 1, 1, 2, 2, 2]$。

## 样例 #1

### 输入

```
7
2 2 2 1 1 2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6
1 2 1 2 1 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
9
2 2 1 1 1 2 2 2 2
```

### 输出

```
6
```

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是通过遍历数组，记录连续相同类型的寿司长度，并在类型切换时计算当前有效子段的长度。所有题解都采用了类似的方法，主要区别在于变量命名和代码实现的细节。

### 评分较高的题解
1. **作者：srds_cbddl (5星)**
   - **关键亮点**：代码简洁，思路清晰，直接通过遍历数组并在类型切换时更新答案。
   - **核心代码**：
     ```cpp
     int cnt = 1, ans = 1, minn = 0;
     for (int i = 0; i < n - 1; i ++) {
         if (a[i] == a[i + 1]) cnt ++, change_max (ans, min (minn, cnt));
         else minn = cnt, cnt = 1;
     }
     ```

2. **作者：sz_jinzikai (4星)**
   - **关键亮点**：使用两个计数器分别记录连续1和2的长度，并在类型切换时交换计数器的作用。
   - **核心代码**：
     ```cpp
     for (int i = 1; i < n; i ++)
         if (a[i] == a[i - 1]) now2 ++;
         else maxx = max (maxx, min (now1, now2)), now1 = now2, now2 = 1;
     ```

3. **作者：StudyingFather (4星)**
   - **关键亮点**：通过记录当前段和前一段的长度，在类型切换时更新答案，代码逻辑清晰。
   - **核心代码**：
     ```cpp
     for (int i = 2; i <= n; i++)
         if (a[i] != cur) {
             ans = max(ans, min(cnt1, cnt2));
             if (cur == 1) cnt2 = 1;
             else cnt1 = 1;
             cur = a[i];
         } else {
             if (cur == 1) cnt1++;
             else cnt2++;
         }
     ```

### 最优关键思路
通过遍历数组，记录连续相同类型的寿司长度，并在类型切换时计算当前有效子段的长度。这种方法的时间复杂度为$O(n)$，空间复杂度为$O(1)$，非常高效。

### 可拓展之处
类似的问题可以扩展到更多类型的寿司或更复杂的条件，例如要求子段中每种类型的寿司数量相等且顺序特定。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)
3. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)

### 个人心得摘录
- **srds_cbddl**：直接通过遍历数组并在类型切换时更新答案，代码简洁且高效。
- **sz_jinzikai**：使用两个计数器分别记录连续1和2的长度，并在类型切换时交换计数器的作用，思路清晰。
- **StudyingFather**：通过记录当前段和前一段的长度，在类型切换时更新答案，代码逻辑清晰。

---
处理用时：33.83秒