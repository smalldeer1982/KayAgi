# 题目信息

# Forecast

## 题目描述

The Department of economic development of IT City created a model of city development till year 2100.

To prepare report about growth perspectives it is required to get growth estimates from the model.

To get the growth estimates it is required to solve a quadratic equation. Since the Department of economic development of IT City creates realistic models only, that quadratic equation has a solution, moreover there are exactly two different real roots.

The greater of these roots corresponds to the optimistic scenario, the smaller one corresponds to the pessimistic one. Help to get these estimates, first the optimistic, then the pessimistic one.

## 样例 #1

### 输入

```
1 30 200
```

### 输出

```
-10.000000000000000
-20.000000000000000```

# AI分析结果



# Forecast

## 题目描述

IT城市经济发展部创建了一个直到2100年的城市发展模型。为了准备增长前景报告，需要从模型中获取增长预测值。这需要解一个二次方程。由于经济发展部只创建现实的模型，该二次方程有且仅有两个不同的实数根。较大的根对应乐观情景，较小的对应悲观情景。请先输出乐观解，再输出悲观解。

## 输入样例

```
1 30 200
```

## 输出样例

```
-10.000000000000000
-20.000000000000000
```

---

**算法分类**：数学

---

### 综合分析与结论

所有题解均基于一元二次方程求根公式。核心难点在于正确处理浮点精度与输出格式。需注意两点：① 判别式开平方只需计算一次，避免重复运算；② 必须输出15位小数。部分题解因输出精度不足或重复计算sqrt导致效率低下被扣分。

---

### 精选题解

#### 1. jimmyfj（5星）
**关键亮点**：  
- 正确使用15位小数输出格式  
- 预先计算sqrt结果提升效率  
- 直接使用max/min函数简化比较逻辑  

**核心代码**：  
```cpp
double a, b, c, DT;
scanf("%lf %lf %lf", &a, &b, &c);
DT = sqrt(b * b - 4.0 * a * c);
printf("%.15lf\n%.15lf", 
       max((-b + DT)/(2*a), (-b - DT)/(2*a)),
       min((-b + DT)/(2*a), (-b - DT)/(2*a)));
```
**实现思想**：  
计算判别式的平方根存入变量DT，避免重复运算。直接通过max/min函数比较两个解的大小。

---

#### 2. tommyfj（4星）
**关键亮点**：  
- 严格遵循15位小数格式  
- 分离计算步骤增强可读性  

**核心代码**：  
```cpp
double delta = b*b - 4.0*a*c;
double delta1 = sqrt(delta);
double maxn = max((-b - delta1)/(2*a), (-b + delta1)/(2*a));
printf("%.15lf\n%.15lf", maxn, min(...));
```
**实现思想**：  
将判别式计算与开平方分离，通过中间变量提升代码可维护性。

---

### 优化技巧总结
- **避免重复计算**：将sqrt结果存入变量，避免重复调用数学函数。  
- **数值稳定性**：当a为负数时，比较逻辑仍能正确识别大小关系。  
- **输出精度控制**：必须使用15位小数格式以满足题目精度要求。

---

### 拓展练习
1. **P1024** [一元三次方程求解] - 浮点根的高精度求解  
2. **P1039** [计算系数] - 多项式展开中的数学应用  
3. **P1054** [等价表达式] - 方程解的等价性验证

---
处理用时：171.37秒