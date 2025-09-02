# 题目信息

# Bouncing Ball

## 题目描述

You're creating a game level for some mobile game. The level should contain some number of cells aligned in a row from left to right and numbered with consecutive integers starting from $ 1 $ , and in each cell you can either put a platform or leave it empty.

In order to pass a level, a player must throw a ball from the left so that it first lands on a platform in the cell $ p $ , then bounces off it, then bounces off a platform in the cell $ (p + k) $ , then a platform in the cell $ (p + 2k) $ , and so on every $ k $ -th platform until it goes farther than the last cell. If any of these cells has no platform, you can't pass the level with these $ p $ and $ k $ .

You already have some level pattern $ a_1 $ , $ a_2 $ , $ a_3 $ , ..., $ a_n $ , where $ a_i = 0 $ means there is no platform in the cell $ i $ , and $ a_i = 1 $ means there is one. You want to modify it so that the level can be passed with given $ p $ and $ k $ . In $ x $ seconds you can add a platform in some empty cell. In $ y $ seconds you can remove the first cell completely, reducing the number of cells by one, and renumerating the other cells keeping their order. You can't do any other operation. You can not reduce the number of cells to less than $ p $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1415C/db37e109bcbb2fc66573faa03cd327ce59fe9d9d.png)Illustration for the third example test case. Crosses mark deleted cells. Blue platform is the newly added.What is the minimum number of seconds you need to make this level passable with given $ p $ and $ k $ ?

## 说明/提示

In the first test case it's best to just remove the first cell, after that all required platforms are in their places: 0101010101. The stroked out digit is removed, the bold ones are where platforms should be located. The time required is $ y = 2 $ .

In the second test case it's best to add a platform to both cells $ 4 $ and $ 5 $ : 00000 $ \to $ 00011. The time required is $ x \cdot 2 = 4 $ .

In the third test case it's best to to remove the first cell twice and then add a platform to the cell which was initially $ 10 $ -th: 10110011000 $ \to $ 10110011010. The time required is $ y \cdot 2 + x = 10 $ .

## 样例 #1

### 输入

```
3
10 3 2
0101010101
2 2
5 4 1
00000
2 10
11 2 3
10110011000
4 3```

### 输出

```
2
4
10```

# AI分析结果

【题目内容】
# 弹跳球

## 题目描述

你正在为某个手机游戏创建一个关卡。关卡应该包含一些按从左到右排列的单元格，编号从1开始连续编号。在每个单元格中，你可以放置一个平台或留空。

为了通过关卡，玩家必须从左向右抛出一个球，使其首先落在单元格$p$的平台上，然后弹起，接着弹到单元格$(p + k)$的平台上，再弹到单元格$(p + 2k)$的平台上，依此类推，每隔$k$个平台弹一次，直到球弹到最后一个单元格之外。如果这些单元格中的任何一个没有平台，则无法通过这些$p$和$k$通过关卡。

你已经有了一个关卡模式$a_1, a_2, a_3, ..., a_n$，其中$a_i = 0$表示单元格$i$中没有平台，$a_i = 1$表示单元格$i$中有平台。你希望修改它，使得关卡可以通过给定的$p$和$k$。在$x$秒内，你可以在某个空单元格中添加一个平台。在$y$秒内，你可以完全删除第一个单元格，减少单元格的数量，并重新编号其他单元格，保持它们的顺序。你不能进行其他操作。你不能将单元格数量减少到少于$p$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1415C/db37e109bcbb2fc66573faa03cd327ce59fe9d9d.png)第三个示例测试用例的图示。叉号标记删除的单元格。蓝色平台是新添加的。要使关卡通过给定的$p$和$k$，最少需要多少秒？

## 说明/提示

在第一个测试用例中，最好直接删除第一个单元格，之后所有需要的平台都在它们的位置上：0101010101。删除的数字被划掉，加粗的数字是平台应该放置的位置。所需时间为$y = 2$。

在第二个测试用例中，最好在单元格$4$和$5$中添加平台：00000 $→$ 00011。所需时间为$x \cdot 2 = 4$。

在第三个测试用例中，最好删除第一个单元格两次，然后在最初的第10个单元格中添加一个平台：10110011000 $→$ 10110011010。所需时间为$y \cdot 2 + x = 10$。

## 样例 #1

### 输入

```
3
10 3 2
0101010101
2 2
5 4 1
00000
2 10
11 2 3
10110011000
4 3```

### 输出

```
2
4
10```

【算法分类】动态规划

【题解分析与结论】
本题的核心在于如何通过动态规划或枚举的方式，找到最小的时间成本来修改关卡，使得球能够按照给定的$p$和$k$弹跳通过。题解中主要采用了动态规划和枚举的思路，通过预处理和状态转移方程来优化计算。

【所选题解】
1. **作者：wawatime1 (赞：2)**  
   - **星级：4**  
   - **关键亮点**：通过动态规划的思路，详细推导了状态转移方程，考虑了删除第一个元素和添加平台的操作，逻辑清晰，代码实现简洁。  
   - **核心代码**：
     ```cpp
     dp[i] = min(dp[i - 1] + (a[i] == 0 ? x : 0), dp[i - 1] + y);
     ```
   - **个人心得**：作者在推导状态转移方程时，详细考虑了不同情况下的操作，使得代码逻辑更加清晰。

2. **作者：Schwarzkopf_Henkal (赞：1)**  
   - **星级：4**  
   - **关键亮点**：通过预处理和分类处理，优化了暴力枚举的复杂度，使得整体时间复杂度降低到$O(n)$，代码实现较为高效。  
   - **核心代码**：
     ```cpp
     for(int i=p;i<=n;i++){
         if(!mk[i]){
             int j=0;
             while(K*(j+1)+i<=n)
                 j++;
             while(j>=0){
                 mk[K*j+i]=1;
                 if(c[K*j+i]==0)
                     res[K*j+i]++;
                 if(j)
                     res[K*(j-1)+i]=res[K*j+i];
                 j--;
             }
         }
         ans=min(ans,(i-p)*y+res[i]*x);
     }
     ```
   - **个人心得**：作者通过预处理和分类处理，减少了重复计算，使得代码更加高效。

3. **作者：TEoS (赞：1)**  
   - **星级：4**  
   - **关键亮点**：通过枚举删除的元素数量，结合预处理和分类处理，优化了计算过程，代码实现较为简洁。  
   - **核心代码**：
     ```cpp
     for(int i=p-1;i<n;i++)
         ans=min(ans,((int)ceil((double)(n-i)/k)-cnt[(i-p+1)%k]+ncnt[(i-p+1)%k])*x+(i-p+1)*y),ncnt[(i-p+1)%k]+=s[i]-'0';
     ```
   - **个人心得**：作者通过枚举删除的元素数量，结合预处理和分类处理，使得代码逻辑更加清晰。

【最优关键思路或技巧】
1. **动态规划**：通过状态转移方程，考虑删除第一个元素和添加平台的操作，找到最小的时间成本。
2. **预处理与分类处理**：通过预处理和分类处理，减少重复计算，优化时间复杂度。
3. **枚举与优化**：通过枚举删除的元素数量，结合预处理和分类处理，优化计算过程。

【可拓展之处】
类似的问题可以通过动态规划、预处理和分类处理来优化计算过程，特别是在需要枚举和状态转移的情况下。

【推荐题目】
1. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)

---
处理用时：37.53秒