# 题目信息

# Elections

## 题目描述

Awruk is taking part in elections in his school. It is the final round. He has only one opponent — Elodreip. The are $ n $ students in the school. Each student has exactly $ k $ votes and is obligated to use all of them. So Awruk knows that if a person gives $ a_i $ votes for Elodreip, than he will get exactly $ k - a_i $ votes from this person. Of course $ 0 \le k - a_i $ holds.

Awruk knows that if he loses his life is over. He has been speaking a lot with his friends and now he knows $ a_1, a_2, \dots, a_n $ — how many votes for Elodreip each student wants to give. Now he wants to change the number $ k $ to win the elections. Of course he knows that bigger $ k $ means bigger chance that somebody may notice that he has changed something and then he will be disqualified.

So, Awruk knows $ a_1, a_2, \dots, a_n $ — how many votes each student will give to his opponent. Help him select the smallest winning number $ k $ . In order to win, Awruk needs to get strictly more votes than Elodreip.

## 说明/提示

In the first example, Elodreip gets $ 1 + 1 + 1 + 5 + 1 = 9 $ votes. The smallest possible $ k $ is $ 5 $ (it surely can't be less due to the fourth person), and it leads to $ 4 + 4 + 4 + 0 + 4 = 16 $ votes for Awruk, which is enough to win.

In the second example, Elodreip gets $ 11 $ votes. If $ k = 4 $ , Awruk gets $ 9 $ votes and loses to Elodreip.

## 样例 #1

### 输入

```
5
1 1 1 5 1
```

### 输出

```
5```

## 样例 #2

### 输入

```
5
2 2 3 2 2
```

### 输出

```
5```

# AI分析结果



## 中文重写题目

### 选举

## 题目描述

Awruk 正在参加学校的最后一轮选举，他唯一的对手是 Elodreip。学校共有 $n$ 名学生，每名学生有恰好 $k$ 张选票且必须全部投出。已知第 $i$ 名学生会投 $a_i$ 票给 Elodreip，那么 Awruk 将获得 $k - a_i$ 票。显然需要满足 $0 \le k - a_i$。

Awruk 想通过调整 $k$ 的值确保自己获胜（总票数严格多于 Elodreip），同时希望 $k$ 尽可能小以避免被发现篡改数据。请帮他计算最小的获胜 $k$ 值。

## 说明/提示

样例1中 Elodreip 总票数为9，当 $k=5$ 时 Awruk 获得16票获胜。样例2中若 $k=4$ 则 Awruk 得9票仍会失败。

## 样例 #1

### 输入
```
5
1 1 1 5 1
```

### 输出
```
5
```

## 样例 #2

### 输入
```
5
2 2 3 2 2
```

### 输出
```
5
```

---

**算法分类**  
数学

---

## 题解对比与结论

### 最优题解（评分4星及以上）

#### Node_Edge 题解（⭐️⭐️⭐️⭐️⭐️）
**关键亮点**  
1. 数学推导得出核心公式：$k = \max(\max a_i, \lceil \frac{2\sum a_i}{n} \rceil)$  
2. 代码简洁高效（时间复杂度 $O(n)$）  
3. 正确处理整除与非整除情况的统一表达式  

**核心代码**  
```cpp
int sum = 0, max_a = 0;
for (int i = 0; i < n; i++) {
    cin >> a[i];
    sum += a[i];
    max_a = max(max_a, a[i]);
}
cout << max(max_a, sum * 2 / n + 1);
```

#### Eason_AC 题解（⭐️⭐️⭐️⭐️）
**关键亮点**  
1. 相同数学思路但更详细的不等式推导  
2. 代码结构清晰，变量命名规范  

**核心代码**  
```cpp
int sum = 0, max_a = 0;
for (int i = 1; i <= n; i++) {
    sum += a[i];
    max_a = max(max_a, a[i]);
}
int k = max(2 * sum / n + 1, max_a);
```

#### liuyz11 题解（⭐️⭐️⭐️⭐️）
**关键亮点**  
1. 明确强调 $k \geq \max a_i$ 的边界条件  
2. 通过实际调试经历提醒常见错误  

**核心代码**  
```cpp
if (2 * sum / n + 1 < max_a) 
    cout << max_a;
else 
    cout << 2 * sum / n + 1;
```

---

## 关键思路总结

1. **数学建模**：通过不等式 $n \cdot k > 2 \sum a_i$ 推导理论最小值 $k_0 = \lceil \frac{2 \sum a_i}{n} \rceil$  
2. **双重约束**：最终 $k$ 必须同时满足 $k \geq \max a_i$ 和 $k \geq k_0$  
3. **整数运算技巧**：利用 `sum * 2 / n + 1` 替代浮点运算，统一处理余数问题  

**调试经验**：务必验证 $k$ 是否满足 $\geq \max a_i$，否则会因单个学生投票数超过 $k$ 而失败。

---

## 类似题目推荐

1. [P1089 津津的储蓄计划](https://www.luogu.com.cn/problem/P1089) - 条件判断与数学模拟  
2. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045) - 数学计算与边界处理  
3. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029) - 数学推导与约束条件结合

---
处理用时：194.54秒