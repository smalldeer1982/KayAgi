# 题目信息

# 「LCOI2022」 Cow Dance

## 题目背景

Bessie 带着他的奶牛姐妹们来跳舞了。

她们已经规划好了跳舞的步骤，但是为了更加美观，她们需要知道其中一些头奶牛在某时的平均位置，已达到更完美的表演效果。

不幸的是，由于 Bessie 的姐妹太多了，最多会有 $8\times 10^4$ 只奶牛同时来跳舞。她没有什么方便且快速的方法算这些平均位置，所以向你求助。

## 题目描述

Bessie 和她的姐妹们已经排好了位置，第 $i$ 头奶牛的坐标为 $(x_i,y_i)$。其中，$x_i$ 是 $x$ 轴坐标，$y_i$ 是 $y$ 轴坐标。

她们的舞蹈队形会有这几种变换方式：
1. 移动：$x$ 到 $y$ 号奶牛的 $x_i\to x_i+a$，$y_i\to y_i+b$。
1. 旋转：$x$ 到 $y$ 号奶牛以 $(a,b)$ 为旋转中心顺时针旋转 $g°$。
1. 散开: $x$ 到 $y$ 号奶牛以 $(a,b)$ 为中心散开为 $\dfrac{p}{q}$ 倍。即设之前奶牛坐标为 $A$，散开后坐标为 $B$，$(a,b)$ 为 $G$，$\overrightarrow{GB}=\dfrac{p}{q}\overrightarrow{GA}$。

Bessie 想知道：对于 $x$ 到 $y$ 号奶牛，他们的平均位置 $(\frac{\sum\limits^y_{i=x}x_i}{y-x+1},\frac{\sum\limits^y_{i=x}y_i}{y-x+1})$。

舞会就要开始了，所以她只能给你 $\texttt{1s}$ 的时间。

## 说明/提示

