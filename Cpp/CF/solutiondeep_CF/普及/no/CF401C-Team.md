# 题目信息

# Team

## 题目描述

Now it's time of Olympiads. Vanya and Egor decided to make his own team to take part in a programming Olympiad. They've been best friends ever since primary school and hopefully, that can somehow help them in teamwork.

For each team Olympiad, Vanya takes his play cards with numbers. He takes only the cards containing numbers 1 and 0. The boys are very superstitious. They think that they can do well at the Olympiad if they begin with laying all the cards in a row so that:

- there wouldn't be a pair of any side-adjacent cards with zeroes in a row;
- there wouldn't be a group of three consecutive cards containing numbers one.

Today Vanya brought $ n $ cards with zeroes and $ m $ cards with numbers one. The number of cards was so much that the friends do not know how to put all those cards in the described way. Help them find the required arrangement of the cards or else tell the guys that it is impossible to arrange cards in such a way.

## 样例 #1

### 输入

```
1 2
```

### 输出

```
101
```

## 样例 #2

### 输入

```
4 8
```

### 输出

```
110110110101
```

## 样例 #3

### 输入

```
4 10
```

### 输出

```
11011011011011
```

## 样例 #4

### 输入

```
1 5
```

### 输出

```
-1
```

# AI分析结果



### 中文重述题目
**题目名称**：Team

**题目描述**  
Vanya和Egor想组成一个团队参加编程奥赛。他们使用带有数字0和1的卡片，希望排列卡片满足以下条件：
1. 没有两个相邻的0；
2. 没有三个连续的1。

给定0的数量$n$和1的数量$m$，判断是否存在合法排列，若存在则输出任意一种，否则输出-1。

---

### 算法分类  
**构造**

---

### 题解分析与结论  
题目核心是构造满足条件的01序列。关键在于分析无解条件，并通过贪心策略分情况构造序列。  
- **无解条件**：当$m > 2n+2$（1太多无法隔开）或$n > m+1$（0太多无法隔开）时无解。
- **构造策略**：优先处理多余的1，剩余部分交替插入01或110的组合。

---

### 精选题解  
#### 1. Zxsoul（⭐⭐⭐⭐）  
**关键亮点**  
- 分三类情况处理：n>m、n≤m≤2n、m>2n，逻辑清晰。
- 代码简洁，直接按条件分支输出，覆盖所有边界情况。

**核心代码**  
```cpp
if (m > n * 2) {
    // 处理多余的1
    for (int i = 1; i <= m - n * 2; i++) cout << "1";
    m = 2 * n;
}
if (m >= n) {
    // 输出m-n组"011"和剩余"01"
    for (int i = 1; i <= m - n; i++) cout << "011";
    for (int i = 1; i <= 2 * n - m; i++) cout << "01";
} else {
    // n = m + 1时特判
    cout << "0";
    for (int i = 1; i <= m; i++) cout << "10";
}
```

#### 2. Histone（⭐⭐⭐⭐）  
**关键亮点**  
- 动态处理剩余量，优先输出110组合，代码更短。
- 通过循环逐步构造，避免冗余分支。

**核心代码**  
```cpp
while (n || m) {
    if (n > m) { // 先导0
        cout << "0"; n--;
    } else if (m > n) { // 输出110
        cout << "110"; m -= 2; n--;
    } else { // 输出10
        cout << "10"; m--; n--;
    }
}
```

#### 3. Blunt_Feeling（⭐⭐⭐）  
**关键亮点**  
- 追求字典序最小，优先放0。
- 处理开头和结尾的特殊情况，确保合法性。

---

### 关键思路总结  
1. **无解判断**：直接通过$m > 2n+2$和$n > m+1$过滤。
2. **贪心构造**：  
   - **多余1**：先输出超出2n的1，剩余按110分组。
   - **平衡情况**：交替使用110和01填充。
   - **0较多时**：以0开头后接10交替。

---

### 拓展与相似题目  
- **构造+贪心**：[CF1157B](https://www.luogu.com.cn/problem/CF1157B)（分段替换数字）
- **条件排列**：[P1056 排座椅](https://www.luogu.com.cn/problem/P1056)（选择最优分隔线）
- **序列构造**：[CF675C](https://www.luogu.com.cn/problem/CF675C)（零和分段）

---
处理用时：76.56秒