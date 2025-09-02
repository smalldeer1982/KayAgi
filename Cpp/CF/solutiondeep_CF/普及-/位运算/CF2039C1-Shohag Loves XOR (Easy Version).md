# 题目信息

# Shohag Loves XOR (Easy Version)

## 题目描述

This is the easy version of the problem. The differences between the two versions are highlighted in bold. You can only make hacks if both versions of the problem are solved.

Shohag has two integers $ x $ and $ m $ . Help him count the number of integers $ 1 \le y \le m $ such that $ \mathbf{x \neq y} $ and $ x \oplus y $ is a divisor $ ^{\text{∗}} $ of either $ x $ , $ y $ , or both. Here $ \oplus $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operator.

 $ ^{\text{∗}} $ The number $ b $ is a divisor of the number $ a $ if there exists an integer $ c $ such that $ a = b \cdot c $ .

## 说明/提示

In the first test case, for $ x = 6 $ , there are $ 3 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 9 $ , and they are $ 4 $ , $ 5 $ , and $ 7 $ .

- $ y = 4 $ is valid because $ x \oplus y = 6 \oplus 4 = 2 $ and $ 2 $ is a divisor of both $ x = 6 $ and $ y = 4 $ .
- $ y = 5 $ is valid because $ x \oplus y = 6 \oplus 5 = 3 $ and $ 3 $ is a divisor of $ x = 6 $ .
- $ y = 7 $ is valid because $ x \oplus y = 6 \oplus 7 = 1 $ and $ 1 $ is a divisor of both $ x = 6 $ and $ y = 7 $ .

In the second test case, for $ x = 5 $ , there are $ 2 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 7 $ , and they are $ 4 $ and $ 6 $ .

- $ y = 4 $ is valid because $ x \oplus y = 5 \oplus 4 = 1 $ and $ 1 $ is a divisor of both $ x = 5 $ and $ y = 4 $ .
- $ y = 6 $ is valid because $ x \oplus y = 5 \oplus 6 = 3 $ and $ 3 $ is a divisor of $ y = 6 $ .

## 样例 #1

### 输入

```
5
6 9
5 7
2 3
6 4
4 1```

### 输出

```
3
2
1
1
0```

# AI分析结果

### 题目中文重写
# Shohag 喜欢异或（简单版本）

## 题目描述
这是该问题的简单版本。两个版本之间的差异用**粗体**突出显示。只有当两个版本的问题都解决后，你才能进行 Hack 操作。

Shohag 有两个整数 $x$ 和 $m$。请帮助他计算满足以下条件的整数 $y$ 的数量：$1 \leq y \leq m$，且 $\mathbf{x \neq y}$，同时 $x \oplus y$ 是 $x$、$y$ 其中之一或两者的因数。这里 $\oplus$ 是[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)运算符。

$^{\text{∗}}$ 若存在整数 $c$ 使得 $a = b \cdot c$，则称数 $b$ 是数 $a$ 的因数。

## 说明/提示
在第一个测试用例中，对于 $x = 6$，在 $1$ 到 $m = 9$ 的整数中，有 $3$ 个有效的 $y$ 值，分别是 $4$、$5$ 和 $7$。
- $y = 4$ 有效，因为 $x \oplus y = 6 \oplus 4 = 2$，且 $2$ 是 $x = 6$ 和 $y = 4$ 的因数。
- $y = 5$ 有效，因为 $x \oplus y = 6 \oplus 5 = 3$，且 $3$ 是 $x = 6$ 的因数。
- $y = 7$ 有效，因为 $x \oplus y = 6 \oplus 7 = 1$，且 $1$ 是 $x = 6$ 和 $y = 7$ 的因数。

在第二个测试用例中，对于 $x = 5$，在 $1$ 到 $m = 7$ 的整数中，有 $2$ 个有效的 $y$ 值，分别是 $4$ 和 $6$。
- $y = 4$ 有效，因为 $x \oplus y = 5 \oplus 4 = 1$，且 $1$ 是 $x = 5$ 和 $y = 4$ 的因数。
- $y = 6$ 有效，因为 $x \oplus y = 5 \oplus 6 = 3$，且 $3$ 是 $y = 6$ 的因数。

## 样例 #1
### 输入
```
5
6 9
5 7
2 3
6 4
4 1
```
### 输出
```
3
2
1
1
0
```

### 综合分析与结论
这些题解的核心目标都是缩小 $y$ 的枚举范围，避免直接枚举 $y$ 从 $1$ 到 $m$ 带来的超时问题。

