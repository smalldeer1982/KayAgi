# 题目信息

# New Year's Eve

## 题目描述

Since Grisha behaved well last year, at New Year's Eve he was visited by Ded Moroz who brought an enormous bag of gifts with him! The bag contains $ n $ sweet candies from the good ol' bakery, each labeled from $ 1 $ to $ n $ corresponding to its tastiness. No two candies have the same tastiness.

The choice of candies has a direct effect on Grisha's happiness. One can assume that he should take the tastiest ones — but no, the holiday magic turns things upside down. It is the xor-sum of tastinesses that matters, not the ordinary sum!

A xor-sum of a sequence of integers $ a_{1},a_{2},...,a_{m} $ is defined as the bitwise XOR of all its elements: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/475d3a054d8c211f23a68d652dd85385e5ab9fc9.png), here ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/4298d47c0191af3c0a3103f431751061bc7e2362.png) denotes the bitwise XOR operation; more about bitwise XOR can be found [here.](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

Ded Moroz warned Grisha he has more houses to visit, so Grisha can take no more than $ k $  candies from the bag. Help Grisha determine the largest xor-sum (largest xor-sum means maximum happiness!) he can obtain.

## 说明/提示

In the first sample case, one optimal answer is $ 1 $ , $ 2 $ and $ 4 $ , giving the xor-sum of $ 7 $ .

In the second sample case, one can, for example, take all six candies and obtain the xor-sum of $ 7 $ .

## 样例 #1

### 输入

```
4 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
6 6
```

### 输出

```
7
```

# AI分析结果



# New Year's Eve

## 题目描述

由于Grisha去年表现良好，新年夜Ded Moroz带着一个装满礼物的大袋子来拜访他！袋子里有$ n $颗美味糖果，编号从$ 1 $到$ n $，每颗糖果的甜度各不相同。Grisha最多可以拿走$ k $颗糖果，甜度的异或和决定他的快乐程度。请帮助Grisha计算他能获得的最大异或和。

## 样例 #1

### 输入

```
4 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
6 6
```

### 输出

```
7
```

---

### 题解综合分析

所有题解均围绕二进制位构造的核心思路展开：
1. **k=1时**直接取最大值n
2. **k≥2时**构造最高位全1的数，即找到n的最高二进制位p，结果为$ 2^{p+1}-1 $

#### 精选题解（评分≥4星）

1. **BB2655（5星）**
   - **亮点**：数学证明严谨，代码清晰展示位运算本质
   - **代码核心**：
     ```cpp
     long long b=0;
     for(;n>>b;b++);
     cout<<(1LL<<b)-1;
     ```

2. **SoyTony（4星）**
   - **亮点**：公式化表达结论，提供严谨数学推导
   - **关键证明**：存在两数异或可填满低位，确保最大全1数可达

3. **GZY007（4星）**
   - **亮点**：代码极简，利用位分解直接构造结果
   - **代码核心**：
     ```cpp
     long long ans=1;
     for( ;n;ans*=2,n>>=1);
     cout<<ans-1;
     ```

---

### 关键思路与技巧
- **位构造法**：将问题转化为二进制位层面的构造，通过最高位确定全1数范围
- **贪心思想**：当允许选多个数时，总能通过两数异或填满低位，无需关心具体组合
- **位运算优化**：通过循环右移/左移快速定位最高位，避免复杂数学运算

---

### 拓展与同类题目
- **类似题目**：
  - P2114 [NOI2014] 起床困难综合症（位运算贪心）
  - P3857 [TJOI2008] 彩灯（线性基求最大异或）
  - P4735 最大异或和（可持久化Trie树应用）

---

### 个人心得摘录
- **调试经验**：注意数据范围必须用long long（BB2655）
- **位运算技巧**：`1LL<<b`可避免int溢出（小坦克）
- **思维突破**：异或最大值不依赖元素数量，而是位模式构造（SoyTony）

---
处理用时：89.48秒