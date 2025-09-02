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



# 题目中文翻译

## 题目名称：改变数组

### 题目描述

Vanya 在教室的黑板上看到一个由 $n$ 个 $k$ 位整数组成的数组 $a_1, a_2, \ldots, a_n$。一个整数 $x$ 被称为 $k$ 位整数，当且仅当 $0 \leq x \leq 2^k - 1$。

Vanya 无法抗拒诱惑，开始修改黑板上的数字。为了不被发现，他只允许进行一种修改操作：选择一个数组下标 $i$（$1 \leq i \leq n$），将数字 $a_i$ 替换为其按位取反的值 $\overline{a_i}$。对于一个 $k$ 位整数 $x$，$\overline{x}$ 定义为与 $x$ 的每一位都不同的 $k$ 位整数。

Vanya 不喜欢数字 $0$。因此，他喜欢满足 $[l, r]$ 区间（$1 \leq l \leq r \leq n$）的异或和不为零的区间，即 $a_l \oplus a_{l+1} \oplus \ldots \oplus a_r \neq 0$（其中 $\oplus$ 表示按位异或运算）。请确定 Vanya 在进行零次或多次操作后，能够获得的最大满足条件的区间数。

### 说明/提示

第一个样例中，若不进行任何操作，数组中有 5 个满足条件的区间。若对 $i=2$ 进行操作，得到数组 $[1, 0, 0]$，此时只有 3 个满足条件的区间。但通过两次操作（$i=3$ 和 $i=2$），可以得到数组 $[1, 0, 3]$，此时满足条件的区间数仍为 5 个。可以证明无法获得 6 个或更多的满足条件的区间。

第二个样例中，进行 4 次操作（$i=3,4,5,6$）后，数组变为 $[1,4,3,0,4,3]$，此时有 19 个满足条件的区间。

### 样例 #1

#### 输入

```
3 2
1 3 0
```

#### 输出

```
5
```

### 样例 #2

#### 输入

```
6 3
1 4 4 7 3 4
```

#### 输出

```
19
```

---

# 题解综合分析与结论

## 核心思路
1. **前缀异或和转换**：将区间异或和问题转化为前缀异或和的数对问题。
2. **正难则反**：计算总区间数减去异或和为0的区间数。
3. **对称性处理**：利用取反操作的对称性，将每个数与其取反值视为等价类，通过统计分组优化计数。
4. **贪心策略**：在线处理时选择当前出现次数较少的分组，最小化冲突。

---

## 高分题解精选

### 1. 灵茶山艾府（★★★★★）
**关键亮点**：
- 数学严谨性：通过公式推导证明最优分组策略
- 高效实现：直接统计最小分组，时间复杂度 $O(n)$
- 代码简洁性：使用最小化映射和组合数公式

**核心代码**：
```go
func main() {
    // ... 输入处理
    cnt := map[int]int{s: 1} // 初始化s[0]
    for ; n > 0; n-- {
        s ^= v // 更新前缀异或和
        key := min(s, s^m)  // 取数与其反值中的较小者
        cnt[key]++
    }
    // 计算总组合数减去冲突组合数
    ans -= c2(c/2) + c2(c-c/2)
}
```

### 2. 花里心爱 & crashed（★★★★）
**共同亮点**：
- 实时贪心策略：每一步选择当前最优分组
- 直观易懂：使用map维护前缀和出现次数
- 空间优化：仅维护当前状态，无需存储历史

**代码片段**：
```cpp
map<int, int> mp;
int pre = 0;
for (int i=1; i<=n; ++i) {
    int nowa = pre ^ a[i];
    int nowb = nowa ^ mask;
    if (mp[nowa] < mp[nowb]) { // 选择出现次数较少的分组
        ans += mp[nowa]++;
        pre = nowa;
    } else {
        ans += mp[nowb]++;
        pre = nowb;
    }
}
```

---

## 最优思路提炼
**关键技巧**：
1. **对称分组法**：将每个前缀异或值 $x$ 和 $x \oplus (2^k-1)$ 视为同一组，统计时取最小值
2. **组合数优化**：每组出现次数 $c$ 的最优贡献为 $\lfloor c/2 \rfloor \times \lceil c/2 \rceil$
3. **零初始化**：初始时需将 $s_0=0$ 加入统计，避免漏算包含第一个元素的区间

**数学推导**：
总区间数 $T = \frac{n(n+1)}{2}$
最优解 = $T - \sum (\lfloor c_i/2 \rfloor \times (\lfloor c_i/2 \rfloor-1)/2 + \lceil c_i/2 \rceil \times (\lceil c_i/2 \rceil-1)/2)$

---

## 拓展学习
**同类问题推荐**：
1. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469) - 异或性质应用
2. [P3401 异或树](https://www.luogu.com.cn/problem/P3401) - 树上前缀异或
3. [P5632 区间异或最大值](https://www.luogu.com.cn/problem/P5632) - 位运算与贪心结合

**调试心得**：
- 注意初始状态：必须初始化 `map[0] = 1`，否则会漏算以第一个元素开头的区间
- 取反运算等价性：同一元素的多次取反会相互抵消，因此每个元素只需考虑操作0/1次
- 类型处理：注意k=0时的边界情况（题目隐含k≥1）

---
处理用时：60.69秒