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

注：如果存在整数 $c$ 使得 $a = b \cdot c$，则称 $b$ 是 $a$ 的因数。

## 说明/提示
在第一个测试用例中，当 $x = 6$ 时，在 $1$ 到 $m = 9$ 的整数中，有 $3$ 个有效的 $y$ 值，分别是 $4$、$5$ 和 $7$。
- $y = 4$ 是有效的，因为 $x \oplus y = 6 \oplus 4 = 2$，且 $2$ 是 $x = 6$ 和 $y = 4$ 的因数。
- $y = 5$ 是有效的，因为 $x \oplus y = 6 \oplus 5 = 3$，且 $3$ 是 $x = 6$ 的因数。
- $y = 7$ 是有效的，因为 $x \oplus y = 6 \oplus 7 = 1$，且 $1$ 是 $x = 6$ 和 $y = 7$ 的因数。

在第二个测试用例中，当 $x = 5$ 时，在 $1$ 到 $m = 7$ 的整数中，有 $2$ 个有效的 $y$ 值，分别是 $4$ 和 $6$。
- $y = 4$ 是有效的，因为 $x \oplus y = 5 \oplus 4 = 1$，且 $1$ 是 $x = 5$ 和 $y = 4$ 的因数。
- $y = 6$ 是有效的，因为 $x \oplus y = 5 \oplus 6 = 3$，且 $3$ 是 $y = 6$ 的因数。

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
这些题解的核心目标都是缩小 $y$ 的枚举范围，避免直接枚举 $[1, m]$ 导致超时。不同题解从不同角度进行分析：
- **二进制位数角度**：Fiendish、Limerency、Dangerise 从二进制位数出发，证明了 $y$ 的二进制位数不超过 $x$ 的二进制位数，从而缩小枚举范围。
- **因数性质角度**：SUNCHAOYI、_lmh_、postpone、sbno333 利用因数的性质，证明当 $y \geq 2x$ 时，$x \oplus y$ 不可能是 $x$ 或 $y$ 的因数，进而将枚举范围缩小到 $[1, \min(2x, m)]$。
- **赛时技巧角度**：Binah_cyc 通过观察样例和打表，先确定大致范围，再进行严谨证明。

### 所选题解
- **作者：SUNCHAOYI（5星）**
    - **关键亮点**：思路清晰，先给出结论猜测并进行证明，代码结构规范，注释详细。
    - **核心代码**：
```cpp
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
    - **核心实现思想**：先证明只有 $y < 2x$ 时才可能满足题意，即 $x \oplus y < x$。然后枚举 $i$ 从 $1$ 到 $x$，计算 $y = x ^ i$，判断 $y$ 是否在 $[1, m]$ 范围内，且 $x \oplus y$ 是否是 $x$ 或 $y$ 的因数，若是则计数器加 1。
- **作者：Fiendish（5星）**
    - **关键亮点**：详细分情况讨论，逻辑严谨，代码简洁，使用位运算优化枚举范围。
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
    - **核心实现思想**：通过分析 $x \oplus y$ 为 $x$ 或 $y$ 的因数时 $y$ 的二进制位数情况，证明 $y$ 的二进制位数不超过 $x$ 的二进制位数。然后枚举缩小后的范围内的 $y$，判断是否满足条件，满足则答案加 1。
- **作者：Limerency（4星）**
    - **关键亮点**：给出结论并进行证明，代码使用命名空间封装，结构清晰。
    - **核心代码**：
```cpp
int solve() {
    cin >> x >> m;
    int hb = 1, p = x, ans = 0;
    while (p) p >>= 1, hb <<= 1;
    int lm = min(hb - 1ll, m);
    for (int i = hb >> 1; i <= lm; i ++) {
        int t = (x ^ i);
        if (x!= i) if (x % t == 0 || i % t == 0) ans ++;
    }
    cout << ans << '\n';
    return 0;
}
```
    - **核心实现思想**：证明对于满足条件的 $y$，其在二进制下的位数与 $x$ 相同。通过循环找到 $x$ 的二进制最高位对应的数值 $hb$，然后枚举二进制位数与 $x$ 相同且在 $[1, m]$ 范围内的 $y$，判断是否满足条件，满足则答案加 1。

### 最优关键思路或技巧
- **缩小枚举范围**：通过分析 $x \oplus y$ 的性质、因数的性质以及二进制位数的关系，将 $y$ 的枚举范围从 $[1, m]$ 缩小到 $[1, \min(2x, m)]$ 或二进制位数不超过 $x$ 的范围，降低时间复杂度。
- **二进制分析**：从二进制的角度分析 $x$ 和 $y$ 的关系，利用异或运算的特点，如最高位的变化情况，来判断 $x \oplus y$ 是否为 $x$ 或 $y$ 的因数。

### 可拓展之处
同类型题可能会改变运算规则（如将异或改为其他位运算）或条件（如要求 $x \oplus y$ 是 $x$ 和 $y$ 的最大公因数），但解题思路仍然可以从二进制分析和范围缩小入手。类似算法套路可用于解决涉及位运算和因数判断的问题。

### 推荐洛谷题目
1. [P1837 连通块](https://www.luogu.com.cn/problem/P1837)：涉及位运算和状态压缩。
2. [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)：需要运用位运算和贪心思想。
3. [P3812 小A的糖果](https://www.luogu.com.cn/problem/P3812)：可以通过位运算优化时间复杂度。

### 个人心得摘录与总结
- **Binah_cyc**：赛时可以先通过观察样例和打表确定大致范围，再进行严谨证明，以保证解题的准确性和效率。

---
处理用时：42.34秒