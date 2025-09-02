# 题目信息

# Error Correct System

## 题目描述

Ford Prefect got a job as a web developer for a small company that makes towels. His current work task is to create a search engine for the website of the company. During the development process, he needs to write a subroutine for comparing strings $ S $ and $ T $ of equal length to be "similar". After a brief search on the Internet, he learned about the Hamming distance between two strings $ S $ and $ T $ of the same length, which is defined as the number of positions in which $ S $ and $ T $ have different characters. For example, the Hamming distance between words "permanent" and "pergament" is two, as these words differ in the fourth and sixth letters.

Moreover, as he was searching for information, he also noticed that modern search engines have powerful mechanisms to correct errors in the request to improve the quality of search. Ford doesn't know much about human beings, so he assumed that the most common mistake in a request is swapping two arbitrary letters of the string (not necessarily adjacent). Now he wants to write a function that determines which two letters should be swapped in string $ S $ , so that the Hamming distance between a new string $ S $ and string $ T $ would be as small as possible, or otherwise, determine that such a replacement cannot reduce the distance between the strings.

Help him do this!

## 说明/提示

In the second test it is acceptable to print $ i=2 $ , $ j=3 $ .

## 样例 #1

### 输入

```
9
pergament
permanent
```

### 输出

```
1
4 6
```

## 样例 #2

### 输入

```
6
wookie
cookie
```

### 输出

```
1
-1 -1
```

## 样例 #3

### 输入

```
4
petr
egor
```

### 输出

```
2
1 2
```

## 样例 #4

### 输入

```
6
double
bundle
```

### 输出

```
2
4 1
```

# AI分析结果



# 错误纠正系统

## 题目描述

Ford Prefect 在一家生产毛巾的小公司担任网页开发，需要实现字符串相似性检测功能。给定两个等长字符串 $S$ 和 $T$，通过交换 $S$ 中的两个字符（任意位置），使得交换后的 $S$ 与 $T$ 的汉明距离最小。要求输出交换后的最小汉明距离及交换位置（若无法减少则输出 -1 -1）。

## 说明/提示

汉明距离定义为相同位置字符不同的数量。交换两个字符可能使距离减少 0、1 或 2。

## 样例 #1

### 输入
```
9
pergament
permanent
```

### 输出
```
1
4 6
```

## 样例 #2

### 输入
```
6
wookie
cookie
```

### 输出
```
1
-1 -1
```

## 样例 #3

### 输入
```
4
petr
egor
```

### 输出
```
2
1 2
```

## 样例 #4

### 输入
```
6
double
bundle
```

### 输出
```
2
4 1
```

**算法分类**：贪心

---

### 题解分析与结论

**核心思路**：  
预处理所有字符差异位置，优先寻找能使距离减少 2 的交换（存在字符对 $(a,b)$ 和 $(b,a)$），其次寻找减少 1 的交换（存在字符 $b$ 在另一位置）。使用哈希表或二维数组记录字符对应关系以快速查询。

**最优题解亮点**：

1. **Zhao_daodao 的题解（4星）**  
   - 通过二维数组 `vis` 记录字符对 $(a_i, b_i)$ 的位置  
   - 优先处理减少 2 的情况，分类明确  
   - 时间复杂度 $O(n)$，空间优化合理  

2. **liuyifan 的题解（4星）**  
   - 使用双数组 `vis`（记录字符对）和 `mark`（记录字符存在性）  
   - 代码简洁高效，逻辑清晰  
   - 通过一次遍历处理两种优化情况  

**关键代码实现**：  
```cpp
int vis[300][300] = {-1}, mark[300] = {-1};
for (int i = 0; i < n; i++) {
    if (a[i] != b[i]) {
        sum++;
        vis[a[i]][b[i]] = i;  // 记录字符对位置
        mark[a[i]] = i;       // 记录字符存在性
    }
}
// 寻找最优交换
for (int i = 0; i < n; i++) {
    if (a[i] != b[i]) {
        if (vis[b[i]][a[i]] != -1) {  // 存在可减少2的交换
            printf("%d %d", i+1, vis[b[i]][a[i]]+1);
            return 0;
        }
        if (mark[b[i]] != -1) {       // 存在可减少1的交换
            ans = sum - 1;
            x = i + 1;
            y = mark[b[i]] + 1;
        }
    }
}
```

**拓展建议**：  
类似题目可考虑字符置换后的匹配优化，如[CF535D](https://codeforces.com/problemset/problem/535/D)（模式匹配）、[CF631C](https://codeforces.com/problemset/problem/631/C)（字符串排序）、[CF518A](https://codeforces.com/problemset/problem/518/A)（字典序优化）。

---

**推荐练习**：  
1. [CF527B - 错误纠正系统（原题）](https://www.luogu.com.cn/problem/CF527B)  
2. [CF535D - Tavas and Malekas](https://www.luogu.com.cn/problem/CF535D)  
3. [CF518A - Vitaly and Strings](https://www.luogu.com.cn/problem/CF518A)

---
处理用时：161.17秒