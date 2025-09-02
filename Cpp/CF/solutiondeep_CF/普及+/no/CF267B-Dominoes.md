# 题目信息

# Dominoes

## 题目描述

You have a set of dominoes. Each domino is a rectangular tile with a line dividing its face into two square ends. Can you put all dominoes in a line one by one from left to right so that any two dominoes touched with the sides that had the same number of points? You can rotate the dominoes, changing the left and the right side (domino "1-4" turns into "4-1").

## 样例 #1

### 输入

```
5
1 2
2 4
2 4
6 4
2 1
```

### 输出

```
2 -
1 -
5 -
3 +
4 -
```

# AI分析结果

### 题目内容
# 多米诺骨牌

## 题目描述
你有一组多米诺骨牌。每张多米诺骨牌都是一个矩形瓷砖，其表面有一条线将其分成两个正方形端点。你能否将所有多米诺骨牌从左到右依次排成一行，使得任意两张相邻的多米诺骨牌接触的两边点数相同？你可以旋转多米诺骨牌，改变其左右两边（例如“1 - 4”的多米诺骨牌可变为“4 - 1”）。

## 样例 #1
### 输入
```
5
1 2
2 4
2 4
6 4
2 1
```
### 输出
```
2 -
1 -
5 -
3 +
4 -
```
• 算法分类：图论（可将多米诺骨牌的点数视为图的节点，多米诺骨牌视为边，问题转化为在图中寻找欧拉路径或回路）
• 综合分析与结论：由于暂无题解，无法进行题解间的对比分析。通用建议是理解将实际问题建模为图论问题的思路，把多米诺骨牌两端的数字看作图的顶点，每张多米诺骨牌看作连接对应顶点的边。扩展思路上，可以考虑如何判断图是否存在欧拉路径或回路，这涉及到顶点度数等相关知识。
• 暂无4星及以上题解。
• 洛谷相似题目推荐：
  - P2731 [USACO3.3]骑马修栅栏 Riding the Fences，该题同样是关于图中欧拉路径的求解。
  - P1341 无序字母对，通过构建图并寻找欧拉路径来解决问题。
  - P2746 [USACO5.3]校园网 Network of Schools，与图的连通性及路径相关，可锻炼图论相关思维。 

---
处理用时：16.75秒