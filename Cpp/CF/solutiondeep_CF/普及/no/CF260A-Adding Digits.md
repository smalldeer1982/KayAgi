# 题目信息

# Adding Digits

## 题目描述

Vasya has got two number: $ a $ and $ b $ . However, Vasya finds number $ a $ too short. So he decided to repeat the operation of lengthening number $ a $ $ n $ times.

One operation of lengthening a number means adding exactly one digit to the number (in the decimal notation) to the right provided that the resulting number is divisible by Vasya's number $ b $ . If it is impossible to obtain the number which is divisible by $ b $ , then the lengthening operation cannot be performed.

Your task is to help Vasya and print the number he can get after applying the lengthening operation to number $ a\ n $ times.

## 样例 #1

### 输入

```
5 4 5
```

### 输出

```
524848
```

## 样例 #2

### 输入

```
12 11 1
```

### 输出

```
121
```

## 样例 #3

### 输入

```
260 150 10
```

### 输出

```
-1
```

# AI分析结果



# 添加数字

## 题目描述

Vasya 有两个数字 $a$ 和 $b$。他觉得 $a$ 太短了，于是决定进行 $n$ 次延长操作。每次操作需要在数字末尾添加一个数字，使得新数字能被 $b$ 整除。若无法完成操作则输出 -1。

## 样例

（保持原样不变）

---

**算法分类**：构造

---

### 题解综合分析

各题解核心思路高度一致：首次枚举添加的个位数（0-9），找到满足条件后补零。关键数学原理是若 $a \equiv 0 \mod b$，则 $a \times 10^k \equiv 0 \mod b$。因此只需确保第一次添加后的数字合法，后续可全补零。

---

### 精选题解

#### 1. PragmaGCC（★★★★☆）
**亮点**：  
- 代码结构最简洁，注释清晰  
- 直接输出构造结果，无冗余变量  
**核心代码**：
```cpp
for (int i = 0; i <= 9; i++) {
    int x = 10 * a + i;
    if (x % b == 0) {
        printf("%d", x);
        for (int j = 1; j <= n - 1; j++) printf("0");
        return 0;
    }
}
```

#### 2. David_H_（★★★★☆）  
**亮点**：  
- 变量命名规范，逻辑层次分明  
- 使用 `!` 运算符简化条件判断  
**核心代码**：
```cpp
if (!((a * 10 + i) % b)) {
    cout << a * 10 + i;
    for (int j = 0; j < n - 1; j++) cout << "0";
    return 0;
}
```

#### 3. TLMPEX（★★★★☆）  
**亮点**：  
- 使用标志变量 `t` 处理边界情况  
- 逐步构建结果而非拼接字符串  
**个人心得**：  
> "一个数乘10除以一个数的余数是不变的" —— 准确抓住数学性质

---

### 关键思路
**余数不变原理**：若首次添加数字 $i$ 得到 $a' = 10a+i \equiv 0 \mod b$，则后续每次添加0时，$a' \times 10^k \equiv 0 \mod b$ 必然成立。因此只需解决首次构造问题。

---

### 拓展应用
类似构造问题常见于以下场景：  
1. 数字拼接后满足特定模数条件  
2. 利用余数性质构造递推式  
3. 固定部分结构后填充固定模式（如全零）

---

### 推荐习题
1. [P1012 拼数](https://www.luogu.com.cn/problem/P1012) - 构造最大拼接数  
2. [CF1294F 三个构造点](https://codeforces.com/problemset/problem/1294/F) - 树结构构造  
3. [P2001 硬币面值](https://www.luogu.com.cn/problem/P2001) - 数学构造解

---
处理用时：85.10秒