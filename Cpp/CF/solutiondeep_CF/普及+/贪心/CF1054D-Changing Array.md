# 题目信息

# Changing Array

## 题目描述

At a break Vanya came to the class and saw an array of $ n $ $ k $ -bit integers $ a_1, a_2, \ldots, a_n $ on the board. An integer $ x $ is called a $ k $ -bit integer if $ 0 \leq x \leq 2^k - 1 $ .

Of course, Vanya was not able to resist and started changing the numbers written on the board. To ensure that no one will note anything, Vanya allowed himself to make only one type of changes: choose an index of the array $ i $ ( $ 1 \leq i \leq n $ ) and replace the number $ a_i $ with the number $ \overline{a_i} $ . We define $ \overline{x} $ for a $ k $ -bit integer $ x $ as the $ k $ -bit integer such that all its $ k $ bits differ from the corresponding bits of $ x $ .

Vanya does not like the number $ 0 $ . Therefore, he likes such segments $ [l, r] $ ( $ 1 \leq l \leq r \leq n $ ) such that $ a_l \oplus a_{l+1} \oplus \ldots \oplus a_r \neq 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Determine the maximum number of segments he likes Vanya can get applying zero or more operations described above.

## 说明/提示

In the first example if Vasya does not perform any operations, he gets an array that has $ 5 $ segments that Vanya likes. If he performs the operation with $ i = 2 $ , he gets an array $ [1, 0, 0] $ , because $ \overline{3} = 0 $ when $ k = 2 $ . This array has $ 3 $ segments that Vanya likes. Also, to get an array with $ 5 $ segments that Vanya likes, he can perform two operations with $ i = 3 $ and with $ i = 2 $ . He then gets an array $ [1, 0, 3] $ . It can be proven that he can't obtain $ 6 $ or more segments that he likes.

In the second example, to get $ 19 $ segments that Vanya likes, he can perform $ 4 $ operations with $ i = 3 $ , $ i = 4 $ , $ i = 5 $ , $ i = 6 $ and get an array $ [1, 4, 3, 0, 4, 3] $ .

## 样例 #1

### 输入

```
3 2
1 3 0
```

### 输出

```
5```

## 样例 #2

### 输入

```
6 3
1 4 4 7 3 4
```

### 输出

```
19```

# AI分析结果



# Changing Array 题目中文翻译

## 题目描述

Vanya 来到教室，看到黑板上写着一个由 $n$ 个 $k$ 位整数组成的数组 $a_1, a_2, \ldots, a_n$。这里的 $k$ 位整数定义为满足 $0 \leq x \leq 2^k - 1$ 的整数。

Vanya 忍不住要修改这些数字。他只能进行一种类型的操作：选择数组的某个索引 $i$（$1 \leq i \leq n$），将 $a_i$ 替换为 $\overline{a_i}$。其中 $\overline{x}$ 定义为将 $x$ 的所有 $k$ 位二进制位取反后得到的数（例如，$x = 3$ 的二进制是 11，取反后为 00，即 $\overline{3} = 0$）。

Vanya 不喜欢数字 $0$，因此他希望最大化满足 $a_l \oplus a_{l+1} \oplus \ldots \oplus a_r \neq 0$ 的区间 $[l, r]$ 的数量。请求出经过若干次操作后，他能够获得的最大满足条件的区间数。

## 样例 #1

### 输入
```
3 2
1 3 0
```

### 输出
```
5
```

## 样例 #2

### 输入
```
6 3
1 4 4 7 3 4
```

### 输出
```
19
```

---

# 题解综合分析

## 核心思路
1. **前缀异或和转换**：将区间异或和问题转化为前缀异或和的配对问题。设前缀异或和数组 $s$，则区间 $[l, r]$ 的异或和为 $s_r \oplus s_{l-1}$。当且仅当 $s_r = s_{l-1}$ 时异或和为 0。
2. **正难则反**：总区间数为 $\frac{n(n+1)}{2}$，减去异或和为 0 的区间数即为答案。
3. **操作等效性**：修改 $a_i$ 等价于将后续所有 $s_j (j \geq i)$ 异或 $2^k-1$。每个 $s_i$ 可以看作可切换为 $s_i$ 或 $s_i \oplus (2^k-1)$。
4. **贪心策略**：对于每个前缀和 $s_i$，统计其本身和异或后的出现次数，始终选择出现次数更少的版本，以最小化重复配对数。

---

## 精选题解（评分≥4星）

### 灵茶山艾府（5星）
**亮点**：数学建模清晰，代码简洁高效，组合数优化公式推导严谨。
```go
func main() {
    // 统计异或前缀和的最小化形式
    cnt := map[int]int{s: 1}
    for ; n > 0; n-- {
        s ^= v
        cnt[min(s, s^m)]++ // 将s和s^mask视为等价类
    }
    // 计算总组合数减去冲突数
    ans := c2(n+1)
    for _, c := range cnt {
        ans -= c2(c/2) + c2(c-c/2)
    }
}
```

### 花里心爱（4星）
**亮点**：动态贪心策略，即时选择最优版本，代码可读性强。
```cpp
if(mp[nowa] < mp[nowb]) {
    ans += (mp[nowa]++); // 选择出现次数少的版本
    pre = nowa;
} else {
    ans += (mp[nowb]++);
    pre = nowb;
}
```

### crashed（4星）
**亮点**：详细数学推导均分策略的正确性，代码结构清晰。
```cpp
if(mp[fir] < mp[sec]) res += mp[pXor = fir]++;
else res += mp[pXor = sec]++;
```

---

## 关键思路总结
1. **前缀异或和的等价类分组**：将每个前缀和与其异或掩码后的值视为同一组，通过统计最小化形式来统一处理。
2. **均分策略优化组合数**：对于每组出现次数 $c$，按均分原则（$\lfloor c/2 \rfloor$ 和 $\lceil c/2 \rceil$）计算最小冲突数。
3. **动态贪心维护最优状态**：每一步选择当前前缀和的版本（原值或异或后），使得全局重复数对最少。

---

## 拓展练习
1. **前缀和+哈希表应用**：[P3131 Subsequences Summing to Sevens](https://www.luogu.com.cn/problem/P3131)
2. **异或性质与贪心**：[P3503 KAM-Pebbles](https://www.luogu.com.cn/problem/P3503)
3. **动态维护最优状态**：[P3403 跳楼机](https://www.luogu.com.cn/problem/P3403)

---
处理用时：64.01秒