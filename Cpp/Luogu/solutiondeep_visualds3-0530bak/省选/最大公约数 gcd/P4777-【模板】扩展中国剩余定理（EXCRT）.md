# 题目信息

# 【模板】扩展中国剩余定理（EXCRT）

## 题目描述

给定 $n$ 组非负整数 $a_i, b_i$ ，求解关于 $x$ 的方程组的最小非负整数解。
$$\begin{cases}x\equiv b_1\pmod{a_1}\\x\equiv b_2\pmod{a_2}\\\dots\\x\equiv b_n\pmod{a_n}\end{cases}$$

## 说明/提示

对于 $100 \%$ 的数据，$1 \le n \le {10}^5$，$1 \le b_i,a_i \le {10}^{12}$，保证所有 $a_i$ 的最小公倍数不超过 ${10}^{18}$。

**请注意程序运行过程中进行乘法运算时结果可能有溢出的风险。**

数据保证有解。

## 样例 #1

### 输入

```
3
11 6
25 9
33 17
```

### 输出

```
809```

# AI分析结果



**唯一算法分类**：数学-扩展中国剩余定理（EXCRT）

---

### **综合分析与结论**
#### **核心算法流程**
1. **方程合并机制**：  
   对于每个同余方程 $x \equiv b_i \pmod{a_i}$，通过扩展欧几里得算法将其与前序合并结果联立，转化为线性方程 $k_1m_1 - k_2m_2 = a_2 - a_1$，求解后得到新的模数（LCM）和余数。

2. **溢出处理**：  
   使用**快速乘（龟速乘）**避免大数相乘溢出，如 `mul(x, c/gcd, bg)` 确保中间结果在模数范围内。

3. **关键变量更新**：  
   - **当前余数**：`ans = (ans + x * M) % new_mod`
   - **当前模数**：`M = lcm(M, a_i)`

#### **可视化设计思路**
- **动画演示**：  
  1. 用像素方块表示每个方程，合并时两方块碰撞后生成新方块（显示新模数LCM）。
  2. **颜色高亮**：当前处理的方程对用红色边框，exgcd计算过程用绿色流动线条表示。
  3. **音效触发**：合并成功时播放“叮”声，无解时播放“错误”音效。

- **复古风格**：  
  采用FC红白机8位风格，模数显示为二进制LED屏样式，余数以滚动数字呈现。

---

### **题解清单 (≥4星)**
1. **阮行止（5星）**  
   - 推导严谨，数学证明清晰，代码使用Python实现合并逻辑，适合理论理解。
   - **关键亮点**：通过构造通解形式证明唯一性，代码中`uni`函数体现合并核心。

2. **niiick（4星）**  
   - C++实现高效，处理输入反序问题，快速乘防止溢出。
   - **关键亮点**：`excrt()`函数逐次合并，`mul`函数优化大数运算。

3. **nekko（4星）**  
   - 使用`__int128`避免中间溢出，代码简洁，适合高精度场景。
   - **关键亮点**：`merge()`函数直接操作模数分解，高效计算LCM。

---

### **最优思路与技巧提炼**
1. **逐步合并法**：  
   每次合并两个方程为 $x \equiv r \pmod{\text{lcm}(m_1,m_2)}$，最终合并所有方程。

2. **快速乘防溢出**：  
   ```cpp
   ll mul(ll a, ll b, ll mod) {
       ll res = 0;
       while (b) {
           if (b & 1) res = (res + a) % mod;
           a = (a + a) % mod;
           b >>= 1;
       }
       return res;
   }
   ```

3. **exgcd参数处理**：  
   求解 $m_1t_1 + m_2t_2 = \gcd(m_1,m_2)$，缩放解以匹配余数差。

---

### **相似题目推荐**
1. [P1495 曹冲养猪](https://www.luogu.com.cn/problem/P1495)（CRT模板）
2. [P3868 [TJOI2009]猜数字](https://www.luogu.com.cn/problem/P3868)（CRT应用）
3. [P2480 [SDOI2010]古代猪文](https://www.luogu.com.cn/problem/P2480)（扩展CRT与组合数）

---

### **代码实现（核心逻辑）**
```cpp
typedef __int128 ll;
ll excrt(vector<pair<ll, ll>> eq) {
    ll M = eq[0].first, ans = eq[0].second;
    for (int i = 1; i < eq.size(); ++i) {
        ll a = eq[i].first, b = eq[i].second;
        ll g = gcd(M, a), c = ((b - ans) % a + a) % a;
        if (c % g != 0) return -1; // 无解
        ll x, y;
        exgcd(M, a, x, y);
        x = mul(x, c / g, a / g); // 快速乘缩放
        ans += x * M;
        M = M / g * a; // 更新模数为LCM
        ans = (ans % M + M) % M;
    }
    return ans;
}
```

---

### **可视化代码片段（Canvas动画）**
```javascript
// 绘制方程合并过程（伪代码）
function drawMergeStep(ctx, eq1, eq2, mergedEq) {
    // 绘制方程1和方程2方块
    drawEquation(ctx, eq1, {x: 100, y: 200, color: '#FF0000'});
    drawEquation(ctx, eq2, {x: 300, y: 200, color: '#00FF00'});
    // 显示exgcd计算过程
    animateLine(ctx, eq1.pos, eq2.pos, () => {
        // 显示合并后的新方块
        drawEquation(ctx, mergedEq, {x: 200, y: 100, color: '#FFFF00'});
        playSound('merge_success.wav');
    });
}
```

---

### **个人心得摘录**
> **调试踩坑**：未处理负数取模导致中间结果错误，需用 `(ans % M + M) % M` 确保非负。  
> **优化经验**：`__int128`在允许使用的平台大幅简化代码，否则必须用龟速乘。  
> **顿悟时刻**：合并后的模数实为LCM，而非简单相乘，避免后续计算错误。

---
处理用时：65.57秒