# 题目信息

# Duff and Weight Lifting

## 题目描述

Recently, Duff has been practicing weight lifting. As a hard practice, Malek gave her a task. He gave her a sequence of weights. Weight of $ i $ -th of them is $ 2^{w_{i}} $ pounds. In each step, Duff can lift some of the remaining weights and throw them away. She does this until there's no more weight left. Malek asked her to minimize the number of steps.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF587A/ae0bf97f46f744ec67cd3653eed80d2fdb7f3472.png)Duff is a competitive programming fan. That's why in each step, she can only lift and throw away a sequence of weights $ 2^{a_{1}},...,2^{a_{k}} $ if and only if there exists a non-negative integer $ x $ such that $ 2^{a_{1}}+2^{a_{2}}+...+2^{a_{k}}=2^{x} $ , i. e. the sum of those numbers is a power of two.

Duff is a competitive programming fan, but not a programmer. That's why she asked for your help. Help her minimize the number of steps.

## 说明/提示

In the first sample case: One optimal way would be to throw away the first three in the first step and the rest in the second step. Also, it's not possible to do it in one step because their sum is not a power of two.

In the second sample case: The only optimal way is to throw away one weight in each step. It's not possible to do it in less than 4 steps because there's no subset of weights with more than one weight and sum equal to a power of two.

## 样例 #1

### 输入

```
5
1 1 2 3 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
0 1 2 3
```

### 输出

```
4
```

# AI分析结果



# Duff and Weight Lifting

## 题目描述

最近，Duff 在练习举重。作为一项高难度训练，Malek 给了她一个任务。他给了她一个权重序列，其中第 $i$ 个权重的重量为 $2^{w_i}$ 磅。Duff 每次可以举起并丢弃剩余权重中的一部分，直到没有剩余。Malek 要求她最小化操作次数。

每次丢弃的权重序列 $2^{a_1},...,2^{a_k}$ 必须满足：存在一个非负整数 $x$ 使得这些权重的总和等于 $2^x$（即总和为 2 的幂）。

请帮助 Duff 找到最小的操作次数。

## 说明/提示

第一个样例中，最优方案是第一步丢弃前三个权重，第二步丢弃剩余两个。第二个样例中必须逐个丢弃，因为不存在多个权重能组合成 2 的幂。

## 样例 #1

### 输入
```
5
1 1 2 3 3
```

### 输出
```
2
```

## 样例 #2

### 输入
```
4
0 1 2 3
```

### 输出
```
4
```

## 算法分类
贪心

---

## 题解分析与结论

### 核心思路
将问题转化为二进制进位问题。统计每个权重值 $w_i$ 的出现次数，从低位到高位进行进位处理：偶数个 $2^x$ 可以合并为更高位的权重，最终剩余奇数个的每个权重需要单独操作一次。

### 最优题解

#### 题解作者：wanggk（★★★★★）
**关键亮点**：  
- 使用桶计数统计每个权重出现次数  
- 模拟二进制进位过程，动态处理最高位  
- 代码简洁高效，时间复杂度 O(n + max_w)

**核心代码**：
```cpp
int cnt[1000050];
for(int i=0;i<=mx||cnt[i];i++) {
    cnt[i+1] += cnt[i]/2;
    if(cnt[i]%2) ans++;
}
```

#### 题解作者：Coros_Trusds（★★★★☆）
**个人心得**：  
- 强调数组大小需足够大（1e6+50）以避免越界  
- 处理进位时需更新最大值边界  
- 提醒注意循环终止条件

**核心代码**：
```cpp
for(int i=0;i<=maxx || t[i]!=0;i++) {
    if(t[i]) {
        t[i+1] += t[i]/2;
        if(t[i]%2) ans++;
    }
}
```

#### 题解作者：skyskyCCC（★★★★☆）
**实现技巧**：  
- 预计算 2 的幂次加速处理  
- 使用位运算优化奇偶判断  
- 采用线性数组处理保证效率

**核心代码**：
```cpp
for(int i=0;i<N-1;i++) {
    ans += a[i]&1;
    a[i+1] += a[i]>>1;
}
```

---

## 关键技巧总结
1. **桶计数+进位模拟**：用数组统计每个权重出现次数，通过类似二进制进位的方式处理合并  
2. **动态处理高位边界**：循环条件需包含当前最大值和可能进位产生的新高位  
3. **奇偶性判断优化**：直接使用取模或位运算判断是否需要单独操作  
4. **数组大小预分配**：根据数据范围预分配足够大的空间（建议 1e6+50 级别）

---

## 拓展练习
1. [P1582 倒水](https://www.luogu.com.cn/problem/P1582) - 同类二进制合并问题  
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心策略应用  
3. [P7072 直播获奖](https://www.luogu.com.cn/problem/P7072) - 动态统计与排序技巧  

通过解决这些题目可以加深对贪心策略和二进制处理技巧的理解。

---
处理用时：105.94秒