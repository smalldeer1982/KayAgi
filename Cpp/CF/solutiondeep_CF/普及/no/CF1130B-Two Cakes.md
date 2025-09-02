# 题目信息

# Two Cakes

## 题目描述

Sasha and Dima want to buy two $ n $ -tier cakes. Each cake should consist of $ n $ different tiers: from the size of $ 1 $ to the size of $ n $ . Tiers should go in order from the smallest to the biggest (from top to bottom).

They live on the same street, there are $ 2 \cdot n $ houses in a row from left to right. Each house has a pastry shop where you can buy a cake tier. Unfortunately, in each pastry shop you can buy only one tier of only one specific size: in the $ i $ -th house you can buy a tier of the size $ a_i $ ( $ 1 \le a_i \le n $ ).

Since the guys carry already purchased tiers, and it is impossible to insert a new tier in the middle of the cake, they agreed to buy tiers from the smallest to the biggest. That is, each of them buys tiers in order: $ 1 $ , then $ 2 $ , then $ 3 $ and so on up to $ n $ .

Initially, Sasha and Dima are located near the first (leftmost) house. Output the minimum distance that they will have to walk in total to buy both cakes. The distance between any two neighboring houses is exactly $ 1 $ .

## 说明/提示

In the first example, the possible optimal sequence of actions is:

- Sasha buys a tier of size $ 1 $ near the $ 1 $ -st house ( $ a_1=1 $ );
- Dima goes to the house $ 2 $ ;
- Dima buys a tier of size $ 1 $ near the $ 2 $ -nd house ( $ a_2=1 $ );
- Sasha goes to the house $ 4 $ ;
- Sasha buys a tier of size $ 2 $ near the $ 4 $ -th house ( $ a_4=2 $ );
- Sasha goes to the house $ 5 $ ;
- Sasha buys a tier of size $ 3 $ near the $ 5 $ -th house ( $ a_5=3 $ );
- Dima goes to the house $ 3 $ ;
- Dima buys a tier of size $ 2 $ near the $ 3 $ -rd house ( $ a_3=2 $ );
- Dima goes to the house $ 6 $ ;
- Dima buys a tier of size $ 3 $ near the $ 6 $ -th house ( $ a_6=3 $ ).

So, Sasha goes the distance $ 3+1=4 $ , and Dima goes the distance $ 1+1+3=5 $ . In total, they cover a distance of $ 4+5=9 $ . You can make sure that with any other sequence of actions they will walk no less distance.

## 样例 #1

### 输入

```
3
1 1 2 2 3 3
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2
2 1 1 2
```

### 输出

```
5
```

## 样例 #3

### 输入

```
4
4 1 3 2 2 3 1 4
```

### 输出

```
17
```

# AI分析结果

### 题目内容重写
# 两个蛋糕

## 题目描述

Sasha和Dima想要购买两个$n$层的蛋糕。每个蛋糕应该由$n$个不同的层组成：从大小为$1$到大小为$n$。层必须按从小到大的顺序排列（从顶部到底部）。

他们住在同一条街上，街上有$2 \cdot n$栋房子，从左到右排列。每栋房子里有一个糕点店，只能购买一个特定大小的蛋糕层：在第$i$栋房子里，你可以购买大小为$a_i$的层（$1 \le a_i \le n$）。

由于他们已经在携带已经购买的层，并且无法在蛋糕中间插入新的层，他们同意按从小到大的顺序购买层。也就是说，他们每个人按顺序购买层：$1$，然后$2$，然后$3$，依此类推，直到$n$。

最初，Sasha和Dima位于第一栋（最左边的）房子旁边。输出他们购买两个蛋糕所需走的最小总距离。任何两栋相邻房子之间的距离正好是$1$。

## 说明/提示

在第一个例子中，可能的优化行动序列是：

