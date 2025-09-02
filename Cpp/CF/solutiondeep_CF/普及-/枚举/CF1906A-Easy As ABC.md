# 题目信息

# Easy As ABC

## 题目描述

You are playing a word puzzle. The puzzle starts with a $ 3 $ by $ 3 $ grid, where each cell contains either the letter A, B, or C.

The goal of this puzzle is to find the lexicographically smallest possible word of length $ 3 $ . The word can be formed by choosing three different cells where the cell containing the first letter is adjacent to the cell containing the second letter, and the cell containing the second letter is adjacent to the cell containing the third letter.

Two cells are adjacent to each other if they share a border or a corner, as shown in the following illustration. Formally, if $ (r, c) $ denotes the cell in the $ r $ -th row and $ c $ -th column, then cell $ (r, c) $ is adjacent to cell $ (r, c + 1) $ , $ (r - 1, c + 1) $ , $ (r - 1, c) $ , $ (r - 1, c - 1) $ , $ (r, c - 1) $ , $ (r + 1, c - 1) $ , $ (r + 1, c) $ , and $ (r + 1, c + 1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906A/525e4da2ea69e21f85179b7ddc65c24b70ec2325.png)Determine the lexicographically smallest possible word of length $ 3 $ that you can find within the grid.

A string $ s $ of length $ n $ is lexicographically smaller than string $ t $ of the same length if there exists an integer $ 1 \leq i \leq n $ such that $ s_j = t_j $ for all $ 1 \leq j < i $ , and $ s_i < t_i $ in alphabetical order. The following illustration shows some examples on some grids and their the lexicographically smallest possible word of length $ 3 $ that you can find within the grids.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906A/2e823a64da2250303d9d2bed5748864eed6f5643.png)

## 样例 #1

### 输入

```
BCB
CAC
BCB```

### 输出

```
ABC```

## 样例 #2

### 输入

```
BCB
CCC
CCA```

### 输出

```
ACB```

## 样例 #3

### 输入

```
ACA
CBC
ACA```

### 输出

```
ABA```

## 样例 #4

### 输入

```
ACA
CAC
ACA```

### 输出

```
AAA```

## 样例 #5

### 输入

```
CCC
CBC
CCC```

### 输出

```
BCC```

# AI分析结果

### 题目内容中文重写
# 简单如 ABC

## 题目描述
你正在玩一个单词谜题。谜题从一个 3×3 的网格开始，网格中的每个单元格都包含字母 A、B 或 C。

这个谜题的目标是找到长度为 3 的字典序最小的单词。这个单词可以通过选择三个不同的单元格来组成，其中包含第一个字母的单元格与包含第二个字母的单元格相邻，包含第二个字母的单元格与包含第三个字母的单元格相邻。

如果两个单元格共享一条边或一个角，则它们彼此相邻，如下图所示。形式上，如果用 $(r, c)$ 表示第 $r$ 行第 $c$ 列的单元格，那么单元格 $(r, c)$ 与单元格 $(r, c + 1)$、$(r - 1, c + 1)$、$(r - 1, c)$、$(r - 1, c - 1)$、$(r, c - 1)$、$(r + 1, c - 1)$、$(r + 1, c)$ 和 $(r + 1, c + 1)$ 相邻。

![相邻单元格图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906A/525e4da2ea69e21f85179b7ddc65c24b70ec2325.png)

确定你能在网格中找到的长度为 3 的字典序最小的单词。

如果存在一个整数 $1 \leq i \leq n$，使得对于所有 $1 \leq j < i$ 都有 $s_j = t_j$，并且按字母顺序 $s_i < t_i$，那么长度为 $n$ 的字符串 $s$ 在字典序上小于长度相同的字符串 $t$。下图展示了一些网格以及在这些网格中能找到的长度为 3 的字典序最小的单词的示例。

![示例图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906A/2e823a64da2250303d9d2bed5748864eed6f5643.png)

## 样例 #1
### 输入
```
BCB
CAC
BCB
```
### 输出
```
ABC
```

## 样例 #2
### 输入
```
BCB
CCC
CCA
```
### 输出
```
ACB
```

## 样例 #3
### 输入
```
ACA
CBC
ACA
```
### 输出
```
ABA
```

## 样例 #4
### 输入
```
ACA
CAC
ACA
```
### 输出
```
AAA
```

## 样例 #5
### 输入
```
CCC
CBC
CCC
```
### 输出
```
BCC
```

### 综合分析与结论
由于暂无题解，以下给出通用建议与扩展思路。

通用建议：
 - 可以采用暴力枚举的方法，遍历网格中所有可能的三个相邻单元格的组合，生成对应的长度为 3 的单词，然后比较这些单词的字典序，找出最小的那个。
 - 为了方便判断相邻关系，可以使用偏移量数组来表示相邻单元格的位置。

扩展思路：
同类型题或类似算法套路：这种在网格中寻找满足特定条件路径或组合的题目比较常见。例如在更大规模的网格中寻找满足条件的最长路径、特定形状的组合等。可以使用深度优先搜索（DFS）或广度优先搜索（BFS）来处理更复杂的相邻关系和路径问题。

### 推荐洛谷题目
1. P1162 填涂颜色：在网格中处理连通区域的问题，与本题在网格中寻找特定组合有相似之处。
2. P1451 求细胞数量：通过遍历网格来确定连通区域的数量，涉及到相邻关系的判断。
3. P1605 迷宫：在网格中寻找可行路径，与本题在网格中寻找满足条件的组合思路有一定关联。 

---
处理用时：18.32秒