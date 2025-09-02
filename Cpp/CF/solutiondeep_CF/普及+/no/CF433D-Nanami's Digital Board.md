# 题目信息

# Nanami's Digital Board

## 题目描述

Nanami is an expert at playing games. This day, Nanami's good friend Hajime invited her to watch a game of baseball. Unwilling as she was, she followed him to the stadium. But Nanami had no interest in the game, so she looked around to see if there was something that might interest her. That's when she saw the digital board at one end of the stadium.

The digital board is $ n $ pixels in height and $ m $ pixels in width, every pixel is either light or dark. The pixels are described by its coordinate. The $ j $ -th pixel of the $ i $ -th line is pixel $ (i,j) $ . The board displays messages by switching a combination of pixels to light, and the rest to dark. Nanami notices that the state of the pixels on the board changes from time to time. At certain times, certain pixels on the board may switch from light to dark, or from dark to light.

Nanami wonders, what is the area of the biggest light block such that a specific pixel is on its side. A light block is a sub-rectangle of the board, in which all pixels are light. Pixel $ (i,j) $ belongs to a side of sub-rectangle with $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ as its upper-left and lower-right vertex if and only if it satisfies the logical condition:

(( $ i=x_{1} $ or $ i=x_{2} $ ) and ( $ y_{1}<=j<=y_{2} $ )) or (( $ j=y_{1} $ or $ j=y_{2} $ ) and ( $ x_{1}<=i<=x_{2} $ )).Nanami has all the history of changing pixels, also she has some questions of the described type, can you answer them?

## 说明/提示

Consider the first sample.

The first query specifies pixel $ (2,2) $ , which is dark itself, so there are no valid light blocks, thus the answer is 0.

The second query specifies pixel $ (1,2) $ . The biggest light block is the block with $ (1,2) $ as its upper-left vertex and $ (1,3) $ as its lower-right vertex.

The last query specifies pixel $ (2,2) $ , which became light in the third operation. The biggest light block is the block with $ (1,2) $ as its upper-left vertex and $ (3,3) $ as its lower-right vertex.

## 样例 #1

### 输入

```
3 4 5
0 1 1 0
1 0 0 1
0 1 1 0
2 2 2
2 1 2
1 2 2
1 2 3
2 2 2
```

### 输出

```
0
2
6
```

## 样例 #2

### 输入

```
3 3 4
1 1 1
1 1 1
1 1 1
2 2 2
1 2 2
2 1 1
2 2 1
```

### 输出

```
6
3
3
```

# AI分析结果

### 题目内容
# 七海的数字板

## 题目描述
七海是游戏高手。这天，她的好朋友日向邀请她去看一场棒球比赛。尽管不情愿，她还是跟着日向去了体育场。但七海对比赛不感兴趣，于是她环顾四周，看看是否有什么能引起她的兴趣。就在这时，她看到了体育场一端的数字板。

数字板高$n$像素，宽$m$像素，每个像素要么亮要么暗。像素通过其坐标来描述。第$i$行的第$j$个像素是像素$(i, j)$。数字板通过将一组像素切换为亮，其余像素切换为暗来显示信息。七海注意到数字板上像素的状态不时变化。在某些时候，数字板上的某些像素可能会从亮变暗，或者从暗变亮。

七海想知道，包含特定像素在其边上的最大亮块的面积是多少。亮块是数字板的一个子矩形，其中所有像素都是亮的。像素$(i, j)$属于以$(x_1, y_1)$和$(x_2, y_2)$为左上角和右下角顶点的子矩形的边，当且仅当它满足逻辑条件：

(( $i = x_1$ 或 $i = x_2$ ) 且 ($y_1 \leq j \leq y_2$ )) 或 (($j = y_1$ 或 $j = y_2$ ) 且 ($x_1 \leq i \leq x_2$ ))。七海有所有像素变化的历史记录，同时她也有一些上述类型的问题，你能回答吗？

## 说明/提示
考虑第一个样例。

第一个查询指定像素$(2, 2)$，它本身是暗的，所以不存在有效的亮块，因此答案是0。