- Sasha在第一栋房子附近购买大小为$1$的层（$a_1=1$）；
- Dima走到第二栋房子；
- Dima在第二栋房子附近购买大小为$1$的层（$a_2=1$）；
- Sasha走到第四栋房子；
- Sasha在第四栋房子附近购买大小为$2$的层（$a_4=2$）；
- Sasha走到第五栋房子；
- Sasha在第五栋房子附近购买大小为$3$的层（$a_5=3$）；
- Dima走到第三栋房子；
- Dima在第三栋房子附近购买大小为$2$的层（$a_3=2$）；
- Dima走到第六栋房子；
- Dima在第六栋房子附近购买大小为$3$的层（$a_6=3$）。

因此，Sasha走了$3+1=4$的距离，Dima走了$1+1+3=5$的距离。总共，他们走了$4+5=9$的距离。你可以确认，任何其他行动序列都不会让他们走更少的距离。

## 样例 #1

### 输入

```
3
1 1 2 2 3 3
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2
2 1 1 2
```

### 输出

```
5
```

## 样例 #3

### 输入

```
4
4 1 3 2 2 3 1 4
```

### 输出

```
17
```

### 算法分类
贪心

### 题解分析与结论
本题的核心是贪心算法，通过每次选择最优的路径来最小化总距离。所有题解都采用了贪心的思路，即在每一步选择中，选择使得当前步数最小的路径。具体来说，每次选择两种可能的路径中总距离较小的那一种。

### 评分较高的题解
1. **作者：shiziyu111 (4星)**
   - **关键亮点**：通过记录每个蛋糕层的位置，并在每一步选择最优路径，代码简洁且易于理解。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++)
     {
         if(abs(home1[i]-ap)+abs(home2[i]-bp)<=abs(home1[i]-bp)+abs(home2[i]-ap))
         {
             ans+=abs(home1[i]-ap)+abs(home2[i]-bp);
             ap=home1[i];
             bp=home2[i];
         }
         else
         {
             ans+=abs(home1[i]-bp)+abs(home2[i]-ap);
             ap=home2[i];
             bp=home1[i];
         }
     }
     ```

2. **作者：AnicoderAndy (4星)**
   - **关键亮点**：通过排序和结构体记录位置，使得每一步的选择更加清晰，代码结构良好。
   - **核心代码**：
     ```cpp
     for (int i = 2; i <= n; i++) {
         int p = a[i * 2 - 1].cur, q = a[i * 2].cur;
         int k = a[i * 2 - 3].cur, l = a[i * 2 - 2].cur;
         ans += min(abs(p - k) + abs(q - l), abs(p - l) + abs(q - k));
     }
     ```

3. **作者：jiangjiangQwQ (4星)**
   - **关键亮点**：直接使用数组记录位置，并在每一步选择最优路径，代码简洁且高效。
   - **核心代码**：
     ```cpp
     For(i,2,n){
         int x=abs(ind[i-1][0]-ind[i][0])+abs(ind[i-1][1]-ind[i][1]);
         int y=abs(ind[i-1][0]-ind[i][1])+abs(ind[i-1][1]-ind[i][0]);
         sum+=min(x,y);
     }
     ```

### 最优关键思路或技巧
- **贪心选择**：在每一步选择中，选择使得当前步数最小的路径。
- **位置记录**：通过数组或结构体记录每个蛋糕层的位置，便于后续计算距离。
- **排序优化**：通过排序使得每一步的选择更加清晰，减少计算复杂度。

### 可拓展之处
- **类似问题**：可以扩展到多个购买者或更多层的蛋糕问题，依然可以采用贪心算法。
- **路径优化**：可以结合图论中的最短路径算法，进一步优化路径选择。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

### 个人心得摘录
- **调试经历**：在调试过程中，发现初始位置的处理非常重要，需要确保初始位置的正确性。
- **踩坑教训**：在记录位置时，确保每个蛋糕层的位置记录正确，避免重复或遗漏。
- **顿悟感想**：通过贪心算法，可以有效地减少计算量，使得问题更加简单明了。

---
处理用时：43.46秒