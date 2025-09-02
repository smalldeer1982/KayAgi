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



---

## 算法分类  
**数论（原根、质数判定）**

---

## 综合分析与结论  

### 题目核心思路  
所有题解均基于以下结论：  
**当且仅当 `n+1` 是质数，且存在 `b` 是该质数的原根时，存在符合条件的 Rotatable Number**。此时需从 `x-1` 到 `2` 倒序寻找最大的原根 `b`，否则输出 `-1`。

### 解决难点与关键步骤  
1. **质数判定**：验证 `n+1` 是否为质数。  
2. **原根判定**：若 `n+1` 是质数 `p`，则 `b` 是原根的条件为：对所有 `p-1` 的质因数 `d`，满足 `b^((p-1)/d) ≡ 1 (mod p)` 不成立。  
3. **快速幂优化**：通过快速幂算法高效验证原根条件。

### 可视化设计  
1. **动画流程**：  
   - **Step 1**：验证 `n+1` 是否为质数（红色高亮质数判断代码）。  
   - **Step 2**：分解 `n` 的质因数（黄色标记质因数分解过程）。  
   - **Step 3**：从 `x-1` 倒序枚举 `b`，对每个 `b` 用快速幂验证原根条件（绿色表示成功，红色表示失败）。  
2. **复古像素风格**：  
   - 质数判定过程用 8-bit 像素字体展示，失败时播放“错误音效”（类似《超级马里奥》死亡音效）。  
   - 原根判定时，每个快速幂步骤对应一个像素方块闪烁，成功时播放“金币收集音效”。  
3. **交互控制**：支持暂停观察快速幂中间结果，速度滑块调节枚举 `b` 的速度。

---

## 题解清单（≥4星）  

### 1. ACAね（★★★★☆）  
**亮点**：  
- 完整数学推导，从分数循环小数到原根条件。  
- 代码清晰，直接枚举 `b` 并验证原根。  
**代码片段**：  
```cpp
bool check(long long k) {
    for(long long i=1; i*i<=n; i++) {
        if(n%i==0) {
            if(i<n && ksm(k,i)==1) return false;
            if(i!=1 && ksm(k,n/i)==1) return false;
        }
    }
    return true;
}
```

### 2. lzytag（★★★★☆）  
**亮点**：  
- 严格数学证明 `T = n+1` 的必要性。  
- 代码中直接利用原根判定定理。  
**代码片段**：  
```cpp
bool check(long long x) {
    for(int i=1; i<=tot; i++) 
        if(qpow(x, (p-1)/a[i], p) == 1) return false;
    return true;
}
```

---

## 最优思路与技巧提炼  

### 关键步骤  
1. **质数判定**：用试除法或 Miller-Rabin 算法判断 `n+1` 是否为质数。  
2. **原根判定**：  
   - 分解 `p-1` 的所有质因数。  
   - 对每个 `b` 检查 `b^((p-1)/d) ≡ 1 (mod p)` 是否全不成立。  

### 代码优化技巧  
- **快速幂优化**：用位运算加速幂取模。  
- **质因数分解缓存**：预处理 `p-1` 的质因数避免重复计算。  

---

## 类似题目推荐  
1. **P1092** [虫食算]：涉及数论与排列组合。  
2. **P2480** [古代猪文]：原根与 Lucas 定理结合。  
3. **P1445** [樱花]：分数化简与质因数分解。  

---

## 个人心得摘录  
- **ACAね**：  
  > “考场上推出原根定理…老师的良心呢” → 强调数学直觉的重要性。  
- **lzytag**：  
  > “2600 困难 MO 题” → 体现对题目难度的敬畏心态。  

---

## 核心代码实现  
```cpp
// 原根判定核心代码
bool is_primitive_root(int b, int p, vector<int>& factors) {
    for (int d : factors) {
        if (qpow(b, (p-1)/d, p) == 1) 
            return false;
    }
    return true;
}

// 主逻辑
int solve(int n, int x) {
    int p = n + 1;
    if (!is_prime(p)) return -1;
    auto factors = prime_factors(p - 1);
    for (int b = x-1; b >= 2; b--) {
        if (is_primitive_root(b, p, factors)) 
            return b;
    }
    return -1;
}
```

---

## 可视化算法演示（Web 实现草图）  

```html
<!DOCTYPE html>
<div class="pixel-screen" style="font-family: 'Press Start 2P'; background: #000;">
  <canvas id="primeCheck"></canvas>
  <div id="status" style="color: #0F0;">Checking p = n+1...</div>
</div>
<script>
// 伪代码：快速幂动画演示
function animatePow(base, exp, mod) {
    let result = 1;
    exp.toString(2).split('').forEach((bit, i) => {
        setTimeout(() => {
            highlightBit(bit, i); // 高亮当前二进制位
            result = (result * result) % mod;
            if (bit === '1') result = (result * base) % mod;
            updateResultDisplay(result); // 更新画布显示
        }, i * 500);
    });
}
</script>
```

**交互设计**：  
- 用户输入 `n` 和 `x` 后，自动播放质数判定 → 原根枚举。  
- 失败时屏幕抖动 + 8-bit 爆炸音效，成功时播放《塞尔达》解谜成功音效。

---
处理用时：67.11秒