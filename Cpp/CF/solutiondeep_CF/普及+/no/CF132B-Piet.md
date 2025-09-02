# 题目信息

# Piet

## 题目描述

Piet is one of the most known visual esoteric programming languages. The programs in Piet are constructed from colorful blocks of pixels and interpreted using pretty complicated rules. In this problem we will use a subset of Piet language with simplified rules.

The program will be a rectangular image consisting of colored and black pixels. The color of each pixel will be given by an integer number between 0 and 9, inclusive, with 0 denoting black. A block of pixels is defined as a rectangle of pixels of the same color (not black). It is guaranteed that all connected groups of colored pixels of the same color will form rectangular blocks. Groups of black pixels can form arbitrary shapes.

The program is interpreted using movement of instruction pointer (IP) which consists of three parts:

- current block pointer (BP); note that there is no concept of current pixel within the block;
- direction pointer (DP) which can point left, right, up or down;
- block chooser (CP) which can point to the left or to the right from the direction given by DP; in absolute values CP can differ from DP by 90 degrees counterclockwise or clockwise, respectively.

Initially BP points to the block which contains the top-left corner of the program, DP points to the right, and CP points to the left (see the orange square on the image below).

One step of program interpretation changes the state of IP in a following way. The interpreter finds the furthest edge of the current color block in the direction of the DP. From all pixels that form this edge, the interpreter selects the furthest one in the direction of CP. After this, BP attempts to move from this pixel into the next one in the direction of DP. If the next pixel belongs to a colored block, this block becomes the current one, and two other parts of IP stay the same. It the next pixel is black or outside of the program, BP stays the same but two other parts of IP change. If CP was pointing to the left, now it points to the right, and DP stays the same. If CP was pointing to the right, now it points to the left, and DP is rotated 90 degrees clockwise.

This way BP will never point to a black block (it is guaranteed that top-left pixel of the program will not be black).

You are given a Piet program. You have to figure out which block of the program will be current after $ n $ steps.

## 说明/提示

In the first example IP changes in the following way. After step 1 block 2 becomes current one and stays it after two more steps. After step 4 BP moves to block 3, after step 7 — to block 4, and finally after step 10 BP returns to block 1.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF132B/ce209b4d4ed0181e1c11bf614ed9fbec2a05e0d7.png)The sequence of states of IP is shown on the image: the arrows are traversed clockwise, the main arrow shows direction of DP, the side one — the direction of CP.

## 样例 #1

### 输入

```
2 10
12
43
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 12
1423
6624
6625
```

### 输出

```
6
```

## 样例 #3

### 输入

```
5 9
10345
23456
34567
45678
56789
```

### 输出

```
5
```

# AI分析结果

### 题目内容
# Piet

## 题目描述
Piet是最著名的可视化深奥编程语言之一。Piet中的程序由彩色像素块构成，并使用相当复杂的规则进行解释。在本题中，我们将使用Piet语言的一个子集，并采用简化规则。

程序是一个由彩色和黑色像素组成的矩形图像。每个像素的颜色由一个介于0到9（含）之间的整数表示，其中0表示黑色。像素块定义为具有相同颜色（非黑色）的像素矩形。保证所有相同颜色的相连彩色像素组将形成矩形块。黑色像素组可以形成任意形状。

程序使用指令指针（IP）的移动来解释，IP由三部分组成：
- 当前块指针（BP）；请注意，块内不存在当前像素的概念；
- 方向指针（DP），可以指向左、右、上或下；
- 块选择器（CP），可以指向DP给定方向的左侧或右侧；绝对值上，CP分别可以与DP逆时针或顺时针相差90度。

最初，BP指向包含程序左上角的块，DP指向右侧，CP指向左侧（见下图中的橙色方块）。

程序解释的一步按以下方式改变IP的状态。解释器找到当前颜色块在DP方向上最远的边缘。从构成该边缘的所有像素中，解释器选择在CP方向上最远的像素。之后，BP尝试从该像素沿DP方向移动到下一个像素。如果下一个像素属于彩色块，则该块成为当前块，IP的另外两部分保持不变。如果下一个像素是黑色或在程序外部，BP保持不变，但IP的另外两部分改变。如果CP原本指向左侧，现在指向右侧，DP保持不变。如果CP原本指向右侧，现在指向左侧，DP顺时针旋转90度。

