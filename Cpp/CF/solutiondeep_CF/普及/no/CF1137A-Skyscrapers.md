# 题目信息

# Skyscrapers

## 题目描述

Dora loves adventures quite a lot. During some journey she encountered an amazing city, which is formed by $ n $ streets along the Eastern direction and $ m $ streets across the Southern direction. Naturally, this city has $ nm $ intersections. At any intersection of $ i $ -th Eastern street and $ j $ -th Southern street there is a monumental skyscraper. Dora instantly became curious and decided to explore the heights of the city buildings.

When Dora passes through the intersection of the $ i $ -th Eastern and $ j $ -th Southern street she examines those two streets. After Dora learns the heights of all the skyscrapers on those two streets she wonders: how one should reassign heights to the skyscrapers on those two streets, so that the maximum height would be as small as possible and the result of comparing the heights of any two skyscrapers on one street wouldn't change.

Formally, on every of $ nm $ intersections Dora solves an independent problem. She sees $ n + m - 1 $ skyscrapers and for each of them she knows its real height. Moreover, any two heights can be compared to get a result "greater", "smaller" or "equal". Now Dora wants to select some integer $ x $ and assign every skyscraper a height from $ 1 $ to $ x $ . When assigning heights, Dora wants to preserve the relative order of the skyscrapers in both streets. That is, the result of any comparison of heights of two skyscrapers in the current Eastern street shouldn't change and the result of any comparison of heights of two skyscrapers in current Southern street shouldn't change as well. Note that skyscrapers located on the Southern street are not compared with skyscrapers located on the Eastern street only. However, the skyscraper located at the streets intersection can be compared with both Southern and Eastern skyscrapers. For every intersection Dora wants to independently calculate the minimum possible $ x $ .

For example, if the intersection and the two streets corresponding to it look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137A/b8843ce623a50ba6456e010cf2c98b56b8233e32.png)Then it is optimal to replace the heights of the skyscrapers as follows (note that all comparisons "less", "equal", "greater" inside the Eastern street and inside the Southern street are preserved)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137A/39639df2ab400935251b9673b829739a400357e3.png)The largest used number is $ 5 $ , hence the answer for this intersection would be $ 5 $ .

Help Dora to compute the answers for each intersection.

## 说明/提示

In the first example, it's not possible to decrease the maximum used height for the problem at any intersection, hence we don't have to change any heights.

In the second example, the answers are as follows:

- For the intersection of the first line and the first column ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137A/bc671d6177e8cc9f707791f4138061e48affa407.png)
- For the intersection of the first line and the second column ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137A/d2849b7fe606944f0348e44d9e4591b7a87d7ec6.png)
- For the intersection of the second line and the first column ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137A/75a5e58bc106cd0d570dac89dc650cfe52c62ac2.png)
- For the intersection of the second line and the second column ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1137A/d38748916182cc695792c65c0945a1b43c6a19ac.png)

## 样例 #1

### 输入

```
2 3
1 2 1
2 1 2
```

### 输出

```
2 2 2 
2 2 2 
```

## 样例 #2

### 输入

```
2 2
1 2
3 4
```

### 输出

```
2 3 
3 2 
```

# AI分析结果

### 题目内容重写
Dora非常喜欢冒险。在一次旅程中，她遇到了一个令人惊叹的城市，这个城市由$n$条东西方向的街道和$m$条南北方向的街道组成。自然地，这个城市有$nm$个交叉路口。在每个交叉路口，即第$i$条东西方向的街道和第$j$条南北方向的街道的交汇处，有一座摩天大楼。Dora立刻产生了好奇心，决定探索这些城市建筑的高度。

当Dora经过第$i$条东西方向的街道和第$j$条南北方向的街道的交汇处时，她会检查这两条街道。在Dora了解到这两条街道上所有摩天大楼的高度后，她想知道：如何重新分配这两条街道上摩天大楼的高度，使得最大高度尽可能小，并且任何两座摩天大楼在同一街道上的高度比较结果不会改变。

