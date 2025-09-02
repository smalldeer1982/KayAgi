# 题目信息

# Number Game

## 题目描述

Ashishgup and FastestFinger play a game.

They start with a number $ n $ and play in turns. In each turn, a player can make any one of the following moves:

- Divide $ n $ by any of its odd divisors greater than $ 1 $ .
- Subtract $ 1 $ from $ n $ if $ n $ is greater than $ 1 $ .

Divisors of a number include the number itself.

The player who is unable to make a move loses the game.

Ashishgup moves first. Determine the winner of the game if both of them play optimally.

## 说明/提示

In the first test case, $ n = 1 $ , Ashishgup cannot make a move. He loses.

In the second test case, $ n = 2 $ , Ashishgup subtracts $ 1 $ on the first move. Now $ n = 1 $ , FastestFinger cannot make a move, so he loses.

In the third test case, $ n = 3 $ , Ashishgup divides by $ 3 $ on the first move. Now $ n = 1 $ , FastestFinger cannot make a move, so he loses.

In the last test case, $ n = 12 $ , Ashishgup divides it by $ 3 $ . Now $ n = 4 $ , FastestFinger is forced to subtract $ 1 $ , and Ashishgup gets $ 3 $ , so he wins by dividing it by $ 3 $ .

## 样例 #1

### 输入

```
7
1
2
3
4
5
6
12```

### 输出

```
FastestFinger
Ashishgup
Ashishgup
FastestFinger
Ashishgup
FastestFinger
Ashishgup```

# AI分析结果

### 题目内容重写

# 数字游戏

## 题目描述

Ashishgup 和 FastestFinger 玩一个游戏。

他们从一个数字 $n$ 开始，轮流进行操作。每次操作，玩家可以选择以下一种操作：

- 将 $n$ 除以一个大于 $1$ 的奇数因子。
- 如果 $n$ 大于 $1$，将 $n$ 减去 $1$。

一个数的因子包括它本身。

无法进行操作的玩家输掉游戏。

Ashishgup 先手。假设双方都采取最优策略，确定游戏的赢家。

## 说明/提示

在第一个测试用例中，$n = 1$，Ashishgup 无法进行操作，因此他输掉游戏。

在第二个测试用例中，$n = 2$，Ashishgup 先手将 $n$ 减去 $1$，此时 $n = 1$，FastestFinger 无法进行操作，因此他输掉游戏。

在第三个测试用例中，$n = 3$，Ashishgup 先手将 $n$ 除以 $3$，此时 $n = 1$，FastestFinger 无法进行操作，因此他输掉游戏。

在最后一个测试用例中，$n = 12$，Ashishgup 先手将 $n$ 除以 $3$，此时 $n = 4$，FastestFinger 被迫将 $n$ 减去 $1$，此时 $n = 3$，Ashishgup 再次将 $n$ 除以 $3$，因此他赢得游戏。

## 样例 #1

### 输入

```
7
1
2
3
4
5
6
12
```

### 输出

```
FastestFinger
Ashishgup
Ashishgup
FastestFinger
Ashishgup
FastestFinger
Ashishgup
```

### 算法分类
数学、博弈论

### 题解综合分析

该题目属于博弈论问题，核心在于分析不同情况下先手和后手的必胜策略。题解主要通过对 $n$ 的奇偶性、质因数分解等进行分类讨论，判断先手是否能够通过最优策略获胜。

### 精选题解

#### 题解1：江户川·萝卜 (5星)
**关键亮点**：
- 详细分类讨论，覆盖了所有可能的情况。
- 代码简洁清晰，逻辑严谨。
- 通过质因数分解和奇偶性分析，准确判断胜负。

**核心代码**：
```cpp
bool isprime(int n){
    if(n<2) return false;
    for(int i=2;i*i<=n;i++)
        if(n%i==0) return false;
    return true;
}
```
**实现思想**：通过质数判断函数 `isprime` 来判断奇数因子是否为质数，进而决定胜负。

#### 题解2：b6e0_ (4星)
**关键亮点**：
- 通过指数和判断胜负，简化了问题。
- 代码优化较好，时间复杂度为 $O(t\sqrt n)$。
- 通过位运算和质因数分解，快速判断胜负。

**核心代码**：
```cpp
int tot=0;
for(int i=3;i*i<=n;i+=2)
    while(n%i==0){
        tot++;
        n/=i;
    }
```
**实现思想**：通过累加奇质因数的指数和，判断先手是否能够通过除以奇数因子获胜。

#### 题解3：KellyFrog (4星)
**关键亮点**：
- 通过质数判断和奇偶性分析，快速判断胜负。
- 代码结构清晰，易于理解。
- 通过质因数分解和奇偶性分析，准确判断胜负。

**核心代码**：
```cpp
bool Prime(int x) {
    for(int i=2;i*i<=x;i++)
        if(x%i==0) return false;
    return true;
}
```
**实现思想**：通过质数判断函数 `Prime` 来判断奇数因子是否为质数，进而决定胜负。

### 最优关键思路或技巧
1. **分类讨论**：通过对 $n$ 的奇偶性、质因数分解等进行分类讨论，判断先手是否能够通过最优策略获胜。
2. **质数判断**：通过质数判断函数，快速判断奇数因子是否为质数，进而决定胜负。
3. **指数和判断**：通过累加奇质因数的指数和，判断先手是否能够通过除以奇数因子获胜。

### 可拓展之处
1. **博弈论问题**：类似的问题可以通过分类讨论和最优策略分析来解决。
2. **质因数分解**：在涉及质因数的题目中，质因数分解是一个常用的技巧。

### 推荐题目
1. [P3150 - 取石子游戏](https://www.luogu.com.cn/problem/P3150)
2. [P1370 - 数字游戏](https://www.luogu.com.cn/problem/P1370)
3. [P1371 - 数字游戏2](https://www.luogu.com.cn/problem/P1371)

### 个人心得摘录
- **江户川·萝卜**：感觉有些长，应该可以让我这样的萌新更好理解吧。
- **b6e0_**：突然发现这题没什么人写题解，~~热心的~~我就来写一篇了。
- **KellyFrog**：那么首先，拿到$1$的人是输的。

---
处理用时：39.54秒