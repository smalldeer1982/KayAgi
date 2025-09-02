# 题目信息

# Square Subsets

## 题目描述

Petya was late for the lesson too. The teacher gave him an additional task. For some array $ a $ Petya should find the number of different ways to select non-empty subset of elements from it in such a way that their product is equal to a square of some integer.

Two ways are considered different if sets of indexes of elements chosen by these ways are different.

Since the answer can be very large, you should find the answer modulo $ 10^{9}+7 $ .

## 说明/提示

In first sample product of elements chosen by any way is $ 1 $ and $ 1=1^{2} $ . So the answer is $ 2^{4}-1=15 $ .

In second sample there are six different ways to choose elements so that their product is $ 4 $ , and only one way so that their product is $ 16 $ . So the answer is $ 6+1=7 $ .

## 样例 #1

### 输入

```
4
1 1 1 1
```

### 输出

```
15
```

## 样例 #2

### 输入

```
4
2 2 2 2
```

### 输出

```
7
```

## 样例 #3

### 输入

```
5
1 2 4 5 8
```

### 输出

```
7
```

# AI分析结果



**唯一算法分类**: 数论

---

### 题解思路与算法要点

#### 核心数学逻辑
1. **质因数奇偶性压缩**：将每个数分解质因数，将质因数指数奇偶性压缩为19位二进制数（对应70以内的19个质数）
2. **异或性质**：乘积为完全平方数 ⇨ 所有质因数指数奇偶性异或结果为0
3. **线性基应用**：将每个数的二进制掩码插入线性基，最终答案为 $2^{n-基大小}-1$

#### 解决难点对比
| 方法       | 时间复杂度   | 空间复杂度 | 核心数学推导                          |
|------------|--------------|------------|---------------------------------------|
| 状压DP     | O(70×2¹⁹)   | O(2¹⁹)     | 二项式定理计算奇偶选择方案数          |
| 线性基     | O(n×19)      | O(19)      | 自由变量数与线性代数基的维度关系      |

---

### 题解评分 (≥4星)

1. **bztMinamoto（5星）**
   - 关键亮点：最简洁的线性基实现，预处理质数表仅需19个元素
   - 代码片段：
     ```cpp
     void ins(int x){
         for(int i=18;i>=0;--i) if(x>>i&1){
             if(!b[i]){b[i]=x;break;}
             x^=b[i];
         }
     }
     ```

2. **1saunoya（4星）**
   - 关键亮点：完整展示线性基理论推导过程
   - 个人心得：详细注释"异或和为0的子集数=自由变量组合数-1"

3. **rui_er（4星）**
   - 关键亮点：模块化编程，独立质因数分解函数
   - 优化点：使用快速幂预处理2的幂次

---

### 最优思路提炼

**关键技巧**：  
1. **质因数奇偶压缩**：  
   ```python
   def get_mask(x):
       mask = 0
       for i, p in enumerate(primes):
           cnt = 0
           while x % p == 0:
               cnt ^= 1
               x //= p
           mask |= (cnt << i)
       return mask
   ```
   
2. **线性基维度定理**：自由变量数 = n - 基的维度，解集数 = $2^{\text{自由变量数}} - 1$

---

### 同类型题拓展

**通用套路**：  
1. 涉及质因数奇偶性的问题优先考虑二进制压缩
2. 异或和归零问题优先考虑线性基或状压DP
3. 常见变种：求最大/最小异或和、统计特定异或值出现次数

**推荐题目**：  
1. P4301 [CQOI2013]新Nim游戏（线性基应用）
2. P2114 [NOI2014]起床困难综合症（位运算贪心）
3. P4869 albus要第一个出场（线性基性质）

---

### 可视化设计

**8位像素化演示方案**：  
1. **质因数分解动画**：  
   - 左侧显示数字分解过程（如70→2×5×7）
   - 右侧用LED灯表示二进制掩码（19个像素点表示质数奇偶性）

2. **线性基插入演示**：  
   ```javascript
   // 伪代码演示插入过程
   function insertToBase(x) {
       for(let i=18; i>=0; i--) {
           if((x >> i) & 1) {
               if(!base[i]) {
                   base[i] = x; // 触发像素闪光特效
                   playSound('insert.wav');
                   break;
               }
               x ^= base[i];   // 显示异或运算过程
               drawXorAnimation(x, base[i]);
           }
       }
   }
   ```

3. **音效设计**：  
   - 成功插入基：8-bit "power-up"音效
   - 异或运算时：电子脉冲音效
   - 最终答案显示：经典FC过关音效

---

### 核心代码实现

**线性基插入与计算**：
```cpp
const int primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};

int main() {
    int n, cnt = 0, base[19] = {};
    for(int i=0; i<n; i++) {
        int x; cin >> x;
        int mask = 0;
        for(int j=0; j<19; j++) {
            int c = 0;
            while(x % primes[j] == 0) {
                c ^= 1;
                x /= primes[j];
            }
            mask |= (c << j);
        }
        // 插入线性基
        for(int j=18; j>=0; j--) if(mask >> j & 1) {
            if(!base[j]) { base[j] = mask; cnt++; break; }
            mask ^= base[j];
        }
    }
    cout << (pow(2, n-cnt) - 1) % MOD;
}
```

---

### 总结

本题通过质因数奇偶性压缩，将复杂数学问题转化为二进制操作问题。线性基解法以其$O(n×w)$的时间复杂度（w为质数个数）成为最优解，而状压DP适用于数值范围更小的场景。理解质因数分解的数学本质与线性空间的维度关系是解决此类问题的关键。

---
处理用时：67.77秒