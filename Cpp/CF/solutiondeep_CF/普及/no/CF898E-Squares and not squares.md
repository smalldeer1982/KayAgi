# 题目信息

# Squares and not squares

## 题目描述

Ann and Borya have $ n $ piles with candies and $ n $ is even number. There are $ a_{i} $ candies in pile with number $ i $ .

Ann likes numbers which are square of some integer and Borya doesn't like numbers which are square of any integer. During one move guys can select some pile with candies and add one candy to it (this candy is new and doesn't belong to any other pile) or remove one candy (if there is at least one candy in this pile).

Find out minimal number of moves that is required to make exactly $ n/2 $ piles contain number of candies that is a square of some integer and exactly $ n/2 $ piles contain number of candies that is not a square of any integer.

## 说明/提示

In first example you can satisfy condition in two moves. During each move you should add one candy to second pile. After it size of second pile becomes $ 16 $ . After that Borya and Ann will have two piles with number of candies which is a square of integer (second and fourth pile) and two piles with number of candies which is not a square of any integer (first and third pile).

In second example you should add two candies to any three piles.

## 样例 #1

### 输入

```
4
12 14 30 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
0 0 0 0 0 0
```

### 输出

```
6
```

## 样例 #3

### 输入

```
6
120 110 23 34 25 45
```

### 输出

```
3
```

## 样例 #4

### 输入

```
10
121 56 78 81 45 100 1 0 54 78
```

### 输出

```
0
```

# AI分析结果



# Squares and not squares

## 题目描述

Ann 和 Borya 有 $n$ 堆糖果（$n$ 为偶数），第 $i$ 堆有 $a_i$ 颗糖果。Ann 喜欢完全平方数，Borya 不喜欢完全平方数。每次操作可以给某堆糖果加 1 或减 1（不能为负）。求使恰好 $n/2$ 堆为完全平方数，其余为非完全平方数的最小操作次数。

## 说明/提示

样例 1 操作两次将第二堆变为 16。样例 2 需要给任意三堆各加 2 颗。样例 4 原始数据已满足条件无需操作。

## 算法分类
贪心

## 题解分析

### 关键思路
1. **双阶段处理**：计算每个数成为平方数的代价，同时预处理平方数转为非平方数的代价
2. **分类讨论**：根据初始平方数数量是否过半，选择转化方向
3. **特殊处理零**：零转为非平方数需 2 次操作（0 → 2）
4. **贪心排序**：按转换代价排序后取最小代价组合

### 最优题解

#### 题解 [CountState] ⭐⭐⭐⭐
**亮点**：  
- 分情况处理逻辑清晰，维护两个独立代价数组
- 直接使用数学推导替代复杂条件判断

**核心代码**：
```cpp
sort(b+1,b+1+n);  // 转为平方数的代价排序
sort(c+1,c+1+n);  // 平方数转非平方的代价排序
if(cnt <= n/2) 
    for(int i=1;i<=n/2;i++) ans += b[i];
else 
    for(int i=1;i<=n/2;i++) ans += c[i];
```

#### 题解 [ivyjiao] ⭐⭐⭐⭐
**亮点**：  
- 二合一处理技巧，通过后序循环补充计算
- 利用 max 函数直接处理零的特殊情况

**核心代码**：
```cpp
ans += max(cnt-n/2,0ll);  // 处理必须转换的零
for(int i=1;i<=n;i++) {
    if(i <= n/2) ans += b[i];  
    else if(b[i] == 0) ans++;  // 处理剩余平方数
}
```

### 关键实现技巧
1. **平方数判定**：`(int)sqrt(x) * (int)sqrt(x) == x`
2. **双代价计算**：`min(x - lower², upper² - x)` 同时计算上下界
3. **零值标记**：单独处理零的转换逻辑避免错误

## 拓展练习
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心+优先队列
2. [P1208 混合牛奶](https://www.luogu.com.cn/problem/P1208) - 性价比贪心选择 
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223) - 经典排序贪心

## 调试心得
> "样例 2 全零卡了半小时，发现零转非平方必须加两次，而普通平方数只需加一次" —— ivyjiao  
总结：特殊边界值需要单独验证，避免惯性思维导致错误。

---
处理用时：143.66秒