# 题目信息

# The Supersonic Rocket

## 题目描述

After the war, the supersonic rocket became the most common public transportation.

Each supersonic rocket consists of two "engines". Each engine is a set of "power sources". The first engine has $ n $ power sources, and the second one has $ m $ power sources. A power source can be described as a point $ (x_i, y_i) $ on a 2-D plane. All points in each engine are different.

You can manipulate each engine separately. There are two operations that you can do with each engine. You can do each operation as many times as you want.

1. For every power source as a whole in that engine: $ (x_i, y_i) $ becomes $ (x_i+a, y_i+b) $ , $ a $ and $ b $ can be any real numbers. In other words, all power sources will be shifted.
2. For every power source as a whole in that engine: $ (x_i, y_i) $ becomes $ (x_i \cos \theta - y_i \sin \theta, x_i \sin \theta + y_i \cos \theta) $ , $ \theta $ can be any real number. In other words, all power sources will be rotated.

The engines work as follows: after the two engines are powered, their power sources are being combined (here power sources of different engines may coincide). If two power sources $ A(x_a, y_a) $ and $ B(x_b, y_b) $ exist, then for all real number $ k $ that $ 0 \lt k \lt 1 $ , a new power source will be created $ C_k(kx_a+(1-k)x_b,ky_a+(1-k)y_b) $ . Then, this procedure will be repeated again with all new and old power sources. After that, the "power field" from all power sources will be generated (can be considered as an infinite set of all power sources occurred).

A supersonic rocket is "safe" if and only if after you manipulate the engines, destroying any power source and then power the engine, the power field generated won't be changed (comparing to the situation where no power source erased). Two power fields are considered the same if and only if any power source in one field belongs to the other one as well.

Given a supersonic rocket, check whether it is safe or not.

## 说明/提示

The first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/1f54366cb2efd6f1fd1d0617b722b5e3979dfd89.png)Those near pairs of blue and orange points actually coincide.First, manipulate the first engine: use the second operation with $ \theta = \pi $ (to rotate all power sources $ 180 $ degrees).

The power sources in the first engine become $ (0, 0) $ , $ (0, -2) $ , and $ (-2, 0) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/d9732486b953667a46772450be0d244f2cb20626.png)Second, manipulate the second engine: use the first operation with $ a = b = -2 $ .

The power sources in the second engine become $ (-2, 0) $ , $ (0, 0) $ , $ (0, -2) $ , and $ (-1, -1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/f5d3a1ffc842f837240530d5f9c0ef57b3d408b7.png)You can examine that destroying any point, the power field formed by the two engines are always the solid triangle $ (0, 0) $ , $ (-2, 0) $ , $ (0, -2) $ .

In the second sample, no matter how you manipulate the engines, there always exists a power source in the second engine that power field will shrink if you destroy it.

## 样例 #1

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
1 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
0 0
```

### 输出

```
NO
```

# AI分析结果



### 算法分类
计算几何（凸包） + 字符串匹配（KMP）

---

### 题解思路与核心难点
**核心思路**：将两个引擎的凸包转换为边-角度序列，判断是否可以通过旋转得到对方。  
**关键步骤**：
1. **求凸包**：使用 Andrew 算法处理坐标点，生成上下凸壳。
2. **序列生成**：记录凸包每条边的长度，及相邻边的夹角（通过向量点积计算）。
3. **循环匹配**：将其中一个序列复制两倍，用 KMP 算法判断另一个序列是否为其子串。

**解决难点**：
- **几何到序列的转换**：通过记录边和角度的组合，保证序列唯一性。
- **旋转同构**：通过序列的循环特性，将原序列扩展两倍覆盖所有旋转可能。
- **精度处理**：使用 `eps` 比较浮点数，避免精度误差导致错误。

---

### 题解评分（≥4星）
1. **cjlak1o1（5星）**  
   - 亮点：通过边和三角形边的组合确保唯一性，处理线段退化情况，代码逻辑清晰。
2. **KKarshilov（4星）**  
   - 亮点：精确处理角度计算，引入 `dcmp` 函数处理浮点精度。
3. **Hoks（4星）**  
   - 亮点：特判 `NaN` 避免数值错误，精简代码结构。

---

### 最优思路与技巧
1. **凸包序列化**：将凸包的边与角度转化为唯一序列，保证旋转后的循环匹配。
2. **KMP 应用**：将几何问题转化为字符串匹配问题，扩展序列处理循环同构。
3. **精度控制**：使用 `eps` 和整数运算避免浮点误差。

---

### 类似题目推荐
1. **P2742 [USACO5.1]圈奶牛**（凸包模板题）  
2. **P3829 [SHOI2012]信用卡凸包**（凸包应用）  
3. **P4196 [CQOI2006]凸多边形**（半平面交与几何匹配）

---

### 核心代码实现（题解1）
```cpp
// 凸包生成（Andrew算法）
void Andrew(int n) {
    sort(p+1, p+n+1);
    st[1]=p[1], top=1;
    for(int i=2; i<=n; i++) {
        while(top>=2 && check(st[top-1], st[top], p[i]) <=0) top--;
        st[++top] = p[i];
    }
    int tt=top;
    for(int i=n-1; i>=1; i--) {
        while(top>=tt+1 && check(st[top-1], st[top], p[i]) <=0) top--;
        st[++top] = p[i];
    }
}

// 序列生成（边与跨边）
void build1(int n) {
    for(int i=3; i<=n; i++) {
        a[cnt1++] = _dis(st[i-1], st[i-2]);
        a[cnt1++] = _dis(st[i], st[i-1]);
        a[cnt1++] = _dis(st[i], st[i-2]);
    }
}

// KMP匹配
bool comp(db a[], db b[]) {
    for(int i=0; i<cnt1; i++) a[i+cnt1] = a[i];
    // KMP预处理与匹配逻辑...
}
```

---

### 可视化与算法演示
**动画设计**：  
1. **凸包构建**：逐步绘制点的排序、上下凸壳形成过程。  
2. **序列生成**：高亮当前处理的边和角度，生成序列元素。  
3. **KMP匹配**：动态展示模式串与扩展串的指针移动，匹配成功时高亮对应位置。  

**复古像素风格**：  
- **颜色方案**：凸包点用蓝色，边用绿色，当前操作元素用红色闪烁。  
- **音效**：边生成时触发 "beep"，匹配成功播放胜利音效。  
- **自动演示**：按步播放构建与匹配过程，支持暂停/步进。  

**交互设计**：  
- **控制面板**：速度滑块、暂停/继续按钮、重置功能。  
- **Canvas绘制**：用网格坐标系展示凸包，序列以滚动条显示。  

---

### 个人心得摘录
- **精度陷阱**：浮点比较需用 `eps`，避免直接 `==`（题解1未显式处理，可能导致边界错误）。  
- **凸包退化**：处理线段或单点情况需特判（如题解1的 `if(top==4)`）。  
- **KMP优化**：模式串预处理可大幅提升匹配效率。

---
处理用时：117.93秒