# 题目信息

# Inna and Pink Pony

## 题目描述

Dima and Inna are doing so great! At the moment, Inna is sitting on the magic lawn playing with a pink pony. Dima wanted to play too. He brought an $ n×m $ chessboard, a very tasty candy and two numbers $ a $ and $ b $ .

Dima put the chessboard in front of Inna and placed the candy in position $ (i,j) $ on the board. The boy said he would give the candy if it reaches one of the corner cells of the board. He's got one more condition. There can only be actions of the following types:

- move the candy from position $ (x,y) $ on the board to position $ (x-a,y-b) $ ;
- move the candy from position $ (x,y) $ on the board to position $ (x+a,y-b) $ ;
- move the candy from position $ (x,y) $ on the board to position $ (x-a,y+b) $ ;
- move the candy from position $ (x,y) $ on the board to position $ (x+a,y+b) $ .

Naturally, Dima doesn't allow to move the candy beyond the chessboard borders.

Inna and the pony started shifting the candy around the board. They wonder what is the minimum number of allowed actions that they need to perform to move the candy from the initial position $ (i,j) $ to one of the chessboard corners. Help them cope with the task!

## 说明/提示

Note to sample 1:

Inna and the pony can move the candy to position $ (1+2,3+2)=(3,5) $ , from there they can move it to positions $ (3-2,5+2)=(1,7) $ and $ (3+2,5+2)=(5,7) $ . These positions correspond to the corner squares of the chess board. Thus, the answer to the test sample equals two.

## 样例 #1

### 输入

```
5 7 1 3 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5 2 3 1 1
```

### 输出

```
Poor Inna and pony!
```

# AI分析结果



# Inna and Pink Pony

## 题目描述

Dima 和 Inna 正在玩一个游戏。Dima 带来了一个 $n×m$ 的棋盘、一颗糖果以及两个数字 $a$ 和 $b$。糖果被放置在棋盘的 $(i,j)$ 位置，需要通过以下四种移动方式之一将其移动到棋盘的任意角落（四个顶点）：

1. 从 $(x,y)$ 移动到 $(x-a,y-b)$
2. 从 $(x,y)$ 移动到 $(x+a,y-b)$
3. 从 $(x,y)$ 移动到 $(x-a,y+b)$
4. 从 $(x,y)$ 移动到 $(x+a,y+b)$

每次移动后糖果必须留在棋盘内。求到达角落所需的最小移动次数，若无法到达则输出 "Poor Inna and pony!"。

## 样例说明

### 样例 #1
输入：
```
5 7 1 3 2 2
```
输出：
```
2
```
说明：通过两次移动可达角落（路径见原题描述）。

### 样例 #2
输入：
```
5 5 2 3 1 1
```
输出：
```
Poor Inna and pony!
```

---

## 算法分类
数学、模拟

---

## 题解对比与结论

### 共同解题思路
1. **特判初始位置**：若糖果已在角落，直接返回0步。
2. **棋盘尺寸检查**：若棋盘尺寸不足以进行移动（如n≤a或m≤b），直接无解。
3. **坐标差约束**：到目标角的横纵坐标差必须能被a和b整除。
4. **奇偶性约束**：横纵方向移动次数的奇偶性必须相同，保证能在交替移动中到达目标。
5. **最小步数计算**：对四个角分别计算符合条件的步数，取最小值。

### 最优题解亮点
#### 题解作者：Fuxh_18（★★★★☆）
**核心思路**：
- 封装判断函数 `zz(int x, int y)` 处理每个角的约束条件
- 清晰处理奇偶性判断：`(x/a % 2) == (y/b % 2)`
- 使用位运算优化奇偶性判断：`(s1 + s2) & 1 ^ 1`
```cpp
void zz(int x,int y){ 
    if(x%a==0 && y%b==0 && x/a%2 == y/b%2){
        ans = min(ans, max(x/a, y/b));
        f = 1;
    }
}
```

#### 题解作者：xiaorui2007（★★★☆☆）
**关键实现**：
- 函数 `f(int x, int y)` 统一处理四个角
- 边界条件处理：`ans > 0` 时检查棋盘是否允许移动
```cpp
if(ans && ((n<=a)||(m<=b))) // 必须保证移动空间
    cout<<"Poor Inna and pony!";
```

#### 题解作者：ZJle（★★★☆☆）
**实现特点**：
- 预处理四个角的坐标差存入数组 `er[5]`
- 使用位运算简化奇偶性判断：`(ans1 & 1) == (ans2 & 1)`
```cpp
for(int i=0;i<4;i++){
    if(差可整除 && 奇偶相同)
        ans = min(ans, max(t1,t2));
}
```

---

## 关键思路总结
1. **数学约束分析**：通过模运算和奇偶性判断将问题转化为数学条件验证。
2. **分角处理技巧**：对四个角分别计算，避免冗余代码。
3. **位运算优化**：使用位运算代替取模运算提升效率。
4. **边界条件检查**：在计算步数后再次验证棋盘尺寸是否允许实际移动。

---

## 相似题目推荐
1. [CF374B - Inna and Nine](https://codeforces.com/problemset/problem/374/B)（数学分析）
2. [洛谷 P1134 阶乘问题](https://www.luogu.com.cn/problem/P1134)（奇偶性与模运算）
3. [洛谷 P3951 小凯的疑惑](https://www.luogu.com.cn/problem/P3951)（数论约束条件分析）

---
处理用时：55.07秒