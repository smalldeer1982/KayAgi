# 题目信息

# [CCC 2023 J5] CCC Word Hunt

## 题目描述

In the CCC Word Hunt, words are hidden in a grid of letters. The letters of a hidden word always appear in order on horizontal, vertical, or diagonal line segments in one of two ways.One way is for the letters of a word to appear on one line segment. The other way is for the letters of a word to appear on one line segment up to some letter and then on a second line segment that forms a right angle at this letter.

Given a grid of letters and a single word to search for, your job is to determine the number of times that particular word is hidden in the grid.

## 说明/提示

**本题采用捆绑测试**。

- Subtask $1$（$2$ points）：隐藏字符串一定在一条水平线段上。
- Subtask $2$（$2$ points）：隐藏字符串一定在一个水平或垂直线段上。
- Subtask $3$（$2$ points）：隐藏字符串一定在一个水平、垂直或对角线线段上。
- Subtask $4$（$9$ points）：隐藏字符串一定在一个线段或两个互相垂直的线段上。

样例 $1$ 图解：

![](https://cdn.luogu.com.cn/upload/image_hosting/wqo2un8k.png)

样例 $2$ 图解：

![](https://cdn.luogu.com.cn/upload/image_hosting/v082p2qr.png)

## 样例 #1

### 输入

```
MENU
5
7
F T R U B L K
P M N A X C U
A E R C N E O
M N E U A R M
M U N E M N S```

### 输出

```
3```

## 样例 #2

### 输入

```
NATURE
6
9
N A T S F E G Q N
S A I B M R H F A
C F T J C U C L T
K B H U P T A N U
D P R R R J D I R
I E E K M E G B E```

### 输出

```
4```

# AI分析结果



**算法分类**  
深度优先搜索 DFS

**综合分析与结论**  
本题需要处理多方向搜索及一次90度转弯的情况。各题解均采用DFS，但在方向管理、转弯处理上存在差异。核心难点在于有效遍历所有可能路径，避免重复计数，并正确处理方向变换。最优思路是分方向处理直行与转弯，使用方向数组统一管理移动，并确保转弯仅在非首字符后进行。

**高星题解推荐**  
1. **Lemonlwl（4星）**  
   **关键亮点**：分三类DFS处理（水平/垂直、对角线、转弯），方向转换逻辑清晰，通过两个方向数组分别管理，确保覆盖所有可能性。  
   **代码核心**：  
   ```cpp
   void dfs1(int x,int y,int d,int dire) { //水平/垂直方向
       ... //沿原方向继续搜索
       // 计算左右转弯后的新方向，调用dfs3处理
   }
   void dfs2(int x,int y,int d,int dire) { //对角线方向
       ... //类似dfs1处理对角转弯
   }
   void dfs3(...) { //处理转弯后的路径
       ... //沿新方向继续搜索
   }
   ```

2. **Jorisy（4星）**  
   **关键亮点**：将方向分为水平和垂直、对角线两类，通过方向数组统一处理，转弯时使用模运算调整方向，代码简洁高效。  
   **核心实现**：  
   ```cpp
   void dfs(...) { //处理水平/垂直
       int vx=x+X[hd], vy=y+Y[hd]; //原方向
       if(合法) dfs(vx,vy,...); 
       // 左右转弯：(hd+1)%4和(hd+3)%4
   }
   void dfs2(...) { //处理对角线
       int vx=x+X2[hd], vy=y+Y2[hd]; 
       ... //类似处理转弯
   }
   ```

**最优技巧总结**  
- **方向数组**：定义dx/dy数组存储8个方向移动增量，统一处理所有可能路径。  
- **转弯标记**：使用bool参数记录是否已转弯，确保仅转一次。  
- **方向转换**：通过模运算计算转弯后的方向（如(dire+1)%4顺时针转90度）。  

**同类题目推荐**  
1. [P1101 单词方阵](https://www.luogu.com.cn/problem/P1101)  
2. [P1432 倒水问题](https://www.luogu.com.cn/problem/P1432)（状态转换搜索）  
3. [P1131 时态同步](https://www.luogu.com.cn/problem/P1131)（树形DFS+路径调整）

---
处理用时：39.92秒