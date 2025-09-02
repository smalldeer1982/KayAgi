# 题目信息

# Maximum Sum of Digits

## 题目描述

You are given a positive integer $ n $ .

Let $ S(x) $ be sum of digits in base 10 representation of $ x $ , for example, $ S(123) = 1 + 2 + 3 = 6 $ , $ S(0) = 0 $ .

Your task is to find two integers $ a, b $ , such that $ 0 \leq a, b \leq n $ , $ a + b = n $ and $ S(a) + S(b) $ is the largest possible among all such pairs.

## 说明/提示

In the first example, you can choose, for example, $ a = 17 $ and $ b = 18 $ , so that $ S(17) + S(18) = 1 + 7 + 1 + 8 = 17 $ . It can be shown that it is impossible to get a larger answer.

In the second test example, you can choose, for example, $ a = 5000000001 $ and $ b = 4999999999 $ , with $ S(5000000001) + S(4999999999) = 91 $ . It can be shown that it is impossible to get a larger answer.

## 样例 #1

### 输入

```
35
```

### 输出

```
17
```

## 样例 #2

### 输入

```
10000000000
```

### 输出

```
91
```

# AI分析结果



# Maximum Sum of Digits

## 题目描述
给定一个正整数 $n$。

定义 $S(x)$ 为 $x$ 的十进制各位数字之和，例如 $S(123) = 1+2+3=6$，$S(0)=0$。

要求找到两个非负整数 $a$ 和 $b$，满足 $a+b=n$，且 $S(a)+S(b)$ 最大。输出这个最大的数位和。

## 样例输入输出
### 样例1
输入：  
```
35
```
输出：  
```
17
```

### 样例2
输入：  
```
10000000000
```
输出：  
```
91
```

---

**算法分类**：贪心

---

## 题解分析与结论

### 核心思路
构造一个尽可能多的由数字9组成的数作为 $a$，使得 $a \leq n$，此时 $b = n - a$。这种构造方式能最大化两数的数位和，因为每个9都能贡献最大的单数字值，且避免进位带来的数位和损失。

### 关键技巧
1. **数位构造**：将 $a$ 构造为最高位减1，后续位全填9（例如 $n=35$ 时构造 $a=29$）
2. **全9验证**：通过循环生成全9数，判断是否超过 $n$ 的范围
3. **数位和计算**：分别计算 $a$ 和 $b$ 的各位和相加

---

## 优质题解推荐

### 题解1：alex_liu（★★★★☆）
**关键亮点**：
- 直接构造最高位减1后补9的简洁实现
- 使用逐位处理代替字符串操作，效率更高

**代码核心**：
```cpp
int main(){
    long long n, m, x, a;
    cin >> n;
    m = x = n;
    while(x >= 10) x /= 10;  // 取最高位
    a = x - 1;               // 最高位减1
    while(m) {
        m /= 10;
        a = a * 10 + 9;     // 后续位补9
    }
    a /= 10;                // 修正多补的9
    long long b = n - a;
    // 计算数位和...
}
```

### 题解2：ly618x（★★★★☆）
**关键亮点**：
- 通过循环生成最大全9数的直观实现
- 代码简洁，适合快速理解

**代码核心**：
```cpp
int main(){
    long long n, sum = 0;
    cin >> n;
    while(sum * 10 + 9 <= n) {  // 生成最大全9数
        sum = sum * 10 + 9;
    }
    long long k = n - sum;
    // 计算数位和...
}
```

### 题解3：Sternenlicht（★★★★☆）
**关键亮点**：
- 循环边界处理严谨，确保生成的数不超过n
- 包含数位和的快速计算方法

**代码核心**：
```cpp
int main(){
    long long n, maxn = 0, ans = 0;
    do {
        maxn = maxn * 10 + 9;  // 生成全9数
        ans += 9;
    } while(maxn <= n);
    maxn = (maxn - 9) / 10;    // 回退到合法值
    ans -= 9;
    long long rest = n - maxn;
    // 计算数位和...
}
```

---

## 同类题目推荐
1. [P1012 拼数](https://www.luogu.com.cn/problem/P1012) - 贪心构造数字排列
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心选择最优合并策略
3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995) - 贪心选择跳跃策略

---
处理用时：152.37秒