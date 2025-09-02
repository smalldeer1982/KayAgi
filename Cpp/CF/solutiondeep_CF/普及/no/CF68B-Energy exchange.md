# 题目信息

# Energy exchange

## 题目描述

It is well known that the planet suffers from the energy crisis. Little Petya doesn't like that and wants to save the world. For this purpose he needs every accumulator to contain the same amount of energy. Initially every accumulator has some amount of energy: the $ i $ -th accumulator has $ a_{i} $ units of energy. Energy can be transferred from one accumulator to the other. Every time $ x $ units of energy are transferred ( $ x $ is not necessarily an integer) $ k $ percent of it is lost. That is, if $ x $ units were transferred from one accumulator to the other, amount of energy in the first one decreased by $ x $ units and in other increased by ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF68B/b2812228d37ba851de724c292afa8e13e0ea3f33.png) units.

Your task is to help Petya find what maximum equal amount of energy can be stored in each accumulator after the transfers.

## 样例 #1

### 输入

```
3 50
4 2 1
```

### 输出

```
2.000000000
```

## 样例 #2

### 输入

```
2 90
1 11
```

### 输出

```
1.909090909
```

# AI分析结果



# 能量交换

## 题目描述

已知每个储能器初始有 $a_i$ 单位能量。每次转移 $x$ 单位能量会损失 $k\%$（即接收方获得 $x(1-\frac{k}{100})$）。求所有储能器能达到的相等能量最大值。

## 样例 #1

### 输入
3 50
4 2 1

### 输出
2.000000000

## 样例 #2

### 输入
2 90
1 11

### 输出
1.909090909

---

**算法分类**: 二分

---

## 题解综合分析

### 思路共性
1. **二分框架**：所有题解均采用浮点数二分法，在 [0, max(a_i)] 范围内搜索最大可行值
2. **可行性判定**：计算超过mid的总能量（可转移量）和不足mid的总缺口，考虑k%损耗后是否满足
3. **精度控制**：使用 1e-8 级别精度终止条件

### 关键差异
| 题解 | 初始范围设定 | 变量命名 | 代码优化点 |
|-----|------------|---------|-----------|
| vanueber | [0,10000] | s1/s2 清晰 | 逻辑判断直接返回布尔值 |
| yutong | [0,1e4] | big/small 更直观 | 使用函数封装判断逻辑 |
| A_B_ | [0,1000] | need/extra 专业 | 使用const常量定义精度 |

---

## 精选题解（评分≥4★）

### 1. vanueber（4.5★）
**亮点**：
- 变量命名清晰（s1/s2）
- 注释明确能量转移计算逻辑
- 预处理100.0避免重复计算
**关键代码**：
```cpp
bool check(double x) {
    double s1 = 0, s2 = 0;
    for(int i=1; i<=n; i++) {
        if(a[i] < x) s1 += x - a[i]; 
        else s2 += a[i] - x;
    }
    return s2*(100.0-k)/100 >= s1;
}
```

### 2. yutong_Seafloor（4★）
**亮点**：
- 使用函数封装判断逻辑
- 变量命名big/small更易理解
**调试心得**：
"注意小数点取8位，printf会自动四舍五入"

### 3. A_B_（4★）
**亮点**：
- 使用const常量定义精度
- 变量命名need/extra专业
**实现技巧**：
将判断条件直接写为 return 表达式，简化代码

---

## 最优策略总结

**核心思路**：
1. **问题转化**：将最值问题转化为判定性问题，利用二分的单调性
2. **能量守恒计算**：Σ(多出量)*(1-k%) ≥ Σ(缺少量)
3. **浮点处理**：使用相对精度控制（1e-8）而非绝对循环次数

**实现要点**：
```cpp
// 典型二分框架
double l=0, r=1e4;
while(r-l > 1e-8) {
    double mid = (l+r)/2;
    if(check(mid)) l = mid;
    else r = mid;
}
```

---

## 拓展应用

**同类题目推荐**：
1. P1577 切绳子（二分答案基础）
2. P3743 kotori的设备（带能耗的充电问题）
3. P2855 [USACO06DEC]River Hopscotch（最大化最小值）

**技巧迁移**：
当遇到"最大/最小化某个值，且验证过程具有单调性"的问题时，均可考虑二分答案框架。例如：
- 分配问题中的公平性最大化
- 资源调度中的最小化等待时间
- 工程优化中的参数临界值确定

---

## 心得摘录

"浮点二分的精度控制需要结合题目要求，通常取1e-8足够应对大多数情况" —— vanueber  
"判断条件要理清能量守恒关系，注意转移后的有效能量是乘以(100-k)/100" —— yutong_Seafloor  
"初始范围不必严格限制在输入极值，适当扩大范围更安全" —— LOLchn0

---
处理用时：48.46秒