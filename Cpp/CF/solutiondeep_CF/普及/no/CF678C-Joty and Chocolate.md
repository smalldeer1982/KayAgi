# 题目信息

# Joty and Chocolate

## 题目描述

Little Joty has got a task to do. She has a line of $ n $ tiles indexed from $ 1 $ to $ n $ . She has to paint them in a strange pattern.

An unpainted tile should be painted Red if it's index is divisible by $ a $ and an unpainted tile should be painted Blue if it's index is divisible by $ b $ . So the tile with the number divisible by $ a $ and $ b $ can be either painted Red or Blue.

After her painting is done, she will get $ p $ chocolates for each tile that is painted Red and $ q $ chocolates for each tile that is painted Blue.

Note that she can paint tiles in any order she wants.

Given the required information, find the maximum number of chocolates Joty can get.

## 样例 #1

### 输入

```
5 2 3 12 15
```

### 输出

```
39
```

## 样例 #2

### 输入

```
20 2 3 3 5
```

### 输出

```
51
```

# AI分析结果



# Joty and Chocolate

## 题目描述

小 Joty 有一个任务。她有一排 $n$ 块瓷砖，索引从 $1$ 到 $n$。她需要用一种特殊的方式给瓷砖上色：

- 如果一个未上色的瓷砖的索引能被 $a$ 整除，则应涂成红色。
- 如果一个未上色的瓷砖的索引能被 $b$ 整除，则应涂成蓝色。
- 如果瓷砖的索引同时能被 $a$ 和 $b$ 整除，则可以选择涂红色或蓝色。

涂色完成后，每个红色瓷砖会获得 $p$ 块巧克力，每个蓝色瓷砖会获得 $q$ 块巧克力。求 Joty 能获得的最大巧克力数。

## 输入样例

### 样例 1
输入：`5 2 3 12 15`
输出：`39`

### 样例 2
输入：`20 2 3 3 5`
输出：`51`

---

## 算法分类
数学、贪心

---

## 题解对比与总结

### 关键思路
1. **容斥原理**：计算单独属于 $a$ 或 $b$ 的倍数数量，减去重复部分（最小公倍数的倍数）。
2. **贪心选择**：对同时是 $a$ 和 $b$ 倍数的瓷砖，选择 $p$ 和 $q$ 中的较大值。
3. **数学公式**：利用 $\text{lcm}(a,b) = \frac{a \cdot b}{\gcd(a,b)}$ 计算重复部分。

### 最优题解

#### 题解作者：_tommysun_（⭐️⭐️⭐️⭐️⭐️）
**亮点**  
- 思路清晰，直接使用容斥原理计算红、蓝瓷砖数。
- 代码简洁，注释明确，时间复杂度 $O(1)$。
```cpp
long long gcd(long long x, long long y) {
    return x % y == 0 ? y : gcd(y, x % y);
}
long long lcm(long long x, long long y) {
    return x * y / gcd(x, y);
}
int main() {
    long long n, a, b, p, q;
    cin >> n >> a >> b >> p >> q;
    long long red = n / a, blue = n / b;
    long long overlap = n / lcm(a, b);
    red -= overlap; // 去重
    blue -= overlap; 
    cout << red * p + blue * q + overlap * max(p, q);
}
```

#### 题解作者：2011FYCCCTA（⭐️⭐️⭐️⭐️⭐️）
**亮点**  
- 公式推导巧妙，直接通过总和减去重复部分的较小值。
- 代码简短，变量命名直观。
```cpp
int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}
int lcm(int x, int y) {
    return x * y / gcd(x, y);
}
int main() {
    long long n, a, b, p, q;
    cin >> n >> a >> b >> p >> q;
    long long overlap = n / lcm(a, b);
    long long ans = (n / a) * p + (n / b) * q - overlap * min(p, q);
    cout << ans;
}
```

#### 题解作者：hexuchen（⭐️⭐️⭐️⭐️）
**亮点**  
- 分模块计算红、蓝、重复部分的价值，逻辑清晰。
- 变量命名规范，注释明确。
```cpp
long long gbs(int a, int b) {
    return a * b / gys(a, b);
}
signed main() {
    int red = (n / a - n / gbs(a, b)) * p;
    int blue = (n / b - n / gbs(a, b)) * q;
    int overlap = n / gbs(a, b) * max(p, q);
    cout << red + blue + overlap;
}
```

---

## 关键技巧总结
- **数学公式应用**：快速计算最小公倍数和最大公约数。
- **容斥原理**：避免重复计数，分离独立部分和重复部分。
- **贪心选择**：对重叠部分取最大收益。

---

## 拓展练习
1. [P2651 添加括号](https://www.luogu.com.cn/problem/P2651)（数学表达式优化）
2. [P1072 Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)（公约数/公倍数应用）
3. [P1290 欧几里得的游戏](https://www.luogu.com.cn/problem/P1290)（博弈与数论结合）

---
处理用时：205.94秒