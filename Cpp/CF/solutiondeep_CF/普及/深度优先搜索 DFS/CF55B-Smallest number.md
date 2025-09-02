# 题目信息

# Smallest number

## 题目描述

Recently, Vladimir got bad mark in algebra again. To avoid such unpleasant events in future he decided to train his arithmetic skills. He wrote four integer numbers $ a $ , $ b $ , $ c $ , $ d $ on the blackboard. During each of the next three minutes he took two numbers from the blackboard (not necessarily adjacent) and replaced them with their sum or their product. In the end he got one number. Unfortunately, due to the awful memory he forgot that number, but he remembers four original numbers, sequence of the operations and his surprise because of the very small result. Help Vladimir remember the forgotten number: find the smallest number that can be obtained from the original numbers by the given sequence of operations.

## 样例 #1

### 输入

```
1 1 1 1
+ + *
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 2 2 2
* * +
```

### 输出

```
8
```

## 样例 #3

### 输入

```
1 2 3 4
* + +
```

### 输出

```
9
```

# AI分析结果

【题目内容】
# 最小数字

## 题目描述

最近，Vladimir在代数考试中又得了低分。为了避免将来再次发生这种不愉快的事情，他决定训练自己的算术技能。他在黑板上写了四个整数 $a$、$b$、$c$、$d$。在接下来的三分钟里，他每分钟从黑板上选取两个数（不一定相邻），并用它们的和或积替换它们。最终，他得到了一个数字。不幸的是，由于记忆力差，他忘记了那个数字，但他记得四个原始数字、操作的顺序以及他对结果非常小的惊讶。帮助Vladimir回忆起那个被遗忘的数字：通过给定的操作顺序，找到可以从原始数字中得到的最小数字。

## 样例 #1

### 输入

```
1 1 1 1
+ + *
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 2 2 2
* * +
```

### 输出

```
8
```

## 样例 #3

### 输入

```
1 2 3 4
* + +
```

### 输出

```
9
```

【题解分析与结论】
题目要求通过给定的操作顺序，从四个数字中得到最小的结果。由于操作顺序固定，且每次操作可以选择任意两个数进行加法或乘法，因此可以通过暴力搜索或全排列的方式枚举所有可能的操作顺序，最终取最小值。

【评分较高的题解】
1. **作者：linyinuo2008 (赞：13)**
   - **星级：4.5**
   - **关键亮点：**
     - 使用深度优先搜索（DFS）进行暴力枚举，思路清晰。
     - 通过`vis`数组记录操作情况，确保每次操作后回溯还原。
     - 代码结构清晰，注释详细，易于理解。
   - **个人心得：**
     - 强调了初始化`ans`为无限大的重要性，避免因未初始化导致的错误。
     - 通过回溯条件明确，确保搜索的正确性。

   ```cpp
   void dfs(int cur) {
       if (cur == 3) {
           for (int i = 0; i < 4; i++)
               if (!vis[i])
                   ans = min(ans, a[i]);
           return;
       }
       for (int i = 0; i < 4; i++) {
           for (int j = 0; j < 4; j++) {
               if (i == j || vis[i] || vis[j]) continue;
               long long p = a[i];
               vis[j] = 1;
               if (ope[cur] == '+') a[i] += a[j];
               else if (ope[cur] == '*') a[i] *= a[j];
               dfs(cur + 1);
               vis[j] = 0;
               a[i] = p;
           }
       }
   }
   ```

2. **作者：翼德天尊 (赞：4)**
   - **星级：4**
   - **关键亮点：**
     - 使用DFS进行暴力搜索，每次选择两个数进行操作，并将结果覆盖其中一个数，另一个数标记为已使用。
     - 通过回溯还原现场，确保搜索的完整性。
     - 代码简洁，逻辑清晰。
   - **个人心得：**
     - 强调了开`long long`的重要性，避免数据溢出。

   ```cpp
   void dfs(int d) {
       if (d == 4) {
           int zc = 0;
           for (int i = 1; i <= 4; i++) {
               if (!vis[i]) zc = a[i];
           }
           ans = min(ans, zc);
           return;
       }
       for (int i = 1; i <= 4; i++) {
           if (!vis[i]) {
               for (int j = i + 1; j <= 4; j++) {
                   if (!vis[j]) {
                       vis[i] = 1;
                       int s = a[j];
                       if (b[d] == '+') a[j] += a[i];
                       else if (b[d] == '*') a[j] *= a[i];
                       dfs(d + 1);
                       a[j] = s;
                       vis[i] = 0;
                   }
               }
           }
       }
   }
   ```

3. **作者：Siyuan (赞：3)**
   - **星级：4**
   - **关键亮点：**
     - 使用DFS进行暴力搜索，每次枚举两个数进行操作，并将结果覆盖其中一个数，另一个数标记为已使用。
     - 通过回溯还原现场，确保搜索的完整性。
     - 代码简洁，逻辑清晰。
   - **个人心得：**
     - 强调了回溯的重要性，确保每次操作后能够正确还原现场。

   ```cpp
   void dfs(const int &left) {
       if (left == 1) {
           register ll s;
           for (register int i = 1; i <= 4; i++)
               if (a[i] != -1) { s = a[i]; break; }
           ans = (ans < s ? ans : s);
           return;
       }
       for (register int i = 1; i <= 4; i++)
           for (register int j = i + 1; j <= 4; j++) {
               register int k = 4 - left + 1;
               if (a[i] == -1 || a[j] == -1 || p[k] == '-') continue;
               register ll x = a[i], y = a[j];
               register char t = p[k];
               p[k] = '-'; a[j] = -1;
               if (t == '+') a[i] = x + y; else a[i] = x * y;
               dfs(left - 1);
               a[i] = x; a[j] = y; p[k] = t;
           }
   }
   ```

【最优关键思路或技巧】
- **暴力搜索与回溯**：通过DFS枚举所有可能的操作顺序，并通过回溯确保每次操作后能够正确还原现场，避免遗漏或重复计算。
- **标记与覆盖**：在操作过程中，将结果覆盖其中一个数，另一个数标记为已使用，简化了删除和添加操作的处理。
- **初始化与边界条件**：确保`ans`初始化为无限大，避免因未初始化导致的错误。

【可拓展之处】
- 类似的问题可以通过暴力搜索或全排列的方式解决，尤其是在数据规模较小的情况下。
- 可以通过剪枝优化搜索过程，减少不必要的计算。

【推荐题目】
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)

---
处理用时：58.88秒