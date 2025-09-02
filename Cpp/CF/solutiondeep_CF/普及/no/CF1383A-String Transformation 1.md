# 题目信息

# String Transformation 1

## 题目描述

Note that the only difference between String Transformation 1 and String Transformation 2 is in the move Koa does. In this version the letter $ y $ Koa selects must be strictly greater alphabetically than $ x $ (read statement for better understanding). You can make hacks in these problems independently.

Koa the Koala has two strings $ A $ and $ B $ of the same length $ n $ ( $ |A|=|B|=n $ ) consisting of the first $ 20 $ lowercase English alphabet letters (ie. from a to t).

In one move Koa:

1. selects some subset of positions $ p_1, p_2, \ldots, p_k $ ( $ k \ge 1; 1 \le p_i \le n; p_i \neq p_j $ if $ i \neq j $ ) of $ A $ such that $ A_{p_1} = A_{p_2} = \ldots = A_{p_k} =         x $ (ie. all letters on this positions are equal to some letter $ x $ ).
2. selects a letter $ y $ (from the first $ 20 $ lowercase letters in English alphabet) such that $ y>x $ (ie. letter $ y $ is strictly greater alphabetically than $ x $ ).
3. sets each letter in positions $ p_1, p_2, \ldots, p_k $ to letter $ y $ . More formally: for each $ i $ ( $ 1 \le i \le         k $ ) Koa sets $ A_{p_i} = y $ .  Note that you can only modify letters in string $ A $ .

Koa wants to know the smallest number of moves she has to do to make strings equal to each other ( $ A = B $ ) or to determine that there is no way to make them equal. Help her!

## 说明/提示

- In the $ 1 $ -st test case Koa: 
  1. selects positions $ 1 $ and $ 2 $ and sets $ A_1 = A_2 =  $ b ( $ \color{red}{aa}b \rightarrow \color{blue}{bb}b $ ).
  2. selects positions $ 2 $ and $ 3 $ and sets $ A_2 =             A_3 =  $ c ( $ b\color{red}{bb} \rightarrow b\color{blue}{cc} $ ).
- In the $ 2 $ -nd test case Koa has no way to make string $ A $ equal $ B $ .
- In the $ 3 $ -rd test case Koa: 
  1. selects position $ 1 $ and sets $ A_1 =  $ t ( $ \color{red}{a}bc             \rightarrow \color{blue}{t}bc $ ).
  2. selects position $ 2 $ and sets $ A_2 =  $ s ( $ t\color{red}{b}c             \rightarrow t\color{blue}{s}c $ ).
  3. selects position $ 3 $ and sets $ A_3 =  $ r ( $ ts\color{red}{c}             \rightarrow ts\color{blue}{r} $ ).

## 样例 #1

### 输入

```
5
3
aab
bcc
4
cabc
abcb
3
abc
tsr
4
aabd
cccd
5
abcbd
bcdda```

### 输出

```
2
-1
3
2
-1```

# AI分析结果

### 题目内容重写

#### 题目描述

注意，String Transformation 1 和 String Transformation 2 的唯一区别在于 Koa 的操作方式。在这个版本中，Koa 选择的字母 $y$ 必须严格大于字母 $x$（详见题目描述）。你可以在这两个问题中独立地进行 hack。

Koa 有两只字符串 $A$ 和 $B$，它们的长度相同，均为 $n$（$|A|=|B|=n$），且由前 20 个小写英文字母组成（即从 a 到 t）。

在一次操作中，Koa：

1. 选择 $A$ 中的一些位置 $p_1, p_2, \ldots, p_k$（$k \ge 1; 1 \le p_i \le n; p_i \neq p_j$ 如果 $i \neq j$），使得 $A_{p_1} = A_{p_2} = \ldots = A_{p_k} = x$（即这些位置上的字母都等于某个字母 $x$）。
2. 选择一个字母 $y$（从前 20 个小写英文字母中选择），使得 $y > x$（即字母 $y$ 严格大于字母 $x$）。
3. 将位置 $p_1, p_2, \ldots, p_k$ 上的字母设置为 $y$。更正式地说：对于每个 $i$（$1 \le i \le k$），Koa 将 $A_{p_i} = y$。注意，你只能修改字符串 $A$ 中的字母。

