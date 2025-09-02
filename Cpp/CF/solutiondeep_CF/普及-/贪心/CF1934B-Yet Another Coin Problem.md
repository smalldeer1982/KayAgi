# 题目信息

# Yet Another Coin Problem

## 题目描述

You have $ 5 $ different types of coins, each with a value equal to one of the first $ 5 $ triangular numbers: $ 1 $ , $ 3 $ , $ 6 $ , $ 10 $ , and $ 15 $ . These coin types are available in abundance. Your goal is to find the minimum number of these coins required such that their total value sums up to exactly $ n $ .

We can show that the answer always exists.

## 说明/提示

In the first test case, for $ n = 1 $ , the answer is $ 1 $ since only one $ 1 $ value coin is sufficient. $ 1 = 1 \cdot 1 $ .

In the fourth test case, for $ n = 5 $ , the answer is $ 3 $ , which can be achieved using two $ 1 $ value coins and one $ 3 $ value coin. $ 5 = 2 \cdot 1 + 1 \cdot 3 $ .

In the seventh test case, for $ n = 12 $ , the answer is $ 2 $ , which can be achieved using two $ 6 $ value coins.

In the ninth test case, for $ n = 16 $ , the answer is $ 2 $ , which can be achieved using one $ 1 $ value coin and one $ 15 $ value coin or using one $ 10 $ value coin and one $ 6 $ value coin. $ 16 = 1 \cdot 1 + 1 \cdot 15 = 1 \cdot 6 + 1 \cdot 10 $ .

## 样例 #1

### 输入

```
14
1
2
3
5
7
11
12
14
16
17
18
20
98
402931328```

### 输出

```
1
2
1
3
2
2
2
3
2
3
2
2
8
26862090```

# AI分析结果



# Yet Another Coin Problem

## 题目描述

你有 $5$ 种不同面值的硬币，其面值分别为前 $5$ 个三角形数：$1$、$3$、$6$、$10$ 和 $15$。每种硬币数量无限。你需要用最少的硬币组合出恰好为 $n$ 的金额。答案保证存在。

## 样例 #1

### 输入
```
14
1
2
3
5
7
11
12
14
16
17
18
20
98
402931328
```

### 输出
```
1
2
1
3
2
2
2
3
2
3
2
2
8
26862090
```

---

## 题解分析与结论

### 核心思路总结
通过数学分析限制较小面值硬币的使用上限（如 $1$ 元硬币最多 $2$ 个），暴力枚举这些硬币的组合，剩余金额用 $15$ 元硬币处理。时间复杂度为 $O(1)$，每个测试用例只需约 $3 \times 2 \times 5 \times 3 = 90$ 次枚举。

### 高星题解推荐

#### 1. __Dist__（5星）
**关键亮点**  
- 通过数学推导严格限制各面值硬币的最大使用数量  
- 四重循环枚举前四类硬币的组合，剩余部分用 $15$ 元处理  
- 代码简洁高效，完全覆盖所有可能情况  

**核心代码**  
```cpp
for (int a=0; a<=2; a++)
    for (int b=0; b<=1; b++)
        for (int c=0; c<=4; c++)
            for (int d=0; d<=2; d++) {
                int e = n - a - 3*b - 6*c - 10*d;
                if (e >= 0 && e%15 == 0)
                    ans = min(ans, a+b+c+d + e/15);
            }
```

#### 2. 2022_37_yzyUUU（5星）
**关键亮点**  
- 直接枚举所有可能的组合，逻辑清晰  
- 严格验证剩余金额能被 $15$ 整除  
- 通过极简代码实现最优解计算  

**个人心得**  
> "枚举硬币数目时从 $0$ 开始，注意边界判断，例如余数不能为负。"

#### 3. Stars_visitor_tyw（5星）
**关键亮点**  
- 预处理各硬币的数学上限（如 $6$ 元最多 $4$ 个）  
- 使用四重循环枚举组合，剩余部分交给最大面值  
- 时间复杂度严格受控，适合大范围输入  

**核心代码**  
```cpp
for (int i=0; i<=2; i++)
    for (int j=0; j<=1; j++)
        for (int k=0; k<=4; k++)
            for (int m=0; m<=2; m++) {
                int tmp = i + j*3 + k*6 + m*10;
                if (n-tmp >= 0 && (n-tmp)%15 == 0)
                    ans = min(ans, i+j+k+m + (n-tmp)/15);
            }
```

### 拓展思路
类似问题可通过分析硬币面值的数学特性，将大范围问题转化为有限枚举。例如若面值成等比数列，可优先使用大面值；若存在互质关系，可用扩展欧几里得算法。

### 推荐练习题
1. [P2925 硬币组合](https://www.luogu.com.cn/problem/P2925)  
2. [P4544 购买饲料](https://www.luogu.com.cn/problem/P4544)  
3. [P2563 质数和分解](https://www.luogu.com.cn/problem/P2563)

---
处理用时：141.78秒