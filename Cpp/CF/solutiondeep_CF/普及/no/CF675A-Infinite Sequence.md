# 题目信息

# Infinite Sequence

## 题目描述

Vasya likes everything infinite. Now he is studying the properties of a sequence $ s $ , such that its first element is equal to $ a $ ( $ s_{1}=a $ ), and the difference between any two neighbouring elements is equal to $ c $ ( $ s_{i}-s_{i-1}=c $ ). In particular, Vasya wonders if his favourite integer $ b $ appears in this sequence, that is, there exists a positive integer $ i $ , such that $ s_{i}=b $ . Of course, you are the person he asks for a help.

## 说明/提示

In the first sample, the sequence starts from integers $ 1 $ , $ 4 $ , $ 7 $ , so $ 7 $ is its element.

In the second sample, the favorite integer of Vasya is equal to the first element of the sequence.

In the third sample all elements of the sequence are greater than Vasya's favorite integer.

In the fourth sample, the sequence starts from $ 0 $ , $ 50 $ , $ 100 $ , and all the following elements are greater than Vasya's favorite integer.

## 样例 #1

### 输入

```
1 7 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
10 10 0
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
1 -4 5
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
0 60 50
```

### 输出

```
NO
```

# AI分析结果



# Infinite Sequence

## 题目描述

Vasya喜欢无限的事物。现在他正在研究一个序列$s$，其第一个元素等于$a$（$s_1 = a$），且任意两个相邻元素的差等于$c$（$s_i - s_{i-1} = c$）。Vasya想知道他最喜欢的整数$b$是否出现在这个序列中，即是否存在正整数$i$使得$s_i = b$。

## 说明/提示

在第一个样例中，序列以1、4、7开始，因此7是其中的元素。

在第二个样例中，Vasya最喜欢的整数等于序列的第一个元素。

在第三个样例中，所有序列元素都大于Vasya最喜欢的整数。

在第四个样例中，序列以0、50、100开始，后续元素均大于Vasya最喜欢的整数。

---

**算法分类**：数学

---

### 题解综合分析

所有题解均围绕等差数列的数学性质展开，核心思路为：
1. 当公差c=0时，必须满足a=b
2. 当c≠0时，需同时满足：
   - (b-a)能被c整除
   - 步数k=(b-a)/c必须是非负整数（根据c的正负决定a与b的大小关系）

关键难点在于处理正负公差的方向性限制，以及避免除零错误。以下是评分较高的题解：

---

#### 题解作者：TRZ_2007（4星）
**关键亮点**：
- 采用分情况讨论，逻辑层次清晰
- 通过abs(c)统一处理负公差的情况
- 完整覆盖所有边界条件

**核心代码**：
```cpp
if(c == 0) {
    if(a == b) puts("YES");
    else puts("NO");
} else {
    if(c > 0) {
        if(b < a) puts("NO");
        else if((b - a) % c == 0) puts("YES");
    } else {
        if(b > a) puts("NO"); 
        else if((a - b) % abs(c) == 0) puts("YES");
    }
}
```

---

#### 题解作者：Eason_AC（4星）
**关键亮点**：
- 提出两个数学定理的严谨证明
- 使用整除判断和符号判断两步验证
- 代码简洁高效

**核心代码**：
```cpp
if(c == 0) {
    puts(a == b ? "YES" : "NO");
} else if( (b-a)%c == 0 && (b-a)/c >= 0 ) {
    puts("YES");
} else {
    puts("NO");
}
```

---

#### 题解作者：Lucifer_Bartholomew（4星）
**关键亮点**：
- 代码极度简洁（仅6行核心逻辑）
- 使用(b-a)/c>0直接验证非负步数
- 包含个人调试经验分享（WA教训）

**核心代码**：
```cpp
if(!c) puts(a==b ? "YES" : "NO");
else if(a==b || ( (b-a)%c==0 && (b-a)/c>0 )) puts("YES");
else puts("NO");
```

---

### 最优解题思路
1. **符号方向判断**：根据公差c的正负确定b相对于a的位置关系
2. **整除性验证**：通过(b-a) % c == 0验证存在性
3. **非负步数验证**：通过计算步数k=(b-a)/c ≥0 保证项数合法

### 拓展应用
此类型问题可延伸至：
- 等比数列存在性判断（需处理除零和符号）
- 多元一次方程整数解问题
- 循环节存在性判断（如P类问题）

---

### 推荐练习
1. [P1035 等差数列求和](https://www.luogu.com.cn/problem/P1035)  
   （等差数列性质应用）
2. [P1304 字符串的序号](https://www.luogu.com.cn/problem/P1304)  
   （数学递推与模运算）
3. [P2249 查找](https://www.luogu.com.cn/problem/P2249)  
   （有序序列存在性判断进阶）

---
处理用时：49.76秒