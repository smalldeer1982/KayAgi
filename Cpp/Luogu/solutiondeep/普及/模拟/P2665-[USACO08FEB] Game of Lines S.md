# 题目信息

# [USACO08FEB] Game of Lines S

## 题目背景

Farmer John 最近发明了一个游戏，来考验自命不凡的贝茜。


## 题目描述

Farmer John has challenged Bessie to the following game: FJ has a board with dots marked at N (2 ≤ N ≤ 200) distinct lattice points. Dot i has the integer coordinates Xi and Yi (-1,000 ≤ Xi ≤ 1,000; -1,000 ≤ Yi ≤ 1,000).

Bessie can score a point in the game by picking two of the dots and drawing a straight line between them; however, she is not allowed to draw a line if she has already drawn another line that is parallel to that line. Bessie would like to know her chances of winning, so she has asked you to help find the maximum score she can obtain.

游戏开始的时 候，FJ 会给贝茜一块画着 $N (2 \le N \le 200)$ 个不重合的点的木板，其中第 $i$ 个点的横、纵坐标分别为 $X_i$ 和 $Y_i (-1000 \le X_i \le 1000, -1000 \le Y_i \le 1000)$。

贝茜可以选两个点画一条过它们的直线，当且仅当平面上不存在与画出直线 平行的直线。游戏结束时贝茜的得分，就是她画出的直线的总条数。为了在游戏中胜出，贝茜找到了你，希望你帮她计算一下最大可能得分。


## 说明/提示

贝茜能画出以下 $4$ 种斜率的直线：$-1$，$0$，$\dfrac{1}{3}$ 以及 $1$。

## 样例 #1

### 输入

```
4 
-1 1 
-2 0 
0 0 
1 1```

### 输出

```
4 ```

# AI分析结果

• 综合分析与结论：
    - 思路：所有题解均围绕计算给定多个点两两连线的不同斜率数量来解决问题，因为不同斜率的直线数量即为贝茜的最大得分。
    - 算法要点：通过双重循环枚举每两个点，计算它们连线的斜率。
    - 解决难点：主要难点在于处理斜率计算时的特殊情况，即直线与坐标轴垂直（分母为0）的情况，所有题解都对此进行了特判。同时，需要对计算出的斜率进行去重，不同题解采用了不同的数据结构和方法实现去重。

    - 整体上，各题解思路清晰，但在代码可读性、优化程度上存在差异。部分题解使用了简单的数据结构如数组结合排序去重，部分使用了STL容器如map、set自动去重，后者代码通常更简洁。

• 通用建议与扩展思路：
    - 关键思路或技巧：使用STL容器（如map、set）能简化去重操作，提高代码简洁性和效率。在计算斜率时，要注意浮点数运算的精度问题以及分母为0的特殊情况处理。
    - 拓展：同类型题可涉及几何图形中直线、线段的关系判断，类似算法套路是通过计算斜率、距离等几何量，结合数据结构处理重复或特定条件的情况。
    - 洛谷相似知识点题目：
        - P1039 [NOIP2003 普及组] 侦探推理，涉及枚举和逻辑判断，类似本题枚举点对并处理特殊情况的思维方式。
        - P1164 小A点菜，同样是通过枚举组合解决问题，可类比本题枚举点对计算斜率。
        - P1909 [NOIP2016 普及组] 买铅笔，通过枚举不同购买方案并比较结果，与本题枚举点对并统计不同斜率数量思路相似。

• 个人心得摘录与总结：
    - Hiraeth：强调了斜率不存在（分母为0）情况的特判以及整型计算浮点型要乘1.0的注意点，避免因除0和数据类型转换导致错误。
    - ljc20020730：指出枚举题要认真考虑特殊情况，如本题中两点x坐标相等、y坐标相等以及两点重合的情况，虽然部分数据较水不考虑也能通过，但完善考虑能保证代码的正确性和健壮性。 

---
处理用时：21.67秒