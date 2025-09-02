# 题目信息

# Kalevitch and Chess

## 题目描述

A famous Berland's painter Kalevitch likes to shock the public. One of his last obsessions is chess. For more than a thousand years people have been playing this old game on uninteresting, monotonous boards. Kalevitch decided to put an end to this tradition and to introduce a new attitude to chessboards.

As before, the chessboard is a square-checkered board with the squares arranged in a $ 8×8 $ grid, each square is painted black or white. Kalevitch suggests that chessboards should be painted in the following manner: there should be chosen a horizontal or a vertical line of 8 squares (i.e. a row or a column), and painted black. Initially the whole chessboard is white, and it can be painted in the above described way one or more times. It is allowed to paint a square many times, but after the first time it does not change its colour any more and remains black. Kalevitch paints chessboards neatly, and it is impossible to judge by an individual square if it was painted with a vertical or a horizontal stroke.

Kalevitch hopes that such chessboards will gain popularity, and he will be commissioned to paint chessboards, which will help him ensure a comfortable old age. The clients will inform him what chessboard they want to have, and the painter will paint a white chessboard meeting the client's requirements.

It goes without saying that in such business one should economize on everything — for each commission he wants to know the minimum amount of strokes that he has to paint to fulfill the client's needs. You are asked to help Kalevitch with this task.

## 样例 #1

### 输入

```
WWWBWWBW
BBBBBBBB
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
```

### 输出

```
3
```

## 样例 #2

### 输入

```
WWWWWWWW
BBBBBBBB
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
```

### 输出

```
1
```

# AI分析结果



【中文重写题目】

# Kalevitch与棋盘

## 题目描述

著名Berland画家Kalevitch喜欢以独特的方式创作棋盘。初始为8x8全白棋盘，每次可选择一行或一列将其涂黑（多次涂染同一区域不会改变颜色）。给定目标棋盘，求达成该图案所需的最少操作次数。

## 样例 #1

### 输入

```
WWWBWWBW
BBBBBBBB
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
```

### 输出

```
3
```

## 样例 #2

### 输入

```
WWWWWWWW
BBBBBBBB
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
```

### 输出

```
1
```

---

【题解综合分析】

各题解核心思路一致：统计全黑行/列数之和，并特判全棋盘全黑的情况。关键差异在于特判处理方式和代码实现细节。最优解法时间复杂度为O(n²)，在8x8规模下完全可行。

---

【精选题解】

1. **作者：Tune_**（★★★★★）  
   **亮点**：双循环清晰分离行列判断，特判条件简洁  
   **代码核心**：
   ```cpp
   // 统计全黑行
   for(int i=0;i<8;i++) {
       bool f=1;
       for(int j=0;j<8;j++) f &= (a[i][j]=='B');
       ans += f;
   }
   // 统计全黑列
   for(int i=0;i<8;i++) {
       bool f=1;
       for(int j=0;j<8;j++) f &= (a[j][i]=='B');
       ans += f;
   }
   if(ans == 16) ans = 8; // 特判全棋盘全黑
   ```

2. **作者：呵呵侠**（★★★★☆）  
   **亮点**：变量命名规范，逻辑与Tune_解法等价  
   **个人心得**：明确强调特判条件的必要性，避免出现16次操作的错误答案

3. **作者：_Legacy**（★★★★☆）  
   **亮点**：使用提前break优化判断，代码效率略优  
   **代码片段**：
   ```cpp
   for(int i=0;i<8;i++){
       t=1;
       for(int j=0;j<8;j++) if(a[j][i]!='B') { t=0; break; }
       ans += t;
   }
   ```

---

【关键思路总结】

1. **贪心策略**：全黑行/列必须选择，因单次操作即可覆盖8格  
2. **特判机制**：当行、列全黑数各为8时，实际只需8次操作而非16次  
3. **优化技巧**：发现非全黑情况可提前终止内层循环

---

【拓展训练】

1. [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005) - 矩阵行操作与动态规划  
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219) - 棋盘行列覆盖判断  
3. [P1320 压缩技术](https://www.luogu.com.cn/problem/P1320) - 矩阵特征统计

---
处理用时：69.01秒