第二个查询指定像素$(1, 2)$。最大的亮块是以$(1, 2)$为左上角顶点，$(1, 3)$为右下角顶点的块。

最后一个查询指定像素$(2, 2)$，它在第三次操作中变亮了。最大的亮块是以$(1, 2)$为左上角顶点，$(3, 3)$为右下角顶点的块。

## 样例 #1
### 输入
```
3 4 5
0 1 1 0
1 0 0 1
0 1 1 0
2 2 2
2 1 2
1 2 2
1 2 3
2 2 2
```
### 输出
```
0
2
6
```

## 样例 #2
### 输入
```
3 3 4
1 1 1
1 1 1
1 1 1
2 2 2
1 2 2
2 1 1
2 2 1
```
### 输出
```
6
3
3
```

### 算法分类
无算法分类

### 题解综合分析与结论
这两道题解都围绕解决在一个$n \times m$的$0/1$矩阵中，根据给定操作（取反像素值、查询特定像素在边上的最大亮块面积）来进行计算。

**SkyRainWind题解思路**：通过维护四个方向（左、右、上、下）的拓展距离数组`ut`，对于查询操作，分别从四个方向扫描并结合最小拓展长度来计算最大亮块面积；修改操作则更新对应像素及其相邻像素的拓展距离。
**_JF_题解思路**：先预处理出行和列上每个点向不同方向连续1的个数，查询时针对每个方向分别处理，利用单调性通过二分查找来计算最大亮块面积，修改时重构受影响的行和列的信息。

两者的算法要点都在于对矩阵信息的预处理和利用，以高效处理查询和修改操作。解决难点在于如何巧妙地维护和更新数据结构，以适应动态的像素状态变化和查询需求。

### 题解列表
- **SkyRainWind题解**：
  - **星级**：4星
  - **关键亮点**：通过直接维护四个方向的拓展距离数组，在查询时全面考虑四个方向的扫描计算，逻辑较为清晰直接。
  - **个人心得**：代码有较多重复部分，复制时需仔细，否则容易出错（如作者少复制一句话调试1h+）。
  - **核心代码片段**：
```cpp
while(q --){
    int op,x,y;scanf("%d%d%d",&op,&x,&y);
    if(op == 2){
        if(a[x][y] == 0){
            puts("0");
            continue;
        }
        int ans = ut[x][y][2] + ut[x][y][3] - 1;
        
        int mn1=ut[x][y][2], mn2 = ut[x][y][3];
        for(int i=y+1;i<=y+ut[x][y][1]-1;i++){
            mn1 = min(mn1, ut[x][i][2]);
            mn2 = min(mn2, ut[x][i][3]);
            ans = max(ans, (mn1 + mn2 - 1) * (i-y+1));
        } 
        mn1=ut[x][y][2], mn2 = ut[x][y][3];
        for(int i=y-1;i>=y-ut[x][y][0]+1;i--){
            mn1 = min(mn1, ut[x][i][2]);
            mn2 = min(mn2, ut[x][i][3]);
            ans = max(ans, (mn1 + mn2 - 1) * (y-i+1));
        } 
        mn1=ut[x][y][0], mn2 = ut[x][y][1];
        ans = max(ans, mn1 + mn2 - 1);
        
        for(int i=x+1;i<=x+ut[x][y][3]-1;i++){
            mn1 = min(ut[i][y][0], mn1);
            mn2 = min(ut[i][y][1], mn2);
            ans = max(ans, (mn1 + mn2 - 1) * (i-x+1));
        } 
        mn1 = ut[x][y][0], mn2 = ut[x][y][1];
        
        for(int i=x-1;i>=x-ut[x][y][2]+1;i--){
            mn1 = min(ut[i][y][0], mn1);
            mn2 = min(ut[i][y][1], mn2);
            ans = max(ans, (mn1 + mn2 - 1) * (x-i+1));
        } 
        printf("%d\n",ans);
    }else{
        a[x][y] ^= 1;
        if(a[x][y] == 1){
            ut[x][y][1] = ut[x][y+1][1] + 1;
            ut[x][y][0] = ut[x][y-1][0] + 1;
            ut[x][y][2] = ut[x-1][y][2] + 1;
            ut[x][y][3] = ut[x+1][y][3] + 1;
        }else ut[x][y][0] = ut[x][y][1] = ut[x][y][2] = ut[x][y][3] = 0;
    
        for(int i=y-1;i>=1;i--){
            if(a[x][i] == 0)break;
            ut[x][i][1] = ut[x][i+1][1] + 1;
        }
        for(int i=y+1;i<=m;i++){
            if(a[x][i] == 0)break;
            ut[x][i][0] = ut[x][i-1][0] + 1;
        }
        for(int i=x+1;i<=n;i++){
            if(a[i][y] == 0)break;
            ut[i][y][2] = ut[i-1][y][2] + 1;
        }
        for(int i=x-1;i>=1;i--){
            if(a[i][y] == 0)break;
            ut[i][y][3] = ut[i+1][y][3] + 1;
        }
    }
}
```
  - **核心实现思想**：查询时，先初始化一个可能的最大面积`ans`，然后分别向四个方向扫描，每次更新最小拓展长度并计算面积，取最大值作为结果；修改时，根据像素值变化更新自身及相邻像素的拓展距离。
