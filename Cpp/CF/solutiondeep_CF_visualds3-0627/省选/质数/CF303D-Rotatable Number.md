# 题目信息

# Rotatable Number

## 题目描述

Bike is a smart boy who loves math very much. He invented a number called "Rotatable Number" inspired by $ 142857 $ .

As you can see, $ 142857 $ is a magic number because any of its rotatings can be got by multiplying that number by $ 1,2,...,6 $ (numbers from one to number's length). Rotating a number means putting its last several digit into first. For example, by rotating number $ 12345 $ you can obtain any numbers: $ 12345,51234,45123,34512,23451 $ . It's worth mentioning that leading-zeroes are allowed. So both $ 4500123 $ and $ 0123450 $ can be obtained by rotating $ 0012345 $ . You can see why $ 142857 $ satisfies the condition. All of the $ 6 $ equations are under base $ 10 $ .

- $ 142857·1=142857 $ ;
- $ 142857·2=285714 $ ;
- $ 142857·3=428571 $ ;
- $ 142857·4=571428 $ ;
- $ 142857·5=714285 $ ;
- $ 142857·6=857142 $ .

Now, Bike has a problem. He extends "Rotatable Number" under any base $ b $ . As is mentioned above, $ 142857 $ is a "Rotatable Number" under base $ 10 $ . Another example is $ 0011 $ under base 2. All of the $ 4 $ equations are under base $ 2 $ .

- $ 0011·1=0011 $ ;
- $ 0011·10=0110 $ ;
- $ 0011·11=1001 $ ;
- $ 0011·100=1100 $ .

So, he wants to find the largest $ b $ $ (1&lt;b&lt;x) $ so that there is a positive "Rotatable Number" (leading-zeroes allowed) of length $ n $ under base $ b $ .

Note that any time you multiply a rotatable number by numbers from 1 to its length you should get a rotating of that number.

## 样例 #1

### 输入

```
6 11
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 8
```

### 输出

```
-1
```

# AI分析结果



## 算法分类
**数论、原根**

---

## 题解思路与核心难点

### 核心思路
1. **数学推导**：  
   可旋转数的存在条件等价于：  
   - **n+1 是质数 p**  
   - **基数 b 是 p 的原根**  

2. **原根判定**：  
   - 分解 p-1 的所有质因数 q  
   - 对每个 q，检查是否满足 b^((p-1)/q) mod p ≠ 1  

### 解决难点
- **数学建模**：将循环数的性质转换为原根存在性问题（需深入数论推导）  
- **高效判定原根**：通过分解质因数快速排除非原根候选  

---

## 题解评分（≥4星）

### 1. ACAね (★★★★☆)  
- **亮点**：代码简洁，快速幂实现高效，直接倒序枚举候选基数  
- **缺点**：质因数分解未显式处理，可能影响可读性  

### 2. 金珂拉 (★★★★☆)  
- **亮点**：预处理素数表加速质因数分解，逻辑清晰  
- **缺点**：冗余的素数筛法可能增加内存占用  

---

## 最优思路提炼

### 关键步骤
1. **质数判定**：检查 n+1 是否为质数  
2. **原根判定**：  
   - 分解 p-1 的质因数  
   - 对每个候选 b，验证 ∀q: b^((p-1)/q) mod p ≠ 1  

### 代码实现核心
```cpp
// 检查 b 是否是 p 的原根
bool check(long long b) {
    for (auto q : factors) { // factors 是 p-1 的质因数列表
        if (qpow(b, (p-1)/q, p) == 1)
            return false;
    }
    return true;
}
```

---

## 同类型题与算法套路
- **原根应用**：涉及循环数、离散对数、密码学（如Diffie-Hellman）  
- **质数性质**：需快速判断质数并分解质因数  

---

## 推荐题目
1. **P1226 【模板】快速幂**  
2. **P1069 原根**  
3. **P2485 计算器**  

---

## 个人心得摘录
- **ACAね**：“昨天学欧拉定理今天考原根，老师的良心呢”——原根问题需结合欧拉定理与数论推导  
- **lzytag**：“2600困难MO题”——强调数学建模的难度  

---

## 可视化算法设计

### 动画方案
1. **像素风格界面**：  
   - **数据结构**：8位网格显示当前检查的 b 和质因数分解结果  
   - **颜色标记**：  
     - 红色：当前检查的 b 和对应的质因数 q  
     - 绿色：验证通过的原根  

2. **流程演示**：  
   - **步骤1**：显示 n+1 的质数判定（质数则亮起绿框）  
   - **步骤2**：从 x-1 开始倒序枚举 b，高亮当前 b  
   - **步骤3**：对每个 b，分解 p-1 的质因数，逐个验证原根条件  
   - **步骤4**：找到首个满足条件的 b 时播放胜利音效  

3. **音效设计**：  
   - **按键音效**：每次质因数检查时播放短促“滴”声  
   - **错误音效**：非质数或找不到原根时播放低音  
   - **成功音效**：找到原根时播放经典FC过关音效  

### 交互设计
- **自动演示**：按空格键切换自动/手动模式  
- **速度调节**：滑块控制动画帧率（1~60 FPS）  

---

## 核心代码实现（ACAね版）
```cpp
// 快速幂模运算
long long ksm(long long a, int b) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

// 检查 b 是否是原根
bool check(long long k) {
    if (k % mod == 0) return false;
    for (long long i = 1; i*i <= n; ++i) {
        if (n % i == 0) {
            if (i < n && ksm(k, i) == 1) return false;
            if (i != 1 && ksm(k, n/i) == 1) return false;
        }
    }
    return true;
}
```

---
处理用时：57.76秒