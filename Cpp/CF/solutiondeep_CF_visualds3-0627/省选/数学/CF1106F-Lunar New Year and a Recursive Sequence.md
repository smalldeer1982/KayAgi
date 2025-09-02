# 题目信息

# Lunar New Year and a Recursive Sequence

## 题目描述

Lunar New Year is approaching, and Bob received a gift from his friend recently — a recursive sequence! He loves this sequence very much and wants to play with it.

Let $ f_1, f_2, \ldots, f_i, \ldots $ be an infinite sequence of positive integers. Bob knows that for $ i > k $ , $ f_i $ can be obtained by the following recursive equation:

 $ $$$f_i = \left(f_{i - 1} ^ {b_1} \cdot f_{i - 2} ^ {b_2} \cdot \cdots \cdot f_{i - k} ^ {b_k}\right) \bmod p, $ $ </p><p>which in short is</p><p> $ $ f_i = \left(\prod_{j = 1}^{k} f_{i - j}^{b_j}\right) \bmod p, $ $ </p><p>where  $ p = 998\\,244\\,353 $  (a widely-used prime),  $ b\_1, b\_2, \\ldots, b\_k $  are known integer constants, and  $ x \\bmod y $  denotes the remainder of  $ x $  divided by  $ y $ .</p><p>Bob lost the values of  $ f\_1, f\_2, \\ldots, f\_k $ , which is extremely troublesome – these are the basis of the sequence! Luckily, Bob remembers the first  $ k - 1 $  elements of the sequence:  $ f\_1 = f\_2 = \\ldots = f\_{k - 1} = 1 $  and the  $ n $ -th element:  $ f\_n = m $ . Please find any possible value of  $ f\_k$$$. If no solution exists, just tell Bob that it is impossible to recover his favorite sequence, regardless of Bob's sadness.

## 说明/提示

In the first sample, we have $ f_4 = f_3^2 \cdot f_2^3 \cdot f_1^5 $ . Therefore, applying $ f_3 = 4 $ , we have $ f_4 = 16 $ . Note that there can be multiple answers.

In the third sample, applying $ f_7 = 1 $ makes $ f_{23333} = 1 $ .

In the fourth sample, no such $ f_1 $ makes $ f_{88888} = 66666 $ . Therefore, we output $ -1 $ instead.

## 样例 #1

### 输入

```
3
2 3 5
4 16
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
4 7 1 5 6
7 14187219
```

### 输出

```
6
```

## 样例 #3

### 输入

```
8
2 3 5 6 1 7 9 10
23333 1
```

### 输出

```
1
```

## 样例 #4

### 输入

```
1
2
88888 66666
```

### 输出

```
-1
```

## 样例 #5

### 输入

```
3
998244352 998244352 998244352
4 2
```

### 输出

```
-1
```

## 样例 #6

### 输入

```
10
283 463 213 777 346 201 463 283 102 999
2333333 6263423
```

### 输出

```
382480067
```

# AI分析结果



## 算法分类
**数论**

---

## 综合分析与结论
本题核心思路为将递推式转化为线性同余方程，通过原根、矩阵快速幂、BSGS算法及扩展欧几里得算法求解。关键步骤如下：

1. **原根转换**  
   利用模数998244353的原根3，将递推式转化为指数线性递推：
   $$g_i \equiv \sum_{j=1}^k b_j g_{i-j} \mod (p-1)$$  
   （可视化：红色高亮原根转换公式，展示乘积→求和的推导）

2. **矩阵快速幂求指数**  
   构造转移矩阵，通过快速幂计算递推后的指数关系：
   $$A^{n-k} \text{的右下角元素} r \Rightarrow r \cdot x \equiv \ln(m) \mod (p-1)$$  
   （可视化：蓝色标记矩阵构造，步进展示矩阵乘法过程）

3. **BSGS求离散对数**  
   计算$m$对应的原根指数，转化为线性同余方程：
   $$\text{BSGS}(3, m) \rightarrow \text{得到} \ln(m)$$  
   （可视化：绿色高亮BSGS分块过程，展示哈希表存储中间值）

