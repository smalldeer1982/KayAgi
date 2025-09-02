# 题目信息

# Shaass and Lights

## 题目描述

There are $ n $ lights aligned in a row. These lights are numbered $ 1 $ to $ n $ from left to right. Initially some of the lights are switched on. Shaass wants to switch all the lights on. At each step he can switch a light on (this light should be switched off at that moment) if there's at least one adjacent light which is already switched on.

He knows the initial state of lights and he's wondering how many different ways there exist to switch all the lights on. Please find the required number of ways modulo $ 1000000007 (10^{9}+7) $ .

## 样例 #1

### 输入

```
3 1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 2
1 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
11 2
4 8
```

### 输出

```
6720
```

# AI分析结果



---

## 数学分类选择  
**组合数学**  

---

## 题解思路、算法要点与解决难点  

### 核心数学逻辑  
将初始已点亮的灯视为分界点，分割出多个连续暗灯区间。总方案数由三部分相乘得到：  
1. **多重排列数**：将各区间操作视为不同颜色球的多重排列，总排列数为 $\frac{(n-m)!}{\prod (len_i!)}$  
2. **中间区间选择方向的贡献**：每个中间区间（非两端）有 $2^{len_i-1}$ 种左右扩展方式  
3. **边界区间特殊处理**：首尾区间只能单向扩展，贡献为 $1$  

### 关键公式推导  
$$
ans = \underbrace{\frac{(n-m)!}{\prod (len_i!)}}_{\text{多重排列}} \times \underbrace{\prod_{mid} 2^{len_i-1}}_{\text{方向选择}}
$$

### 解决难点  
1. **区间划分与边界处理**：正确处理首尾区间与中间区间的差异  
2. **组合数模运算**：通过预处理阶乘与逆元实现 $O(1)$ 组合数计算  
3. **指数运算优化**：使用快速幂预处理 $2^k$ 值  

---

## 题解评分 (≥4★)  

### 1. StillEmpty（4.5★）  
- **亮点**：公式推导清晰，注释详细，预处理逆元方式高效  
- **关键代码**：  
  ```cpp
  ans = (ans * C(k, len) % mod * qpow(2, len - 1)) % mod;
  ```

### 2. RedreamMer（4★）  
- **亮点**：代码简洁，组合数预处理逻辑完整  
- **优化点**：逆元递推公式 $(mod - mod/i) * inv[mod\%i] \% mod$  

### 3. xqh07（4★）  
- **亮点**：容斥思想解释新颖，阶乘逆元双重预处理  
- **代码特色**：  
  ```cpp
  res = f[n-m] * qpow(f[b[1]], mod-2) % mod * ... 
  ```

---

## 最优思路与技巧提炼  

### 关键技巧  
1. **区间分割模型**：  
   ```python
   pos = sorted(灯位置)
   segs = [pos[i] - pos[i-1]-1 for 中间区间]
   ```

2. **快速幂预处理**：  
   ```cpp
   pow2[0] = 1;
   for(int i=1; i<=n; i++) 
       pow2[i] = (pow2[i-1] * 2) % mod;
   ```

3. **组合数优化模板**：  
   ```cpp
   void init() { // 预处理阶乘与逆元
       fac[0] = inv[0] = 1;
       for(int i=1; i<=N; i++) 
           fac[i] = fac[i-1] * i % mod;
       inv[N] = qpow(fac[N], mod-2);
       for(int i=N-1; i>=1; i--)
           inv[i] = inv[i+1] * (i+1) % mod;
   }
   ```

---

## 同类型题套路  
1. **分治组合**：将大问题分解为独立子问题相乘  
2. **多重排列**：$\frac{(\sum k_i)!}{\prod k_i!}$ 处理不同操作序列  
3. **方向选择模型**：$2^{k}$ 类二叉树式扩展问题  

---

## 推荐题目  
1. **P1375 灯泡**（组合数应用）  
2. **P3807 卢卡斯定理**（组合数模运算）  
3. **P1495 曹冲养猪**（模运算与分治）  

---

## 可视化设计  

### 像素动画方案  
```javascript
// 核心演示逻辑（伪代码）
class LightAnim {
    constructor(segs) {
        this.grid = new PixelGrid(16, 16); // 16x16像素画布
        this.colors = ['#FF0000', '#00FF00', '#0000FF']; // 红绿蓝三色
    }

    async animateStep(segIndex) {
        const seg = segs[segIndex];
        // 高亮当前区间
        this.grid.fillRect(seg.start, 0, seg.length, 1, this.colors[segIndex%3]);
        // 显示组合数计算过程
        this.showText(`C(${total}, ${seg.len}) × 2^${seg.len-1}`);
        await sleep(500); // 步进间隔
    }
}
```

### 复古特效  
- **音效设计**：  
  - 正确步骤：8-bit "coin" 音效（频率 800Hz）  
  - 错误操作：短促噪声（频率 200Hz）  
- **动画流程**：  
  ![灯泡扩展动图](https://example.com/light-anim.gif)  

---

## 核心代码实现  
```cpp
int main() {
    init(); // 预处理阶乘&逆元
    sort(a, a+m);
    int ans = 1, total = n-m;
    
    // 处理首区间
    int len = a[0]-1;
    ans = ans * C(total, len) % mod;
    total -= len;

    // 处理中间区间
    for(int i=1; i<m; i++) {
        len = a[i] - a[i-1] - 1;
        ans = ans * C(total, len) % mod;
        ans = ans * qpow(2, len-1) % mod; // 核心方向选择
        total -= len;
    }

    // 处理尾区间
    len = n - a[m-1];
    ans = ans * C(total, len) % mod;
    cout << ans;
}
```

---
处理用时：74.67秒