【样例解释】
![](https://cdn.luogu.com.cn/upload/image_hosting/3jt6apa4.png)

$0$ 为初始情况。$1$ 为进行样例中 `1 1 2 1 -2` 操作后结果。$2$ 为进行样例中 `2 1 3 2 0 270` 操作后结果。$3$ 为进行样例中 `3 1 2 2 2 2 1` 操作后结果。

【数据范围与约定】

保证运算时所有数的绝对值小于或等于 $10^{15}$。

|subtask|特殊限制|分数|
|:-:|:-:|:-:|
|$1$|$1\le n,m\le10^3$|$8$|
|$2$|只有旋转操作且都按奶牛为旋转中心|$18$|
|$3$|只有散开操作且都按奶牛为位似中心|$18$|
|$4$|没有旋转和散开操作|$8$|
|$5$|对于所有操作和询问 $x=y$|$18$|
|$6$|旋转中心和散开中心都是奶牛|$8$|
|$7$|$1\le n,m\le 8\times10^4$|$10$|
|$8$|没有特殊限制|$12$|

对于 $100\%$ 的数据，$1\le n,m\le3\times10^5$，$1\le x\le y\le n$，$-32768\le a,b<32768$，$0< \dfrac{p}{q}\le 233333$，$0\le g\le359$，初始坐标限制同 $a,b$。

### **注：**
- **请注意常数因子优化。**
- **此题输入输出量较大，建议使用 `scanf` 和 `printf`。**

## 样例 #1

### 输入

```
3 7
1 1
1 3
3 1
1 1 2 1 -2
4 1 3
2 1 3 2 0 270
4 1 2
3 1 2 2 2 2 1
4 1 3
4 3 3```

### 输出

```
2.3333333333 0.3333333333
2.0000000000 0.0000000000
1.6666666667 -1.0000000000
1.0000000000 1.0000000000```

# AI分析结果



# 算法分类  
线段树结合线性变换（矩阵/复数）

---

## 综合分析与结论  
### 核心思路  
所有题解均基于**线段树维护几何变换**的核心逻辑，将平移、旋转、位似操作转化为矩阵乘法或复数运算。通过线段树**合并区间变换参数**，在保证 O(n logn) 时间复杂度的前提下，解决大规模区间操作与查询问题。

### 核心难点与解决方案  
1. **几何变换的数学表示**  
   - 平移：直接加法运算  
   - 旋转：分解为原点平移→旋转→反向平移的复合矩阵/复数运算  
   - 位似：分解为原点平移→缩放→反向平移  
   - 数学推导：通过线性代数或复数运算，将几何变换统一为可叠加的表达式  

2. **线段树懒标记的合并**  
   - 矩阵方法：维护 3×3 变换矩阵，合并时进行矩阵乘法  
   - 复数方法：维护复数乘法因子（旋转/缩放）和加法因子（平移）  
   - 四参数法：用四个参数 (A,B,C,D) 表示变换方程 x'=Ax+By+C, y'=-Bx+Ay+D  

3. **常数优化**  
   - 矩阵展开：将矩阵元素展开为独立变量，避免结构体操作（STA_Morlin）  
   - 复数运算优化：利用复数乘法的代数性质减少计算量（Link_Cut_Y）  

### 可视化设计要点  
1. **动画方案**  
   - **网格坐标系**：用 Canvas 绘制平面网格，每个点表示奶牛  
   - **颜色标记**：操作区间用高亮色块标记，变换后坐标用不同颜色显示  
   - **步进控制**：单步展示平移、旋转、缩放对区间内点的影响  

2. **复古像素风格**  
   - **8位音效**：矩阵合并时播放“哔”声，查询时播放“叮”声  
   - **像素动画**：用 16×16 像素块表示奶牛，变换时产生拖影效果  
   - **自动演示模式**：模拟贪吃蛇式路径，自动遍历三种操作类型  

---

## 题解清单 (≥4星)  
### 1. STA_Morlin（⭐⭐⭐⭐⭐）  
**核心亮点**：  
- 使用 3×3 矩阵统一所有几何变换  
- 将矩阵元素拆分为独立变量优化计算  
- 提供完整的矩阵乘法推导公式  

**代码片段**：  
```cpp  
struct mat {
    double a, b, c, d, e, f, g, h, i;
    mat operator*(mat x) { // 展开的矩阵乘法
        return { a*x.a + b*x.d + c*x.g, a*x.b + b*x.e + c*x.h, ..., 
                g*x.c + h*x.f + i*x.i };
    }
};
void mod(int p, int l, int r, int x, int y) {
    if (x <= l && y >= r) { 
        g[p] = t * g[p]; // 合并懒标记
        f[p] = t * f[p]; // 更新区间和
        return; 
    }
    // 下传标记逻辑
}
```

### 2. kbtyyds（⭐⭐⭐⭐）  
**核心亮点**：  
- 提出四参数线性变换方程  
- 推导懒标记合并公式  
- 实现简洁的标记下传逻辑  

**代码片段**：  
```cpp  
void pushone(int o, double a, double b, double c, double d) {
    // 新标记与旧标记的合并公式
    double A = taga[o], B = tagb[o], C = tagc[o], D = tagd[o];
    taga[o] = a*A - b*B;
    tagb[o] = a*B + b*A;
    tagc[o] = a*C + b*D + c;
    tagd[o] = a*D - b*C + d;
}
```

### 3. Link_Cut_Y（⭐⭐⭐⭐）  
**核心亮点**：  
- 复数表示坐标与变换  
- 利用复数乘法的旋转性质  
- 代码结构清晰易扩展  

**代码片段**：  
```cpp  
struct Complex {
    double x, y; // 表示复数 x + yi
    Complex operator*(Complex p) { 
        return {x*p.x - y*p.y, x*p.y + y*p.x}; 
    }
};
void rotate(int l, int r, int a, int b, int g) {
    Complex center(a, b);
    update_mul(l, r, Complex(cos(g), -sin(g))); // 旋转因子
    update_add(l, r, center * (Complex(1,0) - rotate_factor)); 
}
```

---

## 同类型题与推荐题目  
1. **CF618E** - 机械臂（线段树维护矩阵变换）  
2. **洛谷P7453** - 矩阵变换与区间查询  
3. **HDU6317** - 带旋转操作的区间统计  

---

## 可视化算法演示  
### 核心动画流程  
1. **初始化**  
   - 绘制平面坐标系，初始点随机分布  
   - 线段树结构以二叉树形式侧边展示  

2. **操作演示**  
   - **平移**：选中区间向右上方平移，显示箭头动画  
   - **旋转**：围绕中心点显示旋转轨迹，伴随角度刻度  
   - **位似**：区间点向外扩散，显示缩放比例  

3. **查询反馈**  
   - 显示红色十字标记平均坐标位置  
   - 输出面板实时显示计算结果  

### 复古游戏化设计  
- **音效设计**：  
  - 矩阵合并：8-bit "哔"声（Web Audio API）  
  - 正确查询：FC风格通关音效  
- **积分系统**：  
  - 每完成10次操作解锁一个成就徽章  
  - 连续正确查询触发连击奖励  

---

## 关键代码实现  
**复数变换核心逻辑**：  
```javascript  
class ComplexTransform {
    constructor() {
        this.mul = { real: 1, imag: 0 }; // 乘法因子
        this.add = { real: 0, imag: 0 }; // 加法因子
    }

    apply(point) {
        // 先乘后加
        let x = point.real * this.mul.real - point.imag * this.mul.imag;
        let y = point.real * this.mul.imag + point.imag * this.mul.real;
        return { real: x + this.add.real, imag: y + this.add.imag };
    }

    combine(newMul, newAdd) {
        // 合并新旧变换参数
        const oldMul = this.mul, oldAdd = this.add;
        this.mul = {
            real: oldMul.real * newMul.real - oldMul.imag * newMul.imag,
            imag: oldMul.real * newMul.imag + oldMul.imag * newMul.real
        };
        this.add = {
            real: oldAdd.real * newMul.real - oldAdd.imag * newMul.imag + newAdd.real,
            imag: oldAdd.real * newMul.imag + oldAdd.imag * newMul.real + newAdd.imag
        };
    }
}
```

---

## 总结  
本题解系统通过**复合几何变换的数学建模**与**线段树的高效区间维护**，展现了处理动态几何问题的经典范式。掌握矩阵/复数变换的表示方法与懒标记合并技巧，是解决此类问题的关键。实际编码时需特别注意浮点数精度控制与常数优化。

---
处理用时：102.07秒