形式上，在每个$nm$个交叉路口，Dora都独立解决一个问题。她看到$n + m - 1$座摩天大楼，并且知道它们的实际高度。此外，任何两个高度都可以比较，结果是“大于”、“小于”或“等于”。现在Dora希望选择一个整数$x$，并将每座摩天大楼的高度分配为$1$到$x$之间的整数。在分配高度时，Dora希望保留两条街道上摩天大楼的相对顺序。也就是说，当前东西方向的街道上任何两座摩天大楼的高度比较结果不应改变，当前南北方向的街道上任何两座摩天大楼的高度比较结果也不应改变。注意，位于南北方向的街道上的摩天大楼不与位于东西方向的街道上的摩天大楼进行比较。然而，位于街道交叉口的摩天大楼可以与东西方向和南北方向的摩天大楼进行比较。对于每个交叉路口，Dora希望独立计算出最小的可能$x$。

### 算法分类
离散化

### 题解分析与结论
题目要求在每个交叉路口，重新分配摩天大楼的高度，使得最大高度尽可能小，并且保留相对顺序。所有题解都采用了离散化的方法，通过对每行和每列进行排序和去重，然后使用二分查找来确定每个元素在行和列中的位置，最终计算出所需的最小$x$。

### 所选高分题解
#### 题解1：CE_Prince (5星)
**关键亮点**：
- 使用了离散化和二分查找，思路清晰，代码简洁。
- 通过`unique`函数去重，减少了重复计算，提高了效率。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        xa=lower_bound(a[i],a[i]+va[i],x[i][j])-a[i];
        ya=lower_bound(b[j],b[j]+vb[j],x[i][j])-b[j];
        int xb=va[i]-xa;
        int yb=vb[j]-ya;
        printf("%d ",max(xa,ya)+max(xb,yb));
    }
    cout<<endl;
}
```

#### 题解2：OIerJiang_1017 (4星)
**关键亮点**：
- 详细解释了离散化的概念，帮助理解算法的背景。
- 代码结构清晰，注释详细，便于理解。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        xa=lower_bound(a[i],a[i]+va[i],x[i][j])-a[i];
        ya=lower_bound(b[j],b[j]+vb[j],x[i][j])-b[j];
        int xb=va[i]-xa, yb=vb[j]-ya;
        printf("%d ",max(xa,ya)+max(xb,yb));
    }
    printf("\n");
}
```

#### 题解3：Zechariah (4星)
**关键亮点**：
- 使用了贪心思想，结合离散化和二分查找，优化了计算过程。
- 代码简洁，效率高。

**核心代码**：
```cpp
for(rg int i=1;i<=n;++i){
    for(rg int j=1;j<=m;++j){
        rg int x=lower_bound(a[i]+1,a[i]+*a[i]+1,ans[i][j])-a[i]-1;
        rg int y=lower_bound(a[j+n]+1,a[j+n]+*a[j+n]+1,ans[i][j])-a[j+n]-1;
        fast_IO::write(fast_IO::max(x,y)+fast_IO::max(*a[i]-x,*a[j+n]-y)); putchar(' ');
    }
    putchar('\n');
}
```

### 最优关键思路
1. **离散化**：通过对每行和每列进行排序和去重，将原始数据映射到有限的空间中，减少计算量。
2. **二分查找**：快速确定每个元素在行和列中的位置，计算比它小和比它大的元素数量。
3. **贪心思想**：在保证相对顺序的前提下，尽可能减少最大高度。

### 可拓展之处
- 类似问题可以扩展到多维数组或更复杂的网格结构中。
- 可以结合其他算法如动态规划或图论，解决更复杂的约束条件。

### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)

### 个人心得
- 离散化在处理大规模数据时非常有效，能够显著减少计算量。
- 二分查找在有序数据中查找元素的位置非常高效，结合离散化可以解决很多排序相关的问题。

---
处理用时：37.45秒