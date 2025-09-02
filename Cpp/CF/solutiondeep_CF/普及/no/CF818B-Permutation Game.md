# 题目信息

# Permutation Game

## 题目描述

 $ n $ children are standing in a circle and playing a game. Children's numbers in clockwise order form a permutation $ a_{1},a_{2},...,a_{n} $ of length $ n $ . It is an integer sequence such that each integer from $ 1 $ to $ n $ appears exactly once in it.

The game consists of $ m $ steps. On each step the current leader with index $ i $ counts out $ a_{i} $ people in clockwise order, starting from the next person. The last one to be pointed at by the leader becomes the new leader.

You are given numbers $ l_{1},l_{2},...,l_{m} $ — indices of leaders in the beginning of each step. Child with number $ l_{1} $ is the first leader in the game.

Write a program which will restore a possible permutation $ a_{1},a_{2},...,a_{n} $ . If there are multiple solutions then print any of them. If there is no solution then print -1.

## 说明/提示

Let's follow leadership in the first example:

- Child $ 2 $ starts.
- Leadership goes from $ 2 $ to $ 2+a_{2}=3 $ .
- Leadership goes from $ 3 $ to $ 3+a_{3}=5 $ . As it's greater than $ 4 $ , it's going in a circle to $ 1 $ .
- Leadership goes from $ 1 $ to $ 1+a_{1}=4 $ .
- Leadership goes from $ 4 $ to $ 4+a_{4}=8 $ . Thus in circle it still remains at $ 4 $ .

## 样例 #1

### 输入

```
4 5
2 3 1 4 4
```

### 输出

```
3 1 2 4 
```

## 样例 #2

### 输入

```
3 3
3 1 2
```

### 输出

```
-1
```

# AI分析结果



【中文重写题目】
# 排列游戏

## 题目描述

$ n $ 个孩子围成一个圆圈进行游戏。孩子们的编号按顺时针顺序形成一个长度为 $ n $ 的排列 $ a_{1},a_{2},...,a_{n} $，即每个 $ 1 $ 到 $ n $ 的整数恰好出现一次。

游戏进行 $ m $ 轮。每轮开始时当前领导者（编号为 $ i $）从其下一个人开始顺时针数出 $ a_{i} $ 个人，最后一个被数到的人成为新的领导者。

给定 $ l_{1},l_{2},...,l_{m} $ 表示每轮初始的领导者编号，其中 $ l_{1} $ 是第一轮的初始领导者。请构造可能的排列 $ a $，若存在多个解输出任意一个，无解输出 -1。

## 算法分类
构造

---

### 综合分析与结论
题目核心是通过给定的领导者序列反向构造排列。关键点在于：
1. 通过相邻领导者计算对应位置的a值（需处理环形移动的模运算）
2. 检查数值冲突（已使用的数或与已赋值位置矛盾）
3. 填充未确定位置（使用未出现的数）

三个题解均采用构造法实现，思路高度一致，区别仅在于模运算处理和填充顺序的实现细节。均能正确处理环形逻辑和冲突检测。

---

### 精选题解与评分

#### 题解1：A_grasser（4.5星）
**核心亮点**  
- 清晰的冲突检测逻辑（数值重复、赋值矛盾双校验）
- 模块化设计 leader() 函数处理环形计算
- 剩余数值填充采用顺序扫描，保证最小可用数优先

**代码核心**  
```cpp
int leader(int x) {
    int q = l[x] - l[x-1];
    return q <= 0 ? q + n : q; // 环形处理
}
// 冲突检测部分
if (a[l[i-1]] != 0 && a[l[i-1]] != leader(i)) {
    cout << -1;
    return 0;
}
```

#### 题解2：小恐（4星）
**核心亮点**  
- 简洁的差值计算 (l[i]-last +n) %n
- 剩余数值填充采用动态指针now优化效率
- 代码注释清晰，易理解

**个人心得**  
> "所有的代码都要自己敲，不要Ctrl c+Ctrl v！" —— 强调手敲代码加深理解

**代码核心**  
```cpp
int x = (l - last + n) % n; // 计算所需a值
x = x == 0 ? n : x;        // 修正模n结果
if (book[x] || (a[last] && a[last] != x)) // 双重检测
    return printf("-1"),0;
```

#### 题解3：Keroshi（4星）
**核心亮点**  
- 最简短的实现（仅22行有效代码）
- 使用pos指针优化剩余数值填充
- 输入输出优化提升效率

**代码核心**  
```cpp
int d = l[i] - l[i-1];
if (d <= 0) d += n; // 处理负差值
// 剩余数值填充逻辑
int pos = 1;
while (b[pos]) pos++; 
a[i] = pos;
```

---

### 关键思路总结
1. **环形移动公式**：$ a_{prev} = (next\_leader - prev\_leader + n) \% n $，若结果为0则修正为n
2. **冲突检测双保险**：既要检查计算值是否已被使用，也要验证与已赋值的兼容性
3. **剩余数值填充策略**：顺序扫描未使用的最小值，保证构造合法排列

---

### 拓展与相似题目
- **构造环形关系**：CF1328C（构造特殊三进制数）
- **排列合法性验证**：洛谷P1075（质因数分解构造）
- **环形模拟问题**：洛谷P1518 [USACO2.4]两只塔姆沃斯牛

推荐题目：  
1. 洛谷P1057 [NOIP2008 普及组] 传球游戏（环形递推）  
2. 洛谷P1603 [USACO08DEC]Hay Forage（环形贪心）  
3. 洛谷P1969 [NOIP2013 提高组] 积木大赛（差分构造）

---
处理用时：66.15秒