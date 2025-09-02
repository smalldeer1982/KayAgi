# 题目信息

# Pythagorean Triples

## 题目描述

Katya studies in a fifth grade. Recently her class studied right triangles and the Pythagorean theorem. It appeared, that there are triples of positive integers such that you can construct a right triangle with segments of lengths corresponding to triple. Such triples are called Pythagorean triples.

For example, triples $ (3,4,5) $ , $ (5,12,13) $ and $ (6,8,10) $ are Pythagorean triples.

Here Katya wondered if she can specify the length of some side of right triangle and find any Pythagorean triple corresponding to such length? Note that the side which length is specified can be a cathetus as well as hypotenuse.

Katya had no problems with completing this task. Will you do the same?

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF707C/80a087cda42609e729836c8476c6d8655d41a6b9.png)Illustration for the first sample.

## 样例 #1

### 输入

```
3
```

### 输出

```
4 5```

## 样例 #2

### 输入

```
6
```

### 输出

```
8 10```

## 样例 #3

### 输入

```
1
```

### 输出

```
-1```

## 样例 #4

### 输入

```
17
```

### 输出

```
144 145```

## 样例 #5

### 输入

```
67
```

### 输出

```
2244 2245```

# AI分析结果



# 勾股三元组（Pythagorean Triples）

## 题目描述

Katya 正在五年级学习。最近她的班级学习了直角三角形和毕达哥拉斯定理。她发现存在三个正整数构成的元组，使得可以用这三条边的长度构造直角三角形。这样的三元组被称为毕达哥拉斯三元组。

例如，三元组 $(3,4,5)$、$(5,12,13)$ 和 $(6,8,10)$ 都是毕达哥拉斯三元组。

Katya 想知道，如果给定某条直角边的长度，能否找到对应的毕达哥拉斯三元组？给定的边可以是直角边或斜边。

## 算法分类
**构造**

---

## 题解分析与结论

### 核心思路
题目要求构造勾股数，核心在于利用勾股数的生成规律：
1. **奇数构造法**：若输入数 $n$ 为奇数且 $n \geq 3$，则存在勾股数 $(n, \frac{n^2-1}{2}, \frac{n^2+1}{2})$。
2. **偶数构造法**：若 $n$ 为偶数，将其转换为奇数处理（如 $n=2^k \cdot m$，其中 $m$ 为奇数），构造后乘回倍数。或直接构造 $(n, (\frac{n}{2})^2-1, (\frac{n}{2})^2+1)$。
3. **特判**：$n \leq 2$ 时无解。

### 最优解法
- **奇偶分治**：直接根据 $n$ 的奇偶性选择对应的构造公式，无需分解因子或复杂循环。
- **数学构造**：通过平方差公式推导，直接生成符合条件的数对。

---

## 精选题解

### 题解1：zenght（⭐⭐⭐⭐⭐）
**关键亮点**：代码简洁，直接分奇偶处理，覆盖所有情况。
```cpp
long long n;
cin >> n;
if (n == 1 || n == 2) cout << -1 << '\n';
else if (n % 2 == 0) cout << n * n / 4 - 1 << " " << n * n / 4 + 1 << '\n';
else cout << n * n / 2 << " " << n * n / 2 + 1 << '\n';
```
**核心思想**：偶数时构造 $\left(\frac{n^2}{4}-1, \frac{n^2}{4}+1\right)$，奇数时构造 $\left(\frac{n^2}{2}, \frac{n^2}{2}+1\right)$。

### 题解2：NFGase（⭐⭐⭐⭐）
**关键亮点**：直观的分治思路，将偶数转换为奇数处理。
```cpp
if (n % 2 != 0) 
    cout << ((n * n) / 2) << " " << ((n * n) / 2) + 1;
else {
    n /= 2;
    cout << (n * n) - 1 << " " << (n * n) + 1;
}
```
**核心思想**：偶数通过除以2转换为奇数后构造，结果乘2还原。

### 题解3：囧仙（⭐⭐⭐⭐）
**关键亮点**：处理2的幂次特殊情况，确保覆盖所有边界。
```cpp
while(n>4&&n%2==0) n/=2,m*=2;
if(n==4) printf("%lld %lld",3*m,5*m);
else printf("%lld %lld\n",(n*n+1)/2*m,(n*n-1)/2*m);
```
**核心思想**：将 $n$ 分解为 $2^k \cdot m$，对 $m$ 构造后乘回 $2^k$，并特殊处理 $n=4$。

---

## 关键技巧总结
1. **奇偶分治**：勾股数的生成公式因奇偶性不同，需分别处理。
2. **数学构造法**：利用平方差公式 $(c+b)(c-b)=a^2$ 快速推导。
3. **边界特判**：$n \leq 2$ 时无解是构造的前提条件。

---

## 拓展与同类题目
- **构造思维**：类似题目需通过数学推导寻找规律，如质数分布、斐波那契数列等。
- **推荐题目**：
  - [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)（构造连续序列和）
  - [P1217 回文质数](https://www.luogu.com.cn/problem/P1217)（数学构造与筛选）
  - [P1572 分解数](https://www.luogu.com.cn/problem/P1572)（分解因子的构造方法）

---
处理用时：179.26秒