# 题目信息

# Grid game

## 题目描述

You are given a 4x4 grid. You play a game — there is a sequence of tiles, each of them is either 2x1 or 1x2. Your task is to consequently place all tiles from the given sequence in the grid. When tile is placed, each cell which is located in fully occupied row or column is deleted (cells are deleted at the same time independently). You can place tile in the grid at any position, the only condition is that tiles (and tile parts) should not overlap. Your goal is to proceed all given figures and avoid crossing at any time.

## 说明/提示

Following image illustrates the example after placing all three tiles:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1103A/f44ced4ce1b8e75991a91740b20934be3a232e59.png) Then the first row is deleted:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1103A/e3af979e6215ad9ab1b846acdc74747882bc4def.png)

## 样例 #1

### 输入

```
010
```

### 输出

```
1 1
1 2
1 4```

# AI分析结果

### 题目内容重写
# 网格游戏

## 题目描述

你有一个4x4的网格。你玩一个游戏——有一系列的方块，每个方块要么是2x1的，要么是1x2的。你的任务是依次将给定序列中的所有方块放置在网格中。当方块被放置时，每一行或每一列如果被完全占据，则该行或列的所有单元格将被删除（单元格同时独立删除）。你可以将方块放置在网格中的任何位置，唯一条件是方块（及其部分）不能重叠。你的目标是处理所有给定的方块，并在任何时候避免重叠。

## 说明/提示

下图展示了放置所有三个方块后的示例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1103A/f44ced4ce1b8e75991a91740b20934be3a232e59.png) 然后第一行被删除：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1103A/e3af979e6215ad9ab1b846acdc74747882bc4def.png)

## 样例 #1

### 输入

```
010
```

### 输出

```
1 1
1 2
1 4
```

### 算法分类
构造

### 题解分析与结论
本题的核心在于如何构造性地放置方块，以避免重叠并利用行和列的自动删除机制。大多数题解采用了将竖直方块放在第一行，水平方块放在最后一行的策略，这样可以确保在放置过程中不会出现重叠，并且当行或列被填满时，会自动删除，从而为后续放置腾出空间。

### 高星题解推荐
1. **作者：miaokehao (5星)**
   - **关键亮点**：简洁明了地实现了将竖直方块放在第一行，水平方块放在最后一行的策略，代码简洁且高效。
   - **核心代码**：
     ```cpp
     for(res i=0;i<s.size();i++)
         if(s[i]=='0')printf("1 %d\n",x+1),x=(x+1)%4;
         else printf("4 %d\n",y+1),y=(y+2)%4;
     ```

2. **作者：Stars_visitor_tyw (4星)**
   - **关键亮点**：详细解释了为什么将竖直方块放在第一行，水平方块放在最后一行可以避免重叠，并且代码实现清晰。
   - **核心代码**：
     ```cpp
     for(int i=0;i<s.size();i++)
     {
         if(s[i]=='0')
         {
             cout<<"1 "<<x+1<<"\n";
             x=(x+1)%mod;
         }
         else
         {
             cout<<"4 "<<y+1<<"\n";
             y=(y+2)%mod;
         }
     }
     ```

3. **作者：__1d0h8dp__ (4星)**
   - **关键亮点**：通过图示详细展示了放置和删除的过程，使得策略更加直观易懂。
   - **核心代码**：
     ```cpp
     for(int i=0;i<s.length();i++){
         if(s[i]=='0'){
             cout<<"1 "<<x1;
             x1++;
             if(x1>4) x1=1;
         }
         else{
             cout<<"4 "<<x2;
             x2+=2;
             if(x2>4) x2=1;
         }
     }
     ```

### 最优关键思路或技巧
- **策略**：将竖直方块放在第一行，水平方块放在最后一行，利用行和列的自动删除机制避免重叠。
- **实现技巧**：使用模运算来循环放置方块，确保在行或列被填满后重新开始放置。

### 可拓展之处
- 类似的问题可以扩展到更大的网格或不同形状的方块，策略的核心依然是利用自动删除机制来避免重叠。
- 可以进一步优化放置顺序，以最大化利用空间或最小化删除次数。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1019 单词接龙](https://www.luogu.com.cn/problem/P1019)

---
处理用时：28.61秒