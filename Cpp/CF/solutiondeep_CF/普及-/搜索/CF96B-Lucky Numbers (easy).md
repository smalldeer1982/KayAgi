# 题目信息

# Lucky Numbers (easy)

## 题目描述

Petya loves lucky numbers. Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than $ 4 $ and $ 7 $ . For example, numbers $ 47 $ , $ 744 $ , $ 4 $ are lucky and $ 5 $ , $ 17 $ , $ 467 $ are not.

Lucky number is super lucky if it's decimal representation contains equal amount of digits $ 4 $ and $ 7 $ . For example, numbers $ 47 $ , $ 7744 $ , $ 474477 $ are super lucky and $ 4 $ , $ 744 $ , $ 467 $ are not.

One day Petya came across a positive integer $ n $ . Help him to find the least super lucky number which is not less than $ n $ .

## 样例 #1

### 输入

```
4500
```

### 输出

```
4747
```

## 样例 #2

### 输入

```
47
```

### 输出

```
47
```

# AI分析结果

### 题目内容重写
#### 幸运数字（简单版）

**题目描述**

Petya喜欢幸运数字。大家都知道，如果一个正整数的十进制表示中只包含数字$4$和$7$，那么这个数就是幸运数字。例如，数字$47$、$744$、$4$是幸运数字，而$5$、$17$、$467$则不是。

一个幸运数字如果其十进制表示中$4$和$7$的数量相等，则称为超级幸运数字。例如，数字$47$、$7744$、$474477$是超级幸运数字，而$4$、$744$、$467$则不是。

有一天，Petya遇到了一个正整数$n$。请你帮助他找到不小于$n$的最小超级幸运数字。

**样例 #1**

**输入**
```
4500
```

**输出**
```
4747
```

**样例 #2**

**输入**
```
47
```

**输出**
```
47
```

### 题解分析与结论

#### 综合分析
本题的核心目标是找到不小于给定数$n$的最小超级幸运数字。超级幸运数字的定义是只包含数字$4$和$7$，并且$4$和$7$的数量相等。题解中主要采用了以下几种思路：

1. **BFS（广度优先搜索）**：通过逐层生成只包含$4$和$7$的数字，并检查是否满足超级幸运数字的条件。
2. **打表法**：预先生成所有可能的超级幸运数字，然后通过遍历表来找到符合条件的数字。
3. **DFS（深度优先搜索）**：通过递归生成所有可能的超级幸运数字，并在生成过程中进行剪枝。

#### 最优思路与技巧
- **BFS**：BFS能够保证找到的第一个符合条件的数字就是最小的，因此适合用于求解最小超级幸运数字的问题。
- **打表法**：虽然打表法在本题中可行，但由于超级幸运数字的数量较多，打表法在实际应用中可能不够高效。
- **DFS**：DFS可以通过剪枝优化，但在本题中BFS更为直接和高效。

#### 推荐题解
1. **作者：hensier (赞：91)**  
   **星级：★★★★★**  
   **关键亮点**：使用BFS逐层生成数字，确保找到的第一个符合条件的数字是最小的。代码清晰，逻辑严谨。  
   **核心代码**：
   ```cpp
   void check(long long x) {
       if (x < n) return;
       long long y = x, a = 0, b = 0;
       while (x) {
           if (x % 10 - 4) a++;
           else b++;
           x /= 10;
       }
       if (a == b) {
           cout << y;
           exit(0);
       }
   }
   ```

2. **作者：StarryWander (赞：11)**  
   **星级：★★★★**  
   **关键亮点**：使用BFS并结合结构体记录$4$和$7$的数量，确保在生成过程中直接判断是否符合条件。  
   **核心代码**：
   ```cpp
   struct node {
       ll x, stp;
   };
   while (!q.empty()) {
       node k = q.front();
       if (k.x >= n && k.stp == 0) {
           cout << k.x;
           return 0;
       }
       if (k.x < 1e9) {
           q.push((node){k.x * 10 + 4, k.stp + 1});
           q.push((node){k.x * 10 + 7, k.stp - 1});
       }
       q.pop();
   }
   ```

3. **作者：_Qer (赞：9)**  
   **星级：★★★★**  
   **关键亮点**：使用BFS生成数字，并在生成过程中直接判断是否符合条件，代码简洁高效。  
   **核心代码**：
   ```cpp
   inline bool check(long long x) {
       int a = 0, b = 0;
       while (x) {
           if (x % 10 == 7) ++a;
           else ++b;
           x /= 10;
       }
       return a == b;
   }
   ```

### 扩展思路与推荐题目
- **扩展思路**：本题可以扩展到其他类似的数字生成问题，例如生成只包含特定数字且满足特定条件的数字。
- **推荐题目**：
  1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
  2. [P1045 数的划分](https://www.luogu.com.cn/problem/P1045)
  3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得摘录
- **hensier**：BFS能够确保找到的第一个符合条件的数字是最小的，因此在本题中非常适用。
- **StarryWander**：使用结构体记录$4$和$7$的数量，可以在生成过程中直接判断是否符合条件，减少了后续的检查步骤。
- **_Qer**：BFS生成数字时，先加$4$再加$7$，可以确保生成的数字顺序是最小的。

---
处理用时：34.95秒