- **思路对比**：多数题解从二进制位数、因数性质、异或运算特性等方面入手，证明当 $y \geq 2x$ 时，$x \oplus y$ 不可能是 $x$ 或 $y$ 的因数，从而将枚举范围缩小到 $[1, \min(2x, m)]$。部分题解还从二进制最高位的角度进行分析。
- **算法要点**：通过数学推理得出 $y$ 的有效枚举范围，然后在该范围内枚举 $y$，计算 $x \oplus y$，判断其是否为 $x$ 或 $y$ 的因数，统计满足条件的 $y$ 的数量。
- **解决难点**：关键在于如何证明当 $y$ 超过一定范围时，$x \oplus y$ 不满足是 $x$ 或 $y$ 的因数这一条件。不同题解采用了不同的证明方法，如从二进制位数、因数大小关系等角度进行分析。

### 所选题解
- **作者：SUNCHAOYI（5星）**
    - **关键亮点**：思路清晰，先给出结论猜测并进行证明，代码规范，注释详细。
    - **核心代码**：
```cpp
t = read ();
while (t--)
{
    ll x = read (),m = read ();
    ll cnt = 0;
    for (int i = 1;i <= x;++i)
    {
        ll y = x ^ i;
        if (!(1 <= y && y <= m)) continue;
        if (x % (x ^ y) == 0 || y % (x ^ y) == 0) ++cnt;
    }
    printf ("%lld\n",cnt);
}
```
核心实现思想：先读取输入的 $x$ 和 $m$，然后枚举 $i$ 从 $1$ 到 $x$，计算 $y = x ^ i$，判断 $y$ 是否在 $[1, m]$ 范围内，若在则判断 $x \oplus y$ 是否为 $x$ 或 $y$ 的因数，若是则计数器加 1。

- **作者：Fiendish（4星）**
    - **关键亮点**：分情况详细讨论 $y$ 的位数与 $x$ 的位数关系，证明过程严谨，代码简洁。
    - **核心代码**：
```cpp
while(T--){
    ans=0;
    cin>>x>>m;
    for(int i=1;i<min((1ll<<((int)__lg(x)+1)),m+1);i++)
        if(i!=x&&(x%(i^x)==0||i%(i^x)==0)) ans++;
    cout<<ans<<'\n';
}
```
核心实现思想：读取输入的 $x$ 和 $m$，枚举 $i$ 从 $1$ 到 $\min(2^{\lfloor\log_2 x\rfloor + 1}, m + 1)$，判断 $i$ 是否不等于 $x$ 且 $x \oplus i$ 是否为 $x$ 或 $i$ 的因数，若是则计数器加 1。

- **作者：Limerency（4星）**
    - **关键亮点**：通过证明 $f(x) = f(y)$（$f(p)$ 为 $p$ 的二进制位数），缩小枚举范围，代码逻辑清晰。
    - **核心代码**：
```cpp
cin >> x >> m;
int hb = 1, p = x, ans = 0;
while (p) p >>= 1, hb <<= 1;
int lm = min(hb - 1ll, m);
for (int i = hb >> 1; i <= lm; i ++) {
    int t = (x ^ i);
    if (x!= i) if (x % t == 0 || i % t == 0) ans ++;
}
cout << ans << '\n';
```
核心实现思想：读取输入的 $x$ 和 $m$，计算 $x$ 的二进制最高位对应的数值 $hb$，确定枚举范围为 $[\frac{hb}{2}, \min(hb - 1, m)]$，在该范围内枚举 $i$，计算 $x \oplus i$，判断其是否为 $x$ 或 $i$ 的因数，若是则计数器加 1。

### 最优关键思路或技巧
- **缩小枚举范围**：通过数学推理，从二进制位数、因数性质、异或运算特性等方面证明当 $y \geq 2x$ 时，$x \oplus y$ 不可能是 $x$ 或 $y$ 的因数，从而将枚举范围缩小到 $[1, \min(2x, m)]$，降低时间复杂度。
- **二进制分析**：从二进制的角度分析异或运算和因数的关系，如最高位的变化、位数的比较等，有助于简化问题。

### 可拓展之处
同类型题或类似算法套路：
- 涉及位运算和因数判断的题目，可尝试从二进制的角度分析问题，缩小枚举范围。
- 对于数据范围较大的枚举问题，可通过数学推理找到有效范围，避免暴力枚举。

### 推荐洛谷题目
- P1886 滑动窗口 /【模板】单调队列
- P1168 中位数
- P1908 逆序对

### 个人心得摘录与总结
- **作者：Binah_cyc**：赛时可通过观察样例和打表来猜测结论，先保证通过题目，后续再进行严谨证明。在不确定枚举范围时，可适当扩大范围以增加通过的概率。 

---
处理用时：40.29秒