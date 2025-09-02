# 题目信息

# Dice Tower

## 题目描述

A dice is a cube, its faces contain distinct integers from 1 to 6 as black points. The sum of numbers at the opposite dice faces always equals 7. Please note that there are only two dice (these dices are mirror of each other) that satisfy the given constraints (both of them are shown on the picture on the left).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF225A/85f2da947143b29924bb6531722e86105dbf28c1.png)Alice and Bob play dice. Alice has built a tower from $ n $ dice. We know that in this tower the adjacent dice contact with faces with distinct numbers. Bob wants to uniquely identify the numbers written on the faces of all dice, from which the tower is built. Unfortunately, Bob is looking at the tower from the face, and so he does not see all the numbers on the faces. Bob sees the number on the top of the tower and the numbers on the two adjacent sides (on the right side of the picture shown what Bob sees).

Help Bob, tell whether it is possible to uniquely identify the numbers on the faces of all the dice in the tower, or not.

## 样例 #1

### 输入

```
3
6
3 2
5 4
2 4
```

### 输出

```
YES```

## 样例 #2

### 输入

```
3
3
2 6
4 1
5 3
```

### 输出

```
NO```

# AI分析结果

### 题目内容
# 骰子塔

## 题目描述
骰子是一个立方体，其面上标有从1到6的不同整数作为黑点。骰子相对面的数字之和始终等于7。请注意，只有两种骰子（这两种骰子互为镜像）满足给定的条件（两种骰子均显示在左侧图片中）。
![骰子图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF225A/85f2da947143b29924bb6531722e86105dbf28c1.png)
爱丽丝和鲍勃玩骰子。爱丽丝用$n$个骰子搭建了一座塔。我们知道，在这座塔中，相邻的骰子接触面数字不同。鲍勃想唯一确定搭建这座塔的所有骰子面上的数字。不幸的是，鲍勃从一个面观察这座塔，所以他看不到所有面上的数字。鲍勃看到塔顶的数字以及两个相邻侧面的数字（如右侧图片所示）。
请帮助鲍勃，判断是否能够唯一确定塔中所有骰子面上的数字。

## 样例 #1
### 输入
```
3
6
3 2
5 4
2 4
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
3
3
2 6
4 1
5 3
```
### 输出
```
NO
```

### 算法分类
数学

### 综合分析与结论
所有题解思路基本一致，核心思路都是判断输入的骰子信息是否存在不合法情况，即通过列举所有可能导致不能唯一确定骰子面数字的情况（如两个侧面数字相等、侧面数字与顶面或底面数字相等、两个侧面数字互为对面等），若存在则输出“NO”，否则输出“YES”。不同题解在代码实现上有一些差异，如输入方式、变量命名、代码风格等，但整体算法逻辑相同。

### 通用建议与扩展思路
 - **通用建议**：在解决此类问题时，关键在于准确理解题目所给条件，像本题中骰子相对面数字和为7以及相邻骰子接触面数字不同等条件，并将这些条件准确转化为代码中的判断逻辑。同时，注意代码实现的简洁性和可读性，合理选择变量命名和代码结构。
 - **扩展思路**：同类型题目可能会改变骰子的数字规则、观察角度或者增加骰子之间的约束条件等。例如，改变骰子相对面数字和的规则，或者要求判断不同排列方式下骰子组合的合法性等。类似算法套路在于通过对给定条件的分析，找出所有可能导致不合法情况的判断依据，并在代码中实现这些判断。

### 洛谷相似题目
 - [P1035 级数求和](https://www.luogu.com.cn/problem/P1035)：通过简单的数学计算和循环结构解决问题，锻炼对基本数学运算和循环逻辑的运用。
 - [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)：根据给定条件进行简单的数学判断和累加操作，与本题判断合法性类似。
 - [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：通过数学分析和循环枚举解决连续自然数和的问题，培养数学思维和枚举法的运用。 

---
处理用时：29.14秒