Koa 想知道她需要进行的最少操作次数，以使字符串 $A$ 和 $B$ 相等（$A = B$），或者确定无法使它们相等。请帮助她！

#### 说明/提示

- 在第 1 个测试用例中，Koa：
  1. 选择位置 1 和 2，并将 $A_1 = A_2 = b$（$aa b \rightarrow bb b$）。
  2. 选择位置 2 和 3，并将 $A_2 = A_3 = c$（$b bb \rightarrow b cc$）。
- 在第 2 个测试用例中，Koa 无法使字符串 $A$ 等于 $B$。
- 在第 3 个测试用例中，Koa：
  1. 选择位置 1，并将 $A_1 = t$（$a bc \rightarrow t bc$）。
  2. 选择位置 2，并将 $A_2 = s$（$t b c \rightarrow t s c$）。
  3. 选择位置 3，并将 $A_3 = r$（$t s c \rightarrow t s r$）。

#### 样例 #1

##### 输入

```
5
3
aab
bcc
4
cabc
abcb
3
abc
tsr
4
aabd
cccd
5
abcbd
bcdda
```

##### 输出

```
2
-1
3
2
-1
```

### 算法分类
并查集

### 题解分析与结论

#### 综合分析
该题的核心在于通过并查集来维护字符之间的转换关系，从而减少操作次数。并查集的使用使得我们可以高效地合并字符集合，并统计合并次数作为最小操作次数。所有题解都提到了无解情况的判断，即当 $A_i > B_i$ 时，直接输出 -1。

#### 最优题解

1. **题解作者：fmj_123 (赞：13)**  
   **星级：5星**  
   **关键亮点**：  
   - 使用并查集维护字符转换关系，简洁高效。
   - 通过路径压缩优化并查集操作，减少时间复杂度。
   - 代码清晰，逻辑严谨，易于理解。

   **核心代码**：
   ```cpp
   int fafa(int x) {
       if (f[x] == x) return x;
       return f[x] = fafa(f[x]);
   }
   void hebing(int x, int y) {
       x = fafa(x); y = fafa(y);
       if (x != y) {
           ans++;
           f[x] = y;
       }
   }
   ```

2. **题解作者：whiteqwq (赞：3)**  
   **星级：4星**  
   **关键亮点**：  
   - 通过并查集维护字符转换关系，思路清晰。
   - 代码简洁，易于实现。
   - 详细解释了并查集的使用场景和优化方法。

   **核心代码**：
   ```cpp
   int find(int x) {
       return f[x] == x ? x : f[x] = find(f[x]);
   }
   void merge(int x, int y) {
       x = find(x), y = find(y);
       if (x != y) {
           f[x] = y;
           ans++;
       }
   }
   ```

3. **题解作者：_GW_ (赞：2)**  
   **星级：4星**  
   **关键亮点**：  
   - 使用并查集维护字符转换关系，代码简洁。
   - 通过路径压缩优化并查集操作，减少时间复杂度。
   - 详细解释了无解情况的判断方法。

   **核心代码**：
   ```cpp
   int find(int x) {
       return fa[x] == x ? x : fa[x] = find(fa[x]);
   }
   void merge(int x, int y) {
       x = find(x), y = find(y);
       if (x != y) {
           fa[x] = y;
           res++;
       }
   }
   ```

### 最优关键思路与技巧
- **并查集优化**：通过路径压缩和按秩合并优化并查集操作，减少时间复杂度。
- **无解判断**：在遍历字符串时，若发现 $A_i > B_i$，直接输出 -1，避免不必要的计算。
- **合并次数统计**：在并查集合并操作中统计合并次数，作为最小操作次数。

### 可拓展之处
- **类似问题**：可以扩展到更复杂的字符转换问题，如允许字符转换为任意字符，或增加其他限制条件。
- **并查集应用**：并查集在解决连通性问题、图论问题等方面有广泛应用，可以进一步学习其在不同场景下的应用。

### 推荐题目
1. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
2. [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)
3. [P1197 [JSOI2008]星球大战](https://www.luogu.com.cn/problem/P1197)

---
处理用时：42.38秒