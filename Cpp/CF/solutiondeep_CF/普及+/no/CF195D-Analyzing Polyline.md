# 题目信息

# Analyzing Polyline

## 题目描述

As Valeric and Valerko were watching one of the last Euro Championship games in a sports bar, they broke a mug. Of course, the guys paid for it but the barman said that he will let them watch football in his bar only if they help his son complete a programming task. The task goes like that.

Let's consider a set of functions of the following form:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF195D/bc3a6f827f49bee100d9da6adde48766963384ee.png) Let's define a sum of $ n $ functions $ y_{1}(x),...,y_{n}(x) $ of the given type as function $ s(x)=y_{1}(x)+...+y_{n}(x) $ for any $ x $ . It's easy to show that in this case the graph $ s(x) $ is a polyline. You are given $ n $ functions of the given type, your task is to find the number of angles that do not equal 180 degrees, in the graph $ s(x) $ , that is the sum of the given functions.Valeric and Valerko really want to watch the next Euro Championship game, so they asked you to help them.

## 样例 #1

### 输入

```
1
1 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 0
0 2
-1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
-2 -4
1 7
-5 1
```

### 输出

```
3
```

# AI分析结果

### 题目内容
#### 分析折线
#### 题目描述
瓦列里和瓦列尔科在一家体育酒吧观看欧洲杯的最后几场比赛时，打碎了一个杯子。当然，他们赔偿了杯子，但酒吧老板表示，只有他们帮助他儿子完成一道编程题，才会让他们继续在酒吧看足球。题目是这样的。

考虑一组如下形式的函数：
\[y(x)=\max(0,kx + b)\]
定义 \(n\) 个这种类型的函数 \(y_{1}(x),...,y_{n}(x)\) 的和为函数 \(s(x)=y_{1}(x)+...+y_{n}(x)\)，对于任意 \(x\) 都成立。很容易证明，在这种情况下，\(s(x)\) 的图像是一条折线。给定 \(n\) 个这种类型的函数，你的任务是找出 \(s(x)\) 的图像中角度不等于 \(180\) 度的角的数量，即给定函数之和的图像中的拐点数量。瓦列里和瓦列尔科非常想看欧洲杯的下一场比赛，所以他们请你帮忙。
#### 样例 #1
- **输入**
```
1
1 0
```
- **输出**
```
1
```
#### 样例 #2
- **输入**
```
3
1 0
0 2
-1 1
```
- **输出**
```
2
```
#### 样例 #3
- **输入**
```
3
-2 -4
1 7
-5 1
```
- **输出**
```
3
```
### 算法分类
数学
### 题解综合分析与结论
这几道题解思路基本一致，均通过分析不同函数相加后图像拐点的规律，得出拐点数目等于所有函数与 \(x\) 轴不同交点数这一关键结论。解决难点在于如何准确找出不同的交点，避免重复计算。题解主要通过使用 `map` 或 `set` 来维护交点，并采用不同方式处理数据以防止重复和精度问题。
### 通用建议与扩展思路
在处理此类涉及函数图像特征计数问题时，关键在于深入分析函数性质，找出影响结果的关键因素（如本题中的函数与 \(x\) 轴交点）。对于可能出现的精度问题和数据重复问题，要选择合适的数据结构和处理方式。同类型题通常围绕函数的组合、图像特征分析以及相关计数展开，类似算法套路包括分析函数性质、寻找关键特征点、利用数据结构去重等。
### 洛谷相似题目推荐
- [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)
- [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)
- [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516)
### 个人心得摘录与总结
renrua52希望疫情早日结束，表达个人情感，与解题思路无关。 

---
处理用时：38.40秒