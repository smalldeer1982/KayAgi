# 题目信息

# Square Difference

## 题目描述

Alice has a lovely piece of cloth. It has the shape of a square with a side of length $ a $ centimeters. Bob also wants such piece of cloth. He would prefer a square with a side of length $ b $ centimeters (where $ b < a $ ). Alice wanted to make Bob happy, so she cut the needed square out of the corner of her piece and gave it to Bob. Now she is left with an ugly L shaped cloth (see pictures below).

Alice would like to know whether the area of her cloth expressed in square centimeters is [prime.](https://en.wikipedia.org/wiki/Prime_number) Could you help her to determine it?

## 说明/提示

The figure below depicts the first test case. The blue part corresponds to the piece which belongs to Bob, and the red part is the piece that Alice keeps for herself. The area of the red part is $ 6^2 - 5^2 = 36 - 25 = 11 $ , which is prime, so the answer is "YES".

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1033B/26aa17f955334a29eef8994b7c5af8ed29b66689.png)In the second case, the area is $ 16^2 - 13^2 = 87 $ , which is divisible by $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1033B/bb700dc40c3e1b73968059e8f9c3fba6a4d8a953.png)In the third case, the area of the remaining piece is $ 61690850361^2 - 24777622630^2 = 3191830435068605713421 $ . This number is not prime because $ 3191830435068605713421 = 36913227731 \cdot 86468472991  $ .

In the last case, the area is $ 34^2 - 33^2 = 67 $ .

## 样例 #1

### 输入

```
4
6 5
16 13
61690850361 24777622630
34 33
```

### 输出

```
YES
NO
NO
YES
```

# AI分析结果



# Square Difference

## 题目描述

爱丽丝有一块美丽的正方形布料，边长为 $a$ 厘米。鲍勃也想要一块这样的布料，但他更希望边长为 $b$ 厘米（其中 $b < a$）。爱丽丝从自己布料的角落剪下所需的正方形给鲍勃后，剩下的布料变成了难看的 L 形（见下图示例）。

爱丽丝想知道她剩余布料的面积（以平方厘米为单位）是否为质数。请帮助她判断。

## 说明/提示

下图展示了第一个测试用例。蓝色部分属于鲍勃，红色部分是爱丽丝保留的布料。红色区域面积为 $6^2 - 5^2 = 11$，是质数，故答案为"YES"。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1033B/26aa17f955334a29eef8994b7c5af8ed29b66689.png)

第二个案例中，面积为 $16^2 - 13^2 = 87$，可被 3 整除。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1033B/bb700dc40c3e1b73968059e8f9c3fba6a4d8a953.png)

## 样例 #1

### 输入
```
4
6 5
16 13
61690850361 24777622630
34 33
```

### 输出
```
YES
NO
NO
YES
```

---

**算法分类**：质数、数学

---

### 题解综合分析

所有题解均基于平方差公式的数学推导，核心思路为：
1. 剩余面积 $a^2 - b^2 = (a+b)(a-b)$
2. 质数的充要条件是两个因子分别为 1 和质数
3. 由于 $a > b$，必然有 $a+b > a-b$，故只需满足：
   - $a - b = 1$ 
   - $a + b$ 为质数

**关键优化**：通过数学公式转换避免直接计算大数平方，将时间复杂度从 $O(1)$ 的数值运算转换为 $O(\sqrt{n})$ 的质数判断。

---

### 精选题解

#### 1. 一扶苏一（★★★★☆）
**亮点**：
- 完整包含公式推导与边界条件处理
- Python 实现简洁易懂
- 函数封装清晰

**核心代码**：
```python
def IsPrime(x):
    k = int(math.sqrt(x) + 1)
    for i in range(2, k):
        if x % i == 0:
            return False
    return True
```

#### 2. _Harrisonwhl_（★★★★☆）
**亮点**：
- 明确强调 long long 类型的重要性
- 代码包含详细的质数判断边界处理
- 使用 puts 优化输出效率

**核心代码**：
```cpp
bool isPr(long long x) {
    if (x < 2) return 0;
    for (int i = 2; i <= sqrt(x); i++)
        if (x % i == 0) return 0;
    return 1;
}
```

#### 3. JoseTony（★★★★☆）
**亮点**：
- 使用 inline 优化函数调用
- 代码风格规范，变量命名清晰
- 包含详细的注释说明

**核心代码**：
```cpp
inline int is_prime(ll x) {
    if(x < 2) return 0;
    for(ll i = 2; i*i <= x; ++i)
        if(x % i == 0) return 0;
    return 1;
}
```

---

### 关键技巧总结
1. **数学公式转换**：遇到大数平方差时，优先考虑因式分解
2. **质数判断优化**：试除范围只需到 $\sqrt{n}$，时间复杂度 $O(\sqrt{n})$
3. **数据类型控制**：必须使用 64 位整型（long long）处理 $10^{11}$ 量级数据
4. **边界条件处理**：当 $a-b \neq 1$ 时直接返回 NO

---

### 拓展练习
1. [P1217 [USACO1.5] 回文质数](https://www.luogu.com.cn/problem/P1217) - 质数的特殊形态判断
2. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075) - 质数性质应用
3. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383) - 质数筛法优化

---

### 个人心得摘录
> "记得开 long long！" —— 多个题解作者强调  
> 调试中发现当 $a+b=2$ 时误判为合数，补充了 $x<=2$ 的边界条件 —— 江户川·乱步  
> 通过数学公式转换避免了高精度计算 —— 多作者共同经验

---
处理用时：46.15秒