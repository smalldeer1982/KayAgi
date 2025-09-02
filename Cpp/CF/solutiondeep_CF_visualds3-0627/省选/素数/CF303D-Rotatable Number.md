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



1. **唯一算法分类**  
   数论（原根与素数判定）

---

### 综合分析与结论

#### 核心逻辑
- **核心条件**：存在 Rotatable Number 当且仅当 `n+1` 是素数且 `b` 是该素数的原根。
- **解决步骤**：
  1. **素数判定**：检查 `n+1` 是否为素数。
  2. **原根判定**：对 `n+1` 分解质因数，若 `b` 满足对每个质因数 `p_i` 都有 `b^((n)/p_i) ≠ 1 (mod n+1)`，则 `b` 是原根。
  3. **逆向枚举**：从 `x-1` 向下遍历所有可能的 `b`，找到最大的满足条件的 `b`。

#### 难点与要点对比
- **ACAね题解**：通过分数循环节的数学推导，最终转化为原根判定。代码直接分解 `n` 的因数，利用快速幂进行原根检验。
- **lzytag题解**：通过模运算的集合等价性推导，明确要求 `n+1` 必须是质数且 `b` 是原根。代码中素数筛法预处理可能优化了质因数分解。
- **金珂拉题解**：在素数判断上可能存在缺陷（如未正确处理 `p=2` 的情况），导致正确性问题。

---

### 题解清单 (≥4星)

1. **ACAね（★★★★☆）**  
   - 亮点：数学推导完整，代码简洁高效，直接针对原根判定实现。
   - 代码片段：
     ```cpp
     bool check(long long k) {
         for(long long i=1; i*i<=n; i++) {
             if(n%i == 0) {
                 if(i < n && ksm(k,i) == 1) return false;
                 if(i !=1 && ksm(k,n/i) ==1 ) return false;
             }
         }
         return true;
     }
     ```

2. **lzytag（★★★★☆）**  
   - 亮点：详细推导模运算的集合等价性，代码逻辑清晰。
   - 引用推导：
     > "若 `n+1` 是素数且 `b` 是其原根，则 `{b^0, b^1, ..., b^{n-1}}` 在模 `n+1` 下生成全部非零余数。"

---

### 最优思路提炼
- **关键技巧**：将循环数问题转化为原根存在性问题。
- **实现优化**：快速幂加速原根判定，逆向枚举减少搜索次数。
- **踩坑点**：必须严格判定 `n+1` 是素数，否则直接无解。

---

### 类似题目推荐
1. **P1067** - 多项式输出（数论基础）
2. **P1092** - 虫食算（原根与进制）
3. **P2480** - 古代猪文（原根应用）

---

### 可视化与算法演示

#### 动画方案设计
1. **素数判定阶段**：
   - **像素效果**：用红色方块表示被检查的数 `n+1`，绿色表示素数，红色表示合数。
   - **音效**：判定成功时播放 "coin" 音效，失败时播放 "bomb" 音效。

2. **原根判定阶段**：
   - **网格展示**：在 Canvas 中绘制 `n+1` 的质因数分解过程，每个质因数用不同颜色方块表示。
   - **快速幂演示**：动态显示 `b^k mod p` 的计算过程，高亮当前计算的指数。

3. **交互设计**：
   - **步进控制**：允许暂停观察快速幂的中间结果。
   - **自动模式**：AI 自动从 `x-1` 向下遍历，用蓝色光标标记当前检查的 `b`。

#### 复古游戏化设计
- **8位风格**：使用 NES 风格的 8-bit 字体，背景音乐为《超级玛丽》地下关 BGM。
- **积分系统**：每找到一个原根得 100 分，连续找到多个触发连击奖励。

---

### 核心代码实现（ACAね）
```cpp
#include<bits/stdc++.h>
using namespace std;

long long n, x, mod;

long long ksm(long long a, int b) {
    long long ans = 1;
    while(b) {
        if(b & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

bool check_prime(long long p) {
    if(p < 2) return false;
    for(long long i = 2; i * i <= p; ++i)
        if(p % i == 0) return false;
    return true;
}

bool check_root(long long b) {
    for(long long i = 1; i * i <= n; ++i) {
        if(n % i == 0) {
            if(i < n && ksm(b, i) == 1) return false;
            if(i != 1 && ksm(b, n/i) == 1) return false;
        }
    }
    return true;
}

int main() {
    cin >> n >> x;
    mod = n + 1;
    if(!check_prime(mod)) {
        cout << -1;
        return 0;
    }
    for(int b = x - 1; b >= 2; --b) {
        if(check_root(b)) {
            cout << b;
            return 0;
        }
    }
    cout << -1;
    return 0;
}
```

---
处理用时：59.79秒