- **_JF_题解**：
  - **星级**：4星
  - **关键亮点**：利用单调性通过二分查找计算最大亮块面积，在处理查询时从不同方向分别考虑，有独特的优化思路。
  - **核心代码片段**：
```cpp
void Slove(int id){
    for(int i=id-1;i>=1;i--)	dus[i]=min(dus[i],dus[i+1]);
    for(int i=id+1;i<=tot;i++)	dus[i]=min(dus[i],dus[i-1]);
    Ans=max(Ans,dus[id]);
    for(int i=1;i<=id;i++)	Dus1[i]=dus[i];
    for(int i=tot,p=1;i>=id;i--,p++)	Dus2[p]=dus[i];
    
    int Len1=tot-id+1;
    for(int i=1;i<=id;i++){
        int pre=Dus1[i],Len=(id-i+1);
        
        int lst=lower_bound(Dus2+1,Dus2+Len1+1,pre)-Dus2;
        if(lst<=Len1)
            Len+=(Len1-lst+1)-1;
        Ans=max(Ans,pre*Len);
    }
    
    for(int i=1;i<=Len1;i++){
        int pre=Dus2[i],Len=(Len1-i+1);
        int lst=lower_bound(Dus1+1,Dus1+id+1,pre)-Dus1;
        if(lst<=id)
            Len+=(id-lst+1)-1;
        Ans=max(Ans,pre*Len);
    }
    
}
```
  - **核心实现思想**：在`Slove`函数中，先处理数组`dus`使其在`id`两侧单调不升，然后分别从左右两侧枚举最小值，通过二分查找找到另一侧满足条件的位置，计算并更新最大面积。

### 最优关键思路或技巧
- **预处理数组**：通过预处理维护每个像素在不同方向上的拓展信息，无论是维护拓展距离（SkyRainWind题解）还是连续1的个数（_JF_题解），都为后续查询和修改操作提供了便利。
- **利用单调性**：_JF_题解中利用数据的单调性，通过二分查找优化计算最大亮块面积的过程，减少了时间复杂度。

### 可拓展之处
同类型题可能涉及在动态变化的矩阵中进行各种区域查询，类似算法套路可总结为预处理关键信息（如拓展距离、连续相同元素个数等），并根据查询和修改操作的特点，合理维护和更新这些信息，利用数据特性（如单调性）优化计算过程。

### 洛谷相似题目推荐
- [P1168 中位数](https://www.luogu.com.cn/problem/P1168)：涉及对动态数据的处理和查询，与本题动态变化的矩阵及查询操作有相似之处。
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)：通过树状数组处理动态区间修改和查询问题，与本题动态修改和查询的场景类似，可锻炼相关数据结构运用能力。
- [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)：同样是在序列上进行动态查询操作，通过合理的数据结构和预处理优化查询效率，与本题思路有相通之处。

---
处理用时：85.98秒