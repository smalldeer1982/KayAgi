# 题目信息

# Lara Croft and the New Game

## 题目描述

You might have heard about the next game in Lara Croft series coming out this year. You also might have watched its trailer. Though you definitely missed the main idea about its plot, so let me lift the veil of secrecy.

Lara is going to explore yet another dangerous dungeon. Game designers decided to use good old 2D environment. The dungeon can be represented as a rectangle matrix of $ n $ rows and $ m $ columns. Cell $ (x,y) $ is the cell in the $ x $ -th row in the $ y $ -th column. Lara can move between the neighbouring by side cells in all four directions.

Moreover, she has even chosen the path for herself to avoid all the traps. She enters the dungeon in cell $ (1,1) $ , that is top left corner of the matrix. Then she goes down all the way to cell $ (n,1) $ — the bottom left corner. Then she starts moving in the snake fashion — all the way to the right, one cell up, then to the left to the cell in $ 2 $ -nd column, one cell up. She moves until she runs out of non-visited cells. $ n $ and $ m $ given are such that she always end up in cell $ (1,2) $ .

Lara has already moved to a neighbouring cell $ k $ times. Can you determine her current position?

## 说明/提示

Here is her path on matrix $ 4 $ by $ 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF976B/1b2df8f31f927201c078b0cd1ef3dccbc8991311.png)

## 样例 #1

### 输入

```
4 3 0
```

### 输出

```
1 1
```

## 样例 #2

### 输入

```
4 3 11
```

### 输出

```
1 2
```

## 样例 #3

### 输入

```
4 3 7
```

### 输出

```
3 2
```

# AI分析结果

### 题目内容翻译

# Lara Croft and the New Game

## 题目描述

你可能已经听说过今年即将推出的Lara Croft系列新游戏。你可能也看过它的预告片。不过你肯定错过了它的主要剧情，所以让我来揭开这层神秘的面纱。

Lara将探索另一个危险的地下城。游戏设计师决定使用经典的2D环境。地下城可以表示为一个$n$行$m$列的矩形矩阵。单元格$(x,y)$表示第$x$行第$y$列的单元格。Lara可以在四个方向上移动到相邻的单元格。

此外，她甚至为自己选择了一条路径，以避免所有的陷阱。她从矩阵的左上角$(1,1)$进入地下城。然后她一直向下走到左下角的单元格$(n,1)$。接着她开始以蛇形方式移动——一直向右移动，然后向上移动一格，再向左移动到第2列，再向上移动一格。她一直移动，直到没有未访问的单元格为止。给定的$n$和$m$使得她最终会停在单元格$(1,2)$。

Lara已经移动了$k$次到相邻的单元格。你能确定她当前的位置吗？

## 说明/提示

以下是她在$4 \times 3$矩阵上的路径：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF976B/1b2df8f31f927201c078b0cd1ef3dccbc8991311.png)

## 样例 #1

### 输入

```
4 3 0
```

### 输出

```
1 1
```

## 样例 #2

### 输入

```
4 3 11
```

### 输出

```
1 2
```

## 样例 #3

### 输入

```
4 3 7
```

### 输出

```
3 2
```

### 题解分析与结论

这道题目要求我们在一个$n \times m$的矩阵中，根据Lara的移动规则，确定她在移动$k$步后的位置。由于$n$和$m$的范围可能很大（$2 \leq n, m \leq 10^9$），直接模拟移动过程是不可行的。因此，我们需要通过数学方法直接计算出第$k$步的位置。

#### 关键思路：
1. **路径分段**：将Lara的路径分为两部分：
   - 第一部分：从$(1,1)$直线向下移动到$(n,1)$。
   - 第二部分：从$(n,1)$开始，以蛇形方式移动到$(1,2)$。
2. **数学计算**：
   - 如果$k < n$，则Lara在第一部分，位置为$(k+1, 1)$。
   - 如果$k \geq n$，则Lara在第二部分。计算$k_1 = k - n$，然后根据$k_1$与$m-1$的关系，确定当前行和列的位置。

#### 难点：
- 如何在不模拟的情况下，直接计算出蛇形路径中的位置。
- 处理大范围数据时的数学推导和边界条件。

### 高星题解推荐

#### 题解1：作者：wwwidk1234 (赞：6)
- **星级**：5星
- **关键亮点**：
  - 思路清晰，将路径分为两部分，分别处理。
  - 通过数学公式直接计算位置，避免了模拟的复杂性。
  - 代码简洁，逻辑严密。
- **核心代码**：
  ```cpp
  if(k<n) cout<<k+1<<" "<<1<<endl;
  else {
      long long k1=k-n;
      if((k1/(m-1))%2==1) cout<<n-k1/(m-1)<<" "<<m-k1%(m-1)<<endl;
      else cout<<n-k1/(m-1)<<" "<<k1%(m-1)+2<<endl;
  }
  ```

#### 题解2：作者：KEBrantily (赞：3)
- **星级**：4星
- **关键亮点**：
  - 同样将路径分为两部分，思路清晰。
  - 通过行的奇偶性判断移动方向，简化了计算。
  - 代码简洁，逻辑清晰。
- **核心代码**：
  ```cpp
  if(k<n) cout<<k+1<<" "<<1;
  else {
      k=k-n+1;
      long long t=(k-1)/(m-1);
      long long q=(k-1)%(m-1);
      x=n-t;
      if(x%2==0) y=q+2;
      else y=m-q;
      cout<<x<<" "<<y;
  }
  ```

#### 题解3：作者：GordonLu (赞：2)
- **星级**：4星
- **关键亮点**：
  - 思路清晰，代码简洁。
  - 通过数学公式直接计算位置，避免了模拟的复杂性。
  - 代码逻辑严密，处理了大范围数据。
- **核心代码**：
  ```cpp
  if(k<n) printf("%lld %d",k+1,1);
  else {
      k-=n; printf("%lld ",n-k/(m-1));
      if(k/(m-1)&1) printf("%lld",m-k%(m-1));
      else printf("%lld",k%(m-1)+2);
  }
  ```

### 最优关键思路与技巧

1. **路径分段**：将复杂的移动路径分为两部分，分别处理，简化问题。
2. **数学计算**：通过数学公式直接计算位置，避免了模拟的复杂性，提高了效率。
3. **行的奇偶性**：利用行的奇偶性判断移动方向，简化了列的计算。

### 可拓展之处

1. **类似路径问题**：可以扩展到其他类型的路径问题，如螺旋矩阵、Z字形路径等。
2. **大范围数据处理**：在处理大范围数据时，数学推导和公式计算是关键，可以应用于其他需要高效计算的问题。

### 推荐题目

1. [P1219 八皇后问题](https://www.luogu.com.cn/problem/P1219)
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得总结

- **调试经历**：在处理大范围数据时，容易忽略边界条件，导致错误。需要仔细检查数学公式的推导和边界情况。
- **顿悟感想**：通过将复杂问题分解为简单部分，并利用数学公式直接计算，可以大大提高解题效率。

---
处理用时：52.32秒