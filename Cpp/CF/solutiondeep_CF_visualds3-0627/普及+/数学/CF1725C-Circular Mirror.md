# 题目信息

# Circular Mirror

## 题目描述

Pak Chanek has a mirror in the shape of a circle. There are $ N $ lamps on the circumference numbered from $ 1 $ to $ N $ in clockwise order. The length of the arc from lamp $ i $ to lamp $ i+1 $ is $ D_i $ for $ 1 \leq i \leq N-1 $ . Meanwhile, the length of the arc between lamp $ N $ and lamp $ 1 $ is $ D_N $ .

Pak Chanek wants to colour the lamps with $ M $ different colours. Each lamp can be coloured with one of the $ M $ colours. However, there cannot be three different lamps such that the colours of the three lamps are the same and the triangle made by considering the three lamps as vertices is a right triangle (triangle with one of its angles being exactly $ 90 $ degrees).

The following are examples of lamp colouring configurations on the circular mirror.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/f662b018d5c25548ad3c12ebf7297c4fe9cddb27.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/d15118feff1296e48df6066dea2761fdbf3bbba3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/904b8c54d18751fcd9444e012c7c141ddaf812b7.png)Figure 1. an example of an incorrect colouring because lamps $ 1 $ , $ 2 $ , and $ 3 $ form a right triangleFigure 2. an example of a correct colouringFigure 3. an example of a correct colouringBefore colouring the lamps, Pak Chanek wants to know the number of distinct colouring configurations he can make. Count the number of distinct possible lamp colouring configurations, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, all correct lamp colouring configurations are $ [1, 1, 2, 1] $ , $ [1, 1, 2, 2] $ , $ [1, 2, 1, 2] $ , $ [1, 2, 2, 1] $ , $ [1, 2, 2, 2] $ , $ [2, 1, 1, 1] $ , $ [2, 1, 1, 2] $ , $ [2, 1, 2, 1] $ , $ [2, 2, 1, 1] $ , and $ [2, 2, 1, 2] $ .

## 样例 #1

### 输入

```
4 2
10 10 6 14```

### 输出

```
10```

## 样例 #2

### 输入

```
1 2
10```

### 输出

```
2```

# AI分析结果



---

### **唯一算法分类**
**组合数学**

---

### **综合分析与结论**
**核心思路**：避免同色三点构成直角三角形，等价于禁止同色直径对与第三点同色。通过统计直径对数目，枚举使用i对同色，确保其余点颜色不与这i种冲突。  
**关键推导**：总方案为Σ[C(cnt,i) * A(m,i) * (m-i)^{n-2cnt} * (m-i-1)^{cnt-i} * (m-i)^{cnt-i}]，其中cnt为直径对数。  
**可视化设计**：  
1. **动画步骤**：绘制圆及直径对，高亮选中的i对，显示颜色分配，计算各部分贡献。  
2. **像素风格**：用色块表示点，直径对用连线标记，步骤音效提示计算进度。  
3. **自动推导**：模拟枚举i的过程，动态显示公式各部分计算结果。

---

### **题解清单 (≥4星)**
1. **yingkeqian9217（4.5星）**  
   - **亮点**：公式推导清晰，预处理阶乘优化组合计算，代码简洁高效。  
   - **代码**：使用前缀和统计直径对，快速幂与逆元预处理。  

2. **Mariposa（4星）**  
   - **亮点**：公式总结简洁，代码结构模块化，组合数计算正确。  

3. **江户川·萝卜（4星）**  
   - **亮点**：公式与代码对应明确，正确使用组合数，但变量命名稍显混乱。  

---

### **核心代码实现**
```cpp
// 预处理阶乘和逆元
void init(){
    fac[0] = inv[0] = 1;
    for(int i=1; i<=m; i++) fac[i] = fac[i-1] * i % Mod;
    inv[m] = qpow(fac[m], Mod-2);
    for(int i=m-1; i>=1; i--) inv[i] = inv[i+1] * (i+1) % Mod;
}

// 主计算逻辑
ll ans = 0;
for(int i=0; i<=min(m, cnt); i++){
    ll term = C(cnt, i) * A(m, i) % Mod;
    term = term * qpow(m-i, n - cnt - i) % Mod;
    term = term * qpow(m-i-1, cnt - i) % Mod;
    ans = (ans + term) % Mod;
}
```

---

### **同类型题与套路**
**通用套路**：  
1. 统计禁止结构的出现方式（如直径对）。  
2. 枚举包含k个禁止结构，用组合数学计算合法方案。  
3. 使用容斥或直接乘法原理累加结果。  

**类似题目**：  
1. **洛谷P1450**（硬币组合数，容斥原理）  
2. **洛谷P3773**（禁止子图计数，组合优化）  
3. **洛谷P2523**（排列组合与禁止模式）  

---

### **个人心得摘录**
- **yingkeqian9217**：调试时发现未处理总弧长为奇数的情况，加入特判后通过。  
- **Siteyava_145**：最初误用Lucas定理，后改用预处理阶乘优化计算。  

---

### **复古游戏化动画设计**
1. **像素风格**：  
   - 圆用16色绘制，直径对用黄色连线，选中i对时闪烁绿色。  
   - 当前计算步骤显示在右侧面板，公式项高亮。  

2. **音效设计**：  
   - **步骤音效**：8-bit "blip"声，每计算一个i播放。  
   - **完成音效**：成功累加term时播放上升音阶。  

3. **自动演示**：  
   - 按i从0到cnt逐步展示，动态更新各部分数值，Canvas同步绘制颜色分配。  

```javascript
// 示例：动画更新逻辑（伪代码）
function animateStep(i) {
    highlightDiameterPairs(i); // 高亮当前i对
    updateFormulaDisplay(i); // 显示C(cnt,i), A(m,i)等值
    playSound('step'); // 播放步骤音效
}
```

---

**可视化总结**：通过交互式像素动画，直观展示直径对的统计与颜色分配过程，结合音效增强学习体验，帮助理解组合公式的推导。

---
处理用时：64.20秒