# 题目信息

# Lucky Mask

## 题目描述

Petya loves lucky numbers very much. Everybody knows that lucky numbers are positive integers whose decimal record contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya calls a mask of a positive integer $ n $ the number that is obtained after successive writing of all lucky digits of number $ n $ from the left to the right. For example, the mask of number $ 72174994 $ is number $ 7744 $ , the mask of $ 7 $ is $ 7 $ , the mask of $ 9999047 $ is $ 47 $ . Obviously, mask of any number is always a lucky number.

Petya has two numbers — an arbitrary integer $ a $ and a lucky number $ b $ . Help him find the minimum number $ c $ $ (c&gt;a) $ such that the mask of number $ c $ equals $ b $ .

## 样例 #1

### 输入

```
1 7
```

### 输出

```
7
```

## 样例 #2

### 输入

```
100 47
```

### 输出

```
147
```

# AI分析结果



# Lucky Mask

## 题目描述

Petya 非常喜欢幸运数字。大家都知道，幸运数字是十进制表示中仅包含幸运数字 4 和 7 的正整数。例如，47、744、4 是幸运数字，而 5、17、467 则不是。

Petya 将正整数 n 的掩码定义为从左到右依次写出 n 中所有幸运数字后形成的数。例如，72174994 的掩码是 7744，7 的掩码是 7，9999047 的掩码是 47。显然，任何数的掩码都是幸运数。

给定一个任意整数 a 和一个幸运数 b，请帮 Petya 找到满足条件的最小数字 c（c > a），使得 c 的掩码等于 b。

## 样例 #1

### 输入
```
1 7
```
### 输出
```
7
```

## 样例 #2

### 输入
```
100 47
```
### 输出
```
147
```

---

**算法分类**：枚举

---

### 题解分析与结论
所有题解均采用暴力枚举法，从 a+1 开始逐个检查每个数的掩码是否等于 b。关键在于如何高效生成掩码：多数解法通过逐位取余提取数字，并按原顺序或逆序重组掩码。

---

### 精选题解

#### 1. L_zaa_L（⭐⭐⭐⭐⭐）
**核心亮点**：
- 双反转法生成掩码，巧妙处理数位顺序
- 代码简洁，循环边界明确（i ≤ 177777）
- 时间复杂度分析清晰（最大枚举量约 2e5）

**代码实现**：
```cpp
int pd(long long s) {
    long long x = s, t = 0, h = 0;
    while(x) { // 提取幸运数字并逆序存储
        if(x%10 ==4 || x%10 ==7) h = h*10 + x%10;
        x /= 10;
    }
    while(h) { // 再反转得到正确顺序的掩码
        t = t*10 + h%10;
        h /= 10;
    }
    return t;
}
```

#### 2. Lylighte（⭐⭐⭐⭐）
**核心亮点**：
- 掩码生成函数设计简洁，仅需一次反转
- 使用无限循环配合 break 简化逻辑
- 代码量极小，适合快速实现

**代码实现**：
```cpp
int Make(int x) {
    int ans = 0;
    while(x) {
        if(x%10 ==4 || x%10 ==7) 
            ans = ans*10 + x%10; // 直接逆序生成掩码
        x /= 10;
    }
    return ans; // 返回逆序后的掩码，与预处理过的b比较
}
```

#### 3. alex_liu（⭐⭐⭐）
**优化技巧**：
- 使用快速幂优化数位权重计算
- 特判 b > a 的情况减少计算量
- 位运算加速循环判断

**核心代码**：
```cpp
for(int i=a+1;;i++) {
    int p = i, q = 0, cnt = 0;
    while(p) {
        if(p%10 ==7) q +=7*Pow(10,cnt++); // 正向构建掩码
        if(p%10 ==4) q +=4*Pow(10,cnt++);
        p /= 10;
    }
    if(q == b) return i;
}
```

---

### 关键思路总结
1. **暴力可行性**：最大候选数约 177777（当 b=777777 时），O(n) 枚举可行
2. **掩码生成技巧**：
   - 逆序提取数字后反转（避免字符串操作）
   - 按位权累加法直接构建正向掩码
3. **优化方向**：
   - 预处理 b 的反转形式减少比较次数
   - 特判 b > a 时直接返回 b

---

### 拓展练习
1. [P1217 USACO1.5 回文质数](https://www.luogu.com.cn/problem/P1217) - 枚举与数位处理
2. [P1029 NOIP2001 最大公约数与最小公倍数](https://www.luogu.com.cn/problem/P1029) - 数学性质与枚举优化
3. [P1866 幸运数字](https://www.luogu.com.cn/problem/P1866) - 类似幸运数处理技巧

---
处理用时：53.71秒