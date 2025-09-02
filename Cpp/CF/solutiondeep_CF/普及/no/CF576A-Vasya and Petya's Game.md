# 题目信息

# Vasya and Petya's Game

## 题目描述

Vasya and Petya are playing a simple game. Vasya thought of number $ x $ between $ 1 $ and $ n $ , and Petya tries to guess the number.

Petya can ask questions like: "Is the unknown number divisible by number $ y $ ?".

The game is played by the following rules: first Petya asks all the questions that interest him (also, he can ask no questions), and then Vasya responds to each question with a 'yes' or a 'no'. After receiving all the answers Petya should determine the number that Vasya thought of.

Unfortunately, Petya is not familiar with the number theory. Help him find the minimum number of questions he should ask to make a guaranteed guess of Vasya's number, and the numbers $ y_{i} $ , he should ask the questions about.

## 说明/提示

The sequence from the answer to the first sample test is actually correct.

If the unknown number is not divisible by one of the sequence numbers, it is equal to $ 1 $ .

If the unknown number is divisible by $ 4 $ , it is $ 4 $ .

If the unknown number is divisible by $ 3 $ , then the unknown number is $ 3 $ .

Otherwise, it is equal to $ 2 $ . Therefore, the sequence of questions allows you to guess the unknown number. It can be shown that there is no correct sequence of questions of length 2 or shorter.

## 样例 #1

### 输入

```
4
```

### 输出

```
3
2 4 3 
```

## 样例 #2

### 输入

```
6
```

### 输出

```
4
2 4 3 5 
```

# AI分析结果



# Vasya and Petya's Game

## 题目描述

Vasya 和 Petya 在玩一个简单的游戏。Vasya 想了一个介于 1 到 n 之间的数 x，Petya 需要通过提问来猜这个数。

Petya 可以提问形式为："未知数是否能被 y 整除？"

游戏规则如下：Petya 首先提出所有他想问的问题（也可以不提问），然后 Vasya 对每个问题回答 "是" 或 "否"。收到所有回答后，Petya 必须确定 Vasya 所想的数。

请帮助 Petya 找到他需要提出的最少问题数量，以及这些问题的具体数值 y_i。

## 说明/提示

第一个样例的正确性验证：
- 若未知数无法被序列中的任何数整除，则为 1
- 若能被 4 整除则为 4
- 若能被 3 整除则为 3
- 否则为 2

## 样例 #1

### 输入
```
4
```

### 输出
```
3
2 4 3 
```

## 样例 #2

### 输入
```
6
```

### 输出
```
4
2 4 3 5 
```

**算法分类**：数学（质数分解）

---

### 题解综合分析

所有题解均基于唯一分解定理，核心思路是：通过询问所有质数的幂次方，确保能唯一确定数的质因数分解。关键点在于必须包含每个质数在范围内的所有幂次（如 2^1, 2^2,...直到超过n）。

#### 最优思路总结
1. **质数筛选**：使用线性筛法预处理所有质数
2. **幂次枚举**：对每个质数 p，枚举其所有幂次 p^k（直到超过n）
3. **结果构造**：收集所有符合条件的幂次数作为问题集合

---

### 高星题解推荐

#### 题解1（作者：_NightFire666_，⭐⭐⭐⭐⭐）
**亮点**：
- 详细解释线性筛原理与幂次枚举逻辑
- 代码可读性强，包含详细注释
- 正确处理边界情况（如空结果输出）

**核心代码**：
```cpp
vector<int>ans;
for(auto i:primes){ // 枚举每个质数
    int k=0;
    while(pow(i,++k)<=n) // 计算所有不超过n的幂次
        ans.push_back(pow(i,k));
}
```

#### 题解2（作者：shaozhehan，⭐⭐⭐⭐）
**亮点**：
- 代码简洁高效，时间复杂度 O(n)
- 使用单独数组标记有效询问数
- 处理了输出格式的特殊情况

**核心实现**：
```cpp
for (int i = 1; i <= cnt; i++)
    for (int j = prime[i]; j <= n; j *= prime[i])
        ans[++cnt1] = j; // 收集质数的所有幂次
```

#### 题解3（作者：zesqwq，⭐⭐⭐⭐）
**亮点**：
- 最优解实现，空间效率高
- 使用布尔数组双重标记质数和有效询问数
- 代码结构紧凑，适合竞赛场景

**核心逻辑**：
```cpp
for (int i = 1; i <= cnt; i++)
    for (int j = prime[i]; j <= n; j *= prime[i])
        flag[j] = 1; // 标记有效询问数
```

---

### 关键技巧与拓展

#### 关键技巧
- **线性筛法优化**：O(n) 时间筛质数，保证每个数被最小质因数筛掉
- **幂次跳跃枚举**：通过连续乘质数代替幂运算，避免浮点误差
- **结果排序优化**：自动按质数大小和幂次顺序生成结果

#### 类似题目推荐
1. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
2. [P1069 细胞分裂](https://www.luogu.com.cn/problem/P1069)
3. [P2043 质因子分解](https://www.luogu.com.cn/problem/P2043)

---

### 个人心得摘录
- **调试经验**：注意当 n=1 时需要特判输出（无询问）
- **格式陷阱**：输出时需检查结果数组是否为空，避免多余空格
- **优化技巧**：用乘法代替 pow 函数，防止因浮点运算导致错误

---
处理用时：61.39秒