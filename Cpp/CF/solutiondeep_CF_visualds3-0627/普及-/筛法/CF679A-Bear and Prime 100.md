# 题目信息

# Bear and Prime 100

## 题目描述

This is an interactive problem. In the output section below you will see the information about flushing the output.

Bear Limak thinks of some hidden number — an integer from interval $ [2,100] $ . Your task is to say if the hidden number is prime or composite.

Integer $ x>1 $ is called prime if it has exactly two distinct divisors, $ 1 $ and $ x $ . If integer $ x>1 $ is not prime, it's called composite.

You can ask up to $ 20 $ queries about divisors of the hidden number. In each query you should print an integer from interval $ [2,100] $ . The system will answer "yes" if your integer is a divisor of the hidden number. Otherwise, the answer will be "no".

For example, if the hidden number is $ 14 $ then the system will answer "yes" only if you print $ 2 $ , $ 7 $ or $ 14 $ .

When you are done asking queries, print "prime" or "composite" and terminate your program.

You will get the Wrong Answer verdict if you ask more than $ 20 $ queries, or if you print an integer not from the range $ [2,100] $ . Also, you will get the Wrong Answer verdict if the printed answer isn't correct.

You will get the Idleness Limit Exceeded verdict if you don't print anything (but you should) or if you forget about flushing the output (more info below).

## 说明/提示

The hidden number in the first query is $ 30 $ . In a table below you can see a better form of the provided example of the communication process.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679A/b5d048578748c4adde3d49c36a749660a61701b4.png)

The hidden number is divisible by both $ 2 $ and $ 5 $ . Thus, it must be composite. Note that it isn't necessary to know the exact value of the hidden number. In this test, the hidden number is $ 30 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679A/f54f8d5adb5e9403a147185e0d841ee7fbfd7d7b.png)

 $ 59 $ is a divisor of the hidden number. In the interval $ [2,100] $ there is only one number with this divisor. The hidden number must be $ 59 $ , which is prime. Note that the answer is known even after the second query and you could print it then and terminate. Though, it isn't forbidden to ask unnecessary queries (unless you exceed the limit of $ 20 $ queries).

## 样例 #1

### 输入

```
yes
no
yes
```

### 输出

```
2
80
5
composite
```

## 样例 #2

### 输入

```
no
yes
no
no
no
```

### 输出

```
58
59
78
78
2
prime
```

# AI分析结果



---

## 算法分类
**数学（质数判断与因数分解策略）**

---

## 题解思路与核心难点

### 核心思路
1. **关键观察**：所有 ≤100 的合数至少有一个 ≤50 的质因数。
2. **平方数特判**：形如 $p^2$（如 $4=2^2, 49=7^2$）的合数需额外检测其平方因子。
3. **动态检测策略**：先询问小质数，对每个回答 "yes" 的质数 $p$，若 $p^2 ≤100$ 则追加询问 $p^2$，快速判断重复因子。

### 解决难点
- **平方数漏判**：通过动态检测质数的平方，覆盖单个质因数多次出现的情况。
- **次数限制**：最多 20 次询问，需紧凑设计问题列表。

---

## 题解评分 (≥4星)

1. **lukelin（5星）**
   - **亮点**：动态检测平方因子，代码高效简洁，减少冗余询问。
   - **代码**：通过质数列表+平方检测，快速终止条件判断。

2. **PC_DOS（4星）**
   - **亮点**：预构造包含质数和平方数的问题列表，逻辑直观。
   - **不足**：列表存在冗余（如 4 与 2 的平方重复检测）。

3. **stdout（4星）**
   - **亮点**：清晰的问题列表构造，代码简洁易读。
   - **改进点**：可优化问题列表减少重复询问。

---

## 最优思路与技巧

### 核心技巧
1. **质因数覆盖**：仅需检测 ≤50 的质数，覆盖所有可能的合数。
2. **平方因子动态检测**：对返回 "yes" 的质数 $p$，立即检测 $p^2$，避免漏判。
3. **提前终止**：发现两个及以上 "yes" 时立即输出结果，节省询问次数。

### 实现片段（lukelin 版）
```cpp
for (int i = 0; i < p_num; ++i){
    cout << prime[i] << endl;
    if (回答为 "yes") {
        if (prime[i]^2 ≤100) {
            询问 prime[i]^2;
            if "yes" → 判定合数；
        }
        cnt++;
        if (cnt ≥2) → 判定合数；
    }
}
if (最终 cnt ≤1) → 判定质数；
```

---

## 同类题型推荐
1. **CF679A**（本题）：质数判断与因数分解。
2. **CF1033A**：数学逻辑推理，类似交互策略。
3. **CF947B**：质因数分解与数论分析。

---

## 可视化算法设计

### 动画方案
1. **网格布局**：显示质数列表（绿色方块），动态高亮当前询问的数。
2. **交互反馈**：
   - "yes" 时标记红色，并显示平方检测（黄色方块）。
   - 累计两个红色标记时，触发红色警示动画。
3. **复古像素风格**：
   - 使用 8-bit 音效：询问时播放 "bleep"，正确判定时播放胜利音效。
   - Canvas 绘制质数网格，步进控制速度。

### 控制面板
- **速度调节**：滑块控制询问间隔（100ms~2s）。
- **自动演示**：AI 自动运行，展示最优路径。

---

## 总结
通过质数覆盖与动态平方检测，该算法在 20 次询问内高效判定质数，核心在于数学特性与交互策略的结合。可视化设计可强化对动态检测过程的理解。

---
处理用时：133.13秒