4. **扩展欧几里得解方程**  
   求解方程$r \cdot x \equiv \ln(m) \mod (p-1)$，验证无解条件  
   （可视化：黄色标记方程求解，展示辗转相除步骤）

---

## 题解清单 (≥4星)
1. **Itst (5星)**  
   - 核心亮点：完整处理模数分解，矩阵乘法优化取模，代码结构清晰  
   - 代码片段：矩阵乘法部分保留中间值的模运算，避免溢出  
   ```cpp
   matrix operator *(matrix b){ // 矩阵乘法优化取模
       matrix c;
       for(int i=0; i<K; ++i)
           for(int j=0; j<K; ++j)
               for(int k=0; k<K; ++k)
                   c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % (MOD-1);
       return c;
   }
   ```

2. **zhiyangfan (4.5星)**  
   - 核心亮点：离散对数推导详细，注释明确，矩阵构造直观  
   - 关键公式：
     $$\begin{bmatrix}lf_{i-k}&...&lf_{i-1}\end{bmatrix} \cdot A = \begin{bmatrix}lf_{i-k+1}&...&lf_i\end{bmatrix}$$

3. **周道_Althen (4星)**  
   - 亮点：代码简洁，重点突出指数递推关系  
   - 代码片段：快速幂优化指数计算  
   ```cpp
   Matrix operator*(const Matrix &b){ // 清晰展示矩阵乘法逻辑
       Matrix c; memset(c.a,0,sizeof(c.a));
       for(int i=1;i<=k;++i)
           for(int j=1;j<=k;++j)
               for(int t=1;t<=k;++t)
                   c.a[i][j] = (c.a[i][j] + a[i][t]*b.a[t][j])%(mod-1);
       return c;
   }
   ```

---

## 最优思路提炼
1. **原根转换技巧**  
   将模意义下的乘积转化为指数加法，利用原根性质简化递推关系。

2. **矩阵构造优化**  
   设计转移矩阵时，将递推系数按列排列，便于快速幂计算指数关系。

3. **BSGS与扩展欧几里得结合**  
   离散对数求值后，通过解线性同余方程确定可行解，注意模数分解后的逆元处理。

---

## 同类型题推荐
1. **P3807 【模板】卢卡斯定理**  
   （模数分解与组合数计算）

2. **P2485 [SDOI2011]计算器**  
   （BSGS算法模板题，含高次同余方程）

3. **P3306 [SDOI2013] 随机数生成器**  
   （递推数列求离散对数）

---

## 可视化与算法演示
**像素化动画设计：**
1. **原根转换阶段**  
   - 显示原始递推式，逐帧转换为指数形式（红色闪烁箭头）
   - 8-bit音效：转换成功时播放"叮"声

2. **矩阵快速幂阶段**  
   - Canvas绘制矩阵，黄色高亮当前计算的行列
   - 步进控制：空格键单步执行矩阵乘法

3. **BSGS遍历阶段**  
   - 分块显示哈希表插入过程，绿色标记碰撞检测
   - 背景音乐：循环8-bit风格旋律，发现匹配时播放上升音阶

4. **方程求解阶段**  
   - 黄色文本框显示方程，红色标记无解条件检查
   - 成功解出时，全屏闪烁绿色，播放胜利音效

**核心JS片段：**
```javascript
// 矩阵快速幂动画
function animateMatrixStep() {
  ctx.fillStyle = "#00FF00"; // 像素绿
  ctx.fillRect(currentRow*32, currentCol*32, 30, 30); // 高亮当前计算单元
  setTimeout(() => {
    if(++step < totalSteps) requestAnimationFrame(animateMatrixStep);
    else playSound('complete'); // 完成音效
  }, 100);
}
```

---

## 个人心得摘录
> "本题调试时发现矩阵乘法未及时取模导致溢出，需注意每步运算后立即取模" —— Itst  
> "BSGS分块大小选择√p+1可避免边界情况" —— zhiyangfan  
> "扩展欧几里得求逆元时需处理gcd非1的情况，否则WA在测试点5" —— 周道_Althen

---
处理用时：63.42秒