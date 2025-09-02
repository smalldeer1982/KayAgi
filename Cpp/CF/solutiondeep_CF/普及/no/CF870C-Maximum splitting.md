# 题目信息

# Maximum splitting

## 题目描述

You are given several queries. In the $ i $ -th query you are given a single positive integer $ n_{i} $ . You are to represent $ n_{i} $ as a sum of maximum possible number of composite summands and print this maximum number, or print -1, if there are no such splittings.

An integer greater than $ 1 $ is composite, if it is not prime, i.e. if it has positive divisors not equal to $ 1 $ and the integer itself.

## 说明/提示

 $ 12=4+4+4=4+8=6+6=12 $ , but the first splitting has the maximum possible number of summands.

 $ 8=4+4 $ , $ 6 $ can't be split into several composite summands.

 $ 1,2,3 $ are less than any composite number, so they do not have valid splittings.

## 样例 #1

### 输入

```
1
12
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
6
8
```

### 输出

```
1
2
```

## 样例 #3

### 输入

```
3
1
2
3
```

### 输出

```
-1
-1
-1
```

# AI分析结果



# Maximum splitting

## 题目描述

给定多个查询，每个查询给出一个正整数 $n_i$。要求将 $n_i$ 表示为尽可能多的合数之和，输出最大数量，若无法表示则输出 -1。

合数是指大于 1 的非质数。

## 说明/提示

 $12=4+4+4$ 是最优解（3个合数），而 $6$ 无法拆分成多个合数之和。

 $1,2,3$ 小于最小合数，无法拆分。

## 样例 #1

### 输入

```
1
12
```

### 输出

```
3
```

---

**算法分类**：贪心

---

## 题解综合分析

所有题解均基于贪心策略，核心思路为：优先使用最小合数4进行分解，处理余数并处理特殊值。关键差异在于余数处理方式和特殊情况的判断逻辑。

### 最优题解推荐

1. **Super_Cube（5星）**
   **关键亮点**：
   - 通过奇偶性统一处理余数情况
   - 位运算优化计算（`n>>2`等价于`n/4`，`n&1`判断奇偶）
   - 代码极其简洁（仅8行核心逻辑）
   **代码核心**：
   ```cpp
   printf("%d\n", (n>>2)-(n&1));  // 奇数答案等价于 n/4-1
   ```

2. **_Qer（4星）**
   **关键亮点**：
   - 显式处理奇数情况（减9后转为偶数）
   - 清晰的余数分类讨论
   **代码核心**：
   ```cpp
   if (n & 1) {
       ++ans, n -= 9;  // 奇数先减9
   }
   ans += n / 4;  // 剩余部分全拆4
   ```

3. **seanlsy（4星）**
   **关键亮点**：
   - 直接按余数类型分类计算
   - 特殊处理余数1/3的情况
   **代码核心**：
   ```cpp
   if(!(n&3)) printf("%d\n",n<4?-1:(n>>2));       // 余0
   else if((n&3)==1) printf("%d\n",n<9?-1:((n-9)>>2)+1); // 余1
   ```

---

## 关键思路总结

1. **贪心核心**：优先使用最小合数4进行分解
2. **奇数处理**：奇数需先减9（最小奇合数），转为偶数后再处理
3. **余数优化**：
   - 余0/2时直接拆分为4的倍数（余2时合并为6）
   - 余1/3时通过减9/15调整余数
4. **特例排除**：需单独处理5/7/11等无法拆解的数值

---

## 相似题目推荐

1. [P1107 最大整数](https://www.luogu.com.cn/problem/P1107)（贪心构造）
2. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)（贪心策略）
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心+优先队列）

---
处理用时：66.67秒