这样，BP永远不会指向黑色块（保证程序的左上角像素不是黑色）。

给定一个Piet程序，你必须找出经过n步后哪个程序块将成为当前块。

## 说明/提示
在第一个示例中，IP的变化如下。在第1步之后，第2块成为当前块，并在接下来的两步中保持不变。在第4步之后，BP移动到第3块，在第7步之后移动到第4块，最后在第10步之后，BP返回到第1块。

![示例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF132B/ce209b4d4ed0181e1c11bf614ed9fbec2a05e0d7.png)

IP状态的顺序如图所示：箭头按顺时针方向遍历，主箭头表示DP的方向，侧箭头表示CP的方向。

## 样例 #1
### 输入
```
2 10
12
43
```
### 输出
```
1
```

## 样例 #2
### 输入
```
3 12
1423
6624
6625
```
### 输出
```
6
```

## 样例 #3
### 输入
```
5 9
10345
23456
34567
45678
56789
```
### 输出
```
5
```
### 算法分类
模拟
### 题解综合分析与结论
当前仅提供一篇题解，整体思路是按照题目给定的规则对指令指针（IP）的移动进行模拟。算法要点在于准确实现IP各部分（BP、DP、CP）状态改变的逻辑，通过数组记录地图信息，结构体存储IP状态，并在结构体的next函数中实现每一步IP状态的更新。解决难点在于理解并正确实现题目中复杂的IP移动规则，包括如何找到当前块在DP方向上最远边缘的像素，以及如何根据CP方向选择像素并更新IP状态。代码通过设置check函数判断是否越界或颜色变化，利用vis数组记录IP状态避免重复计算。

### 题解
- **星级**：3星
- **关键亮点**：按照题目规则详细模拟IP移动过程，通过结构体封装IP状态及相关操作，利用vis数组优化循环计算。
- **重点代码核心实现思想**：
  - `next`函数实现IP状态的更新，通过循环找到当前块在DP方向上最远边缘的像素，再根据CP方向选择像素，然后根据下一个像素情况更新BP、DP和CP。
  - `check`函数用于判断当前尝试移动的位置是否越界或颜色与当前块不一致。
  - `visId`和`setVis`函数用于操作vis数组，记录和判断IP状态是否重复。
- **核心代码片段**：
```cpp
struct Item{
    int dp,cp,r,c,tr,tc;
    void next(){
        while(1){
            tr=r+dir[dp][0];
            tc=c+dir[dp][1];
            if(check()) break;
            r=tr;c=tc;
            }
            int t=dp;
            dp=cp==0?(dp+3)%4:(dp+1)%4;
            while(1){
                tr=r+dir[dp][0];
                tc=c+dir[dp][1];
                if(check()) break;
                r=tr;c=tc;
            }
            dp=t;
            tr=r+dir[dp][0];
            tc=c+dir[dp][1];
            if(tr<0||tr>=m||tc<0||tc>=l||map[tr][tc]==0){
                if(cp==0) cp=1;
                else{cp=0;dp=(dp+1)%4;}
            }
            else{r=tr;c=tc;}
        }
    bool check(){
        return(tr<0||tr>=m||tc<0||tc>=l||map[tr][tc]!=map[r][c]);
    }
    int visId(){
        return vis[r][c][dp][cp];
    }
    void setVis(int id){
        vis[r][c][dp][cp]=id;
    }
};
```
### 通用建议与扩展思路
对于此类模拟题，关键在于深入理解题目规则，并将其清晰地转化为代码逻辑。在实现过程中，可通过模块化代码，如将复杂规则封装成函数，提高代码可读性和可维护性。类似题目通常会给定复杂的操作规则，需要耐心梳理，逐步实现。可拓展思路为考虑更复杂的图形结构或移动规则，如在不同形状的地图中进行移动，或增加更多影响移动的条件等。

### 洛谷相似题目推荐
- P1032 [NOIP2002 普及组] 字串变换：涉及字符串变换规则的模拟。
- P1046 [NOIP2005 普及组] 陶陶摘苹果：简单的条件模拟问题。
- P1089 [NOIP2004 提高组] 津津的储蓄计划：模拟日常生活中的储蓄计划。 

---
处理用时：65.69秒