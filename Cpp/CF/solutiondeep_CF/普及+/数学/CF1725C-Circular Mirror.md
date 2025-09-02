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



# Circular Mirror

## 题目描述

Pak Chanek 有一个圆形镜子，圆周上有 $N$ 个灯，按顺时针顺序编号 $1$ 到 $N$。相邻两灯的弧长由数组 $D$ 给出（$D_N$ 为第 $N$ 灯到第 $1$ 灯的弧长）。要求用 $M$ 种颜色给灯染色，使得不存在三个同色灯构成直角三角形。求合法染色方案数模 $998244353$。

## 样例

### 样例 #1
**输入**
```
4 2
10 10 6 14
```
**输出**
```
10
```

### 样例 #2
**输入**
```
1 2
10
```
**输出**
```
2
```

---

## 题解综合分析

### 关键思路总结
1. **几何性质转化**：圆内接直角三角形的斜边必为直径。转化为避免同色直径对+同色第三点的组合。
2. **统计直径对**：计算总周长，若为奇数则无直径对。否则用前缀和和哈希表统计满足弧长为半周长的点对数量 $cnt$。
3. **组合计数**：枚举选 $i$ 对直径染同色，剩余点按规则染色。公式为：
   $$
   \sum_{i=0}^{\min(m,cnt)} \binom{cnt}{i} \cdot A_m^i \cdot (m-i)^{n-cnt-i} \cdot (m-i-1)^{cnt-i}
   $$
4. **模运算优化**：预处理阶乘、逆元，快速幂加速计算。

---

## 优质题解推荐

### 题解一（作者：yingkeqian9217） ★★★★★
**关键亮点**  
- 思路清晰，公式推导严谨，代码结构简洁。
- 正确处理直径对统计，快速幂与组合数预处理优化到位。

**核心代码**  
```cpp
// 预处理阶乘和逆元
void init(){
    fac[0]=inv[0]=1;
    for(int i=1;i<=m;i++) fac[i]=fac[i-1]*i%Mod;
    for(int i=1;i<=m;i++) inv[i]=qpow(fac[i],Mod-2);
}

// 主计算逻辑
for(int i=0;i<=min(m,cnt);i++)
 ans=(ans+qpow(m-i,n-cnt-i)*qpow(m-i-1,cnt-i)%Mod*C(cnt,i)*A(m,i))%Mod;
```

### 题解二（作者：Mariposa） ★★★★★
**关键亮点**  
- 代码简洁高效，直接调用组合数学模块。
- 公式实现无冗余，快速幂与组合数计算高度优化。

**核心代码**  
```cpp
for(int i=0;i<=cnt;i++)
 ans=(ans+1ll*com(cnt,i)*com(m,i)%mod*fac[i]%mod
 *ksm(1ll*(m-i)*(m-i-1)%mod,cnt-i)%mod*ksm(m-i,n-2*cnt))%mod;
```

### 题解三（作者：Siteyava_145） ★★★★☆
**关键亮点**  
- 公式正确但代码稍冗长，使用 Lucas 定理处理组合数。
- 详细注释帮助理解，适合学习组合数扩展应用。

**核心代码**  
```cpp
aans=(aans + lucas(zj, eq) %p * lucas(m, eq) %p * fac[eq] %p 
 * fp((m-eq)*(m-eq-1)%p,zj-eq,p) %p * fp(m-eq,n-zj*2,p))%p;
```

---

## 扩展与推荐
**相似题目**  
1. [CF615D](https://codeforces.com/problemset/problem/615/D)：组合数学与因数分解。
2. [P1350 车的放置](https://www.luogu.com.cn/problem/P1350)：排列组合模型。
3. [CF559C](https://codeforces.com/problemset/problem/559/C)：组合数路径计数。

**心得摘录**  
- "调了好久才找到直径对统计的边界问题" —— 强调几何条件转化的严谨性。
- "枚举时注意颜色不能重复使用" —— 组合枚举的容斥思想是关键。

---
处理用时：287.61秒